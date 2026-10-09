// 矿山专业参数化图元 — 公共助手 + A 井巷工程 + B 支护系统
// (minebim P 线, Q/SHJ 0035.3-2012; GIM 模式: 造型全在 C++, Go 层只做参数搬运)
//
// 单位: 无量纲 (minebim 场景口径 m; 铁路轨件沿用其声明单位)。
// 坐标: 世界坐标; 断面局部系 X=宽向, Y=高向, 底板 y=0。
#include "primitives_mine.hh"

#include <BRepAlgoAPI_Cut.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_MakePolygon.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_Transform.hxx>
#include <BRepOffsetAPI_ThruSections.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepPrimAPI_MakePrism.hxx>
#include <GC_MakeArcOfCircle.hxx>
#include <gp_Ax2.hxx>
#include <gp_Circ.hxx>
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

// ============ 公共助手 (mine 图元族共享, 外部链接, 声明见 primitives_mine.hh) ============

gp_Trsf mine_translation_trsf(const gp_Vec &v) {
  gp_Trsf t;
  t.SetTranslation(v);
  return t;
}

// 水平左法向 (-dy, dx); dir 非纯竖直。
gp_Dir mine_left_perp(const gp_Dir &d) {
  double hl = std::hypot(d.Y(), -d.X());
  if (hl < Precision::Confusion())
    return gp_Dir(1, 0, 0);
  return gp_Dir(-d.Y() / hl, d.X() / hl, 0);
}

// 水平右法向 (dy, -dx): 作 xdir=dir 平面的法向时, 局部 Y = normal×xdir = 竖直向上。
gp_Dir mine_right_perp(const gp_Dir &d) {
  double hl = std::hypot(d.Y(), -d.X());
  if (hl < Precision::Confusion())
    return gp_Dir(0, 1, 0);
  return gp_Dir(d.Y() / hl, -d.X() / hl, 0);
}

// 局部闭环 (origin + u*xdir + v*(normal×xdir)) → 闭合 wire。
TopoDS_Wire mine_wire_on_plane(const gp_Pnt &origin, const gp_Dir &xdir,
                          const gp_Dir &normal,
                          const std::vector<std::pair<double, double>> &pts) {
  gp_Dir ydir = normal.Crossed(xdir);
  BRepBuilderAPI_MakePolygon poly;
  for (const auto &q : pts) {
    gp_Pnt p = origin.Translated(gp_Vec(xdir) * q.first)
                   .Translated(gp_Vec(ydir) * q.second);
    poly.Add(p);
  }
  poly.Close();
  if (!poly.IsDone())
    throw Standard_ConstructionError("mine: polygon wire failed");
  return poly.Wire();
}

// 平面上的闭环沿 normal 挤出 dist (实体)。
TopoDS_Shape mine_extrude_profile(const gp_Pnt &origin, const gp_Dir &xdir,
                             const gp_Dir &normal,
                             const std::vector<std::pair<double, double>> &pts,
                             double dist) {
  TopoDS_Wire w = mine_wire_on_plane(origin, xdir, normal, pts);
  gp_Pln pln(origin, normal);
  BRepBuilderAPI_MakeFace mkFace(pln, w);
  if (!mkFace.IsDone())
    throw Standard_ConstructionError("mine: profile face failed");
  gp_Vec v(normal);
  v.Scale(dist);
  BRepPrimAPI_MakePrism prism(mkFace.Face(), v);
  if (!prism.IsDone())
    throw Standard_ConstructionError("mine: profile prism failed");
  return prism.Shape();
}

TopoDS_Shape mine_fuse_two(const TopoDS_Shape &a, const TopoDS_Shape &b) {
  BRepAlgoAPI_Fuse fuse(a, b);
  if (!fuse.IsDone())
    throw Standard_ConstructionError("mine: fuse failed");
  return fuse.Shape();
}

TopoDS_Shape mine_compound_all(const std::vector<TopoDS_Shape> &parts) {
  BRep_Builder bld;
  TopoDS_Compound cmp;
  bld.MakeCompound(cmp);
  int added = 0;
  for (const auto &p : parts) {
    if (p.IsNull())
      continue;
    bld.Add(cmp, p);
    ++added;
  }
  if (added == 0)
    throw Standard_ConstructionError("mine: empty compound");
  return cmp;
}

// 圆柱段 (起点 base, 沿 dir 长 len)。
TopoDS_Shape mine_cylinder_from(const gp_Pnt &base, const gp_Dir &dir, double r,
                           double len) {
  gp_Ax2 axis(base, dir);
  return BRepPrimAPI_MakeCylinder(axis, r, len).Shape();
}

// 断面环 → 环形棱柱体 (带孔: 内圈反向作孔), 用于井筒/带孔墙。
TopoDS_Shape mine_prism_with_hole(const gp_Pln &pln, const TopoDS_Wire &outer,
                             const TopoDS_Wire &inner, const gp_Vec &v) {
  BRepBuilderAPI_MakeFace mkFace(pln, outer);
  if (!mkFace.IsDone())
    throw Standard_ConstructionError("mine: outer face failed");
  mkFace.Add(TopoDS::Wire(inner.Reversed()));
  if (!mkFace.IsDone())
    throw Standard_ConstructionError("mine: inner hole failed");
  BRepPrimAPI_MakePrism prism(mkFace.Face(), v);
  if (!prism.IsDone())
    throw Standard_ConstructionError("mine: hole prism failed");
  return prism.Shape();
}

// ========================= 断面族 (6 种, 图例枚举) =========================

std::vector<std::pair<double, double>>
mine_section_loop(mine_section sec, double w, double h) {
  if (w <= 0 || h <= 0)
    throw Standard_ConstructionError("mine section: width/height positive");
  double hw = w / 2;
  std::vector<std::pair<double, double>> pts;
  switch (sec) {
  case mine_section::rect:
    pts = {{-hw, 0}, {hw, 0}, {hw, h}, {-hw, h}};
    return pts;
  case mine_section::trap: {
    double tw = w * 0.78;
    pts = {{-hw, 0}, {hw, 0}, {tw / 2, h}, {-tw / 2, h}};
    return pts;
  }
  case mine_section::circle: {
    double r = h / 2;
    for (int i = 0; i < 12; ++i) {
      double a = double(i) / 12 * 2 * M_PI;
      pts.push_back({r * std::cos(a), r * (1 + std::sin(a))});
    }
    return pts;
  }
  case mine_section::horseshoe: {
    // 马蹄: 直墙外张 + 侧弧 + 顶弧 (对齐 minebim SectionLoop 公式)
    double hw2 = hw * 1.12;
    double wall = h * 0.42;
    pts.push_back({-hw2, 0});
    pts.push_back({-hw2, wall});
    for (int i = 1; i <= 6; ++i) {
      double a = double(i) / 6 * (M_PI / 2);
      pts.push_back({-hw2 + hw2 * 0.12 + hw * 0.88 * (1 - std::cos(a)),
                     wall + (hw * 0.88) * std::sin(a) * 0.6});
    }
    for (int i = 1; i <= 8; ++i) {
      double a = double(i) / 8 * M_PI;
      pts.push_back({hw * std::cos(a), h - hw * (1 - std::sin(a))});
    }
    for (int i = 6; i >= 1; --i) {
      double a = double(i) / 6 * (M_PI / 2);
      pts.push_back({hw2 - hw2 * 0.12 - hw * 0.88 * (1 - std::cos(a)),
                     wall + (hw * 0.88) * std::sin(a) * 0.6});
    }
    pts.push_back({hw2, wall});
    pts.push_back({hw2, 0});
    return pts;
  }
  case mine_section::arc_arch: {
    // 圆弧拱: 直墙腿 + 大半径顶弧
    double wall = h * 0.35;
    double r = hw * 1.35;
    pts.push_back({-hw, 0});
    pts.push_back({-hw, wall});
    for (int i = 1; i <= 12; ++i) {
      double a = M_PI - double(i) / 12 * M_PI;
      pts.push_back(
          {r * std::cos(a), wall + (h - wall) * (std::sin(a) + 1) / 2});
    }
    pts.push_back({hw, wall});
    pts.push_back({hw, 0});
    return pts;
  }
  case mine_section::ellipse: {
    for (int i = 0; i < 20; ++i) {
      double a = double(i) / 20 * 2 * M_PI;
      pts.push_back({hw * std::cos(a), h / 2 + h / 2 * std::sin(a)});
    }
    return pts;
  }
  default: { // arch 半圆拱
    double wall = h - hw;
    if (wall < 0)
      wall = 0;
    pts.push_back({-hw, 0});
    pts.push_back({-hw, wall});
    for (int i = 1; i <= 10; ++i) {
      double a = M_PI - double(i) / 10 * M_PI;
      pts.push_back({hw * std::cos(a), wall + hw * std::sin(a)});
    }
    pts.push_back({hw, 0});
    return pts;
  }
  }
}

// 水沟: 断面沿偏移路径扫掠 (梯形/矩形; 左右偏移)。
TopoDS_Shape create_mine_trench(const mine_trench_params &params) {
  if (params.width <= 0 || params.height <= 0)
    throw Standard_ConstructionError("trench width/height positive");
  if (params.path.size() < 2)
    throw Standard_ConstructionError("trench path needs >= 2 points");
  auto loop = mine_section_loop(params.section, params.width, params.height);
  // 横向偏移 (逐段左法向 × sideOffset)
  std::vector<gp_Pnt> off;
  off.reserve(params.path.size());
  for (size_t i = 0; i < params.path.size(); ++i) {
    gp_Vec d = i + 1 < params.path.size()
                   ? gp_Vec(params.path[i], params.path[i + 1])
                   : gp_Vec(params.path[i - 1], params.path[i]);
    double l = d.Magnitude();
    if (l < Precision::Confusion()) {
      off.push_back(params.path[i]);
      continue;
    }
    d.Normalize();
    off.push_back(params.path[i].Translated(
        gp_Vec(d.Y(), -d.X(), 0) * (-params.sideOffset)));
  }
  TopoDS_Shape acc;
  for (size_t i = 1; i < off.size(); ++i) {
    const gp_Pnt &a = off[i - 1];
    const gp_Pnt &b = off[i];
    gp_Vec seg(a, b);
    double l = seg.Magnitude();
    if (l < Precision::Confusion())
      continue;
    gp_Dir dir(seg);
    TopoDS_Shape s = mine_extrude_profile(a, mine_left_perp(dir), dir, loop, l);
    acc = acc.IsNull() ? s : mine_fuse_two(acc, s);
  }
  if (acc.IsNull())
    throw Standard_ConstructionError("trench produced no geometry");
  return acc;
}

// 交岔点: 主巷×支巷棱柱并 + 可选加固衬砌段。
TopoDS_Shape create_mine_junction(const mine_junction_params &params) {
  if (params.width <= 0 || params.height <= 0 || params.mainLength <= 0 ||
      params.branchLength <= 0)
    throw Standard_ConstructionError("junction dims positive");
  if (params.branchAngleDeg <= 0 || params.branchAngleDeg >= 180)
    throw Standard_ConstructionError("branch angle must be in (0,180) degrees");
  gp_Vec axv(params.mainAxis);
  if (axv.Magnitude() < Precision::Confusion())
    throw Standard_ConstructionError("junction axis degenerate");
  gp_Dir mainAx(axv);
  auto loop = mine_section_loop(params.section, params.width, params.height);
  double ang = params.branchAngleDeg * M_PI / 180.0;

  // 主巷: 自 center 后退 mainLength/2 起沿主轴挤 mainLength
  gp_Pnt mo =
      params.center.Translated(gp_Vec(mainAx) * (-params.mainLength / 2));
  TopoDS_Shape acc = mine_extrude_profile(mo, mine_left_perp(mainAx), mainAx,
                                          loop, params.mainLength);

  // 支巷: 主轴旋转 branchAngle
  gp_Trsf rot;
  rot.SetRotation(gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), ang);
  gp_Dir branchAx = gp_Dir(gp_Vec(mainAx).Transformed(rot));
  gp_Pnt bo =
      params.center.Translated(gp_Vec(branchAx) * (-params.branchLength / 2));
  TopoDS_Shape branch = mine_extrude_profile(
      bo, mine_left_perp(branchAx), branchAx, loop, params.branchLength);
  acc = mine_fuse_two(acc, branch);

  // 加固段 (挑棚): 交点处衬砌环
  if (params.reinforceLength > 0) {
    mine_shotcrete_params sp;
    sp.origin = params.center;
    sp.axis = mainAx;
    sp.section = params.section;
    sp.width = params.width;
    sp.height = params.height;
    sp.thickness = std::max(params.reinforceLength, 0.05);
    sp.length = params.reinforceLength;
    acc = mine_fuse_two(acc, create_mine_shotcrete(sp));
  }
  return acc;
}

mine_section mine_section_cast(int v) {
  if (v < 0 || v > 6)
    throw Standard_ConstructionError("mine section enum out of range");
  return static_cast<mine_section>(v);
}

// ================= 立井井筒 (图例 2/3/4/5/9) — 沿用并复用助手 =================

TopoDS_Shape create_mine_shaft(const mine_shaft_params &params) {
  if (params.depth <= 0.0)
    throw Standard_ConstructionError("Depth must be positive");

  TopoDS_Wire outerWire, innerWire;
  if (params.shape == 0) {
    if (params.innerRadius <= 0.0)
      throw Standard_ConstructionError("Inner radius must be positive");
    if (params.outerRadius <= params.innerRadius)
      throw Standard_ConstructionError(
          "Outer radius must be greater than inner radius");
    gp_Ax2 axis(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
    outerWire =
        BRepBuilderAPI_MakeWire(BRepBuilderAPI_MakeEdge(gp_Circ(axis, params.outerRadius)).Edge())
            .Wire();
    innerWire =
        BRepBuilderAPI_MakeWire(BRepBuilderAPI_MakeEdge(gp_Circ(axis, params.innerRadius)).Edge())
            .Wire();
  } else {
    if (params.innerWidth <= 0.0 || params.innerLength <= 0.0)
      throw Standard_ConstructionError("Inner length/width must be positive");
    if (params.outerWidth <= params.innerWidth ||
        params.outerLength <= params.innerLength)
      throw Standard_ConstructionError(
          "Outer dims must be greater than inner dims");
    double il = params.innerLength / 2, iw = params.innerWidth / 2;
    double ol = params.outerLength / 2, ow = params.outerWidth / 2;
    BRepBuilderAPI_MakePolygon op, ip;
    op.Add(gp_Pnt(-ol, -ow, 0));
    op.Add(gp_Pnt(ol, -ow, 0));
    op.Add(gp_Pnt(ol, ow, 0));
    op.Add(gp_Pnt(-ol, ow, 0));
    op.Close();
    ip.Add(gp_Pnt(-il, -iw, 0));
    ip.Add(gp_Pnt(il, -iw, 0));
    ip.Add(gp_Pnt(il, iw, 0));
    ip.Add(gp_Pnt(-il, iw, 0));
    ip.Close();
    if (!op.IsDone() || !ip.IsDone())
      throw Standard_ConstructionError("Failed to create shaft rectangles");
    outerWire = op.Wire();
    innerWire = ip.Wire();
  }

  gp_Pln pln(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
  gp_Vec down(0, 0, -params.depth);
  return mine_prism_with_hole(pln, outerWire, innerWire, down);
}

TopoDS_Shape create_mine_shaft(const mine_shaft_params &params,
                               const gp_Pnt &collarCenter) {
  TopoDS_Shape shaft = create_mine_shaft(params);
  BRepBuilderAPI_Transform transform(
      shaft, mine_translation_trsf(gp_Vec(collarCenter.XYZ())));
  return transform.Shape();
}

// ================= 煤仓/溜煤眼 (图例 16): 站位变径放样 =================

TopoDS_Shape create_mine_orepass(const mine_orepass_params &params) {
  if (params.stations.size() < 2)
    throw Standard_ConstructionError("Orepass needs at least 2 stations");
  double lastDepth = -1.0;
  for (const auto &st : params.stations) {
    if (st.radius <= 0.0)
      throw Standard_ConstructionError("Station radius must be positive");
    if (st.depth < 0.0)
      throw Standard_ConstructionError("Station depth must be non-negative");
    if (st.depth <= lastDepth + Precision::Confusion())
      throw Standard_ConstructionError("Station depths must strictly increase");
    lastDepth = st.depth;
  }

  BRepOffsetAPI_ThruSections generator(Standard_True);
  for (const auto &st : params.stations) {
    gp_Ax2 axis(gp_Pnt(params.center.X(), params.center.Y(),
                       params.center.Z() - st.depth),
                gp_Dir(0, 0, 1));
    gp_Circ circ(axis, st.radius);
    generator.AddWire(
        BRepBuilderAPI_MakeWire(BRepBuilderAPI_MakeEdge(circ).Edge()).Wire());
  }
  generator.Build();
  if (!generator.IsDone())
    throw Standard_ConstructionError("Failed to loft orepass");
  return generator.Shape();
}

// ================= 巷道支护衬砌壳 (喷浆/砌碹/U型钢环) =================

TopoDS_Shape create_mine_lining(const mine_lining_params &params) {
  if (params.thickness <= 0.0)
    throw Standard_ConstructionError("Thickness must be positive");
  if (params.length <= 0.0)
    throw Standard_ConstructionError("Length must be positive");
  const std::vector<gp_Pnt> &pts = params.section;
  if (pts.size() < 3)
    throw Standard_ConstructionError("At least 3 section points required");
  gp_Dir dir = params.dir;

  // Newell 法求断面环法向
  double nx = 0, ny = 0, nz = 0;
  for (size_t i = 0; i < pts.size(); ++i) {
    const gp_Pnt &a = pts[i];
    const gp_Pnt &b = pts[(i + 1) % pts.size()];
    nx += (a.Y() - b.Y()) * (a.Z() + b.Z());
    ny += (a.Z() - b.Z()) * (a.X() + b.X());
    nz += (a.X() - b.X()) * (a.Y() + b.Y());
  }
  gp_Vec loopNormal(nx, ny, nz);
  if (loopNormal.Magnitude() < Precision::Confusion())
    throw Standard_ConstructionError("Degenerate section loop");

  double t = params.thickness;
  gp_Vec extrude(dir);
  extrude.Scale(params.length);

  TopoDS_Shape acc;
  for (size_t i = 0; i < pts.size(); ++i) {
    gp_Pnt p1 = pts[i];
    gp_Pnt p2 = pts[(i + 1) % pts.size()];
    gp_Vec e(p1, p2);
    if (e.Magnitude() < Precision::Confusion())
      continue;
    e.Normalize();
    gp_Vec out = e.Crossed(loopNormal);
    out.Normalize();
    out.Scale(t);

    gp_Pnt q1 = p1.Translated(gp_Vec(e) * (-t));
    gp_Pnt q2 = p2.Translated(gp_Vec(e) * t);
    gp_Pnt q3 = q2.Translated(out);
    gp_Pnt q4 = q1.Translated(out);

    BRepBuilderAPI_MakePolygon poly;
    poly.Add(q1);
    poly.Add(q2);
    poly.Add(q3);
    poly.Add(q4);
    poly.Close();
    if (!poly.IsDone())
      throw Standard_ConstructionError("Failed to build lining segment");
    BRepBuilderAPI_MakeFace mkFace(poly.Wire());
    if (!mkFace.IsDone())
      throw Standard_ConstructionError("Failed to face lining segment");
    BRepPrimAPI_MakePrism seg(mkFace.Face(), extrude);
    if (!seg.IsDone())
      throw Standard_ConstructionError("Failed to extrude lining segment");

    if (acc.IsNull()) {
      acc = seg.Shape();
    } else {
      acc = mine_fuse_two(acc, seg.Shape());
    }
  }
  if (acc.IsNull())
    throw Standard_ConstructionError("Empty lining");
  return acc;
}

// 喷浆/砌碹衬砌 (断面枚举式)。
TopoDS_Shape create_mine_shotcrete(const mine_shotcrete_params &params) {
  if (params.width <= 0 || params.height <= 0 || params.thickness <= 0 ||
      params.length <= 0)
    throw Standard_ConstructionError("shotcrete dims positive");
  gp_Vec axv(params.axis);
  if (axv.Magnitude() < Precision::Confusion())
    throw Standard_ConstructionError("shotcrete axis degenerate");
  gp_Dir axis(axv);
  auto loop = mine_section_loop(params.section, params.width, params.height);
  gp_Dir xdir = mine_left_perp(axis);
  gp_Dir up = axis.Crossed(xdir);
  std::vector<gp_Pnt> pts;
  pts.reserve(loop.size());
  for (const auto &q : loop) {
    pts.push_back(params.origin.Translated(gp_Vec(xdir) * q.first)
                      .Translated(gp_Vec(up) * q.second));
  }
  mine_lining_params lp;
  lp.section = pts;
  lp.thickness = params.thickness;
  lp.length = params.length;
  lp.dir = axis;
  return create_mine_lining(lp);
}

// 钢带/W钢带: 长板 + n 孔 (Cut); 长度沿局部 X, 平面 z=0。
TopoDS_Shape create_mine_steel_band(const mine_steel_band_params &params) {
  if (params.length <= 0 || params.width <= 0 || params.thickness <= 0)
    throw Standard_ConstructionError("steel band dims positive");
  if (params.holeCount < 0)
    throw Standard_ConstructionError("hole count non-negative");
  BRepBuilderAPI_MakePolygon poly;
  poly.Add(gp_Pnt(-params.length / 2, -params.width / 2, 0));
  poly.Add(gp_Pnt(params.length / 2, -params.width / 2, 0));
  poly.Add(gp_Pnt(params.length / 2, params.width / 2, 0));
  poly.Add(gp_Pnt(-params.length / 2, params.width / 2, 0));
  poly.Close();
  if (!poly.IsDone())
    throw Standard_ConstructionError("steel band polygon failed");
  BRepBuilderAPI_MakeFace mkFace(poly.Wire());
  if (!mkFace.IsDone())
    throw Standard_ConstructionError("steel band face failed");
  gp_Vec up(0, 0, params.thickness);
  BRepPrimAPI_MakePrism plate(mkFace.Face(), up);
  if (!plate.IsDone())
    throw Standard_ConstructionError("steel band prism failed");
  TopoDS_Shape acc = plate.Shape();
  if (params.holeCount > 0 && params.holeDia > 0) {
    double span = params.length - 2 * params.holeEdge;
    if (span <= 0)
      throw Standard_ConstructionError("holes do not fit band length");
    for (int i = 0; i < params.holeCount; ++i) {
      double x = -params.length / 2 + params.holeEdge +
                 span * double(i) / std::max(params.holeCount - 1, 1);
      gp_Ax2 axis(gp_Pnt(x, 0, -1), gp_Dir(0, 0, 1));
      BRepPrimAPI_MakeCylinder hole(axis, params.holeDia / 2, params.thickness + 2);
      BRepAlgoAPI_Cut cut(acc, hole.Shape());
      if (!cut.IsDone())
        throw Standard_ConstructionError("steel band hole cut failed");
      acc = cut.Shape();
    }
  }
  return acc;
}

// ================= A 井巷: 巷道 (断面沿折线扫掠 + 拐角楔补) =================

// 拐角楔补长度 (对齐 minebim cornerFill): hw×(1/max(dot,0.2)-1) 上界, 封顶 2hw。
static double mine_corner_fill(double w, const gp_Dir &d1, const gp_Dir &d2) {
  double dot = d1.X() * d2.X() + d1.Y() * d2.Y();
  if (dot >= 0.999)
    return 0;
  double hw = w / 2;
  if (dot <= -0.999)
    return hw;
  double fill = hw * (1.0 / std::max(dot, 0.2) - 1.0);
  if (fill > 2 * hw)
    fill = 2 * hw;
  if (fill < 0.05)
    return 0;
  return fill;
}

TopoDS_Shape create_mine_roadway(const mine_roadway_params &params) {
  if (params.width <= 0 || params.height <= 0)
    throw Standard_ConstructionError("roadway width/height positive");
  if (params.path.size() < 2)
    throw Standard_ConstructionError("roadway path needs >= 2 points");
  auto loop = mine_section_loop(params.section, params.width, params.height);

  TopoDS_Shape acc;
  const std::vector<gp_Pnt> &path = params.path;
  for (size_t i = 1; i < path.size(); ++i) {
    const gp_Pnt &a = path[i - 1];
    const gp_Pnt &b = path[i];
    gp_Vec seg(a, b);
    double l = seg.Magnitude();
    if (l < Precision::Confusion())
      continue;
    gp_Dir dir(seg);
    gp_Dir xdir = mine_left_perp(dir);
    TopoDS_Shape body =
        mine_extrude_profile(a, xdir, dir, loop, l);
    acc = acc.IsNull() ? body : mine_fuse_two(acc, body);

    // 内角楔补 (凸拐角外缺口)
    if (i + 1 < path.size()) {
      const gp_Pnt &c = path[i + 1];
      gp_Vec seg2(b, c);
      if (seg2.Magnitude() < Precision::Confusion())
        continue;
      gp_Dir dir2(seg2);
      gp_Vec bis = gp_Vec(dir) + gp_Vec(dir2);
      if (bis.Magnitude() < Precision::Confusion())
        continue;
      gp_Dir bdir(bis);
      gp_Dir bx = mine_left_perp(bdir);
      // 水平分量退化 (竖直段) 不补楔
      if (std::hypot(dir.X(), dir.Y()) < Precision::Confusion() ||
          std::hypot(dir2.X(), dir2.Y()) < Precision::Confusion())
        continue;
      double fill = mine_corner_fill(params.width, gp_Dir(dir.X(), dir.Y(), 0),
                                     gp_Dir(dir2.X(), dir2.Y(), 0));
      if (fill > 0) {
        TopoDS_Shape wedge =
            mine_extrude_profile(b, bx, gp_Dir(bdir.X(), bdir.Y(), 0), loop, fill);
        acc = mine_fuse_two(acc, wedge);
      }
    }
  }
  if (acc.IsNull())
    throw Standard_ConstructionError("roadway produced no geometry");
  return acc;
}

// ================= A 井巷: 硐室 / 工作面 / 迎头 / 面状体 =================

TopoDS_Shape create_mine_chamber(const mine_chamber_params &params) {
  if (params.length <= 0 || params.width <= 0 || params.height <= 0)
    throw Standard_ConstructionError("chamber dims positive");
  auto loop = mine_section_loop(mine_section::rect, params.length, params.height);
  // center = 底面中心: 局部 X ∈ ±长/2, 沿 -Y 挤宽 → 先把原点移到 +宽/2
  gp_Pnt o = params.center.Translated(gp_Vec(0, params.width / 2, 0));
  return mine_extrude_profile(o, gp_Dir(1, 0, 0), gp_Dir(0, -1, 0), loop,
                         params.width);
}

TopoDS_Shape create_mine_workingface(const mine_workingface_params &params) {
  if (params.faceLength <= 0 || params.advance <= 0 || params.seamThickness <= 0)
    throw Standard_ConstructionError("workingface dims positive");
  gp_Dir dir = params.dir;
  gp_Dir nrm = mine_right_perp(dir); // 法向: 保证局部 Y = 竖直向上
  std::vector<std::pair<double, double>> loop = {
      {0, 0}, {params.faceLength, 0}, {params.faceLength, params.advance}, {0, params.advance}};
  return mine_extrude_profile(params.origin, dir, nrm, loop, params.seamThickness);
}

TopoDS_Shape create_mine_heading(const mine_heading_params &params) {
  if (params.width <= 0 || params.height <= 0)
    throw Standard_ConstructionError("heading dims positive");
  gp_Vec d(params.dir);
  if (d.Magnitude() < Precision::Confusion())
    throw Standard_ConstructionError("heading dir degenerate");
  auto loop = mine_section_loop(params.section, params.width, params.height);
  return mine_extrude_profile(params.center, mine_left_perp(gp_Dir(d)),
                         gp_Dir(d), loop, 0.5);
}

TopoDS_Shape create_mine_area_body(const mine_area_body_params &params) {
  if (params.boundary.size() < 3)
    throw Standard_ConstructionError("area boundary needs >= 3 points");
  if (params.height <= 0)
    throw Standard_ConstructionError("area height positive");
  BRepBuilderAPI_MakePolygon poly;
  for (const auto &q : params.boundary)
    poly.Add(q);
  poly.Close();
  if (!poly.IsDone())
    throw Standard_ConstructionError("area polygon failed");
  BRepBuilderAPI_MakeFace mkFace(poly.Wire());
  if (!mkFace.IsDone())
    throw Standard_ConstructionError("area face failed");
  gp_Vec up(0, 0, params.height);
  BRepPrimAPI_MakePrism prism(mkFace.Face(), up);
  if (!prism.IsDone())
    throw Standard_ConstructionError("area prism failed");
  if (params.baseZ != 0) {
    BRepBuilderAPI_Transform tr(prism.Shape(),
                                mine_translation_trsf(gp_Vec(0, 0, params.baseZ)));
    return tr.Shape();
  }
  return prism.Shape();
}

// ================= B 支护: 锚杆排 / U型钢排 / 液压支架排 =================

TopoDS_Shape create_mine_bolt_row(const mine_bolt_row_params &params) {
  if (params.width <= 0 || params.height <= 0 || params.boltLength <= 0 ||
      params.diameter <= 0 || params.spacing <= 0)
    throw Standard_ConstructionError("bolt dims positive");
  if (params.rowCount <= 0 || params.rowCount > 12)
    throw Standard_ConstructionError("rowCount out of [1,12]");
  if (params.perRow <= 0 || params.perRow > 8)
    throw Standard_ConstructionError("perRow out of [1,8]");

  gp_Vec ax(params.axis);
  if (ax.Magnitude() < Precision::Confusion())
    throw Standard_ConstructionError("bolt axis degenerate");
  gp_Dir axis(ax);
  gp_Dir side = mine_left_perp(axis);
  double hw = params.width / 2;
  gp_Dir up(0, 0, 1);

  std::vector<TopoDS_Shape> parts;
  for (int row = 0; row < params.rowCount; ++row) {
    gp_Pnt c = params.origin.Translated(gp_Vec(axis) * (params.spacing * row));
    for (int k = 0; k < params.perRow; ++k) {
      double t = (double(k) + 0.5) / params.perRow * params.width - hw;
      parts.push_back(mine_cylinder_from(
          c.Translated(gp_Vec(side) * t).Translated(gp_Vec(0, 0, params.height)),
          up, params.diameter / 2, params.boltLength));
    }
    for (int s = 0; s < 2; ++s) {
      gp_Vec sd = gp_Vec(side) * (s == 0 ? 1 : -1);
      parts.push_back(mine_cylinder_from(
          c.Translated(sd * hw).Translated(gp_Vec(0, 0, params.height * 0.6)),
          gp_Dir(sd), params.diameter / 2, params.boltLength));
    }
    if (params.cable) { // 锚索托盘 (薄板)
      std::vector<std::pair<double, double>> tray = {
          {-hw + 0.15, params.height - 0.02}, {hw - 0.15, params.height - 0.02},
          {hw - 0.15, params.height + 0.02}, {-hw + 0.15, params.height + 0.02}};
      parts.push_back(mine_extrude_profile(c, side, axis, tray, 0.02));
    }
  }
  return mine_compound_all(parts);
}

TopoDS_Shape create_mine_usteel_row(const mine_usteel_row_params &params) {
  if (params.width <= 0 || params.height <= 0 || params.thickness <= 0 ||
      params.spacing <= 0)
    throw Standard_ConstructionError("usteel dims positive");
  if (params.count <= 0 || params.count > 20)
    throw Standard_ConstructionError("count out of [1,20]");

  gp_Vec ax(params.axis);
  if (ax.Magnitude() < Precision::Confusion())
    throw Standard_ConstructionError("usteel axis degenerate");
  gp_Dir axis(ax);
  auto loop = mine_section_loop(params.section, params.width, params.height);
  gp_Dir xdir = mine_left_perp(axis);

  std::vector<TopoDS_Shape> parts;
  for (int i = 0; i < params.count; ++i) {
    gp_Pnt c = params.origin.Translated(gp_Vec(axis) * (params.spacing * i));
    TopoDS_Wire w = mine_wire_on_plane(c, xdir, axis, loop);
    gp_Pln pln(c, axis);
    BRepBuilderAPI_MakeFace mkFace(pln, w);
    if (!mkFace.IsDone())
      throw Standard_ConstructionError("usteel face failed");
    gp_Vec ex(axis);
    ex.Scale(params.thickness);
    BRepPrimAPI_MakePrism ring(mkFace.Face(), ex);
    if (!ring.IsDone())
      throw Standard_ConstructionError("usteel ring failed");
    parts.push_back(ring.Shape());
  }
  return mine_compound_all(parts);
}

TopoDS_Shape create_mine_shield_row(const mine_shield_row_params &params) {
  if (params.count <= 0 || params.centerDist <= 0 || params.beamWidth <= 0 ||
      params.beamThick <= 0 || params.height <= 0)
    throw Standard_ConstructionError("shield dims positive");
  if (params.count > 400)
    throw Standard_ConstructionError("count > 400");

  gp_Vec dv(params.dir);
  if (dv.Magnitude() < Precision::Confusion())
    throw Standard_ConstructionError("shield dir degenerate");
  gp_Dir dir(dv);
  gp_Dir side = mine_left_perp(dir);
  double length = params.count * params.centerDist;
  double hw = params.beamWidth / 2;
  int legPairs = std::min(params.count, 24);

  // 通长板: 局部 X = 切眼向 (plane 法向 = 右法向, 局部 Y = 竖直向上)
  std::vector<std::pair<double, double>> base = {{0, 0}, {length, 0}, {length, 0.4}, {0, 0.4}};
  std::vector<std::pair<double, double>> beam = {
      {0, params.height - params.beamThick},
      {length, params.height - params.beamThick},
      {length, params.height},
      {0, params.height}};
  gp_Dir nrm = mine_right_perp(dir);
  gp_Pnt o1 = params.origin.Translated(gp_Vec(nrm) * hw);
  std::vector<TopoDS_Shape> parts;
  parts.push_back(mine_extrude_profile(o1, dir, nrm, base, params.beamWidth));
  parts.push_back(mine_extrude_profile(o1, dir, nrm, beam, params.beamWidth));

  gp_Dir up(0, 0, 1);
  double legH = params.height - params.beamThick - 0.4;
  for (int i = 0; i < legPairs; ++i) {
    double d = length / legPairs * (i + 0.5);
    for (int s = 0; s < 2; ++s) {
      gp_Vec sd = gp_Vec(side) * (s == 0 ? 1 : -1) * (hw * 0.6);
      parts.push_back(mine_cylinder_from(
          params.origin.Translated(gp_Vec(dir) * d).Translated(sd).Translated(gp_Vec(0, 0, 0.4)),
          up, 0.14, legH));
    }
  }
  return mine_compound_all(parts);
}

// 测风站: 断面框标 (两侧立柱 + 顶梁, 沿轴挤 depth)。compound。
TopoDS_Shape create_mine_vent_station(const mine_vent_station_params &params) {
  if (params.width <= 0 || params.height <= 0 || params.postWidth <= 0 ||
      params.depth <= 0)
    throw Standard_ConstructionError("vent station dims positive");
  gp_Vec axv(params.axis);
  if (axv.Magnitude() < Precision::Confusion())
    throw Standard_ConstructionError("vent station axis degenerate");
  gp_Dir axis(axv);
  double hw = params.width / 2, pw = params.postWidth;
  auto rect = [](double x0, double y0, double x1, double y1) {
    return std::vector<std::pair<double, double>>{
        {x0, y0}, {x1, y0}, {x1, y1}, {x0, y1}};
  };
  std::vector<TopoDS_Shape> parts;
  parts.push_back(mine_extrude_profile(params.center, mine_left_perp(axis),
                                       axis, rect(-hw, 0, -hw + pw, params.height),
                                       params.depth));
  parts.push_back(mine_extrude_profile(params.center, mine_left_perp(axis),
                                       axis, rect(hw - pw, 0, hw, params.height),
                                       params.depth));
  parts.push_back(mine_extrude_profile(params.center, mine_left_perp(axis),
                                       axis,
                                       rect(-hw, params.height - pw, hw, params.height),
                                       params.depth));
  return mine_compound_all(parts);
}

} // namespace topo
} // namespace flywave
