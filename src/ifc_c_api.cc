#include "ifc_c_api.h"
#include "ifc.hh"
#include "ifc_impl.hh"
#include "shape.hh"
#include "topo_impl.hh"

#include <memory>
#include <string>
#include <vector>

#ifdef __cplusplus
extern "C" {
#endif

ifc_convert_t *ifc_convert_new() { return new ifc_convert_t{nullptr}; }

void ifc_convert_free(ifc_convert_t *p) {
  if (p) {
    delete p;
  }
}

_Bool ifc_convert_load(ifc_convert_t *p, const char *filename) {
  if (!p)
    return false;
  try {
    p->ct = std::make_unique<flywave::ifc::ifc_convert>(filename);
    if (!p->ct || !p->ct->load()) {
      return false;
    }
    return true;
  } catch (...) {
    return false;
  }
}

char *ifc_convert_get_version(ifc_convert_t *p) {
  if (!p || !p->ct)
    return nullptr;
  return strdup(p->ct->get_version().c_str());
}

ifc_element_t **ifc_convert_get_elements(ifc_convert_t *p, int *count) {
  if (!p || !p->ct) {
    *count = 0;
    return nullptr;
  }
  auto shps = p->ct->get_shape();
  *count = static_cast<int>(shps.size());
  auto sp = new ifc_element_t *[shps.size()];
  for (int i = 0; i < shps.size(); i++) {
    auto s = shps[i];
    auto shp = std::make_shared<flywave::topo::shape>(s.shp);
    sp[i] = new ifc_element_t{
        .shp = shp,
        .id = s.id,
        .parent_id = s.parent_id,
        .name = s.name,
        .guid = s.guid,
    };
  }
  return sp;
}

ifc_triangulation_t **ifc_convert_get_triangulations(ifc_convert_t *p,
                                                     int *count) {
  if (!p || !p->ct) {
    *count = 0;
    return nullptr;
  }
  auto tris = p->ct->get_geometry();
  *count = static_cast<int>(tris.size());
  auto sp = new ifc_triangulation_t *[tris.size()];
  for (int i = 0; i < tris.size(); i++) {
    auto t = tris[i];
    sp[i] = new ifc_triangulation_t{
        .tri = t,
    };
  }
  return sp;
}

ifc_element_t **ifc_get_elements(const char *filename, int *count) {
  auto ct = flywave::ifc::get_convert(filename);
  if (!ct) {
    *count = 0;
    return nullptr;
  }
  auto shps = ct->get_shape();
  *count = static_cast<int>(shps.size());
  auto sp = new ifc_element_t *[shps.size()];
  for (int i = 0; i < shps.size(); i++) {
    auto s = shps[i];
    auto shp = std::make_shared<flywave::topo::shape>(s.shp);
    sp[i] = new ifc_element_t{
        .shp = shp,
        .id = s.id,
        .parent_id = s.parent_id,
        .name = s.name,
        .guid = s.guid,
    };
  }
  return sp;
}

ifc_triangulation_t **ifc_get_triangulations(const char *filename, int *count) {
  auto ct = flywave::ifc::get_convert(filename);
  if (!ct) {
    *count = 0;
    return nullptr;
  }
  auto tris = ct->get_geometry();
  *count = static_cast<int>(tris.size());
  auto sp = new ifc_triangulation_t *[tris.size()];
  for (int i = 0; i < tris.size(); i++) {
    auto t = tris[i];
    sp[i] = new ifc_triangulation_t{
        .tri = t,
    };
  }
  return sp;
}

void ifc_triangulations_free(ifc_triangulation_t **shps) {
  if (shps) {
    delete[] shps;
  }
}

ifc_triangulation_t *ifc_get_triangulation(ifc_triangulation_t **triangulations,
                                           int index) {
  return triangulations[index];
}

_Bool is_ifc_file(const char *filename) {
  auto v = flywave::ifc::get_version(filename);
  return !v.empty();
}

void ifc_elements_free(ifc_element_t **shps) {
  if (shps) {
    delete[] shps;
  }
}

int ifc_element_get_id(ifc_element_t *p) { return p->id; }

int ifc_element_get_parent_id(ifc_element_t *p) { return p->parent_id; }

const char *ifc_element_get_name(ifc_element_t *p) { return p->name.c_str(); }

const char *ifc_element_get_guid(ifc_element_t *p) { return p->guid.c_str(); }

topo_shape_t *ifc_element_get_shape(ifc_element_t *p) {
  return new topo_shape_t{
      .shp = p->shp,
  };
}

ifc_element_t *ifc_get_element(ifc_element_t **elements, int index) {
  return elements[index];
}

void ifc_triangulation_free(ifc_triangulation_t *p) {
  if (p) {
    delete p;
  }
}

const double *ifc_triangulation_get_verts(ifc_triangulation_t *p, int *count) {
  auto &tri = p->tri;
  *count = static_cast<int>(tri->verts().size());
  return tri->verts().data();
}

const int *ifc_triangulation_get_faces(ifc_triangulation_t *p, int *count) {
  auto &tri = p->tri;
  *count = static_cast<int>(tri->faces().size());
  return tri->faces().data();
}

const double *ifc_triangulation_get_normals(ifc_triangulation_t *p,
                                            int *count) {
  auto &tri = p->tri;
  *count = static_cast<int>(tri->normals().size());
  return tri->normals().data();
}

const int *ifc_triangulation_get_edges(ifc_triangulation_t *p, int *count) {
  auto &tri = p->tri;
  *count = static_cast<int>(tri->edges().size());
  return tri->edges().data();
}

const double *ifc_triangulation_get_uvs(ifc_triangulation_t *p, int *count) {
  auto &tri = p->tri;
  *count = static_cast<int>(tri->uvs().size());
  return tri->uvs().data();
}

const int *ifc_triangulation_get_material_ids(ifc_triangulation_t *p,
                                              int *count) {
  auto &tri = p->tri;
  *count = static_cast<int>(tri->material_ids().size());
  return tri->material_ids().data();
}

const int *ifc_triangulation_get_item_ids(ifc_triangulation_t *p, int *count) {
  auto &tri = p->tri;
  *count = static_cast<int>(tri->item_ids().size());
  return tri->item_ids().data();
}

const int *ifc_triangulation_get_edges_item_ids(ifc_triangulation_t *p,
                                                int *count) {
  auto &tri = p->tri;
  *count = static_cast<int>(tri->edges_item_ids().size());
  return tri->edges_item_ids().data();
}

ifc_material_t *ifc_triangulation_get_materials(ifc_triangulation_t *p,
                                                int *count) {
  auto &tri = p->tri;
  auto &materials = tri->materials();
  *count = static_cast<int>(materials.size());
  auto mtls = new ifc_material_t[materials.size()];
  for (size_t i = 0; i < materials.size(); i++) {
    mtls[i] = ifc_material_t{.mtl = materials[i]};
  }
  return mtls;
}

void ifc_materials_free(ifc_material_t *mtls) {
  if (mtls) {
    delete[] mtls;
  }
}

const char *ifc_material_get_name(ifc_material_t *mtl) {
  return mtl->mtl->name.c_str();
}

ifc_color_t ifc_material_get_diffuse(ifc_material_t *mtl) {
  const auto &c = mtl->mtl->diffuse;
  return ifc_color_t{c.r(), c.g(), c.b()};
}

ifc_color_t ifc_material_get_surface(ifc_material_t *mtl) {
  const auto &c = mtl->mtl->surface;
  return ifc_color_t{c.r(), c.g(), c.b()};
}

ifc_color_t ifc_material_get_specular(ifc_material_t *mtl) {
  const auto &c = mtl->mtl->specular;
  return ifc_color_t{c.r(), c.g(), c.b()};
}

double ifc_material_get_specularity(ifc_material_t *mtl) {
  return mtl->mtl->specularity;
}

double ifc_material_get_transparency(ifc_material_t *mtl) {
  return mtl->mtl->transparency;
}
#ifdef __cplusplus
}
#endif
