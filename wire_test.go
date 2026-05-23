package topo

import (
	"math"
	"testing"
)

func makeRectWire(t *testing.T) *Wire {
	p1 := NewPoint3([3]float64{0, 0, 0})
	p2 := NewPoint3([3]float64{10, 0, 0})
	p3 := NewPoint3([3]float64{10, 10, 0})
	p4 := NewPoint3([3]float64{0, 10, 0})
	e1 := TopoMakeEdgeFromTwoPoint(p1, p2)
	e2 := TopoMakeEdgeFromTwoPoint(p2, p3)
	e3 := TopoMakeEdgeFromTwoPoint(p3, p4)
	e4 := TopoMakeEdgeFromTwoPoint(p4, p1)
	return TopoMakeWireFromEdges([]Edge{*e1, *e2, *e3, *e4})
}

func TestNewWire(t *testing.T) {
	t.Run("empty", func(t *testing.T) {
		w := TopoMakeWire()
		if w == nil {
			t.Fatal("TopoMakeWire returned nil")
		}
	})
	t.Run("from edges", func(t *testing.T) {
		w := makeRectWire(t)
		if w.IsNull() {
			t.Fatal("expected non-null wire")
		}
	})
	t.Run("from edge", func(t *testing.T) {
		e := TopoMakeEdgeFromTwoPoint(NewPoint3([3]float64{0, 0, 0}), NewPoint3([3]float64{10, 0, 0}))
		w := TopoMakeWireFromEdge(*e)
		if w == nil {
			t.Fatal("TopoMakeWireFromEdge failed")
		}
	})
	t.Run("circle wire", func(t *testing.T) {
		w := TopoMakeWireFromCircle(5, NewPoint3([3]float64{0, 0, 0}), NewDir3FromXYZ([3]float64{0, 0, 1}))
		if w == nil {
			t.Fatal("TopoMakeWireFromCircle failed")
		}
	})
	t.Run("rect wire", func(t *testing.T) {
		w := TopoMakeWireFromRect(10, 5)
		if w == nil {
			t.Fatal("TopoMakeWireFromRect failed")
		}
	})
}

func TestWireProperties(t *testing.T) {
	w := makeRectWire(t)
	t.Run("num vertices", func(t *testing.T) {
		n := w.NumVertices()
		if n < 4 {
			t.Fatalf("expected >=4 vertices, got %d", n)
		}
	})
	t.Run("num edges", func(t *testing.T) {
		n := w.NumEdges()
		if n < 4 {
			t.Fatalf("expected >=4 edges, got %d", n)
		}
	})
	t.Run("is closed", func(t *testing.T) {
		if !w.IsClosed() {
			t.Fatal("rect wire should be closed")
		}
	})
	t.Run("start/end point", func(t *testing.T) {
		s := w.StartPoint()
		e := w.EndPoint()
		_ = s
		_ = e
	})
	t.Run("bounds", func(t *testing.T) {
		min, max := w.Bounds()
		_ = min
		_ = max
	})
}

func TestWireTangent(t *testing.T) {
	w := makeRectWire(t)
	t.Run("tangent at", func(t *testing.T) {
		tang := w.TangentAt(0.5)
		_ = tang
	})
	t.Run("tangents", func(t *testing.T) {
		tangs := w.Tangents([]float64{0, 0.5, 1.0})
		if len(tangs) != 3 {
			t.Fatalf("expected 3, got %d", len(tangs))
		}
	})
}

func TestWirePosition(t *testing.T) {
	w := makeRectWire(t)
	t.Run("position at", func(t *testing.T) {
		p := w.PositionAt(0.5, 0)
		_ = p
	})
	t.Run("positions", func(t *testing.T) {
		ps := w.Positions([]float64{0, 0.5, 1.0}, 0)
		if len(ps) != 3 {
			t.Fatalf("expected 3, got %d", len(ps))
		}
	})
}

func TestWireParams(t *testing.T) {
	w := makeRectWire(t)
	t.Run("param at", func(t *testing.T) {
		p := w.ParamAt(0.5)
		_ = p
	})
	t.Run("param at point", func(t *testing.T) {
		pt := w.StartPoint()
		p := w.ParamAtPoint(pt)
		if p < 0 {
			t.Fatalf("param at start point negative: %f", p)
		}
	})
	t.Run("params", func(t *testing.T) {
		pts := []Point3{w.StartPoint(), w.EndPoint()}
		params := w.Params(pts, 1e-6)
		if len(params) != 2 {
			t.Fatalf("expected 2, got %d", len(params))
		}
	})
	t.Run("params length", func(t *testing.T) {
		params := w.ParamsLength([]float64{0, 0.5, 1.0})
		if len(params) != 3 {
			t.Fatalf("expected 3, got %d", len(params))
		}
	})
}

func TestWireCenterRadius(t *testing.T) {
	w := TopoMakeWireFromCircle(5, NewPoint3([3]float64{0, 0, 0}), NewDir3FromXYZ([3]float64{0, 0, 1}))
	t.Run("center", func(t *testing.T) {
		c := w.Center()
		_ = c
	})
	t.Run("radius", func(t *testing.T) {
		r := w.Radius()
		if math.Abs(r-5) > 1e-6 {
			t.Fatalf("expected radius 5, got %f", r)
		}
	})
}

func TestWireSampleUniform(t *testing.T) {
	w := makeRectWire(t)
	t.Run("sample uniform", func(t *testing.T) {
		pts, params := w.SampleUniform(10)
		if len(pts) == 0 {
			t.Fatal("expected points from SampleUniform")
		}
		if len(params) == 0 {
			t.Fatal("expected params from SampleUniform")
		}
	})
}

func TestWireNormal(t *testing.T) {
	w := makeRectWire(t)
	t.Run("normal", func(t *testing.T) {
		n := w.Normal()
		_ = n
	})
}

func TestWireCurvature(t *testing.T) {
	w := TopoMakeWireFromCircle(5, NewPoint3([3]float64{0, 0, 0}), NewDir3FromXYZ([3]float64{0, 0, 1}))
	t.Run("curvature at", func(t *testing.T) {
		c := w.CurvatureAt(0.5, 0, 0.01)
		_ = c
	})
	t.Run("curvatures", func(t *testing.T) {
		cs := w.Curvatures([]float64{0, 0.5, 1.0}, 0, 0.01)
		if len(cs) != 3 {
			t.Fatalf("expected 3, got %d", len(cs))
		}
	})
}

func TestWireIterator(t *testing.T) {
	t.Run("iterate", func(t *testing.T) {
		w := makeRectWire(t)
		it := TopoMakeWireIterator(*w.ToShape())
		if it == nil {
			t.Fatal("TopoMakeWireIterator returned nil")
		}
		count := 0
		for {
			v := it.Next()
			if v == nil {
				break
			}
			count++
		}
		if count == 0 {
			t.Fatal("no sub-wires found")
		}
	})
}

func TestWireToShape(t *testing.T) {
	w := makeRectWire(t)
	t.Run("to shape", func(t *testing.T) {
		s := w.ToShape()
		if s == nil {
			t.Fatal("ToShape returned nil")
		}
	})
}

func TestWireLocationAt(t *testing.T) {
	w := makeRectWire(t)
	t.Run("location at", func(t *testing.T) {
		loc := w.LocationAt(0.5, 0, 0, false)
		_ = loc
	})
}

func TestWirePolygonConstructors(t *testing.T) {
	t.Run("polygon 2 point", func(t *testing.T) {
		w := TopoMakePolygonFromTwoPoint(NewPoint3([3]float64{0, 0, 0}), NewPoint3([3]float64{10, 0, 0}))
		if w == nil {
			t.Fatal("TopoMakePolygonFromTwoPoint failed")
		}
	})
	t.Run("polygon 3 point", func(t *testing.T) {
		w := TopoMakePolygonFromThreePoint(
			NewPoint3([3]float64{0, 0, 0}), NewPoint3([3]float64{10, 0, 0}),
			NewPoint3([3]float64{10, 10, 0}), false)
		if w == nil {
			t.Fatal("TopoMakePolygonFromThreePoint failed")
		}
	})
	t.Run("polygon 4 point", func(t *testing.T) {
		w := TopoMakePolygonFromFourPoint(
			NewPoint3([3]float64{0, 0, 0}), NewPoint3([3]float64{10, 0, 0}),
			NewPoint3([3]float64{10, 10, 0}), NewPoint3([3]float64{0, 10, 0}), true)
		if w == nil {
			t.Fatal("TopoMakePolygonFromFourPoint failed")
		}
	})
}

func TestWireTranslate(t *testing.T) {
	w := makeRectWire(t)
	t.Run("translate", func(t *testing.T) {
		v := NewVector3([3]float64{5, 0, 0})
		w.Translate(v)
	})
}
