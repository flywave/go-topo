package topo

import (
	"testing"
)

func TestNewCompSolid(t *testing.T) {
	t.Run("make", func(t *testing.T) {
		cs := TopoMakeCompSolid()
		if cs == nil {
			t.Fatal("TopoMakeCompSolid returned nil")
		}
	})
}

func TestCompSolidBasicProps(t *testing.T) {
	t.Run("is null", func(t *testing.T) {
		cs := TopoMakeCompSolid()
		_ = cs.IsNull()
	})

	t.Run("type", func(t *testing.T) {
		cs := TopoMakeCompSolid()
		_ = cs.Type()
	})

	t.Run("hash", func(t *testing.T) {
		cs := TopoMakeCompSolid()
		_ = cs.Hash()
	})
}

func TestCompSolidCopy(t *testing.T) {
	t.Run("copy", func(t *testing.T) {
		cs := TopoMakeCompSolid()
		cs2 := cs.Copy()
		if cs2 == nil {
			t.Fatal("Copy returned nil")
		}
	})
}

func TestCompSolidTransforms(t *testing.T) {
	t.Run("translate", func(t *testing.T) {
		cs := TopoMakeCompSolid()
		v := NewVector3([3]float64{10, 0, 0})
		cs.Translate(v)
	})

	t.Run("translated", func(t *testing.T) {
		cs := TopoMakeCompSolid()
		v := NewVector3([3]float64{10, 0, 0})
		cs2 := cs.Translated(v)
		if cs2 == nil {
			t.Fatal("Translated returned nil")
		}
	})

	t.Run("rotate", func(t *testing.T) {
		cs := TopoMakeCompSolid()
		p1 := NewPoint3([3]float64{0, 0, 0})
		p2 := NewPoint3([3]float64{0, 0, 1})
		cs.RotateFromPoint(45, p1, p2)
	})

	t.Run("scale", func(t *testing.T) {
		cs := TopoMakeCompSolid()
		p := NewPoint3([3]float64{0, 0, 0})
		cs.Scale(2.0, p)
	})
}

func TestCompSolidColourLabel(t *testing.T) {
	t.Run("set surface colour", func(t *testing.T) {
		cs := TopoMakeCompSolid()
		col := NewColor([3]float64{1, 0, 0})
		cs.SetSurfaceColour(col)
	})

	t.Run("set label", func(t *testing.T) {
		cs := TopoMakeCompSolid()
		cs.SetLabel("test_cs")
		if cs.GetLabel() != "test_cs" {
			t.Fatalf("label mismatch")
		}
	})
}

func TestCompSolidUV(t *testing.T) {
	t.Run("set uv origin", func(t *testing.T) {
		cs := TopoMakeCompSolid()
		cs.SetUVOrigin(0.5, 0.5)
		_, _ = cs.GetUVOrigin()
	})

	t.Run("set uv repeat", func(t *testing.T) {
		cs := TopoMakeCompSolid()
		cs.SetUVRepeat(2.0, 2.0)
		_, _ = cs.GetUVRepeat()
	})

	t.Run("set rotation angle", func(t *testing.T) {
		cs := TopoMakeCompSolid()
		cs.SetRotationAngle(45.0)
		if cs.GetRotationAngle() != 45.0 {
			t.Fatal("rotation angle mismatch")
		}
	})
}

func TestCompSolidOrientation(t *testing.T) {
	t.Run("get/set orientation", func(t *testing.T) {
		cs := TopoMakeCompSolid()
		cs.SetOrientation(FORWARD)
		if cs.GetOrientation() != FORWARD {
			t.Fatal("orientation mismatch")
		}
	})
}

func TestCompSolidToShape(t *testing.T) {
	t.Run("to shape", func(t *testing.T) {
		cs := TopoMakeCompSolid()
		s := cs.ToShape()
		if s == nil {
			t.Fatal("ToShape returned nil")
		}
	})
}

func TestCompSolidLocation(t *testing.T) {
	t.Run("get/set location", func(t *testing.T) {
		cs := TopoMakeCompSolid()
		loc := cs.GetLocation()
		if loc == nil {
			t.Fatal("GetLocation returned nil")
		}
		cs.SetLocation(loc)
	})
}

func TestCompSolidFixShape(t *testing.T) {
	t.Run("fix shape", func(t *testing.T) {
		cs := TopoMakeCompSolid()
		cs.FixShape()
	})
}

func TestCompSolidMesh(t *testing.T) {
	t.Run("mesh", func(t *testing.T) {
		cs := TopoMakeCompSolid()
		m := NewMeshReceiver()
		cs.Mesh(m, 0.1, 0.1, 0.5)
	})
}

func TestCompSolidIterator(t *testing.T) {
	t.Run("iterate", func(t *testing.T) {
		cs := TopoMakeCompSolid()
		it := TopoMakeCompSolidIterator(*cs.ToShape())
		if it == nil {
			t.Fatal("TopoMakeCompSolidIterator returned nil")
		}
		for {
			sub := it.Next()
			if sub == nil {
				break
			}
			_ = sub.Type()
		}
	})
}

func TestCompSolidCentreInertia(t *testing.T) {
	t.Run("centre of mass", func(t *testing.T) {
		cs := TopoMakeCompSolid()
		_ = cs.CentreOfMass()
	})

	t.Run("inertia", func(t *testing.T) {
		cs := TopoMakeCompSolid()
		_ = cs.Inertia()
	})
}
