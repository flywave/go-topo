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
	m.Faces = append(m.Faces, c)
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
