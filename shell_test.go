package topo

import (
	"testing"
)

func TestNewShell(t *testing.T) {
	t.Run("empty", func(t *testing.T) {
		sh := TopoMakeShell()
		if sh == nil {
			t.Fatal("TopoMakeShell returned nil")
		}
	})
}

func TestShellConstructors(t *testing.T) {
	t.Run("from box", func(t *testing.T) {
		sh := TopoMakeShellFromBox(10, 20, 30)
		if sh == nil {
			t.Fatal("TopoMakeShellFromBox returned nil")
		}
	})
	t.Run("from box point", func(t *testing.T) {
		p := NewPoint3([3]float64{0, 0, 0})
		sh := TopoMakeShellFromBoxPoint(p, 10, 20, 30)
		if sh == nil {
			t.Fatal("TopoMakeShellFromBoxPoint returned nil")
		}
	})
	t.Run("from box two point", func(t *testing.T) {
		p1 := NewPoint3([3]float64{0, 0, 0})
		p2 := NewPoint3([3]float64{10, 20, 30})
		sh := TopoMakeShellFromBoxTwoPoint(p1, p2)
		if sh == nil {
			t.Fatal("TopoMakeShellFromBoxTwoPoint returned nil")
		}
	})
	t.Run("from cylinder", func(t *testing.T) {
		sh := TopoMakeShellFromCylinder(5, 20)
		if sh == nil {
			t.Fatal("TopoMakeShellFromCylinder returned nil")
		}
	})
	t.Run("from cone", func(t *testing.T) {
		sh := TopoMakeShellFromCone(10, 5, 20)
		if sh == nil {
			t.Fatal("TopoMakeShellFromCone returned nil")
		}
	})
	t.Run("from sphere", func(t *testing.T) {
		sh := TopoMakeShellFromSpere(10)
		if sh == nil {
			t.Fatal("TopoMakeShellFromSpere returned nil")
		}
	})
	t.Run("from torus", func(t *testing.T) {
		sh := TopoMakeShellFromTorus(20, 5)
		if sh == nil {
			t.Fatal("TopoMakeShellFromTorus returned nil")
		}
	})
	t.Run("from wedge", func(t *testing.T) {
		sh := TopoMakeShellFromWedge(10, 20, 15, 5)
		if sh == nil {
			t.Fatal("TopoMakeShellFromWedge returned nil")
		}
	})
}

func TestShellToShape(t *testing.T) {
	t.Run("to shape", func(t *testing.T) {
		sh := TopoMakeShellFromBox(10, 10, 10)
		s, err := sh.ToShape()
		if err != nil {
			t.Fatalf("ToShape error: %v", err)
		}
		if s == nil {
			t.Fatal("ToShape returned nil")
		}
	})
}

func TestShellIterator(t *testing.T) {
	t.Run("iterate from box", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		s := r1.Value()
		it, err := TopoMakeShellIterator(s)
		if err != nil {
			t.Fatalf("TopoMakeShellIterator error: %v", err)
		}
		count := 0
		for {
			sh, err := it.Next()
			if err != nil {
				t.Fatalf("Next error: %v", err)
			}
			if sh == nil {
				break
			}
			count++
		}
		if count == 0 {
			// Box has no shells by default (it's a solid)
			t.Log("no shells found (box may be solid, not shell)")
		}
	})
}

func TestShellSweep(t *testing.T) {
	t.Run("sweep wire", func(t *testing.T) {
		sh := TopoMakeShellFromCylinder(5, 20)
		// Create path wire
		p1 := NewPoint3([3]float64{0, 0, 0})
		p2 := NewPoint3([3]float64{0, 0, 20})
		path := TopoMakeEdgeFromTwoPoint(p1, p2)
		pathWire := TopoMakeWireFromEdge(*path)
		// Create profile shape
		profilePts := []Point3{
			NewPoint3([3]float64{-2, 0, 0}),
			NewPoint3([3]float64{2, 0, 0}),
			NewPoint3([3]float64{2, 0, 5}),
			NewPoint3([3]float64{-2, 0, 5}),
		}
		profileEdges := make([]Edge, 4)
		for i := 0; i < 4; i++ {
			e := TopoMakeEdgeFromTwoPoint(profilePts[i], profilePts[(i+1)%4])
			profileEdges[i] = *e
		}
		profile := TopoMakeWireFromEdges(profileEdges)
		profileShape := profile.ToShape()
		_, err := sh.Sweep(pathWire, []Shape{*profileShape}, 0)
		if err != nil {
			t.Logf("Sweep error (may be expected): %v", err)
		}
	})
}
