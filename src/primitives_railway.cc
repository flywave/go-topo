#include "primitives_railway.hh"

#include <cmath>
#include <BRepAlgoAPI_Cut.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_MakePolygon.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_Transform.hxx>
#include <BRepFilletAPI_MakeFillet.hxx>
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
#include <BRepLib_MakeFace.hxx>
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
  double beamBottomZ = CH + SH;  // 横梁底部高度 = 导高 + 结构高度
  double cantileverSystemMargin = 800.0;  // 腕臂系统最小占用高度

  out.contactWireZ = CH;
  out.messengerWireZ = CH + SH;
  out.beamBottomZ = beamBottomZ;

  // 校验高度约束
  if (MH < beamBottomZ + cantileverSystemMargin) {
    out.totalLength = 0; out.mastCount = 0;
    return out;  // 柱高不足
  }

  // 沿中心线计算总弧长
  double totalLen = 0;
  std::vector<double> segLens;
  for (size_t i = 0; i < input.centerline.size() - 1; ++i) {
    double d = input.centerline[i].Distance(input.centerline[i+1]);
    segLens.push_back(d); totalLen += d;
  }
  out.totalLength = totalLen;
  out.mastCount = std::max(2, (int)(totalLen / spanLen) + 1);

  // 沿中心线等距采样柱位
  double mastSpacing = totalLen / (out.mastCount - 1);
  int staggerCount = (int)input.staggerTable.size();

  for (int m = 0; m < out.mastCount; ++ m) {
    double dist = m * mastSpacing;
    // 插值获取柱位坐标
    gp_Pnt pos; double acc = 0;
    for (size_t j = 0; j < segLens.size(); ++j) {
      if (acc + segLens[j] >= dist || j == segLens.size() - 1) {
        double t = segLens[j] > 0 ? (dist - acc) / segLens[j] : 0;
        pos = input.centerline[j].Translated(
            gp_Vec(input.centerline[j+1].XYZ() - input.centerline[j].XYZ()) * t);
        break;
      }
      acc += segLens[j];
    }

    OcsMastPosition mp;
    mp.mileage = dist / 1000.0;  // m
    mp.position = pos;
    mp.mastHeight = MH;
    mp.beamBottomZ = beamBottomZ;
    mp.contactWireZ = CH;
    mp.messengerWireZ = CH + SH;
    mp.stagger = (m < staggerCount) ? input.staggerTable[m] : 0;
    mp.hangerPostLength = MH - beamBottomZ - cantileverSystemMargin * 0.5;
    mp.bracketMountZ = beamBottomZ - 100;    // 腕臂底座低于横梁底部
    mp.insulatorMountZ = mp.bracketMountZ - 500; // 绝缘子 500mm
    mp.registrationArmZ = CH;                 // 定位器在接触线高度
    mp.isTensionMast = (input.hasCompensator && (m == 0 || m == out.mastCount - 1));
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
  const double bR =
      params.bottomRadius > 0 ? params.bottomRadius : R * 0.6;
  const double tR = params.topRadius > 0 ? params.topRadius : 3.0;

  // Build profile points (YZ plane, centered on X axis)
  // Starting from bottom center, going clockwise
  double bottomArcCenterY = 0;
  double bottomArcCenterZ = bR;

  // Key profile points
  gp_Pnt p0(0, -R, 0);                          // bottom-left
  gp_Pnt p1(0, -R + gD, -gW / 2);               // groove bottom-left
  gp_Pnt p2(0, -R + gD, gW / 2);                // groove bottom-right
  gp_Pnt p3(0, -R + gD + (h - 2 * bR), gW / 2); // shoulder-right
  gp_Pnt p4(0, -R + gD + (h - 2 * bR), -gW / 2); // shoulder-left
  gp_Pnt p5(0, -R, h);                           // top-left

  // Bottom arc
  gp_Circ bottomArc(
      gp_Ax2(gp_Pnt(0, 0, bR), gp_Dir(1, 0, 0)),
      bR);
  Handle(Geom_TrimmedCurve) bottomArcCurve =
      GC_MakeArcOfCircle(bottomArc, -M_PI / 2, M_PI / 2, false).Value();

  TopoDS_Edge bottomArcEdge = BRepBuilderAPI_MakeEdge(bottomArcCurve).Edge();
  TopoDS_Edge e1 = BRepBuilderAPI_MakeEdge(p0, p1).Edge();
  TopoDS_Edge e2 = BRepBuilderAPI_MakeEdge(p1, p2).Edge();
  TopoDS_Edge e3 = BRepBuilderAPI_MakeEdge(p2, p3).Edge();
  TopoDS_Edge e4 = BRepBuilderAPI_MakeEdge(p3, p4).Edge();
  TopoDS_Edge e5 = BRepBuilderAPI_MakeEdge(p4, p5).Edge();

  // Top semi-circle for clamping area
  gp_Circ topArc(
      gp_Ax2(gp_Pnt(0, -R + h - tR, -tR), gp_Dir(0, 0, 1)),
      tR);
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

  BRep_Builder builder; TopoDS_Compound compound; builder.MakeCompound(compound);

  double BL = params.beamLength, BH = params.beamHeight, BW = params.beamWidth;
  double gap = params.beamSpacing > 0 ? params.beamSpacing : BH * 3;

  // Upper beam — along Y (perpendicular to track)
  gp_Pnt ubOrg(0, -BL/2, gap + BH/2);
  TopoDS_Shape upperBeam = BRepPrimAPI_MakeBox(ubOrg, BW, BL, BH).Shape();
  builder.Add(compound, upperBeam);

  // Lower beam
  gp_Pnt lbOrg(0, -BL/2, -BH/2);
  TopoDS_Shape lowerBeam = BRepPrimAPI_MakeBox(lbOrg, BW, BL, BH).Shape();
  builder.Add(compound, lowerBeam);

  // Two diagonal braces — cross at center (定交点固定于立柱)
  double braceR = BW * 0.25;
  for (int side = -1; side <= 1; side += 2) {
    gp_Pnt p1(0, side * BL * 0.45, gap + BH);
    gp_Pnt p2(0, -side * BL * 0.45, 0);
    gp_Vec v(p1, p2); double l = v.Magnitude();
    if (l > Precision::Confusion())
      builder.Add(compound, BRepPrimAPI_MakeCylinder(gp_Ax2(p1, gp_Dir(v)), braceR, l).Shape());
  }

  // Bolt holes in beams for mast connection at center
  if (params.boltDiameter > 0) {
    double hr = params.boltDiameter / 2, hs = params.boltSpacing / 2;
    for (int level = 0; level < 2; ++level) {
      double z = (level == 0) ? BH/2 : gap + BH + BH/2;
      for (int bx = -1; bx <= 1; bx += 2) if (params.boltCount >= 3 || bx == 0)
        for (int by = -1; by <= 1; by += 2) {
          TopoDS_Shape h = BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(bx*hs, by*hs, z - BW/2 - 1), gp::DY()), hr, BW+2).Shape();
          lowerBeam = BRepAlgoAPI_Cut(lowerBeam, h).Shape();
          upperBeam = BRepAlgoAPI_Cut(upperBeam, h).Shape();
        }
    }
  }

  return compound;
}

TopoDS_Shape create_cross_arm(const cross_arm_params &params,
                              const gp_Pnt &position,
                              const gp_Dir &normal,
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
  if (params.wallThickness <= 0 || params.wallThickness >= params.outerDiameter / 2)
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
  if (params.wallThickness <= 0 || params.wallThickness >= params.outerDiameter / 2)
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
      params.bendRadius > 0 ? params.bendRadius
                            : std::min(params.verticalLength,
                                       params.horizontalLength) * 0.3;
  double V = params.verticalLength;
  double H = params.horizontalLength;

  if (R > V || R > H)
    R = std::min(V, H) * 0.5;

  // Build centerline path: vertical straight + quarter-circle arc + horizontal straight
  // Arc center: (R, 0, V-R), quarter turn from Z-direction to X-direction
  gp_Pnt arcCenter(R, 0, V - R);

  // Vertical segment: from origin to arc start point (0, 0, V-R)
  gp_Pnt vStart(0, 0, 0);
  gp_Pnt arcStart(0, 0, V - R);

  // Quarter-circle arc (in XZ plane, from left to top of center)
  // At parameter 0: arcCenter + (R*cos(0), 0, R*sin(0)) = (R+R, 0, V-R) — right side
  // At parameter pi/2: arcCenter + (R*cos(pi/2), 0, R*sin(pi/2)) = (R, 0, V) — top
  // At parameter pi: arcCenter + (R*cos(pi), 0, R*sin(pi)) = (0, 0, V-R) — left side
  // Arc from pi to pi/2: quarter turn left-to-top (Z-vertical to X-horizontal)
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
    gp_Pnt flangeOrigin(-flangeSize / 2, -flangeSize / 2, -params.flangeThickness);
    TopoDS_Shape flange =
        BRepPrimAPI_MakeBox(flangeOrigin, flangeSize, flangeSize,
                              params.flangeThickness)
            .Shape();
    arm = BRepAlgoAPI_Fuse(arm, flange).Shape();
  }

  return arm;
}

TopoDS_Shape create_curved_arm(const curved_arm_params &params,
                               const gp_Pnt &position,
                               const gp_Dir &normal,
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

  if (params.shedCount == 0) return rod;

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
  if (params.endFitting == end_fitting_type::FLANGE && params.flangeDiameter > rodRadius * 2) {
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
  TopoDS_Shape plate =
      BRepPrimAPI_MakeBox(plateOrg, params.thickness, params.width,
                            params.height).Shape();
  builder.Add(compound, plate);

  // Mounting bolt holes
  if (params.boltDiameter > 0 && params.boltSpacing > 0) {
    double hs = params.boltSpacing / 2.0;
    double midZ = params.height / 2.0;
    double holeR = params.boltDiameter / 2.0;
    gp_Pnt hc[4] = {{0, -hs, midZ - hs}, {0, hs, midZ - hs},
                     {0, -hs, midZ + hs}, {0, hs, midZ + hs}};
    for (auto &c : hc) {
      TopoDS_Shape hole =
          BRepPrimAPI_MakeCylinder(gp_Ax2(c, gp::DX()), holeR, params.thickness + 2).Shape();
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
      TopoDS_Shape ear =
          BRepPrimAPI_MakeBox(earOrg, eT, eW, eH).Shape();
      plate = BRepAlgoAPI_Fuse(plate, ear).Shape();

      // Ear pin hole
      if (params.insulatorBoltDiameter > 0) {
        double hr = params.insulatorBoltDiameter / 2.0;
        double hz = params.height / 2.0;
        TopoDS_Shape hole =
            BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(eOff, params.width / 2.0, hz), gp::DY()),
                                      hr, eW + 2).Shape();
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
    gp_Pnt rp2(-params.thickness / 2.0 - ribW, y, params.height / 2.0 - ribH / 2.0);
    gp_Pnt rp3(-params.thickness / 2.0 - ribW, y, params.height / 2.0 + ribH / 2.0);
    TopoDS_Wire rw = BRepBuilderAPI_MakePolygon(rp1, rp2, rp3, Standard_True).Wire();
    TopoDS_Face rf = BRepLib_MakeFace(rw).Face();
    TopoDS_Shape rib = BRepPrimAPI_MakePrism(rf, gp_Vec(0, -side * ribThick, 0)).Shape();
    plate = BRepAlgoAPI_Fuse(plate, rib).Shape();
  }

  // Apply mount angle
  if (std::abs(params.mountAngle) > Precision::Angular()) {
    double a = params.mountAngle * M_PI / 180.0;
    gp_Trsf rot;
    rot.SetRotation(gp_Ax1(gp_Pnt(0, params.width / 2.0, params.height / 2.0), gp::DY()), a);
    plate = BRepBuilderAPI_Transform(plate, rot).Shape();
  }

  return plate;
}

TopoDS_Shape create_mast_bracket(const mast_bracket_params &params,
                                 const gp_Pnt &position,
                                 const gp_Dir &normal,
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

  double W = params.tubeWidth, H = params.tubeHeight > 0 ? params.tubeHeight : W;
  double t = params.wallThickness > 0 ? params.wallThickness : W * 0.15;
  double L = params.length;
  double dir = params.isReverse ? -1.0 : 1.0;

  auto makeTube = [&](gp_Pnt org, gp_Dir axis, double len) -> TopoDS_Shape {
    gp_Pnt outerOrg(org.X() - W/2, org.Y() - H/2, org.Z() - W/2);
    TopoDS_Shape outer = BRepPrimAPI_MakeBox(outerOrg, W, H, W).Shape();
    if (t > 0 && W > 2*t && H > 2*t) {
      TopoDS_Shape inner = BRepPrimAPI_MakeBox(gp_Pnt(org.X()-W/2+t, org.Y()-H/2+t, org.Z()-W/2-1), W-2*t, H-2*t, W+2).Shape();
      outer = BRepAlgoAPI_Cut(outer, inner).Shape();
    }
    // Align along axis, extrude to length
    gp_Ax3 srcAx(org, gp::DZ(), gp::DX());
    gp_Dir yDir = gp::DZ().Crossed(axis);
    gp_Ax3 tgtAx(org, axis, gp_Dir(0,0,1));
    gp_Trsf tr; tr.SetTransformation(tgtAx, srcAx);
    return BRepBuilderAPI_Transform(outer, tr).Shape();
  };

  TopoDS_Shape tube;
  double totalL = (params.type == registration_arm_type::EXTENDED) ? L * 1.3 : L;

  if (params.type == registration_arm_type::STRAIGHT ||
      params.type == registration_arm_type::EXTENDED) {
    // Tube along X: width in Y, height in Z
    TopoDS_Shape outer = BRepPrimAPI_MakeBox(gp_Pnt(0, -W/2, -H/2), totalL, W, H).Shape();
    if (t > 0 && W > 2*t && H > 2*t) {
      TopoDS_Shape inner = BRepPrimAPI_MakeBox(gp_Pnt(-1, -W/2+t, -H/2+t), totalL+2, W-2*t, H-2*t).Shape();
      tube = BRepAlgoAPI_Cut(outer, inner).Shape();
    } else tube = outer;
  } else {
    // Curved type: single continuous sweep — straight + arc transition + curved tip
    double straightLen = L * 0.7, curveLen = L * 0.3;
    gp_Pnt p0(0, 0, 0), p1(straightLen, 0, 0);
    gp_Pnt p2(straightLen + curveLen * 0.5, 0, -curveLen * 0.1);
    gp_Pnt p3(straightLen + curveLen, 0, -curveLen * 0.2);

    // Build single path: line + Bezier
    BRepBuilderAPI_MakeWire pathWire;
    pathWire.Add(BRepBuilderAPI_MakeEdge(p0, p1));  // straight segment
    Handle(TColgp_HArray1OfPnt) bzp = new TColgp_HArray1OfPnt(1, 3);
    bzp->SetValue(1, p1); bzp->SetValue(2, p2); bzp->SetValue(3, p3);
    pathWire.Add(BRepBuilderAPI_MakeEdge(new Geom_BezierCurve(bzp->Array1())));

    // Square section in YZ plane at start
    gp_Pnt s1(0, -W/2, -H/2), s2(0, W/2, -H/2), s3(0, W/2, H/2), s4(0, -W/2, H/2);
    TopoDS_Wire sqWire = BRepBuilderAPI_MakePolygon(s1, s2, s3, s4, Standard_True).Wire();

    BRepOffsetAPI_MakePipeShell pipe(pathWire.Wire());
    pipe.Add(sqWire);
    pipe.SetMode(Standard_True);
    pipe.Build();
    if (pipe.IsDone() && pipe.MakeSolid()) tube = pipe.Shape();
  }


  // Base end: joint plate + L-flange toward band
  double jointSize = std::max(W, H) * 1.2;
  double jThick = W * 0.6;
  double jY = jointSize/6, jW = jointSize/3, jZ = jointSize*1.8, jH = jointSize*2;
  gp_Pnt jOrg(-jThick/2, -jY, -jZ);
  TopoDS_Shape joint = BRepPrimAPI_MakeBox(jOrg, jThick, jW, jH).Shape();
  tube = BRepAlgoAPI_Fuse(tube, joint).Shape();

  // L-flange — short tab in XZ, 90° to joint
  double fLen = jThick * 1.5, fH = jThick * 0.8;
  gp_Pnt fOrg(-jThick/2 - fLen, -jThick/2, -jZ - fH);
  TopoDS_Shape flange = BRepPrimAPI_MakeBox(fOrg, fLen + jThick, jThick, fH).Shape();
  tube = BRepAlgoAPI_Fuse(tube, flange).Shape();

  // Front end: wire clamp — top flush with tube top, extends downward
  double clampW = W * 1.2, clampH = H * 2, cThick = W * 0.6;
  double clampX = totalL;
  double tubeTopZ = (params.type == registration_arm_type::CURVED) ? -(L * 0.3 * 0.2) + H/2 : H/2;
  // Clamp hangs down from tube top
  gp_Pnt cOrg(clampX, -clampW/2, tubeTopZ - clampH);
  TopoDS_Shape clamp = BRepPrimAPI_MakeBox(cOrg, cThick, clampW, clampH).Shape();

  // Wire groove at clamp bottom
  double gr = W * 0.35;
  gp_Ax2 ga(gp_Pnt(clampX + cThick/2, -clampW/2, tubeTopZ - clampH), gp::DY());
  clamp = BRepAlgoAPI_Cut(clamp, BRepPrimAPI_MakeCylinder(ga, gr, clampW).Shape()).Shape();

  // Bolts at mid-clamp
  double br = W * 0.09, boltLen = cThick + W * 0.15;
  for (int side = -1; side <= 1; side += 2) {
    double by = side * clampW * 0.35;
    TopoDS_Shape bolt = BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(clampX - 1, by, tubeTopZ - clampH/2), gp::DX()), br, boltLen).Shape();
    clamp = BRepAlgoAPI_Fuse(clamp, bolt).Shape();
  }
  tube = BRepAlgoAPI_Fuse(tube, clamp).Shape();

  if (std::abs(params.angle) > Precision::Angular()) {
    double ar = params.angle * M_PI / 180.0;
    gp_Trsf rot; rot.SetRotation(gp_Ax1(gp::Origin(), gp::DY()), ar);
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
  rot.SetRotation(gp_Ax1(gp::Origin(), gp::DY()),
                  M_PI / 2 - angleRad);
  return BRepBuilderAPI_Transform(wire, rot).Shape();
}

TopoDS_Shape create_guy_wire(const guy_wire_params &params,
                             const gp_Pnt &anchorPoint,
                             const gp_Pnt &mastPoint,
                             const gp_Dir &upDir) {
  // Calculate direction and length from anchor to mast point
  gp_Vec vec(anchorPoint, mastPoint);
  double len = vec.Magnitude();
  if (len <= Precision::Confusion())
    throw Standard_ConstructionError("Anchor and mast points must differ");

  // Create wire segment directly along the vector
  double radius = params.diameter / 2;
  gp_Ax2 wireAxis(anchorPoint, gp_Dir(vec));
  TopoDS_Shape wire =
      BRepPrimAPI_MakeCylinder(wireAxis, radius, len).Shape();

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
TopoDS_Wire makeAngleSteelProfile(double legLong, double legShort, double thick) {
  BRepBuilderAPI_MakeWire w;
  // L-shape in the XY plane: origin at the outer corner
  // Long leg along +Y, short leg along +X
  w.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(0, 0, 0), gp_Pnt(0, legLong, 0)));
  w.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(0, legLong, 0), gp_Pnt(thick, legLong, 0)));
  w.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(thick, legLong, 0), gp_Pnt(thick, legShort, 0)));
  w.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(thick, legShort, 0), gp_Pnt(0, 0, 0)));
  return w.Wire();
}

} // anonymous namespace

TopoDS_Shape create_steel_mast(const steel_mast_params &params) {
  if (params.height <= 0 || params.bottomWidth <= 0)
    throw Standard_ConstructionError("Height and bottom width must be positive");

  BRep_Builder builder;
  TopoDS_Compound compound;
  builder.MakeCompound(compound);

  const double H = params.height;
  const double B = params.bottomWidth;    // bottom outer width between leg centers
  const double T = params.topWidth > 0 ? params.topWidth : B * 0.6;
  const double L = params.wallThickness;  // plate/steel thickness

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
      gp_Pnt webBt[4] = {{-L/2, -hw0+fT, z0}, {L/2, -hw0+fT, z0},
                          {L/2, hw0-fT, z0}, {-L/2, hw0-fT, z0}};
      TopoDS_Wire webBw = BRepBuilderAPI_MakePolygon(webBt[0], webBt[1], webBt[2], webBt[3], Standard_True).Wire();
      gp_Pnt webTt[4] = {{-L/2, -hw1+fT, z0+segH}, {L/2, -hw1+fT, z0+segH},
                          {L/2, hw1-fT, z0+segH}, {-L/2, hw1-fT, z0+segH}};
      TopoDS_Wire webTw = BRepBuilderAPI_MakePolygon(webTt[0], webTt[1], webTt[2], webTt[3], Standard_True).Wire();
      BRepOffsetAPI_ThruSections webThru(Standard_True);
      webThru.AddWire(webBw); webThru.AddWire(webTw); webThru.Build();

      // Left flange: wide plate in X, spanning from -hw0 to hw0, Y=-hw0 to -hw0+fT
      gp_Pnt lfBt[4] = {{-hw0, -hw0, z0}, {hw0, -hw0, z0},
                         {hw0, -hw0+fT, z0}, {-hw0, -hw0+fT, z0}};
      TopoDS_Wire lfBw = BRepBuilderAPI_MakePolygon(lfBt[0], lfBt[1], lfBt[2], lfBt[3], Standard_True).Wire();
      gp_Pnt lfTt[4] = {{-hw1, -hw1, z0+segH}, {hw1, -hw1, z0+segH},
                         {hw1, -hw1+fT, z0+segH}, {-hw1, -hw1+fT, z0+segH}};
      TopoDS_Wire lfTw = BRepBuilderAPI_MakePolygon(lfTt[0], lfTt[1], lfTt[2], lfTt[3], Standard_True).Wire();
      BRepOffsetAPI_ThruSections lfThru(Standard_True);
      lfThru.AddWire(lfBw); lfThru.AddWire(lfTw); lfThru.Build();

      // Right flange: wide plate, Y from hw0-fT to hw0, X from -hw0 to hw0
      gp_Pnt rfBt[4] = {{-hw0, hw0-fT, z0}, {hw0, hw0-fT, z0},
                         {hw0, hw0, z0}, {-hw0, hw0, z0}};
      TopoDS_Wire rfBw = BRepBuilderAPI_MakePolygon(rfBt[0], rfBt[1], rfBt[2], rfBt[3], Standard_True).Wire();
      gp_Pnt rfTt[4] = {{-hw1, hw1-fT, z0+segH}, {hw1, hw1-fT, z0+segH},
                         {hw1, hw1, z0+segH}, {-hw1, hw1, z0+segH}};
      TopoDS_Wire rfTw = BRepBuilderAPI_MakePolygon(rfTt[0], rfTt[1], rfTt[2], rfTt[3], Standard_True).Wire();
      BRepOffsetAPI_ThruSections rfThru(Standard_True);
      rfThru.AddWire(rfBw); rfThru.AddWire(rfTw); rfThru.Build();

      TopoDS_Shape segBody = BRepAlgoAPI_Fuse(webThru.Shape(), lfThru.Shape()).Shape();
      segBody = BRepAlgoAPI_Fuse(segBody, rfThru.Shape()).Shape();
      builder.Add(compound, segBody);

      if (seg > 0 && params.flangeThickness > 0) {
        gp_Pnt fo(-hw0, -hw0, z0 - params.flangeThickness);
        builder.Add(compound, BRepPrimAPI_MakeBox(fo, w0, w0, params.flangeThickness).Shape());
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
      gp_Circ bc(gp_Ax2(gp_Pnt(xb, yb, 0), gp::DZ()), legW/2);
      TopoDS_Wire bw = BRepBuilderAPI_MakeWire(BRepBuilderAPI_MakeEdge(bc)).Wire();
      gp_Circ tc(gp_Ax2(gp_Pnt(xt, yt, H), gp::DZ()), legW*0.6/2);
      TopoDS_Wire tw = BRepBuilderAPI_MakeWire(BRepBuilderAPI_MakeEdge(tc)).Wire();
      BRepOffsetAPI_ThruSections lg(Standard_True);
      lg.AddWire(bw); lg.AddWire(tw); lg.Build();
      return lg.IsDone() ? lg.Shape() : BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(xb, yb, 0), gp::DZ()), legW/2, H).Shape();
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
            case 0: x1=-interp0; y1=-interp0; x2=interp0; y2=-interp0; break;
            case 1: x1=interp0; y1=-interp0; x2=interp0; y2=interp0; break;
            case 2: x1=interp0; y1=interp0; x2=-interp0; y2=interp0; break;
            case 3: x1=-interp0; y1=interp0; x2=-interp0; y2=-interp0; break;
          }
          gp_Pnt t1(x1, y1, z0), t2(x2, y2, z0);
          gp_Vec v(t1, t2); double l = v.Magnitude();
          if (l > Precision::Confusion())
            builder.Add(compound, BRepPrimAPI_MakeCylinder(gp_Ax2(t1, gp_Dir(v)), braceR, l).Shape());
          double gs = std::min(gussetSize, l * 0.2);
          gp_Pnt go(x1-gs/2, y1-gs/2, z0-gussetThick/2);
          gp_Trsf gTrs; gTrs.SetTranslation(gp_Vec(0, 0, 0));
          builder.Add(compound, BRepPrimAPI_MakeBox(go, gs, gs, gussetThick).Shape());
        }
      }

      for (int face = 0; face < 4; ++face) {
        double xb, yb, xt, yt;
        switch (face) {
          case 0: xb=interp0; yb=-interp0; xt=-interp1; yt=-interp1; break;
          case 1: xb=interp0; yb=interp0; xt=interp1; yt=-interp1; break;
          case 2: xb=-interp0; yb=interp0; xt=interp1; yt=interp1; break;
          case 3: xb=-interp0; yb=-interp0; xt=-interp1; yt=interp1; break;
        }
        gp_Pnt pz1(xb, yb, z0), pz2(xt, yt, z1);
        gp_Vec vz(pz1, pz2); double dz = vz.Magnitude();
        if (dz > Precision::Confusion())
          builder.Add(compound, BRepPrimAPI_MakeCylinder(gp_Ax2(pz1, gp_Dir(vz)), braceR*0.7, dz).Shape());
      }
    }

    int pegCount = (int)(H / 300);
    for (int p = 0; p < pegCount; ++p) {
      double z = (p + 1) * 300;
      double ip = halfB + (halfT - halfB) * z / H;
      builder.Add(compound, BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(ip, -ip, z), gp_Dir(1, -1, 0)), legW*0.15, legW*0.8).Shape());
    }
  }

  // ===== BASE FLANGE (柱底法兰) =====
  double fw = params.flangeWidth > 0 ? params.flangeWidth : params.bottomWidth * 1.3;
  double fth = params.flangeThickness > 0 ? params.flangeThickness : params.wallThickness * 2;
  double halfFW = fw / 2.0;
  gp_Pnt flgOrg(-halfFW, -halfFW, -fth);
  TopoDS_Shape flange = BRepPrimAPI_MakeBox(flgOrg, fw, fw, fth).Shape();
  builder.Add(compound, flange);

  // ===== TOP CAP PLATE (柱顶封板) — extend beyond leg centers
  double twBase = params.topWidth > 0 ? params.topWidth : params.bottomWidth * 0.6;
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
    double a = r * 2*M_PI / ribCount + M_PI / ribCount;
    gp_Pnt r1(halfFW*0.15*cos(a), halfFW*0.15*sin(a), -fth);
    gp_Pnt r2(halfFW*0.85*cos(a), halfFW*0.85*sin(a), -fth);
    gp_Pnt r3(halfFW*0.15*cos(a), halfFW*0.15*sin(a), -fth+ribH);
    gp_Dir tang(-sin(a), cos(a), 0);
    TopoDS_Wire rw = BRepBuilderAPI_MakePolygon(r1, r2, r3, Standard_True).Wire();
    TopoDS_Face rf = BRepLib_MakeFace(rw).Face();
    TopoDS_Shape rib = BRepPrimAPI_MakePrism(rf, gp_Vec(tang.XYZ()*ribT/2)).Shape();
    rib = BRepAlgoAPI_Fuse(rib, BRepPrimAPI_MakePrism(rf,
        gp_Vec(-tang.X()*ribT/2, -tang.Y()*ribT/2, 0)).Shape()).Shape();
    builder.Add(compound, rib);
  }
  }

  if (params.anchorDiameter > 0 && params.anchorSpacing > 0) {
    double ar = params.anchorDiameter / 2.0, hs = params.anchorSpacing / 2.0;
    for (int ax = -1; ax <= 1; ax += 2)
      for (int ay = -1; ay <= 1; ay += 2) {
        TopoDS_Shape hole = BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(ax*hs, ay*hs, -fth-1), gp::DZ()), ar, fth+2).Shape();
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
    double outerR = params.bottomWidth / 2, innerR = outerR - params.wallThickness, topR = params.topWidth / 2;
    if (std::abs(topR - outerR) > Precision::Confusion()) {
      BRepOffsetAPI_ThruSections gen(Standard_True);
      gp_Circ bc(gp_Ax2(gp::Origin(), gp::DZ()), outerR);
      TopoDS_Wire bw = BRepBuilderAPI_MakeWire(BRepBuilderAPI_MakeEdge(bc).Edge());
      gen.AddWire(bw);
      gp_Circ tc(gp_Ax2(gp_Pnt(0, 0, params.height), gp::DZ()), topR);
      TopoDS_Wire tw = BRepBuilderAPI_MakeWire(BRepBuilderAPI_MakeEdge(tc).Edge());
      gen.AddWire(tw); gen.Build();
      mast = gen.Shape();
    } else {
      mast = BRepPrimAPI_MakeCylinder(gp_Ax2(gp::Origin(), gp::DZ()), outerR, params.height).Shape();
    }
    if (innerR > 0) {
      double innerTopR = std::max(innerR - (params.bottomWidth - params.topWidth) / 2, 0.1);
      TopoDS_Shape inner;
      if (std::abs(innerTopR - innerR) > Precision::Confusion()) {
        BRepOffsetAPI_ThruSections ig(Standard_True);
        gp_Circ ibc(gp_Ax2(gp::Origin(), gp::DZ()), innerR);
        ig.AddWire(BRepBuilderAPI_MakeWire(BRepBuilderAPI_MakeEdge(ibc).Edge()));
        gp_Circ itc(gp_Ax2(gp_Pnt(0, 0, params.height), gp::DZ()), innerTopR);
        ig.AddWire(BRepBuilderAPI_MakeWire(BRepBuilderAPI_MakeEdge(itc).Edge()));
        ig.Build(); inner = ig.Shape();
      } else {
        inner = BRepPrimAPI_MakeCylinder(gp_Ax2(gp::Origin(), gp::DZ()), innerR, params.height).Shape();
      }
      mast = BRepAlgoAPI_Cut(mast, inner).Shape();
    }
    if (params.sectionType == concrete_mast_section_type::CIRCULAR_HOLED && params.holeDiameter > 0) {
      double holeR = params.holeDiameter / 2;
      for (int row = 0; row < params.holeRowCount; ++row) {
        double zPos = params.firstHoleOffset + row * params.holeSpacingV;
        if (zPos + holeR > params.height) break;
        for (int col = 0; col < params.holesPerRow; ++col) {
          double a = 2 * M_PI * col / params.holesPerRow;
          TopoDS_Shape h = BRepPrimAPI_MakeCylinder(
              gp_Ax2(gp_Pnt(outerR*cos(a), outerR*sin(a), zPos),
                     gp_Dir(cos(a), sin(a), 0)), holeR, params.wallThickness+2).Shape();
          mast = BRepAlgoAPI_Cut(mast, h).Shape();
        }
      }
    }
  } else if (params.sectionType == concrete_mast_section_type::RECTANGULAR) {
    double b = params.bottomWidth;
    double t = params.topWidth > 0 ? params.topWidth : b;
    if (std::abs(t - b) > Precision::Confusion()) {
      BRepOffsetAPI_ThruSections gen(Standard_True);
      gp_Pnt bp[4] = {{-b/2, -b/2, 0}, {b/2, -b/2, 0}, {b/2, b/2, 0}, {-b/2, b/2, 0}};
      gen.AddWire(BRepBuilderAPI_MakePolygon(bp[0], bp[1], bp[2], bp[3], Standard_True));
      gp_Pnt tp[4] = {{-t/2, -t/2, (double)params.height}, {t/2, -t/2, (double)params.height}, {t/2, t/2, (double)params.height}, {-t/2, t/2, (double)params.height}};
      gen.AddWire(BRepBuilderAPI_MakePolygon(tp[0], tp[1], tp[2], tp[3], Standard_True));
      gen.Build(); mast = gen.Shape();
    } else {
      mast = BRepPrimAPI_MakeBox(gp_Pnt(-b/2, -b/2, 0), b, b, params.height).Shape();
    }
    if (params.wallThickness > 0 && b > 2*params.wallThickness) {
      double ib = b - 2*params.wallThickness;
      TopoDS_Shape inner = BRepPrimAPI_MakeBox(gp_Pnt(-ib/2, -ib/2, -1), ib, ib, params.height+2).Shape();
      mast = BRepAlgoAPI_Cut(mast, inner).Shape();
    }
  } else if (params.sectionType == concrete_mast_section_type::RECTANGULAR_HOLED) {
    double b = params.bottomWidth;
    double t = params.topWidth > 0 ? params.topWidth : b;
    double thinW = b * 0.45;
    if (std::abs(t - b) > Precision::Confusion()) {
      double thinT = t * 0.45;
      BRepOffsetAPI_ThruSections gen(Standard_True);
      gp_Pnt bp[4] = {{-thinW/2, -b/2, 0}, {thinW/2, -b/2, 0}, {thinW/2, b/2, 0}, {-thinW/2, b/2, 0}};
      gen.AddWire(BRepBuilderAPI_MakePolygon(bp[0], bp[1], bp[2], bp[3], Standard_True));
      gp_Pnt tp[4] = {{-thinT/2, -t/2, (double)params.height}, {thinT/2, -t/2, (double)params.height}, {thinT/2, t/2, (double)params.height}, {-thinT/2, t/2, (double)params.height}};
      gen.AddWire(BRepBuilderAPI_MakePolygon(tp[0], tp[1], tp[2], tp[3], Standard_True));
      gen.Build(); mast = gen.Shape();
    } else {
      mast = BRepPrimAPI_MakeBox(gp_Pnt(-thinW/2, -b/2, 0), thinW, b, params.height).Shape();
    }
    // Round wind holes — diameter proportional to current column width
    if (params.holeDiameter > 0 && params.holeSpacingV > 0) {
      for (double z = params.firstHoleOffset; z < params.height; z += params.holeSpacingV) {
        double curW = b + (t - b) * z / params.height;
        double holeR = params.holeDiameter * curW / b / 2;
        TopoDS_Shape h = BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(-thinW, 0, z), gp::DX(), gp::DZ()), holeR, curW * 4).Shape();
        mast = BRepAlgoAPI_Cut(mast, h).Shape();
      }
    }
  }
  return mast;
}
TopoDS_Shape create_concrete_mast(const concrete_mast_params &params, const gp_Pnt &baseCenter, const gp_Dir &axisDirection) {
  TopoDS_Shape s = create_concrete_mast(params);
  gp_Ax3 src(gp::Origin(), gp::DZ()), tgt(baseCenter, axisDirection);
  gp_Trsf tr; tr.SetTransformation(tgt, src);
  return BRepBuilderAPI_Transform(s, tr).Shape();
}

// =========================================================================
// 13. OCS Foundation (支柱基础)
// =========================================================================
TopoDS_Shape create_ocs_foundation(const ocs_foundation_params &params) {
  if (params.height <= 0) throw Standard_ConstructionError("Height must be positive");
  TopoDS_Shape foundation;
  switch (params.type) {
  case foundation_type::FLANGE:
    foundation = BRepPrimAPI_MakeBox(gp_Pnt(-params.length/2, -params.width/2, 0), params.length, params.width, params.height).Shape();
    if (params.flangeThickness > 0) {
      double fs = std::min(params.length, params.width) * 0.8;
      foundation = BRepAlgoAPI_Fuse(foundation, BRepPrimAPI_MakeBox(gp_Pnt(-fs/2, -fs/2, params.height), fs, fs, params.flangeThickness).Shape()).Shape();
    }
    if (params.anchorCount > 0 && params.anchorDiameter > 0) {
      double hs = params.anchorSpacing/2, br = params.anchorDiameter/2, th = params.height + params.flangeThickness + params.anchorLength;
      for (int ax = -1; ax <= 1; ax += 2) for (int ay = -1; ay <= 1; ay += 2) {
        if (params.anchorCount >= 4 || (ax == -1 && ay == -1))
          foundation = BRepAlgoAPI_Fuse(foundation, BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(ax*hs, ay*hs, 0), gp::DZ()), br, th).Shape()).Shape();
      }
    }
    break;
  case foundation_type::DIRECT_BURIED:
    foundation = BRepPrimAPI_MakeCylinder(gp_Ax2(gp::Origin(), gp::DZ()), std::min(params.length, params.width)/2, params.height).Shape(); break;
  case foundation_type::BORED_PILE: {
    double pr = std::min(params.length, params.width)/2;
    foundation = BRepPrimAPI_MakeCylinder(gp_Ax2(gp::Origin(), gp::DZ()), pr, params.height).Shape();
    foundation = BRepAlgoAPI_Fuse(foundation, BRepPrimAPI_MakeCone(gp_Ax2(gp_Pnt(0, 0, params.height*0.85), gp::DZ()), pr*1.3, pr, params.height*0.15).Shape()).Shape();
    break;
  }
  default:
    foundation = BRepPrimAPI_MakeCylinder(gp_Ax2(gp::Origin(), gp::DZ()), std::min(params.length, params.width)/2, params.height).Shape(); break;
  }
  return foundation;
}
TopoDS_Shape create_ocs_foundation(const ocs_foundation_params &params, const gp_Pnt &position, const gp_Dir &normal, const gp_Dir &xDir) {
  TopoDS_Shape s = create_ocs_foundation(params);
  gp_Ax3 src(gp::Origin(), gp::DZ(), gp::DX()), tgt(position, normal, xDir);
  gp_Trsf tr; tr.SetTransformation(tgt, src);
  return BRepBuilderAPI_Transform(s, tr).Shape();
}

// =========================================================================
// 14. Dropper (吊弦)
// =========================================================================
TopoDS_Shape create_dropper(const dropper_params &params) {
  if (params.length <= 0 || params.wireDiameter <= 0) throw Standard_ConstructionError("Invalid dimensions");
  double wr = params.wireDiameter/2;
  TopoDS_Shape wire = BRepPrimAPI_MakeCylinder(gp_Ax2(gp::Origin(), gp::DZ()), wr, params.length).Shape();
  if (params.clampLength > 0 && params.clampWidth > 0) {
    double ch = params.clampThickness > 0 ? params.clampThickness : params.wireDiameter;
    wire = BRepAlgoAPI_Fuse(wire, BRepPrimAPI_MakeBox(gp_Pnt(-params.clampWidth/2, -params.clampWidth/2, params.length), params.clampWidth, params.clampWidth, ch).Shape()).Shape();
    wire = BRepAlgoAPI_Fuse(wire, BRepPrimAPI_MakeBox(gp_Pnt(-params.clampWidth/2, -params.clampWidth/2, -ch), params.clampWidth, params.clampWidth, ch).Shape()).Shape();
  }
  return wire;
}
TopoDS_Shape create_dropper(const dropper_params &params, const gp_Pnt &topPoint, const gp_Dir &direction) {
  TopoDS_Shape s = create_dropper(params);
  gp_Ax3 src(gp::Origin(), gp::DZ()), tgt(topPoint, direction);
  gp_Trsf tr; tr.SetTransformation(tgt, src);
  return BRepBuilderAPI_Transform(s, tr).Shape();
}

// =========================================================================
// 15. Cantilever Base (腕臂底座)
// =========================================================================
TopoDS_Shape create_cantilever_base(const cantilever_base_params &params) {
  if (params.length <= 0 || params.width <= 0 || params.height <= 0) throw Standard_ConstructionError("Invalid dimensions");
  TopoDS_Shape base = BRepPrimAPI_MakeBox(gp_Pnt(-params.length/2, -params.width/2, 0), params.length, params.width, params.height).Shape();
  if (params.boltDiameter > 0 && params.boltCount > 0) {
    double hr = params.boltDiameter/2, hs = params.boltSpacing/2;
    int cols = std::max(1, params.boltCount/2);
    for (int i = 0; i < cols; ++i) for (int j = 0; j < 2; ++j) {
      double x = (i - (cols-1)/2.0) * params.boltSpacing, y = (j == 0) ? -hs : hs;
      base = BRepAlgoAPI_Cut(base, BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(x, y, -1), gp::DZ()), hr, params.height+2).Shape()).Shape();
    }
  }
  return base;
}
TopoDS_Shape create_cantilever_base(const cantilever_base_params &params, const gp_Pnt &position, const gp_Dir &normal, const gp_Dir &upDir) {
  TopoDS_Shape s = create_cantilever_base(params);
  gp_Ax3 src(gp::Origin(), gp::DZ(), gp::DX()), tgt(position, upDir, normal);
  gp_Trsf tr; tr.SetTransformation(tgt, src);
  return BRepBuilderAPI_Transform(s, tr).Shape();
}

// =========================================================================
// 16. Messenger Wire Saddle (承力索座)
// =========================================================================
TopoDS_Shape create_mw_saddle(const mw_saddle_params &params) {
  if (params.length <= 0 || params.width <= 0) throw Standard_ConstructionError("Invalid dimensions");
  TopoDS_Shape body = BRepPrimAPI_MakeBox(gp_Pnt(-params.length/2, -params.width/2, 0), params.length, params.width, params.height).Shape();
  if (params.grooveRadius > 0) body = BRepAlgoAPI_Cut(body, BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, params.height), gp::DY()), params.grooveRadius, params.width+2).Shape()).Shape();
  if (params.boltDiameter > 0) {
    double hr = params.boltDiameter/2, hl = params.length*0.3;
    body = BRepAlgoAPI_Cut(body, BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(-hl, 0, -1), gp::DZ()), hr, params.height+2).Shape()).Shape();
    body = BRepAlgoAPI_Cut(body, BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(hl, 0, -1), gp::DZ()), hr, params.height+2).Shape()).Shape();
  }
  return body;
}
TopoDS_Shape create_mw_saddle(const mw_saddle_params &params, const gp_Pnt &position, const gp_Dir &normal, const gp_Dir &xDir) {
  TopoDS_Shape s = create_mw_saddle(params);
  gp_Ax3 src(gp::Origin(), gp::DZ(), gp::DX()), tgt(position, normal, xDir);
  gp_Trsf tr; tr.SetTransformation(tgt, src);
  return BRepBuilderAPI_Transform(s, tr).Shape();
}

// =========================================================================
// 17. Balance Weight (坠砣)
// =========================================================================
TopoDS_Shape create_balance_weight(const balance_weight_params &params) {
  if (params.width <= 0 || params.thickness <= 0 || params.height <= 0) throw Standard_ConstructionError("Invalid dimensions");
  TopoDS_Shape b = BRepPrimAPI_MakeBox(gp_Pnt(-params.width/2, -params.thickness/2, 0), params.width, params.thickness, params.height).Shape();
  double fr = std::min({params.width, params.thickness, params.height}) * 0.08;
  if (fr > Precision::Confusion()) {
    BRepFilletAPI_MakeFillet fillet(b);
    for (TopExp_Explorer ex(b, TopAbs_EDGE); ex.More(); ex.Next()) {
      TopoDS_Edge e = TopoDS::Edge(ex.Current());
      gp_Pnt p1 = BRep_Tool::Pnt(TopExp::FirstVertex(e)), p2 = BRep_Tool::Pnt(TopExp::LastVertex(e));
      if (std::abs(p1.Z()-p2.Z()) < Precision::Confusion() && std::abs(p1.X()-p2.X()) > Precision::Confusion())
        fillet.Add(fr, e);
    }
    fillet.Build(); if (fillet.IsDone()) b = fillet.Shape();
  }
  if (params.centerHoleDiameter > 0) b = BRepAlgoAPI_Cut(b, BRepPrimAPI_MakeCylinder(gp_Ax2(gp::Origin(), gp::DZ()), params.centerHoleDiameter/2, params.height+2).Shape()).Shape();
  return b;
}
TopoDS_Shape create_balance_weight(const balance_weight_params &params, const gp_Pnt &position, const gp_Dir &normal, const gp_Dir &xDir) {
  TopoDS_Shape s = create_balance_weight(params);
  gp_Ax3 src(gp::Origin(), gp::DZ(), gp::DX()), tgt(position, normal, xDir);
  gp_Trsf tr; tr.SetTransformation(tgt, src);
  return BRepBuilderAPI_Transform(s, tr).Shape();
}

// =========================================================================
// 18. Weight Rod (坠砣杆)
// =========================================================================
TopoDS_Shape create_weight_rod(const weight_rod_params &params) {
  if (params.rodDiameter <= 0 || params.rodLength <= 0) throw Standard_ConstructionError("Invalid dimensions");
  double rr = params.rodDiameter/2;
  TopoDS_Shape rod = BRepPrimAPI_MakeCylinder(gp_Ax2(gp::Origin(), gp::DZ()), rr, params.rodLength).Shape();
  if (params.topHoleDiameter > 0) rod = BRepAlgoAPI_Cut(rod, BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, params.rodLength - rr*3), gp::DY()), params.topHoleDiameter/2, rr*4).Shape()).Shape();
  return rod;
}
TopoDS_Shape create_weight_rod(const weight_rod_params &params, const gp_Pnt &position, const gp_Dir &axisDirection) {
  TopoDS_Shape s = create_weight_rod(params);
  gp_Ax3 src(gp::Origin(), gp::DZ()), tgt(position, axisDirection);
  gp_Trsf tr; tr.SetTransformation(tgt, src);
  return BRepBuilderAPI_Transform(s, tr).Shape();
}

// =========================================================================
// 19. Anchor Fitting (下锚金具)
// =========================================================================
TopoDS_Shape create_anchor_fitting(const anchor_fitting_params &params) {
  if (params.length <= 0 || params.diameter <= 0) throw Standard_ConstructionError("Invalid dimensions");
  double R = params.diameter/2;
  if (params.type == anchor_fitting_type::ROD_AND_RING) {
    return BRepAlgoAPI_Fuse(BRepPrimAPI_MakeCylinder(gp_Ax2(gp::Origin(), gp::DX()), R, params.length).Shape(),
                             BRepPrimAPI_MakeSphere(gp_Ax2(gp_Pnt(params.length, 0, 0), gp::DX()), R*1.5).Shape()).Shape();
  } else if (params.type == anchor_fitting_type::DOUBLE_EAR) {
    TopoDS_Shape b = BRepPrimAPI_MakeBox(gp_Pnt(-params.length/2, -R, -R), params.length, R*2, R*2).Shape();
    if (R > 0) {
      b = BRepAlgoAPI_Cut(b, BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(-params.length/3, 0, 0), gp::DY()), R*0.4, R*4).Shape()).Shape();
      b = BRepAlgoAPI_Cut(b, BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(params.length/3, 0, 0), gp::DY()), R*0.4, R*4).Shape()).Shape();
    }
    return b;
  } else {
    gp_Pnt bp[4] = {{-R, -R, 0}, {R, -R, 0}, {R, R, 0}, {-R, R, 0}};
    BRepOffsetAPI_ThruSections gen(Standard_True);
    gen.AddWire(BRepBuilderAPI_MakePolygon(bp[0], bp[1], bp[2], bp[3], Standard_True));
    gp_Pnt tp[4] = {{-R*0.7, -R*0.7, params.length}, {R*0.7, -R*0.7, params.length}, {R*0.7, R*0.7, params.length}, {-R*0.7, R*0.7, params.length}};
    gen.AddWire(BRepBuilderAPI_MakePolygon(tp[0], tp[1], tp[2], tp[3], Standard_True));
    gen.Build(); return gen.Shape();
  }
}
TopoDS_Shape create_anchor_fitting(const anchor_fitting_params &params, const gp_Pnt &position, const gp_Dir &direction, const gp_Dir &upDir) {
  TopoDS_Shape s = create_anchor_fitting(params);
  gp_Ax3 src(gp::Origin(), gp::DZ(), gp::DX()), tgt(position, upDir, direction);
  gp_Trsf tr; tr.SetTransformation(tgt, src);
  return BRepBuilderAPI_Transform(s, tr).Shape();
}

// =========================================================================
// 20. Crossing (线岔)
// =========================================================================
TopoDS_Shape create_crossing(const crossing_params &params) {
  if (params.limitPipeLength <= 0) throw Standard_ConstructionError("Invalid pipe length");
  double pr = params.pipeDiameter/2, wr = params.wireDiameter/2;
  TopoDS_Shape pipe = BRepPrimAPI_MakeCylinder(gp_Ax2(gp::Origin(), gp::DX()), pr*2, params.limitPipeLength).Shape();
  if (pr > 0) pipe = BRepAlgoAPI_Cut(pipe, BRepPrimAPI_MakeCylinder(gp_Ax2(gp::Origin(), gp::DX()), pr, params.limitPipeLength).Shape()).Shape();
  double wl = params.limitPipeLength/2*3;
  TopoDS_Shape result = BRepAlgoAPI_Fuse(pipe, BRepPrimAPI_MakeCylinder(gp_Ax2(gp::Origin(), gp::DX()), wr, wl).Shape()).Shape();
  double a = M_PI/6;
  result = BRepAlgoAPI_Fuse(result, BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(-wl/2, 0, 0), gp_Dir(cos(a), sin(a), 0)), wr, wl).Shape()).Shape();
  return result;
}
TopoDS_Shape create_crossing(const crossing_params &params, const gp_Pnt &crossPoint, const gp_Dir &mainDir, const gp_Dir &branchDir) {
  TopoDS_Shape s = create_crossing(params);
  gp_Dir up = mainDir.Crossed(branchDir); if (gp_Vec(up.X(), up.Y(), up.Z()).Magnitude() < Precision::Confusion()) up = gp::DZ();
  gp_Ax3 src(gp::Origin(), gp::DZ(), gp::DX()), tgt(crossPoint, up, mainDir);
  gp_Trsf tr; tr.SetTransformation(tgt, src);
  return BRepBuilderAPI_Transform(s, tr).Shape();
}

// =========================================================================
// 21. Head Span (软横跨)
// =========================================================================
TopoDS_Shape create_head_span(const head_span_params &params) {
  if (params.span <= 0) throw Standard_ConstructionError("Span must be positive");
  double span = params.span, cDia = params.crossCatenaryDiameter > 0 ? params.crossCatenaryDiameter : 10;
  double uDia = params.upperRopeDiameter > 0 ? params.upperRopeDiameter : 8, lDia = params.lowerRopeDiameter > 0 ? params.lowerRopeDiameter : 8;
  double sag = params.crossCatenarySag > 0 ? params.crossCatenarySag : span * 0.05;

  BRep_Builder builder; TopoDS_Compound compound; builder.MakeCompound(compound);

  // Cross catenary — approximated as cylinder along Z at mid-point (simplified)
  gp_Pnt cl(0, 0, sag+1000), cr(span, 0, sag+1000);
  builder.Add(compound, BRepPrimAPI_MakeCylinder(gp_Ax2(cl, gp_Dir(cr.XYZ()-cl.XYZ())), cDia/2, span).Shape());

  // Fixed ropes
  gp_Pnt ul(0, 0, sag+800), ur(span, 0, sag+800);
  builder.Add(compound, BRepPrimAPI_MakeCylinder(gp_Ax2(ul, gp_Dir(ur.XYZ()-ul.XYZ())), uDia/2, span).Shape());
  gp_Pnt ll(0, 0, 800), lr(span, 0, 800);
  builder.Add(compound, BRepPrimAPI_MakeCylinder(gp_Ax2(ll, gp_Dir(lr.XYZ()-ll.XYZ())), lDia/2, span).Shape());

  // Insulators
  if (params.insulatorLength > 0) {
    double iL = params.insulatorLength, iD = iL*0.2;
    rod_insulator_params rip; rip.type = rod_insulator_type::SOLID; rip.height = iL; rip.outerDiameter = iD;
    rip.innerDiameter = 0; rip.shedDiameter = iD*1.5; rip.shedSpacing = iL/5; rip.shedCount = 3;
    rip.endFitting = end_fitting_type::FLANGE; rip.flangeDiameter = iD*1.2; rip.flangeBoltSpacing = iD*0.7; rip.flangeBoltDiameter = iD*0.18;
    for (int side = 0; side < 2; ++side) {
      double x = side * span;
      builder.Add(compound, create_rod_insulator(rip, gp_Pnt(x, 0, sag+1000), gp::DZ()));
      builder.Add(compound, create_rod_insulator(rip, gp_Pnt(x, 0, sag+800), gp::DX()));
      builder.Add(compound, create_rod_insulator(rip, gp_Pnt(x, 0, 800), gp::DX()));
    }
  }
  return compound;
}
TopoDS_Shape create_head_span(const head_span_params &params, const gp_Pnt &leftMast, const gp_Pnt &rightMast, const gp_Dir &upDir) {
  TopoDS_Shape s = create_head_span(params);
  gp_Vec v(leftMast, rightMast); double len = v.Magnitude();
  if (len <= Precision::Confusion()) return s;
  double scale = len / params.span;
  gp_Trsf sc; sc.SetScale(gp::Origin(), scale);
  gp_Ax3 src(gp::Origin(), gp::DZ(), gp::DX()), tgt(leftMast, upDir, gp_Dir(v));
  gp_Trsf tr; tr.SetTransformation(tgt, src);
  return BRepBuilderAPI_Transform(BRepBuilderAPI_Transform(s, sc).Shape(), tr).Shape();
}
TopoDS_Shape create_transverse_span(const transverse_span_params &params) {
  if (params.span <= 0 || params.beamHeight <= 0)
    throw Standard_ConstructionError("Dimensions must be positive");

  BRep_Builder builder;
  TopoDS_Compound compound;
  builder.MakeCompound(compound);

  double span = params.span;
  double bh = params.beamHeight, bw = params.beamWidth, bt = params.beamThickness;

  if (params.beamType == beam_section_type::TRUSS) {
    int nPanels = std::max(4, (int)(span / 2000));
    double panelLen = span / nPanels;
    double chordR = bw * 0.15, webR = bw * 0.10;
    double camber = span * 0.002;

    auto makeChord = [&](gp_Pnt from, gp_Pnt to, double r) -> TopoDS_Shape {
      gp_Vec v(from, to);
      return BRepPrimAPI_MakeCylinder(gp_Ax2(from, gp_Dir(v)), r, v.Magnitude()).Shape();
    };

    std::vector<gp_Pnt> topPts, botPts;
    for (int i = 0; i <= nPanels; ++i) {
      double x = -span/2 + i * panelLen;
      double t = (double)i / nPanels;
      double cz = camber * (1.0 - 4.0 * (t - 0.5) * (t - 0.5));
      topPts.push_back(gp_Pnt(x, 0, bh + cz));
      botPts.push_back(gp_Pnt(x, 0, cz * 0.3));
    }

    for (int i = 0; i < nPanels; ++i) {
      for (int face = -1; face <= 1; face += 2) {
        double y = face * bw/2;
        builder.Add(compound, makeChord(gp_Pnt(topPts[i].X(), y, topPts[i].Z()), gp_Pnt(topPts[i+1].X(), y, topPts[i+1].Z()), chordR));
        builder.Add(compound, makeChord(gp_Pnt(botPts[i].X(), y, botPts[i].Z()), gp_Pnt(botPts[i+1].X(), y, botPts[i+1].Z()), chordR));
        // Verticals
        builder.Add(compound, makeChord(gp_Pnt(topPts[i].X(), y, topPts[i].Z()), gp_Pnt(botPts[i].X(), y, botPts[i].Z()), webR));
        // Z-diagonals
        builder.Add(compound, makeChord(gp_Pnt(botPts[i].X(), y, botPts[i].Z()), gp_Pnt(topPts[i+1].X(), y, topPts[i+1].Z()), webR*0.8));
        builder.Add(compound, makeChord(gp_Pnt(topPts[i].X(), y, topPts[i].Z()), gp_Pnt(botPts[i+1].X(), y, botPts[i+1].Z()), webR*0.8));
      }
    }
  } else if (params.beamType == beam_section_type::BOX) {
    gp_Pnt b1(-span/2, -bw/2, 0), b2(-span/2, bw/2, 0), b3(-span/2, bw/2, bh), b4(-span/2, -bw/2, bh);
    TopoDS_Face of = BRepLib_MakeFace(BRepBuilderAPI_MakePolygon(b1, b2, b3, b4, Standard_True).Wire()).Face();
    TopoDS_Shape beam = BRepPrimAPI_MakePrism(of, gp_Vec(span, 0, 0)).Shape();
    if (bt > 0 && bh > 2*bt && bw > 2*bt) {
      gp_Pnt i1(-span/2-1, -bw/2+bt, bt), i2(-span/2-1, bw/2-bt, bt);
      gp_Pnt i3(-span/2-1, bw/2-bt, bh-bt), i4(-span/2-1, -bw/2+bt, bh-bt);
      TopoDS_Face inf = BRepLib_MakeFace(BRepBuilderAPI_MakePolygon(i1, i2, i3, i4, Standard_True).Wire()).Face();
      beam = BRepAlgoAPI_Cut(beam, BRepPrimAPI_MakePrism(inf, gp_Vec(span+2, 0, 0)).Shape()).Shape();
    }
    builder.Add(compound, beam);
  } else if (params.beamType == beam_section_type::H_BEAM_T) {
    TopoDS_Shape web = BRepPrimAPI_MakeBox(gp_Pnt(-span/2, -bw*0.15, bt), span, bw*0.3, bh-2*bt).Shape();
    TopoDS_Shape lf = BRepPrimAPI_MakeBox(gp_Pnt(-span/2, -bw/2, 0), span, bw, bt).Shape();
    TopoDS_Shape rf = BRepPrimAPI_MakeBox(gp_Pnt(-span/2, -bw/2, bh-bt), span, bw, bt).Shape();
    TopoDS_Shape beam = BRepAlgoAPI_Fuse(web, lf).Shape();
    beam = BRepAlgoAPI_Fuse(beam, rf).Shape();
    builder.Add(compound, beam);
  } else {
    // COMBO: upper box + lower truss
    double boxH = bh * 0.4, trussH = bh - boxH;
    gp_Pnt bb1(-span/2, -bw/2, trussH), bb2(-span/2, bw/2, trussH);
    gp_Pnt bb3(-span/2, bw/2, bh), bb4(-span/2, -bw/2, bh);
    TopoDS_Face bf = BRepLib_MakeFace(BRepBuilderAPI_MakePolygon(bb1, bb2, bb3, bb4, Standard_True).Wire()).Face();
    builder.Add(compound, BRepPrimAPI_MakePrism(bf, gp_Vec(span, 0, 0)).Shape());
    int nPanels = std::max(4, (int)(span / 2000));
    double panelLen = span / nPanels;
    double chordR = bw * 0.1;
    for (int i = 0; i <= nPanels; ++i) {
      double x = -span/2 + i * panelLen;
      for (int face = -1; face <= 1; face += 2) {
        double y = face * bw/2;
        gp_Pnt bc(x, y, 0);
        if (i < nPanels) {
          gp_Pnt bcN(-span/2 + (i+1)*panelLen, y, 0);
          builder.Add(compound, BRepPrimAPI_MakeCylinder(gp_Ax2(bc, gp_Dir(bcN.XYZ()-bc.XYZ())), chordR, panelLen).Shape());
          gp_Pnt upN(-span/2 + (i+1)*panelLen, y, trussH);
          builder.Add(compound, BRepPrimAPI_MakeCylinder(gp_Ax2(bc, gp_Dir(upN.XYZ()-bc.XYZ())), chordR*0.7, panelLen*1.2).Shape());
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
    throw Standard_ConstructionError("Length and section size must be positive");

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
    TopoDS_Shape outer =
        BRepPrimAPI_MakeBox(outerOrg, params.sectionSize, params.sectionSize,
                              params.length).Shape();
    if (wT > 0 && ext > wT) {
      double innerExt = ext - wT;
      gp_Pnt innerOrg(-innerExt, -innerExt, -1);
      TopoDS_Shape inner =
          BRepPrimAPI_MakeBox(innerOrg, params.sectionSize - 2 * wT,
                                params.sectionSize - 2 * wT,
                                params.length + 2).Shape();
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
    TopoDS_Shape tf =
        BRepPrimAPI_MakeBox(tfOrg, params.topFlangeSize, params.topFlangeSize,
                              flgTh).Shape();
    // Bolt holes
    if (params.boltDiameter > 0) {
      double hr = params.boltDiameter / 2.0;
      double hs = params.boltSpacing / 2.0;
      for (int x = -1; x <= 1; x += 2)
        for (int y = -1; y <= 1; y += 2) {
          TopoDS_Shape h =
              BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(x * hs, y * hs, params.length - 1),
                                               gp::DZ()),
                                        hr, flgTh + 2).Shape();
          tf = BRepAlgoAPI_Cut(tf, h).Shape();
        }
    }
    body = BRepAlgoAPI_Fuse(body, tf).Shape();

    // Stiffener ribs (三角加劲肋) between tube and top flange — 4 corners
    double ribH = params.topFlangeSize * 0.3;        // rib height
    double ribW = params.topFlangeSize * 0.25;        // rib extends outward from tube
    double ribT = params.wallThickness * 0.8;          // rib plate thickness
    for (int r = 0; r < 4; ++r) {
      double a = r * M_PI / 2.0 + M_PI / 4.0;          // 45°, 135°, 225°, 315°
      double nx = cos(a), ny = sin(a);                  // outward normal
      double tx = -ny, ty = nx;                         // tangential direction
      double bx = halfS * 0.85 * nx, by = halfS * 0.85 * ny;  // base on tube surface

      // Three vertices: tube→flange edge→tube(offset down)
      gp_Pnt r1(bx, by, params.length);                              // top (flange level)
      gp_Pnt r2(bx + ribW * nx, by + ribW * ny, params.length - ribH * 0.3);  // flange edge
      gp_Pnt r3(bx, by, params.length - ribH);                       // tube(offset down)
      TopoDS_Wire rw = BRepBuilderAPI_MakePolygon(r1, r2, r3, Standard_True).Wire();
      TopoDS_Face rf = BRepLib_MakeFace(rw).Face();
      // Extrude along tangential direction to give thickness
      TopoDS_Shape rib = BRepPrimAPI_MakePrism(rf,
          gp_Vec(tx * ribT * 0.5, ty * ribT * 0.5, 0)).Shape();
      rib = BRepAlgoAPI_Fuse(rib,
          BRepPrimAPI_MakePrism(rf,
              gp_Vec(-tx * ribT * 0.5, -ty * ribT * 0.5, 0)).Shape()).Shape();
      body = BRepAlgoAPI_Fuse(body, rib).Shape();
    }
  }

  // Bottom flange (安装腕臂底座)
  if (params.bottomFlangeSize > 0) {
    double flgH = params.bottomFlangeSize / 2.0;
    double flgTh = params.bottomFlangeThick > 0 ? params.bottomFlangeThick : wT * 2;
    gp_Pnt bfOrg(-flgH, -flgH, -flgTh);
    TopoDS_Shape bf =
        BRepPrimAPI_MakeBox(bfOrg, params.bottomFlangeSize, params.bottomFlangeSize,
                              flgTh).Shape();
    if (params.boltDiameter > 0) {
      double hr = params.boltDiameter / 2.0;
      double hs = params.boltSpacing / 2.0;
      for (int x = -1; x <= 1; x += 2)
        for (int y = -1; y <= 1; y += 2) {
          TopoDS_Shape h =
              BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(x * hs, y * hs, -flgTh - 1),
                                               gp::DZ()),
                                        hr, flgTh + 2).Shape();
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
  auto makeTube = [](gp_Ax2 axis, double OR, double IR, double len) -> TopoDS_Shape {
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
  TopoDS_Shape rightPost = makeTube(rightAxis, postR, postIR, params.frameHeight);

  // Top horizontal beam along X, at Z=frameHeight
  gp_Ax2 topAxis(gp_Pnt(-halfBL, 0, params.frameHeight), gp::DX());
  TopoDS_Shape topBeam = makeTube(topAxis, beamR, beamIR, params.beamLength);

  result = BRepAlgoAPI_Fuse(leftPost, rightPost).Shape();
  result = BRepAlgoAPI_Fuse(result, topBeam).Shape();

  // Base plates under each post
  if (params.basePlateLength > 0) {
    double bpl = params.basePlateLength / 2.0;
    double bpw = params.basePlateWidth / 2.0;
    double bpt = params.basePlateThick > 0 ? params.basePlateThick : params.postWallThick * 2;

    for (int side = -1; side <= 1; side += 2) {
      double cx = side * halfFW;
      gp_Pnt bpOrg(cx - bpl, -bpw, -bpt);
      TopoDS_Shape bp =
          BRepPrimAPI_MakeBox(bpOrg, params.basePlateLength, params.basePlateWidth,
                                bpt).Shape();
      // Bolt holes
      if (params.boltDiameter > 0) {
        double hr = params.boltDiameter / 2.0;
        double hs = params.boltSpacing / 2.0;
        for (int bx = -1; bx <= 1; bx += 2)
          for (int by = -1; by <= 1; by += 2) {
            TopoDS_Shape hole =
                BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(cx + bx * hs, by * hs, -bpt - 1),
                                                  gp::DZ()),
                                          hr, bpt + 2).Shape();
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
        TopoDS_Wire rw = BRepBuilderAPI_MakePolygon(r1, r2, r3, Standard_True).Wire();
        TopoDS_Face rf = BRepLib_MakeFace(rw).Face();
        TopoDS_Shape rib = BRepPrimAPI_MakePrism(rf, gp_Vec(0, fr * bpt, 0)).Shape();
        result = BRepAlgoAPI_Fuse(result, rib).Shape();
      }
    }
  }

  // Hanging ear plates on top beam
  int nHang = std::max(0, params.hangPointCount);
  if (nHang > 0) {
    double hSpacing = params.hangPointSpacing > 0 ? params.hangPointSpacing
                                                   : params.beamLength / (nHang + 1);
    double earW = beamR * 1.5, earH = beamR * 1.0, earT = params.beamWallThick * 2;
    for (int i = 0; i < nHang; ++i) {
      double x = -halfBL + (i + 1) * hSpacing;
      gp_Pnt earOrg(x - earT/2, -earW/2, params.frameHeight + beamR);
      TopoDS_Shape ear =
          BRepPrimAPI_MakeBox(earOrg, earT, earW, earH).Shape();
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
                                  const gp_Dir &direction,
                                  const gp_Dir &upDir) {
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
  if (params.diameter <= 0) throw Standard_ConstructionError("Diameter must be positive");
  double R = params.diameter / 2.0;
  gp_Vec vec(params.startPoint, params.endPoint);
  double len = vec.Magnitude();
  if (len < Precision::Confusion()) return BRepPrimAPI_MakeCylinder(gp_Ax2(params.startPoint, gp::DX()), R, 1).Shape();
  // Simplified: straight cylinder along span direction
  return BRepPrimAPI_MakeCylinder(gp_Ax2(params.startPoint, gp_Dir(vec)), R, len).Shape();
}

TopoDS_Wire create_suspension_cable_centerline(const suspension_cable_params &params) {
  gp_Vec vec(params.startPoint, params.endPoint);
  double span = vec.Magnitude();
  if (span <= Precision::Confusion())
    return BRepBuilderAPI_MakeWire(BRepBuilderAPI_MakeEdge(params.startPoint, params.startPoint));

  BRepBuilderAPI_MakeWire wire;

  if (params.cableType == suspension_cable_type::FIXED_ROPE || span < Precision::Confusion()) {
    // Straight line
    wire.Add(BRepBuilderAPI_MakeEdge(params.startPoint, params.endPoint));
  } else {
    // Catenary arc (Bezier) — sag is the mid-span deviation
    double sag = params.sag > 0 ? params.sag : span * 0.05;
    double sign = (params.cableType == suspension_cable_type::DROPPER) ? 1.0 : -1.0;
    gp_Vec sagVec = gp_Vec(0, 0, 1) * sag * sign;

    gp_Pnt mid = gp_Pnt(
        (params.startPoint.X() + params.endPoint.X()) / 2.0,
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
TopoDS_Shape create_suspension_hard_span(const suspension_hard_span_params &params) {
  if (params.span <= 0 || params.mastHeight <= 0)
    throw Standard_ConstructionError("Span and height must be positive");

  BRep_Builder builder;
  TopoDS_Compound compound;
  builder.MakeCompound(compound);

  double span = params.span;

  // Main suspension cable (top span, catenary type)
  suspension_cable_params sc;
  sc.startPoint = gp_Pnt(-span/2, 0, params.mastHeight);
  sc.endPoint   = gp_Pnt(span/2, 0, params.mastHeight);
  sc.diameter   = params.cableDiameter;
  sc.sag        = params.cableSag > 0 ? params.cableSag : span * 0.05;
  sc.cableType  = suspension_cable_type::CATENARY;
  sc.tension    = 0;
  builder.Add(compound, create_suspension_cable(sc));

  // Vertical dropper cables
  if (params.dropperCount > 0) {
    int nDrop = params.dropperCount;
    double dSpacing = params.dropperSpacing > 0 ? params.dropperSpacing
                                                 : span / (nDrop + 1);
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
        double dropLen = topPt.Z() * 0.5;  // arbitrary: half height
        gp_Pnt botPt = topPt.Translated(gp_Vec(0, 0, -dropLen));

        suspension_cable_params dropCable;
        dropCable.startPoint = topPt;
        dropCable.endPoint   = botPt;
        dropCable.diameter   = params.dropperCableDiameter;
        dropCable.sag        = 0;
        dropCable.cableType  = suspension_cable_type::DROPPER;
        dropCable.tension    = 0;
        builder.Add(compound, create_suspension_cable(dropCable));
      }
    }
  }

  // Upper fixed rope (水平) at ~70% mast height — shared pattern with soft span
  suspension_cable_params upRope;
  upRope.startPoint = gp_Pnt(-span/2, 0, params.mastHeight * 0.7);
  upRope.endPoint   = gp_Pnt(span/2, 0, params.mastHeight * 0.7);
  upRope.diameter   = params.cableDiameter * 0.6;
  upRope.sag        = 0;
  upRope.cableType  = suspension_cable_type::FIXED_ROPE;
  upRope.tension    = 0;
  builder.Add(compound, create_suspension_cable(upRope));

  // Lower fixed rope (水平) at ~50% mast height — shared pattern with soft span
  suspension_cable_params loRope;
  loRope.startPoint = gp_Pnt(-span/2, 0, params.mastHeight * 0.5);
  loRope.endPoint   = gp_Pnt(span/2, 0, params.mastHeight * 0.5);
  loRope.diameter   = params.cableDiameter * 0.5;
  loRope.sag        = 0;
  loRope.cableType  = suspension_cable_type::FIXED_ROPE;
  loRope.tension    = 0;
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
          create_rod_insulator(insParams,
              gp_Pnt(mastX, 0, params.mastHeight * 0.7),
              gp_Dir(-side, 0, 0)));
      // Insulator at lower fixed rope end
      builder.Add(compound,
          create_rod_insulator(insParams,
              gp_Pnt(mastX, 0, params.mastHeight * 0.5),
              gp_Dir(-side, 0, 0)));
    }
  }

  return compound;
}

TopoDS_Shape create_suspension_hard_span(const suspension_hard_span_params &params,
                                          const gp_Pnt &position,
                                          const gp_Dir &direction,
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
  if (params.diameter <= 0) throw Standard_ConstructionError("Diameter must be positive");

  gp_Vec v(params.topPoint, params.bottomPoint);
  double len = v.Magnitude();
  if (len <= Precision::Confusion())
    throw Standard_ConstructionError("Top and bottom points must differ");

  double R = params.diameter / 2.0;
  TopoDS_Shape cable;

  if (params.adjustable) {
    // Three-segment: upper straight + threaded adjuster + lower straight
    double adjLen = len * 0.15;       // adjuster length in middle
    double segLen = (len - adjLen) / 2.0;
    gp_Dir dir(v);
    gp_Vec halfStep = gp_Vec(dir.XYZ() * segLen);

    gp_Pnt adjStart = params.topPoint.Translated(halfStep);
    gp_Pnt adjEnd = adjStart.Translated(gp_Vec(dir.XYZ() * adjLen));

    // Upper segment
    gp_Ax2 upAxis(params.topPoint, dir);
    TopoDS_Shape upper =
        BRepPrimAPI_MakeCylinder(upAxis, R, segLen).Shape();

    // Lower segment
    gp_Ax2 loAxis(adjEnd, dir);
    TopoDS_Shape lower =
        BRepPrimAPI_MakeCylinder(loAxis, R, segLen).Shape();

    // Threaded adjuster: thicker cylinder + hex nut
    gp_Ax2 adjAxis(adjStart, dir);
    TopoDS_Shape adjRod =
        BRepPrimAPI_MakeCylinder(adjAxis, R * 1.3, adjLen).Shape();
    // Hex nut (approximated by hexagonal prism)
    double nutH = adjLen * 0.3;
    gp_Pnt nutCenter = adjStart.Translated(gp_Vec(dir.XYZ() * adjLen * 0.5));
    // Simple box approximation for the nut
    gp_Pnt nutOrg(nutCenter.X() - R*1.5, nutCenter.Y() - R*1.5, nutCenter.Z() - nutH/2);
    TopoDS_Shape nut =
        BRepPrimAPI_MakeBox(nutOrg, R*3, R*3, nutH).Shape();
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
    gp_Pnt plateOrg(pt.X() - plateSize/2, pt.Y() - plateSize/2,
                    pt.Z() - (end == 0 ? 0 : plateThick));
    TopoDS_Shape plate =
        BRepPrimAPI_MakeBox(plateOrg, plateSize, plateSize, plateThick).Shape();
    // Bolt hole
    double holeR = R * 0.5;
    TopoDS_Shape hole =
        BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(pt.X(), pt.Y(),
                                                  pt.Z() + (end == 0 ? -1 : plateThick+1)),
                                        gp::DZ()), holeR, plateThick+2).Shape();
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
            BRepPrimAPI_MakeCylinder(ha, holeR, params.mountHeight + 2)
                .Shape();
        plate = BRepAlgoAPI_Cut(plate, hole).Shape();
      }
    }
    return plate;
  }
}

TopoDS_Shape create_aux_bracket(const aux_bracket_params &params,
                                const gp_Pnt &position,
                                const gp_Dir &normal,
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
  if (params.railHeight <= 0 || params.headWidth <= 0 || params.baseWidth <= 0)
    throw Standard_ConstructionError("Rail dimensions must be positive");

  const double H = params.railHeight;
  const double hH = params.headHeight > 0 ? params.headHeight : H * 0.36;
  const double bH = params.baseHeight > 0 ? params.baseHeight : H * 0.18;
  const double hW = params.headWidth / 2.0;
  const double bW = params.baseWidth / 2.0;
  const double wT = params.webThickness > 0 ? params.webThickness / 2.0 : bW * 0.22;

  // 18-point rail profile in YZ plane (Z=0 at base bottom, Y=0 at centerline)
  // Head: wide top with rounded corners, slight dome
  // Web: tapered waist connecting head to base
  // Base: wide bottom with 1:4 end slopes
  BRepBuilderAPI_MakeWire wire;

  // Head top surface (3 segments for slight dome)
  gp_Pnt hTL(-hW, 0, H);
  gp_Pnt hTC(-hW * 0.7, 0, H + hH * 0.02);
  gp_Pnt hTM(0, 0, H + hH * 0.03);
  gp_Pnt hTR(hW * 0.7, 0, H + hH * 0.02);
  gp_Pnt hTR2(hW, 0, H);
  wire.Add(BRepBuilderAPI_MakeEdge(hTL, hTC));
  wire.Add(BRepBuilderAPI_MakeEdge(hTC, hTM));
  wire.Add(BRepBuilderAPI_MakeEdge(hTM, hTR));
  wire.Add(BRepBuilderAPI_MakeEdge(hTR, hTR2));

  // Head right side: outer vertical + bevel to web
  gp_Pnt hRB1(hW, 0, H - hH * 0.3);
  gp_Pnt hRB2(hW * 0.85, 0, H - hH * 0.7);
  wire.Add(BRepBuilderAPI_MakeEdge(hTR2, hRB1));
  wire.Add(BRepBuilderAPI_MakeEdge(hRB1, hRB2));

  // Head-web transition (beveled)
  gp_Pnt hwb(wT, 0, H - hH);
  wire.Add(BRepBuilderAPI_MakeEdge(hRB2, hwb));

  // Web body (tapered waist)
  gp_Pnt webBot(wT, 0, bH + bH * 0.3);
  wire.Add(BRepBuilderAPI_MakeEdge(hwb, webBot));

  // Web-base transition (flare to base)
  gp_Pnt wbFlare(bW * 0.7, 0, bH * 0.5);
  gp_Pnt wbBase(bW, 0, bH);
  wire.Add(BRepBuilderAPI_MakeEdge(webBot, wbFlare));
  wire.Add(BRepBuilderAPI_MakeEdge(wbFlare, wbBase));

  // Base right slope (1:4) and bottom
  gp_Pnt baseBotR(bW, 0, 0);
  wire.Add(BRepBuilderAPI_MakeEdge(wbBase, baseBotR));

  // Base bottom flat
  gp_Pnt baseBotL(-bW, 0, 0);
  wire.Add(BRepBuilderAPI_MakeEdge(baseBotR, baseBotL));

  // Base left slope (1:4)
  gp_Pnt baseTopL(-bW, 0, bH);
  wire.Add(BRepBuilderAPI_MakeEdge(baseBotL, baseTopL));

  // Base left top → web flare
  gp_Pnt wbFlareL(-bW * 0.7, 0, bH * 0.5);
  gp_Pnt webBotL(-wT, 0, bH + bH * 0.3);
  wire.Add(BRepBuilderAPI_MakeEdge(baseTopL, wbFlareL));
  wire.Add(BRepBuilderAPI_MakeEdge(wbFlareL, webBotL));

  // Web left body
  gp_Pnt webTopL(-wT, 0, H - hH);
  wire.Add(BRepBuilderAPI_MakeEdge(webBotL, webTopL));

  // Head-web left transition
  gp_Pnt hwbL(-hW * 0.85, 0, H - hH * 0.7);
  gp_Pnt hLB1(-hW, 0, H - hH * 0.3);
  wire.Add(BRepBuilderAPI_MakeEdge(webTopL, hwbL));
  wire.Add(BRepBuilderAPI_MakeEdge(hwbL, hLB1));
  wire.Add(BRepBuilderAPI_MakeEdge(hLB1, hTL));  // close to start

  if (!wire.IsDone())
    throw Standard_ConstructionError("Rail profile wire failed");

  TopoDS_Face face = BRepLib_MakeFace(wire.Wire()).Face();
  return BRepPrimAPI_MakePrism(face, gp_Vec(0, 0, params.standardLength)).Shape();
}

TopoDS_Shape create_rail(const rail_params &params,
                         const gp_Pnt &startPoint,
                         const gp_Pnt &endPoint) {
  TopoDS_Shape shape = create_rail(params);
  gp_Vec vec(startPoint, endPoint);
  double len = vec.Magnitude();
  if (len <= Precision::Confusion()) return shape;

  // Scale to match length, then rotate and translate
  gp_Dir dir(vec);
  double scale = len / params.standardLength;
  gp_Trsf s;
  s.SetScale(gp::Origin(), scale);
  shape = BRepBuilderAPI_Transform(shape, s).Shape();

  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(startPoint, gp::DZ(), dir);
  gp_Trsf t;
  t.SetTransformation(targetAx3, sourceAx3);
  return BRepBuilderAPI_Transform(shape, t).Shape();
}

// =========================================================================
// 25. Sleeper (轨枕)
// =========================================================================
TopoDS_Shape create_sleeper(const sleeper_params &params) {
  if (params.length <= 0 || params.width <= 0 || params.height <= 0)
    throw Standard_ConstructionError("Dimensions must be positive");

  double L = params.length, W = params.width, H = params.height;
  TopoDS_Shape body;

  if (params.shapeType == sleeper_shape_type::TRAPEZOIDAL) {
    double topW = W * 0.75, midW = W * 0.85;
    // Fish-belly: ends(wide) → center(narrow)
    BRepOffsetAPI_ThruSections gen(Standard_True);
    for (int s = 0; s < 3; ++s) {
      double t = s / 2.0;
      double x = -L/2 + t * L;
      double curW = (s == 1) ? midW : W;
      double curTopW = (s == 1) ? topW * 0.85 : topW;
      double hw = curW / 2, htw = curTopW / 2;
      gp_Pnt bp[4] = {{x, -hw, 0}, {x, -htw, H},
                       {x, htw, H}, {x, hw, 0}};
      gen.AddWire(BRepBuilderAPI_MakePolygon(bp[0], bp[1], bp[2], bp[3], Standard_True));
    }
    gen.Build(); body = gen.Shape();

    // Rail seats — shallow grooves at correct gauge positions
    if (params.grooveDepth > 0 && params.gauge > 0) {
      double hG = params.gauge / 2, gD = params.grooveDepth;
      for (int side = -1; side <= 1; side += 2) {
        double y = side * hG;
        TopoDS_Shape seat = BRepPrimAPI_MakeBox(gp_Pnt(-L*0.12, y - W*0.1, H - gD), L*0.24, W*0.2, gD+1).Shape();
        body = BRepAlgoAPI_Cut(body, seat).Shape();
      }
    }
  } else {
    double cfLen = L * 0.08;
    body = BRepPrimAPI_MakeBox(gp_Pnt(-L/2, -W/2, 0), L, W, H).Shape();

    for (int side = -1; side <= 1; side += 2) {
      double x = side * L/2;
      gp_Pnt tp1(x, -W/2 - 1, -1), tp2(x - side*cfLen, -W/2 - 1, -1);
      gp_Pnt tp3(x - side*cfLen, W/2 + 1, -1), tp4(x, W/2 + 1, -1);
      TopoDS_Wire cw = BRepBuilderAPI_MakePolygon(tp1, tp2, tp3, tp4, Standard_True).Wire();
      body = BRepAlgoAPI_Cut(body, BRepPrimAPI_MakePrism(BRepLib_MakeFace(cw).Face(), gp_Vec(0, 0, H*1.5)).Shape()).Shape();
    }

    if (params.grooveDepth > 0 && params.gauge > 0) {
      double hG = params.gauge / 2;
      for (int side = -1; side <= 1; side += 2)
        body = BRepAlgoAPI_Cut(body, BRepPrimAPI_MakeBox(gp_Pnt(-L*0.15, side*hG - W*0.18, H - params.grooveDepth), L*0.3, W*0.35, params.grooveDepth+1).Shape()).Shape();
    }
  }

  return body;
}

TopoDS_Shape create_sleeper(const sleeper_params &params,
                            const gp_Pnt &position,
                            const gp_Dir &direction,
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
  if (params.topWidth <= 0 || params.thickness <= 0 || params.centerlineSegments.empty())
    throw Standard_ConstructionError("Invalid ballast dimensions or centerline");

  double slope = params.sideSlope > 0 ? params.sideSlope : 1.5;
  double tw = params.topWidth, th = params.thickness;
  double bw = tw + 2 * slope * th;
  double bs = std::min(th * 0.25, tw * 0.1);
  int nSeg = 5;

  // Trapezoidal profile (same as before)
  BRepBuilderAPI_MakeWire profile;
  profile.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(0, -bw/2, 0), gp_Pnt(0, bw/2, 0)));
  profile.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(0, bw/2, 0), gp_Pnt(0, tw/2 + bs, th - bs)));
  for (int i = 0; i <= nSeg; ++i) {
    double t = (double)i / nSeg, y = tw/2 + bs * (1.0 - t), z = th - bs * (1.0 - t);
    if (i < nSeg) { double t2=(double)(i+1)/nSeg; profile.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(0,y,z), gp_Pnt(0,tw/2+bs*(1.0-t2), th-bs*(1.0-t2)))); }
  }
  profile.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(0, tw/2, th), gp_Pnt(0, -tw/2, th)));
  for (int i = 0; i <= nSeg; ++i) {
    double t = (double)i / nSeg, y = -tw/2 - bs * t, z = th - bs * t;
    if (i < nSeg) { double t2=(double)(i+1)/nSeg; profile.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(0,y,z), gp_Pnt(0,-tw/2-bs*t2, th-bs*t2))); }
  }
  profile.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(0, -tw/2 - bs, th - bs), gp_Pnt(0, -bw/2, 0)));

  // Build centerline path from curve segments
  BRepBuilderAPI_MakeWire path;
  for (auto &seg : params.centerlineSegments) {
    if (seg.points.size() < 2) continue;
    if (seg.type == centerline_curve_type::LINE) {
      path.Add(BRepBuilderAPI_MakeEdge(seg.points[0], seg.points[1]));
    } else if (seg.type == centerline_curve_type::ARC && seg.points.size() >= 3) {
      Handle(Geom_TrimmedCurve) arc = GC_MakeArcOfCircle(seg.points[0], seg.points[1], seg.points[2]);
      if (arc.IsNull()) continue;
      path.Add(BRepBuilderAPI_MakeEdge(arc));
    } else if (seg.type == centerline_curve_type::BEZIER) {
      Handle(TColgp_HArray1OfPnt) ctrl = new TColgp_HArray1OfPnt(1, (int)seg.points.size());
      for (size_t i = 0; i < seg.points.size(); ++i) ctrl->SetValue((int)(i+1), seg.points[i]);
      path.Add(BRepBuilderAPI_MakeEdge(new Geom_BezierCurve(ctrl->Array1())));
    }
  }

  BRepOffsetAPI_MakePipeShell pipe(path.Wire());
  pipe.Add(profile.Wire());
  pipe.SetMode(Standard_False);
  pipe.Build();
  if (!pipe.IsDone()) throw Standard_ConstructionError("Ballast sweep failed");
  pipe.MakeSolid();
  return pipe.Shape();
}

TopoDS_Shape create_track_slab(const track_slab_params &params) {
  if (params.length <= 0 || params.width <= 0 || params.thickness <= 0)
    throw Standard_ConstructionError("Dimensions must be positive");

  // Main slab
  gp_Pnt slabOrigin(-params.length / 2, -params.width / 2, 0);
  TopoDS_Shape slab =
      BRepPrimAPI_MakeBox(slabOrigin, params.length, params.width,
                            params.thickness)
          .Shape();

  // Rail seats on top
  int nSeats = std::max(2, params.railSeatCount);
  double seatSpacing = params.railSeatSpacing > 0
                           ? params.railSeatSpacing
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
        BRepPrimAPI_MakeBox(caOrigin, params.length, params.width, caH)
            .Shape();
    slab = BRepAlgoAPI_Fuse(slab, caLayer).Shape();
  }

  return slab;
}

TopoDS_Shape create_track_slab(const track_slab_params &params,
                               const gp_Pnt &position,
                               const gp_Dir &direction,
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
  if (params.padLength <= 0 || params.padWidth <= 0)
    throw Standard_ConstructionError("Pad dimensions must be positive");

  // Base pad
  gp_Pnt padOrigin(-params.padLength / 2, -params.padWidth / 2, 0);
  TopoDS_Shape pad =
      BRepPrimAPI_MakeBox(padOrigin, params.padLength, params.padWidth,
                            params.padThickness)
          .Shape();

  // Bolt holes
  if (params.gauge > 0) {
    double halfG = params.gauge / 2;
    double holeR = 8;
    gp_Ax2 h1(gp_Pnt(-25, -halfG, -1), gp::DZ());
    gp_Ax2 h2(gp_Pnt(25, -halfG, -1), gp::DZ());
    gp_Ax2 h3(gp_Pnt(-25, halfG, -1), gp::DZ());
    gp_Ax2 h4(gp_Pnt(25, halfG, -1), gp::DZ());
    for (auto &ha : {h1, h2, h3, h4}) {
      TopoDS_Shape hole =
          BRepPrimAPI_MakeCylinder(ha, holeR, params.padThickness + 2).Shape();
      pad = BRepAlgoAPI_Cut(pad, hole).Shape();
    }
  }

  return pad;
}

TopoDS_Shape create_fastener(const fastener_params &params,
                             const gp_Pnt &position,
                             const gp_Dir &direction,
                             const gp_Dir &upDir) {
  TopoDS_Shape shape = create_fastener(params);
  gp_Dir yDir = upDir.Crossed(direction);
  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(position, upDir, direction);
  gp_Trsf t;
  t.SetTransformation(targetAx3, sourceAx3);
  return BRepBuilderAPI_Transform(shape, t).Shape();
}

// =========================================================================
// 29. Guard Rail (护轨)
// =========================================================================
TopoDS_Shape create_guard_rail(const guard_rail_params &params) {
  if (params.height <= 0 || params.totalLength <= 0)
    throw Standard_ConstructionError("Dimensions must be positive");
  if (params.grooveWidth <= 0)
    throw Standard_ConstructionError("Groove width must be positive");

  double hW = params.headWidth / 2;
  double bW = params.baseWidth / 2;
  double gW = params.grooveWidth / 2;
  double H = params.height;

  // U-shaped cross-section profile
  // Has a groove in the head (typical for guard rail)
  gp_Pnt p1(-bW, 0, 0);
  gp_Pnt p2(bW, 0, 0);
  gp_Pnt p3(bW, 0, H);
  gp_Pnt p4(gW, 0, H);
  gp_Pnt p5(gW, 0, H * 0.8);
  gp_Pnt p6(-gW, 0, H * 0.8);
  gp_Pnt p7(-gW, 0, H);
  gp_Pnt p8(-bW, 0, H);

  BRepBuilderAPI_MakeWire wire;
  wire.Add(BRepBuilderAPI_MakeEdge(p1, p2));
  wire.Add(BRepBuilderAPI_MakeEdge(p2, p3));
  wire.Add(BRepBuilderAPI_MakeEdge(p3, p4));
  wire.Add(BRepBuilderAPI_MakeEdge(p4, p5));
  wire.Add(BRepBuilderAPI_MakeEdge(p5, p6));
  wire.Add(BRepBuilderAPI_MakeEdge(p6, p7));
  wire.Add(BRepBuilderAPI_MakeEdge(p7, p8));
  wire.Add(BRepBuilderAPI_MakeEdge(p8, p1));
  TopoDS_Face face = BRepBuilderAPI_MakeFace(wire.Wire()).Face();
  return BRepPrimAPI_MakePrism(face, gp_Vec(0, 0, params.totalLength)).Shape();
}

TopoDS_Shape create_guard_rail(const guard_rail_params &params,
                               const gp_Pnt &startPoint,
                               const gp_Pnt &endPoint) {
  // Create rail along X, then transform
  rail_params rp;
  rp.railHeight = params.height;
  rp.headWidth = params.headWidth;
  rp.baseWidth = params.baseWidth;
  rp.standardLength = params.totalLength;
  rp.headHeight = params.height * 0.4;
  rp.baseHeight = params.height * 0.2;
  rp.webThickness = params.baseWidth * 0.2;
  TopoDS_Shape shape = create_rail(rp);

  gp_Vec vec(startPoint, endPoint);
  double len = vec.Magnitude();
  if (len <= Precision::Confusion()) return shape;

  double scale = len / params.totalLength;
  gp_Trsf s;
  s.SetScale(gp::Origin(), scale);
  shape = BRepBuilderAPI_Transform(shape, s).Shape();

  gp_Ax3 sourceAx3(gp::Origin(), gp::DZ(), gp::DX());
  gp_Ax3 targetAx3(startPoint, gp::DZ(), gp_Dir(vec));
  gp_Trsf t;
  t.SetTransformation(targetAx3, sourceAx3);
  return BRepBuilderAPI_Transform(shape, t).Shape();
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
    TopoDS_Shape insulator = create_rod_insulator(
        rodParams, gp_Pnt(80, 0, bracketH), gp::DX());
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
    regParams.tubeWidth = 30; regParams.tubeHeight = 25;
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
TopoDS_Shape create_switch_rail(const switch_rail_params &params) {
  if (params.length <= 0 || params.railHeight <= 0)
    throw Standard_ConstructionError("Invalid switch rail dimensions");

  double H = params.railHeight;
  double hW = params.railHeadWidth / 2.0;
  double bW = params.railBaseWidth / 2.0;
  double tW = std::max(params.tipWidth / 2.0, Precision::Confusion());

  auto makeProfile = [&](double yHalfFromCenter, double zScale) -> TopoDS_Wire {
    double y = yHalfFromCenter;
    double hh = H * 0.36 * zScale;
    double bh = H * 0.18 * zScale;
    double hw = hW * zScale, bw = bW * zScale, wt = bw * 0.22;
    BRepBuilderAPI_MakeWire w;
    w.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(-hw, y, H*zScale), gp_Pnt(hw, y, H*zScale)));
    w.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(hw, y, H*zScale), gp_Pnt(hw, y, H*zScale - hh)));
    w.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(hw, y, H*zScale - hh), gp_Pnt(wt, y, H*zScale - hh)));
    w.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(wt, y, H*zScale - hh), gp_Pnt(wt, y, bh)));
    w.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(wt, y, bh), gp_Pnt(bw, y, bh)));
    w.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(bw, y, bh), gp_Pnt(bw, y, 0)));
    w.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(bw, y, 0), gp_Pnt(-bw, y, 0)));
    w.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(-bw, y, 0), gp_Pnt(-bw, y, bh)));
    w.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(-bw, y, bh), gp_Pnt(-wt, y, bh)));
    w.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(-wt, y, bh), gp_Pnt(-wt, y, H*zScale - hh)));
    w.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(-wt, y, H*zScale - hh), gp_Pnt(-hw, y, H*zScale - hh)));
    w.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(-hw, y, H*zScale - hh), gp_Pnt(-hw, y, H*zScale)));
    return w.Wire();
  };

  // Build taper: 3 sections from tip(very thin) to heel(full)
  int nSections = 5;
  BRepOffsetAPI_ThruSections gen(Standard_True);
  for (int i = 0; i < nSections; ++i) {
    double t = (double)i / (nSections - 1);
    double x = t * params.length;
    double scale = 0.05 + 0.95 * t;
    gen.AddWire(makeProfile(0, scale));
  }
  gen.Build();
  TopoDS_Shape rail = gen.Shape();

  // If curved, rotate each section point around the curve center
  if (params.curveRadius > 0) {
    double curveDir = params.isLeftHand ? 1.0 : -1.0;
    // Build curved path
    double R = params.curveRadius;
    double totalAngle = params.length / R;
    int nSeg = 20;
    std::vector<gp_Pnt> pathPts;
    for (int i = 0; i <= nSeg; ++i) {
      double a = totalAngle * i / nSeg * curveDir;
      pathPts.push_back(gp_Pnt(R * sin(a), R * (1 - cos(a)) * curveDir, 0));
    }
    // Sweep along curved path
    BRepBuilderAPI_MakeWire pathWire;
    for (int i = 0; i < nSeg; ++i)
      pathWire.Add(BRepBuilderAPI_MakeEdge(pathPts[i], pathPts[i+1]));
    // Use tip profile and heel profile for the sweep
    TopoDS_Face tipFace = BRepLib_MakeFace(makeProfile(0, 0.05)).Face();
    TopoDS_Face heelFace = BRepLib_MakeFace(makeProfile(0, 1.0)).Face();
    BRepOffsetAPI_ThruSections curveGen(Standard_True);
    curveGen.AddWire(makeProfile(0, 0.05));
    curveGen.AddWire(makeProfile(0, 0.3));
    curveGen.AddWire(makeProfile(0, 1.0));
    curveGen.Build();
    return curveGen.Shape();
  }

  return rail;
}

TopoDS_Shape create_switch_rail(const switch_rail_params &params,
                                 const gp_Pnt &position,
                                 const gp_Dir &direction,
                                 const gp_Dir &upDir) {
  TopoDS_Shape s = create_switch_rail(params);
  gp_Ax3 src(gp::Origin(), gp::DZ(), gp::DX()), tgt(position, upDir, direction);
  gp_Trsf tr; tr.SetTransformation(tgt, src);
  return BRepBuilderAPI_Transform(s, tr).Shape();
}

// =========================================================================
// TRACK: 32. Frog (辙叉) — V-shaped crossing
// =========================================================================
TopoDS_Shape create_frog(const frog_params &params) {
  if (params.turnoutNo <= 0) throw Standard_ConstructionError("Turnout number must be positive");

  double frogAngle = atan2(1.0, (double)params.turnoutNo);
  double gauge = params.gauge;
  double frogLen = gauge * params.turnoutNo * 0.3;
  double H = params.railHeight;
  double hW = params.railHeadWidth / 2.0;
  double bW = params.railBaseWidth / 2.0;

  auto makePointRail = [&](double yOff, double angle, double len) -> TopoDS_Shape {
    // Point rail: triangular tapered beam
    gp_Pnt b1(-bW, yOff - bW, 0), b2(bW, yOff - bW, 0);
    gp_Pnt b3(bW, yOff + bW, 0), b4(-bW, yOff + bW, 0);
    TopoDS_Wire bw = BRepBuilderAPI_MakePolygon(b1, b2, b3, b4, Standard_True).Wire();
    double tipX = len * cos(frogAngle * 0.5);
    gp_Pnt t1(-1, yOff - 1, H), t2(1, yOff - 1, H);
    gp_Pnt t3(1, yOff + 1, H), t4(-1, yOff + 1, H);
    TopoDS_Wire tw = BRepBuilderAPI_MakePolygon(t1, t2, t3, t4, Standard_True).Wire();
    BRepOffsetAPI_ThruSections gen(Standard_True);
    gen.AddWire(bw); gen.AddWire(tw); gen.Build();
    return gen.Shape();
  };

  BRep_Builder builder;
  TopoDS_Compound compound;
  builder.MakeCompound(compound);

  // Left point rail tapering right
  double halfGauge = gauge / 2.0;
  builder.Add(compound, makePointRail(-halfGauge * 0.3,  frogAngle / 2, frogLen * 0.7));
  // Right point rail tapering left
  builder.Add(compound, makePointRail( halfGauge * 0.3, -frogAngle / 2, frogLen * 0.7));

  // Wing rails on each side
  for (int side = -1; side <= 1; side += 2) {
    double y = side * halfGauge;
    double wingLen = frogLen * 0.6;
    // Wing rail: bent rail segment tapering toward frog
    gp_Pnt w1(0, y, 0), w2(frogLen * 0.4, y + side * frogLen * 0.15, 0);
    gp_Pnt w3(frogLen * 0.8, y + side * frogLen * 0.08, 0);
    BRepBuilderAPI_MakeWire ww;
    ww.Add(BRepBuilderAPI_MakeEdge(w1, w2));
    ww.Add(BRepBuilderAPI_MakeEdge(w2, w3));
    // Rail section
    BRepBuilderAPI_MakeWire rw;
    rw.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(-hW, 0, 0), gp_Pnt(hW, 0, 0)));
    rw.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(hW, 0, 0), gp_Pnt(hW, 0, H)));
    rw.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(hW, 0, H), gp_Pnt(-hW, 0, H)));
    rw.Add(BRepBuilderAPI_MakeEdge(gp_Pnt(-hW, 0, H), gp_Pnt(-hW, 0, 0)));
    TopoDS_Face rf = BRepLib_MakeFace(rw.Wire()).Face();
    // Use the wing wire as spine
    BRepOffsetAPI_MakePipeShell wingPipe(ww.Wire());
    wingPipe.Add(rw.Wire());
    wingPipe.SetMode(Standard_False);
    wingPipe.Build();
    if (wingPipe.IsDone()) builder.Add(compound, wingPipe.Shape());
  }

  return compound;
}

TopoDS_Shape create_frog(const frog_params &params,
                          const gp_Pnt &position,
                          const gp_Dir &direction,
                          const gp_Dir &upDir) {
  TopoDS_Shape s = create_frog(params);
  gp_Ax3 src(gp::Origin(), gp::DZ(), gp::DX()), tgt(position, upDir, direction);
  gp_Trsf tr; tr.SetTransformation(tgt, src);
  return BRepBuilderAPI_Transform(s, tr).Shape();
}

// =========================================================================
// TRACK: 33. Turnout (单开道岔)
// =========================================================================
TopoDS_Shape create_turnout(const turnout_params &params) {
  if (params.turnoutNo <= 0 || params.gauge <= 0)
    throw Standard_ConstructionError("Invalid turnout dimensions");

  double gauge = params.gauge, halfGauge = gauge / 2.0;
  double frogAngle = atan2(1.0, (double)params.turnoutNo);
  double handSign = params.isLeftHand ? 1.0 : -1.0;
  double totalLen = gauge * params.turnoutNo;
  double frogLen = params.frogLength > 0 ? params.frogLength : totalLen * 0.3;
  double switchLen = params.switchRailLength > 0 ? params.switchRailLength : totalLen * 0.35;
  double R = params.leadCurveRadius > 0 ? params.leadCurveRadius : totalLen * 1.5;

  BRep_Builder builder;
  TopoDS_Compound compound;
  builder.MakeCompound(compound);

  // --- Stock rails (基本轨) ---
  // Straight stock rail
  gp_Pnt sl1(0, -halfGauge, 0), sl2(totalLen, -halfGauge, 0);
  TopoDS_Shape sRail = BRepPrimAPI_MakeCylinder(gp_Ax2(sl1, gp_Dir(sl2.XYZ()-sl1.XYZ())),
                                                  params.railHeadWidth/2, totalLen).Shape();
  builder.Add(compound, sRail);
  // Straight stock rail (other side)
  gp_Pnt sr1(0, halfGauge, 0), sr2(totalLen, halfGauge, 0);
  TopoDS_Shape sRail2 = BRepPrimAPI_MakeCylinder(gp_Ax2(sr1, gp_Dir(sr2.XYZ()-sr1.XYZ())),
                                                   params.railHeadWidth/2, totalLen).Shape();
  builder.Add(compound, sRail2);

  // --- Switch rail (尖轨) ---
  switch_rail_params srp;
  srp.length = switchLen; srp.railHeight = params.railHeight;
  srp.railHeadWidth = params.railHeadWidth; srp.railBaseWidth = params.railBaseWidth;
  srp.tipWidth = 2; srp.curveRadius = R; srp.isLeftHand = params.isLeftHand;
  builder.Add(compound, create_switch_rail(srp, gp_Pnt(0, halfGauge * handSign, 0), gp::DX(), gp::DZ()));

  // --- Guide curve rail (导曲线轨) ---
  double curveStart = switchLen * 0.8;
  double curveEnd = totalLen - frogLen * 0.9;
  int nCurvePts = 30;
  std::vector<gp_Pnt> curvePts;
  for (int i = 0; i <= nCurvePts; ++i) {
    double t = (double)i / nCurvePts;
    double a = frogAngle * t * handSign;
    double x = curveStart + t * (curveEnd - curveStart);
    double y = halfGauge * handSign - R * (1 - cos(a)) * handSign;
    curvePts.push_back(gp_Pnt(x, y, 0));
  }
  BRepBuilderAPI_MakeWire cWire;
  for (int i = 0; i < nCurvePts; ++i)
    cWire.Add(BRepBuilderAPI_MakeEdge(curvePts[i], curvePts[i+1]));
  gp_Circ cs(gp_Ax2(curvePts[0], gp::DZ()), params.railHeadWidth/2);
  TopoDS_Wire cSec = BRepBuilderAPI_MakeWire(BRepBuilderAPI_MakeEdge(cs));
  BRepOffsetAPI_MakePipeShell cPipe(cWire.Wire());
  cPipe.Add(cSec); cPipe.SetMode(Standard_True); cPipe.Build();
  if (cPipe.IsDone()) builder.Add(compound, cPipe.Shape());

  // --- Frog (辙叉) ---
  frog_params fp; fp.turnoutNo = params.turnoutNo; fp.gauge = gauge;
  fp.railHeight = params.railHeight; fp.railHeadWidth = params.railHeadWidth;
  fp.railBaseWidth = params.railBaseWidth;
  builder.Add(compound, create_frog(fp, gp_Pnt(totalLen - frogLen, 0, 0), gp::DX(), gp::DZ()));

  // --- Guard rails (护轨) — short rails inside stock rails at frog ---
  for (int side = -1; side <= 1; side += 2) {
    double grLen = frogLen * 0.5;
    double grX = totalLen - frogLen * 0.7;
    double grY = side * (halfGauge - 30);
    gp_Pnt g1(grX, grY, 0), g2(grX + grLen, grY, 0);
    builder.Add(compound, BRepPrimAPI_MakeCylinder(gp_Ax2(g1, gp_Dir(g2.XYZ()-g1.XYZ())),
                                                     params.railBaseWidth*0.3, grLen).Shape());
  }

  // --- Sleepers (岔枕) — variable length ---
  int nSleepers = std::max(5, params.sleeperCount);
  double spSpacing = params.sleeperSpacing > 0 ? params.sleeperSpacing : totalLen / nSleepers;
  for (int i = 0; i < nSleepers; ++i) {
    double x = i * spSpacing;
    double t = x / totalLen;
    double sLen = 2500 + 300 * t;  // sleeper length increases along turnout
    double sH = 200;
    builder.Add(compound, BRepPrimAPI_MakeBox(gp_Pnt(x - spSpacing/2, -sLen/2, -sH),
                                                spSpacing * 0.8, sLen, sH).Shape());
  }

  return compound;
}

TopoDS_Shape create_turnout(const turnout_params &params,
                             const gp_Pnt &position,
                             const gp_Dir &direction,
                             const gp_Dir &upDir) {
  TopoDS_Shape s = create_turnout(params);
  gp_Ax3 src(gp::Origin(), gp::DZ(), gp::DX()), tgt(position, upDir, direction);
  gp_Trsf tr; tr.SetTransformation(tgt, src);
  return BRepBuilderAPI_Transform(s, tr).Shape();
}

// =========================================================================
// TRACK: 34. Frog Auto-Calculation (辙叉自动查表)
// =========================================================================
frog_calculated_params calculate_frog_params(int turnoutNo, double gauge) {
  frog_calculated_params p; p.turnoutNo = turnoutNo;
  p.frogAngle = atan2(1.0, (double)turnoutNo);
  double N = (double)turnoutNo;

  // Standard lookup tables per Chinese railway specs
  p.frogTotalLength = gauge * N * 0.28;
  p.frogPointLength = p.frogTotalLength * 0.55;
  p.wingRailLength  = p.frogTotalLength * 0.6;
  p.guardRailLength = p.frogTotalLength * 0.4;
  p.guardFlangeGroove = 44.0;
  p.throatWidth = gauge * 0.02;

  switch (turnoutNo) {
    case 9:  p.leadCurveRadius = 180000; p.switchRailLength = 6450; break;
    case 12: p.leadCurveRadius = 350000; p.switchRailLength = 7700; break;
    case 18: p.leadCurveRadius = 800000; p.switchRailLength =12500; break;
    case 30: p.leadCurveRadius =2700000; p.switchRailLength =15400; break;
    case 42: p.leadCurveRadius =5000000; p.switchRailLength =19200; break;
    default: p.leadCurveRadius = 350000; p.switchRailLength = 7700; break;
  }
  return p;
}

// =========================================================================
// TRACK: 35. Rail Pair (轨排对) — 左右股钢轨沿中心线
// =========================================================================
TopoDS_Shape create_rail_pair(const rail_pair_params &params) {
  if (params.centerline.size() < 2 || params.gauge <= 0)
    throw Standard_ConstructionError("Invalid rail pair dimensions");

  double halfGauge = params.gauge / 2.0;
  double R = params.railHeadWidth / 2.0;
  double se = params.superElevation;
  double segLen = std::max(params.centerline[0].Distance(params.centerline[1]), 100.0);

  BRep_Builder builder;
  TopoDS_Compound compound;
  builder.MakeCompound(compound);

  // Build centerline path
  BRepBuilderAPI_MakeWire pathWire;
  for (size_t i = 0; i < params.centerline.size() - 1; ++i)
    pathWire.Add(BRepBuilderAPI_MakeEdge(params.centerline[i], params.centerline[i+1]));
  TopoDS_Wire clWire = pathWire.Wire();

  // Generate left rail (offset -halfGauge perpendicular to centerline)
  // Generate right rail (offset +halfGauge perpendicular to centerline)
  for (int side = -1; side <= 1; side += 2) {
    double yOff = side * halfGauge;
    double zOff = (side == 1) ? se : 0;  // superelevation lifts outer rail

    BRepBuilderAPI_MakeWire railWire;
    for (size_t i = 0; i < params.centerline.size() - 1; ++i) {
      gp_Vec tangent(params.centerline[i], params.centerline[i+1]);
      if (tangent.Magnitude() < Precision::Confusion()) continue;
      gp_Dir dir(tangent);
      gp_Dir perp = gp_Dir(0, 0, 1).Crossed(dir);  // perpendicular in XY plane

      gp_Pnt p1 = params.centerline[i].Translated(gp_Vec(perp.XYZ() * yOff));
      p1.SetZ(p1.Z() + zOff);
      gp_Pnt p2 = params.centerline[i+1].Translated(gp_Vec(perp.XYZ() * yOff));
      p2.SetZ(p2.Z() + zOff);
      railWire.Add(BRepBuilderAPI_MakeEdge(p1, p2));
    }
    // Sweep section along rail path
    gp_Ax2 secAx(params.centerline[0], gp::DZ());
    gp_Circ secCirc(secAx, R);
    TopoDS_Wire secW = BRepBuilderAPI_MakeWire(BRepBuilderAPI_MakeEdge(secCirc)).Wire();
    Handle(ShapeFix_Wire) fixer = new ShapeFix_Wire; fixer->Load(secW); fixer->Perform();
    BRepOffsetAPI_MakePipeShell pipe(railWire.Wire());
    pipe.Add(fixer->Wire()); pipe.SetMode(Standard_True); pipe.Build();
    if (pipe.IsDone()) builder.Add(compound, pipe.Shape());
  }

  return compound;
}

TopoDS_Shape create_rail_pair(const rail_pair_params &params,
                               const gp_Pnt &position,
                               const gp_Dir &direction,
                               const gp_Dir &upDir) {
  TopoDS_Shape s = create_rail_pair(params);
  gp_Ax3 src(gp::Origin(), gp::DZ(), gp::DX()), tgt(position, upDir, direction);
  gp_Trsf tr; tr.SetTransformation(tgt, src);
  return BRepBuilderAPI_Transform(s, tr).Shape();
}

// =========================================================================
// TRACK: 36. Sleeper Layout (轨枕阵列)
// =========================================================================
TopoDS_Shape create_sleeper_layout(const sleeper_layout_params &params) {
  if (params.centerline.size() < 2) throw Standard_ConstructionError("Need at least 2 points");

  BRep_Builder builder;
  TopoDS_Compound compound;
  builder.MakeCompound(compound);

  // Walk along centerline, placing sleepers at spacing intervals
  double totalLen = 0;
  std::vector<double> segLens;
  for (size_t i = 0; i < params.centerline.size() - 1; ++i) {
    double d = params.centerline[i].Distance(params.centerline[i+1]);
    segLens.push_back(d); totalLen += d;
  }

  double pos = 0; size_t segIdx = 0;
  while (pos < totalLen && segIdx < segLens.size()) {
    double localT = pos;
    for (size_t i = 0; i < segIdx; ++i) localT -= segLens[i];
    double t = segLens[segIdx] > 0 ? localT / segLens[segIdx] : 0;
    gp_Pnt pt = params.centerline[segIdx].Translated(
        gp_Vec(params.centerline[segIdx+1].XYZ() - params.centerline[segIdx].XYZ()) * t);

    gp_Pnt sp(pt.X() - params.spacing/2, pt.Y() - params.length/2, pt.Z() - params.height);
    TopoDS_Shape sleeper = BRepPrimAPI_MakeBox(sp, params.spacing*0.7, params.length, params.height).Shape();
    builder.Add(compound, sleeper);

    pos += params.spacing;
    while (segIdx < segLens.size() && pos >= 0) {
      double segEnd = 0; for (size_t j = 0; j <= segIdx; ++j) segEnd += segLens[j];
      if (pos < segEnd) break;
      segIdx++;
    }
  }

  return compound;
}

// =========================================================================
// TRACK: 37. Track Section (轨道区段装配)
// =========================================================================
TopoDS_Shape create_track_section(const track_section_params &params) {
  if (params.centerline.size() < 2) throw Standard_ConstructionError("Need at least 2 points");

  BRep_Builder builder;
  TopoDS_Compound compound;
  builder.MakeCompound(compound);

  // 1. Rail pair
  rail_pair_params rpp;
  rpp.centerline = params.centerline; rpp.gauge = params.gauge;
  rpp.superElevation = params.superElevation;
  rpp.railHeight = params.railHeight; rpp.railHeadWidth = params.railHeadWidth;
  rpp.railBaseWidth = params.railBaseWidth;
  builder.Add(compound, create_rail_pair(rpp));

  // 2. Sleeper layout
  sleeper_layout_params slp;
  slp.centerline = params.centerline;
  slp.length = params.sleeperLength; slp.width = params.sleeperWidth;
  slp.height = params.sleeperHeight; slp.spacing = params.sleeperSpacing;
  builder.Add(compound, create_sleeper_layout(slp));

  // 3. Ballast bed
  double totalLen = 0;
  for (size_t i = 0; i < params.centerline.size() - 1; ++i)
    totalLen += params.centerline[i].Distance(params.centerline[i+1]);
  ballast_params bp; bp.topWidth = params.ballastTopWidth;
  bp.thickness = params.ballastThickness; bp.sideSlope = params.ballastSlope;
  bp.centerlineSegments = {};
  for (size_t i = 0; i < params.centerline.size() - 1; ++i)
    bp.centerlineSegments.push_back({centerline_curve_type::LINE, {params.centerline[i], params.centerline[i+1]}});
  builder.Add(compound, create_ballast(bp));

  return compound;
}

TopoDS_Shape create_track_section(const track_section_params &params,
                                   const gp_Pnt &position,
                                   const gp_Dir &direction,
                                   const gp_Dir &upDir) {
  TopoDS_Shape s = create_track_section(params);
  gp_Ax3 src(gp::Origin(), gp::DZ(), gp::DX()), tgt(position, upDir, direction);
  gp_Trsf tr; tr.SetTransformation(tgt, src);
  return BRepBuilderAPI_Transform(s, tr).Shape();
}

// =========================================================================
// TRACK: 37. Straight Track (直线轨道段)
// =========================================================================
TopoDS_Shape create_straight_track(const straight_track_params &params) {
  gp_Vec dir(params.startPoint, params.endPoint);
  double len = dir.Magnitude();
  if (len <= Precision::Confusion()) throw Standard_ConstructionError("Zero length track");

  double halfGauge = params.gauge / 2.0;
  double R = params.railHeadWidth / 2.0;
  gp_Dir tang(dir);

  BRep_Builder builder; TopoDS_Compound compound; builder.MakeCompound(compound);

  // Left & right rails — simple cylinders along direction
  gp_Dir perp = gp_Dir(0, 0, 1).Crossed(tang);
  for (int side = -1; side <= 1; side += 2) {
    gp_Pnt start = params.startPoint.Translated(gp_Vec(perp.XYZ() * side * halfGauge));
    builder.Add(compound, BRepPrimAPI_MakeCylinder(gp_Ax2(start, tang), R, len).Shape());
  }

  // Sleepers
  int nSleepers = std::max(1, (int)(len / params.sleeperSpacing));
  for (int i = 0; i <= nSleepers; ++i) {
    double t = (double)i / nSleepers;
    gp_Pnt sp = params.startPoint.Translated(gp_Vec(tang.XYZ() * len * t));
    gp_Pnt so(sp.X() - params.sleeperSpacing/2, sp.Y() - params.sleeperLength/2, sp.Z() - params.sleeperHeight);
    builder.Add(compound, BRepPrimAPI_MakeBox(so, params.sleeperSpacing*0.7, params.sleeperLength, params.sleeperHeight).Shape());
  }

  // Ballast
  ballast_params bp; bp.topWidth = params.ballastTopWidth;
  bp.thickness = params.ballastThickness; bp.sideSlope = params.ballastSlope;
  bp.centerlineSegments = {{centerline_curve_type::LINE, {params.startPoint, params.endPoint}}};
  builder.Add(compound, create_ballast(bp));

  return compound;
}

TopoDS_Shape create_straight_track(const straight_track_params &params,
                                    const gp_Pnt &position, const gp_Dir &direction, const gp_Dir &upDir) {
  TopoDS_Shape s = create_straight_track(params);
  gp_Ax3 src(gp::Origin(), gp::DZ(), gp::DX()), tgt(position, upDir, direction);
  gp_Trsf tr; tr.SetTransformation(tgt, src);
  return BRepBuilderAPI_Transform(s, tr).Shape();
}

// =========================================================================
// TRACK: 38. Curve Track (曲线轨道段) — 含超高
// =========================================================================
TopoDS_Shape create_curve_track(const curve_track_params &params) {
  double R = params.curveRadius;
  if (R <= Precision::Confusion()) throw Standard_ConstructionError("Invalid curve radius");

  double totalAngle = std::abs(params.sweepAngle);
  if (totalAngle < Precision::Angular()) throw Standard_ConstructionError("Invalid sweep angle");

  double halfGauge = params.gauge / 2.0;
  double SE = params.superElevation;
  int nSeg = std::max(10, (int)(totalAngle * R / 1000));
  double dA = params.sweepAngle / nSeg;
  double a0 = params.startAngle;

  BRep_Builder builder;
  TopoDS_Compound compound;
  builder.MakeCompound(compound);

  // Rail section profile (standard 14-point)
  double H = params.railHeight, hH = H * 0.36, bH = H * 0.18;
  double hW = params.railHeadWidth / 2, bW = params.railBaseWidth / 2, wT = bW * 0.22;

  auto makeRailInCurve = [&](double yOff, double zOff) {
    for (int i = 0; i < nSeg; ++i) {
      double a1 = a0 + i * dA;
      gp_Pnt c(R * cos(a1), R * sin(a1), 0);
      gp_Dir tang(-sin(a1), cos(a1), 0);
      gp_Dir rad(cos(a1), sin(a1), 0);

      gp_Pnt p1 = c.Translated(gp_Vec(rad.XYZ() * yOff));
      p1.SetZ(zOff);

      // Simple rail segment as a tilted cylinder along arc
      double segLen = R * std::abs(dA);
      TopoDS_Shape railSeg = BRepPrimAPI_MakeCylinder(gp_Ax2(p1, tang), hW, segLen).Shape();
      builder.Add(compound, railSeg);
    }
  };

  // Inner rail
  for (int i = 0; i < nSeg; ++i) {
    double a1 = a0 + i * dA, a2 = a1 + dA;
    gp_Pnt c(R * cos(a1), R * sin(a1), 0);
    gp_Pnt cn(R * cos(a2), R * sin(a2), 0);
    gp_Dir rad(cos(a1), sin(a1), 0);

    gp_Pnt pIn = c.Translated(gp_Vec(rad.XYZ() * -halfGauge));
    gp_Pnt pInN = cn.Translated(gp_Vec(rad.XYZ() * -halfGauge));
    double segLen = pIn.Distance(pInN);
    gp_Vec v(pIn, pInN);
    if (v.Magnitude() > Precision::Confusion())
      builder.Add(compound, BRepPrimAPI_MakeCylinder(gp_Ax2(pIn, gp_Dir(v)), hW, segLen).Shape());
  }

  // Outer rail (with superelevation)
  for (int i = 0; i < nSeg; ++i) {
    double a1 = a0 + i * dA, a2 = a1 + dA;
    gp_Pnt c(R * cos(a1), R * sin(a1), 0);
    gp_Pnt cn(R * cos(a2), R * sin(a2), 0);
    gp_Dir rad(cos(a1), sin(a1), 0);

    gp_Pnt pOut = c.Translated(gp_Vec(rad.XYZ() * halfGauge));
    pOut.SetZ(SE);
    gp_Pnt pOutN = cn.Translated(gp_Vec(rad.XYZ() * halfGauge));
    pOutN.SetZ(SE);
    double segLen2 = pOut.Distance(pOutN);
    gp_Vec v2(pOut, pOutN);
    if (v2.Magnitude() > Precision::Confusion())
      builder.Add(compound, BRepPrimAPI_MakeCylinder(gp_Ax2(pOut, gp_Dir(v2)), hW, segLen2).Shape());
  }

  // Sleepers along curve
  int nSleepers = std::max(2, (int)(totalAngle * R / params.sleeperSpacing));
  for (int s = 0; s <= nSleepers; ++s) {
    double a = a0 + totalAngle * s / nSleepers;
    double x = R * cos(a), y = R * sin(a);
    double sl = 2500, sw = params.sleeperWidth, sh = params.sleeperHeight;
    builder.Add(compound, BRepPrimAPI_MakeBox(gp_Pnt(x - sw/2, y - sl/2, -sh), sw, sl, sh).Shape());
  }

  return compound;
}

TopoDS_Shape create_curve_track(const curve_track_params &params,
                                 const gp_Pnt &position, const gp_Dir &direction, const gp_Dir &upDir) {
  TopoDS_Shape s = create_curve_track(params);
  gp_Ax3 src(gp::Origin(), gp::DZ(), gp::DX()), tgt(position, upDir, direction);
  gp_Trsf tr; tr.SetTransformation(tgt, src);
  return BRepBuilderAPI_Transform(s, tr).Shape();
}

// =========================================================================
// 9b. Registration Arm Bracket (定位器底座 L型金具)
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

  // Band clamp — centered at half-band position along X
  double bw2 = bWidth/2;
  b.Add(c, BRepAlgoAPI_Cut(
    BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(-bw2, 0, 0), gp::DX()), R + bThick, bWidth).Shape(),
    BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(-bw2, 0, 0), gp::DX()), R, bWidth + 2).Shape()).Shape());

  // Vertical plate — from tube bottom (Z=-R) extending down
  b.Add(c, BRepPrimAPI_MakeBox(gp_Pnt(-bThick/2, -bkW/2, -R - bkH), bThick, bkW, bkH).Shape());

  // Pin bolt at bottom of plate2
  if (params.mountHoleDiameter > 0) {
    double br = params.mountHoleDiameter / 2.0;
    double bz = -R - bkH * 0.85;
    b.Add(c, BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(-bThick/2 - br*0.3, 0, bz), gp::DX()), br, bThick + br*0.6).Shape());
  }

  return c;
}

TopoDS_Shape create_reg_arm_bracket(const reg_arm_bracket_params &params,
                                     const gp_Pnt &position,
                                     const gp_Dir &tubeDir,
                                     const gp_Dir &upDir) {
  TopoDS_Shape s = create_reg_arm_bracket(params);
  gp_Ax3 src(gp::Origin(), gp::DZ(), gp::DX()), tgt(position, upDir, tubeDir);
  gp_Trsf tr; tr.SetTransformation(tgt, src);
  return BRepBuilderAPI_Transform(s, tr).Shape();
}

} // namespace topo
} // namespace flywave
