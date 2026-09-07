#include <cmath>
#include "primitives.hh"
#include "bounding_pipe.hh"
#include "catenary.hh"

#include <BRepAdaptor_CompCurve.hxx>
#include <BRepAlgoAPI_Common.hxx>
#include <BRepAlgoAPI_Cut.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepBndLib.hxx>
#include <BRepBuilderAPI_Copy.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_MakePolygon.hxx>
#include <BRepBuilderAPI_MakeShell.hxx>
#include <BRepBuilderAPI_MakeSolid.hxx>
#include <BRepBuilderAPI_MakeVertex.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_Sewing.hxx>
#include <BRepBuilderAPI_Transform.hxx>
#include <BRepBuilderAPI_TransitionMode.hxx>
#include <BRepCheck_Analyzer.hxx>
#include <BRepCheck_Wire.hxx>
#include <BRepFilletAPI_MakeChamfer.hxx>
#include <BRepFilletAPI_MakeFillet.hxx>
#include <BRepGProp.hxx>
#include <BRepOffsetAPI_MakeOffset.hxx>
#include <BRepOffsetAPI_MakePipe.hxx>
#include <BRepOffsetAPI_MakePipeShell.hxx>
#include <BRepOffsetAPI_ThruSections.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeCone.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepPrimAPI_MakePrism.hxx>
#include <BRepPrimAPI_MakeRevol.hxx>
#include <BRepPrimAPI_MakeRevolution.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>
#include <BRepPrimAPI_MakeTorus.hxx>
#include <BRepPrimAPI_MakeWedge.hxx>
#include <BRepTools.hxx>
#include <BRepTools_WireExplorer.hxx>
#include <BRep_Tool.hxx>
#include <ChFi2d_AnaFilletAlgo.hxx>
#include <ElCLib.hxx>
#include <GCPnts_AbscissaPoint.hxx>
#include <GCPnts_UniformAbscissa.hxx>
#include <GC_MakeArcOfCircle.hxx>
#include <GC_MakeCircle.hxx>
#include <GC_MakeSegment.hxx>
#include <GProp_GProps.hxx>
#include <GeomAPI_IntCS.hxx>
#include <GeomAPI_Interpolate.hxx>
#include <GeomAPI_PointsToBSpline.hxx>
#include <GeomFill_Pipe.hxx>
#include <Geom_BezierCurve.hxx>
#include <Geom_Circle.hxx>
#include <Geom_Line.hxx>
#include <Geom_Plane.hxx>
#include <Geom_SurfaceOfRevolution.hxx>
#include <Law_Linear.hxx>
#include <Precision.hxx>
#include <STEPControl_Reader.hxx>
#include <ShapeFix_Shape.hxx>
#include <Standard_ConstructionError.hxx>
#include <TColgp_Array1OfPnt.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Wire.hxx>
#include <gp_Ax2.hxx>
#include <gp_Ax3.hxx>
#include <gp_Circ.hxx>
#include <gp_Dir.hxx>
#include <gp_Elips.hxx>
#include <gp_Pln.hxx>
#include <gp_Pnt.hxx>
#include <gp_Vec.hxx>
#include <StlAPI_Writer.hxx>
#include <BRepMesh_IncrementalMesh.hxx>

// ==================================================================
// 由 primitives.cc 按专业拆分而来; 声明统一见 primitives.hh
// GIM 电缆工程 (cable) — 电缆本体与附件 / 桥架 / 电缆沟 / 隧道 / 工井 / 排管 / 通风

namespace flywave {
namespace topo {


TopoDS_Wire create_oriented_wire(const gp_Ax2 &system, double radius,
                                 double angle, bool isHole) {
  // float32 传入的 2π 比 double 2π 大 ~1.7e-7, 先钳制到精确 2π,
  // 否则 GC_MakeArcOfCircle 对超 2π 的角度构造异常
  if (std::fabs(angle - 2 * M_PI) < 1e-6) {
    angle = 2 * M_PI;
  }
  // 创建主圆弧（带容差计算）
  const double adjusted_angle =
      angle < 2 * M_PI ? angle - Precision::Angular() / 100 : angle;
  Handle(Geom_TrimmedCurve) arc =
      GC_MakeArcOfCircle(gp_Circ(system, radius), 0, adjusted_angle, false)
          .Value();

  BRepBuilderAPI_MakeWire wireMaker;

  // 添加圆弧边（精确端点捕捉）
  wireMaker.Add(BRepBuilderAPI_MakeEdge(arc));

  // 非完整圆处理
  if (adjusted_angle < 2 * M_PI - Precision::Angular()) {
    gp_Pnt start = arc->Value(arc->FirstParameter());
    gp_Pnt end = arc->Value(arc->LastParameter());

    // 精确连接线段（使用几何API）
    Handle(Geom_TrimmedCurve) line1 =
        GC_MakeSegment(start, gp::Origin()).Value();
    Handle(Geom_TrimmedCurve) line2 = GC_MakeSegment(gp::Origin(), end).Value();

    if (isHole) {
      wireMaker.Add(BRepBuilderAPI_MakeEdge(line2)); // 终点到圆心
      wireMaker.Add(BRepBuilderAPI_MakeEdge(line1)); // 圆心到起点
    } else {
      wireMaker.Add(BRepBuilderAPI_MakeEdge(line1)); // 起点到圆心
      wireMaker.Add(BRepBuilderAPI_MakeEdge(line2)); // 圆心到终点
    }
  }

  // 强制线框方向
  TopoDS_Wire result = wireMaker.Wire();
  result.Closed(true); // 显式设置闭合标志
  if (isHole) {
    result.Reverse();
  }

  // 增强闭合性检查
  BRepCheck_Wire checker(result);
  if (checker.Closed() != BRepCheck_NoError) {
    throw Standard_ConstructionError("Wire closure verification failed");
  }

  return result;
}


TopoDS_Shape create_wire(const wire_params &params) {
  // 参数验证
  if (params.sag <= 0.0) {
    throw Standard_ConstructionError("Sag must be positive");
  }
  if (params.diameter <= 0.0) {
    throw Standard_ConstructionError("Diameter must be positive");
  }
  if (!params.fitPoints.empty() && params.fitPoints.size() < 2) {
    throw Standard_ConstructionError("At least 2 fit points are required");
  }

  // 创建导线路径
  BRepBuilderAPI_MakeWire wireMaker;

  Handle(Geom_BSplineCurve) curve;
  if (!params.fitPoints.empty()) {
    // 使用拟合点集创建样条曲线
    Handle(TColgp_HArray1OfPnt) points =
        new TColgp_HArray1OfPnt(1, params.fitPoints.size());
    for (int i = 0; i < params.fitPoints.size(); ++i) {
      points->SetValue(i + 1, params.fitPoints[i]);
    }

    GeomAPI_Interpolate interpolate(points, false, Precision::Confusion());
    interpolate.Load(gp_Vec(0, 0, 1), gp_Vec(0, 0, 1),
                     true); // 添加首末端导数约束
    interpolate.Perform();
    if (!interpolate.IsDone()) {
      fprintf(stderr, "DBG cable: interpolate failed\n");
      throw Standard_ConstructionError("Failed to create interpolated curve");      throw Standard_ConstructionError("Failed to create interpolated curve");
    }

    curve = interpolate.Curve();
    if (curve.IsNull()) {
      throw Standard_ConstructionError("Failed to create curve");
    }
    BRepBuilderAPI_MakeEdge edgeMaker(curve);
    if (!edgeMaker.IsDone()) {
      throw Standard_ConstructionError("Failed to create edge from curve");
    }
    wireMaker.Add(edgeMaker.Edge());
  } else {
    // 创建直线段
    wireMaker.Add(
        BRepBuilderAPI_MakeEdge(params.startPoint, params.endPoint).Edge());
  }

  if (!wireMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create wire path");
  }
  TopoDS_Wire pathWire = wireMaker.Wire();

  // 创建圆形截面（直径方向始终垂直于路径）
  gp_Ax2 sectionAxis;
  if (!params.fitPoints.empty() && curve) {
    // 使用曲线起点处的Frenet标架
    gp_Pnt startPnt;
    gp_Vec tangent, normal, binormal;
    curve->D1(0, startPnt, tangent);

    // 自动生成法向量（确保不平行于切线）
    if (tangent.IsParallel(gp_Vec(0, 0, 1), Precision::Angular())) {
      normal = gp_Vec(1, 0, 0);
    } else {
      normal = gp_Vec(0, 0, 1);
    }
    binormal = tangent.Crossed(normal);

    sectionAxis = gp_Ax2(startPnt,
                         gp_Dir(tangent), // X轴沿切线方向
                         gp_Dir(normal)); // Z轴沿法线方向
  } else {
    sectionAxis = gp_Ax2(params.startPoint, gp_Dir(params.endPoint.XYZ() -
                                                   params.startPoint.XYZ()));
  }

  // 创建截面圆
  gp_Circ sectionCircle(sectionAxis, params.diameter / 2);
  TopoDS_Wire sectionWire =
      BRepBuilderAPI_MakeWire(BRepBuilderAPI_MakeEdge(sectionCircle).Edge())
          .Wire();

  // 配置扫掠生成器（关键修正部分）
  BRepOffsetAPI_MakePipeShell pipeMaker(pathWire);
  pipeMaker.Add(sectionWire);
  pipeMaker.SetTolerance(1e-6);     // 添加容差设置
  pipeMaker.SetMode(Standard_True); // 启用Frenet坐标系
  pipeMaker.Build();

  if (!pipeMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to generate wire pipe");
  }
  if (!pipeMaker.MakeSolid()) {
    throw std::runtime_error("Failed to create a solid object from sweep");
  }

  // 闭合开口端
  if (pipeMaker.Shape().IsNull()) {
    throw Standard_ConstructionError("Generated shape is invalid");
  }

  return pipeMaker.Shape();
}


TopoDS_Shape create_wire(const wire_params &params, const gp_Pnt &position,
                         const gp_Dir &direction, const gp_Dir &upDirection) {
  // 首先创建标准方向的电线
  TopoDS_Shape cable = create_wire(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 1, 0), gp_Dir(1, 0, 0));
  gp_Ax3 targetAx3(position, direction, upDirection);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(cable, transformation);
  return transform.Shape();
}


TopoDS_Wire create_wire_centerline(const wire_params &params) {
  // 参数验证
  if (params.diameter <= 0) {
    throw Standard_ConstructionError("导线直径必须为正数");
  }
  if (params.sag <= 0) {
    throw Standard_ConstructionError("导线弧垂必须为正数");
  }

  std::vector<gp_Pnt> samples;
  Handle(Geom_BSplineCurve) curve;

  if (!params.fitPoints.empty()) {
    // 使用拟合点集创建样条曲线
    Handle(TColgp_HArray1OfPnt) points =
        new TColgp_HArray1OfPnt(1, params.fitPoints.size());
    for (int i = 0; i < params.fitPoints.size(); ++i) {
      points->SetValue(i + 1, params.fitPoints[i]);
    }

    GeomAPI_Interpolate interpolate(points, false, Precision::Confusion());
    interpolate.Load(gp_Vec(0, 0, 1), gp_Vec(0, 0, 1), true);
    interpolate.Perform();

    if (!interpolate.IsDone()) {
      throw Standard_ConstructionError("Failed to create interpolated curve");
    }

    curve = interpolate.Curve();
    if (curve.IsNull()) {
      throw Standard_ConstructionError("Failed to create curve");
    }

    return BRepBuilderAPI_MakeWire(BRepBuilderAPI_MakeEdge(curve).Edge())
        .Wire();
  } else {
    return BRepBuilderAPI_MakeWire(
               BRepBuilderAPI_MakeEdge(params.startPoint, params.endPoint)
                   .Edge())
        .Wire();
  }
}


TopoDS_Shape create_cable(const cable_params &params) {
  // 参数验证
  if (params.diameter <= 0.0) {
    throw Standard_ConstructionError("Diameter must be positive");
  }
  if (params.inflectionPoints.size() != params.radii.size()) {
    throw Standard_ConstructionError(
        "Inflection points and radii count mismatch");
  }
  for (double r : params.radii) {
    if (r <= 0.0) {
      throw Standard_ConstructionError("Radius must be positive");
    }
  }

  // 创建路径曲线
  BRepBuilderAPI_MakeWire wireMaker;
  std::vector<gp_Pnt> allPoints;
  allPoints.push_back(params.startPoint);
  allPoints.insert(allPoints.end(), params.inflectionPoints.begin(),
                   params.inflectionPoints.end());
  allPoints.push_back(params.endPoint);

  if (allPoints.size() == 2) {
    wireMaker.Add(
        BRepBuilderAPI_MakeEdge(params.startPoint, params.endPoint).Edge());
  } else {
    // 创建样条曲线
    Handle(TColgp_HArray1OfPnt) points =
        new TColgp_HArray1OfPnt(1, allPoints.size());
    for (int i = 0; i < allPoints.size(); ++i) {
      points->SetValue(i + 1, allPoints[i]);
    }

    GeomAPI_Interpolate interpolate(points, false, Precision::Confusion());
    // 不强加端部切向约束: 固定 (0,0,1) 与实际走向冲突时会生成病态曲线,
    // 导致后续 PipeShell Build 失败
    interpolate.Perform();
    if (!interpolate.IsDone()) {
      throw Standard_ConstructionError("Failed to create interpolated curve");
    }

    Handle(Geom_BSplineCurve) curve = interpolate.Curve();
    wireMaker.Add(BRepBuilderAPI_MakeEdge(curve).Edge());
  }

  if (!wireMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to create cable path");
  }
  TopoDS_Wire pathWire = wireMaker.Wire();

  // 获取路径起始点的切线方向
  BRepAdaptor_CompCurve curveAdaptor(wireMaker.Wire());
  gp_Pnt startPoint;
  gp_Vec startTangent;
  curveAdaptor.D1(curveAdaptor.FirstParameter(), startPoint, startTangent);

  // 在创建截面圆之前添加方向修正
  gp_Dir initNormal = startTangent.Normalized();
  gp_Dir refDir(0, 1, 0);
  // 确保参考方向与切线不平行
  if (Abs(initNormal.Dot(refDir)) > 0.99) {
    refDir = gp_Dir(1, 0, 0);
  }
  gp_Ax2 sectionAxes(gp::Origin(), initNormal, refDir);

  // 创建电缆截面圆
  gp_Circ sectionCircle(sectionAxes, params.diameter / 2);
  TopoDS_Edge sectionEdge = BRepBuilderAPI_MakeEdge(sectionCircle).Edge();
  TopoDS_Wire sectionWire = BRepBuilderAPI_MakeWire(sectionEdge).Wire();

  // 沿路径扫掠创建电缆
  BRepOffsetAPI_MakePipeShell pipeMaker(pathWire);
  pipeMaker.Add(sectionWire);
  pipeMaker.SetTolerance(1e-6); // 添加容差设置
  pipeMaker.SetMaxDegree(5);
  pipeMaker.SetMode(Standard_True); // 启用Frenet坐标系
  pipeMaker.SetTransitionMode(BRepBuilderAPI_RoundCorner);
  pipeMaker.Build();

  if (!pipeMaker.IsDone()) {
    fprintf(stderr, "DBG cable: pipe Build failed\n");
    throw Standard_ConstructionError("Failed to generate cable");
  }
  if (!pipeMaker.MakeSolid()) {
    fprintf(stderr, "DBG cable: MakeSolid failed\n");
    throw std::runtime_error("Failed to create a solid object from sweep");
  }

  return pipeMaker.Shape();
}


TopoDS_Wire create_cable_centerline(const cable_params &params) {
  // 参数验证
  if (params.diameter <= 0.0) {
    throw Standard_ConstructionError("Diameter must be positive");
  }

  // 收集所有路径点
  std::vector<gp_Pnt> allPoints;
  allPoints.push_back(params.startPoint);
  allPoints.insert(allPoints.end(), params.inflectionPoints.begin(),
                   params.inflectionPoints.end());
  allPoints.push_back(params.endPoint);
  if (allPoints.size() == 2) {
    return BRepBuilderAPI_MakeWire(
               BRepBuilderAPI_MakeEdge(allPoints[0], allPoints[1]).Edge())
        .Wire();
  } else {
    BRepBuilderAPI_MakeWire wireMaker;

    // 创建样条曲线
    Handle(TColgp_HArray1OfPnt) points =
        new TColgp_HArray1OfPnt(1, allPoints.size());
    for (int i = 0; i < allPoints.size(); ++i) {
      points->SetValue(i + 1, allPoints[i]);
    }

    GeomAPI_Interpolate interpolate(points, false, Precision::Confusion());
    interpolate.Load(gp_Vec(0, 0, 1), gp_Vec(0, 0, 1),
                     true); // 添加首末端导数约束
    interpolate.Perform();
    if (!interpolate.IsDone()) {
      throw Standard_ConstructionError("Failed to create interpolated curve");
    }

    Handle(Geom_BSplineCurve) curve = interpolate.Curve();
    wireMaker.Add(BRepBuilderAPI_MakeEdge(curve).Edge());

    if (!wireMaker.IsDone()) {
      throw Standard_ConstructionError("Failed to create cable path");
    }
    return wireMaker.Wire();
  }
}


std::vector<gp_Pnt> sample_cable(const cable_params &params,
                                 double tessellation) {
  // 参数验证
  if (params.diameter <= 0.0) {
    throw Standard_ConstructionError("Diameter must be positive");
  }

  // 收集所有路径点
  std::vector<gp_Pnt> allPoints;
  allPoints.push_back(params.startPoint);
  allPoints.insert(allPoints.end(), params.inflectionPoints.begin(),
                   params.inflectionPoints.end());
  allPoints.push_back(params.endPoint);

  // 计算采样点数量
  double totalLength = 0.0;
  for (size_t i = 1; i < allPoints.size(); ++i) {
    totalLength += allPoints[i - 1].Distance(allPoints[i]);
  }

  int sampleCount =
      tessellation > 0 ? static_cast<int>(totalLength / tessellation) : 20;
  sampleCount = std::max(sampleCount, 2); // 至少2个点

  std::vector<gp_Pnt> samples;
  samples.reserve(sampleCount);

  if (allPoints.size() == 2) {
    samples.push_back(allPoints[0]);
    samples.push_back(allPoints[1]);
  } else {
    // 曲线采样
    Handle(TColgp_HArray1OfPnt) points =
        new TColgp_HArray1OfPnt(1, allPoints.size());
    for (int i = 0; i < allPoints.size(); ++i) {
      points->SetValue(i + 1, allPoints[i]);
    }

    GeomAPI_Interpolate interpolate(points, false, Precision::Confusion());
    interpolate.Load(gp_Vec(0, 0, 1), gp_Vec(0, 0, 1), true);
    interpolate.Perform();

    if (!interpolate.IsDone()) {
      throw Standard_ConstructionError("Failed to create interpolated curve");
    }

    Handle(Geom_BSplineCurve) curve = interpolate.Curve();

    // 曲线参数化采样
    for (int i = 0; i < sampleCount; ++i) {
      double t = static_cast<double>(i) / (sampleCount - 1);
      gp_Pnt point;
      curve->D0(t * curve->LastParameter(), point);
      samples.push_back(point);
    }
  }

  return samples;
}


TopoDS_Shape create_cable(const cable_params &params, const gp_Pnt &position,
                          const gp_Dir &direction, const gp_Dir &upDirection) {
  // 首先创建标准方向的电缆
  TopoDS_Shape cable = create_cable(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 1, 0), gp_Dir(1, 0, 0));
  gp_Ax3 targetAx3(position, direction, upDirection);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(cable, transformation);
  return transform.Shape();
}


TopoDS_Shape create_curve_cable(const curve_cable_params &params) {
  // 参数验证
  if (params.diameter <= 0) {
    throw Standard_ConstructionError("Cable diameter must be positive");
  }
  if (params.controlPoints.empty()) {
    throw Standard_ConstructionError("Control points cannot be empty");
  }
  if (params.controlPoints.size() != params.curveTypes.size()) {
    throw Standard_ConstructionError(
        "Control points and curve types count mismatch");
  }

  auto create_transition = [](const gp_Dir &normal1, const gp_Dir &normal2,
                              const gp_Dir &upDir, const gp_Pnt &position,
                              double diameter) {
    // 计算两个法向量的夹角
    double angle = normal1.Angle(normal2);
    if (angle < Precision::Angular()) {
      return TopoDS_Shape(); // 角度太小不需要过渡
    }

    gp_Dir tan1Dir = gp_Vec(normal1).Normalized();
    gp_Dir ref1Dir = gp_Vec(upDir.Crossed(tan1Dir)).Normalized();

    // 如果参考方向长度接近0(切线几乎与径向平行)，使用全局Y轴作为备用
    if (gp_Vec(ref1Dir).SquareMagnitude() < Precision::SquareConfusion()) {
      ref1Dir = gp::DY();
    }

    gp_Dir tan2Dir = gp_Vec(normal2).Normalized();
    gp_Dir ref2Dir = gp_Vec(upDir.Crossed(tan2Dir)).Normalized();

    // 如果参考方向长度接近0(切线几乎与径向平行)，使用全局Y轴作为备用
    if (gp_Vec(ref2Dir).SquareMagnitude() < Precision::SquareConfusion()) {
      ref2Dir = gp::DY();
    }

    // 创建两个截面的局部坐标系
    gp_Ax2 ax1(position, tan1Dir, ref1Dir);
    gp_Ax2 ax2(position, tan2Dir, ref2Dir);

    gp_Circ circle1(ax1, diameter / 2);
    TopoDS_Wire shape1 =
        BRepBuilderAPI_MakeWire(BRepBuilderAPI_MakeEdge(circle1).Edge()).Wire();

    gp_Circ circle2(ax2, diameter / 2);
    TopoDS_Wire shape2 =
        BRepBuilderAPI_MakeWire(BRepBuilderAPI_MakeEdge(circle2).Edge()).Wire();

    TopoDS_Shape part1;
    {
      gp_Pnt position2 =
          position.Translated((gp_Vec(normal1).Normalized() * diameter).XYZ());
      BRepBuilderAPI_MakeWire wireMaker;
      wireMaker.Add(BRepBuilderAPI_MakeEdge(position, position2));

      TopoDS_Wire wire = wireMaker.Wire();

      BRepOffsetAPI_MakePipeShell pipeMaker(wire);
      pipeMaker.Add(shape1);

      pipeMaker.Build();

      if (!pipeMaker.IsDone()) {
        throw Standard_ConstructionError("Failed to create pipe");
      }

      if (!pipeMaker.MakeSolid()) {
        throw Standard_ConstructionError("Failed to make pipe solid");
      }

      part1 = pipeMaker.Shape();
    }

    TopoDS_Shape part2;
    {
      gp_Pnt position2 = position.Translated(
          (gp_Vec(normal2.Reversed()).Normalized() * diameter).XYZ());
      BRepBuilderAPI_MakeWire wireMaker;
      wireMaker.Add(BRepBuilderAPI_MakeEdge(position, position2));

      TopoDS_Wire wire = wireMaker.Wire();

      BRepOffsetAPI_MakePipeShell pipeMaker(wire);
      pipeMaker.Add(shape2);

      pipeMaker.Build();

      if (!pipeMaker.IsDone()) {
        throw Standard_ConstructionError("Failed to create pipe");
      }

      if (!pipeMaker.MakeSolid()) {
        throw Standard_ConstructionError("Failed to make pipe solid");
      }

      part2 = pipeMaker.Shape();
    }

    return BRepAlgoAPI_Common(part1, part2).Shape();
  };

  // 创建路径线
  std::vector<TopoDS_Wire> allWires;

  for (size_t i = 0; i < params.controlPoints.size(); ++i) {
    const auto &points = params.controlPoints[i];
    curve_type type = params.curveTypes[i];

    switch (type) {
    case curve_type::LINE: {
      if (points.size() != 2) {
        throw Standard_ConstructionError(
            "Line segment requires exactly 2 points");
      }
      TopoDS_Edge edge = BRepBuilderAPI_MakeEdge(points[0], points[1]).Edge();
      allWires.push_back(BRepBuilderAPI_MakeWire(edge).Wire());
      break;
    }
    case curve_type::ARC: {
      if (points.size() != 3) {
        throw Standard_ConstructionError(
            "Arc segment requires exactly 3 points");
      }
      // 创建三点圆弧
      GC_MakeArcOfCircle arcMaker(points[0], points[1], points[2]);
      if (!arcMaker.IsDone()) {
        throw Standard_ConstructionError("Failed to create arc segment");
      }
      TopoDS_Edge edge = BRepBuilderAPI_MakeEdge(arcMaker.Value()).Edge();
      allWires.push_back(BRepBuilderAPI_MakeWire(edge).Wire());
      break;
    }
    case curve_type::BEZIER: {
      if (points.size() < 3) { // 贝塞尔曲线至少需要起点、控制点和终点
        throw Standard_ConstructionError(
            "Bezier segment requires at least 3 points");
      }

      // 创建贝塞尔曲线控制点数组
      TColgp_Array1OfPnt poles(1, points.size());
      for (size_t j = 0; j < points.size(); ++j) {
        poles.SetValue(j + 1, points[j]);
      }

      // 创建二次或三次贝塞尔曲线
      Handle(Geom_BezierCurve) bezierCurve;
      if (points.size() == 3) { // 二次贝塞尔曲线
        bezierCurve = new Geom_BezierCurve(poles);
      } else { // 三次或更高阶贝塞尔曲线
        bezierCurve = new Geom_BezierCurve(poles);
      }

      // 创建边并添加到线框
      TopoDS_Edge edge = BRepBuilderAPI_MakeEdge(bezierCurve).Edge();
      allWires.push_back(BRepBuilderAPI_MakeWire(edge).Wire());
      break;
    }
    default:
      throw Standard_ConstructionError("Unknown curve type");
    }
  }

  TopoDS_Shape cable;
  gp_Dir prev_normal;
  bool has_prev = false;

  for (const auto &wire : allWires) {
    if (wire.IsNull()) {
      throw Standard_ConstructionError("Failed to create wire segment");
    }
    BRepAdaptor_CompCurve curveAdaptor(wire);
    gp_Pnt startPoint;
    gp_Vec startTangent;
    curveAdaptor.D1(curveAdaptor.FirstParameter(), startPoint, startTangent);

    gp_Pnt endPoint;
    gp_Vec endTangent;
    curveAdaptor.D1(curveAdaptor.LastParameter(), endPoint, endTangent);

    // 在创建截面圆之前添加方向修正
    gp_Dir initNormal = startTangent.Normalized();
    gp_Dir refDir(0, 1, 0);
    // 确保参考方向与切线不平行
    if (Abs(initNormal.Dot(refDir)) > 0.99) {
      refDir = gp_Dir(1, 0, 0);
    }
    gp_Ax2 sectionAxes(startPoint, initNormal, refDir);

    // 创建圆形截面（直径方向始终垂直于路径）
    gp_Circ circle(sectionAxes, params.diameter / 2);
    TopoDS_Wire profile =
        BRepBuilderAPI_MakeWire(BRepBuilderAPI_MakeEdge(circle).Edge()).Wire();

    // 使用扫掠器自动计算坐标系（添加Frenet模式）
    BRepOffsetAPI_MakePipeShell pipeMaker(wire);
    pipeMaker.SetMode(true);                   // 设置为实体模式
    pipeMaker.SetMaxDegree(5);                 // 提高最大阶数以适应复杂曲率
    pipeMaker.SetTolerance(1e-5);              // 放宽容差适应复杂路径
    pipeMaker.SetForceApproxC1(Standard_True); // 强制C1连续近似

    // 创建动态调整的圆形截面（直径始终垂直于路径）
    Handle(Law_Linear) law = new Law_Linear();
    law->Set(0, 1, 0, 1);                           // 保持恒定半径
    pipeMaker.SetLaw(profile, law, Standard_False); // 关联截面和变化规律

    pipeMaker.Add(profile);
    pipeMaker.SetTransitionMode(BRepBuilderAPI_RightCorner); // 改进过渡模式

    pipeMaker.Build();

    if (!pipeMaker.IsDone()) {
      throw Standard_ConstructionError("Failed to create cable by pipe shell");
    }
    if (!pipeMaker.MakeSolid()) {
      throw std::runtime_error("Failed to create a solid object from sweep");
    }

    if (cable.IsNull()) {
      cable = pipeMaker.Shape();
    } else {
      BRepAlgoAPI_Fuse fuse(cable, pipeMaker.Shape());
      if (!fuse.IsDone()) {
        throw Standard_ConstructionError("Failed to fuse cable segments");
      }
      cable = fuse.Shape();
    }

    // 如果有上一段，创建过渡面
    if (has_prev) {
      TopoDS_Shape transition =
          create_transition(prev_normal, initNormal, gp_Dir(0, 0, 1),
                            startPoint, params.diameter);

      if (!transition.IsNull()) {
        cable = BRepAlgoAPI_Fuse(cable, transition).Shape();
      }
    }

    // 保存当前段信息供下一段使用
    prev_normal = endTangent.Normalized();
    has_prev = true;
  }

  return cable;
}


TopoDS_Shape create_curve_cable(const curve_cable_params &params,
                                const gp_Pnt &position, const gp_Dir &direction,
                                const gp_Dir &upDirection) {
  // 正交性校验
  if (Abs(direction.Dot(upDirection)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Direction and up direction must be perpendicular");
  }

  // 创建标准方向的电缆
  TopoDS_Shape cable = create_curve_cable(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, direction, upDirection);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(cable, transformation);
  return transform.Shape();
}


TopoDS_Wire create_curve_cable_centerline(const curve_cable_params &params) {
  // 参数验证
  if (params.controlPoints.empty()) {
    throw Standard_ConstructionError("Control points cannot be empty");
  }
  if (params.controlPoints.size() != params.curveTypes.size()) {
    throw Standard_ConstructionError(
        "Control points and curve types count mismatch");
  }
  BRepBuilderAPI_MakeWire wireMaker;
  for (size_t i = 0; i < params.controlPoints.size(); ++i) {
    const auto &points = params.controlPoints[i];
    curve_type type = params.curveTypes[i];

    switch (type) {
    case curve_type::LINE: {
      if (points.size() != 2) {
        throw Standard_ConstructionError(
            "Line segment requires exactly 2 points");
      }
      TopoDS_Edge edge = BRepBuilderAPI_MakeEdge(points[0], points[1]).Edge();
      wireMaker.Add(edge);
      break;
    }
    case curve_type::ARC: {
      if (points.size() != 3) {
        throw Standard_ConstructionError(
            "Arc segment requires exactly 3 points");
      }
      // 创建三点圆弧
      GC_MakeArcOfCircle arcMaker(points[0], points[1], points[2]);
      if (!arcMaker.IsDone()) {
        throw Standard_ConstructionError("Failed to create arc segment");
      }
      TopoDS_Edge edge = BRepBuilderAPI_MakeEdge(arcMaker.Value()).Edge();
      wireMaker.Add(edge);
      break;
    }
    case curve_type::BEZIER: {
      if (points.size() < 3) { // 贝塞尔曲线至少需要起点、控制点和终点
        throw Standard_ConstructionError(
            "Bezier segment requires at least 3 points");
      }

      // 创建贝塞尔曲线控制点数组
      TColgp_Array1OfPnt poles(1, points.size());
      for (size_t j = 0; j < points.size(); ++j) {
        poles.SetValue(j + 1, points[j]);
      }

      // 创建二次或三次贝塞尔曲线
      Handle(Geom_BezierCurve) bezierCurve;
      if (points.size() == 3) { // 二次贝塞尔曲线
        bezierCurve = new Geom_BezierCurve(poles);
      } else { // 三次或更高阶贝塞尔曲线
        bezierCurve = new Geom_BezierCurve(poles);
      }

      // 创建边并添加到线框
      TopoDS_Edge edge = BRepBuilderAPI_MakeEdge(bezierCurve).Edge();
      wireMaker.Add(edge);
      break;
    }
    default:
      throw Standard_ConstructionError("Unknown curve type");
    }
  }
  return wireMaker.Wire();
}


TopoDS_Wire create_cable_wire_centerline(const cable_wire_params &params) {
  // 参数验证
  if (params.points.size() < 2) {
    throw Standard_ConstructionError("At least 2 points are required");
  }
  if (params.outsideDiameter <= 0.0) {
    throw Standard_ConstructionError("Outside diameter must be positive");
  }

  // 创建电缆路径
  BRepBuilderAPI_MakeWire wireMaker;

  if (params.points.size() == 2) {
    // 直接创建直线
    wireMaker.Add(
        BRepBuilderAPI_MakeEdge(params.points[0], params.points[1]).Edge());
  } else {

    // 使用拟合点集创建样条曲线
    Handle(TColgp_HArray1OfPnt) points =
        new TColgp_HArray1OfPnt(1, params.points.size());
    for (int i = 0; i < params.points.size(); ++i) {
      points->SetValue(i + 1, params.points[i]);
    }

    GeomAPI_Interpolate interpolate(points, false, Precision::Confusion());
    interpolate.Load(gp_Vec(0, 0, 1), gp_Vec(0, 0, 1),
                     true); // 添加首末端导数约束
    interpolate.Perform();
    if (!interpolate.IsDone()) {
      throw Standard_ConstructionError("Failed to create interpolated curve");
    }

    const Handle(Geom_BSplineCurve) &curve = interpolate.Curve();
    if (curve.IsNull()) {
      throw Standard_ConstructionError("Failed to create curve");
    }
    BRepBuilderAPI_MakeEdge edgeMaker(curve);
    if (!edgeMaker.IsDone()) {
      throw Standard_ConstructionError("Failed to create edge from curve");
    }
    wireMaker.Add(edgeMaker.Edge());
  }
  return wireMaker.Wire();
}


TopoDS_Shape create_cable_wire(const cable_wire_params &params) {
  // 参数验证
  if (params.points.size() < 2) {
    throw Standard_ConstructionError("At least 2 points are required");
  }
  if (params.outsideDiameter <= 0.0) {
    throw Standard_ConstructionError("Outside diameter must be positive");
  }

  // 创建电缆路径
  BRepBuilderAPI_MakeWire wireMaker;

  if (params.points.size() == 2) {
    // 直接创建直线
    wireMaker.Add(
        BRepBuilderAPI_MakeEdge(params.points[0], params.points[1]).Edge());
  } else {

    // 使用拟合点集创建样条曲线
    Handle(TColgp_HArray1OfPnt) points =
        new TColgp_HArray1OfPnt(1, params.points.size());
    for (int i = 0; i < params.points.size(); ++i) {
      points->SetValue(i + 1, params.points[i]);
    }

    GeomAPI_Interpolate interpolate(points, false, Precision::Confusion());
    // 不强加端部切向约束 (固定 (0,0,1) 与实际走向冲突会生成病态曲线)
    interpolate.Perform();
    if (!interpolate.IsDone()) {
      throw Standard_ConstructionError("Failed to create interpolated curve");
    }

    const Handle(Geom_BSplineCurve) &curve = interpolate.Curve();
    if (curve.IsNull()) {
      throw Standard_ConstructionError("Failed to create curve");
    }
    BRepBuilderAPI_MakeEdge edgeMaker(curve);
    if (!edgeMaker.IsDone()) {
      throw Standard_ConstructionError("Failed to create edge from curve");
    }
    wireMaker.Add(edgeMaker.Edge());
  }

  // 获取路径起始点的切线方向
  BRepAdaptor_CompCurve curveAdaptor(wireMaker.Wire());
  gp_Pnt startPoint;
  gp_Vec startTangent;
  curveAdaptor.D1(curveAdaptor.FirstParameter(), startPoint, startTangent);

  // 在创建截面圆之前添加方向修正
  gp_Dir initNormal = startTangent.Normalized();
  gp_Dir refDir(0, 1, 0);
  // 确保参考方向与切线不平行
  if (Abs(initNormal.Dot(refDir)) > 0.99) {
    refDir = gp_Dir(1, 0, 0);
  }
  gp_Ax2 sectionAxes(gp::Origin(), initNormal, refDir);

  // 创建圆形截面（直径方向始终垂直于路径）
  gp_Circ circle(sectionAxes, params.outsideDiameter / 2);
  TopoDS_Wire profile =
      BRepBuilderAPI_MakeWire(BRepBuilderAPI_MakeEdge(circle).Edge()).Wire();

  // 沿路径扫掠生成电缆
  BRepOffsetAPI_MakePipeShell pipeMaker(wireMaker.Wire());
  pipeMaker.Add(profile);
  pipeMaker.SetMode(Standard_True); // 使用Frenet坐标系
  pipeMaker.SetTolerance(1e-6);
  pipeMaker.SetMaxDegree(5);
  pipeMaker.SetTransitionMode(BRepBuilderAPI_RoundCorner);
  pipeMaker.Build();

  if (!pipeMaker.IsDone()) {
    throw Standard_ConstructionError("Failed to generate cable wire");
  }
  if (!pipeMaker.MakeSolid()) {
    throw std::runtime_error("Failed to create a solid object from sweep");
  }

  return pipeMaker.Shape();
}


TopoDS_Shape create_cable_wire(const cable_wire_params &params,
                               const gp_Pnt &position, const gp_Dir &direction,
                               const gp_Dir &upDirection) {
  // 首先创建标准方向的电缆
  TopoDS_Shape cable = create_cable_wire(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 1, 0), gp_Dir(1, 0, 0));
  gp_Ax3 targetAx3(position, direction, upDirection);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(cable, transformation);
  return transform.Shape();
}


TopoDS_Shape create_cable_joint(const cable_joint_params &params) {
  // 参数验证
  if (params.length <= 0 || params.outerDiameter <= 0 ||
      params.terminalLength <= 0 || params.innerDiameter <= 0) {
    throw Standard_ConstructionError("All dimensions must be positive");
  }
  if (params.innerDiameter >= params.outerDiameter) {
    throw Standard_ConstructionError(
        "Inner diameter must be less than outer diameter");
  }
  if (params.terminalLength * 2 >= params.length) {
    throw Standard_ConstructionError(
        "Terminal length too large compared to total length");
  }

  // 计算中间圆柱体长度
  double middleLength = params.length - (2 * params.terminalLength);

  // 创建中间圆柱体
  gp_Ax2 middleAxis(gp_Pnt(-middleLength / 2, 0, 0), gp::DX());
  TopoDS_Shape joint = BRepPrimAPI_MakeCylinder(
                           middleAxis, params.outerDiameter / 2, middleLength)
                           .Shape();

  // 创建两端过渡圆台
  gp_Ax2 leftAxis(gp_Pnt(-params.length / 2, 0, 0), gp::DX());
  TopoDS_Shape leftCone =
      BRepPrimAPI_MakeCone(leftAxis, params.innerDiameter / 2,
                           params.outerDiameter / 2, params.terminalLength)
          .Shape();

  gp_Ax2 rightAxis(gp_Pnt(params.length / 2 - params.terminalLength, 0, 0),
                   gp::DX());
  TopoDS_Shape rightCone =
      BRepPrimAPI_MakeCone(rightAxis, params.outerDiameter / 2,
                           params.innerDiameter / 2, params.terminalLength)
          .Shape();

  // 合并所有部件
  joint = BRepAlgoAPI_Fuse(joint, leftCone).Shape();
  joint = BRepAlgoAPI_Fuse(joint, rightCone).Shape();

  // 创建中间芯体
  gp_Ax2 holeAxis(gp_Pnt(-params.length / 2 - 1, 0, 0), gp::DX());
  TopoDS_Shape middleHole =
      BRepPrimAPI_MakeCylinder(holeAxis, params.innerDiameter / 2,
                               params.length + 2)
          .Shape();

  BRepAlgoAPI_Cut fusHole(joint, middleHole);
  if (!fusHole.IsDone()) {
    throw Standard_ConstructionError("Failed to fuse port with joint");
  }
  joint = fusHole.Shape();

  return joint;
}


TopoDS_Shape create_cable_joint(const cable_joint_params &params,
                                const gp_Pnt &position, const gp_Dir &direction,
                                const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(direction.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Direction and xDir must be perpendicular");
  }

  // 创建标准方向的接头
  TopoDS_Shape joint = create_cable_joint(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, direction, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(joint, transformation);
  return transform.Shape();
}


TopoDS_Shape create_optical_fiber_box(const optical_fiber_box_params &params) {
  // 参数验证
  if (params.length <= 0 || params.height <= 0 || params.width <= 0) {
    throw Standard_ConstructionError("All dimensions must be positive");
  }

  // 创建主体盒子
  gp_Pnt corner(-params.length / 2, -params.width / 2, -params.height / 2);
  TopoDS_Shape box =
      BRepPrimAPI_MakeBox(corner, params.length, params.width, params.height)
          .Shape();

  // 创建顶部圆角特征
  double radius = std::min(params.width, params.height) * 0.1;
  BRepFilletAPI_MakeFillet fillet(box);

  TopExp_Explorer explorer(box, TopAbs_EDGE);
  while (explorer.More()) {
    TopoDS_Edge edge = TopoDS::Edge(explorer.Current());
    fillet.Add(radius, edge);
    explorer.Next();
  }

  return fillet.Shape();
}


TopoDS_Shape create_optical_fiber_box(const optical_fiber_box_params &params,
                                      const gp_Pnt &position,
                                      const gp_Dir &direction,
                                      const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(direction.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Direction and xDir must be perpendicular");
  }

  // 创建标准方向的接头盒
  TopoDS_Shape box = create_optical_fiber_box(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, direction, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(box, transformation);
  return transform.Shape();
}


// 创建户外-干式电缆终端
TopoDS_Shape
create_outdoor_cable_terminal(const cable_terminal_params &params) {
  BRep_Builder builder;
  TopoDS_Compound compound;
  builder.MakeCompound(compound);

  double currentZ = -params.lowerTerminalLength;

  // 1. 创建下端电缆连接器 (圆柱)
  gp_Ax2 lowerTerminalAxis(gp_Pnt(0, 0, currentZ), gp::DZ());
  TopoDS_Shape lowerTerminal =
      BRepPrimAPI_MakeCylinder(lowerTerminalAxis,
                               params.lowerTerminalDiameter / 2,
                               params.lowerTerminalLength)
          .Shape();
  builder.Add(compound, lowerTerminal);
  currentZ += params.lowerTerminalLength;

  // 2. 创建法兰盘
  // 法兰盘主体 (矩形)
  double flangeThickness = params.flangeBoltHeight / 2;
  gp_Pnt flangeCorner1(-params.flangeWidth / 2, -params.flangeWidth / 2,
                       currentZ);
  gp_Pnt flangeCorner2(params.flangeWidth / 2, params.flangeWidth / 2,
                       currentZ + flangeThickness);
  TopoDS_Shape flange =
      BRepPrimAPI_MakeBox(flangeCorner1, flangeCorner2).Shape();

  // 边缘倒角（仅处理四个角上平行于Z轴的四条边）
  if (params.flangeChamferRadius > 0) {
    BRepFilletAPI_MakeChamfer chamfer(flange);
    TopExp_Explorer edgeExp(flange, TopAbs_EDGE);

    // 检查每条边是否在四个角上且平行于Z轴
    for (; edgeExp.More(); edgeExp.Next()) {
      TopoDS_Edge edge = TopoDS::Edge(edgeExp.Current());

      // 获取边的两个顶点
      TopoDS_Vertex v1, v2;
      TopExp::Vertices(edge, v1, v2);
      gp_Pnt p1 = BRep_Tool::Pnt(v1);
      gp_Pnt p2 = BRep_Tool::Pnt(v2);

      // 检查边是否平行于Z轴
      if (Abs(p1.X() - p2.X()) < Precision::Confusion() &&
          Abs(p1.Y() - p2.Y()) < Precision::Confusion()) {
        chamfer.Add(params.flangeChamferRadius, edge);
      }
    }
    flange = chamfer.Shape();
  }

  // 中心孔
  gp_Ax2 centerAxis(gp_Pnt(0, 0, currentZ), gp::DZ());
  TopoDS_Shape centerHole =
      BRepPrimAPI_MakeCylinder(centerAxis, params.flangeCenterHoleRadius,
                               flangeThickness)
          .Shape();
  flange = BRepAlgoAPI_Cut(flange, centerHole).Shape();

  // 矩形开口
  if (params.flangeOpeningWidth > 0) {
    gp_Pnt openingCorner1(-params.flangeOpeningWidth / 2, 0, currentZ);
    gp_Pnt openingCorner2(params.flangeOpeningWidth / 2, params.flangeWidth / 2,
                          currentZ + flangeThickness);
    TopoDS_Shape opening =
        BRepPrimAPI_MakeBox(openingCorner1, openingCorner2).Shape();
    flange = BRepAlgoAPI_Cut(flange, opening).Shape();
  }

  // 螺栓孔
  if (params.flangeHoleDiameter > 0) {
    // 创建螺栓（四个角的圆柱体）
    double boltRadius = params.flangeHoleDiameter / 2;
    double boltHeight = params.flangeBoltHeight;
    double boltProtrusion = boltHeight / 4; // 上下各露出1/4高度
    double boltPos = params.flangeHoleSpacing / 2;

    gp_Pnt boltPositions[4] = {
        gp_Pnt(boltPos, boltPos, currentZ - boltProtrusion),
        gp_Pnt(-boltPos, boltPos, currentZ - boltProtrusion),
        gp_Pnt(boltPos, -boltPos, currentZ - boltProtrusion),
        gp_Pnt(-boltPos, -boltPos, currentZ - boltProtrusion)};

    for (int i = 0; i < 4; i++) {
      gp_Ax2 boltAxis(boltPositions[i], gp::DZ());
      TopoDS_Shape bolt =
          BRepPrimAPI_MakeCylinder(boltAxis, boltRadius, boltHeight).Shape();
      flange = BRepAlgoAPI_Fuse(flange, bolt).Shape();
    }
  }

  // 添加法兰盘到组合体
  builder.Add(compound, flange);
  currentZ += flangeThickness;

  // 3. 创建尾管 (圆柱)
  gp_Ax2 tailAxis(gp_Pnt(0, 0, currentZ), gp::DZ());
  TopoDS_Shape tail = BRepPrimAPI_MakeCylinder(
                          tailAxis, params.tailDiameter / 2, params.tailHeight)
                          .Shape();
  builder.Add(compound, tail);
  currentZ += params.tailHeight;

  // 4. 创建绝缘子 (锥形或圆柱)
  gp_Ax2 insulatorAxis(gp_Pnt(0, 0, currentZ), gp::DZ());
  TopoDS_Shape insulator;
  if (fabs(params.topDiameter - params.bottomDiameter) <
      Precision::Confusion()) {
    // 等径圆柱
    insulator = BRepPrimAPI_MakeCylinder(insulatorAxis, params.topDiameter / 2,
                                         params.height)
                    .Shape();
  } else {
    // 锥形
    insulator = BRepPrimAPI_MakeCone(insulatorAxis, params.bottomDiameter / 2,
                                     params.topDiameter / 2, params.height)
                    .Shape();
  }
  builder.Add(compound, insulator);

  // 添加伞裙 (仅当有伞裙参数时)
  if (params.skirtCount > 0) {
    double skirtHeight = params.skirtSectionHeight;
    double skirtSpacing = (params.height - params.skirtCount * skirtHeight) /
                          (params.skirtCount + 1);

    for (int i = 0; i < params.skirtCount; ++i) {
      // 计算当前高度位置
      double zPos = currentZ + skirtSpacing + i * (skirtHeight + skirtSpacing);

      // 计算当前直径 (线性插值)
      double ratio = zPos / params.height;
      double currentDiameter =
          params.bottomDiameter +
          (params.topDiameter - params.bottomDiameter) * ratio;

      // 选择伞裙类型 (交替使用两种伞裙)
      bool useUpperSkirt = (i % 2 == 0);
      double skirtTopDiameter = useUpperSkirt ? params.upperSkirtTopDiameter
                                              : params.lowerSkirtTopDiameter;
      double skirtBottomDiameter = useUpperSkirt
                                       ? params.upperSkirtBottomDiameter
                                       : params.lowerSkirtBottomDiameter;

      // 创建伞裙截面 (5点曲线)
      BRepBuilderAPI_MakeWire wire;
      gp_Pnt basePoint(currentDiameter / 2, 0, zPos); // 起始点：主体表面
      gp_Pnt p1(skirtTopDiameter / 2, 0, zPos);       // 伞裙外缘顶部
      gp_Pnt p2(skirtBottomDiameter / 2, 0,
                zPos + skirtHeight * 0.3); // 伞裙外缘底部
      gp_Pnt p3(currentDiameter / 2 * 0.9, 0,
                zPos + skirtHeight * 0.6); // 内凹点
      gp_Pnt endPoint(currentDiameter / 2, 0,
                      zPos + skirtHeight); // 结束点：主体表面

      wire.Add(BRepBuilderAPI_MakeEdge(basePoint, p1));
      wire.Add(BRepBuilderAPI_MakeEdge(p1, p2));
      wire.Add(BRepBuilderAPI_MakeEdge(p2, p3));
      wire.Add(BRepBuilderAPI_MakeEdge(p3, endPoint));
      wire.Add(BRepBuilderAPI_MakeEdge(endPoint, basePoint));

      if (!wire.IsDone()) {
        throw Standard_ConstructionError("Failed to create skirt wire");
      }

      // 旋转生成伞裙 (360度)
      BRepPrimAPI_MakeRevol skirtRevol(BRepLib_MakeFace(wire.Wire()).Face(),
                                       gp_Ax1(gp::Origin(), gp::DZ()));
      TopoDS_Shape skirt = skirtRevol.Shape();
      if (skirt.IsNull()) {
        throw Standard_ConstructionError("Failed to create skirt");
      }

      builder.Add(compound, skirt);
    }
  }

  currentZ += params.height;

  // 5. 创建顶部连接金具 (带孔的圆柱)
  gp_Ax2 upperTerminalAxis(gp_Pnt(0, 0, currentZ), gp::DZ());
  TopoDS_Shape upperTerminal =
      BRepPrimAPI_MakeCylinder(upperTerminalAxis,
                               params.upperTerminalDiameter / 2,
                               params.upperTerminalLength)
          .Shape();

  // 添加连接孔
  if (params.hole1Diameter > 0 && params.hole2Diameter > 0) {
    double holeZ = currentZ + params.upperTerminalLength - params.hole1Distance;
    gp_Ax2 hole1Axis(gp_Pnt(0, -params.upperTerminalDiameter / 2, holeZ),
                     gp::DY());
    TopoDS_Shape hole1 =
        BRepPrimAPI_MakeCylinder(hole1Axis, params.hole1Diameter / 2,
                                 params.upperTerminalDiameter)
            .Shape();

    gp_Ax2 hole2Axis(gp_Pnt(0, -params.upperTerminalDiameter / 2,
                            holeZ - params.holeSpacing),
                     gp::DY());
    TopoDS_Shape hole2 =
        BRepPrimAPI_MakeCylinder(hole2Axis, params.hole2Diameter / 2,
                                 params.upperTerminalDiameter)
            .Shape();

    upperTerminal = BRepAlgoAPI_Cut(upperTerminal, hole1).Shape();
    upperTerminal = BRepAlgoAPI_Cut(upperTerminal, hole2).Shape();
  }

  builder.Add(compound, upperTerminal);

  return compound;
}


// 创建户内电缆终端
TopoDS_Shape create_indoor_cable_terminal(const cable_terminal_params &params) {
  BRep_Builder builder;
  TopoDS_Compound compound;
  builder.MakeCompound(compound);

  double currentZ = 0;

  // 1. 创建下端电缆连接器 (圆柱)
  gp_Ax2 lowerTerminalAxis(gp_Pnt(0, 0, currentZ), gp::DZ());
  TopoDS_Shape lowerTerminal =
      BRepPrimAPI_MakeCylinder(lowerTerminalAxis,
                               params.lowerTerminalDiameter / 2,
                               params.lowerTerminalLength)
          .Shape();
  builder.Add(compound, lowerTerminal);
  currentZ += params.lowerTerminalLength;

  // 2. 创建主体 (锥形或圆柱)
  gp_Ax2 bodyAxis(gp_Pnt(0, 0, currentZ), gp::DZ());
  TopoDS_Shape body;
  if (fabs(params.topDiameter - params.bottomDiameter) <
      Precision::Confusion()) {
    // 等径圆柱
    body = BRepPrimAPI_MakeCylinder(bodyAxis, params.topDiameter / 2,
                                    params.height)
               .Shape();
  } else {
    // 锥形
    body = BRepPrimAPI_MakeCone(bodyAxis, params.bottomDiameter / 2,
                                params.topDiameter / 2, params.height)
               .Shape();
  }
  builder.Add(compound, body);
  currentZ += params.height;

  // 3. 创建顶部连接金具 (圆柱)
  gp_Ax2 upperTerminalAxis(gp_Pnt(0, 0, currentZ), gp::DZ());
  TopoDS_Shape upperTerminal =
      BRepPrimAPI_MakeCylinder(upperTerminalAxis,
                               params.upperTerminalDiameter / 2,
                               params.upperTerminalLength)
          .Shape();
  builder.Add(compound, upperTerminal);

  return compound;
}


TopoDS_Shape create_cable_terminal(const cable_terminal_params &params) {
  // 根据类型调用不同的创建函数
  if (params.sort == cable_terminal_type::OUTDOOR ||
      params.sort == cable_terminal_type::DRY) { // 户外或干式
    return create_outdoor_cable_terminal(params);
  } else { // 户内
    return create_indoor_cable_terminal(params);
  }
}


TopoDS_Shape create_cable_terminal(const cable_terminal_params &params,
                                   const gp_Pnt &position,
                                   const gp_Dir &direction) {
  // 创建标准方向的终端
  TopoDS_Shape terminal = create_cable_terminal(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp::DZ());
  gp_Ax3 targetAx3(position, direction);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  // 应用变换
  BRepBuilderAPI_Transform transform(terminal, transformation);
  return transform.Shape();
}


TopoDS_Shape create_cable_accessory(const cable_accessory_params &params) {
  // 参数验证
  if (params.length <= 0 || params.width <= 0 || params.height <= 0) {
    throw Standard_ConstructionError("Box dimensions must be positive");
  }
  if (params.portCount != 3 && params.portCount != 6) {
    throw Standard_ConstructionError("Port count must be 3 or 6");
  }
  if (params.portDiameter <= 0) {
    throw Standard_ConstructionError("Port diameter must be positive");
  }

  // 创建箱体主体
  gp_Pnt origin(-params.length / 2, -params.width / 2, -params.height / 2);
  TopoDS_Shape box =
      BRepPrimAPI_MakeBox(origin, params.length, params.width, params.height)
          .Shape();

  // 创建电缆进出口
  double radius = params.portDiameter / 2;

  std::array<gp_Pnt, 2> portCenters;
  if (params.portCount == 3) {
    portCenters[0] = gp_Pnt(0, -params.width / 2 + params.sidePanelDistance,
                            -params.height / 2);
  } else if (params.portCount == 6) {
    portCenters[0] = gp_Pnt(0, -params.width / 2 + params.sidePanelDistance,
                            -params.height / 2);
    portCenters[1] = gp_Pnt(0, params.width / 2 - params.sidePanelDistance,
                            -params.height / 2);
  }

  int row = params.portCount == 3 ? 1 : 2;

  for (int i = 0; i < row; ++i) {
    gp_Pnt portCenter = portCenters[i];

    gp_Ax2 midAxis(gp_Pnt(portCenter.X(), portCenter.Y(),
                          portCenter.Z() + params.height / 2),
                   gp_Dir(0, 0, -1));
    TopoDS_Shape portMid = BRepPrimAPI_MakeCylinder(
                               midAxis, params.portDiameter / 2, params.height)
                               .Shape();

    gp_Ax2 leftAxis(gp_Pnt(portCenter.X() - params.portSpacing, portCenter.Y(),
                           portCenter.Z() + params.height / 2),
                    gp_Dir(0, 0, -1));
    TopoDS_Shape portLeft =
        BRepPrimAPI_MakeCylinder(leftAxis, params.portDiameter / 2,
                                 params.height)
            .Shape();

    gp_Ax2 rightAxis(gp_Pnt(portCenter.X() + params.portSpacing, portCenter.Y(),
                            portCenter.Z() + params.height / 2),
                     gp_Dir(0, 0, -1));
    TopoDS_Shape portRight =
        BRepPrimAPI_MakeCylinder(rightAxis, params.portDiameter / 2,
                                 params.height)
            .Shape();

    BRepAlgoAPI_Cut fuseMaker0(box, portMid);
    if (!fuseMaker0.IsDone()) {
      throw Standard_ConstructionError("Failed to fuse port with box");
    }
    box = fuseMaker0.Shape();

    BRepAlgoAPI_Cut fuseMaker1(box, portLeft);
    if (!fuseMaker1.IsDone()) {
      throw Standard_ConstructionError("Failed to fuse port with box");
    }
    box = fuseMaker1.Shape();

    BRepAlgoAPI_Cut fuseMaker2(box, portRight);
    if (!fuseMaker2.IsDone()) {
      throw Standard_ConstructionError("Failed to fuse port with box");
    }
    box = fuseMaker2.Shape();
  }

  return box;
}


TopoDS_Shape create_cable_accessory(const cable_accessory_params &params,
                                    const gp_Pnt &position,
                                    const gp_Dir &normal, const gp_Dir &xDir) {
  // 首先创建标准方向的箱体
  TopoDS_Shape box = create_cable_accessory(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, normal, xDir);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(box, transformation);
  return transform.Shape();
}


TopoDS_Shape create_cable_bracket(const cable_bracket_params &params) {
  // 参数验证
  if (params.length <= 0)
    throw Standard_ConstructionError("Length must be positive");
  if (params.rootHeight <= 0)
    throw Standard_ConstructionError("Root height must be positive");
  if (params.rootWidth <= 0)
    throw Standard_ConstructionError("Root width must be positive");
  if (params.width <= 0)
    throw Standard_ConstructionError("Width must be positive");
  if (params.topThickness <= 0)
    throw Standard_ConstructionError("Top thickness must be positive");
  if (params.rootThickness <= 0)
    throw Standard_ConstructionError("Root thickness must be positive");

  // 创建支架根部（垂直部分）
  gp_Pnt rootP1(0, -params.rootThickness / 2, 0);
  gp_Pnt rootP2(0, params.rootThickness / 2, 0);
  gp_Pnt rootP3(0, params.rootThickness / 2, -params.rootHeight);
  gp_Pnt rootP4(0, -params.rootThickness / 2, -params.rootHeight);

  BRepBuilderAPI_MakePolygon rootPoly;
  rootPoly.Add(rootP1);
  rootPoly.Add(rootP2);
  rootPoly.Add(rootP3);
  rootPoly.Add(rootP4);
  rootPoly.Close();

  TopoDS_Face rootFace = BRepBuilderAPI_MakeFace(rootPoly.Wire()).Face();
  TopoDS_Shape root =
      BRepPrimAPI_MakePrism(rootFace, gp_Vec(params.rootWidth, 0, 0)).Shape();

  // 创建支架顶部（水平部分）
  gp_Pnt topP1(params.rootWidth, -params.topThickness / 2, 0);
  gp_Pnt topP2(params.rootWidth, params.topThickness / 2, 0);
  gp_Pnt topP3(params.rootWidth, params.topThickness / 2, -params.width);
  gp_Pnt topP4(params.rootWidth, -params.topThickness / 2, -params.width);

  BRepBuilderAPI_MakePolygon topPoly;
  topPoly.Add(topP1);
  topPoly.Add(topP2);
  topPoly.Add(topP3);
  topPoly.Add(topP4);
  topPoly.Close();

  TopoDS_Face topFace = BRepBuilderAPI_MakeFace(topPoly.Wire()).Face();
  TopoDS_Shape top =
      BRepPrimAPI_MakePrism(topFace, gp_Vec(params.length, 0, 0)).Shape();

  // 合并根部和顶部
  TopoDS_Shape support = BRepAlgoAPI_Fuse(root, top).Shape();

  // 添加三角形加强筋（新增强部分）
  {
    // 定义三角形顶点（Y方向位于底面，后续进行拉伸）
    gp_Pnt ribA(params.rootWidth, -params.topThickness / 4,
                -params.rootHeight);                            // 根部底点
    gp_Pnt ribB(params.rootWidth, -params.topThickness / 4, 0); // 顶部起点
    gp_Pnt ribC(params.rootWidth + params.length / 2, -params.topThickness / 4,
                -params.width); // 顶部终点

    // 构建三角形轮廓
    BRepBuilderAPI_MakePolygon ribPoly;
    ribPoly.Add(ribA);
    ribPoly.Add(ribB);
    ribPoly.Add(ribC);
    ribPoly.Close(); // 闭合为三角形

    // 创建面并沿Y轴拉伸形成实体
    TopoDS_Face ribFace = BRepBuilderAPI_MakeFace(ribPoly.Wire()).Face();
    TopoDS_Shape rib =
        BRepPrimAPI_MakePrism(ribFace, gp_Vec(0, params.topThickness / 2, 0))
            .Shape();

    // 将加强筋融合到主体结构
    support = BRepAlgoAPI_Fuse(support, rib).Shape();
  }

  // 创建立柱安装孔（修正方向轴）
  for (const auto &point : params.columnMountPoints) {
    gp_Ax2 holeAxis(point, gp::DY());
    TopoDS_Shape hole =
        BRepPrimAPI_MakeCylinder(holeAxis, params.rootThickness / 2,
                                 params.rootThickness * 2)
            .Shape();
    support = BRepAlgoAPI_Cut(support, hole).Shape();
  }

  // 创建夹具安装孔（修正方向轴）
  for (const auto &point : params.clampMountPoints) {
    gp_Ax2 holeAxis(point, gp::DY());
    TopoDS_Shape hole =
        BRepPrimAPI_MakeCylinder(holeAxis, params.topThickness / 2,
                                 params.topThickness * 2)
            .Shape();
    support = BRepAlgoAPI_Cut(support, hole).Shape();
  }

  return support;
}


TopoDS_Shape create_cable_bracket(const cable_bracket_params &params,
                                  const gp_Pnt &position, const gp_Dir &normal,
                                  const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(normal.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Normal and direction must be perpendicular");
  }

  // 创建标准方向的支架
  TopoDS_Shape support = create_cable_bracket(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, normal, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(support, transformation);
  return transform.Shape();
}


TopoDS_Shape create_cable_clamp(const cable_clamp_params &params) {
  // 参数验证
  if (params.diameter <= 0 || params.thickness <= 0 || params.width <= 0) {
    throw Standard_ConstructionError("Dimensions must be positive");
  }

  switch (params.type) {
  case cable_clamp_type::SINGLE: {
    // 单根夹具 - 矩形底板 + 环形圆柱
    // 创建底板
    TopoDS_Shape base =
        BRepPrimAPI_MakeBox(gp_Pnt(-(params.diameter) / 2 - params.thickness,
                                   -params.width / 2, 0),
                            params.diameter + params.thickness * 2,
                            params.width, params.thickness)
            .Shape();

    // 创建环形圆柱
    TopoDS_Shape outerCyl =
        BRepPrimAPI_MakeCylinder(
            gp_Ax2(gp_Pnt(0, -params.width / 2,
                          params.thickness + (params.diameter / 2) +
                              params.thickness),
                   gp::DY()),
            params.diameter / 2 + params.thickness, params.width)
            .Shape();
    TopoDS_Shape innerCyl =
        BRepPrimAPI_MakeCylinder(
            gp_Ax2(gp_Pnt(0, -params.width / 2,
                          params.thickness + (params.diameter / 2) +
                              params.thickness),
                   gp::DY()),
            params.diameter / 2, params.width)
            .Shape();
    TopoDS_Shape ring = BRepAlgoAPI_Cut(outerCyl, innerCyl).Shape();

    // 合并底板和环形圆柱
    return BRepAlgoAPI_Fuse(base, ring).Shape();
  }
  case cable_clamp_type::LINEAR: {
    // 一字式夹具 - 长条矩形
    // 创建底板
    TopoDS_Shape base =
        BRepPrimAPI_MakeBox(
            gp_Pnt(-(params.diameter + params.thickness * 2) * 1.5,
                   -params.width / 2, 0),
            (params.diameter + params.thickness * 2) * 3, params.width,
            params.thickness)
            .Shape();

    // 创建三个环形圆柱
    double spacing = params.diameter + params.thickness * 2;
    TopoDS_Shape rings;
    for (int i = -1; i <= 1; i++) {
      gp_Pnt center(i * spacing, -params.width / 2,
                    params.thickness + (params.diameter / 2) +
                        params.thickness);
      TopoDS_Shape outerCyl =
          BRepPrimAPI_MakeCylinder(gp_Ax2(center, gp::DY()),
                                   params.diameter / 2 + params.thickness,
                                   params.width)
              .Shape();
      TopoDS_Shape innerCyl =
          BRepPrimAPI_MakeCylinder(gp_Ax2(center, gp::DY()),
                                   params.diameter / 2, params.width)
              .Shape();
      TopoDS_Shape ring = BRepAlgoAPI_Cut(outerCyl, innerCyl).Shape();

      if (rings.IsNull()) {
        rings = ring;
      } else {
        rings = BRepAlgoAPI_Fuse(rings, ring).Shape();
      }
    }

    // 合并底板和环形圆柱
    return BRepAlgoAPI_Fuse(base, rings).Shape();
  }
  case cable_clamp_type::CONTACT_TRIPLE: {
    // 品字接触式 - 底板 + 带三个圆孔的三角形柱
    // 创建底板
    double circleDiameter = params.diameter + params.thickness * 2;
    double sideLength = circleDiameter * (1 + 2.0 / std::sqrt(3));
    double height = std::sqrt(3.0) * sideLength / 2.0;

    TopoDS_Shape base =
        BRepPrimAPI_MakeBox(gp_Pnt(-sideLength / 2, -params.width / 2, 0),
                            sideLength, params.width, params.thickness)
            .Shape();

    // 创建三角形柱
    gp_Pnt p1(0, -params.width / 2, height + params.thickness);
    gp_Pnt p2(-sideLength / 2, -params.width / 2, params.thickness);
    gp_Pnt p3(sideLength / 2, -params.width / 2, params.thickness);

    BRepBuilderAPI_MakePolygon poly;
    poly.Add(p1);
    poly.Add(p2);
    poly.Add(p3);
    poly.Close();
    TopoDS_Face triangleFace = BRepBuilderAPI_MakeFace(poly.Wire()).Face();
    TopoDS_Shape prism =
        BRepPrimAPI_MakePrism(triangleFace, gp_Vec(0, params.width, 0)).Shape();

    // 添加圆角 - 只处理平行于Y轴的边
    BRepFilletAPI_MakeFillet fillet(prism);
    double filletRadius = sideLength * 0.12; // 圆角半径为边长的1/10

    // 获取所有边
    TopExp_Explorer edgeExp(prism, TopAbs_EDGE);
    for (; edgeExp.More(); edgeExp.Next()) {
      TopoDS_Edge edge = TopoDS::Edge(edgeExp.Current());

      // 获取边的两个顶点
      TopoDS_Vertex v1, v2;
      TopExp::Vertices(edge, v1, v2);
      gp_Pnt p1 = BRep_Tool::Pnt(v1);
      gp_Pnt p2 = BRep_Tool::Pnt(v2);

      // 检查边是否平行于Y轴
      if (Abs(p1.X() - p2.X()) < Precision::Confusion() &&
          Abs(p1.Z() - p2.Z()) < Precision::Confusion()) {
        fillet.Add(filletRadius, edge);
      }
    }

    prism = fillet.Shape();

    std::array<gp_Pnt, 3> holePoints;
    double offset = circleDiameter / 2 / std::sqrt(3.0); // 圆心到三角形边的距离
    double holeRadius = params.diameter / 2;

    // 上方圆的圆心 (C1)
    holePoints[0] =
        gp_Pnt(0, -params.width, (3 * offset) + params.thickness * 2);

    // 下方左侧圆的圆心 (C2)
    holePoints[1] = gp_Pnt(-circleDiameter / 2.0 + params.thickness,
                           -params.width, offset + params.thickness * 1.8);

    // 下方右侧圆的圆心 (C3)
    holePoints[2] = gp_Pnt(circleDiameter / 2.0 - params.thickness,
                           -params.width, offset + params.thickness * 1.8);

    // 创建三个圆孔
    gp_Pnt hole1 = holePoints[0];
    gp_Pnt hole2 = holePoints[1];
    gp_Pnt hole3 = holePoints[2];

    TopoDS_Shape holeShape1 =
        BRepPrimAPI_MakeCylinder(gp_Ax2(hole1, gp::DY()), holeRadius,
                                 params.width * 2)
            .Shape();
    TopoDS_Shape holeShape2 =
        BRepPrimAPI_MakeCylinder(gp_Ax2(hole2, gp::DY()), holeRadius,
                                 params.width * 2)
            .Shape();
    TopoDS_Shape holeShape3 =
        BRepPrimAPI_MakeCylinder(gp_Ax2(hole3, gp::DY()), holeRadius,
                                 params.width * 2)
            .Shape();

    TopoDS_Shape withHoles = BRepAlgoAPI_Cut(prism, holeShape1).Shape();
    withHoles = BRepAlgoAPI_Cut(withHoles, holeShape2).Shape();
    withHoles = BRepAlgoAPI_Cut(withHoles, holeShape3).Shape();

    // 合并底板和带孔三角形柱
    return BRepAlgoAPI_Fuse(base, withHoles).Shape();
  }
  case cable_clamp_type::SEPARATE_TRIPLE: {
    // 品字分离式 - 底板 + 三个环形圆柱
    // 品字接触式 - 底板 + 带三个圆孔的三角形柱
    // 创建底板
    double circleDiameter = params.diameter + params.thickness * 2;
    double sideLength = circleDiameter * (1 + 2.0 / std::sqrt(3));
    double height = std::sqrt(3.0) * sideLength / 2.0;

    TopoDS_Shape base =
        BRepPrimAPI_MakeBox(gp_Pnt(-sideLength / 2, -params.width / 2, 0),
                            sideLength, params.width, params.thickness)
            .Shape();

    // 创建三角形柱
    gp_Pnt p1(0, -params.width / 2, height + params.thickness);
    gp_Pnt p2(-sideLength / 2, -params.width / 2, params.thickness);
    gp_Pnt p3(sideLength / 2, -params.width / 2, params.thickness);

    BRepBuilderAPI_MakePolygon poly;
    poly.Add(p1);
    poly.Add(p2);
    poly.Add(p3);
    poly.Close();
    TopoDS_Face triangleFace = BRepBuilderAPI_MakeFace(poly.Wire()).Face();
    TopoDS_Shape prism =
        BRepPrimAPI_MakePrism(triangleFace, gp_Vec(0, params.width, 0)).Shape();

    // 添加圆角 - 只处理平行于Y轴的边
    BRepFilletAPI_MakeFillet fillet(prism);
    double filletRadius = sideLength * 0.12; // 圆角半径为边长的1/10

    // 获取所有边
    TopExp_Explorer edgeExp(prism, TopAbs_EDGE);
    for (; edgeExp.More(); edgeExp.Next()) {
      TopoDS_Edge edge = TopoDS::Edge(edgeExp.Current());

      // 获取边的两个顶点
      TopoDS_Vertex v1, v2;
      TopExp::Vertices(edge, v1, v2);
      gp_Pnt p1 = BRep_Tool::Pnt(v1);
      gp_Pnt p2 = BRep_Tool::Pnt(v2);

      // 检查边是否平行于Y轴
      if (Abs(p1.X() - p2.X()) < Precision::Confusion() &&
          Abs(p1.Z() - p2.Z()) < Precision::Confusion()) {
        fillet.Add(filletRadius, edge);
      }
    }

    prism = fillet.Shape();

    std::array<gp_Pnt, 3> holePoints;
    double offset = circleDiameter / 2 / std::sqrt(3.0); // 圆心到三角形边的距离
    double holeRadius = params.diameter / 2;

    // 上方圆的圆心 (C1)
    holePoints[0] =
        gp_Pnt(0, -params.width, (3 * offset) + params.thickness * 2);

    // 下方左侧圆的圆心 (C2)
    holePoints[1] = gp_Pnt(-circleDiameter / 2.0 + params.thickness / 1.5,
                           -params.width, offset + params.thickness * 1.5);

    // 下方右侧圆的圆心 (C3)
    holePoints[2] = gp_Pnt(circleDiameter / 2.0 - params.thickness / 1.5,
                           -params.width, offset + params.thickness * 1.5);

    // 创建三个圆孔
    gp_Pnt hole1 = holePoints[0];
    gp_Pnt hole2 = holePoints[1];
    gp_Pnt hole3 = holePoints[2];

    TopoDS_Shape holeShape1 =
        BRepPrimAPI_MakeCylinder(gp_Ax2(hole1, gp::DY()), holeRadius,
                                 params.width * 2)
            .Shape();
    TopoDS_Shape holeShape2 =
        BRepPrimAPI_MakeCylinder(gp_Ax2(hole2, gp::DY()), holeRadius,
                                 params.width * 2)
            .Shape();
    TopoDS_Shape holeShape3 =
        BRepPrimAPI_MakeCylinder(gp_Ax2(hole3, gp::DY()), holeRadius,
                                 params.width * 2)
            .Shape();

    TopoDS_Shape withHoles = BRepAlgoAPI_Cut(prism, holeShape1).Shape();
    withHoles = BRepAlgoAPI_Cut(withHoles, holeShape2).Shape();
    withHoles = BRepAlgoAPI_Cut(withHoles, holeShape3).Shape();

    // 合并底板和带孔三角形柱
    return BRepAlgoAPI_Fuse(base, withHoles).Shape();
  }
  default:
    throw Standard_ConstructionError("Unknown cable clamp type");
  }
}


TopoDS_Shape create_cable_clamp(const cable_clamp_params &params,
                                const gp_Pnt &position, const gp_Dir &normal,
                                const gp_Dir &xDir) {
  // 首先创建标准方向的夹具
  TopoDS_Shape clamp = create_cable_clamp(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, normal, xDir);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(clamp, transformation);
  return transform.Shape();
}


TopoDS_Shape create_cable_pole(const cable_pole_params &params) {
  // 参数验证
  if (params.length <= 0)
    throw Standard_ConstructionError("Pole length must be positive");
  if (params.width <= 0)
    throw Standard_ConstructionError("Pole width must be positive");
  if (params.thickness <= 0)
    throw Standard_ConstructionError("Pole thickness must be positive");
  if (params.thickness >= params.width / 2)
    throw Standard_ConstructionError("Thickness must be less than half width");
  if (params.fixedLegLength < 0)
    throw Standard_ConstructionError("Fixed leg length must be non-negative");
  if (params.fixedLegWidth < 0)
    throw Standard_ConstructionError("Fixed leg width must be non-negative");

  TopoDS_Shape pole;

  // 创建立柱主体
  if (params.radius > 0) {
    // 圆弧立柱
    if (params.arcAngle <= 0 || params.arcAngle > 2 * M_PI)
      throw Standard_ConstructionError("Arc angle must be in (0, 2PI]");

    // 创建圆弧路径
    gp_Ax2 arcAxis(gp_Pnt(0, 0, params.radius), gp_Dir(0, -1, 0));
    gp_Circ arc(arcAxis, params.radius);
    Handle(Geom_Curve) circle = new Geom_Circle(arc);
    TopoDS_Edge path =
        BRepBuilderAPI_MakeEdge(circle, 0, params.arcAngle).Edge();

    // 显式构建路径Wire并检查闭合性
    BRepBuilderAPI_MakeWire wireMaker;
    wireMaker.Add(path);
    if (!wireMaker.IsDone()) {
      throw Standard_ConstructionError("Failed to create arc path wire");
    }
    TopoDS_Wire wire = wireMaker.Wire();

    // 创建矩形截面
    gp_Pnt p1(0, -params.width / 2, 0);
    gp_Pnt p2(0, -params.width / 2, params.thickness);
    gp_Pnt p3(0, params.width / 2, params.thickness);
    gp_Pnt p4(0, params.width / 2, 0);
    TopoDS_Wire profile =
        BRepBuilderAPI_MakePolygon(p1, p2, p3, p4, Standard_True).Wire();

    // 扫掠成圆弧立柱
    BRepOffsetAPI_MakePipeShell pipeMaker(wire);
    pipeMaker.Add(profile);
    pipeMaker.SetMode(Standard_True);
    pipeMaker.SetTolerance(1e-6); // 设置更高精度
    pipeMaker.Build();

    // 添加详细错误检查
    if (!pipeMaker.IsDone()) {
      std::string msg = "PipeShell error: ";
      switch (pipeMaker.GetStatus()) {
      case BRepBuilderAPI_PlaneNotIntersectGuide:
        msg += "Profile plane does not intersect guide";
        break;
      default:
        msg += "Unknown error";
        break;
      }
      throw Standard_ConstructionError(msg.c_str());
    }
    if (!pipeMaker.MakeSolid()) {
      throw std::runtime_error("Failed to create a solid object from sweep");
    }

    pole = pipeMaker.Shape();
  } else {
    // 直立柱
    gp_Pnt p1(-params.width / 2, -params.thickness / 2, 0);
    gp_Pnt p2(-params.width / 2, params.thickness / 2, 0);
    gp_Pnt p3(params.width / 2, params.thickness / 2, 0);
    gp_Pnt p4(params.width / 2, -params.thickness / 2, 0);
    TopoDS_Face face = BRepBuilderAPI_MakeFace(
        BRepBuilderAPI_MakePolygon(p1, p2, p3, p4, Standard_True).Wire());
    pole = BRepPrimAPI_MakePrism(face, gp_Vec(0, 0, params.length)).Shape();
  }

  BRep_Builder builder;
  TopoDS_Compound compound;
  builder.MakeCompound(compound);
  builder.Add(compound, pole);

  // 创建固定肢
  if (params.fixedLegLength > 0 && params.fixedLegWidth > 0) {
    for (const auto &point : params.mountPoints) {
      if (params.radius > 0) {
        // 计算安装点处的径向方向
        gp_Vec radialDir(point.X(), 0, point.Z() - params.radius);
        if (radialDir.Magnitude() < Precision::Confusion()) {
          throw Standard_ConstructionError(
              "Mount point coincides with circle center");
        }
        radialDir.Normalize();

        // 计算切线方向（与径向垂直且沿圆弧方向）
        gp_Vec tangentDir = radialDir.Crossed(gp_Vec(0, 1, 0));
        tangentDir.Normalize();

        // 确定延伸方向（根据是否需要向外延伸）
        bool isOuterSide = (point.X() * radialDir.X() +
                            (point.Z() - params.radius) * radialDir.Z()) > 0;
        double extension = isOuterSide ? 1.0 : -1.0;
        double fixedThickness = params.thickness / 2;

        // 构建固定肢截面（在切线-Y平面）
        gp_Pnt basePoint = gp_Pnt(point.X(), point.Y(), point.Z());
        double halfLength = params.fixedLegLength / 2;
        double halfThick = fixedThickness / 2;
        double halfWidth = params.fixedLegWidth / 2;

        // 截面点计算（矩形截面）
        gp_Pnt p1 = basePoint.Translated(tangentDir * (-halfWidth) +
                                         radialDir * (-fixedThickness) +
                                         gp_Vec(0, -halfLength, 0));
        gp_Pnt p2 = basePoint.Translated(tangentDir * (halfWidth) +
                                         radialDir * (-fixedThickness) +
                                         gp_Vec(0, -halfLength, 0));
        gp_Pnt p3 =
            basePoint.Translated(tangentDir * (halfWidth) + radialDir * (0) +
                                 gp_Vec(0, -halfLength, 0));
        gp_Pnt p4 =
            basePoint.Translated(tangentDir * (-halfWidth) + radialDir * (0) +
                                 gp_Vec(0, -halfLength, 0));

        gp_Vec extrudeDir = gp_Vec(0, extension, 0) * params.fixedLegLength;

        // 修正3：调整挤出方向为Y轴方向
        TopoDS_Shape leg =
            BRepPrimAPI_MakePrism(
                BRepBuilderAPI_MakeFace(
                    BRepBuilderAPI_MakePolygon(p1, p2, p3, p4, Standard_True)),
                extrudeDir // Y方向挤出厚度
                )
                .Shape();

        // 修正4：安装孔位置调整到固定肢中心
        gp_Pnt holeCenter =
            basePoint.Translated(radialDir * (-params.thickness));
        TopoDS_Shape hole = BRepPrimAPI_MakeCylinder(
                                gp_Ax2(holeCenter, radialDir),
                                params.fixedLegWidth / 4, params.thickness * 2)
                                .Shape();

        // 布尔运算切割孔洞
        leg = BRepAlgoAPI_Cut(leg, hole).Shape();

        builder.Add(compound, leg);
      } else {
        // 判断安装点在立柱的哪一侧
        bool isRightSide = point.X() > 0;
        double legDirection = isRightSide ? 1.0 : -1.0;

        double fixedThickness = params.thickness / 2;

        // 创建固定肢矩形
        gp_Pnt p1(point.X() + legDirection * params.fixedLegLength / 2,
                  point.Y() - fixedThickness / 2,
                  point.Z() - params.fixedLegWidth / 2);
        gp_Pnt p2(point.X() - legDirection * params.fixedLegLength / 2,
                  point.Y() - fixedThickness / 2,
                  point.Z() - params.fixedLegWidth / 2);
        gp_Pnt p3(point.X() - legDirection * params.fixedLegLength / 2,
                  point.Y() + fixedThickness / 2,
                  point.Z() - params.fixedLegWidth / 2);
        gp_Pnt p4(point.X() + legDirection * params.fixedLegLength / 2,
                  point.Y() + fixedThickness / 2,
                  point.Z() - params.fixedLegWidth / 2);

        TopoDS_Face legFace = BRepBuilderAPI_MakeFace(
            BRepBuilderAPI_MakePolygon(p1, p2, p3, p4, Standard_True).Wire());
        TopoDS_Shape leg =
            BRepPrimAPI_MakePrism(legFace, gp_Vec(0, 0, params.fixedLegWidth))
                .Shape();

        // 合并到主体
        leg = BRepAlgoAPI_Fuse(pole, leg).Shape();

        // 创建安装孔
        gp_Pnt holePos(point.X(), point.Y() - params.thickness, point.Z());
        TopoDS_Shape hole = BRepPrimAPI_MakeCylinder(gp_Ax2(holePos, gp::DY()),
                                                     params.fixedLegWidth / 4,
                                                     params.thickness * 2)
                                .Shape();
        leg = BRepAlgoAPI_Cut(leg, hole).Shape();

        builder.Add(compound, leg);
      }
    }
  }

  return compound;
}


TopoDS_Shape create_cable_pole(const cable_pole_params &params,
                               const gp_Pnt &position,
                               const gp_Dir &direction) {
  // 创建标准方向的立柱
  TopoDS_Shape pole = create_cable_pole(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ());
  gp_Ax3 targetAx3(position, direction);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(pole, transformation);
  return transform.Shape();
}


TopoDS_Shape create_ground_flat_iron(const ground_flat_iron_params &params) {
  // 参数验证
  if (params.length <= 0)
    throw Standard_ConstructionError("Length must be positive");
  if (params.height <= 0)
    throw Standard_ConstructionError("Height must be positive");
  if (params.thickness <= 0)
    throw Standard_ConstructionError("Thickness must be positive");
  if (params.thickness >= params.height)
    throw Standard_ConstructionError("Thickness must be less than height");

  // 创建扁铁截面轮廓
  gp_Pnt p1(-params.length / 2, -params.height / 2, 0);
  gp_Pnt p2(params.length / 2, -params.height / 2, 0);
  gp_Pnt p3(params.length / 2, params.height / 2, 0);
  gp_Pnt p4(-params.length / 2, params.height / 2, 0);

  BRepBuilderAPI_MakePolygon polyMaker;
  polyMaker.Add(p1);
  polyMaker.Add(p2);
  polyMaker.Add(p3);
  polyMaker.Add(p4);
  polyMaker.Add(p1);
  TopoDS_Wire wire = polyMaker.Wire();

  // 创建扁铁实体
  TopoDS_Face face = BRepBuilderAPI_MakeFace(wire).Face();
  TopoDS_Shape flatIron =
      BRepPrimAPI_MakePrism(face, gp_Vec(0, 0, params.thickness)).Shape();

  return flatIron;
}


TopoDS_Shape create_ground_flat_iron(const ground_flat_iron_params &params,
                                     const gp_Pnt &position,
                                     const gp_Dir &normal, const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(normal.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Normal and direction must be perpendicular");
  }

  // 创建标准方向的扁铁
  TopoDS_Shape flatIron = create_ground_flat_iron(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, normal, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(flatIron, transformation);
  return transform.Shape();
}


TopoDS_Shape create_embedded_part(const embedded_part_params &params) {
  // 参数验证
  if (params.length <= 0)
    throw Standard_ConstructionError("Length must be positive");
  if (params.radius <= 0)
    throw Standard_ConstructionError("Radius must be positive");
  if (params.height <= 0)
    throw Standard_ConstructionError("Height must be positive");
  if (params.materialRadius <= 0)
    throw Standard_ConstructionError("Material radius must be positive");
  if (params.lowerLength <= 0)
    throw Standard_ConstructionError("Lower length must be positive");
  if (params.materialRadius >= params.radius)
    throw Standard_ConstructionError(
        "Material radius must be less than hook radius");

  // 创建伸部分
  gp_Pnt pathStart(0, 0, -params.height);
  gp_Pnt pathMid(0, 0, 0);              // 路径起点
  gp_Pnt arcStart(params.length, 0, 0); // 路径终点

  gp_Pnt arcEnd(arcStart.X(), arcStart.Y(), arcStart.Z() - params.radius * 2);
  gp_Pnt arcCenter(arcStart.X() + params.radius, arcStart.Y(),
                   arcStart.Z() - params.radius);
  gp_Pnt pathEnd(arcEnd.X() - params.lowerLength, arcEnd.Y(),
                 arcEnd.Z()); // 路径终点

  TopoDS_Edge edge1 = BRepBuilderAPI_MakeEdge(pathStart, pathMid).Edge();
  TopoDS_Edge edge2 = BRepBuilderAPI_MakeEdge(pathMid, arcStart).Edge();
  Handle(Geom_TrimmedCurve) arc =
      GC_MakeArcOfCircle(arcStart, arcCenter, arcEnd).Value();
  TopoDS_Edge arcEdge = BRepBuilderAPI_MakeEdge(arc).Edge();
  TopoDS_Edge edge3 = BRepBuilderAPI_MakeEdge(arcEnd, pathEnd).Edge();

  BRepBuilderAPI_MakeWire wireMaker(edge1, edge2);
  wireMaker.Add(arcEdge);
  wireMaker.Add(edge3);
  TopoDS_Wire pathWire = wireMaker.Wire();

  // 创建圆形截面（与圆柱相同半径）
  gp_Ax2 sectionAxis(pathStart, gp_Dir(0, 0, -1));
  BRepBuilderAPI_MakeWire circleMaker;
  circleMaker.Add(
      BRepBuilderAPI_MakeEdge(gp_Circ(sectionAxis, params.materialRadius))
          .Edge());
  TopoDS_Wire sectionWire = circleMaker.Wire();

  // 沿路径扫掠生成水平延伸
  BRepOffsetAPI_MakePipeShell pipeMaker(pathWire);
  pipeMaker.Add(sectionWire);
  pipeMaker.SetMode(Standard_True);
  pipeMaker.SetTransitionMode(BRepBuilderAPI_RightCorner);
  pipeMaker.Build();
  if (!pipeMaker.IsDone()) {
    throw std::runtime_error("Failed to create a solid object from sweep");
  }
  if (!pipeMaker.MakeSolid()) {
    throw std::runtime_error("Failed to create a solid object from sweep");
  }

  return pipeMaker.Shape();
}


TopoDS_Shape create_embedded_part(const embedded_part_params &params,
                                  const gp_Pnt &position, const gp_Dir &normal,
                                  const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(normal.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Normal and direction must be perpendicular");
  }

  // 创建标准方向的预埋件
  TopoDS_Shape embeddedPart = create_embedded_part(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, normal, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(embeddedPart, transformation);
  return transform.Shape();
}


TopoDS_Shape create_lifting_eye(const lifting_eye_params &params) {
  // 参数验证
  if (params.height <= 0)
    throw Standard_ConstructionError("Height must be positive");
  if (params.ringRadius <= 0)
    throw Standard_ConstructionError("Ring radius must be positive");
  if (params.pipeDiameter <= 0)
    throw Standard_ConstructionError("Pipe diameter must be positive");
  if (params.pipeDiameter >= 2 * params.ringRadius)
    throw Standard_ConstructionError(
        "Pipe diameter must be less than ring diameter");

  // 创建吊臂部分（垂直圆柱）
  gp_Ax2 armAxis(gp_Pnt(0, 0, -params.height), gp::DZ());
  TopoDS_Shape arm =
      BRepPrimAPI_MakeCylinder(armAxis, params.pipeDiameter / 2, params.height)
          .Shape();

  // 创建圆环部分
  gp_Ax2 ringAxis(gp_Pnt(0, 0, -params.height - params.ringRadius), gp::DX());
  TopoDS_Shape ring = BRepPrimAPI_MakeTorus(ringAxis, params.ringRadius,
                                            params.pipeDiameter / 2)
                          .Shape();

  // 合并吊臂和圆环
  TopoDS_Shape liftingEye = BRepAlgoAPI_Fuse(arm, ring).Shape();

  return liftingEye;
}


TopoDS_Shape create_lifting_eye(const lifting_eye_params &params,
                                const gp_Pnt &position, const gp_Dir &normal,
                                const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(normal.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Normal and direction must be perpendicular");
  }

  // 创建标准方向的吊攀
  TopoDS_Shape liftingEye = create_lifting_eye(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, normal, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(liftingEye, transformation);
  return transform.Shape();
}


/**
 * @brief 创建矩形截面连接段
 * @param length 长度（X方向）
 * @param width 宽度（Y方向）
 * @param height 高度（Z方向）
 * @param wallThickness 壁厚
 * @param isOuter 是否创建外壁
 * @return TopoDS_Shape 连接段形状
 */
TopoDS_Shape create_rectangular_section(double length, double width,
                                        double height, double wallThickness,
                                        double topThickness,
                                        double bottomThickness, bool isOuter) {
  double halfWidth = width / 2;
  double heightOffset = 0;
  double realHeight = height;

  if (isOuter) {
    halfWidth += wallThickness;
    heightOffset = -bottomThickness;
    realHeight += topThickness + bottomThickness;
  }

  gp_Pnt p1(0, -halfWidth, heightOffset);
  gp_Pnt p2(length, -halfWidth, heightOffset);
  gp_Pnt p3(length, halfWidth, heightOffset);
  gp_Pnt p4(0, halfWidth, heightOffset);

  BRepBuilderAPI_MakeWire wireMaker;
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p1, p2));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p2, p3));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p3, p4));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p4, p1));

  TopoDS_Face face = BRepBuilderAPI_MakeFace(wireMaker.Wire());
  gp_Vec vec(0, 0, realHeight);
  return BRepPrimAPI_MakePrism(face, vec).Shape();
}


/**
 * @brief 创建圆形截面连接段
 * @param length 长度（X方向）
 * @param radius 半径
 * @param wallThickness 壁厚
 * @param isOuter 是否创建外壁
 * @return TopoDS_Shape 连接段形状
 */
TopoDS_Shape create_circular_section(double length, double radius,
                                     double wallThickness, bool isOuter) {
  double actualRadius = isOuter ? radius + wallThickness : radius;

  gp_Ax2 axis(gp_Pnt(0, 0, radius), gp_Dir(1, 0, 0));
  TopoDS_Shape cylinder =
      BRepPrimAPI_MakeCylinder(axis, actualRadius, length).Shape();
  return cylinder;
}


/**
 * @brief 创建马蹄形截面连接段
 * @param length 长度（X方向）
 * @param width 宽度（Y方向）
 * @param height 高度（Z方向）
 * @param arcHeight 拱高
 * @param wallThickness 壁厚
 * @param isOuter 是否创建外壁
 * @return TopoDS_Shape 连接段形状
 */
TopoDS_Shape create_horseshoe_section(double length, double width,
                                      double height, double arcHeight,
                                      double wallThickness, bool isOuter) {
  // 计算尺寸参数
  double halfWidth = width / 2.0;
  double baseHeight = height - arcHeight;
  double heightOffset = 0;

  if (isOuter) {
    halfWidth += wallThickness;
    baseHeight += wallThickness;
    arcHeight += wallThickness;
    heightOffset = -wallThickness;
  }

  // 创建截面轮廓线
  BRepBuilderAPI_MakeWire sectionWire;

  // 底部直线段
  gp_Pnt p1(0, -halfWidth, heightOffset);
  gp_Pnt p2(0, halfWidth, heightOffset);
  sectionWire.Add(BRepBuilderAPI_MakeEdge(p1, p2));

  // 右侧垂直线段
  gp_Pnt p3(0, halfWidth, baseHeight + heightOffset);
  sectionWire.Add(BRepBuilderAPI_MakeEdge(p2, p3));

  // 顶部圆弧 (使用三点构造圆弧)
  gp_Pnt arcStart(0, halfWidth, baseHeight + heightOffset);
  gp_Pnt arcMid(0, 0, baseHeight + arcHeight + heightOffset); // 拱顶中点
  gp_Pnt arcEnd(0, -halfWidth, baseHeight + heightOffset);

  Handle(Geom_TrimmedCurve) topArc =
      GC_MakeArcOfCircle(arcStart, arcMid, arcEnd).Value();
  sectionWire.Add(BRepBuilderAPI_MakeEdge(topArc));

  // 左侧垂直线段
  gp_Pnt p4(0, -halfWidth, heightOffset);
  sectionWire.Add(BRepBuilderAPI_MakeEdge(arcEnd, p4));

  // 创建面并拉伸
  TopoDS_Face sectionFace = BRepBuilderAPI_MakeFace(sectionWire.Wire());
  return BRepPrimAPI_MakePrism(sectionFace, gp_Vec(length, 0, 0)).Shape();
}


/**
 * @brief 创建直线井
 * @param params 井参数
 * @return TopoDS_Shape 井形状
 */
TopoDS_Shape create_straight_well(const tunnel_well_params &params) {
  // 1. 创建垫层
  double cushionTotalWidth =
      params.width + 2 * (params.outerWallThickness + params.cushionExtension);
  double cushionTotalLength =
      params.length + 2 * (params.outerWallThickness + params.cushionExtension);

  TopoDS_Shape cushion =
      BRepPrimAPI_MakeBox(
          gp_Pnt(-cushionTotalLength / 2, -cushionTotalWidth / 2,
                 -params.cushionThickness - params.bottomThickness),
          cushionTotalLength, cushionTotalWidth, params.cushionThickness)
          .Shape();

  // 2. 创建井身外壁
  double outerLength = params.length + 2 * params.outerWallThickness;
  double outerWidth = params.width + 2 * params.outerWallThickness;
  double outerHeight =
      params.height + params.topThickness + params.bottomThickness;

  TopoDS_Shape outerWell =
      BRepPrimAPI_MakeBox(
          gp_Pnt(-outerLength / 2, -outerWidth / 2, -params.bottomThickness),
          outerLength, outerWidth, outerHeight)
          .Shape();

  // 3. 创建井身内腔
  TopoDS_Shape innerWell =
      BRepPrimAPI_MakeBox(gp_Pnt(-params.length, -params.width / 2, 0),
                          params.length * 2, params.width, params.height)
          .Shape();

  // 4. 从外壁中减去内腔
  TopoDS_Shape well = BRepAlgoAPI_Cut(outerWell, innerWell).Shape();

  // 5. 合并垫层和井身
  return BRepAlgoAPI_Fuse(cushion, well).Shape();
}


TopoDS_Shape create_straight_tunnel_well(const tunnel_well_params &params) {
  // 参数验证
  if (params.length <= 0 || params.width <= 0 || params.height <= 0) {
    throw Standard_ConstructionError("Well dimensions must be positive");
  }
  if (params.topThickness < 0 || params.bottomThickness < 0) {
    throw Standard_ConstructionError("Thickness must be non-negative");
  }
  TopoDS_Shape result;

  // 2. 创建左连接段
  TopoDS_Shape leftTunnel;
  switch (params.leftSectionType) {
  case connection_section_style::RECTANGULAR:
    leftTunnel = create_rectangular_section(
        params.leftLength, params.leftWidth, params.leftHeight,
        params.outerWallThickness, params.outerWallThickness,
        params.outerWallThickness, true);
    break;
  case connection_section_style::HORSESHOE:
    leftTunnel = create_horseshoe_section(
        params.leftLength, params.leftWidth, params.leftHeight,
        params.leftArcHeight, params.outerWallThickness, true);
    break;
  case connection_section_style::CIRCULAR:
    leftTunnel =
        create_circular_section(params.leftLength, params.leftHeight / 2,
                                params.outerWallThickness, true);
    break;
  }

  // 移动左连接段到正确位置
  gp_Trsf leftTrsf;
  leftTrsf.SetTranslation(gp_Vec(
      -params.leftLength - params.radius - params.outerWallThickness, 0, 0));
  leftTunnel = BRepBuilderAPI_Transform(leftTunnel, leftTrsf).Shape();

  // 3. 创建右连接段
  TopoDS_Shape rightTunnel;
  switch (params.rightSectionType) {
  case connection_section_style::RECTANGULAR:
    rightTunnel = create_rectangular_section(
        params.rightLength, params.rightWidth, params.rightHeight,
        params.outerWallThickness, params.outerWallThickness,
        params.outerWallThickness, true);
    break;
  case connection_section_style::HORSESHOE:
    rightTunnel = create_horseshoe_section(
        params.rightLength, params.rightWidth, params.rightHeight,
        params.rightArcHeight, params.outerWallThickness, true);
    break;
  case connection_section_style::CIRCULAR:
    rightTunnel =
        create_circular_section(params.rightLength, params.rightHeight / 2,
                                params.outerWallThickness, true);
    break;
  }

  // 移动右连接段到正确位置
  gp_Trsf rightTrsf;
  rightTrsf.SetTranslation(
      gp_Vec(params.radius + params.outerWallThickness, 0, 0));
  rightTunnel = BRepBuilderAPI_Transform(rightTunnel, rightTrsf).Shape();

  // 5. 合并所有部分
  TopoDS_Shape tunnel = BRepAlgoAPI_Fuse(leftTunnel, rightTunnel).Shape();

  // 6. 创建内腔
  TopoDS_Shape innerTunnel;
  switch (params.leftSectionType) {
  case connection_section_style::RECTANGULAR:
    innerTunnel = create_rectangular_section(
        params.leftLength, params.leftWidth, params.leftHeight,
        params.outerWallThickness, params.outerWallThickness,
        params.outerWallThickness, false);
    break;
  case connection_section_style::HORSESHOE:
    innerTunnel = create_horseshoe_section(
        params.leftLength, params.leftWidth, params.leftHeight,
        params.leftArcHeight, params.outerWallThickness, false);
    break;
  case connection_section_style::CIRCULAR:
    innerTunnel =
        create_circular_section(params.leftLength, params.leftHeight / 2,
                                params.outerWallThickness, false);
    break;
  }

  innerTunnel = BRepBuilderAPI_Transform(innerTunnel, leftTrsf).Shape();

  TopoDS_Shape innerRightTunnel;
  switch (params.rightSectionType) {
  case connection_section_style::RECTANGULAR:
    innerRightTunnel = create_rectangular_section(
        params.rightLength, params.rightWidth, params.rightHeight,
        params.outerWallThickness, params.outerWallThickness,
        params.outerWallThickness, false);
    break;
  case connection_section_style::HORSESHOE:
    innerRightTunnel = create_horseshoe_section(
        params.rightLength, params.rightWidth, params.rightHeight,
        params.rightArcHeight, params.outerWallThickness, false);
    break;
  case connection_section_style::CIRCULAR:
    innerRightTunnel =
        create_circular_section(params.rightLength, params.rightHeight / 2,
                                params.outerWallThickness, false);
    break;
  }

  innerRightTunnel =
      BRepBuilderAPI_Transform(innerRightTunnel, rightTrsf).Shape();

  TopoDS_Shape innerShape =
      BRepAlgoAPI_Fuse(innerTunnel, innerRightTunnel).Shape();

  // 7. 从外壁中减去内腔
  TopoDS_Shape well = BRepAlgoAPI_Cut(tunnel, innerShape).Shape();

  {
    // 创建过渡段
    TopoDS_Shape transition = create_transition_section(params, true);
    TopoDS_Shape innerTransition = create_transition_section(params, false);

    // 4. 创建竖井段
    double wellOuterRadius = params.radius + params.outerWallThickness;
    double wellHeight =
        params.height + params.topThickness + params.bottomThickness;

    gp_Ax2 axis(gp_Pnt(0, 0, params.outerWallThickness), gp_Dir(0, 0, 1));

    TopoDS_Shape outerCylinder =
        BRepPrimAPI_MakeCylinder(axis, wellOuterRadius, wellHeight).Shape();

    TopoDS_Shape innerCylinder =
        BRepPrimAPI_MakeCylinder(axis, params.radius, params.height * 2)
            .Shape();
    transition = BRepAlgoAPI_Fuse(transition, outerCylinder).Shape();
    transition = BRepAlgoAPI_Cut(transition, innerTransition).Shape();
    transition = BRepAlgoAPI_Cut(transition, innerCylinder).Shape();

    well = BRepAlgoAPI_Fuse(well, transition).Shape();
  }
  // 8. 合并垫层和井身
  return well;
}


/**
 * @brief 创建隧道井
 * @param params 井参数
 * @return TopoDS_Shape 井形状
 */
TopoDS_Shape create_tunnel_well(const tunnel_well_params &params) {
  switch (params.type) {
  case tunnel_well_type::STRAIGHT:
    return create_straight_well(params);
  case tunnel_well_type::STRAIGHT_TUNNEL:
    return create_straight_tunnel_well(params);
  default:
    return TopoDS_Shape(); // 返回空形状
  }
}


TopoDS_Shape create_tunnel_well(const tunnel_well_params &params,
                                const gp_Pnt &position, const gp_Dir &direction,
                                const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(direction.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Direction and xDir must be perpendicular");
  }

  // 创建标准方向的井
  TopoDS_Shape well = create_tunnel_well(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, direction, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(well, transformation);
  return transform.Shape();
}


TopoDS_Shape create_corner_well(double leftLength, double rightLength,
                                double baseZ, double realHeight,
                                const gp_Pnt &arcCenter_, double outerRadius,
                                double innerRadius, double theta) {
  gp_Pnt arcCenter(arcCenter_.X(), arcCenter_.Y(), baseZ);
  double startAngle = M_PI / 2;
  double endAngle = M_PI - (2 * theta) + M_PI / 2;
  // 关键点计算
  gp_Pnt outerStart = ElCLib::CircleValue(
      startAngle, gp_Ax2(arcCenter, gp_Dir(0, 0, -1)), outerRadius);
  outerStart.SetZ(baseZ);
  gp_Pnt outerEnd = ElCLib::CircleValue(
      endAngle, gp_Ax2(arcCenter, gp_Dir(0, 0, -1)), outerRadius);
  outerEnd.SetZ(baseZ);
  gp_Pnt innerStart = ElCLib::CircleValue(
      startAngle, gp_Ax2(arcCenter, gp_Dir(0, 0, -1)), innerRadius);
  outerEnd.SetZ(baseZ);
  gp_Pnt innerEnd = ElCLib::CircleValue(
      endAngle, gp_Ax2(arcCenter, gp_Dir(0, 0, -1)), innerRadius);
  innerEnd.SetZ(baseZ);

  // 计算连接段端点
  gp_Pnt leftOuterStart =
      gp_Pnt(outerStart.X() - leftLength, outerStart.Y(), outerStart.Z());
  gp_Pnt leftInnerStart =
      gp_Pnt(innerStart.X() - leftLength, innerStart.Y(), innerStart.Z());

  gp_Vec segmentVec(gp_Vec(innerEnd, outerEnd));
  gp_Vec rightDir(segmentVec.Y(), -segmentVec.X(), 0.0);
  rightDir.Normalize();

  gp_Pnt rightOuterEnd = outerEnd.Translated(rightDir * (rightLength));
  gp_Pnt rightInnerEnd = innerEnd.Translated(rightDir * (rightLength));

  // 创建弧形段
  Handle(Geom_Circle) outerArc =
      new Geom_Circle(gp_Ax2(arcCenter, gp_Dir(0, 0, -1)), outerRadius);
  TopoDS_Edge outerEdge =
      BRepBuilderAPI_MakeEdge(outerArc, startAngle, endAngle).Edge();

  Handle(Geom_Circle) innerArc =
      new Geom_Circle(gp_Ax2(arcCenter, gp_Dir(0, 0, -1)), innerRadius);
  TopoDS_Edge innerEdge =
      BRepBuilderAPI_MakeEdge(innerArc, startAngle, endAngle).Edge();
  innerEdge.Reverse();

  // 创建弧形段外轮廓
  BRepBuilderAPI_MakeWire outerWire;
  outerWire.Add(outerEdge);
  outerWire.Add(BRepBuilderAPI_MakeEdge(outerEnd, innerEnd).Edge());
  outerWire.Add(innerEdge);
  outerWire.Add(BRepBuilderAPI_MakeEdge(innerStart, outerStart).Edge());
  TopoDS_Face arcFace = BRepBuilderAPI_MakeFace(outerWire.Wire()).Face();

  // 创建左连接段
  BRepBuilderAPI_MakeWire leftWire;
  leftWire.Add(BRepBuilderAPI_MakeEdge(leftOuterStart, outerStart).Edge());
  leftWire.Add(BRepBuilderAPI_MakeEdge(outerStart, innerStart).Edge());
  leftWire.Add(BRepBuilderAPI_MakeEdge(innerStart, leftInnerStart).Edge());
  leftWire.Add(BRepBuilderAPI_MakeEdge(leftInnerStart, leftOuterStart).Edge());
  TopoDS_Face leftFace = BRepBuilderAPI_MakeFace(leftWire.Wire()).Face();

  // 创建右连接段
  BRepBuilderAPI_MakeWire rightWire;
  rightWire.Add(BRepBuilderAPI_MakeEdge(outerEnd, rightOuterEnd).Edge());
  rightWire.Add(BRepBuilderAPI_MakeEdge(rightOuterEnd, rightInnerEnd).Edge());
  rightWire.Add(BRepBuilderAPI_MakeEdge(rightInnerEnd, innerEnd).Edge());
  rightWire.Add(BRepBuilderAPI_MakeEdge(innerEnd, outerEnd).Edge());
  TopoDS_Face rightFace = BRepBuilderAPI_MakeFace(rightWire.Wire()).Face();

  // 拉伸所有部分
  TopoDS_Shape arcOuter =
      BRepPrimAPI_MakePrism(arcFace, gp_Vec(0, 0, realHeight)).Shape();
  TopoDS_Shape leftOuter =
      BRepPrimAPI_MakePrism(leftFace, gp_Vec(0, 0, realHeight)).Shape();
  TopoDS_Shape rightOuter =
      BRepPrimAPI_MakePrism(rightFace, gp_Vec(0, 0, realHeight)).Shape();

  // 合并所有部分
  TopoDS_Shape outer = BRepAlgoAPI_Fuse(arcOuter, leftOuter).Shape();
  outer = BRepAlgoAPI_Fuse(outer, rightOuter).Shape();

  return outer;
}


TopoDS_Shape create_corner_well(const corner_well_params &params) {
  if (params.cornerRadius <= 0 || params.width <= 0 || params.height <= 0 ||
      params.angle <= 0) {
    throw Standard_ConstructionError(
        "Corner radius, width, height, and angle must be positive");
  }

  const double R = params.cornerRadius + params.width / 2;
  const double theta = params.angle * M_PI / 180.0 / 2; // 转换为半角弧度

  // 圆心坐标计算
  const double arcCenterX = -R * sin(theta); // X轴负方向
  const double arcCenterY = -R * cos(theta); // Y轴负方向
  gp_Pnt arcCenter(arcCenterX, arcCenterY, 0);

  // 外轮廓参数
  double outerRadius =
      params.cornerRadius + params.width + params.wallThickness;
  double innerRadius = params.cornerRadius - params.wallThickness;

  TopoDS_Shape outer = create_corner_well(
      params.leftLength + params.wallThickness,
      params.rightLength + params.wallThickness, -params.bottomThickness,
      params.height + params.topThickness + params.bottomThickness, arcCenter,
      outerRadius, innerRadius, theta);

  // 外轮廓参数
  outerRadius = params.cornerRadius + params.width;
  innerRadius = params.cornerRadius;

  TopoDS_Shape inner = create_corner_well(
      params.leftLength + params.wallThickness,
      params.rightLength + params.wallThickness, 0, params.height, arcCenter,
      outerRadius, innerRadius, theta);

  // 外轮廓参数
  outerRadius = params.cornerRadius + params.width + params.wallThickness +
                params.cushionExtension;
  innerRadius =
      params.cornerRadius - params.wallThickness - params.cushionExtension;

  TopoDS_Shape cushion = create_corner_well(
      params.leftLength + params.wallThickness + params.cushionExtension,
      params.rightLength + params.wallThickness + params.cushionExtension,
      -params.bottomThickness - params.cushionThickness,
      params.cushionThickness, arcCenter, outerRadius, innerRadius, theta);

  // 合并所有部分
  TopoDS_Shape well = BRepAlgoAPI_Cut(outer, inner).Shape();
  well = BRepAlgoAPI_Fuse(well, cushion).Shape();

  return well;
}


TopoDS_Shape create_corner_well(const corner_well_params &params,
                                const gp_Pnt &position, const gp_Dir &direction,
                                const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(direction.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Direction and xDir must be perpendicular");
  }

  // 创建标准方向的转角井
  TopoDS_Shape well = create_corner_well(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, direction, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(well, transformation);
  return transform.Shape();
}


/**
 * @brief 创建直角三通圆角工作井
 * @param length 直通段长度(mm)
 * @param width 直通段宽度(mm)
 * @param height 直通段高度(mm)
 * @param length1 支线段长度(mm)
 * @param width1 支线段宽度(mm)
 * @param cornerRadius 井转角半径(mm)
 * @return 直角三通圆角工作井的形状
 */
TopoDS_Shape create_three_way_round_working_well_part(
    double length, double width, double height, double length1, double width1,
    double cornerRadius, double zoffset) {
  // 参数校验
  if (length <= 0 || width <= 0 || height <= 0 || length1 <= 0 || width1 <= 0) {
    throw Standard_ConstructionError("尺寸参数必须为正数");
  }
  if (cornerRadius <= 0) {
    throw Standard_ConstructionError("圆角半径必须大于0");
  }

  // 1. 计算关键几何参数
  const double halfLength = length / 2;
  const double halfWidth = width / 2;
  const double halfWidth1 = width1 / 2;

  // 2. 定义主直通段四个角点
  const gp_Pnt p1(-halfLength, -halfWidth, zoffset); // 左下角
  const gp_Pnt p2(-halfLength, halfWidth, zoffset);  // 左上角
  const gp_Pnt p3(halfLength, halfWidth, zoffset);   // 右上角
  const gp_Pnt p4(halfLength, -halfWidth, zoffset);  // 右下角

  // 3. 定义支线段端点
  const gp_Pnt p7(-halfWidth1, halfWidth + length1,
                  zoffset);                                  // 支线段左上角点
  const gp_Pnt p8(halfWidth1, halfWidth + length1, zoffset); // 支线段右下角点

  // 4. 计算圆弧关键点（精确几何关系）
  // 右圆弧参数（连接直通段右侧底部与支段底部）
  const gp_Pnt rightArcStart(halfWidth1 + cornerRadius, halfWidth, zoffset);
  const gp_Pnt rightArcEnd(halfWidth1, halfWidth + cornerRadius, zoffset);

  // 左圆弧参数（连接直通段右侧顶部与支段顶部）
  const gp_Pnt leftArcStart(-halfWidth1 - cornerRadius, halfWidth, zoffset);
  const gp_Pnt leftArcEnd(-halfWidth1, halfWidth + cornerRadius, zoffset);

  // 5. 计算圆心位置（Y轴中点）
  // 左圆弧圆心
  const gp_Pnt leftCircleCenter(-halfWidth1 - cornerRadius,
                                halfWidth + cornerRadius, zoffset);

  // 右圆弧圆心
  const gp_Pnt rightCircleCenter(halfWidth1 + cornerRadius,
                                 halfWidth + cornerRadius, zoffset);

  // 6. 构造圆弧几何
  // 左圆弧构造
  gp_Circ leftCircle(gp_Ax2(leftCircleCenter, gp_Dir(0, 0, 1)), cornerRadius);
  Handle(Geom_Circle) leftGeomCircle = new Geom_Circle(leftCircle);
  Standard_Real leftStartParam = ElCLib::Parameter(leftCircle, leftArcStart);
  Standard_Real leftEndParam = ElCLib::Parameter(leftCircle, leftArcEnd);
  TopoDS_Edge leftArc =
      BRepBuilderAPI_MakeEdge(leftGeomCircle, leftStartParam, leftEndParam)
          .Edge();

  // 右圆弧构造
  gp_Circ rightCircle(gp_Ax2(rightCircleCenter, gp_Dir(0, 0, 1)), cornerRadius);
  Handle(Geom_Circle) rightGeomCircle = new Geom_Circle(rightCircle);
  Standard_Real rightStartParam = ElCLib::Parameter(rightCircle, rightArcEnd);
  Standard_Real rightEndParam = ElCLib::Parameter(rightCircle, rightArcStart);
  TopoDS_Edge rightArc =
      BRepBuilderAPI_MakeEdge(rightGeomCircle, rightStartParam, rightEndParam)
          .Edge();
  rightArc.Reverse();

  // 7. 构建完整线框（确保拓扑闭合）
  BRepBuilderAPI_MakeWire wireMaker;

  // 主直通段底边
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p1, p2));

  // 左过渡段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p2, leftArcStart));
  wireMaker.Add(leftArc);
  wireMaker.Add(BRepBuilderAPI_MakeEdge(leftArcEnd, p7));

  // 支线段底部
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p7, p8));

  // 右过渡段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p8, rightArcEnd));
  wireMaker.Add(rightArc);
  wireMaker.Add(BRepBuilderAPI_MakeEdge(rightArcStart, p3));

  // 主直通段顶边
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p3, p4));

  // 闭合线段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p4, p1));

  // 8. 创建底面并拉伸
  if (!wireMaker.IsDone()) {
    throw Standard_ConstructionError("线框构造失败");
  }
  TopoDS_Face face = BRepBuilderAPI_MakeFace(wireMaker.Wire());

  return BRepPrimAPI_MakePrism(face, gp_Vec(0, 0, height)).Shape();
}


/**
 * @brief 创建三通折角工作井
 * @param length 直通段长度(mm)
 * @param width 直通段宽度(mm)
 * @param height 直通段高度(mm)
 * @param length1 支线段长度(mm)
 * @param width1 支线段宽度(mm)
 * @param cornerLength 井转角折角长(mm)
 * @param cornerWidth 井转角折角宽(mm)
 * @param angle  井转角角度
 * @return 三通工作井的形状
 */
TopoDS_Shape create_three_way_corner_working_well_part(
    double length, double width, double height, double length1, double width1,
    double cornerLength, double cornerWidth, double zoffset) {
  // 参数校验
  if (length <= 0 || width <= 0 || height <= 0 || length1 <= 0 || width1 <= 0) {
    throw Standard_ConstructionError("尺寸参数必须为正数");
  }
  if (length1 <= 0 || width1 <= 0) {
    throw Standard_ConstructionError("支线段尺寸参数必须为正数");
  }

  // 1. 计算关键几何参数
  const double halfLength = length / 2;
  const double halfWidth = width / 2;
  const double halfWidth1 = width1 / 2;

  // 2. 定义主直通段四个角点
  const gp_Pnt p1(-halfLength, -halfWidth, zoffset); // 左下角
  const gp_Pnt p2(-halfLength, halfWidth, zoffset);  // 左上角
  const gp_Pnt p3(halfLength, halfWidth, zoffset);   // 右上角
  const gp_Pnt p4(halfLength, -halfWidth, zoffset);  // 右下角

  // 3. 定义支线段端点
  const gp_Pnt p7(-halfWidth1, halfWidth + length1,
                  zoffset);                                  // 支线段左上角点
  const gp_Pnt p8(halfWidth1, halfWidth + length1, zoffset); // 支线段右下角点

  const gp_Pnt leftStart(-halfWidth1 - cornerLength, halfWidth, zoffset);
  const gp_Pnt leftEnd(-halfWidth1, halfWidth + cornerWidth, zoffset);

  const gp_Pnt rightStart(halfWidth1 + cornerLength, halfWidth, zoffset);
  const gp_Pnt rightEnd(halfWidth1, halfWidth + cornerWidth, zoffset);

  // 7. 构建完整线框（确保拓扑闭合）
  BRepBuilderAPI_MakeWire wireMaker;

  // 主直通段底边
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p1, p2));

  // 左过渡段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p2, leftStart));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(leftStart, leftEnd));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(leftEnd, p7));

  // 支线段底部
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p7, p8));

  // 右过渡段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p8, rightEnd));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(rightEnd, rightStart));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(rightStart, p3));

  // 主直通段顶边
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p3, p4));

  // 闭合线段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p4, p1));

  // 8. 创建底面并拉伸
  if (!wireMaker.IsDone()) {
    throw Standard_ConstructionError("线框构造失败");
  }
  TopoDS_Face face = BRepBuilderAPI_MakeFace(wireMaker.Wire());

  return BRepPrimAPI_MakePrism(face, gp_Vec(0, 0, height)).Shape();
}


TopoDS_Shape create_three_way_chamfer_round_corner_working_well_part(
    double length, double width, double height, double length1, double width1,
    double cornerLength2, double cornerRadius, double angle, double yoffset,
    double zoffset) {
  // 1. 计算关键点坐标
  double halfLength = length / 2;

  // 2. 定义主直通段四个角点
  const gp_Pnt p1(-halfLength, yoffset, zoffset);         // 左下角
  const gp_Pnt p2(-halfLength, width + yoffset, zoffset); // 左上角
  const gp_Pnt p3(halfLength, width + yoffset, zoffset);  // 右上角
  const gp_Pnt p4(halfLength, yoffset, zoffset);          // 右下角

  // 3. 计算支线段端点
  const gp_Pnt p9(-halfLength + cornerLength2, yoffset,
                  zoffset); // 支线段起点
  gp_Vec vec19(p1, p9);     // p1指向p9的向量

  // 创建旋转轴(Z轴负方向)
  gp_Ax1 rotationAxis(p9, gp_Dir(0, 0, 1));

  // 旋转指定角度得到p8方向向量
  gp_Vec vec8 = vec19.Rotated(rotationAxis, -(180 - angle) * M_PI / 180.0);
  vec8.Normalize();
  vec8 *= length1;
  const gp_Pnt p8(p9.X() + vec8.X(), p9.Y() + vec8.Y(), p9.Z() + vec8.Z());

  // 4. 计算支线段其他点
  gp_Vec vec98(p9, p8); // p9指向p8的向量

  // 创建新的旋转轴(Z轴正方向)
  gp_Ax1 rotationAxis2(p8, gp_Dir(0, 0, 1));

  // 旋转90度得到垂直向量
  gp_Vec vec7 = vec98.Rotated(rotationAxis2, M_PI_2);

  // 归一化并缩放为宽度width1
  vec7.Normalize();
  vec7 *= width1;
  const gp_Pnt p7(p8.X() + vec7.X(), p8.Y() + vec7.Y(), p8.Z() + vec7.Z());

  // 计算p6点向量(与vec98垂直)
  gp_Vec vec76 = vec7.Crossed(gp_Vec(0, 0, -1)); // 使用叉积计算垂直向量
  vec76.Normalize();
  vec76 *= length1;
  // 改为求vec76和x轴交点
  // 修正后的交点计算逻辑
  gp_Pnt p61(0, yoffset, zoffset); // X轴上交点 (Y保持偏移量)
  gp_Vec vec_p7_p61(p7, p61);      // 从p7指向X轴的向量

  // 计算在vec76方向上的投影参数t
  // 使用向量分解公式：vec_p7_p61 = t*vec76 + normal_component
  double t = vec_p7_p61.Dot(vec76) / vec76.SquareMagnitude();

  // 应用参数得到精确交点
  gp_Pnt p6 = p7.Translated(vec76 * t);

  BRepBuilderAPI_MakeWire wireMaker;
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p1, p2));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p2, p3));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p3, p4));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p4, p6));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p6, p7));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p7, p8));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p8, p9));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p9, p1));

  // 7. 创建三维形状
  TopoDS_Shape well =
      BRepPrimAPI_MakePrism(BRepBuilderAPI_MakeFace(wireMaker.Wire()),
                            gp_Vec(0, 0, height))
          .Shape();

  // 7. 自动添加圆角（替代手动计算）
  BRepFilletAPI_MakeFillet fillet(well);
  TopExp_Explorer edgeExplorer(well, TopAbs_EDGE);

  // 添加p6-p7-p8转角处圆角
  for (; edgeExplorer.More(); edgeExplorer.Next()) {
    TopoDS_Edge edge = TopoDS::Edge(edgeExplorer.Current());

    // 获取端点坐标和几何信息
    TopoDS_Vertex first, last;
    TopExp::Vertices(edge, first, last);
    gp_Pnt firstPnt = BRep_Tool::Pnt(first);
    gp_Pnt lastPnt = BRep_Tool::Pnt(last);

    // 检测与p6连接的边
    const bool connectP6 = firstPnt.IsEqual(p6, Precision::Confusion()) ||
                           lastPnt.IsEqual(p6, Precision::Confusion());

    // 新增Z轴平行性检测
    if (connectP6) {
      // 获取边几何参数
      BRepAdaptor_Curve curve(edge);
      if (curve.GetType() == GeomAbs_Line) {
        gp_Dir edgeDir = curve.Line().Direction();

        // 判断是否平行于Z轴（允许角度误差）
        const bool isZParallel =
            edgeDir.IsParallel(gp::DZ(), Precision::Angular());

        if (isZParallel) {
          fillet.Add(cornerRadius, edge);
        }
      }
    }
  }
  fillet.Build();

  return fillet.Shape();
}


/**
 * @brief 创建三通工作井
 */
TopoDS_Shape
create_three_way_working_well(const three_way_well_params &params) {
  if (params.type != three_way_well_type::WORKING_WELL) {
    throw Standard_ConstructionError(
        "three_way_well_type must be WORKING_WELL");
  }
  TopoDS_Shape outer;
  if (params.angle != 90) {
    double offset =
        calculate_length_difference(params.angle, params.outerWallThickness);
    outer = create_three_way_chamfer_round_corner_working_well_part(
        params.length, params.width + params.outerWallThickness * 2,
        params.height + params.topThickness + params.bottomThickness,
        params.branchLength, params.branchWidth + params.outerWallThickness * 2,
        params.branchLeftLength - offset, params.cornerRadius, params.angle,
        -params.outerWallThickness, -params.bottomThickness);
  } else {
    switch (params.cornerType) {
    case corner_style::ROUNDED:
      outer = create_three_way_round_working_well_part(
          params.length, params.width + params.outerWallThickness * 2,
          params.height + params.topThickness + params.bottomThickness,
          params.branchLength,
          params.branchWidth + params.outerWallThickness * 2,
          params.cornerRadius - params.outerWallThickness,
          -params.bottomThickness);
      break;
    case corner_style::ANGLED:
      outer = create_three_way_corner_working_well_part(
          params.length, params.width + params.outerWallThickness * 2,
          params.height + params.topThickness + params.bottomThickness,
          params.branchLength,
          params.branchWidth + params.outerWallThickness * 2,
          params.cornerLength - params.outerWallThickness,
          params.cornerWidth - params.outerWallThickness,
          -params.bottomThickness);
      break;
    default:
      break;
    }
  }

  TopoDS_Shape inner;
  if (params.angle != 90) {
    inner = create_three_way_chamfer_round_corner_working_well_part(
        params.length, params.width, params.height, params.branchLength * 2,
        params.branchWidth, // 支线宽度保持对称
        params.branchLeftLength,
        params.cornerRadius, // 修正转角半径
        params.angle, 0, 0);
  } else {
    switch (params.cornerType) {
    case corner_style::ROUNDED:
      inner = create_three_way_round_working_well_part(
          params.length + params.outerWallThickness * 2, params.width,
          params.height, params.branchLength + params.outerWallThickness * 2,
          params.branchWidth, params.cornerRadius, 0);
      break;
    case corner_style::ANGLED:
      inner = create_three_way_corner_working_well_part(
          params.length + params.outerWallThickness * 2, params.width,
          params.height, params.branchLength + params.outerWallThickness * 2,
          params.branchWidth, params.cornerLength, params.cornerWidth, 0);
      break;
    default:
      break;
    }
  }

  TopoDS_Shape cushion;
  if (params.angle != 90) {
    double offset = calculate_length_difference(
        params.angle, params.outerWallThickness + params.cushionExtension);
    cushion = create_three_way_chamfer_round_corner_working_well_part(
        params.length,
        params.width + params.outerWallThickness * 2 +
            params.cushionExtension * 2,
        params.cushionThickness, params.branchLength,
        params.branchWidth + params.outerWallThickness * 2 +
            params.cushionExtension * 2,
        params.branchLeftLength - offset, params.cornerRadius, params.angle,
        -params.cushionExtension - params.outerWallThickness,
        -params.bottomThickness - params.cushionThickness);
  } else {
    switch (params.cornerType) {
    case corner_style::ROUNDED:
      cushion = create_three_way_round_working_well_part(
          params.length,
          params.width + params.outerWallThickness * 2 +
              params.cushionExtension * 2,
          params.cushionThickness, params.branchLength,
          params.branchWidth + params.outerWallThickness * 2 +
              params.cushionExtension * 2,
          params.cornerRadius - params.outerWallThickness -
              params.cushionExtension,
          -params.bottomThickness - params.cushionThickness);
      break;
    case corner_style::ANGLED:
      cushion = create_three_way_corner_working_well_part(
          params.length,
          params.width + params.outerWallThickness * 2 +
              params.cushionExtension * 2,
          params.cushionThickness, params.branchLength,
          params.branchWidth + params.outerWallThickness * 2 +
              params.cushionExtension * 2,
          params.cornerLength + params.outerWallThickness +
              params.cushionExtension,
          params.cornerWidth + params.outerWallThickness +
              params.cushionExtension,
          -params.bottomThickness - params.cushionThickness);
      break;
    default:
      break;
    }
  }

  // 合并所有部分
  TopoDS_Shape well = BRepAlgoAPI_Cut(outer, inner).Shape();

  well = BRepAlgoAPI_Fuse(well, cushion).Shape();

  return well;
}


/**
 * @brief 创建三通明挖隧道井
 */
TopoDS_Shape
create_three_way_open_cut_tunnel(const three_way_well_params &params) {
  if (params.type != three_way_well_type::OPEN_CUT_TUNNEL) {
    throw Standard_ConstructionError(
        "three_way_open_cut_tunnel must be OPEN_CUT_TUNNEL");
  }
  TopoDS_Shape outer;
  switch (params.cornerType) {
  case corner_style::ROUNDED:
    outer = create_three_way_round_working_well_part(
        params.length + params.outerWallThickness * 2,
        params.width + params.outerWallThickness * 2,
        params.height + params.topThickness + params.bottomThickness,
        params.branchLength + params.outerWallThickness * 2,
        params.branchWidth + params.outerWallThickness * 2,
        params.cornerRadius - params.outerWallThickness,
        -params.bottomThickness);
    break;
  case corner_style::ANGLED:
    outer = create_three_way_corner_working_well_part(
        params.length + params.outerWallThickness * 2,
        params.width + params.outerWallThickness * 2,
        params.height + params.topThickness + params.bottomThickness,
        params.branchLength + params.outerWallThickness * 2,
        params.branchWidth + params.outerWallThickness * 2,
        params.cornerLength - params.outerWallThickness,
        params.cornerWidth - params.outerWallThickness,
        -params.bottomThickness);
    break;
  default:
    break;
  }

  // 2. 创建左连接段
  TopoDS_Shape leftTunnel;
  switch (params.leftSectionStyle) {
  case connection_section_style::RECTANGULAR:
    leftTunnel = create_rectangular_section(
        params.leftSectionLength, params.leftSectionWidth,
        params.leftSectionHeight, params.outerWallThickness,
        params.topThickness, params.bottomThickness, true);
    break;
  case connection_section_style::HORSESHOE:
    leftTunnel = create_horseshoe_section(
        params.leftSectionLength, params.leftSectionWidth,
        params.leftSectionHeight, params.leftSectionArcHeight,
        params.outerWallThickness, true);
    break;
  case connection_section_style::CIRCULAR:
    leftTunnel = create_circular_section(params.leftSectionLength,
                                         params.leftSectionHeight / 2,
                                         params.outerWallThickness, true);
    break;
  }

  // 移动左连接段到正确位置
  gp_Trsf leftTrsf;
  leftTrsf.SetTranslation(
      gp_Vec(-params.leftSectionLength - params.length / 2, 0, 0));
  leftTunnel = BRepBuilderAPI_Transform(leftTunnel, leftTrsf).Shape();

  outer = BRepAlgoAPI_Fuse(outer, leftTunnel).Shape();

  // 3. 创建右连接段
  TopoDS_Shape rightTunnel;
  switch (params.rightSectionStyle) {
  case connection_section_style::RECTANGULAR:
    rightTunnel = create_rectangular_section(
        params.rightSectionLength, params.rightSectionWidth,
        params.rightSectionHeight, params.outerWallThickness,
        params.topThickness, params.bottomThickness, true);
    break;
  case connection_section_style::HORSESHOE:
    rightTunnel = create_horseshoe_section(
        params.rightSectionLength, params.rightSectionWidth,
        params.rightSectionHeight, params.rightSectionArcHeight,
        params.outerWallThickness, true);
    break;
  case connection_section_style::CIRCULAR:
    rightTunnel = create_circular_section(params.rightSectionLength,
                                          params.rightSectionHeight / 2,
                                          params.outerWallThickness, true);
    break;
  }

  // 移动支连接段到正确位置
  gp_Trsf rightTrsf;
  rightTrsf.SetTranslation(gp_Vec(params.length / 2, 0, 0));
  rightTunnel = BRepBuilderAPI_Transform(rightTunnel, rightTrsf).Shape();

  outer = BRepAlgoAPI_Fuse(outer, rightTunnel).Shape();

  // 3. 创建支连接段
  TopoDS_Shape branchTunnel;
  switch (params.branchSectionStyle) {
  case connection_section_style::RECTANGULAR:
    branchTunnel = create_rectangular_section(
        params.branchSectionLength, params.branchSectionWidth,
        params.branchSectionHeight, params.outerWallThickness,
        params.topThickness, params.bottomThickness, true);
    break;
  case connection_section_style::HORSESHOE:
    branchTunnel = create_horseshoe_section(
        params.branchSectionLength, params.branchSectionWidth,
        params.branchSectionHeight, params.branchSectionArcHeight,
        params.outerWallThickness, true);
    break;
  case connection_section_style::CIRCULAR:
    branchTunnel = create_circular_section(params.branchSectionLength,
                                           params.branchSectionHeight / 2,
                                           params.outerWallThickness, true);
    break;
  }

  // 移动右连接段到正确位置
  gp_Trsf branchTrsf;
  gp_Trsf branchModel;
  branchModel.SetTranslation(gp_Vec(-params.branchSectionLength / 2, 0, 0));
  gp_Trsf rotateTrsf;
  rotateTrsf.SetRotation(gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(0, 0, -1)),
                         90 * M_PI / 180.0);

  branchTrsf.SetTranslation(gp_Vec(0,
                                   params.branchLength + params.width / 2 +
                                       params.branchSectionLength / 2,
                                   0));
  branchTunnel = BRepBuilderAPI_Transform(branchTunnel, branchModel).Shape();
  branchTunnel = BRepBuilderAPI_Transform(branchTunnel, rotateTrsf).Shape();
  branchTunnel = BRepBuilderAPI_Transform(branchTunnel, branchTrsf).Shape();

  outer = BRepAlgoAPI_Fuse(outer, branchTunnel).Shape();

  TopoDS_Shape inner;
  switch (params.cornerType) {
  case corner_style::ROUNDED:
    inner = create_three_way_round_working_well_part(
        params.length + params.outerWallThickness * 2, params.width,
        params.height, params.branchLength + params.outerWallThickness * 2,
        params.branchWidth, params.cornerRadius, 0);
    break;
  case corner_style::ANGLED:
    inner = create_three_way_corner_working_well_part(
        params.length + params.outerWallThickness * 2, params.width,
        params.height, params.branchLength + params.outerWallThickness * 2,
        params.branchWidth, params.cornerLength, params.cornerWidth, 0);
    break;
  default:
    break;
  }

  TopoDS_Shape innerLeftTunnel;
  switch (params.leftSectionStyle) {
  case connection_section_style::RECTANGULAR:
    innerLeftTunnel = create_rectangular_section(
        params.leftSectionLength - params.outerWallThickness,
        params.leftSectionWidth, params.leftSectionHeight,
        params.outerWallThickness, params.topThickness, params.bottomThickness,
        false);
    break;
  case connection_section_style::HORSESHOE:
    innerLeftTunnel = create_horseshoe_section(
        params.leftSectionLength - params.outerWallThickness,
        params.leftSectionWidth, params.leftSectionHeight,
        params.leftSectionArcHeight, params.outerWallThickness, false);
    break;
  case connection_section_style::CIRCULAR:
    innerLeftTunnel = create_circular_section(
        params.leftSectionLength - params.outerWallThickness,
        params.leftSectionHeight / 2, params.outerWallThickness, false);
    break;
  }

  innerLeftTunnel = BRepBuilderAPI_Transform(innerLeftTunnel, leftTrsf).Shape();

  inner = BRepAlgoAPI_Fuse(inner, innerLeftTunnel).Shape();

  TopoDS_Shape innerRightTunnel;
  switch (params.rightSectionStyle) {
  case connection_section_style::RECTANGULAR:
    innerRightTunnel = create_rectangular_section(
        params.rightSectionLength - params.outerWallThickness,
        params.rightSectionWidth, params.rightSectionHeight,
        params.outerWallThickness, params.topThickness, params.bottomThickness,
        false);
    break;
  case connection_section_style::HORSESHOE:
    innerRightTunnel = create_horseshoe_section(
        params.rightSectionLength - params.outerWallThickness,
        params.rightSectionWidth, params.rightSectionHeight,
        params.rightSectionArcHeight, params.outerWallThickness, false);
    break;
  case connection_section_style::CIRCULAR:
    innerRightTunnel = create_circular_section(
        params.rightSectionLength - params.outerWallThickness,
        params.rightSectionHeight / 2, params.outerWallThickness, false);
    break;
  }

  rightTrsf.SetTranslation(
      gp_Vec(params.length / 2 + params.outerWallThickness, 0, 0));
  innerRightTunnel =
      BRepBuilderAPI_Transform(innerRightTunnel, rightTrsf).Shape();

  inner = BRepAlgoAPI_Fuse(inner, innerRightTunnel).Shape();

  // 3. 创建右连接段
  TopoDS_Shape innerBranchTunnel;
  switch (params.branchSectionStyle) {
  case connection_section_style::RECTANGULAR:
    innerBranchTunnel = create_rectangular_section(
        params.branchSectionLength - params.outerWallThickness,
        params.branchSectionWidth, params.branchSectionHeight,
        params.outerWallThickness, params.topThickness, params.bottomThickness,
        false);
    break;
  case connection_section_style::HORSESHOE:
    innerBranchTunnel = create_horseshoe_section(
        params.branchSectionLength - params.outerWallThickness,
        params.branchSectionWidth, params.branchSectionHeight,
        params.branchSectionArcHeight, params.outerWallThickness, false);
    break;
  case connection_section_style::CIRCULAR:
    innerBranchTunnel = create_circular_section(
        params.branchSectionLength - params.outerWallThickness,
        params.branchSectionHeight / 2, params.outerWallThickness, false);
    break;
  }

  branchModel.SetTranslation(gp_Vec(
      -(params.branchSectionLength - params.outerWallThickness) / 2, 0, 0));
  branchTrsf.SetTranslation(gp_Vec(
      0,
      params.branchLength + params.width / 2 + params.branchSectionLength / 2 +
          params.outerWallThickness + params.outerWallThickness / 2,
      0));
  innerBranchTunnel =
      BRepBuilderAPI_Transform(innerBranchTunnel, branchModel).Shape();
  innerBranchTunnel =
      BRepBuilderAPI_Transform(innerBranchTunnel, rotateTrsf).Shape();
  innerBranchTunnel =
      BRepBuilderAPI_Transform(innerBranchTunnel, branchTrsf).Shape();

  inner = BRepAlgoAPI_Fuse(inner, innerBranchTunnel).Shape();

  TopoDS_Shape cushion;
  switch (params.cornerType) {
  case corner_style::ROUNDED:
    cushion = create_three_way_round_working_well_part(
        params.length + params.leftSectionLength + params.rightSectionLength,
        params.width + params.outerWallThickness * 2 +
            params.cushionExtension * 2,
        params.cushionThickness,
        params.branchLength + params.branchSectionLength,
        params.branchWidth + params.outerWallThickness * 2 +
            params.cushionExtension * 2,
        params.cornerRadius - params.outerWallThickness -
            params.cushionExtension,
        -params.bottomThickness - params.cushionThickness);
    break;
  case corner_style::ANGLED:
    cushion = create_three_way_corner_working_well_part(
        params.length + params.leftSectionLength + params.rightSectionLength,
        params.width + params.outerWallThickness * 2 +
            params.cushionExtension * 2,
        params.cushionThickness,
        params.branchLength + params.branchSectionLength,
        params.branchWidth + params.outerWallThickness * 2 +
            params.cushionExtension * 2,
        params.cornerLength + params.outerWallThickness +
            params.cushionExtension,
        params.cornerWidth + params.outerWallThickness +
            params.cushionExtension,
        -params.bottomThickness - params.cushionThickness);
    break;
  default:
    break;
  }

  // 合并所有部分
  TopoDS_Shape well = BRepAlgoAPI_Cut(outer, inner).Shape();

  well = BRepAlgoAPI_Fuse(well, cushion).Shape();

  return well;
}


TopoDS_Shape create_three_way_circle_well_part(double length, double width,
                                               double height, double length1,
                                               double width1, double wellRadius,
                                               double weelheight,
                                               double zoffset) {
  // 参数校验
  if (length <= 0 || width <= 0 || height <= 0 || length1 <= 0 || width1 <= 0) {
    throw Standard_ConstructionError("尺寸参数必须为正数");
  }
  if (length1 <= 0 || width1 <= 0) {
    throw Standard_ConstructionError("支线段尺寸参数必须为正数");
  }

  // 1. 计算关键几何参数
  const double halfLength = length / 2;
  const double halfWidth = width / 2;
  const double halfWidth1 = width1 / 2;

  // 2. 定义主直通段四个角点
  const gp_Pnt p1(-halfLength, -halfWidth, zoffset); // 左下角
  const gp_Pnt p2(-halfLength, halfWidth, zoffset);  // 左上角
  const gp_Pnt p3(halfLength, halfWidth, zoffset);   // 右上角
  const gp_Pnt p4(halfLength, -halfWidth, zoffset);  // 右下角

  // 3. 定义支线段端点
  const gp_Pnt p7(-halfWidth1, halfWidth + length1,
                  zoffset);                                  // 支线段左上角点
  const gp_Pnt p8(halfWidth1, halfWidth + length1, zoffset); // 支线段右下角点
  const gp_Pnt p9(-halfWidth1, halfWidth, zoffset);          // 支线段左下角点
  const gp_Pnt p10(halfWidth1, halfWidth, zoffset);          // 支线段右下角点

  // 7. 构建完整线框（确保拓扑闭合）
  BRepBuilderAPI_MakeWire wireMaker;

  // 主直通段底边
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p1, p2));

  // 左过渡段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p2, p9));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p9, p7));

  // 支线段底部
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p7, p8));

  // 右过渡段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p8, p10));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p10, p3));

  // 主直通段顶边
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p3, p4));

  // 闭合线段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p4, p1));

  // 8. 创建底面并拉伸
  if (!wireMaker.IsDone()) {
    throw Standard_ConstructionError("线框构造失败");
  }
  TopoDS_Face face = BRepBuilderAPI_MakeFace(wireMaker.Wire());

  TopoDS_Shape tunnel =
      BRepPrimAPI_MakePrism(face, gp_Vec(0, 0, height)).Shape();

  gp_Ax2 wellAxis(gp_Pnt(0, 0, zoffset), gp::DZ());
  TopoDS_Shape well =
      BRepPrimAPI_MakeCylinder(wellAxis, wellRadius, weelheight).Shape();
  return BRepAlgoAPI_Fuse(tunnel, well).Shape();
}


TopoDS_Shape create_three_way_rectangular_well_part(
    double length, double width, double height, double length1, double width1,
    double wellWidth, double weelheight, double zoffset) {
  // 参数校验
  if (length <= 0 || width <= 0 || height <= 0 || length1 <= 0 || width1 <= 0) {
    throw Standard_ConstructionError("尺寸参数必须为正数");
  }
  if (length1 <= 0 || width1 <= 0) {
    throw Standard_ConstructionError("支线段尺寸参数必须为正数");
  }

  // 1. 计算关键几何参数
  const double halfLength = length / 2;
  const double halfWidth = width / 2;
  const double halfWidth1 = width1 / 2;

  // 2. 定义主直通段四个角点
  const gp_Pnt p1(-halfLength, -halfWidth, zoffset); // 左下角
  const gp_Pnt p2(-halfLength, halfWidth, zoffset);  // 左上角
  const gp_Pnt p3(halfLength, halfWidth, zoffset);   // 右上角
  const gp_Pnt p4(halfLength, -halfWidth, zoffset);  // 右下角

  // 3. 定义支线段端点
  const gp_Pnt p7(-halfWidth1, halfWidth + length1,
                  zoffset);                                  // 支线段左上角点
  const gp_Pnt p8(halfWidth1, halfWidth + length1, zoffset); // 支线段右上角点
  const gp_Pnt p9(-halfWidth1, halfWidth, zoffset);          // 支线段左下角点
  const gp_Pnt p10(halfWidth1, halfWidth, zoffset);          // 支线段右下角点

  // 7. 构建完整线框（确保拓扑闭合）
  BRepBuilderAPI_MakeWire wireMaker;

  // 主直通段底边
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p1, p2));

  // 左过渡段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p2, p9));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p9, p7));

  // 支线段底部
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p7, p8));

  // 右过渡段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p8, p10));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p10, p3));

  // 主直通段顶边
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p3, p4));

  // 闭合线段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p4, p1));

  // 8. 创建底面并拉伸
  if (!wireMaker.IsDone()) {
    throw Standard_ConstructionError("线框构造失败");
  }
  TopoDS_Face face = BRepBuilderAPI_MakeFace(wireMaker.Wire());

  TopoDS_Shape tunnel =
      BRepPrimAPI_MakePrism(face, gp_Vec(0, 0, height)).Shape();

  gp_Pnt innerOrigin(-wellWidth / 2, -wellWidth / 2, zoffset);
  BRepPrimAPI_MakeBox well(innerOrigin, wellWidth, wellWidth, weelheight);

  return BRepAlgoAPI_Fuse(tunnel, well).Shape();
}


/**
 * @brief 创建三通暗挖隧道井
 */
TopoDS_Shape
create_three_way_underground_tunnel(const three_way_well_params &params) {
  if (params.type != three_way_well_type::UNDERGROUND_TUNNEL) {
    throw Standard_ConstructionError(
        "three_way_underground_tunnel must be UNDERGROUND_TUNNEL");
  }
  if (params.isDoubleShaft) {
    throw Standard_ConstructionError(
        "three_way_underground_tunnel must be single shaft");
  }
  TopoDS_Shape outer;
  switch (params.shaftType) {
  case shaft_style::CIRCULAR:
    outer = create_three_way_circle_well_part(
        params.length + params.outerWallThickness * 2,
        params.width + params.outerWallThickness * 2,
        params.height + params.outerWallThickness * 2,
        params.branchLength + params.outerWallThickness * 2,
        params.branchWidth + params.outerWallThickness * 2,
        params.shaftRadius + params.outerWallThickness +
            params.innerWallThickness,
        params.height + params.outerWallThickness * 2,
        -params.outerWallThickness);
    break;
  case shaft_style::RECTANGULAR:
    outer = create_three_way_rectangular_well_part(
        params.length + params.outerWallThickness * 2,
        params.width + params.outerWallThickness * 2,
        params.height + params.outerWallThickness * 2,
        params.branchLength + params.outerWallThickness * 2,
        params.branchWidth + params.outerWallThickness * 2,
        (params.shaftRadius + params.outerWallThickness +
         params.innerWallThickness) *
            2,
        params.height + params.outerWallThickness * 2,
        -params.outerWallThickness);
    break;
  default:
    break;
  }

  // 2. 创建左连接段
  TopoDS_Shape leftTunnel;
  switch (params.leftSectionStyle) {
  case connection_section_style::RECTANGULAR:
    leftTunnel = create_rectangular_section(
        params.leftSectionLength, params.leftSectionWidth,
        params.leftSectionHeight, params.outerWallThickness,
        params.outerWallThickness, params.outerWallThickness, true);
    break;
  case connection_section_style::HORSESHOE:
    leftTunnel = create_horseshoe_section(
        params.leftSectionLength, params.leftSectionWidth,
        params.leftSectionHeight, params.leftSectionArcHeight,
        params.outerWallThickness, true);
    break;
  case connection_section_style::CIRCULAR:
    leftTunnel = create_circular_section(params.leftSectionLength,
                                         params.leftSectionHeight / 2,
                                         params.outerWallThickness, true);
    break;
  }

  // 移动左连接段到正确位置
  gp_Trsf leftTrsf;
  leftTrsf.SetTranslation(
      gp_Vec(-params.leftSectionLength - params.length / 2, 0, 0));
  leftTunnel = BRepBuilderAPI_Transform(leftTunnel, leftTrsf).Shape();

  outer = BRepAlgoAPI_Fuse(outer, leftTunnel).Shape();

  // 3. 创建右连接段
  TopoDS_Shape rightTunnel;
  switch (params.rightSectionStyle) {
  case connection_section_style::RECTANGULAR:
    rightTunnel = create_rectangular_section(
        params.rightSectionLength, params.rightSectionWidth,
        params.rightSectionHeight, params.outerWallThickness,
        params.outerWallThickness, params.outerWallThickness, true);
    break;
  case connection_section_style::HORSESHOE:
    rightTunnel = create_horseshoe_section(
        params.rightSectionLength, params.rightSectionWidth,
        params.rightSectionHeight, params.rightSectionArcHeight,
        params.outerWallThickness, true);
    break;
  case connection_section_style::CIRCULAR:
    rightTunnel = create_circular_section(params.rightSectionLength,
                                          params.rightSectionHeight / 2,
                                          params.outerWallThickness, true);
    break;
  }

  // 移动支连接段到正确位置
  gp_Trsf rightTrsf;
  rightTrsf.SetTranslation(gp_Vec(params.length / 2, 0, 0));
  rightTunnel = BRepBuilderAPI_Transform(rightTunnel, rightTrsf).Shape();

  outer = BRepAlgoAPI_Fuse(outer, rightTunnel).Shape();

  // 3. 创建支连接段
  TopoDS_Shape branchTunnel;
  switch (params.branchSectionStyle) {
  case connection_section_style::RECTANGULAR:
    branchTunnel = create_rectangular_section(
        params.branchSectionLength, params.branchSectionWidth,
        params.branchSectionHeight, params.outerWallThickness,
        params.outerWallThickness, params.outerWallThickness, true);
    break;
  case connection_section_style::HORSESHOE:
    branchTunnel = create_horseshoe_section(
        params.branchSectionLength, params.branchSectionWidth,
        params.branchSectionHeight, params.branchSectionArcHeight,
        params.outerWallThickness, true);
    break;
  case connection_section_style::CIRCULAR:
    branchTunnel = create_circular_section(params.branchSectionLength,
                                           params.branchSectionHeight / 2,
                                           params.outerWallThickness, true);
    break;
  }

  // 移动右连接段到正确位置
  gp_Trsf branchTrsf;
  gp_Trsf branchModel;
  branchModel.SetTranslation(gp_Vec(-params.branchSectionLength / 2, 0, 0));
  gp_Trsf rotateTrsf;
  rotateTrsf.SetRotation(gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(0, 0, -1)),
                         90 * M_PI / 180.0);

  branchTrsf.SetTranslation(gp_Vec(0,
                                   params.branchLength + params.width / 2 +
                                       params.branchSectionLength / 2,
                                   0));
  branchTunnel = BRepBuilderAPI_Transform(branchTunnel, branchModel).Shape();
  branchTunnel = BRepBuilderAPI_Transform(branchTunnel, rotateTrsf).Shape();
  branchTunnel = BRepBuilderAPI_Transform(branchTunnel, branchTrsf).Shape();

  outer = BRepAlgoAPI_Fuse(outer, branchTunnel).Shape();

  TopoDS_Shape inner;
  switch (params.shaftType) {
  case shaft_style::CIRCULAR:
    inner = create_three_way_circle_well_part(
        params.length + params.outerWallThickness * 2, params.width,
        params.height, params.branchLength + params.outerWallThickness * 2,
        params.branchWidth, params.shaftRadius,
        params.height + params.outerWallThickness * 2, 0);
    break;
  case shaft_style::RECTANGULAR:
    inner = create_three_way_rectangular_well_part(
        params.length + params.outerWallThickness * 2, params.width,
        params.height, params.branchLength + params.outerWallThickness * 2,
        params.branchWidth, params.shaftRadius * 2,
        params.height + params.outerWallThickness * 2, 0);
    break;
  default:
    break;
  }

  TopoDS_Shape innerLeftTunnel;
  switch (params.leftSectionStyle) {
  case connection_section_style::RECTANGULAR:
    innerLeftTunnel = create_rectangular_section(
        params.leftSectionLength - params.outerWallThickness,
        params.leftSectionWidth, params.leftSectionHeight,
        params.outerWallThickness, params.outerWallThickness,
        params.outerWallThickness, false);
    break;
  case connection_section_style::HORSESHOE:
    innerLeftTunnel = create_horseshoe_section(
        params.leftSectionLength - params.outerWallThickness,
        params.leftSectionWidth, params.leftSectionHeight,
        params.leftSectionArcHeight, params.outerWallThickness, false);
    break;
  case connection_section_style::CIRCULAR:
    innerLeftTunnel = create_circular_section(
        params.leftSectionLength - params.outerWallThickness,
        params.leftSectionHeight / 2, params.outerWallThickness, false);
    break;
  }

  innerLeftTunnel = BRepBuilderAPI_Transform(innerLeftTunnel, leftTrsf).Shape();

  inner = BRepAlgoAPI_Fuse(inner, innerLeftTunnel).Shape();

  TopoDS_Shape innerRightTunnel;
  switch (params.rightSectionStyle) {
  case connection_section_style::RECTANGULAR:
    innerRightTunnel = create_rectangular_section(
        params.rightSectionLength - params.outerWallThickness,
        params.rightSectionWidth, params.rightSectionHeight,
        params.outerWallThickness, params.outerWallThickness,
        params.outerWallThickness, false);
    break;
  case connection_section_style::HORSESHOE:
    innerRightTunnel = create_horseshoe_section(
        params.rightSectionLength - params.outerWallThickness,
        params.rightSectionWidth, params.rightSectionHeight,
        params.rightSectionArcHeight, params.outerWallThickness, false);
    break;
  case connection_section_style::CIRCULAR:
    innerRightTunnel = create_circular_section(
        params.rightSectionLength - params.outerWallThickness,
        params.rightSectionHeight / 2, params.outerWallThickness, false);
    break;
  }

  rightTrsf.SetTranslation(
      gp_Vec(params.length / 2 + params.outerWallThickness, 0, 0));
  innerRightTunnel =
      BRepBuilderAPI_Transform(innerRightTunnel, rightTrsf).Shape();

  inner = BRepAlgoAPI_Fuse(inner, innerRightTunnel).Shape();

  // 3. 创建右连接段
  TopoDS_Shape innerBranchTunnel;
  switch (params.branchSectionStyle) {
  case connection_section_style::RECTANGULAR:
    innerBranchTunnel = create_rectangular_section(
        params.branchSectionLength - params.outerWallThickness,
        params.branchSectionWidth, params.branchSectionHeight,
        params.outerWallThickness, params.outerWallThickness,
        params.outerWallThickness, false);
    break;
  case connection_section_style::HORSESHOE:
    innerBranchTunnel = create_horseshoe_section(
        params.branchSectionLength - params.outerWallThickness,
        params.branchSectionWidth, params.branchSectionHeight,
        params.branchSectionArcHeight, params.outerWallThickness, false);
    break;
  case connection_section_style::CIRCULAR:
    innerBranchTunnel = create_circular_section(
        params.branchSectionLength - params.outerWallThickness,
        params.branchSectionHeight / 2, params.outerWallThickness, false);
    break;
  }

  branchModel.SetTranslation(gp_Vec(
      -(params.branchSectionLength - params.outerWallThickness) / 2, 0, 0));
  branchTrsf.SetTranslation(gp_Vec(
      0,
      params.branchLength + params.width / 2 + params.branchSectionLength / 2 +
          params.outerWallThickness + params.outerWallThickness / 2,
      0));
  innerBranchTunnel =
      BRepBuilderAPI_Transform(innerBranchTunnel, branchModel).Shape();
  innerBranchTunnel =
      BRepBuilderAPI_Transform(innerBranchTunnel, rotateTrsf).Shape();
  innerBranchTunnel =
      BRepBuilderAPI_Transform(innerBranchTunnel, branchTrsf).Shape();

  inner = BRepAlgoAPI_Fuse(inner, innerBranchTunnel).Shape();
  // 合并所有部分
  TopoDS_Shape well = BRepAlgoAPI_Cut(outer, inner).Shape();

  return well;
}


/**
 * @brief 创建三通暗挖隧道双拼井
 */
TopoDS_Shape
create_three_way_double_shaft_tunnel(const three_way_well_params &params) {
  if (params.type != three_way_well_type::UNDERGROUND_TUNNEL) {
    throw Standard_ConstructionError(
        "three_way_underground_tunnel must be UNDERGROUND_TUNNEL");
  }
  if (!params.isDoubleShaft) {
    throw Standard_ConstructionError(
        "three_way_underground_tunnel must be single shaft");
  }
  TopoDS_Shape outer;
  switch (params.shaftType) {
  case shaft_style::CIRCULAR:
    outer = create_three_way_circle_well_part(
        params.length + params.outerWallThickness * 2,
        params.width + params.outerWallThickness * 2,
        params.height + params.outerWallThickness * 2,
        params.branchLength + params.outerWallThickness * 2,
        (params.branchWidth + params.outerWallThickness * 2) * 2,
        params.shaftRadius + params.outerWallThickness +
            params.innerWallThickness,
        params.height + params.outerWallThickness * 2,
        -params.outerWallThickness);
    break;
  case shaft_style::RECTANGULAR:
    outer = create_three_way_rectangular_well_part(
        params.length + params.outerWallThickness * 2,
        params.width + params.outerWallThickness * 2,
        params.height + params.outerWallThickness * 2,
        params.branchLength + params.outerWallThickness * 2,
        (params.branchWidth + params.outerWallThickness * 2) * 2,
        (params.shaftRadius + params.outerWallThickness +
         params.innerWallThickness) *
            2,
        params.height + params.outerWallThickness * 2,
        -params.outerWallThickness);
    break;
  default:
    break;
  }

  // 2. 创建左连接段
  TopoDS_Shape leftTunnel;
  switch (params.leftSectionStyle) {
  case connection_section_style::RECTANGULAR:
    leftTunnel = create_rectangular_section(
        params.leftSectionLength, params.leftSectionWidth,
        params.leftSectionHeight, params.outerWallThickness,
        params.outerWallThickness, params.outerWallThickness, true);
    break;
  case connection_section_style::HORSESHOE:
    leftTunnel = create_horseshoe_section(
        params.leftSectionLength, params.leftSectionWidth,
        params.leftSectionHeight, params.leftSectionArcHeight,
        params.outerWallThickness, true);
    break;
  case connection_section_style::CIRCULAR:
    leftTunnel = create_circular_section(params.leftSectionLength,
                                         params.leftSectionHeight / 2,
                                         params.outerWallThickness, true);
    break;
  }

  // 移动左连接段到正确位置
  gp_Trsf leftTrsf;
  leftTrsf.SetTranslation(
      gp_Vec(-params.leftSectionLength - params.length / 2, 0, 0));
  leftTunnel = BRepBuilderAPI_Transform(leftTunnel, leftTrsf).Shape();

  outer = BRepAlgoAPI_Fuse(outer, leftTunnel).Shape();

  // 3. 创建右连接段
  TopoDS_Shape rightTunnel;
  switch (params.rightSectionStyle) {
  case connection_section_style::RECTANGULAR:
    rightTunnel = create_rectangular_section(
        params.rightSectionLength, params.rightSectionWidth,
        params.rightSectionHeight, params.outerWallThickness,
        params.outerWallThickness, params.outerWallThickness, true);
    break;
  case connection_section_style::HORSESHOE:
    rightTunnel = create_horseshoe_section(
        params.rightSectionLength, params.rightSectionWidth,
        params.rightSectionHeight, params.rightSectionArcHeight,
        params.outerWallThickness, true);
    break;
  case connection_section_style::CIRCULAR:
    rightTunnel = create_circular_section(params.rightSectionLength,
                                          params.rightSectionHeight / 2,
                                          params.outerWallThickness, true);
    break;
  }

  // 移动支连接段到正确位置
  gp_Trsf rightTrsf;
  rightTrsf.SetTranslation(gp_Vec(params.length / 2, 0, 0));
  rightTunnel = BRepBuilderAPI_Transform(rightTunnel, rightTrsf).Shape();

  outer = BRepAlgoAPI_Fuse(outer, rightTunnel).Shape();

  // 3. 创建左支连接段
  TopoDS_Shape branchLeftTunnel;
  switch (params.branchSectionStyle) {
  case connection_section_style::RECTANGULAR:
    branchLeftTunnel = create_rectangular_section(
        params.branchSectionLength, params.branchSectionWidth,
        params.branchSectionHeight, params.outerWallThickness,
        params.outerWallThickness, params.outerWallThickness, true);
    break;
  case connection_section_style::HORSESHOE:
    branchLeftTunnel = create_horseshoe_section(
        params.branchSectionLength, params.branchSectionWidth,
        params.branchSectionHeight, params.branchSectionArcHeight,
        params.outerWallThickness, true);
    break;
  case connection_section_style::CIRCULAR:
    branchLeftTunnel = create_circular_section(params.branchSectionLength,
                                               params.branchSectionHeight / 2,
                                               params.outerWallThickness, true);
    break;
  }

  // 移动右连接段到正确位置
  gp_Trsf branchLeftTrsf;
  gp_Trsf branchLeftModel;
  branchLeftModel.SetTranslation(gp_Vec(-params.branchSectionLength / 2, 0, 0));
  gp_Trsf rotateLeftTrsf;
  rotateLeftTrsf.SetRotation(gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(0, 0, -1)),
                             90 * M_PI / 180.0);

  branchLeftTrsf.SetTranslation(gp_Vec(
      -params.branchSectionWidth / 2 - params.outerWallThickness,
      params.branchLength + params.width / 2 + params.branchSectionLength / 2,
      0));
  branchLeftTunnel =
      BRepBuilderAPI_Transform(branchLeftTunnel, branchLeftModel).Shape();
  branchLeftTunnel =
      BRepBuilderAPI_Transform(branchLeftTunnel, rotateLeftTrsf).Shape();
  branchLeftTunnel =
      BRepBuilderAPI_Transform(branchLeftTunnel, branchLeftTrsf).Shape();

  outer = BRepAlgoAPI_Fuse(outer, branchLeftTunnel).Shape();

  // 3. 创建右支连接段
  TopoDS_Shape branchRightTunnel;
  switch (params.branchSectionStyle) {
  case connection_section_style::RECTANGULAR:
    branchRightTunnel = create_rectangular_section(
        params.branchSectionLength, params.branchSectionWidth,
        params.branchSectionHeight, params.outerWallThickness,
        params.outerWallThickness, params.outerWallThickness, true);
    break;
  case connection_section_style::HORSESHOE:
    branchRightTunnel = create_horseshoe_section(
        params.branchSectionLength, params.branchSectionWidth,
        params.branchSectionHeight, params.branchSectionArcHeight,
        params.outerWallThickness, true);
    break;
  case connection_section_style::CIRCULAR:
    branchRightTunnel = create_circular_section(
        params.branchSectionLength, params.branchSectionHeight / 2,
        params.outerWallThickness, true);
    break;
  }

  // 移动右连接段到正确位置
  gp_Trsf branchRightTrsf;
  gp_Trsf branchRightModel;
  branchRightModel.SetTranslation(
      gp_Vec(-params.branchSectionLength / 2, 0, 0));
  gp_Trsf rotateRightTrsf;
  rotateRightTrsf.SetRotation(gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(0, 0, -1)),
                              90 * M_PI / 180.0);

  branchRightTrsf.SetTranslation(gp_Vec(
      params.branchSectionWidth / 2 + params.outerWallThickness,
      params.branchLength + params.width / 2 + params.branchSectionLength / 2,
      0));
  branchRightTunnel =
      BRepBuilderAPI_Transform(branchRightTunnel, branchRightModel).Shape();
  branchRightTunnel =
      BRepBuilderAPI_Transform(branchRightTunnel, rotateRightTrsf).Shape();
  branchRightTunnel =
      BRepBuilderAPI_Transform(branchRightTunnel, branchRightTrsf).Shape();

  outer = BRepAlgoAPI_Fuse(outer, branchRightTunnel).Shape();

  TopoDS_Shape inner;
  switch (params.shaftType) {
  case shaft_style::CIRCULAR:
    inner = create_three_way_circle_well_part(
        params.length + params.outerWallThickness * 2, params.width,
        params.height, params.branchLength + params.outerWallThickness * 2,
        params.branchWidth * 2, params.shaftRadius,
        params.height + params.outerWallThickness * 2, 0);
    break;
  case shaft_style::RECTANGULAR:
    inner = create_three_way_rectangular_well_part(
        params.length + params.outerWallThickness * 2, params.width,
        params.height, params.branchLength + params.outerWallThickness * 2,
        params.branchWidth * 2, params.shaftRadius * 2,
        params.height + params.outerWallThickness * 2, 0);
    break;
  default:
    break;
  }

  TopoDS_Shape innerLeftTunnel;
  switch (params.leftSectionStyle) {
  case connection_section_style::RECTANGULAR:
    innerLeftTunnel = create_rectangular_section(
        params.leftSectionLength - params.outerWallThickness,
        params.leftSectionWidth, params.leftSectionHeight,
        params.outerWallThickness, params.outerWallThickness,
        params.outerWallThickness, false);
    break;
  case connection_section_style::HORSESHOE:
    innerLeftTunnel = create_horseshoe_section(
        params.leftSectionLength - params.outerWallThickness,
        params.leftSectionWidth, params.leftSectionHeight,
        params.leftSectionArcHeight, params.outerWallThickness, false);
    break;
  case connection_section_style::CIRCULAR:
    innerLeftTunnel = create_circular_section(
        params.leftSectionLength - params.outerWallThickness,
        params.leftSectionHeight / 2, params.outerWallThickness, false);
    break;
  }

  innerLeftTunnel = BRepBuilderAPI_Transform(innerLeftTunnel, leftTrsf).Shape();

  inner = BRepAlgoAPI_Fuse(inner, innerLeftTunnel).Shape();

  TopoDS_Shape innerRightTunnel;
  switch (params.rightSectionStyle) {
  case connection_section_style::RECTANGULAR:
    innerRightTunnel = create_rectangular_section(
        params.rightSectionLength - params.outerWallThickness,
        params.rightSectionWidth, params.rightSectionHeight,
        params.outerWallThickness, params.outerWallThickness,
        params.outerWallThickness, false);
    break;
  case connection_section_style::HORSESHOE:
    innerRightTunnel = create_horseshoe_section(
        params.rightSectionLength - params.outerWallThickness,
        params.rightSectionWidth, params.rightSectionHeight,
        params.rightSectionArcHeight, params.outerWallThickness, false);
    break;
  case connection_section_style::CIRCULAR:
    innerRightTunnel = create_circular_section(
        params.rightSectionLength - params.outerWallThickness,
        params.rightSectionHeight / 2, params.outerWallThickness, false);
    break;
  }

  rightTrsf.SetTranslation(
      gp_Vec(params.length / 2 + params.outerWallThickness, 0, 0));
  innerRightTunnel =
      BRepBuilderAPI_Transform(innerRightTunnel, rightTrsf).Shape();

  inner = BRepAlgoAPI_Fuse(inner, innerRightTunnel).Shape();

  // 3. 创建右连接段
  TopoDS_Shape innerLeftBranchTunnel;
  switch (params.branchSectionStyle) {
  case connection_section_style::RECTANGULAR:
    innerLeftBranchTunnel = create_rectangular_section(
        params.branchSectionLength - params.outerWallThickness,
        params.branchSectionWidth, params.branchSectionHeight,
        params.outerWallThickness, params.outerWallThickness,
        params.outerWallThickness, false);
    break;
  case connection_section_style::HORSESHOE:
    innerLeftBranchTunnel = create_horseshoe_section(
        params.branchSectionLength - params.outerWallThickness,
        params.branchSectionWidth, params.branchSectionHeight,
        params.branchSectionArcHeight, params.outerWallThickness, false);
    break;
  case connection_section_style::CIRCULAR:
    innerLeftBranchTunnel = create_circular_section(
        params.branchSectionLength - params.outerWallThickness,
        params.branchSectionHeight / 2, params.outerWallThickness, false);
    break;
  }

  branchLeftModel.SetTranslation(gp_Vec(
      -(params.branchSectionLength - params.outerWallThickness) / 2, 0, 0));
  branchLeftTrsf.SetTranslation(gp_Vec(
      -params.branchSectionWidth / 2 - params.outerWallThickness,
      params.branchLength + params.width / 2 + params.branchSectionLength / 2 +
          params.outerWallThickness + params.outerWallThickness / 2,
      0));
  innerLeftBranchTunnel =
      BRepBuilderAPI_Transform(innerLeftBranchTunnel, branchLeftModel).Shape();
  innerLeftBranchTunnel =
      BRepBuilderAPI_Transform(innerLeftBranchTunnel, rotateLeftTrsf).Shape();
  innerLeftBranchTunnel =
      BRepBuilderAPI_Transform(innerLeftBranchTunnel, branchLeftTrsf).Shape();

  inner = BRepAlgoAPI_Fuse(inner, innerLeftBranchTunnel).Shape();

  // 3. 创建右连接段
  TopoDS_Shape innerRightBranchTunnel;
  switch (params.branchSectionStyle) {
  case connection_section_style::RECTANGULAR:
    innerRightBranchTunnel = create_rectangular_section(
        params.branchSectionLength - params.outerWallThickness,
        params.branchSectionWidth, params.branchSectionHeight,
        params.outerWallThickness, params.outerWallThickness,
        params.outerWallThickness, false);
    break;
  case connection_section_style::HORSESHOE:
    innerRightBranchTunnel = create_horseshoe_section(
        params.branchSectionLength - params.outerWallThickness,
        params.branchSectionWidth, params.branchSectionHeight,
        params.branchSectionArcHeight, params.outerWallThickness, false);
    break;
  case connection_section_style::CIRCULAR:
    innerRightBranchTunnel = create_circular_section(
        params.branchSectionLength - params.outerWallThickness,
        params.branchSectionHeight / 2, params.outerWallThickness, false);
    break;
  }

  branchRightModel.SetTranslation(gp_Vec(
      -(params.branchSectionLength - params.outerWallThickness) / 2, 0, 0));
  branchRightTrsf.SetTranslation(gp_Vec(
      params.branchSectionWidth / 2 + params.outerWallThickness,
      params.branchLength + params.width / 2 + params.branchSectionLength / 2 +
          params.outerWallThickness + params.outerWallThickness / 2,
      0));
  innerRightBranchTunnel =
      BRepBuilderAPI_Transform(innerRightBranchTunnel, branchRightModel)
          .Shape();
  innerRightBranchTunnel =
      BRepBuilderAPI_Transform(innerRightBranchTunnel, rotateRightTrsf).Shape();
  innerRightBranchTunnel =
      BRepBuilderAPI_Transform(innerRightBranchTunnel, branchRightTrsf).Shape();

  inner = BRepAlgoAPI_Fuse(inner, innerRightBranchTunnel).Shape();

  // 合并所有部分
  TopoDS_Shape well = BRepAlgoAPI_Cut(outer, inner).Shape();

  return well;
}


TopoDS_Shape create_three_way_well(const three_way_well_params &params) {
  // 参数验证
  if (params.length <= 0 || params.width <= 0 || params.height <= 0) {
    throw Standard_ConstructionError("Main well dimensions must be positive");
  }

  if (params.type == three_way_well_type::WORKING_WELL &&
      (params.topThickness <= 0 || params.bottomThickness <= 0)) {
    throw Standard_ConstructionError(
        "Working well must have positive top and bottom thickness");
  }
  switch (params.type) {
  case three_way_well_type::WORKING_WELL:
    return create_three_way_working_well(params);
  case three_way_well_type::OPEN_CUT_TUNNEL:
    return create_three_way_open_cut_tunnel(params);
  case three_way_well_type::UNDERGROUND_TUNNEL:
    return params.isDoubleShaft ? create_three_way_double_shaft_tunnel(params)
                                : create_three_way_underground_tunnel(params);
  default:
    return TopoDS_Shape();
  }
}


TopoDS_Shape create_three_way_well(const three_way_well_params &params,
                                   const gp_Pnt &position,
                                   const gp_Dir &mainDirection,
                                   const gp_Dir &branchDirection) {
  // 正交性校验
  if (Abs(mainDirection.Dot(branchDirection)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Main and branch directions must be perpendicular");
  }

  // 创建标准方向的三通井
  TopoDS_Shape well = create_three_way_well(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, mainDirection.Crossed(branchDirection),
                   mainDirection);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(well, transformation);
  return transform.Shape();
}


/**
 * @brief 创建四通圆角工作井
 * @param length 直通段长度(mm)
 * @param width 直通段宽度(mm)
 * @param height 直通段高度(mm)
 * @param length1 支线段长度(mm)
 * @param width1 支线段宽度(mm)
 * @param cornerRadius 井转角半径(mm)
 * @return 四通圆角工作井的形状
 */
TopoDS_Shape create_four_way_round_working_well_part(
    double length, double width, double height, double length1, double width1,
    double length2, double width2, double cornerRadius, double zoffset) {
  // 参数校验
  if (length <= 0 || width <= 0 || height <= 0 || length1 <= 0 || width1 <= 0 ||
      length2 <= 0 || width2 <= 0) {
    throw Standard_ConstructionError("尺寸参数必须为正数");
  }
  if (cornerRadius <= 0) {
    throw Standard_ConstructionError("圆角半径必须大于0");
  }

  // 1. 计算关键几何参数
  const double halfLength = length / 2;
  const double halfWidth = width / 2;
  const double halfWidth1 = width1 / 2;
  const double halfWidth2 = width2 / 2;

  // 2. 定义主直通段四个角点
  const gp_Pnt p1(-halfLength, -halfWidth, zoffset); // 左下角
  const gp_Pnt p2(-halfLength, halfWidth, zoffset);  // 左上角
  const gp_Pnt p3(halfLength, halfWidth, zoffset);   // 右上角
  const gp_Pnt p4(halfLength, -halfWidth, zoffset);  // 右下角

  // 3. 定义支线段端点
  const gp_Pnt p7(-halfWidth1, halfWidth + length1,
                  zoffset);                                  // 支线段左上角点
  const gp_Pnt p8(halfWidth1, halfWidth + length1, zoffset); // 支线段右下角点

  // 4. 定义支线段2端点（下方）
  const gp_Pnt p9(-halfWidth2, -halfWidth - length2,
                  zoffset); // 支线段2左下角点
  const gp_Pnt p10(halfWidth2, -halfWidth - length2,
                   zoffset); // 支线段2右下角点

  // 4. 计算圆弧关键点（精确几何关系）
  // 上方圆弧（连接直通段与支线段1）
  const gp_Pnt topRightArcStart(halfWidth1 + cornerRadius, halfWidth, zoffset);
  const gp_Pnt topRightArcEnd(halfWidth1, halfWidth + cornerRadius, zoffset);
  const gp_Pnt topLeftArcStart(-halfWidth1 - cornerRadius, halfWidth, zoffset);
  const gp_Pnt topLeftArcEnd(-halfWidth1, halfWidth + cornerRadius, zoffset);

  // 下方圆弧（连接直通段与支线段2）
  const gp_Pnt bottomRightArcStart(halfWidth2 + cornerRadius, -halfWidth,
                                   zoffset);
  const gp_Pnt bottomRightArcEnd(halfWidth2, -halfWidth - cornerRadius,
                                 zoffset);
  const gp_Pnt bottomLeftArcStart(-halfWidth2 - cornerRadius, -halfWidth,
                                  zoffset);
  const gp_Pnt bottomLeftArcEnd(-halfWidth2, -halfWidth - cornerRadius,
                                zoffset);

  // 6. 构造圆弧几何
  // 上方左圆弧
  gp_Pnt topLeftCircleCenter(-halfWidth1 - cornerRadius,
                             halfWidth + cornerRadius, zoffset);
  gp_Circ topLeftCircle(gp_Ax2(topLeftCircleCenter, gp_Dir(0, 0, 1)),
                        cornerRadius);
  TopoDS_Edge topLeftArc =
      BRepBuilderAPI_MakeEdge(new Geom_Circle(topLeftCircle),
                              ElCLib::Parameter(topLeftCircle, topLeftArcStart),
                              ElCLib::Parameter(topLeftCircle, topLeftArcEnd))
          .Edge();

  // 上方右圆弧
  gp_Pnt topRightCircleCenter(halfWidth1 + cornerRadius,
                              halfWidth + cornerRadius, zoffset);
  gp_Circ topRightCircle(gp_Ax2(topRightCircleCenter, gp_Dir(0, 0, 1)),
                         cornerRadius);
  TopoDS_Edge topRightArc =
      BRepBuilderAPI_MakeEdge(
          new Geom_Circle(topRightCircle),
          ElCLib::Parameter(topRightCircle, topRightArcEnd),
          ElCLib::Parameter(topRightCircle, topRightArcStart))
          .Edge();
  topRightArc.Reverse();

  // 下方左圆弧
  gp_Pnt bottomLeftCircleCenter(-halfWidth2 - cornerRadius,
                                -halfWidth - cornerRadius, zoffset);
  gp_Circ bottomLeftCircle(gp_Ax2(bottomLeftCircleCenter, gp_Dir(0, 0, -1)),
                           cornerRadius);
  TopoDS_Edge bottomLeftArc =
      BRepBuilderAPI_MakeEdge(
          new Geom_Circle(bottomLeftCircle),
          ElCLib::Parameter(bottomLeftCircle, bottomLeftArcStart),
          ElCLib::Parameter(bottomLeftCircle, bottomLeftArcEnd))
          .Edge();

  // 下方右圆弧
  gp_Pnt bottomRightCircleCenter(halfWidth2 + cornerRadius,
                                 -halfWidth - cornerRadius, zoffset);
  gp_Circ bottomRightCircle(gp_Ax2(bottomRightCircleCenter, gp_Dir(0, 0, -1)),
                            cornerRadius);
  TopoDS_Edge bottomRightArc =
      BRepBuilderAPI_MakeEdge(
          new Geom_Circle(bottomRightCircle),
          ElCLib::Parameter(bottomRightCircle, bottomRightArcEnd),
          ElCLib::Parameter(bottomRightCircle, bottomRightArcStart))
          .Edge();
  bottomRightArc.Reverse();

  // 7. 构建完整线框
  BRepBuilderAPI_MakeWire wireMaker;

  // 主直通段左侧边
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p1, p2));

  // 上方连接段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p2, topLeftArcStart));
  wireMaker.Add(topLeftArc);
  wireMaker.Add(BRepBuilderAPI_MakeEdge(topLeftArcEnd, p7));

  // 支线段1顶部
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p7, p8));

  // 上方右侧连接段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p8, topRightArcEnd));
  wireMaker.Add(topRightArc);
  wireMaker.Add(BRepBuilderAPI_MakeEdge(topRightArcStart, p3));

  // 主直通段右侧边
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p3, p4));

  // 下方右侧连接段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p4, bottomRightArcStart));
  wireMaker.Add(bottomRightArc);
  wireMaker.Add(BRepBuilderAPI_MakeEdge(bottomRightArcEnd, p10));

  // 支线段2底部
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p10, p9));

  // 下方左侧连接段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p9, bottomLeftArcEnd));
  wireMaker.Add(bottomLeftArc);
  wireMaker.Add(BRepBuilderAPI_MakeEdge(bottomLeftArcStart, p1));

  // 8. 创建底面并拉伸
  if (!wireMaker.IsDone()) {
    throw Standard_ConstructionError("线框构造失败");
  }
  TopoDS_Face face = BRepBuilderAPI_MakeFace(wireMaker.Wire());

  return BRepPrimAPI_MakePrism(face, gp_Vec(0, 0, height)).Shape();
}


/**
 * @brief 创建四通折角工作井
 * @param length 直通段长度(mm)
 * @param width 直通段宽度(mm)
 * @param height 直通段高度(mm)
 * @param length1 支线段长度(mm)
 * @param width1 支线段宽度(mm)
 * @param cornerLength 井转角折角长(mm)
 * @param cornerWidth 井转角折角宽(mm)
 * @param angle  井转角角度
 * @return 四通工作井的形状
 */
TopoDS_Shape create_four_way_corner_working_well_part(
    double length, double width, double height, double length1, double width1,
    double length2, double width2, double cornerLength, double cornerWidth,
    double zoffset) {
  // 参数校验
  if (length <= 0 || width <= 0 || height <= 0 || length1 <= 0 || width1 <= 0 ||
      length2 <= 0 || width2 <= 0) {
    throw Standard_ConstructionError("尺寸参数必须为正数");
  }
  if (length1 <= 0 || width1 <= 0) {
    throw Standard_ConstructionError("支线段尺寸参数必须为正数");
  }

  // 1. 计算关键几何参数
  const double halfLength = length / 2;
  const double halfWidth = width / 2;
  const double halfWidth1 = width1 / 2;
  const double halfWidth2 = width2 / 2;

  // 2. 定义主直通段四个角点
  const gp_Pnt p1(-halfLength, -halfWidth, zoffset); // 左下角
  const gp_Pnt p2(-halfLength, halfWidth, zoffset);  // 左上角
  const gp_Pnt p3(halfLength, halfWidth, zoffset);   // 右上角
  const gp_Pnt p4(halfLength, -halfWidth, zoffset);  // 右下角

  // 3. 定义支线段1端点（上方）
  const gp_Pnt p7(-halfWidth1, halfWidth + length1,
                  zoffset); // 支线段1左上角点
  const gp_Pnt p8(halfWidth1, halfWidth + length1,
                  zoffset); // 支线段1右下角点

  // 4. 定义支线段2端点（下方）
  const gp_Pnt p9(-halfWidth2, -halfWidth - length2,
                  zoffset); // 支线段2左下角点
  const gp_Pnt p10(halfWidth2, -halfWidth - length2,
                   zoffset); // 支线段2右下角点

  // 5. 定义转角连接点
  // 上方转角点
  const gp_Pnt topLeftStart(-halfWidth1 - cornerLength, halfWidth, zoffset);
  const gp_Pnt topLeftEnd(-halfWidth1, halfWidth + cornerWidth, zoffset);
  const gp_Pnt topRightStart(halfWidth1 + cornerLength, halfWidth, zoffset);
  const gp_Pnt topRightEnd(halfWidth1, halfWidth + cornerWidth, zoffset);

  // 下方转角点
  const gp_Pnt bottomLeftStart(-halfWidth2 - cornerLength, -halfWidth, zoffset);
  const gp_Pnt bottomLeftEnd(-halfWidth2, -halfWidth - cornerWidth, zoffset);
  const gp_Pnt bottomRightStart(halfWidth2 + cornerLength, -halfWidth, zoffset);
  const gp_Pnt bottomRightEnd(halfWidth2, -halfWidth - cornerWidth, zoffset);

  // 6. 构建完整线框
  BRepBuilderAPI_MakeWire wireMaker;

  // 主直通段左侧边
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p1, p2));

  // 上方连接段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p2, topLeftStart));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(topLeftStart, topLeftEnd));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(topLeftEnd, p7));

  // 支线段1顶部
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p7, p8));

  // 上方右侧连接段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p8, topRightEnd));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(topRightEnd, topRightStart));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(topRightStart, p3));

  // 主直通段右侧边
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p3, p4));

  // 下方右侧连接段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p4, bottomRightStart));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(bottomRightStart, bottomRightEnd));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(bottomRightEnd, p10));

  // 支线段2底部
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p10, p9));

  // 下方左侧连接段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p9, bottomLeftEnd));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(bottomLeftEnd, bottomLeftStart));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(bottomLeftStart, p1));

  // 7. 创建底面并拉伸
  if (!wireMaker.IsDone()) {
    throw Standard_ConstructionError("线框构造失败");
  }
  TopoDS_Face face = BRepBuilderAPI_MakeFace(wireMaker.Wire());

  return BRepPrimAPI_MakePrism(face, gp_Vec(0, 0, height)).Shape();
}


TopoDS_Shape create_four_way_working_well(const four_way_well_params &params) {
  if (params.type != four_way_well_type::WORKING_WELL) {
    throw Standard_ConstructionError("four_way_well_type must be WORKING_WELL");
  }
  TopoDS_Shape outer;
  switch (params.cornerStyle) {
  case corner_style::ROUNDED:
    outer = create_four_way_round_working_well_part(
        params.length, params.width + params.outerWallThickness * 2,
        params.height + params.topThickness + params.bottomThickness,
        params.branchLength, params.branchWidth + params.outerWallThickness * 2,
        params.branchLength, params.branchWidth + params.outerWallThickness * 2,
        params.cornerRadius - params.outerWallThickness,
        -params.bottomThickness);
    break;
  case corner_style::ANGLED:
    outer = create_four_way_corner_working_well_part(
        params.length, params.width + params.outerWallThickness * 2,
        params.height + params.topThickness + params.bottomThickness,
        params.branchLength, params.branchWidth + params.outerWallThickness * 2,
        params.branchLength, params.branchWidth + params.outerWallThickness * 2,
        params.cornerLength - params.outerWallThickness,
        params.cornerWidth - params.outerWallThickness,
        -params.bottomThickness);
    break;
  default:
    break;
  }

  TopoDS_Shape inner;
  switch (params.cornerStyle) {
  case corner_style::ROUNDED:
    inner = create_four_way_round_working_well_part(
        params.length + params.outerWallThickness * 2, params.width,
        params.height, params.branchLength + params.outerWallThickness * 2,
        params.branchWidth, params.branchLength + params.outerWallThickness * 2,
        params.branchWidth, params.cornerRadius, 0);
    break;
  case corner_style::ANGLED:
    inner = create_four_way_corner_working_well_part(
        params.length + params.outerWallThickness * 2, params.width,
        params.height, params.branchLength + params.outerWallThickness * 2,
        params.branchWidth, params.branchLength + params.outerWallThickness * 2,
        params.branchWidth, params.cornerLength, params.cornerWidth, 0);
    break;
  default:
    break;
  }

  TopoDS_Shape cushion;
  switch (params.cornerStyle) {
  case corner_style::ROUNDED:
    cushion = create_four_way_round_working_well_part(
        params.length,
        params.width + params.outerWallThickness * 2 +
            params.cushionExtension * 2,
        params.cushionThickness, params.branchLength,
        params.branchWidth + params.outerWallThickness * 2 +
            params.cushionExtension * 2,
        params.branchLength,
        params.branchWidth + params.outerWallThickness * 2 +
            params.cushionExtension * 2,
        params.cornerRadius - params.outerWallThickness -
            params.cushionExtension,
        -params.bottomThickness - params.cushionThickness);
    break;
  case corner_style::ANGLED:
    cushion = create_four_way_corner_working_well_part(
        params.length,
        params.width + params.outerWallThickness * 2 +
            params.cushionExtension * 2,
        params.cushionThickness, params.branchLength,
        params.branchWidth + params.outerWallThickness * 2 +
            params.cushionExtension * 2,
        params.branchLength,
        params.branchWidth + params.outerWallThickness * 2 +
            params.cushionExtension * 2,
        params.cornerLength + params.outerWallThickness +
            params.cushionExtension,
        params.cornerWidth + params.outerWallThickness +
            params.cushionExtension,
        -params.bottomThickness - params.cushionThickness);
    break;
  default:
    break;
  }

  // 合并所有部分
  TopoDS_Shape well = BRepAlgoAPI_Cut(outer, inner).Shape();

  well = BRepAlgoAPI_Fuse(well, cushion).Shape();

  return well;
}


TopoDS_Shape
create_four_way_open_cut_tunnel(const four_way_well_params &params) {
  if (params.type != four_way_well_type::OPEN_CUT_TUNNEL) {
    throw Standard_ConstructionError(
        "three_way_open_cut_tunnel must be OPEN_CUT_TUNNEL");
  }
  TopoDS_Shape outer;
  switch (params.cornerStyle) {
  case corner_style::ROUNDED:
    outer = create_four_way_round_working_well_part(
        params.length + params.outerWallThickness * 2,
        params.width + params.outerWallThickness * 2,
        params.height + params.topThickness + params.bottomThickness,
        params.branchLength + params.outerWallThickness * 2,
        params.branchWidth + params.outerWallThickness * 2,
        params.branchLength + params.outerWallThickness * 2,
        params.branchWidth + params.outerWallThickness * 2,
        params.cornerRadius - params.outerWallThickness,
        -params.bottomThickness);
    break;
  case corner_style::ANGLED:
    outer = create_four_way_corner_working_well_part(
        params.length + params.outerWallThickness * 2,
        params.width + params.outerWallThickness * 2,
        params.height + params.topThickness + params.bottomThickness,
        params.branchLength + params.outerWallThickness * 2,
        params.branchWidth + params.outerWallThickness * 2,
        params.branchLength + params.outerWallThickness * 2,
        params.branchWidth + params.outerWallThickness * 2,
        params.cornerLength - params.outerWallThickness,
        params.cornerWidth - params.outerWallThickness,
        -params.bottomThickness);
    break;
  default:
    break;
  }

  // 2. 创建左连接段
  TopoDS_Shape leftTunnel;
  switch (params.leftSection.sectionType) {
  case connection_section_style::RECTANGULAR:
    leftTunnel = create_rectangular_section(
        params.leftSection.length, params.leftSection.width,
        params.leftSection.height, params.outerWallThickness,
        params.topThickness, params.bottomThickness, true);
    break;
  case connection_section_style::HORSESHOE:
    leftTunnel = create_horseshoe_section(
        params.leftSection.length, params.leftSection.width,
        params.leftSection.height, params.leftSection.arcHeight,
        params.outerWallThickness, true);
    break;
  case connection_section_style::CIRCULAR:
    leftTunnel = create_circular_section(params.leftSection.length,
                                         params.leftSection.height / 2,
                                         params.outerWallThickness, true);
    break;
  }

  // 移动左连接段到正确位置
  gp_Trsf leftTrsf;
  leftTrsf.SetTranslation(
      gp_Vec(-params.leftSection.length - params.length / 2, 0, 0));
  leftTunnel = BRepBuilderAPI_Transform(leftTunnel, leftTrsf).Shape();

  outer = BRepAlgoAPI_Fuse(outer, leftTunnel).Shape();

  // 3. 创建右连接段
  TopoDS_Shape rightTunnel;
  switch (params.rightSection.sectionType) {
  case connection_section_style::RECTANGULAR:
    rightTunnel = create_rectangular_section(
        params.rightSection.length, params.rightSection.width,
        params.rightSection.height, params.outerWallThickness,
        params.topThickness, params.bottomThickness, true);
    break;
  case connection_section_style::HORSESHOE:
    rightTunnel = create_horseshoe_section(
        params.rightSection.length, params.rightSection.width,
        params.rightSection.height, params.rightSection.arcHeight,
        params.outerWallThickness, true);
    break;
  case connection_section_style::CIRCULAR:
    rightTunnel = create_circular_section(params.rightSection.length,
                                          params.rightSection.height / 2,
                                          params.outerWallThickness, true);
    break;
  }

  // 移动支连接段到正确位置
  gp_Trsf rightTrsf;
  rightTrsf.SetTranslation(gp_Vec(params.length / 2, 0, 0));
  rightTunnel = BRepBuilderAPI_Transform(rightTunnel, rightTrsf).Shape();

  outer = BRepAlgoAPI_Fuse(outer, rightTunnel).Shape();

  // 3. 创建上支连接段
  TopoDS_Shape branch1Tunnel;
  switch (params.branchSection1.sectionType) {
  case connection_section_style::RECTANGULAR:
    branch1Tunnel = create_rectangular_section(
        params.branchSection1.length, params.branchSection1.width,
        params.branchSection1.height, params.outerWallThickness,
        params.topThickness, params.bottomThickness, true);
    break;
  case connection_section_style::HORSESHOE:
    branch1Tunnel = create_horseshoe_section(
        params.branchSection1.length, params.branchSection1.width,
        params.branchSection1.height, params.branchSection1.arcHeight,
        params.outerWallThickness, true);
    break;
  case connection_section_style::CIRCULAR:
    branch1Tunnel = create_circular_section(params.branchSection1.length,
                                            params.branchSection1.height / 2,
                                            params.outerWallThickness, true);
    break;
  }

  // 移动上连接段到正确位置
  gp_Trsf branch1Trsf;
  gp_Trsf branch1Model;
  branch1Model.SetTranslation(gp_Vec(-params.branchSection1.length / 2, 0, 0));
  gp_Trsf rotate1Trsf;
  rotate1Trsf.SetRotation(gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(0, 0, -1)),
                          90 * M_PI / 180.0);

  branch1Trsf.SetTranslation(gp_Vec(0,
                                    params.branchLength + params.width / 2 +
                                        params.branchSection1.length / 2,
                                    0));
  branch1Tunnel = BRepBuilderAPI_Transform(branch1Tunnel, branch1Model).Shape();
  branch1Tunnel = BRepBuilderAPI_Transform(branch1Tunnel, rotate1Trsf).Shape();
  branch1Tunnel = BRepBuilderAPI_Transform(branch1Tunnel, branch1Trsf).Shape();

  outer = BRepAlgoAPI_Fuse(outer, branch1Tunnel).Shape();

  // 4. 创建下支连接段
  TopoDS_Shape branch2Tunnel;
  switch (params.branchSection2.sectionType) {
  case connection_section_style::RECTANGULAR:
    branch2Tunnel = create_rectangular_section(
        params.branchSection2.length, params.branchSection2.width,
        params.branchSection2.height, params.outerWallThickness,
        params.topThickness, params.bottomThickness, true);
    break;
  case connection_section_style::HORSESHOE:
    branch2Tunnel = create_horseshoe_section(
        params.branchSection2.length, params.branchSection2.width,
        params.branchSection2.height, params.branchSection2.arcHeight,
        params.outerWallThickness, true);
    break;
  case connection_section_style::CIRCULAR:
    branch2Tunnel = create_circular_section(params.branchSection2.length,
                                            params.branchSection2.height / 2,
                                            params.outerWallThickness, true);
    break;
  }

  // 移动上连接段到正确位置
  gp_Trsf branch2Trsf;
  gp_Trsf branch2Model;
  branch2Model.SetTranslation(gp_Vec(-params.branchSection2.length / 2, 0, 0));
  gp_Trsf rotate2Trsf;
  rotate2Trsf.SetRotation(gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(0, 0, -1)),
                          -90 * M_PI / 180.0);

  branch2Trsf.SetTranslation(gp_Vec(0,
                                    -params.branchLength - params.width / 2 -
                                        params.branchSection2.length / 2,
                                    0));
  branch2Tunnel = BRepBuilderAPI_Transform(branch2Tunnel, branch2Model).Shape();
  branch2Tunnel = BRepBuilderAPI_Transform(branch2Tunnel, rotate2Trsf).Shape();
  branch2Tunnel = BRepBuilderAPI_Transform(branch2Tunnel, branch2Trsf).Shape();

  outer = BRepAlgoAPI_Fuse(outer, branch2Tunnel).Shape();

  TopoDS_Shape inner;
  switch (params.cornerStyle) {
  case corner_style::ROUNDED:
    inner = create_four_way_round_working_well_part(
        params.length + params.outerWallThickness * 2, params.width,
        params.height, params.branchLength + params.outerWallThickness * 2,
        params.branchWidth, params.branchLength + params.outerWallThickness * 2,
        params.branchWidth, params.cornerRadius, 0);
    break;
  case corner_style::ANGLED:
    inner = create_four_way_corner_working_well_part(
        params.length + params.outerWallThickness * 2, params.width,
        params.height, params.branchLength + params.outerWallThickness * 2,
        params.branchWidth, params.branchLength + params.outerWallThickness * 2,
        params.branchWidth, params.cornerLength, params.cornerWidth, 0);
    break;
  default:
    break;
  }

  TopoDS_Shape innerLeftTunnel;
  switch (params.leftSection.sectionType) {
  case connection_section_style::RECTANGULAR:
    innerLeftTunnel = create_rectangular_section(
        params.leftSection.length - params.outerWallThickness,
        params.leftSection.width, params.leftSection.height,
        params.outerWallThickness, params.topThickness, params.bottomThickness,
        false);
    break;
  case connection_section_style::HORSESHOE:
    innerLeftTunnel = create_horseshoe_section(
        params.leftSection.length - params.outerWallThickness,
        params.leftSection.width, params.leftSection.height,
        params.leftSection.arcHeight, params.outerWallThickness, false);
    break;
  case connection_section_style::CIRCULAR:
    innerLeftTunnel = create_circular_section(
        params.leftSection.length - params.outerWallThickness,
        params.leftSection.height / 2, params.outerWallThickness, false);
    break;
  }

  innerLeftTunnel = BRepBuilderAPI_Transform(innerLeftTunnel, leftTrsf).Shape();

  inner = BRepAlgoAPI_Fuse(inner, innerLeftTunnel).Shape();

  TopoDS_Shape innerRightTunnel;
  switch (params.rightSection.sectionType) {
  case connection_section_style::RECTANGULAR:
    innerRightTunnel = create_rectangular_section(
        params.rightSection.length - params.outerWallThickness,
        params.rightSection.width, params.rightSection.height,
        params.outerWallThickness, params.topThickness, params.bottomThickness,
        false);
    break;
  case connection_section_style::HORSESHOE:
    innerRightTunnel = create_horseshoe_section(
        params.rightSection.length - params.outerWallThickness,
        params.rightSection.width, params.rightSection.height,
        params.rightSection.arcHeight, params.outerWallThickness, false);
    break;
  case connection_section_style::CIRCULAR:
    innerRightTunnel = create_circular_section(
        params.rightSection.length - params.outerWallThickness,
        params.rightSection.height / 2, params.outerWallThickness, false);
    break;
  }

  rightTrsf.SetTranslation(
      gp_Vec(params.length / 2 + params.outerWallThickness, 0, 0));
  innerRightTunnel =
      BRepBuilderAPI_Transform(innerRightTunnel, rightTrsf).Shape();

  inner = BRepAlgoAPI_Fuse(inner, innerRightTunnel).Shape();

  // 3. 创建上连接段
  TopoDS_Shape innerBranch1Tunnel;
  switch (params.branchSection1.sectionType) {
  case connection_section_style::RECTANGULAR:
    innerBranch1Tunnel = create_rectangular_section(
        params.branchSection1.length - params.outerWallThickness,
        params.branchSection1.width, params.branchSection1.height,
        params.outerWallThickness, params.topThickness, params.bottomThickness,
        false);
    break;
  case connection_section_style::HORSESHOE:
    innerBranch1Tunnel = create_horseshoe_section(
        params.branchSection1.length - params.outerWallThickness,
        params.branchSection1.width, params.branchSection1.height,
        params.branchSection1.arcHeight, params.outerWallThickness, false);
    break;
  case connection_section_style::CIRCULAR:
    innerBranch1Tunnel = create_circular_section(
        params.branchSection1.length - params.outerWallThickness,
        params.branchSection1.height / 2, params.outerWallThickness, false);
    break;
  }

  branch1Model.SetTranslation(gp_Vec(
      -(params.branchSection1.length - params.outerWallThickness) / 2, 0, 0));
  branch1Trsf.SetTranslation(gp_Vec(0,
                                    params.branchLength + params.width / 2 +
                                        params.branchSection1.length / 2 +
                                        params.outerWallThickness +
                                        params.outerWallThickness / 2,
                                    0));
  innerBranch1Tunnel =
      BRepBuilderAPI_Transform(innerBranch1Tunnel, branch1Model).Shape();
  innerBranch1Tunnel =
      BRepBuilderAPI_Transform(innerBranch1Tunnel, rotate1Trsf).Shape();
  innerBranch1Tunnel =
      BRepBuilderAPI_Transform(innerBranch1Tunnel, branch1Trsf).Shape();

  inner = BRepAlgoAPI_Fuse(inner, innerBranch1Tunnel).Shape();

  // 4. 创建下连接段
  TopoDS_Shape innerBranch2Tunnel;
  switch (params.branchSection2.sectionType) {
  case connection_section_style::RECTANGULAR:
    innerBranch2Tunnel = create_rectangular_section(
        params.branchSection2.length - params.outerWallThickness,
        params.branchSection2.width, params.branchSection2.height,
        params.outerWallThickness, params.topThickness, params.bottomThickness,
        false);
    break;
  case connection_section_style::HORSESHOE:
    innerBranch2Tunnel = create_horseshoe_section(
        params.branchSection2.length - params.outerWallThickness,
        params.branchSection2.width, params.branchSection2.height,
        params.branchSection2.arcHeight, params.outerWallThickness, false);
    break;
  case connection_section_style::CIRCULAR:
    innerBranch2Tunnel = create_circular_section(
        params.branchSection2.length - params.outerWallThickness,
        params.branchSection2.height / 2, params.outerWallThickness, false);
    break;
  }

  branch2Model.SetTranslation(gp_Vec(
      -(params.branchSection2.length - params.outerWallThickness) / 2, 0, 0));
  branch2Trsf.SetTranslation(gp_Vec(0,
                                    -params.branchLength - params.width / 2 -
                                        params.branchSection2.length / 2 -
                                        params.outerWallThickness -
                                        params.outerWallThickness / 2,
                                    0));
  innerBranch2Tunnel =
      BRepBuilderAPI_Transform(innerBranch2Tunnel, branch2Model).Shape();
  innerBranch2Tunnel =
      BRepBuilderAPI_Transform(innerBranch2Tunnel, rotate2Trsf).Shape();
  innerBranch2Tunnel =
      BRepBuilderAPI_Transform(innerBranch2Tunnel, branch2Trsf).Shape();

  inner = BRepAlgoAPI_Fuse(inner, innerBranch2Tunnel).Shape();

  TopoDS_Shape cushion;
  switch (params.cornerStyle) {
  case corner_style::ROUNDED:
    cushion = create_four_way_round_working_well_part(
        params.length + params.leftSection.length + params.rightSection.length,
        params.width + params.outerWallThickness * 2 +
            params.cushionExtension * 2,
        params.cushionThickness,
        params.branchLength + params.branchSection1.length,
        params.branchWidth + params.outerWallThickness * 2 +
            params.cushionExtension * 2,
        params.branchLength + params.branchSection2.length,
        params.branchWidth + params.outerWallThickness * 2 +
            params.cushionExtension * 2,
        params.cornerRadius - params.outerWallThickness -
            params.cushionExtension,
        -params.bottomThickness - params.cushionThickness);
    break;
  case corner_style::ANGLED:
    cushion = create_four_way_corner_working_well_part(
        params.length + params.leftSection.length + params.rightSection.length,
        params.width + params.outerWallThickness * 2 +
            params.cushionExtension * 2,
        params.cushionThickness,
        params.branchLength + params.branchSection1.length,
        params.branchWidth + params.outerWallThickness * 2 +
            params.cushionExtension * 2,
        params.branchLength + params.branchSection2.length,
        params.branchWidth + params.outerWallThickness * 2 +
            params.cushionExtension * 2,
        params.cornerLength + params.outerWallThickness +
            params.cushionExtension,
        params.cornerWidth + params.outerWallThickness +
            params.cushionExtension,
        -params.bottomThickness - params.cushionThickness);
    break;
  default:
    break;
  }

  // 合并所有部分
  TopoDS_Shape well = BRepAlgoAPI_Cut(outer, inner).Shape();

  well = BRepAlgoAPI_Fuse(well, cushion).Shape();

  return well;
}


TopoDS_Shape create_four_way_circle_well_part(double length, double width,
                                              double height, double length1,
                                              double width1, double length2,
                                              double width2, double wellRadius,
                                              double weelheight,
                                              double zoffset) {
  // 参数校验
  if (length <= 0 || width <= 0 || height <= 0 || length1 <= 0 || width1 <= 0 ||
      length2 <= 0 || width2 <= 0) {
    throw Standard_ConstructionError("尺寸参数必须为正数");
  }

  // 1. 计算关键几何参数
  const double halfLength = length / 2;
  const double halfWidth = width / 2;
  const double halfWidth1 = width1 / 2;
  const double halfWidth2 = width2 / 2;

  // 2. 定义主直通段四个角点
  const gp_Pnt p1(-halfLength, -halfWidth, zoffset); // 左下角
  const gp_Pnt p2(-halfLength, halfWidth, zoffset);  // 左上角
  const gp_Pnt p3(halfLength, halfWidth, zoffset);   // 右上角
  const gp_Pnt p4(halfLength, -halfWidth, zoffset);  // 右下角

  // 3. 定义支线段1端点（上方）
  const gp_Pnt p7(-halfWidth1, halfWidth + length1,
                  zoffset); // 支线段1左上角点
  const gp_Pnt p8(halfWidth1, halfWidth + length1,
                  zoffset);                         // 支线段1右下角点
  const gp_Pnt p9(-halfWidth1, halfWidth, zoffset); // 支线段1左下角点
  const gp_Pnt p10(halfWidth1, halfWidth, zoffset); // 支线段1右下角点

  // 4. 定义支线段2端点（下方）
  const gp_Pnt p11(-halfWidth2, -halfWidth - length2,
                   zoffset); // 支线段2左下角点
  const gp_Pnt p12(halfWidth2, -halfWidth - length2,
                   zoffset);                          // 支线段2右下角点
  const gp_Pnt p13(-halfWidth2, -halfWidth, zoffset); // 支线段2左上角点
  const gp_Pnt p14(halfWidth2, -halfWidth, zoffset);  // 支线段2右上角点

  // 5. 构建完整线框
  BRepBuilderAPI_MakeWire wireMaker;

  // 主直通段左侧边
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p1, p2));

  // 上方连接段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p2, p9));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p9, p7));

  // 支线段1顶部
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p7, p8));

  // 上方右侧连接段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p8, p10));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p10, p3));

  // 主直通段右侧边
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p3, p4));

  // 下方右侧连接段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p4, p14));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p14, p12));

  // 支线段2底部
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p12, p11));

  // 下方左侧连接段
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p11, p13));
  wireMaker.Add(BRepBuilderAPI_MakeEdge(p13, p1));

  // 6. 创建底面并拉伸
  if (!wireMaker.IsDone()) {
    throw Standard_ConstructionError("线框构造失败");
  }
  TopoDS_Face face = BRepBuilderAPI_MakeFace(wireMaker.Wire());

  TopoDS_Shape tunnel =
      BRepPrimAPI_MakePrism(face, gp_Vec(0, 0, height)).Shape();

  // 创建竖井
  gp_Ax2 wellAxis(gp_Pnt(0, 0, zoffset), gp::DZ());
  TopoDS_Shape well =
      BRepPrimAPI_MakeCylinder(wellAxis, wellRadius, weelheight).Shape();

  return BRepAlgoAPI_Fuse(tunnel, well).Shape();
}


TopoDS_Shape
create_four_way_underground_tunnel(const four_way_well_params &params) {
  if (params.type != four_way_well_type::UNDERGROUND_TUNNEL) {
    throw Standard_ConstructionError(
        "four_way_underground_tunnel must be UNDERGROUND_TUNNEL");
  }
  TopoDS_Shape outer;
  outer = create_four_way_circle_well_part(
      params.length + params.outerWallThickness * 2,
      params.width + params.outerWallThickness * 2,
      params.height + params.outerWallThickness * 2,
      params.branchLength + params.outerWallThickness * 2,
      params.branchWidth + params.outerWallThickness * 2,
      params.branchLength + params.outerWallThickness * 2,
      params.branchWidth + params.outerWallThickness * 2,
      params.shaftRadius + params.outerWallThickness +
          params.innerWallThickness,
      params.height + params.outerWallThickness * 2,
      -params.outerWallThickness);

  // 2. 创建左连接段
  TopoDS_Shape leftTunnel;
  switch (params.leftSection.sectionType) {
  case connection_section_style::RECTANGULAR:
    leftTunnel = create_rectangular_section(
        params.leftSection.length, params.leftSection.width,
        params.leftSection.height, params.outerWallThickness,
        params.topThickness, params.bottomThickness, true);
    break;
  case connection_section_style::HORSESHOE:
    leftTunnel = create_horseshoe_section(
        params.leftSection.length, params.leftSection.width,
        params.leftSection.height, params.leftSection.arcHeight,
        params.outerWallThickness, true);
    break;
  case connection_section_style::CIRCULAR:
    leftTunnel = create_circular_section(params.leftSection.length,
                                         params.leftSection.height / 2,
                                         params.outerWallThickness, true);
    break;
  }

  // 移动左连接段到正确位置
  gp_Trsf leftTrsf;
  leftTrsf.SetTranslation(
      gp_Vec(-params.leftSection.length - params.length / 2, 0, 0));
  leftTunnel = BRepBuilderAPI_Transform(leftTunnel, leftTrsf).Shape();

  outer = BRepAlgoAPI_Fuse(outer, leftTunnel).Shape();

  // 3. 创建右连接段
  TopoDS_Shape rightTunnel;
  switch (params.rightSection.sectionType) {
  case connection_section_style::RECTANGULAR:
    rightTunnel = create_rectangular_section(
        params.rightSection.length, params.rightSection.width,
        params.rightSection.height, params.outerWallThickness,
        params.topThickness, params.bottomThickness, true);
    break;
  case connection_section_style::HORSESHOE:
    rightTunnel = create_horseshoe_section(
        params.rightSection.length, params.rightSection.width,
        params.rightSection.height, params.rightSection.arcHeight,
        params.outerWallThickness, true);
    break;
  case connection_section_style::CIRCULAR:
    rightTunnel = create_circular_section(params.rightSection.length,
                                          params.rightSection.height / 2,
                                          params.outerWallThickness, true);
    break;
  }

  // 移动支连接段到正确位置
  gp_Trsf rightTrsf;
  rightTrsf.SetTranslation(gp_Vec(params.length / 2, 0, 0));
  rightTunnel = BRepBuilderAPI_Transform(rightTunnel, rightTrsf).Shape();

  outer = BRepAlgoAPI_Fuse(outer, rightTunnel).Shape();

  // 3. 创建上支连接段
  TopoDS_Shape branch1Tunnel;
  switch (params.branchSection1.sectionType) {
  case connection_section_style::RECTANGULAR:
    branch1Tunnel = create_rectangular_section(
        params.branchSection1.length, params.branchSection1.width,
        params.branchSection1.height, params.outerWallThickness,
        params.topThickness, params.bottomThickness, true);
    break;
  case connection_section_style::HORSESHOE:
    branch1Tunnel = create_horseshoe_section(
        params.branchSection1.length, params.branchSection1.width,
        params.branchSection1.height, params.branchSection1.arcHeight,
        params.outerWallThickness, true);
    break;
  case connection_section_style::CIRCULAR:
    branch1Tunnel = create_circular_section(params.branchSection1.length,
                                            params.branchSection1.height / 2,
                                            params.outerWallThickness, true);
    break;
  }

  // 移动上连接段到正确位置
  gp_Trsf branch1Trsf;
  gp_Trsf branch1Model;
  branch1Model.SetTranslation(gp_Vec(-params.branchSection1.length / 2, 0, 0));
  gp_Trsf rotate1Trsf;
  rotate1Trsf.SetRotation(gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(0, 0, -1)),
                          90 * M_PI / 180.0);

  branch1Trsf.SetTranslation(gp_Vec(0,
                                    params.branchLength + params.width / 2 +
                                        params.branchSection1.length / 2,
                                    0));
  branch1Tunnel = BRepBuilderAPI_Transform(branch1Tunnel, branch1Model).Shape();
  branch1Tunnel = BRepBuilderAPI_Transform(branch1Tunnel, rotate1Trsf).Shape();
  branch1Tunnel = BRepBuilderAPI_Transform(branch1Tunnel, branch1Trsf).Shape();

  outer = BRepAlgoAPI_Fuse(outer, branch1Tunnel).Shape();

  // 4. 创建下支连接段
  TopoDS_Shape branch2Tunnel;
  switch (params.branchSection2.sectionType) {
  case connection_section_style::RECTANGULAR:
    branch2Tunnel = create_rectangular_section(
        params.branchSection2.length, params.branchSection2.width,
        params.branchSection2.height, params.outerWallThickness,
        params.topThickness, params.bottomThickness, true);
    break;
  case connection_section_style::HORSESHOE:
    branch2Tunnel = create_horseshoe_section(
        params.branchSection2.length, params.branchSection2.width,
        params.branchSection2.height, params.branchSection2.arcHeight,
        params.outerWallThickness, true);
    break;
  case connection_section_style::CIRCULAR:
    branch2Tunnel = create_circular_section(params.branchSection2.length,
                                            params.branchSection2.height / 2,
                                            params.outerWallThickness, true);
    break;
  }

  // 移动上连接段到正确位置
  gp_Trsf branch2Trsf;
  gp_Trsf branch2Model;
  branch2Model.SetTranslation(gp_Vec(-params.branchSection2.length / 2, 0, 0));
  gp_Trsf rotate2Trsf;
  rotate2Trsf.SetRotation(gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(0, 0, -1)),
                          -90 * M_PI / 180.0);

  branch2Trsf.SetTranslation(gp_Vec(0,
                                    -params.branchLength - params.width / 2 -
                                        params.branchSection2.length / 2,
                                    0));
  branch2Tunnel = BRepBuilderAPI_Transform(branch2Tunnel, branch2Model).Shape();
  branch2Tunnel = BRepBuilderAPI_Transform(branch2Tunnel, rotate2Trsf).Shape();
  branch2Tunnel = BRepBuilderAPI_Transform(branch2Tunnel, branch2Trsf).Shape();

  outer = BRepAlgoAPI_Fuse(outer, branch2Tunnel).Shape();

  TopoDS_Shape inner;
  inner = create_four_way_circle_well_part(
      params.length + params.outerWallThickness * 2, params.width,
      params.height, params.branchLength + params.outerWallThickness * 2,
      params.branchWidth, params.branchLength + params.outerWallThickness * 2,
      params.branchWidth, params.shaftRadius,
      params.height + params.outerWallThickness * 2, 0);

  TopoDS_Shape innerLeftTunnel;
  switch (params.leftSection.sectionType) {
  case connection_section_style::RECTANGULAR:
    innerLeftTunnel = create_rectangular_section(
        params.leftSection.length - params.outerWallThickness,
        params.leftSection.width, params.leftSection.height,
        params.outerWallThickness, params.topThickness, params.bottomThickness,
        false);
    break;
  case connection_section_style::HORSESHOE:
    innerLeftTunnel = create_horseshoe_section(
        params.leftSection.length - params.outerWallThickness,
        params.leftSection.width, params.leftSection.height,
        params.leftSection.arcHeight, params.outerWallThickness, false);
    break;
  case connection_section_style::CIRCULAR:
    innerLeftTunnel = create_circular_section(
        params.leftSection.length - params.outerWallThickness,
        params.leftSection.height / 2, params.outerWallThickness, false);
    break;
  }

  innerLeftTunnel = BRepBuilderAPI_Transform(innerLeftTunnel, leftTrsf).Shape();

  inner = BRepAlgoAPI_Fuse(inner, innerLeftTunnel).Shape();

  TopoDS_Shape innerRightTunnel;
  switch (params.rightSection.sectionType) {
  case connection_section_style::RECTANGULAR:
    innerRightTunnel = create_rectangular_section(
        params.rightSection.length - params.outerWallThickness,
        params.rightSection.width, params.rightSection.height,
        params.outerWallThickness, params.topThickness, params.bottomThickness,
        false);
    break;
  case connection_section_style::HORSESHOE:
    innerRightTunnel = create_horseshoe_section(
        params.rightSection.length - params.outerWallThickness,
        params.rightSection.width, params.rightSection.height,
        params.rightSection.arcHeight, params.outerWallThickness, false);
    break;
  case connection_section_style::CIRCULAR:
    innerRightTunnel = create_circular_section(
        params.rightSection.length - params.outerWallThickness,
        params.rightSection.height / 2, params.outerWallThickness, false);
    break;
  }

  rightTrsf.SetTranslation(
      gp_Vec(params.length / 2 + params.outerWallThickness, 0, 0));
  innerRightTunnel =
      BRepBuilderAPI_Transform(innerRightTunnel, rightTrsf).Shape();

  inner = BRepAlgoAPI_Fuse(inner, innerRightTunnel).Shape();

  // 3. 创建上连接段
  TopoDS_Shape innerBranch1Tunnel;
  switch (params.branchSection1.sectionType) {
  case connection_section_style::RECTANGULAR:
    innerBranch1Tunnel = create_rectangular_section(
        params.branchSection1.length - params.outerWallThickness,
        params.branchSection1.width, params.branchSection1.height,
        params.outerWallThickness, params.topThickness, params.bottomThickness,
        false);
    break;
  case connection_section_style::HORSESHOE:
    innerBranch1Tunnel = create_horseshoe_section(
        params.branchSection1.length - params.outerWallThickness,
        params.branchSection1.width, params.branchSection1.height,
        params.branchSection1.arcHeight, params.outerWallThickness, false);
    break;
  case connection_section_style::CIRCULAR:
    innerBranch1Tunnel = create_circular_section(
        params.branchSection1.length - params.outerWallThickness,
        params.branchSection1.height / 2, params.outerWallThickness, false);
    break;
  }

  branch1Model.SetTranslation(gp_Vec(
      -(params.branchSection1.length - params.outerWallThickness) / 2, 0, 0));
  branch1Trsf.SetTranslation(gp_Vec(0,
                                    params.branchLength + params.width / 2 +
                                        params.branchSection1.length / 2 +
                                        params.outerWallThickness +
                                        params.outerWallThickness / 2,
                                    0));
  innerBranch1Tunnel =
      BRepBuilderAPI_Transform(innerBranch1Tunnel, branch1Model).Shape();
  innerBranch1Tunnel =
      BRepBuilderAPI_Transform(innerBranch1Tunnel, rotate1Trsf).Shape();
  innerBranch1Tunnel =
      BRepBuilderAPI_Transform(innerBranch1Tunnel, branch1Trsf).Shape();

  inner = BRepAlgoAPI_Fuse(inner, innerBranch1Tunnel).Shape();

  // 4. 创建下连接段
  TopoDS_Shape innerBranch2Tunnel;
  switch (params.branchSection2.sectionType) {
  case connection_section_style::RECTANGULAR:
    innerBranch2Tunnel = create_rectangular_section(
        params.branchSection2.length - params.outerWallThickness,
        params.branchSection2.width, params.branchSection2.height,
        params.outerWallThickness, params.topThickness, params.bottomThickness,
        false);
    break;
  case connection_section_style::HORSESHOE:
    innerBranch2Tunnel = create_horseshoe_section(
        params.branchSection2.length - params.outerWallThickness,
        params.branchSection2.width, params.branchSection2.height,
        params.branchSection2.arcHeight, params.outerWallThickness, false);
    break;
  case connection_section_style::CIRCULAR:
    innerBranch2Tunnel = create_circular_section(
        params.branchSection2.length - params.outerWallThickness,
        params.branchSection2.height / 2, params.outerWallThickness, false);
    break;
  }

  branch2Model.SetTranslation(gp_Vec(
      -(params.branchSection2.length - params.outerWallThickness) / 2, 0, 0));
  branch2Trsf.SetTranslation(gp_Vec(0,
                                    -params.branchLength - params.width / 2 -
                                        params.branchSection2.length / 2 -
                                        params.outerWallThickness -
                                        params.outerWallThickness / 2,
                                    0));
  innerBranch2Tunnel =
      BRepBuilderAPI_Transform(innerBranch2Tunnel, branch2Model).Shape();
  innerBranch2Tunnel =
      BRepBuilderAPI_Transform(innerBranch2Tunnel, rotate2Trsf).Shape();
  innerBranch2Tunnel =
      BRepBuilderAPI_Transform(innerBranch2Tunnel, branch2Trsf).Shape();

  inner = BRepAlgoAPI_Fuse(inner, innerBranch2Tunnel).Shape();

  // 合并所有部分
  TopoDS_Shape well = BRepAlgoAPI_Cut(outer, inner).Shape();

  return well;
}


TopoDS_Shape create_four_way_well(const four_way_well_params &params) {
  // 参数验证
  if (params.length <= 0 || params.width <= 0 || params.height <= 0) {
    throw Standard_ConstructionError(
        "Length, width and height must be positive");
  }
  switch (params.type) {
  case four_way_well_type::WORKING_WELL:
    return create_four_way_working_well(params);
  case four_way_well_type::OPEN_CUT_TUNNEL:
    return create_four_way_open_cut_tunnel(params);
  case four_way_well_type::UNDERGROUND_TUNNEL:
    return create_four_way_underground_tunnel(params);
  default:
    break;
  }
  throw Standard_ConstructionError("Unsupported four_way_well_type");
}


TopoDS_Shape create_four_way_well(const four_way_well_params &params,
                                  const gp_Pnt &position,
                                  const gp_Dir &direction,
                                  const gp_Dir &xDirection) {
  // 正交性校验
  if (Abs(direction.Dot(xDirection)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Direction and xDirection must be perpendicular");
  }

  // 创建标准方向的四通井
  TopoDS_Shape junction = create_four_way_well(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, direction, xDirection);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(junction, transformation);
  return transform.Shape();
}


// 辅助函数：创建拉管截面
TopoDS_Compound create_pull_pipe_section(const pipe_row_params &params) {
  BRepBuilderAPI_MakeWire outerMaker;

  bool hasArc = false;

  // 创建路径线框
  BRepBuilderAPI_MakeWire pathWire;

  // 处理点序列
  for (size_t i = 0; i < params.points.size() - 1; i++) {
    const gp_Pnt &current = params.points[i].position;
    const gp_Pnt &next = params.points[i + 1].position;

    if (params.points[i].type == channel_point_type::LINE &&
        params.points[i + 1].type == channel_point_type::LINE) { // 普通节点
      // 创建直线段
      pathWire.Add(BRepBuilderAPI_MakeEdge(current, next).Edge());
    } else if (params.points[i].type == channel_point_type::ARC) { // 弧形节点
      // 确保有前一个点和后一个点
      if (i == 0 || i == params.points.size() - 1) {
        throw Standard_ConstructionError("弧形节点需要前后都有节点");
      }

      const gp_Pnt &prev = params.points[i - 1].position;

      // 创建三点圆弧
      pathWire.Add(BRepBuilderAPI_MakeEdge(
                       GC_MakeArcOfCircle(prev, current, next).Value())
                       .Edge());
      hasArc = true;
    }
  }

  if (!pathWire.IsDone()) {
    throw Standard_ConstructionError("路径线框创建失败");
  }

  TopoDS_Wire path = pathWire.Wire();

  // 获取路径起始点的切线方向
  BRepAdaptor_CompCurve curveAdaptor(path);
  gp_Pnt startPoint;
  gp_Vec startTangent;
  curveAdaptor.D1(curveAdaptor.FirstParameter(), startPoint, startTangent);

  // 在创建截面圆之前添加方向修正
  gp_Dir tanDir = startTangent.Normalized();
  gp_Dir refDir = gp::DZ(); // 默认参考方向为全局Y轴

  // 如果tanDir平行于全局X轴，调整参考方向为全局Z轴
  if (IsParallel(tanDir, gp::DX())) {
    refDir = gp::DZ();
  }
  gp_Ax2 sectionAxes(startPoint, tanDir, refDir);

  // 创建变换对象
  gp_Trsf trsf;
  trsf.SetTransformation(sectionAxes, gp_Ax2(gp::Origin(), gp::DZ()));

  // 创建外管圆
  gp_Circ outerCircle(gp_Ax2(gp::Origin(), gp::DX()),
                      params.pullPipeInnerDiameter / 2 +
                          params.pullPipeThickness);
  outerMaker.Add(BRepBuilderAPI_MakeEdge(outerCircle).Edge());

  BRepBuilderAPI_MakeWire innerMaker;

  // 创建内管圆（挖空）
  gp_Circ innerCircle(gp_Ax2(gp::Origin(), gp::DX()),
                      params.pullPipeInnerDiameter / 2);
  innerMaker.Add(BRepBuilderAPI_MakeEdge(innerCircle).Edge());

  TopoDS_Shape outerPipe = create_channel_shape(outerMaker.Wire(), path);
  TopoDS_Shape innerPipe = create_channel_shape(innerMaker.Wire(), path);

  TopoDS_Shape rpipe = BRepAlgoAPI_Cut(outerPipe, innerPipe).Shape();

  TopoDS_Compound result;
  BRep_Builder builder;
  builder.MakeCompound(result);

  builder.Add(result, rpipe);

  // 创建内部排管
  for (size_t i = 0; i < params.pipePositions.size(); ++i) {
    BRepBuilderAPI_MakeWire pipeMaker;
    BRepBuilderAPI_MakeWire pipeHoleMaker;

    gp_Pnt localCenter(0, params.pipePositions[i].X(),
                       params.pipePositions[i].Y());
    gp_Pnt projectedPoint = sectionAxes.Location().Translated(
        gp_Vec(localCenter.Z(), localCenter.Y(), 0).Transformed(trsf));

    gp_Circ pipeCircle(gp_Ax2(projectedPoint, tanDir),
                       params.pipeInnerDiameters[i] / 2 +
                           params.pipeWallThicknesses[i]);
    gp_Circ pipeHole(gp_Ax2(projectedPoint, tanDir),
                     params.pipeInnerDiameters[i] / 2);

    pipeMaker.Add(BRepBuilderAPI_MakeEdge(pipeCircle).Edge());
    pipeHoleMaker.Add(BRepBuilderAPI_MakeEdge(pipeHole).Edge());

    TopoDS_Shape outerPipe = create_channel_shape(pipeMaker.Wire(), path);
    TopoDS_Shape holePipe = create_channel_shape(pipeHoleMaker.Wire(), path);

    TopoDS_Shape ipipe = BRepAlgoAPI_Cut(outerPipe, holePipe).Shape();

    builder.Add(result, ipipe);
  }

  return result;
}


// 辅助函数：创建普通排管截面(YZ平面)
TopoDS_Compound create_normal_pipe_section(const pipe_row_params &params) {

  // 创建底板轮廓
  double baseWidth =
      params.hasEnclosure
          ? params.enclosureWidth + 2 * params.baseExtension
          : [&]() {
              // 计算最外侧管道位置(X坐标)
              double minX = std::numeric_limits<double>::max();
              double maxX = std::numeric_limits<double>::lowest();
              for (const auto &pos : params.pipePositions) {
                size_t i = &pos - &params.pipePositions[0];
                double radius = params.pipeInnerDiameters[i] / 2 +
                                params.pipeWallThicknesses[i];
                minX = std::min(minX, pos.X() - radius);
                maxX = std::max(maxX, pos.X() + radius);
              }
              return (maxX - minX) + 2 * params.baseExtension;
            }();
  BRepBuilderAPI_MakeWire baseMaker;

  // 创建路径线框
  BRepBuilderAPI_MakeWire pathWire;

  // 处理点序列
  for (size_t i = 0; i < params.points.size() - 1; i++) {
    const gp_Pnt &current = params.points[i].position;
    const gp_Pnt &next = params.points[i + 1].position;

    if (params.points[i].type == channel_point_type::LINE &&
        params.points[i + 1].type == channel_point_type::LINE) { // 普通节点
      // 创建直线段
      pathWire.Add(BRepBuilderAPI_MakeEdge(current, next).Edge());
    } else if (params.points[i].type == channel_point_type::ARC) { // 弧形节点
      // 确保有前一个点和后一个点
      if (i == 0 || i == params.points.size() - 1) {
        throw Standard_ConstructionError("弧形节点需要前后都有节点");
      }

      const gp_Pnt &prev = params.points[i - 1].position;

      // 创建三点圆弧
      pathWire.Add(BRepBuilderAPI_MakeEdge(
                       GC_MakeArcOfCircle(prev, current, next).Value())
                       .Edge());
    }
  }

  if (!pathWire.IsDone()) {
    throw Standard_ConstructionError("路径线框创建失败");
  }

  TopoDS_Wire path = pathWire.Wire();

  // 获取路径起始点的切线方向
  BRepAdaptor_CompCurve curveAdaptor(path);
  gp_Pnt startPoint;
  gp_Vec startTangent;
  curveAdaptor.D1(curveAdaptor.FirstParameter(), startPoint, startTangent);

  // 在创建截面圆之前添加方向修正
  gp_Dir tanDir = startTangent.Normalized();
  gp_Dir refDir = gp::DZ(); // 默认参考方向为全局Y轴

  // 如果tanDir平行于全局X轴，调整参考方向为全局Z轴
  if (IsParallel(tanDir, gp::DX())) {
    refDir = gp::DZ();
  }
  gp_Ax2 sectionAxes(startPoint, tanDir, refDir);

  // 创建变换对象
  gp_Trsf trsf;
  trsf.SetTransformation(sectionAxes, gp_Ax2(gp::Origin(), gp::DZ()));

  // YZ平面上的点坐标 (X=0)
  gp_Pnt p1(0, -baseWidth / 2, -params.baseThickness);
  gp_Pnt projectedp1 = sectionAxes.Location().Translated(
      gp_Vec(p1.Z(), p1.Y(), 0).Transformed(trsf));

  gp_Pnt p2(0, baseWidth / 2, -params.baseThickness);
  gp_Pnt projectedp2 = sectionAxes.Location().Translated(
      gp_Vec(p2.Z(), p2.Y(), 0).Transformed(trsf));

  gp_Pnt p3(0, baseWidth / 2, 0);
  gp_Pnt projectedp3 = sectionAxes.Location().Translated(
      gp_Vec(p3.Z(), p3.Y(), 0).Transformed(trsf));

  gp_Pnt p4(0, -baseWidth / 2, 0);
  gp_Pnt projectedp4 = sectionAxes.Location().Translated(
      gp_Vec(p4.Z(), p4.Y(), 0).Transformed(trsf));

  baseMaker.Add(BRepBuilderAPI_MakeEdge(projectedp1, projectedp2).Edge());
  baseMaker.Add(BRepBuilderAPI_MakeEdge(projectedp2, projectedp3).Edge());
  baseMaker.Add(BRepBuilderAPI_MakeEdge(projectedp3, projectedp4).Edge());
  baseMaker.Add(BRepBuilderAPI_MakeEdge(projectedp4, projectedp1).Edge());

  TopoDS_Compound result;
  BRep_Builder builder;
  builder.MakeCompound(result);

  TopoDS_Shape base = create_channel_shape(baseMaker.Wire(), path);

  builder.Add(result, base);

  if (params.cushionExtension > 0 && params.cushionThickness > 0) {
    BRepBuilderAPI_MakeWire cushionMaker;
    gp_Pnt p1(0, -baseWidth / 2 - params.cushionExtension,
              -params.baseThickness - params.cushionThickness);
    gp_Pnt projectedp1 = sectionAxes.Location().Translated(
        gp_Vec(p1.Z(), p1.Y(), 0).Transformed(trsf));

    gp_Pnt p2(0, baseWidth / 2 + params.cushionExtension,
              -params.baseThickness - params.cushionThickness);
    gp_Pnt projectedp2 = sectionAxes.Location().Translated(
        gp_Vec(p2.Z(), p2.Y(), 0).Transformed(trsf));

    gp_Pnt p3(0, baseWidth / 2 + params.cushionExtension,
              -params.baseThickness);
    gp_Pnt projectedp3 = sectionAxes.Location().Translated(
        gp_Vec(p3.Z(), p3.Y(), 0).Transformed(trsf));

    gp_Pnt p4(0, -baseWidth / 2 - params.cushionExtension,
              -params.baseThickness);
    gp_Pnt projectedp4 = sectionAxes.Location().Translated(
        gp_Vec(p4.Z(), p4.Y(), 0).Transformed(trsf));

    cushionMaker.Add(BRepBuilderAPI_MakeEdge(projectedp1, projectedp2).Edge());
    cushionMaker.Add(BRepBuilderAPI_MakeEdge(projectedp2, projectedp3).Edge());
    cushionMaker.Add(BRepBuilderAPI_MakeEdge(projectedp3, projectedp4).Edge());
    cushionMaker.Add(BRepBuilderAPI_MakeEdge(projectedp4, projectedp1).Edge());

    TopoDS_Shape cushion = create_channel_shape(cushionMaker.Wire(), path);

    builder.Add(result, cushion);
  }

  BRepBuilderAPI_MakeWire wireMaker1;
  TopoDS_Shape enclosure;

  // 创建封包（如果有）
  if (params.hasEnclosure) {
    gp_Pnt e1(0, -params.enclosureWidth / 2, 0);
    gp_Pnt e2(0, -params.enclosureWidth / 2, params.enclosureHeight);
    gp_Pnt e3(0, params.enclosureWidth / 2, params.enclosureHeight);
    gp_Pnt e4(0, params.enclosureWidth / 2, 0);

    gp_Pnt projectede1 = sectionAxes.Location().Translated(
        gp_Vec(e1.Z(), e1.Y(), 0).Transformed(trsf));
    gp_Pnt projectede2 = sectionAxes.Location().Translated(
        gp_Vec(e2.Z(), e2.Y(), 0).Transformed(trsf));
    gp_Pnt projectede3 = sectionAxes.Location().Translated(
        gp_Vec(e3.Z(), e3.Y(), 0).Transformed(trsf));
    gp_Pnt projectede4 = sectionAxes.Location().Translated(
        gp_Vec(e4.Z(), e4.Y(), 0).Transformed(trsf));

    wireMaker1.Add(BRepBuilderAPI_MakeEdge(projectede1, projectede2).Edge());
    wireMaker1.Add(BRepBuilderAPI_MakeEdge(projectede2, projectede3).Edge());
    wireMaker1.Add(BRepBuilderAPI_MakeEdge(projectede3, projectede4).Edge());
    wireMaker1.Add(BRepBuilderAPI_MakeEdge(projectede4, projectede1).Edge());

    enclosure = create_channel_shape(wireMaker1.Wire(), path);
  }

  // 创建管道
  for (size_t i = 0; i < params.pipePositions.size(); ++i) {
    BRepBuilderAPI_MakeWire pipeMaker;
    BRepBuilderAPI_MakeWire pipeHoleMaker;

    // YZ平面上的中心点 (X=0)
    gp_Pnt localCenter(0, params.pipePositions[i].X(),
                       params.pipePositions[i].Y());
    gp_Pnt projectedPoint = sectionAxes.Location().Translated(
        gp_Vec(localCenter.Z(), localCenter.Y(), 0).Transformed(trsf));

    gp_Circ pipeCircle(gp_Ax2(projectedPoint, tanDir), // 法线方向为X轴
                       params.pipeInnerDiameters[i] / 2 +
                           params.pipeWallThicknesses[i]);
    gp_Circ pipeHole(gp_Ax2(projectedPoint, tanDir),
                     params.pipeInnerDiameters[i] / 2);

    pipeMaker.Add(BRepBuilderAPI_MakeEdge(pipeCircle).Edge());
    pipeHoleMaker.Add(BRepBuilderAPI_MakeEdge(pipeHole).Edge());

    TopoDS_Shape pipe = create_channel_shape(pipeMaker.Wire(), path);

    if (params.hasEnclosure) {
      enclosure = BRepAlgoAPI_Cut(enclosure, pipe).Shape();
    } else {
      TopoDS_Shape holePipe = create_channel_shape(pipeHoleMaker.Wire(), path);

      pipe = BRepAlgoAPI_Cut(pipe, holePipe).Shape();
      builder.Add(result, pipe);
    }
  }

  if (params.hasEnclosure) {
    builder.Add(result, enclosure);
  }

  return result;
}


TopoDS_Shape create_pipe_row(const pipe_row_params &params) {
  // 创建截面
  TopoDS_Shape result;
  if (params.pipeType == pipe_row_type::NORMAL) {
    result = create_normal_pipe_section(params);
  } else {
    result = create_pull_pipe_section(params);
  }

  return result;
}


TopoDS_Shape create_pipe_row(const pipe_row_params &params,
                             const gp_Pnt &position, const gp_Dir &normal,
                             const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(normal.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Normal and direction must be perpendicular");
  }

  // 创建标准方向的排管
  TopoDS_Shape pipeRow = create_pipe_row(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, normal, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(pipeRow, transformation);
  return transform.Shape();
}


TopoDS_Wire create_pipe_row_centerline(const pipe_row_params &params) {
  BRepBuilderAPI_MakeWire pathWire;
  for (size_t i = 0; i < params.points.size() - 1; i++) {
    const gp_Pnt &current = params.points[i].position;
    const gp_Pnt &next = params.points[i + 1].position;

    if (params.points[i].type == channel_point_type::LINE &&
        params.points[i + 1].type == channel_point_type::LINE) { // 普通节点
      // 创建直线段
      pathWire.Add(BRepBuilderAPI_MakeEdge(current, next).Edge());
    } else if (params.points[i].type == channel_point_type::ARC) { // 弧形节点
      // 确保有前一个点和后一个点
      if (i == 0 || i == params.points.size() - 1) {
        throw Standard_ConstructionError("弧形节点需要前后都有节点");
      }

      const gp_Pnt &prev = params.points[i - 1].position;

      // 创建三点圆弧
      pathWire.Add(BRepBuilderAPI_MakeEdge(
                       GC_MakeArcOfCircle(prev, current, next).Value())
                       .Edge());
    }
  }

  if (!pathWire.IsDone()) {
    throw Standard_ConstructionError("路径线框创建失败");
  }

  return pathWire.Wire();
}


TopoDS_Shape create_cable_trench(const cable_trench_params &params) {
  // 参数验证
  if (params.width <= 0 || params.height <= 0) {
    throw Standard_ConstructionError("Width and height must be positive");
  }
  if (params.coverThickness < 0 || params.baseThickness < 0 ||
      params.cushionThickness < 0 || params.wallThickness < 0) {
    throw Standard_ConstructionError("Thickness values must be non-negative");
  }

  BRepBuilderAPI_MakeWire baseMaker;

  // 创建路径线框
  BRepBuilderAPI_MakeWire pathWire;

  // 处理点序列
  for (size_t i = 0; i < params.points.size() - 1; i++) {
    const gp_Pnt &current = params.points[i].position;
    const gp_Pnt &next = params.points[i + 1].position;

    if (params.points[i].type == channel_point_type::LINE &&
        params.points[i + 1].type == channel_point_type::LINE) { // 普通节点
      // 创建直线段
      pathWire.Add(BRepBuilderAPI_MakeEdge(current, next).Edge());
    } else if (params.points[i].type == channel_point_type::ARC) { // 弧形节点
      // 确保有前一个点和后一个点
      if (i == 0 || i == params.points.size() - 1) {
        throw Standard_ConstructionError("弧形节点需要前后都有节点");
      }

      const gp_Pnt &prev = params.points[i - 1].position;

      // 创建三点圆弧
      pathWire.Add(BRepBuilderAPI_MakeEdge(
                       GC_MakeArcOfCircle(prev, current, next).Value())
                       .Edge());
    }
  }

  if (!pathWire.IsDone()) {
    throw Standard_ConstructionError("路径线框创建失败");
  }

  TopoDS_Wire path = pathWire.Wire();

  // 获取路径起始点的切线方向
  BRepAdaptor_CompCurve curveAdaptor(path);
  gp_Pnt startPoint;
  gp_Vec startTangent;
  curveAdaptor.D1(curveAdaptor.FirstParameter(), startPoint, startTangent);

  // 在创建截面圆之前添加方向修正
  gp_Dir tanDir = startTangent.Normalized();
  gp_Dir refDir = gp::DZ(); // 默认参考方向为全局Y轴

  // 如果tanDir平行于全局X轴，调整参考方向为全局Z轴
  if (IsParallel(tanDir, gp::DX())) {
    refDir = gp::DZ();
  }
  gp_Ax2 sectionAxes(startPoint, tanDir, refDir);

  // 创建变换对象
  gp_Trsf trsf;
  trsf.SetTransformation(sectionAxes, gp_Ax2(gp::Origin(), gp::DZ()));

  double baseWidth =
      params.width + 2 * params.wallThickness + 2 * params.baseExtension;

  // YZ平面上的点坐标 (X=0)
  gp_Pnt p1(0, -baseWidth / 2, -params.baseThickness);
  gp_Pnt p2(0, baseWidth / 2, -params.baseThickness);
  gp_Pnt p3(0, baseWidth / 2, 0);
  gp_Pnt p4(0, -baseWidth / 2, 0);

  gp_Pnt projectedp1 = sectionAxes.Location().Translated(
      gp_Vec(p1.Z(), p1.Y(), 0).Transformed(trsf));
  gp_Pnt projectedp2 = sectionAxes.Location().Translated(
      gp_Vec(p2.Z(), p2.Y(), 0).Transformed(trsf));
  gp_Pnt projectedp3 = sectionAxes.Location().Translated(
      gp_Vec(p3.Z(), p3.Y(), 0).Transformed(trsf));
  gp_Pnt projectedp4 = sectionAxes.Location().Translated(
      gp_Vec(p4.Z(), p4.Y(), 0).Transformed(trsf));

  baseMaker.Add(BRepBuilderAPI_MakeEdge(projectedp1, projectedp2).Edge());
  baseMaker.Add(BRepBuilderAPI_MakeEdge(projectedp2, projectedp3).Edge());
  baseMaker.Add(BRepBuilderAPI_MakeEdge(projectedp3, projectedp4).Edge());
  baseMaker.Add(BRepBuilderAPI_MakeEdge(projectedp4, projectedp1).Edge());

  TopoDS_Compound result;
  BRep_Builder builder;
  builder.MakeCompound(result);

  TopoDS_Shape base = create_channel_shape(baseMaker.Wire(), path);

  builder.Add(result, base);

  if (params.cushionExtension > 0 && params.cushionThickness > 0) {
    BRepBuilderAPI_MakeWire cushionMaker;
    gp_Pnt p1(0, -baseWidth / 2 - params.cushionExtension,
              -params.baseThickness - params.cushionThickness);
    gp_Pnt p2(0, baseWidth / 2 + params.cushionExtension,
              -params.baseThickness - params.cushionThickness);
    gp_Pnt p3(0, baseWidth / 2 + params.cushionExtension,
              -params.baseThickness);
    gp_Pnt p4(0, -baseWidth / 2 - params.cushionExtension,
              -params.baseThickness);

    gp_Pnt projectedp1 = sectionAxes.Location().Translated(
        gp_Vec(p1.Z(), p1.Y(), 0).Transformed(trsf));
    gp_Pnt projectedp2 = sectionAxes.Location().Translated(
        gp_Vec(p2.Z(), p2.Y(), 0).Transformed(trsf));
    gp_Pnt projectedp3 = sectionAxes.Location().Translated(
        gp_Vec(p3.Z(), p3.Y(), 0).Transformed(trsf));
    gp_Pnt projectedp4 = sectionAxes.Location().Translated(
        gp_Vec(p4.Z(), p4.Y(), 0).Transformed(trsf));

    cushionMaker.Add(BRepBuilderAPI_MakeEdge(projectedp1, projectedp2).Edge());
    cushionMaker.Add(BRepBuilderAPI_MakeEdge(projectedp2, projectedp3).Edge());
    cushionMaker.Add(BRepBuilderAPI_MakeEdge(projectedp3, projectedp4).Edge());
    cushionMaker.Add(BRepBuilderAPI_MakeEdge(projectedp4, projectedp1).Edge());

    TopoDS_Shape cushion = create_channel_shape(cushionMaker.Wire(), path);

    builder.Add(result, cushion);
  }

  // 创建盖板
  TopoDS_Shape cover;
  if (params.coverThickness > 0) {
    BRepBuilderAPI_MakeWire coverMaker;
    double coverWidth = params.coverWidth > 0
                            ? params.coverWidth
                            : params.width + 2 * params.wallThickness;

    gp_Pnt p1(0, -params.coverWidth / 2, params.height);
    gp_Pnt p2(0, params.coverWidth / 2, params.height);
    gp_Pnt p3(0, params.coverWidth / 2, params.height + params.coverThickness);
    gp_Pnt p4(0, -params.coverWidth / 2, params.height + params.coverThickness);

    gp_Pnt projectedp1 = sectionAxes.Location().Translated(
        gp_Vec(p1.Z(), p1.Y(), 0).Transformed(trsf));
    gp_Pnt projectedp2 = sectionAxes.Location().Translated(
        gp_Vec(p2.Z(), p2.Y(), 0).Transformed(trsf));
    gp_Pnt projectedp3 = sectionAxes.Location().Translated(
        gp_Vec(p3.Z(), p3.Y(), 0).Transformed(trsf));
    gp_Pnt projectedp4 = sectionAxes.Location().Translated(
        gp_Vec(p4.Z(), p4.Y(), 0).Transformed(trsf));

    coverMaker.Add(BRepBuilderAPI_MakeEdge(projectedp1, projectedp2).Edge());
    coverMaker.Add(BRepBuilderAPI_MakeEdge(projectedp2, projectedp3).Edge());
    coverMaker.Add(BRepBuilderAPI_MakeEdge(projectedp3, projectedp4).Edge());
    coverMaker.Add(BRepBuilderAPI_MakeEdge(projectedp4, projectedp1).Edge());

    TopoDS_Shape cover = create_channel_shape(coverMaker.Wire(), path);

    builder.Add(result, cover);
  }

  // 创建墙壁
  {
    BRepBuilderAPI_MakeWire wall1Maker;
    double wall1Width = params.width + 2 * params.wallThickness;
    gp_Pnt p1(0, params.width / 2, 0);
    gp_Pnt projectedp1 = sectionAxes.Location().Translated(
        gp_Vec(p1.Z(), p1.Y(), 0).Transformed(trsf));

    gp_Pnt p2(0, wall1Width / 2, 0);
    gp_Pnt projectedp2 = sectionAxes.Location().Translated(
        gp_Vec(p2.Z(), p2.Y(), 0).Transformed(trsf));

    gp_Pnt p3(0, wall1Width / 2, params.height + params.coverThickness);
    gp_Pnt projectedp3 = sectionAxes.Location().Translated(
        gp_Vec(p3.Z(), p3.Y(), 0).Transformed(trsf));

    gp_Pnt p4(0, wall1Width / 2 - params.wallThickness2,
              params.height + params.coverThickness);
    gp_Pnt projectedp4 = sectionAxes.Location().Translated(
        gp_Vec(p4.Z(), p4.Y(), 0).Transformed(trsf));

    gp_Pnt p5(0, wall1Width / 2 - params.wallThickness2, params.height);
    gp_Pnt projectedp5 = sectionAxes.Location().Translated(
        gp_Vec(p5.Z(), p5.Y(), 0).Transformed(trsf));

    gp_Pnt p6(0, params.width / 2, params.height);
    gp_Pnt projectedp6 = sectionAxes.Location().Translated(
        gp_Vec(p6.Z(), p6.Y(), 0).Transformed(trsf));

    wall1Maker.Add(BRepBuilderAPI_MakeEdge(projectedp1, projectedp2).Edge());
    wall1Maker.Add(BRepBuilderAPI_MakeEdge(projectedp2, projectedp3).Edge());
    wall1Maker.Add(BRepBuilderAPI_MakeEdge(projectedp3, projectedp4).Edge());
    wall1Maker.Add(BRepBuilderAPI_MakeEdge(projectedp4, projectedp5).Edge());
    wall1Maker.Add(BRepBuilderAPI_MakeEdge(projectedp5, projectedp6).Edge());
    wall1Maker.Add(BRepBuilderAPI_MakeEdge(projectedp6, projectedp1).Edge());
    TopoDS_Shape wall = create_channel_shape(wall1Maker.Wire(), path);
    builder.Add(result, wall);
  }
  {
    BRepBuilderAPI_MakeWire wall2Maker;
    double wall1Width = params.width + 2 * params.wallThickness;
    gp_Pnt p1(0, -params.width / 2, 0);
    gp_Pnt projectedp1 = sectionAxes.Location().Translated(
        gp_Vec(p1.Z(), p1.Y(), 0).Transformed(trsf));

    gp_Pnt p2(0, -wall1Width / 2, 0);
    gp_Pnt projectedp2 = sectionAxes.Location().Translated(
        gp_Vec(p2.Z(), p2.Y(), 0).Transformed(trsf));

    gp_Pnt p3(0, -wall1Width / 2, params.height + params.coverThickness);
    gp_Pnt projectedp3 = sectionAxes.Location().Translated(
        gp_Vec(p3.Z(), p3.Y(), 0).Transformed(trsf));

    gp_Pnt p4(0, -wall1Width / 2 + params.wallThickness2,
              params.height + params.coverThickness);
    gp_Pnt projectedp4 = sectionAxes.Location().Translated(
        gp_Vec(p4.Z(), p4.Y(), 0).Transformed(trsf));

    gp_Pnt p5(0, -wall1Width / 2 + params.wallThickness2, params.height);
    gp_Pnt projectedp5 = sectionAxes.Location().Translated(
        gp_Vec(p5.Z(), p5.Y(), 0).Transformed(trsf));

    gp_Pnt p6(0, -params.width / 2, params.height);
    gp_Pnt projectedp6 = sectionAxes.Location().Translated(
        gp_Vec(p6.Z(), p6.Y(), 0).Transformed(trsf));

    wall2Maker.Add(BRepBuilderAPI_MakeEdge(projectedp1, projectedp2).Edge());
    wall2Maker.Add(BRepBuilderAPI_MakeEdge(projectedp2, projectedp3).Edge());
    wall2Maker.Add(BRepBuilderAPI_MakeEdge(projectedp3, projectedp4).Edge());
    wall2Maker.Add(BRepBuilderAPI_MakeEdge(projectedp4, projectedp5).Edge());
    wall2Maker.Add(BRepBuilderAPI_MakeEdge(projectedp5, projectedp6).Edge());
    wall2Maker.Add(BRepBuilderAPI_MakeEdge(projectedp6, projectedp1).Edge());
    TopoDS_Shape wall = create_channel_shape(wall2Maker.Wire(), path);
    builder.Add(result, wall);
  }

  return result;
}


TopoDS_Shape create_cable_trench(const cable_trench_params &params,
                                 const gp_Pnt &position,
                                 const gp_Dir &direction, const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(direction.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Direction and xDir must be perpendicular");
  }

  // 创建标准方向的电缆沟
  TopoDS_Shape trench = create_cable_trench(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, direction, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(trench, transformation);

  return transform.Shape();
}


TopoDS_Wire create_cable_trench_centerline(const cable_trench_params &params) {
  if (params.coverThickness < 0 || params.baseThickness < 0 ||
      params.cushionThickness < 0 || params.wallThickness < 0) {
    throw Standard_ConstructionError("Thickness values must be non-negative");
  }

  BRepBuilderAPI_MakeWire baseMaker;

  // 创建路径线框
  BRepBuilderAPI_MakeWire pathWire;

  // 处理点序列
  for (size_t i = 0; i < params.points.size() - 1; i++) {
    const gp_Pnt &current = params.points[i].position;
    const gp_Pnt &next = params.points[i + 1].position;

    if (params.points[i].type == channel_point_type::LINE &&
        params.points[i + 1].type == channel_point_type::LINE) { // 普通节点
      // 创建直线段
      pathWire.Add(BRepBuilderAPI_MakeEdge(current, next).Edge());
    } else if (params.points[i].type == channel_point_type::ARC) { // 弧形节点
      // 确保有前一个点和后一个点
      if (i == 0 || i == params.points.size() - 1) {
        throw Standard_ConstructionError("弧形节点需要前后都有节点");
      }

      const gp_Pnt &prev = params.points[i - 1].position;

      // 创建三点圆弧
      pathWire.Add(BRepBuilderAPI_MakeEdge(
                       GC_MakeArcOfCircle(prev, current, next).Value())
                       .Edge());
    }
  }

  if (!pathWire.IsDone()) {
    throw Standard_ConstructionError("路径线框创建失败");
  }

  return pathWire.Wire();
}


TopoDS_Shape create_cable_tunnel(const cable_tunnel_params &params) {
  // 参数验证
  if (params.width <= 0 || params.height <= 0) {
    throw Standard_ConstructionError("Width and height must be positive");
  }
  if (params.points.size() < 2) {
    throw Standard_ConstructionError("At least 2 points are required");
  }

  // 创建路径线框
  BRepBuilderAPI_MakeWire pathWire;

  // 处理点序列
  for (size_t i = 0; i < params.points.size() - 1; i++) {
    const gp_Pnt &current = params.points[i].position;
    const gp_Pnt &next = params.points[i + 1].position;

    if (params.points[i].type == channel_point_type::LINE &&
        params.points[i + 1].type == channel_point_type::LINE) { // 普通节点
      // 创建直线段
      pathWire.Add(BRepBuilderAPI_MakeEdge(current, next).Edge());
    } else if (params.points[i].type == channel_point_type::ARC) { // 弧形节点
      // 确保有前一个点和后一个点
      if (i == 0 || i == params.points.size() - 1) {
        throw Standard_ConstructionError("弧形节点需要前后都有节点");
      }

      const gp_Pnt &prev = params.points[i - 1].position;

      // 创建三点圆弧
      pathWire.Add(BRepBuilderAPI_MakeEdge(
                       GC_MakeArcOfCircle(prev, current, next).Value())
                       .Edge());
    }
  }

  if (!pathWire.IsDone()) {
    throw Standard_ConstructionError("路径线框创建失败");
  }

  TopoDS_Wire path = pathWire.Wire();

  // 获取路径起始点的切线方向
  BRepAdaptor_CompCurve curveAdaptor(path);
  gp_Pnt startPoint;
  gp_Vec startTangent;
  curveAdaptor.D1(curveAdaptor.FirstParameter(), startPoint, startTangent);

  // 在创建截面圆之前添加方向修正
  gp_Dir tanDir = startTangent.Normalized();
  gp_Dir refDir = gp::DZ(); // 默认参考方向为全局Y轴

  // 如果tanDir平行于全局X轴，调整参考方向为全局Z轴
  if (IsParallel(tanDir, gp::DX())) {
    refDir = gp::DZ();
  }
  gp_Ax2 sectionAxes(startPoint, tanDir, refDir);

  // 创建变换对象
  gp_Trsf trsf;
  trsf.SetTransformation(sectionAxes, gp_Ax2(gp::Origin(), gp::DZ()));

  TopoDS_Compound result;
  BRep_Builder builder;
  builder.MakeCompound(result);

  if (params.cushionExtension > 0 && params.cushionThickness > 0 &&
      params.style != connection_section_style::CIRCULAR) {
    double zoffset = -params.cushionThickness;

    if (params.style == connection_section_style::HORSESHOE) {
      zoffset = -params.cushionThickness - params.outerWallThickness -
                params.innerWallThickness;
    }

    double cushionWidth = params.width + 2 * params.cushionExtension +
                          2 * params.outerWallThickness;
    BRepBuilderAPI_MakeWire cushionMaker;
    gp_Pnt p1(0, -cushionWidth / 2 - params.cushionExtension, zoffset);
    gp_Pnt p2(0, cushionWidth / 2 + params.cushionExtension, zoffset);
    gp_Pnt p3(0, cushionWidth / 2 + params.cushionExtension,
              zoffset + params.cushionThickness);
    gp_Pnt p4(0, -cushionWidth / 2 - params.cushionExtension,
              zoffset + params.cushionThickness);

    gp_Pnt projectedp1 = sectionAxes.Location().Translated(
        gp_Vec(p1.Z(), p1.Y(), 0).Transformed(trsf));
    gp_Pnt projectedp2 = sectionAxes.Location().Translated(
        gp_Vec(p2.Z(), p2.Y(), 0).Transformed(trsf));
    gp_Pnt projectedp3 = sectionAxes.Location().Translated(
        gp_Vec(p3.Z(), p3.Y(), 0).Transformed(trsf));
    gp_Pnt projectedp4 = sectionAxes.Location().Translated(
        gp_Vec(p4.Z(), p4.Y(), 0).Transformed(trsf));

    cushionMaker.Add(BRepBuilderAPI_MakeEdge(projectedp1, projectedp2).Edge());
    cushionMaker.Add(BRepBuilderAPI_MakeEdge(projectedp2, projectedp3).Edge());
    cushionMaker.Add(BRepBuilderAPI_MakeEdge(projectedp3, projectedp4).Edge());
    cushionMaker.Add(BRepBuilderAPI_MakeEdge(projectedp4, projectedp1).Edge());

    TopoDS_Shape cushion = create_channel_shape(cushionMaker.Wire(), path);

    builder.Add(result, cushion);
  }

  // 创建隧道截面轮廓
  TopoDS_Wire outerWire;
  switch (params.style) {
  case connection_section_style::RECTANGULAR: {
    // 矩形截面
    double width = params.width + 2 * params.outerWallThickness;
    gp_Pnt p1(0, -width / 2, -params.bottomThickness);
    gp_Pnt p2(0, width / 2, -params.bottomThickness);
    gp_Pnt p3(0, width / 2, params.height + params.topThickness);
    gp_Pnt p4(0, -width / 2, params.height + params.topThickness);

    gp_Pnt projectedp1 = sectionAxes.Location().Translated(
        gp_Vec(p1.Z(), p1.Y(), 0).Transformed(trsf));
    gp_Pnt projectedp2 = sectionAxes.Location().Translated(
        gp_Vec(p2.Z(), p2.Y(), 0).Transformed(trsf));
    gp_Pnt projectedp3 = sectionAxes.Location().Translated(
        gp_Vec(p3.Z(), p3.Y(), 0).Transformed(trsf));
    gp_Pnt projectedp4 = sectionAxes.Location().Translated(
        gp_Vec(p4.Z(), p4.Y(), 0).Transformed(trsf));

    outerWire = BRepBuilderAPI_MakePolygon(projectedp1, projectedp2,
                                           projectedp3, projectedp4, true)
                    .Wire();
    break;
  }
  case connection_section_style::HORSESHOE: {
    // 马蹄形截面 - 外部轮廓
    double outerWidth = params.width + 2 * params.outerWallThickness +
                        2 * params.innerWallThickness;
    double outerRadius = outerWidth / 2;
    double outerHeight =
        params.height + params.outerWallThickness + params.innerWallThickness;
    double outerArchHeight = params.arcHeight + params.outerWallThickness +
                             params.innerWallThickness;

    // 底部点
    gp_Pnt localBottomLeft(0, -outerRadius,
                           -params.outerWallThickness -
                               params.innerWallThickness);
    gp_Pnt bottomLeft = sectionAxes.Location().Translated(
        gp_Vec(localBottomLeft.Z(), localBottomLeft.Y(), 0).Transformed(trsf));

    gp_Pnt localBottomRight(
        0, outerRadius, -params.outerWallThickness - params.innerWallThickness);
    gp_Pnt bottomRight = sectionAxes.Location().Translated(
        gp_Vec(localBottomRight.Z(), localBottomRight.Y(), 0)
            .Transformed(trsf));

    // 侧壁点
    gp_Pnt localLeftTop(0, -outerRadius, outerHeight);
    gp_Pnt leftTop = sectionAxes.Location().Translated(
        gp_Vec(localLeftTop.Z(), localLeftTop.Y(), 0).Transformed(trsf));

    gp_Pnt localRightTop(0, outerRadius, outerHeight);
    gp_Pnt rightTop = sectionAxes.Location().Translated(
        gp_Vec(localRightTop.Z(), localRightTop.Y(), 0).Transformed(trsf));

    // 顶部圆弧中点
    gp_Pnt localArcMid(0, 0, outerHeight + outerArchHeight);
    gp_Pnt arcMid = sectionAxes.Location().Translated(
        gp_Vec(localArcMid.Z(), localArcMid.Y(), 0).Transformed(trsf));

    // 创建侧壁直线
    TopoDS_Edge leftEdge = BRepBuilderAPI_MakeEdge(bottomLeft, leftTop).Edge();
    TopoDS_Edge rightEdge =
        BRepBuilderAPI_MakeEdge(bottomRight, rightTop).Edge();

    // 创建顶部圆弧 (从右到左)
    Handle(Geom_TrimmedCurve) topArc =
        GC_MakeArcOfCircle(rightTop, arcMid, leftTop).Value();
    TopoDS_Edge topEdge = BRepBuilderAPI_MakeEdge(topArc).Edge();

    // 创建底部直线
    TopoDS_Edge bottomEdge =
        BRepBuilderAPI_MakeEdge(bottomLeft, bottomRight).Edge();

    // 组合成完整轮廓 (确保闭合)
    BRepBuilderAPI_MakeWire wireMaker;
    wireMaker.Add(leftEdge);
    wireMaker.Add(topEdge);
    wireMaker.Add(rightEdge);
    wireMaker.Add(bottomEdge);

    if (!wireMaker.IsDone()) {
      throw Standard_ConstructionError(
          "Failed to create closed wire for horseshoe section");
    }

    outerWire = wireMaker.Wire();

    if (!outerWire.Closed()) {
      throw Standard_ConstructionError("Outer horseshoe section is not closed");
    }
    break;
  }
  case connection_section_style::CIRCULAR: {
    // 圆形截面 - 外部轮廓
    double outerRadius = params.width / 2 + params.outerWallThickness;
    gp_Pnt center(0, 0, 0);
    Handle(Geom_Circle) outerCircle =
        new Geom_Circle(gp_Ax2(center, gp::DX()), outerRadius);
    TopoDS_Edge outerEdge = BRepBuilderAPI_MakeEdge(outerCircle).Edge();
    outerWire = BRepBuilderAPI_MakeWire(outerEdge).Wire();
    break;
  }
  default:
    throw Standard_ConstructionError("Invalid tunnel section style");
  }
  TopoDS_Shape outer = create_channel_shape(outerWire, path);

  // 创建隧道截面轮廓
  TopoDS_Wire innerWire;
  switch (params.style) {
  case connection_section_style::RECTANGULAR: {
    // 矩形截面
    gp_Pnt p1(0, -params.width / 2, 0);
    gp_Pnt p2(0, params.width / 2, 0);
    gp_Pnt p3(0, params.width / 2, params.height);
    gp_Pnt p4(0, -params.width / 2, params.height);

    gp_Pnt projectedp1 = sectionAxes.Location().Translated(
        gp_Vec(p1.Z(), p1.Y(), 0).Transformed(trsf));
    gp_Pnt projectedp2 = sectionAxes.Location().Translated(
        gp_Vec(p2.Z(), p2.Y(), 0).Transformed(trsf));
    gp_Pnt projectedp3 = sectionAxes.Location().Translated(
        gp_Vec(p3.Z(), p3.Y(), 0).Transformed(trsf));
    gp_Pnt projectedp4 = sectionAxes.Location().Translated(
        gp_Vec(p4.Z(), p4.Y(), 0).Transformed(trsf));

    innerWire = BRepBuilderAPI_MakePolygon(projectedp1, projectedp2,
                                           projectedp3, projectedp4, true)
                    .Wire();
    break;
  }
  case connection_section_style::HORSESHOE: {
    // 马蹄形截面 - 内部轮廓
    double innerRadius = params.width / 2;
    double innerHeight = params.height;
    double innerArchHeight = params.arcHeight;

    // 底部点
    gp_Pnt localBottomLeft(0, -innerRadius, 0);
    gp_Pnt bottomLeft = sectionAxes.Location().Translated(
        gp_Vec(localBottomLeft.Z(), localBottomLeft.Y(), 0).Transformed(trsf));

    gp_Pnt localBottomRight(0, innerRadius, 0);
    gp_Pnt bottomRight = sectionAxes.Location().Translated(
        gp_Vec(localBottomRight.Z(), localBottomRight.Y(), 0)
            .Transformed(trsf));

    // 侧壁点
    gp_Pnt localLeftTop(0, -innerRadius, innerHeight);
    gp_Pnt leftTop = sectionAxes.Location().Translated(
        gp_Vec(localLeftTop.Z(), localLeftTop.Y(), 0).Transformed(trsf));

    gp_Pnt localRightTop(0, innerRadius, innerHeight);
    gp_Pnt rightTop = sectionAxes.Location().Translated(
        gp_Vec(localRightTop.Z(), localRightTop.Y(), 0).Transformed(trsf));

    // 顶部圆弧中点
    gp_Pnt localArcMid(0, 0, innerHeight + innerArchHeight);
    gp_Pnt arcMid = sectionAxes.Location().Translated(
        gp_Vec(localArcMid.Z(), localArcMid.Y(), 0).Transformed(trsf));

    // 创建侧壁直线
    TopoDS_Edge leftEdge = BRepBuilderAPI_MakeEdge(bottomLeft, leftTop).Edge();
    TopoDS_Edge rightEdge =
        BRepBuilderAPI_MakeEdge(bottomRight, rightTop).Edge();

    // 创建顶部圆弧 (从右到左)
    Handle(Geom_TrimmedCurve) topArc =
        GC_MakeArcOfCircle(rightTop, arcMid, leftTop).Value();
    TopoDS_Edge topEdge = BRepBuilderAPI_MakeEdge(topArc).Edge();

    // 创建底部直线
    TopoDS_Edge bottomEdge =
        BRepBuilderAPI_MakeEdge(bottomLeft, bottomRight).Edge();

    // 组合成完整轮廓 (确保闭合)
    BRepBuilderAPI_MakeWire wireMaker;
    wireMaker.Add(leftEdge);
    wireMaker.Add(topEdge);
    wireMaker.Add(rightEdge);
    wireMaker.Add(bottomEdge);

    if (!wireMaker.IsDone()) {
      throw Standard_ConstructionError(
          "Failed to create closed wire for inner horseshoe section");
    }

    innerWire = wireMaker.Wire();

    if (!innerWire.Closed()) {
      throw Standard_ConstructionError("Inner horseshoe section is not closed");
    }
    break;
  }
  case connection_section_style::CIRCULAR: {
    // 圆形截面 - 内部轮廓
    double innerRadius = params.width / 2;
    gp_Pnt center(0, 0, 0);
    Handle(Geom_Circle) innerCircle =
        new Geom_Circle(gp_Ax2(center, gp::DX()), innerRadius);
    TopoDS_Edge innerEdge = BRepBuilderAPI_MakeEdge(innerCircle).Edge();
    innerWire = BRepBuilderAPI_MakeWire(innerEdge).Wire();

    break;
  }
  default:
    throw Standard_ConstructionError("Invalid tunnel section style");
  }

  TopoDS_Shape inner = create_channel_shape(innerWire, path);

  // 处理底部平台
  if (params.style == connection_section_style::CIRCULAR &&
      params.bottomPlatformHeight != 0) {
    double innerRadius = params.width / 2;

    double zoffset = -innerRadius;
    gp_Pnt p1(0, -innerRadius, -innerRadius + params.bottomPlatformHeight);
    gp_Pnt p2(0, innerRadius, -innerRadius + params.bottomPlatformHeight);
    gp_Pnt p3(0, innerRadius, -innerRadius);
    gp_Pnt p4(0, -innerRadius, -innerRadius);

    gp_Pnt projectedp1 = sectionAxes.Location().Translated(
        gp_Vec(p1.Z(), p1.Y(), 0).Transformed(trsf));
    gp_Pnt projectedp2 = sectionAxes.Location().Translated(
        gp_Vec(p2.Z(), p2.Y(), 0).Transformed(trsf));
    gp_Pnt projectedp3 = sectionAxes.Location().Translated(
        gp_Vec(p3.Z(), p3.Y(), 0).Transformed(trsf));
    gp_Pnt projectedp4 = sectionAxes.Location().Translated(
        gp_Vec(p4.Z(), p4.Y(), 0).Transformed(trsf));

    TopoDS_Wire tempWire =
        BRepBuilderAPI_MakePolygon(projectedp1, projectedp2, projectedp3,
                                   projectedp4, true)
            .Wire();
    TopoDS_Shape cutBottom = create_channel_shape(tempWire, path);

    inner = BRepAlgoAPI_Cut(inner, cutBottom).Shape();
  }

  TopoDS_Shape tunnel = BRepAlgoAPI_Cut(outer, inner).Shape();
  builder.Add(result, tunnel);

  return result;
}


TopoDS_Shape create_cable_tunnel(const cable_tunnel_params &params,
                                 const gp_Pnt &position,
                                 const gp_Dir &direction, const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(direction.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Direction and xDir must be perpendicular");
  }

  // 创建标准方向的电缆隧道
  TopoDS_Shape tunnel = create_cable_tunnel(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, direction, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(tunnel, transformation);
  return transform.Shape();
}

TopoDS_Wire create_cable_tunnel_centerline(const cable_tunnel_params &params) {
  BRepBuilderAPI_MakeWire pathWire;

  // 处理点序列
  for (size_t i = 0; i < params.points.size() - 1; i++) {
    const gp_Pnt &current = params.points[i].position;
    const gp_Pnt &next = params.points[i + 1].position;

    if (params.points[i].type == channel_point_type::LINE &&
        params.points[i + 1].type == channel_point_type::LINE) { // 普通节点
      // 创建直线段
      pathWire.Add(BRepBuilderAPI_MakeEdge(current, next).Edge());
    } else if (params.points[i].type == channel_point_type::ARC) { // 弧形节点
      // 确保有前一个点和后一个点
      if (i == 0 || i == params.points.size() - 1) {
        throw Standard_ConstructionError("弧形节点需要前后都有节点");
      }

      const gp_Pnt &prev = params.points[i - 1].position;

      // 创建三点圆弧
      pathWire.Add(BRepBuilderAPI_MakeEdge(
                       GC_MakeArcOfCircle(prev, current, next).Value())
                       .Edge());
    }
  }

  if (!pathWire.IsDone()) {
    throw Standard_ConstructionError("路径线框创建失败");
  }

  return pathWire.Wire();
}


TopoDS_Shape create_cable_tray(const cable_tray_params &params) {
  // 参数验证
  if (params.width <= 0 || params.height <= 0 || params.span <= 0) {
    throw Standard_ConstructionError("Width, height and span must be positive");
  }
  if (params.points.size() < 2) {
    throw Standard_ConstructionError("At least 2 points are required");
  }

  // 创建路径线框
  BRepBuilderAPI_MakeWire pathWire;

  // 处理点序列
  for (size_t i = 0; i < params.points.size() - 1; i++) {
    const gp_Pnt &current = params.points[i].position;
    const gp_Pnt &next = params.points[i + 1].position;

    if (params.points[i].type == channel_point_type::LINE &&
        params.points[i + 1].type == channel_point_type::LINE) { // 普通节点
      // 创建直线段
      pathWire.Add(BRepBuilderAPI_MakeEdge(current, next).Edge());
    } else if (params.points[i].type == channel_point_type::ARC) { // 弧形节点
      // 确保有前一个点和后一个点
      if (i == 0 || i == params.points.size() - 1) {
        throw Standard_ConstructionError("弧形节点需要前后都有节点");
      }

      const gp_Pnt &prev = params.points[i - 1].position;

      // 创建三点圆弧
      pathWire.Add(BRepBuilderAPI_MakeEdge(
                       GC_MakeArcOfCircle(prev, current, next).Value())
                       .Edge());
    }
  }

  if (!pathWire.IsDone()) {
    throw Standard_ConstructionError("路径线框创建失败");
  }

  TopoDS_Wire path = pathWire.Wire();

  // 获取路径起始点的切线方向
  BRepAdaptor_CompCurve curveAdaptor(path);
  gp_Pnt startPoint;
  gp_Vec startTangent;
  curveAdaptor.D1(curveAdaptor.FirstParameter(), startPoint, startTangent);

  // 在创建截面圆之前添加方向修正
  gp_Dir tanDir = startTangent.Normalized();
  gp_Dir refDir = gp::DZ(); // 默认参考方向为全局Y轴

  // 如果tanDir平行于全局X轴，调整参考方向为全局Z轴
  if (IsParallel(tanDir, gp::DX())) {
    refDir = gp::DZ();
  }
  gp_Ax2 sectionAxes(startPoint, tanDir, refDir);

  // 创建变换对象
  gp_Trsf trsf;
  trsf.SetTransformation(sectionAxes, gp_Ax2(gp::Origin(), gp::DZ()));

  TopoDS_Compound result;
  BRep_Builder builder;
  builder.MakeCompound(result);

  // 创建管道
  for (size_t i = 0; i < params.pipePositions.size(); ++i) {
    BRepBuilderAPI_MakeWire pipeMaker;
    BRepBuilderAPI_MakeWire pipeHoleMaker;

    // YZ平面上的中心点 (X=0)
    gp_Pnt localCenter(0, params.pipePositions[i].X(),
                       params.pipePositions[i].Y());

    gp_Pnt projectedPoint = sectionAxes.Location().Translated(
        gp_Vec(localCenter.Z(), localCenter.Y(), 0).Transformed(trsf));

    gp_Circ pipeCircle(gp_Ax2(projectedPoint, tanDir), // 法线方向为X轴
                       params.pipeInnerDiameters[i] / 2 +
                           params.pipeWallThicknesses[i]);
    gp_Circ pipeHole(gp_Ax2(projectedPoint, tanDir),
                     params.pipeInnerDiameters[i] / 2);

    pipeMaker.Add(BRepBuilderAPI_MakeEdge(pipeCircle).Edge());
    pipeHoleMaker.Add(BRepBuilderAPI_MakeEdge(pipeHole).Edge());

    TopoDS_Shape pipe = create_channel_shape(pipeMaker.Wire(), path);

    TopoDS_Shape holePipe = create_channel_shape(pipeHoleMaker.Wire(), path);

    pipe = BRepAlgoAPI_Cut(pipe, holePipe).Shape();
    builder.Add(result, pipe);
  }

  // 创建盖板
  TopoDS_Shape cover;
  if (params.topPlateHeight > 0) {
    BRepBuilderAPI_MakeWire coverMaker;

    gp_Pnt p1(0, -params.width / 2, params.height);
    gp_Pnt p2(0, params.width / 2, params.height);
    gp_Pnt p3(0, params.width / 2, params.height + params.topPlateHeight);
    gp_Pnt p4(0, -params.width / 2, params.height + params.topPlateHeight);

    coverMaker.Add(BRepBuilderAPI_MakeEdge(p1, p2).Edge());
    coverMaker.Add(BRepBuilderAPI_MakeEdge(p2, p3).Edge());
    coverMaker.Add(BRepBuilderAPI_MakeEdge(p3, p4).Edge());
    coverMaker.Add(BRepBuilderAPI_MakeEdge(p4, p1).Edge());

    TopoDS_Shape cover = create_channel_shape(coverMaker.Wire(), path);

    builder.Add(result, cover);
  }

  // 创建墙壁
  {
    BRepBuilderAPI_MakeWire wall1Maker;
    double wall1Width = params.width;
    gp_Pnt p1(0, wall1Width / 2, 0);
    gp_Pnt projectedp1 = sectionAxes.Location().Translated(
        gp_Vec(p1.Z(), p1.Y(), 0).Transformed(trsf));

    gp_Pnt p2(0, wall1Width / 2, params.height);
    gp_Pnt projectedp2 = sectionAxes.Location().Translated(
        gp_Vec(p2.Z(), p2.Y(), 0).Transformed(trsf));

    gp_Pnt p3(0, wall1Width / 2 - params.wallThickness, params.height);
    gp_Pnt projectedp3 = sectionAxes.Location().Translated(
        gp_Vec(p3.Z(), p3.Y(), 0).Transformed(trsf));

    gp_Pnt p4(0, params.width / 2 - params.wallThickness, 0);
    gp_Pnt projectedp4 = sectionAxes.Location().Translated(
        gp_Vec(p4.Z(), p4.Y(), 0).Transformed(trsf));

    wall1Maker.Add(BRepBuilderAPI_MakeEdge(projectedp1, projectedp2).Edge());
    wall1Maker.Add(BRepBuilderAPI_MakeEdge(projectedp2, projectedp3).Edge());
    wall1Maker.Add(BRepBuilderAPI_MakeEdge(projectedp3, projectedp4).Edge());
    wall1Maker.Add(BRepBuilderAPI_MakeEdge(projectedp4, projectedp1).Edge());
    TopoDS_Shape wall = create_channel_shape(wall1Maker.Wire(), path);
    builder.Add(result, wall);
  }
  {
    BRepBuilderAPI_MakeWire wall2Maker;
    double wall1Width = params.width;
    gp_Pnt p1(0, -wall1Width / 2, 0);
    gp_Pnt projectedp1 = sectionAxes.Location().Translated(
        gp_Vec(p1.Z(), p1.Y(), 0).Transformed(trsf));

    gp_Pnt p2(0, -wall1Width / 2, params.height);
    gp_Pnt projectedp2 = sectionAxes.Location().Translated(
        gp_Vec(p2.Z(), p2.Y(), 0).Transformed(trsf));

    gp_Pnt p3(0, -wall1Width / 2 + params.wallThickness, params.height);
    gp_Pnt projectedp3 = sectionAxes.Location().Translated(
        gp_Vec(p3.Z(), p3.Y(), 0).Transformed(trsf));

    gp_Pnt p4(0, -wall1Width / 2 + params.wallThickness, 0);
    gp_Pnt projectedp4 = sectionAxes.Location().Translated(
        gp_Vec(p4.Z(), p4.Y(), 0).Transformed(trsf));

    wall2Maker.Add(BRepBuilderAPI_MakeEdge(projectedp1, projectedp2).Edge());
    wall2Maker.Add(BRepBuilderAPI_MakeEdge(projectedp2, projectedp3).Edge());
    wall2Maker.Add(BRepBuilderAPI_MakeEdge(projectedp3, projectedp4).Edge());
    wall2Maker.Add(BRepBuilderAPI_MakeEdge(projectedp4, projectedp1).Edge());
    TopoDS_Shape wall = create_channel_shape(wall2Maker.Wire(), path);
    builder.Add(result, wall);
  }

  // 计算路径总长度
  GProp_GProps props;
  BRepGProp::LinearProperties(path, props);
  double totalLength = props.Mass();

  // 创建桥柱
  if (params.columnDiameter > 0 && params.columnHeight > 0) {
    // 沿路径生成桥柱
    double currentPos = 0;
    while (currentPos < totalLength) {
      // 获取路径上当前点的位置和切线方向
      gp_Pnt pointOnPath;
      gp_Vec tangent;

      // 遍历Wire中的边来找到当前位置对应的边
      TopExp_Explorer edgeExplorer(path, TopAbs_EDGE);
      double accumulatedLength = 0;
      bool found = false;

      for (; edgeExplorer.More() && !found; edgeExplorer.Next()) {
        const TopoDS_Edge &edge = TopoDS::Edge(edgeExplorer.Current());

        // 计算当前边的长度
        GProp_GProps edgeProps;
        BRepGProp::LinearProperties(edge, edgeProps);
        double edgeLength = edgeProps.Mass();

        if (currentPos <= accumulatedLength + edgeLength) {
          // 找到包含当前点的边
          BRepAdaptor_Curve curveAdaptor(edge);
          double param = curveAdaptor.FirstParameter() +
                         (currentPos - accumulatedLength) / edgeLength *
                             (curveAdaptor.LastParameter() -
                              curveAdaptor.FirstParameter());

          curveAdaptor.D1(param, pointOnPath, tangent);
          found = true;
        }
        accumulatedLength += edgeLength;
      }

      // 创建桥柱坐标系
      gp_Dir upDir(0, 0, 1);

      // 创建圆柱形桥柱
      gp_Ax2 columnAxis(gp_Pnt(pointOnPath.X(), pointOnPath.Y(),
                               pointOnPath.Z() - params.columnHeight),
                        upDir);
      TopoDS_Shape column =
          BRepPrimAPI_MakeCylinder(columnAxis, params.columnDiameter / 2,
                                   params.columnHeight)
              .Shape();

      builder.Add(result, column);
      currentPos += params.span;
    }
  }

  if (params.style == cable_tray_style::ARCH && (params.points.size() == 2) &&
      totalLength >= params.span) {
    // 沿路径生成桥柱
    double currentPos = 0;

    gp_Pnt prepoint;

    while (currentPos < totalLength) {
      // 获取路径上当前点的位置和切线方向
      gp_Pnt pointOnPath;
      gp_Vec tangent;

      // 遍历Wire中的边来找到当前位置对应的边
      TopExp_Explorer edgeExplorer(path, TopAbs_EDGE);
      double accumulatedLength = 0;
      bool found = false;

      for (; edgeExplorer.More() && !found; edgeExplorer.Next()) {
        const TopoDS_Edge &edge = TopoDS::Edge(edgeExplorer.Current());

        // 计算当前边的长度
        GProp_GProps edgeProps;
        BRepGProp::LinearProperties(edge, edgeProps);
        double edgeLength = edgeProps.Mass();

        if (currentPos <= accumulatedLength + edgeLength) {
          // 找到包含当前点的边
          BRepAdaptor_Curve curveAdaptor(edge);
          double param = curveAdaptor.FirstParameter() +
                         (currentPos - accumulatedLength) / edgeLength *
                             (curveAdaptor.LastParameter() -
                              curveAdaptor.FirstParameter());

          curveAdaptor.D1(param, pointOnPath, tangent);
          found = true;
        }
        accumulatedLength += edgeLength;
      }

      if (currentPos == 0) {
        prepoint = pointOnPath;
      } else {
        gp_Pnt startPoint = prepoint;
        gp_Pnt endPoint = pointOnPath;

        // 计算两点连线的中点
        gp_Pnt arcMidPoint((startPoint.X() + endPoint.X()) / 2,
                           (startPoint.Y() + endPoint.Y()) / 2,
                           (startPoint.Z() + endPoint.Z()) / 2 + params.height +
                               params.arcHeight);

        // 创建拱形起点和终点（高度增加桥架高度）
        gp_Pnt arcStartPoint(startPoint.X(), startPoint.Y(),
                             startPoint.Z() + params.height);
        gp_Pnt arcEndPoint(endPoint.X(), endPoint.Y(),
                           endPoint.Z() + params.height);

        // 计算路径方向向量
        gp_Vec pathVec(arcEndPoint.X() - arcStartPoint.X(),
                       arcEndPoint.Y() - arcStartPoint.Y(),
                       arcEndPoint.Z() - arcStartPoint.Z());

        // 计算垂直于路径方向的向量（假设Z轴向上）
        gp_Vec upVec(0, 0, 1);
        gp_Vec sideVec = pathVec.Crossed(upVec);
        sideVec.Normalize();
        pathVec.Normalize();

        // 计算两侧偏移量
        double offset = params.width / 2;

        // 生成加强筋
        double rebarRadius = params.width / 40;
        int rebarCount = 9;
        // 计算左侧圆弧点
        gp_Pnt leftArcStartPoint(arcStartPoint.X() - sideVec.X() * offset,
                                 arcStartPoint.Y() - sideVec.Y() * offset,
                                 arcStartPoint.Z());
        gp_Pnt leftArcMidPoint(arcMidPoint.X() - sideVec.X() * offset,
                               arcMidPoint.Y() - sideVec.Y() * offset,
                               arcMidPoint.Z());
        gp_Pnt leftArcEndPoint(arcEndPoint.X() - sideVec.X() * offset,
                               arcEndPoint.Y() - sideVec.Y() * offset,
                               arcEndPoint.Z());

        // 计算右侧圆弧点
        gp_Pnt rightArcStartPoint(arcStartPoint.X() + sideVec.X() * offset,
                                  arcStartPoint.Y() + sideVec.Y() * offset,
                                  arcStartPoint.Z());
        gp_Pnt rightArcMidPoint(arcMidPoint.X() + sideVec.X() * offset,
                                arcMidPoint.Y() + sideVec.Y() * offset,
                                arcMidPoint.Z());
        gp_Pnt rightArcEndPoint(arcEndPoint.X() + sideVec.X() * offset,
                                arcEndPoint.Y() + sideVec.Y() * offset,
                                arcEndPoint.Z());
        {

          // 创建弧形路径Wire
          BRepBuilderAPI_MakeWire pathWire;
          pathWire.Add(BRepBuilderAPI_MakeEdge(
                           GC_MakeArcOfCircle(leftArcStartPoint,
                                              leftArcMidPoint, leftArcEndPoint)
                               .Value())
                           .Edge());

          // 创建圆形截面（钢管半径5mm）
          double pipeRadius = params.width / 20;
          gp_Circ sectionCircle(gp_Ax2(leftArcStartPoint, pathVec), pipeRadius);
          TopoDS_Wire sectionWire =
              BRepBuilderAPI_MakeWire(
                  BRepBuilderAPI_MakeEdge(sectionCircle).Edge())
                  .Wire();

          // 沿路径扫掠生成钢管
          BRepOffsetAPI_MakePipeShell pipeMaker(pathWire.Wire());
          pipeMaker.Add(sectionWire);
          pipeMaker.SetMode(Standard_True); // 使用Frenet框架
          pipeMaker.Build();

          if (!pipeMaker.IsDone()) {
            throw Standard_ConstructionError("Failed to generate steel pipe");
          }

          if (!pipeMaker.MakeSolid()) {
            throw Standard_ConstructionError("Failed to make steel pipe solid");
          }

          TopoDS_Shape steelPipe = pipeMaker.Shape();

          builder.Add(result, steelPipe);
        }

        {

          // 创建弧形路径Wire
          BRepBuilderAPI_MakeWire pathWire;
          pathWire.Add(
              BRepBuilderAPI_MakeEdge(GC_MakeArcOfCircle(rightArcStartPoint,
                                                         rightArcMidPoint,
                                                         rightArcEndPoint)
                                          .Value())
                  .Edge());

          // 创建圆形截面（钢管半径5mm）
          double pipeRadius = params.width / 20;
          gp_Circ sectionCircle(gp_Ax2(rightArcStartPoint, pathVec),
                                pipeRadius);
          TopoDS_Wire sectionWire =
              BRepBuilderAPI_MakeWire(
                  BRepBuilderAPI_MakeEdge(sectionCircle).Edge())
                  .Wire();

          // 沿路径扫掠生成钢管
          BRepOffsetAPI_MakePipeShell pipeMaker(pathWire.Wire());
          pipeMaker.Add(sectionWire);
          pipeMaker.SetMode(Standard_True); // 使用Frenet框架
          pipeMaker.Build();

          if (!pipeMaker.IsDone()) {
            throw Standard_ConstructionError("Failed to generate steel pipe");
          }

          if (!pipeMaker.MakeSolid()) {
            throw Standard_ConstructionError("Failed to make steel pipe solid");
          }

          TopoDS_Shape steelPipe = pipeMaker.Shape();
          builder.Add(result, steelPipe);
        }

        {
          // 计算左右钢梁之间的加强筋
          for (int i = 1; i <= rebarCount; ++i) {
            double t = i * 1.0 / (rebarCount + 1);

            // 计算当前和下一个加强筋位置
            gp_Pnt leftPoint, rightPoint;
            gp_Pnt nextLeftPoint, nextRightPoint;

            if (leftArcStartPoint.Distance(leftArcEndPoint) >
                Precision::Confusion()) {
              // 创建圆弧
              GC_MakeArcOfCircle arcMaker(leftArcStartPoint, leftArcMidPoint,
                                          leftArcEndPoint);
              if (arcMaker.IsDone()) {
                Handle(Geom_TrimmedCurve) arc = arcMaker.Value();
                leftPoint = arc->Value(
                    arc->FirstParameter() +
                    t * (arc->LastParameter() - arc->FirstParameter()));
              } else {
                // 如果创建圆弧失败，回退到直线计算
                leftPoint = leftArcStartPoint.Translated(
                    gp_Vec(leftArcEndPoint.X() - leftArcStartPoint.X(),
                           leftArcEndPoint.Y() - leftArcStartPoint.Y(),
                           leftArcEndPoint.Z() - leftArcStartPoint.Z()) *
                    t);
              }
            } else {
              // 如果起点和终点重合，直接使用起点
              leftPoint = leftArcStartPoint;
            }

            if (rightArcStartPoint.Distance(rightArcEndPoint) >
                Precision::Confusion()) {
              // 创建圆弧
              GC_MakeArcOfCircle arcMaker(rightArcStartPoint, rightArcMidPoint,
                                          rightArcEndPoint);
              if (arcMaker.IsDone()) {
                Handle(Geom_TrimmedCurve) arc = arcMaker.Value();
                rightPoint = arc->Value(
                    arc->FirstParameter() +
                    t * (arc->LastParameter() - arc->FirstParameter()));
              } else {
                // 如果创建圆弧失败，回退到直线计算
                rightPoint = rightArcStartPoint.Translated(
                    gp_Vec(rightArcEndPoint.X() - rightArcStartPoint.X(),
                           rightArcEndPoint.Y() - rightArcStartPoint.Y(),
                           rightArcEndPoint.Z() - rightArcStartPoint.Z()) *
                    t);
              }
            } else {
              // 如果起点和终点重合，直接使用起点
              rightPoint = rightArcStartPoint;
            }

            // 创建水平加强筋
            TopoDS_Shape horizontalRebar =
                BRepPrimAPI_MakeCylinder(
                    gp_Ax2(leftPoint, gp_Vec(rightPoint.X() - leftPoint.X(),
                                             rightPoint.Y() - leftPoint.Y(),
                                             rightPoint.Z() - leftPoint.Z())),
                    rebarRadius, leftPoint.Distance(rightPoint))
                    .Shape();
            builder.Add(result, horizontalRebar);

            // 创建左侧垂直加强筋
            gp_Pnt leftBottomPoint =
                startPoint.Translated(gp_Vec(endPoint.X() - startPoint.X(),
                                             endPoint.Y() - startPoint.Y(),
                                             endPoint.Z() - startPoint.Z()) *
                                      t);
            // 应用侧向偏移
            leftBottomPoint.SetX(leftBottomPoint.X() - sideVec.X() * offset);
            leftBottomPoint.SetY(leftBottomPoint.Y() - sideVec.Y() * offset);
            leftBottomPoint.SetZ(leftBottomPoint.Z() + params.height);

            TopoDS_Shape leftVerticalRebar =
                BRepPrimAPI_MakeCylinder(
                    gp_Ax2(leftPoint,
                           gp_Vec(leftBottomPoint.X() - leftPoint.X(),
                                  leftBottomPoint.Y() - leftPoint.Y(),
                                  leftBottomPoint.Z() - leftPoint.Z())),
                    rebarRadius, leftPoint.Distance(leftBottomPoint))
                    .Shape();
            builder.Add(result, leftVerticalRebar);

            // 创建右侧垂直加强筋
            gp_Pnt rightBottomPoint =
                startPoint.Translated(gp_Vec(endPoint.X() - startPoint.X(),
                                             endPoint.Y() - startPoint.Y(),
                                             endPoint.Z() - startPoint.Z()) *
                                      t);
            // 应用侧向偏移
            rightBottomPoint.SetX(rightBottomPoint.X() + sideVec.X() * offset);
            rightBottomPoint.SetY(rightBottomPoint.Y() + sideVec.Y() * offset);
            rightBottomPoint.SetZ(rightBottomPoint.Z() + params.height);

            TopoDS_Shape rightVerticalRebar =
                BRepPrimAPI_MakeCylinder(
                    gp_Ax2(rightPoint,
                           gp_Vec(rightBottomPoint.X() - rightPoint.X(),
                                  rightBottomPoint.Y() - rightPoint.Y(),
                                  rightBottomPoint.Z() - rightPoint.Z())),
                    rebarRadius, rightPoint.Distance(rightBottomPoint))
                    .Shape();
            builder.Add(result, rightVerticalRebar);

            // 如果不是最后一个加强筋，添加斜拉筋
            if (i < rebarCount) {
              // 计算下一个加强筋位置
              double nextT = (i + 1) * 1.0 / (rebarCount + 1);
              gp_Pnt nextLeftPoint, nextRightPoint;

              // 计算下一个左侧点
              if (leftArcStartPoint.Distance(leftArcEndPoint) >
                  Precision::Confusion()) {
                GC_MakeArcOfCircle leftArc(leftArcStartPoint, leftArcMidPoint,
                                           leftArcEndPoint);
                if (leftArc.IsDone()) {
                  nextLeftPoint = leftArc.Value()->Value(
                      leftArc.Value()->FirstParameter() +
                      nextT * (leftArc.Value()->LastParameter() -
                               leftArc.Value()->FirstParameter()));
                } else {
                  nextLeftPoint = leftArcStartPoint.Translated(
                      gp_Vec(leftArcEndPoint.X() - leftArcStartPoint.X(),
                             leftArcEndPoint.Y() - leftArcStartPoint.Y(),
                             leftArcEndPoint.Z() - leftArcStartPoint.Z()) *
                      nextT);
                }
              } else {
                nextLeftPoint = leftArcStartPoint;
              }

              // 计算下一个右侧点
              if (rightArcStartPoint.Distance(rightArcEndPoint) >
                  Precision::Confusion()) {
                GC_MakeArcOfCircle rightArc(rightArcStartPoint,
                                            rightArcMidPoint, rightArcEndPoint);
                if (rightArc.IsDone()) {
                  nextRightPoint = rightArc.Value()->Value(
                      rightArc.Value()->FirstParameter() +
                      nextT * (rightArc.Value()->LastParameter() -
                               rightArc.Value()->FirstParameter()));
                } else {
                  nextRightPoint = rightArcStartPoint.Translated(
                      gp_Vec(rightArcEndPoint.X() - rightArcStartPoint.X(),
                             rightArcEndPoint.Y() - rightArcStartPoint.Y(),
                             rightArcEndPoint.Z() - rightArcStartPoint.Z()) *
                      nextT);
                }
              } else {
                nextRightPoint = rightArcStartPoint;
              }

              gp_Pnt nextLeftBottomPoint =
                  startPoint.Translated(gp_Vec(endPoint.X() - startPoint.X(),
                                               endPoint.Y() - startPoint.Y(),
                                               endPoint.Z() - startPoint.Z()) *
                                        nextT);
              nextLeftBottomPoint.SetX(nextLeftBottomPoint.X() -
                                       sideVec.X() * offset);
              nextLeftBottomPoint.SetY(nextLeftBottomPoint.Y() -
                                       sideVec.Y() * offset);
              nextLeftBottomPoint.SetZ(nextLeftBottomPoint.Z() + params.height);

              gp_Pnt nextRightBottomPoint =
                  startPoint.Translated(gp_Vec(endPoint.X() - startPoint.X(),
                                               endPoint.Y() - startPoint.Y(),
                                               endPoint.Z() - startPoint.Z()) *
                                        nextT);
              nextRightBottomPoint.SetX(nextRightBottomPoint.X() +
                                        sideVec.X() * offset);
              nextRightBottomPoint.SetY(nextRightBottomPoint.Y() +
                                        sideVec.Y() * offset);
              nextRightBottomPoint.SetZ(nextRightBottomPoint.Z() +
                                        params.height);

              // 创建左上到右下的斜拉筋
              TopoDS_Shape diagonalRebar1 =
                  BRepPrimAPI_MakeCylinder(
                      gp_Ax2(leftPoint,
                             gp_Vec(nextRightPoint.X() - leftPoint.X(),
                                    nextRightPoint.Y() - leftPoint.Y(),
                                    nextRightPoint.Z() - leftPoint.Z())),
                      rebarRadius, leftPoint.Distance(nextRightPoint))
                      .Shape();
              builder.Add(result, diagonalRebar1);

              // 创建右上到左下的斜拉筋
              TopoDS_Shape diagonalRebar2 =
                  BRepPrimAPI_MakeCylinder(
                      gp_Ax2(rightPoint,
                             gp_Vec(nextLeftPoint.X() - rightPoint.X(),
                                    nextLeftPoint.Y() - rightPoint.Y(),
                                    nextLeftPoint.Z() - rightPoint.Z())),
                      rebarRadius, rightPoint.Distance(nextLeftPoint))
                      .Shape();
              builder.Add(result, diagonalRebar2);

              // 添加左侧斜拉筋 (从当前左点到下一个左底点)
              if (i < 5) {
                TopoDS_Shape leftDiagonalRebar =
                    BRepPrimAPI_MakeCylinder(
                        gp_Ax2(leftPoint,
                               gp_Vec(nextLeftBottomPoint.X() - leftPoint.X(),
                                      nextLeftBottomPoint.Y() - leftPoint.Y(),
                                      nextLeftBottomPoint.Z() - leftPoint.Z())),
                        rebarRadius, leftPoint.Distance(nextLeftBottomPoint))
                        .Shape();
                builder.Add(result, leftDiagonalRebar);
              } else {
                // 后半部分：从当前底端连向下一个顶端
                TopoDS_Shape leftDiagonalRebar =
                    BRepPrimAPI_MakeCylinder(
                        gp_Ax2(nextLeftPoint,
                               gp_Vec(leftBottomPoint.X() - nextLeftPoint.X(),
                                      leftBottomPoint.Y() - nextLeftPoint.Y(),
                                      leftBottomPoint.Z() - nextLeftPoint.Z())),
                        rebarRadius, nextLeftPoint.Distance(leftBottomPoint))
                        .Shape();
                builder.Add(result, leftDiagonalRebar);
              }

              // 添加右侧斜拉筋 (从当前右点到下一个右底点)
              if (i < 5) {
                TopoDS_Shape rightDiagonalRebar =
                    BRepPrimAPI_MakeCylinder(
                        gp_Ax2(
                            rightPoint,
                            gp_Vec(nextRightBottomPoint.X() - rightPoint.X(),
                                   nextRightBottomPoint.Y() - rightPoint.Y(),
                                   nextRightBottomPoint.Z() - rightPoint.Z())),
                        rebarRadius, rightPoint.Distance(nextRightBottomPoint))
                        .Shape();
                builder.Add(result, rightDiagonalRebar);
              } else {
                // 后半部分：从当前底端连向下一个顶端
                TopoDS_Shape rightDiagonalRebar =
                    BRepPrimAPI_MakeCylinder(
                        gp_Ax2(
                            nextRightPoint,
                            gp_Vec(rightBottomPoint.X() - nextRightPoint.X(),
                                   rightBottomPoint.Y() - nextRightPoint.Y(),
                                   rightBottomPoint.Z() - nextRightPoint.Z())),
                        rebarRadius, nextRightPoint.Distance(rightBottomPoint))
                        .Shape();
                builder.Add(result, rightDiagonalRebar);
              }
            }
          }
        }

        prepoint = pointOnPath;
      }

      currentPos += params.span;
    }
  }

  return result;
}


TopoDS_Shape create_cable_tray(const cable_tray_params &params,
                               const gp_Pnt &position, const gp_Dir &direction,
                               const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(direction.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Direction and xDir must be perpendicular");
  }

  // 创建标准方向的电缆桥架
  TopoDS_Shape tray = create_cable_tray(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, direction, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(tray, transformation);
  return transform.Shape();
}


TopoDS_Wire create_cable_tray_centerline(const cable_tray_params &params) {
  // 参数验证
  if (params.width <= 0 || params.height <= 0 || params.span <= 0) {
    throw Standard_ConstructionError("Width, height and span must be positive");
  }
  if (params.points.size() < 2) {
    throw Standard_ConstructionError("At least 2 points are required");
  }

  // 创建路径线框
  BRepBuilderAPI_MakeWire pathWire;

  // 处理点序列
  for (size_t i = 0; i < params.points.size() - 1; i++) {
    const gp_Pnt &current = params.points[i].position;
    const gp_Pnt &next = params.points[i + 1].position;

    if (params.points[i].type == channel_point_type::LINE &&
        params.points[i + 1].type == channel_point_type::LINE) { // 普通节点
      // 创建直线段
      pathWire.Add(BRepBuilderAPI_MakeEdge(current, next).Edge());
    } else if (params.points[i].type == channel_point_type::ARC) { // 弧形节点
      // 确保有前一个点和后一个点
      if (i == 0 || i == params.points.size() - 1) {
        throw Standard_ConstructionError("弧形节点需要前后都有节点");
      }

      const gp_Pnt &prev = params.points[i - 1].position;

      // 创建三点圆弧
      pathWire.Add(BRepBuilderAPI_MakeEdge(
                       GC_MakeArcOfCircle(prev, current, next).Value())
                       .Edge());
    }
  }

  if (!pathWire.IsDone()) {
    throw Standard_ConstructionError("路径线框创建失败");
  }

  return pathWire.Wire();
}


TopoDS_Shape create_cable_L_beam(const cable_L_beam_params &params) {
  // 参数验证
  if (params.length <= 0 || params.width <= 0 || params.height <= 0) {
    throw Standard_ConstructionError("L, W and H must be positive");
  }

  TopoDS_Shape beam =
      BRepPrimAPI_MakeBox(gp_Pnt(-params.length / 2, -params.width / 2, 0),
                          params.length, params.width, params.height)
          .Shape();

  return beam;
}


TopoDS_Shape create_cable_L_beam(const cable_L_beam_params &params,
                                 const gp_Pnt &position,
                                 const gp_Dir &xDirection,
                                 const gp_Dir &zDirection) {
  // 正交性校验
  if (Abs(xDirection.Dot(zDirection)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "X and Z directions must be perpendicular");
  }

  // 创建标准方向的L梁
  TopoDS_Shape LBeam = create_cable_L_beam(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, zDirection, xDirection);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(LBeam, transformation);
  return transform.Shape();
}


TopoDS_Shape create_manhole(const manhole_params &params) {
  // 参数验证
  if (params.length <= 0 || params.height <= 0 || params.wallThickness <= 0) {
    throw Standard_ConstructionError(
        "Length, height and wall thickness must be positive");
  }
  if (params.style == manhole_style::RECTANGULAR && params.width <= 0) {
    throw Standard_ConstructionError(
        "Width must be positive for rectangular manhole");
  }

  TopoDS_Shape manhole;

  switch (params.style) {
  case manhole_style::CIRCULAR: {
    // 创建圆形人孔
    double outerRadius = params.length / 2;
    double innerRadius = outerRadius - params.wallThickness;

    // 创建外壁圆柱
    TopoDS_Shape outerCylinder =
        BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp::DZ()), outerRadius,
                                 params.height)
            .Shape();

    // 创建内壁圆柱(空心部分)
    if (innerRadius > 0) {
      TopoDS_Shape innerCylinder =
          BRepPrimAPI_MakeCylinder(
              gp_Ax2(gp_Pnt(0, 0, -params.height), gp::DZ()), innerRadius,
              params.height * 2)
              .Shape();
      manhole = BRepAlgoAPI_Cut(outerCylinder, innerCylinder).Shape();
    } else {
      manhole = outerCylinder;
    }
    break;
  }

  case manhole_style::RECTANGULAR: {
    // 创建方形人孔
    double outerLength = params.length;
    double outerWidth = params.width;
    double innerLength = params.length - 2 * params.wallThickness;
    double innerWidth = params.width - 2 * params.wallThickness;

    // 创建外壁长方体
    TopoDS_Shape outerBox =
        BRepPrimAPI_MakeBox(gp_Pnt(-outerLength / 2, -outerWidth / 2, 0),
                            outerLength, outerWidth, params.height)
            .Shape();

    // 创建内壁长方体(空心部分)
    if (innerLength > 0 && innerWidth > 0) {
      TopoDS_Shape innerBox =
          BRepPrimAPI_MakeBox(gp_Pnt(-innerLength / 2, -innerWidth / 2, -1),
                              innerLength, innerWidth, params.height + 2)
              .Shape();
      manhole = BRepAlgoAPI_Cut(outerBox, innerBox).Shape();
    } else {
      manhole = outerBox;
    }
    break;
  }
  }

  return manhole;
}


TopoDS_Shape create_manhole(const manhole_params &params,
                            const gp_Pnt &position, const gp_Dir &direction,
                            const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(direction.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Direction and xDir must be perpendicular");
  }

  // 创建标准方向的人孔
  TopoDS_Shape manhole = create_manhole(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, direction, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(manhole, transformation);
  return transform.Shape();
}


TopoDS_Shape create_manhole_cover(const manhole_cover_params &params) {
  // 参数验证
  if (params.length <= 0.0) {
    throw Standard_ConstructionError("Length/diameter must be positive");
  }
  if (params.thickness <= 0.0) {
    throw Standard_ConstructionError("Thickness must be positive");
  }
  if (params.style == manhole_cover_style::RECTANGULAR && params.width <= 0.0) {
    throw Standard_ConstructionError(
        "Width must be positive for rectangle cover");
  }

  TopoDS_Shape cover;

  if (params.style == manhole_cover_style::CIRCULAR) {
    // 创建圆形井盖
    gp_Ax2 axis(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
    BRepPrimAPI_MakeCylinder cylinderMaker(axis, params.length / 2,
                                           params.thickness);
    cover = cylinderMaker.Shape();
  } else {
    // 创建矩形井盖
    gp_Pnt corner(-params.length / 2, -params.width / 2, 0);
    BRepPrimAPI_MakeBox boxMaker(corner, params.length, params.width,
                                 params.thickness);
    cover = boxMaker.Shape();

    // 添加倒角处理
    BRepFilletAPI_MakeChamfer chamferMaker(cover);
    TopExp_Explorer edgeExplorer(cover, TopAbs_EDGE);
    for (; edgeExplorer.More(); edgeExplorer.Next()) {
      const TopoDS_Edge &edge = TopoDS::Edge(edgeExplorer.Current());
      chamferMaker.Add(params.thickness / 10, edge); // 倒角大小为厚度的1/10
    }
    if (chamferMaker.IsDone()) {
      cover = chamferMaker.Shape();
    }
  }

  return cover;
}


TopoDS_Shape create_manhole_cover(const manhole_cover_params &params,
                                  const gp_Pnt &position,
                                  const gp_Dir &direction, const gp_Dir &xDir) {
  // 首先创建原点处的井盖
  TopoDS_Shape cover = create_manhole_cover(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), gp_Dir(1, 0, 0));
  gp_Ax3 targetAx3(position, direction, xDir);

  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(cover, transformation);
  return transform.Shape();
}


TopoDS_Shape create_ladder(const ladder_params &params) {
  // 参数验证
  if (params.length <= 0 || params.width <= 0 || params.thickness <= 0) {
    throw Standard_ConstructionError(
        "Length, width and thickness must be positive");
  }

  // 创建爬梯主体
  TopoDS_Shape ladder =
      BRepPrimAPI_MakeBox(gp_Pnt(-params.length / 2, -params.width, 0),
                          params.length, params.width, params.thickness)
          .Shape();

  return ladder;
}


TopoDS_Shape create_ladder(const ladder_params &params, const gp_Pnt &position,
                           const gp_Dir &direction, const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(direction.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Direction and xDir must be perpendicular");
  }

  // 创建标准方向的爬梯
  TopoDS_Shape ladder = create_ladder(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, direction, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(ladder, transformation);
  return transform.Shape();
}


TopoDS_Shape create_footpath(const footpath_params &params) {
  // 参数验证
  if (params.height <= 0 || params.width <= 0) {
    throw Standard_ConstructionError("Height and width must be positive");
  }

  BRepBuilderAPI_MakeWire baseMaker;

  // 创建路径线框
  BRepBuilderAPI_MakeWire pathWire;

  // 处理点序列
  for (size_t i = 0; i < params.points.size() - 1; i++) {
    const gp_Pnt &current = params.points[i].position;
    const gp_Pnt &next = params.points[i + 1].position;

    if (params.points[i].type == channel_point_type::LINE &&
        params.points[i + 1].type == channel_point_type::LINE) { // 普通节点
      // 创建直线段
      pathWire.Add(BRepBuilderAPI_MakeEdge(current, next).Edge());
    } else if (params.points[i].type == channel_point_type::ARC) { // 弧形节点
      // 确保有前一个点和后一个点
      if (i == 0 || i == params.points.size() - 1) {
        throw Standard_ConstructionError("弧形节点需要前后都有节点");
      }

      const gp_Pnt &prev = params.points[i - 1].position;

      // 创建三点圆弧
      pathWire.Add(BRepBuilderAPI_MakeEdge(
                       GC_MakeArcOfCircle(prev, current, next).Value())
                       .Edge());
    }
  }

  if (!pathWire.IsDone()) {
    throw Standard_ConstructionError("路径线框创建失败");
  }

  TopoDS_Wire path = pathWire.Wire();

  // 获取路径起始点的切线方向
  BRepAdaptor_CompCurve curveAdaptor(path);
  gp_Pnt startPoint;
  gp_Vec startTangent;
  curveAdaptor.D1(curveAdaptor.FirstParameter(), startPoint, startTangent);

  // 在创建截面圆之前添加方向修正
  gp_Dir tanDir = startTangent.Normalized();
  gp_Dir refDir = gp::DZ(); // 默认参考方向为全局Y轴

  // 如果tanDir平行于全局X轴，调整参考方向为全局Z轴
  if (IsParallel(tanDir, gp::DX())) {
    refDir = gp::DZ();
  }
  gp_Ax2 sectionAxes(startPoint, tanDir, refDir);

  // 创建变换对象
  gp_Trsf trsf;
  trsf.SetTransformation(sectionAxes, gp_Ax2(gp::Origin(), gp::DZ()));

  // YZ平面上的点坐标 (X=0)
  gp_Pnt p1(0, -params.width / 2, -params.height);
  gp_Pnt p2(0, params.width / 2, -params.height);
  gp_Pnt p3(0, params.width / 2, 0);
  gp_Pnt p4(0, -params.width / 2, 0);

  gp_Pnt projectedp1 = sectionAxes.Location().Translated(
      gp_Vec(p1.Z(), p1.Y(), 0).Transformed(trsf));
  gp_Pnt projectedp2 = sectionAxes.Location().Translated(
      gp_Vec(p2.Z(), p2.Y(), 0).Transformed(trsf));
  gp_Pnt projectedp3 = sectionAxes.Location().Translated(
      gp_Vec(p3.Z(), p3.Y(), 0).Transformed(trsf));
  gp_Pnt projectedp4 = sectionAxes.Location().Translated(
      gp_Vec(p4.Z(), p4.Y(), 0).Transformed(trsf));

  baseMaker.Add(BRepBuilderAPI_MakeEdge(projectedp1, projectedp2).Edge());
  baseMaker.Add(BRepBuilderAPI_MakeEdge(projectedp2, projectedp3).Edge());
  baseMaker.Add(BRepBuilderAPI_MakeEdge(projectedp3, projectedp4).Edge());
  baseMaker.Add(BRepBuilderAPI_MakeEdge(projectedp4, projectedp1).Edge());

  return create_channel_shape(baseMaker.Wire(), path);
}


TopoDS_Shape create_footpath(const footpath_params &params,
                             const gp_Pnt &position, const gp_Dir &direction,
                             const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(direction.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Direction and xDir must be perpendicular");
  }

  // 创建标准方向的步道
  TopoDS_Shape footpath = create_footpath(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, direction, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(footpath, transformation);
  return transform.Shape();
}


TopoDS_Wire create_footpath_centerline(const footpath_params &params) {
  // 创建路径线框
  BRepBuilderAPI_MakeWire pathWire;

  // 处理点序列
  for (size_t i = 0; i < params.points.size() - 1; i++) {
    const gp_Pnt &current = params.points[i].position;
    const gp_Pnt &next = params.points[i + 1].position;

    if (params.points[i].type == channel_point_type::LINE &&
        params.points[i + 1].type == channel_point_type::LINE) { // 普通节点
      // 创建直线段
      pathWire.Add(BRepBuilderAPI_MakeEdge(current, next).Edge());
    } else if (params.points[i].type == channel_point_type::ARC) { // 弧形节点
      // 确保有前一个点和后一个点
      if (i == 0 || i == params.points.size() - 1) {
        throw Standard_ConstructionError("弧形节点需要前后都有节点");
      }

      const gp_Pnt &prev = params.points[i - 1].position;

      // 创建三点圆弧
      pathWire.Add(BRepBuilderAPI_MakeEdge(
                       GC_MakeArcOfCircle(prev, current, next).Value())
                       .Edge());
    }
  }

  if (!pathWire.IsDone()) {
    throw Standard_ConstructionError("路径线框创建失败");
  }

  return pathWire.Wire();
}


TopoDS_Shape create_shaft_chamber(const shaft_chamber_params &params) {
  // 参数验证
  if (params.supportDiameter <= 0 || params.workingHeight <= 0) {
    throw Standard_ConstructionError("Diameter and height must be positive");
  }
  if (params.supportWallThickness < 0 || params.outerWallThickness < 0 ||
      params.innerWallThickness < 0 || params.topThickness < 0) {
    throw Standard_ConstructionError("Thickness values must be non-negative");
  }

  // 创建支护结构（外圆柱）
  gp_Ax2 supportAxis(gp_Pnt(0, 0, params.workingHeight), gp::DZ());
  TopoDS_Shape support;
  if (params.supportWallThickness > 0 && params.supportHeight > 0) {
    double supportRadius =
        params.supportDiameter / 2 + params.supportWallThickness;
    support =
        BRepPrimAPI_MakeCylinder(supportAxis, supportRadius,
                                 params.supportHeight + params.topThickness)
            .Shape();

    if (params.supportWallThickness > 0) {
      gp_Ax2 supportInnerAxis(
          gp_Pnt(0, 0, params.workingHeight + params.topThickness), gp::DZ());

      // 创建内壁空腔
      TopoDS_Shape innerCavity =
          BRepPrimAPI_MakeCylinder(supportInnerAxis, params.supportDiameter / 2,
                                   params.supportHeight)
              .Shape();
      support = BRepAlgoAPI_Cut(support, innerCavity).Shape();
    }
  }

  // 创建工作仓外壁
  TopoDS_Shape outerWall;
  if (params.outerWallThickness > 0) {
    gp_Ax2 outerAxis(gp_Pnt(0, 0, 0), gp::DZ());
    double outerRadius = params.innerDiameter / 2 + params.innerWallThickness +
                         params.outerWallThickness;
    outerWall =
        BRepPrimAPI_MakeCylinder(outerAxis, outerRadius, params.workingHeight)
            .Shape();

    if (params.innerWallThickness > 0) {
      // 创建内壁空腔
      TopoDS_Shape innerCavity =
          BRepPrimAPI_MakeCylinder(outerAxis, params.innerDiameter / 2,
                                   params.workingHeight)
              .Shape();
      outerWall = BRepAlgoAPI_Cut(outerWall, innerCavity).Shape();
    }

    if (!support.IsNull()) {
      outerWall = BRepAlgoAPI_Fuse(outerWall, support).Shape();
    }
  }

  return outerWall;
}


TopoDS_Shape create_shaft_chamber(const shaft_chamber_params &params,
                                  const gp_Pnt &position,
                                  const gp_Dir &direction, const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(direction.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Direction and xDir must be perpendicular");
  }

  // 创建标准方向的竖井仓
  TopoDS_Shape well = create_shaft_chamber(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, direction, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(well, transformation);
  return transform.Shape();
}


TopoDS_Shape create_tunnel_compartment_partition(
    const tunnel_compartment_partition_params &params) {
  try {
    // 创建矩形隔板
    gp_Pnt position(-params.width / 2, -params.width / 2, -params.thickness);
    BRepPrimAPI_MakeBox boxMaker(position, params.width, params.width,
                                 params.thickness);
    return boxMaker.Shape();
  } catch (const Standard_Failure &e) {
    throw Standard_ConstructionError(
        "Failed to create tunnel compartment partition");
  }
}


TopoDS_Shape create_tunnel_compartment_partition(
    const tunnel_compartment_partition_params &params, const gp_Pnt &position,
    const gp_Dir &normal, const gp_Dir &xDir) {
  // 先创建基本形状
  TopoDS_Shape shape = create_tunnel_compartment_partition(params);

  // 创建变换矩阵
  gp_Trsf transform;
  transform.SetTransformation(gp_Ax3(position, normal, xDir));

  // 应用变换
  BRepBuilderAPI_Transform transformer(shape, transform);
  return transformer.Shape();
}


TopoDS_Shape
create_tunnel_partition_board(const tunnel_partition_board_params &params) {
  // 参数验证
  if (params.thickness <= 0) {
    throw Standard_ConstructionError("Partition thickness must be positive");
  }
  if (params.holeCount != params.holePositions.size() ||
      params.holeCount != params.holeStyles.size() ||
      params.holeCount != params.holeDiameters.size() ||
      params.holeCount != params.holeWidths.size()) {
    throw Standard_ConstructionError("Hole parameters count mismatch");
  }

  // 创建隔板主体
  TopoDS_Shape partition;
  if (params.style == tunnel_partition_board_style::CIRCULAR) { // 圆形隔板
    partition = BRepPrimAPI_MakeCylinder(gp_Ax2(gp::Origin(), gp::DZ()),
                                         params.length / 2, params.thickness)
                    .Shape();
  } else { // 方形隔板
    partition =
        BRepPrimAPI_MakeBox(gp_Pnt(-params.length / 2, -params.width / 2, 0),
                            params.length, params.width, params.thickness)
            .Shape();
  }

  // 创建开孔
  for (int i = 0; i < params.holeCount; ++i) {
    TopoDS_Shape hole;
    gp_Pnt center(params.holePositions[i].X(), params.holePositions[i].Y(), -1);

    if (params.holeStyles[i] == 1) { // 圆形孔
      hole = BRepPrimAPI_MakeCylinder(gp_Ax2(center, gp::DZ()),
                                      params.holeDiameters[i] / 2,
                                      params.thickness + 2)
                 .Shape(); // 加2mm确保完全穿透
    } else {               // 方形孔
      hole =
          BRepPrimAPI_MakeBox(gp_Pnt(center.X() - params.holeDiameters[i] / 2,
                                     center.Y() - params.holeWidths[i] / 2,
                                     -1), // 确保完全穿透
                              params.holeDiameters[i], params.holeWidths[i],
                              params.thickness + 2)
              .Shape();
    }

    // 从隔板中减去孔
    partition = BRepAlgoAPI_Cut(partition, hole).Shape();
  }

  return partition;
}


TopoDS_Shape
create_tunnel_partition_board(const tunnel_partition_board_params &params,
                              const gp_Pnt &position, const gp_Dir &normal,
                              const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(normal.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Normal and direction must be perpendicular");
  }

  // 创建标准方向的隔板
  TopoDS_Shape partition = create_tunnel_partition_board(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, normal, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(partition, transformation);
  return transform.Shape();
}


TopoDS_Shape
create_ventilation_pavilion(const ventilation_pavilion_params &params) {
  // 参数验证
  if (params.height <= 0 || params.baseHeight <= 0) {
    throw Standard_ConstructionError("Height values must be positive");
  }

  // 创建底座

  // 创建底座（改为棱台形状）
  gp_Pnt baseBottom1(-params.bottomLength / 2, -params.bottomWidth / 2, 0);
  gp_Pnt baseBottom2(params.bottomLength / 2, -params.bottomWidth / 2, 0);
  gp_Pnt baseBottom3(params.bottomLength / 2, params.bottomWidth / 2, 0);
  gp_Pnt baseBottom4(-params.bottomLength / 2, params.bottomWidth / 2, 0);

  // 棱台上部与主体相同尺寸
  gp_Pnt baseTop1(-params.middleLength / 2, -params.middleWidth / 2,
                  params.baseHeight);
  gp_Pnt baseTop2(params.middleLength / 2, -params.middleWidth / 2,
                  params.baseHeight);
  gp_Pnt baseTop3(params.middleLength / 2, params.middleWidth / 2,
                  params.baseHeight);
  gp_Pnt baseTop4(-params.middleLength / 2, params.middleWidth / 2,
                  params.baseHeight);

  // 创建上下底面
  BRepBuilderAPI_MakeWire bottomWire;
  bottomWire.Add(BRepBuilderAPI_MakeEdge(baseBottom1, baseBottom2));
  bottomWire.Add(BRepBuilderAPI_MakeEdge(baseBottom2, baseBottom3));
  bottomWire.Add(BRepBuilderAPI_MakeEdge(baseBottom3, baseBottom4));
  bottomWire.Add(BRepBuilderAPI_MakeEdge(baseBottom4, baseBottom1));

  BRepBuilderAPI_MakeWire topWire;
  topWire.Add(BRepBuilderAPI_MakeEdge(baseTop1, baseTop2));
  topWire.Add(BRepBuilderAPI_MakeEdge(baseTop2, baseTop3));
  topWire.Add(BRepBuilderAPI_MakeEdge(baseTop3, baseTop4));
  topWire.Add(BRepBuilderAPI_MakeEdge(baseTop4, baseTop1));

  // 创建棱台的侧面（通过放样）
  TopoDS_Shape base;
  BRepOffsetAPI_ThruSections loftMaker(Standard_True); // 生成实体
  loftMaker.AddWire(bottomWire.Wire());
  loftMaker.AddWire(topWire.Wire());
  loftMaker.Build();
  if (!loftMaker.IsDone())
    throw Standard_ConstructionError("棱台放样失败");
  base = loftMaker.Shape();

  // 创建主体
  gp_Pnt bodyOrigin(-params.middleLength / 2, -params.middleWidth / 2,
                    params.baseHeight);
  TopoDS_Shape body = BRepPrimAPI_MakeBox(bodyOrigin, params.middleLength,
                                          params.middleWidth, params.height)
                          .Shape();

  gp_Pnt roofOrigin(-params.topLength / 2, -params.topWidth / 2,
                    params.height + params.baseHeight);
  TopoDS_Shape roofBody = BRepPrimAPI_MakeBox(roofOrigin, params.topLength,
                                              params.topWidth, params.topHeight)
                              .Shape();

  // 创建屋顶
  gp_Pnt roofBaseCenter(0, 0,
                        params.height + params.baseHeight + params.topHeight);
  gp_Pnt roofTop(0, 0,
                 params.height + params.baseHeight + params.topHeight +
                     params.topHeight);

  // 创建金字塔底面四个角点
  gp_Pnt base1(-params.topLength / 2, -params.topWidth / 2, roofBaseCenter.Z());
  gp_Pnt base2(params.topLength / 2, -params.topWidth / 2, roofBaseCenter.Z());
  gp_Pnt base3(params.topLength / 2, params.topWidth / 2, roofBaseCenter.Z());
  gp_Pnt base4(-params.topLength / 2, params.topWidth / 2, roofBaseCenter.Z());

  // 创建金字塔的四个三角形面
  BRepBuilderAPI_MakeEdge edge1(base1, base2);
  BRepBuilderAPI_MakeEdge edge2(base2, roofTop);
  BRepBuilderAPI_MakeEdge edge3(roofTop, base1);
  BRepBuilderAPI_MakeWire wire1;
  wire1.Add(edge1);
  wire1.Add(edge2);
  wire1.Add(edge3);

  TopoDS_Wire faceWire1 = wire1.Wire();

  if (!faceWire1.Closed()) {
    throw Standard_ConstructionError("Face wire is not closed");
  }

  BRepBuilderAPI_MakeFace face1(faceWire1);

  // 其他三个面也采用同样的方式创建
  BRepBuilderAPI_MakeEdge edge4(base2, base3);
  BRepBuilderAPI_MakeEdge edge5(base3, roofTop);
  BRepBuilderAPI_MakeEdge edge6(roofTop, base2);
  BRepBuilderAPI_MakeWire wire2;
  wire2.Add(edge4);
  wire2.Add(edge5);
  wire2.Add(edge6);

  TopoDS_Wire faceWire2 = wire2.Wire();

  if (!faceWire2.Closed()) {
    throw Standard_ConstructionError("Face wire is not closed");
  }

  BRepBuilderAPI_MakeFace face2(faceWire2);

  BRepBuilderAPI_MakeEdge edge7(base3, base4);
  BRepBuilderAPI_MakeEdge edge8(base4, roofTop);
  BRepBuilderAPI_MakeEdge edge9(roofTop, base3);
  BRepBuilderAPI_MakeWire wire3;
  wire3.Add(edge7);
  wire3.Add(edge8);
  wire3.Add(edge9);

  TopoDS_Wire faceWire3 = wire3.Wire();

  if (!faceWire3.Closed()) {
    throw Standard_ConstructionError("Face wire is not closed");
  }

  BRepBuilderAPI_MakeFace face3(faceWire3);

  BRepBuilderAPI_MakeEdge edge10(base4, base1);
  BRepBuilderAPI_MakeEdge edge11(base1, roofTop);
  BRepBuilderAPI_MakeEdge edge12(roofTop, base4);
  BRepBuilderAPI_MakeWire wire4;
  wire4.Add(edge10);
  wire4.Add(edge11);
  wire4.Add(edge12);

  TopoDS_Wire faceWire4 = wire4.Wire();

  if (!faceWire4.Closed()) {
    throw Standard_ConstructionError("Face wire is not closed");
  }

  BRepBuilderAPI_MakeFace face4(faceWire4);

  // 创建金字塔底面
  BRepBuilderAPI_MakeWire baseWire;
  baseWire.Add(BRepBuilderAPI_MakeEdge(base1, base2));
  baseWire.Add(BRepBuilderAPI_MakeEdge(base2, base3));
  baseWire.Add(BRepBuilderAPI_MakeEdge(base3, base4));
  baseWire.Add(BRepBuilderAPI_MakeEdge(base4, base1));

  TopoDS_Wire faceWire5 = baseWire.Wire();

  if (!faceWire5.Closed()) {
    throw Standard_ConstructionError("Face wire is not closed");
  }

  BRepBuilderAPI_MakeFace baseFace(faceWire5);

  // 组合所有面形成封闭的金字塔形状
  BRepBuilderAPI_Sewing sewer;
  sewer.Add(face1.Face());
  sewer.Add(face2.Face());
  sewer.Add(face3.Face());
  sewer.Add(face4.Face());
  sewer.Add(baseFace.Face());
  sewer.Perform();

  TopoDS_Shape roof = sewer.SewedShape();

  // 添加通风格栅（长条洞）
  double holeWidth = params.middleWidth * 0.8;     // 洞长为面宽的0.8倍
  double holeLength = params.middleLength * 0.8;   // 洞长为面宽的0.8倍
  double holeHeight = (params.height / 8.0) * 0.3; // 洞高为body高的0.05倍

  // 在（前、后）面上均匀挖8个洞
  for (int j = 0; j < 8; ++j) {
    // 计算洞的位置（垂直方向均匀分布）
    double holePosZ = params.baseHeight + (j + 0.5) * (params.height / 8.0);

    // 根据面的方向确定洞的长宽

    TopoDS_Shape hole =
        BRepPrimAPI_MakeBox(
            gp_Pnt(-holeLength / 2, -params.middleLength, holePosZ), holeLength,
            params.middleLength * 2, holeHeight)
            .Shape();

    body = BRepAlgoAPI_Cut(body, hole).Shape();
  }

  // 在（左，右）面上均匀挖8个洞
  for (int j = 0; j < 8; ++j) {
    // 计算洞的位置（垂直方向均匀分布）
    double holePosZ = params.baseHeight + (j + 0.5) * (params.height / 8.0);

    // 创建左右方向的通风格栅
    TopoDS_Shape hole =
        BRepPrimAPI_MakeBox(
            gp_Pnt(-params.middleWidth, -holeWidth / 2, holePosZ),
            params.middleWidth * 2, holeWidth, holeHeight)
            .Shape();

    body = BRepAlgoAPI_Cut(body, hole).Shape();
  }

  BRep_Builder builder;
  TopoDS_Compound compound;
  builder.MakeCompound(compound);
  builder.Add(compound, roof);
  builder.Add(compound, roofBody);
  builder.Add(compound, body);
  builder.Add(compound, base);

  return compound;
}


TopoDS_Shape
create_ventilation_pavilion(const ventilation_pavilion_params &params,
                            const gp_Pnt &position, const gp_Dir &direction,
                            const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(direction.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Direction and xDir must be perpendicular");
  }

  // 创建标准方向的风亭
  TopoDS_Shape pavilion = create_ventilation_pavilion(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, direction, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(pavilion, transformation);
  return transform.Shape();
}


TopoDS_Shape create_straight_ventilation_duct(
    const straight_ventilation_duct_params &params) {
  // 参数验证
  if (params.diameter <= 0 || params.height <= 0) {
    throw Standard_ConstructionError("Diameter and height must be positive");
  }
  if (params.wallThickness < 0 || params.wallThickness >= params.diameter / 2) {
    throw Standard_ConstructionError("Wall thickness must be in [0, D/2)");
  }

  // 创建外圆柱
  gp_Ax2 axis(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  BRepPrimAPI_MakeCylinder outerCylinder(axis, params.diameter / 2,
                                         params.height);
  TopoDS_Shape duct = outerCylinder.Shape();

  // 如果有壁厚，创建内圆柱并进行布尔减操作
  if (params.wallThickness > 0) {
    double innerRadius = params.diameter / 2 - params.wallThickness;
    BRepPrimAPI_MakeCylinder innerCylinder(axis, innerRadius, params.height);
    duct = BRepAlgoAPI_Cut(duct, innerCylinder.Shape()).Shape();
  }

  return duct;
}


TopoDS_Shape
create_straight_ventilation_duct(const straight_ventilation_duct_params &params,
                                 const gp_Pnt &position,
                                 const gp_Dir &direction, const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(direction.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Direction and xDir must be perpendicular");
  }

  // 创建标准方向的直通风道
  TopoDS_Shape duct = create_straight_ventilation_duct(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, direction, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(duct, transformation);
  return transform.Shape();
}


TopoDS_Shape
create_oblique_ventilation_duct(const oblique_ventilation_duct_params &params) {
  // 参数验证
  if (params.hoodRoomLength <= 0 || params.hoodRoomWidth <= 0 ||
      params.hoodRoomHeight <= 0) {
    throw Standard_ConstructionError("Hood room dimensions must be positive");
  }
  if (params.ductDiameter <= 0 || params.ductLength <= 0) {
    throw Standard_ConstructionError("Duct dimensions must be positive");
  }
  if (params.baseRoomLength <= 0 || params.baseRoomWidth <= 0 ||
      params.baseRoomHeight <= 0) {
    throw Standard_ConstructionError("Base room dimensions must be positive");
  }

  // 创建风帽室（长方体）
  gp_Pnt hoodOrigin(-params.hoodRoomWidth / 2, -params.hoodRoomLength / 2, 0);
  TopoDS_Shape hoodRoom =
      BRepPrimAPI_MakeBox(hoodOrigin, params.hoodRoomWidth,
                          params.hoodRoomLength, params.hoodRoomHeight)
          .Shape();

  // 创建风帽室内腔（如果壁厚大于0）
  if (params.hoodWallThickness > 0) {
    gp_Pnt innerOrigin(-params.hoodRoomWidth / 2 + params.hoodWallThickness,
                       -params.hoodRoomLength / 2 + params.hoodWallThickness,
                       0);
    TopoDS_Shape innerHood =
        BRepPrimAPI_MakeBox(
            innerOrigin, params.hoodRoomWidth - 2 * params.hoodWallThickness,
            params.hoodRoomLength - 2 * params.hoodWallThickness,
            params.hoodRoomHeight - params.hoodWallThickness)
            .Shape();
    hoodRoom = BRepAlgoAPI_Cut(hoodRoom, innerHood).Shape();
  }

  // 创建风基座（长方体）
  double baseCenterX =
      params.ductLength + params.hoodRoomWidth / 2 + params.baseRoomWidth / 2;
  gp_Pnt baseOrigin(baseCenterX - params.baseWidth / 2, -params.baseLength / 2,
                    params.ductHeightDifference);
  TopoDS_Shape base = BRepPrimAPI_MakeBox(baseOrigin, params.baseWidth,
                                          params.baseLength, params.baseHeight)
                          .Shape();

  // 创建风基室（长方体）
  gp_Pnt baseRoomOrigin(
      baseCenterX - params.baseRoomWidth / 2 - params.baseRoomWallThickness,
      -params.baseRoomLength / 2 - params.baseRoomWallThickness,
      params.ductHeightDifference + params.baseHeight);
  TopoDS_Shape baseRoom =
      BRepPrimAPI_MakeBox(
          baseRoomOrigin,
          params.baseRoomWidth + (2 * params.baseRoomWallThickness),
          params.baseRoomLength + (2 * params.baseRoomWallThickness),
          params.baseRoomHeight)
          .Shape();

  // 创建风基室内腔（如果壁厚大于0）
  if (params.baseRoomWallThickness > 0) {
    gp_Pnt innerBaseRoomOrigin(baseCenterX - params.baseRoomWidth / 2,
                               -params.baseRoomLength / 2,
                               params.ductHeightDifference + params.baseHeight);
    TopoDS_Shape innerBaseRoom =
        BRepPrimAPI_MakeBox(innerBaseRoomOrigin, params.baseRoomWidth,
                            params.baseRoomLength, params.baseRoomHeight)
            .Shape();
    baseRoom = BRepAlgoAPI_Cut(baseRoom, innerBaseRoom).Shape();
  }

  // 创建风通道（倾斜圆柱）
  gp_Pnt ductStart(params.hoodRoomWidth / 2 - 2 * params.hoodWallThickness,
                   params.ductLeftDistance - params.hoodRoomLength / 2,
                   params.ductCenterHeight);
  gp_Pnt ductEnd(params.hoodRoomWidth / 2 + params.ductLength + 2 +
                     2 * params.baseRoomWallThickness,
                 params.ductLeftDistance - params.hoodRoomLength / 2,
                 params.ductCenterHeight + params.ductHeightDifference +
                     params.baseHeight);

  // 创建风通道外壁
  gp_Vec ductDir(ductEnd.X() - ductStart.X(), 0, ductEnd.Z() - ductStart.Z());
  TopoDS_Shape duct = BRepPrimAPI_MakeCylinder(gp_Ax2(ductStart, ductDir),
                                               params.ductDiameter / 2 +
                                                   params.ductWallThickness,
                                               ductDir.Magnitude())
                          .Shape();

  hoodRoom = BRepAlgoAPI_Cut(hoodRoom, duct).Shape();
  baseRoom = BRepAlgoAPI_Cut(baseRoom, duct).Shape();

  // 创建风通道内腔（如果壁厚大于0）
  if (params.ductWallThickness > 0) {
    TopoDS_Shape innerDuct =
        BRepPrimAPI_MakeCylinder(
            gp_Ax2(ductStart, ductDir), params.ductDiameter / 2,
            ductDir.Magnitude() + 2 * params.ductWallThickness)
            .Shape();
    duct = BRepAlgoAPI_Cut(duct, innerDuct).Shape();
  }

  // 合并所有部件
  TopoDS_Shape ventilationDuct = BRepAlgoAPI_Fuse(hoodRoom, duct).Shape();
  ventilationDuct = BRepAlgoAPI_Fuse(ventilationDuct, base).Shape();
  ventilationDuct = BRepAlgoAPI_Fuse(ventilationDuct, baseRoom).Shape();

  return ventilationDuct;
}


TopoDS_Shape
create_oblique_ventilation_duct(const oblique_ventilation_duct_params &params,
                                const gp_Pnt &position, const gp_Dir &direction,
                                const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(direction.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Direction and xDir must be perpendicular");
  }

  // 创建标准方向的斜通风道
  TopoDS_Shape duct = create_oblique_ventilation_duct(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, direction, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(duct, transformation);
  return transform.Shape();
}


TopoDS_Shape create_pipe_support(const pipe_support_params &params) {
  // 参数验证
  if (params.length <= 0 || params.height <= 0) {
    throw Standard_ConstructionError("Length and height must be positive");
  }
  if (params.style != pipe_support_style::SINGLE_SIDED &&
      params.style != pipe_support_style::DOUBLE_SIDED) {
    throw Standard_ConstructionError("Style must be 1 or 2");
  }
  if (params.count != params.positions.size() ||
      params.count != params.radii.size()) {
    throw Standard_ConstructionError("Position and radius count mismatch");
  }

  TopoDS_Shape support;
  if (params.style == pipe_support_style::SINGLE_SIDED) {
    gp_Pnt baseOrigin(-params.width / 2, -params.length / 2, 0);
    support = BRepPrimAPI_MakeBox(baseOrigin, params.width, params.length,
                                  params.height)
                  .Shape();
  } else {
    gp_Pnt baseOrigin(-params.width / 2, -params.length / 2,
                      -params.height / 2);
    support = BRepPrimAPI_MakeBox(baseOrigin, params.width, params.length,
                                  params.height)
                  .Shape();
  }

  // 创建管枕孔
  for (int i = 0; i < params.count; ++i) {
    if (params.radii[i] <= 0)
      continue;

    // 创建圆柱形孔
    gp_Pnt center(-params.width, params.positions[i].X(),
                  params.positions[i].Y());
    TopoDS_Shape hole =
        BRepPrimAPI_MakeCylinder(gp_Ax2(center, gp::DX()), params.radii[i],
                                 params.width * 2)
            .Shape();

    // 从基础中减去孔
    support = BRepAlgoAPI_Cut(support, hole).Shape();
  }

  return support;
}


TopoDS_Shape create_pipe_support(const pipe_support_params &params,
                                 const gp_Pnt &position,
                                 const gp_Dir &direction, const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(direction.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Direction and xDir must be perpendicular");
  }

  // 创建标准方向的管枕
  TopoDS_Shape support = create_pipe_support(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, direction, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(support, transformation);
  return transform.Shape();
}


TopoDS_Shape create_cover_plate(const cover_plate_params &params) {
  // 参数验证
  if (params.thickness <= 0) {
    throw Standard_ConstructionError("Thickness must be positive");
  }

  TopoDS_Shape cover;

  if (params.style == cover_plate_style::RECTANGULAR) { // 长方形盖板
    if (params.length <= 0 || params.width <= 0) {
      throw Standard_ConstructionError(
          "Length and width must be positive for rectangular cover");
    }

    // 创建长方体盖板
    gp_Pnt origin(-params.length / 2, -params.width / 2, 0);
    cover = BRepPrimAPI_MakeBox(origin, params.length, params.width,
                                params.thickness)
                .Shape();

  } else if (params.style == cover_plate_style::SECTOR) { // 扇形盖板
    // 参数验证
    if (params.length <= 0 || params.largeRadius <= 0 ||
        params.smallRadius <= 0) {
      throw Standard_ConstructionError(
          "参数必须满足：length > 0, largeRadius > 0, smallRadius > 0");
    }
    // 参数验证
    if (params.largeRadius <= params.smallRadius) {
      throw Standard_ConstructionError(
          "参数必须满足：largeRadius > smallRadius");
    }

    // 计算连接边长度
    double L3 = params.length;
    double L1 = params.smallRadius; // 小圆弧弧长
    double L2 = params.largeRadius; // 大圆弧弧长

    // 计算半径和角度
    double r1 = (L1 * L3) / (L2 - L1); // 小圆半径
    double theta = (L2 - L1) / L3;     // 扇形角度(弧度)
    double r2 = r1 + L3;               // 大圆半径

    // 创建内圆弧 - 修改坐标系使弧线对齐X轴
    gp_Pnt O(0, 0, 0);

    // 定义点
    gp_Pnt A(r1 * cos(-theta / 2), r1 * sin(-theta / 2), 0);
    gp_Pnt B(r1 * cos(theta / 2), r1 * sin(theta / 2), 0);
    gp_Pnt C(r2 * cos(-theta / 2), r2 * sin(-theta / 2), 0);
    gp_Pnt D(r2 * cos(theta / 2), r2 * sin(theta / 2), 0);

    // 使用 gp_Circ 创建圆，对称于 X 轴构造圆弧
    gp_Circ innerCircle(gp_Ax2(O, gp::DZ()), r1);
    gp_Circ outerCircle(gp_Ax2(O, gp::DZ()), r2);

    // 构造内圆弧
    Handle(Geom_TrimmedCurve) innerArc =
        GC_MakeArcOfCircle(innerCircle, -theta / 2, theta / 2, Standard_True)
            .Value();

    // 构造外圆弧
    Handle(Geom_TrimmedCurve) outerArc =
        GC_MakeArcOfCircle(outerCircle, -theta / 2, theta / 2, Standard_True)
            .Value();

    // 构造边
    TopoDS_Edge edgeInner = BRepBuilderAPI_MakeEdge(innerArc).Edge();
    TopoDS_Edge edgeOuter = BRepBuilderAPI_MakeEdge(outerArc).Edge();
    edgeOuter.Reverse();
    TopoDS_Edge edgeBD = BRepBuilderAPI_MakeEdge(B, D).Edge();
    TopoDS_Edge edgeAC = BRepBuilderAPI_MakeEdge(C, A).Edge();

    // 构建闭合Wire
    BRepBuilderAPI_MakeWire wireBuilder;
    wireBuilder.Add(edgeInner);
    wireBuilder.Add(edgeBD);
    wireBuilder.Add(edgeOuter);
    wireBuilder.Add(edgeAC);
    TopoDS_Wire wire = wireBuilder.Wire();

    // 创建面并拉伸
    TopoDS_Face face = BRepBuilderAPI_MakeFace(wire).Face();
    cover = BRepPrimAPI_MakePrism(face, gp_Vec(0, 0, params.thickness)).Shape();

  } else {
    throw Standard_ConstructionError("Invalid cover plate style");
  }

  return cover;
}


TopoDS_Shape create_cover_plate(const cover_plate_params &params,
                                const gp_Pnt &position, const gp_Dir &normal,
                                const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(normal.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Normal and direction must be perpendicular");
  }

  // 创建标准方向的盖板
  TopoDS_Shape cover = create_cover_plate(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, normal, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(cover, transformation);
  return transform.Shape();
}


TopoDS_Shape create_cable_ray(const cable_ray_params &params) {
  // 参数验证
  if (params.outerLength <= 0 || params.outerHeight <= 0 ||
      params.innerLength <= 0 || params.innerHeight <= 0 ||
      params.coverThickness <= 0) {
    throw Standard_ConstructionError("All dimensions must be positive");
  }
  if (params.innerLength >= params.outerLength ||
      params.innerHeight >= params.outerHeight) {
    throw Standard_ConstructionError(
        "Inner dimensions must be smaller than outer dimensions");
  }

  // 创建槽盒主体外轮廓
  gp_Pnt outerOrigin(-params.outerLength / 2, -params.outerLength / 2, 0);
  TopoDS_Shape outerBox =
      BRepPrimAPI_MakeBox(outerOrigin, params.outerLength, params.outerLength,
                          params.outerLength)
          .Shape();

  // 创建槽盒主体内轮廓
  gp_Pnt innerOrigin(-params.innerLength / 2, -params.innerLength / 2,
                     params.outerHeight - params.innerHeight);
  TopoDS_Shape innerBox =
      BRepPrimAPI_MakeBox(innerOrigin, params.innerLength, params.innerLength,
                          params.outerLength + 2)
          .Shape();

  // 从外轮廓中减去内轮廓形成槽盒主体
  TopoDS_Shape troughBody = BRepAlgoAPI_Cut(outerBox, innerBox).Shape();

  // 创建盖板
  gp_Pnt coverOrigin(-params.outerLength / 2, -params.outerLength / 2,
                     params.outerLength + params.coverThickness);
  TopoDS_Shape cover =
      BRepPrimAPI_MakeBox(coverOrigin, params.outerLength, params.outerLength,
                          params.coverThickness)
          .Shape();

  // 合并槽盒主体和盖板
  return BRepAlgoAPI_Fuse(troughBody, cover).Shape();
}


TopoDS_Shape create_cable_ray(const cable_ray_params &params,
                              const gp_Pnt &position, const gp_Dir &direction,
                              const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(direction.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Direction and xDir must be perpendicular");
  }

  // 创建标准方向的槽盒
  TopoDS_Shape trough = create_cable_ray(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, direction, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(trough, transformation);
  return transform.Shape();
}

} // namespace topo
} // namespace flywave
