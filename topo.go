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
	TextureCube            = int(C.TextureCube)
	TextureNormal          = int(C.TextureNormal)
	TextureNormalAutoScale = int(C.TextureNormalAutoScale)
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
	hasTexCoords bool
	inner        *innerMeshReceiver
	index        int
	Faces        []Color
	Vers         [][]Point3
	Norms        [][]Point3
	TexCoords    [][]Point2
	Tris         [][][3]int
}

type innerMeshReceiver struct {
	val *C.struct__topo_mesh_receiver_t
}

func NewMeshReceiver() *MeshReceiver {
	ret := &MeshReceiver{inner: nil, index: -1, hasTexCoords: false}
	var cb C.struct__mesh_receiver_cb_t
	cb.ctx = unsafe.Pointer(ret)
	ret.inner = &innerMeshReceiver{C.topo_mesh_receiver_new(cb)}
	runtime.SetFinalizer(ret.inner, (*innerMeshReceiver).free)
	return ret
}

func (m *MeshReceiver) begin() {
	m.Faces = append(m.Faces, Color{})
	m.Vers = append(m.Vers, []Point3{})
	m.Norms = append(m.Norms, []Point3{})
	m.Tris = append(m.Tris, [][3]int{})
	if m.hasTexCoords {
		m.TexCoords = append(m.TexCoords, []Point2{})
	}
	m.index++
}

func (m *MeshReceiver) HasTexCoord() bool {
	return m.hasTexCoords
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
	if m.hasTexCoords {
		m.TexCoords[f] = append(m.TexCoords[f], uv)
	}
}

func (m *MeshReceiver) appendNode(f int, p Point3) {
	m.Vers[f] = append(m.Vers[f], p)
}

func (m *MeshReceiver) appendTriangle(f int, tri [3]int) {
	m.Tris[f] = append(m.Tris[f], tri)
}

func (m *innerMeshReceiver) free() {
	C.topo_mesh_receiver_free(m.val)
	m.val = nil
}

type Location struct {
	inner *innerLocation
}

type innerLocation struct {
	val *C.struct__topo_location_t
}

func NewLocation(t Trsf) *Location {
	p := &Location{inner: &innerLocation{val: C.topo_location_new(t.val)}}
	runtime.SetFinalizer(p.inner, (*innerLocation).free)
	return p
}

func (l *Location) Trsf() Trsf {
	return Trsf{val: C.topo_location_get_trsf(l.inner.val)}
}

func (l *innerLocation) free() {
	C.topo_location_free(l.val)
	l.val = nil
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

func (s *Shape) GetLocation() *Location {
	p := &Location{inner: &innerLocation{val: C.topo_shape_get_location(s.inner.val)}}
	runtime.SetFinalizer(p.inner, (*innerLocation).free)
	return p
}

func (s *Shape) SetLocation(t *Location) {
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

func (s *Shape) SetTxtureMapType(t int) {
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

type CompSolid struct {
	inner *innerCompSolid
}

type innerCompSolid struct {
	val C.struct__topo_comp_solid_t
}

func TopoMakeCompSolid() *CompSolid {
	p := &CompSolid{inner: &innerCompSolid{val: C.topo_make_comp_solid()}}
	runtime.SetFinalizer(p.inner, (*innerCompSolid).free)
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
	p := &Location{inner: &innerLocation{val: C.topo_shape_get_location(s.inner.val.shp)}}
	runtime.SetFinalizer(p.inner, (*innerLocation).free)
	return p
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
	C.topo_shape_mesh(s.inner.val.shp, m.inner.val, C.double(tolerance), C.double(deflection), C.double(angle), C.bool(false))
}

func (s *CompSolid) MeshWithTexture(m *MeshReceiver, tolerance, deflection, angle float64) {
	m.hasTexCoords = true
	C.topo_shape_mesh(s.inner.val.shp, m.inner.val, C.double(tolerance), C.double(deflection), C.double(angle), C.bool(true))
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

func (s *CompSolid) SetUVOrigin(u, v float64) {
	C.topo_shape_set_u_origin(s.inner.val.shp, C.double(u))
	C.topo_shape_set_v_origin(s.inner.val.shp, C.double(v))
}

func (s *CompSolid) SetUVRepeat(u, v float64) {
	C.topo_shape_set_u_repeat(s.inner.val.shp, C.double(u))
	C.topo_shape_set_v_repeat(s.inner.val.shp, C.double(v))
}

func (s *CompSolid) SetScaleU(u float64) {
	C.topo_shape_set_scale_u(s.inner.val.shp, C.double(u))
}

func (s *CompSolid) SetScaleV(v float64) {
	C.topo_shape_set_scale_v(s.inner.val.shp, C.double(v))
}

func (s *CompSolid) SetAutoScaleSizeOnU(u float64) {
	C.topo_shape_set_auto_scale_size_on_u(s.inner.val.shp, C.double(u))
}

func (s *CompSolid) SetAutoScaleSizeOnV(v float64) {
	C.topo_shape_set_auto_scale_size_on_v(s.inner.val.shp, C.double(v))
}

func (s *CompSolid) SetTxtureMapType(t int) {
	C.topo_shape_set_txture_map_type(s.inner.val.shp, C.int(t))
}

func (s *CompSolid) SetRotationAngle(a float64) {
	C.topo_shape_set_rotation_angle(s.inner.val.shp, C.double(a))
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

func (s *CompSolid) GetUVOrigin() (u, v float64) {
	u = float64(C.topo_shape_get_u_origin(s.inner.val.shp))
	v = float64(C.topo_shape_get_v_origin(s.inner.val.shp))
	return
}

func (s *CompSolid) GetUVRepeat() (u, v float64) {
	u = float64(C.topo_shape_get_u_repeat(s.inner.val.shp))
	v = float64(C.topo_shape_get_v_repeat(s.inner.val.shp))
	return
}

func (s *CompSolid) GetUVScale() (u, v float64) {
	u = float64(C.topo_shape_get_scale_u(s.inner.val.shp))
	v = float64(C.topo_shape_get_scale_v(s.inner.val.shp))
	return
}

func (s *CompSolid) GetUVAutoScaleSize() (u, v float64) {
	u = float64(C.topo_shape_get_auto_scale_size_on_u(s.inner.val.shp))
	v = float64(C.topo_shape_get_auto_scale_size_on_v(s.inner.val.shp))
	return
}

func (s *CompSolid) GetTxtureMapType() int {
	return int(C.topo_shape_get_txture_map_type(s.inner.val.shp))
}

func (s *CompSolid) GetRotationAngle() float64 {
	return float64(C.topo_shape_get_rotation_angle(s.inner.val.shp))
}

func (t *innerCompSolid) free() {
	C.topo_comp_solid_free(t.val)
}

func (t *CompSolid) solid() C.struct__topo_solid_t {
	var val C.struct__topo_solid_t
	val.shp = t.inner.val.shp
	return val
}

func (t *CompSolid) ToShape() *Shape {
	sp := &Shape{inner: &innerShape{val: C.topo_shape_share(t.inner.val.shp)}}
	runtime.SetFinalizer(sp.inner, (*innerShape).free)
	return sp
}

func (t *CompSolid) ToSolid() *Solid {
	var val C.struct__topo_solid_t
	val.shp = C.topo_shape_share(t.inner.val.shp)
	sld := &Solid{inner: &innerSolid{val: val}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
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

func (s *CompSolid) Sweep(spine *Wire, profiles []Shape, cornerMode int) int {
	cshp := make([]*C.struct__topo_shape_t, len(profiles))
	for i := range profiles {
		cshp[i] = profiles[i].inner.val
	}
	return int(C.topo_solid_sweep(s.solid(), spine.inner.val, &cshp[0], C.int(len(profiles)), C.int(cornerMode)))
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
	p := &Face{inner: &innerFace{val: C.topo_solid_section_face(s.solid(), pnt.val, nor.val)}}
	runtime.SetFinalizer(p.inner, (*innerLocation).free)
	return p
}

func (s *CompSolid) ConvertToNurbs() int {
	return int(C.topo_solid_convert_to_nurbs(s.solid()))
}

func TopoCompSolidMake(s []Solid) *CompSolid {
	sos := make([]C.struct__topo_solid_t, len(s))
	for i := range s {
		sos[i] = s[i].inner.val
	}
	c := &CompSolid{inner: &innerCompSolid{val: C.topo_comp_solid_make_comp_solid(&sos[0], C.int(len(s)))}}
	runtime.SetFinalizer(c.inner, (*innerCompSolid).free)
	return c
}

type Compound struct {
	inner *innerCompound
}

type innerCompound struct {
	val C.struct__topo_compound_t
}

func TopoMakeCompound() *Compound {
	c := &Compound{inner: &innerCompound{val: C.topo_make_compound()}}
	runtime.SetFinalizer(c.inner, (*innerCompound).free)
	return c
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
	p := &Location{inner: &innerLocation{val: C.topo_shape_get_location(s.inner.val.shp)}}
	runtime.SetFinalizer(p.inner, (*innerLocation).free)
	return p
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
	C.topo_shape_mesh(s.inner.val.shp, m.inner.val, C.double(tolerance), C.double(deflection), C.double(angle), C.bool(false))
}

func (s *Compound) MeshWithTexture(m *MeshReceiver, tolerance, deflection, angle float64) {
	m.hasTexCoords = true
	C.topo_shape_mesh(s.inner.val.shp, m.inner.val, C.double(tolerance), C.double(deflection), C.double(angle), C.bool(true))
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

func (s *Compound) SetUVOrigin(u, v float64) {
	C.topo_shape_set_u_origin(s.inner.val.shp, C.double(u))
	C.topo_shape_set_v_origin(s.inner.val.shp, C.double(v))
}

func (s *Compound) SetUVRepeat(u, v float64) {
	C.topo_shape_set_u_repeat(s.inner.val.shp, C.double(u))
	C.topo_shape_set_v_repeat(s.inner.val.shp, C.double(v))
}

func (s *Compound) SetScaleU(u float64) {
	C.topo_shape_set_scale_u(s.inner.val.shp, C.double(u))
}

func (s *Compound) SetScaleV(v float64) {
	C.topo_shape_set_scale_v(s.inner.val.shp, C.double(v))
}

func (s *Compound) SetAutoScaleSizeOnU(u float64) {
	C.topo_shape_set_auto_scale_size_on_u(s.inner.val.shp, C.double(u))
}

func (s *Compound) SetAutoScaleSizeOnV(v float64) {
	C.topo_shape_set_auto_scale_size_on_v(s.inner.val.shp, C.double(v))
}

func (s *Compound) SetTxtureMapType(t int) {
	C.topo_shape_set_txture_map_type(s.inner.val.shp, C.int(t))
}

func (s *Compound) SetRotationAngle(a float64) {
	C.topo_shape_set_rotation_angle(s.inner.val.shp, C.double(a))
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

func (s *Compound) GetUVOrigin() (u, v float64) {
	u = float64(C.topo_shape_get_u_origin(s.inner.val.shp))
	v = float64(C.topo_shape_get_v_origin(s.inner.val.shp))
	return
}

func (s *Compound) GetUVRepeat() (u, v float64) {
	u = float64(C.topo_shape_get_u_repeat(s.inner.val.shp))
	v = float64(C.topo_shape_get_v_repeat(s.inner.val.shp))
	return
}

func (s *Compound) GetUVScale() (u, v float64) {
	u = float64(C.topo_shape_get_scale_u(s.inner.val.shp))
	v = float64(C.topo_shape_get_scale_v(s.inner.val.shp))
	return
}

func (s *Compound) GetUVAutoScaleSize() (u, v float64) {
	u = float64(C.topo_shape_get_auto_scale_size_on_u(s.inner.val.shp))
	v = float64(C.topo_shape_get_auto_scale_size_on_v(s.inner.val.shp))
	return
}

func (s *Compound) GetTxtureMapType() int {
	return int(C.topo_shape_get_txture_map_type(s.inner.val.shp))
}

func (s *Compound) GetRotationAngle() float64 {
	return float64(C.topo_shape_get_rotation_angle(s.inner.val.shp))
}

func (t *innerCompound) free() {
	C.topo_compound_free(t.val)
}

func (t *Compound) solid() C.struct__topo_solid_t {
	var val C.struct__topo_solid_t
	val.shp = t.inner.val.shp
	return val
}

func (t *Compound) ToShape() *Shape {
	sp := &Shape{inner: &innerShape{val: C.topo_shape_share(t.inner.val.shp)}}
	runtime.SetFinalizer(sp.inner, (*innerShape).free)
	return sp
}

func (t *Compound) ToSolid() *Solid {
	var val C.struct__topo_solid_t
	val.shp = C.topo_shape_share(t.inner.val.shp)
	sld := &Solid{inner: &innerSolid{val: val}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
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
	p := &Face{inner: &innerFace{val: C.topo_solid_section_face(s.solid(), pnt.val, nor.val)}}
	runtime.SetFinalizer(p.inner, (*innerFace).free)
	return p
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

func (s *Edge) GetLocation() *Location {
	p := &Location{inner: &innerLocation{val: C.topo_shape_get_location(s.inner.val.shp)}}
	runtime.SetFinalizer(p.inner, (*innerLocation).free)
	return p
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

func (s *Edge) SetTxtureMapType(t int) {
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

func (s *Face) GetLocation() *Location {
	p := &Location{inner: &innerLocation{val: C.topo_shape_get_location(s.inner.val.shp)}}
	runtime.SetFinalizer(p.inner, (*innerLocation).free)
	return p
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

func (s *Face) SetTxtureMapType(t int) {
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

type Shell struct {
	inner *innerShell
}

type innerShell struct {
	val C.struct__topo_shell_t
}

func TopoMakeShell() *Shell {
	p := &Shell{inner: &innerShell{val: C.topo_make_shell()}}
	runtime.SetFinalizer(p.inner, (*innerShell).free)
	return p
}

func (s *Shell) Sweep(spine *Wire, profiles []Shape, cornerMode int) int {
	cshp := make([]*C.struct__topo_shape_t, len(profiles))
	for i := range profiles {
		cshp[i] = profiles[i].inner.val
	}
	return int(C.topo_shell_sweep(s.inner.val, spine.inner.val, &cshp[0], C.int(len(profiles)), C.int(cornerMode)))
}

func (t *Shell) ToShape() *Shape {
	sp := &Shape{inner: &innerShape{val: C.topo_shape_share(t.inner.val.shp)}}
	runtime.SetFinalizer(sp.inner, (*innerShape).free)
	return sp
}

func (t *innerShell) free() {
	C.topo_shell_free(t.val)
}

func TopoMakeShellFromSurface(S *GeomSurface, Segment bool) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_surface(S.inner.geom, C.bool(Segment))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromSurfaceFromSurfaceParm(S *GeomSurface, UMin, UMax, VMin, VMax float64, Segment bool) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_surface_p(S.inner.geom, C.double(UMin), C.double(UMax), C.double(VMin), C.double(VMax), C.bool(Segment))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromBox(dx, dy, dz float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_box(C.double(dx), C.double(dy), C.double(dz))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromBoxPoint(p Point3, dx, dy, dz float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_box_point(p.val, C.double(dx), C.double(dy), C.double(dz))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromBoxTwoPoint(p1, p2 Point3) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_box_two_point(p1.val, p2.val)}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromBoxAxis2(a Axis2, dx, dy, dz float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_box_axis2(a.val, C.double(dx), C.double(dy), C.double(dz))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromCylinder(R, H float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_cylinder(C.double(R), C.double(H))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromCylinderAngle(R, H, Angle float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_cylinder_angle(C.double(R), C.double(H), C.double(Angle))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromCylinderAxis2(a Axis2, R, H float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_cylinder_axis2(a.val, C.double(R), C.double(H))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromCylinderAxis2Angle(a Axis2, R, H, Angle float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_cylinder_axis2_angle(a.val, C.double(R), C.double(H), C.double(Angle))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromCone(R1, R2, H float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_cone(C.double(R1), C.double(R2), C.double(H))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromConeAngle(R1, R2, H, Angle float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_cone_angle(C.double(R1), C.double(R2), C.double(H), C.double(Angle))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromConeAxis2(a Axis2, R1, R2, H float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_cone_axis2(a.val, C.double(R1), C.double(R2), C.double(H))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromConeAxis2Angle(a Axis2, R1, R2, H, Angle float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_cone_axis2_angle(a.val, C.double(R1), C.double(R2), C.double(H), C.double(Angle))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromRevolution(m *GeomCurve) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_revolution(m.inner.geom)}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromRevolutionAngle(m *GeomCurve, Angle float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_revolution_angle(m.inner.geom, C.double(Angle))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromRevolutionLimit(m *GeomCurve, VMin, VMax float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_revolution_limit(m.inner.geom, C.double(VMin), C.double(VMax))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromRevolutionLimitAngle(m *GeomCurve, VMin, VMax, Angle float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_revolution_limit_angle(m.inner.geom, C.double(VMin), C.double(VMax), C.double(Angle))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromRevolutionAxis2(a Axis2, m *GeomCurve) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_revolution_axis2(a.val, m.inner.geom)}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromRevolutionAxis2Angle(a Axis2, m *GeomCurve, Angle float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_revolution_axis2_angle(a.val, m.inner.geom, C.double(Angle))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromRevolutionAxis2Limit(a Axis2, m *GeomCurve, VMin, VMax float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_revolution_axis2_limit(a.val, m.inner.geom, C.double(VMin), C.double(VMax))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromRevolutionAxis2LimitAngle(a Axis2, m *GeomCurve, VMin, VMax, Angle float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_revolution_axis2_limit_angle(a.val, m.inner.geom, C.double(VMin), C.double(VMax), C.double(Angle))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromSpere(R float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_sphere(C.double(R))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromSpereAngle(R float64, Angle float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_sphere_angle(C.double(R), C.double(Angle))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromSpereTwoAngle(R float64, Angle1, Angle2 float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_sphere_two_angle(C.double(R), C.double(Angle1), C.double(Angle2))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromSpereThreeAngle(R float64, Angle1, Angle2, Angle3 float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_sphere_three_angle(C.double(R), C.double(Angle1), C.double(Angle2), C.double(Angle3))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromSpereCenterRaduis(Center Point3, R float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_sphere_center_raduis(Center.val, C.double(R))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromSpereCenterAngle(Center Point3, R, Angle float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_sphere_center_angle(Center.val, C.double(R), C.double(Angle))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromSpereCenterTwoAngle(Center Point3, R, Angle1, Angle2 float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_sphere_center_two_angle(Center.val, C.double(R), C.double(Angle1), C.double(Angle2))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromSpereCenterThreeAngle(Center Point3, R, Angle1, Angle2, Angle3 float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_sphere_center_three_angle(Center.val, C.double(R), C.double(Angle1), C.double(Angle2), C.double(Angle3))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromSpereAxis2(a Axis2, R float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_sphere_axis2(a.val, C.double(R))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromSpereAxis2Angle(a Axis2, R, Angle float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_sphere_axis2_raduis(a.val, C.double(R), C.double(Angle))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromSpereAxis2TwoAngle(a Axis2, R, Angle1, Angle2 float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_sphere_axis2_two_angle(a.val, C.double(R), C.double(Angle1), C.double(Angle2))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromSpereAxis2ThreeAngle(a Axis2, R, Angle1, Angle2, Angle3 float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_sphere_axis2_three_angle(a.val, C.double(R), C.double(Angle1), C.double(Angle2), C.double(Angle3))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromTorus(R1, R2 float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_torus(C.double(R1), C.double(R2))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromTorusAngle(R1, R2, Angle float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_torus_angle(C.double(R1), C.double(R2), C.double(Angle))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromTorusTwoAngle(R1, R2, Angle1, Angle2 float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_torus_two_angle(C.double(R1), C.double(R2), C.double(Angle1), C.double(Angle2))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromTorusThreeAngle(R1, R2, Angle1, Angle2, Angle3 float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_torus_three_angle(C.double(R1), C.double(R2), C.double(Angle1), C.double(Angle2), C.double(Angle3))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromTorusAxis2(a Axis2, R1, R2 float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_torus_axis2(a.val, C.double(R1), C.double(R2))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromTorusAxis2Angle(a Axis2, R1, R2, Angle float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_torus_axis2_angle(a.val, C.double(R1), C.double(R2), C.double(Angle))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromTorusAxis2TwoAngle(a Axis2, R1, R2, Angle1, Angle2 float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_torus_axis2_two_angle(a.val, C.double(R1), C.double(R2), C.double(Angle1), C.double(Angle2))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromTorusAxis2ThreeAngle(a Axis2, R1, R2, Angle1, Angle2, Angle3 float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_torus_axis2_three_angle(a.val, C.double(R1), C.double(R2), C.double(Angle1), C.double(Angle2), C.double(Angle3))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromWedge(dx, dy, dz, ltx float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_wedge(C.double(dx), C.double(dy), C.double(dz), C.double(ltx))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromWedgeAxis2(a Axis2, dx, dy, dz, ltx float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_wedge_axis2(a.val, C.double(dx), C.double(dy), C.double(dz), C.double(ltx))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromWedgeLimit(dx, dy, dz, xmin, zmin, xmax, zmax float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_wedge_limit(C.double(dx), C.double(dy), C.double(dz), C.double(xmin), C.double(zmin), C.double(xmax), C.double(zmax))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromWedgeAxis2Limit(a Axis2, dx, dy, dz, xmin, zmin, xmax, zmax float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_wedge_axis2_limit(a.val, C.double(dx), C.double(dy), C.double(dz), C.double(xmin), C.double(zmin), C.double(xmax), C.double(zmax))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

type Solid struct {
	inner *innerSolid
}

type innerSolid struct {
	val C.struct__topo_solid_t
}

func TopoMakeSolid() *Solid {
	p := &Solid{inner: &innerSolid{val: C.topo_make_solid()}}
	runtime.SetFinalizer(p.inner, (*innerSolid).free)
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
	sld := &Solid{inner: &innerSolid{val: val}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func (s *Solid) Translated(v Vector3) *Solid {
	var val C.struct__topo_solid_t
	val.shp = C.topo_shape_translated(s.inner.val.shp, v.val)
	sld := &Solid{inner: &innerSolid{val: val}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func (s *Solid) RotatedFromPoint(angle float64, p1, p2 Point3) *Solid {
	var val C.struct__topo_solid_t
	val.shp = C.topo_shape_rotated_from_two_point(s.inner.val.shp, C.double(angle), p1.val, p2.val)
	sld := &Solid{inner: &innerSolid{val: val}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func (s *Solid) RotatedFromAxis1(angle float64, a Axis1) *Solid {
	var val C.struct__topo_solid_t
	val.shp = C.topo_shape_rotated_from_axis1(s.inner.val.shp, C.double(angle), a.val)
	sld := &Solid{inner: &innerSolid{val: val}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func (s *Solid) RotatedFromQuaternion(q Quaternion) *Solid {
	var val C.struct__topo_solid_t
	val.shp = C.topo_shape_rotated_from_quaternion(s.inner.val.shp, q.val)
	sld := &Solid{inner: &innerSolid{val: val}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func (s *Solid) Scaled(angle float64, a Point3) *Solid {
	var val C.struct__topo_solid_t
	val.shp = C.topo_shape_scaled(s.inner.val.shp, C.double(angle), a.val)
	sld := &Solid{inner: &innerSolid{val: val}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func (s *Solid) MirroredFromPointNorm(pnt, ner Point3) *Solid {
	var val C.struct__topo_solid_t
	val.shp = C.topo_shape_mirrored_from_point_norm(s.inner.val.shp, pnt.val, ner.val)
	sld := &Solid{inner: &innerSolid{val: val}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func (s *Solid) MirroredFromAxis1(a Axis1) *Solid {
	var val C.struct__topo_solid_t
	val.shp = C.topo_shape_mirrored_from_axis1(s.inner.val.shp, a.val)
	sld := &Solid{inner: &innerSolid{val: val}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func (s *Solid) MirroredFromAxis2(a Axis2) *Solid {
	var val C.struct__topo_solid_t
	val.shp = C.topo_shape_mirrored_from_axis2(s.inner.val.shp, a.val)
	sld := &Solid{inner: &innerSolid{val: val}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func (s *Solid) GetOrientation() int {
	return int(C.topo_shape_get_orientation(s.inner.val.shp))
}

func (s *Solid) SetOrientation(t int) {
	C.topo_shape_set_orientation(s.inner.val.shp, C.int(t))
}

func (s *Solid) GetLocation() *Location {
	p := &Location{inner: &innerLocation{val: C.topo_shape_get_location(s.inner.val.shp)}}
	runtime.SetFinalizer(p.inner, (*innerLocation).free)
	return p
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
	sld := &Solid{inner: &innerSolid{val: val}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func (s *Solid) Mesh(m *MeshReceiver, tolerance, deflection, angle float64) {
	C.topo_shape_mesh(s.inner.val.shp, m.inner.val, C.double(tolerance), C.double(deflection), C.double(angle), C.bool(false))
}

func (s *Solid) MeshWithTexture(m *MeshReceiver, tolerance, deflection, angle float64) {
	m.hasTexCoords = true
	C.topo_shape_mesh(s.inner.val.shp, m.inner.val, C.double(tolerance), C.double(deflection), C.double(angle), C.bool(true))
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

func (s *Solid) SetUVOrigin(u, v float64) {
	C.topo_shape_set_u_origin(s.inner.val.shp, C.double(u))
	C.topo_shape_set_v_origin(s.inner.val.shp, C.double(v))
}

func (s *Solid) SetUVRepeat(u, v float64) {
	C.topo_shape_set_u_repeat(s.inner.val.shp, C.double(u))
	C.topo_shape_set_v_repeat(s.inner.val.shp, C.double(v))
}

func (s *Solid) SetScaleU(u float64) {
	C.topo_shape_set_scale_u(s.inner.val.shp, C.double(u))
}

func (s *Solid) SetScaleV(v float64) {
	C.topo_shape_set_scale_v(s.inner.val.shp, C.double(v))
}

func (s *Solid) SetAutoScaleSizeOnU(u float64) {
	C.topo_shape_set_auto_scale_size_on_u(s.inner.val.shp, C.double(u))
}

func (s *Solid) SetAutoScaleSizeOnV(v float64) {
	C.topo_shape_set_auto_scale_size_on_v(s.inner.val.shp, C.double(v))
}

func (s *Solid) SetTxtureMapType(t int) {
	C.topo_shape_set_txture_map_type(s.inner.val.shp, C.int(t))
}

func (s *Solid) SetRotationAngle(a float64) {
	C.topo_shape_set_rotation_angle(s.inner.val.shp, C.double(a))
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

func (s *Solid) GetUVOrigin() (u, v float64) {
	u = float64(C.topo_shape_get_u_origin(s.inner.val.shp))
	v = float64(C.topo_shape_get_v_origin(s.inner.val.shp))
	return
}

func (s *Solid) GetUVRepeat() (u, v float64) {
	u = float64(C.topo_shape_get_u_repeat(s.inner.val.shp))
	v = float64(C.topo_shape_get_v_repeat(s.inner.val.shp))
	return
}

func (s *Solid) GetUVScale() (u, v float64) {
	u = float64(C.topo_shape_get_scale_u(s.inner.val.shp))
	v = float64(C.topo_shape_get_scale_v(s.inner.val.shp))
	return
}

func (s *Solid) GetUVAutoScaleSize() (u, v float64) {
	u = float64(C.topo_shape_get_auto_scale_size_on_u(s.inner.val.shp))
	v = float64(C.topo_shape_get_auto_scale_size_on_v(s.inner.val.shp))
	return
}

func (s *Solid) GetTxtureMapType() int {
	return int(C.topo_shape_get_txture_map_type(s.inner.val.shp))
}

func (s *Solid) GetRotationAngle() float64 {
	return float64(C.topo_shape_get_rotation_angle(s.inner.val.shp))
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

func (s *Solid) Sweep(spine *Wire, profiles []Shape, cornerMode int) int {
	cshp := make([]*C.struct__topo_shape_t, len(profiles))
	for i := range profiles {
		cshp[i] = profiles[i].inner.val
	}
	return int(C.topo_solid_sweep(s.inner.val, spine.inner.val, &cshp[0], C.int(len(profiles)), C.int(cornerMode)))
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
	p := &Face{inner: &innerFace{val: C.topo_solid_section_face(s.inner.val, pnt.val, nor.val)}}
	runtime.SetFinalizer(p.inner, (*innerFace).free)
	return p
}

func (s *Solid) ConvertToNurbs() int {
	return int(C.topo_solid_convert_to_nurbs(s.inner.val))
}

func (t *Solid) ToShape() *Shape {
	sp := &Shape{inner: &innerShape{val: C.topo_shape_share(t.inner.val.shp)}}
	runtime.SetFinalizer(sp.inner, (*innerShape).free)
	return sp
}

func (t *innerSolid) free() {
	C.topo_solid_free(t.val)
}

func TopoMakeSolidFromCompSolid(S *CompSolid) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_comp_solid(S.inner.val)}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromShell(S *Shell) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_shell(S.inner.val)}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromTwoShell(S1, S2 *Shell) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_two_shell(S1.inner.val, S2.inner.val)}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromThreeShell(S1, S2, S3 *Shell) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_three_shell(S1.inner.val, S2.inner.val, S3.inner.val)}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromShells(S []Shell) *Solid {
	shls := make([]C.struct__topo_shell_t, len(S))
	for i := range S {
		shls[i] = S[i].inner.val
	}
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_shells(&shls[0], C.int(len(S)))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromSolid(S *Solid) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_solid(S.inner.val)}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromSolidShell(S *Solid, sl *Shell) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_solid_shell(S.inner.val, sl.inner.val)}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromFaces(S []Face, tolerance float64) *Solid {
	shls := make([]C.struct__topo_face_t, len(S))
	for i := range S {
		shls[i] = S[i].inner.val
	}
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_faces(&shls[0], C.int(len(S)), C.double(tolerance))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromBox(dx, dy, dz float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_box(C.double(dx), C.double(dy), C.double(dz))}}
	runtime.SetFinalizer(sld.inner, (*innerLocation).free)
	return sld
}

func TopoMakeSolidFromBoxPoint(p Point3, dx, dy, dz float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_box_point(p.val, C.double(dx), C.double(dy), C.double(dz))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromBoxTwoPoint(p1, p2 Point3) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_box_two_point(p1.val, p2.val)}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromBoxAxis2(a Axis2, dx, dy, dz float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_box_axis2(a.val, C.double(dx), C.double(dy), C.double(dz))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromCylinder(R, H float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_cylinder(C.double(R), C.double(H))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromCylinderAngle(R, H, Angle float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_cylinder_angle(C.double(R), C.double(H), C.double(Angle))}}
	runtime.SetFinalizer(sld.inner, (*innerLocation).free)
	return sld
}

func TopoMakeSolidFromCylinderAxis2(a Axis2, R, H float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_cylinder_axis2(a.val, C.double(R), C.double(H))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromCylinderAxis2Angle(a Axis2, R, H, Angle float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_cylinder_axis2_angle(a.val, C.double(R), C.double(H), C.double(Angle))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromCone(R1, R2, H float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_cone(C.double(R1), C.double(R2), C.double(H))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromConeAngle(R1, R2, H, Angle float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_cone_angle(C.double(R1), C.double(R2), C.double(H), C.double(Angle))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromConeAxis2(a Axis2, R1, R2, H float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_cone_axis2(a.val, C.double(R1), C.double(R2), C.double(H))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromConeAxis2Angle(a Axis2, R1, R2, H, Angle float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_cone_axis2_angle(a.val, C.double(R1), C.double(R2), C.double(H), C.double(Angle))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFroRevolution(Meridian *GeomCurve) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_revolution(Meridian.inner.geom)}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFroRevolutionAngle(Meridian *GeomCurve, angle float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_revolution_angle(Meridian.inner.geom, C.double(angle))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFroRevolutionLimit(Meridian *GeomCurve, VMin, VMax float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_revolution_limit(Meridian.inner.geom, C.double(VMin), C.double(VMax))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFroRevolutionLimitAngle(Meridian *GeomCurve, VMin, VMax, angle float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_revolution_limit_angle(Meridian.inner.geom, C.double(VMin), C.double(VMax), C.double(angle))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFroRevolutionAxis2(a Axis2, Meridian *GeomCurve) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_revolution_axis2(a.val, Meridian.inner.geom)}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFroRevolutionAxis2Angle(a Axis2, Meridian *GeomCurve, angle float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_revolution_axis2_angle(a.val, Meridian.inner.geom, C.double(angle))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFroRevolutionAxis2Limit(a Axis2, Meridian *GeomCurve, VMin, VMax float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_revolution_axis2_limit(a.val, Meridian.inner.geom, C.double(VMin), C.double(VMax))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFroRevolutionAxis2LimitAngle(a Axis2, Meridian *GeomCurve, VMin, VMax, angle float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_revolution_axis2_limit_angle(a.val, Meridian.inner.geom, C.double(VMin), C.double(VMax), C.double(angle))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromSphere(R float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_sphere(C.double(R))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromSphereAngle(R, angle float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_sphere_angle(C.double(R), C.double(angle))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromSphereTwoAngle(R, angle1, angle2 float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_sphere_two_angle(C.double(R), C.double(angle1), C.double(angle2))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromSphereThreeAngle(R, angle1, angle2, angle3 float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_sphere_three_angle(C.double(R), C.double(angle1), C.double(angle2), C.double(angle3))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromSphereCenterAngle(c Point3, R, angle float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_sphere_center_angle(c.val, C.double(R), C.double(angle))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromSphereCenterTwoAngle(c Point3, R, angle1, angle2 float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_sphere_center_two_angle(c.val, C.double(R), C.double(angle1), C.double(angle2))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromSphereCenterThreeAngle(c Point3, R, angle1, angle2, angle3 float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_sphere_center_three_angle(c.val, C.double(R), C.double(angle1), C.double(angle2), C.double(angle3))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromSphereAxis2(a Axis2, R float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_sphere_axis2(a.val, C.double(R))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromSphereAxis2Angle(a Axis2, R, angle float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_sphere_axis2_angle(a.val, C.double(R), C.double(angle))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromSphereAxis2TwoAngle(a Axis2, R, angle1, angle2 float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_sphere_axis2_two_angle(a.val, C.double(R), C.double(angle1), C.double(angle2))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromSphereAxis2ThreeAngle(a Axis2, R, angle1, angle2, angle3 float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_sphere_axis2_three_angle(a.val, C.double(R), C.double(angle1), C.double(angle2), C.double(angle3))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromSphereTorus(R1, R2 float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_torus(C.double(R1), C.double(R2))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromSphereTorusAngle(R1, R2, angle float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_torus_angle(C.double(R1), C.double(R2), C.double(angle))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromSphereTorusTwoAngle(R1, R2, angle1, angle2 float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_torus_two_angle(C.double(R1), C.double(R2), C.double(angle1), C.double(angle2))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromSphereTorusThreeAngle(R1, R2, angle1, angle2, angle3 float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_torus_three_angle(C.double(R1), C.double(R2), C.double(angle1), C.double(angle2), C.double(angle3))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromSphereTorusAxis2(a Axis2, R1, R2 float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_torus_axis2(a.val, C.double(R1), C.double(R2))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromSphereTorusAxis2Angle(a Axis2, R1, R2, angle float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_torus_axis2_angle(a.val, C.double(R1), C.double(R2), C.double(angle))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromSphereTorusAxis2TwoAngle(a Axis2, R1, R2, angle1, angle2 float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_torus_axis2_two_angle(a.val, C.double(R1), C.double(R2), C.double(angle1), C.double(angle2))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromSphereTorusAxis2ThreeAngle(a Axis2, R1, R2, angle1, angle2, angle3 float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_torus_axis2_three_angle(a.val, C.double(R1), C.double(R2), C.double(angle1), C.double(angle2), C.double(angle3))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromSphereWedge(dx, dy, dz, ltx float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_wedge(C.double(dx), C.double(dy), C.double(dz), C.double(ltx))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromSphereWedgeAxis2(a Axis2, dx, dy, dz, ltx float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_wedge_axis2(a.val, C.double(dx), C.double(dy), C.double(dz), C.double(ltx))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromSphereWedgeLimit(dx, dy, dz, xmin, zmin, xmax, zmax float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_wedge_limit(C.double(dx), C.double(dy), C.double(dz), C.double(xmin), C.double(zmin), C.double(xmax), C.double(zmax))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromSphereWedgeAxis2Limit(a Axis2, dx, dy, dz, xmin, zmin, xmax, zmax float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_wedge_axis2_limit(a.val, C.double(dx), C.double(dy), C.double(dz), C.double(xmin), C.double(zmin), C.double(xmax), C.double(zmax))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
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

func (s *Vertex) GetLocation() *Location {
	p := &Location{inner: &innerLocation{val: C.topo_shape_get_location(s.inner.val.shp)}}
	runtime.SetFinalizer(p.inner, (*innerLocation).free)
	return p
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

func (s *Vertex) SetTxtureMapType(t int) {
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

func (s *Wire) GetLocation() *Location {
	sp := &Location{inner: &innerLocation{val: C.topo_shape_get_location(s.inner.val.shp)}}
	runtime.SetFinalizer(sp.inner, (*innerShape).free)
	return sp
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

func (s *Wire) SetTxtureMapType(t int) {
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

type CompSolidIterator struct {
	inner *innerCompSolidIterator
}
type innerCompSolidIterator struct {
	val *C.struct__topo_comp_solid_iterator_t
}

func TopoMakeCompSolidIterator(p Shape) *CompSolidIterator {
	wr := &CompSolidIterator{inner: &innerCompSolidIterator{val: C.topo_comp_solid_iterator_make(p.inner.val)}}
	runtime.SetFinalizer(wr.inner, (*innerCompSolidIterator).free)
	return wr
}

func (t *innerCompSolidIterator) free() {
	C.topo_comp_solid_iterator_free(t.val)
}

func (t *CompSolidIterator) Next() *CompSolid {
	v := C.topo_comp_solid_iterator_next(t.inner.val)
	if v != nil {
		var val C.struct__topo_comp_solid_t
		val.shp = v
		p := &CompSolid{inner: &innerCompSolid{val: val}}
		runtime.SetFinalizer(p.inner, (*innerCompSolid).free)
		return p
	}
	return nil
}

type CompoundIterator struct {
	inner *innerCompoundIterator
}
type innerCompoundIterator struct {
	val *C.struct__topo_compound_iterator_t
}

func TopoMakeCompoundIterator(p Shape) *CompoundIterator {
	wr := &CompoundIterator{inner: &innerCompoundIterator{val: C.topo_compound_iterator_make(p.inner.val)}}
	runtime.SetFinalizer(wr.inner, (*innerCompoundIterator).free)
	return wr
}

func (t *innerCompoundIterator) free() {
	C.topo_compound_iterator_free(t.val)
}

func (t *CompoundIterator) Next() *Compound {
	v := C.topo_compound_iterator_next(t.inner.val)
	if v != nil {
		var val C.struct__topo_compound_t
		val.shp = v
		p := &Compound{inner: &innerCompound{val: val}}
		runtime.SetFinalizer(p.inner, (*innerCompound).free)
		return p
	}
	return nil
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

type ShellIterator struct {
	inner *innerShellIterator
}
type innerShellIterator struct {
	val *C.struct__topo_shell_iterator_t
}

func TopoMakeShellIterator(p Shape) *ShellIterator {
	wr := &ShellIterator{inner: &innerShellIterator{val: C.topo_shell_iterator_make(p.inner.val)}}
	runtime.SetFinalizer(wr.inner, (*innerShellIterator).free)
	return wr
}

func (t *innerShellIterator) free() {
	C.topo_shell_iterator_free(t.val)
}

func (t *ShellIterator) Next() *Shell {
	v := C.topo_shell_iterator_next(t.inner.val)
	if v != nil {
		var val C.struct__topo_shell_t
		val.shp = v
		p := &Shell{inner: &innerShell{val: val}}
		runtime.SetFinalizer(p.inner, (*innerShell).free)
		return p
	}
	return nil
}

type SolidIterator struct {
	inner *innerSolidIterator
}
type innerSolidIterator struct {
	val *C.struct__topo_solid_iterator_t
}

func TopoMakeSolidIterator(p Shape) *SolidIterator {
	wr := &SolidIterator{inner: &innerSolidIterator{val: C.topo_solid_iterator_make(p.inner.val)}}
	runtime.SetFinalizer(wr.inner, (*innerSolidIterator).free)
	return wr
}

func (t *innerSolidIterator) free() {
	C.topo_solid_iterator_free(t.val)
}

func (t *SolidIterator) Next() *Solid {
	v := C.topo_solid_iterator_next(t.inner.val)
	if v != nil {
		var val C.struct__topo_solid_t
		val.shp = v
		p := &Solid{inner: &innerSolid{val: val}}
		runtime.SetFinalizer(p.inner, (*innerSolid).free)
		return p
	}
	return nil
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
