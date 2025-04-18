package topo

/*
#include <stdlib.h>
#include "selector_c_api.h"
#cgo CFLAGS: -I  ./libs
#cgo linux CXXFLAGS: -I ./libs  -std=gnu++14
#cgo darwin,amd64 CXXFLAGS: -I ./libs  -std=gnu++14
#cgo darwin,arm64 CXXFLAGS: -I ./libs  -std=gnu++14
#cgo windows CXXFLAGS: -I ./libs  -std=gnu++14
topo_shape_t **customSelectorFunc(void* userdata, topo_shape_t** shapes, int num_shapes, int* num_selected_shapes);
*/
import "C"
import (
	"runtime"
	"unsafe"
)

type Selector struct {
	inner *innerSelector
}

type innerSelector struct {
	val *C.struct__selector_t
}

func (c *innerSelector) free() {
	C.selector_free(c.val)
}

func NewNearestToPointSelector(p *TopoVector) *Selector {
	c := &Selector{inner: &innerSelector{C.selector_nearest_to_point_selector_create(p.inner.val)}}
	runtime.SetFinalizer(c.inner, (*innerSelector).free)
	return c
}

func NewBoxSelector(p0 *TopoVector, p1 *TopoVector, use_bb bool) *Selector {
	c := &Selector{inner: &innerSelector{C.selector_box_selector_create(p0.inner.val, p1.inner.val, C.bool(use_bb))}}
	runtime.SetFinalizer(c.inner, (*innerSelector).free)
	return c
}

func NewRadiusNthSelector(n int, direction_max bool, tolerance float64) *Selector {
	c := &Selector{inner: &innerSelector{C.selector_radius_nth_selector_create(C.int(n), C.bool(direction_max), C.double(tolerance))}}
	runtime.SetFinalizer(c.inner, (*innerSelector).free)
	return c
}

func NewCenterNthSelector(dir *TopoVector, n int, direction_max bool, tolerance float64) *Selector {
	c := &Selector{inner: &innerSelector{C.selector_center_nth_selector_create(dir.inner.val, C.int(n), C.bool(direction_max), C.double(tolerance))}}
	runtime.SetFinalizer(c.inner, (*innerSelector).free)
	return c
}

func NewDirectionMinmaxSelector(dir *TopoVector, direction_max bool, tolerance float64) *Selector {
	c := &Selector{inner: &innerSelector{C.selector_direction_minmax_selector_create(dir.inner.val, C.bool(direction_max), C.double(tolerance))}}
	runtime.SetFinalizer(c.inner, (*innerSelector).free)
	return c
}

func NewParallelDirSelector(dir *TopoVector, tol float64) *Selector {
	c := &Selector{inner: &innerSelector{C.selector_parallel_dir_selector_create(dir.inner.val, C.double(tol))}}
	runtime.SetFinalizer(c.inner, (*innerSelector).free)
	return c
}

func NewDirSelector(dir *TopoVector, tol float64) *Selector {
	c := &Selector{inner: &innerSelector{C.selector_dir_selector_create(dir.inner.val, C.double(tol))}}
	runtime.SetFinalizer(c.inner, (*innerSelector).free)
	return c
}

func NewPerpendicularDirSelector(dir *TopoVector, tol float64) *Selector {
	c := &Selector{inner: &innerSelector{C.selector_perpendicular_dir_selector_create(dir.inner.val, C.double(tol))}}
	runtime.SetFinalizer(c.inner, (*innerSelector).free)
	return c
}

func NewDirectionNthSelector(dir *TopoVector, n int, direction_max bool, tolerance float64) *Selector {
	c := &Selector{inner: &innerSelector{C.selector_direction_nth_selector_create(dir.inner.val, C.int(n), C.bool(direction_max), C.double(tolerance))}}
	runtime.SetFinalizer(c.inner, (*innerSelector).free)
	return c
}

func NewLengthNthSelector(n int, direction_max bool, tolerance float64) *Selector {
	c := &Selector{inner: &innerSelector{C.selector_length_nth_selector_create(C.int(n), C.bool(direction_max), C.double(tolerance))}}
	runtime.SetFinalizer(c.inner, (*innerSelector).free)
	return c
}

func NewTypeSelector(typ int) *Selector {
	c := &Selector{inner: &innerSelector{C.selector_type_selector_create(C.int(typ))}}
	runtime.SetFinalizer(c.inner, (*innerSelector).free)
	return c
}

func NewAreaNthSelector(n int, direction_max bool, tolerance float64) *Selector {
	c := &Selector{inner: &innerSelector{C.selector_area_nth_selector_create(C.int(n), C.bool(direction_max), C.double(tolerance))}}
	runtime.SetFinalizer(c.inner, (*innerSelector).free)
	return c
}

func NewAndSelector(left *Selector, right *Selector) *Selector {
	c := &Selector{inner: &innerSelector{C.selector_and_selector_create(left.inner.val, right.inner.val)}}
	runtime.SetFinalizer(c.inner, (*innerSelector).free)
	return c
}

func NewOrSelector(left *Selector, right *Selector) *Selector {
	c := &Selector{inner: &innerSelector{C.selector_or_selector_create(left.inner.val, right.inner.val)}}
	runtime.SetFinalizer(c.inner, (*innerSelector).free)
	return c
}

func NewSubtractSelector(left *Selector, right *Selector) *Selector {
	c := &Selector{inner: &innerSelector{C.selector_subtract_selector_create(left.inner.val, right.inner.val)}}
	runtime.SetFinalizer(c.inner, (*innerSelector).free)
	return c
}

func NewNotSelector(sel *Selector) *Selector {
	c := &Selector{inner: &innerSelector{C.selector_not_selector_create(sel.inner.val)}}
	runtime.SetFinalizer(c.inner, (*innerSelector).free)
	return c
}

func NewStringSyntaxSelector(selector_str string) *Selector {
	cselector_str := C.CString(selector_str)
	defer C.free(unsafe.Pointer(cselector_str))
	c := &Selector{inner: &innerSelector{C.selector_string_syntax_selector_create(cselector_str)}}
	runtime.SetFinalizer(c.inner, (*innerSelector).free)
	return c
}

//export customSelectorFunc
func customSelectorFunc(user_data unsafe.Pointer, shapes **C.struct__topo_shape_t, num C.int, index *C.int) **C.struct__topo_shape_t {
	shapes_ := make([]*Shape, num)
	shapesSlice := unsafe.Slice(shapes, num)
	for i := 0; i < int(num); i++ {
		shp := &Shape{inner: &innerShape{val: shapesSlice[i]}}
		shapes_[i] = shp
	}
	index_ := int(*index)
	shapes_ = (*(*func([]*Shape) []*Shape)(user_data))(shapes_)
	*index = C.int(index_)
	shapesSlice_ := make([]*C.struct__topo_shape_t, len(shapes_))
	for i := 0; i < len(shapes_); i++ {
		shapesSlice_[i] = shapes_[i].inner.val
	}
	return &shapesSlice_[0]
}

func NewCustomSelector(f func(shapes []*Shape) []*Shape) *Selector {
	c := &Selector{inner: &innerSelector{C.selector_custom_selector_create(unsafe.Pointer(&f), (*[0]byte)(C.customSelectorFunc))}}
	runtime.SetFinalizer(c.inner, (*innerSelector).free)
	return c
}
