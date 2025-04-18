#ifndef GO_DXF_C_API_H
#define GO_DXF_C_API_H

#include "standard_c_api.h"
#include "topo_c_api.h"

#if defined(WIN32) || defined(WINDOWS) || defined(_WIN32) || defined(_WINDOWS)
#define DXFCAPICALL __declspec(dllexport)
#else
#define DXFCAPICALL
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _dxf_reader_t dxf_reader_t;
typedef struct _dxf_writer_t dxf_writer_t;
typedef struct _dxf_shape_entity_layer_t dxf_shape_entity_layer_t;
typedef struct _dxf_shape_entity_t dxf_shape_entity_t;
typedef struct _dxf_text_entity_layer_t dxf_text_entity_layer_t;
typedef struct _dxf_text_entity_t dxf_text_entity_t;

DXFCAPICALL dxf_reader_t *dxf_open_reader(const char *filename);
DXFCAPICALL void dxf_reader_free(dxf_reader_t *p);
DXFCAPICALL _Bool dxf_reader_is_failed(dxf_reader_t *p);
DXFCAPICALL void dxf_reader_do_read(dxf_reader_t *p);
DXFCAPICALL const char *dxf_reader_get_error(dxf_reader_t *p);
DXFCAPICALL _Bool dxf_reader_has_error(dxf_reader_t *p);
DXFCAPICALL const char **dxf_reader_get_layer_names(dxf_reader_t *p,
                                                    int *count);
DXFCAPICALL void dxf_layer_names_free(const char **names);

DXFCAPICALL dxf_writer_t *dxf_open_writer(const char *filename);
DXFCAPICALL void dxf_writer_free(dxf_writer_t *p);
DXFCAPICALL void dxf_writer_add_shape(dxf_writer_t *p, const char *layerName,
                                      topo_shape_t *shape, int index);
DXFCAPICALL void dxf_writer_add_text(dxf_writer_t *p, const char *layerName,
                                     const char *text, pnt3d_t position,
                                     double height, double rotation, int index);
DXFCAPICALL void dxf_writer_add_shape_layer(dxf_writer_t *p, const char *name,
                                            dxf_shape_entity_layer_t *layer);
DXFCAPICALL void dxf_writer_add_text_layer(dxf_writer_t *p, const char *name,
                                           dxf_text_entity_layer_t *layer);
DXFCAPICALL _Bool dxf_writer_write(dxf_writer_t *p);

DXFCAPICALL dxf_shape_entity_layer_t *dxf_shape_entity_layer_new();
DXFCAPICALL dxf_shape_entity_layer_t *
dxf_reader_get_shape_entity_layer(dxf_reader_t *p, const char *name);
DXFCAPICALL void dxf_shape_entity_layer_add(dxf_shape_entity_layer_t *p,
                                            dxf_shape_entity_t *entity);
DXFCAPICALL void dxf_shape_entity_layer_free(dxf_shape_entity_layer_t *p);
DXFCAPICALL int dxf_shape_entity_layer_get_count(dxf_shape_entity_layer_t *p);
DXFCAPICALL dxf_shape_entity_t *
dxf_shape_entity_layer_get_entity(dxf_shape_entity_layer_t *p, int index);
DXFCAPICALL dxf_shape_entity_t *dxf_shape_entity_new(topo_shape_t *shape,
                                                     int color);
DXFCAPICALL void dxf_shape_entity_free(dxf_shape_entity_t *p);
DXFCAPICALL color_t dxf_shape_entity_get_color(dxf_shape_entity_t *p);
DXFCAPICALL topo_shape_t *dxf_shape_entity_get_shape(dxf_shape_entity_t *p);

DXFCAPICALL dxf_text_entity_layer_t *dxf_text_entity_layer_new();
DXFCAPICALL dxf_text_entity_layer_t *
dxf_reader_get_text_entity_layer(dxf_reader_t *p, const char *name);
DXFCAPICALL void dxf_text_entity_layer_add_entity(dxf_text_entity_layer_t *p,
                                                  dxf_text_entity_t *entity);
DXFCAPICALL void dxf_text_entity_layer_free(dxf_text_entity_layer_t *p);
DXFCAPICALL int dxf_text_entity_layer_get_count(dxf_text_entity_layer_t *p);
DXFCAPICALL dxf_text_entity_t *
dxf_text_entity_layer_get_entity(dxf_text_entity_layer_t *p, int index);
DXFCAPICALL dxf_text_entity_t *dxf_text_entity_new(const char *text,
                                                   pnt3d_t position,
                                                   double height,
                                                   double rotation, int color);

DXFCAPICALL void dxf_text_entity_free(dxf_text_entity_t *p);
DXFCAPICALL const char *dxf_text_entity_get_text(dxf_text_entity_t *p);
DXFCAPICALL pnt3d_t dxf_text_entity_get_position(dxf_text_entity_t *p);
DXFCAPICALL vec3d_t dxf_text_entity_get_normal(dxf_text_entity_t *p);
DXFCAPICALL vec3d_t dxf_text_entity_get_x_axis_dir(dxf_text_entity_t *p);

#ifdef __cplusplus
}
#endif

#endif