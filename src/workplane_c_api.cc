#include "workplane_c_api.h"
#include "selector_impl.hh"
#include "sketch_impl.hh"
#include "topo_impl.hh"
#include "workplane_impl.hh"

#ifdef __cplusplus
extern "C" {
#endif

WORKPLANECAPICALL workplane_t *workplane_create() {
  return new workplane_t{std::make_shared<flywave::topo::workplane>()};
}

WORKPLANECAPICALL workplane_t *
workplane_create_from_plane(topo_plane_t *plane, topo_vector_t *origin) {
  return new workplane_t{
      std::make_shared<flywave::topo::workplane>(plane->plane, &origin->vec)};
}

WORKPLANECAPICALL workplane_t *
workplane_create_from_name(const char *planeName, topo_vector_t *origin) {
  return new workplane_t{
      std::make_shared<flywave::topo::workplane>(planeName, &origin->vec)};
}

WORKPLANECAPICALL void workplane_free(workplane_t *wp) {
  if (wp) {
    delete wp;
  }
}

WORKPLANECAPICALL topo_shape_t *workplane_value(workplane_t *wp) {
  return new topo_shape_t{
      std::make_shared<flywave::topo::shape>(wp->ptr->value())};
}

WORKPLANECAPICALL workplane_t *workplane_clean(workplane_t *wp) {
  return new workplane_t{wp->ptr->clean()};
}

WORKPLANECAPICALL workplane_t *workplane_workplane(workplane_t *wp,
                                                   double offset, bool invert,
                                                   int centerOption,
                                                   topo_vector_t *origin) {
  return new workplane_t{wp->ptr->create(
      offset, invert, static_cast<flywave::topo::center_option>(centerOption),
      origin ? &origin->vec : nullptr)};
}

WORKPLANECAPICALL void workplane_tag(workplane_t *wp, const char *name) {
  wp->ptr->tag(name);
}

WORKPLANECAPICALL workplane_t *workplane_split(workplane_t *wp, bool keepTop,
                                               bool keepBottom) {
  return new workplane_t{wp->ptr->split(keepTop, keepBottom)};
}

WORKPLANECAPICALL workplane_t *
workplane_split_with_shape(workplane_t *wp, topo_shape_t *splitter) {
  return new workplane_t{wp->ptr->split(*splitter->shp)};
}

WORKPLANECAPICALL workplane_t *
workplane_split_with_workplane(workplane_t *wp, workplane_t *splitter) {
  return new workplane_t{wp->ptr->split(*splitter->ptr)};
}

WORKPLANECAPICALL void workplane_add(workplane_t *wp, workplane_t *other) {
  wp->ptr->add(*other->ptr);
}

WORKPLANECAPICALL void workplane_add_shape(workplane_t *wp,
                                           shape_object_t *obj) {
  wp->ptr->add(obj->obj);
}

WORKPLANECAPICALL void workplane_add_shapes(workplane_t *wp,
                                            shape_object_t **objs, int size) {
  std::vector<flywave::topo::shape_object> objs_;
  for (int i = 0; i < size; ++i) {
    objs_.push_back(objs[i]->obj);
  }
  wp->ptr->add(objs_);
}

WORKPLANECAPICALL workplane_t *workplane_from_tagged(workplane_t *wp,
                                                     const char *tag) {
  return new workplane_t{wp->ptr->workplane_from_tagged(tag)};
}

WORKPLANECAPICALL topo_solid_t *
workplane_find_solid(workplane_t *wp, bool searchStack, bool searchParents) {
  return new topo_solid_t{
      new topo_shape_t{std::make_shared<flywave::topo::shape>(
          wp->ptr->find_solid(searchStack, searchParents))}};
}

WORKPLANECAPICALL workplane_t *
workplane_vertices(workplane_t *wp, const char *selector, const char *tag) {
  return new workplane_t{wp->ptr->vertices(selector, tag)};
}
WORKPLANECAPICALL workplane_t *
workplane_vertices_with_selector(workplane_t *wp, selector_t *sel,
                                 const char *tag) {
  return new workplane_t{wp->ptr->vertices(sel->ptr, tag)};
}

WORKPLANECAPICALL workplane_t *
workplane_faces(workplane_t *wp, const char *selector, const char *tag) {
  return new workplane_t{wp->ptr->faces(selector, tag)};
}
WORKPLANECAPICALL workplane_t *workplane_faces_with_selector(workplane_t *wp,
                                                             selector_t *sel,
                                                             const char *tag) {
  return new workplane_t{wp->ptr->faces(sel->ptr, tag)};
}

WORKPLANECAPICALL workplane_t *
workplane_edges(workplane_t *wp, const char *selector, const char *tag) {
  return new workplane_t{wp->ptr->edges(selector, tag)};
}
WORKPLANECAPICALL workplane_t *workplane_edges_with_selector(workplane_t *wp,
                                                             selector_t *sel,
                                                             const char *tag) {
  return new workplane_t{wp->ptr->edges(sel->ptr, tag)};
}

WORKPLANECAPICALL workplane_t *
workplane_wires(workplane_t *wp, const char *selector, const char *tag) {
  return new workplane_t{wp->ptr->wires(selector, tag)};
}

WORKPLANECAPICALL workplane_t *workplane_wires_with_selector(workplane_t *wp,
                                                             selector_t *sel,
                                                             const char *tag) {
  return new workplane_t{wp->ptr->wires(sel->ptr, tag)};
}

WORKPLANECAPICALL workplane_t *
workplane_solids(workplane_t *wp, const char *selector, const char *tag) {
  return new workplane_t{wp->ptr->solids(selector, tag)};
}

WORKPLANECAPICALL workplane_t *workplane_solids_with_selector(workplane_t *wp,
                                                              selector_t *sel,
                                                              const char *tag) {
  return new workplane_t{wp->ptr->solids(sel->ptr, tag)};
}

WORKPLANECAPICALL workplane_t *
workplane_shells(workplane_t *wp, const char *selector, const char *tag) {
  return new workplane_t{wp->ptr->shells(selector, tag)};
}

WORKPLANECAPICALL workplane_t *workplane_shells_with_selector(workplane_t *wp,
                                                              selector_t *sel,
                                                              const char *tag) {
  return new workplane_t{wp->ptr->shells(sel->ptr, tag)};
}

WORKPLANECAPICALL workplane_t *
workplane_compounds(workplane_t *wp, const char *selector, const char *tag) {
  return new workplane_t{wp->ptr->compounds(selector, tag)};
}

WORKPLANECAPICALL workplane_t *
workplane_compounds_with_selector(workplane_t *wp, selector_t *sel,
                                  const char *tag) {
  return new workplane_t{wp->ptr->compounds(sel->ptr, tag)};
}

WORKPLANECAPICALL workplane_t *workplane_ancestors(workplane_t *wp, int kind,
                                                   const char *tag) {
  return new workplane_t{wp->ptr->ancestors(
      static_cast<TopAbs_ShapeEnum>(kind),
      tag ? boost::optional<std::string>(tag) : boost::none)};
}

WORKPLANECAPICALL workplane_t *workplane_siblings(workplane_t *wp, int kind,
                                                  int level, const char *tag) {
  return new workplane_t{
      wp->ptr->siblings(static_cast<TopAbs_ShapeEnum>(kind), level,
                        tag ? boost::optional<std::string>(tag) : boost::none)};
}

WORKPLANECAPICALL workplane_t *
workplane_rotate_about_center(workplane_t *wp, topo_vector_t *axisEndPoint,
                              double angle) {
  return new workplane_t{
      wp->ptr->rotate_about_center(axisEndPoint->vec, angle)};
}

WORKPLANECAPICALL workplane_t *workplane_rotate(workplane_t *wp,
                                                topo_vector_t *axisStart,
                                                topo_vector_t *axisEnd,
                                                double angle) {
  return new workplane_t{wp->ptr->rotate(axisStart->vec, axisEnd->vec, angle)};
}

WORKPLANECAPICALL workplane_t *workplane_mirror(workplane_t *wp,
                                                const char *planeName,
                                                topo_vector_t *basePoint) {
  return new workplane_t{wp->ptr->mirror(planeName, basePoint->vec)};
}

WORKPLANECAPICALL workplane_t *
workplane_mirror_with_normal(workplane_t *wp, topo_vector_t *normal,
                             topo_vector_t *basePoint) {
  return new workplane_t{wp->ptr->mirror(normal->vec, basePoint->vec)};
}

WORKPLANECAPICALL workplane_t *
workplane_mirror_with_name(workplane_t *wp, const char *planeName,
                           topo_vector_t *basePoint, bool unionResult) {
  return new workplane_t{
      wp->ptr->mirror(planeName, basePoint->vec, unionResult)};
}

WORKPLANECAPICALL workplane_t *
workplane_mirror_with_face(workplane_t *wp, topo_face_t *mirrorFace,
                           topo_vector_t *basePoint, bool unionResult) {
  return new workplane_t{
      wp->ptr->mirror(*mirrorFace->shp->shp->cast<flywave::topo::face>(),
                      basePoint->vec, unionResult)};
}

WORKPLANECAPICALL workplane_t *workplane_translate(workplane_t *wp,
                                                   topo_vector_t *vec) {
  return new workplane_t{wp->ptr->translate(vec->vec)};
}

WORKPLANECAPICALL workplane_t *
workplane_shell(workplane_t *wp, double thickness, const char *kind) {
  return new workplane_t{wp->ptr->shell(thickness, kind)};
}

WORKPLANECAPICALL workplane_t *workplane_fillet(workplane_t *wp,
                                                double radius) {
  return new workplane_t{wp->ptr->fillet(radius)};
}

WORKPLANECAPICALL workplane_t *workplane_chamfer(workplane_t *wp, double length,
                                                 double length2) {
  return new workplane_t{wp->ptr->chamfer(length, length2)};
}

WORKPLANECAPICALL workplane_t *workplane_transformed(workplane_t *wp,
                                                     topo_vector_t *rotate,
                                                     topo_vector_t *offset) {
  return new workplane_t{wp->ptr->transformed(rotate->vec, offset->vec)};
}

WORKPLANECAPICALL workplane_t *
workplane_rarray(workplane_t *wp, double xSpacing, double ySpacing, int xCount,
                 int yCount, bool centerX, bool centerY) {
  return new workplane_t{wp->ptr->rarray(xSpacing, ySpacing, xCount, yCount,
                                         std::make_pair(centerX, centerY))};
}

WORKPLANECAPICALL workplane_t *
workplane_polar_array(workplane_t *wp, double radius, double startAngle,
                      double angle, int count, bool fill, bool rotate) {
  return new workplane_t{
      wp->ptr->polar_array(radius, startAngle, angle, count, fill, rotate)};
}

WORKPLANECAPICALL workplane_t *
workplane_push_points(workplane_t *wp, topo_location_t **locs, int size) {
  std::vector<flywave::topo::topo_location> locs_;
  for (int i = 0; i < size; ++i) {
    locs_.push_back(locs[i]->loc);
  }
  return new workplane_t{wp->ptr->push_points(locs_)};
}

WORKPLANECAPICALL workplane_t *
workplane_push_points_with_vector(workplane_t *wp, topo_vector_t **vecs,
                                  int size) {
  std::vector<flywave::topo::topo_vector> vecs_;
  for (int i = 0; i < size; ++i) {
    vecs_.push_back(vecs[i]->vec);
  }
  return new workplane_t{wp->ptr->push_points(vecs_)};
}

WORKPLANECAPICALL workplane_t *workplane_center(workplane_t *wp, double x,
                                                double y) {
  return new workplane_t{wp->ptr->center(x, y)};
}

WORKPLANECAPICALL workplane_t *
workplane_line_to(workplane_t *wp, double x, double y, bool forConstruction) {
  return new workplane_t{wp->ptr->line_to(x, y, forConstruction)};
}

WORKPLANECAPICALL workplane_t *
workplane_bezier(workplane_t *wp, topo_vector_t **points, int size,
                 bool forConstruction, bool includeCurrent, bool makeWire) {
  std::vector<flywave::topo::topo_vector> points_;
  for (int i = 0; i < size; ++i) {
    points_.push_back(points[i]->vec);
  }
  return new workplane_t{
      wp->ptr->bezier(points_, forConstruction, includeCurrent, makeWire)};
}

WORKPLANECAPICALL workplane_t *workplane_line(workplane_t *wp, double xDist,
                                              double yDist,
                                              bool forConstruction) {
  return new workplane_t{wp->ptr->line(xDist, yDist, forConstruction)};
}

WORKPLANECAPICALL workplane_t *workplane_vline(workplane_t *wp, double distance,
                                               bool forConstruction) {
  return new workplane_t{wp->ptr->vline(distance, forConstruction)};
}

WORKPLANECAPICALL workplane_t *workplane_hline(workplane_t *wp, double distance,
                                               bool forConstruction) {
  return new workplane_t{wp->ptr->hline(distance, forConstruction)};
}

WORKPLANECAPICALL workplane_t *
workplane_vline_to(workplane_t *wp, double yCoord, bool forConstruction) {
  return new workplane_t{wp->ptr->vline_to(yCoord, forConstruction)};
}

WORKPLANECAPICALL workplane_t *
workplane_hline_to(workplane_t *wp, double xCoord, bool forConstruction) {
  return new workplane_t{wp->ptr->hline_to(xCoord, forConstruction)};
}

WORKPLANECAPICALL workplane_t *workplane_polar_line(workplane_t *wp,
                                                    double distance,
                                                    double angle,
                                                    bool forConstruction) {
  return new workplane_t{wp->ptr->polar_line(distance, angle, forConstruction)};
}

WORKPLANECAPICALL workplane_t *workplane_polar_line_to(workplane_t *wp,
                                                       double distance,
                                                       double angle,
                                                       bool forConstruction) {
  return new workplane_t{
      wp->ptr->polar_line_to(distance, angle, forConstruction)};
}

WORKPLANECAPICALL workplane_t *workplane_move_to(workplane_t *wp, double x,
                                                 double y) {
  return new workplane_t{wp->ptr->move_to(x, y)};
}

WORKPLANECAPICALL workplane_t *workplane_move(workplane_t *wp, double xDist,
                                              double yDist) {
  return new workplane_t{wp->ptr->move(xDist, yDist)};
}

WORKPLANECAPICALL workplane_t *workplane_slot2d(workplane_t *wp, double length,
                                                double diameter, double angle) {
  return new workplane_t{wp->ptr->slot2d(length, diameter, angle)};
}

#ifdef __cplusplus
}
#endif
