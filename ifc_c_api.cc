#include "ifc_c_api.h"
#include "ifc.hh"
#include "shape.hh"
#include "topo_impl.hh"

#include <memory>
#include <string>
#include <vector>

#ifdef __cplusplus
extern "C" {
#endif

topo_shape_t **ifc_get_topo_shapes(const char *filename, int *count) {
  std::string f{filename};
  auto ct = flywave::ifc::get_convert(f);
  if (!ct) {
    *count = 0;
    return nullptr;
  }
  auto shps = ct->get_shape();
  *count = shps.size();
  auto sp = new topo_shape_t *[shps.size()];
  for (int i = 0; i < shps.size(); i++) {
    auto shp = std::make_shared<flywave::topo::shape>(shps[i]);
    sp[i] = new _topo_shape_t{shp : shp};
  }
  return sp;
}

void ifc_shapes_free(topo_shape_t **shps) {
  if (shps) {
    delete[] shps;
  }
}

void ifc_register_schema() { flywave::ifc::ifc_register_schema(); }

topo_shape_t *ifc_get_topo_shape(topo_shape_t **ts, int index) {
  return ts[index];
}

#ifdef __cplusplus
}
#endif