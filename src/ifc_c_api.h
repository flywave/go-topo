#ifndef GO_IFC_C_API_H
#define GO_IFC_C_API_H

#include "topo_c_api.h"

#if defined(WIN32) || defined(WINDOWS) || defined(_WIN32) || defined(_WINDOWS)
#define IFCCAPICALL __declspec(dllexport)
#else
#define IFCCAPICALL
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _ifc_convert_t ifc_convert_t;
typedef struct _ifc_element_t ifc_element_t;
typedef struct _ifc_triangulation_t ifc_triangulation_t;
typedef struct _ifc_material_t ifc_material_t;

typedef struct _ifc_color_t {
  double r;
  double g;
  double b;
} ifc_color_t;

IFCCAPICALL _Bool is_ifc_file(const char *filename);

IFCCAPICALL ifc_convert_t *ifc_convert_new();
IFCCAPICALL void ifc_convert_free(ifc_convert_t *p);
IFCCAPICALL _Bool ifc_convert_load(ifc_convert_t *p, const char *filename);
IFCCAPICALL char *ifc_convert_get_version(ifc_convert_t *p); // must free
IFCCAPICALL ifc_element_t **ifc_convert_get_elements(ifc_convert_t *p,
                                                     int *count);
IFCCAPICALL ifc_triangulation_t **
ifc_convert_get_triangulations(ifc_convert_t *p, int *count);

IFCCAPICALL ifc_element_t **ifc_get_elements(const char *filename, int *count);
IFCCAPICALL void ifc_elements_free(ifc_element_t **shps);
IFCCAPICALL ifc_element_t *ifc_get_element(ifc_element_t **elements, int index);

IFCCAPICALL ifc_triangulation_t **ifc_get_triangulations(const char *filename,
                                                         int *count);
IFCCAPICALL void ifc_triangulations_free(ifc_triangulation_t **triangulations);
IFCCAPICALL ifc_triangulation_t *
ifc_get_triangulation(ifc_triangulation_t **triangulations, int index);

IFCCAPICALL int ifc_element_get_id(ifc_element_t *p);
IFCCAPICALL int ifc_element_get_parent_id(ifc_element_t *p);
IFCCAPICALL const char *ifc_element_get_name(ifc_element_t *p);
IFCCAPICALL const char *ifc_element_get_guid(ifc_element_t *p);
IFCCAPICALL topo_shape_t *ifc_element_get_shape(ifc_element_t *p);

IFCCAPICALL void ifc_triangulation_free(ifc_triangulation_t *p);
IFCCAPICALL const double *ifc_triangulation_get_verts(ifc_triangulation_t *p,
                                                      int *count);
IFCCAPICALL const int *ifc_triangulation_get_faces(ifc_triangulation_t *p,
                                                   int *count);
IFCCAPICALL const double *ifc_triangulation_get_normals(ifc_triangulation_t *p,
                                                        int *count);
IFCCAPICALL const int *ifc_triangulation_get_edges(ifc_triangulation_t *p,
                                                   int *count);
IFCCAPICALL const double *ifc_triangulation_get_uvs(ifc_triangulation_t *p,
                                                    int *count);
IFCCAPICALL const int *
ifc_triangulation_get_material_ids(ifc_triangulation_t *p, int *count);
IFCCAPICALL const int *ifc_triangulation_get_item_ids(ifc_triangulation_t *p,
                                                      int *count);
IFCCAPICALL const int *
ifc_triangulation_get_edges_item_ids(ifc_triangulation_t *p, int *count);

IFCCAPICALL ifc_material_t *
ifc_triangulation_get_materials(ifc_triangulation_t *p, int *count);
IFCCAPICALL void ifc_materials_free(ifc_material_t *mtls);

IFCCAPICALL const char *ifc_material_get_name(ifc_material_t *mtl);
IFCCAPICALL ifc_color_t ifc_material_get_diffuse(ifc_material_t *mtl);
IFCCAPICALL ifc_color_t ifc_material_get_surface(ifc_material_t *mtl);
IFCCAPICALL ifc_color_t ifc_material_get_specular(ifc_material_t *mtl);
IFCCAPICALL double ifc_material_get_specularity(ifc_material_t *mtl);
IFCCAPICALL double ifc_material_get_transparency(ifc_material_t *mtl);

#ifdef __cplusplus
}
#endif

#endif