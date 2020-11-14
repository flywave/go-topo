#include "ifc_c_api.h"
#include "ifc.hh"

#include <memory>
#include <string>
#include <vector>

#ifdef __cplusplus
extern "C" {
#endif

topo_shape_t** ifc_get_topo_shapes(const char *filename,int *count) {
  std::string f{filename};
  flywave::ifc::convert ct{f};
  auto shps = ct.get_shape();
  *count = shps.size();
  auto sp = new topo_shape_t*[shps.size()];
  for (auto &s : shps) {
    auto shp = std::make_shared<flywave::topo::shape>(std::move(s));
    sp = new topo_shape_t{shp : shp};
    sp++;
  }
  return sp;
}

void ifc_shapes_free(topo_shape_t **shps){
  if(shps){
    delete[] shps;
  }
}

#ifdef __cplusplus
}
#endif