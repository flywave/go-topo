package topovis

/*
#include <stdlib.h>
#include "topo_c_api.h"
#cgo CFLAGS: -I ./
#cgo linux CXXFLAGS: -I ./include/oce -I ./include/linux/oce -I ./
#cgo darwin CXXFLAGS: -I ./include/oce -I ./include/darwin/oce -I ./
#cgo windows CXXFLAGS:  -I ./include/oce -I ./include/windows/oce -I ./
#cgo linux LDFLAGS: -L ./lib/linux_amd64 -L /usr/lib/x86_64-linux-gnu/ -Wl,--start-group -lpthread -ldl -lm -lGL -lGLU -lX11 -lfreetype -lTKernel -lTKMath -lTKG2d -lTKG3d -lTKGeomBase -lTKBRep -lTKGeomAlgo -lTKTopAlgo -lTKPrim -lTKBO -lTKHLR -lTKMesh -lTKShHealing -lTKXMesh -lTKBool -lTKFillet -lTKFeat -lTKOffset -lTKService -lTKV3d -lTKCDF -lPTKernel -lTKLCAF -lFWOSPlugin -lTKPShape -lTKBinL -lTKXmlL -lTKPLCAF -lTKTObj -lTKShapeSchema -lTKStdLSchema -lTKCAF -lTKBin -lTKXml -lTKPCAF -lTKBinTObj -lTKXmlTObj -lTKStdSchema -lTKSTL -lTKXSBase -lTKSTEPBase -lTKIGES -lTKSTEPAttr -lTKSTEP209 -lTKSTEP -lTKVRML -lTKXCAF -lTKXCAFSchema -lTKXmlXCAF -lTKBinXCAF -lTKXDEIGES -lTKXDESTEP -Wl,--end-group
#cgo darwin LDFLAGS: -L ./lib/darwin_amd64 -lfreetype -lTKernel -lTKMath -lTKG2d -lTKG3d -lTKGeomBase -lTKBRep -lTKGeomAlgo -lTKTopAlgo -lTKPrim -lTKBO -lTKHLR -lTKMesh -lTKShHealing -lTKXMesh -lTKBool -lTKFillet -lTKFeat -lTKOffset -lTKService -lTKV3d -lTKCDF -lPTKernel -lTKLCAF -lFWOSPlugin -lTKPShape -lTKBinL -lTKXmlL -lTKPLCAF -lTKTObj -lTKShapeSchema -lTKStdLSchema -lTKCAF -lTKBin -lTKXml -lTKPCAF -lTKBinTObj -lTKXmlTObj -lTKStdSchema -lTKSTL -lTKXSBase -lTKSTEPBase -lTKIGES -lTKSTEPAttr -lTKSTEP209 -lTKSTEP -lTKVRML -lTKXCAF -lTKXCAFSchema -lTKXmlXCAF -lTKBinXCAF -lTKXDEIGES -lTKXDESTEP
#cgo windows LDFLAGS: -L ./lib/windows_amd64 -lfreetype -lTKernel -lTKMath -lTKG2d -lTKG3d -lTKGeomBase -lTKBRep -lTKGeomAlgo -lTKTopAlgo -lTKPrim -lTKBO -lTKHLR -lTKMesh -lTKShHealing -lTKXMesh -lTKBool -lTKFillet -lTKFeat -lTKOffset -lTKService -lTKV3d -lTKCDF -lPTKernel -lTKLCAF -lFWOSPlugin -lTKPShape -lTKBinL -lTKXmlL -lTKPLCAF -lTKTObj -lTKShapeSchema -lTKStdLSchema -lTKCAF -lTKBin -lTKXml -lTKPCAF -lTKBinTObj -lTKXmlTObj -lTKStdSchema -lTKSTL -lTKXSBase -lTKSTEPBase -lTKIGES -lTKSTEPAttr -lTKSTEP209 -lTKSTEP -lTKVRML -lTKXCAF -lTKXCAFSchema -lTKXmlXCAF -lTKBinXCAF -lTKXDEIGES -lTKXDESTEP
*/
import "C"

import (
	"unsafe"
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
	val   *C.struct__topo_mesh_receiver_t
	index int
	Faces []Color
	Vers  [][]Point3
	Norms [][]Point3
	Tris  [][][3]int
}

func NewMeshReceiver() *MeshReceiver {
	ret := &MeshReceiver{val: nil, index: -1}
	var cb C.struct__mesh_receiver_cb_t
	cb.ctx = unsafe.Pointer(ret)
	ret.val = C.topo_mesh_receiver_new(cb)
	return ret
}

func (m *MeshReceiver) begin() {
	m.Faces = append(m.Faces, Color{})
	m.Vers = append(m.Vers, []Point3{})
	m.Norms = append(m.Norms, []Point3{})
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

func (m *MeshReceiver) appendNode(f int, p Point3) {
	m.Vers[f] = append(m.Vers[f], p)
}

func (m *MeshReceiver) appendTriangle(f int, tri [3]int) {
	m.Tris[f] = append(m.Tris[f], tri)
}

func (m *MeshReceiver) Free() {
	C.topo_mesh_receiver_free(m.val)
	m.val = nil
}

type Location struct {
	val *C.struct__topo_location_t
}

func (l *Location) Free() {
	C.topo_location_free(l.val)
	l.val = nil
}

type Shape struct {
	val *C.struct__topo_shape_t
}

func (t *Shape) Free() {
	C.topo_shape_free(t.val)
	t.val = nil
}

type CompSolid struct {
	val C.struct__topo_comp_solid_t
}

func (t *CompSolid) Free() {
	C.topo_comp_solid_free(t.val)
}

type Compound struct {
	val C.struct__topo_compound_t
}

func (t *Compound) Free() {
	C.topo_compound_free(t.val)
}

type Edge struct {
	val C.struct__topo_edge_t
}

func (t *Edge) Free() {
	C.topo_edge_free(t.val)
}

type Face struct {
	val C.struct__topo_face_t
}

func (t *Face) Free() {
	C.topo_face_free(t.val)
}

type Shell struct {
	val C.struct__topo_shell_t
}

func (t *Shell) Free() {
	C.topo_shell_free(t.val)
}

type Solid struct {
	val C.struct__topo_solid_t
}

func (t *Solid) Free() {
	C.topo_solid_free(t.val)
}

type Vertex struct {
	val C.struct__topo_vertex_t
}

func (t *Vertex) Free() {
	C.topo_vertex_free(t.val)
}

type Wire struct {
	val C.struct__topo_wire_t
}

func (t *Wire) Free() {
	C.topo_wire_free(t.val)
}
