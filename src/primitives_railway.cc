#include "primitives_railway.hh"

#include <BRepAlgoAPI_Cut.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
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
#include <BRep_Tool.hxx>
#include <GC_MakeArcOfCircle.hxx>
#include <GC_MakeSegment.hxx>
#include <Geom_BezierCurve.hxx>
#include <Geom_Circle.hxx>
#include <Geom_Plane.hxx>
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

  // Build contact wire cross-section profile:
  //   Top: clamping area with rounded edge (semi-circle R=topRadius)
  //   Middle: trapezoidal transition
  //   Bottom: contact surface arc (R=bottomRadius)
  //   Sides: grooves (deep grooveDepth, wide grooveWidth)
  const double R = params.diameter / 2.0;
  const double h = params.diameter * 0.6; // approximate profile height
  const double gD = params.grooveDepth > 0 ? params.grooveDepth : 2.0;
  const double gW = params.grooveWidth > 0 ? params.grooveWidth : 3.0;
  const double bR = params.bottomRadius > 0 ? params.bottomRadius : R * 0.6;
  const double tR = params.topRadius > 0 ? params.topRadius : 3.0;

  // Build profile points (YZ plane, centered on X axis)
  // Starting from bottom center, going clockwise
  double bottomArcCenterY = 0;
  double bottomArcCenterZ = bR;

  // Key profile points
  gp_Pnt p0(0, -R, 0);                           // bottom-left
  gp_Pnt p1(0, -R + gD, -gW / 2);                // groove bottom-left
  gp_Pnt p2(0, -R + gD, gW / 2);                 // groove bottom-right
  gp_Pnt p3(0, -R + gD + (h - 2 * bR), gW / 2);  // shoulder-right
  gp_Pnt p4(0, -R + gD + (h - 2 * bR), -gW / 2); // shoulder-left
  gp_Pnt p5(0, -R, h);                           // top-left

  // Bottom arc
  gp_Circ bottomArc(gp_Ax2(gp_Pnt(0, 0, bR), gp_Dir(1, 0, 0)), bR);
  Handle(Geom_TrimmedCurve) bottomArcCurve =
      GC_MakeArcOfCircle(bottomArc, -M_PI / 2, M_PI / 2, false).Value();

  TopoDS_Edge bottomArcEdge = BRepBuilderAPI_MakeEdge(bottomArcCurve).Edge();
  TopoDS_Edge e1 = BRepBuilderAPI_MakeEdge(p0, p1).Edge();
  TopoDS_Edge e2 = BRepBuilderAPI_MakeEdge(p1, p2).Edge();
  TopoDS_Edge e3 = BRepBuilderAPI_MakeEdge(p2, p3).Edge();
  TopoDS_Edge e4 = BRepBuilderAPI_MakeEdge(p3, p4).Edge();
  TopoDS_Edge e5 = BRepBuilderAPI_MakeEdge(p4, p5).Edge();

  // Top semi-circle for clamping area
  gp_Circ topArc(gp_Ax2(gp_Pnt(0, -R + h - tR, -tR), gp_Dir(0, 0, 1)), tR);
  Handle(Geom_TrimmedCurve) topArcCurve =
      GC_MakeArcOfCircle(topArc, -M_PI / 2, M_PI / 2, false).Value();
  TopoDS_Edge topArcEdge = BRepBuilderAPI_MakeEdge(topArcCurve).Edge();

  BRepBuilderAPI_MakeWire wireMaker;
  wireMaker.Add(bottomArcEdge);
  wireMaker.Add(e1);
  wireMaker.Add(e2);
  wireMaker.Add(e3);
  wireMaker.Add(e4);
  wireMaker.Add(e5);
  wireMaker.Add(topArcEdge);
  TopoDS_Wire profileWire = wireMaker.Wire();

  TopoDS_Face profileFace = BRepBuilderAPI_MakeFace(profileWire).Face();

  // Extrude along the path from startPoint to endPoint
  gp_Vec pathVec(startPoint, endPoint);
  return BRepPrimAPI_MakePrism(profileFace, pathVec).Shape();
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

  // Create a circular profile centered at startPoint
  gp_Ax2 axis(startPoint, gp_Dir(endPoint.XYZ() - startPoint.XYZ()));
  gp_Circ sectionCircle(axis, radius);
  TopoDS_Edge sectionEdge = BRepBuilderAPI_MakeEdge(sectionCircle).Edge();
  TopoDS_Wire sectionWire = BRepBuilderAPI_MakeWire(sectionEdge).Wire();
  TopoDS_Face sectionFace = BRepBuilderAPI_MakeFace(sectionWire).Face();

  // Extrude along path
  gp_Vec pathVec(startPoint, endPoint);
  return BRepPrimAPI_MakePrism(sectionFace, pathVec).Shape();
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

  // Upper beam — along Y (perpendicular to track)
  gp_Pnt ubOrg(0, -BL / 2, gap + BH / 2);
  TopoDS_Shape upperBeam = BRepPrimAPI_MakeBox(ubOrg, BW, BL, BH).Shape();
  builder.Add(compound, upperBeam);

  // Lower beam
  gp_Pnt lbOrg(0, -BL / 2, -BH / 2);
  TopoDS_Shape lowerBeam = BRepPrimAPI_MakeBox(lbOrg, BW, BL, BH).Shape();
  builder.Add(compound, lowerBeam);

  // Two diagonal braces — cross at center (定交点固定于立柱)
  double braceR = BW * 0.25;
  for (int side = -1; side <= 1; side += 2) {
    gp_Pnt p1(0, side * BL * 0.45, gap + BH);
    gp_Pnt p2(0, -side * BL * 0.45, 0);
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
      double z = (level == 0) ? BH / 2 : gap + BH + BH / 2;
      for (int bx = -1; bx <= 1; bx += 2)
        if (params.boltCount >= 3 || bx == 0)
          for (int by = -1; by <= 1; by += 2) {
            TopoDS_Shape h =
                BRepPrimAPI_MakeCylinder(
                    gp_Ax2(gp_Pnt(bx * hs, by * hs, z - BW / 2 - 1), gp::DY()),
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

  // Create tube along Z axis first (vertical), then rotate
  gp_Ax2 outerAxis(gp::Origin(), gp::DZ());
  TopoDS_Shape outerCyl =
      BRepPrimAPI_MakeCylinder(outerAxis, outerRadius, params.length).Shape();

  gp_Ax2 innerAxis(gp::Origin(), gp::DZ());
  TopoDS_Shape innerCyl =
      BRepPrimAPI_MakeCylinder(innerAxis, innerRadius, params.length).Shape();

  TopoDS_Shape tube = BRepAlgoAPI_Cut(outerCyl, innerCyl).Shape();

  // Rotate by slant angle around Y axis
  double angleRad = params.slantAngle * M_PI / 180.0;
  gp_Trsf rot;
  rot.SetRotation(gp_Ax1(gp::Origin(), gp::DY()), angleRad);
  return BRepBuilderAPI_Transform(tube, rot).Shape();
}

TopoDS_Shape create_slant_cantilever(const slant_cantilever_params &params,
                                     const gp_Pnt &basePoint,
                                     const gp_Dir &axisDirection,
                                     const gp_Dir &upDir) {
  TopoDS_Shape shape = create_slant_cantilever(params);

  gp_Dir yDir = upDir.Crossed(axisDirection);
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

  // Build centerline path: vertical straight + quarter-circle arc + horizontal
  // straight Arc center: (R, 0, V-R), quarter turn from Z-direction to
  // X-direction
  gp_Pnt arcCenter(R, 0, V - R);

  // Vertical segment: from origin to arc start point (0, 0, V-R)
  gp_Pnt vStart(0, 0, 0);
  gp_Pnt arcStart(0, 0, V - R);

  // Quarter-circle arc (in XZ plane, from left to top of center)
  // At parameter 0: arcCenter + (R*cos(0), 0, R*sin(0)) = (R+R, 0, V-R) — right
  // side At parameter pi/2: arcCenter + (R*cos(pi/2), 0, R*sin(pi/2)) = (R, 0,
  // V) — top At parameter pi: arcCenter + (R*cos(pi), 0, R*sin(pi)) = (0, 0,
  // V-R) — left side Arc from pi to pi/2: quarter turn left-to-top (Z-vertical
  // to X-horizontal)
  gp_Circ arcCircle(gp_Ax2(arcCenter, gp_Dir(0, -1, 0)), R);
  Handle(Geom_TrimmedCurve) arcCurve =
      GC_MakeArcOfCircle(arcCircle, M_PI, M_PI / 2, false).Value();

  // Horizontal segment: from arc end to horizontal end
  gp_Pnt arcEnd(R, 0, V);
  gp_Pnt hEnd(H, 0, V);

  TopoDS_Edge vertEdge = BRepBuilderAPI_MakeEdge(vStart, arcStart).Edge();
  TopoDS_Edge arcEdge = BRepBuilderAPI_MakeEdge(arcCurve).Edge();
  TopoDS_Edge hEdge = BRepBuilderAPI_MakeEdge(arcEnd, hEnd).Edge();

  BRepBuilderAPI_MakeWire pathMaker;
  pathMaker.Add(vertEdge);
  pathMaker.Add(arcEdge);
  pathMaker.Add(hEdge);
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

  // Add mounting flange at base
  if (params.flangeThickness > 0) {
    double flangeSize = params.outerDiameter * 2;
    gp_Pnt flangeOrigin(-flangeSize / 2, -flangeSize / 2,
                        -params.flangeThickness);
    TopoDS_Shape flange =
        BRepPrimAPI_MakeBox(flangeOrigin, flangeSize, flangeSize,
                            params.flangeThickness)
            .Shape();
    arm = BRepAlgoAPI_Fuse(arm, flange).Shape();
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

  // Main rod body — hollow if innerDiameter > 0
  gp_Ax2 rodAxis(gp::Origin(), gp::DZ());
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

  if (params.shedCount == 0)
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
    double zPos = (i + 1) * shedSpacing;
    double r = (i % 2 == 0) ? shedMajorR : shedMinorR;

    // 5-point shed profile (references GIM porcelain bushing pattern)
    // basePoint → outer edge → upper lip → inner dip → end point
    BRepBuilderAPI_MakeWire wire;
    gp_Pnt basePt(rodRadius, 0, zPos);
    gp_Pnt p1(r, 0, zPos);
    gp_Pnt p2(r * 0.95, 0, zPos + segH * 0.25);
    gp_Pnt p3(r * 0.7, 0, zPos + segH * 0.4);
    gp_Pnt endPt(rodRadius, 0, zPos + segH * 0.25);

    wire.Add(BRepBuilderAPI_MakeEdge(basePt, p1));
    wire.Add(BRepBuilderAPI_MakeEdge(p1, p2));
    wire.Add(BRepBuilderAPI_MakeEdge(p2, p3));
    wire.Add(BRepBuilderAPI_MakeEdge(p3, endPt));
    wire.Add(BRepBuilderAPI_MakeEdge(endPt, basePt));

    if (!wire.IsDone())
      throw Standard_ConstructionError("Shed wire not closed");

    TopoDS_Face face = BRepLib_MakeFace(wire.Wire()).Face();
    BRepPrimAPI_MakeRevol revol(face, gp_Ax1(gp::Origin(), gp::DZ()));
    revol.Build();
    TopoDS_Shape shed = revol.Shape();
    if (shed.IsNull())
      throw Standard_ConstructionError("Shed revolution failed");

    builder.Add(compound, shed);
  }

  // End flanges
  if (params.endFitting == end_fitting_type::FLANGE &&
      params.flangeDiameter > rodRadius * 2) {
    double flangeR = params.flangeDiameter / 2.0;
    double flangeH = params.height * 0.05;
    gp_Ax2 botAxis(gp_Pnt(0, 0, -flangeH), gp::DZ());
    TopoDS_Shape botFlange =
        BRepPrimAPI_MakeCylinder(botAxis, flangeR, flangeH).Shape();
    builder.Add(compound, botFlange);

    gp_Ax2 topAxis(gp_Pnt(0, 0, params.height), gp::DZ());
    TopoDS_Shape topFlange =
        BRepPrimAPI_MakeCylinder(topAxis, flangeR, flangeH).Shape();
    builder.Add(compound, topFlange);
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

  BRep_Builder builder;
  TopoDS_Compound compound;
  builder.MakeCompound(compound);

  // Main plate
  gp_Pnt plateOrg(-params.thickness / 2.0, -params.width / 2.0, 0);
  TopoDS_Shape plate = BRepPrimAPI_MakeBox(plateOrg, params.thickness,
                                           params.width, params.height)
                           .Shape();
  builder.Add(compound, plate);

  // Mounting bolt holes
  if (params.boltDiameter > 0 && params.boltSpacing > 0) {
    double hs = params.boltSpacing / 2.0;
    double midZ = params.height / 2.0;
    double holeR = params.boltDiameter / 2.0;
    gp_Pnt hc[4] = {{0, -hs, midZ - hs},
                    {0, hs, midZ - hs},
                    {0, -hs, midZ + hs},
                    {0, hs, midZ + hs}};
    for (auto &c : hc) {
      TopoDS_Shape hole = BRepPrimAPI_MakeCylinder(gp_Ax2(c, gp::DX()), holeR,
                                                   params.thickness + 2)
                              .Shape();
      plate = BRepAlgoAPI_Cut(plate, hole).Shape();
    }
  }

  // Insulator ear plates
  if (params.insulatorBoltSpacing > 0) {
    double eT = params.thickness * 0.8;
    double eW = params.width * 0.3;
    double eH = params.height * 0.6;
    double eOff = params.thickness / 2.0;
    double eZ = (params.height - eH) / 2.0;

    // Two ear plates at top and bottom edges
    for (int side = 0; side < 2; ++side) {
      double y = (side == 0) ? -eW / 2.0 : params.width - eW / 2.0;
      gp_Pnt earOrg(eOff, y, eZ);
      TopoDS_Shape ear = BRepPrimAPI_MakeBox(earOrg, eT, eW, eH).Shape();
      plate = BRepAlgoAPI_Fuse(plate, ear).Shape();

      // Ear pin hole
      if (params.insulatorBoltDiameter > 0) {
        double hr = params.insulatorBoltDiameter / 2.0;
        double hz = params.height / 2.0;
        TopoDS_Shape hole =
            BRepPrimAPI_MakeCylinder(
                gp_Ax2(gp_Pnt(eOff, params.width / 2.0, hz), gp::DY()), hr,
                eW + 2)
                .Shape();
        plate = BRepAlgoAPI_Cut(plate, hole).Shape();
      }
    }
  }

  // Stiffener ribs (triangular plates connecting plate to mast)
  double ribH = params.height * 0.3;
  double ribW = params.thickness * 2.0;
  double ribThick = params.thickness * 0.5;
  for (int side = -1; side <= 1; side += 2) {
    double y = params.width / 2.0 + side * (params.width / 2.0 - ribW);
    gp_Pnt rp1(-params.thickness / 2.0, y, params.height / 2.0);
    gp_Pnt rp2(-params.thickness / 2.0 - ribW, y,
               params.height / 2.0 - ribH / 2.0);
    gp_Pnt rp3(-params.thickness / 2.0 - ribW, y,
               params.height / 2.0 + ribH / 2.0);
    TopoDS_Wire rw =
        BRepBuilderAPI_MakePolygon(rp1, rp2, rp3, Standard_True).Wire();
    TopoDS_Face rf = BRepLib_MakeFace(rw).Face();
    TopoDS_Shape rib =
        BRepPrimAPI_MakePrism(rf, gp_Vec(0, -side * ribThick, 0)).Shape();
    plate = BRepAlgoAPI_Fuse(plate, rib).Shape();
  }

  // Apply mount angle
  if (std::abs(params.mountAngle) > Precision::Angular()) {
    double a = params.mountAngle * M_PI / 180.0;
    gp_Trsf rot;
    rot.SetRotation(
        gp_Ax1(gp_Pnt(0, params.width / 2.0, params.height / 2.0), gp::DY()),
        a);
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
TopoDS_Shape create_guy_wire(const guy_wire_params &params) {
  if (params.length <= 0 || params.diameter <= 0)
    throw Standard_ConstructionError("Length and diameter must be positive");

  double radius = params.diameter / 2;

  // Wire body — a straight cable segment
  gp_Ax2 wireAxis(gp::Origin(), gp::DZ());
  TopoDS_Shape wire =
      BRepPrimAPI_MakeCylinder(wireAxis, radius, params.length).Shape();

  // Apply angle (rotate from vertical to specified angle)
  double angleRad = params.angle * M_PI / 180.0;
  gp_Trsf rot;
  rot.SetRotation(gp_Ax1(gp::Origin(), gp::DY()), M_PI / 2 - angleRad);
  return BRepBuilderAPI_Transform(wire, rot).Shape();
}

TopoDS_Shape create_guy_wire(const guy_wire_params &params,
                             const gp_Pnt &anchorPoint, const gp_Pnt &mastPoint,
                             const gp_Dir &upDir) {
  // Calculate direction and length from anchor to mast point
  gp_Vec vec(anchorPoint, mastPoint);
  double len = vec.Magnitude();
  if (len <= Precision::Confusion())
    throw Standard_ConstructionError("Anchor and mast points must differ");

  // Create wire segment directly along the vector
  double radius = params.diameter / 2;
  gp_Ax2 wireAxis(anchorPoint, gp_Dir(vec));
  TopoDS_Shape wire = BRepPrimAPI_MakeCylinder(wireAxis, radius, len).Shape();

  return wire;
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
  // L-shape in the XY plane: origin at the outer corner
  // Long leg along +Y, short leg along +X
  w.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(0, 0, 0), gp_Pnt(0, legLong, 0)));
  w.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(0, legLong, 0),
                                gp_Pnt(thick, legLong, 0)));
  w.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(thick, legLong, 0),
                                gp_Pnt(thick, legShort, 0)));
  w.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(thick, legShort, 0), gp_Pnt(0, 0, 0)));
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
    double legT = L * 0.8;
    double halfB = B / 2.0, halfT = T / 2.0;

    auto makeTaperedLeg = [&](double sx, double sy) -> TopoDS_Shape {
      double xb = sx * halfB, yb = sy * halfB;
      double xt = sx * halfT, yt = sy * halfT;
      gp_Circ bc(gp_Ax2(gp_Pnt(xb, yb, 0), gp::DZ()), legW / 2);
      TopoDS_Wire bw =
          BRepBuilderAPI_MakeWire(BRepBuilderAPI_MakeEdge(bc)).Wire();
      gp_Circ tc(gp_Ax2(gp_Pnt(xt, yt, H), gp::DZ()), legW * 0.6 / 2);
      TopoDS_Wire tw =
          BRepBuilderAPI_MakeWire(BRepBuilderAPI_MakeEdge(tc)).Wire();
      BRepOffsetAPI_ThruSections lg(Standard_True);
      lg.AddWire(bw);
      lg.AddWire(tw);
      lg.Build();
      return lg.IsDone() ? lg.Shape()
                         : BRepPrimAPI_MakeCylinder(
                               gp_Ax2(gp_Pnt(xb, yb, 0), gp::DZ()), legW / 2, H)
                               .Shape();
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
    // Round wind holes — diameter proportional to current column width
    if (params.holeDiameter > 0 && params.holeSpacingV > 0) {
      for (double z = params.firstHoleOffset; z < params.height;
           z += params.holeSpacingV) {
        double curW = b + (t - b) * z / params.height;
        double holeR = params.holeDiameter * curW / b / 2;
        TopoDS_Shape h = BRepPrimAPI_MakeCylinder(
                             gp_Ax2(gp_Pnt(-thinW, 0, z), gp::DX(), gp::DZ()),
                             holeR, curW * 4)
                             .Shape();
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
    foundation =
        BRepPrimAPI_MakeBox(gp_Pnt(-params.length / 2, -params.width / 2, 0),
                            params.length, params.width, params.height)
            .Shape();
    if (params.flangeThickness > 0) {
      double fs = std::min(params.length, params.width) * 0.8;
      foundation = BRepAlgoAPI_Fuse(foundation,
                                    BRepPrimAPI_MakeBox(
                                        gp_Pnt(-fs / 2, -fs / 2, params.height),
                                        fs, fs, params.flangeThickness)
                                        .Shape())
                       .Shape();
    }
    if (params.anchorCount > 0 && params.anchorDiameter > 0) {
      double hs = params.anchorSpacing / 2, br = params.anchorDiameter / 2,
             th = params.height + params.flangeThickness + params.anchorLength;
      for (int ax = -1; ax <= 1; ax += 2)
        for (int ay = -1; ay <= 1; ay += 2) {
          if (params.anchorCount >= 4 || (ax == -1 && ay == -1))
            foundation =
                BRepAlgoAPI_Fuse(
                    foundation,
                    BRepPrimAPI_MakeCylinder(
                        gp_Ax2(gp_Pnt(ax * hs, ay * hs, 0), gp::DZ()), br, th)
                        .Shape())
                    .Shape();
        }
    }
    break;
  case foundation_type::DIRECT_BURIED:
    foundation = BRepPrimAPI_MakeCylinder(
                     gp_Ax2(gp::Origin(), gp::DZ()),
                     std::min(params.length, params.width) / 2, params.height)
                     .Shape();
    break;
  case foundation_type::BORED_PILE: {
    double pr = std::min(params.length, params.width) / 2;
    foundation = BRepPrimAPI_MakeCylinder(gp_Ax2(gp::Origin(), gp::DZ()), pr,
                                          params.height)
                     .Shape();
    foundation = BRepAlgoAPI_Fuse(
                     foundation,
                     BRepPrimAPI_MakeCone(
                         gp_Ax2(gp_Pnt(0, 0, params.height * 0.85), gp::DZ()),
                         pr * 1.3, pr, params.height * 0.15)
                         .Shape())
                     .Shape();
    break;
  }
  default:
    foundation = BRepPrimAPI_MakeCylinder(
                     gp_Ax2(gp::Origin(), gp::DZ()),
                     std::min(params.length, params.width) / 2, params.height)
                     .Shape();
    break;
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
// =========================================================================
TopoDS_Shape create_dropper(const dropper_params &params) {
  if (params.length <= 0 || params.wireDiameter <= 0)
    throw Standard_ConstructionError("Invalid dimensions");
  double wr = params.wireDiameter / 2;
  TopoDS_Shape wire = BRepPrimAPI_MakeCylinder(gp_Ax2(gp::Origin(), gp::DZ()),
                                               wr, params.length)
                          .Shape();
  if (params.clampLength > 0 && params.clampWidth > 0) {
    double ch =
        params.clampThickness > 0 ? params.clampThickness : params.wireDiameter;
    wire = BRepAlgoAPI_Fuse(wire,
                            BRepPrimAPI_MakeBox(
                                gp_Pnt(-params.clampWidth / 2,
                                       -params.clampWidth / 2, params.length),
                                params.clampWidth, params.clampWidth, ch)
                                .Shape())
               .Shape();
    wire = BRepAlgoAPI_Fuse(wire, BRepPrimAPI_MakeBox(
                                      gp_Pnt(-params.clampWidth / 2,
                                             -params.clampWidth / 2, -ch),
                                      params.clampWidth, params.clampWidth, ch)
                                      .Shape())
               .Shape();
  }
  return wire;
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
  if (params.width <= 0 || params.thickness <= 0 || params.height <= 0)
    throw Standard_ConstructionError("Invalid dimensions");
  TopoDS_Shape b =
      BRepPrimAPI_MakeBox(gp_Pnt(-params.width / 2, -params.thickness / 2, 0),
                          params.width, params.thickness, params.height)
          .Shape();
  double fr = std::min({params.width, params.thickness, params.height}) * 0.08;
  if (fr > Precision::Confusion()) {
    BRepFilletAPI_MakeFillet fillet(b);
    for (TopExp_Explorer ex(b, TopAbs_EDGE); ex.More(); ex.Next()) {
      TopoDS_Edge e = TopoDS::Edge(ex.Current());
      gp_Pnt p1 = BRep_Tool::Pnt(TopExp::FirstVertex(e)),
             p2 = BRep_Tool::Pnt(TopExp::LastVertex(e));
      if (std::abs(p1.Z() - p2.Z()) < Precision::Confusion() &&
          std::abs(p1.X() - p2.X()) > Precision::Confusion())
        fillet.Add(fr, e);
    }
    fillet.Build();
    if (fillet.IsDone())
      b = fillet.Shape();
  }
  if (params.centerHoleDiameter > 0)
    b = BRepAlgoAPI_Cut(b, BRepPrimAPI_MakeCylinder(
                               gp_Ax2(gp::Origin(), gp::DZ()),
                               params.centerHoleDiameter / 2, params.height + 2)
                               .Shape())
            .Shape();
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
    return BRepAlgoAPI_Fuse(
               BRepPrimAPI_MakeCylinder(gp_Ax2(gp::Origin(), gp::DX()), R,
                                        params.length)
                   .Shape(),
               BRepPrimAPI_MakeSphere(
                   gp_Ax2(gp_Pnt(params.length, 0, 0), gp::DX()), R * 1.5)
                   .Shape())
        .Shape();
  } else if (params.type == anchor_fitting_type::DOUBLE_EAR) {
    TopoDS_Shape b = BRepPrimAPI_MakeBox(gp_Pnt(-params.length / 2, -R, -R),
                                         params.length, R * 2, R * 2)
                         .Shape();
    if (R > 0) {
      b = BRepAlgoAPI_Cut(
              b, BRepPrimAPI_MakeCylinder(
                     gp_Ax2(gp_Pnt(-params.length / 3, 0, 0), gp::DY()),
                     R * 0.4, R * 4)
                     .Shape())
              .Shape();
      b = BRepAlgoAPI_Cut(b,
                          BRepPrimAPI_MakeCylinder(
                              gp_Ax2(gp_Pnt(params.length / 3, 0, 0), gp::DY()),
                              R * 0.4, R * 4)
                              .Shape())
              .Shape();
    }
    return b;
  } else {
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
    return gen.Shape();
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
TopoDS_Shape create_crossing(const crossing_params &params) {
  if (params.limitPipeLength <= 0)
    throw Standard_ConstructionError("Invalid pipe length");
  double pr = params.pipeDiameter / 2, wr = params.wireDiameter / 2;
  TopoDS_Shape pipe = BRepPrimAPI_MakeCylinder(gp_Ax2(gp::Origin(), gp::DX()),
                                               pr * 2, params.limitPipeLength)
                          .Shape();
  if (pr > 0)
    pipe = BRepAlgoAPI_Cut(
               pipe, BRepPrimAPI_MakeCylinder(gp_Ax2(gp::Origin(), gp::DX()),
                                              pr, params.limitPipeLength)
                         .Shape())
               .Shape();
  double wl = params.limitPipeLength / 2 * 3;
  TopoDS_Shape result =
      BRepAlgoAPI_Fuse(
          pipe, BRepPrimAPI_MakeCylinder(gp_Ax2(gp::Origin(), gp::DX()), wr, wl)
                    .Shape())
          .Shape();
  double a = M_PI / 6;
  result =
      BRepAlgoAPI_Fuse(
          result,
          BRepPrimAPI_MakeCylinder(
              gp_Ax2(gp_Pnt(-wl / 2, 0, 0), gp_Dir(cos(a), sin(a), 0)), wr, wl)
              .Shape())
          .Shape();
  return result;
}
TopoDS_Shape create_crossing(const crossing_params &params,
                             const gp_Pnt &crossPoint, const gp_Dir &mainDir,
                             const gp_Dir &branchDir) {
  TopoDS_Shape s = create_crossing(params);
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

  // Cross catenary — approximated as cylinder along Z at mid-point (simplified)
  gp_Pnt cl(0, 0, sag + 1000), cr(span, 0, sag + 1000);
  builder.Add(compound,
              BRepPrimAPI_MakeCylinder(gp_Ax2(cl, gp_Dir(cr.XYZ() - cl.XYZ())),
                                       cDia / 2, span)
                  .Shape());

  // Fixed ropes
  gp_Pnt ul(0, 0, sag + 800), ur(span, 0, sag + 800);
  builder.Add(compound,
              BRepPrimAPI_MakeCylinder(gp_Ax2(ul, gp_Dir(ur.XYZ() - ul.XYZ())),
                                       uDia / 2, span)
                  .Shape());
  gp_Pnt ll(0, 0, 800), lr(span, 0, 800);
  builder.Add(compound,
              BRepPrimAPI_MakeCylinder(gp_Ax2(ll, gp_Dir(lr.XYZ() - ll.XYZ())),
                                       lDia / 2, span)
                  .Shape());

  // Insulators
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
      builder.Add(compound, create_rod_insulator(rip, gp_Pnt(x, 0, sag + 1000),
                                                 gp::DZ()));
      builder.Add(compound,
                  create_rod_insulator(rip, gp_Pnt(x, 0, sag + 800), gp::DX()));
      builder.Add(compound,
                  create_rod_insulator(rip, gp_Pnt(x, 0, 800), gp::DX()));
    }
  }
  return compound;
}
TopoDS_Shape create_head_span(const head_span_params &params,
                              const gp_Pnt &leftMast, const gp_Pnt &rightMast,
                              const gp_Dir &upDir) {
  TopoDS_Shape s = create_head_span(params);
  gp_Vec v(leftMast, rightMast);
  double len = v.Magnitude();
  if (len <= Precision::Confusion())
    return s;
  double scale = len / params.span;
  gp_Trsf sc;
  sc.SetScale(gp::Origin(), scale);
  gp_Ax3 src(gp::Origin(), gp::DZ(), gp::DX()), tgt(leftMast, upDir, gp_Dir(v));
  gp_Trsf tr;
  tr.SetTransformation(tgt, src);
  return BRepBuilderAPI_Transform(BRepBuilderAPI_Transform(s, sc).Shape(), tr)
      .Shape();
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
  double len = vec.Magnitude();
  if (len < Precision::Confusion())
    return BRepPrimAPI_MakeCylinder(gp_Ax2(params.startPoint, gp::DX()), R, 1)
        .Shape();
  // Simplified: straight cylinder along span direction
  return BRepPrimAPI_MakeCylinder(gp_Ax2(params.startPoint, gp_Dir(vec)), R,
                                  len)
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
TopoDS_Shape create_rail(const rail_params &params) {
  rail_curve_params rp;
  rp.curve.type = curve_type::LINE;
  rp.curve.startPoint = gp::Origin();
  rp.curve.endPoint = gp_Pnt(0, 0, params.standardLength > 0 ? params.standardLength : 25000);
  rp.railHeight = params.railHeight;
  rp.headWidth = params.headWidth;
  rp.baseWidth = params.baseWidth;
  rp.webThickness = params.webThickness;
  rp.headHeight = params.headHeight;
  rp.baseHeight = params.baseHeight;
  rp.headRadius = params.headRadius;
  return create_rail_curve(rp);
}

TopoDS_Shape create_rail(const rail_params &params, const gp_Pnt &startPoint,
                         const gp_Pnt &endPoint) {
  rail_curve_params rp;
  rp.curve.type = curve_type::LINE;
  rp.curve.startPoint = startPoint;
  rp.curve.endPoint = endPoint;
  rp.railHeight = params.railHeight;
  rp.headWidth = params.headWidth;
  rp.baseWidth = params.baseWidth;
  rp.webThickness = params.webThickness;
  rp.headHeight = params.headHeight;
  rp.baseHeight = params.baseHeight;
  rp.headRadius = params.headRadius;
  return create_rail_curve(rp);
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
TopoDS_Shape create_ballast(const ballast_params &params) {
    if (params.centerlineSegments.empty() || params.centerlineSegments[0].points.size() < 2)
        throw Standard_ConstructionError("ballast: need >=2 points");
    ballast_from_sleepers_params bsp;
    // Construct artificial sleepers from centerline to derive ballast bounds
    auto &seg = params.centerlineSegments[0];
    double halfGauge = 800;
    for (size_t i = 0; i < seg.points.size(); ++i) {
        sleeper_line_params sp;
        sp.startPoint = gp_Pnt(seg.points[i].X(), seg.points[i].Y() - halfGauge, seg.points[i].Z());
        sp.endPoint = gp_Pnt(seg.points[i].X(), seg.points[i].Y() + halfGauge, seg.points[i].Z());
        bsp.sleepers.push_back(sp);
    }
    bsp.topWidth = params.topWidth;
    bsp.thickness = params.thickness;
    bsp.sideSlope = params.sideSlope;
    return create_ballast_from_sleepers(bsp);
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
    fp.side = 3;
    fp.padThickness = params.padThickness;
    return create_fastener_point(fp);
}

TopoDS_Shape create_fastener(const fastener_params &params,
                             const gp_Pnt &position, const gp_Dir &direction,
                             const gp_Dir &upDir) {
    fastener_point_params fp;
    fp.position = position;
    fp.side = 3;
    fp.padThickness = params.padThickness;
    if (!direction.IsEqual(gp::DX(), Precision::Angular()) || !upDir.IsEqual(gp::DZ(), Precision::Angular()))
        fp.rotation = direction.Angle(gp::DX());
    return create_fastener_point(fp);
}

// =========================================================================
// 29. Guard Rail (护轨)
// =========================================================================
TopoDS_Shape create_guard_rail(const guard_rail_params &params) {
    guard_rail_curve_params gp;
    gp.curve.type = curve_type::LINE;
    gp.curve.startPoint = gp::Origin();
    gp.curve.endPoint = gp_Pnt(params.totalLength, 0, 0);
    gp.channelHeight = params.height;
    gp.grooveWidth = params.grooveWidth;
    gp.flangeWidth = params.baseWidth;
    return create_guard_rail_curve(gp);
}

TopoDS_Shape create_guard_rail(const guard_rail_params &params,
                                const gp_Pnt &startPoint,
                               const gp_Pnt &endPoint) {
    guard_rail_curve_params gp;
    gp.curve.type = curve_type::LINE;
    gp.curve.startPoint = startPoint;
    gp.curve.endPoint = endPoint;
    gp.channelHeight = params.height;
    gp.grooveWidth = params.grooveWidth;
    gp.flangeWidth = params.baseWidth;
    return create_guard_rail_curve(gp);
}

// =========================================================================
// 30. Mast Assembly (支柱装配)
// =========================================================================
TopoDS_Shape create_mast_assembly(const mast_assembly_params &params) {
  // Start with mast
  steel_mast_params mastParams;
  mastParams.type = steel_mast_type::H_BEAM;
  mastParams.height = params.mastHeight;
  mastParams.topWidth = 200;
  mastParams.bottomWidth = 300;
  mastParams.wallThickness = 10;
  mastParams.flangeThickness = 16;
  mastParams.flangeWidth = 350;
  mastParams.anchorSpacing = 200;
  mastParams.anchorDiameter = 24;
  mastParams.segmentCount = 1;
  TopoDS_Shape result = create_steel_mast(mastParams);

  // Cantilever system
  if (params.cantileverType > 0) {
    double armDiam = params.armDiameter > 0 ? params.armDiameter : 60;
    double armLen = 2500;

    // Mast bracket at specified height
    mast_bracket_params bracketParams;
    bracketParams.boltSpacing = 80;
    bracketParams.boltDiameter = 16;
    bracketParams.height = 150;
    bracketParams.width = 120;
    bracketParams.thickness = 12;
    bracketParams.insulatorBoltSpacing = 60;
    bracketParams.insulatorBoltDiameter = 14;
    bracketParams.mountAngle = 0;
    double bracketH = params.mastHeight * 0.7;
    TopoDS_Shape bracket = create_mast_bracket(
        bracketParams, gp_Pnt(0, 0, bracketH), gp::DX(), gp::DZ());
    result = BRepAlgoAPI_Fuse(result, bracket).Shape();

    // Rod insulator
    rod_insulator_params rodParams;
    rodParams.type = rod_insulator_type::SOLID;
    rodParams.height = 500;
    rodParams.outerDiameter = 80;
    rodParams.innerDiameter = 0;
    rodParams.shedDiameter = 140;
    rodParams.shedSpacing = 60;
    rodParams.shedCount = 6;
    rodParams.endFitting = end_fitting_type::FLANGE;
    rodParams.flangeDiameter = 100;
    rodParams.flangeBoltSpacing = 70;
    rodParams.flangeBoltDiameter = 12;
    TopoDS_Shape insulator =
        create_rod_insulator(rodParams, gp_Pnt(80, 0, bracketH), gp::DX());
    result = BRepAlgoAPI_Fuse(result, insulator).Shape();

    // Level cantilever
    level_cantilever_params levelParams;
    levelParams.length = armLen;
    levelParams.outerDiameter = armDiam;
    levelParams.wallThickness = 4;
    levelParams.mountHeight = bracketH + 80;
    levelParams.riseAngle = 0;
    TopoDS_Shape level = create_level_cantilever(
        levelParams, gp_Pnt(580, 0, bracketH), gp::DX(), gp::DZ());
    result = BRepAlgoAPI_Fuse(result, level).Shape();

    if (params.cantileverType == 2) {
      // Slanted cantilever (double arm)
      slant_cantilever_params slantParams;
      slantParams.length = armLen * 0.9;
      slantParams.outerDiameter = armDiam;
      slantParams.wallThickness = 4;
      slantParams.slantAngle = 45;
      TopoDS_Shape slant = create_slant_cantilever(
          slantParams, gp_Pnt(80, 0, bracketH - 100), gp::DX(), gp::DZ());
      result = BRepAlgoAPI_Fuse(result, slant).Shape();
    }

    // Registration arm at cantilever tip
    registration_arm_params regParams;
    regParams.type = registration_arm_type::STRAIGHT;
    regParams.length = 800;
    regParams.tubeWidth = 30;
    regParams.tubeHeight = 25;
    regParams.wallThickness = 3;
    regParams.angle = 0;
    regParams.isReverse = false;
    TopoDS_Shape regArm = create_registration_arm(
        regParams, gp_Pnt(armLen + 580, params.stagger, bracketH - 200),
        gp::DX(), gp::DZ());
    result = BRepAlgoAPI_Fuse(result, regArm).Shape();
  }

  return result;
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
// TRACK: 31. Switch Rail (尖轨) — tapered from tip to heel
// =========================================================================
// TRACK: 32. Frog (辙叉) — V-shaped crossing
// =========================================================================
TopoDS_Shape create_frog(const frog_params &params) {
    // Frog = 2 point rails (SWITCH ends) + 2 wing rails
    frog_calculated_params fc = calculate_frog_params(params.turnoutNo, params.gauge);
    BRep_Builder bld; TopoDS_Compound cmp; bld.MakeCompound(cmp);
    double halfG = params.gauge / 2;
    // Point rail A (left incoming)
    rail_curve_params rp;
    rp.curve.type = curve_type::LINE;
    rp.curve.startPoint = gp_Pnt(-fc.frogPointLength, -halfG, 0);
    rp.curve.endPoint = gp_Pnt(0, 0, 0);
    rp.railHeight = params.railHeight;
    rp.headWidth = params.railHeadWidth;
    rp.baseWidth = params.railBaseWidth;
    rp.endFinish.type = end_treatment_type::SWITCH;
    rp.endFinish.toeWidth = 2;
    try { bld.Add(cmp, create_rail_curve(rp)); } catch (...) {}
    // Point rail B (right outgoing)
    rp.curve.startPoint = gp_Pnt(0, 0, 0);
    rp.curve.endPoint = gp_Pnt(fc.frogPointLength, halfG, 0);
    rp.endStart.type = end_treatment_type::SWITCH;
    rp.endStart.toeWidth = 2;
    rp.endFinish.type = end_treatment_type::PLANE;
    try { bld.Add(cmp, create_rail_curve(rp)); } catch (...) {}
    // Wing rails
    wing_rail_curve_params wp;
    wp.curve.type = curve_type::LINE;
    wp.curve.startPoint = gp_Pnt(-fc.wingRailLength * 0.4, -halfG - 50, 0);
    wp.curve.endPoint = gp_Pnt(fc.wingRailLength * 0.6, -halfG - 50, 0);
    wp.channelHeight = params.railHeight * 0.7;
    try { bld.Add(cmp, create_wing_rail_curve(wp)); } catch (...) {}
    wp.curve.startPoint = gp_Pnt(-fc.wingRailLength * 0.4, halfG + 50, 0);
    wp.curve.endPoint = gp_Pnt(fc.wingRailLength * 0.6, halfG + 50, 0);
    try { bld.Add(cmp, create_wing_rail_curve(wp)); } catch (...) {}
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
    // Delegated to create_turnout_assembly
    turnout_assembly_params tap;
    tap.turnoutNo = params.turnoutNo;
    tap.hand = params.isLeftHand ? 1 : 2;
    tap.gauge = params.gauge;
    
    frog_calculated_params fc = calculate_frog_params(params.turnoutNo, params.gauge);
    double hg = params.gauge / 2;
    double swLen = params.switchRailLength > 0 ? params.switchRailLength : fc.switchRailLength;
    double leadR = params.leadCurveRadius > 0 ? params.leadCurveRadius : fc.leadCurveRadius;
    double dirSign = params.isLeftHand ? -1.0 : 1.0;
    
    // 1. Stock rails
    rail_curve_params sr;
    sr.curve.type = curve_type::LINE;
    sr.curve.startPoint = gp_Pnt(-swLen - 2000, -hg, 0);
    sr.curve.endPoint = gp_Pnt(fc.frogTotalLength * 1.2, -hg, 0);
    sr.railHeight = params.railHeight; sr.headWidth = params.railHeadWidth;
    sr.baseWidth = params.railBaseWidth; sr.webThickness = params.webThickness;
    tap.rails.push_back(sr);
    sr.curve.startPoint = gp_Pnt(-swLen - 2000, hg, 0);
    sr.curve.endPoint = gp_Pnt(fc.frogTotalLength * 1.2, hg, 0);
    tap.rails.push_back(sr);
    
    // 2. Switch rails (tapered at switch end)
    rail_curve_params sw;
    sw.curve.type = curve_type::LINE;
    sw.curve.startPoint = gp_Pnt(-swLen, -hg, 0);
    sw.curve.endPoint = gp_Pnt(0, -hg, 0);
    sw.endStart.type = end_treatment_type::SWITCH;
    sw.endStart.toeWidth = 2; sw.endStart.switchLength = swLen;
    sw.railHeight = params.railHeight; sw.headWidth = params.railHeadWidth;
    sw.baseWidth = params.railBaseWidth; sw.webThickness = params.webThickness;
    tap.rails.push_back(sw);
    // Curved switch on diverging side
    sw.curve.type = curve_type::ARC;
    sw.curve.startPoint = gp_Pnt(-swLen, hg, 0);
    sw.curve.endPoint = gp_Pnt(0, hg, 0);
    sw.curve.radius = leadR;
    sw.curve.arcDirection = params.isLeftHand ? 1 : 2;
    tap.rails.push_back(sw);
    
    // 3. Sleepers
    int sc = params.sleeperCount;
    for (int i = 0; i < sc; ++i) {
        double t = (double)i / sc;
        double x = -swLen + t * (fc.frogTotalLength * 1.2 + swLen);
        double sl = 2500 + t * 200; // varying length
        sleeper_line_params slp;
        slp.startPoint = gp_Pnt(x, -sl / 2, 0);
        slp.endPoint = gp_Pnt(x, sl / 2, 0);
        slp.width = 260; slp.height = 200; slp.gauge = params.gauge;
        tap.sleepers.push_back(slp);
    }
    
    return create_turnout_assembly(tap);
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
    rail_curve_params rp;
    rp.curve.type = curve_type::LINE;
    rp.curve.startPoint = params.centerline[0];
    rp.curve.endPoint = params.centerline[1];
    rp.railHeight = params.railHeight;
    rp.headWidth = params.railHeadWidth;
    rp.baseWidth = params.railBaseWidth;
    // Left rail
    gp_Trsf lTr; lTr.SetTranslation(gp_Vec(0, -params.gauge / 2, 0));
    rp.curve.startPoint = params.centerline[0].Translated(gp_Vec(0, -params.gauge / 2, 0));
    rp.curve.endPoint = params.centerline[1].Translated(gp_Vec(0, -params.gauge / 2, 0));
    try { bld.Add(cmp, create_rail_curve(rp)); } catch (...) {}
    // Right rail
    rp.curve.startPoint = params.centerline[0].Translated(gp_Vec(0, params.gauge / 2, 0));
    rp.curve.endPoint = params.centerline[1].Translated(gp_Vec(0, params.gauge / 2, 0));
    try { bld.Add(cmp, create_rail_curve(rp)); } catch (...) {}
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
    if (params.centerline.size() < 2) return TopoDS_Shape();
    BRep_Builder bld; TopoDS_Compound cmp; bld.MakeCompound(cmp);
    double totalLen = 0;
    for (size_t i = 0; i < params.centerline.size() - 1; ++i)
        totalLen += params.centerline[i].Distance(params.centerline[i + 1]);
    int count = std::max(1, (int)(totalLen / params.spacing));
    for (int i = 0; i < count; ++i) {
        double t = (double)i / count;
        double d = t * totalLen; double acc = 0;
        gp_Pnt pos;
        for (size_t j = 0; j < params.centerline.size() - 1; ++j) {
            double segL = params.centerline[j].Distance(params.centerline[j + 1]);
            if (acc + segL >= d || j == params.centerline.size() - 2) {
                double lt = segL > 0 ? (d - acc) / segL : 0;
                pos = params.centerline[j].Translated(
                                                      gp_Vec(params.centerline[j+1].XYZ() - params.centerline[j].XYZ()) * lt);
                break;
            }
            acc += segL;
        }
        sleeper_line_params sp;
        sp.startPoint = gp_Pnt(pos.X() - params.length / 2, pos.Y(), pos.Z());
        sp.endPoint = gp_Pnt(pos.X() + params.length / 2, pos.Y(), pos.Z());
        sp.width = params.width;
        sp.height = params.height;
        sp.gauge = params.gauge;
        try { bld.Add(cmp, create_sleeper_line(sp)); } catch (...) {}
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
  
  // Rails
  rail_curve_params rp;
  rp.curve.type = curve_type::LINE;
  rp.curve.startPoint = params.startPoint.Translated(gp_Vec(0, -hg, 0));
  rp.curve.endPoint = params.endPoint.Translated(gp_Vec(0, -hg, 0));
  rp.railHeight = params.railHeight; rp.headWidth = params.railHeadWidth;
  rp.baseWidth = params.railBaseWidth; rp.webThickness = params.webThickness;
  try { bld.Add(cmp, create_rail_curve(rp)); } catch (...) {}
  rp.curve.startPoint = params.startPoint.Translated(gp_Vec(0, hg, 0));
  rp.curve.endPoint = params.endPoint.Translated(gp_Vec(0, hg, 0));
  try { bld.Add(cmp, create_rail_curve(rp)); } catch (...) {}
  
  // Sleepers
  int sc = std::max(2, (int)(len / params.sleeperSpacing));
  for (int i = 0; i < sc; ++i) {
    double t = (double)i / (sc - 1);
    gp_Pnt pos = params.startPoint.Translated(dir * t);
    sleeper_line_params slp;
    slp.startPoint = gp_Pnt(pos.X() - params.sleeperLength / 2, pos.Y(), pos.Z());
    slp.endPoint = gp_Pnt(pos.X() + params.sleeperLength / 2, pos.Y(), pos.Z());
    slp.width = params.sleeperWidth; slp.height = params.sleeperHeight;
    slp.gauge = params.gauge;
    try { bld.Add(cmp, create_sleeper_line(slp)); } catch (...) {}
  }
  
  // Ballast
  ballast_from_sleepers_params bsp;
  for (int i = 0; i < sc; ++i) {
    double t = (double)i / (sc - 1);
    gp_Pnt pos = params.startPoint.Translated(dir * t);
    sleeper_line_params slp;
    slp.startPoint = gp_Pnt(pos.X(), pos.Y() - params.sleeperLength / 2, pos.Z());
    slp.endPoint = gp_Pnt(pos.X(), pos.Y() + params.sleeperLength / 2, pos.Z());
    bsp.sleepers.push_back(slp);
  }
  bsp.topWidth = params.ballastTopWidth;
  bsp.thickness = params.ballastThickness;
  bsp.sideSlope = params.ballastSlope;
  try { bld.Add(cmp, create_ballast_from_sleepers(bsp)); } catch (...) {}
  
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
  rp.curve.type = curve_type::ARC;
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
    try { bld.Add(cmp, create_rail_curve(rp)); } catch (...) {}
  }
  
  // Sleepers (radially arranged)
  double arcLen = fabs(sweep) * R;
  int sc = std::max(2, (int)(arcLen / params.sleeperSpacing));
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
    try { bld.Add(cmp, create_sleeper_line(slp)); } catch (...) {}
  }
  
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
// Switch Rail (尖轨) — delegated to create_rail_curve + end_treatment
// =========================================================================
TopoDS_Shape create_switch_rail(const switch_rail_params &params) {
  rail_curve_params rp;
  rp.curve.type = params.curveRadius > Precision::Confusion() ? curve_type::ARC : curve_type::LINE;
  rp.curve.startPoint = gp::Origin();
  rp.curve.endPoint = gp_Pnt(params.length, 0, 0);
  if (rp.curve.type == curve_type::ARC) {
    rp.curve.radius = params.curveRadius;
    rp.curve.arcDirection = params.isLeftHand ? 2 : 1;
  }
  rp.railHeight = params.railHeight;
  rp.headWidth = params.railHeadWidth;
  rp.baseWidth = params.railBaseWidth;
  rp.webThickness = params.webThickness;
  rp.endStart.type = end_treatment_type::SWITCH;
  rp.endStart.toeWidth = params.tipWidth;
  return create_rail_curve(rp);
}

TopoDS_Shape create_switch_rail(const switch_rail_params &params,
                                 const gp_Pnt &position,
                                 const gp_Dir &direction,
                                 const gp_Dir &upDir) {
  TopoDS_Shape shape = create_switch_rail(params);
  gp_Ax3 src(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 tgt(position, upDir, direction);
  gp_Trsf tr; tr.SetTransformation(tgt, src);
  return BRepBuilderAPI_Transform(shape, tr).Shape();
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
  BRep_Builder b; TopoDS_Compound c; b.MakeCompound(c);
  double bw2 = bWidth / 2;
  b.Add(c, BRepAlgoAPI_Cut(
    BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(-bw2, 0, 0), gp::DX()), R + bThick, bWidth).Shape(),
    BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(-bw2, 0, 0), gp::DX()), R, bWidth + 2).Shape()).Shape());
  b.Add(c, BRepPrimAPI_MakeBox(gp_Pnt(-bThick / 2, -bkW / 2, -R - bkH), bThick, bkW, bkH).Shape());
  if (params.mountHoleDiameter > 0) {
    double br = params.mountHoleDiameter / 2.0;
    double bz = -R - bkH * 0.85;
    b.Add(c, BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(-bThick / 2 - br * 0.3, 0, bz), gp::DX()), br, bThick + br * 0.6).Shape());
  }
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
  case curve_type::LINE:
    w.Add(makeEdgeSafe(curve.startPoint, curve.endPoint));
    break;
  case curve_type::ARC: {
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
  case curve_type::BEZIER: {
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

TopoDS_Face buildRailProfile(double railHeight, double headWidth,
                              double baseWidth, double webThickness,
                              double headHeight, double baseHeight,
                              double headRadius) {
  double hh = headHeight > 0 ? headHeight : railHeight * 0.3;
  double bh = baseHeight > 0 ? baseHeight : railHeight * 0.15;
  double hw = headWidth / 2.0, bw = baseWidth / 2.0, wt = webThickness / 2.0;
  double hr = headRadius > 0 ? headRadius : 13.0;
  double zw = bh, zt = railHeight - hh, zTop = railHeight;
  BRepBuilderAPI_MakeWire w;
  w.Add(makeEdgeSafe(gp_Pnt(0, -bw, 0), gp_Pnt(0, -bw, zw)));
  w.Add(makeEdgeSafe(gp_Pnt(0, -bw, zw), gp_Pnt(0, -wt, zw)));
  w.Add(makeEdgeSafe(gp_Pnt(0, -wt, zw), gp_Pnt(0, -wt, zt)));
  w.Add(makeEdgeSafe(gp_Pnt(0, -wt, zt), gp_Pnt(0, -hw, zt)));
  w.Add(makeEdgeSafe(gp_Pnt(0, -hw, zt), gp_Pnt(0, -hw, zTop - hr)));
  gp_Circ arcL(gp_Ax2(gp_Pnt(0, -hw + hr, zTop - hr), gp_Dir(1, 0, 0)), hr);
  w.Add(BRepBuilderAPI_MakeEdge(GC_MakeArcOfCircle(arcL, M_PI / 2, M_PI, false).Value()).Edge());
  gp_Circ arcR(gp_Ax2(gp_Pnt(0, hw - hr, zTop - hr), gp_Dir(1, 0, 0)), hr);
  w.Add(BRepBuilderAPI_MakeEdge(GC_MakeArcOfCircle(arcR, 0, M_PI / 2, false).Value()).Edge());
  w.Add(makeEdgeSafe(gp_Pnt(0, hw, zTop - hr), gp_Pnt(0, hw, zt)));
  w.Add(makeEdgeSafe(gp_Pnt(0, hw, zt), gp_Pnt(0, wt, zt)));
  w.Add(makeEdgeSafe(gp_Pnt(0, wt, zt), gp_Pnt(0, wt, zw)));
  w.Add(makeEdgeSafe(gp_Pnt(0, wt, zw), gp_Pnt(0, bw, zw)));
  w.Add(makeEdgeSafe(gp_Pnt(0, bw, zw), gp_Pnt(0, bw, 0)));
  w.Add(makeEdgeSafe(gp_Pnt(0, bw, 0), gp_Pnt(0, -bw, 0)));
  ShapeFix_Wire fx; fx.Load(w.Wire()); fx.Perform();
  return BRepLib_MakeFace(fx.Wire()).Face();
}

TopoDS_Face buildChannelProfile(double height, double flangeWidth, double webThickness) {
  double hw = webThickness / 2.0, fw = flangeWidth;
  BRepBuilderAPI_MakeWire w;
  w.Add(makeEdgeSafe(gp_Pnt(0, -fw, 0), gp_Pnt(0, -fw, height)));
  w.Add(makeEdgeSafe(gp_Pnt(0, -fw, height), gp_Pnt(0, -hw, height)));
  w.Add(makeEdgeSafe(gp_Pnt(0, -hw, height), gp_Pnt(0, hw, height)));
  w.Add(makeEdgeSafe(gp_Pnt(0, hw, height), gp_Pnt(0, fw, height)));
  w.Add(makeEdgeSafe(gp_Pnt(0, fw, height), gp_Pnt(0, fw, 0)));
  w.Add(makeEdgeSafe(gp_Pnt(0, fw, 0), gp_Pnt(0, -fw, 0)));
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
  TopoDS_Wire wire = buildCurveWire(curve);
  BRepOffsetAPI_MakePipeShell pipe(wire);
  pipe.Add(face);
  pipe.SetMode(Standard_True);
  pipe.Build();
  if (!pipe.IsDone()) throw Standard_ConstructionError("sweep failed");
  return pipe.Shape();
}

TopoDS_Shape applyEndTreatment(const TopoDS_Shape &shape,
                                const end_treatment_params &t,
                                const curve_params &curve, bool isStart) {
  if (t.type == end_treatment_type::PLANE) return shape;
  if (t.type == end_treatment_type::SCARF) {
    gp_Pnt pt = isStart ? curve.startPoint : curve.endPoint;
    gp_Vec dir(curve.startPoint, curve.endPoint);
    double len = dir.Magnitude();
    if (len < Precision::Confusion()) return shape;
    double a = t.scarfAngle * M_PI / 180.0;
    gp_Dir cd = isStart ? gp_Dir(dir).Rotated(gp_Ax1(pt, gp_Dir(0, 1, 0)), a)
                       : gp_Dir(dir).Rotated(gp_Ax1(pt, gp_Dir(0, 1, 0)), -a);
    TopoDS_Shape r = shape;
    return r.IsNull() ? shape : r;
  }
  if (t.type == end_treatment_type::BELL) {
    double bl = t.bellLength;
    if (bl < 1) return shape;
    gp_Pnt c = isStart ? curve.startPoint : curve.endPoint;
    gp_Vec d(curve.startPoint, curve.endPoint);
    gp_Dir ax(d);
    gp_Dir perp(0, 1, 0);
    if (std::abs(ax.Dot(perp)) > 0.9) perp = gp_Dir(1, 0, 0);
    gp_Vec axv(ax.XYZ()), perpv(perp.XYZ());
    gp_Pnt o = isStart ? c.Translated(-axv * bl - perpv * 30) : c.Translated(-perpv * 30);
    TopoDS_Shape b = BRepPrimAPI_MakeBox(o, bl, 60, 60).Shape();
    return BRepAlgoAPI_Fuse(shape, b).Shape();
  }
  return shape;
}

} // anonymous namespace

// =========================================================================
// 钢轨（独立曲线）
// =========================================================================
TopoDS_Shape create_rail_curve(const rail_curve_params &params) {
  TopoDS_Face face = buildRailProfile(params.railHeight, params.headWidth,
                                       params.baseWidth, params.webThickness,
                                       params.headHeight, params.baseHeight,
                                       params.headRadius);
  TopoDS_Shape shape = sweepProfile(face, params.curve);
  shape = applyEndTreatment(shape, params.endStart, params.curve, true);
  shape = applyEndTreatment(shape, params.endFinish, params.curve, false);
  return shape;
}

// =========================================================================
// 翼轨（独立曲线）
// =========================================================================
TopoDS_Shape create_wing_rail_curve(const wing_rail_curve_params &params) {
  TopoDS_Face face;
  if (params.profile == profile_type::RAIL)
    face = buildRailProfile(120, 50, 100, 12, 40, 20, 10);
  else
    face = buildChannelProfile(params.channelHeight, params.flangeWidth, params.webThickness);
  TopoDS_Shape shape = sweepProfile(face, params.curve);
  shape = applyEndTreatment(shape, params.endStart, params.curve, true);
  shape = applyEndTreatment(shape, params.endFinish, params.curve, false);
  return shape;
}

// =========================================================================
// 护轨（独立曲线）
// =========================================================================
TopoDS_Shape create_guard_rail_curve(const guard_rail_curve_params &params) {
  TopoDS_Face face = buildChannelProfile(params.channelHeight, params.flangeWidth, params.webThickness);
  TopoDS_Shape shape = sweepProfile(face, params.curve);
  shape = applyEndTreatment(shape, params.endStart, params.curve, true);
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
    } catch (...) {}
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
// 扣件（点）
// =========================================================================
TopoDS_Shape create_fastener_point(const fastener_point_params &params) {
  BRep_Builder bld; TopoDS_Compound cmp; bld.MakeCompound(cmp);
  auto addAt = [&](double yOff) {
    gp_Pnt p(params.position.X(), params.position.Y() + yOff, params.position.Z());
    TopoDS_Shape pad = BRepPrimAPI_MakeBox(gp_Pnt(p.X() - 75, p.Y() - 60, p.Z()), 150, 120, params.padThickness).Shape();
    for (int bx = -1; bx <= 1; bx += 2)
      for (int by = -1; by <= 1; by += 2) {
        TopoDS_Shape h = BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(p.X() + bx * 40, p.Y() + by * 35, p.Z() - 1), gp::DZ()), 6, params.padThickness + 2).Shape();
        pad = BRepAlgoAPI_Cut(pad, h).Shape();
      }
    bld.Add(cmp, pad);
    TopoDS_Shape clip = BRepPrimAPI_MakeBox(gp_Pnt(p.X() - 15, p.Y() - 10, p.Z() + params.padThickness), 30, 20, 30).Shape();
    bld.Add(cmp, clip);
  };
  if (params.side == 3 || params.side == 1) addAt(-751.5);
  if (params.side == 3 || params.side == 2) addAt(751.5);
  return cmp;
}

// =========================================================================
// 减速顶（点）
// =========================================================================
TopoDS_Shape create_retarder_point(const retarder_point_params &params) {
  gp_Pnt p = params.position;
  TopoDS_Shape body = BRepPrimAPI_MakeBox(gp_Pnt(p.X() - params.length / 2, p.Y() - params.width / 2, p.Z()), params.length, params.width, params.height).Shape();
  if (params.type == 1) {
    TopoDS_Shape pist = BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(p.X(), p.Y(), p.Z() + params.height), gp::DZ()), params.width * 0.3, params.height * 0.3).Shape();
    body = BRepAlgoAPI_Fuse(body, pist).Shape();
  }
  return body;
}

// =========================================================================
// 道床（由枕木线驱动）
// =========================================================================
TopoDS_Shape create_ballast_from_sleepers(const ballast_from_sleepers_params &params) {
  if (params.sleepers.empty()) throw Standard_ConstructionError("ballast: no sleepers");
  double minX = 1e38, maxX = -1e38, minY = 1e38, maxY = -1e38, sz = 0;
  for (auto &sl : params.sleepers) {
    minX = std::min({minX, sl.startPoint.X(), sl.endPoint.X()});
    maxX = std::max({maxX, sl.startPoint.X(), sl.endPoint.X()});
    minY = std::min({minY, sl.startPoint.Y(), sl.endPoint.Y()});
    maxY = std::max({maxY, sl.startPoint.Y(), sl.endPoint.Y()});
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
  for (auto &r : params.rails)      try { bld.Add(cmp, create_rail_curve(r)); } catch (...) {}
  for (auto &w : params.wingRails)  try { bld.Add(cmp, create_wing_rail_curve(w)); } catch (...) {}
  for (auto &g : params.guardRails) try { bld.Add(cmp, create_guard_rail_curve(g)); } catch (...) {}
  for (auto &s : params.sleepers)   try { bld.Add(cmp, create_sleeper_line(s)); } catch (...) {}
  for (auto &f : params.fasteners)  try {
    fastener_point_params fp; fp.position = f.position; fp.side = f.side; fp.padThickness = f.padThickness;
    bld.Add(cmp, create_fastener_point(fp));
  } catch (...) {}
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

// =========================================================================
// 钢轨伸缩调节器
// =========================================================================
TopoDS_Shape create_expansion_joint(const expansion_joint_params &params) {
  BRep_Builder bld; TopoDS_Compound cmp; bld.MakeCompound(cmp);
  try { bld.Add(cmp, create_rail_curve(params.stockRail)); } catch (...) {}
  try { bld.Add(cmp, create_rail_curve(params.switchRail)); } catch (...) {}
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
