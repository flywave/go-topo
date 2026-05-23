package topo

import (
	"testing"
)

func TestGeomConstants(t *testing.T) {
	if GEOMLINE == 0 || GEOMCIRCLE == 0 {
		t.Fatal("geom constants not set")
	}
	if GEOM2DLINE == 0 || GEOM2DCIRCLE == 0 {
		t.Fatal("geom2d constants not set")
	}
}

func TestGeomMakeDirection(t *testing.T) {
	d := GeomMakeDirection(1, 0, 0)
	if d == nil {
		t.Fatal("GeomMakeDirection returned nil")
	}
	d2 := GeomMakeDirectionFromDir(NewDir3FromXYZ([3]float64{0, 1, 0}))
	if d2 == nil {
		t.Fatal("GeomMakeDirectionFromDir returned nil")
	}
}

func TestGeomMakeVector(t *testing.T) {
	v := GeomMakeVectorWithMagnitude(1, 0, 0)
	if v == nil {
		t.Fatal("GeomMakeVectorWithMagnitude returned nil")
	}
	v2 := GeomMakeVectorWithMagnitudeFromVector(NewVector3([3]float64{10, 0, 0}))
	if v2 == nil {
		t.Fatal("GeomMakeVectorWithMagnitudeFromVector returned nil")
	}
	P1 := NewPoint3([3]float64{0, 0, 0})
	P2 := NewPoint3([3]float64{10, 0, 0})
	v3 := GeomMakeVectorWithMagnitudeFromPoint(P1, P2)
	if v3 == nil {
		t.Fatal("GeomMakeVectorWithMagnitudeFromPoint returned nil")
	}
}

func TestGeomMakeAxisPlacement(t *testing.T) {
	a1 := GeomMakeAxis1PlacementFromPointDir(
		NewPoint3([3]float64{0, 0, 0}), NewDir3FromXYZ([3]float64{0, 0, 1}))
	if a1 == nil {
		t.Fatal("GeomMakeAxis1PlacementFromPointDir returned nil")
	}
	a2 := GeomMakeAxis2PlacementForPointNVX(
		NewPoint3([3]float64{0, 0, 0}),
		NewDir3FromXYZ([3]float64{0, 0, 1}),
		NewDir3FromXYZ([3]float64{1, 0, 0}))
	if a2 == nil {
		t.Fatal("GeomMakeAxis2PlacementForPointNVX returned nil")
	}
}

func TestGeomMakeArcOfPoint(t *testing.T) {
	c := GeomMakeArcOfPoint(
		NewPoint3([3]float64{0, 0, 0}),
		NewPoint3([3]float64{5, 5, 0}),
		NewPoint3([3]float64{10, 0, 0}))
	if c == nil {
		t.Fatal("GeomMakeArcOfPoint returned nil")
	}
}

func TestGeomMakeBezier(t *testing.T) {
	pts := []Point3{
		NewPoint3([3]float64{0, 0, 0}),
		NewPoint3([3]float64{5, 10, 0}),
		NewPoint3([3]float64{10, 0, 0}),
	}
	c := GeomMakeBezierCurve(pts)
	if c == nil {
		t.Fatal("GeomMakeBezierCurve returned nil")
	}
}

func TestGeomMakeSurface(t *testing.T) {
	pts := [][]Point3{
		{NewPoint3([3]float64{0, 0, 0}), NewPoint3([3]float64{10, 0, 0})},
		{NewPoint3([3]float64{0, 10, 0}), NewPoint3([3]float64{10, 10, 0})},
	}
	s := GeomMakeBezierSurface(pts)
	if s == nil {
		t.Fatal("GeomMakeBezierSurface returned nil")
	}
}

func TestGeomMakeSegment(t *testing.T) {
	c := GeomMakeSegmentOfTwoPoint(NewPoint3([3]float64{0, 0, 0}), NewPoint3([3]float64{10, 0, 0}))
	if c == nil {
		t.Fatal("GeomMakeSegmentOfTwoPoint returned nil")
	}
}

func TestGeomMakeLine(t *testing.T) {
	l := GeomMakeLineOfTwoPoint(NewPoint3([3]float64{0, 0, 0}), NewPoint3([3]float64{10, 0, 0}))
	if l == nil {
		t.Fatal("GeomMakeLineOfTwoPoint returned nil")
	}
	l2 := GeomMakeLineOfPointDir(NewPoint3([3]float64{0, 0, 0}), NewDir3FromXYZ([3]float64{1, 0, 0}))
	if l2 == nil {
		t.Fatal("GeomMakeLineOfPointDir returned nil")
	}
}

func TestGeomMakeCircle(t *testing.T) {
	c := GeomMakeCircleOfThreePoint(
		NewPoint3([3]float64{-5, 0, 0}), NewPoint3([3]float64{0, 5, 0}), NewPoint3([3]float64{5, 0, 0}))
	if c == nil {
		t.Fatal("GeomMakeCircleOfThreePoint returned nil")
	}
	c2 := GeomMakeCircleOfCenterNorm(NewPoint3([3]float64{0, 0, 0}), NewDir3FromXYZ([3]float64{0, 0, 1}), 5)
	if c2 == nil {
		t.Fatal("GeomMakeCircleOfCenterNorm returned nil")
	}
}

func TestGeomMakeEllipse(t *testing.T) {
	a := NewAxis2FromNVX(NewPoint3([3]float64{0, 0, 0}),
		NewDir3FromXYZ([3]float64{0, 0, 1}), NewDir3FromXYZ([3]float64{1, 0, 0}))
	e := GeomMakeEllipseOfAxis2(a, 10, 5)
	if e == nil {
		t.Fatal("GeomMakeEllipseOfAxis2 returned nil")
	}
}

func TestGeomMakePlane(t *testing.T) {
	p := GeomMakePlaneOfPointDir(NewPoint3([3]float64{0, 0, 0}), NewDir3FromXYZ([3]float64{0, 0, 1}))
	if p == nil {
		t.Fatal("GeomMakePlaneOfPointDir returned nil")
	}
}

func TestGeomMakeTransform(t *testing.T) {
	r := GeomMakeRotationOfPointDir(
		NewPoint3([3]float64{0, 0, 0}), NewDir3FromXYZ([3]float64{0, 0, 1}), 45)
	if r == nil {
		t.Fatal("GeomMakeRotationOfPointDir returned nil")
	}
	tv := GeomMakeTranslationOfVector(NewVector3([3]float64{10, 0, 0}))
	if tv == nil {
		t.Fatal("GeomMakeTranslationOfVector returned nil")
	}
}

func TestGeomMakeMirror(t *testing.T) {
	m := GeomMakeMirrorOfAxis2(NewAxis2FromNVX(NewPoint3([3]float64{0, 0, 0}),
		NewDir3FromXYZ([3]float64{0, 0, 1}), NewDir3FromXYZ([3]float64{1, 0, 0})))
	if m == nil {
		t.Fatal("GeomMakeMirrorOfAxis2 returned nil")
	}
}

func TestGeomMakeCylindricalSurface(t *testing.T) {
	a := NewAxis2FromNVX(NewPoint3([3]float64{0, 0, 0}),
		NewDir3FromXYZ([3]float64{0, 0, 1}), NewDir3FromXYZ([3]float64{1, 0, 0}))
	s := GeomMakeCylindricalSurfaceOfAxis2(a, 5)
	if s == nil {
		t.Fatal("GeomMakeCylindricalSurfaceOfAxis2 returned nil")
	}
}




