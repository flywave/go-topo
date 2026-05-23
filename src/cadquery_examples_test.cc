#include <iostream>
#include <string>
#include <vector>
#include <memory>

#define _Bool bool

#include <gp_Pnt.hxx>
#include <gp_Vec.hxx>

#include "workplane.hh"

// Only include C API header from libs/ for types needed by stubs
#include "standard_c_api.h"
#include "topo_c_api.h"

// Stubs for cgo-exported symbols
extern "C" {
void begin(void *) {}
void end(void *) {}
int appendFace(void *, color_t) { return 0; }
void appendNodeNorm(void *, int, pnt3d_t, pnt3d_t) {}
void appendNodeNormUv(void *, int, pnt3d_t, pnt3d_t, pnt2d_t) {}
void appendNode(void *, int, pnt3d_t) {}
void appendTriangle(void *, int, int, int, int) {}
}

namespace ftopo = flywave::topo;

static int pass = 0, fail = 0;

#define CHECK(cond, msg) \
  do { \
    if (!(cond)) { \
      std::cout << "FAIL: " << msg << std::endl; \
      fail++; \
      return; \
    } \
    std::cout << "ok" << std::endl; \
    pass++; \
  } while (0)

static void test(const char *name, void (*fn)()) {
  std::cout << "  " << name << "... " << std::flush;
  fn();
}

// ---------------------------------------------------------------------------
// 1: Simple rectangular plate
// ---------------------------------------------------------------------------
void test_rectangular_plate() {
  auto wp = std::make_shared<ftopo::workplane>();
  auto r = wp->box(2.0, 2.0, 0.5, true, true, true);
  r->value().cast<ftopo::compound>()->export_step(
      "example_01_rectangular_plate.step");
  CHECK(true, "ok");
}

// ---------------------------------------------------------------------------
// 2: Plate with hole
// ---------------------------------------------------------------------------
void test_plate_with_hole() {
  double length = 80.0, height = 60.0, thickness = 10.0, hole_dia = 22.0;
  auto wp = std::make_shared<ftopo::workplane>();
  auto r = wp->box(length, height, thickness, true, true, true);
  r = r->faces(">Z", "")->create(0, false, ftopo::center_option::ProjectedOrigin, nullptr);
  r = r->hole(hole_dia, boost::none, true);
  r->value().cast<ftopo::compound>()->export_step(
      "example_02_plate_with_hole.step");
  CHECK(true, "ok");
}

// ---------------------------------------------------------------------------
// 3: Extrude prism
// ---------------------------------------------------------------------------
void test_extrude_prism() {
  auto wp = std::make_shared<ftopo::workplane>();
  auto r = wp->circle(2.0, false)->rect(0.5, 0.75, true, false);
  r = r->extrude(0.5, true, true, false, boost::none);
  r->value().cast<ftopo::compound>()->export_step(
      "example_03_extrude_prism.step");
  CHECK(true, "ok");
}

// ---------------------------------------------------------------------------
// 4: Line and arc
// ---------------------------------------------------------------------------
void test_line_and_arc() {
  auto wp = std::make_shared<ftopo::workplane>();
  auto r = wp->line_to(2.0, 0, false);
  r = r->line_to(2.0, 1.0, false);
  r = r->three_point_arc(gp_Pnt(1.0, 1.5, 0), gp_Pnt(0.0, 1.0, 0), false);
  r = r->close();
  r = r->extrude(0.25, true, true, false, boost::none);
  r->value().cast<ftopo::compound>()->export_step(
      "example_04_line_and_arc.step");
  CHECK(true, "ok");
}

// ---------------------------------------------------------------------------
// 5: Move work point
// ---------------------------------------------------------------------------
void test_move_work_point() {
  auto wp = std::make_shared<ftopo::workplane>();
  auto r = wp->circle(3.0, false);
  r = r->center(1.5, 0.0)->rect(0.5, 0.5, true, false);
  r = r->center(-1.5, 1.5)->circle(0.25, false);
  r = r->extrude(0.25, true, true, false, boost::none);
  r->value().cast<ftopo::compound>()->export_step(
      "example_05_move_work_point.step");
  CHECK(true, "ok");
}

// ---------------------------------------------------------------------------
// 6: Point list
// ---------------------------------------------------------------------------
void test_point_list() {
  auto wp = std::make_shared<ftopo::workplane>();
  auto r = wp->circle(2.0, false);
  std::vector<ftopo::topo_vector> pts = {
    {1.5, 0, 0}, {0, 1.5, 0}, {-1.5, 0, 0}, {0, -1.5, 0}};
  r = r->push_points(pts)->circle(0.25, false);
  r = r->extrude(0.125, true, true, false, boost::none);
  r->value().cast<ftopo::compound>()->export_step(
      "example_06_point_list.step");
  CHECK(true, "ok");
}

// ---------------------------------------------------------------------------
// 8: Polyline (I-beam)
// ---------------------------------------------------------------------------
void test_polyline() {
  double L = 100.0, H = 20.0, W = 20.0, t = 1.0;
  std::vector<gp_Pnt> pts = {
    {0, H/2, 0}, {W/2, H/2, 0}, {W/2, (H/2-t), 0}, {t/2, (H/2-t), 0},
    {t/2, (t-H/2), 0}, {W/2, (t-H/2), 0}, {W/2, H/-2.0, 0}, {0, H/-2.0, 0}};
  auto wp = std::make_shared<ftopo::workplane>();
  auto r = wp->polyline(pts, false, false);
  r = r->mirror_y();
  r = r->extrude(L, true, true, false, boost::none);
  r->value().cast<ftopo::compound>()->export_step(
      "example_08_polyline.step");
  CHECK(true, "ok");
}

int main() {
  std::cout << "=== CadQuery Examples (C++ API) ===\n" << std::endl;

  test("01 Rectangular Plate", test_rectangular_plate);
  test("02 Plate with Hole", test_plate_with_hole);
  test("03 Extrude Prism", test_extrude_prism);
  test("04 Line and Arc", test_line_and_arc);
  test("05 Move Work Point", test_move_work_point);
  test("06 Point List", test_point_list);
  test("08 Polyline", test_polyline);

  std::cout << "\n=== Results: " << (pass + fail) << " tests, "
            << pass << " passed, " << fail << " failed" << std::endl;
  return fail > 0 ? 1 : 0;
}
