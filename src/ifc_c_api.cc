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

_Bool is_ifc_file(const char *filename) {
  std::string f{filename};
  auto v = flywave::ifc::get_version(f);
  return !v.empty();
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
/**
struct element {
  std::make_shared<flywave::topo::shape> shape;
  std::string id;
  std::string guuid;
  std::string type;
  std::string context;
  std::string unique_id;
  std::string parent_id;
  entity *product;
};

struct declaration {
  std::string name, name_lower;
  int index_in_schema;
};

struct entity : public declaration {
  std::string _Bool is_abstract;
  entity *supertype;
  std::vector<entity *> subtyoes;
  std::vector<attribute *> attributes;
  std::vector<_Bool> derived;
  std::vector<inverse_attribute *> inverse_attributes;
};

struct attribute {
  std::string name;
  bool optional;
};

struct inverse_attribute {
  std::string name;
  int type_of_aggregation;
  int bound1_, bound2_;
  entity *entity_reference;
  attribute *attribute_reference;
};
**/

#ifdef __cplusplus
}
#endif