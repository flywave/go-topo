package topo

import (
	"math"
	"testing"
)

func edgeFromLine(t *testing.T) *Edge {
	p1 := NewPoint3([3]float64{0, 0, 0})
	p2 := NewPoint3([3]float64{10, 0, 0})
	e := TopoMakeEdgeFromTwoPoint(p1, p2)
	if e == nil || e.IsNull() {
		t.Fatal("TopoMakeEdgeFromTwoPoint failed")
	}
	return e
}

func TestNewEdge(t *testing.T) {
	t.Run("empty", func(t *testing.T) {
		e := TopoMakeEdge()
		if e == nil {
			t.Fatal("TopoMakeEdge returned nil")
		}
	})
	t.Run("from two points", func(t *testing.T) {
		e := edgeFromLine(t)
		if e.Type() != TopoEdge {
			t.Fatalf("expected TopoEdge, got %d", e.Type())
		}
	})
	t.Run("from points slice", func(t *testing.T) {
		pts := []Point3{
			NewPoint3([3]float64{0, 0, 0}),
			NewPoint3([3]float64{10, 0, 0}),
		}
		e := TopoMakeEdgeFromPoints(pts)
		if e == nil {
			t.Fatal("TopoMakeEdgeFromPoints returned nil")
		}
	})
	t.Run("from polygon", func(t *testing.T) {
		e := TopoEdgeMakePolygonFromTwoPoint(NewPoint3([3]float64{0, 0, 0}), NewPoint3([3]float64{10, 0, 0}))
		if e == nil {
			t.Fatal("TopoEdgeMakePolygonFromTwoPoint failed")
		}
	})
}

func TestEdgeProperties(t *testing.T) {
	e := edgeFromLine(t)
	t.Run("is null", func(t *testing.T) {
		if e.IsNull() {
			t.Fatal("expected non-null")
		}
	})
	t.Run("is valid", func(t *testing.T) {
		if !e.IsValid() {
			t.Fatal("expected valid")
		}
	})
	t.Run("length", func(t *testing.T) {
		l := e.Length()
		if math.Abs(l-10) > 1e-6 {
			t.Fatalf("expected length 10, got %f", l)
		}
	})
	t.Run("start/end point", func(t *testing.T) {
		s := e.StartPoint()
		ep := e.EndPoint()
		d := s.Data()
		if math.Abs(d[0]) > 1e-6 || math.Abs(d[1]) > 1e-6 || math.Abs(d[2]) > 1e-6 {
			t.Fatalf("start point not at origin: %v", d)
		}
		d2 := ep.Data()
		if math.Abs(d2[0]-10) > 1e-6 {
			t.Fatalf("end point x not 10: %v", d2)
		}
	})
}

func TestEdgeBounds(t *testing.T) {
	e := edgeFromLine(t)
	t.Run("bounds", func(t *testing.T) {
		min, max := e.Bounds()
		if min > max {
			t.Fatalf("bounds invalid: %f > %f", min, max)
		}
	})
}

func TestEdgeParams(t *testing.T) {
	e := edgeFromLine(t)
	t.Run("param at", func(t *testing.T) {
		p := e.ParamAt(0.5)
		if p < 0 || p > 10 {
			t.Fatalf("param at 0.5 out of range: %f", p)
		}
	})
	t.Run("param at point", func(t *testing.T) {
		pt := NewPoint3([3]float64{5, 0, 0})
		p := e.ParamAtPoint(pt)
		if p < 0 {
			t.Fatalf("param at point negative: %f", p)
		}
	})
	t.Run("params", func(t *testing.T) {
		pts := []Point3{NewPoint3([3]float64{0, 0, 0}), NewPoint3([3]float64{10, 0, 0})}
		params := e.Params(pts, 1e-6)
		if len(params) != 2 {
			t.Fatalf("expected 2 params, got %d", len(params))
		}
	})
	t.Run("params length", func(t *testing.T) {
		locs := []float64{0, 0.5, 1.0}
		params := e.ParamsLength(locs)
		if len(params) != 3 {
			t.Fatalf("expected 3 params, got %d", len(params))
		}
	})
}

func TestEdgeTangent(t *testing.T) {
	e := edgeFromLine(t)
	t.Run("tangent at", func(t *testing.T) {
		tang := e.TangentAt(0.5)
		d := tang.Data()
		if math.Abs(d[0]-1) > 1e-6 {
			t.Fatalf("expected tangent (1,0,0), got %v", d)
		}
	})
	t.Run("tangents", func(t *testing.T) {
		tangs := e.Tangents([]float64{0, 0.5, 1.0})
		if len(tangs) != 3 {
			t.Fatalf("expected 3 tangents, got %d", len(tangs))
		}
	})
}

func TestEdgeCurvature(t *testing.T) {
	e := edgeFromLine(t)
	t.Run("curvature at", func(t *testing.T) {
		c := e.CurvatureAt(0.5, 0, 0.01)
		if c != 0 {
			t.Logf("line curvature: %f", c)
		}
	})
	t.Run("curvatures", func(t *testing.T) {
		cs := e.Curvatures([]float64{0, 0.5, 1.0}, 0, 0.01)
		if len(cs) != 3 {
			t.Fatalf("expected 3 curvatures, got %d", len(cs))
		}
	})
}

func TestEdgePosition(t *testing.T) {
	e := edgeFromLine(t)
	t.Run("position at", func(t *testing.T) {
		p := e.PositionAt(0.5, 0)
		d := p.Data()
		if math.Abs(d[0]-5) > 1e-6 {
			t.Fatalf("expected x=5, got %f", d[0])
		}
	})
	t.Run("positions", func(t *testing.T) {
		ps := e.Positions([]float64{0, 0.5, 1.0}, 0)
		if len(ps) != 3 {
			t.Fatalf("expected 3 positions, got %d", len(ps))
		}
	})
}

func TestEdgeSampleUniform(t *testing.T) {
	e := edgeFromLine(t)
	t.Run("sample uniform", func(t *testing.T) {
		pts, params := e.SampleUniform(5)
		if len(pts) == 0 {
			t.Fatal("expected points from SampleUniform")
		}
		if len(params) == 0 {
			t.Fatal("expected params from SampleUniform")
		}
	})
}

func TestEdgeCenterRadius(t *testing.T) {
	e := edgeFromLine(t)
	t.Run("center", func(t *testing.T) {
		c := e.Center()
		_ = c
	})
	t.Run("radius", func(t *testing.T) {
		r := e.Radius()
		_ = r
	})
}

func TestEdgeFlags(t *testing.T) {
	e := edgeFromLine(t)
	t.Run("degenerated", func(t *testing.T) {
		_ = e.IsDegenerated()
	})
	t.Run("closed", func(t *testing.T) {
		_ = e.IsClosed()
	})
	t.Run("infinite", func(t *testing.T) {
		_ = e.IsInifinite()
	})
	t.Run("curve3d", func(t *testing.T) {
		_ = e.IsCurve3d()
	})
	t.Run("num vertices", func(t *testing.T) {
		n := e.NumVertices()
		if n < 2 {
			t.Fatalf("expected at least 2 vertices, got %d", n)
		}
	})
	t.Run("tolerance", func(t *testing.T) {
		tol := e.Tolerance()
		if tol < 0 {
			t.Fatalf("negative tolerance: %f", tol)
		}
	})
}

func TestEdgeReverse(t *testing.T) {
	e := edgeFromLine(t)
	t.Run("reverse", func(t *testing.T) {
		e.Reverse()
		_ = e.StartPoint()
	})
}

func TestEdgeTransform(t *testing.T) {
	e := edgeFromLine(t)
	t.Run("translate", func(t *testing.T) {
		v := NewVector3([3]float64{5, 0, 0})
		e.Translate(v)
		s := e.StartPoint().Data()
		if math.Abs(s[0]-5) > 1e-6 {
			t.Fatalf("after translate, start x should be 5, got %f", s[0])
		}
	})
}

func TestEdgeCopy(t *testing.T) {
	e := edgeFromLine(t)
	t.Run("copy", func(t *testing.T) {
		e2 := e.Copy()
		if e2 == nil {
			t.Fatal("Copy returned nil")
		}
		_ = e2.Length()
	})
}

func TestEdgeToShape(t *testing.T) {
	e := edgeFromLine(t)
	t.Run("to shape", func(t *testing.T) {
		s := e.ToShape()
		if s == nil {
			t.Fatal("ToShape returned nil")
		}
	})
}

func TestEdgeIterator(t *testing.T) {
	t.Run("iterate", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.RectCentered(10, 10)
		shape := r1.Value()
		it := TopoMakeEdgeIterator(*shape)
		if it == nil {
			t.Fatal("TopoMakeEdgeIterator returned nil")
		}
		count := 0
		for {
			e := it.Next()
			if e == nil {
				break
			}
			count++
			_ = e.Length()
		}
		if count == 0 {
			t.Fatal("no edges found")
		}
	})
}

func TestEdgeNormal(t *testing.T) {
	e := edgeFromLine(t)
	t.Run("normal", func(t *testing.T) {
		n := e.Normal()
		_ = n
	})
}

func TestEdgeLocationAt(t *testing.T) {
	e := edgeFromLine(t)
	t.Run("location at", func(t *testing.T) {
		loc := e.LocationAt(0.5, 0, 0, false)
		if loc == nil {
			t.Log("LocationAt returned nil (may not apply to line)")
		}
	})
}

func TestEdgeThreePointArc(t *testing.T) {
	t.Run("three point arc", func(t *testing.T) {
		e := TopoMakeThreePointArc(
			NewPoint3([3]float64{0, 0, 0}),
			NewPoint3([3]float64{5, 5, 0}),
			NewPoint3([3]float64{10, 0, 0}),
		)
		if e == nil || e.IsNull() {
			t.Fatal("TopoMakeThreePointArc failed")
		}
		t.Logf("arc length: %f", e.Length())
	})
}

func TestEdgePolygonMulti(t *testing.T) {
	t.Run("polygon 3 points", func(t *testing.T) {
		e := TopoEdgeMakePolygonFromThreePoint(
			NewPoint3([3]float64{0, 0, 0}),
			NewPoint3([3]float64{10, 0, 0}),
			NewPoint3([3]float64{10, 10, 0}), false,
		)
		if e == nil {
			t.Fatal("TopoEdgeMakePolygonFromThreePoint failed")
		}
	})
	t.Run("rect", func(t *testing.T) {
		e := TopoMakeRect(10, 5)
		if e == nil {
			t.Fatal("TopoMakeRect failed")
		}
	})
}

func TestEdgeMakeCircle(t *testing.T) {
	t.Run("make circle", func(t *testing.T) {
		e := TopoMakeCircle(5, NewPoint3([3]float64{0, 0, 0}),
			NewVector3([3]float64{0, 0, 1}), 0, 360, true)
		if e == nil || e.IsNull() {
			t.Fatal("TopoMakeCircle failed")
		}
		if e.IsClosed() {
			t.Log("circle is closed")
		}
	})
}

func TestEdgePropertiesGetters(t *testing.T) {
	e := edgeFromLine(t)
	t.Run("bbox", func(t *testing.T) {
		_ = e.BBox()
	})
	t.Run("hash", func(t *testing.T) {
		_ = e.Hash()
	})
	t.Run("get orientation", func(t *testing.T) {
		_ = e.GetOrientation()
	})
	t.Run("get location", func(t *testing.T) {
		_ = e.GetLocation()
	})
	t.Run("fix shape", func(t *testing.T) {
		e.FixShape()
	})
}

func TestEdgeSetGet(t *testing.T) {
	e := edgeFromLine(t)
	t.Run("set orientation", func(t *testing.T) {
		e.SetOrientation(FORWARD)
		if e.GetOrientation() != FORWARD {
			t.Fatal("orientation mismatch")
		}
	})
	t.Run("set label", func(t *testing.T) {
		e.SetLabel("test_edge")
		if e.GetLabel() != "test_edge" {
			t.Fatal("label mismatch")
		}
	})
	t.Run("set colour", func(t *testing.T) {
		e.SetSurfaceColour(NewColor([3]float64{1, 0, 0}))
		e.SetCurveColour(NewColor([3]float64{0, 1, 0}))
	})
	t.Run("set uv", func(t *testing.T) {
		e.SetUVOrigin(0.5, 0.5)
		e.SetUVRepeat(2.0, 2.0)
		e.SetScaleU(1.5)
		e.SetScaleV(1.5)
		_, _ = e.GetUVOrigin()
		_, _ = e.GetUVRepeat()
		_, _ = e.GetUVScale()
		_, _ = e.GetUVAutoScaleSize()
	})
	t.Run("set texture", func(t *testing.T) {
		e.SetTextureMapType(TextureNormal)
		_ = e.GetTxtureMapType()
	})
	t.Run("set rotation angle", func(t *testing.T) {
		e.SetRotationAngle(45)
		if e.GetRotationAngle() != 45 {
			t.Fatal("rotation angle mismatch")
		}
	})
}

func TestEdgeTransformedCopy(t *testing.T) {
	e := edgeFromLine(t)
	t.Run("translated", func(t *testing.T) {
		v := NewVector3([3]float64{5, 0, 0})
		e2 := e.Translated(v)
		if e2 == nil {
			t.Fatal("Translated returned nil")
		}
	})
	t.Run("scaled", func(t *testing.T) {
		p := NewPoint3([3]float64{0, 0, 0})
		e2 := e.Scaled(2.0, p)
		if e2 == nil {
			t.Fatal("Scaled returned nil")
		}
	})
}
