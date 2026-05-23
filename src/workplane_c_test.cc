#include <iostream>
#include <string>

#ifndef __cplusplus
#include <stdbool.h>
#else
#define _Bool bool
#endif

#include "workplane_c_api.h"

// Stubs for cgo-exported symbols referenced by libtopo.a's mesh receiver
extern "C" {
void begin(void *) {}
void end(void *) {}
int appendFace(void *, color_t) { return 0; }
void appendNodeNorm(void *, int, pnt3d_t, pnt3d_t) {}
void appendNodeNormUv(void *, int, pnt3d_t, pnt3d_t, pnt2d_t) {}
void appendNode(void *, int, pnt3d_t) {}
void appendTriangle(void *, int, int, int, int) {}
}

// ---- test starts here ----

static int pass = 0, fail = 0;

#define TEST(name)                                \
  do {                                             \
    std::cout << "  " << name << "... ";            \
  } while (0)

#define CHECK(cond, msg)                           \
  do {                                             \
    if (!(cond)) {                                  \
      std::cout << "FAIL: " << msg << std::endl;    \
      fail++;                                       \
      return;                                       \
    }                                               \
    std::cout << "ok" << std::endl;                 \
    pass++;                                         \
  } while (0)

#define CHECK_RESULT(wp, result, msg)              \
  do {                                             \
    if (workplane_has_error(wp)) {                  \
      std::cout << "FAIL: " << msg                  \
                << " error=" << workplane_error(wp)  \
                << std::endl;                        \
      fail++;                                       \
      return;                                       \
    }                                               \
    if (!(result)) {                                \
      std::cout << "FAIL: " << msg << " null result" \
                << std::endl;                        \
      fail++;                                       \
      return;                                       \
    }                                               \
    std::cout << "ok" << std::endl;                 \
    pass++;                                         \
  } while (0)

void test_create_empty() {
  TEST("create empty workplane");
  workplane_t *wp = workplane_create();
  CHECK(wp != nullptr, "null wp");
  CHECK(!workplane_has_error(wp), "unexpected error");
  workplane_free(wp);
}

void test_create_named() {
  TEST("create named XY workplane");
  topo_vector_t *o = topo_vector_new(0, 0, 0);
  workplane_t *wp = workplane_create_from_name("XY", o);
  CHECK(wp != nullptr, "null wp");
  CHECK(!workplane_has_error(wp), "unexpected error");
  workplane_free(wp);
  topo_vector_free(o);
}

void test_create_named_null_origin() {
  TEST("create named XY with null origin");
  workplane_t *wp = workplane_create_from_name("XY", nullptr);
  CHECK(wp != nullptr, "null wp");
  CHECK(!workplane_has_error(wp), "unexpected error");
  workplane_free(wp);
}

void test_rect_on_named() {
  TEST("rect on named XY");
  topo_vector_t *o = topo_vector_new(0, 0, 0);
  workplane_t *wp = workplane_create_from_name("XY", o);
  workplane_rect_all(wp, 10, 10, true, false);
  CHECK(!workplane_has_error(wp), "rect failed");
  workplane_free(wp);
  topo_vector_free(o);
}

void test_circle_on_named() {
  TEST("circle on named XY");
  topo_vector_t *o = topo_vector_new(0, 0, 0);
  workplane_t *wp = workplane_create_from_name("XY", o);
  workplane_circle(wp, 5, false);
  CHECK(!workplane_has_error(wp), "circle failed");
  workplane_free(wp);
  topo_vector_free(o);
}

void test_box_centered() {
  TEST("box centered on named XY");
  topo_vector_t *o = topo_vector_new(0, 0, 0);
  workplane_t *wp = workplane_create_from_name("XY", o);
  workplane_t *r = workplane_box_all(wp, 10, 20, 30, true, true, true);
  CHECK_RESULT(wp, r, "box centered");
  workplane_free(r);
  workplane_free(wp);
  topo_vector_free(o);
}

void test_box_corners() {
  TEST("box corners on named XY");
  topo_vector_t *o = topo_vector_new(0, 0, 0);
  workplane_t *wp = workplane_create_from_name("XY", o);
  workplane_t *r = workplane_box(wp, 10, 20, 30, false, false, false, true, true);
  CHECK_RESULT(wp, r, "box corners");
  workplane_free(r);
  workplane_free(wp);
  topo_vector_free(o);
}

void test_sphere_centered() {
  TEST("sphere centered on named XY");
  topo_vector_t *o = topo_vector_new(0, 0, 0);
  workplane_t *wp = workplane_create_from_name("XY", o);
  workplane_t *r = workplane_sphere_all(wp, 10, nullptr, -90, 90, 360, true, true, true);
  CHECK_RESULT(wp, r, "sphere centered");
  workplane_free(r);
  workplane_free(wp);
  topo_vector_free(o);
}

void test_cylinder_centered() {
  TEST("cylinder centered on named XY");
  topo_vector_t *o = topo_vector_new(0, 0, 0);
  workplane_t *wp = workplane_create_from_name("XY", o);
  workplane_t *r = workplane_cylinder_all(wp, 20, 5, nullptr, 360, true, true, true);
  CHECK_RESULT(wp, r, "cylinder centered");
  workplane_free(r);
  workplane_free(wp);
  topo_vector_free(o);
}

void test_extrude_simple() {
  TEST("extrude simple on named XY");
  topo_vector_t *o = topo_vector_new(0, 0, 0);
  workplane_t *wp = workplane_create_from_name("XY", o);
  workplane_rect_all(wp, 10, 10, true, false);
  workplane_t *r = workplane_extrude(wp, 20, true, true, false, nullptr);
  CHECK_RESULT(wp, r, "extrude simple");
  workplane_free(r);
  workplane_free(wp);
  topo_vector_free(o);
}

void test_mirror_x() {
  TEST("mirror X on named XY");
  topo_vector_t *o = topo_vector_new(0, 0, 0);
  workplane_t *wp = workplane_create_from_name("XY", o);
  workplane_rect_all(wp, 10, 10, true, false);
  workplane_t *r = workplane_mirror_x(wp);
  CHECK_RESULT(wp, r, "mirror x");
  workplane_free(r);
  workplane_free(wp);
  topo_vector_free(o);
}

void test_mirror_y() {
  TEST("mirror Y on named XY");
  topo_vector_t *o = topo_vector_new(0, 0, 0);
  workplane_t *wp = workplane_create_from_name("XY", o);
  workplane_rect_all(wp, 10, 10, true, false);
  workplane_t *r = workplane_mirror_y(wp);
  CHECK_RESULT(wp, r, "mirror y");
  workplane_free(r);
  workplane_free(wp);
  topo_vector_free(o);
}

void test_nil_origin_create() {
  TEST("create_from_name with null origin");
  workplane_t *wp = workplane_create_from_name("XY", nullptr);
  CHECK(wp != nullptr, "null wp");
  CHECK(!workplane_has_error(wp), "unexpected error");
  workplane_free(wp);
}

void test_nil_depth_hole() {
  TEST("hole with null depth on named XY");
  topo_vector_t *o = topo_vector_new(0, 0, 0);
  workplane_t *wp = workplane_create_from_name("XY", o);
  workplane_t *wp2 = workplane_box_all(wp, 20, 20, 20, true, true, true);
  if (workplane_has_error(wp)) {
    std::cout << "SKIP (box failed)" << std::endl;
    workplane_free(wp); workplane_free(wp2); topo_vector_free(o); return;
  }
  workplane_t *wp3 = workplane_faces(wp2, ">Z", "");
  if (workplane_has_error(wp2)) {
    std::cout << "SKIP (faces failed)" << std::endl;
    workplane_free(wp); workplane_free(wp2); workplane_free(wp3); topo_vector_free(o); return;
  }
  workplane_t *sub = workplane_workplane(wp3, 0, false, 0, nullptr);
  if (workplane_has_error(wp3)) {
    std::cout << "SKIP (sub wp failed)" << std::endl;
    workplane_free(wp); workplane_free(wp2); workplane_free(wp3); workplane_free(sub); topo_vector_free(o); return;
  }
  workplane_t *r = workplane_hole(sub, 5, nullptr, true);
  if (workplane_has_error(sub)) {
    std::cout << "FAIL: hole error=" << workplane_error(sub) << std::endl;
    fail++;
  } else {
    CHECK(r != nullptr, "null result");
    std::cout << "ok" << std::endl;
    pass++;
    workplane_free(r);
  }
  workplane_free(sub);
  workplane_free(wp3);
  workplane_free(wp2);
  workplane_free(wp);
  topo_vector_free(o);
}

void test_workplane_to_pending() {
  TEST("to_pending on named XY");
  topo_vector_t *o = topo_vector_new(0, 0, 0);
  workplane_t *wp = workplane_create_from_name("XY", o);
  workplane_move_to(wp, 0, 0);
  workplane_line_to(wp, 10, 0, false);
  workplane_line_to(wp, 10, 10, false);
  workplane_line_to(wp, 0, 10, false);
  workplane_close(wp);
  CHECK(!workplane_has_error(wp), "2d chain failed");
  workplane_free(wp);
  topo_vector_free(o);
}

void test_consolidate_wires() {
  TEST("consolidate wires on named XY");
  topo_vector_t *o = topo_vector_new(0, 0, 0);
  workplane_t *wp = workplane_create_from_name("XY", o);
  workplane_move_to(wp, 0, 0);
  workplane_line_to(wp, 10, 0, false);
  workplane_line_to(wp, 10, 10, false);
  workplane_line_to(wp, 0, 10, false);
  workplane_close(wp);
  workplane_t *r = workplane_consolidate_wires(wp);
  CHECK_RESULT(wp, r, "consolidate wires");
  workplane_free(r);
  workplane_free(wp);
  topo_vector_free(o);
}

int main() {
  std::cout << "=== Workplane C API Test ===\n" << std::endl;

  std::cout << "--- Construction ---" << std::endl;
  test_create_empty();
  test_create_named();
  test_create_named_null_origin();

  std::cout << "\n--- 2D Operations ---" << std::endl;
  test_rect_on_named();
  test_circle_on_named();
  test_mirror_x();
  test_mirror_y();
  test_workplane_to_pending();
  test_consolidate_wires();

  std::cout << "\n--- 3D Primitives ---" << std::endl;
  test_box_centered();
  test_box_corners();
  test_sphere_centered();
  test_cylinder_centered();

  std::cout << "\n--- 3D Operations ---" << std::endl;
  test_extrude_simple();

  std::cout << "\n--- Nil Safety (requires rebuilt lib) ---" << std::endl;
  test_nil_origin_create();
  test_nil_depth_hole();

  std::cout << "\n=== Results: " << (pass + fail) << " tests, "
            << pass << " passed, " << fail << " failed ===" << std::endl;
  return fail > 0 ? 1 : 0;
}
