#ifndef GO_TOPO_C_API_H
#define GO_TOPO_C_API_H

#if defined(WIN32) || defined(WINDOWS) || defined(_WIN32) || defined(_WINDOWS)
#define TOPOCAPICALL __declspec(dllexport)
#else
#define TOPOCAPICALL
#endif

#include <stdbool.h>

#include "geometry_c_api.h"
#include "standard_c_api.h"

#ifdef __cplusplus
extern "C" {
#endif

enum { BOOLFUSE, BOOLCUT, BOOLCOMMON };

enum { TextureCube, TextureNormal, TextureNormalAutoScale };
enum { DIR_WEST, DIR_EAST, DIR_NORTH, DIR_SOUTH, DIR_UP, DIR_DOWN };
enum {
  TopoSolid,
  TopoShell,
  TopoFace,
  TopoEdge,
  TopoVertex,
  TopoWire,
  TopoCompound,
  TopoCompSolid,
  TopoShape,
};
enum { ORI_FORWARD, ORI_REVERSED, ORI_INTERNAL, ORI_EXTERNAL, ORI_UNKNOW };

typedef struct _topo_shape_t topo_shape_t;
typedef struct _topo_vector_t topo_vector_t;
typedef struct _topo_plane_t topo_plane_t;
typedef struct _topo_bbox_t topo_bbox_t;
typedef struct _topo_matrix_t topo_matrix_t;
typedef struct _topo_location_t topo_location_t;
typedef struct _topo_mesh_receiver_t topo_mesh_receiver_t;
typedef struct _topo_comp_solid_iterator_t topo_comp_solid_iterator_t;
typedef struct _topo_compound_iterator_t topo_compound_iterator_t;
typedef struct _topo_edge_iterator_t topo_edge_iterator_t;
typedef struct _topo_face_iterator_t topo_face_iterator_t;
typedef struct _topo_shell_iterator_t topo_shell_iterator_t;
typedef struct _topo_solid_iterator_t topo_solid_iterator_t;
typedef struct _topo_vertex_iterator_t topo_vertex_iterator_t;
typedef struct _topo_wire_iterator_t topo_wire_iterator_t;

typedef struct _topo_comp_solid_t {
  topo_shape_t *shp;
} topo_comp_solid_t;

typedef struct _topo_compound_t {
  topo_shape_t *shp;
} topo_compound_t;

typedef struct _topo_face_t {
  topo_shape_t *shp;
} topo_face_t;

typedef struct _topo_shell_t {
  topo_shape_t *shp;
} topo_shell_t;

typedef struct _topo_solid_t {
  topo_shape_t *shp;
} topo_solid_t;

typedef struct _topo_vertex_t {
  topo_shape_t *shp;
} topo_vertex_t;

typedef struct _topo_wire_t {
  topo_shape_t *shp;
} topo_wire_t;

typedef struct _topo_edge_t {
  topo_shape_t *shp;
} topo_edge_t;

typedef struct _mesh_receiver_cb_t {
  void *ctx;
  void (*begin)(void *ctx);
  void (*end)(void *ctx);
  int (*append_face)(void *ctx, color_t color);
  void (*append_node_norm)(void *ctx, int face, pnt3d_t p, pnt3d_t n);
  void (*append_node_norm_uv)(void *ctx, int face, pnt3d_t p, pnt3d_t n,
                              pnt2d_t uv);
  void (*append_node)(void *ctx, int face, pnt3d_t p);
  void (*append_triangle)(void *ctx, int face, int a, int b, int c);
} mesh_receiver_cb_t;

TOPOCAPICALL topo_mesh_receiver_t *
topo_mesh_receiver_new(mesh_receiver_cb_t cb);
TOPOCAPICALL void topo_mesh_receiver_free(topo_mesh_receiver_t *p);

TOPOCAPICALL topo_location_t *topo_location_new(trsf_t t);
TOPOCAPICALL void topo_location_free(topo_location_t *p);
TOPOCAPICALL trsf_t topo_location_get_trsf(topo_location_t *p);
TOPOCAPICALL void topo_location_list_free(topo_location_t **result,
                                          int result_count);

TOPOCAPICALL topo_vector_t *topo_vector_new(double x, double y, double z);
TOPOCAPICALL void topo_vector_free(topo_vector_t *p);
TOPOCAPICALL double topo_vector_get_x(topo_vector_t *p);
TOPOCAPICALL double topo_vector_get_y(topo_vector_t *p);
TOPOCAPICALL double topo_vector_get_z(topo_vector_t *p);

TOPOCAPICALL topo_plane_t *topo_plane_new(pnt3d_t *origin, dir3d_t *xDir,
                                          vec3d_t *normal);
TOPOCAPICALL topo_plane_t *topo_plane_new_from_named(const char *name,
                                                     pnt3d_t *origin);
TOPOCAPICALL void topo_plane_free(topo_plane_t *p);
TOPOCAPICALL pnt3d_t topo_plane_get_origin(topo_plane_t *p);
TOPOCAPICALL dir3d_t topo_plane_get_x_dir(topo_plane_t *p);
TOPOCAPICALL dir3d_t topo_plane_get_y_dir(topo_plane_t *p);
TOPOCAPICALL dir3d_t topo_plane_get_z_dir(topo_plane_t *p);

TOPOCAPICALL topo_bbox_t *topo_bbox_new(bbox_t bbox);
TOPOCAPICALL topo_bbox_t *topo_bbox_new_from_shape(topo_shape_t *p);
TOPOCAPICALL void topo_bbox_free(topo_bbox_t *p);
TOPOCAPICALL bbox_t topo_bbox_get_bbox(topo_bbox_t *p);

TOPOCAPICALL topo_matrix_t *topo_matrix_new(trsf_t t);
TOPOCAPICALL void topo_matrix_free(topo_matrix_t *p);
TOPOCAPICALL double topo_matrix_get_value(topo_matrix_t *p, int row, int col);

TOPOCAPICALL void topo_shape_free(topo_shape_t *p);
TOPOCAPICALL topo_shape_t *topo_shape_share(topo_shape_t *p);

TOPOCAPICALL topo_solid_t topo_make_solid();
TOPOCAPICALL _Bool topo_shape_is_null(topo_shape_t *p);
TOPOCAPICALL _Bool topo_shape_is_valid(topo_shape_t *p);
TOPOCAPICALL _Bool topo_shape_equals(topo_shape_t *p, topo_shape_t *o);
TOPOCAPICALL int topo_shape_type(topo_shape_t *p);

TOPOCAPICALL bbox_t topo_shape_bounding_box(topo_shape_t *p);
TOPOCAPICALL int topo_shape_hash_code(topo_shape_t *p);
TOPOCAPICALL int topo_shape_transform(topo_shape_t *p, trsf_t mat);
TOPOCAPICALL int topo_shape_translate(topo_shape_t *p, vec3d_t delta);
TOPOCAPICALL int topo_shape_rotate_from_two_point(topo_shape_t *p, double angle,
                                                  pnt3d_t p1, pnt3d_t p2);
TOPOCAPICALL int topo_shape_rotate_from_axis1(topo_shape_t *p, double angle,
                                              axis1_t a);
TOPOCAPICALL int topo_shape_rotate_from_quaternion(topo_shape_t *p,
                                                   quaternion_t q);
TOPOCAPICALL int topo_shape_scale(topo_shape_t *p, double angle, pnt3d_t a);
TOPOCAPICALL int topo_shape_mirror_from_point_norm(topo_shape_t *p, pnt3d_t pnt,
                                                   pnt3d_t ner);
TOPOCAPICALL int topo_shape_mirror_from_axis1(topo_shape_t *p, axis1_t a);
TOPOCAPICALL int topo_shape_mirror_from_axis2(topo_shape_t *p, axis2_t a);
TOPOCAPICALL topo_shape_t *topo_shape_transformed(topo_shape_t *p, trsf_t mat);
TOPOCAPICALL topo_shape_t *topo_shape_translated(topo_shape_t *p,
                                                 vec3d_t delta);
TOPOCAPICALL topo_shape_t *topo_shape_rotated_from_two_point(topo_shape_t *p,
                                                             double angle,
                                                             pnt3d_t p1,
                                                             pnt3d_t p2);
TOPOCAPICALL topo_shape_t *
topo_shape_rotated_from_axis1(topo_shape_t *p, double angle, axis1_t a);
TOPOCAPICALL topo_shape_t *topo_shape_rotated_from_quaternion(topo_shape_t *p,
                                                              quaternion_t q);
TOPOCAPICALL topo_shape_t *topo_shape_scaled(topo_shape_t *p, double angle,
                                             pnt3d_t a);
TOPOCAPICALL topo_shape_t *
topo_shape_mirrored_from_point_norm(topo_shape_t *p, pnt3d_t pnt, pnt3d_t ner);
TOPOCAPICALL topo_shape_t *topo_shape_mirrored_from_axis1(topo_shape_t *p,
                                                          axis1_t a);
TOPOCAPICALL topo_shape_t *topo_shape_mirrored_from_axis2(topo_shape_t *p,
                                                          axis2_t a);
TOPOCAPICALL int topo_shape_get_orientation(topo_shape_t *p);
TOPOCAPICALL void topo_shape_set_orientation(topo_shape_t *p, int ori);
TOPOCAPICALL topo_location_t *topo_shape_get_location(topo_shape_t *p);
TOPOCAPICALL void topo_shape_set_location(topo_shape_t *p,
                                          topo_location_t *loc);
TOPOCAPICALL _Bool topo_shape_fix_shape(topo_shape_t *p);
TOPOCAPICALL topo_shape_t *topo_shape_copy(topo_shape_t *p);
TOPOCAPICALL int topo_shape_mesh(topo_shape_t *p,
                                 topo_mesh_receiver_t *receiver,
                                 double tolerance, double deflection,
                                 double angle, _Bool uv_coords);

TOPOCAPICALL void topo_shape_set_surface_colour(topo_shape_t *p, color_t c);
TOPOCAPICALL void topo_shape_set_curve_colour(topo_shape_t *p, color_t c);
TOPOCAPICALL void topo_shape_set_label(topo_shape_t *p, const char *name);
TOPOCAPICALL void topo_shape_set_u_origin(topo_shape_t *p, double u);
TOPOCAPICALL void topo_shape_set_v_origin(topo_shape_t *p, double v);
TOPOCAPICALL void topo_shape_set_u_repeat(topo_shape_t *p, double u);
TOPOCAPICALL void topo_shape_set_v_repeat(topo_shape_t *p, double v);
TOPOCAPICALL void topo_shape_set_scale_v(topo_shape_t *p, double v);
TOPOCAPICALL void topo_shape_set_scale_u(topo_shape_t *p, double u);
TOPOCAPICALL void topo_shape_set_auto_scale_size_on_u(topo_shape_t *p,
                                                      double u);
TOPOCAPICALL void topo_shape_set_auto_scale_size_on_v(topo_shape_t *p,
                                                      double v);
TOPOCAPICALL void topo_shape_set_txture_map_type(topo_shape_t *p, int t);
TOPOCAPICALL void topo_shape_set_rotation_angle(topo_shape_t *p, double angle);

TOPOCAPICALL color_t topo_shape_get_surface_colour(topo_shape_t *p);
TOPOCAPICALL color_t topo_shape_get_curve_colour(topo_shape_t *p);
TOPOCAPICALL const char *topo_shape_get_label(topo_shape_t *p);
TOPOCAPICALL _Bool topo_shape_surface_colour(topo_shape_t *p, double *colour);
TOPOCAPICALL double topo_shape_get_u_origin(topo_shape_t *p);
TOPOCAPICALL double topo_shape_get_v_origin(topo_shape_t *p);
TOPOCAPICALL double topo_shape_get_u_repeat(topo_shape_t *p);
TOPOCAPICALL double topo_shape_get_v_repeat(topo_shape_t *p);
TOPOCAPICALL double topo_shape_get_scale_v(topo_shape_t *p);
TOPOCAPICALL double topo_shape_get_scale_u(topo_shape_t *p);
TOPOCAPICALL double topo_shape_get_auto_scale_size_on_u(topo_shape_t *p);
TOPOCAPICALL double topo_shape_get_auto_scale_size_on_v(topo_shape_t *p);
TOPOCAPICALL int topo_shape_get_txture_map_type(topo_shape_t *p);
TOPOCAPICALL double topo_shape_get_rotation_angle(topo_shape_t *p);

TOPOCAPICALL pnt3d_t topo_shape_centre_of_mass(topo_shape_t *p);
TOPOCAPICALL double topo_shape_compute_mass(topo_shape_t *p);
TOPOCAPICALL double topo_shape_compute_area(topo_shape_t *p);

TOPOCAPICALL void topo_shape_list_free(topo_shape_t **result, int result_count);

TOPOCAPICALL topo_vertex_t topo_vertex_new(double x, double y, double z);
TOPOCAPICALL void topo_vertex_free(topo_vertex_t t);
TOPOCAPICALL pnt3d_t topo_vertex_get_point(topo_vertex_t t);

TOPOCAPICALL topo_wire_t topo_make_wire();

TOPOCAPICALL void topo_wire_free(topo_wire_t t);
TOPOCAPICALL topo_wire_t topo_make_polygon();
TOPOCAPICALL topo_wire_t topo_make_polygon_from_two_point(pnt3d_t P1,
                                                          pnt3d_t P2);
TOPOCAPICALL topo_wire_t topo_make_polygon_from_three_point(pnt3d_t P1,
                                                            pnt3d_t P2,
                                                            pnt3d_t P3,
                                                            _Bool Close);
TOPOCAPICALL topo_wire_t topo_make_polygon_from_four_point(
    pnt3d_t P1, pnt3d_t P2, pnt3d_t P3, pnt3d_t P4, _Bool Close);

TOPOCAPICALL topo_wire_t topo_make_polygon_two_vertex(topo_vertex_t V1,
                                                      topo_vertex_t V2);
TOPOCAPICALL topo_wire_t topo_make_polygon_from_three_vertex(topo_vertex_t V1,
                                                             topo_vertex_t V2,
                                                             topo_vertex_t V3,
                                                             _Bool Close);
TOPOCAPICALL topo_wire_t topo_make_polygon_from_four_vertex(topo_vertex_t V1,
                                                            topo_vertex_t V2,
                                                            topo_vertex_t V3,
                                                            topo_vertex_t V4,
                                                            _Bool Close);

TOPOCAPICALL topo_wire_t topo_make_wire_from_edge(topo_edge_t E);
TOPOCAPICALL topo_wire_t topo_make_wire_from_two_edge(topo_edge_t E1,
                                                      topo_edge_t E2);
TOPOCAPICALL topo_wire_t topo_make_wire_from_three_edge(topo_edge_t E1,
                                                        topo_edge_t E2,
                                                        topo_edge_t E3);
TOPOCAPICALL topo_wire_t topo_make_wire_from_four_edge(topo_edge_t E1,
                                                       topo_edge_t E2,
                                                       topo_edge_t E3,
                                                       topo_edge_t E4);

TOPOCAPICALL topo_wire_t topo_make_wire_from_wire(topo_wire_t W);
TOPOCAPICALL topo_wire_t topo_make_wire_from_two_wire(topo_wire_t W,
                                                      topo_edge_t E);

TOPOCAPICALL topo_wire_t topo_make_wire_from_edges(topo_edge_t *edges,
                                                   int count);
TOPOCAPICALL topo_wire_t topo_make_wire_from_wries(topo_wire_t *wires,
                                                   int count);

TOPOCAPICALL topo_wire_t topo_make_wire_from_rect(double width, double height);
TOPOCAPICALL topo_wire_t topo_make_wire_from_circle(double radius,
                                                    pnt3d_t center,
                                                    dir3d_t normal);
TOPOCAPICALL topo_wire_t
topo_make_wire_from_ellipse(double x_radius, double y_radius, pnt3d_t center,
                            dir3d_t normal, dir3d_t xDir, double angle1,
                            double angle2, double rotation_angle, _Bool closed);
TOPOCAPICALL topo_wire_t topo_make_wire_from_helix(double pitch, double height,
                                                   double radius,
                                                   pnt3d_t center, dir3d_t dir,
                                                   double angle,
                                                   _Bool lefthand);

enum {
  CURVE_LINE,
  CURVE_THREE_POINT_ARC,
  CURVE_CIRCLE_CENTER_ARC,
  CURVE_SPLINE
};
TOPOCAPICALL topo_wire_t topo_make_wire_from_combine_curve(pnt3d_t **points,
                                                           int *point_counts,
                                                           int curve_count,
                                                           int *curve_types);
TOPOCAPICALL topo_wire_t *topo_make_wire_from_combine(topo_wire_t *wires,
                                                      int count, double tol,
                                                      int *retCount);
TOPOCAPICALL void topo_wire_list_free(topo_wire_t *wires, int count);

TOPOCAPICALL topo_wire_t topo_wire_stitch(topo_wire_t w1, topo_wire_t w2);
TOPOCAPICALL int topo_wire_num_vertices(topo_wire_t w);
TOPOCAPICALL int topo_wire_num_edges(topo_wire_t w);
TOPOCAPICALL bool topo_wire_is_closed(topo_wire_t w);
TOPOCAPICALL double topo_wire_length(topo_wire_t w);
TOPOCAPICALL void topo_wire_convert_to_curves3d(topo_wire_t w);

TOPOCAPICALL topo_wire_t *topo_wire_offset2d(topo_wire_t w, double distance,
                                             int joinType, int *retCount);
TOPOCAPICALL topo_wire_t topo_wire_fillet2d(topo_wire_t w,
                                            topo_vertex_t *vertices,
                                            int vertcount, double radius);
TOPOCAPICALL topo_wire_t topo_wire_chamfer2d(topo_wire_t w,
                                             topo_vertex_t *vertices,
                                             int vertcount, double distance);

TOPOCAPICALL int topo_wire_project(topo_wire_t w, topo_face_t f);

TOPOCAPICALL int topo_wire_offset(topo_wire_t w, double distance, int joinType);

TOPOCAPICALL int topo_wire_fillet(topo_wire_t w, topo_vertex_t *vertices,
                                  int vertcount, double *radius, int radcount);
TOPOCAPICALL int topo_wire_chamfer(topo_wire_t w, topo_vertex_t *vertices,
                                   int vertcount, double *distances,
                                   int distcount);

TOPOCAPICALL void topo_wire_bounds(topo_wire_t w, double *min, double *max);
TOPOCAPICALL pnt3d_t topo_wire_start_point(topo_wire_t w);
TOPOCAPICALL pnt3d_t topo_wire_end_point(topo_wire_t w);
TOPOCAPICALL double topo_wire_param_at(topo_wire_t w, double d);
TOPOCAPICALL double topo_wire_param_at_point(topo_wire_t w, pnt3d_t pt);
TOPOCAPICALL void topo_wire_params(topo_wire_t w, pnt3d_t *pts, int count,
                                   double *params, double tol);
TOPOCAPICALL void topo_wire_params_length(topo_wire_t w, double *locations,
                                          int count, double *params);
TOPOCAPICALL dir3d_t topo_wire_tangent_at(topo_wire_t w, double param);
TOPOCAPICALL void topo_wire_tangents(topo_wire_t w, double *params, int count,
                                     dir3d_t *tangents);
TOPOCAPICALL dir3d_t topo_wire_normal(topo_wire_t w);
TOPOCAPICALL pnt3d_t topo_wire_center(topo_wire_t w);
TOPOCAPICALL double topo_wire_radius(topo_wire_t w);
TOPOCAPICALL pnt3d_t topo_wire_position_at(topo_wire_t w, double d, int mode);
TOPOCAPICALL void topo_wire_positions(topo_wire_t w, double *ds, int count,
                                      pnt3d_t *points, int mode);
TOPOCAPICALL void topo_wire_sample_uniform(topo_wire_t w, double n,
                                           pnt3d_t **points, int *point_count,
                                           double **params, int *param_count);
TOPOCAPICALL topo_location_t *topo_wire_location_at(topo_wire_t w, double d,
                                                    int mode, int frame,
                                                    bool planar);
TOPOCAPICALL topo_location_t **topo_wire_locations(topo_wire_t w, double *ds,
                                                   int count, int mode,
                                                   int frame, bool planar,
                                                   int *result_count);
TOPOCAPICALL int topo_wire_projected(topo_wire_t w, topo_face_t f,
                                     vec3d_t direction, bool closest,
                                     topo_shape_t ***result, int *result_count);
TOPOCAPICALL double topo_wire_curvature_at(topo_wire_t w, double d, int mode,
                                           double resolution);
TOPOCAPICALL void topo_wire_curvatures(topo_wire_t w, double *ds, int count,
                                       double *curvatures, int mode,
                                       double resolution);

TOPOCAPICALL topo_edge_t topo_make_edge();

TOPOCAPICALL void topo_edge_free(topo_edge_t t);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_points(pnt3d_t *pts,
                                                         int size);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_two_vertex(topo_vertex_t V1,
                                                             topo_vertex_t V2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_two_point(pnt3d_t P1,
                                                            pnt3d_t P2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_line(line_t L);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_line_p(line_t L, double p1,
                                                         double p2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_line_point(line_t L,
                                                             pnt3d_t P1,
                                                             pnt3d_t P2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_line_vertex(line_t L,
                                                              topo_vertex_t V1,
                                                              topo_vertex_t V2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_circ(circ_t L);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_circ_p(circ_t L, double p1,
                                                         double p2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_circ_point(circ_t L,
                                                             pnt3d_t P1,
                                                             pnt3d_t P2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_circ_vertex(circ_t L,
                                                              topo_vertex_t V1,
                                                              topo_vertex_t V2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_elips(elips_t L);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_elips_p(elips_t L, double p1,
                                                          double p2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_elips_point(elips_t L,
                                                              pnt3d_t P1,
                                                              pnt3d_t P2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_elips_vertex(
    elips_t L, topo_vertex_t V1, topo_vertex_t V2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_hyper(hyperbola_t L);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_hyper_p(hyperbola_t L,
                                                          double p1, double p2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_hyper_point(hyperbola_t L,
                                                              pnt3d_t P1,
                                                              pnt3d_t P2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_hyper_vertex(
    hyperbola_t L, topo_vertex_t V1, topo_vertex_t V2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_parab(parabola_t L);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_parab_p(parabola_t L,
                                                          double p1, double p2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_parab_point(parabola_t L,
                                                              pnt3d_t P1,
                                                              pnt3d_t P2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_parab_vertex(
    parabola_t L, topo_vertex_t V1, topo_vertex_t V2);

TOPOCAPICALL topo_edge_t topo_edge_make_edgee_from_curve(geom_curve_t *L);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_curve_p(geom_curve_t *L,
                                                          double p1, double p2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_curve_point(geom_curve_t *L,
                                                              pnt3d_t P1,
                                                              pnt3d_t P2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_curve_vertex(
    geom_curve_t *L, topo_vertex_t V1, topo_vertex_t V2);

TOPOCAPICALL topo_edge_t topo_edge_make_edgee_from_curve_point_p(
    geom_curve_t *L, pnt3d_t P1, pnt3d_t P2, double p1, double p2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_curve_vertex_p(
    geom_curve_t *L, topo_vertex_t V1, topo_vertex_t V2, double p1, double p2);

TOPOCAPICALL topo_edge_t
topo_edge_make_edge_from_curve_surface(geom2d_curve_t *L, geom_surface_t *S);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_curve_surface_p(
    geom2d_curve_t *L, geom_surface_t *S, double p1, double p2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_curve_surface_point(
    geom2d_curve_t *L, geom_surface_t *S, pnt3d_t P1, pnt3d_t P2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_curve_surface_vertex(
    geom2d_curve_t *L, geom_surface_t *S, topo_vertex_t V1, topo_vertex_t V2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_curve_surface_point_p(
    geom2d_curve_t *L, geom_surface_t *S, pnt3d_t P1, pnt3d_t P2, double p1,
    double p2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_curve_surface_vertex_p(
    geom2d_curve_t *L, geom_surface_t *S, topo_vertex_t V1, topo_vertex_t V2,
    double p1, double p2);

TOPOCAPICALL topo_edge_t
topo_edge_make_edge2d_from_two_vertex(topo_vertex_t V1, topo_vertex_t V2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge2d_from_two_point(pnt2d_t P1,
                                                              pnt2d_t P2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge2d_from_line(line2d_t L);

TOPOCAPICALL topo_edge_t topo_edge_make_edge2d_from_line_p(line2d_t L,
                                                           double p1,
                                                           double p2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge2d_from_line_point(line2d_t L,
                                                               pnt2d_t P1,
                                                               pnt2d_t P2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge2d_from_line_vertex(
    line2d_t L, topo_vertex_t V1, topo_vertex_t V2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge2d_from_circ(circ2d_t L);

TOPOCAPICALL topo_edge_t topo_edge_make_edge2d_from_circ_p(circ2d_t L,
                                                           double p1,
                                                           double p2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge2d_from_circ_point(circ2d_t L,
                                                               pnt2d_t P1,
                                                               pnt2d_t P2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge2d_from_circ_vertex(
    circ2d_t L, topo_vertex_t V1, topo_vertex_t V2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge2d_from_elips(elips2d_t L);

TOPOCAPICALL topo_edge_t topo_edge_make_edge2d_from_elips_p(elips2d_t L,
                                                            double p1,
                                                            double p2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge2d_from_elips_point(elips2d_t L,
                                                                pnt2d_t P1,
                                                                pnt2d_t P2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge2d_from_elips_vertex(
    elips2d_t L, topo_vertex_t V1, topo_vertex_t V2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge2d_from_hyper(hyperbola2d_t L);

TOPOCAPICALL topo_edge_t topo_edge_make_edge2d_from_hyper_p(hyperbola2d_t L,
                                                            double p1,
                                                            double p2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge2d_from_hyper_point(hyperbola2d_t L,
                                                                pnt2d_t P1,
                                                                pnt2d_t P2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge2d_from_hyper_vertex(
    hyperbola2d_t L, topo_vertex_t V1, topo_vertex_t V2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge2d_from_parab(parabola2d_t L);

TOPOCAPICALL topo_edge_t topo_edge_make_edge2d_from_parab_p(parabola2d_t L,
                                                            double p1,
                                                            double p2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge2d_from_parab_point(parabola2d_t L,
                                                                pnt2d_t P1,
                                                                pnt2d_t P2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge2d_from_parab_vertex(
    parabola2d_t L, topo_vertex_t V1, topo_vertex_t V2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge2d_from_curve(geom2d_curve_t *L);

TOPOCAPICALL topo_edge_t topo_edge_make_edge2d_from_curve_p(geom2d_curve_t *L,
                                                            double p1,
                                                            double p2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge2d_from_curve_point(
    geom2d_curve_t *L, pnt2d_t P1, pnt2d_t P2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge2d_from_curve_vertex(
    geom2d_curve_t *L, topo_vertex_t V1, topo_vertex_t V2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge2d_from_curve_point_p(
    geom2d_curve_t *L, pnt2d_t P1, pnt2d_t P2, double p1, double p2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge2d_from_curve_vertex_p(
    geom2d_curve_t *L, topo_vertex_t V1, topo_vertex_t V2, double p1,
    double p2);

TOPOCAPICALL topo_edge_t topo_edge_make_polygon();

TOPOCAPICALL topo_edge_t topo_edge_make_polygon_from_two_point(pnt3d_t P1,
                                                               pnt3d_t P2);

TOPOCAPICALL topo_edge_t topo_edge_make_polygon_from_three_point(pnt3d_t P1,
                                                                 pnt3d_t P2,
                                                                 pnt3d_t P3,
                                                                 _Bool Close);

TOPOCAPICALL topo_edge_t topo_edge_make_polygon_from_four_point(
    pnt3d_t P1, pnt3d_t P2, pnt3d_t P3, pnt3d_t P4, _Bool Close);

TOPOCAPICALL topo_edge_t
topo_edge_make_polygon_from_two_vertex(topo_vertex_t V1, topo_vertex_t V2);

TOPOCAPICALL topo_edge_t topo_edge_make_polygon_from_three_vertex(
    topo_vertex_t V1, topo_vertex_t V2, topo_vertex_t V3, _Bool Close);

TOPOCAPICALL topo_edge_t topo_edge_make_polygon_from_four_vertex(
    topo_vertex_t V1, topo_vertex_t V2, topo_vertex_t V3, topo_vertex_t V4,
    _Bool Close);

TOPOCAPICALL topo_edge_t topo_edge_make_polygon_from_vertices(
    topo_vertex_t *vertices, int vertcount, _Bool Close);
TOPOCAPICALL topo_edge_t topo_edge_make_polygonn_from_points(pnt3d_t *vertexs,
                                                             int vertcount,
                                                             _Bool Close);
TOPOCAPICALL topo_edge_t topo_edge_make_rect(double width, double height);
TOPOCAPICALL topo_edge_t topo_edge_make_spline(pnt3d_t *vertexs, int vertcount,
                                               double tol, bool periodic);
TOPOCAPICALL topo_edge_t topo_edge_make_spline_from_tangents_and_parameters(
    pnt3d_t *points, int pntcount, vec3d_t *tangents, int tancount,
    double *parameters, int paramcount, double tol, bool periodic, bool scale);
TOPOCAPICALL topo_edge_t
topo_edge_make_spline_approx(pnt3d_t *points, int pntcount, double tolerance,
                             double *smoothing, int minDegree, int maxDegree);
TOPOCAPICALL topo_edge_t topo_edge_make_catenary(pnt3d_t p1, pnt3d_t p2,
                                                 double slack, double maxSag,
                                                 dir3d_t up,
                                                 double tessellation);
TOPOCAPICALL topo_edge_t topo_edge_make_circle(double radius, pnt3d_t center,
                                               vec3d_t normal, double angle1,
                                               double angle2, bool orientation);
TOPOCAPICALL topo_edge_t topo_edge_make_ellipse(double majorRadius,
                                                double minorRadius,
                                                pnt3d_t center, vec3d_t normal,
                                                vec3d_t xnormal, double angle1,
                                                double angle2, int sense);
TOPOCAPICALL topo_edge_t topo_edge_make_bezier(pnt3d_t *points, int pntcount);
TOPOCAPICALL topo_edge_t topo_edge_make_three_point_arc(pnt3d_t v1, pnt3d_t v2,
                                                        pnt3d_t v3);
TOPOCAPICALL topo_edge_t topo_edge_make_circle_center_arc(pnt3d_t v1,
                                                          pnt3d_t center,
                                                          pnt3d_t v2);

TOPOCAPICALL topo_edge_t topo_edge_make_tangent_arc(pnt3d_t v1, vec3d_t tangent,
                                                    pnt3d_t v3);
TOPOCAPICALL bool topo_edge_is_seam(topo_edge_t e, topo_face_t f);
TOPOCAPICALL bool topo_edge_is_degenerated(topo_edge_t e);
TOPOCAPICALL bool topo_edge_is_closed(topo_edge_t e);
TOPOCAPICALL bool topo_edge_is_inifinite(topo_edge_t e);
TOPOCAPICALL int topo_edge_num_vertices(topo_edge_t e);
TOPOCAPICALL double topo_edge_length(topo_edge_t e);
TOPOCAPICALL float topo_edge_tolerance(topo_edge_t e);
TOPOCAPICALL bool topo_edge_is_curve3d(topo_edge_t e);
TOPOCAPICALL void topo_edge_convert_to_curve3d(topo_edge_t e);
TOPOCAPICALL void topo_edge_reverse(topo_edge_t e);

TOPOCAPICALL void topo_edge_bounds(topo_edge_t e, double *min, double *max);
TOPOCAPICALL double topo_edge_length(topo_edge_t e);
TOPOCAPICALL bool topo_edge_is_closed(topo_edge_t e);
TOPOCAPICALL pnt3d_t topo_edge_start_point(topo_edge_t e);
TOPOCAPICALL pnt3d_t topo_edge_end_point(topo_edge_t e);
TOPOCAPICALL double topo_edge_param_at(topo_edge_t e, double d);
TOPOCAPICALL double topo_edge_param_at_point(topo_edge_t e, pnt3d_t pt);
TOPOCAPICALL void topo_edge_params(topo_edge_t e, pnt3d_t *pts, int count,
                                   double *params, double tol);
TOPOCAPICALL void topo_edge_params_length(topo_edge_t e, double *locations,
                                          int count, double *params);
TOPOCAPICALL dir3d_t topo_edge_tangent_at(topo_edge_t e, double param);
TOPOCAPICALL void topo_edge_tangents(topo_edge_t e, double *params, int count,
                                     dir3d_t *tangents);
TOPOCAPICALL dir3d_t topo_edge_normal(topo_edge_t e);
TOPOCAPICALL pnt3d_t topo_edge_center(topo_edge_t e);
TOPOCAPICALL double topo_edge_radius(topo_edge_t e);
TOPOCAPICALL pnt3d_t topo_edge_position_at(topo_edge_t e, double d, int mode);
TOPOCAPICALL void topo_edge_positions(topo_edge_t e, double *ds, int count,
                                      pnt3d_t *points, int mode);
TOPOCAPICALL void topo_edge_sample_uniform(topo_edge_t e, double n,
                                           pnt3d_t **points, int *point_count,
                                           double **params, int *param_count);
TOPOCAPICALL topo_location_t *topo_edge_location_at(topo_edge_t e, double d,
                                                    int mode, int frame,
                                                    bool planar);
TOPOCAPICALL topo_location_t **topo_edge_locations(topo_edge_t e, double *ds,
                                                   int count, int mode,
                                                   int frame, bool planar,
                                                   int *result_count);
TOPOCAPICALL int topo_edge_projected(topo_edge_t e, topo_face_t f,
                                     vec3d_t direction, bool closest,
                                     topo_shape_t ***result, int *result_count);
TOPOCAPICALL double topo_edge_curvature_at(topo_edge_t e, double d, int mode,
                                           double resolution);
TOPOCAPICALL void topo_edge_curvatures(topo_edge_t e, double *ds, int count,
                                       double *curvatures, int mode,
                                       double resolution);

TOPOCAPICALL void topo_face_free(topo_face_t t);

TOPOCAPICALL topo_face_t topo_make_face();

TOPOCAPICALL topo_face_t topo_face_make_face(topo_face_t F);

TOPOCAPICALL topo_face_t topo_face_make_face_from_plane(plane_t P);

TOPOCAPICALL topo_face_t topo_face_make_face_from_cylinder(cylinder_t C);

TOPOCAPICALL topo_face_t topo_face_make_face_from_cone(cone_t C);

TOPOCAPICALL topo_face_t topo_face_make_face_from_sphere(sphere_t S);

TOPOCAPICALL topo_face_t topo_face_make_face_from_torus(torus_t C);

TOPOCAPICALL topo_face_t topo_face_make_face_from_surface(geom_surface_t *S,
                                                          double TolDegen);

TOPOCAPICALL topo_face_t topo_face_make_face_from_plane_p(
    plane_t P, double UMin, double UMax, double VMin, double VMax);

TOPOCAPICALL topo_face_t topo_face_make_face_from_cylinder_p(
    cylinder_t C, double UMin, double UMax, double VMin, double VMax);

TOPOCAPICALL topo_face_t topo_face_make_face_from_cone_p(cone_t C, double UMin,
                                                         double UMax,
                                                         double VMin,
                                                         double VMax);

TOPOCAPICALL topo_face_t topo_face_make_face_from_sphere_p(
    sphere_t S, double UMin, double UMax, double VMin, double VMax);

TOPOCAPICALL topo_face_t topo_face_make_face_from_torus_p(
    torus_t C, double UMin, double UMax, double VMin, double VMax);

TOPOCAPICALL topo_face_t
topo_face_make_face_from_surface_p(geom_surface_t *S, double UMin, double UMax,
                                   double VMin, double VMax, double TolDegen);

TOPOCAPICALL topo_face_t
topo_face_make_face_from_wire_onlyplane(topo_wire_t W, _Bool OnlyPlane);

TOPOCAPICALL topo_face_t topo_face_make_face_from_plane_wire(plane_t P,
                                                             topo_wire_t W,
                                                             _Bool Inside);

TOPOCAPICALL topo_face_t topo_face_make_face_from_cylinder_wire(cylinder_t C,
                                                                topo_wire_t W,
                                                                _Bool Inside);

TOPOCAPICALL topo_face_t topo_face_make_face_from_cone_wire(cone_t C,
                                                            topo_wire_t W,
                                                            _Bool Inside);

TOPOCAPICALL topo_face_t topo_face_make_face_from_sphere_wire(sphere_t S,
                                                              topo_wire_t W,
                                                              _Bool Inside);

TOPOCAPICALL topo_face_t topo_face_make_face_from_torus_wire(torus_t C,
                                                             topo_wire_t W,
                                                             _Bool Inside);

TOPOCAPICALL topo_face_t topo_face_make_face_from_surface_wire(
    geom_surface_t *S, topo_wire_t W, _Bool Inside);

TOPOCAPICALL topo_face_t topo_face_make_face_from_face_wire(topo_face_t F,
                                                            topo_wire_t W);

TOPOCAPICALL topo_face_t topo_face_make_face_from_wire(topo_wire_t *wires,
                                                       int count);

TOPOCAPICALL topo_face_t topo_face_make_face_from_egdes(topo_edge_t *edges,
                                                        int edgecount,
                                                        pnt3d_t *points,
                                                        int pcount);

TOPOCAPICALL topo_face_t topo_face_make_face_from_points(pnt3d_t *points,
                                                         int count);

TOPOCAPICALL topo_face_t *topo_face_make_from_wires(topo_wire_t outer,
                                                    topo_wire_t *inners,
                                                    int inner_count,
                                                    int *result_count);
TOPOCAPICALL void topo_face_list_free(topo_face_t *faces, int count);
TOPOCAPICALL topo_face_t topo_face_make_complex(
    topo_shape_t **edges, int edge_count, topo_shape_t **constraints,
    int constraint_count, int continuity, int degree, int nb_pts_on_curve,
    int nb_iter, bool anisotropy, double tol2d, double tol3d, double tol_angle,
    double tol_curv, int max_degree, int max_segments);

TOPOCAPICALL topo_face_t topo_face_make_plane(pnt3d_t base_point,
                                              dir3d_t direction, double *length,
                                              double *width);

TOPOCAPICALL topo_face_t topo_face_make_spline_approx(
    pnt3d_t *points, int *point_counts, int point_array_size, double tol,
    double *smoothing, int min_degree, int max_degree);

TOPOCAPICALL int topo_face_num_wires(topo_face_t f);

TOPOCAPICALL int topo_face_num_faces(topo_face_t f);

TOPOCAPICALL double topo_face_area(topo_face_t f);

TOPOCAPICALL float topo_face_tolerance(topo_face_t f);

TOPOCAPICALL bbox_t topo_face_inertia(topo_face_t f);

TOPOCAPICALL pnt3d_t topo_face_centre_of_mass(topo_face_t f);

TOPOCAPICALL topo_plane_t *topo_face_to_plane(topo_face_t f);

TOPOCAPICALL int topo_face_offset(topo_face_t f, double offset,
                                  double tolerance);

TOPOCAPICALL int topo_face_extrude(topo_face_t f, topo_shape_t *shp, pnt3d_t p1,
                                   pnt3d_t p2);

TOPOCAPICALL int topo_face_revolve(topo_face_t f, topo_shape_t *shp, pnt3d_t p1,
                                   pnt3d_t p2, double angle);

TOPOCAPICALL int topo_face_sweep(topo_face_t f, topo_wire_t spine,
                                 topo_shape_t **profiles, int profilesCount,
                                 int cornerMode);
TOPOCAPICALL int topo_face_sweep_wire(topo_face_t ss, topo_wire_t spine,
                                      topo_wire_t *profiles, int count,
                                      int cornerMode);

TOPOCAPICALL int topo_face_loft(topo_face_t f, topo_shape_t **profiles,
                                int profilesCount, bool ruled,
                                double tolerance);

TOPOCAPICALL int topo_face_boolean(topo_face_t f, topo_face_t tool, int op);
TOPOCAPICALL void topo_face_uv_bounds(topo_face_t f, double *u_min,
                                      double *u_max, double *v_min,
                                      double *v_max);
TOPOCAPICALL void topo_face_param_at(topo_face_t f, pnt3d_t pt, double *u,
                                     double *v);
TOPOCAPICALL void topo_face_params(topo_face_t f, pnt3d_t *pts, int count,
                                   double *us, double *vs, double tol);
TOPOCAPICALL pnt3d_t topo_face_position_at(topo_face_t f, double u, double v);
TOPOCAPICALL void topo_face_positions(topo_face_t f, double *us, double *vs,
                                      int count, pnt3d_t *points);
TOPOCAPICALL vec3d_t topo_face_normal_at(topo_face_t f, pnt3d_t *location);
TOPOCAPICALL void topo_face_normal_at_uv(topo_face_t f, double u, double v,
                                         vec3d_t *normal, pnt3d_t *point);
TOPOCAPICALL void topo_face_normals(topo_face_t f, double *us, double *vs,
                                    int count, vec3d_t *normals,
                                    pnt3d_t *points);

TOPOCAPICALL topo_face_t topo_face_fillet2d(topo_face_t f, double radius,
                                            topo_vertex_t *vertices, int count);
TOPOCAPICALL topo_face_t topo_face_chamfer2d(topo_face_t f, double distance,
                                             topo_vertex_t *vertices,
                                             int count);
TOPOCAPICALL topo_solid_t topo_face_thicken(topo_face_t f, double thickness);
TOPOCAPICALL topo_face_t topo_face_project(topo_face_t f, topo_face_t other,
                                           vec3d_t direction);
TOPOCAPICALL topo_face_t topo_face_to_arcs(topo_face_t f, double tolerance);
TOPOCAPICALL topo_face_t topo_face_trim(topo_face_t f, double u0, double u1,
                                        double v0, double v1, double tol);
TOPOCAPICALL topo_edge_t topo_face_isoline(topo_face_t f, double param,
                                           const char *direction);
TOPOCAPICALL topo_edge_t *topo_face_isolines(topo_face_t f, double *params,
                                             int count, const char *direction,
                                             int *result_count);
TOPOCAPICALL topo_wire_t topo_face_outer_wire(topo_face_t f);
TOPOCAPICALL topo_wire_t *topo_face_inner_wires(topo_face_t f, int *count);

TOPOCAPICALL void topo_shell_free(topo_shell_t t);

TOPOCAPICALL topo_shell_t topo_make_shell();

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_surface(geom_surface_t *S,
                                                             _Bool Segment);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_surface_p(
    geom_surface_t *S, double UMin, double UMax, double VMin, double VMax,
    _Bool Segment);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_box(double dx, double dy,
                                                         double dz);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_box_point(pnt3d_t P,
                                                               double dx,
                                                               double dy,
                                                               double dz);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_box_two_point(pnt3d_t P1,
                                                                   pnt3d_t P2);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_box_axis2(axis2_t Axes,
                                                               double dx,
                                                               double dy,
                                                               double dz);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_cylinder(double R,
                                                              double H);

TOPOCAPICALL topo_shell_t
topo_shell_make_shell_from_cylinder_angle(double R, double H, double Angle);

TOPOCAPICALL topo_shell_t
topo_shell_make_shell_from_cylinder_axis2(axis2_t Axes, double R, double H);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_cylinder_axis2_angle(
    axis2_t Axes, double R, double H, double Angle);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_cone(double R1, double R2,
                                                          double H);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_cone_angle(double R1,
                                                                double R2,
                                                                double H,
                                                                double angle);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_cone_axis2(axis2_t Axes,
                                                                double R1,
                                                                double R2,
                                                                double H);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_cone_axis2_angle(
    axis2_t Axes, double R1, double R2, double H, double angle);

TOPOCAPICALL topo_shell_t
topo_shell_make_shell_from_revolution(geom_curve_t *Meridian);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_revolution_angle(
    geom_curve_t *Meridian, double angle);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_revolution_limit(
    geom_curve_t *Meridian, double VMin, double VMax);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_revolution_limit_angle(
    geom_curve_t *Meridian, double VMin, double VMax, double angle);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_revolution_axis2(
    axis2_t Axes, geom_curve_t *Meridian);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_revolution_axis2_angle(
    axis2_t Axes, geom_curve_t *Meridian, double angle);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_revolution_axis2_limit(
    axis2_t Axes, geom_curve_t *Meridian, double VMin, double VMax);

TOPOCAPICALL topo_shell_t
topo_shell_make_shell_from_revolution_axis2_limit_angle(axis2_t Axes,
                                                        geom_curve_t *Meridian,
                                                        double VMin,
                                                        double VMax,
                                                        double angle);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_sphere(double R);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_sphere_angle(double R,
                                                                  double angle);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_sphere_two_angle(
    double R, double angle1, double angle2);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_sphere_three_angle(
    double R, double angle1, double angle2, double angle3);

TOPOCAPICALL topo_shell_t
topo_shell_make_shell_from_sphere_center_raduis(pnt3d_t Center, double R);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_sphere_center_angle(
    pnt3d_t Center, double R, double angle);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_sphere_center_two_angle(
    pnt3d_t Center, double R, double angle1, double angle2);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_sphere_center_three_angle(
    pnt3d_t Center, double R, double angle1, double angle2, double angle3);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_sphere_axis2(axis2_t Axis,
                                                                  double R);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_sphere_axis2_raduis(
    axis2_t Axis, double R, double angle);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_sphere_axis2_two_angle(
    axis2_t Axis, double R, double angle1, double angle2);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_sphere_axis2_three_angle(
    axis2_t Axis, double R, double angle1, double angle2, double angle3);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_torus(double R1,
                                                           double R2);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_torus_angle(double R1,
                                                                 double R2,
                                                                 double angle);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_torus_two_angle(
    double R1, double R2, double angle1, double angle2);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_torus_three_angle(
    double R1, double R2, double angle1, double angle2, double angle);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_torus_axis2(axis2_t Axes,
                                                                 double R1,
                                                                 double R2);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_torus_axis2_angle(
    axis2_t Axes, double R1, double R2, double angle);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_torus_axis2_two_angle(
    axis2_t Axes, double R1, double R2, double angle1, double angle2);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_torus_axis2_three_angle(
    axis2_t Axes, double R1, double R2, double angle1, double angle2,
    double angle);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_wedge(double dx, double dy,
                                                           double dz,
                                                           double ltx);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_wedge_axis2(
    axis2_t Axes, double dx, double dy, double dz, double ltx);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_wedge_limit(
    double dx, double dy, double dz, double xmin, double zmin, double xmax,
    double zmax);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_wedge_axis2_limit(
    axis2_t Axes, double dx, double dy, double dz, double xmin, double zmin,
    double xmax, double zmax);

TOPOCAPICALL int topo_shell_sweep(topo_shell_t ss, topo_wire_t spine,
                                  topo_shape_t **profiles, int count,
                                  int cornerMode);

TOPOCAPICALL int topo_shell_sweep_wire(topo_shell_t ss, topo_wire_t spine,
                                       topo_wire_t *profiles, int count,
                                       int cornerMode);

TOPOCAPICALL void topo_solid_free(topo_solid_t t);

TOPOCAPICALL topo_solid_t
topo_solid_make_solid_from_comp_solid(topo_comp_solid_t S);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_shell(topo_shell_t S);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_two_shell(topo_shell_t S1,
                                                               topo_shell_t S2);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_three_shell(
    topo_shell_t S1, topo_shell_t S2, topo_shell_t S3);

TOPOCAPICALL topo_solid_t
topo_solid_make_solid_from_shells(topo_shell_t *shells, int count);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_solid(topo_solid_t So);

TOPOCAPICALL topo_solid_t
topo_solid_make_solid_from_solid_shell(topo_solid_t So, topo_shell_t S);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_faces(topo_face_t *faces,
                                                           int count,
                                                           double tolerance);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_box(double dx, double dy,
                                                         double dz);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_box_point(pnt3d_t P,
                                                               double dx,
                                                               double dy,
                                                               double dz);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_box_two_point(pnt3d_t P1,
                                                                   pnt3d_t P2);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_box_axis2(axis2_t Axes,
                                                               double dx,
                                                               double dy,
                                                               double dz);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_cylinder(double R,
                                                              double H);

TOPOCAPICALL topo_solid_t
topo_solid_make_solid_from_cylinder_angle(double R, double H, double Angle);

TOPOCAPICALL topo_solid_t
topo_solid_make_solid_from_cylinder_axis2(axis2_t Axes, double R, double H);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_cylinder_axis2_angle(
    axis2_t Axes, double R, double H, double Angle);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_cone(double R1, double R2,
                                                          double H);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_cone_angle(double R1,
                                                                double R2,
                                                                double H,
                                                                double angle);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_cone_axis2(axis2_t Axes,
                                                                double R1,
                                                                double R2,
                                                                double H);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_cone_axis2_angle(
    axis2_t Axes, double R1, double R2, double H, double angle);

TOPOCAPICALL topo_solid_t
topo_solid_make_solid_from_revolution(geom_curve_t *Meridian);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_revolution_angle(
    geom_curve_t *Meridian, double angle);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_revolution_limit(
    geom_curve_t *Meridian, double VMin, double VMax);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_revolution_limit_angle(
    geom_curve_t *Meridian, double VMin, double VMax, double angle);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_revolution_axis2(
    axis2_t Axes, geom_curve_t *Meridian);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_revolution_axis2_angle(
    axis2_t Axes, geom_curve_t *Meridian, double angle);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_revolution_axis2_limit(
    axis2_t Axes, geom_curve_t *Meridian, double VMin, double VMax);

TOPOCAPICALL topo_solid_t
topo_solid_make_solid_from_revolution_axis2_limit_angle(axis2_t Axes,
                                                        geom_curve_t *Meridian,
                                                        double VMin,
                                                        double VMax,
                                                        double angle);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_sphere(double R);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_sphere_angle(double R,
                                                                  double angle);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_sphere_two_angle(
    double R, double angle1, double angle2);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_sphere_three_angle(
    double R, double angle1, double angle2, double angle3);

TOPOCAPICALL topo_solid_t
topo_solid_make_solid_from_sphere_center_raduis(pnt3d_t Center, double R);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_sphere_center_angle(
    pnt3d_t Center, double R, double angle);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_sphere_center_two_angle(
    pnt3d_t Center, double R, double angle1, double angle2);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_sphere_center_three_angle(
    pnt3d_t Center, double R, double angle1, double angle2, double angle3);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_sphere_axis2(axis2_t Axis,
                                                                  double R);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_sphere_axis2_angle(
    axis2_t Axis, double R, double angle);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_sphere_axis2_two_angle(
    axis2_t Axis, double R, double angle1, double angle2);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_sphere_axis2_three_angle(
    axis2_t Axis, double R, double angle1, double angle2, double angle3);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_torus(double R1,
                                                           double R2);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_torus_angle(double R1,
                                                                 double R2,
                                                                 double angle);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_torus_two_angle(
    double R1, double R2, double angle1, double angle2);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_torus_three_angle(
    double R1, double R2, double angle1, double angle2, double angle);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_torus_axis2(axis2_t Axes,
                                                                 double R1,
                                                                 double R2);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_torus_axis2_angle(
    axis2_t Axes, double R1, double R2, double angle);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_torus_axis2_two_angle(
    axis2_t Axes, double R1, double R2, double angle1, double angle2);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_torus_axis2_three_angle(
    axis2_t Axes, double R1, double R2, double angle1, double angle2,
    double angle);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_wedge(double dx, double dy,
                                                           double dz,
                                                           double ltx);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_wedge_axis2(
    axis2_t Axes, double dx, double dy, double dz, double ltx);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_wedge_limit(
    double dx, double dy, double dz, double xmin, double zmin, double xmax,
    double zmax);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_wedge_axis2_limit(
    axis2_t Axes, double dx, double dy, double dz, double xmin, double zmin,
    double xmax, double zmax);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_loft(topo_wire_t *wires,
                                                          int count,
                                                          _Bool ruled);

TOPOCAPICALL _Bool topo_solid_is_inside(topo_solid_t s, pnt3d_t p, double tol);

TOPOCAPICALL int topo_solid_num_solids(topo_solid_t s);

TOPOCAPICALL int topo_solid_num_faces(topo_solid_t s);

TOPOCAPICALL double topo_solid_area(topo_solid_t s);

TOPOCAPICALL double topo_solid_volume(topo_solid_t s);

TOPOCAPICALL bbox_t topo_solid_inertia(topo_solid_t s);

TOPOCAPICALL pnt3d_t topo_solid_centre_of_mass(topo_solid_t s);

TOPOCAPICALL int topo_solid_extrude_with_rotation(
    topo_solid_t s, topo_wire_t outerWire, topo_wire_t *innerWires,
    int innerCount, pnt3d_t vecCenter, vec3d_t vecNormal, double angleDegrees);

TOPOCAPICALL int
topo_solid_extrude_with_rotation_from_face(topo_solid_t s, topo_face_t face,
                                           pnt3d_t vecCenter, vec3d_t vecNormal,
                                           double angleDegrees);

TOPOCAPICALL int topo_solid_extrude(topo_solid_t s, topo_face_t f, pnt3d_t p1,
                                    pnt3d_t p2);

TOPOCAPICALL int topo_solid_extrude_from_dir(topo_solid_t s, topo_face_t f,
                                             vec3d_t dir);

TOPOCAPICALL int topo_solid_extrude_with_rotation_from_wire(
    topo_solid_t s, topo_wire_t outerWire, topo_wire_t *innerWires,
    int innerCount, pnt3d_t vecCenter, vec3d_t vecNormal, double angleDegrees);

TOPOCAPICALL int
topo_solid_extrude_with_rotation_from_face(topo_solid_t s, topo_face_t face,
                                           pnt3d_t vecCenter, vec3d_t vecNormal,
                                           double angleDegrees);

TOPOCAPICALL int topo_solid_revolve(topo_solid_t s, topo_face_t f, pnt3d_t p1,
                                    pnt3d_t p2, double angle);

TOPOCAPICALL int topo_solid_loft(topo_solid_t s, topo_shape_t **profiles,
                                 int count, _Bool ruled, double tolerance);

TOPOCAPICALL int topo_solid_pipe(topo_solid_t s, topo_face_t f, topo_wire_t w);

typedef struct {
  topo_shape_t *profile;
  int index; // -1为NULL
} topo_sweep_profile_t;

TOPOCAPICALL int topo_solid_sweep_compound(topo_solid_t s, topo_wire_t spine,
                                           topo_sweep_profile_t *profiles,
                                           int profile_count, int corner_mode);

TOPOCAPICALL int topo_solid_sweep(topo_solid_t s, topo_wire_t spine,
                                  topo_shape_t **profiles, int count,
                                  int cornerMode);
TOPOCAPICALL int topo_solid_sweep_wire(topo_solid_t s, topo_wire_t spine,
                                       topo_wire_t *profiles, int count,
                                       int cornerMode);

TOPOCAPICALL int topo_solid_sweep_multi_from_vector(
    topo_solid_t s, topo_shape_t **profiles, int count, topo_shape_t *path,
    _Bool makeSolid, _Bool isFrenet, topo_vector_t *vec);

TOPOCAPICALL int
topo_solid_sweep_multi_from_wire(topo_solid_t s, topo_shape_t **profiles,
                                 int count, topo_shape_t *path, _Bool makeSolid,
                                 _Bool isFrenet, topo_wire_t *wire);

TOPOCAPICALL int
topo_solid_sweep_multi_from_edge(topo_solid_t s, topo_shape_t **profiles,
                                 int count, topo_shape_t *path, _Bool makeSolid,
                                 _Bool isFrenet, topo_edge_t *edge);

TOPOCAPICALL int topo_solid_boolean(topo_solid_t s, topo_solid_t tool, int op);

TOPOCAPICALL int topo_solid_split(topo_solid_t s, topo_shape_t **splitters,
                                  int count);

TOPOCAPICALL int topo_solid_fillet(topo_solid_t s, topo_edge_t *edges,
                                   int count, double *radius, int rcount);

TOPOCAPICALL int topo_solid_chamfer(topo_solid_t s, topo_edge_t *edges,
                                    int count, double *distances, int dcount);

TOPOCAPICALL int topo_solid_shelling(topo_solid_t s, topo_face_t *faces,
                                     int count, double offset,
                                     double tolerance);

TOPOCAPICALL int topo_solid_offset(topo_solid_t s, topo_face_t f, double offset,
                                   double tolerance);

TOPOCAPICALL int topo_solid_draft(topo_solid_t s, topo_face_t *faces, int count,
                                  dir3d_t d, double angle, plane_t p);

TOPOCAPICALL int topo_solid_evolved_from_face(topo_solid_t s, topo_face_t Spine,
                                              topo_wire_t Profil);

TOPOCAPICALL int topo_solid_evolved_from_wire(topo_solid_t s, topo_wire_t Spine,
                                              topo_wire_t Profil);

TOPOCAPICALL int topo_solid_feat_prism(topo_solid_t s, topo_face_t f, dir3d_t d,
                                       double height, _Bool fuse);

TOPOCAPICALL int topo_solid_feat_prism_for_range(topo_solid_t s, topo_face_t f,
                                                 dir3d_t d, topo_face_t from,
                                                 topo_face_t end, _Bool fuse);

TOPOCAPICALL int topo_solid_feat_prism_for_until(topo_solid_t s, topo_face_t f,
                                                 dir3d_t d, topo_face_t until,
                                                 _Bool fuse);

TOPOCAPICALL int topo_solid_feat_draft_prism(topo_solid_t s, topo_face_t f,
                                             double angle, double height,
                                             _Bool fuse);

TOPOCAPICALL int
topo_solid_feat_draft_prism_for_range(topo_solid_t s, topo_face_t f,
                                      double angle, topo_face_t from,
                                      topo_face_t end, _Bool fuse);

TOPOCAPICALL int topo_solid_feat_draft_prism_for_until(
    topo_solid_t s, topo_face_t f, double angle, topo_face_t until, _Bool fuse);

TOPOCAPICALL int topo_solid_feat_revol_for_range(topo_solid_t s, topo_face_t f,
                                                 axis1_t Axes, topo_face_t from,
                                                 topo_face_t end, _Bool fuse);

TOPOCAPICALL int topo_solid_feat_revol_for_until(topo_solid_t s, topo_face_t f,
                                                 axis1_t Axes,
                                                 topo_face_t until, _Bool fuse);

TOPOCAPICALL int topo_solid_feat_pipe_for_range(topo_solid_t s, topo_face_t f,
                                                topo_wire_t Spine,
                                                topo_face_t from,
                                                topo_face_t end, _Bool fuse);

TOPOCAPICALL int topo_solid_feat_pipe_for_until(topo_solid_t s, topo_face_t f,
                                                topo_wire_t Spine,
                                                topo_face_t until, _Bool fuse);

TOPOCAPICALL int topo_solid_linear_form(topo_solid_t s, topo_wire_t w,
                                        geom_plane_surface_t *p, dir3d_t d,
                                        dir3d_t d1, _Bool fuse);

TOPOCAPICALL int topo_solid_revolution_form(topo_solid_t s, topo_wire_t w,
                                            geom_plane_surface_t *p,
                                            axis1_t Axes, double h1, double h2,
                                            _Bool fuse);

TOPOCAPICALL topo_face_t topo_solid_section_face(topo_solid_t s, pnt3d_t pnt,
                                                 pnt3d_t nor);

TOPOCAPICALL topo_wire_t topo_solid_section_wire(topo_solid_t s, pnt3d_t pnt,
                                                 pnt3d_t nor);

TOPOCAPICALL int topo_solid_convert_to_nurbs(topo_solid_t s);

TOPOCAPICALL topo_shell_t topo_solid_outer_shell(topo_solid_t s);
TOPOCAPICALL topo_shell_t *topo_solid_inner_shells(topo_solid_t s, int *count);

TOPOCAPICALL topo_compound_t topo_make_compound();

TOPOCAPICALL topo_compound_t topo_make_text(const char *text, double size,
                                            const char *font,
                                            const char *fontPath, int kind,
                                            int halign, int valign,
                                            topo_plane_t *position);

TOPOCAPICALL topo_compound_t topo_make_text_with_spine(
    const char *text, double size, topo_wire_t *spine, bool planar,
    const char *font, const char *path, int kind, int halign, int valign);

TOPOCAPICALL topo_compound_t topo_make_text_with_spine_and_base(
    const char *text, double size, topo_wire_t *spine, topo_face_t *base,
    const char *font, const char *path, int kind, int halign, int valign);

TOPOCAPICALL topo_compound_t
topo_make_text_with_height(const char *text, double size, double height,
                           const char *font, const char *fontPath, int kind,
                           int halign, int valign, topo_plane_t *position);

TOPOCAPICALL void topo_compound_free(topo_compound_t t);

TOPOCAPICALL topo_compound_t topo_compound_make_compound(topo_shape_t **S,
                                                         int count);
TOPOCAPICALL void topo_compound_remove(topo_compound_t t, topo_shape_t *s);
TOPOCAPICALL topo_compound_t topo_compound_cut(topo_compound_t t,
                                               topo_shape_t **toCut, int count,
                                               double tol);
TOPOCAPICALL topo_compound_t topo_compound_fuse(topo_compound_t t,
                                                topo_shape_t **toFuse,
                                                int count, bool glue,
                                                double tol);
TOPOCAPICALL topo_compound_t topo_compound_intersect(topo_compound_t t,
                                                     topo_shape_t **toIntersect,
                                                     int count, double tol);
TOPOCAPICALL topo_compound_t topo_compound_ancestors(topo_compound_t t,
                                                     topo_shape_t *s, int kind);
TOPOCAPICALL topo_compound_t topo_compound_siblings(topo_compound_t t,
                                                    topo_shape_t *shape,
                                                    int kind, int level);

TOPOCAPICALL topo_comp_solid_t topo_make_comp_solid();

TOPOCAPICALL void topo_comp_solid_free(topo_comp_solid_t t);

TOPOCAPICALL topo_comp_solid_t topo_comp_solid_make_comp_solid(topo_solid_t *S,
                                                               int count);

TOPOCAPICALL void topo_shape_to_stl(topo_shape_t *p, char *);

TOPOCAPICALL topo_comp_solid_iterator_t *
topo_comp_solid_iterator_make(topo_shape_t *shp);
TOPOCAPICALL void topo_comp_solid_iterator_free(topo_comp_solid_iterator_t *it);
TOPOCAPICALL void
topo_comp_solid_iterator_reset(topo_comp_solid_iterator_t *it);
TOPOCAPICALL topo_shape_t *
topo_comp_solid_iterator_next(topo_comp_solid_iterator_t *it);

TOPOCAPICALL topo_compound_iterator_t *
topo_compound_iterator_make(topo_shape_t *shp);
TOPOCAPICALL void topo_compound_iterator_free(topo_compound_iterator_t *it);
TOPOCAPICALL void topo_compound_iterator_reset(topo_compound_iterator_t *it);
TOPOCAPICALL topo_shape_t *
topo_compound_iterator_next(topo_compound_iterator_t *it);

TOPOCAPICALL topo_edge_iterator_t *topo_edge_iterator_make(topo_shape_t *shp);
TOPOCAPICALL void topo_edge_iterator_free(topo_edge_iterator_t *it);
TOPOCAPICALL void topo_edge_iterator_reset(topo_edge_iterator_t *it);
TOPOCAPICALL topo_shape_t *topo_edge_iterator_next(topo_edge_iterator_t *it);

TOPOCAPICALL topo_face_iterator_t *topo_face_iterator_make(topo_shape_t *shp);
TOPOCAPICALL void topo_face_iterator_free(topo_face_iterator_t *it);
TOPOCAPICALL void topo_face_iterator_reset(topo_face_iterator_t *it);
TOPOCAPICALL topo_shape_t *topo_face_iterator_next(topo_face_iterator_t *it);

TOPOCAPICALL topo_shell_iterator_t *topo_shell_iterator_make(topo_shape_t *shp);
TOPOCAPICALL void topo_shell_iterator_free(topo_shell_iterator_t *it);
TOPOCAPICALL void topo_shell_iterator_reset(topo_shell_iterator_t *it);
TOPOCAPICALL topo_shape_t *topo_shell_iterator_next(topo_shell_iterator_t *it);

TOPOCAPICALL topo_solid_iterator_t *topo_solid_iterator_make(topo_shape_t *shp);
TOPOCAPICALL void topo_solid_iterator_free(topo_solid_iterator_t *it);
TOPOCAPICALL void topo_solid_iterator_reset(topo_solid_iterator_t *it);
TOPOCAPICALL topo_shape_t *topo_solid_iterator_next(topo_solid_iterator_t *it);

TOPOCAPICALL topo_vertex_iterator_t *
topo_vertex_iterator_make(topo_shape_t *shp);
TOPOCAPICALL void topo_vertex_iterator_free(topo_vertex_iterator_t *it);
TOPOCAPICALL void topo_vertex_iterator_reset(topo_vertex_iterator_t *it);
TOPOCAPICALL topo_shape_t *
topo_vertex_iterator_next(topo_vertex_iterator_t *it);

TOPOCAPICALL topo_wire_iterator_t *topo_wire_iterator_make(topo_shape_t *shp);
TOPOCAPICALL void topo_wire_iterator_free(topo_wire_iterator_t *it);
TOPOCAPICALL void topo_wire_iterator_reset(topo_wire_iterator_t *it);
TOPOCAPICALL topo_shape_t *topo_wire_iterator_next(topo_wire_iterator_t *it);

// Boolean operations
TOPOCAPICALL topo_shape_t *topo_fuse(topo_shape_t **shapes, int count,
                                     double tol, bool glue);
TOPOCAPICALL topo_shape_t *topo_cut(topo_shape_t *shp, topo_shape_t *tool,
                                    double tol, bool glue);
TOPOCAPICALL topo_shape_t *topo_cut_multi(topo_shape_t *shp,
                                          topo_shape_t **toCuts, int count,
                                          double tol, bool glue);
TOPOCAPICALL topo_shape_t *topo_intersect(topo_shape_t *shp,
                                          topo_shape_t *toIntersect, double tol,
                                          bool glue);
TOPOCAPICALL topo_shape_t *topo_intersect_multi(topo_shape_t *shp,
                                                topo_shape_t **toIntersects,
                                                int count, double tol,
                                                bool glue);
TOPOCAPICALL topo_shape_t *
topo_split(topo_shape_t *shp, topo_shape_t **splitters, int count, double tol);

typedef enum {
  INTERSECTION_NONE,
  INTERSECTION_ALONG_AXIS,
  INTERSECTION_OPPOSITE
} intersection_direction_t;

TOPOCAPICALL topo_face_t *
topo_faces_intersected_by_line(topo_shape_t *shp, pnt3d_t point, dir3d_t axis,
                               double tolerance,
                               intersection_direction_t direction, int *count);

TOPOCAPICALL topo_shape_t *topo_fill(topo_shape_t *shp,
                                     topo_shape_t **constraints, int count);
TOPOCAPICALL topo_shape_t *topo_shelling(topo_shape_t *shp,
                                         topo_face_t *faceList, int faceCount,
                                         double thickness, double tolerance,
                                         int joinType);
TOPOCAPICALL topo_shape_t *topo_fillet(topo_shape_t *shp, topo_edge_t *edges,
                                       int edgeCount, double radius);
TOPOCAPICALL topo_shape_t *topo_chamfer(topo_shape_t *baseShape,
                                        topo_edge_t *edges, int edgeCount,
                                        double distance1, double distance2,
                                        bool hasDistance2);

TOPOCAPICALL topo_shape_t *topo_extrude(topo_shape_t *shape, vec3d_t direction);
TOPOCAPICALL topo_shape_t *topo_extrude_linear(topo_wire_t outerWire,
                                               topo_wire_t *innerWires,
                                               int innerCount,
                                               vec3d_t vecNormal, double taper);
TOPOCAPICALL topo_shape_t *topo_extrude_linear_with_rotation(
    topo_wire_t outerWire, topo_wire_t *innerWires, int innerCount,
    pnt3d_t center, vec3d_t normal, double angleDegrees);

TOPOCAPICALL topo_shape_t *topo_revolve(topo_shape_t *shape, pnt3d_t axisPoint,
                                        dir3d_t axisDirection,
                                        double angleDegrees);
TOPOCAPICALL topo_shape_t *
topo_revolve_wire(topo_wire_t outerWire, topo_wire_t *innerWires,
                  int innerCount, double angleDegrees, pnt3d_t axisStart,
                  pnt3d_t axisEnd);

typedef enum {
  TRANSITION_TRANSFORMED,
  TRANSITION_ROUND,
  TRANSITION_RIGHT
} transition_mode_t;

TOPOCAPICALL topo_shape_t *topo_sweep(topo_wire_t outerWire,
                                      topo_wire_t *innerWires, int innerCount,
                                      topo_shape_t *path, bool makeSolid,
                                      bool isFrenet, topo_shape_t *mode,
                                      transition_mode_t transitionMode);
TOPOCAPICALL topo_shape_t *topo_sweep_multi(topo_shape_t **profiles, int count,
                                            topo_shape_t *path, bool makeSolid,
                                            bool isFrenet, topo_shape_t *mode);

TOPOCAPICALL topo_shape_t *
topo_loft(topo_shape_t **profiles, int count, bool cap, bool ruled,
          const char *continuity, const char *parametrization, int degree,
          bool compat, bool smoothing, double *weights);

TOPOCAPICALL topo_shape_t *topo_offset(topo_shape_t *shape, double offset,
                                       bool cap, bool both, double tol);
TOPOCAPICALL topo_shape_t *topo_clean(topo_shape_t *shape);

TOPOCAPICALL void topo_closest(topo_shape_t *shape1, topo_shape_t *shape2,
                               pnt3d_t *p1, pnt3d_t *p2);
TOPOCAPICALL pnt3d_t topo_combined_center(topo_shape_t **objects, int count);
TOPOCAPICALL pnt3d_t topo_combined_center_of_bound_box(topo_shape_t **objects,
                                                       int count);

TOPOCAPICALL topo_shape_t *read_shape_from_step_file(const char *filename);

typedef struct {
  pnt3d_t position;
  vec3d_t tangent;
  topo_edge_t edge;
} topo_wire_sample_point_t;

TOPOCAPICALL topo_wire_sample_point_t *
topo_wire_sample_at_distances(topo_wire_t wire, double *distances, int count,
                              int *result_count);
TOPOCAPICALL void topo_wire_sample_list_free(topo_wire_sample_point_t *samples,
                                             int count);
TOPOCAPICALL topo_wire_t topo_wire_clip_between_distances(topo_wire_t wire,
                                                          double start_distance,
                                                          double end_distance);

typedef struct {
  axis2_t axes;
  trsf_t trsf;
  vec3d_t tangent;
  pnt3d_t position;
} topo_profile_projection_t;

TOPOCAPICALL topo_profile_projection_t
topo_calc_profile_projection(topo_wire_t path, dir3d_t upDir, double *offset);
TOPOCAPICALL pnt3d_t topo_profile_project_point(topo_profile_projection_t *proj,
                                                pnt3d_t point);
TOPOCAPICALL pnt3d_t *
topo_profile_project_point_list(topo_profile_projection_t *proj, pnt3d_t *point,
                                int count);
TOPOCAPICALL void topo_profile_project_point_list_free(pnt3d_t *points);

TOPOCAPICALL double topo_wrie_length(topo_wire_t wire);

TOPOCAPICALL pnt3d_t *topo_make_catenary(pnt3d_t p1, pnt3d_t p2, double slack,
                                         double maxSag, dir3d_t up,
                                         double tessellation, int *point_count);

TOPOCAPICALL void topo_free_catenary_points(pnt3d_t *points);

#ifdef __cplusplus
}
#endif

#endif
