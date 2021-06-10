package topo

/*
#include <stdlib.h>
#include "ifc_c_api.h"
#cgo CFLAGS: -I  ./libs
#cgo linux CXXFLAGS: -I  ./libs  -std=gnu++14
#cgo darwin CXXFLAGS: -I  ./libs  -std=gnu++14
#cgo windows CXXFLAGS:-I  ./libs  -std=gnu++14
*/
import "C"

import (
	"unsafe"
)

func init() {
	C.ifc_register_schema()
}

func IfcToTopoShape(f string) []Shape {
	fl := C.CString(f)
	defer C.free(unsafe.Pointer(fl))
	count := 0
	sp := []Shape{}
	res := C.ifc_get_topo_shapes(fl, (*C.int)(unsafe.Pointer(&count)))
	if count == 0 {
		return sp
	}
	defer C.ifc_shapes_free(res)
	for i := 0; i < count; i++ {
		sp = append(sp, *NewShape(C.ifc_get_topo_shape(res, C.int(i))))
	}
	return sp
}

func IsIfc(f string) bool {
	fl := C.CString(f)
	defer C.free(unsafe.Pointer(fl))
	return bool(C.is_ifc_file(fl))
}
