// 矿山专业参数化图元 — C 通风设施 (minebim P 线)
// 风墙/密闭 (189,190) / 防爆·防火·防水墙 (191,212,213) / 风门 (177-186) /
// 调节风窗 (185,186) / 风桥 (197) / 风筒 (198)。
#include "primitives_mine.hh"

#include <BRepAlgoAPI_Cut.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_Transform.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepPrimAPI_MakePrism.hxx>
#include <GC_MakeArcOfCircle.hxx>
#include <gp_Ax1.hxx>
#include <gp_Circ.hxx>
#include <gp_Pln.hxx>
#include <cmath>
#include <Precision.hxx>
#include <TopoDS.hxx>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace flywave {
namespace topo {

// 风墙/密闭: 宿主断面 loop 沿轴向挤 thickness。
TopoDS_Shape create_mine_vent_wall(const mine_vent_wall_params &params) {
  if (params.width <= 0 || params.height <= 0 || params.thickness <= 0)
    throw Standard_ConstructionError("vent wall dims positive");
  gp_Vec ax(params.axis);
  if (ax.Magnitude() < Precision::Confusion())
    throw Standard_ConstructionError("vent wall axis degenerate");
  gp_Dir axis(ax);
  auto loop = mine_section_loop(params.section, params.width, params.height);
  return mine_extrude_profile(params.center, mine_left_perp(axis), axis, loop,
                              params.thickness);
}

// 矩形墙体 (防爆墙/防火墙/防水墙共用)。
TopoDS_Shape create_mine_box_wall(const mine_box_wall_params &params) {
  if (params.width <= 0 || params.height <= 0 || params.thickness <= 0)
    throw Standard_ConstructionError("box wall dims positive");
  gp_Vec ax(params.axis);
  if (ax.Magnitude() < Precision::Confusion())
    throw Standard_ConstructionError("box wall axis degenerate");
  gp_Dir axis(ax);
  double hw = params.width / 2;
  std::vector<std::pair<double, double>> loop = {
      {-hw, 0}, {hw, 0}, {hw, params.height}, {-hw, params.height}};
  return mine_extrude_profile(params.center, mine_left_perp(axis), axis, loop,
                              params.thickness);
}

// 风门: 双立柱 + 门楣门框 + 门板 (openAngleDeg 绕门洞右边缘竖轴外摆)。compound。
TopoDS_Shape create_mine_vent_door(const mine_vent_door_params &params) {
  if (params.width <= 0 || params.height <= 0 || params.doorWidth <= 0 ||
      params.doorHeight <= 0)
    throw Standard_ConstructionError("vent door dims positive");
  if (params.doorWidth >= params.width || params.doorHeight >= params.height)
    throw Standard_ConstructionError("door opening must fit inside section");
  if (params.doorThick <= 0 || params.frameWidth <= 0)
    throw Standard_ConstructionError("vent door thickness positive");
  gp_Vec ax(params.axis);
  if (ax.Magnitude() < Precision::Confusion())
    throw Standard_ConstructionError("vent door axis degenerate");
  gp_Dir axis(ax);

  double hw = params.width / 2, dw2 = params.doorWidth / 2;
  double dh = params.doorHeight, fw = params.frameWidth;
  auto rect = [](double x0, double y0, double x1, double y1) {
    return std::vector<std::pair<double, double>>{
        {x0, y0}, {x1, y0}, {x1, y1}, {x0, y1}};
  };
  std::vector<std::pair<double, double>> left = rect(-hw, 0, -dw2, dh);
  std::vector<std::pair<double, double>> right = rect(dw2, 0, hw, dh);
  std::vector<std::pair<double, double>> lintel =
      rect(-dw2 - fw, dh, dw2 + fw, params.height);
  std::vector<std::pair<double, double>> leaf = rect(-dw2, 0, dw2, dh);

  // 门板开启: 绕门洞右边缘竖轴 (局部 x=+dw2) 旋转 openAngleDeg
  gp_Pnt hinge = params.center.Translated(gp_Vec(mine_left_perp(axis)) * dw2);
  gp_Trsf rot;
  if (params.openAngleDeg > 0) {
    rot.SetRotation(gp_Ax1(hinge, gp_Dir(0, 0, 1)),
                    params.openAngleDeg * M_PI / 180.0);
  }

  std::vector<TopoDS_Shape> parts;
  parts.push_back(mine_extrude_profile(params.center, mine_left_perp(axis),
                                       axis, left, params.doorThick));
  parts.push_back(mine_extrude_profile(params.center, mine_left_perp(axis),
                                       axis, right, params.doorThick));
  parts.push_back(mine_extrude_profile(params.center, mine_left_perp(axis),
                                       axis, lintel, params.doorThick));
  TopoDS_Shape leafShape = mine_extrude_profile(
      params.center, mine_left_perp(axis), axis, leaf, params.doorThick);
  if (params.openAngleDeg > 0) {
    BRepBuilderAPI_Transform tr(leafShape, rot);
    leafShape = tr.Shape();
  }
  parts.push_back(leafShape);
  return mine_compound_all(parts);
}

// 调节风窗: 带窗孔墙体 (外框面挖孔后棱柱) + 竖向格栅。compound。
TopoDS_Shape create_mine_vent_window(const mine_vent_window_params &params) {
  if (params.width <= 0 || params.height <= 0 || params.thickness <= 0)
    throw Standard_ConstructionError("vent window wall dims positive");
  if (params.winWidth <= 0 || params.winHeight <= 0 ||
      params.winWidth >= params.width ||
      params.winSill + params.winHeight >= params.height)
    throw Standard_ConstructionError("window opening must fit inside wall");
  if (params.bars < 0)
    throw Standard_ConstructionError("bars non-negative");
  gp_Vec ax(params.axis);
  if (ax.Magnitude() < Precision::Confusion())
    throw Standard_ConstructionError("vent window axis degenerate");
  gp_Dir axis(ax);

  double hw = params.width / 2, ww2 = params.winWidth / 2;
  double sill = params.winSill, sillTop = params.winSill + params.winHeight;
  auto rect = [](double x0, double y0, double x1, double y1) {
    return std::vector<std::pair<double, double>>{
        {x0, y0}, {x1, y0}, {x1, y1}, {x0, y1}};
  };
  gp_Dir xdir = mine_left_perp(axis);

  // 墙体四块 (左/右/上/下窗)
  std::vector<TopoDS_Shape> parts;
  const double segs[4][4] = {{-hw, 0, -ww2, params.height},
                             {ww2, 0, hw, params.height},
                             {-ww2, sillTop, ww2, params.height},
                             {-ww2, 0, ww2, sill}};
  for (auto &sg : segs) {
    parts.push_back(mine_extrude_profile(
        params.center, xdir, axis,
        rect(sg[0], sg[1], sg[2], sg[3]), params.thickness));
  }
  // 竖向格栅 (推拉调节板)
  if (params.bars > 0) {
    double step = params.winWidth / params.bars;
    double bw = step * 0.4;
    for (int i = 0; i < params.bars; ++i) {
      double cx = -ww2 + step * (i + 0.5);
      parts.push_back(mine_extrude_profile(
          params.center, xdir, axis, rect(cx - bw / 2, sill, cx + bw / 2, sillTop),
          params.thickness * 0.5));
    }
  }
  return mine_compound_all(parts);
}

// 栅栏/栅栏门: 立柱 + 上下横档 + 竖栅条。compound (免布尔)。
TopoDS_Shape create_mine_fence(const mine_fence_params &params) {
  if (params.width <= 0 || params.height <= 0 || params.postWidth <= 0 ||
      params.barWidth <= 0 || params.thickness <= 0)
    throw Standard_ConstructionError("fence dims positive");
  if (params.bars < 1 || params.bars > 64)
    throw Standard_ConstructionError("fence bars out of [1,64]");
  if (params.postWidth * 2 >= params.width)
    throw Standard_ConstructionError("posts must be narrower than span");
  gp_Vec axv(params.axis);
  if (axv.Magnitude() < Precision::Confusion())
    throw Standard_ConstructionError("fence axis degenerate");
  gp_Dir axis(axv);
  double hw = params.width / 2, pw = params.postWidth;
  double railH = std::min(params.height * 0.08, pw);
  auto rect = [](double x0, double y0, double x1, double y1) {
    return std::vector<std::pair<double, double>>{
        {x0, y0}, {x1, y0}, {x1, y1}, {x0, y1}};
  };
  gp_Dir xdir = mine_left_perp(axis);
  std::vector<TopoDS_Shape> parts;
  // 双立柱
  parts.push_back(mine_extrude_profile(params.center, xdir, axis,
                                       rect(-hw, 0, -hw + pw, params.height),
                                       params.thickness));
  parts.push_back(mine_extrude_profile(params.center, xdir, axis,
                                       rect(hw - pw, 0, hw, params.height),
                                       params.thickness));
  // 上下横档
  parts.push_back(mine_extrude_profile(params.center, xdir, axis,
                                       rect(-hw, params.height - railH, hw, params.height),
                                       params.thickness));
  parts.push_back(mine_extrude_profile(params.center, xdir, axis,
                                       rect(-hw, 0, hw, railH), params.thickness));
  // 竖栅条 (半厚)
  double inner = params.width - 2 * pw;
  double step = inner / params.bars;
  double bw = std::min(params.barWidth, step * 0.8);
  for (int i = 0; i < params.bars; ++i) {
    double cx = -hw + pw + step * (i + 0.5);
    parts.push_back(mine_extrude_profile(params.center, xdir, axis,
                                         rect(cx - bw / 2, railH, cx + bw / 2, params.height - railH),
                                         params.thickness * 0.5));
  }
  return mine_compound_all(parts);
}

// 风桥: 拱环带 (外拱去+内拱回闭环), 环面含 axis, 沿其垂直向挤 width。
TopoDS_Shape create_mine_vent_bridge(const mine_vent_bridge_params &params) {
  if (params.span <= 0 || params.width <= 0 || params.thickness <= 0 ||
      params.apex <= 0)
    throw Standard_ConstructionError("vent bridge dims positive");
  gp_Vec ax(params.axis);
  if (ax.Magnitude() < Precision::Confusion())
    throw Standard_ConstructionError("vent bridge axis degenerate");
  gp_Dir axis(ax);

  double rIn = params.span / 2, rOut = rIn + params.thickness;
  double kOut = params.apex / std::max(rOut, 1e-9);
  double kIn = params.apex / std::max(rIn, 1e-9);
  const int n = 12;
  std::vector<std::pair<double, double>> loop;
  for (int i = 0; i <= n; ++i) {
    double a = M_PI - double(i) / n * M_PI;
    loop.push_back({rOut * std::cos(a), rOut * std::sin(a) * kOut});
  }
  for (int i = n; i >= 0; --i) {
    double a = M_PI - double(i) / n * M_PI;
    loop.push_back({rIn * std::cos(a), rIn * std::sin(a) * kIn});
  }
  // 环面含 axis: plane 法向 = axis 的垂直向 (右法向), xdir = axis
  return mine_extrude_profile(params.center, axis, mine_right_perp(axis), loop,
                              params.width);
}

// 风筒: 圆管沿 3D 路径段挤出链 (路径已含吊挂标高)。
TopoDS_Shape create_mine_vent_duct(const mine_vent_duct_params &params) {
  if (params.diameter <= 0)
    throw Standard_ConstructionError("vent duct diameter positive");
  if (params.path.size() < 2)
    throw Standard_ConstructionError("vent duct path needs >= 2 points");
  double r = params.diameter / 2;
  std::vector<std::pair<double, double>> circ;
  for (int i = 0; i < 12; ++i) {
    double a = double(i) / 12 * 2 * M_PI;
    circ.push_back({r * std::cos(a), r * std::sin(a)});
  }
  TopoDS_Shape acc;
  for (size_t i = 1; i < params.path.size(); ++i) {
    const gp_Pnt &a = params.path[i - 1];
    const gp_Pnt &b = params.path[i];
    gp_Vec seg(a, b);
    double l = seg.Magnitude();
    if (l < Precision::Confusion())
      continue;
    gp_Dir dir(seg);
    TopoDS_Shape segShape =
        mine_extrude_profile(a, mine_left_perp(dir), dir, circ, l);
    acc = acc.IsNull() ? segShape : mine_fuse_two(acc, segShape);
  }
  if (acc.IsNull())
    throw Standard_ConstructionError("vent duct produced no geometry");
  return acc;
}

} // namespace topo
} // namespace flywave
