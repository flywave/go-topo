package topovis

/*
#include <stdlib.h>
#include "topovis_c_api.h"
#cgo CFLAGS: -I ./
#cgo linux CXXFLAGS: -I ./include/oce -I ./include/linux/oce -I ./
#cgo darwin CXXFLAGS: -I ./include/oce -I ./include/darwin/oce -I ./
#cgo windows CXXFLAGS:  -I ./include/oce -I ./include/windows/oce -I ./
#cgo linux LDFLAGS: -L ./lib/linux_amd64 -L /usr/lib/x86_64-linux-gnu/ -Wl,--start-group -lpthread -ldl -lm -lGL -lGLU -lX11 -lfreetype -lTKernel -lTKMath -lTKG2d -lTKG3d -lTKGeomBase -lTKBRep -lTKGeomAlgo -lTKTopAlgo -lTKPrim -lTKBO -lTKHLR -lTKMesh -lTKShHealing -lTKXMesh -lTKBool -lTKFillet -lTKFeat -lTKOffset -lTKService -lTKV3d -lTKCDF -lPTKernel -lTKLCAF -lFWOSPlugin -lTKPShape -lTKBinL -lTKXmlL -lTKPLCAF -lTKTObj -lTKShapeSchema -lTKStdLSchema -lTKCAF -lTKBin -lTKXml -lTKPCAF -lTKBinTObj -lTKXmlTObj -lTKStdSchema -lTKSTL -lTKXSBase -lTKSTEPBase -lTKIGES -lTKSTEPAttr -lTKSTEP209 -lTKSTEP -lTKVRML -lTKXCAF -lTKXCAFSchema -lTKXmlXCAF -lTKBinXCAF -lTKXDEIGES -lTKXDESTEP -Wl,--end-group
#cgo darwin LDFLAGS: -L ./lib/darwin_amd64 -lfreetype -lTKernel -lTKMath -lTKG2d -lTKG3d -lTKGeomBase -lTKBRep -lTKGeomAlgo -lTKTopAlgo -lTKPrim -lTKBO -lTKHLR -lTKMesh -lTKShHealing -lTKXMesh -lTKBool -lTKFillet -lTKFeat -lTKOffset -lTKService -lTKV3d -lTKCDF -lPTKernel -lTKLCAF -lFWOSPlugin -lTKPShape -lTKBinL -lTKXmlL -lTKPLCAF -lTKTObj -lTKShapeSchema -lTKStdLSchema -lTKCAF -lTKBin -lTKXml -lTKPCAF -lTKBinTObj -lTKXmlTObj -lTKStdSchema -lTKSTL -lTKXSBase -lTKSTEPBase -lTKIGES -lTKSTEPAttr -lTKSTEP209 -lTKSTEP -lTKVRML -lTKXCAF -lTKXCAFSchema -lTKXmlXCAF -lTKBinXCAF -lTKXDEIGES -lTKXDESTEP
#cgo windows LDFLAGS: -L ./lib/windows_amd64 -lfreetype -lTKernel -lTKMath -lTKG2d -lTKG3d -lTKGeomBase -lTKBRep -lTKGeomAlgo -lTKTopAlgo -lTKPrim -lTKBO -lTKHLR -lTKMesh -lTKShHealing -lTKXMesh -lTKBool -lTKFillet -lTKFeat -lTKOffset -lTKService -lTKV3d -lTKCDF -lPTKernel -lTKLCAF -lFWOSPlugin -lTKPShape -lTKBinL -lTKXmlL -lTKPLCAF -lTKTObj -lTKShapeSchema -lTKStdLSchema -lTKCAF -lTKBin -lTKXml -lTKPCAF -lTKBinTObj -lTKXmlTObj -lTKStdSchema -lTKSTL -lTKXSBase -lTKSTEPBase -lTKIGES -lTKSTEPAttr -lTKSTEP209 -lTKSTEP -lTKVRML -lTKXCAF -lTKXCAFSchema -lTKXmlXCAF -lTKBinXCAF -lTKXDEIGES -lTKXDESTEP
*/
import "C"

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

type CompSolid struct {
	val *C.struct__topo_comp_solid_t
}

type Compound struct {
	val *C.struct__topo_compound_t
}

type Edge struct {
	val *C.struct__topo_edge_t
}

type Face struct {
	val *C.struct__topo_face_t
}

type Shape struct {
	val *C.struct__topo_shape_t
}

type Shell struct {
	val *C.struct__topo_shell_t
}

type Solid struct {
	val *C.struct__topo_solid_t
}

type Vertex struct {
	val *C.struct__topo_vertex_t
}

type Wire struct {
	val *C.struct__topo_wire_t
}
