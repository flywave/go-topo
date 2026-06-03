#include "primitives_railway.hh"
#include <BRep_Builder.hxx>
#include <BRepMesh_IncrementalMesh.hxx>
#include <StlAPI_Writer.hxx>
#include <Standard_Failure.hxx>
#include <gp_Pnt.hxx>
#include <iostream>
#include <sys/stat.h>

using namespace flywave::topo;

void ensure_dir(const std::string &path) { mkdir(path.c_str(), 0755); }

bool exportShapeToStl(const TopoDS_Shape &shape, const std::string &path,
                      double tolerance = 0.5, double angularTolerance = 0.3) {
  if (shape.IsNull()) return false;
  BRepMesh_IncrementalMesh mesher(shape, tolerance, false, angularTolerance);
  mesher.Perform();
  return StlAPI_Writer().Write(shape, path.c_str());
}

bool test_export(const TopoDS_Shape &shape, const std::string &name) {
  ensure_dir("./test_output");
  std::cout << "Exporting " << name << "... ";
  bool ok = exportShapeToStl(shape, "./test_output/" + name + ".stl");
  std::cout << (ok ? "OK" : "FAIL") << std::endl;
  return ok;
}

// === OCS 接触网体系 ===

void test_rod_insulator() {
  std::cout << "\n=== Rod Insulator ===" << std::endl;
  rod_insulator_params p;
  p.type = rod_insulator_type::SOLID;
  p.height = 500; p.outerDiameter = 80; p.innerDiameter = 0;
  p.shedDiameter = 140; p.shedSpacing = 55; p.shedCount = 8;
  p.endFitting = end_fitting_type::FLANGE;
  p.flangeDiameter = 100; p.flangeBoltSpacing = 70; p.flangeBoltDiameter = 12;
  test_export(create_rod_insulator(p), "rod_insulator");
}

void test_steel_mast() {
  std::cout << "\n=== Steel Mast ===" << std::endl;
  steel_mast_params p;
  p.type = steel_mast_type::H_BEAM;
  p.height = 8000; p.topWidth = 200; p.bottomWidth = 350;
  p.wallThickness = 10; p.flangeThickness = 16; p.flangeWidth = 450;
  p.anchorSpacing = 200; p.anchorDiameter = 24; p.segmentCount = 1;
  test_export(create_steel_mast(p), "steel_mast_hbeam");

  p.type = steel_mast_type::LATTICE;
  p.height = 8000; p.topWidth = 300; p.bottomWidth = 600;
  p.wallThickness = 8; p.segmentCount = 1;
  test_export(create_steel_mast(p), "steel_mast_lattice");
}

void test_cross_arm() {
  std::cout << "\n=== Cross Arm ===" << std::endl;
  cross_arm_params p;
  p.type = cross_arm_type::DOUBLE_FORK;
  p.beamLength = 3000; p.beamHeight = 200; p.beamWidth = 80; p.beamThickness = 6;
  p.beamSpacing = 1500;  // 上下梁间距=腕臂上下底座安装距
  p.braceLength = 1800; p.braceDiameter = 50;
  p.mountHeight = 6000; p.boltSpacing = 100; p.boltDiameter = 16; p.boltCount = 4;
  test_export(create_cross_arm(p), "cross_arm");
}

void test_registration_arm() {
  std::cout << "\n=== Registration Arm ===" << std::endl;
  registration_arm_params p;
  p.type = registration_arm_type::STRAIGHT;
  p.length = 800; p.tubeWidth = 35; p.tubeHeight = 20; p.wallThickness = 4; p.angle = 0; p.isReverse = false;
  test_export(create_registration_arm(p), "registration_arm");

  p.type = registration_arm_type::CURVED;
  test_export(create_registration_arm(p), "registration_arm_bow");
}

void test_concrete_mast() {
  std::cout << "\n=== Concrete Mast ===" << std::endl;
  concrete_mast_params p;
  p.sectionType = concrete_mast_section_type::CIRCULAR;
  p.height = 9000; p.topWidth = 250; p.bottomWidth = 350; p.wallThickness = 60;
  test_export(create_concrete_mast(p), "concrete_mast");

  p.sectionType = concrete_mast_section_type::CIRCULAR_HOLED;
  p.holeDiameter = 30; p.holeSpacingV = 600; p.holeSpacingH = 200;
  p.firstHoleOffset = 500; p.holeRowCount = 4; p.holesPerRow = 2;
  test_export(create_concrete_mast(p), "concrete_mast_holed");

  p.sectionType = concrete_mast_section_type::RECTANGULAR;
  p.topWidth = 250; p.bottomWidth = 350; p.wallThickness = 60;
  p.holeDiameter = 0; p.holeRowCount = 0; p.holesPerRow = 0;
  test_export(create_concrete_mast(p), "concrete_mast_rect");

  p.sectionType = concrete_mast_section_type::RECTANGULAR_HOLED;
  p.topWidth = 250; p.bottomWidth = 400; p.wallThickness = 0;
  p.holeDiameter = 240; p.holeSpacingV = 500; p.firstHoleOffset = 300;
  p.holeRowCount = 0; p.holesPerRow = 0;
  test_export(create_concrete_mast(p), "concrete_mast_rect_holed");
}

void test_head_span() {
  std::cout << "\n=== Head Span ===" << std::endl;
  head_span_params p;
  p.span = 30000; p.hangPointCount = 4; p.hangPointSpacing = 7500;
  p.crossCatenaryDiameter = 12; p.crossCatenarySag = 1500;
  p.upperRopeDiameter = 8; p.lowerRopeDiameter = 6; p.insulatorLength = 500;
  test_export(create_head_span(p), "head_span");
}

void test_transverse_span() {
  std::cout << "\n=== Transverse Span ===" << std::endl;
  transverse_span_params p;
  p.span = 20000; p.beamHeight = 800; p.beamWidth = 500; p.beamThickness = 12;
  p.mastHeight = 8000; p.mastWidth = 400;
  p.beamType = beam_section_type::TRUSS;
  test_export(create_transverse_span(p), "transverse_span_truss");

  p.beamType = beam_section_type::BOX;
  test_export(create_transverse_span(p), "transverse_span_box");

  p.beamType = beam_section_type::COMBO;
  test_export(create_transverse_span(p), "transverse_span_combo");
}

void test_hanger_post() {
  std::cout << "\n=== Hanger Post ===" << std::endl;
  hanger_post_params p;
  p.sectionType = hanger_post_section_type::ROUND;
  p.length = 1500; p.sectionSize = 200; p.wallThickness = 10;
  p.topFlangeSize = 300; p.topFlangeThick = 20;
  p.bottomFlangeSize = 250; p.bottomFlangeThick = 16;
  p.boltDiameter = 20; p.boltSpacing = 150;
  test_export(create_hanger_post(p), "hanger_post");
}

void test_portal_frame() {
  std::cout << "\n=== Portal Frame ===" << std::endl;
  portal_frame_params p;
  p.frameHeight = 1200; p.frameWidth = 600;
  p.postDiameter = 80; p.postWallThick = 6;
  p.beamDiameter = 60; p.beamWallThick = 5; p.beamLength = 800;
  p.basePlateLength = 200; p.basePlateWidth = 200; p.basePlateThick = 12;
  p.hangPointCount = 2; p.hangPointSpacing = 300;
  p.boltSpacing = 100; p.boltDiameter = 14;
  test_export(create_portal_frame(p), "portal_frame");
}

void test_suspension_hard_span() {
  std::cout << "\n=== Suspension Hard Span ===" << std::endl;
  suspension_hard_span_params p;
  p.span = 25000; p.mastHeight = 10000; p.mastWidth = 400;
  p.cableDiameter = 16; p.cableSag = 1250;
  p.dropperCableDiameter = 8; p.dropperCount = 5; p.dropperSpacing = 4000;
  p.insulatorLength = 400; p.insulatorDiameter = 80;
  test_export(create_suspension_hard_span(p), "suspension_hard_span");
}

// === 轨道体系 ===

void test_rail() {
  std::cout << "\n=== Rail ===" << std::endl;
  rail_params p;
  p.railHeight = 180.98; p.headWidth = 76.2; p.baseWidth = 152.4;
  p.webThickness = 16.67; p.headHeight = 44.45; p.baseHeight = 30.16;
  p.headRadius = 31.75; p.standardLength = 2000;
  test_export(create_rail(p), "rail_132re");
}

void test_switch_rail() {
  std::cout << "\n=== Switch Rail ===" << std::endl;
  // Straight switch (delegated to create_rail_curve with SWITCH end)
  rail_curve_params rp;
  rp.curve.type = rail_curve_type::LINE;
  rp.curve.startPoint = gp::Origin();
  rp.curve.endPoint = gp_Pnt(7700, 0, 0);
  rp.railHeight = 176; rp.headWidth = 73; rp.baseWidth = 150; rp.webThickness = 16.5;
  rp.endStart.type = end_treatment_type::SWITCH;
  rp.endStart.toeWidth = 2;
  test_export(create_rail_curve(rp), "switch_rail_straight");
  // Curved switch (ARC path)
  rp.curve.type = rail_curve_type::ARC;
  rp.curve.radius = 350000;
  rp.curve.arcDirection = 1;
  rp.curve.controlPoints = {gp_Pnt(3850, 500, 0)};
  test_export(create_rail_curve(rp), "switch_rail_arc");
}

void test_wing_rail() {
  std::cout << "\n=== Wing Rail ===" << std::endl;
  // Straight wing rail
  wing_rail_curve_params wp;
  wp.curve.type = rail_curve_type::LINE;
  wp.curve.startPoint = gp::Origin();
  wp.curve.endPoint = gp_Pnt(3000, 0, 0);
  wp.channelHeight = 120; wp.flangeWidth = 30; wp.webThickness = 12;
  test_export(create_wing_rail_curve(wp), "wing_rail_straight");
  // Bent wing rail (multi-segment: two lines meeting at an angle)
  // Use ARC to approximate the bend
  wp.curve.type = rail_curve_type::ARC;
  wp.curve.radius = 5000;
  wp.curve.arcDirection = 2;
  wp.curve.startPoint = gp_Pnt(0, 0, 0);
  wp.curve.endPoint = gp_Pnt(3000, 300, 0);
  wp.curve.controlPoints = {gp_Pnt(1500, 50, 0)};
  test_export(create_wing_rail_curve(wp), "wing_rail_bent");
}

void test_frog() {
  std::cout << "\n=== Frog ===" << std::endl;
  frog_params p;
  p.turnoutNo = 12; p.gauge = 1435;
  p.railHeight = 176; p.railHeadWidth = 73.02; p.railBaseWidth = 150;
  test_export(create_frog(p), "frog");
  test_export(create_frog(p, gp_Pnt(5000,0,0), gp::DX(), gp::DZ()), "frog_pos");
}

void test_guard_rail() {
  std::cout << "\n=== Guard Rail ===" << std::endl;
  guard_rail_params p;
  p.height = 80; p.headWidth = 93; p.baseWidth = 93;
  p.grooveWidth = 42; p.totalLength = 3600;
  p.gaugeDistance = 42;
  test_export(create_guard_rail(p), "guard_rail");
  test_export(create_guard_rail(p, gp_Pnt(0,0,0), gp_Pnt(3600,0,0)), "guard_rail_line");
}

void test_sleeper() {
  std::cout << "\n=== Sleeper ===" << std::endl;
  sleeper_params p;
  p.shapeType = sleeper_shape_type::RECTANGULAR;
  p.length = 2600; p.width = 300; p.height = 200;
  p.gauge = 1435; p.railBaseWidth = 150; p.grooveDepth = 25; p.spacing = 600;
  test_export(create_sleeper(p), "sleeper_rect");

  p.shapeType = sleeper_shape_type::TRAPEZOIDAL;
  test_export(create_sleeper(p), "sleeper_trap");

  // Multi-groove sleeper (岔枕场景: 4条槽, pos沿枕木长度方向)
  sleeper_line_params sp;
  sp.startPoint = gp_Pnt(-1500, 0, 0);
  sp.endPoint = gp_Pnt(1500, 0, 0);
  sp.width = 300; sp.height = 200; sp.gauge = 1435;
  sp.grooveWidth = 150; sp.grooveDepth = 25;
  sp.grooveYs = {-717.75, -350, 350, 717.75};
  sp.shapeType = 1;
  test_export(create_sleeper_line(sp), "sleeper_multi");
}

void test_ballast() {
  std::cout << "\n=== Ballast ===" << std::endl;
  ballast_params p;
  p.topWidth = 3600; p.thickness = 350; p.sideSlope = 1.5;
  p.centerlineSegments = {{centerline_curve_type::LINE, {gp_Pnt(0, 0, 0), gp_Pnt(5000, 0, 0)}}};
  test_export(create_ballast(p), "ballast");
}

void test_contact_wire() {
  std::cout << "\n=== Contact Wire ===" << std::endl;
  contact_wire_params p;
  p.sectionalArea = 120; p.diameter = 14.5; p.ratedTension = 15;
  p.grooveDepth = 1.5; p.grooveWidth = 2.5; p.bottomRadius = 6.5; p.topRadius = 3.0;
  p.sag = 0;
  test_export(create_contact_wire(p, gp::Origin(), gp_Pnt(1000, 0, 0)), "contact_wire");
  test_export(create_contact_wire(p, gp_Pnt(200, 100, 0), gp_Pnt(1200, 100, 0)), "contact_wire_offset");
  p.sag = 200;
  test_export(create_contact_wire(p, gp::Origin(), gp_Pnt(5000, 0, 0)), "contact_wire_sag");
}

void test_messenger_wire() {
  std::cout << "\n=== Messenger Wire ===" << std::endl;
  messenger_wire_params p;
  p.diameter = 20; p.ratedTension = 20; p.structuralHeight = 1800; p.sag = 500;
  test_export(create_messenger_wire(p, gp::Origin(), gp_Pnt(3000, 0, 0)), "messenger_wire");
  test_export(create_messenger_wire(p, gp_Pnt(200, 100, 50), gp_Pnt(3200, 100, 50)), "messenger_wire_offset");
}

void test_curved_arm() {
  std::cout << "\n=== Curved Arm ===" << std::endl;
  curved_arm_params p;
  p.type = curved_arm_type::ARC;
  p.verticalLength = 500; p.horizontalLength = 800;
  p.bendRadius = 200; p.bendAngle = 90;
  p.outerDiameter = 48; p.wallThickness = 3.5;
  p.flangeThickness = 10; p.boltSpacing = 80; p.boltDiameter = 12;
  test_export(create_curved_arm(p), "curved_arm");
  test_export(create_curved_arm(p, gp_Pnt(200,0,0), gp::DZ(), gp::DX()), "curved_arm_pos");
}

void test_straight_track() {
  std::cout << "\n=== Straight Track ===" << std::endl;
  straight_track_params p;
  p.startPoint = gp_Pnt(0, 0, 0); p.endPoint = gp_Pnt(5000, 0, 0);
  p.gauge = 1435; p.railHeight = 176; p.railHeadWidth = 73.02; p.railBaseWidth = 150;
  p.webThickness = 16.67; p.sleeperLength = 2600; p.sleeperWidth = 300; p.sleeperHeight = 200;
  p.sleeperSpacing = 600;
  p.ballastTopWidth = 3600; p.ballastThickness = 350; p.ballastSlope = 1.5;
  test_export(create_straight_track(p), "straight_track");
}

void test_curve_track() {
  std::cout << "\n=== Curve Track ===" << std::endl;
  curve_track_params p;
  p.curveCenter = gp_Pnt(0, 0, 0);
  p.startAngle = 0; p.sweepAngle = M_PI / 4;
  p.curveRadius = 5000;
  p.gauge = 1435; p.superElevation = 80;
  p.railHeight = 180.98; p.railHeadWidth = 76.2; p.railBaseWidth = 152.4;
  p.webThickness = 16.67;
  p.sleeperLength = 2600; p.sleeperWidth = 300; p.sleeperHeight = 200;
  p.sleeperSpacing = 600;
  p.ballastTopWidth = 3600; p.ballastThickness = 350; p.ballastSlope = 1.5;
  test_export(create_curve_track(p), "curve_track");
}

void test_turnout_new() {
  std::cout << "\n=== Turnout (Element Assembly) ===" << std::endl;
  turnout_assembly_params tap;
  tap.turnoutNo = 12;
  tap.hand = 1;
  tap.gauge = 1435;

  double hg = tap.gauge / 2.0;
  frog_calculated_params fc = calculate_frog_params(12, tap.gauge);
  double swLen = fc.switchRailLength;
  double leadR = fc.leadCurveRadius;

  // Stock rails (LINE)
  rail_curve_params sr;
  sr.curve.type = rail_curve_type::LINE;
  sr.curve.startPoint = gp_Pnt(-swLen - 2000, -hg, 0);
  sr.curve.endPoint = gp_Pnt(fc.frogTotalLength * 1.2, -hg, 0);
  sr.railHeight = 176; sr.headWidth = 73; sr.baseWidth = 150; sr.webThickness = 16.5;
  tap.rails.push_back(sr);
  sr.curve.startPoint = gp_Pnt(-swLen - 2000, hg, 0);
  sr.curve.endPoint = gp_Pnt(fc.frogTotalLength * 1.2, hg, 0);
  tap.rails.push_back(sr);

  // Switch rails (tapered at switch end)
  rail_curve_params sw_r;
  sw_r.curve.type = rail_curve_type::LINE;
  sw_r.curve.startPoint = gp_Pnt(-swLen, -hg, 0);
  sw_r.curve.endPoint = gp_Pnt(0, -hg, 0);
  sw_r.endStart.type = end_treatment_type::SWITCH;
  sw_r.endStart.toeWidth = 2;
  sw_r.railHeight = 176; sw_r.headWidth = 73; sw_r.baseWidth = 150; sw_r.webThickness = 16.5;
  tap.rails.push_back(sw_r);
  // Curved switch on diverging side
  sw_r.curve.type = rail_curve_type::ARC;
  sw_r.curve.startPoint = gp_Pnt(-swLen, hg, 0);
  sw_r.curve.endPoint = gp_Pnt(0, hg, 0);
  sw_r.curve.radius = leadR;
  sw_r.curve.arcDirection = 1;
  tap.rails.push_back(sw_r);

  // Sleepers
  int sc = 8;
  for (int i = 0; i < sc; ++i) {
    double t = (double)i / sc;
    double x = -swLen + t * (fc.frogTotalLength * 1.2 + swLen);
    double sl = 2500 + t * 200;
    sleeper_line_params slp;
    slp.startPoint = gp_Pnt(x, -sl / 2, 0);
    slp.endPoint = gp_Pnt(x, sl / 2, 0);
    slp.width = 260; slp.height = 200; slp.gauge = tap.gauge;
    tap.sleepers.push_back(slp);
  }

  test_export(create_turnout_assembly(tap), "turnout_assembly");
}

void test_turnout() {
  std::cout << "\n=== Turnout ===" << std::endl;
  turnout_params p;
  p.turnoutNo = 12; p.isLeftHand = true; p.gauge = 1435;
  p.railHeight = 180.98; p.railHeadWidth = 76.2; p.railBaseWidth = 152.4;
  p.webThickness = 16.67;
  p.switchRailLength = 7700; p.leadCurveRadius = 350000;
  p.frogLength = 6050; p.sleeperCount = 50; p.sleeperSpacing = 600;
  test_export(create_turnout(p), "turnout");
}

// === 装配 ===

void test_mast_assembly() {
  std::cout << "\n=== Mast Assembly ===" << std::endl;
  mast_assembly_params p;
  p.mastType = 2; p.mastHeight = 8000; p.cantileverType = 2;
  p.hasCrossArm = false; p.armDiameter = 60; p.stagger = 300;
  p.compType = 0; p.ratedTension = 0; p.hasGuyWire = false;
  test_export(create_mast_assembly(p), "mast_assembly");
}

void test_mast_bracket() {
  std::cout << "\n=== Mast Bracket ===" << std::endl;
  mast_bracket_params p;
  p.boltSpacing = 200; p.boltDiameter = 18;
  p.height = 300; p.width = 200; p.thickness = 12;
  p.insulatorBoltSpacing = 150; p.insulatorBoltDiameter = 16;
  p.mountAngle = 0;
  test_export(create_mast_bracket(p), "mast_bracket");
  test_export(create_mast_bracket(p, gp_Pnt(500,0,0), gp::DX(), gp::DZ()), "mast_bracket_pos");
  p.mountAngle = 15;
  test_export(create_mast_bracket(p), "mast_bracket_angle");
}

void test_reg_arm_bracket() {
  std::cout << "\n=== Reg Arm Bracket ===" << std::endl;
  reg_arm_bracket_params p;
  p.tubeDiameter = 60; p.bandWidth = 50; p.bandThickness = 6;
  p.bracketHeight = 120; p.bracketThickness = 8; p.bracketWidth = 40;
  p.mountHoleDiameter = 20;
  test_export(create_reg_arm_bracket(p), "reg_arm_bracket");
}

void test_guy_wire() {
  std::cout << "\n=== Guy Wire ===" << std::endl;
  guy_wire_params p;
  p.length = 3000; p.diameter = 16; p.angle = 45; p.ratedTension = 50;
  p.hasInsulator = false;
  p.anchorRodDiameter = 20; p.anchorRodLength = 800;
  p.anchorPlateLength = 300; p.anchorPlateWidth = 200;
  test_export(create_guy_wire(p), "guy_wire");
  test_export(create_guy_wire(p, gp_Pnt(2121, 0, -2121), gp::Origin(), gp::DZ()), "guy_wire_pos");
  p.hasInsulator = true; p.insulatorCount = 3;
  test_export(create_guy_wire(p), "guy_wire_insulator");
}

void test_dropper() {
  std::cout << "\n=== Dropper ===" << std::endl;
  dropper_params p;
  p.length = 1500; p.wireDiameter = 6; p.clampLength = 30;
  p.clampWidth = 20; p.clampThickness = 8; p.conductive = true;
  test_export(create_dropper(p), "dropper");
  test_export(create_dropper(p, gp_Pnt(1000, 0, 0), gp::DZ()), "dropper_pos");
}

void test_ocs_foundation() {
  std::cout << "\n=== OCS Foundation ===" << std::endl;
  ocs_foundation_params p;
  p.type = foundation_type::FLANGE;
  p.height = 2000; p.width = 1200; p.length = 1200;
  p.flangeThickness = 30; p.anchorCount = 4;
  p.anchorDiameter = 24; p.anchorLength = 600; p.anchorSpacing = 800;
  test_export(create_ocs_foundation(p), "ocs_foundation_flange");
  test_export(create_ocs_foundation(p, gp_Pnt(5000,0,0), gp::DZ(), gp::DX()), "ocs_foundation_pos");

  p.type = foundation_type::DIRECT_BURIED;
  p.flangeThickness = 0; p.anchorCount = 0;
  test_export(create_ocs_foundation(p), "ocs_foundation_buried");

  p.type = foundation_type::BORED_PILE;
  p.length = 800; p.width = 800;
  test_export(create_ocs_foundation(p), "ocs_foundation_pile");
}

void test_retarder_point() {
  std::cout << "\n=== Retarder Point ===" << std::endl;
  retarder_point_params p;
  p.side = 1; p.type = 1; p.mountType = 1;
  p.height = 200; p.bodyDiameter = 70; p.capDiameter = 82;
  p.capHeight = 28; p.transitionHeight = 18;
  p.armLength = 60; p.armWidth = 20; p.armThickness = 20;
  p.boltDiameter = 18; p.portDiameter = 18;
  test_export(create_retarder_point(p), "retarder_point");
  test_export(create_retarder_point(p, gp_Pnt(500,0,0), gp::DX(), gp::DZ()), "retarder_point_pos");
}

void test_fastener() {
  std::cout << "\n=== Fastener ===" << std::endl;
  fastener_params p;
  p.spacing = 600; p.gauge = 1435;
  p.padThickness = 10; p.padLength = 200; p.padWidth = 160;
  test_export(create_fastener(p), "fastener");
  test_export(create_fastener(p, gp_Pnt(0,0,0), gp::DX(), gp::DZ()), "fastener_pos");
}

void test_rail_with_fasteners() {
  std::cout << "\n=== Rail with Fasteners ===" << std::endl;
  BRep_Builder bld; TopoDS_Compound cmp; bld.MakeCompound(cmp);

  // Rail along X axis, base at sleeper-groove level
  double railZ = 192; // sleeper top(200) - grooveDepth(8)
  rail_params rp;
  rp.railHeight = 180.98; rp.headWidth = 76.2; rp.baseWidth = 152.4;
  rp.webThickness = 16.67; rp.headHeight = 44.45; rp.baseHeight = 30.16;
  rp.headRadius = 31.75; rp.standardLength = 3000;
  bld.Add(cmp, create_rail(rp, gp_Pnt(0, 0, railZ), gp_Pnt(3000, 0, railZ)));

  // Sleepers (矩形枕木) along Y, every 600mm
  for (double x = 200; x < 2800; x += 600) {
    sleeper_line_params sl;
    sl.startPoint = gp_Pnt(x, -1100, 0);
    sl.endPoint = gp_Pnt(x, 1100, 0);
    sl.width = 260;
    sl.height = 200;
    sl.grooveDepth = 8;
    sl.grooveWidth = 155;
    sl.grooveYs = {1100};  // 承轨槽在枕木中心
    sl.shapeType = 1;    // RECTANGULAR
    bld.Add(cmp, create_sleeper_line(sl));
  }

  // Fasteners along rail (X), pads on sleeper top
  for (double x = 200; x < 2800; x += 600) {
    fastener_point_params fp;
    fp.position = gp_Pnt(x, 0, railZ);
    fp.railNormal = gp::DY();
    fp.railBaseWidth = 150.0;
    fp.padThickness = 25;
    bld.Add(cmp, create_fastener_point(fp));
  }
  test_export(cmp, "rail_with_fasteners");
}


int main() {
  auto run = [](const char *name, auto fn) {
    std::cout << "\n=== " << name << " ===" << std::endl;
    try { fn(); } catch (const Standard_Failure &e) { std::cerr << "  ERROR: " << e.GetMessageString() << std::endl; }
    catch (const std::exception &e) { std::cerr << "  ERROR: " << e.what() << std::endl; }
    catch (...) { std::cerr << "  ERROR: unknown exception" << std::endl; }
  };

  run("Rod Insulator", test_rod_insulator);
  run("Steel Mast H-Beam", []{ test_export(create_steel_mast(steel_mast_params{
    steel_mast_type::H_BEAM,8000,200,350,10,16,450,200,24,1}), "steel_mast_hbeam"); });
  run("Steel Mast Lattice", []{ test_export(create_steel_mast(steel_mast_params{
    steel_mast_type::LATTICE,8000,300,600,8,12,750,200,24,1}), "steel_mast_lattice"); });
  run("Cross Arm", test_cross_arm);
  run("Registration Arm", test_registration_arm);
  run("Mast Bracket", test_mast_bracket);
  run("Reg Arm Bracket", test_reg_arm_bracket);
  run("Concrete Mast", test_concrete_mast);
  run("Head Span", test_head_span);
  run("Transverse Span", []{
    transverse_span_params p; p.span=20000; p.beamHeight=800; p.beamWidth=500; p.beamThickness=12;
    p.mastHeight=8000; p.mastWidth=400;
    p.beamType=beam_section_type::TRUSS; test_export(create_transverse_span(p),"transverse_span_truss");
    p.beamType=beam_section_type::BOX; test_export(create_transverse_span(p),"transverse_span_box");
  });
  run("Hanger Post", test_hanger_post);
  run("Portal Frame", test_portal_frame);
  run("Suspension Hard Span", test_suspension_hard_span);
  run("Rail 132RE", test_rail);
  run("Switch Rail", test_switch_rail);
  run("Wing Rail", test_wing_rail);
  run("Frog", test_frog);
  run("Guard Rail", test_guard_rail);
  run("Sleeper", test_sleeper);
  run("Contact Wire", test_contact_wire);
  run("Messenger Wire", test_messenger_wire);
  run("Curved Arm", test_curved_arm);
  run("Ballast Straight", []{
    ballast_params p; p.topWidth = 3600; p.thickness = 350; p.sideSlope = 1.5;
    p.centerlineSegments = {{centerline_curve_type::LINE, {gp_Pnt(0,0,0), gp_Pnt(5000,0,0)}}};
    test_export(create_ballast(p), "ballast_straight");
  });
  run("Ballast Curve", []{
    ballast_params p; p.topWidth = 3600; p.thickness = 350; p.sideSlope = 1.5;
    p.centerlineSegments = {{centerline_curve_type::ARC, {gp_Pnt(0,0,0), gp_Pnt(4000,1000,0), gp_Pnt(5000,5000,0)}}};
    test_export(create_ballast(p), "ballast_curve");
  });
  run("Straight Track", test_straight_track);
  run("Curve Track", test_curve_track);
  run("Turnout 12#", test_turnout);
  run("Turnout Graph", test_turnout_new);
  run("Mast Assembly", test_mast_assembly);
  run("Guy Wire", test_guy_wire);
  run("Dropper", test_dropper);
  run("OCS Foundation", test_ocs_foundation);
  run("Retarder Point", test_retarder_point);
  run("Fastener", test_fastener);
  run("Rail with Fasteners", test_rail_with_fasteners);

  std::cout << "\nAll tests completed." << std::endl;
  return 0;
}
