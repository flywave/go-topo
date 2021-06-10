#ifndef GO_PLATE_PLATE_C_API_H
#define GO_PLATE_PLATE_C_API_H

#if defined(WIN32) || defined(WINDOWS) || defined(_WIN32) || defined(_WINDOWS)
#define PLATECAPICALL __declspec(dllexport)
#else
#define PLATECAPICALL
#endif

#include "standard_c_api.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _plate_plate_t plate_plate_t;
typedef struct _plate_pinpoint_constraint_t plate_pinpoint_constraint_t;
typedef struct _plate_linear_xyz_constraint_t plate_linear_xyz_constraint_t;
typedef struct _plate_linear_scalar_constraint_t
    plate_linear_scalar_constraint_t;
typedef struct _plate_global_translation_constraint_t
    plate_global_translation_constraint_t;
typedef struct _plate_line_constraint_t plate_line_constraint_t;
typedef struct _plate_plane_constraint_t plate_plane_constraint_t;
typedef struct _plate_sampled_curve_constraint_t
    plate_sampled_curve_constraint_t;
typedef struct _plate_g_to_c_constraint_t plate_g_to_c_constraint_t;
typedef struct _plate_free_g_to_c_constraint_t plate_free_g_to_c_constraint_t;

typedef struct _plate_d1_t {
  xyz_t du;
  xyz_t dv;
} plate_d1_t;

typedef struct _plate_d2_t {
  xyz_t duu;
  xyz_t duv;
  xyz_t dvv;
} plate_d2_t;

typedef struct _plate_d3_t {
  xyz_t duuu;
  xyz_t duuv;
  xyz_t duvv;
  xyz_t dvvv;
} plate_d3_t;

PLATECAPICALL plate_plate_t *plate_plate_new();
PLATECAPICALL void plate_plate_free(plate_plate_t *p);
PLATECAPICALL void
plate_plate_load_plate_pinpoint_constraint(plate_plate_t *pp,
                                           plate_pinpoint_constraint_t *p);
PLATECAPICALL void
plate_plate_load_plate_linear_xyz_constraint(plate_plate_t *pp,
                                             plate_linear_xyz_constraint_t *p);
PLATECAPICALL void plate_plate_load_plate_linear_scalar_constraint(
    plate_plate_t *pp, plate_linear_scalar_constraint_t *p);
PLATECAPICALL void plate_plate_load_plate_global_translation_constraint(
    plate_plate_t *pp, plate_global_translation_constraint_t *p);
PLATECAPICALL void
plate_plate_load_plate_line_constraint(plate_plate_t *pp,
                                       plate_line_constraint_t *p);
PLATECAPICALL void
plate_plate_load_plate_plane_constraint(plate_plate_t *pp,
                                        plate_plane_constraint_t *p);
PLATECAPICALL void plate_plate_load_plate_sampled_curve_constraint(
    plate_plate_t *pp, plate_sampled_curve_constraint_t *p);
PLATECAPICALL void
plate_plate_load_plate_g_to_c_constraint(plate_plate_t *pp,
                                         plate_g_to_c_constraint_t *p);
PLATECAPICALL void plate_plate_load_plate_free_g_to_c_constraint(
    plate_plate_t *pp, plate_free_g_to_c_constraint_t *p);
PLATECAPICALL void plate_plate_solveti(plate_plate_t *pp, int ord,
                                       double anisotropie);

PLATECAPICALL plate_pinpoint_constraint_t *
plate_pinpoint_constraint_new(xy_t point2d, xyz_t ImposedValue, int iu, int iv);
PLATECAPICALL void
plate_pinpoint_constraint_free(plate_pinpoint_constraint_t *p);

PLATECAPICALL plate_linear_xyz_constraint_t *
plate_linear_xyz_constraint_new_1dim(plate_pinpoint_constraint_t **ppc,
                                     int ppccount, double *coffe,
                                     int coffecount);
PLATECAPICALL plate_linear_xyz_constraint_t *
plate_linear_xyz_constraint_new_2dim(plate_pinpoint_constraint_t **ppc,
                                     int ppccount, double *coffe, int cofferow,
                                     int coffecol);
PLATECAPICALL void
plate_linear_xyz_constraint_free(plate_linear_xyz_constraint_t *p);

PLATECAPICALL plate_linear_scalar_constraint_t *
plate_linear_scalar_constraint_new(plate_pinpoint_constraint_t *ppc,
                                   xyz_t coffe);
PLATECAPICALL plate_linear_scalar_constraint_t *
plate_linear_scalar_constraint_new_1dim(plate_pinpoint_constraint_t **ppc,
                                        int ppccount, xyz_t *coffe,
                                        int coffecount);
PLATECAPICALL plate_linear_scalar_constraint_t *
plate_linear_scalar_constraint_new_2dim(plate_pinpoint_constraint_t **ppc,
                                        int ppccount, xyz_t *coffe,
                                        int cofferow, int coffecol);
PLATECAPICALL void
plate_linear_scalar_constraint_free(plate_linear_scalar_constraint_t *p);

PLATECAPICALL plate_global_translation_constraint_t *
plate_global_translation_constraint_new(xy_t *coffe, int coffecount);
PLATECAPICALL void plate_global_translation_constraint_free(
    plate_global_translation_constraint_t *p);

PLATECAPICALL plate_line_constraint_t *
plate_line_constraint_new(xy_t point2d, line_t l, int iu, int iv);
PLATECAPICALL void plate_line_constraint_free(plate_line_constraint_t *p);

PLATECAPICALL plate_plane_constraint_t *
plate_plane_constraint_new(xy_t point2d, plane_t l, int iu, int iv);
PLATECAPICALL void plate_plane_constraint_free(plate_plane_constraint_t *p);

PLATECAPICALL plate_sampled_curve_constraint_t *
plate_sampled_curve_constraint_new(plate_pinpoint_constraint_t **cons,
                                   int count);
PLATECAPICALL void
plate_sampled_curve_constraint_free(plate_sampled_curve_constraint_t *p);

PLATECAPICALL plate_g_to_c_constraint_t *
plate_g_to_c_constraint_new_1(xy_t point2d, plate_d1_t D1S, plate_d1_t D1T);
PLATECAPICALL plate_g_to_c_constraint_t *
plate_g_to_c_constraint_new_2(xy_t point2d, plate_d1_t D1S, plate_d1_t D1T,
                              xyz_t nP);
PLATECAPICALL plate_g_to_c_constraint_t *
plate_g_to_c_constraint_new_3(xy_t point2d, plate_d1_t D1S, plate_d1_t D1T,
                              plate_d2_t D2S, plate_d2_t D2T);
PLATECAPICALL plate_g_to_c_constraint_t *
plate_g_to_c_constraint_new_4(xy_t point2d, plate_d1_t D1S, plate_d1_t D1T,
                              plate_d2_t D2S, plate_d2_t D2T, xyz_t nP);
PLATECAPICALL plate_g_to_c_constraint_t *
plate_g_to_c_constraint_new_5(xy_t point2d, plate_d1_t D1S, plate_d1_t D1T,
                              plate_d2_t D2S, plate_d2_t D2T, plate_d3_t D3S,
                              plate_d3_t D3T);
PLATECAPICALL plate_g_to_c_constraint_t *
plate_g_to_c_constraint_new_6(xy_t point2d, plate_d1_t D1S, plate_d1_t D1T,
                              plate_d2_t D2S, plate_d2_t D2T, plate_d3_t D3S,
                              plate_d3_t D3T, xyz_t nP);
PLATECAPICALL void plate_g_to_c_constraint_free(plate_g_to_c_constraint_t *p);

PLATECAPICALL plate_free_g_to_c_constraint_t *
plate_free_g_to_c_constraint_new_1(xy_t point2d, plate_d1_t D1S, plate_d1_t D1T,
                                   double IncrementalLoad, int orientation);
PLATECAPICALL plate_free_g_to_c_constraint_t *
plate_free_g_to_c_constraint_new_2(xy_t point2d, plate_d1_t D1S, plate_d1_t D1T,
                                   plate_d2_t D2S, plate_d2_t D2T,
                                   double IncrementalLoad, int orientation);
PLATECAPICALL plate_free_g_to_c_constraint_t *
plate_free_g_to_c_constraint_new_3(xy_t point2d, plate_d1_t D1S, plate_d1_t D1T,
                                   plate_d2_t D2S, plate_d2_t D2T,
                                   plate_d3_t D3S, plate_d3_t D3T,
                                   double IncrementalLoad, int orientation);
PLATECAPICALL void
plate_free_g_to_c_constraint_free(plate_free_g_to_c_constraint_t *p);

#ifdef __cplusplus
}
#endif

#endif
