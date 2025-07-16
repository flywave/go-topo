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

func (w *Wire) Bounds() (min, max float64) {
	C.topo_wire_bounds(w.inner.val, (*C.double)(&min), (*C.double)(&max))
	return
}

func (w *Wire) StartPoint() Point3 {
	return Point3{val: C.topo_wire_start_point(w.inner.val)}
}

func (w *Wire) EndPoint() Point3 {
	return Point3{val: C.topo_wire_end_point(w.inner.val)}
}

func (w *Wire) ParamAt(d float64) float64 {
	return float64(C.topo_wire_param_at(w.inner.val, C.double(d)))
}

func (w *Wire) ParamAtPoint(pt Point3) float64 {
	return float64(C.topo_wire_param_at_point(w.inner.val, pt.val))
}

func (w *Wire) Params(pts []Point3, tol float64) []float64 {
	count := len(pts)
	cPoints := make([]C.pnt3d_t, count)
	params := make([]float64, count)

	for i := range pts {
		cPoints[i] = pts[i].val
	}

	C.topo_wire_params(w.inner.val, &cPoints[0], C.int(count),
		(*C.double)(&params[0]), C.double(tol))
	return params
}

func (w *Wire) ParamsLength(locations []float64) []float64 {
	count := len(locations)
	params := make([]float64, count)
	C.topo_wire_params_length(w.inner.val, (*C.double)(&locations[0]),
		C.int(count), (*C.double)(&params[0]))
	return params
}

func (w *Wire) TangentAt(param float64) Dir3 {
	return Dir3{val: C.topo_wire_tangent_at(w.inner.val, C.double(param))}
}

func (w *Wire) Tangents(params []float64) []Dir3 {
	count := len(params)
	tangents := make([]Dir3, count)
	cParams := make([]float64, count)
	copy(cParams, params)

	cTangents := make([]C.dir3d_t, count)
	C.topo_wire_tangents(w.inner.val, (*C.double)(&cParams[0]), C.int(count),
		&cTangents[0])

	for i := range cTangents {
		tangents[i] = Dir3{val: cTangents[i]}
	}
	return tangents
}

func (w *Wire) Normal() Dir3 {
	return Dir3{val: C.topo_wire_normal(w.inner.val)}
}

func (w *Wire) Center() Point3 {
	return Point3{val: C.topo_wire_center(w.inner.val)}
}

func (w *Wire) Radius() float64 {
	return float64(C.topo_wire_radius(w.inner.val))
}

func (w *Wire) PositionAt(d float64, mode int) Point3 {
	return Point3{val: C.topo_wire_position_at(w.inner.val, C.double(d), C.int(mode))}
}

func (w *Wire) Positions(ds []float64, mode int) []Point3 {
	count := len(ds)
	points := make([]Point3, count)
	cPoints := make([]C.pnt3d_t, count)
	cDs := make([]float64, count)
	copy(cDs, ds)

	C.topo_wire_positions(w.inner.val, (*C.double)(&cDs[0]), C.int(count),
		&cPoints[0], C.int(mode))

	for i := range cPoints {
		points[i] = Point3{val: cPoints[i]}
	}
	return points
}

func (w *Wire) SampleUniform(n float64) ([]Point3, []float64) {
	var (
		cPoints    *C.pnt3d_t
		cParams    *C.double
		pointCount C.int
		paramCount C.int
	)

	C.topo_wire_sample_uniform(w.inner.val, C.double(n), &cPoints, &pointCount,
		&cParams, &paramCount)
	defer func() {
		C.free(unsafe.Pointer(cPoints))
		C.free(unsafe.Pointer(cParams))
	}()

	points := make([]Point3, pointCount)
	params := make([]float64, paramCount)

	pointSlice := (*[1 << 30]C.pnt3d_t)(unsafe.Pointer(cPoints))[:pointCount:pointCount]
	paramSlice := (*[1 << 30]C.double)(unsafe.Pointer(cParams))[:paramCount:paramCount]

	for i := range pointSlice {
		points[i] = Point3{val: pointSlice[i]}
	}
	for i := range paramSlice {
		params[i] = float64(paramSlice[i])
	}

	return points, params
}

func (w *Wire) LocationAt(d float64, mode, frame int, planar bool) *TopoLocation {
	loc := C.topo_wire_location_at(w.inner.val, C.double(d), C.int(mode),
		C.int(frame), C.bool(planar))
	if loc == nil {
		return nil
	}
	return &TopoLocation{inner: &innerTopoLocation{val: loc}}
}

func (w *Wire) Locations(ds []float64, mode, frame int, planar bool) []*TopoLocation {
	count := len(ds)
	cDs := make([]float64, count)
	copy(cDs, ds)

	var resultCount C.int
	locs := C.topo_wire_locations(w.inner.val, (*C.double)(&cDs[0]), C.int(count),
		C.int(mode), C.int(frame), C.bool(planar), &resultCount)
	if locs == nil {
		return nil
	}
	defer C.topo_location_list_free(locs, resultCount)

	locSlice := (*[1 << 30]*C.struct__topo_location_t)(unsafe.Pointer(locs))[:resultCount:resultCount]
	locations := make([]*TopoLocation, resultCount)

	for i := range locSlice {
		locations[i] = &TopoLocation{inner: &innerTopoLocation{val: locSlice[i]}}
		runtime.SetFinalizer(locations[i].inner, (*innerTopoLocation).free)
	}

	return locations
}

func (w *Wire) Projected(f *Face, direction Vector3, closest bool) ([]*Shape, int) {
	var resultCount C.int
	var cResult **C.struct__topo_shape_t

	ret := C.topo_wire_projected(w.inner.val, f.inner.val, direction.val,
		C.bool(closest), &cResult, &resultCount)
	if ret != 0 || cResult == nil {
		return nil, 0
	}
	defer C.topo_shape_list_free(cResult, resultCount)

	resultSlice := (*[1 << 30]*C.struct__topo_shape_t)(unsafe.Pointer(cResult))[:resultCount:resultCount]
	shapes := make([]*Shape, resultCount)

	for i := range resultSlice {
		shapes[i] = &Shape{inner: &innerShape{val: resultSlice[i]}}
	}

	return shapes, int(ret)
}

func (w *Wire) CurvatureAt(d float64, mode int, resolution float64) float64 {
	return float64(C.topo_wire_curvature_at(w.inner.val, C.double(d),
		C.int(mode), C.double(resolution)))
}

func (w *Wire) Curvatures(ds []float64, mode int, resolution float64) []float64 {
	count := len(ds)
	curvatures := make([]float64, count)
	cDs := make([]float64, count)
	copy(cDs, ds)

	C.topo_wire_curvatures(w.inner.val, (*C.double)(&cDs[0]), C.int(count),
		(*C.double)(&curvatures[0]), C.int(mode), C.double(resolution))
	return curvatures
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

func TopoMakeWireFromRect(width, height float64) *Wire {
	wr := &Wire{inner: &innerWire{val: C.topo_make_wire_from_rect(C.double(width), C.double(height))}}
	runtime.SetFinalizer(wr.inner, (*innerWire).free)
	return wr
}

func TopoMakeWireFromCircle(radius float64, center Point3, normal Dir3) *Wire {
	wr := &Wire{inner: &innerWire{val: C.topo_make_wire_from_circle(C.double(radius), center.val, normal.val)}}
	runtime.SetFinalizer(wr.inner, (*innerWire).free)
	return wr
}

func TopoMakeWireFromEllipse(xRadius, yRadius float64, center Point3, normal, xDir Dir3, angle1, angle2, rotationAngle float64, closed bool) *Wire {
	wr := &Wire{inner: &innerWire{val: C.topo_make_wire_from_ellipse(C.double(xRadius), C.double(yRadius), center.val, normal.val, xDir.val, C.double(angle1), C.double(angle2), C.double(rotationAngle), C.bool(closed))}}
	runtime.SetFinalizer(wr.inner, (*innerWire).free)
	return wr
}

func TopoMakeWireFromHelix(pitch, height, radius float64, center Point3, dir Dir3, angle float64, lefthand bool) *Wire {
	wr := &Wire{inner: &innerWire{val: C.topo_make_wire_from_helix(C.double(pitch), C.double(height), C.double(radius), center.val, dir.val, C.double(angle), C.bool(lefthand))}}
	runtime.SetFinalizer(wr.inner, (*innerWire).free)
	return wr
}

func TopoMakeWireFromCombine(wires []Wire, tol float64) []*Wire {
	es := make([]C.struct__topo_wire_t, len(wires))
	for i := range wires {
		es[i] = wires[i].inner.val
	}
	var count C.int
	val := C.topo_make_wire_from_combine(&es[0], C.int(len(wires)), C.double(tol), &count)
	if val == nil {
		return nil
	}
	defer C.topo_wire_list_free(val, count)
	valSlice := (*[1 << 30]C.struct__topo_wire_t)(unsafe.Pointer(val))[:count:count]
	ws := make([]*Wire, count)
	for i := 0; i < int(count); i++ {
		ws[i] = &Wire{inner: &innerWire{val: valSlice[i]}}
		runtime.SetFinalizer(ws[i].inner, (*innerWire).free)
	}
	return ws
}

type SweepCurveType int

const (
	SweepCurveTypeLine            = SweepCurveType(C.CURVE_LINE)
	SweepCurveTypeThreePointArc   = SweepCurveType(C.CURVE_THREE_POINT_ARC)
	SweepCurveTypeCircleCenterArc = SweepCurveType(C.CURVE_CIRCLE_CENTER_ARC)
	SweepCurveTypeSpline          = SweepCurveType(C.CURVE_SPLINE)
)

func TopoMakeWireFromCombineCurve(points [][]Point3, curveTypes []SweepCurveType) *Wire {
	curveCount := len(points)
	if curveCount == 0 {
		return &Wire{inner: &innerWire{}}
	}

	// 分配C内存来存储曲线指针数组
	cPointsArray := C.malloc(C.size_t(curveCount) * C.size_t(unsafe.Sizeof(unsafe.Pointer(nil))))
	defer C.free(cPointsArray)

	// 分配C内存来存储每个曲线的点数据
	cPointCounts := make([]C.int, curveCount)
	for i, pts := range points {
		pointCount := len(pts)
		cPointCounts[i] = C.int(pointCount)

		// 为当前曲线分配点数组内存
		curvePoints := C.malloc(C.size_t(pointCount) * C.size_t(unsafe.Sizeof(C.pnt3d_t{})))

		// 将点数据复制到C内存
		for j := 0; j < pointCount; j++ {
			cPoint := (*C.pnt3d_t)(unsafe.Pointer(uintptr(curvePoints) + uintptr(j)*unsafe.Sizeof(C.pnt3d_t{})))
			*cPoint = pts[j].val
		}

		// 将曲线指针存入指针数组
		ptr := (*unsafe.Pointer)(unsafe.Pointer(uintptr(cPointsArray) + uintptr(i)*unsafe.Sizeof(unsafe.Pointer(nil))))
		*ptr = curvePoints
	}

	// 分配C内存来存储曲线类型数组
	cCurveTypes := C.malloc(C.size_t(curveCount) * C.size_t(unsafe.Sizeof(C.int(0))))
	defer C.free(cCurveTypes)
	for i, t := range curveTypes {
		*(*C.int)(unsafe.Pointer(uintptr(cCurveTypes) + uintptr(i)*unsafe.Sizeof(C.int(0)))) = C.int(t)
	}

	// 调用C函数
	wr := &Wire{
		inner: &innerWire{
			val: C.topo_make_wire_from_combine_curve(
				(**C.pnt3d_t)(cPointsArray),
				(*C.int)(unsafe.Pointer(&cPointCounts[0])),
				C.int(curveCount),
				(*C.int)(cCurveTypes),
			),
		},
	}
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
