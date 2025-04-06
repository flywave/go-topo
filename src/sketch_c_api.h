#ifndef GO_SKETCH_C_API_H
#define GO_SKETCH_C_API_H

#include "selector_c_api.h"
#include "standard_c_api.h"
#include "topo_c_api.h"

#if defined(WIN32) || defined(WINDOWS) || defined(_sWIN32) || defined(_WINDOWS)
#define SKETCHCAPICALL __declspec(dllexport)
#else
#define SKETCHCAPICALL
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _workplane_t workplane_t;
typedef struct _sketch_val_t sketch_val_t;
typedef struct _sketch_t sketch_t;
typedef struct _sketch_constraint_value_t sketch_constraint_value_t;

SKETCHCAPICALL sketch_val_t *sketch_val_create_from_shape(topo_shape_t *shape);
SKETCHCAPICALL sketch_val_t *
sketch_val_create_from_location(topo_location_t *location);
SKETCHCAPICALL void sketch_val_free(sketch_val_t *obj);
SKETCHCAPICALL topo_shape_t *sketch_val_get_shape(sketch_val_t *obj);
SKETCHCAPICALL topo_location_t *sketch_val_get_location(sketch_val_t *obj);

SKETCHCAPICALL sketch_t *sketch_create_from_workplane(workplane_t *inPlane,
                                                      topo_location_t *location,
                                                      topo_compound_t *comp);
SKETCHCAPICALL sketch_t *sketch_create_from_location(topo_location_t *location,
                                                     topo_compound_t *comp);
SKETCHCAPICALL void sketch_free(sketch_t *obj);
SKETCHCAPICALL topo_face_t *sketch_get_faces(sketch_t *obj, int *size);

SKETCHCAPICALL void sketch_face_from_wire(sketch_t *sk, topo_wire_t *wire,
                                          double angle, const char *tag);
SKETCHCAPICALL void sketch_face_from_edges(sketch_t *sk, topo_edge_t **edges,
                                           int size, double angle,
                                           const char *tag);
SKETCHCAPICALL void sketch_face_from_shape(sketch_t *sk, topo_shape_t *shape,
                                           double angle, const char *tag);
SKETCHCAPICALL void sketch_face_from_sketch(sketch_t *sk, sketch_t *other,
                                            double angle, const char *tag);

SKETCHCAPICALL void sketch_rect(sketch_t *sk, double w, double h, double angle,
                                const char *tag);
SKETCHCAPICALL void sketch_circle(sketch_t *sk, double r, const char *tag);
SKETCHCAPICALL void sketch_ellipse(sketch_t *sk, double a1, double a2,
                                   double angle, const char *tag);
SKETCHCAPICALL void sketch_trapezoid(sketch_t *sk, double w, double h,
                                     double a1, double a2, double angle,
                                     const char *tag);
SKETCHCAPICALL void sketch_slot(sketch_t *sk, double w, double h, double angle,
                                const char *tag);
SKETCHCAPICALL void sketch_regular_polygon(sketch_t *sk, double r, int n,
                                           double angle, const char *tag);
SKETCHCAPICALL void sketch_polygon(sketch_t *sk, topo_vector_t **pts, int size,
                                   double angle, const char *tag);
SKETCHCAPICALL void sketch_rarray(sketch_t *sk, double xs, double ys, int nx,
                                  int ny, double angle, const char *tag);
SKETCHCAPICALL void sketch_parray(sketch_t *sk, double r, double a1, double da,
                                  int n, bool rotate, double angle,
                                  const char *tag);
SKETCHCAPICALL void sketch_distribute(sketch_t *sk, int n, double start,
                                      double stop, bool rotate, double angle,
                                      const char *tag);
SKETCHCAPICALL void sketch_push(sketch_t *sk, topo_location_t **locs, int size,
                                const char *tag);

// s
SKETCHCAPICALL void sketch_each(sketch_t *sk, topo_location_t **locs, int size,
                                const char *tag);
SKETCHCAPICALL void sketch_each_face(sketch_t *sk, topo_location_t **locs,
                                     int size, const char *tag);
SKETCHCAPICALL void sketch_each_sketch(sketch_t *sk, topo_location_t **locs,
                                       int size, const char *tag);
SKETCHCAPICALL void sketch_each_compound(sketch_t *sk, topo_location_t **locs,
                                         int size, const char *tag);
// s

SKETCHCAPICALL void sketch_hull(sketch_t *sk, int mode, const char *tag);
SKETCHCAPICALL void sketch_offset(sketch_t *sk, double d, int mode,
                                  const char *tag);
SKETCHCAPICALL void sketch_fillet(sketch_t *sk, double d);
SKETCHCAPICALL void sketch_chamfer(sketch_t *sk, double d);
SKETCHCAPICALL void sketch_clean(sketch_t *sk);
// tag
SKETCHCAPICALL void sketch_tag(sketch_t *sk, const char *tag);
// select
SKETCHCAPICALL void sketch_select(sketch_t *sk, const char **tags, int size);
// faces
SKETCHCAPICALL void sketch_faces(sketch_t *sk, const char *selector,
                                 const char *tag);
SKETCHCAPICALL void
sketch_faces_for_selector(sketch_t *sk, selector_t *selector, const char *tag);
// wires
SKETCHCAPICALL void sketch_wires(sketch_t *sk, const char *selector,
                                 const char *tag);
SKETCHCAPICALL void
sketch_wires_for_selector(sketch_t *sk, selector_t *selector, const char *tag);
// edges
SKETCHCAPICALL void sketch_edges(sketch_t *sk, const char *selector,
                                 const char *tag);
SKETCHCAPICALL void
sketch_edges_for_selector(sketch_t *sk, selector_t *selector, const char *tag);
// vertices
SKETCHCAPICALL void sketch_vertices(sketch_t *sk, const char *selector,
                                    const char *tag);
SKETCHCAPICALL void sketch_vertices_for_selector(sketch_t *sk,
                                                 selector_t *selector,
                                                 const char *tag);
// reset
SKETCHCAPICALL void sketch_reset(sketch_t *sk);
// delete_selected
SKETCHCAPICALL void sketch_delete_selected(sketch_t *sk);

SKETCHCAPICALL void sketch_edge(sketch_t *sk, topo_edge_t *edge,
                                const char *tag, bool forConstruction);
SKETCHCAPICALL void sketch_segment(sketch_t *sk, topo_vector_t *p1,
                                   topo_vector_t *p2, const char *tag,
                                   bool forConstruction);
SKETCHCAPICALL void sketch_segment2(sketch_t *sk, topo_vector_t *p2,
                                    const char *tag, bool forConstruction);
SKETCHCAPICALL void sketch_segment3(sketch_t *sk, double l, double a,
                                    const char *tag, bool forConstruction);
SKETCHCAPICALL void sketch_arc(sketch_t *sk, topo_vector_t *p1,
                               topo_vector_t *p2, topo_vector_t *p3,
                               const char *tag, bool forConstruction);
SKETCHCAPICALL void sketch_arc2(sketch_t *sk, topo_vector_t *p2,
                                topo_vector_t *p3, const char *tag,
                                bool forConstruction);
SKETCHCAPICALL void sketch_arc3(sketch_t *sk, topo_vector_t *center,
                                double radius, double start_angle,
                                double delta_angle, const char *tag,
                                bool forConstruction);
SKETCHCAPICALL void sketch_spline(sketch_t *sk, topo_vector_t **points,
                                  int size, const char *tag,
                                  bool forConstruction);
// const boost::optional<std::pair<topo_vector, topo_vector>> &tangents
SKETCHCAPICALL void sketch_spline2(sketch_t *sk, topo_vector_t **points,
                                   int size, topo_vector_t *tangents1,
                                   topo_vector_t *tangents2, bool periodic,
                                   const char *tag, bool forConstruction);
SKETCHCAPICALL void sketch_bezier(sketch_t *sk, topo_vector_t **points,
                                  int size, const char *tag,
                                  bool forConstruction);
SKETCHCAPICALL void sketch_close(sketch_t *sk, const char *tag);
SKETCHCAPICALL void sketch_assemble(sketch_t *sk, int mode, const char *tag);
SKETCHCAPICALL void sketch_constrain(sketch_t *sk, const char *tag,
                                     int constraint,
                                     sketch_constraint_value_t *arg);
SKETCHCAPICALL void sketch_constrain2(sketch_t *sk, const char *tag1,
                                      const char *tag2, int constraint,
                                      sketch_constraint_value_t *arg);
SKETCHCAPICALL void sketch_solve(sketch_t *sk);

SKETCHCAPICALL sketch_t *sketch_copy(sketch_t *sk);
SKETCHCAPICALL sketch_t *sketch_moved(sketch_t *sk, topo_location_t **locs,
                                      int size);
SKETCHCAPICALL sketch_t *sketch_located(sketch_t *sk, topo_location_t *loc);
SKETCHCAPICALL workplane_t *sketch_finalize(sketch_t *sk);
SKETCHCAPICALL sketch_val_t *sketch_val(sketch_t *sk);
SKETCHCAPICALL sketch_val_t **sketch_vals(sketch_t *sk, int *size);
SKETCHCAPICALL void sketch_add(sketch_t *sk);
SKETCHCAPICALL void sketch_subtract(sketch_t *sk);
SKETCHCAPICALL void sketch_replace(sketch_t *sk);

SKETCHCAPICALL void sketch_val_filter(sketch_t *sk,
                                      bool (*pred)(sketch_val_t *));
SKETCHCAPICALL void sketch_val_map(sketch_t *sk,
                                   sketch_val_t *(*f)(sketch_val_t *));
SKETCHCAPICALL void sketch_val_apply(sketch_t *sk,
                                     sketch_val_t **(*f)(sketch_val_t **, int));
SKETCHCAPICALL void sketch_val_sort(sketch_t *sk, bool (*comp)(sketch_val_t *,
                                                               sketch_val_t *));

#ifdef __cplusplus
}
#endif

#endif
