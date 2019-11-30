#ifndef GO_GEOMETRY_C_API_H
#define GO_GEOMETRY_C_API_H
#include "standard_c_api.h"
#include <stdbool.h>

#if defined(WIN32) || defined(WINDOWS) || defined(_WIN32) || defined(_WINDOWS)
#define GEOMCAPICALL __declspec(dllexport)
#else
#define GEOMCAPICALL
#endif

#ifdef __cplusplus
extern "C" {
#endif
enum {
  GeomAxis1Placement,
  GeomAxis2Placement,
  GeomBSplineCurve,
  GeomBSplineSurface,
  GeomBezierCurve,
  GeomBezierSurface,
  GeomCartesianPoint,
  GeomCircle,
  GeomConicalSurface,
  GeomCylindricalSurface,
  GeomDirection,
  GeomElementarySurface,
  GeomEllipse,
  GeomHyperbola,
  GeomLine,
  GeomOffsetCurve,
  GeomOffsetSurface,
  GeomParabola,
  GeomPlane,
  GeomRectangularTrimmedSurface,
  GeomSphericalSurface,
  GeomSurfaceOfLinearExtrusion,
  GeomSurfaceOfRevolution,
  GeomSweptSurface,
  GeomToroidalSurface,
  GeomTrimmedCurve,
  GeomVectorWithMagnitude,
  GeomPlateSurface,
};

enum {
  Geom2dBisectorBisecAna,
  Geom2dBisectorBisecCC,
  Geom2dBisectorBisecPC,
  Geom2dAxisPlacement,
  Geom2dBSplineCurve,
  Geom2dBezierCurve,
  Geom2dBisectorCurve,
  Geom2dBoundedCurve,
  Geom2dCartesianPoint,
  Geom2dCircle,
  Geom2dConic,
  Geom2dDirection,
  Geom2dEllipse,
  Geom2dHyperbola,
  Geom2dLine,
  Geom2dOffsetCurve,
  Geom2dParabola,
  Geom2dTrimmedCurve,
  Geom2dVectorWithMagnitude,
};

typedef struct _geom_geometry_t geom_geometry_t;
typedef struct _geom_transformation_t geom_transformation_t;
typedef struct _geom_axis_placement_t geom_axis_placement_t;
typedef struct _geom_axis1_placement_t geom_axis1_placement_t;
typedef struct _geom_axis2_placement_t geom_axis2_placement_t;
typedef struct _geom_curve_t geom_curve_t;
typedef struct _geom_bounded_curve_t geom_bounded_curve_t;
typedef struct _geom_bezier_curve_t geom_bezier_curve_t;
typedef struct _geom_bspline_curve_t geom_bspline_curve_t;
typedef struct _geom_trimmed_curve_t geom_trimmed_curve_t;
typedef struct _geom_conic_t geom_conic_t;
typedef struct _geom_circle_t geom_circle_t;
typedef struct _geom_ellipse_t geom_ellipse_t;
typedef struct _geom_hyperbola_t geom_hyperbola_t;
typedef struct _geom_parabola_t geom_parabola_t;
typedef struct _geom_line_t geom_line_t;
typedef struct _geom_offset_curve_t geom_offset_curve_t;
typedef struct _geom_point_t geom_point_t;
typedef struct _geom_cartesian_point_t geom_cartesian_point_t;
typedef struct _geom_surface_t geom_surface_t;
typedef struct _geom_bounded_surface_t geom_bounded_surface_t;
typedef struct _geom_bezier_surface_t geom_bezier_surface_t;
typedef struct _geom_bspline_surface_t geom_bspline_surface_t;
typedef struct _geom_rectangular_trimmed_surface_t
    geom_rectangular_trimmed_surface_t;
typedef struct _geom_elementary_surface_t geom_elementary_surface_t;
typedef struct _geom_cylindrical_surface_t geom_cylindrical_surface_t;
typedef struct _geom_plane_surface_t geom_plane_surface_t;
typedef struct _geom_conical_surface_t geom_conical_surface_t;
typedef struct _geom_spherical_surface_t geom_spherical_surface_t;
typedef struct _geom_toroidal_surface_t geom_toroidal_surface_t;
typedef struct _geom_offset_surface_t geom_offset_surface_t;
typedef struct _geom_swept_surface_t geom_swept_surface_t;
typedef struct _geom_surface_of_linear_extrusion_t
    geom_surface_of_linear_extrusion_t;
typedef struct _geom_surface_of_revolution_extrusion_t
    geom_surface_of_revolution_extrusion_t;
typedef struct _geom_plate_surface_t geom_plate_surface_t;
typedef struct _geom_vector_t geom_vector_t;
typedef struct _geom_direction_t geom_direction_t;
typedef struct _geom_vector_with_magnitude_t geom_vector_with_magnitude_t;

typedef struct _geom2d_geometry_t geom2d_geometry_t;
typedef struct _geom2d_transformation_t geom2d_transformation_t;
typedef struct _geom2d_axis_placement_t geom2d_axis_placement_t;
typedef struct _geom2d_curve_t geom2d_curve_t;
typedef struct _geom2d_bisector_curve_t geom2d_bisector_curve_t;
typedef struct _geom2d_bezier_bisec_ana_curve_t geom2d_bezier_bisec_ana_curve_t;
typedef struct _geom2d_bezier_bisec_cc_curve_t geom2d_bezier_bisec_cc_curve_t;
typedef struct _geom2d_bezier_bisec_pc_curve_t geom2d_bezier_bisec_pc_curve_t;
typedef struct _geom2d_bounded_curve_t geom2d_bounded_curve_t;
typedef struct _geom2d_bezier_curve_t geom2d_bezier_curve_t;
typedef struct _geom2d_bspline_curve_t geom2d_bspline_curve_t;
typedef struct _geom2d_trimmed_curve_t geom2d_trimmed_curve_t;
typedef struct _geom2d_conic_t geom2d_conic_t;
typedef struct _geom2d_circle_t geom2d_circle_t;
typedef struct _geom2d_ellipse_t geom2d_ellipse_t;
typedef struct _geom2d_hyperbola_t geom2d_hyperbola_t;
typedef struct _geom2d_parabola_t geom2d_parabola_t;
typedef struct _geom2d_line_t geom2d_line_t;
typedef struct _geom2d_offset_curve_t geom2d_offset_curve_t;
typedef struct _geom2d_point_t geom2d_point_t;
typedef struct _geom2d_cartesian_point_t geom2d_cartesian_point_t;
typedef struct _geom2d_vector_t geom2d_vector_t;
typedef struct _geom2d_direction_t geom2d_direction_t;
typedef struct _geom2d_vector_with_magnitude_t geom2d_vector_with_magnitude_t;
typedef struct _plate_plate_t plate_plate_t;

GEOMCAPICALL void geom_geometry_free(geom_geometry_t *p);
GEOMCAPICALL void geom_transformation_free(geom_transformation_t *p);
GEOMCAPICALL void geom_axis_placement_free(geom_axis_placement_t *p);
GEOMCAPICALL void geom_axis1_placement_free(geom_axis1_placement_t *p);
GEOMCAPICALL void geom_axis2_placement_free(geom_axis2_placement_t *p);
GEOMCAPICALL void geom_curve_free(geom_curve_t *p);
GEOMCAPICALL void geom_bounded_curve_free(geom_bounded_curve_t *p);
GEOMCAPICALL void geom_bezier_curve_free(geom_bezier_curve_t *p);
GEOMCAPICALL void geom_bspline_curve_free(geom_bspline_curve_t *p);
GEOMCAPICALL void geom_trimmed_curve_free(geom_trimmed_curve_t *p);
GEOMCAPICALL void geom_conic_free(geom_conic_t *p);
GEOMCAPICALL void geom_circle_free(geom_circle_t *p);
GEOMCAPICALL void geom_ellipse_free(geom_ellipse_t *p);
GEOMCAPICALL void geom_hyperbola_free(geom_hyperbola_t *p);
GEOMCAPICALL void geom_parabola_free(geom_parabola_t *p);
GEOMCAPICALL void geom_line_free(geom_line_t *p);
GEOMCAPICALL void geom_offset_curve_free(geom_offset_curve_t *p);
GEOMCAPICALL void geom_point_free(geom_point_t *p);
GEOMCAPICALL void geom_cartesian_point_free(geom_cartesian_point_t *p);
GEOMCAPICALL void geom_surface_free(geom_surface_t *p);
GEOMCAPICALL void geom_bounded_surface_free(geom_bounded_surface_t *p);
GEOMCAPICALL void geom_bezier_surface_free(geom_bezier_surface_t *p);
GEOMCAPICALL void geom_bspline_surface_free(geom_bspline_surface_t *p);
GEOMCAPICALL void
geom_rectangular_trimmed_surface_free(geom_rectangular_trimmed_surface_t *p);
GEOMCAPICALL void geom_elementary_surface_free(geom_elementary_surface_t *p);
GEOMCAPICALL void geom_cylindrical_surface_free(geom_cylindrical_surface_t *p);
GEOMCAPICALL void geom_plane_surface_free(geom_plane_surface_t *p);
GEOMCAPICALL void geom_conical_surface_free(geom_conical_surface_t *p);
GEOMCAPICALL void geom_spherical_surface_free(geom_spherical_surface_t *p);
GEOMCAPICALL void geom_toroidal_surface_free(geom_toroidal_surface_t *p);
GEOMCAPICALL void geom_offset_surface_free(geom_offset_surface_t *p);
GEOMCAPICALL void geom_swept_surface_free(geom_swept_surface_t *p);
GEOMCAPICALL void
geom_surface_of_linear_extrusion_free(geom_surface_of_linear_extrusion_t *p);
GEOMCAPICALL void geom_surface_of_revolution_extrusion_free(
    geom_surface_of_revolution_extrusion_t *p);
GEOMCAPICALL void geom_plate_surface_free(geom_plate_surface_t *p);
GEOMCAPICALL void geom_vector_free(geom_vector_t *p);
GEOMCAPICALL void geom_direction_free(geom_direction_t *p);
GEOMCAPICALL void
geom_vector_with_magnitude_free(geom_vector_with_magnitude_t *p);

GEOMCAPICALL void geom2d_geometry_free(geom2d_geometry_t *p);
GEOMCAPICALL void geom2d_transformation_free(geom2d_transformation_t *p);
GEOMCAPICALL void geom2d_axis_placement_free(geom2d_axis_placement_t *p);
GEOMCAPICALL void geom2d_curve_free(geom2d_curve_t *p);
GEOMCAPICALL void geom2d_bisector_curve_free(geom2d_bisector_curve_t *p);
GEOMCAPICALL void
geom2d_bezier_bisec_ana_curve_free(geom2d_bezier_bisec_ana_curve_t *p);
GEOMCAPICALL void
geom2d_bezier_bisec_cc_curve_free(geom2d_bezier_bisec_cc_curve_t *p);
GEOMCAPICALL void
geom2d_bezier_bisec_pc_curve_free(geom2d_bezier_bisec_pc_curve_t *p);
GEOMCAPICALL void geom2d_bounded_curve_free(geom2d_bounded_curve_t *p);
GEOMCAPICALL void geom2d_bezier_curve_free(geom2d_bezier_curve_t *p);
GEOMCAPICALL void geom2d_bspline_curve_free(geom2d_bspline_curve_t *p);
GEOMCAPICALL void geom2d_trimmed_curve_free(geom2d_trimmed_curve_t *p);
GEOMCAPICALL void geom2d_conic_free(geom2d_conic_t *p);
GEOMCAPICALL void geom2d_circle_free(geom2d_circle_t *p);
GEOMCAPICALL void geom2d_ellipse_free(geom2d_ellipse_t *p);
GEOMCAPICALL void geom2d_hyperbola_free(geom2d_hyperbola_t *p);
GEOMCAPICALL void geom2d_parabola_free(geom2d_parabola_t *p);
GEOMCAPICALL void geom2d_line_free(geom2d_line_t *p);
GEOMCAPICALL void geom2d_offset_curve_free(geom2d_offset_curve_t *p);
GEOMCAPICALL void geom2d_point_free(geom2d_point_t *p);
GEOMCAPICALL void geom2d_cartesian_point_free(geom2d_cartesian_point_t *p);
GEOMCAPICALL void geom2d_vector_free(geom2d_vector_t *p);
GEOMCAPICALL void geom2d_direction_free(geom2d_direction_t *p);
GEOMCAPICALL void
geom2d_vector_with_magnitude_free(geom2d_vector_with_magnitude_t *p);

GEOMCAPICALL int geom_geometry_type(geom_geometry_t *p);
GEOMCAPICALL int geom2d_geometry_type(geom2d_geometry_t *p);

GEOMCAPICALL geom_geometry_t *geom_geometry_copy(geom_geometry_t *t);
GEOMCAPICALL geom_transformation_t *
geom_transformation_copy(geom_transformation_t *t);
GEOMCAPICALL geom_axis_placement_t *
geom_axis_placement_copy(geom_axis_placement_t *t);
GEOMCAPICALL geom_axis1_placement_t *
geom_axis1_placement_copy(geom_axis1_placement_t *t);
GEOMCAPICALL geom_axis2_placement_t *
geom_axis2_placement_copy(geom_axis2_placement_t *t);
GEOMCAPICALL geom_curve_t *geom_curve_copy(geom_curve_t *t);
GEOMCAPICALL geom_bounded_curve_t *
geom_bounded_curve_copy(geom_bounded_curve_t *t);
GEOMCAPICALL geom_bezier_curve_t *
geom_bezier_curve_copy(geom_bezier_curve_t *t);
GEOMCAPICALL geom_bspline_curve_t *
geom_bspline_curve_copy(geom_bspline_curve_t *t);
GEOMCAPICALL geom_trimmed_curve_t *
geom_trimmed_curve_copy(geom_trimmed_curve_t *t);
GEOMCAPICALL geom_conic_t *geom_conic_copy(geom_conic_t *t);
GEOMCAPICALL geom_circle_t *geom_circle_copy(geom_circle_t *t);
GEOMCAPICALL geom_ellipse_t *geom_ellipse_copy(geom_ellipse_t *t);
GEOMCAPICALL geom_hyperbola_t *geom_hyperbola_copy(geom_hyperbola_t *t);
GEOMCAPICALL geom_parabola_t *geom_parabola_copy(geom_parabola_t *t);
GEOMCAPICALL geom_line_t *geom_line_copy(geom_line_t *t);
GEOMCAPICALL geom_offset_curve_t *
geom_offset_curve_copy(geom_offset_curve_t *t);
GEOMCAPICALL geom_point_t *geom_point_copy(geom_point_t *t);
GEOMCAPICALL geom_cartesian_point_t *
geom_cartesian_point_copy(geom_cartesian_point_t *t);
GEOMCAPICALL geom_surface_t *geom_surface_copy(geom_surface_t *t);
GEOMCAPICALL geom_bounded_surface_t *
geom_bounded_surface_copy(geom_bounded_surface_t *t);
GEOMCAPICALL geom_bezier_surface_t *
geom_bezier_surface_copy(geom_bezier_surface_t *t);
GEOMCAPICALL geom_bspline_surface_t *
geom_bspline_surface_copy(geom_bspline_surface_t *t);
GEOMCAPICALL geom_rectangular_trimmed_surface_t *
geom_rectangular_trimmed_surface_copy(geom_rectangular_trimmed_surface_t *t);
GEOMCAPICALL geom_elementary_surface_t *
geom_elementary_surface_copy(geom_elementary_surface_t *t);
GEOMCAPICALL geom_cylindrical_surface_t *
geom_cylindrical_surface_copy(geom_cylindrical_surface_t *t);
GEOMCAPICALL geom_plane_surface_t *
geom_plane_surface_copy(geom_plane_surface_t *t);
GEOMCAPICALL geom_conical_surface_t *
geom_conical_surface_copy(geom_conical_surface_t *t);
GEOMCAPICALL geom_spherical_surface_t *
geom_spherical_surface_copy(geom_spherical_surface_t *t);
GEOMCAPICALL geom_toroidal_surface_t *
geom_toroidal_surface_copy(geom_toroidal_surface_t *t);
GEOMCAPICALL geom_offset_surface_t *
geom_offset_surface_copy(geom_offset_surface_t *t);
GEOMCAPICALL geom_swept_surface_t *
geom_swept_surface_copy(geom_swept_surface_t *t);
GEOMCAPICALL geom_surface_of_linear_extrusion_t *
geom_surface_of_linear_extrusion_copy(geom_surface_of_linear_extrusion_t *t);
GEOMCAPICALL geom_surface_of_revolution_extrusion_t *
geom_surface_of_revolution_extrusion_copy(
    geom_surface_of_revolution_extrusion_t *t);
GEOMCAPICALL geom_plate_surface_t *
geom_plate_surface_copy(geom_plate_surface_t *t);
GEOMCAPICALL geom_vector_t *geom_vector_copy(geom_vector_t *t);
GEOMCAPICALL geom_direction_t *geom_direction_copy(geom_direction_t *t);
GEOMCAPICALL geom_vector_with_magnitude_t *
geom_vector_with_magnitude_copy(geom_vector_with_magnitude_t *t);

GEOMCAPICALL geom2d_geometry_t *geom2d_geometry_copy(geom2d_geometry_t *t);
GEOMCAPICALL geom2d_transformation_t *
geom2d_transformation_copy(geom2d_transformation_t *t);
GEOMCAPICALL geom2d_axis_placement_t *
geom2d_axis_placement_copy(geom2d_axis_placement_t *t);
GEOMCAPICALL geom2d_curve_t *geom2d_curve_copy(geom2d_curve_t *t);
GEOMCAPICALL geom2d_bisector_curve_t *
geom2d_bisector_curve_copy(geom2d_bisector_curve_t *t);
GEOMCAPICALL geom2d_bezier_bisec_ana_curve_t *
geom2d_bezier_bisec_ana_curve_copy(geom2d_bezier_bisec_ana_curve_t *t);
GEOMCAPICALL geom2d_bezier_bisec_cc_curve_t *
geom2d_bezier_bisec_cc_curve_copy(geom2d_bezier_bisec_cc_curve_t *t);
GEOMCAPICALL geom2d_bezier_bisec_pc_curve_t *
geom2d_bezier_bisec_pc_curve_copy(geom2d_bezier_bisec_pc_curve_t *t);
GEOMCAPICALL geom2d_bounded_curve_t *
geom2d_bounded_curve_copy(geom2d_bounded_curve_t *t);
GEOMCAPICALL geom2d_bezier_curve_t *
geom2d_bezier_curve_copy(geom2d_bezier_curve_t *t);
GEOMCAPICALL geom2d_bspline_curve_t *
geom2d_bspline_curve_copy(geom2d_bspline_curve_t *t);
GEOMCAPICALL geom2d_trimmed_curve_t *
geom2d_trimmed_curve_copy(geom2d_trimmed_curve_t *t);
GEOMCAPICALL geom2d_conic_t *geom2d_conic_copy(geom2d_conic_t *t);
GEOMCAPICALL geom2d_circle_t *geom2d_circle_copy(geom2d_circle_t *t);
GEOMCAPICALL geom2d_ellipse_t *geom2d_ellipse_copy(geom2d_ellipse_t *t);
GEOMCAPICALL geom2d_hyperbola_t *geom2d_hyperbola_copy(geom2d_hyperbola_t *t);
GEOMCAPICALL geom2d_parabola_t *geom2d_parabola_copy(geom2d_parabola_t *t);
GEOMCAPICALL geom2d_line_t *geom2d_line_copy(geom2d_line_t *t);
GEOMCAPICALL geom2d_offset_curve_t *
geom2d_offset_curve_copy(geom2d_offset_curve_t *t);
GEOMCAPICALL geom2d_point_t *geom2d_point_copy(geom2d_point_t *t);
GEOMCAPICALL geom2d_cartesian_point_t *
geom2d_cartesian_point_copy(geom2d_cartesian_point_t *t);
GEOMCAPICALL geom2d_vector_t *geom2d_vector_copy(geom2d_vector_t *t);
GEOMCAPICALL geom2d_direction_t *geom2d_direction_copy(geom2d_direction_t *t);
GEOMCAPICALL geom2d_vector_with_magnitude_t *
geom2d_vector_with_magnitude_copy(geom2d_vector_with_magnitude_t *t);

GEOMCAPICALL geom_geometry_t *
geom_axis_placement_to_geometry(geom_axis_placement_t *t);
GEOMCAPICALL geom_geometry_t *
geom_axis1_placement_to_geometry(geom_axis1_placement_t *t);
GEOMCAPICALL geom_geometry_t *
geom_axis2_placement_to_geometry(geom_axis2_placement_t *t);
GEOMCAPICALL geom_geometry_t *geom_curve_to_geometry(geom_curve_t *t);
GEOMCAPICALL geom_geometry_t *
geom_bounded_curve_to_geometry(geom_bounded_curve_t *t);
GEOMCAPICALL geom_geometry_t *
geom_bezier_curve_to_geometry(geom_bezier_curve_t *t);
GEOMCAPICALL geom_geometry_t *
geom_bspline_curve_to_geometry(geom_bspline_curve_t *t);
GEOMCAPICALL geom_geometry_t *
geom_trimmed_curve_to_geometry(geom_trimmed_curve_t *t);
GEOMCAPICALL geom_geometry_t *geom_conic_to_geometry(geom_conic_t *t);
GEOMCAPICALL geom_geometry_t *geom_circle_to_geometry(geom_circle_t *t);
GEOMCAPICALL geom_geometry_t *geom_ellipse_to_geometry(geom_ellipse_t *t);
GEOMCAPICALL geom_geometry_t *geom_hyperbola_to_geometry(geom_hyperbola_t *t);
GEOMCAPICALL geom_geometry_t *geom_parabola_to_geometry(geom_parabola_t *t);
GEOMCAPICALL geom_geometry_t *geom_line_to_geometry(geom_line_t *t);
GEOMCAPICALL geom_geometry_t *
geom_offset_curve_to_geometry(geom_offset_curve_t *t);
GEOMCAPICALL geom_geometry_t *geom_point_to_geometry(geom_point_t *t);
GEOMCAPICALL geom_geometry_t *
geom_cartesian_point_to_geometry(geom_cartesian_point_t *t);
GEOMCAPICALL geom_geometry_t *geom_surface_to_geometry(geom_surface_t *t);
GEOMCAPICALL geom_geometry_t *
geom_bounded_surface_to_geometry(geom_bounded_surface_t *t);
GEOMCAPICALL geom_geometry_t *
geom_bezier_surface_to_geometry(geom_bezier_surface_t *t);
GEOMCAPICALL geom_geometry_t *
geom_bspline_surface_to_geometry(geom_bspline_surface_t *t);
GEOMCAPICALL geom_geometry_t *geom_rectangular_trimmed_surface_to_geometry(
    geom_rectangular_trimmed_surface_t *t);
GEOMCAPICALL geom_geometry_t *
geom_elementary_surface_to_geometry(geom_elementary_surface_t *t);
GEOMCAPICALL geom_geometry_t *
geom_cylindrical_surface_to_geometry(geom_cylindrical_surface_t *t);
GEOMCAPICALL geom_geometry_t *
geom_plane_surface_to_geometry(geom_plane_surface_t *t);
GEOMCAPICALL geom_geometry_t *
geom_conical_surface_to_geometry(geom_conical_surface_t *t);
GEOMCAPICALL geom_geometry_t *
geom_spherical_surface_to_geometry(geom_spherical_surface_t *t);
GEOMCAPICALL geom_geometry_t *
geom_toroidal_surface_to_geometry(geom_toroidal_surface_t *t);
GEOMCAPICALL geom_geometry_t *
geom_offset_surface_to_geometry(geom_offset_surface_t *t);
GEOMCAPICALL geom_geometry_t *
geom_swept_surface_to_geometry(geom_swept_surface_t *t);
GEOMCAPICALL geom_geometry_t *geom_surface_of_linear_extrusion_to_geometry(
    geom_surface_of_linear_extrusion_t *t);
GEOMCAPICALL geom_geometry_t *geom_surface_of_revolution_extrusion_to_geometry(
    geom_surface_of_revolution_extrusion_t *t);
GEOMCAPICALL geom_geometry_t *
geom_plate_surface_to_geometry(geom_plate_surface_t *t);
GEOMCAPICALL geom_geometry_t *geom_vector_to_geometry(geom_vector_t *t);
GEOMCAPICALL geom_geometry_t *geom_direction_to_geometry(geom_direction_t *t);
GEOMCAPICALL geom_geometry_t *
geom_vector_with_magnitude_to_geometry(geom_vector_with_magnitude_t *t);

GEOMCAPICALL geom2d_geometry_t *
geom2d_axis_placement_to_geometry(geom2d_axis_placement_t *t);
GEOMCAPICALL geom2d_geometry_t *geom2d_curve_to_geometry(geom2d_curve_t *t);
GEOMCAPICALL geom2d_geometry_t *
geom2d_bisector_curve_to_geometry(geom2d_bisector_curve_t *t);
GEOMCAPICALL geom2d_geometry_t *
geom2d_bezier_bisec_ana_curve_to_geometry(geom2d_bezier_bisec_ana_curve_t *t);
GEOMCAPICALL geom2d_geometry_t *
geom2d_bezier_bisec_cc_curve_to_geometry(geom2d_bezier_bisec_cc_curve_t *t);
GEOMCAPICALL geom2d_geometry_t *
geom2d_bezier_bisec_pc_curve_to_geometry(geom2d_bezier_bisec_pc_curve_t *t);
GEOMCAPICALL geom2d_geometry_t *
geom2d_bounded_curve_to_geometry(geom2d_bounded_curve_t *t);
GEOMCAPICALL geom2d_geometry_t *
geom2d_bezier_curve_to_geometry(geom2d_bezier_curve_t *t);
GEOMCAPICALL geom2d_geometry_t *
geom2d_bspline_curve_to_geometry(geom2d_bspline_curve_t *t);
GEOMCAPICALL geom2d_geometry_t *
geom2d_trimmed_curve_to_geometry(geom2d_trimmed_curve_t *t);
GEOMCAPICALL geom2d_geometry_t *geom2d_conic_to_geometry(geom2d_conic_t *t);
GEOMCAPICALL geom2d_geometry_t *geom2d_circle_to_geometry(geom2d_circle_t *t);
GEOMCAPICALL geom2d_geometry_t *geom2d_ellipse_to_geometry(geom2d_ellipse_t *t);
GEOMCAPICALL geom2d_geometry_t *
geom2d_hyperbola_to_geometry(geom2d_hyperbola_t *t);
GEOMCAPICALL geom2d_geometry_t *
geom2d_parabola_to_geometry(geom2d_parabola_t *t);
GEOMCAPICALL geom2d_geometry_t *geom2d_line_to_geometry(geom2d_line_t *t);
GEOMCAPICALL geom2d_geometry_t *
geom2d_offset_curve_to_geometry(geom2d_offset_curve_t *t);
GEOMCAPICALL geom2d_geometry_t *geom2d_point_to_geometry(geom2d_point_t *t);
GEOMCAPICALL geom2d_geometry_t *
geom2d_cartesian_point_to_geometry(geom2d_cartesian_point_t *t);
GEOMCAPICALL geom2d_geometry_t *geom2d_vector_to_geometry(geom2d_vector_t *t);
GEOMCAPICALL geom2d_geometry_t *
geom2d_direction_to_geometry(geom2d_direction_t *t);
GEOMCAPICALL geom2d_geometry_t *
geom2d_vector_with_magnitude_to_geometry(geom2d_vector_with_magnitude_t *t);

GEOMCAPICALL geom_axis_placement_t *
geom_axis_placement_from_geometry(geom_geometry_t *t);
GEOMCAPICALL geom_axis1_placement_t *
geom_axis1_placement_from_geometry(geom_geometry_t *t);
GEOMCAPICALL geom_axis2_placement_t *
geom_axis2_placement_from_geometry(geom_geometry_t *t);
GEOMCAPICALL geom_curve_t *geom_curve_from_geometry(geom_geometry_t *t);
GEOMCAPICALL geom_bounded_curve_t *
geom_bounded_curve_from_geometry(geom_geometry_t *t);
GEOMCAPICALL geom_bezier_curve_t *
geom_bezier_curve_from_geometry(geom_geometry_t *t);
GEOMCAPICALL geom_bspline_curve_t *
geom_bspline_curve_from_geometry(geom_geometry_t *t);
GEOMCAPICALL geom_bspline_curve_t *geom_bspline_curve_from_points(pnt3d_t *t,
                                                                  int size);
GEOMCAPICALL geom_trimmed_curve_t *
geom_trimmed_curve_from_geometry(geom_geometry_t *t);
GEOMCAPICALL geom_conic_t *geom_conic_from_geometry(geom_geometry_t *t);
GEOMCAPICALL geom_circle_t *geom_circle_from_geometry(geom_geometry_t *t);
GEOMCAPICALL geom_ellipse_t *geom_ellipse_from_geometry(geom_geometry_t *t);
GEOMCAPICALL geom_hyperbola_t *geom_hyperbola_from_geometry(geom_geometry_t *t);
GEOMCAPICALL geom_parabola_t *geom_parabola_from_geometry(geom_geometry_t *t);
GEOMCAPICALL geom_line_t *geom_line_from_geometry(geom_geometry_t *t);
GEOMCAPICALL geom_offset_curve_t *
geom_offset_curve_from_geometry(geom_geometry_t *t);
GEOMCAPICALL geom_point_t *geom_point_from_geometry(geom_geometry_t *t);
GEOMCAPICALL geom_cartesian_point_t *
geom_cartesian_point_from_geometry(geom_geometry_t *t);
GEOMCAPICALL geom_surface_t *geom_surface_from_geometry(geom_geometry_t *t);
GEOMCAPICALL geom_bounded_surface_t *
geom_bounded_surface_from_geometry(geom_geometry_t *t);
GEOMCAPICALL geom_bezier_surface_t *
geom_bezier_surface_from_geometry(geom_geometry_t *t);
GEOMCAPICALL geom_bspline_surface_t *
geom_bspline_surface_from_geometry(geom_geometry_t *t);
GEOMCAPICALL geom_rectangular_trimmed_surface_t *
geom_rectangular_trimmed_surface_from_geometry(geom_geometry_t *t);
GEOMCAPICALL geom_elementary_surface_t *
geom_elementary_surface_from_geometry(geom_geometry_t *t);
GEOMCAPICALL geom_cylindrical_surface_t *
geom_cylindrical_surface_from_geometry(geom_geometry_t *t);
GEOMCAPICALL geom_plane_surface_t *
geom_plane_surface_from_geometry(geom_geometry_t *t);
GEOMCAPICALL geom_conical_surface_t *
geom_conical_surface_from_geometry(geom_geometry_t *t);
GEOMCAPICALL geom_spherical_surface_t *
geom_spherical_surface_from_geometry(geom_geometry_t *t);
GEOMCAPICALL geom_toroidal_surface_t *
geom_toroidal_surface_from_geometry(geom_geometry_t *t);
GEOMCAPICALL geom_offset_surface_t *
geom_offset_surface_from_geometry(geom_geometry_t *t);
GEOMCAPICALL geom_swept_surface_t *
geom_swept_surface_from_geometry(geom_geometry_t *t);
GEOMCAPICALL geom_surface_of_linear_extrusion_t *
geom_surface_of_linear_extrusion_from_geometry(geom_geometry_t *t);
GEOMCAPICALL geom_surface_of_revolution_extrusion_t *
geom_surface_of_revolution_extrusion_from_geometry(geom_geometry_t *t);
GEOMCAPICALL geom_plate_surface_t *
geom_plate_surface_from_geometry(geom_geometry_t *t);
GEOMCAPICALL geom_vector_t *geom_vector_from_geometry(geom_geometry_t *t);
GEOMCAPICALL geom_direction_t *geom_direction_from_geometry(geom_geometry_t *t);
GEOMCAPICALL geom_vector_with_magnitude_t *
geom_vector_with_magnitude_from_geometry(geom_geometry_t *t);

GEOMCAPICALL geom2d_axis_placement_t *
geom2d_axis_placement_from_geometry(geom2d_geometry_t *t);
GEOMCAPICALL geom2d_curve_t *geom2d_curve_from_geometry(geom2d_geometry_t *t);
GEOMCAPICALL geom2d_bisector_curve_t *
geom2d_bisector_curve_from_geometry(geom2d_geometry_t *t);
GEOMCAPICALL geom2d_bezier_bisec_ana_curve_t *
geom2d_bezier_bisec_ana_curve_from_geometry(geom2d_geometry_t *t);
GEOMCAPICALL geom2d_bezier_bisec_cc_curve_t *
geom2d_bezier_bisec_cc_curve_from_geometry(geom2d_geometry_t *t);
GEOMCAPICALL geom2d_bezier_bisec_pc_curve_t *
geom2d_bezier_bisec_pc_curve_from_geometry(geom2d_geometry_t *t);
GEOMCAPICALL geom2d_bounded_curve_t *
geom2d_bounded_curve_from_geometry(geom2d_geometry_t *t);
GEOMCAPICALL geom2d_bezier_curve_t *
geom2d_bezier_curve_from_geometry(geom2d_geometry_t *t);
GEOMCAPICALL geom2d_bspline_curve_t *
geom2d_bspline_curve_from_geometry(geom2d_geometry_t *t);
GEOMCAPICALL geom2d_trimmed_curve_t *
geom2d_trimmed_curve_from_geometry(geom2d_geometry_t *t);
GEOMCAPICALL geom2d_conic_t *geom2d_conic_from_geometry(geom2d_geometry_t *t);
GEOMCAPICALL geom2d_circle_t *geom2d_circle_from_geometry(geom2d_geometry_t *t);
GEOMCAPICALL geom2d_ellipse_t *
geom2d_ellipse_from_geometry(geom2d_geometry_t *t);
GEOMCAPICALL geom2d_hyperbola_t *
geom2d_hyperbola_from_geometry(geom2d_geometry_t *t);
GEOMCAPICALL geom2d_parabola_t *
geom2d_parabola_from_geometry(geom2d_geometry_t *t);
GEOMCAPICALL geom2d_line_t *geom2d_line_from_geometry(geom2d_geometry_t *t);
GEOMCAPICALL geom2d_offset_curve_t *
geom2d_offset_curve_from_geometry(geom2d_geometry_t *t);
GEOMCAPICALL geom2d_point_t *geom2d_point_from_geometry(geom2d_geometry_t *t);
GEOMCAPICALL geom2d_cartesian_point_t *
geom2d_cartesian_point_from_geometry(geom2d_geometry_t *t);
GEOMCAPICALL geom2d_vector_t *geom2d_vector_from_geometry(geom2d_geometry_t *t);
GEOMCAPICALL geom2d_direction_t *
geom2d_direction_from_geometry(geom2d_geometry_t *t);
GEOMCAPICALL geom2d_vector_with_magnitude_t *
geom2d_vector_with_magnitude_from_geometry(geom2d_geometry_t *t);

GEOMCAPICALL geom_curve_t *
geom_bounded_curve_to_geom_curve(geom_bounded_curve_t *t);
GEOMCAPICALL geom_curve_t *
geom_bezier_curve_to_geom_curve(geom_bezier_curve_t *t);
GEOMCAPICALL geom_curve_t *
geom_bspline_curve_to_geom_curve(geom_bspline_curve_t *t);
GEOMCAPICALL geom_curve_t *
geom_trimmed_curve_to_geom_curve(geom_trimmed_curve_t *t);
GEOMCAPICALL geom_curve_t *geom_conic_to_geom_curve(geom_conic_t *t);
GEOMCAPICALL geom_curve_t *geom_circle_to_geom_curve(geom_circle_t *t);
GEOMCAPICALL geom_curve_t *geom_ellipse_to_geom_curve(geom_ellipse_t *t);
GEOMCAPICALL geom_curve_t *geom_hyperbola_to_geom_curve(geom_hyperbola_t *t);
GEOMCAPICALL geom_curve_t *geom_parabola_to_geom_curve(geom_parabola_t *t);
GEOMCAPICALL geom_curve_t *geom_line_to_geom_curve(geom_line_t *t);
GEOMCAPICALL geom_curve_t *
geom_offset_curve_to_geom_curve(geom_offset_curve_t *t);

GEOMCAPICALL geom_surface_t *
geom_bounded_surface_to_geom_surface(geom_bounded_surface_t *t);
GEOMCAPICALL geom_surface_t *
geom_bezier_surface_to_geom_surface(geom_bezier_surface_t *t);
GEOMCAPICALL geom_surface_t *
geom_bspline_surface_to_geom_surface(geom_bspline_surface_t *t);
GEOMCAPICALL geom_surface_t *geom_rectangular_trimmed_surface_to_geom_surface(
    geom_rectangular_trimmed_surface_t *t);
GEOMCAPICALL geom_surface_t *
geom_elementary_surface_to_geom_surface(geom_elementary_surface_t *t);
GEOMCAPICALL geom_surface_t *
geom_cylindrical_surface_to_geom_surface(geom_cylindrical_surface_t *t);
GEOMCAPICALL geom_surface_t *
geom_plane_surface_to_geom_surface(geom_plane_surface_t *t);
GEOMCAPICALL geom_surface_t *
geom_conical_surface_to_geom_surface(geom_conical_surface_t *t);
GEOMCAPICALL geom_surface_t *
geom_spherical_surface_to_geom_surface(geom_spherical_surface_t *t);
GEOMCAPICALL geom_surface_t *
geom_toroidal_surface_to_geom_surface(geom_toroidal_surface_t *t);
GEOMCAPICALL geom_surface_t *
geom_offset_surface_to_geom_surface(geom_offset_surface_t *t);
GEOMCAPICALL geom_surface_t *
geom_swept_surface_to_geom_surface(geom_swept_surface_t *t);
GEOMCAPICALL geom_surface_t *geom_surface_of_linear_extrusion_to_geom_surface(
    geom_surface_of_linear_extrusion_t *t);
GEOMCAPICALL geom_surface_t *
geom_surface_of_revolution_extrusion_to_geom_surface(
    geom_surface_of_revolution_extrusion_t *t);
GEOMCAPICALL geom_surface_t *
geom_plate_surface_to_geom_surface(geom_plate_surface_t *t);

GEOMCAPICALL geom2d_curve_t *
geom2d_bisector_curve_to_geom2d_curve(geom2d_bisector_curve_t *t);
GEOMCAPICALL geom2d_curve_t *geom2d_bezier_bisec_ana_curve_to_geom2d_curve(
    geom2d_bezier_bisec_ana_curve_t *t);
GEOMCAPICALL geom2d_curve_t *
geom2d_bezier_bisec_cc_curve_to_geom2d_curve(geom2d_bezier_bisec_cc_curve_t *t);
GEOMCAPICALL geom2d_curve_t *
geom2d_bezier_bisec_pc_curve_to_geom2d_curve(geom2d_bezier_bisec_pc_curve_t *t);
GEOMCAPICALL geom2d_curve_t *
geom2d_bounded_curve_to_geom2d_curve(geom2d_bounded_curve_t *t);
GEOMCAPICALL geom2d_curve_t *
geom2d_bezier_curve_to_geom2d_curve(geom2d_bezier_curve_t *t);
GEOMCAPICALL geom2d_curve_t *
geom2d_bspline_curve_to_geom2d_curve(geom2d_bspline_curve_t *t);
GEOMCAPICALL geom2d_curve_t *
geom2d_trimmed_curve_to_geom2d_curve(geom2d_trimmed_curve_t *t);
GEOMCAPICALL geom2d_curve_t *geom2d_conic_to_geom2d_curve(geom2d_conic_t *t);
GEOMCAPICALL geom2d_curve_t *geom2d_circle_to_geom2d_curve(geom2d_circle_t *t);
GEOMCAPICALL geom2d_curve_t *
geom2d_ellipse_to_geom2d_curve(geom2d_ellipse_t *t);
GEOMCAPICALL geom2d_curve_t *
geom2d_hyperbola_to_geom2d_curve(geom2d_hyperbola_t *t);
GEOMCAPICALL geom2d_curve_t *
geom2d_parabola_to_geom2d_curve(geom2d_parabola_t *t);
GEOMCAPICALL geom2d_curve_t *geom2d_line_to_geom2d_curve(geom2d_line_t *t);
GEOMCAPICALL geom2d_curve_t *
geom2d_offset_curve_to_geom2d_curve(geom2d_offset_curve_t *t);

GEOMCAPICALL void geom_apply_mirror_with_point(geom_geometry_t *t, pnt3d_t P);
GEOMCAPICALL void geom_apply_mirror_with_axis1(geom_geometry_t *t, axis1_t A1);
GEOMCAPICALL void geom_apply_mirror_with_axis2(geom_geometry_t *t, axis2_t A2);
GEOMCAPICALL void geom_apply_rotate(geom_geometry_t *t, axis1_t A1, double Ang);
GEOMCAPICALL void geom_apply_scale(geom_geometry_t *t, pnt3d_t P, double S);
GEOMCAPICALL void geom_apply_translate_with_vector(geom_geometry_t *t,
                                                   vec3d_t V);
GEOMCAPICALL void geom_apply_translate_with_point(geom_geometry_t *t,
                                                  pnt3d_t P1, pnt3d_t P2);
GEOMCAPICALL void geom_apply_transform(geom_geometry_t *t, trsf_t tr);

GEOMCAPICALL geom_geometry_t *geom_mirror_with_point(geom_geometry_t *t,
                                                     pnt3d_t P);
GEOMCAPICALL geom_geometry_t *geom_mirror_with_axis1(geom_geometry_t *t,
                                                     axis1_t A1);
GEOMCAPICALL geom_geometry_t *geom_mirror_with_axis2(geom_geometry_t *t,
                                                     axis2_t A2);
GEOMCAPICALL geom_geometry_t *geom_rotate(geom_geometry_t *t, axis1_t A1,
                                          double Ang);
GEOMCAPICALL geom_geometry_t *geom_scale(geom_geometry_t *t, pnt3d_t P,
                                         double S);
GEOMCAPICALL geom_geometry_t *geom_translate_with_vector(geom_geometry_t *t,
                                                         vec3d_t V);
GEOMCAPICALL geom_geometry_t *geom_translate_with_point(geom_geometry_t *t,
                                                        pnt3d_t P1, pnt3d_t P2);
GEOMCAPICALL geom_geometry_t *geom_transform(geom_geometry_t *t, trsf_t tr);

GEOMCAPICALL void geom2d_apply_mirror_with_point(geom2d_geometry_t *t,
                                                 pnt2d_t P);
GEOMCAPICALL void geom2d_apply_mirror_with_axis2(geom2d_geometry_t *t,
                                                 axis2d_t A2);
GEOMCAPICALL void geom2d_apply_rotate(geom2d_geometry_t *t, pnt2d_t P,
                                      double Ang);
GEOMCAPICALL void geom2d_apply_scale(geom2d_geometry_t *t, pnt2d_t P, double S);
GEOMCAPICALL void geom2d_apply_translate_with_vector(geom2d_geometry_t *t,
                                                     vec2d_t V);
GEOMCAPICALL void geom2d_apply_translate_with_point(geom2d_geometry_t *t,
                                                    pnt2d_t P1, pnt2d_t P2);
GEOMCAPICALL void geom2d_apply_transform(geom2d_geometry_t *t, trsf2d_t tr);

GEOMCAPICALL geom2d_geometry_t *geom2d_mirror_with_point(geom2d_geometry_t *t,
                                                         pnt2d_t P);
GEOMCAPICALL geom2d_geometry_t *geom2d_mirror_with_axis2(geom2d_geometry_t *t,
                                                         axis2d_t A2);
GEOMCAPICALL geom2d_geometry_t *geom2d_rotate(geom2d_geometry_t *t, pnt2d_t P,
                                              double Ang);
GEOMCAPICALL geom2d_geometry_t *geom2d_scale(geom2d_geometry_t *t, pnt2d_t P,
                                             double S);
GEOMCAPICALL geom2d_geometry_t *
geom2d_translate_with_vector(geom2d_geometry_t *t, vec2d_t V);
GEOMCAPICALL geom2d_geometry_t *
geom2d_translate_with_point(geom2d_geometry_t *t, pnt2d_t P1, pnt2d_t P2);
GEOMCAPICALL geom2d_geometry_t *geom2d_transform(geom2d_geometry_t *t,
                                                 trsf2d_t tr);

GEOMCAPICALL _Bool geom_curve_point(geom_curve_t *curve, double s,
                                    double *point);
GEOMCAPICALL _Bool geom_surface_point(geom_surface_t *curve, double s,
                                      double *point);

GEOMCAPICALL geom_axis1_placement_t *geom_make_axis1_placement(axis1_t Axis);
GEOMCAPICALL geom_axis1_placement_t *
geom_make_axis1_placement_of_point_dir(pnt3d_t p, dir3d_t d);
GEOMCAPICALL geom_axis2_placement_t *geom_make_axis2_placement(axis2_t Axis);
GEOMCAPICALL geom_axis2_placement_t *
geom_make_axis2_placement_of_point_nvx(pnt3d_t p, dir3d_t N, dir3d_t VX);
GEOMCAPICALL geom_bezier_curve_t *geom_make_bezier_curve(pnt3d_t *CurvePoles,
                                                         int count);
GEOMCAPICALL geom_bezier_curve_t *
geom_make_bezier_curve_from_weight(pnt3d_t *CurvePoles, double *PoleWeights,
                                   int count);
GEOMCAPICALL geom_bspline_curve_t *
geom_make_bspline_curve(pnt3d_t *Poles, double *Knots, int *Multiplicities,
                        int count, int Degree, _Bool Periodic);
GEOMCAPICALL geom_bspline_curve_t *geom_make_bspline_curve_from_weight(
    pnt3d_t *Poles, double *Weights, double *Knots, int *Multiplicities,
    int count, int Degree, _Bool Periodic, _Bool CheckRational);

GEOMCAPICALL geom_bezier_surface_t *
geom_make_bezier_surface(pnt3d_t *SurfacePoles, int row, int col);

GEOMCAPICALL geom_bezier_surface_t *
geom_make_bezier_surface_from_weight(pnt3d_t *SurfacePoles, double *PoleWeights,
                                     int row, int col);

GEOMCAPICALL geom_plate_surface_t *
geom_make_plate_surface(geom_surface_t *Surfinit, plate_plate_t *Surfinter);

GEOMCAPICALL geom_bspline_surface_t *
geom_make_bspline_surface(pnt3d_t *Poles, double *UKnots, double *VKnots,
                          int *UMults, int *VMults, int row, int col,
                          int UCount, int VCount, int UDegree, int VDegree,
                          _Bool UPeriodic, _Bool VPeriodic);

GEOMCAPICALL geom_bspline_surface_t *geom_make_bspline_surface_from_weight(
    pnt3d_t *Poles, double *Weights, double *UKnots, double *VKnots,
    int *UMults, int *VMults, int row, int col, int UCount, int VCount,
    int UDegree, int VDegree, _Bool UPeriodic, _Bool VPeriodic);

GEOMCAPICALL geom_rectangular_trimmed_surface_t *
geom_make_rectangular_trimmed_surface_from_lrud(geom_surface_t *S, double U1,
                                                double U2, double V1, double V2,
                                                _Bool USense, _Bool VSense);

GEOMCAPICALL geom_rectangular_trimmed_surface_t *
geom_make_rectangular_trimmed_surface(geom_surface_t *S, double Param1,
                                      double Param2, _Bool UTrim, _Bool Sense);

GEOMCAPICALL geom_surface_of_linear_extrusion_t *
geom_make_surface_of_linear_extrusion(geom_curve_t *C, dir3d_t V);
GEOMCAPICALL geom_surface_of_revolution_extrusion_t *
geom_make_surface_of_revolution_extrusion(geom_curve_t *C, axis1_t V);

GEOMCAPICALL geom_direction_t *geom_make_direction(double X, double Y,
                                                   double Z);

GEOMCAPICALL geom_direction_t *geom_make_direction_with_dir(dir3d_t V);
GEOMCAPICALL geom_vector_with_magnitude_t *
geom_make_vector_with_magnitude_with_vector(vec3d_t V);
GEOMCAPICALL geom_vector_with_magnitude_t *
geom_make_vector_with_magnitude_with_xyz(double X, double Y, double Z);
GEOMCAPICALL geom_vector_with_magnitude_t *
geom_make_vector_with_magnitude_with_point(pnt3d_t P1, pnt3d_t P2);

GEOMCAPICALL geom_trimmed_curve_t *
geom_make_arc_of_circle_two_angles(circ_t Circ, double Alpha1, double Alpha2,
                                   _Bool Sense);

GEOMCAPICALL geom_trimmed_curve_t *geom_make_arc_of_circle_angle(circ_t Circ,
                                                                 pnt3d_t P,
                                                                 double Alpha,
                                                                 _Bool Sense);

GEOMCAPICALL geom_trimmed_curve_t *
geom_make_arc_of_circle_two_point(circ_t Circ, pnt3d_t P1, pnt3d_t P2,
                                  _Bool Sense);

GEOMCAPICALL geom_trimmed_curve_t *
geom_make_arc_of_point(pnt3d_t P1, pnt3d_t P2, pnt3d_t P3);

GEOMCAPICALL geom_trimmed_curve_t *
geom_make_arc_of_two_points_vector(pnt3d_t P1, vec3d_t V, pnt3d_t P2);

GEOMCAPICALL geom_trimmed_curve_t *
geom_make_arc_of_ellipsee_two_angles(elips_t Elips, double Alpha1,
                                     double Alpha2, _Bool Sense);

GEOMCAPICALL geom_trimmed_curve_t *geom_make_arc_of_ellipse_angle(elips_t Elips,
                                                                  pnt3d_t P,
                                                                  double Alpha,
                                                                  _Bool Sense);

GEOMCAPICALL geom_trimmed_curve_t *geom_make_arc_of_ellipse_point(elips_t Elips,
                                                                  pnt3d_t P1,
                                                                  pnt3d_t P2,
                                                                  _Bool Sense);

GEOMCAPICALL geom_trimmed_curve_t *
geom_make_arc_of_hyperbola_two_angles(hyperbola_t Hypr, double Alpha1,
                                      double Alpha2, _Bool Sense);

GEOMCAPICALL geom_trimmed_curve_t *
geom_make_arc_of_hyperbola_angle(hyperbola_t Hypr, pnt3d_t P, double Alpha,
                                 _Bool Sense);

GEOMCAPICALL geom_trimmed_curve_t *
geom_make_arc_of_hyperbola_point(hyperbola_t Hypr, pnt3d_t P1, pnt3d_t P2,
                                 _Bool Sense);

GEOMCAPICALL geom_trimmed_curve_t *
geom_make_arc_of_parabola_two_angles(parabola_t Parab, double Alpha1,
                                     double Alpha2, _Bool Sense);

GEOMCAPICALL geom_trimmed_curve_t *
geom_make_arc_of_parabola_angle(parabola_t Parab, pnt3d_t P, double Alpha,
                                _Bool Sense);

GEOMCAPICALL geom_trimmed_curve_t *
geom_make_arc_of_parabola_point(parabola_t Parab, pnt3d_t P1, pnt3d_t P2,
                                _Bool Sense);

GEOMCAPICALL geom_circle_t *geom_make_circle(circ_t C);

GEOMCAPICALL geom_circle_t *geom_make_circle_of_axis2(axis2_t A2,
                                                      double Radius);

GEOMCAPICALL geom_circle_t *geom_make_circle_of_dist(circ_t Circ, double Dist);

GEOMCAPICALL geom_circle_t *geom_make_circle_of_point(circ_t Circ,
                                                      pnt3d_t Point);

GEOMCAPICALL geom_circle_t *
geom_make_circle_of_three_point(pnt3d_t P1, pnt3d_t P2, pnt3d_t P3);

GEOMCAPICALL geom_circle_t *
geom_make_circle_of_center_norm(pnt3d_t Center, dir3d_t Norm, double Radius);

GEOMCAPICALL geom_circle_t *
geom_make_circle_center_axis(pnt3d_t Center, pnt3d_t PtAxis, double Radius);

GEOMCAPICALL geom_circle_t *geom_make_circle_of_axis1(axis1_t Axis,
                                                      double Radius);

GEOMCAPICALL geom_ellipse_t *geom_make_ellipse(elips_t E);

GEOMCAPICALL geom_ellipse_t *
geom_make_ellipse_of_axis2(axis2_t A2, double MajorRadius, double MinorRadius);

GEOMCAPICALL geom_ellipse_t *
geom_make_ellipse_point_center(pnt3d_t S1, pnt3d_t S2, pnt3d_t Center);

GEOMCAPICALL geom_hyperbola_t *geom_make_hyperbola(hyperbola_t H);

GEOMCAPICALL geom_hyperbola_t *geom_make_hyperbola_of_axis2(axis2_t A2,
                                                            double MajorRadius,
                                                            double MinorRadius);

GEOMCAPICALL geom_hyperbola_t *
geom_make_hyperbola_point_center(pnt3d_t S1, pnt3d_t S2, pnt3d_t Center);

GEOMCAPICALL geom_conical_surface_t *
geom_make_conical_surface_axis2(axis2_t A2, double Ang, double Radius);

GEOMCAPICALL geom_conical_surface_t *geom_make_conical_surface(cone_t C);

GEOMCAPICALL geom_conical_surface_t *
geom_make_conical_surface_of_point(pnt3d_t P1, pnt3d_t P2, pnt3d_t P3,
                                   pnt3d_t P4);

GEOMCAPICALL geom_conical_surface_t *
geom_make_conical_surface_of_point_radius(pnt3d_t P1, pnt3d_t P2, double R1,
                                          double R2);

GEOMCAPICALL geom_cylindrical_surface_t *
geom_make_cylindrical_surface_of_axis2(axis2_t A2, double Radius);

GEOMCAPICALL geom_cylindrical_surface_t *
geom_make_cylindrical_surface(cylinder_t C);

GEOMCAPICALL geom_cylindrical_surface_t *
geom_make_cylindrical_surface_of_point(cylinder_t Cyl, pnt3d_t Point);

GEOMCAPICALL geom_cylindrical_surface_t *
geom_make_cylindrical_surface_of_dist(cylinder_t Cyl, double Dist);

GEOMCAPICALL geom_cylindrical_surface_t *
geom_make_cylindrical_surface_of_three_point(pnt3d_t P1, pnt3d_t P2,
                                             pnt3d_t P3);

GEOMCAPICALL geom_cylindrical_surface_t *
geom_make_cylindrical_surface_of_axis_radius(axis1_t Axis, double Radius);

GEOMCAPICALL geom_cylindrical_surface_t *
geom_make_cylindrical_surface_of_circ(circ_t Circ);

GEOMCAPICALL geom_line_t *geom_make_line_of_axis1(axis1_t A1);

GEOMCAPICALL geom_line_t *geom_make_line(line_t L);

GEOMCAPICALL geom_line_t *geom_make_line_of_point_dir(pnt3d_t P, dir3d_t V);

GEOMCAPICALL geom_line_t *geom_make_line_point(line_t Lin, pnt3d_t Point);

GEOMCAPICALL geom_line_t *geom_make_line_of_two_point(pnt3d_t P1, pnt3d_t P2);

GEOMCAPICALL geom_transformation_t *geom_make_mirror_of_point(pnt3d_t Point);

GEOMCAPICALL geom_transformation_t *geom_make_mirror_of_axis1(axis1_t Axis);

GEOMCAPICALL geom_transformation_t *geom_make_mirror_of_line(line_t Line);

GEOMCAPICALL geom_transformation_t *
geom_make_mirror_of_point_dir(pnt3d_t Point, dir3d_t Direc);

GEOMCAPICALL geom_transformation_t *geom_make_mirror_of_plane(plane_t Plane);

GEOMCAPICALL geom_transformation_t *geom_make_mirror_of_axis2(axis2_t Plane);

GEOMCAPICALL geom_transformation_t *geom_make_rotation_of_line(line_t Line,
                                                               double Angle);

GEOMCAPICALL geom_transformation_t *geom_make_rotation_of_axis1(axis1_t Axis,
                                                                double Angle);

GEOMCAPICALL geom_transformation_t *
geom_make_rotation_of_point_dir(pnt3d_t Point, dir3d_t Direc, double Angle);

GEOMCAPICALL geom_transformation_t *geom_make_translation_of_vect(vec3d_t Vect);

GEOMCAPICALL geom_transformation_t *
geom_make_translation_of_two_point(pnt3d_t Point1, pnt3d_t Point2);

GEOMCAPICALL geom_transformation_t *
geom_make_scale_of_point_scale(pnt3d_t Point, double Scale);

GEOMCAPICALL geom_plane_surface_t *geom_make_plane(plane_t Pl);

GEOMCAPICALL geom_plane_surface_t *geom_make_plane_of_point_dir(pnt3d_t P,
                                                                dir3d_t V);

GEOMCAPICALL geom_plane_surface_t *geom_make_plane_of_lrud(double A, double B,
                                                           double C, double D);

GEOMCAPICALL geom_plane_surface_t *geom_make_plane_of_point(plane_t Pln,
                                                            pnt3d_t Point);

GEOMCAPICALL geom_plane_surface_t *geom_make_plane_of_dist(plane_t Pln,
                                                           double Dist);

GEOMCAPICALL geom_plane_surface_t *
geom_make_plane_of_three_point(pnt3d_t P1, pnt3d_t P2, pnt3d_t P3);

GEOMCAPICALL geom_plane_surface_t *geom_make_plane_of_axis1(axis1_t Axis);

GEOMCAPICALL geom_trimmed_curve_t *geom_make_segment_of_two_point(pnt3d_t P1,
                                                                  pnt3d_t P2);

GEOMCAPICALL geom_trimmed_curve_t *
geom_make_segment_of_line_u(line_t Line, double U1, double U2);

GEOMCAPICALL geom_trimmed_curve_t *
geom_make_segment_of_line_point(line_t Line, pnt3d_t Point, double Ulast);

GEOMCAPICALL geom_trimmed_curve_t *
geom_make_segment_of_point(line_t Line, pnt3d_t P1, pnt3d_t P2);

GEOMCAPICALL geom_rectangular_trimmed_surface_t *
geom_make_trimmed_cone_of_point(pnt3d_t P1, pnt3d_t P2, pnt3d_t P3, pnt3d_t P4);

GEOMCAPICALL geom_rectangular_trimmed_surface_t *
geom_make_trimmed_cone_of_point_radius(pnt3d_t P1, pnt3d_t P2, double R1,
                                       double R2);

GEOMCAPICALL geom_rectangular_trimmed_surface_t *
geom_make_trimmed_cylinder_of_point(pnt3d_t P1, pnt3d_t P2, pnt3d_t P3);

GEOMCAPICALL geom_rectangular_trimmed_surface_t *
geom_make_trimmed_cylinder_of_circ_height(circ_t Circ, double Height);

GEOMCAPICALL geom_rectangular_trimmed_surface_t *
geom_make_trimmed_cylinder_axis_radius(axis1_t A1, double Radius,
                                       double Height);

GEOMCAPICALL geom2d_axis_placement_t *geom2d_make_axis_placement(axis2d_t A);
GEOMCAPICALL geom2d_axis_placement_t *
geom2d_make_axis_placement_from_point(pnt2d_t P, dir2d_t V);
GEOMCAPICALL geom2d_bezier_bisec_cc_curve_t *
geom2d_make_bezier_bisec_cc_curve(geom2d_curve_t *Cu1, geom2d_curve_t *Cu2,
                                  double Side1, double Side2, pnt2d_t Origin,
                                  double DistMax);

GEOMCAPICALL geom2d_bezier_bisec_pc_curve_t *
geom2d_make_bezier_bisec_pc_curve_with_dist(geom2d_curve_t *Cu, pnt2d_t P,
                                            double Side, double DistMax);
GEOMCAPICALL geom2d_bezier_bisec_pc_curve_t *
geom2d_make_bezier_bisec_pc_curve(geom2d_curve_t *Cu, pnt2d_t P, double Side,
                                  double UMin, double UMax);

GEOMCAPICALL geom2d_bezier_curve_t *
geom2d_make_bezier_curve(pnt2d_t *CurvePoles, int count);
GEOMCAPICALL geom2d_bezier_curve_t *
geom2d_make_bezier_curve_with_weight(pnt2d_t *CurvePoles, double *PoleWeights,
                                     int count);
GEOMCAPICALL geom2d_bspline_curve_t *
geom2d_make_bspline_curve(pnt2d_t *Poles, double *Knots, int *Multiplicities,
                          int Count, int Degree, _Bool Periodic);
GEOMCAPICALL geom2d_bspline_curve_t *
geom2d_make_bspline_curve_with_weight(pnt2d_t *CurvePoles, double *Weights,
                                      double *Knots, int *Multiplicities,
                                      int Count, int Degree, _Bool Periodic);
GEOMCAPICALL geom2d_trimmed_curve_t *
geom2d_make_trimmed_curve(geom2d_curve_t *C, double U1, double U2, _Bool Sense,
                          _Bool theAdjustPeriodic);
GEOMCAPICALL geom2d_offset_curve_t *
geom2d_make_offset_curve(geom2d_curve_t *C, double Offset, _Bool isNotCheckC0);
GEOMCAPICALL geom2d_cartesian_point_t *geom2d_make_cartesian_point(pnt2d_t P);
GEOMCAPICALL geom2d_cartesian_point_t *geom2d_make_cartesian_point_xy(double X,
                                                                      double Y);
GEOMCAPICALL geom2d_direction_t *geom2d_make_direction(double X, double Y);
GEOMCAPICALL geom2d_direction_t *geom2d_make_direction_with_dir(dir2d_t V);
GEOMCAPICALL geom2d_vector_with_magnitude_t *
geom2d_make_vector_with_magnitude_with_vector(vec2d_t V);
GEOMCAPICALL geom2d_vector_with_magnitude_t *
geom2d_make_vector_with_magnitude_with_xy(double X, double Y);
GEOMCAPICALL geom2d_vector_with_magnitude_t *
geom2d_make_vector_with_magnitude_with_point(pnt2d_t P1, pnt2d_t P2);

GEOMCAPICALL geom2d_trimmed_curve_t *
geom2d_make_arc_of_circle_two_angles(circ2d_t Circ, double Alpha1,
                                     double Alpha2, _Bool Sense);

GEOMCAPICALL geom2d_trimmed_curve_t *
geom2d_make_arc_of_circle_angle(circ2d_t Circ, pnt2d_t P, double Alpha,
                                _Bool Sense);

GEOMCAPICALL geom2d_trimmed_curve_t *
geom2d_make_arc_of_circle_two_point(circ2d_t Circ, pnt2d_t P1, pnt2d_t P2,
                                    _Bool Sense);

GEOMCAPICALL geom2d_trimmed_curve_t *
geom2d_make_arc_of_circle_point(pnt2d_t P1, pnt2d_t P2, pnt2d_t P3);

GEOMCAPICALL geom2d_trimmed_curve_t *
geom2d_make_arc_of_circle_vector(pnt2d_t P1, vec2d_t V, pnt2d_t P2);

GEOMCAPICALL geom2d_trimmed_curve_t *
geom2d_make_arc_of_ellipse_two_angles(elips2d_t Elips, double Alpha1,
                                      double Alpha2, _Bool Sense);

GEOMCAPICALL geom2d_trimmed_curve_t *
geom2d_make_arc_of_ellipse_angle(elips2d_t Elips, pnt2d_t P, double Alpha,
                                 _Bool Sense);

GEOMCAPICALL geom2d_trimmed_curve_t *
geom2d_make_arc_of_ellipse_point(elips2d_t Elips, pnt2d_t P1, pnt2d_t P2,
                                 _Bool Sense);

GEOMCAPICALL geom2d_trimmed_curve_t *
geom2d_make_arc_of_hyperbola_two_angles(hyperbola2d_t Hypr, double Alpha1,
                                        double Alpha2, _Bool Sense);

GEOMCAPICALL geom2d_trimmed_curve_t *
geom2d_make_arc_of_hyperbola_angle(hyperbola2d_t Hypr, pnt2d_t P, double Alpha,
                                   _Bool Sense);

GEOMCAPICALL geom2d_trimmed_curve_t *
geom2d_make_arc_of_hyperbola_point(hyperbola2d_t Hypr, pnt2d_t P1, pnt2d_t P2,
                                   _Bool Sense);

GEOMCAPICALL geom2d_trimmed_curve_t *
geom2d_make_arc_of_parabola_two_angles(parabola2d_t Parab, double Alpha1,
                                       double Alpha2, _Bool Sense);

GEOMCAPICALL geom2d_trimmed_curve_t *
geom2d_make_arc_of_parabola_angle_angle(parabola2d_t Parab, pnt2d_t P,
                                        double Alpha, _Bool Sense);

GEOMCAPICALL geom2d_trimmed_curve_t *
geom2d_make_arc_of_parabola_point(parabola2d_t Parab, pnt2d_t P1, pnt2d_t P2,
                                  _Bool Sense);

GEOMCAPICALL geom2d_circle_t *geom2d_make_circle(circ2d_t C);

GEOMCAPICALL geom2d_circle_t *
geom2d_make_circle_of_axis2d(axis2d_t A, double Radius, _Bool Sense);

GEOMCAPICALL geom2d_circle_t *geom2d_make_circle_of_axis22d(axis22d_t A,
                                                            double Radius);

GEOMCAPICALL geom2d_circle_t *geom2d_make_circle_of_circ2d_dist(circ2d_t Circ,
                                                                double Dist);

GEOMCAPICALL geom2d_circle_t *geom2d_make_circle_of_circ2d_point(circ2d_t Circ,
                                                                 pnt2d_t Point);

GEOMCAPICALL geom2d_circle_t *
geom2d_make_circle_of_three_point(pnt2d_t P1, pnt2d_t P2, pnt2d_t P3);

GEOMCAPICALL geom2d_circle_t *
geom2d_make_circle_of_point_radius(pnt2d_t P, double Radius, _Bool Sense);

GEOMCAPICALL geom2d_circle_t *
geom2d_make_circle_of_center_radius(pnt2d_t Center, pnt2d_t Point, _Bool Sense);

GEOMCAPICALL geom2d_ellipse_t *geom2d_make_ellipse(elips2d_t E);

GEOMCAPICALL geom2d_ellipse_t *
geom2d_make_ellipse_of_axis2d_radius(axis2d_t MajorAxis, double MajorRadius,
                                     double MinorRadius, _Bool Sense);

GEOMCAPICALL geom2d_ellipse_t *
geom2d_make_ellipse_of_axis22d_radius(axis22d_t Axis, double MajorRadius,
                                      double MinorRadius);

GEOMCAPICALL geom2d_ellipse_t *
geom2d_make_ellipse_of_three_point(pnt2d_t S1, pnt2d_t S2, pnt2d_t Center);

GEOMCAPICALL geom2d_hyperbola_t *geom2d_make_hyperbola(hyperbola2d_t H);

GEOMCAPICALL geom2d_hyperbola_t *
geom2d_make_hyperbola_of_axis2d_radius(axis2d_t MajorAxis, double MajorRadius,
                                       double MinorRadius, _Bool Sense);

GEOMCAPICALL geom2d_hyperbola_t *
geom2d_make_hyperbola_of_axis22d_radius(axis22d_t Axis, double MajorRadius,
                                        double MinorRadius);

GEOMCAPICALL geom2d_hyperbola_t *
geom2d_make_hyperbola_of_three_point(pnt2d_t S1, pnt2d_t S2, pnt2d_t Center);

GEOMCAPICALL geom2d_line_t *geom2d_make_line_of_axis2d(axis2d_t A);

GEOMCAPICALL geom2d_line_t *geom2d_make_line(line2d_t L);

GEOMCAPICALL geom2d_line_t *geom2d_make_line_of_point_dir(pnt2d_t P, dir2d_t V);

GEOMCAPICALL geom2d_line_t *geom2d_make_line_of_point(line2d_t Lin,
                                                      pnt2d_t Point);

GEOMCAPICALL geom2d_line_t *geom2d_make_line_of_dist(line2d_t Lin, double Dist);

GEOMCAPICALL geom2d_line_t *geom2d_make_line_of_two_point(pnt2d_t P1,
                                                          pnt2d_t P2);

GEOMCAPICALL geom2d_parabola_t *geom2d_make_parabola(parabola2d_t Prb);

GEOMCAPICALL geom2d_parabola_t *geom2d_make_parabola_of_axis22d(axis22d_t Axis,
                                                                double Focal);

GEOMCAPICALL geom2d_parabola_t *
geom2d_make_parabola_of_axis2d(axis2d_t MirrorAxis, double Focal, _Bool Sense);

GEOMCAPICALL geom2d_parabola_t *
geom2d_make_parabola_of_axis2d_point(axis2d_t D, pnt2d_t F, _Bool Sense);

GEOMCAPICALL geom2d_parabola_t *geom2d_make_parabola_point(pnt2d_t S1,
                                                           pnt2d_t O);

GEOMCAPICALL geom2d_trimmed_curve_t *geom2d_make_segment_of_point(pnt2d_t P1,
                                                                  pnt2d_t P2);

GEOMCAPICALL geom2d_trimmed_curve_t *
geom2d_make_segment_of_point_dir(pnt2d_t P1, dir2d_t V, pnt2d_t P2);

GEOMCAPICALL geom2d_trimmed_curve_t *
geom2d_make_segment_of_line(line2d_t Line, double U1, double U2);

GEOMCAPICALL geom2d_trimmed_curve_t *
geom2d_make_segment_of_line_point(line2d_t Line, pnt2d_t Point, double Ulast);

GEOMCAPICALL geom2d_trimmed_curve_t *
geom2d_make_segment_of_line_two_point(line2d_t Line, pnt2d_t P1, pnt2d_t P2);

GEOMCAPICALL geom2d_transformation_t *
geom2d_make_mirror_of_point(pnt2d_t Point);

GEOMCAPICALL geom2d_transformation_t *
geom2d_make_mirror_of_axis2d(axis2d_t Axis);

GEOMCAPICALL geom2d_transformation_t *
geom2d_make_mirror_of_line2d(line2d_t Line);

GEOMCAPICALL geom2d_transformation_t *
geom2d_make_mirror_of_point_dir(pnt2d_t Point, dir2d_t Direc);

GEOMCAPICALL geom2d_transformation_t *
geom2d_make_rotation_of_point_angle(pnt2d_t Point, double Angle);

GEOMCAPICALL geom2d_transformation_t *
geom2d_make_scale_point_scale(pnt2d_t Point, double Scale);

GEOMCAPICALL geom2d_transformation_t *
geom2d_make_translation_of_vector(vec2d_t Vect);

GEOMCAPICALL geom2d_transformation_t *
geom2d_make_translation_of_point(pnt2d_t Point1, pnt2d_t Point2);

#ifdef __cplusplus
}
#endif

#endif
