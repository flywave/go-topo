#include "topo_c_api.h"
#include "geometry_impl.hh"
#include "standard_impl.hh"
#include "topo_impl.hh"

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
    return new topo_shape_t{p->shp};
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
    return p->shp->transform(cast_to_gp(mat));
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
    return new topo_shape_t{std::make_shared<flywave::topo::shape>(
        p->shp->transformed(cast_to_gp(mat)))};
  }
  return nullptr;
}

topo_shape_t *topo_shape_translated(topo_shape_t *p, vec3d_t delta) {
  if (p) {
    return new topo_shape_t{std::make_shared<flywave::topo::shape>(
        p->shp->translated(cast_to_gp(delta)))};
  }
  return nullptr;
}

topo_shape_t *topo_shape_rotated_from_two_point(topo_shape_t *p, double angle,
                                                pnt3d_t p1, pnt3d_t p2) {
  if (p) {
    return new topo_shape_t{std::make_shared<flywave::topo::shape>(
        p->shp->rotated(angle, cast_to_gp(p1), cast_to_gp(p2)))};
  }
  return nullptr;
}

topo_shape_t *topo_shape_rotated_from_axis1(topo_shape_t *p, double angle,
                                            axis1_t a) {
  if (p) {
    return new topo_shape_t{std::make_shared<flywave::topo::shape>(
        p->shp->rotated(angle, cast_to_gp(a)))};
  }
  return nullptr;
}

topo_shape_t *topo_shape_rotated_from_quaternion(topo_shape_t *p,
                                                 quaternion_t q) {
  if (p) {
    return new topo_shape_t{
        std::make_shared<flywave::topo::shape>(p->shp->rotated(cast_to_gp(q)))};
  }
  return nullptr;
}

topo_shape_t *topo_shape_scaled(topo_shape_t *p, double angle, pnt3d_t a) {
  if (p) {
    return new topo_shape_t{std::make_shared<flywave::topo::shape>(
        p->shp->scaled(cast_to_gp(a), angle))};
  }
  return nullptr;
}

topo_shape_t *topo_shape_mirrored_from_point_norm(topo_shape_t *p, pnt3d_t pnt,
                                                  pnt3d_t ner) {
  if (p) {
    return new topo_shape_t{std::make_shared<flywave::topo::shape>(
        p->shp->mirrored(cast_to_gp(pnt), cast_to_gp(ner)))};
  }
  return nullptr;
}

topo_shape_t *topo_shape_mirrored_from_axis1(topo_shape_t *p, axis1_t a) {
  if (p) {
    return new topo_shape_t{std::make_shared<flywave::topo::shape>(
        p->shp->mirrored(cast_to_gp(a)))};
  }
  return nullptr;
}

topo_shape_t *topo_shape_mirrored_from_axis2(topo_shape_t *p, axis2_t a) {
  if (p) {
    return new topo_shape_t{std::make_shared<flywave::topo::shape>(
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
  return new topo_location_t{p->shp->location()};
}

void topo_shape_set_location(topo_shape_t *p, topo_location_t *loc) {
  p->shp->set_location(loc->loc);
}

_Bool topo_shape_fix_shape(topo_shape_t *p) { return p->shp->fix_shape(); }

topo_shape_t *topo_shape_copy(topo_shape_t *p) {
  return new topo_shape_t{
      std::make_shared<flywave::topo::shape>(p->shp->copy())};
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

topo_vertex_t topo_vertex_new(double x, double y, double z) {
  return topo_vertex_t{
      new topo_shape_t{std::make_shared<flywave::topo::vertex>(x, y, z)}};
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
  return topo_wire_t{new topo_shape_t{std::make_shared<flywave::topo::wire>(
      flywave::topo::wire::make_polygon())}};
}

topo_wire_t topo_make_polygon_from_two_point(pnt3d_t P1, pnt3d_t P2) {
  return topo_wire_t{new topo_shape_t{std::make_shared<flywave::topo::wire>(
      flywave::topo::wire::make_polygon(cast_to_gp(P1), cast_to_gp(P2)))}};
}

topo_wire_t topo_make_polygon_from_three_point(pnt3d_t P1, pnt3d_t P2,
                                               pnt3d_t P3, _Bool Close) {
  return topo_wire_t{new topo_shape_t{
      std::make_shared<flywave::topo::wire>(flywave::topo::wire::make_polygon(
          cast_to_gp(P1), cast_to_gp(P2), cast_to_gp(P3), Close))}};
}

topo_wire_t topo_make_polygon_from_four_point(pnt3d_t P1, pnt3d_t P2,
                                              pnt3d_t P3, pnt3d_t P4,
                                              _Bool Close) {
  return topo_wire_t{new topo_shape_t{std::make_shared<flywave::topo::wire>(
      flywave::topo::wire::make_polygon(cast_to_gp(P1), cast_to_gp(P2),
                                        cast_to_gp(P3), cast_to_gp(P4),
                                        Close))}};
}

topo_wire_t topo_make_polygon_two_vertex(topo_vertex_t V1, topo_vertex_t V2) {
  return topo_wire_t{new topo_shape_t{
      std::make_shared<flywave::topo::wire>(flywave::topo::wire::make_polygon(
          *cast_to_topo(V1), *cast_to_topo(V2)))}};
}

topo_wire_t topo_make_polygon_from_three_vertex(topo_vertex_t V1,
                                                topo_vertex_t V2,
                                                topo_vertex_t V3, _Bool Close) {
  return topo_wire_t{new topo_shape_t{
      std::make_shared<flywave::topo::wire>(flywave::topo::wire::make_polygon(
          *cast_to_topo(V1), *cast_to_topo(V2), *cast_to_topo(V3), Close))}};
}

topo_wire_t topo_make_polygon_from_four_vertex(topo_vertex_t V1,
                                               topo_vertex_t V2,
                                               topo_vertex_t V3,
                                               topo_vertex_t V4, _Bool Close) {
  return topo_wire_t{new topo_shape_t{std::make_shared<flywave::topo::wire>(
      flywave::topo::wire::make_polygon(*cast_to_topo(V1), *cast_to_topo(V2),
                                        *cast_to_topo(V3), *cast_to_topo(V4),
                                        Close))}};
}

topo_wire_t topo_make_wire_from_edge(topo_edge_t E) {
  return topo_wire_t{new topo_shape_t{std::make_shared<flywave::topo::wire>(
      flywave::topo::wire::make_wire(*cast_to_topo(E)))}};
}

topo_wire_t topo_make_wire_from_two_edge(topo_edge_t E1, topo_edge_t E2) {
  return topo_wire_t{new topo_shape_t{std::make_shared<flywave::topo::wire>(
      flywave::topo::wire::make_wire(*cast_to_topo(E1), *cast_to_topo(E2)))}};
}

topo_wire_t topo_make_wire_from_three_edge(topo_edge_t E1, topo_edge_t E2,
                                           topo_edge_t E3) {
  return topo_wire_t{new topo_shape_t{
      std::make_shared<flywave::topo::wire>(flywave::topo::wire::make_wire(
          *cast_to_topo(E1), *cast_to_topo(E2), *cast_to_topo(E3)))}};
}

topo_wire_t topo_make_wire_from_four_edge(topo_edge_t E1, topo_edge_t E2,
                                          topo_edge_t E3, topo_edge_t E4) {
  return topo_wire_t{new topo_shape_t{std::make_shared<flywave::topo::wire>(
      flywave::topo::wire::make_wire(*cast_to_topo(E1), *cast_to_topo(E2),
                                     *cast_to_topo(E3), *cast_to_topo(E4)))}};
}

topo_wire_t topo_make_wire_from_wire(topo_wire_t W) {
  return topo_wire_t{new topo_shape_t{std::make_shared<flywave::topo::wire>(
      flywave::topo::wire::make_wire(*cast_to_topo(W)))}};
}

topo_wire_t topo_make_wire_from_two_wire(topo_wire_t W, topo_edge_t E) {
  return topo_wire_t{new topo_shape_t{std::make_shared<flywave::topo::wire>(
      flywave::topo::wire::make_wire(*cast_to_topo(W), *cast_to_topo(E)))}};
}

topo_wire_t topo_make_wire_from_edges(topo_edge_t *edges, int count) {
  try {
    std::vector<flywave::topo::edge> oes;
    for (int i = 0; i < count; i++) {
      oes.emplace_back(*cast_to_topo(edges[i]));
    }
    return topo_wire_t{new topo_shape_t{std::make_shared<flywave::topo::wire>(
        flywave::topo::wire::make_wire(oes))}};
  } catch (...) {
    return topo_wire_t{};
  }
}

topo_wire_t topo_make_wire_from_wries(topo_wire_t *wires, int count) {
  std::vector<flywave::topo::wire> ows;
  for (int i = 0; i < count; i++) {
    ows.emplace_back(*cast_to_topo(wires[i]));
  }
  return topo_wire_t{new topo_shape_t{std::make_shared<flywave::topo::wire>(
      flywave::topo::wire::make_wire(ows))}};
}

int topo_wire_num_vertices(topo_wire_t w) {
  auto opt = cast_to_topo(w);
  if (opt) {
    return opt->num_vertices();
  }
  return -1;
}

int topo_wire_num_edges(topo_wire_t w) {
  auto opt = cast_to_topo(w);
  if (opt) {
    return opt->num_edges();
  }
  return -1;
}

bool topo_wire_is_closed(topo_wire_t w) {
  auto opt = cast_to_topo(w);
  if (opt) {
    return opt->is_closed();
  }
  return false;
}

double topo_wire_length(topo_wire_t w) {
  auto opt = cast_to_topo(w);
  if (opt) {
    return opt->length();
  }
  return 0.0;
}

void topo_wire_convert_to_curves3d(topo_wire_t w) {
  auto opt = cast_to_topo(w);
  if (opt) {
    opt->convert_to_curves3d();
  }
}

int topo_wire_project(topo_wire_t w, topo_face_t f) {
  auto opt = cast_to_topo(w);
  if (opt) {
    return opt->project(*cast_to_topo(f));
  }
  return -1;
}

int topo_wire_offset(topo_wire_t w, double distance, int joinType) {
  auto opt = cast_to_topo(w);
  if (opt) {
    return opt->offset(distance, joinType);
  }
  return -1;
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

topo_edge_t topo_make_edge() {
  return topo_edge_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::edge>()}};
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
  return topo_edge_t{new topo_shape_t{std::make_shared<flywave::topo::edge>(
      flywave::topo::edge::make_polygon(vec, true))}};
}

topo_edge_t topo_edge_make_edge_from_two_vertex(topo_vertex_t V1,
                                                topo_vertex_t V2) {
  return topo_edge_t{new topo_shape_t{std::make_shared<flywave::topo::edge>(
      flywave::topo::edge::make_edge(*cast_to_topo(V1), *cast_to_topo(V2)))}};
}

topo_edge_t topo_edge_make_edge_from_two_point(pnt3d_t P1, pnt3d_t P2) {
  return topo_edge_t{new topo_shape_t{std::make_shared<flywave::topo::edge>(
      flywave::topo::edge::make_edge(cast_to_gp(P1), cast_to_gp(P2)))}};
}

topo_edge_t topo_edge_make_edge_from_line(line_t L) {
  return topo_edge_t{new topo_shape_t{std::make_shared<flywave::topo::edge>(
      flywave::topo::edge::make_edge(cast_to_gp(L)))}};
}

topo_edge_t topo_edge_make_edge_from_line_p(line_t L, double p1, double p2) {
  return topo_edge_t{new topo_shape_t{std::make_shared<flywave::topo::edge>(
      flywave::topo::edge::make_edge(cast_to_gp(L), p1, p2))}};
}

topo_edge_t topo_edge_make_edge_from_line_point(line_t L, pnt3d_t P1,
                                                pnt3d_t P2) {
  return topo_edge_t{new topo_shape_t{
      std::make_shared<flywave::topo::edge>(flywave::topo::edge::make_edge(
          cast_to_gp(L), cast_to_gp(P1), cast_to_gp(P2)))}};
}

topo_edge_t topo_edge_make_edge_from_line_vertex(line_t L, topo_vertex_t V1,
                                                 topo_vertex_t V2) {
  return topo_edge_t{new topo_shape_t{
      std::make_shared<flywave::topo::edge>(flywave::topo::edge::make_edge(
          cast_to_gp(L), *cast_to_topo(V1), *cast_to_topo(V2)))}};
}

topo_edge_t topo_edge_make_edge_from_circ(circ_t L) {
  return topo_edge_t{new topo_shape_t{std::make_shared<flywave::topo::edge>(
      flywave::topo::edge::make_edge(cast_to_gp(L)))}};
}

topo_edge_t topo_edge_make_edge_from_circ_p(circ_t L, double p1, double p2) {
  return topo_edge_t{new topo_shape_t{std::make_shared<flywave::topo::edge>(
      flywave::topo::edge::make_edge(cast_to_gp(L), p1, p2))}};
}

topo_edge_t topo_edge_make_edge_from_circ_point(circ_t L, pnt3d_t P1,
                                                pnt3d_t P2) {
  return topo_edge_t{new topo_shape_t{
      std::make_shared<flywave::topo::edge>(flywave::topo::edge::make_edge(
          cast_to_gp(L), cast_to_gp(P1), cast_to_gp(P2)))}};
}

topo_edge_t topo_edge_make_edge_from_circ_vertex(circ_t L, topo_vertex_t V1,
                                                 topo_vertex_t V2) {
  return topo_edge_t{new topo_shape_t{
      std::make_shared<flywave::topo::edge>(flywave::topo::edge::make_edge(
          cast_to_gp(L), *cast_to_topo(V1), *cast_to_topo(V2)))}};
}

topo_edge_t topo_edge_make_edge_from_elips(elips_t L) {
  return topo_edge_t{new topo_shape_t{std::make_shared<flywave::topo::edge>(
      flywave::topo::edge::make_edge(cast_to_gp(L)))}};
}

topo_edge_t topo_edge_make_edge_from_elips_p(elips_t L, double p1, double p2) {
  return topo_edge_t{new topo_shape_t{std::make_shared<flywave::topo::edge>(
      flywave::topo::edge::make_edge(cast_to_gp(L), p1, p2))}};
}

topo_edge_t topo_edge_make_edge_from_elips_point(elips_t L, pnt3d_t P1,
                                                 pnt3d_t P2) {
  return topo_edge_t{new topo_shape_t{
      std::make_shared<flywave::topo::edge>(flywave::topo::edge::make_edge(
          cast_to_gp(L), cast_to_gp(P1), cast_to_gp(P2)))}};
}

topo_edge_t topo_edge_make_edge_from_elips_vertex(elips_t L, topo_vertex_t V1,
                                                  topo_vertex_t V2) {
  return topo_edge_t{new topo_shape_t{
      std::make_shared<flywave::topo::edge>(flywave::topo::edge::make_edge(
          cast_to_gp(L), *cast_to_topo(V1), *cast_to_topo(V2)))}};
}

topo_edge_t topo_edge_make_edge_from_hyper(hyperbola_t L) {
  return topo_edge_t{new topo_shape_t{std::make_shared<flywave::topo::edge>(
      flywave::topo::edge::make_edge(cast_to_gp(L)))}};
}

topo_edge_t topo_edge_make_edge_from_hyper_p(hyperbola_t L, double p1,
                                             double p2) {
  return topo_edge_t{new topo_shape_t{std::make_shared<flywave::topo::edge>(
      flywave::topo::edge::make_edge(cast_to_gp(L), p1, p2))}};
}

topo_edge_t topo_edge_make_edge_from_hyper_point(hyperbola_t L, pnt3d_t P1,
                                                 pnt3d_t P2) {
  return topo_edge_t{new topo_shape_t{
      std::make_shared<flywave::topo::edge>(flywave::topo::edge::make_edge(
          cast_to_gp(L), cast_to_gp(P1), cast_to_gp(P2)))}};
}

topo_edge_t topo_edge_make_edge_from_hyper_vertex(hyperbola_t L,
                                                  topo_vertex_t V1,
                                                  topo_vertex_t V2) {
  return topo_edge_t{new topo_shape_t{
      std::make_shared<flywave::topo::edge>(flywave::topo::edge::make_edge(
          cast_to_gp(L), *cast_to_topo(V1), *cast_to_topo(V2)))}};
}

topo_edge_t topo_edge_make_edge_from_parab(parabola_t L) {
  return topo_edge_t{new topo_shape_t{std::make_shared<flywave::topo::edge>(
      flywave::topo::edge::make_edge(cast_to_gp(L)))}};
}

topo_edge_t topo_edge_make_edge_from_parab_p(parabola_t L, double p1,
                                             double p2) {
  return topo_edge_t{new topo_shape_t{std::make_shared<flywave::topo::edge>(
      flywave::topo::edge::make_edge(cast_to_gp(L), p1, p2))}};
}

topo_edge_t topo_edge_make_edge_from_parab_point(parabola_t L, pnt3d_t P1,
                                                 pnt3d_t P2) {
  return topo_edge_t{new topo_shape_t{
      std::make_shared<flywave::topo::edge>(flywave::topo::edge::make_edge(
          cast_to_gp(L), cast_to_gp(P1), cast_to_gp(P2)))}};
}

topo_edge_t topo_edge_make_edge_from_parab_vertex(parabola_t L,
                                                  topo_vertex_t V1,
                                                  topo_vertex_t V2) {
  return topo_edge_t{new topo_shape_t{
      std::make_shared<flywave::topo::edge>(flywave::topo::edge::make_edge(
          cast_to_gp(L), *cast_to_topo(V1), *cast_to_topo(V2)))}};
}

topo_edge_t topo_edge_make_edgee_from_curve(geom_curve_t *L) {
  return topo_edge_t{new topo_shape_t{std::make_shared<flywave::topo::edge>(
      flywave::topo::edge::make_edge(L->handle))}};
}

topo_edge_t topo_edge_make_edge_from_curve_p(geom_curve_t *L, double p1,
                                             double p2) {
  return topo_edge_t{new topo_shape_t{std::make_shared<flywave::topo::edge>(
      flywave::topo::edge::make_edge(L->handle, p1, p2))}};
}

topo_edge_t topo_edge_make_edge_from_curve_point(geom_curve_t *L, pnt3d_t P1,
                                                 pnt3d_t P2) {
  return topo_edge_t{new topo_shape_t{
      std::make_shared<flywave::topo::edge>(flywave::topo::edge::make_edge(
          L->handle, cast_to_gp(P1), cast_to_gp(P2)))}};
}

topo_edge_t topo_edge_make_edge_from_curve_vertex(geom_curve_t *L,
                                                  topo_vertex_t V1,
                                                  topo_vertex_t V2) {
  return topo_edge_t{new topo_shape_t{
      std::make_shared<flywave::topo::edge>(flywave::topo::edge::make_edge(
          L->handle, *cast_to_topo(V1), *cast_to_topo(V2)))}};
}

topo_edge_t topo_edge_make_edgee_from_curve_point_p(geom_curve_t *L, pnt3d_t P1,
                                                    pnt3d_t P2, double p1,
                                                    double p2) {
  return topo_edge_t{new topo_shape_t{
      std::make_shared<flywave::topo::edge>(flywave::topo::edge::make_edge(
          L->handle, cast_to_gp(P1), cast_to_gp(P2), p1, p2))}};
}

topo_edge_t topo_edge_make_edge_from_curve_vertex_p(geom_curve_t *L,
                                                    topo_vertex_t V1,
                                                    topo_vertex_t V2, double p1,
                                                    double p2) {
  return topo_edge_t{new topo_shape_t{
      std::make_shared<flywave::topo::edge>(flywave::topo::edge::make_edge(
          L->handle, *cast_to_topo(V1), *cast_to_topo(V2), p1, p2))}};
}

topo_edge_t topo_edge_make_edge_from_curve_surface(geom2d_curve_t *L,
                                                   geom_surface_t *S) {
  return topo_edge_t{new topo_shape_t{std::make_shared<flywave::topo::edge>(
      flywave::topo::edge::make_edge(L->handle, S->handle))}};
}

topo_edge_t topo_edge_make_edge_from_curve_surface_p(geom2d_curve_t *L,
                                                     geom_surface_t *S,
                                                     double p1, double p2) {
  return topo_edge_t{new topo_shape_t{std::make_shared<flywave::topo::edge>(
      flywave::topo::edge::make_edge(L->handle, S->handle, p1, p2))}};
}

topo_edge_t topo_edge_make_edge_from_curve_surface_point(geom2d_curve_t *L,
                                                         geom_surface_t *S,
                                                         pnt3d_t P1,
                                                         pnt3d_t P2) {
  return topo_edge_t{new topo_shape_t{
      std::make_shared<flywave::topo::edge>(flywave::topo::edge::make_edge(
          L->handle, S->handle, cast_to_gp(P1), cast_to_gp(P2)))}};
}

topo_edge_t topo_edge_make_edge_from_curve_surface_vertex(geom2d_curve_t *L,
                                                          geom_surface_t *S,
                                                          topo_vertex_t V1,
                                                          topo_vertex_t V2) {
  return topo_edge_t{new topo_shape_t{
      std::make_shared<flywave::topo::edge>(flywave::topo::edge::make_edge(
          L->handle, S->handle, *cast_to_topo(V1), *cast_to_topo(V2)))}};
}

topo_edge_t topo_edge_make_edge_from_curve_surface_point_p(
    geom2d_curve_t *L, geom_surface_t *S, pnt3d_t P1, pnt3d_t P2, double p1,
    double p2) {
  return topo_edge_t{new topo_shape_t{
      std::make_shared<flywave::topo::edge>(flywave::topo::edge::make_edge(
          L->handle, S->handle, cast_to_gp(P1), cast_to_gp(P2), p1, p2))}};
}

topo_edge_t topo_edge_make_edge_from_curve_surface_vertex_p(
    geom2d_curve_t *L, geom_surface_t *S, topo_vertex_t V1, topo_vertex_t V2,
    double p1, double p2) {
  return topo_edge_t{new topo_shape_t{std::make_shared<flywave::topo::edge>(
      flywave::topo::edge::make_edge(L->handle, S->handle, *cast_to_topo(V1),
                                     *cast_to_topo(V2), p1, p2))}};
}

topo_edge_t topo_edge_make_edge2d_from_two_vertex(topo_vertex_t V1,
                                                  topo_vertex_t V2) {
  return topo_edge_t{new topo_shape_t{std::make_shared<flywave::topo::edge>(
      flywave::topo::edge::make_edge2d(*cast_to_topo(V1), *cast_to_topo(V2)))}};
}

topo_edge_t topo_edge_make_edge2d_from_two_point(pnt2d_t P1, pnt2d_t P2) {
  return topo_edge_t{new topo_shape_t{std::make_shared<flywave::topo::edge>(
      flywave::topo::edge::make_edge2d(cast_to_gp(P1), cast_to_gp(P2)))}};
}

topo_edge_t topo_edge_make_edge2d_from_line(line2d_t L) {
  return topo_edge_t{new topo_shape_t{std::make_shared<flywave::topo::edge>(
      flywave::topo::edge::make_edge2d(cast_to_gp(L)))}};
}

topo_edge_t topo_edge_make_edge2d_from_line_p(line2d_t L, double p1,
                                              double p2) {
  return topo_edge_t{new topo_shape_t{std::make_shared<flywave::topo::edge>(
      flywave::topo::edge::make_edge2d(cast_to_gp(L), p1, p2))}};
}

topo_edge_t topo_edge_make_edge2d_from_line_point(line2d_t L, pnt2d_t P1,
                                                  pnt2d_t P2) {
  return topo_edge_t{new topo_shape_t{
      std::make_shared<flywave::topo::edge>(flywave::topo::edge::make_edge2d(
          cast_to_gp(L), cast_to_gp(P1), cast_to_gp(P2)))}};
}

topo_edge_t topo_edge_make_edge2d_from_line_vertex(line2d_t L, topo_vertex_t V1,
                                                   topo_vertex_t V2) {
  return topo_edge_t{new topo_shape_t{
      std::make_shared<flywave::topo::edge>(flywave::topo::edge::make_edge2d(
          cast_to_gp(L), *cast_to_topo(V1), *cast_to_topo(V2)))}};
}

topo_edge_t topo_edge_make_edge2d_from_circ(circ2d_t L) {
  return topo_edge_t{new topo_shape_t{std::make_shared<flywave::topo::edge>(
      flywave::topo::edge::make_edge2d(cast_to_gp(L)))}};
}

topo_edge_t topo_edge_make_edge2d_from_circ_p(circ2d_t L, double p1,
                                              double p2) {
  return topo_edge_t{new topo_shape_t{std::make_shared<flywave::topo::edge>(
      flywave::topo::edge::make_edge2d(cast_to_gp(L), p1, p2))}};
}

topo_edge_t topo_edge_make_edge2d_from_circ_point(circ2d_t L, pnt2d_t P1,
                                                  pnt2d_t P2) {
  return topo_edge_t{new topo_shape_t{
      std::make_shared<flywave::topo::edge>(flywave::topo::edge::make_edge2d(
          cast_to_gp(L), cast_to_gp(P1), cast_to_gp(P2)))}};
}

topo_edge_t topo_edge_make_edge2d_from_circ_vertex(circ2d_t L, topo_vertex_t V1,
                                                   topo_vertex_t V2) {
  return topo_edge_t{new topo_shape_t{
      std::make_shared<flywave::topo::edge>(flywave::topo::edge::make_edge2d(
          cast_to_gp(L), *cast_to_topo(V1), *cast_to_topo(V2)))}};
}

topo_edge_t topo_edge_make_edge2d_from_elips(elips2d_t L) {
  return topo_edge_t{new topo_shape_t{std::make_shared<flywave::topo::edge>(
      flywave::topo::edge::make_edge2d(cast_to_gp(L)))}};
}

topo_edge_t topo_edge_make_edge2d_from_elips_p(elips2d_t L, double p1,
                                               double p2) {
  return topo_edge_t{new topo_shape_t{std::make_shared<flywave::topo::edge>(
      flywave::topo::edge::make_edge2d(cast_to_gp(L), p1, p2))}};
}

topo_edge_t topo_edge_make_edge2d_from_elips_point(elips2d_t L, pnt2d_t P1,
                                                   pnt2d_t P2) {
  return topo_edge_t{new topo_shape_t{
      std::make_shared<flywave::topo::edge>(flywave::topo::edge::make_edge2d(
          cast_to_gp(L), cast_to_gp(P1), cast_to_gp(P2)))}};
}

topo_edge_t topo_edge_make_edge2d_from_elips_vertex(elips2d_t L,
                                                    topo_vertex_t V1,
                                                    topo_vertex_t V2) {
  return topo_edge_t{new topo_shape_t{
      std::make_shared<flywave::topo::edge>(flywave::topo::edge::make_edge2d(
          cast_to_gp(L), *cast_to_topo(V1), *cast_to_topo(V2)))}};
}

topo_edge_t topo_edge_make_edge2d_from_hyper(hyperbola2d_t L) {
  return topo_edge_t{new topo_shape_t{std::make_shared<flywave::topo::edge>(
      flywave::topo::edge::make_edge2d(cast_to_gp(L)))}};
}

topo_edge_t topo_edge_make_edge2d_from_hyper_p(hyperbola2d_t L, double p1,
                                               double p2) {
  return topo_edge_t{new topo_shape_t{std::make_shared<flywave::topo::edge>(
      flywave::topo::edge::make_edge2d(cast_to_gp(L), p1, p2))}};
}

topo_edge_t topo_edge_make_edge2d_from_hyper_point(hyperbola2d_t L, pnt2d_t P1,
                                                   pnt2d_t P2) {
  return topo_edge_t{new topo_shape_t{
      std::make_shared<flywave::topo::edge>(flywave::topo::edge::make_edge2d(
          cast_to_gp(L), cast_to_gp(P1), cast_to_gp(P2)))}};
}

topo_edge_t topo_edge_make_edge2d_from_hyper_vertex(hyperbola2d_t L,
                                                    topo_vertex_t V1,
                                                    topo_vertex_t V2) {
  return topo_edge_t{new topo_shape_t{
      std::make_shared<flywave::topo::edge>(flywave::topo::edge::make_edge2d(
          cast_to_gp(L), *cast_to_topo(V1), *cast_to_topo(V2)))}};
}

topo_edge_t topo_edge_make_edge2d_from_parab(parabola2d_t L) {
  return topo_edge_t{new topo_shape_t{std::make_shared<flywave::topo::edge>(
      flywave::topo::edge::make_edge2d(cast_to_gp(L)))}};
}

topo_edge_t topo_edge_make_edge2d_from_parab_p(parabola2d_t L, double p1,
                                               double p2) {
  return topo_edge_t{new topo_shape_t{std::make_shared<flywave::topo::edge>(
      flywave::topo::edge::make_edge2d(cast_to_gp(L), p1, p2))}};
}

topo_edge_t topo_edge_make_edge2d_from_parab_point(parabola2d_t L, pnt2d_t P1,
                                                   pnt2d_t P2) {
  return topo_edge_t{new topo_shape_t{
      std::make_shared<flywave::topo::edge>(flywave::topo::edge::make_edge2d(
          cast_to_gp(L), cast_to_gp(P1), cast_to_gp(P2)))}};
}

topo_edge_t topo_edge_make_edge2d_from_parab_vertex(parabola2d_t L,
                                                    topo_vertex_t V1,
                                                    topo_vertex_t V2) {
  return topo_edge_t{new topo_shape_t{
      std::make_shared<flywave::topo::edge>(flywave::topo::edge::make_edge2d(
          cast_to_gp(L), *cast_to_topo(V1), *cast_to_topo(V2)))}};
}

topo_edge_t topo_edge_make_edge2d_from_curve(geom2d_curve_t *L) {
  return topo_edge_t{new topo_shape_t{std::make_shared<flywave::topo::edge>(
      flywave::topo::edge::make_edge2d(L->handle))}};
}

topo_edge_t topo_edge_make_edge2d_from_curve_p(geom2d_curve_t *L, double p1,
                                               double p2) {
  return topo_edge_t{new topo_shape_t{std::make_shared<flywave::topo::edge>(
      flywave::topo::edge::make_edge2d(L->handle, p1, p2))}};
}

topo_edge_t topo_edge_make_edge2d_from_curve_point(geom2d_curve_t *L,
                                                   pnt2d_t P1, pnt2d_t P2) {
  return topo_edge_t{new topo_shape_t{
      std::make_shared<flywave::topo::edge>(flywave::topo::edge::make_edge2d(
          L->handle, cast_to_gp(P1), cast_to_gp(P2)))}};
}

topo_edge_t topo_edge_make_edge2d_from_curve_vertex(geom2d_curve_t *L,
                                                    topo_vertex_t V1,
                                                    topo_vertex_t V2) {
  return topo_edge_t{new topo_shape_t{
      std::make_shared<flywave::topo::edge>(flywave::topo::edge::make_edge2d(
          L->handle, *cast_to_topo(V1), *cast_to_topo(V2)))}};
}

topo_edge_t topo_edge_make_edge2d_from_curve_point_p(geom2d_curve_t *L,
                                                     pnt2d_t P1, pnt2d_t P2,
                                                     double p1, double p2) {
  return topo_edge_t{new topo_shape_t{
      std::make_shared<flywave::topo::edge>(flywave::topo::edge::make_edge2d(
          L->handle, cast_to_gp(P1), cast_to_gp(P2), p1, p2))}};
}

topo_edge_t topo_edge_make_edge2d_from_curve_vertex_p(geom2d_curve_t *L,
                                                      topo_vertex_t V1,
                                                      topo_vertex_t V2,
                                                      double p1, double p2) {
  return topo_edge_t{new topo_shape_t{
      std::make_shared<flywave::topo::edge>(flywave::topo::edge::make_edge2d(
          L->handle, *cast_to_topo(V1), *cast_to_topo(V2), p1, p2))}};
}

topo_edge_t topo_edge_make_polygon() {
  return topo_edge_t{new topo_shape_t{std::make_shared<flywave::topo::edge>(
      flywave::topo::edge::make_polygon())}};
}

topo_edge_t topo_edge_make_polygon_from_two_point(pnt3d_t P1, pnt3d_t P2) {
  return topo_edge_t{new topo_shape_t{std::make_shared<flywave::topo::edge>(
      flywave::topo::edge::make_polygon(cast_to_gp(P1), cast_to_gp(P2)))}};
}

topo_edge_t topo_edge_make_polygon_from_three_point(pnt3d_t P1, pnt3d_t P2,
                                                    pnt3d_t P3, _Bool Close) {
  return topo_edge_t{new topo_shape_t{
      std::make_shared<flywave::topo::edge>(flywave::topo::edge::make_polygon(
          cast_to_gp(P1), cast_to_gp(P2), cast_to_gp(P3), Close))}};
}

topo_edge_t topo_edge_make_polygon_from_four_point(pnt3d_t P1, pnt3d_t P2,
                                                   pnt3d_t P3, pnt3d_t P4,
                                                   _Bool Close) {
  return topo_edge_t{new topo_shape_t{std::make_shared<flywave::topo::edge>(
      flywave::topo::edge::make_polygon(cast_to_gp(P1), cast_to_gp(P2),
                                        cast_to_gp(P3), cast_to_gp(P4),
                                        Close))}};
}

topo_edge_t topo_edge_make_polygon_from_two_vertex(topo_vertex_t V1,
                                                   topo_vertex_t V2) {
  return topo_edge_t{new topo_shape_t{
      std::make_shared<flywave::topo::edge>(flywave::topo::edge::make_polygon(
          *cast_to_topo(V1), *cast_to_topo(V2)))}};
}

topo_edge_t topo_edge_make_polygon_from_three_vertex(topo_vertex_t V1,
                                                     topo_vertex_t V2,
                                                     topo_vertex_t V3,
                                                     _Bool Close) {
  return topo_edge_t{new topo_shape_t{
      std::make_shared<flywave::topo::edge>(flywave::topo::edge::make_polygon(
          *cast_to_topo(V1), *cast_to_topo(V2), *cast_to_topo(V3), Close))}};
}

topo_edge_t topo_edge_make_polygon_from_four_vertex(topo_vertex_t V1,
                                                    topo_vertex_t V2,
                                                    topo_vertex_t V3,
                                                    topo_vertex_t V4,
                                                    _Bool Close) {
  return topo_edge_t{new topo_shape_t{std::make_shared<flywave::topo::edge>(
      flywave::topo::edge::make_polygon(*cast_to_topo(V1), *cast_to_topo(V2),
                                        *cast_to_topo(V3), *cast_to_topo(V4),
                                        Close))}};
}

topo_edge_t topo_edge_make_polygon_from_vertices(topo_vertex_t *vertices,
                                                 int vertcount, _Bool Close) {
  std::vector<flywave::topo::vertex *> oes;
  for (int i = 0; i < vertcount; i++) {
    oes.emplace_back(
        std::dynamic_pointer_cast<flywave::topo::vertex>(vertices[i].shp->shp)
            .get());
  }
  return topo_edge_t{new topo_shape_t{std::make_shared<flywave::topo::edge>(
      flywave::topo::edge::make_polygon(oes, Close))}};
}

topo_edge_t topo_edge_make_polygonn_from_points(pnt3d_t *vertexs, int vertcount,
                                                _Bool Close) {
  std::vector<gp_Pnt> oes;
  for (int i = 0; i < vertcount; i++) {
    oes.emplace_back(cast_to_gp(vertexs[i]));
  }
  return topo_edge_t{new topo_shape_t{std::make_shared<flywave::topo::edge>(
      flywave::topo::edge::make_polygon(oes, Close))}};
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
  return topo_face_t{new topo_shape_t{std::make_shared<flywave::topo::face>(
      flywave::topo::face::make_face(*cast_to_topo(F)))}};
}

topo_face_t topo_face_make_face_from_plane(plane_t P) {
  return topo_face_t{new topo_shape_t{std::make_shared<flywave::topo::face>(
      flywave::topo::face::make_face(cast_to_gp(P)))}};
}

topo_face_t topo_face_make_face_from_cylinder(cylinder_t C) {
  return topo_face_t{new topo_shape_t{std::make_shared<flywave::topo::face>(
      flywave::topo::face::make_face(cast_to_gp(C)))}};
}

topo_face_t topo_face_make_face_from_cone(cone_t C) {
  return topo_face_t{new topo_shape_t{std::make_shared<flywave::topo::face>(
      flywave::topo::face::make_face(cast_to_gp(C)))}};
}

topo_face_t topo_face_make_face_from_sphere(sphere_t S) {
  return topo_face_t{new topo_shape_t{std::make_shared<flywave::topo::face>(
      flywave::topo::face::make_face(cast_to_gp(S)))}};
}

topo_face_t topo_face_make_face_from_torus(torus_t C) {
  return topo_face_t{new topo_shape_t{std::make_shared<flywave::topo::face>(
      flywave::topo::face::make_face(cast_to_gp(C)))}};
}

topo_face_t topo_face_make_face_from_surface(geom_surface_t *S,
                                             double TolDegen) {
  return topo_face_t{new topo_shape_t{std::make_shared<flywave::topo::face>(
      flywave::topo::face::make_face(S->handle, TolDegen))}};
}

topo_face_t topo_face_make_face_from_plane_p(plane_t P, double UMin,
                                             double UMax, double VMin,
                                             double VMax) {
  return topo_face_t{new topo_shape_t{std::make_shared<flywave::topo::face>(
      flywave::topo::face::make_face(cast_to_gp(P), UMin, UMax, VMin, VMax))}};
}

topo_face_t topo_face_make_face_from_cylinder_p(cylinder_t C, double UMin,
                                                double UMax, double VMin,
                                                double VMax) {
  return topo_face_t{new topo_shape_t{std::make_shared<flywave::topo::face>(
      flywave::topo::face::make_face(cast_to_gp(C), UMin, UMax, VMin, VMax))}};
}

topo_face_t topo_face_make_face_from_cone_p(cone_t C, double UMin, double UMax,
                                            double VMin, double VMax) {
  return topo_face_t{new topo_shape_t{std::make_shared<flywave::topo::face>(
      flywave::topo::face::make_face(cast_to_gp(C), UMin, UMax, VMin, VMax))}};
}

topo_face_t topo_face_make_face_from_sphere_p(sphere_t S, double UMin,
                                              double UMax, double VMin,
                                              double VMax) {
  return topo_face_t{new topo_shape_t{std::make_shared<flywave::topo::face>(
      flywave::topo::face::make_face(cast_to_gp(S), UMin, UMax, VMin, VMax))}};
}

topo_face_t topo_face_make_face_from_torus_p(torus_t C, double UMin,
                                             double UMax, double VMin,
                                             double VMax) {
  return topo_face_t{new topo_shape_t{std::make_shared<flywave::topo::face>(
      flywave::topo::face::make_face(cast_to_gp(C), UMin, UMax, VMin, VMax))}};
}

topo_face_t topo_face_make_face_from_surface_p(geom_surface_t *S, double UMin,
                                               double UMax, double VMin,
                                               double VMax, double TolDegen) {
  return topo_face_t{new topo_shape_t{
      std::make_shared<flywave::topo::face>(flywave::topo::face::make_face(
          S->handle, UMin, UMax, VMin, VMax, TolDegen))}};
}

topo_face_t topo_face_make_face_from_wire_onlyplane(topo_wire_t W,
                                                    _Bool OnlyPlane) {
  return topo_face_t{new topo_shape_t{std::make_shared<flywave::topo::face>(
      flywave::topo::face::make_face(*cast_to_topo(W), OnlyPlane))}};
}

topo_face_t topo_face_make_face_from_plane_wire(plane_t P, topo_wire_t W,
                                                _Bool Inside) {
  return topo_face_t{new topo_shape_t{
      std::make_shared<flywave::topo::face>(flywave::topo::face::make_face(
          cast_to_gp(P), *cast_to_topo(W), Inside))}};
}

topo_face_t topo_face_make_face_from_cylinder_wire(cylinder_t C, topo_wire_t W,
                                                   _Bool Inside) {
  return topo_face_t{new topo_shape_t{
      std::make_shared<flywave::topo::face>(flywave::topo::face::make_face(
          cast_to_gp(C), *cast_to_topo(W), Inside))}};
}

topo_face_t topo_face_make_face_from_cone_wire(cone_t C, topo_wire_t W,
                                               _Bool Inside) {
  return topo_face_t{new topo_shape_t{
      std::make_shared<flywave::topo::face>(flywave::topo::face::make_face(
          cast_to_gp(C), *cast_to_topo(W), Inside))}};
}

topo_face_t topo_face_make_face_from_sphere_wire(sphere_t S, topo_wire_t W,
                                                 _Bool Inside) {
  return topo_face_t{new topo_shape_t{
      std::make_shared<flywave::topo::face>(flywave::topo::face::make_face(
          cast_to_gp(S), *cast_to_topo(W), Inside))}};
}

topo_face_t topo_face_make_face_from_torus_wire(torus_t C, topo_wire_t W,
                                                _Bool Inside) {
  return topo_face_t{new topo_shape_t{
      std::make_shared<flywave::topo::face>(flywave::topo::face::make_face(
          cast_to_gp(C), *cast_to_topo(W), Inside))}};
}

topo_face_t topo_face_make_face_from_surface_wire(geom_surface_t *S,
                                                  topo_wire_t W, _Bool Inside) {
  return topo_face_t{new topo_shape_t{std::make_shared<flywave::topo::face>(
      flywave::topo::face::make_face(S->handle, *cast_to_topo(W), Inside))}};
}

topo_face_t topo_face_make_face_from_face_wire(topo_face_t F, topo_wire_t W) {
  return topo_face_t{new topo_shape_t{std::make_shared<flywave::topo::face>(
      flywave::topo::face::make_face(*cast_to_topo(F), *cast_to_topo(W)))}};
}

topo_face_t topo_face_make_face_from_wire(topo_wire_t *wires, int count) {
  std::vector<flywave::topo::wire> ows;
  for (int i = 0; i < count; i++) {
    ows.emplace_back(*cast_to_topo(wires[i]));
  }
  return topo_face_t{new topo_shape_t{std::make_shared<flywave::topo::face>(
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
  return topo_face_t{new topo_shape_t{std::make_shared<flywave::topo::face>(
      flywave::topo::face::make_face(oes, ops))}};
}

topo_face_t topo_face_make_face_from_points(pnt3d_t *points, int count) {
  std::vector<gp_Pnt> ops;
  for (int i = 0; i < count; i++) {
    ops.emplace_back(cast_to_gp(points[i]));
  }
  return topo_face_t{new topo_shape_t{std::make_shared<flywave::topo::face>(
      flywave::topo::face::make_face(ops))}};
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
      std::vector<flywave::topo::shape *> prs;
      for (int i = 0; i < profilesCount; i++) {
        prs.emplace_back(profiles[i]->shp.get());
      }
      return opt->sweep(*cast_to_topo(spine), prs, cornerMode);
    }
  } catch (...) {
    return -1;
  }
}

int topo_face_sweep_wire(topo_face_t f, topo_wire_t spine,
                         topo_wire_t *profiles, int profilesCount,
                         int cornerMode) {
  try {
    auto opt = cast_to_topo(f);
    if (opt) {
      std::vector<flywave::topo::shape *> prs;
      for (int i = 0; i < profilesCount; i++) {
        prs.emplace_back(profiles[i].shp->shp.get());
      }
      return opt->sweep(*cast_to_topo(spine), prs, cornerMode);
    }
  } catch (...) {
    return -1;
  }
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
  return topo_shell_t{new topo_shape_t{std::make_shared<flywave::topo::shell>(
      flywave::topo::shell::make_shell(S->handle, Segment))}};
}

topo_shell_t topo_shell_make_shell_from_surface_p(geom_surface_t *S,
                                                  double UMin, double UMax,
                                                  double VMin, double VMax,
                                                  _Bool Segment) {
  return topo_shell_t{new topo_shape_t{
      std::make_shared<flywave::topo::shell>(flywave::topo::shell::make_shell(
          S->handle, UMin, UMax, VMin, VMax, Segment))}};
}

topo_shell_t topo_shell_make_shell_from_box(double dx, double dy, double dz) {
  return topo_shell_t{new topo_shape_t{std::make_shared<flywave::topo::shell>(
      flywave::topo::shell::make_shell_from_box(dx, dy, dz))}};
}

topo_shell_t topo_shell_make_shell_from_box_point(pnt3d_t P, double dx,
                                                  double dy, double dz) {
  return topo_shell_t{new topo_shape_t{std::make_shared<flywave::topo::shell>(
      flywave::topo::shell::make_shell_from_box(cast_to_gp(P), dx, dy, dz))}};
}

topo_shell_t topo_shell_make_shell_from_box_two_point(pnt3d_t P1, pnt3d_t P2) {
  return topo_shell_t{new topo_shape_t{std::make_shared<flywave::topo::shell>(
      flywave::topo::shell::make_shell_from_box(cast_to_gp(P1),
                                                cast_to_gp(P2)))}};
}

topo_shell_t topo_shell_make_shell_from_box_axis2(axis2_t Axes, double dx,
                                                  double dy, double dz) {
  return topo_shell_t{new topo_shape_t{std::make_shared<flywave::topo::shell>(
      flywave::topo::shell::make_shell_from_box(cast_to_gp(Axes), dx, dy,
                                                dz))}};
}

topo_shell_t topo_shell_make_shell_from_cylinder(double R, double H) {
  return topo_shell_t{new topo_shape_t{std::make_shared<flywave::topo::shell>(
      flywave::topo::shell::make_shell_from_cylinder(R, H))}};
}

topo_shell_t topo_shell_make_shell_from_cylinder_angle(double R, double H,
                                                       double Angle) {
  return topo_shell_t{new topo_shape_t{std::make_shared<flywave::topo::shell>(
      flywave::topo::shell::make_shell_from_cylinder(R, H, Angle))}};
}

topo_shell_t topo_shell_make_shell_from_cylinder_axis2(axis2_t Axes, double R,
                                                       double H) {
  return topo_shell_t{new topo_shape_t{std::make_shared<flywave::topo::shell>(
      flywave::topo::shell::make_shell_from_cylinder(cast_to_gp(Axes), R, H))}};
}

topo_shell_t topo_shell_make_shell_from_cylinder_axis2_angle(axis2_t Axes,
                                                             double R, double H,
                                                             double Angle) {
  return topo_shell_t{new topo_shape_t{std::make_shared<flywave::topo::shell>(
      flywave::topo::shell::make_shell_from_cylinder(cast_to_gp(Axes), R, H,
                                                     Angle))}};
}

topo_shell_t topo_shell_make_shell_from_cone(double R1, double R2, double H) {
  return topo_shell_t{new topo_shape_t{std::make_shared<flywave::topo::shell>(
      flywave::topo::shell::make_shell_from_cone(R1, R2, H))}};
}

topo_shell_t topo_shell_make_shell_from_cone_angle(double R1, double R2,
                                                   double H, double angle) {
  return topo_shell_t{new topo_shape_t{std::make_shared<flywave::topo::shell>(
      flywave::topo::shell::make_shell_from_cone(R1, R2, H, angle))}};
}

topo_shell_t topo_shell_make_shell_from_cone_axis2(axis2_t Axes, double R1,
                                                   double R2, double H) {
  return topo_shell_t{new topo_shape_t{std::make_shared<flywave::topo::shell>(
      flywave::topo::shell::make_shell_from_cone(cast_to_gp(Axes), R1, R2,
                                                 H))}};
}

topo_shell_t topo_shell_make_shell_from_cone_axis2_angle(axis2_t Axes,
                                                         double R1, double R2,
                                                         double H,
                                                         double angle) {
  return topo_shell_t{new topo_shape_t{std::make_shared<flywave::topo::shell>(
      flywave::topo::shell::make_shell_from_cone(cast_to_gp(Axes), R1, R2, H,
                                                 angle))}};
}

topo_shell_t topo_shell_make_shell_from_revolution(geom_curve_t *Meridian) {
  return topo_shell_t{new topo_shape_t{std::make_shared<flywave::topo::shell>(
      flywave::topo::shell::make_shell_from_revolution(Meridian->handle))}};
}

topo_shell_t topo_shell_make_shell_from_revolution_angle(geom_curve_t *Meridian,
                                                         double angle) {
  return topo_shell_t{new topo_shape_t{std::make_shared<flywave::topo::shell>(
      flywave::topo::shell::make_shell_from_revolution(Meridian->handle,
                                                       angle))}};
}

topo_shell_t topo_shell_make_shell_from_revolution_limit(geom_curve_t *Meridian,
                                                         double VMin,
                                                         double VMax) {
  return topo_shell_t{new topo_shape_t{std::make_shared<flywave::topo::shell>(
      flywave::topo::shell::make_shell_from_revolution(Meridian->handle, VMin,
                                                       VMax))}};
}

topo_shell_t topo_shell_make_shell_from_revolution_limit_angle(
    geom_curve_t *Meridian, double VMin, double VMax, double angle) {
  return topo_shell_t{new topo_shape_t{std::make_shared<flywave::topo::shell>(
      flywave::topo::shell::make_shell_from_revolution(Meridian->handle, VMin,
                                                       VMax, angle))}};
}

topo_shell_t
topo_shell_make_shell_from_revolution_axis2(axis2_t Axes,
                                            geom_curve_t *Meridian) {
  return topo_shell_t{new topo_shape_t{std::make_shared<flywave::topo::shell>(
      flywave::topo::shell::make_shell_from_revolution(cast_to_gp(Axes),
                                                       Meridian->handle))}};
}

topo_shell_t topo_shell_make_shell_from_revolution_axis2_angle(
    axis2_t Axes, geom_curve_t *Meridian, double angle) {
  return topo_shell_t{new topo_shape_t{std::make_shared<flywave::topo::shell>(
      flywave::topo::shell::make_shell_from_revolution(
          cast_to_gp(Axes), Meridian->handle, angle))}};
}

topo_shell_t topo_shell_make_shell_from_revolution_axis2_limit(
    axis2_t Axes, geom_curve_t *Meridian, double VMin, double VMax) {
  return topo_shell_t{new topo_shape_t{std::make_shared<flywave::topo::shell>(
      flywave::topo::shell::make_shell_from_revolution(
          cast_to_gp(Axes), Meridian->handle, VMin, VMax))}};
}

topo_shell_t topo_shell_make_shell_from_revolution_axis2_limit_angle(
    axis2_t Axes, geom_curve_t *Meridian, double VMin, double VMax,
    double angle) {
  return topo_shell_t{new topo_shape_t{std::make_shared<flywave::topo::shell>(
      flywave::topo::shell::make_shell_from_revolution(
          cast_to_gp(Axes), Meridian->handle, VMin, VMax, angle))}};
}

topo_shell_t topo_shell_make_shell_from_sphere(double R) {
  return topo_shell_t{new topo_shape_t{std::make_shared<flywave::topo::shell>(
      flywave::topo::shell::make_shell_from_sphere(R))}};
}

topo_shell_t topo_shell_make_shell_from_sphere_angle(double R, double angle) {
  return topo_shell_t{new topo_shape_t{std::make_shared<flywave::topo::shell>(
      flywave::topo::shell::make_shell_from_sphere(R, angle))}};
}

topo_shell_t topo_shell_make_shell_from_sphere_two_angle(double R,
                                                         double angle1,
                                                         double angle2) {
  return topo_shell_t{new topo_shape_t{std::make_shared<flywave::topo::shell>(
      flywave::topo::shell::make_shell_from_sphere(R, angle1, angle2))}};
}

topo_shell_t topo_shell_make_shell_from_sphere_three_angle(double R,
                                                           double angle1,
                                                           double angle2,
                                                           double angle3) {
  return topo_shell_t{new topo_shape_t{std::make_shared<flywave::topo::shell>(
      flywave::topo::shell::make_shell_from_sphere(R, angle1, angle2,
                                                   angle3))}};
}

topo_shell_t topo_shell_make_shell_from_sphere_center_raduis(pnt3d_t Center,
                                                             double R) {
  return topo_shell_t{new topo_shape_t{std::make_shared<flywave::topo::shell>(
      flywave::topo::shell::make_shell_from_sphere(cast_to_gp(Center), R))}};
}

topo_shell_t topo_shell_make_shell_from_sphere_center_angle(pnt3d_t Center,
                                                            double R,
                                                            double angle) {
  return topo_shell_t{new topo_shape_t{std::make_shared<flywave::topo::shell>(
      flywave::topo::shell::make_shell_from_sphere(cast_to_gp(Center), R,
                                                   angle))}};
}

topo_shell_t topo_shell_make_shell_from_sphere_center_two_angle(pnt3d_t Center,
                                                                double R,
                                                                double angle1,
                                                                double angle2) {
  return topo_shell_t{new topo_shape_t{std::make_shared<flywave::topo::shell>(
      flywave::topo::shell::make_shell_from_sphere(cast_to_gp(Center), R,
                                                   angle1, angle2))}};
}

topo_shell_t topo_shell_make_shell_from_sphere_center_three_angle(
    pnt3d_t Center, double R, double angle1, double angle2, double angle3) {
  return topo_shell_t{new topo_shape_t{std::make_shared<flywave::topo::shell>(
      flywave::topo::shell::make_shell_from_sphere(cast_to_gp(Center), R,
                                                   angle1, angle2, angle3))}};
}

topo_shell_t topo_shell_make_shell_from_sphere_axis2(axis2_t Axis, double R) {
  return topo_shell_t{new topo_shape_t{std::make_shared<flywave::topo::shell>(
      flywave::topo::shell::make_shell_from_sphere(cast_to_gp(Axis), R))}};
}

topo_shell_t topo_shell_make_shell_from_sphere_axis2_raduis(axis2_t Axis,
                                                            double R,
                                                            double angle) {
  return topo_shell_t{new topo_shape_t{std::make_shared<flywave::topo::shell>(
      flywave::topo::shell::make_shell_from_sphere(cast_to_gp(Axis), R,
                                                   angle))}};
}

topo_shell_t topo_shell_make_shell_from_sphere_axis2_two_angle(axis2_t Axis,
                                                               double R,
                                                               double angle1,
                                                               double angle2) {
  return topo_shell_t{new topo_shape_t{std::make_shared<flywave::topo::shell>(
      flywave::topo::shell::make_shell_from_sphere(cast_to_gp(Axis), R, angle1,
                                                   angle2))}};
}

topo_shell_t topo_shell_make_shell_from_sphere_axis2_three_angle(
    axis2_t Axis, double R, double angle1, double angle2, double angle3) {
  return topo_shell_t{new topo_shape_t{std::make_shared<flywave::topo::shell>(
      flywave::topo::shell::make_shell_from_sphere(cast_to_gp(Axis), R, angle1,
                                                   angle2, angle3))}};
}

topo_shell_t topo_shell_make_shell_from_torus(double R1, double R2) {
  return topo_shell_t{new topo_shape_t{std::make_shared<flywave::topo::shell>(
      flywave::topo::shell::make_shell_from_torus(R1, R2))}};
}

topo_shell_t topo_shell_make_shell_from_torus_angle(double R1, double R2,
                                                    double angle) {
  return topo_shell_t{new topo_shape_t{std::make_shared<flywave::topo::shell>(
      flywave::topo::shell::make_shell_from_torus(R1, R2, angle))}};
}

topo_shell_t topo_shell_make_shell_from_torus_two_angle(double R1, double R2,
                                                        double angle1,
                                                        double angle2) {
  return topo_shell_t{new topo_shape_t{std::make_shared<flywave::topo::shell>(
      flywave::topo::shell::make_shell_from_torus(R1, R2, angle1, angle2))}};
}

topo_shell_t topo_shell_make_shell_from_torus_three_angle(double R1, double R2,
                                                          double angle1,
                                                          double angle2,
                                                          double angle) {
  return topo_shell_t{new topo_shape_t{std::make_shared<flywave::topo::shell>(
      flywave::topo::shell::make_shell_from_torus(R1, R2, angle1, angle2,
                                                  angle))}};
}

topo_shell_t topo_shell_make_shell_from_torus_axis2(axis2_t Axes, double R1,
                                                    double R2) {
  return topo_shell_t{new topo_shape_t{std::make_shared<flywave::topo::shell>(
      flywave::topo::shell::make_shell_from_torus(cast_to_gp(Axes), R1, R2))}};
}

topo_shell_t topo_shell_make_shell_from_torus_axis2_angle(axis2_t Axes,
                                                          double R1, double R2,
                                                          double angle) {
  return topo_shell_t{new topo_shape_t{std::make_shared<flywave::topo::shell>(
      flywave::topo::shell::make_shell_from_torus(cast_to_gp(Axes), R1, R2,
                                                  angle))}};
}

topo_shell_t topo_shell_make_shell_from_torus_axis2_two_angle(
    axis2_t Axes, double R1, double R2, double angle1, double angle2) {
  return topo_shell_t{new topo_shape_t{std::make_shared<flywave::topo::shell>(
      flywave::topo::shell::make_shell_from_torus(cast_to_gp(Axes), R1, R2,
                                                  angle1, angle2))}};
}

topo_shell_t topo_shell_make_shell_from_torus_axis2_three_angle(
    axis2_t Axes, double R1, double R2, double angle1, double angle2,
    double angle) {
  return topo_shell_t{new topo_shape_t{std::make_shared<flywave::topo::shell>(
      flywave::topo::shell::make_shell_from_torus(cast_to_gp(Axes), R1, R2,
                                                  angle1, angle2, angle))}};
}

topo_shell_t topo_shell_make_shell_from_wedge(double dx, double dy, double dz,
                                              double ltx) {
  return topo_shell_t{new topo_shape_t{std::make_shared<flywave::topo::shell>(
      flywave::topo::shell::make_shell_from_wedge(dx, dy, dz, ltx))}};
}

topo_shell_t topo_shell_make_shell_from_wedge_axis2(axis2_t Axes, double dx,
                                                    double dy, double dz,
                                                    double ltx) {
  return topo_shell_t{new topo_shape_t{std::make_shared<flywave::topo::shell>(
      flywave::topo::shell::make_shell_from_wedge(cast_to_gp(Axes), dx, dy, dz,
                                                  ltx))}};
}

topo_shell_t topo_shell_make_shell_from_wedge_limit(double dx, double dy,
                                                    double dz, double xmin,
                                                    double zmin, double xmax,
                                                    double zmax) {
  return topo_shell_t{new topo_shape_t{std::make_shared<flywave::topo::shell>(
      flywave::topo::shell::make_shell_from_wedge(dx, dy, dz, xmin, zmin, xmax,
                                                  zmax))}};
}

topo_shell_t topo_shell_make_shell_from_wedge_axis2_limit(
    axis2_t Axes, double dx, double dy, double dz, double xmin, double zmin,
    double xmax, double zmax) {
  return topo_shell_t{new topo_shape_t{std::make_shared<flywave::topo::shell>(
      flywave::topo::shell::make_shell_from_wedge(cast_to_gp(Axes), dx, dy, dz,
                                                  xmin, zmin, xmax, zmax))}};
}

int topo_shell_sweep(topo_shell_t ss, topo_wire_t spine,
                     topo_shape_t **profiles, int count, int cornerMode) {
  try {
    auto opt = cast_to_topo(ss);
    if (opt) {
      std::vector<flywave::topo::shape *> pros;
      for (int i = 0; i < count; i++) {
        pros.emplace_back(profiles[i]->shp.get());
      }
      return opt->sweep(*cast_to_topo(spine), pros, cornerMode);
    }
  } catch (...) {
    return -1;
  }
}

int topo_shell_sweep_wire(topo_shell_t ss, topo_wire_t spine,
                          topo_wire_t *profiles, int count, int cornerMode) {
  try {
    auto opt = cast_to_topo(ss);
    if (opt) {
      std::vector<flywave::topo::shape *> pros;
      for (int i = 0; i < count; i++) {
        pros.emplace_back(profiles[i].shp->shp.get());
      }
      return opt->sweep(*cast_to_topo(spine), pros, cornerMode);
    }
  } catch (...) {
    return -1;
  }
}

void topo_solid_free(topo_solid_t t) {
  if (t.shp) {
    delete t.shp;
  }
}
topo_solid_t topo_solid_make_solid_from_comp_solid(topo_comp_solid_t S) {
  return topo_solid_t{new topo_shape_t{std::make_shared<flywave::topo::solid>(
      flywave::topo::solid::make_solid(*cast_to_topo(S)))}};
}

topo_solid_t topo_solid_make_solid_from_shell(topo_shell_t S) {
  return topo_solid_t{new topo_shape_t{std::make_shared<flywave::topo::solid>(
      flywave::topo::solid::make_solid(*cast_to_topo(S)))}};
}

topo_solid_t topo_solid_make_solid_from_two_shell(topo_shell_t S1,
                                                  topo_shell_t S2) {
  return topo_solid_t{new topo_shape_t{std::make_shared<flywave::topo::solid>(
      flywave::topo::solid::make_solid(*cast_to_topo(S1), *cast_to_topo(S2)))}};
}

topo_solid_t topo_solid_make_solid_from_three_shell(topo_shell_t S1,
                                                    topo_shell_t S2,
                                                    topo_shell_t S3) {
  return topo_solid_t{new topo_shape_t{
      std::make_shared<flywave::topo::solid>(flywave::topo::solid::make_solid(
          *cast_to_topo(S1), *cast_to_topo(S2), *cast_to_topo(S3)))}};
}

topo_solid_t topo_solid_make_solid_from_shells(topo_shell_t *shells,
                                               int count) {
  std::vector<flywave::topo::shell> shels;
  for (int i = 0; i < count; i++) {
    shels.emplace_back(*cast_to_topo(shells[i]));
  }
  return topo_solid_t{new topo_shape_t{std::make_shared<flywave::topo::solid>(
      flywave::topo::solid::make_solid(shels))}};
}

topo_solid_t topo_solid_make_solid_from_solid(topo_solid_t So) {
  return topo_solid_t{new topo_shape_t{std::make_shared<flywave::topo::solid>(
      flywave::topo::solid::make_solid(*cast_to_topo(So)))}};
}

topo_solid_t topo_solid_make_solid_from_solid_shell(topo_solid_t So,
                                                    topo_shell_t S) {
  return topo_solid_t{new topo_shape_t{std::make_shared<flywave::topo::solid>(
      flywave::topo::solid::make_solid(*cast_to_topo(So), *cast_to_topo(S)))}};
}

topo_solid_t topo_solid_make_solid_from_faces(topo_face_t *faces, int count,
                                              double tolerance) {
  std::vector<flywave::topo::face> cfaces;
  for (int i = 0; i < count; i++) {
    cfaces.emplace_back(*cast_to_topo(faces[i]));
  }
  return topo_solid_t{new topo_shape_t{std::make_shared<flywave::topo::solid>(
      flywave::topo::solid::make_solid(cfaces, tolerance))}};
}

topo_solid_t topo_solid_make_solid_from_box(double dx, double dy, double dz) {
  return topo_solid_t{new topo_shape_t{std::make_shared<flywave::topo::solid>(
      flywave::topo::solid::make_solid_from_box(dx, dy, dz))}};
}

topo_solid_t topo_solid_make_solid_from_box_point(pnt3d_t P, double dx,
                                                  double dy, double dz) {
  return topo_solid_t{new topo_shape_t{std::make_shared<flywave::topo::solid>(
      flywave::topo::solid::make_solid_from_box(cast_to_gp(P), dx, dy, dz))}};
}

topo_solid_t topo_solid_make_solid_from_box_two_point(pnt3d_t P1, pnt3d_t P2) {
  return topo_solid_t{new topo_shape_t{std::make_shared<flywave::topo::solid>(
      flywave::topo::solid::make_solid_from_box(cast_to_gp(P1),
                                                cast_to_gp(P2)))}};
}

topo_solid_t topo_solid_make_solid_from_box_axis2(axis2_t Axes, double dx,
                                                  double dy, double dz) {
  return topo_solid_t{new topo_shape_t{std::make_shared<flywave::topo::solid>(
      flywave::topo::solid::make_solid_from_box(cast_to_gp(Axes), dx, dy,
                                                dz))}};
}

topo_solid_t topo_solid_make_solid_from_cylinder(double R, double H) {
  return topo_solid_t{new topo_shape_t{std::make_shared<flywave::topo::solid>(
      flywave::topo::solid::make_solid_from_cylinder(R, H))}};
}

topo_solid_t topo_solid_make_solid_from_cylinder_angle(double R, double H,
                                                       double Angle) {
  return topo_solid_t{new topo_shape_t{std::make_shared<flywave::topo::solid>(
      flywave::topo::solid::make_solid_from_cylinder(R, H, Angle))}};
}

topo_solid_t topo_solid_make_solid_from_cylinder_axis2(axis2_t Axes, double R,
                                                       double H) {
  return topo_solid_t{new topo_shape_t{std::make_shared<flywave::topo::solid>(
      flywave::topo::solid::make_solid_from_cylinder(cast_to_gp(Axes), R, H))}};
}

topo_solid_t topo_solid_make_solid_from_cylinder_axis2_angle(axis2_t Axes,
                                                             double R, double H,
                                                             double Angle) {
  return topo_solid_t{new topo_shape_t{std::make_shared<flywave::topo::solid>(
      flywave::topo::solid::make_solid_from_cylinder(cast_to_gp(Axes), R, H,
                                                     Angle))}};
}

topo_solid_t topo_solid_make_solid_from_cone(double R1, double R2, double H) {
  return topo_solid_t{new topo_shape_t{std::make_shared<flywave::topo::solid>(
      flywave::topo::solid::make_solid_from_cone(R1, R2, H))}};
}

topo_solid_t topo_solid_make_solid_from_cone_angle(double R1, double R2,
                                                   double H, double angle) {
  return topo_solid_t{new topo_shape_t{std::make_shared<flywave::topo::solid>(
      flywave::topo::solid::make_solid_from_cone(R1, R2, H, angle))}};
}

topo_solid_t topo_solid_make_solid_from_cone_axis2(axis2_t Axes, double R1,
                                                   double R2, double H) {
  return topo_solid_t{new topo_shape_t{std::make_shared<flywave::topo::solid>(
      flywave::topo::solid::make_solid_from_cone(cast_to_gp(Axes), R1, R2,
                                                 H))}};
}

topo_solid_t topo_solid_make_solid_from_cone_axis2_angle(axis2_t Axes,
                                                         double R1, double R2,
                                                         double H,
                                                         double angle) {
  return topo_solid_t{new topo_shape_t{std::make_shared<flywave::topo::solid>(
      flywave::topo::solid::make_solid_from_cone(cast_to_gp(Axes), R1, R2, H,
                                                 angle))}};
}

topo_solid_t topo_solid_make_solid_from_revolution(geom_curve_t *Meridian) {
  return topo_solid_t{new topo_shape_t{std::make_shared<flywave::topo::solid>(
      flywave::topo::solid::make_solid_from_revolution(Meridian->handle))}};
}

topo_solid_t topo_solid_make_solid_from_revolution_angle(geom_curve_t *Meridian,
                                                         double angle) {
  return topo_solid_t{new topo_shape_t{std::make_shared<flywave::topo::solid>(
      flywave::topo::solid::make_solid_from_revolution(Meridian->handle,
                                                       angle))}};
}

topo_solid_t topo_solid_make_solid_from_revolution_limit(geom_curve_t *Meridian,
                                                         double VMin,
                                                         double VMax) {
  return topo_solid_t{new topo_shape_t{std::make_shared<flywave::topo::solid>(
      flywave::topo::solid::make_solid_from_revolution(Meridian->handle, VMin,
                                                       VMax))}};
}

topo_solid_t topo_solid_make_solid_from_revolution_limit_angle(
    geom_curve_t *Meridian, double VMin, double VMax, double angle) {
  return topo_solid_t{new topo_shape_t{std::make_shared<flywave::topo::solid>(
      flywave::topo::solid::make_solid_from_revolution(Meridian->handle, VMin,
                                                       VMax, angle))}};
}

topo_solid_t
topo_solid_make_solid_from_revolution_axis2(axis2_t Axes,
                                            geom_curve_t *Meridian) {
  return topo_solid_t{new topo_shape_t{std::make_shared<flywave::topo::solid>(
      flywave::topo::solid::make_solid_from_revolution(cast_to_gp(Axes),
                                                       Meridian->handle))}};
}

topo_solid_t topo_solid_make_solid_from_revolution_axis2_angle(
    axis2_t Axes, geom_curve_t *Meridian, double angle) {
  return topo_solid_t{new topo_shape_t{std::make_shared<flywave::topo::solid>(
      flywave::topo::solid::make_solid_from_revolution(
          cast_to_gp(Axes), Meridian->handle, angle))}};
}

topo_solid_t topo_solid_make_solid_from_revolution_axis2_limit(
    axis2_t Axes, geom_curve_t *Meridian, double VMin, double VMax) {
  return topo_solid_t{new topo_shape_t{std::make_shared<flywave::topo::solid>(
      flywave::topo::solid::make_solid_from_revolution(
          cast_to_gp(Axes), Meridian->handle, VMin, VMax))}};
}

topo_solid_t topo_solid_make_solid_from_revolution_axis2_limit_angle(
    axis2_t Axes, geom_curve_t *Meridian, double VMin, double VMax,
    double angle) {
  return topo_solid_t{new topo_shape_t{std::make_shared<flywave::topo::solid>(
      flywave::topo::solid::make_solid_from_revolution(
          cast_to_gp(Axes), Meridian->handle, VMin, VMax, angle))}};
}

topo_solid_t topo_solid_make_solid_from_sphere(double R) {
  return topo_solid_t{new topo_shape_t{std::make_shared<flywave::topo::solid>(
      flywave::topo::solid::make_solid_from_sphere(R))}};
}

topo_solid_t topo_solid_make_solid_from_sphere_angle(double R, double angle) {
  return topo_solid_t{new topo_shape_t{std::make_shared<flywave::topo::solid>(
      flywave::topo::solid::make_solid_from_sphere(R, angle))}};
}

topo_solid_t topo_solid_make_solid_from_sphere_two_angle(double R,
                                                         double angle1,
                                                         double angle2) {
  return topo_solid_t{new topo_shape_t{std::make_shared<flywave::topo::solid>(
      flywave::topo::solid::make_solid_from_sphere(R, angle1, angle2))}};
}

topo_solid_t topo_solid_make_solid_from_sphere_three_angle(double R,
                                                           double angle1,
                                                           double angle2,
                                                           double angle3) {
  return topo_solid_t{new topo_shape_t{std::make_shared<flywave::topo::solid>(
      flywave::topo::solid::make_solid_from_sphere(R, angle1, angle2,
                                                   angle3))}};
}

topo_solid_t topo_solid_make_solid_from_sphere_center_raduis(pnt3d_t Center,
                                                             double R) {
  return topo_solid_t{new topo_shape_t{std::make_shared<flywave::topo::solid>(
      flywave::topo::solid::make_solid_from_sphere(cast_to_gp(Center), R))}};
}

topo_solid_t topo_solid_make_solid_from_sphere_center_angle(pnt3d_t Center,
                                                            double R,
                                                            double angle) {
  return topo_solid_t{new topo_shape_t{std::make_shared<flywave::topo::solid>(
      flywave::topo::solid::make_solid_from_sphere(cast_to_gp(Center), R,
                                                   angle))}};
}

topo_solid_t topo_solid_make_solid_from_sphere_center_two_angle(pnt3d_t Center,
                                                                double R,
                                                                double angle1,
                                                                double angle2) {
  return topo_solid_t{new topo_shape_t{std::make_shared<flywave::topo::solid>(
      flywave::topo::solid::make_solid_from_sphere(cast_to_gp(Center), R,
                                                   angle1, angle2))}};
}

topo_solid_t topo_solid_make_solid_from_sphere_center_three_angle(
    pnt3d_t Center, double R, double angle1, double angle2, double angle3) {
  return topo_solid_t{new topo_shape_t{std::make_shared<flywave::topo::solid>(
      flywave::topo::solid::make_solid_from_sphere(cast_to_gp(Center), R,
                                                   angle1, angle2, angle3))}};
}

topo_solid_t topo_solid_make_solid_from_sphere_axis2(axis2_t Axis, double R) {
  return topo_solid_t{new topo_shape_t{std::make_shared<flywave::topo::solid>(
      flywave::topo::solid::make_solid_from_sphere(cast_to_gp(Axis), R))}};
}

topo_solid_t topo_solid_make_solid_from_sphere_axis2_angle(axis2_t Axis,
                                                           double R,
                                                           double angle) {
  return topo_solid_t{new topo_shape_t{std::make_shared<flywave::topo::solid>(
      flywave::topo::solid::make_solid_from_sphere(cast_to_gp(Axis), R,
                                                   angle))}};
}

topo_solid_t topo_solid_make_solid_from_sphere_axis2_two_angle(axis2_t Axis,
                                                               double R,
                                                               double angle1,
                                                               double angle2) {
  return topo_solid_t{new topo_shape_t{std::make_shared<flywave::topo::solid>(
      flywave::topo::solid::make_solid_from_sphere(cast_to_gp(Axis), R, angle1,
                                                   angle2))}};
}

topo_solid_t topo_solid_make_solid_from_sphere_axis2_three_angle(
    axis2_t Axis, double R, double angle1, double angle2, double angle3) {
  return topo_solid_t{new topo_shape_t{std::make_shared<flywave::topo::solid>(
      flywave::topo::solid::make_solid_from_sphere(cast_to_gp(Axis), R, angle1,
                                                   angle2, angle3))}};
}

topo_solid_t topo_solid_make_solid_from_torus(double R1, double R2) {
  return topo_solid_t{new topo_shape_t{std::make_shared<flywave::topo::solid>(
      flywave::topo::solid::make_solid_from_torus(R1, R2))}};
}

topo_solid_t topo_solid_make_solid_from_torus_angle(double R1, double R2,
                                                    double angle) {
  return topo_solid_t{new topo_shape_t{std::make_shared<flywave::topo::solid>(
      flywave::topo::solid::make_solid_from_torus(R1, R2, angle))}};
}

topo_solid_t topo_solid_make_solid_from_torus_two_angle(double R1, double R2,
                                                        double angle1,
                                                        double angle2) {
  return topo_solid_t{new topo_shape_t{std::make_shared<flywave::topo::solid>(
      flywave::topo::solid::make_solid_from_torus(R1, R2, angle1, angle2))}};
}

topo_solid_t topo_solid_make_solid_from_torus_three_angle(double R1, double R2,
                                                          double angle1,
                                                          double angle2,
                                                          double angle) {
  return topo_solid_t{new topo_shape_t{std::make_shared<flywave::topo::solid>(
      flywave::topo::solid::make_solid_from_torus(R1, R2, angle1, angle2,
                                                  angle))}};
}

topo_solid_t topo_solid_make_solid_from_torus_axis2(axis2_t Axes, double R1,
                                                    double R2) {
  return topo_solid_t{new topo_shape_t{std::make_shared<flywave::topo::solid>(
      flywave::topo::solid::make_solid_from_torus(cast_to_gp(Axes), R1, R2))}};
}

topo_solid_t topo_solid_make_solid_from_torus_axis2_angle(axis2_t Axes,
                                                          double R1, double R2,
                                                          double angle) {
  return topo_solid_t{new topo_shape_t{std::make_shared<flywave::topo::solid>(
      flywave::topo::solid::make_solid_from_torus(cast_to_gp(Axes), R1, R2,
                                                  angle))}};
}

topo_solid_t topo_solid_make_solid_from_torus_axis2_two_angle(
    axis2_t Axes, double R1, double R2, double angle1, double angle2) {
  return topo_solid_t{new topo_shape_t{std::make_shared<flywave::topo::solid>(
      flywave::topo::solid::make_solid_from_torus(cast_to_gp(Axes), R1, R2,
                                                  angle1, angle2))}};
}

topo_solid_t topo_solid_make_solid_from_torus_axis2_three_angle(
    axis2_t Axes, double R1, double R2, double angle1, double angle2,
    double angle) {
  return topo_solid_t{new topo_shape_t{std::make_shared<flywave::topo::solid>(
      flywave::topo::solid::make_solid_from_torus(cast_to_gp(Axes), R1, R2,
                                                  angle1, angle2, angle))}};
}

topo_solid_t topo_solid_make_solid_from_wedge(double dx, double dy, double dz,
                                              double ltx) {
  return topo_solid_t{new topo_shape_t{std::make_shared<flywave::topo::solid>(
      flywave::topo::solid::make_solid_from_wedge(dx, dy, dz, ltx))}};
}

topo_solid_t topo_solid_make_solid_from_wedge_axis2(axis2_t Axes, double dx,
                                                    double dy, double dz,
                                                    double ltx) {
  return topo_solid_t{new topo_shape_t{std::make_shared<flywave::topo::solid>(
      flywave::topo::solid::make_solid_from_wedge(cast_to_gp(Axes), dx, dy, dz,
                                                  ltx))}};
}

topo_solid_t topo_solid_make_solid_from_wedge_limit(double dx, double dy,
                                                    double dz, double xmin,
                                                    double zmin, double xmax,
                                                    double zmax) {
  return topo_solid_t{new topo_shape_t{std::make_shared<flywave::topo::solid>(
      flywave::topo::solid::make_solid_from_wedge(dx, dy, dz, xmin, zmin, xmax,
                                                  zmax))}};
}

topo_solid_t topo_solid_make_solid_from_wedge_axis2_limit(
    axis2_t Axes, double dx, double dy, double dz, double xmin, double zmin,
    double xmax, double zmax) {
  return topo_solid_t{new topo_shape_t{std::make_shared<flywave::topo::solid>(
      flywave::topo::solid::make_solid_from_wedge(cast_to_gp(Axes), dx, dy, dz,
                                                  xmin, zmin, xmax, zmax))}};
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
      return topo_face_t{new topo_shape_t{
          std::make_shared<flywave::topo::shape>(fopt->value())}};
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

topo_compound_t topo_make_compound() {
  return topo_compound_t{
      .shp =
          new topo_shape_t{.shp = std::make_shared<flywave::topo::compound>()}};
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
  return topo_compound_t{
      new topo_shape_t{std::make_shared<flywave::topo::compound>(
          flywave::topo::compound::make_compound(sps))}};
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
      new topo_shape_t{std::make_shared<flywave::topo::comp_solid>(
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
      std::unique_ptr<flywave::topo::mesh_receiver>(new go_mesh_receiver(cb))};
}

void topo_mesh_receiver_free(topo_mesh_receiver_t *p) {
  if (p) {
    delete p;
  }
}

topo_location_t *topo_location_new(trsf_t t) {
  return new topo_location_t{flywave::topo::topo_location{cast_to_gp(t)}};
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

void topo_shape_to_stl(topo_shape_t *p, char *str) {
  StlAPI_Writer writer = StlAPI_Writer();
  writer.Write(p->shp->value(), str);
}

topo_comp_solid_iterator_t *topo_comp_solid_iterator_make(topo_shape_t *shp) {
  return new topo_comp_solid_iterator_t{
      flywave::topo::comp_solid_iterator{*shp->shp}};
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
    return new topo_shape_t{std::make_shared<flywave::topo::comp_solid>(*opt)};
  }
  return nullptr;
}

topo_compound_iterator_t *topo_compound_iterator_make(topo_shape_t *shp) {
  return new topo_compound_iterator_t{
      flywave::topo::compound_iterator{*shp->shp}};
}

void topo_compound_iterator_reset(topo_compound_iterator_t *it) {
  it->iter.reset();
}

void topo_compound_iterator_free(topo_compound_iterator_t *it) { delete it; }

topo_shape_t *topo_compound_iterator_next(topo_compound_iterator_t *it) {
  boost::optional<flywave::topo::compound> opt = it->iter.next();
  if (opt) {
    return new topo_shape_t{std::make_shared<flywave::topo::compound>(*opt)};
  }
  return nullptr;
}

topo_edge_iterator_t *topo_edge_iterator_make(topo_shape_t *shp) {
  return new topo_edge_iterator_t{flywave::topo::edge_iterator{*shp->shp}};
}

void topo_edge_iterator_free(topo_edge_iterator_t *it) { delete it; }

void topo_edge_iterator_reset(topo_edge_iterator_t *it) { it->iter.reset(); }

topo_shape_t *topo_edge_iterator_next(topo_edge_iterator_t *it) {
  boost::optional<flywave::topo::edge> opt = it->iter.next();
  if (opt) {
    return new topo_shape_t{std::make_shared<flywave::topo::edge>(*opt)};
  }
  return nullptr;
}

topo_face_iterator_t *topo_face_iterator_make(topo_shape_t *shp) {
  return new topo_face_iterator_t{flywave::topo::face_iterator{*shp->shp}};
}

void topo_face_iterator_free(topo_face_iterator_t *it) { delete it; }

void topo_face_iterator_reset(topo_face_iterator_t *it) { it->iter.reset(); }

topo_shape_t *topo_face_iterator_next(topo_face_iterator_t *it) {
  boost::optional<flywave::topo::face> opt = it->iter.next();
  if (opt) {
    return new topo_shape_t{std::make_shared<flywave::topo::face>(*opt)};
  }
  return nullptr;
}

topo_shell_iterator_t *topo_shell_iterator_make(topo_shape_t *shp) {
  return new topo_shell_iterator_t{flywave::topo::shell_iterator{*shp->shp}};
}

void topo_shell_iterator_free(topo_shell_iterator_t *it) { delete it; }

void topo_shell_iterator_reset(topo_shell_iterator_t *it) { it->iter.reset(); }

topo_shape_t *topo_shell_iterator_next(topo_shell_iterator_t *it) {
  boost::optional<flywave::topo::shell> opt = it->iter.next();
  if (opt) {
    return new topo_shape_t{std::make_shared<flywave::topo::shell>(*opt)};
  }
  return nullptr;
}

topo_solid_iterator_t *topo_solid_iterator_make(topo_shape_t *shp) {
  return new topo_solid_iterator_t{flywave::topo::solid_iterator{*shp->shp}};
}

void topo_solid_iterator_free(topo_solid_iterator_t *it) { delete it; }

void topo_solid_iterator_reset(topo_solid_iterator_t *it) { it->iter.reset(); }

topo_shape_t *topo_solid_iterator_next(topo_solid_iterator_t *it) {
  boost::optional<flywave::topo::solid> opt = it->iter.next();
  if (opt) {
    return new topo_shape_t{std::make_shared<flywave::topo::solid>(*opt)};
  }
  return nullptr;
}

topo_vertex_iterator_t *topo_vertex_iterator_make(topo_shape_t *shp) {
  return new topo_vertex_iterator_t{flywave::topo::vertex_iterator{*shp->shp}};
}

void topo_vertex_iterator_free(topo_vertex_iterator_t *it) { delete it; }

void topo_vertex_iterator_reset(topo_vertex_iterator_t *it) {
  it->iter.reset();
}

topo_shape_t *topo_vertex_iterator_next(topo_vertex_iterator_t *it) {
  boost::optional<flywave::topo::vertex> opt = it->iter.next();
  if (opt) {
    return new topo_shape_t{std::make_shared<flywave::topo::vertex>(*opt)};
  }
  return nullptr;
}

topo_wire_iterator_t *topo_wire_iterator_make(topo_shape_t *shp) {
  return new topo_wire_iterator_t{flywave::topo::wire_iterator{*shp->shp}};
}

void topo_wire_iterator_free(topo_wire_iterator_t *it) { delete it; }

void topo_wire_iterator_reset(topo_wire_iterator_t *it) { it->iter.reset(); }

topo_shape_t *topo_wire_iterator_next(topo_wire_iterator_t *it) {
  boost::optional<flywave::topo::wire> opt = it->iter.next();
  if (opt) {
    return new topo_shape_t{std::make_shared<flywave::topo::wire>(*opt)};
  }
  return nullptr;
}

#ifdef __cplusplus
}
#endif
