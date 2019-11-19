#ifndef GO_STANDARD_C_API_H
#define GO_STANDARD_C_API_H

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

typedef struct _dir2d_t {
  double x;
  double y;
} dir2d_t;

typedef struct _axis1_t {
  pnt3d_t p;
  dir3d_t d;
} axis1_t;

typedef struct _axis2_t {
  axis1_t a;
  dir3d_t vy;
  dir3d_t vx;
} axis2_t;

typedef struct _axis3_t {
  axis1_t a;
  dir3d_t vy;
  dir3d_t vx;
} axis3_t;

typedef struct _axis2d_t {
  pnt2d_t p;
  dir2d_t v;
} axis2d_t;

typedef struct _axis22d_t {
  pnt2d_t p;
  dir2d_t vx;
  dir2d_t vy;
} axis22d_t;

typedef struct _circ_t {
  axis2_t a2;
  double radius;
} circ_t;

typedef struct _circ2d_t {
  axis22d_t a2;
  double radius;
} circ2d_t;

typedef struct _cone_t {
  axis3_t a3;
  double ang;
  double radius;
} cone_t;

typedef struct _cylinder_t {
  axis3_t a3;
  double radius;
} cylinder_t;

typedef struct _elips_t {
  axis2_t a2;
  double major_radius;
  double minor_radius;
} elips_t;

typedef struct _elips2d_t {
  axis22d_t a2;
  double major_radius;
  double minor_radius;
} elips2d_t;

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

typedef struct _hyperbola2d_t {
  axis22d_t a2;
  double major_radius;
  double minor_radius;
} hyperbola2d_t;

typedef struct _line_t {
  pnt3d_t p;
  dir3d_t v;
} line_t;

typedef struct _line2d_t {
  pnt2d_t p;
  dir2d_t v;
} line2d_t;

typedef struct _parabola_t {
  axis2_t a2;
  double focal;
} parabola_t;

typedef struct _parabola2d_t {
  axis22d_t a2;
  double focal;
} parabola2d_t;

typedef struct _plane_t {
  axis3_t p;
} plane_t;

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

typedef struct _torus_t {
  axis3_t a3;
  double major_radius;
  double minor_radius;
} torus_t;

typedef struct _trsf_t {
  double m[12];
} trsf_t;

typedef struct _trsf2d_t {
  double m[6];
} trsf2d_t;

#ifdef __cplusplus
}
#endif

#endif
