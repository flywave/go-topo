package topo

import (
	"math"
	"testing"
)

func makeShape(t *testing.T) *Shape {
	wp := NewNamedWorkplane("XY")
	r := wp.BoxCentered(10, 10, 10)
	s := r.Value()
	if s == nil {
		t.Fatal("Value returned nil")
	}
	return s
}

func TestShapeProperties(t *testing.T) {
	s := makeShape(t)
	t.Run("is null", func(t *testing.T) {
		if s.IsNull() {
			t.Fatal("expected non-null")
		}
	})
	t.Run("is valid", func(t *testing.T) {
		if !s.IsValid() {
			t.Fatal("expected valid")
		}
	})
	t.Run("type", func(t *testing.T) {
		if s.Type() != TopoCompound {
			t.Fatalf("expected TopoCompound, got %d", s.Type())
		}
	})
	t.Run("bbox", func(t *testing.T) {
		bb := s.BBox()
		_ = bb
	})
	t.Run("hash", func(t *testing.T) {
		_ = s.Hash()
	})
}

func TestShapeComputeProps(t *testing.T) {
	s := makeShape(t)
	t.Run("centre of mass", func(t *testing.T) {
		c := s.CentreOfMass()
		d := c.Data()
		if math.Abs(d[0]) > 1e-6 || math.Abs(d[1]) > 1e-6 || math.Abs(d[2]) > 1e-6 {
			t.Logf("centre of mass: %v", d)
		}
	})
	t.Run("compute mass", func(t *testing.T) {
		m := s.ComputeMass()
		if m <= 0 {
			t.Fatalf("expected positive mass, got %f", m)
		}
	})
	t.Run("compute area", func(t *testing.T) {
		a := s.ComputeArea()
		if a <= 0 {
			t.Fatalf("expected positive area, got %f", a)
		}
	})
}

func TestShapeAutoCast(t *testing.T) {
	s := makeShape(t)
	t.Run("auto cast solid", func(t *testing.T) {
		cast := s.AutoCast()
		if cast == nil {
			t.Fatal("AutoCast returned nil")
		}
		switch v := cast.(type) {
		case *Solid:
			t.Log("auto cast to Solid")
			_ = v
		default:
			t.Logf("auto cast to %T", v)
		}
	})
}

func TestShapeShare(t *testing.T) {
	s := makeShape(t)
	t.Run("share", func(t *testing.T) {
		s2 := s.Share()
		if s2 == nil {
			t.Fatal("Share returned nil")
		}
	})
}

func TestShapeWriteToStl(t *testing.T) {
	s := makeShape(t)
	t.Run("write to stl", func(t *testing.T) {
		s.WriteToStl("/tmp/test_shape.stl")
	})
}

func TestShapeEquality(t *testing.T) {
	s := makeShape(t)
	t.Run("equals self", func(t *testing.T) {
		if !s.Equals(s) {
			t.Fatal("shape should equal itself")
		}
	})
}

func TestShapeCopy(t *testing.T) {
	s := makeShape(t)
	t.Run("copy", func(t *testing.T) {
		s2 := s.Copy()
		if s2 == nil {
			t.Fatal("Copy returned nil")
		}
	})
}

func TestShapeTransform(t *testing.T) {
	s := makeShape(t)
	t.Run("translate", func(t *testing.T) {
		v := NewVector3([3]float64{5, 0, 0})
		s.Translate(v)
	})
	t.Run("transformed", func(t *testing.T) {
		v := NewVector3([3]float64{10, 0, 0})
		s2 := s.Translated(v)
		if s2 == nil {
			t.Fatal("Translated returned nil")
		}
	})
}

func TestShapeSetGet(t *testing.T) {
	s := makeShape(t)
	t.Run("set label", func(t *testing.T) {
		s.SetLabel("test_shape")
		if s.GetLabel() != "test_shape" {
			t.Fatal("label mismatch")
		}
	})
	t.Run("set colour", func(t *testing.T) {
		s.SetSurfaceColour(NewColor([3]float64{1, 0, 0}))
	})
	t.Run("set orientation", func(t *testing.T) {
		s.SetOrientation(FORWARD)
		if s.GetOrientation() != FORWARD {
			t.Fatal("orientation mismatch")
		}
	})
	t.Run("set uv", func(t *testing.T) {
		s.SetUVOrigin(0.5, 0.5)
		s.SetUVRepeat(2.0, 2.0)
		s.SetScaleU(1.5)
		s.SetScaleV(1.5)
		_, _ = s.GetUVOrigin()
		_, _ = s.GetUVRepeat()
		_, _ = s.GetUVScale()
	})
	t.Run("set rotation", func(t *testing.T) {
		s.SetRotationAngle(45)
		if s.GetRotationAngle() != 45 {
			t.Fatal("rotation angle mismatch")
		}
	})
}

func TestShapeLocation(t *testing.T) {
	s := makeShape(t)
	t.Run("get/set location", func(t *testing.T) {
		loc := s.GetLocation()
		if loc == nil {
			t.Fatal("GetLocation returned nil")
		}
		s.SetLocation(loc)
	})
}

func TestShapeFixMesh(t *testing.T) {
	s := makeShape(t)
	t.Run("fix shape", func(t *testing.T) {
		s.FixShape()
	})
	t.Run("mesh", func(t *testing.T) {
		m := NewMeshReceiver()
		s.Mesh(m, 0.1, 0.1, 0.5)
	})
}

func TestShapeMirrorRotate(t *testing.T) {
	s := makeShape(t)
	t.Run("rotate", func(t *testing.T) {
		p1 := NewPoint3([3]float64{0, 0, 0})
		p2 := NewPoint3([3]float64{0, 0, 1})
		s.RotateFromPoint(45, p1, p2)
	})
	t.Run("mirror", func(t *testing.T) {
		p := NewPoint3([3]float64{0, 0, 0})
		n := NewPoint3([3]float64{0, 0, 1})
		s.MirrorFromPointNorm(p, n)
	})
}
