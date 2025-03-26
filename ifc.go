package topo

/*
#include <stdlib.h>
#include "ifc_c_api.h"
#cgo CFLAGS: -I  ./libs
#cgo linux CXXFLAGS: -I ./libs  -std=gnu++14
#cgo darwin,amd64 CXXFLAGS: -I ./libs  -std=gnu++14
#cgo darwin,arm64 CXXFLAGS: -I ./libs  -std=gnu++14
#cgo windows CXXFLAGS: -I ./libs  -std=gnu++14
*/
import "C"

import (
	"unsafe"
)

func init() {
	C.ifc_register_schema()
}

type IfcElementInfo struct {
	Shape    *Shape
	Id       int
	ParentId int
	Name     string
	Guid     string
}

func IfcToTopoShape(f string) []*IfcElementInfo {
	fl := C.CString(f)
	defer C.free(unsafe.Pointer(fl))
	count := 0
	sp := []*IfcElementInfo{}
	res := C.ifc_get_topo_shapes(fl, (*C.int)(unsafe.Pointer(&count)))
	if count == 0 {
		return sp
	}
	defer C.ifc_shapes_free(res)
	for i := 0; i < count; i++ {
		shp := NewShape(C.ifc_get_topo_shape(res, C.int(i)))
		sp = append(sp, &IfcElementInfo{
			Shape:    shp,
			Id:       shp.Id(),
			ParentId: shp.ParentId(),
			Name:     shp.Name(),
			Guid:     shp.Guid(),
		})
	}
	return sp
}

func IsIfc(f string) bool {
	fl := C.CString(f)
	defer C.free(unsafe.Pointer(fl))
	return bool(C.is_ifc_file(fl))
}
