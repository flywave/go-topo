#include "workplane_c_api.h"
#include "selector_impl.hh"
#include "sketch_impl.hh"
#include "topo_impl.hh"
#include "workplane_impl.hh"

#ifdef __cplusplus
extern "C" {
#endif

workplane_t *workplane_create() {
  return new workplane_t{std::make_shared<flywave::topo::workplane>()};
}

workplane_t *workplane_create_from_plane(topo_plane_t *plane,
                                         topo_vector_t *origin) {
  return new workplane_t{
      std::make_shared<flywave::topo::workplane>(plane->plane, &origin->vec)};
}

workplane_t *workplane_create_from_name(const char *planeName,
                                        topo_vector_t *origin) {
  return new workplane_t{
      std::make_shared<flywave::topo::workplane>(planeName, &origin->vec)};
}

void workplane_free(workplane_t *wp) {
  if (wp) {
    delete wp;
  }
}

topo_shape_t *workplane_value(workplane_t *wp) {
  return new topo_shape_t{
      std::make_shared<flywave::topo::shape>(wp->ptr->value())};
}

workplane_t *workplane_clean(workplane_t *wp) {
  return new workplane_t{wp->ptr->clean()};
}

workplane_t *workplane_workplane(workplane_t *wp, double offset, bool invert,
                                 int centerOption, topo_vector_t *origin) {
  return new workplane_t{wp->ptr->create(
      offset, invert, static_cast<flywave::topo::center_option>(centerOption),
      origin ? &origin->vec : nullptr)};
}

void workplane_tag(workplane_t *wp, const char *name) { wp->ptr->tag(name); }

workplane_t *workplane_split(workplane_t *wp, bool keepTop, bool keepBottom) {
  return new workplane_t{wp->ptr->split(keepTop, keepBottom)};
}

workplane_t *workplane_split_with_shape(workplane_t *wp,
                                        topo_shape_t *splitter) {
  return new workplane_t{wp->ptr->split(*splitter->shp)};
}

workplane_t *workplane_split_with_workplane(workplane_t *wp,
                                            workplane_t *splitter) {
  return new workplane_t{wp->ptr->split(*splitter->ptr)};
}

void workplane_add(workplane_t *wp, workplane_t *other) {
  wp->ptr->add(*other->ptr);
}

void workplane_add_shape(workplane_t *wp, shape_object_t *obj) {
  wp->ptr->add(obj->obj);
}

void workplane_add_shapes(workplane_t *wp, shape_object_t **objs, int size) {
  std::vector<flywave::topo::shape_object> objs_;
  for (int i = 0; i < size; ++i) {
    objs_.push_back(objs[i]->obj);
  }
  wp->ptr->add(objs_);
}

workplane_t *workplane_from_tagged(workplane_t *wp, const char *tag) {
  return new workplane_t{wp->ptr->from_tagged(tag)};
}

topo_solid_t *workplane_find_solid(workplane_t *wp, bool searchStack,
                                   bool searchParents) {
  return new topo_solid_t{
      new topo_shape_t{std::make_shared<flywave::topo::shape>(
          wp->ptr->find_solid(searchStack, searchParents))}};
}

workplane_t *workplane_vertices(workplane_t *wp, const char *selector,
                                const char *tag) {
  return new workplane_t{wp->ptr->vertices(selector, tag)};
}
workplane_t *workplane_vertices_with_selector(workplane_t *wp, selector_t *sel,
                                              const char *tag) {
  return new workplane_t{wp->ptr->vertices(sel->ptr, tag)};
}

workplane_t *workplane_faces(workplane_t *wp, const char *selector,
                             const char *tag) {
  return new workplane_t{wp->ptr->faces(selector, tag)};
}
workplane_t *workplane_faces_with_selector(workplane_t *wp, selector_t *sel,
                                           const char *tag) {
  return new workplane_t{wp->ptr->faces(sel->ptr, tag)};
}

workplane_t *workplane_edges(workplane_t *wp, const char *selector,
                             const char *tag) {
  return new workplane_t{wp->ptr->edges(selector, tag)};
}
workplane_t *workplane_edges_with_selector(workplane_t *wp, selector_t *sel,
                                           const char *tag) {
  return new workplane_t{wp->ptr->edges(sel->ptr, tag)};
}

workplane_t *workplane_wires(workplane_t *wp, const char *selector,
                             const char *tag) {
  return new workplane_t{wp->ptr->wires(selector, tag)};
}

workplane_t *workplane_wires_with_selector(workplane_t *wp, selector_t *sel,
                                           const char *tag) {
  return new workplane_t{wp->ptr->wires(sel->ptr, tag)};
}

workplane_t *workplane_solids(workplane_t *wp, const char *selector,
                              const char *tag) {
  return new workplane_t{wp->ptr->solids(selector, tag)};
}

workplane_t *workplane_solids_with_selector(workplane_t *wp, selector_t *sel,
                                            const char *tag) {
  return new workplane_t{wp->ptr->solids(sel->ptr, tag)};
}

workplane_t *workplane_shells(workplane_t *wp, const char *selector,
                              const char *tag) {
  return new workplane_t{wp->ptr->shells(selector, tag)};
}

workplane_t *workplane_shells_with_selector(workplane_t *wp, selector_t *sel,
                                            const char *tag) {
  return new workplane_t{wp->ptr->shells(sel->ptr, tag)};
}

workplane_t *workplane_compounds(workplane_t *wp, const char *selector,
                                 const char *tag) {
  return new workplane_t{wp->ptr->compounds(selector, tag)};
}

workplane_t *workplane_compounds_with_selector(workplane_t *wp, selector_t *sel,
                                               const char *tag) {
  return new workplane_t{wp->ptr->compounds(sel->ptr, tag)};
}

workplane_t *workplane_ancestors(workplane_t *wp, int kind, const char *tag) {
  return new workplane_t{wp->ptr->ancestors(
      static_cast<TopAbs_ShapeEnum>(kind),
      tag ? boost::optional<std::string>(tag) : boost::none)};
}

workplane_t *workplane_siblings(workplane_t *wp, int kind, int level,
                                const char *tag) {
  return new workplane_t{
      wp->ptr->siblings(static_cast<TopAbs_ShapeEnum>(kind), level,
                        tag ? boost::optional<std::string>(tag) : boost::none)};
}

workplane_t *workplane_rotate_about_center(workplane_t *wp,
                                           topo_vector_t *axisEndPoint,
                                           double angle) {
  return new workplane_t{
      wp->ptr->rotate_about_center(axisEndPoint->vec, angle)};
}

workplane_t *workplane_rotate(workplane_t *wp, topo_vector_t *axisStart,
                              topo_vector_t *axisEnd, double angle) {
  return new workplane_t{wp->ptr->rotate(axisStart->vec, axisEnd->vec, angle)};
}

workplane_t *workplane_mirror(workplane_t *wp, const char *planeName,
                              topo_vector_t *basePoint) {
  return new workplane_t{wp->ptr->mirror(planeName, basePoint->vec)};
}

workplane_t *workplane_mirror_with_normal(workplane_t *wp,
                                          topo_vector_t *normal,
                                          topo_vector_t *basePoint) {
  return new workplane_t{wp->ptr->mirror(normal->vec, basePoint->vec)};
}

workplane_t *workplane_mirror_with_name(workplane_t *wp, const char *planeName,
                                        topo_vector_t *basePoint,
                                        bool unionResult) {
  return new workplane_t{
      wp->ptr->mirror(planeName, basePoint->vec, unionResult)};
}

workplane_t *workplane_mirror_with_face(workplane_t *wp,
                                        topo_face_t *mirrorFace,
                                        topo_vector_t *basePoint,
                                        bool unionResult) {
  return new workplane_t{
      wp->ptr->mirror(*mirrorFace->shp->shp->cast<flywave::topo::face>(),
                      basePoint->vec, unionResult)};
}

workplane_t *workplane_translate(workplane_t *wp, topo_vector_t *vec) {
  return new workplane_t{wp->ptr->translate(vec->vec)};
}

workplane_t *workplane_shell(workplane_t *wp, double thickness,
                             const char *kind) {
  return new workplane_t{wp->ptr->shell(thickness, kind)};
}

workplane_t *workplane_fillet(workplane_t *wp, double radius) {
  return new workplane_t{wp->ptr->fillet(radius)};
}

workplane_t *workplane_chamfer(workplane_t *wp, double length, double length2) {
  return new workplane_t{wp->ptr->chamfer(length, length2)};
}

workplane_t *workplane_transformed(workplane_t *wp, topo_vector_t *rotate,
                                   topo_vector_t *offset) {
  return new workplane_t{wp->ptr->transformed(rotate->vec, offset->vec)};
}

workplane_t *workplane_rarray(workplane_t *wp, double xSpacing, double ySpacing,
                              int xCount, int yCount, bool centerX,
                              bool centerY) {
  return new workplane_t{wp->ptr->rarray(xSpacing, ySpacing, xCount, yCount,
                                         std::make_pair(centerX, centerY))};
}

workplane_t *workplane_polar_array(workplane_t *wp, double radius,
                                   double startAngle, double angle, int count,
                                   bool fill, bool rotate) {
  return new workplane_t{
      wp->ptr->polar_array(radius, startAngle, angle, count, fill, rotate)};
}

workplane_t *workplane_push_points(workplane_t *wp, topo_location_t **locs,
                                   int size) {
  std::vector<flywave::topo::topo_location> locs_;
  for (int i = 0; i < size; ++i) {
    locs_.push_back(locs[i]->loc);
  }
  return new workplane_t{wp->ptr->push_points(locs_)};
}

workplane_t *workplane_push_points_with_vector(workplane_t *wp,
                                               topo_vector_t **vecs, int size) {
  std::vector<flywave::topo::topo_vector> vecs_;
  for (int i = 0; i < size; ++i) {
    vecs_.push_back(vecs[i]->vec);
  }
  return new workplane_t{wp->ptr->push_points(vecs_)};
}

workplane_t *workplane_center(workplane_t *wp, double x, double y) {
  return new workplane_t{wp->ptr->center(x, y)};
}

workplane_t *workplane_line_to(workplane_t *wp, double x, double y,
                               bool forConstruction) {
  return new workplane_t{wp->ptr->line_to(x, y, forConstruction)};
}

workplane_t *workplane_bezier(workplane_t *wp, topo_vector_t **points, int size,
                              bool forConstruction, bool includeCurrent,
                              bool makeWire) {
  std::vector<flywave::topo::topo_vector> points_;
  for (int i = 0; i < size; ++i) {
    points_.push_back(points[i]->vec);
  }
  return new workplane_t{
      wp->ptr->bezier(points_, forConstruction, includeCurrent, makeWire)};
}

workplane_t *workplane_line(workplane_t *wp, double xDist, double yDist,
                            bool forConstruction) {
  return new workplane_t{wp->ptr->line(xDist, yDist, forConstruction)};
}

workplane_t *workplane_vline(workplane_t *wp, double distance,
                             bool forConstruction) {
  return new workplane_t{wp->ptr->vline(distance, forConstruction)};
}

workplane_t *workplane_hline(workplane_t *wp, double distance,
                             bool forConstruction) {
  return new workplane_t{wp->ptr->hline(distance, forConstruction)};
}

workplane_t *workplane_vline_to(workplane_t *wp, double yCoord,
                                bool forConstruction) {
  return new workplane_t{wp->ptr->vline_to(yCoord, forConstruction)};
}

workplane_t *workplane_hline_to(workplane_t *wp, double xCoord,
                                bool forConstruction) {
  return new workplane_t{wp->ptr->hline_to(xCoord, forConstruction)};
}

workplane_t *workplane_polar_line(workplane_t *wp, double distance,
                                  double angle, bool forConstruction) {
  return new workplane_t{wp->ptr->polar_line(distance, angle, forConstruction)};
}

workplane_t *workplane_polar_line_to(workplane_t *wp, double distance,
                                     double angle, bool forConstruction) {
  return new workplane_t{
      wp->ptr->polar_line_to(distance, angle, forConstruction)};
}

workplane_t *workplane_move_to(workplane_t *wp, double x, double y) {
  return new workplane_t{wp->ptr->move_to(x, y)};
}

workplane_t *workplane_move(workplane_t *wp, double xDist, double yDist) {
  return new workplane_t{wp->ptr->move(xDist, yDist)};
}

workplane_t *workplane_slot2d(workplane_t *wp, double length, double diameter,
                              double angle) {
  return new workplane_t{wp->ptr->slot2d(length, diameter, angle)};
}

workplane_t *workplane_spline(workplane_t *wp, topo_vector_t **points, int size,
                              bool periodic, topo_vector_t **tangents,
                              int size2, bool scale, double tol,
                              bool forConstruction, bool includeCurrent,
                              bool makeWire) {
  std::vector<gp_Pnt> pts;
  for (int i = 0; i < size; i++) {
    pts.push_back(
        gp_Pnt(points[i]->vec.x(), points[i]->vec.y(), points[i]->vec.z()));
  }

  boost::optional<std::vector<gp_Vec>> tans;
  if (tangents && size2 > 0) {
    std::vector<gp_Vec> tanVecs;
    for (int i = 0; i < size2; i++) {
      tanVecs.push_back(gp_Vec(tangents[i]->vec.x(), tangents[i]->vec.y(),
                               tangents[i]->vec.z()));
    }
    tans = tanVecs;
  }

  auto result = wp->ptr->spline(pts, tans, periodic, boost::none, scale, tol,
                                forConstruction, includeCurrent, makeWire);
  return new workplane_t{result};
}

workplane_t *workplane_spline_approx(workplane_t *wp, topo_vector_t **points,
                                     int size, double tol, int minDeg,
                                     int maxDeg, topo_vector_t *smoothing,
                                     bool forConstruction, bool includeCurrent,
                                     bool makeWire) {
  std::vector<gp_Pnt> pts;
  for (int i = 0; i < size; i++) {
    pts.push_back(
        gp_Pnt(points[i]->vec.x(), points[i]->vec.y(), points[i]->vec.z()));
  }

  boost::optional<std::tuple<double, double, double>> smooth;
  if (smoothing) {
    smooth = std::make_tuple(smoothing->vec.x(), smoothing->vec.y(),
                             smoothing->vec.z());
  }

  auto result =
      wp->ptr->spline_approx(pts, tol, minDeg, maxDeg, smooth, forConstruction,
                             includeCurrent, makeWire);
  return new workplane_t{result};
}

workplane_t *workplane_parametric_curve(workplane_t *wp,
                                        pnt3d_t (*func)(double), int N,
                                        double start, double stop, double tol,
                                        int minDeg, int maxDeg,
                                        topo_vector_t *smoothing,
                                        bool makeWire) {
  auto wrapper = [func](double t) {
    pnt3d_t p = func(t);
    return gp_Pnt(p.x, p.y, p.z);
  };

  std::tuple<double, double, double> smooth(
      smoothing->vec.x(), smoothing->vec.y(), smoothing->vec.z());

  auto result = wp->ptr->parametric_curve(wrapper, N, start, stop, tol, minDeg,
                                          maxDeg, smooth, makeWire);
  return new workplane_t{result};
}

workplane_t *workplane_parametric_surface(workplane_t *wp,
                                          pnt3d_t (*func)(double, double),
                                          int N, double start, double stop,
                                          double tol, int minDeg, int maxDeg,
                                          topo_vector_t *smoothing) {
  auto wrapper = [func](double u, double v) {
    pnt3d_t p = func(u, v);
    return gp_Pnt(p.x, p.y, p.z);
  };

  std::tuple<double, double, double> smooth(
      smoothing->vec.x(), smoothing->vec.y(), smoothing->vec.z());

  auto result = wp->ptr->parametric_surface(wrapper, N, start, stop, tol,
                                            minDeg, maxDeg, smooth);
  return new workplane_t{result};
}

workplane_t *workplane_ellipse_arc(workplane_t *wp, double x_radius,
                                   double y_radius, double angle1,
                                   double angle2, double rotation_angle,
                                   int sense, bool forConstruction,
                                   bool startAtCurrent, bool makeWire) {
  auto result =
      wp->ptr->ellipse_arc(x_radius, y_radius, angle1, angle2, rotation_angle,
                           sense, forConstruction, startAtCurrent, makeWire);
  return new workplane_t{result};
}

workplane_t *workplane_three_point_arc(workplane_t *wp, topo_vector_t *point1,
                                       topo_vector_t *point2,
                                       bool forConstruction) {
  gp_Pnt p1(point1->vec.x(), point1->vec.y(), point1->vec.z());
  gp_Pnt p2(point2->vec.x(), point2->vec.y(), point2->vec.z());

  auto result = wp->ptr->three_point_arc(p1, p2, forConstruction);
  return new workplane_t{result};
}

workplane_t *workplane_sagitta_arc(workplane_t *wp, topo_vector_t *endPoint,
                                   double sag, bool forConstruction) {
  gp_Pnt ep(endPoint->vec.x(), endPoint->vec.y(), endPoint->vec.z());
  auto result = wp->ptr->sagitta_arc(ep, sag, forConstruction);
  return new workplane_t{result};
}

workplane_t *workplane_radius_arc(workplane_t *wp, topo_vector_t *endPoint,
                                  double radius, bool forConstruction) {
  gp_Pnt ep(endPoint->vec.x(), endPoint->vec.y(), endPoint->vec.z());
  auto result = wp->ptr->radius_arc(ep, radius, forConstruction);
  return new workplane_t{result};
}

workplane_t *workplane_tangent_arc_point(workplane_t *wp,
                                         topo_vector_t *endpoint,
                                         bool forConstruction, bool relative) {
  gp_Pnt ep(endpoint->vec.x(), endpoint->vec.y(), endpoint->vec.z());
  auto result = wp->ptr->tangent_arc_point(ep, forConstruction, relative);
  return new workplane_t{result};
}

workplane_t *workplane_mirror_y(workplane_t *wp) {
  auto result = wp->ptr->mirror_y();
  return new workplane_t{result};
}

workplane_t *workplane_mirror_x(workplane_t *wp) {
  auto result = wp->ptr->mirror_x();
  return new workplane_t{result};
}

workplane_t *workplane_consolidate_wires(workplane_t *wp) {
  auto result = wp->ptr->consolidate_wires();
  return new workplane_t{result};
}

workplane_t *workplane_each(workplane_t *wp, void (*func)(shape_object_t *),
                            bool useLocalCoordinates, bool combine,
                            bool clean) {
  auto wrapper =
      [func](flywave::topo::shape_object &obj) -> flywave::topo::shape_object {
    shape_object_t sobj{obj};
    func(&sobj);
    return sobj.obj;
  };

  auto result = wp->ptr->each(wrapper, useLocalCoordinates, combine, clean);
  return new workplane_t{result};
}

workplane_t *workplane_eachpoint(workplane_t *wp,
                                 void (*func)(shape_object_t *),
                                 bool useLocalCoordinates, bool combine,
                                 bool clean) {
  auto wrapper =
      [func](flywave::topo::topo_location loc) -> flywave::topo::shape {
    shape_object_t sobj{loc};
    func(&sobj);
    return boost::get<flywave::topo::shape>(sobj.obj);
  };

  auto result =
      wp->ptr->eachpoint(wrapper, useLocalCoordinates, combine, clean);
  return new workplane_t{result};
}

workplane_t *workplane_eachpoint_with_shape(workplane_t *wp,
                                            topo_shape_t *shapeObj,
                                            bool useLocalCoordinates,
                                            bool combine, bool clean) {
  auto result =
      wp->ptr->eachpoint(*shapeObj->shp, useLocalCoordinates, combine, clean);
  return new workplane_t{result};
}

workplane_t *workplane_eachpoint_with_workplane(workplane_t *wp,
                                                workplane_t *wp2,
                                                bool useLocalCoordinates,
                                                bool combine, bool clean) {
  auto result =
      wp->ptr->eachpoint(*wp2->ptr, useLocalCoordinates, combine, clean);
  return new workplane_t{result};
}

workplane_t *workplane_eachpoint_with_location(
    workplane_t *wp, topo_shape_t *(*func)(topo_location_t *loc),
    bool useLocalCoordinates, bool combine, bool clean) {
  auto wrapper = [func](const flywave::topo::topo_location &p) {
    topo_location_t loc{.loc = p};
    return *func(&loc)->shp;
  };
  auto result =
      wp->ptr->eachpoint(wrapper, useLocalCoordinates, combine, clean);
  return new workplane_t{result};
}

workplane_t *workplane_rect(workplane_t *wp, double xLen, double yLen,
                            bool centerX, bool centerY, bool forConstruction) {
  auto result = wp->ptr->rect(xLen, yLen, std::make_pair(centerX, centerY),
                              forConstruction);
  return new workplane_t{result};
}

workplane_t *workplane_rect_all(workplane_t *wp, double xLen, double yLen,
                                bool centerAll, bool forConstruction) {
  auto result = wp->ptr->rect(xLen, yLen, centerAll, forConstruction);
  return new workplane_t{result};
}

workplane_t *workplane_circle(workplane_t *wp, double radius,
                              bool forConstruction) {
  auto result = wp->ptr->circle(radius, forConstruction);
  return new workplane_t{result};
}

workplane_t *workplane_ellipse(workplane_t *wp, double x_radius,
                               double y_radius, double rotation_angle,
                               bool forConstruction) {
  auto result =
      wp->ptr->ellipse(x_radius, y_radius, rotation_angle, forConstruction);
  return new workplane_t{result};
}

workplane_t *workplane_polygon(workplane_t *wp, int nSides, double diameter,
                               bool forConstruction, bool circumscribed) {
  auto result =
      wp->ptr->polygon(nSides, diameter, forConstruction, circumscribed);
  return new workplane_t{result};
}

workplane_t *workplane_polyline(workplane_t *wp, topo_vector_t **points,
                                int size, bool forConstruction,
                                bool includeCurrent) {
  std::vector<gp_Pnt> pts;
  for (int i = 0; i < size; i++) {
    pts.push_back(
        gp_Pnt(points[i]->vec.x(), points[i]->vec.y(), points[i]->vec.z()));
  }
  auto result = wp->ptr->polyline(pts, forConstruction, includeCurrent);
  return new workplane_t{result};
}

workplane_t *workplane_close(workplane_t *wp) {
  auto result = wp->ptr->close();
  return new workplane_t{result};
}

double workplane_largest_dimension(workplane_t *wp) {
  auto result = wp->ptr->largest_dimension();
  return result;
}

workplane_t *workplane_cut_each(workplane_t *wp,
                                topo_shape_t *(*fcn)(topo_location_t *loc),
                                bool useLocalCoordinates, bool clean) {
  auto wrapper = [fcn](flywave::topo::topo_location loc) {
    topo_location_t loc_ = {.loc = loc};
    return *fcn(&loc_)->shp;
  };
  auto result = wp->ptr->cut_each(wrapper, useLocalCoordinates, clean);
  return new workplane_t{result};
}

workplane_t *workplane_cbore_hole(workplane_t *wp, double diameter,
                                  double cboreDiameter, double cboreDepth,
                                  double depth, bool clean) {
  auto result =
      wp->ptr->cbore_hole(diameter, cboreDiameter, cboreDepth, depth, clean);
  return new workplane_t{result};
}

workplane_t *workplane_csk_hole(workplane_t *wp, double diameter,
                                double cskDiameter, double cskAngle,
                                double depth, bool clean) {
  auto result =
      wp->ptr->csk_hole(diameter, cskDiameter, cskAngle, depth, clean);
  return new workplane_t{result};
}

workplane_t *workplane_hole(workplane_t *wp, double diameter, double depth,
                            bool clean) {
  auto result = wp->ptr->hole(diameter, depth, clean);
  return new workplane_t{result};
}

workplane_t *workplane_twist_extrude(workplane_t *wp, double distance,
                                     double angleDegrees, bool combine,
                                     bool clean) {
  auto result = wp->ptr->twist_extrude(distance, angleDegrees, combine, clean);
  return new workplane_t{result};
}

workplane_t *workplane_extrude(workplane_t *wp, double distance, bool combine,
                               bool clean, bool both, double *taper) {
  auto result =
      wp->ptr->extrude(distance, combine, clean, both,
                       taper ? boost::optional<double>(*taper) : boost::none);
  return new workplane_t{result};
}

workplane_t *workplane_extrude_with_face_type(workplane_t *wp, int index_type,
                                              bool combine, bool clean,
                                              bool both, double *taper) {
  auto result =
      wp->ptr->extrude(index_type, combine, clean, both,
                       taper ? boost::optional<double>(*taper) : boost::none);
  return new workplane_t{result};
}

workplane_t *workplane_extrude_with_face(workplane_t *wp, topo_face_t *face,
                                         bool combine, bool clean, bool both,
                                         double *taper) {
  auto result = wp->ptr->extrude(
      *face->shp->shp->cast<flywave::topo::face>(), combine, clean, both,
      taper ? boost::optional<double>(*taper) : boost::none);
  return new workplane_t{result};
}

workplane_t *workplane_sweep(workplane_t *wp, workplane_t *path,
                             bool multisection, bool makeSolid, bool isFrenet,
                             bool combine, bool clean, int transition,
                             topo_vector_t *normal, workplane_t *auxSpine) {
  auto result = wp->ptr->sweep(
      *path->ptr, multisection, makeSolid, isFrenet, combine, clean,
      static_cast<flywave::topo::transition_mode>(transition),
      normal ? boost::make_optional(normal->vec) : boost::none,
      auxSpine ? boost::make_optional(*auxSpine->ptr) : boost::none);
  return new workplane_t{result};
}

workplane_t *workplane_sweep_with_wire(workplane_t *wp, topo_wire_t *path,
                                       bool multisection, bool makeSolid,
                                       bool isFrenet, bool combine, bool clean,
                                       int transition, topo_vector_t *normal,
                                       workplane_t *auxSpine) {
  auto result = wp->ptr->sweep(
      *path->shp->shp->cast<flywave::topo::wire>(), multisection, makeSolid,
      isFrenet, combine, clean,
      static_cast<flywave::topo::transition_mode>(transition),
      normal ? boost::make_optional(normal->vec) : boost::none,
      auxSpine ? boost::make_optional(*auxSpine->ptr) : boost::none);
  return new workplane_t{result};
}

workplane_t *workplane_sweep_with_edge(workplane_t *wp, topo_edge_t *path,
                                       bool multisection, bool makeSolid,
                                       bool isFrenet, bool combine, bool clean,
                                       int transition, topo_vector_t *normal,
                                       workplane_t *auxSpine) {
  auto result = wp->ptr->sweep(
      *path->shp->shp->cast<flywave::topo::edge>(), multisection, makeSolid,
      isFrenet, combine, clean,
      static_cast<flywave::topo::transition_mode>(transition),
      normal ? boost::make_optional(normal->vec) : boost::none,
      auxSpine ? boost::make_optional(*auxSpine->ptr) : boost::none);
  return new workplane_t{result};
}

workplane_t *workplane_union(workplane_t *wp, workplane_t *other, bool clean,
                             bool glue, double tol) {
  auto result = wp->ptr->union_(*other->ptr, clean, glue, tol);
  return new workplane_t{result};
}

workplane_t *workplane_union_with_solid(workplane_t *wp, topo_solid_t *other,
                                        bool clean, bool glue, double tol) {
  auto result = wp->ptr->union_(*other->shp->shp->cast<flywave::topo::solid>(),
                                clean, glue, tol);
  return new workplane_t{result};
}

workplane_t *workplane_union_with_compound(workplane_t *wp,
                                           topo_compound_t *other, bool clean,
                                           bool glue, double tol) {
  auto result = wp->ptr->union_(
      *other->shp->shp->cast<flywave::topo::compound>(), clean, glue, tol);
  return new workplane_t{result};
}

workplane_t *workplane_cut(workplane_t *wp, workplane_t *other, bool clean,
                           double tol) {
  auto result = wp->ptr->cut(*other->ptr, clean, tol);
  return new workplane_t{result};
}

workplane_t *workplane_cut_with_solid(workplane_t *wp, topo_solid_t *other,
                                      bool clean, double tol) {
  auto result =
      wp->ptr->cut(*other->shp->shp->cast<flywave::topo::solid>(), clean, tol);
  return new workplane_t{result};
}

workplane_t *workplane_cut_with_compound(workplane_t *wp,
                                         topo_compound_t *other, bool clean,
                                         double tol) {
  auto result = wp->ptr->cut(*other->shp->shp->cast<flywave::topo::compound>(),
                             clean, tol);
  return new workplane_t{result};
}

workplane_t *workplane_intersect(workplane_t *wp, workplane_t *other,
                                 bool clean, double tol) {
  auto result = wp->ptr->intersect(*other->ptr, clean, tol);
  return new workplane_t{result};
}

workplane_t *workplane_intersect_with_solid(workplane_t *wp,
                                            topo_solid_t *other, bool clean,
                                            double tol) {
  auto result = wp->ptr->intersect(
      *other->shp->shp->cast<flywave::topo::solid>(), clean, tol);
  return new workplane_t{result};
}

workplane_t *workplane_intersect_with_compound(workplane_t *wp,
                                               topo_compound_t *other,
                                               bool clean, double tol) {
  auto result = wp->ptr->intersect(
      *other->shp->shp->cast<flywave::topo::compound>(), clean, tol);
  return new workplane_t{result};
}

workplane_t *workplane_cut_blind(workplane_t *wp, double distance, bool clean,
                                 bool both, double taper) {
  auto result = wp->ptr->cut_blind(distance, clean, both, taper);
  return new workplane_t{result};
}

workplane_t *workplane_cut_blind_with_until_face(workplane_t *wp, int untilFace,
                                                 bool clean, bool both,
                                                 double taper) {
  auto result =
      wp->ptr->cut_blind(static_cast<flywave::topo::face_index_type>(untilFace),
                         clean, both, taper);
  return new workplane_t{result};
}

workplane_t *workplane_cut_blind_with_face(workplane_t *wp, topo_face_t *face,
                                           bool clean, bool both,
                                           double taper) {
  auto result = wp->ptr->cut_blind(*face->shp->shp->cast<flywave::topo::face>(),
                                   clean, both, taper);
  return new workplane_t{result};
}

workplane_t *workplane_revolve(workplane_t *wp, topo_vector_t *axisStart,
                               topo_vector_t *axisEnd, double angleDegrees,
                               bool combine, bool clean) {
  gp_Pnt start(axisStart->vec.x(), axisStart->vec.y(), axisStart->vec.z());
  gp_Pnt end(axisEnd->vec.x(), axisEnd->vec.y(), axisEnd->vec.z());
  auto result = wp->ptr->revolve(angleDegrees, start, end, combine, clean);
  return new workplane_t{result};
}

workplane_t *workplane_interp_plate(workplane_t *wp, topo_vector_t **points,
                                    int size, double thickness, bool combine,
                                    bool clean, int degree, int nbPtsOnCur,
                                    int nbIter, bool anisotropy, double tol2d,
                                    double tol3d, double tolAng, double tolCurv,
                                    int maxDeg, int maxSegments) {
  std::vector<gp_Pnt> pts;
  for (int i = 0; i < size; i++) {
    pts.push_back(
        gp_Pnt(points[i]->vec.x(), points[i]->vec.y(), points[i]->vec.z()));
  }
  auto result = wp->ptr->interp_plate(
      pts, thickness, combine, clean, degree, nbPtsOnCur, nbIter, anisotropy,
      tol2d, tol3d, tolAng, tolCurv, maxDeg, maxSegments);
  return new workplane_t{result};
}

workplane_t *workplane_interp_plate_with_edges(
    workplane_t *wp, topo_edge_t **edges, int size, topo_vector_t **points,
    int size2, double thickness, bool combine, bool clean, int degree,
    int nbPtsOnCur, int nbIter, bool anisotropy, double tol2d, double tol3d,
    double tolAng, double tolCurv, int maxDeg, int maxSegments) {
  std::vector<flywave::topo::edge> edgeList;
  for (int i = 0; i < size; i++) {
    edgeList.push_back(*edges[i]->shp->shp->cast<flywave::topo::edge>());
  }
  std::vector<gp_Pnt> pts;
  for (int i = 0; i < size2; i++) {
    pts.push_back(
        gp_Pnt(points[i]->vec.x(), points[i]->vec.y(), points[i]->vec.z()));
  }
  auto result = wp->ptr->interp_plate(
      edgeList, pts, thickness, combine, clean, degree, nbPtsOnCur, nbIter,
      anisotropy, tol2d, tol3d, tolAng, tolCurv, maxDeg, maxSegments);
  return new workplane_t{result};
}

workplane_t *workplane_interp_plate_with_workplane(
    workplane_t *wp, workplane_t *wp2, topo_vector_t **points, int size,
    double thickness, bool combine, bool clean, int degree, int nbPtsOnCur,
    int nbIter, bool anisotropy, double tol2d, double tol3d, double tolAng,
    double tolCurv, int maxDeg, int maxSegments) {
  std::vector<gp_Pnt> pts;
  for (int i = 0; i < size; i++) {
    pts.push_back(
        gp_Pnt(points[i]->vec.x(), points[i]->vec.y(), points[i]->vec.z()));
  }
  auto result = wp->ptr->interp_plate(
      *wp2->ptr, pts, thickness, combine, clean, degree, nbPtsOnCur, nbIter,
      anisotropy, tol2d, tol3d, tolAng, tolCurv, maxDeg, maxSegments);
  return new workplane_t{result};
}

workplane_t *workplane_box(workplane_t *wp, double length, double width,
                           double height, bool centerX, bool centerY,
                           bool centerZ, bool combine, bool clean) {
  auto result = wp->ptr->box(length, width, height, {centerX, centerY, centerZ},
                             combine, clean);
  return new workplane_t{result};
}

workplane_t *workplane_box_all(workplane_t *wp, double length, double width,
                               double height, bool centerAll, bool combine,
                               bool clean) {
  auto result = wp->ptr->box(length, width, height, centerAll, combine, clean);
  return new workplane_t{result};
}

workplane_t *workplane_sphere(workplane_t *wp, double radius,
                              topo_vector_t *direct, double angle1,
                              double angle2, double angle3, bool centerX,
                              bool centerY, bool centerZ, bool combine,
                              bool clean) {
  gp_Dir dir(direct->vec.x(), direct->vec.y(), direct->vec.z());
  auto result = wp->ptr->sphere(radius, dir, angle1, angle2, angle3,
                                {centerX, centerY, centerZ}, combine, clean);
  return new workplane_t{result};
}

workplane_t *workplane_sphere_all(workplane_t *wp, double radius,
                                  topo_vector_t *direct, double angle1,
                                  double angle2, double angle3, bool centerAll,
                                  bool combine, bool clean) {
  gp_Dir dir(direct->vec.x(), direct->vec.y(), direct->vec.z());
  auto result = wp->ptr->sphere(radius, dir, angle1, angle2, angle3, centerAll,
                                combine, clean);
  return new workplane_t{result};
}

workplane_t *workplane_cylinder(workplane_t *wp, double height, double radius,
                                topo_vector_t *direct, double angle,
                                bool centerX, bool centerY, bool centerZ,
                                bool combine, bool clean) {
  gp_Dir dir(direct->vec.x(), direct->vec.y(), direct->vec.z());
  auto result = wp->ptr->cylinder(height, radius, dir, angle,
                                  {centerX, centerY, centerZ}, combine, clean);
  return new workplane_t{result};
}

workplane_t *workplane_cylinder_all(workplane_t *wp, double height,
                                    double radius, topo_vector_t *direct,
                                    double angle, bool centerAll, bool combine,
                                    bool clean) {
  gp_Dir dir(direct->vec.x(), direct->vec.y(), direct->vec.z());
  auto result =
      wp->ptr->cylinder(height, radius, dir, angle, centerAll, combine, clean);
  return new workplane_t{result};
}

workplane_t *workplane_wedge(workplane_t *wp, double dx, double dy, double dz,
                             double xmin, double zmin, double xmax, double zmax,
                             topo_vector_t *pnt, topo_vector_t *dir,
                             bool centerX, bool centerY, bool centerZ,
                             bool combine, bool clean) {
  gp_Pnt point(pnt->vec.x(), pnt->vec.y(), pnt->vec.z());
  gp_Dir direction(dir->vec.x(), dir->vec.y(), dir->vec.z());
  auto result =
      wp->ptr->wedge(dx, dy, dz, xmin, zmin, xmax, zmax, point, direction,
                     {centerX, centerY, centerZ}, combine, clean);
  return new workplane_t{result};
}

workplane_t *workplane_wedge_all(workplane_t *wp, double dx, double dy,
                                 double dz, double xmin, double zmin,
                                 double xmax, double zmax, topo_vector_t *pnt,
                                 topo_vector_t *dir, bool centerAll,
                                 bool combine, bool clean) {
  gp_Pnt point(pnt->vec.x(), pnt->vec.y(), pnt->vec.z());
  gp_Dir direction(dir->vec.x(), dir->vec.y(), dir->vec.z());
  auto result = wp->ptr->wedge(dx, dy, dz, xmin, zmin, xmax, zmax, point,
                               direction, centerAll, combine, clean);
  return new workplane_t{result};
}

workplane_t *workplane_combine(workplane_t *wp, bool clean, bool glue,
                               double tol) {
  auto result = wp->ptr->combine(clean, glue, tol);
  return new workplane_t{result};
}

workplane_t *workplane_cut_thru_all(workplane_t *wp, double taper, bool clean) {
  auto result = wp->ptr->cut_thru_all(taper, clean);
  return new workplane_t{result};
}

workplane_t *workplane_loft(workplane_t *wp, bool ruled, bool combine,
                            bool clean) {
  auto result = wp->ptr->loft(ruled, combine, clean);
  return new workplane_t{result};
}

workplane_t *workplane_text(workplane_t *wp, const char *txt, double fontsize,
                            double distance, bool cut, bool combine, bool clean,
                            const char *font, const char *fontPath, int kind,
                            int halign, int valign) {
  auto result = wp->ptr->text(
      txt, fontsize, distance, cut, combine, clean, font,
      fontPath ? boost::make_optional<std::string>(fontPath) : boost::none,
      static_cast<flywave::topo::font_kind>(kind),
      static_cast<flywave::topo::horizontal_align>(halign),
      static_cast<flywave::topo::vertical_align>(valign));
  return new workplane_t{result};
}

workplane_t *workplane_section(workplane_t *wp, double height) {
  auto result = wp->ptr->section(height);
  return new workplane_t{result};
}

void workplane_to_pending(workplane_t *wp) { wp->ptr->to_pending(); }

workplane_t *workplane_offset2d(workplane_t *wp, double d, int kind,
                                bool forConstruction) {
  auto result = wp->ptr->offset2d(d, static_cast<GeomAbs_JoinType>(kind),
                                  forConstruction);
  return new workplane_t{result};
}

workplane_t *workplane_place_sketch(workplane_t *wp, sketch_t **sketches,
                                    int size) {
  std::vector<std::shared_ptr<flywave::topo::sketch>> sketchList;
  for (int i = 0; i < size; i++) {
    sketchList.push_back(sketches[i]->ptr);
  }
  auto result = wp->ptr->place_sketch(sketchList);
  return new workplane_t{result};
}

workplane_t *workplane_get(workplane_t *wp, int index) {
  auto result = (*wp->ptr)[index];
  return new workplane_t{result};
}

workplane_t *workplane_get_range(workplane_t *wp, int start, int end) {
  auto result = (*wp->ptr)[std::make_pair(start, end)];
  return new workplane_t{result};
}

workplane_t *workplane_get_indices(workplane_t *wp, int *indices, int size) {
  std::vector<int> idxList(indices, indices + size);
  auto result = (*wp->ptr)[idxList];
  return new workplane_t{result};
}

workplane_t *workplane_filter(workplane_t *wp,
                              bool (*predicate)(shape_object_t *)) {
  auto result =
      wp->ptr->filter([predicate](const flywave::topo::shape_object &obj) {
        shape_object_t wrapper{obj};
        return predicate(&wrapper);
      });
  return new workplane_t{result};
}

workplane_t *workplane_map(workplane_t *wp,
                           shape_object_t *(*mapper)(shape_object_t *)) {
  auto result = wp->ptr->map([mapper](const flywave::topo::shape_object &obj) {
    shape_object_t wrapper{obj};
    auto mapped = mapper(&wrapper);
    return mapped->obj;
  });
  return new workplane_t{result};
}

workplane_t *workplane_apply(workplane_t *wp,
                             shape_object_t **(*applier)(shape_object_t **,
                                                         int)) {
  auto result = wp->ptr->apply(
      [applier](const std::vector<flywave::topo::shape_object> &objs) {
        std::vector<shape_object_t *> wrappers;
        for (auto &obj : objs) {
          wrappers.push_back(new shape_object_t{obj});
        }
        auto applied = applier(wrappers.data(), wrappers.size());
        std::vector<flywave::topo::shape_object> result;
        for (int i = 0; i < wrappers.size(); i++) {
          result.push_back(applied[i]->obj);
          delete wrappers[i];
        }
        return result;
      });
  return new workplane_t{result};
}

workplane_t *workplane_sort(workplane_t *wp,
                            bool (*comparator)(shape_object_t *,
                                               shape_object_t *)) {
  auto result =
      wp->ptr->sort([comparator](const flywave::topo::shape_object &a,
                                 const flywave::topo::shape_object &b) {
        shape_object_t *wrapperA = new shape_object_t{a};
        shape_object_t *wrapperB = new shape_object_t{b};
        return comparator(wrapperA, wrapperB);
      });
  return new workplane_t{result};
}

void workplane_invoke(workplane_t *wp, workplane_t *(*fcn)()) {
  auto result = fcn();
  *wp = *result;
  delete result;
}

void workplane_export_to(workplane_t *wp, const char *path) {
  wp->ptr->export_to(path);
}

sketch_t *workplane_sketck(workplane_t *wp) {
  auto result = wp->ptr->sketch();
  return new sketch_t{result};
}

workplane_t *workplane_first(workplane_t *wp) {
  auto result = wp->ptr->first();
  return new workplane_t{result};
}

workplane_t *workplane_item(workplane_t *wp, int i) {
  auto result = wp->ptr->item(i);
  return new workplane_t{result};
}

workplane_t *workplane_last(workplane_t *wp) {
  auto result = wp->ptr->last();
  return new workplane_t{result};
}

workplane_t *workplane_end(workplane_t *wp, int n) {
  auto result = wp->ptr->end(n);
  return new workplane_t{result};
}

workplane_t **workplane_all(workplane_t *wp, int *count) {
  auto results = wp->ptr->all();
  *count = results.size();
  auto arr = new workplane_t *[*count];
  for (int i = 0; i < *count; i++) {
    arr[i] = new workplane_t{results[i]};
  }
  return arr;
}

shape_object_t **workplane_shapes(workplane_t *wp, int *count) {
  auto shapes = wp->ptr->shapes();
  *count = shapes.size();
  auto arr = new shape_object_t *[*count];
  for (int i = 0; i < *count; i++) {
    arr[i] = new shape_object_t{shapes[i]};
  }
  return arr;
}

shape_object_t **workplane_vals(workplane_t *wp, int *count) {
  auto vals = wp->ptr->vals();
  *count = vals.size();
  auto arr = new shape_object_t *[*count];
  for (int i = 0; i < *count; i++) {
    arr[i] = new shape_object_t{vals[i]};
  }
  return arr;
}

shape_object_t *workplane_val(workplane_t *wp) {
  auto val = wp->ptr->val();
  return new shape_object_t{val};
}

int workplane_size(workplane_t *wp) { return wp->ptr->size(); }

bool workplane_has_parent(workplane_t *wp) { return wp->ptr->has_parent(); }

workplane_t *workplane_parent(workplane_t *wp) {
  auto parent = wp->ptr->parent();
  return new workplane_t{parent};
}

#ifdef __cplusplus
}
#endif
