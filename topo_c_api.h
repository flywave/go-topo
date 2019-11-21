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
typedef struct _topo_location_t topo_location_t;
typedef struct _topo_mesh_receiver_t topo_mesh_receiver_t;

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

TOPOCAPICALL void topo_shape_free(topo_shape_t *p);
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
TOPOCAPICALL void topo_shape_mesh(topo_shape_t *p,
                                  topo_mesh_receiver_t *receiver,
                                  double tolerance, double deflection,
                                  double angle);

TOPOCAPICALL void topo_shape_set_surface_colour(topo_shape_t *p, color_t c);
TOPOCAPICALL void topo_shape_set_curve_colour(topo_shape_t *p, color_t c);
TOPOCAPICALL void topo_shape_set_label(topo_shape_t *p, const char *name);

TOPOCAPICALL color_t topo_shape_get_surface_colour(topo_shape_t *p);
TOPOCAPICALL color_t topo_shape_get_curve_colour(topo_shape_t *p);
TOPOCAPICALL const char *topo_shape_get_label(topo_shape_t *p);
TOPOCAPICALL _Bool topo_shape_surface_colour(topo_shape_t *p, double *colour);

typedef struct _topo_vertex_t {
  topo_shape_t *shp;
} topo_vertex_t;

TOPOCAPICALL topo_vertex_t topo_vertex_new(double x, double y, double z);
TOPOCAPICALL void topo_vertex_free(topo_vertex_t t);
TOPOCAPICALL pnt3d_t topo_vertex_get_point(topo_vertex_t t);

typedef struct _topo_wire_t {
  topo_shape_t *shp;
} topo_wire_t;

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

TOPOCAPICALL int topo_wire_num_vertices(topo_wire_t w);
TOPOCAPICALL int topo_wire_num_edges(topo_wire_t w);
TOPOCAPICALL bool topo_wire_is_closed(topo_wire_t w);
TOPOCAPICALL double topo_wire_length(topo_wire_t w);
TOPOCAPICALL void topo_wire_convert_to_curves3d(topo_wire_t w);

TOPOCAPICALL int topo_wire_project(topo_wire_t w, topo_face_t f);

TOPOCAPICALL int topo_wire_offset(topo_wire_t w, double distance, int joinType);

TOPOCAPICALL int topo_wire_fillet(topo_wire_t w, topo_vertex_t *vertices,
                                  int vertcount, double *radius, int radcount);
TOPOCAPICALL int topo_wire_chamfer(topo_wire_t w, topo_vertex_t *vertices,
                                   int vertcount, double *distances,
                                   int distcount);

typedef struct _topo_edge_t {
  topo_shape_t *shp;
} topo_edge_t;

TOPOCAPICALL void topo_edge_free(topo_edge_t t);

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
TOPOCAPICALL bool topo_edge_is_seam(topo_edge_t e, topo_face_t f);
TOPOCAPICALL bool topo_edge_is_degenerated(topo_edge_t e);
TOPOCAPICALL bool topo_edge_is_closed(topo_edge_t e);
TOPOCAPICALL bool topo_edge_is_inifinite(topo_edge_t e);
TOPOCAPICALL int topo_edge_num_vertices(topo_edge_t e);
TOPOCAPICALL double topo_edge_length(topo_edge_t e);
TOPOCAPICALL float topo_edge_tolerance(topo_edge_t e);
TOPOCAPICALL bool topo_edge_is_curve3d(topo_edge_t e);
TOPOCAPICALL void topo_edge_convert_to_curve3d(topo_edge_t e);

#ifdef __cplusplus
}
#endif

#endif
