package topo

import (
	"testing"
)

func TestNewCompound(t *testing.T) {
	t.Run("make compound", func(t *testing.T) {
		c := TopoMakeCompound()
		if c == nil {
			t.Fatal("TopoMakeCompound returned nil")
		}
	})

	t.Run("make compound from shapes", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		shapes := []Shape{*r1.Value()}
		c := TopoCompoundMake(shapes)
		if c == nil {
			t.Fatal("TopoCompoundMake returned nil")
		}
	})
}

func TestCompoundBasicProps(t *testing.T) {
	t.Run("is null on empty", func(t *testing.T) {
		c := TopoMakeCompound()
		// Empty compound may be considered null by C API
		_ = c.IsNull()
	})

	t.Run("type", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		shapes := []Shape{*r1.Value()}
		c := TopoCompoundMake(shapes)
		if c.Type() != TopoCompound {
			t.Fatalf("expected compound type, got %d", c.Type())
		}
	})

	t.Run("bbox", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		shapes := []Shape{*r1.Value()}
		c := TopoCompoundMake(shapes)
		bb := c.BBox()
		_ = bb
	})

	t.Run("hash", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		shapes := []Shape{*r1.Value()}
		c := TopoCompoundMake(shapes)
		h := c.Hash()
		if h == 0 {
			t.Log("hash may be zero for empty compound")
		}
	})
}

func TestCompoundCopy(t *testing.T) {
	t.Run("copy", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		shapes := []Shape{*r1.Value()}
		c := TopoCompoundMake(shapes)
		c2 := c.Copy()
		if c2 == nil {
			t.Fatal("Copy returned nil")
		}
	})
}

func TestCompoundTransforms(t *testing.T) {
	t.Run("translate", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		shapes := []Shape{*r1.Value()}
		c := TopoCompoundMake(shapes)
		v := NewVector3([3]float64{10, 0, 0})
		c.Translate(v)
	})

	t.Run("translated", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		shapes := []Shape{*r1.Value()}
		c := TopoCompoundMake(shapes)
		v := NewVector3([3]float64{10, 0, 0})
		c2 := c.Translated(v)
		if c2 == nil {
			t.Fatal("Translated returned nil")
		}
	})

	t.Run("rotate", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		shapes := []Shape{*r1.Value()}
		c := TopoCompoundMake(shapes)
		p1 := NewPoint3([3]float64{0, 0, 0})
		p2 := NewPoint3([3]float64{0, 0, 1})
		c.RotateFromPoint(45, p1, p2)
	})

	t.Run("scale", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		shapes := []Shape{*r1.Value()}
		c := TopoCompoundMake(shapes)
		p := NewPoint3([3]float64{0, 0, 0})
		c.Scale(2.0, p)
	})
}

func TestCompoundColourLabel(t *testing.T) {
	t.Run("set surface colour", func(t *testing.T) {
		c := TopoMakeCompound()
		col := NewColor([3]float64{1, 0, 0})
		c.SetSurfaceColour(col)
	})

	t.Run("set curve colour", func(t *testing.T) {
		c := TopoMakeCompound()
		col := NewColor([3]float64{0, 1, 0})
		c.SetCurveColour(col)
	})

	t.Run("set label", func(t *testing.T) {
		c := TopoMakeCompound()
		c.SetLabel("test_label")
		label := c.GetLabel()
		if label != "test_label" {
			t.Fatalf("expected 'test_label', got '%s'", label)
		}
	})
}

func TestCompoundUV(t *testing.T) {
	t.Run("set uv origin", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		shapes := []Shape{*r1.Value()}
		c := TopoCompoundMake(shapes)
		c.SetUVOrigin(0.5, 0.5)
		u, v := c.GetUVOrigin()
		_ = u
		_ = v
	})

	t.Run("set uv repeat", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		shapes := []Shape{*r1.Value()}
		c := TopoCompoundMake(shapes)
		c.SetUVRepeat(2.0, 2.0)
		u, v := c.GetUVRepeat()
		_ = u
		_ = v
	})

	t.Run("set scale", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		shapes := []Shape{*r1.Value()}
		c := TopoCompoundMake(shapes)
		c.SetScaleU(1.5)
		c.SetScaleV(1.5)
		u, v := c.GetUVScale()
		_ = u
		_ = v
	})

	t.Run("set auto scale", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		shapes := []Shape{*r1.Value()}
		c := TopoCompoundMake(shapes)
		c.SetAutoScaleSizeOnU(2.0)
		c.SetAutoScaleSizeOnV(2.0)
		u, v := c.GetUVAutoScaleSize()
		_ = u
		_ = v
	})

	t.Run("set texture map type", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		shapes := []Shape{*r1.Value()}
		c := TopoCompoundMake(shapes)
		c.SetTextureMapType(TextureCube)
		tp := c.GetTxtureMapType()
		if tp != TextureCube {
			t.Fatalf("expected TextureCube, got %d", tp)
		}
	})

	t.Run("set rotation angle", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		shapes := []Shape{*r1.Value()}
		c := TopoCompoundMake(shapes)
		c.SetRotationAngle(45.0)
		a := c.GetRotationAngle()
		if a != 45.0 {
			t.Fatalf("expected 45, got %f", a)
		}
	})
}

func TestCompoundOrientation(t *testing.T) {
	t.Run("get/set orientation", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		shapes := []Shape{*r1.Value()}
		c := TopoCompoundMake(shapes)
		c.SetOrientation(FORWARD)
		o := c.GetOrientation()
		if o != FORWARD {
			t.Fatalf("expected FORWARD, got %d", o)
		}
	})
}

func TestCompoundToShape(t *testing.T) {
	t.Run("to shape", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		shapes := []Shape{*r1.Value()}
		c := TopoCompoundMake(shapes)
		s := c.ToShape()
		if s == nil {
			t.Fatal("ToShape returned nil")
		}
	})

	t.Run("to solid", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		shapes := []Shape{*r1.Value()}
		c := TopoCompoundMake(shapes)
		s := c.ToSolid()
		if s == nil {
			t.Fatal("ToSolid returned nil")
		}
	})
}

func TestCompoundVolArea(t *testing.T) {
	t.Run("area", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		shapes := []Shape{*r1.Value()}
		c := TopoCompoundMake(shapes)
		_ = c.Area()
	})
}

func TestCompoundCentreInertia(t *testing.T) {
	t.Run("centre of mass", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		shapes := []Shape{*r1.Value()}
		c := TopoCompoundMake(shapes)
		cm := c.CentreOfMass()
		_ = cm
	})

	t.Run("inertia", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		shapes := []Shape{*r1.Value()}
		c := TopoCompoundMake(shapes)
		bb := c.Inertia()
		_ = bb
	})
}

func TestCompoundIterator(t *testing.T) {
	t.Run("iterate", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		r2 := wp.BoxCentered(5, 5, 5)
		shapes := []Shape{*r1.Value(), *r2.Value()}
		c := TopoCompoundMake(shapes)
		it := TopoMakeCompoundIterator(*c.ToShape())
		if it == nil {
			t.Fatal("TopoMakeCompoundIterator returned nil")
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

func TestCompoundBoolean(t *testing.T) {
	t.Run("fuse", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		shapes := []Shape{*r1.Value()}
		c := TopoCompoundMake(shapes)
		wp2 := NewNamedWorkplane("XY")
		r2 := wp2.BoxCentered(5, 5, 20)
		fused := c.Fuse([]*Shape{r2.Value()}, false, 0.001)
		if fused == nil {
			t.Fatal("Fuse returned nil")
		}
	})
}

func TestCompoundFixShape(t *testing.T) {
	t.Run("fix shape", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		shapes := []Shape{*r1.Value()}
		c := TopoCompoundMake(shapes)
		c.FixShape()
	})
}

func TestCompoundLocation(t *testing.T) {
	t.Run("get/set location", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		shapes := []Shape{*r1.Value()}
		c := TopoCompoundMake(shapes)
		loc := c.GetLocation()
		if loc == nil {
			t.Fatal("GetLocation returned nil")
		}
		c.SetLocation(loc)
	})
}

func TestCompoundMesh(t *testing.T) {
	t.Run("mesh", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		shapes := []Shape{*r1.Value()}
		c := TopoCompoundMake(shapes)
		m := NewMeshReceiver()
		c.Mesh(m, 0.1, 0.1, 0.5)
	})
}

func TestCompoundText(t *testing.T) {
	t.Run("make text", func(t *testing.T) {
		t.Skip("TopoCompoundMakeText crashes in prebuilt lib")
	})
}

func TestCompoundCutIntersect(t *testing.T) {
	t.Run("cut", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		shapes := []Shape{*r1.Value()}
		c := TopoCompoundMake(shapes)
		wp2 := NewNamedWorkplane("XY")
		r2 := wp2.BoxCentered(5, 5, 20)
		cut := c.Cut([]*Shape{r2.Value()}, 0.001)
		if cut == nil {
			t.Fatal("Cut returned nil")
		}
	})

	t.Run("intersect", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		shapes := []Shape{*r1.Value()}
		c := TopoCompoundMake(shapes)
		wp2 := NewNamedWorkplane("XY")
		r2 := wp2.BoxCentered(5, 5, 20)
		inter := c.Intersect([]*Shape{r2.Value()}, 0.001)
		if inter == nil {
			t.Fatal("Intersect returned nil")
		}
	})
}
