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
import "unsafe"

//export begin
func begin(ctx unsafe.Pointer) {
	(*MeshReceiver)(ctx).begin()
}

//export end
func end(ctx unsafe.Pointer) {
	(*MeshReceiver)(ctx).end()
}

//export appendFace
func appendFace(ctx unsafe.Pointer, color C.struct__color_t) C.int {
	return C.int((*MeshReceiver)(ctx).appendFace(Color{val: color}))
}

//export appendNodeNorm
func appendNodeNorm(ctx unsafe.Pointer, face C.int, p, n C.struct__pnt3d_t) {
	(*MeshReceiver)(ctx).appendNodeNorm(int(face), Point3{val: p}, Point3{val: n})
}

//export appendNodeNormUv
func appendNodeNormUv(ctx unsafe.Pointer, face C.int, p, n C.struct__pnt3d_t, uv C.struct__pnt2d_t) {
	(*MeshReceiver)(ctx).appendNodeNormUv(int(face), Point3{val: p}, Point3{val: n}, Point2{val: uv})
}

//export appendNode
func appendNode(ctx unsafe.Pointer, face C.int, p C.struct__pnt3d_t) {
	(*MeshReceiver)(ctx).appendNode(int(face), Point3{val: p})
}

//export appendTriangle
func appendTriangle(ctx unsafe.Pointer, face C.int, a C.int, b C.int, c C.int) {
	(*MeshReceiver)(ctx).appendTriangle(int(face), [3]int{int(a), int(b), int(c)})
}
