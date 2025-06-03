#include "topo_c_api.h"
#include "geometry_impl.hh"
#include "shape.hh"
#include "shape_ops.hh"
#include "standard_impl.hh"
#include "topo_impl.hh"

#include <memory>
#include <string>
#include <vector>
#ifdef __cplusplus
extern "C" {
#endif

void topo_shape_free(topo_shape_t *p) {
  if (p) {
    delete p;
  }
}

topo_shape_t *topo_shape_share(topo_shape_t *p) {
  if (p) {
    return new topo_shape_t{.shp = p->shp};
  }
  return nullptr;
}

topo_solid_t topo_make_solid() {
  return topo_solid_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::solid>()}};
}

_Bool topo_shape_is_null(topo_shape_t *p) {
  if (p) {
    return p->shp->is_null();
  }
  return false;
}

_Bool topo_shape_is_valid(topo_shape_t *p) {
  if (p) {
    return p->shp->is_valid();
  }
  return false;
}

_Bool topo_shape_equals(topo_shape_t *p, topo_shape_t *o) {
  if (p != NULL && o != NULL && p != o) {
    return p->shp->equals(*o->shp);
  }
  return true;
}

int topo_shape_type(topo_shape_t *p) {
  return static_cast<int>(p->shp->type());
}

bbox_t topo_shape_bounding_box(topo_shape_t *p) {
  auto b = p->shp->bounding_box();
  return cast_from_gp(b);
}

int topo_shape_hash_code(topo_shape_t *p) { return p->shp->hash_code(); }

int topo_shape_transform(topo_shape_t *p, trsf_t mat) {
  if (p) {
    auto t = cast_to_gp(mat);
    return p->shp->transform(t);
  }
  return -1;
}

int topo_shape_translate(topo_shape_t *p, vec3d_t delta) {
  if (p) {
    return p->shp->translate(cast_to_gp(delta));
  }
  return -1;
}

int topo_shape_rotate_from_two_point(topo_shape_t *p, double angle, pnt3d_t p1,
                                     pnt3d_t p2) {
  if (p) {
    return p->shp->rotate(angle, cast_to_gp(p1), cast_to_gp(p2));
  }
  return -1;
}

int topo_shape_rotate_from_axis1(topo_shape_t *p, double angle, axis1_t a) {
  if (p) {
    return p->shp->rotate(angle, cast_to_gp(a));
  }
  return -1;
}

int topo_shape_rotate_from_quaternion(topo_shape_t *p, quaternion_t q) {
  if (p) {
    return p->shp->rotate(cast_to_gp(q));
  }
  return -1;
}

int topo_shape_scale(topo_shape_t *p, double angle, pnt3d_t a) {
  if (p) {
    return p->shp->scale(cast_to_gp(a), angle);
  }
  return -1;
}

int topo_shape_mirror_from_point_norm(topo_shape_t *p, pnt3d_t pnt,
                                      pnt3d_t ner) {
  if (p) {
    return p->shp->mirror(cast_to_gp(pnt), cast_to_gp(ner));
  }
  return -1;
}

int topo_shape_mirror_from_axis1(topo_shape_t *p, axis1_t a) {
  if (p) {
    return p->shp->mirror(cast_to_gp(a));
  }
  return -1;
}

int topo_shape_mirror_from_axis2(topo_shape_t *p, axis2_t a) {
  if (p) {
    return p->shp->mirror(cast_to_gp(a));
  }
  return -1;
}

topo_shape_t *topo_shape_transformed(topo_shape_t *p, trsf_t mat) {
  if (p) {
    return new topo_shape_t{.shp = std::make_shared<flywave::topo::shape>(
                                p->shp->transformed(cast_to_gp(mat)))};
  }
  return nullptr;
}

topo_shape_t *topo_shape_translated(topo_shape_t *p, vec3d_t delta) {
  if (p) {
    return new topo_shape_t{.shp = std::make_shared<flywave::topo::shape>(
                                p->shp->translated(cast_to_gp(delta)))};
  }
  return nullptr;
}

topo_shape_t *topo_shape_rotated_from_two_point(topo_shape_t *p, double angle,
                                                pnt3d_t p1, pnt3d_t p2) {
  if (p) {
    return new topo_shape_t{
        .shp = std::make_shared<flywave::topo::shape>(
            p->shp->rotated(angle, cast_to_gp(p1), cast_to_gp(p2)))};
  }
  return nullptr;
}

topo_shape_t *topo_shape_rotated_from_axis1(topo_shape_t *p, double angle,
                                            axis1_t a) {
  if (p) {
    return new topo_shape_t{.shp = std::make_shared<flywave::topo::shape>(
                                p->shp->rotated(angle, cast_to_gp(a)))};
  }
  return nullptr;
}

topo_shape_t *topo_shape_rotated_from_quaternion(topo_shape_t *p,
                                                 quaternion_t q) {
  if (p) {
    return new topo_shape_t{.shp = std::make_shared<flywave::topo::shape>(
                                p->shp->rotated(cast_to_gp(q)))};
  }
  return nullptr;
}

topo_shape_t *topo_shape_scaled(topo_shape_t *p, double angle, pnt3d_t a) {
  if (p) {
    return new topo_shape_t{.shp = std::make_shared<flywave::topo::shape>(
                                p->shp->scaled(cast_to_gp(a), angle))};
  }
  return nullptr;
}

topo_shape_t *topo_shape_mirrored_from_point_norm(topo_shape_t *p, pnt3d_t pnt,
                                                  pnt3d_t ner) {
  if (p) {
    return new topo_shape_t{
        .shp = std::make_shared<flywave::topo::shape>(
            p->shp->mirrored(cast_to_gp(pnt), cast_to_gp(ner)))};
  }
  return nullptr;
}

topo_shape_t *topo_shape_mirrored_from_axis1(topo_shape_t *p, axis1_t a) {
  if (p) {
    return new topo_shape_t{.shp = std::make_shared<flywave::topo::shape>(
                                p->shp->mirrored(cast_to_gp(a)))};
  }
  return nullptr;
}

topo_shape_t *topo_shape_mirrored_from_axis2(topo_shape_t *p, axis2_t a) {
  if (p) {
    return new topo_shape_t{.shp = std::make_shared<flywave::topo::shape>(
                                p->shp->mirrored(cast_to_gp(a)))};
  }
  return nullptr;
}

int topo_shape_get_orientation(topo_shape_t *p) {
  return static_cast<int>(p->shp->get_orientation());
}

void topo_shape_set_orientation(topo_shape_t *p, int ori) {
  if (p) {
    p->shp->set_orientation(static_cast<flywave::topo::orientation>(ori));
  }
}

topo_location_t *topo_shape_get_location(topo_shape_t *p) {
  return new topo_location_t{.loc = p->shp->location()};
}

void topo_shape_set_location(topo_shape_t *p, topo_location_t *loc) {
  p->shp->set_location(loc->loc);
}

_Bool topo_shape_fix_shape(topo_shape_t *p) { return p->shp->fix_shape(); }

topo_shape_t *topo_shape_copy(topo_shape_t *p) {
  return new topo_shape_t{
      .shp = std::make_shared<flywave::topo::shape>(p->shp->copy())};
}

int topo_shape_mesh(topo_shape_t *p, topo_mesh_receiver_t *receiver,
                    double tolerance, double deflection, double angle,
                    _Bool uv_coords) {
  if (p) {
    return p->shp->write_triangulation(*receiver->recv, tolerance, deflection,
                                       angle, uv_coords);
  }
  return 1;
}

void topo_shape_set_surface_colour(topo_shape_t *p, color_t c) {
  if (p) {
    p->shp->set_surface_colour(cast_to_gp(c));
  }
}

void topo_shape_set_curve_colour(topo_shape_t *p, color_t c) {
  if (p) {
    p->shp->set_curve_colour(cast_to_gp(c));
  }
}

void topo_shape_set_label(topo_shape_t *p, const char *name) {
  if (p) {
    p->shp->set_label(name);
  }
}

void topo_shape_set_u_origin(topo_shape_t *p, double u) {
  if (p) {
    p->shp->set_u_origin(u);
  }
}

void topo_shape_set_v_origin(topo_shape_t *p, double v) {
  if (p) {
    p->shp->set_v_origin(v);
  }
}

void topo_shape_set_u_repeat(topo_shape_t *p, double u) {
  if (p) {
    p->shp->set_u_repeat(u);
  }
}

void topo_shape_set_v_repeat(topo_shape_t *p, double v) {
  if (p) {
    p->shp->set_v_repeat(v);
  }
}

void topo_shape_set_scale_v(topo_shape_t *p, double v) {
  if (p) {
    p->shp->set_scale_v(v);
  }
}

void topo_shape_set_scale_u(topo_shape_t *p, double u) {
  if (p) {
    p->shp->set_scale_u(u);
  }
}

void topo_shape_set_auto_scale_size_on_u(topo_shape_t *p, double u) {
  if (p) {
    p->shp->set_auto_scale_size_on_u(u);
  }
}

void topo_shape_set_auto_scale_size_on_v(topo_shape_t *p, double v) {
  if (p) {
    p->shp->set_auto_scale_size_on_v(v);
  }
}

void topo_shape_set_txture_map_type(topo_shape_t *p, int t) {
  if (p) {
    p->shp->set_txture_map_type(
        static_cast<flywave::topo::texture_mapping_rule>(t));
  }
}

void topo_shape_set_rotation_angle(topo_shape_t *p, double angle) {
  if (p) {
    p->shp->set_rotation_angle(angle);
  }
}

color_t topo_shape_get_surface_colour(topo_shape_t *p) {
  if (p) {
    return cast_from_gp(p->shp->surface_colour());
  }
  return color_t{0., 0., 0.};
}

color_t topo_shape_get_curve_colour(topo_shape_t *p) {
  if (p) {
    return cast_from_gp(p->shp->curve_colour());
  }
  return color_t{0., 0., 0.};
}

const char *topo_shape_get_label(topo_shape_t *p) {
  if (p) {
    return p->shp->label();
  }
  return nullptr;
}

double topo_shape_get_u_origin(topo_shape_t *p) {
  if (p) {
    return p->shp->get_u_origin();
  }
  return 0.;
}

double topo_shape_get_v_origin(topo_shape_t *p) {
  if (p) {
    return p->shp->get_v_origin();
  }
  return 0.;
}

double topo_shape_get_u_repeat(topo_shape_t *p) {
  if (p) {
    return p->shp->get_u_repeat();
  }
  return 1.;
}

double topo_shape_get_v_repeat(topo_shape_t *p) {
  if (p) {
    return p->shp->get_v_repeat();
  }
  return 1.;
}

double topo_shape_get_scale_v(topo_shape_t *p) {
  if (p) {
    return p->shp->get_scale_v();
  }
  return 1.;
}

double topo_shape_get_scale_u(topo_shape_t *p) {
  if (p) {
    return p->shp->get_scale_u();
  }
  return 1.;
}

double topo_shape_get_auto_scale_size_on_u(topo_shape_t *p) {
  if (p) {
    return p->shp->get_auto_scale_size_on_u();
  }
  return 1.;
}

double topo_shape_get_auto_scale_size_on_v(topo_shape_t *p) {
  if (p) {
    return p->shp->get_auto_scale_size_on_v();
  }
  return 1.;
}

int topo_shape_get_txture_map_type(topo_shape_t *p) {
  if (p) {
    return p->shp->get_txture_map_type();
  }
  return TextureNormal;
}

double topo_shape_get_rotation_angle(topo_shape_t *p) {
  if (p) {
    return p->shp->get_rotation_angle();
  }
  return 1.;
}

_Bool topo_shape_surface_colour(topo_shape_t *p, double *colour) {
  if (p) {
    return p->shp->surface_colour(colour);
  }
  return false;
}

pnt3d_t topo_shape_centre_of_mass(topo_shape_t *p) {
  if (p) {
    return cast_from_gp(p->shp->centre_of_mass());
  }
  return pnt3d_t{0, 0, 0};
}

double topo_shape_compute_mass(topo_shape_t *p) {
  if (p) {
    return p->shp->compute_mass();
  }
  return 0.;
}

double topo_shape_compute_area(topo_shape_t *p) {
  if (p) {
    return p->shp->compute_area();
  }
  return 0.;
}

topo_vertex_t topo_vertex_new(double x, double y, double z) {
  return topo_vertex_t{
      .shp = new topo_shape_t{
          .shp = std::make_shared<flywave::topo::vertex>(x, y, z)}};
}

void topo_vertex_free(topo_vertex_t t) {
  if (t.shp) {
    delete t.shp;
  }
}

pnt3d_t topo_vertex_get_point(topo_vertex_t t) {
  auto opt = cast_to_topo(t);
  if (opt) {
    gp_Pnt pt = (*opt);
    return cast_from_gp(pt);
  }
  return pnt3d_t{0., 0., 0.};
}

topo_wire_t topo_make_wire() {
  return topo_wire_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::wire>()}};
}

void topo_wire_free(topo_wire_t t) {
  if (t.shp) {
    delete t.shp;
  }
}

topo_wire_t topo_make_polygon() {
  return topo_wire_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::wire>(
                                  flywave::topo::wire::make_polygon())}};
}

topo_wire_t topo_make_polygon_from_two_point(pnt3d_t P1, pnt3d_t P2) {
  return topo_wire_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::wire>(
                                  flywave::topo::wire::make_polygon(
                                      cast_to_gp(P1), cast_to_gp(P2)))}};
}

topo_wire_t topo_make_polygon_from_three_point(pnt3d_t P1, pnt3d_t P2,
                                               pnt3d_t P3, _Bool Close) {
  return topo_wire_t{
      .shp = new topo_shape_t{
          .shp = std::make_shared<flywave::topo::wire>(
              flywave::topo::wire::make_polygon(cast_to_gp(P1), cast_to_gp(P2),
                                                cast_to_gp(P3), Close))}};
}

topo_wire_t topo_make_polygon_from_four_point(pnt3d_t P1, pnt3d_t P2,
                                              pnt3d_t P3, pnt3d_t P4,
                                              _Bool Close) {
  return topo_wire_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::wire>(
                                  flywave::topo::wire::make_polygon(
                                      cast_to_gp(P1), cast_to_gp(P2),
                                      cast_to_gp(P3), cast_to_gp(P4), Close))}};
}

topo_wire_t topo_make_polygon_two_vertex(topo_vertex_t V1, topo_vertex_t V2) {
  return topo_wire_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::wire>(
                                  flywave::topo::wire::make_polygon(
                                      *cast_to_topo(V1), *cast_to_topo(V2)))}};
}

topo_wire_t topo_make_polygon_from_three_vertex(topo_vertex_t V1,
                                                topo_vertex_t V2,
                                                topo_vertex_t V3, _Bool Close) {
  return topo_wire_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::wire>(
                                  flywave::topo::wire::make_polygon(
                                      *cast_to_topo(V1), *cast_to_topo(V2),
                                      *cast_to_topo(V3), Close))}};
}

topo_wire_t topo_make_polygon_from_four_vertex(topo_vertex_t V1,
                                               topo_vertex_t V2,
                                               topo_vertex_t V3,
                                               topo_vertex_t V4, _Bool Close) {
  return topo_wire_t{
      .shp = new topo_shape_t{
          .shp = std::make_shared<flywave::topo::wire>(
              flywave::topo::wire::make_polygon(
                  *cast_to_topo(V1), *cast_to_topo(V2), *cast_to_topo(V3),
                  *cast_to_topo(V4), Close))}};
}

topo_wire_t topo_make_wire_from_edge(topo_edge_t E) {
  return topo_wire_t{
      .shp = new topo_shape_t{
          .shp = std::make_shared<flywave::topo::wire>(
              flywave::topo::wire::make_wire(*cast_to_topo(E)))}};
}

topo_wire_t topo_make_wire_from_two_edge(topo_edge_t E1, topo_edge_t E2) {
  return topo_wire_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::wire>(
                                  flywave::topo::wire::make_wire(
                                      *cast_to_topo(E1), *cast_to_topo(E2)))}};
}

topo_wire_t topo_make_wire_from_three_edge(topo_edge_t E1, topo_edge_t E2,
                                           topo_edge_t E3) {
  return topo_wire_t{
      .shp = new topo_shape_t{
          .shp = std::make_shared<flywave::topo::wire>(
              flywave::topo::wire::make_wire(
                  *cast_to_topo(E1), *cast_to_topo(E2), *cast_to_topo(E3)))}};
}

topo_wire_t topo_make_wire_from_four_edge(topo_edge_t E1, topo_edge_t E2,
                                          topo_edge_t E3, topo_edge_t E4) {
  return topo_wire_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::wire>(
                                  flywave::topo::wire::make_wire(
                                      *cast_to_topo(E1), *cast_to_topo(E2),
                                      *cast_to_topo(E3), *cast_to_topo(E4)))}};
}

topo_wire_t topo_make_wire_from_wire(topo_wire_t W) {
  return topo_wire_t{
      .shp = new topo_shape_t{
          .shp = std::make_shared<flywave::topo::wire>(
              flywave::topo::wire::make_wire(*cast_to_topo(W)))}};
}

topo_wire_t topo_make_wire_from_two_wire(topo_wire_t W, topo_edge_t E) {
  return topo_wire_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::wire>(
                                  flywave::topo::wire::make_wire(
                                      *cast_to_topo(W), *cast_to_topo(E)))}};
}

topo_wire_t topo_make_wire_from_edges(topo_edge_t *edges, int count) {
  try {
    std::vector<flywave::topo::edge> oes;
    for (int i = 0; i < count; i++) {
      oes.emplace_back(*cast_to_topo(edges[i]));
    }
    return topo_wire_t{
        .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::wire>(
                                    flywave::topo::wire::make_wire(oes))}};
  } catch (...) {
    return topo_wire_t{};
  }
}

topo_wire_t topo_make_wire_from_wries(topo_wire_t *wires, int count) {
  try {
    std::vector<flywave::topo::wire> ows;
    for (int i = 0; i < count; i++) {
      ows.emplace_back(*cast_to_topo(wires[i]));
    }
    return topo_wire_t{
        .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::wire>(
                                    flywave::topo::wire::make_wire(ows))}};
  } catch (...) {
    return topo_wire_t{};
  }
}

topo_wire_t topo_make_wire_from_rect(double width, double height) {
  try {
    return topo_wire_t{.shp = new topo_shape_t{
                           .shp = std::make_shared<flywave::topo::wire>(
                               flywave::topo::wire::make_rect(width, height))}};
  } catch (...) {
    return topo_wire_t{};
  }
}

topo_wire_t topo_make_wire_from_circle(double radius, pnt3d_t center,
                                       dir3d_t normal) {
  try {
    return topo_wire_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::wire>(
                flywave::topo::wire::make_circle(radius, cast_to_gp(center),
                                                 cast_to_gp(normal)))}};
  } catch (...) {
    return topo_wire_t{};
  }
}

topo_wire_t topo_make_wire_from_ellipse(double x_radius, double y_radius,
                                        pnt3d_t center, dir3d_t normal,
                                        dir3d_t xDir, double angle1,
                                        double angle2, double rotation_angle,
                                        _Bool closed) {
  try {
    return topo_wire_t{.shp = new topo_shape_t{
                           .shp = std::make_shared<flywave::topo::wire>(
                               flywave::topo::wire::make_ellipse(
                                   x_radius, y_radius, cast_to_gp(center),
                                   cast_to_gp(normal), cast_to_gp(xDir), angle1,
                                   angle2, rotation_angle, closed))}};
  } catch (...) {
    return topo_wire_t{};
  }
}

topo_wire_t topo_make_wire_from_helix(double pitch, double height,
                                      double radius, pnt3d_t center,
                                      dir3d_t dir, double angle,
                                      _Bool lefthand) {
  try {
    return topo_wire_t{.shp = new topo_shape_t{
                           .shp = std::make_shared<flywave::topo::wire>(
                               flywave::topo::wire::make_helix(
                                   pitch, height, radius, cast_to_gp(center),
                                   cast_to_gp(dir), angle, lefthand))}};
  } catch (...) {
    return topo_wire_t{};
  }
}

topo_wire_t topo_make_wire_from_combine_curve(pnt3d_t **points,
                                              int *point_counts,
                                              int curve_count,
                                              int *curve_types) {
  try {
    // 转换点数据
    std::vector<std::vector<gp_Pnt>> cpp_points;
    for (int i = 0; i < curve_count; i++) {
      std::vector<gp_Pnt> curve_points;
      for (int j = 0; j < point_counts[i]; j++) {
        curve_points.push_back(
            gp_Pnt(points[i][j].x, points[i][j].y, points[i][j].z));
      }
      cpp_points.push_back(curve_points);
    }

    // 转换曲线类型
    std::vector<flywave::topo::wire::curve_type> cpp_curve_types;
    for (int i = 0; i < curve_count; i++) {
      switch (curve_types[i]) {
      case CURVE_LINE:
        cpp_curve_types.push_back(flywave::topo::wire::curve_type::line);
        break;
      case CURVE_THREE_POINT_ARC:
        cpp_curve_types.push_back(
            flywave::topo::wire::curve_type::three_point_arc);
        break;
      case CURVE_CIRCLE_CENTER_ARC:
        cpp_curve_types.push_back(
            flywave::topo::wire::curve_type::circle_center_arc);
        break;
      case CURVE_SPLINE:
        cpp_curve_types.push_back(flywave::topo::wire::curve_type::spline);
        break;
      default:
        return topo_wire_t{};
      }
    }
    return topo_wire_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::wire>(
                flywave::topo::wire::make_wire(cpp_points, cpp_curve_types))}};

  } catch (...) {
    return topo_wire_t{};
  }
}

topo_wire_t *topo_make_wire_from_combine(topo_wire_t *wires, int count,
                                         double tol, int *retCount) {
  try {
    std::vector<flywave::topo::shape> ows;
    for (int i = 0; i < count; i++) {
      ows.emplace_back(*cast_to_topo(wires[i]));
    }
    auto ret = flywave::topo::wire::combine(ows, tol);
    *retCount = static_cast<int>(ret.size());
    if (!ret.empty()) {
      auto *p = new topo_wire_t[ret.size()];
      for (size_t i = 0; i < ret.size(); i++) {
        p[i] = topo_wire_t{
            .shp = new topo_shape_t{
                .shp = std::make_shared<flywave::topo::wire>(ret[i])}};
      }
      return p;
    }
    return nullptr;
  } catch (...) {
    return nullptr;
  }
}

void topo_wire_list_free(topo_wire_t *wires, int count) { delete[] wires; }

topo_wire_t topo_wire_stitch(topo_wire_t w1, topo_wire_t w2) {
  try {
    return topo_wire_t{.shp = new topo_shape_t{
                           .shp = std::make_shared<flywave::topo::shape>(
                               cast_to_topo(w1)->stitch(*cast_to_topo(w2)))}};
  } catch (...) {
    return topo_wire_t{};
  }
}

int topo_wire_num_vertices(topo_wire_t w) {
  try {
    auto opt = cast_to_topo(w);
    if (opt) {
      return opt->num_vertices();
    }
    return -1;
  } catch (...) {
    return -1;
  }
}

int topo_wire_num_edges(topo_wire_t w) {
  try {
    auto opt = cast_to_topo(w);
    if (opt) {
      return opt->num_edges();
    }
    return -1;
  } catch (...) {
    return -1;
  }
}

bool topo_wire_is_closed(topo_wire_t w) {
  try {
    auto opt = cast_to_topo(w);
    if (opt) {
      return opt->is_closed();
    }
  } catch (...) {
    return false;
  }
  return false;
}

double topo_wire_length(topo_wire_t w) {
  try {
    auto opt = cast_to_topo(w);
    if (opt) {
      return opt->length();
    }
  } catch (...) {
    return 0;
  }
  return 0;
}

void topo_wire_convert_to_curves3d(topo_wire_t w) {
  try {
    auto opt = cast_to_topo(w);
    if (opt) {
      return opt->convert_to_curves3d();
    }
  } catch (...) {
  }
}

topo_wire_t *topo_wire_offset2d(topo_wire_t w, double distance, int joinType,
                                int *retCount) {
  try {
    auto opt = cast_to_topo(w);
    if (opt) {
      auto wires =
          opt->offset2d(distance, static_cast<GeomAbs_JoinType>(joinType));
      if (retCount) {
        *retCount = static_cast<int>(wires.size());
      }
      auto *p = new topo_wire_t[wires.size()];
      for (size_t i = 0; i < wires.size(); i++) {
        p[i] = topo_wire_t{
            .shp = new topo_shape_t{
                .shp = std::make_shared<flywave::topo::shape>(wires[i])}};
      }
      return p;
    }
    return nullptr;
  } catch (...) {
    return nullptr;
  }
}

topo_wire_t topo_wire_fillet2d(topo_wire_t w, topo_vertex_t *vertices,
                               int vertcount, double radius) {
  try {
    auto opt = cast_to_topo(w);
    if (opt) {
      std::vector<flywave::topo::vertex> ows;
      for (int i = 0; i < vertcount; i++) {
        ows.emplace_back(*cast_to_topo(vertices[i]));
      }

      return topo_wire_t{
          .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::wire>(
                                      opt->fillet2d(radius, ows))}};
    }
  } catch (...) {
    return topo_wire_t{};
  }
}

topo_wire_t topo_wire_chamfer2d(topo_wire_t w, topo_vertex_t *vertices,
                                int vertcount, double distance) {
  try {
    auto opt = cast_to_topo(w);
    if (opt) {
      std::vector<flywave::topo::vertex> ows;
      for (int i = 0; i < vertcount; i++) {
        ows.emplace_back(*cast_to_topo(vertices[i]));
      }
      return topo_wire_t{
          .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::wire>(
                                      opt->chamfer2d(distance, ows))}};
    }
  } catch (...) {
    return topo_wire_t{};
  }
}

int topo_wire_project(topo_wire_t w, topo_face_t f) {
  try {
    auto opt = cast_to_topo(w);
    if (opt) {
      return opt->project(*cast_to_topo(f));
    }
    return -1;
  } catch (...) {
    return -1;
  }
}

int topo_wire_offset(topo_wire_t w, double distance, int joinType) {
  try {
    auto opt = cast_to_topo(w);
    if (opt) {
      return opt->offset(distance, static_cast<GeomAbs_JoinType>(joinType));
    }
    return -1;
  } catch (...) {
    return -1;
  }
}

int topo_wire_fillet(topo_wire_t w, topo_vertex_t *vertices, int vertcount,
                     double *radius, int radcount) {
  auto opt = cast_to_topo(w);
  if (opt) {
    std::vector<flywave::topo::vertex> ows;
    for (int i = 0; i < vertcount; i++) {
      ows.emplace_back(*cast_to_topo(vertices[i]));
    }
    std::vector<double> ors;
    for (int i = 0; i < radcount; i++) {
      ors.emplace_back(radius[i]);
    }
    return opt->fillet(ows, ors);
  }
  return -1;
}

int topo_wire_chamfer(topo_wire_t w, topo_vertex_t *vertices, int vertcount,
                      double *distances, int distcount) {
  auto opt = cast_to_topo(w);
  if (opt) {
    std::vector<flywave::topo::vertex> ows;
    for (int i = 0; i < vertcount; i++) {
      ows.emplace_back(*cast_to_topo(vertices[i]));
    }
    std::vector<double> ors;
    for (int i = 0; i < distcount; i++) {
      ors.emplace_back(distances[i]);
    }
    return opt->chamfer(ows, ors);
  }
  return -1;
}

void topo_wire_bounds(topo_wire_t w, double *min, double *max) {
  try {
    auto bounds = cast_to_topo(w)->bounds();
    *min = bounds.first;
    *max = bounds.second;
  } catch (...) {
    *min = *max = 0.0;
  }
}

pnt3d_t topo_wire_start_point(topo_wire_t w) {
  pnt3d_t result = {0, 0, 0};
  try {
    auto point = cast_to_topo(w)->start_point();
    result.x = point.X();
    result.y = point.Y();
    result.z = point.Z();
  } catch (...) {
  }
  return result;
}

pnt3d_t topo_wire_end_point(topo_wire_t w) {
  pnt3d_t result = {0, 0, 0};
  try {
    auto point = cast_to_topo(w)->end_point();
    result.x = point.X();
    result.y = point.Y();
    result.z = point.Z();
  } catch (...) {
  }
  return result;
}

double topo_wire_param_at(topo_wire_t w, double d) {
  try {
    return cast_to_topo(w)->param_at(d);
  } catch (...) {
    return 0.0;
  }
}

double topo_wire_param_at_point(topo_wire_t w, pnt3d_t pt) {
  try {
    gp_Pnt point(pt.x, pt.y, pt.z);
    return cast_to_topo(w)->param_at(point);
  } catch (...) {
    return 0.0;
  }
}

void topo_wire_params(topo_wire_t w, pnt3d_t *pts, int count, double *params,
                      double tol) {
  try {
    std::vector<gp_Pnt> points;
    for (int i = 0; i < count; i++) {
      points.emplace_back(pts[i].x, pts[i].y, pts[i].z);
    }
    auto result = cast_to_topo(w)->params(points, tol);
    for (int i = 0; i < count; i++) {
      params[i] = result[i];
    }
  } catch (...) {
    for (int i = 0; i < count; i++) {
      params[i] = 0.0;
    }
  }
}

void topo_wire_params_length(topo_wire_t w, double *locations, int count,
                             double *params) {
  try {
    std::vector<double> locs(locations, locations + count);
    auto result = cast_to_topo(w)->params_length(locs);
    for (int i = 0; i < count; i++) {
      params[i] = result[i];
    }
  } catch (...) {
    for (int i = 0; i < count; i++) {
      params[i] = 0.0;
    }
  }
}

dir3d_t topo_wire_tangent_at(topo_wire_t w, double param) {
  dir3d_t result = {0, 0, 0};
  try {
    auto dir = cast_to_topo(w)->tangent_at(param);
    result.x = dir.X();
    result.y = dir.Y();
    result.z = dir.Z();
  } catch (...) {
  }
  return result;
}

void topo_wire_tangents(topo_wire_t w, double *params, int count,
                        dir3d_t *tangents) {
  try {
    std::vector<double> paramVec(params, params + count);
    auto result = cast_to_topo(w)->tangents(paramVec);
    for (int i = 0; i < count; i++) {
      tangents[i].x = result[i].X();
      tangents[i].y = result[i].Y();
      tangents[i].z = result[i].Z();
    }
  } catch (...) {
    for (int i = 0; i < count; i++) {
      tangents[i] = {0, 0, 0};
    }
  }
}

dir3d_t topo_wire_normal(topo_wire_t w) {
  dir3d_t result = {0, 0, 0};
  try {
    auto dir = cast_to_topo(w)->normal();
    result.x = dir.X();
    result.y = dir.Y();
    result.z = dir.Z();
  } catch (...) {
  }
  return result;
}

pnt3d_t topo_wire_center(topo_wire_t w) {
  pnt3d_t result = {0, 0, 0};
  try {
    auto point = cast_to_topo(w)->center();
    result.x = point.X();
    result.y = point.Y();
    result.z = point.Z();
  } catch (...) {
  }
  return result;
}

double topo_wire_radius(topo_wire_t w) {
  try {
    return cast_to_topo(w)->radius();
  } catch (...) {
    return 0.0;
  }
}

pnt3d_t topo_wire_position_at(topo_wire_t w, double d, int mode) {
  pnt3d_t result = {0, 0, 0};
  try {
    auto point = cast_to_topo(w)->position_at(
        d, static_cast<flywave::topo::wire::ParamMode>(mode));
    result.x = point.X();
    result.y = point.Y();
    result.z = point.Z();
  } catch (...) {
  }
  return result;
}

void topo_wire_positions(topo_wire_t w, double *ds, int count, pnt3d_t *points,
                         int mode) {
  try {
    std::vector<double> dVec(ds, ds + count);
    auto result = cast_to_topo(w)->positions(
        dVec, static_cast<flywave::topo::wire::ParamMode>(mode));
    for (int i = 0; i < count; i++) {
      points[i].x = result[i].X();
      points[i].y = result[i].Y();
      points[i].z = result[i].Z();
    }
  } catch (...) {
    for (int i = 0; i < count; i++) {
      points[i] = {0, 0, 0};
    }
  }
}

void topo_wire_sample_uniform(topo_wire_t w, double n, pnt3d_t **points,
                              int *point_count, double **params,
                              int *param_count) {
  try {
    auto result = cast_to_topo(w)->sample_uniform(n);

    *point_count = static_cast<int>(result.first.size());
    *param_count = static_cast<int>(result.second.size());

    *points = new pnt3d_t[*point_count];
    *params = new double[*param_count];

    for (int i = 0; i < *point_count; i++) {
      (*points)[i].x = result.first[i].X();
      (*points)[i].y = result.first[i].Y();
      (*points)[i].z = result.first[i].Z();
    }

    for (int i = 0; i < *param_count; i++) {
      (*params)[i] = result.second[i];
    }
  } catch (...) {
    *point_count = 0;
    *param_count = 0;
    *points = nullptr;
    *params = nullptr;
  }
}

topo_location_t *topo_wire_location_at(topo_wire_t w, double d, int mode,
                                       int frame, bool planar) {
  try {
    auto loc = cast_to_topo(w)->location_at(
        d, static_cast<flywave::topo::wire::ParamMode>(mode),
        static_cast<flywave::topo::wire::FrameMode>(frame), planar);
    return new topo_location_t{.loc = loc};
  } catch (...) {
    return nullptr;
  }
}

topo_location_t **topo_wire_locations(topo_wire_t w, double *ds, int count,
                                      int mode, int frame, bool planar,
                                      int *result_count) {
  try {
    std::vector<double> dVec(ds, ds + count);
    auto result = cast_to_topo(w)->locations(
        dVec, static_cast<flywave::topo::wire::ParamMode>(mode),
        static_cast<flywave::topo::wire::FrameMode>(frame), planar);

    auto **locs = new topo_location_t *[result.size()];
    for (size_t i = 0; i < result.size(); i++) {
      locs[i] = new topo_location_t{.loc = result[i]};
    }
    *result_count = static_cast<int>(result.size());
    return locs;
  } catch (...) {
    *result_count = 0;
    return nullptr;
  }
}

int topo_wire_projected(topo_wire_t w, topo_face_t f, vec3d_t direction,
                        bool closest, topo_shape_t ***result,
                        int *result_count) {
  try {
    gp_Vec dir(direction.x, direction.y, direction.z);
    auto proj = cast_to_topo(w)->projected(*cast_to_topo(f), dir, closest);
    if (proj.which() == 0) {
      *result_count = 1;
      *result = new topo_shape_t *[1];
      (*result)[0] =
          new topo_shape_t{.shp = std::make_shared<flywave::topo::shape>(
                               boost::get<flywave::topo::shape>(proj))};
    } else {
      auto shapes = boost::get<std::vector<flywave::topo::shape>>(proj);
      *result_count = static_cast<int>(shapes.size());
      *result = new topo_shape_t *[*result_count];
      for (int i = 0; i < *result_count; i++) {
        (*result)[i] = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::shape>(shapes[i])};
      }
    }
    return 0;
  } catch (...) {
    *result_count = 0;
    *result = nullptr;
    return -1;
  }
}

void topo_shape_list_free(topo_shape_t **result, int result_count) {
  delete[] result;
}

double topo_wire_curvature_at(topo_wire_t w, double d, int mode,
                              double resolution) {
  try {
    return cast_to_topo(w)->curvature_at(
        d, static_cast<flywave::topo::wire::ParamMode>(mode), resolution);
  } catch (...) {
    return 0.0;
  }
}

void topo_wire_curvatures(topo_wire_t w, double *ds, int count,
                          double *curvatures, int mode, double resolution) {
  try {
    std::vector<double> dVec(ds, ds + count);
    auto result = cast_to_topo(w)->curvatures(
        dVec, static_cast<flywave::topo::wire::ParamMode>(mode), resolution);
    for (int i = 0; i < count; i++) {
      curvatures[i] = result[i];
    }
  } catch (...) {
    for (int i = 0; i < count; i++) {
      curvatures[i] = 0.0;
    }
  }
}

topo_edge_t topo_make_edge() {
  try {
    return topo_edge_t{.shp = new topo_shape_t{
                           .shp = std::make_shared<flywave::topo::edge>()}};
  } catch (...) {
    return topo_edge_t{};
  }
}

void topo_edge_free(topo_edge_t t) {
  if (t.shp) {
    delete t.shp;
  }
}

topo_edge_t topo_edge_make_edge_from_points(pnt3d_t *pts, int size) {
  std::vector<gp_Pnt> vec;
  for (int i = 0; i < size; i++) {
    vec.emplace_back(cast_to_gp(pts[i]));
  }
  try {
    return topo_edge_t{.shp = new topo_shape_t{
                           .shp = std::make_shared<flywave::topo::edge>(
                               flywave::topo::edge::make_polygon(vec, true))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edge_from_two_vertex(topo_vertex_t V1,
                                                topo_vertex_t V2) {
  try {
    return topo_edge_t{.shp = new topo_shape_t{
                           .shp = std::make_shared<flywave::topo::edge>(
                               flywave::topo::edge::make_edge(
                                   *cast_to_topo(V1), *cast_to_topo(V2)))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edge_from_two_point(pnt3d_t P1, pnt3d_t P2) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::edge>(
                                    flywave::topo::edge::make_edge(
                                        cast_to_gp(P1), cast_to_gp(P2)))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edge_from_line(line_t L) {
  try {
    return topo_edge_t{.shp = new topo_shape_t{
                           .shp = std::make_shared<flywave::topo::edge>(
                               flywave::topo::edge::make_edge(cast_to_gp(L)))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edge_from_line_p(line_t L, double p1, double p2) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::edge>(
                flywave::topo::edge::make_edge(cast_to_gp(L), p1, p2))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edge_from_line_point(line_t L, pnt3d_t P1,
                                                pnt3d_t P2) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::edge>(
                flywave::topo::edge::make_edge(cast_to_gp(L), cast_to_gp(P1),
                                               cast_to_gp(P2)))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edge_from_line_vertex(line_t L, topo_vertex_t V1,
                                                 topo_vertex_t V2) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::edge>(
                flywave::topo::edge::make_edge(cast_to_gp(L), *cast_to_topo(V1),
                                               *cast_to_topo(V2)))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edge_from_circ(circ_t L) {
  try {
    return topo_edge_t{.shp = new topo_shape_t{
                           .shp = std::make_shared<flywave::topo::edge>(
                               flywave::topo::edge::make_edge(cast_to_gp(L)))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edge_from_circ_p(circ_t L, double p1, double p2) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::edge>(
                flywave::topo::edge::make_edge(cast_to_gp(L), p1, p2))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edge_from_circ_point(circ_t L, pnt3d_t P1,
                                                pnt3d_t P2) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::edge>(
                flywave::topo::edge::make_edge(cast_to_gp(L), cast_to_gp(P1),
                                               cast_to_gp(P2)))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edge_from_circ_vertex(circ_t L, topo_vertex_t V1,
                                                 topo_vertex_t V2) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::edge>(
                flywave::topo::edge::make_edge(cast_to_gp(L), *cast_to_topo(V1),
                                               *cast_to_topo(V2)))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edge_from_elips(elips_t L) {
  try {
    return topo_edge_t{.shp = new topo_shape_t{
                           .shp = std::make_shared<flywave::topo::edge>(
                               flywave::topo::edge::make_edge(cast_to_gp(L)))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edge_from_elips_p(elips_t L, double p1, double p2) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::edge>(
                flywave::topo::edge::make_edge(cast_to_gp(L), p1, p2))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edge_from_elips_point(elips_t L, pnt3d_t P1,
                                                 pnt3d_t P2) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::edge>(
                flywave::topo::edge::make_edge(cast_to_gp(L), cast_to_gp(P1),
                                               cast_to_gp(P2)))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edge_from_elips_vertex(elips_t L, topo_vertex_t V1,
                                                  topo_vertex_t V2) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::edge>(
                flywave::topo::edge::make_edge(cast_to_gp(L), *cast_to_topo(V1),
                                               *cast_to_topo(V2)))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edge_from_hyper(hyperbola_t L) {
  try {
    return topo_edge_t{.shp = new topo_shape_t{
                           .shp = std::make_shared<flywave::topo::edge>(
                               flywave::topo::edge::make_edge(cast_to_gp(L)))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edge_from_hyper_p(hyperbola_t L, double p1,
                                             double p2) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::edge>(
                flywave::topo::edge::make_edge(cast_to_gp(L), p1, p2))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edge_from_hyper_point(hyperbola_t L, pnt3d_t P1,
                                                 pnt3d_t P2) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::edge>(
                flywave::topo::edge::make_edge(cast_to_gp(L), cast_to_gp(P1),
                                               cast_to_gp(P2)))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edge_from_hyper_vertex(hyperbola_t L,
                                                  topo_vertex_t V1,
                                                  topo_vertex_t V2) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::edge>(
                flywave::topo::edge::make_edge(cast_to_gp(L), *cast_to_topo(V1),
                                               *cast_to_topo(V2)))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edge_from_parab(parabola_t L) {
  try {
    return topo_edge_t{.shp = new topo_shape_t{
                           .shp = std::make_shared<flywave::topo::edge>(
                               flywave::topo::edge::make_edge(cast_to_gp(L)))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edge_from_parab_p(parabola_t L, double p1,
                                             double p2) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::edge>(
                flywave::topo::edge::make_edge(cast_to_gp(L), p1, p2))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edge_from_parab_point(parabola_t L, pnt3d_t P1,
                                                 pnt3d_t P2) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::edge>(
                flywave::topo::edge::make_edge(cast_to_gp(L), cast_to_gp(P1),
                                               cast_to_gp(P2)))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edge_from_parab_vertex(parabola_t L,
                                                  topo_vertex_t V1,
                                                  topo_vertex_t V2) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::edge>(
                flywave::topo::edge::make_edge(cast_to_gp(L), *cast_to_topo(V1),
                                               *cast_to_topo(V2)))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edgee_from_curve(geom_curve_t *L) {
  try {
    return topo_edge_t{.shp = new topo_shape_t{
                           .shp = std::make_shared<flywave::topo::edge>(
                               flywave::topo::edge::make_edge(L->handle))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edge_from_curve_p(geom_curve_t *L, double p1,
                                             double p2) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::edge>(
                flywave::topo::edge::make_edge(L->handle, p1, p2))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edge_from_curve_point(geom_curve_t *L, pnt3d_t P1,
                                                 pnt3d_t P2) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::edge>(
                flywave::topo::edge::make_edge(L->handle, cast_to_gp(P1),
                                               cast_to_gp(P2)))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edge_from_curve_vertex(geom_curve_t *L,
                                                  topo_vertex_t V1,
                                                  topo_vertex_t V2) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::edge>(
                flywave::topo::edge::make_edge(L->handle, *cast_to_topo(V1),
                                               *cast_to_topo(V2)))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edgee_from_curve_point_p(geom_curve_t *L, pnt3d_t P1,
                                                    pnt3d_t P2, double p1,
                                                    double p2) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::edge>(
                flywave::topo::edge::make_edge(L->handle, cast_to_gp(P1),
                                               cast_to_gp(P2), p1, p2))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edge_from_curve_vertex_p(geom_curve_t *L,
                                                    topo_vertex_t V1,
                                                    topo_vertex_t V2, double p1,
                                                    double p2) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::edge>(
                flywave::topo::edge::make_edge(L->handle, *cast_to_topo(V1),
                                               *cast_to_topo(V2), p1, p2))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edge_from_curve_surface(geom2d_curve_t *L,
                                                   geom_surface_t *S) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::edge>(
                flywave::topo::edge::make_edge(L->handle, S->handle))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edge_from_curve_surface_p(geom2d_curve_t *L,
                                                     geom_surface_t *S,
                                                     double p1, double p2) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::edge>(
                flywave::topo::edge::make_edge(L->handle, S->handle, p1, p2))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edge_from_curve_surface_point(geom2d_curve_t *L,
                                                         geom_surface_t *S,
                                                         pnt3d_t P1,
                                                         pnt3d_t P2) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::edge>(
                flywave::topo::edge::make_edge(
                    L->handle, S->handle, cast_to_gp(P1), cast_to_gp(P2)))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edge_from_curve_surface_vertex(geom2d_curve_t *L,
                                                          geom_surface_t *S,
                                                          topo_vertex_t V1,
                                                          topo_vertex_t V2) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::edge>(
                                    flywave::topo::edge::make_edge(
                                        L->handle, S->handle, *cast_to_topo(V1),
                                        *cast_to_topo(V2)))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edge_from_curve_surface_point_p(
    geom2d_curve_t *L, geom_surface_t *S, pnt3d_t P1, pnt3d_t P2, double p1,
    double p2) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::edge>(
                                    flywave::topo::edge::make_edge(
                                        L->handle, S->handle, cast_to_gp(P1),
                                        cast_to_gp(P2), p1, p2))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edge_from_curve_surface_vertex_p(
    geom2d_curve_t *L, geom_surface_t *S, topo_vertex_t V1, topo_vertex_t V2,
    double p1, double p2) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::edge>(
                                    flywave::topo::edge::make_edge(
                                        L->handle, S->handle, *cast_to_topo(V1),
                                        *cast_to_topo(V2), p1, p2))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edge2d_from_two_vertex(topo_vertex_t V1,
                                                  topo_vertex_t V2) {
  try {
    return topo_edge_t{.shp = new topo_shape_t{
                           .shp = std::make_shared<flywave::topo::edge>(
                               flywave::topo::edge::make_edge2d(
                                   *cast_to_topo(V1), *cast_to_topo(V2)))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edge2d_from_two_point(pnt2d_t P1, pnt2d_t P2) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::edge>(
                                    flywave::topo::edge::make_edge2d(
                                        cast_to_gp(P1), cast_to_gp(P2)))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edge2d_from_line(line2d_t L) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::edge>(
                flywave::topo::edge::make_edge2d(cast_to_gp(L)))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edge2d_from_line_p(line2d_t L, double p1,
                                              double p2) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::edge>(
                flywave::topo::edge::make_edge2d(cast_to_gp(L), p1, p2))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edge2d_from_line_point(line2d_t L, pnt2d_t P1,
                                                  pnt2d_t P2) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::edge>(
                flywave::topo::edge::make_edge2d(cast_to_gp(L), cast_to_gp(P1),
                                                 cast_to_gp(P2)))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edge2d_from_line_vertex(line2d_t L, topo_vertex_t V1,
                                                   topo_vertex_t V2) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::edge>(
                flywave::topo::edge::make_edge2d(
                    cast_to_gp(L), *cast_to_topo(V1), *cast_to_topo(V2)))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edge2d_from_circ(circ2d_t L) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::edge>(
                flywave::topo::edge::make_edge2d(cast_to_gp(L)))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edge2d_from_circ_p(circ2d_t L, double p1,
                                              double p2) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::edge>(
                flywave::topo::edge::make_edge2d(cast_to_gp(L), p1, p2))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edge2d_from_circ_point(circ2d_t L, pnt2d_t P1,
                                                  pnt2d_t P2) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::edge>(
                flywave::topo::edge::make_edge2d(cast_to_gp(L), cast_to_gp(P1),
                                                 cast_to_gp(P2)))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edge2d_from_circ_vertex(circ2d_t L, topo_vertex_t V1,
                                                   topo_vertex_t V2) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::edge>(
                flywave::topo::edge::make_edge2d(
                    cast_to_gp(L), *cast_to_topo(V1), *cast_to_topo(V2)))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edge2d_from_elips(elips2d_t L) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::edge>(
                flywave::topo::edge::make_edge2d(cast_to_gp(L)))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edge2d_from_elips_p(elips2d_t L, double p1,
                                               double p2) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::edge>(
                flywave::topo::edge::make_edge2d(cast_to_gp(L), p1, p2))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edge2d_from_elips_point(elips2d_t L, pnt2d_t P1,
                                                   pnt2d_t P2) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::edge>(
                flywave::topo::edge::make_edge2d(cast_to_gp(L), cast_to_gp(P1),
                                                 cast_to_gp(P2)))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edge2d_from_elips_vertex(elips2d_t L,
                                                    topo_vertex_t V1,
                                                    topo_vertex_t V2) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::edge>(
                flywave::topo::edge::make_edge2d(
                    cast_to_gp(L), *cast_to_topo(V1), *cast_to_topo(V2)))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edge2d_from_hyper(hyperbola2d_t L) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::edge>(
                flywave::topo::edge::make_edge2d(cast_to_gp(L)))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edge2d_from_hyper_p(hyperbola2d_t L, double p1,
                                               double p2) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::edge>(
                flywave::topo::edge::make_edge2d(cast_to_gp(L), p1, p2))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edge2d_from_hyper_point(hyperbola2d_t L, pnt2d_t P1,
                                                   pnt2d_t P2) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::edge>(
                flywave::topo::edge::make_edge2d(cast_to_gp(L), cast_to_gp(P1),
                                                 cast_to_gp(P2)))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edge2d_from_hyper_vertex(hyperbola2d_t L,
                                                    topo_vertex_t V1,
                                                    topo_vertex_t V2) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::edge>(
                flywave::topo::edge::make_edge2d(
                    cast_to_gp(L), *cast_to_topo(V1), *cast_to_topo(V2)))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edge2d_from_parab(parabola2d_t L) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::edge>(
                flywave::topo::edge::make_edge2d(cast_to_gp(L)))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edge2d_from_parab_p(parabola2d_t L, double p1,
                                               double p2) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::edge>(
                flywave::topo::edge::make_edge2d(cast_to_gp(L), p1, p2))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edge2d_from_parab_point(parabola2d_t L, pnt2d_t P1,
                                                   pnt2d_t P2) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::edge>(
                flywave::topo::edge::make_edge2d(cast_to_gp(L), cast_to_gp(P1),
                                                 cast_to_gp(P2)))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edge2d_from_parab_vertex(parabola2d_t L,
                                                    topo_vertex_t V1,
                                                    topo_vertex_t V2) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::edge>(
                flywave::topo::edge::make_edge2d(
                    cast_to_gp(L), *cast_to_topo(V1), *cast_to_topo(V2)))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edge2d_from_curve(geom2d_curve_t *L) {
  try {
    return topo_edge_t{.shp = new topo_shape_t{
                           .shp = std::make_shared<flywave::topo::edge>(
                               flywave::topo::edge::make_edge2d(L->handle))}};
  } catch (...) {
    return topo_edge_t{};
  }
}
topo_edge_t topo_edge_make_edge2d_from_curve_p(geom2d_curve_t *L, double p1,
                                               double p2) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::edge>(
                flywave::topo::edge::make_edge2d(L->handle, p1, p2))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edge2d_from_curve_point(geom2d_curve_t *L,
                                                   pnt2d_t P1, pnt2d_t P2) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::edge>(
                flywave::topo::edge::make_edge2d(L->handle, cast_to_gp(P1),
                                                 cast_to_gp(P2)))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edge2d_from_curve_vertex(geom2d_curve_t *L,
                                                    topo_vertex_t V1,
                                                    topo_vertex_t V2) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::edge>(
                flywave::topo::edge::make_edge2d(L->handle, *cast_to_topo(V1),
                                                 *cast_to_topo(V2)))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edge2d_from_curve_point_p(geom2d_curve_t *L,
                                                     pnt2d_t P1, pnt2d_t P2,
                                                     double p1, double p2) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::edge>(
                flywave::topo::edge::make_edge2d(L->handle, cast_to_gp(P1),
                                                 cast_to_gp(P2), p1, p2))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_edge2d_from_curve_vertex_p(geom2d_curve_t *L,
                                                      topo_vertex_t V1,
                                                      topo_vertex_t V2,
                                                      double p1, double p2) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::edge>(
                flywave::topo::edge::make_edge2d(L->handle, *cast_to_topo(V1),
                                                 *cast_to_topo(V2), p1, p2))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_polygon() {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::edge>(
                                    flywave::topo::edge::make_polygon())}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_polygon_from_two_point(pnt3d_t P1, pnt3d_t P2) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::edge>(
                                    flywave::topo::edge::make_polygon(
                                        cast_to_gp(P1), cast_to_gp(P2)))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_polygon_from_three_point(pnt3d_t P1, pnt3d_t P2,
                                                    pnt3d_t P3, _Bool Close) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::edge>(
                flywave::topo::edge::make_polygon(
                    cast_to_gp(P1), cast_to_gp(P2), cast_to_gp(P3), Close))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_polygon_from_four_point(pnt3d_t P1, pnt3d_t P2,
                                                   pnt3d_t P3, pnt3d_t P4,
                                                   _Bool Close) {
  try {
    return topo_edge_t{.shp = new topo_shape_t{
                           .shp = std::make_shared<flywave::topo::edge>(
                               flywave::topo::edge::make_polygon(
                                   cast_to_gp(P1), cast_to_gp(P2),
                                   cast_to_gp(P3), cast_to_gp(P4), Close))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_polygon_from_two_vertex(topo_vertex_t V1,
                                                   topo_vertex_t V2) {
  try {
    return topo_edge_t{.shp = new topo_shape_t{
                           .shp = std::make_shared<flywave::topo::edge>(
                               flywave::topo::edge::make_polygon(
                                   *cast_to_topo(V1), *cast_to_topo(V2)))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_polygon_from_three_vertex(topo_vertex_t V1,
                                                     topo_vertex_t V2,
                                                     topo_vertex_t V3,
                                                     _Bool Close) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::edge>(
                                    flywave::topo::edge::make_polygon(
                                        *cast_to_topo(V1), *cast_to_topo(V2),
                                        *cast_to_topo(V3), Close))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_polygon_from_four_vertex(topo_vertex_t V1,
                                                    topo_vertex_t V2,
                                                    topo_vertex_t V3,
                                                    topo_vertex_t V4,
                                                    _Bool Close) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::edge>(
                flywave::topo::edge::make_polygon(
                    *cast_to_topo(V1), *cast_to_topo(V2), *cast_to_topo(V3),
                    *cast_to_topo(V4), Close))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_polygon_from_vertices(topo_vertex_t *vertices,
                                                 int vertcount, _Bool Close) {
  std::vector<flywave::topo::vertex> oes;
  for (int i = 0; i < vertcount; i++) {
    oes.emplace_back(
        *std::dynamic_pointer_cast<flywave::topo::vertex>(vertices[i].shp->shp)
             .get());
  }
  try {
    return topo_edge_t{.shp = new topo_shape_t{
                           .shp = std::make_shared<flywave::topo::edge>(
                               flywave::topo::edge::make_polygon(oes, Close))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_polygonn_from_points(pnt3d_t *vertexs, int vertcount,
                                                _Bool Close) {
  std::vector<gp_Pnt> oes;
  for (int i = 0; i < vertcount; i++) {
    oes.emplace_back(cast_to_gp(vertexs[i]));
  }
  try {
    return topo_edge_t{.shp = new topo_shape_t{
                           .shp = std::make_shared<flywave::topo::edge>(
                               flywave::topo::edge::make_polygon(oes, Close))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_rect(double width, double height) {
  try {
    return topo_edge_t{.shp = new topo_shape_t{
                           .shp = std::make_shared<flywave::topo::edge>(
                               flywave::topo::edge::make_rect(width, height))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_spline(pnt3d_t *vertexs, int vertcount, double tol,
                                  bool periodic) {
  try {
    std::vector<gp_Pnt> oes;
    for (int i = 0; i < vertcount; i++) {
      oes.emplace_back(cast_to_gp(vertexs[i]));
    }
    return topo_edge_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::edge>(
                flywave::topo::edge::make_spline(oes, tol, periodic))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_spline_from_tangents_and_parameters(
    pnt3d_t *points, int pntcount, vec3d_t *tangents, int tancount,
    double *parameters, int paramcount, double tol, bool periodic, bool scale) {
  try {
    std::vector<gp_Pnt> oes;
    for (int i = 0; i < pntcount; i++) {
      oes.emplace_back(cast_to_gp(points[i]));
    }
    std::vector<gp_Vec> otangents;
    for (int i = 0; i < tancount; i++) {
      otangents.emplace_back(cast_to_gp(tangents[i]));
    }
    std::vector<double> oparameters;
    for (int i = 0; i < paramcount; i++) {
      oparameters.emplace_back(parameters[i]);
    }
    return topo_edge_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::edge>(
                flywave::topo::edge::make_spline(
                    oes, &otangents, periodic,
                    parameters ? &oparameters : nullptr, scale, tol))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_spline_approx(pnt3d_t *points, int pntcount,
                                         double tolerance, double *smoothing,
                                         int minDegree, int maxDegree) {
  try {
    std::vector<gp_Pnt> oes;
    for (int i = 0; i < pntcount; i++) {
      oes.emplace_back(cast_to_gp(points[i]));
    }
    boost::optional<std::tuple<double, double, double>> osmoothing =
        boost::none;
    if (smoothing) {
      osmoothing = std::make_tuple(smoothing[0], smoothing[1], smoothing[2]);
    }
    return topo_edge_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::edge>(
                flywave::topo::edge::make_spline_approx(
                    oes, tolerance, osmoothing, minDegree, maxDegree))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_catenary(pnt3d_t p1, pnt3d_t p2, double slack,
                                    double maxSag, dir3d_t up,
                                    double tessellation) {
  try {
    return topo_edge_t{.shp = new topo_shape_t{
                           .shp = std::make_shared<flywave::topo::edge>(
                               flywave::topo::edge::make_catenary(
                                   cast_to_gp(p1), cast_to_gp(p2), slack,
                                   maxSag, cast_to_gp(up), tessellation))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_circle(double radius, pnt3d_t center, vec3d_t normal,
                                  double angle1, double angle2,
                                  bool orientation) {
  try {
    return topo_edge_t{new topo_shape_t{std::make_shared<flywave::topo::edge>(
        flywave::topo::edge::make_circle(radius, cast_to_gp(center),
                                         cast_to_gp(normal), angle1, angle2,
                                         orientation))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_ellipse(double majorRadius, double minorRadius,
                                   pnt3d_t center, vec3d_t normal,
                                   vec3d_t xnormal, double angle1,
                                   double angle2, int sense) {
  try {
    return topo_edge_t{.shp = new topo_shape_t{
                           .shp = std::make_shared<flywave::topo::edge>(
                               flywave::topo::edge::make_ellipse(
                                   majorRadius, minorRadius, cast_to_gp(center),
                                   cast_to_gp(normal), cast_to_gp(xnormal),
                                   angle1, angle2, sense))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_three_point_arc(pnt3d_t v1, pnt3d_t v2, pnt3d_t v3) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::edge>(
                flywave::topo::edge::make_three_point_arc(
                    cast_to_gp(v1), cast_to_gp(v2), cast_to_gp(v3)))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_circle_center_arc(pnt3d_t v1, pnt3d_t center,
                                             pnt3d_t v2) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::edge>(
                flywave::topo::edge::make_circle_center_arc(
                    cast_to_gp(v1), cast_to_gp(center), cast_to_gp(v2)))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_tangent_arc(pnt3d_t v1, vec3d_t tangent,
                                       pnt3d_t v3) {
  try {
    return topo_edge_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::edge>(
                flywave::topo::edge::make_tangent_arc(
                    cast_to_gp(v1), cast_to_gp(tangent), cast_to_gp(v3)))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

topo_edge_t topo_edge_make_bezier(pnt3d_t *points, int pntcount) {
  try {
    std::vector<gp_Pnt> oes;
    for (int i = 0; i < pntcount; i++) {
      oes.emplace_back(cast_to_gp(points[i]));
    }
    return topo_edge_t{
        .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::edge>(
                                    flywave::topo::edge::make_bezier(oes))}};
  } catch (...) {
    return topo_edge_t{};
  }
}

bool topo_edge_is_seam(topo_edge_t e, topo_face_t f) {
  auto opt = cast_to_topo(e);
  if (opt) {
    return opt->is_seam(*cast_to_topo(f));
  }
  return false;
}

bool topo_edge_is_degenerated(topo_edge_t e) {
  auto opt = cast_to_topo(e);
  if (opt) {
    return opt->is_degenerated();
  }
  return false;
}

bool topo_edge_is_closed(topo_edge_t e) {
  auto opt = cast_to_topo(e);
  if (opt) {
    return opt->is_closed();
  }
  return false;
}

bool topo_edge_is_inifinite(topo_edge_t e) {
  auto opt = cast_to_topo(e);
  if (opt) {
    return opt->is_inifinite();
  }
  return false;
}

int topo_edge_num_vertices(topo_edge_t e) {
  auto opt = cast_to_topo(e);
  if (opt) {
    return opt->num_vertices();
  }
  return -1;
}

double topo_edge_length(topo_edge_t e) {
  auto opt = cast_to_topo(e);
  if (opt) {
    return opt->length();
  }
  return 0.0;
}

float topo_edge_tolerance(topo_edge_t e) {
  auto opt = cast_to_topo(e);
  if (opt) {
    return opt->tolerance();
  }
  return 0.0f;
}

bool topo_edge_is_curve3d(topo_edge_t e) {
  auto opt = cast_to_topo(e);
  if (opt) {
    return opt->is_curve3d();
  }
  return false;
}

void topo_edge_convert_to_curve3d(topo_edge_t e) {
  auto opt = cast_to_topo(e);
  if (opt) {
    return opt->convert_to_curve3d();
  }
}

void topo_edge_reverse(topo_edge_t e) {
  auto opt = cast_to_topo(e);
  if (opt) {
    return opt->reverse();
  }
}

void topo_edge_bounds(topo_edge_t e, double *min, double *max) {
  try {
    auto bounds = cast_to_topo(e)->bounds();
    *min = bounds.first;
    *max = bounds.second;
  } catch (...) {
    *min = *max = 0.0;
  }
}

pnt3d_t topo_edge_start_point(topo_edge_t e) {
  pnt3d_t result = {0, 0, 0};
  try {
    auto point = cast_to_topo(e)->start_point();
    result.x = point.X();
    result.y = point.Y();
    result.z = point.Z();
  } catch (...) {
  }
  return result;
}

pnt3d_t topo_edge_end_point(topo_edge_t e) {
  pnt3d_t result = {0, 0, 0};
  try {
    auto point = cast_to_topo(e)->end_point();
    result.x = point.X();
    result.y = point.Y();
    result.z = point.Z();
  } catch (...) {
  }
  return result;
}

double topo_edge_param_at(topo_edge_t e, double d) {
  try {
    return cast_to_topo(e)->param_at(d);
  } catch (...) {
    return 0.0;
  }
}

double topo_edge_param_at_point(topo_edge_t e, pnt3d_t pt) {
  try {
    gp_Pnt point(pt.x, pt.y, pt.z);
    return cast_to_topo(e)->param_at(point);
  } catch (...) {
    return 0.0;
  }
}

void topo_edge_params(topo_edge_t e, pnt3d_t *pts, int count, double *params,
                      double tol) {
  try {
    std::vector<gp_Pnt> points;
    for (int i = 0; i < count; i++) {
      points.emplace_back(pts[i].x, pts[i].y, pts[i].z);
    }
    auto result = cast_to_topo(e)->params(points, tol);
    for (int i = 0; i < count; i++) {
      params[i] = result[i];
    }
  } catch (...) {
    for (int i = 0; i < count; i++) {
      params[i] = 0.0;
    }
  }
}

void topo_edge_params_length(topo_edge_t e, double *locations, int count,
                             double *params) {
  try {
    std::vector<double> locs(locations, locations + count);
    auto result = cast_to_topo(e)->params_length(locs);
    for (int i = 0; i < count; i++) {
      params[i] = result[i];
    }
  } catch (...) {
    for (int i = 0; i < count; i++) {
      params[i] = 0.0;
    }
  }
}

dir3d_t topo_edge_tangent_at(topo_edge_t e, double param) {
  dir3d_t result = {0, 0, 0};
  try {
    auto dir = cast_to_topo(e)->tangent_at(param);
    result.x = dir.X();
    result.y = dir.Y();
    result.z = dir.Z();
  } catch (...) {
  }
  return result;
}

void topo_edge_tangents(topo_edge_t e, double *params, int count,
                        dir3d_t *tangents) {
  try {
    std::vector<double> paramVec(params, params + count);
    auto result = cast_to_topo(e)->tangents(paramVec);
    for (int i = 0; i < count; i++) {
      tangents[i].x = result[i].X();
      tangents[i].y = result[i].Y();
      tangents[i].z = result[i].Z();
    }
  } catch (...) {
    for (int i = 0; i < count; i++) {
      tangents[i] = {0, 0, 0};
    }
  }
}

dir3d_t topo_edge_normal(topo_edge_t e) {
  dir3d_t result = {0, 0, 0};
  try {
    auto dir = cast_to_topo(e)->normal();
    result.x = dir.X();
    result.y = dir.Y();
    result.z = dir.Z();
  } catch (...) {
  }
  return result;
}

pnt3d_t topo_edge_center(topo_edge_t e) {
  pnt3d_t result = {0, 0, 0};
  try {
    auto point = cast_to_topo(e)->center();
    result.x = point.X();
    result.y = point.Y();
    result.z = point.Z();
  } catch (...) {
  }
  return result;
}

double topo_edge_radius(topo_edge_t e) {
  try {
    return cast_to_topo(e)->radius();
  } catch (...) {
    return 0.0;
  }
}

pnt3d_t topo_edge_position_at(topo_edge_t e, double d, int mode) {
  pnt3d_t result = {0, 0, 0};
  try {
    auto point = cast_to_topo(e)->position_at(
        d, static_cast<flywave::topo::edge::ParamMode>(mode));
    result.x = point.X();
    result.y = point.Y();
    result.z = point.Z();
  } catch (...) {
  }
  return result;
}

void topo_edge_positions(topo_edge_t e, double *ds, int count, pnt3d_t *points,
                         int mode) {
  try {
    std::vector<double> dVec(ds, ds + count);
    auto result = cast_to_topo(e)->positions(
        dVec, static_cast<flywave::topo::edge::ParamMode>(mode));
    for (int i = 0; i < count; i++) {
      points[i].x = result[i].X();
      points[i].y = result[i].Y();
      points[i].z = result[i].Z();
    }
  } catch (...) {
    for (int i = 0; i < count; i++) {
      points[i] = {0, 0, 0};
    }
  }
}

void topo_edge_sample_uniform(topo_edge_t e, double n, pnt3d_t **points,
                              int *point_count, double **params,
                              int *param_count) {
  try {
    auto result = cast_to_topo(e)->sample_uniform(n);

    *point_count = static_cast<int>(result.first.size());
    *param_count = static_cast<int>(result.second.size());

    *points = new pnt3d_t[*point_count];
    *params = new double[*param_count];

    for (int i = 0; i < *point_count; i++) {
      (*points)[i].x = result.first[i].X();
      (*points)[i].y = result.first[i].Y();
      (*points)[i].z = result.first[i].Z();
    }

    for (int i = 0; i < *param_count; i++) {
      (*params)[i] = result.second[i];
    }
  } catch (...) {
    *point_count = 0;
    *param_count = 0;
    *points = nullptr;
    *params = nullptr;
  }
}

topo_location_t *topo_edge_location_at(topo_edge_t e, double d, int mode,
                                       int frame, bool planar) {
  try {
    auto loc = cast_to_topo(e)->location_at(
        d, static_cast<flywave::topo::edge::ParamMode>(mode),
        static_cast<flywave::topo::edge::FrameMode>(frame), planar);
    return new topo_location_t{.loc = loc};
  } catch (...) {
    return nullptr;
  }
}

topo_location_t **topo_edge_locations(topo_edge_t e, double *ds, int count,
                                      int mode, int frame, bool planar,
                                      int *result_count) {
  try {
    std::vector<double> dVec(ds, ds + count);
    auto result = cast_to_topo(e)->locations(
        dVec, static_cast<flywave::topo::edge::ParamMode>(mode),
        static_cast<flywave::topo::edge::FrameMode>(frame), planar);

    auto **locs = new topo_location_t *[result.size()];
    for (size_t i = 0; i < result.size(); i++) {
      locs[i] = new topo_location_t{.loc = result[i]};
    }
    *result_count = static_cast<int>(result.size());
    return locs;
  } catch (...) {
    *result_count = 0;
    return nullptr;
  }
}

int topo_edge_projected(topo_edge_t e, topo_face_t f, vec3d_t direction,
                        bool closest, topo_shape_t ***result,
                        int *result_count) {
  try {
    gp_Vec dir(direction.x, direction.y, direction.z);
    auto proj = cast_to_topo(e)->projected(*cast_to_topo(f), dir, closest);

    if (proj.which() == 0) {
      *result_count = 1;
      *result = new topo_shape_t *[1];
      *result[0] =
          new topo_shape_t{.shp = std::make_shared<flywave::topo::edge>(
                               boost::get<flywave::topo::shape>(proj))};
    } else {
      auto shapes = boost::get<std::vector<flywave::topo::shape>>(proj);
      *result_count = static_cast<int>(shapes.size());
      *result = new topo_shape_t *[*result_count];
      for (int i = 0; i < *result_count; i++) {
        (*result)[i] = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::shape>(shapes[i])};
      }
    }
    return 0;
  } catch (...) {
    *result_count = 0;
    *result = nullptr;
    return -1;
  }
}

double topo_edge_curvature_at(topo_edge_t e, double d, int mode,
                              double resolution) {
  try {
    return cast_to_topo(e)->curvature_at(
        d, static_cast<flywave::topo::edge::ParamMode>(mode), resolution);
  } catch (...) {
    return 0.0;
  }
}

void topo_edge_curvatures(topo_edge_t e, double *ds, int count,
                          double *curvatures, int mode, double resolution) {
  try {
    std::vector<double> dVec(ds, ds + count);
    auto result = cast_to_topo(e)->curvatures(
        dVec, static_cast<flywave::topo::edge::ParamMode>(mode), resolution);
    for (int i = 0; i < count; i++) {
      curvatures[i] = result[i];
    }
  } catch (...) {
    for (int i = 0; i < count; i++) {
      curvatures[i] = 0.0;
    }
  }
}

topo_face_t topo_make_face() {
  return topo_face_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::face>()}};
}

void topo_face_free(topo_face_t t) {
  if (t.shp) {
    delete t.shp;
  }
}

topo_face_t topo_face_make_face(topo_face_t F) {
  return topo_face_t{
      .shp = new topo_shape_t{
          .shp = std::make_shared<flywave::topo::face>(
              flywave::topo::face::make_face(*cast_to_topo(F)))}};
}

topo_face_t topo_face_make_face_from_plane(plane_t P) {
  return topo_face_t{.shp = new topo_shape_t{
                         .shp = std::make_shared<flywave::topo::face>(
                             flywave::topo::face::make_face(cast_to_gp(P)))}};
}

topo_face_t topo_face_make_face_from_cylinder(cylinder_t C) {
  return topo_face_t{.shp = new topo_shape_t{
                         .shp = std::make_shared<flywave::topo::face>(
                             flywave::topo::face::make_face(cast_to_gp(C)))}};
}

topo_face_t topo_face_make_face_from_cone(cone_t C) {
  return topo_face_t{.shp = new topo_shape_t{
                         .shp = std::make_shared<flywave::topo::face>(
                             flywave::topo::face::make_face(cast_to_gp(C)))}};
}

topo_face_t topo_face_make_face_from_sphere(sphere_t S) {
  return topo_face_t{.shp = new topo_shape_t{
                         .shp = std::make_shared<flywave::topo::face>(
                             flywave::topo::face::make_face(cast_to_gp(S)))}};
}

topo_face_t topo_face_make_face_from_torus(torus_t C) {
  return topo_face_t{.shp = new topo_shape_t{
                         .shp = std::make_shared<flywave::topo::face>(
                             flywave::topo::face::make_face(cast_to_gp(C)))}};
}

topo_face_t topo_face_make_face_from_surface(geom_surface_t *S,
                                             double TolDegen) {
  return topo_face_t{
      .shp = new topo_shape_t{
          .shp = std::make_shared<flywave::topo::face>(
              flywave::topo::face::make_face(S->handle, TolDegen))}};
}

topo_face_t topo_face_make_face_from_plane_p(plane_t P, double UMin,
                                             double UMax, double VMin,
                                             double VMax) {
  return topo_face_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::face>(
                                  flywave::topo::face::make_face(
                                      cast_to_gp(P), UMin, UMax, VMin, VMax))}};
}

topo_face_t topo_face_make_face_from_cylinder_p(cylinder_t C, double UMin,
                                                double UMax, double VMin,
                                                double VMax) {
  return topo_face_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::face>(
                                  flywave::topo::face::make_face(
                                      cast_to_gp(C), UMin, UMax, VMin, VMax))}};
}

topo_face_t topo_face_make_face_from_cone_p(cone_t C, double UMin, double UMax,
                                            double VMin, double VMax) {
  return topo_face_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::face>(
                                  flywave::topo::face::make_face(
                                      cast_to_gp(C), UMin, UMax, VMin, VMax))}};
}

topo_face_t topo_face_make_face_from_sphere_p(sphere_t S, double UMin,
                                              double UMax, double VMin,
                                              double VMax) {
  return topo_face_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::face>(
                                  flywave::topo::face::make_face(
                                      cast_to_gp(S), UMin, UMax, VMin, VMax))}};
}

topo_face_t topo_face_make_face_from_torus_p(torus_t C, double UMin,
                                             double UMax, double VMin,
                                             double VMax) {
  return topo_face_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::face>(
                                  flywave::topo::face::make_face(
                                      cast_to_gp(C), UMin, UMax, VMin, VMax))}};
}

topo_face_t topo_face_make_face_from_surface_p(geom_surface_t *S, double UMin,
                                               double UMax, double VMin,
                                               double VMax, double TolDegen) {
  return topo_face_t{
      .shp = new topo_shape_t{
          .shp = std::make_shared<flywave::topo::face>(
              flywave::topo::face::make_face(S->handle, UMin, UMax, VMin, VMax,
                                             TolDegen))}};
}

topo_face_t topo_face_make_face_from_wire_onlyplane(topo_wire_t W,
                                                    _Bool OnlyPlane) {
  return topo_face_t{
      .shp = new topo_shape_t{
          .shp = std::make_shared<flywave::topo::face>(
              flywave::topo::face::make_face(*cast_to_topo(W), OnlyPlane))}};
}

topo_face_t topo_face_make_face_from_plane_wire(plane_t P, topo_wire_t W,
                                                _Bool Inside) {
  return topo_face_t{.shp = new topo_shape_t{
                         .shp = std::make_shared<flywave::topo::face>(
                             flywave::topo::face::make_face(
                                 cast_to_gp(P), *cast_to_topo(W), Inside))}};
}

topo_face_t topo_face_make_face_from_cylinder_wire(cylinder_t C, topo_wire_t W,
                                                   _Bool Inside) {
  return topo_face_t{.shp = new topo_shape_t{
                         .shp = std::make_shared<flywave::topo::face>(
                             flywave::topo::face::make_face(
                                 cast_to_gp(C), *cast_to_topo(W), Inside))}};
}

topo_face_t topo_face_make_face_from_cone_wire(cone_t C, topo_wire_t W,
                                               _Bool Inside) {
  return topo_face_t{.shp = new topo_shape_t{
                         .shp = std::make_shared<flywave::topo::face>(
                             flywave::topo::face::make_face(
                                 cast_to_gp(C), *cast_to_topo(W), Inside))}};
}

topo_face_t topo_face_make_face_from_sphere_wire(sphere_t S, topo_wire_t W,
                                                 _Bool Inside) {
  return topo_face_t{.shp = new topo_shape_t{
                         .shp = std::make_shared<flywave::topo::face>(
                             flywave::topo::face::make_face(
                                 cast_to_gp(S), *cast_to_topo(W), Inside))}};
}

topo_face_t topo_face_make_face_from_torus_wire(torus_t C, topo_wire_t W,
                                                _Bool Inside) {
  return topo_face_t{.shp = new topo_shape_t{
                         .shp = std::make_shared<flywave::topo::face>(
                             flywave::topo::face::make_face(
                                 cast_to_gp(C), *cast_to_topo(W), Inside))}};
}

topo_face_t topo_face_make_face_from_surface_wire(geom_surface_t *S,
                                                  topo_wire_t W, _Bool Inside) {
  return topo_face_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::face>(
                                  flywave::topo::face::make_face(
                                      S->handle, *cast_to_topo(W), Inside))}};
}

topo_face_t topo_face_make_face_from_face_wire(topo_face_t F, topo_wire_t W) {
  return topo_face_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::face>(
                                  flywave::topo::face::make_face(
                                      *cast_to_topo(F), *cast_to_topo(W)))}};
}

topo_face_t topo_face_make_face_from_wire(topo_wire_t *wires, int count) {
  std::vector<flywave::topo::wire> ows;
  for (int i = 0; i < count; i++) {
    ows.emplace_back(*cast_to_topo(wires[i]));
  }
  return topo_face_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::face>(
                                  flywave::topo::face::make_face(ows))}};
}

topo_face_t topo_face_make_face_from_egdes(topo_edge_t *edges, int edgecount,
                                           pnt3d_t *points, int pcount) {
  std::vector<flywave::topo::edge> oes;
  std::vector<gp_Pnt> ops;
  for (int i = 0; i < edgecount; i++) {
    oes.emplace_back(*cast_to_topo(edges[i]));
  }

  for (int i = 0; i < pcount; i++) {
    ops.emplace_back(cast_to_gp(points[i]));
  }
  return topo_face_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::face>(
                                  flywave::topo::face::make_face(oes, ops))}};
}

topo_face_t topo_face_make_face_from_points(pnt3d_t *points, int count) {
  std::vector<gp_Pnt> ops;
  for (int i = 0; i < count; i++) {
    ops.emplace_back(cast_to_gp(points[i]));
  }
  return topo_face_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::face>(
                                  flywave::topo::face::make_face(ops))}};
}

topo_face_t *topo_face_make_from_wires(topo_wire_t outer, topo_wire_t *inners,
                                       int inner_count, int *result_count) {
  try {
    std::vector<flywave::topo::wire> innerWires;
    for (int i = 0; i < inner_count; i++) {
      innerWires.push_back(*cast_to_topo(inners[i]));
    }

    auto result =
        flywave::topo::face::make_from_wires(*cast_to_topo(outer), innerWires);

    *result_count = static_cast<int>(result.size());
    auto *faces = new topo_face_t[result.size()];
    for (size_t i = 0; i < result.size(); i++) {
      faces[i] =
          topo_face_t{.shp = new topo_shape_t{
                          .shp = std::make_shared<flywave::topo::face>(
                              flywave::topo::face::make_face(result[i]))}};
    }
    return faces;
  } catch (...) {
    return nullptr;
  }
}

void topo_face_list_free(topo_face_t *faces, int count) { delete[] faces; }

topo_face_t topo_face_make_complex(topo_shape_t **edges, int edge_count,
                                   topo_shape_t **constraints,
                                   int constraint_count, int continuity,
                                   int degree, int nb_pts_on_curve, int nb_iter,
                                   bool anisotropy, double tol2d, double tol3d,
                                   double tol_angle, double tol_curv,
                                   int max_degree, int max_segments) {
  try {
    std::vector<boost::variant<flywave::topo::wire, flywave::topo::edge>>
        edgeVec;
    for (int i = 0; i < edge_count; i++) {
      if (edges[i]->shp->shape_type() == TopAbs_EDGE) {
        edgeVec.push_back(flywave::topo::edge(edges[i]->shp->value()));
      } else if (edges[i]->shp->shape_type() == TopAbs_WIRE) {
        edgeVec.push_back(flywave::topo::wire(edges[i]->shp->value()));
      }
    }

    std::vector<
        boost::variant<flywave::topo::wire, flywave::topo::edge, gp_Pnt>>
        constraintVec;
    for (int i = 0; i < constraint_count; i++) {
      if (constraints[i]->shp->shape_type() == TopAbs_EDGE) {
        constraintVec.push_back(
            flywave::topo::edge(constraints[i]->shp->value()));
      } else if (constraints[i]->shp->shape_type() == TopAbs_WIRE) {
        constraintVec.push_back(
            flywave::topo::wire(constraints[i]->shp->value()));
      } else if (constraints[i]->shp->shape_type() == TopAbs_VERTEX) {
        constraintVec.push_back(
            (constraints[i])->shp->cast<flywave::topo::vertex>()->point());
      }
    }

    auto result = flywave::topo::face::make_face(
        edgeVec, constraintVec, static_cast<GeomAbs_Shape>(continuity), degree,
        nb_pts_on_curve, nb_iter, anisotropy, tol2d, tol3d, tol_angle, tol_curv,
        max_degree, max_segments);

    return topo_face_t{
        .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::face>(
                                    flywave::topo::face::make_face(result))}};
  } catch (...) {
    return topo_face_t{};
  }
}

topo_face_t topo_face_make_plane(pnt3d_t base_point, dir3d_t direction,
                                 double *length, double *width) {
  try {
    gp_Pnt basePnt(base_point.x, base_point.y, base_point.z);
    gp_Dir dir(direction.x, direction.y, direction.z);

    boost::optional<double> lenOpt, widthOpt;
    if (length)
      lenOpt = *length;
    if (width)
      widthOpt = *width;

    auto result =
        flywave::topo::face::make_plane(basePnt, dir, lenOpt, widthOpt);

    return topo_face_t{
        .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::face>(
                                    flywave::topo::face::make_face(result))}};
  } catch (...) {
    return topo_face_t{};
  }
}

topo_face_t topo_face_make_spline_approx(pnt3d_t *points, int *point_counts,
                                         int point_array_size, double tol,
                                         double *smoothing, int min_degree,
                                         int max_degree) {
  try {
    std::vector<std::vector<gp_Pnt>> pointVec;
    int offset = 0;
    for (int i = 0; i < point_array_size; i++) {
      std::vector<gp_Pnt> curvePoints;
      for (int j = 0; j < point_counts[i]; j++) {
        auto &p = points[offset++];
        curvePoints.emplace_back(p.x, p.y, p.z);
      }
      pointVec.push_back(curvePoints);
    }

    std::tuple<double, double, double> smoothParams;
    if (smoothing) {
      smoothParams = std::make_tuple(smoothing[0], smoothing[1], smoothing[2]);
    }

    auto result = flywave::topo::face::make_spline_approx(
        pointVec, tol, smoothing ? &smoothParams : nullptr, min_degree,
        max_degree);

    return topo_face_t{
        .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::face>(
                                    flywave::topo::face::make_face(result))}};
  } catch (...) {
    return topo_face_t{};
  }
}

int topo_face_num_wires(topo_face_t f) {
  auto opt = cast_to_topo(f);
  if (opt) {
    return opt->num_wires();
  }
  return -1;
}

int topo_face_num_faces(topo_face_t f) {
  auto opt = cast_to_topo(f);
  if (opt) {
    return opt->num_faces();
  }
  return -1;
}

double topo_face_area(topo_face_t f) {
  auto opt = cast_to_topo(f);
  if (opt) {
    return opt->area();
  }
  return 0.0;
}

float topo_face_tolerance(topo_face_t f) {
  auto opt = cast_to_topo(f);
  if (opt) {
    return opt->tolerance();
  }
  return 0.0f;
}

bbox_t topo_face_inertia(topo_face_t f) {
  auto opt = cast_to_topo(f);
  if (opt) {
    return cast_from_gp(opt->inertia());
  }
  return bbox_t{0, 0, 0, 0, 0, 0};
}

pnt3d_t topo_face_centre_of_mass(topo_face_t f) {
  auto opt = cast_to_topo(f);
  if (opt) {
    return cast_from_gp(opt->centre_of_mass());
  }
  return pnt3d_t{0, 0, 0};
}

topo_plane_t *topo_face_to_plane(topo_face_t f) {
  auto opt = cast_to_topo(f);
  if (opt) {
    return new topo_plane_t{.plane =
                                flywave::topo::topo_plane(opt->to_plane())};
  }
}

int topo_face_offset(topo_face_t f, double offset, double tolerance) {
  auto opt = cast_to_topo(f);
  if (opt) {
    return opt->offset(offset, tolerance);
  }
  return -1;
}

int topo_face_extrude(topo_face_t f, topo_shape_t *shp, pnt3d_t p1,
                      pnt3d_t p2) {
  auto opt = cast_to_topo(f);
  if (opt) {
    return opt->extrude(*shp->shp, cast_to_gp(p1), cast_to_gp(p2));
  }
  return -1;
}

int topo_face_revolve(topo_face_t f, topo_shape_t *shp, pnt3d_t p1, pnt3d_t p2,
                      double angle) {
  auto opt = cast_to_topo(f);
  if (opt) {
    return opt->revolve(*shp->shp, cast_to_gp(p1), cast_to_gp(p2), angle);
  }
  return -1;
}

int topo_face_sweep(topo_face_t f, topo_wire_t spine, topo_shape_t **profiles,
                    int profilesCount, int cornerMode) {
  try {
    auto opt = cast_to_topo(f);
    if (opt) {
      std::vector<flywave::topo::shape> prs;
      for (int i = 0; i < profilesCount; i++) {
        prs.emplace_back(*profiles[i]->shp);
      }
      return opt->sweep(*cast_to_topo(spine), prs, cornerMode);
    }
  } catch (...) {
    return -1;
  }
  return -1;
}

int topo_face_sweep_wire(topo_face_t f, topo_wire_t spine,
                         topo_wire_t *profiles, int profilesCount,
                         int cornerMode) {
  try {
    auto opt = cast_to_topo(f);
    if (opt) {
      std::vector<flywave::topo::shape> prs;
      for (int i = 0; i < profilesCount; i++) {
        prs.emplace_back(*profiles[i].shp->shp);
      }
      return opt->sweep(*cast_to_topo(spine), prs, cornerMode);
    }
  } catch (...) {
    return -1;
  }
  return -1;
}

int topo_face_loft(topo_face_t f, topo_shape_t **profiles, int profilesCount,
                   bool ruled, double tolerance) {
  auto opt = cast_to_topo(f);
  if (opt) {
    std::vector<flywave::topo::shape> prs;
    for (int i = 0; i < profilesCount; i++) {
      prs.emplace_back(*profiles[i]->shp);
    }
    return opt->loft(prs, ruled, tolerance);
  }
  return -1;
}

int topo_face_boolean(topo_face_t f, topo_face_t tool, int op) {
  auto opt = cast_to_topo(f);
  if (opt) {
    return opt->boolean(*cast_to_topo(tool),
                        static_cast<flywave::topo::bool_op_type>(op));
  }
  return -1;
}

void topo_face_uv_bounds(topo_face_t f, double *u_min, double *u_max,
                         double *v_min, double *v_max) {
  try {
    auto bounds = cast_to_topo(f)->uv_bounds();
    *u_min = std::get<0>(bounds);
    *u_max = std::get<1>(bounds);
    *v_min = std::get<2>(bounds);
    *v_max = std::get<3>(bounds);
  } catch (...) {
    *u_min = *u_max = *v_min = *v_max = 0.0;
  }
}

void topo_face_param_at(topo_face_t f, pnt3d_t pt, double *u, double *v) {
  try {
    gp_Pnt point(pt.x, pt.y, pt.z);
    auto params = cast_to_topo(f)->param_at(point);
    *u = params.first;
    *v = params.second;
  } catch (...) {
    *u = *v = 0.0;
  }
}

void topo_face_params(topo_face_t f, pnt3d_t *pts, int count, double *us,
                      double *vs, double tol) {
  try {
    std::vector<gp_Pnt> points;
    for (int i = 0; i < count; i++) {
      points.emplace_back(pts[i].x, pts[i].y, pts[i].z);
    }
    auto params = cast_to_topo(f)->params(points, tol);
    for (int i = 0; i < count; i++) {
      us[i] = params.first[i];
      vs[i] = params.second[i];
    }
  } catch (...) {
    for (int i = 0; i < count; i++) {
      us[i] = vs[i] = 0.0;
    }
  }
}

pnt3d_t topo_face_position_at(topo_face_t f, double u, double v) {
  pnt3d_t result = {0, 0, 0};
  try {
    auto point = cast_to_topo(f)->position_at(u, v);
    result.x = point.X();
    result.y = point.Y();
    result.z = point.Z();
  } catch (...) {
  }
  return result;
}

void topo_face_positions(topo_face_t f, double *us, double *vs, int count,
                         pnt3d_t *points) {
  try {
    std::vector<std::pair<double, double>> uvs;
    for (int i = 0; i < count; i++) {
      uvs.emplace_back(us[i], vs[i]);
    }
    auto result = cast_to_topo(f)->positions(uvs);
    for (int i = 0; i < count; i++) {
      points[i].x = result[i].X();
      points[i].y = result[i].Y();
      points[i].z = result[i].Z();
    }
  } catch (...) {
    for (int i = 0; i < count; i++) {
      points[i] = {0, 0, 0};
    }
  }
}

vec3d_t topo_face_normal_at(topo_face_t f, pnt3d_t *location) {
  vec3d_t result = {0, 0, 0};
  try {
    gp_Pnt loc(location ? location->x : 0, location ? location->y : 0,
               location ? location->z : 0);
    auto normal = cast_to_topo(f)->normal_at(location ? &loc : nullptr);
    result.x = normal.X();
    result.y = normal.Y();
    result.z = normal.Z();
  } catch (...) {
  }
  return result;
}

void topo_face_normal_at_uv(topo_face_t f, double u, double v, vec3d_t *normal,
                            pnt3d_t *point) {
  try {
    auto result = cast_to_topo(f)->normal_at(u, v);
    normal->x = result.first.X();
    normal->y = result.first.Y();
    normal->z = result.first.Z();
    point->x = result.second.X();
    point->y = result.second.Y();
    point->z = result.second.Z();
  } catch (...) {
    *normal = {0, 0, 0};
    *point = {0, 0, 0};
  }
}

void topo_face_normals(topo_face_t f, double *us, double *vs, int count,
                       vec3d_t *normals, pnt3d_t *points) {
  try {
    std::vector<double> uVec(us, us + count);
    std::vector<double> vVec(vs, vs + count);
    auto result = cast_to_topo(f)->normals(uVec, vVec);

    for (int i = 0; i < count; i++) {
      normals[i].x = result.first[i].X();
      normals[i].y = result.first[i].Y();
      normals[i].z = result.first[i].Z();
      points[i].x = result.second[i].X();
      points[i].y = result.second[i].Y();
      points[i].z = result.second[i].Z();
    }
  } catch (...) {
    for (int i = 0; i < count; i++) {
      normals[i] = {0, 0, 0};
      points[i] = {0, 0, 0};
    }
  }
}

topo_face_t topo_face_fillet2d(topo_face_t f, double radius,
                               topo_vertex_t *vertices, int count) {
  try {
    std::vector<flywave::topo::vertex> verts;
    for (int i = 0; i < count; i++) {
      verts.push_back(*cast_to_topo(vertices[i]));
    }
    auto result = cast_to_topo(f)->fillet2d(radius, verts);
    return topo_face_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::shell>(result)}};
  } catch (...) {
    return topo_face_t{nullptr};
  }
}

topo_face_t topo_face_chamfer2d(topo_face_t f, double distance,
                                topo_vertex_t *vertices, int count) {
  try {
    std::vector<flywave::topo::vertex> verts;
    for (int i = 0; i < count; i++) {
      verts.push_back(*cast_to_topo(vertices[i]));
    }
    auto result = cast_to_topo(f)->chamfer2d(distance, verts);
    return topo_face_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::shell>(result)}};
  } catch (...) {
    return topo_face_t{nullptr};
  }
}

topo_solid_t topo_face_thicken(topo_face_t f, double thickness) {
  try {
    auto result = cast_to_topo(f)->thicken(thickness);
    return topo_solid_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::shell>(result)}};
  } catch (...) {
    return topo_solid_t{nullptr};
  }
}

topo_face_t topo_face_project(topo_face_t f, topo_face_t other,
                              vec3d_t direction) {
  try {
    gp_Vec dir(direction.x, direction.y, direction.z);
    auto result = cast_to_topo(f)->project(*cast_to_topo(other), dir);
    return topo_face_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::shell>(result)}};
  } catch (...) {
    return topo_face_t{nullptr};
  }
}

topo_face_t topo_face_to_arcs(topo_face_t f, double tolerance) {
  try {
    auto result = cast_to_topo(f)->to_arcs(tolerance);
    return topo_face_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::shell>(result)}};
  } catch (...) {
    return topo_face_t{nullptr};
  }
}

topo_face_t topo_face_trim(topo_face_t f, double u0, double u1, double v0,
                           double v1, double tol) {
  try {
    auto result = cast_to_topo(f)->trim(u0, u1, v0, v1, tol);
    return topo_face_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::shell>(result)}};
  } catch (...) {
    return topo_face_t{nullptr};
  }
}

topo_edge_t topo_face_isoline(topo_face_t f, double param,
                              const char *direction) {
  try {
    std::string dir = direction ? direction : "v";
    auto result = cast_to_topo(f)->isoline(param, dir);
    return topo_edge_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::shell>(result)}};
  } catch (...) {
    return topo_edge_t{nullptr};
  }
}

topo_edge_t *topo_face_isolines(topo_face_t f, double *params, int count,
                                const char *direction, int *result_count) {
  try {
    std::vector<double> paramVec(params, params + count);
    std::string dir = direction ? direction : "v";
    auto result = cast_to_topo(f)->isolines(paramVec, dir);

    auto *edges = new topo_edge_t[result.size()];
    for (size_t i = 0; i < result.size(); i++) {
      edges[i] = topo_edge_t{
          .shp = new topo_shape_t{
              .shp = std::make_shared<flywave::topo::shell>(result[i])}};
    }
    *result_count = static_cast<int>(result.size());
    return edges;
  } catch (...) {
    *result_count = 0;
    return nullptr;
  }
}

topo_wire_t topo_face_outer_wire(topo_face_t f) {
  try {
    auto result = cast_to_topo(f)->outer_wire();
    return topo_wire_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::shell>(result)}};
  } catch (...) {
    return topo_wire_t{nullptr};
  }
}

topo_wire_t *topo_face_inner_wires(topo_face_t f, int *count) {
  try {
    auto result = cast_to_topo(f)->inner_wires();
    auto *wires = new topo_wire_t[result.size()];
    for (size_t i = 0; i < result.size(); i++) {
      wires[i] = topo_wire_t{
          .shp = new topo_shape_t{
              .shp = std::make_shared<flywave::topo::shell>(result[i])}};
    }
    *count = static_cast<int>(result.size());
    return wires;
  } catch (...) {
    *count = 0;
    return nullptr;
  }
}

topo_shell_t topo_make_shell() {
  return topo_shell_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::shell>()}};
}

void topo_shell_free(topo_shell_t t) {
  if (t.shp) {
    delete t.shp;
  }
}

topo_shell_t topo_shell_make_shell_from_surface(geom_surface_t *S,
                                                _Bool Segment) {
  return topo_shell_t{
      .shp = new topo_shape_t{
          .shp = std::make_shared<flywave::topo::shell>(
              flywave::topo::shell::make_shell(S->handle, Segment))}};
}

topo_shell_t topo_shell_make_shell_from_surface_p(geom_surface_t *S,
                                                  double UMin, double UMax,
                                                  double VMin, double VMax,
                                                  _Bool Segment) {
  return topo_shell_t{
      .shp = new topo_shape_t{
          .shp = std::make_shared<flywave::topo::shell>(
              flywave::topo::shell::make_shell(S->handle, UMin, UMax, VMin,
                                               VMax, Segment))}};
}

topo_shell_t topo_shell_make_shell_from_box(double dx, double dy, double dz) {
  return topo_shell_t{
      .shp = new topo_shape_t{
          .shp = std::make_shared<flywave::topo::shell>(
              flywave::topo::shell::make_shell_from_box(dx, dy, dz))}};
}

topo_shell_t topo_shell_make_shell_from_box_point(pnt3d_t P, double dx,
                                                  double dy, double dz) {
  return topo_shell_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::shell>(
                                  flywave::topo::shell::make_shell_from_box(
                                      cast_to_gp(P), dx, dy, dz))}};
}

topo_shell_t topo_shell_make_shell_from_box_two_point(pnt3d_t P1, pnt3d_t P2) {
  return topo_shell_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::shell>(
                                  flywave::topo::shell::make_shell_from_box(
                                      cast_to_gp(P1), cast_to_gp(P2)))}};
}

topo_shell_t topo_shell_make_shell_from_box_axis2(axis2_t Axes, double dx,
                                                  double dy, double dz) {
  return topo_shell_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::shell>(
                                  flywave::topo::shell::make_shell_from_box(
                                      cast_to_gp(Axes), dx, dy, dz))}};
}

topo_shell_t topo_shell_make_shell_from_cylinder(double R, double H) {
  return topo_shell_t{
      .shp = new topo_shape_t{
          .shp = std::make_shared<flywave::topo::shell>(
              flywave::topo::shell::make_shell_from_cylinder(R, H))}};
}

topo_shell_t topo_shell_make_shell_from_cylinder_angle(double R, double H,
                                                       double Angle) {
  return topo_shell_t{
      .shp = new topo_shape_t{
          .shp = std::make_shared<flywave::topo::shell>(
              flywave::topo::shell::make_shell_from_cylinder(R, H, Angle))}};
}

topo_shell_t topo_shell_make_shell_from_cylinder_axis2(axis2_t Axes, double R,
                                                       double H) {
  return topo_shell_t{.shp = new topo_shape_t{
                          .shp = std::make_shared<flywave::topo::shell>(
                              flywave::topo::shell::make_shell_from_cylinder(
                                  cast_to_gp(Axes), R, H))}};
}

topo_shell_t topo_shell_make_shell_from_cylinder_axis2_angle(axis2_t Axes,
                                                             double R, double H,
                                                             double Angle) {
  return topo_shell_t{.shp = new topo_shape_t{
                          .shp = std::make_shared<flywave::topo::shell>(
                              flywave::topo::shell::make_shell_from_cylinder(
                                  cast_to_gp(Axes), R, H, Angle))}};
}

topo_shell_t topo_shell_make_shell_from_cone(double R1, double R2, double H) {
  return topo_shell_t{
      .shp = new topo_shape_t{
          .shp = std::make_shared<flywave::topo::shell>(
              flywave::topo::shell::make_shell_from_cone(R1, R2, H))}};
}

topo_shell_t topo_shell_make_shell_from_cone_angle(double R1, double R2,
                                                   double H, double angle) {
  return topo_shell_t{
      .shp = new topo_shape_t{
          .shp = std::make_shared<flywave::topo::shell>(
              flywave::topo::shell::make_shell_from_cone(R1, R2, H, angle))}};
}

topo_shell_t topo_shell_make_shell_from_cone_axis2(axis2_t Axes, double R1,
                                                   double R2, double H) {
  return topo_shell_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::shell>(
                                  flywave::topo::shell::make_shell_from_cone(
                                      cast_to_gp(Axes), R1, R2, H))}};
}

topo_shell_t topo_shell_make_shell_from_cone_axis2_angle(axis2_t Axes,
                                                         double R1, double R2,
                                                         double H,
                                                         double angle) {
  return topo_shell_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::shell>(
                                  flywave::topo::shell::make_shell_from_cone(
                                      cast_to_gp(Axes), R1, R2, H, angle))}};
}

topo_shell_t topo_shell_make_shell_from_revolution(geom_curve_t *Meridian) {
  return topo_shell_t{.shp = new topo_shape_t{
                          .shp = std::make_shared<flywave::topo::shell>(
                              flywave::topo::shell::make_shell_from_revolution(
                                  Meridian->handle))}};
}

topo_shell_t topo_shell_make_shell_from_revolution_angle(geom_curve_t *Meridian,
                                                         double angle) {
  return topo_shell_t{.shp = new topo_shape_t{
                          .shp = std::make_shared<flywave::topo::shell>(
                              flywave::topo::shell::make_shell_from_revolution(
                                  Meridian->handle, angle))}};
}

topo_shell_t topo_shell_make_shell_from_revolution_limit(geom_curve_t *Meridian,
                                                         double VMin,
                                                         double VMax) {
  return topo_shell_t{.shp = new topo_shape_t{
                          .shp = std::make_shared<flywave::topo::shell>(
                              flywave::topo::shell::make_shell_from_revolution(
                                  Meridian->handle, VMin, VMax))}};
}

topo_shell_t topo_shell_make_shell_from_revolution_limit_angle(
    geom_curve_t *Meridian, double VMin, double VMax, double angle) {
  return topo_shell_t{.shp = new topo_shape_t{
                          .shp = std::make_shared<flywave::topo::shell>(
                              flywave::topo::shell::make_shell_from_revolution(
                                  Meridian->handle, VMin, VMax, angle))}};
}

topo_shell_t
topo_shell_make_shell_from_revolution_axis2(axis2_t Axes,
                                            geom_curve_t *Meridian) {
  return topo_shell_t{.shp = new topo_shape_t{
                          .shp = std::make_shared<flywave::topo::shell>(
                              flywave::topo::shell::make_shell_from_revolution(
                                  cast_to_gp(Axes), Meridian->handle))}};
}

topo_shell_t topo_shell_make_shell_from_revolution_axis2_angle(
    axis2_t Axes, geom_curve_t *Meridian, double angle) {
  return topo_shell_t{.shp = new topo_shape_t{
                          .shp = std::make_shared<flywave::topo::shell>(
                              flywave::topo::shell::make_shell_from_revolution(
                                  cast_to_gp(Axes), Meridian->handle, angle))}};
}

topo_shell_t topo_shell_make_shell_from_revolution_axis2_limit(
    axis2_t Axes, geom_curve_t *Meridian, double VMin, double VMax) {
  return topo_shell_t{
      .shp = new topo_shape_t{
          .shp = std::make_shared<flywave::topo::shell>(
              flywave::topo::shell::make_shell_from_revolution(
                  cast_to_gp(Axes), Meridian->handle, VMin, VMax))}};
}

topo_shell_t topo_shell_make_shell_from_revolution_axis2_limit_angle(
    axis2_t Axes, geom_curve_t *Meridian, double VMin, double VMax,
    double angle) {
  return topo_shell_t{
      .shp = new topo_shape_t{
          .shp = std::make_shared<flywave::topo::shell>(
              flywave::topo::shell::make_shell_from_revolution(
                  cast_to_gp(Axes), Meridian->handle, VMin, VMax, angle))}};
}

topo_shell_t topo_shell_make_shell_from_sphere(double R) {
  return topo_shell_t{
      .shp = new topo_shape_t{
          .shp = std::make_shared<flywave::topo::shell>(
              flywave::topo::shell::make_shell_from_sphere(R))}};
}

topo_shell_t topo_shell_make_shell_from_sphere_angle(double R, double angle) {
  return topo_shell_t{
      .shp = new topo_shape_t{
          .shp = std::make_shared<flywave::topo::shell>(
              flywave::topo::shell::make_shell_from_sphere(R, angle))}};
}

topo_shell_t topo_shell_make_shell_from_sphere_two_angle(double R,
                                                         double angle1,
                                                         double angle2) {
  return topo_shell_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::shell>(
                                  flywave::topo::shell::make_shell_from_sphere(
                                      R, angle1, angle2))}};
}

topo_shell_t topo_shell_make_shell_from_sphere_three_angle(double R,
                                                           double angle1,
                                                           double angle2,
                                                           double angle3) {
  return topo_shell_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::shell>(
                                  flywave::topo::shell::make_shell_from_sphere(
                                      R, angle1, angle2, angle3))}};
}

topo_shell_t topo_shell_make_shell_from_sphere_center_raduis(pnt3d_t Center,
                                                             double R) {
  return topo_shell_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::shell>(
                                  flywave::topo::shell::make_shell_from_sphere(
                                      cast_to_gp(Center), R))}};
}

topo_shell_t topo_shell_make_shell_from_sphere_center_angle(pnt3d_t Center,
                                                            double R,
                                                            double angle) {
  return topo_shell_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::shell>(
                                  flywave::topo::shell::make_shell_from_sphere(
                                      cast_to_gp(Center), R, angle))}};
}

topo_shell_t topo_shell_make_shell_from_sphere_center_two_angle(pnt3d_t Center,
                                                                double R,
                                                                double angle1,
                                                                double angle2) {
  return topo_shell_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::shell>(
                                  flywave::topo::shell::make_shell_from_sphere(
                                      cast_to_gp(Center), R, angle1, angle2))}};
}

topo_shell_t topo_shell_make_shell_from_sphere_center_three_angle(
    pnt3d_t Center, double R, double angle1, double angle2, double angle3) {
  return topo_shell_t{
      .shp = new topo_shape_t{
          .shp = std::make_shared<flywave::topo::shell>(
              flywave::topo::shell::make_shell_from_sphere(
                  cast_to_gp(Center), R, angle1, angle2, angle3))}};
}

topo_shell_t topo_shell_make_shell_from_sphere_axis2(axis2_t Axis, double R) {
  return topo_shell_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::shell>(
                                  flywave::topo::shell::make_shell_from_sphere(
                                      cast_to_gp(Axis), R))}};
}

topo_shell_t topo_shell_make_shell_from_sphere_axis2_raduis(axis2_t Axis,
                                                            double R,
                                                            double angle) {
  return topo_shell_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::shell>(
                                  flywave::topo::shell::make_shell_from_sphere(
                                      cast_to_gp(Axis), R, angle))}};
}

topo_shell_t topo_shell_make_shell_from_sphere_axis2_two_angle(axis2_t Axis,
                                                               double R,
                                                               double angle1,
                                                               double angle2) {
  return topo_shell_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::shell>(
                                  flywave::topo::shell::make_shell_from_sphere(
                                      cast_to_gp(Axis), R, angle1, angle2))}};
}

topo_shell_t topo_shell_make_shell_from_sphere_axis2_three_angle(
    axis2_t Axis, double R, double angle1, double angle2, double angle3) {
  return topo_shell_t{
      .shp = new topo_shape_t{
          .shp = std::make_shared<flywave::topo::shell>(
              flywave::topo::shell::make_shell_from_sphere(
                  cast_to_gp(Axis), R, angle1, angle2, angle3))}};
}

topo_shell_t topo_shell_make_shell_from_torus(double R1, double R2) {
  return topo_shell_t{
      .shp = new topo_shape_t{
          .shp = std::make_shared<flywave::topo::shell>(
              flywave::topo::shell::make_shell_from_torus(R1, R2))}};
}

topo_shell_t topo_shell_make_shell_from_torus_angle(double R1, double R2,
                                                    double angle) {
  return topo_shell_t{
      .shp = new topo_shape_t{
          .shp = std::make_shared<flywave::topo::shell>(
              flywave::topo::shell::make_shell_from_torus(R1, R2, angle))}};
}

topo_shell_t topo_shell_make_shell_from_torus_two_angle(double R1, double R2,
                                                        double angle1,
                                                        double angle2) {
  return topo_shell_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::shell>(
                                  flywave::topo::shell::make_shell_from_torus(
                                      R1, R2, angle1, angle2))}};
}

topo_shell_t topo_shell_make_shell_from_torus_three_angle(double R1, double R2,
                                                          double angle1,
                                                          double angle2,
                                                          double angle) {
  return topo_shell_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::shell>(
                                  flywave::topo::shell::make_shell_from_torus(
                                      R1, R2, angle1, angle2, angle))}};
}

topo_shell_t topo_shell_make_shell_from_torus_axis2(axis2_t Axes, double R1,
                                                    double R2) {
  return topo_shell_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::shell>(
                                  flywave::topo::shell::make_shell_from_torus(
                                      cast_to_gp(Axes), R1, R2))}};
}

topo_shell_t topo_shell_make_shell_from_torus_axis2_angle(axis2_t Axes,
                                                          double R1, double R2,
                                                          double angle) {
  return topo_shell_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::shell>(
                                  flywave::topo::shell::make_shell_from_torus(
                                      cast_to_gp(Axes), R1, R2, angle))}};
}

topo_shell_t topo_shell_make_shell_from_torus_axis2_two_angle(
    axis2_t Axes, double R1, double R2, double angle1, double angle2) {
  return topo_shell_t{.shp = new topo_shape_t{
                          .shp = std::make_shared<flywave::topo::shell>(
                              flywave::topo::shell::make_shell_from_torus(
                                  cast_to_gp(Axes), R1, R2, angle1, angle2))}};
}

topo_shell_t topo_shell_make_shell_from_torus_axis2_three_angle(
    axis2_t Axes, double R1, double R2, double angle1, double angle2,
    double angle) {
  return topo_shell_t{
      .shp = new topo_shape_t{
          .shp = std::make_shared<flywave::topo::shell>(
              flywave::topo::shell::make_shell_from_torus(
                  cast_to_gp(Axes), R1, R2, angle1, angle2, angle))}};
}

topo_shell_t topo_shell_make_shell_from_wedge(double dx, double dy, double dz,
                                              double ltx) {
  return topo_shell_t{
      .shp = new topo_shape_t{
          .shp = std::make_shared<flywave::topo::shell>(
              flywave::topo::shell::make_shell_from_wedge(dx, dy, dz, ltx))}};
}

topo_shell_t topo_shell_make_shell_from_wedge_axis2(axis2_t Axes, double dx,
                                                    double dy, double dz,
                                                    double ltx) {
  return topo_shell_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::shell>(
                                  flywave::topo::shell::make_shell_from_wedge(
                                      cast_to_gp(Axes), dx, dy, dz, ltx))}};
}

topo_shell_t topo_shell_make_shell_from_wedge_limit(double dx, double dy,
                                                    double dz, double xmin,
                                                    double zmin, double xmax,
                                                    double zmax) {
  return topo_shell_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::shell>(
                                  flywave::topo::shell::make_shell_from_wedge(
                                      dx, dy, dz, xmin, zmin, xmax, zmax))}};
}

topo_shell_t topo_shell_make_shell_from_wedge_axis2_limit(
    axis2_t Axes, double dx, double dy, double dz, double xmin, double zmin,
    double xmax, double zmax) {
  return topo_shell_t{
      .shp = new topo_shape_t{
          .shp = std::make_shared<flywave::topo::shell>(
              flywave::topo::shell::make_shell_from_wedge(
                  cast_to_gp(Axes), dx, dy, dz, xmin, zmin, xmax, zmax))}};
}

int topo_shell_sweep(topo_shell_t ss, topo_wire_t spine,
                     topo_shape_t **profiles, int count, int cornerMode) {
  try {
    auto opt = cast_to_topo(ss);
    if (opt) {
      std::vector<flywave::topo::shape> pros;
      for (int i = 0; i < count; i++) {
        pros.emplace_back(*profiles[i]->shp);
      }
      return opt->sweep(*cast_to_topo(spine), pros, cornerMode);
    }
  } catch (...) {
    return -1;
  }
  return -1;
}

int topo_shell_sweep_wire(topo_shell_t ss, topo_wire_t spine,
                          topo_wire_t *profiles, int count, int cornerMode) {
  try {
    auto opt = cast_to_topo(ss);
    if (opt) {
      std::vector<flywave::topo::shape> pros;
      for (int i = 0; i < count; i++) {
        pros.emplace_back(*profiles[i].shp->shp);
      }
      return opt->sweep(*cast_to_topo(spine), pros, cornerMode);
    }
  } catch (...) {
    return -1;
  }
  return -1;
}

void topo_solid_free(topo_solid_t t) {
  if (t.shp) {
    delete t.shp;
  }
}
topo_solid_t topo_solid_make_solid_from_comp_solid(topo_comp_solid_t S) {
  return topo_solid_t{
      .shp = new topo_shape_t{
          .shp = std::make_shared<flywave::topo::solid>(
              flywave::topo::solid::make_solid(*cast_to_topo(S)))}};
}

topo_solid_t topo_solid_make_solid_from_shell(topo_shell_t S) {
  return topo_solid_t{
      .shp = new topo_shape_t{
          .shp = std::make_shared<flywave::topo::solid>(
              flywave::topo::solid::make_solid(*cast_to_topo(S)))}};
}

topo_solid_t topo_solid_make_solid_from_two_shell(topo_shell_t S1,
                                                  topo_shell_t S2) {
  return topo_solid_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::solid>(
                                  flywave::topo::solid::make_solid(
                                      *cast_to_topo(S1), *cast_to_topo(S2)))}};
}

topo_solid_t topo_solid_make_solid_from_three_shell(topo_shell_t S1,
                                                    topo_shell_t S2,
                                                    topo_shell_t S3) {
  return topo_solid_t{
      .shp = new topo_shape_t{
          .shp = std::make_shared<flywave::topo::solid>(
              flywave::topo::solid::make_solid(
                  *cast_to_topo(S1), *cast_to_topo(S2), *cast_to_topo(S3)))}};
}

topo_solid_t topo_solid_make_solid_from_shells(topo_shell_t *shells,
                                               int count) {
  std::vector<flywave::topo::shell> shels;
  for (int i = 0; i < count; i++) {
    shels.emplace_back(*cast_to_topo(shells[i]));
  }
  return topo_solid_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::solid>(
                                  flywave::topo::solid::make_solid(shels))}};
}

topo_solid_t topo_solid_make_solid_from_solid(topo_solid_t So) {
  return topo_solid_t{
      .shp = new topo_shape_t{
          .shp = std::make_shared<flywave::topo::solid>(
              flywave::topo::solid::make_solid(*cast_to_topo(So)))}};
}

topo_solid_t topo_solid_make_solid_from_solid_shell(topo_solid_t So,
                                                    topo_shell_t S) {
  return topo_solid_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::solid>(
                                  flywave::topo::solid::make_solid(
                                      *cast_to_topo(So), *cast_to_topo(S)))}};
}

topo_solid_t topo_solid_make_solid_from_faces(topo_face_t *faces, int count,
                                              double tolerance) {
  std::vector<flywave::topo::face> cfaces;
  for (int i = 0; i < count; i++) {
    cfaces.emplace_back(*cast_to_topo(faces[i]));
  }
  return topo_solid_t{
      .shp = new topo_shape_t{
          .shp = std::make_shared<flywave::topo::solid>(
              flywave::topo::solid::make_solid(cfaces, tolerance))}};
}

topo_solid_t topo_solid_make_solid_from_box(double dx, double dy, double dz) {
  return topo_solid_t{
      .shp = new topo_shape_t{
          .shp = std::make_shared<flywave::topo::solid>(
              flywave::topo::solid::make_solid_from_box(dx, dy, dz))}};
}

topo_solid_t topo_solid_make_solid_from_box_point(pnt3d_t P, double dx,
                                                  double dy, double dz) {
  return topo_solid_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::solid>(
                                  flywave::topo::solid::make_solid_from_box(
                                      cast_to_gp(P), dx, dy, dz))}};
}

topo_solid_t topo_solid_make_solid_from_box_two_point(pnt3d_t P1, pnt3d_t P2) {
  return topo_solid_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::solid>(
                                  flywave::topo::solid::make_solid_from_box(
                                      cast_to_gp(P1), cast_to_gp(P2)))}};
}

topo_solid_t topo_solid_make_solid_from_box_axis2(axis2_t Axes, double dx,
                                                  double dy, double dz) {
  return topo_solid_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::solid>(
                                  flywave::topo::solid::make_solid_from_box(
                                      cast_to_gp(Axes), dx, dy, dz))}};
}

topo_solid_t topo_solid_make_solid_from_cylinder(double R, double H) {
  return topo_solid_t{
      .shp = new topo_shape_t{
          .shp = std::make_shared<flywave::topo::solid>(
              flywave::topo::solid::make_solid_from_cylinder(R, H))}};
}

topo_solid_t topo_solid_make_solid_from_cylinder_angle(double R, double H,
                                                       double Angle) {
  return topo_solid_t{
      .shp = new topo_shape_t{
          .shp = std::make_shared<flywave::topo::solid>(
              flywave::topo::solid::make_solid_from_cylinder(R, H, Angle))}};
}

topo_solid_t topo_solid_make_solid_from_cylinder_axis2(axis2_t Axes, double R,
                                                       double H) {
  return topo_solid_t{.shp = new topo_shape_t{
                          .shp = std::make_shared<flywave::topo::solid>(
                              flywave::topo::solid::make_solid_from_cylinder(
                                  cast_to_gp(Axes), R, H))}};
}

topo_solid_t topo_solid_make_solid_from_cylinder_axis2_angle(axis2_t Axes,
                                                             double R, double H,
                                                             double Angle) {
  return topo_solid_t{.shp = new topo_shape_t{
                          .shp = std::make_shared<flywave::topo::solid>(
                              flywave::topo::solid::make_solid_from_cylinder(
                                  cast_to_gp(Axes), R, H, Angle))}};
}

topo_solid_t topo_solid_make_solid_from_cone(double R1, double R2, double H) {
  return topo_solid_t{
      .shp = new topo_shape_t{
          .shp = std::make_shared<flywave::topo::solid>(
              flywave::topo::solid::make_solid_from_cone(R1, R2, H))}};
}

topo_solid_t topo_solid_make_solid_from_cone_angle(double R1, double R2,
                                                   double H, double angle) {
  return topo_solid_t{
      .shp = new topo_shape_t{
          .shp = std::make_shared<flywave::topo::solid>(
              flywave::topo::solid::make_solid_from_cone(R1, R2, H, angle))}};
}

topo_solid_t topo_solid_make_solid_from_cone_axis2(axis2_t Axes, double R1,
                                                   double R2, double H) {
  return topo_solid_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::solid>(
                                  flywave::topo::solid::make_solid_from_cone(
                                      cast_to_gp(Axes), R1, R2, H))}};
}

topo_solid_t topo_solid_make_solid_from_cone_axis2_angle(axis2_t Axes,
                                                         double R1, double R2,
                                                         double H,
                                                         double angle) {
  return topo_solid_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::solid>(
                                  flywave::topo::solid::make_solid_from_cone(
                                      cast_to_gp(Axes), R1, R2, H, angle))}};
}

topo_solid_t topo_solid_make_solid_from_revolution(geom_curve_t *Meridian) {
  return topo_solid_t{.shp = new topo_shape_t{
                          .shp = std::make_shared<flywave::topo::solid>(
                              flywave::topo::solid::make_solid_from_revolution(
                                  Meridian->handle))}};
}

topo_solid_t topo_solid_make_solid_from_revolution_angle(geom_curve_t *Meridian,
                                                         double angle) {
  return topo_solid_t{.shp = new topo_shape_t{
                          .shp = std::make_shared<flywave::topo::solid>(
                              flywave::topo::solid::make_solid_from_revolution(
                                  Meridian->handle, angle))}};
}

topo_solid_t topo_solid_make_solid_from_revolution_limit(geom_curve_t *Meridian,
                                                         double VMin,
                                                         double VMax) {
  return topo_solid_t{.shp = new topo_shape_t{
                          .shp = std::make_shared<flywave::topo::solid>(
                              flywave::topo::solid::make_solid_from_revolution(
                                  Meridian->handle, VMin, VMax))}};
}

topo_solid_t topo_solid_make_solid_from_revolution_limit_angle(
    geom_curve_t *Meridian, double VMin, double VMax, double angle) {
  return topo_solid_t{.shp = new topo_shape_t{
                          .shp = std::make_shared<flywave::topo::solid>(
                              flywave::topo::solid::make_solid_from_revolution(
                                  Meridian->handle, VMin, VMax, angle))}};
}

topo_solid_t
topo_solid_make_solid_from_revolution_axis2(axis2_t Axes,
                                            geom_curve_t *Meridian) {
  return topo_solid_t{.shp = new topo_shape_t{
                          .shp = std::make_shared<flywave::topo::solid>(
                              flywave::topo::solid::make_solid_from_revolution(
                                  cast_to_gp(Axes), Meridian->handle))}};
}

topo_solid_t topo_solid_make_solid_from_revolution_axis2_angle(
    axis2_t Axes, geom_curve_t *Meridian, double angle) {
  return topo_solid_t{.shp = new topo_shape_t{
                          .shp = std::make_shared<flywave::topo::solid>(
                              flywave::topo::solid::make_solid_from_revolution(
                                  cast_to_gp(Axes), Meridian->handle, angle))}};
}

topo_solid_t topo_solid_make_solid_from_revolution_axis2_limit(
    axis2_t Axes, geom_curve_t *Meridian, double VMin, double VMax) {
  return topo_solid_t{
      .shp = new topo_shape_t{
          .shp = std::make_shared<flywave::topo::solid>(
              flywave::topo::solid::make_solid_from_revolution(
                  cast_to_gp(Axes), Meridian->handle, VMin, VMax))}};
}

topo_solid_t topo_solid_make_solid_from_revolution_axis2_limit_angle(
    axis2_t Axes, geom_curve_t *Meridian, double VMin, double VMax,
    double angle) {
  return topo_solid_t{
      .shp = new topo_shape_t{
          .shp = std::make_shared<flywave::topo::solid>(
              flywave::topo::solid::make_solid_from_revolution(
                  cast_to_gp(Axes), Meridian->handle, VMin, VMax, angle))}};
}

topo_solid_t topo_solid_make_solid_from_sphere(double R) {
  return topo_solid_t{
      .shp = new topo_shape_t{
          .shp = std::make_shared<flywave::topo::solid>(
              flywave::topo::solid::make_solid_from_sphere(R))}};
}

topo_solid_t topo_solid_make_solid_from_sphere_angle(double R, double angle) {
  return topo_solid_t{
      .shp = new topo_shape_t{
          .shp = std::make_shared<flywave::topo::solid>(
              flywave::topo::solid::make_solid_from_sphere(R, angle))}};
}

topo_solid_t topo_solid_make_solid_from_sphere_two_angle(double R,
                                                         double angle1,
                                                         double angle2) {
  return topo_solid_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::solid>(
                                  flywave::topo::solid::make_solid_from_sphere(
                                      R, angle1, angle2))}};
}

topo_solid_t topo_solid_make_solid_from_sphere_three_angle(double R,
                                                           double angle1,
                                                           double angle2,
                                                           double angle3) {
  return topo_solid_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::solid>(
                                  flywave::topo::solid::make_solid_from_sphere(
                                      R, angle1, angle2, angle3))}};
}

topo_solid_t topo_solid_make_solid_from_sphere_center_raduis(pnt3d_t Center,
                                                             double R) {
  return topo_solid_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::solid>(
                                  flywave::topo::solid::make_solid_from_sphere(
                                      cast_to_gp(Center), R))}};
}

topo_solid_t topo_solid_make_solid_from_sphere_center_angle(pnt3d_t Center,
                                                            double R,
                                                            double angle) {
  return topo_solid_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::solid>(
                                  flywave::topo::solid::make_solid_from_sphere(
                                      cast_to_gp(Center), R, angle))}};
}

topo_solid_t topo_solid_make_solid_from_sphere_center_two_angle(pnt3d_t Center,
                                                                double R,
                                                                double angle1,
                                                                double angle2) {
  return topo_solid_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::solid>(
                                  flywave::topo::solid::make_solid_from_sphere(
                                      cast_to_gp(Center), R, angle1, angle2))}};
}

topo_solid_t topo_solid_make_solid_from_sphere_center_three_angle(
    pnt3d_t Center, double R, double angle1, double angle2, double angle3) {
  return topo_solid_t{
      .shp = new topo_shape_t{
          .shp = std::make_shared<flywave::topo::solid>(
              flywave::topo::solid::make_solid_from_sphere(
                  cast_to_gp(Center), R, angle1, angle2, angle3))}};
}

topo_solid_t topo_solid_make_solid_from_sphere_axis2(axis2_t Axis, double R) {
  return topo_solid_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::solid>(
                                  flywave::topo::solid::make_solid_from_sphere(
                                      cast_to_gp(Axis), R))}};
}

topo_solid_t topo_solid_make_solid_from_sphere_axis2_angle(axis2_t Axis,
                                                           double R,
                                                           double angle) {
  return topo_solid_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::solid>(
                                  flywave::topo::solid::make_solid_from_sphere(
                                      cast_to_gp(Axis), R, angle))}};
}

topo_solid_t topo_solid_make_solid_from_sphere_axis2_two_angle(axis2_t Axis,
                                                               double R,
                                                               double angle1,
                                                               double angle2) {
  return topo_solid_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::solid>(
                                  flywave::topo::solid::make_solid_from_sphere(
                                      cast_to_gp(Axis), R, angle1, angle2))}};
}

topo_solid_t topo_solid_make_solid_from_sphere_axis2_three_angle(
    axis2_t Axis, double R, double angle1, double angle2, double angle3) {
  return topo_solid_t{
      .shp = new topo_shape_t{
          .shp = std::make_shared<flywave::topo::solid>(
              flywave::topo::solid::make_solid_from_sphere(
                  cast_to_gp(Axis), R, angle1, angle2, angle3))}};
}

topo_solid_t topo_solid_make_solid_from_torus(double R1, double R2) {
  return topo_solid_t{
      .shp = new topo_shape_t{
          .shp = std::make_shared<flywave::topo::solid>(
              flywave::topo::solid::make_solid_from_torus(R1, R2))}};
}

topo_solid_t topo_solid_make_solid_from_torus_angle(double R1, double R2,
                                                    double angle) {
  return topo_solid_t{
      .shp = new topo_shape_t{
          .shp = std::make_shared<flywave::topo::solid>(
              flywave::topo::solid::make_solid_from_torus(R1, R2, angle))}};
}

topo_solid_t topo_solid_make_solid_from_torus_two_angle(double R1, double R2,
                                                        double angle1,
                                                        double angle2) {
  return topo_solid_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::solid>(
                                  flywave::topo::solid::make_solid_from_torus(
                                      R1, R2, angle1, angle2))}};
}

topo_solid_t topo_solid_make_solid_from_torus_three_angle(double R1, double R2,
                                                          double angle1,
                                                          double angle2,
                                                          double angle) {
  return topo_solid_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::solid>(
                                  flywave::topo::solid::make_solid_from_torus(
                                      R1, R2, angle1, angle2, angle))}};
}

topo_solid_t topo_solid_make_solid_from_torus_axis2(axis2_t Axes, double R1,
                                                    double R2) {
  return topo_solid_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::solid>(
                                  flywave::topo::solid::make_solid_from_torus(
                                      cast_to_gp(Axes), R1, R2))}};
}

topo_solid_t topo_solid_make_solid_from_torus_axis2_angle(axis2_t Axes,
                                                          double R1, double R2,
                                                          double angle) {
  return topo_solid_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::solid>(
                                  flywave::topo::solid::make_solid_from_torus(
                                      cast_to_gp(Axes), R1, R2, angle))}};
}

topo_solid_t topo_solid_make_solid_from_torus_axis2_two_angle(
    axis2_t Axes, double R1, double R2, double angle1, double angle2) {
  return topo_solid_t{.shp = new topo_shape_t{
                          .shp = std::make_shared<flywave::topo::solid>(
                              flywave::topo::solid::make_solid_from_torus(
                                  cast_to_gp(Axes), R1, R2, angle1, angle2))}};
}

topo_solid_t topo_solid_make_solid_from_torus_axis2_three_angle(
    axis2_t Axes, double R1, double R2, double angle1, double angle2,
    double angle) {
  return topo_solid_t{
      .shp = new topo_shape_t{
          .shp = std::make_shared<flywave::topo::solid>(
              flywave::topo::solid::make_solid_from_torus(
                  cast_to_gp(Axes), R1, R2, angle1, angle2, angle))}};
}

topo_solid_t topo_solid_make_solid_from_wedge(double dx, double dy, double dz,
                                              double ltx) {
  return topo_solid_t{
      .shp = new topo_shape_t{
          .shp = std::make_shared<flywave::topo::solid>(
              flywave::topo::solid::make_solid_from_wedge(dx, dy, dz, ltx))}};
}

topo_solid_t topo_solid_make_solid_from_wedge_axis2(axis2_t Axes, double dx,
                                                    double dy, double dz,
                                                    double ltx) {
  return topo_solid_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::solid>(
                                  flywave::topo::solid::make_solid_from_wedge(
                                      cast_to_gp(Axes), dx, dy, dz, ltx))}};
}

topo_solid_t topo_solid_make_solid_from_wedge_limit(double dx, double dy,
                                                    double dz, double xmin,
                                                    double zmin, double xmax,
                                                    double zmax) {
  return topo_solid_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::solid>(
                                  flywave::topo::solid::make_solid_from_wedge(
                                      dx, dy, dz, xmin, zmin, xmax, zmax))}};
}

topo_solid_t topo_solid_make_solid_from_wedge_axis2_limit(
    axis2_t Axes, double dx, double dy, double dz, double xmin, double zmin,
    double xmax, double zmax) {
  return topo_solid_t{
      .shp = new topo_shape_t{
          .shp = std::make_shared<flywave::topo::solid>(
              flywave::topo::solid::make_solid_from_wedge(
                  cast_to_gp(Axes), dx, dy, dz, xmin, zmin, xmax, zmax))}};
}

topo_solid_t topo_solid_make_solid_from_loft(topo_wire_t *wires, int count,
                                             _Bool ruled) {
  try {
    std::vector<flywave::topo::wire> wireVec;
    for (int i = 0; i < count; i++) {
      wireVec.emplace_back(*cast_to_topo(wires[i]));
    }
    auto solid = flywave::topo::solid::make_solid_from_loft(wireVec, ruled);
    return topo_solid_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::solid>(solid)}};
  } catch (...) {
    return topo_solid_t{nullptr};
  }
}

int topo_solid_extrude_with_rotation_from_wire(
    topo_solid_t s, topo_wire_t outerWire, topo_wire_t *innerWires,
    int innerCount, pnt3d_t vecCenter, vec3d_t vecNormal, double angleDegrees) {
  try {
    std::vector<flywave::topo::wire> innerWireVec;
    for (int i = 0; i < innerCount; i++) {
      innerWireVec.emplace_back(*cast_to_topo(innerWires[i]));
    }

    gp_Pnt center(vecCenter.x, vecCenter.y, vecCenter.z);
    gp_Vec normal(vecNormal.x, vecNormal.y, vecNormal.z);

    return cast_to_topo(s)->extrude_with_rotation(
        *cast_to_topo(outerWire), innerWireVec, center, normal, angleDegrees);
  } catch (...) {
    return -1;
  }
}

int topo_solid_sweep_multi_from_vector(topo_solid_t s, topo_shape_t **profiles,
                                       int count, topo_shape_t *path,
                                       _Bool makeSolid, _Bool isFrenet,
                                       topo_vector_t *vec) {
  try {
    std::vector<boost::variant<flywave::topo::wire, flywave::topo::face>>
        profileVec;
    for (int i = 0; i < count; i++) {
      if (profiles[i]->shp->shape_type() == TopAbs_WIRE) {
        profileVec.emplace_back(*profiles[i]->shp->cast<flywave::topo::wire>());
      } else if (profiles[i]->shp->shape_type() == TopAbs_FACE) {
        profileVec.emplace_back(*profiles[i]->shp->cast<flywave::topo::face>());
      }
    }

    boost::optional<flywave::topo::solid::SweepMode> mode = boost::none;
    if (vec) {
      mode = vec->vec.to_vec();
    }

    return cast_to_topo(s)->sweep_multi(profileVec, *path->shp, makeSolid,
                                        isFrenet, mode);
  } catch (...) {
    return -1;
  }
}

int topo_solid_sweep_multi_from_wire(topo_solid_t s, topo_shape_t **profiles,
                                     int count, topo_shape_t *path,
                                     _Bool makeSolid, _Bool isFrenet,
                                     topo_wire_t *wire) {
  try {
    std::vector<boost::variant<flywave::topo::wire, flywave::topo::face>>
        profileVec;
    for (int i = 0; i < count; i++) {
      if (profiles[i]->shp->shape_type() == TopAbs_WIRE) {
        profileVec.emplace_back(*profiles[i]->shp->cast<flywave::topo::wire>());
      } else if (profiles[i]->shp->shape_type() == TopAbs_FACE) {
        profileVec.emplace_back(*profiles[i]->shp->cast<flywave::topo::face>());
      }
    }

    boost::optional<flywave::topo::solid::SweepMode> mode = boost::none;
    if (wire) {
      mode = cast_to_topo(*wire)->value();
    }

    return cast_to_topo(s)->sweep_multi(profileVec, *path->shp, makeSolid,
                                        isFrenet, mode);
  } catch (...) {
    return -1;
  }
}

int topo_solid_sweep_multi_from_edge(topo_solid_t s, topo_shape_t **profiles,
                                     int count, topo_shape_t *path,
                                     _Bool makeSolid, _Bool isFrenet,
                                     topo_edge_t *edge) {
  try {
    std::vector<boost::variant<flywave::topo::wire, flywave::topo::face>>
        profileVec;
    for (int i = 0; i < count; i++) {
      if (profiles[i]->shp->shape_type() == TopAbs_WIRE) {
        profileVec.emplace_back(*profiles[i]->shp->cast<flywave::topo::wire>());
      } else if (profiles[i]->shp->shape_type() == TopAbs_FACE) {
        profileVec.emplace_back(*profiles[i]->shp->cast<flywave::topo::face>());
      }
    }

    boost::optional<flywave::topo::solid::SweepMode> mode = boost::none;
    if (edge) {
      mode = cast_to_topo(*edge)->value();
    }

    return cast_to_topo(s)->sweep_multi(profileVec, *path->shp, makeSolid,
                                        isFrenet, mode);
  } catch (...) {
    return -1;
  }
}

int topo_solid_split(topo_solid_t s, topo_shape_t **splitters, int count) {
  try {
    std::vector<flywave::topo::shape> splitterVec;
    for (int i = 0; i < count; i++) {
      splitterVec.emplace_back(*splitters[i]->shp);
    }
    return cast_to_topo(s)->split(splitterVec);
  } catch (...) {
    return -1;
  }
}

topo_wire_t topo_solid_section_wire(topo_solid_t s, pnt3d_t pnt, pnt3d_t nor) {
  try {
    gp_Pnt point(pnt.x, pnt.y, pnt.z);
    gp_Pnt normal(nor.x, nor.y, nor.z);

    auto section = cast_to_topo(s)->section(point, normal);
    if (section) {
      return topo_wire_t{
          .shp = new topo_shape_t{
              .shp = std::make_shared<flywave::topo::wire>(*section)}};
    }
    return topo_wire_t{nullptr};
  } catch (...) {
    return topo_wire_t{nullptr};
  }
}

_Bool topo_solid_is_inside(topo_solid_t s, pnt3d_t p, double tol) {
  try {
    gp_Pnt point(p.x, p.y, p.z);
    return cast_to_topo(s)->is_inside(point, tol);
  } catch (...) {
    return false;
  }
}

int topo_solid_num_solids(topo_solid_t s) {
  auto opt = cast_to_topo(s);
  if (opt) {
    return opt->num_solids();
  }
  return -1;
}

int topo_solid_num_faces(topo_solid_t s) {
  auto opt = cast_to_topo(s);
  if (opt) {
    return opt->num_faces();
  }
  return -1;
}

double topo_solid_area(topo_solid_t s) {
  auto opt = cast_to_topo(s);
  if (opt) {
    return opt->area();
  }
  return 0.0;
}

double topo_solid_volume(topo_solid_t s) {
  auto opt = cast_to_topo(s);
  if (opt) {
    return opt->volume();
  }
  return 0.0;
}

bbox_t topo_solid_inertia(topo_solid_t s) {
  auto opt = cast_to_topo(s);
  if (opt) {
    return cast_from_gp(opt->inertia());
  }
  return bbox_t{0, 0, 0, 0, 0, 0};
}

pnt3d_t topo_solid_centre_of_mass(topo_solid_t s) {
  auto opt = cast_to_topo(s);
  if (opt) {
    return cast_from_gp(opt->centre_of_mass());
  }
  return pnt3d_t{0, 0, 0};
}

int topo_solid_extrude_with_rotation(topo_solid_t s, topo_wire_t outerWire,
                                     topo_wire_t *innerWires, int innerCount,
                                     pnt3d_t vecCenter, vec3d_t vecNormal,
                                     double angleDegrees) {
  try {
    std::vector<flywave::topo::wire> innerWireVec;
    for (int i = 0; i < innerCount; i++) {
      innerWireVec.emplace_back(*cast_to_topo(innerWires[i]));
    }
    gp_Pnt center(vecCenter.x, vecCenter.y, vecCenter.z);
    gp_Vec normal(vecNormal.x, vecNormal.y, vecNormal.z);
    return cast_to_topo(s)->extrude_with_rotation(
        *cast_to_topo(outerWire), innerWireVec, center, normal, angleDegrees);
  } catch (...) {
    return -1;
  }
}

int topo_solid_extrude_with_rotation_from_face(topo_solid_t s, topo_face_t face,
                                               pnt3d_t vecCenter,
                                               vec3d_t vecNormal,
                                               double angleDegrees) {
  auto opt = cast_to_topo(s);
  if (opt) {
    return opt->extrude_with_rotation(*cast_to_topo(face),
                                      cast_to_gp(vecCenter),
                                      cast_to_gp(vecNormal), angleDegrees);
  }
  return -1;
}

int topo_solid_extrude(topo_solid_t s, topo_face_t f, pnt3d_t p1, pnt3d_t p2) {
  auto opt = cast_to_topo(s);
  if (opt) {
    return opt->extrude(*cast_to_topo(f), cast_to_gp(p1), cast_to_gp(p2));
  }
  return -1;
}

int topo_solid_extrude_from_dir(topo_solid_t s, topo_face_t f, vec3d_t dir) {
  auto opt = cast_to_topo(s);
  if (opt) {
    return opt->extrude(*cast_to_topo(f), cast_to_gp(dir));
  }
  return -1;
}

int topo_solid_revolve(topo_solid_t s, topo_face_t f, pnt3d_t p1, pnt3d_t p2,
                       double angle) {
  auto opt = cast_to_topo(s);
  if (opt) {
    return opt->revolve(*cast_to_topo(f), cast_to_gp(p1), cast_to_gp(p2),
                        angle);
  }
  return -1;
}

int topo_solid_loft(topo_solid_t s, topo_shape_t **profiles, int count,
                    _Bool ruled, double tolerance) {
  auto opt = cast_to_topo(s);
  if (opt) {
    std::vector<flywave::topo::shape> prs;
    for (int i = 0; i < count; i++) {
      prs.emplace_back(*profiles[i]->shp);
    }
    return opt->loft(prs, ruled, tolerance);
  }
  return -1;
}

int topo_solid_pipe(topo_solid_t s, topo_face_t f, topo_wire_t w) {
  auto opt = cast_to_topo(s);
  if (opt) {
    return opt->pipe(*cast_to_topo(f), *cast_to_topo(w));
  }
  return -1;
}

// 实现函数
TOPOCAPICALL int topo_solid_sweep_compound(topo_solid_t s, topo_wire_t spine,
                                           topo_sweep_profile_t *profiles,
                                           int profile_count, int corner_mode) {
  try {

    std::vector<flywave::topo::solid::sweep_profile> cpp_profiles;
    for (int i = 0; i < profile_count; i++) {
      flywave::topo::solid::sweep_profile profile;
      profile.profile = *profiles[i].profile->shp;
      if (profiles[i].index >= 0) {
        profile.index = profiles[i].index;
      } else {
        profile.index = -1;
      }
      cpp_profiles.push_back(profile);
    }

    auto result = reinterpret_cast<flywave::topo::solid *>(s.shp)->sweep(
        *cast_to_topo(spine), cpp_profiles, corner_mode);

    return result;
  } catch (...) {
    return -1; // 异常处理
  }
}

int topo_solid_sweep(topo_solid_t s, topo_wire_t spine, topo_shape_t **profiles,
                     int count, int cornerMode) {
  try {
    auto opt = cast_to_topo(s);
    if (opt) {
      std::vector<flywave::topo::shape> prs;
      for (int i = 0; i < count; i++) {
        prs.emplace_back(*(profiles[i]->shp.get()));
      }
      return opt->sweep(*cast_to_topo(spine), prs, cornerMode);
    }
  } catch (...) {
    return -1;
  }
  return -1;
}

int topo_solid_sweep_wire(topo_solid_t s, topo_wire_t spine,
                          topo_wire_t *profiles, int count, int cornerMode) {
  try {
    auto opt = cast_to_topo(s);
    if (opt) {
      std::vector<flywave::topo::shape> prs;
      for (int i = 0; i < count; i++) {
        prs.emplace_back(*profiles[i].shp->shp.get());
      }
      return opt->sweep(*cast_to_topo(spine), prs, cornerMode);
    }
  } catch (...) {
    return -1;
  }
  return -1;
}

int topo_solid_boolean(topo_solid_t s, topo_solid_t tool, int op) {
  auto opt = cast_to_topo(s);
  if (opt) {
    try {
      return opt->boolean(*cast_to_topo(tool),
                          static_cast<flywave::topo::bool_op_type>(op));
    } catch (...) {
      return -1;
    }
  }
  return -1;
}

int topo_solid_fillet(topo_solid_t s, topo_edge_t *edges, int count,
                      double *radius, int rcount) {
  auto opt = cast_to_topo(s);
  if (opt) {
    std::vector<flywave::topo::edge> es;
    for (int i = 0; i < count; i++) {
      es.emplace_back(*cast_to_topo(edges[i]));
    }
    std::vector<double> ras;
    for (int i = 0; i < rcount; i++) {
      ras.emplace_back(radius[i]);
    }
    return opt->fillet(es, ras);
  }
  return -1;
}

int topo_solid_chamfer(topo_solid_t s, topo_edge_t *edges, int count,
                       double *distances, int dcount) {
  auto opt = cast_to_topo(s);
  if (opt) {
    std::vector<flywave::topo::edge> es;
    for (int i = 0; i < count; i++) {
      es.emplace_back(*cast_to_topo(edges[i]));
    }
    std::vector<double> ras;
    for (int i = 0; i < dcount; i++) {
      ras.emplace_back(distances[i]);
    }
    return opt->chamfer(es, ras);
  }
  return -1;
}

int topo_solid_shelling(topo_solid_t s, topo_face_t *faces, int count,
                        double offset, double tolerance) {
  auto opt = cast_to_topo(s);
  if (opt) {
    std::vector<flywave::topo::face> es;
    for (int i = 0; i < count; i++) {
      es.emplace_back(*cast_to_topo(faces[i]));
    }
    return opt->shelling(es, offset, tolerance);
  }
  return -1;
}

int topo_solid_offset(topo_solid_t s, topo_face_t f, double offset,
                      double tolerance) {
  auto opt = cast_to_topo(s);
  if (opt) {
    return opt->offset(*cast_to_topo(f), offset, tolerance);
  }
  return -1;
}

int topo_solid_draft(topo_solid_t s, topo_face_t *faces, int count, dir3d_t d,
                     double angle, plane_t p) {
  auto opt = cast_to_topo(s);
  if (opt) {
    std::vector<flywave::topo::face> es;
    for (int i = 0; i < count; i++) {
      es.emplace_back(*cast_to_topo(faces[i]));
    }
    return opt->draft(es, cast_to_gp(d), angle, cast_to_gp(p));
  }
  return -1;
}

int topo_solid_evolved_from_face(topo_solid_t s, topo_face_t Spine,
                                 topo_wire_t Profil) {
  auto opt = cast_to_topo(s);
  if (opt) {
    return opt->evolved(*cast_to_topo(Spine), *cast_to_topo(Profil));
  }
  return -1;
}

int topo_solid_evolved_from_wire(topo_solid_t s, topo_wire_t Spine,
                                 topo_wire_t Profil) {
  auto opt = cast_to_topo(s);
  if (opt) {
    return opt->evolved(*cast_to_topo(Spine), *cast_to_topo(Profil));
  }
  return -1;
}

int topo_solid_feat_prism(topo_solid_t s, topo_face_t f, dir3d_t d,
                          double height, _Bool fuse) {
  auto opt = cast_to_topo(s);
  if (opt) {
    return opt->feat_prism(*cast_to_topo(f), cast_to_gp(d), height, fuse);
  }
  return -1;
}

int topo_solid_feat_prism_for_range(topo_solid_t s, topo_face_t f, dir3d_t d,
                                    topo_face_t from, topo_face_t end,
                                    _Bool fuse) {
  auto opt = cast_to_topo(s);
  if (opt) {
    return opt->feat_prism(*cast_to_topo(f), cast_to_gp(d), *cast_to_topo(from),
                           *cast_to_topo(end), fuse);
  }
  return -1;
}

int topo_solid_feat_prism_for_until(topo_solid_t s, topo_face_t f, dir3d_t d,
                                    topo_face_t until, _Bool fuse) {
  auto opt = cast_to_topo(s);
  if (opt) {
    return opt->feat_prism(*cast_to_topo(f), cast_to_gp(d),
                           *cast_to_topo(until), fuse);
  }
  return -1;
}

int topo_solid_feat_draft_prism(topo_solid_t s, topo_face_t f, double angle,
                                double height, _Bool fuse) {
  auto opt = cast_to_topo(s);
  if (opt) {
    return opt->feat_draft_prism(*cast_to_topo(f), angle, height, fuse);
  }
  return -1;
}

int topo_solid_feat_draft_prism_for_range(topo_solid_t s, topo_face_t f,
                                          double angle, topo_face_t from,
                                          topo_face_t end, _Bool fuse) {
  auto opt = cast_to_topo(s);
  if (opt) {
    return opt->feat_draft_prism(*cast_to_topo(f), angle, *cast_to_topo(from),
                                 *cast_to_topo(end), fuse);
  }
  return -1;
}

int topo_solid_feat_draft_prism_for_until(topo_solid_t s, topo_face_t f,
                                          double angle, topo_face_t until,
                                          _Bool fuse) {
  auto opt = cast_to_topo(s);
  if (opt) {
    return opt->feat_draft_prism(*cast_to_topo(f), angle, *cast_to_topo(until),
                                 fuse);
  }
  return -1;
}

int topo_solid_feat_revol_for_range(topo_solid_t s, topo_face_t f, axis1_t Axes,
                                    topo_face_t from, topo_face_t end,
                                    _Bool fuse) {
  auto opt = cast_to_topo(s);
  if (opt) {
    return opt->feat_revol(*cast_to_topo(f), cast_to_gp(Axes),
                           *cast_to_topo(from), *cast_to_topo(end), fuse);
  }
  return -1;
}

int topo_solid_feat_revol_for_until(topo_solid_t s, topo_face_t f, axis1_t Axes,
                                    topo_face_t until, _Bool fuse) {
  auto opt = cast_to_topo(s);
  if (opt) {
    return opt->feat_revol(*cast_to_topo(f), cast_to_gp(Axes),
                           *cast_to_topo(until), fuse);
  }
  return -1;
}

int topo_solid_feat_pipe_for_range(topo_solid_t s, topo_face_t f,
                                   topo_wire_t Spine, topo_face_t from,
                                   topo_face_t end, _Bool fuse) {
  auto opt = cast_to_topo(s);
  if (opt) {
    return opt->feat_pipe(*cast_to_topo(f), *cast_to_topo(Spine),
                          *cast_to_topo(from), *cast_to_topo(end), fuse);
  }
  return -1;
}

int topo_solid_feat_pipe_for_until(topo_solid_t s, topo_face_t f,
                                   topo_wire_t Spine, topo_face_t until,
                                   _Bool fuse) {
  auto opt = cast_to_topo(s);
  if (opt) {
    return opt->feat_pipe(*cast_to_topo(f), *cast_to_topo(Spine),
                          *cast_to_topo(until), fuse);
  }
  return -1;
}

int topo_solid_linear_form(topo_solid_t s, topo_wire_t w,
                           geom_plane_surface_t *p, dir3d_t d, dir3d_t d1,
                           _Bool fuse) {
  auto opt = cast_to_topo(s);
  if (opt) {
    return opt->linear_form(*cast_to_topo(w), p->handle, cast_to_gp(d),
                            cast_to_gp(d1), fuse);
  }
  return -1;
}

int topo_solid_revolution_form(topo_solid_t s, topo_wire_t w,
                               geom_plane_surface_t *p, axis1_t Axes, double h1,
                               double h2, _Bool fuse) {
  auto opt = cast_to_topo(s);
  if (opt) {
    return opt->revolution_form(*cast_to_topo(w), p->handle, cast_to_gp(Axes),
                                h1, h2, fuse);
  }
  return -1;
}

topo_face_t topo_solid_section_face(topo_solid_t s, pnt3d_t pnt, pnt3d_t nor) {
  auto opt = cast_to_topo(s);
  if (opt) {
    auto fopt = opt->section(cast_to_gp(pnt), cast_to_gp(nor));
    if (fopt) {
      return topo_face_t{
          .shp = new topo_shape_t{
              .shp = std::make_shared<flywave::topo::shape>(fopt->value())}};
    }
  }
  return topo_face_t{nullptr};
}

int topo_solid_convert_to_nurbs(topo_solid_t s) {
  auto opt = cast_to_topo(s);
  if (opt) {
    return opt->convert_to_nurbs();
  }
  return -1;
}

topo_shell_t topo_solid_outer_shell(topo_solid_t s) {
  try {
    auto opt = cast_to_topo(s);
    if (opt) {
      auto shell = opt->outer_shell();
      return topo_shell_t{
          .shp = new topo_shape_t{
              .shp = std::make_shared<flywave::topo::shape>(shell)}};
    }
  } catch (...) {
    return topo_shell_t{nullptr};
  }
  return topo_shell_t{nullptr};
}

topo_shell_t *topo_solid_inner_shells(topo_solid_t s, int *count) {
  try {
    auto opt = cast_to_topo(s);
    if (opt) {
      auto shells = opt->inner_shells();
      *count = static_cast<int>(shells.size());
      auto result = new topo_shell_t[*count];
      for (int i = 0; i < *count; i++) {
        result[i].shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::shape>(shells[i])};
      }
      return result;
    }
  } catch (...) {
    return nullptr;
  }
  return nullptr;
}

topo_compound_t topo_make_compound() {
  return topo_compound_t{
      .shp =
          new topo_shape_t{.shp = std::make_shared<flywave::topo::compound>()}};
}

topo_compound_t topo_make_text(const char *text, double size, const char *font,
                               const char *fontPath, int kind, int halign,
                               int valign, topo_plane_t *position) {
  try {
    auto cpp_plane =
        position ? position->plane : flywave::topo::topo_plane::named("XY");
    auto result = flywave::topo::compound::make_text(
        text, size, font ? font : "Arial", fontPath ? fontPath : "",
        static_cast<flywave::topo::font_kind>(kind),
        static_cast<flywave::topo::horizontal_align>(halign),
        static_cast<flywave::topo::vertical_align>(valign), cpp_plane);
    return topo_compound_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::compound>(result)}};
  } catch (...) {
    return topo_compound_t{};
  }
}

topo_compound_t topo_make_text_with_spine(const char *text, double size,
                                          topo_wire_t *spine, bool planar,
                                          const char *font, const char *path,
                                          int kind, int halign, int valign) {
  try {
    auto result = flywave::topo::compound::make_text(
        text, size, *cast_to_topo(*spine), planar, font ? font : "Arial",
        path ? path : "", static_cast<flywave::topo::font_kind>(kind),
        static_cast<flywave::topo::horizontal_align>(halign),
        static_cast<flywave::topo::vertical_align>(valign));
    return topo_compound_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::compound>(result)}};
  } catch (...) {
    return topo_compound_t{};
  }
}

topo_compound_t topo_make_text_with_spine_and_base(
    const char *text, double size, topo_wire_t *spine, topo_face_t *base,
    const char *font, const char *path, int kind, int halign, int valign) {
  try {
    auto result = flywave::topo::compound::make_text(
        text, size, *cast_to_topo(*spine), *cast_to_topo(*base),
        font ? font : "Arial", path ? path : "",
        static_cast<flywave::topo::font_kind>(kind),
        static_cast<flywave::topo::horizontal_align>(halign),
        static_cast<flywave::topo::vertical_align>(valign));
    return topo_compound_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::compound>(result)}};
  } catch (...) {
    return topo_compound_t{};
  }
}

topo_compound_t topo_make_text_with_height(const char *text, double size,
                                           double height, const char *font,
                                           const char *fontPath, int kind,
                                           int halign, int valign,
                                           topo_plane_t *position) {
  try {
    auto cpp_plane =
        position ? position->plane : flywave::topo::topo_plane::named("XY");
    auto result = flywave::topo::compound::make_text(
        text, size, height, font ? font : "Arial", fontPath ? fontPath : "",
        static_cast<flywave::topo::font_kind>(kind),
        static_cast<flywave::topo::horizontal_align>(halign),
        static_cast<flywave::topo::vertical_align>(valign), cpp_plane);
    return topo_compound_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::compound>(result)}};
  } catch (...) {
    return topo_compound_t{};
  }
}

void topo_compound_free(topo_compound_t t) {
  if (t.shp) {
    delete t.shp;
  }
}

topo_compound_t topo_compound_make_compound(topo_shape_t **S, int count) {
  std::vector<flywave::topo::shape> sps;
  for (int i = 0; i < count; i++) {
    sps.emplace_back(*S[i]->shp);
  }
  return topo_compound_t{.shp = new topo_shape_t{
                             .shp = std::make_shared<flywave::topo::compound>(
                                 flywave::topo::compound::make_compound(sps))}};
}

void topo_compound_remove(topo_compound_t t, topo_shape_t *s) {
  auto opt = cast_to_topo(t);
  if (opt) {
    opt->remove(*s->shp);
  }
}

topo_compound_t topo_compound_cut(topo_compound_t t, topo_shape_t **toCut,
                                  int count, double tol) {
  std::vector<flywave::topo::shape> sps;
  for (int i = 0; i < count; i++) {
    sps.emplace_back(*toCut[i]->shp);
  }
  return topo_compound_t{.shp = new topo_shape_t{
                             .shp = std::make_shared<flywave::topo::compound>(
                                 flywave::topo::compound::make_compound(sps))}};
}

topo_compound_t topo_compound_fuse(topo_compound_t t, topo_shape_t **toFuse,
                                   int count, bool glue, double tol) {
  std::vector<flywave::topo::shape> sps;
  for (int i = 0; i < count; i++) {
    sps.emplace_back(*toFuse[i]->shp);
  }
  return topo_compound_t{.shp = new topo_shape_t{
                             .shp = std::make_shared<flywave::topo::compound>(
                                 flywave::topo::compound::make_compound(sps))}};
}

topo_compound_t topo_compound_intersect(topo_compound_t t,
                                        topo_shape_t **toIntersect, int count,
                                        double tol) {
  std::vector<flywave::topo::shape> sps;
  for (int i = 0; i < count; i++) {
    sps.emplace_back(*toIntersect[i]->shp);
  }
  return topo_compound_t{.shp = new topo_shape_t{
                             .shp = std::make_shared<flywave::topo::compound>(
                                 flywave::topo::compound::make_compound(sps))}};
}

topo_compound_t topo_compound_ancestors(topo_compound_t t, topo_shape_t *s,
                                        int kind) {
  auto opt = cast_to_topo(t);
  if (opt) {
    auto fopt = opt->ancestors(*s->shp, static_cast<TopAbs_ShapeEnum>(kind));
    if (fopt) {
      return topo_compound_t{
          .shp = new topo_shape_t{
              .shp = std::make_shared<flywave::topo::compound>(fopt)}};
    }
  }
  return topo_compound_t{nullptr};
}

topo_compound_t topo_compound_siblings(topo_compound_t t, topo_shape_t *shape,
                                       int kind, int level) {
  auto opt = cast_to_topo(t);
  if (opt) {
    auto fopt =
        opt->siblings(*shape->shp, static_cast<TopAbs_ShapeEnum>(kind), level);
    if (fopt) {
      return topo_compound_t{
          .shp = new topo_shape_t{
              .shp = std::make_shared<flywave::topo::compound>(fopt)}};
    }
  }
  return topo_compound_t{nullptr};
}

topo_comp_solid_t topo_make_comp_solid() {
  return topo_comp_solid_t{
      .shp = new topo_shape_t{
          .shp = std::make_shared<flywave::topo::comp_solid>()}};
}

void topo_comp_solid_free(topo_comp_solid_t t) {
  if (t.shp) {
    delete t.shp;
  }
}

topo_comp_solid_t topo_comp_solid_make_comp_solid(topo_solid_t *S, int count) {
  std::vector<flywave::topo::solid> sps;
  for (int i = 0; i < count; i++) {
    sps.emplace_back(*cast_to_topo(S[i]));
  }
  return topo_comp_solid_t{
      .shp = new topo_shape_t{
          .shp = std::make_shared<flywave::topo::comp_solid>(
              flywave::topo::comp_solid::make_comp_solid(sps))}};
}

class go_mesh_receiver : public flywave::topo::mesh_receiver {
public:
  go_mesh_receiver(mesh_receiver_cb_t cb) : _cb(cb) {}
  virtual ~go_mesh_receiver() {}

  void begin() override { _cb.begin(_cb.ctx); }

  void end() override { _cb.end(_cb.ctx); }

  int append_face(Quantity_Color color) override {
    return _cb.append_face(_cb.ctx, cast_from_gp(color));
  }

  void append_node(int face, gp_Pnt p, gp_Pnt n) override {
    return _cb.append_node_norm(_cb.ctx, face, cast_from_gp(p),
                                cast_from_gp(n));
  }

  void append_node(int face, gp_Pnt p, gp_Pnt n, gp_Pnt2d uv) override {
    return _cb.append_node_norm_uv(_cb.ctx, face, cast_from_gp(p),
                                   cast_from_gp(n), cast_from_gp(uv));
  }

  void append_node(int face, gp_Pnt p) override {
    return _cb.append_node(_cb.ctx, face, cast_from_gp(p));
  }

  void append_triangle(int face, int tri[3]) override {
    return _cb.append_triangle(_cb.ctx, face, tri[0], tri[1], tri[2]);
  }

protected:
  mesh_receiver_cb_t _cb;
};

extern void begin(void *ctx);
extern void end(void *ctx);
extern int appendFace(void *ctx, color_t color);
extern void appendNodeNorm(void *ctx, int face, pnt3d_t p, pnt3d_t n);
extern void appendNodeNormUv(void *ctx, int face, pnt3d_t p, pnt3d_t n,
                             pnt2d_t uv);
extern void appendNode(void *ctx, int face, pnt3d_t p);
extern void appendTriangle(void *ctx, int face, int a, int b, int c);

topo_mesh_receiver_t *topo_mesh_receiver_new(mesh_receiver_cb_t cb) {
  cb.begin = begin;
  cb.end = end;
  cb.append_face = appendFace;
  cb.append_node = appendNode;
  cb.append_node_norm = appendNodeNorm;
  cb.append_node_norm_uv = appendNodeNormUv;
  cb.append_triangle = appendTriangle;
  return new topo_mesh_receiver_t{
      .recv = std::unique_ptr<flywave::topo::mesh_receiver>(
          new go_mesh_receiver(cb))};
}

void topo_mesh_receiver_free(topo_mesh_receiver_t *p) {
  if (p) {
    delete p;
  }
}

topo_location_t *topo_location_new(trsf_t t) {
  return new topo_location_t{.loc =
                                 flywave::topo::topo_location{cast_to_gp(t)}};
}

void topo_location_free(topo_location_t *p) {
  if (p) {
    delete p;
  }
}

trsf_t topo_location_get_trsf(topo_location_t *p) {
  if (p) {
    return cast_from_gp(gp_Trsf(p->loc));
  }
  return trsf_t{};
}

void topo_location_list_free(topo_location_t **result, int result_count) {
  delete[] result;
}

void topo_shape_to_stl(topo_shape_t *p, char *str) {
  StlAPI_Writer writer = StlAPI_Writer();
  writer.Write(p->shp->value(), str);
}

topo_comp_solid_iterator_t *topo_comp_solid_iterator_make(topo_shape_t *shp) {
  return new topo_comp_solid_iterator_t{
      .iter = flywave::topo::comp_solid_iterator{*shp->shp}};
}

void topo_comp_solid_iterator_reset(topo_comp_solid_iterator_t *it) {
  it->iter.reset();
}

void topo_comp_solid_iterator_free(topo_comp_solid_iterator_t *it) {
  delete it;
}

topo_shape_t *topo_comp_solid_iterator_next(topo_comp_solid_iterator_t *it) {
  boost::optional<flywave::topo::comp_solid> opt = it->iter.next();
  if (opt) {
    return new topo_shape_t{
        .shp = std::make_shared<flywave::topo::comp_solid>(*opt)};
  }
  return nullptr;
}

topo_compound_iterator_t *topo_compound_iterator_make(topo_shape_t *shp) {
  return new topo_compound_iterator_t{
      .iter = flywave::topo::compound_iterator{*shp->shp}};
}

void topo_compound_iterator_reset(topo_compound_iterator_t *it) {
  it->iter.reset();
}

void topo_compound_iterator_free(topo_compound_iterator_t *it) { delete it; }

topo_shape_t *topo_compound_iterator_next(topo_compound_iterator_t *it) {
  boost::optional<flywave::topo::compound> opt = it->iter.next();
  if (opt) {
    return new topo_shape_t{
        .shp = std::make_shared<flywave::topo::compound>(*opt)};
  }
  return nullptr;
}

topo_edge_iterator_t *topo_edge_iterator_make(topo_shape_t *shp) {
  return new topo_edge_iterator_t{.iter =
                                      flywave::topo::edge_iterator{*shp->shp}};
}

void topo_edge_iterator_free(topo_edge_iterator_t *it) { delete it; }

void topo_edge_iterator_reset(topo_edge_iterator_t *it) { it->iter.reset(); }

topo_shape_t *topo_edge_iterator_next(topo_edge_iterator_t *it) {
  boost::optional<flywave::topo::edge> opt = it->iter.next();
  if (opt) {
    return new topo_shape_t{.shp = std::make_shared<flywave::topo::edge>(*opt)};
  }
  return nullptr;
}

topo_face_iterator_t *topo_face_iterator_make(topo_shape_t *shp) {
  return new topo_face_iterator_t{.iter =
                                      flywave::topo::face_iterator{*shp->shp}};
}

void topo_face_iterator_free(topo_face_iterator_t *it) { delete it; }

void topo_face_iterator_reset(topo_face_iterator_t *it) { it->iter.reset(); }

topo_shape_t *topo_face_iterator_next(topo_face_iterator_t *it) {
  boost::optional<flywave::topo::face> opt = it->iter.next();
  if (opt) {
    return new topo_shape_t{.shp = std::make_shared<flywave::topo::face>(*opt)};
  }
  return nullptr;
}

topo_shell_iterator_t *topo_shell_iterator_make(topo_shape_t *shp) {
  return new topo_shell_iterator_t{
      .iter = flywave::topo::shell_iterator{*shp->shp}};
}

void topo_shell_iterator_free(topo_shell_iterator_t *it) { delete it; }

void topo_shell_iterator_reset(topo_shell_iterator_t *it) { it->iter.reset(); }

topo_shape_t *topo_shell_iterator_next(topo_shell_iterator_t *it) {
  boost::optional<flywave::topo::shell> opt = it->iter.next();
  if (opt) {
    return new topo_shape_t{.shp =
                                std::make_shared<flywave::topo::shell>(*opt)};
  }
  return nullptr;
}

topo_solid_iterator_t *topo_solid_iterator_make(topo_shape_t *shp) {
  return new topo_solid_iterator_t{
      .iter = flywave::topo::solid_iterator{*shp->shp}};
}

void topo_solid_iterator_free(topo_solid_iterator_t *it) { delete it; }

void topo_solid_iterator_reset(topo_solid_iterator_t *it) { it->iter.reset(); }

topo_shape_t *topo_solid_iterator_next(topo_solid_iterator_t *it) {
  boost::optional<flywave::topo::solid> opt = it->iter.next();
  if (opt) {
    return new topo_shape_t{.shp =
                                std::make_shared<flywave::topo::solid>(*opt)};
  }
  return nullptr;
}

topo_vertex_iterator_t *topo_vertex_iterator_make(topo_shape_t *shp) {
  return new topo_vertex_iterator_t{
      .iter = flywave::topo::vertex_iterator{*shp->shp}};
}

void topo_vertex_iterator_free(topo_vertex_iterator_t *it) { delete it; }

void topo_vertex_iterator_reset(topo_vertex_iterator_t *it) {
  it->iter.reset();
}

topo_shape_t *topo_vertex_iterator_next(topo_vertex_iterator_t *it) {
  boost::optional<flywave::topo::vertex> opt = it->iter.next();
  if (opt) {
    return new topo_shape_t{.shp =
                                std::make_shared<flywave::topo::vertex>(*opt)};
  }
  return nullptr;
}

topo_wire_iterator_t *topo_wire_iterator_make(topo_shape_t *shp) {
  return new topo_wire_iterator_t{.iter =
                                      flywave::topo::wire_iterator{*shp->shp}};
}

void topo_wire_iterator_free(topo_wire_iterator_t *it) { delete it; }

void topo_wire_iterator_reset(topo_wire_iterator_t *it) { it->iter.reset(); }

topo_shape_t *topo_wire_iterator_next(topo_wire_iterator_t *it) {
  boost::optional<flywave::topo::wire> opt = it->iter.next();
  if (opt) {
    return new topo_shape_t{.shp = std::make_shared<flywave::topo::wire>(*opt)};
  }
  return nullptr;
}

topo_vector_t *topo_vector_new(double x, double y, double z) {
  return new topo_vector_t{.vec = flywave::topo::topo_vector(x, y, z)};
}

void topo_vector_free(topo_vector_t *p) {
  if (p) {
    delete p;
  }
}

double topo_vector_get_x(topo_vector_t *p) {
  if (p) {
    return p->vec.x();
  }
  return 0;
}

double topo_vector_get_y(topo_vector_t *p) {
  if (p) {
    return p->vec.y();
  }
  return 0;
}

double topo_vector_get_z(topo_vector_t *p) {
  if (p) {
    return p->vec.z();
  }
  return 0;
}

topo_plane_t *topo_plane_new(pnt3d_t *origin, dir3d_t *xDir, vec3d_t *normal) {
  return new topo_plane_t{.plane = flywave::topo::topo_plane(
                              flywave::topo::topo_vector(cast_to_gp(*origin)),
                              flywave::topo::topo_vector(cast_to_gp(*xDir)),
                              flywave::topo::topo_vector(cast_to_gp(*normal)))};
}

topo_plane_t *topo_plane_new_from_named(const char *name, pnt3d_t *origin) {
  return new topo_plane_t{
      .plane = flywave::topo::topo_plane::named(
          std::string(name), flywave::topo::topo_vector(cast_to_gp(*origin)))};
}

void topo_plane_free(topo_plane_t *p) {
  if (p) {
    delete p;
  }
}

pnt3d_t topo_plane_get_origin(topo_plane_t *p) {
  if (p) {
    return cast_from_gp(p->plane.origin().to_pnt());
  }
  return pnt3d_t{};
}

dir3d_t topo_plane_get_x_dir(topo_plane_t *p) {
  if (p) {
    return cast_from_gp(p->plane.x_dir().to_dir());
  }
  return dir3d_t{};
}

dir3d_t topo_plane_get_y_dir(topo_plane_t *p) {
  if (p) {
    return cast_from_gp(p->plane.y_dir().to_dir());
  }
  return dir3d_t{};
}

dir3d_t topo_plane_get_z_dir(topo_plane_t *p) {
  if (p) {
    return cast_from_gp(p->plane.z_dir().to_dir());
  }
  return dir3d_t{};
}

topo_bbox_t *topo_bbox_new(bbox_t bbox) {
  return new topo_bbox_t{
      .bbox = flywave::topo::topo_bbox(bbox.minx, bbox.miny, bbox.minz,
                                       bbox.maxx, bbox.maxy, bbox.maxz)};
}

topo_bbox_t *topo_bbox_new_from_shape(topo_shape_t *p) { return nullptr; }

void topo_bbox_free(topo_bbox_t *p) {
  if (p) {
    delete p;
  }
}

bbox_t topo_bbox_get_bbox(topo_bbox_t *p) {
  if (p) {
    bbox_t bbox{
        .minx = p->bbox.x_min(),
        .miny = p->bbox.y_min(),
        .minz = p->bbox.z_min(),
        .maxx = p->bbox.x_max(),
        .maxy = p->bbox.y_max(),
        .maxz = p->bbox.z_max(),
    };
    return bbox;
  }
  return bbox_t{};
}

topo_matrix_t *topo_matrix_new(trsf_t t) {
  return new topo_matrix_t{.mat = flywave::topo::topo_matrix(cast_to_gp(t))};
}

void topo_matrix_free(topo_matrix_t *p) {
  if (p) {
    delete p;
  }
}

double topo_matrix_get_value(topo_matrix_t *p, int row, int col) {
  if (p) {
    return p->mat.get(row, col);
  }
  return 0;
}

// Boolean operations
TOPOCAPICALL topo_shape_t *topo_fuse(topo_shape_t **shapes, int count,
                                     double tol, bool glue) {
  try {
    std::vector<flywave::topo::shape> shapeVec;
    for (int i = 0; i < count; i++) {
      shapeVec.emplace_back(*shapes[i]->shp);
    }
    auto result = flywave::topo::fuse(shapeVec, tol, glue);
    if (result) {
      return new topo_shape_t{
          .shp = std::make_shared<flywave::topo::shape>(*result)};
    }
  } catch (...) {
  }
  return nullptr;
}

TOPOCAPICALL topo_shape_t *topo_cut(topo_shape_t *shp, topo_shape_t *tool,
                                    double tol, bool glue) {
  try {
    auto result = flywave::topo::cut(*shp->shp, *tool->shp, tol, glue);
    if (result) {
      return new topo_shape_t{
          .shp = std::make_shared<flywave::topo::shape>(*result)};
    }
  } catch (...) {
  }
  return nullptr;
}

TOPOCAPICALL topo_shape_t *topo_cut_multi(topo_shape_t *shp,
                                          topo_shape_t **toCuts, int count,
                                          double tol, bool glue) {
  try {
    std::vector<flywave::topo::shape> toCutVec;
    for (int i = 0; i < count; i++) {
      toCutVec.emplace_back(*toCuts[i]->shp);
    }
    auto result = flywave::topo::cut(*shp->shp, toCutVec, tol, glue);
    if (result) {
      return new topo_shape_t{
          .shp = std::make_shared<flywave::topo::shape>(*result)};
    }
  } catch (...) {
  }
  return nullptr;
}

TOPOCAPICALL topo_shape_t *topo_intersect(topo_shape_t *shp,
                                          topo_shape_t *toIntersect, double tol,
                                          bool glue) {
  try {
    auto result =
        flywave::topo::intersect(*shp->shp, *toIntersect->shp, tol, glue);
    if (result) {
      return new topo_shape_t{
          .shp = std::make_shared<flywave::topo::shape>(*result)};
    }
  } catch (...) {
  }
  return nullptr;
}

TOPOCAPICALL topo_shape_t *topo_intersect_multi(topo_shape_t *shp,
                                                topo_shape_t **toIntersects,
                                                int count, double tol,
                                                bool glue) {
  try {
    std::vector<flywave::topo::shape> toIntersectVec;
    for (int i = 0; i < count; i++) {
      toIntersectVec.emplace_back(*toIntersects[i]->shp);
    }
    auto result =
        flywave::topo::intersect(*shp->shp, toIntersectVec, tol, glue);
    if (result) {
      return new topo_shape_t{
          .shp = std::make_shared<flywave::topo::shape>(*result)};
    }
  } catch (...) {
  }
  return nullptr;
}

TOPOCAPICALL topo_shape_t *
topo_split(topo_shape_t *shp, topo_shape_t **splitters, int count, double tol) {
  try {
    std::vector<flywave::topo::shape> splitterVec;
    for (int i = 0; i < count; i++) {
      splitterVec.emplace_back(*splitters[i]->shp);
    }
    auto result = flywave::topo::split(*shp->shp, splitterVec, tol);
    if (result) {
      return new topo_shape_t{
          .shp = std::make_shared<flywave::topo::shape>(*result)};
    }
  } catch (...) {
  }
  return nullptr;
}

// Intersection operations
TOPOCAPICALL topo_face_t *
topo_faces_intersected_by_line(topo_shape_t *shp, pnt3d_t point, dir3d_t axis,
                               double tolerance,
                               intersection_direction_t direction, int *count) {
  try {
    gp_Pnt p(point.x, point.y, point.z);
    gp_Dir d(axis.x, axis.y, axis.z);
    auto faces = flywave::topo::faces_intersected_by_line(
        *shp->shp, p, d, tolerance,
        static_cast<flywave::topo::intersection_direction>(direction));

    *count = static_cast<int>(faces.size());
    auto result = new topo_face_t[*count];
    for (int i = 0; i < *count; i++) {
      result[i].shp = new topo_shape_t{
          .shp = std::make_shared<flywave::topo::face>(faces[i])};
    }
    return result;
  } catch (...) {
    *count = 0;
    return nullptr;
  }
}

// Modeling operations
TOPOCAPICALL topo_shape_t *topo_fill(topo_shape_t *shp,
                                     topo_shape_t **constraints, int count) {
  try {
    std::vector<flywave::topo::shape> constraintVec;
    for (int i = 0; i < count; i++) {
      constraintVec.emplace_back(*constraints[i]->shp);
    }
    auto result = flywave::topo::fill(*shp->shp, constraintVec);
    if (result) {
      return new topo_shape_t{
          .shp = std::make_shared<flywave::topo::shape>(*result)};
    }
  } catch (...) {
  }
  return nullptr;
}

TOPOCAPICALL topo_shape_t *topo_shelling(topo_shape_t *shp,
                                         topo_face_t *faceList, int faceCount,
                                         double thickness, double tolerance,
                                         int joinType) {
  try {
    std::vector<flywave::topo::face> faces;
    for (int i = 0; i < faceCount; i++) {
      faces.emplace_back(*cast_to_topo(faceList[i]));
    }
    auto result =
        flywave::topo::shelling(*shp->shp, faces, thickness, tolerance,
                                static_cast<GeomAbs_JoinType>(joinType));
    if (result) {
      return new topo_shape_t{
          .shp = std::make_shared<flywave::topo::shape>(*result)};
    }
  } catch (...) {
  }
  return nullptr;
}

TOPOCAPICALL topo_shape_t *topo_fillet(topo_shape_t *shp, topo_edge_t *edges,
                                       int edgeCount, double radius) {
  try {
    std::vector<flywave::topo::edge> edgeVec;
    for (int i = 0; i < edgeCount; i++) {
      edgeVec.emplace_back(*cast_to_topo(edges[i]));
    }
    auto result = flywave::topo::fillet(*shp->shp, edgeVec, radius);
    if (result) {
      return new topo_shape_t{
          .shp = std::make_shared<flywave::topo::shape>(*result)};
    }
  } catch (...) {
  }
  return nullptr;
}

TOPOCAPICALL topo_shape_t *topo_chamfer(topo_shape_t *baseShape,
                                        topo_edge_t *edges, int edgeCount,
                                        double distance1, double distance2,
                                        bool hasDistance2) {
  try {
    std::vector<flywave::topo::edge> edgeVec;
    for (int i = 0; i < edgeCount; i++) {
      edgeVec.emplace_back(*cast_to_topo(edges[i]));
    }
    boost::optional<double> dist2 =
        hasDistance2 ? boost::optional<double>(distance2) : boost::none;
    auto result =
        flywave::topo::chamfer(*baseShape->shp, edgeVec, distance1, dist2);
    if (result) {
      return new topo_shape_t{
          .shp = std::make_shared<flywave::topo::shape>(*result)};
    }
  } catch (...) {
  }
  return nullptr;
}

// Extrusion operations
TOPOCAPICALL topo_shape_t *topo_extrude(topo_shape_t *shape,
                                        vec3d_t direction) {
  try {
    gp_Vec dir(direction.x, direction.y, direction.z);
    auto result = flywave::topo::extrude(*shape->shp, dir);
    if (result) {
      return new topo_shape_t{
          .shp = std::make_shared<flywave::topo::shape>(*result)};
    }
  } catch (...) {
  }
  return nullptr;
}

TOPOCAPICALL topo_shape_t *
topo_extrude_linear(topo_wire_t outerWire, topo_wire_t *innerWires,
                    int innerCount, vec3d_t vecNormal, double taper) {
  try {
    std::vector<flywave::topo::wire> innerWireVec;
    for (int i = 0; i < innerCount; i++) {
      innerWireVec.emplace_back(*cast_to_topo(innerWires[i]));
    }
    gp_Vec normal(vecNormal.x, vecNormal.y, vecNormal.z);
    auto result = flywave::topo::extrude_linear(*cast_to_topo(outerWire),
                                                innerWireVec, normal, taper);
    if (result) {
      return new topo_shape_t{
          .shp = std::make_shared<flywave::topo::shape>(*result)};
    }
  } catch (...) {
  }
  return nullptr;
}

TOPOCAPICALL topo_shape_t *topo_extrude_linear_with_rotation(
    topo_wire_t outerWire, topo_wire_t *innerWires, int innerCount,
    pnt3d_t center, vec3d_t normal, double angleDegrees) {
  try {
    std::vector<flywave::topo::wire> innerWireVec;
    for (int i = 0; i < innerCount; i++) {
      innerWireVec.emplace_back(*cast_to_topo(innerWires[i]));
    }
    gp_Pnt c(center.x, center.y, center.z);
    gp_Vec n(normal.x, normal.y, normal.z);
    auto result = flywave::topo::extrude_linear_with_rotation(
        *cast_to_topo(outerWire), innerWireVec, c, n, angleDegrees);
    if (result) {
      return new topo_shape_t{
          .shp = std::make_shared<flywave::topo::shape>(*result)};
    }
  } catch (...) {
  }
  return nullptr;
}

// Revolution operations
TOPOCAPICALL topo_shape_t *topo_revolve(topo_shape_t *shape, pnt3d_t axisPoint,
                                        dir3d_t axisDirection,
                                        double angleDegrees) {
  try {
    gp_Pnt p(axisPoint.x, axisPoint.y, axisPoint.z);
    gp_Dir d(axisDirection.x, axisDirection.y, axisDirection.z);
    auto result = flywave::topo::revolve(*shape->shp, p, d, angleDegrees);
    if (result) {
      return new topo_shape_t{
          .shp = std::make_shared<flywave::topo::shape>(*result)};
    }
  } catch (...) {
  }
  return nullptr;
}

TOPOCAPICALL topo_shape_t *
topo_revolve_wire(topo_wire_t outerWire, topo_wire_t *innerWires,
                  int innerCount, double angleDegrees, pnt3d_t axisStart,
                  pnt3d_t axisEnd) {
  try {
    std::vector<flywave::topo::wire> innerWireVec;
    for (int i = 0; i < innerCount; i++) {
      innerWireVec.emplace_back(*cast_to_topo(innerWires[i]));
    }
    gp_Pnt start(axisStart.x, axisStart.y, axisStart.z);
    gp_Pnt end(axisEnd.x, axisEnd.y, axisEnd.z);
    auto result = flywave::topo::revolve(*cast_to_topo(outerWire), innerWireVec,
                                         angleDegrees, start, end);
    if (result) {
      return new topo_shape_t{
          .shp = std::make_shared<flywave::topo::shape>(*result)};
    }
  } catch (...) {
  }
  return nullptr;
}

// Sweep operations
TOPOCAPICALL topo_shape_t *topo_sweep(topo_wire_t outerWire,
                                      topo_wire_t *innerWires, int innerCount,
                                      topo_shape_t *path, bool makeSolid,
                                      bool isFrenet, topo_shape_t *mode,
                                      transition_mode_t transitionMode) {
  try {
    std::vector<flywave::topo::wire> innerWireVec;
    for (int i = 0; i < innerCount; i++) {
      innerWireVec.emplace_back(*cast_to_topo(innerWires[i]));
    }
    auto result = flywave::topo::sweep(
        *cast_to_topo(outerWire), innerWireVec, *path->shp, makeSolid, isFrenet,
        mode ? &(*mode->shp) : nullptr,
        static_cast<flywave::topo::transition_mode>(transitionMode));
    if (result) {
      return new topo_shape_t{
          .shp = std::make_shared<flywave::topo::shape>(*result)};
    }
  } catch (...) {
  }
  return nullptr;
}

TOPOCAPICALL topo_shape_t *topo_sweep_multi(topo_shape_t **profiles, int count,
                                            topo_shape_t *path, bool makeSolid,
                                            bool isFrenet, topo_shape_t *mode) {
  try {
    std::vector<flywave::topo::shape> profileVec;
    for (int i = 0; i < count; i++) {
      profileVec.emplace_back(*profiles[i]->shp);
    }
    auto result =
        flywave::topo::sweep_multi(profileVec, *path->shp, makeSolid, isFrenet,
                                   mode ? &(*mode->shp) : nullptr);
    if (result) {
      return new topo_shape_t{
          .shp = std::make_shared<flywave::topo::shape>(*result)};
    }
  } catch (...) {
  }
  return nullptr;
}

// Loft operations
TOPOCAPICALL topo_shape_t *
topo_loft(topo_shape_t **profiles, int count, bool cap, bool ruled,
          const char *continuity, const char *parametrization, int degree,
          bool compat, bool smoothing, double *weights) {
  try {
    std::vector<flywave::topo::shape> profileVec;
    for (int i = 0; i < count; i++) {
      profileVec.emplace_back(*profiles[i]->shp);
    }
    std::array<double, 3> weightArr = {weights[0], weights[1], weights[2]};
    auto result = flywave::topo::loft(
        profileVec, cap, ruled, continuity ? continuity : "C2",
        parametrization ? parametrization : "uniform", degree, compat,
        smoothing, weightArr);
    if (result) {
      return new topo_shape_t{
          .shp = std::make_shared<flywave::topo::shape>(*result)};
    }
  } catch (...) {
  }
  return nullptr;
}

// Other operations
TOPOCAPICALL topo_shape_t *topo_offset(topo_shape_t *shape, double offset,
                                       bool cap, bool both, double tol) {
  try {
    auto result = flywave::topo::offset(*shape->shp, offset, cap, both, tol);
    if (result) {
      return new topo_shape_t{
          .shp = std::make_shared<flywave::topo::shape>(*result)};
    }
  } catch (...) {
  }
  return nullptr;
}

TOPOCAPICALL topo_shape_t *topo_clean(topo_shape_t *shape) {
  try {
    auto result = flywave::topo::clean(*shape->shp);
    if (result) {
      return new topo_shape_t{
          .shp = std::make_shared<flywave::topo::shape>(*result)};
    }
  } catch (...) {
  }
  return nullptr;
}

// Utility functions
TOPOCAPICALL void topo_closest(topo_shape_t *shape1, topo_shape_t *shape2,
                               pnt3d_t *p1, pnt3d_t *p2) {
  try {
    auto result = flywave::topo::closest(*shape1->shp, *shape2->shp);
    *p1 = cast_from_gp(result.first);
    *p2 = cast_from_gp(result.second);
  } catch (...) {
    *p1 = pnt3d_t{0, 0, 0};
    *p2 = pnt3d_t{0, 0, 0};
  }
}

TOPOCAPICALL pnt3d_t topo_combined_center(topo_shape_t **objects, int count) {
  try {
    std::vector<flywave::topo::shape> objectVec;
    for (int i = 0; i < count; i++) {
      objectVec.emplace_back(*objects[i]->shp);
    }
    auto result = flywave::topo::combined_center(objectVec);
    return cast_from_gp(result);
  } catch (...) {
    return pnt3d_t{0, 0, 0};
  }
}

TOPOCAPICALL pnt3d_t topo_combined_center_of_bound_box(topo_shape_t **objects,
                                                       int count) {
  try {
    std::vector<flywave::topo::shape> objectVec;
    for (int i = 0; i < count; i++) {
      objectVec.emplace_back(*objects[i]->shp);
    }
    auto result = flywave::topo::combined_center_of_bound_box(objectVec);
    return cast_from_gp(result);
  } catch (...) {
    return pnt3d_t{0, 0, 0};
  }
}

topo_shape_t *read_shape_from_step_file(const char *filename) {
  std::string f{filename};
  auto res = flywave::topo::read_shape_from_step(f);
  auto shp = std::make_shared<flywave::topo::shape>(res);
  return new _topo_shape_t{.shp = shp};
}

TOPOCAPICALL char *topo_shape_write_to_step_buffer(topo_shape_t *shape,
                                                   int *buffer_size) {
  if (!shape || !buffer_size)
    return nullptr;
  std::string stepStr = flywave::topo::write_shape_to_step(*shape->shp);
  *buffer_size = stepStr.size();

  char *buffer = (char *)malloc(*buffer_size + 1);
  if (!buffer)
    return nullptr;

  memcpy(buffer, stepStr.c_str(), *buffer_size);
  buffer[*buffer_size] = '\0';

  return buffer;
}

TOPOCAPICALL topo_shape_t **read_shapes_from_step_file(const char *filename,
                                                       int *count) {
  if (!filename || !count)
    return nullptr;

  if (*count == 0) {
    return nullptr;
  }
  std::vector<flywave::topo::shape> shapes =
      flywave::topo::read_shapes_from_step(filename);
  *count = shapes.size();

  topo_shape_t **result =
      (topo_shape_t **)malloc(*count * sizeof(topo_shape_t *));
  if (!result)
    return nullptr;

  for (int i = 1; i <= *count; i++) {
    result[i - 1] = new topo_shape_t{
        .shp = std::make_shared<flywave::topo::shape>(shapes[i - 1])};
  }

  return result;
}

TOPOCAPICALL void free_shapes_from_step(topo_shape_t **shapes, int count) {
  if (!shapes)
    return;
  free(shapes);
}

topo_wire_sample_point_t *topo_wire_sample_at_distances(topo_wire_t wire,
                                                        double *distances,
                                                        int count,
                                                        int *result_count) {
  try {
    std::vector<double> dists(distances, distances + count);
    auto samples =
        flywave::topo::sample_wire_at_distances(*cast_to_topo(wire), dists);

    auto result = new topo_wire_sample_point_t[samples.size()];
    for (size_t i = 0; i < samples.size(); i++) {
      result[i].position = cast_from_gp(samples[i].position);
      result[i].tangent = cast_from_gp(samples[i].tangent);
      result[i].edge = topo_edge_t{
          .shp = new topo_shape_t{
              .shp = std::make_shared<flywave::topo::shape>(samples[i].edge)}};
    }
    *result_count = static_cast<int>(samples.size());
    return result;
  } catch (...) {
    *result_count = 0;
    return nullptr;
  }
}

void topo_wire_sample_list_free(topo_wire_sample_point_t *samples, int count) {
  if (samples) {
    for (int i = 0; i < count; i++) {
      if (samples[i].edge.shp) {
        delete samples[i].edge.shp;
      }
    }
    delete[] samples;
  }
}

topo_wire_t topo_wire_clip_between_distances(topo_wire_t wire,
                                             double start_distance,
                                             double end_distance) {
  try {
    auto clipped = flywave::topo::clip_wire_between_distances(
        *cast_to_topo(wire), start_distance, end_distance);
    return topo_wire_t{
        .shp = new topo_shape_t{
            .shp = std::make_shared<flywave::topo::wire>(clipped)}};
  } catch (...) {
    return {nullptr};
  }
}

topo_profile_projection_t
topo_calc_profile_projection(topo_wire_t path, dir3d_t upDir, double *offset) {
  topo_profile_projection_t result;
  boost::optional<double> posOpt =
      offset ? boost::optional<double>{*offset} : boost::none;
  auto section = flywave::topo::cacl_profile_projection(
      *cast_to_topo(path), cast_to_gp(upDir), posOpt);
  result.axes = cast_from_gp(section.axes);
  result.trsf = cast_from_gp(section.trsf);
  result.tangent = cast_from_gp(section.tangent);
  result.position = cast_from_gp(section.position);
  return result;
}

pnt3d_t topo_profile_project_point(topo_profile_projection_t *proj,
                                   pnt3d_t point) {
  gp_Ax2 axes = cast_to_gp(proj->axes);
  gp_Trsf trsf = cast_to_gp(proj->trsf);
  gp_Pnt out =
      axes.Location().Translated(gp_Vec(point.z, point.y, 0).Transformed(trsf));
  return cast_from_gp(out);
}

pnt3d_t *topo_profile_project_point_list(topo_profile_projection_t *proj,
                                         pnt3d_t *points, int count) {
  try {
    gp_Ax2 axes = cast_to_gp(proj->axes);
    gp_Trsf trsf = cast_to_gp(proj->trsf);

    pnt3d_t *result = new pnt3d_t[count];
    for (int i = 0; i < count; i++) {
      gp_Pnt point(points[i].x, points[i].y, points[i].z);
      gp_Pnt projected = axes.Location().Translated(
          gp_Vec(point.Z(), point.Y(), 0).Transformed(trsf));
      result[i] = cast_from_gp(projected);
    }
    return result;
  } catch (...) {
    return nullptr;
  }
}

void topo_profile_project_point_list_free(pnt3d_t *points) {
  if (points) {
    delete[] points;
  }
}

double topo_wrie_length(topo_wire_t wire) {
  return flywave::topo::wrie_length(*cast_to_topo(wire));
}

pnt3d_t *topo_make_catenary(pnt3d_t p1, pnt3d_t p2, double slack, double maxSag,
                            dir3d_t up, double tessellation, int *point_count) {
  try {
    gp_Pnt gp_p1(p1.x, p1.y, p1.z);
    gp_Pnt gp_p2(p2.x, p2.y, p2.z);
    gp_Dir up_dir = cast_to_gp(up);

    auto points = flywave::topo::make_catenary(gp_p1, gp_p2, slack, maxSag,
                                               up_dir, tessellation);

    pnt3d_t *result = (pnt3d_t *)malloc(sizeof(pnt3d_t) * points.size());
    for (size_t i = 0; i < points.size(); i++) {
      result[i].x = points[i].X();
      result[i].y = points[i].Y();
      result[i].z = points[i].Z();
    }

    *point_count = static_cast<int>(points.size());
    return result;
  } catch (...) {
    *point_count = 0;
    return nullptr;
  }
}

void topo_free_catenary_points(pnt3d_t *points) {
  if (points) {
    free(points);
  }
}

TOPOCAPICALL topo_shape_t *
topo_clip_with_4d(topo_shape_t *shape, const work_progress_params_t *params) {
  try {
    flywave::topo::work_progress_params cpp_params;

    if (params->direction) {
      cpp_params.direction = boost::make_optional(gp_Dir(
          params->direction->x, params->direction->y, params->direction->z));
    }

    if (params->radius) {
      cpp_params.radius = boost::make_optional(*params->radius);
    }

    if (params->original_path) {
      cpp_params.original_path =
          flywave::topo::wire(*params->original_path->shp->shp);
    }

    if (params->points && params->point_count > 0) {
      cpp_params.points.reserve(params->point_count);
      for (int i = 0; i < params->point_count; ++i) {
        cpp_params.points.push_back(gp_Pnt(
            params->points[i].x, params->points[i].y, params->points[i].z));
      }
    }

    cpp_params.type = static_cast<flywave::topo::progress_type>(params->_type);

    cpp_params.range = {params->_range[0], params->_range[1]};

    flywave::topo::shape result = clip_with_topo4d(*shape->shp, cpp_params);

    // 返回结果
    return new topo_shape_t{.shp =
                                std::make_shared<flywave::topo::shape>(result)};

  } catch (...) {
    return NULL;
  }
}
#ifdef __cplusplus
}
#endif
