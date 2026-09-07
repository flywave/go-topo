#include "ifc_c_api.h"
#include "ifc.hh"
#include "ifc_impl.hh"
#include "shape.hh"
#include "topo_impl.hh"

#include <cstring>
#include <memory>
#include <new>
#include <string>
#include <vector>

template <typename T, typename U>
T **get_object_vector(const std::vector<U> &vec, int *count) {
  if (!count)
    return nullptr;

  *count = vec.size();
  if (*count == 0)
    return nullptr;

  T **result = new T *[*count];
  for (int i = 0; i < *count; ++i) {
    result[i] = new T{vec[i]};
  }
  return result;
}

template <typename T>
const char **get_string_vector(const std::vector<T> &vec, int *count) {
  if (!count)
    return nullptr;

  *count = vec.size();
  if (*count == 0)
    return nullptr;

  const char **result = new const char *[*count];
  for (int i = 0; i < *count; ++i) {
    result[i] = vec[i].c_str();
  }
  return result;
}

template <typename T> void free_object_vector(T **objects) {
  if (!objects)
    return;
  delete[] objects;
}

#ifdef __cplusplus
extern "C" {
#endif

ifc_convert_t *ifc_convert_new() { try { return new ifc_convert_t{nullptr};   }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

void ifc_convert_free(ifc_convert_t *p) { try {
  if (p) {
    delete p;
  }
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
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

char *ifc_convert_get_version(ifc_convert_t *p) { try {
  if (!p || !p->ct)
    return nullptr;
  return strdup(p->ct->get_version().c_str());
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

ifc_data_t *ifc_convert_get_data(ifc_convert_t *p) { try {
  if (!p)
    return nullptr;
  auto data = p->ct->get_data();
  if (!data)
    return nullptr;
  return new _ifc_data_t{std::move(data)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

ifc_element_t **ifc_convert_get_elements(ifc_convert_t *p, int *count) { try {
  if (!p || !p->ct) {
    *count = 0;
    return nullptr;
  }
  auto infos = p->ct->get_element_infos();
  *count = static_cast<int>(infos.size());
  auto sp = new ifc_element_t *[infos.size()+1];
  for (int i = 0; i < infos.size(); i++) {
    auto s = infos[i];
    auto shp = std::make_shared<flywave::topo::shape>(s.shp);
    sp[i] = new ifc_element_t{
        .shp = shp,
        .id = s.id,
        .parent_id = s.parent_id,
        .name = s.name,
        .guid = s.guid,
        .type = s.type,
     };
  if (s.transform) {
      auto trans = new double[16];
      std::copy(s.transform->begin(), s.transform->end(), trans);
      sp[i]->transform = trans;
    }
   }
  sp[*count] = nullptr;
  return sp;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

ifc_triangulation_t **ifc_convert_get_triangulations(ifc_convert_t *p,
                                                     int *count) { try {
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
        .tri = t.triangulation,
        .id = t.id,
        .parent_id = t.parent_id,
        .name = t.name,
        .guid = t.guid,
        .type = t.type,
     };
    if (t.transform) {
      auto trans = new double[16];
      std::copy(t.transform->begin(), t.transform->end(), trans);
      sp[i]->transform = trans;
    }
  }
  return sp;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

ifc_element_t **ifc_get_elements(const char *filename, int *count) { try {
  auto ct = flywave::ifc::get_convert(filename);
  if (!ct) {
    *count = 0;
    return nullptr;
  }
  auto shps = ct->get_element_infos();
  *count = static_cast<int>(shps.size());
  auto sp = new ifc_element_t *[shps.size()+1];
  for (int i = 0; i < shps.size(); i++) {
    auto s = shps[i];
    auto shp = std::make_shared<flywave::topo::shape>(s.shp);
    sp[i] = new ifc_element_t{
        .shp = shp,
        .id = s.id,
        .parent_id = s.parent_id,
        .name = s.name,
        .guid = s.guid,
        .type = s.type,
     };
    if (s.transform) {
      auto trans = new double[16];
      std::copy(s.transform->begin(), s.transform->end(), trans);
      sp[i]->transform = trans;
    }
   }
   sp[*count] = nullptr;
  return sp;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

ifc_triangulation_t **ifc_get_triangulations(const char *filename, int *count) { try {
  auto ct = flywave::ifc::get_convert(filename);
  if (!ct) {
    *count = 0;
    return nullptr;
  }
  auto tris = ct->get_geometry();
  *count = static_cast<int>(tris.size());
  auto sp = new ifc_triangulation_t *[tris.size()+1];
  for (int i = 0; i < tris.size(); i++) {
    auto t = tris[i];
    sp[i] = new ifc_triangulation_t{
        .tri = t.triangulation,
        .id = t.id,
        .parent_id = t.parent_id,
        .name = t.name,
        .guid = t.guid,
        .type = t.type,
     };
 
    if (t.transform) {
      auto trans = new double[16];
      std::copy(t.transform->begin(), t.transform->end(), trans);
      sp[i]->transform = trans;
    }
  }
  return sp;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

void ifc_triangulations_free(ifc_triangulation_t **shps) { try {
  if (shps) {
         delete []shps;
    }
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

ifc_triangulation_t *ifc_get_triangulation(ifc_triangulation_t **triangulations,
                                           int index) { try {
  return triangulations[index];
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

_Bool is_ifc_file(const char *filename) { try {
  auto v = flywave::ifc::get_version(filename);
  return !v.empty();
  }
  catch (const std::exception &e) {
    (void)e;
    return false;
  }
  catch (...) {
    return false;
  }
}

void ifc_elements_free(ifc_element_t **shps) { try {
  if (shps) {
      for(int i=0;shps[i]!=nullptr;i++){
          if(shps[i]->transform!=nullptr){
              delete [] shps[i]->transform;
          }
          delete shps[i];
      }
      delete []shps;
  }
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

int ifc_element_get_id(ifc_element_t *p) { try { return p->id;   }
  catch (const std::exception &e) {
    (void)e;
    return 0;
  }
  catch (...) {
    return 0;
  }
}

int ifc_element_get_parent_id(ifc_element_t *p) { try { return p->parent_id;   }
  catch (const std::exception &e) {
    (void)e;
    return 0;
  }
  catch (...) {
    return 0;
  }
}

const char *ifc_element_get_name(ifc_element_t *p) { try { return p->name.c_str();   }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

const char *ifc_element_get_guid(ifc_element_t *p) { try { return p->guid.c_str();   }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

const double *ifc_element_get_transform(ifc_element_t *p) { try { return p->transform;   }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}


topo_shape_t *ifc_element_get_shape(ifc_element_t *p) { try {
  return new topo_shape_t{
      .shp = p->shp,
  };
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

const char *ifc_element_get_type(ifc_element_t *p) { try { return p->type.c_str();   }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

ifc_element_t *ifc_get_element(ifc_element_t **elements, int index) { try {
  return elements[index];
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

void ifc_triangulation_free(ifc_triangulation_t *p) { try {
  if (p) {
      if(p->transform!=nullptr){
          delete [] p->transform;
      }
    delete p;
  }
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

const double *ifc_triangulation_get_verts(ifc_triangulation_t *p, int *count) { try {
  auto &tri = p->tri;
  *count = static_cast<int>(tri->verts().size());
  return tri->verts().data();
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

const int *ifc_triangulation_get_faces(ifc_triangulation_t *p, int *count) { try {
  auto &tri = p->tri;
  *count = static_cast<int>(tri->faces().size());
  return tri->faces().data();
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

const double *ifc_triangulation_get_normals(ifc_triangulation_t *p,
                                            int *count) { try {
  auto &tri = p->tri;
  *count = static_cast<int>(tri->normals().size());
  return tri->normals().data();
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

const int *ifc_triangulation_get_edges(ifc_triangulation_t *p, int *count) { try {
  auto &tri = p->tri;
  *count = static_cast<int>(tri->edges().size());
  return tri->edges().data();
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

const double *ifc_triangulation_get_uvs(ifc_triangulation_t *p, int *count) { try {
  auto &tri = p->tri;
  *count = static_cast<int>(tri->uvs().size());
  return tri->uvs().data();
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

const int *ifc_triangulation_get_material_ids(ifc_triangulation_t *p,
                                              int *count) { try {
  auto &tri = p->tri;
  *count = static_cast<int>(tri->material_ids().size());
  return tri->material_ids().data();
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

const int *ifc_triangulation_get_item_ids(ifc_triangulation_t *p, int *count) { try {
  auto &tri = p->tri;
  *count = static_cast<int>(tri->item_ids().size());
  return tri->item_ids().data();
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

int ifc_triangulation_get_id(ifc_triangulation_t *p) { try { return p->id;   }
  catch (const std::exception &e) {
    (void)e;
    return 0;
  }
  catch (...) {
    return 0;
  }
}

int ifc_triangulation_get_parent_id(ifc_triangulation_t *p) { try { return p->parent_id;   }
  catch (const std::exception &e) {
    (void)e;
    return 0;
  }
  catch (...) {
    return 0;
  }
}

const char *ifc_triangulation_get_name(ifc_triangulation_t *p) { try { return p->name.c_str();   }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

const char *ifc_triangulation_get_guid(ifc_triangulation_t *p) { try { return p->guid.c_str();   }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

const char *ifc_triangulation_get_type(ifc_triangulation_t *p) { try { return p->type.c_str();   }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

const double *ifc_triangulation_get_transform(ifc_triangulation_t *p) { try {
  return p->transform;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

const int *ifc_triangulation_get_edges_item_ids(ifc_triangulation_t *p,
                                                int *count) { try {
  auto &tri = p->tri;
  *count = static_cast<int>(tri->edges_item_ids().size());
  return tri->edges_item_ids().data();
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

ifc_triangulation_material_t *
ifc_triangulation_get_materials(ifc_triangulation_t *p, int *count) { try {
  auto &tri = p->tri;
  auto &materials = tri->materials();
  *count = static_cast<int>(materials.size());
  auto mtls = new ifc_triangulation_material_t[materials.size()];
  for (size_t i = 0; i < materials.size(); i++) {
    mtls[i].mtl = materials[i];
  }
  return mtls;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

void ifc_triangulation_materials_free(ifc_triangulation_material_t *mtls) { try {
  if (mtls) {
    delete[] mtls;
  }
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

const char *
ifc_triangulation_material_get_name(ifc_triangulation_material_t *mtl) { try {
  return mtl->mtl->name.c_str();
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

ifc_color_t
ifc_triangulation_material_get_diffuse(ifc_triangulation_material_t *mtl) { try {
  const auto &c = mtl->mtl->diffuse;
  return ifc_color_t{c.r(), c.g(), c.b()};
  }
  catch (const std::exception &e) {
    (void)e;
    return ifc_color_t{};
  }
  catch (...) {
    return ifc_color_t{};
  }
}

ifc_color_t
ifc_triangulation_material_get_surface(ifc_triangulation_material_t *mtl) { try {
  const auto &c = mtl->mtl->surface;
  return ifc_color_t{c.r(), c.g(), c.b()};
  }
  catch (const std::exception &e) {
    (void)e;
    return ifc_color_t{};
  }
  catch (...) {
    return ifc_color_t{};
  }
}

ifc_color_t
ifc_triangulation_material_get_specular(ifc_triangulation_material_t *mtl) { try {
  const auto &c = mtl->mtl->specular;
  return ifc_color_t{c.r(), c.g(), c.b()};
  }
  catch (const std::exception &e) {
    (void)e;
    return ifc_color_t{};
  }
  catch (...) {
    return ifc_color_t{};
  }
}

double
ifc_triangulation_material_get_specularity(ifc_triangulation_material_t *mtl) { try {
  return mtl->mtl->specularity;
  }
  catch (const std::exception &e) {
    (void)e;
    return 0;
  }
  catch (...) {
    return 0;
  }
}

double
ifc_triangulation_material_get_transparency(ifc_triangulation_material_t *mtl) { try {
  return mtl->mtl->transparency;
  }
  catch (const std::exception &e) {
    (void)e;
    return 0;
  }
  catch (...) {
    return 0;
  }
}
int ifc_triangulation_material_size() { try {
    return sizeof(ifc_triangulation_material_t);
  }
  catch (const std::exception &e) {
    (void)e;
    return 0;
  }
  catch (...) {
    return 0;
  }
}

IFCCAPICALL void ifc_header_free(ifc_header_t *header) { try {
  if (header) {
    delete header;
  }
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

// FileDescription 相关函数实现
IFCCAPICALL const char *
ifc_header_get_implementation_level(ifc_header_t *header) { try {
  return header ? header->header.file_description.implementation_level.c_str()
                : nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL const char **ifc_header_get_descriptions(ifc_header_t *header,
                                                     int *count) { try {
  if (!header || !count)
    return nullptr;

  *count = header->header.file_description.description.size();
  if (*count == 0)
    return nullptr;

  const char **result = new const char *[*count];
  for (int i = 0; i < *count; ++i) {
    result[i] = header->header.file_description.description[i].c_str();
  }
  return result;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL void ifc_header_free_descriptions(const char **descriptions) { try {
  if (descriptions) {
    delete[] descriptions;
  }
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

// FileName 相关函数实现
IFCCAPICALL const char *ifc_header_get_filename(ifc_header_t *header) { try {
  return header ? header->header.file_name.name.c_str() : nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL const char **ifc_header_get_authors(ifc_header_t *header,
                                                int *count) { try {
  if (!header || !count)
    return nullptr;

  *count = header->header.file_name.author.size();
  if (*count == 0)
    return nullptr;

  const char **result = new const char *[*count];
  for (int i = 0; i < *count; ++i) {
    result[i] = header->header.file_name.author[i].c_str();
  }
  return result;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL void ifc_header_free_authors(const char **authors) { try {
  if (authors) {
    delete[] authors;
  }
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

IFCCAPICALL const char **ifc_header_get_organizations(ifc_header_t *header,
                                                      int *count) { try {
  if (!header || !count)
    return nullptr;

  *count = header->header.file_name.organization.size();
  if (*count == 0)
    return nullptr;

  const char **result = new const char *[*count];
  for (int i = 0; i < *count; ++i) {
    result[i] = header->header.file_name.organization[i].c_str();
  }
  return result;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL void ifc_header_free_organizations(const char **organizations) { try {
  if (organizations) {
    delete[] organizations;
  }
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

IFCCAPICALL const char *ifc_header_get_timestamp(ifc_header_t *header) { try {
  return header ? header->header.file_name.time_stamp.c_str() : nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL const char *
ifc_header_get_preprocessor_version(ifc_header_t *header) { try {
  return header ? header->header.file_name.preprocessor_version.c_str()
                : nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL const char *
ifc_header_get_originating_system(ifc_header_t *header) { try {
  return header ? header->header.file_name.originating_system.c_str() : nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL const char *ifc_header_get_authorization(ifc_header_t *header) { try {
  return header ? header->header.file_name.authorization.c_str() : nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

// FileSchema 相关函数实现
IFCCAPICALL const char **ifc_header_get_schema_identifiers(ifc_header_t *header,
                                                           int *count) { try {
  if (!header || !count)
    return nullptr;

  *count = header->header.file_schema.schema_identifiers.size();
  if (*count == 0)
    return nullptr;

  const char **result = new const char *[*count];
  for (int i = 0; i < *count; ++i) {
    result[i] = header->header.file_schema.schema_identifiers[i].c_str();
  }
  return result;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL void ifc_header_free_schema_identifiers(const char **identifiers) { try {
  if (identifiers) {
    delete[] identifiers;
  }
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

IFCCAPICALL void ifc_unit_free(ifc_unit_t *unit) { try {
  if (unit) {
    delete unit;
  }
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

IFCCAPICALL const char *ifc_unit_get_type(ifc_unit_t *unit) { try {
  return unit ? unit->unit.type.c_str() : nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL const char *ifc_unit_get_name(ifc_unit_t *unit) { try {
  return unit ? unit->unit.name.c_str() : nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL _Bool ifc_unit_has_SI_equivalent(ifc_unit_t *unit) { try {
  return unit ? unit->unit.SI_equivalent.is_initialized() : false;
  }
  catch (const std::exception &e) {
    (void)e;
    return false;
  }
  catch (...) {
    return false;
  }
}

IFCCAPICALL double ifc_unit_get_SI_equivalent(ifc_unit_t *unit) { try {
  if (!unit || !unit->unit.SI_equivalent) {
    return 0.0;
  }
  return *unit->unit.SI_equivalent;
  }
  catch (const std::exception &e) {
    (void)e;
    return 0;
  }
  catch (...) {
    return 0;
  }
}

IFCCAPICALL void ifc_property_free(ifc_property_t *property) { try {
  if (property) {
    delete property;
  }
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

IFCCAPICALL const char *ifc_property_get_name(ifc_property_t *property) { try {
  return property ? property->property.name.c_str() : nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL const char *ifc_property_get_type(ifc_property_t *property) { try {
  return property ? property->property.type.c_str() : nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL _Bool ifc_property_is_null(ifc_property_t *property) { try {
  return property
             ? boost::get<boost::blank>(&property->property.value) != nullptr
             : false;
  }
  catch (const std::exception &e) {
    (void)e;
    return false;
  }
  catch (...) {
    return false;
  }
}

IFCCAPICALL _Bool ifc_property_is_int(ifc_property_t *property) { try {
  return property ? boost::get<int>(&property->property.value) != nullptr
                  : false;
  }
  catch (const std::exception &e) {
    (void)e;
    return false;
  }
  catch (...) {
    return false;
  }
}

IFCCAPICALL _Bool ifc_property_is_bool(ifc_property_t *property) { try {
  return property ? boost::get<bool>(&property->property.value) != nullptr
                  : false;
  }
  catch (const std::exception &e) {
    (void)e;
    return false;
  }
  catch (...) {
    return false;
  }
}

IFCCAPICALL _Bool ifc_property_is_double(ifc_property_t *property) { try {
  return property ? boost::get<double>(&property->property.value) != nullptr
                  : false;
  }
  catch (const std::exception &e) {
    (void)e;
    return false;
  }
  catch (...) {
    return false;
  }
}

IFCCAPICALL _Bool ifc_property_is_string(ifc_property_t *property) { try {
  return property
             ? boost::get<std::string>(&property->property.value) != nullptr
             : false;
  }
  catch (const std::exception &e) {
    (void)e;
    return false;
  }
  catch (...) {
    return false;
  }
}

IFCCAPICALL _Bool ifc_property_is_bitset(ifc_property_t *property) { try {
  if (!property)
    return false;
  return property->property.value.type() == typeid(boost::dynamic_bitset<>);
  }
  catch (const std::exception &e) {
    (void)e;
    return false;
  }
  catch (...) {
    return false;
  }
}

IFCCAPICALL _Bool ifc_property_is_int_vector(ifc_property_t *property) { try {
  if (!property)
    return false;
  return property->property.value.type() == typeid(std::vector<int>);
  }
  catch (const std::exception &e) {
    (void)e;
    return false;
  }
  catch (...) {
    return false;
  }
}

IFCCAPICALL _Bool ifc_property_is_double_vector(ifc_property_t *property) { try {
  if (!property)
    return false;
  return property->property.value.type() == typeid(std::vector<double>);
  }
  catch (const std::exception &e) {
    (void)e;
    return false;
  }
  catch (...) {
    return false;
  }
}

IFCCAPICALL _Bool ifc_property_is_string_vector(ifc_property_t *property) { try {
  if (!property)
    return false;
  return property->property.value.type() == typeid(std::vector<std::string>);
  }
  catch (const std::exception &e) {
    (void)e;
    return false;
  }
  catch (...) {
    return false;
  }
}

IFCCAPICALL _Bool ifc_property_is_bitset_vector(ifc_property_t *property) { try {
  if (!property)
    return false;
  return property->property.value.type() ==
         typeid(std::vector<boost::dynamic_bitset<>>);
  }
  catch (const std::exception &e) {
    (void)e;
    return false;
  }
  catch (...) {
    return false;
  }
}

IFCCAPICALL _Bool ifc_property_is_int_matrix(ifc_property_t *property) { try {
  if (!property)
    return false;
  return property->property.value.type() ==
         typeid(std::vector<std::vector<int>>);
  }
  catch (const std::exception &e) {
    (void)e;
    return false;
  }
  catch (...) {
    return false;
  }
}

IFCCAPICALL _Bool ifc_property_is_double_matrix(ifc_property_t *property) { try {
  if (!property)
    return false;
  return property->property.value.type() ==
         typeid(std::vector<std::vector<double>>);
  }
  catch (const std::exception &e) {
    (void)e;
    return false;
  }
  catch (...) {
    return false;
  }
}

IFCCAPICALL int ifc_property_get_int(ifc_property_t *property) { try {
  if (!property || !ifc_property_is_int(property))
    return 0;
  return boost::get<int>(property->property.value);
  }
  catch (const std::exception &e) {
    (void)e;
    return 0;
  }
  catch (...) {
    return 0;
  }
}

IFCCAPICALL _Bool ifc_property_get_bool(ifc_property_t *property) { try {
  if (!property || !ifc_property_is_bool(property))
    return false;
  return boost::get<bool>(property->property.value);
  }
  catch (const std::exception &e) {
    (void)e;
    return false;
  }
  catch (...) {
    return false;
  }
}

IFCCAPICALL double ifc_property_get_double(ifc_property_t *property) { try {
  if (!property || !ifc_property_is_double(property))
    return 0.0;
  return boost::get<double>(property->property.value);
  }
  catch (const std::exception &e) {
    (void)e;
    return 0;
  }
  catch (...) {
    return 0;
  }
}

IFCCAPICALL const char *ifc_property_get_string(ifc_property_t *property) { try {
  if (!property || !ifc_property_is_string(property))
    return nullptr;
  return boost::get<std::string>(property->property.value).c_str();
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL const unsigned char *
ifc_property_get_bitset(ifc_property_t *property, int *size) { try {
  if (!property || !size || !ifc_property_is_bitset(property))
    return nullptr;

  auto &bitset = boost::get<boost::dynamic_bitset<>>(property->property.value);
  *size = bitset.size();
  // to_block_range 按 block (通常 64 bit) 写入, 缓冲必须按 block 对齐取整
  size_t bytes =
      bitset.num_blocks() * sizeof(boost::dynamic_bitset<>::block_type);
  if (bytes == 0) {
    bytes = 1;
  }
  unsigned char *result = new unsigned char[bytes];
  std::memset(result, 0, bytes);
  boost::to_block_range(bitset, result);
  return result;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL const int *ifc_property_get_int_vector(ifc_property_t *property,
                                                   int *count) { try {
  if (!property || !count || !ifc_property_is_int_vector(property))
    return nullptr;

  auto &vec = boost::get<std::vector<int>>(property->property.value);
  *count = vec.size();
  int *result = new int[*count];
  std::copy(vec.begin(), vec.end(), result);
  return result;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL const double *
ifc_property_get_double_vector(ifc_property_t *property, int *count) { try {
  if (!property || !count || !ifc_property_is_double_vector(property))
    return nullptr;

  auto &vec = boost::get<std::vector<double>>(property->property.value);
  *count = vec.size();
  double *result = new double[*count];
  std::copy(vec.begin(), vec.end(), result);
  return result;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL const char **
ifc_property_get_string_vector(ifc_property_t *property, int *count) { try {
  if (!property || !count || !ifc_property_is_string_vector(property))
    return nullptr;

  auto &vec = boost::get<std::vector<std::string>>(property->property.value);
  *count = vec.size();
  const char **result = new const char *[*count];
  for (int i = 0; i < *count; ++i) {
    result[i] = vec[i].c_str();
  }
  return result;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL unsigned char **
ifc_property_get_bitset_vector(ifc_property_t *property, int *count,
                               int **sizes) { try {
  if (!property || !count || !sizes || !ifc_property_is_bitset_vector(property))
    return nullptr;

  auto &vec = boost::get<std::vector<boost::dynamic_bitset<>>>(
      property->property.value);
  *count = vec.size();
  unsigned char **result = new unsigned char *[*count];
  *sizes = new int[*count];

  for (int i = 0; i < *count; ++i) {
    (*sizes)[i] = vec[i].size();
    size_t bytes =
        vec[i].num_blocks() * sizeof(boost::dynamic_bitset<>::block_type);
    if (bytes == 0) {
      bytes = 1;
    }
    result[i] = new unsigned char[bytes];
    std::memset(result[i], 0, bytes);
    boost::to_block_range(vec[i], result[i]);
  }
  return result;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL const int **ifc_property_get_int_matrix(ifc_property_t *property,
                                                    int *rows, int *cols) { try {
  if (!property || !rows || !cols || !ifc_property_is_int_matrix(property))
    return nullptr;

  auto &matrix =
      boost::get<std::vector<std::vector<int>>>(property->property.value);
  *rows = matrix.size();
  *cols = (*rows > 0) ? matrix[0].size() : 0;
  // 锯齿矩阵会按第 0 行列数拷贝导致堆溢出, 直接拒绝
  for (const auto &row : matrix) {
    if (row.size() != *cols) {
      *rows = 0;
      *cols = 0;
      return nullptr;
    }
  }

  int **result = new int *[*rows > 0 ? *rows : 1];
  for (int i = 0; i < *rows; ++i) {
    result[i] = new int[*cols];
    std::copy(matrix[i].begin(), matrix[i].end(), result[i]);
  }
  return const_cast<const int **>(result);
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL const double **
ifc_property_get_double_matrix(ifc_property_t *property, int *rows, int *cols) { try {
  if (!property || !rows || !cols || !ifc_property_is_double_matrix(property))
    return nullptr;

  auto &matrix =
      boost::get<std::vector<std::vector<double>>>(property->property.value);
  *rows = matrix.size();
  *cols = (*rows > 0) ? matrix[0].size() : 0;
  for (const auto &row : matrix) {
    if (row.size() != *cols) {
      *rows = 0;
      *cols = 0;
      return nullptr;
    }
  }

  double **result = new double *[*rows > 0 ? *rows : 1];
  for (int i = 0; i < *rows; ++i) {
    result[i] = new double[*cols];
    std::copy(matrix[i].begin(), matrix[i].end(), result[i]);
  }
  return const_cast<const double **>(result);
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

// 元素可能是 new unsigned char[] / new int[] / new double[] / new char*[]
// 等 POD 数组, 统一用无类型 operator delete[] 释放, 避免跨类型 delete[] 的 UB。
IFCCAPICALL void ifc_property_free_vector(void *vec) { try {
  if (vec) {
    ::operator delete[](vec);
  }
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

IFCCAPICALL void ifc_property_free_matrix(void **matrix, int rows) { try {
  if (!matrix)
    return;

  for (int i = 0; i < rows; ++i) {
    if (matrix[i]) {
      ::operator delete[](matrix[i]);
    }
  }
  ::operator delete[](matrix);
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

IFCCAPICALL void ifc_property_set_free(ifc_property_set_t *ps) { try {
  if (ps) {
    delete ps;
  }
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

IFCCAPICALL const char *ifc_property_set_get_id(ifc_property_set_t *ps) { try {
  return ps ? ps->ps.id.c_str() : nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL const char *ifc_property_set_get_name(ifc_property_set_t *ps) { try {
  return ps ? ps->ps.name.c_str() : nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL ifc_property_t **
ifc_property_set_get_properties(ifc_property_set_t *ps, int *count) { try {
  if (!ps || !count)
    return nullptr;

  *count = ps->ps.properties.size();
  if (*count == 0)
    return nullptr;

  ifc_property_t **result = new ifc_property_t *[*count];
  for (int i = 0; i < *count; ++i) {
    result[i] = new _ifc_property_t{ps->ps.properties[i]};
  }
  return result;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL void ifc_property_set_free_properties(ifc_property_t **properties) { try {
  if (!properties)
    return;
  delete[] properties;
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

IFCCAPICALL void ifc_quantity_free(ifc_quantity_t *quantity) { try {
  if (quantity) {
    delete quantity;
  }
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

IFCCAPICALL const char *ifc_quantity_get_type(ifc_quantity_t *quantity) { try {
  return quantity ? quantity->quantity.type.c_str() : nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL const char *ifc_quantity_get_name(ifc_quantity_t *quantity) { try {
  return quantity ? quantity->quantity.name.c_str() : nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL double ifc_quantity_get_value(ifc_quantity_t *quantity) { try {
  return quantity ? quantity->quantity.value : 0.0;
  }
  catch (const std::exception &e) {
    (void)e;
    return 0;
  }
  catch (...) {
    return 0;
  }
}

IFCCAPICALL const char *ifc_quantity_get_unit(ifc_quantity_t *quantity) { try {
  return quantity ? quantity->quantity.unit.c_str() : nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL void ifc_element_quantity_free(ifc_element_quantity_t *eq) { try {
  if (eq) {
    delete eq;
  }
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

IFCCAPICALL const char *
ifc_element_quantity_get_id(ifc_element_quantity_t *eq) { try {
  return eq ? eq->quantity.id.c_str() : nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL const char *
ifc_element_quantity_get_name(ifc_element_quantity_t *eq) { try {
  return eq ? eq->quantity.name.c_str() : nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL ifc_quantity_t **
ifc_element_quantity_get_quantities(ifc_element_quantity_t *eq, int *count) { try {
  if (!eq || !count)
    return nullptr;

  *count = eq->quantity.quantities.size();
  if (*count == 0)
    return nullptr;

  ifc_quantity_t **result = new ifc_quantity_t *[*count];
  for (int i = 0; i < *count; ++i) {
    result[i] = new _ifc_quantity_t{eq->quantity.quantities[i]};
  }
  return result;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL void
ifc_element_quantity_free_quantities(ifc_quantity_t **quantities) { try {
  if (!quantities)
    return;
  delete[] quantities;
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

IFCCAPICALL void ifc_task_time_free(ifc_task_time_t *tt) { try {
  if (tt) {
    delete tt;
  }
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

IFCCAPICALL const char *ifc_task_time_get_schedule_start(ifc_task_time_t *tt) { try {
  return tt ? tt->time.schedule_start.c_str() : nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL const char *ifc_task_time_get_schedule_finish(ifc_task_time_t *tt) { try {
  return tt ? tt->time.schedule_finish.c_str() : nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL const char *ifc_task_time_get_actual_start(ifc_task_time_t *tt) { try {
  return tt ? tt->time.actual_start.c_str() : nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL const char *ifc_task_time_get_actual_finish(ifc_task_time_t *tt) { try {
  return tt ? tt->time.actual_finish.c_str() : nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL const char *ifc_task_time_get_free_float(ifc_task_time_t *tt) { try {
  return tt ? tt->time.free_float.c_str() : nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL const char *ifc_task_time_get_total_float(ifc_task_time_t *tt) { try {
  return tt ? tt->time.total_float.c_str() : nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL _Bool ifc_task_time_is_critical(ifc_task_time_t *tt) { try {
  return tt ? tt->time.is_critical : false;
  }
  catch (const std::exception &e) {
    (void)e;
    return false;
  }
  catch (...) {
    return false;
  }
}

IFCCAPICALL void ifc_task_free(ifc_task_t *task) { try {
  if (task) {
    delete task;
  }
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

// 基本属性实现
IFCCAPICALL const char *ifc_task_get_id(ifc_task_t *task) { try {
  return task ? task->task.id.c_str() : nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL const char *ifc_task_get_name(ifc_task_t *task) { try {
  return task ? task->task.name.c_str() : nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL const char *ifc_task_get_status(ifc_task_t *task) { try {
  return task ? task->task.status.c_str() : nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL const char *ifc_task_get_description(ifc_task_t *task) { try {
  return task ? task->task.description.c_str() : nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL const char *ifc_task_get_object_type(ifc_task_t *task) { try {
  return task ? task->task.object_type.c_str() : nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL const char *ifc_task_get_work_method(ifc_task_t *task) { try {
  return task ? task->task.work_method.c_str() : nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL int ifc_task_get_priority(ifc_task_t *task) { try {
  return task ? task->task.priority : 0;
  }
  catch (const std::exception &e) {
    (void)e;
    return 0;
  }
  catch (...) {
    return 0;
  }
}

IFCCAPICALL _Bool ifc_task_is_milestone(ifc_task_t *task) { try {
  return task ? task->task.is_milestone : false;
  }
  catch (const std::exception &e) {
    (void)e;
    return false;
  }
  catch (...) {
    return false;
  }
}

IFCCAPICALL ifc_task_time_t *ifc_task_get_task_time(ifc_task_t *task) { try {
  if (!task || !task->task.task_time)
    return nullptr;
  return new _ifc_task_time_t{*task->task.task_time};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL const char **ifc_task_get_predecessors(ifc_task_t *task,
                                                   int *count) { try {
  if (!task || !count)
    return nullptr;
  return get_string_vector(task->task.predecessor_tasks, count);
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL const char **ifc_task_get_successors(ifc_task_t *task, int *count) { try {
  if (!task || !count)
    return nullptr;
  return get_string_vector(task->task.successor_tasks, count);
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

// 子任务
IFCCAPICALL ifc_task_t **ifc_task_get_subtasks(ifc_task_t *task, int *count) { try {
  if (!task || !count)
    return nullptr;

  *count = task->task.subtasks.size();
  if (*count == 0)
    return nullptr;

  ifc_task_t **result = new ifc_task_t *[*count];
  for (int i = 0; i < *count; ++i) {
    result[i] = new _ifc_task_t{task->task.subtasks[i]};
  }
  return result;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

// 列表释放函数
IFCCAPICALL void ifc_task_free_string_list(const char **list) { try {
  if (list)
    delete[] list;
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

IFCCAPICALL void ifc_task_free_subtasks(ifc_task_t **subtasks) { try {
  if (!subtasks)
    return;

  delete[] subtasks;
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

IFCCAPICALL void ifc_work_time_free(ifc_work_time_t *wt) { try {
  if (wt) {
    delete wt;
  }
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

IFCCAPICALL const char *ifc_work_time_get_name(ifc_work_time_t *wt) { try {
  return wt ? wt->tm.name.c_str() : nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL const char *ifc_work_time_get_start_time(ifc_work_time_t *wt) { try {
  return wt ? wt->tm.start_time.c_str() : nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL const char *ifc_work_time_get_finish_time(ifc_work_time_t *wt) { try {
  return wt ? wt->tm.finish_time.c_str() : nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL void ifc_work_calendar_free(ifc_work_calendar_t *wc) { try {
  if (wc) {
    delete wc;
  }
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

IFCCAPICALL const char *ifc_work_calendar_get_id(ifc_work_calendar_t *wc) { try {
  return wc ? wc->wc.id.c_str() : nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL const char *ifc_work_calendar_get_name(ifc_work_calendar_t *wc) { try {
  return wc ? wc->wc.name.c_str() : nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL ifc_work_time_t **
ifc_work_calendar_get_working_times(ifc_work_calendar_t *wc, int *count) { try {
  if (!wc || !count)
    return nullptr;

  *count = wc->wc.working_times.size();
  if (*count == 0)
    return nullptr;

  ifc_work_time_t **result = new ifc_work_time_t *[*count];
  for (int i = 0; i < *count; ++i) {
    result[i] = new _ifc_work_time_t{wc->wc.working_times[i]};
  }
  return result;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL void
ifc_work_calendar_free_working_times(ifc_work_time_t **working_times) { try {
  if (!working_times)
    return;
  delete[] working_times;
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

IFCCAPICALL void ifc_work_schedule_free(ifc_work_schedule_t *ws) { try {
  if (ws) {
    delete ws;
  }
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

IFCCAPICALL const char *ifc_work_schedule_get_id(ifc_work_schedule_t *ws) { try {
  return ws ? ws->ws.id.c_str() : nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL const char *ifc_work_schedule_get_name(ifc_work_schedule_t *ws) { try {
  return ws ? ws->ws.name.c_str() : nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL ifc_task_t **ifc_work_schedule_get_tasks(ifc_work_schedule_t *ws,
                                                     int *count) { try {
  if (!ws || !count)
    return nullptr;

  *count = ws->ws.tasks.size();
  if (*count == 0)
    return nullptr;

  ifc_task_t **result = new ifc_task_t *[*count];
  for (int i = 0; i < *count; ++i) {
    result[i] = new _ifc_task_t{ws->ws.tasks[i]};
  }
  return result;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL void ifc_work_schedule_free_tasks(ifc_task_t **tasks) { try {
  if (!tasks)
    return;

  delete[] tasks;
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

IFCCAPICALL const char *ifc_work_schedule_get_purpose(ifc_work_schedule_t *ws) { try {
  if (!ws)
    return NULL;
  return ws->ws.purpose.c_str();
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL const char *
ifc_work_schedule_get_start_time(ifc_work_schedule_t *ws) { try {
  if (!ws)
    return NULL;
  return ws->ws.start_time.c_str();
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL const char *
ifc_work_schedule_get_finish_time(ifc_work_schedule_t *ws) { try {
  if (!ws)
    return NULL;
  return ws->ws.finish_time.c_str();
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL double ifc_work_schedule_get_duration(ifc_work_schedule_t *ws) { try {
  if (!ws)
    return 0.0;
  return ws->ws.duration;
  }
  catch (const std::exception &e) {
    (void)e;
    return 0;
  }
  catch (...) {
    return 0;
  }
}

IFCCAPICALL double ifc_work_schedule_get_total_float(ifc_work_schedule_t *ws) { try {
  if (!ws)
    return 0.0;
  return ws->ws.total_float;
  }
  catch (const std::exception &e) {
    (void)e;
    return 0;
  }
  catch (...) {
    return 0;
  }
}

IFCCAPICALL const char **ifc_work_schedule_get_creators(ifc_work_schedule_t *ws,
                                                        int *count) { try {
  if (!ws || !count)
    return NULL;

  *count = ws->ws.creators.size();
  if (*count == 0)
    return NULL;

  const char **result = (const char **)malloc(*count * sizeof(const char *));
  for (int i = 0; i < *count; i++) {
    result[i] = ws->ws.creators[i].c_str();
  }
  return result;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL void ifc_work_schedule_free_creators(const char **creators) { try {
  if (creators) {
    free(creators);
  }
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}
IFCCAPICALL void ifc_work_plan_free(ifc_work_plan_t *wp) { try {
  if (wp) {
    delete wp;
  }
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

IFCCAPICALL const char *ifc_work_plan_get_id(ifc_work_plan_t *wp) { try {
  return wp ? wp->wp.id.c_str() : nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL const char *ifc_work_plan_get_name(ifc_work_plan_t *wp) { try {
  return wp ? wp->wp.name.c_str() : nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL const char **
ifc_work_plan_get_work_schedule_ids(ifc_work_plan_t *wp, int *count) { try {
  if (!wp || !count)
    return nullptr;

  *count = wp->wp.work_schedule_ids.size();
  if (*count == 0)
    return nullptr;

  const char **result = new const char *[*count];
  for (int i = 0; i < *count; ++i) {
    result[i] = wp->wp.work_schedule_ids[i].c_str();
  }
  return result;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL void ifc_work_plan_free_work_schedule_ids(const char **ids) { try {
  if (ids) {
    delete[] ids;
  }
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

IFCCAPICALL const char *ifc_work_plan_get_purpose(ifc_work_plan_t *wp) { try {
  if (!wp)
    return NULL;
  return wp->wp.purpose.c_str();
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL const char *ifc_work_plan_get_start_time(ifc_work_plan_t *wp) { try {
  if (!wp)
    return NULL;
  return wp->wp.start_time.c_str();
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL const char *ifc_work_plan_get_finish_time(ifc_work_plan_t *wp) { try {
  if (!wp)
    return NULL;
  return wp->wp.finish_time.c_str();
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL double ifc_work_plan_get_duration(ifc_work_plan_t *wp) { try {
  if (!wp)
    return 0.0;
  return wp->wp.duration;
  }
  catch (const std::exception &e) {
    (void)e;
    return 0;
  }
  catch (...) {
    return 0;
  }
}

IFCCAPICALL double ifc_work_plan_get_total_float(ifc_work_plan_t *wp) { try {
  if (!wp)
    return 0.0;
  return wp->wp.total_float;
  }
  catch (const std::exception &e) {
    (void)e;
    return 0;
  }
  catch (...) {
    return 0;
  }
}

IFCCAPICALL const char **ifc_work_plan_get_creators(ifc_work_plan_t *wp,
                                                    int *count) { try {
  if (!wp || !count)
    return NULL;

  *count = wp->wp.creators.size();
  if (*count == 0)
    return NULL;

  const char **result = (const char **)malloc(*count * sizeof(const char *));
  for (int i = 0; i < *count; i++) {
    result[i] = wp->wp.creators[i].c_str();
  }
  return result;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL void ifc_work_plan_free_creators(const char **creators) { try {
  if (creators) {
    free(creators);
  }
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}
IFCCAPICALL void ifc_connection_free(ifc_connection_t *conn) { try {
  if (conn) {
    delete conn;
  }
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

IFCCAPICALL const char *ifc_connection_get_id(ifc_connection_t *conn) { try {
  return conn ? conn->con.id.c_str() : nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL const char *
ifc_connection_get_relating_element_id(ifc_connection_t *conn) { try {
  return conn ? conn->con.relating_element_id.c_str() : nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL const char *
ifc_connection_get_related_element_id(ifc_connection_t *conn) { try {
  return conn ? conn->con.related_element_id.c_str() : nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL void ifc_type_object_free(ifc_type_object_t *obj) { try {
  if (obj) {
    delete obj;
  }
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

IFCCAPICALL const char *ifc_type_object_get_id(ifc_type_object_t *obj) { try {
  return obj ? obj->obj.id.c_str() : nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL const char *ifc_type_object_get_name(ifc_type_object_t *obj) { try {
  return obj ? obj->obj.name.c_str() : nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL ifc_property_set_t **
ifc_type_object_get_property_sets(ifc_type_object_t *obj, int *count) { try {
  if (!obj || !count)
    return nullptr;

  *count = obj->obj.property_sets.size();
  if (*count == 0)
    return nullptr;

  ifc_property_set_t **result = new ifc_property_set_t *[*count];
  for (int i = 0; i < *count; ++i) {
    result[i] = new _ifc_property_set_t{obj->obj.property_sets[i]};
  }
  return result;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL void
ifc_type_object_free_property_sets(ifc_property_set_t **psets) { try {
  if (!psets)
    return;
  delete[] psets;
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

IFCCAPICALL void ifc_layer_free(ifc_layer_t *layer) { try {
  if (layer) {
    delete layer;
  }
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

IFCCAPICALL const char *ifc_layer_get_name(ifc_layer_t *layer) { try {
  return layer ? layer->lyr.name.c_str() : nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL const char *ifc_layer_get_id(ifc_layer_t *layer) { try {
  return layer ? layer->lyr.id.c_str() : nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL const char **ifc_layer_get_assigned_elements(ifc_layer_t *layer,
                                                         int *count) { try {
  if (!layer || !count)
    return nullptr;

  *count = layer->lyr.assigned_elements.size();
  if (*count == 0)
    return nullptr;

  const char **result = new const char *[*count];
  for (int i = 0; i < *count; ++i) {
    result[i] = layer->lyr.assigned_elements[i].c_str();
  }
  return result;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL const char *ifc_layer_get_description(ifc_layer_t *layer) { try {
  return layer ? layer->lyr.description.c_str() : nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL void ifc_layer_free_assigned_elements(const char **elements) { try {
  if (elements) {
    delete[] elements;
  }
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

IFCCAPICALL void ifc_material_free(ifc_material_t *mtl) { try {
  if (mtl) {
    delete mtl;
  }
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

IFCCAPICALL const char *ifc_material_get_id(ifc_material_t *mtl) { try {
  return mtl ? mtl->mtl.id.c_str() : nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL const char *ifc_material_get_name(ifc_material_t *mtl) { try {
  return mtl ? mtl->mtl.name.c_str() : nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL const char *ifc_material_get_description(ifc_material_t *mtl) { try {
  return mtl ? mtl->mtl.description.c_str() : nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL const char *ifc_material_get_category(ifc_material_t *mtl) { try {
  return mtl ? mtl->mtl.category.c_str() : nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL void ifc_group_free(ifc_group_t *group) { try {
  if (group) {
    delete group;
  }
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

IFCCAPICALL const char *ifc_group_get_id(ifc_group_t *group) { try {
  return group ? group->group.id.c_str() : nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL const char *ifc_group_get_name(ifc_group_t *group) { try {
  return group ? group->group.name.c_str() : nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL const char **ifc_group_get_member_ids(ifc_group_t *group,
                                                  int *count) { try {
  if (!group || !count)
    return nullptr;

  *count = group->group.member_ids.size();
  if (*count == 0)
    return nullptr;

  const char **result = new const char *[*count];
  for (int i = 0; i < *count; ++i) {
    result[i] = group->group.member_ids[i].c_str();
  }
  return result;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL void ifc_group_free_member_ids(const char **member_ids) { try {
  if (member_ids) {
    delete[] member_ids;
  }
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

IFCCAPICALL void ifc_data_free(ifc_data_t *data) { try {
  if (data) {
    delete data;
  }
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

IFCCAPICALL ifc_header_t *ifc_data_get_header(ifc_data_t *data) { try {
  if (!data)
    return nullptr;
  return new _ifc_header_t{data->data->header};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL ifc_unit_t **ifc_data_get_units(ifc_data_t *data, int *count) { try {
  if (!data || !count)
    return nullptr;
  return get_object_vector<_ifc_unit_t, ifcopenshell::data::IfcUnit>(
      data->data->units, count);
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL ifc_property_set_t **ifc_data_get_properties(ifc_data_t *data,
                                                         int *count) { try {
  if (!data || !count)
    return nullptr;
  return get_object_vector<_ifc_property_set_t,
                           ifcopenshell::data::IfcPropertySet>(
      data->data->properties, count);
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL ifc_element_quantity_t **ifc_data_get_quantities(ifc_data_t *data,
                                                             int *count) { try {
  if (!data || !count)
    return nullptr;
  return get_object_vector<_ifc_element_quantity_t,
                           ifcopenshell::data::IfcElementQuantity>(
      data->data->quantities, count);
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL ifc_work_schedule_t **ifc_data_get_work_schedules(ifc_data_t *data,
                                                              int *count) { try {
  if (!data || !count)
    return nullptr;
  return get_object_vector<_ifc_work_schedule_t,
                           ifcopenshell::data::IfcWorkSchedule>(
      data->data->work_schedules, count);
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL ifc_work_plan_t **ifc_data_get_work_plans(ifc_data_t *data,
                                                      int *count) { try {
  if (!data || !count)
    return nullptr;
  return get_object_vector<_ifc_work_plan_t, ifcopenshell::data::IfcWorkPlan>(
      data->data->work_plans, count);
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL ifc_work_calendar_t **ifc_data_get_calendars(ifc_data_t *data,
                                                         int *count) { try {
  if (!data || !count)
    return nullptr;
  return get_object_vector<_ifc_work_calendar_t,
                           ifcopenshell::data::IfcWorkCalendar>(
      data->data->calendars, count);
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL ifc_connection_t **ifc_data_get_connections(ifc_data_t *data,
                                                        int *count) { try {
  if (!data || !count)
    return nullptr;
  return get_object_vector<_ifc_connection_t,
                           ifcopenshell::data::IfcConnection>(
      data->data->connections, count);
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL ifc_type_object_t **ifc_data_get_types(ifc_data_t *data,
                                                   int *count) { try {
  if (!data || !count)
    return nullptr;
  return get_object_vector<_ifc_type_object_t,
                           ifcopenshell::data::IfcTypeObject>(data->data->types,
                                                              count);
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL ifc_layer_t **ifc_data_get_layers(ifc_data_t *data, int *count) { try {
  if (!data || !count)
    return nullptr;
  return get_object_vector<_ifc_layer_t, ifcopenshell::data::IfcLayer>(
      data->data->layers, count);
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL ifc_material_t **ifc_data_get_materials(ifc_data_t *data,
                                                    int *count) { try {
  if (!data || !count)
    return nullptr;
  return get_object_vector<_ifc_material_t, ifcopenshell::data::IfcMaterial>(
      data->data->materials, count);
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL ifc_group_t **ifc_data_get_groups(ifc_data_t *data, int *count) { try {
  if (!data || !count)
    return nullptr;
  return get_object_vector<_ifc_group_t, ifcopenshell::data::IfcGroup>(
      data->data->groups, count);
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL ifc_rel_defines_by_type_t **ifc_data_get_rel_defines_by_types(ifc_data_t *data, int *count){ try {
  if (!data || !count)
    return nullptr;
  return get_object_vector<_ifc_rel_defines_by_type_t, ifcopenshell::data::IfcRelDefinesByType>(
      data->data->rel_defines_by_types, count);
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL ifc_rel_defines_by_properties_t **ifc_data_get_rel_defines_by_properties(ifc_data_t *data, int *count){ try {
  if (!data || !count)
    return nullptr;
  return get_object_vector<_ifc_rel_defines_by_properties_t, ifcopenshell::data::IfcRelDefinesByProperties>(
      data->data->rel_defines_by_properties, count);
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}



IFCCAPICALL void ifc_data_free_units(ifc_unit_t **units) { try {
  free_object_vector(units);
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

IFCCAPICALL void ifc_data_free_properties(ifc_property_set_t **properties) { try {
  free_object_vector(properties);
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

IFCCAPICALL void ifc_data_free_quantities(ifc_element_quantity_t **quantities) { try {
  free_object_vector(quantities);
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

IFCCAPICALL void ifc_data_free_work_schedules(ifc_work_schedule_t **schedules) { try {
  free_object_vector(schedules);
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

IFCCAPICALL void ifc_data_free_work_plans(ifc_work_plan_t **plans) { try {
  free_object_vector(plans);
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

IFCCAPICALL void ifc_data_free_calendars(ifc_work_calendar_t **calendars) { try {
  free_object_vector(calendars);
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

IFCCAPICALL void ifc_data_free_connections(ifc_connection_t **connections) { try {
  free_object_vector(connections);
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

IFCCAPICALL void ifc_data_free_types(ifc_type_object_t **types) { try {
  free_object_vector(types);
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

IFCCAPICALL void ifc_data_free_layers(ifc_layer_t **layers) { try {
  free_object_vector(layers);
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

IFCCAPICALL void ifc_data_free_materials(ifc_material_t **materials) { try {
  free_object_vector(materials);
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

IFCCAPICALL void ifc_data_free_groups(ifc_group_t **groups) { try {
  free_object_vector(groups);
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

IFCCAPICALL void ifc_data_free_rel_defines_by_types(ifc_rel_defines_by_type_t **rdts) { try {
  free_object_vector(rdts);
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

IFCCAPICALL void ifc_data_free_rel_defines_by_properties(ifc_rel_defines_by_properties_t **rdts){ try {
  free_object_vector(rdts);
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

// IfcTimePeriod 相关函数实现
IFCCAPICALL const char *ifc_time_period_get_start_time(ifc_time_period_t *tp) { try {
  return tp->tp.start_time.c_str();
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL const char *ifc_time_period_get_end_time(ifc_time_period_t *tp) { try {
  return tp->tp.end_time.c_str();
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL void ifc_time_period_free(ifc_time_period_t *tp) { try {
  if (tp) {
    delete tp;
  }
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

// IfcRecurrencePattern 基本属性函数实现
IFCCAPICALL int
ifc_recurrence_pattern_get_position(ifc_recurrence_pattern_t *rp) { try {
  return rp->rp.position;
  }
  catch (const std::exception &e) {
    (void)e;
    return 0;
  }
  catch (...) {
    return 0;
  }
}

IFCCAPICALL int
ifc_recurrence_pattern_get_interval(ifc_recurrence_pattern_t *rp) { try {
  return rp->rp.interval;
  }
  catch (const std::exception &e) {
    (void)e;
    return 0;
  }
  catch (...) {
    return 0;
  }
}

IFCCAPICALL int
ifc_recurrence_pattern_get_occurrences(ifc_recurrence_pattern_t *rp) { try {
  return rp->rp.occurrences;
  }
  catch (const std::exception &e) {
    (void)e;
    return 0;
  }
  catch (...) {
    return 0;
  }
}

// IfcRecurrencePattern 数组属性函数实现
IFCCAPICALL const double *
ifc_recurrence_pattern_get_day_components(ifc_recurrence_pattern_t *rp,
                                          int *count) { try {
  *count = rp->rp.day_component.size();
  return rp->rp.day_component.data();
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL const double *
ifc_recurrence_pattern_get_weekday_components(ifc_recurrence_pattern_t *rp,
                                              int *count) { try {
  *count = rp->rp.weekday_component.size();
  return rp->rp.weekday_component.data();
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL const double *
ifc_recurrence_pattern_get_month_components(ifc_recurrence_pattern_t *rp,
                                            int *count) { try {
  *count = rp->rp.month_component.size();
  return rp->rp.month_component.data();
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL ifc_time_period_t **
ifc_recurrence_pattern_get_time_periods(ifc_recurrence_pattern_t *rp,
                                        int *count) { try {
  if (!rp || !count) {
    return nullptr;
  }
  *count = rp->rp.time_periods.size();
  if (*count == 0) {
    return nullptr;
  }
  // _ifc_time_period_t 内含 C++ 对象, 必须用 new 构造
  ifc_time_period_t **result = new ifc_time_period_t *[*count];
  for (int i = 0; i < *count; i++) {
    result[i] = new ifc_time_period_t{.tp = rp->rp.time_periods[i]};
  }
  return result;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL void ifc_recurrence_pattern_free(ifc_recurrence_pattern_t *rp) { try {
  if (rp) {
    delete rp;
  }
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

// 所有权契约: 元素由调用方经 ifc_time_period_free 逐个释放,
// 本函数仅释放指针数组本身。
IFCCAPICALL void
ifc_recurrence_pattern_free_time_periods(ifc_time_period_t **periods) { try {
  if (periods) {
    delete[] periods;
  }
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

IFCCAPICALL ifc_recurrence_pattern_t *
ifc_work_time_get_recurrence_pattern(ifc_work_time_t *wt) { try {
  if (!wt)
    return NULL;

  _ifc_recurrence_pattern_t *rp =
      new _ifc_recurrence_pattern_t{.rp = wt->tm.recurrence_pattern};
  return rp;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL const char * ifc_rel_defines_by_type_get_id(ifc_rel_defines_by_type_t *rdt){ try {
  return rdt->rdt.id.c_str();
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL const char * ifc_rel_defines_by_type_get_name(ifc_rel_defines_by_type_t *rdt){ try {
  return rdt->rdt.name.c_str();
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL const char * ifc_rel_defines_by_type_get_desc(ifc_rel_defines_by_type_t *rdt){ try {
  return rdt->rdt.desc.c_str();
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL const char * ifc_rel_defines_by_type_get_type_obj_id(ifc_rel_defines_by_type_t *rdt){ try {
  return rdt->rdt.type_object_id.c_str();
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL const char ** ifc_rel_defines_by_type_get_obj_ids(ifc_rel_defines_by_type_t *rdt, int *count){ try {
    if (!rdt || !count) {
    return nullptr;
  }

  *count = rdt->rdt.object_ids.size();
  if (*count == 0) {
    return nullptr;
  }

  // 分配指针数组
  const char **result = new const char *[*count];
  
  // 将每个string的c_str()存入指针数组
  for (int i = 0; i < *count; ++i) {
    result[i] = rdt->rdt.object_ids[i].c_str();
  }

  return result;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL void ifc_rel_defines_by_type_free_obj_ids(const char **ids) { try {
  if (ids) {
    delete[] ids;
  }
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}
IFCCAPICALL void ifc_rel_defines_by_type_free(ifc_rel_defines_by_type_t *rdt){ try {
    if (rdt) {
    delete rdt;
  }
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}


IFCCAPICALL const char * ifc_rel_defines_by_properties_get_id(ifc_rel_defines_by_properties_t *rdt){ try {
  return rdt->rdt.id.c_str();
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}
IFCCAPICALL const char * ifc_rel_defines_by_properties_get_name(ifc_rel_defines_by_properties_t *rdt){ try {
  return rdt->rdt.name.c_str();
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL const char * ifc_rel_defines_by_properties_get_desc(ifc_rel_defines_by_properties_t *rdt){ try {
  return rdt->rdt.desc.c_str();
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL const char ** ifc_rel_defines_by_properties_get_obj_ids(ifc_rel_defines_by_properties_t *rdt, int *count){ try {
     if (!rdt || !count) {
    return nullptr;
  }

  *count = rdt->rdt.object_ids.size();
  if (*count == 0) {
    return nullptr;
  }

   const char **result = new const char *[*count];
  
   for (int i = 0; i < *count; ++i) {
    result[i] = rdt->rdt.object_ids[i].c_str();
  }

  return result;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}
IFCCAPICALL const char* ifc_rel_defines_by_properties_get_propertyset_id(ifc_rel_defines_by_properties_t *rdt){ try {
    return  rdt->rdt.propertyset_id.c_str();
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

IFCCAPICALL void ifc_rel_defines_by_properties_free(ifc_rel_defines_by_properties_t *rdt){ try {
  if (rdt) {
    delete rdt;
  }
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

IFCCAPICALL void ifc_rel_defines_by_properties_free_obj_ids(const char **ids){ try {
  if (ids) {
    delete[] ids;
  }
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

#ifdef __cplusplus
}
#endif
