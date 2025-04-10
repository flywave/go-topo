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

func Fuse(shapes []*Shape, tol float64, glue bool) *Shape {
	count := len(shapes)
	if count == 0 {
		return nil
	}
	cShapes := make([]*C.struct__topo_shape_t, count)
	for i, shp := range shapes {
		cShapes[i] = shp.inner.val
	}
	result := C.topo_fuse(&cShapes[0], C.int(count), C.double(tol), C.bool(glue))
	if result == nil {
		return nil
	}
	return NewShape(result)
}

func Cut(shp, tool *Shape, tol float64, glue bool) *Shape {
	result := C.topo_cut(shp.inner.val, tool.inner.val, C.double(tol), C.bool(glue))
	if result == nil {
		return nil
	}
	return NewShape(result)
}

func CutMulti(shp *Shape, toCuts []*Shape, tol float64, glue bool) *Shape {
	count := len(toCuts)
	if count == 0 {
		return nil
	}
	cToCuts := make([]*C.struct__topo_shape_t, count)
	for i, cut := range toCuts {
		cToCuts[i] = cut.inner.val
	}
	result := C.topo_cut_multi(shp.inner.val, &cToCuts[0], C.int(count), C.double(tol), C.bool(glue))
	if result == nil {
		return nil
	}
	return NewShape(result)
}

func Intersect(shp, toIntersect *Shape, tol float64, glue bool) *Shape {
	result := C.topo_intersect(shp.inner.val, toIntersect.inner.val, C.double(tol), C.bool(glue))
	if result == nil {
		return nil
	}
	return NewShape(result)
}

func IntersectMulti(shp *Shape, toIntersects []*Shape, tol float64, glue bool) *Shape {
	count := len(toIntersects)
	if count == 0 {
		return nil
	}
	cToIntersects := make([]*C.struct__topo_shape_t, count)
	for i, intersect := range toIntersects {
		cToIntersects[i] = intersect.inner.val
	}
	result := C.topo_intersect_multi(shp.inner.val, &cToIntersects[0], C.int(count), C.double(tol), C.bool(glue))
	if result == nil {
		return nil
	}
	return NewShape(result)
}

func Split(shp *Shape, splitters []*Shape, tol float64) *Shape {
	count := len(splitters)
	if count == 0 {
		return nil
	}
	cSplitters := make([]*C.struct__topo_shape_t, count)
	for i, splitter := range splitters {
		cSplitters[i] = splitter.inner.val
	}
	result := C.topo_split(shp.inner.val, &cSplitters[0], C.int(count), C.double(tol))
	if result == nil {
		return nil
	}
	return NewShape(result)
}

func Fill(shp *Shape, constraints []*Shape) *Shape {
	count := len(constraints)
	if count == 0 {
		return nil
	}
	cConstraints := make([]*C.struct__topo_shape_t, count)
	for i, constraint := range constraints {
		cConstraints[i] = constraint.inner.val
	}
	result := C.topo_fill(shp.inner.val, &cConstraints[0], C.int(count))
	if result == nil {
		return nil
	}
	return NewShape(result)
}

func Shelling(shp *Shape, faces []*Face, thickness, tolerance float64, joinType int) *Shape {
	count := len(faces)
	if count == 0 {
		return nil
	}
	cFaces := make([]C.struct__topo_face_t, count)
	for i, face := range faces {
		cFaces[i] = face.inner.val
	}
	result := C.topo_shelling(shp.inner.val, &cFaces[0], C.int(count),
		C.double(thickness), C.double(tolerance), C.int(joinType))
	if result == nil {
		return nil
	}
	return NewShape(result)
}

func Fillet(shp *Shape, edges []*Edge, radius float64) *Shape {
	count := len(edges)
	if count == 0 {
		return nil
	}
	cEdges := make([]C.struct__topo_edge_t, count)
	for i, edge := range edges {
		cEdges[i] = edge.inner.val
	}
	result := C.topo_fillet(shp.inner.val, &cEdges[0], C.int(count), C.double(radius))
	if result == nil {
		return nil
	}
	return NewShape(result)
}

func Chamfer(shp *Shape, edges []*Edge, distance1, distance2 float64, hasDistance2 bool) *Shape {
	count := len(edges)
	if count == 0 {
		return nil
	}
	cEdges := make([]C.struct__topo_edge_t, count)
	for i, edge := range edges {
		cEdges[i] = edge.inner.val
	}
	result := C.topo_chamfer(shp.inner.val, &cEdges[0], C.int(count),
		C.double(distance1), C.double(distance2), C.bool(hasDistance2))
	if result == nil {
		return nil
	}
	return NewShape(result)
}

func Extrude(shape *Shape, direction Vector3) *Shape {
	result := C.topo_extrude(shape.inner.val, direction.val)
	if result == nil {
		return nil
	}
	return NewShape(result)
}

func ExtrudeLinear(wire *Wire, innerWires []*Wire, normal Vector3, taper float64) *Shape {
	count := len(innerWires)
	cInnerWires := make([]C.struct__topo_wire_t, count)
	for i, innerWire := range innerWires {
		cInnerWires[i] = innerWire.inner.val
	}
	result := C.topo_extrude_linear(wire.inner.val, &cInnerWires[0], C.int(count), normal.val, C.double(taper))
	if result == nil {
		return nil
	}
	return NewShape(result)
}

func ExtrudeLinearWithRotation(wire *Wire, innerWires []*Wire, center Point3, normal Vector3, angleDegrees float64) *Shape {
	count := len(innerWires)
	cInnerWires := make([]C.struct__topo_wire_t, count)
	for i, innerWire := range innerWires {
		cInnerWires[i] = innerWire.inner.val
	}
	result := C.topo_extrude_linear_with_rotation(wire.inner.val, &cInnerWires[0], C.int(count), center.val, normal.val, C.double(angleDegrees))
	if result == nil {
		return nil
	}
	return NewShape(result)
}

func Revolve(shape *Shape, axisPoint Point3, axisDirection Dir3, angleDegrees float64) *Shape {
	result := C.topo_revolve(shape.inner.val, axisPoint.val, axisDirection.val, C.double(angleDegrees))
	if result == nil {
		return nil
	}
	return NewShape(result)
}

func RevolveWire(wire *Wire, innerWires []*Wire, angleDegrees float64, axisStart, axisEnd Point3) *Shape {
	count := len(innerWires)
	cInnerWires := make([]C.struct__topo_wire_t, count)
	for i, innerWire := range innerWires {
		cInnerWires[i] = innerWire.inner.val
	}
	result := C.topo_revolve_wire(wire.inner.val, &cInnerWires[0], C.int(count),
		C.double(angleDegrees), axisStart.val, axisEnd.val)
	if result == nil {
		return nil
	}
	return NewShape(result)
}

type TransitionMode int

const (
	TransitionTransformed TransitionMode = C.TRANSITION_TRANSFORMED
	TransitionRound       TransitionMode = C.TRANSITION_ROUND
	TransitionRight       TransitionMode = C.TRANSITION_RIGHT
)

func Sweep(wire *Wire, innerWires []*Wire, path *Shape, makeSolid, isFrenet bool,
	mode *Shape, transition TransitionMode) *Shape {
	count := len(innerWires)
	cInnerWires := make([]C.struct__topo_wire_t, count)
	for i, innerWire := range innerWires {
		cInnerWires[i] = innerWire.inner.val
	}
	var cMode *C.struct__topo_shape_t
	if mode != nil {
		cMode = mode.inner.val
	}
	result := C.topo_sweep(wire.inner.val, &cInnerWires[0], C.int(count),
		path.inner.val, C.bool(makeSolid), C.bool(isFrenet), cMode,
		C.transition_mode_t(transition))
	if result == nil {
		return nil
	}
	return NewShape(result)
}

func SweepMulti(profiles []*Shape, path *Shape, makeSolid, isFrenet bool, mode *Shape) *Shape {
	count := len(profiles)
	cProfiles := make([]*C.struct__topo_shape_t, count)
	for i, profile := range profiles {
		cProfiles[i] = profile.inner.val
	}
	var cMode *C.struct__topo_shape_t
	if mode != nil {
		cMode = mode.inner.val
	}
	result := C.topo_sweep_multi(&cProfiles[0], C.int(count), path.inner.val,
		C.bool(makeSolid), C.bool(isFrenet), cMode)
	if result == nil {
		return nil
	}
	return NewShape(result)
}

func Loft(profiles []*Shape, cap, ruled bool, continuity, parametrization string,
	degree int, compat, smoothing bool, weights [3]float64) *Shape {
	count := len(profiles)
	cProfiles := make([]*C.struct__topo_shape_t, count)
	for i, profile := range profiles {
		cProfiles[i] = profile.inner.val
	}
	cContinuity := C.CString(continuity)
	cParametrization := C.CString(parametrization)
	defer func() {
		C.free(unsafe.Pointer(cContinuity))
		C.free(unsafe.Pointer(cParametrization))
	}()
	result := C.topo_loft(&cProfiles[0], C.int(count), C.bool(cap), C.bool(ruled),
		cContinuity, cParametrization, C.int(degree), C.bool(compat),
		C.bool(smoothing), (*C.double)(&weights[0]))
	if result == nil {
		return nil
	}
	return NewShape(result)
}

func Offset(shape *Shape, offset float64, cap, both bool, tol float64) *Shape {
	result := C.topo_offset(shape.inner.val, C.double(offset), C.bool(cap),
		C.bool(both), C.double(tol))
	if result == nil {
		return nil
	}
	return NewShape(result)
}

func Clean(shape *Shape) *Shape {
	result := C.topo_clean(shape.inner.val)
	if result == nil {
		return nil
	}
	return NewShape(result)
}

func Closest(shape1, shape2 *Shape) (Point3, Point3) {
	var p1, p2 C.pnt3d_t
	C.topo_closest(shape1.inner.val, shape2.inner.val, &p1, &p2)
	return Point3{val: p1}, Point3{val: p2}
}

func CombinedCenter(objects []*Shape) Point3 {
	count := len(objects)
	if count == 0 {
		return Point3{}
	}
	cObjects := make([]*C.struct__topo_shape_t, count)
	for i, obj := range objects {
		cObjects[i] = obj.inner.val
	}
	result := C.topo_combined_center(&cObjects[0], C.int(count))
	return Point3{val: result}
}

func CombinedCenterOfBoundBox(objects []*Shape) Point3 {
	count := len(objects)
	if count == 0 {
		return Point3{}
	}
	cObjects := make([]*C.struct__topo_shape_t, count)
	for i, obj := range objects {
		cObjects[i] = obj.inner.val
	}
	result := C.topo_combined_center_of_bound_box(&cObjects[0], C.int(count))
	return Point3{val: result}
}
