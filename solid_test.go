package topo

import (
	"testing"
)

func TestNewSolid(t *testing.T) {
	t.Run("empty", func(t *testing.T) {
		s := TopoMakeSolid()
		if s == nil {
			t.Fatal("TopoMakeSolid returned nil")
		}
	})
}

func TestSolidConstructors(t *testing.T) {
	t.Run("from box", func(t *testing.T) {
		s := TopoMakeSolidFromBox(10, 20, 30)
		if s == nil {
			t.Fatal("TopoMakeSolidFromBox returned nil")
		}
		if s.Type() != TopoSolid {
			t.Fatalf("expected TopoSolid, got %d", s.Type())
		}
	})
	t.Run("from box two point", func(t *testing.T) {
		p1 := NewPoint3([3]float64{0, 0, 0})
		p2 := NewPoint3([3]float64{10, 20, 30})
		s := TopoMakeSolidFromBoxTwoPoint(p1, p2)
		if s == nil {
			t.Fatal("TopoMakeSolidFromBoxTwoPoint returned nil")
		}
		if !s.IsValid() {
			t.Fatal("box from two point is not valid")
		}
	})
	t.Run("from sphere", func(t *testing.T) {
		s := TopoMakeSolidFromSphere(10)
		if s == nil {
			t.Fatal("TopoMakeSolidFromSphere returned nil")
		}
	})
	t.Run("from cylinder", func(t *testing.T) {
		s := TopoMakeSolidFromCylinder(5, 20)
		if s == nil {
			t.Fatal("TopoMakeSolidFromCylinder returned nil")
		}
	})
	t.Run("from cone", func(t *testing.T) {
		s := TopoMakeSolidFromCone(10, 5, 20)
		if s == nil {
			t.Fatal("TopoMakeSolidFromCone returned nil")
		}
	})
}

func TestSolidProperties(t *testing.T) {
	s := TopoMakeSolidFromBox(10, 10, 10)
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
		if s.Type() != TopoSolid {
			t.Fatalf("expected TopoSolid, got %d", s.Type())
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

func TestSolidAreaVolume(t *testing.T) {
	s := TopoMakeSolidFromBox(10, 10, 10)
	t.Run("area", func(t *testing.T) {
		a := s.Area()
		if a <= 0 {
			t.Fatalf("expected positive area, got %f", a)
		}
	})
	t.Run("volume", func(t *testing.T) {
		v := s.Volume()
		if v <= 0 {
			t.Fatalf("expected positive volume, got %f", v)
		}
	})
}

func TestSolidInertiaCentre(t *testing.T) {
	s := TopoMakeSolidFromBox(10, 10, 10)
	t.Run("centre of mass", func(t *testing.T) {
		c := s.CentreOfMass()
		_ = c
	})
	t.Run("inertia", func(t *testing.T) {
		bb := s.Inertia()
		_ = bb
	})
}

func TestSolidInside(t *testing.T) {
	s := TopoMakeSolidFromBox(10, 10, 10)
	t.Run("is inside", func(t *testing.T) {
		p := NewPoint3([3]float64{5, 5, 5})
		inside := s.IsInside(p, 1e-6)
		_ = inside
	})
}

func TestSolidTransform(t *testing.T) {
	s := TopoMakeSolidFromBox(10, 10, 10)
	t.Run("translate", func(t *testing.T) {
		v := NewVector3([3]float64{5, 0, 0})
		s.Translate(v)
	})
	t.Run("translated", func(t *testing.T) {
		v := NewVector3([3]float64{10, 0, 0})
		s2 := s.Translated(v)
		if s2 == nil {
			t.Fatal("Translated returned nil")
		}
	})
}

func TestSolidCopy(t *testing.T) {
	s := TopoMakeSolidFromBox(10, 10, 10)
	t.Run("copy", func(t *testing.T) {
		s2 := s.Copy()
		if s2 == nil {
			t.Fatal("Copy returned nil")
		}
		_ = s2.Volume()
	})
}

func TestSolidToShape(t *testing.T) {
	s := TopoMakeSolidFromBox(10, 10, 10)
	t.Run("to shape", func(t *testing.T) {
		sh := s.ToShape()
		if sh == nil {
			t.Fatal("ToShape returned nil")
		}
	})
}

func TestSolidLabelColour(t *testing.T) {
	s := TopoMakeSolidFromBox(10, 10, 10)
	t.Run("set label", func(t *testing.T) {
		s.SetLabel("test_solid")
		if s.GetLabel() != "test_solid" {
			t.Fatal("label mismatch")
		}
	})
	t.Run("set colour", func(t *testing.T) {
		s.SetSurfaceColour(NewColor([3]float64{1, 0, 0}))
	})
}

func TestSolidUV(t *testing.T) {
	s := TopoMakeSolidFromBox(10, 10, 10)
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

func TestSolidOrientation(t *testing.T) {
	s := TopoMakeSolidFromBox(10, 10, 10)
	t.Run("set/get orientation", func(t *testing.T) {
		s.SetOrientation(FORWARD)
		if s.GetOrientation() != FORWARD {
			t.Fatal("orientation mismatch")
		}
	})
}

func TestSolidLocation(t *testing.T) {
	s := TopoMakeSolidFromBox(10, 10, 10)
	t.Run("get/set location", func(t *testing.T) {
		loc := s.GetLocation()
		if loc == nil {
			t.Fatal("GetLocation returned nil")
		}
		s.SetLocation(loc)
	})
}

func TestSolidFixShape(t *testing.T) {
	s := TopoMakeSolidFromBox(10, 10, 10)
	t.Run("fix shape", func(t *testing.T) {
		s.FixShape()
	})
}

func TestSolidMesh(t *testing.T) {
	s := TopoMakeSolidFromBox(10, 10, 10)
	t.Run("mesh", func(t *testing.T) {
		m := NewMeshReceiver()
		s.Mesh(m, 0.1, 0.1, 0.5)
	})
}

func TestSolidNumFacesSolid(t *testing.T) {
	s := TopoMakeSolidFromBox(10, 10, 10)
	t.Run("num solids", func(t *testing.T) {
		n := s.NumSolids()
		if n < 1 {
			t.Fatalf("expected >=1 solids, got %d", n)
		}
	})
	t.Run("num faces", func(t *testing.T) {
		n := s.NumFaces()
		if n < 1 {
			t.Fatalf("expected >=1 faces, got %d", n)
		}
	})
}
