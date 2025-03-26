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
import "runtime"

type Shell struct {
	inner *innerShell
}

type innerShell struct {
	val C.struct__topo_shell_t
}

func TopoMakeShell() *Shell {
	p := &Shell{inner: &innerShell{val: C.topo_make_shell()}}
	runtime.SetFinalizer(p.inner, (*innerShell).free)
	return p
}

func (s *Shell) Sweep(spine *Wire, profiles []Shape, cornerMode int) int {
	cshp := make([]*C.struct__topo_shape_t, len(profiles))
	for i := range profiles {
		cshp[i] = profiles[i].inner.val
	}
	return int(C.topo_shell_sweep(s.inner.val, spine.inner.val, &cshp[0], C.int(len(profiles)), C.int(cornerMode)))
}

func (t *Shell) ToShape() *Shape {
	sp := &Shape{inner: &innerShape{val: C.topo_shape_share(t.inner.val.shp)}}
	runtime.SetFinalizer(sp.inner, (*innerShape).free)
	return sp
}

func (t *innerShell) free() {
	C.topo_shell_free(t.val)
}

func TopoMakeShellFromSurface(S *GeomSurface, Segment bool) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_surface(S.inner.geom, C.bool(Segment))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromSurfaceFromSurfaceParm(S *GeomSurface, UMin, UMax, VMin, VMax float64, Segment bool) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_surface_p(S.inner.geom, C.double(UMin), C.double(UMax), C.double(VMin), C.double(VMax), C.bool(Segment))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromBox(dx, dy, dz float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_box(C.double(dx), C.double(dy), C.double(dz))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromBoxPoint(p Point3, dx, dy, dz float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_box_point(p.val, C.double(dx), C.double(dy), C.double(dz))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromBoxTwoPoint(p1, p2 Point3) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_box_two_point(p1.val, p2.val)}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromBoxAxis2(a Axis2, dx, dy, dz float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_box_axis2(a.val, C.double(dx), C.double(dy), C.double(dz))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromCylinder(R, H float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_cylinder(C.double(R), C.double(H))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromCylinderAngle(R, H, Angle float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_cylinder_angle(C.double(R), C.double(H), C.double(Angle))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromCylinderAxis2(a Axis2, R, H float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_cylinder_axis2(a.val, C.double(R), C.double(H))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromCylinderAxis2Angle(a Axis2, R, H, Angle float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_cylinder_axis2_angle(a.val, C.double(R), C.double(H), C.double(Angle))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromCone(R1, R2, H float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_cone(C.double(R1), C.double(R2), C.double(H))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromConeAngle(R1, R2, H, Angle float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_cone_angle(C.double(R1), C.double(R2), C.double(H), C.double(Angle))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromConeAxis2(a Axis2, R1, R2, H float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_cone_axis2(a.val, C.double(R1), C.double(R2), C.double(H))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromConeAxis2Angle(a Axis2, R1, R2, H, Angle float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_cone_axis2_angle(a.val, C.double(R1), C.double(R2), C.double(H), C.double(Angle))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromRevolution(m *GeomCurve) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_revolution(m.inner.geom)}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromRevolutionAngle(m *GeomCurve, Angle float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_revolution_angle(m.inner.geom, C.double(Angle))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromRevolutionLimit(m *GeomCurve, VMin, VMax float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_revolution_limit(m.inner.geom, C.double(VMin), C.double(VMax))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromRevolutionLimitAngle(m *GeomCurve, VMin, VMax, Angle float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_revolution_limit_angle(m.inner.geom, C.double(VMin), C.double(VMax), C.double(Angle))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromRevolutionAxis2(a Axis2, m *GeomCurve) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_revolution_axis2(a.val, m.inner.geom)}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromRevolutionAxis2Angle(a Axis2, m *GeomCurve, Angle float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_revolution_axis2_angle(a.val, m.inner.geom, C.double(Angle))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromRevolutionAxis2Limit(a Axis2, m *GeomCurve, VMin, VMax float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_revolution_axis2_limit(a.val, m.inner.geom, C.double(VMin), C.double(VMax))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromRevolutionAxis2LimitAngle(a Axis2, m *GeomCurve, VMin, VMax, Angle float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_revolution_axis2_limit_angle(a.val, m.inner.geom, C.double(VMin), C.double(VMax), C.double(Angle))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromSpere(R float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_sphere(C.double(R))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromSpereAngle(R float64, Angle float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_sphere_angle(C.double(R), C.double(Angle))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromSpereTwoAngle(R float64, Angle1, Angle2 float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_sphere_two_angle(C.double(R), C.double(Angle1), C.double(Angle2))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromSpereThreeAngle(R float64, Angle1, Angle2, Angle3 float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_sphere_three_angle(C.double(R), C.double(Angle1), C.double(Angle2), C.double(Angle3))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromSpereCenterRaduis(Center Point3, R float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_sphere_center_raduis(Center.val, C.double(R))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromSpereCenterAngle(Center Point3, R, Angle float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_sphere_center_angle(Center.val, C.double(R), C.double(Angle))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromSpereCenterTwoAngle(Center Point3, R, Angle1, Angle2 float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_sphere_center_two_angle(Center.val, C.double(R), C.double(Angle1), C.double(Angle2))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromSpereCenterThreeAngle(Center Point3, R, Angle1, Angle2, Angle3 float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_sphere_center_three_angle(Center.val, C.double(R), C.double(Angle1), C.double(Angle2), C.double(Angle3))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromSpereAxis2(a Axis2, R float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_sphere_axis2(a.val, C.double(R))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromSpereAxis2Angle(a Axis2, R, Angle float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_sphere_axis2_raduis(a.val, C.double(R), C.double(Angle))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromSpereAxis2TwoAngle(a Axis2, R, Angle1, Angle2 float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_sphere_axis2_two_angle(a.val, C.double(R), C.double(Angle1), C.double(Angle2))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromSpereAxis2ThreeAngle(a Axis2, R, Angle1, Angle2, Angle3 float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_sphere_axis2_three_angle(a.val, C.double(R), C.double(Angle1), C.double(Angle2), C.double(Angle3))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromTorus(R1, R2 float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_torus(C.double(R1), C.double(R2))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromTorusAngle(R1, R2, Angle float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_torus_angle(C.double(R1), C.double(R2), C.double(Angle))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromTorusTwoAngle(R1, R2, Angle1, Angle2 float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_torus_two_angle(C.double(R1), C.double(R2), C.double(Angle1), C.double(Angle2))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromTorusThreeAngle(R1, R2, Angle1, Angle2, Angle3 float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_torus_three_angle(C.double(R1), C.double(R2), C.double(Angle1), C.double(Angle2), C.double(Angle3))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromTorusAxis2(a Axis2, R1, R2 float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_torus_axis2(a.val, C.double(R1), C.double(R2))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromTorusAxis2Angle(a Axis2, R1, R2, Angle float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_torus_axis2_angle(a.val, C.double(R1), C.double(R2), C.double(Angle))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromTorusAxis2TwoAngle(a Axis2, R1, R2, Angle1, Angle2 float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_torus_axis2_two_angle(a.val, C.double(R1), C.double(R2), C.double(Angle1), C.double(Angle2))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromTorusAxis2ThreeAngle(a Axis2, R1, R2, Angle1, Angle2, Angle3 float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_torus_axis2_three_angle(a.val, C.double(R1), C.double(R2), C.double(Angle1), C.double(Angle2), C.double(Angle3))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromWedge(dx, dy, dz, ltx float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_wedge(C.double(dx), C.double(dy), C.double(dz), C.double(ltx))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromWedgeAxis2(a Axis2, dx, dy, dz, ltx float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_wedge_axis2(a.val, C.double(dx), C.double(dy), C.double(dz), C.double(ltx))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromWedgeLimit(dx, dy, dz, xmin, zmin, xmax, zmax float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_wedge_limit(C.double(dx), C.double(dy), C.double(dz), C.double(xmin), C.double(zmin), C.double(xmax), C.double(zmax))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

func TopoMakeShellFromWedgeAxis2Limit(a Axis2, dx, dy, dz, xmin, zmin, xmax, zmax float64) *Shell {
	sh := &Shell{inner: &innerShell{val: C.topo_shell_make_shell_from_wedge_axis2_limit(a.val, C.double(dx), C.double(dy), C.double(dz), C.double(xmin), C.double(zmin), C.double(xmax), C.double(zmax))}}
	runtime.SetFinalizer(sh.inner, (*innerShell).free)
	return sh
}

type ShellIterator struct {
	inner *innerShellIterator
}
type innerShellIterator struct {
	val *C.struct__topo_shell_iterator_t
}

func TopoMakeShellIterator(p Shape) *ShellIterator {
	wr := &ShellIterator{inner: &innerShellIterator{val: C.topo_shell_iterator_make(p.inner.val)}}
	runtime.SetFinalizer(wr.inner, (*innerShellIterator).free)
	return wr
}

func (t *innerShellIterator) free() {
	C.topo_shell_iterator_free(t.val)
}

func (t *ShellIterator) Next() *Shell {
	v := C.topo_shell_iterator_next(t.inner.val)
	if v != nil {
		var val C.struct__topo_shell_t
		val.shp = v
		p := &Shell{inner: &innerShell{val: val}}
		runtime.SetFinalizer(p.inner, (*innerShell).free)
		return p
	}
	return nil
}
