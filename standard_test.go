package topo

import (
	"math"
	"testing"
)

func TestPoint3(t *testing.T) {
	p := NewPoint3([3]float64{1, 2, 3})
	d := p.Data()
	if d[0] != 1 || d[1] != 2 || d[2] != 3 {
		t.Fatalf("unexpected: %v", d)
	}
}

func TestVector3(t *testing.T) {
	v := NewVector3([3]float64{4, 5, 6})
	d := v.Data()
	if d[0] != 4 || d[1] != 5 || d[2] != 6 {
		t.Fatalf("unexpected: %v", d)
	}
}

func TestDir3(t *testing.T) {
	t.Run("from xyz", func(t *testing.T) {
		d := NewDir3FromXYZ([3]float64{1, 0, 0})
		data := d.Data()
		if math.Abs(data[0]-1) > 1e-6 {
			t.Fatalf("unexpected: %v", data)
		}
	})
	t.Run("from vector", func(t *testing.T) {
		v := NewVector3([3]float64{0, 1, 0})
		d := NewDir3FromVector(v)
		_ = d.Data()
	})
	t.Run("from point", func(t *testing.T) {
		d := NewDir3FromPoint(NewPoint3([3]float64{0, 0, 0}), NewPoint3([3]float64{0, 1, 0}))
		data := d.Data()
		if math.Abs(data[1]-1) > 1e-6 {
			t.Fatalf("unexpected: %v", data)
		}
	})
}

func TestXYPoint2Vector2(t *testing.T) {
	t.Run("xy", func(t *testing.T) {
		xy := NewXY([2]float64{1, 2})
		d := xy.Data()
		if d[0] != 1 || d[1] != 2 {
			t.Fatalf("unexpected: %v", d)
		}
	})
	t.Run("point2", func(t *testing.T) {
		p := NewPoint2([2]float64{3, 4})
		d := p.Data()
		if d[0] != 3 || d[1] != 4 {
			t.Fatalf("unexpected: %v", d)
		}
	})
	t.Run("vector2", func(t *testing.T) {
		v := NewVector2([2]float64{5, 6})
		d := v.Data()
		if d[0] != 5 || d[1] != 6 {
			t.Fatalf("unexpected: %v", d)
		}
	})
}

func TestDir2(t *testing.T) {
	t.Run("from xy", func(t *testing.T) {
		d := NewDir2([2]float64{1, 0})
		_ = d.Data()
	})
	t.Run("from vector", func(t *testing.T) {
		v := NewVector2([2]float64{0, 1})
		d := NewDir2FromVector(v)
		_ = d.Data()
	})
	t.Run("from point", func(t *testing.T) {
		d := NewDir2FromPoint(NewPoint2([2]float64{0, 0}), NewPoint2([2]float64{1, 0}))
		_ = d.Data()
	})
}

func TestAxis1(t *testing.T) {
	a := NewAxis1(NewPoint3([3]float64{0, 0, 0}), NewDir3FromXYZ([3]float64{0, 0, 1}))
	p := a.Point()
	d := a.Dir()
	_ = p
	_ = d
}

func TestAxis2(t *testing.T) {
	t.Run("from nvx", func(t *testing.T) {
		a := NewAxis2FromNVX(NewPoint3([3]float64{0, 0, 0}),
			NewDir3FromXYZ([3]float64{0, 0, 1}), NewDir3FromXYZ([3]float64{1, 0, 0}))
		_ = a.Axis()
		_ = a.DirX()
		_ = a.DirY()
	})
	t.Run("from name", func(t *testing.T) {
		a := NewxAxis2FromName("XY", NewPoint3([3]float64{0, 0, 0}))
		_ = a.Axis()
	})
}

func TestAxis3(t *testing.T) {
	a := NewAxis3FromV(NewPoint3([3]float64{0, 0, 0}), NewDir3FromXYZ([3]float64{0, 0, 1}))
	_ = a.Axis()
	_ = a.DirX()
	_ = a.DirY()
	a2 := NewAxis3(NewAxis2FromNVX(NewPoint3([3]float64{0, 0, 0}),
		NewDir3FromXYZ([3]float64{0, 0, 1}), NewDir3FromXYZ([3]float64{1, 0, 0})))
	_ = a2
}

func TestAxis2d(t *testing.T) {
	a := NewAxis2d(NewPoint2([2]float64{0, 0}), NewDir2([2]float64{1, 0}))
	_ = a.Point()
	_ = a.Dir()
}

func TestAxis22d(t *testing.T) {
	a2d := NewAxis2d(NewPoint2([2]float64{0, 0}), NewDir2([2]float64{1, 0}))
	a := NewAxis22d(a2d)
	_ = a.Point()
	_ = a.DirX()
	_ = a.DirY()
	a2 := NewAxis22dFromV(NewPoint2([2]float64{0, 0}), NewDir2([2]float64{1, 0}))
	_ = a2
	a3 := NewAxis22dFromVXY(NewPoint2([2]float64{0, 0}), NewDir2([2]float64{1, 0}), NewDir2([2]float64{0, 1}))
	_ = a3
}

func TestCirc(t *testing.T) {
	t.Run("from axis2", func(t *testing.T) {
		a := NewAxis2FromNVX(NewPoint3([3]float64{0, 0, 0}),
			NewDir3FromXYZ([3]float64{0, 0, 1}), NewDir3FromXYZ([3]float64{1, 0, 0}))
		c := NewCircFromAxis2(a, 5)
		if c.Radius() != 5 {
			t.Fatalf("expected radius 5, got %f", c.Radius())
		}
	})
	t.Run("from 3 points", func(t *testing.T) {
		c := NewCircFromPoint(
			NewPoint3([3]float64{-5, 0, 0}),
			NewPoint3([3]float64{0, 5, 0}),
			NewPoint3([3]float64{5, 0, 0}),
		)
		_ = c.Radius()
	})
	t.Run("from center normal", func(t *testing.T) {
		c := NewCircFromCenterNorm(NewPoint3([3]float64{0, 0, 0}), NewDir3FromXYZ([3]float64{0, 0, 1}), 5)
		_ = c
	})
}

func TestCirc2d(t *testing.T) {
	c := NewCirc2dFromCenterRadius(NewPoint2([2]float64{0, 0}), 5)
	_ = c.Radius()
	_ = c.Axis()
}

func TestLine(t *testing.T) {
	l := NewLineFromPointDir(NewPoint3([3]float64{0, 0, 0}), NewDir3FromXYZ([3]float64{1, 0, 0}))
	_ = l
	l2 := NewLineFromPoint(NewPoint3([3]float64{0, 0, 0}), NewPoint3([3]float64{10, 0, 0}))
	_ = l2
}

func TestLine2d(t *testing.T) {
	l := NewLine2dFromPointDir(NewPoint2([2]float64{0, 0}), NewDir2([2]float64{1, 0}))
	_ = l
}

func TestPlane(t *testing.T) {
	p := NewPlaneFromPointDir(NewPoint3([3]float64{0, 0, 0}), NewDir3FromXYZ([3]float64{0, 0, 1}))
	_ = p
}

func TestCone(t *testing.T) {
	a := NewAxis2FromNVX(NewPoint3([3]float64{0, 0, 0}),
		NewDir3FromXYZ([3]float64{0, 0, 1}), NewDir3FromXYZ([3]float64{1, 0, 0}))
	c := NewConeFromAxis2(a, 30, 5)
	_ = c.Axis()
	_ = c.Angle()
	_ = c.Radius()
}

func TestCylinderGeom(t *testing.T) {
	a := NewAxis2FromNVX(NewPoint3([3]float64{0, 0, 0}),
		NewDir3FromXYZ([3]float64{0, 0, 1}), NewDir3FromXYZ([3]float64{1, 0, 0}))
	c := NewCylinderFromAxis2(a, 5)
	_ = c.Axis()
	_ = c.Radius()
}

func TestElips(t *testing.T) {
	a := NewAxis2FromNVX(NewPoint3([3]float64{0, 0, 0}),
		NewDir3FromXYZ([3]float64{0, 0, 1}), NewDir3FromXYZ([3]float64{1, 0, 0}))
	e := NewElipsFromAxis2Radius(a, 10, 5)
	if e.MajorRadius() != 10 || e.MinorRadius() != 5 {
		t.Fatalf("unexpected radii: %f, %f", e.MajorRadius(), e.MinorRadius())
	}
	_ = e.Axis()

	e2 := NewElipsFromPoint(NewPoint3([3]float64{-10, 0, 0}), NewPoint3([3]float64{10, 0, 0}), NewPoint3([3]float64{0, 0, 0}))
	_ = e2
}

func TestElips2d(t *testing.T) {
	a := NewAxis2d(NewPoint2([2]float64{0, 0}), NewDir2([2]float64{1, 0}))
	e := NewElips2dFromAxis2dRadius(a, 10, 5)
	_ = e.MajorRadius()
	_ = e.MinorRadius()
	_ = e.Axis()
}

func TestHyperbola(t *testing.T) {
	a := NewAxis2FromNVX(NewPoint3([3]float64{0, 0, 0}),
		NewDir3FromXYZ([3]float64{0, 0, 1}), NewDir3FromXYZ([3]float64{1, 0, 0}))
	h := NewHyperbolaFromAxis2(a, 10, 5)
	_ = h.Axis()
	_ = h.MajorRadius()
	_ = h.MinorRadius()
}

func TestParabola(t *testing.T) {
	a := NewAxis2FromNVX(NewPoint3([3]float64{0, 0, 0}),
		NewDir3FromXYZ([3]float64{0, 0, 1}), NewDir3FromXYZ([3]float64{1, 0, 0}))
	p := NewParabolaFromAxis2(a, 5)
	_ = p.Axis()
	_ = p.Focal()
}

func TestSphereGeom(t *testing.T) {
	a3 := NewAxis3FromV(NewPoint3([3]float64{0, 0, 0}), NewDir3FromXYZ([3]float64{0, 0, 1}))
	s := NewSphere(a3, 10)
	_ = s.Radius()
}

func TestTorusGeom(t *testing.T) {
	a3 := NewAxis3FromV(NewPoint3([3]float64{0, 0, 0}), NewDir3FromXYZ([3]float64{0, 0, 1}))
	tor := NewTorusFromAxis3(a3, 20, 5)
	_ = tor.MajorRadius()
	_ = tor.MinorRadius()
}

func TestTrsf(t *testing.T) {
	t.Run("identity", func(t *testing.T) {
		tr := NewTrsf(1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0)
		_ = tr
	})
	t.Run("translation", func(t *testing.T) {
		v := NewVector3([3]float64{10, 0, 0})
		tr := NewTrsfTranslationFromVector(v)
		_ = tr
	})
	t.Run("rotation", func(t *testing.T) {
		tr := NewTrsfRotationFromPointDir(
			NewPoint3([3]float64{0, 0, 0}),
			NewDir3FromXYZ([3]float64{0, 0, 1}), 45)
		_ = tr
	})
	t.Run("scale", func(t *testing.T) {
		tr := NewTrsfScaleFromLine(NewPoint3([3]float64{0, 0, 0}), 2)
		_ = tr
	})
}

func TestTrsfMirror(t *testing.T) {
	t.Run("mirror point", func(t *testing.T) {
		tr := NewTrsfMirrorFromPoint(NewPoint3([3]float64{0, 0, 0}))
		_ = tr
	})
	t.Run("mirror axis1", func(t *testing.T) {
		a := NewAxis1(NewPoint3([3]float64{0, 0, 0}), NewDir3FromXYZ([3]float64{0, 0, 1}))
		tr := NewTrsfMirrorFromAxis1(a)
		_ = tr
	})
	t.Run("mirror plane", func(t *testing.T) {
		p := NewPlaneFromPointDir(NewPoint3([3]float64{0, 0, 0}), NewDir3FromXYZ([3]float64{0, 0, 1}))
		tr := NewTrsfMirrorFromPlane(p)
		_ = tr
	})
}

func TestTrsf2d(t *testing.T) {
	t.Run("translation", func(t *testing.T) {
		v := NewVector2([2]float64{10, 0})
		tr := NewTrsf2dTranslationFromVector(v)
		_ = tr
	})
	t.Run("rotation", func(t *testing.T) {
		tr := NewTrsf2dRotationFromPoint(NewPoint2([2]float64{0, 0}), 45)
		_ = tr
	})
}

func TestColor(t *testing.T) {
	c := NewColor([3]float64{1, 0.5, 0})
	_, _, _ = c.RGBF()
	_, _, _ = c.RGBD()
	rgb := c.RGB()
	if rgb[0] != 255 || rgb[1] != 127 || rgb[2] != 0 {
		t.Fatalf("unexpected rgb: %v", rgb)
	}
}

func TestBBox(t *testing.T) {
	bb := NewBBox([6]float64{0, 10, 0, 10, 0, 10})
	d := bb.Data()
	if len(d) == 6 {
		t.Logf("bbox: %v", d)
	}
}

func TestQuaternion(t *testing.T) {
	q := NewQuaternion([4]float64{0, 0, 0, 1})
	_ = q.Data()
}

func TestPlaneNameConstants(t *testing.T) {
	if XYPlane != "XY" || YZPlane != "YZ" || TopPlane != "top" || FrontPlane != "front" {
		t.Fatal("plane name constants mismatch")
	}
}

func TestXYZ(t *testing.T) {
	xyz := NewXYZ([3]float64{1, 2, 3})
	d := xyz.Data()
	if d[0] != 1 || d[1] != 2 || d[2] != 3 {
		t.Fatalf("unexpected: %v", d)
	}
}
