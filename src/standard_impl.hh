#ifndef GO_STANDARD_IMPL_H
#define GO_STANDARD_IMPL_H

#include "standard_c_api.h"

#include <NCollection_Array1.hxx>
#include <TColStd_Array1OfInteger.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <TColStd_Array2OfReal.hxx>
#include <TColgp_Array1OfCirc2d.hxx>
#include <TColgp_Array1OfDir.hxx>
#include <TColgp_Array1OfDir2d.hxx>
#include <TColgp_Array1OfLin2d.hxx>
#include <TColgp_Array1OfPnt.hxx>
#include <TColgp_Array1OfPnt2d.hxx>
#include <TColgp_Array1OfVec.hxx>
#include <TColgp_Array1OfVec2d.hxx>
#include <TColgp_Array1OfXY.hxx>
#include <TColgp_Array1OfXYZ.hxx>
#include <TColgp_Array2OfCirc2d.hxx>
#include <TColgp_Array2OfDir.hxx>
#include <TColgp_Array2OfDir2d.hxx>
#include <TColgp_Array2OfLin2d.hxx>
#include <TColgp_Array2OfPnt.hxx>
#include <TColgp_Array2OfPnt2d.hxx>
#include <TColgp_Array2OfVec.hxx>
#include <TColgp_Array2OfVec2d.hxx>
#include <TColgp_Array2OfXY.hxx>
#include <TColgp_Array2OfXYZ.hxx>

#include <gp.hxx>
#include <gp_Ax22d.hxx>
#include <gp_Circ.hxx>
#include <gp_Circ2d.hxx>
#include <gp_Cone.hxx>
#include <gp_Cylinder.hxx>
#include <gp_Elips.hxx>
#include <gp_Elips2d.hxx>
#include <gp_GTrsf.hxx>
#include <gp_GTrsf2d.hxx>
#include <gp_Hypr.hxx>
#include <gp_Hypr2d.hxx>
#include <gp_Lin.hxx>
#include <gp_Lin2d.hxx>
#include <gp_Parab.hxx>
#include <gp_Parab2d.hxx>
#include <gp_Pln.hxx>
#include <gp_Pnt.hxx>
#include <gp_Sphere.hxx>
#include <gp_Torus.hxx>

#include <Bnd_Box.hxx>
#include <Quantity_Color.hxx>

#include <TColgp_HArray1OfPnt.hxx>
#include <TColgp_HArray1OfPnt2d.hxx>

#include <TColgp_SequenceOfArray1OfPnt2d.hxx>
#include <TColgp_SequenceOfAx1.hxx>
#include <TColgp_SequenceOfDir.hxx>
#include <TColgp_SequenceOfDir2d.hxx>
#include <TColgp_SequenceOfPnt.hxx>
#include <TColgp_SequenceOfPnt2d.hxx>
#include <TColgp_SequenceOfVec.hxx>
#include <TColgp_SequenceOfVec2d.hxx>
#include <TColgp_SequenceOfXY.hxx>
#include <TColgp_SequenceOfXYZ.hxx>

#include <gp_QuaternionNLerp.hxx>
#include <gp_QuaternionSLerp.hxx>

#include <gce_MakeCirc.hxx>
#include <gce_MakeCirc2d.hxx>
#include <gce_MakeCone.hxx>
#include <gce_MakeCylinder.hxx>
#include <gce_MakeDir.hxx>
#include <gce_MakeDir2d.hxx>
#include <gce_MakeElips.hxx>
#include <gce_MakeElips2d.hxx>
#include <gce_MakeHypr.hxx>
#include <gce_MakeHypr2d.hxx>
#include <gce_MakeLin.hxx>
#include <gce_MakeLin2d.hxx>
#include <gce_MakeMirror.hxx>
#include <gce_MakeMirror2d.hxx>
#include <gce_MakeParab.hxx>
#include <gce_MakeParab2d.hxx>
#include <gce_MakePln.hxx>
#include <gce_MakeRotation.hxx>
#include <gce_MakeRotation2d.hxx>
#include <gce_MakeScale.hxx>
#include <gce_MakeScale2d.hxx>
#include <gce_MakeTranslation.hxx>
#include <gce_MakeTranslation2d.hxx>

#include <list>
#include <vector>

inline gp_XYZ cast_to_gp(const xyz_t &p) {
  return gp_XYZ{static_cast<Standard_Real>(p.x),
                static_cast<Standard_Real>(p.y),
                static_cast<Standard_Real>(p.z)};
}

inline gp_Pnt cast_to_gp(const pnt3d_t &p) {
  return gp_Pnt{static_cast<Standard_Real>(p.x),
                static_cast<Standard_Real>(p.y),
                static_cast<Standard_Real>(p.z)};
}

inline gp_Vec cast_to_gp(const vec3d_t &p) {
  return gp_Vec{static_cast<Standard_Real>(p.x),
                static_cast<Standard_Real>(p.y),
                static_cast<Standard_Real>(p.z)};
}

inline pnt3d_t cast_from_gp(const gp_Pnt &p) {
  return pnt3d_t{p.X(), p.Y(), p.Z()};
}

inline xyz_t cast_from_gp(const gp_XYZ &p) {
  return xyz_t{p.X(), p.Y(), p.Z()};
}

inline vec3d_t cast_from_gp(const gp_Vec &p) {
  return vec3d_t{p.X(), p.Y(), p.Z()};
}

inline gp_Dir cast_to_gp(const dir3d_t &p) {
  gce_MakeDir md(gp_Vec(p.x, p.y, p.z));
  return md.Value();
}

inline dir3d_t cast_from_gp(const gp_Dir &d) {
  return dir3d_t{d.X(), d.Y(), d.Z()};
}

inline gp_XY cast_to_gp(const xy_t &p) {
  return gp_XY{static_cast<Standard_Real>(p.x),
               static_cast<Standard_Real>(p.y)};
}

inline gp_Pnt2d cast_to_gp(const pnt2d_t &p) {
  return gp_Pnt2d{static_cast<Standard_Real>(p.x),
                  static_cast<Standard_Real>(p.y)};
}

inline gp_Vec2d cast_to_gp(const vec2d_t &p) {
  return gp_Vec2d{static_cast<Standard_Real>(p.x),
                  static_cast<Standard_Real>(p.y)};
}

inline xy_t cast_from_gp(const gp_XY &p) { return xy_t{p.X(), p.Y()}; }

inline pnt2d_t cast_from_gp(const gp_Pnt2d &p) { return pnt2d_t{p.X(), p.Y()}; }

inline vec2d_t cast_from_gp(const gp_Vec2d &p) { return vec2d_t{p.X(), p.Y()}; }

inline gp_Dir2d cast_to_gp(const dir2d_t &p) {
  gp_Dir2d md(gp_Vec2d(p.x, p.y));
  return md;
}

inline dir2d_t cast_from_gp(const gp_Dir2d &d) { return dir2d_t{d.X(), d.Y()}; }

inline gp_Ax1 cast_to_gp(const axis1_t &a) {
  return gp_Ax1(gp_Pnt(cast_to_gp(a.p)), cast_to_gp(a.d));
}

inline axis1_t cast_from_gp(const gp_Ax1 &a) {
  return axis1_t{cast_from_gp(a.Location()), cast_from_gp(a.Direction())};
}

inline gp_Ax2 cast_to_gp(const axis2_t &a) {
  gp_Ax2 ret;
  ret.SetAxis(cast_to_gp(a.a));
  ret.SetXDirection(cast_to_gp(a.vx));
  ret.SetYDirection(cast_to_gp(a.vy));
  return ret;
}

inline axis2_t cast_from_gp(const gp_Ax2 &a) {
  return axis2_t{cast_from_gp(a.Axis()), cast_from_gp(a.YDirection()),
                 cast_from_gp(a.XDirection())};
}

inline gp_Ax3 cast_to_gp(const axis3_t &a) {
  gp_Ax3 ret;
  ret.SetAxis(cast_to_gp(a.a));
  ret.SetXDirection(cast_to_gp(a.vx));
  ret.SetYDirection(cast_to_gp(a.vy));
  return ret;
}

inline axis3_t cast_from_gp(const gp_Ax3 &a) {
  return axis3_t{cast_from_gp(a.Axis()), cast_from_gp(a.YDirection()),
                 cast_from_gp(a.XDirection())};
}

inline gp_Ax2d cast_to_gp(const axis2d_t &a) {
  return gp_Ax2d(gp_Pnt2d{cast_to_gp(a.p)}, cast_to_gp(a.v));
}

inline axis2d_t cast_from_gp(const gp_Ax2d &a) {
  return axis2d_t{cast_from_gp(a.Location()), cast_from_gp(a.Direction())};
}

inline gp_Ax22d cast_to_gp(const axis22d_t &a) {
  return gp_Ax22d(gp_Pnt2d(cast_to_gp(a.p)), cast_to_gp(a.vx),
                  cast_to_gp(a.vy));
}

inline axis22d_t cast_from_gp(const gp_Ax22d &a) {
  return axis22d_t{cast_from_gp(a.Location()), cast_from_gp(a.XDirection()),
                   cast_from_gp(a.YDirection())};
}

inline gp_Circ cast_to_gp(const circ_t &a) {
  return gp_Circ(cast_to_gp(a.a2), a.radius);
}

inline circ_t cast_from_gp(const gp_Circ &a) {
  return circ_t{cast_from_gp(a.Position()), a.Radius()};
}

inline gp_Circ2d cast_to_gp(const circ2d_t &a) {
  return gp_Circ2d(cast_to_gp(a.a2), a.radius);
}

inline circ2d_t cast_from_gp(const gp_Circ2d &a) {
  return circ2d_t{cast_from_gp(a.Location()), a.Radius()};
}

inline gp_Cone cast_to_gp(const cone_t &a) {
  return gp_Cone(cast_to_gp(a.a3), a.ang, a.radius);
}

inline cone_t cast_from_gp(const gp_Cone &a) {
  return cone_t{cast_from_gp(a.Position()), a.SemiAngle(), a.RefRadius()};
}

inline gp_Cylinder cast_to_gp(const cylinder_t &a) {
  return gp_Cylinder(cast_to_gp(a.a3), a.radius);
}

inline cylinder_t cast_from_gp(const gp_Cylinder &a) {
  return cylinder_t{cast_from_gp(a.Position()), a.Radius()};
}

inline gp_Elips cast_to_gp(const elips_t &a) {
  return gp_Elips(cast_to_gp(a.a2), a.major_radius, a.minor_radius);
}

inline elips_t cast_from_gp(const gp_Elips &a) {
  return elips_t{cast_from_gp(a.Position()), a.MajorRadius(), a.MinorRadius()};
}

inline gp_Elips2d cast_to_gp(const elips2d_t &a) {
  return gp_Elips2d(cast_to_gp(a.a2), a.major_radius, a.minor_radius);
}

inline elips2d_t cast_from_gp(const gp_Elips2d &a) {
  return elips2d_t{cast_from_gp(a.Axis()), a.MajorRadius(), a.MinorRadius()};
}

inline gp_Mat cast_to_gp(const mat3x3_t &a) {
  return gp_Mat{static_cast<Standard_Real>(a.mat[0]),
                static_cast<Standard_Real>(a.mat[3]),
                static_cast<Standard_Real>(a.mat[6]),
                static_cast<Standard_Real>(a.mat[1]),
                static_cast<Standard_Real>(a.mat[4]),
                static_cast<Standard_Real>(a.mat[7]),
                static_cast<Standard_Real>(a.mat[2]),
                static_cast<Standard_Real>(a.mat[5]),
                static_cast<Standard_Real>(a.mat[8])};
}

inline mat3x3_t cast_from_gp(const gp_Mat &a) {
  return mat3x3_t{{a(1, 1), a(2, 1), a(3, 1), a(1, 2), a(2, 2), a(3, 2),
                   a(1, 3), a(2, 3), a(3, 3)}};
}

inline gp_Mat2d cast_to_gp(const mat2x2_t &a) {
  return gp_Mat2d{gp_XY{static_cast<Standard_Real>(a.mat[0]),
                        static_cast<Standard_Real>(a.mat[1])},
                  gp_XY{static_cast<Standard_Real>(a.mat[2]),
                        static_cast<Standard_Real>(a.mat[3])}};
}

inline mat2x2_t cast_from_gp(const gp_Mat2d &a) {
  return mat2x2_t{{a(1, 1), a(2, 1), a(1, 2), a(2, 2)}};
}

template <typename T> inline gp_GTrsf cast_to_gp(const transform_t &a) {
  return gp_GTrsf{cast_to_gp(a.m), cast_to_gp(a.v)};
}

inline transform_t cast_from_gp(const gp_GTrsf &a) {
  return transform_t{cast_from_gp(a.VectorialPart()),
                     cast_from_gp(a.TranslationPart())};
}

template <typename T> inline gp_GTrsf2d cast_to_gp(const transform2d_t &a) {
  return gp_GTrsf2d{cast_to_gp(a.m), cast_to_gp(a.v)};
}

inline transform2d_t cast_from_gp(const gp_GTrsf2d &a) {
  return transform2d_t{cast_from_gp(a.VectorialPart()),
                       cast_from_gp(a.TranslationPart())};
}

inline gp_Hypr cast_to_gp(const hyperbola_t &a) {
  return gp_Hypr(cast_to_gp(a.a2), a.major_radius, a.minor_radius);
}

inline hyperbola_t cast_from_gp(const gp_Hypr &a) {
  return hyperbola_t{cast_from_gp(a.Position()), a.MajorRadius(),
                     a.MinorRadius()};
}

inline gp_Hypr2d cast_to_gp(const hyperbola2d_t &a) {
  return gp_Hypr2d(cast_to_gp(a.a2), a.major_radius, a.minor_radius);
}

inline hyperbola2d_t cast_from_gp(const gp_Hypr2d &a) {
  return hyperbola2d_t{cast_from_gp(a.Axis()), a.MajorRadius(),
                       a.MinorRadius()};
}

inline gp_Lin cast_to_gp(const line_t &a) {
  return gp_Lin(gp_Pnt(cast_to_gp(a.p)), cast_to_gp(a.v));
}

inline line_t cast_from_gp(const gp_Lin &a) {
  return line_t{cast_from_gp(a.Location()), cast_from_gp(a.Direction())};
}

inline gp_Lin2d cast_to_gp(const line2d_t &a) {
  return gp_Lin2d(gp_Pnt2d(cast_to_gp(a.p)), cast_to_gp(a.v));
}

inline line2d_t cast_from_gp(const gp_Lin2d &a) {
  return line2d_t{cast_from_gp(a.Location()), cast_from_gp(a.Direction())};
}

inline gp_Parab cast_to_gp(const parabola_t &a) {
  return gp_Parab(cast_to_gp(a.a2), a.focal);
}

inline parabola_t cast_from_gp(const gp_Parab &a) {
  return parabola_t{cast_from_gp(a.Position()), a.Focal()};
}

inline gp_Parab2d cast_to_gp(const parabola2d_t &a) {
  return gp_Parab2d(cast_to_gp(a.a2), a.focal);
}

inline parabola2d_t cast_from_gp(const gp_Parab2d &a) {
  return parabola2d_t{cast_from_gp(a.Axis()), a.Focal()};
}

inline gp_Pln cast_to_gp(const plane_t &a) { return gp_Pln(cast_to_gp(a.p)); }

inline plane_t cast_from_gp(const gp_Pln &a) {
  return plane_t{cast_from_gp(a.Position())};
}

inline gp_Quaternion cast_to_gp(const quaternion_t &p) {
  return gp_Quaternion{
      static_cast<Standard_Real>(p.q[0]), static_cast<Standard_Real>(p.q[1]),
      static_cast<Standard_Real>(p.q[2]), static_cast<Standard_Real>(p.q[3])};
}

inline quaternion_t cast_from_gp(const gp_Quaternion &p) {
  return quaternion_t{{p.X(), p.Y(), p.Z(), p.W()}};
}

inline gp_QuaternionNLerp cast_to_gp(const quat_n_lerp_t &a) {
  return gp_QuaternionNLerp(cast_to_gp(a.start), cast_to_gp(a.end));
}

inline gp_QuaternionSLerp cast_to_gp(const quat_s_lerp_t &a) {
  return gp_QuaternionSLerp(cast_to_gp(a.start), cast_to_gp(a.end));
}

inline gp_Sphere cast_to_gp(const sphere_t &a) {
  return gp_Sphere(cast_to_gp(a.a3), a.radius);
}

inline sphere_t cast_from_gp(const gp_Sphere &a) {
  return sphere_t{cast_from_gp(a.Position()), a.Radius()};
}

inline gp_Torus cast_to_gp(const torus_t &a) {
  return gp_Torus(cast_to_gp(a.a3), a.major_radius, a.minor_radius);
}

inline torus_t cast_from_gp(const gp_Torus &a) {
  return torus_t{cast_from_gp(a.Position()), a.MajorRadius(), a.MinorRadius()};
}

inline gp_Trsf cast_to_gp(const trsf_t &a) {
  gp_Trsf tr;
  tr.SetValues(a.m[0], a.m[1], a.m[2], a.m[3], a.m[4], a.m[5], a.m[6], a.m[7],
               a.m[8], a.m[9], a.m[10], a.m[11]);
  return tr;
}

inline trsf_t cast_from_gp(const gp_Trsf &mat) {
  return trsf_t{{mat.Value(1, 1), mat.Value(1, 2), mat.Value(1, 3),
                 mat.Value(1, 4), mat.Value(2, 1), mat.Value(2, 2),
                 mat.Value(2, 3), mat.Value(2, 4), mat.Value(3, 1),
                 mat.Value(3, 2), mat.Value(3, 3), mat.Value(3, 4)}};
}

inline gp_Trsf2d cast_to_gp(const trsf2d_t &a) {
  gp_Trsf2d tr;
  tr.SetValues(a.m[0], a.m[1], a.m[2], a.m[3], a.m[4], a.m[5]);
  return tr;
}

inline trsf2d_t cast_from_gp(const gp_Trsf2d &mat) {
  return trsf2d_t{{mat.Value(1, 1), mat.Value(1, 2), mat.Value(1, 3),
                   mat.Value(2, 1), mat.Value(2, 2), mat.Value(2, 3)}};
}

inline Quantity_Color cast_to_gp(const color_t &a) {
  return Quantity_Color{a.r, a.g, a.b, Quantity_TOC_RGB};
}

inline color_t cast_from_gp(const Quantity_Color &mat) {
  return color_t{mat.Red(), mat.Green(), mat.Blue()};
}

inline Bnd_Box cast_to_gp(const bbox_t &a) {
  Bnd_Box b;
  b.Update(a.minx, a.miny, a.minz, a.maxx, a.maxy, a.maxz);
  return b;
}

inline bbox_t cast_from_gp(const Bnd_Box &b) {
  bbox_t a;
  b.Get(a.minx, a.miny, a.minz, a.maxx, a.maxy, a.maxz);
  return a;
}

inline TColgp_Array1OfPnt &cast_to_gp(const std::vector<pnt3d_t> &a,
                                      TColgp_Array1OfPnt &dst) {
  if (dst.Length() != a.size()) {
    dst.Resize(0, a.size() - 1, Standard_False);
  }
  for (int i = 0; i < a.size(); i++) {
    dst.SetValue(i + dst.Lower(), gp_Pnt{cast_to_gp(a[i])});
  }
  return dst;
}

inline std::vector<pnt3d_t> cast_from_gp(const TColgp_Array1OfPnt &a) {
  std::vector<pnt3d_t> dst;
  dst.resize(a.Length());
  for (int i = a.Lower(); i <= a.Upper(); i++) {
    dst[i] = cast_from_gp(a.Value(i));
  }
  return dst;
}

inline TColgp_HArray1OfPnt &cast_to_gp(const std::vector<pnt3d_t> &a,
                                       TColgp_HArray1OfPnt &dst) {
  if (dst.Length() != a.size()) {
    dst.Resize(0, a.size() - 1, Standard_False);
  }
  for (int i = 0; i < a.size(); i++) {
    dst.SetValue(i + dst.Lower(), gp_Pnt{cast_to_gp(a[i])});
  }
  return dst;
}

inline std::vector<pnt3d_t> cast_from_gp(const TColgp_HArray1OfPnt &a) {
  std::vector<pnt3d_t> dst;
  dst.resize(a.Length());
  for (int i = a.Lower(); i <= a.Upper(); i++) {
    dst[i] = cast_from_gp(a.Value(i));
  }
  return dst;
}

inline TColStd_Array1OfReal &cast_to_gp(const std::vector<Standard_Real> &a,
                                        TColStd_Array1OfReal &dst) {
  if (dst.Length() != a.size()) {
    dst.Resize(0, a.size() - 1, Standard_False);
  }
  for (int i = 0; i < a.size(); i++) {
    dst.SetValue(i + dst.Lower(), a[i]);
  }
  return dst;
}

inline std::vector<Standard_Real> cast_from_gp(const TColStd_Array1OfReal &a) {
  std::vector<Standard_Real> dst;
  dst.resize(a.Length());
  for (int i = a.Lower(); i <= a.Upper(); i++) {
    dst[i] = a.Value(i);
  }
  return dst;
}

inline TColStd_Array1OfInteger &
cast_to_gp(const std::vector<Standard_Integer> &a,
           TColStd_Array1OfInteger &dst) {
  if (dst.Length() != a.size()) {
    dst.Resize(0, a.size() - 1, Standard_False);
  }
  for (int i = 0; i < a.size(); i++) {
    dst.SetValue(i, a[i]);
  }
  return dst;
}

inline std::vector<Standard_Integer>
cast_from_gp(const TColStd_Array1OfInteger &a) {
  std::vector<Standard_Integer> dst;
  dst.resize(a.Length());
  for (int i = a.Lower(); i <= a.Upper(); i++) {
    dst[i] = a.Value(i);
  }
  return dst;
}

inline TColgp_Array1OfCirc2d &cast_to_gp(const std::vector<circ2d_t> &a,
                                         TColgp_Array1OfCirc2d &dst) {
  if (dst.Length() != a.size()) {
    dst.Resize(0, a.size() - 1, Standard_False);
  }
  for (int i = 0; i < a.size(); i++) {
    dst.SetValue(i + dst.Lower(), cast_to_gp(a[i]));
  }
  return dst;
}
inline std::vector<circ2d_t> cast_from_gp(const TColgp_Array1OfCirc2d &a) {
  std::vector<circ2d_t> dst;
  dst.resize(a.Length());
  for (int i = a.Lower(); i <= a.Upper(); i++) {
    dst[i] = cast_from_gp(a.Value(i));
  }
  return dst;
}

inline TColgp_Array1OfDir &cast_to_gp(const std::vector<dir3d_t> &a,
                                      TColgp_Array1OfDir &dst) {
  if (dst.Length() != a.size()) {
    dst.Resize(0, a.size() - 1, Standard_False);
  }
  for (int i = 0; i < a.size(); i++) {
    dst.SetValue(i + dst.Lower(), cast_to_gp(a[i]));
  }
  return dst;
}
inline std::vector<dir3d_t> cast_from_gp(const TColgp_Array1OfDir &a) {
  std::vector<dir3d_t> dst;
  dst.resize(a.Length());
  for (int i = a.Lower(); i <= a.Upper(); i++) {
    dst[i] = cast_from_gp(a.Value(i));
  }
  return dst;
}

inline TColgp_Array1OfDir2d &cast_to_gp(const std::vector<dir2d_t> &a,
                                        TColgp_Array1OfDir2d &dst) {
  if (dst.Length() != a.size()) {
    dst.Resize(0, a.size() - 1, Standard_False);
  }
  for (int i = 0; i < a.size(); i++) {
    dst.SetValue(i + dst.Lower(), cast_to_gp(a[i]));
  }
  return dst;
}

inline std::vector<dir2d_t> cast_from_gp(const TColgp_Array1OfDir2d &a) {
  std::vector<dir2d_t> dst;
  dst.resize(a.Length());
  for (int i = a.Lower(); i <= a.Upper(); i++) {
    dst[i] = cast_from_gp(a.Value(i));
  }
  return dst;
}

inline TColgp_Array1OfLin2d &cast_to_gp(const std::vector<line2d_t> &a,
                                        TColgp_Array1OfLin2d &dst) {
  if (dst.Length() != a.size()) {
    dst.Resize(0, a.size() - 1, Standard_False);
  }
  for (int i = 0; i < a.size(); i++) {
    dst.SetValue(i + dst.Lower(), cast_to_gp(a[i]));
  }
  return dst;
}

inline std::vector<line2d_t> cast_from_gp(const TColgp_Array1OfLin2d &a) {
  std::vector<line2d_t> dst;
  dst.resize(a.Length());
  for (int i = a.Lower(); i <= a.Upper(); i++) {
    dst[i] = cast_from_gp(a.Value(i));
  }
  return dst;
}

inline TColgp_Array1OfPnt2d &cast_to_gp(const std::vector<pnt2d_t> &a,
                                        TColgp_Array1OfPnt2d &dst) {
  if (dst.Length() != a.size()) {
    dst.Resize(0, a.size() - 1, Standard_False);
  }
  for (int i = 0; i < a.size(); i++) {
    dst.SetValue(i + dst.Lower(), gp_Pnt2d{cast_to_gp(a[i])});
  }
  return dst;
}

inline std::vector<pnt2d_t> cast_from_gp(const TColgp_Array1OfPnt2d &a) {
  std::vector<pnt2d_t> dst;
  dst.resize(a.Length());
  for (int i = a.Lower(); i <= a.Upper(); i++) {
    dst[i] = cast_from_gp(a.Value(i));
  }
  return dst;
}

inline TColgp_Array1OfVec &cast_to_gp(const std::vector<vec3d_t> &a,
                                      TColgp_Array1OfVec &dst) {
  if (dst.Length() != a.size()) {
    dst.Resize(0, a.size() - 1, Standard_False);
  }
  for (int i = 0; i < a.size(); i++) {
    dst.SetValue(i + dst.Lower(), cast_to_gp(a[i]));
  }
  return dst;
}

inline std::vector<vec3d_t> cast_from_gp(const TColgp_Array1OfVec &a) {
  std::vector<vec3d_t> dst;
  dst.resize(a.Length());
  for (int i = a.Lower(); i <= a.Upper(); i++) {
    dst[i] = cast_from_gp(a.Value(i));
  }
  return dst;
}

inline TColgp_Array1OfVec2d &cast_to_gp(const std::vector<vec2d_t> &a,
                                        TColgp_Array1OfVec2d &dst) {
  if (dst.Length() != a.size()) {
    dst.Resize(0, a.size() - 1, Standard_False);
  }
  for (int i = 0; i < a.size(); i++) {
    dst.SetValue(i + dst.Lower(), cast_to_gp(a[i]));
  }
  return dst;
}

inline std::vector<vec2d_t> cast_from_gp(const TColgp_Array1OfVec2d &a) {
  std::vector<vec2d_t> dst;
  dst.resize(a.Length());
  for (int i = a.Lower(); i <= a.Upper(); i++) {
    dst[i] = cast_from_gp(a.Value(i));
  }
  return dst;
}

inline TColgp_Array1OfXY &cast_to_gp(const std::vector<xy_t> &a,
                                     TColgp_Array1OfXY &dst) {
  if (dst.Length() != a.size()) {
    dst.Resize(0, a.size() - 1, Standard_False);
  }
  for (int i = 0; i < a.size(); i++) {
    dst.SetValue(i + dst.Lower(), cast_to_gp(a[i]));
  }
  return dst;
}

inline std::vector<xy_t> cast_from_gp(const TColgp_Array1OfXY &a) {
  std::vector<xy_t> dst;
  dst.resize(a.Length());
  for (int i = a.Lower(); i <= a.Upper(); i++) {
    dst[i] = cast_from_gp(a.Value(i));
  }
  return dst;
}

inline TColgp_Array1OfXYZ &cast_to_gp(const std::vector<xyz_t> &a,
                                      TColgp_Array1OfXYZ &dst) {
  if (dst.Length() != a.size()) {
    dst.Resize(0, a.size() - 1, Standard_False);
  }
  for (int i = 0; i < a.size(); i++) {
    dst.SetValue(i + dst.Lower(), cast_to_gp(a[i]));
  }
  return dst;
}

inline std::vector<xyz_t> cast_from_gp(const TColgp_Array1OfXYZ &a) {
  std::vector<xyz_t> dst;
  dst.resize(a.Length());
  for (int i = a.Lower(); i <= a.Upper(); i++) {
    dst[i] = cast_from_gp(a.Value(i));
  }
  return dst;
}

inline TColgp_Array2OfCirc2d &
cast_to_gp(const std::vector<std::vector<circ2d_t>> &a,
           TColgp_Array2OfCirc2d &dst) {
  if (dst.RowLength() != a.size() ||
      dst.ColLength() != (a.empty() ? 0 : a[0].size())) {
    dst.Resize(0, a.size() - 1, 0, a.empty() ? 0 : a[0].size() - 1,
               Standard_False);
  }
  for (int i = 0; i < a.size(); i++) {
    for (int j = 0; j < a[i].size(); j++) {
      dst.SetValue(i, j, cast_to_gp(a[i][j]));
    }
  }
  return dst;
}

inline std::vector<std::vector<circ2d_t>>
cast_from_gp(const TColgp_Array2OfCirc2d &a) {
  std::vector<std::vector<circ2d_t>> dst;
  dst.resize(a.RowLength());
  for (int i = a.LowerRow(); i <= a.UpperRow(); i++) {
    dst[i].resize(a.ColLength());
    for (int j = a.LowerCol(); j <= a.UpperCol(); j++) {
      dst[i][j] = cast_from_gp(a.Value(i, j));
    }
  }
  return dst;
}

inline TColgp_Array2OfDir &
cast_to_gp(const std::vector<std::vector<dir3d_t>> &a,
           TColgp_Array2OfDir &dst) {
  if (dst.RowLength() != a.size() ||
      dst.ColLength() != (a.empty() ? 0 : a[0].size())) {
    dst.Resize(0, a.size() - 1, 0, a.empty() ? 0 : a[0].size() - 1,
               Standard_False);
  }
  for (int i = 0; i < a.size(); i++) {
    for (int j = 0; j < a[i].size(); j++) {
      dst.SetValue(i, j, cast_to_gp(a[i][j]));
    }
  }
  return dst;
}

inline std::vector<std::vector<dir3d_t>>
cast_from_gp(const TColgp_Array2OfDir &a) {
  std::vector<std::vector<dir3d_t>> dst;
  dst.resize(a.RowLength());
  for (int i = a.LowerRow(); i <= a.UpperRow(); i++) {
    dst[i].resize(a.ColLength());
    for (int j = a.LowerCol(); j <= a.UpperCol(); j++) {
      dst[i][j] = cast_from_gp(a.Value(i, j));
    }
  }
  return dst;
}

inline TColgp_Array2OfDir2d &
cast_to_gp(const std::vector<std::vector<dir2d_t>> &a,
           TColgp_Array2OfDir2d &dst) {
  if (dst.RowLength() != a.size() ||
      dst.ColLength() != (a.empty() ? 0 : a[0].size())) {
    dst.Resize(0, a.size() - 1, 0, a.empty() ? 0 : a[0].size() - 1,
               Standard_False);
  }
  for (int i = 0; i < a.size(); i++) {
    for (int j = 0; j < a[i].size(); j++) {
      dst.SetValue(i, j, cast_to_gp(a[i][j]));
    }
  }
  return dst;
}

inline std::vector<std::vector<dir2d_t>>
cast_from_gp(const TColgp_Array2OfDir2d &a) {
  std::vector<std::vector<dir2d_t>> dst;
  dst.resize(a.RowLength());
  for (int i = a.LowerRow(); i <= a.UpperRow(); i++) {
    dst[i].resize(a.ColLength());
    for (int j = a.LowerCol(); j <= a.UpperCol(); j++) {
      dst[i][j] = cast_from_gp(a.Value(i, j));
    }
  }
  return dst;
}

inline TColgp_Array2OfLin2d &
cast_to_gp(const std::vector<std::vector<line2d_t>> &a,
           TColgp_Array2OfLin2d &dst) {
  if (dst.RowLength() != a.size() ||
      dst.ColLength() != (a.empty() ? 0 : a[0].size())) {
    dst.Resize(0, a.size() - 1, 0, a.empty() ? 0 : a[0].size() - 1,
               Standard_False);
  }
  for (int i = 0; i < a.size(); i++) {
    for (int j = 0; j < a[i].size(); j++) {
      dst.SetValue(i, j, cast_to_gp(a[i][j]));
    }
  }
  return dst;
}

inline std::vector<std::vector<line2d_t>>
cast_from_gp(const TColgp_Array2OfLin2d &a) {
  std::vector<std::vector<line2d_t>> dst;
  dst.resize(a.RowLength());
  for (int i = a.LowerRow(); i <= a.UpperRow(); i++) {
    dst[i].resize(a.ColLength());
    for (int j = a.LowerCol(); j <= a.UpperCol(); j++) {
      dst[i][j] = cast_from_gp(a.Value(i, j));
    }
  }
  return dst;
}

inline TColgp_Array2OfPnt &
cast_to_gp(const std::vector<std::vector<pnt3d_t>> &a,
           TColgp_Array2OfPnt &dst) {
  if (dst.RowLength() != a.size() ||
      dst.ColLength() != (a.empty() ? 0 : a[0].size())) {
    dst.Resize(0, a.size() - 1, 0, a.empty() ? 0 : a[0].size() - 1,
               Standard_False);
  }
  for (int i = 0; i < a.size(); i++) {
    for (int j = 0; j < a[i].size(); j++) {
      dst.SetValue(i, j, cast_to_gp(a[i][j]));
    }
  }
  return dst;
}

inline std::vector<std::vector<pnt3d_t>>
cast_from_gp(const TColgp_Array2OfPnt &a) {
  std::vector<std::vector<pnt3d_t>> dst;
  dst.resize(a.RowLength());
  for (int i = a.LowerRow(); i <= a.UpperRow(); i++) {
    dst[i].resize(a.ColLength());
    for (int j = a.LowerCol(); j <= a.UpperCol(); j++) {
      dst[i][j] = cast_from_gp(a.Value(i, j));
    }
  }
  return dst;
}

inline TColgp_Array2OfPnt2d &
cast_to_gp(const std::vector<std::vector<pnt2d_t>> &a,
           TColgp_Array2OfPnt2d &dst) {
  if (dst.RowLength() != a.size() ||
      dst.ColLength() != (a.empty() ? 0 : a[0].size())) {
    dst.Resize(0, a.size() - 1, 0, a.empty() ? 0 : a[0].size() - 1,
               Standard_False);
  }
  for (int i = 0; i < a.size(); i++) {
    for (int j = 0; j < a[i].size(); j++) {
      dst.SetValue(i, j, cast_to_gp(a[i][j]));
    }
  }
  return dst;
}

inline std::vector<std::vector<pnt2d_t>>
cast_from_gp(const TColgp_Array2OfPnt2d &a) {
  std::vector<std::vector<pnt2d_t>> dst;
  dst.resize(a.RowLength());
  for (int i = a.LowerRow(); i <= a.UpperRow(); i++) {
    dst[i].resize(a.ColLength());
    for (int j = a.LowerCol(); j <= a.UpperCol(); j++) {
      dst[i][j] = cast_from_gp(a.Value(i, j));
    }
  }
  return dst;
}

inline TColgp_Array2OfVec &
cast_to_gp(const std::vector<std::vector<vec3d_t>> &a,
           TColgp_Array2OfVec &dst) {
  if (dst.RowLength() != a.size() ||
      dst.ColLength() != (a.empty() ? 0 : a[0].size())) {
    dst.Resize(0, a.size() - 1, 0, a.empty() ? 0 : a[0].size() - 1,
               Standard_False);
  }
  for (int i = 0; i < a.size(); i++) {
    for (int j = 0; j < a[i].size(); j++) {
      dst.SetValue(i, j, cast_to_gp(a[i][j]));
    }
  }
  return dst;
}

inline std::vector<std::vector<vec3d_t>>
cast_from_gp(const TColgp_Array2OfVec &a) {
  std::vector<std::vector<vec3d_t>> dst;
  dst.resize(a.RowLength());
  for (int i = a.LowerRow(); i <= a.UpperRow(); i++) {
    dst[i].resize(a.ColLength());
    for (int j = a.LowerCol(); j <= a.UpperCol(); j++) {
      dst[i][j] = cast_from_gp(a.Value(i, j));
    }
  }
  return dst;
}

inline TColgp_Array2OfVec2d &
cast_to_gp(const std::vector<std::vector<vec2d_t>> &a,
           TColgp_Array2OfVec2d &dst) {
  if (dst.RowLength() != a.size() ||
      dst.ColLength() != (a.empty() ? 0 : a[0].size())) {
    dst.Resize(0, a.size() - 1, 0, a.empty() ? 0 : a[0].size() - 1,
               Standard_False);
  }
  for (int i = 0; i < a.size(); i++) {
    for (int j = 0; j < a[i].size(); j++) {
      dst.SetValue(i, j, cast_to_gp(a[i][j]));
    }
  }
  return dst;
}

inline std::vector<std::vector<vec2d_t>>
cast_from_gp(const TColgp_Array2OfVec2d &a) {
  std::vector<std::vector<vec2d_t>> dst;
  dst.resize(a.RowLength());
  for (int i = a.LowerRow(); i <= a.UpperRow(); i++) {
    dst[i].resize(a.ColLength());
    for (int j = a.LowerCol(); j <= a.UpperCol(); j++) {
      dst[i][j] = cast_from_gp(a.Value(i, j));
    }
  }
  return dst;
}

inline TColgp_Array2OfXY &cast_to_gp(const std::vector<std::vector<xy_t>> &a,
                                     TColgp_Array2OfXY &dst) {
  if (dst.RowLength() != a.size() ||
      dst.ColLength() != (a.empty() ? 0 : a[0].size())) {
    dst.Resize(0, a.size() - 1, 0, a.empty() ? 0 : a[0].size() - 1,
               Standard_False);
  }
  for (int i = 0; i < a.size(); i++) {
    for (int j = 0; j < a[i].size(); j++) {
      dst.SetValue(i, j, cast_to_gp(a[i][j]));
    }
  }
  return dst;
}

inline std::vector<std::vector<xy_t>> cast_from_gp(const TColgp_Array2OfXY &a) {
  std::vector<std::vector<xy_t>> dst;
  dst.resize(a.RowLength());
  for (int i = a.LowerRow(); i <= a.UpperRow(); i++) {
    dst[i].resize(a.ColLength());
    for (int j = a.LowerCol(); j <= a.UpperCol(); j++) {
      dst[i][j] = cast_from_gp(a.Value(i, j));
    }
  }
  return dst;
}

inline TColgp_Array2OfXYZ &cast_to_gp(const std::vector<std::vector<xyz_t>> &a,
                                      TColgp_Array2OfXYZ &dst) {
  if (dst.RowLength() != a.size() ||
      dst.ColLength() != (a.empty() ? 0 : a[0].size())) {
    dst.Resize(0, a.size() - 1, 0, a.empty() ? 0 : a[0].size() - 1,
               Standard_False);
  }
  for (int i = 0; i < a.size(); i++) {
    for (int j = 0; j < a[i].size(); j++) {
      dst.SetValue(i, j, cast_to_gp(a[i][j]));
    }
  }
  return dst;
}

inline std::vector<std::vector<xyz_t>>
cast_from_gp(const TColgp_Array2OfXYZ &a) {
  std::vector<std::vector<xyz_t>> dst;
  dst.resize(a.RowLength());
  for (int i = a.LowerRow(); i <= a.UpperRow(); i++) {
    dst[i].resize(a.ColLength());
    for (int j = a.LowerCol(); j <= a.UpperCol(); j++) {
      dst[i][j] = cast_from_gp(a.Value(i, j));
    }
  }
  return dst;
}

inline TColStd_Array2OfReal &
cast_to_gp(const std::vector<std::vector<Standard_Real>> &a,
           TColStd_Array2OfReal &dst) {
  if (dst.RowLength() != a.size() ||
      dst.ColLength() != (a.empty() ? 0 : a[0].size())) {
    dst.Resize(0, a.size() - 1, 0, a.empty() ? 0 : a[0].size() - 1,
               Standard_False);
  }
  for (int i = 0; i < a.size(); i++) {
    for (int j = 0; j < a[i].size(); j++) {
      dst.SetValue(i, j, a[i][j]);
    }
  }
  return dst;
}

inline std::vector<std::vector<Standard_Real>>
cast_from_gp(const TColStd_Array2OfReal &a) {
  std::vector<std::vector<Standard_Real>> dst;
  dst.resize(a.RowLength());
  for (int i = a.LowerRow(); i <= a.UpperRow(); i++) {
    dst[i].resize(a.ColLength());
    for (int j = a.LowerCol(); j <= a.UpperCol(); j++) {
      dst[i][j] = a.Value(i, j);
    }
  }
  return dst;
}

inline std::list<std::vector<pnt2d_t>>
cast_from_gp(const TColgp_SequenceOfArray1OfPnt2d &a) {
  std::list<std::vector<pnt2d_t>> dst;
  for (int i = 0; i < a.Length(); i++) {
    dst.push_back(cast_from_gp(a.Value(i)->Array1()));
  }
  return dst;
}

inline TColgp_SequenceOfArray1OfPnt2d &
cast_to_gp(const std::list<std::vector<pnt2d_t>> &a,
           TColgp_SequenceOfArray1OfPnt2d &dst) {
  dst.Clear();
  for (auto &s : a) {
    Handle(TColgp_HArray1OfPnt2d) arr = new TColgp_HArray1OfPnt2d(0, s.size());
    for (int i = 0; i < s.size(); i++) {
      arr->SetValue(i, cast_to_gp(s[i]));
    }
    dst.Append(arr);
  }
  return dst;
}

inline std::list<axis1_t> cast_from_gp(const TColgp_SequenceOfAx1 &a) {
  std::list<axis1_t> dst;
  for (int i = 0; i < a.Length(); i++) {
    dst.push_back(cast_from_gp(a.Value(i)));
  }
  return dst;
}

inline TColgp_SequenceOfAx1 &cast_to_gp(const std::list<axis1_t> &a,
                                        TColgp_SequenceOfAx1 &dst) {
  dst.Clear();

  for (auto &s : a) {
    dst.Append(cast_to_gp(s));
  }
  return dst;
}

inline std::list<dir3d_t> cast_from_gp(const TColgp_SequenceOfDir &a) {
  std::list<dir3d_t> dst;
  for (int i = 0; i < a.Length(); i++) {
    dst.push_back(cast_from_gp(a.Value(i)));
  }
  return dst;
}

inline TColgp_SequenceOfDir &cast_to_gp(const std::list<dir3d_t> &a,
                                        TColgp_SequenceOfDir &dst) {
  dst.Clear();
  for (auto &s : a) {
    dst.Append(cast_to_gp(s));
  }
  return dst;
}

inline std::list<dir2d_t> cast_from_gp(const TColgp_SequenceOfDir2d &a) {
  std::list<dir2d_t> dst;
  for (int i = 0; i < a.Length(); i++) {
    dst.push_back(cast_from_gp(a.Value(i)));
  }
  return dst;
}

inline TColgp_SequenceOfDir2d &cast_to_gp(const std::list<dir2d_t> &a,
                                          TColgp_SequenceOfDir2d &dst) {
  dst.Clear();
  for (auto &s : a) {
    dst.Append(cast_to_gp(s));
  }
  return dst;
}

inline std::list<pnt2d_t> cast_from_gp(const TColgp_SequenceOfPnt2d &a) {
  std::list<pnt2d_t> dst;
  for (int i = 0; i < a.Length(); i++) {
    dst.push_back(cast_from_gp(a.Value(i)));
  }
  return dst;
}

inline TColgp_SequenceOfPnt2d &cast_to_gp(const std::list<pnt2d_t> &a,
                                          TColgp_SequenceOfPnt2d &dst) {
  dst.Clear();
  for (auto &s : a) {
    dst.Append(cast_to_gp(s));
  }
  return dst;
}

inline std::list<pnt3d_t> cast_from_gp(const TColgp_SequenceOfPnt &a) {
  std::list<pnt3d_t> dst;
  for (int i = 0; i < a.Length(); i++) {
    dst.push_back(cast_from_gp(a.Value(i)));
  }
  return dst;
}

inline TColgp_SequenceOfPnt &cast_to_gp(const std::list<pnt3d_t> &a,
                                        TColgp_SequenceOfPnt &dst) {
  dst.Clear();
  for (auto &s : a) {
    dst.Append(cast_to_gp(s));
  }
  return dst;
}

inline std::list<vec3d_t> cast_from_gp(const TColgp_SequenceOfVec &a) {
  std::list<vec3d_t> dst;
  for (int i = 0; i < a.Length(); i++) {
    dst.push_back(cast_from_gp(a.Value(i)));
  }
  return dst;
}

inline TColgp_SequenceOfVec &cast_to_gp(const std::list<vec3d_t> &a,
                                        TColgp_SequenceOfVec &dst) {
  dst.Clear();
  for (auto &s : a) {
    dst.Append(cast_to_gp(s));
  }
  return dst;
}

inline std::list<vec2d_t> cast_from_gp(const TColgp_SequenceOfVec2d &a) {
  std::list<vec2d_t> dst;
  for (int i = 0; i < a.Length(); i++) {
    dst.push_back(cast_from_gp(a.Value(i)));
  }
  return dst;
}

inline TColgp_SequenceOfVec2d &cast_to_gp(const std::list<vec2d_t> &a,
                                          TColgp_SequenceOfVec2d &dst) {
  dst.Clear();
  for (auto &s : a) {
    dst.Append(cast_to_gp(s));
  }
  return dst;
}

inline std::list<xy_t> cast_from_gp(const TColgp_SequenceOfXY &a) {
  std::list<xy_t> dst;
  for (int i = 0; i < a.Length(); i++) {
    dst.push_back(cast_from_gp(a.Value(i)));
  }
  return dst;
}

inline TColgp_SequenceOfXY &cast_to_gp(const std::list<xy_t> &a,
                                       TColgp_SequenceOfXY &dst) {
  dst.Clear();
  for (auto &s : a) {
    dst.Append(cast_to_gp(s));
  }
  return dst;
}

inline std::list<xyz_t> cast_from_gp(const TColgp_SequenceOfXYZ &a) {
  std::list<xyz_t> dst;
  for (int i = 0; i < a.Length(); i++) {
    dst.push_back(cast_from_gp(a.Value(i)));
  }
  return dst;
}

inline TColgp_SequenceOfXYZ &cast_to_gp(const std::list<xyz_t> &a,
                                        TColgp_SequenceOfXYZ &dst) {
  dst.Clear();
  for (auto &s : a) {
    dst.Append(cast_to_gp(s));
  }
  return dst;
}

template <typename D, typename T>
inline NCollection_Array1<D> cast_to_gp(const std::vector<T> &a) {
  NCollection_Array1<D> dst(0, a.size());
  for (int i = 0; i < a.size(); i++) {
    dst.SetValue(i, D{cast_to_gp(a[i])});
  }
  return dst;
}

template <typename T>
inline std::vector<decltype(cast_from_gp(std::declval<const T &>()))>
cast_from_gp(const NCollection_Array1<T> &a) {
  std::vector<decltype(cast_from_gp(std::declval<const T &>()))> dst;
  dst.resize(a.Size());
  for (int i = a.Lower(); i <= a.Upper(); i++) {
    dst[i] = cast_from_gp(a[i]);
  }
}
#endif
