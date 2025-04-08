#ifndef GO_WORKPLANE_C_API_H
#define GO_WORKPLANE_C_API_H

#include "sketch_c_api.h"
#include "standard_c_api.h"
#include "topo_c_api.h"

#if defined(WIN32) || defined(WINDOWS) || defined(_WIN32) || defined(_WINDOWS)
#define WORKPLANECAPICALL __declspec(dllexport)
#else
#define WORKPLANECAPICALL
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _shape_object_t shape_object_t;
typedef struct _workplane_t workplane_t;

WORKPLANECAPICALL void shape_object_free(shape_object_t *obj);
WORKPLANECAPICALL shape_object_t *
shape_object_create_from_shape(topo_shape_t *shape);
WORKPLANECAPICALL shape_object_t *
shape_object_create_from_vector(topo_vector_t *vector);
WORKPLANECAPICALL shape_object_t *
shape_object_create_from_location(topo_location_t *location);
WORKPLANECAPICALL shape_object_t *
shape_object_create_from_sketch(sketch_t *sketch);
WORKPLANECAPICALL shape_object_t *shape_object_create();
WORKPLANECAPICALL int shape_object_type(shape_object_t *obj);
WORKPLANECAPICALL topo_shape_t *shape_object_get_shape(shape_object_t *obj);
WORKPLANECAPICALL topo_vector_t *shape_object_get_vector(shape_object_t *obj);
WORKPLANECAPICALL topo_location_t *
shape_object_get_location(shape_object_t *obj);
WORKPLANECAPICALL sketch_t *shape_object_get_sketch(shape_object_t *obj);

WORKPLANECAPICALL workplane_t *workplane_create();
WORKPLANECAPICALL workplane_t *
workplane_create_from_plane(topo_plane_t *plane, topo_vector_t *origin);
WORKPLANECAPICALL workplane_t *
workplane_create_from_name(const char *planeName, topo_vector_t *origin);

WORKPLANECAPICALL void workplane_free(workplane_t *wp);

WORKPLANECAPICALL topo_shape_t *workplane_value(workplane_t *wp);
WORKPLANECAPICALL workplane_t *workplane_clean(workplane_t *wp);

WORKPLANECAPICALL workplane_t *workplane_workplane(workplane_t *wp,
                                                   double offset, bool invert,
                                                   int centerOption,
                                                   topo_vector_t *origin);

WORKPLANECAPICALL void workplane_tag(workplane_t *wp, const char *name);

WORKPLANECAPICALL workplane_t *workplane_split(workplane_t *wp, bool keepTop,
                                               bool keepBottom);
WORKPLANECAPICALL workplane_t *
workplane_split_with_shape(workplane_t *wp, topo_shape_t *splitter);
WORKPLANECAPICALL workplane_t *
workplane_split_with_workplane(workplane_t *wp, workplane_t *splitter);

WORKPLANECAPICALL void workplane_add(workplane_t *wp, workplane_t *other);
WORKPLANECAPICALL void workplane_add_shape(workplane_t *wp,
                                           shape_object_t *obj);
WORKPLANECAPICALL void workplane_add_shapes(workplane_t *wp,
                                            shape_object_t **objs, int size);

WORKPLANECAPICALL workplane_t *workplane_from_tagged(workplane_t *wp,
                                                     const char *tag);

WORKPLANECAPICALL topo_solid_t workplane_find_solid(workplane_t *wp,
                                                    bool searchStack,
                                                    bool searchParents);

WORKPLANECAPICALL workplane_t *
workplane_vertices(workplane_t *wp, const char *selector, const char *tag);
WORKPLANECAPICALL workplane_t *
workplane_vertices_with_selector(workplane_t *wp, selector_t *sel,
                                 const char *tag);

WORKPLANECAPICALL workplane_t *
workplane_faces(workplane_t *wp, const char *selector, const char *tag);
WORKPLANECAPICALL workplane_t *workplane_faces_with_selector(workplane_t *wp,
                                                             selector_t *sel,
                                                             const char *tag);

WORKPLANECAPICALL workplane_t *
workplane_edges(workplane_t *wp, const char *selector, const char *tag);
WORKPLANECAPICALL workplane_t *workplane_edges_with_selector(workplane_t *wp,
                                                             selector_t *sel,
                                                             const char *tag);

WORKPLANECAPICALL workplane_t *
workplane_wires(workplane_t *wp, const char *selector, const char *tag);
WORKPLANECAPICALL workplane_t *workplane_wires_with_selector(workplane_t *wp,
                                                             selector_t *sel,
                                                             const char *tag);

WORKPLANECAPICALL workplane_t *
workplane_solids(workplane_t *wp, const char *selector, const char *tag);
WORKPLANECAPICALL workplane_t *workplane_solids_with_selector(workplane_t *wp,
                                                              selector_t *sel,
                                                              const char *tag);

WORKPLANECAPICALL workplane_t *
workplane_shells(workplane_t *wp, const char *selector, const char *tag);
WORKPLANECAPICALL workplane_t *workplane_shells_with_selector(workplane_t *wp,
                                                              selector_t *sel,
                                                              const char *tag);

WORKPLANECAPICALL workplane_t *
workplane_compounds(workplane_t *wp, const char *selector, const char *tag);
WORKPLANECAPICALL workplane_t *
workplane_compounds_with_selector(workplane_t *wp, selector_t *sel,
                                  const char *tag);

WORKPLANECAPICALL workplane_t *workplane_ancestors(workplane_t *wp, int kind,
                                                   const char *tag);
WORKPLANECAPICALL workplane_t *workplane_siblings(workplane_t *wp, int kind,
                                                  int level, const char *tag);

WORKPLANECAPICALL workplane_t *
workplane_rotate_about_center(workplane_t *wp, topo_vector_t *axisEndPoint,
                              double angle);
WORKPLANECAPICALL workplane_t *workplane_rotate(workplane_t *wp,
                                                topo_vector_t *axisStart,
                                                topo_vector_t *axisEnd,
                                                double angle);
WORKPLANECAPICALL workplane_t *workplane_mirror(workplane_t *wp,
                                                const char *planeName,
                                                topo_vector_t *basePoint);
WORKPLANECAPICALL workplane_t *
workplane_mirror_with_normal(workplane_t *wp, topo_vector_t *normal,
                             topo_vector_t *basePoint);
WORKPLANECAPICALL workplane_t *
workplane_mirror_with_name(workplane_t *wp, const char *planeName,
                           topo_vector_t *basePoint, bool unionResult);
WORKPLANECAPICALL workplane_t *
workplane_mirror_with_face(workplane_t *wp, topo_face_t *mirrorFace,
                           topo_vector_t *basePoint, bool unionResult);

WORKPLANECAPICALL workplane_t *workplane_translate(workplane_t *wp,
                                                   topo_vector_t *vec);

WORKPLANECAPICALL workplane_t *
workplane_shell(workplane_t *wp, double thickness, const char *kind);
WORKPLANECAPICALL workplane_t *workplane_fillet(workplane_t *wp, double radius);
WORKPLANECAPICALL workplane_t *workplane_chamfer(workplane_t *wp, double length,
                                                 double length2);

WORKPLANECAPICALL workplane_t *workplane_transformed(workplane_t *wp,
                                                     topo_vector_t *rotate,
                                                     topo_vector_t *offset);

WORKPLANECAPICALL workplane_t *
workplane_rarray(workplane_t *wp, double xSpacing, double ySpacing, int xCount,
                 int yCount, bool centerX, bool centerY);
WORKPLANECAPICALL workplane_t *
workplane_polar_array(workplane_t *wp, double radius, double startAngle,
                      double angle, int count, bool fill, bool rotate);

WORKPLANECAPICALL workplane_t *
workplane_push_points(workplane_t *wp, topo_location_t **locs, int size);
WORKPLANECAPICALL workplane_t *
workplane_push_points_with_vector(workplane_t *wp, topo_vector_t **vecs,
                                  int size);

WORKPLANECAPICALL workplane_t *workplane_center(workplane_t *wp, double x,
                                                double y);

WORKPLANECAPICALL workplane_t *
workplane_line_to(workplane_t *wp, double x, double y, bool forConstruction);
WORKPLANECAPICALL workplane_t *
workplane_bezier(workplane_t *wp, topo_vector_t **points, int size,
                 bool forConstruction, bool includeCurrent, bool makeWire);
WORKPLANECAPICALL workplane_t *workplane_line(workplane_t *wp, double xDist,
                                              double yDist,
                                              bool forConstruction);
WORKPLANECAPICALL workplane_t *workplane_vline(workplane_t *wp, double distance,
                                               bool forConstruction);
WORKPLANECAPICALL workplane_t *workplane_hline(workplane_t *wp, double distance,
                                               bool forConstruction);
WORKPLANECAPICALL workplane_t *
workplane_vline_to(workplane_t *wp, double yCoord, bool forConstruction);
WORKPLANECAPICALL workplane_t *
workplane_hline_to(workplane_t *wp, double xCoord, bool forConstruction);
WORKPLANECAPICALL workplane_t *workplane_polar_line(workplane_t *wp,
                                                    double distance,
                                                    double angle,
                                                    bool forConstruction);
WORKPLANECAPICALL workplane_t *workplane_polar_line_to(workplane_t *wp,
                                                       double distance,
                                                       double angle,
                                                       bool forConstruction);
WORKPLANECAPICALL workplane_t *workplane_move_to(workplane_t *wp, double x,
                                                 double y);
WORKPLANECAPICALL workplane_t *workplane_move(workplane_t *wp, double xDist,
                                              double yDist);
WORKPLANECAPICALL workplane_t *workplane_slot2d(workplane_t *wp, double length,
                                                double diameter, double angle);

WORKPLANECAPICALL workplane_t *
workplane_spline(workplane_t *wp, topo_vector_t **points, int size,
                 bool periodic, topo_vector_t **tangents, int size2, bool scale,
                 double tol, bool forConstruction, bool includeCurrent,
                 bool makeWire);
WORKPLANECAPICALL workplane_t *
workplane_spline_approx(workplane_t *wp, topo_vector_t **points, int size,
                        double tol, int minDeg, int maxDeg,
                        topo_vector_t *smoothing, bool forConstruction,
                        bool includeCurrent, bool makeWire);
WORKPLANECAPICALL workplane_t *
workplane_parametric_curve(workplane_t *wp, void *userdata,
                           pnt3d_t (*func)(void *userdata, double), int N,
                           double start, double stop, double tol, int minDeg,
                           int maxDeg, topo_vector_t *smoothing, bool makeWire);
WORKPLANECAPICALL workplane_t *
workplane_parametric_surface(workplane_t *wp, void *userdata,
                             pnt3d_t (*func)(void *userdata, double, double),
                             int N, double start, double stop, double tol,
                             int minDeg, int maxDeg, topo_vector_t *smoothing);
WORKPLANECAPICALL workplane_t *
workplane_ellipse_arc(workplane_t *wp, double x_radius, double y_radius,
                      double angle1, double angle2, double rotation_angle,
                      int sense, bool forConstruction, bool startAtCurrent,
                      bool makeWire);
WORKPLANECAPICALL workplane_t *workplane_three_point_arc(workplane_t *wp,
                                                         topo_vector_t *point1,
                                                         topo_vector_t *point2,
                                                         bool forConstruction);
WORKPLANECAPICALL workplane_t *workplane_sagitta_arc(workplane_t *wp,
                                                     topo_vector_t *endPoint,
                                                     double sag,
                                                     bool forConstruction);
WORKPLANECAPICALL workplane_t *workplane_radius_arc(workplane_t *wp,
                                                    topo_vector_t *endPoint,
                                                    double radius,
                                                    bool forConstruction);
WORKPLANECAPICALL workplane_t *
workplane_tangent_arc_point(workplane_t *wp, topo_vector_t *endpoint,
                            bool forConstruction, bool relative);
WORKPLANECAPICALL workplane_t *workplane_mirror_y(workplane_t *wp);
WORKPLANECAPICALL workplane_t *workplane_mirror_x(workplane_t *wp);
WORKPLANECAPICALL workplane_t *workplane_consolidate_wires(workplane_t *wp);

WORKPLANECAPICALL workplane_t *
workplane_each(workplane_t *wp, void *userdata,
               void (*func)(void *userdata, shape_object_t *),
               bool useLocalCoordinates, bool combine, bool clean);
WORKPLANECAPICALL workplane_t *
workplane_eachpoint(workplane_t *wp, void *userdata,
                    void (*func)(void *userdata, shape_object_t *),
                    bool useLocalCoordinates, bool combine, bool clean);
WORKPLANECAPICALL workplane_t *
workplane_eachpoint_with_shape(workplane_t *wp, topo_shape_t *shapeObj,
                               bool useLocalCoordinates, bool combine,
                               bool clean);
WORKPLANECAPICALL workplane_t *
workplane_eachpoint_with_workplane(workplane_t *wp, workplane_t *wp2,
                                   bool useLocalCoordinates, bool combine,
                                   bool clean);
WORKPLANECAPICALL workplane_t *workplane_eachpoint_with_location(
    workplane_t *wp, void *userdata,
    topo_shape_t *(*func)(void *userdata, topo_location_t *loc),
    bool useLocalCoordinates, bool combine, bool clean);
WORKPLANECAPICALL workplane_t *workplane_rect(workplane_t *wp, double xLen,
                                              double yLen, bool centerX,
                                              bool centerY,
                                              bool forConstruction);
WORKPLANECAPICALL workplane_t *workplane_rect_all(workplane_t *wp, double xLen,
                                                  double yLen, bool centerAll,
                                                  bool forConstruction);
WORKPLANECAPICALL workplane_t *workplane_circle(workplane_t *wp, double radius,
                                                bool forConstruction);
WORKPLANECAPICALL workplane_t *
workplane_ellipse(workplane_t *wp, double x_radius, double y_radius,
                  double rotation_angle, bool forConstruction);
WORKPLANECAPICALL workplane_t *workplane_polygon(workplane_t *wp, int nSides,
                                                 double diameter,
                                                 bool forConstruction,
                                                 bool circumscribed);
WORKPLANECAPICALL workplane_t *
workplane_polyline(workplane_t *wp, topo_vector_t **points, int size,
                   bool forConstruction, bool includeCurrent);
WORKPLANECAPICALL workplane_t *workplane_close(workplane_t *wp);
WORKPLANECAPICALL double workplane_largest_dimension(workplane_t *wp);
WORKPLANECAPICALL workplane_t *
workplane_cut_each(workplane_t *wp, void *userdata,
                   topo_shape_t *(*fcn)(void *userdata, topo_location_t *loc),
                   bool useLocalCoordinates, bool clean);
WORKPLANECAPICALL workplane_t *
workplane_cbore_hole(workplane_t *wp, double diameter, double cboreDiameter,
                     double cboreDepth, double depth, bool clean);
WORKPLANECAPICALL workplane_t *
workplane_csk_hole(workplane_t *wp, double diameter, double cskDiameter,
                   double cskAngle, double depth, bool clean);
WORKPLANECAPICALL workplane_t *workplane_hole(workplane_t *wp, double diameter,
                                              double depth, bool clean);
WORKPLANECAPICALL workplane_t *
workplane_twist_extrude(workplane_t *wp, double distance, double angleDegrees,
                        bool combine, bool clean);

WORKPLANECAPICALL workplane_t *workplane_extrude(workplane_t *wp,
                                                 double distance, bool combine,
                                                 bool clean, bool both,
                                                 double *taper);
WORKPLANECAPICALL workplane_t *
workplane_extrude_with_face_type(workplane_t *wp, int index_type, bool combine,
                                 bool clean, bool both, double *taper);
WORKPLANECAPICALL workplane_t *
workplane_extrude_with_face(workplane_t *wp, topo_face_t *face, bool combine,
                            bool clean, bool both, double *taper);

WORKPLANECAPICALL workplane_t *
workplane_sweep(workplane_t *wp, workplane_t *path, bool multisection,
                bool makeSolid, bool isFrenet, bool combine, bool clean,
                int transition, topo_vector_t *normal, workplane_t *auxSpine);
WORKPLANECAPICALL workplane_t *
workplane_sweep_with_wire(workplane_t *wp, topo_wire_t *path, bool multisection,
                          bool makeSolid, bool isFrenet, bool combine,
                          bool clean, int transition, topo_vector_t *normal,
                          workplane_t *auxSpine);
WORKPLANECAPICALL workplane_t *
workplane_sweep_with_edge(workplane_t *wp, topo_edge_t *path, bool multisection,
                          bool makeSolid, bool isFrenet, bool combine,
                          bool clean, int transition, topo_vector_t *normal,
                          workplane_t *auxSpine);

WORKPLANECAPICALL workplane_t *workplane_union(workplane_t *wp,
                                               workplane_t *other, bool clean,
                                               bool glue, double tol);
WORKPLANECAPICALL workplane_t *workplane_union_with_solid(workplane_t *wp,
                                                          topo_solid_t *other,
                                                          bool clean, bool glue,
                                                          double tol);
WORKPLANECAPICALL workplane_t *
workplane_union_with_compound(workplane_t *wp, topo_compound_t *other,
                              bool clean, bool glue, double tol);
WORKPLANECAPICALL workplane_t *
workplane_cut(workplane_t *wp, workplane_t *other, bool clean, double tol);
WORKPLANECAPICALL workplane_t *workplane_cut_with_solid(workplane_t *wp,
                                                        topo_solid_t *other,
                                                        bool clean, double tol);
WORKPLANECAPICALL workplane_t *
workplane_cut_with_compound(workplane_t *wp, topo_compound_t *other, bool clean,
                            double tol);
WORKPLANECAPICALL workplane_t *workplane_intersect(workplane_t *wp,
                                                   workplane_t *other,
                                                   bool clean, double tol);
WORKPLANECAPICALL workplane_t *
workplane_intersect_with_solid(workplane_t *wp, topo_solid_t *other, bool clean,
                               double tol);
WORKPLANECAPICALL workplane_t *
workplane_intersect_with_compound(workplane_t *wp, topo_compound_t *other,
                                  bool clean, double tol);

WORKPLANECAPICALL workplane_t *workplane_cut_blind(workplane_t *wp,
                                                   double distance, bool clean,
                                                   bool both, double taper);
WORKPLANECAPICALL workplane_t *
workplane_cut_blind_with_until_face(workplane_t *wp, int untilFace, bool clean,
                                    bool both, double taper);
WORKPLANECAPICALL workplane_t *
workplane_cut_blind_with_face(workplane_t *wp, topo_face_t *face, bool clean,
                              bool both, double taper);
WORKPLANECAPICALL workplane_t *workplane_revolve(workplane_t *wp,
                                                 topo_vector_t *axisStart,
                                                 topo_vector_t *axisEnd,
                                                 double angleDegrees,
                                                 bool combine, bool clean);
WORKPLANECAPICALL workplane_t *
workplane_interp_plate(workplane_t *wp, topo_vector_t **points, int size,
                       double thickness, bool combine, bool clean, int degree,
                       int nbPtsOnCur, int nbIter, bool anisotropy,
                       double tol2d, double tol3d, double tolAng,
                       double tolCurv, int maxDeg, int maxSegments);
WORKPLANECAPICALL workplane_t *workplane_interp_plate_with_edges(
    workplane_t *wp, topo_edge_t **edges, int size, topo_vector_t **points,
    int size2, double thickness, bool combine, bool clean, int degree,
    int nbPtsOnCur, int nbIter, bool anisotropy, double tol2d, double tol3d,
    double tolAng, double tolCurv, int maxDeg, int maxSegments);
WORKPLANECAPICALL workplane_t *workplane_interp_plate_with_workplane(
    workplane_t *wp, workplane_t *wp2, topo_vector_t **points, int size,
    double thickness, bool combine, bool clean, int degree, int nbPtsOnCur,
    int nbIter, bool anisotropy, double tol2d, double tol3d, double tolAng,
    double tolCurv, int maxDeg, int maxSegments);

WORKPLANECAPICALL workplane_t *workplane_box(workplane_t *wp, double length,
                                             double width, double height,
                                             bool centerX, bool centerY,
                                             bool centerZ, bool combine,
                                             bool clean);
WORKPLANECAPICALL workplane_t *workplane_box_all(workplane_t *wp, double length,
                                                 double width, double height,
                                                 bool centerAll, bool combine,
                                                 bool clean);
WORKPLANECAPICALL workplane_t *
workplane_sphere(workplane_t *wp, double radius, topo_vector_t *direct,
                 double angle1, double angle2, double angle3, bool centerX,
                 bool centerY, bool centerZ, bool combine, bool clean);
WORKPLANECAPICALL workplane_t *
workplane_sphere_all(workplane_t *wp, double radius, topo_vector_t *direct,
                     double angle1, double angle2, double angle3,
                     bool centerAll, bool combine, bool clean);
WORKPLANECAPICALL workplane_t *
workplane_cylinder(workplane_t *wp, double height, double radius,
                   topo_vector_t *direct, double angle, bool centerX,
                   bool centerY, bool centerZ, bool combine, bool clean);
WORKPLANECAPICALL workplane_t *
workplane_cylinder_all(workplane_t *wp, double height, double radius,
                       topo_vector_t *direct, double angle, bool centerAll,
                       bool combine, bool clean);
WORKPLANECAPICALL workplane_t *
workplane_wedge(workplane_t *wp, double dx, double dy, double dz, double xmin,
                double zmin, double xmax, double zmax, topo_vector_t *pnt,
                topo_vector_t *dir, bool centerX, bool centerY, bool centerZ,
                bool combine, bool clean);
WORKPLANECAPICALL workplane_t *
workplane_wedge_all(workplane_t *wp, double dx, double dy, double dz,
                    double xmin, double zmin, double xmax, double zmax,
                    topo_vector_t *pnt, topo_vector_t *dir, bool centerAll,
                    bool combine, bool clean);
WORKPLANECAPICALL workplane_t *workplane_combine(workplane_t *wp, bool clean,
                                                 bool glue, double tol);
WORKPLANECAPICALL workplane_t *workplane_cut_thru_all(workplane_t *wp,
                                                      double taper, bool clean);
WORKPLANECAPICALL workplane_t *workplane_loft(workplane_t *wp, bool ruled,
                                              bool combine, bool clean);
WORKPLANECAPICALL workplane_t *workplane_text(workplane_t *wp, const char *txt,
                                              double fontsize, double distance,
                                              bool cut, bool combine,
                                              bool clean, const char *font,
                                              const char *fontPath, int kind,
                                              int halign, int valign);
WORKPLANECAPICALL workplane_t *workplane_section(workplane_t *wp,
                                                 double height);
WORKPLANECAPICALL void workplane_to_pending(workplane_t *wp);
WORKPLANECAPICALL workplane_t *
workplane_offset2d(workplane_t *wp, double d, int kind, bool forConstruction);
WORKPLANECAPICALL workplane_t *
workplane_place_sketch(workplane_t *wp, sketch_t **sketches, int size);

WORKPLANECAPICALL workplane_t *workplane_get(workplane_t *wp, int index);
WORKPLANECAPICALL workplane_t *workplane_get_range(workplane_t *wp, int start,
                                                   int end);
WORKPLANECAPICALL workplane_t *workplane_get_indices(workplane_t *wp,
                                                     int *indices, int size);

WORKPLANECAPICALL workplane_t *
workplane_filter(workplane_t *wp, void *userdate,
                 bool (*predicate)(void *userdate, shape_object_t *obj));
WORKPLANECAPICALL workplane_t *
workplane_map(workplane_t *wp, void *userdate,
              shape_object_t *(*mapper)(void *userdate, shape_object_t *obj));
WORKPLANECAPICALL workplane_t *
workplane_apply(workplane_t *wp, void *userdate,
                shape_object_t **(*applier)(void *userdate,
                                            shape_object_t **objs, int count));
WORKPLANECAPICALL workplane_t *
workplane_sort(workplane_t *wp, void *userdate,
               bool (*comparator)(void *userdate, shape_object_t *obj1,
                                  shape_object_t *obj2));
WORKPLANECAPICALL void workplane_invoke(workplane_t *wp, void *userdate,
                                        workplane_t *(*fcn)(void *userdate));

WORKPLANECAPICALL void workplane_export_to(workplane_t *wp, const char *path);
WORKPLANECAPICALL sketch_t *workplane_sketck(workplane_t *wp);

WORKPLANECAPICALL workplane_t *workplane_first(workplane_t *wp);
WORKPLANECAPICALL workplane_t *workplane_item(workplane_t *wp, int i);
WORKPLANECAPICALL workplane_t *workplane_last(workplane_t *wp);
WORKPLANECAPICALL workplane_t *workplane_end(workplane_t *wp, int n);

WORKPLANECAPICALL workplane_t **workplane_all(workplane_t *wp, int *count);
WORKPLANECAPICALL void workplane_list_free(workplane_t **list, int count);
WORKPLANECAPICALL topo_shape_t **workplane_shapes(workplane_t *wp,
                                                    int *count);
WORKPLANECAPICALL void shape_list_free(topo_shape_t **list, int count);
WORKPLANECAPICALL shape_object_t **workplane_vals(workplane_t *wp, int *count);
WORKPLANECAPICALL void shape_objects_free(shape_object_t **list, int count);
WORKPLANECAPICALL shape_object_t *workplane_val(workplane_t *wp);
WORKPLANECAPICALL int workplane_size(workplane_t *wp);
WORKPLANECAPICALL bool workplane_has_parent(workplane_t *wp);
WORKPLANECAPICALL workplane_t *workplane_parent(workplane_t *wp);

#ifdef __cplusplus
}
#endif

#endif
