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

type Wire struct {
	inner *innerWire
}

type innerWire struct {
	val C.struct__topo_wire_t
}

func TopoMakeWire() *Wire {
	p := &Wire{inner: &innerWire{val: C.topo_make_wire()}}
	runtime.SetFinalizer(p.inner, (*innerWire).free)
	return p
}

func (s *Wire) IsNull() bool {
	return bool(C.topo_shape_is_null(s.inner.val.shp))
}

func (s *Wire) IsValid() bool {
	return bool(C.topo_shape_is_valid(s.inner.val.shp))
}

func (s *Wire) Equals(e *Shape) bool {
	return bool(C.topo_shape_equals(s.inner.val.shp, e.inner.val))
}

func (s *Wire) Type() int {
	return int(C.topo_shape_type(s.inner.val.shp))
}

func (s *Wire) BBox() BBox {
	return BBox{val: C.topo_shape_bounding_box(s.inner.val.shp)}
}

func (s *Wire) Hash() int {
	return int(C.topo_shape_hash_code(s.inner.val.shp))
}

func (s *Wire) Transform(t Trsf) int {
	return int(C.topo_shape_transform(s.inner.val.shp, t.val))
}

func (s *Wire) Translate(v Vector3) int {
	return int(C.topo_shape_translate(s.inner.val.shp, v.val))
}

func (s *Wire) RotateFromPoint(angle float64, p1, p2 Point3) int {
	return int(C.topo_shape_rotate_from_two_point(s.inner.val.shp, C.double(angle), p1.val, p2.val))
}

func (s *Wire) RotateFromAxis1(angle float64, a Axis1) int {
	return int(C.topo_shape_rotate_from_axis1(s.inner.val.shp, C.double(angle), a.val))
}

func (s *Wire) RotateFromQuaternion(q Quaternion) int {
	return int(C.topo_shape_rotate_from_quaternion(s.inner.val.shp, q.val))
}

func (s *Wire) Scale(angle float64, a Point3) int {
	return int(C.topo_shape_scale(s.inner.val.shp, C.double(angle), a.val))
}

func (s *Wire) MirrorFromPointNorm(pnt, ner Point3) int {
	return int(C.topo_shape_mirror_from_point_norm(s.inner.val.shp, pnt.val, ner.val))
}

func (s *Wire) MirrorFromAxis1(a Axis1) int {
	return int(C.topo_shape_mirror_from_axis1(s.inner.val.shp, a.val))
}

func (s *Wire) MirrorFromAxis2(a Axis2) int {
	return int(C.topo_shape_mirror_from_axis2(s.inner.val.shp, a.val))
}

func (s *Wire) Transformed(t Trsf) *Wire {
	var val C.struct__topo_wire_t
	val.shp = C.topo_shape_transformed(s.inner.val.shp, t.val)
	wr := &Wire{inner: &innerWire{val: val}}
	runtime.SetFinalizer(wr.inner, (*innerWire).free)
	return wr
}

func (s *Wire) Translated(v Vector3) *Wire {
	var val C.struct__topo_wire_t
	val.shp = C.topo_shape_translated(s.inner.val.shp, v.val)
	wr := &Wire{inner: &innerWire{val: val}}
	runtime.SetFinalizer(wr.inner, (*innerWire).free)
	return wr
}

func (s *Wire) RotatedFromPoint(angle float64, p1, p2 Point3) *Wire {
	var val C.struct__topo_wire_t
	val.shp = C.topo_shape_rotated_from_two_point(s.inner.val.shp, C.double(angle), p1.val, p2.val)
	wr := &Wire{inner: &innerWire{val: val}}
	runtime.SetFinalizer(wr.inner, (*innerWire).free)
	return wr
}

func (s *Wire) RotatedFromAxis1(angle float64, a Axis1) *Wire {
	var val C.struct__topo_wire_t
	val.shp = C.topo_shape_rotated_from_axis1(s.inner.val.shp, C.double(angle), a.val)
	wr := &Wire{inner: &innerWire{val: val}}
	runtime.SetFinalizer(wr.inner, (*innerWire).free)
	return wr
}

func (s *Wire) RotatedFromQuaternion(q Quaternion) *Wire {
	var val C.struct__topo_wire_t
	val.shp = C.topo_shape_rotated_from_quaternion(s.inner.val.shp, q.val)
	wr := &Wire{inner: &innerWire{val: val}}
	runtime.SetFinalizer(wr.inner, (*innerWire).free)
	return wr
}

func (s *Wire) Scaled(angle float64, a Point3) *Wire {
	var val C.struct__topo_wire_t
	val.shp = C.topo_shape_scaled(s.inner.val.shp, C.double(angle), a.val)
	wr := &Wire{inner: &innerWire{val: val}}
	runtime.SetFinalizer(wr.inner, (*innerWire).free)
	return wr
}

func (s *Wire) MirroredFromPointNorm(pnt, ner Point3) *Wire {
	var val C.struct__topo_wire_t
	val.shp = C.topo_shape_mirrored_from_point_norm(s.inner.val.shp, pnt.val, ner.val)
	wr := &Wire{inner: &innerWire{val: val}}
	runtime.SetFinalizer(wr.inner, (*innerWire).free)
	return wr
}

func (s *Wire) MirroredFromAxis1(a Axis1) *Wire {
	var val C.struct__topo_wire_t
	val.shp = C.topo_shape_mirrored_from_axis1(s.inner.val.shp, a.val)
	wr := &Wire{inner: &innerWire{val: val}}
	runtime.SetFinalizer(wr.inner, (*innerWire).free)
	return wr
}

func (s *Wire) MirroredFromAxis2(a Axis2) *Wire {
	var val C.struct__topo_wire_t
	val.shp = C.topo_shape_mirrored_from_axis2(s.inner.val.shp, a.val)
	wr := &Wire{inner: &innerWire{val: val}}
	runtime.SetFinalizer(wr.inner, (*innerWire).free)
	return wr
}

func (s *Wire) GetOrientation() int {
	return int(C.topo_shape_get_orientation(s.inner.val.shp))
}

func (s *Wire) SetOrientation(t int) {
	C.topo_shape_set_orientation(s.inner.val.shp, C.int(t))
}

func (s *Wire) GetLocation() *TopoLocation {
	sp := &TopoLocation{inner: &innerTopoLocation{val: C.topo_shape_get_location(s.inner.val.shp)}}
	runtime.SetFinalizer(sp.inner, (*innerShape).free)
	return sp
}

func (s *Wire) SetLocation(t *TopoLocation) {
	C.topo_shape_set_location(s.inner.val.shp, t.inner.val)
}

func (s *Wire) FixShape() bool {
	return bool(C.topo_shape_fix_shape(s.inner.val.shp))
}

func (s *Wire) Copy() *Wire {
	var val C.struct__topo_wire_t
	val.shp = C.topo_shape_copy(s.inner.val.shp)
	wr := &Wire{inner: &innerWire{val: val}}
	runtime.SetFinalizer(wr.inner, (*innerWire).free)
	return wr
}

func (s *Wire) Mesh(m *MeshReceiver, tolerance, deflection, angle float64) {
	C.topo_shape_mesh(s.inner.val.shp, m.inner.val, C.double(tolerance), C.double(deflection), C.double(angle), C.bool(false))
}

func (s *Wire) MeshWithTexture(m *MeshReceiver, tolerance, deflection, angle float64) {
	m.hasTexCoords = true
	C.topo_shape_mesh(s.inner.val.shp, m.inner.val, C.double(tolerance), C.double(deflection), C.double(angle), C.bool(true))
}

func (s *Wire) SetSurfaceColour(c Color) {
	C.topo_shape_set_surface_colour(s.inner.val.shp, c.val)
}

func (s *Wire) SetCurveColour(c Color) {
	C.topo_shape_set_curve_colour(s.inner.val.shp, c.val)
}

func (s *Wire) SetLabel(l string) {
	str := C.CString(l)
	defer C.free(unsafe.Pointer(str))
	C.topo_shape_set_label(s.inner.val.shp, str)
}

func (s *Wire) SetUVOrigin(u, v float64) {
	C.topo_shape_set_u_origin(s.inner.val.shp, C.double(u))
	C.topo_shape_set_v_origin(s.inner.val.shp, C.double(v))
}

func (s *Wire) SetUVRepeat(u, v float64) {
	C.topo_shape_set_u_repeat(s.inner.val.shp, C.double(u))
	C.topo_shape_set_v_repeat(s.inner.val.shp, C.double(v))
}

func (s *Wire) SetScaleU(u float64) {
	C.topo_shape_set_scale_u(s.inner.val.shp, C.double(u))
}

func (s *Wire) SetScaleV(v float64) {
	C.topo_shape_set_scale_v(s.inner.val.shp, C.double(v))
}

func (s *Wire) SetAutoScaleSizeOnU(u float64) {
	C.topo_shape_set_auto_scale_size_on_u(s.inner.val.shp, C.double(u))
}

func (s *Wire) SetAutoScaleSizeOnV(v float64) {
	C.topo_shape_set_auto_scale_size_on_v(s.inner.val.shp, C.double(v))
}

func (s *Wire) SetTextureMapType(t int) {
	C.topo_shape_set_txture_map_type(s.inner.val.shp, C.int(t))
}

func (s *Wire) SetRotationAngle(a float64) {
	C.topo_shape_set_rotation_angle(s.inner.val.shp, C.double(a))
}

func (s *Wire) GetSurfaceColour() Color {
	return Color{val: C.topo_shape_get_surface_colour(s.inner.val.shp)}
}

func (s *Wire) GetCurveColour() Color {
	return Color{val: C.topo_shape_get_surface_colour(s.inner.val.shp)}
}

func (s *Wire) GetLabel() string {
	return C.GoString(C.topo_shape_get_label(s.inner.val.shp))
}

func (s *Wire) GetUVOrigin() (u, v float64) {
	u = float64(C.topo_shape_get_u_origin(s.inner.val.shp))
	v = float64(C.topo_shape_get_v_origin(s.inner.val.shp))
	return
}

func (s *Wire) GetUVRepeat() (u, v float64) {
	u = float64(C.topo_shape_get_u_repeat(s.inner.val.shp))
	v = float64(C.topo_shape_get_v_repeat(s.inner.val.shp))
	return
}

func (s *Wire) GetUVScale() (u, v float64) {
	u = float64(C.topo_shape_get_scale_u(s.inner.val.shp))
	v = float64(C.topo_shape_get_scale_v(s.inner.val.shp))
	return
}

func (s *Wire) GetUVAutoScaleSize() (u, v float64) {
	u = float64(C.topo_shape_get_auto_scale_size_on_u(s.inner.val.shp))
	v = float64(C.topo_shape_get_auto_scale_size_on_v(s.inner.val.shp))
	return
}

func (s *Wire) GetTxtureMapType() int {
	return int(C.topo_shape_get_txture_map_type(s.inner.val.shp))
}

func (s *Wire) GetRotationAngle() float64 {
	return float64(C.topo_shape_get_rotation_angle(s.inner.val.shp))
}

func (t *Wire) ToShape() *Shape {
	sp := &Shape{inner: &innerShape{val: C.topo_shape_share(t.inner.val.shp)}}
	runtime.SetFinalizer(sp.inner, (*innerShape).free)
	return sp
}

func (t *innerWire) free() {
	C.topo_wire_free(t.val)
}

func (t *Wire) NumVertices() int {
	return int(C.topo_wire_num_vertices(t.inner.val))
}

func (t *Wire) NumEdges() int {
	return int(C.topo_wire_num_edges(t.inner.val))
}

func (t *Wire) IsClosed() bool {
	return bool(C.topo_wire_is_closed(t.inner.val))
}

func (t *Wire) Length() int {
	return int(C.topo_wire_length(t.inner.val))
}

func (t *Wire) ToCurves3d() {
	C.topo_wire_convert_to_curves3d(t.inner.val)
}

func (t *Wire) Project(f Face) int {
	return int(C.topo_wire_project(t.inner.val, f.inner.val))
}

func (t *Wire) Offset(distance float64, joinType int) int {
	return int(C.topo_wire_offset(t.inner.val, C.double(distance), C.int(joinType)))
}

func (t *Wire) Fillet(vertices []Vertex, radius []float64) int {
	vers := make([]C.struct__topo_vertex_t, len(vertices))
	for i := range vertices {
		vers[i] = vertices[i].inner.val
	}
	return int(C.topo_wire_fillet(t.inner.val, &vers[0], C.int(len(vertices)), (*C.double)(unsafe.Pointer(&radius[0])), C.int(len(radius))))
}

func (t *Wire) Chamfer(vertices []Vertex, radius []float64) int {
	vers := make([]C.struct__topo_vertex_t, len(vertices))
	for i := range vertices {
		vers[i] = vertices[i].inner.val
	}
	return int(C.topo_wire_chamfer(t.inner.val, &vers[0], C.int(len(vertices)), (*C.double)(unsafe.Pointer(&radius[0])), C.int(len(radius))))
}

func TopoMakePolygon() *Wire {
	wr := &Wire{inner: &innerWire{val: C.topo_make_polygon()}}
	runtime.SetFinalizer(wr.inner, (*innerWire).free)
	return wr
}

func TopoMakePolygonFromTwoPoint(p1, p2 Point3) *Wire {
	wr := &Wire{inner: &innerWire{val: C.topo_make_polygon_from_two_point(p1.val, p2.val)}}
	runtime.SetFinalizer(wr.inner, (*innerWire).free)
	return wr
}

func TopoMakePolygonFromThreePoint(p1, p2, p3 Point3, Close bool) *Wire {
	wr := &Wire{inner: &innerWire{val: C.topo_make_polygon_from_three_point(p1.val, p2.val, p3.val, C.bool(Close))}}
	runtime.SetFinalizer(wr.inner, (*innerWire).free)
	return wr
}

func TopoMakePolygonFromFourPoint(p1, p2, p3, p4 Point3, Close bool) *Wire {
	wr := &Wire{inner: &innerWire{val: C.topo_make_polygon_from_four_point(p1.val, p2.val, p3.val, p4.val, C.bool(Close))}}
	runtime.SetFinalizer(wr.inner, (*innerWire).free)
	return wr
}

func TopoMakePolygonFromTwoVertex(p1, p2 Vertex) *Wire {
	wr := &Wire{inner: &innerWire{val: C.topo_make_polygon_two_vertex(p1.inner.val, p2.inner.val)}}
	runtime.SetFinalizer(wr.inner, (*innerWire).free)
	return wr
}

func TopoMakePolygonFromThreeVertex(p1, p2, p3 Vertex, Close bool) *Wire {
	wr := &Wire{inner: &innerWire{val: C.topo_make_polygon_from_three_vertex(p1.inner.val, p2.inner.val, p3.inner.val, C.bool(Close))}}
	runtime.SetFinalizer(wr.inner, (*innerWire).free)
	return wr
}

func TopoMakePolygonFromFourVertex(p1, p2, p3, p4 Vertex, Close bool) *Wire {
	wr := &Wire{inner: &innerWire{val: C.topo_make_polygon_from_four_vertex(p1.inner.val, p2.inner.val, p3.inner.val, p4.inner.val, C.bool(Close))}}
	runtime.SetFinalizer(wr.inner, (*innerWire).free)
	return wr
}

func TopoMakeWireFromEdge(p Edge) *Wire {
	wr := &Wire{inner: &innerWire{val: C.topo_make_wire_from_edge(p.inner.val)}}
	runtime.SetFinalizer(wr.inner, (*innerWire).free)
	return wr
}

func TopoMakeWireFromTwoEdge(p1, p2 Edge) *Wire {
	wr := &Wire{inner: &innerWire{val: C.topo_make_wire_from_two_edge(p1.inner.val, p2.inner.val)}}
	runtime.SetFinalizer(wr.inner, (*innerWire).free)
	return wr
}

func TopoMakeWireFromThreeEdge(p1, p2, p3 Edge) *Wire {
	wr := &Wire{inner: &innerWire{val: C.topo_make_wire_from_three_edge(p1.inner.val, p2.inner.val, p3.inner.val)}}
	runtime.SetFinalizer(wr.inner, (*innerWire).free)
	return wr
}

func TopoMakeWireFromFourEdge(p1, p2, p3, p4 Edge) *Wire {
	wr := &Wire{inner: &innerWire{val: C.topo_make_wire_from_four_edge(p1.inner.val, p2.inner.val, p3.inner.val, p4.inner.val)}}
	runtime.SetFinalizer(wr.inner, (*innerWire).free)
	return wr
}

func TopoMakeWireFromWire(p Wire) *Wire {
	wr := &Wire{inner: &innerWire{val: C.topo_make_wire_from_wire(p.inner.val)}}
	runtime.SetFinalizer(wr.inner, (*innerWire).free)
	return wr
}

func TopoMakeWireFromTwoWire(p1 Wire, p2 Edge) *Wire {
	wr := &Wire{inner: &innerWire{val: C.topo_make_wire_from_two_wire(p1.inner.val, p2.inner.val)}}
	runtime.SetFinalizer(wr.inner, (*innerWire).free)
	return wr
}

func TopoMakeWireFromEdges(edges []Edge) *Wire {
	es := make([]C.struct__topo_edge_t, len(edges))
	for i := range edges {
		es[i] = edges[i].inner.val
	}
	wr := &Wire{inner: &innerWire{val: C.topo_make_wire_from_edges(&es[0], C.int(len(edges)))}}
	runtime.SetFinalizer(wr.inner, (*innerWire).free)
	return wr
}

func TopoMakeWireFromWires(wires []Wire) *Wire {
	es := make([]C.struct__topo_wire_t, len(wires))
	for i := range wires {
		es[i] = wires[i].inner.val
	}
	wr := &Wire{inner: &innerWire{val: C.topo_make_wire_from_wries(&es[0], C.int(len(wires)))}}
	runtime.SetFinalizer(wr.inner, (*innerWire).free)
	return wr
}

type WireIterator struct {
	inner *innerWireIterator
}
type innerWireIterator struct {
	val *C.struct__topo_wire_iterator_t
}

func TopoMakeWireIterator(p Shape) *WireIterator {
	wr := &WireIterator{inner: &innerWireIterator{val: C.topo_wire_iterator_make(p.inner.val)}}
	runtime.SetFinalizer(wr.inner, (*innerWireIterator).free)
	return wr
}

func (t *innerWireIterator) free() {
	C.topo_wire_iterator_free(t.val)
}

func (t *WireIterator) Next() *Wire {
	v := C.topo_wire_iterator_next(t.inner.val)
	if v != nil {
		var val C.struct__topo_wire_t
		val.shp = v
		p := &Wire{inner: &innerWire{val: val}}
		runtime.SetFinalizer(p.inner, (*innerWire).free)
		return p
	}
	return nil
}
