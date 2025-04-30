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

type Solid struct {
	inner *innerSolid
}

type innerSolid struct {
	val C.struct__topo_solid_t
}

func TopoMakeSolid() *Solid {
	p := &Solid{inner: &innerSolid{val: C.topo_make_solid()}}
	runtime.SetFinalizer(p.inner, (*innerSolid).free)
	return p
}

func (s *Solid) IsNull() bool {
	return bool(C.topo_shape_is_null(s.inner.val.shp))
}

func (s *Solid) IsValid() bool {
	return bool(C.topo_shape_is_valid(s.inner.val.shp))
}

func (s *Solid) Equals(e *Shape) bool {
	return bool(C.topo_shape_equals(s.inner.val.shp, e.inner.val))
}

func (s *Solid) Type() int {
	return int(C.topo_shape_type(s.inner.val.shp))
}

func (s *Solid) BBox() BBox {
	return BBox{val: C.topo_shape_bounding_box(s.inner.val.shp)}
}

func (s *Solid) Hash() int {
	return int(C.topo_shape_hash_code(s.inner.val.shp))
}

func (s *Solid) Transform(t Trsf) int {
	return int(C.topo_shape_transform(s.inner.val.shp, t.val))
}

func (s *Solid) Translate(v Vector3) int {
	return int(C.topo_shape_translate(s.inner.val.shp, v.val))
}

func (s *Solid) RotateFromPoint(angle float64, p1, p2 Point3) int {
	return int(C.topo_shape_rotate_from_two_point(s.inner.val.shp, C.double(angle), p1.val, p2.val))
}

func (s *Solid) RotateFromAxis1(angle float64, a Axis1) int {
	return int(C.topo_shape_rotate_from_axis1(s.inner.val.shp, C.double(angle), a.val))
}

func (s *Solid) RotateFromQuaternion(q Quaternion) int {
	return int(C.topo_shape_rotate_from_quaternion(s.inner.val.shp, q.val))
}

func (s *Solid) Scale(angle float64, a Point3) int {
	return int(C.topo_shape_scale(s.inner.val.shp, C.double(angle), a.val))
}

func (s *Solid) MirrorFromPointNorm(pnt, ner Point3) int {
	return int(C.topo_shape_mirror_from_point_norm(s.inner.val.shp, pnt.val, ner.val))
}

func (s *Solid) MirrorFromAxis1(a Axis1) int {
	return int(C.topo_shape_mirror_from_axis1(s.inner.val.shp, a.val))
}

func (s *Solid) MirrorFromAxis2(a Axis2) int {
	return int(C.topo_shape_mirror_from_axis2(s.inner.val.shp, a.val))
}

func (s *Solid) Transformed(t Trsf) *Solid {
	var val C.struct__topo_solid_t
	val.shp = C.topo_shape_transformed(s.inner.val.shp, t.val)
	sld := &Solid{inner: &innerSolid{val: val}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func (s *Solid) Translated(v Vector3) *Solid {
	var val C.struct__topo_solid_t
	val.shp = C.topo_shape_translated(s.inner.val.shp, v.val)
	sld := &Solid{inner: &innerSolid{val: val}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func (s *Solid) RotatedFromPoint(angle float64, p1, p2 Point3) *Solid {
	var val C.struct__topo_solid_t
	val.shp = C.topo_shape_rotated_from_two_point(s.inner.val.shp, C.double(angle), p1.val, p2.val)
	sld := &Solid{inner: &innerSolid{val: val}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func (s *Solid) RotatedFromAxis1(angle float64, a Axis1) *Solid {
	var val C.struct__topo_solid_t
	val.shp = C.topo_shape_rotated_from_axis1(s.inner.val.shp, C.double(angle), a.val)
	sld := &Solid{inner: &innerSolid{val: val}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func (s *Solid) RotatedFromQuaternion(q Quaternion) *Solid {
	var val C.struct__topo_solid_t
	val.shp = C.topo_shape_rotated_from_quaternion(s.inner.val.shp, q.val)
	sld := &Solid{inner: &innerSolid{val: val}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func (s *Solid) Scaled(angle float64, a Point3) *Solid {
	var val C.struct__topo_solid_t
	val.shp = C.topo_shape_scaled(s.inner.val.shp, C.double(angle), a.val)
	sld := &Solid{inner: &innerSolid{val: val}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func (s *Solid) MirroredFromPointNorm(pnt, ner Point3) *Solid {
	var val C.struct__topo_solid_t
	val.shp = C.topo_shape_mirrored_from_point_norm(s.inner.val.shp, pnt.val, ner.val)
	sld := &Solid{inner: &innerSolid{val: val}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func (s *Solid) MirroredFromAxis1(a Axis1) *Solid {
	var val C.struct__topo_solid_t
	val.shp = C.topo_shape_mirrored_from_axis1(s.inner.val.shp, a.val)
	sld := &Solid{inner: &innerSolid{val: val}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func (s *Solid) MirroredFromAxis2(a Axis2) *Solid {
	var val C.struct__topo_solid_t
	val.shp = C.topo_shape_mirrored_from_axis2(s.inner.val.shp, a.val)
	sld := &Solid{inner: &innerSolid{val: val}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func (s *Solid) GetOrientation() int {
	return int(C.topo_shape_get_orientation(s.inner.val.shp))
}

func (s *Solid) SetOrientation(t int) {
	C.topo_shape_set_orientation(s.inner.val.shp, C.int(t))
}

func (s *Solid) GetLocation() *TopoLocation {
	p := &TopoLocation{inner: &innerTopoLocation{val: C.topo_shape_get_location(s.inner.val.shp)}}
	runtime.SetFinalizer(p.inner, (*innerTopoLocation).free)
	return p
}

func (s *Solid) SetLocation(t *TopoLocation) {
	C.topo_shape_set_location(s.inner.val.shp, t.inner.val)
}

func (s *Solid) FixShape() bool {
	return bool(C.topo_shape_fix_shape(s.inner.val.shp))
}

func (s *Solid) Copy() *Solid {
	var val C.struct__topo_solid_t
	val.shp = C.topo_shape_copy(s.inner.val.shp)
	sld := &Solid{inner: &innerSolid{val: val}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func (s *Solid) Mesh(m *MeshReceiver, tolerance, deflection, angle float64) {
	C.topo_shape_mesh(s.inner.val.shp, m.inner.val, C.double(tolerance), C.double(deflection), C.double(angle), C.bool(false))
}

func (s *Solid) MeshWithTexture(m *MeshReceiver, tolerance, deflection, angle float64) {
	m.hasTexCoords = true
	C.topo_shape_mesh(s.inner.val.shp, m.inner.val, C.double(tolerance), C.double(deflection), C.double(angle), C.bool(true))
}

func (s *Solid) SetSurfaceColour(c Color) {
	C.topo_shape_set_surface_colour(s.inner.val.shp, c.val)
}

func (s *Solid) SetCurveColour(c Color) {
	C.topo_shape_set_curve_colour(s.inner.val.shp, c.val)
}

func (s *Solid) SetLabel(l string) {
	str := C.CString(l)
	defer C.free(unsafe.Pointer(str))
	C.topo_shape_set_label(s.inner.val.shp, str)
}

func (s *Solid) SetUVOrigin(u, v float64) {
	C.topo_shape_set_u_origin(s.inner.val.shp, C.double(u))
	C.topo_shape_set_v_origin(s.inner.val.shp, C.double(v))
}

func (s *Solid) SetUVRepeat(u, v float64) {
	C.topo_shape_set_u_repeat(s.inner.val.shp, C.double(u))
	C.topo_shape_set_v_repeat(s.inner.val.shp, C.double(v))
}

func (s *Solid) SetScaleU(u float64) {
	C.topo_shape_set_scale_u(s.inner.val.shp, C.double(u))
}

func (s *Solid) SetScaleV(v float64) {
	C.topo_shape_set_scale_v(s.inner.val.shp, C.double(v))
}

func (s *Solid) SetAutoScaleSizeOnU(u float64) {
	C.topo_shape_set_auto_scale_size_on_u(s.inner.val.shp, C.double(u))
}

func (s *Solid) SetAutoScaleSizeOnV(v float64) {
	C.topo_shape_set_auto_scale_size_on_v(s.inner.val.shp, C.double(v))
}

func (s *Solid) SetTextureMapType(t int) {
	C.topo_shape_set_txture_map_type(s.inner.val.shp, C.int(t))
}

func (s *Solid) SetRotationAngle(a float64) {
	C.topo_shape_set_rotation_angle(s.inner.val.shp, C.double(a))
}

func (s *Solid) GetSurfaceColour() Color {
	return Color{val: C.topo_shape_get_surface_colour(s.inner.val.shp)}
}

func (s *Solid) GetCurveColour() Color {
	return Color{val: C.topo_shape_get_surface_colour(s.inner.val.shp)}
}

func (s *Solid) GetLabel() string {
	return C.GoString(C.topo_shape_get_label(s.inner.val.shp))
}

func (s *Solid) GetUVOrigin() (u, v float64) {
	u = float64(C.topo_shape_get_u_origin(s.inner.val.shp))
	v = float64(C.topo_shape_get_v_origin(s.inner.val.shp))
	return
}

func (s *Solid) GetUVRepeat() (u, v float64) {
	u = float64(C.topo_shape_get_u_repeat(s.inner.val.shp))
	v = float64(C.topo_shape_get_v_repeat(s.inner.val.shp))
	return
}

func (s *Solid) GetUVScale() (u, v float64) {
	u = float64(C.topo_shape_get_scale_u(s.inner.val.shp))
	v = float64(C.topo_shape_get_scale_v(s.inner.val.shp))
	return
}

func (s *Solid) GetUVAutoScaleSize() (u, v float64) {
	u = float64(C.topo_shape_get_auto_scale_size_on_u(s.inner.val.shp))
	v = float64(C.topo_shape_get_auto_scale_size_on_v(s.inner.val.shp))
	return
}

func (s *Solid) GetTxtureMapType() int {
	return int(C.topo_shape_get_txture_map_type(s.inner.val.shp))
}

func (s *Solid) GetRotationAngle() float64 {
	return float64(C.topo_shape_get_rotation_angle(s.inner.val.shp))
}

func (s *Solid) IsInside(p Point3, tol float64) bool {
	return bool(C.topo_solid_is_inside(s.inner.val, p.val, C.double(tol)))
}

func (s *Solid) NumSolids() int {
	return int(C.topo_solid_num_solids(s.inner.val))
}

func (s *Solid) NumFaces() int {
	return int(C.topo_solid_num_faces(s.inner.val))
}

func (s *Solid) Area() float64 {
	return float64(C.topo_solid_area(s.inner.val))
}

func (s *Solid) Volume() float64 {
	return float64(C.topo_solid_volume(s.inner.val))
}

func (s *Solid) Inertia() BBox {
	return BBox{val: C.topo_solid_inertia(s.inner.val)}
}

func (s *Solid) CentreOfMass() Point3 {
	return Point3{val: C.topo_solid_centre_of_mass(s.inner.val)}
}

func (s *Solid) Extrude(f *Face, p1, p2 Point3) int {
	return int(C.topo_solid_extrude(s.inner.val, f.inner.val, p1.val, p2.val))
}

func (s *Solid) ExtrudeFromDir(f *Face, d Vector3) int {
	return int(C.topo_solid_extrude_from_dir(s.inner.val, f.inner.val, d.val))
}

func (s *Solid) OuterShell() *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_solid_outer_shell(s.inner.val)}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func (s *Solid) InnerShells() []*Shell {
	var count C.int
	cShells := C.topo_solid_inner_shells(s.inner.val, &count)
	ccShellsSlice := (*[1 << 30]C.struct__topo_shell_t)(unsafe.Pointer(cShells))[:count:count]
	shells := make([]*Shell, int(count))
	for i := 0; i < int(count); i++ {
		sh := &Shell{inner: &innerShell{val: ccShellsSlice[i]}}
		runtime.SetFinalizer(sh.inner, (*innerShell).free)
		shells[i] = sh
	}
	return shells
}

func (s *Solid) ExtrudeWithRotationFromWire(outerWire *Wire, innerWires []*Wire, vecCenter Point3, vecNormal Vector3, angleDegrees float64) int {
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
		s.inner.val, outerWire.inner.val, cWiresPtr, C.int(innerCount),
		vecCenter.val, vecNormal.val, C.double(angleDegrees)))
}

func (s *Solid) ExtrudeWithRotationFromFace(face *Face, vecCenter Point3, vecNormal Vector3, angleDegrees float64) int {
	return int(C.topo_solid_extrude_with_rotation_from_face(
		s.inner.val, face.inner.val, vecCenter.val, vecNormal.val,
		C.double(angleDegrees)))
}

func (s *Solid) SweepWire(spine *Wire, profiles []*Wire, cornerMode int) int {
	count := len(profiles)
	cProfiles := make([]C.struct__topo_wire_t, count)
	for i, w := range profiles {
		cProfiles[i] = w.inner.val
	}

	var cProfilesPtr *C.struct__topo_wire_t
	if count > 0 {
		cProfilesPtr = &cProfiles[0]
	}

	return int(C.topo_solid_sweep_wire(
		s.inner.val, spine.inner.val, cProfilesPtr, C.int(count), C.int(cornerMode)))
}

func (s *Solid) SweepMultiFromVector(profiles []*Shape, path *Shape, makeSolid, isFrenet bool, vec *TopoVector) int {
	count := len(profiles)
	cProfiles := make([]*C.struct__topo_shape_t, count)
	for i, p := range profiles {
		cProfiles[i] = p.inner.val
	}

	var cProfilesPtr **C.struct__topo_shape_t
	if count > 0 {
		cProfilesPtr = &cProfiles[0]
	}

	return int(C.topo_solid_sweep_multi_from_vector(
		s.inner.val, cProfilesPtr, C.int(count), path.inner.val,
		C.bool(makeSolid), C.bool(isFrenet), vec.inner.val))
}

func (s *Solid) SweepMultiFromWire(profiles []*Shape, path *Shape, makeSolid, isFrenet bool, wire *Wire) int {
	count := len(profiles)
	cProfiles := make([]*C.struct__topo_shape_t, count)
	for i, p := range profiles {
		cProfiles[i] = p.inner.val
	}

	var cProfilesPtr **C.struct__topo_shape_t
	if count > 0 {
		cProfilesPtr = &cProfiles[0]
	}

	return int(C.topo_solid_sweep_multi_from_wire(
		s.inner.val, cProfilesPtr, C.int(count), path.inner.val,
		C.bool(makeSolid), C.bool(isFrenet), &wire.inner.val))
}

func (s *Solid) SweepMultiFromEdge(profiles []*Shape, path *Shape, makeSolid, isFrenet bool, edge *Edge) int {
	count := len(profiles)
	cProfiles := make([]*C.struct__topo_shape_t, count)
	for i, p := range profiles {
		cProfiles[i] = p.inner.val
	}

	var cProfilesPtr **C.struct__topo_shape_t
	if count > 0 {
		cProfilesPtr = &cProfiles[0]
	}

	return int(C.topo_solid_sweep_multi_from_edge(
		s.inner.val, cProfilesPtr, C.int(count), path.inner.val,
		C.bool(makeSolid), C.bool(isFrenet), &edge.inner.val))
}

func (s *Solid) Revolve(f *Face, p1, p2 Point3, angle float64) int {
	return int(C.topo_solid_revolve(s.inner.val, f.inner.val, p1.val, p2.val, C.double(angle)))
}

func (s *Solid) Loft(profiles []Shape, ruled bool, tolerance float64) int {
	cshp := make([]*C.struct__topo_shape_t, len(profiles))
	for i := range profiles {
		cshp[i] = profiles[i].inner.val
	}
	return int(C.topo_solid_loft(s.inner.val, &cshp[0], C.int(len(profiles)), C.bool(ruled), C.double(tolerance)))
}

func (s *Solid) Pipe(f *Face, w Wire) int {
	return int(C.topo_solid_pipe(s.inner.val, f.inner.val, w.inner.val))
}

type SweepCurveType int

const (
	SweepCurveTypeLine            = SweepCurveType(C.CURVE_LINE)
	SweepCurveTypeThreePointArc   = SweepCurveType(C.CURVE_THREE_POINT_ARC)
	SweepCurveTypeCircleCenterArc = SweepCurveType(C.CURVE_CIRCLE_CENTER_ARC)
	SweepCurveTypeSpline          = SweepCurveType(C.CURVE_SPLINE)
)

// SweepProfile 扫掠剖面结构
type SweepProfile struct {
	Profile  Shape
	Location *Vertex
}

// SweepCompound 通过点集和剖面进行扫掠
func (s *Solid) SweepCompound(
	points [][]Point3,
	curveTypes []SweepCurveType,
	profiles []SweepProfile,
	cornerMode int,
) int {
	curveCount := len(points)
	profileCount := len(profiles)

	cPoints := make([]*C.pnt3d_t, curveCount)
	cPointCounts := make([]C.int, curveCount)
	for i, pts := range points {
		cPointCounts[i] = C.int(len(pts))
		cPoints[i] = (*C.pnt3d_t)(unsafe.Pointer(&pts[0].val))
	}

	cCurveTypes := make([]C.int, curveCount)
	for i, t := range curveTypes {
		cCurveTypes[i] = C.int(t)
	}

	cProfiles := make([]C.topo_sweep_profile_t, profileCount)
	for i, p := range profiles {
		cProfiles[i] = C.topo_sweep_profile_t{
			profile: p.Profile.inner.val,
		}

		if p.Location != nil {
			cProfiles[i].location = &p.Location.inner.val
		}
	}

	ret := C.topo_solid_sweep_compound(
		s.inner.val,
		(**C.pnt3d_t)(unsafe.Pointer(&cPoints[0])),
		(*C.int)(unsafe.Pointer(&cPointCounts[0])),
		C.int(curveCount),
		(*C.int)(unsafe.Pointer(&cCurveTypes[0])),
		(*C.topo_sweep_profile_t)(unsafe.Pointer(&cProfiles[0])),
		C.int(profileCount),
		C.int(cornerMode),
	)

	return int(ret)
}

func (s *Solid) Sweep(spine *Wire, profiles []Shape, cornerMode int) int {
	cshp := make([]*C.struct__topo_shape_t, len(profiles))
	for i := range profiles {
		cshp[i] = profiles[i].inner.val
	}
	return int(C.topo_solid_sweep(s.inner.val, spine.inner.val, &cshp[0], C.int(len(profiles)), C.int(cornerMode)))
}

func (s *Solid) Boolean(tool *Solid, op int) int {
	return int(C.topo_solid_boolean(s.inner.val, tool.inner.val, C.int(op)))
}

func (s *Solid) Fillet(edges []Edge, radius []float64) int {
	cshp := make([]C.struct__topo_edge_t, len(edges))
	for i := range edges {
		cshp[i] = edges[i].inner.val
	}
	return int(C.topo_solid_fillet(s.inner.val, &cshp[0], C.int(len(edges)), (*C.double)(unsafe.Pointer(&radius[0])), C.int(len(radius))))
}

func (s *Solid) Chamfer(edges []Edge, distances []float64) int {
	cshp := make([]C.struct__topo_edge_t, len(edges))
	for i := range edges {
		cshp[i] = edges[i].inner.val
	}
	return int(C.topo_solid_chamfer(s.inner.val, &cshp[0], C.int(len(edges)), (*C.double)(unsafe.Pointer(&distances[0])), C.int(len(distances))))
}

func (s *Solid) Shelling(faces []Face, offset, tolerance float64) int {
	cshp := make([]C.struct__topo_face_t, len(faces))
	for i := range faces {
		cshp[i] = faces[i].inner.val
	}
	return int(C.topo_solid_shelling(s.inner.val, &cshp[0], C.int(len(faces)), C.double(offset), C.double(tolerance)))
}

func (s *Solid) Offset(f *Face, offset, tolerance float64) int {
	return int(C.topo_solid_offset(s.inner.val, f.inner.val, C.double(offset), C.double(tolerance)))
}

func (s *Solid) Draft(faces []Face, d Dir3, angle float64, p Plane) int {
	fs := make([]C.struct__topo_face_t, len(faces))
	for i := range faces {
		fs[i] = faces[i].inner.val
	}
	return int(C.topo_solid_draft(s.inner.val, &fs[0], C.int(len(faces)), d.val, C.double(angle), p.val))
}

func (s *Solid) EvolvedFromFace(Spine *Face, Profil *Wire) int {
	return int(C.topo_solid_evolved_from_face(s.inner.val, Spine.inner.val, Profil.inner.val))
}

func (s *Solid) EvolvedFromWire(Spine *Wire, Profil *Wire) int {
	return int(C.topo_solid_evolved_from_wire(s.inner.val, Spine.inner.val, Profil.inner.val))
}

func (s *Solid) FeatPrism(f *Face, d Dir3, height float64, fuse bool) int {
	return int(C.topo_solid_feat_prism(s.inner.val, f.inner.val, d.val, C.double(height), C.bool(fuse)))
}

func (s *Solid) FeatPrismForRange(f *Face, d Dir3, from, end Face, fuse bool) int {
	return int(C.topo_solid_feat_prism_for_range(s.inner.val, f.inner.val, d.val, from.inner.val, end.inner.val, C.bool(fuse)))
}

func (s *Solid) FeatPrismForUntil(f *Face, d Dir3, until Face, fuse bool) int {
	return int(C.topo_solid_feat_prism_for_until(s.inner.val, f.inner.val, d.val, until.inner.val, C.bool(fuse)))
}

func (s *Solid) DraftPrism(f *Face, angle, height float64, fuse bool) int {
	return int(C.topo_solid_feat_draft_prism(s.inner.val, f.inner.val, C.double(angle), C.double(height), C.bool(fuse)))
}

func (s *Solid) DraftPrismForRange(f *Face, angle float64, from, end Face, fuse bool) int {
	return int(C.topo_solid_feat_draft_prism_for_range(s.inner.val, f.inner.val, C.double(angle), from.inner.val, end.inner.val, C.bool(fuse)))
}

func (s *Solid) DraftPrismForUntil(f *Face, angle float64, until Face, fuse bool) int {
	return int(C.topo_solid_feat_draft_prism_for_until(s.inner.val, f.inner.val, C.double(angle), until.inner.val, C.bool(fuse)))
}

func (s *Solid) RevolForRange(f *Face, a Axis1, from, end Face, fuse bool) int {
	return int(C.topo_solid_feat_revol_for_range(s.inner.val, f.inner.val, a.val, from.inner.val, end.inner.val, C.bool(fuse)))
}

func (s *Solid) RevolForUntil(f *Face, a Axis1, until Face, fuse bool) int {
	return int(C.topo_solid_feat_revol_for_until(s.inner.val, f.inner.val, a.val, until.inner.val, C.bool(fuse)))
}

func (s *Solid) PipeForRange(f *Face, w *Wire, from, end Face, fuse bool) int {
	return int(C.topo_solid_feat_pipe_for_range(s.inner.val, f.inner.val, w.inner.val, from.inner.val, end.inner.val, C.bool(fuse)))
}

func (s *Solid) PipeForUntil(f *Face, w *Wire, until Face, fuse bool) int {
	return int(C.topo_solid_feat_pipe_for_until(s.inner.val, f.inner.val, w.inner.val, until.inner.val, C.bool(fuse)))
}

func (s *Solid) LinearForm(w *Wire, p *GeomPlane, d, d1 Dir3, fuse bool) int {
	return int(C.topo_solid_linear_form(s.inner.val, w.inner.val, p.inner.geom, d.val, d1.val, C.bool(fuse)))
}

func (s *Solid) RevolutionForm(w *Wire, p *GeomPlane, a Axis1, h1, h2 float64, fuse bool) int {
	return int(C.topo_solid_revolution_form(s.inner.val, w.inner.val, p.inner.geom, a.val, C.double(h1), C.double(h2), C.bool(fuse)))
}

func (s *Solid) SectionFace(pnt, nor Point3) *Face {
	p := &Face{inner: &innerFace{val: C.topo_solid_section_face(s.inner.val, pnt.val, nor.val)}}
	runtime.SetFinalizer(p.inner, (*innerFace).free)
	return p
}

func (s *Solid) ConvertToNurbs() int {
	return int(C.topo_solid_convert_to_nurbs(s.inner.val))
}

func (t *Solid) ToShape() *Shape {
	sp := &Shape{inner: &innerShape{val: C.topo_shape_share(t.inner.val.shp)}}
	runtime.SetFinalizer(sp.inner, (*innerShape).free)
	return sp
}

func (t *innerSolid) free() {
	C.topo_solid_free(t.val)
}

func TopoMakeSolidFromCompSolid(S *CompSolid) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_comp_solid(S.inner.val)}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromShell(S *Shell) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_shell(S.inner.val)}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromTwoShell(S1, S2 *Shell) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_two_shell(S1.inner.val, S2.inner.val)}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromThreeShell(S1, S2, S3 *Shell) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_three_shell(S1.inner.val, S2.inner.val, S3.inner.val)}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromShells(S []Shell) *Solid {
	shls := make([]C.struct__topo_shell_t, len(S))
	for i := range S {
		shls[i] = S[i].inner.val
	}
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_shells(&shls[0], C.int(len(S)))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromSolid(S *Solid) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_solid(S.inner.val)}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromSolidShell(S *Solid, sl *Shell) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_solid_shell(S.inner.val, sl.inner.val)}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromFaces(S []Face, tolerance float64) *Solid {
	shls := make([]C.struct__topo_face_t, len(S))
	for i := range S {
		shls[i] = S[i].inner.val
	}
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_faces(&shls[0], C.int(len(S)), C.double(tolerance))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromBox(dx, dy, dz float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_box(C.double(dx), C.double(dy), C.double(dz))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromBoxPoint(p Point3, dx, dy, dz float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_box_point(p.val, C.double(dx), C.double(dy), C.double(dz))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromBoxTwoPoint(p1, p2 Point3) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_box_two_point(p1.val, p2.val)}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromBoxAxis2(a Axis2, dx, dy, dz float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_box_axis2(a.val, C.double(dx), C.double(dy), C.double(dz))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromCylinder(R, H float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_cylinder(C.double(R), C.double(H))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromCylinderAngle(R, H, Angle float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_cylinder_angle(C.double(R), C.double(H), C.double(Angle))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromCylinderAxis2(a Axis2, R, H float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_cylinder_axis2(a.val, C.double(R), C.double(H))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromCylinderAxis2Angle(a Axis2, R, H, Angle float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_cylinder_axis2_angle(a.val, C.double(R), C.double(H), C.double(Angle))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromCone(R1, R2, H float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_cone(C.double(R1), C.double(R2), C.double(H))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromConeAngle(R1, R2, H, Angle float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_cone_angle(C.double(R1), C.double(R2), C.double(H), C.double(Angle))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromConeAxis2(a Axis2, R1, R2, H float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_cone_axis2(a.val, C.double(R1), C.double(R2), C.double(H))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromConeAxis2Angle(a Axis2, R1, R2, H, Angle float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_cone_axis2_angle(a.val, C.double(R1), C.double(R2), C.double(H), C.double(Angle))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFroRevolution(Meridian *GeomCurve) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_revolution(Meridian.inner.geom)}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFroRevolutionAngle(Meridian *GeomCurve, angle float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_revolution_angle(Meridian.inner.geom, C.double(angle))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFroRevolutionLimit(Meridian *GeomCurve, VMin, VMax float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_revolution_limit(Meridian.inner.geom, C.double(VMin), C.double(VMax))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFroRevolutionLimitAngle(Meridian *GeomCurve, VMin, VMax, angle float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_revolution_limit_angle(Meridian.inner.geom, C.double(VMin), C.double(VMax), C.double(angle))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFroRevolutionAxis2(a Axis2, Meridian *GeomCurve) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_revolution_axis2(a.val, Meridian.inner.geom)}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFroRevolutionAxis2Angle(a Axis2, Meridian *GeomCurve, angle float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_revolution_axis2_angle(a.val, Meridian.inner.geom, C.double(angle))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFroRevolutionAxis2Limit(a Axis2, Meridian *GeomCurve, VMin, VMax float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_revolution_axis2_limit(a.val, Meridian.inner.geom, C.double(VMin), C.double(VMax))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFroRevolutionAxis2LimitAngle(a Axis2, Meridian *GeomCurve, VMin, VMax, angle float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_revolution_axis2_limit_angle(a.val, Meridian.inner.geom, C.double(VMin), C.double(VMax), C.double(angle))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromSphere(R float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_sphere(C.double(R))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromSphereAngle(R, angle float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_sphere_angle(C.double(R), C.double(angle))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromSphereTwoAngle(R, angle1, angle2 float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_sphere_two_angle(C.double(R), C.double(angle1), C.double(angle2))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromSphereThreeAngle(R, angle1, angle2, angle3 float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_sphere_three_angle(C.double(R), C.double(angle1), C.double(angle2), C.double(angle3))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromSphereCenterAngle(c Point3, R, angle float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_sphere_center_angle(c.val, C.double(R), C.double(angle))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromSphereCenterTwoAngle(c Point3, R, angle1, angle2 float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_sphere_center_two_angle(c.val, C.double(R), C.double(angle1), C.double(angle2))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromSphereCenterThreeAngle(c Point3, R, angle1, angle2, angle3 float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_sphere_center_three_angle(c.val, C.double(R), C.double(angle1), C.double(angle2), C.double(angle3))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromSphereAxis2(a Axis2, R float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_sphere_axis2(a.val, C.double(R))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromSphereAxis2Angle(a Axis2, R, angle float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_sphere_axis2_angle(a.val, C.double(R), C.double(angle))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromSphereAxis2TwoAngle(a Axis2, R, angle1, angle2 float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_sphere_axis2_two_angle(a.val, C.double(R), C.double(angle1), C.double(angle2))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromSphereAxis2ThreeAngle(a Axis2, R, angle1, angle2, angle3 float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_sphere_axis2_three_angle(a.val, C.double(R), C.double(angle1), C.double(angle2), C.double(angle3))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromSphereTorus(R1, R2 float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_torus(C.double(R1), C.double(R2))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromSphereTorusAngle(R1, R2, angle float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_torus_angle(C.double(R1), C.double(R2), C.double(angle))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromSphereTorusTwoAngle(R1, R2, angle1, angle2 float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_torus_two_angle(C.double(R1), C.double(R2), C.double(angle1), C.double(angle2))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromSphereTorusThreeAngle(R1, R2, angle1, angle2, angle3 float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_torus_three_angle(C.double(R1), C.double(R2), C.double(angle1), C.double(angle2), C.double(angle3))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromSphereTorusAxis2(a Axis2, R1, R2 float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_torus_axis2(a.val, C.double(R1), C.double(R2))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromSphereTorusAxis2Angle(a Axis2, R1, R2, angle float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_torus_axis2_angle(a.val, C.double(R1), C.double(R2), C.double(angle))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromSphereTorusAxis2TwoAngle(a Axis2, R1, R2, angle1, angle2 float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_torus_axis2_two_angle(a.val, C.double(R1), C.double(R2), C.double(angle1), C.double(angle2))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromSphereTorusAxis2ThreeAngle(a Axis2, R1, R2, angle1, angle2, angle3 float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_torus_axis2_three_angle(a.val, C.double(R1), C.double(R2), C.double(angle1), C.double(angle2), C.double(angle3))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromSphereWedge(dx, dy, dz, ltx float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_wedge(C.double(dx), C.double(dy), C.double(dz), C.double(ltx))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromSphereWedgeAxis2(a Axis2, dx, dy, dz, ltx float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_wedge_axis2(a.val, C.double(dx), C.double(dy), C.double(dz), C.double(ltx))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromSphereWedgeLimit(dx, dy, dz, xmin, zmin, xmax, zmax float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_wedge_limit(C.double(dx), C.double(dy), C.double(dz), C.double(xmin), C.double(zmin), C.double(xmax), C.double(zmax))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromSphereWedgeAxis2Limit(a Axis2, dx, dy, dz, xmin, zmin, xmax, zmax float64) *Solid {
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_wedge_axis2_limit(a.val, C.double(dx), C.double(dy), C.double(dz), C.double(xmin), C.double(zmin), C.double(xmax), C.double(zmax))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

func TopoMakeSolidFromLoft(wires []Wire, ruled bool) *Solid {
	cshp := make([]C.struct__topo_wire_t, len(wires))
	for i := range wires {
		cshp[i] = wires[i].inner.val
	}
	sld := &Solid{inner: &innerSolid{val: C.topo_solid_make_solid_from_loft(&cshp[0], C.int(len(wires)), C.bool(ruled))}}
	runtime.SetFinalizer(sld.inner, (*innerSolid).free)
	return sld
}

type SolidIterator struct {
	inner *innerSolidIterator
}
type innerSolidIterator struct {
	val *C.struct__topo_solid_iterator_t
}

func TopoMakeSolidIterator(p Shape) *SolidIterator {
	wr := &SolidIterator{inner: &innerSolidIterator{val: C.topo_solid_iterator_make(p.inner.val)}}
	runtime.SetFinalizer(wr.inner, (*innerSolidIterator).free)
	return wr
}

func (t *innerSolidIterator) free() {
	C.topo_solid_iterator_free(t.val)
}

func (t *SolidIterator) Next() *Solid {
	v := C.topo_solid_iterator_next(t.inner.val)
	if v != nil {
		var val C.struct__topo_solid_t
		val.shp = v
		p := &Solid{inner: &innerSolid{val: val}}
		runtime.SetFinalizer(p.inner, (*innerSolid).free)
		return p
	}
	return nil
}
