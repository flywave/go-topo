// 矿山专业参数化图元 — F 管线系统 (minebim P 线)
// 多介质管路 (排水405/供水215/注浆209/注氮208/压风/瓦斯抽采) /
// 电缆·通讯线 (441,442)。
#include "primitives_mine.hh"

#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <TopoDS.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepPrimAPI_MakePrism.hxx>
#include <gp_Ax2.hxx>
#include <gp_Circ.hxx>
#include <cmath>
#include <Precision.hxx>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace flywave {
namespace topo {

namespace {

// 圆断面 (n 段折线)。
std::vector<std::pair<double, double>> mine_circle(double r, int n) {
  std::vector<std::pair<double, double>> pts;
  pts.reserve(n);
  for (int i = 0; i < n; ++i) {
    double a = double(i) / n * 2 * M_PI;
    pts.push_back({r * std::cos(a), r * std::sin(a)});
  }
  return pts;
}

// 圆管沿 3D 路径段挤出链 (平接)。
TopoDS_Shape mine_tube_run(const std::vector<gp_Pnt> &path, double r) {
  auto circ = mine_circle(r, 10);
  TopoDS_Shape acc;
  for (size_t i = 1; i < path.size(); ++i) {
    const gp_Pnt &a = path[i - 1];
    const gp_Pnt &b = path[i];
    gp_Vec seg(a, b);
    double l = seg.Magnitude();
    if (l < Precision::Confusion())
      continue;
    gp_Dir dir(seg);
    TopoDS_Shape s = mine_extrude_profile(a, mine_left_perp(dir), dir, circ, l);
    acc = acc.IsNull() ? s : mine_fuse_two(acc, s);
  }
  if (acc.IsNull())
    throw Standard_ConstructionError("tube run produced no geometry");
  return acc;
}

} // namespace

// 管路: 圆管沿路径 + 托架环 (bracketSpacing>0, 环形箍)。
TopoDS_Shape create_mine_pipe_run(const mine_pipe_run_params &params) {
  if (params.diameter <= 0 || params.diameter > 1)
    throw Standard_ConstructionError("pipe diameter out of (0,1]");
  if (params.path.size() < 2)
    throw Standard_ConstructionError("pipe path needs >= 2 points");
  if (params.bracketSpacing < 0)
    throw Standard_ConstructionError("bracket spacing non-negative");

  TopoDS_Shape acc = mine_tube_run(params.path, params.diameter / 2);
  if (params.bracketSpacing <= 0)
    return acc;

  // 托架环: 圆环箍 (外圈 r+t, 内圈 r) 短棱柱 — 用环形 wire 带孔面
  double r = params.diameter / 2;
  double t = 0.02;
  std::vector<std::pair<double, double>> ringOut, ringIn;
  for (int i = 0; i < 16; ++i) {
    double a = double(i) / 16 * 2 * M_PI;
    ringOut.push_back({(r + t) * std::cos(a), (r + t) * std::sin(a)});
    ringIn.push_back({r * std::cos(a), r * std::sin(a)});
  }
  std::vector<TopoDS_Shape> parts{acc};
  double mileage = 0;
  int made = 0;
  for (size_t i = 1; i < params.path.size() && made < 200; ++i) {
    const gp_Pnt &a = params.path[i - 1];
    const gp_Pnt &b = params.path[i];
    gp_Vec seg(a, b);
    double l = seg.Magnitude();
    if (l < Precision::Confusion())
      continue;
    gp_Dir dir(seg);
    for (double d = params.bracketSpacing -
                    std::fmod(mileage, params.bracketSpacing);
         d <= l && made < 200; d += params.bracketSpacing) {
      gp_Pnt c = a.Translated(gp_Vec(dir) * d);
      TopoDS_Wire out =
          mine_wire_on_plane(c, mine_left_perp(dir), dir, ringOut);
      TopoDS_Wire in =
          mine_wire_on_plane(c, mine_left_perp(dir), dir, ringIn);
      gp_Pln pln(c, dir);
      BRepBuilderAPI_MakeFace mkFace(pln, out);
      if (!mkFace.IsDone())
        continue;
      mkFace.Add(TopoDS::Wire(in.Reversed()));
      if (!mkFace.IsDone())
        continue;
      gp_Vec ex(dir);
      ex.Scale(t);
      BRepPrimAPI_MakePrism ring(mkFace.Face(), ex);
      if (ring.IsDone()) {
        parts.push_back(ring.Shape());
        ++made;
      }
    }
    mileage += l;
  }
  return mine_compound_all(parts);
}

// 三通/弯通管件: 主管段 + 支管段 (夹角) Union。
TopoDS_Shape create_mine_pipe_fitting(const mine_pipe_fitting_params &params) {
  if (params.diameter <= 0 || params.diameter > 1)
    throw Standard_ConstructionError("fitting diameter out of (0,1]");
  if (params.mainLength <= 0 || params.branchLength <= 0)
    throw Standard_ConstructionError("fitting lengths positive");
  if (params.branchAngleDeg <= 0 || params.branchAngleDeg >= 180)
    throw Standard_ConstructionError("branch angle must be in (0,180) degrees");
  gp_Vec axv(params.mainAxis);
  if (axv.Magnitude() < Precision::Confusion())
    throw Standard_ConstructionError("fitting axis degenerate");
  gp_Dir mainAx(axv);
  double r = params.diameter / 2;

  gp_Pnt m0 = params.center.Translated(gp_Vec(mainAx) * (-params.mainLength / 2));
  TopoDS_Shape acc = mine_cylinder_from(m0, mainAx, r, params.mainLength);

  gp_Trsf rot;
  rot.SetRotation(gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)),
                  params.branchAngleDeg * M_PI / 180.0);
  gp_Dir branchAx = gp_Dir(gp_Vec(mainAx).Transformed(rot));
  gp_Pnt b0 = params.center.Translated(gp_Vec(branchAx) * (-params.branchLength / 2));
  TopoDS_Shape branch = mine_cylinder_from(b0, branchAx, r, params.branchLength);
  return mine_fuse_two(acc, branch);
}

// 电缆/通讯线: lines 根并行细缆 (横向间距 = 直径×1.2)。
TopoDS_Shape create_mine_cable_run(const mine_cable_run_params &params) {
  if (params.diameter <= 0 || params.diameter > 0.2)
    throw Standard_ConstructionError("cable diameter out of (0,0.2]");
  if (params.lines <= 0 || params.lines > 6)
    throw Standard_ConstructionError("lines out of [1,6]");
  if (params.path.size() < 2)
    throw Standard_ConstructionError("cable path needs >= 2 points");

  std::vector<TopoDS_Shape> parts;
  for (int i = 0; i < params.lines; ++i) {
    double off =
        (double(i) - double(params.lines - 1) / 2) * params.diameter * 1.2;
    std::vector<gp_Pnt> line;
    line.reserve(params.path.size());
    for (size_t k = 0; k < params.path.size(); ++k) {
      gp_Vec d;
      if (k + 1 < params.path.size())
        d = gp_Vec(params.path[k], params.path[k + 1]);
      else
        d = gp_Vec(params.path[k - 1], params.path[k]);
      double l = d.Magnitude();
      if (l < Precision::Confusion()) {
        line.push_back(params.path[k]);
        continue;
      }
      d.Normalize();
      line.push_back(params.path[k].Translated(
          gp_Vec(d.Y(), -d.X(), 0) * off)); // 右法向 × off
    }
    parts.push_back(mine_tube_run(line, params.diameter / 2));
  }
  return mine_compound_all(parts);
}

} // namespace topo
} // namespace flywave
