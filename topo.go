package topo

/*
#include <stdlib.h>
#include "topo_c_api.h"
#cgo CFLAGS: -I  ./libs
#cgo linux CXXFLAGS: -I ./libs  -std=gnu++14
#cgo darwin,amd64 CXXFLAGS: -I ./libs  -std=gnu++14
#cgo darwin,arm64 CXXFLAGS: -I ./libs  -std=gnu++14
#cgo windows CXXFLAGS: -I ./libs  -std=gnu++14
#cgo darwin LDFLAGS: -L /usr/local/gfortran/lib -Wl,-rpath,/usr/local/gfortran/lib
#cgo linux,amd64 LDFLAGS: -L ./libs/linux  -Wl,--start-group -ltopo -lpthread -lnlopt -lfreetype -lzlib -lfontconfig -lexpat -lxml2 -licudata -licui18n -licudt -licuuc -lifc -lgeometry_mapping_ifc2x3 -lgeometry_mapping_ifc4 -lgeometry_mapping_ifc4x1 -lgeometry_mapping_ifc4x2 -lgeometry_mapping_ifc4x3_add1 -lgeometry_mapping_ifc4x3_add2 -lgeometry_mapping_ifc4x3_tc1 -lgeometry_mapping_ifc4x3 -lgeometry_serializer_ifc2x3 -lgeometry_serializer_ifc4 -lgeometry_serializer_ifc4x1 -lgeometry_serializer_ifc4x2 -lgeometry_serializer_ifc4x3_add1 -lgeometry_serializer_ifc4x3_add2 -lgeometry_serializer_ifc4x3_tc1 -lgeometry_serializer_ifc4x3 -lread_data_ifc2x3 -lread_data_ifc4 -lread_data_ifc4x1 -lread_data_ifc4x2 -lread_data_ifc4x3_add1 -lread_data_ifc4x3_add2 -lread_data_ifc4x3_tc1 -lread_data_ifc4x3  -lstdc++ -ldl -lm  -lTKernel -lTKMath -lTKG2d -lTKG3d -lTKGeomBase -lTKBRep -lTKService -lTKV3d -lTKShHealing -lTKTopAlgo -lTKMesh -lTKGeomAlgo -lTKHLR -lTKOffset -lTKFillet -lTKFeat -lTKXMesh -lTKMeshVS -lTKCDF -lTKLCAF -lTKCAF -lTKBO -lTKPrim -lTKBinL -lTKXmlL -lTKBin -lTKXml -lTKStdL -lTKStd -lTKTObj -lTKBinTObj -lTKXmlTObj -lTKVCAF -lTKXDE -lTKXSBase -lTKSTEPBase -lTKSTEPAttr -lTKSTEP209 -lTKSTEP -lTKIGES -lTKBool -lTKXCAF -lTKXDEIGES -lTKXDESTEP -lTKSTL -lTKVRML -lTKRWMesh -lTKXmlXCAF -lTKBinXCAF -lTKXDECascade -lTKExpress -lboost_system_internal -lboost_filesystem_internal -lboost_date_time_internal -lboost_regex_internal -lboost_chrono_internal -lboost_program_options_internal -lboost_test_internal -Wl,--end-group
#cgo linux,arm64 LDFLAGS: -L ./libs/linux_arm -Wl,--start-group -ltopo -lpthread -lnlopt -lfreetype -lzlib -lfontconfig -lexpat -lxml2 -licudata -licui18n -licudt -licuuc -lifc -lgeometry_mapping_ifc2x3 -lgeometry_mapping_ifc4 -lgeometry_mapping_ifc4x1 -lgeometry_mapping_ifc4x2 -lgeometry_mapping_ifc4x3_add1 -lgeometry_mapping_ifc4x3_add2 -lgeometry_mapping_ifc4x3_tc1 -lgeometry_mapping_ifc4x3 -lgeometry_serializer_ifc2x3 -lgeometry_serializer_ifc4 -lgeometry_serializer_ifc4x1 -lgeometry_serializer_ifc4x2 -lgeometry_serializer_ifc4x3_add1 -lgeometry_serializer_ifc4x3_add2 -lgeometry_serializer_ifc4x3_tc1 -lgeometry_serializer_ifc4x3 -lread_data_ifc2x3 -lread_data_ifc4 -lread_data_ifc4x1 -lread_data_ifc4x2 -lread_data_ifc4x3_add1 -lread_data_ifc4x3_add2 -lread_data_ifc4x3_tc1 -lread_data_ifc4x3  -lstdc++ -ldl -lm  -lTKernel -lTKMath -lTKG2d -lTKG3d -lTKGeomBase -lTKBRep -lTKService -lTKV3d -lTKShHealing -lTKTopAlgo -lTKMesh -lTKGeomAlgo -lTKHLR -lTKOffset -lTKFillet -lTKFeat -lTKXMesh -lTKMeshVS -lTKCDF -lTKLCAF -lTKCAF -lTKBO -lTKPrim -lTKBinL -lTKXmlL -lTKBin -lTKXml -lTKStdL -lTKStd -lTKTObj -lTKBinTObj -lTKXmlTObj -lTKVCAF -lTKXDE -lTKXSBase -lTKSTEPBase -lTKSTEPAttr -lTKSTEP209 -lTKSTEP -lTKIGES -lTKBool -lTKXCAF -lTKXDEIGES -lTKXDESTEP -lTKSTL -lTKVRML -lTKRWMesh -lTKXmlXCAF -lTKBinXCAF -lTKXDECascade -lTKExpress -lboost_system_internal -lboost_filesystem_internal -lboost_date_time_internal -lboost_regex_internal -lboost_chrono_internal -lboost_program_options_internal -lboost_test_internal -Wl,--end-group
#cgo darwin,amd64 LDFLAGS: -L /usr/lib -lc++ -L ./libs/darwin  -lfontconfig -lfreetype -lzlib -lnlopt  -lexpat -lxml2 -licudata -licui18n -licudt -licuuc -ltopo  -lifc -lgeometry_mapping_ifc2x3 -lgeometry_mapping_ifc4 -lgeometry_mapping_ifc4x1 -lgeometry_mapping_ifc4x2 -lgeometry_mapping_ifc4x3_add1 -lgeometry_mapping_ifc4x3_add2 -lgeometry_mapping_ifc4x3_tc1 -lgeometry_mapping_ifc4x3 -lgeometry_serializer_ifc2x3 -lgeometry_serializer_ifc4 -lgeometry_serializer_ifc4x1 -lgeometry_serializer_ifc4x2 -lgeometry_serializer_ifc4x3_add1 -lgeometry_serializer_ifc4x3_add2 -lgeometry_serializer_ifc4x3_tc1 -lgeometry_serializer_ifc4x3 -lread_data_ifc2x3 -lread_data_ifc4 -lread_data_ifc4x1 -lread_data_ifc4x2 -lread_data_ifc4x3_add1 -lread_data_ifc4x3_add2 -lread_data_ifc4x3_tc1 -lread_data_ifc4x3  -lboost_system_internal -lboost_filesystem_internal -lboost_date_time_internal -lboost_regex_internal -lboost_chrono_internal -lboost_program_options_internal -lboost_test_internal -framework Foundation -framework CoreFoundation -framework CoreGraphics -framework Cocoa -lTKernel -lTKMath -lTKG2d -lTKG3d -lTKGeomBase -lTKBRep -lTKService -lTKV3d -lTKShHealing -lTKTopAlgo -lTKMesh -lTKGeomAlgo -lTKHLR -lTKOffset -lTKFillet -lTKFeat -lTKXMesh -lTKMeshVS -lTKCDF -lTKLCAF -lTKCAF -lTKBO -lTKPrim -lTKBinL -lTKXmlL -lTKBin -lTKXml -lTKStdL -lTKStd -lTKTObj -lTKBinTObj -lTKXmlTObj -lTKVCAF -lTKXDE -lTKXSBase -lTKSTEPBase -lTKSTEPAttr -lTKSTEP209 -lTKSTEP -lTKIGES -lTKBool -lTKXCAF -lTKXDEIGES -lTKXDESTEP -lTKSTL -lTKVRML -lTKRWMesh -lTKXmlXCAF -lTKBinXCAF -lTKXDECascade -lTKExpress
#cgo darwin,arm64 LDFLAGS: -L /usr/lib -lc++ -L ./libs/darwin_arm  -lfontconfig -lfreetype -lzlib -lnlopt  -lexpat -lxml2 -licudata -licui18n -licudt -licuuc -ltopo -lifc -lgeometry_mapping_ifc2x3 -lgeometry_mapping_ifc4 -lgeometry_mapping_ifc4x1 -lgeometry_mapping_ifc4x2 -lgeometry_mapping_ifc4x3_add1 -lgeometry_mapping_ifc4x3_add2 -lgeometry_mapping_ifc4x3_tc1 -lgeometry_mapping_ifc4x3 -lgeometry_serializer_ifc2x3 -lgeometry_serializer_ifc4 -lgeometry_serializer_ifc4x1 -lgeometry_serializer_ifc4x2 -lgeometry_serializer_ifc4x3_add1 -lgeometry_serializer_ifc4x3_add2 -lgeometry_serializer_ifc4x3_tc1 -lgeometry_serializer_ifc4x3 -lread_data_ifc2x3 -lread_data_ifc4 -lread_data_ifc4x1 -lread_data_ifc4x2 -lread_data_ifc4x3_add1 -lread_data_ifc4x3_add2 -lread_data_ifc4x3_tc1 -lread_data_ifc4x3  -lboost_system_internal -lboost_filesystem_internal -lboost_date_time_internal -lboost_regex_internal -lboost_chrono_internal -lboost_program_options_internal -lboost_test_internal -framework Foundation -framework CoreFoundation -framework CoreGraphics -framework Cocoa  -lTKernel -lTKMath -lTKG2d -lTKG3d -lTKGeomBase -lTKBRep -lTKService -lTKV3d -lTKShHealing -lTKTopAlgo -lTKMesh -lTKGeomAlgo -lTKHLR -lTKOffset -lTKFillet -lTKFeat -lTKXMesh -lTKMeshVS -lTKCDF -lTKLCAF -lTKCAF -lTKBO -lTKPrim -lTKBinL -lTKXmlL -lTKBin -lTKXml -lTKStdL -lTKStd -lTKTObj -lTKBinTObj -lTKXmlTObj -lTKVCAF -lTKXDE -lTKXSBase -lTKSTEPBase -lTKSTEPAttr -lTKSTEP209 -lTKSTEP -lTKIGES -lTKBool -lTKXCAF -lTKXDEIGES -lTKXDESTEP -lTKSTL -lTKVRML -lTKRWMesh -lTKXmlXCAF -lTKBinXCAF -lTKXDECascade -lTKExpress
#cgo windows LDFLAGS: -L ./libs/windows  -Wl,--start-group -ltopo -lnlopt -lfontconfig -lfreetype -lzlib -lexpat -lxml2 -licudata -licui18n  -licudt -licuuc -lws2_32  -lwinspool -lbcrypt -lifc -lgeometry_mapping_ifc2x3 -lgeometry_mapping_ifc4 -lgeometry_mapping_ifc4x1 -lgeometry_mapping_ifc4x2 -lgeometry_mapping_ifc4x3_add1 -lgeometry_mapping_ifc4x3_add2 -lgeometry_mapping_ifc4x3_tc1 -lgeometry_mapping_ifc4x3 -lgeometry_serializer_ifc2x3 -lgeometry_serializer_ifc4 -lgeometry_serializer_ifc4x1 -lgeometry_serializer_ifc4x2 -lgeometry_serializer_ifc4x3_add1 -lgeometry_serializer_ifc4x3_add2 -lgeometry_serializer_ifc4x3_tc1 -lgeometry_serializer_ifc4x3 -lread_data_ifc2x3 -lread_data_ifc4 -lread_data_ifc4x1 -lread_data_ifc4x2 -lread_data_ifc4x3_add1 -lread_data_ifc4x3_add2 -lread_data_ifc4x3_tc1 -lread_data_ifc4x3 -lstdc++  -lm  -lTKernel -lTKMath -lTKG2d -lTKG3d -lTKGeomBase -lTKBRep -lTKService -lTKV3d -lTKShHealing -lTKTopAlgo -lTKMesh -lTKGeomAlgo -lTKHLR -lTKOffset -lTKFillet -lTKFeat -lTKXMesh -lTKMeshVS -lTKCDF -lTKLCAF -lTKCAF -lTKBO -lTKPrim -lTKBinL -lTKXmlL -lTKBin -lTKXml -lTKStdL -lTKStd -lTKTObj -lTKBinTObj -lTKXmlTObj -lTKVCAF -lTKXDE -lTKXSBase -lTKSTEPBase -lTKSTEPAttr -lTKSTEP209 -lTKSTEP -lTKIGES -lTKBool -lTKXCAF -lTKXDEIGES -lTKXDESTEP -lTKSTL -lTKVRML -lTKRWMesh -lTKXmlXCAF -lTKBinXCAF -lTKXDECascade -lTKExpress -lboost_system_internal -lboost_filesystem_internal -lboost_date_time_internal -lboost_regex_internal -lboost_chrono_internal -lboost_program_options_internal -lboost_test_internal -Wl,--end-group
*/
import "C"

import (
	"runtime"
	"unsafe"
)

// 布尔运算类型 (src/topo_c_api.h: enum { BOOLFUSE, BOOLCUT, BOOLCOMMON })
// 以字面量钉死数值: 不经 cgo 常量转换, 避免 pkg.go.dev / CGO_ENABLED=0 分析环境
// 中 "constant unknown with invalid type" 的显示与诊断问题; 一致性由
// topo_const_alignment_test.go 对照 C 枚举运行时校验。
const (
	FUSE   = 0 // BOOLFUSE
	CUT    = 1 // BOOLCUT
	COMMON = 2 // BOOLCOMMON
)

// 方向枚举 (src/topo_c_api.h: enum { DIR_WEST.. DIR_DOWN })
const (
	WEST  = 0
	EAST  = 1
	NORTH = 2
	SOUTH = 3
	UP    = 4
	DOWN  = 5
)

// 纹理类型 (src/topo_c_api.h: enum { TextureCube.. TextureNormalAutoScale })
const (
	TextureCube            = 0
	TextureNormal          = 1
	TextureNormalAutoScale = 2
)

// 形状类型 (src/topo_c_api.h: enum { TopoSolid.. TopoShape })
const (
	TopoSolid     = 0
	TopoShell     = 1
	TopoFace      = 2
	TopoEdge      = 3
	TopoVertex    = 4
	TopoWire      = 5
	TopoCompound  = 6
	TopoCompSolid = 7
	TopoShape     = 8
)

// 朝向枚举 (src/topo_c_api.h: enum { ORI_FORWARD.. ORI_UNKNOW })
const (
	FORWARD  = 0
	REVERSED = 1
	INTERNAL = 2
	EXTERNAL = 3
	UNKNOW   = 4
)

type TopoLocation struct {
	inner *innerTopoLocation
}

type innerTopoLocation struct {
	val *C.struct__topo_location_t
}

func newTopoLocation(val *C.struct__topo_location_t) *TopoLocation {
	p := &TopoLocation{inner: &innerTopoLocation{val: val}}
	runtime.SetFinalizer(p.inner, (*innerTopoLocation).free)
	return p
}

func NewTopoLocation(t Trsf) *TopoLocation {
	p := &TopoLocation{inner: &innerTopoLocation{val: C.topo_location_new(t.val)}}
	runtime.SetFinalizer(p.inner, (*innerTopoLocation).free)
	return p
}

func (l *TopoLocation) Trsf() Trsf {
	return Trsf{val: C.topo_location_get_trsf(l.inner.val)}
}

func (l *innerTopoLocation) free() {
	C.topo_location_free(l.val)
	l.val = nil
}

type TopoVector struct {
	inner *innerVector
}

type innerVector struct {
	val *C.struct__topo_vector_t
}

func NewTopoVector(x, y, z float64) *TopoVector {
	p := &TopoVector{inner: &innerVector{val: C.topo_vector_new(C.double(x), C.double(y), C.double(z))}}
	runtime.SetFinalizer(p.inner, (*innerVector).free)
	return p
}

func (v *innerVector) free() {
	C.topo_vector_free(v.val)
	v.val = nil
}

func (v *TopoVector) X() float64 {
	return float64(C.topo_vector_get_x(v.inner.val))
}

func (v *TopoVector) Y() float64 {
	return float64(C.topo_vector_get_y(v.inner.val))
}

func (v *TopoVector) Z() float64 {
	return float64(C.topo_vector_get_z(v.inner.val))
}

type TopoPlane struct {
	inner *innerTopoPlane
}

type innerTopoPlane struct {
	val *C.struct__topo_plane_t
}

func NewTopoPlane(origin *Point3, xDir *Dir3, normal *Vector3) *TopoPlane {
	p := &TopoPlane{inner: &innerTopoPlane{val: C.topo_plane_new(&origin.val, &xDir.val, &normal.val)}}
	runtime.SetFinalizer(p.inner, (*innerTopoPlane).free)
	return p
}

func NewTopoPlaneFromNamed(name string, origin *Point3) *TopoPlane {
	cname := C.CString(name)
	defer C.free(unsafe.Pointer(cname))
	var cOrigin *C.pnt3d_t
	if origin != nil {
		cOrigin = &origin.val
	}
	p := &TopoPlane{inner: &innerTopoPlane{val: C.topo_plane_new_from_named(cname, cOrigin)}}
	runtime.SetFinalizer(p.inner, (*innerTopoPlane).free)
	return p
}

func (p *innerTopoPlane) free() {
	C.topo_plane_free(p.val)
	p.val = nil
}

func (p *TopoPlane) Origin() *Point3 {
	return &Point3{val: C.topo_plane_get_origin(p.inner.val)}
}

func (p *TopoPlane) XDir() *Dir3 {
	return &Dir3{val: C.topo_plane_get_x_dir(p.inner.val)}
}

func (p *TopoPlane) YDir() *Dir3 {
	return &Dir3{val: C.topo_plane_get_y_dir(p.inner.val)}
}

func (p *TopoPlane) ZDir() *Dir3 {
	return &Dir3{val: C.topo_plane_get_z_dir(p.inner.val)}
}

type TopoBBox struct {
	inner *innerTopoBBox
}

type innerTopoBBox struct {
	val *C.struct__topo_bbox_t
}

func (b *innerTopoBBox) free() {
	C.topo_bbox_free(b.val)
	b.val = nil
}

func NewTopoBBox(bbox BBox) *TopoBBox {
	p := &TopoBBox{inner: &innerTopoBBox{val: C.topo_bbox_new(bbox.val)}}
	runtime.SetFinalizer(p.inner, (*innerTopoBBox).free)
	return p
}

func NewTopoBBoxFromShape(shape *Shape) *TopoBBox {
	p := &TopoBBox{inner: &innerTopoBBox{val: C.topo_bbox_new_from_shape(shape.inner.val)}}
	runtime.SetFinalizer(p.inner, (*innerTopoBBox).free)
	return p
}

func (b *TopoBBox) BBox() BBox {
	return BBox{val: C.topo_bbox_get_bbox(b.inner.val)}
}

type TopoMatrix struct {
	inner *innerTopoMatrix
}
type innerTopoMatrix struct {
	val *C.struct__topo_matrix_t
}

func NewTopoMatrix(t Trsf) *TopoMatrix {
	p := &TopoMatrix{inner: &innerTopoMatrix{val: C.topo_matrix_new(t.val)}}
	runtime.SetFinalizer(p.inner, (*innerTopoMatrix).free)
	return p
}

func (m *innerTopoMatrix) free() {
	C.topo_matrix_free(m.val)
	m.val = nil
}

func (m *TopoMatrix) GetValue(row, col int) float64 {
	return float64(C.topo_matrix_get_value(m.inner.val, C.int(row), C.int(col)))
}
