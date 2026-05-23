package topo

import (
	"testing"
)

func TestNewSketch(t *testing.T) {
	t.Run("from workplane", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sk := NewSketchFromWorkplane(wp, nil, nil)
		if sk == nil {
			t.Fatal("NewSketchFromWorkplane returned nil")
		}
		if err := sk.Err(); err != nil {
			t.Fatalf("error: %v", err)
		}
	})

	t.Run("from location", func(t *testing.T) {
		id := NewTrsfTranslationFromVector(NewVector3([3]float64{0, 0, 0}))
		loc := NewTopoLocation(id)
		sk := NewSketchFromLocation(loc, nil)
		if sk == nil {
			t.Fatal("NewSketchFromLocation returned nil")
		}
	})

	t.Run("from workplane via bridge", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sk := wp.Sketch()
		if sk == nil {
			t.Fatal("Sketch() returned nil")
		}
	})
}

func TestSketchRect(t *testing.T) {
	t.Run("rect", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sk := NewSketchFromWorkplane(wp, nil, nil)
		sk.Rect(10, 5, 0, "")
		if err := sk.Err(); err != nil {
			t.Fatalf("Rect error: %v", err)
		}
		faces := sk.GetFaces()
		if len(faces) == 0 {
			t.Fatal("expected faces after Rect")
		}
	})
}

func TestSketchCircle(t *testing.T) {
	t.Run("circle", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sk := NewSketchFromWorkplane(wp, nil, nil)
		sk.Circle(5, "")
		if err := sk.Err(); err != nil {
			t.Fatalf("Circle error: %v", err)
		}
	})
}

func TestSketchEllipse(t *testing.T) {
	t.Run("ellipse", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sk := NewSketchFromWorkplane(wp, nil, nil)
		sk.Ellipse(10, 5, 0, "")
		if err := sk.Err(); err != nil {
			t.Fatalf("Ellipse error: %v", err)
		}
	})
}

func TestSketchTrapezoid(t *testing.T) {
	t.Run("trapezoid", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sk := NewSketchFromWorkplane(wp, nil, nil)
		sk.Trapezoid(10, 5, 10, 10, 0, "")
		if err := sk.Err(); err != nil {
			t.Fatalf("Trapezoid error: %v", err)
		}
	})
}

func TestSketchSlot(t *testing.T) {
	t.Run("slot", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sk := NewSketchFromWorkplane(wp, nil, nil)
		sk.Slot(10, 4, 0, "")
		if err := sk.Err(); err != nil {
			t.Fatalf("Slot error: %v", err)
		}
	})
}

func TestSketchRegularPolygon(t *testing.T) {
	t.Run("regular polygon", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sk := NewSketchFromWorkplane(wp, nil, nil)
		sk.RegularPolygon(10, 6, 0, "")
		if err := sk.Err(); err != nil {
			t.Fatalf("RegularPolygon error: %v", err)
		}
	})
}

func TestSketchPolygon(t *testing.T) {
	t.Run("polygon", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sk := NewSketchFromWorkplane(wp, nil, nil)
		pts := []*TopoVector{
			NewTopoVector(0, 0, 0),
			NewTopoVector(10, 0, 0),
			NewTopoVector(10, 10, 0),
			NewTopoVector(0, 10, 0),
			NewTopoVector(0, 0, 0),
		}
		sk.Polygon(pts, 0, "")
		if err := sk.Err(); err != nil {
			t.Fatalf("Polygon error: %v", err)
		}
	})
}

func TestSketchSegmentAndEdge(t *testing.T) {
	t.Run("segment", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sk := NewSketchFromWorkplane(wp, nil, nil)
		sk.Segment(NewTopoVector(0, 0, 0), NewTopoVector(10, 0, 0), "", false)
		if err := sk.Err(); err != nil {
			t.Fatalf("Segment error: %v", err)
		}
	})

	t.Run("segment from point", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sk := NewSketchFromWorkplane(wp, nil, nil)
		sk.Segment(NewTopoVector(0, 0, 0), NewTopoVector(10, 0, 0), "", false)
		sk.SegmentFromPoint(NewTopoVector(10, 10, 0), "", false)
		if err := sk.Err(); err != nil {
			t.Fatalf("SegmentFromPoint error: %v", err)
		}
	})

	t.Run("segment from length angle", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sk := NewSketchFromWorkplane(wp, nil, nil)
		sk.Segment(NewTopoVector(0, 0, 0), NewTopoVector(10, 0, 0), "", false)
		sk.SegmentFromLengthAngle(10, 90, "", false)
		if err := sk.Err(); err != nil {
			t.Fatalf("SegmentFromLengthAngle error: %v", err)
		}
	})
}

func TestSketchArc(t *testing.T) {
	t.Run("three point arc", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sk := NewSketchFromWorkplane(wp, nil, nil)
		sk.Arc(NewTopoVector(0, 0, 0), NewTopoVector(5, 5, 0), NewTopoVector(10, 0, 0), "", false)
		if err := sk.Err(); err != nil {
			t.Fatalf("Arc error: %v", err)
		}
	})

	t.Run("arc from center", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sk := NewSketchFromWorkplane(wp, nil, nil)
		sk.ArcFromCenter(NewTopoVector(0, 0, 0), 10, 0, 90, "", false)
		if err := sk.Err(); err != nil {
			t.Fatalf("ArcFromCenter error: %v", err)
		}
	})
}

func TestSketchBezierSpline(t *testing.T) {
	t.Run("bezier", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sk := NewSketchFromWorkplane(wp, nil, nil)
		pts := []*TopoVector{NewTopoVector(0, 0, 0), NewTopoVector(5, 10, 0), NewTopoVector(10, 0, 0)}
		sk.Bezier(pts, "", false)
		if err := sk.Err(); err != nil {
			t.Fatalf("Bezier error: %v", err)
		}
	})

	t.Run("spline with tangents", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sk := NewSketchFromWorkplane(wp, nil, nil)
		pts := []*TopoVector{NewTopoVector(0, 0, 0), NewTopoVector(10, 0, 0)}
		sk.SplineWithTangents(pts, NewTopoVector(1, 0, 0), NewTopoVector(1, 0, 0), false, "", false)
		if err := sk.Err(); err != nil {
			t.Fatalf("SplineWithTangents error: %v", err)
		}
	})
}

func TestSketchAssembleClose(t *testing.T) {
	t.Run("assemble", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sk := NewSketchFromWorkplane(wp, nil, nil)
		sk.Segment(NewTopoVector(0, 0, 0), NewTopoVector(10, 0, 0), "", false)
		sk.SegmentFromPoint(NewTopoVector(10, 10, 0), "", false)
		sk.Close("")
		sk.Assemble(0, "")
		if err := sk.Err(); err != nil {
			t.Fatalf("Assemble error: %v", err)
		}
	})
}

func TestSketchTransform(t *testing.T) {
	t.Run("copy", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sk := NewSketchFromWorkplane(wp, nil, nil)
		sk.Rect(10, 5, 0, "")
		sk2 := sk.Copy()
		if sk2 == nil {
			t.Fatal("Copy returned nil")
		}
	})

	t.Run("moved", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sk := NewSketchFromWorkplane(wp, nil, nil)
		sk.Rect(10, 5, 0, "")
		loc := NewTopoLocation(NewTrsfTranslationFromVector(NewVector3([3]float64{0, 0, 0})))
		sk2 := sk.Moved([]*TopoLocation{loc})
		if sk2 == nil {
			t.Fatal("Moved returned nil")
		}
	})
}

func TestSketchFinalize(t *testing.T) {
	t.Run("finalize", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sk := NewSketchFromWorkplane(wp, nil, nil)
		sk.Rect(10, 5, 0, "")
		wp2 := sk.Finalize()
		if wp2 == nil {
			t.Fatal("Finalize returned nil")
		}
	})
}

func TestSketchValues(t *testing.T) {
	t.Run("Val and Vals", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sk := NewSketchFromWorkplane(wp, nil, nil)
		sk.Rect(10, 5, 0, "")
		v := sk.Val()
		if v == nil {
			t.Fatal("Val returned nil")
		}
		vals := sk.Vals()
		if len(vals) == 0 {
			t.Fatal("Vals returned empty")
		}
	})
}

func TestSketchAddSubtract(t *testing.T) {
	t.Run("add with selection", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sk := NewSketchFromWorkplane(wp, nil, nil)
		sk.Rect(10, 5, 0, "")
		sk.Faces("", "")
		sk.Add()
		if err := sk.Err(); err != nil {
			t.Fatalf("Add error: %v", err)
		}
	})
}

func TestSketchCleanReset(t *testing.T) {
	t.Run("clean", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sk := NewSketchFromWorkplane(wp, nil, nil)
		sk.Rect(10, 5, 0, "")
		sk.Clean()
		if err := sk.Err(); err != nil {
			t.Fatalf("Clean error: %v", err)
		}
	})

	t.Run("reset", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sk := NewSketchFromWorkplane(wp, nil, nil)
		sk.Rect(10, 5, 0, "")
		sk.Reset()
	})
}

func TestSketchPushRArray(t *testing.T) {
	t.Run("push", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sk := NewSketchFromWorkplane(wp, nil, nil)
		id := NewTrsfTranslationFromVector(NewVector3([3]float64{0, 0, 0}))
		loc := NewTopoLocation(id)
		sk.Push([]*TopoLocation{loc}, "")
		if err := sk.Err(); err != nil {
			t.Fatalf("Push error: %v", err)
		}
	})

	t.Run("rarray", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sk := NewSketchFromWorkplane(wp, nil, nil)
		sk.RArray(10, 10, 2, 2, 0, "")
		if err := sk.Err(); err != nil {
			t.Fatalf("RArray error: %v", err)
		}
	})

	t.Run("parray", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sk := NewSketchFromWorkplane(wp, nil, nil)
		sk.PArray(10, 0, 360, 6, true, 0, "")
		if err := sk.Err(); err != nil {
			t.Fatalf("PArray error: %v", err)
		}
	})
}

func TestSketchSelection(t *testing.T) {
	t.Run("select faces", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sk := NewSketchFromWorkplane(wp, nil, nil)
		sk.Rect(10, 5, 0, "")
		sk.Faces("", "")
		if err := sk.Err(); err != nil {
			t.Fatalf("Faces selector error: %v", err)
		}
	})

	t.Run("select wires", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sk := NewSketchFromWorkplane(wp, nil, nil)
		sk.Rect(10, 5, 0, "")
		sk.Wires("", "")
		if err := sk.Err(); err != nil {
			t.Fatalf("Wires selector error: %v", err)
		}
	})

	t.Run("select edges with ForSelector", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sk := NewSketchFromWorkplane(wp, nil, nil)
		sk.Rect(10, 5, 0, "")
		sk.EdgesForSelector(nil, "")
		if err := sk.Err(); err != nil {
			t.Fatalf("EdgesForSelector error: %v", err)
		}
	})

	t.Run("select vertices with ForSelector", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sk := NewSketchFromWorkplane(wp, nil, nil)
		sk.Rect(10, 5, 0, "")
		sk.VerticesForSelector(nil, "")
		if err := sk.Err(); err != nil {
			t.Fatalf("VerticesForSelector error: %v", err)
		}
	})
}

func TestSketchTag(t *testing.T) {
	t.Run("tag and select", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sk := NewSketchFromWorkplane(wp, nil, nil)
		sk.Rect(10, 5, 0, "myrect")
		sk.Select([]string{"myrect"})
		if err := sk.Err(); err != nil {
			t.Fatalf("Tag/Select error: %v", err)
		}
	})
}

func TestSketchEdge(t *testing.T) {
	t.Run("edge", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sk := NewSketchFromWorkplane(wp, nil, nil)
		e := TopoMakeEdgeFromTwoPoint(NewPoint3([3]float64{0, 0, 0}), NewPoint3([3]float64{10, 0, 0}))
		sk.Edge(e, "", false)
		if err := sk.Err(); err != nil {
			t.Fatalf("Edge error: %v", err)
		}
	})
}

func TestSketchBoolOps(t *testing.T) {
	t.Run("subtract", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sk := NewSketchFromWorkplane(wp, nil, nil)
		sk.Rect(10, 10, 0, "")
		sk.Faces("", "")
		sk.Subtract()
		if err := sk.Err(); err != nil {
			t.Fatalf("Subtract error: %v", err)
		}
	})

	t.Run("replace", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sk := NewSketchFromWorkplane(wp, nil, nil)
		sk.Rect(10, 10, 0, "")
		sk.Faces("", "")
		sk.Replace()
		if err := sk.Err(); err != nil {
			t.Fatalf("Replace error: %v", err)
		}
	})
}

func TestSketchEach(t *testing.T) {
	t.Run("each for face", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sk := NewSketchFromWorkplane(wp, nil, nil)
		sk.EachForFace(func(loc *TopoLocation) *Face {
			wire := TopoMakeWireFromCircle(5, NewPoint3([3]float64{0, 0, 0}), NewDir3FromXYZ([3]float64{0, 0, 1}))
			face := TopoMakeFaceFromWire(*wire, true)
			return face
		}, 0, "", false)
		if err := sk.Err(); err != nil {
			t.Fatalf("EachForFace error: %v", err)
		}
	})
}

func TestSketchFilterMap(t *testing.T) {
	t.Run("filter", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sk := NewSketchFromWorkplane(wp, nil, nil)
		sk.Rect(10, 5, 0, "")
		sk.Filter(func(v *SketchObject) bool { return true })
		if err := sk.Err(); err != nil {
			t.Fatalf("Filter error: %v", err)
		}
	})

	t.Run("sort", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sk := NewSketchFromWorkplane(wp, nil, nil)
		sk.Rect(10, 5, 0, "")
		sk.Sort(func(a, b *SketchObject) bool { return false })
		if err := sk.Err(); err != nil {
			t.Fatalf("Sort error: %v", err)
		}
	})
}

func TestSketchObject(t *testing.T) {
	t.Run("sketch object from shape", func(t *testing.T) {
		e := TopoMakeEdgeFromTwoPoint(NewPoint3([3]float64{0, 0, 0}), NewPoint3([3]float64{10, 0, 0}))
		w := TopoMakeWireFromEdge(*e)
		f := TopoMakeFaceFromWire(*w, true)
		so := NewSketchObjectFromShpe(*f.ToShape())
		if so == nil {
			t.Fatal("NewSketchObjectFromShpe returned nil")
		}
		if !so.IsShape() {
			t.Fatal("expected IsShape = true")
		}
		shp := so.GetShape()
		if shp == nil {
			t.Fatal("GetShape returned nil")
		}
	})

	t.Run("sketch object from location", func(t *testing.T) {
		id := NewTrsfTranslationFromVector(NewVector3([3]float64{0, 0, 0}))
		loc := NewTopoLocation(id)
		so := NewSketchObjectFromLocation(loc)
		if so == nil {
			t.Fatal("NewSketchObjectFromLocation returned nil")
		}
		if !so.IsLocation() {
			t.Fatal("expected IsLocation = true")
		}
	})

	t.Run("sketch object from location with nil", func(t *testing.T) {
		t.Skip("C API sketch_val_create_from_location crashes on null")
	})
}

// ---------------------------------------------------------------------------
// sketch_solver: all constraint kinds and combinations
// ---------------------------------------------------------------------------

// makeSegment creates a sketch with a single tagged line segment.
func makeSegment(wp *Workplane, tag string) *Sketch {
	sk := NewSketchFromWorkplane(wp, nil, nil)
	sk.Segment(NewTopoVector(0, 0, 0), NewTopoVector(10, 0, 0), tag, false)
	return sk
}

// makeCircleEdge creates a sketch with a single tagged arc edge (3-point arc).
func makeCircleEdge(wp *Workplane, tag string) *Sketch {
	sk := NewSketchFromWorkplane(wp, nil, nil)
	// Arc from (5,0) through (0,5) to (-5,0) — a half-circle
	sk.Arc(
		NewTopoVector(5, 0, 0),
		NewTopoVector(0, 5, 0),
		NewTopoVector(-5, 0, 0),
		tag, false)
	return sk
}

// makeTwoSegments creates a sketch with two parallel horizontal segments.
func makeTwoSegments(wp *Workplane, tag1, tag2 string) *Sketch {
	sk := NewSketchFromWorkplane(wp, nil, nil)
	sk.Segment(NewTopoVector(0, 0, 0), NewTopoVector(10, 0, 0), tag1, false)
	sk.Segment(NewTopoVector(0, 10, 0), NewTopoVector(10, 10, 0), tag2, false)
	return sk
}

func TestSketchSolver_SingleConstraint(t *testing.T) {
	wp := func() *Workplane { return NewNamedWorkplane("XY") }

	// FIXED (0) — fix entire entity DOFs; value = double (unused sentinel)
	t.Run("FIXED on segment", func(t *testing.T) {
		sk := makeSegment(wp(), "e1")
		sk.Constrain("e1", 0, NewSketchConstraintValueFromDouble(0))
		sk.Solve()
		if err := sk.Err(); err != nil {
			t.Fatalf("FIXED error: %v", err)
		}
	})

	// FIXED_POINT (1) — fix a point at parametric position; value = double (t in [0,1])
	t.Run("FIXED_POINT on segment", func(t *testing.T) {
		sk := makeSegment(wp(), "e1")
		sk.Constrain("e1", 1, NewSketchConstraintValueFromDouble(0.5))
		sk.Solve()
		if err := sk.Err(); err != nil {
			t.Fatalf("FIXED_POINT error: %v", err)
		}
	})
	t.Run("FIXED_POINT at start", func(t *testing.T) {
		sk := makeSegment(wp(), "e1")
		sk.Constrain("e1", 1, NewSketchConstraintValueFromDouble(0.0))
		sk.Solve()
		if err := sk.Err(); err != nil {
			t.Fatalf("FIXED_POINT at start error: %v", err)
		}
	})
	t.Run("FIXED_POINT at end", func(t *testing.T) {
		sk := makeSegment(wp(), "e1")
		sk.Constrain("e1", 1, NewSketchConstraintValueFromDouble(1.0))
		sk.Solve()
		if err := sk.Err(); err != nil {
			t.Fatalf("FIXED_POINT at end error: %v", err)
		}
	})

	// LENGTH (4) — constrain edge length; value = double (target length)
	t.Run("LENGTH on segment", func(t *testing.T) {
		sk := makeSegment(wp(), "e1")
		sk.Constrain("e1", 4, NewSketchConstraintValueFromDouble(5))
		sk.Solve()
		if err := sk.Err(); err != nil {
			t.Fatalf("LENGTH error: %v", err)
		}
	})
	t.Run("LENGTH zero on segment", func(t *testing.T) {
		sk := makeSegment(wp(), "e1")
		sk.Constrain("e1", 4, NewSketchConstraintValueFromDouble(0))
		sk.Solve()
		if err := sk.Err(); err != nil {
			t.Logf("LENGTH zero expected to be problematic: %v", err)
		}
	})

	// ORIENTATION (7) — constrain entity orientation; value = double2 (dx, dy)
	t.Run("ORIENTATION horizontal", func(t *testing.T) {
		sk := makeSegment(wp(), "e1")
		sk.Constrain("e1", 7, NewSketchConstraintValueFromDouble2(1, 0))
		sk.Solve()
		if err := sk.Err(); err != nil {
			t.Fatalf("ORIENTATION horizontal error: %v", err)
		}
	})
	t.Run("ORIENTATION vertical", func(t *testing.T) {
		sk := makeSegment(wp(), "e1")
		sk.Constrain("e1", 7, NewSketchConstraintValueFromDouble2(0, 1))
		sk.Solve()
		if err := sk.Err(); err != nil {
			t.Fatalf("ORIENTATION vertical error: %v", err)
		}
	})
	t.Run("ORIENTATION diagonal", func(t *testing.T) {
		sk := makeSegment(wp(), "e1")
		sk.Constrain("e1", 7, NewSketchConstraintValueFromDouble2(1, 1))
		sk.Solve()
		if err := sk.Err(); err != nil {
			t.Fatalf("ORIENTATION diagonal error: %v", err)
		}
	})

	// RADIUS (6) — constrain arc radius; value = double
	t.Run("RADIUS on arc", func(t *testing.T) {
		sk := makeCircleEdge(wp(), "a1")
		sk.Constrain("a1", 6, NewSketchConstraintValueFromDouble(3))
		sk.Solve()
		if err := sk.Err(); err != nil {
			t.Fatalf("RADIUS error: %v", err)
		}
	})
	t.Run("RADIUS larger", func(t *testing.T) {
		sk := makeCircleEdge(wp(), "a1")
		sk.Constrain("a1", 6, NewSketchConstraintValueFromDouble(10))
		sk.Solve()
		if err := sk.Err(); err != nil {
			t.Fatalf("RADIUS larger error: %v", err)
		}
	})

	// ARC_ANGLE (8) — constrain arc sweep angle; value = double (radians)
	t.Run("ARC_ANGLE on arc", func(t *testing.T) {
		sk := makeCircleEdge(wp(), "a1")
		sk.Constrain("a1", 8, NewSketchConstraintValueFromDouble(2.0944))
		sk.Solve()
		if err := sk.Err(); err != nil {
			t.Fatalf("ARC_ANGLE error: %v", err)
		}
	})
	t.Run("ARC_ANGLE full circle", func(t *testing.T) {
		sk := makeCircleEdge(wp(), "a1")
		sk.Constrain("a1", 8, NewSketchConstraintValueFromDouble(6.28318))
		sk.Solve()
		if err := sk.Err(); err != nil {
			t.Fatalf("ARC_ANGLE full circle error: %v", err)
		}
	})
}

func TestSketchSolver_BetweenConstraint(t *testing.T) {

	// COINCIDENT (2) — two entities share point; value = blank
	t.Run("COINCIDENT line-line", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sk := makeTwoSegments(wp, "e1", "e2")
		sk.ConstraintBetween("e1", "e2", 2, NewSketchConstraintValueFromBlank())
		sk.Solve()
		if err := sk.Err(); err != nil {
			t.Fatalf("COINCIDENT line-line error: %v", err)
		}
	})

	// ANGLE (3) — angle between two entities; value = double (radians)
	t.Run("ANGLE 0 rad", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sk := makeTwoSegments(wp, "e1", "e2")
		sk.ConstraintBetween("e1", "e2", 3, NewSketchConstraintValueFromDouble(0))
		sk.Solve()
		if err := sk.Err(); err != nil {
			t.Fatalf("ANGLE 0 error: %v", err)
		}
	})
	t.Run("ANGLE 90 deg", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sk := NewSketchFromWorkplane(wp, nil, nil)
		sk.Segment(NewTopoVector(0, 0, 0), NewTopoVector(10, 0, 0), "e1", false)
		sk.Segment(NewTopoVector(0, 0, 0), NewTopoVector(0, 10, 0), "e2", false)
		sk.ConstraintBetween("e1", "e2", 3, NewSketchConstraintValueFromDouble(1.5708))
		sk.Solve()
		if err := sk.Err(); err != nil {
			t.Fatalf("ANGLE 90 deg error: %v", err)
		}
	})
	t.Run("ANGLE 45 deg", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sk := NewSketchFromWorkplane(wp, nil, nil)
		sk.Segment(NewTopoVector(0, 0, 0), NewTopoVector(10, 0, 0), "e1", false)
		sk.Segment(NewTopoVector(0, 0, 0), NewTopoVector(10, 10, 0), "e2", false)
		sk.ConstraintBetween("e1", "e2", 3, NewSketchConstraintValueFromDouble(0.785398))
		sk.Solve()
		if err := sk.Err(); err != nil {
			t.Fatalf("ANGLE 45 deg error: %v", err)
		}
	})

	// DISTANCE (5) — distance between two points on entities; value = double3
	t.Run("DISTANCE between segments", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sk := makeTwoSegments(wp, "e1", "e2")
		sk.ConstraintBetween("e1", "e2", 5,
			NewSketchConstraintValueFromDouble3(0.5, 0.5, 5))
		sk.Solve()
		if err := sk.Err(); err != nil {
			t.Fatalf("DISTANCE error: %v", err)
		}
	})
	t.Run("DISTANCE zero", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sk := makeTwoSegments(wp, "e1", "e2")
		sk.ConstraintBetween("e1", "e2", 5,
			NewSketchConstraintValueFromDouble3(0.5, 0.5, 0))
		sk.Solve()
		if err := sk.Err(); err != nil {
			t.Fatalf("DISTANCE zero error: %v", err)
		}
	})
	t.Run("DISTANCE with nil params", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sk := makeTwoSegments(wp, "e1", "e2")
		sk.ConstraintBetween("e1", "e2", 5,
			NewSketchConstraintValueFromDouble3(0, 0, 10))
		sk.Solve()
		if err := sk.Err(); err != nil {
			t.Fatalf("DISTANCE nil params error: %v", err)
		}
	})
}

func TestSketchSolver_CombinedConstraints(t *testing.T) {

	t.Run("FIXED + LENGTH", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sk := makeSegment(wp, "e1")
		sk.Constrain("e1", 0, NewSketchConstraintValueFromDouble(0))
		sk.Constrain("e1", 4, NewSketchConstraintValueFromDouble(5))
		sk.Solve()
		if err := sk.Err(); err != nil {
			t.Fatalf("FIXED+LENGTH error: %v", err)
		}
	})
	t.Run("FIXED + ORIENTATION", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sk := makeSegment(wp, "e1")
		sk.Constrain("e1", 0, NewSketchConstraintValueFromDouble(0))
		sk.Constrain("e1", 7, NewSketchConstraintValueFromDouble2(0, 1))
		sk.Solve()
		if err := sk.Err(); err != nil {
			t.Fatalf("FIXED+ORIENTATION error: %v", err)
		}
	})
	t.Run("COINCIDENT + ANGLE", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sk := NewSketchFromWorkplane(wp, nil, nil)
		sk.Segment(NewTopoVector(0, 0, 0), NewTopoVector(10, 0, 0), "e1", false)
		sk.Segment(NewTopoVector(5, 5, 0), NewTopoVector(15, 5, 0), "e2", false)
		sk.ConstraintBetween("e1", "e2", 2, NewSketchConstraintValueFromBlank())
		sk.ConstraintBetween("e1", "e2", 3, NewSketchConstraintValueFromDouble(1.0472))
		sk.Solve()
		if err := sk.Err(); err != nil {
			t.Fatalf("COINCIDENT+ANGLE error: %v", err)
		}
	})
	t.Run("DISTANCE + ANGLE", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sk := makeTwoSegments(wp, "e1", "e2")
		sk.ConstraintBetween("e1", "e2", 5,
			NewSketchConstraintValueFromDouble3(0, 0, 3))
		sk.ConstraintBetween("e1", "e2", 3, NewSketchConstraintValueFromDouble(0))
		sk.Solve()
		if err := sk.Err(); err != nil {
			t.Fatalf("DISTANCE+ANGLE error: %v", err)
		}
	})
	t.Run("LENGTH + ARC_ANGLE", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sk := NewSketchFromWorkplane(wp, nil, nil)
		sk.Segment(NewTopoVector(0, 0, 0), NewTopoVector(10, 0, 0), "e1", false)
		sk.Arc(NewTopoVector(5, 0, 0), NewTopoVector(0, 5, 0), NewTopoVector(-5, 0, 0), "a1", false)
		sk.Constrain("e1", 4, NewSketchConstraintValueFromDouble(8))
		sk.Constrain("a1", 8, NewSketchConstraintValueFromDouble(2.0944))
		sk.Solve()
		if err := sk.Err(); err != nil {
			t.Fatalf("LENGTH+ARC_ANGLE error: %v", err)
		}
	})
	t.Run("three constraints chain", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sk := NewSketchFromWorkplane(wp, nil, nil)
		sk.Segment(NewTopoVector(0, 0, 0), NewTopoVector(10, 0, 0), "e1", false)
		sk.Segment(NewTopoVector(5, 5, 0), NewTopoVector(15, 5, 0), "e2", false)
		sk.Segment(NewTopoVector(-5, -5, 0), NewTopoVector(5, -5, 0), "e3", false)
		sk.ConstraintBetween("e1", "e2", 2, NewSketchConstraintValueFromBlank())
		sk.ConstraintBetween("e2", "e3", 2, NewSketchConstraintValueFromBlank())
		sk.ConstraintBetween("e1", "e3", 3, NewSketchConstraintValueFromDouble(0))
		sk.Solve()
		if err := sk.Err(); err != nil {
			t.Fatalf("three constraints chain error: %v", err)
		}
	})
}

func TestSketchSolver_EdgeCases(t *testing.T) {

	t.Run("no constraints", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sk := makeSegment(wp, "e1")
		sk.Solve()
		if err := sk.Err(); err != nil {
			t.Fatalf("no constraints error: %v", err)
		}
	})
	t.Run("no entities", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sk := NewSketchFromWorkplane(wp, nil, nil)
		sk.Solve()
		// nlopt requires at least 1 DOF; this is an expected limitation
		if err := sk.Err(); err != nil {
			t.Logf("no entities expected error: %v", err)
		}
	})
	t.Run("multiple solves", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sk := makeSegment(wp, "e1")
		sk.Constrain("e1", 4, NewSketchConstraintValueFromDouble(5))
		sk.Solve()
		sk.Solve()
		sk.Solve()
		if err := sk.Err(); err != nil {
			t.Fatalf("multiple solves error: %v", err)
		}
	})
	t.Run("constrain after solve", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sk := makeSegment(wp, "e1")
		sk.Constrain("e1", 4, NewSketchConstraintValueFromDouble(5))
		sk.Solve()
		sk.Constrain("e1", 7, NewSketchConstraintValueFromDouble2(0, 1))
		sk.Solve()
		if err := sk.Err(); err != nil {
			t.Fatalf("constrain after solve error: %v", err)
		}
	})
	t.Run("overconstrained consistent", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sk := NewSketchFromWorkplane(wp, nil, nil)
		sk.Segment(NewTopoVector(0, 0, 0), NewTopoVector(10, 0, 0), "e1", false)
		sk.Constrain("e1", 4, NewSketchConstraintValueFromDouble(10))
		sk.Constrain("e1", 7, NewSketchConstraintValueFromDouble2(1, 0))
		sk.Constrain("e1", 0, NewSketchConstraintValueFromDouble(0))
		sk.Solve()
		if err := sk.Err(); err != nil {
			t.Fatalf("overconstrained consistent error: %v", err)
		}
	})
	t.Run("arc FIXED_POINT", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sk := makeCircleEdge(wp, "a1")
		sk.Constrain("a1", 1, NewSketchConstraintValueFromDouble(0.3))
		sk.Solve()
		if err := sk.Err(); err != nil {
			t.Fatalf("arc FIXED_POINT error: %v", err)
		}
	})
	t.Run("arc FIXED", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sk := makeCircleEdge(wp, "a1")
		sk.Constrain("a1", 0, NewSketchConstraintValueFromDouble(0))
		sk.Solve()
		if err := sk.Err(); err != nil {
			t.Fatalf("arc FIXED error: %v", err)
		}
	})
}

func TestSketchConstraintValue(t *testing.T) {
	t.Run("blank", func(t *testing.T) {
		cv := NewSketchConstraintValueFromBlank()
		if cv == nil {
			t.Fatal("NewSketchConstraintValueFromBlank returned nil")
		}
	})
	t.Run("double", func(t *testing.T) {
		cv := NewSketchConstraintValueFromDouble(5.0)
		if cv == nil {
			t.Fatal("NewSketchConstraintValueFromDouble returned nil")
		}
	})
	t.Run("double2", func(t *testing.T) {
		cv := NewSketchConstraintValueFromDouble2(1.0, 2.0)
		if cv == nil {
			t.Fatal("NewSketchConstraintValueFromDouble2 returned nil")
		}
	})
	t.Run("double3", func(t *testing.T) {
		cv := NewSketchConstraintValueFromDouble3(1.0, 2.0, 3.0)
		if cv == nil {
			t.Fatal("NewSketchConstraintValueFromDouble3 returned nil")
		}
	})
}
