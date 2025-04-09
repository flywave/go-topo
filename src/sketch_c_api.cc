#include "sketch_c_api.h"
#include "selector_impl.hh"
#include "sketch_impl.hh"
#include "topo_impl.hh"
#include "workplane_impl.hh"

namespace flywave {
namespace topo {

template <typename T>
void safe_call(std::shared_ptr<sketch> sk, const T &func) {
  if (sk->has_error()) {
    return *sk;
  }
  try {
    func();
  } catch (const std::exception &e) {
    sk->set_error(e.what());
  } catch (...) {
    sk->set_error("Unknown error occurred");
  }
}

} // namespace topo
} // namespace flywave

#ifdef __cplusplus
extern "C" {
#endif

sketch_val_t *sketch_val_create_from_shape(topo_shape_t *shape) {
  auto val = new sketch_val_t{flywave::topo::shape(*shape->shp)};
  return val;
}

sketch_val_t *sketch_val_create_from_location(topo_location_t *location) {
  auto val = new sketch_val_t{location->loc};
  return val;
}

void sketch_val_free(sketch_val_t *obj) {
  if (obj)
    delete obj;
}

bool sketch_val_is_shape(sketch_val_t *obj) {
  if (auto shape = boost::get<flywave::topo::shape>(&obj->val)) {
    return true;
  }
  return false;
}

bool sketch_val_is_location(sketch_val_t *obj) {
  if (auto loc = boost::get<flywave::topo::topo_location>(&obj->val)) {
    return true;
  }
  return false;
}

topo_shape_t *sketch_val_get_shape(sketch_val_t *obj) {
  if (auto shape = boost::get<flywave::topo::shape>(&obj->val)) {
    return new topo_shape_t{std::make_shared<flywave::topo::shape>(*shape)};
  }
  return nullptr;
}

topo_location_t *sketch_val_get_location(sketch_val_t *obj) {
  if (auto loc = boost::get<flywave::topo::topo_location>(&obj->val)) {
    return new topo_location_t{*loc};
  }
  return nullptr;
}

sketch_constraint_value_t *sketch_constraint_value_create_blank() {
  return new sketch_constraint_value_t{
      flywave::topo::sketch_constraint_value{boost::blank()}};
}

sketch_constraint_value_t *sketch_constraint_value_create_double(double val) {
  return new sketch_constraint_value_t{
      flywave::topo::sketch_constraint_value{val}};
}

sketch_constraint_value_t *
sketch_constraint_value_create_double3(double val1, double val2, double val3) {
  return new sketch_constraint_value_t{
      flywave::topo::sketch_constraint_value{std::make_tuple(
          boost::optional<double>(val1), boost::optional<double>(val2), val3)}};
}

sketch_constraint_value_t *sketch_constraint_value_create_double2(double val1,
                                                                  double val2) {
  return new sketch_constraint_value_t{
      flywave::topo::sketch_constraint_value{std::make_pair(val1, val2)}};
}

void sketch_constraint_value_free(sketch_constraint_value_t *obj) {
  if (obj) {
    delete obj;
  }
}

sketch_t *sketch_create_from_workplane(workplane_t *inPlane,
                                       topo_location_t *location,
                                       topo_compound_t *comp) {
  std::vector<flywave::topo::topo_location> locs;
  if (location)
    locs.push_back(location->loc);

  boost::optional<flywave::topo::compound> c;
  if (comp)
    c = *comp->shp->shp->cast<flywave::topo::compound>();

  auto sk = new sketch_t{
      std::make_shared<flywave::topo::sketch>(inPlane->ptr, locs, c)};
  return sk;
}

sketch_t *sketch_create_from_location(topo_location_t *location,
                                      topo_compound_t *comp) {
  std::vector<flywave::topo::topo_location> locs;
  if (location)
    locs.push_back(location->loc);

  boost::optional<flywave::topo::compound> c;
  if (comp)
    c = *comp->shp->shp->cast<flywave::topo::compound>();

  auto sk = new sketch_t{std::make_shared<flywave::topo::sketch>(locs, c)};
  return sk;
}

void sketch_free(sketch_t *obj) {
  if (obj)
    delete obj;
}

topo_face_t *sketch_get_faces(sketch_t *obj, int *size) {
  auto faces = obj->ptr->get_faces();
  *size = static_cast<int>(faces.size());
  auto result = new topo_face_t[faces.size()];
  for (size_t i = 0; i < faces.size(); i++) {
    result[i] = topo_face_t{new topo_shape_t{
        .shp = std::make_shared<flywave::topo::face>(faces[i])}};
  }
  return result;
}

#define SAFE_CALL(sk, expr) flywave::topo::safe_call((sk->ptr), [&]() { expr; })

void sketch_face_from_wire(sketch_t *sk, topo_wire_t *wire, double angle,
                           const char *tag) {
  SAFE_CALL(sk, sk->ptr->face(*wire->shp->shp, angle, flywave::topo::Mode::ADD,
                              tag ? tag : "", false));
}

void sketch_face_from_edges(sketch_t *sk, topo_edge_t **edges, int size,
                            double angle, const char *tag) {
  std::vector<flywave::topo::edge> edgesVec;
  for (int i = 0; i < size; i++) {
    edgesVec.push_back(*edges[i]->shp->shp->cast<flywave::topo::edge>());
  }
  SAFE_CALL(sk, sk->ptr->face(edgesVec, angle, flywave::topo::Mode::ADD,
                              tag ? tag : "", false));
}

void sketch_face_from_shape(sketch_t *sk, topo_shape_t *shape, double angle,
                            const char *tag) {
  SAFE_CALL(sk, sk->ptr->face(*shape->shp, angle, flywave::topo::Mode::ADD,
                              tag ? tag : "", false));
}

void sketch_face_from_sketch(sketch_t *sk, sketch_t *other, double angle,
                             const char *tag) {
  SAFE_CALL(sk, sk->ptr->face(other->ptr, angle, flywave::topo::Mode::ADD,
                              tag ? tag : "", false));
}

void sketch_rect(sketch_t *sk, double w, double h, double angle,
                 const char *tag) {
  SAFE_CALL(
      sk, sk->ptr->rect(w, h, angle, flywave::topo::Mode::ADD,
                        tag ? boost::optional<std::string>(tag) : boost::none));
}

void sketch_circle(sketch_t *sk, double r, const char *tag) {
  SAFE_CALL(sk, sk->ptr->circle(r, flywave::topo::Mode::ADD,
                                tag ? boost::optional<std::string>(tag)
                                    : boost::none));
}

void sketch_ellipse(sketch_t *sk, double a1, double a2, double angle,
                    const char *tag) {
  SAFE_CALL(sk, sk->ptr->ellipse(a1, a2, angle, flywave::topo::Mode::ADD,
                                 tag ? boost::optional<std::string>(tag)
                                     : boost::none));
}

void sketch_trapezoid(sketch_t *sk, double w, double h, double a1, double a2,
                      double angle, const char *tag) {
  SAFE_CALL(sk, sk->ptr->trapezoid(
                    w, h, a1, a2, angle, flywave::topo::Mode::ADD,
                    tag ? boost::optional<std::string>(tag) : boost::none));
}

void sketch_slot(sketch_t *sk, double w, double h, double angle,
                 const char *tag) {
  SAFE_CALL(
      sk, sk->ptr->slot(w, h, angle, flywave::topo::Mode::ADD,
                        tag ? boost::optional<std::string>(tag) : boost::none));
}

void sketch_regular_polygon(sketch_t *sk, double r, int n, double angle,
                            const char *tag) {
  SAFE_CALL(sk, sk->ptr->regular_polygon(r, n, angle, flywave::topo::Mode::ADD,
                                         tag ? boost::optional<std::string>(tag)
                                             : boost::none));
}

void sketch_polygon(sketch_t *sk, topo_vector_t **pts, int size, double angle,
                    const char *tag) {
  std::vector<flywave::topo::topo_vector> points;
  for (int i = 0; i < size; i++) {
    points.push_back(pts[i]->vec);
  }
  SAFE_CALL(sk, sk->ptr->polygon(points, angle, flywave::topo::Mode::ADD,
                                 tag ? boost::optional<std::string>(tag)
                                     : boost::none));
}

void sketch_rarray(sketch_t *sk, double xs, double ys, int nx, int ny,
                   double angle, const char *tag) {
  SAFE_CALL(sk, sk->ptr->rarray(xs, ys, nx, ny));
}

void sketch_parray(sketch_t *sk, double r, double a1, double da, int n,
                   bool rotate, double angle, const char *tag) {
  SAFE_CALL(sk, sk->ptr->parray(r, a1, da, n, rotate));
}

void sketch_each_for_face(sketch_t *sk, void *userdata,
                          topo_face_t (*func)(void *userdata,
                                              const topo_location_t *location),
                          int mode, const char *tag, bool ignore_selection) {
  auto _func =
      [&](const flywave::topo::topo_location &loc) -> flywave::topo::face {
    auto f = func(userdata, new topo_location_t{loc});
    return *f.shp->shp->cast<flywave::topo::face>();
  };

  SAFE_CALL(sk, sk->ptr->each(_func, static_cast<flywave::topo::Mode>(mode),
                              tag ? tag : "", ignore_selection));
}

void sketch_each_for_sketch(sketch_t *sk, void *userdata,
                            sketch_t *(*func)(void *userdata,
                                              const topo_location_t *location),
                            int mode, const char *tag, bool ignore_selection) {
  auto _func = [&](const flywave::topo::topo_location &loc)
      -> std::shared_ptr<flywave::topo::sketch> {
    auto s = func(userdata, new topo_location_t{loc});
    return s->ptr;
  };
  SAFE_CALL(sk, sk->ptr->each(_func, static_cast<flywave::topo::Mode>(mode),
                              tag ? tag : "", ignore_selection));
}

void sketch_each_for_compound(
    sketch_t *sk, void *userdata,
    topo_compound_t (*func)(void *userdata, const topo_location_t *location),
    int mode, const char *tag, bool ignore_selection) {
  auto _func =
      [&](const flywave::topo::topo_location &loc) -> flywave::topo::compound {
    auto c = func(userdata, new topo_location_t{loc});
    return *c.shp->shp->cast<flywave::topo::compound>();
  };
  SAFE_CALL(sk, sk->ptr->each(_func, static_cast<flywave::topo::Mode>(mode),
                              tag ? tag : "", ignore_selection));
}

void sketch_distribute(sketch_t *sk, int n, double start, double stop,
                       bool rotate, double angle, const char *tag) {
  SAFE_CALL(sk, sk->ptr->distribute(n, start, stop, rotate));
}

void sketch_push(sketch_t *sk, topo_location_t **locs, int size,
                 const char *tag) {
  std::vector<flywave::topo::topo_location> locations;
  for (int i = 0; i < size; i++) {
    locations.push_back(locs[i]->loc);
  }
  SAFE_CALL(sk, sk->ptr->push(locations, tag ? boost::optional<std::string>(tag)
                                             : boost::none));
}

void sketch_hull(sketch_t *sk, int mode, const char *tag) {
  SAFE_CALL(
      sk, sk->ptr->hull(static_cast<flywave::topo::Mode>(mode),
                        tag ? boost::optional<std::string>(tag) : boost::none));
}

void sketch_offset(sketch_t *sk, double d, int mode, const char *tag) {
  SAFE_CALL(sk, sk->ptr->offset(d, static_cast<flywave::topo::Mode>(mode),
                                tag ? boost::optional<std::string>(tag)
                                    : boost::none));
}

void sketch_fillet(sketch_t *sk, double d) {
  SAFE_CALL(sk, sk->ptr->fillet(d));
}

void sketch_chamfer(sketch_t *sk, double d) {
  SAFE_CALL(sk, sk->ptr->chamfer(d));
}

void sketch_clean(sketch_t *sk) { SAFE_CALL(sk, sk->ptr->clean()); }

void sketch_tag(sketch_t *sk, const char *tag) {
  SAFE_CALL(sk, sk->ptr->tag(tag ? tag : ""));
}

void sketch_select(sketch_t *sk, const char **tags, int size) {
  std::vector<std::string> tagVec;
  for (int i = 0; i < size; i++) {
    tagVec.push_back(tags[i] ? tags[i] : "");
  }
  SAFE_CALL(sk, sk->ptr->select(tagVec));
}

void sketch_faces(sketch_t *sk, const char *selector, const char *tag) {
  SAFE_CALL(sk, sk->ptr->faces(selector ? selector : "", tag ? tag : ""));
}

void sketch_faces_for_selector(sketch_t *sk, selector_t *selector,
                               const char *tag) {
  SAFE_CALL(sk, sk->ptr->faces(selector->ptr, tag ? tag : ""));
}

void sketch_wires(sketch_t *sk, const char *selector, const char *tag) {
  SAFE_CALL(sk, sk->ptr->wires(selector ? selector : "", tag ? tag : ""));
}

void sketch_wires_for_selector(sketch_t *sk, selector_t *selector,
                               const char *tag) {
  SAFE_CALL(sk, sk->ptr->wires(selector->ptr, tag ? tag : ""));
}

void sketch_edges(sketch_t *sk, const char *selector, const char *tag) {
  SAFE_CALL(sk, sk->ptr->edges(selector ? selector : "", tag ? tag : ""));
}

void sketch_edges_for_selector(sketch_t *sk, selector_t *selector,
                               const char *tag) {
  SAFE_CALL(sk, sk->ptr->edges(selector->ptr, tag ? tag : ""));
}

void sketch_vertices(sketch_t *sk, const char *selector, const char *tag) {
  SAFE_CALL(sk, sk->ptr->vertices(selector ? selector : "", tag ? tag : ""));
}

void sketch_vertices_for_selector(sketch_t *sk, selector_t *selector,
                                  const char *tag) {
  SAFE_CALL(sk, sk->ptr->vertices(selector->ptr, tag ? tag : ""));
}

void sketch_reset(sketch_t *sk) { SAFE_CALL(sk, sk->ptr->reset()); }

void sketch_delete_selected(sketch_t *sk) {
  SAFE_CALL(sk, sk->ptr->delete_selected());
}

void sketch_edge(sketch_t *sk, topo_edge_t *edge, const char *tag,
                 bool forConstruction) {
  SAFE_CALL(sk,
            sk->ptr->edge(*edge->shp->shp->cast<flywave::topo::edge>(),
                          tag ? boost::optional<std::string>(tag) : boost::none,
                          forConstruction));
}

void sketch_segment(sketch_t *sk, topo_vector_t *p1, topo_vector_t *p2,
                    const char *tag, bool forConstruction) {
  SAFE_CALL(sk, sk->ptr->segment(p1->vec, p2->vec,
                                 tag ? boost::optional<std::string>(tag)
                                     : boost::none,
                                 forConstruction));
}

void sketch_segment2(sketch_t *sk, topo_vector_t *p2, const char *tag,
                     bool forConstruction) {
  SAFE_CALL(sk, sk->ptr->segment(p2->vec,
                                 tag ? boost::optional<std::string>(tag)
                                     : boost::none,
                                 forConstruction));
}
void sketch_segment3(sketch_t *sk, double l, double a, const char *tag,
                     bool forConstruction) {
  SAFE_CALL(sk, sk->ptr->segment(
                    l, a, tag ? boost::optional<std::string>(tag) : boost::none,
                    forConstruction));
}

void sketch_arc(sketch_t *sk, topo_vector_t *p1, topo_vector_t *p2,
                topo_vector_t *p3, const char *tag, bool forConstruction) {
  SAFE_CALL(sk,
            sk->ptr->arc(p1->vec, p2->vec, p3->vec,
                         tag ? boost::optional<std::string>(tag) : boost::none,
                         forConstruction));
}
void sketch_arc2(sketch_t *sk, topo_vector_t *p2, topo_vector_t *p3,
                 const char *tag, bool forConstruction) {
  SAFE_CALL(sk,
            sk->ptr->arc(p2->vec, p3->vec,
                         tag ? boost::optional<std::string>(tag) : boost::none,
                         forConstruction));
}
void sketch_arc3(sketch_t *sk, topo_vector_t *center, double radius,
                 double start_angle, double delta_angle, const char *tag,
                 bool forConstruction) {
  SAFE_CALL(sk,
            sk->ptr->arc(center->vec, radius, start_angle, delta_angle,
                         tag ? boost::optional<std::string>(tag) : boost::none,
                         forConstruction));
}

void sketch_spline(sketch_t *sk, topo_vector_t **points, int size,
                   const char *tag, bool forConstruction) {
  std::vector<flywave::topo::topo_vector> pts;
  for (int i = 0; i < size; i++) {
    pts.push_back(points[i]->vec);
  }
  SAFE_CALL(sk, sk->ptr->spline(
                    pts, tag ? boost::optional<std::string>(tag) : boost::none,
                    forConstruction));
}

void sketch_spline2(sketch_t *sk, topo_vector_t **points, int size,
                    topo_vector_t *tangents1, topo_vector_t *tangents2,
                    bool periodic, const char *tag, bool forConstruction) {
  std::vector<flywave::topo::topo_vector> pts;
  for (int i = 0; i < size; i++) {
    pts.push_back(points[i]->vec);
  }
  boost::optional<
      std::pair<flywave::topo::topo_vector, flywave::topo::topo_vector>>
      tangents = boost::none;
  if (tangents1 && tangents2) {
    tangents =
        std::pair<flywave::topo::topo_vector, flywave::topo::topo_vector>(
            tangents1->vec, tangents2->vec);
  }
  SAFE_CALL(
      sk, sk->ptr->spline(pts, tangents, periodic,
                          tag ? boost::optional<std::string>(tag) : boost::none,
                          forConstruction));
}

void sketch_bezier(sketch_t *sk, topo_vector_t **points, int size,
                   const char *tag, bool forConstruction) {
  std::vector<flywave::topo::topo_vector> pts;
  for (int i = 0; i < size; i++) {
    pts.push_back(points[i]->vec);
  }
  SAFE_CALL(sk, sk->ptr->bezier(
                    pts, tag ? boost::optional<std::string>(tag) : boost::none,
                    forConstruction));
}

void sketch_close(sketch_t *sk, const char *tag) {
  SAFE_CALL(sk, sk->ptr->close(tag ? boost::optional<std::string>(tag)
                                   : boost::none));
}

void sketch_assemble(sketch_t *sk, int mode, const char *tag) {
  SAFE_CALL(sk, sk->ptr->assemble(static_cast<flywave::topo::Mode>(mode),
                                  tag ? boost::optional<std::string>(tag)
                                      : boost::none));
}

void sketch_constrain(sketch_t *sk, const char *tag, int constraint,
                      sketch_constraint_value_t *arg) {
  SAFE_CALL(sk,
            sk->ptr->constrain(
                tag ? tag : "",
                static_cast<flywave::topo::sketch_constraint_kind>(constraint),
                arg ? arg->val : flywave::topo::sketch_constraint_value()));
}

void sketch_constrain2(sketch_t *sk, const char *tag1, const char *tag2,
                       int constraint, sketch_constraint_value_t *arg) {
  SAFE_CALL(sk,
            sk->ptr->constrain(
                tag1 ? tag1 : "", tag2 ? tag2 : "",
                static_cast<flywave::topo::sketch_constraint_kind>(constraint),
                arg ? arg->val : flywave::topo::sketch_constraint_value()));
}

void sketch_solve(sketch_t *sk) { SAFE_CALL(sk, sk->ptr->solve()); }

sketch_t *sketch_copy(sketch_t *sk) { return new sketch_t{sk->ptr->copy()}; }

sketch_t *sketch_moved(sketch_t *sk, topo_location_t **locs, int size) {
  std::vector<flywave::topo::topo_location> locations;
  for (int i = 0; i < size; i++) {
    locations.push_back(locs[i]->loc);
  }
  return new sketch_t{sk->ptr->moved(locations)};
}

sketch_t *sketch_located(sketch_t *sk, topo_location_t *loc) {
  return new sketch_t{sk->ptr->located(loc->loc)};
}

workplane_t *sketch_finalize(sketch_t *sk) {
  return new workplane_t{sk->ptr->finalize()};
}

sketch_val_t *sketch_val(sketch_t *sk) {
  return new sketch_val_t{sk->ptr->val()};
}

sketch_val_t **sketch_vals(sketch_t *sk, int *size) {
  auto vals = sk->ptr->vals();
  *size = static_cast<int>(vals.size());
  auto result = new sketch_val_t *[vals.size()];
  for (size_t i = 0; i < vals.size(); i++) {
    result[i] = new sketch_val_t{vals[i]};
  }
  return result;
}

void sketch_add(sketch_t *sk) { SAFE_CALL(sk, sk->ptr->add()); }

void sketch_subtract(sketch_t *sk) { SAFE_CALL(sk, sk->ptr->subtract()); }

void sketch_replace(sketch_t *sk) { SAFE_CALL(sk, sk->ptr->replace()); }

void sketch_filter(sketch_t *sk, void *userdata,
                   bool (*pred)(void *userdata, sketch_val_t *)) {
  SAFE_CALL(sk, sk->ptr->filter([&](const flywave::topo::sketch_val &val) {
    return pred(userdata, new sketch_val_t{val});
  }));
}

void sketch_map(sketch_t *sk, void *userdata,
                sketch_val_t *(*f)(void *userdata, sketch_val_t *)) {
  SAFE_CALL(sk, sk->ptr->map([&](const flywave::topo::sketch_val &val) {
    auto v = f(userdata, new sketch_val_t{val});
    return v->val;
  }));
}

void sketch_apply(sketch_t *sk, void *userdata,
                  sketch_val_t **(*f)(void *userdata, sketch_val_t **, int)) {
  SAFE_CALL(sk, sk->ptr->apply(
                    [&](const std::vector<flywave::topo::sketch_val> &val) {
                      int count = static_cast<int>(val.size());
                      auto vals = new sketch_val_t *[count];
                      for (int i = 0; i < count; i++) {
                        vals[i] = new sketch_val_t{val[i]};
                      }
                      auto vecs = f(userdata, vals, count);
                      for (int i = 0; i < count; i++) {
                        delete vals[i];
                      }
                      delete[] vals;
                      std::vector<flywave::topo::sketch_val> ret;
                      for (int i = 0; i < count; i++) {
                        ret.push_back(vecs[i]->val);
                        delete vecs[i];
                      }
                      return ret;
                    }));
}

void sketch_sort(sketch_t *sk, void *userdata,
                 bool (*comp)(void *userdata, sketch_val_t *, sketch_val_t *)) {
  SAFE_CALL(sk, sk->ptr->sort([&](const flywave::topo::sketch_val &a,
                                  const flywave::topo::sketch_val &b) {
    return comp(userdata, new sketch_val_t{a}, new sketch_val_t{b});
  }));
}

bool sketch_has_error(sketch_t *sk) { return sk->ptr->has_error(); }

const char *sketch_error(sketch_t *sk) { return sk->ptr->error().c_str(); }

#ifdef __cplusplus
}
#endif
