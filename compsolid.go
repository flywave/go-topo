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

type CompSolid struct {
	inner *innerCompSolid
}

type innerCompSolid struct {
	val C.struct__topo_comp_solid_t
}

func TopoMakeCompSolid() *CompSolid {
	p := &CompSolid{inner: &innerCompSolid{val: C.topo_make_comp_solid()}}
	runtime.SetFinalizer(p.inner, (*innerCompSolid).free)
	return p
}

func (s *CompSolid) IsNull() bool {
	return bool(C.topo_shape_is_null(s.inner.val.shp))
}

func (s *CompSolid) IsValid() bool {
	return bool(C.topo_shape_is_valid(s.inner.val.shp))
}

func (s *CompSolid) Equals(e *Shape) bool {
	return bool(C.topo_shape_equals(s.inner.val.shp, e.inner.val))
}

func (s *CompSolid) Type() int {
	return int(C.topo_shape_type(s.inner.val.shp))
}

func (s *CompSolid) BBox() BBox {
	return BBox{val: C.topo_shape_bounding_box(s.inner.val.shp)}
}

func (s *CompSolid) Hash() int {
	return int(C.topo_shape_hash_code(s.inner.val.shp))
}

func (s *CompSolid) Transform(t Trsf) int {
	return int(C.topo_shape_transform(s.inner.val.shp, t.val))
}

func (s *CompSolid) Translate(v Vector3) int {
	return int(C.topo_shape_translate(s.inner.val.shp, v.val))
}

func (s *CompSolid) RotateFromPoint(angle float64, p1, p2 Point3) int {
	return int(C.topo_shape_rotate_from_two_point(s.inner.val.shp, C.double(angle), p1.val, p2.val))
}

func (s *CompSolid) RotateFromAxis1(angle float64, a Axis1) int {
	return int(C.topo_shape_rotate_from_axis1(s.inner.val.shp, C.double(angle), a.val))
}

func (s *CompSolid) RotateFromQuaternion(q Quaternion) int {
	return int(C.topo_shape_rotate_from_quaternion(s.inner.val.shp, q.val))
}

func (s *CompSolid) Scale(angle float64, a Point3) int {
	return int(C.topo_shape_scale(s.inner.val.shp, C.double(angle), a.val))
}

func (s *CompSolid) MirrorFromPointNorm(pnt, ner Point3) int {
	return int(C.topo_shape_mirror_from_point_norm(s.inner.val.shp, pnt.val, ner.val))
}

func (s *CompSolid) MirrorFromAxis1(a Axis1) int {
	return int(C.topo_shape_mirror_from_axis1(s.inner.val.shp, a.val))
}

func (s *CompSolid) MirrorFromAxis2(a Axis2) int {
	return int(C.topo_shape_mirror_from_axis2(s.inner.val.shp, a.val))
}

func (s *CompSolid) Transformed(t Trsf) *CompSolid {
	var val C.struct__topo_comp_solid_t
	val.shp = C.topo_shape_transformed(s.inner.val.shp, t.val)
	return &CompSolid{inner: &innerCompSolid{val: val}}
}

func (s *CompSolid) Translated(v Vector3) *CompSolid {
	var val C.struct__topo_comp_solid_t
	val.shp = C.topo_shape_translated(s.inner.val.shp, v.val)
	return &CompSolid{inner: &innerCompSolid{val: val}}
}

func (s *CompSolid) RotatedFromPoint(angle float64, p1, p2 Point3) *CompSolid {
	var val C.struct__topo_comp_solid_t
	val.shp = C.topo_shape_rotated_from_two_point(s.inner.val.shp, C.double(angle), p1.val, p2.val)
	return &CompSolid{inner: &innerCompSolid{val: val}}
}

func (s *CompSolid) RotatedFromAxis1(angle float64, a Axis1) *CompSolid {
	var val C.struct__topo_comp_solid_t
	val.shp = C.topo_shape_rotated_from_axis1(s.inner.val.shp, C.double(angle), a.val)
	return &CompSolid{inner: &innerCompSolid{val: val}}
}

func (s *CompSolid) RotatedFromQuaternion(q Quaternion) *CompSolid {
	var val C.struct__topo_comp_solid_t
	val.shp = C.topo_shape_rotated_from_quaternion(s.inner.val.shp, q.val)
	return &CompSolid{inner: &innerCompSolid{val: val}}
}

func (s *CompSolid) Scaled(angle float64, a Point3) *CompSolid {
	var val C.struct__topo_comp_solid_t
	val.shp = C.topo_shape_scaled(s.inner.val.shp, C.double(angle), a.val)
	return &CompSolid{inner: &innerCompSolid{val: val}}
}

func (s *CompSolid) MirroredFromPointNorm(pnt, ner Point3) *CompSolid {
	var val C.struct__topo_comp_solid_t
	val.shp = C.topo_shape_mirrored_from_point_norm(s.inner.val.shp, pnt.val, ner.val)
	return &CompSolid{inner: &innerCompSolid{val: val}}
}

func (s *CompSolid) MirroredFromAxis1(a Axis1) *CompSolid {
	var val C.struct__topo_comp_solid_t
	val.shp = C.topo_shape_mirrored_from_axis1(s.inner.val.shp, a.val)
	return &CompSolid{inner: &innerCompSolid{val: val}}
}

func (s *CompSolid) MirroredFromAxis2(a Axis2) *CompSolid {
	var val C.struct__topo_comp_solid_t
	val.shp = C.topo_shape_mirrored_from_axis2(s.inner.val.shp, a.val)
	return &CompSolid{inner: &innerCompSolid{val: val}}
}

func (s *CompSolid) GetOrientation() int {
	return int(C.topo_shape_get_orientation(s.inner.val.shp))
}

func (s *CompSolid) SetOrientation(t int) {
	C.topo_shape_set_orientation(s.inner.val.shp, C.int(t))
}

func (s *CompSolid) GetLocation() *TopoLocation {
	p := &TopoLocation{inner: &innerTopoLocation{val: C.topo_shape_get_location(s.inner.val.shp)}}
	runtime.SetFinalizer(p.inner, (*innerTopoLocation).free)
	return p
}

func (s *CompSolid) SetLocation(t *TopoLocation) {
	C.topo_shape_set_location(s.inner.val.shp, t.inner.val)
}

func (s *CompSolid) FixShape() bool {
	return bool(C.topo_shape_fix_shape(s.inner.val.shp))
}

func (s *CompSolid) Copy() *CompSolid {
	var val C.struct__topo_comp_solid_t
	val.shp = C.topo_shape_copy(s.inner.val.shp)
	return &CompSolid{inner: &innerCompSolid{val: val}}
}

func (s *CompSolid) Mesh(m *MeshReceiver, tolerance, deflection, angle float64) {
	C.topo_shape_mesh(s.inner.val.shp, m.inner.val, C.double(tolerance), C.double(deflection), C.double(angle), C.bool(false))
}

func (s *CompSolid) MeshWithTexture(m *MeshReceiver, tolerance, deflection, angle float64) {
	m.hasTexCoords = true
	C.topo_shape_mesh(s.inner.val.shp, m.inner.val, C.double(tolerance), C.double(deflection), C.double(angle), C.bool(true))
}

func (s *CompSolid) SetSurfaceColour(c Color) {
	C.topo_shape_set_surface_colour(s.inner.val.shp, c.val)
}

func (s *CompSolid) SetCurveColour(c Color) {
	C.topo_shape_set_curve_colour(s.inner.val.shp, c.val)
}

func (s *CompSolid) SetLabel(l string) {
	str := C.CString(l)
	defer C.free(unsafe.Pointer(str))
	C.topo_shape_set_label(s.inner.val.shp, str)
}

func (s *CompSolid) SetUVOrigin(u, v float64) {
	C.topo_shape_set_u_origin(s.inner.val.shp, C.double(u))
	C.topo_shape_set_v_origin(s.inner.val.shp, C.double(v))
}

func (s *CompSolid) SetUVRepeat(u, v float64) {
	C.topo_shape_set_u_repeat(s.inner.val.shp, C.double(u))
	C.topo_shape_set_v_repeat(s.inner.val.shp, C.double(v))
}

func (s *CompSolid) SetScaleU(u float64) {
	C.topo_shape_set_scale_u(s.inner.val.shp, C.double(u))
}

func (s *CompSolid) SetScaleV(v float64) {
	C.topo_shape_set_scale_v(s.inner.val.shp, C.double(v))
}

func (s *CompSolid) SetAutoScaleSizeOnU(u float64) {
	C.topo_shape_set_auto_scale_size_on_u(s.inner.val.shp, C.double(u))
}

func (s *CompSolid) SetAutoScaleSizeOnV(v float64) {
	C.topo_shape_set_auto_scale_size_on_v(s.inner.val.shp, C.double(v))
}

func (s *CompSolid) SetTextureMapType(t int) {
	C.topo_shape_set_txture_map_type(s.inner.val.shp, C.int(t))
}

func (s *CompSolid) SetRotationAngle(a float64) {
	C.topo_shape_set_rotation_angle(s.inner.val.shp, C.double(a))
}

func (s *CompSolid) GetSurfaceColour() Color {
	return Color{val: C.topo_shape_get_surface_colour(s.inner.val.shp)}
}

func (s *CompSolid) GetCurveColour() Color {
	return Color{val: C.topo_shape_get_surface_colour(s.inner.val.shp)}
}

func (s *CompSolid) GetLabel() string {
	return C.GoString(C.topo_shape_get_label(s.inner.val.shp))
}

func (s *CompSolid) GetUVOrigin() (u, v float64) {
	u = float64(C.topo_shape_get_u_origin(s.inner.val.shp))
	v = float64(C.topo_shape_get_v_origin(s.inner.val.shp))
	return
}

func (s *CompSolid) GetUVRepeat() (u, v float64) {
	u = float64(C.topo_shape_get_u_repeat(s.inner.val.shp))
	v = float64(C.topo_shape_get_v_repeat(s.inner.val.shp))
	return
}

func (s *CompSolid) GetUVScale() (u, v float64) {
	u = float64(C.topo_shape_get_scale_u(s.inner.val.shp))
	v = float64(C.topo_shape_get_scale_v(s.inner.val.shp))
	return
}

func (s *CompSolid) GetUVAutoScaleSize() (u, v float64) {
	u = float64(C.topo_shape_get_auto_scale_size_on_u(s.inner.val.shp))
	v = float64(C.topo_shape_get_auto_scale_size_on_v(s.inner.val.shp))
	return
}

func (s *CompSolid) GetTxtureMapType() int {
	return int(C.topo_shape_get_txture_map_type(s.inner.val.shp))
}

func (s *CompSolid) GetRotationAngle() float64 {
	return float64(C.topo_shape_get_rotation_angle(s.inner.val.shp))
}

func (t *innerCompSolid) free() {
	C.topo_comp_solid_free(t.val)
}

func (t *CompSolid) solid() C.struct__topo_solid_t {
	var val C.struct__topo_solid_t
	val.shp = t.inner.val.shp
	return val
}

func (t *CompSolid) ToShape() *Shape {
	sp := &Shape{inner: &innerShape{val: C.topo_shape_share(t.inner.val.shp)}}
	runtime.SetFinalizer(sp.inner, (*innerShape).free)
	return sp
}

func (t *CompSolid) ToSolid() *Solid {
	var val C.struct__topo_solid_t
	val.shp = C.topo_shape_share(t.inner.val.shp)
	sld := &Solid{inner: &innerSolid{val: val}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func (s *CompSolid) IsInside(p Point3, tol float64) bool {
	return bool(C.topo_solid_is_inside(s.solid(), p.val, C.double(tol)))
}

func (s *CompSolid) NumSolids() int {
	return int(C.topo_solid_num_solids(s.solid()))
}

func (s *CompSolid) NumFaces() int {
	return int(C.topo_solid_num_faces(s.solid()))
}

func (s *CompSolid) Area() float64 {
	return float64(C.topo_solid_area(s.solid()))
}

func (s *CompSolid) Volume() float64 {
	return float64(C.topo_solid_volume(s.solid()))
}

func (s *CompSolid) Inertia() BBox {
	return BBox{val: C.topo_solid_inertia(s.solid())}
}

func (s *CompSolid) CentreOfMass() Point3 {
	return Point3{val: C.topo_solid_centre_of_mass(s.solid())}
}

func (s *CompSolid) Extrude(f *Face, p1, p2 Point3) int {
	return int(C.topo_solid_extrude(s.solid(), f.inner.val, p1.val, p2.val))
}

func (s *CompSolid) ExtrudeFromDir(f *Face, d Vector3) int {
	return int(C.topo_solid_extrude_from_dir(s.solid(), f.inner.val, d.val))
}

func (s *CompSolid) Revolve(f *Face, p1, p2 Point3, angle float64) int {
	return int(C.topo_solid_revolve(s.solid(), f.inner.val, p1.val, p2.val, C.double(angle)))
}

func (s *CompSolid) ExtrudeWithRotationFromWire(outerWire *Wire, innerWires []*Wire, vecCenter Point3, vecNormal Vector3, angleDegrees float64) int {
	innerCount := len(innerWires)
	cWires := make([]C.struct__topo_wire_t, innerCount)
	for i, w := range innerWires {
		cWires[i] = w.inner.val
	}

	var cWiresPtr *C.struct__topo_wire_t
	if innerCount > 0 {
		cWiresPtr = &cWires[0]
	}

	return int(C.topo_solid_extrude_with_rotation_from_wire(
		s.solid(), outerWire.inner.val, cWiresPtr, C.int(innerCount),
		vecCenter.val, vecNormal.val, C.double(angleDegrees)))
}

func (s *CompSolid) ExtrudeWithRotationFromFace(face *Face, vecCenter Point3, vecNormal Vector3, angleDegrees float64) int {
	return int(C.topo_solid_extrude_with_rotation_from_face(
		s.solid(), face.inner.val, vecCenter.val, vecNormal.val,
		C.double(angleDegrees)))
}

func (s *CompSolid) SweepWire(spine *Wire, profiles []*Wire, cornerMode int) int {
	count := len(profiles)
	if count == 0 {
		return 0
	}

	cMem := C.malloc(C.size_t(count) * C.size_t(unsafe.Sizeof(C.struct__topo_wire_t{})))
	defer C.free(cMem)
	cProfiles := (*[1<<30 - 1]C.struct__topo_wire_t)(cMem)[:count:count]
	for i, w := range profiles {
		cProfiles[i] = w.inner.val
	}
	cProfilesPtr := (*C.struct__topo_wire_t)(cMem)
	result := C.topo_solid_sweep_wire(
		s.solid(),
		spine.inner.val,
		cProfilesPtr,
		C.int(count),
		C.int(cornerMode),
	)
	return int(result)
}

func (s *CompSolid) SweepMultiFromVector(profiles []*Shape, path *Shape, makeSolid, isFrenet bool, vec *TopoVector) int {
	count := len(profiles)
	if count == 0 {
		return 0
	}

	cMem := C.malloc(C.size_t(count) * C.size_t(unsafe.Sizeof(uintptr(0))))
	defer C.free(cMem)
	cProfiles := (*[1<<30 - 1]*C.struct__topo_shape_t)(cMem)[:count:count]
	for i, p := range profiles {
		cProfiles[i] = p.inner.val
	}

	return int(C.topo_solid_sweep_multi_from_vector(
		s.solid(), (**C.struct__topo_shape_t)(cMem), C.int(count), path.inner.val,
		C.bool(makeSolid), C.bool(isFrenet), vec.inner.val))
}

func (s *CompSolid) SweepMultiFromWire(profiles []*Shape, path *Shape, makeSolid, isFrenet bool, wire *Wire) int {
	count := len(profiles)
	if count == 0 {
		return 0
	}

	cMem := C.malloc(C.size_t(count) * C.size_t(unsafe.Sizeof(uintptr(0))))
	defer C.free(cMem)
	cProfiles := (*[1<<30 - 1]*C.struct__topo_shape_t)(cMem)[:count:count]
	for i, p := range profiles {
		cProfiles[i] = p.inner.val
	}

	return int(C.topo_solid_sweep_multi_from_wire(
		s.solid(), (**C.struct__topo_shape_t)(cMem), C.int(count), path.inner.val,
		C.bool(makeSolid), C.bool(isFrenet), &wire.inner.val))
}

func (s *CompSolid) SweepMultiFromEdge(profiles []*Shape, path *Shape, makeSolid, isFrenet bool, edge *Edge) int {
	count := len(profiles)
	if count == 0 {
		return 0
	}

	cMem := C.malloc(C.size_t(count) * C.size_t(unsafe.Sizeof(uintptr(0))))
	defer C.free(cMem)
	cProfiles := (*[1<<30 - 1]*C.struct__topo_shape_t)(cMem)[:count:count]
	for i, p := range profiles {
		cProfiles[i] = p.inner.val
	}

	return int(C.topo_solid_sweep_multi_from_edge(
		s.solid(), (**C.struct__topo_shape_t)(cMem), C.int(count), path.inner.val,
		C.bool(makeSolid), C.bool(isFrenet), &edge.inner.val))
}

func (s *CompSolid) Loft(profiles []Shape, ruled bool, tolerance float64) int {
	count := len(profiles)
	if count == 0 {
		return 0
	}
	cMem := C.malloc(C.size_t(count) * C.size_t(unsafe.Sizeof(uintptr(0))))
	defer C.free(cMem)
	cProfiles := (*[1<<30 - 1]*C.struct__topo_shape_t)(cMem)[:count:count]
	for i, p := range profiles {
		cProfiles[i] = p.inner.val
	}

	return int(C.topo_solid_loft(s.solid(), (**C.struct__topo_shape_t)(cMem), C.int(len(profiles)), C.bool(ruled), C.double(tolerance)))
}

func (s *CompSolid) Pipe(f *Face, w Wire) int {
	return int(C.topo_solid_pipe(s.solid(), f.inner.val, w.inner.val))
}

func (s *CompSolid) Sweep(spine *Wire, profiles []Shape, cornerMode int) int {
	count := len(profiles)
	if count == 0 {
		return 0
	}

	cMem := C.malloc(C.size_t(count) * C.size_t(unsafe.Sizeof(uintptr(0))))
	defer C.free(cMem)
	cProfiles := (*[1<<30 - 1]*C.struct__topo_shape_t)(cMem)[:count:count]
	for i, p := range profiles {
		cProfiles[i] = p.inner.val
	}
	return int(C.topo_solid_sweep(s.solid(), spine.inner.val, (**C.struct__topo_shape_t)(cMem), C.int(len(profiles)), C.int(cornerMode)))
}

func (s *CompSolid) Boolean(tool *Solid, op int) int {
	return int(C.topo_solid_boolean(s.solid(), tool.inner.val, C.int(op)))
}

func (s *CompSolid) Fillet(edges []Edge, radius []float64) int {
	cshp := C.malloc(C.size_t(len(edges)) * C.size_t(unsafe.Sizeof(C.struct__topo_edge_t{})))
	defer C.free(cshp)
	cshpSlice := (*[1<<30 - 1]C.struct__topo_edge_t)(cshp)[:len(edges):len(edges)]
	for i := range edges {
		cshpSlice[i] = edges[i].inner.val
	}
	return int(C.topo_solid_fillet(s.solid(), (*C.struct__topo_edge_t)(cshp), C.int(len(edges)), (*C.double)(unsafe.Pointer(&radius[0])), C.int(len(radius))))
}

func (s *CompSolid) Chamfer(edges []Edge, distances []float64) int {
	cshp := C.malloc(C.size_t(len(edges)) * C.size_t(unsafe.Sizeof(C.struct__topo_edge_t{})))
	defer C.free(cshp)
	cshpSlice := (*[1<<30 - 1]C.struct__topo_edge_t)(cshp)[:len(edges):len(edges)]
	for i := range edges {
		cshpSlice[i] = edges[i].inner.val
	}
	return int(C.topo_solid_chamfer(s.solid(), (*C.struct__topo_edge_t)(cshp), C.int(len(edges)), (*C.double)(unsafe.Pointer(&distances[0])), C.int(len(distances))))
}

func (s *CompSolid) Shelling(faces []Face, offset, tolerance float64) int {
	cshp := C.malloc(C.size_t(len(faces)) * C.size_t(unsafe.Sizeof(C.struct__topo_face_t{})))
	defer C.free(cshp)
	cshpSlice := (*[1<<30 - 1]C.struct__topo_face_t)(cshp)[:len(faces):len(faces)]
	for i := range faces {
		cshpSlice[i] = faces[i].inner.val
	}
	return int(C.topo_solid_shelling(s.solid(), (*C.struct__topo_face_t)(cshp), C.int(len(faces)), C.double(offset), C.double(tolerance)))
}

func (s *CompSolid) Offset(f *Face, offset, tolerance float64) int {
	return int(C.topo_solid_offset(s.solid(), f.inner.val, C.double(offset), C.double(tolerance)))
}

func (s *CompSolid) Draft(faces []Face, d Dir3, angle float64, p Plane) int {
	cshp := C.malloc(C.size_t(len(faces)) * C.size_t(unsafe.Sizeof(C.struct__topo_face_t{})))
	defer C.free(cshp)
	cshpSlice := (*[1<<30 - 1]C.struct__topo_face_t)(cshp)[:len(faces):len(faces)]
	for i := range faces {
		cshpSlice[i] = faces[i].inner.val
	}
	return int(C.topo_solid_draft(s.solid(), (*C.struct__topo_face_t)(cshp), C.int(len(faces)), d.val, C.double(angle), p.val))
}

func (s *CompSolid) EvolvedFromFace(Spine *Face, Profil *Wire) int {
	return int(C.topo_solid_evolved_from_face(s.solid(), Spine.inner.val, Profil.inner.val))
}

func (s *CompSolid) EvolvedFromWire(Spine *Wire, Profil *Wire) int {
	return int(C.topo_solid_evolved_from_wire(s.solid(), Spine.inner.val, Profil.inner.val))
}

func (s *CompSolid) FeatPrism(f *Face, d Dir3, height float64, fuse bool) int {
	return int(C.topo_solid_feat_prism(s.solid(), f.inner.val, d.val, C.double(height), C.bool(fuse)))
}

func (s *CompSolid) FeatPrismForRange(f *Face, d Dir3, from, end Face, fuse bool) int {
	return int(C.topo_solid_feat_prism_for_range(s.solid(), f.inner.val, d.val, from.inner.val, end.inner.val, C.bool(fuse)))
}

func (s *CompSolid) FeatPrismForUntil(f *Face, d Dir3, until Face, fuse bool) int {
	return int(C.topo_solid_feat_prism_for_until(s.solid(), f.inner.val, d.val, until.inner.val, C.bool(fuse)))
}

func (s *CompSolid) DraftPrism(f *Face, angle, height float64, fuse bool) int {
	return int(C.topo_solid_feat_draft_prism(s.solid(), f.inner.val, C.double(angle), C.double(height), C.bool(fuse)))
}

func (s *CompSolid) DraftPrismForRange(f *Face, angle float64, from, end Face, fuse bool) int {
	return int(C.topo_solid_feat_draft_prism_for_range(s.solid(), f.inner.val, C.double(angle), from.inner.val, end.inner.val, C.bool(fuse)))
}

func (s *CompSolid) DraftPrismForUntil(f *Face, angle float64, until Face, fuse bool) int {
	return int(C.topo_solid_feat_draft_prism_for_until(s.solid(), f.inner.val, C.double(angle), until.inner.val, C.bool(fuse)))
}

func (s *CompSolid) RevolForRange(f *Face, a Axis1, from, end Face, fuse bool) int {
	return int(C.topo_solid_feat_revol_for_range(s.solid(), f.inner.val, a.val, from.inner.val, end.inner.val, C.bool(fuse)))
}

func (s *CompSolid) RevolForUntil(f *Face, a Axis1, until Face, fuse bool) int {
	return int(C.topo_solid_feat_revol_for_until(s.solid(), f.inner.val, a.val, until.inner.val, C.bool(fuse)))
}

func (s *CompSolid) PipeForRange(f *Face, w *Wire, from, end Face, fuse bool) int {
	return int(C.topo_solid_feat_pipe_for_range(s.solid(), f.inner.val, w.inner.val, from.inner.val, end.inner.val, C.bool(fuse)))
}

func (s *CompSolid) PipeForUntil(f *Face, w *Wire, until Face, fuse bool) int {
	return int(C.topo_solid_feat_pipe_for_until(s.solid(), f.inner.val, w.inner.val, until.inner.val, C.bool(fuse)))
}

func (s *CompSolid) LinearForm(w *Wire, p *GeomPlane, d, d1 Dir3, fuse bool) int {
	return int(C.topo_solid_linear_form(s.solid(), w.inner.val, p.inner.geom, d.val, d1.val, C.bool(fuse)))
}

func (s *CompSolid) RevolutionForm(w *Wire, p *GeomPlane, a Axis1, h1, h2 float64, fuse bool) int {
	return int(C.topo_solid_revolution_form(s.solid(), w.inner.val, p.inner.geom, a.val, C.double(h1), C.double(h2), C.bool(fuse)))
}

func (s *CompSolid) SectionFace(pnt, nor Point3) *Face {
	p := &Face{inner: &innerFace{val: C.topo_solid_section_face(s.solid(), pnt.val, nor.val)}}
	runtime.SetFinalizer(p.inner, (*innerFace).free)
	return p
}

func (s *CompSolid) ConvertToNurbs() int {
	return int(C.topo_solid_convert_to_nurbs(s.solid()))
}

func TopoCompSolidMake(s []Solid) *CompSolid {
	cshp := C.malloc(C.size_t(len(s)) * C.size_t(unsafe.Sizeof(C.struct__topo_solid_t{})))
	defer C.free(cshp)
	cshpSlice := (*[1<<30 - 1]C.struct__topo_solid_t)(cshp)[:len(s):len(s)]
	for i := range s {
		cshpSlice[i] = s[i].inner.val
	}
	c := &CompSolid{inner: &innerCompSolid{val: C.topo_comp_solid_make_comp_solid((*C.struct__topo_solid_t)(cshp), C.int(len(s)))}}
	runtime.SetFinalizer(c.inner, (*innerCompSolid).free)
	return c
}

type CompSolidIterator struct {
	inner *innerCompSolidIterator
}
type innerCompSolidIterator struct {
	val *C.struct__topo_comp_solid_iterator_t
}

func TopoMakeCompSolidIterator(p Shape) *CompSolidIterator {
	wr := &CompSolidIterator{inner: &innerCompSolidIterator{val: C.topo_comp_solid_iterator_make(p.inner.val)}}
	runtime.SetFinalizer(wr.inner, (*innerCompSolidIterator).free)
	return wr
}

func (t *innerCompSolidIterator) free() {
	C.topo_comp_solid_iterator_free(t.val)
}

func (t *CompSolidIterator) Next() *CompSolid {
	v := C.topo_comp_solid_iterator_next(t.inner.val)
	if v != nil {
		var val C.struct__topo_comp_solid_t
		val.shp = v
		p := &CompSolid{inner: &innerCompSolid{val: val}}
		runtime.SetFinalizer(p.inner, (*innerCompSolid).free)
		return p
	}
	return nil
}
