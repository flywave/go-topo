// 矿山专业参数化图元 — E 运输系统 (minebim P 线)
// 轨道 (170, 复用 create_rail_pair) / 道岔 (161-167) / 带式输送机 (34-36) /
// 刮板输送机 (28-33) / 单轨吊 (74)。
#include "primitives_mine.hh"

#include "primitives_railway.hh"

#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepPrimAPI_MakePrism.hxx>
#include <gp_Ax1.hxx>
#include <gp_Ax2.hxx>
#include <gp_Circ.hxx>
#include <gp_Pln.hxx>
#include <algorithm>
#include <cmath>
#include <Precision.hxx>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace flywave {
namespace topo {

namespace {

// 折线横向偏移 (逐段左法向; 拐角缺口由轨枕遮蔽)。
std::vector<gp_Pnt> mine_offset_path(const std::vector<gp_Pnt> &path,
                                     double off) {
  std::vector<gp_Pnt> out;
  out.reserve(path.size());
  for (size_t i = 0; i < path.size(); ++i) {
    gp_Vec d = i + 1 < path.size() ? gp_Vec(path[i], path[i + 1])
                                   : gp_Vec(path[i - 1], path[i]);
    double l = d.Magnitude();
    if (l < Precision::Confusion()) {
      out.push_back(path[i]);
      continue;
    }
    d.Normalize();
    gp_Vec n = gp_Vec(d.Y(), -d.X(), 0) * (-off); // 左法向 × off
    out.push_back(path[i].Translated(n));
  }
  return out;
}

} // namespace

// 轨道: rail pair (复用铁路图元) + 轨枕 compound; 双轨 ±centerDistance/2。
TopoDS_Shape create_mine_rail_track(const mine_rail_track_params &params) {
  if (params.gauge <= 0)
    throw Standard_ConstructionError("rail gauge positive");
  if (params.path.size() < 2)
    throw Standard_ConstructionError("rail path needs >= 2 points");
  if (params.sleeperSpacing < 0)
    throw Standard_ConstructionError("sleeper spacing non-negative");

  rail_pair_params rp;
  rp.gauge = params.gauge;
  rp.superElevation = 0;
  rp.railHeight = 0.135;
  rp.railHeadWidth = 0.042;
  rp.railBaseWidth = 0.06;

  std::vector<std::vector<gp_Pnt>> lines;
  if (params.doubleTrack) {
    if (params.centerDistance <= params.gauge)
      throw Standard_ConstructionError("center distance must exceed gauge");
    double d = params.centerDistance / 2;
    lines.push_back(mine_offset_path(params.path, d));
    lines.push_back(mine_offset_path(params.path, -d));
  } else {
    lines.push_back(params.path);
  }

  std::vector<TopoDS_Shape> parts;
  for (auto &ln : lines) {
    rp.centerline = ln;
    parts.push_back(create_rail_pair(rp));
  }

  // 轨枕 (垂直轨道的横板, 免布尔 compound, 数量封顶)
  if (params.sleeperSpacing > 0 && params.sleeperMax > 0) {
    double zBase = params.path.front().Z();
    int count = 0;
    for (auto &ln : lines) {
      for (size_t i = 1; i < ln.size() && count < params.sleeperMax; ++i) {
        gp_Vec seg(ln[i - 1], ln[i]);
        double l = seg.Magnitude();
        if (l < Precision::Confusion())
          continue;
        gp_Dir dir(seg);
        int n = int(l / params.sleeperSpacing);
        for (int k = 0; k < n && count < params.sleeperMax; ++k) {
          double d = params.sleeperSpacing * (k + 0.5);
          gp_Pnt c = ln[i - 1].Translated(gp_Vec(dir) * d)
                         .Translated(gp_Vec(0, 0, -0.06));
          // 轨枕横板: 局部 X = 横向 (轨距+0.5), Y = 竖厚 0.12, 沿轨道向挤 0.12
          double half = (params.gauge + 0.5) / 2;
          std::vector<std::pair<double, double>> sleeper = {
              {-half, 0}, {half, 0}, {half, 0.12}, {-half, 0.12}};
          parts.push_back(mine_extrude_profile(c, mine_left_perp(dir), dir,
                                               sleeper, 0.12));
          ++count;
        }
      }
    }
  }
  return mine_compound_all(parts);
}

// 道岔 (v1 骨架): 直股 + 辙叉角曲股 rail pairs。
TopoDS_Shape create_mine_turnout(const mine_turnout_params &params) {
  if (params.gauge <= 0 || params.length <= 0 || params.length > 200)
    throw Standard_ConstructionError("turnout length out of (0,200]");
  if (params.frogNo < 2 || params.frogNo > 30)
    throw Standard_ConstructionError("frogNo out of [2,30]");
  gp_Vec axv(params.axis);
  if (axv.Magnitude() < Precision::Confusion())
    throw Standard_ConstructionError("turnout axis degenerate");
  gp_Dir axis(axv);

  rail_pair_params rp;
  rp.gauge = params.gauge;
  rp.superElevation = 0;
  rp.railHeight = 0.135;
  rp.railHeadWidth = 0.042;
  rp.railBaseWidth = 0.06;

  std::vector<TopoDS_Shape> parts;
  // 直股
  rp.centerline = {params.origin,
                   params.origin.Translated(gp_Vec(axis) * params.length)};
  parts.push_back(create_rail_pair(rp));

  // 曲股: 岔尖 2m 起以辙叉角渐进偏转 (1:n → 角 = 2·atan(1/2n))
  double angle = 2.0 * std::atan(1.0 / (2.0 * params.frogNo));
  double az = std::atan2(axis.Y(), axis.X());
  std::vector<gp_Pnt> branch{params.origin.Translated(gp_Vec(axis) * 2.0)};
  double cx = params.origin.X(), cy = params.origin.Y();
  double dir = az;
  const double step = 2.0;
  for (double d = 2.0; d < params.length; d += step) {
    dir += angle * step / params.length;
    cx += std::cos(dir) * step;
    cy += std::sin(dir) * step;
    branch.push_back(gp_Pnt(cx, cy, params.origin.Z()));
  }
  rp.centerline = mine_offset_path(branch, params.gauge / 2);
  parts.push_back(create_rail_pair(rp));
  return mine_compound_all(parts);
}

// 带式输送机: 带面扫掠 + 头尾滚筒 (path z = 底板标高)。
TopoDS_Shape create_mine_belt(const mine_belt_params &params) {
  if (params.beltWidth <= 0 || params.beltWidth > 2.5)
    throw Standard_ConstructionError("belt width out of (0,2.5]");
  if (params.frameHeight <= 0)
    throw Standard_ConstructionError("frame height positive");
  if (params.path.size() < 2)
    throw Standard_ConstructionError("belt path needs >= 2 points");

  double hw = params.beltWidth / 2;
  std::vector<std::pair<double, double>> belt = {
      {-hw, params.frameHeight - 0.04},
      {hw, params.frameHeight - 0.04},
      {hw, params.frameHeight + 0.04},
      {-hw, params.frameHeight + 0.04}};

  TopoDS_Shape acc;
  for (size_t i = 1; i < params.path.size(); ++i) {
    const gp_Pnt &a = params.path[i - 1];
    const gp_Pnt &b = params.path[i];
    gp_Vec seg(a, b);
    double l = seg.Magnitude();
    if (l < Precision::Confusion())
      continue;
    gp_Dir dir(seg);
    TopoDS_Shape s = mine_extrude_profile(a, mine_left_perp(dir), dir, belt, l);
    acc = acc.IsNull() ? s : mine_fuse_two(acc, s);
  }
  if (acc.IsNull())
    throw Standard_ConstructionError("belt produced no geometry");

  // 头尾滚筒 (横置圆柱, 轴垂直端段)
  std::vector<TopoDS_Shape> parts{acc};
  for (int end = 0; end < 2; ++end) {
    size_t i = end == 0 ? 1 : params.path.size() - 1;
    gp_Vec seg(params.path[end == 0 ? 0 : params.path.size() - 1], params.path[i]);
    if (seg.Magnitude() < Precision::Confusion())
      continue;
    gp_Dir dir(seg);
    gp_Dir drumAxis = mine_left_perp(dir);
    parts.push_back(mine_cylinder_from(
        params.path[end == 0 ? 0 : params.path.size() - 1], drumAxis,
        params.beltWidth / 4 + 0.05, params.beltWidth + 0.2));
  }
  return mine_compound_all(parts);
}

// 刮板输送机: U 槽断面沿路径 (槽厚 0.03)。
TopoDS_Shape create_mine_scraper(const mine_scraper_params &params) {
  if (params.panWidth <= 0 || params.panHeight <= 0)
    throw Standard_ConstructionError("pan dims positive");
  if (params.path.size() < 2)
    throw Standard_ConstructionError("scraper path needs >= 2 points");
  double w2 = params.panWidth / 2, t = 0.03, h = params.panHeight;
  std::vector<std::pair<double, double>> u = {
      {-w2, 0},      {w2, 0},      {w2, t},      {w2 - t, t},
      {w2 - t, h - t}, {w2, h - t}, {w2, h},    {-w2, h},
      {-w2, h - t},  {-w2 + t, h - t}, {-w2 + t, t}, {-w2, t}};
  TopoDS_Shape acc;
  for (size_t i = 1; i < params.path.size(); ++i) {
    const gp_Pnt &a = params.path[i - 1];
    const gp_Pnt &b = params.path[i];
    gp_Vec seg(a, b);
    double l = seg.Magnitude();
    if (l < Precision::Confusion())
      continue;
    gp_Dir dir(seg);
    TopoDS_Shape s = mine_extrude_profile(a, mine_left_perp(dir), dir, u, l);
    acc = acc.IsNull() ? s : mine_fuse_two(acc, s);
  }
  if (acc.IsNull())
    throw Standard_ConstructionError("scraper produced no geometry");
  return acc;
}

// 单轨吊: I 断面沿吊挂路径。
TopoDS_Shape create_mine_monorail(const mine_monorail_params &params) {
  if (params.railHeight <= 0 || params.railHeight > 0.5 ||
      params.flangeWidth <= 0 || params.flangeWidth > 0.3)
    throw Standard_ConstructionError("monorail dims out of range");
  if (params.path.size() < 2)
    throw Standard_ConstructionError("monorail path needs >= 2 points");
  double h = params.railHeight, w = params.flangeWidth;
  double tf = h / 6, tw = w / 3;
  std::vector<std::pair<double, double>> iBeam = {
      {-w / 2, 0},     {w / 2, 0},         {w / 2, tf},      {tw / 2, tf},
      {tw / 2, h - tf}, {w / 2, h - tf},   {w / 2, h},       {-w / 2, h},
      {-w / 2, h - tf}, {-tw / 2, h - tf}, {-tw / 2, tf},    {-w / 2, tf}};
  TopoDS_Shape acc;
  for (size_t i = 1; i < params.path.size(); ++i) {
    const gp_Pnt &a = params.path[i - 1];
    const gp_Pnt &b = params.path[i];
    gp_Vec seg(a, b);
    double l = seg.Magnitude();
    if (l < Precision::Confusion())
      continue;
    gp_Dir dir(seg);
    TopoDS_Shape s =
        mine_extrude_profile(a, mine_left_perp(dir), dir, iBeam, l);
    acc = acc.IsNull() ? s : mine_fuse_two(acc, s);
  }
  if (acc.IsNull())
    throw Standard_ConstructionError("monorail produced no geometry");
  return acc;
}

} // namespace topo
} // namespace flywave
