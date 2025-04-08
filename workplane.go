package topo

/*
#include <stdlib.h>
#include "workplane_c_api.h"
#cgo CFLAGS: -I  ./libs
#cgo linux CXXFLAGS: -I ./libs  -std=gnu++14
#cgo darwin,amd64 CXXFLAGS: -I ./libs  -std=gnu++14
#cgo darwin,arm64 CXXFLAGS: -I ./libs  -std=gnu++14
#cgo windows CXXFLAGS: -I ./libs  -std=gnu++14

topo_vector_t* parametricCurveFunc(void* userdata, double t);
topo_vector_t* parametricSurfaceFunc(void* userdata, double t, double u);
void eachFunc(void* userdata, struct _shape_object_t* obj);
topo_shape_t* eachFuncWithLocation(void* userdata, topo_location_t* loc);
topo_shape_t* cutEachFunc(void* userdata, topo_location_t* loc);
bool workplaneFilterFunc(void* userdata, struct _shape_object_t* obj);
struct _shape_object_t* workplaneMapFunc(void* userdata, struct _shape_object_t* obj);
struct _shape_object_t** workplaneApplyFunc(void* userdata, struct _shape_object_t** objs, int count);
bool workplaneSortFunc(void* userdata, struct _shape_object_t* obj1, struct _shape_object_t* obj2);
struct _workplane_t* workplaneInvokeFunc(void* userdata);
*/
import "C"
import (
	"runtime"
	"unsafe"
)

type ShapeObjectType int

const (
	ShapeCompound  ShapeObjectType = 0
	ShapeCompSolid ShapeObjectType = 1
	ShapeSolid     ShapeObjectType = 2
	ShapeShell     ShapeObjectType = 3
	ShapeFace      ShapeObjectType = 4
	ShapeWire      ShapeObjectType = 5
	ShapeEdge      ShapeObjectType = 6
	ShapeVertex    ShapeObjectType = 7
	ShapeShape     ShapeObjectType = 8
	ShapeVector    ShapeObjectType = 100
	ShapeLocation  ShapeObjectType = 101
	ShapeSketch    ShapeObjectType = 102
	ShapeBlank     ShapeObjectType = 103
)

type ShapeObject struct {
	inner *innerShapeObject
}

type innerShapeObject struct {
	val *C.struct__shape_object_t
}

func (c *innerShapeObject) free() {
	C.shape_object_free(c.val)
}

func NewShapeObjectFromShape(shape *Shape) *ShapeObject {
	c := &ShapeObject{inner: &innerShapeObject{val: C.shape_object_create_from_shape(shape.inner.val)}}
	runtime.SetFinalizer(c.inner, (*innerShapeObject).free)
	return c
}

func NewShapeObjectFromVector(vector *TopoVector) *ShapeObject {
	c := &ShapeObject{inner: &innerShapeObject{val: C.shape_object_create_from_vector(vector.inner.val)}}
	runtime.SetFinalizer(c.inner, (*innerShapeObject).free)
	return c
}

func NewShapeObjectFromLocation(location *TopoLocation) *ShapeObject {
	c := &ShapeObject{inner: &innerShapeObject{val: C.shape_object_create_from_location(location.inner.val)}}
	runtime.SetFinalizer(c.inner, (*innerShapeObject).free)
	return c
}

func NewShapeObjectFromSketch(sketch *Sketch) *ShapeObject {
	c := &ShapeObject{inner: &innerShapeObject{val: C.shape_object_create_from_sketch(sketch.inner.val)}}
	runtime.SetFinalizer(c.inner, (*innerShapeObject).free)
	return c
}

func NewShapeObject() *ShapeObject {
	c := &ShapeObject{inner: &innerShapeObject{val: C.shape_object_create()}}
	runtime.SetFinalizer(c.inner, (*innerShapeObject).free)
	return c
}

func (c *ShapeObject) Type() ShapeObjectType {
	return ShapeObjectType(C.shape_object_type(c.inner.val))
}

func (c *ShapeObject) GetShape() *Shape {
	if c.Type() == ShapeVector || c.Type() == ShapeLocation || c.Type() == ShapeSketch || c.Type() == ShapeBlank {
		return nil
	}
	shp := &Shape{inner: &innerShape{C.shape_object_get_shape(c.inner.val)}}
	runtime.SetFinalizer(shp.inner, (*innerShape).free)
	return shp
}

func (c *ShapeObject) GetCompound() *Compound {
	if c.Type() != ShapeCompound {
		return nil
	}
	shp := c.GetShape()
	var val C.struct__topo_compound_t
	val.shp = C.topo_shape_share(shp.inner.val)
	p := &Compound{inner: &innerCompound{val: val}}
	runtime.SetFinalizer(p.inner, (*innerCompound).free)
	return p
}

func (c *ShapeObject) GetCompSolid() *CompSolid {
	if c.Type() != ShapeCompSolid {
		return nil
	}
	shp := c.GetShape()
	var val C.struct__topo_comp_solid_t
	val.shp = C.topo_shape_share(shp.inner.val)
	p := &CompSolid{inner: &innerCompSolid{val: val}}
	runtime.SetFinalizer(p.inner, (*innerCompSolid).free)
	return p
}

func (c *ShapeObject) GetSolid() *Solid {
	if c.Type() != ShapeSolid {
		return nil
	}
	shp := c.GetShape()
	var val C.struct__topo_solid_t
	val.shp = C.topo_shape_share(shp.inner.val)
	p := &Solid{inner: &innerSolid{val: val}}
	runtime.SetFinalizer(p.inner, (*innerSolid).free)
	return p
}

func (c *ShapeObject) GetShell() *Shell {
	if c.Type() != ShapeShell {
		return nil
	}
	shp := c.GetShape()
	var val C.struct__topo_shell_t
	val.shp = C.topo_shape_share(shp.inner.val)
	p := &Shell{inner: &innerShell{val: val}}
	runtime.SetFinalizer(p.inner, (*innerShell).free)
	return p
}

func (c *ShapeObject) GetFace() *Face {
	if c.Type() != ShapeFace {
		return nil
	}
	shp := c.GetShape()
	var val C.struct__topo_face_t
	val.shp = C.topo_shape_share(shp.inner.val)
	p := &Face{inner: &innerFace{val: val}}
	runtime.SetFinalizer(p.inner, (*innerFace).free)
	return p
}

func (c *ShapeObject) GetWire() *Wire {
	if c.Type() != ShapeWire {
		return nil
	}
	shp := c.GetShape()
	var val C.struct__topo_wire_t
	val.shp = C.topo_shape_share(shp.inner.val)
	p := &Wire{inner: &innerWire{val: val}}
	runtime.SetFinalizer(p.inner, (*innerWire).free)
	return p
}

func (c *ShapeObject) GetEdge() *Edge {
	if c.Type() != ShapeEdge {
		return nil
	}
	shp := c.GetShape()
	var val C.struct__topo_edge_t
	val.shp = C.topo_shape_share(shp.inner.val)
	p := &Edge{inner: &innerEdge{val: val}}
	runtime.SetFinalizer(p.inner, (*innerEdge).free)
	return p
}

func (c *ShapeObject) GetVertex() *Vertex {
	if c.Type() != ShapeVertex {
		return nil
	}
	shp := c.GetShape()
	var val C.struct__topo_vertex_t
	val.shp = C.topo_shape_share(shp.inner.val)
	p := &Vertex{inner: &innerVertex{val: val}}
	runtime.SetFinalizer(p.inner, (*innerVertex).free)
	return p
}

func (c *ShapeObject) GetVector() *TopoVector {
	if c.Type() != ShapeVector {
		return nil
	}
	shp := &TopoVector{inner: &innerVector{C.shape_object_get_vector(c.inner.val)}}
	runtime.SetFinalizer(shp.inner, (*innerVector).free)
	return shp
}

func (c *ShapeObject) GetLocation() *TopoLocation {
	if c.Type() != ShapeLocation {
		return nil
	}
	shp := &TopoLocation{inner: &innerTopoLocation{C.shape_object_get_location(c.inner.val)}}
	runtime.SetFinalizer(shp.inner, (*innerTopoLocation).free)
	return shp
}

func (c *ShapeObject) GetSketch() *Sketch {
	if c.Type() != ShapeSketch {
		return nil
	}
	shp := &Sketch{inner: &innerSketch{C.shape_object_get_sketch(c.inner.val)}}
	runtime.SetFinalizer(shp.inner, (*innerSketch).free)
	return shp
}

type Workplane struct {
	inner *innerWorkplane
}

type innerWorkplane struct {
	val *C.struct__workplane_t
}

func NewWorkplane() *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_create()}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

func NewWorkplaneFromPlane(plane *TopoPlane, origin *TopoVector) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_create_from_plane(plane.inner.val, origin.inner.val)}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

func NewWorkplaneFromName(name string, origin *TopoVector) *Workplane {
	cname := C.CString(name)
	defer C.free(unsafe.Pointer(cname))
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_create_from_name(cname, origin.inner.val)}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

func (c *innerWorkplane) free() {
	C.workplane_free(c.val)
}

func (c *Workplane) Value() *Shape {
	shp := &Shape{inner: &innerShape{C.workplane_value(c.inner.val)}}
	runtime.SetFinalizer(shp.inner, (*innerShape).free)
	return shp
}

func (c *Workplane) Clean() *Workplane {
	wp := &Workplane{inner: &innerWorkplane{val: C.workplane_clean(c.inner.val)}}
	runtime.SetFinalizer(wp.inner, (*innerWorkplane).free)
	return wp
}

func (c *Workplane) Workplane(offset float64, invert bool, centerOption int, origin *TopoVector) *Workplane {
	wp := &Workplane{inner: &innerWorkplane{val: C.workplane_workplane(c.inner.val, C.double(offset), C.bool(invert), C.int(centerOption), origin.inner.val)}}
	runtime.SetFinalizer(wp.inner, (*innerWorkplane).free)
	return wp
}

func (c *Workplane) Tag(name string) *Workplane {
	cname := C.CString(name)
	defer C.free(unsafe.Pointer(cname))
	C.workplane_tag(c.inner.val, cname)
	return c
}

func (c *Workplane) Split(keepTop bool, keepBottom bool) *Workplane {
	wp := &Workplane{inner: &innerWorkplane{val: C.workplane_split(c.inner.val, C.bool(keepTop), C.bool(keepBottom))}}
	runtime.SetFinalizer(wp.inner, (*innerWorkplane).free)
	return wp
}

func (c *Workplane) SplitWithShape(splitter *Shape) *Workplane {
	wp := &Workplane{inner: &innerWorkplane{val: C.workplane_split_with_shape(c.inner.val, splitter.inner.val)}}
	runtime.SetFinalizer(wp.inner, (*innerWorkplane).free)
	return wp
}

func (c *Workplane) SplitWithWorkplane(splitter *Workplane) *Workplane {
	wp := &Workplane{inner: &innerWorkplane{val: C.workplane_split_with_workplane(c.inner.val, splitter.inner.val)}}
	runtime.SetFinalizer(wp.inner, (*innerWorkplane).free)
	return wp
}

func (c *Workplane) Add(other *Workplane) *Workplane {
	C.workplane_add(c.inner.val, other.inner.val)
	return c
}

func (c *Workplane) AddShape(obj *ShapeObject) *Workplane {
	C.workplane_add_shape(c.inner.val, obj.inner.val)
	return c
}

func (c *Workplane) AddShapes(objs []*ShapeObject) *Workplane {
	objsPtr := make([]*C.struct__shape_object_t, len(objs))
	for i, obj := range objs {
		objsPtr[i] = obj.inner.val
	}
	C.workplane_add_shapes(c.inner.val, &objsPtr[0], C.int(len(objs)))
	return c
}

func (c *Workplane) FindSolid(searchStack bool, searchParents bool) *Solid {
	shp := &Solid{inner: &innerSolid{C.workplane_find_solid(c.inner.val, C.bool(searchStack), C.bool(searchParents))}}
	runtime.SetFinalizer(shp.inner, (*innerSolid).free)
	return shp
}

func (wp *Workplane) Vertices(selector string, tag string) *Workplane {
	cselector := C.CString(selector)
	defer C.free(unsafe.Pointer(cselector))
	ctag := C.CString(tag)
	defer C.free(unsafe.Pointer(ctag))
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_vertices(wp.inner.val, cselector, ctag)}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) VerticesWithSelector(selector *Selector, tag string) *Workplane {
	ctag := C.CString(tag)
	defer C.free(unsafe.Pointer(ctag))
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_vertices_with_selector(wp.inner.val, selector.inner.val, ctag)}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) Edges(selector string, tag string) *Workplane {
	cselector := C.CString(selector)
	defer C.free(unsafe.Pointer(cselector))
	ctag := C.CString(tag)
	defer C.free(unsafe.Pointer(ctag))
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_edges(wp.inner.val, cselector, ctag)}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) EdgesWithSelector(selector *Selector, tag string) *Workplane {
	ctag := C.CString(tag)
	defer C.free(unsafe.Pointer(ctag))
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_edges_with_selector(wp.inner.val, selector.inner.val, ctag)}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) Wires(selector string, tag string) *Workplane {
	cselector := C.CString(selector)
	defer C.free(unsafe.Pointer(cselector))
	ctag := C.CString(tag)
	defer C.free(unsafe.Pointer(ctag))
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_wires(wp.inner.val, cselector, ctag)}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) WiresWithSelector(selector *Selector, tag string) *Workplane {
	ctag := C.CString(tag)
	defer C.free(unsafe.Pointer(ctag))
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_wires_with_selector(wp.inner.val, selector.inner.val, ctag)}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) Faces(selector string, tag string) *Workplane {
	cselector := C.CString(selector)
	defer C.free(unsafe.Pointer(cselector))
	ctag := C.CString(tag)
	defer C.free(unsafe.Pointer(ctag))
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_faces(wp.inner.val, cselector, ctag)}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) FacesWithSelector(selector *Selector, tag string) *Workplane {
	ctag := C.CString(tag)
	defer C.free(unsafe.Pointer(ctag))
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_faces_with_selector(wp.inner.val, selector.inner.val, ctag)}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) Shells(selector string, tag string) *Workplane {
	cselector := C.CString(selector)
	defer C.free(unsafe.Pointer(cselector))
	ctag := C.CString(tag)
	defer C.free(unsafe.Pointer(ctag))
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_shells(wp.inner.val, cselector, ctag)}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) ShellsWithSelector(selector *Selector, tag string) *Workplane {
	ctag := C.CString(tag)
	defer C.free(unsafe.Pointer(ctag))
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_shells_with_selector(wp.inner.val, selector.inner.val, ctag)}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) Solids(selector string, tag string) *Workplane {
	cselector := C.CString(selector)
	defer C.free(unsafe.Pointer(cselector))
	ctag := C.CString(tag)
	defer C.free(unsafe.Pointer(ctag))
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_solids(wp.inner.val, cselector, ctag)}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) SolidsWithSelector(selector *Selector, tag string) *Workplane {
	ctag := C.CString(tag)
	defer C.free(unsafe.Pointer(ctag))
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_solids_with_selector(wp.inner.val, selector.inner.val, ctag)}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) Compounds(selector string, tag string) *Workplane {
	cselector := C.CString(selector)
	defer C.free(unsafe.Pointer(cselector))
	ctag := C.CString(tag)
	defer C.free(unsafe.Pointer(ctag))
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_compounds(wp.inner.val, cselector, ctag)}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}
func (wp *Workplane) CompoundsWithSelector(selector *Selector, tag string) *Workplane {
	ctag := C.CString(tag)
	defer C.free(unsafe.Pointer(ctag))
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_compounds_with_selector(wp.inner.val, selector.inner.val, ctag)}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) Ancestors(kind int, tag string) *Workplane {
	ctag := C.CString(tag)
	defer C.free(unsafe.Pointer(ctag))
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_ancestors(wp.inner.val, C.int(kind), ctag)}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) Siblings(kind int, level int, tag string) *Workplane {
	ctag := C.CString(tag)
	defer C.free(unsafe.Pointer(ctag))
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_siblings(wp.inner.val, C.int(kind), C.int(level), ctag)}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) RotateAboutCenter(axisEndPoint *TopoVector, angle float64) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_rotate_about_center(wp.inner.val, axisEndPoint.inner.val, C.double(angle))}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) Rotate(axisStart *TopoVector, axisEnd *TopoVector, angle float64) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_rotate(wp.inner.val, axisStart.inner.val, axisEnd.inner.val, C.double(angle))}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) Mirror(planeName string, basePoint *TopoVector) *Workplane {
	cplaneName := C.CString(planeName)
	defer C.free(unsafe.Pointer(cplaneName))
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_mirror(wp.inner.val, cplaneName, basePoint.inner.val)}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) MirrorWithNormal(normal *TopoVector, basePoint *TopoVector) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_mirror_with_normal(wp.inner.val, normal.inner.val, basePoint.inner.val)}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) MirrorWithName(planeName string, basePoint *TopoVector, unionResult bool) *Workplane {
	cplaneName := C.CString(planeName)
	defer C.free(unsafe.Pointer(cplaneName))
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_mirror_with_name(wp.inner.val, cplaneName, basePoint.inner.val, C.bool(unionResult))}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) MirrorWithFace(mirrorFace *Face, basePoint *TopoVector, unionResult bool) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_mirror_with_face(wp.inner.val, &mirrorFace.inner.val, basePoint.inner.val, C.bool(unionResult))}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}
func (wp *Workplane) Transform(rotate *TopoVector, offset *TopoVector) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_transformed(wp.inner.val, rotate.inner.val, offset.inner.val)}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) PushPoints(locs []*TopoLocation) *Workplane {
	locsPtr := make([]*C.struct__topo_location_t, len(locs))
	for i, loc := range locs {
		locsPtr[i] = loc.inner.val
	}
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_push_points(wp.inner.val, &locsPtr[0], C.int(len(locs)))}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) PushPointsWithVector(vecs []*TopoVector) *Workplane {
	vecsPtr := make([]*C.struct__topo_vector_t, len(vecs))
	for i, vec := range vecs {
		vecsPtr[i] = vec.inner.val
	}
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_push_points_with_vector(wp.inner.val, &vecsPtr[0], C.int(len(vecs)))}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) Translate(vec *TopoVector) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_translate(wp.inner.val, vec.inner.val)}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) Shell(thickness float64, kind string) *Workplane {
	ckind := C.CString(kind)
	defer C.free(unsafe.Pointer(ckind))
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_shell(wp.inner.val, C.double(thickness), ckind)}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) Fillet(radius float64) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_fillet(wp.inner.val, C.double(radius))}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) Chamfer(length float64, length2 float64) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_chamfer(wp.inner.val, C.double(length), C.double(length2))}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) Rarray(xSpacing float64, ySpacing float64, xCount int, yCount int, centerX bool, centerY bool) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_rarray(wp.inner.val, C.double(xSpacing), C.double(ySpacing), C.int(xCount), C.int(yCount), C.bool(centerX), C.bool(centerY))}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) PolarArray(radius float64, startAngle float64, angle float64, count int, fill bool, rotate bool) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_polar_array(wp.inner.val, C.double(radius), C.double(startAngle), C.double(angle), C.int(count), C.bool(fill), C.bool(rotate))}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) Center(x float64, y float64) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_center(wp.inner.val, C.double(x), C.double(y))}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) LineTo(x float64, y float64, forConstruction bool) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_line_to(wp.inner.val, C.double(x), C.double(y), C.bool(forConstruction))}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) Bezier(points []*TopoVector, forConstruction bool, includeCurrent bool, makeWire bool) *Workplane {
	pointsPtr := make([]*C.struct__topo_vector_t, len(points))
	for i, point := range points {
		pointsPtr[i] = point.inner.val
	}
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_bezier(wp.inner.val, &pointsPtr[0], C.int(len(points)), C.bool(forConstruction), C.bool(includeCurrent), C.bool(makeWire))}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) Line(xDist float64, yDist float64, forConstruction bool) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_line(wp.inner.val, C.double(xDist), C.double(yDist), C.bool(forConstruction))}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) VLine(distance float64, forConstruction bool) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_vline(wp.inner.val, C.double(distance), C.bool(forConstruction))}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) HLine(distance float64, forConstruction bool) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_hline(wp.inner.val, C.double(distance), C.bool(forConstruction))}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) VLineTo(yCoord float64, forConstruction bool) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_vline_to(wp.inner.val, C.double(yCoord), C.bool(forConstruction))}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) HLineTo(xCoord float64, forConstruction bool) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_hline_to(wp.inner.val, C.double(xCoord), C.bool(forConstruction))}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) PolarLine(distance float64, angle float64, forConstruction bool) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_polar_line(wp.inner.val, C.double(distance), C.double(angle), C.bool(forConstruction))}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) PolarLineTo(distance float64, angle float64, forConstruction bool) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_polar_line_to(wp.inner.val, C.double(distance), C.double(angle), C.bool(forConstruction))}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) MoveTo(x float64, y float64) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_move_to(wp.inner.val, C.double(x), C.double(y))}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) Move(xDist float64, yDist float64) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_move(wp.inner.val, C.double(xDist), C.double(yDist))}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) Slot2d(length float64, diameter float64, angle float64) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_slot2d(wp.inner.val, C.double(length), C.double(diameter), C.double(angle))}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) Spline(points []*TopoVector, periodic bool, tangents []*TopoVector, scale bool, tol float64, forConstruction bool, includeCurrent bool, makeWire bool) *Workplane {
	pointsPtr := make([]*C.struct__topo_vector_t, len(points))
	for i, point := range points {
		pointsPtr[i] = point.inner.val
	}
	tangentsPtr := make([]*C.struct__topo_vector_t, len(tangents))
	for i, tangent := range tangents {
		tangentsPtr[i] = tangent.inner.val
	}
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_spline(wp.inner.val, &pointsPtr[0], C.int(len(points)), C.bool(periodic), &tangentsPtr[0], C.int(len(tangents)), C.bool(scale), C.double(tol), C.bool(forConstruction), C.bool(includeCurrent), C.bool(makeWire))}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) SplineApprox(points []*TopoVector, tol float64, minDeg int, maxDeg int, smoothing *TopoVector, forConstruction bool, includeCurrent bool, makeWire bool) *Workplane {
	pointsPtr := make([]*C.struct__topo_vector_t, len(points))
	for i, point := range points {
		pointsPtr[i] = point.inner.val
	}
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_spline_approx(wp.inner.val, &pointsPtr[0], C.int(len(points)), C.double(tol), C.int(minDeg), C.int(maxDeg), smoothing.inner.val, C.bool(forConstruction), C.bool(includeCurrent), C.bool(makeWire))}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

//export parametricCurveFunc
func parametricCurveFunc(userdata unsafe.Pointer, t float64) *C.struct__topo_vector_t {
	func_ := *(*func(float64) *TopoVector)(userdata)
	return func_(t).inner.val
}

// C.parametricCurveFunc
func (wp *Workplane) ParametricCurve(func_ func(float64) *TopoVector, N int, start float64, stop float64, tol float64, minDeg int, maxDeg int, smoothing *TopoVector, makeWire bool) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_parametric_curve(wp.inner.val, unsafe.Pointer(&func_), (*[0]byte)(C.parametricCurveFunc), C.int(N), C.double(start), C.double(stop), C.double(tol), C.int(minDeg), C.int(maxDeg), smoothing.inner.val, C.bool(makeWire))}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

//export parametricSurfaceFunc
func parametricSurfaceFunc(userdata unsafe.Pointer, t float64, u float64) *C.struct__topo_vector_t {
	func_ := *(*func(float64, float64) *TopoVector)(userdata)
	return func_(t, u).inner.val
}

func (wp *Workplane) ParametricSurface(func_ func(float64, float64) *TopoVector, N int, start float64, stop float64, tol float64, minDeg int, maxDeg int, smoothing *TopoVector) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_parametric_surface(wp.inner.val, unsafe.Pointer(&func_), (*[0]byte)(C.parametricSurfaceFunc), C.int(N), C.double(start), C.double(stop), C.double(tol), C.int(minDeg), C.int(maxDeg), smoothing.inner.val)}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) EllipseArc(xRadius float64, yRadius float64, angle1 float64, angle2 float64, rotationAngle float64, sense int, forConstruction bool, startAtCurrent bool, makeWire bool) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_ellipse_arc(wp.inner.val, C.double(xRadius), C.double(yRadius), C.double(angle1), C.double(angle2), C.double(rotationAngle), C.int(sense), C.bool(forConstruction), C.bool(startAtCurrent), C.bool(makeWire))}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) ThreePointArc(point1 *TopoVector, point2 *TopoVector, forConstruction bool) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_three_point_arc(wp.inner.val, point1.inner.val, point2.inner.val, C.bool(forConstruction))}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) SagittaArc(endPoint *TopoVector, sag float64, forConstruction bool) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_sagitta_arc(wp.inner.val, endPoint.inner.val, C.double(sag), C.bool(forConstruction))}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) TangentArcPoint(endPoint *TopoVector, forConstruction bool, relative bool) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_tangent_arc_point(wp.inner.val, endPoint.inner.val, C.bool(forConstruction), C.bool(relative))}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) RadiusArc(endPoint *TopoVector, radius float64, forConstruction bool) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_radius_arc(wp.inner.val, endPoint.inner.val, C.double(radius), C.bool(forConstruction))}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) MirrorY() *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_mirror_y(wp.inner.val)}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) MirrorX() *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_mirror_x(wp.inner.val)}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) ConsolidateWires() *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_consolidate_wires(wp.inner.val)}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

// export eachFunc
func eachFunc(userdata unsafe.Pointer, obj *C.struct__shape_object_t) {
	func_ := *(*func(*ShapeObject))(userdata)
	o := &ShapeObject{inner: &innerShapeObject{val: obj}}
	runtime.SetFinalizer(o, (*innerShapeObject).free)
	func_(o)
}

func (wp *Workplane) Each(func_ func(*ShapeObject)) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_each(wp.inner.val, unsafe.Pointer(&func_), (*[0]byte)(C.eachFunc), C.bool(false), C.bool(false), C.bool(false))}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) EachPoint(func_ func(*ShapeObject)) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_eachpoint(wp.inner.val, unsafe.Pointer(&func_), (*[0]byte)(C.eachFunc), C.bool(false), C.bool(false), C.bool(false))}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) EachPointWithShape(shapeObj *Shape) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_eachpoint_with_shape(wp.inner.val, shapeObj.inner.val, C.bool(false), C.bool(false), C.bool(false))}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) EachPointWithWorkplane(wp2 *Workplane) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_eachpoint_with_workplane(wp.inner.val, wp2.inner.val, C.bool(false), C.bool(false), C.bool(false))}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

//export eachFuncWithLocation
func eachFuncWithLocation(userdata unsafe.Pointer, loc *C.struct__topo_location_t) *C.struct__topo_shape_t {
	func_ := *(*func(*TopoLocation) *Shape)(userdata)
	l := &TopoLocation{inner: &innerTopoLocation{val: loc}}
	runtime.SetFinalizer(l, (*innerTopoLocation).free)
	shp := func_(l)
	return shp.inner.val
}

func (wp *Workplane) EachPointWithLocation(func_ func(*TopoLocation) *Shape) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_eachpoint_with_location(wp.inner.val, unsafe.Pointer(&func_), (*[0]byte)(C.eachFuncWithLocation), C.bool(false), C.bool(false), C.bool(false))}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) Rect(xLen, yLen float64, centerX, centerY, forConstruction bool) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_rect(wp.inner.val, C.double(xLen), C.double(yLen), C.bool(centerX), C.bool(centerY), C.bool(forConstruction))}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) RectAll(xLen, yLen float64, centerAll, forConstruction bool) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_rect_all(wp.inner.val, C.double(xLen), C.double(yLen), C.bool(centerAll), C.bool(forConstruction))}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) Circle(radius float64, forConstruction bool) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_circle(wp.inner.val, C.double(radius), C.bool(forConstruction))}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) Ellipse(xRadius, yRadius, rotationAngle float64, forConstruction bool) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_ellipse(wp.inner.val, C.double(xRadius), C.double(yRadius), C.double(rotationAngle), C.bool(forConstruction))}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) Polygon(nSides int, diameter float64, forConstruction, circumscribed bool) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_polygon(wp.inner.val, C.int(nSides), C.double(diameter), C.bool(forConstruction), C.bool(circumscribed))}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) Polyline(points []*TopoVector, forConstruction, includeCurrent bool) *Workplane {
	pointsPtr := make([]*C.struct__topo_vector_t, len(points))
	for i, point := range points {
		pointsPtr[i] = point.inner.val
	}
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_polyline(wp.inner.val, &pointsPtr[0], C.int(len(points)), C.bool(forConstruction), C.bool(includeCurrent))}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) Close() *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_close(wp.inner.val)}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) LargestDimension() float64 {
	return float64(C.workplane_largest_dimension(wp.inner.val))
}

// export cutEachFunc
func cutEachFunc(userdata unsafe.Pointer, loc *C.struct__topo_location_t) *C.struct__topo_shape_t {
	func_ := *(*func(*TopoLocation) *Shape)(userdata)
	l := &TopoLocation{inner: &innerTopoLocation{val: loc}}
	runtime.SetFinalizer(l, (*innerTopoLocation).free)
	shp := func_(l)
	return shp.inner.val
}

func (wp *Workplane) CutEach(func_ func(*TopoLocation) *Shape, useLocalCoordinates, clean bool) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_cut_each(wp.inner.val, unsafe.Pointer(&func_), (*[0]byte)(C.cutEachFunc), C.bool(useLocalCoordinates), C.bool(clean))}}
	runtime.SetFinalizer(c, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) CboreHole(diameter, cboreDiameter, cboreDepth, depth float64, clean bool) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_cbore_hole(wp.inner.val, C.double(diameter), C.double(cboreDiameter), C.double(cboreDepth), C.double(depth), C.bool(clean))}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) CskHole(diameter, cskDiameter, cskAngle, depth float64, clean bool) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_csk_hole(wp.inner.val, C.double(diameter), C.double(cskDiameter), C.double(cskAngle), C.double(depth), C.bool(clean))}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) Hole(diameter, depth float64, clean bool) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_hole(wp.inner.val, C.double(diameter), C.double(depth), C.bool(clean))}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) TwistExtrude(distance, angleDegrees float64, combine, clean bool) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_twist_extrude(wp.inner.val, C.double(distance), C.double(angleDegrees), C.bool(combine), C.bool(clean))}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) Extrude(distance float64, combine, clean, both bool, taper float64) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_extrude(wp.inner.val, C.double(distance), C.bool(combine), C.bool(clean), C.bool(both), (*C.double)(&taper))}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) ExtrudeWithFaceType(indexType int, combine, clean, both bool, taper float64) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_extrude_with_face_type(wp.inner.val, C.int(indexType), C.bool(combine), C.bool(clean), C.bool(both), (*C.double)(&taper))}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) ExtrudeWithFace(face *Face, combine, clean, both bool, taper float64) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_extrude_with_face(wp.inner.val, &face.inner.val, C.bool(combine), C.bool(clean), C.bool(both), (*C.double)(&taper))}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) Sweep(path *Workplane, multisection, makeSolid, isFrenet, combine, clean bool, transition int, normal *TopoVector, auxSpine *Workplane) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_sweep(wp.inner.val, path.inner.val, C.bool(multisection), C.bool(makeSolid), C.bool(isFrenet), C.bool(combine), C.bool(clean), C.int(transition), normal.inner.val, auxSpine.inner.val)}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) SweepWithWire(wire *Wire, multisection, makeSolid, isFrenet, combine, clean bool, transition int, normal *TopoVector, auxSpine *Workplane) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_sweep_with_wire(wp.inner.val, &wire.inner.val, C.bool(multisection), C.bool(makeSolid), C.bool(isFrenet), C.bool(combine), C.bool(clean), C.int(transition), normal.inner.val, auxSpine.inner.val)}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) SweepWithEdge(edge *Edge, multisection, makeSolid, isFrenet, combine, clean bool, transition int, normal *TopoVector, auxSpine *Workplane) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_sweep_with_edge(wp.inner.val, &edge.inner.val, C.bool(multisection), C.bool(makeSolid), C.bool(isFrenet), C.bool(combine), C.bool(clean), C.int(transition), normal.inner.val, auxSpine.inner.val)}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) Union(other *Workplane, clean, glue bool, tol float64) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_union(wp.inner.val, other.inner.val, C.bool(clean), C.bool(glue), C.double(tol))}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) UnionWithSolid(solid *Solid, clean, glue bool, tol float64) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_union_with_solid(wp.inner.val, &solid.inner.val, C.bool(clean), C.bool(glue), C.double(tol))}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) UnionWithCompound(compound *Compound, clean, glue bool, tol float64) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_union_with_compound(wp.inner.val, &compound.inner.val, C.bool(clean), C.bool(glue), C.double(tol))}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) Cut(other *Workplane, clean bool, tol float64) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_cut(wp.inner.val, other.inner.val, C.bool(clean), C.double(tol))}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) CutWithSolid(solid *Solid, clean bool, tol float64) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_cut_with_solid(wp.inner.val, &solid.inner.val, C.bool(clean), C.double(tol))}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) CutWithCompound(compound *Compound, clean bool, tol float64) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_cut_with_compound(wp.inner.val, &compound.inner.val, C.bool(clean), C.double(tol))}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) Intersect(other *Workplane, clean bool, tol float64) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_intersect(wp.inner.val, other.inner.val, C.bool(clean), C.double(tol))}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) IntersectWithSolid(solid *Solid, clean bool, tol float64) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_intersect_with_solid(wp.inner.val, &solid.inner.val, C.bool(clean), C.double(tol))}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) IntersectWithCompound(compound *Compound, clean bool, tol float64) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_intersect_with_compound(wp.inner.val, &compound.inner.val, C.bool(clean), C.double(tol))}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) CutBlind(distance float64, clean, both bool, taper float64) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_cut_blind(wp.inner.val, C.double(distance), C.bool(clean), C.bool(both), C.double(taper))}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) CutBlindWithUntilFace(untilFace int, clean, both bool, taper float64) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_cut_blind_with_until_face(wp.inner.val, C.int(untilFace), C.bool(clean), C.bool(both), C.double(taper))}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) CutBlindWithFace(face *Face, clean, both bool, taper float64) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_cut_blind_with_face(wp.inner.val, &face.inner.val, C.bool(clean), C.bool(both), C.double(taper))}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) Revolve(axisStart, axisEnd *TopoVector, angleDegrees float64, combine, clean bool) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_revolve(wp.inner.val, axisStart.inner.val, axisEnd.inner.val, C.double(angleDegrees), C.bool(combine), C.bool(clean))}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) InterpPlate(points []*TopoVector, thickness float64, combine, clean bool, degree, nbPtsOnCur, nbIter int, anisotropy bool, tol2d, tol3d, tolAng, tolCurv float64, maxDeg, maxSegments int) *Workplane {
	pointsPtr := make([]*C.struct__topo_vector_t, len(points))
	for i, point := range points {
		pointsPtr[i] = point.inner.val
	}
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_interp_plate(wp.inner.val, &pointsPtr[0], C.int(len(points)), C.double(thickness), C.bool(combine), C.bool(clean), C.int(degree), C.int(nbPtsOnCur), C.int(nbIter), C.bool(anisotropy), C.double(tol2d), C.double(tol3d), C.double(tolAng), C.double(tolCurv), C.int(maxDeg), C.int(maxSegments))}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) InterpPlateWithEdges(edges []*Edge, points []*TopoVector, thickness float64, combine, clean bool, degree, nbPtsOnCur, nbIter int, anisotropy bool, tol2d, tol3d, tolAng, tolCurv float64, maxDeg, maxSegments int) *Workplane {
	edgesPtr := make([]*C.struct__topo_edge_t, len(edges))
	for i, edge := range edges {
		edgesPtr[i] = &edge.inner.val
	}
	pointsPtr := make([]*C.struct__topo_vector_t, len(points))
	for i, point := range points {
		pointsPtr[i] = point.inner.val
	}
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_interp_plate_with_edges(wp.inner.val, &edgesPtr[0], C.int(len(edges)), &pointsPtr[0], C.int(len(points)), C.double(thickness), C.bool(combine), C.bool(clean), C.int(degree), C.int(nbPtsOnCur), C.int(nbIter), C.bool(anisotropy), C.double(tol2d), C.double(tol3d), C.double(tolAng), C.double(tolCurv), C.int(maxDeg), C.int(maxSegments))}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) InterpPlateWithWorkplane(wp2 *Workplane, points []*TopoVector, thickness float64, combine, clean bool, degree, nbPtsOnCur, nbIter int, anisotropy bool, tol2d, tol3d, tolAng, tolCurv float64, maxDeg, maxSegments int) *Workplane {
	pointsPtr := make([]*C.struct__topo_vector_t, len(points))
	for i, point := range points {
		pointsPtr[i] = point.inner.val
	}
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_interp_plate_with_workplane(wp.inner.val, wp2.inner.val, &pointsPtr[0], C.int(len(points)), C.double(thickness), C.bool(combine), C.bool(clean), C.int(degree), C.int(nbPtsOnCur), C.int(nbIter), C.bool(anisotropy), C.double(tol2d), C.double(tol3d), C.double(tolAng), C.double(tolCurv), C.int(maxDeg), C.int(maxSegments))}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) Box(length, width, height float64, centerX, centerY, centerZ, combine, clean bool) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_box(wp.inner.val, C.double(length), C.double(width), C.double(height), C.bool(centerX), C.bool(centerY), C.bool(centerZ), C.bool(combine), C.bool(clean))}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) BoxAll(length, width, height float64, centerAll, combine, clean bool) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_box_all(wp.inner.val, C.double(length), C.double(width), C.double(height), C.bool(centerAll), C.bool(combine), C.bool(clean))}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) Sphere(radius float64, direct *TopoVector, angle1, angle2, angle3 float64, centerX, centerY, centerZ, combine, clean bool) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_sphere(wp.inner.val, C.double(radius), direct.inner.val, C.double(angle1), C.double(angle2), C.double(angle3), C.bool(centerX), C.bool(centerY), C.bool(centerZ), C.bool(combine), C.bool(clean))}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) SphereAll(radius float64, direct *TopoVector, angle1, angle2, angle3 float64, centerAll, combine, clean bool) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_sphere_all(wp.inner.val, C.double(radius), direct.inner.val, C.double(angle1), C.double(angle2), C.double(angle3), C.bool(centerAll), C.bool(combine), C.bool(clean))}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) Cylinder(height, radius float64, direct *TopoVector, angle float64, centerX, centerY, centerZ, combine, clean bool) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_cylinder(wp.inner.val, C.double(height), C.double(radius), direct.inner.val, C.double(angle), C.bool(centerX), C.bool(centerY), C.bool(centerZ), C.bool(combine), C.bool(clean))}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) CylinderAll(height, radius float64, direct *TopoVector, angle float64, centerAll, combine, clean bool) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_cylinder_all(wp.inner.val, C.double(height), C.double(radius), direct.inner.val, C.double(angle), C.bool(centerAll), C.bool(combine), C.bool(clean))}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) Wedge(dx, dy, dz, xmin, zmin, xmax, zmax float64, pnt, dir *TopoVector, centerX, centerY, centerZ, combine, clean bool) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_wedge(wp.inner.val, C.double(dx), C.double(dy), C.double(dz), C.double(xmin), C.double(zmin), C.double(xmax), C.double(zmax), pnt.inner.val, dir.inner.val, C.bool(centerX), C.bool(centerY), C.bool(centerZ), C.bool(combine), C.bool(clean))}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) WedgeAll(dx, dy, dz, xmin, zmin, xmax, zmax float64, pnt, dir *TopoVector, centerAll, combine, clean bool) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_wedge_all(wp.inner.val, C.double(dx), C.double(dy), C.double(dz), C.double(xmin), C.double(zmin), C.double(xmax), C.double(zmax), pnt.inner.val, dir.inner.val, C.bool(centerAll), C.bool(combine), C.bool(clean))}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) Combine(clean, glue bool, tol float64) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_combine(wp.inner.val, C.bool(clean), C.bool(glue), C.double(tol))}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) CutThruAll(taper float64, clean bool) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_cut_thru_all(wp.inner.val, C.double(taper), C.bool(clean))}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) Loft(ruled, combine, clean bool) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_loft(wp.inner.val, C.bool(ruled), C.bool(combine), C.bool(clean))}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) Text(txt string, fontsize, distance float64, cut, combine, clean bool, font, fontPath string, kind, halign, valign int) *Workplane {
	ctxt := C.CString(txt)
	defer C.free(unsafe.Pointer(ctxt))
	cfont := C.CString(font)
	defer C.free(unsafe.Pointer(cfont))
	cfontPath := C.CString(fontPath)
	defer C.free(unsafe.Pointer(cfontPath))

	c := &Workplane{inner: &innerWorkplane{val: C.workplane_text(wp.inner.val, ctxt, C.double(fontsize), C.double(distance), C.bool(cut), C.bool(combine), C.bool(clean), cfont, cfontPath, C.int(kind), C.int(halign), C.int(valign))}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) Section(height float64) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_section(wp.inner.val, C.double(height))}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) ToPending() *Workplane {
	C.workplane_to_pending(wp.inner.val)
	return wp
}

func (wp *Workplane) Offset2D(d float64, kind int, forConstruction bool) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_offset2d(wp.inner.val, C.double(d), C.int(kind), C.bool(forConstruction))}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) PlaceSketch(sketches []*Sketch) *Workplane {
	sketchesPtr := make([]*C.struct__sketch_t, len(sketches))
	for i, sketch := range sketches {
		sketchesPtr[i] = sketch.inner.val
	}
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_place_sketch(wp.inner.val, &sketchesPtr[0], C.int(len(sketches)))}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) Get(index int) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_get(wp.inner.val, C.int(index))}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) GetRange(start, end int) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_get_range(wp.inner.val, C.int(start), C.int(end))}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) GetIndices(indices []int) *Workplane {
	cIndices := make([]C.int, len(indices))
	for i, v := range indices {
		cIndices[i] = C.int(v)
	}
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_get_indices(wp.inner.val, &cIndices[0], C.int(len(indices)))}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) ExportTo(path string) {
	cpath := C.CString(path)
	defer C.free(unsafe.Pointer(cpath))
	C.workplane_export_to(wp.inner.val, cpath)
}

func (wp *Workplane) Sketch() *Sketch {
	c := &Sketch{inner: &innerSketch{C.workplane_sketck(wp.inner.val)}}
	runtime.SetFinalizer(c.inner, (*innerSketch).free)
	return c
}

func (wp *Workplane) First() *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_first(wp.inner.val)}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) Item(i int) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_item(wp.inner.val, C.int(i))}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) Last() *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_last(wp.inner.val)}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) End(n int) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_end(wp.inner.val, C.int(n))}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

func (wp *Workplane) All() []*Workplane {
	var count C.int
	ptr := C.workplane_all(wp.inner.val, &count)
	if ptr == nil {
		return nil
	}

	defer C.workplane_list_free(ptr, count)

	workspaces := make([]*Workplane, int(count))
	slice := (*[1 << 30]*C.struct__workplane_t)(unsafe.Pointer(ptr))[:count:count]
	for i := 0; i < int(count); i++ {
		workspaces[i] = &Workplane{inner: &innerWorkplane{val: slice[i]}}
		runtime.SetFinalizer(workspaces[i].inner, (*innerWorkplane).free)
	}
	return workspaces
}

func (wp *Workplane) Shapes() []*Shape {
	var count C.int
	ptr := C.workplane_shapes(wp.inner.val, &count)
	if ptr == nil {
		return nil
	}

	defer C.shape_list_free(ptr, count)

	shapes := make([]*Shape, int(count))
	slice := (*[1 << 30]*C.struct__topo_shape_t)(unsafe.Pointer(ptr))[:count:count]
	for i := 0; i < int(count); i++ {
		shapes[i] = &Shape{inner: &innerShape{val: slice[i]}}
		runtime.SetFinalizer(shapes[i].inner, (*innerShape).free)
	}
	return shapes
}

func (wp *Workplane) Vals() []*ShapeObject {
	var count C.int
	ptr := C.workplane_vals(wp.inner.val, &count)
	if ptr == nil {
		return nil
	}

	defer C.shape_objects_free(ptr, count)

	shapes := make([]*ShapeObject, int(count))
	slice := (*[1 << 30]*C.struct__shape_object_t)(unsafe.Pointer(ptr))[:count:count]
	for i := 0; i < int(count); i++ {
		shapes[i] = &ShapeObject{inner: &innerShapeObject{val: slice[i]}}
		runtime.SetFinalizer(shapes[i].inner, (*innerShapeObject).free)
	}
	return shapes
}

func (wp *Workplane) Val() *ShapeObject {
	c := &ShapeObject{inner: &innerShapeObject{val: C.workplane_val(wp.inner.val)}}
	runtime.SetFinalizer(c.inner, (*innerShapeObject).free)
	return c
}

func (wp *Workplane) Size() int {
	return int(C.workplane_size(wp.inner.val))
}

func (wp *Workplane) HasParent() bool {
	return bool(C.workplane_has_parent(wp.inner.val))
}

func (wp *Workplane) Parent() *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_parent(wp.inner.val)}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

//export workplaneFilterFunc
func workplaneFilterFunc(userdata unsafe.Pointer, obj *C.struct__shape_object_t) C.bool {
	func_ := *(*func(*ShapeObject) bool)(userdata)
	o := &ShapeObject{inner: &innerShapeObject{val: obj}}
	runtime.SetFinalizer(o.inner, (*innerShapeObject).free)
	return C.bool(func_(o))
}

func (wp *Workplane) Filter(func_ func(*ShapeObject) bool) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_filter(wp.inner.val, unsafe.Pointer(&func_), (*[0]byte)(C.workplaneFilterFunc))}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

//export workplaneMapFunc
func workplaneMapFunc(userdata unsafe.Pointer, obj *C.struct__shape_object_t) *C.struct__shape_object_t {
	func_ := *(*func(*ShapeObject) *ShapeObject)(userdata)
	o := &ShapeObject{inner: &innerShapeObject{val: obj}}
	runtime.SetFinalizer(o.inner, (*innerShapeObject).free)
	result := func_(o)
	return result.inner.val
}

func (wp *Workplane) Map(func_ func(*ShapeObject) *ShapeObject) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_map(wp.inner.val, unsafe.Pointer(&func_), (*[0]byte)(C.workplaneMapFunc))}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

//export workplaneApplyFunc
func workplaneApplyFunc(userdata unsafe.Pointer, objs **C.struct__shape_object_t, count C.int) **C.struct__shape_object_t {
	func_ := *(*func([]*ShapeObject) []*ShapeObject)(userdata)

	slice := (*[1 << 30]*C.struct__shape_object_t)(unsafe.Pointer(objs))[:count:count]
	input := make([]*ShapeObject, count)
	for i := range input {
		input[i] = &ShapeObject{inner: &innerShapeObject{val: slice[i]}}
		runtime.SetFinalizer(input[i].inner, (*innerShapeObject).free)
	}

	output := func_(input)

	result := C.malloc(C.size_t(len(output)) * C.size_t(unsafe.Sizeof(uintptr(0))))
	outputSlice := (*[1 << 30]*C.struct__shape_object_t)(result)
	for i, obj := range output {
		outputSlice[i] = obj.inner.val
	}

	return (**C.struct__shape_object_t)(result)
}

func (wp *Workplane) Apply(func_ func([]*ShapeObject) []*ShapeObject) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_apply(wp.inner.val, unsafe.Pointer(&func_), (*[0]byte)(C.workplaneApplyFunc))}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

//export workplaneSortFunc
func workplaneSortFunc(userdata unsafe.Pointer, obj1, obj2 *C.struct__shape_object_t) C.bool {
	func_ := *(*func(*ShapeObject, *ShapeObject) bool)(userdata)
	o1 := &ShapeObject{inner: &innerShapeObject{val: obj1}}
	o2 := &ShapeObject{inner: &innerShapeObject{val: obj2}}
	runtime.SetFinalizer(o1.inner, (*innerShapeObject).free)
	runtime.SetFinalizer(o2.inner, (*innerShapeObject).free)
	return C.bool(func_(o1, o2))
}

func (wp *Workplane) Sort(func_ func(*ShapeObject, *ShapeObject) bool) *Workplane {
	c := &Workplane{inner: &innerWorkplane{val: C.workplane_sort(wp.inner.val, unsafe.Pointer(&func_), (*[0]byte)(C.workplaneSortFunc))}}
	runtime.SetFinalizer(c.inner, (*innerWorkplane).free)
	return c
}

//export workplaneInvokeFunc
func workplaneInvokeFunc(userdata unsafe.Pointer) *C.struct__workplane_t {
	func_ := *(*func() *Workplane)(userdata)
	wp := func_()
	return wp.inner.val
}

func (wp *Workplane) Invoke(func_ func() *Workplane) {
	C.workplane_invoke(wp.inner.val, unsafe.Pointer(&func_), (*[0]byte)(C.workplaneInvokeFunc))
}
