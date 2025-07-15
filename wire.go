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
	if len(vertices) == 0 || len(radius) == 0 || len(vertices) != len(radius) {
		return 0
	}

	// 分配C内存
	cVertices := C.malloc(C.size_t(len(vertices)) * C.size_t(unsafe.Sizeof(C.struct__topo_vertex_t{})))
	defer C.free(cVertices)

	cRadius := C.malloc(C.size_t(len(radius)) * C.size_t(unsafe.Sizeof(C.double(0))))
	defer C.free(cRadius)

	// 使用更安全的方式填充数据
	verticesPtr := (*[1<<30 - 1]C.struct__topo_vertex_t)(cVertices)
	radiusPtr := (*[1<<30 - 1]C.double)(cRadius)

	for i := range vertices {
		verticesPtr[i] = vertices[i].inner.val
		radiusPtr[i] = C.double(radius[i])
	}

	return int(C.topo_wire_fillet(
		t.inner.val,
		(*C.struct__topo_vertex_t)(cVertices),
		C.int(len(vertices)),
		(*C.double)(cRadius),
		C.int(len(radius)),
	))
}

func (t *Wire) Chamfer(vertices []Vertex, distance []float64) int {
	if len(vertices) == 0 || len(distance) == 0 || len(vertices) != len(distance) {
		return 0
	}

	// 分配C内存
	cVertices := C.malloc(C.size_t(len(vertices)) * C.size_t(unsafe.Sizeof(C.struct__topo_vertex_t{})))
	defer C.free(cVertices)

	cDistance := C.malloc(C.size_t(len(distance)) * C.size_t(unsafe.Sizeof(C.double(0))))
	defer C.free(cDistance)

	// 填充数据
	verticesPtr := (*[1<<30 - 1]C.struct__topo_vertex_t)(cVertices)
	distancePtr := (*[1<<30 - 1]C.double)(cDistance)

	for i := range vertices {
		verticesPtr[i] = vertices[i].inner.val
		distancePtr[i] = C.double(distance[i])
	}

	return int(C.topo_wire_chamfer(
		t.inner.val,
		(*C.struct__topo_vertex_t)(cVertices),
		C.int(len(vertices)),
		(*C.double)(cDistance),
		C.int(len(distance)),
	))
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
	if len(pts) == 0 {
		return nil
	}

	// 分配C内存
	cPoints := C.malloc(C.size_t(len(pts)) * C.size_t(unsafe.Sizeof(C.pnt3d_t{})))
	defer C.free(cPoints)

	params := make([]float64, len(pts))

	// 填充点数据
	pointsPtr := (*[1<<30 - 1]C.pnt3d_t)(cPoints)
	for i := range pts {
		pointsPtr[i] = pts[i].val
	}

	C.topo_wire_params(
		w.inner.val,
		(*C.pnt3d_t)(cPoints),
		C.int(len(pts)),
		(*C.double)(unsafe.Pointer(&params[0])),
		C.double(tol),
	)

	return params
}

func (w *Wire) ParamsLength(locations []float64) []float64 {
	if len(locations) == 0 {
		return nil
	}

	params := make([]float64, len(locations))

	// 分配C内存
	cLocations := C.malloc(C.size_t(len(locations)) * C.size_t(unsafe.Sizeof(C.double(0))))
	defer C.free(cLocations)

	// 填充数据
	locationsPtr := (*[1<<30 - 1]C.double)(cLocations)
	for i := range locations {
		locationsPtr[i] = C.double(locations[i])
	}

	C.topo_wire_params_length(
		w.inner.val,
		(*C.double)(cLocations),
		C.int(len(locations)),
		(*C.double)(unsafe.Pointer(&params[0])),
	)

	return params
}

func (w *Wire) TangentAt(param float64) Dir3 {
	return Dir3{val: C.topo_wire_tangent_at(w.inner.val, C.double(param))}
}

func (w *Wire) Tangents(params []float64) []Dir3 {
	if len(params) == 0 {
		return nil
	}

	// 分配C内存
	cParams := C.malloc(C.size_t(len(params)) * C.size_t(unsafe.Sizeof(C.double(0))))
	defer C.free(cParams)

	cTangents := C.malloc(C.size_t(len(params)) * C.size_t(unsafe.Sizeof(C.dir3d_t{})))
	defer C.free(cTangents)

	// 填充参数数据
	paramsPtr := (*[1<<30 - 1]C.double)(cParams)
	for i := range params {
		paramsPtr[i] = C.double(params[i])
	}

	C.topo_wire_tangents(
		w.inner.val,
		(*C.double)(cParams),
		C.int(len(params)),
		(*C.dir3d_t)(cTangents),
	)

	// 转换结果
	tangents := make([]Dir3, len(params))
	tangentsPtr := (*[1<<30 - 1]C.dir3d_t)(cTangents)
	for i := range tangents {
		tangents[i] = Dir3{val: tangentsPtr[i]}
	}

	return tangents
}

func (w *Wire) Positions(ds []float64, mode int) []Point3 {
	if len(ds) == 0 {
		return nil
	}

	// 分配C内存
	cDs := C.malloc(C.size_t(len(ds)) * C.size_t(unsafe.Sizeof(C.double(0))))
	defer C.free(cDs)

	cPoints := C.malloc(C.size_t(len(ds)) * C.size_t(unsafe.Sizeof(C.pnt3d_t{})))
	defer C.free(cPoints)

	// 填充参数数据
	dsPtr := (*[1<<30 - 1]C.double)(cDs)
	for i := range ds {
		dsPtr[i] = C.double(ds[i])
	}

	C.topo_wire_positions(
		w.inner.val,
		(*C.double)(cDs),
		C.int(len(ds)),
		(*C.pnt3d_t)(cPoints),
		C.int(mode),
	)

	// 转换结果
	points := make([]Point3, len(ds))
	pointsPtr := (*[1<<30 - 1]C.pnt3d_t)(cPoints)
	for i := range points {
		points[i] = Point3{val: pointsPtr[i]}
	}

	return points
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
	if len(ds) == 0 {
		return nil
	}

	// 分配C内存
	cDs := C.malloc(C.size_t(len(ds)) * C.size_t(unsafe.Sizeof(C.double(0))))
	defer C.free(cDs)

	// 填充参数数据
	dsPtr := (*[1<<30 - 1]C.double)(cDs)
	for i := range ds {
		dsPtr[i] = C.double(ds[i])
	}

	var resultCount C.int
	locs := C.topo_wire_locations(
		w.inner.val,
		(*C.double)(cDs),
		C.int(len(ds)),
		C.int(mode),
		C.int(frame),
		C.bool(planar),
		&resultCount,
	)
	if locs == nil {
		return nil
	}
	defer C.topo_location_list_free(locs, resultCount)

	// 转换结果
	locations := make([]*TopoLocation, resultCount)
	locsPtr := (*[1<<30 - 1]*C.struct__topo_location_t)(unsafe.Pointer(locs))
	for i := range locations {
		locations[i] = &TopoLocation{inner: &innerTopoLocation{val: locsPtr[i]}}
		runtime.SetFinalizer(locations[i].inner, (*innerTopoLocation).free)
	}

	return locations
}

func (w *Wire) Projected(f *Face, direction Vector3, closest bool) ([]*Shape, int) {
	var resultCount C.int
	var cResult **C.struct__topo_shape_t

	ret := C.topo_wire_projected(
		w.inner.val,
		f.inner.val,
		direction.val,
		C.bool(closest),
		&cResult,
		&resultCount,
	)
	if ret != 0 || cResult == nil {
		return nil, 0
	}
	defer C.topo_shape_list_free(cResult, resultCount)

	// 转换结果
	shapes := make([]*Shape, resultCount)
	resultPtr := (*[1<<30 - 1]*C.struct__topo_shape_t)(unsafe.Pointer(cResult))
	for i := range shapes {
		shapes[i] = &Shape{inner: &innerShape{val: resultPtr[i]}}
		runtime.SetFinalizer(shapes[i].inner, (*innerShape).free)
	}

	return shapes, int(ret)
}

func (w *Wire) CurvatureAt(d float64, mode int, resolution float64) float64 {
	return float64(C.topo_wire_curvature_at(w.inner.val, C.double(d),
		C.int(mode), C.double(resolution)))
}

func (w *Wire) Curvatures(ds []float64, mode int, resolution float64) []float64 {
	if len(ds) == 0 {
		return nil
	}

	curvatures := make([]float64, len(ds))

	// 分配C内存
	cDs := C.malloc(C.size_t(len(ds)) * C.size_t(unsafe.Sizeof(C.double(0))))
	defer C.free(cDs)

	// 填充参数数据
	dsPtr := (*[1<<30 - 1]C.double)(cDs)
	for i := range ds {
		dsPtr[i] = C.double(ds[i])
	}

	C.topo_wire_curvatures(
		w.inner.val,
		(*C.double)(cDs),
		C.int(len(ds)),
		(*C.double)(unsafe.Pointer(&curvatures[0])),
		C.int(mode),
		C.double(resolution),
	)

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
	if len(edges) == 0 {
		return &Wire{inner: &innerWire{}}
	}

	// 分配C内存
	cEdges := C.malloc(C.size_t(len(edges)) * C.size_t(unsafe.Sizeof(C.struct__topo_edge_t{})))
	defer C.free(cEdges)

	// 填充数据
	edgesPtr := (*[1<<30 - 1]C.struct__topo_edge_t)(cEdges)
	for i := range edges {
		edgesPtr[i] = edges[i].inner.val
	}

	wr := &Wire{
		inner: &innerWire{
			val: C.topo_make_wire_from_edges(
				(*C.struct__topo_edge_t)(cEdges),
				C.int(len(edges)),
			),
		},
	}
	runtime.SetFinalizer(wr.inner, (*innerWire).free)
	return wr
}

func TopoMakeWireFromWires(wires []Wire) *Wire {
	if len(wires) == 0 {
		return &Wire{inner: &innerWire{}}
	}

	// 分配C内存
	cWires := C.malloc(C.size_t(len(wires)) * C.size_t(unsafe.Sizeof(C.struct__topo_wire_t{})))
	defer C.free(cWires)

	// 填充数据
	wiresPtr := (*[1<<30 - 1]C.struct__topo_wire_t)(cWires)
	for i := range wires {
		wiresPtr[i] = wires[i].inner.val
	}

	wr := &Wire{
		inner: &innerWire{
			val: C.topo_make_wire_from_wries(
				(*C.struct__topo_wire_t)(cWires),
				C.int(len(wires)),
			),
		},
	}
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
	if len(wires) == 0 {
		return nil
	}

	// 分配C内存
	cWires := C.malloc(C.size_t(len(wires)) * C.size_t(unsafe.Sizeof(C.struct__topo_wire_t{})))
	defer C.free(cWires)

	// 填充数据
	wiresPtr := (*[1<<30 - 1]C.struct__topo_wire_t)(cWires)
	for i := range wires {
		wiresPtr[i] = wires[i].inner.val
	}

	var count C.int
	cResult := C.topo_make_wire_from_combine(
		(*C.struct__topo_wire_t)(cWires),
		C.int(len(wires)),
		C.double(tol),
		&count,
	)
	if cResult == nil {
		return nil
	}
	defer C.topo_wire_list_free(cResult, count)

	// 转换结果
	result := make([]*Wire, count)
	resultPtr := (*[1<<30 - 1]C.struct__topo_wire_t)(unsafe.Pointer(cResult))
	for i := range result {
		result[i] = &Wire{inner: &innerWire{val: resultPtr[i]}}
		runtime.SetFinalizer(result[i].inner, (*innerWire).free)
	}

	return result
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
	if curveCount == 0 || curveCount != len(curveTypes) {
		return &Wire{inner: &innerWire{}}
	}

	// 分配C内存来存储曲线指针数组
	cPointsArray := C.malloc(C.size_t(curveCount) * C.size_t(unsafe.Sizeof(unsafe.Pointer(nil))))
	defer C.free(cPointsArray)

	// 分配C内存来存储每个曲线的点数据
	cPointCounts := make([]C.int, curveCount)
	for i, pts := range points {
		pointCount := len(pts)
		if pointCount == 0 {
			return &Wire{inner: &innerWire{}}
		}
		cPointCounts[i] = C.int(pointCount)

		// 为当前曲线分配点数组内存
		curvePoints := C.malloc(C.size_t(pointCount) * C.size_t(unsafe.Sizeof(C.pnt3d_t{})))
		defer C.free(curvePoints) // 注意：这里不能立即释放，需要在C函数中使用完后释放

		// 将点数据复制到C内存
		pointsPtr := (*[1<<30 - 1]C.pnt3d_t)(curvePoints)
		for j := 0; j < pointCount; j++ {
			pointsPtr[j] = pts[j].val
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
