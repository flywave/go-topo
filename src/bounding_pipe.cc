#include "bounding_pipe.hh"

#include <BRepAdaptor_CompCurve.hxx>
#include <BRepAdaptor_Curve.hxx>
#include <BRepAdaptor_Surface.hxx>
#include <BRepAlgoAPI_Cut.hxx>
#include <BRepAlgoAPI_Section.hxx>
#include <BRepBndLib.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_MakeVertex.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_Sewing.hxx>
#include <BRepExtrema_DistShapeShape.hxx>
#include <BRepGProp.hxx>
#include <BRepLib.hxx>
#include <BRepMesh_IncrementalMesh.hxx>
#include <BRepOffsetAPI_MakePipeShell.hxx>
#include <BRepPrimAPI_MakePrism.hxx>
#include <BRepTools.hxx>
#include <BRep_Tool.hxx>
#include <GCPnts_AbscissaPoint.hxx>
#include <GCPnts_UniformAbscissa.hxx>
#include <GProp_GProps.hxx>
#include <GeomAPI_ExtremaCurveCurve.hxx>
#include <GeomAPI_PointsToBSpline.hxx>
#include <GeomAPI_ProjectPointOnCurve.hxx>
#include <GeomAPI_ProjectPointOnSurf.hxx>
#include <GeomAdaptor_Curve.hxx>
#include <Geom_BSplineCurve.hxx>
#include <Geom_Circle.hxx>
#include <Geom_Curve.hxx>
#include <Geom_Line.hxx>
#include <Geom_Plane.hxx>
#include <Geom_RectangularTrimmedSurface.hxx>
#include <Geom_Surface.hxx>
#include <Geom_TrimmedCurve.hxx>
#include <Poly_Triangulation.hxx>
#include <Precision.hxx>
#include <ShapeAnalysis_Curve.hxx>
#include <ShapeAnalysis_FreeBounds.hxx>
#include <ShapeAnalysis_Surface.hxx>
#include <ShapeFix_Shape.hxx>
#include <TColgp_Array1OfPnt.hxx>
#include <TopExp.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Shell.hxx>
#include <TopoDS_Vertex.hxx>
#include <TopoDS_Wire.hxx>
#include <algorithm>
#include <gp_Ax1.hxx>
#include <gp_Circ.hxx>
#include <gp_Dir.hxx>
#include <gp_Pln.hxx>
#include <gp_Vec.hxx>
#include <gp_XYZ.hxx>
#include <math_Jacobi.hxx>
#include <math_Matrix.hxx>

namespace flywave {
namespace topo {

extern TopoDS_Wire
clip_wire_between_distances_helper(const TopoDS_Wire &wire_path,
                                   double start_distance, double end_distance);

// 新增方法：从形状中提取所有三角网格顶点
std::vector<gp_Pnt> extract_shape_points(const TopoDS_Shape &shape) {
  // 1. 网格化形状（如果还不是离散形式）
  BRepMesh_IncrementalMesh mesher(shape, 0.1, false, 0.5, true);
  mesher.Perform();

  // 2. 提取所有顶点
  std::vector<gp_Pnt> points;
  TopExp_Explorer faceExplorer(shape, TopAbs_FACE);
  for (; faceExplorer.More(); faceExplorer.Next()) {
    TopoDS_Face face = TopoDS::Face(faceExplorer.Current());
    TopLoc_Location loc;
    Handle(Poly_Triangulation) triangulation =
        BRep_Tool::Triangulation(face, loc);
    if (!triangulation.IsNull()) {
      const Poly_ArrayOfNodes &nodes = triangulation->InternalNodes();
      for (int i = nodes.Lower(); i <= nodes.Upper(); ++i) {
        points.push_back(nodes.Value(i));
      }
    }
  }
  return points;
}

// 从任意形状拟合中心线
Handle(Geom_Curve)
    fit_centerline_from_shape(const TopoDS_Shape &shape, int numSamples,
                              int splineDegree, double smoothingFactor) {
  // 1. 提取形状点
  std::vector<gp_Pnt> points = extract_shape_points(shape);

  // 处理空点集的情况
  if (points.empty()) {
    return nullptr;
  }

  // 3. 计算点集重心
  gp_XYZ centroid(0, 0, 0);
  for (const auto &p : points) {
    centroid += p.XYZ();
  }
  centroid /= points.size();

  // 4. 计算协方差矩阵
  math_Matrix cov(1, 3, 1, 3, 0.0);
  for (const auto &p : points) {
    gp_XYZ diff = p.XYZ() - centroid;
    cov(1, 1) += diff.X() * diff.X();
    cov(1, 2) += diff.X() * diff.Y();
    cov(1, 3) += diff.X() * diff.Z();
    cov(2, 1) += diff.Y() * diff.X();
    cov(2, 2) += diff.Y() * diff.Y();
    cov(2, 3) += diff.Y() * diff.Z();
    cov(3, 1) += diff.Z() * diff.X();
    cov(3, 2) += diff.Z() * diff.Y();
    cov(3, 3) += diff.Z() * diff.Z();
  }

  // 5. PCA（雅可比法求特征向量）
  math_Jacobi jacobi(cov);
  math_Vector eigenValues(1, 3);
  math_Matrix eigenVectors(1, 3, 1, 3);

  eigenValues = jacobi.Values();
  eigenVectors = jacobi.Vectors();

  // 6. 确定最大特征值对应的主轴方向
  int maxIndex = 1;
  double maxEigenValue = eigenValues(1);
  if (eigenValues(2) > maxEigenValue) {
    maxIndex = 2;
    maxEigenValue = eigenValues(2);
  }
  if (eigenValues(3) > maxEigenValue) {
    maxIndex = 3;
  }

  gp_Dir axis(eigenVectors(1, maxIndex), eigenVectors(2, maxIndex),
              eigenVectors(3, maxIndex));

  // 7. 沿主轴方向投影点
  std::vector<std::pair<double, gp_Pnt>> projectedPoints;
  for (const auto &p : points) {
    gp_Vec vecToPoint = p.XYZ() - centroid;
    double projection = vecToPoint.Dot(gp_Vec(axis));
    projectedPoints.push_back({projection, p});
  }

  // 8. 按投影值排序
  std::sort(
      projectedPoints.begin(), projectedPoints.end(),
      [](const std::pair<double, gp_Pnt> &a,
         const std::pair<double, gp_Pnt> &b) { return a.first < b.first; });

  // 9. 创建初始中心线点
  double minProjection = projectedPoints.front().first;
  double maxProjection = projectedPoints.back().first;
  double step = (maxProjection - minProjection) / (numSamples - 1);

  TColgp_Array1OfPnt centerlinePoints(1, numSamples);
  for (int i = 1; i <= numSamples; ++i) {
    double proj = minProjection + (i - 1) * step;
    gp_Pnt centerPoint = centroid + axis.XYZ() * proj;
    centerlinePoints.SetValue(i, centerPoint);
  }

  // 10. 拟合初始B样条曲线
  Handle(Geom_BSplineCurve) centerline;
  GeomAPI_PointsToBSpline fitter;
  fitter.Init(centerlinePoints, splineDegree, 8); // 3阶曲线，最大分段数8
  if (fitter.IsDone()) {
    centerline = fitter.Curve();
  } else {
    // 简单回退：使用直线
    gp_Lin line(centroid, axis);
    return new Geom_Line(line);
  }

  // 11. 迭代优化中心线
  for (int iter = 0; iter < 5; ++iter) {
    // 11.1 沿中心线均匀采样
    GeomAdaptor_Curve adaptor(centerline);
    GCPnts_UniformAbscissa abscissa(adaptor, numSamples);
    if (!abscissa.IsDone())
      break;

    // 11.2 更新中心线点
    TColgp_Array1OfPnt centerlinePoints(1, abscissa.NbPoints());
    for (int i = 1; i <= abscissa.NbPoints(); i++) {
      double param = abscissa.Parameter(i);
      gp_Pnt point = centerline->Value(param);

      // 11.3 收集附近点
      double searchRadius = 0.1 * (maxProjection - minProjection);
      gp_XYZ localCentroid(0, 0, 0);
      int count = 0;

      for (const auto &p : points) {
        if (point.Distance(p) < searchRadius) {
          localCentroid += p.XYZ();
          count++;
        }
      }

      // 11.4 向局部重心方向移动
      if (count > 0) {
        localCentroid /= count;
        gp_Pnt newPoint = point.XYZ() * (1.0 - smoothingFactor) +
                          localCentroid * smoothingFactor;
        centerlinePoints.SetValue(i, newPoint);
      } else {
        centerlinePoints.SetValue(i, point);
      }
    }

    // 11.5 重新拟合曲线
    fitter.Init(centerlinePoints, splineDegree, 8);
    if (fitter.IsDone()) {
      centerline = fitter.Curve();
    } else {
      break; // 保持上一次拟合结果
    }
  }

  return centerline;
}

// 优化中心线（确保平滑且位于形状中心）
Handle(Geom_Curve)
    optimize_centerline(const Handle(Geom_Curve) & centerline,
                        const std::vector<gp_Pnt> &points, int numIterations,
                        double smoothingFactor) {
  if (centerline.IsNull() || points.empty()) {
    return centerline;
  }

  Handle(Geom_Curve) optimizedCurve = centerline;

  for (int iter = 0; iter < numIterations; ++iter) {
    // 1. 沿曲线均匀采样
    GeomAdaptor_Curve adaptor(optimizedCurve);
    int numSamples = 50;
    GCPnts_UniformAbscissa abscissa(adaptor, numSamples);
    if (!abscissa.IsDone())
      break;

    // 2. 准备新控制点
    TColgp_Array1OfPnt newPoints(1, abscissa.NbPoints());
    TColStd_Array1OfReal params(1, abscissa.NbPoints());

    for (int i = 1; i <= abscissa.NbPoints(); i++) {
      double param = abscissa.Parameter(i);
      params.SetValue(i, param);
      newPoints.SetValue(i, optimizedCurve->Value(param));
    }

    // 3. 优化每个点
    for (int i = 1; i <= newPoints.Length(); ++i) {
      gp_Pnt point = newPoints.Value(i);
      double param = params.Value(i);

      // 3.1 计算当前点的法向平面
      gp_Vec tangent;
      optimizedCurve->D1(param, point, tangent);
      if (tangent.Magnitude() < Precision::Confusion())
        continue;

      gp_Dir normalDir(tangent);
      gp_Pln sectionPlane(point, normalDir);

      // 3.2 收集截面附近点
      std::vector<gp_Pnt> sectionPoints;
      for (const auto &p : points) {
        if (sectionPlane.Distance(p) < 0.1 * tangent.Magnitude()) {
          sectionPoints.push_back(p);
        }
      }

      // 3.3 计算截面重心
      if (!sectionPoints.empty()) {
        gp_XYZ centroid(0, 0, 0);
        for (const auto &p : sectionPoints) {
          centroid += p.XYZ();
        }
        centroid /= sectionPoints.size();

        // 3.4 向重心方向移动
        gp_Pnt newPoint =
            point.XYZ() * (1.0 - smoothingFactor) + centroid * smoothingFactor;
        newPoints.SetValue(i, newPoint);
      }
    }

    // 4. 重新拟合曲线
    GeomAPI_PointsToBSpline fitter;
    fitter.Init(newPoints, 3, 8); // 3阶B样条
    if (fitter.IsDone()) {
      optimizedCurve = fitter.Curve();
    } else {
      break; // 保持上一次拟合结果
    }
  }

  return optimizedCurve;
}

TopoDS_Shape create_bounding_pipe_shape(const bounding_pipe_section &section,
                                        const TopoDS_Wire &path) {
  if (path.IsNull()) {
    return TopoDS_Shape();
  }

  // 1. 创建截面轮廓
  TopoDS_Wire wire;
  BRepBuilderAPI_MakeWire wireMaker;

  gp_Ax2 axis(section.center, section.direction);
  Handle(Geom_Circle) circle = new Geom_Circle(axis, section.radius);
  TopoDS_Edge edge = BRepBuilderAPI_MakeEdge(circle);
  wireMaker.Add(edge);

  if (!wireMaker.IsDone()) {
    return TopoDS_Shape();
  }
  wire = wireMaker.Wire();

  // 2. 创建放样曲面
  BRepOffsetAPI_MakePipeShell pipeMaker(path);
  pipeMaker.Add(wire);
  if (!pipeMaker.IsDone()) {
    return TopoDS_Shape();
  }

  // 3. 创建端面
  TopoDS_Shape pipeShape = pipeMaker.Shape();

  // 4. 修复形状
  ShapeFix_Shape fixer(pipeShape);
  fixer.Perform();
  return fixer.Shape();
}

// 创建边界管道形状
TopoDS_Shape create_bounding_pipe_shape(const bounding_pipe &boundPipe) {
  if (boundPipe.centerline.IsNull()) {
    return TopoDS_Shape();
  }

  BRepBuilderAPI_MakeEdge edgeMaker1(boundPipe.centerline);
  auto path = BRepBuilderAPI_MakeWire(edgeMaker1.Edge()).Wire();

  return create_bounding_pipe_shape(boundPipe.sections, path);
}

// 辅助函数：提取管道的内外边界
void extract_pipe_boundaries(const TopoDS_Shape &pipeShape,
                             TopoDS_Shape &outerBoundary,
                             TopoDS_Shape &innerBoundary) {
  // 获取所有边
  TopTools_IndexedMapOfShape edges;
  TopExp::MapShapes(pipeShape, TopAbs_EDGE, edges);

  // 按长度排序边
  std::vector<std::pair<double, TopoDS_Edge>> sortedEdges;
  for (int i = 1; i <= edges.Extent(); i++) {
    TopoDS_Edge edge = TopoDS::Edge(edges(i));
    BRepAdaptor_Curve curve(edge);
    double length = GCPnts_AbscissaPoint::Length(curve);
    sortedEdges.push_back(std::make_pair(length, edge));
  }

  // 按长度降序排序
  std::sort(sortedEdges.begin(), sortedEdges.end(),
            [](const auto &a, const auto &b) { return a.first > b.first; });

  // 最长的两条边作为边界
  if (sortedEdges.size() >= 2) {
    outerBoundary = sortedEdges[0].second;
    innerBoundary = sortedEdges[1].second;
  } else if (sortedEdges.size() == 1) {
    outerBoundary = sortedEdges[0].second;
    innerBoundary = sortedEdges[0].second;
  }
}

// 辅助函数：计算边的长度
double calculate_edge_length(const TopoDS_Edge &edge) {
  BRepAdaptor_Curve curve(edge);
  GCPnts_UniformAbscissa abscissa(curve, 10);
  if (!abscissa.IsDone())
    return 0.0;
  return abscissa.Parameter(abscissa.NbPoints());
}

// 辅助函数：计算形状的长度
double calculate_shape_length(const TopoDS_Shape &shape) {
  double totalLength = 0.0;
  TopTools_IndexedMapOfShape edges;
  TopExp::MapShapes(shape, TopAbs_EDGE, edges);

  for (int i = 1; i <= edges.Extent(); i++) {
    totalLength += calculate_edge_length(TopoDS::Edge(edges(i)));
  }

  return totalLength;
}

// 辅助函数：沿管道长度获取点
gp_Pnt get_point_at_distance(const TopoDS_Shape &pipeShape, double distance) {
  // 使用管道形状的线性属性
  GProp_GProps gprops;
  BRepGProp::LinearProperties(pipeShape, gprops);
  gp_Pnt centroid = gprops.CentreOfMass();

  // 获取主要方向
  gp_Mat inertia = gprops.MatrixOfInertia();
  gp_Vec principalVec = inertia.Diagonal();

  // 归一化
  if (principalVec.Magnitude() > 1e-5) {
    principalVec.Normalize();
  } else {
    principalVec = gp_Vec(1, 0, 0); // 默认方向
  }

  // 沿主方向移动
  return centroid.Translated(principalVec * distance);
}

// 辅助函数：找到中轴点（到内外边界距离相等的点）
gp_Pnt find_medial_point(const gp_Pnt &samplePoint,
                         const TopoDS_Shape &outerBoundary,
                         const TopoDS_Shape &innerBoundary) {
  // 创建采样点顶点
  TopoDS_Vertex sampleVertex = BRepBuilderAPI_MakeVertex(samplePoint);

  // 计算到外边界的最小距离 - 使用正确的初始化
  BRepExtrema_DistShapeShape distToOuter(sampleVertex, outerBoundary,
                                         Extrema_ExtFlag_MINMAX,
                                         Extrema_ExtAlgo_Grad);
  distToOuter.Perform();
  double distOuter = distToOuter.Value();
  gp_Pnt outerPoint = distToOuter.PointOnShape2(1);

  // 计算到内边界的最小距离 - 使用正确的初始化
  BRepExtrema_DistShapeShape distToInner(sampleVertex, innerBoundary,
                                         Extrema_ExtFlag_MINMAX,
                                         Extrema_ExtAlgo_Grad);
  distToInner.Perform();
  double distInner = distToInner.Value();
  gp_Pnt innerPoint = distToInner.PointOnShape2(1);

  // 计算中点
  double totalDist = distOuter + distInner;
  if (totalDist < Precision::Confusion()) {
    return samplePoint; // 避免除零
  }

  double weightOuter = distInner / totalDist;
  double weightInner = distOuter / totalDist;

  double x = weightOuter * outerPoint.X() + weightInner * innerPoint.X();
  double y = weightOuter * outerPoint.Y() + weightInner * innerPoint.Y();
  double z = weightOuter * outerPoint.Z() + weightInner * innerPoint.Z();

  return gp_Pnt(x, y, z);
}

// 改进的路径线提取函数
TopoDS_Wire extract_path_wire_from_pipe_shape(const TopoDS_Shape &pipeShape) {
  // 1. 获取管道边界
  TopoDS_Shape outerBoundary;
  TopoDS_Shape innerBoundary;
  extract_pipe_boundaries(pipeShape, outerBoundary, innerBoundary);

  // 2. 沿管道长度采样点
  std::vector<gp_Pnt> centerPoints;
  const int numSamples = 100;

  // 计算管道总长度
  GProp_GProps gprops;
  BRepGProp::LinearProperties(pipeShape, gprops);
  double totalLength = gprops.Mass();

  // 3. 沿管道均匀采样
  for (int i = 0; i < numSamples; i++) {
    double param = (double)i / (numSamples - 1);
    double distance = param * totalLength;

    // 获取当前采样点的近似位置
    gp_Pnt samplePoint = get_point_at_distance(pipeShape, distance);

    // 找到到内外边界距离相等的点
    gp_Pnt centerPoint =
        find_medial_point(samplePoint, outerBoundary, innerBoundary);
    centerPoints.push_back(centerPoint);
  }

  // 4. 拟合中心线曲线
  TColgp_Array1OfPnt points(1, centerPoints.size());
  for (size_t i = 0; i < centerPoints.size(); i++) {
    points.SetValue(i + 1, centerPoints[i]);
  }

  GeomAPI_PointsToBSpline fitter;
  fitter.Init(points, 3, 8, GeomAbs_C2, 1e-5);
  Handle(Geom_BSplineCurve) centerCurve = fitter.Curve();

  // 5. 创建中心线
  TopoDS_Edge centerEdge = BRepBuilderAPI_MakeEdge(centerCurve).Edge();
  return BRepBuilderAPI_MakeWire(centerEdge).Wire();
}

bounding_pipe extract_bounding_pipe_from_shape(const TopoDS_Shape &shape,
                                               const gp_Dir *userDir,
                                               int numSamplePoints) {
  bounding_pipe result;

  // 1. 检查是否为管道形状
  if (shape.IsNull()) {
    return result;
  }

  // 2. 检查是否使用用户指定的方向
  bool useUserDirection =
      (userDir != nullptr &&
       !userDir->IsEqual(gp_Dir(0, 0, 0), Precision::Confusion()));

  // 3. 尝试提取路径线(Wire) - 仅在未指定方向时执行
  if (!useUserDirection) {
    // 尝试提取路径线
    TopoDS_Wire pathWire = extract_path_wire_from_pipe_shape(shape);

    if (!pathWire.IsNull()) {
      // 3.1 创建复合曲线适配器
      BRepAdaptor_CompCurve compCurve(pathWire);

      // 3.2 获取参数范围
      double first = compCurve.FirstParameter();
      double last = compCurve.LastParameter();

      // 3.3 采样点以创建B样条曲线
      const int numSamplePoints = 50; // 适当减少点数提高性能
      GCPnts_UniformAbscissa abscissa;
      abscissa.Initialize(compCurve, numSamplePoints, first, last);

      if (abscissa.IsDone()) {
        TColgp_Array1OfPnt points(1, abscissa.NbPoints());
        for (int i = 1; i <= abscissa.NbPoints(); i++) {
          double param = abscissa.Parameter(i);
          gp_Pnt p = compCurve.Value(param);
          points.SetValue(i, p);
        }

        // 3.4 拟合B样条曲线
        GeomAPI_PointsToBSpline fitter;
        fitter.Init(points); // 使用插值而非逼近

        if (fitter.IsDone()) {
          result.centerline = fitter.Curve();

          // 优化曲线参数化
          GeomAdaptor_Curve adaptor(result.centerline);
          GCPnts_UniformAbscissa reparam(adaptor, numSamplePoints);
          if (reparam.IsDone()) {
            TColgp_Array1OfPnt refinedPoints(1, reparam.NbPoints());
            for (int i = 1; i <= reparam.NbPoints(); i++) {
              refinedPoints.SetValue(
                  i, result.centerline->Value(reparam.Parameter(i)));
            }

            GeomAPI_PointsToBSpline refitter;
            refitter.Init(refinedPoints, 3, GeomAbs_C2, 1.0e-3);
            if (refitter.IsDone()) {
              result.centerline = refitter.Curve();
            }
          }
        }
      }
    }
  }

  // 4. 如果未提取到中心线，尝试使用PCA方法或用户指定方向
  if (result.centerline.IsNull()) {
    result.centerline =
        fit_centerline_from_shape(shape, numSamplePoints, 3, 0.2);
  }

  // 5. 提取截面信息
  if (!result.centerline.IsNull()) {
    double maxRadius = 0.0;
    gp_Pnt maxCenterPoint;
    gp_Dir maxSectionDir;

    // 5.1 沿中心线采样点
    GeomAdaptor_Curve curveAdaptor(result.centerline);
    int numSections = 20;
    GCPnts_UniformAbscissa abscissa(curveAdaptor, numSections);

    if (abscissa.IsDone()) {
      for (int i = 1; i <= abscissa.NbPoints(); i++) {
        double param = abscissa.Parameter(i);
        gp_Pnt centerPoint;
        gp_Vec tangent;
        result.centerline->D1(param, centerPoint, tangent);

        // 5.2 确定截面方向
        gp_Dir sectionDir;
        if (useUserDirection) {
          sectionDir = *userDir;
        } else {
          sectionDir = gp_Dir(tangent);
        }

        // 5.3 创建垂直于中心线的平面
        gp_Pln sectionPlane(centerPoint, sectionDir);

        // 5.4 计算该截面的半径
        double currentRadius = 0.0;
        TopExp_Explorer vertexExplorer(shape, TopAbs_VERTEX);
        while (vertexExplorer.More()) {
          TopoDS_Vertex vertex = TopoDS::Vertex(vertexExplorer.Current());
          gp_Pnt point = BRep_Tool::Pnt(vertex);

          double distToPlane = sectionPlane.Distance(point);
          ShapeAnalysis_Curve sac;
          gp_Pnt nearestPoint;
          double paramOnCurve;
          double distToCenter =
              sac.Project(result.centerline, point, Precision::Confusion(),
                          nearestPoint, paramOnCurve);

          if (distToPlane < currentRadius * 0.5 || currentRadius == 0.0) {
            double radius = centerPoint.Distance(point);
            if (radius > currentRadius)
              currentRadius = radius;
          }

          vertexExplorer.Next();
        }

        // 5.5 更新最大截面信息
        if (currentRadius > maxRadius) {
          maxRadius = currentRadius;
          maxCenterPoint = centerPoint;
          maxSectionDir = sectionDir;
        }
      }
    }

    // 5.6 保存最大截面信息
    if (maxRadius > Precision::Confusion()) {
      bounding_pipe_section section;
      section.center = maxCenterPoint;
      section.radius = maxRadius * 1.1; // 添加10%安全余量
      section.direction = maxSectionDir;
      result.sections = section;
    }
  }
  return result;
}

TopoDS_Shape clip_with_bounding_pipe_and_split_distances(
    const TopoDS_Shape &shape, const bounding_pipe &boundPipe,
    std::array<double, 2> splitDistances, TopoDS_Wire originalPathWire) {
  // 参数验证
  if (splitDistances[0] < 0) {
    throw Standard_ConstructionError("First split distance must be >= 0");
  }

  TopoDS_Shape fullPipe = shape;
  TopoDS_Wire pathWire =
      originalPathWire.IsNull()
          ? boundPipe.centerline.IsNull()
                ? extract_path_wire_from_pipe_shape(shape)
                : BRepLib_MakeWire(
                      BRepLib_MakeEdge(boundPipe.centerline).Edge())
                      .Wire()
          : originalPathWire;

  if (pathWire.IsNull()) {
    throw Standard_ConstructionError("Failed to extract path wire");
  }

  // 计算路径总长度
  GProp_GProps lengthProps;
  BRepGProp::LinearProperties(pathWire, lengthProps);
  double totalLength = lengthProps.Mass();

  // 处理第二个分割距离
  if (splitDistances[1] == -1) {
    splitDistances[1] = totalLength;
  } else if (splitDistances[1] <= splitDistances[0] ||
             splitDistances[1] > totalLength) {
    throw Standard_ConstructionError("Invalid second split distance");
  }

  // 如果不需要分割，直接返回完整管道
  if (splitDistances[0] == 0 && splitDistances[1] >= totalLength) {
    return fullPipe;
  }

  // 创建前段裁切体
  TopoDS_Shape frontCut;
  if (splitDistances[0] > 0) {
    TopoDS_Wire frontWire =
        clip_wire_between_distances_helper(pathWire, 0, splitDistances[0]);

    if (!frontWire.IsNull()) {
      // 使用最大圆形截面创建裁切体
      frontCut = create_bounding_pipe_shape(boundPipe.sections, frontWire);
    }
  }

  // 创建后段裁切体
  TopoDS_Shape backCut;
  if (splitDistances[1] < totalLength) {
    TopoDS_Wire backWire = clip_wire_between_distances_helper(
        pathWire, splitDistances[1], totalLength);

    if (!backWire.IsNull()) {
      // 使用最大圆形截面创建裁切体
      backCut = create_bounding_pipe_shape(boundPipe.sections, backWire);
    }
  }

  // 执行裁切操作
  TopoDS_Shape result = fullPipe;
  if (!frontCut.IsNull()) {
    result = BRepAlgoAPI_Cut(result, frontCut).Shape();
  }
  if (!backCut.IsNull()) {
    result = BRepAlgoAPI_Cut(result, backCut).Shape();
  }

  return result;
}

TopoDS_Shape clip_with_bounding_pipe_by_ratios(
    const TopoDS_Shape &shape, const bounding_pipe &boundPipe,
    std::array<double, 2> splitRatios, TopoDS_Wire originalPathWire) {
  // 参数验证
  if (splitRatios[0] < 0 || splitRatios[0] > 1.0) {
    throw Standard_ConstructionError(
        "First split ratio must be between 0 and 1");
  }
  if (splitRatios[1] != -1 &&
      (splitRatios[1] <= splitRatios[0] || splitRatios[1] > 1.0)) {
    throw Standard_ConstructionError("Invalid second split ratio");
  }

  // 计算路径总长度
  TopoDS_Wire pathWire =
      originalPathWire.IsNull()
          ? boundPipe.centerline.IsNull()
                ? extract_path_wire_from_pipe_shape(shape)
                : BRepLib_MakeWire(
                      BRepLib_MakeEdge(boundPipe.centerline).Edge())
                      .Wire()
          : originalPathWire;

  if (pathWire.IsNull()) {
    throw Standard_ConstructionError("Failed to extract path wire");
  }

  GProp_GProps lengthProps;
  BRepGProp::LinearProperties(pathWire, lengthProps);
  double totalLength = lengthProps.Mass();

  // 转换为实际距离
  std::array<double, 2> splitDistances = {
      splitRatios[0] * totalLength,
      splitRatios[1] == -1 ? -1 : splitRatios[1] * totalLength};

  // 调用基于距离的版本
  return clip_with_bounding_pipe_and_split_distances(shape, boundPipe,
                                                     splitDistances, pathWire);
}

} // namespace topo
} // namespace flywave
