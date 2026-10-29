package topo

import (
	"math"
	"testing"
)

// TestGeomSurfacesIntersectPlanePlane: two non-parallel planes intersect in
// one straight line through the origin.
func TestGeomSurfacesIntersectPlanePlane(t *testing.T) {
	a := GeomSurfaceMakePlane(NewPoint3([3]float64{0, 0, 0}), NewDir3FromXYZ([3]float64{0, 0, 1}))
	b := GeomSurfaceMakePlane(NewPoint3([3]float64{0, 0, 0}), NewDir3FromXYZ([3]float64{1, 0, 0}))
	if a == nil || b == nil {
		t.Fatal("surface construction failed")
	}
	curves := GeomSurfacesIntersect(a, b, 1e-7)
	if len(curves) != 1 {
		t.Fatalf("intersection curves = %d, want 1", len(curves))
	}
	c := curves[0]
	// the line is the y axis: projecting (0,2,0) must land on it
	u, ok := c.ProjectParam(NewPoint3([3]float64{0, 2, 0}))
	if !ok {
		t.Fatal("projection failed")
	}
	p := c.ValueAt(u).Data()
	if math.Abs(p[0]) > 1e-6 || math.Abs(p[2]) > 1e-6 || math.Abs(p[1]-2) > 1e-6 {
		t.Fatalf("projected point = %v, want (0,2,0)", p)
	}
	if e := TopoMakeEdgeFromCurveParm(c, u-1, u+1); e == nil || e.IsNull() {
		t.Fatal("edge from curve parameter range failed")
	}
}

// TestGeomSurfacesIntersectPlaneCylinder: a plane cutting a cylinder
// perpendicular to its axis yields circles (2 boundary curves on the
// infinite cylinder are separate results only when they exist; the y=0
// through-axis plane yields 2 lines).
func TestGeomSurfacesIntersectPlaneCylinder(t *testing.T) {
	cy := GeomSurfaceMakeCylinder(
		NewAxis2(NewPoint3([3]float64{0, 0, 0}), NewDir3FromXYZ([3]float64{0, 0, 1})), 2)
	pl := GeomSurfaceMakePlane(NewPoint3([3]float64{0, 0, 0}), NewDir3FromXYZ([3]float64{0, 1, 0}))
	curves := GeomSurfacesIntersect(cy, pl, 1e-7)
	if len(curves) != 2 {
		t.Fatalf("intersection curves = %d, want 2 (the x=±2 lines)", len(curves))
	}
	// every point of every curve must lie on BOTH surfaces: check radius 2
	// (the lines are infinite — bound them by projecting a known point)
	for i := range curves {
		u, ok := curves[i].ProjectParam(NewPoint3([3]float64{2, 0, 0.5}))
		if !ok {
			t.Fatalf("curve %d projection failed", i)
		}
		for k := -4; k <= 4; k++ {
			p := curves[i].ValueAt(u + float64(k)*0.25).Data()
			r := math.Hypot(p[0], p[1])
			if math.Abs(r-2) > 1e-6 {
				t.Fatalf("curve %d point %v radius %f, want 2", i, p, r)
			}
			if math.Abs(p[1]) > 1e-6 {
				t.Fatalf("curve %d point %v not on plane y=0", i, p)
			}
		}
	}
}

// TestGeomSurfacesIntersectParallel: two parallel planes do not intersect.
func TestGeomSurfacesIntersectParallel(t *testing.T) {
	a := GeomSurfaceMakePlane(NewPoint3([3]float64{0, 0, 0}), NewDir3FromXYZ([3]float64{0, 0, 1}))
	b := GeomSurfaceMakePlane(NewPoint3([3]float64{0, 0, 5}), NewDir3FromXYZ([3]float64{0, 0, 1}))
	if curves := GeomSurfacesIntersect(a, b, 1e-7); len(curves) != 0 {
		t.Fatalf("parallel planes curves = %d, want 0", len(curves))
	}
}

// TestMakeEdgeCurveVertsTol: an edge on the exact y-axis line whose vertices
// sit 0.05 OFF the line — the deviation lands in the edge tolerance while
// the vertices stay at the given points.
func TestMakeEdgeCurveVertsTol(t *testing.T) {
	line := GeomMakeLineOfPointDir(NewPoint3([3]float64{0, 0, 0}), NewDir3FromXYZ([3]float64{0, 1, 0}))
	if line == nil {
		t.Fatal("line construction failed")
	}
	curve := *line.Curve()
	p1 := NewPoint3([3]float64{0.05, -1, 0})
	p2 := NewPoint3([3]float64{-0.04, 2, 0})
	e := MakeEdgeCurveVertsTol(curve, p1, p2, -3, 2, 0.1)
	if e == nil || e.IsNull() {
		t.Fatal("edge construction failed")
	}
	// StartPoint/EndPoint report the CURVE points at the parameter range
	// (the exact y axis); the vertices sit at the input points p1/p2 and
	// carry the deviation — that split is what wire building and sewing
	// rely on.
	q1 := e.StartPoint().Data()
	q2 := e.EndPoint().Data()
	if math.Abs(q1[0]) > 1e-9 || math.Abs(q1[2]) > 1e-9 ||
		math.Abs(q1[1]+3) > 1e-9 || math.Abs(q2[0]) > 1e-9 ||
		math.Abs(q2[2]) > 1e-9 || math.Abs(q2[1]-2) > 1e-9 {
		t.Fatalf("curve endpoints = %v %v, want on the y axis at -3/2", q1, q2)
	}
	// the parameter range follows the requested curve span
	lo, hi := e.Bounds()
	if math.Abs(lo+3) > 1e-6 || math.Abs(hi-2) > 1e-6 {
		t.Fatalf("edge bounds = (%f,%f), want (-3,2)", lo, hi)
	}
}
