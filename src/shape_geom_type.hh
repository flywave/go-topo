#pragma once

namespace flywave {
namespace topo {

enum shape_geom_type {
  shape_geom_null,
  shape_geom_vertex,
  shape_geom_wire,
  shape_geom_shell,
  shape_geom_solid,
  shape_geom_compsolid,
  shape_geom_compound,
  shape_geom_line,
  shape_geom_circle,
  shape_geom_hyperbola,
  shape_geom_parabola,
  shape_geom_ellipse,
  shape_geom_bezier_curve,
  shape_geom_bspline_curve,
  shape_geom_offset_curve,
  shape_geom_other_curve,
  shape_geom_plane,
  shape_geom_cylinder,
  shape_geom_cone,
  shape_geom_sphere,
  shape_geom_torus,
  shape_geom_bezier_surface,
  shape_geom_bspline_surface,
  shape_geom_offset_surface,
  shape_geom_other_surface,
  shape_geom_revolved_surface,
  shape_geom_extruded_surface,
};
} // namespace topo
} // namespace flywave
