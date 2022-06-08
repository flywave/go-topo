package topo

/*
#include <stdlib.h>
#include "topo_c_api.h"
#cgo CFLAGS: -I  ./libs
#cgo linux CXXFLAGS: -I ./libs  -std=gnu++14
#cgo darwin CXXFLAGS: -I ./libs  -std=gnu++14
#cgo darwin,arm CXXFLAGS: -I ./libs  -std=gnu++14
#cgo windows CXXFLAGS: -I ./libs  -std=gnu++14
#cgo linux LDFLAGS: -L ./libs/linux -Wl,--start-group -ltopo -lpthread  -lifc23 -lifc4 -lifc41 -lifc42 -lifc43_rc1 -lstdc++ -ldl -lm -lGL -lGLU -lX11  -lTKernel -lTKMath -lTKG2d -lTKG3d -lTKGeomBase -lTKBRep -lTKGeomAlgo -lTKTopAlgo -lTKPrim -lTKBO -lTKHLR -lTKMesh -lTKShHealing -lTKXMesh -lTKBool -lTKFillet -lTKFeat -lTKOffset -lTKService -lTKV3d -lTKCDF -lPTKernel -lTKLCAF -lFWOSPlugin -lTKPShape -lTKBinL -lTKXmlL -lTKPLCAF -lTKTObj -lTKShapeSchema -lTKStdLSchema -lTKCAF -lTKBin -lTKXml -lTKPCAF -lTKBinTObj -lTKXmlTObj -lTKStdSchema -lTKSTL -lTKXSBase -lTKSTEPBase -lTKIGES -lTKSTEPAttr -lTKSTEP209 -lTKSTEP -lTKVRML -lTKXCAF -lTKXCAFSchema -lTKXmlXCAF -lTKBinXCAF -lTKXDEIGES -lTKXDESTEP -lboost_system_internal -lboost_filesystem_internal -lboost_date_time_internal -lboost_regex_internal -lboost_chrono_internal -lboost_program_options_internal -lboost_test_internal -Wl,--end-group
#cgo darwin LDFLAGS: -L /usr/lib -lc++ -L ./libs/darwin  -ltopo  -lifc23 -lifc4 -lifc41 -lifc42 -lifc43_rc1 -lboost_system_internal -lboost_filesystem_internal -lboost_date_time_internal -lboost_regex_internal -lboost_chrono_internal -lboost_program_options_internal -lboost_test_internal -framework Foundation -framework CoreFoundation -framework CoreGraphics -framework Cocoa  -lTKernel -lTKMath -lTKG2d -lTKG3d -lTKGeomBase -lTKBRep -lTKGeomAlgo -lTKTopAlgo -lTKPrim -lTKBO -lTKHLR -lTKMesh -lTKShHealing -lTKXMesh -lTKBool -lTKFillet -lTKFeat -lTKOffset -lTKService -lTKV3d -lTKCDF -lPTKernel -lTKLCAF -lFWOSPlugin -lTKPShape -lTKBinL -lTKXmlL -lTKPLCAF -lTKTObj -lTKShapeSchema -lTKStdLSchema -lTKCAF -lTKBin -lTKXml -lTKPCAF -lTKBinTObj -lTKXmlTObj -lTKStdSchema -lTKSTL -lTKXSBase -lTKSTEPBase -lTKIGES -lTKSTEPAttr -lTKSTEP209 -lTKSTEP -lTKVRML -lTKXCAF -lTKXCAFSchema -lTKXmlXCAF -lTKBinXCAF -lTKXDEIGES -lTKXDESTEP
#cgo darwin,arm LDFLAGS: -L /usr/lib -lc++ -L ./libs/darwin_arm  -ltopo -lifc23 -lifc4 -lifc41 -lifc42 -lifc43_rc1  -lboost_system_internal -lboost_filesystem_internal -lboost_date_time_internal -lboost_regex_internal -lboost_chrono_internal -lboost_program_options_internal -lboost_test_internal -framework Foundation -framework CoreFoundation -framework CoreGraphics -framework Cocoa  -lTKernel -lTKMath -lTKG2d -lTKG3d -lTKGeomBase -lTKBRep -lTKGeomAlgo -lTKTopAlgo -lTKPrim -lTKBO -lTKHLR -lTKMesh -lTKShHealing -lTKXMesh -lTKBool -lTKFillet -lTKFeat -lTKOffset -lTKService -lTKV3d -lTKCDF -lPTKernel -lTKLCAF -lFWOSPlugin -lTKPShape -lTKBinL -lTKXmlL -lTKPLCAF -lTKTObj -lTKShapeSchema -lTKStdLSchema -lTKCAF -lTKBin -lTKXml -lTKPCAF -lTKBinTObj -lTKXmlTObj -lTKStdSchema -lTKSTL -lTKXSBase -lTKSTEPBase -lTKIGES -lTKSTEPAttr -lTKSTEP209 -lTKSTEP -lTKVRML -lTKXCAF -lTKXCAFSchema -lTKXmlXCAF -lTKBinXCAF -lTKXDEIGES -lTKXDESTEP
#cgo windows LDFLAGS: -L ./libs/windows  -ltopo -lifc23 -lifc4 -lifc41 -lifc42 -lifc43_rc1 -lboost_system_internal -lboost_filesystem_internal -lboost_date_time_internal -lboost_regex_internal -lboost_chrono_internal -lboost_program_options_internal -lboost_test_internal  -lTKernel -lTKMath -lTKG2d -lTKG3d -lTKGeomBase -lTKBRep -lTKGeomAlgo -lTKTopAlgo -lTKPrim -lTKBO -lTKHLR -lTKMesh -lTKShHealing -lTKXMesh -lTKBool -lTKFillet -lTKFeat -lTKOffset -lTKService -lTKV3d -lTKCDF -lPTKernel -lTKLCAF -lFWOSPlugin -lTKPShape -lTKBinL -lTKXmlL -lTKPLCAF -lTKTObj -lTKShapeSchema -lTKStdLSchema -lTKCAF -lTKBin -lTKXml -lTKPCAF -lTKBinTObj -lTKXmlTObj -lTKStdSchema -lTKSTL -lTKXSBase -lTKSTEPBase -lTKIGES -lTKSTEPAttr -lTKSTEP209 -lTKSTEP -lTKVRML -lTKXCAF -lTKXCAFSchema -lTKXmlXCAF -lTKBinXCAF -lTKXDEIGES -lTKXDESTEP
*/
import "C"

import (
	"runtime"
	"unsafe"
)

const (
	FUSE   = int(C.BOOLFUSE)
	CUT    = int(C.BOOLCUT)
	COMMON = int(C.BOOLCOMMON)
)

const (
	WEST  = int(C.DIR_WEST)
	EAST  = int(C.DIR_EAST)
	NORTH = int(C.DIR_NORTH)
	SOUTH = int(C.DIR_SOUTH)
	UP    = int(C.DIR_UP)
	DOWN  = int(C.DIR_DOWN)
)

const (
	TopoSolid     = int(C.TopoSolid)
	TopoShell     = int(C.TopoShell)
	TopoFace      = int(C.TopoFace)
	TopoEdge      = int(C.TopoEdge)
	TopoVertex    = int(C.TopoVertex)
	TopoWire      = int(C.TopoWire)
	TopoCompound  = int(C.TopoCompound)
	TopoCompSolid = int(C.TopoCompSolid)
	TopoShape     = int(C.TopoShape)
)

const (
	FORWARD  = int(C.ORI_FORWARD)
	REVERSED = int(C.ORI_REVERSED)
	INTERNAL = int(C.ORI_INTERNAL)
	EXTERNAL = int(C.ORI_EXTERNAL)
	UNKNOW   = int(C.ORI_UNKNOW)
)

type MeshReceiver struct {
	inner *innerMeshReceiver
	index int
	Faces []Color
	Vers  [][]Point3
	Norms [][]Point3
	UVs   [][]Point2
	Tris  [][][3]int
}

type innerMeshReceiver struct {
	val *C.struct__topo_mesh_receiver_t
}

func NewMeshReceiver() *MeshReceiver {
	ret := &MeshReceiver{inner: nil, index: -1}
	var cb C.struct__mesh_receiver_cb_t
	cb.ctx = unsafe.Pointer(ret)
	ret.inner = &innerMeshReceiver{C.topo_mesh_receiver_new(cb)}
	runtime.SetFinalizer(ret, (*MeshReceiver).free)
	return ret
}

func (m *MeshReceiver) begin() {
	m.Faces = append(m.Faces, Color{})
	m.Vers = append(m.Vers, []Point3{})
	m.Norms = append(m.Norms, []Point3{})
	m.UVs = append(m.UVs, []Point2{})
	m.Tris = append(m.Tris, [][3]int{})
	m.index++
}

func (m *MeshReceiver) end() {

}

func (m *MeshReceiver) appendFace(c Color) int {
	return m.index
}

func (m *MeshReceiver) appendNodeNorm(f int, p, n Point3) {
	m.Vers[f] = append(m.Vers[f], p)
	m.Norms[f] = append(m.Norms[f], n)
}

func (m *MeshReceiver) appendNodeNormUv(f int, p, n Point3, uv Point2) {
	m.Vers[f] = append(m.Vers[f], p)
	m.Norms[f] = append(m.Norms[f], n)
	m.UVs[f] = append(m.UVs[f], uv)
}

func (m *MeshReceiver) appendNode(f int, p Point3) {
	m.Vers[f] = append(m.Vers[f], p)
}

func (m *MeshReceiver) appendTriangle(f int, tri [3]int) {
	m.Tris[f] = append(m.Tris[f], tri)
}

func (m *MeshReceiver) free() {
	C.topo_mesh_receiver_free(m.inner.val)
	m.inner.val = nil
}

type Location struct {
	inner *innerLocation
}

type innerLocation struct {
	val *C.struct__topo_location_t
}

func NewLocation(t Trsf) *Location {
	p := &Location{inner: &innerLocation{val: C.topo_location_new(t.val)}}
	runtime.SetFinalizer(p, (*Location).free)
	return p
}

func (l *Location) Trsf() Trsf {
	return Trsf{val: C.topo_location_get_trsf(l.inner.val)}
}

func (l *Location) free() {
	C.topo_location_free(l.inner.val)
	l.inner.val = nil
}

type Shape struct {
	inner *innerShape
}

type innerShape struct {
	val *C.struct__topo_shape_t
}

func NewShape(v *C.struct__topo_shape_t) *Shape {
	s := &Shape{inner: &innerShape{val: v}}
	runtime.SetFinalizer(s, (*Shape).free)
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
	return &Shape{inner: &innerShape{val: C.topo_shape_transformed(s.inner.val, t.val)}}
}

func (s *Shape) Translated(v Vector3) *Shape {
	return &Shape{inner: &innerShape{val: C.topo_shape_translated(s.inner.val, v.val)}}
}

func (s *Shape) RotatedFromPoint(angle float64, p1, p2 Point3) *Shape {
	return &Shape{inner: &innerShape{val: C.topo_shape_rotated_from_two_point(s.inner.val, C.double(angle), p1.val, p2.val)}}
}

func (s *Shape) RotatedFromAxis1(angle float64, a Axis1) *Shape {
	return &Shape{inner: &innerShape{val: C.topo_shape_rotated_from_axis1(s.inner.val, C.double(angle), a.val)}}
}

func (s *Shape) RotatedFromQuaternion(q Quaternion) *Shape {
	return &Shape{inner: &innerShape{val: C.topo_shape_rotated_from_quaternion(s.inner.val, q.val)}}
}

func (s *Shape) Scaled(angle float64, a Point3) *Shape {
	return &Shape{inner: &innerShape{val: C.topo_shape_scaled(s.inner.val, C.double(angle), a.val)}}
}

func (s *Shape) MirroredFromPointNorm(pnt, ner Point3) *Shape {
	return &Shape{inner: &innerShape{val: C.topo_shape_mirrored_from_point_norm(s.inner.val, pnt.val, ner.val)}}
}

func (s *Shape) MirroredFromAxis1(a Axis1) *Shape {
	return &Shape{inner: &innerShape{val: C.topo_shape_mirrored_from_axis1(s.inner.val, a.val)}}
}

func (s *Shape) MirroredFromAxis2(a Axis2) *Shape {
	return &Shape{inner: &innerShape{val: C.topo_shape_mirrored_from_axis2(s.inner.val, a.val)}}
}

func (s *Shape) GetOrientation() int {
	return int(C.topo_shape_get_orientation(s.inner.val))
}

func (s *Shape) SetOrientation(t int) {
	C.topo_shape_set_orientation(s.inner.val, C.int(t))
}

func (s *Shape) GetLocation() *Location {
	return &Location{inner: &innerLocation{val: C.topo_shape_get_location(s.inner.val)}}
}

func (s *Shape) SetLocation(t *Location) {
	C.topo_shape_set_location(s.inner.val, t.inner.val)
}

func (s *Shape) FixShape() bool {
	return bool(C.topo_shape_fix_shape(s.inner.val))
}

func (s *Shape) Copy() *Shape {
	return &Shape{inner: &innerShape{val: C.topo_shape_copy(s.inner.val)}}
}

func (s *Shape) Share() *Shape {
	return &Shape{inner: &innerShape{val: C.topo_shape_share(s.inner.val)}}
}

func (s *Shape) Mesh(m *MeshReceiver, tolerance, deflection, angle float64) int8 {
	return int8(C.topo_shape_mesh(s.inner.val, m.inner.val, C.double(tolerance), C.double(deflection), C.double(angle)))
}

func (s *Shape) SetSurfaceColour(c Color) {
	C.topo_shape_set_surface_colour(s.inner.val, c.val)
}

func (s *Shape) SetCurveColour(c Color) {
	C.topo_shape_set_curve_colour(s.inner.val, c.val)
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

func (t *Shape) free() {
	C.topo_shape_free(t.inner.val)
	t.inner.val = nil
}

func (t *Shape) AutoCast() interface{} {
	switch t.Type() {
	case TopoSolid:
		var val C.struct__topo_solid_t
		val.shp = C.topo_shape_share(t.inner.val)
		return &Solid{inner: &innerSolid{val: val}}
	case TopoShell:
		var val C.struct__topo_shell_t
		val.shp = C.topo_shape_share(t.inner.val)
		return &Shell{inner: &innerShell{val: val}}
	case TopoFace:
		var val C.struct__topo_face_t
		val.shp = C.topo_shape_share(t.inner.val)
		return &Face{inner: &innerFace{val: val}}
	case TopoEdge:
		var val C.struct__topo_edge_t
		val.shp = C.topo_shape_share(t.inner.val)
		return &Edge{inner: &innerEdge{val: val}}
	case TopoVertex:
		var val C.struct__topo_vertex_t
		val.shp = C.topo_shape_share(t.inner.val)
		return &Vertex{inner: &innerVertex{val: val}}
	case TopoWire:
		var val C.struct__topo_wire_t
		val.shp = C.topo_shape_share(t.inner.val)
		return &Wire{inner: &innerWire{val: val}}
	case TopoCompound:
		var val C.struct__topo_compound_t
		val.shp = C.topo_shape_share(t.inner.val)
		return &Compound{inner: &innerCompound{val: val}}
	case TopoCompSolid:
		var val C.struct__topo_comp_solid_t
		val.shp = C.topo_shape_share(t.inner.val)
		return &CompSolid{inner: &innerCompSolid{val: val}}
	case TopoShape:
		return &Shape{inner: &innerShape{val: C.topo_shape_share(t.inner.val)}}
	}
	return nil
}

type CompSolid struct {
	inner *innerCompSolid
}

type innerCompSolid struct {
	val C.struct__topo_comp_solid_t
}

func TopoMakeCompSolid() *CompSolid {
	p := &CompSolid{inner: &innerCompSolid{val: C.topo_make_comp_solid()}}
	runtime.SetFinalizer(p, (*CompSolid).free)
	return p
}

func (s *CompSolid) IsNull() bool {
	return bool(C.topo_shape_is_null(s.inner.val.shp))
}

func (s *CompSolid) IsValid() bool {
	return bool(C.topo_shape_is_valid(s.inner.val.shp))
}

func (s *CompSolid) Equals(e *Shape) bool {
	return bool(C.topo_shape_equals(s.inner.val.shp, e.inner.val))
}

func (s *CompSolid) Type() int {
	return int(C.topo_shape_type(s.inner.val.shp))
}

func (s *CompSolid) BBox() BBox {
	return BBox{val: C.topo_shape_bounding_box(s.inner.val.shp)}
}

func (s *CompSolid) Hash() int {
	return int(C.topo_shape_hash_code(s.inner.val.shp))
}

func (s *CompSolid) Transform(t Trsf) int {
	return int(C.topo_shape_transform(s.inner.val.shp, t.val))
}

func (s *CompSolid) Translate(v Vector3) int {
	return int(C.topo_shape_translate(s.inner.val.shp, v.val))
}

func (s *CompSolid) RotateFromPoint(angle float64, p1, p2 Point3) int {
	return int(C.topo_shape_rotate_from_two_point(s.inner.val.shp, C.double(angle), p1.val, p2.val))
}

func (s *CompSolid) RotateFromAxis1(angle float64, a Axis1) int {
	return int(C.topo_shape_rotate_from_axis1(s.inner.val.shp, C.double(angle), a.val))
}

func (s *CompSolid) RotateFromQuaternion(q Quaternion) int {
	return int(C.topo_shape_rotate_from_quaternion(s.inner.val.shp, q.val))
}

func (s *CompSolid) Scale(angle float64, a Point3) int {
	return int(C.topo_shape_scale(s.inner.val.shp, C.double(angle), a.val))
}

func (s *CompSolid) MirrorFromPointNorm(pnt, ner Point3) int {
	return int(C.topo_shape_mirror_from_point_norm(s.inner.val.shp, pnt.val, ner.val))
}

func (s *CompSolid) MirrorFromAxis1(a Axis1) int {
	return int(C.topo_shape_mirror_from_axis1(s.inner.val.shp, a.val))
}

func (s *CompSolid) MirrorFromAxis2(a Axis2) int {
	return int(C.topo_shape_mirror_from_axis2(s.inner.val.shp, a.val))
}

func (s *CompSolid) Transformed(t Trsf) *CompSolid {
	var val C.struct__topo_comp_solid_t
	val.shp = C.topo_shape_transformed(s.inner.val.shp, t.val)
	return &CompSolid{inner: &innerCompSolid{val: val}}
}

func (s *CompSolid) Translated(v Vector3) *CompSolid {
	var val C.struct__topo_comp_solid_t
	val.shp = C.topo_shape_translated(s.inner.val.shp, v.val)
	return &CompSolid{inner: &innerCompSolid{val: val}}
}

func (s *CompSolid) RotatedFromPoint(angle float64, p1, p2 Point3) *CompSolid {
	var val C.struct__topo_comp_solid_t
	val.shp = C.topo_shape_rotated_from_two_point(s.inner.val.shp, C.double(angle), p1.val, p2.val)
	return &CompSolid{inner: &innerCompSolid{val: val}}
}

func (s *CompSolid) RotatedFromAxis1(angle float64, a Axis1) *CompSolid {
	var val C.struct__topo_comp_solid_t
	val.shp = C.topo_shape_rotated_from_axis1(s.inner.val.shp, C.double(angle), a.val)
	return &CompSolid{inner: &innerCompSolid{val: val}}
}

func (s *CompSolid) RotatedFromQuaternion(q Quaternion) *CompSolid {
	var val C.struct__topo_comp_solid_t
	val.shp = C.topo_shape_rotated_from_quaternion(s.inner.val.shp, q.val)
	return &CompSolid{inner: &innerCompSolid{val: val}}
}

func (s *CompSolid) Scaled(angle float64, a Point3) *CompSolid {
	var val C.struct__topo_comp_solid_t
	val.shp = C.topo_shape_scaled(s.inner.val.shp, C.double(angle), a.val)
	return &CompSolid{inner: &innerCompSolid{val: val}}
}

func (s *CompSolid) MirroredFromPointNorm(pnt, ner Point3) *CompSolid {
	var val C.struct__topo_comp_solid_t
	val.shp = C.topo_shape_mirrored_from_point_norm(s.inner.val.shp, pnt.val, ner.val)
	return &CompSolid{inner: &innerCompSolid{val: val}}
}

func (s *CompSolid) MirroredFromAxis1(a Axis1) *CompSolid {
	var val C.struct__topo_comp_solid_t
	val.shp = C.topo_shape_mirrored_from_axis1(s.inner.val.shp, a.val)
	return &CompSolid{inner: &innerCompSolid{val: val}}
}

func (s *CompSolid) MirroredFromAxis2(a Axis2) *CompSolid {
	var val C.struct__topo_comp_solid_t
	val.shp = C.topo_shape_mirrored_from_axis2(s.inner.val.shp, a.val)
	return &CompSolid{inner: &innerCompSolid{val: val}}
}

func (s *CompSolid) GetOrientation() int {
	return int(C.topo_shape_get_orientation(s.inner.val.shp))
}

func (s *CompSolid) SetOrientation(t int) {
	C.topo_shape_set_orientation(s.inner.val.shp, C.int(t))
}

func (s *CompSolid) GetLocation() *Location {
	return &Location{inner: &innerLocation{val: C.topo_shape_get_location(s.inner.val.shp)}}
}

func (s *CompSolid) SetLocation(t *Location) {
	C.topo_shape_set_location(s.inner.val.shp, t.inner.val)
}

func (s *CompSolid) FixShape() bool {
	return bool(C.topo_shape_fix_shape(s.inner.val.shp))
}

func (s *CompSolid) Copy() *CompSolid {
	var val C.struct__topo_comp_solid_t
	val.shp = C.topo_shape_copy(s.inner.val.shp)
	return &CompSolid{inner: &innerCompSolid{val: val}}
}

func (s *CompSolid) Mesh(m *MeshReceiver, tolerance, deflection, angle float64) {
	C.topo_shape_mesh(s.inner.val.shp, m.inner.val, C.double(tolerance), C.double(deflection), C.double(angle))
}

func (s *CompSolid) SetSurfaceColour(c Color) {
	C.topo_shape_set_surface_colour(s.inner.val.shp, c.val)
}

func (s *CompSolid) SetCurveColour(c Color) {
	C.topo_shape_set_curve_colour(s.inner.val.shp, c.val)
}

func (s *CompSolid) SetLabel(l string) {
	str := C.CString(l)
	defer C.free(unsafe.Pointer(str))
	C.topo_shape_set_label(s.inner.val.shp, str)
}

func (s *CompSolid) GetSurfaceColour() Color {
	return Color{val: C.topo_shape_get_surface_colour(s.inner.val.shp)}
}

func (s *CompSolid) GetCurveColour() Color {
	return Color{val: C.topo_shape_get_surface_colour(s.inner.val.shp)}
}

func (s *CompSolid) GetLabel() string {
	return C.GoString(C.topo_shape_get_label(s.inner.val.shp))
}

func (t *CompSolid) free() {
	C.topo_comp_solid_free(t.inner.val)
}

func (t *CompSolid) solid() C.struct__topo_solid_t {
	var val C.struct__topo_solid_t
	val.shp = t.inner.val.shp
	return val
}

func (t *CompSolid) ToShape() *Shape {
	return &Shape{inner: &innerShape{val: C.topo_shape_share(t.inner.val.shp)}}
}

func (t *CompSolid) ToSolid() *Solid {
	var val C.struct__topo_solid_t
	val.shp = C.topo_shape_share(t.inner.val.shp)
	return &Solid{inner: &innerSolid{val: val}}
}

func (s *CompSolid) NumSolids() int {
	return int(C.topo_solid_num_solids(s.solid()))
}

func (s *CompSolid) NumFaces() int {
	return int(C.topo_solid_num_faces(s.solid()))
}

func (s *CompSolid) Area() float64 {
	return float64(C.topo_solid_area(s.solid()))
}

func (s *CompSolid) Volume() float64 {
	return float64(C.topo_solid_volume(s.solid()))
}

func (s *CompSolid) Inertia() BBox {
	return BBox{val: C.topo_solid_inertia(s.solid())}
}

func (s *CompSolid) CentreOfMass() Point3 {
	return Point3{val: C.topo_solid_centre_of_mass(s.solid())}
}

func (s *CompSolid) Extrude(f *Face, p1, p2 Point3) int {
	return int(C.topo_solid_extrude(s.solid(), f.inner.val, p1.val, p2.val))
}

func (s *CompSolid) ExtrudeFromDir(f *Face, d Vector3) int {
	return int(C.topo_solid_extrude_from_dir(s.solid(), f.inner.val, d.val))
}

func (s *CompSolid) Revolve(f *Face, p1, p2 Point3, angle float64) int {
	return int(C.topo_solid_revolve(s.solid(), f.inner.val, p1.val, p2.val, C.double(angle)))
}

func (s *CompSolid) Loft(profiles []Shape, ruled bool, tolerance float64) int {
	cshp := make([]*C.struct__topo_shape_t, len(profiles))
	for i := range profiles {
		cshp[i] = profiles[i].inner.val
	}
	return int(C.topo_solid_loft(s.solid(), &cshp[0], C.int(len(profiles)), C.bool(ruled), C.double(tolerance)))
}

func (s *CompSolid) Pipe(f *Face, w Wire) int {
	return int(C.topo_solid_pipe(s.solid(), f.inner.val, w.inner.val))
}

func (s *CompSolid) Sweep(spine *Wire, profiles []Wire, cornerMode int) int {
	cshp := make([]C.struct__topo_wire_t, len(profiles))
	for i := range profiles {
		cshp[i] = profiles[i].inner.val
	}
	return int(C.topo_solid_sweep_wire(s.solid(), spine.inner.val, &cshp[0], C.int(len(profiles)), C.int(cornerMode)))
}

func (s *CompSolid) Boolean(tool *Solid, op int) int {
	return int(C.topo_solid_boolean(s.solid(), tool.inner.val, C.int(op)))
}

func (s *CompSolid) Fillet(edges []Edge, radius []float64) int {
	cshp := make([]C.struct__topo_edge_t, len(edges))
	for i := range edges {
		cshp[i] = edges[i].inner.val
	}
	return int(C.topo_solid_fillet(s.solid(), &cshp[0], C.int(len(edges)), (*C.double)(unsafe.Pointer(&radius[0])), C.int(len(radius))))
}

func (s *CompSolid) Chamfer(edges []Edge, distances []float64) int {
	cshp := make([]C.struct__topo_edge_t, len(edges))
	for i := range edges {
		cshp[i] = edges[i].inner.val
	}
	return int(C.topo_solid_chamfer(s.solid(), &cshp[0], C.int(len(edges)), (*C.double)(unsafe.Pointer(&distances[0])), C.int(len(distances))))
}

func (s *CompSolid) Shelling(faces []Face, offset, tolerance float64) int {
	cshp := make([]C.struct__topo_face_t, len(faces))
	for i := range faces {
		cshp[i] = faces[i].inner.val
	}
	return int(C.topo_solid_shelling(s.solid(), &cshp[0], C.int(len(faces)), C.double(offset), C.double(tolerance)))
}

func (s *CompSolid) Offset(f *Face, offset, tolerance float64) int {
	return int(C.topo_solid_offset(s.solid(), f.inner.val, C.double(offset), C.double(tolerance)))
}

func (s *CompSolid) Draft(faces []Face, d Dir3, angle float64, p Plane) int {
	fs := make([]C.struct__topo_face_t, len(faces))
	for i := range faces {
		fs[i] = faces[i].inner.val
	}
	return int(C.topo_solid_draft(s.solid(), &fs[0], C.int(len(faces)), d.val, C.double(angle), p.val))
}

func (s *CompSolid) EvolvedFromFace(Spine *Face, Profil *Wire) int {
	return int(C.topo_solid_evolved_from_face(s.solid(), Spine.inner.val, Profil.inner.val))
}

func (s *CompSolid) EvolvedFromWire(Spine *Wire, Profil *Wire) int {
	return int(C.topo_solid_evolved_from_wire(s.solid(), Spine.inner.val, Profil.inner.val))
}

func (s *CompSolid) FeatPrism(f *Face, d Dir3, height float64, fuse bool) int {
	return int(C.topo_solid_feat_prism(s.solid(), f.inner.val, d.val, C.double(height), C.bool(fuse)))
}

func (s *CompSolid) FeatPrismForRange(f *Face, d Dir3, from, end Face, fuse bool) int {
	return int(C.topo_solid_feat_prism_for_range(s.solid(), f.inner.val, d.val, from.inner.val, end.inner.val, C.bool(fuse)))
}

func (s *CompSolid) FeatPrismForUntil(f *Face, d Dir3, until Face, fuse bool) int {
	return int(C.topo_solid_feat_prism_for_until(s.solid(), f.inner.val, d.val, until.inner.val, C.bool(fuse)))
}

func (s *CompSolid) DraftPrism(f *Face, angle, height float64, fuse bool) int {
	return int(C.topo_solid_feat_draft_prism(s.solid(), f.inner.val, C.double(angle), C.double(height), C.bool(fuse)))
}

func (s *CompSolid) DraftPrismForRange(f *Face, angle float64, from, end Face, fuse bool) int {
	return int(C.topo_solid_feat_draft_prism_for_range(s.solid(), f.inner.val, C.double(angle), from.inner.val, end.inner.val, C.bool(fuse)))
}

func (s *CompSolid) DraftPrismForUntil(f *Face, angle float64, until Face, fuse bool) int {
	return int(C.topo_solid_feat_draft_prism_for_until(s.solid(), f.inner.val, C.double(angle), until.inner.val, C.bool(fuse)))
}

func (s *CompSolid) RevolForRange(f *Face, a Axis1, from, end Face, fuse bool) int {
	return int(C.topo_solid_feat_revol_for_range(s.solid(), f.inner.val, a.val, from.inner.val, end.inner.val, C.bool(fuse)))
}

func (s *CompSolid) RevolForUntil(f *Face, a Axis1, until Face, fuse bool) int {
	return int(C.topo_solid_feat_revol_for_until(s.solid(), f.inner.val, a.val, until.inner.val, C.bool(fuse)))
}

func (s *CompSolid) PipeForRange(f *Face, w *Wire, from, end Face, fuse bool) int {
	return int(C.topo_solid_feat_pipe_for_range(s.solid(), f.inner.val, w.inner.val, from.inner.val, end.inner.val, C.bool(fuse)))
}

func (s *CompSolid) PipeForUntil(f *Face, w *Wire, until Face, fuse bool) int {
	return int(C.topo_solid_feat_pipe_for_until(s.solid(), f.inner.val, w.inner.val, until.inner.val, C.bool(fuse)))
}

func (s *CompSolid) LinearForm(w *Wire, p *GeomPlane, d, d1 Dir3, fuse bool) int {
	return int(C.topo_solid_linear_form(s.solid(), w.inner.val, p.inner.geom, d.val, d1.val, C.bool(fuse)))
}

func (s *CompSolid) RevolutionForm(w *Wire, p *GeomPlane, a Axis1, h1, h2 float64, fuse bool) int {
	return int(C.topo_solid_revolution_form(s.solid(), w.inner.val, p.inner.geom, a.val, C.double(h1), C.double(h2), C.bool(fuse)))
}

func (s *CompSolid) SectionFace(pnt, nor Point3) *Face {
	return &Face{inner: &innerFace{val: C.topo_solid_section_face(s.solid(), pnt.val, nor.val)}}
}

func (s *CompSolid) ConvertToNurbs() int {
	return int(C.topo_solid_convert_to_nurbs(s.solid()))
}

func TopoCompSolidMake(s []Solid) *CompSolid {
	sos := make([]C.struct__topo_solid_t, len(s))
	for i := range s {
		sos[i] = s[i].inner.val
	}
	return &CompSolid{inner: &innerCompSolid{val: C.topo_comp_solid_make_comp_solid(&sos[0], C.int(len(s)))}}
}

type Compound struct {
	inner *innerCompound
}

type innerCompound struct {
	val C.struct__topo_compound_t
}

func TopoMakeCompound() *Compound {
	return &Compound{inner: &innerCompound{val: C.topo_make_compound()}}
}

func (s *Compound) IsNull() bool {
	return bool(C.topo_shape_is_null(s.inner.val.shp))
}

func (s *Compound) IsValid() bool {
	return bool(C.topo_shape_is_valid(s.inner.val.shp))
}

func (s *Compound) Equals(e *Shape) bool {
	return bool(C.topo_shape_equals(s.inner.val.shp, e.inner.val))
}

func (s *Compound) Type() int {
	return int(C.topo_shape_type(s.inner.val.shp))
}

func (s *Compound) BBox() BBox {
	return BBox{val: C.topo_shape_bounding_box(s.inner.val.shp)}
}

func (s *Compound) Hash() int {
	return int(C.topo_shape_hash_code(s.inner.val.shp))
}

func (s *Compound) Transform(t Trsf) int {
	return int(C.topo_shape_transform(s.inner.val.shp, t.val))
}

func (s *Compound) Translate(v Vector3) int {
	return int(C.topo_shape_translate(s.inner.val.shp, v.val))
}

func (s *Compound) RotateFromPoint(angle float64, p1, p2 Point3) int {
	return int(C.topo_shape_rotate_from_two_point(s.inner.val.shp, C.double(angle), p1.val, p2.val))
}

func (s *Compound) RotateFromAxis1(angle float64, a Axis1) int {
	return int(C.topo_shape_rotate_from_axis1(s.inner.val.shp, C.double(angle), a.val))
}

func (s *Compound) RotateFromQuaternion(q Quaternion) int {
	return int(C.topo_shape_rotate_from_quaternion(s.inner.val.shp, q.val))
}

func (s *Compound) Scale(angle float64, a Point3) int {
	return int(C.topo_shape_scale(s.inner.val.shp, C.double(angle), a.val))
}

func (s *Compound) MirrorFromPointNorm(pnt, ner Point3) int {
	return int(C.topo_shape_mirror_from_point_norm(s.inner.val.shp, pnt.val, ner.val))
}

func (s *Compound) MirrorFromAxis1(a Axis1) int {
	return int(C.topo_shape_mirror_from_axis1(s.inner.val.shp, a.val))
}

func (s *Compound) MirrorFromAxis2(a Axis2) int {
	return int(C.topo_shape_mirror_from_axis2(s.inner.val.shp, a.val))
}

func (s *Compound) Transformed(t Trsf) *Compound {
	var val C.struct__topo_compound_t
	val.shp = C.topo_shape_transformed(s.inner.val.shp, t.val)
	return &Compound{inner: &innerCompound{val: val}}
}

func (s *Compound) Translated(v Vector3) *Compound {
	var val C.struct__topo_compound_t
	val.shp = C.topo_shape_translated(s.inner.val.shp, v.val)
	return &Compound{inner: &innerCompound{val: val}}
}

func (s *Compound) RotatedFromPoint(angle float64, p1, p2 Point3) *Compound {
	var val C.struct__topo_compound_t
	val.shp = C.topo_shape_rotated_from_two_point(s.inner.val.shp, C.double(angle), p1.val, p2.val)
	return &Compound{inner: &innerCompound{val: val}}
}

func (s *Compound) RotatedFromAxis1(angle float64, a Axis1) *Compound {
	var val C.struct__topo_compound_t
	val.shp = C.topo_shape_rotated_from_axis1(s.inner.val.shp, C.double(angle), a.val)
	return &Compound{inner: &innerCompound{val: val}}
}

func (s *Compound) RotatedFromQuaternion(q Quaternion) *Compound {
	var val C.struct__topo_compound_t
	val.shp = C.topo_shape_rotated_from_quaternion(s.inner.val.shp, q.val)
	return &Compound{inner: &innerCompound{val: val}}
}

func (s *Compound) Scaled(angle float64, a Point3) *Compound {
	var val C.struct__topo_compound_t
	val.shp = C.topo_shape_scaled(s.inner.val.shp, C.double(angle), a.val)
	return &Compound{inner: &innerCompound{val: val}}
}

func (s *Compound) MirroredFromPointNorm(pnt, ner Point3) *Compound {
	var val C.struct__topo_compound_t
	val.shp = C.topo_shape_mirrored_from_point_norm(s.inner.val.shp, pnt.val, ner.val)
	return &Compound{inner: &innerCompound{val: val}}
}

func (s *Compound) MirroredFromAxis1(a Axis1) *Compound {
	var val C.struct__topo_compound_t
	val.shp = C.topo_shape_mirrored_from_axis1(s.inner.val.shp, a.val)
	return &Compound{inner: &innerCompound{val: val}}
}

func (s *Compound) MirroredFromAxis2(a Axis2) *Compound {
	var val C.struct__topo_compound_t
	val.shp = C.topo_shape_mirrored_from_axis2(s.inner.val.shp, a.val)
	return &Compound{inner: &innerCompound{val: val}}
}

func (s *Compound) GetOrientation() int {
	return int(C.topo_shape_get_orientation(s.inner.val.shp))
}

func (s *Compound) SetOrientation(t int) {
	C.topo_shape_set_orientation(s.inner.val.shp, C.int(t))
}

func (s *Compound) GetLocation() *Location {
	return &Location{inner: &innerLocation{val: C.topo_shape_get_location(s.inner.val.shp)}}
}

func (s *Compound) SetLocation(t *Location) {
	C.topo_shape_set_location(s.inner.val.shp, t.inner.val)
}

func (s *Compound) FixShape() bool {
	return bool(C.topo_shape_fix_shape(s.inner.val.shp))
}

func (s *Compound) Copy() *Compound {
	var val C.struct__topo_compound_t
	val.shp = C.topo_shape_copy(s.inner.val.shp)
	return &Compound{inner: &innerCompound{val: val}}
}

func (s *Compound) Mesh(m *MeshReceiver, tolerance, deflection, angle float64) {
	C.topo_shape_mesh(s.inner.val.shp, m.inner.val, C.double(tolerance), C.double(deflection), C.double(angle))
}

func (s *Compound) SetSurfaceColour(c Color) {
	C.topo_shape_set_surface_colour(s.inner.val.shp, c.val)
}

func (s *Compound) SetCurveColour(c Color) {
	C.topo_shape_set_curve_colour(s.inner.val.shp, c.val)
}

func (s *Compound) SetLabel(l string) {
	str := C.CString(l)
	defer C.free(unsafe.Pointer(str))
	C.topo_shape_set_label(s.inner.val.shp, str)
}

func (s *Compound) GetSurfaceColour() Color {
	return Color{val: C.topo_shape_get_surface_colour(s.inner.val.shp)}
}

func (s *Compound) GetCurveColour() Color {
	return Color{val: C.topo_shape_get_surface_colour(s.inner.val.shp)}
}

func (s *Compound) GetLabel() string {
	return C.GoString(C.topo_shape_get_label(s.inner.val.shp))
}

func (t *Compound) free() {
	C.topo_compound_free(t.inner.val)
}

func (t *Compound) solid() C.struct__topo_solid_t {
	var val C.struct__topo_solid_t
	val.shp = t.inner.val.shp
	return val
}

func (t *Compound) ToShape() *Shape {
	return &Shape{inner: &innerShape{val: C.topo_shape_share(t.inner.val.shp)}}
}

func (t *Compound) ToSolid() *Solid {
	var val C.struct__topo_solid_t
	val.shp = C.topo_shape_share(t.inner.val.shp)
	return &Solid{inner: &innerSolid{val: val}}
}

func (s *Compound) NumSolids() int {
	return int(C.topo_solid_num_solids(s.solid()))
}

func (s *Compound) NumFaces() int {
	return int(C.topo_solid_num_faces(s.solid()))
}

func (s *Compound) Area() float64 {
	return float64(C.topo_solid_area(s.solid()))
}

func (s *Compound) Volume() float64 {
	return float64(C.topo_solid_volume(s.solid()))
}

func (s *Compound) Inertia() BBox {
	return BBox{val: C.topo_solid_inertia(s.solid())}
}

func (s *Compound) CentreOfMass() Point3 {
	return Point3{val: C.topo_solid_centre_of_mass(s.solid())}
}

func (s *Compound) Extrude(f *Face, p1, p2 Point3) int {
	return int(C.topo_solid_extrude(s.solid(), f.inner.val, p1.val, p2.val))
}

func (s *Compound) ExtrudeFromDir(f *Face, d Vector3) int {
	return int(C.topo_solid_extrude_from_dir(s.solid(), f.inner.val, d.val))
}

func (s *Compound) Revolve(f *Face, p1, p2 Point3, angle float64) int {
	return int(C.topo_solid_revolve(s.solid(), f.inner.val, p1.val, p2.val, C.double(angle)))
}

func (s *Compound) Loft(profiles []Shape, ruled bool, tolerance float64) int {
	cshp := make([]*C.struct__topo_shape_t, len(profiles))
	for i := range profiles {
		cshp[i] = profiles[i].inner.val
	}
	return int(C.topo_solid_loft(s.solid(), &cshp[0], C.int(len(profiles)), C.bool(ruled), C.double(tolerance)))
}

func (s *Compound) Pipe(f *Face, w Wire) int {
	return int(C.topo_solid_pipe(s.solid(), f.inner.val, w.inner.val))
}

func (s *Compound) Sweep(spine *Wire, profiles []Shape, cornerMode int) int {
	cshp := make([]*C.struct__topo_shape_t, len(profiles))
	for i := range profiles {
		cshp[i] = profiles[i].inner.val
	}
	return int(C.topo_solid_sweep(s.solid(), spine.inner.val, &cshp[0], C.int(len(profiles)), C.int(cornerMode)))
}

func (s *Compound) Boolean(tool *Solid, op int) int {
	return int(C.topo_solid_boolean(s.solid(), tool.inner.val, C.int(op)))
}

func (s *Compound) Fillet(edges []Edge, radius []float64) int {
	cshp := make([]C.struct__topo_edge_t, len(edges))
	for i := range edges {
		cshp[i] = edges[i].inner.val
	}
	return int(C.topo_solid_fillet(s.solid(), &cshp[0], C.int(len(edges)), (*C.double)(unsafe.Pointer(&radius[0])), C.int(len(radius))))
}

func (s *Compound) Chamfer(edges []Edge, distances []float64) int {
	cshp := make([]C.struct__topo_edge_t, len(edges))
	for i := range edges {
		cshp[i] = edges[i].inner.val
	}
	return int(C.topo_solid_chamfer(s.solid(), &cshp[0], C.int(len(edges)), (*C.double)(unsafe.Pointer(&distances[0])), C.int(len(distances))))
}

func (s *Compound) Shelling(faces []Face, offset, tolerance float64) int {
	cshp := make([]C.struct__topo_face_t, len(faces))
	for i := range faces {
		cshp[i] = faces[i].inner.val
	}
	return int(C.topo_solid_shelling(s.solid(), &cshp[0], C.int(len(faces)), C.double(offset), C.double(tolerance)))
}

func (s *Compound) Offset(f *Face, offset, tolerance float64) int {
	return int(C.topo_solid_offset(s.solid(), f.inner.val, C.double(offset), C.double(tolerance)))
}

func (s *Compound) Draft(faces []Face, d Dir3, angle float64, p Plane) int {
	fs := make([]C.struct__topo_face_t, len(faces))
	for i := range faces {
		fs[i] = faces[i].inner.val
	}
	return int(C.topo_solid_draft(s.solid(), &fs[0], C.int(len(faces)), d.val, C.double(angle), p.val))
}

func (s *Compound) EvolvedFromFace(Spine *Face, Profil *Wire) int {
	return int(C.topo_solid_evolved_from_face(s.solid(), Spine.inner.val, Profil.inner.val))
}

func (s *Compound) EvolvedFromWire(Spine *Wire, Profil *Wire) int {
	return int(C.topo_solid_evolved_from_wire(s.solid(), Spine.inner.val, Profil.inner.val))
}

func (s *Compound) FeatPrism(f *Face, d Dir3, height float64, fuse bool) int {
	return int(C.topo_solid_feat_prism(s.solid(), f.inner.val, d.val, C.double(height), C.bool(fuse)))
}

func (s *Compound) FeatPrismForRange(f *Face, d Dir3, from, end Face, fuse bool) int {
	return int(C.topo_solid_feat_prism_for_range(s.solid(), f.inner.val, d.val, from.inner.val, end.inner.val, C.bool(fuse)))
}

func (s *Compound) FeatPrismForUntil(f *Face, d Dir3, until Face, fuse bool) int {
	return int(C.topo_solid_feat_prism_for_until(s.solid(), f.inner.val, d.val, until.inner.val, C.bool(fuse)))
}

func (s *Compound) DraftPrism(f *Face, angle, height float64, fuse bool) int {
	return int(C.topo_solid_feat_draft_prism(s.solid(), f.inner.val, C.double(angle), C.double(height), C.bool(fuse)))
}

func (s *Compound) DraftPrismForRange(f *Face, angle float64, from, end Face, fuse bool) int {
	return int(C.topo_solid_feat_draft_prism_for_range(s.solid(), f.inner.val, C.double(angle), from.inner.val, end.inner.val, C.bool(fuse)))
}

func (s *Compound) DraftPrismForUntil(f *Face, angle float64, until Face, fuse bool) int {
	return int(C.topo_solid_feat_draft_prism_for_until(s.solid(), f.inner.val, C.double(angle), until.inner.val, C.bool(fuse)))
}

func (s *Compound) RevolForRange(f *Face, a Axis1, from, end Face, fuse bool) int {
	return int(C.topo_solid_feat_revol_for_range(s.solid(), f.inner.val, a.val, from.inner.val, end.inner.val, C.bool(fuse)))
}

func (s *Compound) RevolForUntil(f *Face, a Axis1, until Face, fuse bool) int {
	return int(C.topo_solid_feat_revol_for_until(s.solid(), f.inner.val, a.val, until.inner.val, C.bool(fuse)))
}

func (s *Compound) PipeForRange(f *Face, w *Wire, from, end Face, fuse bool) int {
	return int(C.topo_solid_feat_pipe_for_range(s.solid(), f.inner.val, w.inner.val, from.inner.val, end.inner.val, C.bool(fuse)))
}

func (s *Compound) PipeForUntil(f *Face, w *Wire, until Face, fuse bool) int {
	return int(C.topo_solid_feat_pipe_for_until(s.solid(), f.inner.val, w.inner.val, until.inner.val, C.bool(fuse)))
}

func (s *Compound) LinearForm(w *Wire, p *GeomPlane, d, d1 Dir3, fuse bool) int {
	return int(C.topo_solid_linear_form(s.solid(), w.inner.val, p.inner.geom, d.val, d1.val, C.bool(fuse)))
}

func (s *Compound) RevolutionForm(w *Wire, p *GeomPlane, a Axis1, h1, h2 float64, fuse bool) int {
	return int(C.topo_solid_revolution_form(s.solid(), w.inner.val, p.inner.geom, a.val, C.double(h1), C.double(h2), C.bool(fuse)))
}

func (s *Compound) SectionFace(pnt, nor Point3) *Face {
	return &Face{inner: &innerFace{val: C.topo_solid_section_face(s.solid(), pnt.val, nor.val)}}
}

func (s *Compound) ConvertToNurbs() int {
	return int(C.topo_solid_convert_to_nurbs(s.solid()))
}

func TopoCompoundMake(s []Shape) *Compound {
	sos := make([]*C.struct__topo_shape_t, len(s))
	for i := range s {
		sos[i] = s[i].inner.val
	}
	return &Compound{inner: &innerCompound{val: C.topo_compound_make_compound(&sos[0], C.int(len(s)))}}
}

type Edge struct {
	inner *innerEdge
}

type innerEdge struct {
	val C.struct__topo_edge_t
}

func TopoMakeEdge() *Edge {
	p := &Edge{inner: &innerEdge{val: C.topo_make_edge()}}
	runtime.SetFinalizer(p, (*Edge).free)
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
	return &Edge{inner: &innerEdge{val: val}}
}

func (s *Edge) Translated(v Vector3) *Edge {
	var val C.struct__topo_edge_t
	val.shp = C.topo_shape_translated(s.inner.val.shp, v.val)
	return &Edge{inner: &innerEdge{val: val}}
}

func (s *Edge) RotatedFromPoint(angle float64, p1, p2 Point3) *Edge {
	var val C.struct__topo_edge_t
	val.shp = C.topo_shape_rotated_from_two_point(s.inner.val.shp, C.double(angle), p1.val, p2.val)
	return &Edge{inner: &innerEdge{val: val}}
}

func (s *Edge) RotatedFromAxis1(angle float64, a Axis1) *Edge {
	var val C.struct__topo_edge_t
	val.shp = C.topo_shape_rotated_from_axis1(s.inner.val.shp, C.double(angle), a.val)
	return &Edge{inner: &innerEdge{val: val}}
}

func (s *Edge) RotatedFromQuaternion(q Quaternion) *Edge {
	var val C.struct__topo_edge_t
	val.shp = C.topo_shape_rotated_from_quaternion(s.inner.val.shp, q.val)
	return &Edge{inner: &innerEdge{val: val}}
}

func (s *Edge) Scaled(angle float64, a Point3) *Edge {
	var val C.struct__topo_edge_t
	val.shp = C.topo_shape_scaled(s.inner.val.shp, C.double(angle), a.val)
	return &Edge{inner: &innerEdge{val: val}}
}

func (s *Edge) MirroredFromPointNorm(pnt, ner Point3) *Edge {
	var val C.struct__topo_edge_t
	val.shp = C.topo_shape_mirrored_from_point_norm(s.inner.val.shp, pnt.val, ner.val)
	return &Edge{inner: &innerEdge{val: val}}
}

func (s *Edge) MirroredFromAxis1(a Axis1) *Edge {
	var val C.struct__topo_edge_t
	val.shp = C.topo_shape_mirrored_from_axis1(s.inner.val.shp, a.val)
	return &Edge{inner: &innerEdge{val: val}}
}

func (s *Edge) MirroredFromAxis2(a Axis2) *Edge {
	var val C.struct__topo_edge_t
	val.shp = C.topo_shape_mirrored_from_axis2(s.inner.val.shp, a.val)
	return &Edge{inner: &innerEdge{val: val}}
}

func (s *Edge) GetOrientation() int {
	return int(C.topo_shape_get_orientation(s.inner.val.shp))
}

func (s *Edge) SetOrientation(t int) {
	C.topo_shape_set_orientation(s.inner.val.shp, C.int(t))
}

func (s *Edge) GetLocation() *Location {
	return &Location{inner: &innerLocation{val: C.topo_shape_get_location(s.inner.val.shp)}}
}

func (s *Edge) SetLocation(t *Location) {
	C.topo_shape_set_location(s.inner.val.shp, t.inner.val)
}

func (s *Edge) FixShape() bool {
	return bool(C.topo_shape_fix_shape(s.inner.val.shp))
}

func (s *Edge) Copy() *Edge {
	var val C.struct__topo_edge_t
	val.shp = C.topo_shape_copy(s.inner.val.shp)
	return &Edge{inner: &innerEdge{val: val}}
}

func (s *Edge) Mesh(m *MeshReceiver, tolerance, deflection, angle float64) {
	C.topo_shape_mesh(s.inner.val.shp, m.inner.val, C.double(tolerance), C.double(deflection), C.double(angle))
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

func (s *Edge) GetSurfaceColour() Color {
	return Color{val: C.topo_shape_get_surface_colour(s.inner.val.shp)}
}

func (s *Edge) GetCurveColour() Color {
	return Color{val: C.topo_shape_get_surface_colour(s.inner.val.shp)}
}

func (s *Edge) GetLabel() string {
	return C.GoString(C.topo_shape_get_label(s.inner.val.shp))
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

func (t *Edge) ToShape() *Shape {
	return &Shape{inner: &innerShape{val: C.topo_shape_share(t.inner.val.shp)}}
}

func (t *Edge) free() {
	C.topo_edge_free(t.inner.val)
}

func TopoMakeEdgeFromPoints(pts []Point3) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_points(&pts[0].val, C.int(len(pts)))}}
}

func TopoMakeEdgeFromTwoVertex(v1, v2 Vertex) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_two_vertex(v1.inner.val, v2.inner.val)}}
}

func TopoMakeEdgeFromTwoPoint(p1, p2 Point3) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_two_point(p1.val, p2.val)}}
}

func TopoMakeEdgeFromLine(l Line) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_line(l.val)}}
}

func TopoMakeEdgeFromLineParm(l Line, p1, p2 float64) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_line_p(l.val, C.double(p1), C.double(p2))}}
}

func TopoMakeEdgeFromLinePoint(l Line, p1, p2 Point3) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_line_point(l.val, p1.val, p2.val)}}
}

func TopoMakeEdgeFromLineVertex(l Line, p1, p2 Vertex) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_line_vertex(l.val, p1.inner.val, p2.inner.val)}}
}

func TopoMakeEdgeFromCirc(s Circ) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_circ(s.val)}}
}

func TopoMakeEdgeFromCircParm(s Circ, p1, p2 float64) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_circ_p(s.val, C.double(p1), C.double(p2))}}
}

func TopoMakeEdgeFromCircPoint(s Circ, p1, p2 Point3) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_circ_point(s.val, p1.val, p2.val)}}
}

func TopoMakeEdgeFromCircVertex(s Circ, p1, p2 Vertex) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_circ_vertex(s.val, p1.inner.val, p2.inner.val)}}
}

func TopoMakeEdgeFromElips(s Elips) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_elips(s.val)}}
}

func TopoMakeEdgeFromElipsParm(s Elips, p1, p2 float64) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_elips_p(s.val, C.double(p1), C.double(p2))}}
}

func TopoMakeEdgeFromElipsPoint(s Elips, p1, p2 Point3) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_elips_point(s.val, p1.val, p2.val)}}
}

func TopoMakeEdgeFromElipsVertex(s Elips, p1, p2 Vertex) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_elips_vertex(s.val, p1.inner.val, p2.inner.val)}}
}

func TopoMakeEdgeFromHyper(s Hyperbola) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_hyper(s.val)}}
}

func TopoMakeEdgeFromHyperParm(s Hyperbola, p1, p2 float64) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_hyper_p(s.val, C.double(p1), C.double(p2))}}
}

func TopoMakeEdgeFromHyperPoint(s Hyperbola, p1, p2 Point3) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_hyper_point(s.val, p1.val, p2.val)}}
}

func TopoMakeEdgeFromHyperVertex(s Hyperbola, p1, p2 Vertex) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_hyper_vertex(s.val, p1.inner.val, p2.inner.val)}}
}

func TopoMakeEdgeFromPara(s Parabola) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_parab(s.val)}}
}

func TopoMakeEdgeFromParaParm(s Parabola, p1, p2 float64) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_parab_p(s.val, C.double(p1), C.double(p2))}}
}

func TopoMakeEdgeFromParaPoint(s Parabola, p1, p2 Point3) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_parab_point(s.val, p1.val, p2.val)}}
}

func TopoMakeEdgeFromParaVertex(s Parabola, p1, p2 Vertex) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_parab_vertex(s.val, p1.inner.val, p2.inner.val)}}
}

func TopoMakeEdgeFromCurve(s GeomCurve) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edgee_from_curve(s.inner.geom)}}
}

func TopoMakeEdgeFromCurveParm(s GeomCurve, p1, p2 float64) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_curve_p(s.inner.geom, C.double(p1), C.double(p2))}}
}

func TopoMakeEdgeFromCurvePoint(s GeomCurve, p1, p2 Point3) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_curve_point(s.inner.geom, p1.val, p2.val)}}
}

func TopoMakeEdgeFromCurveVertex(s GeomCurve, p1, p2 Vertex) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_curve_vertex(s.inner.geom, p1.inner.val, p2.inner.val)}}
}

func TopoMakeEdgeFromCurvePointParm(s GeomCurve, pt1, pt2 Point3, p1, p2 float64) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edgee_from_curve_point_p(s.inner.geom, pt1.val, pt2.val, C.double(p1), C.double(p2))}}
}

func TopoMakeEdgeFromCurveVertexParm(s GeomCurve, pt1, pt2 Vertex, p1, p2 float64) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_curve_vertex_p(s.inner.geom, pt1.inner.val, pt2.inner.val, C.double(p1), C.double(p2))}}
}

func TopoMakeEdgeFromSurface(cu Geom2dCurve, s GeomSurface) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_curve_surface(cu.inner.geom, s.inner.geom)}}
}

func TopoMakeEdgeFromSurfaceParm(cu Geom2dCurve, s GeomSurface, p1, p2 float64) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_curve_surface_p(cu.inner.geom, s.inner.geom, C.double(p1), C.double(p2))}}
}

func TopoMakeEdgeFromSurfacePoint(cu Geom2dCurve, s GeomSurface, p1, p2 Point3) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_curve_surface_point(cu.inner.geom, s.inner.geom, p1.val, p2.val)}}
}

func TopoMakeEdgeFromSurfaceVertex(cu Geom2dCurve, s GeomSurface, p1, p2 Vertex) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_curve_surface_vertex(cu.inner.geom, s.inner.geom, p1.inner.val, p2.inner.val)}}
}

func TopoMakeEdgeFromSurfacePointParm(cu Geom2dCurve, s GeomSurface, pt1, pt2 Point3, p1, p2 float64) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_curve_surface_point_p(cu.inner.geom, s.inner.geom, pt1.val, pt2.val, C.double(p1), C.double(p2))}}
}

func TopoMakeEdgeFromSurfaceVertexParm(cu Geom2dCurve, s GeomSurface, pt1, pt2 Vertex, p1, p2 float64) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_from_curve_surface_vertex_p(cu.inner.geom, s.inner.geom, pt1.inner.val, pt2.inner.val, C.double(p1), C.double(p2))}}
}

func TopoMakeEdge2dFromTwoVertex(pt1, pt2 Vertex) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge2d_from_two_vertex(pt1.inner.val, pt2.inner.val)}}
}

func TopoMakeEdge2dFromTwoPoint(pt1, pt2 Point2) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge2d_from_two_point(pt1.val, pt2.val)}}
}

func TopoMakeEdge2dFromLine(l Line2d) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge2d_from_line(l.val)}}
}

func TopoMakeEdge2dFromLineParm(l Line2d, p1, p2 float64) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge2d_from_line_p(l.val, C.double(p1), C.double(p2))}}
}

func TopoMakeEdge2dFromLinePoint(l Line2d, p1, p2 Point2) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge2d_from_line_point(l.val, p1.val, p2.val)}}
}

func TopoMakeEdge2dFromLineVertex(l Line2d, p1, p2 Vertex) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge2d_from_line_vertex(l.val, p1.inner.val, p2.inner.val)}}
}

func TopoMakeEdge2dFromCirc(l Circ2d) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge2d_from_circ(l.val)}}
}

func TopoMakeEdge2dFromCircParm(l Circ2d, p1, p2 float64) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge2d_from_circ_p(l.val, C.double(p1), C.double(p2))}}
}

func TopoMakeEdge2dFromCircPoint(l Circ2d, p1, p2 Point2) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge2d_from_circ_point(l.val, p1.val, p2.val)}}
}

func TopoMakeEdge2dFromCircVertex(l Circ2d, p1, p2 Vertex) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge2d_from_circ_vertex(l.val, p1.inner.val, p2.inner.val)}}
}

func TopoMakeEdge2dFromElips(l Elips2d) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge2d_from_elips(l.val)}}
}

func TopoMakeEdge2dFromElipsParm(l Elips2d, p1, p2 float64) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge2d_from_elips_p(l.val, C.double(p1), C.double(p2))}}
}

func TopoMakeEdge2dFromElipsPoint(l Elips2d, p1, p2 Point2) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge2d_from_elips_point(l.val, p1.val, p2.val)}}
}

func TopoMakeEdge2dFromElipsVertex(l Elips2d, p1, p2 Vertex) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge2d_from_elips_vertex(l.val, p1.inner.val, p2.inner.val)}}
}

func TopoMakeEdge2dFromHyper(l Hyperbola2d) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge2d_from_hyper(l.val)}}
}

func TopoMakeEdge2dFromHyperParm(l Hyperbola2d, p1, p2 float64) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge2d_from_hyper_p(l.val, C.double(p1), C.double(p2))}}
}

func TopoMakeEdge2dFromHyperPoint(l Hyperbola2d, p1, p2 Point2) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge2d_from_hyper_point(l.val, p1.val, p2.val)}}
}

func TopoMakeEdge2dFromHyperVertex(l Hyperbola2d, p1, p2 Vertex) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge2d_from_hyper_vertex(l.val, p1.inner.val, p2.inner.val)}}
}

func TopoMakeEdge2dFromPara(l Parabola2d) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge2d_from_parab(l.val)}}
}

func TopoMakeEdge2dFromParaParm(l Parabola2d, p1, p2 float64) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge2d_from_parab_p(l.val, C.double(p1), C.double(p2))}}
}

func TopoMakeEdge2dFromParaPoint(l Parabola2d, p1, p2 Point2) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge2d_from_parab_point(l.val, p1.val, p2.val)}}
}

func TopoMakeEdge2dFromParaVertex(l Parabola2d, p1, p2 Vertex) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge2d_from_parab_vertex(l.val, p1.inner.val, p2.inner.val)}}
}

func TopoMakeEdge2dFromCurve(l Geom2dCurve) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge2d_from_curve(l.inner.geom)}}
}

func TopoMakeEdge2dFromCurveParm(l Geom2dCurve, p1, p2 float64) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge2d_from_curve_p(l.inner.geom, C.double(p1), C.double(p2))}}
}

func TopoMakeEdge2dFromCurvePoint(l Geom2dCurve, p1, p2 Point2) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge2d_from_curve_point(l.inner.geom, p1.val, p2.val)}}
}

func TopoMakeEdge2dFromCurveVertex(l Geom2dCurve, p1, p2 Vertex) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge2d_from_curve_vertex(l.inner.geom, p1.inner.val, p2.inner.val)}}
}

func TopoMakeEdge2dFromCurvePointParm(l Geom2dCurve, pt1, pt2 Point2, p1, p2 float64) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge2d_from_curve_point_p(l.inner.geom, pt1.val, pt2.val, C.double(p1), C.double(p2))}}
}

func TopoMakeEdge2dFromCurveVertexParm(l Geom2dCurve, pt1, pt2 Vertex, p1, p2 float64) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_edge2d_from_curve_vertex_p(l.inner.geom, pt1.inner.val, pt2.inner.val, C.double(p1), C.double(p2))}}
}

func TopoEdgeMakePolygon() *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_polygon()}}
}

func TopoEdgeMakePolygonFromTwoPoint(p1, p2 Point3) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_polygon_from_two_point(p1.val, p2.val)}}
}

func TopoEdgeMakePolygonFromThreePoint(p1, p2, p3 Point3, Close bool) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_polygon_from_three_point(p1.val, p2.val, p3.val, C.bool(Close))}}
}

func TopoEdgeMakePolygonFromFourPoint(p1, p2, p3, p4 Point3, Close bool) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_polygon_from_four_point(p1.val, p2.val, p3.val, p4.val, C.bool(Close))}}
}

func TopoEdgeMakePolygonFromTwoVertex(p1, p2 Vertex) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_polygon_from_two_vertex(p1.inner.val, p2.inner.val)}}
}

func TopoEdgeMakePolygonFromThreeVertex(p1, p2, p3 Vertex, Close bool) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_polygon_from_three_vertex(p1.inner.val, p2.inner.val, p3.inner.val, C.bool(Close))}}
}

func TopoEdgeMakePolygonFromFourVertex(p1, p2, p3, p4 Vertex, Close bool) *Edge {
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_polygon_from_four_vertex(p1.inner.val, p2.inner.val, p3.inner.val, p4.inner.val, C.bool(Close))}}
}

func TopoEdgeMakePolygonFromVertices(vers []Vertex, Close bool) *Edge {
	cvs := make([]C.struct__topo_vertex_t, len(vers))
	for i := range vers {
		cvs[i] = vers[i].inner.val
	}
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_polygon_from_vertices(&cvs[0], C.int(len(vers)), C.bool(Close))}}
}

func TopoEdgeMakePolygonFromPoints(points []Point3, Close bool) *Edge {
	cvs := make([]C.struct__pnt3d_t, len(points))
	for i := range points {
		cvs[i] = points[i].val
	}
	return &Edge{inner: &innerEdge{val: C.topo_edge_make_polygonn_from_points(&cvs[0], C.int(len(points)), C.bool(Close))}}
}

type Face struct {
	inner *innerFace
}

type innerFace struct {
	val C.struct__topo_face_t
}

func TopoMakeFace() *Face {
	p := &Face{inner: &innerFace{val: C.topo_make_face()}}
	runtime.SetFinalizer(p, (*Face).free)
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
	return &Face{inner: &innerFace{val: val}}
}

func (s *Face) Translated(v Vector3) *Face {
	var val C.struct__topo_face_t
	val.shp = C.topo_shape_translated(s.inner.val.shp, v.val)
	return &Face{inner: &innerFace{val: val}}
}

func (s *Face) RotatedFromPoint(angle float64, p1, p2 Point3) *Face {
	var val C.struct__topo_face_t
	val.shp = C.topo_shape_rotated_from_two_point(s.inner.val.shp, C.double(angle), p1.val, p2.val)
	return &Face{inner: &innerFace{val: val}}
}

func (s *Face) RotatedFromAxis1(angle float64, a Axis1) *Face {
	var val C.struct__topo_face_t
	val.shp = C.topo_shape_rotated_from_axis1(s.inner.val.shp, C.double(angle), a.val)
	return &Face{inner: &innerFace{val: val}}
}

func (s *Face) RotatedFromQuaternion(q Quaternion) *Face {
	var val C.struct__topo_face_t
	val.shp = C.topo_shape_rotated_from_quaternion(s.inner.val.shp, q.val)
	return &Face{inner: &innerFace{val: val}}
}

func (s *Face) Scaled(angle float64, a Point3) *Face {
	var val C.struct__topo_face_t
	val.shp = C.topo_shape_scaled(s.inner.val.shp, C.double(angle), a.val)
	return &Face{inner: &innerFace{val: val}}
}

func (s *Face) MirroredFromPointNorm(pnt, ner Point3) *Face {
	var val C.struct__topo_face_t
	val.shp = C.topo_shape_mirrored_from_point_norm(s.inner.val.shp, pnt.val, ner.val)
	return &Face{inner: &innerFace{val: val}}
}

func (s *Face) MirroredFromAxis1(a Axis1) *Face {
	var val C.struct__topo_face_t
	val.shp = C.topo_shape_mirrored_from_axis1(s.inner.val.shp, a.val)
	return &Face{inner: &innerFace{val: val}}
}

func (s *Face) MirroredFromAxis2(a Axis2) *Face {
	var val C.struct__topo_face_t
	val.shp = C.topo_shape_mirrored_from_axis2(s.inner.val.shp, a.val)
	return &Face{inner: &innerFace{val: val}}
}

func (s *Face) GetOrientation() int {
	return int(C.topo_shape_get_orientation(s.inner.val.shp))
}

func (s *Face) SetOrientation(t int) {
	C.topo_shape_set_orientation(s.inner.val.shp, C.int(t))
}

func (s *Face) GetLocation() *Location {
	return &Location{inner: &innerLocation{val: C.topo_shape_get_location(s.inner.val.shp)}}
}

func (s *Face) SetLocation(t *Location) {
	C.topo_shape_set_location(s.inner.val.shp, t.inner.val)
}

func (s *Face) FixShape() bool {
	return bool(C.topo_shape_fix_shape(s.inner.val.shp))
}

func (s *Face) Copy() *Face {
	var val C.struct__topo_face_t
	val.shp = C.topo_shape_copy(s.inner.val.shp)
	return &Face{inner: &innerFace{val: val}}
}

func (s *Face) Mesh(m *MeshReceiver, tolerance, deflection, angle float64) {
	C.topo_shape_mesh(s.inner.val.shp, m.inner.val, C.double(tolerance), C.double(deflection), C.double(angle))
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

func (s *Face) GetSurfaceColour() Color {
	return Color{val: C.topo_shape_get_surface_colour(s.inner.val.shp)}
}

func (s *Face) GetCurveColour() Color {
	return Color{val: C.topo_shape_get_surface_colour(s.inner.val.shp)}
}

func (s *Face) GetLabel() string {
	return C.GoString(C.topo_shape_get_label(s.inner.val.shp))
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

func (s *Face) Sweep(spine *Wire, profiles []Wire, cornerMode int) int {
	cshp := make([]C.struct__topo_wire_t, len(profiles))
	for i := range profiles {
		cshp[i] = profiles[i].inner.val
	}
	return int(C.topo_face_sweep_wire(s.inner.val, spine.inner.val, &cshp[0], C.int(len(profiles)), C.int(cornerMode)))
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
	return &Shape{inner: &innerShape{val: C.topo_shape_share(t.inner.val.shp)}}
}

func (t *Face) free() {
	C.topo_face_free(t.inner.val)
}

func TopoMakeFaceFromPlane(f Plane) *Face {
	return &Face{inner: &innerFace{val: C.topo_face_make_face_from_plane(f.val)}}
}

func TopoMakeFaceFromCylinder(f Cylinder) *Face {
	return &Face{inner: &innerFace{val: C.topo_face_make_face_from_cylinder(f.val)}}
}

func TopoMakeFaceFromCone(f Cone) *Face {
	return &Face{inner: &innerFace{val: C.topo_face_make_face_from_cone(f.val)}}
}

func TopoMakeFaceFromSphere(f Sphere) *Face {
	return &Face{inner: &innerFace{val: C.topo_face_make_face_from_sphere(f.val)}}
}

func TopoMakeFaceFromTorus(f Torus) *Face {
	return &Face{inner: &innerFace{val: C.topo_face_make_face_from_torus(f.val)}}
}

func TopoMakeFaceFromSurface(S *GeomSurface, TolDegen float64) *Face {
	return &Face{inner: &innerFace{val: C.topo_face_make_face_from_surface(S.inner.geom, C.double(TolDegen))}}
}

func TopoMakeFaceFromPlaneParm(f Plane, UMin, UMax, VMin, VMax float64) *Face {
	return &Face{inner: &innerFace{val: C.topo_face_make_face_from_plane_p(f.val, C.double(UMin), C.double(UMax), C.double(VMin), C.double(VMax))}}
}

func TopoMakeFaceFromCylinderParm(f Cylinder, UMin, UMax, VMin, VMax float64) *Face {
	return &Face{inner: &innerFace{val: C.topo_face_make_face_from_cylinder_p(f.val, C.double(UMin), C.double(UMax), C.double(VMin), C.double(VMax))}}
}

func TopoMakeFaceFromConeParm(f Cone, UMin, UMax, VMin, VMax float64) *Face {
	return &Face{inner: &innerFace{val: C.topo_face_make_face_from_cone_p(f.val, C.double(UMin), C.double(UMax), C.double(VMin), C.double(VMax))}}
}

func TopoMakeFaceFromSphereParm(f Sphere, UMin, UMax, VMin, VMax float64) *Face {
	return &Face{inner: &innerFace{val: C.topo_face_make_face_from_sphere_p(f.val, C.double(UMin), C.double(UMax), C.double(VMin), C.double(VMax))}}
}

func TopoMakeFaceFromTorusParm(f Torus, UMin, UMax, VMin, VMax float64) *Face {
	return &Face{inner: &innerFace{val: C.topo_face_make_face_from_torus_p(f.val, C.double(UMin), C.double(UMax), C.double(VMin), C.double(VMax))}}
}

func TopoMakeFaceFromSurfaceParm(S *GeomSurface, UMin, UMax, VMin, VMax, TolDegen float64) *Face {
	return &Face{inner: &innerFace{val: C.topo_face_make_face_from_surface_p(S.inner.geom, C.double(UMin), C.double(UMax), C.double(VMin), C.double(VMax), C.double(TolDegen))}}
}

func TopoMakeFaceFromWire(w Wire, OnlyPlane bool) *Face {
	return &Face{inner: &innerFace{val: C.topo_face_make_face_from_wire_onlyplane(w.inner.val, C.bool(OnlyPlane))}}
}

func TopoMakeFaceFromPlaneWire(p Plane, w Wire, Inside bool) *Face {
	return &Face{inner: &innerFace{val: C.topo_face_make_face_from_plane_wire(p.val, w.inner.val, C.bool(Inside))}}
}

func TopoMakeFaceFromCylinderWire(p Cylinder, w Wire, Inside bool) *Face {
	return &Face{inner: &innerFace{val: C.topo_face_make_face_from_cylinder_wire(p.val, w.inner.val, C.bool(Inside))}}
}

func TopoMakeFaceFromConeWire(p Cone, w Wire, Inside bool) *Face {
	return &Face{inner: &innerFace{val: C.topo_face_make_face_from_cone_wire(p.val, w.inner.val, C.bool(Inside))}}
}

func TopoMakeFaceFromSphereWire(p Sphere, w Wire, Inside bool) *Face {
	return &Face{inner: &innerFace{val: C.topo_face_make_face_from_sphere_wire(p.val, w.inner.val, C.bool(Inside))}}
}

func TopoMakeFaceFromTorusWire(p Torus, w Wire, Inside bool) *Face {
	return &Face{inner: &innerFace{val: C.topo_face_make_face_from_torus_wire(p.val, w.inner.val, C.bool(Inside))}}
}

func TopoMakeFaceFromSurfaceWire(S *GeomSurface, w Wire, Inside bool) *Face {
	return &Face{inner: &innerFace{val: C.topo_face_make_face_from_surface_wire(S.inner.geom, w.inner.val, C.bool(Inside))}}
}

func TopoMakeFaceFromFaceWire(f *Face, w Wire) *Face {
	return &Face{inner: &innerFace{val: C.topo_face_make_face_from_face_wire(f.inner.val, w.inner.val)}}
}

func TopoMakeFaceFromWires(ws []Wire) *Face {
	cws := make([]C.struct__topo_wire_t, len(ws))
	for i := range ws {
		cws[i] = ws[i].inner.val
	}
	return &Face{inner: &innerFace{val: C.topo_face_make_face_from_wire(&cws[0], C.int(len(ws)))}}
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
	return &Face{inner: &innerFace{val: C.topo_face_make_face_from_egdes(&cws[0], C.int(len(ws)), &cpts[0], C.int(len(pts)))}}
}

func TopoMakeFaceFromPoints(pts []Point3) *Face {
	cpts := make([]C.struct__pnt3d_t, len(pts))
	for i := range pts {
		cpts[i] = pts[i].val
	}
	return &Face{inner: &innerFace{val: C.topo_face_make_face_from_points(&cpts[0], C.int(len(pts)))}}
}

type Shell struct {
	inner *innerShell
}

type innerShell struct {
	val C.struct__topo_shell_t
}

func TopoMakeShell() *Shell {
	p := &Shell{inner: &innerShell{val: C.topo_make_shell()}}
	runtime.SetFinalizer(p, (*Shell).free)
	return p
}

func (s *Shell) Sweep(spine *Wire, profiles []Wire, cornerMode int) int {
	cshp := make([]C.struct__topo_wire_t, len(profiles))
	for i := range profiles {
		cshp[i] = profiles[i].inner.val
	}
	return int(C.topo_shell_sweep_wire(s.inner.val, spine.inner.val, &cshp[0], C.int(len(profiles)), C.int(cornerMode)))
}

func (t *Shell) ToShape() *Shape {
	return &Shape{inner: &innerShape{val: C.topo_shape_share(t.inner.val.shp)}}
}

func (t *Shell) free() {
	C.topo_shell_free(t.inner.val)
}

func TopoMakeShellFromSurface(S *GeomSurface, Segment bool) *Shell {
	return &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_surface(S.inner.geom, C.bool(Segment))}}
}

func TopoMakeShellFromSurfaceFromSurfaceParm(S *GeomSurface, UMin, UMax, VMin, VMax float64, Segment bool) *Shell {
	return &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_surface_p(S.inner.geom, C.double(UMin), C.double(UMax), C.double(VMin), C.double(VMax), C.bool(Segment))}}
}

func TopoMakeShellFromBox(dx, dy, dz float64) *Shell {
	return &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_box(C.double(dx), C.double(dy), C.double(dz))}}
}

func TopoMakeShellFromBoxPoint(p Point3, dx, dy, dz float64) *Shell {
	return &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_box_point(p.val, C.double(dx), C.double(dy), C.double(dz))}}
}

func TopoMakeShellFromBoxTwoPoint(p1, p2 Point3) *Shell {
	return &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_box_two_point(p1.val, p2.val)}}
}

func TopoMakeShellFromBoxAxis2(a Axis2, dx, dy, dz float64) *Shell {
	return &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_box_axis2(a.val, C.double(dx), C.double(dy), C.double(dz))}}
}

func TopoMakeShellFromCylinder(R, H float64) *Shell {
	return &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_cylinder(C.double(R), C.double(H))}}
}

func TopoMakeShellFromCylinderAngle(R, H, Angle float64) *Shell {
	return &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_cylinder_angle(C.double(R), C.double(H), C.double(Angle))}}
}

func TopoMakeShellFromCylinderAxis2(a Axis2, R, H float64) *Shell {
	return &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_cylinder_axis2(a.val, C.double(R), C.double(H))}}
}

func TopoMakeShellFromCylinderAxis2Angle(a Axis2, R, H, Angle float64) *Shell {
	return &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_cylinder_axis2_angle(a.val, C.double(R), C.double(H), C.double(Angle))}}
}

func TopoMakeShellFromCone(R1, R2, H float64) *Shell {
	return &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_cone(C.double(R1), C.double(R2), C.double(H))}}
}

func TopoMakeShellFromConeAngle(R1, R2, H, Angle float64) *Shell {
	return &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_cone_angle(C.double(R1), C.double(R2), C.double(H), C.double(Angle))}}
}

func TopoMakeShellFromConeAxis2(a Axis2, R1, R2, H float64) *Shell {
	return &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_cone_axis2(a.val, C.double(R1), C.double(R2), C.double(H))}}
}

func TopoMakeShellFromConeAxis2Angle(a Axis2, R1, R2, H, Angle float64) *Shell {
	return &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_cone_axis2_angle(a.val, C.double(R1), C.double(R2), C.double(H), C.double(Angle))}}
}

func TopoMakeShellFromRevolution(m *GeomCurve) *Shell {
	return &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_revolution(m.inner.geom)}}
}

func TopoMakeShellFromRevolutionAngle(m *GeomCurve, Angle float64) *Shell {
	return &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_revolution_angle(m.inner.geom, C.double(Angle))}}
}

func TopoMakeShellFromRevolutionLimit(m *GeomCurve, VMin, VMax float64) *Shell {
	return &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_revolution_limit(m.inner.geom, C.double(VMin), C.double(VMax))}}
}

func TopoMakeShellFromRevolutionLimitAngle(m *GeomCurve, VMin, VMax, Angle float64) *Shell {
	return &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_revolution_limit_angle(m.inner.geom, C.double(VMin), C.double(VMax), C.double(Angle))}}
}

func TopoMakeShellFromRevolutionAxis2(a Axis2, m *GeomCurve) *Shell {
	return &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_revolution_axis2(a.val, m.inner.geom)}}
}

func TopoMakeShellFromRevolutionAxis2Angle(a Axis2, m *GeomCurve, Angle float64) *Shell {
	return &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_revolution_axis2_angle(a.val, m.inner.geom, C.double(Angle))}}
}

func TopoMakeShellFromRevolutionAxis2Limit(a Axis2, m *GeomCurve, VMin, VMax float64) *Shell {
	return &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_revolution_axis2_limit(a.val, m.inner.geom, C.double(VMin), C.double(VMax))}}
}

func TopoMakeShellFromRevolutionAxis2LimitAngle(a Axis2, m *GeomCurve, VMin, VMax, Angle float64) *Shell {
	return &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_revolution_axis2_limit_angle(a.val, m.inner.geom, C.double(VMin), C.double(VMax), C.double(Angle))}}
}

func TopoMakeShellFromSpere(R float64) *Shell {
	return &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_sphere(C.double(R))}}
}

func TopoMakeShellFromSpereAngle(R float64, Angle float64) *Shell {
	return &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_sphere_angle(C.double(R), C.double(Angle))}}
}

func TopoMakeShellFromSpereTwoAngle(R float64, Angle1, Angle2 float64) *Shell {
	return &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_sphere_two_angle(C.double(R), C.double(Angle1), C.double(Angle2))}}
}

func TopoMakeShellFromSpereThreeAngle(R float64, Angle1, Angle2, Angle3 float64) *Shell {
	return &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_sphere_three_angle(C.double(R), C.double(Angle1), C.double(Angle2), C.double(Angle3))}}
}

func TopoMakeShellFromSpereCenterRaduis(Center Point3, R float64) *Shell {
	return &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_sphere_center_raduis(Center.val, C.double(R))}}
}

func TopoMakeShellFromSpereCenterAngle(Center Point3, R, Angle float64) *Shell {
	return &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_sphere_center_angle(Center.val, C.double(R), C.double(Angle))}}
}

func TopoMakeShellFromSpereCenterTwoAngle(Center Point3, R, Angle1, Angle2 float64) *Shell {
	return &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_sphere_center_two_angle(Center.val, C.double(R), C.double(Angle1), C.double(Angle2))}}
}

func TopoMakeShellFromSpereCenterThreeAngle(Center Point3, R, Angle1, Angle2, Angle3 float64) *Shell {
	return &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_sphere_center_three_angle(Center.val, C.double(R), C.double(Angle1), C.double(Angle2), C.double(Angle3))}}
}

func TopoMakeShellFromSpereAxis2(a Axis2, R float64) *Shell {
	return &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_sphere_axis2(a.val, C.double(R))}}
}

func TopoMakeShellFromSpereAxis2Angle(a Axis2, R, Angle float64) *Shell {
	return &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_sphere_axis2_raduis(a.val, C.double(R), C.double(Angle))}}
}

func TopoMakeShellFromSpereAxis2TwoAngle(a Axis2, R, Angle1, Angle2 float64) *Shell {
	return &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_sphere_axis2_two_angle(a.val, C.double(R), C.double(Angle1), C.double(Angle2))}}
}

func TopoMakeShellFromSpereAxis2ThreeAngle(a Axis2, R, Angle1, Angle2, Angle3 float64) *Shell {
	return &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_sphere_axis2_three_angle(a.val, C.double(R), C.double(Angle1), C.double(Angle2), C.double(Angle3))}}
}

func TopoMakeShellFromTorus(R1, R2 float64) *Shell {
	return &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_torus(C.double(R1), C.double(R2))}}
}

func TopoMakeShellFromTorusAngle(R1, R2, Angle float64) *Shell {
	return &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_torus_angle(C.double(R1), C.double(R2), C.double(Angle))}}
}

func TopoMakeShellFromTorusTwoAngle(R1, R2, Angle1, Angle2 float64) *Shell {
	return &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_torus_two_angle(C.double(R1), C.double(R2), C.double(Angle1), C.double(Angle2))}}
}

func TopoMakeShellFromTorusThreeAngle(R1, R2, Angle1, Angle2, Angle3 float64) *Shell {
	return &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_torus_three_angle(C.double(R1), C.double(R2), C.double(Angle1), C.double(Angle2), C.double(Angle3))}}
}

func TopoMakeShellFromTorusAxis2(a Axis2, R1, R2 float64) *Shell {
	return &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_torus_axis2(a.val, C.double(R1), C.double(R2))}}
}

func TopoMakeShellFromTorusAxis2Angle(a Axis2, R1, R2, Angle float64) *Shell {
	return &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_torus_axis2_angle(a.val, C.double(R1), C.double(R2), C.double(Angle))}}
}

func TopoMakeShellFromTorusAxis2TwoAngle(a Axis2, R1, R2, Angle1, Angle2 float64) *Shell {
	return &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_torus_axis2_two_angle(a.val, C.double(R1), C.double(R2), C.double(Angle1), C.double(Angle2))}}
}

func TopoMakeShellFromTorusAxis2ThreeAngle(a Axis2, R1, R2, Angle1, Angle2, Angle3 float64) *Shell {
	return &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_torus_axis2_three_angle(a.val, C.double(R1), C.double(R2), C.double(Angle1), C.double(Angle2), C.double(Angle3))}}
}

func TopoMakeShellFromWedge(dx, dy, dz, ltx float64) *Shell {
	return &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_wedge(C.double(dx), C.double(dy), C.double(dz), C.double(ltx))}}
}

func TopoMakeShellFromWedgeAxis2(a Axis2, dx, dy, dz, ltx float64) *Shell {
	return &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_wedge_axis2(a.val, C.double(dx), C.double(dy), C.double(dz), C.double(ltx))}}
}

func TopoMakeShellFromWedgeLimit(dx, dy, dz, xmin, zmin, xmax, zmax float64) *Shell {
	return &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_wedge_limit(C.double(dx), C.double(dy), C.double(dz), C.double(xmin), C.double(zmin), C.double(xmax), C.double(zmax))}}
}

func TopoMakeShellFromWedgeAxis2Limit(a Axis2, dx, dy, dz, xmin, zmin, xmax, zmax float64) *Shell {
	return &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_wedge_axis2_limit(a.val, C.double(dx), C.double(dy), C.double(dz), C.double(xmin), C.double(zmin), C.double(xmax), C.double(zmax))}}
}

type Solid struct {
	inner *innerSolid
}

type innerSolid struct {
	val C.struct__topo_solid_t
}

func TopoMakeSolid() *Solid {
	p := &Solid{inner: &innerSolid{val: C.topo_make_solid()}}
	runtime.SetFinalizer(p, (*Solid).free)
	return p
}

func (s *Solid) IsNull() bool {
	return bool(C.topo_shape_is_null(s.inner.val.shp))
}

func (s *Solid) IsValid() bool {
	return bool(C.topo_shape_is_valid(s.inner.val.shp))
}

func (s *Solid) Equals(e *Shape) bool {
	return bool(C.topo_shape_equals(s.inner.val.shp, e.inner.val))
}

func (s *Solid) Type() int {
	return int(C.topo_shape_type(s.inner.val.shp))
}

func (s *Solid) BBox() BBox {
	return BBox{val: C.topo_shape_bounding_box(s.inner.val.shp)}
}

func (s *Solid) Hash() int {
	return int(C.topo_shape_hash_code(s.inner.val.shp))
}

func (s *Solid) Transform(t Trsf) int {
	return int(C.topo_shape_transform(s.inner.val.shp, t.val))
}

func (s *Solid) Translate(v Vector3) int {
	return int(C.topo_shape_translate(s.inner.val.shp, v.val))
}

func (s *Solid) RotateFromPoint(angle float64, p1, p2 Point3) int {
	return int(C.topo_shape_rotate_from_two_point(s.inner.val.shp, C.double(angle), p1.val, p2.val))
}

func (s *Solid) RotateFromAxis1(angle float64, a Axis1) int {
	return int(C.topo_shape_rotate_from_axis1(s.inner.val.shp, C.double(angle), a.val))
}

func (s *Solid) RotateFromQuaternion(q Quaternion) int {
	return int(C.topo_shape_rotate_from_quaternion(s.inner.val.shp, q.val))
}

func (s *Solid) Scale(angle float64, a Point3) int {
	return int(C.topo_shape_scale(s.inner.val.shp, C.double(angle), a.val))
}

func (s *Solid) MirrorFromPointNorm(pnt, ner Point3) int {
	return int(C.topo_shape_mirror_from_point_norm(s.inner.val.shp, pnt.val, ner.val))
}

func (s *Solid) MirrorFromAxis1(a Axis1) int {
	return int(C.topo_shape_mirror_from_axis1(s.inner.val.shp, a.val))
}

func (s *Solid) MirrorFromAxis2(a Axis2) int {
	return int(C.topo_shape_mirror_from_axis2(s.inner.val.shp, a.val))
}

func (s *Solid) Transformed(t Trsf) *Solid {
	var val C.struct__topo_solid_t
	val.shp = C.topo_shape_transformed(s.inner.val.shp, t.val)
	return &Solid{inner: &innerSolid{val: val}}
}

func (s *Solid) Translated(v Vector3) *Solid {
	var val C.struct__topo_solid_t
	val.shp = C.topo_shape_translated(s.inner.val.shp, v.val)
	return &Solid{inner: &innerSolid{val: val}}
}

func (s *Solid) RotatedFromPoint(angle float64, p1, p2 Point3) *Solid {
	var val C.struct__topo_solid_t
	val.shp = C.topo_shape_rotated_from_two_point(s.inner.val.shp, C.double(angle), p1.val, p2.val)
	return &Solid{inner: &innerSolid{val: val}}
}

func (s *Solid) RotatedFromAxis1(angle float64, a Axis1) *Solid {
	var val C.struct__topo_solid_t
	val.shp = C.topo_shape_rotated_from_axis1(s.inner.val.shp, C.double(angle), a.val)
	return &Solid{inner: &innerSolid{val: val}}
}

func (s *Solid) RotatedFromQuaternion(q Quaternion) *Solid {
	var val C.struct__topo_solid_t
	val.shp = C.topo_shape_rotated_from_quaternion(s.inner.val.shp, q.val)
	return &Solid{inner: &innerSolid{val: val}}
}

func (s *Solid) Scaled(angle float64, a Point3) *Solid {
	var val C.struct__topo_solid_t
	val.shp = C.topo_shape_scaled(s.inner.val.shp, C.double(angle), a.val)
	return &Solid{inner: &innerSolid{val: val}}
}

func (s *Solid) MirroredFromPointNorm(pnt, ner Point3) *Solid {
	var val C.struct__topo_solid_t
	val.shp = C.topo_shape_mirrored_from_point_norm(s.inner.val.shp, pnt.val, ner.val)
	return &Solid{inner: &innerSolid{val: val}}
}

func (s *Solid) MirroredFromAxis1(a Axis1) *Solid {
	var val C.struct__topo_solid_t
	val.shp = C.topo_shape_mirrored_from_axis1(s.inner.val.shp, a.val)
	return &Solid{inner: &innerSolid{val: val}}
}

func (s *Solid) MirroredFromAxis2(a Axis2) *Solid {
	var val C.struct__topo_solid_t
	val.shp = C.topo_shape_mirrored_from_axis2(s.inner.val.shp, a.val)
	return &Solid{inner: &innerSolid{val: val}}
}

func (s *Solid) GetOrientation() int {
	return int(C.topo_shape_get_orientation(s.inner.val.shp))
}

func (s *Solid) SetOrientation(t int) {
	C.topo_shape_set_orientation(s.inner.val.shp, C.int(t))
}

func (s *Solid) GetLocation() *Location {
	return &Location{inner: &innerLocation{val: C.topo_shape_get_location(s.inner.val.shp)}}
}

func (s *Solid) SetLocation(t *Location) {
	C.topo_shape_set_location(s.inner.val.shp, t.inner.val)
}

func (s *Solid) FixShape() bool {
	return bool(C.topo_shape_fix_shape(s.inner.val.shp))
}

func (s *Solid) Copy() *Solid {
	var val C.struct__topo_solid_t
	val.shp = C.topo_shape_copy(s.inner.val.shp)
	return &Solid{inner: &innerSolid{val: val}}
}

func (s *Solid) Mesh(m *MeshReceiver, tolerance, deflection, angle float64) {
	C.topo_shape_mesh(s.inner.val.shp, m.inner.val, C.double(tolerance), C.double(deflection), C.double(angle))
}

func (s *Solid) SetSurfaceColour(c Color) {
	C.topo_shape_set_surface_colour(s.inner.val.shp, c.val)
}

func (s *Solid) SetCurveColour(c Color) {
	C.topo_shape_set_curve_colour(s.inner.val.shp, c.val)
}

func (s *Solid) SetLabel(l string) {
	str := C.CString(l)
	defer C.free(unsafe.Pointer(str))
	C.topo_shape_set_label(s.inner.val.shp, str)
}

func (s *Solid) GetSurfaceColour() Color {
	return Color{val: C.topo_shape_get_surface_colour(s.inner.val.shp)}
}

func (s *Solid) GetCurveColour() Color {
	return Color{val: C.topo_shape_get_surface_colour(s.inner.val.shp)}
}

func (s *Solid) GetLabel() string {
	return C.GoString(C.topo_shape_get_label(s.inner.val.shp))
}

func (s *Solid) NumSolids() int {
	return int(C.topo_solid_num_solids(s.inner.val))
}

func (s *Solid) NumFaces() int {
	return int(C.topo_solid_num_faces(s.inner.val))
}

func (s *Solid) Area() float64 {
	return float64(C.topo_solid_area(s.inner.val))
}

func (s *Solid) Volume() float64 {
	return float64(C.topo_solid_volume(s.inner.val))
}

func (s *Solid) Inertia() BBox {
	return BBox{val: C.topo_solid_inertia(s.inner.val)}
}

func (s *Solid) CentreOfMass() Point3 {
	return Point3{val: C.topo_solid_centre_of_mass(s.inner.val)}
}

func (s *Solid) Extrude(f *Face, p1, p2 Point3) int {
	return int(C.topo_solid_extrude(s.inner.val, f.inner.val, p1.val, p2.val))
}

func (s *Solid) ExtrudeFromDir(f *Face, d Vector3) int {
	return int(C.topo_solid_extrude_from_dir(s.inner.val, f.inner.val, d.val))
}

func (s *Solid) Revolve(f *Face, p1, p2 Point3, angle float64) int {
	return int(C.topo_solid_revolve(s.inner.val, f.inner.val, p1.val, p2.val, C.double(angle)))
}

func (s *Solid) Loft(profiles []Shape, ruled bool, tolerance float64) int {
	cshp := make([]*C.struct__topo_shape_t, len(profiles))
	for i := range profiles {
		cshp[i] = profiles[i].inner.val
	}
	return int(C.topo_solid_loft(s.inner.val, &cshp[0], C.int(len(profiles)), C.bool(ruled), C.double(tolerance)))
}

func (s *Solid) Pipe(f *Face, w Wire) int {
	return int(C.topo_solid_pipe(s.inner.val, f.inner.val, w.inner.val))
}

func (s *Solid) Sweep(spine *Wire, profiles []Wire, cornerMode int) int {
	cshp := make([]C.struct__topo_wire_t, len(profiles))
	for i := range profiles {
		cshp[i] = profiles[i].inner.val
	}
	return int(C.topo_solid_sweep_wire(s.inner.val, spine.inner.val, &cshp[0], C.int(len(profiles)), C.int(cornerMode)))
}

func (s *Solid) Boolean(tool *Solid, op int) int {
	return int(C.topo_solid_boolean(s.inner.val, tool.inner.val, C.int(op)))
}

func (s *Solid) Fillet(edges []Edge, radius []float64) int {
	cshp := make([]C.struct__topo_edge_t, len(edges))
	for i := range edges {
		cshp[i] = edges[i].inner.val
	}
	return int(C.topo_solid_fillet(s.inner.val, &cshp[0], C.int(len(edges)), (*C.double)(unsafe.Pointer(&radius[0])), C.int(len(radius))))
}

func (s *Solid) Chamfer(edges []Edge, distances []float64) int {
	cshp := make([]C.struct__topo_edge_t, len(edges))
	for i := range edges {
		cshp[i] = edges[i].inner.val
	}
	return int(C.topo_solid_chamfer(s.inner.val, &cshp[0], C.int(len(edges)), (*C.double)(unsafe.Pointer(&distances[0])), C.int(len(distances))))
}

func (s *Solid) Shelling(faces []Face, offset, tolerance float64) int {
	cshp := make([]C.struct__topo_face_t, len(faces))
	for i := range faces {
		cshp[i] = faces[i].inner.val
	}
	return int(C.topo_solid_shelling(s.inner.val, &cshp[0], C.int(len(faces)), C.double(offset), C.double(tolerance)))
}

func (s *Solid) Offset(f *Face, offset, tolerance float64) int {
	return int(C.topo_solid_offset(s.inner.val, f.inner.val, C.double(offset), C.double(tolerance)))
}

func (s *Solid) Draft(faces []Face, d Dir3, angle float64, p Plane) int {
	fs := make([]C.struct__topo_face_t, len(faces))
	for i := range faces {
		fs[i] = faces[i].inner.val
	}
	return int(C.topo_solid_draft(s.inner.val, &fs[0], C.int(len(faces)), d.val, C.double(angle), p.val))
}

func (s *Solid) EvolvedFromFace(Spine *Face, Profil *Wire) int {
	return int(C.topo_solid_evolved_from_face(s.inner.val, Spine.inner.val, Profil.inner.val))
}

func (s *Solid) EvolvedFromWire(Spine *Wire, Profil *Wire) int {
	return int(C.topo_solid_evolved_from_wire(s.inner.val, Spine.inner.val, Profil.inner.val))
}

func (s *Solid) FeatPrism(f *Face, d Dir3, height float64, fuse bool) int {
	return int(C.topo_solid_feat_prism(s.inner.val, f.inner.val, d.val, C.double(height), C.bool(fuse)))
}

func (s *Solid) FeatPrismForRange(f *Face, d Dir3, from, end Face, fuse bool) int {
	return int(C.topo_solid_feat_prism_for_range(s.inner.val, f.inner.val, d.val, from.inner.val, end.inner.val, C.bool(fuse)))
}

func (s *Solid) FeatPrismForUntil(f *Face, d Dir3, until Face, fuse bool) int {
	return int(C.topo_solid_feat_prism_for_until(s.inner.val, f.inner.val, d.val, until.inner.val, C.bool(fuse)))
}

func (s *Solid) DraftPrism(f *Face, angle, height float64, fuse bool) int {
	return int(C.topo_solid_feat_draft_prism(s.inner.val, f.inner.val, C.double(angle), C.double(height), C.bool(fuse)))
}

func (s *Solid) DraftPrismForRange(f *Face, angle float64, from, end Face, fuse bool) int {
	return int(C.topo_solid_feat_draft_prism_for_range(s.inner.val, f.inner.val, C.double(angle), from.inner.val, end.inner.val, C.bool(fuse)))
}

func (s *Solid) DraftPrismForUntil(f *Face, angle float64, until Face, fuse bool) int {
	return int(C.topo_solid_feat_draft_prism_for_until(s.inner.val, f.inner.val, C.double(angle), until.inner.val, C.bool(fuse)))
}

func (s *Solid) RevolForRange(f *Face, a Axis1, from, end Face, fuse bool) int {
	return int(C.topo_solid_feat_revol_for_range(s.inner.val, f.inner.val, a.val, from.inner.val, end.inner.val, C.bool(fuse)))
}

func (s *Solid) RevolForUntil(f *Face, a Axis1, until Face, fuse bool) int {
	return int(C.topo_solid_feat_revol_for_until(s.inner.val, f.inner.val, a.val, until.inner.val, C.bool(fuse)))
}

func (s *Solid) PipeForRange(f *Face, w *Wire, from, end Face, fuse bool) int {
	return int(C.topo_solid_feat_pipe_for_range(s.inner.val, f.inner.val, w.inner.val, from.inner.val, end.inner.val, C.bool(fuse)))
}

func (s *Solid) PipeForUntil(f *Face, w *Wire, until Face, fuse bool) int {
	return int(C.topo_solid_feat_pipe_for_until(s.inner.val, f.inner.val, w.inner.val, until.inner.val, C.bool(fuse)))
}

func (s *Solid) LinearForm(w *Wire, p *GeomPlane, d, d1 Dir3, fuse bool) int {
	return int(C.topo_solid_linear_form(s.inner.val, w.inner.val, p.inner.geom, d.val, d1.val, C.bool(fuse)))
}

func (s *Solid) RevolutionForm(w *Wire, p *GeomPlane, a Axis1, h1, h2 float64, fuse bool) int {
	return int(C.topo_solid_revolution_form(s.inner.val, w.inner.val, p.inner.geom, a.val, C.double(h1), C.double(h2), C.bool(fuse)))
}

func (s *Solid) SectionFace(pnt, nor Point3) *Face {
	return &Face{inner: &innerFace{val: C.topo_solid_section_face(s.inner.val, pnt.val, nor.val)}}
}

func (s *Solid) ConvertToNurbs() int {
	return int(C.topo_solid_convert_to_nurbs(s.inner.val))
}

func (t *Solid) ToShape() *Shape {
	return &Shape{inner: &innerShape{val: C.topo_shape_share(t.inner.val.shp)}}
}

func (t *Solid) free() {
	C.topo_solid_free(t.inner.val)
}

func TopoMakeSolidFromCompSolid(S *CompSolid) *Solid {
	return &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_comp_solid(S.inner.val)}}
}

func TopoMakeSolidFromShell(S *Shell) *Solid {
	return &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_shell(S.inner.val)}}
}

func TopoMakeSolidFromTwoShell(S1, S2 *Shell) *Solid {
	return &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_two_shell(S1.inner.val, S2.inner.val)}}
}

func TopoMakeSolidFromThreeShell(S1, S2, S3 *Shell) *Solid {
	return &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_three_shell(S1.inner.val, S2.inner.val, S3.inner.val)}}
}

func TopoMakeSolidFromShells(S []Shell) *Solid {
	shls := make([]C.struct__topo_shell_t, len(S))
	for i := range S {
		shls[i] = S[i].inner.val
	}
	return &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_shells(&shls[0], C.int(len(S)))}}
}

func TopoMakeSolidFromSolid(S *Solid) *Solid {
	return &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_solid(S.inner.val)}}
}

func TopoMakeSolidFromSolidShell(S *Solid, sl *Shell) *Solid {
	return &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_solid_shell(S.inner.val, sl.inner.val)}}
}

func TopoMakeSolidFromFaces(S []Face, tolerance float64) *Solid {
	shls := make([]C.struct__topo_face_t, len(S))
	for i := range S {
		shls[i] = S[i].inner.val
	}
	return &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_faces(&shls[0], C.int(len(S)), C.double(tolerance))}}
}

func TopoMakeSolidFromBox(dx, dy, dz float64) *Solid {
	return &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_box(C.double(dx), C.double(dy), C.double(dz))}}
}

func TopoMakeSolidFromBoxPoint(p Point3, dx, dy, dz float64) *Solid {
	return &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_box_point(p.val, C.double(dx), C.double(dy), C.double(dz))}}
}

func TopoMakeSolidFromBoxTwoPoint(p1, p2 Point3) *Solid {
	return &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_box_two_point(p1.val, p2.val)}}
}

func TopoMakeSolidFromBoxAxis2(a Axis2, dx, dy, dz float64) *Solid {
	return &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_box_axis2(a.val, C.double(dx), C.double(dy), C.double(dz))}}
}

func TopoMakeSolidFromCylinder(R, H float64) *Solid {
	return &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_cylinder(C.double(R), C.double(H))}}
}

func TopoMakeSolidFromCylinderAngle(R, H, Angle float64) *Solid {
	return &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_cylinder_angle(C.double(R), C.double(H), C.double(Angle))}}
}

func TopoMakeSolidFromCylinderAxis2(a Axis2, R, H float64) *Solid {
	return &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_cylinder_axis2(a.val, C.double(R), C.double(H))}}
}

func TopoMakeSolidFromCylinderAxis2Angle(a Axis2, R, H, Angle float64) *Solid {
	return &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_cylinder_axis2_angle(a.val, C.double(R), C.double(H), C.double(Angle))}}
}

func TopoMakeSolidFromCone(R1, R2, H float64) *Solid {
	return &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_cone(C.double(R1), C.double(R2), C.double(H))}}
}

func TopoMakeSolidFromConeAngle(R1, R2, H, Angle float64) *Solid {
	return &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_cone_angle(C.double(R1), C.double(R2), C.double(H), C.double(Angle))}}
}

func TopoMakeSolidFromConeAxis2(a Axis2, R1, R2, H float64) *Solid {
	return &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_cone_axis2(a.val, C.double(R1), C.double(R2), C.double(H))}}
}

func TopoMakeSolidFromConeAxis2Angle(a Axis2, R1, R2, H, Angle float64) *Solid {
	return &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_cone_axis2_angle(a.val, C.double(R1), C.double(R2), C.double(H), C.double(Angle))}}
}

func TopoMakeSolidFroRevolution(Meridian *GeomCurve) *Solid {
	return &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_revolution(Meridian.inner.geom)}}
}

func TopoMakeSolidFroRevolutionAngle(Meridian *GeomCurve, angle float64) *Solid {
	return &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_revolution_angle(Meridian.inner.geom, C.double(angle))}}
}

func TopoMakeSolidFroRevolutionLimit(Meridian *GeomCurve, VMin, VMax float64) *Solid {
	return &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_revolution_limit(Meridian.inner.geom, C.double(VMin), C.double(VMax))}}
}

func TopoMakeSolidFroRevolutionLimitAngle(Meridian *GeomCurve, VMin, VMax, angle float64) *Solid {
	return &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_revolution_limit_angle(Meridian.inner.geom, C.double(VMin), C.double(VMax), C.double(angle))}}
}

func TopoMakeSolidFroRevolutionAxis2(a Axis2, Meridian *GeomCurve) *Solid {
	return &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_revolution_axis2(a.val, Meridian.inner.geom)}}
}

func TopoMakeSolidFroRevolutionAxis2Angle(a Axis2, Meridian *GeomCurve, angle float64) *Solid {
	return &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_revolution_axis2_angle(a.val, Meridian.inner.geom, C.double(angle))}}
}

func TopoMakeSolidFroRevolutionAxis2Limit(a Axis2, Meridian *GeomCurve, VMin, VMax float64) *Solid {
	return &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_revolution_axis2_limit(a.val, Meridian.inner.geom, C.double(VMin), C.double(VMax))}}
}

func TopoMakeSolidFroRevolutionAxis2LimitAngle(a Axis2, Meridian *GeomCurve, VMin, VMax, angle float64) *Solid {
	return &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_revolution_axis2_limit_angle(a.val, Meridian.inner.geom, C.double(VMin), C.double(VMax), C.double(angle))}}
}

func TopoMakeSolidFromSphere(R float64) *Solid {
	return &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_sphere(C.double(R))}}
}

func TopoMakeSolidFromSphereAngle(R, angle float64) *Solid {
	return &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_sphere_angle(C.double(R), C.double(angle))}}
}

func TopoMakeSolidFromSphereTwoAngle(R, angle1, angle2 float64) *Solid {
	return &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_sphere_two_angle(C.double(R), C.double(angle1), C.double(angle2))}}
}

func TopoMakeSolidFromSphereThreeAngle(R, angle1, angle2, angle3 float64) *Solid {
	return &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_sphere_three_angle(C.double(R), C.double(angle1), C.double(angle2), C.double(angle3))}}
}

func TopoMakeSolidFromSphereCenterAngle(c Point3, R, angle float64) *Solid {
	return &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_sphere_center_angle(c.val, C.double(R), C.double(angle))}}
}

func TopoMakeSolidFromSphereCenterTwoAngle(c Point3, R, angle1, angle2 float64) *Solid {
	return &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_sphere_center_two_angle(c.val, C.double(R), C.double(angle1), C.double(angle2))}}
}

func TopoMakeSolidFromSphereCenterThreeAngle(c Point3, R, angle1, angle2, angle3 float64) *Solid {
	return &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_sphere_center_three_angle(c.val, C.double(R), C.double(angle1), C.double(angle2), C.double(angle3))}}
}

func TopoMakeSolidFromSphereAxis2(a Axis2, R float64) *Solid {
	return &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_sphere_axis2(a.val, C.double(R))}}
}

func TopoMakeSolidFromSphereAxis2Angle(a Axis2, R, angle float64) *Solid {
	return &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_sphere_axis2_angle(a.val, C.double(R), C.double(angle))}}
}

func TopoMakeSolidFromSphereAxis2TwoAngle(a Axis2, R, angle1, angle2 float64) *Solid {
	return &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_sphere_axis2_two_angle(a.val, C.double(R), C.double(angle1), C.double(angle2))}}
}

func TopoMakeSolidFromSphereAxis2ThreeAngle(a Axis2, R, angle1, angle2, angle3 float64) *Solid {
	return &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_sphere_axis2_three_angle(a.val, C.double(R), C.double(angle1), C.double(angle2), C.double(angle3))}}
}

func TopoMakeSolidFromSphereTorus(R1, R2 float64) *Solid {
	return &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_torus(C.double(R1), C.double(R2))}}
}

func TopoMakeSolidFromSphereTorusAngle(R1, R2, angle float64) *Solid {
	return &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_torus_angle(C.double(R1), C.double(R2), C.double(angle))}}
}

func TopoMakeSolidFromSphereTorusTwoAngle(R1, R2, angle1, angle2 float64) *Solid {
	return &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_torus_two_angle(C.double(R1), C.double(R2), C.double(angle1), C.double(angle2))}}
}

func TopoMakeSolidFromSphereTorusThreeAngle(R1, R2, angle1, angle2, angle3 float64) *Solid {
	return &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_torus_three_angle(C.double(R1), C.double(R2), C.double(angle1), C.double(angle2), C.double(angle3))}}
}

func TopoMakeSolidFromSphereTorusAxis2(a Axis2, R1, R2 float64) *Solid {
	return &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_torus_axis2(a.val, C.double(R1), C.double(R2))}}
}

func TopoMakeSolidFromSphereTorusAxis2Angle(a Axis2, R1, R2, angle float64) *Solid {
	return &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_torus_axis2_angle(a.val, C.double(R1), C.double(R2), C.double(angle))}}
}

func TopoMakeSolidFromSphereTorusAxis2TwoAngle(a Axis2, R1, R2, angle1, angle2 float64) *Solid {
	return &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_torus_axis2_two_angle(a.val, C.double(R1), C.double(R2), C.double(angle1), C.double(angle2))}}
}

func TopoMakeSolidFromSphereTorusAxis2ThreeAngle(a Axis2, R1, R2, angle1, angle2, angle3 float64) *Solid {
	return &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_torus_axis2_three_angle(a.val, C.double(R1), C.double(R2), C.double(angle1), C.double(angle2), C.double(angle3))}}
}

func TopoMakeSolidFromSphereWedge(dx, dy, dz, ltx float64) *Solid {
	return &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_wedge(C.double(dx), C.double(dy), C.double(dz), C.double(ltx))}}
}

func TopoMakeSolidFromSphereWedgeAxis2(a Axis2, dx, dy, dz, ltx float64) *Solid {
	return &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_wedge_axis2(a.val, C.double(dx), C.double(dy), C.double(dz), C.double(ltx))}}
}

func TopoMakeSolidFromSphereWedgeLimit(dx, dy, dz, xmin, zmin, xmax, zmax float64) *Solid {
	return &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_wedge_limit(C.double(dx), C.double(dy), C.double(dz), C.double(xmin), C.double(zmin), C.double(xmax), C.double(zmax))}}
}

func TopoMakeSolidFromSphereWedgeAxis2Limit(a Axis2, dx, dy, dz, xmin, zmin, xmax, zmax float64) *Solid {
	return &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_wedge_axis2_limit(a.val, C.double(dx), C.double(dy), C.double(dz), C.double(xmin), C.double(zmin), C.double(xmax), C.double(zmax))}}
}

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
	return &Vertex{inner: &innerVertex{val: val}}
}

func (s *Vertex) Translated(v Vector3) *Vertex {
	var val C.struct__topo_vertex_t
	val.shp = C.topo_shape_translated(s.inner.val.shp, v.val)
	return &Vertex{inner: &innerVertex{val: val}}
}

func (s *Vertex) RotatedFromPoint(angle float64, p1, p2 Point3) *Vertex {
	var val C.struct__topo_vertex_t
	val.shp = C.topo_shape_rotated_from_two_point(s.inner.val.shp, C.double(angle), p1.val, p2.val)
	return &Vertex{inner: &innerVertex{val: val}}
}

func (s *Vertex) RotatedFromAxis1(angle float64, a Axis1) *Vertex {
	var val C.struct__topo_vertex_t
	val.shp = C.topo_shape_rotated_from_axis1(s.inner.val.shp, C.double(angle), a.val)
	return &Vertex{inner: &innerVertex{val: val}}
}

func (s *Vertex) RotatedFromQuaternion(q Quaternion) *Vertex {
	var val C.struct__topo_vertex_t
	val.shp = C.topo_shape_rotated_from_quaternion(s.inner.val.shp, q.val)
	return &Vertex{inner: &innerVertex{val: val}}
}

func (s *Vertex) Scaled(angle float64, a Point3) *Vertex {
	var val C.struct__topo_vertex_t
	val.shp = C.topo_shape_scaled(s.inner.val.shp, C.double(angle), a.val)
	return &Vertex{inner: &innerVertex{val: val}}
}

func (s *Vertex) MirroredFromPointNorm(pnt, ner Point3) *Vertex {
	var val C.struct__topo_vertex_t
	val.shp = C.topo_shape_mirrored_from_point_norm(s.inner.val.shp, pnt.val, ner.val)
	return &Vertex{inner: &innerVertex{val: val}}
}

func (s *Vertex) MirroredFromAxis1(a Axis1) *Vertex {
	var val C.struct__topo_vertex_t
	val.shp = C.topo_shape_mirrored_from_axis1(s.inner.val.shp, a.val)
	return &Vertex{inner: &innerVertex{val: val}}
}

func (s *Vertex) MirroredFromAxis2(a Axis2) *Vertex {
	var val C.struct__topo_vertex_t
	val.shp = C.topo_shape_mirrored_from_axis2(s.inner.val.shp, a.val)
	return &Vertex{inner: &innerVertex{val: val}}
}

func (s *Vertex) GetOrientation() int {
	return int(C.topo_shape_get_orientation(s.inner.val.shp))
}

func (s *Vertex) SetOrientation(t int) {
	C.topo_shape_set_orientation(s.inner.val.shp, C.int(t))
}

func (s *Vertex) GetLocation() *Location {
	return &Location{inner: &innerLocation{val: C.topo_shape_get_location(s.inner.val.shp)}}
}

func (s *Vertex) SetLocation(t *Location) {
	C.topo_shape_set_location(s.inner.val.shp, t.inner.val)
}

func (s *Vertex) FixShape() bool {
	return bool(C.topo_shape_fix_shape(s.inner.val.shp))
}

func (s *Vertex) Copy() *Vertex {
	var val C.struct__topo_vertex_t
	val.shp = C.topo_shape_copy(s.inner.val.shp)
	return &Vertex{inner: &innerVertex{val: val}}
}

func (s *Vertex) Mesh(m *MeshReceiver, tolerance, deflection, angle float64) {
	C.topo_shape_mesh(s.inner.val.shp, m.inner.val, C.double(tolerance), C.double(deflection), C.double(angle))
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

func (s *Vertex) GetSurfaceColour() Color {
	return Color{val: C.topo_shape_get_surface_colour(s.inner.val.shp)}
}

func (s *Vertex) GetCurveColour() Color {
	return Color{val: C.topo_shape_get_surface_colour(s.inner.val.shp)}
}

func (s *Vertex) GetLabel() string {
	return C.GoString(C.topo_shape_get_label(s.inner.val.shp))
}

func (t *Vertex) GetPoint() Point3 {
	return Point3{val: C.topo_vertex_get_point(t.inner.val)}
}

func (t *Vertex) ToShape() *Shape {
	return &Shape{inner: &innerShape{val: C.topo_shape_share(t.inner.val.shp)}}
}

func (t *Vertex) free() {
	C.topo_vertex_free(t.inner.val)
}

func NewVertex(x, y, z float64) *Vertex {
	p := &Vertex{inner: &innerVertex{val: C.topo_vertex_new(C.double(x), C.double(y), C.double(z))}}
	runtime.SetFinalizer(p, (*Vertex).free)
	return p
}

type Wire struct {
	inner *innerWire
}

type innerWire struct {
	val C.struct__topo_wire_t
}

func TopoMakeWire() *Wire {
	p := &Wire{inner: &innerWire{val: C.topo_make_wire()}}
	runtime.SetFinalizer(p, (*Wire).free)
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
	return &Wire{inner: &innerWire{val: val}}
}

func (s *Wire) Translated(v Vector3) *Wire {
	var val C.struct__topo_wire_t
	val.shp = C.topo_shape_translated(s.inner.val.shp, v.val)
	return &Wire{inner: &innerWire{val: val}}
}

func (s *Wire) RotatedFromPoint(angle float64, p1, p2 Point3) *Wire {
	var val C.struct__topo_wire_t
	val.shp = C.topo_shape_rotated_from_two_point(s.inner.val.shp, C.double(angle), p1.val, p2.val)
	return &Wire{inner: &innerWire{val: val}}
}

func (s *Wire) RotatedFromAxis1(angle float64, a Axis1) *Wire {
	var val C.struct__topo_wire_t
	val.shp = C.topo_shape_rotated_from_axis1(s.inner.val.shp, C.double(angle), a.val)
	return &Wire{inner: &innerWire{val: val}}
}

func (s *Wire) RotatedFromQuaternion(q Quaternion) *Wire {
	var val C.struct__topo_wire_t
	val.shp = C.topo_shape_rotated_from_quaternion(s.inner.val.shp, q.val)
	return &Wire{inner: &innerWire{val: val}}
}

func (s *Wire) Scaled(angle float64, a Point3) *Wire {
	var val C.struct__topo_wire_t
	val.shp = C.topo_shape_scaled(s.inner.val.shp, C.double(angle), a.val)
	return &Wire{inner: &innerWire{val: val}}
}

func (s *Wire) MirroredFromPointNorm(pnt, ner Point3) *Wire {
	var val C.struct__topo_wire_t
	val.shp = C.topo_shape_mirrored_from_point_norm(s.inner.val.shp, pnt.val, ner.val)
	return &Wire{inner: &innerWire{val: val}}
}

func (s *Wire) MirroredFromAxis1(a Axis1) *Wire {
	var val C.struct__topo_wire_t
	val.shp = C.topo_shape_mirrored_from_axis1(s.inner.val.shp, a.val)
	return &Wire{inner: &innerWire{val: val}}
}

func (s *Wire) MirroredFromAxis2(a Axis2) *Wire {
	var val C.struct__topo_wire_t
	val.shp = C.topo_shape_mirrored_from_axis2(s.inner.val.shp, a.val)
	return &Wire{inner: &innerWire{val: val}}
}

func (s *Wire) GetOrientation() int {
	return int(C.topo_shape_get_orientation(s.inner.val.shp))
}

func (s *Wire) SetOrientation(t int) {
	C.topo_shape_set_orientation(s.inner.val.shp, C.int(t))
}

func (s *Wire) GetLocation() *Location {
	return &Location{inner: &innerLocation{val: C.topo_shape_get_location(s.inner.val.shp)}}
}

func (s *Wire) SetLocation(t *Location) {
	C.topo_shape_set_location(s.inner.val.shp, t.inner.val)
}

func (s *Wire) FixShape() bool {
	return bool(C.topo_shape_fix_shape(s.inner.val.shp))
}

func (s *Wire) Copy() *Wire {
	var val C.struct__topo_wire_t
	val.shp = C.topo_shape_copy(s.inner.val.shp)
	return &Wire{inner: &innerWire{val: val}}
}

func (s *Wire) Mesh(m *MeshReceiver, tolerance, deflection, angle float64) {
	C.topo_shape_mesh(s.inner.val.shp, m.inner.val, C.double(tolerance), C.double(deflection), C.double(angle))
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

func (s *Wire) GetSurfaceColour() Color {
	return Color{val: C.topo_shape_get_surface_colour(s.inner.val.shp)}
}

func (s *Wire) GetCurveColour() Color {
	return Color{val: C.topo_shape_get_surface_colour(s.inner.val.shp)}
}

func (s *Wire) GetLabel() string {
	return C.GoString(C.topo_shape_get_label(s.inner.val.shp))
}

func (t *Wire) ToShape() *Shape {
	return &Shape{inner: &innerShape{val: C.topo_shape_share(t.inner.val.shp)}}
}

func (t *Wire) free() {
	C.topo_wire_free(t.inner.val)
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
	return &Wire{inner: &innerWire{val: C.topo_make_polygon()}}
}

func TopoMakePolygonFromTwoPoint(p1, p2 Point3) *Wire {
	return &Wire{inner: &innerWire{val: C.topo_make_polygon_from_two_point(p1.val, p2.val)}}
}

func TopoMakePolygonFromThreePoint(p1, p2, p3 Point3, Close bool) *Wire {
	return &Wire{inner: &innerWire{val: C.topo_make_polygon_from_three_point(p1.val, p2.val, p3.val, C.bool(Close))}}
}

func TopoMakePolygonFromFourPoint(p1, p2, p3, p4 Point3, Close bool) *Wire {
	return &Wire{inner: &innerWire{val: C.topo_make_polygon_from_four_point(p1.val, p2.val, p3.val, p4.val, C.bool(Close))}}
}

func TopoMakePolygonFromTwoVertex(p1, p2 Vertex) *Wire {
	return &Wire{inner: &innerWire{val: C.topo_make_polygon_two_vertex(p1.inner.val, p2.inner.val)}}
}

func TopoMakePolygonFromThreeVertex(p1, p2, p3 Vertex, Close bool) *Wire {
	return &Wire{inner: &innerWire{val: C.topo_make_polygon_from_three_vertex(p1.inner.val, p2.inner.val, p3.inner.val, C.bool(Close))}}
}

func TopoMakePolygonFromFourVertex(p1, p2, p3, p4 Vertex, Close bool) *Wire {
	return &Wire{inner: &innerWire{val: C.topo_make_polygon_from_four_vertex(p1.inner.val, p2.inner.val, p3.inner.val, p4.inner.val, C.bool(Close))}}
}

func TopoMakeWireFromEdge(p Edge) *Wire {
	return &Wire{inner: &innerWire{val: C.topo_make_wire_from_edge(p.inner.val)}}
}

func TopoMakeWireFromTwoEdge(p1, p2 Edge) *Wire {
	return &Wire{inner: &innerWire{val: C.topo_make_wire_from_two_edge(p1.inner.val, p2.inner.val)}}
}

func TopoMakeWireFromThreeEdge(p1, p2, p3 Edge) *Wire {
	return &Wire{inner: &innerWire{val: C.topo_make_wire_from_three_edge(p1.inner.val, p2.inner.val, p3.inner.val)}}
}

func TopoMakeWireFromFourEdge(p1, p2, p3, p4 Edge) *Wire {
	return &Wire{inner: &innerWire{val: C.topo_make_wire_from_four_edge(p1.inner.val, p2.inner.val, p3.inner.val, p4.inner.val)}}
}

func TopoMakeWireFromWire(p Wire) *Wire {
	return &Wire{inner: &innerWire{val: C.topo_make_wire_from_wire(p.inner.val)}}
}

func TopoMakeWireFromTwoWire(p1 Wire, p2 Edge) *Wire {
	return &Wire{inner: &innerWire{val: C.topo_make_wire_from_two_wire(p1.inner.val, p2.inner.val)}}
}

func TopoMakeWireFromEdges(edges []Edge) *Wire {
	es := make([]C.struct__topo_edge_t, len(edges))
	for i := range edges {
		es[i] = edges[i].inner.val
	}
	return &Wire{inner: &innerWire{val: C.topo_make_wire_from_edges(&es[0], C.int(len(edges)))}}
}

func TopoMakeWireFromWires(wires []Wire) *Wire {
	es := make([]C.struct__topo_wire_t, len(wires))
	for i := range wires {
		es[i] = wires[i].inner.val
	}
	return &Wire{inner: &innerWire{val: C.topo_make_wire_from_wries(&es[0], C.int(len(wires)))}}
}
