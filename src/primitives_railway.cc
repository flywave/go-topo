#include "primitives_railway.hh"

#include <BRepAlgoAPI_Common.hxx>
#include <BRepAlgoAPI_Cut.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepBndLib.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_MakePolygon.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_Transform.hxx>
#include <BRepFilletAPI_MakeFillet.hxx>
#include <BRepLib_MakeFace.hxx>
#include <BRepOffsetAPI_MakePipe.hxx>
#include <BRepOffsetAPI_MakePipeShell.hxx>
#include <BRepOffsetAPI_ThruSections.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeCone.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepPrimAPI_MakePrism.hxx>
#include <BRepPrimAPI_MakeRevol.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>
#include <BRepPrimAPI_MakeTorus.hxx>
#include <BRepTools.hxx>
#include <BRep_Tool.hxx>
#include <Bnd_Box.hxx>
#include <GC_MakeArcOfCircle.hxx>
#include <GC_MakeSegment.hxx>
#include <GCPnts_AbscissaPoint.hxx>
#include <GeomAdaptor_Curve.hxx>
#include <Geom_BezierCurve.hxx>
#include <Geom_BSplineCurve.hxx>
#include <Geom_Circle.hxx>
#include <Geom_Ellipse.hxx>
#include <Geom_Plane.hxx>
#include <GeomAPI_Interpolate.hxx>
#include <Precision.hxx>
#include <ShapeFix_Wire.hxx>
#include <Standard_ConstructionError.hxx>
#include <TColgp_Array1OfPnt.hxx>
#include <TColgp_HArray1OfPnt.hxx>
#include <TopExp.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Wire.hxx>
#include <cmath>
#include <iostream>
#include <gp_Ax2.hxx>
#include <gp_Ax3.hxx>
#include <gp_Circ.hxx>
#include <gp_Dir.hxx>
#include <gp_Pnt.hxx>
#include <gp_Trsf.hxx>
#include <gp_Vec.hxx>

#include <cmath>

namespace flywave {
namespace topo {

// 部件级构建失败的告警日志 (装配函数吞异常时至少能在控制台看到缺件原因)
static void warn_part_failed(const char *func, const char *part) {
  std::cerr << "[primitives_railway] warning: " << func
            << ": failed to build part '" << part << "', skipped" << std::endl;
}

// =========================================================================
// 纯计算函数: 从中心线+高层参数推算各支柱全部位姿
// =========================================================================
OcsSpanCalcOutput calc_ocs_span_positions(const OcsSpanCalcInput &input) {
  OcsSpanCalcOutput out;
  if (input.centerline.size() < 2 || input.spanLength <= 0)
    return out;

  double CH = input.contactHeight > 0 ? input.contactHeight : 5300.0;
  double SH = input.structureHeight > 0 ? input.structureHeight : 1400.0;
  double spanLen = input.spanLength > 0 ? input.spanLength : 50000.0;
  double MH = input.mastHeight > 0 ? input.mastHeight : 8000.0;
  double beamBottomZ = CH + SH;          // 横梁底部高度 = 导高 + 结构高度
  double cantileverSystemMargin = 800.0; // 腕臂系统最小占用高度

  out.contactWireZ = CH;
  out.messengerWireZ = CH + SH;
  out.beamBottomZ = beamBottomZ;

  // 校验高度约束
  if (MH < beamBottomZ + cantileverSystemMargin) {
    out.totalLength = 0;
    out.mastCount = 0;
    return out; // 柱高不足
  }

  // 沿中心线计算总弧长
  double totalLen = 0;
  std::vector<double> segLens;
  for (size_t i = 0; i < input.centerline.size() - 1; ++i) {
    double d = input.centerline[i].Distance(input.centerline[i + 1]);
    segLens.push_back(d);
    totalLen += d;
  }
  out.totalLength = totalLen;
  out.mastCount = std::max(2, (int)(totalLen / spanLen) + 1);

  // 沿中心线等距采样柱位
  double mastSpacing = totalLen / (out.mastCount - 1);
  int staggerCount = (int)input.staggerTable.size();

  for (int m = 0; m < out.mastCount; ++m) {
    double dist = m * mastSpacing;
    // 插值获取柱位坐标
    gp_Pnt pos;
    double acc = 0;
    for (size_t j = 0; j < segLens.size(); ++j) {
      if (acc + segLens[j] >= dist || j == segLens.size() - 1) {
        double t = segLens[j] > 0 ? (dist - acc) / segLens[j] : 0;
        pos = input.centerline[j].Translated(
            gp_Vec(input.centerline[j + 1].XYZ() - input.centerline[j].XYZ()) *
            t);
        break;
      }
      acc += segLens[j];
    }

    OcsMastPosition mp;
    mp.mileage = dist / 1000.0; // m
    mp.position = pos;
    mp.mastHeight = MH;
    mp.beamBottomZ = beamBottomZ;
    mp.contactWireZ = CH;
    mp.messengerWireZ = CH + SH;
    mp.stagger = (m < staggerCount) ? input.staggerTable[m] : 0;
    mp.hangerPostLength = MH - beamBottomZ - cantileverSystemMargin * 0.5;
    mp.bracketMountZ = beamBottomZ - 100;        // 腕臂底座低于横梁底部
    mp.insulatorMountZ = mp.bracketMountZ - 500; // 绝缘子 500mm
    mp.registrationArmZ = CH;                    // 定位器在接触线高度
    mp.isTensionMast =
        (input.hasCompensator && (m == 0 || m == out.mastCount - 1));
    out.masts.push_back(mp);
  }

  return out;
}

// =========================================================================
// OCCT Geometry Implementations
// =========================================================================
// =========================================================================
TopoDS_Shape create_contact_wire(const contact_wire_params &params,
                                 const gp_Pnt &startPoint,
                                 const gp_Pnt &endPoint) {
  if (params.diameter <= 0)
    throw Standard_ConstructionError("Diameter must be positive");
  if (params.bottomRadius <= 0)
    throw Standard_ConstructionError("Bottom radius must be positive");

  const double R = params.diameter / 2.0;
  const double h = params.diameter * 0.98;  // 截面总高 ≈ 直径 (CTHA 系列近圆形)
  const double gD = params.grooveDepth > 0 ? params.grooveDepth : 2.0;
  const double gW = params.grooveWidth > 0 ? params.grooveWidth : 3.0;
  const double bR = params.bottomRadius > 0 ? params.bottomRadius : R * 0.6;
  const double tR = params.topRadius > 0 ? params.topRadius : 3.0;

  // Profile in YZ plane (extruded along X). Y=horizontal, Z=vertical.
  // Going clockwise starting from bottom-left.
  //
  //   p6(-sh,h)╭──────────╮p5(sh,h)   ← top arc (clamping area)
  //            │          │
  //   p7(-sh, ├──────────┤p4(sh, shZ) ← shoulder
  //     shZ)  │  ┌────┐  │
  // p8(-R+gD, ├──┤    ├──┤p3(R-gD, gW/2) ← groove top
  //   gW/2)   │  │    │  │
  //           │  │    │  │              ← groove
  // p9(-R+gD, ├──┤    ├──┤p2(R-gD, -gW/2) ← groove bottom
  //  -gW/2)   │  └────┘  │
  //           │          │
  //    p10(-R,0)╲      ╱p1(R,0)         ← bottom-left / bottom-right
  //              ╲    ╱
  //               ╲  ╱
  //           pMid(0,-sag)              ← bottom arc midpoint

  double sh = R * 0.85;  // shoulder half-width (slightly narrower than full width)
  double sag = (R * R) / (2.0 * bR);  // parabolic sagitta for bottom arc

  // Define profile points (all X=0), clockwise from bottom-left
  // 沟槽位于截面上部靠近夹持肩 (真实 CTHA 截面特征)
  const double shZ = h * 0.80;                  // 肩部高度
  const double zG = shZ - gW * 1.2;             // 沟槽中心高度
  gp_Pnt p10(0, -R, 0);                   // bottom-left
  gp_Pnt pMid(0, 0, -sag);                // bottom arc midpoint (convex downward)
  gp_Pnt p1(0, R, 0);                     // bottom-right
  gp_Pnt p2(0, R - gD, zG - gW / 2);      // right groove bottom
  gp_Pnt p3(0, R - gD, zG + gW / 2);      // right groove top
  gp_Pnt p4(0, sh, shZ);                  // right shoulder
  gp_Pnt p5(0, sh, h);                    // right top arc start
  gp_Pnt p6(0, -sh, h);                   // left top arc end
  gp_Pnt p7(0, -sh, shZ);                 // left shoulder
  gp_Pnt p8(0, -R + gD, zG + gW / 2);     // left groove top
  gp_Pnt p9(0, -R + gD, zG - gW / 2);     // left groove bottom

  // Bottom arc: 3-point arc through p10(-R,0), pMid(0,-sag), p1(R,0)
  Handle(Geom_TrimmedCurve) bottomArcCurve =
      GC_MakeArcOfCircle(p10, pMid, p1).Value();
  TopoDS_Edge bottomArcEdge = BRepBuilderAPI_MakeEdge(bottomArcCurve).Edge();

  // Right side (bottom to top)
  TopoDS_Edge e1 = BRepBuilderAPI_MakeEdge(p1, p2).Edge();
  TopoDS_Edge e2 = BRepBuilderAPI_MakeEdge(p2, p3).Edge();
  TopoDS_Edge e3 = BRepBuilderAPI_MakeEdge(p3, p4).Edge();
  TopoDS_Edge e4 = BRepBuilderAPI_MakeEdge(p4, p5).Edge();

  // Top arc: 3-point arc through p5(sh,h), pTop(0,h+topping), p6(-sh,h)
  // to create rounded clamping area (convex outward)
  double topping = std::min(tR, sh * 0.9);
  gp_Pnt pTop(0, 0, h + topping);
  Handle(Geom_TrimmedCurve) topArcCurve =
      GC_MakeArcOfCircle(p5, pTop, p6).Value();
  TopoDS_Edge topArcEdge = BRepBuilderAPI_MakeEdge(topArcCurve).Edge();

  // Left side (top to bottom)
  TopoDS_Edge e5 = BRepBuilderAPI_MakeEdge(p6, p7).Edge();
  TopoDS_Edge e6 = BRepBuilderAPI_MakeEdge(p7, p8).Edge();
  TopoDS_Edge e7 = BRepBuilderAPI_MakeEdge(p8, p9).Edge();
  TopoDS_Edge e8 = BRepBuilderAPI_MakeEdge(p9, p10).Edge();

  BRepBuilderAPI_MakeWire wireMaker;
  wireMaker.Add(bottomArcEdge);
  wireMaker.Add(e1);
  wireMaker.Add(e2);
  wireMaker.Add(e3);
  wireMaker.Add(e4);
  wireMaker.Add(topArcEdge);
  wireMaker.Add(e5);
  wireMaker.Add(e6);
  wireMaker.Add(e7);
  wireMaker.Add(e8);
  TopoDS_Wire profileWire = wireMaker.Wire();

  gp_Vec spanVec(startPoint, endPoint);
  double span = spanVec.Magnitude();
  if (span <= Precision::Confusion())
    return TopoDS_Shape();

  double sagVal = params.sag > 0 ? params.sag : span * 0.01;

  if (sagVal <= Precision::Confusion()) {
    TopoDS_Face profileFace = BRepBuilderAPI_MakeFace(profileWire).Face();
    return BRepPrimAPI_MakePrism(profileFace, spanVec).Shape();
  }

  // Build parabolic centerline: 3-point Bezier with sag at mid-span
  gp_Pnt mid((startPoint.X() + endPoint.X()) / 2.0,
             (startPoint.Y() + endPoint.Y()) / 2.0,
             (startPoint.Z() + endPoint.Z()) / 2.0);
  mid.Translate(gp_Vec(0, 0, -sagVal));

  BRepBuilderAPI_MakeWire pathBuilder;
  Handle(TColgp_HArray1OfPnt) poles = new TColgp_HArray1OfPnt(1, 3);
  poles->SetValue(1, startPoint);
  poles->SetValue(2, mid);
  poles->SetValue(3, endPoint);
  Handle(Geom_BezierCurve) bezier = new Geom_BezierCurve(poles->Array1());
  pathBuilder.Add(BRepBuilderAPI_MakeEdge(bezier));
  TopoDS_Wire pathWire = pathBuilder.Wire();

  // Position profile in plane perpendicular to path start direction
  gp_Pnt startP; gp_Vec startV; bezier->D1(0, startP, startV);
  if (startV.Magnitude() <= Precision::Confusion())
    startV = spanVec;
  gp_Dir startDir = gp_Dir(startV);

  // Build profile wire and position at startPoint with normal along startDir
  // Profile is in YZ plane (X=0), normal = (1,0,0)
  // We need to rotate so normal aligns with startDir and translate to startPoint
  BRepBuilderAPI_MakeWire profileWiz;
  profileWiz.Add(bottomArcEdge);
  profileWiz.Add(e1);
  profileWiz.Add(e2);
  profileWiz.Add(e3);
  profileWiz.Add(e4);
  profileWiz.Add(topArcEdge);
  profileWiz.Add(e5);
  profileWiz.Add(e6);
  profileWiz.Add(e7);
  profileWiz.Add(e8);
  TopoDS_Wire pw = profileWiz.Wire();

  // Build destination frame: 路径切向 → 局部 X (断面法向), 竖直 → 局部 Z
  gp_Ax3 srcAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 tgtAx3(startPoint, gp::DZ(), startDir);
  gp_Trsf trsf;
  trsf.SetTransformation(tgtAx3, srcAx3);
  BRepBuilderAPI_Transform xf(pw, trsf);
  TopoDS_Wire positioned = TopoDS::Wire(xf.Shape());

  // Sweep along the parabolic path
  BRepOffsetAPI_MakePipeShell pipe(pathWire);
  pipe.Add(positioned);
  pipe.SetMode(Standard_True);
  pipe.Build();
  if (pipe.IsDone() && pipe.MakeSolid())
    return pipe.Shape();

  // Fallback: straight extrusion
  TopoDS_Face profileFace = BRepBuilderAPI_MakeFace(profileWire).Face();
  return BRepPrimAPI_MakePrism(profileFace, spanVec).Shape();
}

// =========================================================================
// 2. Messenger Wire (承力索)
// =========================================================================
TopoDS_Shape create_messenger_wire(const messenger_wire_params &params,
                                   const gp_Pnt &startPoint,
                                   const gp_Pnt &endPoint) {
  if (params.diameter <= 0)
    throw Standard_ConstructionError("Diameter must be positive");

  double radius = params.diameter / 2.0;
  gp_Vec spanVec(startPoint, endPoint);
  double span = spanVec.Magnitude();
  if (span <= Precision::Confusion())
    return BRepPrimAPI_MakeCylinder(gp_Ax2(startPoint, gp::DX()), radius, 1)
        .Shape();

  // Build parabolic centerline: 3-point Bezier with sag at mid-span
  // 缺省弛度: 跨距的 1.5%
  double sag = params.sag > 0 ? params.sag : span * 0.015;
  gp_Pnt mid((startPoint.X() + endPoint.X()) / 2.0,
             (startPoint.Y() + endPoint.Y()) / 2.0,
             (startPoint.Z() + endPoint.Z()) / 2.0);
  mid.Translate(gp_Vec(0, 0, -sag));

  BRepBuilderAPI_MakeWire wireBuilder;
  Handle(TColgp_HArray1OfPnt) poles = new TColgp_HArray1OfPnt(1, 3);
  poles->SetValue(1, startPoint);
  poles->SetValue(2, mid);
  poles->SetValue(3, endPoint);
  Handle(Geom_BezierCurve) bezier = new Geom_BezierCurve(poles->Array1());
  wireBuilder.Add(BRepBuilderAPI_MakeEdge(bezier));
  TopoDS_Wire pathWire = wireBuilder.Wire();

  // Circular profile in plane perpendicular to path start direction
  gp_Pnt startP; gp_Vec startV; bezier->D1(0, startP, startV);
  gp_Dir startDir = gp_Dir(startV);
  gp_Ax2 profileAxis(startPoint, startDir);
  gp_Circ sectionCircle(profileAxis, radius);
  TopoDS_Edge sectionEdge = BRepBuilderAPI_MakeEdge(sectionCircle).Edge();
  TopoDS_Wire sectionWire = BRepBuilderAPI_MakeWire(sectionEdge).Wire();

  // Sweep along the parabolic path
  BRepOffsetAPI_MakePipeShell pipe(pathWire);
  pipe.Add(sectionWire);
  pipe.SetMode(Standard_True);
  pipe.Build();
  if (pipe.IsDone() && pipe.MakeSolid())
    return pipe.Shape();

  // Fallback: straight cylinder
  return BRepPrimAPI_MakeCylinder(gp_Ax2(startPoint, gp_Dir(spanVec)), radius,
                                  span)
      .Shape();
}

// =========================================================================
// 3. Cross Arm (横担)
// =========================================================================
TopoDS_Shape create_cross_arm(const cross_arm_params &params) {
  if (params.beamLength <= 0 || params.beamHeight <= 0 || params.beamWidth <= 0)
    throw Standard_ConstructionError("Beam dimensions must be positive");

  BRep_Builder builder;
  TopoDS_Compound compound;
  builder.MakeCompound(compound);

  double BL = params.beamLength, BH = params.beamHeight, BW = params.beamWidth;
  double gap = params.beamSpacing > 0 ? params.beamSpacing : BH * 3;

  // 几何中心居中：X 偏移 -BW/2, Z 偏移 -(gap+BH)/2
  double xOff = -BW / 2.0;
  double zOff = -(gap + BH) / 2.0;

  // Upper beam — along Y, Z range: [gap/2, gap/2+BH]
  gp_Pnt ubOrg(xOff, -BL / 2, zOff + gap + BH / 2);
  TopoDS_Shape upperBeam = BRepPrimAPI_MakeBox(ubOrg, BW, BL, BH).Shape();
  builder.Add(compound, upperBeam);

  // Lower beam — Z range: [-gap/2-BH, -gap/2]
  gp_Pnt lbOrg(xOff, -BL / 2, zOff - BH / 2);
  TopoDS_Shape lowerBeam = BRepPrimAPI_MakeBox(lbOrg, BW, BL, BH).Shape();
  builder.Add(compound, lowerBeam);

  // Two diagonal braces — cross at center
  double braceR = BW * 0.25;
  for (int side = -1; side <= 1; side += 2) {
    gp_Pnt p1(0, side * BL * 0.45, zOff + gap + BH);
    gp_Pnt p2(0, -side * BL * 0.45, zOff);
    gp_Vec v(p1, p2);
    double l = v.Magnitude();
    if (l > Precision::Confusion())
      builder.Add(
          compound,
          BRepPrimAPI_MakeCylinder(gp_Ax2(p1, gp_Dir(v)), braceR, l).Shape());
  }

  // Bolt holes in beams for mast connection at center
  if (params.boltDiameter > 0) {
    double hr = params.boltDiameter / 2, hs = params.boltSpacing / 2;
    for (int level = 0; level < 2; ++level) {
      double zCenter = (level == 0) ? zOff : zOff + gap + BH;
      for (int bx = -1; bx <= 1; bx += 2)
        if (params.boltCount >= 3 || bx == 0)
          for (int by = -1; by <= 1; by += 2) {
            TopoDS_Shape h =
                BRepPrimAPI_MakeCylinder(
                    gp_Ax2(gp_Pnt(bx * hs, by * hs, zCenter - BW / 2 - 1), gp::DY()),
                    hr, BW + 2)
                    .Shape();
            lowerBeam = BRepAlgoAPI_Cut(lowerBeam, h).Shape();
            upperBeam = BRepAlgoAPI_Cut(upperBeam, h).Shape();
          }
    }
  }

  return compound;
}

TopoDS_Shape create_cross_arm(const cross_arm_params &params,
                              const gp_Pnt &position, const gp_Dir &normal,
                              const gp_Dir &xDir) {
  TopoDS_Shape shape = create_cross_arm(params);

  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, normal, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  return BRepBuilderAPI_Transform(shape, transformation).Shape();
}

// =========================================================================
// 4. Level Cantilever (平腕臂)
// =========================================================================
TopoDS_Shape create_level_cantilever(const level_cantilever_params &params) {
  if (params.length <= 0 || params.outerDiameter <= 0)
    throw Standard_ConstructionError("Length and diameter must be positive");
  if (params.wallThickness <= 0 ||
      params.wallThickness >= params.outerDiameter / 2)
    throw Standard_ConstructionError("Invalid wall thickness");

  double innerRadius = params.outerDiameter / 2 - params.wallThickness;
  double outerRadius = params.outerDiameter / 2;

  // Outer cylinder along X axis
  gp_Ax2 outerAxis(gp::Origin(), gp::DX());
  TopoDS_Shape outerCyl =
      BRepPrimAPI_MakeCylinder(outerAxis, outerRadius, params.length).Shape();

  // Inner cylinder (to be subtracted)
  gp_Ax2 innerAxis(gp::Origin(), gp::DX());
  TopoDS_Shape innerCyl =
      BRepPrimAPI_MakeCylinder(innerAxis, innerRadius, params.length).Shape();

  // Thin-walled tube
  TopoDS_Shape tube = BRepAlgoAPI_Cut(outerCyl, innerCyl).Shape();

  // Apply rise angle rotation
  if (std::abs(params.riseAngle) > Precision::Angular()) {
    double angleRad = params.riseAngle * M_PI / 180.0;
    gp_Trsf rot;
    rot.SetRotation(gp_Ax1(gp::Origin(), gp::DY()), angleRad);
    return BRepBuilderAPI_Transform(tube, rot).Shape();
  }

  return tube;
}

TopoDS_Shape create_level_cantilever(const level_cantilever_params &params,
                                     const gp_Pnt &basePoint,
                                     const gp_Dir &axisDirection,
                                     const gp_Dir &upDir) {
  TopoDS_Shape shape = create_level_cantilever(params);

  gp_Dir yDir = upDir.Crossed(axisDirection);
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(basePoint, upDir, axisDirection);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  return BRepBuilderAPI_Transform(shape, transformation).Shape();
}

// =========================================================================
// 5. Slanted Cantilever (斜腕臂)
// =========================================================================
TopoDS_Shape create_slant_cantilever(const slant_cantilever_params &params) {
  if (params.length <= 0 || params.outerDiameter <= 0)
    throw Standard_ConstructionError("Length and diameter must be positive");
  if (params.wallThickness <= 0 ||
      params.wallThickness >= params.outerDiameter / 2)
    throw Standard_ConstructionError("Invalid wall thickness");

  double innerRadius = params.outerDiameter / 2 - params.wallThickness;
  double outerRadius = params.outerDiameter / 2;

  // Create tube along X axis，再绕 Y 旋转实现 +X → -Z 方向倾斜
  gp_Ax2 outerAxis(gp::Origin(), gp::DX());
  TopoDS_Shape outerCyl =
      BRepPrimAPI_MakeCylinder(outerAxis, outerRadius, params.length).Shape();

  gp_Ax2 innerAxis(gp::Origin(), gp::DX());
  TopoDS_Shape innerCyl =
      BRepPrimAPI_MakeCylinder(innerAxis, innerRadius, params.length).Shape();

  TopoDS_Shape tube = BRepAlgoAPI_Cut(outerCyl, innerCyl).Shape();

  // 绕 Y 旋转：+X 方向向 +Z 方向倾斜
  double angleRad = params.slantAngle * M_PI / 180.0;
  gp_Trsf rot;
  rot.SetRotation(gp_Ax1(gp::Origin(), gp::DY()), -angleRad);
  return BRepBuilderAPI_Transform(tube, rot).Shape();
}

TopoDS_Shape create_slant_cantilever(const slant_cantilever_params &params,
                                     const gp_Pnt &basePoint,
                                     const gp_Dir &axisDirection,
                                     const gp_Dir &upDir) {
  TopoDS_Shape shape = create_slant_cantilever(params);

  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(basePoint, upDir, axisDirection);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  return BRepBuilderAPI_Transform(shape, transformation).Shape();
}

// =========================================================================
// 6a. Cantilever Brace (斜撑)
// =========================================================================
TopoDS_Shape create_cantilever_brace(const cantilever_brace_params &params) {
  if (params.length <= 0 || params.outerDiameter <= 0)
    throw Standard_ConstructionError("Length and diameter must be positive");
  if (params.wallThickness <= 0 ||
      params.wallThickness >= params.outerDiameter / 2)
    throw Standard_ConstructionError("Invalid wall thickness");

  double innerRadius = params.outerDiameter / 2 - params.wallThickness;
  double outerRadius = params.outerDiameter / 2;

  // Create tube along X axis，绕 Y 旋转向 +X → -Z 方向倾斜
  gp_Ax2 outerAxis(gp::Origin(), gp::DX());
  TopoDS_Shape outerCyl =
      BRepPrimAPI_MakeCylinder(outerAxis, outerRadius, params.length).Shape();

  gp_Ax2 innerAxis(gp::Origin(), gp::DX());
  TopoDS_Shape innerCyl =
      BRepPrimAPI_MakeCylinder(innerAxis, innerRadius, params.length).Shape();

  TopoDS_Shape tube = BRepAlgoAPI_Cut(outerCyl, innerCyl).Shape();

  // 绕 Y 旋转：+X 方向向 -Z 方向倾斜
  double angleRad = params.slantAngle * M_PI / 180.0;
  gp_Trsf rot;
  rot.SetRotation(gp_Ax1(gp::Origin(), gp::DY()), angleRad);
  return BRepBuilderAPI_Transform(tube, rot).Shape();
}

TopoDS_Shape create_cantilever_brace(const cantilever_brace_params &params,
                                     const gp_Pnt &basePoint,
                                     const gp_Dir &axisDirection,
                                     const gp_Dir &upDir) {
  TopoDS_Shape shape = create_cantilever_brace(params);

  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(basePoint, upDir, axisDirection);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  return BRepBuilderAPI_Transform(shape, transformation).Shape();
}

// =========================================================================
// 6. Curved Arm (弯臂)
// =========================================================================
TopoDS_Shape create_curved_arm(const curved_arm_params &params) {
  if (params.verticalLength <= 0 || params.horizontalLength <= 0)
    throw Standard_ConstructionError("Lengths must be positive");
  if (params.outerDiameter <= 0)
    throw Standard_ConstructionError("Outer diameter must be positive");

  double tubeRadius = params.outerDiameter / 2;
  double R =
      params.bendRadius > 0
          ? params.bendRadius
          : std::min(params.verticalLength, params.horizontalLength) * 0.3;
  double V = params.verticalLength;
  double H = params.horizontalLength;

  if (R > V || R > H)
    R = std::min(V, H) * 0.5;

  // Build centerline path using 3-point Bezier (平滑过渡): 
  // vStart → arcStart (中点) → hEnd (终点)
  gp_Pnt vStart(0, 0, 0);
  gp_Pnt midPnt(V - R, 0, V - R); // 中间控制点保证切线连续
  gp_Pnt hEnd(H, 0, V);

  Handle(TColgp_HArray1OfPnt) poles = new TColgp_HArray1OfPnt(1, 3);
  poles->SetValue(1, vStart);
  poles->SetValue(2, midPnt);
  poles->SetValue(3, hEnd);
  Handle(Geom_BezierCurve) bezier = new Geom_BezierCurve(poles->Array1());

  BRepBuilderAPI_MakeWire pathMaker;
  pathMaker.Add(BRepBuilderAPI_MakeEdge(bezier));
  TopoDS_Wire pathWire = pathMaker.Wire();

  // Circular cross-section at path start
  gp_Ax2 sectionAxes(vStart, gp_Dir(0, 0, 1));
  gp_Circ sectionCircle(sectionAxes, tubeRadius);
  TopoDS_Edge sectionEdge = BRepBuilderAPI_MakeEdge(sectionCircle).Edge();
  TopoDS_Wire sectionWire = BRepBuilderAPI_MakeWire(sectionEdge).Wire();

  // Sweep along path
  BRepOffsetAPI_MakePipeShell pipeMaker(pathWire);
  pipeMaker.Add(sectionWire);
  pipeMaker.SetMode(Standard_True);
  pipeMaker.Build();

  if (!pipeMaker.IsDone())
    throw Standard_ConstructionError("Curved arm pipe generation failed");
  if (!pipeMaker.MakeSolid())
    throw Standard_ConstructionError("Failed to create solid curved arm");

  TopoDS_Shape arm = pipeMaker.Shape();

  // Add mounting flange at base (向上延伸 1mm 与管道重叠，避免共面融合失败)
  double zOffset = 0;
  if (params.flangeThickness > 0) {
    double flangeSize = params.outerDiameter * 2;
    double flangeOverlap = 1.0;
    gp_Pnt flangeOrigin(-flangeSize / 2, -flangeSize / 2,
                        -params.flangeThickness);
    TopoDS_Shape flange =
        BRepPrimAPI_MakeBox(flangeOrigin, flangeSize, flangeSize,
                            params.flangeThickness + flangeOverlap)
            .Shape();
    arm = BRepAlgoAPI_Fuse(arm, flange).Shape();
    zOffset = params.flangeThickness;
  }

  // 将原点移动到法兰底面中心（安装面）
  if (zOffset > Precision::Confusion()) {
    gp_Trsf shift;
    shift.SetTranslation(gp_Vec(0, 0, zOffset));
    arm = BRepBuilderAPI_Transform(arm, shift).Shape();
  }

  return arm;
}

TopoDS_Shape create_curved_arm(const curved_arm_params &params,
                               const gp_Pnt &position, const gp_Dir &normal,
                               const gp_Dir &xDir) {
  TopoDS_Shape shape = create_curved_arm(params);

  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, normal, xDir);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  return BRepBuilderAPI_Transform(shape, transformation).Shape();
}

// =========================================================================
// 7. Rod Insulator (棒式绝缘子)
// =========================================================================
TopoDS_Shape create_rod_insulator(const rod_insulator_params &params) {
  if (params.height <= 0 || params.outerDiameter <= 0)
    throw Standard_ConstructionError("Height and diameter must be positive");
  if (params.shedDiameter < params.outerDiameter)
    throw Standard_ConstructionError("Shed diameter must be >= outer diameter");
  if (params.shedCount < 0)
    throw Standard_ConstructionError("Shed count must be non-negative");

  double rodRadius = params.outerDiameter / 2.0;
  double shedMajorR = params.shedDiameter / 2.0;
  double shedMinorR = shedMajorR * 0.85;
  double innerR = params.innerDiameter / 2.0;

  // 计算偏移量：使原点位于最底面（法兰底面或棒体底面）
  double flangeH = 0;
  bool hasFlange = (params.endFitting == end_fitting_type::FLANGE &&
                    params.flangeDiameter > rodRadius * 2);
  if (hasFlange) {
    flangeH = params.height * 0.05;
  }
  double zOffset = hasFlange ? flangeH : 0;

  // Main rod body — hollow if innerDiameter > 0
  gp_Ax2 rodAxis(gp_Pnt(0, 0, zOffset), gp::DZ());
  TopoDS_Shape rod;
  if (innerR > Precision::Confusion() && innerR < rodRadius) {
    TopoDS_Shape outerCyl =
        BRepPrimAPI_MakeCylinder(rodAxis, rodRadius, params.height).Shape();
    TopoDS_Shape innerCyl =
        BRepPrimAPI_MakeCylinder(rodAxis, innerR, params.height).Shape();
    rod = BRepAlgoAPI_Cut(outerCyl, innerCyl).Shape();
  } else {
    rod = BRepPrimAPI_MakeCylinder(rodAxis, rodRadius, params.height).Shape();
  }

  if (params.shedCount == 0 && !hasFlange)
    return rod;

  // Build compound: body + all shed rings
  BRep_Builder builder;
  TopoDS_Compound compound;
  builder.MakeCompound(compound);
  builder.Add(compound, rod);

  double shedSpacing = params.shedSpacing > 0
                           ? params.shedSpacing
                           : params.height / (params.shedCount + 1);
  double segH = shedSpacing;

  for (int i = 0; i < params.shedCount; ++i) {
    double zPos = zOffset + (i + 1) * shedSpacing;
    double r = (i % 2 == 0) ? shedMajorR : shedMinorR;

    // 圆弧伞裙截面 (r-z 平面): 下垂底面 → 外缘滴水沿圆角 → 上凸顶面
    gp_Pnt basePt(rodRadius, 0, zPos);
    gp_Pnt u1(r, 0, zPos - segH * 0.06);                 // 底面外缘 (略下垂)
    gp_Pnt u2(r * 1.02, 0, zPos + segH * 0.05);          // 滴水沿
    gp_Pnt u3(r * 0.98, 0, zPos + segH * 0.16);          // 外缘上
    gp_Pnt u4((r + rodRadius) / 2, 0, zPos + segH * 0.28); // 顶面弧中
    gp_Pnt endPt(rodRadius, 0, zPos + segH * 0.22);

    BRepBuilderAPI_MakeWire wire;
    wire.Add(BRepBuilderAPI_MakeEdge(basePt, u1));
    wire.Add(BRepBuilderAPI_MakeEdge(
        GC_MakeArcOfCircle(u1, u2, u3).Value()));       // 外缘圆角
    wire.Add(BRepBuilderAPI_MakeEdge(
        GC_MakeArcOfCircle(u3, u4, endPt).Value()));    // 上凸顶面
    wire.Add(BRepBuilderAPI_MakeEdge(endPt, basePt));

    if (!wire.IsDone())
      throw Standard_ConstructionError("Shed wire not closed");

    TopoDS_Face face = BRepLib_MakeFace(wire.Wire()).Face();
    gp_Pnt revolCenter(0, 0, 0);
    BRepPrimAPI_MakeRevol revol(face, gp_Ax1(revolCenter, gp::DZ()));
    revol.Build();
    TopoDS_Shape shed = revol.Shape();
    if (shed.IsNull())
      throw Standard_ConstructionError("Shed revolution failed");

    builder.Add(compound, shed);
  }

  // End flanges
  if (hasFlange) {
    double flangeR = params.flangeDiameter / 2.0;
    gp_Ax2 botAxis(gp::Origin(), gp::DZ());
    TopoDS_Shape botFlange =
        BRepPrimAPI_MakeCylinder(botAxis, flangeR, flangeH).Shape();
    gp_Ax2 topAxis(gp_Pnt(0, 0, zOffset + params.height), gp::DZ());
    TopoDS_Shape topFlange =
        BRepPrimAPI_MakeCylinder(topAxis, flangeR, flangeH).Shape();

    // 法兰螺栓孔 (分度圆上阵列 4 孔)
    if (params.flangeBoltSpacing > 0 && params.flangeBoltDiameter > 0) {
      double br = params.flangeBoltDiameter / 2.0;
      double bc = params.flangeBoltSpacing / 2.0;
      for (int k = 0; k < 4; ++k) {
        double a = k * M_PI / 2.0 + M_PI / 4.0;
        gp_Pnt hc(bc * std::cos(a), bc * std::sin(a), -1);
        TopoDS_Shape hole = BRepPrimAPI_MakeCylinder(
            gp_Ax2(hc, gp::DZ()), br, zOffset + params.height + flangeH + 2).Shape();
        botFlange = BRepAlgoAPI_Cut(botFlange, hole).Shape();
        topFlange = BRepAlgoAPI_Cut(topFlange, hole).Shape();
      }
    }
    builder.Add(compound, botFlange);
    builder.Add(compound, topFlange);
  }

  // 球头端部: 两端球窝球头
  if (params.endFitting == end_fitting_type::BALL) {
    double ballR = rodRadius * 1.5;
    builder.Add(compound, BRepPrimAPI_MakeSphere(
        gp_Ax2(gp_Pnt(0, 0, zOffset), gp::DZ()), ballR).Shape());
    builder.Add(compound, BRepPrimAPI_MakeSphere(
        gp_Ax2(gp_Pnt(0, 0, zOffset + params.height), gp::DZ()), ballR).Shape());
  }

  // 螺杆端部: 两端螺柱 + 六角螺母
  if (params.endFitting == end_fitting_type::SCREW) {
    double studR = rodRadius * 0.55;
    double studL = params.height * 0.08;
    double nutR = studR * 1.8, nutH = studR * 1.4;
    auto stud = [&](double z0, double z1) {
      double len = z1 - z0;
      builder.Add(compound, BRepPrimAPI_MakeCylinder(
          gp_Ax2(gp_Pnt(0, 0, z0), gp::DZ()), studR, len).Shape());
      BRepBuilderAPI_MakePolygon hex;
      double zn = len > 0 ? z1 - nutH : z0;
      for (int k = 0; k < 6; ++k) {
        double a = k * M_PI / 3.0;
        hex.Add(gp_Pnt(nutR * std::cos(a), nutR * std::sin(a), zn));
      }
      hex.Close();
      builder.Add(compound, BRepPrimAPI_MakePrism(
          BRepLib_MakeFace(hex.Wire()).Face(), gp_Vec(0, 0, nutH)).Shape());
    };
    stud(zOffset - studL, zOffset);                       // 下螺柱
    stud(zOffset + params.height, zOffset + params.height + studL); // 上螺柱
  }

  return compound;
}

TopoDS_Shape create_rod_insulator(const rod_insulator_params &params,
                                  const gp_Pnt &basePoint,
                                  const gp_Dir &axisDirection) {
  TopoDS_Shape shape = create_rod_insulator(params);

  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ());
  gp_Ax3 targetAx3(basePoint, axisDirection);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  return BRepBuilderAPI_Transform(shape, transformation).Shape();
}

// =========================================================================
// 8. Mast Bracket (支柱连接座)
// =========================================================================
TopoDS_Shape create_mast_bracket(const mast_bracket_params &params) {
  if (params.height <= 0 || params.width <= 0 || params.thickness <= 0)
    throw Standard_ConstructionError("Dimensions must be positive");

  // Main plate: centered in X (thickness), centered in Y (width), centered in Z (height)
  gp_Pnt plateOrg(-params.thickness / 2.0, -params.width / 2.0,
                  -params.height / 2.0);
  TopoDS_Shape plate = BRepPrimAPI_MakeBox(plateOrg, params.thickness,
                                           params.width, params.height)
                           .Shape();

  // Mounting bolt holes: 4 holes through plate (along X, from back face to front face)
  if (params.boltDiameter > 0 && params.boltSpacing > 0) {
    double holeR = params.boltDiameter / 2.0;
    double hs = std::min(params.boltSpacing, params.width * 0.7);
    double vs = std::min(hs, params.height * 0.5);
    for (int iz = -1; iz <= 1; iz += 2) {
      for (int iy = -1; iy <= 1; iy += 2) {
        double y = iy * hs / 2.0;
        double z = iz * vs / 2.0;
        gp_Pnt cStart(-params.thickness / 2.0 - 1, y, z);
        TopoDS_Shape hole = BRepPrimAPI_MakeCylinder(
            gp_Ax2(cStart, gp::DX()), holeR, params.thickness + 2).Shape();
        plate = BRepAlgoAPI_Cut(plate, hole).Shape();
      }
    }
  }

  // Insulator ear plates (on front face, X = +thickness/2)
  if (params.insulatorBoltSpacing > 0) {
    double eT = params.thickness * 0.8;
    double eW = params.width * 0.3;
    double eH = params.height * 0.6;
    double eOff = params.thickness / 2.0;
    double eZ = -eH / 2.0;

    // Two ear plates positioned at ±insulatorBoltSpacing/2 in Y
    for (int side = -1; side <= 1; side += 2) {
      double yCenter = side * params.insulatorBoltSpacing / 2.0;
      gp_Pnt earOrg(eOff, yCenter - eW / 2.0, eZ);
      TopoDS_Shape ear = BRepPrimAPI_MakeBox(earOrg, eT, eW, eH).Shape();
      plate = BRepAlgoAPI_Fuse(plate, ear).Shape();

      // Ear pin hole (through ear along Y axis, from -Y side to +Y side)
      if (params.insulatorBoltDiameter > 0) {
        double hr = params.insulatorBoltDiameter / 2.0;
        gp_Pnt holeStart(eOff, yCenter - eW / 2.0 - 1, 0);
        TopoDS_Shape hole = BRepPrimAPI_MakeCylinder(
            gp_Ax2(holeStart, gp::DY()), hr, eW + 2).Shape();
        plate = BRepAlgoAPI_Cut(plate, hole).Shape();
      }
    }
  }

  // 抱箍弧带 (圆管支柱, mastDiameter>0): 半圆环带 + 开口螺栓耳
  if (params.mastDiameter > 0) {
    double rm = params.mastDiameter / 2.0;
    double bt = params.thickness * 0.8;
    double bandH = params.height * 0.5;
    double xc = -params.thickness / 2.0 - rm; // 柱心 X
    // 半圆环带: 外筒减内筒, 再取 -X 半侧
    TopoDS_Shape band = BRepAlgoAPI_Cut(
        BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(xc, 0, -bandH / 2), gp::DZ()),
                                 rm + bt, bandH).Shape(),
        BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(xc, 0, -bandH / 2 - 1), gp::DZ()),
                                 rm, bandH + 2).Shape()).Shape();
    band = BRepAlgoAPI_Common(
        band, BRepPrimAPI_MakeBox(
                  gp_Pnt(xc - rm - bt - 1, -rm - bt - 1, -bandH / 2 - 1),
                  rm + bt + 1, 2 * (rm + bt + 1), bandH + 2).Shape()).Shape();
    // 开口螺栓耳: 带两端 (y=±rm 处) 各一块耳板连接座体, 耳板带横向螺栓孔
    for (int side = -1; side <= 1; side += 2) {
      double ey = side * (rm + bt / 2);
      gp_Pnt earOrg(xc, ey - bt / 2, -bandH / 2);
      TopoDS_Shape ear = BRepPrimAPI_MakeBox(
          earOrg, -xc - params.thickness / 2, bt, bandH).Shape();
      if (params.boltDiameter > 0) {
        double hr = params.boltDiameter / 2.0;
        ear = BRepAlgoAPI_Cut(
            ear, BRepPrimAPI_MakeCylinder(
                     gp_Ax2(gp_Pnt(xc - 1, ey - bt / 2 - 1, 0), gp::DY()), hr,
                     bt + 2).Shape()).Shape();
      }
      band = BRepAlgoAPI_Fuse(band, ear).Shape();
    }
    plate = BRepAlgoAPI_Fuse(plate, band).Shape();
  }

  // Apply mount angle
  if (std::abs(params.mountAngle) > Precision::Angular()) {
    double a = params.mountAngle * M_PI / 180.0;
    gp_Trsf rot;
    rot.SetRotation(
        gp_Ax1(gp_Pnt(0, params.width / 2.0, 0), gp::DY()), a);
    plate = BRepBuilderAPI_Transform(plate, rot).Shape();
  }

  return plate;
}

TopoDS_Shape create_mast_bracket(const mast_bracket_params &params,
                                 const gp_Pnt &position, const gp_Dir &normal,
                                 const gp_Dir &upDir) {
  TopoDS_Shape shape = create_mast_bracket(params);

  gp_Dir yDir = upDir.Crossed(normal);
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, upDir, normal);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  return BRepBuilderAPI_Transform(shape, transformation).Shape();
}

// =========================================================================
// 9. Registration Arm (定位器)
// =========================================================================
TopoDS_Shape create_registration_arm(const registration_arm_params &params) {
  if (params.length <= 0 || params.tubeWidth <= 0)
    throw Standard_ConstructionError("Length and width must be positive");

  double W = params.tubeWidth,
         H = params.tubeHeight > 0 ? params.tubeHeight : W;
  double t = params.wallThickness > 0 ? params.wallThickness : W * 0.15;
  double L = params.length;
  double dir = params.isReverse ? -1.0 : 1.0;

  auto makeTube = [&](gp_Pnt org, gp_Dir axis, double len) -> TopoDS_Shape {
    gp_Pnt outerOrg(org.X() - W / 2, org.Y() - H / 2, org.Z() - W / 2);
    TopoDS_Shape outer = BRepPrimAPI_MakeBox(outerOrg, W, H, W).Shape();
    if (t > 0 && W > 2 * t && H > 2 * t) {
      TopoDS_Shape inner =
          BRepPrimAPI_MakeBox(gp_Pnt(org.X() - W / 2 + t, org.Y() - H / 2 + t,
                                     org.Z() - W / 2 - 1),
                              W - 2 * t, H - 2 * t, W + 2)
              .Shape();
      outer = BRepAlgoAPI_Cut(outer, inner).Shape();
    }
    // Align along axis, extrude to length
    gp_Ax3 srcAx(org, gp::DZ(), gp::DX());
    gp_Dir yDir = gp::DZ().Crossed(axis);
    gp_Ax3 tgtAx(org, axis, gp_Dir(0, 0, 1));
    gp_Trsf tr;
    tr.SetTransformation(tgtAx, srcAx);
    return BRepBuilderAPI_Transform(outer, tr).Shape();
  };

  TopoDS_Shape tube;
  double totalL =
      (params.type == registration_arm_type::EXTENDED) ? L * 1.3 : L;

  if (params.type == registration_arm_type::STRAIGHT ||
      params.type == registration_arm_type::EXTENDED) {
    // Tube along X: width in Y, height in Z
    TopoDS_Shape outer =
        BRepPrimAPI_MakeBox(gp_Pnt(0, -W / 2, -H / 2), totalL, W, H).Shape();
    if (t > 0 && W > 2 * t && H > 2 * t) {
      TopoDS_Shape inner =
          BRepPrimAPI_MakeBox(gp_Pnt(-1, -W / 2 + t, -H / 2 + t), totalL + 2,
                              W - 2 * t, H - 2 * t)
              .Shape();
      tube = BRepAlgoAPI_Cut(outer, inner).Shape();
    } else
      tube = outer;
  } else {
    // Curved type: single continuous sweep — straight + arc transition + curved
    // tip
    double straightLen = L * 0.7, curveLen = L * 0.3;
    gp_Pnt p0(0, 0, 0), p1(straightLen, 0, 0);
    gp_Pnt p2(straightLen + curveLen * 0.5, 0, -curveLen * 0.1);
    gp_Pnt p3(straightLen + curveLen, 0, -curveLen * 0.2);

    // Build single path: line + Bezier
    BRepBuilderAPI_MakeWire pathWire;
    pathWire.Add(BRepBuilderAPI_MakeEdge(p0, p1)); // straight segment
    Handle(TColgp_HArray1OfPnt) bzp = new TColgp_HArray1OfPnt(1, 3);
    bzp->SetValue(1, p1);
    bzp->SetValue(2, p2);
    bzp->SetValue(3, p3);
    pathWire.Add(BRepBuilderAPI_MakeEdge(new Geom_BezierCurve(bzp->Array1())));

    // Square section in YZ plane at start
    gp_Pnt s1(0, -W / 2, -H / 2), s2(0, W / 2, -H / 2), s3(0, W / 2, H / 2),
        s4(0, -W / 2, H / 2);
    TopoDS_Wire sqWire =
        BRepBuilderAPI_MakePolygon(s1, s2, s3, s4, Standard_True).Wire();

    BRepOffsetAPI_MakePipeShell pipe(pathWire.Wire());
    pipe.Add(sqWire);
    pipe.SetMode(Standard_True);
    pipe.Build();
    if (pipe.IsDone() && pipe.MakeSolid())
      tube = pipe.Shape();
  }

  // Base end: joint plate + L-flange toward band
  double jointSize = std::max(W, H) * 1.2;
  double jThick = W * 0.6;
  double jY = jointSize / 6, jW = jointSize / 3, jZ = jointSize * 1.8,
         jH = jointSize * 2;
  gp_Pnt jOrg(-jThick / 2, -jY, -jZ);
  TopoDS_Shape joint = BRepPrimAPI_MakeBox(jOrg, jThick, jW, jH).Shape();
  tube = BRepAlgoAPI_Fuse(tube, joint).Shape();

  // L-flange — short tab in XZ, 90° to joint
  double fLen = jThick * 1.5, fH = jThick * 0.8;
  gp_Pnt fOrg(-jThick / 2 - fLen, -jThick / 2, -jZ - fH);
  TopoDS_Shape flange =
      BRepPrimAPI_MakeBox(fOrg, fLen + jThick, jThick, fH).Shape();
  tube = BRepAlgoAPI_Fuse(tube, flange).Shape();

  // Front end: wire clamp — top flush with tube top, extends downward
  double clampW = W * 1.2, clampH = H * 2, cThick = W * 0.6;
  double clampX = totalL;
  double tubeTopZ = (params.type == registration_arm_type::CURVED)
                        ? -(L * 0.3 * 0.2) + H / 2
                        : H / 2;
  // Clamp hangs down from tube top
  gp_Pnt cOrg(clampX, -clampW / 2, tubeTopZ - clampH);
  TopoDS_Shape clamp =
      BRepPrimAPI_MakeBox(cOrg, cThick, clampW, clampH).Shape();

  // Wire groove at clamp bottom
  double gr = W * 0.35;
  gp_Ax2 ga(gp_Pnt(clampX + cThick / 2, -clampW / 2, tubeTopZ - clampH),
            gp::DY());
  clamp =
      BRepAlgoAPI_Cut(clamp, BRepPrimAPI_MakeCylinder(ga, gr, clampW).Shape())
          .Shape();

  // Bolts at mid-clamp
  double br = W * 0.09, boltLen = cThick + W * 0.15;
  for (int side = -1; side <= 1; side += 2) {
    double by = side * clampW * 0.35;
    TopoDS_Shape bolt =
        BRepPrimAPI_MakeCylinder(
            gp_Ax2(gp_Pnt(clampX - 1, by, tubeTopZ - clampH / 2), gp::DX()), br,
            boltLen)
            .Shape();
    clamp = BRepAlgoAPI_Fuse(clamp, bolt).Shape();
  }
  tube = BRepAlgoAPI_Fuse(tube, clamp).Shape();

  // 将原点移动到 L 型法兰悬空侧中心
  double xShift = jThick / 2.0 + fLen;
  double zShift = jZ + fH / 2.0;
  gp_Trsf originShift;
  originShift.SetTranslation(gp_Vec(xShift, 0, zShift));
  tube = BRepBuilderAPI_Transform(tube, originShift).Shape();

  if (std::abs(params.angle) > Precision::Angular()) {
    double ar = params.angle * M_PI / 180.0;
    gp_Trsf rot;
    rot.SetRotation(gp_Ax1(gp::Origin(), gp::DY()), ar);
    tube = BRepBuilderAPI_Transform(tube, rot).Shape();
  }

  return tube;
}

TopoDS_Shape create_registration_arm(const registration_arm_params &params,
                                     const gp_Pnt &basePoint,
                                     const gp_Dir &axisDirection,
                                     const gp_Dir &upDir) {
  TopoDS_Shape shape = create_registration_arm(params);

  gp_Dir yDir = upDir.Crossed(axisDirection);
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(basePoint, upDir, axisDirection);
  gp_Trsf transformation;
  transformation.SetTransformation(targetAx3, sourceAx3);

  return BRepBuilderAPI_Transform(shape, transformation).Shape();
}

// =========================================================================
// 10. Guy Wire (下锚拉线)
// =========================================================================
// Origin: center of mast mounting base (立柱安装底座中心).
// The entire assembly lies in the XZ plane.
// Cable extends in +X +Z direction based on angle and length.
// Mast side: rectangular plate in YZ plane + mounting ring.
// Ground side: mounting ring pointing in -Z direction.
// =========================================================================
namespace {

// Create a U-shaped ring from round rebar using ThruSections loft.
// The ring lies in the XZ plane (Y=0), connecting fromP to toP,
// with a mid-point offset outward for the bend.
TopoDS_Shape makeRebarRing(const gp_Pnt &fromP, const gp_Pnt &toP,
                            double rebarR) {
  gp_Vec span(fromP, toP);
  double half = span.Magnitude() / 2.0;
  if (half < rebarR * 2) half = rebarR * 2;

  // Mid-point bulging outward by half the span length
  gp_Pnt mid((fromP.X() + toP.X()) / 2.0,
             (fromP.Y() + toP.Y()) / 2.0,
             (fromP.Z() + toP.Z()) / 2.0 + half * 0.6);

  // Build 3-point Bezier path
  Handle(TColgp_HArray1OfPnt) poles = new TColgp_HArray1OfPnt(1, 3);
  poles->SetValue(1, fromP);
  poles->SetValue(2, mid);
  poles->SetValue(3, toP);
  Handle(Geom_BezierCurve) bezier = new Geom_BezierCurve(poles->Array1());
  TopoDS_Edge pathEdge = BRepBuilderAPI_MakeEdge(bezier).Edge();
  TopoDS_Wire pathWire = BRepBuilderAPI_MakeWire(pathEdge).Wire();

  // Sweep circular profile along path
  gp_Pnt startP; gp_Vec startV; bezier->D1(0, startP, startV);
  if (startV.Magnitude() <= Precision::Confusion())
    startV = gp_Vec(1, 0, 0);

  gp_Dir startDir(startV);
  gp_Dir perpDir = startDir.IsParallel(gp_Dir(0, 1, 0), Precision::Angular())
                       ? gp_Dir(1, 0, 0)
                       : startDir.Crossed(gp_Dir(0, 1, 0));

  gp_Circ profileCirc(gp_Ax2(fromP, perpDir), rebarR);
  Handle(Geom_Curve) profileCurve = new Geom_Circle(profileCirc);
  TopoDS_Edge profileEdge = BRepBuilderAPI_MakeEdge(profileCurve).Edge();
  TopoDS_Wire profileWire = BRepBuilderAPI_MakeWire(profileEdge).Wire();

  BRepOffsetAPI_MakePipeShell pipe(pathWire);
  pipe.Add(profileWire, Standard_False, Standard_True);
  pipe.SetMode(Standard_True);
  pipe.Build();
  if (pipe.IsDone()) return pipe.Shape();

  // Fallback: straight bar
  return BRepPrimAPI_MakeCylinder(gp_Ax2(fromP, gp_Dir(span)), rebarR,
                                   span.Magnitude()).Shape();
}

} // anonymous namespace

TopoDS_Shape create_guy_wire(const guy_wire_params &params) {
  if (params.length <= 0 || params.diameter <= 0)
    throw Standard_ConstructionError("Length and diameter must be positive");

  BRep_Builder builder;
  TopoDS_Compound compound;
  builder.MakeCompound(compound);

  double angleRad = params.angle * M_PI / 180.0;
  double cableR = params.diameter / 2.0;

  // Cable direction in XZ plane
  gp_Dir cableDir(cos(angleRad), 0, sin(angleRad));
  gp_Pnt cableEnd(params.length * cos(angleRad), 0,
                  params.length * sin(angleRad));

  // 1. Mast mounting base: rectangular plate in YZ plane at origin
  double baseW = 80, baseH = 100, baseT = 8;
  if (params.anchorPlateLength > 0) baseW = params.anchorPlateLength * 0.3;
  if (params.anchorPlateWidth > 0) baseH = params.anchorPlateWidth * 0.3;
  TopoDS_Shape basePlate = BRepPrimAPI_MakeBox(
      gp_Pnt(-baseT / 2, -baseW / 2, -baseH / 2), baseT, baseW, baseH).Shape();
  builder.Add(compound, basePlate);

  // 2. Mast-side elliptical rebar ring: connects plate (origin) to cable start
  {
    double rebarR = std::max(cableR * 0.4, 2.0);
    gp_Pnt ringEnd(cableR * 3, 0, 0);
    TopoDS_Shape ring = makeRebarRing(gp::Origin(), ringEnd, rebarR);
    builder.Add(compound, ring);
  }

  // 3. Cable body (拉筋): cylinder from origin along cableDir to cableEnd
  TopoDS_Shape cable = BRepPrimAPI_MakeCylinder(
      gp_Ax2(gp::Origin(), cableDir), cableR, params.length).Shape();
  builder.Add(compound, cable);

  // 4. Ground-side elliptical rebar ring: connects cable end to anchor plate
  {
    double rebarR = std::max(cableR * 0.4, 2.0);
    double pL = params.anchorPlateLength > 0 ? params.anchorPlateLength : 200;
    double pW = params.anchorPlateWidth > 0 ? params.anchorPlateWidth : 150;
    gp_Pnt plateCenter(cableEnd.X(), cableEnd.Y(), cableEnd.Z() - cableR * 3);
    TopoDS_Shape ring = makeRebarRing(cableEnd, plateCenter, rebarR);
    builder.Add(compound, ring);

    // 5. Anchor plate (at bottom of ground ring, parallel to XY plane)
    double pT = 10;
    gp_Pnt pOrg(plateCenter.X() - pL / 2, plateCenter.Y() - pW / 2,
                plateCenter.Z() - pT);
    TopoDS_Shape plate = BRepPrimAPI_MakeBox(pOrg, pL, pW, pT).Shape();
    builder.Add(compound, plate);
  }

  // 7. Butterfly disc insulators (蝶形绝缘子)
  if (params.hasInsulator && params.insulatorCount > 0) {
    int count = params.insulatorCount > 0 ? params.insulatorCount : 2;
    double discR = cableR * 4.0;
    double neckR = cableR * 1.5;
    double discH = cableR * 2.5;
    double gap = discH * 0.3;
    double totalH = count * discH + (count - 1) * gap;
    double startRatio = 0.3;
    gp_Pnt insStart(params.length * startRatio * cos(angleRad), 0,
                    params.length * startRatio * sin(angleRad));

    for (int i = 0; i < count; ++i) {
      gp_Pnt discBase(insStart.X() + i * (discH + gap) * cos(angleRad), 0,
                      insStart.Z() + i * (discH + gap) * sin(angleRad));

      // Each disc: bottom cone flares out, top cone tapers back
      gp_Pnt midP(discBase.X() + discH * 0.5 * cos(angleRad), 0,
                  discBase.Z() + discH * 0.5 * sin(angleRad));
      gp_Pnt topP(discBase.X() + discH * cos(angleRad), 0,
                  discBase.Z() + discH * sin(angleRad));

      // Bottom cone: neckR → discR, half height
      TopoDS_Shape bot = BRepPrimAPI_MakeCone(
          gp_Ax2(discBase, cableDir), neckR, discR, discH * 0.5).Shape();

      // Top cone: discR → neckR, half height
      TopoDS_Shape top = BRepPrimAPI_MakeCone(
          gp_Ax2(midP, cableDir), discR, neckR, discH * 0.5).Shape();

      TopoDS_Shape disc = BRepAlgoAPI_Fuse(bot, top).Shape();
      builder.Add(compound, disc);
    }
  }

  return compound;
}

TopoDS_Shape create_guy_wire(const guy_wire_params &params,
                             const gp_Pnt &anchorPoint, const gp_Pnt &mastPoint,
                             const gp_Dir &upDir) {
  if (params.length <= 0 || params.diameter <= 0)
    throw Standard_ConstructionError("Length and diameter must be positive");

  BRep_Builder builder;
  TopoDS_Compound compound;
  builder.MakeCompound(compound);

  gp_Vec spanVec(anchorPoint, mastPoint);
  double span = spanVec.Magnitude();
  if (span <= Precision::Confusion())
    throw Standard_ConstructionError("Anchor and mast points must differ");

  gp_Dir cableDir(spanVec);
  double cableR = params.diameter / 2.0;

  // 1. Mast mounting base at mastPoint
  double baseW = 80, baseH = 100, baseT = 8;
  if (params.anchorPlateLength > 0) baseW = params.anchorPlateLength * 0.3;
  if (params.anchorPlateWidth > 0) baseH = params.anchorPlateWidth * 0.3;
  TopoDS_Shape basePlate = BRepPrimAPI_MakeBox(
      gp_Pnt(mastPoint.X() - baseT / 2, mastPoint.Y() - baseW / 2,
             mastPoint.Z() - baseH / 2),
      baseT, baseW, baseH).Shape();
  builder.Add(compound, basePlate);

  // 2. Mast-side elliptical rebar ring
  {
    double rebarR = std::max(cableR * 0.4, 2.0);
    gp_Pnt ringEnd(mastPoint.X() + cableR * 3, mastPoint.Y(), mastPoint.Z());
    TopoDS_Shape ring = makeRebarRing(mastPoint, ringEnd, rebarR);
    builder.Add(compound, ring);
  }

  // 3. Cable body (拉筋)
  TopoDS_Shape cable = BRepPrimAPI_MakeCylinder(
      gp_Ax2(anchorPoint, cableDir), cableR, span).Shape();
  builder.Add(compound, cable);

  // 4. Ground-side elliptical rebar ring + anchor plate
  {
    double rebarR = std::max(cableR * 0.4, 2.0);
    double pL = params.anchorPlateLength > 0 ? params.anchorPlateLength : 200;
    double pW = params.anchorPlateWidth > 0 ? params.anchorPlateWidth : 150;
    gp_Pnt plateCenter(anchorPoint.X(), anchorPoint.Y(),
                       anchorPoint.Z() - cableR * 3);
    TopoDS_Shape ring = makeRebarRing(anchorPoint, plateCenter, rebarR);
    builder.Add(compound, ring);

    double pT = 10;
    gp_Pnt pOrg(plateCenter.X() - pL / 2, plateCenter.Y() - pW / 2,
                plateCenter.Z() - pT);
    TopoDS_Shape plate = BRepPrimAPI_MakeBox(pOrg, pL, pW, pT).Shape();
    builder.Add(compound, plate);
  }

  return compound;
}

// =========================================================================
// 11. Steel Mast (钢支柱) — TB/T 中国电气化铁路标准
// =========================================================================
// Types: LATTICE=格构式角钢柱(H/系列), H_BEAM=H型钢柱(GH/系列)
// 特征: 格构式4角主肢角钢+Z字腹杆+节点板+柱底法兰+攀爬脚钉
//       H型钢腹板+翼缘+T形截面锥度+渐变法兰
// =========================================================================

namespace {

// Helper: create an L-shaped angle steel cross-section wire for lattice legs
// legLong = long leg length, legShort = short leg length, thick = thickness
TopoDS_Wire makeAngleSteelProfile(double legLong, double legShort,
                                  double thick) {
  BRepBuilderAPI_MakeWire w;
  // L-shape in the XY plane: heel (outer corner) at the origin
  // Long leg along +Y, short leg along +X
  gp_Pnt p0(0, 0, 0), p1(0, legLong, 0), p2(thick, legLong, 0),
      p3(thick, thick, 0), p4(legShort, thick, 0), p5(legShort, 0, 0);
  w.Add(BRepBuilderAPI_MakeEdge(p0, p1));
  w.Add(BRepBuilderAPI_MakeEdge(p1, p2));
  w.Add(BRepBuilderAPI_MakeEdge(p2, p3));
  w.Add(BRepBuilderAPI_MakeEdge(p3, p4));
  w.Add(BRepBuilderAPI_MakeEdge(p4, p5));
  w.Add(BRepBuilderAPI_MakeEdge(p5, p0));
  return w.Wire();
}

} // anonymous namespace

TopoDS_Shape create_steel_mast(const steel_mast_params &params) {
  if (params.height <= 0 || params.bottomWidth <= 0)
    throw Standard_ConstructionError(
        "Height and bottom width must be positive");

  BRep_Builder builder;
  TopoDS_Compound compound;
  builder.MakeCompound(compound);

  const double H = params.height;
  const double B = params.bottomWidth; // bottom outer width between leg centers
  const double T = params.topWidth > 0 ? params.topWidth : B * 0.6;
  const double L = params.wallThickness; // plate/steel thickness

  // ===== H-BEAM TYPE =====
  if (params.type == steel_mast_type::H_BEAM) {
    double fT = params.flangeThickness > 0 ? params.flangeThickness : L * 1.5;
    int nSeg = std::max(1, params.segmentCount);
    double segH = H / nSeg;

    for (int seg = 0; seg < nSeg; ++seg) {
      double r0 = (double)seg / nSeg, r1 = (double)(seg + 1) / nSeg;
      double w0 = B + (T - B) * r0, w1 = B + (T - B) * r1;
      double z0 = seg * segH;
      double hw0 = w0 / 2.0, hw1 = w1 / 2.0;

      // Web: thin plate in X, spanning Y from -hw0+fT to hw0-fT
      gp_Pnt webBt[4] = {{-L / 2, -hw0 + fT, z0},
                         {L / 2, -hw0 + fT, z0},
                         {L / 2, hw0 - fT, z0},
                         {-L / 2, hw0 - fT, z0}};
      TopoDS_Wire webBw =
          BRepBuilderAPI_MakePolygon(webBt[0], webBt[1], webBt[2], webBt[3],
                                     Standard_True)
              .Wire();
      gp_Pnt webTt[4] = {{-L / 2, -hw1 + fT, z0 + segH},
                         {L / 2, -hw1 + fT, z0 + segH},
                         {L / 2, hw1 - fT, z0 + segH},
                         {-L / 2, hw1 - fT, z0 + segH}};
      TopoDS_Wire webTw =
          BRepBuilderAPI_MakePolygon(webTt[0], webTt[1], webTt[2], webTt[3],
                                     Standard_True)
              .Wire();
      BRepOffsetAPI_ThruSections webThru(Standard_True);
      webThru.AddWire(webBw);
      webThru.AddWire(webTw);
      webThru.Build();

      // Left flange: wide plate in X, spanning from -hw0 to hw0, Y=-hw0 to
      // -hw0+fT
      gp_Pnt lfBt[4] = {{-hw0, -hw0, z0},
                        {hw0, -hw0, z0},
                        {hw0, -hw0 + fT, z0},
                        {-hw0, -hw0 + fT, z0}};
      TopoDS_Wire lfBw = BRepBuilderAPI_MakePolygon(lfBt[0], lfBt[1], lfBt[2],
                                                    lfBt[3], Standard_True)
                             .Wire();
      gp_Pnt lfTt[4] = {{-hw1, -hw1, z0 + segH},
                        {hw1, -hw1, z0 + segH},
                        {hw1, -hw1 + fT, z0 + segH},
                        {-hw1, -hw1 + fT, z0 + segH}};
      TopoDS_Wire lfTw = BRepBuilderAPI_MakePolygon(lfTt[0], lfTt[1], lfTt[2],
                                                    lfTt[3], Standard_True)
                             .Wire();
      BRepOffsetAPI_ThruSections lfThru(Standard_True);
      lfThru.AddWire(lfBw);
      lfThru.AddWire(lfTw);
      lfThru.Build();

      // Right flange: wide plate, Y from hw0-fT to hw0, X from -hw0 to hw0
      gp_Pnt rfBt[4] = {{-hw0, hw0 - fT, z0},
                        {hw0, hw0 - fT, z0},
                        {hw0, hw0, z0},
                        {-hw0, hw0, z0}};
      TopoDS_Wire rfBw = BRepBuilderAPI_MakePolygon(rfBt[0], rfBt[1], rfBt[2],
                                                    rfBt[3], Standard_True)
                             .Wire();
      gp_Pnt rfTt[4] = {{-hw1, hw1 - fT, z0 + segH},
                        {hw1, hw1 - fT, z0 + segH},
                        {hw1, hw1, z0 + segH},
                        {-hw1, hw1, z0 + segH}};
      TopoDS_Wire rfTw = BRepBuilderAPI_MakePolygon(rfTt[0], rfTt[1], rfTt[2],
                                                    rfTt[3], Standard_True)
                             .Wire();
      BRepOffsetAPI_ThruSections rfThru(Standard_True);
      rfThru.AddWire(rfBw);
      rfThru.AddWire(rfTw);
      rfThru.Build();

      TopoDS_Shape segBody =
          BRepAlgoAPI_Fuse(webThru.Shape(), lfThru.Shape()).Shape();
      segBody = BRepAlgoAPI_Fuse(segBody, rfThru.Shape()).Shape();
      builder.Add(compound, segBody);

      if (seg > 0 && params.flangeThickness > 0) {
        gp_Pnt fo(-hw0, -hw0, z0 - params.flangeThickness);
        builder.Add(
            compound,
            BRepPrimAPI_MakeBox(fo, w0, w0, params.flangeThickness).Shape());
      }
    }
  }

  // ===== LATTICE TYPE (格构式角钢柱) =====
  else {
    double legW = std::max(L * 5.0, B * 0.10);
    double legT = std::max(L * 0.8, legW * 0.08); // 角钢肢厚, 兜底避免零厚度
    double halfB = B / 2.0, halfT = T / 2.0;

    auto makeTaperedLeg = [&](double sx, double sy) -> TopoDS_Shape {
      double xb = sx * halfB, yb = sy * halfB;
      double xt = sx * halfT, yt = sy * halfT;
      // 主肢等边角钢断面: 角跟朝外, 两肢朝内 (按象限旋转 L 断面)
      double rot = 0;
      if (sx > 0 && sy > 0) rot = M_PI;
      else if (sx > 0) rot = M_PI / 2;
      else if (sy > 0) rot = -M_PI / 2;
      gp_Trsf rr;
      rr.SetRotation(gp_Ax1(gp::Origin(), gp::DZ()), rot);
      TopoDS_Shape prof = BRepBuilderAPI_Transform(
          makeAngleSteelProfile(legW, legW, legT), rr).Shape();
      gp_Trsf tb;
      tb.SetTranslation(gp_Vec(xb, yb, 0));
      TopoDS_Wire bw =
          TopoDS::Wire(BRepBuilderAPI_Transform(prof, tb).Shape());
      gp_Trsf tt;
      tt.SetTranslation(gp_Vec(xt, yt, H));
      TopoDS_Wire tw =
          TopoDS::Wire(BRepBuilderAPI_Transform(prof, tt).Shape());
      BRepOffsetAPI_ThruSections lg(Standard_True);
      lg.AddWire(bw);
      lg.AddWire(tw);
      try { lg.Build(); } catch (...) { warn_part_failed("create_steel_mast", "lattice leg loft"); }
      if (lg.IsDone()) return lg.Shape();
      // 放样失败退化: 角钢断面沿 Z 拉伸 (不做圆管)
      return BRepPrimAPI_MakePrism(bw, gp_Vec(0, 0, H)).Shape();
    };

    for (auto &c : {std::make_pair(-1.0, -1.0), std::make_pair(-1.0, 1.0),
                    std::make_pair(1.0, -1.0), std::make_pair(1.0, 1.0)})
      builder.Add(compound, makeTaperedLeg(c.first, c.second));

    int nLevels = std::max(2, (int)(H / 1200));
    int nSeg = nLevels + 1;
    double segH = H / nSeg;
    double braceR = legW * 0.25;
    double gussetSize = legW * 2.5, gussetThick = L * 0.6;

    for (int i = 0; i < nSeg; ++i) {
      double z0 = i * segH, z1 = (i + 1) * segH;
      double interp0 = halfB + (halfT - halfB) * z0 / H;
      double interp1 = halfB + (halfT - halfB) * z1 / H;

      if (i > 0) {
        for (int face = 0; face < 4; ++face) {
          double x1, y1, x2, y2;
          switch (face) {
          case 0:
            x1 = -interp0;
            y1 = -interp0;
            x2 = interp0;
            y2 = -interp0;
            break;
          case 1:
            x1 = interp0;
            y1 = -interp0;
            x2 = interp0;
            y2 = interp0;
            break;
          case 2:
            x1 = interp0;
            y1 = interp0;
            x2 = -interp0;
            y2 = interp0;
            break;
          case 3:
            x1 = -interp0;
            y1 = interp0;
            x2 = -interp0;
            y2 = -interp0;
            break;
          }
          gp_Pnt t1(x1, y1, z0), t2(x2, y2, z0);
          gp_Vec v(t1, t2);
          double l = v.Magnitude();
          if (l > Precision::Confusion())
            builder.Add(compound, BRepPrimAPI_MakeCylinder(
                                      gp_Ax2(t1, gp_Dir(v)), braceR, l)
                                      .Shape());
          double gs = std::min(gussetSize, l * 0.2);
          gp_Pnt go(x1 - gs / 2, y1 - gs / 2, z0 - gussetThick / 2);
          gp_Trsf gTrs;
          gTrs.SetTranslation(gp_Vec(0, 0, 0));
          builder.Add(compound,
                      BRepPrimAPI_MakeBox(go, gs, gs, gussetThick).Shape());
        }
      }

      for (int face = 0; face < 4; ++face) {
        double xb, yb, xt, yt;
        switch (face) {
        case 0:
          xb = interp0;
          yb = -interp0;
          xt = -interp1;
          yt = -interp1;
          break;
        case 1:
          xb = interp0;
          yb = interp0;
          xt = interp1;
          yt = -interp1;
          break;
        case 2:
          xb = -interp0;
          yb = interp0;
          xt = interp1;
          yt = interp1;
          break;
        case 3:
          xb = -interp0;
          yb = -interp0;
          xt = -interp1;
          yt = interp1;
          break;
        }
        gp_Pnt pz1(xb, yb, z0), pz2(xt, yt, z1);
        gp_Vec vz(pz1, pz2);
        double dz = vz.Magnitude();
        if (dz > Precision::Confusion())
          builder.Add(compound, BRepPrimAPI_MakeCylinder(
                                    gp_Ax2(pz1, gp_Dir(vz)), braceR * 0.7, dz)
                                    .Shape());
      }
    }

    int pegCount = (int)(H / 300);
    for (int p = 0; p < pegCount; ++p) {
      double z = (p + 1) * 300;
      double ip = halfB + (halfT - halfB) * z / H;
      builder.Add(compound, BRepPrimAPI_MakeCylinder(
                                gp_Ax2(gp_Pnt(ip, -ip, z), gp_Dir(1, -1, 0)),
                                legW * 0.15, legW * 0.8)
                                .Shape());
    }
  }

  // ===== BASE FLANGE (柱底法兰) =====
  double fw =
      params.flangeWidth > 0 ? params.flangeWidth : params.bottomWidth * 1.3;
  double fth = params.flangeThickness > 0 ? params.flangeThickness
                                          : params.wallThickness * 2;
  double halfFW = fw / 2.0;
  gp_Pnt flgOrg(-halfFW, -halfFW, -fth);
  TopoDS_Shape flange = BRepPrimAPI_MakeBox(flgOrg, fw, fw, fth).Shape();
  builder.Add(compound, flange);

  // ===== TOP CAP PLATE (柱顶封板) — extend beyond leg centers
  double twBase =
      params.topWidth > 0 ? params.topWidth : params.bottomWidth * 0.6;
  double tw = twBase * 1.2;
  double capThick = std::max(fth * 0.6, params.wallThickness * 1.2);
  double halfTW = tw / 2.0;
  gp_Pnt capOrg(-halfTW, -halfTW, H);
  TopoDS_Shape topCap = BRepPrimAPI_MakeBox(capOrg, tw, tw, capThick).Shape();
  builder.Add(compound, topCap);

  if (params.type == steel_mast_type::H_BEAM) {
    int ribCount = 4;
    double ribH = fw * 0.25, ribT = L * 1.5;
    for (int r = 0; r < ribCount; ++r) {
      double a = r * 2 * M_PI / ribCount + M_PI / ribCount;
      gp_Pnt r1(halfFW * 0.15 * cos(a), halfFW * 0.15 * sin(a), -fth);
      gp_Pnt r2(halfFW * 0.85 * cos(a), halfFW * 0.85 * sin(a), -fth);
      gp_Pnt r3(halfFW * 0.15 * cos(a), halfFW * 0.15 * sin(a), -fth + ribH);
      gp_Dir tang(-sin(a), cos(a), 0);
      TopoDS_Wire rw =
          BRepBuilderAPI_MakePolygon(r1, r2, r3, Standard_True).Wire();
      TopoDS_Face rf = BRepLib_MakeFace(rw).Face();
      TopoDS_Shape rib =
          BRepPrimAPI_MakePrism(rf, gp_Vec(tang.XYZ() * ribT / 2)).Shape();
      rib = BRepAlgoAPI_Fuse(
                rib, BRepPrimAPI_MakePrism(rf, gp_Vec(-tang.X() * ribT / 2,
                                                      -tang.Y() * ribT / 2, 0))
                         .Shape())
                .Shape();
      builder.Add(compound, rib);
    }
  }

  if (params.anchorDiameter > 0 && params.anchorSpacing > 0) {
    double ar = params.anchorDiameter / 2.0, hs = params.anchorSpacing / 2.0;
    for (int ax = -1; ax <= 1; ax += 2)
      for (int ay = -1; ay <= 1; ay += 2) {
        TopoDS_Shape hole =
            BRepPrimAPI_MakeCylinder(
                gp_Ax2(gp_Pnt(ax * hs, ay * hs, -fth - 1), gp::DZ()), ar,
                fth + 2)
                .Shape();
        flange = BRepAlgoAPI_Cut(flange, hole).Shape();
      }
  }

  return compound;
}
TopoDS_Shape create_steel_mast(const steel_mast_params &params,
                               const gp_Pnt &baseCenter,
                               const gp_Dir &axisDirection) {
  TopoDS_Shape s = create_steel_mast(params);
  gp_Ax3 src(gp::Origin(), gp::DZ()), tgt(baseCenter, axisDirection);
  gp_Trsf tr;
  tr.SetTransformation(tgt, src);
  return BRepBuilderAPI_Transform(s, tr).Shape();
}

// =========================================================================
// 12. Concrete Mast (混凝土支柱)
// =========================================================================
TopoDS_Shape create_concrete_mast(const concrete_mast_params &params) {
  if (params.height <= 0 || params.bottomWidth <= 0)
    throw Standard_ConstructionError("Height and width must be positive");
  TopoDS_Shape mast;
  if (params.sectionType == concrete_mast_section_type::CIRCULAR ||
      params.sectionType == concrete_mast_section_type::CIRCULAR_HOLED) {
    double outerR = params.bottomWidth / 2,
           innerR = outerR - params.wallThickness, topR = params.topWidth / 2;
    if (std::abs(topR - outerR) > Precision::Confusion()) {
      BRepOffsetAPI_ThruSections gen(Standard_True);
      gp_Circ bc(gp_Ax2(gp::Origin(), gp::DZ()), outerR);
      TopoDS_Wire bw =
          BRepBuilderAPI_MakeWire(BRepBuilderAPI_MakeEdge(bc).Edge());
      gen.AddWire(bw);
      gp_Circ tc(gp_Ax2(gp_Pnt(0, 0, params.height), gp::DZ()), topR);
      TopoDS_Wire tw =
          BRepBuilderAPI_MakeWire(BRepBuilderAPI_MakeEdge(tc).Edge());
      gen.AddWire(tw);
      gen.Build();
      mast = gen.Shape();
    } else {
      mast = BRepPrimAPI_MakeCylinder(gp_Ax2(gp::Origin(), gp::DZ()), outerR,
                                      params.height)
                 .Shape();
    }
    if (innerR > 0) {
      double innerTopR =
          std::max(innerR - (params.bottomWidth - params.topWidth) / 2, 0.1);
      TopoDS_Shape inner;
      if (std::abs(innerTopR - innerR) > Precision::Confusion()) {
        BRepOffsetAPI_ThruSections ig(Standard_True);
        gp_Circ ibc(gp_Ax2(gp::Origin(), gp::DZ()), innerR);
        ig.AddWire(
            BRepBuilderAPI_MakeWire(BRepBuilderAPI_MakeEdge(ibc).Edge()));
        gp_Circ itc(gp_Ax2(gp_Pnt(0, 0, params.height), gp::DZ()), innerTopR);
        ig.AddWire(
            BRepBuilderAPI_MakeWire(BRepBuilderAPI_MakeEdge(itc).Edge()));
        ig.Build();
        inner = ig.Shape();
      } else {
        inner = BRepPrimAPI_MakeCylinder(gp_Ax2(gp::Origin(), gp::DZ()), innerR,
                                         params.height)
                    .Shape();
      }
      mast = BRepAlgoAPI_Cut(mast, inner).Shape();
    }
    if (params.sectionType == concrete_mast_section_type::CIRCULAR_HOLED &&
        params.holeDiameter > 0) {
      double holeR = params.holeDiameter / 2;
      for (int row = 0; row < params.holeRowCount; ++row) {
        double zPos = params.firstHoleOffset + row * params.holeSpacingV;
        if (zPos + holeR > params.height)
          break;
        for (int col = 0; col < params.holesPerRow; ++col) {
          double a = 2 * M_PI * col / params.holesPerRow;
          TopoDS_Shape h =
              BRepPrimAPI_MakeCylinder(
                  gp_Ax2(gp_Pnt(outerR * cos(a), outerR * sin(a), zPos),
                         gp_Dir(cos(a), sin(a), 0)),
                  holeR, params.wallThickness + 2)
                  .Shape();
          mast = BRepAlgoAPI_Cut(mast, h).Shape();
        }
      }
    }
  } else if (params.sectionType == concrete_mast_section_type::RECTANGULAR) {
    double b = params.bottomWidth;
    double t = params.topWidth > 0 ? params.topWidth : b;
    if (std::abs(t - b) > Precision::Confusion()) {
      BRepOffsetAPI_ThruSections gen(Standard_True);
      gp_Pnt bp[4] = {{-b / 2, -b / 2, 0},
                      {b / 2, -b / 2, 0},
                      {b / 2, b / 2, 0},
                      {-b / 2, b / 2, 0}};
      gen.AddWire(BRepBuilderAPI_MakePolygon(bp[0], bp[1], bp[2], bp[3],
                                             Standard_True));
      gp_Pnt tp[4] = {{-t / 2, -t / 2, (double)params.height},
                      {t / 2, -t / 2, (double)params.height},
                      {t / 2, t / 2, (double)params.height},
                      {-t / 2, t / 2, (double)params.height}};
      gen.AddWire(BRepBuilderAPI_MakePolygon(tp[0], tp[1], tp[2], tp[3],
                                             Standard_True));
      gen.Build();
      mast = gen.Shape();
    } else {
      mast = BRepPrimAPI_MakeBox(gp_Pnt(-b / 2, -b / 2, 0), b, b, params.height)
                 .Shape();
    }
    if (params.wallThickness > 0 && b > 2 * params.wallThickness) {
      double ib = b - 2 * params.wallThickness;
      TopoDS_Shape inner = BRepPrimAPI_MakeBox(gp_Pnt(-ib / 2, -ib / 2, -1), ib,
                                               ib, params.height + 2)
                               .Shape();
      mast = BRepAlgoAPI_Cut(mast, inner).Shape();
    }
  } else if (params.sectionType ==
             concrete_mast_section_type::RECTANGULAR_HOLED) {
    double b = params.bottomWidth;
    double t = params.topWidth > 0 ? params.topWidth : b;
    double thinW = b * 0.45;
    if (std::abs(t - b) > Precision::Confusion()) {
      double thinT = t * 0.45;
      BRepOffsetAPI_ThruSections gen(Standard_True);
      gp_Pnt bp[4] = {{-thinW / 2, -b / 2, 0},
                      {thinW / 2, -b / 2, 0},
                      {thinW / 2, b / 2, 0},
                      {-thinW / 2, b / 2, 0}};
      gen.AddWire(BRepBuilderAPI_MakePolygon(bp[0], bp[1], bp[2], bp[3],
                                             Standard_True));
      gp_Pnt tp[4] = {{-thinT / 2, -t / 2, (double)params.height},
                      {thinT / 2, -t / 2, (double)params.height},
                      {thinT / 2, t / 2, (double)params.height},
                      {-thinT / 2, t / 2, (double)params.height}};
      gen.AddWire(BRepBuilderAPI_MakePolygon(tp[0], tp[1], tp[2], tp[3],
                                             Standard_True));
      gen.Build();
      mast = gen.Shape();
    } else {
      mast = BRepPrimAPI_MakeBox(gp_Pnt(-thinW / 2, -b / 2, 0), thinW, b,
                                 params.height)
                 .Shape();
    }
    // 安装孔 — 仅分布在柱身上部安装段, 支持长圆孔 (holeLength>holeDiameter)
    if (params.holeDiameter > 0 && params.holeSpacingV > 0) {
      double holeLen = std::max(params.holeLength, params.holeDiameter);
      int maxCount = params.holeRowCount > 0 ? params.holeRowCount : 1000;
      double zTop = params.height - params.holeSpacingV * 0.5; // 顶部留安装余量
      int n = 0;
      for (double z = params.firstHoleOffset + holeLen / 2;
           z + holeLen / 2 <= zTop && n < maxCount;
           z += params.holeSpacingV, ++n) {
        double curW = b + (t - b) * z / params.height;
        double holeR = params.holeDiameter * curW / b / 2;
        double segZ = (holeLen - params.holeDiameter) * curW / b; // 长圆孔直线段
        TopoDS_Shape h = BRepPrimAPI_MakeCylinder(
                             gp_Ax2(gp_Pnt(-thinW, 0, z - segZ / 2), gp::DX(), gp::DZ()),
                             holeR, curW * 4)
                             .Shape();
        if (segZ > Precision::Confusion()) {
          h = BRepAlgoAPI_Fuse(h, BRepPrimAPI_MakeCylinder(
                  gp_Ax2(gp_Pnt(-thinW, 0, z + segZ / 2), gp::DX(), gp::DZ()),
                  holeR, curW * 4).Shape()).Shape();
          h = BRepAlgoAPI_Fuse(h, BRepPrimAPI_MakeBox(
                  gp_Pnt(-thinW, -holeR, z - segZ / 2), thinW * 2, holeR * 2,
                  segZ).Shape()).Shape();
        }
        mast = BRepAlgoAPI_Cut(mast, h).Shape();
      }
    }
  }
  return mast;
}
TopoDS_Shape create_concrete_mast(const concrete_mast_params &params,
                                  const gp_Pnt &baseCenter,
                                  const gp_Dir &axisDirection) {
  TopoDS_Shape s = create_concrete_mast(params);
  gp_Ax3 src(gp::Origin(), gp::DZ()), tgt(baseCenter, axisDirection);
  gp_Trsf tr;
  tr.SetTransformation(tgt, src);
  return BRepBuilderAPI_Transform(s, tr).Shape();
}

// =========================================================================
// 13. OCS Foundation (支柱基础)
// =========================================================================
TopoDS_Shape create_ocs_foundation(const ocs_foundation_params &params) {
  if (params.height <= 0)
    throw Standard_ConstructionError("Height must be positive");
  TopoDS_Shape foundation;
  switch (params.type) {
  case foundation_type::FLANGE:
    // Body: top at Z=0, extends downward to -height
    foundation =
        BRepPrimAPI_MakeBox(gp_Pnt(-params.length / 2, -params.width / 2,
                                   -params.height),
                            params.length, params.width, params.height)
            .Shape();
    if (params.flangeThickness > 0) {
      double fs = std::min(params.length, params.width) * 0.8;
      foundation = BRepAlgoAPI_Fuse(
                       foundation,
                       BRepPrimAPI_MakeBox(
                           gp_Pnt(-fs / 2, -fs / 2, -params.flangeThickness),
                           fs, fs, params.flangeThickness)
                           .Shape())
                       .Shape();
    }
    if (params.anchorCount > 0 && params.anchorDiameter > 0) {
      double hs = params.anchorSpacing / 2, br = params.anchorDiameter / 2;
      double boltLen = params.height + params.anchorLength;
      for (int ax = -1; ax <= 1; ax += 2)
        for (int ay = -1; ay <= 1; ay += 2) {
          if (params.anchorCount >= 4 || (ax == -1 && ay == -1))
            foundation =
                BRepAlgoAPI_Fuse(
                    foundation,
                    BRepPrimAPI_MakeCylinder(
                        gp_Ax2(gp_Pnt(ax * hs, ay * hs, 0),
                               gp_Dir(0, 0, -1)),
                        br, boltLen)
                        .Shape())
                    .Shape();
        }
    }
    break;
  case foundation_type::DIRECT_BURIED: {
    double r = std::min(params.length, params.width) / 2;
    foundation = BRepPrimAPI_MakeCylinder(
                     gp_Ax2(gp_Pnt(0, 0, -params.height), gp::DZ()), r,
                     params.height)
                     .Shape();
    break;
  }
  case foundation_type::BORED_PILE: {
    double pr = std::min(params.length, params.width) / 2;
    foundation = BRepPrimAPI_MakeCylinder(
                     gp_Ax2(gp_Pnt(0, 0, -params.height), gp::DZ()), pr,
                     params.height)
                     .Shape();
    double flareH = params.height * 0.15;
    gp_Pnt flareBase(0, 0, -params.height * 0.15);
    foundation = BRepAlgoAPI_Fuse(
                     foundation,
                     BRepPrimAPI_MakeCone(
                         gp_Ax2(flareBase, gp::DZ()),
                         pr * 1.3, pr, flareH)
                         .Shape())
                     .Shape();
    break;
  }
  default: {
    double r = std::min(params.length, params.width) / 2;
    foundation = BRepPrimAPI_MakeCylinder(
                     gp_Ax2(gp_Pnt(0, 0, -params.height), gp::DZ()), r,
                     params.height)
                     .Shape();
    break;
  }
  }
  return foundation;
}
TopoDS_Shape create_ocs_foundation(const ocs_foundation_params &params,
                                   const gp_Pnt &position, const gp_Dir &normal,
                                   const gp_Dir &xDir) {
  TopoDS_Shape s = create_ocs_foundation(params);
  gp_Ax3 src(gp::Origin(), gp::DZ(), gp::DX()), tgt(position, normal, xDir);
  gp_Trsf tr;
  tr.SetTransformation(tgt, src);
  return BRepBuilderAPI_Transform(s, tr).Shape();
}

// =========================================================================
// 14. Dropper (吊弦)
// Origin: top of upper crimp tube, extends downward in -Z.
// Assembly: upper crimp → upper thimble → upper loop arc
//          → main wire → lower loop arc → lower thimble → lower crimp
// Loop arcs use 3-point circular arcs (no BSpline twisting).
// =========================================================================

namespace {

} // anonymous namespace

TopoDS_Shape create_dropper(const dropper_params &params) {
  if (params.length <= 0 || params.wireDiameter <= 0)
    throw Standard_ConstructionError("Invalid dimensions");

  BRep_Builder builder;
  TopoDS_Compound compound;
  builder.MakeCompound(compound);

  const double wr = params.wireDiameter / 2.0;
  const double cL = params.clampLength > 0 ? params.clampLength : 60;
  const double cW = params.clampWidth > 0 ? params.clampWidth : 40;
  const double cT = params.clampThickness > 0 ? params.clampThickness : 6;
  const double gripR = 8.0; // 被夹导线半径 (承力索/接触线)

  // D 型整体吊弦 (沿 -Z 悬挂):
  //   线夹 → 挂环耳板 → 心形护环 → 钳压管 → 吊弦线 → 钳压管 → 心形护环 → 线夹
  //   导电型侧面带载流环

  // 心形护环 (鸡心形: 上尖下圆水滴环, XZ 平面)
  // 心形护环 (样条构建不对称耳朵形: 顶尖一侧饱满, 底部偏圆非半圆)
  auto thimble = [&](double zc) {
    double tw = wr * 3.0, th = wr * 4.0, tk = wr * 1.6;
    auto ringWire = [&](double s, double y) {
      // 耳朵形轮廓: 顶点 → 右肩 → 右腹(饱满) → 右底 → 底(偏心) → 左底 → 左腹 → 左肩
      std::vector<gp_Pnt> pts = {
          gp_Pnt(0, y, zc + th * s),
          gp_Pnt(tw * 0.82 * s, y, zc + th * 0.58 * s),
          gp_Pnt(tw * s, y, zc + th * 0.12 * s),
          gp_Pnt(tw * 0.86 * s, y, zc - tw * 0.5 * s),
          gp_Pnt(tw * 0.18 * s, y, zc - tw * 0.92 * s),
          gp_Pnt(-tw * 0.62 * s, y, zc - tw * 0.68 * s),
          gp_Pnt(-tw * 0.92 * s, y, zc + th * 0.05 * s),
          gp_Pnt(-tw * 0.62 * s, y, zc + th * 0.62 * s),
      };
      Handle(TColgp_HArray1OfPnt) arr = new TColgp_HArray1OfPnt(1, (int)pts.size());
      for (size_t i = 0; i < pts.size(); ++i) arr->SetValue((int)(i + 1), pts[i]);
      GeomAPI_Interpolate interp(arr, Standard_True, 1e-5); // 周期闭合样条
      interp.Perform();
      return BRepBuilderAPI_MakeWire(
          BRepBuilderAPI_MakeEdge(interp.Curve()).Edge()).Wire();
    };
    TopoDS_Shape o = BRepPrimAPI_MakePrism(
        BRepBuilderAPI_MakeFace(ringWire(1.0, -tk / 2)).Face(),
        gp_Vec(0, tk, 0)).Shape();
    TopoDS_Shape in = BRepPrimAPI_MakePrism(
        BRepBuilderAPI_MakeFace(ringWire(0.55, -tk / 2 - 1)).Face(),
        gp_Vec(0, tk + 2, 0)).Shape();
    return BRepAlgoAPI_Cut(o, in).Shape();
  };
  // 钳压管 (多节肋纹压接管, 3 节)
  auto crimp = [&](double zTop) {
    BRep_Builder b; TopoDS_Compound c; b.MakeCompound(c);
    double seg = wr * 2.2;
    for (int k = 0; k < 3; ++k) {
      double rr = (k == 1) ? wr * 1.6 : wr * 1.9;
      b.Add(c, BRepPrimAPI_MakeCylinder(
          gp_Ax2(gp_Pnt(0, 0, zTop - seg * (k + 1)), gp::DZ()), rr, seg).Shape());
    }
    return TopoDS_Shape(c);
  };
  // 挂环耳板 (带销孔; dir=+1 向上伸出, -1 向下伸出)
  auto earPlate = [&](double zc, int dir) {
    double z0 = dir > 0 ? zc - cW * 0.05 : zc - cW * 0.35;
    TopoDS_Shape ear = BRepPrimAPI_MakeBox(
        gp_Pnt(-cT / 2, -cT, z0), cT, cT * 2, cW * 0.4).Shape();
    double hz = zc + dir * cW * 0.15;
    ear = BRepAlgoAPI_Cut(ear, BRepPrimAPI_MakeCylinder(
        gp_Ax2(gp_Pnt(-cT / 2 - 1, 0, hz), gp::DX()), wr * 1.2,
        cT + 2).Shape()).Shape();
    return ear;
  };
  // 线夹 (夹板×2 + 螺栓×2 + 六角螺母)
  auto clamp = [&](double zc) {
    for (int s = -1; s <= 1; s += 2) {
      double y0 = s > 0 ? gripR : -gripR - cT;
      builder.Add(compound, BRepPrimAPI_MakeBox(
          gp_Pnt(-cL / 2, y0, zc - cW / 2), cL, cT, cW).Shape());
    }
    for (int s = -1; s <= 1; s += 2) {
      double bx = s * cL / 4;
      builder.Add(compound, BRepPrimAPI_MakeCylinder(
          gp_Ax2(gp_Pnt(bx, -gripR - cT, zc), gp::DY()), cT * 0.6,
          2 * (gripR + cT)).Shape());
      BRepBuilderAPI_MakePolygon hex;
      for (int k = 0; k < 6; ++k) {
        double a = k * M_PI / 3.0;
        hex.Add(gp_Pnt(bx + cT * std::cos(a), gripR + cT, zc + cT * std::sin(a)));
      }
      hex.Close();
      builder.Add(compound, BRepPrimAPI_MakePrism(
          BRepLib_MakeFace(hex.Wire()).Face(), gp_Vec(0, cT * 0.8, 0)).Shape());
    }
  };

  // 上端: 承力索吊弦线夹 → 耳板销孔挂心形护环 → 钳压管
  const double th = wr * 4.0; // 护环高 (与 thimble 内一致)
  // 钳压管端部 D 形回绕: 双股吊弦线 U 形绕过心形护环底部
  auto wrapLoop = [&](double zStrand, double zBend) {
    double r = wr * 3.0 + wr;
    // 耳朵状不对称回弯: 一股斜出饱满, 弯底偏心, 另一股陡收 (非标准半圆)
    std::vector<gp_Pnt> pts = {
        gp_Pnt(-r * 0.85, 0, zStrand),
        gp_Pnt(-r * 1.08, 0, (zStrand + zBend) / 2),
        gp_Pnt(-r * 0.52, 0, zBend - r * 0.58),
        gp_Pnt(r * 0.42, 0, zBend - r * 0.52),
        gp_Pnt(r * 0.98, 0, (zStrand + zBend) / 2 + wr),
        gp_Pnt(r * 0.85, 0, zStrand),
    };
    Handle(TColgp_HArray1OfPnt) arr = new TColgp_HArray1OfPnt(1, (int)pts.size());
    for (size_t i = 0; i < pts.size(); ++i) arr->SetValue((int)(i + 1), pts[i]);
    GeomAPI_Interpolate interp(arr, Standard_False, 1e-5);
    interp.Perform();
    if (!interp.IsDone()) return;
    TopoDS_Wire pathW = BRepBuilderAPI_MakeWire(
        BRepBuilderAPI_MakeEdge(interp.Curve()).Edge()).Wire();
    gp_Dir tan(pts[1].XYZ() - pts[0].XYZ());
    TopoDS_Wire secW = BRepBuilderAPI_MakeWire(
        BRepBuilderAPI_MakeEdge(gp_Circ(gp_Ax2(pts[0], tan), wr)).Edge()).Wire();
    BRepOffsetAPI_MakePipe pipe(pathW, BRepLib_MakeFace(secW).Face());
    pipe.Build();
    if (pipe.IsDone())
      builder.Add(compound, pipe.Shape());
  };

  clamp(-cW / 2);
  builder.Add(compound, earPlate(-cW / 2, -1));
  double holeT = -cW / 2 - cW * 0.15;          // 上耳板销孔
  double zcT = holeT - th * 0.8;               // 护环顶对正销孔
  builder.Add(compound, thimble(zcT));
  // 链序: 护环 → D形回绕(U弯在护环底) → 钳压管(在回绕下方) → 调节螺栓 → 吊弦线
  const double wrapR = wr * 3.0 + wr;          // 回弯半径 (与 wrapLoop 一致)
  double topBendZ = zcT - wr * 3.0 + 1;        // U弯中心 (护环底)
  double crimpTopT = topBendZ - wrapR + 2;     // 钳压管顶 (回绕下方搭接)
  builder.Add(compound, crimp(crimpTopT));
  wrapLoop(crimpTopT, topBendZ);               // 上端 D 形回绕
  // 调节固定螺栓 (贴心形护环下方, 横向穿过 D 形回绕双股 + 六角螺母)
  {
    double bz = topBendZ + wr * 0.5;           // 贴护环底部, 压住回绕双股
    builder.Add(compound, BRepPrimAPI_MakeCylinder(
        gp_Ax2(gp_Pnt(0, -16, bz), gp::DY()), wr * 1.5, 32).Shape());
    BRepBuilderAPI_MakePolygon hex;
    for (int k = 0; k < 6; ++k) {
      double a = k * M_PI / 3.0;
      hex.Add(gp_Pnt(wr * 2.6 * std::cos(a), 16, bz + wr * 2.6 * std::sin(a)));
    }
    hex.Close();
    builder.Add(compound, BRepPrimAPI_MakePrism(
        BRepLib_MakeFace(hex.Wire()).Face(), gp_Vec(0, wr * 2, 0)).Shape());
  }

  // 下端: 接触线吊弦线夹 → 耳板(向上)销孔挂心形护环 → D形回绕 → 钳压管
  clamp(-params.length + cW / 2);
  builder.Add(compound, earPlate(-params.length + cW / 2, +1));
  double holeB = -params.length + cW / 2 + cW * 0.15;
  double zcB = holeB + th * 0.6;               // 护环底对正销孔
  builder.Add(compound, thimble(zcB));
  double botBendZ = zcB - wr * 3.0 + 1;        // U弯中心 (护环底下方)
  double crimpBotB = botBendZ + wrapR - 2;     // 钳压管底
  builder.Add(compound, crimp(crimpBotB + wr * 6.6));
  wrapLoop(crimpBotB, botBendZ);               // 下端 D 形回绕

  // 吊弦线 (两钳压管之间)
  double topZ = crimpTopT - wr * 6.6;
  double botZ = crimpBotB + wr * 6.6;
  if (topZ > botZ)
    builder.Add(compound, BRepPrimAPI_MakeCylinder(
        gp_Ax2(gp_Pnt(0, 0, botZ), gp::DZ()), wr, topZ - botZ).Shape());

  // 载流环 (导电型): 仅两端松弛泪滴环 (中部为单根吊弦线, 无并行载流线)
  // 泪滴环为不对称自然弯 (非工整半圆), 收回处加线箍
  if (params.conductive) {
    auto pipePts = [&](std::vector<gp_Pnt> pts) {
      Handle(TColgp_HArray1OfPnt) arr = new TColgp_HArray1OfPnt(1, (int)pts.size());
      for (size_t i = 0; i < pts.size(); ++i) arr->SetValue((int)(i + 1), pts[i]);
      GeomAPI_Interpolate interp(arr, Standard_False, 1e-5);
      interp.Perform();
      if (!interp.IsDone()) return;
      TopoDS_Wire pathW = BRepBuilderAPI_MakeWire(
          BRepBuilderAPI_MakeEdge(interp.Curve()).Edge()).Wire();
      gp_Dir tan(pts[1].XYZ() - pts[0].XYZ());
      TopoDS_Wire secW = BRepBuilderAPI_MakeWire(
          BRepBuilderAPI_MakeEdge(gp_Circ(gp_Ax2(pts[0], tan), wr * 1.4)).Edge()).Wire();
      BRepOffsetAPI_MakePipe pipe(pathW, BRepLib_MakeFace(secW).Face());
      pipe.Build();
      if (pipe.IsDone())
        builder.Add(compound, pipe.Shape());
    };
    // 线箍 (泪滴环收回处, 捆扎环端与吊弦线)
    auto wireClip = [&](double zc) {
      builder.Add(compound, BRepPrimAPI_MakeCylinder(
          gp_Ax2(gp_Pnt(0, 0, zc - wr * 2.5), gp::DZ()), wr * 2.2, wr * 5).Shape());
      builder.Add(compound, BRepPrimAPI_MakeCylinder(
          gp_Ax2(gp_Pnt(0, 0, zc - wr * 0.8), gp::DZ()), wr * 2.5, wr * 1.6).Shape());
    };
    // 上端松弛泪滴环: 线夹侧 → 不对称下垂 → 收回处线箍 (收回点近端部)
    {
      pipePts({gp_Pnt(cL / 2, 0, -cW),
               gp_Pnt(cL / 2 + 66, 0, -cW - 28),
               gp_Pnt(cL / 2 + 74, 0, -cW - 68),
               gp_Pnt(cL / 2 + 36, 0, -cW - 92),
               gp_Pnt(wr * 2, 0, -cW - 100)});
      wireClip(-cW - 100);
    }
    // 下端松弛泪滴环: 线夹侧 → 不对称上提 → 收回处线箍 (收回点近端部)
    {
      pipePts({gp_Pnt(cL / 2, 0, -params.length + cW),
               gp_Pnt(cL / 2 + 54, 0, -params.length + cW + 26),
               gp_Pnt(cL / 2 + 60, 0, -params.length + cW + 58),
               gp_Pnt(cL / 2 + 30, 0, -params.length + cW + 84),
               gp_Pnt(wr * 2, 0, -params.length + cW + 96)});
      wireClip(-params.length + cW + 96);
    }
  }

  return compound;
}

TopoDS_Shape create_dropper(const dropper_params &params,
                            const gp_Pnt &topPoint, const gp_Dir &direction) {
  TopoDS_Shape s = create_dropper(params);
  gp_Ax3 src(gp::Origin(), gp::DZ()), tgt(topPoint, direction);
  gp_Trsf tr;
  tr.SetTransformation(tgt, src);
  return BRepBuilderAPI_Transform(s, tr).Shape();
}

// =========================================================================
// 15. Cantilever Base (腕臂底座)
// =========================================================================
TopoDS_Shape create_cantilever_base(const cantilever_base_params &params) {
  if (params.length <= 0 || params.width <= 0 || params.height <= 0)
    throw Standard_ConstructionError("Invalid dimensions");
  TopoDS_Shape base =
      BRepPrimAPI_MakeBox(gp_Pnt(-params.length / 2, -params.width / 2, 0),
                          params.length, params.width, params.height)
          .Shape();
  if (params.boltDiameter > 0 && params.boltCount > 0) {
    double hr = params.boltDiameter / 2, hs = params.boltSpacing / 2;
    int cols = std::max(1, params.boltCount / 2);
    for (int i = 0; i < cols; ++i)
      for (int j = 0; j < 2; ++j) {
        double x = (i - (cols - 1) / 2.0) * params.boltSpacing,
               y = (j == 0) ? -hs : hs;
        base = BRepAlgoAPI_Cut(base, BRepPrimAPI_MakeCylinder(
                                         gp_Ax2(gp_Pnt(x, y, -1), gp::DZ()), hr,
                                         params.height + 2)
                                         .Shape())
                   .Shape();
      }
  }
  return base;
}
TopoDS_Shape create_cantilever_base(const cantilever_base_params &params,
                                    const gp_Pnt &position,
                                    const gp_Dir &normal, const gp_Dir &upDir) {
  TopoDS_Shape s = create_cantilever_base(params);
  gp_Ax3 src(gp::Origin(), gp::DZ(), gp::DX()), tgt(position, upDir, normal);
  gp_Trsf tr;
  tr.SetTransformation(tgt, src);
  return BRepBuilderAPI_Transform(s, tr).Shape();
}

// =========================================================================
// 16. Messenger Wire Saddle (承力索座)
// =========================================================================
TopoDS_Shape create_mw_saddle(const mw_saddle_params &params) {
  if (params.length <= 0 || params.width <= 0)
    throw Standard_ConstructionError("Invalid dimensions");
  TopoDS_Shape body =
      BRepPrimAPI_MakeBox(gp_Pnt(-params.length / 2, -params.width / 2, 0),
                          params.length, params.width, params.height)
          .Shape();
  if (params.grooveRadius > 0)
    body =
        BRepAlgoAPI_Cut(body, BRepPrimAPI_MakeCylinder(
                                  gp_Ax2(gp_Pnt(0, 0, params.height), gp::DY()),
                                  params.grooveRadius, params.width + 2)
                                  .Shape())
            .Shape();
  if (params.boltDiameter > 0) {
    double hr = params.boltDiameter / 2, hl = params.length * 0.3;
    body = BRepAlgoAPI_Cut(body, BRepPrimAPI_MakeCylinder(
                                     gp_Ax2(gp_Pnt(-hl, 0, -1), gp::DZ()), hr,
                                     params.height + 2)
                                     .Shape())
               .Shape();
    body = BRepAlgoAPI_Cut(body, BRepPrimAPI_MakeCylinder(
                                     gp_Ax2(gp_Pnt(hl, 0, -1), gp::DZ()), hr,
                                     params.height + 2)
                                     .Shape())
               .Shape();
  }
  return body;
}
TopoDS_Shape create_mw_saddle(const mw_saddle_params &params,
                              const gp_Pnt &position, const gp_Dir &normal,
                              const gp_Dir &xDir) {
  TopoDS_Shape s = create_mw_saddle(params);
  gp_Ax3 src(gp::Origin(), gp::DZ(), gp::DX()), tgt(position, normal, xDir);
  gp_Trsf tr;
  tr.SetTransformation(tgt, src);
  return BRepBuilderAPI_Transform(s, tr).Shape();
}

// =========================================================================
// 17. Balance Weight (坠砣)
// =========================================================================
TopoDS_Shape create_balance_weight(const balance_weight_params &params) {
  if (params.width <= 0 || params.height <= 0)
    throw Standard_ConstructionError("Invalid dimensions");
  // 圆形坠砣: 铸铁圆片 + 中心孔 + 径向开口槽 (侧向穿杆)
  double R = params.width / 2.0;
  double H = params.height;
  TopoDS_Shape b =
      BRepPrimAPI_MakeCylinder(gp_Ax2(gp::Origin(), gp::DZ()), R, H).Shape();
  // 中心孔
  if (params.centerHoleDiameter > 0) {
    double hr = params.centerHoleDiameter / 2;
    b = BRepAlgoAPI_Cut(b, BRepPrimAPI_MakeCylinder(
                               gp_Ax2(gp_Pnt(0, 0, -1), gp::DZ()), hr, H + 2)
                               .Shape())
            .Shape();
    // 径向开口槽 (从中心孔通到外缘)
    b = BRepAlgoAPI_Cut(b, BRepPrimAPI_MakeBox(
                               gp_Pnt(0, -hr * 0.6, -1), R + 1, hr * 1.2, H + 2)
                               .Shape())
            .Shape();
  }
  // 上下边缘倒圆
  double fr = std::min(R, H) * 0.08;
  if (fr > Precision::Confusion()) {
    BRepFilletAPI_MakeFillet fillet(b);
    for (TopExp_Explorer ex(b, TopAbs_EDGE); ex.More(); ex.Next()) {
      TopoDS_Edge e = TopoDS::Edge(ex.Current());
      gp_Pnt p1 = BRep_Tool::Pnt(TopExp::FirstVertex(e)),
             p2 = BRep_Tool::Pnt(TopExp::LastVertex(e));
      // 仅外缘水平圆边 (上下面的外圆)
      if (std::abs(p1.Z() - p2.Z()) < Precision::Confusion() &&
          std::abs(p1.X() - p2.X()) > Precision::Confusion())
        fillet.Add(fr, e);
    }
    fillet.Build();
    if (fillet.IsDone())
      b = fillet.Shape();
  }
  return b;
}
TopoDS_Shape create_balance_weight(const balance_weight_params &params,
                                   const gp_Pnt &position, const gp_Dir &normal,
                                   const gp_Dir &xDir) {
  TopoDS_Shape s = create_balance_weight(params);
  gp_Ax3 src(gp::Origin(), gp::DZ(), gp::DX()), tgt(position, normal, xDir);
  gp_Trsf tr;
  tr.SetTransformation(tgt, src);
  return BRepBuilderAPI_Transform(s, tr).Shape();
}

// =========================================================================
// 18. Weight Rod (坠砣杆)
// =========================================================================
TopoDS_Shape create_weight_rod(const weight_rod_params &params) {
  if (params.rodDiameter <= 0 || params.rodLength <= 0)
    throw Standard_ConstructionError("Invalid dimensions");
  double rr = params.rodDiameter / 2;
  TopoDS_Shape rod = BRepPrimAPI_MakeCylinder(gp_Ax2(gp::Origin(), gp::DZ()),
                                              rr, params.rodLength)
                         .Shape();
  if (params.topHoleDiameter > 0)
    rod =
        BRepAlgoAPI_Cut(
            rod, BRepPrimAPI_MakeCylinder(
                     gp_Ax2(gp_Pnt(0, 0, params.rodLength - rr * 3), gp::DY()),
                     params.topHoleDiameter / 2, rr * 4)
                     .Shape())
            .Shape();
  return rod;
}
TopoDS_Shape create_weight_rod(const weight_rod_params &params,
                               const gp_Pnt &position,
                               const gp_Dir &axisDirection) {
  TopoDS_Shape s = create_weight_rod(params);
  gp_Ax3 src(gp::Origin(), gp::DZ()), tgt(position, axisDirection);
  gp_Trsf tr;
  tr.SetTransformation(tgt, src);
  return BRepBuilderAPI_Transform(s, tr).Shape();
}

// =========================================================================
// 19. Anchor Fitting (下锚金具)
// =========================================================================
TopoDS_Shape create_anchor_fitting(const anchor_fitting_params &params) {
  if (params.length <= 0 || params.diameter <= 0)
    throw Standard_ConstructionError("Invalid dimensions");
  double R = params.diameter / 2;
  if (params.type == anchor_fitting_type::ROD_AND_RING) {
    // 杵环杆: 圆钢杆 + 杵头 + U 形环
    BRep_Builder b; TopoDS_Compound c; b.MakeCompound(c);
    // 杆体 (留环连接段)
    double rodL = params.length - R * 2.5;
    b.Add(c, BRepPrimAPI_MakeCylinder(gp_Ax2(gp::Origin(), gp::DX()), R, rodL).Shape());
    // 杵头 (球头)
    b.Add(c, BRepPrimAPI_MakeSphere(gp_Ax2(gp_Pnt(rodL, 0, 0), gp::DX()), R * 1.5).Shape());
    // 环: 竖直面内 torus, 与杆端颈接
    double ringR = R * 1.6, ringT = R * 0.5;
    double ringX = -ringR - R * 0.2;
    b.Add(c, BRepPrimAPI_MakeTorus(
        gp_Ax2(gp_Pnt(ringX, 0, 0), gp::DY()), ringR, ringT).Shape());
    // 环-杆连接颈
    b.Add(c, BRepPrimAPI_MakeCylinder(
        gp_Ax2(gp_Pnt(-R * 0.2, 0, 0), gp::DX()), R * 0.7, R * 0.4).Shape());
    // 统一原点: 连接点 (环心, 与拉线/线索连接处) 移至原点, 杆体沿 +X 伸展
    gp_Trsf mv; mv.SetTranslation(gp_Vec(-ringX, 0, 0));
    return BRepBuilderAPI_Transform(c, mv).Shape();
  } else if (params.type == anchor_fitting_type::DOUBLE_EAR) {
    // 双耳连接器: 中部连接体 + 两端 U 形叉 (双夹板 + 销孔)
    BRep_Builder b; TopoDS_Compound c; b.MakeCompound(c);
    double bodyL = params.length * 0.4;
    double forkL = params.length * 0.3;
    double gap = R * 0.9;                    // 叉口半宽
    double earT = R * 0.55;                  // 耳板厚
    // 中部连接体 (圆角方块)
    TopoDS_Shape body = BRepPrimAPI_MakeBox(
        gp_Pnt(-bodyL / 2, -R, -R), bodyL, R * 2, R * 2).Shape();
    b.Add(c, body);
    for (int side = -1; side <= 1; side += 2) {
      double x0 = side > 0 ? bodyL / 2 : -bodyL / 2 - forkL;
      for (int e = -1; e <= 1; e += 2) {
        double y0 = e > 0 ? gap : -gap - earT;
        TopoDS_Shape ear = BRepPrimAPI_MakeBox(
            gp_Pnt(x0, y0, -R), forkL, earT, R * 2).Shape();
        // 耳端倒圆: 用圆柱端头近似
        ear = BRepAlgoAPI_Fuse(ear, BRepPrimAPI_MakeCylinder(
            gp_Ax2(gp_Pnt(x0 + forkL, y0, 0), gp::DY()), R, earT).Shape()).Shape();
        b.Add(c, ear);
      }
      // 销孔 (贯穿双耳, 沿 Y)
      double px = side > 0 ? bodyL / 2 + forkL * 0.6 : -bodyL / 2 - forkL * 0.4;
      b.Add(c, BRepPrimAPI_MakeCylinder(
          gp_Ax2(gp_Pnt(px, 0, 0), gp::DY()), R * 0.5, gap + earT).Shape());
    }
    // 统一原点: 连接点 (-X 侧销孔, 与拉线/线索连接处) 移至原点, 本体沿 +X 伸展
    gp_Trsf mv; mv.SetTranslation(gp_Vec(bodyL / 2 + forkL * 0.4, 0, 0));
    return BRepBuilderAPI_Transform(c, mv).Shape();
  } else {
    // 楔形线夹: 锥形线夹体 + 导线弧槽 + 楔块
    // 原点约定: 连接点 (线索入口, 底面中心/导线槽轴线) 已在原点, 线夹体沿 +Z 伸展
    BRep_Builder b; TopoDS_Compound c; b.MakeCompound(c);
    gp_Pnt bp[4] = {{-R, -R, 0}, {R, -R, 0}, {R, R, 0}, {-R, R, 0}};
    BRepOffsetAPI_ThruSections gen(Standard_True);
    gen.AddWire(
        BRepBuilderAPI_MakePolygon(bp[0], bp[1], bp[2], bp[3], Standard_True));
    gp_Pnt tp[4] = {{-R * 0.7, -R * 0.7, params.length},
                    {R * 0.7, -R * 0.7, params.length},
                    {R * 0.7, R * 0.7, params.length},
                    {-R * 0.7, R * 0.7, params.length}};
    gen.AddWire(
        BRepBuilderAPI_MakePolygon(tp[0], tp[1], tp[2], tp[3], Standard_True));
    gen.Build();
    TopoDS_Shape body = gen.Shape();
    // 导线槽: 底面半圆弧槽 (沿 Z)
    body = BRepAlgoAPI_Cut(body, BRepPrimAPI_MakeCylinder(
        gp_Ax2(gp_Pnt(0, 0, -1), gp::DZ()), R * 0.55, params.length + 2).Shape()).Shape();
    b.Add(c, body);
    // 楔块: 从侧面插入的小楔台
    gp_Pnt wb[4] = {{R * 0.3, -R * 0.5, params.length * 0.15},
                    {R * 1.2, -R * 0.5, params.length * 0.15},
                    {R * 1.2, R * 0.5, params.length * 0.15},
                    {R * 0.3, R * 0.5, params.length * 0.15}};
    gp_Pnt wt[4] = {{R * 0.35, -R * 0.45, params.length * 0.75},
                    {R * 1.0, -R * 0.45, params.length * 0.75},
                    {R * 1.0, R * 0.45, params.length * 0.75},
                    {R * 0.35, R * 0.45, params.length * 0.75}};
    BRepOffsetAPI_ThruSections wgen(Standard_True);
    wgen.AddWire(BRepBuilderAPI_MakePolygon(wb[0], wb[1], wb[2], wb[3], Standard_True));
    wgen.AddWire(BRepBuilderAPI_MakePolygon(wt[0], wt[1], wt[2], wt[3], Standard_True));
    wgen.Build();
    b.Add(c, wgen.Shape());
    return c;
  }
}
TopoDS_Shape create_anchor_fitting(const anchor_fitting_params &params,
                                   const gp_Pnt &position,
                                   const gp_Dir &direction,
                                   const gp_Dir &upDir) {
  TopoDS_Shape s = create_anchor_fitting(params);
  gp_Ax3 src(gp::Origin(), gp::DZ(), gp::DX()), tgt(position, upDir, direction);
  gp_Trsf tr;
  tr.SetTransformation(tgt, src);
  return BRepBuilderAPI_Transform(s, tr).Shape();
}

// =========================================================================
// 20. Crossing (线岔)
// =========================================================================
namespace {
// 线岔局部模型: 主线沿 +X, 支线在 XY 平面内与主线夹角 alpha (支线高出 heightDiff)
// 限制管位于两接触线交叉点上方, 两端线夹分别固定到两支接触线上;
// 线夹到交叉点的距离 s 由交角与限制管长度决定: L = 2*s*sin(alpha/2)
TopoDS_Shape build_crossing_local(const crossing_params &params, double alpha) {
  double pr = params.pipeDiameter / 2, wr = params.wireDiameter / 2;
  double L = params.limitPipeLength;
  double hd = params.heightDiff;
  // 交角限制在合理范围, 避免退化
  alpha = std::max(5 * M_PI / 180, std::min(alpha, 175 * M_PI / 180));
  gp_Dir mainD(1, 0, 0);
  gp_Dir brD(cos(alpha), sin(alpha), 0);
  double s = L / (2 * sin(alpha / 2));
  // 接触线展示长度: 覆盖线夹位置并外延, 小交角时封顶避免过长
  double wl = 2 * std::min(s + 500.0, 2.0 * L);
  // 限制管抬高量: 线夹高度
  double clear = wr + 60.0;

  BRep_Builder bld;
  TopoDS_Compound cmp;
  bld.MakeCompound(cmp);

  // 两支接触线 (主线 z=0, 支线 z=heightDiff)
  bld.Add(cmp, BRepPrimAPI_MakeCylinder(
                   gp_Ax2(gp_Pnt(-wl / 2, 0, 0), mainD), wr, wl).Shape());
  bld.Add(cmp, BRepPrimAPI_MakeCylinder(
                   gp_Ax2(gp_Pnt((brD.XYZ()) * (-wl / 2))
                              .Translated(gp_Vec(0, 0, hd)),
                          brD), wr, wl).Shape());

  // 线夹位置: 两接触线上距交叉点 s 处
  gp_Pnt p1(mainD.XYZ() * s);
  gp_Pnt p2 = gp_Pnt(brD.XYZ() * s).Translated(gp_Vec(0, 0, hd));

  // 限制管 (空心圆管) 横跨两接触线, 位于线夹上方
  gp_Pnt a1 = p1.Translated(gp_Vec(0, 0, clear));
  gp_Pnt a2 = p2.Translated(gp_Vec(0, 0, clear));
  gp_Vec axis(a1, a2);
  double pipeLen = axis.Magnitude();
  gp_Ax2 pipeAx(a1, gp_Dir(axis));
  TopoDS_Shape pipe =
      BRepPrimAPI_MakeCylinder(pipeAx, pr * 2, pipeLen).Shape();
  if (pr > 0)
    pipe = BRepAlgoAPI_Cut(
               pipe, BRepPrimAPI_MakeCylinder(pipeAx, pr, pipeLen).Shape())
               .Shape();
  bld.Add(cmp, pipe);

  // 两端线夹: 连接接触线与限制管的短柱
  for (auto &pc : {p1, p2})
    bld.Add(cmp, BRepPrimAPI_MakeCylinder(
                     gp_Ax2(pc, gp::DZ()), wr * 1.5, clear).Shape());
  return cmp;
}
} // anonymous namespace

TopoDS_Shape create_crossing(const crossing_params &params) {
  if (params.limitPipeLength <= 0)
    throw Standard_ConstructionError("Invalid pipe length");
  return build_crossing_local(params, M_PI / 6);
}
TopoDS_Shape create_crossing(const crossing_params &params,
                             const gp_Pnt &crossPoint, const gp_Dir &mainDir,
                             const gp_Dir &branchDir) {
  // 交角由主线/支线方向真实计算
  double alpha = mainDir.Angle(branchDir);
  TopoDS_Shape s = build_crossing_local(params, alpha);
  gp_Dir up = mainDir.Crossed(branchDir);
  if (gp_Vec(up.X(), up.Y(), up.Z()).Magnitude() < Precision::Confusion())
    up = gp::DZ();
  gp_Ax3 src(gp::Origin(), gp::DZ(), gp::DX()), tgt(crossPoint, up, mainDir);
  gp_Trsf tr;
  tr.SetTransformation(tgt, src);
  return BRepBuilderAPI_Transform(s, tr).Shape();
}

// =========================================================================
// 21. Head Span (软横跨)
// =========================================================================
TopoDS_Shape create_head_span(const head_span_params &params) {
  if (params.span <= 0)
    throw Standard_ConstructionError("Span must be positive");
  double span = params.span, cDia = params.crossCatenaryDiameter > 0
                                        ? params.crossCatenaryDiameter
                                        : 10;
  double uDia = params.upperRopeDiameter > 0 ? params.upperRopeDiameter : 8,
         lDia = params.lowerRopeDiameter > 0 ? params.lowerRopeDiameter : 8;
  double sag =
      params.crossCatenarySag > 0 ? params.crossCatenarySag : span * 0.05;

  BRep_Builder builder;
  TopoDS_Compound compound;
  builder.MakeCompound(compound);

  // 布局 (局部: X 跨向 0→span, Z 向上): 横向承力索在上(带弧垂),
  // 上/下部固定绳水平, 悬挂点处直吊弦连接承力索与固定绳
  const double zCat = sag + 2000;    // 承力索端部高
  const double zUp = zCat - sag - 800;  // 上部固定绳 (承力索跨中下方 800)
  const double zLow = zUp - 600;        // 下部固定绳

  // 1. 横向承力索: 上凸弧垂曲线 (复用悬索生成)
  {
    suspension_cable_params sc;
    sc.startPoint = gp_Pnt(0, 0, zCat);
    sc.endPoint = gp_Pnt(span, 0, zCat);
    sc.diameter = cDia;
    sc.sag = sag;
    sc.cableType = suspension_cable_type::CATENARY;
    sc.tension = 0;
    builder.Add(compound, create_suspension_cable(sc));
  }
  // 2. 上/下部固定绳 (水平)
  for (auto &rp : {std::make_pair(zUp, uDia), std::make_pair(zLow, lDia)}) {
    suspension_cable_params sc;
    sc.startPoint = gp_Pnt(0, 0, rp.first);
    sc.endPoint = gp_Pnt(span, 0, rp.first);
    sc.diameter = rp.second;
    sc.sag = 0;
    sc.cableType = suspension_cable_type::FIXED_ROPE;
    sc.tension = 0;
    builder.Add(compound, create_suspension_cable(sc));
  }
  // 3. 直吊弦 (悬挂点: 跨中对称布置)
  int nHP = params.hangPointCount > 0 ? params.hangPointCount : 2;
  double hpSpacing = params.hangPointSpacing > 0 ? params.hangPointSpacing : 4000;
  for (int i = 0; i < nHP; ++i) {
    double x = span / 2 + (i - (nHP - 1) / 2.0) * hpSpacing;
    double t = x / span;
    double zCatAt = zCat - 4 * sag * t * (1 - t); // 承力索抛物线
    // 承力索 → 上部固定绳 的直吊弦
    double drop = zCatAt - zUp;
    if (drop > 50)
      builder.Add(compound, BRepPrimAPI_MakeCylinder(
          gp_Ax2(gp_Pnt(x, 0, zUp), gp::DZ()), 2.5, drop).Shape());
    // 上部固定绳 → 下部固定绳 的连接吊弦
    builder.Add(compound, BRepPrimAPI_MakeCylinder(
        gp_Ax2(gp_Pnt(x, 0, zLow), gp::DZ()), 2.5, zUp - zLow).Shape());
  }
  // 4. 绝缘子串: 两端沿绳方向 (水平, 向支柱侧伸出)
  if (params.insulatorLength > 0) {
    double iL = params.insulatorLength, iD = iL * 0.2;
    rod_insulator_params rip;
    rip.type = rod_insulator_type::SOLID;
    rip.height = iL;
    rip.outerDiameter = iD;
    rip.innerDiameter = 0;
    rip.shedDiameter = iD * 1.5;
    rip.shedSpacing = iL / 5;
    rip.shedCount = 3;
    rip.endFitting = end_fitting_type::FLANGE;
    rip.flangeDiameter = iD * 1.2;
    rip.flangeBoltSpacing = iD * 0.7;
    rip.flangeBoltDiameter = iD * 0.18;
    for (int side = 0; side < 2; ++side) {
      double x = side * span;
      gp_Dir out = side == 0 ? gp_Dir(-1, 0, 0) : gp_Dir(1, 0, 0);
      for (double z : {zCat, zUp, zLow}) {
        gp_Pnt p0(x, 0, z);
        // 绝缘子从绳端向对应支柱侧伸出: 左端朝 -X, 右端朝 +X
        builder.Add(compound, create_rod_insulator(rip, p0, out));
      }
    }
  }
  return compound;
}
TopoDS_Shape create_head_span(const head_span_params &params,
                              const gp_Pnt &leftMast, const gp_Pnt &rightMast,
                              const gp_Dir &upDir) {
  gp_Vec v(leftMast, rightMast);
  double len = v.Magnitude();
  if (len <= Precision::Confusion())
    return create_head_span(params);
  // 按实际跨距重建, 不做整体缩放 (缩放会把绳径/绝缘子一起缩错)
  head_span_params p2 = params;
  p2.span = len;
  TopoDS_Shape s = create_head_span(p2);
  gp_Ax3 src(gp::Origin(), gp::DZ(), gp::DX()), tgt(leftMast, upDir, gp_Dir(v));
  gp_Trsf tr;
  tr.SetTransformation(tgt, src);
  return BRepBuilderAPI_Transform(s, tr).Shape();
}
TopoDS_Shape create_transverse_span(const transverse_span_params &params) {
  if (params.span <= 0 || params.beamHeight <= 0)
    throw Standard_ConstructionError("Dimensions must be positive");

  BRep_Builder builder;
  TopoDS_Compound compound;
  builder.MakeCompound(compound);

  double span = params.span;
  double bh = params.beamHeight, bw = params.beamWidth,
         bt = params.beamThickness;

  if (params.beamType == beam_section_type::TRUSS) {
    int nPanels = std::max(4, (int)(span / 2000));
    double panelLen = span / nPanels;
    double chordR = bw * 0.15, webR = bw * 0.10;
    double camber = span * 0.002;

    auto makeChord = [&](gp_Pnt from, gp_Pnt to, double r) -> TopoDS_Shape {
      gp_Vec v(from, to);
      return BRepPrimAPI_MakeCylinder(gp_Ax2(from, gp_Dir(v)), r, v.Magnitude())
          .Shape();
    };

    std::vector<gp_Pnt> topPts, botPts;
    for (int i = 0; i <= nPanels; ++i) {
      double x = -span / 2 + i * panelLen;
      double t = (double)i / nPanels;
      double cz = camber * (1.0 - 4.0 * (t - 0.5) * (t - 0.5));
      topPts.push_back(gp_Pnt(x, 0, bh + cz));
      botPts.push_back(gp_Pnt(x, 0, cz * 0.3));
    }

    for (int i = 0; i < nPanels; ++i) {
      for (int face = -1; face <= 1; face += 2) {
        double y = face * bw / 2;
        builder.Add(compound,
                    makeChord(gp_Pnt(topPts[i].X(), y, topPts[i].Z()),
                              gp_Pnt(topPts[i + 1].X(), y, topPts[i + 1].Z()),
                              chordR));
        builder.Add(compound,
                    makeChord(gp_Pnt(botPts[i].X(), y, botPts[i].Z()),
                              gp_Pnt(botPts[i + 1].X(), y, botPts[i + 1].Z()),
                              chordR));
        // Verticals
        builder.Add(compound,
                    makeChord(gp_Pnt(topPts[i].X(), y, topPts[i].Z()),
                              gp_Pnt(botPts[i].X(), y, botPts[i].Z()), webR));
        // Z-diagonals
        builder.Add(compound,
                    makeChord(gp_Pnt(botPts[i].X(), y, botPts[i].Z()),
                              gp_Pnt(topPts[i + 1].X(), y, topPts[i + 1].Z()),
                              webR * 0.8));
        builder.Add(compound,
                    makeChord(gp_Pnt(topPts[i].X(), y, topPts[i].Z()),
                              gp_Pnt(botPts[i + 1].X(), y, botPts[i + 1].Z()),
                              webR * 0.8));
      }
      // 上下弦面水平横联 (每隔一节间 X 形交叉) → 空间桁架
      if (i % 2 == 0) {
        for (int lvl = 0; lvl < 2; ++lvl) {
          double z = lvl == 0 ? botPts[i].Z() : topPts[i].Z();
          double zN = lvl == 0 ? botPts[i + 1].Z() : topPts[i + 1].Z();
          builder.Add(compound,
                      makeChord(gp_Pnt(topPts[i].X(), -bw / 2, z),
                                gp_Pnt(topPts[i + 1].X(), bw / 2, zN), webR * 0.6));
          builder.Add(compound,
                      makeChord(gp_Pnt(topPts[i].X(), bw / 2, z),
                                gp_Pnt(topPts[i + 1].X(), -bw / 2, zN), webR * 0.6));
        }
      }
    }
  } else if (params.beamType == beam_section_type::BOX) {
    gp_Pnt b1(-span / 2, -bw / 2, 0), b2(-span / 2, bw / 2, 0),
        b3(-span / 2, bw / 2, bh), b4(-span / 2, -bw / 2, bh);
    TopoDS_Face of =
        BRepLib_MakeFace(
            BRepBuilderAPI_MakePolygon(b1, b2, b3, b4, Standard_True).Wire())
            .Face();
    TopoDS_Shape beam = BRepPrimAPI_MakePrism(of, gp_Vec(span, 0, 0)).Shape();
    if (bt > 0 && bh > 2 * bt && bw > 2 * bt) {
      gp_Pnt i1(-span / 2 - 1, -bw / 2 + bt, bt),
          i2(-span / 2 - 1, bw / 2 - bt, bt);
      gp_Pnt i3(-span / 2 - 1, bw / 2 - bt, bh - bt),
          i4(-span / 2 - 1, -bw / 2 + bt, bh - bt);
      TopoDS_Face inf =
          BRepLib_MakeFace(
              BRepBuilderAPI_MakePolygon(i1, i2, i3, i4, Standard_True).Wire())
              .Face();
      beam =
          BRepAlgoAPI_Cut(
              beam, BRepPrimAPI_MakePrism(inf, gp_Vec(span + 2, 0, 0)).Shape())
              .Shape();
    }
    builder.Add(compound, beam);
  } else if (params.beamType == beam_section_type::H_BEAM_T) {
    TopoDS_Shape web = BRepPrimAPI_MakeBox(gp_Pnt(-span / 2, -bw * 0.15, bt),
                                           span, bw * 0.3, bh - 2 * bt)
                           .Shape();
    TopoDS_Shape lf =
        BRepPrimAPI_MakeBox(gp_Pnt(-span / 2, -bw / 2, 0), span, bw, bt)
            .Shape();
    TopoDS_Shape rf =
        BRepPrimAPI_MakeBox(gp_Pnt(-span / 2, -bw / 2, bh - bt), span, bw, bt)
            .Shape();
    TopoDS_Shape beam = BRepAlgoAPI_Fuse(web, lf).Shape();
    beam = BRepAlgoAPI_Fuse(beam, rf).Shape();
    builder.Add(compound, beam);
  } else {
    // COMBO: upper box + lower truss
    double boxH = bh * 0.4, trussH = bh - boxH;
    gp_Pnt bb1(-span / 2, -bw / 2, trussH), bb2(-span / 2, bw / 2, trussH);
    gp_Pnt bb3(-span / 2, bw / 2, bh), bb4(-span / 2, -bw / 2, bh);
    TopoDS_Face bf = BRepLib_MakeFace(BRepBuilderAPI_MakePolygon(
                                          bb1, bb2, bb3, bb4, Standard_True)
                                          .Wire())
                         .Face();
    builder.Add(compound,
                BRepPrimAPI_MakePrism(bf, gp_Vec(span, 0, 0)).Shape());
    int nPanels = std::max(4, (int)(span / 2000));
    double panelLen = span / nPanels;
    double chordR = bw * 0.1;
    for (int i = 0; i <= nPanels; ++i) {
      double x = -span / 2 + i * panelLen;
      for (int face = -1; face <= 1; face += 2) {
        double y = face * bw / 2;
        gp_Pnt bc(x, y, 0);
        if (i < nPanels) {
          gp_Pnt bcN(-span / 2 + (i + 1) * panelLen, y, 0);
          builder.Add(compound, BRepPrimAPI_MakeCylinder(
                                    gp_Ax2(bc, gp_Dir(bcN.XYZ() - bc.XYZ())),
                                    chordR, panelLen)
                                    .Shape());
          gp_Pnt upN(-span / 2 + (i + 1) * panelLen, y, trussH);
          builder.Add(compound, BRepPrimAPI_MakeCylinder(
                                    gp_Ax2(bc, gp_Dir(upN.XYZ() - bc.XYZ())),
                                    chordR * 0.7, panelLen * 1.2)
                                    .Shape());
        }
      }
    }
  }

  // 两端立柱 (格构式钢柱, 梁底 z=0 向下延伸至基础)
  if (params.mastHeight > 0) {
    double mw = params.mastWidth > 0 ? params.mastWidth : 400;
    steel_mast_params mp{steel_mast_type::LATTICE, params.mastHeight,
                         mw * 0.7, mw, 8, 12, mw * 1.5, 200, 24, 1};
    for (int side = -1; side <= 1; side += 2) {
      TopoDS_Shape mast = create_steel_mast(mp);
      gp_Trsf t;
      t.SetTranslation(gp_Vec(side * span / 2, 0, -params.mastHeight));
      builder.Add(compound, BRepBuilderAPI_Transform(mast, t).Shape());
      // 梁-柱连接节点板
      builder.Add(compound, BRepPrimAPI_MakeBox(
          gp_Pnt(side * span / 2 - mw * 0.4, -bw / 2 - 20, -30),
          mw * 0.8, bw + 40, 30).Shape());
    }
  }

  return compound;
}

TopoDS_Shape create_transverse_span(const transverse_span_params &params,
                                    const gp_Pnt &position,
                                    const gp_Dir &direction,
                                    const gp_Dir &upDir) {
  TopoDS_Shape shape = create_transverse_span(params);
  gp_Dir yDir = upDir.Crossed(direction);
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, upDir, direction);
  gp_Trsf t;
  t.SetTransformation(targetAx3, sourceAx3);
  return BRepBuilderAPI_Transform(shape, t).Shape();
}

// =========================================================================
// 22b. Hanger Post (硬横跨吊柱) TYPE=OCS_HANGER_POST
// =========================================================================
TopoDS_Shape create_hanger_post(const hanger_post_params &params) {
  if (params.length <= 0 || params.sectionSize <= 0)
    throw Standard_ConstructionError(
        "Length and section size must be positive");

  double halfS = params.sectionSize / 2.0;
  double wT = params.wallThickness;

  // Main body: hollow tube
  TopoDS_Shape body;
  gp_Ax2 bodyAxis(gp::Origin(), gp::DZ());
  if (params.sectionType == hanger_post_section_type::ROUND) {
    TopoDS_Shape outer =
        BRepPrimAPI_MakeCylinder(bodyAxis, halfS, params.length).Shape();
    if (wT > 0 && halfS > wT) {
      TopoDS_Shape inner =
          BRepPrimAPI_MakeCylinder(bodyAxis, halfS - wT, params.length).Shape();
      body = BRepAlgoAPI_Cut(outer, inner).Shape();
    } else {
      body = outer;
    }
  } else {
    // Square or H-beam: square tube
    double ext = halfS;
    gp_Pnt outerOrg(-ext, -ext, 0);
    TopoDS_Shape outer = BRepPrimAPI_MakeBox(outerOrg, params.sectionSize,
                                             params.sectionSize, params.length)
                             .Shape();
    if (wT > 0 && ext > wT) {
      double innerExt = ext - wT;
      gp_Pnt innerOrg(-innerExt, -innerExt, -1);
      TopoDS_Shape inner =
          BRepPrimAPI_MakeBox(innerOrg, params.sectionSize - 2 * wT,
                              params.sectionSize - 2 * wT, params.length + 2)
              .Shape();
      body = BRepAlgoAPI_Cut(outer, inner).Shape();
    } else {
      body = outer;
    }
  }

  // Top flange (连接横梁)
  if (params.topFlangeSize > 0) {
    double flgH = params.topFlangeSize / 2.0;
    double flgTh = params.topFlangeThick > 0 ? params.topFlangeThick : wT * 2;
    gp_Pnt tfOrg(-flgH, -flgH, params.length);
    TopoDS_Shape tf = BRepPrimAPI_MakeBox(tfOrg, params.topFlangeSize,
                                          params.topFlangeSize, flgTh)
                          .Shape();
    // Bolt holes
    if (params.boltDiameter > 0) {
      double hr = params.boltDiameter / 2.0;
      double hs = params.boltSpacing / 2.0;
      for (int x = -1; x <= 1; x += 2)
        for (int y = -1; y <= 1; y += 2) {
          TopoDS_Shape h =
              BRepPrimAPI_MakeCylinder(
                  gp_Ax2(gp_Pnt(x * hs, y * hs, params.length - 1), gp::DZ()),
                  hr, flgTh + 2)
                  .Shape();
          tf = BRepAlgoAPI_Cut(tf, h).Shape();
        }
    }
    body = BRepAlgoAPI_Fuse(body, tf).Shape();

    // Stiffener ribs (三角加劲肋) between tube and top flange — 4 corners
    double ribH = params.topFlangeSize * 0.3;  // rib height
    double ribW = params.topFlangeSize * 0.25; // rib extends outward from tube
    double ribT = params.wallThickness * 0.8;  // rib plate thickness
    for (int r = 0; r < 4; ++r) {
      double a = r * M_PI / 2.0 + M_PI / 4.0; // 45°, 135°, 225°, 315°
      double nx = cos(a), ny = sin(a);        // outward normal
      double tx = -ny, ty = nx;               // tangential direction
      double bx = halfS * 0.85 * nx,
             by = halfS * 0.85 * ny; // base on tube surface

      // Three vertices: tube→flange edge→tube(offset down)
      gp_Pnt r1(bx, by, params.length); // top (flange level)
      gp_Pnt r2(bx + ribW * nx, by + ribW * ny,
                params.length - ribH * 0.3);   // flange edge
      gp_Pnt r3(bx, by, params.length - ribH); // tube(offset down)
      TopoDS_Wire rw =
          BRepBuilderAPI_MakePolygon(r1, r2, r3, Standard_True).Wire();
      TopoDS_Face rf = BRepLib_MakeFace(rw).Face();
      // Extrude along tangential direction to give thickness
      TopoDS_Shape rib =
          BRepPrimAPI_MakePrism(rf, gp_Vec(tx * ribT * 0.5, ty * ribT * 0.5, 0))
              .Shape();
      rib = BRepAlgoAPI_Fuse(
                rib, BRepPrimAPI_MakePrism(
                         rf, gp_Vec(-tx * ribT * 0.5, -ty * ribT * 0.5, 0))
                         .Shape())
                .Shape();
      body = BRepAlgoAPI_Fuse(body, rib).Shape();
    }
  }

  // Bottom flange (安装腕臂底座)
  if (params.bottomFlangeSize > 0) {
    double flgH = params.bottomFlangeSize / 2.0;
    double flgTh =
        params.bottomFlangeThick > 0 ? params.bottomFlangeThick : wT * 2;
    gp_Pnt bfOrg(-flgH, -flgH, -flgTh);
    TopoDS_Shape bf = BRepPrimAPI_MakeBox(bfOrg, params.bottomFlangeSize,
                                          params.bottomFlangeSize, flgTh)
                          .Shape();
    if (params.boltDiameter > 0) {
      double hr = params.boltDiameter / 2.0;
      double hs = params.boltSpacing / 2.0;
      for (int x = -1; x <= 1; x += 2)
        for (int y = -1; y <= 1; y += 2) {
          TopoDS_Shape h =
              BRepPrimAPI_MakeCylinder(
                  gp_Ax2(gp_Pnt(x * hs, y * hs, -flgTh - 1), gp::DZ()), hr,
                  flgTh + 2)
                  .Shape();
          bf = BRepAlgoAPI_Cut(bf, h).Shape();
        }
    }
    body = BRepAlgoAPI_Fuse(body, bf).Shape();
  }

  return body;
}

TopoDS_Shape create_hanger_post(const hanger_post_params &params,
                                const gp_Pnt &position,
                                const gp_Dir &direction) {
  TopoDS_Shape shape = create_hanger_post(params);
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ());
  gp_Ax3 targetAx3(position, direction);
  gp_Trsf t;
  t.SetTransformation(targetAx3, sourceAx3);
  return BRepBuilderAPI_Transform(shape, t).Shape();
}

// =========================================================================
// 22c. Portal Frame (梁顶门型架) TYPE=OCS_PORTAL_FRAME
// =========================================================================
TopoDS_Shape create_portal_frame(const portal_frame_params &params) {
  if (params.frameHeight <= 0 || params.frameWidth <= 0)
    throw Standard_ConstructionError("Frame dimensions must be positive");

  double postR = params.postDiameter / 2.0;
  double postIR = postR - params.postWallThick;
  double beamR = params.beamDiameter / 2.0;
  double beamIR = beamR - params.beamWallThick;
  double halfFW = params.frameWidth / 2.0;
  double halfBL = params.beamLength / 2.0;

  // Helper: hollow tube
  auto makeTube = [](gp_Ax2 axis, double OR, double IR,
                     double len) -> TopoDS_Shape {
    TopoDS_Shape outer = BRepPrimAPI_MakeCylinder(axis, OR, len).Shape();
    if (IR > Precision::Confusion()) {
      TopoDS_Shape inner = BRepPrimAPI_MakeCylinder(axis, IR, len).Shape();
      return BRepAlgoAPI_Cut(outer, inner).Shape();
    }
    return outer;
  };

  TopoDS_Shape result;

  // Left post: vertical along Z, at X=-halfFW
  gp_Ax2 leftAxis(gp_Pnt(-halfFW, 0, 0), gp::DZ());
  TopoDS_Shape leftPost = makeTube(leftAxis, postR, postIR, params.frameHeight);

  // Right post: vertical along Z, at X=+halfFW
  gp_Ax2 rightAxis(gp_Pnt(halfFW, 0, 0), gp::DZ());
  TopoDS_Shape rightPost =
      makeTube(rightAxis, postR, postIR, params.frameHeight);

  // Top horizontal beam along X, at Z=frameHeight
  gp_Ax2 topAxis(gp_Pnt(-halfBL, 0, params.frameHeight), gp::DX());
  TopoDS_Shape topBeam = makeTube(topAxis, beamR, beamIR, params.beamLength);

  result = BRepAlgoAPI_Fuse(leftPost, rightPost).Shape();
  result = BRepAlgoAPI_Fuse(result, topBeam).Shape();

  // Base plates under each post
  if (params.basePlateLength > 0) {
    double bpl = params.basePlateLength / 2.0;
    double bpw = params.basePlateWidth / 2.0;
    double bpt = params.basePlateThick > 0 ? params.basePlateThick
                                           : params.postWallThick * 2;

    for (int side = -1; side <= 1; side += 2) {
      double cx = side * halfFW;
      gp_Pnt bpOrg(cx - bpl, -bpw, -bpt);
      TopoDS_Shape bp = BRepPrimAPI_MakeBox(bpOrg, params.basePlateLength,
                                            params.basePlateWidth, bpt)
                            .Shape();
      // Bolt holes
      if (params.boltDiameter > 0) {
        double hr = params.boltDiameter / 2.0;
        double hs = params.boltSpacing / 2.0;
        for (int bx = -1; bx <= 1; bx += 2)
          for (int by = -1; by <= 1; by += 2) {
            TopoDS_Shape hole =
                BRepPrimAPI_MakeCylinder(
                    gp_Ax2(gp_Pnt(cx + bx * hs, by * hs, -bpt - 1), gp::DZ()),
                    hr, bpt + 2)
                    .Shape();
            bp = BRepAlgoAPI_Cut(bp, hole).Shape();
          }
      }
      result = BRepAlgoAPI_Fuse(result, bp).Shape();

      // Stiffener ribs between post and base plate (前后各一片)
      for (int fr = -1; fr <= 1; fr += 2) {
        double ry = fr * bpw * 0.7;
        double ribH = params.frameHeight * 0.15;
        gp_Pnt r1(cx, ry, 0);
        gp_Pnt r2(cx + side * ribH * 0.5, ry, 0);
        gp_Pnt r3(cx, ry, -ribH);
        TopoDS_Wire rw =
            BRepBuilderAPI_MakePolygon(r1, r2, r3, Standard_True).Wire();
        TopoDS_Face rf = BRepLib_MakeFace(rw).Face();
        TopoDS_Shape rib =
            BRepPrimAPI_MakePrism(rf, gp_Vec(0, fr * bpt, 0)).Shape();
        result = BRepAlgoAPI_Fuse(result, rib).Shape();
      }
    }
  }

  // Hanging ear plates on top beam
  int nHang = std::max(0, params.hangPointCount);
  if (nHang > 0) {
    double hSpacing = params.hangPointSpacing > 0
                          ? params.hangPointSpacing
                          : params.beamLength / (nHang + 1);
    double earW = beamR * 1.5, earH = beamR * 1.0,
           earT = params.beamWallThick * 2;
    for (int i = 0; i < nHang; ++i) {
      double x = -halfBL + (i + 1) * hSpacing;
      gp_Pnt earOrg(x - earT / 2, -earW / 2, params.frameHeight + beamR);
      TopoDS_Shape ear = BRepPrimAPI_MakeBox(earOrg, earT, earW, earH).Shape();
      gp_Ax2 earHole(gp_Pnt(x, 0, params.frameHeight + beamR + earH * 0.6),
                     gp::DY());
      TopoDS_Shape hole =
          BRepPrimAPI_MakeCylinder(earHole, beamR * 0.3, earW + 2).Shape();
      ear = BRepAlgoAPI_Cut(ear, hole).Shape();
      result = BRepAlgoAPI_Fuse(result, ear).Shape();
    }
  }

  return result;
}

TopoDS_Shape create_portal_frame(const portal_frame_params &params,
                                 const gp_Pnt &position,
                                 const gp_Dir &direction, const gp_Dir &upDir) {
  TopoDS_Shape shape = create_portal_frame(params);
  gp_Dir yDir = upDir.Crossed(direction);
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, upDir, direction);
  gp_Trsf t;
  t.SetTransformation(targetAx3, sourceAx3);
  return BRepBuilderAPI_Transform(shape, t).Shape();
}

// =========================================================================
// 22d. Suspension Cable (悬索) — shared primitive
// =========================================================================
TopoDS_Shape create_suspension_cable(const suspension_cable_params &params) {
  if (params.diameter <= 0)
    throw Standard_ConstructionError("Diameter must be positive");
  double R = params.diameter / 2.0;
  gp_Vec vec(params.startPoint, params.endPoint);
  double span = vec.Magnitude();
  if (span < Precision::Confusion())
    return BRepPrimAPI_MakeCylinder(gp_Ax2(params.startPoint, gp::DX()), R, 1)
        .Shape();

  if (params.cableType == suspension_cable_type::FIXED_ROPE) {
    // Straight cylinder
    return BRepPrimAPI_MakeCylinder(gp_Ax2(params.startPoint, gp_Dir(vec)), R,
                                    span)
        .Shape();
  }

  // Parabolic cable: 3-point Bezier with sag at mid-span
  // 缺省弛度: 跨距的 1.5% (DROPPER 吊弦保持 5% 及其特殊符号逻辑)
  double sag = params.sag > 0 ? params.sag
               : span * (params.cableType == suspension_cable_type::DROPPER
                             ? 0.05
                             : 0.015);
  double sign =
      (params.cableType == suspension_cable_type::DROPPER) ? 1.0 : -1.0;
  gp_Pnt mid((params.startPoint.X() + params.endPoint.X()) / 2.0,
             (params.startPoint.Y() + params.endPoint.Y()) / 2.0,
             (params.startPoint.Z() + params.endPoint.Z()) / 2.0);
  mid.Translate(gp_Vec(0, 0, 1) * sag * sign);

  BRepBuilderAPI_MakeWire wireBuilder;
  Handle(TColgp_HArray1OfPnt) poles = new TColgp_HArray1OfPnt(1, 3);
  poles->SetValue(1, params.startPoint);
  poles->SetValue(2, mid);
  poles->SetValue(3, params.endPoint);
  Handle(Geom_BezierCurve) bezier = new Geom_BezierCurve(poles->Array1());
  wireBuilder.Add(BRepBuilderAPI_MakeEdge(bezier));
  TopoDS_Wire pathWire = wireBuilder.Wire();

  // Circular profile in plane perpendicular to path start
  gp_Pnt startP; gp_Vec startV; bezier->D1(0, startP, startV);
  gp_Ax2 profileAxis(params.startPoint, gp_Dir(startV));
  gp_Circ sectionCircle(profileAxis, R);
  TopoDS_Edge sectionEdge = BRepBuilderAPI_MakeEdge(sectionCircle).Edge();
  TopoDS_Wire sectionWire = BRepBuilderAPI_MakeWire(sectionEdge).Wire();

  // Sweep along the parabolic path
  BRepOffsetAPI_MakePipeShell pipe(pathWire);
  pipe.Add(sectionWire);
  pipe.SetMode(Standard_True);
  pipe.Build();
  if (pipe.IsDone() && pipe.MakeSolid())
    return pipe.Shape();

  // Fallback: straight cylinder
  return BRepPrimAPI_MakeCylinder(gp_Ax2(params.startPoint, gp_Dir(vec)), R,
                                  span)
      .Shape();
}

TopoDS_Wire
create_suspension_cable_centerline(const suspension_cable_params &params) {
  gp_Vec vec(params.startPoint, params.endPoint);
  double span = vec.Magnitude();
  if (span <= Precision::Confusion())
    return BRepBuilderAPI_MakeWire(
        BRepBuilderAPI_MakeEdge(params.startPoint, params.startPoint));

  BRepBuilderAPI_MakeWire wire;

  if (params.cableType == suspension_cable_type::FIXED_ROPE ||
      span < Precision::Confusion()) {
    // Straight line
    wire.Add(BRepBuilderAPI_MakeEdge(params.startPoint, params.endPoint));
  } else {
    // Catenary arc (Bezier) — sag is the mid-span deviation
    double sag = params.sag > 0 ? params.sag : span * 0.05;
    double sign =
        (params.cableType == suspension_cable_type::DROPPER) ? 1.0 : -1.0;
    gp_Vec sagVec = gp_Vec(0, 0, 1) * sag * sign;

    gp_Pnt mid = gp_Pnt((params.startPoint.X() + params.endPoint.X()) / 2.0,
                        (params.startPoint.Y() + params.endPoint.Y()) / 2.0,
                        (params.startPoint.Z() + params.endPoint.Z()) / 2.0);
    mid.Translate(sagVec);

    Handle(TColgp_HArray1OfPnt) pts = new TColgp_HArray1OfPnt(1, 3);
    pts->SetValue(1, params.startPoint);
    pts->SetValue(2, mid);
    pts->SetValue(3, params.endPoint);
    Handle(Geom_BezierCurve) bezier = new Geom_BezierCurve(pts->Array1());
    wire.Add(BRepBuilderAPI_MakeEdge(bezier));
  }

  return wire.Wire();
}

// =========================================================================
// 22e. Suspension Hard Span (悬索式硬横跨)
// =========================================================================
TopoDS_Shape
create_suspension_hard_span(const suspension_hard_span_params &params) {
  if (params.span <= 0 || params.mastHeight <= 0)
    throw Standard_ConstructionError("Span and height must be positive");

  BRep_Builder builder;
  TopoDS_Compound compound;
  builder.MakeCompound(compound);

  double span = params.span;

  // Main suspension cable (top span, catenary type)
  suspension_cable_params sc;
  sc.startPoint = gp_Pnt(-span / 2, 0, params.mastHeight);
  sc.endPoint = gp_Pnt(span / 2, 0, params.mastHeight);
  sc.diameter = params.cableDiameter;
  sc.sag = params.cableSag > 0 ? params.cableSag : span * 0.05;
  sc.cableType = suspension_cable_type::CATENARY;
  sc.tension = 0;
  builder.Add(compound, create_suspension_cable(sc));

  // Vertical dropper cables
  if (params.dropperCount > 0) {
    int nDrop = params.dropperCount;
    double dSpacing =
        params.dropperSpacing > 0 ? params.dropperSpacing : span / (nDrop + 1);
    auto cl = create_suspension_cable_centerline(sc);
    TopExp_Explorer ex(cl, TopAbs_EDGE);
    if (ex.More()) {
      TopoDS_Edge ce = TopoDS::Edge(ex.Current());
      double first = 0, last = 0;
      Handle(Geom_Curve) curve = BRep_Tool::Curve(ce, first, last);

      for (int i = 0; i < nDrop; ++i) {
        double t = first + (last - first) * (i + 1) / (nDrop + 1);
        gp_Pnt topPt = curve->Value(t);
        // Vertical dropper from cable down to contact height
        double dropLen = topPt.Z() * 0.5; // arbitrary: half height
        gp_Pnt botPt = topPt.Translated(gp_Vec(0, 0, -dropLen));

        suspension_cable_params dropCable;
        dropCable.startPoint = topPt;
        dropCable.endPoint = botPt;
        dropCable.diameter = params.dropperCableDiameter;
        dropCable.sag = 0;
        dropCable.cableType = suspension_cable_type::DROPPER;
        dropCable.tension = 0;
        builder.Add(compound, create_suspension_cable(dropCable));
      }
    }
  }

  // Upper fixed rope (水平) at ~70% mast height — shared pattern with soft span
  suspension_cable_params upRope;
  upRope.startPoint = gp_Pnt(-span / 2, 0, params.mastHeight * 0.7);
  upRope.endPoint = gp_Pnt(span / 2, 0, params.mastHeight * 0.7);
  upRope.diameter = params.cableDiameter * 0.6;
  upRope.sag = 0;
  upRope.cableType = suspension_cable_type::FIXED_ROPE;
  upRope.tension = 0;
  builder.Add(compound, create_suspension_cable(upRope));

  // Lower fixed rope (水平) at ~50% mast height — shared pattern with soft span
  suspension_cable_params loRope;
  loRope.startPoint = gp_Pnt(-span / 2, 0, params.mastHeight * 0.5);
  loRope.endPoint = gp_Pnt(span / 2, 0, params.mastHeight * 0.5);
  loRope.diameter = params.cableDiameter * 0.5;
  loRope.sag = 0;
  loRope.cableType = suspension_cable_type::FIXED_ROPE;
  loRope.tension = 0;
  builder.Add(compound, create_suspension_cable(loRope));

  // Insulators at fixed rope ends (each mast side)
  if (params.insulatorLength > 0 && params.insulatorDiameter > 0) {
    rod_insulator_params insParams;
    insParams.type = rod_insulator_type::SOLID;
    insParams.height = params.insulatorLength;
    insParams.outerDiameter = params.insulatorDiameter;
    insParams.innerDiameter = 0;
    insParams.shedDiameter = params.insulatorDiameter * 1.6;
    insParams.shedSpacing = params.insulatorLength / 5;
    insParams.shedCount = 3;
    insParams.endFitting = end_fitting_type::FLANGE;
    insParams.flangeDiameter = params.insulatorDiameter * 1.3;
    insParams.flangeBoltSpacing = params.insulatorDiameter * 0.8;
    insParams.flangeBoltDiameter = params.insulatorDiameter * 0.2;

    for (int side = -1; side <= 1; side += 2) {
      double mastX = side * span / 2.0;
      // Insulator at upper fixed rope end
      builder.Add(compound,
                  create_rod_insulator(
                      insParams, gp_Pnt(mastX, 0, params.mastHeight * 0.7),
                      gp_Dir(-side, 0, 0)));
      // Insulator at lower fixed rope end
      builder.Add(compound,
                  create_rod_insulator(
                      insParams, gp_Pnt(mastX, 0, params.mastHeight * 0.5),
                      gp_Dir(-side, 0, 0)));
    }
  }

  return compound;
}

TopoDS_Shape
create_suspension_hard_span(const suspension_hard_span_params &params,
                            const gp_Pnt &position, const gp_Dir &direction,
                            const gp_Dir &upDir) {
  TopoDS_Shape shape = create_suspension_hard_span(params);
  gp_Dir yDir = upDir.Crossed(direction);
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, upDir, direction);
  gp_Trsf t;
  t.SetTransformation(targetAx3, sourceAx3);
  return BRepBuilderAPI_Transform(shape, t).Shape();
}

// =========================================================================
// 22f. Positioning Cable (定位索)
// =========================================================================
// Shared straight-cable geometry — also usable by HeadSpan fixed ropes
TopoDS_Shape create_positioning_cable(const positioning_cable_params &params) {
  if (params.diameter <= 0)
    throw Standard_ConstructionError("Diameter must be positive");

  gp_Vec v(params.topPoint, params.bottomPoint);
  double len = v.Magnitude();
  if (len <= Precision::Confusion())
    throw Standard_ConstructionError("Top and bottom points must differ");

  double R = params.diameter / 2.0;
  TopoDS_Shape cable;

  if (params.adjustable) {
    // Three-segment: upper straight + threaded adjuster + lower straight
    double adjLen = len * 0.15; // adjuster length in middle
    double segLen = (len - adjLen) / 2.0;
    gp_Dir dir(v);
    gp_Vec halfStep = gp_Vec(dir.XYZ() * segLen);

    gp_Pnt adjStart = params.topPoint.Translated(halfStep);
    gp_Pnt adjEnd = adjStart.Translated(gp_Vec(dir.XYZ() * adjLen));

    // Upper segment
    gp_Ax2 upAxis(params.topPoint, dir);
    TopoDS_Shape upper = BRepPrimAPI_MakeCylinder(upAxis, R, segLen).Shape();

    // Lower segment
    gp_Ax2 loAxis(adjEnd, dir);
    TopoDS_Shape lower = BRepPrimAPI_MakeCylinder(loAxis, R, segLen).Shape();

    // Threaded adjuster: thicker cylinder + hex nut
    gp_Ax2 adjAxis(adjStart, dir);
    TopoDS_Shape adjRod =
        BRepPrimAPI_MakeCylinder(adjAxis, R * 1.3, adjLen).Shape();
    // Hex nut (approximated by hexagonal prism)
    double nutH = adjLen * 0.3;
    gp_Pnt nutCenter = adjStart.Translated(gp_Vec(dir.XYZ() * adjLen * 0.5));
    // Simple box approximation for the nut
    gp_Pnt nutOrg(nutCenter.X() - R * 1.5, nutCenter.Y() - R * 1.5,
                  nutCenter.Z() - nutH / 2);
    TopoDS_Shape nut = BRepPrimAPI_MakeBox(nutOrg, R * 3, R * 3, nutH).Shape();
    adjRod = BRepAlgoAPI_Fuse(adjRod, nut).Shape();

    cable = BRepAlgoAPI_Fuse(upper, adjRod).Shape();
    cable = BRepAlgoAPI_Fuse(cable, lower).Shape();
  } else {
    // Simple straight cylinder
    gp_Ax2 cableAxis(params.topPoint, gp_Dir(v));
    cable = BRepPrimAPI_MakeCylinder(cableAxis, R, len).Shape();
  }

  // Connection plates at both ends
  double plateSize = R * 4;
  double plateThick = R * 1.5;
  for (int end = 0; end < 2; ++end) {
    gp_Pnt pt = (end == 0) ? params.topPoint : params.bottomPoint;
    gp_Pnt plateOrg(pt.X() - plateSize / 2, pt.Y() - plateSize / 2,
                    pt.Z() - (end == 0 ? 0 : plateThick));
    TopoDS_Shape plate =
        BRepPrimAPI_MakeBox(plateOrg, plateSize, plateSize, plateThick).Shape();
    // Bolt hole
    double holeR = R * 0.5;
    TopoDS_Shape hole =
        BRepPrimAPI_MakeCylinder(
            gp_Ax2(gp_Pnt(pt.X(), pt.Y(),
                          pt.Z() + (end == 0 ? -1 : plateThick + 1)),
                   gp::DZ()),
            holeR, plateThick + 2)
            .Shape();
    plate = BRepAlgoAPI_Cut(plate, hole).Shape();
    cable = BRepAlgoAPI_Fuse(cable, plate).Shape();
  }

  return cable;
}

// =========================================================================
// 23. Auxiliary Wire Bracket (附加导线安装支架)
// =========================================================================
TopoDS_Shape create_aux_bracket(const aux_bracket_params &params) {
  if (params.overhangLength <= 0)
    throw Standard_ConstructionError("Overhang length must be positive");

  double halfL = params.bracketLength / 2;
  double halfW = params.bracketWidth / 2;

  if (params.type == aux_bracket_type::CROSS_ARM) {
    // Main beam along Y
    gp_Pnt beamOrigin(-halfL, -params.overhangLength / 2, 0);
    TopoDS_Shape beam =
        BRepPrimAPI_MakeBox(beamOrigin, params.bracketLength,
                            params.overhangLength, params.bracketWidth)
            .Shape();

    // Diagonal brace
    double braceLen = params.overhangLength * 0.6;
    gp_Ax2 braceAxis(gp_Pnt(0, 0, 0), gp::DZ());
    TopoDS_Shape brace =
        BRepPrimAPI_MakeCylinder(braceAxis, halfW * 0.3, braceLen).Shape();
    gp_Trsf rot;
    rot.SetRotation(gp_Ax1(gp_Pnt(0, 0, 0), gp::DY()), -M_PI / 4);
    brace = BRepBuilderAPI_Transform(brace, rot).Shape();
    return BRepAlgoAPI_Fuse(beam, brace).Shape();
  } else {
    // Wall-mount or double mast: flat plate
    gp_Pnt plateOrigin(-halfL, -halfW, 0);
    TopoDS_Shape plate =
        BRepPrimAPI_MakeBox(plateOrigin, params.bracketLength,
                            params.bracketWidth, params.mountHeight)
            .Shape();

    // Bolt holes
    if (params.boltDiameter > 0) {
      double holeR = params.boltDiameter / 2;
      double hs = params.boltSpacing / 2;
      gp_Ax2 h1(gp_Pnt(-hs, -hs, -1), gp::DZ());
      gp_Ax2 h2(gp_Pnt(hs, -hs, -1), gp::DZ());
      gp_Ax2 h3(gp_Pnt(-hs, hs, -1), gp::DZ());
      gp_Ax2 h4(gp_Pnt(hs, hs, -1), gp::DZ());
      for (auto &ha : {h1, h2, h3, h4}) {
        TopoDS_Shape hole =
            BRepPrimAPI_MakeCylinder(ha, holeR, params.mountHeight + 2).Shape();
        plate = BRepAlgoAPI_Cut(plate, hole).Shape();
      }
    }
    return plate;
  }
}

TopoDS_Shape create_aux_bracket(const aux_bracket_params &params,
                                const gp_Pnt &position, const gp_Dir &normal,
                                const gp_Dir &upDir) {
  TopoDS_Shape shape = create_aux_bracket(params);
  gp_Dir yDir = upDir.Crossed(normal);
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, upDir, normal);
  gp_Trsf t;
  t.SetTransformation(targetAx3, sourceAx3);
  return BRepBuilderAPI_Transform(shape, t).Shape();
}

// =========================================================================
// 24. Rail (钢轨)
// =========================================================================
namespace {

// 圆弧边: p0 → p1 经过弧上一点 pm
TopoDS_Edge railArcEdge(const gp_Pnt &p0, const gp_Pnt &pm, const gp_Pnt &p1) {
  return BRepBuilderAPI_MakeEdge(GC_MakeArcOfCircle(p0, pm, p1).Value()).Edge();
}

// 弦中点向理想角点 corner 方向偏移 sagitta, 得到圆弧中点 (凹凸圆角通用)
gp_Pnt railArcMid(const gp_Pnt &p0, const gp_Pnt &p1, const gp_Pnt &corner,
                  double radius) {
  gp_Vec chord(p0, p1);
  double c = chord.Magnitude();
  gp_Pnt mid((p0.X() + p1.X()) / 2, (p0.Y() + p1.Y()) / 2, 0);
  if (c < Precision::Confusion() || radius <= 0)
    return mid;
  gp_Vec toK(mid, corner);
  if (toK.Magnitude() < Precision::Confusion())
    return mid;
  double h = std::min(c / 2.0, radius * 0.95);
  double sag = radius - std::sqrt(std::max(radius * radius - h * h, 1e-9));
  return mid.Translated(toK.Normalized() * sag);
}

// 真实钢轨断面 (以 60kg/m 为基准, 按比例适配其他轨型):
//   R300 踏面圆弧 + R80 轨头侧面 + R13 轨头下圆角
//   头腰/腰底圆角过渡, 轨底上翼缘斜坡, 轨底边缘小圆角
// 断面位于 XY 平面 (X=横向, Y=竖向), 轨底中心为原点
// widthScale/anchorX: 横向缩放 (尖轨单侧刨削用), x' = anchorX + (x-anchorX)*widthScale
TopoDS_Wire buildRailSectionWire(double railHeight, double headWidth,
                                 double baseWidth, double webThickness,
                                 double headHeight, double baseHeight,
                                 double headRadius, double widthScale = 1.0,
                                 double anchorX = 0.0) {
  const double H = railHeight;
  const double hW = headWidth / 2.0;
  const double bW = baseWidth / 2.0;
  const double wT = webThickness > 0 ? webThickness / 2.0 : 8.25;
  const double hH = headHeight > 0 ? headHeight : H * 0.2456;
  const double bH = baseHeight > 0 ? baseHeight : H * 0.1667;
  const double sc = headWidth / 73.0;             // 以 60kg/m 断面为基准的比例
  const double crnR = std::max(300.0 * sc, hW * 1.2); // 踏面圆弧半径
  const double sidR = 80.0 * sc;                  // 轨头侧面圆弧半径
  const double corR = headRadius > 0 ? headRadius : 13.0 * sc; // 轨头下圆角
  const double fwh = std::min(13.0 * sc, hH * 0.5); // 头腰过渡圆角
  const double fwb = std::min(25.0 * sc, bH * 0.8); // 腰底过渡圆角
  const double beR = 2.0 * sc;                    // 轨底边缘圆角
  const double bEdge = bH * 0.4;                  // 轨底边缘厚度

  // 特征点 (右半, x>=0)
  const double xc = hW * 0.45;                    // 踏面弧半宽
  const double s1 = crnR - std::sqrt(crnR * crnR - xc * xc); // 踏面矢高
  const double ySd = H - hH * 0.40;               // 侧面弧下端
  const double xUH = hW * 0.92, yUH = H - hH * 0.78; // 头底斜线起点
  const double xF0 = wT + fwh * 0.85, yF0 = H - hH;  // 头腰圆角起点
  const double yF1 = H - hH - fwh * 0.85;         // 头腰圆角终点 (x=wT)
  const double yW = bH + fwb * 0.85;              // 腰底圆角起点 (x=wT)
  const double xB0 = wT + fwb * 0.85;             // 腰底圆角终点
  const double mUH = (yF0 - yUH) / (xF0 - xUH);   // 头底斜线斜率
  const double mBS = (bEdge - bH) / (bW - beR - xB0); // 轨底斜坡斜率

  struct Seg {
    gp_Pnt p0, pm, p1;
  };
  std::vector<Seg> half;
  auto P = [](double x, double y) { return gp_Pnt(x, y, 0); };
  auto addLine = [&](double x0, double y0, double x1, double y1) {
    half.push_back({P(x0, y0), P((x0 + x1) / 2, (y0 + y1) / 2), P(x1, y1)});
  };
  auto addArcK = [&](double x0, double y0, double x1, double y1, double kx,
                     double ky, double R) {
    half.push_back(
        {P(x0, y0), railArcMid(P(x0, y0), P(x1, y1), P(kx, ky), R), P(x1, y1)});
  };

  // 踏面: 圆心在 (0, H-crnR)
  {
    double sagH = crnR - std::sqrt(crnR * crnR - (xc / 2) * (xc / 2));
    half.push_back({P(0, H), P(xc / 2, H - sagH), P(xc, H - s1)});
  }
  // 侧面: 过踏面切线与 x=hW 的交角点
  {
    double Ky = (H - s1) - xc * (hW - xc) / (crnR - s1);
    addArcK(xc, H - s1, hW, ySd, hW, Ky, sidR);
  }
  // 轨头下圆角
  addArcK(hW, ySd, xUH, yUH, hW, yUH + mUH * (hW - xUH), corR);
  // 头底斜线
  addLine(xUH, yUH, xF0, yF0);
  // 头腰圆角
  addArcK(xF0, yF0, wT, yF1, wT, yUH + mUH * (wT - xUH), fwh);
  // 轨腰
  addLine(wT, yF1, wT, yW);
  // 腰底圆角
  addArcK(wT, yW, xB0, bH, wT, bH + mBS * (wT - xB0), fwb);
  // 轨底上翼缘斜坡
  addLine(xB0, bH, bW - beR, bEdge);
  // 轨底外缘圆角 (凸)
  addArcK(bW - beR, bEdge, bW, bEdge - beR, bW, bH + mBS * (bW - xB0), beR);
  // 轨底立面
  addLine(bW, bEdge - beR, bW, beR);
  // 轨底底角 (凸)
  addArcK(bW, beR, bW - beR, 0, bW, 0, beR);

  BRepBuilderAPI_MakeWire wire;
  auto tx = [&](double x) { return anchorX + (x - anchorX) * widthScale; };
  auto emit = [&](const Seg &s, double sign, bool rev) {
    gp_Pnt a(tx(s.p0.X() * sign), s.p0.Y(), 0);
    gp_Pnt m(tx(s.pm.X() * sign), s.pm.Y(), 0);
    gp_Pnt b(tx(s.p1.X() * sign), s.p1.Y(), 0);
    if (rev)
      std::swap(a, b);
    bool degenerate = a.Distance(m) < Precision::Confusion() ||
                      m.Distance(b) < Precision::Confusion();
    bool collinear = false;
    if (!degenerate) {
      gp_Vec v1(a, m), v2(a, b);
      collinear = std::abs(v1.Normalized().Dot(v2.Normalized())) > 0.999999;
    }
    if (degenerate || collinear) {
      if (a.Distance(b) >= Precision::Confusion())
        wire.Add(BRepBuilderAPI_MakeEdge(a, b));
    } else {
      wire.Add(railArcEdge(a, m, b));
    }
  };
  // 右半: 顶心 → 轨底
  for (const auto &s : half)
    emit(s, +1, false);
  // 轨底底面
  wire.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(tx(bW - beR), 0, 0),
                                   gp_Pnt(tx(-(bW - beR)), 0, 0)));
  // 左半: 轨底 → 顶心 (右半镜像逆序)
  for (auto it = half.rbegin(); it != half.rend(); ++it)
    emit(*it, -1, true);

  ShapeFix_Wire fx;
  fx.Load(wire.Wire());
  fx.Perform();
  return fx.Wire();
}

} // anonymous namespace

// 标准钢轨断面查表 (kg/m: 43/50/60/75), 未识别时返回 60kg/m
rail_params standard_rail_params(double kgPerMeter) {
  rail_params p{};
  p.headRadius = 13.0;
  p.standardLength = 25000.0;
  switch ((int)std::round(kgPerMeter)) {
  case 43:
    p.railHeight = 140; p.headWidth = 70; p.baseWidth = 114;
    p.webThickness = 14.5; p.headHeight = 40; p.baseHeight = 27;
    break;
  case 50:
    p.railHeight = 152; p.headWidth = 70; p.baseWidth = 132;
    p.webThickness = 15.5; p.headHeight = 42; p.baseHeight = 27;
    break;
  case 75:
    p.railHeight = 192; p.headWidth = 75; p.baseWidth = 150;
    p.webThickness = 20; p.headHeight = 55; p.baseHeight = 32;
    break;
  case 60:
  default:
    p.railHeight = 176; p.headWidth = 73; p.baseWidth = 150;
    p.webThickness = 16.5; p.headHeight = 48.5; p.baseHeight = 30.5;
    break;
  }
  return p;
}

TopoDS_Shape create_rail(const rail_params &params) {
  if (params.railHeight <= 0 || params.headWidth <= 0 || params.baseWidth <= 0)
    throw Standard_ConstructionError("Rail dimensions must be positive");

  TopoDS_Wire wire = buildRailSectionWire(
      params.railHeight, params.headWidth, params.baseWidth,
      params.webThickness, params.headHeight, params.baseHeight,
      params.headRadius);
  TopoDS_Face face = BRepLib_MakeFace(wire).Face();
  return BRepPrimAPI_MakePrism(face, gp_Vec(0, 0, params.standardLength)).Shape();
}

TopoDS_Shape create_rail(const rail_params &params, const gp_Pnt &startPoint,
                         const gp_Pnt &endPoint) {
  gp_Vec vec(startPoint, endPoint);
  double len = vec.Magnitude();
  if (len <= Precision::Confusion())
    return create_rail(params);
  // 按实际长度重建, 不做整体缩放 (缩放会把断面尺寸一起缩错)
  rail_params rp2 = params;
  rp2.standardLength = len;
  TopoDS_Shape shape = create_rail(rp2);
  gp_Dir dir(vec);
  gp_Dir crossDir = gp::DZ().Crossed(dir);
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(startPoint, dir, crossDir);
  gp_Trsf t; t.SetTransformation(targetAx3, sourceAx3);
  return BRepBuilderAPI_Transform(shape, t).Shape();
}

// Rail on arbitrary path (LINE/ARC/BEZIER) via ThruSections
TopoDS_Shape create_rail_path(const rail_params &params,
                               const std::vector<centerline_segment> &segments,
                               double lateralOffset,
                               double verticalOffset,
                               double tiltAngle) {
  if (segments.empty())
    throw Standard_ConstructionError("Empty rail path");

  // 断面模板 (局部坐标: X=横向, Y=竖向, 轨底中心为原点)
  TopoDS_Wire tmpl = buildRailSectionWire(
      params.railHeight, params.headWidth, params.baseWidth,
      params.webThickness, params.headHeight, params.baseHeight,
      params.headRadius);
  // 截面坐标架 (Hd, t×Hd, t) 相对轮廓映射 (Hd, Vd, t) 为镜像, 预翻转模板
  TopoDS_Shape tmplMir;
  {
    gp_Trsf flip;
    flip.SetMirror(gp_Ax2(gp::Origin(), gp::DY()));
    tmplMir = BRepBuilderAPI_Transform(tmpl, flip).Shape();
  }

  // Build section at a path point p with tangent t
  auto makeSection = [&](const gp_Pnt &p, const gp_Dir &t) {
    gp_Vec Hv(t.XYZ().Crossed(gp::DZ().XYZ()));
    gp_Dir Hd = Hv.Magnitude() < Precision::Confusion() ? gp::DX() : gp_Dir(Hv);
    gp_Dir Vd = Hd.Crossed(t);
    // Superelevation tilt: rotate (H,V) frame around T using OCCT SetRotation convention
    if (std::abs(tiltAngle) > Precision::Angular()) {
      gp_Trsf tilt;
      tilt.SetRotation(gp_Ax1(gp::Origin(), t), tiltAngle);
      gp_XYZ hx = Hd.XYZ(); tilt.Transforms(hx); Hd = gp_Dir(hx);
      gp_XYZ vx = Vd.XYZ(); tilt.Transforms(vx); Vd = gp_Dir(vx);
    }
    gp_Pnt o = p.Translated(
        gp_Vec(Hd.XYZ() * lateralOffset + Vd.XYZ() * verticalOffset));
    gp_Ax3 src(gp::Origin(), gp::DZ(), gp::DX());
    gp_Ax3 tgt(o, t, Hd);
    gp_Trsf tr;
    tr.SetTransformation(tgt, src);
    return TopoDS::Wire(BRepBuilderAPI_Transform(tmplMir, tr).Shape());
  };

  // Build curves, sample, loft
  struct CR { Handle(Geom_Curve) c; double l; };
  std::vector<CR> crvs;
  for (auto &seg : segments) {
    if (seg.points.size() < 2) continue;
    if (seg.type == centerline_curve_type::LINE) {
      double d = seg.points[0].Distance(seg.points[1]);
      if (d <= Precision::Confusion())
        continue; // 零长度段 (起终点重合) 无法生成曲线, 跳过
      Handle(Geom_TrimmedCurve) tc = GC_MakeSegment(seg.points[0], seg.points[1]).Value();
      if (tc.IsNull())
        continue;
      Handle(Geom_Curve) c = tc;
      crvs.push_back({c, d});
    } else if (seg.type == centerline_curve_type::ARC && seg.points.size() >= 3) {
      Handle(Geom_TrimmedCurve) arc = GC_MakeArcOfCircle(seg.points[0], seg.points[1], seg.points[2]);
      if (!arc.IsNull()) {
        double al = 0;
        Handle(Geom_Curve) bc = arc->BasisCurve();
        if (!bc.IsNull()) {
          double r = Handle(Geom_Circle)::DownCast(bc)->Circ().Radius();
          al = r * std::abs(arc->LastParameter() - arc->FirstParameter());
        }
        crvs.push_back({Handle(Geom_Curve)(arc), al});
      }
    } else if (seg.type == centerline_curve_type::BEZIER) {
      Handle(TColgp_HArray1OfPnt) arr = new TColgp_HArray1OfPnt(1, (int)seg.points.size());
      for (size_t i = 0; i < seg.points.size(); ++i) arr->SetValue((int)(i+1), seg.points[i]);
      Handle(Geom_Curve) bez = new Geom_BezierCurve(arr->Array1());
      crvs.push_back({bez, seg.points.front().Distance(seg.points.back())});
    }
  }
  if (crvs.empty()) throw Standard_ConstructionError("No valid rail path");

  double tot = 0;
  for (auto &cr : crvs) tot += cr.l;
  if (tot <= Precision::Confusion())
    throw Standard_ConstructionError("Degenerate rail path length");

  // LINE paths → build face at origin along Z, extrude along Z, rotate+translate to position
  if (segments.size() == 1 && segments[0].type == centerline_curve_type::LINE) {
    gp_Pnt p0; gp_Vec v0;
    crvs[0].c->D1(crvs[0].c->FirstParameter(), p0, v0);
    gp_Dir t0(v0);
    // 与放样路径 makeSection 完全一致的坐标架: Hd = t×DZ, Vd = Hd×t,
    // 含超高倾角 tilt (旧实现偏移方向相反且丢弃 tilt, 导致单段直线与
    // 多段折线生成的左右股钢轨互换)
    gp_Vec Hv(t0.XYZ().Crossed(gp::DZ().XYZ()));
    gp_Dir Hd = Hv.Magnitude() < Precision::Confusion() ? gp::DX() : gp_Dir(Hv);
    gp_Dir Vd = Hd.Crossed(t0);
    if (std::abs(tiltAngle) > Precision::Angular()) {
      gp_Trsf tilt;
      tilt.SetRotation(gp_Ax1(gp::Origin(), t0), tiltAngle);
      gp_XYZ hx = Hd.XYZ(); tilt.Transforms(hx); Hd = gp_Dir(hx);
      gp_XYZ vx = Vd.XYZ(); tilt.Transforms(vx); Vd = gp_Dir(vx);
    }

    // Build profile at origin with standardLength = tot
    rail_params rp2 = params;
    rp2.standardLength = tot;
    TopoDS_Shape rail = create_rail(rp2);

    // Apply rotation: Z→t0 (along track), X→DZ×t0 (= -Hd, 此朝向下断面
    // 与放样路径的预翻转断面朝向一致)
    gp_Ax3 src(gp::Origin(), gp::DZ(), gp::DX());
    gp_Ax3 tgt(gp::Origin(), t0, Hd.Reversed());
    gp_Trsf r; r.SetTransformation(tgt, src);
    rail = BRepBuilderAPI_Transform(rail, r).Shape();

    // Translate to path start + lateral/vertical offsets (沿 Hd/Vd, 与放样一致)
    gp_Trsf tr;
    tr.SetTranslation(gp_Vec(p0.XYZ() + Hd.XYZ() * lateralOffset + Vd.XYZ() * verticalOffset));
    return BRepBuilderAPI_Transform(rail, tr).Shape();
  }

  // ARC / BEZIER paths → ThruSections loft
  // 截面数上限: 长中心线按 ~500mm 采样会无界增长 (10km=20000 截面,
  // ThruSections 复杂度超线性), 封顶后放大采样间距
  int nSec = std::max(2, std::min(512, (int)(tot / 500.0)));
  BRepOffsetAPI_ThruSections loft(Standard_True, Standard_True);
  for (int i = 0; i <= nSec; ++i) {
    double target = tot * i / nSec;
    double walked = 0;
    bool found = false;
    for (auto &cr : crvs) {
      if (walked + cr.l >= target - 1e-9) {
        double frac = (target - walked) / cr.l;
        double u = cr.c->FirstParameter() + frac * (cr.c->LastParameter() - cr.c->FirstParameter());
        gp_Pnt pt; gp_Vec vt; cr.c->D1(u, pt, vt);
        loft.AddWire(makeSection(pt, gp_Dir(vt)));
        found = true; break;
      }
      walked += cr.l;
    }
    if (!found) {
      gp_Pnt pt; gp_Vec vt;
      crvs.back().c->D1(crvs.back().c->LastParameter(), pt, vt);
      loft.AddWire(makeSection(pt, gp_Dir(vt)));
    }
  }
  loft.Build();
  if (!loft.IsDone()) throw Standard_ConstructionError("Rail path loft failed");
  return loft.Shape();
}

// =========================================================================
// 25. Sleeper (轨枕)
// =========================================================================
TopoDS_Shape create_sleeper(const sleeper_params &params) {
    sleeper_line_params sp;
    sp.startPoint = gp_Pnt(-params.length / 2, 0, 0);
    sp.endPoint = gp_Pnt(params.length / 2, 0, 0);
    sp.width = params.width;
    sp.height = params.height;
    sp.grooveDepth = params.grooveDepth;
    sp.gauge = params.gauge;
    sp.grooveWidth = params.railBaseWidth > 0 ? params.railBaseWidth : 150;
    sp.sleeperType = 2;
    sp.shapeType = (int)params.shapeType;
    return create_sleeper_line(sp);
}

TopoDS_Shape create_sleeper(const sleeper_params &params,
                            const gp_Pnt &position, const gp_Dir &direction,
                            const gp_Dir &upDir) {
  TopoDS_Shape shape = create_sleeper(params);
  gp_Dir yDir = upDir.Crossed(direction);
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, upDir, direction);
  gp_Trsf t;
  t.SetTransformation(targetAx3, sourceAx3);
  return BRepBuilderAPI_Transform(shape, t).Shape();
}

// =========================================================================
// 26. Ballast Bed (道床)
// =========================================================================
// 沿完整中心线(所有段, 支持直线/圆弧/贝塞尔/坡度)放样梯形道床断面
// 断面顶面与中心线齐平, tiltAngle 为绕路径切向的超高倾角(rad)
TopoDS_Shape create_ballast(const ballast_params &params) {
  if (params.centerlineSegments.empty())
    throw Standard_ConstructionError("ballast: no centerline");
  double tw = params.topWidth, th = params.thickness, ss = params.sideSlope;
  if (tw <= 0 || th <= 0)
    throw Standard_ConstructionError("ballast: invalid dimensions");
  double bw = tw + 2 * th * ss, hbw = bw / 2, htw = tw / 2;

  // 断面模板 (局部坐标: X=横向, Y=竖向, 底边中心为原点)
  TopoDS_Wire tmpl;
  {
    BRepBuilderAPI_MakeWire w;
    w.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(-hbw, 0, 0), gp_Pnt(hbw, 0, 0)));
    w.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(hbw, 0, 0), gp_Pnt(htw, th, 0)));
    w.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(htw, th, 0), gp_Pnt(-htw, th, 0)));
    w.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(-htw, th, 0), gp_Pnt(-hbw, 0, 0)));
    tmpl = w.Wire();
  }
  // 截面坐标架 (Hd, t×Hd, t) 相对轮廓映射 (Hd, Vd, t) 为镜像, 预翻转模板
  TopoDS_Shape tmplMir;
  {
    gp_Trsf flip;
    flip.SetMirror(gp_Ax2(gp::Origin(), gp::DY()));
    tmplMir = BRepBuilderAPI_Transform(tmpl, flip).Shape();
  }

  double tilt = params.tiltAngle;
  // Build section at a path point p with tangent t (断面顶面与中心线齐平 → 原点下沉 th)
  auto makeSection = [&](const gp_Pnt &p, const gp_Dir &t) {
    gp_Vec Hv(t.XYZ().Crossed(gp::DZ().XYZ()));
    gp_Dir Hd = Hv.Magnitude() < Precision::Confusion() ? gp::DX() : gp_Dir(Hv);
    gp_Dir Vd = Hd.Crossed(t);
    // Superelevation tilt: rotate (H,V) frame around T
    if (std::abs(tilt) > Precision::Angular()) {
      gp_Trsf rot;
      rot.SetRotation(gp_Ax1(gp::Origin(), t), tilt);
      gp_XYZ hx = Hd.XYZ(); rot.Transforms(hx); Hd = gp_Dir(hx);
      gp_XYZ vx = Vd.XYZ(); rot.Transforms(vx); Vd = gp_Dir(vx);
    }
    gp_Pnt o = p.Translated(gp_Vec(Vd.XYZ() * (-th)));
    gp_Ax3 src(gp::Origin(), gp::DZ(), gp::DX());
    gp_Ax3 tgt(o, t, Hd);
    gp_Trsf tr;
    tr.SetTransformation(tgt, src);
    return TopoDS::Wire(BRepBuilderAPI_Transform(tmplMir, tr).Shape());
  };

  // Build curves per segment (与 create_rail_path 相同的路径展开)
  struct CR { Handle(Geom_Curve) c; double l; };
  std::vector<CR> crvs;
  for (auto &seg : params.centerlineSegments) {
    if (seg.points.size() < 2) continue;
    if (seg.type == centerline_curve_type::LINE) {
      double d = seg.points[0].Distance(seg.points[1]);
      if (d < Precision::Confusion()) continue;
      Handle(Geom_TrimmedCurve) tc = GC_MakeSegment(seg.points[0], seg.points[1]).Value();
      crvs.push_back({Handle(Geom_Curve)(tc), d});
    } else if (seg.type == centerline_curve_type::ARC && seg.points.size() >= 3) {
      Handle(Geom_TrimmedCurve) arc = GC_MakeArcOfCircle(seg.points[0], seg.points[1], seg.points[2]);
      if (!arc.IsNull()) {
        double al = 0;
        Handle(Geom_Curve) bc = arc->BasisCurve();
        if (!bc.IsNull()) {
          double r = Handle(Geom_Circle)::DownCast(bc)->Circ().Radius();
          al = r * std::abs(arc->LastParameter() - arc->FirstParameter());
        }
        if (al > Precision::Confusion())
          crvs.push_back({Handle(Geom_Curve)(arc), al});
      }
    } else if (seg.type == centerline_curve_type::BEZIER) {
      Handle(TColgp_HArray1OfPnt) arr = new TColgp_HArray1OfPnt(1, (int)seg.points.size());
      for (size_t i = 0; i < seg.points.size(); ++i) arr->SetValue((int)(i + 1), seg.points[i]);
      Handle(Geom_Curve) bez = new Geom_BezierCurve(arr->Array1());
      crvs.push_back({bez, seg.points.front().Distance(seg.points.back())});
    }
  }
  if (crvs.empty()) throw Standard_ConstructionError("ballast: no valid centerline");

  double tot = 0;
  for (auto &cr : crvs) tot += cr.l;

  // ThruSections 放样; 两端沿切向各外延 500mm (与旧行为一致, 道床长出端部)
  // 截面数上限: 长中心线按 ~500mm 采样会无界增长 (10km=20000 截面,
  // ThruSections 复杂度超线性), 封顶后放大采样间距
  int nSec = std::max(2, std::min(512, (int)(tot / 500.0)));
  BRepOffsetAPI_ThruSections loft(Standard_True, Standard_True);
  {
    gp_Pnt p; gp_Vec v;
    crvs.front().c->D1(crvs.front().c->FirstParameter(), p, v);
    gp_Dir t(v);
    loft.AddWire(makeSection(p.Translated(gp_Vec(t.XYZ() * (-500.0))), t));
  }
  for (int i = 0; i <= nSec; ++i) {
    double target = tot * i / nSec;
    double walked = 0;
    bool found = false;
    for (auto &cr : crvs) {
      if (walked + cr.l >= target - 1e-9) {
        double frac = (target - walked) / cr.l;
        double u = cr.c->FirstParameter() + frac * (cr.c->LastParameter() - cr.c->FirstParameter());
        gp_Pnt pt; gp_Vec vt; cr.c->D1(u, pt, vt);
        loft.AddWire(makeSection(pt, gp_Dir(vt)));
        found = true; break;
      }
      walked += cr.l;
    }
    if (!found) {
      gp_Pnt pt; gp_Vec vt;
      crvs.back().c->D1(crvs.back().c->LastParameter(), pt, vt);
      loft.AddWire(makeSection(pt, gp_Dir(vt)));
    }
  }
  {
    gp_Pnt p; gp_Vec v;
    crvs.back().c->D1(crvs.back().c->LastParameter(), p, v);
    gp_Dir t(v);
    loft.AddWire(makeSection(p.Translated(gp_Vec(t.XYZ() * 500.0)), t));
  }
  loft.Build();
  if (!loft.IsDone()) throw Standard_ConstructionError("Ballast loft failed");
  return loft.Shape();
}

TopoDS_Shape create_track_slab(const track_slab_params &params) {
  if (params.length <= 0 || params.width <= 0 || params.thickness <= 0)
    throw Standard_ConstructionError("Dimensions must be positive");

  // Main slab
  gp_Pnt slabOrigin(-params.length / 2, -params.width / 2, 0);
  TopoDS_Shape slab = BRepPrimAPI_MakeBox(slabOrigin, params.length,
                                          params.width, params.thickness)
                          .Shape();

  // Rail seats on top
  int nSeats = std::max(2, params.railSeatCount);
  double seatSpacing = params.railSeatSpacing > 0 ? params.railSeatSpacing
                                                  : params.length / nSeats;
  double seatW = 200;
  double seatH = 30;

  for (int i = 0; i < nSeats; ++i) {
    double x = -params.length / 2 + (i + 0.5) * seatSpacing;
    gp_Pnt seatOrigin(x - seatW / 2, -seatW / 2, params.thickness);
    TopoDS_Shape seat =
        BRepPrimAPI_MakeBox(seatOrigin, seatW, seatW, seatH).Shape();
    slab = BRepAlgoAPI_Fuse(slab, seat).Shape();
  }

  // CA mortar layer underneath
  if (params.cementAsphaltThickness > 0) {
    double caH = params.cementAsphaltThickness;
    gp_Pnt caOrigin(-params.length / 2, -params.width / 2, -caH);
    TopoDS_Shape caLayer =
        BRepPrimAPI_MakeBox(caOrigin, params.length, params.width, caH).Shape();
    slab = BRepAlgoAPI_Fuse(slab, caLayer).Shape();
  }

  return slab;
}

TopoDS_Shape create_track_slab(const track_slab_params &params,
                               const gp_Pnt &position, const gp_Dir &direction,
                               const gp_Dir &upDir) {
  TopoDS_Shape shape = create_track_slab(params);
  gp_Dir yDir = upDir.Crossed(direction);
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, upDir, direction);
  gp_Trsf t;
  t.SetTransformation(targetAx3, sourceAx3);
  return BRepBuilderAPI_Transform(shape, t).Shape();
}

// =========================================================================
// 28. Fastener (扣件)
// =========================================================================
TopoDS_Shape create_fastener(const fastener_params &params) {
    fastener_point_params fp;
    fp.position = gp::Origin();
    fp.railNormal = gp::DY();
    fp.railBaseWidth = 150.0;
    fp.padThickness = params.padThickness;
    return create_fastener_point(fp);
}

TopoDS_Shape create_fastener(const fastener_params &params,
                             const gp_Pnt &position, const gp_Dir &direction,
                             const gp_Dir &upDir) {
    fastener_point_params fp;
    fp.position = position;
    fp.railNormal = upDir.Crossed(direction);
    fp.railBaseWidth = 150.0;
    fp.padThickness = params.padThickness;
    return create_fastener_point(fp);
}

// =========================================================================
// 29. Guard Rail (护轨)
// =========================================================================
TopoDS_Shape create_guard_rail(const guard_rail_params &params) {
    guard_rail_curve_params gp;
    gp.curve.type = rail_curve_type::LINE;
    gp.curve.startPoint = gp::Origin();
    gp.curve.endPoint = gp_Pnt(params.totalLength, 0, 0);
    gp.channelHeight = params.height;
    gp.grooveWidth = params.grooveWidth;
    gp.flangeWidth = std::max((params.baseWidth - params.grooveWidth) / 2 - 12.0, 10.0);
    return create_guard_rail_curve(gp);
}

TopoDS_Shape create_guard_rail(const guard_rail_params &params,
                                const gp_Pnt &startPoint,
                               const gp_Pnt &endPoint) {
    guard_rail_curve_params gp;
    gp.curve.type = rail_curve_type::LINE;
    gp.curve.startPoint = startPoint;
    gp.curve.endPoint = endPoint;
    gp.channelHeight = params.height;
    gp.grooveWidth = params.grooveWidth;
    gp.flangeWidth = std::max((params.baseWidth - params.grooveWidth) / 2 - 12.0, 10.0);
    return create_guard_rail_curve(gp);
}

// =========================================================================
// 30. Mast Assembly (支柱装配)
// =========================================================================
TopoDS_Shape create_mast_assembly(const mast_assembly_params &params) {
  // 局部坐标: 原点=柱底中心, +X=指向线路, +Y=沿线路, Z=向上
  // 尺寸链: 平腕臂高 = 导高+结构高度-150; 下底座 = 平腕臂-1300
  BRep_Builder bld; TopoDS_Compound cmp; bld.MakeCompound(cmp);
  const double CH = params.contactHeight > 0 ? params.contactHeight : 5300;
  const double SH = params.structureHeight > 0 ? params.structureHeight : 1400;
  const double CX = params.sideOffset > 0 ? params.sideOffset : 2900;
  const double messengerZ = CH + SH;
  const double mastHalf = 150.0;
  const double armD = params.armDiameter > 0 ? params.armDiameter : 60;

  // 1. 支柱
  if (params.mastType == 2) {
    concrete_mast_params mp{};
    mp.sectionType = concrete_mast_section_type::CIRCULAR;
    mp.height = params.mastHeight;
    mp.topWidth = 250; mp.bottomWidth = 350; mp.wallThickness = 60;
    bld.Add(cmp, create_concrete_mast(mp));
  } else {
    steel_mast_params mp{steel_mast_type::H_BEAM, params.mastHeight, 200, 300,
                         10, 16, 350, 200, 24, 1};
    bld.Add(cmp, create_steel_mast(mp));
  }

  if (params.cantileverType > 0) {
    const double levelZ = messengerZ - 150;   // 平腕臂轴线高
    const double lowerZ = levelZ - 1300;      // 下底座高
    const double insLen = 700;                // 棒式绝缘子长
    const double bracketT = 80;
    const double armStartX = mastHalf + bracketT + insLen;
    const double tipX = CX - params.stagger;  // 定位点 X (拉出值偏向支柱为正)
    const double armLen = tipX - armStartX;
    const double rise = 3.0 * M_PI / 180.0;

    // 2. 支柱连接座 ×2
    mast_bracket_params bp;
    bp.boltSpacing = 80; bp.boltDiameter = 16;
    bp.height = 150; bp.width = 120; bp.thickness = 12;
    bp.insulatorBoltSpacing = 60; bp.insulatorBoltDiameter = 14;
    bp.mountAngle = 0; bp.mastDiameter = 0;
    bld.Add(cmp, create_mast_bracket(bp, gp_Pnt(mastHalf, 0, levelZ), gp::DX(), gp::DZ()));
    bld.Add(cmp, create_mast_bracket(bp, gp_Pnt(mastHalf, 0, lowerZ), gp::DX(), gp::DZ()));

    // 3. 棒式绝缘子 ×2 (沿腕臂轴)
    rod_insulator_params rip;
    rip.type = rod_insulator_type::SOLID;
    rip.height = insLen; rip.outerDiameter = 80; rip.innerDiameter = 0;
    rip.shedDiameter = 150; rip.shedSpacing = 65; rip.shedCount = 8;
    rip.endFitting = end_fitting_type::FLANGE;
    rip.flangeDiameter = 110; rip.flangeBoltSpacing = 80; rip.flangeBoltDiameter = 12;
    bld.Add(cmp, create_rod_insulator(rip, gp_Pnt(mastHalf + bracketT, 0, levelZ), gp::DX()));
    bld.Add(cmp, create_rod_insulator(rip, gp_Pnt(mastHalf + bracketT, 0, lowerZ), gp::DX()));

    // 4. 平腕臂 (仰角 3°)
    level_cantilever_params lp{armLen, armD, 4, levelZ, 3};
    bld.Add(cmp, create_level_cantilever(lp, gp_Pnt(armStartX, 0, levelZ), gp::DX(), gp::DZ()));

    // 5. 斜腕臂 (下绝缘子端 → 平腕臂 65% 处, 三角桁架)
    {
      double jointX = armStartX + armLen * 0.65;
      double jointZ = levelZ + armLen * 0.65 * std::tan(rise);
      gp_Pnt sl0(armStartX, 0, lowerZ), sl1(jointX, 0, jointZ);
      gp_Vec slv(sl0, sl1);
      slant_cantilever_params sp{slv.Magnitude(), armD, 4, 45};
      bld.Add(cmp, create_slant_cantilever(sp, sl0, gp_Dir(slv), gp::DZ()));
    }

    // 6. 承力索座 (平腕臂外端顶面, 线槽沿 Y=线路方向)
    {
      mw_saddle_params sp2{150, 80, 60, 7, 12};
      double sz = messengerZ + 7 - 60; // 线槽底 = 承力索高
      bld.Add(cmp, create_mw_saddle(sp2, gp_Pnt(tipX - 250, 0, sz), gp::DZ(), gp::DX()));
    }

    // 7. 定位器 (平腕臂端部 → 接触线点)
    {
      gp_Pnt r0(tipX - 150, 0, levelZ + armLen * std::tan(rise));
      gp_Pnt r1(tipX, 0, CH + 30);
      gp_Vec rv(r0, r1);
      registration_arm_params rp2;
      rp2.type = registration_arm_type::STRAIGHT;
      rp2.length = rv.Magnitude();
      rp2.tubeWidth = 34; rp2.tubeHeight = 30; rp2.wallThickness = 3;
      rp2.angle = 0; rp2.isReverse = false;
      bld.Add(cmp, create_registration_arm(rp2, r0, gp_Dir(rv), gp::DZ()));
    }

    // 8. 补偿装置 (锚柱): 棘轮 + 坠砣串
    if (params.compType > 0) {
      ratchet_compensator_params rp3;
      TopoDS_Shape comp = create_ratchet_compensator(
          rp3, gp_Pnt(mastHalf + 260, -250, messengerZ + 260), gp::DY());
      bld.Add(cmp, comp);
    }

    // 9. 下锚拉线
    if (params.hasGuyWire) {
      guy_wire_params gp2;
      gp2.length = 9000; gp2.diameter = 11; gp2.angle = 45;
      gp2.ratedTension = params.ratedTension;
      gp2.hasInsulator = true; gp2.insulatorCount = 2;
      gp2.anchorRodDiameter = 20; gp2.anchorRodLength = 1800;
      gp2.anchorPlateLength = 600; gp2.anchorPlateWidth = 400;
      bld.Add(cmp, create_guy_wire(gp2, gp_Pnt(-4500, 0, -200),
                                   gp_Pnt(0, 0, params.mastHeight * 0.75)));
    }
  }
  return cmp;
}

TopoDS_Shape create_mast_assembly(const mast_assembly_params &params,
                                  const gp_Pnt &position,
                                  const gp_Dir &direction,
                                  const gp_Dir &upDir) {
  TopoDS_Shape shape = create_mast_assembly(params);
  gp_Dir yDir = upDir.Crossed(direction);
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, upDir, direction);
  gp_Trsf t;
  t.SetTransformation(targetAx3, sourceAx3);
  return BRepBuilderAPI_Transform(shape, t).Shape();
}

// =========================================================================
// 30b. Weight Stack (坠砣串) / Ratchet Compensator (棘轮补偿装置)
// =========================================================================
TopoDS_Shape create_weight_stack(const weight_stack_params &params) {
  // 局部: 杆顶在原点, 串向下 (-Z) 悬挂
  BRep_Builder bld; TopoDS_Compound cmp; bld.MakeCompound(cmp);
  double rr = params.rodDiameter / 2;
  // 坠砣杆
  bld.Add(cmp, BRepPrimAPI_MakeCylinder(
      gp_Ax2(gp_Pnt(0, 0, -params.rodLength), gp::DZ()), rr,
      params.rodLength).Shape());
  // 底部托盘
  bld.Add(cmp, BRepPrimAPI_MakeCylinder(
      gp_Ax2(gp_Pnt(0, 0, -params.rodLength), gp::DZ()),
      params.blockDiameter * 0.35, 10).Shape());
  // 坠砣叠放
  double z = -params.rodLength + 10;
  for (int i = 0; i < params.blockCount; ++i) {
    balance_weight_params bp{params.blockDiameter, params.blockHeight,
                             params.blockHeight, params.holeDiameter};
    bld.Add(cmp, create_balance_weight(bp, gp_Pnt(0, 0, z), gp::DZ(), gp::DX()));
    z += params.blockHeight + params.blockGap;
  }
  return cmp;
}

TopoDS_Shape create_weight_stack(const weight_stack_params &params,
                                 const gp_Pnt &topPoint) {
  TopoDS_Shape s = create_weight_stack(params);
  gp_Trsf tr;
  tr.SetTranslation(gp_Vec(topPoint.XYZ()));
  return BRepBuilderAPI_Transform(s, tr).Shape();
}

TopoDS_Shape create_ratchet_compensator(const ratchet_compensator_params &params) {
  // 局部: 棘轮中心在原点, 轴向 Y; 坠砣串悬挂于轮下方
  BRep_Builder bld; TopoDS_Compound cmp; bld.MakeCompound(cmp);
  const double wr = params.wheelDiameter / 2;
  const double ww = params.wheelWidth;
  // 棘轮盘
  TopoDS_Shape wheel = BRepPrimAPI_MakeCylinder(
      gp_Ax2(gp_Pnt(0, -ww / 2, 0), gp::DY()), wr, ww).Shape();
  // 中心轴孔
  wheel = BRepAlgoAPI_Cut(wheel, BRepPrimAPI_MakeCylinder(
      gp_Ax2(gp_Pnt(0, -ww / 2 - 1, 0), gp::DY()), wr * 0.1, ww + 2).Shape()).Shape();
  // 减重孔 ×4
  for (int k = 0; k < 4; ++k) {
    double a = k * M_PI / 2 + M_PI / 4;
    wheel = BRepAlgoAPI_Cut(wheel, BRepPrimAPI_MakeCylinder(
        gp_Ax2(gp_Pnt(wr * 0.55 * std::cos(a), -ww / 2 - 1,
                      wr * 0.55 * std::sin(a)),
               gp::DY()),
        wr * 0.16, ww + 2).Shape()).Shape();
  }
  // 轮缘 V 形绳槽 (回转切除)
  {
    double gw = params.ropeDiameter + 2;
    BRepBuilderAPI_MakeWire tri;
    gp_Pnt t0(wr + 1, 0, -gw / 2), t1(wr + 1, 0, gw / 2),
           t2(wr - gw * 0.8, 0, 0);
    tri.Add(BRepBuilderAPI_MakeEdge(t0, t1));
    tri.Add(BRepBuilderAPI_MakeEdge(t1, t2));
    tri.Add(BRepBuilderAPI_MakeEdge(t2, t0));
    TopoDS_Face f = BRepLib_MakeFace(tri.Wire()).Face();
    BRepPrimAPI_MakeRevol rev(f, gp_Ax1(gp::Origin(), gp::DY()));
    rev.Build();
    if (rev.IsDone())
      wheel = BRepAlgoAPI_Cut(wheel, rev.Shape()).Shape();
  }
  bld.Add(cmp, wheel);
  // 安装支架 (轮后侧)
  bld.Add(cmp, BRepPrimAPI_MakeBox(
      gp_Pnt(-wr - 20, -ww * 0.8, -wr * 0.4), 20, ww * 1.6, wr * 0.8).Shape());
  // 补偿绳 (轮底 → 坠砣串顶)
  double stackTopZ = -wr - params.ropeDiameter;
  bld.Add(cmp, BRepPrimAPI_MakeCylinder(
      gp_Ax2(gp_Pnt(0, 0, stackTopZ - params.strokeLength), gp::DZ()),
      params.ropeDiameter / 2, params.strokeLength).Shape());
  // 坠砣串
  bld.Add(cmp, create_weight_stack(
      params.stack, gp_Pnt(0, 0, stackTopZ - params.strokeLength)));
  return cmp;
}

TopoDS_Shape create_ratchet_compensator(const ratchet_compensator_params &params,
                                        const gp_Pnt &wheelCenter,
                                        const gp_Dir &wheelAxis) {
  TopoDS_Shape s = create_ratchet_compensator(params);
  // 局部轮轴沿 Y → 目标坐标系 Y 轴对齐 wheelAxis (wheelAxis=DY 时为恒等变换)
  gp_Dir xDir = wheelAxis.Crossed(
      std::abs(wheelAxis.Dot(gp::DZ())) < 0.9 ? gp::DZ() : gp::DX());
  gp_Ax3 src(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 tgt(wheelCenter, xDir.Crossed(wheelAxis), xDir);
  gp_Trsf tr;
  tr.SetTransformation(tgt, src);
  return BRepBuilderAPI_Transform(s, tr).Shape();
}

// =========================================================================
// 30c. Auxiliary Wire (附加导线本体)
// =========================================================================
TopoDS_Shape create_auxiliary_wire(const auxiliary_wire_params &params,
                                   const gp_Pnt &startPoint,
                                   const gp_Pnt &endPoint) {
  suspension_cable_params sc;
  sc.startPoint = startPoint;
  sc.endPoint = endPoint;
  sc.diameter = params.diameter;
  sc.sag = params.sag;
  sc.cableType = suspension_cable_type::CATENARY;
  sc.tension = params.ratedTension;
  return create_suspension_cable(sc);
}

// =========================================================================
// 30d. Disconnector (隔离开关) / Arrester (避雷器)
// =========================================================================
TopoDS_Shape create_disconnector(const disconnector_params &params) {
  // 局部: 底座中心原点, 触刀沿 X, Z 向上
  BRep_Builder bld; TopoDS_Compound cmp; bld.MakeCompound(cmp);
  const double bL = params.baseLength, bW = params.baseWidth;
  const double insH = params.insulatorHeight;
  // 1. 底座 + 安装孔
  TopoDS_Shape base = BRepPrimAPI_MakeBox(
      gp_Pnt(-bL / 2, -bW / 2, 0), bL, bW, 16).Shape();
  for (int s = -1; s <= 1; s += 2)
    base = BRepAlgoAPI_Cut(base, BRepPrimAPI_MakeCylinder(
        gp_Ax2(gp_Pnt(s * (bL / 2 - 40), 0, -1), gp::DZ()), 9, 18).Shape()).Shape();
  bld.Add(cmp, base);
  // 2. 支柱绝缘子 ×2 (简化为带伞裙棒式)
  rod_insulator_params rip;
  rip.type = rod_insulator_type::SOLID;
  rip.height = insH; rip.outerDiameter = 70; rip.innerDiameter = 0;
  rip.shedDiameter = 120; rip.shedSpacing = 55; rip.shedCount = 6;
  rip.endFitting = end_fitting_type::FLANGE;
  rip.flangeDiameter = 90; rip.flangeBoltSpacing = 65; rip.flangeBoltDiameter = 10;
  double insX = bL / 2 - 100;
  bld.Add(cmp, create_rod_insulator(rip, gp_Pnt(-insX, 0, 16), gp::DZ()));
  bld.Add(cmp, create_rod_insulator(rip, gp_Pnt(insX, 0, 16), gp::DZ()));
  double topZ = 16 + insH;
  // 3. 静触头 ×2 (导电块 + 接线端子)
  for (int s = -1; s <= 1; s += 2) {
    bld.Add(cmp, BRepPrimAPI_MakeBox(
        gp_Pnt(s * insX - 30, -25, topZ), 60, 50, 20).Shape());
    bld.Add(cmp, BRepPrimAPI_MakeCylinder(
        gp_Ax2(gp_Pnt(s * insX, 0, topZ + 20), gp::DZ()), 8, 25).Shape());
  }
  // 4. 动触刀 (铰链于左侧, 分闸旋转 openAngle)
  {
    double bl = params.bladeLength;
    TopoDS_Shape blade = BRepPrimAPI_MakeBox(
        gp_Pnt(0, -12, -8), bl, 24, 16).Shape();
    double a = params.openAngle * M_PI / 180.0;
    gp_Trsf rot;
    rot.SetRotation(gp_Ax1(gp_Pnt(-insX, 0, topZ + 28), gp::DY()), -a);
    bld.Add(cmp, BRepBuilderAPI_Transform(blade, rot).Shape());
    // 铰链销
    bld.Add(cmp, BRepPrimAPI_MakeCylinder(
        gp_Ax2(gp_Pnt(-insX, -30, topZ + 28), gp::DY()), 10, 60).Shape());
  }
  // 5. 操作机构箱
  bld.Add(cmp, BRepPrimAPI_MakeBox(
      gp_Pnt(-bL / 2 - 60, -bW / 2, 0), 60, bW, insH * 0.5).Shape());
  return cmp;
}

TopoDS_Shape create_disconnector(const disconnector_params &params,
                                 const gp_Pnt &position, const gp_Dir &direction,
                                 const gp_Dir &upDir) {
  TopoDS_Shape s = create_disconnector(params);
  gp_Ax3 src(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 tgt(position, upDir, direction);
  gp_Trsf tr;
  tr.SetTransformation(tgt, src);
  return BRepBuilderAPI_Transform(s, tr).Shape();
}

TopoDS_Shape create_arrester(const arrester_params &params) {
  // 局部: 底面中心原点, Z 向上
  BRep_Builder bld; TopoDS_Compound cmp; bld.MakeCompound(cmp);
  const double R = params.outerDiameter / 2;
  const double H = params.height;
  const double flangeH = H * 0.06;
  // 1. 下法兰 (带安装孔)
  {
    TopoDS_Shape fl = BRepPrimAPI_MakeCylinder(
        gp_Ax2(gp::Origin(), gp::DZ()), R * 1.25, flangeH).Shape();
    for (int k = 0; k < 4; ++k) {
      double a = k * M_PI / 2 + M_PI / 4;
      fl = BRepAlgoAPI_Cut(fl, BRepPrimAPI_MakeCylinder(
          gp_Ax2(gp_Pnt(R * 0.95 * std::cos(a), R * 0.95 * std::sin(a), -1),
                 gp::DZ()), 6, flangeH + 2).Shape()).Shape();
    }
    bld.Add(cmp, fl);
  }
  // 2. 阀片柱主体
  bld.Add(cmp, BRepPrimAPI_MakeCylinder(
      gp_Ax2(gp_Pnt(0, 0, flangeH), gp::DZ()), R, H - 2 * flangeH).Shape());
  // 3. 伞裙 (回转体, 同棒式绝缘子)
  double sp = params.shedSpacing > 0 ? params.shedSpacing
                                     : (H - 2 * flangeH) / (params.shedCount + 1);
  for (int i = 0; i < params.shedCount; ++i) {
    double zPos = flangeH + (i + 1) * sp;
    double r = params.shedDiameter / 2;
    BRepBuilderAPI_MakeWire wire;
    gp_Pnt basePt(R, 0, zPos), u1(r, 0, zPos - sp * 0.06),
           u2(r * 1.02, 0, zPos + sp * 0.05), u3(r * 0.98, 0, zPos + sp * 0.16),
           u4((r + R) / 2, 0, zPos + sp * 0.28), endPt(R, 0, zPos + sp * 0.22);
    wire.Add(BRepBuilderAPI_MakeEdge(basePt, u1));
    wire.Add(BRepBuilderAPI_MakeEdge(GC_MakeArcOfCircle(u1, u2, u3).Value()));
    wire.Add(BRepBuilderAPI_MakeEdge(GC_MakeArcOfCircle(u3, u4, endPt).Value()));
    wire.Add(BRepBuilderAPI_MakeEdge(endPt, basePt));
    BRepPrimAPI_MakeRevol revol(BRepLib_MakeFace(wire.Wire()).Face(),
                                gp_Ax1(gp::Origin(), gp::DZ()));
    revol.Build();
    if (revol.IsDone())
      bld.Add(cmp, revol.Shape());
  }
  // 4. 上法兰 + 接线端子
  bld.Add(cmp, BRepPrimAPI_MakeCylinder(
      gp_Ax2(gp_Pnt(0, 0, H - flangeH), gp::DZ()), R * 1.25, flangeH).Shape());
  bld.Add(cmp, BRepPrimAPI_MakeBox(
      gp_Pnt(-15, -10, H), 30, 20, 8).Shape());
  return cmp;
}

TopoDS_Shape create_arrester(const arrester_params &params,
                             const gp_Pnt &position,
                             const gp_Dir &axisDirection) {
  TopoDS_Shape s = create_arrester(params);
  gp_Ax3 src(gp::Origin(), gp::DZ());
  gp_Ax3 tgt(position, axisDirection);
  gp_Trsf tr;
  tr.SetTransformation(tgt, src);
  return BRepBuilderAPI_Transform(s, tr).Shape();
}

// =========================================================================
// 30e. Pulley Compensator (滑轮补偿装置)
// =========================================================================
TopoDS_Shape create_pulley_compensator(const pulley_compensator_params &params) {
  // 局部: 定滑轮中心原点, 轴向 Y; 动滑轮+坠砣串在下方
  BRep_Builder bld; TopoDS_Compound cmp; bld.MakeCompound(cmp);
  const double pr = params.pulleyDiameter / 2;
  const double rr = params.ropeDiameter / 2;
  const double gw = params.grooveWidth;
  auto pulley = [&](const gp_Pnt &c) {
    TopoDS_Shape w = BRepPrimAPI_MakeCylinder(
        gp_Ax2(gp_Pnt(c.X(), c.Y() - gw / 2, c.Z()), gp::DY()), pr, gw).Shape();
    // 绳槽
    BRepBuilderAPI_MakeWire tri;
    gp_Pnt t0(pr + 1, 0, -gw / 2 + 1), t1(pr + 1, 0, gw / 2 - 1),
           t2(pr - rr, 0, 0);
    tri.Add(BRepBuilderAPI_MakeEdge(t0, t1));
    tri.Add(BRepBuilderAPI_MakeEdge(t1, t2));
    tri.Add(BRepBuilderAPI_MakeEdge(t2, t0));
    BRepPrimAPI_MakeRevol rev(BRepLib_MakeFace(tri.Wire()).Face(),
                              gp_Ax1(gp::Origin(), gp::DY()));
    rev.Build();
    if (rev.IsDone()) {
      gp_Trsf mv;
      mv.SetTranslation(gp_Vec(c.XYZ()));
      w = BRepAlgoAPI_Cut(w, BRepBuilderAPI_Transform(rev.Shape(), mv).Shape()).Shape();
    }
    // 中心孔
    w = BRepAlgoAPI_Cut(w, BRepPrimAPI_MakeCylinder(
        gp_Ax2(gp_Pnt(c.X(), c.Y() - gw / 2 - 1, c.Z()), gp::DY()), pr * 0.12,
        gw + 2).Shape()).Shape();
    return w;
  };
  // 定滑轮 (原点) + 支架
  bld.Add(cmp, pulley(gp::Origin()));
  bld.Add(cmp, BRepPrimAPI_MakeBox(
      gp_Pnt(-pr - 20, -gw, -pr * 0.4), 20, gw * 2, pr * 0.8).Shape());
  // 动滑轮 (下方行程中点)
  double movZ = -params.strokeLength * 0.5;
  bld.Add(cmp, pulley(gp_Pnt(0, 0, movZ)));
  // 补偿绳: 定滑轮 → 动滑轮 → 上返 (简化 U 形绕法)
  bld.Add(cmp, BRepPrimAPI_MakeCylinder(
      gp_Ax2(gp_Pnt(-pr + rr, 0, movZ), gp::DZ()), rr, -movZ).Shape());
  bld.Add(cmp, BRepPrimAPI_MakeCylinder(
      gp_Ax2(gp_Pnt(pr - rr, 0, movZ), gp::DZ()), rr, -movZ).Shape());
  // 动滑轮 → 坠砣串
  double stackTop = movZ - pr - 50;
  bld.Add(cmp, BRepPrimAPI_MakeCylinder(
      gp_Ax2(gp_Pnt(0, 0, stackTop), gp::DZ()), rr, 50).Shape());
  bld.Add(cmp, create_weight_stack(params.stack, gp_Pnt(0, 0, stackTop)));
  // 坠砣限制架 (四角立杆 + 上下环框)
  if (params.hasLimitFrame) {
    double fr = params.stack.blockDiameter * 0.65;
    double zBot = stackTop - params.stack.rodLength - 20;
    for (int sx = -1; sx <= 1; sx += 2)
      for (int sy = -1; sy <= 1; sy += 2)
        bld.Add(cmp, BRepPrimAPI_MakeCylinder(
            gp_Ax2(gp_Pnt(sx * fr, sy * fr, zBot), gp::DZ()), 6,
            stackTop - zBot).Shape());
    for (double z : {zBot, stackTop}) {
      for (int sx = -1; sx <= 1; sx += 2)
        bld.Add(cmp, BRepPrimAPI_MakeBox(
            gp_Pnt(sx > 0 ? fr : -fr - 12, -fr - 6, z - 6), 12, 2 * (fr + 6), 12).Shape());
    }
  }
  return cmp;
}

TopoDS_Shape create_pulley_compensator(const pulley_compensator_params &params,
                                       const gp_Pnt &pulleyCenter,
                                       const gp_Dir &wheelAxis) {
  TopoDS_Shape s = create_pulley_compensator(params);
  // 局部轮轴沿 Y → 目标坐标系 Y 轴对齐 wheelAxis (wheelAxis=DY 时为恒等变换)
  gp_Dir xDir = wheelAxis.Crossed(
      std::abs(wheelAxis.Dot(gp::DZ())) < 0.9 ? gp::DZ() : gp::DX());
  gp_Ax3 src(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 tgt(pulleyCenter, xDir.Crossed(wheelAxis), xDir);
  gp_Trsf tr;
  tr.SetTransformation(tgt, src);
  return BRepBuilderAPI_Transform(s, tr).Shape();
}

// =========================================================================
// 30f. Cantilever Fittings (双套筒连接器 / 套管单耳)
// =========================================================================
TopoDS_Shape create_sleeve_connector(const sleeve_connector_params &params) {
  // 局部: 套筒1 沿 X, 套筒2 绕 Y 旋转 angle, 交于原点
  BRep_Builder bld; TopoDS_Compound cmp; bld.MakeCompound(cmp);
  double R = params.tubeDiameter / 2;
  double ro = R + params.wallThickness;
  double sl = params.sleeveLength;
  auto sleeve = [&](const gp_Trsf &rot) {
    TopoDS_Shape s = BRepAlgoAPI_Cut(
        BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(-sl / 2, 0, 0), gp::DX()), ro, sl).Shape(),
        BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(-sl / 2 - 1, 0, 0), gp::DX()), R, sl + 2).Shape()).Shape();
    // 紧固螺栓 (中部, 沿 Z)
    TopoDS_Shape bolt = BRepPrimAPI_MakeCylinder(
        gp_Ax2(gp_Pnt(0, 0, -ro - 2), gp::DZ()), params.boltDiameter / 2,
        2 * ro + 4).Shape();
    s = BRepAlgoAPI_Fuse(s, bolt).Shape();
    return BRepBuilderAPI_Transform(s, rot).Shape();
  };
  gp_Trsf id;
  bld.Add(cmp, sleeve(id));
  gp_Trsf rot;
  rot.SetRotation(gp_Ax1(gp::Origin(), gp::DY()), params.angle * M_PI / 180.0);
  bld.Add(cmp, sleeve(rot));
  return cmp;
}

TopoDS_Shape create_sleeve_ear(const sleeve_ear_params &params) {
  // 局部: 套筒沿 X, 耳板向上 (+Z)
  BRep_Builder bld; TopoDS_Compound cmp; bld.MakeCompound(cmp);
  double R = params.tubeDiameter / 2;
  double ro = R + params.wallThickness;
  bld.Add(cmp, BRepAlgoAPI_Cut(
      BRepPrimAPI_MakeCylinder(
          gp_Ax2(gp_Pnt(-params.sleeveLength / 2, 0, 0), gp::DX()), ro,
          params.sleeveLength).Shape(),
      BRepPrimAPI_MakeCylinder(
          gp_Ax2(gp_Pnt(-params.sleeveLength / 2 - 1, 0, 0), gp::DX()), R,
          params.sleeveLength + 2).Shape()).Shape());
  // 单耳板 (端部圆角)
  TopoDS_Shape ear = BRepPrimAPI_MakeBox(
      gp_Pnt(-params.earThickness / 2, -params.sleeveLength * 0.3, 0),
      params.earThickness, params.sleeveLength * 0.6, ro + params.earHeight).Shape();
  ear = BRepAlgoAPI_Fuse(ear, BRepPrimAPI_MakeCylinder(
      gp_Ax2(gp_Pnt(-params.earThickness / 2, 0, ro + params.earHeight),
             gp::DX()),
      params.sleeveLength * 0.3, params.earThickness).Shape()).Shape();
  // 耳孔
  ear = BRepAlgoAPI_Cut(ear, BRepPrimAPI_MakeCylinder(
      gp_Ax2(gp_Pnt(-params.earThickness / 2 - 1, 0, ro + params.earHeight),
             gp::DX()),
      params.holeDiameter / 2, params.earThickness + 2).Shape()).Shape();
  bld.Add(cmp, ear);
  return cmp;
}

// =========================================================================
// TRACK: 31. Switch Rail (尖轨) — tapered from tip to heel
// =========================================================================
// TRACK: 32. Frog (辙叉) — V-shaped crossing
// =========================================================================
TopoDS_Shape create_frog(const frog_params &params) {
    // 辙叉 = 4 段心轨 (汇聚到 ~2mm 岔心尖端) + 2 根弯折翼轨 + 2 根护轨
    frog_calculated_params fc = calculate_frog_params(params.turnoutNo, params.gauge);
    BRep_Builder bld; TopoDS_Compound cmp; bld.MakeCompound(cmp);
    const double alpha = std::atan2(1.0, (double)params.turnoutNo);
    const double Lp = fc.frogPointLength;
    const gp_Pnt O(0, 0, 0);

    // 两条交叉轨线关于 X 轴对称, 夹角 = 辙叉角 alpha
    const gp_Dir u1(std::cos(alpha / 2), -std::sin(alpha / 2), 0);
    const gp_Dir u2(std::cos(alpha / 2), +std::sin(alpha / 2), 0);
    auto along = [](const gp_Dir &u, double s) { return gp_Vec(u.XYZ().Multiplied(s)); };

    // 心轨: 每段以 SWITCH 端刨削汇聚到岔心, 刨削侧朝向另一轨线
    auto pointRail = [&](const gp_Dir &u, bool outgoing, int planedSide) {
      rail_curve_params rp;
      rp.curve.type = rail_curve_type::LINE;
      rp.curve.startPoint = outgoing ? O : O.Translated(along(u, -Lp));
      rp.curve.endPoint = outgoing ? O.Translated(along(u, Lp)) : O;
      rp.railHeight = params.railHeight;
      rp.headWidth = params.railHeadWidth;
      rp.baseWidth = params.railBaseWidth;
      end_treatment_params e;
      e.type = end_treatment_type::SWITCH;
      e.toeWidth = 2.0;
      e.switchLength = Lp * 0.7;
      e.planedSide = planedSide;
      (outgoing ? rp.endStart : rp.endFinish) = e;
      return create_rail_curve(rp);
    };
    // u1 线内侧朝 +Y (行进左侧), u2 线内侧朝 -Y (行进右侧)
    try { bld.Add(cmp, pointRail(u1, false, 1)); } catch (...) { warn_part_failed("create_frog", "point rail u1 incoming"); }
    try { bld.Add(cmp, pointRail(u1, true, 1)); } catch (...) { warn_part_failed("create_frog", "point rail u1 outgoing"); }
    try { bld.Add(cmp, pointRail(u2, false, 2)); } catch (...) { warn_part_failed("create_frog", "point rail u2 incoming"); }
    try { bld.Add(cmp, pointRail(u2, true, 2)); } catch (...) { warn_part_failed("create_frog", "point rail u2 outgoing"); }

    // 翼轨: 普通钢轨断面沿真实线形弯折 — 开口段→咽喉弯折→平直段(44mm轮缘槽)
    //       →绕岔心弯折→出口平直段→开口段, u2 侧由镜像生成
    const double groove = fc.guardFlangeGroove;            // 轮缘槽宽 44
    const double wOff = params.railHeadWidth + groove;     // 翼轨/心轨中心距
    const double Lw = fc.wingRailLength;
    const double sB = Lw * 0.30;                           // 出入口平直段
    const double Lf = Lw * 0.25;                           // 开口段长度
    const double fl = 46.0;                                // 开口张开量 (槽宽至 ~90)
    const double csA = std::cos(alpha / 2), snA = std::sin(alpha / 2);
    auto wingRail = [&](const gp_Dir &u, const gp_Dir &v) {
      gp_Dir n(-u.Y(), u.X(), 0);   // u 线轮缘槽侧法向 (行进左)
      gp_Dir nv(v.Y(), -v.X(), 0);  // v 线轮缘槽侧法向 (行进右)
      // 绕岔心: 两条偏移线的竖直连线位于岔心前 wOff 处
      const double xq = wOff;
      const double t1 = (xq - wOff * snA) / csA;
      gp_Pnt P1 = O.Translated(along(u, -sB) + gp_Vec(n.XYZ().Multiplied(wOff)));
      gp_Pnt B1 = O.Translated(gp_Vec(n.XYZ().Multiplied(wOff)) + along(u, t1));
      gp_Pnt B2 = O.Translated(gp_Vec(nv.XYZ().Multiplied(wOff)) + along(v, t1));
      gp_Pnt E0 = P1.Translated(along(u, -Lf) + gp_Vec(n.XYZ().Multiplied(fl)));
      gp_Pnt P3 = B2.Translated(along(v, sB));
      gp_Pnt E1 = P3.Translated(along(v, Lf) + gp_Vec(nv.XYZ().Multiplied(fl)));
      rail_params rp{};
      rp.railHeight = params.railHeight;
      rp.headWidth = params.railHeadWidth;
      rp.baseWidth = params.railBaseWidth;
      rp.webThickness = 16.5;
      rp.headRadius = 13.0;
      std::vector<centerline_segment> segs = {
          {centerline_curve_type::LINE, {E0, P1}},
          {centerline_curve_type::LINE, {P1, B1}},
          {centerline_curve_type::LINE, {B1, B2}},
          {centerline_curve_type::LINE, {B2, P3}},
          {centerline_curve_type::LINE, {P3, E1}}};
      return create_rail_path(rp, segs, 0, 0, 0);
    };
    TopoDS_Shape wing1;
    try { wing1 = wingRail(u1, u2); bld.Add(cmp, wing1); } catch (...) { warn_part_failed("create_frog", "wing rail u1"); }
    // u2 的翼轨 = u1 翼轨关于 XZ 平面镜像
    try {
      gp_Trsf mir;
      mir.SetMirror(gp_Ax2(O, gp::DY()));
      bld.Add(cmp, BRepBuilderAPI_Transform(wing1, mir).Shape());
    } catch (...) { warn_part_failed("create_frog", "wing rail u2 (mirror)"); }

    // 护轨: 43kg 旧钢轨断面, 对侧轨线内侧 gauge-groove 处, 两端弯折张开 (喇叭口)
    const double gOff = params.gauge - groove;
    const double Lg = fc.guardRailLength;
    auto guardRail = [&](const gp_Dir &u, double sideSign) {
      gp_Dir n(-u.Y(), u.X(), 0);
      gp_Vec off(n.XYZ().Multiplied(sideSign * gOff));
      gp_Vec flareDir(n.XYZ().Multiplied(-sideSign * 60.0)); // 端部向辙叉侧张开
      const double bend = 400.0;
      gp_Pnt sB = O.Translated(along(u, -Lg / 2) + off);
      gp_Pnt eB = O.Translated(along(u, Lg / 2) + off);
      gp_Pnt sT = sB.Translated(along(u, -bend) + flareDir);
      gp_Pnt eT = eB.Translated(along(u, bend) + flareDir);
      rail_params rp = standard_rail_params(43);
      std::vector<centerline_segment> segs = {
          {centerline_curve_type::LINE, {sT, sB}},
          {centerline_curve_type::LINE, {sB, eB}},
          {centerline_curve_type::LINE, {eB, eT}}};
      return create_rail_path(rp, segs, 0, 0, 0);
    };
    try { bld.Add(cmp, guardRail(u1, +1)); } catch (...) { warn_part_failed("create_frog", "guard rail u1"); }
    try { bld.Add(cmp, guardRail(u2, -1)); } catch (...) { warn_part_failed("create_frog", "guard rail u2"); }
    return cmp;
}

TopoDS_Shape create_frog(const frog_params &params, const gp_Pnt &position,
                         const gp_Dir &direction, const gp_Dir &upDir) {
    TopoDS_Shape shape = create_frog(params);
    gp_Dir yDir = upDir.Crossed(direction);
    gp_Ax3 src(gp::Origin(), gp::DZ(), gp::DX());
    gp_Ax3 tgt(position, upDir, direction);
    gp_Trsf tr; tr.SetTransformation(tgt, src);
    return BRepBuilderAPI_Transform(shape, tr).Shape();
}

// =========================================================================
// TRACK: 33. Turnout (单开道岔)
// =========================================================================
TopoDS_Shape create_turnout(const turnout_params &params) {
    // 单开道岔布局 (转辙器 → 连接部分 → 辙叉):
    //   直股: 两基本轨沿 X; 侧股中心线以半径 leadR 从岔始点向 sgn 侧弯出
    //   辙叉心 = 直股侧轨 (y=sgn*hg) 与侧股外股 (半径 leadR+hg) 的交叉点
    turnout_assembly_params tap;
    tap.turnoutNo = params.turnoutNo;
    tap.hand = params.isLeftHand ? 1 : 2;
    tap.gauge = params.gauge;

    frog_calculated_params fc = calculate_frog_params(params.turnoutNo, params.gauge);
    const double hg = params.gauge / 2;
    const double swLen = params.switchRailLength > 0 ? params.switchRailLength : fc.switchRailLength;
    const double leadR = params.leadCurveRadius > 0 ? params.leadCurveRadius : fc.leadCurveRadius;
    const double sgn = params.isLeftHand ? 1.0 : -1.0;

    const double Ro = leadR + hg;                     // 侧股外股半径
    const double Ri = leadR - hg;                     // 侧股内股半径
    const double frogX = std::sqrt(Ro * Ro - Ri * Ri); // 辙叉心 X (两轨线交点)
    const double thFrog = std::asin(frogX / Ro);       // 交叉角 (外股圆上)
    const double tail = fc.frogTotalLength;
    const double x0 = -swLen - 2000;                   // 岔前起点
    const double x1 = frogX + tail;                    // 岔后终点

    // 侧股圆弧 (圆心 (0, sgn*leadR)) 上取点
    auto circlePt = [&](double R, double th) {
      return gp_Pnt(R * std::sin(th), sgn * (leadR - R * std::cos(th)), 0);
    };
    auto railSeg = [&](rail_curve_params &rp) {
      rp.railHeight = params.railHeight; rp.headWidth = params.railHeadWidth;
      rp.baseWidth = params.railBaseWidth; rp.webThickness = params.webThickness;
      tap.rails.push_back(rp);
    };

    // 1. 基本轨 (直股两侧)
    rail_curve_params rp;
    rp.curve.type = rail_curve_type::LINE;
    rp.curve.startPoint = gp_Pnt(x0, sgn * hg, 0);
    rp.curve.endPoint = gp_Pnt(x1, sgn * hg, 0);
    railSeg(rp);
    rp.curve.startPoint = gp_Pnt(x0, -sgn * hg, 0);
    rp.curve.endPoint = gp_Pnt(x1, -sgn * hg, 0);
    railSeg(rp);

    // 2. 直尖轨 (贴直股侧股侧基本轨, 尖端在岔始点)
    {
      rail_curve_params sw;
      sw.curve.type = rail_curve_type::LINE;
      sw.curve.startPoint = gp_Pnt(0, sgn * (hg - 2), 0);
      sw.curve.endPoint = gp_Pnt(swLen, sgn * hg, 0);
      sw.endStart.type = end_treatment_type::SWITCH;
      sw.endStart.toeWidth = 2;
      sw.endStart.switchLength = swLen;
      sw.endStart.planedSide = sgn > 0 ? 1 : 2; // 刨削侧朝基本轨
      railSeg(sw);
    }
    // 3. 曲尖轨 (贴另一侧基本轨, 沿侧股外股圆弧)
    {
      double thS = swLen / Ro;
      rail_curve_params sw;
      sw.curve.type = rail_curve_type::ARC;
      sw.curve.startPoint = circlePt(Ro, 0).Translated(gp_Vec(0, sgn * 2, 0));
      sw.curve.controlPoints = {circlePt(Ro, thS / 2)};
      sw.curve.endPoint = circlePt(Ro, thS);
      sw.endStart.type = end_treatment_type::SWITCH;
      sw.endStart.toeWidth = 2;
      sw.endStart.switchLength = swLen;
      sw.endStart.planedSide = sgn > 0 ? 2 : 1;
      railSeg(sw);
    }
    // 4. 导曲线外股 (曲尖轨跟端 → 过辙叉)
    {
      double thS = swLen / Ro;
      double thE = thFrog + tail / Ro;
      rail_curve_params cr;
      cr.curve.type = rail_curve_type::ARC;
      cr.curve.startPoint = circlePt(Ro, thS);
      cr.curve.controlPoints = {circlePt(Ro, (thS + thE) / 2)};
      cr.curve.endPoint = circlePt(Ro, thE);
      railSeg(cr);
    }
    // 5. 导曲线内股 (直尖轨跟端起, 同圆心渐开)
    {
      double thE = thFrog + tail / Ri;
      gp_Pnt p0(swLen, sgn * hg, 0);
      gp_Pnt p2 = circlePt(Ri, thE);
      double thM = (std::asin(swLen / Ri) + thE) / 2;
      rail_curve_params cr;
      cr.curve.type = rail_curve_type::ARC;
      cr.curve.startPoint = p0;
      cr.curve.controlPoints = {circlePt(Ri, thM)};
      cr.curve.endPoint = p2;
      railSeg(cr);
    }

    // 6. 岔枕 (沿直股均布, 转辙区/辙叉区加长)
    // sleeperSpacing > 0 时按间距推算数量, 否则沿用 sleeperCount
    int sc = params.sleeperCount;
    if (params.sleeperSpacing > 0)
        sc = std::max(1, (int)std::floor((x1 - x0) / params.sleeperSpacing));
    for (int i = 0; i < sc; ++i) {
        double t = (double)i / sc;
        double x = x0 + t * (x1 - x0);
        double sl = 2500 + t * 200;
        sleeper_line_params slp;
        slp.startPoint = gp_Pnt(x, -sl / 2, 0);
        slp.endPoint = gp_Pnt(x, sl / 2, 0);
        slp.width = 260; slp.height = 200; slp.gauge = params.gauge;
        tap.sleepers.push_back(slp);
    }

    TopoDS_Shape base = create_turnout_assembly(tap);

    // 7. 辙叉 (心轨+翼轨+护轨): 置于两轨线交点, 旋转半交叉角
    frog_params fp;
    fp.turnoutNo = params.turnoutNo;
    fp.gauge = params.gauge;
    fp.railHeight = params.railHeight;
    fp.railHeadWidth = params.railHeadWidth;
    fp.railBaseWidth = params.railBaseWidth;
    double half = sgn * thFrog / 2;
    TopoDS_Shape frog = create_frog(fp, gp_Pnt(frogX, sgn * hg, 0),
                                    gp_Dir(std::cos(half), std::sin(half), 0),
                                    gp::DZ());

    BRep_Builder bld; TopoDS_Compound cmp; bld.MakeCompound(cmp);
    bld.Add(cmp, base);
    bld.Add(cmp, frog);
    return cmp;
}

TopoDS_Shape create_turnout(const turnout_params &params,
                            const gp_Pnt &position, const gp_Dir &direction,
                            const gp_Dir &upDir) {
    TopoDS_Shape shape = create_turnout(params);
    gp_Dir yDir = upDir.Crossed(direction);
    gp_Ax3 src(gp::Origin(), gp::DZ(), gp::DX());
    gp_Ax3 tgt(position, upDir, direction);
    gp_Trsf tr; tr.SetTransformation(tgt, src);
    return BRepBuilderAPI_Transform(shape, tr).Shape();
}

// =========================================================================
// TRACK: 34. Frog Auto-Calculation (辙叉自动查表)
// =========================================================================
frog_calculated_params calculate_frog_params(int turnoutNo, double gauge) {
  frog_calculated_params p;
  p.turnoutNo = turnoutNo;
  p.frogAngle = atan2(1.0, (double)turnoutNo);
  double N = (double)turnoutNo;

  // Standard lookup tables per Chinese railway specs
  p.frogTotalLength = gauge * N * 0.28;
  p.frogPointLength = p.frogTotalLength * 0.55;
  p.wingRailLength = p.frogTotalLength * 0.6;
  p.guardRailLength = p.frogTotalLength * 0.4;
  p.guardFlangeGroove = 44.0;
  p.throatWidth = gauge * 0.02;

  switch (turnoutNo) {
  case 9:
    p.leadCurveRadius = 180000;
    p.switchRailLength = 6450;
    break;
  case 12:
    p.leadCurveRadius = 350000;
    p.switchRailLength = 7700;
    break;
  case 18:
    p.leadCurveRadius = 800000;
    p.switchRailLength = 12500;
    break;
  case 30:
    p.leadCurveRadius = 2700000;
    p.switchRailLength = 15400;
    break;
  case 42:
    p.leadCurveRadius = 5000000;
    p.switchRailLength = 19200;
    break;
  default:
    p.leadCurveRadius = 350000;
    p.switchRailLength = 7700;
    break;
  }
  return p;
}

// =========================================================================
// TRACK: 35. Rail Pair (轨排对) — 左右股钢轨沿中心线
// =========================================================================
TopoDS_Shape create_rail_pair(const rail_pair_params &params) {
    BRep_Builder bld; TopoDS_Compound cmp; bld.MakeCompound(cmp);
    if (params.centerline.size() < 2) return cmp;
    rail_params rp{};
    rp.railHeight = params.railHeight;
    rp.headWidth = params.railHeadWidth;
    rp.baseWidth = params.railBaseWidth;
    // 完整折线中心线 → LINE 段序列
    std::vector<centerline_segment> segs;
    for (size_t i = 1; i < params.centerline.size(); ++i)
        segs.push_back({centerline_curve_type::LINE,
                        {params.centerline[i - 1], params.centerline[i]}});
    // 超高 → 绕线路切向的倾角 (左右轨同一倾角, 外轨抬高)
    double tilt = params.gauge > 0
                      ? std::atan2(params.superElevation, params.gauge) : 0;
    try { bld.Add(cmp, create_rail_path(rp, segs, -params.gauge / 2, 0, tilt)); } catch (...) { warn_part_failed("create_rail_pair", "left rail"); }
    try { bld.Add(cmp, create_rail_path(rp, segs, params.gauge / 2, 0, tilt)); } catch (...) { warn_part_failed("create_rail_pair", "right rail"); }
    return cmp;
}

TopoDS_Shape create_rail_pair(const rail_pair_params &params,
                              const gp_Pnt &position, const gp_Dir &direction,
                              const gp_Dir &upDir) {
    TopoDS_Shape shape = create_rail_pair(params);
    gp_Dir yDir = upDir.Crossed(direction);
    gp_Ax3 src(gp::Origin(), gp::DZ(), gp::DX());
    gp_Ax3 tgt(position, upDir, direction);
    gp_Trsf tr; tr.SetTransformation(tgt, src);
    return BRepBuilderAPI_Transform(shape, tr).Shape();
}

// =========================================================================
// TRACK: 36. Sleeper Layout (轨枕阵列)
// =========================================================================
TopoDS_Shape create_sleeper_layout(const sleeper_layout_params &params) {
    if (params.centerline.size() < 2 || params.spacing <= 0) return TopoDS_Shape();
    BRep_Builder bld; TopoDS_Compound cmp; bld.MakeCompound(cmp);
    // 累计弧长
    std::vector<double> acc(params.centerline.size(), 0);
    for (size_t i = 1; i < params.centerline.size(); ++i)
        acc[i] = acc[i - 1] + params.centerline[i - 1].Distance(params.centerline[i]);
    double totalLen = acc.back();
    if (totalLen < params.spacing) return TopoDS_Shape();
    int count = std::max(1, (int)std::floor(totalLen / params.spacing));
    double step = totalLen / count; // 弧长等间距
    for (int i = 0; i <= count; ++i) {
        double d = i * step;
        // 定位到弧长 d 处并求切向
        size_t j = 1;
        while (j < acc.size() - 1 && acc[j] < d) ++j;
        double segL = acc[j] - acc[j - 1];
        double lt = segL > Precision::Confusion() ? (d - acc[j - 1]) / segL : 0;
        gp_Vec tv(params.centerline[j - 1], params.centerline[j]);
        gp_Pnt pos = params.centerline[j - 1].Translated(tv * lt);
        if (tv.Magnitude() < Precision::Confusion()) continue;
        // 轨枕方向 = 切向 × 竖直 (水平面内垂直于线路, 曲线上即径向)
        gp_Vec sidev(gp_Dir(tv).XYZ().Crossed(gp::DZ().XYZ()));
        if (sidev.Magnitude() < Precision::Confusion()) sidev = gp::DY().XYZ();
        gp_Vec side(sidev.Normalized());
        sleeper_line_params sp;
        sp.startPoint = pos.Translated(side * (-params.length / 2));
        sp.endPoint = pos.Translated(side * (params.length / 2));
        sp.width = params.width;
        sp.height = params.height;
        sp.gauge = params.gauge;
        try { bld.Add(cmp, create_sleeper_line(sp)); } catch (...) { warn_part_failed("create_sleeper_layout", "sleeper"); }
    }
    return cmp;
}

// =============================================================

// =========================================================================
// TRACK: 37. Straight Track (直线轨道段) — element assembly
// =========================================================================
TopoDS_Shape create_straight_track(const straight_track_params &params) {
  BRep_Builder bld; TopoDS_Compound cmp; bld.MakeCompound(cmp);
  double hg = params.gauge / 2;
  gp_Vec dir(params.startPoint, params.endPoint);
  double len = dir.Magnitude();
  if (len < Precision::Confusion()) return cmp;
  gp_Dir tan(dir);
  // 横向: 水平面内垂直于线路
  gp_Vec sidev(tan.XYZ().Crossed(gp::DZ().XYZ()));
  if (sidev.Magnitude() < Precision::Confusion()) sidev = gp::DY().XYZ();
  gp_Vec side(sidev.Normalized());

  // Rails
  rail_curve_params rp;
  rp.curve.type = rail_curve_type::LINE;
  rp.curve.startPoint = params.startPoint.Translated(side * (-hg));
  rp.curve.endPoint = params.endPoint.Translated(side * (-hg));
  rp.railHeight = params.railHeight; rp.headWidth = params.railHeadWidth;
  rp.baseWidth = params.railBaseWidth; rp.webThickness = params.webThickness;
  try { bld.Add(cmp, create_rail_curve(rp)); } catch (...) { warn_part_failed("create_straight_track", "left rail"); }
  rp.curve.startPoint = params.startPoint.Translated(side * hg);
  rp.curve.endPoint = params.endPoint.Translated(side * hg);
  try { bld.Add(cmp, create_rail_curve(rp)); } catch (...) { warn_part_failed("create_straight_track", "right rail"); }

  // Sleepers (垂直于线路方向, 弧长等距)
  if (!(params.sleeperSpacing > Precision::Confusion()))
    throw Standard_ConstructionError("sleeperSpacing must be positive");
  int sc = std::max(2, (int)(len / params.sleeperSpacing));
  // 上限防护: 极小间距会把轨枕循环放大到数亿次
  if (sc > 100000)
    throw Standard_ConstructionError("sleeperSpacing too small for track length");
  for (int i = 0; i < sc; ++i) {
    double t = (double)i / (sc - 1);
    gp_Pnt pos = params.startPoint.Translated(dir * t);
    sleeper_line_params slp;
    slp.startPoint = pos.Translated(side * (-params.sleeperLength / 2));
    slp.endPoint = pos.Translated(side * (params.sleeperLength / 2));
    slp.width = params.sleeperWidth; slp.height = params.sleeperHeight;
    slp.gauge = params.gauge;
    try { bld.Add(cmp, create_sleeper_line(slp)); } catch (...) { warn_part_failed("create_straight_track", "sleeper"); }
  }

  // Ballast (沿中心线放样梯形断面)
  ballast_params bp;
  bp.topWidth = params.ballastTopWidth;
  bp.thickness = params.ballastThickness;
  bp.sideSlope = params.ballastSlope;
  bp.tiltAngle = 0;
  centerline_segment bseg;
  bseg.type = centerline_curve_type::LINE;
  bseg.points = {params.startPoint, params.endPoint};
  bp.centerlineSegments.push_back(bseg);
  try { bld.Add(cmp, create_ballast(bp)); } catch (...) { warn_part_failed("create_straight_track", "ballast"); }
  
  return cmp;
}

TopoDS_Shape create_straight_track(const straight_track_params &params,
                                    const gp_Pnt &position,
                                    const gp_Dir &direction,
                                    const gp_Dir &upDir) {
  TopoDS_Shape shape = create_straight_track(params);
  gp_Dir yDir = upDir.Crossed(direction);
  gp_Ax3 src(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 tgt(position, upDir, direction);
  gp_Trsf tr; tr.SetTransformation(tgt, src);
  return BRepBuilderAPI_Transform(shape, tr).Shape();
}

// =========================================================================
// TRACK: 38. Curve Track (曲线轨道段) — element assembly
// =========================================================================
TopoDS_Shape create_curve_track(const curve_track_params &params) {
  BRep_Builder bld; TopoDS_Compound cmp; bld.MakeCompound(cmp);
  double hg = params.gauge / 2;
  double startA = params.startAngle;
  double sweep = params.sweepAngle;
  double R = params.curveRadius;
  
  // Rails (ARC curves)
  rail_curve_params rp;
  rp.curve.type = rail_curve_type::ARC;
  rp.railHeight = params.railHeight; rp.headWidth = params.railHeadWidth;
  rp.baseWidth = params.railBaseWidth; rp.webThickness = params.webThickness;
  
  for (int side = -1; side <= 1; side += 2) {
    double railR = side < 0 ? R - hg : R + hg;
    gp_Pnt center = params.curveCenter;
    gp_Pnt p1(center.X() + railR * cos(startA), center.Y() + railR * sin(startA), 0);
    gp_Pnt p2(center.X() + railR * cos(startA + sweep), center.Y() + railR * sin(startA + sweep), 0);
    gp_Pnt pmid(center.X() + railR * cos(startA + sweep / 2), center.Y() + railR * sin(startA + sweep / 2), 0);
    rp.curve.startPoint = p1;
    rp.curve.endPoint = p2;
    rp.curve.controlPoints = {pmid};
    try { bld.Add(cmp, create_rail_curve(rp)); } catch (...) { warn_part_failed("create_curve_track", "rail"); }
  }
  
  // Sleepers (radially arranged)
  double arcLen = fabs(sweep) * R;
  if (!(params.sleeperSpacing > Precision::Confusion()))
    throw Standard_ConstructionError("sleeperSpacing must be positive");
  // 上限防护: 极小间距会把轨枕循环放大到数亿次
  int sc = std::max(2, (int)(arcLen / params.sleeperSpacing));
  if (sc > 100000)
    throw Standard_ConstructionError("sleeperSpacing too small for track length");
  for (int i = 0; i < sc; ++i) {
    double a = startA + sweep * (double)i / (sc - 1);
    double cx = params.curveCenter.X(), cy = params.curveCenter.Y();
    gp_Pnt pos(cx + R * cos(a), cy + R * sin(a), 0);
    gp_Dir radial(cos(a), sin(a), 0);
    sleeper_line_params slp;
    gp_Vec rv(radial.XYZ());
    slp.startPoint = pos.Translated(-rv * params.sleeperLength / 2);
    slp.endPoint = pos.Translated(rv * params.sleeperLength / 2);
    slp.width = params.sleeperWidth; slp.height = params.sleeperHeight;
    slp.gauge = params.gauge;
    try { bld.Add(cmp, create_sleeper_line(slp)); } catch (...) { warn_part_failed("create_curve_track", "sleeper"); }
  }

  // Ballast (沿曲线中心线放样, 超高 → 断面绕切向倾转, 符号取扫掠方向使外侧抬起)
  ballast_params bp;
  bp.topWidth = params.ballastTopWidth;
  bp.thickness = params.ballastThickness;
  bp.sideSlope = params.ballastSlope;
  double cx = params.curveCenter.X(), cy = params.curveCenter.Y();
  centerline_segment bseg;
  bseg.type = centerline_curve_type::ARC;
  bseg.points = {gp_Pnt(cx + R * cos(startA), cy + R * sin(startA), 0),
                 gp_Pnt(cx + R * cos(startA + sweep / 2), cy + R * sin(startA + sweep / 2), 0),
                 gp_Pnt(cx + R * cos(startA + sweep), cy + R * sin(startA + sweep), 0)};
  bp.centerlineSegments.push_back(bseg);
  bp.tiltAngle = (params.gauge > 0 && std::abs(params.superElevation) > Precision::Confusion())
                     ? -std::copysign(std::atan(std::abs(params.superElevation) / params.gauge), sweep)
                     : 0.0;
  try { bld.Add(cmp, create_ballast(bp)); } catch (...) { warn_part_failed("create_curve_track", "ballast"); }

  return cmp;
}

TopoDS_Shape create_curve_track(const curve_track_params &params,
                                 const gp_Pnt &position,
                                 const gp_Dir &direction,
                                 const gp_Dir &upDir) {
  TopoDS_Shape shape = create_curve_track(params);
  gp_Dir yDir = upDir.Crossed(direction);
  gp_Ax3 src(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 tgt(position, upDir, direction);
  gp_Trsf tr; tr.SetTransformation(tgt, src);
  return BRepBuilderAPI_Transform(shape, tr).Shape();
}

// =========================================================================
// POINT/LINE-DRIVEN TRACK — internal helpers
// =========================================================================


// =========================================================================
// TRACK: 31. Switch Rail (尖轨) — tapered from tip to heel
// =========================================================================
TopoDS_Shape create_switch_rail(const switch_rail_params &params) {
  if (params.length <= 0 || params.railHeight <= 0)
    throw Standard_ConstructionError("Invalid switch rail dimensions");

  const double H = params.railHeight;
  const double hW = params.railHeadWidth / 2.0;
  const double tipScale = std::max(params.tipWidth, 2.0) / params.railHeadWidth;
  // 非刨削侧 (贴基本轨侧) 边缘为锚点, 宽度向刨削侧收缩
  const double anchor = params.isLeftHand ? -hW : hW;

  // 断面序列: 尖端 (窄+降低) → 跟端 (全剖面)
  auto sectionAt = [&](double t) {
    double wsc = tipScale + (1.0 - tipScale) * t;
    double hsc = 0.9 + 0.1 * t;
    return buildRailSectionWire(H * hsc, params.railHeadWidth,
                                params.railBaseWidth, params.webThickness,
                                0, 0, 13.0, wsc, anchor);
  };

  const int nSec = 12;
  BRepOffsetAPI_ThruSections loft(Standard_True, Standard_True);
  const bool curved = params.curveRadius > Precision::Confusion();
  const double R = curved ? params.curveRadius : 1.0;
  const double sgn = params.isLeftHand ? 1.0 : -1.0;
  for (int i = 0; i <= nSec; ++i) {
    double t = (double)i / nSec;
    double s = t * params.length;
    gp_Pnt p;
    gp_Dir tan;
    if (curved) {
      double th = s / R;
      p = gp_Pnt(R * std::sin(th), sgn * R * (1 - std::cos(th)), 0);
      tan = gp_Dir(std::cos(th), sgn * std::sin(th), 0);
    } else {
      p = gp_Pnt(s, 0, 0);
      tan = gp::DX();
    }
    // 断面坐标架: 局部 X=横向 → lat, 局部 Y=竖向 → up, 法向 → tan
    gp_Dir lat = gp::DZ().Crossed(tan);
    gp_Ax3 src(gp::Origin(), gp::DZ(), gp::DX());
    gp_Ax3 tgt(p, tan, lat);
    gp_Trsf tr;
    tr.SetTransformation(tgt, src);
    loft.AddWire(TopoDS::Wire(
        BRepBuilderAPI_Transform(sectionAt(t), tr).Shape()));
  }
  loft.Build();
  if (!loft.IsDone())
    throw Standard_ConstructionError("Switch rail loft failed");
  return loft.Shape();
}

TopoDS_Shape create_switch_rail(const switch_rail_params &params,
                                const gp_Pnt &position, const gp_Dir &direction,
                                const gp_Dir &upDir) {
  TopoDS_Shape s = create_switch_rail(params);
  gp_Ax3 src(gp::Origin(), gp::DZ(), gp::DX()), tgt(position, upDir, direction);
  gp_Trsf tr;
  tr.SetTransformation(tgt, src);
  return BRepBuilderAPI_Transform(s, tr).Shape();
}
// =========================================================================
// Registration Arm Bracket (定位器底座)
// =========================================================================
TopoDS_Shape create_reg_arm_bracket(const reg_arm_bracket_params &params) {
  if (params.tubeDiameter <= 0 || params.bracketHeight <= 0)
    throw Standard_ConstructionError("Invalid bracket dimensions");
  double R = params.tubeDiameter / 2.0;
  double bWidth = params.bandWidth > 0 ? params.bandWidth : R * 0.8;
  double bThick = params.bandThickness > 0 ? params.bandThickness : R * 0.12;
  double bkW = params.bracketWidth > 0 ? params.bracketWidth : bThick * 3;
  double bkH = params.bracketHeight;
  double br = params.mountHoleDiameter / 2.0;
  double bw2 = bWidth / 2;
  double gapW = bThick * 0.8;

  BRep_Builder b; TopoDS_Compound c; b.MakeCompound(c);

  // 抱箍环带 (绕腕臂管, 管轴 = X), 底部开槽
  TopoDS_Shape band = BRepAlgoAPI_Cut(
    BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(-bw2, 0, 0), gp::DX()), R + bThick, bWidth).Shape(),
    BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(-bw2 - 1, 0, 0), gp::DX()), R, bWidth + 2).Shape()).Shape();
  band = BRepAlgoAPI_Cut(
    band, BRepPrimAPI_MakeBox(gp_Pnt(-bw2 - 1, -gapW / 2, -R - bThick - 1),
                              bWidth + 2, gapW, bThick + 2).Shape()).Shape();
  b.Add(c, band);

  // 开口两侧螺栓耳 (带紧固孔)
  for (int side = -1; side <= 1; side += 2) {
    double ey = side * (gapW / 2 + bThick / 2);
    TopoDS_Shape ear = BRepPrimAPI_MakeBox(
        gp_Pnt(-bw2, ey - bThick / 2, -R - bThick * 2.5), bWidth, bThick,
        bThick * 1.8).Shape();
    if (br > 0) {
      ear = BRepAlgoAPI_Cut(
          ear, BRepPrimAPI_MakeCylinder(
                   gp_Ax2(gp_Pnt(-bw2 - 1, ey, -R - bThick * 1.6), gp::DX()),
                   br, bWidth + 2).Shape()).Shape();
    }
    b.Add(c, ear);
  }

  // L 型弯板 (定位器座), 底部带销轴孔
  TopoDS_Shape plate = BRepPrimAPI_MakeBox(
      gp_Pnt(-bThick / 2, -bkW / 2, -R - bkH), bThick, bkW, bkH).Shape();
  if (br > 0) {
    plate = BRepAlgoAPI_Cut(
        plate, BRepPrimAPI_MakeCylinder(
                   gp_Ax2(gp_Pnt(-bThick / 2 - 1, 0, -R - bkH * 0.85), gp::DX()),
                   br, bThick + 2).Shape()).Shape();
  }
  b.Add(c, plate);
  return c;
}

TopoDS_Shape create_reg_arm_bracket(const reg_arm_bracket_params &params,
                                    const gp_Pnt &position,
                                    const gp_Dir &tubeDir,
                                    const gp_Dir &upDir) {
  TopoDS_Shape s = create_reg_arm_bracket(params);
  gp_Ax3 src(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 tgt(position, upDir, tubeDir);
  gp_Trsf tr; tr.SetTransformation(tgt, src);
  return BRepBuilderAPI_Transform(s, tr).Shape();
}

namespace {

TopoDS_Edge makeEdgeSafe(const gp_Pnt &a, const gp_Pnt &b) {
  if (a.Distance(b) < Precision::Confusion())
    return BRepBuilderAPI_MakeEdge(a, b.Translated(gp_Vec(0.001, 0, 0))).Edge();
  return BRepBuilderAPI_MakeEdge(a, b).Edge();
}

Handle(Geom_BezierCurve) makeBezier(const std::vector<gp_Pnt> &pts) {
  int n = std::max((int)pts.size(), 2);
  TColgp_Array1OfPnt arr(1, n);
  for (int i = 0; i < n && i < (int)pts.size(); ++i)
    arr.SetValue(i + 1, pts[i]);
  for (int i = (int)pts.size(); i < n; ++i)
    arr.SetValue(i + 1, pts.back());
  return new Geom_BezierCurve(arr);
}

TopoDS_Wire buildCurveWire(const curve_params &curve) {
  BRepBuilderAPI_MakeWire w;
  switch (curve.type) {
  case rail_curve_type::LINE:
    w.Add(makeEdgeSafe(curve.startPoint, curve.endPoint));
    break;
  case rail_curve_type::ARC: {
    Handle(Geom_TrimmedCurve) arc;
    if (curve.controlPoints.size() >= 1)
      arc = GC_MakeArcOfCircle(curve.startPoint, curve.controlPoints[0], curve.endPoint).Value();
    else if (curve.radius > Precision::Confusion()) {
      gp_Pnt mid((curve.startPoint.X() + curve.endPoint.X()) / 2.0,
                  (curve.startPoint.Y() + curve.endPoint.Y()) / 2.0,
                  (curve.startPoint.Z() + curve.endPoint.Z()) / 2.0);
      gp_Dir dir(0, 0, curve.arcDirection == 1 ? 1 : -1);
      double d2 = curve.startPoint.Distance(curve.endPoint) / 2.0;
      double h = sqrt(std::max(0.0, curve.radius * curve.radius - d2 * d2));
      gp_Pnt center = mid.XYZ() + dir.XYZ() * h;
      arc = GC_MakeArcOfCircle(curve.startPoint, center, curve.endPoint).Value();
    }
    w.Add(BRepBuilderAPI_MakeEdge(arc).Edge());
    break;
  }
  case rail_curve_type::BEZIER: {
    std::vector<gp_Pnt> cpts = curve.controlPoints;
    if (cpts.empty() || cpts.front().Distance(curve.startPoint) > Precision::Confusion())
      cpts.insert(cpts.begin(), curve.startPoint);
    if (cpts.back().Distance(curve.endPoint) > Precision::Confusion())
      cpts.push_back(curve.endPoint);
    w.Add(BRepBuilderAPI_MakeEdge(makeBezier(cpts)).Edge());
    break;
  }
  }
  return w.Wire();
}

// 槽形截面 (U 形轮缘槽, 开口朝上): 槽底 + 两侧立壁 + 外翼缘, 内槽角圆角
TopoDS_Face buildChannelProfile(double height, double flangeWidth,
                                double webThickness, double grooveWidth = 45.0,
                                double grooveThickness = 15.0) {
  double gw2 = grooveWidth / 2.0;
  double wT = webThickness;
  double bT = grooveThickness;
  double ow = gw2 + wT + flangeWidth; // 外缘半宽
  double lipH = bT * 1.6;             // 外翼缘高度
  double fr = std::min(6.0, gw2 * 0.15); // 内槽角圆角
  BRepBuilderAPI_MakeWire w;
  auto P = [](double y, double z) { return gp_Pnt(0, y, z); };
  auto line = [&](double y0, double z0, double y1, double z1) {
    w.Add(BRepBuilderAPI_MakeEdge(P(y0, z0), P(y1, z1)));
  };
  auto fillet = [&](double cx, double cz, double a0deg) {
    // 以 (cx,cz) 为圆心 fr 半径, 从 a0 到 a0-90° 的四分之一圆弧
    double a0 = a0deg * M_PI / 180.0, a1 = a0 - M_PI / 2, am = a0 - M_PI / 4;
    w.Add(BRepBuilderAPI_MakeEdge(
        GC_MakeArcOfCircle(P(cx + fr * std::cos(a0), cz + fr * std::sin(a0)),
                           P(cx + fr * std::cos(am), cz + fr * std::sin(am)),
                           P(cx + fr * std::cos(a1), cz + fr * std::sin(a1)))
            .Value()));
  };
  // 底面 → 右外翼缘 → 右立壁 → 内槽角圆角 → 槽底 → 左内槽角 → 左立壁 → 左外翼缘
  line(-ow, 0, ow, 0);
  line(ow, 0, ow, lipH);
  line(ow, lipH, gw2 + wT, lipH);
  line(gw2 + wT, lipH, gw2 + wT, height);
  line(gw2 + wT, height, gw2, height);
  line(gw2, height, gw2, bT + fr);
  fillet(gw2 - fr, bT + fr, 0);       // 右内槽角
  line(gw2 - fr, bT, -(gw2 - fr), bT);
  fillet(-(gw2 - fr), bT + fr, 270);  // 左内槽角
  line(-gw2, bT + fr, -gw2, height);
  line(-gw2, height, -(gw2 + wT), height);
  line(-(gw2 + wT), height, -(gw2 + wT), lipH);
  line(-(gw2 + wT), lipH, -ow, lipH);
  line(-ow, lipH, -ow, 0);
  ShapeFix_Wire fx; fx.Load(w.Wire()); fx.Perform();
  return BRepLib_MakeFace(fx.Wire()).Face();
}

TopoDS_Face buildPlateProfile(double height, double width) {
  double hw = width / 2.0;
  BRepBuilderAPI_MakeWire w;
  w.Add(makeEdgeSafe(gp_Pnt(0, -hw, 0), gp_Pnt(0, -hw, height)));
  w.Add(makeEdgeSafe(gp_Pnt(0, -hw, height), gp_Pnt(0, hw, height)));
  w.Add(makeEdgeSafe(gp_Pnt(0, hw, height), gp_Pnt(0, hw, 0)));
  w.Add(makeEdgeSafe(gp_Pnt(0, hw, 0), gp_Pnt(0, -hw, 0)));
  return BRepLib_MakeFace(w.Wire()).Face();
}

TopoDS_Shape sweepProfile(const TopoDS_Face &face, const curve_params &curve) {
  if (curve.type == rail_curve_type::LINE) {
    gp_Vec dir(curve.startPoint, curve.endPoint);
    if (dir.Magnitude() < Precision::Confusion())
      throw Standard_ConstructionError("zero-length path");
    gp_Trsf tr; tr.SetTranslation(gp_Vec(curve.startPoint.XYZ()));
    return BRepPrimAPI_MakePrism(BRepBuilderAPI_Transform(face, tr).Shape(), dir).Shape();
  }

  Handle(Geom_Curve) c;
  if (curve.type == rail_curve_type::BEZIER) {
    std::vector<gp_Pnt> pts = curve.controlPoints;
    pts.insert(pts.begin(), curve.startPoint);
    pts.push_back(curve.endPoint);
    TColgp_Array1OfPnt arr(1, (int)pts.size());
    for (size_t i = 0; i < pts.size(); i++) arr.SetValue((int)(i + 1), pts[i]);
    c = new Geom_BezierCurve(arr);
  } else if (curve.type == rail_curve_type::ARC) {
    if (curve.controlPoints.size() >= 1)
      c = GC_MakeArcOfCircle(curve.startPoint, curve.controlPoints[0], curve.endPoint).Value();
    else if (curve.radius > Precision::Confusion()) {
      gp_Pnt mid((curve.startPoint.X() + curve.endPoint.X()) / 2,
                 (curve.startPoint.Y() + curve.endPoint.Y()) / 2, 0);
      gp_Dir dir(0, 0, curve.arcDirection == 1 ? 1 : -1);
      double d2 = curve.startPoint.Distance(curve.endPoint) / 2;
      double h = sqrt(std::max(0.0, curve.radius * curve.radius - d2 * d2));
      gp_Pnt center = mid.XYZ() + dir.XYZ() * h;
      c = GC_MakeArcOfCircle(curve.startPoint, center, curve.endPoint).Value();
    }
  }
  if (c.IsNull()) throw Standard_ConstructionError("failed to create curve");

  // 沿曲线用 MakePipeShell 一次扫掠成形。
  // 旧实现按 ~30mm 逐段 prism 再两两 Fuse: O(n) 次布尔并, 25m 护轨 ≈ 833 段,
  // 长中心线下耗时/内存无界增长直至假死。
  TopoDS_Wire spine = BRepBuilderAPI_MakeWire(BRepBuilderAPI_MakeEdge(c).Edge()).Wire();
  BRepOffsetAPI_MakePipeShell maker(spine);
  // 副法线固定为 +Z, 截面随路径转动 (与旧实现的恒定 DZ 坐标架一致)
  maker.SetMode(gp_Dir(0, 0, 1)); // 副法线固定 +Z
  maker.SetTransitionMode(BRepBuilderAPI_Transformed);
  for (TopExp_Explorer exp(face, TopAbs_WIRE); exp.More(); exp.Next()) {
    maker.Add(TopoDS::Wire(exp.Current()), Standard_False);
  }
  maker.Build();
  if (!maker.IsDone()) {
    throw Standard_ConstructionError("sweep profile failed");
  }
  maker.MakeSolid();
  return maker.Shape();
}

// 从 curve_params 构建 Geom 曲线 (用于端部处理的几何计算)
Handle(Geom_Curve) pathCurveGeom(const curve_params &curve) {
  switch (curve.type) {
  case rail_curve_type::LINE:
    if (curve.startPoint.Distance(curve.endPoint) < Precision::Confusion())
      return nullptr;
    return GC_MakeSegment(curve.startPoint, curve.endPoint).Value();
  case rail_curve_type::ARC: {
    if (curve.controlPoints.size() >= 1)
      return GC_MakeArcOfCircle(curve.startPoint, curve.controlPoints[0],
                                curve.endPoint).Value();
    if (curve.radius > Precision::Confusion()) {
      gp_Pnt mid((curve.startPoint.X() + curve.endPoint.X()) / 2.0,
                 (curve.startPoint.Y() + curve.endPoint.Y()) / 2.0,
                 (curve.startPoint.Z() + curve.endPoint.Z()) / 2.0);
      gp_Dir dir(0, 0, curve.arcDirection == 1 ? 1 : -1);
      double d2 = curve.startPoint.Distance(curve.endPoint) / 2.0;
      double h = sqrt(std::max(0.0, curve.radius * curve.radius - d2 * d2));
      gp_Pnt center = mid.XYZ() + dir.XYZ() * h;
      return GC_MakeArcOfCircle(curve.startPoint, center, curve.endPoint).Value();
    }
    return nullptr;
  }
  case rail_curve_type::BEZIER: {
    std::vector<gp_Pnt> cpts = curve.controlPoints;
    if (cpts.empty() || cpts.front().Distance(curve.startPoint) > Precision::Confusion())
      cpts.insert(cpts.begin(), curve.startPoint);
    if (cpts.back().Distance(curve.endPoint) > Precision::Confusion())
      cpts.push_back(curve.endPoint);
    return makeBezier(cpts);
  }
  }
  return nullptr;
}

// 平面四边形 + 沿竖直方向拉伸成切割楔体
TopoDS_Shape makeWedge(const gp_Pnt &a, const gp_Pnt &b, const gp_Pnt &c,
                       const gp_Pnt &d, const gp_Vec &prismVec) {
  BRepBuilderAPI_MakePolygon poly;
  poly.Add(a);
  poly.Add(b);
  poly.Add(c);
  poly.Add(d);
  poly.Close();
  TopoDS_Face f = BRepBuilderAPI_MakeFace(poly.Wire(), true).Face();
  return BRepPrimAPI_MakePrism(f, prismVec).Shape();
}

TopoDS_Shape applyEndTreatment(const TopoDS_Shape &shape,
                                const end_treatment_params &t,
                                const curve_params &curve, bool isStart) {
  if (t.type == end_treatment_type::PLANE) return shape;

  // SCARF: 用斜切平面切掉端部
  if (t.type == end_treatment_type::SCARF) {
    gp_Pnt pt = isStart ? curve.startPoint : curve.endPoint;
    gp_Vec dir(curve.startPoint, curve.endPoint);
    if (dir.Magnitude() < Precision::Confusion()) return shape;
    gp_Dir outward(dir);
    if (isStart) outward.Reverse();
    double a = t.scarfAngle * M_PI / 180.0;
    gp_Dir n = outward.Rotated(gp_Ax1(pt, gp::DZ()), a);
    gp_Ax2 ax(pt, n);
    TopoDS_Shape box = BRepPrimAPI_MakeBox(ax, 4000, 4000, 4000).Shape();
    gp_Trsf mv;
    mv.SetTranslation(gp_Vec(ax.XDirection().XYZ() * -2000 +
                             ax.YDirection().XYZ() * -2000));
    box = BRepBuilderAPI_Transform(box, mv).Shape();
    TopoDS_Shape r = BRepAlgoAPI_Cut(shape, box).Shape();
    return r.IsNull() ? shape : r;
  }

  // SWITCH: 单侧刨削 — 刨切楔体从全剖面切到尖端, 可选尖端降低
  if (t.type == end_treatment_type::SWITCH) {
    Handle(Geom_Curve) c = pathCurveGeom(curve);
    if (c.IsNull()) return shape;
    GeomAdaptor_Curve gac(c);
    double L = GCPnts_AbscissaPoint::Length(gac);
    double swL = t.switchLength > 0 ? t.switchLength : std::min(1200.0, L * 0.3);
    if (swL >= L || swL < 50) return shape;
    double toe = std::max(t.toeWidth, 2.0);

    Bnd_Box bb;
    BRepBndLib::Add(shape, bb);
    double x0, y0, z0, x1, y1, z1;
    bb.Get(x0, y0, z0, x1, y1, z1);
    double H = z1 - z0;

    // 端点 E 与刨削起点 S
    double uE = isStart ? c->FirstParameter() : c->LastParameter();
    double sS = isStart ? swL : L - swL;
    double uS;
    try {
      GCPnts_AbscissaPoint ap(gac, sS, c->FirstParameter());
      uS = ap.Parameter();
    } catch (...) {
      warn_part_failed("applyEndTreatment", "SWITCH abscissa point");
      return shape;
    }
    gp_Pnt E, S;
    gp_Vec vE, vS;
    c->D1(uE, E, vE);
    c->D1(uS, S, vS);
    gp_Dir T(vE);                       // 指向端部的行进方向
    if (isStart) T.Reverse();
    gp_Vec Hv(T.XYZ().Crossed(gp::DZ().XYZ()));
    gp_Dir Hd = Hv.Magnitude() < Precision::Confusion() ? gp::DX() : gp_Dir(Hv);
    double side = (t.planedSide == 1) ? -1.0 : 1.0; // Hd 指向行进右侧
    gp_Dir Ps(Hd.XYZ() * side);         // 刨削侧方向

    // 刨削侧外缘: 包围盒角点在 Ps 方向的最大投影
    double hW = 40.0;
    for (int i = 0; i < 8; ++i) {
      gp_Pnt cor(i & 1 ? x1 : x0, i & 2 ? y1 : y0, i & 4 ? z1 : z0);
      hW = std::max(hW, gp_Vec(S, cor).Dot(gp_Vec(Ps.XYZ())));
    }

    // 刨切楔体: 从 S 处外缘斜切到 E 处半尖宽, 竖直覆盖轨头区域
    gp_Pnt A = S.Translated(gp_Vec(Ps.XYZ()) * hW);
    gp_Pnt B = E.Translated(gp_Vec(Ps.XYZ()) * (toe / 2));
    gp_Pnt C = E.Translated(gp_Vec(Ps.XYZ()) * (hW * 4));
    gp_Pnt D = S.Translated(gp_Vec(Ps.XYZ()) * (hW * 4));
    double zBase = z0 + H * 0.2;
    double zMin = std::min(S.Z(), E.Z());
    gp_Vec down(0, 0, zBase - zMin);
    TopoDS_Shape wedge = makeWedge(A.Translated(down), B.Translated(down),
                                   C.Translated(down), D.Translated(down),
                                   gp_Vec(0, 0, (z1 + 500) - zBase));
    TopoDS_Shape r = BRepAlgoAPI_Cut(shape, wedge).Shape();
    if (r.IsNull()) return shape;

    // 尖端降低: 顶部斜切楔体
    if (t.dropValue > Precision::Confusion()) {
      gp_Pnt A2(S.X(), S.Y(), S.Z() + H + 1);
      gp_Pnt B2(E.X(), E.Y(), E.Z() + H + 1 - t.dropValue);
      gp_Pnt C2(E.X(), E.Y(), E.Z() + H + 500);
      gp_Pnt D2(S.X(), S.Y(), S.Z() + H + 500);
      gp_Vec aside(Ps.XYZ() * -(hW * 4));
      TopoDS_Shape drop = makeWedge(A2.Translated(aside), B2.Translated(aside),
                                    C2.Translated(aside), D2.Translated(aside),
                                    gp_Vec(Ps.XYZ()) * (hW * 8));
      TopoDS_Shape r2 = BRepAlgoAPI_Cut(r, drop).Shape();
      if (!r2.IsNull()) r = r2;
    }
    return r;
  }

  return shape;
}

// BELL 喇叭口: 从正常槽型截面放样张开到外扩截面
TopoDS_Shape addBellMouth(const TopoDS_Shape &shape, const curve_params &curve,
                          bool isStart, double height, double flangeWidth,
                          double webThickness, double bellLength,
                          double grooveWidth = 45.0,
                          double grooveThickness = 15.0) {
  if (bellLength < 1) return shape;
  gp_Pnt E = isStart ? curve.startPoint : curve.endPoint;
  gp_Vec d(curve.startPoint, curve.endPoint);
  if (d.Magnitude() < Precision::Confusion() || d.Magnitude() <= bellLength)
    return shape;
  gp_Dir Tin(d);                 // 指向实体内部的行进方向
  if (isStart) Tin.Reverse();
  gp_Dir outward(Tin);
  outward.Reverse();
  gp_Pnt S = E.Translated(gp_Vec(outward.XYZ()) * bellLength);

  TopoDS_Face fNorm =
      buildChannelProfile(height, flangeWidth, webThickness, grooveWidth,
                          grooveThickness);
  TopoDS_Face fBell =
      buildChannelProfile(height, flangeWidth * 2.0, webThickness,
                          grooveWidth * 1.6, grooveThickness);
  gp_Ax3 src(gp::Origin(), gp::DZ(), gp::DX());
  auto secWire = [&](const TopoDS_Face &f, const gp_Pnt &p) {
    gp_Ax3 tgt(p, gp::DZ(), Tin);
    gp_Trsf tr;
    tr.SetTransformation(tgt, src);
    TopoDS_Shape s = BRepBuilderAPI_Transform(f, tr).Shape();
    return BRepTools::OuterWire(TopoDS::Face(s));
  };
  BRepOffsetAPI_ThruSections loft(Standard_True, Standard_True);
  loft.AddWire(secWire(fNorm, S));
  loft.AddWire(secWire(fNorm, S.Translated(gp_Vec(Tin.XYZ()) * (bellLength * 0.6))));
  loft.AddWire(secWire(fBell, E));
  loft.Build();
  if (!loft.IsDone()) return shape;
  TopoDS_Shape r = BRepAlgoAPI_Fuse(shape, loft.Shape()).Shape();
  return r.IsNull() ? shape : r;
}

} // anonymous namespace

// =========================================================================
// 钢轨（独立曲线）
// =========================================================================
TopoDS_Shape create_rail_curve(const rail_curve_params &params) {
  rail_params rp;
  rp.railHeight = params.railHeight;
  rp.headWidth = params.headWidth;
  rp.baseWidth = params.baseWidth;
  rp.webThickness = params.webThickness;
  rp.headHeight = params.headHeight;
  rp.baseHeight = params.baseHeight;
  rp.headRadius = params.headRadius;
  centerline_curve_type ct = params.curve.type == rail_curve_type::LINE ? centerline_curve_type::LINE
    : params.curve.type == rail_curve_type::ARC ? centerline_curve_type::ARC : centerline_curve_type::BEZIER;
  std::vector<gp_Pnt> pts = {params.curve.startPoint, params.curve.endPoint};
  if (params.curve.type == rail_curve_type::ARC && params.curve.controlPoints.size() >= 1)
    pts.insert(pts.begin() + 1, params.curve.controlPoints[0]);
  centerline_segment seg{ct, pts};
  TopoDS_Shape shape = create_rail_path(rp, {seg}, 0, 0, 0);
  shape = applyEndTreatment(shape, params.endStart, params.curve, true);
  shape = applyEndTreatment(shape, params.endFinish, params.curve, false);
  return shape;
}

// =========================================================================
// 翼轨（独立曲线）
// =========================================================================
TopoDS_Shape create_wing_rail_curve(const wing_rail_curve_params &params) {
  // RAIL 分支: 真实钢轨断面 (翼轨由普通钢轨弯折而成)
  if (params.profile == rail_profile_type::RAIL) {
    rail_params std60 = standard_rail_params(60);
    rail_curve_params rc;
    rc.curve = params.curve;
    rc.endStart = params.endStart;
    rc.endFinish = params.endFinish;
    rc.railHeight = std60.railHeight;
    rc.headWidth = std60.headWidth;
    rc.baseWidth = std60.baseWidth;
    rc.webThickness = std60.webThickness;
    rc.headHeight = std60.headHeight;
    rc.baseHeight = std60.baseHeight;
    rc.headRadius = std60.headRadius;
    return create_rail_curve(rc);
  }
  TopoDS_Face face = buildChannelProfile(params.channelHeight, params.flangeWidth,
                                         params.webThickness, params.grooveWidth,
                                         params.grooveThickness);
  TopoDS_Shape shape = sweepProfile(face, params.curve);
  if (params.endStart.type == end_treatment_type::BELL)
    shape = addBellMouth(shape, params.curve, true, params.channelHeight,
                         params.flangeWidth, params.webThickness, params.endStart.bellLength,
                         params.grooveWidth, params.grooveThickness);
  else
    shape = applyEndTreatment(shape, params.endStart, params.curve, true);
  if (params.endFinish.type == end_treatment_type::BELL)
    shape = addBellMouth(shape, params.curve, false, params.channelHeight,
                         params.flangeWidth, params.webThickness, params.endFinish.bellLength,
                         params.grooveWidth, params.grooveThickness);
  else
    shape = applyEndTreatment(shape, params.endFinish, params.curve, false);
  return shape;
}

// =========================================================================
// 护轨（独立曲线）
// =========================================================================
TopoDS_Shape create_guard_rail_curve(const guard_rail_curve_params &params) {
  TopoDS_Shape shape;
  if (params.profile == rail_profile_type::RAIL) {
    // 钢轨改造护轨: 43kg 旧钢轨真实断面
    rail_params std43 = standard_rail_params(43);
    rail_curve_params rc;
    rc.curve = params.curve;
    rc.endStart = params.endStart;
    rc.endFinish = params.endFinish;
    rc.railHeight = std43.railHeight;
    rc.headWidth = std43.headWidth;
    rc.baseWidth = std43.baseWidth;
    rc.webThickness = std43.webThickness;
    rc.headHeight = std43.headHeight;
    rc.baseHeight = std43.baseHeight;
    rc.headRadius = std43.headRadius;
    shape = create_rail_curve(rc);
  } else if (params.profile == rail_profile_type::PLATE) {
    shape = sweepProfile(
        buildPlateProfile(params.channelHeight, params.flangeWidth * 2),
        params.curve);
  } else {
    TopoDS_Face face = buildChannelProfile(
        params.channelHeight, params.flangeWidth, params.webThickness,
        params.grooveWidth, params.grooveThickness);
    shape = sweepProfile(face, params.curve);
  }
  if (params.endStart.type == end_treatment_type::BELL &&
      params.profile != rail_profile_type::RAIL)
    shape = addBellMouth(shape, params.curve, true, params.channelHeight,
                         params.flangeWidth, params.webThickness, params.endStart.bellLength,
                         params.grooveWidth, params.grooveThickness);
  else if (params.profile != rail_profile_type::RAIL)
    shape = applyEndTreatment(shape, params.endStart, params.curve, true);
  if (params.endFinish.type == end_treatment_type::BELL &&
      params.profile != rail_profile_type::RAIL)
    shape = addBellMouth(shape, params.curve, false, params.channelHeight,
                         params.flangeWidth, params.webThickness, params.endFinish.bellLength,
                         params.grooveWidth, params.grooveThickness);
  else if (params.profile != rail_profile_type::RAIL)
    shape = applyEndTreatment(shape, params.endFinish, params.curve, false);
  if (params.raiseHeight > Precision::Confusion()) {
    gp_Trsf tr; tr.SetTranslation(gp_Vec(0, 0, params.raiseHeight));
    shape = BRepBuilderAPI_Transform(shape, tr).Shape();
  }
  return shape;
}

// =========================================================================
// 枕木（直线）
// =========================================================================
TopoDS_Shape create_sleeper_line(const sleeper_line_params &params) {
  gp_Vec dir(params.startPoint, params.endPoint);
  double length = dir.Magnitude();
  if (length < Precision::Confusion())
    throw Standard_ConstructionError("sleeper: zero length");

  TopoDS_Shape body;

  if (params.shapeType == 2) {
    // TRAPEZOIDAL: fish-belly concrete sleeper with ThruSections
    double L = length, W = params.width, H = params.height;
    double topW = W * 0.75, midW = W * 0.85;
    BRepOffsetAPI_ThruSections gen(Standard_True);
    for (int s = 0; s < 3; ++s) {
      double t = s / 2.0;
      double curW = (s == 1) ? midW : W;
      double curTopW = (s == 1) ? topW * 0.85 : topW;
      double hw = curW / 2, htw = curTopW / 2;
      double z1 = H * 0.08, z2 = H * 0.25, z3 = H * 0.7, z4 = H * 0.95;
      double y1 = hw, y2 = hw - (hw - htw) * 0.15, y3 = htw + (hw - htw) * 0.2, y4 = htw + (hw - htw) * 0.05;
      gp_Pnt sp[12] = {
        {0, -hw, 0}, {0, -hw, z1}, {0, -y2, z2}, {0, -y3, z3},
        {0, -htw, z4}, {0, -htw, H}, {0, htw, H}, {0, htw, z4},
        {0, y3, z3}, {0, y2, z2}, {0, hw, z1}, {0, hw, 0}
      };
      BRepBuilderAPI_MakeWire w;
      for (int p = 0; p < 12; ++p)
        w.Add(BRepBuilderAPI_MakeEdge(sp[p], sp[(p + 1) % 12]));
      gp_Trsf tr; tr.SetTranslation(gp_Vec(-L / 2 + t * L, 0, 0));
      TopoDS_Wire tw = TopoDS::Wire(BRepBuilderAPI_Transform(w.Wire(), tr).Shape());
      gen.AddWire(tw);
    }
    gen.Build();
    body = gen.Shape();
    // Fillet edges
    double fr = topW * 0.04;
    try {
      BRepFilletAPI_MakeFillet fm(body);
      for (TopExp_Explorer ex(body, TopAbs_EDGE); ex.More(); ex.Next())
        fm.Add(fr, TopoDS::Edge(ex.Current()));
      fm.Build();
      if (fm.IsDone()) body = fm.Shape();
    } catch (...) { warn_part_failed("create_sleeper_line", "fillet"); }
    // Rail seats (承轨槽: 比轨底宽, 沿枕木宽度方向贯通)
    double gD = params.grooveDepth;
    double gW = params.grooveWidth;
    double seatL = params.width * 1.2;  // 贯通枕木宽度并略有余量
    auto grooveYs = [&]() {
      if (!params.grooveYs.empty()) return params.grooveYs;
      return std::vector<double>{-params.gauge / 2.0, params.gauge / 2.0};
    };
    std::vector<double> groovy = grooveYs();
    auto cutGrooves = [&](const TopoDS_Shape &s, double L) {
      TopoDS_Shape r = s;
      for (double pos : groovy) {
        // pos = 沿枕木长度方向(X), 槽沿Y(宽度方向)贯通
        TopoDS_Shape seat = BRepPrimAPI_MakeBox(
            gp_Pnt(pos - gW/2, -seatL/2, params.height - gD), gW, seatL, gD + 1).Shape();
        r = BRepAlgoAPI_Cut(r, seat).Shape();
      }
      return r;
    };
    if (params.grooveDepth > Precision::Confusion())
      body = cutGrooves(body, length);
    // 局部几何沿 X 居中 (-L/2..L/2) → 平移到 [0,L] 后按 startPoint→endPoint 放置
    // (与 RECTANGULAR 分支一致)
    gp_Trsf shift; shift.SetTranslation(gp_Vec(L / 2, 0, 0));
    gp_Ax3 src(gp::Origin(), gp::DZ(), gp::DX());
    gp_Ax3 tgt(params.startPoint, gp::DZ(), gp_Dir(dir));
    gp_Trsf place; place.SetTransformation(tgt, src);
    place.Multiply(shift);
    body = BRepBuilderAPI_Transform(body, place).Shape();
  } else {
    // RECTANGULAR: simple box aligned to line direction
    gp_Dir ax(dir);
    gp_Ax3 src(gp::Origin(), gp::DZ(), gp::DX());
    gp_Ax3 tgt(params.startPoint, gp::DZ(), ax);
    gp_Trsf tr; tr.SetTransformation(tgt, src);
    body = BRepPrimAPI_MakeBox(gp_Pnt(0, -params.width / 2, 0), length, params.width, params.height).Shape();
    body = BRepBuilderAPI_Transform(body, tr).Shape();
    // Groove cuts (承轨槽: 比轨底宽, 沿枕木宽度方向贯通)
    if (params.grooveDepth > Precision::Confusion()) {
      auto groovy = params.grooveYs.empty()
          ? std::vector<double>{-params.gauge / 2.0, params.gauge / 2.0}
          : params.grooveYs;
      double seatL = params.width * 1.2;
      for (double pos : groovy) {
        TopoDS_Shape g = BRepPrimAPI_MakeBox(
            gp_Pnt(pos - params.grooveWidth / 2, -seatL / 2, params.height - params.grooveDepth),
            params.grooveWidth, seatL, params.grooveDepth + 1).Shape();
        body = BRepAlgoAPI_Cut(body, BRepBuilderAPI_Transform(g, tr).Shape()).Shape();
      }
    }
  }

  return body;
}

// =========================================================================
// 扣件（点）— 扣具安装在单根铁轨两侧
// =========================================================================
TopoDS_Shape create_fastener_point(const fastener_point_params &params) {
  BRep_Builder bld; TopoDS_Compound cmp; bld.MakeCompound(cmp);
  double halfW = params.railBaseWidth / 2.0 + 10.0;
  gp_Dir cross = params.railNormal;
  gp_Dir railDir = cross.Crossed(gp::DZ());
  gp_Ax3 originAx3(gp::Origin(), gp::DZ(), gp::DX());
  const double footTop = params.railBaseWidth * 0.2; // 轨翼顶面 ≈ 轨底高

  // 1. 铁垫板 (垫于轨下垫板之下) + 带肋橡胶垫板 (钢轨正下方)
  {
    gp_Ax3 padAx3(params.position, gp::DZ(), railDir);
    gp_Trsf padTrsf;
    padTrsf.SetTransformation(padAx3, originAx3);
    double plL = 170.0;                        // 垫板长 (沿轨向)
    double plW = params.railBaseWidth + 140.0; // 垫板宽 (横向)
    TopoDS_Shape plate = BRepPrimAPI_MakeBox(
        gp_Pnt(-plL / 2, -plW / 2, -params.padThickness), plL, plW,
        std::max(params.padThickness - 10, 4.0)).Shape();
    for (int s = -1; s <= 1; s += 2) {
      plate = BRepAlgoAPI_Cut(plate, BRepPrimAPI_MakeCylinder(
          gp_Ax2(gp_Pnt(0, s * (plW / 2 - 20), -params.padThickness - 1),
                 gp::DZ()),
          11.0, params.padThickness + 2).Shape()).Shape();
    }
    bld.Add(cmp, BRepBuilderAPI_Transform(plate, padTrsf).Shape());
    // 橡胶垫板: 钢轨正下方, 顶面带横向沟槽 (参考实物带肋垫板)
    double rbW = params.railBaseWidth + 30.0;
    TopoDS_Shape rubber = BRepPrimAPI_MakeBox(
        gp_Pnt(-plL / 2, -rbW / 2, -10), plL, rbW, 10).Shape();
    for (int k = -2; k <= 2; ++k) {
      rubber = BRepAlgoAPI_Cut(rubber, BRepPrimAPI_MakeBox(
          gp_Pnt(-plL / 2 - 1, k * rbW / 6 - 2, -4), plL + 2, 4, 4).Shape()).Shape();
    }
    bld.Add(cmp, BRepBuilderAPI_Transform(rubber, padTrsf).Shape());
  }

  auto addPad = [&](double sign) {
    gp_Pnt p = params.position.Translated(gp_Vec(cross.XYZ()) * (sign * halfW));
    gp_Ax3 padAx3(p, gp::DZ(), railDir);
    gp_Trsf padTrsf;
    padTrsf.SetTransformation(padAx3, originAx3);
    auto addLocal = [&](const TopoDS_Shape &s) {
      bld.Add(cmp, BRepBuilderAPI_Transform(s, padTrsf).Shape());
    };
    const double m = sign; // sign=-1 侧镜像 Y (钢轨始终在局部 -Y)

    // 2. 铸铁挡板座 (外侧) + 尼龙轨距挡板 (贴轨翼)
    {
      const double sbL = 120, sbT = 14;
      // 挡板座铸件: 底板 + 两侧立墙 + 中心钉孔
      TopoDS_Shape seat = BRepPrimAPI_MakeBox(
          gp_Pnt(-sbL / 2, m > 0 ? 8 : -58, 0), sbL, 50, sbT).Shape();
      seat = BRepAlgoAPI_Cut(seat, BRepPrimAPI_MakeCylinder(
          gp_Ax2(gp_Pnt(0, m * 42, -1), gp::DZ()), 11.0, sbT + 2).Shape()).Shape();
      addLocal(seat);
      for (int s2 = -1; s2 <= 1; s2 += 2) {
        addLocal(BRepPrimAPI_MakeBox(
            gp_Pnt(s2 * sbL / 2 - (s2 > 0 ? 14 : 0), m > 0 ? 8 : -58, sbT),
            14, 50, 22).Shape());
      }
      // 尼龙轨距挡板 (白色块, 挡肩与轨翼之间)
      addLocal(BRepPrimAPI_MakeBox(
          gp_Pnt(-30, m > 0 ? -10 : -6, 0), 60, 16, 26).Shape());
    }

    // 3. ω 形弹条: 圆钢在水平面内弯曲 (俯视图 ω 形)
    //    跟端钩 → 外谷 → 后冠(道钉垫圈下) → 长前臂 → 趾端U弯(压轨翼) → 对称
    {
      const double wireR = 6.5;
      const int nP = 17;
      const gp_Pnt pts[nP] = {
          {-48, m * 50, 20},          // 跟端钩1 端头
          {-46, m * 38, 24},          // 跟端钩下弯
          {-40, m * 26, 26},          // 外谷1
          {-28, m * 34, 40},          // 起弧
          {-18, m * 46, 46},          // 后冠1 (垫圈压点)
          {-9,  m * 38, 44},          //
          {-14, m * 10, 38},          // 趾端圆弧 (R≈17 钝U)
          {-12, m * -6, 35},          //
          {0,   m * -14, footTop + 3},// 趾端底部 (压轨翼顶面)
          {12,  m * -6, 35},          //
          {14,  m * 10, 38},          //
          {9,   m * 38, 44},          //
          {18,  m * 46, 46},          // 后冠2 (垫圈压点)
          {28,  m * 34, 40},          //
          {40,  m * 26, 26},          // 外谷2
          {46,  m * 38, 24},          // 跟端钩下弯
          {48,  m * 50, 20},          // 跟端钩2 端头
      };
      Handle(TColgp_HArray1OfPnt) arr = new TColgp_HArray1OfPnt(1, nP);
      for (int i = 0; i < nP; ++i) arr->SetValue(i + 1, pts[i]);
      GeomAPI_Interpolate interp(arr, Standard_False, 1e-5);
      interp.Perform();
      if (interp.IsDone()) {
        TopoDS_Wire pathW = BRepBuilderAPI_MakeWire(
            BRepBuilderAPI_MakeEdge(interp.Curve()).Edge()).Wire();
        gp_Dir tan(pts[1].XYZ() - pts[0].XYZ());
        gp_Ax2 secAx(pts[0], tan);
        TopoDS_Wire secW = BRepBuilderAPI_MakeWire(
            BRepBuilderAPI_MakeEdge(gp_Circ(secAx, wireR)).Edge()).Wire();
        BRepOffsetAPI_MakePipe pipe(pathW, BRepLib_MakeFace(secW).Face());
        pipe.Build();
        if (pipe.IsDone())
          addLocal(pipe.Shape());
      }
    }

    // 4. 螺旋道钉 + 平垫圈 (弹条III型为无螺栓式)
    if (params.type != 3) {
      const double bx = 0, by = m * 42;
      const double shR = 9.0, thR = 12.5, pitch = 6.0;
      const double zTop = 56;                   // 光杆顶
      const double zShank = 14;                 // 螺纹段顶
      const double zBot = -60;                  // 螺纹段底 (旋入轨枕套管)
      // 道钉主体: 锯齿剖面回转 (螺纹段粗牙 + 光杆)
      {
        BRepBuilderAPI_MakeWire prof;
        auto P = [&](double r, double z) { return gp_Pnt(bx + r, by, z); };
        prof.Add(BRepBuilderAPI_MakeEdge(P(0, zBot), P(shR * 0.8, zBot)));
        double z = zBot;
        while (z + pitch < zShank) {
          prof.Add(BRepBuilderAPI_MakeEdge(P(z == zBot ? shR * 0.8 : shR, z),
                                           P(thR, z + pitch / 2)));
          prof.Add(BRepBuilderAPI_MakeEdge(P(thR, z + pitch / 2),
                                           P(shR, z + pitch)));
          z += pitch;
        }
        prof.Add(BRepBuilderAPI_MakeEdge(P(shR, z), P(shR, zTop)));
        prof.Add(BRepBuilderAPI_MakeEdge(P(shR, zTop), P(0, zTop)));
        prof.Add(BRepBuilderAPI_MakeEdge(P(0, zTop), P(0, zBot)));
        TopoDS_Face f = BRepLib_MakeFace(prof.Wire()).Face();
        BRepPrimAPI_MakeRevol rev(f, gp_Ax1(gp_Pnt(bx, by, 0), gp::DZ()));
        rev.Build();
        if (rev.IsDone())
          addLocal(rev.Shape());
      }
      // 六角头
      {
        BRepBuilderAPI_MakePolygon hex;
        double hr = 13.0;
        for (int k = 0; k < 6; ++k) {
          double a = k * M_PI / 3.0;
          hex.Add(gp_Pnt(bx + hr * std::cos(a), by + hr * std::sin(a), zTop));
        }
        hex.Close();
        addLocal(BRepPrimAPI_MakePrism(BRepLib_MakeFace(hex.Wire()).Face(),
                                       gp_Vec(0, 0, 12)).Shape());
      }
      // 平垫圈 (压住弹条两后冠)
      {
        TopoDS_Shape washer = BRepAlgoAPI_Cut(
            BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(bx, by, 50), gp::DZ()),
                                     22.0, 5).Shape(),
            BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(bx, by, 49), gp::DZ()),
                                     9.5, 7).Shape()).Shape();
        addLocal(washer);
      }
    }
  };

  addPad(-1.0);
  addPad(1.0);
  return cmp;
}

// =========================================================================
// 减速顶（点）
// =========================================================================
TopoDS_Shape create_retarder_point(const retarder_point_params &params) {
  double bodyH = params.height * 0.5;
  double bodyR = params.bodyDiameter / 2.0;
  double capR = params.capDiameter / 2.0;
  double capH = params.capHeight;
  double armLen = params.armLength;
  double armW = params.armWidth;
  double armT = params.armThickness;
  double boltR = params.boltDiameter / 2.0;
  double portR = params.portDiameter / 2.0;

  BRep_Builder bld;
  TopoDS_Compound cmp;
  bld.MakeCompound(cmp);

  // 六角棱柱 (螺栓头/堵头)
  auto hexPrism = [&](const gp_Pnt &c, double r, double h, const gp_Dir &axis) {
    gp_Dir u = std::abs(axis.Z()) < 0.9 ? gp_Dir(axis.Crossed(gp::DZ())) : gp::DX();
    gp_Dir v = axis.Crossed(u);
    BRepBuilderAPI_MakePolygon hex;
    for (int k = 0; k < 6; ++k) {
      double a = k * M_PI / 3.0;
      hex.Add(c.Translated(gp_Vec(u.XYZ()) * (r * std::cos(a)) +
                             gp_Vec(v.XYZ()) * (r * std::sin(a))));
    }
    hex.Close();
    return BRepPrimAPI_MakePrism(BRepLib_MakeFace(hex.Wire()).Face(),
                                 gp_Vec(axis.XYZ()) * h).Shape();
  };

  // 1. 主缸体
  bld.Add(cmp, BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, 0), gp::DZ()),
                                        bodyR, bodyH).Shape());

  // 2. 缸口密封压盖法兰 + 法兰侧堵头 (贴在法兰侧面)
  bld.Add(cmp, BRepPrimAPI_MakeCylinder(
      gp_Ax2(gp_Pnt(0, 0, bodyH - 8), gp::DZ()), bodyR * 1.12, 8).Shape());
  bld.Add(cmp, BRepPrimAPI_MakeCylinder(
      gp_Ax2(gp_Pnt(bodyR * 0.8, 0, bodyH - 4), gp::DX()), boltR * 0.6,
      bodyR * 0.55).Shape());
  bld.Add(cmp, hexPrism(gp_Pnt(bodyR * 1.35, 0, bodyH - 4), boltR * 1.1, 5,
                        gp::DX()));

  // 3. 活塞杆 (压入状态, 外露段约为缸体的一半)
  double stemR = capR * 0.62;
  double stemTop = bodyH + params.height * 0.32;
  bld.Add(cmp, BRepPrimAPI_MakeCylinder(
      gp_Ax2(gp_Pnt(0, 0, bodyH - 10), gp::DZ()), stemR,
      stemTop - bodyH + 10).Shape());

  // 4. 蘑菇顶帽: 帽檐 + 扁平圆顶 (球冠高 ≈ 0.5×capHeight)
  double rimH = capH * 0.3;
  bld.Add(cmp, BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, stemTop), gp::DZ()),
                                        capR, rimH).Shape());
  {
    double rimTop = stemTop + rimH;
    double domeH = capH * 0.5;
    double Rs = (capR * capR + domeH * domeH) / (2 * domeH); // 浅球冠半径
    gp_Pnt center(0, 0, rimTop + domeH - Rs);
    TopoDS_Shape sphere = BRepPrimAPI_MakeSphere(center, Rs).Shape();
    TopoDS_Shape cutBox = BRepPrimAPI_MakeBox(
        gp_Pnt(-capR * 1.2, -capR * 1.2, rimTop), capR * 2.4, capR * 2.4,
        domeH + Rs).Shape();
    bld.Add(cmp, BRepAlgoAPI_Common(sphere, cutBox).Shape());
  }

  // 5. 固定臂 ×2 (八字张开, 各带端部竖直夹板 + 双水平六角螺栓)
  double armZ = bodyH - 10;
  const double armSpread = 0.21; // 八字张开角 (rad, 单侧 ~12°)
  for (int side = -1; side <= 1; side += 2) {
    double x0 = side * armW * 0.85;
    BRep_Builder ab; TopoDS_Compound arm; ab.MakeCompound(arm);
    // 肘臂圆管 (铸件弯臂, 根部埋入缸体)
    ab.Add(arm, BRepPrimAPI_MakeCylinder(
        gp_Ax2(gp_Pnt(x0, -bodyR * 0.2, armZ), gp::DY()), armT,
        bodyR * 0.6 + armLen).Shape());
    // 端部竖直夹板
    ab.Add(arm, BRepPrimAPI_MakeBox(
        gp_Pnt(x0 - armW * 0.7, bodyR * 0.4 + armLen, armZ - armW * 0.7),
        armW * 1.4, armT, armW * 1.4).Shape());
    // 双水平六角螺栓
    for (int s = -1; s <= 1; s += 2) {
      double bx = x0 + s * armW * 0.35;
      double by = bodyR * 0.4 + armLen;
      ab.Add(arm, BRepPrimAPI_MakeCylinder(
          gp_Ax2(gp_Pnt(bx, by + armT, armZ), gp::DY()), boltR,
          armT + 14).Shape());
      ab.Add(arm, hexPrism(gp_Pnt(bx, by + armT + 14, armZ), boltR * 1.8, 7,
                           gp::DY()));
    }
    // 绕各自臂根向外张开 (外八字)
    gp_Trsf spread;
    spread.SetRotation(gp_Ax1(gp_Pnt(x0, 0, armZ), gp::DZ()),
                       -side * armSpread);
    bld.Add(cmp, BRepBuilderAPI_Transform(arm, spread).Shape());
  }

  // 6. 缸体侧面堵头 ×2 (外凸 4mm)
  for (int k = 0; k < 2; ++k) {
    double pz = bodyH * (0.45 + 0.15 * k);
    bld.Add(cmp, BRepPrimAPI_MakeCylinder(
        gp_Ax2(gp_Pnt(0, -bodyR - 4, pz), gp::DY()), boltR * 0.5, 10).Shape());
  }

  // 7. 底部侧向油口 (黄铜接头, 与缸体相连)
  bld.Add(cmp, BRepPrimAPI_MakeCylinder(
      gp_Ax2(gp_Pnt(0, -bodyR, bodyH * 0.12), gp::DY().Reversed()), portR,
      14).Shape());
  bld.Add(cmp, BRepPrimAPI_MakeCylinder(
      gp_Ax2(gp_Pnt(0, -bodyR - 14, bodyH * 0.12), gp::DY().Reversed()),
      portR * 0.45, 6).Shape());

  // Transform to position
  if (params.position.Distance(gp::Origin()) > Precision::Confusion() ||
      fabs(params.rotation) > Precision::Angular()) {
    gp_Trsf t;
    t.SetTranslation(gp_Vec(params.position.X(), params.position.Y(),
                            params.position.Z()));
    if (fabs(params.rotation) > Precision::Angular()) {
      gp_Trsf r;
      r.SetRotation(gp_Ax1(gp::Origin(), gp::DZ()), params.rotation);
      t = r * t;
    }
    BRepBuilderAPI_Transform xform(cmp, t);
    return xform.Shape();
  }

  return cmp;
}

TopoDS_Shape create_retarder_point(const retarder_point_params &params,
                                   const gp_Pnt &position,
                                   const gp_Dir &direction,
                                   const gp_Dir &upDir) {
  TopoDS_Shape shape = create_retarder_point(params);
  gp_Dir yDir = upDir.Crossed(direction);
  gp_Ax3 src(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 tgt(position, upDir, direction);
  gp_Trsf trsf;
  trsf.SetTransformation(tgt, src);
  return BRepBuilderAPI_Transform(shape, trsf).Shape();
}

// =========================================================================
// 道床（由枕木线驱动）
// =========================================================================
TopoDS_Shape create_ballast_from_sleepers(const ballast_from_sleepers_params &params) {
  if (params.sleepers.empty()) throw Standard_ConstructionError("ballast: no sleepers");
  double minX = 1e38, maxX = -1e38, minY = 1e38, maxY = -1e38, sz = 0;
  for (auto &sl : params.sleepers) {
    minX = std::min(minX, std::min(sl.startPoint.X(), sl.endPoint.X()));
    maxX = std::max(maxX, std::max(sl.startPoint.X(), sl.endPoint.X()));
    minY = std::min(minY, std::min(sl.startPoint.Y(), sl.endPoint.Y()));
    maxY = std::max(maxY, std::max(sl.startPoint.Y(), sl.endPoint.Y()));
    sz = sl.startPoint.Z();
  }
  double tw = params.topWidth, th = params.thickness, ss = params.sideSlope;
  double bw = tw + 2 * th * ss, hbw = bw / 2, htw = tw / 2;
  BRepBuilderAPI_MakeWire w;
  w.Add(makeEdgeSafe(gp_Pnt(0, -hbw, 0), gp_Pnt(0, -htw, th)));
  w.Add(makeEdgeSafe(gp_Pnt(0, -htw, th), gp_Pnt(0, htw, th)));
  w.Add(makeEdgeSafe(gp_Pnt(0, htw, th), gp_Pnt(0, hbw, 0)));
  w.Add(makeEdgeSafe(gp_Pnt(0, hbw, 0), gp_Pnt(0, -hbw, 0)));
  TopoDS_Face face = BRepLib_MakeFace(w.Wire()).Face();
  double len = maxX - minX + 1000;
  TopoDS_Shape ballast = BRepPrimAPI_MakePrism(face, gp_Vec(len, 0, 0)).Shape();
  gp_Trsf tr; tr.SetTranslation(gp_Vec(minX - 500, (minY + maxY) / 2, sz - th));
  return BRepBuilderAPI_Transform(ballast, tr).Shape();
}

// =========================================================================
// 道岔（由独立元素组合）
// =========================================================================
TopoDS_Shape create_turnout_assembly(const turnout_assembly_params &params) {
  BRep_Builder bld; TopoDS_Compound cmp; bld.MakeCompound(cmp);
  for (auto &r : params.rails)      try { bld.Add(cmp, create_rail_curve(r)); } catch (...) { warn_part_failed("create_turnout_assembly", "rail"); }
  for (auto &w : params.wingRails)  try { bld.Add(cmp, create_wing_rail_curve(w)); } catch (...) { warn_part_failed("create_turnout_assembly", "wing rail"); }
  for (auto &g : params.guardRails) try { bld.Add(cmp, create_guard_rail_curve(g)); } catch (...) { warn_part_failed("create_turnout_assembly", "guard rail"); }
  for (auto &s : params.sleepers)   try { bld.Add(cmp, create_sleeper_line(s)); } catch (...) { warn_part_failed("create_turnout_assembly", "sleeper"); }
  for (auto &f : params.fasteners)  try {
    fastener_point_params fp; fp.position = f.position; fp.railNormal = gp::DY(); fp.railBaseWidth = 150.0; fp.padThickness = f.padThickness;
    bld.Add(cmp, create_fastener_point(fp));
  } catch (...) { warn_part_failed("create_turnout_assembly", "fastener"); }
  return cmp;
}

TopoDS_Shape create_turnout_assembly(const turnout_assembly_params &params,
                                      const gp_Pnt &position,
                                      const gp_Dir &direction,
                                      const gp_Dir &upDir) {
  TopoDS_Shape shape = create_turnout_assembly(params);
  gp_Dir yDir = upDir.Crossed(direction);
  gp_Ax3 src(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 tgt(position, upDir, direction);
  gp_Trsf tr; tr.SetTransformation(tgt, src);
  return BRepBuilderAPI_Transform(shape, tr).Shape();
}

TopoDS_Shape create_expansion_joint(const expansion_joint_params &params) {
  BRep_Builder bld; TopoDS_Compound cmp; bld.MakeCompound(cmp);
  try { bld.Add(cmp, create_rail_curve(params.stockRail)); } catch (...) { warn_part_failed("create_expansion_joint", "stock rail"); }
  try { bld.Add(cmp, create_rail_curve(params.switchRail)); } catch (...) { warn_part_failed("create_expansion_joint", "switch rail"); }
  return cmp;
}

TopoDS_Shape create_expansion_joint(const expansion_joint_params &params,
                                     const gp_Pnt &position,
                                     const gp_Dir &direction,
                                     const gp_Dir &upDir) {
  TopoDS_Shape shape = create_expansion_joint(params);
  gp_Dir yDir = upDir.Crossed(direction);
  gp_Ax3 src(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 tgt(position, upDir, direction);
  gp_Trsf tr; tr.SetTransformation(tgt, src);
  return BRepBuilderAPI_Transform(shape, tr).Shape();
}



} // namespace topo
} // namespace flywave
