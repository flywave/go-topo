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

func StepToTopoShape(f string) *Shape {
	fl := C.CString(f)
	defer C.free(unsafe.Pointer(fl))
	res := C.step_get_topo_shape(fl)
	return NewShape(res)
}

type WireSamplePoint struct {
	Position Point3
	Tangent  Vector3
	Edge     *Edge
}

func SampleWireAtDistances(wire *Wire, distances []float64) []WireSamplePoint {
	count := len(distances)
	if count == 0 {
		return nil
	}

	var resultCount C.int
	cDistances := make([]C.double, count)
	for i, d := range distances {
		cDistances[i] = C.double(d)
	}

	cSamples := C.topo_wire_sample_at_distances(
		wire.inner.val,
		&cDistances[0],
		C.int(count),
		&resultCount,
	)
	defer C.topo_wire_sample_list_free(cSamples, resultCount)

	if cSamples == nil {
		return nil
	}

	sampleSlice := (*[1 << 30]C.topo_wire_sample_point_t)(unsafe.Pointer(cSamples))[:resultCount:resultCount]

	samples := make([]WireSamplePoint, resultCount)
	for i := 0; i < int(resultCount); i++ {
		e := &Edge{inner: &innerEdge{val: sampleSlice[i].edge}}
		runtime.SetFinalizer(e.inner, (*innerEdge).free)

		samples[i] = WireSamplePoint{
			Position: Point3{val: sampleSlice[i].position},
			Tangent:  Vector3{val: sampleSlice[i].tangent},
			Edge:     e,
		}
	}

	return samples
}

func ClipWireBetweenDistances(wire *Wire, startDistance, endDistance float64) *Wire {
	result := C.topo_wire_clip_between_distances(
		wire.inner.val,
		C.double(startDistance),
		C.double(endDistance),
	)

	if result.shp == nil {
		return nil
	}
	w := &Wire{inner: &innerWire{result}}
	runtime.SetFinalizer(w.inner, (*innerWire).free)
	return w
}

type ProfileProjection struct {
	inner C.topo_profile_projection_t
}

func (p *ProfileProjection) GetAxis2() Axis2 {
	return Axis2{
		val: p.inner.axes,
	}
}

func (p *ProfileProjection) GetTrsf() Trsf {
	return Trsf{
		val: p.inner.trsf,
	}
}

func (p *ProfileProjection) GeTangent() Vector3 {
	return Vector3{
		val: p.inner.tangent,
	}
}

func (p *ProfileProjection) GePosition() Point3 {
	return Point3{
		val: p.inner.position,
	}
}

func CalcProfileProjection(wire *Wire, up Dir3, offset *float64) ProfileProjection {
	var cOffset *C.double
	if offset != nil {
		cOffset = (*C.double)(offset)
	}
	result := C.topo_calc_profile_projection(wire.inner.val, up.val, cOffset)
	return ProfileProjection{inner: result}
}

func ProfileProjectPoint(proj *ProfileProjection, point Point3) Point3 {
	result := C.topo_profile_project_point(&proj.inner, point.val)
	return Point3{val: result}
}

func ProfileProjectPointList(proj *ProfileProjection, points []Point3) []Point3 {
	count := len(points)
	if count == 0 {
		return nil
	}

	cPoints := make([]C.pnt3d_t, count)
	for i, p := range points {
		cPoints[i] = p.val
	}

	cResult := C.topo_profile_project_point_list(&proj.inner, &cPoints[0], C.int(count))
	defer C.topo_profile_project_point_list_free(cResult)

	if cResult == nil {
		return nil
	}

	result := make([]Point3, count)
	resultSlice := (*[1 << 30]C.pnt3d_t)(unsafe.Pointer(cResult))[:count:count]
	for i := 0; i < count; i++ {
		result[i] = Point3{val: resultSlice[i]}
	}

	return result
}

func WireLength(wire *Wire) float64 {
	return float64(C.topo_wrie_length(wire.inner.val))
}

func MakeCatenary(p1, p2 Point3, slack, maxSag float64, orientation Axis3, tessellation float64) []Point3 {
	var count C.int
	cPoints := C.topo_make_catenary(
		p1.val,
		p2.val,
		C.double(slack),
		C.double(maxSag),
		orientation.val,
		C.double(tessellation),
		&count,
	)
	defer C.topo_free_catenary_points(cPoints)

	if cPoints == nil || count == 0 {
		return nil
	}

	points := make([]Point3, int(count))
	pointsSlice := (*[1 << 30]C.pnt3d_t)(unsafe.Pointer(cPoints))[:count:count]
	for i := 0; i < int(count); i++ {
		points[i] = Point3{val: pointsSlice[i]}
	}

	return points
}
