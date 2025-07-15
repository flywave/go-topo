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

func (t *Face) ToPlane() *TopoPlane {
	p := &TopoPlane{inner: &innerTopoPlane{val: C.topo_face_to_plane(t.inner.val)}}
	runtime.SetFinalizer(p.inner, (*innerTopoPlane).free)
	return p
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
	// 分配C内存来存储形状指针
	cshp := C.malloc(C.size_t(len(profiles)) * C.size_t(unsafe.Sizeof(uintptr(0))))
	defer C.free(cshp)

	// 转换为C指针数组
	cshpArray := (*[1<<30 - 1]*C.struct__topo_shape_t)(cshp)
	for i := range profiles {
		cshpArray[i] = profiles[i].inner.val
	}

	return int(C.topo_face_sweep(s.inner.val, spine.inner.val,
		(**C.struct__topo_shape_t)(cshp), C.int(len(profiles)), C.int(cornerMode)))
}

func (s *Face) SweepWire(spine *Wire, profiles []Wire, cornerMode int) int {
	if len(profiles) == 0 {
		return int(C.topo_face_sweep_wire(s.inner.val, spine.inner.val, nil, 0, C.int(cornerMode)))
	}

	cArray := C.malloc(C.size_t(len(profiles)) * C.size_t(unsafe.Sizeof(C.struct__topo_wire_t{})))
	defer C.free(cArray)

	cArrayPtr := (*[1<<30 - 1]C.struct__topo_wire_t)(cArray)
	for i := range profiles {
		cArrayPtr[i] = profiles[i].inner.val
	}

	return int(C.topo_face_sweep_wire(
		s.inner.val,
		spine.inner.val,
		(*C.struct__topo_wire_t)(cArray),
		C.int(len(profiles)),
		C.int(cornerMode),
	))
}

func (t *Face) Loft(profiles []Shape, ruled bool, tolerance float64) int {
	// 分配C内存
	cshp := C.malloc(C.size_t(len(profiles)) * C.size_t(unsafe.Sizeof(uintptr(0))))
	defer C.free(cshp)

	// 转换为C指针数组
	cshpArray := (*[1<<30 - 1]*C.struct__topo_shape_t)(cshp)
	for i := range profiles {
		cshpArray[i] = profiles[i].inner.val
	}

	return int(C.topo_face_loft(t.inner.val, (**C.struct__topo_shape_t)(cshp),
		C.int(len(profiles)), C.bool(ruled), C.double(tolerance)))
}

func (t *Face) Boolean(tool *Face, op int) int {
	return int(C.topo_face_boolean(t.inner.val, tool.inner.val, C.int(op)))
}

func (f *Face) UVBounds() (uMin, uMax, vMin, vMax float64) {
	C.topo_face_uv_bounds(f.inner.val, (*C.double)(&uMin), (*C.double)(&uMax),
		(*C.double)(&vMin), (*C.double)(&vMax))
	return
}

func (f *Face) ParamAt(pt Point3) (u, v float64) {
	C.topo_face_param_at(f.inner.val, pt.val, (*C.double)(&u), (*C.double)(&v))
	return
}

func (f *Face) Params(pts []Point3, tol float64) ([]float64, []float64) {
	if len(pts) == 0 {
		return nil, nil
	}

	// 分配C内存存储点数据
	cPoints := C.malloc(C.size_t(len(pts)) * C.size_t(unsafe.Sizeof(C.pnt3d_t{})))
	defer C.free(cPoints)

	// 填充C数组
	cPointsPtr := (*[1<<30 - 1]C.pnt3d_t)(cPoints)
	for i := range pts {
		cPointsPtr[i] = pts[i].val
	}

	// 分配Go切片用于返回结果
	us := make([]float64, len(pts))
	vs := make([]float64, len(pts))

	C.topo_face_params(
		f.inner.val,
		(*C.pnt3d_t)(cPoints),
		C.int(len(pts)),
		(*C.double)(&us[0]),
		(*C.double)(&vs[0]),
		C.double(tol),
	)
	return us, vs
}

func (f *Face) PositionAt(u, v float64) Point3 {
	return Point3{val: C.topo_face_position_at(f.inner.val, C.double(u), C.double(v))}
}

func (f *Face) Positions(us, vs []float64) []Point3 {
	if len(us) == 0 || len(vs) == 0 || len(us) != len(vs) {
		return nil
	}

	count := len(us)

	// 分配C内存存储u/v参数
	cUs := C.malloc(C.size_t(count) * C.size_t(unsafe.Sizeof(C.double(0))))
	defer C.free(cUs)
	cVs := C.malloc(C.size_t(count) * C.size_t(unsafe.Sizeof(C.double(0))))
	defer C.free(cVs)

	// 填充u/v数组
	cUsPtr := (*[1<<30 - 1]C.double)(cUs)
	cVsPtr := (*[1<<30 - 1]C.double)(cVs)
	for i := 0; i < count; i++ {
		cUsPtr[i] = C.double(us[i])
		cVsPtr[i] = C.double(vs[i])
	}

	// 分配C内存存储结果点
	cPoints := C.malloc(C.size_t(count) * C.size_t(unsafe.Sizeof(C.pnt3d_t{})))
	defer C.free(cPoints)

	C.topo_face_positions(
		f.inner.val,
		(*C.double)(cUs),
		(*C.double)(cVs),
		C.int(count),
		(*C.pnt3d_t)(cPoints),
	)

	// 转换结果到Go切片
	points := make([]Point3, count)
	cPointsPtr := (*[1<<30 - 1]C.pnt3d_t)(cPoints)
	for i := 0; i < count; i++ {
		points[i] = Point3{val: cPointsPtr[i]}
	}

	return points
}

func (f *Face) NormalAt(location Point3) Vector3 {
	return Vector3{val: C.topo_face_normal_at(f.inner.val, &location.val)}
}

func (f *Face) NormalAtUV(u, v float64) (Vector3, Point3) {
	var normal C.vec3d_t
	var point C.pnt3d_t
	C.topo_face_normal_at_uv(f.inner.val, C.double(u), C.double(v), &normal, &point)
	return Vector3{val: normal}, Point3{val: point}
}

func (f *Face) Normals(us, vs []float64) ([]Vector3, []Point3) {
	if len(us) == 0 || len(vs) == 0 || len(us) != len(vs) {
		return nil, nil
	}

	count := len(us)

	// 分配C内存存储u/v参数
	cUs := C.malloc(C.size_t(count) * C.size_t(unsafe.Sizeof(C.double(0))))
	defer C.free(cUs)
	cVs := C.malloc(C.size_t(count) * C.size_t(unsafe.Sizeof(C.double(0))))
	defer C.free(cVs)

	// 填充u/v数组
	cUsPtr := (*[1<<30 - 1]C.double)(cUs)
	cVsPtr := (*[1<<30 - 1]C.double)(cVs)
	for i := 0; i < count; i++ {
		cUsPtr[i] = C.double(us[i])
		cVsPtr[i] = C.double(vs[i])
	}

	// 分配C内存存储结果
	cNormals := C.malloc(C.size_t(count) * C.size_t(unsafe.Sizeof(C.vec3d_t{})))
	defer C.free(cNormals)
	cPoints := C.malloc(C.size_t(count) * C.size_t(unsafe.Sizeof(C.pnt3d_t{})))
	defer C.free(cPoints)

	C.topo_face_normals(
		f.inner.val,
		(*C.double)(cUs),
		(*C.double)(cVs),
		C.int(count),
		(*C.vec3d_t)(cNormals),
		(*C.pnt3d_t)(cPoints),
	)

	// 转换结果到Go切片
	normals := make([]Vector3, count)
	points := make([]Point3, count)
	cNormalsPtr := (*[1<<30 - 1]C.vec3d_t)(cNormals)
	cPointsPtr := (*[1<<30 - 1]C.pnt3d_t)(cPoints)
	for i := 0; i < count; i++ {
		normals[i] = Vector3{val: cNormalsPtr[i]}
		points[i] = Point3{val: cPointsPtr[i]}
	}

	return normals, points
}

func (f *Face) Fillet2D(radius float64, vertices []*Vertex) *Face {
	if len(vertices) == 0 {
		return &Face{inner: &innerFace{val: C.topo_face_fillet2d(f.inner.val, C.double(radius), nil, 0)}}
	}

	cVertices := C.malloc(C.size_t(len(vertices)) * C.size_t(unsafe.Sizeof(C.struct__topo_vertex_t{})))
	defer C.free(cVertices)

	cVerticesPtr := (*[1<<30 - 1]C.struct__topo_vertex_t)(cVertices)
	for i, v := range vertices {
		cVerticesPtr[i] = v.inner.val
	}

	p := &Face{inner: &innerFace{val: C.topo_face_fillet2d(
		f.inner.val,
		C.double(radius),
		(*C.struct__topo_vertex_t)(cVertices),
		C.int(len(vertices))),
	}}
	runtime.SetFinalizer(p.inner, (*innerFace).free)
	return p
}

func (f *Face) Chamfer2D(distance float64, vertices []*Vertex) *Face {
	if len(vertices) == 0 {
		return &Face{inner: &innerFace{val: C.topo_face_chamfer2d(f.inner.val, C.double(distance), nil, 0)}}
	}

	cVertices := C.malloc(C.size_t(len(vertices)) * C.size_t(unsafe.Sizeof(C.struct__topo_vertex_t{})))
	defer C.free(cVertices)

	cVerticesPtr := (*[1<<30 - 1]C.struct__topo_vertex_t)(cVertices)
	for i, v := range vertices {
		cVerticesPtr[i] = v.inner.val
	}

	p := &Face{inner: &innerFace{val: C.topo_face_chamfer2d(
		f.inner.val,
		C.double(distance),
		(*C.struct__topo_vertex_t)(cVertices),
		C.int(len(vertices))),
	}}
	runtime.SetFinalizer(p.inner, (*innerFace).free)
	return p
}

func (f *Face) Thicken(thickness float64) *Solid {
	p := &Solid{inner: &innerSolid{val: C.topo_face_thicken(f.inner.val, C.double(thickness))}}
	runtime.SetFinalizer(p.inner, (*innerSolid).free)
	return p
}

func (f *Face) Project(other *Face, direction Vector3) *Face {
	p := &Face{inner: &innerFace{val: C.topo_face_project(f.inner.val,
		other.inner.val, direction.val)}}
	runtime.SetFinalizer(p.inner, (*innerFace).free)
	return p
}

func (f *Face) ToArcs(tolerance float64) *Face {
	p := &Face{inner: &innerFace{val: C.topo_face_to_arcs(f.inner.val, C.double(tolerance))}}
	runtime.SetFinalizer(p.inner, (*innerFace).free)
	return p
}

func (f *Face) Trim(u0, u1, v0, v1, tol float64) *Face {
	p := &Face{inner: &innerFace{val: C.topo_face_trim(f.inner.val,
		C.double(u0), C.double(u1), C.double(v0), C.double(v1), C.double(tol))}}
	runtime.SetFinalizer(p.inner, (*innerFace).free)
	return p
}

func (f *Face) Isoline(param float64, direction string) *Edge {
	cDir := C.CString(direction)
	defer C.free(unsafe.Pointer(cDir))
	p := &Edge{inner: &innerEdge{val: C.topo_face_isoline(f.inner.val,
		C.double(param), cDir)}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func (f *Face) Isolines(params []float64, direction string) []*Edge {
	count := len(params)
	cParams := make([]float64, count)
	copy(cParams, params)
	cDir := C.CString(direction)
	defer C.free(unsafe.Pointer(cDir))

	var resultCount C.int
	edges := C.topo_face_isolines(f.inner.val, (*C.double)(&cParams[0]),
		C.int(count), cDir, &resultCount)
	if edges == nil {
		return nil
	}
	defer C.free(unsafe.Pointer(edges))

	edgeSlice := (*[1 << 30]C.struct__topo_edge_t)(unsafe.Pointer(edges))[:resultCount:resultCount]
	result := make([]*Edge, resultCount)

	for i := range edgeSlice {
		result[i] = &Edge{inner: &innerEdge{val: edgeSlice[i]}}
		runtime.SetFinalizer(result[i].inner, (*innerEdge).free)
	}

	return result
}

func (f *Face) OuterWire() *Wire {
	p := &Wire{inner: &innerWire{val: C.topo_face_outer_wire(f.inner.val)}}
	runtime.SetFinalizer(p.inner, (*innerWire).free)
	return p
}

func (f *Face) InnerWires() []*Wire {
	var count C.int
	wires := C.topo_face_inner_wires(f.inner.val, &count)
	if wires == nil {
		return nil
	}
	defer C.free(unsafe.Pointer(wires))

	wireSlice := (*[1 << 30]C.struct__topo_wire_t)(unsafe.Pointer(wires))[:count:count]
	result := make([]*Wire, count)

	for i := range wireSlice {
		result[i] = &Wire{inner: &innerWire{val: wireSlice[i]}}
		runtime.SetFinalizer(result[i].inner, (*innerWire).free)
	}

	return result
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
	if len(ws) == 0 {
		return &Face{inner: &innerFace{val: C.topo_face_make_face_from_wire(nil, 0)}}
	}

	cArray := C.malloc(C.size_t(len(ws)) * C.size_t(unsafe.Sizeof(C.struct__topo_wire_t{})))
	defer C.free(cArray)

	cArrayPtr := (*[1<<30 - 1]C.struct__topo_wire_t)(cArray)
	for i := range ws {
		cArrayPtr[i] = ws[i].inner.val
	}

	p := &Face{inner: &innerFace{val: C.topo_face_make_face_from_wire(
		(*C.struct__topo_wire_t)(cArray),
		C.int(len(ws)),
	)}}
	runtime.SetFinalizer(p.inner, (*innerFace).free)
	return p
}

func TopoMakeFaceFromEdges(ws []Edge, pts []Point3) *Face {
	if len(ws) == 0 || len(pts) == 0 {
		return &Face{inner: &innerFace{val: C.topo_face_make_face_from_egdes(nil, 0, nil, 0)}}
	}

	// 分配并填充edges数组
	cEdges := C.malloc(C.size_t(len(ws)) * C.size_t(unsafe.Sizeof(C.struct__topo_edge_t{})))
	defer C.free(cEdges)
	cEdgesPtr := (*[1<<30 - 1]C.struct__topo_edge_t)(cEdges)
	for i := range ws {
		cEdgesPtr[i] = ws[i].inner.val
	}

	// 分配并填充points数组
	cPoints := C.malloc(C.size_t(len(pts)) * C.size_t(unsafe.Sizeof(C.pnt3d_t{})))
	defer C.free(cPoints)
	cPointsPtr := (*[1<<30 - 1]C.pnt3d_t)(cPoints)
	for i := range pts {
		cPointsPtr[i] = pts[i].val
	}

	p := &Face{inner: &innerFace{val: C.topo_face_make_face_from_egdes(
		(*C.struct__topo_edge_t)(cEdges),
		C.int(len(ws)),
		(*C.pnt3d_t)(cPoints),
		C.int(len(pts)),
	)}}
	runtime.SetFinalizer(p.inner, (*innerFace).free)
	return p
}

func TopoMakeFaceFromPoints(pts []Point3) *Face {
	if len(pts) == 0 {
		return &Face{inner: &innerFace{val: C.topo_face_make_face_from_points(nil, 0)}}
	}

	cArray := C.malloc(C.size_t(len(pts)) * C.size_t(unsafe.Sizeof(C.pnt3d_t{})))
	defer C.free(cArray)

	cArrayPtr := (*[1<<30 - 1]C.pnt3d_t)(cArray)
	for i := range pts {
		cArrayPtr[i] = pts[i].val
	}

	p := &Face{inner: &innerFace{val: C.topo_face_make_face_from_points(
		(*C.pnt3d_t)(cArray),
		C.int(len(pts)),
	)}}
	runtime.SetFinalizer(p.inner, (*innerFace).free)
	return p
}

func TopoMakeFaceFromOuterAndInners(outer *Wire, inners []*Wire) []*Face {
	innerCount := len(inners)
	var cInners unsafe.Pointer

	if innerCount > 0 {
		cInners = C.malloc(C.size_t(innerCount) * C.size_t(unsafe.Sizeof(C.struct__topo_wire_t{})))
		defer C.free(cInners)

		cInnersArray := (*[1<<30 - 1]C.struct__topo_wire_t)(cInners)
		for i, w := range inners {
			cInnersArray[i] = w.inner.val
		}
	}

	var resultCount C.int
	cFace := C.topo_face_make_from_wires(outer.inner.val,
		(*C.struct__topo_wire_t)(cInners),
		C.int(innerCount),
		&resultCount)

	defer C.topo_face_list_free(cFace, resultCount)

	cfaceSlice := (*[1 << 30]C.struct__topo_face_t)(unsafe.Pointer(cFace))[:resultCount:resultCount]
	faces := make([]*Face, int(resultCount))

	for i := 0; i < int(resultCount); i++ {
		faces[i] = &Face{inner: &innerFace{val: cfaceSlice[i]}}
		runtime.SetFinalizer(faces[i].inner, (*innerFace).free)
	}

	return faces
}

func TopoMakeComplexFace(edges []*Shape, constraints []*Shape, continuity, degree int,
	nbPtsOnCurve, nbIter int, anisotropy bool, tol2d, tol3d, tolAngle, tolCurv float64,
	maxDegree, maxSegments int) *Face {

	// 处理edges
	edgeCount := len(edges)
	cEdges := C.malloc(C.size_t(edgeCount) * C.size_t(unsafe.Sizeof(uintptr(0))))
	defer C.free(cEdges)
	cEdgesArray := (*[1<<30 - 1]*C.struct__topo_shape_t)(cEdges)
	for i, e := range edges {
		cEdgesArray[i] = e.inner.val
	}

	// 处理constraints
	constraintCount := len(constraints)
	cConstraints := C.malloc(C.size_t(constraintCount) * C.size_t(unsafe.Sizeof(uintptr(0))))
	defer C.free(cConstraints)
	cConstraintsArray := (*[1<<30 - 1]*C.struct__topo_shape_t)(cConstraints)
	for i, c := range constraints {
		cConstraintsArray[i] = c.inner.val
	}

	p := &Face{inner: &innerFace{val: C.topo_face_make_complex(
		(**C.struct__topo_shape_t)(cEdges), C.int(edgeCount),
		(**C.struct__topo_shape_t)(cConstraints), C.int(constraintCount),
		C.int(continuity), C.int(degree), C.int(nbPtsOnCurve), C.int(nbIter),
		C.bool(anisotropy), C.double(tol2d), C.double(tol3d),
		C.double(tolAngle), C.double(tolCurv), C.int(maxDegree),
		C.int(maxSegments))}}
	runtime.SetFinalizer(p.inner, (*innerFace).free)
	return p
}
func TopoMakePlaneFace(basePoint Point3, direction Dir3, length, width float64) *Face {
	p := &Face{inner: &innerFace{val: C.topo_face_make_plane(
		basePoint.val, direction.val, (*C.double)(&length), (*C.double)(&width))}}
	runtime.SetFinalizer(p.inner, (*innerFace).free)
	return p
}

func TopoMakeSplineApproxFace(points [][]Point3, tol float64, smoothing []float64,
	minDegree, maxDegree int) *Face {

	pointArraySize := len(points)
	if pointArraySize == 0 {
		return &Face{inner: &innerFace{val: C.topo_face_make_spline_approx(nil, nil, 0, C.double(tol), nil, C.int(minDegree), C.int(maxDegree))}}
	}

	// 计算总点数并填充pointCounts数组
	pointCounts := make([]C.int, pointArraySize)
	totalPoints := 0
	for i, pts := range points {
		pointCounts[i] = C.int(len(pts))
		totalPoints += len(pts)
	}

	// 分配并填充pointCounts到C数组
	cPointCounts := C.malloc(C.size_t(pointArraySize) * C.size_t(unsafe.Sizeof(C.int(0))))
	defer C.free(cPointCounts)
	cPointCountsPtr := (*[1<<30 - 1]C.int)(cPointCounts)
	for i := range pointCounts {
		cPointCountsPtr[i] = pointCounts[i]
	}

	// 分配并填充所有点到C数组
	cPoints := C.malloc(C.size_t(totalPoints) * C.size_t(unsafe.Sizeof(C.pnt3d_t{})))
	defer C.free(cPoints)
	cPointsPtr := (*[1<<30 - 1]C.pnt3d_t)(cPoints)
	index := 0
	for _, pts := range points {
		for _, pt := range pts {
			cPointsPtr[index] = pt.val
			index++
		}
	}

	// 处理smoothing参数
	var cSmoothing *C.double
	if len(smoothing) > 0 {
		cSmoothing = (*C.double)(&smoothing[0])
	}

	p := &Face{inner: &innerFace{val: C.topo_face_make_spline_approx(
		(*C.pnt3d_t)(cPoints),
		(*C.int)(cPointCounts),
		C.int(pointArraySize),
		C.double(tol),
		cSmoothing,
		C.int(minDegree),
		C.int(maxDegree)),
	}}
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
