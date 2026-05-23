package topo

import (
	"math"
	"testing"
)

func makeRectFace(t *testing.T) *Face {
	p1 := NewPoint3([3]float64{0, 0, 0})
	p2 := NewPoint3([3]float64{10, 0, 0})
	p3 := NewPoint3([3]float64{10, 10, 0})
	p4 := NewPoint3([3]float64{0, 10, 0})
	e1 := TopoMakeEdgeFromTwoPoint(p1, p2)
	e2 := TopoMakeEdgeFromTwoPoint(p2, p3)
	e3 := TopoMakeEdgeFromTwoPoint(p3, p4)
	e4 := TopoMakeEdgeFromTwoPoint(p4, p1)
	w := TopoMakeWireFromEdges([]Edge{*e1, *e2, *e3, *e4})
	f := TopoMakeFaceFromWire(*w, true)
	if f == nil || f.IsNull() {
		t.Fatal("TopoMakeFaceFromWire failed")
	}
	return f
}

func TestNewFace(t *testing.T) {
	t.Run("empty", func(t *testing.T) {
		f := TopoMakeFace()
		if f == nil {
			t.Fatal("TopoMakeFace returned nil")
		}
	})
	t.Run("from wire", func(t *testing.T) {
		f := makeRectFace(t)
		if f.Type() != TopoFace {
			t.Fatalf("expected TopoFace, got %d", f.Type())
		}
	})
	t.Run("from points", func(t *testing.T) {
		pts := []Point3{
			NewPoint3([3]float64{0, 0, 0}),
			NewPoint3([3]float64{10, 0, 0}),
			NewPoint3([3]float64{10, 10, 0}),
			NewPoint3([3]float64{0, 10, 0}),
		}
		f := TopoMakeFaceFromPoints(pts)
		if f == nil {
			t.Fatal("TopoMakeFaceFromPoints returned nil")
		}
	})
	t.Run("plane face", func(t *testing.T) {
		base := NewPoint3([3]float64{0, 0, 0})
		dir := NewDir3FromXYZ([3]float64{0, 0, 1})
		f := TopoMakePlaneFace(base, dir, 10, 10)
		if f == nil {
			t.Fatal("TopoMakePlaneFace failed")
		}
	})
}

func TestFaceProperties(t *testing.T) {
	f := makeRectFace(t)
	t.Run("is null", func(t *testing.T) {
		if f.IsNull() {
			t.Fatal("expected non-null")
		}
	})
	t.Run("is valid", func(t *testing.T) {
		if !f.IsValid() {
			t.Fatal("expected valid")
		}
	})
	t.Run("num wires", func(t *testing.T) {
		n := f.NumWires()
		if n < 1 {
			t.Fatalf("expected >=1 wires, got %d", n)
		}
	})
	t.Run("num faces", func(t *testing.T) {
		n := f.NumFaces()
		_ = n
	})
	t.Run("area", func(t *testing.T) {
		a := f.Area()
		if a <= 0 {
			t.Fatalf("expected positive area, got %f", a)
		}
	})
	t.Run("tolerance", func(t *testing.T) {
		tol := f.Tolerance()
		if tol < 0 {
			t.Fatalf("negative tolerance: %f", tol)
		}
	})
}

func TestFaceNormal(t *testing.T) {
	f := makeRectFace(t)
	t.Run("normal at", func(t *testing.T) {
		n := f.NormalAt(NewPoint3([3]float64{5, 5, 0}))
		d := n.Data()
		if math.Abs(d[2]-1) > 1e-6 {
			t.Fatalf("expected normal (0,0,1), got (%f,%f,%f)", d[0], d[1], d[2])
		}
	})
	t.Run("normal at uv", func(t *testing.T) {
		n, p := f.NormalAtUV(0.5, 0.5)
		_ = n
		_ = p
	})
}

func TestFaceCentreInertia(t *testing.T) {
	f := makeRectFace(t)
	t.Run("centre of mass", func(t *testing.T) {
		c := f.CentreOfMass()
		_ = c
	})
	t.Run("inertia", func(t *testing.T) {
		bb := f.Inertia()
		_ = bb
	})
}

func TestFaceToPlane(t *testing.T) {
	f := makeRectFace(t)
	t.Run("to plane", func(t *testing.T) {
		p := f.ToPlane()
		if p == nil {
			t.Fatal("ToPlane returned nil")
		}
	})
}

func TestFaceUV(t *testing.T) {
	f := makeRectFace(t)
	t.Run("uv bounds", func(t *testing.T) {
		uMin, uMax, vMin, vMax := f.UVBounds()
		if uMin >= uMax || vMin >= vMax {
			t.Fatalf("invalid uv bounds: %f,%f %f,%f", uMin, uMax, vMin, vMax)
		}
	})
	t.Run("param at", func(t *testing.T) {
		u, v := f.ParamAt(NewPoint3([3]float64{5, 5, 0}))
		_ = u
		_ = v
	})
	t.Run("position at", func(t *testing.T) {
		p := f.PositionAt(0.5, 0.5)
		_ = p
	})
}

func TestFaceTransform(t *testing.T) {
	f := makeRectFace(t)
	t.Run("translate", func(t *testing.T) {
		v := NewVector3([3]float64{5, 0, 0})
		f.Translate(v)
	})
}

func TestFaceCopy(t *testing.T) {
	f := makeRectFace(t)
	t.Run("copy", func(t *testing.T) {
		f2 := f.Copy()
		if f2 == nil {
			t.Fatal("Copy returned nil")
		}
		_ = f2.Area()
	})
}

func TestFaceLabelColour(t *testing.T) {
	f := makeRectFace(t)
	t.Run("set label", func(t *testing.T) {
		f.SetLabel("test_face")
		if f.GetLabel() != "test_face" {
			t.Fatal("label mismatch")
		}
	})
	t.Run("set colour", func(t *testing.T) {
		f.SetSurfaceColour(NewColor([3]float64{1, 0, 0}))
	})
}

func TestFaceIterator(t *testing.T) {
	t.Run("iterate", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		shape := r1.Value()
		it := TopoMakeFaceIterator(*shape)
		if it == nil {
			t.Fatal("TopoMakeFaceIterator returned nil")
		}
		count := 0
		for {
			f := it.Next()
			if f == nil {
				break
			}
			count++
			_ = f.Area()
		}
		if count == 0 {
			t.Fatal("no faces found")
		}
	})
}

func TestFaceOuterWire(t *testing.T) {
	f := makeRectFace(t)
	t.Run("outer wire", func(t *testing.T) {
		w := f.OuterWire()
		if w == nil {
			t.Fatal("OuterWire returned nil")
		}
	})
}

func TestFaceSetGet(t *testing.T) {
	f := makeRectFace(t)
	t.Run("set/get orientation", func(t *testing.T) {
		f.SetOrientation(FORWARD)
		if f.GetOrientation() != FORWARD {
			t.Fatal("orientation mismatch")
		}
	})
	t.Run("set uv", func(t *testing.T) {
		f.SetUVOrigin(0.5, 0.5)
		f.SetUVRepeat(2.0, 2.0)
		f.SetScaleU(1.5)
		f.SetScaleV(1.5)
		_, _ = f.GetUVOrigin()
		_, _ = f.GetUVRepeat()
		_, _ = f.GetUVScale()
	})
	t.Run("set rotation", func(t *testing.T) {
		f.SetRotationAngle(45)
		if f.GetRotationAngle() != 45 {
			t.Fatal("rotation angle mismatch")
		}
	})
}

func TestFaceBBoxHash(t *testing.T) {
	f := makeRectFace(t)
	t.Run("bbox", func(t *testing.T) {
		_ = f.BBox()
	})
	t.Run("hash", func(t *testing.T) {
		_ = f.Hash()
	})
}

func TestFaceLocations(t *testing.T) {
	f := makeRectFace(t)
	t.Run("get location", func(t *testing.T) {
		loc := f.GetLocation()
		if loc == nil {
			t.Fatal("GetLocation returned nil")
		}
	})
	t.Run("fix shape", func(t *testing.T) {
		f.FixShape()
	})
}

func TestFaceTransformed(t *testing.T) {
	f := makeRectFace(t)
	t.Run("translated", func(t *testing.T) {
		v := NewVector3([3]float64{10, 0, 0})
		f2 := f.Translated(v)
		if f2 == nil {
			t.Fatal("Translated returned nil")
		}
	})
}

func TestFaceNormals(t *testing.T) {
	f := makeRectFace(t)
	t.Run("normals", func(t *testing.T) {
		us := []float64{0.25, 0.75}
		vs := []float64{0.25, 0.75}
		normals, points := f.Normals(us, vs)
		if len(normals) == 0 {
			t.Log("Normals returned empty (may require non-planar face)")
		}
		_ = points
	})
}
