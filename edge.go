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

type Edge struct {
	inner *innerEdge
}

type innerEdge struct {
	val C.struct__topo_edge_t
}

func TopoMakeEdge() *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_make_edge()}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func (s *Edge) IsNull() bool {
	return bool(C.topo_shape_is_null(s.inner.val.shp))
}

func (s *Edge) IsValid() bool {
	return bool(C.topo_shape_is_valid(s.inner.val.shp))
}

func (s *Edge) Equals(e *Shape) bool {
	return bool(C.topo_shape_equals(s.inner.val.shp, e.inner.val))
}

func (s *Edge) Type() int {
	return int(C.topo_shape_type(s.inner.val.shp))
}

func (s *Edge) BBox() BBox {
	return BBox{val: C.topo_shape_bounding_box(s.inner.val.shp)}
}

func (s *Edge) Hash() int {
	return int(C.topo_shape_hash_code(s.inner.val.shp))
}

func (s *Edge) Transform(t Trsf) int {
	return int(C.topo_shape_transform(s.inner.val.shp, t.val))
}

func (s *Edge) Translate(v Vector3) int {
	return int(C.topo_shape_translate(s.inner.val.shp, v.val))
}

func (s *Edge) RotateFromPoint(angle float64, p1, p2 Point3) int {
	return int(C.topo_shape_rotate_from_two_point(s.inner.val.shp, C.double(angle), p1.val, p2.val))
}

func (s *Edge) RotateFromAxis1(angle float64, a Axis1) int {
	return int(C.topo_shape_rotate_from_axis1(s.inner.val.shp, C.double(angle), a.val))
}

func (s *Edge) RotateFromQuaternion(q Quaternion) int {
	return int(C.topo_shape_rotate_from_quaternion(s.inner.val.shp, q.val))
}

func (s *Edge) Scale(angle float64, a Point3) int {
	return int(C.topo_shape_scale(s.inner.val.shp, C.double(angle), a.val))
}

func (s *Edge) MirrorFromPointNorm(pnt, ner Point3) int {
	return int(C.topo_shape_mirror_from_point_norm(s.inner.val.shp, pnt.val, ner.val))
}

func (s *Edge) MirrorFromAxis1(a Axis1) int {
	return int(C.topo_shape_mirror_from_axis1(s.inner.val.shp, a.val))
}

func (s *Edge) MirrorFromAxis2(a Axis2) int {
	return int(C.topo_shape_mirror_from_axis2(s.inner.val.shp, a.val))
}

func (s *Edge) Transformed(t Trsf) *Edge {
	var val C.struct__topo_edge_t
	val.shp = C.topo_shape_transformed(s.inner.val.shp, t.val)
	p := &Edge{inner: &innerEdge{val: val}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func (s *Edge) Translated(v Vector3) *Edge {
	var val C.struct__topo_edge_t
	val.shp = C.topo_shape_translated(s.inner.val.shp, v.val)
	p := &Edge{inner: &innerEdge{val: val}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func (s *Edge) RotatedFromPoint(angle float64, p1, p2 Point3) *Edge {
	var val C.struct__topo_edge_t
	val.shp = C.topo_shape_rotated_from_two_point(s.inner.val.shp, C.double(angle), p1.val, p2.val)
	p := &Edge{inner: &innerEdge{val: val}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func (s *Edge) RotatedFromAxis1(angle float64, a Axis1) *Edge {
	var val C.struct__topo_edge_t
	val.shp = C.topo_shape_rotated_from_axis1(s.inner.val.shp, C.double(angle), a.val)
	p := &Edge{inner: &innerEdge{val: val}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func (s *Edge) RotatedFromQuaternion(q Quaternion) *Edge {
	var val C.struct__topo_edge_t
	val.shp = C.topo_shape_rotated_from_quaternion(s.inner.val.shp, q.val)
	p := &Edge{inner: &innerEdge{val: val}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func (s *Edge) Scaled(angle float64, a Point3) *Edge {
	var val C.struct__topo_edge_t
	val.shp = C.topo_shape_scaled(s.inner.val.shp, C.double(angle), a.val)
	p := &Edge{inner: &innerEdge{val: val}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func (s *Edge) MirroredFromPointNorm(pnt, ner Point3) *Edge {
	var val C.struct__topo_edge_t
	val.shp = C.topo_shape_mirrored_from_point_norm(s.inner.val.shp, pnt.val, ner.val)
	p := &Edge{inner: &innerEdge{val: val}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func (s *Edge) MirroredFromAxis1(a Axis1) *Edge {
	var val C.struct__topo_edge_t
	val.shp = C.topo_shape_mirrored_from_axis1(s.inner.val.shp, a.val)
	p := &Edge{inner: &innerEdge{val: val}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func (s *Edge) MirroredFromAxis2(a Axis2) *Edge {
	var val C.struct__topo_edge_t
	val.shp = C.topo_shape_mirrored_from_axis2(s.inner.val.shp, a.val)
	p := &Edge{inner: &innerEdge{val: val}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func (s *Edge) GetOrientation() int {
	return int(C.topo_shape_get_orientation(s.inner.val.shp))
}

func (s *Edge) SetOrientation(t int) {
	C.topo_shape_set_orientation(s.inner.val.shp, C.int(t))
}

func (s *Edge) GetLocation() *TopoLocation {
	p := &TopoLocation{inner: &innerTopoLocation{val: C.topo_shape_get_location(s.inner.val.shp)}}
	runtime.SetFinalizer(p.inner, (*innerTopoLocation).free)
	return p
}

func (s *Edge) SetLocation(t *TopoLocation) {
	C.topo_shape_set_location(s.inner.val.shp, t.inner.val)
}

func (s *Edge) FixShape() bool {
	return bool(C.topo_shape_fix_shape(s.inner.val.shp))
}

func (s *Edge) Copy() *Edge {
	var val C.struct__topo_edge_t
	val.shp = C.topo_shape_copy(s.inner.val.shp)
	p := &Edge{inner: &innerEdge{val: val}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func (s *Edge) Mesh(m *MeshReceiver, tolerance, deflection, angle float64) {
	C.topo_shape_mesh(s.inner.val.shp, m.inner.val, C.double(tolerance), C.double(deflection), C.double(angle), C.bool(false))
}

func (s *Edge) MeshWithTexture(m *MeshReceiver, tolerance, deflection, angle float64) {
	m.hasTexCoords = true
	C.topo_shape_mesh(s.inner.val.shp, m.inner.val, C.double(tolerance), C.double(deflection), C.double(angle), C.bool(true))
}

func (s *Edge) SetSurfaceColour(c Color) {
	C.topo_shape_set_surface_colour(s.inner.val.shp, c.val)
}

func (s *Edge) SetCurveColour(c Color) {
	C.topo_shape_set_curve_colour(s.inner.val.shp, c.val)
}

func (s *Edge) SetLabel(l string) {
	str := C.CString(l)
	defer C.free(unsafe.Pointer(str))
	C.topo_shape_set_label(s.inner.val.shp, str)
}

func (s *Edge) SetUVOrigin(u, v float64) {
	C.topo_shape_set_u_origin(s.inner.val.shp, C.double(u))
	C.topo_shape_set_v_origin(s.inner.val.shp, C.double(v))
}

func (s *Edge) SetUVRepeat(u, v float64) {
	C.topo_shape_set_u_repeat(s.inner.val.shp, C.double(u))
	C.topo_shape_set_v_repeat(s.inner.val.shp, C.double(v))
}

func (s *Edge) SetScaleU(u float64) {
	C.topo_shape_set_scale_u(s.inner.val.shp, C.double(u))
}

func (s *Edge) SetScaleV(v float64) {
	C.topo_shape_set_scale_v(s.inner.val.shp, C.double(v))
}

func (s *Edge) SetAutoScaleSizeOnU(u float64) {
	C.topo_shape_set_auto_scale_size_on_u(s.inner.val.shp, C.double(u))
}

func (s *Edge) SetAutoScaleSizeOnV(v float64) {
	C.topo_shape_set_auto_scale_size_on_v(s.inner.val.shp, C.double(v))
}

func (s *Edge) SetTextureMapType(t int) {
	C.topo_shape_set_txture_map_type(s.inner.val.shp, C.int(t))
}

func (s *Edge) SetRotationAngle(a float64) {
	C.topo_shape_set_rotation_angle(s.inner.val.shp, C.double(a))
}

func (s *Edge) GetSurfaceColour() Color {
	return Color{val: C.topo_shape_get_surface_colour(s.inner.val.shp)}
}

func (s *Edge) GetCurveColour() Color {
	return Color{val: C.topo_shape_get_surface_colour(s.inner.val.shp)}
}

func (s *Edge) GetLabel() string {
	return C.GoString(C.topo_shape_get_label(s.inner.val.shp))
}

func (s *Edge) GetUVOrigin() (u, v float64) {
	u = float64(C.topo_shape_get_u_origin(s.inner.val.shp))
	v = float64(C.topo_shape_get_v_origin(s.inner.val.shp))
	return
}

func (s *Edge) GetUVRepeat() (u, v float64) {
	u = float64(C.topo_shape_get_u_repeat(s.inner.val.shp))
	v = float64(C.topo_shape_get_v_repeat(s.inner.val.shp))
	return
}

func (s *Edge) GetUVScale() (u, v float64) {
	u = float64(C.topo_shape_get_scale_u(s.inner.val.shp))
	v = float64(C.topo_shape_get_scale_v(s.inner.val.shp))
	return
}

func (s *Edge) GetUVAutoScaleSize() (u, v float64) {
	u = float64(C.topo_shape_get_auto_scale_size_on_u(s.inner.val.shp))
	v = float64(C.topo_shape_get_auto_scale_size_on_v(s.inner.val.shp))
	return
}

func (s *Edge) GetTxtureMapType() int {
	return int(C.topo_shape_get_txture_map_type(s.inner.val.shp))
}

func (s *Edge) GetRotationAngle() float64 {
	return float64(C.topo_shape_get_rotation_angle(s.inner.val.shp))
}

func (t *Edge) IsSeam(f Face) bool {
	return bool(C.topo_edge_is_seam(t.inner.val, f.inner.val))
}

func (t *Edge) IsDegenerated() bool {
	return bool(C.topo_edge_is_degenerated(t.inner.val))
}

func (t *Edge) IsClosed() bool {
	return bool(C.topo_edge_is_closed(t.inner.val))
}

func (t *Edge) IsInifinite() bool {
	return bool(C.topo_edge_is_inifinite(t.inner.val))
}

func (t *Edge) NumVertices() int {
	return int(C.topo_edge_num_vertices(t.inner.val))
}

func (t *Edge) Length() float64 {
	return float64(C.topo_edge_length(t.inner.val))
}

func (t *Edge) Tolerance() float32 {
	return float32(C.topo_edge_tolerance(t.inner.val))
}

func (t *Edge) IsCurve3d() bool {
	return bool(C.topo_edge_is_curve3d(t.inner.val))
}

func (t *Edge) ToCurve3d() {
	C.topo_edge_convert_to_curve3d(t.inner.val)
}

func (e *Edge) Bounds() (min, max float64) {
	C.topo_edge_bounds(e.inner.val, (*C.double)(&min), (*C.double)(&max))
	return
}

func (e *Edge) StartPoint() Point3 {
	return Point3{val: C.topo_edge_start_point(e.inner.val)}
}

func (e *Edge) EndPoint() Point3 {
	return Point3{val: C.topo_edge_end_point(e.inner.val)}
}

func (e *Edge) ParamAt(d float64) float64 {
	return float64(C.topo_edge_param_at(e.inner.val, C.double(d)))
}

func (e *Edge) ParamAtPoint(pt Point3) float64 {
	return float64(C.topo_edge_param_at_point(e.inner.val, pt.val))
}

func (s *Edge) Reverse() {
	C.topo_edge_reverse(s.inner.val)
}

func (e *Edge) Params(pts []Point3, tol float64) []float64 {
	count := len(pts)
	cPoints := make([]C.pnt3d_t, count)
	params := make([]float64, count)

	for i := range pts {
		cPoints[i] = pts[i].val
	}

	C.topo_edge_params(e.inner.val, &cPoints[0], C.int(count),
		(*C.double)(&params[0]), C.double(tol))
	return params
}

func (e *Edge) ParamsLength(locations []float64) []float64 {
	count := len(locations)
	params := make([]float64, count)
	C.topo_edge_params_length(e.inner.val, (*C.double)(&locations[0]),
		C.int(count), (*C.double)(&params[0]))
	return params
}

func (e *Edge) TangentAt(param float64) Dir3 {
	return Dir3{val: C.topo_edge_tangent_at(e.inner.val, C.double(param))}
}

func (e *Edge) Tangents(params []float64) []Dir3 {
	count := len(params)
	tangents := make([]Dir3, count)
	cParams := make([]float64, count)
	copy(cParams, params)

	cTangents := make([]C.dir3d_t, count)
	C.topo_edge_tangents(e.inner.val, (*C.double)(&cParams[0]), C.int(count),
		&cTangents[0])

	for i := range cTangents {
		tangents[i] = Dir3{val: cTangents[i]}
	}
	return tangents
}

func (e *Edge) Normal() Dir3 {
	return Dir3{val: C.topo_edge_normal(e.inner.val)}
}

func (e *Edge) Center() Point3 {
	return Point3{val: C.topo_edge_center(e.inner.val)}
}

func (e *Edge) Radius() float64 {
	return float64(C.topo_edge_radius(e.inner.val))
}

func (e *Edge) PositionAt(d float64, mode int) Point3 {
	return Point3{val: C.topo_edge_position_at(e.inner.val, C.double(d), C.int(mode))}
}

func (e *Edge) Positions(ds []float64, mode int) []Point3 {
	count := len(ds)
	points := make([]Point3, count)
	cPoints := make([]C.pnt3d_t, count)
	cDs := make([]float64, count)
	copy(cDs, ds)

	C.topo_edge_positions(e.inner.val, (*C.double)(&cDs[0]), C.int(count),
		&cPoints[0], C.int(mode))

	for i := range cPoints {
		points[i] = Point3{val: cPoints[i]}
	}
	return points
}

func (e *Edge) SampleUniform(n float64) ([]Point3, []float64) {
	var (
		cPoints    *C.pnt3d_t
		cParams    *C.double
		pointCount C.int
		paramCount C.int
	)

	C.topo_edge_sample_uniform(e.inner.val, C.double(n), &cPoints, &pointCount,
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

func (e *Edge) LocationAt(d float64, mode, frame int, planar bool) *TopoLocation {
	loc := C.topo_edge_location_at(e.inner.val, C.double(d), C.int(mode),
		C.int(frame), C.bool(planar))
	if loc == nil {
		return nil
	}
	return &TopoLocation{inner: &innerTopoLocation{val: loc}}
}

func (e *Edge) Locations(ds []float64, mode, frame int, planar bool) []*TopoLocation {
	count := len(ds)
	cDs := make([]float64, count)
	copy(cDs, ds)

	var resultCount C.int
	locs := C.topo_edge_locations(e.inner.val, (*C.double)(&cDs[0]), C.int(count),
		C.int(mode), C.int(frame), C.bool(planar), &resultCount)
	if locs == nil {
		return nil
	}
	defer C.topo_location_list_free(locs, resultCount)

	locSlice := (*[1 << 30]*C.struct__topo_location_t)(unsafe.Pointer(locs))[:resultCount:resultCount]
	locations := make([]*TopoLocation, resultCount)

	for i := range locSlice {
		locations[i] = &TopoLocation{inner: &innerTopoLocation{val: locSlice[i]}}
	}

	return locations
}

func (e *Edge) Projected(f *Face, direction Vector3, closest bool) ([]*Shape, int) {
	var resultCount C.int
	var cResult **C.struct__topo_shape_t

	ret := C.topo_edge_projected(e.inner.val, f.inner.val, direction.val,
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

func (e *Edge) CurvatureAt(d float64, mode int, resolution float64) float64 {
	return float64(C.topo_edge_curvature_at(e.inner.val, C.double(d),
		C.int(mode), C.double(resolution)))
}

func (e *Edge) Curvatures(ds []float64, mode int, resolution float64) []float64 {
	count := len(ds)
	curvatures := make([]float64, count)
	cDs := make([]float64, count)
	copy(cDs, ds)

	C.topo_edge_curvatures(e.inner.val, (*C.double)(&cDs[0]), C.int(count),
		(*C.double)(&curvatures[0]), C.int(mode), C.double(resolution))
	return curvatures
}

func (t *Edge) ToShape() *Shape {
	sp := &Shape{inner: &innerShape{val: C.topo_shape_share(t.inner.val.shp)}}
	runtime.SetFinalizer(sp.inner, (*innerShape).free)
	return sp
}

func (t *innerEdge) free() {
	C.topo_edge_free(t.val)
}

func TopoMakeEdgeFromPoints(pts []Point3) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_points(&pts[0].val, C.int(len(pts)))}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeEdgeFromTwoVertex(v1, v2 Vertex) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_two_vertex(v1.inner.val, v2.inner.val)}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeEdgeFromTwoPoint(p1, p2 Point3) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_two_point(p1.val, p2.val)}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeEdgeFromLine(l Line) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_line(l.val)}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeEdgeFromLineParm(l Line, p1, p2 float64) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_line_p(l.val, C.double(p1), C.double(p2))}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeEdgeFromLinePoint(l Line, p1, p2 Point3) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_line_point(l.val, p1.val, p2.val)}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeEdgeFromLineVertex(l Line, p1, p2 Vertex) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_line_vertex(l.val, p1.inner.val, p2.inner.val)}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeEdgeFromCirc(s Circ) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_circ(s.val)}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeEdgeFromCircParm(s Circ, p1, p2 float64) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_circ_p(s.val, C.double(p1), C.double(p2))}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeEdgeFromCircPoint(s Circ, p1, p2 Point3) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_circ_point(s.val, p1.val, p2.val)}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeEdgeFromCircVertex(s Circ, p1, p2 Vertex) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_circ_vertex(s.val, p1.inner.val, p2.inner.val)}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeEdgeFromElips(s Elips) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_elips(s.val)}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeEdgeFromElipsParm(s Elips, p1, p2 float64) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_elips_p(s.val, C.double(p1), C.double(p2))}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeEdgeFromElipsPoint(s Elips, p1, p2 Point3) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_elips_point(s.val, p1.val, p2.val)}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeEdgeFromElipsVertex(s Elips, p1, p2 Vertex) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_elips_vertex(s.val, p1.inner.val, p2.inner.val)}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeEdgeFromHyper(s Hyperbola) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_hyper(s.val)}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeEdgeFromHyperParm(s Hyperbola, p1, p2 float64) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_hyper_p(s.val, C.double(p1), C.double(p2))}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeEdgeFromHyperPoint(s Hyperbola, p1, p2 Point3) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_hyper_point(s.val, p1.val, p2.val)}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeEdgeFromHyperVertex(s Hyperbola, p1, p2 Vertex) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_hyper_vertex(s.val, p1.inner.val, p2.inner.val)}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeEdgeFromPara(s Parabola) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_parab(s.val)}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeEdgeFromParaParm(s Parabola, p1, p2 float64) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_parab_p(s.val, C.double(p1), C.double(p2))}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}
func TopoMakeEdgeFromParaPoint(s Parabola, p1, p2 Point3) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_parab_point(s.val, p1.val, p2.val)}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeEdgeFromParaVertex(s Parabola, p1, p2 Vertex) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_parab_vertex(s.val, p1.inner.val, p2.inner.val)}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}
func TopoMakeEdgeFromCurve(s GeomCurve) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edgee_from_curve(s.inner.geom)}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}
func TopoMakeEdgeFromCurveParm(s GeomCurve, p1, p2 float64) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_curve_p(s.inner.geom, C.double(p1), C.double(p2))}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}
func TopoMakeEdgeFromCurvePoint(s GeomCurve, p1, p2 Point3) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_curve_point(s.inner.geom, p1.val, p2.val)}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeEdgeFromCurveVertex(s GeomCurve, p1, p2 Vertex) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_curve_vertex(s.inner.geom, p1.inner.val, p2.inner.val)}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeEdgeFromCurvePointParm(s GeomCurve, pt1, pt2 Point3, p1, p2 float64) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edgee_from_curve_point_p(s.inner.geom, pt1.val, pt2.val, C.double(p1), C.double(p2))}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}
func TopoMakeEdgeFromCurveVertexParm(s GeomCurve, pt1, pt2 Vertex, p1, p2 float64) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_curve_vertex_p(s.inner.geom, pt1.inner.val, pt2.inner.val, C.double(p1), C.double(p2))}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeEdgeFromSurface(cu Geom2dCurve, s GeomSurface) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_curve_surface(cu.inner.geom, s.inner.geom)}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeEdgeFromSurfaceParm(cu Geom2dCurve, s GeomSurface, p1, p2 float64) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_curve_surface_p(cu.inner.geom, s.inner.geom, C.double(p1), C.double(p2))}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeEdgeFromSurfacePoint(cu Geom2dCurve, s GeomSurface, p1, p2 Point3) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_curve_surface_point(cu.inner.geom, s.inner.geom, p1.val, p2.val)}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeEdgeFromSurfaceVertex(cu Geom2dCurve, s GeomSurface, p1, p2 Vertex) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_curve_surface_vertex(cu.inner.geom, s.inner.geom, p1.inner.val, p2.inner.val)}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeEdgeFromSurfacePointParm(cu Geom2dCurve, s GeomSurface, pt1, pt2 Point3, p1, p2 float64) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_curve_surface_point_p(cu.inner.geom, s.inner.geom, pt1.val, pt2.val, C.double(p1), C.double(p2))}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeEdgeFromSurfaceVertexParm(cu Geom2dCurve, s GeomSurface, pt1, pt2 Vertex, p1, p2 float64) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_curve_surface_vertex_p(cu.inner.geom, s.inner.geom, pt1.inner.val, pt2.inner.val, C.double(p1), C.double(p2))}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeEdge2dFromTwoVertex(pt1, pt2 Vertex) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge2d_from_two_vertex(pt1.inner.val, pt2.inner.val)}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeEdge2dFromTwoPoint(pt1, pt2 Point2) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge2d_from_two_point(pt1.val, pt2.val)}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeEdge2dFromLine(l Line2d) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge2d_from_line(l.val)}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeEdge2dFromLineParm(l Line2d, p1, p2 float64) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge2d_from_line_p(l.val, C.double(p1), C.double(p2))}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeEdge2dFromLinePoint(l Line2d, p1, p2 Point2) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge2d_from_line_point(l.val, p1.val, p2.val)}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeEdge2dFromLineVertex(l Line2d, p1, p2 Vertex) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge2d_from_line_vertex(l.val, p1.inner.val, p2.inner.val)}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeEdge2dFromCirc(l Circ2d) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge2d_from_circ(l.val)}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeEdge2dFromCircParm(l Circ2d, p1, p2 float64) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge2d_from_circ_p(l.val, C.double(p1), C.double(p2))}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeEdge2dFromCircPoint(l Circ2d, p1, p2 Point2) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge2d_from_circ_point(l.val, p1.val, p2.val)}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeEdge2dFromCircVertex(l Circ2d, p1, p2 Vertex) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge2d_from_circ_vertex(l.val, p1.inner.val, p2.inner.val)}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeEdge2dFromElips(l Elips2d) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge2d_from_elips(l.val)}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeEdge2dFromElipsParm(l Elips2d, p1, p2 float64) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge2d_from_elips_p(l.val, C.double(p1), C.double(p2))}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeEdge2dFromElipsPoint(l Elips2d, p1, p2 Point2) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge2d_from_elips_point(l.val, p1.val, p2.val)}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeEdge2dFromElipsVertex(l Elips2d, p1, p2 Vertex) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge2d_from_elips_vertex(l.val, p1.inner.val, p2.inner.val)}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeEdge2dFromHyper(l Hyperbola2d) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge2d_from_hyper(l.val)}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeEdge2dFromHyperParm(l Hyperbola2d, p1, p2 float64) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge2d_from_hyper_p(l.val, C.double(p1), C.double(p2))}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeEdge2dFromHyperPoint(l Hyperbola2d, p1, p2 Point2) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge2d_from_hyper_point(l.val, p1.val, p2.val)}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeEdge2dFromHyperVertex(l Hyperbola2d, p1, p2 Vertex) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge2d_from_hyper_vertex(l.val, p1.inner.val, p2.inner.val)}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeEdge2dFromPara(l Parabola2d) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge2d_from_parab(l.val)}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeEdge2dFromParaParm(l Parabola2d, p1, p2 float64) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge2d_from_parab_p(l.val, C.double(p1), C.double(p2))}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeEdge2dFromParaPoint(l Parabola2d, p1, p2 Point2) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge2d_from_parab_point(l.val, p1.val, p2.val)}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeEdge2dFromParaVertex(l Parabola2d, p1, p2 Vertex) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge2d_from_parab_vertex(l.val, p1.inner.val, p2.inner.val)}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeEdge2dFromCurve(l Geom2dCurve) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge2d_from_curve(l.inner.geom)}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeEdge2dFromCurveParm(l Geom2dCurve, p1, p2 float64) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge2d_from_curve_p(l.inner.geom, C.double(p1), C.double(p2))}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeEdge2dFromCurvePoint(l Geom2dCurve, p1, p2 Point2) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge2d_from_curve_point(l.inner.geom, p1.val, p2.val)}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeEdge2dFromCurveVertex(l Geom2dCurve, p1, p2 Vertex) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge2d_from_curve_vertex(l.inner.geom, p1.inner.val, p2.inner.val)}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeEdge2dFromCurvePointParm(l Geom2dCurve, pt1, pt2 Point2, p1, p2 float64) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge2d_from_curve_point_p(l.inner.geom, pt1.val, pt2.val, C.double(p1), C.double(p2))}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeEdge2dFromCurveVertexParm(l Geom2dCurve, pt1, pt2 Vertex, p1, p2 float64) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge2d_from_curve_vertex_p(l.inner.geom, pt1.inner.val, pt2.inner.val, C.double(p1), C.double(p2))}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoEdgeMakePolygon() *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_polygon()}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoEdgeMakePolygonFromTwoPoint(p1, p2 Point3) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_polygon_from_two_point(p1.val, p2.val)}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoEdgeMakePolygonFromThreePoint(p1, p2, p3 Point3, Close bool) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_polygon_from_three_point(p1.val, p2.val, p3.val, C.bool(Close))}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoEdgeMakePolygonFromFourPoint(p1, p2, p3, p4 Point3, Close bool) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_polygon_from_four_point(p1.val, p2.val, p3.val, p4.val, C.bool(Close))}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoEdgeMakePolygonFromTwoVertex(p1, p2 Vertex) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_polygon_from_two_vertex(p1.inner.val, p2.inner.val)}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoEdgeMakePolygonFromThreeVertex(p1, p2, p3 Vertex, Close bool) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_polygon_from_three_vertex(p1.inner.val, p2.inner.val, p3.inner.val, C.bool(Close))}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoEdgeMakePolygonFromFourVertex(p1, p2, p3, p4 Vertex, Close bool) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_polygon_from_four_vertex(p1.inner.val, p2.inner.val, p3.inner.val, p4.inner.val, C.bool(Close))}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoEdgeMakePolygonFromVertices(vers []Vertex, Close bool) *Edge {
	cvs := make([]C.struct__topo_vertex_t, len(vers))
	for i := range vers {
		cvs[i] = vers[i].inner.val
	}
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_polygon_from_vertices(&cvs[0], C.int(len(vers)), C.bool(Close))}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoEdgeMakePolygonFromPoints(points []Point3, Close bool) *Edge {
	cvs := make([]C.struct__pnt3d_t, len(points))
	for i := range points {
		cvs[i] = points[i].val
	}
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_polygonn_from_points(&cvs[0], C.int(len(points)), C.bool(Close))}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeRect(width, height float64) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_rect(C.double(width), C.double(height))}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeSpline(vertices []Point3, tol float64, periodic bool) *Edge {
	count := len(vertices)
	cVertices := make([]C.pnt3d_t, count)
	for i, v := range vertices {
		cVertices[i] = v.val
	}
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_spline(&cVertices[0], C.int(count),
		C.double(tol), C.bool(periodic))}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeSplineFromTangentsAndParameters(points []Point3, tangents []Vector3,
	parameters []float64, tol float64, periodic, scale bool) *Edge {
	pntCount := len(points)
	tanCount := len(tangents)
	paramCount := len(parameters)

	cPoints := make([]C.pnt3d_t, pntCount)
	for i, p := range points {
		cPoints[i] = p.val
	}

	cTangents := make([]C.vec3d_t, tanCount)
	for i, t := range tangents {
		cTangents[i] = t.val
	}

	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_spline_from_tangents_and_parameters(
		&cPoints[0], C.int(pntCount), &cTangents[0], C.int(tanCount),
		(*C.double)(&parameters[0]), C.int(paramCount), C.double(tol),
		C.bool(periodic), C.bool(scale))}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeSplineApprox(points []Point3, tolerance float64, smoothing []float64,
	minDegree, maxDegree int) *Edge {
	count := len(points)
	cPoints := make([]C.pnt3d_t, count)
	for i, p := range points {
		cPoints[i] = p.val
	}

	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_spline_approx(
		&cPoints[0], C.int(count), C.double(tolerance),
		(*C.double)(&smoothing[0]), C.int(minDegree), C.int(maxDegree))}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeCatenary(p1, p2 Point3,
	slack, maxSag float64, up Dir3, tessellation float64) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_catenary(
		p1.val, p2.val, C.double(slack),
		C.double(maxSag), up.val, C.double(tessellation))}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeCircle(radius float64, center Point3, normal Vector3,
	angle1, angle2 float64, orientation bool) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_circle(
		C.double(radius), center.val, normal.val,
		C.double(angle1), C.double(angle2), C.bool(orientation))}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeEllipse(majorRadius, minorRadius float64, center Point3,
	normal, xnormal Vector3, angle1, angle2 float64, sense int) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_ellipse(
		C.double(majorRadius), C.double(minorRadius), center.val, normal.val,
		xnormal.val, C.double(angle1), C.double(angle2), C.int(sense))}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeBezier(points []Point3) *Edge {
	count := len(points)
	cPoints := make([]C.pnt3d_t, count)
	for i, p := range points {
		cPoints[i] = p.val
	}
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_bezier(
		&cPoints[0], C.int(count))}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeThreePointArc(v1, v2, v3 Point3) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_three_point_arc(
		v1.val, v2.val, v3.val)}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeEdgeCircleCenterArc(v1, center, v2 Point3) *Edge {
	p := &Edge{
		inner: &innerEdge{
			val: C.topo_edge_make_circle_center_arc(v1.val, center.val, v2.val),
		},
	}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func TopoMakeTangentArc(v1 Point3, tangent Vector3, v3 Point3) *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_edge_make_tangent_arc(
		v1.val, tangent.val, v3.val)}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

type EdgeIterator struct {
	inner *innerEdgeIterator
}
type innerEdgeIterator struct {
	val *C.struct__topo_edge_iterator_t
}

func TopoMakeEdgeIterator(p Shape) *EdgeIterator {
	wr := &EdgeIterator{inner: &innerEdgeIterator{val: C.topo_edge_iterator_make(p.inner.val)}}
	runtime.SetFinalizer(wr.inner, (*innerEdgeIterator).free)
	return wr
}

func (t *innerEdgeIterator) free() {
	C.topo_edge_iterator_free(t.val)
}

func (t *EdgeIterator) Next() *Edge {
	v := C.topo_edge_iterator_next(t.inner.val)
	if v != nil {
		var val C.struct__topo_edge_t
		val.shp = v
		p := &Edge{inner: &innerEdge{val: val}}
		runtime.SetFinalizer(p.inner, (*innerEdge).free)
		return p
	}
	return nil
}
