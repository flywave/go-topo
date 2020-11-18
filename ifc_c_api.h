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

IFCCAPICALL topo_shape_t** ifc_get_topo_shapes(const char *filename,int *count);
IFCCAPICALL void ifc_shapes_free(topo_shape_t **shps);
IFCCAPICALL void ifc_register_schema();
IFCCAPICALL topo_shape_t* ifc_get_topo_shape(topo_shape_t**,int index);

#ifdef __cplusplus
}
#endif

#endif