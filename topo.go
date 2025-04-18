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
#cgo linux,amd64 LDFLAGS: -L ./lib/linux  -Wl,--start-group -ltopo -lpthread -lipopt -lfreetype -lzlib -llapack -lblas -lma27 -lmetis -lnlopt -lgfortran -lfontconfig -lexpat -lxml2 -licudata -licui18n -licudt -licuuc -lifc23 -lifc4 -lifc41 -lifc42 -lifc43_rc1 -lstdc++ -ldl -lm  -lTKernel -lTKMath -lTKG2d -lTKG3d -lTKGeomBase -lTKBRep -lTKService -lTKV3d -lTKShHealing -lTKTopAlgo -lTKMesh -lTKGeomAlgo -lTKHLR -lTKOffset -lTKFillet -lTKFeat -lTKXMesh -lTKMeshVS -lTKCDF -lTKLCAF -lTKCAF -lTKBO -lTKPrim -lTKBinL -lTKXmlL -lTKBin -lTKXml -lTKStdL -lTKStd -lTKTObj -lTKBinTObj -lTKXmlTObj -lTKVCAF -lTKXDE -lTKXSBase -lTKSTEPBase -lTKSTEPAttr -lTKSTEP209 -lTKSTEP -lTKIGES -lTKBool -lTKXCAF -lTKXDEIGES -lTKXDESTEP -lTKSTL -lTKVRML -lTKRWMesh -lTKXmlXCAF -lTKBinXCAF -lTKXDECascade -lTKExpress -lboost_system_internal -lboost_filesystem_internal -lboost_date_time_internal -lboost_regex_internal -lboost_chrono_internal -lboost_program_options_internal -lboost_test_internal -Wl,--end-group
#cgo linux,arm64 LDFLAGS: -L ./lib/linux_arm -Wl,--start-group -ltopo -lpthread -lipopt -lfreetype -lzlib -llapack -lblas -lma27 -lmetis -lnlopt -lgfortran -lfontconfig -lexpat -lxml2 -licudata -licui18n -licudt -licuuc -lifc23 -lifc4 -lifc41 -lifc42 -lifc43_rc1 -lstdc++ -ldl -lm  -lTKernel -lTKMath -lTKG2d -lTKG3d -lTKGeomBase -lTKBRep -lTKService -lTKV3d -lTKShHealing -lTKTopAlgo -lTKMesh -lTKGeomAlgo -lTKHLR -lTKOffset -lTKFillet -lTKFeat -lTKXMesh -lTKMeshVS -lTKCDF -lTKLCAF -lTKCAF -lTKBO -lTKPrim -lTKBinL -lTKXmlL -lTKBin -lTKXml -lTKStdL -lTKStd -lTKTObj -lTKBinTObj -lTKXmlTObj -lTKVCAF -lTKXDE -lTKXSBase -lTKSTEPBase -lTKSTEPAttr -lTKSTEP209 -lTKSTEP -lTKIGES -lTKBool -lTKXCAF -lTKXDEIGES -lTKXDESTEP -lTKSTL -lTKVRML -lTKRWMesh -lTKXmlXCAF -lTKBinXCAF -lTKXDECascade -lTKExpress -lboost_system_internal -lboost_filesystem_internal -lboost_date_time_internal -lboost_regex_internal -lboost_chrono_internal -lboost_program_options_internal -lboost_test_internal -Wl,--end-group
#cgo darwin,amd64 LDFLAGS: -L /usr/lib -lc++ -L ./libs/darwin  -lgfortran -lfontconfig -lfreetype -lzlib -lipopt  -lma27 -lmetis -lnlopt -framework Accelerate  -lexpat -lxml2 -licudata -licui18n -licudt -licuuc -ltopo  -lifc23 -lifc4 -lifc41 -lifc42 -lifc43_rc1 -lboost_system_internal -lboost_filesystem_internal -lboost_date_time_internal -lboost_regex_internal -lboost_chrono_internal -lboost_program_options_internal -lboost_test_internal -framework Foundation -framework CoreFoundation -framework CoreGraphics -framework Cocoa -lTKernel -lTKMath -lTKG2d -lTKG3d -lTKGeomBase -lTKBRep -lTKService -lTKV3d -lTKShHealing -lTKTopAlgo -lTKMesh -lTKGeomAlgo -lTKHLR -lTKOffset -lTKFillet -lTKFeat -lTKXMesh -lTKMeshVS -lTKCDF -lTKLCAF -lTKCAF -lTKBO -lTKPrim -lTKBinL -lTKXmlL -lTKBin -lTKXml -lTKStdL -lTKStd -lTKTObj -lTKBinTObj -lTKXmlTObj -lTKVCAF -lTKXDE -lTKXSBase -lTKSTEPBase -lTKSTEPAttr -lTKSTEP209 -lTKSTEP -lTKIGES -lTKBool -lTKXCAF -lTKXDEIGES -lTKXDESTEP -lTKSTL -lTKVRML -lTKRWMesh -lTKXmlXCAF -lTKBinXCAF -lTKXDECascade -lTKExpress
#cgo darwin,arm64 LDFLAGS: -L /usr/lib -lc++ -L ./libs/darwin_arm  -lgfortran -lfontconfig -lfreetype -lzlib -lipopt  -lma27 -lmetis -lnlopt -framework Accelerate  -lexpat -lxml2 -licudata -licui18n -licudt -licuuc -ltopo -lifc23 -lifc4 -lifc41 -lifc42 -lifc43_rc1  -lboost_system_internal -lboost_filesystem_internal -lboost_date_time_internal -lboost_regex_internal -lboost_chrono_internal -lboost_program_options_internal -lboost_test_internal -framework Foundation -framework CoreFoundation -framework CoreGraphics -framework Cocoa  -lTKernel -lTKMath -lTKG2d -lTKG3d -lTKGeomBase -lTKBRep -lTKService -lTKV3d -lTKShHealing -lTKTopAlgo -lTKMesh -lTKGeomAlgo -lTKHLR -lTKOffset -lTKFillet -lTKFeat -lTKXMesh -lTKMeshVS -lTKCDF -lTKLCAF -lTKCAF -lTKBO -lTKPrim -lTKBinL -lTKXmlL -lTKBin -lTKXml -lTKStdL -lTKStd -lTKTObj -lTKBinTObj -lTKXmlTObj -lTKVCAF -lTKXDE -lTKXSBase -lTKSTEPBase -lTKSTEPAttr -lTKSTEP209 -lTKSTEP -lTKIGES -lTKBool -lTKXCAF -lTKXDEIGES -lTKXDESTEP -lTKSTL -lTKVRML -lTKRWMesh -lTKXmlXCAF -lTKBinXCAF -lTKXDECascade -lTKExpress
#cgo windows LDFLAGS: -L ./libs/windows  -Wl,--start-group -ltopo -lipopt -llapack -lblas -lma27 -lmetis -lnlopt -lgfortran  -lfontconfig -lfreetype -lzlib -lexpat -lxml2 -licudata -licui18n  -licudt -licuuc -lws2_32  -lwinspool -lbcrypt -lifc23 -lifc4 -lifc41 -lifc42 -lifc43_rc1 -lstdc++  -lm  -lTKernel -lTKMath -lTKG2d -lTKG3d -lTKGeomBase -lTKBRep -lTKService -lTKV3d -lTKShHealing -lTKTopAlgo -lTKMesh -lTKGeomAlgo -lTKHLR -lTKOffset -lTKFillet -lTKFeat -lTKXMesh -lTKMeshVS -lTKCDF -lTKLCAF -lTKCAF -lTKBO -lTKPrim -lTKBinL -lTKXmlL -lTKBin -lTKXml -lTKStdL -lTKStd -lTKTObj -lTKBinTObj -lTKXmlTObj -lTKVCAF -lTKXDE -lTKXSBase -lTKSTEPBase -lTKSTEPAttr -lTKSTEP209 -lTKSTEP -lTKIGES -lTKBool -lTKXCAF -lTKXDEIGES -lTKXDESTEP -lTKSTL -lTKVRML -lTKRWMesh -lTKXmlXCAF -lTKBinXCAF -lTKXDECascade -lTKExpress -lboost_system_internal -lboost_filesystem_internal -lboost_date_time_internal -lboost_regex_internal -lboost_chrono_internal -lboost_program_options_internal -lboost_test_internal -Wl,--end-group
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

type TopoLocation struct {
	inner *innerTopoLocation
}

type innerTopoLocation struct {
	val *C.struct__topo_location_t
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
	p := &TopoPlane{inner: &innerTopoPlane{val: C.topo_plane_new_from_named(cname, &origin.val)}}
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
