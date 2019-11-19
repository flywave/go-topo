package topovis

/*
#include <stdlib.h>
#include "standard_c_api.h"
#cgo CFLAGS: -I ./
#cgo linux CXXFLAGS: -I ./include/oce -I ./include/linux/oce -I ./
#cgo darwin CXXFLAGS: -I ./include/oce -I ./include/darwin/oce -I ./
#cgo windows CXXFLAGS:  -I ./include/oce -I ./include/windows/oce -I ./
*/
import "C"

type XYZ struct {
	val C.struct__xyz_t
}

func (d XYZ) Data() [3]float64 {
	return [3]float64{float64(d.val.x), float64(d.val.y), float64(d.val.z)}
}

func NewXYZ(d [3]float64) XYZ {
	var o C.struct__xyz_t
	o.x = C.double(d[0])
	o.y = C.double(d[1])
	o.z = C.double(d[2])
	return XYZ{val: o}
}

type Point3 struct {
	val C.struct__pnt3d_t
}

func (d Point3) Data() [3]float64 {
	return [3]float64{float64(d.val.x), float64(d.val.y), float64(d.val.z)}
}

func NewPoint3(d [3]float64) Point3 {
	var o C.struct__pnt3d_t
	o.x = C.double(d[0])
	o.y = C.double(d[1])
	o.z = C.double(d[2])
	return Point3{val: o}
}

type Vector3 struct {
	val C.struct__vec3d_t
}

func (d Vector3) Data() [3]float64 {
	return [3]float64{float64(d.val.x), float64(d.val.y), float64(d.val.z)}
}

func NewVector3(d [3]float64) Vector3 {
	var o C.struct__vec3d_t
	o.x = C.double(d[0])
	o.y = C.double(d[1])
	o.z = C.double(d[2])
	return Vector3{val: o}
}

type Dir3 struct {
	val C.struct__dir3d_t
}

func (d Dir3) Data() [3]float64 {
	return [3]float64{float64(d.val.x), float64(d.val.y), float64(d.val.z)}
}

func NewDir3FromVector(v Vector3) Dir3 {
	return Dir3{val: C.make_dir(v.val)}
}

func NewDir3FromXYZ(d [3]float64) Dir3 {
	return Dir3{val: C.make_dir_from_xyz(C.double(d[0]), C.double(d[1]), C.double(d[2]))}
}

func NewDir3FromPoint(p1, p2 Point3) Dir3 {
	return Dir3{val: C.make_dir_from_point(p1.val, p2.val)}
}

type XY struct {
	val C.struct__xy_t
}

func (d XY) Data() [2]float64 {
	return [2]float64{float64(d.val.x), float64(d.val.y)}
}

func NewXY(d [2]float64) XY {
	var o C.struct__xy_t
	o.x = C.double(d[0])
	o.y = C.double(d[1])
	return XY{val: o}
}

type Point2 struct {
	val C.struct__pnt2d_t
}

func (d Point2) Data() [2]float64 {
	return [2]float64{float64(d.val.x), float64(d.val.y)}
}

func NewPoint2(d [2]float64) Point2 {
	var o C.struct__pnt2d_t
	o.x = C.double(d[0])
	o.y = C.double(d[1])
	return Point2{val: o}
}

type Vector2 struct {
	val C.struct__vec2d_t
}

func (d Vector2) Data() [2]float64 {
	return [2]float64{float64(d.val.x), float64(d.val.y)}
}

func NewVector2(d [2]float64) Vector2 {
	var o C.struct__vec2d_t
	o.x = C.double(d[0])
	o.y = C.double(d[1])
	return Vector2{val: o}
}

type Dir2 struct {
	val C.struct__dir2d_t
}

func (d Dir2) Data() [2]float64 {
	return [2]float64{float64(d.val.x), float64(d.val.y)}
}

func NewDir2(d [2]float64) Dir2 {
	var o C.struct__dir2d_t
	o.x = C.double(d[0])
	o.y = C.double(d[1])
	return Dir2{val: o}
}

func NewDir2FromVector(v Vector2) Dir2 {
	return Dir2{val: C.make_dir2d(v.val)}
}

func NewDir2FromXY(d [2]float64) Dir2 {
	return Dir2{val: C.make_dir2d_from_xy(C.double(d[0]), C.double(d[1]))}
}

func NewDir2FromPoint(p1, p2 Point2) Dir2 {
	return Dir2{val: C.make_dir2d_from_point(p1.val, p2.val)}
}

type Axis1 struct {
	val C.struct__axis1_t
}

func NewAxis1(p Point3, d Dir3) Axis1 {
	return Axis1{val: C.make_axis(p.val, d.val)}
}

type Axis2 struct {
	val C.struct__axis2_t
}

func NewAxis2FromNVX(p Point3, n Dir3, x Dir3) Axis2 {
	return Axis2{val: C.make_axis2_from_nvx(p.val, n.val, x.val)}
}

func NewAxis2(p Point3, d Dir3) Axis2 {
	return Axis2{val: C.make_axis2(p.val, d.val)}
}

type Axis3 struct {
	val C.struct__axis3_t
}

func NewAxis3FromV(p Point3, v Dir3) Axis3 {
	return Axis3{val: C.make_axis3_from_v(p.val, v.val)}
}

func NewAxis3FromNVX(p Point3, n Dir3, x Dir3) Axis3 {
	return Axis3{val: C.make_axis3_from_nvx(p.val, n.val, x.val)}
}

func NewAxis3(p Axis2) Axis3 {
	return Axis3{val: C.make_axis3(p.val)}
}

type Axis2d struct {
	val C.struct__axis2d_t
}

func NewAxis2d(p Point2, v Dir2) Axis2d {
	return Axis2d{val: C.make_axis2d(p.val, v.val)}
}

type Axis22d struct {
	val C.struct__axis22d_t
}

func NewAxis22d(p Axis2d) Axis22d {
	return Axis22d{val: C.make_axis22d(p.val)}
}

func NewAxis22dFromV(p Point2, v Dir2) Axis22d {
	return Axis22d{val: C.make_axis22d_from_v(p.val, v.val)}
}

func NewAxis22dFromVXY(p Point2, vx Dir2, vy Dir2) Axis22d {
	return Axis22d{val: C.make_axis22d_from_vxy(p.val, vx.val, vy.val)}
}

type Circ struct {
	val C.struct__circ_t
}

func NewCircFromAxis2(p Axis2, radius float64) Circ {
	return Circ{val: C.make_circ_from_axis2(p.val, C.double(radius))}
}

func NewCircFromCircDist(c Circ, dist float64) Circ {
	return Circ{val: C.make_circ_from_circ_dist(c.val, C.double(dist))}
}

func NewCircFromCircPoint(c Circ, p Point3) Circ {
	return Circ{val: C.make_circ_from_circ_point(c.val, p.val)}
}

func NewCircFromPoint(p1, p2, p3 Point3) Circ {
	return Circ{val: C.make_circ_from_point(p1.val, p2.val, p3.val)}
}

func NewCircFromCenterNorm(center Point3, Norm Dir3, radius float64) Circ {
	return Circ{val: C.make_circ_from_center_norm(center.val, Norm.val, C.double(radius))}
}

func NewCircFromCenterPlane(center Point3, pl Plane, radius float64) Circ {
	return Circ{val: C.make_circ_from_center_plan(center.val, pl.val, C.double(radius))}
}

func NewCircFromAxis1(aa Axis1, radius float64) Circ {
	return Circ{val: C.make_circ_from_axis1(aa.val, C.double(radius))}
}

type Circ2d struct {
	val C.struct__circ2d_t
}

func NewCirc2dFromAxis2d(p Axis2d, radius float64) Circ2d {
	return Circ2d{val: C.make_circ2d_from_axis2(p.val, C.double(radius))}
}

func NewCirc2dFromAxis22d(p Axis22d, radius float64) Circ2d {
	return Circ2d{val: C.make_circ2d_from_axis22d(p.val, C.double(radius))}
}

func NewCirc2dFromCircDist(p Circ2d, dist float64) Circ2d {
	return Circ2d{val: C.make_circ2d_from_circ_dist(p.val, C.double(dist))}
}

func NewCirc2dFromCirc2d(c Circ2d, pnt Point2) Circ2d {
	return Circ2d{val: C.make_circ2d_from_circ2d(c.val, pnt.val)}
}

func NewCirc2dFromPoint(p1, p2, p3 Point2) Circ2d {
	return Circ2d{val: C.make_circ2d_from_point(p1.val, p2.val, p3.val)}
}

func NewCirc2dFromCenterRadius(center Point2, radius float64) Circ2d {
	return Circ2d{val: C.make_circ2d_from_center_radius(center.val, C.double(radius))}
}

func NewCirc2dFromCenterPoint(center Point2, p Point2) Circ2d {
	return Circ2d{val: C.make_circ2d_from_center_point(center.val, p.val)}
}

type Cone struct {
	val C.struct__cone_t
}

func NewConeFromAxis2(a Axis2, ang float64, radius float64) Cone {
	return Cone{val: C.make_cone_from_axis2(a.val, C.double(ang), C.double(radius))}
}

func NewConeFromConePoint(a Cone, p Point3) Cone {
	return Cone{val: C.make_cone_from_cone_point(a.val, p.val)}
}

func NewConeFromConeDist(a Cone, dist float64) Cone {
	return Cone{val: C.make_cone_from_cone_dist(a.val, C.double(dist))}
}

func NewConeFromPoint(p1, p2, p3, p4 Point3) Cone {
	return Cone{val: C.make_cone_from_point(p1.val, p2.val, p3.val, p4.val)}
}

func NewConeFromAxis1Point(a Axis1, p1, p2 Point3) Cone {
	return Cone{val: C.make_cone_from_axis1_point(a.val, p1.val, p2.val)}
}

func NewConeFromLinePoint(l Line, p1, p2 Point3) Cone {
	return Cone{val: C.make_cone_from_line_point(l.val, p1.val, p2.val)}
}

func NewConeFromPointRadius(p1, p2 Point3, r1, r2 float64) Cone {
	return Cone{val: C.make_cone_point_radius(p1.val, p2.val, C.double(r1), C.double(r2))}
}

type Cylinder struct {
	val C.struct__cylinder_t
}

func NewCylinderFromAxis2(a Axis2, radius float64) Cylinder {
	return Cylinder{val: C.make_cylinder_from_axis2(a.val, C.double(radius))}
}

func NewCylinderFromCylinderPoint(a Cylinder, p Point3) Cylinder {
	return Cylinder{val: C.make_cylinder_from_cylinder_point(a.val, p.val)}
}

func NewCylinderFromCylinderDist(a Cylinder, dist float64) Cylinder {
	return Cylinder{val: C.make_cylinder_from_cylinder_dist(a.val, C.double(dist))}
}

func NewCylinderFromPoint(p1, p2, p3 Point3) Cylinder {
	return Cylinder{val: C.make_cylinder_from_point(p1.val, p2.val, p3.val)}
}

func NewCylinderFromAxis1Radius(a Axis1, radius float64) Cylinder {
	return Cylinder{val: C.make_cylinder_from_axis1_radius(a.val, C.double(radius))}
}

func NewCylinderFromCirc(a Circ) Cylinder {
	return Cylinder{val: C.make_cylinder_from_circ(a.val)}
}

type Elips struct {
	val C.struct__elips_t
}

func NewElipsFromAxis2Radius(a Axis2, major_radius, minor_radius float64) Elips {
	return Elips{val: C.make_elips_from_axis2_radius(a.val, C.double(major_radius), C.double(minor_radius))}
}

func NewElipsFromPoint(s1, s2, center Point3) Elips {
	return Elips{val: C.make_elips_point(s1.val, s2.val, center.val)}
}

type Elips2d struct {
	val C.struct__elips2d_t
}

func NewElips2dFromAxis2dRadius(a Axis2d, major_radius, minor_radius float64) Elips2d {
	return Elips2d{val: C.make_elips2d_axis2d_radius(a.val, C.double(major_radius), C.double(minor_radius))}
}

func NewElips2dFromPoint(s1, s2, center Point2) Elips2d {
	return Elips2d{val: C.make_elips2d_point(s1.val, s2.val, center.val)}
}

type Mat3x3 struct {
	val C.struct__mat3x3_t
}

func NewMat3x3(mat [9]float64) Mat3x3 {
	var m C.struct__mat3x3_t
	for i := range mat {
		m.mat[i] = C.double(mat[i])
	}
	return Mat3x3{val: m}
}

type Mat2x2 struct {
	val C.struct__mat2x2_t
}

func NewMat2x2(mat [4]float64) Mat2x2 {
	var m C.struct__mat2x2_t
	for i := range mat {
		m.mat[i] = C.double(mat[i])
	}
	return Mat2x2{val: m}
}

type Transform struct {
	val C.struct__transform_t
}

func NewTransform(mat Mat3x3, v XYZ) Transform {
	var t C.struct__transform_t
	t.m = mat.val
	t.v = v.val
	return Transform{val: t}
}

type Transform2d struct {
	val C.struct__transform2d_t
}

func NewTransform2d(mat Mat2x2, v XY) Transform2d {
	var t C.struct__transform2d_t
	t.m = mat.val
	t.v = v.val
	return Transform2d{val: t}
}

type Hyperbola struct {
	val C.struct__hyperbola_t
}

func NewHyperbolaFromAxis2(a Axis2, major_radius, minor_radius float64) Hyperbola {
	var t C.struct__hyperbola_t
	t.a2 = a.val
	t.major_radius = C.double(major_radius)
	t.minor_radius = C.double(minor_radius)
	return Hyperbola{val: t}
}

func NewHyperbolaFromPoint(s1, s2, center Point3) Hyperbola {
	return Hyperbola{val: C.make_hyperbola_from_point(s1.val, s2.val, center.val)}
}

type Hyperbola2d struct {
	val C.struct__hyperbola2d_t
}

func NewHyperbola2dFromAxis22d(a Axis22d, major_radius, minor_radius float64) Hyperbola2d {
	var t C.struct__hyperbola2d_t
	t.a2 = a.val
	t.major_radius = C.double(major_radius)
	t.minor_radius = C.double(minor_radius)
	return Hyperbola2d{val: t}
}

func NewHyperbola2dFromAxis2d(a Axis2d, major_radius, minor_radius float64) Hyperbola2d {
	return Hyperbola2d{val: C.make_hyperbola2d_from_axis2d(a.val, C.double(major_radius), C.double(minor_radius))}
}

func NewHyperbola2dFromPoint(s1, s2, center Point2) Hyperbola2d {
	return Hyperbola2d{val: C.make_hyperbola2d_from_point(s1.val, s2.val, center.val)}
}

type Line struct {
	val C.struct__line_t
}

func NewLineFromAxis1(a Axis1) Line {
	return Line{val: C.make_line_from_axis1(a.val)}
}

func NewLineFromPointDir(l Point3, p Dir3) Line {
	return Line{val: C.make_line_from_point_dir(l.val, p.val)}
}

func NewLineFromLinePoint(l Line, p Point3) Line {
	return Line{val: C.make_line_from_line_point(l.val, p.val)}
}

func NewLineFromPoint(p1, p2 Point3) Line {
	return Line{val: C.make_line_from_point(p1.val, p2.val)}
}

type Line2d struct {
	val C.struct__line2d_t
}

func NewLine2dFromAxis2d(a Axis2d) Line2d {
	return Line2d{val: C.make_line2d_from_axis2d(a.val)}
}

func NewLine2dFromPointDir(l Point2, p Dir2) Line2d {
	return Line2d{val: C.make_line2d_point_dir(l.val, p.val)}
}

func NewLine2dFromLineDist(l Line2d, dist float64) Line2d {
	return Line2d{val: C.make_line2d_from_line_dist(l.val, C.double(dist))}
}

func NewLine2dFromLinePoint(l Line2d, p Point2) Line2d {
	return Line2d{val: C.make_line2d_line_point(l.val, p.val)}
}

func NewLine2dFromPoint(p1, p2 Point2) Line2d {
	return Line2d{val: C.make_line2d_from_point(p1.val, p2.val)}
}

type Parabola struct {
	val C.struct__parabola_t
}

func NewParabolaFromAxis2(a Axis2, focal float64) Parabola {
	return Parabola{val: C.make_parabola_from_axis2(a.val, C.double(focal))}
}

func NewParabolaFromAxis1(a Axis1, v Point3) Parabola {
	return Parabola{val: C.make_parabola_from_axis1(a.val, v.val)}
}

type Parabola2d struct {
	val C.struct__parabola2d_t
}

func NewParabola2dFromAxis2d(a Axis2d, focal float64) Parabola2d {
	return Parabola2d{val: C.make_parabola2d_from_axis2d(a.val, C.double(focal))}
}

func NewParabola2dFromAxis22d(a Axis22d, focal float64) Parabola2d {
	return Parabola2d{val: C.make_parabola2d_from_axis22d(a.val, C.double(focal))}
}

func NewParabola2dFromAxis2dPoint(a Axis2d, focal Point2) Parabola2d {
	return Parabola2d{val: C.make_parabola2d_from_axis2d_point(a.val, focal.val)}
}

func NewParabola2dFromPoint(s1, center Point2) Parabola2d {
	return Parabola2d{val: C.make_parabola2d_point(s1.val, center.val)}
}

type Plane struct {
	val C.struct__plane_t
}

func NewPlaneFromAxis2(a Axis2) Plane {
	return Plane{val: C.make_plane_from_axis2(a.val)}
}

func NewPlaneFromAxis1(a Axis1) Plane {
	return Plane{val: C.make_plane_from_axis1(a.val)}
}

func NewPlaneFromPointDir(a Point3, v Dir3) Plane {
	return Plane{val: C.make_plane_from_point_dir(a.val, v.val)}
}

func NewPlaneFromLRUD(a, b, c, d float64) Plane {
	return Plane{val: C.make_plane_from_lrud(C.double(a), C.double(b), C.double(c), C.double(d))}
}

func NewPlaneFromPlanePoint(p Plane, a Point3) Plane {
	return Plane{val: C.make_plane_from_plane_point(p.val, a.val)}
}

func NewPlaneFromPlaneDist(p Plane, dist float64) Plane {
	return Plane{val: C.make_plane_from_plane_dist(p.val, C.double(dist))}
}

func NewPlaneFromPoint(p1, p2, p3 Point3) Plane {
	return Plane{val: C.make_plane_from_point(p1.val, p2.val, p3.val)}
}

func NewPlaneFromTwoPoint(p1, p2 Point3) Plane {
	return Plane{val: C.make_plane_from_two_point(p1.val, p2.val)}
}

type Quaternion struct {
	val C.struct__quaternion_t
}

func NewQuaternion(q [4]float64) Quaternion {
	var m C.struct__quaternion_t
	m.q[0] = C.double(q[0])
	m.q[1] = C.double(q[1])
	m.q[2] = C.double(q[2])
	m.q[3] = C.double(q[3])
	return Quaternion{val: m}
}

type Sphere struct {
	val C.struct__sphere_t
}

func NewSphere(a Axis3, radius float64) Sphere {
	return Sphere{val: C.make_sphere_from_axis3(a.val, C.double(radius))}
}

type Torus struct {
	val C.struct__torus_t
}

func NewTorusFromAxis3(a Axis3, major_radius, minor_radius float64) Torus {
	return Torus{val: C.make_torus_from_axis3(a.val, C.double(major_radius), C.double(minor_radius))}
}

func NewTorusFromElips(a Elips) Torus {
	return Torus{val: C.make_torus_from_elips(a.val)}
}

type Trsf struct {
	val C.struct__trsf_t
}

func NewTrsfMirrorFromPoint(p Point3) Trsf {
	return Trsf{val: C.make_trsf_mirror_from_point(p.val)}
}

func NewTrsfMirrorFromAxis1(a Axis1) Trsf {
	return Trsf{val: C.make_trsf_mirror_from_axis1(a.val)}
}

func NewTrsfMirrorFromLine(l Line) Trsf {
	return Trsf{val: C.make_trsf_mirror_from_line(l.val)}
}

func NewTrsfMirrorFromPointDir(p Point3, d Dir3) Trsf {
	return Trsf{val: C.make_trsf_mirror_from_point_dir(p.val, d.val)}
}

func NewTrsfMirrorFromAxis2(a Axis2) Trsf {
	return Trsf{val: C.make_trsf_mirror_from_axis2(a.val)}
}

func NewTrsfMirrorFromPlane(p Plane) Trsf {
	return Trsf{val: C.make_trsf_mirror_from_plane(p.val)}
}

func NewTrsfRotationFromLine(l Line, ang float64) Trsf {
	return Trsf{val: C.make_trsf_rotation_from_line(l.val, C.double(ang))}
}

func NewTrsfRotationFromAxis1(a Axis1, ang float64) Trsf {
	return Trsf{val: C.make_trsf_rotation_from_axis1(a.val, C.double(ang))}
}

func NewTrsfRotationFromPointDir(p Point3, d Dir3, ang float64) Trsf {
	return Trsf{val: C.make_trsf_rotation_point_dir(p.val, d.val, C.double(ang))}
}

func NewTrsfScaleFromLine(p Point3, s float64) Trsf {
	return Trsf{val: C.make_trsf_scale_from_point(p.val, C.double(s))}
}

func NewTrsfTranslationFromVector(v Vector3) Trsf {
	return Trsf{val: C.make_trsf_translation_from_vector(v.val)}
}

func NewTrsfTranslationFromPoint(p1, p2 Point3) Trsf {
	return Trsf{val: C.make_trsf_translation_from_point(p1.val, p2.val)}
}

type Trsf2d struct {
	val C.struct__trsf2d_t
}

func NewTrsf2dMirrorFromPoint(p Point2) Trsf2d {
	return Trsf2d{val: C.make_trsf2d_mirror_from_point(p.val)}
}

func NewTrsf2dMirrorFromAxis2d(p Axis2d) Trsf2d {
	return Trsf2d{val: C.make_trsf2d_mirror_from_axis2d(p.val)}
}

func NewTrsf2dMirrorFromLine(p Line2d) Trsf2d {
	return Trsf2d{val: C.make_trsf2d_mirror_from_line(p.val)}
}

func NewTrsf2dMirrorFromPointDir(p Point2, d Dir2) Trsf2d {
	return Trsf2d{val: C.make_trsf2d_mirror_from_point_dir(p.val, d.val)}
}

func NewTrsf2dRotationFromPoint(p Point2, ang float64) Trsf2d {
	return Trsf2d{val: C.make_trsf2d_rotation_from_point(p.val, C.double(ang))}
}

func NewTrsf2dScaleFromPoint(p Point2, s float64) Trsf2d {
	return Trsf2d{val: C.make_trsf2d_scale_from_point(p.val, C.double(s))}
}

func NewTrsf2dTranslationFromVector(v Vector2) Trsf2d {
	return Trsf2d{val: C.make_trsf2d_translation_from_vector(v.val)}
}

func NewTrsf2dTranslationFromPoint(p1, p2 Point2) Trsf2d {
	return Trsf2d{val: C.make_trsf2d_translation_from_point(p1.val, p2.val)}
}

type Color struct {
	val C.struct__color_t
}

func NewColor(c [3]float64) Color {
	var m C.struct__color_t
	m.r = C.double(c[0])
	m.g = C.double(c[1])
	m.b = C.double(c[2])
	return Color{val: m}
}

func NewColorFromByte(c [3]byte) Color {
	var m C.struct__color_t
	m.r = C.double(c[0] / 255)
	m.g = C.double(c[1] / 255)
	m.b = C.double(c[2] / 255)
	return Color{val: m}
}
