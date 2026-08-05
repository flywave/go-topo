#include "primitives_railway.hh"
#include <BRepBndLib.hxx>
#include <BRep_Builder.hxx>
#include <BRepMesh_IncrementalMesh.hxx>
#include <Bnd_Box.hxx>
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
  p.holeDiameter = 200; p.holeLength = 320; p.holeSpacingV = 600; p.firstHoleOffset = 2800;
  p.holeRowCount = 9; p.holesPerRow = 1;
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
  // 钢轨改造护轨 (43kg 旧钢轨断面, 两端喇叭口)
  guard_rail_curve_params gp;
  gp.profile = rail_profile_type::RAIL;
  gp.curve.type = rail_curve_type::LINE;
  gp.curve.startPoint = gp::Origin();
  gp.curve.endPoint = gp_Pnt(3600, 0, 0);
  test_export(create_guard_rail_curve(gp), "guard_rail_railprofile");
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

// =========================================================================
// 补充测试: 规范对照用 (关键尺寸打印)
// =========================================================================

void report_dims(const std::string &name, const TopoDS_Shape &shape) {
  if (shape.IsNull()) { std::cout << "  [dims] " << name << ": NULL" << std::endl; return; }
  Bnd_Box bb;
  BRepBndLib::Add(shape, bb);
  double x0, y0, z0, x1, y1, z1;
  bb.Get(x0, y0, z0, x1, y1, z1);
  printf("  [dims] %-28s %8.1f x %8.1f x %8.1f mm\n", name.c_str(),
         x1 - x0, y1 - y0, z1 - z0);
}

// --- 腕臂系统 ---
void test_cantilevers() {
  std::cout << "\n=== Cantilevers (腕臂) ===" << std::endl;
  // 平腕臂: Ø60x4 无缝钢管, 仰角 3°
  auto lv = create_level_cantilever(level_cantilever_params{2800, 60, 4, 5300, 3});
  test_export(lv, "level_cantilever");
  report_dims("level_cantilever(Ø60x2800)", lv);
  // 斜腕臂: Ø60x4, 倾角 45°
  auto sl = create_slant_cantilever(slant_cantilever_params{2600, 60, 4, 45});
  test_export(sl, "slant_cantilever");
  report_dims("slant_cantilever(Ø60x2600)", sl);
  // 腕臂斜撑: Ø48x3.5
  auto br = create_cantilever_brace(cantilever_brace_params{1500, 48, 3.5, 30});
  test_export(br, "cantilever_brace");
  report_dims("cantilever_brace(Ø48x1500)", br);
  // 腕臂底座
  auto cb = create_cantilever_base(cantilever_base_params{200, 160, 80, 100, 16, 4});
  test_export(cb, "cantilever_base");
  report_dims("cantilever_base(200x160x80)", cb);
  // 承力索座 (JTMH-95: 线径 ~13.5)
  auto ms = create_mw_saddle(mw_saddle_params{150, 80, 60, 7, 12});
  test_export(ms, "mw_saddle");
  report_dims("mw_saddle(150x80x60)", ms);
}

// --- 补偿装置组件 ---
void test_compensator_parts() {
  std::cout << "\n=== Compensator Parts (补偿装置组件) ===" << std::endl;
  // 坠砣: 圆形铸铁片 Ø380, 厚 75, 中心孔 Ø30, 带径向开口槽
  auto bw = create_balance_weight(balance_weight_params{380, 75, 75, 30});
  test_export(bw, "balance_weight");
  report_dims("balance_weight(Ø380x75)", bw);
  // 坠砣杆: Ø20 圆钢, 长 2000, 顶端横孔 Ø16
  auto wr = create_weight_rod(weight_rod_params{20, 2000, 16});
  test_export(wr, "weight_rod");
  report_dims("weight_rod(Ø20x2000)", wr);
  // 下锚金具三件套
  auto af1 = create_anchor_fitting(anchor_fitting_params{anchor_fitting_type::ROD_AND_RING, 800, 24});
  test_export(af1, "anchor_fitting_rod_ring");
  report_dims("rod_ring(L800 Ø24)", af1);
  auto af2 = create_anchor_fitting(anchor_fitting_params{anchor_fitting_type::DOUBLE_EAR, 400, 30});
  test_export(af2, "anchor_fitting_double_ear");
  report_dims("double_ear(L400 Ø30)", af2);
  auto af3 = create_anchor_fitting(anchor_fitting_params{anchor_fitting_type::WEDGE_CLAMP, 300, 40});
  test_export(af3, "anchor_fitting_wedge_clamp");
  report_dims("wedge_clamp(L300 Ø40)", af3);
}

// --- 线索与线岔 ---
void test_cables_and_crossing() {
  std::cout << "\n=== Cables & Crossing (悬索/定位索/线岔) ===" << std::endl;
  // 悬索三型
  suspension_cable_params sc;
  sc.startPoint = gp_Pnt(0, 0, 8000);
  sc.endPoint = gp_Pnt(30000, 0, 8000);
  sc.diameter = 13; sc.tension = 0;
  sc.cableType = suspension_cable_type::CATENARY; sc.sag = 600;
  auto c1 = create_suspension_cable(sc);
  test_export(c1, "suspension_cable_catenary");
  report_dims("cable_catenary(L30m sag600)", c1);
  sc.cableType = suspension_cable_type::FIXED_ROPE; sc.sag = 0;
  test_export(create_suspension_cable(sc), "suspension_cable_fixed");
  sc.cableType = suspension_cable_type::DROPPER; sc.sag = 400;
  sc.startPoint = gp_Pnt(0, 0, 7000); sc.endPoint = gp_Pnt(30000, 0, 7000);
  test_export(create_suspension_cable(sc), "suspension_cable_dropper");
  // 定位索 (可调)
  positioning_cable_params pc;
  pc.diameter = 10; pc.topPoint = gp_Pnt(0, 0, 7000);
  pc.bottomPoint = gp_Pnt(0, 0, 5300); pc.adjustable = true;
  auto pcable = create_positioning_cable(pc);
  test_export(pcable, "positioning_cable");
  report_dims("positioning_cable(L1700)", pcable);
  // 线岔: 限制管 L1200 Ø38, 接触线 Ø12.9, 导高差 30
  auto cr = create_crossing(crossing_params{1200, 38, 12.9, 30});
  test_export(cr, "ocs_crossing");
  report_dims("ocs_crossing(L1200)", cr);
}

// --- 附加导线支架 ---
void test_aux_bracket() {
  std::cout << "\n=== Aux Bracket (附加导线支架) ===" << std::endl;
  auto b1 = create_aux_bracket(aux_bracket_params{aux_bracket_type::CROSS_ARM, 7000, 1200, 400, 300, 100, 16});
  test_export(b1, "aux_bracket_crossarm");
  report_dims("aux_crossarm(L1200)", b1);
  auto b2 = create_aux_bracket(aux_bracket_params{aux_bracket_type::WALL_MOUNT, 6000, 300, 500, 200, 100, 16});
  test_export(b2, "aux_bracket_wall");
  report_dims("aux_wall(500x200)", b2);
  auto b3 = create_aux_bracket(aux_bracket_params{aux_bracket_type::DOUBLE_MAST, 7000, 4000, 400, 300, 100, 16});
  test_export(b3, "aux_bracket_doublemast");
  report_dims("aux_doublemast(L4000)", b3);
}

// --- 轨道补充 ---
void test_track_extras() {
  std::cout << "\n=== Track Extras (轨道板/轨排/枕木阵列/伸缩调节器) ===" << std::endl;
  // CRTS III 轨道板: 5600x2500x210, 9 承轨台 @600, CA砂浆 50
  auto slab = create_track_slab(track_slab_params{5600, 2500, 210, 9, 600, 50});
  test_export(slab, "track_slab_crts3");
  report_dims("track_slab(5600x2500x210)", slab);

  // 曲线轨排 (带超高 120mm): 直线 20m + R800m 圆弧
  std::vector<gp_Pnt> cl;
  for (double x = 0; x <= 20000; x += 5000) cl.push_back(gp_Pnt(x, 0, 0));
  double R = 800000;
  for (int i = 1; i <= 24; ++i) {
    double th = i * 0.006;
    cl.push_back(gp_Pnt(20000 + R * sin(th), R - R * cos(th), 0));
  }
  auto rp = create_rail_pair(rail_pair_params{cl, 1435, 120, 176, 73, 150});
  test_export(rp, "rail_pair_curve_se120");
  report_dims("rail_pair_curve(超高120)", rp);

  // 曲线枕木阵列 (验证径向扇形排布)
  auto sl = create_sleeper_layout(sleeper_layout_params{cl, 2600, 260, 200, 600, 1435});
  test_export(sl, "sleeper_layout_curve");
  report_dims("sleeper_layout_curve", sl);

  // 枕木驱动道床
  ballast_from_sleepers_params bsp;
  for (double x = 0; x <= 6000; x += 600) {
    sleeper_line_params slp;
    slp.startPoint = gp_Pnt(x, -1300, 0);
    slp.endPoint = gp_Pnt(x, 1300, 0);
    bsp.sleepers.push_back(slp);
  }
  auto bl = create_ballast_from_sleepers(bsp);
  test_export(bl, "ballast_from_sleepers");
  report_dims("ballast_from_sleepers", bl);

  // 钢轨伸缩调节器
  expansion_joint_params ej;
  ej.stockRail.curve.type = rail_curve_type::LINE;
  ej.stockRail.curve.startPoint = gp_Pnt(0, -717.5, 0);
  ej.stockRail.curve.endPoint = gp_Pnt(6000, -717.5, 0);
  ej.switchRail.curve.type = rail_curve_type::LINE;
  ej.switchRail.curve.startPoint = gp_Pnt(0, 717.5, 0);
  ej.switchRail.curve.endPoint = gp_Pnt(6000, 717.5, 0);
  ej.switchRail.endStart.type = end_treatment_type::SWITCH;
  ej.switchRail.endStart.toeWidth = 2;
  ej.switchRail.endStart.switchLength = 2000;
  auto ejs = create_expansion_joint(ej);
  test_export(ejs, "expansion_joint");
  report_dims("expansion_joint(L6000)", ejs);

  // 标准钢轨断面查表 43/50/60/75
  for (int kg : {43, 50, 60, 75}) {
    rail_params sp = standard_rail_params(kg);
    sp.standardLength = 1000;
    char nm[32];
    snprintf(nm, sizeof(nm), "rail_std_%dkg", kg);
    auto rl = create_rail(sp);
    test_export(rl, nm);
    report_dims(nm, rl);
  }

  // 独立尖轨: 直线 + 曲线 (R=350m)
  auto swr1 = create_switch_rail(switch_rail_params{7700, 176, 73, 150, 16.5, 2, 0, true});
  test_export(swr1, "switch_rail_standalone");
  report_dims("switch_rail(L7700 tip2)", swr1);
  auto swr2 = create_switch_rail(switch_rail_params{7700, 176, 73, 150, 16.5, 2, 350000, true});
  test_export(swr2, "switch_rail_curve");
  report_dims("switch_rail_curve(R350m)", swr2);
}

// --- 补偿装置/开关/避雷器/连接小件 ---
void test_ocs_devices() {
  std::cout << "\n=== OCS Devices (补偿/开关/避雷器/小件) ===" << std::endl;
  auto ws = create_weight_stack(weight_stack_params{});
  test_export(ws, "weight_stack");
  report_dims("weight_stack(8块Ø380)", ws);
  auto rc = create_ratchet_compensator(ratchet_compensator_params{});
  test_export(rc, "ratchet_compensator");
  report_dims("ratchet_compensator", rc);
  auto pc = create_pulley_compensator(pulley_compensator_params{});
  test_export(pc, "pulley_compensator");
  report_dims("pulley_compensator", pc);
  auto dc = create_disconnector(disconnector_params{});
  test_export(dc, "disconnector");
  report_dims("disconnector(分闸75°)", dc);
  auto ar = create_arrester(arrester_params{});
  test_export(ar, "arrester");
  report_dims("arrester(H800)", ar);
  auto sc = create_sleeve_connector(sleeve_connector_params{});
  test_export(sc, "sleeve_connector");
  report_dims("sleeve_connector(Ø60/45°)", sc);
  auto se = create_sleeve_ear(sleeve_ear_params{});
  test_export(se, "sleeve_ear");
  report_dims("sleeve_ear(Ø60)", se);
  // 附加导线 (回流线, 跨距 50m 弛度 500)
  auto aw = create_auxiliary_wire(auxiliary_wire_params{12, 500, 0},
                                  gp_Pnt(0, 0, 8000), gp_Pnt(50000, 0, 8000));
  test_export(aw, "auxiliary_wire");
  report_dims("auxiliary_wire(L50m)", aw);
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
  run("Cantilevers", test_cantilevers);
  run("Compensator Parts", test_compensator_parts);
  run("Cables & Crossing", test_cables_and_crossing);
  run("Aux Bracket", test_aux_bracket);
  run("Track Extras", test_track_extras);
  run("OCS Devices", test_ocs_devices);

  std::cout << "\nAll tests completed." << std::endl;
  return 0;
}
