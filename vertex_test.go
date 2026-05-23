package topo

import (
	"math"
	"testing"
)

func TestVertex(t *testing.T) {
	t.Run("new vertex", func(t *testing.T) {
		v := NewVertex(1, 2, 3)
		if v == nil {
			t.Fatal("NewVertex returned nil")
		}
		if v.IsNull() {
			t.Fatal("expected non-null")
		}
	})
	t.Run("get point", func(t *testing.T) {
		v := NewVertex(10, 20, 30)
		p := v.GetPoint()
		d := p.Data()
		if math.Abs(d[0]-10) > 1e-6 || math.Abs(d[1]-20) > 1e-6 || math.Abs(d[2]-30) > 1e-6 {
			t.Fatalf("unexpected point: %v", d)
		}
	})
	t.Run("type", func(t *testing.T) {
		v := NewVertex(0, 0, 0)
		if v.Type() != TopoVertex {
			t.Fatalf("expected TopoVertex, got %d", v.Type())
		}
	})
	t.Run("to shape", func(t *testing.T) {
		v := NewVertex(0, 0, 0)
		s := v.ToShape()
		if s == nil {
			t.Fatal("ToShape returned nil")
		}
	})
	t.Run("bbox", func(t *testing.T) {
		v := NewVertex(5, 5, 5)
		bb := v.BBox()
		_ = bb
	})
	t.Run("hash", func(t *testing.T) {
		v := NewVertex(0, 0, 0)
		_ = v.Hash()
	})
}

func TestVertexIterator(t *testing.T) {
	t.Run("iterate", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.RectCentered(10, 10)
		shape := r1.Value()
		it := TopoMakeVertexIterator(*shape)
		if it == nil {
			t.Fatal("TopoMakeVertexIterator returned nil")
		}
		count := 0
		for {
			v := it.Next()
			if v == nil {
				break
			}
			count++
			_ = v.GetPoint()
		}
		if count == 0 {
			t.Fatal("no vertices found")
		}
	})
}

func TestVertexSetGet(t *testing.T) {
	v := NewVertex(0, 0, 0)
	t.Run("set label", func(t *testing.T) {
		v.SetLabel("v1")
		if v.GetLabel() != "v1" {
			t.Fatal("label mismatch")
		}
	})
	t.Run("set colour", func(t *testing.T) {
		v.SetSurfaceColour(NewColor([3]float64{1, 0, 0}))
	})
}
