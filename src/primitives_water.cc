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
// 水利工程 (water) — 输水隧道 / 排水井 / 集水坑 / 钻孔

namespace flywave {
namespace topo {


TopoDS_Shape create_sump(const sump_params &params) {
  // 参数验证
  if (params.length <= 0 || params.width <= 0 || params.depth <= 0) {
    throw Standard_ConstructionError(
        "Length, width and depth must be positive");
  }
  if (params.bottomThickness < 0) {
    throw Standard_ConstructionError("Floor thickness must be non-negative");
  }

  // 创建集水坑主体（长方体）
  gp_Pnt origin(-params.length / 2 - params.bottomThickness,
                -params.width / 2 - params.bottomThickness,
                -params.depth - params.bottomThickness);
  BRepPrimAPI_MakeBox pitMaker(origin,
                               params.length + 2 * params.bottomThickness,
                               params.width + 2 * params.bottomThickness,
                               params.depth + params.bottomThickness);
  TopoDS_Shape pit = pitMaker.Shape();

  // 创建内部空腔（如果底板厚度大于0）
  if (params.bottomThickness > 0) {
    gp_Pnt innerOrigin(-params.length / 2, -params.width / 2, -params.depth);
    BRepPrimAPI_MakeBox cavityMaker(innerOrigin, params.length, params.width,
                                    params.depth * 2);
    pit = BRepAlgoAPI_Cut(pit, cavityMaker.Shape()).Shape();
  }

  return pit;
}


TopoDS_Shape create_sump(const sump_params &params, const gp_Pnt &position,
                         const gp_Dir &normal, const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(normal.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Normal and direction must be perpendicular");
  }

  // 创建标准方向的集水坑
  TopoDS_Shape pit = create_sump(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, normal, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(pit, transformation);
  return transform.Shape();
}


TopoDS_Shape create_drainage_well(const drainage_well_params &params) {
  // 参数验证
  if (params.length <= 0 || params.width <= 0 || params.height <= 0) {
    throw Standard_ConstructionError(
        "Length, width and height must be positive");
  }
  if (params.wallThickness < 0 || params.bottomThickness < 0) {
    throw Standard_ConstructionError("Thickness values must be non-negative");
  }

  // 创建井主体外壁
  double outerLength = params.length + 2 * params.wallThickness;
  double outerWidth = params.width + 2 * params.wallThickness;
  double outerHeight = params.height + params.bottomThickness;

  gp_Pnt baseOrigin(-outerLength / 2, 0, 0);
  TopoDS_Shape outerBox =
      BRepPrimAPI_MakeBox(baseOrigin, outerLength, outerWidth, outerHeight)
          .Shape();

  // 创建井主体内腔
  gp_Pnt innerOrigin(-params.length / 2, params.wallThickness, 0);
  TopoDS_Shape innerBox = BRepPrimAPI_MakeBox(innerOrigin, params.length,
                                              params.width, params.height)
                              .Shape();

  // 从外壁中减去内腔
  TopoDS_Shape wellBody = BRepAlgoAPI_Cut(outerBox, innerBox).Shape();

  // 创建井脖
  if (params.neckDiameter > 0 && params.neckHeight > 0) {
    double neckDiameter = params.neckDiameter + 2 * params.wallThickness;

    gp_Ax2 neckAxis(
        gp_Pnt(0, outerWidth - params.wallThickness - params.neckDiameter / 2,
               outerHeight - 3 * params.wallThickness),
        gp::DZ());
    TopoDS_Shape neck =
        BRepPrimAPI_MakeCylinder(neckAxis, neckDiameter / 2,
                                 params.neckHeight + 3 * params.wallThickness)
            .Shape();

    // 合并井脖和主体
    wellBody = BRepAlgoAPI_Cut(wellBody, neck).Shape();

    gp_Ax2 innerNeckAxis(
        gp_Pnt(0, outerWidth - params.wallThickness - params.neckDiameter / 2,
               outerHeight - 4 * params.wallThickness),
        gp::DZ());
    TopoDS_Shape innerNseck =
        BRepPrimAPI_MakeCylinder(innerNeckAxis, params.neckDiameter / 2,
                                 params.neckHeight + 5 * params.wallThickness)
            .Shape();

    neck = BRepAlgoAPI_Cut(neck, innerNseck).Shape();
    wellBody = BRepAlgoAPI_Fuse(wellBody, neck).Shape();
  }

  // 创建垫层
  if (params.cushionExtension > 0) {
    double cushionLength = outerLength + 2 * params.cushionExtension;
    double cushionWidth = outerWidth + 2 * params.cushionExtension;

    gp_Pnt cushionOrigin(-cushionLength / 2, -params.cushionExtension,
                         -params.bottomThickness);
    TopoDS_Shape cushion =
        BRepPrimAPI_MakeBox(cushionOrigin, cushionLength, cushionWidth,
                            params.bottomThickness)
            .Shape();

    wellBody = BRepAlgoAPI_Fuse(wellBody, cushion).Shape();
  }

  return wellBody;
}


TopoDS_Shape create_drainage_well(const drainage_well_params &params,
                                  const gp_Pnt &position,
                                  const gp_Dir &direction, const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(direction.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Direction and xDir must be perpendicular");
  }

  // 创建标准方向的排水井
  TopoDS_Shape well = create_drainage_well(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, direction, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(well, transformation);
  return transform.Shape();
}


TopoDS_Shape create_water_tunnel(const water_tunnel_params &params) {
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
      params.style == water_tunnel_section_style::RECTANGULAR) {
    double zoffset = -params.cushionThickness;

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
  case water_tunnel_section_style::RECTANGULAR: {
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
  case water_tunnel_section_style::CITYOPENING: {
    // 城门洞截面 - 外部轮廓
    double arcHeight = params.arcHeight;
    if (arcHeight == 0 && params.arcRadius == 0) {
      throw Standard_ConstructionError(
          "Either arcHeight or arcRadius must be non-zero");
    }

    double outerWidth = params.width + 2 * params.outerWallThickness +
                        2 * params.innerWallThickness;
    double outerRadius = outerWidth / 2;
    double outerHeight =
        params.height + params.outerWallThickness + params.innerWallThickness;
    double outerArchHeight;

    // 计算拱高或拱半径
    if (arcHeight == 0) {
      // 根据拱半径计算拱高
      double halfWidth = params.width / 2;
      if (params.arcRadius < halfWidth) {
        throw Standard_ConstructionError(
            "Arc radius must be greater than or equal to half width");
      }
      arcHeight = params.arcRadius - sqrt(params.arcRadius * params.arcRadius -
                                          halfWidth * halfWidth);
      outerArchHeight =
          arcHeight + params.outerWallThickness + params.innerWallThickness;
    } else {
      // 使用提供的拱高
      outerArchHeight =
          arcHeight + params.outerWallThickness + params.innerWallThickness;
    }

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
  case water_tunnel_section_style::CIRCULAR: {
    // 圆形截面 - 外部轮廓
    double outerRadius = params.width / 2 + params.outerWallThickness;
    gp_Pnt center(0, 0, 0);
    Handle(Geom_Circle) outerCircle =
        new Geom_Circle(gp_Ax2(center, gp::DX()), outerRadius);
    TopoDS_Edge outerEdge = BRepBuilderAPI_MakeEdge(outerCircle).Edge();
    outerWire = BRepBuilderAPI_MakeWire(outerEdge).Wire();
    break;
  }
  case water_tunnel_section_style::POLYGON: {
    if (params.polygon.size() < 3) {
      throw Standard_ConstructionError(
          "POLYGON style requires at least 3 polygon vertices");
    }
    double thickness = params.outerWallThickness;
    if (thickness < 0.01) thickness = 0.1;
    gp_XYZ centroid(0, 0, 0);
    for (const auto &pt : params.polygon) {
      centroid += pt.XYZ();
    }
    centroid /= params.polygon.size();
    BRepBuilderAPI_MakePolygon innerPoly;
    BRepBuilderAPI_MakePolygon outerPoly;
    for (const auto &pt : params.polygon) {
      gp_Pnt inner = sectionAxes.Location().Translated(
          gp_Vec(pt.Z(), pt.Y(), 0).Transformed(trsf));
      innerPoly.Add(inner);
      gp_Vec dir(pt.X() - centroid.X(), pt.Y() - centroid.Y(), pt.Z() - centroid.Z());
      double len = dir.Magnitude();
      if (len > 1e-12) {
        dir /= len;
      } else {
        dir = gp_Vec(0, 0, 1);
      }
      gp_Pnt outer = sectionAxes.Location().Translated(
          gp_Vec(pt.Z() + dir.Z() * thickness, pt.Y() + dir.Y() * thickness, 0).Transformed(trsf));
      outerPoly.Add(outer);
    }
    outerPoly.Close();
    outerWire = outerPoly.Wire();
    // innerWire will be set in the inner wire switch below
    break;
  }
  case water_tunnel_section_style::HORSESHOE: {
    // 马蹄形截面 - 外部轮廓
    double outerWidth = params.width + 2 * params.outerWallThickness +
                        2 * params.innerWallThickness;
    double outerRadius = outerWidth / 2;
    double outerHeight =
        params.height + params.outerWallThickness + params.innerWallThickness;

    // 计算圆心位置
    double arcRadius = params.arcRadius + params.outerWallThickness +
                       params.innerWallThickness;

    // 底部连接段点
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

    // 计算钝角情况下的圆弧起点和终点
    double angle =
        (360 - params.arcAngle) * M_PI / 180.0; // 正确转换补角为 360-θ

    // 圆弧起点和终点计算(使用360补角)
    gp_Pnt localArcEnd(
        0, -arcRadius * sin(angle), // 当 angle>180° 时 sin 值为负，负负得正
        params.height - arcRadius * (1 - cos(angle)));
    gp_Pnt arcEnd = sectionAxes.Location().Translated(
        gp_Vec(localArcEnd.Z(), localArcEnd.Y(), 0).Transformed(trsf));

    gp_Pnt localArcStart(0,
                         arcRadius * sin(angle), // 当 angle>180° 时 sin 值为负
                         params.height - arcRadius * (1 - cos(angle)));
    gp_Pnt arcStart = sectionAxes.Location().Translated(
        gp_Vec(localArcStart.Z(), localArcStart.Y(), 0).Transformed(trsf));

    // 创建左侧连接段(从底部到顶部)
    TopoDS_Edge leftSegment =
        BRepBuilderAPI_MakeEdge(bottomLeft, arcStart).Edge();

    // 创建右侧连接段(从顶部到底部)
    TopoDS_Edge rightSegment =
        BRepBuilderAPI_MakeEdge(arcEnd, bottomRight).Edge();

    // 创建顶部圆弧(从右到左)
    gp_Pnt localArcMid(0, 0, outerHeight);
    gp_Pnt arcMid = sectionAxes.Location().Translated(
        gp_Vec(localArcMid.Z(), localArcMid.Y(), 0).Transformed(trsf));

    Handle(Geom_TrimmedCurve) topArc =
        GC_MakeArcOfCircle(arcStart, arcMid, arcEnd).Value();

    TopoDS_Edge bootomEgde =
        BRepBuilderAPI_MakeEdge(bottomRight, bottomLeft).Edge();
    bootomEgde.Reversed();

    // 修正连接顺序和边方向
    BRepBuilderAPI_MakeWire wireMaker;
    wireMaker.Add(leftSegment);                            // 左侧连接段
    wireMaker.Add(BRepBuilderAPI_MakeEdge(topArc).Edge()); // 顶部圆弧
    wireMaker.Add(rightSegment);                           // 右侧连接段
    wireMaker.Add(bootomEgde);                             // 底部边

    // 添加完整性检查
    if (!wireMaker.IsDone() || !wireMaker.Wire().Closed()) {
      // 输出调试信息
      throw Standard_ConstructionError(
          "Failed to create closed wire for horseshoe section");
    }

    outerWire = wireMaker.Wire();

    break;
  }
  default:
    throw Standard_ConstructionError("Invalid tunnel section style");
  }
  TopoDS_Shape outer = create_channel_shape(outerWire, path);

  // 创建隧道截面轮廓
  TopoDS_Wire innerWire;
  switch (params.style) {
  case water_tunnel_section_style::RECTANGULAR: {
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
  case water_tunnel_section_style::CITYOPENING: {
    double arcHeight = params.arcHeight;
    if (arcHeight == 0 && params.arcRadius == 0) {
      throw Standard_ConstructionError(
          "Either arcHeight or arcRadius must be non-zero");
    }

    // 马蹄形截面 - 内部轮廓
    double innerRadius = params.width / 2;
    double innerHeight = params.height;
    double innerArchHeight = params.arcHeight;

    // 计算拱高或拱半径
    if (arcHeight == 0) {
      // 根据拱半径计算拱高
      double halfWidth = innerRadius;
      if (params.arcRadius < halfWidth) {
        throw Standard_ConstructionError(
            "Arc radius must be greater than or equal to half width");
      }
      innerArchHeight =
          params.arcRadius -
          sqrt(params.arcRadius * params.arcRadius - halfWidth * halfWidth);
    } else {
      // 使用提供的拱高
      innerArchHeight = arcHeight;
    }

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
  case water_tunnel_section_style::CIRCULAR: {
    // 圆形截面 - 内部轮廓
    double innerRadius = params.width / 2;
    gp_Pnt center(0, 0, 0);
    Handle(Geom_Circle) innerCircle =
        new Geom_Circle(gp_Ax2(center, gp::DX()), innerRadius);
    TopoDS_Edge innerEdge = BRepBuilderAPI_MakeEdge(innerCircle).Edge();
    innerWire = BRepBuilderAPI_MakeWire(innerEdge).Wire();
    break;
  }
  case water_tunnel_section_style::POLYGON: {
    if (params.polygon.size() < 3) {
      throw Standard_ConstructionError(
          "POLYGON style requires at least 3 polygon vertices");
    }
    BRepBuilderAPI_MakePolygon innerPoly;
    for (const auto &pt : params.polygon) {
      gp_Pnt inner = sectionAxes.Location().Translated(
          gp_Vec(pt.Z(), pt.Y(), 0).Transformed(trsf));
      innerPoly.Add(inner);
    }
    innerPoly.Close();
    innerWire = innerPoly.Wire();
    break;
  }
  case water_tunnel_section_style::HORSESHOE: {
    // 马蹄形截面 - 内部轮廓
    double innerWidth = params.width; // 内净宽
    double innerRadius = innerWidth / 2;
    double innerHeight = params.height; // 内净高

    // 计算内轮廓圆心位置
    double innerArcRadius = params.arcRadius;

    // 内轮廓底部点
    gp_Pnt localBottomLeft(0, -innerRadius, 0);
    gp_Pnt innerBottomLeft = sectionAxes.Location().Translated(
        gp_Vec(localBottomLeft.Z(), localBottomLeft.Y(), 0).Transformed(trsf));

    gp_Pnt localBottomRight(0, innerRadius, 0);
    gp_Pnt innerBottomRight = sectionAxes.Location().Translated(
        gp_Vec(localBottomRight.Z(), localBottomRight.Y(), 0)
            .Transformed(trsf));

    // 计算内轮廓圆弧起点和终点
    double innerAngle =
        (360 - params.arcAngle) * M_PI / 180.0; // 正确转换补角为 360-θ

    gp_Pnt localArcEnd(0, -innerArcRadius * sin(innerAngle),
                       params.height - innerArcRadius * (1 - cos(innerAngle)));
    gp_Pnt innerArcEnd = sectionAxes.Location().Translated(
        gp_Vec(localArcEnd.Z(), localArcEnd.Y(), 0).Transformed(trsf));

    gp_Pnt localArcStart(0, innerArcRadius * sin(innerAngle),
                         params.height -
                             innerArcRadius * (1 - cos(innerAngle)));
    gp_Pnt innerArcStart = sectionAxes.Location().Translated(
        gp_Vec(localArcStart.Z(), localArcStart.Y(), 0).Transformed(trsf));

    // 创建内轮廓左侧连接段
    TopoDS_Edge innerLeftSegment =
        BRepBuilderAPI_MakeEdge(innerBottomLeft, innerArcStart).Edge();

    // 创建内轮廓右侧连接段
    TopoDS_Edge innerRightSegment =
        BRepBuilderAPI_MakeEdge(innerArcEnd, innerBottomRight).Edge();

    // 创建顶部圆弧(从右到左)
    gp_Pnt localArcMid(0, 0, innerHeight);
    gp_Pnt innerArcMid = sectionAxes.Location().Translated(
        gp_Vec(localArcMid.Z(), localArcMid.Y(), 0).Transformed(trsf));

    Handle(Geom_TrimmedCurve) innerTopArc =
        GC_MakeArcOfCircle(innerArcStart, innerArcMid, innerArcEnd).Value();

    TopoDS_Edge innerTopEdge = BRepBuilderAPI_MakeEdge(innerTopArc).Edge();

    // 创建内轮廓底部边
    TopoDS_Edge innerBottomEdge =
        BRepBuilderAPI_MakeEdge(innerBottomRight, innerBottomLeft).Edge();
    innerBottomEdge.Reversed();

    // 组合内轮廓线框
    BRepBuilderAPI_MakeWire innerWireMaker;
    innerWireMaker.Add(innerLeftSegment);
    innerWireMaker.Add(innerTopEdge);
    innerWireMaker.Add(innerRightSegment);
    innerWireMaker.Add(innerBottomEdge);

    if (!innerWireMaker.IsDone() || !innerWireMaker.Wire().Closed()) {
      throw Standard_ConstructionError(
          "Failed to create closed wire for inner horseshoe section");
    }

    innerWire = innerWireMaker.Wire();
    break;
  }
  default:
    throw Standard_ConstructionError("Invalid tunnel section style");
  }

  TopoDS_Shape inner = create_channel_shape(innerWire, path);

  // 处理底部平台
  if (params.style == water_tunnel_section_style::CIRCULAR &&
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


TopoDS_Shape create_water_tunnel(const water_tunnel_params &params,
                                 const gp_Pnt &position,
                                 const gp_Dir &direction, const gp_Dir &xDir) {
  // 正交性校验
  if (Abs(direction.Dot(xDir)) > Precision::Angular()) {
    throw Standard_ConstructionError(
        "Direction and xDir must be perpendicular");
  }

  // 创建标准方向的输水隧洞
  TopoDS_Shape tunnel = create_water_tunnel(params);

  // 创建坐标系变换
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, direction, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  BRepBuilderAPI_Transform transform(tunnel, transformation);
  return transform.Shape();
}


TopoDS_Wire create_water_tunnel_centerline(const water_tunnel_params &params) {
  if (params.points.size() < 2) {
    throw Standard_ConstructionError("At least 2 points are required");
  }

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


std::map<std::string, TopoDS_Shape>
create_borehole(const borehole_params &params) {
  std::map<std::string, TopoDS_Shape> result;

  if (params.samples.empty()) {
    return result;
  }

  // 复制并排序samples
  auto sorted_samples = params.samples;
  std::sort(sorted_samples.begin(), sorted_samples.end(),
            [](const borehole_sample &a, const borehole_sample &b) {
              return a.depth_from < b.depth_from;
            });

  // 创建圆柱体
  for (const auto &sample : sorted_samples) {
    if (sample.depth_to == 0.0) {
      result[sample.name] = TopoDS_Shape(); // 空shape
      continue;
    }

    double height = sample.depth_to - sample.depth_from;
    if (height <= 0.0) {
      result[sample.name] = TopoDS_Shape(); // 空shape
      continue;
    }

    gp_Dir upDir = params.upDir ? *params.upDir : gp::DZ();

    // 创建圆柱体
    gp_Ax2 axis(gp_Pnt(0, 0, -sample.depth_to), upDir);
    BRepPrimAPI_MakeCylinder maker(axis, params.diameter / 2.0, height);
    result[sample.name] = maker.Shape();
  }

  return result;
}

} // namespace topo
} // namespace flywave
