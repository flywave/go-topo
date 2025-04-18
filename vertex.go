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

type Vertex struct {
	inner *innerVertex
}

type innerVertex struct {
	val C.struct__topo_vertex_t
}

func (s *Vertex) IsNull() bool {
	return bool(C.topo_shape_is_null(s.inner.val.shp))
}

func (s *Vertex) IsValid() bool {
	return bool(C.topo_shape_is_valid(s.inner.val.shp))
}

func (s *Vertex) Equals(e *Shape) bool {
	return bool(C.topo_shape_equals(s.inner.val.shp, e.inner.val))
}

func (s *Vertex) Type() int {
	return int(C.topo_shape_type(s.inner.val.shp))
}

func (s *Vertex) BBox() BBox {
	return BBox{val: C.topo_shape_bounding_box(s.inner.val.shp)}
}

func (s *Vertex) Hash() int {
	return int(C.topo_shape_hash_code(s.inner.val.shp))
}

func (s *Vertex) Transform(t Trsf) int {
	return int(C.topo_shape_transform(s.inner.val.shp, t.val))
}

func (s *Vertex) Translate(v Vector3) int {
	return int(C.topo_shape_translate(s.inner.val.shp, v.val))
}

func (s *Vertex) RotateFromPoint(angle float64, p1, p2 Point3) int {
	return int(C.topo_shape_rotate_from_two_point(s.inner.val.shp, C.double(angle), p1.val, p2.val))
}

func (s *Vertex) RotateFromAxis1(angle float64, a Axis1) int {
	return int(C.topo_shape_rotate_from_axis1(s.inner.val.shp, C.double(angle), a.val))
}

func (s *Vertex) RotateFromQuaternion(q Quaternion) int {
	return int(C.topo_shape_rotate_from_quaternion(s.inner.val.shp, q.val))
}

func (s *Vertex) Scale(angle float64, a Point3) int {
	return int(C.topo_shape_scale(s.inner.val.shp, C.double(angle), a.val))
}

func (s *Vertex) MirrorFromPointNorm(pnt, ner Point3) int {
	return int(C.topo_shape_mirror_from_point_norm(s.inner.val.shp, pnt.val, ner.val))
}

func (s *Vertex) MirrorFromAxis1(a Axis1) int {
	return int(C.topo_shape_mirror_from_axis1(s.inner.val.shp, a.val))
}

func (s *Vertex) MirrorFromAxis2(a Axis2) int {
	return int(C.topo_shape_mirror_from_axis2(s.inner.val.shp, a.val))
}

func (s *Vertex) Transformed(t Trsf) *Vertex {
	var val C.struct__topo_vertex_t
	val.shp = C.topo_shape_transformed(s.inner.val.shp, t.val)
	vx := &Vertex{inner: &innerVertex{val: val}}
	runtime.SetFinalizer(vx.inner, (*innerVertex).free)
	return vx
}

func (s *Vertex) Translated(v Vector3) *Vertex {
	var val C.struct__topo_vertex_t
	val.shp = C.topo_shape_translated(s.inner.val.shp, v.val)
	vx := &Vertex{inner: &innerVertex{val: val}}
	runtime.SetFinalizer(vx.inner, (*innerVertex).free)
	return vx
}

func (s *Vertex) RotatedFromPoint(angle float64, p1, p2 Point3) *Vertex {
	var val C.struct__topo_vertex_t
	val.shp = C.topo_shape_rotated_from_two_point(s.inner.val.shp, C.double(angle), p1.val, p2.val)
	vx := &Vertex{inner: &innerVertex{val: val}}
	runtime.SetFinalizer(vx.inner, (*innerVertex).free)
	return vx
}

func (s *Vertex) RotatedFromAxis1(angle float64, a Axis1) *Vertex {
	var val C.struct__topo_vertex_t
	val.shp = C.topo_shape_rotated_from_axis1(s.inner.val.shp, C.double(angle), a.val)
	vx := &Vertex{inner: &innerVertex{val: val}}
	runtime.SetFinalizer(vx.inner, (*innerVertex).free)
	return vx
}

func (s *Vertex) RotatedFromQuaternion(q Quaternion) *Vertex {
	var val C.struct__topo_vertex_t
	val.shp = C.topo_shape_rotated_from_quaternion(s.inner.val.shp, q.val)
	vx := &Vertex{inner: &innerVertex{val: val}}
	runtime.SetFinalizer(vx.inner, (*innerVertex).free)
	return vx
}

func (s *Vertex) Scaled(angle float64, a Point3) *Vertex {
	var val C.struct__topo_vertex_t
	val.shp = C.topo_shape_scaled(s.inner.val.shp, C.double(angle), a.val)
	vx := &Vertex{inner: &innerVertex{val: val}}
	runtime.SetFinalizer(vx.inner, (*innerVertex).free)
	return vx
}

func (s *Vertex) MirroredFromPointNorm(pnt, ner Point3) *Vertex {
	var val C.struct__topo_vertex_t
	val.shp = C.topo_shape_mirrored_from_point_norm(s.inner.val.shp, pnt.val, ner.val)
	vx := &Vertex{inner: &innerVertex{val: val}}
	runtime.SetFinalizer(vx.inner, (*innerVertex).free)
	return vx
}

func (s *Vertex) MirroredFromAxis1(a Axis1) *Vertex {
	var val C.struct__topo_vertex_t
	val.shp = C.topo_shape_mirrored_from_axis1(s.inner.val.shp, a.val)
	vx := &Vertex{inner: &innerVertex{val: val}}
	runtime.SetFinalizer(vx.inner, (*innerVertex).free)
	return vx
}

func (s *Vertex) MirroredFromAxis2(a Axis2) *Vertex {
	var val C.struct__topo_vertex_t
	val.shp = C.topo_shape_mirrored_from_axis2(s.inner.val.shp, a.val)
	vx := &Vertex{inner: &innerVertex{val: val}}
	runtime.SetFinalizer(vx.inner, (*innerVertex).free)
	return vx
}

func (s *Vertex) GetOrientation() int {
	return int(C.topo_shape_get_orientation(s.inner.val.shp))
}

func (s *Vertex) SetOrientation(t int) {
	C.topo_shape_set_orientation(s.inner.val.shp, C.int(t))
}

func (s *Vertex) GetLocation() *TopoLocation {
	p := &TopoLocation{inner: &innerTopoLocation{val: C.topo_shape_get_location(s.inner.val.shp)}}
	runtime.SetFinalizer(p.inner, (*innerTopoLocation).free)
	return p
}

func (s *Vertex) SetLocation(t *TopoLocation) {
	C.topo_shape_set_location(s.inner.val.shp, t.inner.val)
}

func (s *Vertex) FixShape() bool {
	return bool(C.topo_shape_fix_shape(s.inner.val.shp))
}

func (s *Vertex) Copy() *Vertex {
	var val C.struct__topo_vertex_t
	val.shp = C.topo_shape_copy(s.inner.val.shp)
	vx := &Vertex{inner: &innerVertex{val: val}}
	runtime.SetFinalizer(vx.inner, (*innerVertex).free)
	return vx
}

func (s *Vertex) Mesh(m *MeshReceiver, tolerance, deflection, angle float64) {
	C.topo_shape_mesh(s.inner.val.shp, m.inner.val, C.double(tolerance), C.double(deflection), C.double(angle), C.bool(false))
}

func (s *Vertex) MeshWithTexture(m *MeshReceiver, tolerance, deflection, angle float64) {
	m.hasTexCoords = true
	C.topo_shape_mesh(s.inner.val.shp, m.inner.val, C.double(tolerance), C.double(deflection), C.double(angle), C.bool(true))
}

func (s *Vertex) SetSurfaceColour(c Color) {
	C.topo_shape_set_surface_colour(s.inner.val.shp, c.val)
}

func (s *Vertex) SetCurveColour(c Color) {
	C.topo_shape_set_curve_colour(s.inner.val.shp, c.val)
}

func (s *Vertex) SetLabel(l string) {
	str := C.CString(l)
	defer C.free(unsafe.Pointer(str))
	C.topo_shape_set_label(s.inner.val.shp, str)
}

func (s *Vertex) SetUVOrigin(u, v float64) {
	C.topo_shape_set_u_origin(s.inner.val.shp, C.double(u))
	C.topo_shape_set_v_origin(s.inner.val.shp, C.double(v))
}

func (s *Vertex) SetUVRepeat(u, v float64) {
	C.topo_shape_set_u_repeat(s.inner.val.shp, C.double(u))
	C.topo_shape_set_v_repeat(s.inner.val.shp, C.double(v))
}

func (s *Vertex) SetScaleU(u float64) {
	C.topo_shape_set_scale_u(s.inner.val.shp, C.double(u))
}

func (s *Vertex) SetScaleV(v float64) {
	C.topo_shape_set_scale_v(s.inner.val.shp, C.double(v))
}

func (s *Vertex) SetAutoScaleSizeOnU(u float64) {
	C.topo_shape_set_auto_scale_size_on_u(s.inner.val.shp, C.double(u))
}

func (s *Vertex) SetAutoScaleSizeOnV(v float64) {
	C.topo_shape_set_auto_scale_size_on_v(s.inner.val.shp, C.double(v))
}

func (s *Vertex) SetTextureMapType(t int) {
	C.topo_shape_set_txture_map_type(s.inner.val.shp, C.int(t))
}

func (s *Vertex) SetRotationAngle(a float64) {
	C.topo_shape_set_rotation_angle(s.inner.val.shp, C.double(a))
}

func (s *Vertex) GetSurfaceColour() Color {
	return Color{val: C.topo_shape_get_surface_colour(s.inner.val.shp)}
}

func (s *Vertex) GetCurveColour() Color {
	return Color{val: C.topo_shape_get_surface_colour(s.inner.val.shp)}
}

func (s *Vertex) GetLabel() string {
	return C.GoString(C.topo_shape_get_label(s.inner.val.shp))
}

func (s *Vertex) GetUVOrigin() (u, v float64) {
	u = float64(C.topo_shape_get_u_origin(s.inner.val.shp))
	v = float64(C.topo_shape_get_v_origin(s.inner.val.shp))
	return
}

func (s *Vertex) GetUVRepeat() (u, v float64) {
	u = float64(C.topo_shape_get_u_repeat(s.inner.val.shp))
	v = float64(C.topo_shape_get_v_repeat(s.inner.val.shp))
	return
}

func (s *Vertex) GetUVScale() (u, v float64) {
	u = float64(C.topo_shape_get_scale_u(s.inner.val.shp))
	v = float64(C.topo_shape_get_scale_v(s.inner.val.shp))
	return
}

func (s *Vertex) GetUVAutoScaleSize() (u, v float64) {
	u = float64(C.topo_shape_get_auto_scale_size_on_u(s.inner.val.shp))
	v = float64(C.topo_shape_get_auto_scale_size_on_v(s.inner.val.shp))
	return
}

func (s *Vertex) GetTxtureMapType() int {
	return int(C.topo_shape_get_txture_map_type(s.inner.val.shp))
}

func (s *Vertex) GetRotationAngle() float64 {
	return float64(C.topo_shape_get_rotation_angle(s.inner.val.shp))
}

func (t *Vertex) GetPoint() Point3 {
	return Point3{val: C.topo_vertex_get_point(t.inner.val)}
}

func (t *Vertex) ToShape() *Shape {
	sp := &Shape{inner: &innerShape{val: C.topo_shape_share(t.inner.val.shp)}}
	runtime.SetFinalizer(sp.inner, (*innerShape).free)
	return sp
}

func (t *innerVertex) free() {
	C.topo_vertex_free(t.val)
}

func NewVertex(x, y, z float64) *Vertex {
	p := &Vertex{inner: &innerVertex{val: C.topo_vertex_new(C.double(x), C.double(y), C.double(z))}}
	runtime.SetFinalizer(p.inner, (*innerVertex).free)
	return p
}

type VertexIterator struct {
	inner *innerVertexIterator
}
type innerVertexIterator struct {
	val *C.struct__topo_vertex_iterator_t
}

func TopoMakeVertexIterator(p Shape) *VertexIterator {
	wr := &VertexIterator{inner: &innerVertexIterator{val: C.topo_vertex_iterator_make(p.inner.val)}}
	runtime.SetFinalizer(wr.inner, (*innerVertexIterator).free)
	return wr
}

func (t *innerVertexIterator) free() {
	C.topo_vertex_iterator_free(t.val)
}

func (t *VertexIterator) Next() *Vertex {
	v := C.topo_vertex_iterator_next(t.inner.val)
	if v != nil {
		var val C.struct__topo_vertex_t
		val.shp = v
		p := &Vertex{inner: &innerVertex{val: val}}
		runtime.SetFinalizer(p.inner, (*innerVertex).free)
		return p
	}
	return nil
}
