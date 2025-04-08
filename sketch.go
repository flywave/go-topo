package topo

/*
#include <stdlib.h>
#include "sketch_c_api.h"
#cgo CFLAGS: -I  ./libs
#cgo linux CXXFLAGS: -I ./libs  -std=gnu++14
#cgo darwin,amd64 CXXFLAGS: -I ./libs  -std=gnu++14
#cgo darwin,arm64 CXXFLAGS: -I ./libs  -std=gnu++14
#cgo windows CXXFLAGS: -I ./libs  -std=gnu++14
topo_face_t eachForFaceFunc(void *userdata, topo_location_t *loc);
topo_face_t eachForFaceFunc(void *userdata, topo_location_t *loc);
topo_face_t eachForSketchFunc(void *userdata, topo_location_t *loc);
topo_face_t eachForCompoundFunc(void *userdata, topo_location_t *loc);
bool sketchFilterFunc(void *userdata, sketch_val_t *val);
sketch_val_t* sketchMapFunc(void *userdata, sketch_val_t *val);
sketch_val_t** sketchApplyFunc(void *userdata, sketch_val_t **vals, int num);
bool sketchSortFunc(void *userdata, sketch_val_t *val1, sketch_val_t *val2);
*/
import "C"
import (
	"runtime"
	"unsafe"
)

type SketchObject struct {
	inner *innerSketchObject
}

type innerSketchObject struct {
	val *C.struct__sketch_val_t
}

func (c *innerSketchObject) free() {
	C.sketch_val_free(c.val)
}

func NewSketchObjectFromShpe(shp Shape) *SketchObject {
	c := &SketchObject{inner: &innerSketchObject{val: C.sketch_val_create_from_shape(shp.inner.val)}}
	runtime.SetFinalizer(c.inner, (*innerSketchObject).free)
	return c
}

func NewSketchObjectFromLocation(loc *TopoLocation) *SketchObject {
	c := &SketchObject{inner: &innerSketchObject{val: C.sketch_val_create_from_location(loc.inner.val)}}
	runtime.SetFinalizer(c.inner, (*innerSketchObject).free)
	return c
}

func (c *SketchObject) IsShape() bool {
	return bool(C.sketch_val_is_shape(c.inner.val))
}

func (c *SketchObject) IsLocation() bool {
	return bool(C.sketch_val_is_location(c.inner.val))
}

func (c *SketchObject) GetShape() *Shape {
	shp := &Shape{inner: &innerShape{C.sketch_val_get_shape(c.inner.val)}}
	runtime.SetFinalizer(c.inner, (*innerShape).free)
	return shp
}

func (c *SketchObject) GetLocation() *TopoLocation {
	return &TopoLocation{inner: &innerTopoLocation{C.sketch_val_get_location(c.inner.val)}}
}

type SketchConstraintValue struct {
	inner *innerSketchConstraintValue
}

type innerSketchConstraintValue struct {
	val *C.struct__sketch_constraint_value_t
}

func NewSketchConstraintValueFromBlank() *SketchConstraintValue {
	c := &SketchConstraintValue{inner: &innerSketchConstraintValue{val: C.sketch_constraint_value_create_blank()}}
	runtime.SetFinalizer(c.inner, (*innerSketchConstraintValue).free)
	return c
}

func NewSketchConstraintValueFromDouble(val float64) *SketchConstraintValue {
	c := &SketchConstraintValue{inner: &innerSketchConstraintValue{val: C.sketch_constraint_value_create_double(C.double(val))}}
	runtime.SetFinalizer(c.inner, (*innerSketchConstraintValue).free)
	return c
}

func NewSketchConstraintValueFromDouble3(val1, val2, val3 float64) *SketchConstraintValue {
	c := &SketchConstraintValue{inner: &innerSketchConstraintValue{val: C.sketch_constraint_value_create_double3(C.double(val1), C.double(val2), C.double(val3))}}
	runtime.SetFinalizer(c.inner, (*innerSketchConstraintValue).free)
	return c
}

func NewSketchConstraintValueFromDouble2(val1, val2 float64) *SketchConstraintValue {
	c := &SketchConstraintValue{inner: &innerSketchConstraintValue{val: C.sketch_constraint_value_create_double2(C.double(val1), C.double(val2))}}
	runtime.SetFinalizer(c.inner, (*innerSketchConstraintValue).free)
	return c
}

func (i *innerSketchConstraintValue) free() {
	C.sketch_constraint_value_free(i.val)
}

type Sketch struct {
	inner *innerSketch
}

type innerSketch struct {
	val *C.struct__sketch_t
}

func (c *innerSketch) free() {
	C.sketch_free(c.val)
}

func NewSketchFromWorkplane(inPlane *Workplane, location *TopoLocation, comp *Compound) *Sketch {
	var cloc *C.struct__topo_location_t
	if location != nil {
		cloc = location.inner.val
	}
	var ccomp *C.struct__topo_compound_t
	if comp != nil {
		ccomp = &comp.inner.val
	}
	c := &Sketch{inner: &innerSketch{val: C.sketch_create_from_workplane(inPlane.inner.val, cloc, ccomp)}}
	runtime.SetFinalizer(c.inner, (*innerSketch).free)
	return c
}

func NewSketchFromLocation(location *TopoLocation, comp *Compound) *Sketch {
	var cloc *C.struct__topo_location_t
	if location != nil {
		cloc = location.inner.val
	}
	var ccomp *C.struct__topo_compound_t
	if comp != nil {
		ccomp = &comp.inner.val
	}
	c := &Sketch{inner: &innerSketch{val: C.sketch_create_from_location(cloc, ccomp)}}
	runtime.SetFinalizer(c.inner, (*innerSketch).free)
	return c
}

func (c *Sketch) GetFaces() []*Face {
	var size C.int
	cs := C.sketch_get_faces(c.inner.val, &size)
	csSlice := unsafe.Slice(cs, size)
	fs := make([]*Face, size)
	for i := 0; i < int(size); i++ {
		f := &Face{inner: &innerFace{val: csSlice[i]}}
		runtime.SetFinalizer(f.inner, (*innerFace).free)
		fs[i] = f
	}
	return fs
}

func (c *Sketch) FaceFromWire(wire *Wire, angle float64, tag string) *Sketch {
	cstr := C.CString(tag)
	defer C.free(unsafe.Pointer(cstr))
	var cwire *C.struct__topo_wire_t
	if wire != nil {
		cwire = &wire.inner.val
	}
	C.sketch_face_from_wire(c.inner.val, cwire, C.double(angle), cstr)
	return c
}

func (c *Sketch) FaceFromEdges(edges []*Edge, angle float64, tag string) *Sketch {
	cstr := C.CString(tag)
	defer C.free(unsafe.Pointer(cstr))
	ces := make([]*C.struct__topo_edge_t, len(edges))
	for i := 0; i < len(edges); i++ {
		ces[i] = &edges[i].inner.val
	}
	C.sketch_face_from_edges(c.inner.val, &ces[0], C.int(len(edges)), C.double(angle), cstr)
	return c
}

func (c *Sketch) FaceFromShape(shape *Shape, angle float64, tag string) *Sketch {
	cstr := C.CString(tag)
	defer C.free(unsafe.Pointer(cstr))
	C.sketch_face_from_shape(c.inner.val, shape.inner.val, C.double(angle), cstr)
	return c
}

func (c *Sketch) FaceFromSketch(other *Sketch, angle float64, tag string) *Sketch {
	cstr := C.CString(tag)
	defer C.free(unsafe.Pointer(cstr))
	C.sketch_face_from_sketch(c.inner.val, other.inner.val, C.double(angle), cstr)
	return c
}

func (c *Sketch) Rect(w, h, angle float64, tag string) *Sketch {
	cstr := C.CString(tag)
	defer C.free(unsafe.Pointer(cstr))
	C.sketch_rect(c.inner.val, C.double(w), C.double(h), C.double(angle), cstr)
	return c
}

func (c *Sketch) Circle(r float64, tag string) *Sketch {
	cstr := C.CString(tag)
	defer C.free(unsafe.Pointer(cstr))
	C.sketch_circle(c.inner.val, C.double(r), cstr)
	return c
}

func (c *Sketch) Ellipse(a1, a2, angle float64, tag string) *Sketch {
	cstr := C.CString(tag)
	defer C.free(unsafe.Pointer(cstr))
	C.sketch_ellipse(c.inner.val, C.double(a1), C.double(a2), C.double(angle), cstr)
	return c
}

func (c *Sketch) Trapezoid(w, h, a1, a2, angle float64, tag string) *Sketch {
	cstr := C.CString(tag)
	defer C.free(unsafe.Pointer(cstr))
	C.sketch_trapezoid(c.inner.val, C.double(w), C.double(h), C.double(a1), C.double(a2), C.double(angle), cstr)
	return c
}

func (c *Sketch) Slot(w, h, angle float64, tag string) *Sketch {
	cstr := C.CString(tag)
	defer C.free(unsafe.Pointer(cstr))
	C.sketch_slot(c.inner.val, C.double(w), C.double(h), C.double(angle), cstr)
	return c
}

func (c *Sketch) RegularPolygon(r float64, n int, angle float64, tag string) *Sketch {
	cstr := C.CString(tag)
	defer C.free(unsafe.Pointer(cstr))
	C.sketch_regular_polygon(c.inner.val, C.double(r), C.int(n), C.double(angle), cstr)
	return c
}

func (c *Sketch) Polygon(pts []*TopoVector, angle float64, tag string) *Sketch {
	cstr := C.CString(tag)
	defer C.free(unsafe.Pointer(cstr))
	cpts := make([]*C.struct__topo_vector_t, len(pts))
	for i := 0; i < len(pts); i++ {
		cpts[i] = pts[i].inner.val
	}
	C.sketch_polygon(c.inner.val, &cpts[0], C.int(len(pts)), C.double(angle), cstr)
	return c
}

func (c *Sketch) RArray(xs, ys float64, nx, ny int, angle float64, tag string) *Sketch {
	cstr := C.CString(tag)
	defer C.free(unsafe.Pointer(cstr))
	C.sketch_rarray(c.inner.val, C.double(xs), C.double(ys), C.int(nx), C.int(ny), C.double(angle), cstr)
	return c
}

func (c *Sketch) PArray(r, a1, da float64, n int, rotate bool, angle float64, tag string) *Sketch {
	cstr := C.CString(tag)
	defer C.free(unsafe.Pointer(cstr))
	C.sketch_parray(c.inner.val, C.double(r), C.double(a1), C.double(da), C.int(n), C.bool(rotate), C.double(angle), cstr)
	return c
}

func (c *Sketch) Distribute(n int, start, stop float64, rotate bool, angle float64, tag string) *Sketch {
	cstr := C.CString(tag)
	defer C.free(unsafe.Pointer(cstr))
	C.sketch_distribute(c.inner.val, C.int(n), C.double(start), C.double(stop), C.bool(rotate), C.double(angle), cstr)
	return c
}

func (c *Sketch) Push(locs []*TopoLocation, tag string) *Sketch {
	cstr := C.CString(tag)
	defer C.free(unsafe.Pointer(cstr))
	clocs := make([]*C.struct__topo_location_t, len(locs))
	for i := 0; i < len(locs); i++ {
		clocs[i] = locs[i].inner.val
	}
	C.sketch_push(c.inner.val, &clocs[0], C.int(len(clocs)), cstr)
	return c
}

func (c *Sketch) Hull(mode int, tag string) *Sketch {
	cstr := C.CString(tag)
	defer C.free(unsafe.Pointer(cstr))
	C.sketch_hull(c.inner.val, C.int(mode), cstr)
	return c
}

func (c *Sketch) Offset(d float64, mode int, tag string) *Sketch {
	cstr := C.CString(tag)
	defer C.free(unsafe.Pointer(cstr))
	C.sketch_offset(c.inner.val, C.double(d), C.int(mode), cstr)
	return c
}

func (c *Sketch) Fillet(d float64) *Sketch {
	C.sketch_fillet(c.inner.val, C.double(d))
	return c
}

func (c *Sketch) Chamfer(d float64) *Sketch {
	C.sketch_chamfer(c.inner.val, C.double(d))
	return c
}

func (c *Sketch) Clean() *Sketch {
	C.sketch_clean(c.inner.val)
	return c
}

func (c *Sketch) Tag(tag string) *Sketch {
	cstr := C.CString(tag)
	defer C.free(unsafe.Pointer(cstr))
	C.sketch_tag(c.inner.val, cstr)
	return c
}

func (c *Sketch) Select(tags []string) *Sketch {
	cstrs := make([]*C.char, len(tags))
	for i := 0; i < len(tags); i++ {
		cstrs[i] = C.CString(tags[i])
		defer C.free(unsafe.Pointer(cstrs[i]))
	}
	C.sketch_select(c.inner.val, &cstrs[0], C.int(len(cstrs)))
	return c
}

func (c *Sketch) Faces(selector string, tag string) *Sketch {
	cstr := C.CString(tag)
	defer C.free(unsafe.Pointer(cstr))
	cstr2 := C.CString(selector)
	defer C.free(unsafe.Pointer(cstr2))
	C.sketch_faces(c.inner.val, cstr2, cstr)
	return c
}

func (c *Sketch) FacesForSelector(selector *Selector, tag string) *Sketch {
	cstr := C.CString(tag)
	defer C.free(unsafe.Pointer(cstr))
	C.sketch_faces_for_selector(c.inner.val, selector.inner.val, cstr)
	return c
}

func (c *Sketch) Wires(selector string, tag string) *Sketch {
	cstr := C.CString(tag)
	defer C.free(unsafe.Pointer(cstr))
	cstr2 := C.CString(selector)
	defer C.free(unsafe.Pointer(cstr2))
	C.sketch_wires(c.inner.val, cstr2, cstr)
	return c
}

func (c *Sketch) WiresForSelector(selector *Selector, tag string) *Sketch {
	cstr := C.CString(tag)
	defer C.free(unsafe.Pointer(cstr))
	C.sketch_wires_for_selector(c.inner.val, selector.inner.val, cstr)
	return c
}

func (c *Sketch) Edges(selector string, tag string) *Sketch {
	cstr := C.CString(tag)
	defer C.free(unsafe.Pointer(cstr))
	cstr2 := C.CString(selector)
	defer C.free(unsafe.Pointer(cstr2))
	C.sketch_edges(c.inner.val, cstr2, cstr)
	return c
}

func (c *Sketch) EdgesForSelector(selector *Selector, tag string) *Sketch {
	cstr := C.CString(tag)
	defer C.free(unsafe.Pointer(cstr))
	C.sketch_edges_for_selector(c.inner.val, selector.inner.val, cstr)
	return c
}

func (c *Sketch) Vertices(selector string, tag string) *Sketch {
	cstr := C.CString(tag)
	defer C.free(unsafe.Pointer(cstr))
	cstr2 := C.CString(selector)
	defer C.free(unsafe.Pointer(cstr2))
	C.sketch_vertices(c.inner.val, cstr2, cstr)
	return c
}

func (c *Sketch) VerticesForSelector(selector *Selector, tag string) *Sketch {
	cstr := C.CString(tag)
	defer C.free(unsafe.Pointer(cstr))
	C.sketch_vertices_for_selector(c.inner.val, selector.inner.val, cstr)
	return c
}

func (c *Sketch) Reset() *Sketch {
	C.sketch_reset(c.inner.val)
	return c
}

func (c *Sketch) DeleteSelected() *Sketch {
	C.sketch_delete_selected(c.inner.val)
	return c
}

func (c *Sketch) Edge(edge *Edge, tag string, forConstruction bool) *Sketch {
	cstr := C.CString(tag)
	defer C.free(unsafe.Pointer(cstr))
	C.sketch_edge(c.inner.val, &edge.inner.val, cstr, C.bool(forConstruction))
	return c
}

func (c *Sketch) Segment(p1, p2 *TopoVector, tag string, forConstruction bool) *Sketch {
	cstr := C.CString(tag)
	defer C.free(unsafe.Pointer(cstr))
	C.sketch_segment(c.inner.val, p1.inner.val, p2.inner.val, cstr, C.bool(forConstruction))
	return c
}

func (c *Sketch) Segment2(p2 *TopoVector, tag string, forConstruction bool) *Sketch {
	cstr := C.CString(tag)
	defer C.free(unsafe.Pointer(cstr))
	C.sketch_segment2(c.inner.val, p2.inner.val, cstr, C.bool(forConstruction))
	return c
}

func (c *Sketch) Segment3(l, a float64, tag string, forConstruction bool) *Sketch {
	cstr := C.CString(tag)
	defer C.free(unsafe.Pointer(cstr))
	C.sketch_segment3(c.inner.val, C.double(l), C.double(a), cstr, C.bool(forConstruction))
	return c
}

func (c *Sketch) Arc(p1, p2, p3 *TopoVector, tag string, forConstruction bool) *Sketch {
	cstr := C.CString(tag)
	defer C.free(unsafe.Pointer(cstr))
	C.sketch_arc(c.inner.val, p1.inner.val, p2.inner.val, p3.inner.val, cstr, C.bool(forConstruction))
	return c
}

func (c *Sketch) Arc2(p2, p3 *TopoVector, tag string, forConstruction bool) *Sketch {
	cstr := C.CString(tag)
	defer C.free(unsafe.Pointer(cstr))
	C.sketch_arc2(c.inner.val, p2.inner.val, p3.inner.val, cstr, C.bool(forConstruction))
	return c
}

func (c *Sketch) Arc3(center *TopoVector, radius, startAngle, deltaAngle float64, tag string, forConstruction bool) *Sketch {
	cstr := C.CString(tag)
	defer C.free(unsafe.Pointer(cstr))
	C.sketch_arc3(c.inner.val, center.inner.val, C.double(radius), C.double(startAngle), C.double(deltaAngle), cstr, C.bool(forConstruction))
	return c
}

func (c *Sketch) Spline(points []*TopoVector, tag string, forConstruction bool) *Sketch {
	cstr := C.CString(tag)
	defer C.free(unsafe.Pointer(cstr))
	cpoints := make([]*C.struct__topo_vector_t, len(points))
	for i := 0; i < len(points); i++ {
		cpoints[i] = points[i].inner.val
	}
	C.sketch_spline(c.inner.val, &cpoints[0], C.int(len(points)), cstr, C.bool(forConstruction))
	return c
}

func (c *Sketch) Spline2(points []*TopoVector, tangents1, tangents2 *TopoVector, periodic bool, tag string, forConstruction bool) *Sketch {
	cstr := C.CString(tag)
	defer C.free(unsafe.Pointer(cstr))
	cpoints := make([]*C.struct__topo_vector_t, len(points))
	for i := 0; i < len(points); i++ {
		cpoints[i] = points[i].inner.val
	}
	var ctangents1 *C.struct__topo_vector_t
	var ctangents2 *C.struct__topo_vector_t
	if tangents1 != nil {
		ctangents1 = tangents1.inner.val
	}
	if tangents2 != nil {
		ctangents2 = tangents2.inner.val
	}
	C.sketch_spline2(c.inner.val, &cpoints[0], C.int(len(points)), ctangents1, ctangents2, C.bool(periodic), cstr, C.bool(forConstruction))
	return c
}

func (c *Sketch) Bezier(points []*TopoVector, tag string, forConstruction bool) *Sketch {
	cstr := C.CString(tag)
	defer C.free(unsafe.Pointer(cstr))
	cpoints := make([]*C.struct__topo_vector_t, len(points))
	for i := 0; i < len(points); i++ {
		cpoints[i] = points[i].inner.val
	}
	C.sketch_bezier(c.inner.val, &cpoints[0], C.int(len(points)), cstr, C.bool(forConstruction))
	return c
}

func (c *Sketch) Close(tag string) *Sketch {
	cstr := C.CString(tag)
	defer C.free(unsafe.Pointer(cstr))
	C.sketch_close(c.inner.val, cstr)
	return c
}

func (c *Sketch) Assemble(mode int, tag string) *Sketch {
	cstr := C.CString(tag)
	defer C.free(unsafe.Pointer(cstr))
	C.sketch_assemble(c.inner.val, C.int(mode), cstr)
	return c
}

func (c *Sketch) Constrain(tag string, constraint int, arg *SketchConstraintValue) *Sketch {
	cstr := C.CString(tag)
	defer C.free(unsafe.Pointer(cstr))
	C.sketch_constrain(c.inner.val, cstr, C.int(constraint), arg.inner.val)
	return c
}

func (c *Sketch) Constrain2(tag1, tag2 string, constraint int, arg *SketchConstraintValue) *Sketch {
	cstr := C.CString(tag1)
	defer C.free(unsafe.Pointer(cstr))
	cstr2 := C.CString(tag2)
	defer C.free(unsafe.Pointer(cstr2))
	C.sketch_constrain2(c.inner.val, cstr, cstr2, C.int(constraint), arg.inner.val)
	return c
}

func (c *Sketch) Solve() *Sketch {
	C.sketch_solve(c.inner.val)
	return c
}

func (c *Sketch) Copy() *Sketch {
	c2 := &Sketch{inner: &innerSketch{val: C.sketch_copy(c.inner.val)}}
	runtime.SetFinalizer(c2.inner, (*innerSketch).free)
	return c2
}

func (c *Sketch) Moved(locs []*TopoLocation) *Sketch {
	clocs := make([]*C.struct__topo_location_t, len(locs))
	for i := 0; i < len(locs); i++ {
		clocs[i] = locs[i].inner.val
	}
	c2 := &Sketch{inner: &innerSketch{val: C.sketch_moved(c.inner.val, &clocs[0], C.int(len(clocs)))}}
	runtime.SetFinalizer(c2.inner, (*innerSketch).free)
	return c2
}

func (c *Sketch) Located(loc *TopoLocation) *Sketch {
	c2 := &Sketch{inner: &innerSketch{val: C.sketch_located(c.inner.val, loc.inner.val)}}
	runtime.SetFinalizer(c2.inner, (*innerSketch).free)
	return c2
}

func (c *Sketch) Finalize() *Workplane {
	c2 := &Workplane{inner: &innerWorkplane{val: C.sketch_finalize(c.inner.val)}}
	runtime.SetFinalizer(c2.inner, (*innerWorkplane).free)
	return c2
}

func (c *Sketch) Val() *SketchObject {
	c2 := &SketchObject{inner: &innerSketchObject{val: C.sketch_val(c.inner.val)}}
	runtime.SetFinalizer(c2.inner, (*innerSketchObject).free)
	return c2
}

func (c *Sketch) Vals() []*SketchObject {
	var size C.int
	cs := C.sketch_vals(c.inner.val, &size)
	csSlice := unsafe.Slice(cs, size)
	os := make([]*SketchObject, size)
	for i := 0; i < int(size); i++ {
		o := &SketchObject{inner: &innerSketchObject{val: csSlice[i]}}
		runtime.SetFinalizer(o.inner, (*innerSketchObject).free)
		os[i] = o
	}
	return os
}

func (c *Sketch) Add() *Sketch {
	C.sketch_add(c.inner.val)
	return c
}

func (c *Sketch) Subtract() *Sketch {
	C.sketch_subtract(c.inner.val)
	return c
}

func (c *Sketch) Replace() *Sketch {
	C.sketch_replace(c.inner.val)
	return c
}

// export eachForFaceFunc
func eachForFaceFunc(userData unsafe.Pointer, loc *C.struct__topo_location_t) C.struct__topo_face_t {
	fn := *(*func(*TopoLocation) *Face)(userData)
	lloc := &TopoLocation{inner: &innerTopoLocation{val: loc}}
	runtime.SetFinalizer(lloc.inner, (*innerTopoLocation).free)
	f := fn(lloc)
	return f.inner.val
}

func (c *Sketch) EachForFace(fn func(*TopoLocation) *Face, mode int, tag string, ignoreSelection bool) *Sketch {
	cstr := C.CString(tag)
	defer C.free(unsafe.Pointer(cstr))
	f := func(loc *TopoLocation) *Face {
		return fn(loc)
	}
	C.sketch_each_for_face(c.inner.val, unsafe.Pointer(&f), (*[0]byte)(C.eachForFaceFunc), C.int(mode), cstr, C.bool(ignoreSelection))
	return c
}

// export eachForSketchFunc
func eachForSketchFunc(userData unsafe.Pointer, loc *C.struct__topo_location_t) *C.struct__sketch_t {
	fn := *(*func(*TopoLocation) *Sketch)(userData)
	lloc := &TopoLocation{inner: &innerTopoLocation{val: loc}}
	runtime.SetFinalizer(lloc.inner, (*innerTopoLocation).free)
	s := fn(lloc)
	return s.inner.val
}

func (c *Sketch) EachForSketch(fn func(*TopoLocation) *Sketch, mode int, tag string, ignoreSelection bool) *Sketch {
	cstr := C.CString(tag)
	defer C.free(unsafe.Pointer(cstr))
	f := func(loc *TopoLocation) *Sketch {
		return fn(loc)
	}
	C.sketch_each_for_sketch(c.inner.val, unsafe.Pointer(&f), (*[0]byte)(C.eachForSketchFunc), C.int(mode), cstr, C.bool(ignoreSelection))
	return c
}

// export eachForCompoundFunc
func eachForCompoundFunc(userData unsafe.Pointer, loc *C.struct__topo_location_t) C.struct__topo_compound_t {
	fn := *(*func(*TopoLocation) *Compound)(userData)
	lloc := &TopoLocation{inner: &innerTopoLocation{val: loc}}
	runtime.SetFinalizer(lloc.inner, (*innerTopoLocation).free)
	c := fn(lloc)
	return c.inner.val
}

func (c *Sketch) EachForCompound(fn func(*TopoLocation) *Compound, mode int, tag string, ignoreSelection bool) *Sketch {
	cstr := C.CString(tag)
	defer C.free(unsafe.Pointer(cstr))
	f := func(loc *TopoLocation) *Compound {
		return fn(loc)
	}
	C.sketch_each_for_compound(c.inner.val, unsafe.Pointer(&f), (*[0]byte)(C.eachForCompoundFunc), C.int(mode), cstr, C.bool(ignoreSelection))
	return c
}

// export sketchFilterFunc
func sketchFilterFunc(userData unsafe.Pointer, val *C.struct__sketch_val_t) C.bool {
	fn := *(*func(*SketchObject) bool)(userData)
	obj := &SketchObject{inner: &innerSketchObject{val: val}}
	runtime.SetFinalizer(obj.inner, (*innerSketchObject).free)
	return C.bool(fn(obj))
}

func (c *Sketch) Filter(fn func(*SketchObject) bool) *Sketch {
	f := func(val *SketchObject) bool {
		return fn(val)
	}
	C.sketch_filter(c.inner.val, unsafe.Pointer(&f), (*[0]byte)(C.sketchFilterFunc))
	return c
}

// export sketchMapFunc
func sketchMapFunc(userData unsafe.Pointer, val *C.struct__sketch_val_t) *C.struct__sketch_val_t {
	fn := *(*func(*SketchObject) *SketchObject)(userData)
	obj := &SketchObject{inner: &innerSketchObject{val: val}}
	runtime.SetFinalizer(obj.inner, (*innerSketchObject).free)
	return fn(obj).inner.val
}

func (c *Sketch) Map(fn func(*SketchObject) *SketchObject) *Sketch {
	C.sketch_map(c.inner.val, unsafe.Pointer(&fn), (*[0]byte)(C.sketchMapFunc))
	return c
}

// export sketchApplyFunc
func sketchApplyFunc(userData unsafe.Pointer, vals **C.struct__sketch_val_t, num C.int) **C.struct__sketch_val_t {
	fn := *(*func([]*SketchObject) []*SketchObject)(userData)
	vals_ := make([]*SketchObject, num)
	valsSlice := unsafe.Slice(vals, num)
	for i := 0; i < int(num); i++ {
		val := &SketchObject{inner: &innerSketchObject{val: valsSlice[i]}}
		runtime.SetFinalizer(val.inner, (*innerSketchObject).free)
		vals_[i] = val
	}
	vals_ = fn(vals_)
	valsSlice_ := make([]*C.struct__sketch_val_t, len(vals_))
	for i := 0; i < len(vals_); i++ {
		valsSlice_[i] = vals_[i].inner.val
	}
	return &valsSlice_[0]
}

func (c *Sketch) Apply(fn func([]*SketchObject) []*SketchObject) *Sketch {
	C.sketch_apply(c.inner.val, unsafe.Pointer(&fn), (*[0]byte)(C.sketchApplyFunc))
	return c
}

// export sketchSortFunc
func sketchSortFunc(userData unsafe.Pointer, val1 *C.struct__sketch_val_t, val2 *C.struct__sketch_val_t) C.bool {
	fn := *(*func(*SketchObject, *SketchObject) bool)(userData)
	o1 := &SketchObject{inner: &innerSketchObject{val: val1}}
	runtime.SetFinalizer(o1.inner, (*innerSketchObject).free)
	o2 := &SketchObject{inner: &innerSketchObject{val: val2}}
	runtime.SetFinalizer(o2.inner, (*innerSketchObject).free)
	return C.bool(fn(o1, o2))
}

func (c *Sketch) Sort(fn func(*SketchObject, *SketchObject) bool) *Sketch {
	C.sketch_sort(c.inner.val, unsafe.Pointer(&fn), (*[0]byte)(C.sketchSortFunc))
	return c
}
