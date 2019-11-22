#ifndef GO_PLATE_PLATE_IMPL_HH
#define GO_PLATE_PLATE_IMPL_HH

#include <Plate_D1.hxx>
#include <Plate_D2.hxx>
#include <Plate_D3.hxx>

#include <Plate_FreeGtoCConstraint.hxx>
#include <Plate_GlobalTranslationConstraint.hxx>
#include <Plate_GtoCConstraint.hxx>
#include <Plate_LineConstraint.hxx>
#include <Plate_LinearScalarConstraint.hxx>
#include <Plate_LinearXYZConstraint.hxx>
#include <Plate_PinpointConstraint.hxx>
#include <Plate_PlaneConstraint.hxx>
#include <Plate_Plate.hxx>
#include <Plate_SampledCurveConstraint.hxx>

#ifdef __cplusplus
extern "C" {
#endif

struct _plate_plate_t {
  Plate_Plate pp;
};

struct _plate_pinpoint_constraint_t {
  Plate_PinpointConstraint pc;
};

struct _plate_linear_xyz_constraint_t {
  Plate_LinearXYZConstraint pc;
};

struct _plate_linear_scalar_constraint_t {
  Plate_LinearScalarConstraint pc;
};

struct _plate_global_translation_constraint_t {
  Plate_GlobalTranslationConstraint pc;
};

struct _plate_line_constraint_t {
  Plate_LineConstraint pc;
};

struct _plate_plane_constraint_t {
  Plate_PlaneConstraint pc;
};

struct _plate_sampled_curve_constraint_t {
  Plate_SampledCurveConstraint pc;
};

struct _plate_g_to_c_constraint_t {
  Plate_GtoCConstraint pc;
};

struct _plate_free_g_to_c_constraint_t {
  Plate_FreeGtoCConstraint pc;
};

#ifdef __cplusplus
}
#endif

#endif
