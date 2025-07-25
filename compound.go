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

type Compound struct {
	inner *innerCompound
}

type innerCompound struct {
	val C.struct__topo_compound_t
}

func TopoMakeCompound() *Compound {
	c := &Compound{inner: &innerCompound{val: C.topo_make_compound()}}
	runtime.SetFinalizer(c.inner, (*innerCompound).free)
	return c
}

func (s *Compound) IsNull() bool {
	return bool(C.topo_shape_is_null(s.inner.val.shp))
}

func (s *Compound) IsValid() bool {
	return bool(C.topo_shape_is_valid(s.inner.val.shp))
}

func (s *Compound) Equals(e *Shape) bool {
	return bool(C.topo_shape_equals(s.inner.val.shp, e.inner.val))
}

func (s *Compound) Type() int {
	return int(C.topo_shape_type(s.inner.val.shp))
}

func (s *Compound) BBox() BBox {
	return BBox{val: C.topo_shape_bounding_box(s.inner.val.shp)}
}

func (s *Compound) Hash() int {
	return int(C.topo_shape_hash_code(s.inner.val.shp))
}

func (s *Compound) Transform(t Trsf) int {
	return int(C.topo_shape_transform(s.inner.val.shp, t.val))
}

func (s *Compound) Translate(v Vector3) int {
	return int(C.topo_shape_translate(s.inner.val.shp, v.val))
}

func (s *Compound) RotateFromPoint(angle float64, p1, p2 Point3) int {
	return int(C.topo_shape_rotate_from_two_point(s.inner.val.shp, C.double(angle), p1.val, p2.val))
}

func (s *Compound) RotateFromAxis1(angle float64, a Axis1) int {
	return int(C.topo_shape_rotate_from_axis1(s.inner.val.shp, C.double(angle), a.val))
}

func (s *Compound) RotateFromQuaternion(q Quaternion) int {
	return int(C.topo_shape_rotate_from_quaternion(s.inner.val.shp, q.val))
}

func (s *Compound) Scale(angle float64, a Point3) int {
	return int(C.topo_shape_scale(s.inner.val.shp, C.double(angle), a.val))
}

func (s *Compound) MirrorFromPointNorm(pnt, ner Point3) int {
	return int(C.topo_shape_mirror_from_point_norm(s.inner.val.shp, pnt.val, ner.val))
}

func (s *Compound) MirrorFromAxis1(a Axis1) int {
	return int(C.topo_shape_mirror_from_axis1(s.inner.val.shp, a.val))
}

func (s *Compound) MirrorFromAxis2(a Axis2) int {
	return int(C.topo_shape_mirror_from_axis2(s.inner.val.shp, a.val))
}

func (s *Compound) Transformed(t Trsf) *Compound {
	var val C.struct__topo_compound_t
	val.shp = C.topo_shape_transformed(s.inner.val.shp, t.val)
	return &Compound{inner: &innerCompound{val: val}}
}

func (s *Compound) Translated(v Vector3) *Compound {
	var val C.struct__topo_compound_t
	val.shp = C.topo_shape_translated(s.inner.val.shp, v.val)
	return &Compound{inner: &innerCompound{val: val}}
}

func (s *Compound) RotatedFromPoint(angle float64, p1, p2 Point3) *Compound {
	var val C.struct__topo_compound_t
	val.shp = C.topo_shape_rotated_from_two_point(s.inner.val.shp, C.double(angle), p1.val, p2.val)
	return &Compound{inner: &innerCompound{val: val}}
}

func (s *Compound) RotatedFromAxis1(angle float64, a Axis1) *Compound {
	var val C.struct__topo_compound_t
	val.shp = C.topo_shape_rotated_from_axis1(s.inner.val.shp, C.double(angle), a.val)
	return &Compound{inner: &innerCompound{val: val}}
}

func (s *Compound) RotatedFromQuaternion(q Quaternion) *Compound {
	var val C.struct__topo_compound_t
	val.shp = C.topo_shape_rotated_from_quaternion(s.inner.val.shp, q.val)
	return &Compound{inner: &innerCompound{val: val}}
}

func (s *Compound) Scaled(angle float64, a Point3) *Compound {
	var val C.struct__topo_compound_t
	val.shp = C.topo_shape_scaled(s.inner.val.shp, C.double(angle), a.val)
	return &Compound{inner: &innerCompound{val: val}}
}

func (s *Compound) MirroredFromPointNorm(pnt, ner Point3) *Compound {
	var val C.struct__topo_compound_t
	val.shp = C.topo_shape_mirrored_from_point_norm(s.inner.val.shp, pnt.val, ner.val)
	return &Compound{inner: &innerCompound{val: val}}
}

func (s *Compound) MirroredFromAxis1(a Axis1) *Compound {
	var val C.struct__topo_compound_t
	val.shp = C.topo_shape_mirrored_from_axis1(s.inner.val.shp, a.val)
	return &Compound{inner: &innerCompound{val: val}}
}

func (s *Compound) MirroredFromAxis2(a Axis2) *Compound {
	var val C.struct__topo_compound_t
	val.shp = C.topo_shape_mirrored_from_axis2(s.inner.val.shp, a.val)
	return &Compound{inner: &innerCompound{val: val}}
}

func (s *Compound) GetOrientation() int {
	return int(C.topo_shape_get_orientation(s.inner.val.shp))
}

func (s *Compound) SetOrientation(t int) {
	C.topo_shape_set_orientation(s.inner.val.shp, C.int(t))
}

func (s *Compound) GetLocation() *TopoLocation {
	p := &TopoLocation{inner: &innerTopoLocation{val: C.topo_shape_get_location(s.inner.val.shp)}}
	runtime.SetFinalizer(p.inner, (*innerTopoLocation).free)
	return p
}

func (s *Compound) SetLocation(t *TopoLocation) {
	C.topo_shape_set_location(s.inner.val.shp, t.inner.val)
}

func (s *Compound) FixShape() bool {
	return bool(C.topo_shape_fix_shape(s.inner.val.shp))
}

func (s *Compound) Copy() *Compound {
	var val C.struct__topo_compound_t
	val.shp = C.topo_shape_copy(s.inner.val.shp)
	return &Compound{inner: &innerCompound{val: val}}
}

func (s *Compound) Mesh(m *MeshReceiver, tolerance, deflection, angle float64) {
	C.topo_shape_mesh(s.inner.val.shp, m.inner.val, C.double(tolerance), C.double(deflection), C.double(angle), C.bool(false))
}

func (s *Compound) MeshWithTexture(m *MeshReceiver, tolerance, deflection, angle float64) {
	m.hasTexCoords = true
	C.topo_shape_mesh(s.inner.val.shp, m.inner.val, C.double(tolerance), C.double(deflection), C.double(angle), C.bool(true))
}

func (s *Compound) SetSurfaceColour(c Color) {
	C.topo_shape_set_surface_colour(s.inner.val.shp, c.val)
}

func (s *Compound) SetCurveColour(c Color) {
	C.topo_shape_set_curve_colour(s.inner.val.shp, c.val)
}

func (s *Compound) SetLabel(l string) {
	str := C.CString(l)
	defer C.free(unsafe.Pointer(str))
	C.topo_shape_set_label(s.inner.val.shp, str)
}

func (s *Compound) SetUVOrigin(u, v float64) {
	C.topo_shape_set_u_origin(s.inner.val.shp, C.double(u))
	C.topo_shape_set_v_origin(s.inner.val.shp, C.double(v))
}

func (s *Compound) SetUVRepeat(u, v float64) {
	C.topo_shape_set_u_repeat(s.inner.val.shp, C.double(u))
	C.topo_shape_set_v_repeat(s.inner.val.shp, C.double(v))
}

func (s *Compound) SetScaleU(u float64) {
	C.topo_shape_set_scale_u(s.inner.val.shp, C.double(u))
}

func (s *Compound) SetScaleV(v float64) {
	C.topo_shape_set_scale_v(s.inner.val.shp, C.double(v))
}

func (s *Compound) SetAutoScaleSizeOnU(u float64) {
	C.topo_shape_set_auto_scale_size_on_u(s.inner.val.shp, C.double(u))
}

func (s *Compound) SetAutoScaleSizeOnV(v float64) {
	C.topo_shape_set_auto_scale_size_on_v(s.inner.val.shp, C.double(v))
}

func (s *Compound) SetTextureMapType(t int) {
	C.topo_shape_set_txture_map_type(s.inner.val.shp, C.int(t))
}

func (s *Compound) SetRotationAngle(a float64) {
	C.topo_shape_set_rotation_angle(s.inner.val.shp, C.double(a))
}

func (s *Compound) GetSurfaceColour() Color {
	return Color{val: C.topo_shape_get_surface_colour(s.inner.val.shp)}
}

func (s *Compound) GetCurveColour() Color {
	return Color{val: C.topo_shape_get_surface_colour(s.inner.val.shp)}
}

func (s *Compound) GetLabel() string {
	return C.GoString(C.topo_shape_get_label(s.inner.val.shp))
}

func (s *Compound) GetUVOrigin() (u, v float64) {
	u = float64(C.topo_shape_get_u_origin(s.inner.val.shp))
	v = float64(C.topo_shape_get_v_origin(s.inner.val.shp))
	return
}

func (s *Compound) GetUVRepeat() (u, v float64) {
	u = float64(C.topo_shape_get_u_repeat(s.inner.val.shp))
	v = float64(C.topo_shape_get_v_repeat(s.inner.val.shp))
	return
}

func (s *Compound) GetUVScale() (u, v float64) {
	u = float64(C.topo_shape_get_scale_u(s.inner.val.shp))
	v = float64(C.topo_shape_get_scale_v(s.inner.val.shp))
	return
}

func (s *Compound) GetUVAutoScaleSize() (u, v float64) {
	u = float64(C.topo_shape_get_auto_scale_size_on_u(s.inner.val.shp))
	v = float64(C.topo_shape_get_auto_scale_size_on_v(s.inner.val.shp))
	return
}

func (s *Compound) GetTxtureMapType() int {
	return int(C.topo_shape_get_txture_map_type(s.inner.val.shp))
}

func (s *Compound) GetRotationAngle() float64 {
	return float64(C.topo_shape_get_rotation_angle(s.inner.val.shp))
}

func (t *innerCompound) free() {
	C.topo_compound_free(t.val)
}

func (t *Compound) solid() C.struct__topo_solid_t {
	var val C.struct__topo_solid_t
	val.shp = t.inner.val.shp
	return val
}

func (s *Compound) IsInside(p Point3, tol float64) bool {
	return bool(C.topo_solid_is_inside(s.solid(), p.val, C.double(tol)))
}

func (t *Compound) ToShape() *Shape {
	sp := &Shape{inner: &innerShape{val: C.topo_shape_share(t.inner.val.shp)}}
	runtime.SetFinalizer(sp.inner, (*innerShape).free)
	return sp
}

func (t *Compound) ToSolid() *Solid {
	var val C.struct__topo_solid_t
	val.shp = C.topo_shape_share(t.inner.val.shp)
	sld := &Solid{inner: &innerSolid{val: val}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func (s *Compound) NumSolids() int {
	return int(C.topo_solid_num_solids(s.solid()))
}

func (s *Compound) NumFaces() int {
	return int(C.topo_solid_num_faces(s.solid()))
}

func (s *Compound) Area() float64 {
	return float64(C.topo_solid_area(s.solid()))
}

func (s *Compound) Volume() float64 {
	return float64(C.topo_solid_volume(s.solid()))
}

func (s *Compound) Remove(shp *Shape) {
	C.topo_compound_remove(s.inner.val, shp.inner.val)
}

func (s *Compound) Inertia() BBox {
	return BBox{val: C.topo_solid_inertia(s.solid())}
}

func (s *Compound) CentreOfMass() Point3 {
	return Point3{val: C.topo_solid_centre_of_mass(s.solid())}
}

func (s *Compound) Extrude(f *Face, p1, p2 Point3) int {
	return int(C.topo_solid_extrude(s.solid(), f.inner.val, p1.val, p2.val))
}

func (s *Compound) ExtrudeFromDir(f *Face, d Vector3) int {
	return int(C.topo_solid_extrude_from_dir(s.solid(), f.inner.val, d.val))
}

func (s *Compound) ExtrudeWithRotationFromWire(outerWire *Wire, innerWires []*Wire, vecCenter Point3, vecNormal Vector3, angleDegrees float64) int {
	innerCount := len(innerWires)
	cWires := C.malloc(C.size_t(innerCount) * C.size_t(unsafe.Sizeof(C.struct__topo_wire_t{})))
	defer C.free(cWires)
	wiresSlice := (*[1<<30 - 1]C.struct__topo_wire_t)(cWires)[:innerCount:innerCount]
	for i, w := range innerWires {
		wiresSlice[i] = w.inner.val
	}

	return int(C.topo_solid_extrude_with_rotation_from_wire(
		s.solid(), outerWire.inner.val, (*C.struct__topo_wire_t)(cWires), C.int(innerCount),
		vecCenter.val, vecNormal.val, C.double(angleDegrees)))
}

func (s *Compound) ExtrudeWithRotationFromFace(face *Face, vecCenter Point3, vecNormal Vector3, angleDegrees float64) int {
	return int(C.topo_solid_extrude_with_rotation_from_face(
		s.solid(), face.inner.val, vecCenter.val, vecNormal.val,
		C.double(angleDegrees)))
}

func (s *Compound) SweepWire(spine *Wire, profiles []*Wire, cornerMode int) int {
	count := len(profiles)
	cProfiles := C.malloc(C.size_t(count) * C.size_t(unsafe.Sizeof(C.struct__topo_wire_t{})))
	defer C.free(cProfiles)
	profilesSlice := (*[1<<30 - 1]C.struct__topo_wire_t)(cProfiles)[:count:count]
	for i, w := range profiles {
		profilesSlice[i] = w.inner.val
	}

	return int(C.topo_solid_sweep_wire(
		s.solid(), spine.inner.val, (*C.struct__topo_wire_t)(cProfiles), C.int(count), C.int(cornerMode)))
}

func (s *Compound) SweepMultiFromVector(profiles []*Shape, path *Shape, makeSolid, isFrenet bool, vec *TopoVector) int {
	count := len(profiles)
	cProfiles := C.malloc(C.size_t(count) * C.size_t(unsafe.Sizeof(uintptr(0))))
	defer C.free(cProfiles)
	profilesSlice := (*[1<<30 - 1]*C.struct__topo_shape_t)(cProfiles)[:count:count]
	for i, p := range profiles {
		profilesSlice[i] = p.inner.val
	}

	return int(C.topo_solid_sweep_multi_from_vector(
		s.solid(), (**C.struct__topo_shape_t)(cProfiles), C.int(count), path.inner.val,
		C.bool(makeSolid), C.bool(isFrenet), vec.inner.val))
}

func (s *Compound) SweepMultiFromWire(profiles []*Shape, path *Shape, makeSolid, isFrenet bool, wire *Wire) int {
	count := len(profiles)
	cProfiles := C.malloc(C.size_t(count) * C.size_t(unsafe.Sizeof(uintptr(0))))
	defer C.free(cProfiles)
	profilesSlice := (*[1<<30 - 1]*C.struct__topo_shape_t)(cProfiles)[:count:count]

	for i, p := range profiles {
		profilesSlice[i] = p.inner.val
	}

	return int(C.topo_solid_sweep_multi_from_wire(
		s.solid(), (**C.struct__topo_shape_t)(cProfiles), C.int(count), path.inner.val,
		C.bool(makeSolid), C.bool(isFrenet), &wire.inner.val))
}

func (s *Compound) SweepMultiFromEdge(profiles []*Shape, path *Shape, makeSolid, isFrenet bool, edge *Edge) int {
	count := len(profiles)
	cProfiles := C.malloc(C.size_t(count) * C.size_t(unsafe.Sizeof(uintptr(0))))
	defer C.free(cProfiles)
	profilesSlice := (*[1<<30 - 1]*C.struct__topo_shape_t)(cProfiles)[:count:count]

	for i, p := range profiles {
		profilesSlice[i] = p.inner.val
	}

	return int(C.topo_solid_sweep_multi_from_edge(
		s.solid(), (**C.struct__topo_shape_t)(cProfiles), C.int(count), path.inner.val,
		C.bool(makeSolid), C.bool(isFrenet), &edge.inner.val))
}

func (s *Compound) Revolve(f *Face, p1, p2 Point3, angle float64) int {
	return int(C.topo_solid_revolve(s.solid(), f.inner.val, p1.val, p2.val, C.double(angle)))
}

func (s *Compound) Loft(profiles []Shape, ruled bool, tolerance float64) int {
	cshp := C.malloc(C.size_t(len(profiles)) * C.size_t(unsafe.Sizeof(uintptr(0))))
	defer C.free(cshp)
	cshpSlice := (*[1<<30 - 1]*C.struct__topo_shape_t)(cshp)[:len(profiles):len(profiles)]

	for i := range profiles {
		cshpSlice[i] = profiles[i].inner.val
	}
	return int(C.topo_solid_loft(s.solid(), (**C.struct__topo_shape_t)(cshp), C.int(len(profiles)), C.bool(ruled), C.double(tolerance)))
}

func (s *Compound) Pipe(f *Face, w Wire) int {
	return int(C.topo_solid_pipe(s.solid(), f.inner.val, w.inner.val))
}

func (s *Compound) Sweep(spine *Wire, profiles []Shape, cornerMode int) int {
	cshp := C.malloc(C.size_t(len(profiles)) * C.size_t(unsafe.Sizeof(uintptr(0))))
	defer C.free(cshp)
	cshpSlice := (*[1<<30 - 1]*C.struct__topo_shape_t)(cshp)[:len(profiles):len(profiles)]
	for i := range profiles {
		cshpSlice[i] = profiles[i].inner.val
	}
	return int(C.topo_solid_sweep(s.solid(), spine.inner.val, (**C.struct__topo_shape_t)(cshp), C.int(len(profiles)), C.int(cornerMode)))
}

func (s *Compound) Boolean(tool *Solid, op int) int {
	return int(C.topo_solid_boolean(s.solid(), tool.inner.val, C.int(op)))
}

func (s *Compound) Fillet(edges []Edge, radius []float64) int {
	cshp := C.malloc(C.size_t(len(edges)) * C.size_t(unsafe.Sizeof(C.struct__topo_edge_t{})))
	defer C.free(cshp)
	cshpSlice := (*[1<<30 - 1]C.struct__topo_edge_t)(cshp)[:len(edges):len(edges)]
	for i := range edges {
		cshpSlice[i] = edges[i].inner.val
	}
	return int(C.topo_solid_fillet(s.solid(), (*C.struct__topo_edge_t)(cshp), C.int(len(edges)), (*C.double)(unsafe.Pointer(&radius[0])), C.int(len(radius))))
}

func (s *Compound) Chamfer(edges []Edge, distances []float64) int {
	cshp := C.malloc(C.size_t(len(edges)) * C.size_t(unsafe.Sizeof(C.struct__topo_edge_t{})))
	defer C.free(cshp)
	cshpSlice := (*[1<<30 - 1]C.struct__topo_edge_t)(cshp)[:len(edges):len(edges)]
	for i := range edges {
		cshpSlice[i] = edges[i].inner.val
	}
	return int(C.topo_solid_chamfer(s.solid(), (*C.struct__topo_edge_t)(cshp), C.int(len(edges)), (*C.double)(unsafe.Pointer(&distances[0])), C.int(len(distances))))
}

func (s *Compound) Shelling(faces []Face, offset, tolerance float64) int {
	cshp := C.malloc(C.size_t(len(faces)) * C.size_t(unsafe.Sizeof(C.struct__topo_face_t{})))
	defer C.free(cshp)
	cshpSlice := (*[1<<30 - 1]C.struct__topo_face_t)(cshp)[:len(faces):len(faces)]
	for i := range faces {
		cshpSlice[i] = faces[i].inner.val
	}
	return int(C.topo_solid_shelling(s.solid(), (*C.struct__topo_face_t)(cshp), C.int(len(faces)), C.double(offset), C.double(tolerance)))
}

func (s *Compound) Offset(f *Face, offset, tolerance float64) int {
	return int(C.topo_solid_offset(s.solid(), f.inner.val, C.double(offset), C.double(tolerance)))
}

func (s *Compound) Draft(faces []Face, d Dir3, angle float64, p Plane) int {
	cshp := C.malloc(C.size_t(len(faces)) * C.size_t(unsafe.Sizeof(C.struct__topo_face_t{})))
	defer C.free(cshp)
	cshpSlice := (*[1<<30 - 1]C.struct__topo_face_t)(cshp)[:len(faces):len(faces)]
	for i := range faces {
		cshpSlice[i] = faces[i].inner.val
	}
	return int(C.topo_solid_draft(s.solid(), (*C.struct__topo_face_t)(cshp), C.int(len(faces)), d.val, C.double(angle), p.val))
}

func (s *Compound) EvolvedFromFace(Spine *Face, Profil *Wire) int {
	return int(C.topo_solid_evolved_from_face(s.solid(), Spine.inner.val, Profil.inner.val))
}

func (s *Compound) EvolvedFromWire(Spine *Wire, Profil *Wire) int {
	return int(C.topo_solid_evolved_from_wire(s.solid(), Spine.inner.val, Profil.inner.val))
}

func (s *Compound) FeatPrism(f *Face, d Dir3, height float64, fuse bool) int {
	return int(C.topo_solid_feat_prism(s.solid(), f.inner.val, d.val, C.double(height), C.bool(fuse)))
}

func (s *Compound) FeatPrismForRange(f *Face, d Dir3, from, end Face, fuse bool) int {
	return int(C.topo_solid_feat_prism_for_range(s.solid(), f.inner.val, d.val, from.inner.val, end.inner.val, C.bool(fuse)))
}

func (s *Compound) FeatPrismForUntil(f *Face, d Dir3, until Face, fuse bool) int {
	return int(C.topo_solid_feat_prism_for_until(s.solid(), f.inner.val, d.val, until.inner.val, C.bool(fuse)))
}

func (s *Compound) DraftPrism(f *Face, angle, height float64, fuse bool) int {
	return int(C.topo_solid_feat_draft_prism(s.solid(), f.inner.val, C.double(angle), C.double(height), C.bool(fuse)))
}

func (s *Compound) DraftPrismForRange(f *Face, angle float64, from, end Face, fuse bool) int {
	return int(C.topo_solid_feat_draft_prism_for_range(s.solid(), f.inner.val, C.double(angle), from.inner.val, end.inner.val, C.bool(fuse)))
}

func (s *Compound) DraftPrismForUntil(f *Face, angle float64, until Face, fuse bool) int {
	return int(C.topo_solid_feat_draft_prism_for_until(s.solid(), f.inner.val, C.double(angle), until.inner.val, C.bool(fuse)))
}

func (s *Compound) RevolForRange(f *Face, a Axis1, from, end Face, fuse bool) int {
	return int(C.topo_solid_feat_revol_for_range(s.solid(), f.inner.val, a.val, from.inner.val, end.inner.val, C.bool(fuse)))
}

func (s *Compound) RevolForUntil(f *Face, a Axis1, until Face, fuse bool) int {
	return int(C.topo_solid_feat_revol_for_until(s.solid(), f.inner.val, a.val, until.inner.val, C.bool(fuse)))
}

func (s *Compound) PipeForRange(f *Face, w *Wire, from, end Face, fuse bool) int {
	return int(C.topo_solid_feat_pipe_for_range(s.solid(), f.inner.val, w.inner.val, from.inner.val, end.inner.val, C.bool(fuse)))
}

func (s *Compound) PipeForUntil(f *Face, w *Wire, until Face, fuse bool) int {
	return int(C.topo_solid_feat_pipe_for_until(s.solid(), f.inner.val, w.inner.val, until.inner.val, C.bool(fuse)))
}

func (s *Compound) LinearForm(w *Wire, p *GeomPlane, d, d1 Dir3, fuse bool) int {
	return int(C.topo_solid_linear_form(s.solid(), w.inner.val, p.inner.geom, d.val, d1.val, C.bool(fuse)))
}

func (s *Compound) RevolutionForm(w *Wire, p *GeomPlane, a Axis1, h1, h2 float64, fuse bool) int {
	return int(C.topo_solid_revolution_form(s.solid(), w.inner.val, p.inner.geom, a.val, C.double(h1), C.double(h2), C.bool(fuse)))
}

func (s *Compound) SectionFace(pnt, nor Point3) *Face {
	p := &Face{inner: &innerFace{val: C.topo_solid_section_face(s.solid(), pnt.val, nor.val)}}
	runtime.SetFinalizer(p.inner, (*innerFace).free)
	return p
}

func (s *Compound) SectionWire(pnt, nor Point3) *Wire {
	p := &Wire{inner: &innerWire{val: C.topo_solid_section_wire(s.solid(), pnt.val, nor.val)}}
	runtime.SetFinalizer(p.inner, (*innerWire).free)
	return p
}

func (c *Compound) Cut(toCut []*Shape, tol float64) *Compound {
	count := len(toCut)
	cShapes := C.malloc(C.size_t(count) * C.size_t(unsafe.Sizeof(uintptr(0))))
	defer C.free(cShapes)
	cShapesSlice := (*[1<<30 - 1]*C.struct__topo_shape_t)(cShapes)[:count:count]
	for i, s := range toCut {
		cShapesSlice[i] = s.inner.val
	}

	p := &Compound{inner: &innerCompound{val: C.topo_compound_cut(
		c.inner.val, (**C.struct__topo_shape_t)(cShapes), C.int(count), C.double(tol))}}
	runtime.SetFinalizer(p.inner, (*innerCompound).free)
	return p
}

func (c *Compound) Fuse(toFuse []*Shape, glue bool, tol float64) *Compound {
	count := len(toFuse)
	cShapes := C.malloc(C.size_t(count) * C.size_t(unsafe.Sizeof(uintptr(0))))
	defer C.free(cShapes)
	cShapesSlice := (*[1<<30 - 1]*C.struct__topo_shape_t)(cShapes)[:count:count]
	for i, s := range toFuse {
		cShapesSlice[i] = s.inner.val
	}

	p := &Compound{inner: &innerCompound{val: C.topo_compound_fuse(
		c.inner.val, (**C.struct__topo_shape_t)(cShapes), C.int(count), C.bool(glue), C.double(tol))}}
	runtime.SetFinalizer(p.inner, (*innerCompound).free)
	return p
}

func (c *Compound) Intersect(toIntersect []*Shape, tol float64) *Compound {
	count := len(toIntersect)
	cShapes := C.malloc(C.size_t(count) * C.size_t(unsafe.Sizeof(uintptr(0))))
	defer C.free(cShapes)
	cShapesSlice := (*[1<<30 - 1]*C.struct__topo_shape_t)(cShapes)[:count:count]
	for i, s := range toIntersect {
		cShapesSlice[i] = s.inner.val
	}

	p := &Compound{inner: &innerCompound{val: C.topo_compound_intersect(
		c.inner.val, (**C.struct__topo_shape_t)(cShapes), C.int(count), C.double(tol))}}
	runtime.SetFinalizer(p.inner, (*innerCompound).free)
	return p
}

func (c *Compound) Ancestors(s *Shape, kind int) *Compound {
	p := &Compound{inner: &innerCompound{val: C.topo_compound_ancestors(
		c.inner.val, s.inner.val, C.int(kind))}}
	runtime.SetFinalizer(p.inner, (*innerCompound).free)
	return p
}

func (c *Compound) Siblings(shape *Shape, kind int, level int) *Compound {
	p := &Compound{inner: &innerCompound{val: C.topo_compound_siblings(
		c.inner.val, shape.inner.val, C.int(kind), C.int(level))}}
	runtime.SetFinalizer(p.inner, (*innerCompound).free)
	return p
}

func (s *Compound) ConvertToNurbs() int {
	return int(C.topo_solid_convert_to_nurbs(s.solid()))
}

func TopoCompoundMake(s []Shape) *Compound {
	sos := make([]*C.struct__topo_shape_t, len(s))
	for i := range s {
		sos[i] = s[i].inner.val
	}
	return &Compound{inner: &innerCompound{val: C.topo_compound_make_compound(&sos[0], C.int(len(s)))}}
}

func TopoCompoundMakeText(text string, size float64, font, fontPath string, kind, halign, valign int, position *TopoPlane) *Compound {
	cText := C.CString(text)
	defer C.free(unsafe.Pointer(cText))

	var cFont *C.char
	if font != "" {
		cFont = C.CString(font)
		defer C.free(unsafe.Pointer(cFont))
	}

	var cFontPath *C.char
	if fontPath != "" {
		cFontPath = C.CString(fontPath)
		defer C.free(unsafe.Pointer(cFontPath))
	}
	c := &Compound{inner: &innerCompound{val: C.topo_make_text(
		cText, C.double(size), cFont, cFontPath, C.int(kind),
		C.int(halign), C.int(valign), position.inner.val)}}
	runtime.SetFinalizer(c.inner, (*innerCompound).free)
	return c
}

func TopoCompoundMakeTextWithSpine(text string, size float64, spine *Wire, planar bool, font, path string, kind, halign, valign int) *Compound {
	cText := C.CString(text)
	defer C.free(unsafe.Pointer(cText))

	var cFont *C.char
	if font != "" {
		cFont = C.CString(font)
		defer C.free(unsafe.Pointer(cFont))
	}

	var cPath *C.char
	if path != "" {
		cPath = C.CString(path)
		defer C.free(unsafe.Pointer(cPath))
	}

	var cSpine *C.struct__topo_wire_t
	if spine != nil {
		cSpine = &spine.inner.val
	}

	c := &Compound{inner: &innerCompound{val: C.topo_make_text_with_spine(
		cText, C.double(size), cSpine, C.bool(planar), cFont, cPath,
		C.int(kind), C.int(halign), C.int(valign))}}
	runtime.SetFinalizer(c.inner, (*innerCompound).free)
	return c
}

func TopoCompoundMakeTextWithSpineAndBase(text string, size float64, spine *Wire, base *Face, font, path string, kind, halign, valign int) *Compound {
	cText := C.CString(text)
	defer C.free(unsafe.Pointer(cText))

	var cFont *C.char
	if font != "" {
		cFont = C.CString(font)
		defer C.free(unsafe.Pointer(cFont))
	}

	var cPath *C.char
	if path != "" {
		cPath = C.CString(path)
		defer C.free(unsafe.Pointer(cPath))
	}

	var cSpine *C.struct__topo_wire_t
	if spine != nil {
		cSpine = &spine.inner.val
	}

	var cBase *C.struct__topo_face_t
	if base != nil {
		cBase = &base.inner.val
	}

	c := &Compound{inner: &innerCompound{val: C.topo_make_text_with_spine_and_base(
		cText, C.double(size), cSpine, cBase, cFont, cPath,
		C.int(kind), C.int(halign), C.int(valign))}}
	runtime.SetFinalizer(c.inner, (*innerCompound).free)
	return c
}

func TopoCompoundMakeTextWithHeight(text string, size, height float64, font, fontPath string, kind, halign, valign int, position *TopoPlane) *Compound {
	cText := C.CString(text)
	defer C.free(unsafe.Pointer(cText))

	var cFont *C.char
	if font != "" {
		cFont = C.CString(font)
		defer C.free(unsafe.Pointer(cFont))
	}

	var cFontPath *C.char
	if fontPath != "" {
		cFontPath = C.CString(fontPath)
		defer C.free(unsafe.Pointer(cFontPath))
	}

	c := &Compound{inner: &innerCompound{val: C.topo_make_text_with_height(
		cText, C.double(size), C.double(height), cFont, cFontPath,
		C.int(kind), C.int(halign), C.int(valign), position.inner.val)}}
	runtime.SetFinalizer(c.inner, (*innerCompound).free)
	return c
}

type CompoundIterator struct {
	inner *innerCompoundIterator
}
type innerCompoundIterator struct {
	val *C.struct__topo_compound_iterator_t
}

func TopoMakeCompoundIterator(p Shape) *CompoundIterator {
	wr := &CompoundIterator{inner: &innerCompoundIterator{val: C.topo_compound_iterator_make(p.inner.val)}}
	runtime.SetFinalizer(wr.inner, (*innerCompoundIterator).free)
	return wr
}

func (t *innerCompoundIterator) free() {
	C.topo_compound_iterator_free(t.val)
}

func (t *CompoundIterator) Next() *Compound {
	v := C.topo_compound_iterator_next(t.inner.val)
	if v != nil {
		var val C.struct__topo_compound_t
		val.shp = v
		p := &Compound{inner: &innerCompound{val: val}}
		runtime.SetFinalizer(p.inner, (*innerCompound).free)
		return p
	}
	return nil
}
