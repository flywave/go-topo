package topo

/*
#include <stdlib.h>
#include "topo_c_api.h"
#cgo CFLAGS: -I  ./libs
#cgo linux CXXFLAGS: -I ./libs  -std=gnu++14
#cgo darwin,amd64 CXXFLAGS: -I ./libs  -std=gnu++14
#cgo darwin,arm64 CXXFLAGS: -I ./libs  -std=gnu++14
#cgo windows CXXFLAGS: -I ./libs  -std=gnu++14
#cgo linux LDFLAGS: -L ./libs/linux -Wl,--start-group -ltopo -lpthread -lfontconfig -lexpat -lxml2 -licudata -licui18n -licudt -licuuc -lifc23 -lifc4 -lifc41 -lifc42 -lifc43_rc1 -lstdc++ -ldl -lm  -lTKernel -lTKMath -lTKG2d -lTKG3d -lTKGeomBase -lTKBRep -lTKService -lTKV3d -lTKShHealing -lTKTopAlgo -lTKMesh -lTKGeomAlgo -lTKHLR -lTKOffset -lTKFillet -lTKFeat -lTKXMesh -lTKMeshVS -lTKCDF -lTKLCAF -lTKCAF -lTKBO -lTKPrim -lTKBinL -lTKXmlL -lTKBin -lTKXml -lTKStdL -lTKStd -lTKTObj -lTKBinTObj -lTKXmlTObj -lTKVCAF -lTKXDE -lTKXSBase -lTKSTEPBase -lTKSTEPAttr -lTKSTEP209 -lTKSTEP -lTKIGES -lTKBool -lTKXCAF -lTKXDEIGES -lTKXDESTEP -lTKSTL -lTKVRML -lTKRWMesh -lTKXmlXCAF -lTKBinXCAF -lTKXDECascade -lTKExpress -lboost_system_internal -lboost_filesystem_internal -lboost_date_time_internal -lboost_regex_internal -lboost_chrono_internal -lboost_program_options_internal -lboost_test_internal -Wl,--end-group
#cgo darwin,amd64 LDFLAGS: -L /usr/lib -lc++ -L ./libs/darwin -lfontconfig -lexpat -lxml2 -licudata -licui18n -licudt -licuuc -ltopo  -lifc23 -lifc4 -lifc41 -lifc42 -lifc43_rc1 -lboost_system_internal -lboost_filesystem_internal -lboost_date_time_internal -lboost_regex_internal -lboost_chrono_internal -lboost_program_options_internal -lboost_test_internal -framework Foundation -framework CoreFoundation -framework CoreGraphics -framework Cocoa -lTKernel -lTKMath -lTKG2d -lTKG3d -lTKGeomBase -lTKBRep -lTKService -lTKV3d -lTKShHealing -lTKTopAlgo -lTKMesh -lTKGeomAlgo -lTKHLR -lTKOffset -lTKFillet -lTKFeat -lTKXMesh -lTKMeshVS -lTKCDF -lTKLCAF -lTKCAF -lTKBO -lTKPrim -lTKBinL -lTKXmlL -lTKBin -lTKXml -lTKStdL -lTKStd -lTKTObj -lTKBinTObj -lTKXmlTObj -lTKVCAF -lTKXDE -lTKXSBase -lTKSTEPBase -lTKSTEPAttr -lTKSTEP209 -lTKSTEP -lTKIGES -lTKBool -lTKXCAF -lTKXDEIGES -lTKXDESTEP -lTKSTL -lTKVRML -lTKRWMesh -lTKXmlXCAF -lTKBinXCAF -lTKXDECascade -lTKExpress
#cgo darwin,arm64 LDFLAGS: -L /usr/lib -lc++ -L ./libs/darwin_arm  -lfontconfig -lexpat -lxml2 -licudata -licui18n -licudt -licuuc -ltopo -lifc23 -lifc4 -lifc41 -lifc42 -lifc43_rc1  -lboost_system_internal -lboost_filesystem_internal -lboost_date_time_internal -lboost_regex_internal -lboost_chrono_internal -lboost_program_options_internal -lboost_test_internal -framework Foundation -framework CoreFoundation -framework CoreGraphics -framework Cocoa  -lTKernel -lTKMath -lTKG2d -lTKG3d -lTKGeomBase -lTKBRep -lTKService -lTKV3d -lTKShHealing -lTKTopAlgo -lTKMesh -lTKGeomAlgo -lTKHLR -lTKOffset -lTKFillet -lTKFeat -lTKXMesh -lTKMeshVS -lTKCDF -lTKLCAF -lTKCAF -lTKBO -lTKPrim -lTKBinL -lTKXmlL -lTKBin -lTKXml -lTKStdL -lTKStd -lTKTObj -lTKBinTObj -lTKXmlTObj -lTKVCAF -lTKXDE -lTKXSBase -lTKSTEPBase -lTKSTEPAttr -lTKSTEP209 -lTKSTEP -lTKIGES -lTKBool -lTKXCAF -lTKXDEIGES -lTKXDESTEP -lTKSTL -lTKVRML -lTKRWMesh -lTKXmlXCAF -lTKBinXCAF -lTKXDECascade -lTKExpress
#cgo windows LDFLAGS: -L ./libs/windows  -Wl,--start-group -ltopo  -lfontconfig -lexpat -lxml2 -licudata -licui18n  -licudt -licuuc -lws2_32  -lwinspool -lbcrypt -lifc23 -lifc4 -lifc41 -lifc42 -lifc43_rc1 -lstdc++  -lm  -lTKernel -lTKMath -lTKG2d -lTKG3d -lTKGeomBase -lTKBRep -lTKService -lTKV3d -lTKShHealing -lTKTopAlgo -lTKMesh -lTKGeomAlgo -lTKHLR -lTKOffset -lTKFillet -lTKFeat -lTKXMesh -lTKMeshVS -lTKCDF -lTKLCAF -lTKCAF -lTKBO -lTKPrim -lTKBinL -lTKXmlL -lTKBin -lTKXml -lTKStdL -lTKStd -lTKTObj -lTKBinTObj -lTKXmlTObj -lTKVCAF -lTKXDE -lTKXSBase -lTKSTEPBase -lTKSTEPAttr -lTKSTEP209 -lTKSTEP -lTKIGES -lTKBool -lTKXCAF -lTKXDEIGES -lTKXDESTEP -lTKSTL -lTKVRML -lTKRWMesh -lTKXmlXCAF -lTKBinXCAF -lTKXDECascade -lTKExpress -lboost_system_internal -lboost_filesystem_internal -lboost_date_time_internal -lboost_regex_internal -lboost_chrono_internal -lboost_program_options_internal -lboost_test_internal -Wl,--end-group
*/
import "C"

import (
	"runtime"
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
