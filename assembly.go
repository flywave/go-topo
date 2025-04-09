package topo

/*
#include <stdlib.h>
#include "assembly_c_api.h"
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

type AssemblyObject struct {
	inner *innerAssemblyObject
}

type innerAssemblyObject struct {
	val *C.struct__assembly_object_t
}

func NewAssemblyObjectFromShpe(shp Shape) *AssemblyObject {
	c := &AssemblyObject{inner: &innerAssemblyObject{val: C.assembly_object_create_from_shape(shp.inner.val)}}
	runtime.SetFinalizer(c.inner, (*innerAssemblyObject).free)
	return c
}

func (c *innerAssemblyObject) free() {
	C.assembly_object_free(c.val)
}

func (c *AssemblyObject) GetShape() *Shape {
	shp := &Shape{inner: &innerShape{C.assembly_object_get_shape(c.inner.val)}}
	runtime.SetFinalizer(c.inner, (*innerShape).free)
	return shp
}

func (c *AssemblyObject) GetWorkplane() *Workplane {
	return &Workplane{inner: &innerWorkplane{C.assembly_object_get_workplane(c.inner.val)}}
}

func (c *AssemblyObject) IsShape() bool {
	return bool(C.assembly_object_is_shape(c.inner.val))
}

func (c *AssemblyObject) IsWorkplane() bool {
	return bool(C.assembly_object_is_workplane(c.inner.val))
}

type AssemblyElament struct {
	inner *innerAssemblyElament
}

type innerAssemblyElament struct {
	val *C.struct__assembly_element_t
}

func (c *innerAssemblyElament) free() {
	C.assembly_element_free(c.val)
}

func (c *AssemblyElament) GetName() string {
	return C.GoString(C.assembly_element_get_name(c.inner.val))
}

func (c *AssemblyElament) GetShape() *Shape {
	shp := &Shape{inner: &innerShape{C.assembly_element_get_shape(c.inner.val)}}
	runtime.SetFinalizer(c.inner, (*innerShape).free)
	return shp
}

func (c *AssemblyElament) GetColor() *Color {
	return &Color{C.assembly_element_get_color(c.inner.val)}
}

func (c *AssemblyElament) GetLocation() *TopoLocation {
	p := &TopoLocation{inner: &innerTopoLocation{val: C.assembly_element_get_location(c.inner.val)}}
	runtime.SetFinalizer(p.inner, (*innerTopoLocation).free)
	return p
}

type AssemblyConstraintParm struct {
	inner *innerAssemblyConstraintParm
}

type innerAssemblyConstraintParm struct {
	val *C.struct__constraint_param_t
}

func NewAssemblyConstraintParmFromDouble(value float64) *AssemblyConstraintParm {
	c := &AssemblyConstraintParm{inner: &innerAssemblyConstraintParm{val: C.constraint_param_create_from_double(C.double(value))}}
	runtime.SetFinalizer(c.inner, (*innerAssemblyConstraintParm).free)
	return c
}

func NewAssemblyConstraintParmFromDouble3(x, y, z float64) *AssemblyConstraintParm {
	c := &AssemblyConstraintParm{inner: &innerAssemblyConstraintParm{val: C.constraint_param_create_from_double3(C.double(x), C.double(y), C.double(z))}}
	runtime.SetFinalizer(c.inner, (*innerAssemblyConstraintParm).free)
	return c
}

func NewAssemblyConstraintParmFromDouble2(x, y float64) *AssemblyConstraintParm {
	c := &AssemblyConstraintParm{inner: &innerAssemblyConstraintParm{val: C.constraint_param_create_from_double2(C.double(x), C.double(y))}}
	runtime.SetFinalizer(c.inner, (*innerAssemblyConstraintParm).free)
	return c
}

func (c *innerAssemblyConstraintParm) free() {
	C.constraint_param_free(c.val)
}

type Assembly struct {
	inner *innerAssembly
}

type innerAssembly struct {
	val *C.struct__assembly_t
}

func (c *innerAssembly) free() {
	C.assembly_free(c.val)
}

func NewAssembly(obj *AssemblyObject, loc *TopoLocation, name string, color *Color) *Assembly {
	cname := C.CString(name)
	defer C.free(unsafe.Pointer(cname))
	var color_ *C.struct__color_t
	if color != nil {
		color_ = &color.val
	} else {
		color_ = nil
	}
	c := &Assembly{inner: &innerAssembly{val: C.assembly_create(obj.inner.val, loc.inner.val, cname, color_)}}
	runtime.SetFinalizer(c.inner, (*innerAssembly).free)
	return c
}

func (c *Assembly) Copy() *Assembly {
	cp := &Assembly{inner: &innerAssembly{val: C.assembly_copy(c.inner.val)}}
	runtime.SetFinalizer(cp.inner, (*innerAssembly).free)
	return cp
}

func (c *Assembly) AddObject(obj *AssemblyObject, loc *TopoLocation, name string, color *Color) *Assembly {
	cname := C.CString(name)
	defer C.free(unsafe.Pointer(cname))
	var color_ *C.struct__color_t
	if color != nil {
		color_ = &color.val
	}
	C.assembly_add_object(c.inner.val, obj.inner.val, loc.inner.val, cname, color_)
	return c
}

func (c *Assembly) AddAssembly(obj *Assembly, loc *TopoLocation, name string, color *Color) *Assembly {
	cname := C.CString(name)
	defer C.free(unsafe.Pointer(cname))
	var color_ *C.struct__color_t
	if color != nil {
		color_ = &color.val
	}
	C.assembly_add_assembly(c.inner.val, obj.inner.val, loc.inner.val, cname, color_)
	return c
}

func (c *Assembly) Remove(name string) *Assembly {
	cname := C.CString(name)
	defer C.free(unsafe.Pointer(cname))
	C.assembly_remove(c.inner.val, cname)
	return c
}

func (c *Assembly) Constrain(q1, q2 string, kind int, param *AssemblyConstraintParm) *Assembly {
	cq1 := C.CString(q1)
	defer C.free(unsafe.Pointer(cq1))
	cq2 := C.CString(q2)
	defer C.free(unsafe.Pointer(cq2))
	C.assembly_constrain(c.inner.val, cq1, cq2, C.int(kind), param.inner.val)
	return c
}

func (c *Assembly) Constrain1(q1 string, kind int, param *AssemblyConstraintParm) *Assembly {
	cq1 := C.CString(q1)
	defer C.free(unsafe.Pointer(cq1))
	C.assembly_constrain1(c.inner.val, cq1, C.int(kind), param.inner.val)
	return c
}

func (c *Assembly) Constrain2(id1 string, s1 *Shape, id2 string, s2 *Shape, kind int, param *AssemblyConstraintParm) *Assembly {
	cid1 := C.CString(id1)
	defer C.free(unsafe.Pointer(cid1))
	cid2 := C.CString(id2)
	defer C.free(unsafe.Pointer(cid2))
	C.assembly_constrain2(c.inner.val, cid1, s1.inner.val, cid2, s2.inner.val, C.int(kind), param.inner.val)
	return c
}

func (c *Assembly) Constrain3(id1 string, s1 *Shape, kind int, param *AssemblyConstraintParm) *Assembly {
	cid1 := C.CString(id1)
	defer C.free(unsafe.Pointer(cid1))
	C.assembly_constrain3(c.inner.val, cid1, s1.inner.val, C.int(kind), param.inner.val)
	return c
}

func (c *Assembly) Solve(verbosity int) *Assembly {
	C.assembly_solve(c.inner.val, C.int(verbosity))
	return c
}

func (c *Assembly) ExportTo(path string, mode int) *Assembly {
	cpath := C.CString(path)
	defer C.free(unsafe.Pointer(cpath))
	C.assembly_export_to(c.inner.val, cpath, C.int(mode))
	return c
}

func (c *Assembly) Shapes() []*Shape {
	var size C.int
	shapes := C.assembly_shapes(c.inner.val, &size)
	defer C.topo_shape_list_free(shapes, size)
	shapesSlice := unsafe.Slice(shapes, int(size))
	var result []*Shape
	for i := 0; i < int(size); i++ {
		shp := &Shape{inner: &innerShape{val: shapesSlice[i]}}
		runtime.SetFinalizer(shp.inner, (*innerShape).free)
		result = append(result, shp)
	}
	return result
}

func (c *Assembly) ToCompound() *Compound {
	cmp := &Compound{inner: &innerCompound{C.assembly_to_compound(c.inner.val)}}
	runtime.SetFinalizer(cmp.inner, (*innerCompound).free)
	return cmp
}

func (c *Assembly) GetElements() []*AssemblyElament {
	var size C.int
	elements := C.assembly_get_elements(c.inner.val, &size)
	defer C.assembly_element_list_free(elements, size)
	elementsSlice := unsafe.Slice(elements, int(size))
	var result []*AssemblyElament
	for i := 0; i < int(size); i++ {
		ele := &AssemblyElament{inner: &innerAssemblyElament{val: elementsSlice[i]}}
		runtime.SetFinalizer(ele.inner, (*innerAssemblyElament).free)
		result = append(result, ele)
	}
	return result
}

func (c *Assembly) GetName() string {
	return C.GoString(C.assembly_get_name(c.inner.val))
}

func (c *Assembly) GetLocation() *TopoLocation {
	p := &TopoLocation{inner: &innerTopoLocation{val: C.assembly_get_location(c.inner.val)}}
	runtime.SetFinalizer(p.inner, (*innerTopoLocation).free)
	return p
}

func (c *Assembly) GetColor() *Color {
	return &Color{C.assembly_get_color(c.inner.val)}
}

func (c *Assembly) GetObject() *AssemblyObject {
	obj := &AssemblyObject{inner: &innerAssemblyObject{C.assembly_get_object(c.inner.val)}}
	runtime.SetFinalizer(obj.inner, (*innerAssemblyObject).free)
	return obj
}

func (c *Assembly) Children() []*Assembly {
	var size C.int
	children := C.assembly_children(c.inner.val, &size)
	defer C.assembly_list_free(children, size)
	childrenSlice := unsafe.Slice(children, int(size))
	var result []*Assembly
	for i := 0; i < int(size); i++ {
		child := &Assembly{inner: &innerAssembly{val: childrenSlice[i]}}
		runtime.SetFinalizer(child.inner, (*innerAssembly).free)
		result = append(result, child)
	}
	return result
}

func (c *Assembly) HasError() bool {
	return bool(C.assembly_has_error(c.inner.val))
}

func (c *Assembly) Error() string {
	return C.GoString(C.assembly_error(c.inner.val))
}
