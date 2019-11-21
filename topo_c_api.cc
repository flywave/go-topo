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
    p->shp->transform(cast_to_gp(mat));
  }
}

int topo_shape_translate(topo_shape_t *p, vec3d_t delta) {
  if (p) {
    p->shp->translate(cast_to_gp(delta));
  }
}

int topo_shape_rotate_from_two_point(topo_shape_t *p, double angle, pnt3d_t p1,
                                     pnt3d_t p2) {
  if (p) {
    p->shp->rotate(angle, cast_to_gp(p1), cast_to_gp(p2));
  }
}

int topo_shape_rotate_from_axis1(topo_shape_t *p, double angle, axis1_t a) {
  if (p) {
    p->shp->rotate(angle, cast_to_gp(a));
  }
}

int topo_shape_rotate_from_quaternion(topo_shape_t *p, quaternion_t q) {
  if (p) {
    p->shp->rotate(cast_to_gp(q));
  }
}

int topo_shape_scale(topo_shape_t *p, double angle, pnt3d_t a) {
  if (p) {
    p->shp->scale(cast_to_gp(a), angle);
  }
}

int topo_shape_mirror_from_point_norm(topo_shape_t *p, pnt3d_t pnt,
                                      pnt3d_t ner) {
  if (p) {
    p->shp->mirror(cast_to_gp(pnt), cast_to_gp(ner));
  }
}

int topo_shape_mirror_from_axis1(topo_shape_t *p, axis1_t a) {
  if (p) {
    p->shp->mirror(cast_to_gp(a));
  }
}

int topo_shape_mirror_from_axis2(topo_shape_t *p, axis2_t a) {
  if (p) {
    p->shp->mirror(cast_to_gp(a));
  }
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

void topo_shape_mesh(topo_shape_t *p, topo_mesh_receiver_t *receiver,
                     double tolerance, double deflection, double angle) {
  if (p) {
    p->shp->write_triangulation(*receiver->recv, tolerance, deflection, angle);
  }
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
    return cast_from_gp((gp_Pnt)(*opt));
  }
  return pnt3d_t{0., 0., 0.};
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
  std::vector<flywave::topo::edge> oes;
  for (int i = 0; i < count; i++) {
    oes.emplace_back(*cast_to_topo(edges[i]));
  }
  return topo_wire_t{new topo_shape_t{std::make_shared<flywave::topo::wire>(
      flywave::topo::wire::make_wire(oes))}};
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

void topo_edge_free(topo_edge_t t) {
  if (t.shp) {
    delete t.shp;
  }
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
  std::vector<flywave::topo::wire> ows;
  std::vector<flywave::topo::vertex> oes;
  for (int i = 0; i < vertcount; i++) {
    ows.emplace_back(*cast_to_topo(vertices[i]));
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

#ifdef __cplusplus
}
#endif
