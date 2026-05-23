// Minimal test: just create a workplane, nothing else
#include <iostream>
#include "workplane_c_api.h"

extern "C" {
void begin(void *) {}
void end(void *) {}
int appendFace(void *, color_t) { return 0; }
void appendNodeNorm(void *, int, pnt3d_t, pnt3d_t) {}
void appendNodeNormUv(void *, int, pnt3d_t, pnt3d_t, pnt2d_t) {}
void appendNode(void *, int, pnt3d_t) {}
void appendTriangle(void *, int, int, int, int) {}
}

int main() {
  std::cout << "1: creating vec... " << std::flush;
  topo_vector_t *o = topo_vector_new(0, 0, 0);
  std::cout << "ok" << std::endl;

  std::cout << "2: creating wp from name... " << std::flush;
  workplane_t *wp = workplane_create_from_name("XY", o);
  std::cout << "ok" << std::endl;

  std::cout << "3: checking error... " << std::flush;
  bool has_err = workplane_has_error(wp);
  std::cout << (has_err ? "error=" : "no error (ok)") << std::endl;
  if (has_err) {
    std::cout << "  msg: " << workplane_error(wp) << std::endl;
  }

  workplane_free(wp);
  topo_vector_free(o);
  return has_err ? 1 : 0;
}
