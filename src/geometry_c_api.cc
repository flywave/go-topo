#include "geometry_c_api.h"
#include "cgo_lock.hh"
#include "geometry_creator.hh"
#include "geometry_impl.hh"
#include "plate_plate_impl.hh"
#include "standard_impl.hh"

#ifdef __cplusplus
extern "C" {
#endif

void geom_geometry_free(geom_geometry_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom_transformation_free(geom_transformation_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom_axis_placement_free(geom_axis_placement_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom_axis1_placement_free(geom_axis1_placement_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom_axis2_placement_free(geom_axis2_placement_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom_curve_free(geom_curve_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom_bounded_curve_free(geom_bounded_curve_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom_bezier_curve_free(geom_bezier_curve_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom_bspline_curve_free(geom_bspline_curve_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom_trimmed_curve_free(geom_trimmed_curve_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom_conic_free(geom_conic_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom_circle_free(geom_circle_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom_ellipse_free(geom_ellipse_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom_hyperbola_free(geom_hyperbola_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom_parabola_free(geom_parabola_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom_line_free(geom_line_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom_offset_curve_free(geom_offset_curve_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom_point_free(geom_point_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom_cartesian_point_free(geom_cartesian_point_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom_surface_free(geom_surface_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom_bounded_surface_free(geom_bounded_surface_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom_bezier_surface_free(geom_bezier_surface_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom_bspline_surface_free(geom_bspline_surface_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom_rectangular_trimmed_surface_free(
    geom_rectangular_trimmed_surface_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom_elementary_surface_free(geom_elementary_surface_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom_cylindrical_surface_free(geom_cylindrical_surface_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom_plane_surface_free(geom_plane_surface_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom_conical_surface_free(geom_conical_surface_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom_spherical_surface_free(geom_spherical_surface_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom_toroidal_surface_free(geom_toroidal_surface_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom_offset_surface_free(geom_offset_surface_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom_swept_surface_free(geom_swept_surface_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom_surface_of_linear_extrusion_free(
    geom_surface_of_linear_extrusion_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom_surface_of_revolution_extrusion_free(
    geom_surface_of_revolution_extrusion_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom_plate_surface_free(geom_plate_surface_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom_vector_free(geom_vector_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom_direction_free(geom_direction_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom_vector_with_magnitude_free(geom_vector_with_magnitude_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom2d_geometry_free(geom2d_geometry_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom2d_transformation_free(geom2d_transformation_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom2d_axis_placement_free(geom2d_axis_placement_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom2d_curve_free(geom2d_curve_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom2d_bisector_curve_free(geom2d_bisector_curve_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom2d_bezier_bisec_ana_curve_free(geom2d_bezier_bisec_ana_curve_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom2d_bezier_bisec_cc_curve_free(geom2d_bezier_bisec_cc_curve_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom2d_bezier_bisec_pc_curve_free(geom2d_bezier_bisec_pc_curve_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom2d_bounded_curve_free(geom2d_bounded_curve_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom2d_bezier_curve_free(geom2d_bezier_curve_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom2d_bspline_curve_free(geom2d_bspline_curve_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom2d_trimmed_curve_free(geom2d_trimmed_curve_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom2d_conic_free(geom2d_conic_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom2d_circle_free(geom2d_circle_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom2d_ellipse_free(geom2d_ellipse_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom2d_hyperbola_free(geom2d_hyperbola_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom2d_parabola_free(geom2d_parabola_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom2d_line_free(geom2d_line_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom2d_offset_curve_free(geom2d_offset_curve_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom2d_point_free(geom2d_point_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom2d_cartesian_point_free(geom2d_cartesian_point_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom2d_vector_free(geom2d_vector_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom2d_direction_free(geom2d_direction_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

void geom2d_vector_with_magnitude_free(geom2d_vector_with_magnitude_t *p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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

geom_geometry_t *geom_geometry_copy(geom_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_geometry_t{t->handle->Copy()};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_transformation_t *geom_transformation_copy(geom_transformation_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_transformation_t{t->handle->Copy()};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_axis_placement_t *geom_axis_placement_copy(geom_axis_placement_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_axis_placement_t{
      Handle(Geom_AxisPlacement)::DownCast(t->handle->Copy())};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_axis1_placement_t *geom_axis1_placement_copy(geom_axis1_placement_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_axis1_placement_t{
      Handle(Geom_Axis1Placement)::DownCast(t->handle->Copy())};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_axis2_placement_t *geom_axis2_placement_copy(geom_axis2_placement_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_axis2_placement_t{
      Handle(Geom_Axis2Placement)::DownCast(t->handle->Copy())};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_curve_t *geom_curve_copy(geom_curve_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_curve_t{.handle =
                              Handle(Geom_Curve)::DownCast(t->handle->Copy())};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_bounded_curve_t *geom_bounded_curve_copy(geom_bounded_curve_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_bounded_curve_t{
      Handle(Geom_BoundedCurve)::DownCast(t->handle->Copy())};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_bezier_curve_t *geom_bezier_curve_copy(geom_bezier_curve_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_bezier_curve_t{
      Handle(Geom_BezierCurve)::DownCast(t->handle->Copy())};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_bspline_curve_t *geom_bspline_curve_copy(geom_bspline_curve_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_bspline_curve_t{
      Handle(Geom_BSplineCurve)::DownCast(t->handle->Copy())};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_trimmed_curve_t *geom_trimmed_curve_copy(geom_trimmed_curve_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_trimmed_curve_t{
      Handle(Geom_TrimmedCurve)::DownCast(t->handle->Copy())};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_conic_t *geom_conic_copy(geom_conic_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_conic_t{Handle(Geom_Conic)::DownCast(t->handle->Copy())};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_circle_t *geom_circle_copy(geom_circle_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_circle_t{Handle(Geom_Circle)::DownCast(t->handle->Copy())};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_ellipse_t *geom_ellipse_copy(geom_ellipse_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_ellipse_t{Handle(Geom_Ellipse)::DownCast(t->handle->Copy())};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_hyperbola_t *geom_hyperbola_copy(geom_hyperbola_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_hyperbola_t{
      Handle(Geom_Hyperbola)::DownCast(t->handle->Copy())};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_parabola_t *geom_parabola_copy(geom_parabola_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_parabola_t{
      Handle(Geom_Parabola)::DownCast(t->handle->Copy())};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_line_t *geom_line_copy(geom_line_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_line_t{Handle(Geom_Line)::DownCast(t->handle->Copy())};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_offset_curve_t *geom_offset_curve_copy(geom_offset_curve_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_offset_curve_t{
      Handle(Geom_OffsetCurve)::DownCast(t->handle->Copy())};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_point_t *geom_point_copy(geom_point_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_point_t{Handle(Geom_Point)::DownCast(t->handle->Copy())};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_cartesian_point_t *geom_cartesian_point_copy(geom_cartesian_point_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_cartesian_point_t{
      Handle(Geom_CartesianPoint)::DownCast(t->handle->Copy())};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_surface_t *geom_surface_copy(geom_surface_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_surface_t{Handle(Geom_Surface)::DownCast(t->handle->Copy())};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_bounded_surface_t *geom_bounded_surface_copy(geom_bounded_surface_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_bounded_surface_t{
      Handle(Geom_BoundedSurface)::DownCast(t->handle->Copy())};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_bezier_surface_t *geom_bezier_surface_copy(geom_bezier_surface_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_bezier_surface_t{
      Handle(Geom_BezierSurface)::DownCast(t->handle->Copy())};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_bspline_surface_t *geom_bspline_surface_copy(geom_bspline_surface_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_bspline_surface_t{
      Handle(Geom_BSplineSurface)::DownCast(t->handle->Copy())};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_rectangular_trimmed_surface_t *
geom_rectangular_trimmed_surface_copy(geom_rectangular_trimmed_surface_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_rectangular_trimmed_surface_t{
      Handle(Geom_RectangularTrimmedSurface)::DownCast(t->handle->Copy())};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_elementary_surface_t *
geom_elementary_surface_copy(geom_elementary_surface_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_elementary_surface_t{
      Handle(Geom_ElementarySurface)::DownCast(t->handle->Copy())};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_cylindrical_surface_t *
geom_cylindrical_surface_copy(geom_cylindrical_surface_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_cylindrical_surface_t{
      Handle(Geom_CylindricalSurface)::DownCast(t->handle->Copy())};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_plane_surface_t *geom_plane_surface_copy(geom_plane_surface_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_plane_surface_t{
      Handle(Geom_Plane)::DownCast(t->handle->Copy())};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_conical_surface_t *geom_conical_surface_copy(geom_conical_surface_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_conical_surface_t{
      Handle(Geom_ConicalSurface)::DownCast(t->handle->Copy())};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_spherical_surface_t *
geom_spherical_surface_copy(geom_spherical_surface_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_spherical_surface_t{
      Handle(Geom_SphericalSurface)::DownCast(t->handle->Copy())};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_toroidal_surface_t *
geom_toroidal_surface_copy(geom_toroidal_surface_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_toroidal_surface_t{
      Handle(Geom_ToroidalSurface)::DownCast(t->handle->Copy())};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_offset_surface_t *geom_offset_surface_copy(geom_offset_surface_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_offset_surface_t{
      Handle(Geom_OffsetSurface)::DownCast(t->handle->Copy())};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_swept_surface_t *geom_swept_surface_copy(geom_swept_surface_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_swept_surface_t{
      Handle(Geom_SweptSurface)::DownCast(t->handle->Copy())};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_surface_of_linear_extrusion_t *
geom_surface_of_linear_extrusion_copy(geom_surface_of_linear_extrusion_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_surface_of_linear_extrusion_t{
      Handle(Geom_SurfaceOfLinearExtrusion)::DownCast(t->handle->Copy())};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_surface_of_revolution_extrusion_t *
geom_surface_of_revolution_extrusion_copy(
    geom_surface_of_revolution_extrusion_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_surface_of_revolution_extrusion_t{
      Handle(Geom_SurfaceOfRevolution)::DownCast(t->handle->Copy())};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_plate_surface_t *geom_plate_surface_copy(geom_plate_surface_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_plate_surface_t{
      Handle(GeomPlate_Surface)::DownCast(t->handle->Copy())};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_vector_t *geom_vector_copy(geom_vector_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_vector_t{Handle(Geom_Vector)::DownCast(t->handle->Copy())};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_direction_t *geom_direction_copy(geom_direction_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_direction_t{
      Handle(Geom_Direction)::DownCast(t->handle->Copy())};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_vector_with_magnitude_t *
geom_vector_with_magnitude_copy(geom_vector_with_magnitude_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_vector_with_magnitude_t{
      Handle(Geom_VectorWithMagnitude)::DownCast(t->handle->Copy())};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_geometry_t *geom2d_geometry_copy(geom2d_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_geometry_t{t->handle->Copy()};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_transformation_t *
geom2d_transformation_copy(geom2d_transformation_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_transformation_t{
      Handle(Geom2d_Transformation)::DownCast(t->handle->Copy())};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_axis_placement_t *
geom2d_axis_placement_copy(geom2d_axis_placement_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_axis_placement_t{
      Handle(Geom2d_AxisPlacement)::DownCast(t->handle->Copy())};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_curve_t *geom2d_curve_copy(geom2d_curve_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_curve_t{Handle(Geom2d_Curve)::DownCast(t->handle->Copy())};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_bisector_curve_t *
geom2d_bisector_curve_copy(geom2d_bisector_curve_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_bisector_curve_t{
      Handle(Bisector_Curve)::DownCast(t->handle->Copy())};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_bezier_bisec_ana_curve_t *
geom2d_bezier_bisec_ana_curve_copy(geom2d_bezier_bisec_ana_curve_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_bezier_bisec_ana_curve_t{
      Handle(Bisector_BisecAna)::DownCast(t->handle->Copy())};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_bezier_bisec_cc_curve_t *
geom2d_bezier_bisec_cc_curve_copy(geom2d_bezier_bisec_cc_curve_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_bezier_bisec_cc_curve_t{
      Handle(Bisector_BisecCC)::DownCast(t->handle->Copy())};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_bezier_bisec_pc_curve_t *
geom2d_bezier_bisec_pc_curve_copy(geom2d_bezier_bisec_pc_curve_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_bezier_bisec_pc_curve_t{
      Handle(Bisector_BisecPC)::DownCast(t->handle->Copy())};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_bounded_curve_t *geom2d_bounded_curve_copy(geom2d_bounded_curve_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_bounded_curve_t{
      Handle(Geom2d_BoundedCurve)::DownCast(t->handle->Copy())};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_bezier_curve_t *geom2d_bezier_curve_copy(geom2d_bezier_curve_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_bezier_curve_t{
      Handle(Geom2d_BezierCurve)::DownCast(t->handle->Copy())};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_bspline_curve_t *geom2d_bspline_curve_copy(geom2d_bspline_curve_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_bspline_curve_t{
      Handle(Geom2d_BSplineCurve)::DownCast(t->handle->Copy())};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_trimmed_curve_t *geom2d_trimmed_curve_copy(geom2d_trimmed_curve_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_trimmed_curve_t{
      Handle(Geom2d_TrimmedCurve)::DownCast(t->handle->Copy())};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_conic_t *geom2d_conic_copy(geom2d_conic_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_conic_t{Handle(Geom2d_Conic)::DownCast(t->handle->Copy())};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_circle_t *geom2d_circle_copy(geom2d_circle_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_circle_t{
      Handle(Geom2d_Circle)::DownCast(t->handle->Copy())};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_ellipse_t *geom2d_ellipse_copy(geom2d_ellipse_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_ellipse_t{
      Handle(Geom2d_Ellipse)::DownCast(t->handle->Copy())};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_hyperbola_t *geom2d_hyperbola_copy(geom2d_hyperbola_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_hyperbola_t{
      Handle(Geom2d_Hyperbola)::DownCast(t->handle->Copy())};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_parabola_t *geom2d_parabola_copy(geom2d_parabola_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_parabola_t{
      Handle(Geom2d_Parabola)::DownCast(t->handle->Copy())};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_line_t *geom2d_line_copy(geom2d_line_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_line_t{Handle(Geom2d_Line)::DownCast(t->handle->Copy())};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_offset_curve_t *geom2d_offset_curve_copy(geom2d_offset_curve_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_offset_curve_t{
      Handle(Geom2d_OffsetCurve)::DownCast(t->handle->Copy())};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_point_t *geom2d_point_copy(geom2d_point_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_point_t{Handle(Geom2d_Point)::DownCast(t->handle->Copy())};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_cartesian_point_t *
geom2d_cartesian_point_copy(geom2d_cartesian_point_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_cartesian_point_t{
      Handle(Geom2d_CartesianPoint)::DownCast(t->handle->Copy())};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_vector_t *geom2d_vector_copy(geom2d_vector_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_vector_t{
      Handle(Geom2d_Vector)::DownCast(t->handle->Copy())};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_direction_t *geom2d_direction_copy(geom2d_direction_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_direction_t{
      Handle(Geom2d_Direction)::DownCast(t->handle->Copy())};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_vector_with_magnitude_t *
geom2d_vector_with_magnitude_copy(geom2d_vector_with_magnitude_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_vector_with_magnitude_t{
      Handle(Geom2d_VectorWithMagnitude)::DownCast(t->handle->Copy())};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

_Bool geom_curve_point(geom_curve_t *curve, double s, double *point) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (point != nullptr && curve != nullptr) {
    gp_Pnt pnt = curve->handle->Value(s);
    point[0] = pnt.X();
    point[1] = pnt.Y();
    point[2] = pnt.Z();
    return true;
  }
  return false;
  }
  catch (const std::exception &e) {
    (void)e;
    return false;
  }
  catch (...) {
    return false;
  }
}

_Bool geom_surface_point(geom_surface_t *curve, double s, double *point) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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
  catch (const std::exception &e) {
    (void)e;
    return false;
  }
  catch (...) {
    return false;
  }
}

geom_trimmed_curve_t *geom_make_arc_of_circle_two_angles(circ_t Circ,
                                                         double Alpha1,
                                                         double Alpha2,
                                                         _Bool Sense) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_trimmed_curve_t{
      flywave::topo::geometry_creator::make_arc_of_circle(
          cast_to_gp(Circ), Alpha1, Alpha2, Sense)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_trimmed_curve_t *geom_make_arc_of_circle_angle(circ_t Circ, pnt3d_t P,
                                                    double Alpha, _Bool Sense) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_trimmed_curve_t{
      flywave::topo::geometry_creator::make_arc_of_circle(
          cast_to_gp(Circ), cast_to_gp(P), Alpha, Sense)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_trimmed_curve_t *geom_make_arc_of_circle_two_point(circ_t Circ, pnt3d_t P1,
                                                        pnt3d_t P2,
                                                        _Bool Sense) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_trimmed_curve_t{
      flywave::topo::geometry_creator::make_arc_of_circle(
          cast_to_gp(Circ), cast_to_gp(P1), cast_to_gp(P2), Sense)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_trimmed_curve_t *geom_make_arc_of_point(pnt3d_t P1, pnt3d_t P2,
                                             pnt3d_t P3) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_trimmed_curve_t{
      .handle = flywave::topo::geometry_creator::make_arc_of_circle(
          cast_to_gp(P1), cast_to_gp(P2), cast_to_gp(P3))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_trimmed_curve_t *geom_make_arc_of_two_points_vector(pnt3d_t P1, vec3d_t V,
                                                         pnt3d_t P2) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_trimmed_curve_t{
      .handle = flywave::topo::geometry_creator::make_arc_of_circle_vector(
          cast_to_gp(P1), cast_to_gp(V), cast_to_gp(P2))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_trimmed_curve_t *geom_make_arc_of_ellipsee_two_angles(elips_t Elips,
                                                           double Alpha1,
                                                           double Alpha2,
                                                           _Bool Sense) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_trimmed_curve_t{
      flywave::topo::geometry_creator::make_arc_of_ellipse(
          cast_to_gp(Elips), Alpha1, Alpha2, Sense)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_trimmed_curve_t *geom_make_arc_of_ellipse_angle(elips_t Elips, pnt3d_t P,
                                                     double Alpha,
                                                     _Bool Sense) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_trimmed_curve_t{
      flywave::topo::geometry_creator::make_arc_of_ellipse(
          cast_to_gp(Elips), cast_to_gp(P), Alpha, Sense)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_trimmed_curve_t *geom_make_arc_of_ellipse_point(elips_t Elips, pnt3d_t P1,
                                                     pnt3d_t P2, _Bool Sense) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_trimmed_curve_t{
      flywave::topo::geometry_creator::make_arc_of_ellipse(
          cast_to_gp(Elips), cast_to_gp(P1), cast_to_gp(P2), Sense)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_trimmed_curve_t *geom_make_arc_of_hyperbola_two_angles(hyperbola_t Hypr,
                                                            double Alpha1,
                                                            double Alpha2,
                                                            _Bool Sense) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_trimmed_curve_t{
      flywave::topo::geometry_creator::make_arc_of_hyperbola(
          cast_to_gp(Hypr), Alpha1, Alpha2, Sense)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_trimmed_curve_t *geom_make_arc_of_hyperbola_angle(hyperbola_t Hypr,
                                                       pnt3d_t P, double Alpha,
                                                       _Bool Sense) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_trimmed_curve_t{
      flywave::topo::geometry_creator::make_arc_of_hyperbola(
          cast_to_gp(Hypr), cast_to_gp(P), Alpha, Sense)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_trimmed_curve_t *geom_make_arc_of_hyperbola_point(hyperbola_t Hypr,
                                                       pnt3d_t P1, pnt3d_t P2,
                                                       _Bool Sense) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_trimmed_curve_t{
      flywave::topo::geometry_creator::make_arc_of_hyperbola(
          cast_to_gp(Hypr), cast_to_gp(P1), cast_to_gp(P2), Sense)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_trimmed_curve_t *geom_make_arc_of_parabola_two_angles(parabola_t Parab,
                                                           double Alpha1,
                                                           double Alpha2,
                                                           _Bool Sense) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_trimmed_curve_t{
      flywave::topo::geometry_creator::make_arc_of_parabola(
          cast_to_gp(Parab), Alpha1, Alpha2, Sense)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_trimmed_curve_t *geom_make_arc_of_parabola_angle(parabola_t Parab,
                                                      pnt3d_t P, double Alpha,
                                                      _Bool Sense) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_trimmed_curve_t{
      flywave::topo::geometry_creator::make_arc_of_parabola(
          cast_to_gp(Parab), cast_to_gp(P), Alpha, Sense)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_trimmed_curve_t *geom_make_arc_of_parabola_point(parabola_t Parab,
                                                      pnt3d_t P1, pnt3d_t P2,
                                                      _Bool Sense) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_trimmed_curve_t{
      flywave::topo::geometry_creator::make_arc_of_parabola(
          cast_to_gp(Parab), cast_to_gp(P1), cast_to_gp(P2), Sense)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_circle_t *geom_make_circle(circ_t C) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_circle_t{
      flywave::topo::geometry_creator::make_circle(cast_to_gp(C))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_circle_t *geom_make_circle_of_axis2(axis2_t A2, double Radius) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_circle_t{
      flywave::topo::geometry_creator::make_circle(cast_to_gp(A2), Radius)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_circle_t *geom_make_circle_of_dist(circ_t Circ, double Dist) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_circle_t{
      flywave::topo::geometry_creator::make_circle(cast_to_gp(Circ), Dist)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_circle_t *geom_make_circle_of_point(circ_t Circ, pnt3d_t Point) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_circle_t{flywave::topo::geometry_creator::make_circle(
      cast_to_gp(Circ), cast_to_gp(Point))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_circle_t *geom_make_circle_of_three_point(pnt3d_t P1, pnt3d_t P2,
                                               pnt3d_t P3) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_circle_t{flywave::topo::geometry_creator::make_circle(
      cast_to_gp(P1), cast_to_gp(P2), cast_to_gp(P3))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_circle_t *geom_make_circle_of_center_norm(pnt3d_t Center, dir3d_t Norm,
                                               double Radius) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_circle_t{flywave::topo::geometry_creator::make_circle(
      cast_to_gp(Center), cast_to_gp(Norm), Radius)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_circle_t *geom_make_circle_center_axis(pnt3d_t Center, pnt3d_t PtAxis,
                                            double Radius) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_circle_t{flywave::topo::geometry_creator::make_circle(
      cast_to_gp(Center), cast_to_gp(PtAxis), Radius)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_circle_t *geom_make_circle_of_axis1(axis1_t Axis, double Radius) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_circle_t{
      flywave::topo::geometry_creator::make_circle(cast_to_gp(Axis), Radius)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_ellipse_t *geom_make_ellipse(elips_t E) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_ellipse_t{
      flywave::topo::geometry_creator::make_ellipse(cast_to_gp(E))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_ellipse_t *geom_make_ellipse_of_axis2(axis2_t A2, double MajorRadius,
                                           double MinorRadius) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_ellipse_t{flywave::topo::geometry_creator::make_ellipse(
      cast_to_gp(A2), MajorRadius, MinorRadius)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_ellipse_t *geom_make_ellipse_point_center(pnt3d_t S1, pnt3d_t S2,
                                               pnt3d_t Center) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_ellipse_t{flywave::topo::geometry_creator::make_ellipse(
      cast_to_gp(S1), cast_to_gp(S2), cast_to_gp(Center))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_hyperbola_t *geom_make_hyperbola(hyperbola_t H) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_hyperbola_t{
      flywave::topo::geometry_creator::make_hyperbola(cast_to_gp(H))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_hyperbola_t *geom_make_hyperbola_of_axis2(axis2_t A2, double MajorRadius,
                                               double MinorRadius) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_hyperbola_t{flywave::topo::geometry_creator::make_hyperbola(
      cast_to_gp(A2), MajorRadius, MinorRadius)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_hyperbola_t *geom_make_hyperbola_point_center(pnt3d_t S1, pnt3d_t S2,
                                                   pnt3d_t Center) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_hyperbola_t{flywave::topo::geometry_creator::make_hyperbola(
      cast_to_gp(S1), cast_to_gp(S2), cast_to_gp(Center))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_conical_surface_t *geom_make_conical_surface_axis2(axis2_t A2, double Ang,
                                                        double Radius) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_conical_surface_t{
      flywave::topo::geometry_creator::make_conical_surface(cast_to_gp(A2), Ang,
                                                            Radius)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_conical_surface_t *geom_make_conical_surface(cone_t C) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_conical_surface_t{
      flywave::topo::geometry_creator::make_conical_surface(cast_to_gp(C))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_conical_surface_t *geom_make_conical_surface_of_point(pnt3d_t P1,
                                                           pnt3d_t P2,
                                                           pnt3d_t P3,
                                                           pnt3d_t P4) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_conical_surface_t{
      flywave::topo::geometry_creator::make_conical_surface(
          cast_to_gp(P1), cast_to_gp(P2), cast_to_gp(P3), cast_to_gp(P4))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_conical_surface_t *geom_make_conical_surface_of_point_radius(pnt3d_t P1,
                                                                  pnt3d_t P2,
                                                                  double R1,
                                                                  double R2) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_conical_surface_t{
      flywave::topo::geometry_creator::make_conical_surface(
          cast_to_gp(P1), cast_to_gp(P2), R1, R2)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_cylindrical_surface_t *
geom_make_cylindrical_surface_of_axis2(axis2_t A2, double Radius) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_cylindrical_surface_t{
      flywave::topo::geometry_creator::make_cylindrical_surface(cast_to_gp(A2),
                                                                Radius)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_cylindrical_surface_t *geom_make_cylindrical_surface(cylinder_t C) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_cylindrical_surface_t{
      flywave::topo::geometry_creator::make_cylindrical_surface(cast_to_gp(C))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_cylindrical_surface_t *
geom_make_cylindrical_surface_of_point(cylinder_t Cyl, pnt3d_t Point) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_cylindrical_surface_t{
      flywave::topo::geometry_creator::make_cylindrical_surface(
          cast_to_gp(Cyl), cast_to_gp(Point))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_cylindrical_surface_t *
geom_make_cylindrical_surface_of_dist(cylinder_t Cyl, double Dist) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_cylindrical_surface_t{
      flywave::topo::geometry_creator::make_cylindrical_surface(cast_to_gp(Cyl),
                                                                Dist)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_cylindrical_surface_t *
geom_make_cylindrical_surface_of_three_point(pnt3d_t P1, pnt3d_t P2,
                                             pnt3d_t P3) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_cylindrical_surface_t{
      flywave::topo::geometry_creator::make_cylindrical_surface(
          cast_to_gp(P1), cast_to_gp(P2), cast_to_gp(P3))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_cylindrical_surface_t *
geom_make_cylindrical_surface_of_axis_radius(axis1_t Axis, double Radius) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_cylindrical_surface_t{
      flywave::topo::geometry_creator::make_cylindrical_surface(
          cast_to_gp(Axis), Radius)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_cylindrical_surface_t *geom_make_cylindrical_surface_of_circ(circ_t Circ) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_cylindrical_surface_t{
      flywave::topo::geometry_creator::make_cylindrical_surface(
          cast_to_gp(Circ))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_line_t *geom_make_line_of_axis1(axis1_t A1) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_line_t{
      flywave::topo::geometry_creator::make_line(cast_to_gp(A1))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_line_t *geom_make_line(line_t L) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_line_t{
      flywave::topo::geometry_creator::make_line(cast_to_gp(L))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_line_t *geom_make_line_of_point_dir(pnt3d_t P, dir3d_t V) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_line_t{
      flywave::topo::geometry_creator::make_line(cast_to_gp(P), cast_to_gp(V))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_line_t *geom_make_line_point(line_t Lin, pnt3d_t Point) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_line_t{flywave::topo::geometry_creator::make_line(
      cast_to_gp(Lin), cast_to_gp(Point))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_line_t *geom_make_line_of_two_point(pnt3d_t P1, pnt3d_t P2) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_line_t{flywave::topo::geometry_creator::make_line(
      cast_to_gp(P1), cast_to_gp(P2))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_transformation_t *geom_make_mirror_of_point(pnt3d_t Point) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_transformation_t{
      flywave::topo::geometry_creator::make_mirror(cast_to_gp(Point))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_transformation_t *geom_make_mirror_of_axis1(axis1_t Axis) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_transformation_t{
      flywave::topo::geometry_creator::make_mirror(cast_to_gp(Axis))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_transformation_t *geom_make_mirror_of_line(line_t Line) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_transformation_t{
      flywave::topo::geometry_creator::make_mirror(cast_to_gp(Line))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_transformation_t *geom_make_mirror_of_point_dir(pnt3d_t Point,
                                                     dir3d_t Direc) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_transformation_t{flywave::topo::geometry_creator::make_mirror(
      cast_to_gp(Point), cast_to_gp(Direc))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_transformation_t *geom_make_mirror_of_plane(plane_t Plane) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_transformation_t{
      flywave::topo::geometry_creator::make_mirror(cast_to_gp(Plane))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_transformation_t *geom_make_mirror_of_axis2(axis2_t Plane) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_transformation_t{
      flywave::topo::geometry_creator::make_mirror(cast_to_gp(Plane))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_transformation_t *geom_make_rotation_of_line(line_t Line, double Angle) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_transformation_t{
      flywave::topo::geometry_creator::make_rotation(cast_to_gp(Line), Angle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_transformation_t *geom_make_rotation_of_axis1(axis1_t Axis, double Angle) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_transformation_t{
      flywave::topo::geometry_creator::make_rotation(cast_to_gp(Axis), Angle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_transformation_t *
geom_make_rotation_of_point_dir(pnt3d_t Point, dir3d_t Direc, double Angle) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_transformation_t{
      flywave::topo::geometry_creator::make_rotation(cast_to_gp(Point),
                                                     cast_to_gp(Direc), Angle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_transformation_t *geom_make_translation_of_vect(vec3d_t Vect) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_transformation_t{
      flywave::topo::geometry_creator::make_translation(cast_to_gp(Vect))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_transformation_t *geom_make_translation_of_two_point(pnt3d_t Point1,
                                                          pnt3d_t Point2) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_transformation_t{
      flywave::topo::geometry_creator::make_translation(cast_to_gp(Point1),
                                                        cast_to_gp(Point2))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_transformation_t *geom_make_scale_of_point_scale(pnt3d_t Point,
                                                      double Scale) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_transformation_t{
      flywave::topo::geometry_creator::make_scale(cast_to_gp(Point), Scale)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_plane_surface_t *geom_make_plane(plane_t Pl) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_plane_surface_t{
      flywave::topo::geometry_creator::make_plane(cast_to_gp(Pl))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_plane_surface_t *geom_make_plane_of_point_dir(pnt3d_t P, dir3d_t V) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_plane_surface_t{flywave::topo::geometry_creator::make_plane(
      cast_to_gp(P), cast_to_gp(V))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_plane_surface_t *geom_make_plane_of_lrud(double A, double B, double C,
                                              double D) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_plane_surface_t{
      flywave::topo::geometry_creator::make_plane(A, B, C, D)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_plane_surface_t *geom_make_plane_of_point(plane_t Pln, pnt3d_t Point) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_plane_surface_t{flywave::topo::geometry_creator::make_plane(
      cast_to_gp(Pln), cast_to_gp(Point))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_plane_surface_t *geom_make_plane_of_dist(plane_t Pln, double Dist) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_plane_surface_t{
      flywave::topo::geometry_creator::make_plane(cast_to_gp(Pln), Dist)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_plane_surface_t *geom_make_plane_of_three_point(pnt3d_t P1, pnt3d_t P2,
                                                     pnt3d_t P3) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_plane_surface_t{flywave::topo::geometry_creator::make_plane(
      cast_to_gp(P1), cast_to_gp(P2), cast_to_gp(P3))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_plane_surface_t *geom_make_plane_of_axis1(axis1_t Axis) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_plane_surface_t{
      flywave::topo::geometry_creator::make_plane(cast_to_gp(Axis))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_trimmed_curve_t *geom_make_segment_of_two_point(pnt3d_t P1, pnt3d_t P2) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_trimmed_curve_t{flywave::topo::geometry_creator::make_segment(
      cast_to_gp(P1), cast_to_gp(P2))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_trimmed_curve_t *geom_make_segment_of_line_u(line_t Line, double U1,
                                                  double U2) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_trimmed_curve_t{
      flywave::topo::geometry_creator::make_segment(cast_to_gp(Line), U1, U2)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_trimmed_curve_t *
geom_make_segment_of_line_point(line_t Line, pnt3d_t Point, double Ulast) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_trimmed_curve_t{flywave::topo::geometry_creator::make_segment(
      cast_to_gp(Line), cast_to_gp(Point), Ulast)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_trimmed_curve_t *geom_make_segment_of_point(line_t Line, pnt3d_t P1,
                                                 pnt3d_t P2) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_trimmed_curve_t{flywave::topo::geometry_creator::make_segment(
      cast_to_gp(Line), cast_to_gp(P1), cast_to_gp(P2))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_rectangular_trimmed_surface_t *
geom_make_trimmed_cone_of_point(pnt3d_t P1, pnt3d_t P2, pnt3d_t P3,
                                pnt3d_t P4) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_rectangular_trimmed_surface_t{
      flywave::topo::geometry_creator::make_trimmed_cone(
          cast_to_gp(P1), cast_to_gp(P2), cast_to_gp(P3), cast_to_gp(P4))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_rectangular_trimmed_surface_t *
geom_make_trimmed_cone_of_point_radius(pnt3d_t P1, pnt3d_t P2, double R1,
                                       double R2) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_rectangular_trimmed_surface_t{
      flywave::topo::geometry_creator::make_trimmed_cone(
          cast_to_gp(P1), cast_to_gp(P2), R1, R2)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_rectangular_trimmed_surface_t *
geom_make_trimmed_cylinder_of_point(pnt3d_t P1, pnt3d_t P2, pnt3d_t P3) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_rectangular_trimmed_surface_t{
      flywave::topo::geometry_creator::make_trimmed_cylinder(
          cast_to_gp(P1), cast_to_gp(P2), cast_to_gp(P3))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_rectangular_trimmed_surface_t *
geom_make_trimmed_cylinder_of_circ_height(circ_t Circ, double Height) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_rectangular_trimmed_surface_t{
      flywave::topo::geometry_creator::make_trimmed_cylinder(cast_to_gp(Circ),
                                                             Height)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_rectangular_trimmed_surface_t *
geom_make_trimmed_cylinder_axis_radius(axis1_t A1, double Radius,
                                       double Height) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_rectangular_trimmed_surface_t{
      flywave::topo::geometry_creator::make_trimmed_cylinder(cast_to_gp(A1),
                                                             Radius, Height)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_trimmed_curve_t *geom2d_make_arc_of_circle_two_angles(circ2d_t Circ,
                                                             double Alpha1,
                                                             double Alpha2,
                                                             _Bool Sense) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_trimmed_curve_t{
      flywave::topo::geometry_creator::make_arc_of_circle(
          cast_to_gp(Circ), Alpha1, Alpha2, Sense)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_trimmed_curve_t *geom2d_make_arc_of_circle_angle(circ2d_t Circ,
                                                        pnt2d_t P, double Alpha,
                                                        _Bool Sense) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_trimmed_curve_t{
      flywave::topo::geometry_creator::make_arc_of_circle(
          cast_to_gp(Circ), cast_to_gp(P), Alpha, Sense)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_trimmed_curve_t *geom2d_make_arc_of_circle_two_point(circ2d_t Circ,
                                                            pnt2d_t P1,
                                                            pnt2d_t P2,
                                                            _Bool Sense) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_trimmed_curve_t{
      flywave::topo::geometry_creator::make_arc_of_circle(
          cast_to_gp(Circ), cast_to_gp(P1), cast_to_gp(P2), Sense)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_trimmed_curve_t *geom2d_make_arc_of_circle_point(pnt2d_t P1, pnt2d_t P2,
                                                        pnt2d_t P3) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_trimmed_curve_t{
      flywave::topo::geometry_creator::make_arc_of_circle(
          cast_to_gp(P1), cast_to_gp(P2), cast_to_gp(P3))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_trimmed_curve_t *geom2d_make_arc_of_circle_vector(pnt2d_t P1, vec2d_t V,
                                                         pnt2d_t P2) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_trimmed_curve_t{
      flywave::topo::geometry_creator::make_arc_of_circle_vector(
          cast_to_gp(P1), cast_to_gp(V), cast_to_gp(P2))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_trimmed_curve_t *geom2d_make_arc_of_ellipse_two_angles(elips2d_t Elips,
                                                              double Alpha1,
                                                              double Alpha2,
                                                              _Bool Sense) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_trimmed_curve_t{
      flywave::topo::geometry_creator::make_arc_of_ellipse(
          cast_to_gp(Elips), Alpha1, Alpha2, Sense)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_trimmed_curve_t *geom2d_make_arc_of_ellipse_angle(elips2d_t Elips,
                                                         pnt2d_t P,
                                                         double Alpha,
                                                         _Bool Sense) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_trimmed_curve_t{
      flywave::topo::geometry_creator::make_arc_of_ellipse(
          cast_to_gp(Elips), cast_to_gp(P), Alpha, Sense)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_trimmed_curve_t *geom2d_make_arc_of_ellipse_point(elips2d_t Elips,
                                                         pnt2d_t P1, pnt2d_t P2,
                                                         _Bool Sense) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_trimmed_curve_t{
      flywave::topo::geometry_creator::make_arc_of_ellipse(
          cast_to_gp(Elips), cast_to_gp(P1), cast_to_gp(P2), Sense)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_trimmed_curve_t *
geom2d_make_arc_of_hyperbola_two_angles(hyperbola2d_t Hypr, double Alpha1,
                                        double Alpha2, _Bool Sense) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_trimmed_curve_t{
      flywave::topo::geometry_creator::make_arc_of_hyperbola(
          cast_to_gp(Hypr), Alpha1, Alpha2, Sense)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_trimmed_curve_t *geom2d_make_arc_of_hyperbola_angle(hyperbola2d_t Hypr,
                                                           pnt2d_t P,
                                                           double Alpha,
                                                           _Bool Sense) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_trimmed_curve_t{
      flywave::topo::geometry_creator::make_arc_of_hyperbola(
          cast_to_gp(Hypr), cast_to_gp(P), Alpha, Sense)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_trimmed_curve_t *geom2d_make_arc_of_hyperbola_point(hyperbola2d_t Hypr,
                                                           pnt2d_t P1,
                                                           pnt2d_t P2,
                                                           _Bool Sense) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_trimmed_curve_t{
      flywave::topo::geometry_creator::make_arc_of_hyperbola(
          cast_to_gp(Hypr), cast_to_gp(P1), cast_to_gp(P2), Sense)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_trimmed_curve_t *
geom2d_make_arc_of_parabola_two_angles(parabola2d_t Parab, double Alpha1,
                                       double Alpha2, _Bool Sense) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_trimmed_curve_t{
      flywave::topo::geometry_creator::make_arc_of_parabola(
          cast_to_gp(Parab), Alpha1, Alpha2, Sense)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_trimmed_curve_t *
geom2d_make_arc_of_parabola_angle_angle(parabola2d_t Parab, pnt2d_t P,
                                        double Alpha, _Bool Sense) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_trimmed_curve_t{
      flywave::topo::geometry_creator::make_arc_of_parabola(
          cast_to_gp(Parab), cast_to_gp(P), Alpha, Sense)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_trimmed_curve_t *geom2d_make_arc_of_parabola_point(parabola2d_t Parab,
                                                          pnt2d_t P1,
                                                          pnt2d_t P2,
                                                          _Bool Sense) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_trimmed_curve_t{
      flywave::topo::geometry_creator::make_arc_of_parabola(
          cast_to_gp(Parab), cast_to_gp(P1), cast_to_gp(P2), Sense)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_circle_t *geom2d_make_circle(circ2d_t C) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_circle_t{
      flywave::topo::geometry_creator::make_circle(cast_to_gp(C))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_circle_t *geom2d_make_circle_of_axis2d(axis2d_t A, double Radius,
                                              _Bool Sense) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_circle_t{flywave::topo::geometry_creator::make_circle(
      cast_to_gp(A), Radius, Sense)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_circle_t *geom2d_make_circle_of_axis22d(axis22d_t A, double Radius) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_circle_t{
      flywave::topo::geometry_creator::make_circle(cast_to_gp(A), Radius)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_circle_t *geom2d_make_circle_of_circ2d_dist(circ2d_t Circ, double Dist) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_circle_t{
      flywave::topo::geometry_creator::make_circle(cast_to_gp(Circ), Dist)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_circle_t *geom2d_make_circle_of_circ2d_point(circ2d_t Circ,
                                                    pnt2d_t Point) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_circle_t{flywave::topo::geometry_creator::make_circle(
      cast_to_gp(Circ), cast_to_gp(Point))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_circle_t *geom2d_make_circle_of_three_point(pnt2d_t P1, pnt2d_t P2,
                                                   pnt2d_t P3) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_circle_t{flywave::topo::geometry_creator::make_circle(
      cast_to_gp(P1), cast_to_gp(P2), cast_to_gp(P3))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_circle_t *geom2d_make_circle_of_point_radius(pnt2d_t P, double Radius,
                                                    _Bool Sense) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_circle_t{flywave::topo::geometry_creator::make_circle(
      cast_to_gp(P), Radius, Sense)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_circle_t *geom2d_make_circle_of_center_radius(pnt2d_t Center,
                                                     pnt2d_t Point,
                                                     _Bool Sense) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_circle_t{flywave::topo::geometry_creator::make_circle(
      cast_to_gp(Center), cast_to_gp(Point), Sense)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_ellipse_t *geom2d_make_ellipse(elips2d_t E) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_ellipse_t{
      flywave::topo::geometry_creator::make_ellipse(cast_to_gp(E))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_ellipse_t *geom2d_make_ellipse_of_axis2d_radius(axis2d_t MajorAxis,
                                                       double MajorRadius,
                                                       double MinorRadius,
                                                       _Bool Sense) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_ellipse_t{flywave::topo::geometry_creator::make_ellipse(
      cast_to_gp(MajorAxis), MajorRadius, MinorRadius, Sense)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_ellipse_t *geom2d_make_ellipse_of_axis22d_radius(axis22d_t Axis,
                                                        double MajorRadius,
                                                        double MinorRadius) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_ellipse_t{flywave::topo::geometry_creator::make_ellipse(
      cast_to_gp(Axis), MajorRadius, MinorRadius)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_ellipse_t *geom2d_make_ellipse_of_three_point(pnt2d_t S1, pnt2d_t S2,
                                                     pnt2d_t Center) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_ellipse_t{flywave::topo::geometry_creator::make_ellipse(
      cast_to_gp(S1), cast_to_gp(S2), cast_to_gp(Center))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_hyperbola_t *geom2d_make_hyperbola(hyperbola2d_t H) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_hyperbola_t{
      flywave::topo::geometry_creator::make_hyperbola(cast_to_gp(H))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_hyperbola_t *geom2d_make_hyperbola_of_axis2d_radius(axis2d_t MajorAxis,
                                                           double MajorRadius,
                                                           double MinorRadius,
                                                           _Bool Sense) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_hyperbola_t{flywave::topo::geometry_creator::make_hyperbola(
      cast_to_gp(MajorAxis), MajorRadius, MinorRadius, Sense)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_hyperbola_t *
geom2d_make_hyperbola_of_axis22d_radius(axis22d_t Axis, double MajorRadius,
                                        double MinorRadius) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_hyperbola_t{flywave::topo::geometry_creator::make_hyperbola(
      cast_to_gp(Axis), MajorRadius, MinorRadius)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_hyperbola_t *geom2d_make_hyperbola_of_three_point(pnt2d_t S1, pnt2d_t S2,
                                                         pnt2d_t Center) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_hyperbola_t{flywave::topo::geometry_creator::make_hyperbola(
      cast_to_gp(S1), cast_to_gp(S2), cast_to_gp(Center))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_line_t *geom2d_make_line_of_axis2d(axis2d_t A) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_line_t{
      flywave::topo::geometry_creator::make_line(cast_to_gp(A))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_line_t *geom2d_make_line(line2d_t L) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_line_t{
      flywave::topo::geometry_creator::make_line(cast_to_gp(L))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_line_t *geom2d_make_line_of_point_dir(pnt2d_t P, dir2d_t V) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_line_t{
      flywave::topo::geometry_creator::make_line(cast_to_gp(P), cast_to_gp(V))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_line_t *geom2d_make_line_of_point(line2d_t Lin, pnt2d_t Point) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_line_t{flywave::topo::geometry_creator::make_line(
      cast_to_gp(Lin), cast_to_gp(Point))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_line_t *geom2d_make_line_of_dist(line2d_t Lin, double Dist) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_line_t{
      flywave::topo::geometry_creator::make_line(cast_to_gp(Lin), Dist)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_line_t *geom2d_make_line_of_two_point(pnt2d_t P1, pnt2d_t P2) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_line_t{flywave::topo::geometry_creator::make_line(
      cast_to_gp(P1), cast_to_gp(P2))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_parabola_t *geom2d_make_parabola(parabola2d_t Prb) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_parabola_t{
      flywave::topo::geometry_creator::make_parabola(cast_to_gp(Prb))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_parabola_t *geom2d_make_parabola_of_axis22d(axis22d_t Axis,
                                                   double Focal) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_parabola_t{
      flywave::topo::geometry_creator::make_parabola(cast_to_gp(Axis), Focal)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_parabola_t *geom2d_make_parabola_of_axis2d(axis2d_t MirrorAxis,
                                                  double Focal, _Bool Sense) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_parabola_t{flywave::topo::geometry_creator::make_parabola(
      cast_to_gp(MirrorAxis), Focal, Sense)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_parabola_t *geom2d_make_parabola_of_axis2d_point(axis2d_t D, pnt2d_t F,
                                                        _Bool Sense) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_parabola_t{flywave::topo::geometry_creator::make_parabola(
      cast_to_gp(D), cast_to_gp(F), Sense)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_parabola_t *geom2d_make_parabola_point(pnt2d_t S1, pnt2d_t O) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_parabola_t{flywave::topo::geometry_creator::make_parabola(
      cast_to_gp(S1), cast_to_gp(O))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_trimmed_curve_t *geom2d_make_segment_of_point(pnt2d_t P1, pnt2d_t P2) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_trimmed_curve_t{
      flywave::topo::geometry_creator::make_segment(cast_to_gp(P1),
                                                    cast_to_gp(P2))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_trimmed_curve_t *geom2d_make_segment_of_point_dir(pnt2d_t P1, dir2d_t V,
                                                         pnt2d_t P2) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_trimmed_curve_t{
      flywave::topo::geometry_creator::make_segment(
          cast_to_gp(P1), cast_to_gp(V), cast_to_gp(P2))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_trimmed_curve_t *geom2d_make_segment_of_line(line2d_t Line, double U1,
                                                    double U2) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_trimmed_curve_t{
      flywave::topo::geometry_creator::make_segment(cast_to_gp(Line), U1, U2)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_trimmed_curve_t *
geom2d_make_segment_of_line_point(line2d_t Line, pnt2d_t Point, double Ulast) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_trimmed_curve_t{
      flywave::topo::geometry_creator::make_segment(cast_to_gp(Line),
                                                    cast_to_gp(Point), Ulast)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_trimmed_curve_t *
geom2d_make_segment_of_line_two_point(line2d_t Line, pnt2d_t P1, pnt2d_t P2) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_trimmed_curve_t{
      flywave::topo::geometry_creator::make_segment(
          cast_to_gp(Line), cast_to_gp(P1), cast_to_gp(P2))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_transformation_t *geom2d_make_mirror_of_point(pnt2d_t Point) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_transformation_t{
      flywave::topo::geometry_creator::make_mirror(cast_to_gp(Point))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_transformation_t *geom2d_make_mirror_of_axis2d(axis2d_t Axis) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_transformation_t{
      flywave::topo::geometry_creator::make_mirror(cast_to_gp(Axis))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_transformation_t *geom2d_make_mirror_of_line2d(line2d_t Line) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_transformation_t{
      flywave::topo::geometry_creator::make_mirror(cast_to_gp(Line))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_transformation_t *geom2d_make_mirror_of_point_dir(pnt2d_t Point,
                                                         dir2d_t Direc) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_transformation_t{
      flywave::topo::geometry_creator::make_mirror(cast_to_gp(Point),
                                                   cast_to_gp(Direc))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_transformation_t *geom2d_make_rotation_of_point_angle(pnt2d_t Point,
                                                             double Angle) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_transformation_t{
      flywave::topo::geometry_creator::make_rotation(cast_to_gp(Point), Angle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_transformation_t *geom2d_make_scale_point_scale(pnt2d_t Point,
                                                       double Scale) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_transformation_t{
      flywave::topo::geometry_creator::make_scale(cast_to_gp(Point), Scale)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_transformation_t *geom2d_make_translation_of_vector(vec2d_t Vect) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_transformation_t{
      flywave::topo::geometry_creator::make_translation(cast_to_gp(Vect))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_transformation_t *geom2d_make_translation_of_point(pnt2d_t Point1,
                                                          pnt2d_t Point2) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_transformation_t{
      flywave::topo::geometry_creator::make_translation(cast_to_gp(Point1),
                                                        cast_to_gp(Point2))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_geometry_t *geom_axis_placement_to_geometry(geom_axis_placement_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_geometry_t{t->handle};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_geometry_t *geom_axis1_placement_to_geometry(geom_axis1_placement_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_geometry_t{t->handle};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_geometry_t *geom_axis2_placement_to_geometry(geom_axis2_placement_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_geometry_t{t->handle};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_geometry_t *geom_curve_to_geometry(geom_curve_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_geometry_t{t->handle};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_geometry_t *geom_bounded_curve_to_geometry(geom_bounded_curve_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_geometry_t{t->handle};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_geometry_t *geom_bezier_curve_to_geometry(geom_bezier_curve_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_geometry_t{t->handle};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_geometry_t *geom_bspline_curve_to_geometry(geom_bspline_curve_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_geometry_t{t->handle};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_geometry_t *geom_trimmed_curve_to_geometry(geom_trimmed_curve_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_geometry_t{t->handle};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_geometry_t *geom_conic_to_geometry(geom_conic_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_geometry_t{t->handle};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_geometry_t *geom_circle_to_geometry(geom_circle_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_geometry_t{t->handle};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_geometry_t *geom_ellipse_to_geometry(geom_ellipse_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_geometry_t{t->handle};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_geometry_t *geom_hyperbola_to_geometry(geom_hyperbola_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_geometry_t{t->handle};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_geometry_t *geom_parabola_to_geometry(geom_parabola_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_geometry_t{t->handle};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_geometry_t *geom_line_to_geometry(geom_line_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_geometry_t{t->handle};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_geometry_t *geom_offset_curve_to_geometry(geom_offset_curve_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_geometry_t{t->handle};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_geometry_t *geom_point_to_geometry(geom_point_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_geometry_t{t->handle};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_geometry_t *geom_cartesian_point_to_geometry(geom_cartesian_point_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_geometry_t{t->handle};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_geometry_t *geom_surface_to_geometry(geom_surface_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_geometry_t{t->handle};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_geometry_t *geom_bounded_surface_to_geometry(geom_bounded_surface_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_geometry_t{t->handle};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_geometry_t *geom_bezier_surface_to_geometry(geom_bezier_surface_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_geometry_t{t->handle};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_geometry_t *geom_bspline_surface_to_geometry(geom_bspline_surface_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_geometry_t{t->handle};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_geometry_t *geom_rectangular_trimmed_surface_to_geometry(
    geom_rectangular_trimmed_surface_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_geometry_t{t->handle};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_geometry_t *
geom_elementary_surface_to_geometry(geom_elementary_surface_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_geometry_t{t->handle};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_geometry_t *
geom_cylindrical_surface_to_geometry(geom_cylindrical_surface_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_geometry_t{t->handle};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_geometry_t *geom_plane_surface_to_geometry(geom_plane_surface_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_geometry_t{t->handle};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_geometry_t *geom_conical_surface_to_geometry(geom_conical_surface_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_geometry_t{t->handle};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_geometry_t *
geom_spherical_surface_to_geometry(geom_spherical_surface_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_geometry_t{t->handle};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_geometry_t *geom_toroidal_surface_to_geometry(geom_toroidal_surface_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_geometry_t{t->handle};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_geometry_t *geom_offset_surface_to_geometry(geom_offset_surface_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_geometry_t{t->handle};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_geometry_t *geom_swept_surface_to_geometry(geom_swept_surface_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_geometry_t{t->handle};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_geometry_t *geom_surface_of_linear_extrusion_to_geometry(
    geom_surface_of_linear_extrusion_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_geometry_t{t->handle};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_geometry_t *geom_surface_of_revolution_extrusion_to_geometry(
    geom_surface_of_revolution_extrusion_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_geometry_t{t->handle};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_geometry_t *geom_plate_surface_to_geometry(geom_plate_surface_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_geometry_t{t->handle};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_geometry_t *geom_vector_to_geometry(geom_vector_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_geometry_t{t->handle};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_geometry_t *geom_direction_to_geometry(geom_direction_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_geometry_t{t->handle};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_geometry_t *
geom_vector_with_magnitude_to_geometry(geom_vector_with_magnitude_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_geometry_t{t->handle};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_geometry_t *
geom2d_axis_placement_to_geometry(geom2d_axis_placement_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_geometry_t{t->handle};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_geometry_t *geom2d_curve_to_geometry(geom2d_curve_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_geometry_t{t->handle};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_geometry_t *
geom2d_bisector_curve_to_geometry(geom2d_bisector_curve_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_geometry_t{t->handle};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_geometry_t *
geom2d_bezier_bisec_ana_curve_to_geometry(geom2d_bezier_bisec_ana_curve_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_geometry_t{t->handle};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_geometry_t *
geom2d_bezier_bisec_cc_curve_to_geometry(geom2d_bezier_bisec_cc_curve_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_geometry_t{t->handle};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_geometry_t *
geom2d_bezier_bisec_pc_curve_to_geometry(geom2d_bezier_bisec_pc_curve_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_geometry_t{t->handle};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_geometry_t *geom2d_bounded_curve_to_geometry(geom2d_bounded_curve_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_geometry_t{t->handle};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_geometry_t *geom2d_bezier_curve_to_geometry(geom2d_bezier_curve_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_geometry_t{t->handle};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_geometry_t *geom2d_bspline_curve_to_geometry(geom2d_bspline_curve_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_geometry_t{t->handle};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_geometry_t *geom2d_trimmed_curve_to_geometry(geom2d_trimmed_curve_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_geometry_t{t->handle};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_geometry_t *geom2d_conic_to_geometry(geom2d_conic_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_geometry_t{t->handle};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_geometry_t *geom2d_circle_to_geometry(geom2d_circle_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_geometry_t{t->handle};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_geometry_t *geom2d_ellipse_to_geometry(geom2d_ellipse_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_geometry_t{t->handle};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_geometry_t *geom2d_hyperbola_to_geometry(geom2d_hyperbola_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_geometry_t{t->handle};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_geometry_t *geom2d_parabola_to_geometry(geom2d_parabola_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_geometry_t{t->handle};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_geometry_t *geom2d_line_to_geometry(geom2d_line_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_geometry_t{t->handle};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_geometry_t *geom2d_offset_curve_to_geometry(geom2d_offset_curve_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_geometry_t{t->handle};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_geometry_t *geom2d_point_to_geometry(geom2d_point_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_geometry_t{t->handle};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_geometry_t *
geom2d_cartesian_point_to_geometry(geom2d_cartesian_point_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_geometry_t{t->handle};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_geometry_t *geom2d_vector_to_geometry(geom2d_vector_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_geometry_t{t->handle};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_geometry_t *geom2d_direction_to_geometry(geom2d_direction_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_geometry_t{t->handle};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_geometry_t *
geom2d_vector_with_magnitude_to_geometry(geom2d_vector_with_magnitude_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_geometry_t{t->handle};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_axis_placement_t *geom_axis_placement_from_geometry(geom_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_AxisPlacement)) {
    return nullptr;
  }
  return new geom_axis_placement_t{
      Handle(Geom_AxisPlacement)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_axis1_placement_t *geom_axis1_placement_from_geometry(geom_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_Axis1Placement)) {
    return nullptr;
  }
  return new geom_axis1_placement_t{
      Handle(Geom_Axis1Placement)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_axis2_placement_t *geom_axis2_placement_from_geometry(geom_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_Axis2Placement)) {
    return nullptr;
  }
  return new geom_axis2_placement_t{
      Handle(Geom_Axis2Placement)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_curve_t *geom_curve_from_geometry(geom_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_Curve)) {
    return nullptr;
  }
  return new geom_curve_t{.handle = Handle(Geom_Curve)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_bounded_curve_t *geom_bounded_curve_from_geometry(geom_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_BoundedCurve)) {
    return nullptr;
  }
  return new geom_bounded_curve_t{
      Handle(Geom_BoundedCurve)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_bezier_curve_t *geom_bezier_curve_from_geometry(geom_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_BezierCurve)) {
    return nullptr;
  }
  return new geom_bezier_curve_t{Handle(Geom_BezierCurve)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_bspline_curve_t *geom_bspline_curve_from_geometry(geom_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_BSplineCurve)) {
    return nullptr;
  }
  return new geom_bspline_curve_t{
      Handle(Geom_BSplineCurve)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}
geom_bspline_curve_t *geom_bspline_curve_from_points(pnt3d_t *t, int size) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_trimmed_curve_t *geom_trimmed_curve_from_geometry(geom_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_TrimmedCurve)) {
    return nullptr;
  }
  return new geom_trimmed_curve_t{
      Handle(Geom_TrimmedCurve)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_conic_t *geom_conic_from_geometry(geom_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_Conic)) {
    return nullptr;
  }
  return new geom_conic_t{Handle(Geom_Conic)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_circle_t *geom_circle_from_geometry(geom_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_Circle)) {
    return nullptr;
  }
  return new geom_circle_t{Handle(Geom_Circle)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_ellipse_t *geom_ellipse_from_geometry(geom_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_Ellipse)) {
    return nullptr;
  }
  return new geom_ellipse_t{Handle(Geom_Ellipse)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_hyperbola_t *geom_hyperbola_from_geometry(geom_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_Hyperbola)) {
    return nullptr;
  }
  return new geom_hyperbola_t{Handle(Geom_Hyperbola)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_parabola_t *geom_parabola_from_geometry(geom_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_Parabola)) {
    return nullptr;
  }
  return new geom_parabola_t{Handle(Geom_Parabola)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_line_t *geom_line_from_geometry(geom_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_Line)) {
    return nullptr;
  }
  return new geom_line_t{Handle(Geom_Line)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_offset_curve_t *geom_offset_curve_from_geometry(geom_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_OffsetCurve)) {
    return nullptr;
  }
  return new geom_offset_curve_t{Handle(Geom_OffsetCurve)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_point_t *geom_point_from_geometry(geom_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_Point)) {
    return nullptr;
  }
  return new geom_point_t{Handle(Geom_Point)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_cartesian_point_t *geom_cartesian_point_from_geometry(geom_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_CartesianPoint)) {
    return nullptr;
  }
  return new geom_cartesian_point_t{
      Handle(Geom_CartesianPoint)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_surface_t *geom_surface_from_geometry(geom_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_Surface)) {
    return nullptr;
  }
  return new geom_surface_t{Handle(Geom_Surface)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_bounded_surface_t *geom_bounded_surface_from_geometry(geom_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_BoundedSurface)) {
    return nullptr;
  }
  return new geom_bounded_surface_t{
      Handle(Geom_BoundedSurface)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_bezier_surface_t *geom_bezier_surface_from_geometry(geom_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_BezierSurface)) {
    return nullptr;
  }
  return new geom_bezier_surface_t{
      Handle(Geom_BezierSurface)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_bspline_surface_t *geom_bspline_surface_from_geometry(geom_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_BSplineSurface)) {
    return nullptr;
  }
  return new geom_bspline_surface_t{
      Handle(Geom_BSplineSurface)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_rectangular_trimmed_surface_t *
geom_rectangular_trimmed_surface_from_geometry(geom_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t->handle->DynamicType() !=
      STANDARD_TYPE(Geom_RectangularTrimmedSurface)) {
    return nullptr;
  }
  return new geom_rectangular_trimmed_surface_t{
      Handle(Geom_RectangularTrimmedSurface)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_elementary_surface_t *
geom_elementary_surface_from_geometry(geom_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_ElementarySurface)) {
    return nullptr;
  }
  return new geom_elementary_surface_t{
      Handle(Geom_ElementarySurface)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_cylindrical_surface_t *
geom_cylindrical_surface_from_geometry(geom_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_CylindricalSurface)) {
    return nullptr;
  }
  return new geom_cylindrical_surface_t{
      Handle(Geom_CylindricalSurface)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_plane_surface_t *geom_plane_surface_from_geometry(geom_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_Plane)) {
    return nullptr;
  }
  return new geom_plane_surface_t{Handle(Geom_Plane)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_conical_surface_t *geom_conical_surface_from_geometry(geom_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_ConicalSurface)) {
    return nullptr;
  }
  return new geom_conical_surface_t{
      Handle(Geom_ConicalSurface)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_spherical_surface_t *
geom_spherical_surface_from_geometry(geom_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_SphericalSurface)) {
    return nullptr;
  }
  return new geom_spherical_surface_t{
      Handle(Geom_SphericalSurface)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_toroidal_surface_t *
geom_toroidal_surface_from_geometry(geom_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_ToroidalSurface)) {
    return nullptr;
  }
  return new geom_toroidal_surface_t{
      Handle(Geom_ToroidalSurface)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_offset_surface_t *geom_offset_surface_from_geometry(geom_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_OffsetSurface)) {
    return nullptr;
  }
  return new geom_offset_surface_t{
      Handle(Geom_OffsetSurface)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_swept_surface_t *geom_swept_surface_from_geometry(geom_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_SweptSurface)) {
    return nullptr;
  }
  return new geom_swept_surface_t{
      Handle(Geom_SweptSurface)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_surface_of_linear_extrusion_t *
geom_surface_of_linear_extrusion_from_geometry(geom_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t->handle->DynamicType() !=
      STANDARD_TYPE(Geom_SurfaceOfLinearExtrusion)) {
    return nullptr;
  }
  return new geom_surface_of_linear_extrusion_t{
      Handle(Geom_SurfaceOfLinearExtrusion)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_surface_of_revolution_extrusion_t *
geom_surface_of_revolution_extrusion_from_geometry(geom_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_SurfaceOfRevolution)) {
    return nullptr;
  }
  return new geom_surface_of_revolution_extrusion_t{
      Handle(Geom_SurfaceOfRevolution)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_plate_surface_t *geom_plate_surface_from_geometry(geom_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t->handle->DynamicType() != STANDARD_TYPE(GeomPlate_Surface)) {
    return nullptr;
  }
  return new geom_plate_surface_t{
      Handle(GeomPlate_Surface)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_vector_t *geom_vector_from_geometry(geom_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_Vector)) {
    return nullptr;
  }
  return new geom_vector_t{Handle(Geom_Vector)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_direction_t *geom_direction_from_geometry(geom_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_Direction)) {
    return nullptr;
  }
  return new geom_direction_t{Handle(Geom_Direction)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_vector_with_magnitude_t *
geom_vector_with_magnitude_from_geometry(geom_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom_VectorWithMagnitude)) {
    return nullptr;
  }
  return new geom_vector_with_magnitude_t{
      Handle(Geom_VectorWithMagnitude)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_axis_placement_t *
geom2d_axis_placement_from_geometry(geom2d_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom2d_AxisPlacement)) {
    return nullptr;
  }
  return new geom2d_axis_placement_t{
      Handle(Geom2d_AxisPlacement)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_curve_t *geom2d_curve_from_geometry(geom2d_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom2d_Curve)) {
    return nullptr;
  }
  return new geom2d_curve_t{Handle(Geom2d_Curve)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_bisector_curve_t *
geom2d_bisector_curve_from_geometry(geom2d_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t->handle->DynamicType() != STANDARD_TYPE(Bisector_Curve)) {
    return nullptr;
  }
  return new geom2d_bisector_curve_t{
      Handle(Bisector_Curve)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_bezier_bisec_ana_curve_t *
geom2d_bezier_bisec_ana_curve_from_geometry(geom2d_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t->handle->DynamicType() != STANDARD_TYPE(Bisector_BisecAna)) {
    return nullptr;
  }
  return new geom2d_bezier_bisec_ana_curve_t{
      Handle(Bisector_BisecAna)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_bezier_bisec_cc_curve_t *
geom2d_bezier_bisec_cc_curve_from_geometry(geom2d_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t->handle->DynamicType() != STANDARD_TYPE(Bisector_BisecCC)) {
    return nullptr;
  }
  return new geom2d_bezier_bisec_cc_curve_t{
      Handle(Bisector_BisecCC)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_bezier_bisec_pc_curve_t *
geom2d_bezier_bisec_pc_curve_from_geometry(geom2d_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t->handle->DynamicType() != STANDARD_TYPE(Bisector_BisecPC)) {
    return nullptr;
  }
  return new geom2d_bezier_bisec_pc_curve_t{
      Handle(Bisector_BisecPC)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_bounded_curve_t *
geom2d_bounded_curve_from_geometry(geom2d_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom2d_BoundedCurve)) {
    return nullptr;
  }
  return new geom2d_bounded_curve_t{
      Handle(Geom2d_BoundedCurve)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_bezier_curve_t *geom2d_bezier_curve_from_geometry(geom2d_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom2d_BezierCurve)) {
    return nullptr;
  }
  return new geom2d_bezier_curve_t{
      Handle(Geom2d_BezierCurve)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_bspline_curve_t *
geom2d_bspline_curve_from_geometry(geom2d_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom2d_BSplineCurve)) {
    return nullptr;
  }
  return new geom2d_bspline_curve_t{
      Handle(Geom2d_BSplineCurve)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_trimmed_curve_t *
geom2d_trimmed_curve_from_geometry(geom2d_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom2d_TrimmedCurve)) {
    return nullptr;
  }
  return new geom2d_trimmed_curve_t{
      Handle(Geom2d_TrimmedCurve)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_conic_t *geom2d_conic_from_geometry(geom2d_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom2d_Conic)) {
    return nullptr;
  }
  return new geom2d_conic_t{Handle(Geom2d_Conic)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_circle_t *geom2d_circle_from_geometry(geom2d_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom2d_Circle)) {
    return nullptr;
  }
  return new geom2d_circle_t{Handle(Geom2d_Circle)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_ellipse_t *geom2d_ellipse_from_geometry(geom2d_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom2d_Ellipse)) {
    return nullptr;
  }
  return new geom2d_ellipse_t{Handle(Geom2d_Ellipse)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_hyperbola_t *geom2d_hyperbola_from_geometry(geom2d_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom2d_Hyperbola)) {
    return nullptr;
  }
  return new geom2d_hyperbola_t{Handle(Geom2d_Hyperbola)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_parabola_t *geom2d_parabola_from_geometry(geom2d_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom2d_Parabola)) {
    return nullptr;
  }
  return new geom2d_parabola_t{Handle(Geom2d_Parabola)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_line_t *geom2d_line_from_geometry(geom2d_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom2d_Line)) {
    return nullptr;
  }
  return new geom2d_line_t{Handle(Geom2d_Line)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_offset_curve_t *geom2d_offset_curve_from_geometry(geom2d_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom2d_OffsetCurve)) {
    return nullptr;
  }
  return new geom2d_offset_curve_t{
      Handle(Geom2d_OffsetCurve)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_point_t *geom2d_point_from_geometry(geom2d_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom2d_Point)) {
    return nullptr;
  }
  return new geom2d_point_t{Handle(Geom2d_Point)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_cartesian_point_t *
geom2d_cartesian_point_from_geometry(geom2d_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom2d_CartesianPoint)) {
    return nullptr;
  }
  return new geom2d_cartesian_point_t{
      Handle(Geom2d_CartesianPoint)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_vector_t *geom2d_vector_from_geometry(geom2d_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom2d_Vector)) {
    return nullptr;
  }
  return new geom2d_vector_t{Handle(Geom2d_Vector)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_direction_t *geom2d_direction_from_geometry(geom2d_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom2d_Direction)) {
    return nullptr;
  }
  return new geom2d_direction_t{Handle(Geom2d_Direction)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_vector_with_magnitude_t *
geom2d_vector_with_magnitude_from_geometry(geom2d_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t->handle->DynamicType() != STANDARD_TYPE(Geom2d_VectorWithMagnitude)) {
    return nullptr;
  }
  return new geom2d_vector_with_magnitude_t{
      .handle = Handle(Geom2d_VectorWithMagnitude)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_curve_t *geom_bounded_curve_to_geom_curve(geom_bounded_curve_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_curve_t{.handle = Handle(Geom_Curve)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_curve_t *geom_bezier_curve_to_geom_curve(geom_bezier_curve_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_curve_t{.handle = Handle(Geom_Curve)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_curve_t *geom_bspline_curve_to_geom_curve(geom_bspline_curve_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_curve_t{.handle = Handle(Geom_Curve)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_curve_t *geom_trimmed_curve_to_geom_curve(geom_trimmed_curve_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_curve_t{.handle = Handle(Geom_Curve)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_curve_t *geom_conic_to_geom_curve(geom_conic_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_curve_t{.handle = Handle(Geom_Curve)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_curve_t *geom_circle_to_geom_curve(geom_circle_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_curve_t{.handle = Handle(Geom_Curve)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_curve_t *geom_ellipse_to_geom_curve(geom_ellipse_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_curve_t{.handle = Handle(Geom_Curve)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_curve_t *geom_hyperbola_to_geom_curve(geom_hyperbola_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_curve_t{Handle(Geom_Curve)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_curve_t *geom_parabola_to_geom_curve(geom_parabola_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_curve_t{.handle = Handle(Geom_Curve)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_curve_t *geom_line_to_geom_curve(geom_line_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_curve_t{.handle = Handle(Geom_Curve)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_curve_t *geom_offset_curve_to_geom_curve(geom_offset_curve_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_curve_t{.handle = Handle(Geom_Curve)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_surface_t *
geom_bounded_surface_to_geom_surface(geom_bounded_surface_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_surface_t{Handle(Geom_Surface)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_surface_t *geom_bezier_surface_to_geom_surface(geom_bezier_surface_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_surface_t{Handle(Geom_Surface)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_surface_t *
geom_bspline_surface_to_geom_surface(geom_bspline_surface_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_surface_t{Handle(Geom_Surface)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_surface_t *geom_rectangular_trimmed_surface_to_geom_surface(
    geom_rectangular_trimmed_surface_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_surface_t{Handle(Geom_Surface)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_surface_t *
geom_elementary_surface_to_geom_surface(geom_elementary_surface_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_surface_t{Handle(Geom_Surface)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_surface_t *
geom_cylindrical_surface_to_geom_surface(geom_cylindrical_surface_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_surface_t{Handle(Geom_Surface)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_surface_t *geom_plane_surface_to_geom_surface(geom_plane_surface_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_surface_t{Handle(Geom_Surface)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_surface_t *
geom_conical_surface_to_geom_surface(geom_conical_surface_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_surface_t{Handle(Geom_Surface)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_surface_t *
geom_spherical_surface_to_geom_surface(geom_spherical_surface_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_surface_t{Handle(Geom_Surface)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_surface_t *
geom_toroidal_surface_to_geom_surface(geom_toroidal_surface_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_surface_t{Handle(Geom_Surface)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_surface_t *geom_offset_surface_to_geom_surface(geom_offset_surface_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_surface_t{Handle(Geom_Surface)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_surface_t *geom_swept_surface_to_geom_surface(geom_swept_surface_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_surface_t{Handle(Geom_Surface)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_surface_t *geom_surface_of_linear_extrusion_to_geom_surface(
    geom_surface_of_linear_extrusion_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_surface_t{Handle(Geom_Surface)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_surface_t *geom_surface_of_revolution_extrusion_to_geom_surface(
    geom_surface_of_revolution_extrusion_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_surface_t{Handle(Geom_Surface)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_surface_t *geom_plate_surface_to_geom_surface(geom_plate_surface_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_surface_t{Handle(Geom_Surface)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_curve_t *
geom2d_bisector_curve_to_geom2d_curve(geom2d_bisector_curve_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_curve_t{Handle(Geom2d_Curve)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_curve_t *geom2d_bezier_bisec_ana_curve_to_geom2d_curve(
    geom2d_bezier_bisec_ana_curve_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_curve_t{Handle(Geom2d_Curve)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_curve_t *geom2d_bezier_bisec_cc_curve_to_geom2d_curve(
    geom2d_bezier_bisec_cc_curve_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_curve_t{Handle(Geom2d_Curve)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_curve_t *geom2d_bezier_bisec_pc_curve_to_geom2d_curve(
    geom2d_bezier_bisec_pc_curve_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_curve_t{Handle(Geom2d_Curve)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_curve_t *
geom2d_bounded_curve_to_geom2d_curve(geom2d_bounded_curve_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_curve_t{Handle(Geom2d_Curve)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_curve_t *geom2d_bezier_curve_to_geom2d_curve(geom2d_bezier_curve_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_curve_t{Handle(Geom2d_Curve)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_curve_t *
geom2d_bspline_curve_to_geom2d_curve(geom2d_bspline_curve_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_curve_t{Handle(Geom2d_Curve)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_curve_t *
geom2d_trimmed_curve_to_geom2d_curve(geom2d_trimmed_curve_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_curve_t{Handle(Geom2d_Curve)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_curve_t *geom2d_conic_to_geom2d_curve(geom2d_conic_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_curve_t{Handle(Geom2d_Curve)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_curve_t *geom2d_circle_to_geom2d_curve(geom2d_circle_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_curve_t{Handle(Geom2d_Curve)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_curve_t *geom2d_ellipse_to_geom2d_curve(geom2d_ellipse_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_curve_t{Handle(Geom2d_Curve)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_curve_t *geom2d_hyperbola_to_geom2d_curve(geom2d_hyperbola_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_curve_t{Handle(Geom2d_Curve)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_curve_t *geom2d_parabola_to_geom2d_curve(geom2d_parabola_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_curve_t{Handle(Geom2d_Curve)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_curve_t *geom2d_line_to_geom2d_curve(geom2d_line_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_curve_t{Handle(Geom2d_Curve)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_curve_t *geom2d_offset_curve_to_geom2d_curve(geom2d_offset_curve_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_curve_t{Handle(Geom2d_Curve)::DownCast(t->handle)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

void geom_apply_mirror_with_point(geom_geometry_t *t, pnt3d_t P) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t) {
    t->handle->Mirror(cast_to_gp(P));
  }
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

void geom_apply_mirror_with_axis1(geom_geometry_t *t, axis1_t A1) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t) {
    t->handle->Mirror(cast_to_gp(A1));
  }
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

void geom_apply_mirror_with_axis2(geom_geometry_t *t, axis2_t A2) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t) {
    t->handle->Mirror(cast_to_gp(A2));
  }
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

void geom_apply_rotate(geom_geometry_t *t, axis1_t A1, double Ang) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t) {
    t->handle->Rotate(cast_to_gp(A1), Ang);
  }
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

void geom_apply_scale(geom_geometry_t *t, pnt3d_t P, double S) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t) {
    t->handle->Scale(cast_to_gp(P), S);
  }
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

void geom_apply_translate_with_vector(geom_geometry_t *t, vec3d_t V) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t) {
    t->handle->Translate(cast_to_gp(V));
  }
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

void geom_apply_translate_with_point(geom_geometry_t *t, pnt3d_t P1,
                                     pnt3d_t P2) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t) {
    t->handle->Translate(cast_to_gp(P1), cast_to_gp(P2));
  }
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

void geom_apply_transform(geom_geometry_t *t, trsf_t tr) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t) {
    t->handle->Transform(cast_to_gp(tr));
  }
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

geom_geometry_t *geom_mirror_with_point(geom_geometry_t *t, pnt3d_t P) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t) {
    return new geom_geometry_t{t->handle->Mirrored(cast_to_gp(P))};
  }
  return nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_geometry_t *geom_mirror_with_axis1(geom_geometry_t *t, axis1_t A1) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t) {
    return new geom_geometry_t{t->handle->Mirrored(cast_to_gp(A1))};
  }
  return nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_geometry_t *geom_mirror_with_axis2(geom_geometry_t *t, axis2_t A2) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t) {
    return new geom_geometry_t{t->handle->Mirrored(cast_to_gp(A2))};
  }
  return nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_geometry_t *geom_rotate(geom_geometry_t *t, axis1_t A1, double Ang) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t) {
    return new geom_geometry_t{t->handle->Rotated(cast_to_gp(A1), Ang)};
  }
  return nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_geometry_t *geom_scale(geom_geometry_t *t, pnt3d_t P, double S) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t) {
    return new geom_geometry_t{t->handle->Scaled(cast_to_gp(P), S)};
  }
  return nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_geometry_t *geom_translate_with_vector(geom_geometry_t *t, vec3d_t V) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t) {
    return new geom_geometry_t{t->handle->Translated(cast_to_gp(V))};
  }
  return nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_geometry_t *geom_translate_with_point(geom_geometry_t *t, pnt3d_t P1,
                                           pnt3d_t P2) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t) {
    return new geom_geometry_t{
        t->handle->Translated(cast_to_gp(P1), cast_to_gp(P2))};
  }
  return nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_geometry_t *geom_transform(geom_geometry_t *t, trsf_t tr) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t) {
    return new geom_geometry_t{t->handle->Transformed(cast_to_gp(tr))};
  }
  return nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

void geom2d_apply_mirror_with_point(geom2d_geometry_t *t, pnt2d_t P) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t) {
    t->handle->Mirror(cast_to_gp(P));
  }
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

void geom2d_apply_mirror_with_axis2(geom2d_geometry_t *t, axis2d_t A2) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t) {
    t->handle->Mirror(cast_to_gp(A2));
  }
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

void geom2d_apply_rotate(geom2d_geometry_t *t, pnt2d_t P, double Ang) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t) {
    t->handle->Rotate(cast_to_gp(P), Ang);
  }
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

void geom2d_apply_scale(geom2d_geometry_t *t, pnt2d_t P, double S) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t) {
    t->handle->Scale(cast_to_gp(P), S);
  }
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

void geom2d_apply_translate_with_vector(geom2d_geometry_t *t, vec2d_t V) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t) {
    t->handle->Translate(cast_to_gp(V));
  }
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

void geom2d_apply_translate_with_point(geom2d_geometry_t *t, pnt2d_t P1,
                                       pnt2d_t P2) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t) {
    t->handle->Translate(cast_to_gp(P1), cast_to_gp(P2));
  }
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

void geom2d_apply_transform(geom2d_geometry_t *t, trsf2d_t tr) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t) {
    t->handle->Transform(cast_to_gp(tr));
  }
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

geom2d_geometry_t *geom2d_mirror_with_point(geom2d_geometry_t *t, pnt2d_t P) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t) {
    return new geom2d_geometry_t{t->handle->Mirrored(cast_to_gp(P))};
  }
  return nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_geometry_t *geom2d_mirror_with_axis2(geom2d_geometry_t *t, axis2d_t A2) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t) {
    return new geom2d_geometry_t{t->handle->Mirrored(cast_to_gp(A2))};
  }
  return nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_geometry_t *geom2d_rotate(geom2d_geometry_t *t, pnt2d_t P, double Ang) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t) {
    return new geom2d_geometry_t{t->handle->Rotated(cast_to_gp(P), Ang)};
  }
  return nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_geometry_t *geom2d_scale(geom2d_geometry_t *t, pnt2d_t P, double S) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t) {
    return new geom2d_geometry_t{t->handle->Scaled(cast_to_gp(P), S)};
  }
  return nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_geometry_t *geom2d_translate_with_vector(geom2d_geometry_t *t,
                                                vec2d_t V) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t) {
    return new geom2d_geometry_t{t->handle->Translated(cast_to_gp(V))};
  }
  return nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_geometry_t *geom2d_translate_with_point(geom2d_geometry_t *t, pnt2d_t P1,
                                               pnt2d_t P2) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t) {
    return new geom2d_geometry_t{
        t->handle->Translated(cast_to_gp(P1), cast_to_gp(P2))};
  }
  return nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_geometry_t *geom2d_transform(geom2d_geometry_t *t, trsf2d_t tr) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (t) {
    return new geom2d_geometry_t{t->handle->Transformed(cast_to_gp(tr))};
  }
  return nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

int geom_geometry_type(geom_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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
  catch (const std::exception &e) {
    (void)e;
    return -1;
  }
  catch (...) {
    return -1;
  }
}

int geom2d_geometry_type(geom2d_geometry_t *t) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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
  catch (const std::exception &e) {
    (void)e;
    return -1;
  }
  catch (...) {
    return -1;
  }
}

geom_axis1_placement_t *geom_make_axis1_placement(axis1_t A1) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_axis1_placement_t{new Geom_Axis1Placement(cast_to_gp(A1))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_axis1_placement_t *geom_make_axis1_placement_of_point_dir(pnt3d_t P,
                                                               dir3d_t V) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_axis1_placement_t{
      new Geom_Axis1Placement(cast_to_gp(P), cast_to_gp(V))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_axis2_placement_t *geom_make_axis2_placement(axis2_t A2) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_axis2_placement_t{new Geom_Axis2Placement(cast_to_gp(A2))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_axis2_placement_t *
geom_make_axis2_placement_of_point_nvx(pnt3d_t P, dir3d_t N, dir3d_t VX) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_axis2_placement_t{
      new Geom_Axis2Placement(cast_to_gp(P), cast_to_gp(N), cast_to_gp(VX))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_bezier_curve_t *geom_make_bezier_curve(pnt3d_t *CurvePoles, int count) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  TColgp_Array1OfPnt pnts{0, static_cast<Standard_Integer>(count)};
  for (int i = 0; i < count; i++) {
    pnts.SetValue(i, cast_to_gp(CurvePoles[i]));
  }
  return new geom_bezier_curve_t{new Geom_BezierCurve(pnts)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_bezier_curve_t *geom_make_bezier_curve_from_weight(pnt3d_t *CurvePoles,
                                                        double *PoleWeights,
                                                        int count) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  TColgp_Array1OfPnt pnts{0, static_cast<Standard_Integer>(count)};
  TColStd_Array1OfReal wei{0, static_cast<Standard_Integer>(count)};
  for (int i = 0; i < count; i++) {
    pnts.SetValue(i, cast_to_gp(CurvePoles[i]));
    wei.SetValue(i, PoleWeights[i]);
  }
  return new geom_bezier_curve_t{new Geom_BezierCurve(pnts, wei)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_bspline_curve_t *geom_make_bspline_curve(pnt3d_t *Poles, double *Knots,
                                              int *Multiplicities, int count,
                                              int Degree, _Bool Periodic) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_bspline_curve_t *geom_make_bspline_curve_from_weight(
    pnt3d_t *Poles, double *Weights, double *Knots, int *Multiplicities,
    int count, int Degree, _Bool Periodic, _Bool CheckRational) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_bezier_surface_t *geom_make_bezier_surface(pnt3d_t *SurfacePoles, int row,
                                                int col) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  TColgp_Array2OfPnt pnt{0, static_cast<Standard_Integer>(col), 0,
                         static_cast<Standard_Integer>(row)};
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      pnt.SetValue(i, j, cast_to_gp(SurfacePoles[i * col + j]));
    }
  }
  return new geom_bezier_surface_t{new Geom_BezierSurface(pnt)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_bezier_surface_t *
geom_make_bezier_surface_from_weight(pnt3d_t *SurfacePoles, double *PoleWeights,
                                     int row, int col) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_bspline_surface_t *
geom_make_bspline_surface(pnt3d_t *Poles, double *UKnots, double *VKnots,
                          int *UMults, int *VMults, int row, int col,
                          int UCount, int VCount, int UDegree, int VDegree,
                          _Bool UPeriodic, _Bool VPeriodic) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_bspline_surface_t *geom_make_bspline_surface_from_weight(
    pnt3d_t *Poles, double *Weights, double *UKnots, double *VKnots,
    int *UMults, int *VMults, int row, int col, int UCount, int VCount,
    int UDegree, int VDegree, _Bool UPeriodic, _Bool VPeriodic) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_rectangular_trimmed_surface_t *
geom_make_rectangular_trimmed_surface_from_lrud(geom_surface_t *S, double U1,
                                                double U2, double V1, double V2,
                                                _Bool USense, _Bool VSense) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {

  return new geom_rectangular_trimmed_surface_t{
      new Geom_RectangularTrimmedSurface(S->handle, U1, U2, V1, V2, USense,
                                         VSense)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_rectangular_trimmed_surface_t *
geom_make_rectangular_trimmed_surface(geom_surface_t *S, double Param1,
                                      double Param2, _Bool UTrim, _Bool Sense) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_rectangular_trimmed_surface_t{
      new Geom_RectangularTrimmedSurface(S->handle, Param1, Param2, UTrim,
                                         Sense)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_surface_of_linear_extrusion_t *
geom_make_surface_of_linear_extrusion(geom_curve_t *C, dir3d_t V) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_surface_of_linear_extrusion_t{
      new Geom_SurfaceOfLinearExtrusion(C->handle, cast_to_gp(V))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_surface_of_revolution_extrusion_t *
geom_make_surface_of_revolution_extrusion(geom_curve_t *C, axis1_t V) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_surface_of_revolution_extrusion_t{
      new Geom_SurfaceOfRevolution(C->handle, cast_to_gp(V))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_direction_t *geom_make_direction(double X, double Y, double Z) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_direction_t{new Geom_Direction(X, Y, Z)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_direction_t *geom_make_direction_with_dir(dir3d_t V) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_direction_t{new Geom_Direction(cast_to_gp(V))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_vector_with_magnitude_t *
geom_make_vector_with_magnitude_with_vector(vec3d_t V) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_vector_with_magnitude_t{
      new Geom_VectorWithMagnitude(cast_to_gp(V))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_vector_with_magnitude_t *
geom_make_vector_with_magnitude_with_xyz(double X, double Y, double Z) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_vector_with_magnitude_t{
      new Geom_VectorWithMagnitude(X, Y, Z)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_vector_with_magnitude_t *
geom_make_vector_with_magnitude_with_point(pnt3d_t P1, pnt3d_t P2) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_vector_with_magnitude_t{
      new Geom_VectorWithMagnitude(cast_to_gp(P1), cast_to_gp(P2))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom_plate_surface_t *geom_make_plate_surface(geom_surface_t *Surfinit,
                                              plate_plate_t *Surfinter) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom_plate_surface_t{
      new GeomPlate_Surface(Surfinit->handle, Surfinter->pp)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_axis_placement_t *geom2d_make_axis_placement(axis2d_t A) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_axis_placement_t{new Geom2d_AxisPlacement(cast_to_gp(A))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_axis_placement_t *geom2d_make_axis_placement_from_point(pnt2d_t P,
                                                               dir2d_t V) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_axis_placement_t{
      new Geom2d_AxisPlacement(cast_to_gp(P), cast_to_gp(V))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_bezier_bisec_cc_curve_t *
geom2d_make_bezier_bisec_cc_curve(geom2d_curve_t *Cu1, geom2d_curve_t *Cu2,
                                  double Side1, double Side2, pnt2d_t Origin,
                                  double DistMax) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_bezier_bisec_cc_curve_t{new Bisector_BisecCC(
      Cu1->handle, Cu2->handle, Side1, Side2, cast_to_gp(Origin), DistMax)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_bezier_bisec_pc_curve_t *
geom2d_make_bezier_bisec_pc_curve_with_dist(geom2d_curve_t *Cu, pnt2d_t P,
                                            double Side, double DistMax) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_bezier_bisec_pc_curve_t{
      new Bisector_BisecPC(Cu->handle, cast_to_gp(P), Side, DistMax)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_bezier_bisec_pc_curve_t *
geom2d_make_bezier_bisec_pc_curve(geom2d_curve_t *Cu, pnt2d_t P, double Side,
                                  double UMin, double UMax) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_bezier_bisec_pc_curve_t{
      new Bisector_BisecPC(Cu->handle, cast_to_gp(P), Side, UMin, UMax)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_bezier_curve_t *geom2d_make_bezier_curve(pnt2d_t *CurvePoles,
                                                int count) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  TColgp_Array1OfPnt2d pnts{0, static_cast<Standard_Integer>(count)};
  for (int i = 0; i < count; i++) {
    pnts.SetValue(i, cast_to_gp(CurvePoles[i]));
  }
  return new geom2d_bezier_curve_t{new Geom2d_BezierCurve(pnts)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_bezier_curve_t *geom2d_make_bezier_curve_with_weight(pnt2d_t *CurvePoles,
                                                            double *PoleWeights,
                                                            int count) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  TColgp_Array1OfPnt2d pnts{0, static_cast<Standard_Integer>(count)};
  TColStd_Array1OfReal wei{0, static_cast<Standard_Integer>(count)};
  for (int i = 0; i < count; i++) {
    pnts.SetValue(i, cast_to_gp(CurvePoles[i]));
    wei.SetValue(i, PoleWeights[i]);
  }
  return new geom2d_bezier_curve_t{new Geom2d_BezierCurve(pnts, wei)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_bspline_curve_t *geom2d_make_bspline_curve(pnt2d_t *Poles, double *Knots,
                                                  int *Multiplicities,
                                                  int Count, int Degree,
                                                  _Bool Periodic) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_bspline_curve_t *
geom2d_make_bspline_curve_with_weight(pnt2d_t *CurvePoles, double *Weights,
                                      double *Knots, int *Multiplicities,
                                      int Count, int Degree, _Bool Periodic) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
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
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_trimmed_curve_t *geom2d_make_trimmed_curve(geom2d_curve_t *C, double U1,
                                                  double U2, _Bool Sense,
                                                  _Bool theAdjustPeriodic) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_trimmed_curve_t{
      new Geom2d_TrimmedCurve(C->handle, U1, U2, Sense, theAdjustPeriodic)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_offset_curve_t *
geom2d_make_offset_curve(geom2d_curve_t *C, double Offset, _Bool isNotCheckC0) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_offset_curve_t{
      new Geom2d_OffsetCurve(C->handle, Offset, isNotCheckC0)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_cartesian_point_t *geom2d_make_cartesian_point(pnt2d_t P) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_cartesian_point_t{new Geom2d_CartesianPoint(cast_to_gp(P))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_cartesian_point_t *geom2d_make_cartesian_point_xy(double X, double Y) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_cartesian_point_t{new Geom2d_CartesianPoint(X, Y)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_direction_t *geom2d_make_direction(double X, double Y) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_direction_t{new Geom2d_Direction(X, Y)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_direction_t *geom2d_make_direction_with_dir(dir2d_t V) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_direction_t{new Geom2d_Direction(cast_to_gp(V))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_vector_with_magnitude_t *
geom2d_make_vector_with_magnitude_with_vector(vec2d_t V) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_vector_with_magnitude_t{
      new Geom2d_VectorWithMagnitude(cast_to_gp(V))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_vector_with_magnitude_t *
geom2d_make_vector_with_magnitude_with_xy(double X, double Y) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_vector_with_magnitude_t{
      new Geom2d_VectorWithMagnitude(X, Y)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

geom2d_vector_with_magnitude_t *
geom2d_make_vector_with_magnitude_with_point(pnt2d_t P1, pnt2d_t P2) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new geom2d_vector_with_magnitude_t{
      new Geom2d_VectorWithMagnitude(cast_to_gp(P1), cast_to_gp(P2))};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

#ifdef __cplusplus
}
#endif
