package topovis

/*
#include <stdlib.h>
#include "topo_c_api.h"
#cgo CFLAGS: -I ./
#cgo linux CXXFLAGS: -I ./include/oce -I ./include/linux/oce -I ./
#cgo darwin CXXFLAGS: -I ./include/oce -I ./include/darwin/oce -I ./
#cgo windows CXXFLAGS:  -I ./include/oce -I ./include/windows/oce -I ./
#cgo linux LDFLAGS: -L ./lib/linux_amd64 -L /usr/lib/x86_64-linux-gnu/ -Wl,--start-group -lpthread -ldl -lm -lGL -lGLU -lX11 -lfreetype -lTKernel -lTKMath -lTKG2d -lTKG3d -lTKGeomBase -lTKBRep -lTKGeomAlgo -lTKTopAlgo -lTKPrim -lTKBO -lTKHLR -lTKMesh -lTKShHealing -lTKXMesh -lTKBool -lTKFillet -lTKFeat -lTKOffset -lTKService -lTKV3d -lTKCDF -lPTKernel -lTKLCAF -lFWOSPlugin -lTKPShape -lTKBinL -lTKXmlL -lTKPLCAF -lTKTObj -lTKShapeSchema -lTKStdLSchema -lTKCAF -lTKBin -lTKXml -lTKPCAF -lTKBinTObj -lTKXmlTObj -lTKStdSchema -lTKSTL -lTKXSBase -lTKSTEPBase -lTKIGES -lTKSTEPAttr -lTKSTEP209 -lTKSTEP -lTKVRML -lTKXCAF -lTKXCAFSchema -lTKXmlXCAF -lTKBinXCAF -lTKXDEIGES -lTKXDESTEP -Wl,--end-group
#cgo darwin LDFLAGS: -L ./lib/darwin_amd64 -lfreetype -lTKernel -lTKMath -lTKG2d -lTKG3d -lTKGeomBase -lTKBRep -lTKGeomAlgo -lTKTopAlgo -lTKPrim -lTKBO -lTKHLR -lTKMesh -lTKShHealing -lTKXMesh -lTKBool -lTKFillet -lTKFeat -lTKOffset -lTKService -lTKV3d -lTKCDF -lPTKernel -lTKLCAF -lFWOSPlugin -lTKPShape -lTKBinL -lTKXmlL -lTKPLCAF -lTKTObj -lTKShapeSchema -lTKStdLSchema -lTKCAF -lTKBin -lTKXml -lTKPCAF -lTKBinTObj -lTKXmlTObj -lTKStdSchema -lTKSTL -lTKXSBase -lTKSTEPBase -lTKIGES -lTKSTEPAttr -lTKSTEP209 -lTKSTEP -lTKVRML -lTKXCAF -lTKXCAFSchema -lTKXmlXCAF -lTKBinXCAF -lTKXDEIGES -lTKXDESTEP
#cgo windows LDFLAGS: -L ./lib/windows_amd64 -lfreetype -lTKernel -lTKMath -lTKG2d -lTKG3d -lTKGeomBase -lTKBRep -lTKGeomAlgo -lTKTopAlgo -lTKPrim -lTKBO -lTKHLR -lTKMesh -lTKShHealing -lTKXMesh -lTKBool -lTKFillet -lTKFeat -lTKOffset -lTKService -lTKV3d -lTKCDF -lPTKernel -lTKLCAF -lFWOSPlugin -lTKPShape -lTKBinL -lTKXmlL -lTKPLCAF -lTKTObj -lTKShapeSchema -lTKStdLSchema -lTKCAF -lTKBin -lTKXml -lTKPCAF -lTKBinTObj -lTKXmlTObj -lTKStdSchema -lTKSTL -lTKXSBase -lTKSTEPBase -lTKIGES -lTKSTEPAttr -lTKSTEP209 -lTKSTEP -lTKVRML -lTKXCAF -lTKXCAFSchema -lTKXmlXCAF -lTKBinXCAF -lTKXDEIGES -lTKXDESTEP
*/
import "C"

import (
	"unsafe"
)

const (
	FUSE   = int(C.BOOLFUSE)
	CUT    = int(C.BOOLCUT)
	COMMON = int(C.BOOLCOMMON)
)

const (
	WEST  = int(C.DIR_WEST)
	EAST  = int(C.DIR_EAST)
	NORTH = int(C.DIR_NORTH)
	SOUTH = int(C.DIR_SOUTH)
	UP    = int(C.DIR_UP)
	DOWN  = int(C.DIR_DOWN)
)

const (
	TopoSolid     = int(C.TopoSolid)
	TopoShell     = int(C.TopoShell)
	TopoFace      = int(C.TopoFace)
	TopoEdge      = int(C.TopoEdge)
	TopoVertex    = int(C.TopoVertex)
	TopoWire      = int(C.TopoWire)
	TopoCompound  = int(C.TopoCompound)
	TopoCompSolid = int(C.TopoCompSolid)
	TopoShape     = int(C.TopoShape)
)

const (
	FORWARD  = int(C.ORI_FORWARD)
	REVERSED = int(C.ORI_REVERSED)
	INTERNAL = int(C.ORI_INTERNAL)
	EXTERNAL = int(C.ORI_EXTERNAL)
	UNKNOW   = int(C.ORI_UNKNOW)
)

type MeshReceiver struct {
	val   *C.struct__topo_mesh_receiver_t
	index int
	Faces []Color
	Vers  [][]Point3
	Norms [][]Point3
	Tris  [][][3]int
}

func NewMeshReceiver() *MeshReceiver {
	ret := &MeshReceiver{val: nil, index: -1}
	var cb C.struct__mesh_receiver_cb_t
	cb.ctx = unsafe.Pointer(ret)
	ret.val = C.topo_mesh_receiver_new(cb)
	return ret
}

func (m *MeshReceiver) begin() {
	m.Faces = append(m.Faces, Color{})
	m.Vers = append(m.Vers, []Point3{})
	m.Norms = append(m.Norms, []Point3{})
	m.Tris = append(m.Tris, [][3]int{})
	m.index++
}

func (m *MeshReceiver) end() {

}

func (m *MeshReceiver) appendFace(c Color) int {
	return m.index
}

func (m *MeshReceiver) appendNodeNorm(f int, p, n Point3) {
	m.Vers[f] = append(m.Vers[f], p)
	m.Norms[f] = append(m.Norms[f], n)
}

func (m *MeshReceiver) appendNode(f int, p Point3) {
	m.Vers[f] = append(m.Vers[f], p)
}

func (m *MeshReceiver) appendTriangle(f int, tri [3]int) {
	m.Tris[f] = append(m.Tris[f], tri)
}

func (m *MeshReceiver) Free() {
	C.topo_mesh_receiver_free(m.val)
	m.val = nil
}

type Location struct {
	val *C.struct__topo_location_t
}

func NewLocation(t Trsf) *Location {
	return &Location{val: C.topo_location_new(t.val)}
}

func (l *Location) Trsf() Trsf {
	return Trsf{val: C.topo_location_get_trsf(l.val)}
}

func (l *Location) Free() {
	C.topo_location_free(l.val)
	l.val = nil
}

type Shape struct {
	val *C.struct__topo_shape_t
}

func (s *Shape) IsNull() bool {
	return bool(C.topo_shape_is_null(s.val))
}

func (s *Shape) IsValid() bool {
	return bool(C.topo_shape_is_valid(s.val))
}

func (s *Shape) Equals(e *Shape) bool {
	return bool(C.topo_shape_equals(s.val, e.val))
}

func (s *Shape) Type() int {
	return int(C.topo_shape_type(s.val))
}

func (s *Shape) BBox() BBox {
	return BBox{val: C.topo_shape_bounding_box(s.val)}
}

func (s *Shape) Hash() int {
	return int(C.topo_shape_hash_code(s.val))
}

func (s *Shape) Transform(t Trsf) int {
	return int(C.topo_shape_transform(s.val, t.val))
}

func (s *Shape) Translate(v Vector3) int {
	return int(C.topo_shape_translate(s.val, v.val))
}

func (s *Shape) RotateFromPoint(angle float64, p1, p2 Point3) int {
	return int(C.topo_shape_rotate_from_two_point(s.val, C.double(angle), p1.val, p2.val))
}

func (s *Shape) RotateFromAxis1(angle float64, a Axis1) int {
	return int(C.topo_shape_rotate_from_axis1(s.val, C.double(angle), a.val))
}

func (s *Shape) RotateFromQuaternion(q Quaternion) int {
	return int(C.topo_shape_rotate_from_quaternion(s.val, q.val))
}

func (s *Shape) Scale(angle float64, a Point3) int {
	return int(C.topo_shape_scale(s.val, C.double(angle), a.val))
}

func (s *Shape) MirrorFromPointNorm(pnt, ner Point3) int {
	return int(C.topo_shape_mirror_from_point_norm(s.val, pnt.val, ner.val))
}

func (s *Shape) MirrorFromAxis1(a Axis1) int {
	return int(C.topo_shape_mirror_from_axis1(s.val, a.val))
}

func (s *Shape) MirrorFromAxis2(a Axis2) int {
	return int(C.topo_shape_mirror_from_axis2(s.val, a.val))
}

func (s *Shape) Transformed(t Trsf) *Shape {
	return &Shape{val: C.topo_shape_transformed(s.val, t.val)}
}

func (s *Shape) Translated(v Vector3) *Shape {
	return &Shape{val: C.topo_shape_translated(s.val, v.val)}
}

func (s *Shape) RotatedFromPoint(angle float64, p1, p2 Point3) *Shape {
	return &Shape{val: C.topo_shape_rotated_from_two_point(s.val, C.double(angle), p1.val, p2.val)}
}

func (s *Shape) RotatedFromAxis1(angle float64, a Axis1) *Shape {
	return &Shape{val: C.topo_shape_rotated_from_axis1(s.val, C.double(angle), a.val)}
}

func (s *Shape) RotatedFromQuaternion(q Quaternion) *Shape {
	return &Shape{val: C.topo_shape_rotated_from_quaternion(s.val, q.val)}
}

func (s *Shape) Scaled(angle float64, a Point3) *Shape {
	return &Shape{val: C.topo_shape_scaled(s.val, C.double(angle), a.val)}
}

func (s *Shape) MirroredFromPointNorm(pnt, ner Point3) *Shape {
	return &Shape{val: C.topo_shape_mirrored_from_point_norm(s.val, pnt.val, ner.val)}
}

func (s *Shape) MirroredFromAxis1(a Axis1) *Shape {
	return &Shape{val: C.topo_shape_mirrored_from_axis1(s.val, a.val)}
}

func (s *Shape) MirroredFromAxis2(a Axis2) *Shape {
	return &Shape{val: C.topo_shape_mirrored_from_axis2(s.val, a.val)}
}

func (s *Shape) GetOrientation() int {
	return int(C.topo_shape_get_orientation(s.val))
}

func (s *Shape) SetOrientation(t int) {
	C.topo_shape_set_orientation(s.val, C.int(t))
}

func (s *Shape) GetLocation() *Location {
	return &Location{val: C.topo_shape_get_location(s.val)}
}

func (s *Shape) SetLocation(t *Location) {
	C.topo_shape_set_location(s.val, t.val)
}

func (s *Shape) FixShape() bool {
	return bool(C.topo_shape_fix_shape(s.val))
}

func (s *Shape) Copy() *Shape {
	return &Shape{val: C.topo_shape_copy(s.val)}
}

func (s *Shape) Mesh(m *MeshReceiver, tolerance, deflection, angle float64) {
	C.topo_shape_mesh(s.val, m.val, C.double(tolerance), C.double(deflection), C.double(angle))
}

func (s *Shape) SetSurfaceColour(c Color) {
	C.topo_shape_set_surface_colour(s.val, c.val)
}

func (s *Shape) SetCurveColour(c Color) {
	C.topo_shape_set_curve_colour(s.val, c.val)
}

func (s *Shape) SetLabel(l string) {
	str := C.CString(l)
	defer C.free(unsafe.Pointer(str))
	C.topo_shape_set_label(s.val, str)
}

func (s *Shape) GetSurfaceColour() Color {
	return Color{val: C.topo_shape_get_surface_colour(s.val)}
}

func (s *Shape) GetCurveColour() Color {
	return Color{val: C.topo_shape_get_surface_colour(s.val)}
}

func (s *Shape) GetLabel() string {
	return C.GoString(C.topo_shape_get_label(s.val))
}

func (t *Shape) Free() {
	C.topo_shape_free(t.val)
	t.val = nil
}

type CompSolid struct {
	val C.struct__topo_comp_solid_t
}

func (t *CompSolid) Free() {
	C.topo_comp_solid_free(t.val)
}

func TopoCompSolidMake(s []Solid) *CompSolid {
	sos := make([]C.struct__topo_solid_t, len(s))
	for i := range s {
		sos[i] = s[i].val
	}
	return &CompSolid{val: C.topo_comp_solid_make_comp_solid(&sos[0], C.int(len(s)))}
}

type Compound struct {
	val C.struct__topo_compound_t
}

func (t *Compound) Free() {
	C.topo_compound_free(t.val)
}

func TopoCompoundMake(s []Shape) *Compound {
	sos := make([]*C.struct__topo_shape_t, len(s))
	for i := range s {
		sos[i] = s[i].val
	}
	return &Compound{val: C.topo_compound_make_compound(&sos[0], C.int(len(s)))}
}

type Edge struct {
	val C.struct__topo_edge_t
}

func (t *Edge) IsSeam(f Face) bool {
	return bool(C.topo_edge_is_seam(t.val, f.val))
}

func (t *Edge) IsDegenerated() bool {
	return bool(C.topo_edge_is_degenerated(t.val))
}

func (t *Edge) IsClosed() bool {
	return bool(C.topo_edge_is_closed(t.val))
}

func (t *Edge) IsInifinite() bool {
	return bool(C.topo_edge_is_inifinite(t.val))
}

func (t *Edge) NumVertices() int {
	return int(C.topo_edge_num_vertices(t.val))
}

func (t *Edge) Length() float64 {
	return float64(C.topo_edge_length(t.val))
}

func (t *Edge) Tolerance() float32 {
	return float32(C.topo_edge_tolerance(t.val))
}

func (t *Edge) IsCurve3d() bool {
	return bool(C.topo_edge_is_curve3d(t.val))
}

func (t *Edge) ToCurve3d() {
	C.topo_edge_convert_to_curve3d(t.val)
}

func (t *Edge) Free() {
	C.topo_edge_free(t.val)
}

/**

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_two_vertex(topo_vertex_t V1,
                                                             topo_vertex_t V2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_two_point(pnt3d_t P1,
                                                            pnt3d_t P2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_line(line_t L);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_line_p(line_t L, double p1,
                                                         double p2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_line_point(line_t L,
                                                             pnt3d_t P1,
                                                             pnt3d_t P2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_line_vertex(line_t L,
                                                              topo_vertex_t V1,
                                                              topo_vertex_t V2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_circ(circ_t L);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_circ_p(circ_t L, double p1,
                                                         double p2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_circ_point(circ_t L,
                                                             pnt3d_t P1,
                                                             pnt3d_t P2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_circ_vertex(circ_t L,
                                                              topo_vertex_t V1,
                                                              topo_vertex_t V2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_elips(elips_t L);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_elips_p(elips_t L, double p1,
                                                          double p2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_elips_point(elips_t L,
                                                              pnt3d_t P1,
                                                              pnt3d_t P2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_elips_vertex(
    elips_t L, topo_vertex_t V1, topo_vertex_t V2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_hyper(hyperbola_t L);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_hyper_p(hyperbola_t L,
                                                          double p1, double p2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_hyper_point(hyperbola_t L,
                                                              pnt3d_t P1,
                                                              pnt3d_t P2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_hyper_vertex(
    hyperbola_t L, topo_vertex_t V1, topo_vertex_t V2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_parab(parabola_t L);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_parab_p(parabola_t L,
                                                          double p1, double p2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_parab_point(parabola_t L,
                                                              pnt3d_t P1,
                                                              pnt3d_t P2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_parab_vertex(
    parabola_t L, topo_vertex_t V1, topo_vertex_t V2);

TOPOCAPICALL topo_edge_t topo_edge_make_edgee_from_curve(geom_curve_t *L);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_curve_p(geom_curve_t *L,
                                                          double p1, double p2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_curve_point(geom_curve_t *L,
                                                              pnt3d_t P1,
                                                              pnt3d_t P2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_curve_vertex(
    geom_curve_t *L, topo_vertex_t V1, topo_vertex_t V2);

TOPOCAPICALL topo_edge_t topo_edge_make_edgee_from_curve_point_p(
    geom_curve_t *L, pnt3d_t P1, pnt3d_t P2, double p1, double p2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_curve_vertex_p(
    geom_curve_t *L, topo_vertex_t V1, topo_vertex_t V2, double p1, double p2);

TOPOCAPICALL topo_edge_t
topo_edge_make_edge_from_curve_surface(geom2d_curve_t *L, geom_surface_t *S);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_curve_surface_p(
    geom2d_curve_t *L, geom_surface_t *S, double p1, double p2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_curve_surface_point(
    geom2d_curve_t *L, geom_surface_t *S, pnt3d_t P1, pnt3d_t P2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_curve_surface_vertex(
    geom2d_curve_t *L, geom_surface_t *S, topo_vertex_t V1, topo_vertex_t V2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_curve_surface_point_p(
    geom2d_curve_t *L, geom_surface_t *S, pnt3d_t P1, pnt3d_t P2, double p1,
    double p2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge_from_curve_surface_vertex_p(
    geom2d_curve_t *L, geom_surface_t *S, topo_vertex_t V1, topo_vertex_t V2,
    double p1, double p2);

TOPOCAPICALL topo_edge_t
topo_edge_make_edge2d_from_two_vertex(topo_vertex_t V1, topo_vertex_t V2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge2d_from_two_point(pnt2d_t P1,
                                                              pnt2d_t P2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge2d_from_line(line2d_t L);

TOPOCAPICALL topo_edge_t topo_edge_make_edge2d_from_line_p(line2d_t L,
                                                           double p1,
                                                           double p2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge2d_from_line_point(line2d_t L,
                                                               pnt2d_t P1,
                                                               pnt2d_t P2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge2d_from_line_vertex(
    line2d_t L, topo_vertex_t V1, topo_vertex_t V2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge2d_from_circ(circ2d_t L);

TOPOCAPICALL topo_edge_t topo_edge_make_edge2d_from_circ_p(circ2d_t L,
                                                           double p1,
                                                           double p2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge2d_from_circ_point(circ2d_t L,
                                                               pnt2d_t P1,
                                                               pnt2d_t P2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge2d_from_circ_vertex(
    circ2d_t L, topo_vertex_t V1, topo_vertex_t V2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge2d_from_elips(elips2d_t L);

TOPOCAPICALL topo_edge_t topo_edge_make_edge2d_from_elips_p(elips2d_t L,
                                                            double p1,
                                                            double p2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge2d_from_elips_point(elips2d_t L,
                                                                pnt2d_t P1,
                                                                pnt2d_t P2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge2d_from_elips_vertex(
    elips2d_t L, topo_vertex_t V1, topo_vertex_t V2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge2d_from_hyper(hyperbola2d_t L);

TOPOCAPICALL topo_edge_t topo_edge_make_edge2d_from_hyper_p(hyperbola2d_t L,
                                                            double p1,
                                                            double p2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge2d_from_hyper_point(hyperbola2d_t L,
                                                                pnt2d_t P1,
                                                                pnt2d_t P2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge2d_from_hyper_vertex(
    hyperbola2d_t L, topo_vertex_t V1, topo_vertex_t V2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge2d_from_parab(parabola2d_t L);

TOPOCAPICALL topo_edge_t topo_edge_make_edge2d_from_parab_p(parabola2d_t L,
                                                            double p1,
                                                            double p2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge2d_from_parab_point(parabola2d_t L,
                                                                pnt2d_t P1,
                                                                pnt2d_t P2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge2d_from_parab_vertex(
    parabola2d_t L, topo_vertex_t V1, topo_vertex_t V2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge2d_from_curve(geom2d_curve_t *L);

TOPOCAPICALL topo_edge_t topo_edge_make_edge2d_from_curve_p(geom2d_curve_t *L,
                                                            double p1,
                                                            double p2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge2d_from_curve_point(
    geom2d_curve_t *L, pnt2d_t P1, pnt2d_t P2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge2d_from_curve_vertex(
    geom2d_curve_t *L, topo_vertex_t V1, topo_vertex_t V2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge2d_from_curve_point_p(
    geom2d_curve_t *L, pnt2d_t P1, pnt2d_t P2, double p1, double p2);

TOPOCAPICALL topo_edge_t topo_edge_make_edge2d_from_curve_vertex_p(
    geom2d_curve_t *L, topo_vertex_t V1, topo_vertex_t V2, double p1,
    double p2);

TOPOCAPICALL topo_edge_t topo_edge_make_polygon();

TOPOCAPICALL topo_edge_t topo_edge_make_polygon_from_two_point(pnt3d_t P1,
                                                               pnt3d_t P2);

TOPOCAPICALL topo_edge_t topo_edge_make_polygon_from_three_point(pnt3d_t P1,
                                                                 pnt3d_t P2,
                                                                 pnt3d_t P3,
                                                                 _Bool Close);

TOPOCAPICALL topo_edge_t topo_edge_make_polygon_from_four_point(
    pnt3d_t P1, pnt3d_t P2, pnt3d_t P3, pnt3d_t P4, _Bool Close);

TOPOCAPICALL topo_edge_t
topo_edge_make_polygon_from_two_vertex(topo_vertex_t V1, topo_vertex_t V2);

TOPOCAPICALL topo_edge_t topo_edge_make_polygon_from_three_vertex(
    topo_vertex_t V1, topo_vertex_t V2, topo_vertex_t V3, _Bool Close);

TOPOCAPICALL topo_edge_t topo_edge_make_polygon_from_four_vertex(
    topo_vertex_t V1, topo_vertex_t V2, topo_vertex_t V3, topo_vertex_t V4,
    _Bool Close);

TOPOCAPICALL topo_edge_t topo_edge_make_polygon_from_vertices(
    topo_vertex_t *vertices, int vertcount, _Bool Close);
TOPOCAPICALL topo_edge_t topo_edge_make_polygonn_from_points(pnt3d_t *vertexs,

**/

type Face struct {
	val C.struct__topo_face_t
}

func (t *Face) NumWires() int {
	return int(C.topo_face_num_wires(t.val))
}

func (t *Face) NumFaces() int {
	return int(C.topo_face_num_faces(t.val))
}

func (t *Face) Area() float64 {
	return float64(C.topo_face_area(t.val))
}

func (t *Face) Tolerance() float32 {
	return float32(C.topo_face_tolerance(t.val))
}

func (t *Face) Inertia() BBox {
	return BBox{val: C.topo_face_inertia(t.val)}
}

func (t *Face) CentreOfMass() Point3 {
	return Point3{val: C.topo_face_centre_of_mass(t.val)}
}

func (t *Face) Offset(offset, tolerance float64) int {
	return int(C.topo_face_offset(t.val, C.double(offset), C.double(tolerance)))
}

func (t *Face) Extrude(shp *Shape, p1, p2 Point3) int {
	return int(C.topo_face_extrude(t.val, shp.val, p1.val, p2.val))
}

func (t *Face) Revolve(shp *Shape, p1, p2 Point3, angle float64) int {
	return int(C.topo_face_revolve(t.val, shp.val, p1.val, p2.val, C.double(angle)))
}

func (t *Face) Sweep(spine *Wire, profiles []Shape, cornerMode int) int {
	prs := make([]*C.struct__topo_shape_t, len(profiles))
	for i := range profiles {
		prs[i] = profiles[i].val
	}
	return int(C.topo_face_sweep(t.val, spine.val, &prs[0], C.int(len(profiles)), C.int(cornerMode)))
}

func (t *Face) Loft(profiles []Shape, ruled bool, tolerance float64) int {
	prs := make([]*C.struct__topo_shape_t, len(profiles))
	for i := range profiles {
		prs[i] = profiles[i].val
	}
	return int(C.topo_face_loft(t.val, &prs[0], C.int(len(profiles)), C.bool(ruled), C.double(tolerance)))
}

func (t *Face) Boolean(tool *Face, op int) int {
	return int(C.topo_face_boolean(t.val, tool.val, C.int(op)))
}

func (t *Face) Free() {
	C.topo_face_free(t.val)
}

/**

TOPOCAPICALL topo_face_t topo_face_make_face(topo_face_t F);

TOPOCAPICALL topo_face_t topo_face_make_face_from_plane(plane_t P);

TOPOCAPICALL topo_face_t topo_face_make_face_from_cylinder(cylinder_t C);

TOPOCAPICALL topo_face_t topo_face_make_face_from_cone(cone_t C);

TOPOCAPICALL topo_face_t topo_face_make_face_from_sphere(sphere_t S);

TOPOCAPICALL topo_face_t topo_face_make_face_from_torus(torus_t C);

TOPOCAPICALL topo_face_t topo_face_make_face_from_surface(geom_surface_t *S,
                                                          double TolDegen);

TOPOCAPICALL topo_face_t topo_face_make_face_from_plane_p(
    plane_t P, double UMin, double UMax, double VMin, double VMax);

TOPOCAPICALL topo_face_t topo_face_make_face_from_cylinder_p(
    cylinder_t C, double UMin, double UMax, double VMin, double VMax);

TOPOCAPICALL topo_face_t topo_face_make_face_from_cone_p(cone_t C, double UMin,
                                                         double UMax,
                                                         double VMin,
                                                         double VMax);

TOPOCAPICALL topo_face_t topo_face_make_face_from_sphere_p(
    sphere_t S, double UMin, double UMax, double VMin, double VMax);

TOPOCAPICALL topo_face_t topo_face_make_face_from_torus_p(
    torus_t C, double UMin, double UMax, double VMin, double VMax);

TOPOCAPICALL topo_face_t
topo_face_make_face_from_surface_p(geom_surface_t *S, double UMin, double UMax,
                                   double VMin, double VMax, double TolDegen);

TOPOCAPICALL topo_face_t
topo_face_make_face_from_wire_onlyplane(topo_wire_t W, _Bool OnlyPlane);

TOPOCAPICALL topo_face_t topo_face_make_face_from_plane_wire(plane_t P,
                                                             topo_wire_t W,
                                                             _Bool Inside);

TOPOCAPICALL topo_face_t topo_face_make_face_from_cylinder_wire(cylinder_t C,
                                                                topo_wire_t W,
                                                                _Bool Inside);

TOPOCAPICALL topo_face_t topo_face_make_face_from_cone_wire(cone_t C,
                                                            topo_wire_t W,
                                                            _Bool Inside);

TOPOCAPICALL topo_face_t topo_face_make_face_from_sphere_wire(sphere_t S,
                                                              topo_wire_t W,
                                                              _Bool Inside);

TOPOCAPICALL topo_face_t topo_face_make_face_from_torus_wire(torus_t C,
                                                             topo_wire_t W,
                                                             _Bool Inside);

TOPOCAPICALL topo_face_t topo_face_make_face_from_surface_wire(
    geom_surface_t *S, topo_wire_t W, _Bool Inside);

TOPOCAPICALL topo_face_t topo_face_make_face_from_face_wire(topo_face_t F,
                                                            topo_wire_t W);

TOPOCAPICALL topo_face_t topo_face_make_face_from_wire(topo_wire_t *wires,
                                                       int count);

TOPOCAPICALL topo_face_t topo_face_make_face_from_egdes(topo_edge_t *edges,
                                                        int edgecount,
                                                        pnt3d_t *points,
                                                        int pcount);

TOPOCAPICALL topo_face_t topo_face_make_face_from_points(pnt3d_t *points,

**/

type Shell struct {
	val C.struct__topo_shell_t
}

func (t *Shell) Free() {
	C.topo_shell_free(t.val)
}

/**

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_surface(geom_surface_t *S,
                                                             _Bool Segment);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_surface_p(
    geom_surface_t *S, double UMin, double UMax, double VMin, double VMax,
    _Bool Segment);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_box(double dx, double dy,
                                                         double dz);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_box_point(pnt3d_t P,
                                                               double dx,
                                                               double dy,
                                                               double dz);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_box_two_point(pnt3d_t P1,
                                                                   pnt3d_t P2);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_box_axis2(axis2_t Axes,
                                                               double dx,
                                                               double dy,
                                                               double dz);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_cylinder(double R,
                                                              double H);

TOPOCAPICALL topo_shell_t
topo_shell_make_shell_from_cylinder_angle(double R, double H, double Angle);

TOPOCAPICALL topo_shell_t
topo_shell_make_shell_from_cylinder_axis2(axis2_t Axes, double R, double H);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_cylinder_axis2_angle(
    axis2_t Axes, double R, double H, double Angle);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_cone(double R1, double R2,
                                                          double H);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_cone_angle(double R1,
                                                                double R2,
                                                                double H,
                                                                double angle);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_cone_axis2(axis2_t Axes,
                                                                double R1,
                                                                double R2,
                                                                double H);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_cone_axis2_angle(
    axis2_t Axes, double R1, double R2, double H, double angle);

TOPOCAPICALL topo_shell_t
topo_shell_make_shell_from_revolution(geom_curve_t *Meridian);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_revolution_angle(
    geom_curve_t *Meridian, double angle);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_revolution_limit(
    geom_curve_t *Meridian, double VMin, double VMax);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_revolution_limit_angle(
    geom_curve_t *Meridian, double VMin, double VMax, double angle);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_revolution_axis2(
    axis2_t Axes, geom_curve_t *Meridian);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_revolution_axis2_angle(
    axis2_t Axes, geom_curve_t *Meridian, double angle);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_revolution_axis2_limit(
    axis2_t Axes, geom_curve_t *Meridian, double VMin, double VMax);

TOPOCAPICALL topo_shell_t
topo_shell_make_shell_from_revolution_axis2_limit_angle(axis2_t Axes,
                                                        geom_curve_t *Meridian,
                                                        double VMin,
                                                        double VMax,
                                                        double angle);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_sphere(double R);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_sphere_angle(double R,
                                                                  double angle);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_sphere_two_angle(
    double R, double angle1, double angle2);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_sphere_three_angle(
    double R, double angle1, double angle2, double angle3);

TOPOCAPICALL topo_shell_t
topo_shell_make_shell_from_sphere_center_raduis(pnt3d_t Center, double R);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_sphere_center_angle(
    pnt3d_t Center, double R, double angle);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_sphere_center_two_angle(
    pnt3d_t Center, double R, double angle1, double angle2);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_sphere_center_three_angle(
    pnt3d_t Center, double R, double angle1, double angle2, double angle3);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_sphere_axis2(axis2_t Axis,
                                                                  double R);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_sphere_axis2_raduis(
    axis2_t Axis, double R, double angle);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_sphere_axis2_two_angle(
    axis2_t Axis, double R, double angle1, double angle2);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_sphere_axis2_three_angle(
    axis2_t Axis, double R, double angle1, double angle2, double angle3);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_torus(double R1,
                                                           double R2);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_torus_angle(double R1,
                                                                 double R2,
                                                                 double angle);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_torus_two_angle(
    double R1, double R2, double angle1, double angle2);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_torus_three_angle(
    double R1, double R2, double angle1, double angle2, double angle);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_torus_axis2(axis2_t Axes,
                                                                 double R1,
                                                                 double R2);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_torus_axis2_angle(
    axis2_t Axes, double R1, double R2, double angle);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_torus_axis2_two_angle(
    axis2_t Axes, double R1, double R2, double angle1, double angle2);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_torus_axis2_three_angle(
    axis2_t Axes, double R1, double R2, double angle1, double angle2,
    double angle);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_wedge(double dx, double dy,
                                                           double dz,
                                                           double ltx);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_wedge_axis2(
    axis2_t Axes, double dx, double dy, double dz, double ltx);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_wedge_limit(
    double dx, double dy, double dz, double xmin, double zmin, double xmax,
    double zmax);

TOPOCAPICALL topo_shell_t topo_shell_make_shell_from_wedge_axis2_limit(
    axis2_t Axes, double dx, double dy, double dz, double xmin, double zmin,
    double xmax, double zmax);

TOPOCAPICALL int topo_shell_sweep(topo_shell_t ss, topo_wire_t spine,
                                  topo_shape_t **profiles, int count,
                                  int cornerMode);

**/

type Solid struct {
	val C.struct__topo_solid_t
}

/**

TOPOCAPICALL int topo_solid_num_solids(topo_solid_t s);

TOPOCAPICALL int topo_solid_num_faces(topo_solid_t s);

TOPOCAPICALL double topo_solid_area(topo_solid_t s);

TOPOCAPICALL double topo_solid_volume(topo_solid_t s);

TOPOCAPICALL bbox_t topo_solid_inertia(topo_solid_t s);

TOPOCAPICALL pnt3d_t topo_solid_centre_of_mass(topo_solid_t s);

TOPOCAPICALL int topo_solid_extrude(topo_solid_t s, topo_face_t f, pnt3d_t p1,
                                    pnt3d_t p2);

TOPOCAPICALL int topo_solid_extrude_from_dir(topo_solid_t s, topo_face_t f,
                                             vec3d_t dir);

TOPOCAPICALL int topo_solid_revolve(topo_solid_t s, topo_face_t f, pnt3d_t p1,
                                    pnt3d_t p2, double angle);

TOPOCAPICALL int topo_solid_loft(topo_solid_t s, topo_shape_t **profiles,
                                 int count, _Bool ruled, double tolerance);

TOPOCAPICALL int topo_solid_pipe(topo_solid_t s, topo_face_t f, topo_wire_t w);

TOPOCAPICALL int topo_solid_sweep(topo_solid_t s, topo_wire_t spine,
                                  topo_shape_t **profiles, int count,
                                  int cornerMode);

TOPOCAPICALL int topo_solid_boolean(topo_solid_t s, topo_solid_t tool, int op);

TOPOCAPICALL int topo_solid_fillet(topo_solid_t s, topo_edge_t *edges,
                                   int count, double *radius, int rcount);

TOPOCAPICALL int topo_solid_chamfer(topo_solid_t s, topo_edge_t *edges,
                                    int count, double *distances, int dcount);

TOPOCAPICALL int topo_solid_shelling(topo_solid_t s, topo_face_t *faces,
                                     int count, double offset,
                                     double tolerance);

TOPOCAPICALL int topo_solid_offset(topo_solid_t s, topo_face_t f, double offset,
                                   double tolerance);

TOPOCAPICALL int topo_solid_draft(topo_solid_t s, topo_face_t *faces, int count,
                                  dir3d_t d, double angle, plane_t p);

TOPOCAPICALL int topo_solid_evolved_from_face(topo_solid_t s, topo_face_t Spine,
                                              topo_wire_t Profil);

TOPOCAPICALL int topo_solid_evolved_from_wire(topo_solid_t s, topo_wire_t Spine,
                                              topo_wire_t Profil);

TOPOCAPICALL int topo_solid_feat_prism(topo_solid_t s, topo_face_t f, dir3d_t d,
                                       double height, _Bool fuse);

TOPOCAPICALL int topo_solid_feat_prism_for_range(topo_solid_t s, topo_face_t f,
                                                 dir3d_t d, topo_face_t from,
                                                 topo_face_t end, _Bool fuse);

TOPOCAPICALL int topo_solid_feat_prism_for_until(topo_solid_t s, topo_face_t f,
                                                 dir3d_t d, topo_face_t until,
                                                 _Bool fuse);

TOPOCAPICALL int topo_solid_feat_draft_prism(topo_solid_t s, topo_face_t f,
                                             double angle, double height,
                                             _Bool fuse);

TOPOCAPICALL int
topo_solid_feat_draft_prism_for_range(topo_solid_t s, topo_face_t f,
                                      double angle, topo_face_t from,
                                      topo_face_t end, _Bool fuse);

TOPOCAPICALL int topo_solid_feat_draft_prism_for_until(
    topo_solid_t s, topo_face_t f, double angle, topo_face_t until, _Bool fuse);

TOPOCAPICALL int topo_solid_feat_revol_for_range(topo_solid_t s, topo_face_t f,
                                                 axis1_t Axes, topo_face_t from,
                                                 topo_face_t end, _Bool fuse);

TOPOCAPICALL int topo_solid_feat_revol_for_until(topo_solid_t s, topo_face_t f,
                                                 axis1_t Axes,
                                                 topo_face_t until, _Bool fuse);

TOPOCAPICALL int topo_solid_feat_pipe_for_range(topo_solid_t s, topo_face_t f,
                                                topo_wire_t Spine,
                                                topo_face_t from,
                                                topo_face_t end, _Bool fuse);

TOPOCAPICALL int topo_solid_feat_pipe_for_until(topo_solid_t s, topo_face_t f,
                                                topo_wire_t Spine,
                                                topo_face_t until, _Bool fuse);

TOPOCAPICALL int topo_solid_linear_form(topo_solid_t s, topo_wire_t w,
                                        geom_plane_surface_t *p, dir3d_t d,
                                        dir3d_t d1, _Bool fuse);

TOPOCAPICALL int topo_solid_revolution_form(topo_solid_t s, topo_wire_t w,
                                            geom_plane_surface_t *p,
                                            axis1_t Axes, double h1, double h2,
                                            _Bool fuse);

TOPOCAPICALL topo_face_t topo_solid_section_face(topo_solid_t s, pnt3d_t pnt,
                                                 pnt3d_t nor);

TOPOCAPICALL int topo_solid_convert_to_nurbs(topo_solid_t s);

**/

func (t *Solid) Free() {
	C.topo_solid_free(t.val)
}

/**

TOPOCAPICALL topo_solid_t
topo_shell_make_solid_from_comp_solid(topo_comp_solid_t S);

TOPOCAPICALL topo_solid_t topo_solid_make_solidd_from_shell(topo_shell_t S);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_two_shell(topo_shell_t S1,
                                                               topo_shell_t S2);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_three_shell(
    topo_shell_t S1, topo_shell_t S2, topo_shell_t S3);

TOPOCAPICALL topo_solid_t
topo_shell_make_solid_from_shells(topo_shell_t *shells, int count);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_solid(topo_solid_t So);

TOPOCAPICALL topo_solid_t
topo_shell_make_solid_from_solid_shell(topo_solid_t So, topo_shell_t S);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_faces(topo_face_t *faces,
                                                           int count,
                                                           double tolerance);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_box(double dx, double dy,
                                                         double dz);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_box_point(pnt3d_t P,
                                                               double dx,
                                                               double dy,
                                                               double dz);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_box_two_point(pnt3d_t P1,
                                                                   pnt3d_t P2);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_box_axis2(axis2_t Axes,
                                                               double dx,
                                                               double dy,
                                                               double dz);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_cylinder(double R,
                                                              double H);

TOPOCAPICALL topo_solid_t
topo_shell_make_solid_from_cylinder_angle(double R, double H, double Angle);

TOPOCAPICALL topo_solid_t
topo_shell_make_solid_from_cylinder_axis2(axis2_t Axes, double R, double H);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_cylinder_axis2_angle(
    axis2_t Axes, double R, double H, double Angle);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_cone(double R1, double R2,
                                                          double H);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_cone_angle(double R1,
                                                                double R2,
                                                                double H,
                                                                double angle);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_cone_axis2(axis2_t Axes,
                                                                double R1,
                                                                double R2,
                                                                double H);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_cone_axis2_angle(
    axis2_t Axes, double R1, double R2, double H, double angle);

TOPOCAPICALL topo_solid_t
topo_shell_make_solid_from_revolution(geom_curve_t *Meridian);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_revolution_angle(
    geom_curve_t *Meridian, double angle);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_revolution_limit(
    geom_curve_t *Meridian, double VMin, double VMax);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_revolution_limit_angle(
    geom_curve_t *Meridian, double VMin, double VMax, double angle);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_revolution_axis2(
    axis2_t Axes, geom_curve_t *Meridian);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_revolution_axis2_angle(
    axis2_t Axes, geom_curve_t *Meridian, double angle);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_revolution_axis2_limit(
    axis2_t Axes, geom_curve_t *Meridian, double VMin, double VMax);

TOPOCAPICALL topo_solid_t
topo_shell_make_solid_from_revolution_axis2_limit_angle(axis2_t Axes,
                                                        geom_curve_t *Meridian,
                                                        double VMin,
                                                        double VMax,
                                                        double angle);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_sphere(double R);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_sphere_angle(double R,
                                                                  double angle);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_sphere_two_angle(
    double R, double angle1, double angle2);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_sphere_three_angle(
    double R, double angle1, double angle2, double angle3);

TOPOCAPICALL topo_solid_t
topo_shell_make_solid_from_sphere_center_raduis(pnt3d_t Center, double R);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_sphere_center_angle(
    pnt3d_t Center, double R, double angle);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_sphere_center_two_angle(
    pnt3d_t Center, double R, double angle1, double angle2);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_sphere_center_three_angle(
    pnt3d_t Center, double R, double angle1, double angle2, double angle3);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_sphere_axis2(axis2_t Axis,
                                                                  double R);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_sphere_axis2_angle(
    axis2_t Axis, double R, double angle);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_sphere_axis2_two_angle(
    axis2_t Axis, double R, double angle1, double angle2);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_sphere_axis2_three_angle(
    axis2_t Axis, double R, double angle1, double angle2, double angle3);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_torus(double R1,
                                                           double R2);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_torus_angle(double R1,
                                                                 double R2,
                                                                 double angle);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_torus_two_angle(
    double R1, double R2, double angle1, double angle2);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_torus_three_angle(
    double R1, double R2, double angle1, double angle2, double angle);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_torus_axis2(axis2_t Axes,
                                                                 double R1,
                                                                 double R2);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_torus_axis2_angle(
    axis2_t Axes, double R1, double R2, double angle);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_torus_axis2_two_angle(
    axis2_t Axes, double R1, double R2, double angle1, double angle2);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_torus_axis2_three_angle(
    axis2_t Axes, double R1, double R2, double angle1, double angle2,
    double angle);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_wedge(double dx, double dy,
                                                           double dz,
                                                           double ltx);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_wedge_axis2(
    axis2_t Axes, double dx, double dy, double dz, double ltx);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_wedge_limit(
    double dx, double dy, double dz, double xmin, double zmin, double xmax,
    double zmax);

TOPOCAPICALL topo_solid_t topo_solid_make_solid_from_wedge_axis2_limit(
    axis2_t Axes, double dx, double dy, double dz, double xmin, double zmin,
    double xmax, double zmax);

**/

type Vertex struct {
	val C.struct__topo_vertex_t
}

func (t *Vertex) GetPoint() Point3 {
	return Point3{val: C.topo_vertex_get_point(t.val)}
}

func (t *Vertex) Free() {
	C.topo_vertex_free(t.val)
}

func NewVertex(x, y, z float64) *Vertex {
	return &Vertex{val: C.topo_vertex_new(C.double(x), C.double(y), C.double(z))}
}

type Wire struct {
	val C.struct__topo_wire_t
}

func (t *Wire) Free() {
	C.topo_wire_free(t.val)
}

func (t *Wire) NumVertices() int {
	return int(C.topo_wire_num_vertices(t.val))
}

func (t *Wire) NumEdges() int {
	return int(C.topo_wire_num_edges(t.val))
}

func (t *Wire) IsClosed() bool {
	return bool(C.topo_wire_is_closed(t.val))
}

func (t *Wire) Length() int {
	return int(C.topo_wire_length(t.val))
}

func (t *Wire) ToCurves3d() {
	C.topo_wire_convert_to_curves3d(t.val)
}

func (t *Wire) Project(f Face) int {
	return int(C.topo_wire_project(t.val, f.val))
}

func (t *Wire) Offset(distance float64, joinType int) int {
	return int(C.topo_wire_offset(t.val, C.double(distance), C.int(joinType)))
}

func (t *Wire) Fillet(vertices []Vertex, radius []float64) int {
	vers := make([]C.struct__topo_vertex_t, len(vertices))
	for i := range vertices {
		vers[i] = vertices[i].val
	}
	return int(C.topo_wire_fillet(t.val, &vers[0], C.int(len(vertices)), (*C.double)(unsafe.Pointer(&radius[0])), C.int(len(radius))))
}

func (t *Wire) Chamfer(vertices []Vertex, radius []float64) int {
	vers := make([]C.struct__topo_vertex_t, len(vertices))
	for i := range vertices {
		vers[i] = vertices[i].val
	}
	return int(C.topo_wire_chamfer(t.val, &vers[0], C.int(len(vertices)), (*C.double)(unsafe.Pointer(&radius[0])), C.int(len(radius))))
}

func TopoMakePolygon() *Wire {
	return &Wire{val: C.topo_make_polygon()}
}

func TopoMakePolygonFromTwoPoint(p1, p2 Point3) *Wire {
	return &Wire{val: C.topo_make_polygon_from_two_point(p1.val, p2.val)}
}

func TopoMakePolygonFromThreePoint(p1, p2, p3 Point3, Close bool) *Wire {
	return &Wire{val: C.topo_make_polygon_from_three_point(p1.val, p2.val, p3.val, C.bool(Close))}
}

func TopoMakePolygonFromFourPoint(p1, p2, p3, p4 Point3, Close bool) *Wire {
	return &Wire{val: C.topo_make_polygon_from_four_point(p1.val, p2.val, p3.val, p4.val, C.bool(Close))}
}

func TopoMakePolygonFromTwoVertex(p1, p2 Vertex) *Wire {
	return &Wire{val: C.topo_make_polygon_two_vertex(p1.val, p2.val)}
}

func TopoMakePolygonFromThreeVertex(p1, p2, p3 Vertex, Close bool) *Wire {
	return &Wire{val: C.topo_make_polygon_from_three_vertex(p1.val, p2.val, p3.val, C.bool(Close))}
}

func TopoMakePolygonFromFourVertex(p1, p2, p3, p4 Vertex, Close bool) *Wire {
	return &Wire{val: C.topo_make_polygon_from_four_vertex(p1.val, p2.val, p3.val, p4.val, C.bool(Close))}
}

func TopoMakeWireFromEdge(p Edge) *Wire {
	return &Wire{val: C.topo_make_wire_from_edge(p.val)}
}

func TopoMakeWireFromTwoEdge(p1, p2 Edge) *Wire {
	return &Wire{val: C.topo_make_wire_from_two_edge(p1.val, p2.val)}
}

func TopoMakeWireFromThreeEdge(p1, p2, p3 Edge) *Wire {
	return &Wire{val: C.topo_make_wire_from_three_edge(p1.val, p2.val, p3.val)}
}

func TopoMakeWireFromFourEdge(p1, p2, p3, p4 Edge) *Wire {
	return &Wire{val: C.topo_make_wire_from_four_edge(p1.val, p2.val, p3.val, p4.val)}
}

func TopoMakeWireFromWire(p Wire) *Wire {
	return &Wire{val: C.topo_make_wire_from_wire(p.val)}
}

func TopoMakeWireFromTwoWire(p1 Wire, p2 Edge) *Wire {
	return &Wire{val: C.topo_make_wire_from_two_wire(p1.val, p2.val)}
}

func TopoMakeWireFromEdges(edges []Edge) *Wire {
	es := make([]C.struct__topo_edge_t, len(edges))
	for i := range edges {
		es[i] = edges[i].val
	}
	return &Wire{val: C.topo_make_wire_from_edges(&es[0], C.int(len(edges)))}
}

func TopoMakeWireFromWires(wires []Wire) *Wire {
	es := make([]C.struct__topo_wire_t, len(wires))
	for i := range wires {
		es[i] = wires[i].val
	}
	return &Wire{val: C.topo_make_wire_from_wries(&es[0], C.int(len(wires)))}
}
