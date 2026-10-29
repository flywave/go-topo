package topo

/*
#include "topo_c_api.h"
*/
import "C"

import (
	"runtime"
	"unsafe"
)

// Analytic surface intersection (GeomAPI_IntSS — the OdGeSurfacesIntersector
// equivalent, scanbim B-1): build Geom surfaces from primitive parameters,
// intersect exactly, and inspect the resulting curves. The shared edge for a
// boundary chain is then built with TopoMakeEdgeFromCurveParm between the
// projected parameters of the chain's corner vertices.

// GeomSurfaceMakePlane wraps a point+normal plane as a Geom surface.
func GeomSurfaceMakePlane(p Point3, d Dir3) *GeomSurface {
	g := C.geom_surface_make_plane(p.val, d.val)
	if g == nil {
		return nil
	}
	s := &GeomSurface{inner: &innerGeomSurface{geom: g}}
	runtime.SetFinalizer(s.inner, (*innerGeomSurface).free)
	return s
}

// GeomSurfaceMakeCylinder wraps an axis2+radius cylinder as a Geom surface.
func GeomSurfaceMakeCylinder(a Axis2, radius float64) *GeomSurface {
	g := C.geom_surface_make_cylinder(a.val, C.double(radius))
	if g == nil {
		return nil
	}
	s := &GeomSurface{inner: &innerGeomSurface{geom: g}}
	runtime.SetFinalizer(s.inner, (*innerGeomSurface).free)
	return s
}

// GeomSurfaceMakeSphere wraps an axis3+radius sphere as a Geom surface.
func GeomSurfaceMakeSphere(a Axis3, radius float64) *GeomSurface {
	g := C.geom_surface_make_sphere(a.val, C.double(radius))
	if g == nil {
		return nil
	}
	s := &GeomSurface{inner: &innerGeomSurface{geom: g}}
	runtime.SetFinalizer(s.inner, (*innerGeomSurface).free)
	return s
}

// GeomSurfaceMakeCone wraps an axis2 cone (half-angle in radians, reference
// radius) as a Geom surface.
func GeomSurfaceMakeCone(a Axis2, halfAngle, radius float64) *GeomSurface {
	g := C.geom_surface_make_cone(a.val, C.double(halfAngle), C.double(radius))
	if g == nil {
		return nil
	}
	s := &GeomSurface{inner: &innerGeomSurface{geom: g}}
	runtime.SetFinalizer(s.inner, (*innerGeomSurface).free)
	return s
}

// GeomSurfacesIntersect returns the exact analytic intersection curves of
// two surfaces (empty when the surfaces do not intersect or OCCT fails).
func GeomSurfacesIntersect(a, b *GeomSurface, tol float64) []GeomCurve {
	if a == nil || b == nil || a.inner == nil || b.inner == nil {
		return nil
	}
	var out **C.geom_curve_t
	n := int(C.topo_geom_surfaces_intersect(a.inner.geom, b.inner.geom,
		C.double(tol), &out))
	if n <= 0 || out == nil {
		return nil
	}
	curves := unsafe.Slice(out, n)
	defer C.topo_geom_curve_ptr_array_free(out)
	res := make([]GeomCurve, 0, n)
	for _, c := range curves {
		if c == nil {
			continue
		}
		g := &GeomCurve{inner: &innerGeomCurve{geom: c}}
		runtime.SetFinalizer(g.inner, (*innerGeomCurve).free)
		res = append(res, *g)
	}
	return res
}

// noParamProj is the sentinel topo_geom_curve_project_param returns when the
// projection has no solution.
const noParamProj = 1e308

// ProjectParam returns the curve parameter of the closest point to p
// (ok=false when the projection fails).
func (g *GeomCurve) ProjectParam(p Point3) (float64, bool) {
	if g == nil || g.inner == nil {
		return 0, false
	}
	u := float64(C.topo_geom_curve_project_param(g.inner.geom, p.val))
	if u >= noParamProj {
		return 0, false
	}
	return u, true
}

// ParamRange returns the curve's natural parameter bounds.
func (g *GeomCurve) ParamRange() (float64, float64, bool) {
	if g == nil || g.inner == nil {
		return 0, 0, false
	}
	var u0, u1 C.double
	if C.topo_geom_curve_param_range(g.inner.geom, &u0, &u1) == 0 {
		return 0, 0, false
	}
	return float64(u0), float64(u1), true
}

// ValueAt evaluates the 3D curve point at parameter u.
func (g *GeomCurve) ValueAt(u float64) Point3 {
	if g == nil || g.inner == nil {
		return Point3{}
	}
	p := C.topo_geom_curve_value(g.inner.geom, C.double(u))
	return Point3{val: p}
}

// MakeEdgeCurveVertsTol builds an edge on the exact curve between u1/u2
// whose vertices sit at the given 3D points, absorbing up to tol of
// point-to-curve deviation into the vertex/edge tolerance (scanbim B-1:
// mesh corner vertices + exact intersection curve).
func MakeEdgeCurveVertsTol(c GeomCurve, p1, p2 Point3, u1, u2, tol float64) *Edge {
	if c.inner == nil {
		return nil
	}
	e := &Edge{inner: &innerEdge{val: C.topo_edge_make_edge_curve_verts_tol(
		c.inner.geom, p1.val, p2.val, C.double(u1), C.double(u2), C.double(tol))}}
	runtime.SetFinalizer(e.inner, (*innerEdge).free)
	if e.inner.val.shp == nil {
		return nil
	}
	return e
}

// ParamOf is a Go-side convenience mirroring ProjectParam for raw coords.
func (g *GeomCurve) ParamOf(x, y, z float64) (float64, bool) {
	return g.ProjectParam(NewPoint3([3]float64{x, y, z}))
}
