#ifndef GO_STANDARD_C_API_H
#define GO_STANDARD_C_API_H

#if defined(WIN32) || defined(WINDOWS) || defined(_WIN32) || defined(_WINDOWS)
#define STDCAPICALL __declspec(dllexport)
#else
#define STDCAPICALL
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _xyz_t {
  double x;
  double y;
  double z;
} xyz_t;

typedef struct _pnt3d_t {
  double x;
  double y;
  double z;
} pnt3d_t;

typedef struct _vec3d_t {
  double x;
  double y;
  double z;
} vec3d_t;

typedef struct _xy_t {
  double x;
  double y;
} xy_t;

typedef struct _pnt2d_t {
  double x;
  double y;
} pnt2d_t;

typedef struct _vec2d_t {
  double x;
  double y;
} vec2d_t;

typedef struct _dir3d_t {
  double x;
  double y;
  double z;
} dir3d_t;

STDCAPICALL dir3d_t make_dir(vec3d_t v);
STDCAPICALL dir3d_t make_dir_from_xyz(double x, double y, double z);
STDCAPICALL dir3d_t make_dir_from_point(pnt3d_t p1, pnt3d_t p2);

typedef struct _dir2d_t {
  double x;
  double y;
} dir2d_t;

STDCAPICALL dir2d_t make_dir2d(vec2d_t p);
STDCAPICALL dir2d_t make_dir2d_from_xy(double x, double y);
STDCAPICALL dir2d_t make_dir2d_from_point(pnt2d_t p1, pnt2d_t p2);

typedef struct _axis1_t {
  pnt3d_t p;
  dir3d_t d;
} axis1_t;

STDCAPICALL axis1_t make_axis(pnt3d_t p, dir3d_t v);

typedef struct _axis2_t {
  axis1_t a;
  dir3d_t vy;
  dir3d_t vx;
} axis2_t;

STDCAPICALL axis2_t make_axis2_from_nvx(pnt3d_t p, dir3d_t N, dir3d_t Vx);
STDCAPICALL axis2_t make_axis2(pnt3d_t p, dir3d_t v);

typedef struct _axis3_t {
  axis1_t a;
  dir3d_t vy;
  dir3d_t vx;
} axis3_t;

STDCAPICALL axis3_t make_axis3(axis2_t a);
STDCAPICALL axis3_t make_axis3_from_nvx(pnt3d_t p, dir3d_t N, dir3d_t Vx);
STDCAPICALL axis3_t make_axis3_from_v(pnt3d_t p, dir3d_t v);

typedef struct _axis2d_t {
  pnt2d_t p;
  dir2d_t v;
} axis2d_t;

STDCAPICALL axis2d_t make_axis2d(pnt2d_t p, dir2d_t v);

typedef struct _axis22d_t {
  pnt2d_t p;
  dir2d_t vx;
  dir2d_t vy;
} axis22d_t;

STDCAPICALL axis22d_t make_axis22d(axis2d_t a);
STDCAPICALL axis22d_t make_axis22d_from_v(pnt2d_t p, dir2d_t v);
STDCAPICALL axis22d_t make_axis22d_from_vxy(pnt2d_t p, dir2d_t vx, dir2d_t vy);

typedef struct _circ_t {
  axis2_t a2;
  double radius;
} circ_t;

typedef struct _plane_t plane_t;

STDCAPICALL circ_t make_circ_from_axis2(axis2_t a, double radius);
STDCAPICALL circ_t make_circ_from_circ_dist(circ_t a, double Dist);
STDCAPICALL circ_t make_circ_from_circ_point(circ_t a, pnt3d_t p);
STDCAPICALL circ_t make_circ_from_point(pnt3d_t p1, pnt3d_t p2, pnt3d_t p3);
STDCAPICALL circ_t make_circ_from_center_norm(pnt3d_t center, dir3d_t Norm,
                                              double radius);
STDCAPICALL circ_t make_circ_from_center_plan(pnt3d_t center, plane_t pl,
                                              double radius);
STDCAPICALL circ_t make_circ_from_axis1(axis1_t a, double radius);

typedef struct _circ2d_t {
  axis22d_t a2;
  double radius;
} circ2d_t;

STDCAPICALL circ2d_t make_circ2d_from_axis2(axis2d_t a, double radius);
STDCAPICALL circ2d_t make_circ2d_from_axis22d(axis22d_t a, double radius);
STDCAPICALL circ2d_t make_circ2d_from_circ_dist(circ2d_t a, double Dist);
STDCAPICALL circ2d_t make_circ2d_from_circ2d(circ2d_t a, pnt2d_t p);
STDCAPICALL circ2d_t make_circ2d_from_point(pnt2d_t p1, pnt2d_t p2, pnt2d_t p3);
STDCAPICALL circ2d_t make_circ2d_from_center_radius(pnt2d_t center,
                                                    double radius);
STDCAPICALL circ2d_t make_circ2d_from_center_point(pnt2d_t center, pnt2d_t p);

typedef struct _cone_t {
  axis3_t a3;
  double ang;
  double radius;
} cone_t;

typedef struct _line_t line_t;

STDCAPICALL cone_t make_cone_from_axis2(axis2_t a, double ang, double radius);
STDCAPICALL cone_t make_cone_from_cone_point(cone_t a, pnt3d_t p);
STDCAPICALL cone_t make_cone_from_cone_dist(cone_t a, double dist);
STDCAPICALL cone_t make_cone_from_point(pnt3d_t p1, pnt3d_t p2, pnt3d_t p3,
                                        pnt3d_t p4);
STDCAPICALL cone_t make_cone_from_axis1_point(axis1_t a, pnt3d_t p1,
                                              pnt3d_t p2);
STDCAPICALL cone_t make_cone_from_line_point(line_t l, pnt3d_t p1, pnt3d_t p2);
STDCAPICALL cone_t make_cone_point_radius(pnt3d_t p1, pnt3d_t p2, double r1,
                                          double r2);

typedef struct _cylinder_t {
  axis3_t a3;
  double radius;
} cylinder_t;

STDCAPICALL cylinder_t make_cylinder_from_axis2(axis2_t a, double radius);
STDCAPICALL cylinder_t make_cylinder_from_cylinder_point(cylinder_t a,
                                                         pnt3d_t p);
STDCAPICALL cylinder_t make_cylinder_from_cylinder_dist(cylinder_t a,
                                                        double dist);
STDCAPICALL cylinder_t make_cylinder_from_point(pnt3d_t p1, pnt3d_t p2,
                                                pnt3d_t p3);
STDCAPICALL cylinder_t make_cylinder_from_axis1_radius(axis1_t a,
                                                       double radius);
STDCAPICALL cylinder_t make_cylinder_from_circ(circ_t a);

typedef struct _elips_t {
  axis2_t a2;
  double major_radius;
  double minor_radius;
} elips_t;

STDCAPICALL elips_t make_elips_from_axis2_radius(axis2_t a, double major_radius,
                                                 double minor_radius);
STDCAPICALL elips_t make_elips_point(pnt3d_t s1, pnt3d_t s2, pnt3d_t center);

typedef struct _elips2d_t {
  axis22d_t a2;
  double major_radius;
  double minor_radius;
} elips2d_t;

STDCAPICALL elips2d_t make_elips2d_axis2d_radius(axis2d_t a,
                                                 double major_radius,
                                                 double minor_radius);
STDCAPICALL elips2d_t make_elips2d_point(pnt2d_t s1, pnt2d_t s2,
                                         pnt2d_t center);

typedef struct _mat3x3_t {
  double mat[9];
} mat3x3_t;

typedef struct _mat2x2_t {
  double mat[4];
} mat2x2_t;

typedef struct _transform_t {
  mat3x3_t m;
  xyz_t v;
} transform_t;

typedef struct _transform2d_t {
  mat2x2_t m;
  xy_t v;
} transform2d_t;

typedef struct _hyperbola_t {
  axis2_t a2;
  double major_radius;
  double minor_radius;
} hyperbola_t;

STDCAPICALL hyperbola_t make_hyperbola_from_axis2(axis2_t a,
                                                  double major_radius,
                                                  double minor_radius);
STDCAPICALL hyperbola_t make_hyperbola_from_point(pnt3d_t s1, pnt3d_t s2,
                                                  pnt3d_t center);

typedef struct _hyperbola2d_t {
  axis22d_t a2;
  double major_radius;
  double minor_radius;
} hyperbola2d_t;

STDCAPICALL hyperbola2d_t make_hyperbola2d_from_axis2d(axis2d_t a,
                                                       double major_radius,
                                                       double minor_radius);
STDCAPICALL hyperbola2d_t make_hyperbola2d_from_point(pnt2d_t s1, pnt2d_t s2,
                                                      pnt2d_t center);

typedef struct _line_t {
  pnt3d_t p;
  dir3d_t v;
} line_t;

STDCAPICALL line_t make_line_from_axis1(axis1_t a);
STDCAPICALL line_t make_line_from_point_dir(pnt3d_t p, dir3d_t v);
STDCAPICALL line_t make_line_from_line_point(line_t l, pnt3d_t p);
STDCAPICALL line_t make_line_from_point(pnt3d_t p1, pnt3d_t p2);

typedef struct _line2d_t {
  pnt2d_t p;
  dir2d_t v;
} line2d_t;

STDCAPICALL line2d_t make_line2d_from_axis2d(axis2d_t a);
STDCAPICALL line2d_t make_line2d_point_dir(pnt2d_t p, dir2d_t v);
STDCAPICALL line2d_t make_line2d_from_line_dist(line2d_t l, double dist);
STDCAPICALL line2d_t make_line2d_line_point(line2d_t l, pnt2d_t p);
STDCAPICALL line2d_t make_line2d_from_point(pnt2d_t p1, pnt2d_t p2);

typedef struct _parabola_t {
  axis2_t a2;
  double focal;
} parabola_t;

parabola_t make_parabola_from_axis2(axis2_t a, double Focal);
parabola_t make_parabola_from_axis1(axis1_t a, pnt3d_t v);

typedef struct _parabola2d_t {
  axis22d_t a2;
  double focal;
} parabola2d_t;

parabola2d_t make_parabola2d_from_axis2d(axis2d_t a, double Focal);
parabola2d_t make_parabola2d_from_axis22d(axis22d_t a, double Focal);
parabola2d_t make_parabola2d_from_axis2d_point(axis2d_t a, pnt2d_t F);
parabola2d_t make_parabola2d_point(pnt2d_t S1, pnt2d_t center);

typedef struct _plane_t {
  axis3_t p;
} plane_t;

plane_t make_plane_from_axis2(axis2_t a);
plane_t make_plane_from_point_dir(pnt3d_t p, dir3d_t v);
plane_t make_plane_from_lrud(double a, double b, double c, double d);
plane_t make_plane_from_plane_point(plane_t pln, pnt3d_t p);
plane_t make_plane_from_plane_dist(plane_t pln, double dist);
plane_t make_plane_from_point(pnt3d_t p1, pnt3d_t p2, pnt3d_t p3);
plane_t make_plane_from_two_point(pnt3d_t p1, pnt3d_t p2);
plane_t make_plane_from_axis1(axis1_t a);

typedef struct _quaternion_t {
  double q[4];
} quaternion_t;

typedef struct _quat_n_lerp_t {
  quaternion_t start;
  quaternion_t end;
} quat_n_lerp_t;

typedef struct _quat_s_lerp_t {
  quaternion_t start;
  quaternion_t end;
} quat_s_lerp_t;

typedef struct _sphere_t {
  axis3_t a3;
  double radius;
} sphere_t;

sphere_t make_sphere_from_axis3(axis3_t a, double radius);

typedef struct _torus_t {
  axis3_t a3;
  double major_radius;
  double minor_radius;
} torus_t;

torus_t make_torus_from_axis3(axis3_t a, double major_radius,
                              double minor_radius);
torus_t make_torus_from_elips(elips_t el);

typedef struct _trsf_t {
  double m[12];
} trsf_t;

STDCAPICALL trsf_t make_trsf_mirror_from_point(pnt3d_t p);
STDCAPICALL trsf_t make_trsf_mirror_from_axis1(axis1_t a);
STDCAPICALL trsf_t make_trsf_mirror_from_line(line_t a);
STDCAPICALL trsf_t make_trsf_mirror_from_point_dir(pnt3d_t p, dir3d_t v);
STDCAPICALL trsf_t make_trsf_mirror_from_axis2(axis2_t a);
STDCAPICALL trsf_t make_trsf_mirror_from_plane(plane_t a);
STDCAPICALL trsf_t make_trsf_rotation_from_line(line_t a, double Angle);
STDCAPICALL trsf_t make_trsf_rotation_from_axis1(axis1_t a, double Angle);
STDCAPICALL trsf_t make_trsf_rotation_point_dir(pnt3d_t p, dir3d_t v,
                                                double Angle);
STDCAPICALL trsf_t make_trsf_scale_from_point(pnt3d_t p, double Scale);
STDCAPICALL trsf_t make_trsf_translation_from_vector(vec3d_t v);
STDCAPICALL trsf_t make_trsf_translation_from_point(pnt3d_t p1, pnt3d_t p2);

typedef struct _trsf2d_t {
  double m[6];
} trsf2d_t;

STDCAPICALL trsf2d_t make_trsf2d_mirror_from_point(pnt2d_t p);
STDCAPICALL trsf2d_t make_trsf2d_mirror_from_axis2d(axis2d_t a);
STDCAPICALL trsf2d_t make_trsf2d_mirror_from_line(line2d_t a);
STDCAPICALL trsf2d_t make_trsf2d_mirror_from_point_dir(pnt2d_t p, dir2d_t v);
STDCAPICALL trsf2d_t make_trsf2d_rotation_from_point(pnt2d_t p, double Angle);
STDCAPICALL trsf2d_t make_trsf2d_scale_from_point(pnt2d_t p, double Scale);
STDCAPICALL trsf2d_t make_trsf2d_translation_from_vector(vec2d_t v);
STDCAPICALL trsf2d_t make_trsf2d_translation_from_point(pnt2d_t p1, pnt2d_t p2);

typedef struct _color_t {
  double r;
  double g;
  double b;
} color_t;

#ifdef __cplusplus
}
#endif

#endif
