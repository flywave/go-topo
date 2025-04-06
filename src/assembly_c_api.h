#ifndef GO_ASSEMBLY_C_API_H
#define GO_ASSEMBLY_C_API_H

#include "standard_c_api.h"
#include "topo_c_api.h"
#include "workplane_c_api.h"

#if defined(WIN32) || defined(WINDOWS) || defined(_WIN32) || defined(_WINDOWS)
#define ASAPICALL __declspec(dllexport)
#else
#define ASAPICALL
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _assembly_object_t assembly_object_t;
typedef struct _assembly_element_t assembly_element_t;
typedef struct _assembly_t assembly_t;
typedef struct _constraint_param_t constraint_param_t;

ASAPICALL assembly_object_t *
assembly_object_create_from_shape(topo_shape_t *shape);
ASAPICALL assembly_object_t *
assembly_object_create_from_workplane(workplane_t *workplane);
ASAPICALL void assembly_object_free(assembly_object_t *obj);
ASAPICALL topo_shape_t *assembly_object_get_shape(assembly_object_t *obj);
ASAPICALL workplane_t *assembly_object_get_workplane(assembly_object_t *obj);
ASAPICALL _Bool assembly_object_is_shape(assembly_object_t *obj);
ASAPICALL _Bool assembly_object_is_workplane(assembly_object_t *obj);

ASAPICALL const char *assembly_element_get_name(assembly_element_t *el);
ASAPICALL topo_shape_t *assembly_element_get_shape(assembly_element_t *el);
ASAPICALL color_t *assembly_element_get_color(assembly_element_t *el);
ASAPICALL topo_location_t *
assembly_element_get_location(assembly_element_t *el);
ASAPICALL void assembly_element_free(assembly_element_t *el);

ASAPICALL constraint_param_t *constraint_param_create_from_double(double value);
ASAPICALL constraint_param_t *
constraint_param_create_from_double3(double x, double y, double z);
ASAPICALL constraint_param_t *constraint_param_create_from_double2(double x,
                                                                   double y);
ASAPICALL void constraint_param_free(constraint_param_t *param);

ASAPICALL assembly_t *assembly_create(assembly_object_t *obj,
                                      topo_location_t *loc, const char *name,
                                      color_t *color);
ASAPICALL void assembly_free(assembly_t *as);
ASAPICALL assembly_t *assembly_copy(assembly_t *as);
ASAPICALL void assembly_add_object(assembly_t *as, assembly_object_t *obj,
                                   topo_location_t *loc, const char *name,
                                   color_t *color);
ASAPICALL void assembly_add_assembly(assembly_t *as, assembly_t *obj,
                                     topo_location_t *loc, const char *name,
                                     color_t *color);
ASAPICALL void assembly_remove(assembly_t *as, const char *name);

ASAPICALL void assembly_constrain(assembly_t *as, const char *q1,
                                  const char *q2, int kind,
                                  constraint_param_t *param);
ASAPICALL void assembly_constrain1(assembly_t *as, const char *q1, int kind,
                                   constraint_param_t *param);
ASAPICALL void assembly_constrain2(assembly_t *as, const char *id1,
                                   topo_shape_t *s1, const char *id2,
                                   topo_shape_t *s2, int kind,
                                   constraint_param_t *param);
ASAPICALL void assembly_constrain3(assembly_t *as, const char *id1,
                                   topo_shape_t *s1, int kind,
                                   constraint_param_t *param);
ASAPICALL void assembly_solve(assembly_t *as, int verbosity);
ASAPICALL void assembly_export_to(assembly_t *as, const char *path, int mode);
ASAPICALL topo_shape_t **assembly_shapes(assembly_t *as, int *size);
ASAPICALL void topo_shape_list_free(topo_shape_t **list, int size);
ASAPICALL topo_compound_t *assembly_to_compound(assembly_t *as);
ASAPICALL assembly_element_t **assembly_get_elements(assembly_t *as, int *size);
ASAPICALL void assembly_element_list_free(assembly_element_t **list, int size);
ASAPICALL const char *assembly_get_name(assembly_t *as);
ASAPICALL topo_location_t *assembly_get_location(assembly_t *as);
ASAPICALL color_t *assembly_get_color(assembly_t *as);
ASAPICALL assembly_object_t *assembly_get_object(assembly_t *as);
ASAPICALL assembly_t **assembly_children(assembly_t *as, int *size);
ASAPICALL void assembly_list_free(assembly_t **list, int size);

#ifdef __cplusplus
}
#endif

#endif
