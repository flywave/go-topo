#include "geometry_c_api.h"
#include "geometry_creator.hh"
#include "geometry_impl.hh"
#include "plate_plate_impl.hh"
#include "standard_impl.hh"

#ifdef __cplusplus
extern "C" {
#endif

void geom_geometry_free(geom_geometry_t *p) {
  if (p) {
    delete p;
  }
}

void geom_transformation_free(geom_transformation_t *p) {
  if (p) {
    delete p;
  }
}

void geom_axis_placement_free(geom_axis_placement_t *p) {
  if (p) {
    delete p;
  }
}

void geom_axis1_placement_free(geom_axis1_placement_t *p) {
  if (p) {
    delete p;
  }
}

void geom_axis2_placement_free(geom_axis2_placement_t *p) {
  if (p) {
    delete p;
  }
}

void geom_curve_free(geom_curve_t *p) {
  if (p) {
    delete p;
  }
}

void geom_bounded_curve_free(geom_bounded_curve_t *p) {
  if (p) {
    delete p;
  }
}

void geom_bezier_curve_free(geom_bezier_curve_t *p) {
  if (p) {
    delete p;
  }
}

void geom_bspline_curve_free(geom_bspline_curve_t *p) {
  if (p) {
    delete p;
  }
}

void geom_trimmed_curve_free(geom_trimmed_curve_t *p) {
  if (p) {
    delete p;
  }
}

void geom_conic_free(geom_conic_t *p) {
  if (p) {
    delete p;
  }
}

void geom_circle_free(geom_circle_t *p) {
  if (p) {
    delete p;
  }
}

void geom_ellipse_free(geom_ellipse_t *p) {
  if (p) {
    delete p;
  }
}

void geom_hyperbola_free(geom_hyperbola_t *p) {
  if (p) {
    delete p;
  }
}

void geom_parabola_free(geom_parabola_t *p) {
  if (p) {
    delete p;
  }
}

void geom_line_free(geom_line_t *p) {
  if (p) {
    delete p;
  }
}

void geom_offset_curve_free(geom_offset_curve_t *p) {
  if (p) {
    delete p;
  }
}

void geom_point_free(geom_point_t *p) {
  if (p) {
    delete p;
  }
}

void geom_cartesian_point_free(geom_cartesian_point_t *p) {
  if (p) {
    delete p;
  }
}

void geom_surface_free(geom_surface_t *p) {
  if (p) {
    delete p;
  }
}

void geom_bounded_surface_free(geom_bounded_surface_t *p) {
  if (p) {
    delete p;
  }
}

void geom_bezier_surface_free(geom_bezier_surface_t *p) {
  if (p) {
    delete p;
  }
}

void geom_bspline_surface_free(geom_bspline_surface_t *p) {
  if (p) {
    delete p;
  }
}

void geom_rectangular_trimmed_surface_free(
    geom_rectangular_trimmed_surface_t *p) {
  if (p) {
    delete p;
  }
}

void geom_elementary_surface_free(geom_elementary_surface_t *p) {
  if (p) {
    delete p;
  }
}

void geom_cylindrical_surface_free(geom_cylindrical_surface_t *p) {
  if (p) {
    delete p;
  }
}

void geom_plane_surface_free(geom_plane_surface_t *p) {
  if (p) {
    delete p;
  }
}

void geom_conical_surface_free(geom_conical_surface_t *p) {
  if (p) {
    delete p;
  }
}

void geom_spherical_surface_free(geom_spherical_surface_t *p) {
  if (p) {
    delete p;
  }
}

void geom_toroidal_surface_free(geom_toroidal_surface_t *p) {
  if (p) {
    delete p;
  }
}

void geom_offset_surface_free(geom_offset_surface_t *p) {
  if (p) {
    delete p;
  }
}

void geom_swept_surface_free(geom_swept_surface_t *p) {
  if (p) {
    delete p;
  }
}

void geom_surface_of_linear_extrusion_free(
    geom_surface_of_linear_extrusion_t *p) {
  if (p) {
    delete p;
  }
}

void geom_surface_of_revolution_extrusion_free(
    geom_surface_of_revolution_extrusion_t *p) {
  if (p) {
    delete p;
  }
}

void geom_plate_surface_free(geom_plate_surface_t *p) {
  if (p) {
    delete p;
  }
}

void geom_vector_free(geom_vector_t *p) {
  if (p) {
    delete p;
  }
}

void geom_direction_free(geom_direction_t *p) {
  if (p) {
    delete p;
  }
}

void geom_vector_with_magnitude_free(geom_vector_with_magnitude_t *p) {
  if (p) {
    delete p;
  }
}

void geom2d_geometry_free(geom2d_geometry_t *p) {
  if (p) {
    delete p;
  }
}

void geom2d_transformation_free(geom2d_transformation_t *p) {
  if (p) {
    delete p;
  }
}

void geom2d_axis_placement_free(geom2d_axis_placement_t *p) {
  if (p) {
    delete p;
  }
}

void geom2d_curve_free(geom2d_curve_t *p) {
  if (p) {
    delete p;
  }
}

void geom2d_bisector_curve_free(geom2d_bisector_curve_t *p) {
  if (p) {
    delete p;
  }
}

void geom2d_bezier_bisec_ana_curve_free(geom2d_bezier_bisec_ana_curve_t *p) {
  if (p) {
    delete p;
  }
}

void geom2d_bezier_bisec_cc_curve_free(geom2d_bezier_bisec_cc_curve_t *p) {
  if (p) {
    delete p;
  }
}

void geom2d_bezier_bisec_pc_curve_free(geom2d_bezier_bisec_pc_curve_t *p) {
  if (p) {
    delete p;
  }
}

void geom2d_bounded_curve_free(geom2d_bounded_curve_t *p) {
  if (p) {
    delete p;
  }
}

void geom2d_bezier_curve_free(geom2d_bezier_curve_t *p) {
  if (p) {
    delete p;
  }
}

void geom2d_bspline_curve_free(geom2d_bspline_curve_t *p) {
  if (p) {
    delete p;
  }
}

void geom2d_trimmed_curve_free(geom2d_trimmed_curve_t *p) {
  if (p) {
    delete p;
  }
}

void geom2d_conic_free(geom2d_conic_t *p) {
  if (p) {
    delete p;
  }
}

void geom2d_circle_free(geom2d_circle_t *p) {
  if (p) {
    delete p;
  }
}

void geom2d_ellipse_free(geom2d_ellipse_t *p) {
  if (p) {
    delete p;
  }
}

void geom2d_hyperbola_free(geom2d_hyperbola_t *p) {
  if (p) {
    delete p;
  }
}

void geom2d_parabola_free(geom2d_parabola_t *p) {
  if (p) {
    delete p;
  }
}

void geom2d_line_free(geom2d_line_t *p) {
  if (p) {
    delete p;
  }
}

void geom2d_offset_curve_free(geom2d_offset_curve_t *p) {
  if (p) {
    delete p;
  }
}

void geom2d_point_free(geom2d_point_t *p) {
  if (p) {
    delete p;
  }
}

void geom2d_cartesian_point_free(geom2d_cartesian_point_t *p) {
  if (p) {
    delete p;
  }
}

void geom2d_vector_free(geom2d_vector_t *p) {
  if (p) {
    delete p;
  }
}

void geom2d_direction_free(geom2d_direction_t *p) {
  if (p) {
    delete p;
  }
}

void geom2d_vector_with_magnitude_free(geom2d_vector_with_magnitude_t *p) {
  if (p) {
    delete p;
  }
}

geom_geometry_t *geom_geometry_copy(geom_geometry_t *t) {
  return new geom_geometry_t{t->handle->Copy()};
}

geom_transformation_t *geom_transformation_copy(geom_transformation_t *t) {
  return new geom_transformation_t{t->handle->Copy()};
}

geom_axis_placement_t *geom_axis_placement_copy(geom_axis_placement_t *t) {
  return new geom_axis_placement_t{
      Handle(Geom_AxisPlacement)::DownCast(t->handle->Copy())};
}

geom_axis1_placement_t *geom_axis1_placement_copy(geom_axis1_placement_t *t) {
  return new geom_axis1_placement_t{
      Handle(Geom_Axis1Placement)::DownCast(t->handle->Copy())};
}

geom_axis2_placement_t *geom_axis2_placement_copy(geom_axis2_placement_t *t) {
  return new geom_axis2_placement_t{
      Handle(Geom_Axis2Placement)::DownCast(t->handle->Copy())};
}

geom_curve_t *geom_curve_copy(geom_curve_t *t) {
  return new geom_curve_t{.handle =Handle(Geom_Curve)::DownCast(t->handle->Copy())};
}

geom_bounded_curve_t *geom_bounded_curve_copy(geom_bounded_curve_t *t) {
  return new geom_bounded_curve_t{
      Handle(Geom_BoundedCurve)::DownCast(t->handle->Copy())};
}

geom_bezier_curve_t *geom_bezier_curve_copy(geom_bezier_curve_t *t) {
  return new geom_bezier_curve_t{
      Handle(Geom_BezierCurve)::DownCast(t->handle->Copy())};
}

geom_bspline_curve_t *geom_bspline_curve_copy(geom_bspline_curve_t *t) {
  return new geom_bspline_curve_t{
      Handle(Geom_BSplineCurve)::DownCast(t->handle->Copy())};
}

geom_trimmed_curve_t *geom_trimmed_curve_copy(geom_trimmed_curve_t *t) {
  return new geom_trimmed_curve_t{
      Handle(Geom_TrimmedCurve)::DownCast(t->handle->Copy())};
}

geom_conic_t *geom_conic_copy(geom_conic_t *t) {
  return new geom_conic_t{Handle(Geom_Conic)::DownCast(t->handle->Copy())};
}

geom_circle_t *geom_circle_copy(geom_circle_t *t) {
  return new geom_circle_t{Handle(Geom_Circle)::DownCast(t->handle->Copy())};
}

geom_ellipse_t *geom_ellipse_copy(geom_ellipse_t *t) {
  return new geom_ellipse_t{Handle(Geom_Ellipse)::DownCast(t->handle->Copy())};
}

geom_hyperbola_t *geom_hyperbola_copy(geom_hyperbola_t *t) {
  return new geom_hyperbola_t{
      Handle(Geom_Hyperbola)::DownCast(t->handle->Copy())};
}

geom_parabola_t *geom_parabola_copy(geom_parabola_t *t) {
  return new geom_parabola_t{
      Handle(Geom_Parabola)::DownCast(t->handle->Copy())};
}

geom_line_t *geom_line_copy(geom_line_t *t) {
  return new geom_line_t{Handle(Geom_Line)::DownCast(t->handle->Copy())};
}

geom_offset_curve_t *geom_offset_curve_copy(geom_offset_curve_t *t) {
  return new geom_offset_curve_t{
      Handle(Geom_OffsetCurve)::DownCast(t->handle->Copy())};
}

geom_point_t *geom_point_copy(geom_point_t *t) {
  return new geom_point_t{Handle(Geom_Point)::DownCast(t->handle->Copy())};
}

geom_cartesian_point_t *geom_cartesian_point_copy(geom_cartesian_point_t *t) {
  return new geom_cartesian_point_t{
      Handle(Geom_CartesianPoint)::DownCast(t->handle->Copy())};
}

geom_surface_t *geom_surface_copy(geom_surface_t *t) {
  return new geom_surface_t{Handle(Geom_Surface)::DownCast(t->handle->Copy())};
}

geom_bounded_surface_t *geom_bounded_surface_copy(geom_bounded_surface_t *t) {
  return new geom_bounded_surface_t{
      Handle(Geom_BoundedSurface)::DownCast(t->handle->Copy())};
}

geom_bezier_surface_t *geom_bezier_surface_copy(geom_bezier_surface_t *t) {
  return new geom_bezier_surface_t{
      Handle(Geom_BezierSurface)::DownCast(t->handle->Copy())};
}

geom_bspline_surface_t *geom_bspline_surface_copy(geom_bspline_surface_t *t) {
  return new geom_bspline_surface_t{
      Handle(Geom_BSplineSurface)::DownCast(t->handle->Copy())};
}

geom_rectangular_trimmed_surface_t *
geom_rectangular_trimmed_surface_copy(geom_rectangular_trimmed_surface_t *t) {
  return new geom_rectangular_trimmed_surface_t{
      Handle(Geom_RectangularTrimmedSurface)::DownCast(t->handle->Copy())};
}

geom_elementary_surface_t *
geom_elementary_surface_copy(geom_elementary_surface_t *t) {
  return new geom_elementary_surface_t{
      Handle(Geom_ElementarySurface)::DownCast(t->handle->Copy())};
}

geom_cylindrical_surface_t *
geom_cylindrical_surface_copy(geom_cylindrical_surface_t *t) {
  return new geom_cylindrical_surface_t{
      Handle(Geom_CylindricalSurface)::DownCast(t->handle->Copy())};
}

geom_plane_surface_t *geom_plane_surface_copy(geom_plane_surface_t *t) {
  return new geom_plane_surface_t{
      Handle(Geom_Plane)::DownCast(t->handle->Copy())};
}

geom_conical_surface_t *geom_conical_surface_copy(geom_conical_surface_t *t) {
  return new geom_conical_surface_t{
      Handle(Geom_ConicalSurface)::DownCast(t->handle->Copy())};
}

geom_spherical_surface_t *
geom_spherical_surface_copy(geom_spherical_surface_t *t) {
  return new geom_spherical_surface_t{
      Handle(Geom_SphericalSurface)::DownCast(t->handle->Copy())};
}

geom_toroidal_surface_t *
geom_toroidal_surface_copy(geom_toroidal_surface_t *t) {
  return new geom_toroidal_surface_t{
      Handle(Geom_ToroidalSurface)::DownCast(t->handle->Copy())};
}

geom_offset_surface_t *geom_offset_surface_copy(geom_offset_surface_t *t) {
  return new geom_offset_surface_t{
      Handle(Geom_OffsetSurface)::DownCast(t->handle->Copy())};
}

geom_swept_surface_t *geom_swept_surface_copy(geom_swept_surface_t *t) {
  return new geom_swept_surface_t{
      Handle(Geom_SweptSurface)::DownCast(t->handle->Copy())};
}

geom_surface_of_linear_extrusion_t *
geom_surface_of_linear_extrusion_copy(geom_surface_of_linear_extrusion_t *t) {
  return new geom_surface_of_linear_extrusion_t{
      Handle(Geom_SurfaceOfLinearExtrusion)::DownCast(t->handle->Copy())};
}

geom_surface_of_revolution_extrusion_t *
geom_surface_of_revolution_extrusion_copy(
    geom_surface_of_revolution_extrusion_t *t) {
  return new geom_surface_of_revolution_extrusion_t{
      Handle(Geom_SurfaceOfRevolution)::DownCast(t->handle->Copy())};
}

geom_plate_surface_t *geom_plate_surface_copy(geom_plate_surface_t *t) {
  return new geom_plate_surface_t{
      Handle(GeomPlate_Surface)::DownCast(t->handle->Copy())};
}

geom_vector_t *geom_vector_copy(geom_vector_t *t) {
  return new geom_vector_t{Handle(Geom_Vector)::DownCast(t->handle->Copy())};
}

geom_direction_t *geom_direction_copy(geom_direction_t *t) {
  return new geom_direction_t{
      Handle(Geom_Direction)::DownCast(t->handle->Copy())};
}

geom_vector_with_magnitude_t *
geom_vector_with_magnitude_copy(geom_vector_with_magnitude_t *t) {
  return new geom_vector_with_magnitude_t{
      Handle(Geom_VectorWithMagnitude)::DownCast(t->handle->Copy())};
}

geom2d_geometry_t *geom2d_geometry_copy(geom2d_geometry_t *t) {
  return new geom2d_geometry_t{t->handle->Copy()};
}

geom2d_transformation_t *
geom2d_transformation_copy(geom2d_transformation_t *t) {
  return new geom2d_transformation_t{
      Handle(Geom2d_Transformation)::DownCast(t->handle->Copy())};
}

geom2d_axis_placement_t *
geom2d_axis_placement_copy(geom2d_axis_placement_t *t) {
  return new geom2d_axis_placement_t{
      Handle(Geom2d_AxisPlacement)::DownCast(t->handle->Copy())};
}

geom2d_curve_t *geom2d_curve_copy(geom2d_curve_t *t) {
  return new geom2d_curve_t{Handle(Geom2d_Curve)::DownCast(t->handle->Copy())};
}

geom2d_bisector_curve_t *
geom2d_bisector_curve_copy(geom2d_bisector_curve_t *t) {
  return new geom2d_bisector_curve_t{
      Handle(Bisector_Curve)::DownCast(t->handle->Copy())};
}

geom2d_bezier_bisec_ana_curve_t *
geom2d_bezier_bisec_ana_curve_copy(geom2d_bezier_bisec_ana_curve_t *t) {
  return new geom2d_bezier_bisec_ana_curve_t{
      Handle(Bisector_BisecAna)::DownCast(t->handle->Copy())};
}

geom2d_bezier_bisec_cc_curve_t *
geom2d_bezier_bisec_cc_curve_copy(geom2d_bezier_bisec_cc_curve_t *t) {
  return new geom2d_bezier_bisec_cc_curve_t{
      Handle(Bisector_BisecCC)::DownCast(t->handle->Copy())};
}

geom2d_bezier_bisec_pc_curve_t *
geom2d_bezier_bisec_pc_curve_copy(geom2d_bezier_bisec_pc_curve_t *t) {
  return new geom2d_bezier_bisec_pc_curve_t{
      Handle(Bisector_BisecPC)::DownCast(t->handle->Copy())};
}

geom2d_bounded_curve_t *geom2d_bounded_curve_copy(geom2d_bounded_curve_t *t) {
  return new geom2d_bounded_curve_t{
      Handle(Geom2d_BoundedCurve)::DownCast(t->handle->Copy())};
}

geom2d_bezier_curve_t *geom2d_bezier_curve_copy(geom2d_bezier_curve_t *t) {
  return new geom2d_bezier_curve_t{
      Handle(Geom2d_BezierCurve)::DownCast(t->handle->Copy())};
}

geom2d_bspline_curve_t *geom2d_bspline_curve_copy(geom2d_bspline_curve_t *t) {
  return new geom2d_bspline_curve_t{
      Handle(Geom2d_BSplineCurve)::DownCast(t->handle->Copy())};
}

geom2d_trimmed_curve_t *geom2d_trimmed_curve_copy(geom2d_trimmed_curve_t *t) {
  return new geom2d_trimmed_curve_t{
      Handle(Geom2d_TrimmedCurve)::DownCast(t->handle->Copy())};
}

geom2d_conic_t *geom2d_conic_copy(geom2d_conic_t *t) {
  return new geom2d_conic_t{Handle(Geom2d_Conic)::DownCast(t->handle->Copy())};
}

geom2d_circle_t *geom2d_circle_copy(geom2d_circle_t *t) {
  return new geom2d_circle_t{
      Handle(Geom2d_Circle)::DownCast(t->handle->Copy())};
}

geom2d_ellipse_t *geom2d_ellipse_copy(geom2d_ellipse_t *t) {
  return new geom2d_ellipse_t{
      Handle(Geom2d_Ellipse)::DownCast(t->handle->Copy())};
}

geom2d_hyperbola_t *geom2d_hyperbola_copy(geom2d_hyperbola_t *t) {
  return new geom2d_hyperbola_t{
      Handle(Geom2d_Hyperbola)::DownCast(t->handle->Copy())};
}

geom2d_parabola_t *geom2d_parabola_copy(geom2d_parabola_t *t) {
  return new geom2d_parabola_t{
      Handle(Geom2d_Parabola)::DownCast(t->handle->Copy())};
}

geom2d_line_t *geom2d_line_copy(geom2d_line_t *t) {
  return new geom2d_line_t{Handle(Geom2d_Line)::DownCast(t->handle->Copy())};
}

geom2d_offset_curve_t *geom2d_offset_curve_copy(geom2d_offset_curve_t *t) {
  return new geom2d_offset_curve_t{
      Handle(Geom2d_OffsetCurve)::DownCast(t->handle->Copy())};
}

geom2d_point_t *geom2d_point_copy(geom2d_point_t *t) {
  return new geom2d_point_t{Handle(Geom2d_Point)::DownCast(t->handle->Copy())};
}

geom2d_cartesian_point_t *
geom2d_cartesian_point_copy(geom2d_cartesian_point_t *t) {
  return new geom2d_cartesian_point_t{
      Handle(Geom2d_CartesianPoint)::DownCast(t->handle->Copy())};
}

geom2d_vector_t *geom2d_vector_copy(geom2d_vector_t *t) {
  return new geom2d_vector_t{
      Handle(Geom2d_Vector)::DownCast(t->handle->Copy())};
}

geom2d_direction_t *geom2d_direction_copy(geom2d_direction_t *t) {
  return new geom2d_direction_t{
      Handle(Geom2d_Direction)::DownCast(t->handle->Copy())};
}

geom2d_vector_with_magnitude_t *
geom2d_vector_with_magnitude_copy(geom2d_vector_with_magnitude_t *t) {
  return new geom2d_vector_with_magnitude_t{
      Handle(Geom2d_VectorWithMagnitude)::DownCast(t->handle->Copy())};
}

_Bool geom_curve_point(geom_curve_t *curve, double s, double *point) {
  if (point != nullptr && curve != nullptr) {
    gp_Pnt pnt = curve->handle->Value(s);
    point[0] = pnt.X();
    point[1] = pnt.Y();
    point[2] = pnt.Z();
    return true;
  }
  return false;
}

_Bool geom_surface_point(geom_surface_t *curve, double s, double *point) {
  gp_Vec d1u, d1v;
  gp_Pnt pnt;
  Standard_Real u, v;
  if (point != nullptr && curve != nullptr) {
    curve->handle->D1(u, v, pnt, d1u, d1v);
    point[0] = pnt.X();
    point[1] = pnt.Y();
    point[2] = pnt.Z();
    return true;
  }
  return false;
}

geom_trimmed_curve_t *geom_make_arc_of_circle_two_angles(circ_t Circ,
                                                         double Alpha1,
                                                         double Alpha2,
                                                         _Bool Sense) {
  return new geom_trimmed_curve_t{
      flywave::topo::geometry_creator::make_arc_of_circle(
          cast_to_gp(Circ), Alpha1, Alpha2, Sense)};
}

geom_trimmed_curve_t *geom_make_arc_of_circle_angle(circ_t Circ, pnt3d_t P,
                                                    double Alpha, _Bool Sense) {
  return new geom_trimmed_curve_t{
      flywave::topo::geometry_creator::make_arc_of_circle(
          cast_to_gp(Circ), cast_to_gp(P), Alpha, Sense)};
}

geom_trimmed_curve_t *geom_make_arc_of_circle_two_point(circ_t Circ, pnt3d_t P1,
                                                        pnt3d_t P2,
                                                        _Bool Sense) {
  return new geom_trimmed_curve_t{
      flywave::topo::geometry_creator::make_arc_of_circle(
          cast_to_gp(Circ), cast_to_gp(P1), cast_to_gp(P2), Sense)};
}

geom_trimmed_curve_t *geom_make_arc_of_point(pnt3d_t P1, pnt3d_t P2,
                                             pnt3d_t P3) {
  return new geom_trimmed_curve_t{
     .handle=flywave::topo::geometry_creator::make_arc_of_circle(
          cast_to_gp(P1), cast_to_gp(P2), cast_to_gp(P3))};
}

geom_trimmed_curve_t *geom_make_arc_of_two_points_vector(pnt3d_t P1, vec3d_t V,
                                                         pnt3d_t P2) {
  return new geom_trimmed_curve_t{
    .handle=flywave::topo::geometry_creator::make_arc_of_circle_vector(
          cast_to_gp(P1), cast_to_gp(V), cast_to_gp(P2))};
}

geom_trimmed_curve_t *geom_make_arc_of_ellipsee_two_angles(elips_t Elips,
                                                           double Alpha1,
                                                           double Alpha2,
                                                           _Bool Sense) {
  return new geom_trimmed_curve_t{
      flywave::topo::geometry_creator::make_arc_of_ellipse(
          cast_to_gp(Elips), Alpha1, Alpha2, Sense)};
}

geom_trimmed_curve_t *geom_make_arc_of_ellipse_angle(elips_t Elips, pnt3d_t P,
                                                     double Alpha,
                                                     _Bool Sense) {
  return new geom_trimmed_curve_t{
      flywave::topo::geometry_creator::make_arc_of_ellipse(
          cast_to_gp(Elips), cast_to_gp(P), Alpha, Sense)};
}

geom_trimmed_curve_t *geom_make_arc_of_ellipse_point(elips_t Elips, pnt3d_t P1,
                                                     pnt3d_t P2, _Bool Sense) {
  return new geom_trimmed_curve_t{
      flywave::topo::geometry_creator::make_arc_of_ellipse(
          cast_to_gp(Elips), cast_to_gp(P1), cast_to_gp(P2), Sense)};
}

geom_trimmed_curve_t *geom_make_arc_of_hyperbola_two_angles(hyperbola_t Hypr,
                                                            double Alpha1,
                                                            double Alpha2,
                                                            _Bool Sense) {
  return new geom_trimmed_curve_t{
      flywave::topo::geometry_creator::make_arc_of_hyperbola(
          cast_to_gp(Hypr), Alpha1, Alpha2, Sense)};
}

geom_trimmed_curve_t *geom_make_arc_of_hyperbola_angle(hyperbola_t Hypr,
                                                       pnt3d_t P, double Alpha,
                                                       _Bool Sense) {
  return new geom_trimmed_curve_t{
      flywave::topo::geometry_creator::make_arc_of_hyperbola(
          cast_to_gp(Hypr), cast_to_gp(P), Alpha, Sense)};
}

geom_trimmed_curve_t *geom_make_arc_of_hyperbola_point(hyperbola_t Hypr,
                                                       pnt3d_t P1, pnt3d_t P2,
                                                       _Bool Sense) {
  return new geom_trimmed_curve_t{
      flywave::topo::geometry_creator::make_arc_of_hyperbola(
          cast_to_gp(Hypr), cast_to_gp(P1), cast_to_gp(P2), Sense)};
}

geom_trimmed_curve_t *geom_make_arc_of_parabola_two_angles(parabola_t Parab,
                                                           double Alpha1,
                                                           double Alpha2,
                                                           _Bool Sense) {
  return new geom_trimmed_curve_t{
      flywave::topo::geometry_creator::make_arc_of_parabola(
          cast_to_gp(Parab), Alpha1, Alpha2, Sense)};
}

geom_trimmed_curve_t *geom_make_arc_of_parabola_angle(parabola_t Parab,
                                                      pnt3d_t P, double Alpha,
                                                      _Bool Sense) {
  return new geom_trimmed_curve_t{
      flywave::topo::geometry_creator::make_arc_of_parabola(
          cast_to_gp(Parab), cast_to_gp(P), Alpha, Sense)};
}

geom_trimmed_curve_t *geom_make_arc_of_parabola_point(parabola_t Parab,
                                                      pnt3d_t P1, pnt3d_t P2,
                                                      _Bool Sense) {
  return new geom_trimmed_curve_t{
      flywave::topo::geometry_creator::make_arc_of_parabola(
          cast_to_gp(Parab), cast_to_gp(P1), cast_to_gp(P2), Sense)};
}

geom_circle_t *geom_make_circle(circ_t C) {
  return new geom_circle_t{
      flywave::topo::geometry_creator::make_circle(cast_to_gp(C))};
}

geom_circle_t *geom_make_circle_of_axis2(axis2_t A2, double Radius) {
  return new geom_circle_t{
      flywave::topo::geometry_creator::make_circle(cast_to_gp(A2), Radius)};
}

geom_circle_t *geom_make_circle_of_dist(circ_t Circ, double Dist) {
  return new geom_circle_t{
      flywave::topo::geometry_creator::make_circle(cast_to_gp(Circ), Dist)};
}

geom_circle_t *geom_make_circle_of_point(circ_t Circ, pnt3d_t Point) {
  return new geom_circle_t{flywave::topo::geometry_creator::make_circle(
      cast_to_gp(Circ), cast_to_gp(Point))};
}

geom_circle_t *geom_make_circle_of_three_point(pnt3d_t P1, pnt3d_t P2,
                                               pnt3d_t P3) {
  return new geom_circle_t{flywave::topo::geometry_creator::make_circle(
      cast_to_gp(P1), cast_to_gp(P2), cast_to_gp(P3))};
}

geom_circle_t *geom_make_circle_of_center_norm(pnt3d_t Center, dir3d_t Norm,
                                               double Radius) {
  return new geom_circle_t{flywave::topo::geometry_creator::make_circle(
      cast_to_gp(Center), cast_to_gp(Norm), Radius)};
}

geom_circle_t *geom_make_circle_center_axis(pnt3d_t Center, pnt3d_t PtAxis,
                                            double Radius) {
  return new geom_circle_t{flywave::topo::geometry_creator::make_circle(
      cast_to_gp(Center), cast_to_gp(PtAxis), Radius)};
}

geom_circle_t *geom_make_circle_of_axis1(axis1_t Axis, double Radius) {
  return new geom_circle_t{
      flywave::topo::geometry_creator::make_circle(cast_to_gp(Axis), Radius)};
}

geom_ellipse_t *geom_make_ellipse(elips_t E) {
  return new geom_ellipse_t{
      flywave::topo::geometry_creator::make_ellipse(cast_to_gp(E))};
}

geom_ellipse_t *geom_make_ellipse_of_axis2(axis2_t A2, double MajorRadius,
                                           double MinorRadius) {
  return new geom_ellipse_t{flywave::topo::geometry_creator::make_ellipse(
      cast_to_gp(A2), MajorRadius, MinorRadius)};
}

geom_ellipse_t *geom_make_ellipse_point_center(pnt3d_t S1, pnt3d_t S2,
                                               pnt3d_t Center) {
  return new geom_ellipse_t{flywave::topo::geometry_creator::make_ellipse(
      cast_to_gp(S1), cast_to_gp(S2), cast_to_gp(Center))};
}

geom_hyperbola_t *geom_make_hyperbola(hyperbola_t H) {
  return new geom_hyperbola_t{
      flywave::topo::geometry_creator::make_hyperbola(cast_to_gp(H))};
}

geom_hyperbola_t *geom_make_hyperbola_of_axis2(axis2_t A2, double MajorRadius,
                                               double MinorRadius) {
  return new geom_hyperbola_t{flywave::topo::geometry_creator::make_hyperbola(
      cast_to_gp(A2), MajorRadius, MinorRadius)};
}

geom_hyperbola_t *geom_make_hyperbola_point_center(pnt3d_t S1, pnt3d_t S2,
                                                   pnt3d_t Center) {
  return new geom_hyperbola_t{flywave::topo::geometry_creator::make_hyperbola(
      cast_to_gp(S1), cast_to_gp(S2), cast_to_gp(Center))};
}

geom_conical_surface_t *geom_make_conical_surface_axis2(axis2_t A2, double Ang,
                                                        double Radius) {
  return new geom_conical_surface_t{
      flywave::topo::geometry_creator::make_conical_surface(cast_to_gp(A2), Ang,
                                                            Radius)};
}

geom_conical_surface_t *geom_make_conical_surface(cone_t C) {
  return new geom_conical_surface_t{
      flywave::topo::geometry_creator::make_conical_surface(cast_to_gp(C))};
}

geom_conical_surface_t *geom_make_conical_surface_of_point(pnt3d_t P1,
                                                           pnt3d_t P2,
                                                           pnt3d_t P3,
                                                           pnt3d_t P4) {
  return new geom_conical_surface_t{
      flywave::topo::geometry_creator::make_conical_surface(
          cast_to_gp(P1), cast_to_gp(P2), cast_to_gp(P3), cast_to_gp(P4))};
}

geom_conical_surface_t *geom_make_conical_surface_of_point_radius(pnt3d_t P1,
                                                                  pnt3d_t P2,
                                                                  double R1,
                                                                  double R2) {
  return new geom_conical_surface_t{
      flywave::topo::geometry_creator::make_conical_surface(
          cast_to_gp(P1), cast_to_gp(P2), R1, R2)};
}

geom_cylindrical_surface_t *
geom_make_cylindrical_surface_of_axis2(axis2_t A2, double Radius) {
  return new geom_cylindrical_surface_t{
      flywave::topo::geometry_creator::make_cylindrical_surface(cast_to_gp(A2),
                                                                Radius)};
}

geom_cylindrical_surface_t *geom_make_cylindrical_surface(cylinder_t C) {
  return new geom_cylindrical_surface_t{
      flywave::topo::geometry_creator::make_cylindrical_surface(cast_to_gp(C))};
}

geom_cylindrical_surface_t *
geom_make_cylindrical_surface_of_point(cylinder_t Cyl, pnt3d_t Point) {
  return new geom_cylindrical_surface_t{
      flywave::topo::geometry_creator::make_cylindrical_surface(
          cast_to_gp(Cyl), cast_to_gp(Point))};
}

geom_cylindrical_surface_t *
geom_make_cylindrical_surface_of_dist(cylinder_t Cyl, double Dist) {
  return new geom_cylindrical_surface_t{
      flywave::topo::geometry_creator::make_cylindrical_surface(cast_to_gp(Cyl),
                                                                Dist)};
}

geom_cylindrical_surface_t *
geom_make_cylindrical_surface_of_three_point(pnt3d_t P1, pnt3d_t P2,
                                             pnt3d_t P3) {
  return new geom_cylindrical_surface_t{
      flywave::topo::geometry_creator::make_cylindrical_surface(
          cast_to_gp(P1), cast_to_gp(P2), cast_to_gp(P3))};
}

geom_cylindrical_surface_t *
geom_make_cylindrical_surface_of_axis_radius(axis1_t Axis, double Radius) {
  return new geom_cylindrical_surface_t{
      flywave::topo::geometry_creator::make_cylindrical_surface(
          cast_to_gp(Axis), Radius)};
}

geom_cylindrical_surface_t *geom_make_cylindrical_surface_of_circ(circ_t Circ) {
  return new geom_cylindrical_surface_t{
      flywave::topo::geometry_creator::make_cylindrical_surface(
          cast_to_gp(Circ))};
}

geom_line_t *geom_make_line_of_axis1(axis1_t A1) {
  return new geom_line_t{
      flywave::topo::geometry_creator::make_line(cast_to_gp(A1))};
}

geom_line_t *geom_make_line(line_t L) {
  return new geom_line_t{
      flywave::topo::geometry_creator::make_line(cast_to_gp(L))};
}

geom_line_t *geom_make_line_of_point_dir(pnt3d_t P, dir3d_t V) {
  return new geom_line_t{
      flywave::topo::geometry_creator::make_line(cast_to_gp(P), cast_to_gp(V))};
}

geom_line_t *geom_make_line_point(line_t Lin, pnt3d_t Point) {
  return new geom_line_t{flywave::topo::geometry_creator::make_line(
      cast_to_gp(Lin), cast_to_gp(Point))};
}

geom_line_t *geom_make_line_of_two_point(pnt3d_t P1, pnt3d_t P2) {
  return new geom_line_t{flywave::topo::geometry_creator::make_line(
      cast_to_gp(P1), cast_to_gp(P2))};
}

geom_transformation_t *geom_make_mirror_of_point(pnt3d_t Point) {
  return new geom_transformation_t{
      flywave::topo::geometry_creator::make_mirror(cast_to_gp(Point))};
}

geom_transformation_t *geom_make_mirror_of_axis1(axis1_t Axis) {
  return new geom_transformation_t{
      flywave::topo::geometry_creator::make_mirror(cast_to_gp(Axis))};
}

geom_transformation_t *geom_make_mirror_of_line(line_t Line) {
  return new geom_transformation_t{
      flywave::topo::geometry_creator::make_mirror(cast_to_gp(Line))};
}

geom_transformation_t *geom_make_mirror_of_point_dir(pnt3d_t Point,
                                                     dir3d_t Direc) {
  return new geom_transformation_t{flywave::topo::geometry_creator::make_mirror(
      cast_to_gp(Point), cast_to_gp(Direc))};
}

geom_transformation_t *geom_make_mirror_of_plane(plane_t Plane) {
  return new geom_transformation_t{
      flywave::topo::geometry_creator::make_mirror(cast_to_gp(Plane))};
}

geom_transformation_t *geom_make_mirror_of_axis2(axis2_t Plane) {
  return new geom_transformation_t{
      flywave::topo::geometry_creator::make_mirror(cast_to_gp(Plane))};
}

geom_transformation_t *geom_make_rotation_of_line(line_t Line, double Angle) {
  return new geom_transformation_t{
      flywave::topo::geometry_creator::make_rotation(cast_to_gp(Line), Angle)};
}

geom_transformation_t *geom_make_rotation_of_axis1(axis1_t Axis, double Angle) {
  return new geom_transformation_t{
      flywave::topo::geometry_creator::make_rotation(cast_to_gp(Axis), Angle)};
}

geom_transformation_t *
geom_make_rotation_of_point_dir(pnt3d_t Point, dir3d_t Direc, double Angle) {
  return new geom_transformation_t{
      flywave::topo::geometry_creator::make_rotation(cast_to_gp(Point),
                                                     cast_to_gp(Direc), Angle)};
}

geom_transformation_t *geom_make_translation_of_vect(vec3d_t Vect) {
  return new geom_transformation_t{
      flywave::topo::geometry_creator::make_translation(cast_to_gp(Vect))};
}

geom_transformation_t *geom_make_translation_of_two_point(pnt3d_t Point1,
                                                          pnt3d_t Point2) {
  return new geom_transformation_t{
      flywave::topo::geometry_creator::make_translation(cast_to_gp(Point1),
                                                        cast_to_gp(Point2))};
}

geom_transformation_t *geom_make_scale_of_point_scale(pnt3d_t Point,
                                                      double Scale) {
  return new geom_transformation_t{
      flywave::topo::geometry_creator::make_scale(cast_to_gp(Point), Scale)};
}

geom_plane_surface_t *geom_make_plane(plane_t Pl) {
  return new geom_plane_surface_t{
      flywave::topo::geometry_creator::make_plane(cast_to_gp(Pl))};
}

geom_plane_surface_t *geom_make_plane_of_point_dir(pnt3d_t P, dir3d_t V) {
  return new geom_plane_surface_t{flywave::topo::geometry_creator::make_plane(
      cast_to_gp(P), cast_to_gp(V))};
}

geom_plane_surface_t *geom_make_plane_of_lrud(double A, double B, double C,
                                              double D) {
  return new geom_plane_surface_t{
      flywave::topo::geometry_creator::make_plane(A, B, C, D)};
}

geom_plane_surface_t *geom_make_plane_of_point(plane_t Pln, pnt3d_t Point) {
  return new geom_plane_surface_t{flywave::topo::geometry_creator::make_plane(
      cast_to_gp(Pln), cast_to_gp(Point))};
}

geom_plane_surface_t *geom_make_plane_of_dist(plane_t Pln, double Dist) {
  return new geom_plane_surface_t{
      flywave::topo::geometry_creator::make_plane(cast_to_gp(Pln), Dist)};
}

geom_plane_surface_t *geom_make_plane_of_three_point(pnt3d_t P1, pnt3d_t P2,
                                                     pnt3d_t P3) {
  return new geom_plane_surface_t{flywave::topo::geometry_creator::make_plane(
      cast_to_gp(P1), cast_to_gp(P2), cast_to_gp(P3))};
}

geom_plane_surface_t *geom_make_plane_of_axis1(axis1_t Axis) {
  return new geom_plane_surface_t{
      flywave::topo::geometry_creator::make_plane(cast_to_gp(Axis))};
}

geom_trimmed_curve_t *geom_make_segment_of_two_point(pnt3d_t P1, pnt3d_t P2) {
  return new geom_trimmed_curve_t{flywave::topo::geometry_creator::make_segment(
      cast_to_gp(P1), cast_to_gp(P2))};
}

geom_trimmed_curve_t *geom_make_segment_of_line_u(line_t Line, double U1,
                                                  double U2) {
  return new geom_trimmed_curve_t{
      flywave::topo::geometry_creator::make_segment(cast_to_gp(Line), U1, U2)};
}

geom_trimmed_curve_t *
geom_make_segment_of_line_point(line_t Line, pnt3d_t Point, double Ulast) {
  return new geom_trimmed_curve_t{flywave::topo::geometry_creator::make_segment(
      cast_to_gp(Line), cast_to_gp(Point), Ulast)};
}

geom_trimmed_curve_t *geom_make_segment_of_point(line_t Line, pnt3d_t P1,
                                                 pnt3d_t P2) {
  return new geom_trimmed_curve_t{flywave::topo::geometry_creator::make_segment(
      cast_to_gp(Line), cast_to_gp(P1), cast_to_gp(P2))};
}

geom_rectangular_trimmed_surface_t *
geom_make_trimmed_cone_of_point(pnt3d_t P1, pnt3d_t P2, pnt3d_t P3,
                                pnt3d_t P4) {
  return new geom_rectangular_trimmed_surface_t{
      flywave::topo::geometry_creator::make_trimmed_cone(
          cast_to_gp(P1), cast_to_gp(P2), cast_to_gp(P3), cast_to_gp(P4))};
}

geom_rectangular_trimmed_surface_t *
geom_make_trimmed_cone_of_point_radius(pnt3d_t P1, pnt3d_t P2, double R1,
                                       double R2) {
  return new geom_rectangular_trimmed_surface_t{
      flywave::topo::geometry_creator::make_trimmed_cone(
          cast_to_gp(P1), cast_to_gp(P2), R1, R2)};
}

geom_rectangular_trimmed_surface_t *
geom_make_trimmed_cylinder_of_point(pnt3d_t P1, pnt3d_t P2, pnt3d_t P3) {
  return new geom_rectangular_trimmed_surface_t{
      flywave::topo::geometry_creator::make_trimmed_cylinder(
          cast_to_gp(P1), cast_to_gp(P2), cast_to_gp(P3))};
}

geom_rectangular_trimmed_surface_t *
geom_make_trimmed_cylinder_of_circ_height(circ_t Circ, double Height) {
  return new geom_rectangular_trimmed_surface_t{
      flywave::topo::geometry_creator::make_trimmed_cylinder(cast_to_gp(Circ),
                                                             Height)};
}

geom_rectangular_trimmed_surface_t *
geom_make_trimmed_cylinder_axis_radius(axis1_t A1, double Radius,
                                       double Height) {
  return new geom_rectangular_trimmed_surface_t{
      flywave::topo::geometry_creator::make_trimmed_cylinder(cast_to_gp(A1),
                                                             Radius, Height)};
}

geom2d_trimmed_curve_t *geom2d_make_arc_of_circle_two_angles(circ2d_t Circ,
                                                             double Alpha1,
                                                             double Alpha2,
                                                             _Bool Sense) {
  return new geom2d_trimmed_curve_t{
      flywave::topo::geometry_creator::make_arc_of_circle(
          cast_to_gp(Circ), Alpha1, Alpha2, Sense)};
}

geom2d_trimmed_curve_t *geom2d_make_arc_of_circle_angle(circ2d_t Circ,
                                                        pnt2d_t P, double Alpha,
                                                        _Bool Sense) {
  return new geom2d_trimmed_curve_t{
      flywave::topo::geometry_creator::make_arc_of_circle(
          cast_to_gp(Circ), cast_to_gp(P), Alpha, Sense)};
}

geom2d_trimmed_curve_t *geom2d_make_arc_of_circle_two_point(circ2d_t Circ,
                                                            pnt2d_t P1,
                                                            pnt2d_t P2,
                                                            _Bool Sense) {
  return new geom2d_trimmed_curve_t{
      flywave::topo::geometry_creator::make_arc_of_circle(
          cast_to_gp(Circ), cast_to_gp(P1), cast_to_gp(P2), Sense)};
}

geom2d_trimmed_curve_t *geom2d_make_arc_of_circle_point(pnt2d_t P1, pnt2d_t P2,
                                                        pnt2d_t P3) {
  return new geom2d_trimmed_curve_t{
      flywave::topo::geometry_creator::make_arc_of_circle(
          cast_to_gp(P1), cast_to_gp(P2), cast_to_gp(P3))};
}

geom2d_trimmed_curve_t *geom2d_make_arc_of_circle_vector(pnt2d_t P1, vec2d_t V,
                                                         pnt2d_t P2) {
  return new geom2d_trimmed_curve_t{
      flywave::topo::geometry_creator::make_arc_of_circle_vector(
          cast_to_gp(P1), cast_to_gp(V), cast_to_gp(P2))};
}

geom2d_trimmed_curve_t *geom2d_make_arc_of_ellipse_two_angles(elips2d_t Elips,
                                                              double Alpha1,
                                                              double Alpha2,
                                                              _Bool Sense) {
  return new geom2d_trimmed_curve_t{
      flywave::topo::geometry_creator::make_arc_of_ellipse(
          cast_to_gp(Elips), Alpha1, Alpha2, Sense)};
}

geom2d_trimmed_curve_t *geom2d_make_arc_of_ellipse_angle(elips2d_t Elips,
                                                         pnt2d_t P,
                                                         double Alpha,
                                                         _Bool Sense) {
  return new geom2d_trimmed_curve_t{
      flywave::topo::geometry_creator::make_arc_of_ellipse(
          cast_to_gp(Elips), cast_to_gp(P), Alpha, Sense)};
}

geom2d_trimmed_curve_t *geom2d_make_arc_of_ellipse_point(elips2d_t Elips,
                                                         pnt2d_t P1, pnt2d_t P2,
                                                         _Bool Sense) {
  return new geom2d_trimmed_curve_t{
      flywave::topo::geometry_creator::make_arc_of_ellipse(
          cast_to_gp(Elips), cast_to_gp(P1), cast_to_gp(P2), Sense)};
}

geom2d_trimmed_curve_t *
geom2d_make_arc_of_hyperbola_two_angles(hyperbola2d_t Hypr, double Alpha1,
                                        double Alpha2, _Bool Sense) {
  return new geom2d_trimmed_curve_t{
      flywave::topo::geometry_creator::make_arc_of_hyperbola(
          cast_to_gp(Hypr), Alpha1, Alpha2, Sense)};
}

geom2d_trimmed_curve_t *geom2d_make_arc_of_hyperbola_angle(hyperbola2d_t Hypr,
                                                           pnt2d_t P,
                                                           double Alpha,
                                                           _Bool Sense) {
  return new geom2d_trimmed_curve_t{
      flywave::topo::geometry_creator::make_arc_of_hyperbola(
          cast_to_gp(Hypr), cast_to_gp(P), Alpha, Sense)};
}

geom2d_trimmed_curve_t *geom2d_make_arc_of_hyperbola_point(hyperbola2d_t Hypr,
                                                           pnt2d_t P1,
                                                           pnt2d_t P2,
                                                           _Bool Sense) {
  return new geom2d_trimmed_curve_t{
      flywave::topo::geometry_creator::make_arc_of_hyperbola(
          cast_to_gp(Hypr), cast_to_gp(P1), cast_to_gp(P2), Sense)};
}

geom2d_trimmed_curve_t *
geom2d_make_arc_of_parabola_two_angles(parabola2d_t Parab, double Alpha1,
                                       double Alpha2, _Bool Sense) {
  return new geom2d_trimmed_curve_t{
      flywave::topo::geometry_creator::make_arc_of_parabola(
          cast_to_gp(Parab), Alpha1, Alpha2, Sense)};
}

geom2d_trimmed_curve_t *
geom2d_make_arc_of_parabola_angle_angle(parabola2d_t Parab, pnt2d_t P,
                                        double Alpha, _Bool Sense) {
  return new geom2d_trimmed_curve_t{
      flywave::topo::geometry_creator::make_arc_of_parabola(
          cast_to_gp(Parab), cast_to_gp(P), Alpha, Sense)};
}

geom2d_trimmed_curve_t *geom2d_make_arc_of_parabola_point(parabola2d_t Parab,
                                                          pnt2d_t P1,
                                                          pnt2d_t P2,
                                                          _Bool Sense) {
  return new geom2d_trimmed_curve_t{
      flywave::topo::geometry_creator::make_arc_of_parabola(
          cast_to_gp(Parab), cast_to_gp(P1), cast_to_gp(P2), Sense)};
}

geom2d_circle_t *geom2d_make_circle(circ2d_t C) {
  return new geom2d_circle_t{
      flywave::topo::geometry_creator::make_circle(cast_to_gp(C))};
}

geom2d_circle_t *geom2d_make_circle_of_axis2d(axis2d_t A, double Radius,
                                              _Bool Sense) {
  return new geom2d_circle_t{flywave::topo::geometry_creator::make_circle(
      cast_to_gp(A), Radius, Sense)};
}

geom2d_circle_t *geom2d_make_circle_of_axis22d(axis22d_t A, double Radius) {
  return new geom2d_circle_t{
      flywave::topo::geometry_creator::make_circle(cast_to_gp(A), Radius)};
}

geom2d_circle_t *geom2d_make_circle_of_circ2d_dist(circ2d_t Circ, double Dist) {
  return new geom2d_circle_t{
      flywave::topo::geometry_creator::make_circle(cast_to_gp(Circ), Dist)};
}

geom2d_circle_t *geom2d_make_circle_of_circ2d_point(circ2d_t Circ,
                                                    pnt2d_t Point) {
  return new geom2d_circle_t{flywave::topo::geometry_creator::make_circle(
      cast_to_gp(Circ), cast_to_gp(Point))};
}

geom2d_circle_t *geom2d_make_circle_of_three_point(pnt2d_t P1, pnt2d_t P2,
                                                   pnt2d_t P3) {
  return new geom2d_circle_t{flywave::topo::geometry_creator::make_circle(
      cast_to_gp(P1), cast_to_gp(P2), cast_to_gp(P3))};
}

geom2d_circle_t *geom2d_make_circle_of_point_radius(pnt2d_t P, double Radius,
                                                    _Bool Sense) {
  return new geom2d_circle_t{flywave::topo::geometry_creator::make_circle(
      cast_to_gp(P), Radius, Sense)};
}

geom2d_circle_t *geom2d_make_circle_of_center_radius(pnt2d_t Center,
                                                     pnt2d_t Point,
                                                     _Bool Sense) {
  return new geom2d_circle_t{flywave::topo::geometry_creator::make_circle(
      cast_to_gp(Center), cast_to_gp(Point), Sense)};
}

geom2d_ellipse_t *geom2d_make_ellipse(elips2d_t E) {
  return new geom2d_ellipse_t{
      flywave::topo::geometry_creator::make_ellipse(cast_to_gp(E))};
}

geom2d_ellipse_t *geom2d_make_ellipse_of_axis2d_radius(axis2d_t MajorAxis,
                                                       double MajorRadius,
                                                       double MinorRadius,
                                                       _Bool Sense) {
  return new geom2d_ellipse_t{flywave::topo::geometry_creator::make_ellipse(
      cast_to_gp(MajorAxis), MajorRadius, MinorRadius, Sense)};
}

geom2d_ellipse_t *geom2d_make_ellipse_of_axis22d_radius(axis22d_t Axis,
                                                        double MajorRadius,
                                                        double MinorRadius) {
  return new geom2d_ellipse_t{flywave::topo::geometry_creator::make_ellipse(
      cast_to_gp(Axis), MajorRadius, MinorRadius)};
}

geom2d_ellipse_t *geom2d_make_ellipse_of_three_point(pnt2d_t S1, pnt2d_t S2,
                                                     pnt2d_t Center) {
  return new geom2d_ellipse_t{flywave::topo::geometry_creator::make_ellipse(
      cast_to_gp(S1), cast_to_gp(S2), cast_to_gp(Center))};
}

geom2d_hyperbola_t *geom2d_make_hyperbola(hyperbola2d_t H) {
  return new geom2d_hyperbola_t{
      flywave::topo::geometry_creator::make_hyperbola(cast_to_gp(H))};
}

geom2d_hyperbola_t *geom2d_make_hyperbola_of_axis2d_radius(axis2d_t MajorAxis,
                                                           double MajorRadius,
                                                           double MinorRadius,
                                                           _Bool Sense) {
  return new geom2d_hyperbola_t{flywave::topo::geometry_creator::make_hyperbola(
      cast_to_gp(MajorAxis), MajorRadius, MinorRadius, Sense)};
}

geom2d_hyperbola_t *
geom2d_make_hyperbola_of_axis22d_radius(axis22d_t Axis, double MajorRadius,
                                        double MinorRadius) {
  return new geom2d_hyperbola_t{flywave::topo::geometry_creator::make_hyperbola(
      cast_to_gp(Axis), MajorRadius, MinorRadius)};
}

geom2d_hyperbola_t *geom2d_make_hyperbola_of_three_point(pnt2d_t S1, pnt2d_t S2,
                                                         pnt2d_t Center) {
  return new geom2d_hyperbola_t{flywave::topo::geometry_creator::make_hyperbola(
      cast_to_gp(S1), cast_to_gp(S2), cast_to_gp(Center))};
}

geom2d_line_t *geom2d_make_line_of_axis2d(axis2d_t A) {
  return new geom2d_line_t{
      flywave::topo::geometry_creator::make_line(cast_to_gp(A))};
}

geom2d_line_t *geom2d_make_line(line2d_t L) {
  return new geom2d_line_t{
      flywave::topo::geometry_creator::make_line(cast_to_gp(L))};
}

geom2d_line_t *geom2d_make_line_of_point_dir(pnt2d_t P, dir2d_t V) {
  return new geom2d_line_t{
      flywave::topo::geometry_creator::make_line(cast_to_gp(P), cast_to_gp(V))};
}

geom2d_line_t *geom2d_make_line_of_point(line2d_t Lin, pnt2d_t Point) {
  return new geom2d_line_t{flywave::topo::geometry_creator::make_line(
      cast_to_gp(Lin), cast_to_gp(Point))};
}

geom2d_line_t *geom2d_make_line_of_dist(line2d_t Lin, double Dist) {
  return new geom2d_line_t{
      flywave::topo::geometry_creator::make_line(cast_to_gp(Lin), Dist)};
}

geom2d_line_t *geom2d_make_line_of_two_point(pnt2d_t P1, pnt2d_t P2) {
  return new geom2d_line_t{flywave::topo::geometry_creator::make_line(
      cast_to_gp(P1), cast_to_gp(P2))};
}

geom2d_parabola_t *geom2d_make_parabola(parabola2d_t Prb) {
  return new geom2d_parabola_t{
      flywave::topo::geometry_creator::make_parabola(cast_to_gp(Prb))};
}

geom2d_parabola_t *geom2d_make_parabola_of_axis22d(axis22d_t Axis,
                                                   double Focal) {
  return new geom2d_parabola_t{
      flywave::topo::geometry_creator::make_parabola(cast_to_gp(Axis), Focal)};
}

geom2d_parabola_t *geom2d_make_parabola_of_axis2d(axis2d_t MirrorAxis,
                                                  double Focal, _Bool Sense) {
  return new geom2d_parabola_t{flywave::topo::geometry_creator::make_parabola(
      cast_to_gp(MirrorAxis), Focal, Sense)};
}

geom2d_parabola_t *geom2d_make_parabola_of_axis2d_point(axis2d_t D, pnt2d_t F,
                                                        _Bool Sense) {
  return new geom2d_parabola_t{flywave::topo::geometry_creator::make_parabola(
      cast_to_gp(D), cast_to_gp(F), Sense)};
}

geom2d_parabola_t *geom2d_make_parabola_point(pnt2d_t S1, pnt2d_t O) {
  return new geom2d_parabola_t{flywave::topo::geometry_creator::make_parabola(
      cast_to_gp(S1), cast_to_gp(O))};
}

geom2d_trimmed_curve_t *geom2d_make_segment_of_point(pnt2d_t P1, pnt2d_t P2) {
  return new geom2d_trimmed_curve_t{
      flywave::topo::geometry_creator::make_segment(cast_to_gp(P1),
                                                    cast_to_gp(P2))};
}

geom2d_trimmed_curve_t *geom2d_make_segment_of_point_dir(pnt2d_t P1, dir2d_t V,
                                                         pnt2d_t P2) {
  return new geom2d_trimmed_curve_t{
      flywave::topo::geometry_creator::make_segment(
          cast_to_gp(P1), cast_to_gp(V), cast_to_gp(P2))};
}

geom2d_trimmed_curve_t *geom2d_make_segment_of_line(line2d_t Line, double U1,
                                                    double U2) {
  return new geom2d_trimmed_curve_t{
      flywave::topo::geometry_creator::make_segment(cast_to_gp(Line), U1, U2)};
}

geom2d_trimmed_curve_t *
geom2d_make_segment_of_line_point(line2d_t Line, pnt2d_t Point, double Ulast) {
  return new geom2d_trimmed_curve_t{
      flywave::topo::geometry_creator::make_segment(cast_to_gp(Line),
                                                    cast_to_gp(Point), Ulast)};
}

geom2d_trimmed_curve_t *
geom2d_make_segment_of_line_two_point(line2d_t Line, pnt2d_t P1, pnt2d_t P2) {
  return new geom2d_trimmed_curve_t{
      flywave::topo::geometry_creator::make_segment(
          cast_to_gp(Line), cast_to_gp(P1), cast_to_gp(P2))};
}

geom2d_transformation_t *geom2d_make_mirror_of_point(pnt2d_t Point) {
  return new geom2d_transformation_t{
      flywave::topo::geometry_creator::make_mirror(cast_to_gp(Point))};
}

geom2d_transformation_t *geom2d_make_mirror_of_axis2d(axis2d_t Axis) {
  return new geom2d_transformation_t{
      flywave::topo::geometry_creator::make_mirror(cast_to_gp(Axis))};
}

geom2d_transformation_t *geom2d_make_mirror_of_line2d(line2d_t Line) {
  return new geom2d_transformation_t{
      flywave::topo::geometry_creator::make_mirror(cast_to_gp(Line))};
}

geom2d_transformation_t *geom2d_make_mirror_of_point_dir(pnt2d_t Point,
                                                         dir2d_t Direc) {
  return new geom2d_transformation_t{
      flywave::topo::geometry_creator::make_mirror(cast_to_gp(Point),
                                                   cast_to_gp(Direc))};
}

geom2d_transformation_t *geom2d_make_rotation_of_point_angle(pnt2d_t Point,
                                                             double Angle) {
  return new geom2d_transformation_t{
      flywave::topo::geometry_creator::make_rotation(cast_to_gp(Point), Angle)};
}

geom2d_transformation_t *geom2d_make_scale_point_scale(pnt2d_t Point,
                                                       double Scale) {
  return new geom2d_transformation_t{
      flywave::topo::geometry_creator::make_scale(cast_to_gp(Point), Scale)};
}

geom2d_transformation_t *geom2d_make_translation_of_vector(vec2d_t Vect) {
  return new geom2d_transformation_t{
      flywave::topo::geometry_creator::make_translation(cast_to_gp(Vect))};
}

geom2d_transformation_t *geom2d_make_translation_of_point(pnt2d_t Point1,
                                                          pnt2d_t Point2) {
  return new geom2d_transformation_t{
      flywave::topo::geometry_creator::make_translation(cast_to_gp(Point1),
                                                        cast_to_gp(Point2))};
}

geom_geometry_t *geom_axis_placement_to_geometry(geom_axis_placement_t *t) {
  return new geom_geometry_t{t->handle};
}

geom_geometry_t *geom_axis1_placement_to_geometry(geom_axis1_placement_t *t) {
  return new geom_geometry_t{t->handle};
}

geom_geometry_t *geom_axis2_placement_to_geometry(geom_axis2_placement_t *t) {
  return new geom_geometry_t{t->handle};
}

geom_geometry_t *geom_curve_to_geometry(geom_curve_t *t) {
  return new geom_geometry_t{t->handle};
}

geom_geometry_t *geom_bounded_curve_to_geometry(geom_bounded_curve_t *t) {
  return new geom_geometry_t{t->handle};
}

geom_geometry_t *geom_bezier_curve_to_geometry(geom_bezier_curve_t *t) {
  return new geom_geometry_t{t->handle};
}

geom_geometry_t *geom_bspline_curve_to_geometry(geom_bspline_curve_t *t) {
  return new geom_geometry_t{t->handle};
}

geom_geometry_t *geom_trimmed_curve_to_geometry(geom_trimmed_curve_t *t) {
  return new geom_geometry_t{t->handle};
}

geom_geometry_t *geom_conic_to_geometry(geom_conic_t *t) {
  return new geom_geometry_t{t->handle};
}

geom_geometry_t *geom_circle_to_geometry(geom_circle_t *t) {
  return new geom_geometry_t{t->handle};
}

geom_geometry_t *geom_ellipse_to_geometry(geom_ellipse_t *t) {
  return new geom_geometry_t{t->handle};
}

geom_geometry_t *geom_hyperbola_to_geometry(geom_hyperbola_t *t) {
  return new geom_geometry_t{t->handle};
}

geom_geometry_t *geom_parabola_to_geometry(geom_parabola_t *t) {
  return new geom_geometry_t{t->handle};
}

geom_geometry_t *geom_line_to_geometry(geom_line_t *t) {
  return new geom_geometry_t{t->handle};
}

geom_geometry_t *geom_offset_curve_to_geometry(geom_offset_curve_t *t) {
  return new geom_geometry_t{t->handle};
}

geom_geometry_t *geom_point_to_geometry(geom_point_t *t) {
  return new geom_geometry_t{t->handle};
}

geom_geometry_t *geom_cartesian_point_to_geometry(geom_cartesian_point_t *t) {
  return new geom_geometry_t{t->handle};
}

geom_geometry_t *geom_surface_to_geometry(geom_surface_t *t) {
  return new geom_geometry_t{t->handle};
}

geom_geometry_t *geom_bounded_surface_to_geometry(geom_bounded_surface_t *t) {
  return new geom_geometry_t{t->handle};
}

geom_geometry_t *geom_bezier_surface_to_geometry(geom_bezier_surface_t *t) {
  return new geom_geometry_t{t->handle};
}

geom_geometry_t *geom_bspline_surface_to_geometry(geom_bspline_surface_t *t) {
  return new geom_geometry_t{t->handle};
}

geom_geometry_t *geom_rectangular_trimmed_surface_to_geometry(
    geom_rectangular_trimmed_surface_t *t) {
  return new geom_geometry_t{t->handle};
}

geom_geometry_t *
geom_elementary_surface_to_geometry(geom_elementary_surface_t *t) {
  return new geom_geometry_t{t->handle};
}

geom_geometry_t *
geom_cylindrical_surface_to_geometry(geom_cylindrical_surface_t *t) {
  return new geom_geometry_t{t->handle};
}

geom_geometry_t *geom_plane_surface_to_geometry(geom_plane_surface_t *t) {
  return new geom_geometry_t{t->handle};
}

geom_geometry_t *geom_conical_surface_to_geometry(geom_conical_surface_t *t) {
  return new geom_geometry_t{t->handle};
}

geom_geometry_t *
geom_spherical_surface_to_geometry(geom_spherical_surface_t *t) {
  return new geom_geometry_t{t->handle};
}

geom_geometry_t *geom_toroidal_surface_to_geometry(geom_toroidal_surface_t *t) {
  return new geom_geometry_t{t->handle};
}

geom_geometry_t *geom_offset_surface_to_geometry(geom_offset_surface_t *t) {
  return new geom_geometry_t{t->handle};
}

geom_geometry_t *geom_swept_surface_to_geometry(geom_swept_surface_t *t) {
  return new geom_geometry_t{t->handle};
}

geom_geometry_t *geom_surface_of_linear_extrusion_to_geometry(
    geom_surface_of_linear_extrusion_t *t) {
  return new geom_geometry_t{t->handle};
}

geom_geometry_t *geom_surface_of_revolution_extrusion_to_geometry(
    geom_surface_of_revolution_extrusion_t *t) {
  return new geom_geometry_t{t->handle};
}

geom_geometry_t *geom_plate_surface_to_geometry(geom_plate_surface_t *t) {
  return new geom_geometry_t{t->handle};
}

geom_geometry_t *geom_vector_to_geometry(geom_vector_t *t) {
  return new geom_geometry_t{t->handle};
}

geom_geometry_t *geom_direction_to_geometry(geom_direction_t *t) {
  return new geom_geometry_t{t->handle};
}

geom_geometry_t *
geom_vector_with_magnitude_to_geometry(geom_vector_with_magnitude_t *t) {
  return new geom_geometry_t{t->handle};
}

geom2d_geometry_t *
geom2d_axis_placement_to_geometry(geom2d_axis_placement_t *t) {
  return new geom2d_geometry_t{t->handle};
}

geom2d_geometry_t *geom2d_curve_to_geometry(geom2d_curve_t *t) {
  return new geom2d_geometry_t{t->handle};
}

geom2d_geometry_t *
geom2d_bisector_curve_to_geometry(geom2d_bisector_curve_t *t) {
  return new geom2d_geometry_t{t->handle};
}

geom2d_geometry_t *
geom2d_bezier_bisec_ana_curve_to_geometry(geom2d_bezier_bisec_ana_curve_t *t) {
  return new geom2d_geometry_t{t->handle};
}

geom2d_geometry_t *
geom2d_bezier_bisec_cc_curve_to_geometry(geom2d_bezier_bisec_cc_curve_t *t) {
  return new geom2d_geometry_t{t->handle};
}

geom2d_geometry_t *
geom2d_bezier_bisec_pc_curve_to_geometry(geom2d_bezier_bisec_pc_curve_t *t) {
  return new geom2d_geometry_t{t->handle};
}

geom2d_geometry_t *geom2d_bounded_curve_to_geometry(geom2d_bounded_curve_t *t) {
  return new geom2d_geometry_t{t->handle};
}

geom2d_geometry_t *geom2d_bezier_curve_to_geometry(geom2d_bezier_curve_t *t) {
  return new geom2d_geometry_t{t->handle};
}

geom2d_geometry_t *geom2d_bspline_curve_to_geometry(geom2d_bspline_curve_t *t) {
  return new geom2d_geometry_t{t->handle};
}

geom2d_geometry_t *geom2d_trimmed_curve_to_geometry(geom2d_trimmed_curve_t *t) {
  return new geom2d_geometry_t{t->handle};
}

geom2d_geometry_t *geom2d_conic_to_geometry(geom2d_conic_t *t) {
  return new geom2d_geometry_t{t->handle};
}

geom2d_geometry_t *geom2d_circle_to_geometry(geom2d_circle_t *t) {
  return new geom2d_geometry_t{t->handle};
}

geom2d_geometry_t *geom2d_ellipse_to_geometry(geom2d_ellipse_t *t) {
  return new geom2d_geometry_t{t->handle};
}

geom2d_geometry_t *geom2d_hyperbola_to_geometry(geom2d_hyperbola_t *t) {
  return new geom2d_geometry_t{t->handle};
}

geom2d_geometry_t *geom2d_parabola_to_geometry(geom2d_parabola_t *t) {
  return new geom2d_geometry_t{t->handle};
}

geom2d_geometry_t *geom2d_line_to_geometry(geom2d_line_t *t) {
  return new geom2d_geometry_t{t->handle};
}

geom2d_geometry_t *geom2d_offset_curve_to_geometry(geom2d_offset_curve_t *t) {
  return new geom2d_geometry_t{t->handle};
}

geom2d_geometry_t *geom2d_point_to_geometry(geom2d_point_t *t) {
  return new geom2d_geometry_t{t->handle};
}

geom2d_geometry_t *
geom2d_cartesian_point_to_geometry(geom2d_cartesian_point_t *t) {
  return new geom2d_geometry_t{t->handle};
}

geom2d_geometry_t *geom2d_vector_to_geometry(geom2d_vector_t *t) {
  return new geom2d_geometry_t{t->handle};
}

geom2d_geometry_t *geom2d_direction_to_geometry(geom2d_direction_t *t) {
  return new geom2d_geometry_t{t->handle};
}

geom2d_geometry_t *
geom2d_vector_with_magnitude_to_geometry(geom2d_vector_with_magnitude_t *t) {
  return new geom2d_geometry_t{t->handle};
}

geom_axis_placement_t *geom_axis_placement_from_geometry(geom_geometry_t *t) {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_AxisPlacement)) {
    return nullptr;
  }
  return new geom_axis_placement_t{
      Handle(Geom_AxisPlacement)::DownCast(t->handle)};
}

geom_axis1_placement_t *geom_axis1_placement_from_geometry(geom_geometry_t *t) {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_Axis1Placement)) {
    return nullptr;
  }
  return new geom_axis1_placement_t{
      Handle(Geom_Axis1Placement)::DownCast(t->handle)};
}

geom_axis2_placement_t *geom_axis2_placement_from_geometry(geom_geometry_t *t) {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_Axis2Placement)) {
    return nullptr;
  }
  return new geom_axis2_placement_t{
      Handle(Geom_Axis2Placement)::DownCast(t->handle)};
}

geom_curve_t *geom_curve_from_geometry(geom_geometry_t *t) {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_Curve)) {
    return nullptr;
  }
  return new geom_curve_t{.handle =Handle(Geom_Curve)::DownCast(t->handle)};
}

geom_bounded_curve_t *geom_bounded_curve_from_geometry(geom_geometry_t *t) {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_BoundedCurve)) {
    return nullptr;
  }
  return new geom_bounded_curve_t{
      Handle(Geom_BoundedCurve)::DownCast(t->handle)};
}

geom_bezier_curve_t *geom_bezier_curve_from_geometry(geom_geometry_t *t) {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_BezierCurve)) {
    return nullptr;
  }
  return new geom_bezier_curve_t{Handle(Geom_BezierCurve)::DownCast(t->handle)};
}

geom_bspline_curve_t *geom_bspline_curve_from_geometry(geom_geometry_t *t) {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_BSplineCurve)) {
    return nullptr;
  }
  return new geom_bspline_curve_t{
      Handle(Geom_BSplineCurve)::DownCast(t->handle)};
}
geom_bspline_curve_t *geom_bspline_curve_from_points(pnt3d_t *t, int size) {
  std::vector<pnt3d_t> pts(size);
  ::memcpy(pts.data(), t, sizeof(pnt3d_t) * size);
  auto points =
      new TColgp_HArray1OfPnt(1, static_cast<Standard_Integer>(pts.size()));
  cast_to_gp(pts, *points);
  Handle_TColgp_HArray1OfPnt p(points);
  GeomAPI_Interpolate interp(p, Standard_False, 1.0e-5);
  interp.Perform();
  if (!interp.IsDone())
    return nullptr;
  auto cur = interp.Curve();
  if (cur.IsNull())
    return nullptr;
  return new geom_bspline_curve_t{cur};
}

geom_trimmed_curve_t *geom_trimmed_curve_from_geometry(geom_geometry_t *t) {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_TrimmedCurve)) {
    return nullptr;
  }
  return new geom_trimmed_curve_t{
      Handle(Geom_TrimmedCurve)::DownCast(t->handle)};
}

geom_conic_t *geom_conic_from_geometry(geom_geometry_t *t) {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_Conic)) {
    return nullptr;
  }
  return new geom_conic_t{Handle(Geom_Conic)::DownCast(t->handle)};
}

geom_circle_t *geom_circle_from_geometry(geom_geometry_t *t) {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_Circle)) {
    return nullptr;
  }
  return new geom_circle_t{Handle(Geom_Circle)::DownCast(t->handle)};
}

geom_ellipse_t *geom_ellipse_from_geometry(geom_geometry_t *t) {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_Ellipse)) {
    return nullptr;
  }
  return new geom_ellipse_t{Handle(Geom_Ellipse)::DownCast(t->handle)};
}

geom_hyperbola_t *geom_hyperbola_from_geometry(geom_geometry_t *t) {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_Hyperbola)) {
    return nullptr;
  }
  return new geom_hyperbola_t{Handle(Geom_Hyperbola)::DownCast(t->handle)};
}

geom_parabola_t *geom_parabola_from_geometry(geom_geometry_t *t) {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_Parabola)) {
    return nullptr;
  }
  return new geom_parabola_t{Handle(Geom_Parabola)::DownCast(t->handle)};
}

geom_line_t *geom_line_from_geometry(geom_geometry_t *t) {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_Line)) {
    return nullptr;
  }
  return new geom_line_t{Handle(Geom_Line)::DownCast(t->handle)};
}

geom_offset_curve_t *geom_offset_curve_from_geometry(geom_geometry_t *t) {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_OffsetCurve)) {
    return nullptr;
  }
  return new geom_offset_curve_t{Handle(Geom_OffsetCurve)::DownCast(t->handle)};
}

geom_point_t *geom_point_from_geometry(geom_geometry_t *t) {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_Point)) {
    return nullptr;
  }
  return new geom_point_t{Handle(Geom_Point)::DownCast(t->handle)};
}

geom_cartesian_point_t *geom_cartesian_point_from_geometry(geom_geometry_t *t) {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_CartesianPoint)) {
    return nullptr;
  }
  return new geom_cartesian_point_t{
      Handle(Geom_CartesianPoint)::DownCast(t->handle)};
}

geom_surface_t *geom_surface_from_geometry(geom_geometry_t *t) {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_Surface)) {
    return nullptr;
  }
  return new geom_surface_t{Handle(Geom_Surface)::DownCast(t->handle)};
}

geom_bounded_surface_t *geom_bounded_surface_from_geometry(geom_geometry_t *t) {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_BoundedSurface)) {
    return nullptr;
  }
  return new geom_bounded_surface_t{
      Handle(Geom_BoundedSurface)::DownCast(t->handle)};
}

geom_bezier_surface_t *geom_bezier_surface_from_geometry(geom_geometry_t *t) {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_BezierSurface)) {
    return nullptr;
  }
  return new geom_bezier_surface_t{
      Handle(Geom_BezierSurface)::DownCast(t->handle)};
}

geom_bspline_surface_t *geom_bspline_surface_from_geometry(geom_geometry_t *t) {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_BSplineSurface)) {
    return nullptr;
  }
  return new geom_bspline_surface_t{
      Handle(Geom_BSplineSurface)::DownCast(t->handle)};
}

geom_rectangular_trimmed_surface_t *
geom_rectangular_trimmed_surface_from_geometry(geom_geometry_t *t) {
  if (t->handle->DynamicType() !=
      STANDARD_TYPE(Geom_RectangularTrimmedSurface)) {
    return nullptr;
  }
  return new geom_rectangular_trimmed_surface_t{
      Handle(Geom_RectangularTrimmedSurface)::DownCast(t->handle)};
}

geom_elementary_surface_t *
geom_elementary_surface_from_geometry(geom_geometry_t *t) {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_ElementarySurface)) {
    return nullptr;
  }
  return new geom_elementary_surface_t{
      Handle(Geom_ElementarySurface)::DownCast(t->handle)};
}

geom_cylindrical_surface_t *
geom_cylindrical_surface_from_geometry(geom_geometry_t *t) {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_CylindricalSurface)) {
    return nullptr;
  }
  return new geom_cylindrical_surface_t{
      Handle(Geom_CylindricalSurface)::DownCast(t->handle)};
}

geom_plane_surface_t *geom_plane_surface_from_geometry(geom_geometry_t *t) {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_Plane)) {
    return nullptr;
  }
  return new geom_plane_surface_t{Handle(Geom_Plane)::DownCast(t->handle)};
}

geom_conical_surface_t *geom_conical_surface_from_geometry(geom_geometry_t *t) {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_ConicalSurface)) {
    return nullptr;
  }
  return new geom_conical_surface_t{
      Handle(Geom_ConicalSurface)::DownCast(t->handle)};
}

geom_spherical_surface_t *
geom_spherical_surface_from_geometry(geom_geometry_t *t) {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_SphericalSurface)) {
    return nullptr;
  }
  return new geom_spherical_surface_t{
      Handle(Geom_SphericalSurface)::DownCast(t->handle)};
}

geom_toroidal_surface_t *
geom_toroidal_surface_from_geometry(geom_geometry_t *t) {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_ToroidalSurface)) {
    return nullptr;
  }
  return new geom_toroidal_surface_t{
      Handle(Geom_ToroidalSurface)::DownCast(t->handle)};
}

geom_offset_surface_t *geom_offset_surface_from_geometry(geom_geometry_t *t) {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_OffsetSurface)) {
    return nullptr;
  }
  return new geom_offset_surface_t{
      Handle(Geom_OffsetSurface)::DownCast(t->handle)};
}

geom_swept_surface_t *geom_swept_surface_from_geometry(geom_geometry_t *t) {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_SweptSurface)) {
    return nullptr;
  }
  return new geom_swept_surface_t{
      Handle(Geom_SweptSurface)::DownCast(t->handle)};
}

geom_surface_of_linear_extrusion_t *
geom_surface_of_linear_extrusion_from_geometry(geom_geometry_t *t) {
  if (t->handle->DynamicType() !=
      STANDARD_TYPE(Geom_SurfaceOfLinearExtrusion)) {
    return nullptr;
  }
  return new geom_surface_of_linear_extrusion_t{
      Handle(Geom_SurfaceOfLinearExtrusion)::DownCast(t->handle)};
}

geom_surface_of_revolution_extrusion_t *
geom_surface_of_revolution_extrusion_from_geometry(geom_geometry_t *t) {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_SurfaceOfRevolution)) {
    return nullptr;
  }
  return new geom_surface_of_revolution_extrusion_t{
      Handle(Geom_SurfaceOfRevolution)::DownCast(t->handle)};
}

geom_plate_surface_t *geom_plate_surface_from_geometry(geom_geometry_t *t) {
  if (t->handle->DynamicType() != STANDARD_TYPE(GeomPlate_Surface)) {
    return nullptr;
  }
  return new geom_plate_surface_t{
      Handle(GeomPlate_Surface)::DownCast(t->handle)};
}

geom_vector_t *geom_vector_from_geometry(geom_geometry_t *t) {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_Vector)) {
    return nullptr;
  }
  return new geom_vector_t{Handle(Geom_Vector)::DownCast(t->handle)};
}

geom_direction_t *geom_direction_from_geometry(geom_geometry_t *t) {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_Direction)) {
    return nullptr;
  }
  return new geom_direction_t{Handle(Geom_Direction)::DownCast(t->handle)};
}

geom_vector_with_magnitude_t *
geom_vector_with_magnitude_from_geometry(geom_geometry_t *t) {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_VectorWithMagnitude)) {
    return nullptr;
  }
  return new geom_vector_with_magnitude_t{
      Handle(Geom_VectorWithMagnitude)::DownCast(t->handle)};
}

geom2d_axis_placement_t *
geom2d_axis_placement_from_geometry(geom2d_geometry_t *t) {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom2d_AxisPlacement)) {
    return nullptr;
  }
  return new geom2d_axis_placement_t{
      Handle(Geom2d_AxisPlacement)::DownCast(t->handle)};
}

geom2d_curve_t *geom2d_curve_from_geometry(geom2d_geometry_t *t) {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom2d_Curve)) {
    return nullptr;
  }
  return new geom2d_curve_t{Handle(Geom2d_Curve)::DownCast(t->handle)};
}

geom2d_bisector_curve_t *
geom2d_bisector_curve_from_geometry(geom2d_geometry_t *t) {
  if (t->handle->DynamicType() != STANDARD_TYPE(Bisector_Curve)) {
    return nullptr;
  }
  return new geom2d_bisector_curve_t{
      Handle(Bisector_Curve)::DownCast(t->handle)};
}

geom2d_bezier_bisec_ana_curve_t *
geom2d_bezier_bisec_ana_curve_from_geometry(geom2d_geometry_t *t) {
  if (t->handle->DynamicType() != STANDARD_TYPE(Bisector_BisecAna)) {
    return nullptr;
  }
  return new geom2d_bezier_bisec_ana_curve_t{
      Handle(Bisector_BisecAna)::DownCast(t->handle)};
}

geom2d_bezier_bisec_cc_curve_t *
geom2d_bezier_bisec_cc_curve_from_geometry(geom2d_geometry_t *t) {
  if (t->handle->DynamicType() != STANDARD_TYPE(Bisector_BisecCC)) {
    return nullptr;
  }
  return new geom2d_bezier_bisec_cc_curve_t{
      Handle(Bisector_BisecCC)::DownCast(t->handle)};
}

geom2d_bezier_bisec_pc_curve_t *
geom2d_bezier_bisec_pc_curve_from_geometry(geom2d_geometry_t *t) {
  if (t->handle->DynamicType() != STANDARD_TYPE(Bisector_BisecPC)) {
    return nullptr;
  }
  return new geom2d_bezier_bisec_pc_curve_t{
      Handle(Bisector_BisecPC)::DownCast(t->handle)};
}

geom2d_bounded_curve_t *
geom2d_bounded_curve_from_geometry(geom2d_geometry_t *t) {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom2d_BoundedCurve)) {
    return nullptr;
  }
  return new geom2d_bounded_curve_t{
      Handle(Geom2d_BoundedCurve)::DownCast(t->handle)};
}

geom2d_bezier_curve_t *geom2d_bezier_curve_from_geometry(geom2d_geometry_t *t) {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom2d_BezierCurve)) {
    return nullptr;
  }
  return new geom2d_bezier_curve_t{
      Handle(Geom2d_BezierCurve)::DownCast(t->handle)};
}

geom2d_bspline_curve_t *
geom2d_bspline_curve_from_geometry(geom2d_geometry_t *t) {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom2d_BSplineCurve)) {
    return nullptr;
  }
  return new geom2d_bspline_curve_t{
      Handle(Geom2d_BSplineCurve)::DownCast(t->handle)};
}

geom2d_trimmed_curve_t *
geom2d_trimmed_curve_from_geometry(geom2d_geometry_t *t) {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom2d_TrimmedCurve)) {
    return nullptr;
  }
  return new geom2d_trimmed_curve_t{
      Handle(Geom2d_TrimmedCurve)::DownCast(t->handle)};
}

geom2d_conic_t *geom2d_conic_from_geometry(geom2d_geometry_t *t) {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom2d_Conic)) {
    return nullptr;
  }
  return new geom2d_conic_t{Handle(Geom2d_Conic)::DownCast(t->handle)};
}

geom2d_circle_t *geom2d_circle_from_geometry(geom2d_geometry_t *t) {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom2d_Circle)) {
    return nullptr;
  }
  return new geom2d_circle_t{Handle(Geom2d_Circle)::DownCast(t->handle)};
}

geom2d_ellipse_t *geom2d_ellipse_from_geometry(geom2d_geometry_t *t) {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom2d_Ellipse)) {
    return nullptr;
  }
  return new geom2d_ellipse_t{Handle(Geom2d_Ellipse)::DownCast(t->handle)};
}

geom2d_hyperbola_t *geom2d_hyperbola_from_geometry(geom2d_geometry_t *t) {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom2d_Hyperbola)) {
    return nullptr;
  }
  return new geom2d_hyperbola_t{Handle(Geom2d_Hyperbola)::DownCast(t->handle)};
}

geom2d_parabola_t *geom2d_parabola_from_geometry(geom2d_geometry_t *t) {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom2d_Parabola)) {
    return nullptr;
  }
  return new geom2d_parabola_t{Handle(Geom2d_Parabola)::DownCast(t->handle)};
}

geom2d_line_t *geom2d_line_from_geometry(geom2d_geometry_t *t) {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom2d_Line)) {
    return nullptr;
  }
  return new geom2d_line_t{Handle(Geom2d_Line)::DownCast(t->handle)};
}

geom2d_offset_curve_t *geom2d_offset_curve_from_geometry(geom2d_geometry_t *t) {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom2d_OffsetCurve)) {
    return nullptr;
  }
  return new geom2d_offset_curve_t{
      Handle(Geom2d_OffsetCurve)::DownCast(t->handle)};
}

geom2d_point_t *geom2d_point_from_geometry(geom2d_geometry_t *t) {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom2d_Point)) {
    return nullptr;
  }
  return new geom2d_point_t{Handle(Geom2d_Point)::DownCast(t->handle)};
}

geom2d_cartesian_point_t *
geom2d_cartesian_point_from_geometry(geom2d_geometry_t *t) {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom2d_CartesianPoint)) {
    return nullptr;
  }
  return new geom2d_cartesian_point_t{
      Handle(Geom2d_CartesianPoint)::DownCast(t->handle)};
}

geom2d_vector_t *geom2d_vector_from_geometry(geom2d_geometry_t *t) {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom2d_Vector)) {
    return nullptr;
  }
  return new geom2d_vector_t{Handle(Geom2d_Vector)::DownCast(t->handle)};
}

geom2d_direction_t *geom2d_direction_from_geometry(geom2d_geometry_t *t) {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom2d_Direction)) {
    return nullptr;
  }
  return new geom2d_direction_t{Handle(Geom2d_Direction)::DownCast(t->handle)};
}

geom2d_vector_with_magnitude_t *
geom2d_vector_with_magnitude_from_geometry(geom2d_geometry_t *t) {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom2d_VectorWithMagnitude)) {
    return nullptr;
  }
  return new geom2d_vector_with_magnitude_t{
    .handle =Handle(Geom2d_VectorWithMagnitude)::DownCast(t->handle)};
}

geom_curve_t *geom_bounded_curve_to_geom_curve(geom_bounded_curve_t *t) {
  return new geom_curve_t{.handle =Handle(Geom_Curve)::DownCast(t->handle)};
}

geom_curve_t *geom_bezier_curve_to_geom_curve(geom_bezier_curve_t *t) {
  return new geom_curve_t{.handle =Handle(Geom_Curve)::DownCast(t->handle)};
}

geom_curve_t *geom_bspline_curve_to_geom_curve(geom_bspline_curve_t *t) {
  return new geom_curve_t{.handle =Handle(Geom_Curve)::DownCast(t->handle)};
}

geom_curve_t *geom_trimmed_curve_to_geom_curve(geom_trimmed_curve_t *t) {
  return new geom_curve_t{.handle =Handle(Geom_Curve)::DownCast(t->handle)};
}

geom_curve_t *geom_conic_to_geom_curve(geom_conic_t *t) {
  return new geom_curve_t{.handle =Handle(Geom_Curve)::DownCast(t->handle)};
}

geom_curve_t *geom_circle_to_geom_curve(geom_circle_t *t) {
  return new geom_curve_t{.handle =Handle(Geom_Curve)::DownCast(t->handle)};
}

geom_curve_t *geom_ellipse_to_geom_curve(geom_ellipse_t *t) {
  return new geom_curve_t{.handle =Handle(Geom_Curve)::DownCast(t->handle)};
}

geom_curve_t *geom_hyperbola_to_geom_curve(geom_hyperbola_t *t) {
  return new geom_curve_t{Handle(Geom_Curve)::DownCast(t->handle)};
}

geom_curve_t *geom_parabola_to_geom_curve(geom_parabola_t *t) {
  return new geom_curve_t{.handle =Handle(Geom_Curve)::DownCast(t->handle)};
}

geom_curve_t *geom_line_to_geom_curve(geom_line_t *t) {
  return new geom_curve_t{.handle =Handle(Geom_Curve)::DownCast(t->handle)};
}

geom_curve_t *geom_offset_curve_to_geom_curve(geom_offset_curve_t *t) {
  return new geom_curve_t{.handle =Handle(Geom_Curve)::DownCast(t->handle)};
}

geom_surface_t *
geom_bounded_surface_to_geom_surface(geom_bounded_surface_t *t) {
  return new geom_surface_t{Handle(Geom_Surface)::DownCast(t->handle)};
}

geom_surface_t *geom_bezier_surface_to_geom_surface(geom_bezier_surface_t *t) {
  return new geom_surface_t{Handle(Geom_Surface)::DownCast(t->handle)};
}

geom_surface_t *
geom_bspline_surface_to_geom_surface(geom_bspline_surface_t *t) {
  return new geom_surface_t{Handle(Geom_Surface)::DownCast(t->handle)};
}

geom_surface_t *geom_rectangular_trimmed_surface_to_geom_surface(
    geom_rectangular_trimmed_surface_t *t) {
  return new geom_surface_t{Handle(Geom_Surface)::DownCast(t->handle)};
}

geom_surface_t *
geom_elementary_surface_to_geom_surface(geom_elementary_surface_t *t) {
  return new geom_surface_t{Handle(Geom_Surface)::DownCast(t->handle)};
}

geom_surface_t *
geom_cylindrical_surface_to_geom_surface(geom_cylindrical_surface_t *t) {
  return new geom_surface_t{Handle(Geom_Surface)::DownCast(t->handle)};
}

geom_surface_t *geom_plane_surface_to_geom_surface(geom_plane_surface_t *t) {
  return new geom_surface_t{Handle(Geom_Surface)::DownCast(t->handle)};
}

geom_surface_t *
geom_conical_surface_to_geom_surface(geom_conical_surface_t *t) {
  return new geom_surface_t{Handle(Geom_Surface)::DownCast(t->handle)};
}

geom_surface_t *
geom_spherical_surface_to_geom_surface(geom_spherical_surface_t *t) {
  return new geom_surface_t{Handle(Geom_Surface)::DownCast(t->handle)};
}

geom_surface_t *
geom_toroidal_surface_to_geom_surface(geom_toroidal_surface_t *t) {
  return new geom_surface_t{Handle(Geom_Surface)::DownCast(t->handle)};
}

geom_surface_t *geom_offset_surface_to_geom_surface(geom_offset_surface_t *t) {
  return new geom_surface_t{Handle(Geom_Surface)::DownCast(t->handle)};
}

geom_surface_t *geom_swept_surface_to_geom_surface(geom_swept_surface_t *t) {
  return new geom_surface_t{Handle(Geom_Surface)::DownCast(t->handle)};
}

geom_surface_t *geom_surface_of_linear_extrusion_to_geom_surface(
    geom_surface_of_linear_extrusion_t *t) {
  return new geom_surface_t{Handle(Geom_Surface)::DownCast(t->handle)};
}

geom_surface_t *geom_surface_of_revolution_extrusion_to_geom_surface(
    geom_surface_of_revolution_extrusion_t *t) {
  return new geom_surface_t{Handle(Geom_Surface)::DownCast(t->handle)};
}

geom_surface_t *geom_plate_surface_to_geom_surface(geom_plate_surface_t *t) {
  return new geom_surface_t{Handle(Geom_Surface)::DownCast(t->handle)};
}

geom2d_curve_t *
geom2d_bisector_curve_to_geom2d_curve(geom2d_bisector_curve_t *t) {
  return new geom2d_curve_t{Handle(Geom2d_Curve)::DownCast(t->handle)};
}

geom2d_curve_t *geom2d_bezier_bisec_ana_curve_to_geom2d_curve(
    geom2d_bezier_bisec_ana_curve_t *t) {
  return new geom2d_curve_t{Handle(Geom2d_Curve)::DownCast(t->handle)};
}

geom2d_curve_t *geom2d_bezier_bisec_cc_curve_to_geom2d_curve(
    geom2d_bezier_bisec_cc_curve_t *t) {
  return new geom2d_curve_t{Handle(Geom2d_Curve)::DownCast(t->handle)};
}

geom2d_curve_t *geom2d_bezier_bisec_pc_curve_to_geom2d_curve(
    geom2d_bezier_bisec_pc_curve_t *t) {
  return new geom2d_curve_t{Handle(Geom2d_Curve)::DownCast(t->handle)};
}

geom2d_curve_t *
geom2d_bounded_curve_to_geom2d_curve(geom2d_bounded_curve_t *t) {
  return new geom2d_curve_t{Handle(Geom2d_Curve)::DownCast(t->handle)};
}

geom2d_curve_t *geom2d_bezier_curve_to_geom2d_curve(geom2d_bezier_curve_t *t) {
  return new geom2d_curve_t{Handle(Geom2d_Curve)::DownCast(t->handle)};
}

geom2d_curve_t *
geom2d_bspline_curve_to_geom2d_curve(geom2d_bspline_curve_t *t) {
  return new geom2d_curve_t{Handle(Geom2d_Curve)::DownCast(t->handle)};
}

geom2d_curve_t *
geom2d_trimmed_curve_to_geom2d_curve(geom2d_trimmed_curve_t *t) {
  return new geom2d_curve_t{Handle(Geom2d_Curve)::DownCast(t->handle)};
}

geom2d_curve_t *geom2d_conic_to_geom2d_curve(geom2d_conic_t *t) {
  return new geom2d_curve_t{Handle(Geom2d_Curve)::DownCast(t->handle)};
}

geom2d_curve_t *geom2d_circle_to_geom2d_curve(geom2d_circle_t *t) {
  return new geom2d_curve_t{Handle(Geom2d_Curve)::DownCast(t->handle)};
}

geom2d_curve_t *geom2d_ellipse_to_geom2d_curve(geom2d_ellipse_t *t) {
  return new geom2d_curve_t{Handle(Geom2d_Curve)::DownCast(t->handle)};
}

geom2d_curve_t *geom2d_hyperbola_to_geom2d_curve(geom2d_hyperbola_t *t) {
  return new geom2d_curve_t{Handle(Geom2d_Curve)::DownCast(t->handle)};
}

geom2d_curve_t *geom2d_parabola_to_geom2d_curve(geom2d_parabola_t *t) {
  return new geom2d_curve_t{Handle(Geom2d_Curve)::DownCast(t->handle)};
}

geom2d_curve_t *geom2d_line_to_geom2d_curve(geom2d_line_t *t) {
  return new geom2d_curve_t{Handle(Geom2d_Curve)::DownCast(t->handle)};
}

geom2d_curve_t *geom2d_offset_curve_to_geom2d_curve(geom2d_offset_curve_t *t) {
  return new geom2d_curve_t{Handle(Geom2d_Curve)::DownCast(t->handle)};
}

void geom_apply_mirror_with_point(geom_geometry_t *t, pnt3d_t P) {
  if (t) {
    t->handle->Mirror(cast_to_gp(P));
  }
}

void geom_apply_mirror_with_axis1(geom_geometry_t *t, axis1_t A1) {
  if (t) {
    t->handle->Mirror(cast_to_gp(A1));
  }
}

void geom_apply_mirror_with_axis2(geom_geometry_t *t, axis2_t A2) {
  if (t) {
    t->handle->Mirror(cast_to_gp(A2));
  }
}

void geom_apply_rotate(geom_geometry_t *t, axis1_t A1, double Ang) {
  if (t) {
    t->handle->Rotate(cast_to_gp(A1), Ang);
  }
}

void geom_apply_scale(geom_geometry_t *t, pnt3d_t P, double S) {
  if (t) {
    t->handle->Scale(cast_to_gp(P), S);
  }
}

void geom_apply_translate_with_vector(geom_geometry_t *t, vec3d_t V) {
  if (t) {
    t->handle->Translate(cast_to_gp(V));
  }
}

void geom_apply_translate_with_point(geom_geometry_t *t, pnt3d_t P1,
                                     pnt3d_t P2) {
  if (t) {
    t->handle->Translate(cast_to_gp(P1), cast_to_gp(P2));
  }
}

void geom_apply_transform(geom_geometry_t *t, trsf_t tr) {
  if (t) {
    t->handle->Transform(cast_to_gp(tr));
  }
}

geom_geometry_t *geom_mirror_with_point(geom_geometry_t *t, pnt3d_t P) {
  if (t) {
    return new geom_geometry_t{t->handle->Mirrored(cast_to_gp(P))};
  }
  return nullptr;
}

geom_geometry_t *geom_mirror_with_axis1(geom_geometry_t *t, axis1_t A1) {
  if (t) {
    return new geom_geometry_t{t->handle->Mirrored(cast_to_gp(A1))};
  }
  return nullptr;
}

geom_geometry_t *geom_mirror_with_axis2(geom_geometry_t *t, axis2_t A2) {
  if (t) {
    return new geom_geometry_t{t->handle->Mirrored(cast_to_gp(A2))};
  }
  return nullptr;
}

geom_geometry_t *geom_rotate(geom_geometry_t *t, axis1_t A1, double Ang) {
  if (t) {
    return new geom_geometry_t{t->handle->Rotated(cast_to_gp(A1), Ang)};
  }
  return nullptr;
}

geom_geometry_t *geom_scale(geom_geometry_t *t, pnt3d_t P, double S) {
  if (t) {
    return new geom_geometry_t{t->handle->Scaled(cast_to_gp(P), S)};
  }
  return nullptr;
}

geom_geometry_t *geom_translate_with_vector(geom_geometry_t *t, vec3d_t V) {
  if (t) {
    return new geom_geometry_t{t->handle->Translated(cast_to_gp(V))};
  }
  return nullptr;
}

geom_geometry_t *geom_translate_with_point(geom_geometry_t *t, pnt3d_t P1,
                                           pnt3d_t P2) {
  if (t) {
    return new geom_geometry_t{
        t->handle->Translated(cast_to_gp(P1), cast_to_gp(P2))};
  }
  return nullptr;
}

geom_geometry_t *geom_transform(geom_geometry_t *t, trsf_t tr) {
  if (t) {
    return new geom_geometry_t{t->handle->Transformed(cast_to_gp(tr))};
  }
  return nullptr;
}

void geom2d_apply_mirror_with_point(geom2d_geometry_t *t, pnt2d_t P) {
  if (t) {
    t->handle->Mirror(cast_to_gp(P));
  }
}

void geom2d_apply_mirror_with_axis2(geom2d_geometry_t *t, axis2d_t A2) {
  if (t) {
    t->handle->Mirror(cast_to_gp(A2));
  }
}

void geom2d_apply_rotate(geom2d_geometry_t *t, pnt2d_t P, double Ang) {
  if (t) {
    t->handle->Rotate(cast_to_gp(P), Ang);
  }
}

void geom2d_apply_scale(geom2d_geometry_t *t, pnt2d_t P, double S) {
  if (t) {
    t->handle->Scale(cast_to_gp(P), S);
  }
}

void geom2d_apply_translate_with_vector(geom2d_geometry_t *t, vec2d_t V) {
  if (t) {
    t->handle->Translate(cast_to_gp(V));
  }
}

void geom2d_apply_translate_with_point(geom2d_geometry_t *t, pnt2d_t P1,
                                       pnt2d_t P2) {
  if (t) {
    t->handle->Translate(cast_to_gp(P1), cast_to_gp(P2));
  }
}

void geom2d_apply_transform(geom2d_geometry_t *t, trsf2d_t tr) {
  if (t) {
    t->handle->Transform(cast_to_gp(tr));
  }
}

geom2d_geometry_t *geom2d_mirror_with_point(geom2d_geometry_t *t, pnt2d_t P) {
  if (t) {
    return new geom2d_geometry_t{t->handle->Mirrored(cast_to_gp(P))};
  }
  return nullptr;
}

geom2d_geometry_t *geom2d_mirror_with_axis2(geom2d_geometry_t *t, axis2d_t A2) {
  if (t) {
    return new geom2d_geometry_t{t->handle->Mirrored(cast_to_gp(A2))};
  }
  return nullptr;
}

geom2d_geometry_t *geom2d_rotate(geom2d_geometry_t *t, pnt2d_t P, double Ang) {
  if (t) {
    return new geom2d_geometry_t{t->handle->Rotated(cast_to_gp(P), Ang)};
  }
  return nullptr;
}

geom2d_geometry_t *geom2d_scale(geom2d_geometry_t *t, pnt2d_t P, double S) {
  if (t) {
    return new geom2d_geometry_t{t->handle->Scaled(cast_to_gp(P), S)};
  }
  return nullptr;
}

geom2d_geometry_t *geom2d_translate_with_vector(geom2d_geometry_t *t,
                                                vec2d_t V) {
  if (t) {
    return new geom2d_geometry_t{t->handle->Translated(cast_to_gp(V))};
  }
  return nullptr;
}

geom2d_geometry_t *geom2d_translate_with_point(geom2d_geometry_t *t, pnt2d_t P1,
                                               pnt2d_t P2) {
  if (t) {
    return new geom2d_geometry_t{
        t->handle->Translated(cast_to_gp(P1), cast_to_gp(P2))};
  }
  return nullptr;
}

geom2d_geometry_t *geom2d_transform(geom2d_geometry_t *t, trsf2d_t tr) {
  if (t) {
    return new geom2d_geometry_t{t->handle->Transformed(cast_to_gp(tr))};
  }
  return nullptr;
}

int geom_geometry_type(geom_geometry_t *t) {
  if (t->handle->DynamicType() == STANDARD_TYPE(Geom_Axis1Placement)) {
    return GeomAxis1Placement;
  } else if (t->handle->DynamicType() == STANDARD_TYPE(Geom_Axis2Placement)) {
    return GeomAxis2Placement;
  } else if (t->handle->DynamicType() == STANDARD_TYPE(Geom_BezierCurve)) {
    return GeomBezierCurve;
  } else if (t->handle->DynamicType() == STANDARD_TYPE(Geom_BSplineCurve)) {
    return GeomBSplineCurve;
  } else if (t->handle->DynamicType() == STANDARD_TYPE(Geom_TrimmedCurve)) {
    return GeomTrimmedCurve;
  } else if (t->handle->DynamicType() == STANDARD_TYPE(Geom_Line)) {
    return GeomLine;
  } else if (t->handle->DynamicType() == STANDARD_TYPE(Geom_OffsetCurve)) {
    return GeomOffsetCurve;
  } else if (t->handle->DynamicType() == STANDARD_TYPE(Geom_Circle)) {
    return GeomCircle;
  } else if (t->handle->DynamicType() == STANDARD_TYPE(Geom_Ellipse)) {
    return GeomEllipse;
  } else if (t->handle->DynamicType() == STANDARD_TYPE(Geom_Hyperbola)) {
    return GeomHyperbola;
  } else if (t->handle->DynamicType() == STANDARD_TYPE(Geom_Parabola)) {
    return GeomParabola;
  } else if (t->handle->DynamicType() == STANDARD_TYPE(Geom_BezierSurface)) {
    return GeomBezierSurface;
  } else if (t->handle->DynamicType() == STANDARD_TYPE(Geom_BSplineSurface)) {
    return GeomBSplineSurface;
  } else if (t->handle->DynamicType() ==
             STANDARD_TYPE(Geom_RectangularTrimmedSurface)) {
    return GeomRectangularTrimmedSurface;
  } else if (t->handle->DynamicType() == STANDARD_TYPE(Geom_ConicalSurface)) {
    return GeomConicalSurface;
  } else if (t->handle->DynamicType() ==
             STANDARD_TYPE(Geom_CylindricalSurface)) {
    return GeomCylindricalSurface;
  } else if (t->handle->DynamicType() == STANDARD_TYPE(Geom_Plane)) {
    return GeomPlane;
  } else if (t->handle->DynamicType() == STANDARD_TYPE(Geom_SphericalSurface)) {
    return GeomSphericalSurface;
  } else if (t->handle->DynamicType() == STANDARD_TYPE(Geom_ToroidalSurface)) {
    return GeomToroidalSurface;
  } else if (t->handle->DynamicType() ==
             STANDARD_TYPE(Geom_ElementarySurface)) {
    return GeomElementarySurface;
  } else if (t->handle->DynamicType() == STANDARD_TYPE(Geom_OffsetSurface)) {
    return GeomOffsetSurface;
  } else if (t->handle->DynamicType() ==
             STANDARD_TYPE(Geom_SurfaceOfLinearExtrusion)) {
    return GeomSurfaceOfLinearExtrusion;
  } else if (t->handle->DynamicType() ==
             STANDARD_TYPE(Geom_SurfaceOfRevolution)) {
    return GeomSurfaceOfRevolution;
  } else if (t->handle->DynamicType() == STANDARD_TYPE(Geom_SweptSurface)) {
    return GeomSweptSurface;
  } else if (t->handle->DynamicType() == STANDARD_TYPE(GeomPlate_Surface)) {
    return GeomPlateSurface;
  } else if (t->handle->DynamicType() == STANDARD_TYPE(Geom_CartesianPoint)) {
    return GeomCartesianPoint;
  } else if (t->handle->DynamicType() == STANDARD_TYPE(Geom_Direction)) {
    return GeomDirection;
  } else if (t->handle->DynamicType() ==
             STANDARD_TYPE(Geom_VectorWithMagnitude)) {
    return GeomVectorWithMagnitude;
  }
  return -1;
}

int geom2d_geometry_type(geom2d_geometry_t *t) {
  if (t->handle->DynamicType() == STANDARD_TYPE(Geom2d_AxisPlacement)) {
    return Geom2dAxisPlacement;
  } else if (t->handle->DynamicType() == STANDARD_TYPE(Bisector_BisecAna)) {
    return Geom2dBisectorBisecAna;
  } else if (t->handle->DynamicType() == STANDARD_TYPE(Bisector_BisecCC)) {
    return Geom2dBisectorBisecCC;
  } else if (t->handle->DynamicType() == STANDARD_TYPE(Bisector_BisecPC)) {
    return Geom2dBisectorBisecPC;
  } else if (t->handle->DynamicType() == STANDARD_TYPE(Geom2d_BezierCurve)) {
    return Geom2dBezierCurve;
  } else if (t->handle->DynamicType() == STANDARD_TYPE(Bisector_Curve)) {
    return Geom2dBisectorCurve;
  } else if (t->handle->DynamicType() == STANDARD_TYPE(Geom2d_BSplineCurve)) {
    return Geom2dBSplineCurve;
  } else if (t->handle->DynamicType() == STANDARD_TYPE(Geom2d_TrimmedCurve)) {
    return Geom2dTrimmedCurve;
  } else if (t->handle->DynamicType() == STANDARD_TYPE(Geom2d_Circle)) {
    return Geom2dCircle;
  } else if (t->handle->DynamicType() == STANDARD_TYPE(Geom2d_Ellipse)) {
    return Geom2dEllipse;
  } else if (t->handle->DynamicType() == STANDARD_TYPE(Geom2d_Hyperbola)) {
    return Geom2dHyperbola;
  } else if (t->handle->DynamicType() == STANDARD_TYPE(Geom2d_Parabola)) {
    return Geom2dParabola;
  } else if (t->handle->DynamicType() == STANDARD_TYPE(Geom2d_Conic)) {
    return Geom2dConic;
  } else if (t->handle->DynamicType() == STANDARD_TYPE(Geom2d_Line)) {
    return Geom2dLine;
  } else if (t->handle->DynamicType() == STANDARD_TYPE(Geom2d_Direction)) {
    return Geom2dDirection;
  } else if (t->handle->DynamicType() == STANDARD_TYPE(Geom2d_OffsetCurve)) {
    return Geom2dOffsetCurve;
  } else if (t->handle->DynamicType() == STANDARD_TYPE(Geom2d_CartesianPoint)) {
    return Geom2dCartesianPoint;
  } else if (t->handle->DynamicType() ==
             STANDARD_TYPE(Geom2d_VectorWithMagnitude)) {
    return Geom2dVectorWithMagnitude;
  }
  return -1;
}

geom_axis1_placement_t *geom_make_axis1_placement(axis1_t A1) {
  return new geom_axis1_placement_t{new Geom_Axis1Placement(cast_to_gp(A1))};
}

geom_axis1_placement_t *geom_make_axis1_placement_of_point_dir(pnt3d_t P,
                                                               dir3d_t V) {
  return new geom_axis1_placement_t{
      new Geom_Axis1Placement(cast_to_gp(P), cast_to_gp(V))};
}

geom_axis2_placement_t *geom_make_axis2_placement(axis2_t A2) {
  return new geom_axis2_placement_t{new Geom_Axis2Placement(cast_to_gp(A2))};
}

geom_axis2_placement_t *
geom_make_axis2_placement_of_point_nvx(pnt3d_t P, dir3d_t N, dir3d_t VX) {
  return new geom_axis2_placement_t{
      new Geom_Axis2Placement(cast_to_gp(P), cast_to_gp(N), cast_to_gp(VX))};
}

geom_bezier_curve_t *geom_make_bezier_curve(pnt3d_t *CurvePoles, int count) {
  TColgp_Array1OfPnt pnts{0, static_cast<Standard_Integer>(count)};
  for (int i = 0; i < count; i++) {
    pnts.SetValue(i, cast_to_gp(CurvePoles[i]));
  }
  return new geom_bezier_curve_t{new Geom_BezierCurve(pnts)};
}

geom_bezier_curve_t *geom_make_bezier_curve_from_weight(pnt3d_t *CurvePoles,
                                                        double *PoleWeights,
                                                        int count) {
  TColgp_Array1OfPnt pnts{0, static_cast<Standard_Integer>(count)};
  TColStd_Array1OfReal wei{0, static_cast<Standard_Integer>(count)};
  for (int i = 0; i < count; i++) {
    pnts.SetValue(i, cast_to_gp(CurvePoles[i]));
    wei.SetValue(i, PoleWeights[i]);
  }
  return new geom_bezier_curve_t{new Geom_BezierCurve(pnts, wei)};
}

geom_bspline_curve_t *geom_make_bspline_curve(pnt3d_t *Poles, double *Knots,
                                              int *Multiplicities, int count,
                                              int Degree, _Bool Periodic) {
  TColgp_Array1OfPnt pnts{0, static_cast<Standard_Integer>(count)};
  TColStd_Array1OfReal kntss{0, static_cast<Standard_Integer>(count)};
  TColStd_Array1OfInteger mu{0, static_cast<Standard_Integer>(count)};
  for (int i = 0; i < count; i++) {
    pnts.SetValue(i, cast_to_gp(Poles[i]));
    kntss.SetValue(i, Knots[i]);
    mu.SetValue(i, Multiplicities[i]);
  }
  return new geom_bspline_curve_t{
      new Geom_BSplineCurve(pnts, kntss, mu, Degree, Periodic)};
}

geom_bspline_curve_t *geom_make_bspline_curve_from_weight(
    pnt3d_t *Poles, double *Weights, double *Knots, int *Multiplicities,
    int count, int Degree, _Bool Periodic, _Bool CheckRational) {
  TColgp_Array1OfPnt pnts{0, static_cast<Standard_Integer>(count)};
  TColStd_Array1OfReal wei{0, static_cast<Standard_Integer>(count)};
  TColStd_Array1OfReal kntss{0, static_cast<Standard_Integer>(count)};
  TColStd_Array1OfInteger mu{0, static_cast<Standard_Integer>(count)};
  for (int i = 0; i < count; i++) {
    pnts.SetValue(i, cast_to_gp(Poles[i]));
    wei.SetValue(i, Weights[i]);
    kntss.SetValue(i, Knots[i]);
    mu.SetValue(i, Multiplicities[i]);
  }
  return new geom_bspline_curve_t{new Geom_BSplineCurve(
      pnts, wei, kntss, mu, Degree, Periodic, CheckRational)};
}

geom_bezier_surface_t *geom_make_bezier_surface(pnt3d_t *SurfacePoles, int row,
                                                int col) {
  TColgp_Array2OfPnt pnt{0, static_cast<Standard_Integer>(col), 0,
                         static_cast<Standard_Integer>(row)};
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      pnt.SetValue(i, j, cast_to_gp(SurfacePoles[i * col + j]));
    }
  }
  return new geom_bezier_surface_t{new Geom_BezierSurface(pnt)};
}

geom_bezier_surface_t *
geom_make_bezier_surface_from_weight(pnt3d_t *SurfacePoles, double *PoleWeights,
                                     int row, int col) {
  TColgp_Array2OfPnt pnt{0, static_cast<Standard_Integer>(col), 0,
                         static_cast<Standard_Integer>(row)};
  TColStd_Array2OfReal wei{0, static_cast<Standard_Integer>(col), 0,
                           static_cast<Standard_Integer>(row)};
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      pnt.SetValue(i, j, cast_to_gp(SurfacePoles[i * col + j]));
      wei.SetValue(i, j, PoleWeights[i * col + j]);
    }
  }
  return new geom_bezier_surface_t{new Geom_BezierSurface(pnt, wei)};
}

geom_bspline_surface_t *
geom_make_bspline_surface(pnt3d_t *Poles, double *UKnots, double *VKnots,
                          int *UMults, int *VMults, int row, int col,
                          int UCount, int VCount, int UDegree, int VDegree,
                          _Bool UPeriodic, _Bool VPeriodic) {
  TColgp_Array2OfPnt pnt{0, static_cast<Standard_Integer>(col), 0,
                         static_cast<Standard_Integer>(row)};
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      pnt.SetValue(i, j, cast_to_gp(Poles[i * col + j]));
    }
  }
  TColStd_Array1OfInteger umus{0, static_cast<Standard_Integer>(UCount)};
  TColStd_Array1OfReal ukets{0, static_cast<Standard_Integer>(UCount)};
  for (int i = 0; i < UCount; i++) {
    ukets.SetValue(i, UKnots[i]);
    umus.SetValue(i, UMults[i]);
  }
  TColStd_Array1OfReal vkets{0, static_cast<Standard_Integer>(VCount)};
  TColStd_Array1OfInteger vmus{0, static_cast<Standard_Integer>(VCount)};
  for (int i = 0; i < VCount; i++) {
    vmus.SetValue(i, VMults[i]);
    vkets.SetValue(i, VKnots[i]);
  }
  return new geom_bspline_surface_t{new Geom_BSplineSurface(
      pnt, ukets, vkets, umus, vmus, UDegree, VDegree, UPeriodic, VPeriodic)};
}

geom_bspline_surface_t *geom_make_bspline_surface_from_weight(
    pnt3d_t *Poles, double *Weights, double *UKnots, double *VKnots,
    int *UMults, int *VMults, int row, int col, int UCount, int VCount,
    int UDegree, int VDegree, _Bool UPeriodic, _Bool VPeriodic) {
  TColgp_Array2OfPnt pnt{0, static_cast<Standard_Integer>(col), 0,
                         static_cast<Standard_Integer>(row)};
  TColStd_Array2OfReal wei{0, static_cast<Standard_Integer>(col), 0,
                           static_cast<Standard_Integer>(row)};
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      pnt.SetValue(i, j, cast_to_gp(Poles[i * col + j]));
      wei.SetValue(i, j, Weights[i * col + j]);
    }
  }
  TColStd_Array1OfInteger umus{0, static_cast<Standard_Integer>(UCount)};
  TColStd_Array1OfReal ukets{0, static_cast<Standard_Integer>(UCount)};
  for (int i = 0; i < UCount; i++) {
    ukets.SetValue(i, UKnots[i]);
    umus.SetValue(i, UMults[i]);
  }
  TColStd_Array1OfReal vkets{0, static_cast<Standard_Integer>(VCount)};
  TColStd_Array1OfInteger vmus{0, static_cast<Standard_Integer>(VCount)};
  for (int i = 0; i < VCount; i++) {
    vmus.SetValue(i, VMults[i]);
    vkets.SetValue(i, VKnots[i]);
  }
  return new geom_bspline_surface_t{
      new Geom_BSplineSurface(pnt, wei, ukets, vkets, umus, vmus, UDegree,
                              VDegree, UPeriodic, VPeriodic)};
}

geom_rectangular_trimmed_surface_t *
geom_make_rectangular_trimmed_surface_from_lrud(geom_surface_t *S, double U1,
                                                double U2, double V1, double V2,
                                                _Bool USense, _Bool VSense) {

  return new geom_rectangular_trimmed_surface_t{
      new Geom_RectangularTrimmedSurface(S->handle, U1, U2, V1, V2, USense,
                                         VSense)};
}

geom_rectangular_trimmed_surface_t *
geom_make_rectangular_trimmed_surface(geom_surface_t *S, double Param1,
                                      double Param2, _Bool UTrim, _Bool Sense) {
  return new geom_rectangular_trimmed_surface_t{
      new Geom_RectangularTrimmedSurface(S->handle, Param1, Param2, UTrim,
                                         Sense)};
}

geom_surface_of_linear_extrusion_t *
geom_make_surface_of_linear_extrusion(geom_curve_t *C, dir3d_t V) {
  return new geom_surface_of_linear_extrusion_t{
      new Geom_SurfaceOfLinearExtrusion(C->handle, cast_to_gp(V))};
}

geom_surface_of_revolution_extrusion_t *
geom_make_surface_of_revolution_extrusion(geom_curve_t *C, axis1_t V) {
  return new geom_surface_of_revolution_extrusion_t{
      new Geom_SurfaceOfRevolution(C->handle, cast_to_gp(V))};
}

geom_direction_t *geom_make_direction(double X, double Y, double Z) {
  return new geom_direction_t{new Geom_Direction(X, Y, Z)};
}

geom_direction_t *geom_make_direction_with_dir(dir3d_t V) {
  return new geom_direction_t{new Geom_Direction(cast_to_gp(V))};
}

geom_vector_with_magnitude_t *
geom_make_vector_with_magnitude_with_vector(vec3d_t V) {
  return new geom_vector_with_magnitude_t{
      new Geom_VectorWithMagnitude(cast_to_gp(V))};
}

geom_vector_with_magnitude_t *
geom_make_vector_with_magnitude_with_xyz(double X, double Y, double Z) {
  return new geom_vector_with_magnitude_t{
      new Geom_VectorWithMagnitude(X, Y, Z)};
}

geom_vector_with_magnitude_t *
geom_make_vector_with_magnitude_with_point(pnt3d_t P1, pnt3d_t P2) {
  return new geom_vector_with_magnitude_t{
      new Geom_VectorWithMagnitude(cast_to_gp(P1), cast_to_gp(P2))};
}

geom_plate_surface_t *geom_make_plate_surface(geom_surface_t *Surfinit,
                                              plate_plate_t *Surfinter) {
  return new geom_plate_surface_t{
      new GeomPlate_Surface(Surfinit->handle, Surfinter->pp)};
}

geom2d_axis_placement_t *geom2d_make_axis_placement(axis2d_t A) {
  return new geom2d_axis_placement_t{new Geom2d_AxisPlacement(cast_to_gp(A))};
}

geom2d_axis_placement_t *geom2d_make_axis_placement_from_point(pnt2d_t P,
                                                               dir2d_t V) {
  return new geom2d_axis_placement_t{
      new Geom2d_AxisPlacement(cast_to_gp(P), cast_to_gp(V))};
}

geom2d_bezier_bisec_cc_curve_t *
geom2d_make_bezier_bisec_cc_curve(geom2d_curve_t *Cu1, geom2d_curve_t *Cu2,
                                  double Side1, double Side2, pnt2d_t Origin,
                                  double DistMax) {
  return new geom2d_bezier_bisec_cc_curve_t{new Bisector_BisecCC(
      Cu1->handle, Cu2->handle, Side1, Side2, cast_to_gp(Origin), DistMax)};
}

geom2d_bezier_bisec_pc_curve_t *
geom2d_make_bezier_bisec_pc_curve_with_dist(geom2d_curve_t *Cu, pnt2d_t P,
                                            double Side, double DistMax) {
  return new geom2d_bezier_bisec_pc_curve_t{
      new Bisector_BisecPC(Cu->handle, cast_to_gp(P), Side, DistMax)};
}

geom2d_bezier_bisec_pc_curve_t *
geom2d_make_bezier_bisec_pc_curve(geom2d_curve_t *Cu, pnt2d_t P, double Side,
                                  double UMin, double UMax) {
  return new geom2d_bezier_bisec_pc_curve_t{
      new Bisector_BisecPC(Cu->handle, cast_to_gp(P), Side, UMin, UMax)};
}

geom2d_bezier_curve_t *geom2d_make_bezier_curve(pnt2d_t *CurvePoles,
                                                int count) {
  TColgp_Array1OfPnt2d pnts{0, static_cast<Standard_Integer>(count)};
  for (int i = 0; i < count; i++) {
    pnts.SetValue(i, cast_to_gp(CurvePoles[i]));
  }
  return new geom2d_bezier_curve_t{new Geom2d_BezierCurve(pnts)};
}

geom2d_bezier_curve_t *geom2d_make_bezier_curve_with_weight(pnt2d_t *CurvePoles,
                                                            double *PoleWeights,
                                                            int count) {
  TColgp_Array1OfPnt2d pnts{0, static_cast<Standard_Integer>(count)};
  TColStd_Array1OfReal wei{0, static_cast<Standard_Integer>(count)};
  for (int i = 0; i < count; i++) {
    pnts.SetValue(i, cast_to_gp(CurvePoles[i]));
    wei.SetValue(i, PoleWeights[i]);
  }
  return new geom2d_bezier_curve_t{new Geom2d_BezierCurve(pnts, wei)};
}

geom2d_bspline_curve_t *geom2d_make_bspline_curve(pnt2d_t *Poles, double *Knots,
                                                  int *Multiplicities,
                                                  int Count, int Degree,
                                                  _Bool Periodic) {
  TColgp_Array1OfPnt2d pnts{0, static_cast<Standard_Integer>(Count)};
  TColStd_Array1OfReal kents{0, static_cast<Standard_Integer>(Count)};
  TColStd_Array1OfInteger mus{0, static_cast<Standard_Integer>(Count)};
  for (int i = 0; i < Count; i++) {
    pnts.SetValue(i, cast_to_gp(Poles[i]));
    kents.SetValue(i, Knots[i]);
    mus.SetValue(i, Multiplicities[i]);
  }
  return new geom2d_bspline_curve_t{
      new Geom2d_BSplineCurve(pnts, kents, mus, Degree, Periodic)};
}

geom2d_bspline_curve_t *
geom2d_make_bspline_curve_with_weight(pnt2d_t *CurvePoles, double *Weights,
                                      double *Knots, int *Multiplicities,
                                      int Count, int Degree, _Bool Periodic) {
  TColgp_Array1OfPnt2d pnts{0, static_cast<Standard_Integer>(Count)};
  TColStd_Array1OfReal wei{0, static_cast<Standard_Integer>(Count)};
  TColStd_Array1OfReal kents{0, static_cast<Standard_Integer>(Count)};
  TColStd_Array1OfInteger mus{0, static_cast<Standard_Integer>(Count)};
  for (int i = 0; i < Count; i++) {
    pnts.SetValue(i, cast_to_gp(CurvePoles[i]));
    kents.SetValue(i, Knots[i]);
    wei.SetValue(i, Weights[i]);
    mus.SetValue(i, Multiplicities[i]);
  }
  return new geom2d_bspline_curve_t{
      new Geom2d_BSplineCurve(pnts, wei, kents, mus, Degree, Periodic)};
}

geom2d_trimmed_curve_t *geom2d_make_trimmed_curve(geom2d_curve_t *C, double U1,
                                                  double U2, _Bool Sense,
                                                  _Bool theAdjustPeriodic) {
  return new geom2d_trimmed_curve_t{
      new Geom2d_TrimmedCurve(C->handle, U1, U2, Sense, theAdjustPeriodic)};
}

geom2d_offset_curve_t *
geom2d_make_offset_curve(geom2d_curve_t *C, double Offset, _Bool isNotCheckC0) {
  return new geom2d_offset_curve_t{
      new Geom2d_OffsetCurve(C->handle, Offset, isNotCheckC0)};
}

geom2d_cartesian_point_t *geom2d_make_cartesian_point(pnt2d_t P) {
  return new geom2d_cartesian_point_t{new Geom2d_CartesianPoint(cast_to_gp(P))};
}

geom2d_cartesian_point_t *geom2d_make_cartesian_point_xy(double X, double Y) {
  return new geom2d_cartesian_point_t{new Geom2d_CartesianPoint(X, Y)};
}

geom2d_direction_t *geom2d_make_direction(double X, double Y) {
  return new geom2d_direction_t{new Geom2d_Direction(X, Y)};
}

geom2d_direction_t *geom2d_make_direction_with_dir(dir2d_t V) {
  return new geom2d_direction_t{new Geom2d_Direction(cast_to_gp(V))};
}

geom2d_vector_with_magnitude_t *
geom2d_make_vector_with_magnitude_with_vector(vec2d_t V) {
  return new geom2d_vector_with_magnitude_t{
      new Geom2d_VectorWithMagnitude(cast_to_gp(V))};
}

geom2d_vector_with_magnitude_t *
geom2d_make_vector_with_magnitude_with_xy(double X, double Y) {
  return new geom2d_vector_with_magnitude_t{
      new Geom2d_VectorWithMagnitude(X, Y)};
}

geom2d_vector_with_magnitude_t *
geom2d_make_vector_with_magnitude_with_point(pnt2d_t P1, pnt2d_t P2) {
  return new geom2d_vector_with_magnitude_t{
      new Geom2d_VectorWithMagnitude(cast_to_gp(P1), cast_to_gp(P2))};
}

#ifdef __cplusplus
}
#endif
