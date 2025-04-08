package topo

/*
#include <stdlib.h>
#include "topo_c_api.h"
#cgo CFLAGS: -I  ./libs
#cgo linux CXXFLAGS: -I ./libs  -std=gnu++14
#cgo darwin,amd64 CXXFLAGS: -I ./libs  -std=gnu++14
#cgo darwin,arm64 CXXFLAGS: -I ./libs  -std=gnu++14
#cgo windows CXXFLAGS: -I ./libs  -std=gnu++14
*/
import "C"
import (
	"runtime"
	"unsafe"
)

type Face struct {
	inner *innerFace
}

type innerFace struct {
	val C.struct__topo_face_t
}

func TopoMakeFace() *Face {
	p := &Face{inner: &innerFace{val: C.topo_make_face()}}
	runtime.SetFinalizer(p.inner, (*innerFace).free)
	return p
}

func (s *Face) IsNull() bool {
	return bool(C.topo_shape_is_null(s.inner.val.shp))
}

func (s *Face) IsValid() bool {
	return bool(C.topo_shape_is_valid(s.inner.val.shp))
}

func (s *Face) Equals(e *Shape) bool {
	return bool(C.topo_shape_equals(s.inner.val.shp, e.inner.val))
}

func (s *Face) Type() int {
	return int(C.topo_shape_type(s.inner.val.shp))
}

func (s *Face) BBox() BBox {
	return BBox{val: C.topo_shape_bounding_box(s.inner.val.shp)}
}

func (s *Face) Hash() int {
	return int(C.topo_shape_hash_code(s.inner.val.shp))
}

func (s *Face) Transform(t Trsf) int {
	return int(C.topo_shape_transform(s.inner.val.shp, t.val))
}

func (s *Face) Translate(v Vector3) int {
	return int(C.topo_shape_translate(s.inner.val.shp, v.val))
}

func (s *Face) RotateFromPoint(angle float64, p1, p2 Point3) int {
	return int(C.topo_shape_rotate_from_two_point(s.inner.val.shp, C.double(angle), p1.val, p2.val))
}

func (s *Face) RotateFromAxis1(angle float64, a Axis1) int {
	return int(C.topo_shape_rotate_from_axis1(s.inner.val.shp, C.double(angle), a.val))
}

func (s *Face) RotateFromQuaternion(q Quaternion) int {
	return int(C.topo_shape_rotate_from_quaternion(s.inner.val.shp, q.val))
}

func (s *Face) Scale(angle float64, a Point3) int {
	return int(C.topo_shape_scale(s.inner.val.shp, C.double(angle), a.val))
}

func (s *Face) MirrorFromPointNorm(pnt, ner Point3) int {
	return int(C.topo_shape_mirror_from_point_norm(s.inner.val.shp, pnt.val, ner.val))
}

func (s *Face) MirrorFromAxis1(a Axis1) int {
	return int(C.topo_shape_mirror_from_axis1(s.inner.val.shp, a.val))
}

func (s *Face) MirrorFromAxis2(a Axis2) int {
	return int(C.topo_shape_mirror_from_axis2(s.inner.val.shp, a.val))
}

func (s *Face) Transformed(t Trsf) *Face {
	var val C.struct__topo_face_t
	val.shp = C.topo_shape_transformed(s.inner.val.shp, t.val)
	p := &Face{inner: &innerFace{val: val}}
	runtime.SetFinalizer(p.inner, (*innerFace).free)
	return p
}

func (s *Face) Translated(v Vector3) *Face {
	var val C.struct__topo_face_t
	val.shp = C.topo_shape_translated(s.inner.val.shp, v.val)
	p := &Face{inner: &innerFace{val: val}}
	runtime.SetFinalizer(p.inner, (*innerFace).free)
	return p
}

func (s *Face) RotatedFromPoint(angle float64, p1, p2 Point3) *Face {
	var val C.struct__topo_face_t
	val.shp = C.topo_shape_rotated_from_two_point(s.inner.val.shp, C.double(angle), p1.val, p2.val)
	p := &Face{inner: &innerFace{val: val}}
	runtime.SetFinalizer(p.inner, (*innerFace).free)
	return p
}

func (s *Face) RotatedFromAxis1(angle float64, a Axis1) *Face {
	var val C.struct__topo_face_t
	val.shp = C.topo_shape_rotated_from_axis1(s.inner.val.shp, C.double(angle), a.val)
	p := &Face{inner: &innerFace{val: val}}
	runtime.SetFinalizer(p.inner, (*innerFace).free)
	return p
}

func (s *Face) RotatedFromQuaternion(q Quaternion) *Face {
	var val C.struct__topo_face_t
	val.shp = C.topo_shape_rotated_from_quaternion(s.inner.val.shp, q.val)
	p := &Face{inner: &innerFace{val: val}}
	runtime.SetFinalizer(p.inner, (*innerFace).free)
	return p
}

func (s *Face) Scaled(angle float64, a Point3) *Face {
	var val C.struct__topo_face_t
	val.shp = C.topo_shape_scaled(s.inner.val.shp, C.double(angle), a.val)
	p := &Face{inner: &innerFace{val: val}}
	runtime.SetFinalizer(p.inner, (*innerFace).free)
	return p
}

func (s *Face) MirroredFromPointNorm(pnt, ner Point3) *Face {
	var val C.struct__topo_face_t
	val.shp = C.topo_shape_mirrored_from_point_norm(s.inner.val.shp, pnt.val, ner.val)
	p := &Face{inner: &innerFace{val: val}}
	runtime.SetFinalizer(p.inner, (*innerFace).free)
	return p
}

func (s *Face) MirroredFromAxis1(a Axis1) *Face {
	var val C.struct__topo_face_t
	val.shp = C.topo_shape_mirrored_from_axis1(s.inner.val.shp, a.val)
	p := &Face{inner: &innerFace{val: val}}
	runtime.SetFinalizer(p.inner, (*innerFace).free)
	return p
}

func (s *Face) MirroredFromAxis2(a Axis2) *Face {
	var val C.struct__topo_face_t
	val.shp = C.topo_shape_mirrored_from_axis2(s.inner.val.shp, a.val)
	p := &Face{inner: &innerFace{val: val}}
	runtime.SetFinalizer(p.inner, (*innerFace).free)
	return p
}

func (s *Face) GetOrientation() int {
	return int(C.topo_shape_get_orientation(s.inner.val.shp))
}

func (s *Face) SetOrientation(t int) {
	C.topo_shape_set_orientation(s.inner.val.shp, C.int(t))
}

func (s *Face) GetLocation() *TopoLocation {
	p := &TopoLocation{inner: &innerTopoLocation{val: C.topo_shape_get_location(s.inner.val.shp)}}
	runtime.SetFinalizer(p.inner, (*innerTopoLocation).free)
	return p
}

func (s *Face) SetLocation(t *TopoLocation) {
	C.topo_shape_set_location(s.inner.val.shp, t.inner.val)
}

func (s *Face) FixShape() bool {
	return bool(C.topo_shape_fix_shape(s.inner.val.shp))
}

func (s *Face) Copy() *Face {
	var val C.struct__topo_face_t
	val.shp = C.topo_shape_copy(s.inner.val.shp)
	p := &Face{inner: &innerFace{val: val}}
	runtime.SetFinalizer(p.inner, (*innerFace).free)
	return p
}

func (s *Face) Mesh(m *MeshReceiver, tolerance, deflection, angle float64) {
	C.topo_shape_mesh(s.inner.val.shp, m.inner.val, C.double(tolerance), C.double(deflection), C.double(angle), C.bool(false))
}

func (s *Face) MeshWithTexture(m *MeshReceiver, tolerance, deflection, angle float64) {
	m.hasTexCoords = true
	C.topo_shape_mesh(s.inner.val.shp, m.inner.val, C.double(tolerance), C.double(deflection), C.double(angle), C.bool(true))
}

func (s *Face) SetSurfaceColour(c Color) {
	C.topo_shape_set_surface_colour(s.inner.val.shp, c.val)
}

func (s *Face) SetCurveColour(c Color) {
	C.topo_shape_set_curve_colour(s.inner.val.shp, c.val)
}

func (s *Face) SetLabel(l string) {
	str := C.CString(l)
	defer C.free(unsafe.Pointer(str))
	C.topo_shape_set_label(s.inner.val.shp, str)
}

func (s *Face) SetUVOrigin(u, v float64) {
	C.topo_shape_set_u_origin(s.inner.val.shp, C.double(u))
	C.topo_shape_set_v_origin(s.inner.val.shp, C.double(v))
}

func (s *Face) SetUVRepeat(u, v float64) {
	C.topo_shape_set_u_repeat(s.inner.val.shp, C.double(u))
	C.topo_shape_set_v_repeat(s.inner.val.shp, C.double(v))
}

func (s *Face) SetScaleU(u float64) {
	C.topo_shape_set_scale_u(s.inner.val.shp, C.double(u))
}

func (s *Face) SetScaleV(v float64) {
	C.topo_shape_set_scale_v(s.inner.val.shp, C.double(v))
}

func (s *Face) SetAutoScaleSizeOnU(u float64) {
	C.topo_shape_set_auto_scale_size_on_u(s.inner.val.shp, C.double(u))
}

func (s *Face) SetAutoScaleSizeOnV(v float64) {
	C.topo_shape_set_auto_scale_size_on_v(s.inner.val.shp, C.double(v))
}

func (s *Face) SetTextureMapType(t int) {
	C.topo_shape_set_txture_map_type(s.inner.val.shp, C.int(t))
}

func (s *Face) SetRotationAngle(a float64) {
	C.topo_shape_set_rotation_angle(s.inner.val.shp, C.double(a))
}

func (s *Face) GetSurfaceColour() Color {
	return Color{val: C.topo_shape_get_surface_colour(s.inner.val.shp)}
}

func (s *Face) GetCurveColour() Color {
	return Color{val: C.topo_shape_get_surface_colour(s.inner.val.shp)}
}

func (s *Face) GetLabel() string {
	return C.GoString(C.topo_shape_get_label(s.inner.val.shp))
}

func (s *Face) GetUVOrigin() (u, v float64) {
	u = float64(C.topo_shape_get_u_origin(s.inner.val.shp))
	v = float64(C.topo_shape_get_v_origin(s.inner.val.shp))
	return
}

func (s *Face) GetUVRepeat() (u, v float64) {
	u = float64(C.topo_shape_get_u_repeat(s.inner.val.shp))
	v = float64(C.topo_shape_get_v_repeat(s.inner.val.shp))
	return
}

func (s *Face) GetUVScale() (u, v float64) {
	u = float64(C.topo_shape_get_scale_u(s.inner.val.shp))
	v = float64(C.topo_shape_get_scale_v(s.inner.val.shp))
	return
}

func (s *Face) GetUVAutoScaleSize() (u, v float64) {
	u = float64(C.topo_shape_get_auto_scale_size_on_u(s.inner.val.shp))
	v = float64(C.topo_shape_get_auto_scale_size_on_v(s.inner.val.shp))
	return
}

func (s *Face) GetTxtureMapType() int {
	return int(C.topo_shape_get_txture_map_type(s.inner.val.shp))
}

func (s *Face) GetRotationAngle() float64 {
	return float64(C.topo_shape_get_rotation_angle(s.inner.val.shp))
}

func (t *Face) NumWires() int {
	return int(C.topo_face_num_wires(t.inner.val))
}

func (t *Face) NumFaces() int {
	return int(C.topo_face_num_faces(t.inner.val))
}

func (t *Face) Area() float64 {
	return float64(C.topo_face_area(t.inner.val))
}

func (t *Face) Tolerance() float32 {
	return float32(C.topo_face_tolerance(t.inner.val))
}

func (t *Face) Inertia() BBox {
	return BBox{val: C.topo_face_inertia(t.inner.val)}
}

func (t *Face) CentreOfMass() Point3 {
	return Point3{val: C.topo_face_centre_of_mass(t.inner.val)}
}

func (t *Face) Offset(offset, tolerance float64) int {
	return int(C.topo_face_offset(t.inner.val, C.double(offset), C.double(tolerance)))
}

func (t *Face) Extrude(shp *Shape, p1, p2 Point3) int {
	return int(C.topo_face_extrude(t.inner.val, shp.inner.val, p1.val, p2.val))
}

func (t *Face) Revolve(shp *Shape, p1, p2 Point3, angle float64) int {
	return int(C.topo_face_revolve(t.inner.val, shp.inner.val, p1.val, p2.val, C.double(angle)))
}

func (s *Face) Sweep(spine *Wire, profiles []Shape, cornerMode int) int {
	cshp := make([]*C.struct__topo_shape_t, len(profiles))
	for i := range profiles {
		cshp[i] = profiles[i].inner.val
	}
	return int(C.topo_face_sweep(s.inner.val, spine.inner.val, &cshp[0], C.int(len(profiles)), C.int(cornerMode)))
}

func (t *Face) Loft(profiles []Shape, ruled bool, tolerance float64) int {
	prs := make([]*C.struct__topo_shape_t, len(profiles))
	for i := range profiles {
		prs[i] = profiles[i].inner.val
	}
	return int(C.topo_face_loft(t.inner.val, &prs[0], C.int(len(profiles)), C.bool(ruled), C.double(tolerance)))
}

func (t *Face) Boolean(tool *Face, op int) int {
	return int(C.topo_face_boolean(t.inner.val, tool.inner.val, C.int(op)))
}

func (t *Face) ToShape() *Shape {
	sp := &Shape{inner: &innerShape{val: C.topo_shape_share(t.inner.val.shp)}}
	runtime.SetFinalizer(sp.inner, (*innerShape).free)
	return sp
}

func (t *innerFace) free() {
	C.topo_face_free(t.val)
}

func TopoMakeFaceFromPlane(f Plane) *Face {
	p := &Face{inner: &innerFace{val: C.topo_face_make_face_from_plane(f.val)}}
	runtime.SetFinalizer(p.inner, (*innerFace).free)
	return p
}

func TopoMakeFaceFromCylinder(f Cylinder) *Face {
	p := &Face{inner: &innerFace{val: C.topo_face_make_face_from_cylinder(f.val)}}
	runtime.SetFinalizer(p.inner, (*innerFace).free)
	return p
}

func TopoMakeFaceFromCone(f Cone) *Face {
	p := &Face{inner: &innerFace{val: C.topo_face_make_face_from_cone(f.val)}}
	runtime.SetFinalizer(p.inner, (*innerFace).free)
	return p
}

func TopoMakeFaceFromSphere(f Sphere) *Face {
	p := &Face{inner: &innerFace{val: C.topo_face_make_face_from_sphere(f.val)}}
	runtime.SetFinalizer(p.inner, (*innerFace).free)
	return p
}

func TopoMakeFaceFromTorus(f Torus) *Face {
	p := &Face{inner: &innerFace{val: C.topo_face_make_face_from_torus(f.val)}}
	runtime.SetFinalizer(p.inner, (*innerFace).free)
	return p
}

func TopoMakeFaceFromSurface(S *GeomSurface, TolDegen float64) *Face {
	p := &Face{inner: &innerFace{val: C.topo_face_make_face_from_surface(S.inner.geom, C.double(TolDegen))}}
	runtime.SetFinalizer(p.inner, (*innerFace).free)
	return p
}

func TopoMakeFaceFromPlaneParm(f Plane, UMin, UMax, VMin, VMax float64) *Face {
	p := &Face{inner: &innerFace{val: C.topo_face_make_face_from_plane_p(f.val, C.double(UMin), C.double(UMax), C.double(VMin), C.double(VMax))}}
	runtime.SetFinalizer(p.inner, (*innerFace).free)
	return p
}

func TopoMakeFaceFromCylinderParm(f Cylinder, UMin, UMax, VMin, VMax float64) *Face {
	p := &Face{inner: &innerFace{val: C.topo_face_make_face_from_cylinder_p(f.val, C.double(UMin), C.double(UMax), C.double(VMin), C.double(VMax))}}
	runtime.SetFinalizer(p.inner, (*innerFace).free)
	return p
}
func TopoMakeFaceFromConeParm(f Cone, UMin, UMax, VMin, VMax float64) *Face {
	p := &Face{inner: &innerFace{val: C.topo_face_make_face_from_cone_p(f.val, C.double(UMin), C.double(UMax), C.double(VMin), C.double(VMax))}}
	runtime.SetFinalizer(p.inner, (*innerFace).free)
	return p
}

func TopoMakeFaceFromSphereParm(f Sphere, UMin, UMax, VMin, VMax float64) *Face {
	p := &Face{inner: &innerFace{val: C.topo_face_make_face_from_sphere_p(f.val, C.double(UMin), C.double(UMax), C.double(VMin), C.double(VMax))}}
	runtime.SetFinalizer(p.inner, (*innerFace).free)
	return p
}

func TopoMakeFaceFromTorusParm(f Torus, UMin, UMax, VMin, VMax float64) *Face {
	p := &Face{inner: &innerFace{val: C.topo_face_make_face_from_torus_p(f.val, C.double(UMin), C.double(UMax), C.double(VMin), C.double(VMax))}}
	runtime.SetFinalizer(p.inner, (*innerFace).free)
	return p
}

func TopoMakeFaceFromSurfaceParm(S *GeomSurface, UMin, UMax, VMin, VMax, TolDegen float64) *Face {
	p := &Face{inner: &innerFace{val: C.topo_face_make_face_from_surface_p(S.inner.geom, C.double(UMin), C.double(UMax), C.double(VMin), C.double(VMax), C.double(TolDegen))}}
	runtime.SetFinalizer(p.inner, (*innerFace).free)
	return p
}

func TopoMakeFaceFromWire(w Wire, OnlyPlane bool) *Face {
	p := &Face{inner: &innerFace{val: C.topo_face_make_face_from_wire_onlyplane(w.inner.val, C.bool(OnlyPlane))}}
	runtime.SetFinalizer(p.inner, (*innerFace).free)
	return p
}

func TopoMakeFaceFromPlaneWire(p Plane, w Wire, Inside bool) *Face {
	f := &Face{inner: &innerFace{val: C.topo_face_make_face_from_plane_wire(p.val, w.inner.val, C.bool(Inside))}}
	runtime.SetFinalizer(f.inner, (*innerFace).free)
	return f
}

func TopoMakeFaceFromCylinderWire(p Cylinder, w Wire, Inside bool) *Face {
	f := &Face{inner: &innerFace{val: C.topo_face_make_face_from_cylinder_wire(p.val, w.inner.val, C.bool(Inside))}}
	runtime.SetFinalizer(f.inner, (*innerFace).free)
	return f
}

func TopoMakeFaceFromConeWire(p Cone, w Wire, Inside bool) *Face {
	f := &Face{inner: &innerFace{val: C.topo_face_make_face_from_cone_wire(p.val, w.inner.val, C.bool(Inside))}}
	runtime.SetFinalizer(f.inner, (*innerFace).free)
	return f
}

func TopoMakeFaceFromSphereWire(p Sphere, w Wire, Inside bool) *Face {
	f := &Face{inner: &innerFace{val: C.topo_face_make_face_from_sphere_wire(p.val, w.inner.val, C.bool(Inside))}}
	runtime.SetFinalizer(f.inner, (*innerFace).free)
	return f
}

func TopoMakeFaceFromTorusWire(p Torus, w Wire, Inside bool) *Face {
	f := &Face{inner: &innerFace{val: C.topo_face_make_face_from_torus_wire(p.val, w.inner.val, C.bool(Inside))}}
	runtime.SetFinalizer(f.inner, (*innerFace).free)
	return f
}

func TopoMakeFaceFromSurfaceWire(S *GeomSurface, w Wire, Inside bool) *Face {
	p := &Face{inner: &innerFace{val: C.topo_face_make_face_from_surface_wire(S.inner.geom, w.inner.val, C.bool(Inside))}}
	runtime.SetFinalizer(p.inner, (*innerFace).free)
	return p
}

func TopoMakeFaceFromFaceWire(f *Face, w Wire) *Face {
	p := &Face{inner: &innerFace{val: C.topo_face_make_face_from_face_wire(f.inner.val, w.inner.val)}}
	runtime.SetFinalizer(p.inner, (*innerFace).free)
	return p
}

func TopoMakeFaceFromWires(ws []Wire) *Face {
	cws := make([]C.struct__topo_wire_t, len(ws))
	for i := range ws {
		cws[i] = ws[i].inner.val
	}
	p := &Face{inner: &innerFace{val: C.topo_face_make_face_from_wire(&cws[0], C.int(len(ws)))}}
	runtime.SetFinalizer(p.inner, (*innerFace).free)
	return p
}

func TopoMakeFaceFromEdges(ws []Edge, pts []Point3) *Face {
	cws := make([]C.struct__topo_edge_t, len(ws))
	for i := range ws {
		cws[i] = ws[i].inner.val
	}
	cpts := make([]C.struct__pnt3d_t, len(pts))
	for i := range pts {
		cpts[i] = pts[i].val
	}
	p := &Face{inner: &innerFace{val: C.topo_face_make_face_from_egdes(&cws[0], C.int(len(ws)), &cpts[0], C.int(len(pts)))}}
	runtime.SetFinalizer(p.inner, (*innerFace).free)
	return p
}

func TopoMakeFaceFromPoints(pts []Point3) *Face {
	cpts := make([]C.struct__pnt3d_t, len(pts))
	for i := range pts {
		cpts[i] = pts[i].val
	}
	p := &Face{inner: &innerFace{val: C.topo_face_make_face_from_points(&cpts[0], C.int(len(pts)))}}
	runtime.SetFinalizer(p.inner, (*innerFace).free)
	return p
}

type FaceIterator struct {
	inner *innerFaceIterator
}
type innerFaceIterator struct {
	val *C.struct__topo_face_iterator_t
}

func TopoMakeFaceIterator(p Shape) *FaceIterator {
	wr := &FaceIterator{inner: &innerFaceIterator{val: C.topo_face_iterator_make(p.inner.val)}}
	runtime.SetFinalizer(wr.inner, (*innerFaceIterator).free)
	return wr
}

func (t *innerFaceIterator) free() {
	C.topo_face_iterator_free(t.val)
}

func (t *FaceIterator) Next() *Face {
	v := C.topo_face_iterator_next(t.inner.val)
	if v != nil {
		var val C.struct__topo_face_t
		val.shp = v
		p := &Face{inner: &innerFace{val: val}}
		runtime.SetFinalizer(p.inner, (*innerFace).free)
		return p
	}
	return nil
}
