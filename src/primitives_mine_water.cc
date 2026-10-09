// 矿山专业参数化图元 — D 防治水与地质 (minebim P 线)
// 陷落柱 (361,362) / 断层透镜体 (345-355) / 水闸墙 (281) / 水闸门 (280) /
// 钻孔 (300-305, 367-383)。
#include "primitives_mine.hh"

#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_Transform.hxx>
#include <BRepOffsetAPI_ThruSections.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepPrimAPI_MakePrism.hxx>
#include <GC_MakeArcOfCircle.hxx>
#include <gp_Ax1.hxx>
#include <gp_Ax2.hxx>
#include <gp_Elips.hxx>
#include <gp_Pln.hxx>
#include <gp_Trsf.hxx>
#include <cmath>
#include <Precision.hxx>
#include <TopoDS.hxx>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace flywave {
namespace topo {

// 陷落柱: 底/顶双椭圆 ThruSections 平滑锥台放样 (长轴为局部 X)。
TopoDS_Shape create_mine_collapse_pillar(
    const mine_collapse_pillar_params &params) {
  if (params.height <= 0)
    throw Standard_ConstructionError("pillar height positive");
  if (params.bottomLong <= 0 || params.bottomShort <= 0 ||
      params.topLong <= 0 || params.topShort <= 0)
    throw Standard_ConstructionError("pillar axes positive");
  if (params.bottomShort > params.bottomLong || params.topShort > params.topLong)
    throw Standard_ConstructionError("long axis must >= short axis");

  auto ellipseWire = [](const gp_Pnt &center, double longR, double shortR) {
    gp_Ax2 ax(center, gp_Dir(0, 0, 1), gp_Dir(1, 0, 0)); // X = 长轴
    gp_Elips el(ax, longR, shortR);
    TopoDS_Edge e = BRepBuilderAPI_MakeEdge(el).Edge();
    TopoDS_Wire w = BRepBuilderAPI_MakeWire(e).Wire();
    return w;
  };

  gp_Pnt bottom(params.bottomCenter.X(), params.bottomCenter.Y(),
                params.bottomCenter.Z());
  gp_Pnt top(bottom.X(), bottom.Y(), bottom.Z() + params.height);

  BRepOffsetAPI_ThruSections gen(Standard_True);
  gen.AddWire(ellipseWire(bottom, params.bottomLong / 2, params.bottomShort / 2));
  gen.AddWire(ellipseWire(top, params.topLong / 2, params.topShort / 2));
  gen.Build();
  if (!gen.IsDone())
    throw Standard_ConstructionError("pillar loft failed");
  return gen.Shape();
}

// 断层破碎带透镜体 (凸透镜状: 中间厚边缘尖灭), 沿走向居中棱柱。
TopoDS_Shape create_mine_fault_lens(const mine_fault_lens_params &params) {
  if (params.dipAngle <= 0.0 || params.dipAngle >= 90.0)
    throw Standard_ConstructionError("Dip angle must be in (0, 90) degrees");
  if (params.zoneWidth <= 0.0)
    throw Standard_ConstructionError("Zone width must be positive");
  if (params.zoneLength <= 0.0)
    throw Standard_ConstructionError("Zone length must be positive");
  if (params.topElev <= params.bottomElev)
    throw Standard_ConstructionError("Top elevation must exceed bottom");

  gp_Dir strike = params.strike;
  gp_Dir dipAz = params.dipAzimuth;
  if (strike.IsParallel(dipAz, Precision::Angular()))
    throw Standard_ConstructionError("Strike and dip azimuth must differ");

  double dipRad = params.dipAngle * M_PI / 180.0;
  gp_Vec vDown =
      gp_Vec(dipAz) * std::cos(dipRad) - gp_Vec(0, 0, 1) * std::sin(dipRad);
  if (vDown.Magnitude() < Precision::Confusion())
    throw Standard_ConstructionError("Degenerate dip direction");
  gp_Dir v(vDown);
  double dipExtent = (params.topElev - params.bottomElev) / std::sin(dipRad);

  double hw = params.zoneWidth / 2.0;
  gp_Pnt T = params.center;
  gp_Pnt B = params.center.Translated(gp_Vec(v) * (-dipExtent));
  gp_Pnt midR = params.center.Translated(gp_Vec(strike) * hw)
                    .Translated(gp_Vec(v) * (-dipExtent / 2.0));
  gp_Pnt midL = params.center.Translated(gp_Vec(strike) * (-hw))
                    .Translated(gp_Vec(v) * (-dipExtent / 2.0));

  Handle(Geom_TrimmedCurve) arcR = GC_MakeArcOfCircle(T, midR, B).Value();
  Handle(Geom_TrimmedCurve) arcL = GC_MakeArcOfCircle(B, midL, T).Value();
  if (arcR.IsNull() || arcL.IsNull())
    throw Standard_ConstructionError("Failed to create lens arcs");
  BRepBuilderAPI_MakeWire mkWire(BRepBuilderAPI_MakeEdge(arcR).Edge());
  mkWire.Add(BRepBuilderAPI_MakeEdge(arcL).Edge());
  if (!mkWire.IsDone())
    throw Standard_ConstructionError("Failed to build lens wire");

  gp_Dir normal = strike.Crossed(v);
  gp_Pln pln(params.center, normal);
  BRepBuilderAPI_MakeFace mkFace(pln, mkWire.Wire());
  if (!mkFace.IsDone())
    throw Standard_ConstructionError("Failed to create lens face");

  gp_Vec prismVec(strike);
  prismVec.Scale(params.zoneLength);
  BRepPrimAPI_MakePrism prismMaker(mkFace.Face(), prismVec);
  if (!prismMaker.IsDone())
    throw Standard_ConstructionError("Failed to extrude lens");
  gp_Vec back = gp_Vec(strike) * (-params.zoneLength / 2.0);
  BRepBuilderAPI_Transform transform(prismMaker.Shape(),
                                     mine_translation_trsf(back));
  return transform.Shape();
}

// 水闸墙: 带行人门洞的宿主断面封堵体 (门洞三块式 compound; doorWidth≤0 实心)。
TopoDS_Shape create_mine_water_gate_wall(
    const mine_water_gate_wall_params &params) {
  if (params.width <= 0 || params.height <= 0 || params.thickness <= 0)
    throw Standard_ConstructionError("water gate wall dims positive");
  if (params.doorWidth < 0 || params.doorHeight < 0)
    throw Standard_ConstructionError("door dims non-negative");
  if (params.doorWidth > 0 &&
      (params.doorWidth >= params.width || params.doorHeight >= params.height))
    throw Standard_ConstructionError("door opening must fit inside section");
  gp_Vec ax(params.axis);
  if (ax.Magnitude() < Precision::Confusion())
    throw Standard_ConstructionError("water gate wall axis degenerate");
  gp_Dir axis(ax);

  auto rect = [](double x0, double y0, double x1, double y1) {
    return std::vector<std::pair<double, double>>{
        {x0, y0}, {x1, y0}, {x1, y1}, {x0, y1}};
  };
  if (params.doorWidth <= 0) {
    double hw = params.width / 2;
    return mine_extrude_profile(params.center, mine_left_perp(axis), axis,
                                rect(-hw, 0, hw, params.height),
                                params.thickness);
  }
  double hw = params.width / 2, dw2 = params.doorWidth / 2;
  double dh = params.doorHeight;
  std::vector<TopoDS_Shape> parts;
  const double segs[3][4] = {{-hw, 0, -dw2, params.height},
                             {dw2, 0, hw, params.height},
                             {-dw2, dh, dw2, params.height}};
  for (auto &sg : segs) {
    parts.push_back(mine_extrude_profile(params.center, mine_left_perp(axis),
                                         axis, rect(sg[0], sg[1], sg[2], sg[3]),
                                         params.thickness));
  }
  return mine_compound_all(parts);
}

// 水闸门: 门框三块 + 承压门扇 + 3 道横肋。compound。
TopoDS_Shape create_mine_water_gate(const mine_water_gate_params &params) {
  if (params.width <= 0 || params.height <= 0 || params.doorWidth <= 0 ||
      params.doorHeight <= 0)
    throw Standard_ConstructionError("water gate dims positive");
  if (params.doorWidth >= params.width || params.doorHeight >= params.height)
    throw Standard_ConstructionError("gate must fit inside section");
  if (params.doorThick <= 0 || params.frameWidth <= 0)
    throw Standard_ConstructionError("water gate thickness positive");
  gp_Vec ax(params.axis);
  if (ax.Magnitude() < Precision::Confusion())
    throw Standard_ConstructionError("water gate axis degenerate");
  gp_Dir axis(ax);

  double hw = params.width / 2, dw2 = params.doorWidth / 2;
  double dh = params.doorHeight, fw = params.frameWidth;
  auto rect = [](double x0, double y0, double x1, double y1) {
    return std::vector<std::pair<double, double>>{
        {x0, y0}, {x1, y0}, {x1, y1}, {x0, y1}};
  };
  gp_Dir xdir = mine_left_perp(axis);
  std::vector<TopoDS_Shape> parts;
  const double frame[3][4] = {{-hw, 0, -dw2, params.height},
                              {dw2, 0, hw, params.height},
                              {-dw2 - fw, dh, dw2 + fw, params.height}};
  for (auto &sg : frame) {
    parts.push_back(mine_extrude_profile(params.center, xdir, axis,
                                         rect(sg[0], sg[1], sg[2], sg[3]),
                                         params.doorThick));
  }
  // 承压门扇 (双倍厚) + 3 道横肋
  parts.push_back(mine_extrude_profile(params.center, xdir, axis,
                                       rect(-dw2, 0, dw2, dh),
                                       params.doorThick * 2));
  for (int i = 1; i <= 3; ++i) {
    double y = dh * i / 4;
    parts.push_back(mine_extrude_profile(
        params.center, xdir, axis, rect(-dw2, y - 0.05, dw2, y + 0.05),
        params.doorThick * 3));
  }
  return mine_compound_all(parts);
}

// 钻孔: 定向分层圆柱段 (layers 空 = 整孔单段)。compound。
TopoDS_Shape create_mine_borehole(const mine_borehole_params &params) {
  if (params.diameter <= 0)
    throw Standard_ConstructionError("borehole diameter positive");
  gp_Vec axv(params.axis);
  if (axv.Magnitude() < Precision::Confusion())
    throw Standard_ConstructionError("borehole axis degenerate");
  gp_Dir axis(axv);
  double r = params.diameter / 2;

  std::vector<TopoDS_Shape> parts;
  if (params.layers.empty()) {
    // 整孔: 由台账 depth 单段 (from=0, to=depth 由调用方给)
    parts.push_back(mine_cylinder_from(params.collar, axis, r, 1.0));
    return mine_compound_all(parts);
  }
  double last = 0;
  for (const auto &ly : params.layers) {
    if (ly.to <= ly.from || ly.from < last - 1e-9)
      throw Standard_ConstructionError("borehole layers must ascend");
    gp_Pnt start = params.collar.Translated(gp_Vec(axis) * ly.from);
    parts.push_back(
        mine_cylinder_from(start, axis, r, ly.to - ly.from));
    last = ly.to;
  }
  return mine_compound_all(parts);
}

} // namespace topo
} // namespace flywave
