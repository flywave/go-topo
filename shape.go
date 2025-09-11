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
	"strings"
	"unsafe"
)

func TxtureMapToString(tp int) string {
	switch tp {
	case TextureCube:
		return "cube"
	case TextureNormal:
		return "normal"
	case TextureNormalAutoScale:
		return "normal-auto-scale"
	default:
		return ""
	}
}

func StringToTxtureMap(tp string) int {
	if strings.EqualFold(tp, "cube") {
		return TextureCube
	} else if strings.EqualFold(tp, "normal") {
		return TextureNormal
	} else if strings.EqualFold(tp, "normal-auto-scale") {
		return TextureNormalAutoScale
	}
	return -1
}

type Shape struct {
	inner *innerShape
}

type innerShape struct {
	val *C.struct__topo_shape_t
}

func NewShape(v *C.struct__topo_shape_t) *Shape {
	s := &Shape{inner: &innerShape{val: v}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func (s *Shape) WriteToStl(ph string) {
	str := C.CString(ph)
	defer C.free(unsafe.Pointer(str))
	C.topo_shape_to_stl(s.inner.val, str)
}

func (s *Shape) IsNull() bool {
	return bool(C.topo_shape_is_null(s.inner.val))
}

func (s *Shape) IsValid() bool {
	return bool(C.topo_shape_is_valid(s.inner.val))
}

func (s *Shape) Equals(e *Shape) bool {
	return bool(C.topo_shape_equals(s.inner.val, e.inner.val))
}

func (s *Shape) Type() int {
	return int(C.topo_shape_type(s.inner.val))
}

func (s *Shape) BBox() BBox {
	return BBox{val: C.topo_shape_bounding_box(s.inner.val)}
}

func (s *Shape) Hash() int {
	return int(C.topo_shape_hash_code(s.inner.val))
}

func (s *Shape) Transform(t Trsf) int {
	return int(C.topo_shape_transform(s.inner.val, t.val))
}

func (s *Shape) Translate(v Vector3) int {
	return int(C.topo_shape_translate(s.inner.val, v.val))
}

func (s *Shape) RotateFromPoint(angle float64, p1, p2 Point3) int {
	return int(C.topo_shape_rotate_from_two_point(s.inner.val, C.double(angle), p1.val, p2.val))
}

func (s *Shape) RotateFromAxis1(angle float64, a Axis1) int {
	return int(C.topo_shape_rotate_from_axis1(s.inner.val, C.double(angle), a.val))
}

func (s *Shape) RotateFromQuaternion(q Quaternion) int {
	return int(C.topo_shape_rotate_from_quaternion(s.inner.val, q.val))
}

func (s *Shape) Scale(angle float64, a Point3) int {
	return int(C.topo_shape_scale(s.inner.val, C.double(angle), a.val))
}

func (s *Shape) MirrorFromPointNorm(pnt, ner Point3) int {
	return int(C.topo_shape_mirror_from_point_norm(s.inner.val, pnt.val, ner.val))
}

func (s *Shape) MirrorFromAxis1(a Axis1) int {
	return int(C.topo_shape_mirror_from_axis1(s.inner.val, a.val))
}

func (s *Shape) MirrorFromAxis2(a Axis2) int {
	return int(C.topo_shape_mirror_from_axis2(s.inner.val, a.val))
}

func (s *Shape) Transformed(t Trsf) *Shape {
	sp := &Shape{inner: &innerShape{val: C.topo_shape_transformed(s.inner.val, t.val)}}
	runtime.SetFinalizer(sp.inner, (*innerShape).free)
	return sp
}

func (s *Shape) CentreOfMass() Point3 {
	return Point3{val: C.topo_shape_centre_of_mass(s.inner.val)}
}

func (s *Shape) ComputeMass() float64 {
	return float64(C.topo_shape_compute_mass(s.inner.val))
}

func (s *Shape) ComputeArea() float64 {
	return float64(C.topo_shape_compute_area(s.inner.val))
}

func (s *Shape) Translated(v Vector3) *Shape {
	sp := &Shape{inner: &innerShape{val: C.topo_shape_translated(s.inner.val, v.val)}}
	runtime.SetFinalizer(sp.inner, (*innerShape).free)
	return sp
}

func (s *Shape) RotatedFromPoint(angle float64, p1, p2 Point3) *Shape {
	sp := &Shape{inner: &innerShape{val: C.topo_shape_rotated_from_two_point(s.inner.val, C.double(angle), p1.val, p2.val)}}
	runtime.SetFinalizer(sp.inner, (*innerShape).free)
	return sp
}

func (s *Shape) RotatedFromAxis1(angle float64, a Axis1) *Shape {
	sp := &Shape{inner: &innerShape{val: C.topo_shape_rotated_from_axis1(s.inner.val, C.double(angle), a.val)}}
	runtime.SetFinalizer(sp.inner, (*innerShape).free)
	return sp
}

func (s *Shape) RotatedFromQuaternion(q Quaternion) *Shape {
	sp := &Shape{inner: &innerShape{val: C.topo_shape_rotated_from_quaternion(s.inner.val, q.val)}}
	runtime.SetFinalizer(sp.inner, (*innerShape).free)
	return sp
}

func (s *Shape) Scaled(angle float64, a Point3) *Shape {
	sp := &Shape{inner: &innerShape{val: C.topo_shape_scaled(s.inner.val, C.double(angle), a.val)}}
	runtime.SetFinalizer(sp.inner, (*innerShape).free)
	return sp
}

func (s *Shape) MirroredFromPointNorm(pnt, ner Point3) *Shape {
	sp := &Shape{inner: &innerShape{val: C.topo_shape_mirrored_from_point_norm(s.inner.val, pnt.val, ner.val)}}
	runtime.SetFinalizer(sp.inner, (*innerShape).free)
	return sp
}

func (s *Shape) MirroredFromAxis1(a Axis1) *Shape {
	sp := &Shape{inner: &innerShape{val: C.topo_shape_mirrored_from_axis1(s.inner.val, a.val)}}
	runtime.SetFinalizer(sp.inner, (*innerShape).free)
	return sp
}

func (s *Shape) MirroredFromAxis2(a Axis2) *Shape {
	sp := &Shape{inner: &innerShape{val: C.topo_shape_mirrored_from_axis2(s.inner.val, a.val)}}
	runtime.SetFinalizer(sp.inner, (*innerShape).free)
	return sp
}

func (s *Shape) GetOrientation() int {
	return int(C.topo_shape_get_orientation(s.inner.val))
}

func (s *Shape) SetOrientation(t int) {
	C.topo_shape_set_orientation(s.inner.val, C.int(t))
}

func (s *Shape) GetLocation() *TopoLocation {
	p := &TopoLocation{inner: &innerTopoLocation{val: C.topo_shape_get_location(s.inner.val)}}
	runtime.SetFinalizer(p.inner, (*innerTopoLocation).free)
	return p
}

func (s *Shape) SetLocation(t *TopoLocation) {
	C.topo_shape_set_location(s.inner.val, t.inner.val)
}

func (s *Shape) FixShape() bool {
	return bool(C.topo_shape_fix_shape(s.inner.val))
}

func (s *Shape) Copy() *Shape {
	sp := &Shape{inner: &innerShape{val: C.topo_shape_copy(s.inner.val)}}
	runtime.SetFinalizer(sp.inner, (*innerShape).free)
	return sp
}

func (s *Shape) Share() *Shape {
	sp := &Shape{inner: &innerShape{val: C.topo_shape_share(s.inner.val)}}
	runtime.SetFinalizer(sp.inner, (*innerShape).free)
	return sp
}

func (s *Shape) Mesh(m *MeshReceiver, tolerance, deflection, angle float64) int8 {
	return int8(C.topo_shape_mesh(s.inner.val, m.inner.val, C.double(tolerance), C.double(deflection), C.double(angle), C.bool(false)))
}

func (s *Shape) MeshWithTexture(m *MeshReceiver, tolerance, deflection, angle float64) int8 {
	m.hasTexCoords = true
	return int8(C.topo_shape_mesh(s.inner.val, m.inner.val, C.double(tolerance), C.double(deflection), C.double(angle), C.bool(true)))
}

func (s *Shape) SetSurfaceColour(c Color) {
	C.topo_shape_set_surface_colour(s.inner.val, c.val)
}

func (s *Shape) SetCurveColour(c Color) {
	C.topo_shape_set_curve_colour(s.inner.val, c.val)
}

func (s *Shape) SetUVOrigin(u, v float64) {
	C.topo_shape_set_u_origin(s.inner.val, C.double(u))
	C.topo_shape_set_v_origin(s.inner.val, C.double(v))
}

func (s *Shape) SetUVRepeat(u, v float64) {
	C.topo_shape_set_u_repeat(s.inner.val, C.double(u))
	C.topo_shape_set_v_repeat(s.inner.val, C.double(v))
}

func (s *Shape) SetScaleU(u float64) {
	C.topo_shape_set_scale_u(s.inner.val, C.double(u))
}

func (s *Shape) SetScaleV(v float64) {
	C.topo_shape_set_scale_v(s.inner.val, C.double(v))
}

func (s *Shape) SetAutoScaleSizeOnU(u float64) {
	C.topo_shape_set_auto_scale_size_on_u(s.inner.val, C.double(u))
}

func (s *Shape) SetAutoScaleSizeOnV(v float64) {
	C.topo_shape_set_auto_scale_size_on_v(s.inner.val, C.double(v))
}

func (s *Shape) SetTextureMapType(t int) {
	C.topo_shape_set_txture_map_type(s.inner.val, C.int(t))
}

func (s *Shape) SetRotationAngle(a float64) {
	C.topo_shape_set_rotation_angle(s.inner.val, C.double(a))
}

func (s *Shape) SetLabel(l string) {
	str := C.CString(l)
	defer C.free(unsafe.Pointer(str))
	C.topo_shape_set_label(s.inner.val, str)
}

func (s *Shape) GetSurfaceColour() Color {
	return Color{val: C.topo_shape_get_surface_colour(s.inner.val)}
}

func (s *Shape) GetCurveColour() Color {
	return Color{val: C.topo_shape_get_surface_colour(s.inner.val)}
}

func (s *Shape) GetLabel() string {
	return C.GoString(C.topo_shape_get_label(s.inner.val))
}

func (s *Shape) GetUVOrigin() (u, v float64) {
	u = float64(C.topo_shape_get_u_origin(s.inner.val))
	v = float64(C.topo_shape_get_v_origin(s.inner.val))
	return
}

func (s *Shape) GetUVRepeat() (u, v float64) {
	u = float64(C.topo_shape_get_u_repeat(s.inner.val))
	v = float64(C.topo_shape_get_v_repeat(s.inner.val))
	return
}

func (s *Shape) GetUVScale() (u, v float64) {
	u = float64(C.topo_shape_get_scale_u(s.inner.val))
	v = float64(C.topo_shape_get_scale_v(s.inner.val))
	return
}

func (s *Shape) GetUVAutoScaleSize() (u, v float64) {
	u = float64(C.topo_shape_get_auto_scale_size_on_u(s.inner.val))
	v = float64(C.topo_shape_get_auto_scale_size_on_v(s.inner.val))
	return
}

func (s *Shape) GetTxtureMapType() int {
	return int(C.topo_shape_get_txture_map_type(s.inner.val))
}

func (s *Shape) GetRotationAngle() float64 {
	return float64(C.topo_shape_get_rotation_angle(s.inner.val))
}

func (t *innerShape) free() {
	C.topo_shape_free(t.val)
	t.val = nil
}

func (t *Shape) AutoCast() interface{} {
	switch t.Type() {
	case TopoSolid:
		var val C.struct__topo_solid_t
		val.shp = C.topo_shape_share(t.inner.val)
		sld := &Solid{inner: &innerSolid{val: val}}
		runtime.SetFinalizer(sld.inner, (*innerSolid).free)
		return sld
	case TopoShell:
		var val C.struct__topo_shell_t
		val.shp = C.topo_shape_share(t.inner.val)
		sh := &Shell{inner: &innerShell{val: val}}
		runtime.SetFinalizer(sh.inner, (*innerShell).free)
		return sh
	case TopoFace:
		var val C.struct__topo_face_t
		val.shp = C.topo_shape_share(t.inner.val)
		p := &Face{inner: &innerFace{val: val}}
		runtime.SetFinalizer(p.inner, (*innerFace).free)
		return p
	case TopoEdge:
		var val C.struct__topo_edge_t
		val.shp = C.topo_shape_share(t.inner.val)
		p := &Edge{inner: &innerEdge{val: val}}
		runtime.SetFinalizer(p.inner, (*innerEdge).free)
		return p
	case TopoVertex:
		var val C.struct__topo_vertex_t
		val.shp = C.topo_shape_share(t.inner.val)
		vx := &Vertex{inner: &innerVertex{val: val}}
		runtime.SetFinalizer(vx.inner, (*innerVertex).free)
		return vx
	case TopoWire:
		var val C.struct__topo_wire_t
		val.shp = C.topo_shape_share(t.inner.val)
		wr := &Wire{inner: &innerWire{val: val}}
		runtime.SetFinalizer(wr.inner, (*innerWire).free)
		return wr
	case TopoCompound:
		var val C.struct__topo_compound_t
		val.shp = C.topo_shape_share(t.inner.val)
		p := &Compound{inner: &innerCompound{val: val}}
		runtime.SetFinalizer(p.inner, (*innerCompound).free)
		return p
	case TopoCompSolid:
		var val C.struct__topo_comp_solid_t
		val.shp = C.topo_shape_share(t.inner.val)
		s := &CompSolid{inner: &innerCompSolid{val: val}}
		runtime.SetFinalizer(s.inner, (*innerCompSolid).free)
		return s
	case TopoShape:
		s := &Shape{inner: &innerShape{val: C.topo_shape_share(t.inner.val)}}
		runtime.SetFinalizer(s.inner, (*innerShape).free)
		return s
	}
	return nil
}
