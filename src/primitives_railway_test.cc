#include "primitives_railway.hh"
#include <BRepMesh_IncrementalMesh.hxx>
#include <StlAPI_Writer.hxx>
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
  p.railHeight = 176; p.headWidth = 70.6; p.baseWidth = 150;
  p.webThickness = 16.5; p.headHeight = 48.5; p.baseHeight = 30.2;
  p.headRadius = 13; p.standardLength = 2000;
  test_export(create_rail(p), "rail_60kg");
}

void test_sleeper() {
  std::cout << "\n=== Sleeper ===" << std::endl;
  sleeper_params p;
  p.length = 2600; p.width = 300; p.height = 200;
  p.gauge = 1435; p.grooveDepth = 30; p.spacing = 600;
  test_export(create_sleeper(p), "sleeper");
}

void test_ballast() {
  std::cout << "\n=== Ballast ===" << std::endl;
  ballast_params p;
  p.topWidth = 3600; p.thickness = 350; p.sideSlope = 1.5;
  p.centerlineSegments = {{centerline_curve_type::LINE, {gp_Pnt(0, 0, 0), gp_Pnt(5000, 0, 0)}}};
  test_export(create_ballast(p), "ballast");
}

void test_straight_track() {
  std::cout << "\n=== Straight Track ===" << std::endl;
  straight_track_params p;
  p.startPoint = gp_Pnt(0, 0, 0); p.endPoint = gp_Pnt(5000, 0, 0);
  p.gauge = 1435; p.railHeight = 176; p.railHeadWidth = 70.6; p.railBaseWidth = 150;
  p.sleeperLength = 2600; p.sleeperWidth = 300; p.sleeperHeight = 200;
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
  p.railHeight = 176; p.railHeadWidth = 70.6; p.railBaseWidth = 150;
  p.sleeperLength = 2600; p.sleeperWidth = 300; p.sleeperHeight = 200;
  p.sleeperSpacing = 600;
  p.ballastTopWidth = 3600; p.ballastThickness = 350; p.ballastSlope = 1.5;
  test_export(create_curve_track(p), "curve_track");
}

void test_turnout() {
  std::cout << "\n=== Turnout ===" << std::endl;
  turnout_params p;
  p.turnoutNo = 12; p.isLeftHand = true; p.gauge = 1435;
  p.railHeight = 176; p.railHeadWidth = 70.6; p.railBaseWidth = 150;
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

int main() {
  auto run = [](const char *name, auto fn) {
    std::cout << "\n=== " << name << " ===" << std::endl;
    try { fn(); } catch (const std::exception &e) { std::cerr << "  ERROR: " << e.what() << std::endl; }
    catch (...) { std::cerr << "  ERROR: unknown exception" << std::endl; }
  };

  run("Rod Insulator", test_rod_insulator);
  run("Steel Mast H-Beam", []{ test_export(create_steel_mast(steel_mast_params{
    steel_mast_type::H_BEAM,8000,200,350,10,16,450,200,24,1}), "steel_mast_hbeam"); });
  run("Steel Mast Lattice", []{ test_export(create_steel_mast(steel_mast_params{
    steel_mast_type::LATTICE,8000,300,600,8,12,750,200,24,1}), "steel_mast_lattice"); });
  run("Cross Arm", test_cross_arm);
  run("Registration Arm", test_registration_arm);
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
  run("Rail 60kg", test_rail);
  run("Sleeper", test_sleeper);
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
  run("Mast Assembly", test_mast_assembly);

  std::cout << "\nAll tests completed." << std::endl;
  return 0;
}
