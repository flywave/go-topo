#include "bounding_pipe.hh"

#include <BRepAdaptor_CompCurve.hxx>
#include <BRepAdaptor_Curve.hxx>
#include <BRepAdaptor_Surface.hxx>
#include <BRepAlgoAPI_Cut.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
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
#include <GeomAPI_Interpolate.hxx>
#include <GeomAPI_PointsToBSpline.hxx>
#include <GeomAPI_ProjectPointOnCurve.hxx>
#include <GeomAPI_ProjectPointOnSurf.hxx>
#include <GeomAdaptor_Curve.hxx>
#include <GeomConvert_ApproxCurve.hxx>
#include <GeomLProp_CLProps.hxx>
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
#include <map>
#include <math_Jacobi.hxx>
#include <math_Matrix.hxx>

namespace flywave {
namespace topo {

extern TopoDS_Wire
clip_wire_between_distances_helper(const TopoDS_Wire &wire_path,
                                   double start_distance, double end_distance);

// 从形状中提取三角网格顶点
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

Handle(Geom_Curve)
    fit_centerline_from_shape(const TopoDS_Shape &shape, int numSamples,
                              int splineDegree, double smoothingFactor) {
  // 1. 提取形状点
  std::vector<gp_Pnt> points = extract_shape_points(shape);
  if (points.empty())
    return nullptr;

  // 2. 计算包围盒和特征长度
  Bnd_Box bbox;
  for (const auto &p : points)
    bbox.Add(p);

  double xMin, yMin, zMin, xMax, yMax, zMax;
  bbox.Get(xMin, yMin, zMin, xMax, yMax, zMax);
  const double bboxDiag =
      sqrt(pow(xMax - xMin, 2) + pow(yMax - yMin, 2) + pow(zMax - zMin, 2));
  const double avgSpacing = bboxDiag / sqrt(points.size());

  // 3. 改进PCA - 修正投影范围计算
  gp_XYZ centroid(0, 0, 0);
  for (const auto &p : points)
    centroid += p.XYZ();
  centroid /= points.size();

  math_Matrix cov(1, 3, 1, 3, 0.0);
  for (const auto &p : points) {
    gp_XYZ diff = p.XYZ() - centroid;
    for (int i = 1; i <= 3; ++i)
      for (int j = 1; j <= 3; ++j)
        cov(i, j) += diff.Coord(i) * diff.Coord(j);
  }

  math_Jacobi jacobi(cov);
  math_Vector eigenValues = jacobi.Values();
  math_Matrix eigenVectors = jacobi.Vectors();

  // 修正1：独立计算每个轴的投影范围
  double bestMinProj = DBL_MAX, bestMaxProj = -DBL_MAX;
  int bestAxis = 1;
  double maxSpan = -DBL_MAX;

  for (int axisIdx = 1; axisIdx <= 3; ++axisIdx) {
    // 为每个轴重置min/max
    double axisMin = DBL_MAX, axisMax = -DBL_MAX;
    gp_Dir axis(eigenVectors(1, axisIdx), eigenVectors(2, axisIdx),
                eigenVectors(3, axisIdx));

    for (const auto &p : points) {
      double proj = (p.XYZ() - centroid).Dot(axis.XYZ());
      axisMin = std::min(axisMin, proj);
      axisMax = std::max(axisMax, proj);
    }

    const double span = axisMax - axisMin;
    if (span > maxSpan) {
      maxSpan = span;
      bestAxis = axisIdx;
      bestMinProj = axisMin;
      bestMaxProj = axisMax;
    }
  }

  gp_Dir mainAxis(eigenVectors(1, bestAxis), eigenVectors(2, bestAxis),
                  eigenVectors(3, bestAxis));

  // 4. 分段投影拟合
  const int numSegments =
      std::max(3, static_cast<int>(maxSpan / (2 * avgSpacing)));
  std::vector<gp_Pnt> validCenterPoints; // 改用vector存储有效点

  for (int seg = 0; seg <= numSegments; ++seg) {
    double proj = bestMinProj + seg * (bestMaxProj - bestMinProj) / numSegments;
    gp_Pnt basePoint = gp_Pnt(centroid).Translated(mainAxis.XYZ() * proj);

    gp_Pln sectionPlane(basePoint, mainAxis);
    gp_XYZ localCentroid(0, 0, 0);
    int count = 0;

    for (const auto &p : points) {
      double distToPlane = fabs(sectionPlane.Distance(p));
      if (distToPlane < 2.0 * avgSpacing) {
        localCentroid += p.XYZ();
        count++;
      }
    }

    if (count > 3) {
      localCentroid /= count;
      validCenterPoints.push_back(gp_Pnt(localCentroid));
    }
  }

  // 定义距离阈值，用于判断两点是否重复
  const double distanceThreshold = Precision::Confusion();
  // 对 validCenterPoints 进行排序
  std::sort(validCenterPoints.begin(), validCenterPoints.end(),
            [](const gp_Pnt &a, const gp_Pnt &b) {
              if (a.X() != b.X())
                return a.X() < b.X();
              if (a.Y() != b.Y())
                return a.Y() < b.Y();
              return a.Z() < b.Z();
            });

  // 移除重复点
  auto last =
      std::unique(validCenterPoints.begin(), validCenterPoints.end(),
                  [distanceThreshold](const gp_Pnt &a, const gp_Pnt &b) {
                    return a.Distance(b) < distanceThreshold;
                  });
  validCenterPoints.erase(last, validCenterPoints.end());

  // 5. 分段拟合B样条
  if (validCenterPoints.size() < 2) {
    gp_Lin line(centroid, mainAxis);
    return new Geom_Line(line);
  }

  auto compute_section_center = [&](const gp_Pnt &curve_point,
                                    const gp_Vec &tangent) -> gp_Pnt {
    if (tangent.Magnitude() < Precision::Confusion())
      return curve_point;

    // 从 validCenterPoints 中找到最接近 curve_point 的点及其前后点
    size_t closestIndex = 0;
    double minDistance = DBL_MAX;
    for (size_t i = 0; i < validCenterPoints.size(); ++i) {
      double dist = curve_point.Distance(validCenterPoints[i]);
      if (dist < minDistance) {
        minDistance = dist;
        closestIndex = i;
      }
    }

    // 确保有足够的点来计算曲率
    double curvature = 0.0;
    if (closestIndex > 0 && closestIndex < validCenterPoints.size() - 1) {
      gp_Pnt p0 = validCenterPoints[closestIndex - 1];
      gp_Pnt p1 = validCenterPoints[closestIndex];
      gp_Pnt p2 = validCenterPoints[closestIndex + 1];

      gp_Vec v1 = gp_Vec(p0, p1);
      gp_Vec v2 = gp_Vec(p1, p2);

      // 计算曲率的近似值
      gp_Vec crossProduct = v1.Crossed(v2);
      double crossMag = crossProduct.Magnitude();
      double v1Mag = v1.Magnitude();
      double v2Mag = v2.Magnitude();
      if (v1Mag > Precision::Confusion() && v2Mag > Precision::Confusion()) {
        curvature = crossMag / (v1Mag * v2Mag * (v1Mag + v2Mag));
      }
    }

    // 动态调整搜索半径
    double radius = (curvature > 1e-3) ? 1.5 * avgSpacing : 4.0 * avgSpacing;
    gp_Pln section_plane(curve_point, gp_Dir(tangent));

    gp_XYZ weightedCentroid(0, 0, 0);
    double totalWeight = 0.0;

    for (const auto &p : points) {
      double distToPlane = section_plane.Distance(p);
      double distToPoint = curve_point.Distance(p);
      if (distToPlane < radius && distToPoint < 2.0 * radius) {
        // 计算权重，距离越近权重越高
        double weight = 1.0 / (1.0 + distToPoint);
        weightedCentroid += p.XYZ() * weight;
        totalWeight += weight;
      }
    }

    return (totalWeight > 0.0) ? gp_Pnt(weightedCentroid / totalWeight)
                               : curve_point;
  };
  // 获取初始曲线端点
  gp_Pnt startPoint = validCenterPoints.front();
  gp_Pnt endPoint = validCenterPoints.back();

  // 改进切线计算，使用更多点
  gp_Vec startTangent = gp_Vec(validCenterPoints[1], startPoint).Normalized();
  gp_Vec endTangent =
      gp_Vec(endPoint, validCenterPoints[validCenterPoints.size() - 2])
          .Normalized();

  // 计算精确端面中心
  gp_Pnt startCenter = compute_section_center(startPoint, startTangent);
  gp_Pnt endCenter = compute_section_center(endPoint, endTangent);

  // 替换首尾点为端面中心
  validCenterPoints.front() = startCenter;
  validCenterPoints.back() = endCenter;

  // 创建插值点集
  Handle(TColgp_HArray1OfPnt) centerlinePoints =
      new TColgp_HArray1OfPnt(1, validCenterPoints.size());
  for (int i = 0; i < validCenterPoints.size(); ++i) {
    centerlinePoints->SetValue(i + 1, validCenterPoints[i]);
  }

  Handle(Geom_BSplineCurve) centerline;

  // 修正3：使用插值而非逼近
  GeomAPI_Interpolate interpolator(centerlinePoints, Standard_False,
                                   Precision::Confusion());
  interpolator.Perform();

  if (interpolator.IsDone()) {
    centerline = interpolator.Curve();
  } else {
    // 回退：直线拟合
    gp_Lin line(centroid, mainAxis);
    return new Geom_Line(line);
  }

  // 6. 曲率自适应迭代优化 - 修正后的曲率计算
  const int maxIterations = 20;

  for (int iter = 0; iter < maxIterations; ++iter) {
    bool significantChange = false;
    GeomAdaptor_Curve adaptor(centerline);

    // 动态采样数
    int adaptiveSamples = std::min(100, std::max(20, numSamples));
    GCPnts_UniformAbscissa abscissa(adaptor, adaptiveSamples);
    if (!abscissa.IsDone())
      break;

    Handle(TColgp_HArray1OfPnt) newPoints =
        new TColgp_HArray1OfPnt(1, abscissa.NbPoints());

    for (int i = 1; i <= abscissa.NbPoints(); ++i) {
      bool isStart = (i == 1);
      bool isEnd = (i == abscissa.NbPoints());
      if (isStart) {
        newPoints->SetValue(i, startCenter);
        continue;
      }
      if (isEnd) {
        newPoints->SetValue(i, endCenter);
        continue;
      }
      double param = abscissa.Parameter(i);
      gp_Pnt point;
      gp_Vec tangent, normal;

      // 直接计算导矢（避免使用GeomLProp_CLProps）
      centerline->D1(param, point, tangent);
      centerline->D2(param, point, tangent, normal);

      // 计算曲率
      double curvature = 0.0;
      const double tangentMag = tangent.Magnitude();
      if (tangentMag > Precision::Confusion()) {
        const double normalMag = normal.Magnitude();
        curvature = normalMag / (tangentMag * tangentMag);
      }

      // 动态搜索半径
      double searchRadius =
          (curvature > 1e-3) ? 0.5 * avgSpacing : 2.0 * avgSpacing;

      gp_XYZ localCentroid(0, 0, 0);
      int count = 0;
      gp_Pln plane(point, gp_Dir(tangent));
      for (const auto &p : points) {
        if (point.Distance(p) < searchRadius &&
            fabs(plane.Distance(p)) < 0.5 * searchRadius) {
          localCentroid += p.XYZ();
          count++;
        }
      }
      gp_Pnt newPoint = point;
      if (count > 0) {
        localCentroid /= count;
        double blendFactor =
            smoothingFactor * exp(-iter / static_cast<double>(maxIterations));
        newPoint = gp_Pnt(point.XYZ() * (1.0 - blendFactor) +
                          localCentroid * blendFactor);
        if (newPoint.Distance(point) > 0.01 * avgSpacing) {
          significantChange = true;
        }
      }
      newPoints->SetValue(i, newPoint);
    }

    if (!significantChange)
      break;

    // 重新拟合
    GeomAPI_Interpolate refitter(newPoints, Standard_False, 0.001 * bboxDiag);
    refitter.Perform();
    if (refitter.IsDone()) {
      centerline = refitter.Curve();
    } else {
      break;
    }
  }

  // 7. 第二阶段延伸：从端面中心点精确延伸（关键改进）
  const auto extend_centerline = [&](Handle(Geom_BSplineCurve) & curve) {
    if (curve.IsNull() || curve->NbPoles() < 2)
      return;

    // 获取端面中心点处的切线方向
    gp_Vec startTangent, endTangent;
    gp_Pnt p1, p2;
    curve->D1(curve->FirstParameter(), p1, startTangent);
    curve->D1(curve->LastParameter(), p2, endTangent);

    // 单位化切向量
    if (startTangent.Magnitude() > Precision::Confusion())
      startTangent.Normalize();
    if (endTangent.Magnitude() > Precision::Confusion())
      endTangent.Normalize();

    // 动态延伸长度（包围盒对角线的10-15%）
    const double extendLen = 0.15 * bboxDiag;

    // 从端面中心点开始延伸
    const gp_Pnt newStart = startCenter.Translated(-extendLen * startTangent);
    const gp_Pnt newEnd = endCenter.Translated(extendLen * endTangent);

    // 创建延伸后的点集（保持内部点不变）
    Handle(TColgp_HArray1OfPnt) newPoles =
        new TColgp_HArray1OfPnt(1, curve->NbPoles());

    for (int i = 1; i <= curve->NbPoles(); ++i) {
      gp_Pnt p = curve->Pole(i);
      if (i == 1)
        p = newStart;
      else if (i == curve->NbPoles())
        p = newEnd;
      newPoles->SetValue(i, p);
    }

    // 重建曲线并保持参数化
    curve = new Geom_BSplineCurve(newPoles->Array1(), curve->Knots(),
                                  curve->Multiplicities(), curve->Degree(),
                                  curve->IsPeriodic());
  };

  // 应用智能延伸
  extend_centerline(centerline);

  // 8. 动态调整起点和终点：确保中心线略微超出原始形状
  // 计算中心线长度
  GCPnts_AbscissaPoint abscissa;
  const double totalLength = abscissa.Length(GeomAdaptor_Curve(centerline));
  const double extensionLength = 0.00001 * totalLength; 

  // 投影所有点到中心线以找到最小和最大参数
  double t_min = DBL_MAX, t_max = -DBL_MAX;
  for (const auto &p : points) {
    GeomAPI_ProjectPointOnCurve projector(p, centerline);
    if (projector.NbPoints() > 0) {
      double param = projector.LowerDistanceParameter();
      t_min = std::min(t_min, param);
      t_max = std::max(t_max, param);
    }
  }

  // 计算新的起点和终点参数（略微超出形状）
  double t_start =
      std::max(centerline->FirstParameter(), t_min - extensionLength);
  double t_end = std::min(centerline->LastParameter(), t_max + extensionLength);

  // 使用Geom_TrimmedCurve创建修剪后的曲线
  Handle(Geom_TrimmedCurve) trimmedCurve =
      new Geom_TrimmedCurve(centerline, t_start, t_end);

  return trimmedCurve;
}

TopoDS_Shape create_bounding_pipe_shape(double radius,
                                        const TopoDS_Wire &path) {
  if (path.IsNull()) {
    return TopoDS_Shape();
  }

  // 1. 创建截面轮廓
  TopoDS_Wire wire;
  BRepBuilderAPI_MakeWire wireMaker;

  BRepAdaptor_CompCurve curveAdaptor(path);

  {

    gp_Pnt startPoint;
    gp_Vec startTangent;
    curveAdaptor.D1(curveAdaptor.FirstParameter(), startPoint, startTangent);

    gp_Ax2 axis(startPoint, startTangent);
    Handle(Geom_Circle) circle = new Geom_Circle(axis, radius);
    TopoDS_Edge edge = BRepBuilderAPI_MakeEdge(circle);
    wireMaker.Add(edge);
  }

  if (!wireMaker.IsDone()) {
    return TopoDS_Shape();
  }
  wire = wireMaker.Wire();

  // 2. 创建放样曲面
  BRepOffsetAPI_MakePipeShell pipeMaker(path);
  pipeMaker.Add(wire);
  pipeMaker.Build();

  if (!pipeMaker.IsDone()) {
    return TopoDS_Shape();
  }

  if (!pipeMaker.MakeSolid()) {
    return TopoDS_Shape();
  }

  // 3. 创建端面
  TopoDS_Shape pipeShape = pipeMaker.Shape();

  // 4. 修复形状
  ShapeFix_Shape fixer(pipeShape);
  fixer.Perform();
  return fixer.Shape();
}

bounding_pipe extract_bounding_pipe_from_shape(const TopoDS_Shape &shape,
                                               const gp_Dir *userDir,
                                               int numSamplePoints) {
  bounding_pipe result;

  // 1. 检查是否为管道形状
  if (shape.IsNull()) {
    return result;
  }

  // 2. 计算包围盒用于后续参考
  Bnd_Box bbox;
  BRepBndLib::Add(shape, bbox);
  double xmin, ymin, zmin, xmax, ymax, zmax;
  bbox.Get(xmin, ymin, zmin, xmax, ymax, zmax);
  double bboxDiag =
      sqrt(pow(xmax - xmin, 2) + pow(ymax - ymin, 2) + pow(zmax - zmin, 2));
  const double avgSpacing = bboxDiag / 100.0; // 估算平均点间距

  // 3. 检查是否使用用户指定的方向
  bool useUserDirection = (userDir != nullptr && gp_Vec(*userDir).Magnitude() >
                                                     Precision::Confusion());

  // 4. 提取中心线
  result.centerline = fit_centerline_from_shape(shape, numSamplePoints, 3, 0.2);

  // 5. 提取截面信息
  if (!result.centerline.IsNull()) {
    // 5.1 收集所有顶点
    std::vector<gp_Pnt> allPoints;
    TopExp_Explorer vertexExplorer(shape, TopAbs_VERTEX);
    for (; vertexExplorer.More(); vertexExplorer.Next()) {
      TopoDS_Vertex vertex = TopoDS::Vertex(vertexExplorer.Current());
      allPoints.push_back(BRep_Tool::Pnt(vertex));
    }

    // 5.2 从边采样点（如果顶点不足）
    if (allPoints.size() < 50) {
      TopExp_Explorer edgeExplorer(shape, TopAbs_EDGE);
      for (; edgeExplorer.More(); edgeExplorer.Next()) {
        TopoDS_Edge edge = TopoDS::Edge(edgeExplorer.Current());
        BRepAdaptor_Curve curve(edge);
        double first = curve.FirstParameter();
        double last = curve.LastParameter();
        int numSamplesPerEdge = 10;
        for (int i = 0; i < numSamplesPerEdge; i++) {
          double param = first + i * (last - first) / (numSamplesPerEdge - 1);
          gp_Pnt point = curve.Value(param);
          allPoints.push_back(point);
        }
      }
    }

    // 5.3 计算所有点到中心线的最大距离
    double maxRadius = 0.0;
    gp_Pnt maxCenterPoint;
    gp_Dir maxSectionDir;

    ShapeAnalysis_Curve sac;
    for (const auto &point : allPoints) {
      gp_Pnt nearestPoint;
      double paramOnCurve;
      double distance =
          sac.Project(result.centerline, point, Precision::Confusion(),
                      nearestPoint, paramOnCurve);

      if (distance > maxRadius) {
        maxRadius = distance;
        maxCenterPoint = nearestPoint;

        // 获取该点的切线方向
        gp_Vec tangent;
        result.centerline->D1(paramOnCurve, nearestPoint, tangent);
        if (tangent.Magnitude() > Precision::Confusion()) {
          maxSectionDir = gp_Dir(tangent);
        }
      }
    }

    // 5.4 添加安全余量并保存结果
    if (maxRadius > Precision::Confusion()) {
      maxRadius *= 1.2; // 20% 安全余量
      result.radius = maxRadius;
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
          ? BRepLib_MakeWire(BRepLib_MakeEdge(boundPipe.centerline).Edge())
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
      frontCut = create_bounding_pipe_shape(boundPipe.radius, frontWire);
    }
  }

  // 创建后段裁切体
  TopoDS_Shape backCut;
  if (splitDistances[1] < totalLength) {
    TopoDS_Wire backWire = clip_wire_between_distances_helper(
        pathWire, splitDistances[1], totalLength);

    if (!backWire.IsNull()) {
      // 使用最大圆形截面创建裁切体
      backCut = create_bounding_pipe_shape(boundPipe.radius, backWire);
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
          ? BRepLib_MakeWire(BRepLib_MakeEdge(boundPipe.centerline).Edge())
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
