#ifndef GO_SELECTOR_C_API_H
#define GO_SELECTOR_C_API_H

#include "standard_c_api.h"
#include "topo_c_api.h"

#if defined(WIN32) || defined(WINDOWS) || defined(_WIN32) || defined(_WINDOWS)
#define SELCAPICALL __declspec(dllexport)
#else
#define SELCAPICALL
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _selector_t selector_t;

SELCAPICALL void selector_free(selector_t *sel);

SELCAPICALL selector_t *selector_custom_selector_create(
    void *user_data,
    topo_shape_t **(*func)(void *user_data, topo_shape_t **, int, int *));

SELCAPICALL selector_t *
selector_nearest_to_point_selector_create(topo_vector_t *p);

SELCAPICALL selector_t *
selector_box_selector_create(topo_vector_t *p0, topo_vector_t *p1, bool use_bb);

SELCAPICALL selector_t *selector_radius_nth_selector_create(int n,
                                                            bool direction_max,
                                                            double tolerance);

SELCAPICALL selector_t *selector_center_nth_selector_create(topo_vector_t *dir,
                                                            int n,
                                                            bool direction_max,
                                                            double tolerance);

SELCAPICALL selector_t *
selector_direction_minmax_selector_create(topo_vector_t *dir,
                                          bool direction_max, double tolerance);

SELCAPICALL selector_t *
selector_parallel_dir_selector_create(topo_vector_t *dir, double tol);

SELCAPICALL selector_t *selector_dir_selector_create(topo_vector_t *dir,
                                                     double tol);

SELCAPICALL selector_t *
selector_perpendicular_dir_selector_create(topo_vector_t *dir, double tol);

SELCAPICALL selector_t *
selector_direction_nth_selector_create(topo_vector_t *dir, int n,
                                       bool direction_max, double tolerance);

SELCAPICALL selector_t *selector_length_nth_selector_create(int n,
                                                            bool direction_max,
                                                            double tolerance);

SELCAPICALL selector_t *selector_type_selector_create(int type);

SELCAPICALL selector_t *
selector_area_nth_selector_create(int n, bool direction_max, double tolerance);

SELCAPICALL selector_t *selector_and_selector_create(selector_t *left,
                                                     selector_t *right);

SELCAPICALL selector_t *selector_or_selector_create(selector_t *left,
                                                    selector_t *right);

SELCAPICALL selector_t *selector_subtract_selector_create(selector_t *left,
                                                          selector_t *right);

SELCAPICALL selector_t *selector_not_selector_create(selector_t *sel);

SELCAPICALL selector_t *
selector_string_syntax_selector_create(const char *selector_str);

#ifdef __cplusplus
}
#endif

#endif
