package topo

import (
	"math"
	"testing"
)

func TestNewWorkplane(t *testing.T) {
	t.Run("empty", func(t *testing.T) {
		wp := NewWorkplane()
		if wp == nil {
			t.Fatal("NewWorkplane returned nil")
		}
		if err := wp.Err(); err != nil {
			t.Fatalf("unexpected error: %v", err)
		}
	})

	t.Run("named XY", func(t *testing.T) {
		origin := NewTopoVector(0, 0, 0)
		wp := NewWorkplaneFromName("XY", origin)
		if wp == nil {
			t.Fatal("NewWorkplaneFromName returned nil")
		}
		if err := wp.Err(); err != nil {
			t.Fatalf("unexpected error: %v", err)
		}
	})

	t.Run("named YZ", func(t *testing.T) {
		origin := NewTopoVector(0, 0, 0)
		wp := NewWorkplaneFromName("YZ", origin)
		if wp == nil {
			t.Fatal("NewWorkplaneFromName returned nil")
		}
	})

	t.Run("named XZ", func(t *testing.T) {
		origin := NewTopoVector(0, 0, 0)
		wp := NewWorkplaneFromName("XZ", origin)
		if wp == nil {
			t.Fatal("NewWorkplaneFromName returned nil")
		}
	})

	t.Run("from plane", func(t *testing.T) {
		originPt := NewPoint3([3]float64{0, 0, 0})
		plane := NewTopoPlaneFromNamed("XY", &originPt)
		originVec := NewTopoVector(0, 0, 0)
		wp := NewWorkplaneFromPlane(plane, originVec)
		if wp == nil {
			t.Fatal("NewWorkplaneFromPlane returned nil")
		}
	})
}

func TestBoxConvenience(t *testing.T) {
	t.Run("BoxCentered", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r := wp.BoxCentered(10, 20, 30)
		if err := r.Err(); err != nil {
			t.Fatalf("BoxCentered error: %v", err)
		}
		val := r.Value()
		if val == nil {
			t.Fatal("Value is nil after BoxCentered")
		}
	})

	t.Run("BoxCorners", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r := wp.BoxCorners(10, 20, 30)
		if err := r.Err(); err != nil {
			t.Fatalf("BoxCorners error: %v", err)
		}
	})

	t.Run("BoxFull params", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r := wp.Box(10, 20, 30, true, true, true, true, true)
		if err := r.Err(); err != nil {
			t.Fatalf("Box error: %v", err)
		}
		val := r.Value()
		if val == nil || !val.IsValid() {
			t.Fatal("Box produced invalid shape")
		}
	})
}

func TestSphereConvenience(t *testing.T) {
	t.Run("SphereCentered", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r := wp.SphereCentered(10)
		if err := r.Err(); err != nil {
			t.Fatalf("SphereCentered error: %v", err)
		}
	})

	t.Run("Sphere with params", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r := wp.Sphere(10, nil, -90, 90, 360, false, false, false, true, true)
		if err := r.Err(); err != nil {
			t.Fatalf("Sphere error: %v", err)
		}
	})
}

func TestCylinderConvenience(t *testing.T) {
	t.Run("CylinderCentered", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r := wp.CylinderCentered(20, 5)
		if err := r.Err(); err != nil {
			t.Fatalf("CylinderCentered error: %v", err)
		}
	})

	t.Run("CylinderAt", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r := wp.CylinderAt(20, 5)
		if err := r.Err(); err != nil {
			t.Fatalf("CylinderAt error: %v", err)
		}
		val := r.Value()
		if val == nil || !val.IsValid() {
			t.Fatal("CylinderAt produced invalid shape")
		}
	})
}

func TestRectCirclePolygon(t *testing.T) {
	t.Run("RectCentered", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r := wp.RectCentered(20, 10)
		if err := r.Err(); err != nil {
			t.Fatalf("RectCentered error: %v", err)
		}
	})

	t.Run("CircleCentered", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r := wp.CircleCentered(10)
		if err := r.Err(); err != nil {
			t.Fatalf("CircleCentered error: %v", err)
		}
	})

	t.Run("PolygonSimple", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r := wp.PolygonSimple(6, 10)
		if err := r.Err(); err != nil {
			t.Fatalf("PolygonSimple error: %v", err)
		}
	})
}

func TestExtrudeSimple(t *testing.T) {
	t.Run("extrude rect", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.RectCentered(10, 10)
		r2 := r1.ExtrudeSimple(20)
		if err := r2.Err(); err != nil {
			t.Fatalf("ExtrudeSimple error: %v", err)
		}
	})

	t.Run("extrude with combine=false", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.RectCentered(10, 10)
		r2 := r1.Extrude(20, false, true, false, 0)
		if err := r2.Err(); err != nil {
			t.Fatalf("Extrude error: %v", err)
		}
	})
}

func TestCutBlindSimple(t *testing.T) {
	t.Run("cut blind simple", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCorners(20, 20, 20)
		if err := r1.Err(); err != nil {
			t.Fatalf("Box error: %v", err)
		}
		r2 := r1.Faces(">Z", "")
		if err := r2.Err(); err != nil {
			t.Fatalf("Faces error: %v", err)
		}
		sub := r2.Workplane(0, false, 0, nil)
		r3 := sub.RectCentered(5, 5)
		r4 := r3.CutBlindSimple(-10)
		if err := r4.Err(); err != nil {
			t.Fatalf("CutBlindSimple error: %v", err)
		}
	})
}

func TestHoleThrough(t *testing.T) {
	t.Run("HoleThrough from top face", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCorners(20, 20, 20)
		if err := r1.Err(); err != nil {
			t.Fatalf("Box error: %v", err)
		}
		topFaces := r1.Faces(">Z", "")
		if err := topFaces.Err(); err != nil {
			t.Fatalf("Faces>Z error: %v", err)
		}
		if topFaces.Size() == 0 {
			t.Fatal("no faces selected with >Z")
		}
		sub := topFaces.Workplane(0, false, 0, nil)
		r2 := sub.HoleThrough(5)
		if err := r2.Err(); err != nil {
			t.Fatalf("HoleThrough error: %v", err)
		}
	})

	t.Run("HoleThroughWithDepth", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCorners(20, 20, 20)
		r2 := r1.Faces(">Z", "")
		sub := r2.Workplane(0, false, 0, nil)
		r3 := sub.HoleThroughWithDepth(5, 25)
		if err := r3.Err(); err != nil {
			t.Fatalf("HoleThroughWithDepth error: %v", err)
		}
	})
}

func TestWorkplaneFacesSelection(t *testing.T) {
	t.Run("select >Z face on box", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCorners(10, 10, 10)
		selected := r1.Faces(">Z", "")
		if err := selected.Err(); err != nil {
			t.Fatalf("Faces>Z error: %v", err)
		}
		if selected.Size() == 0 {
			t.Fatal("expected at least one face from >Z selector")
		}
	})

	t.Run("select <Z face on box", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCorners(10, 10, 10)
		selected := r1.Faces("<Z", "")
		if err := selected.Err(); err != nil {
			t.Fatalf("Faces<Z error: %v", err)
		}
		if selected.Size() == 0 {
			t.Fatal("expected at least one face from <Z selector")
		}
	})

	t.Run("select edges", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCorners(10, 10, 10)
		edges := r1.Edges("%line", "")
		if err := edges.Err(); err != nil {
			t.Fatalf("Edges %%line error: %v", err)
		}
	})

	t.Run("select vertices", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCorners(10, 10, 10)
		verts := r1.Vertices("", "")
		if err := verts.Err(); err != nil {
			t.Fatalf("Vertices error: %v", err)
		}
	})
}

func TestWorkplaneMirror(t *testing.T) {
	t.Run("MirrorX", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.RectCentered(10, 10)
		r2 := r1.MirrorX()
		if err := r2.Err(); err != nil {
			t.Fatalf("MirrorX error: %v", err)
		}
	})

	t.Run("MirrorY", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.RectCentered(10, 10)
		r2 := r1.MirrorY()
		if err := r2.Err(); err != nil {
			t.Fatalf("MirrorY error: %v", err)
		}
	})
}


func TestWorkplaneConstruction2D(t *testing.T) {
	t.Run("line chain and close", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r := wp.MoveTo(-5, -5).LineTo(5, -5, false).LineTo(5, 5, false).LineTo(-5, 5, false).Close()
		if err := r.Err(); err != nil {
			t.Fatalf("2D line chain error: %v", err)
		}
	})

	t.Run("slot2d", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r := wp.Slot2d(10, 4, 0)
		if err := r.Err(); err != nil {
			t.Fatalf("Slot2d error: %v", err)
		}
	})

	t.Run("three point arc", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		p1 := NewTopoVector(0, 5, 0)
		p2 := NewTopoVector(5, 0, 0)
		r := wp.MoveTo(-5, 0).ThreePointArc(p1, p2, false)
		if err := r.Err(); err != nil {
			t.Fatalf("ThreePointArc error: %v", err)
		}
	})
}

func TestWorkplaneRevolveSimple(t *testing.T) {
	t.Run("revolve rect", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.RectCentered(5, 10)
		r2 := r1.RevolveSimple(180)
		if err := r2.Err(); err != nil {
			t.Fatalf("RevolveSimple error: %v", err)
		}
	})
}

func TestWorkplaneLoftSimple(t *testing.T) {
	t.Run("loft between two rects", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.RectCentered(10, 10)
		sub := r1.Workplane(20, false, 0, nil)
		r2 := sub.RectCentered(5, 5)
		res := r2.LoftSimple()
		if err := res.Err(); err != nil {
			t.Fatalf("LoftSimple error: %v", err)
		}
	})
}

func TestWorkplaneFilletChamfer(t *testing.T) {
	t.Run("fillet on box edges", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCorners(10, 10, 10)
		// 顶面 4 条直边做圆角 (方体上没有圆边, 原 %circle 选择器匹配为空,
		// fillet 会因 "edges be selected" 报错)
		r2 := r1.Faces(">Z", "").Edges("", "")
		r3 := r2.Fillet(1)
		if err := r3.Err(); err != nil {
			t.Fatalf("Fillet error: %v", err)
		}
	})
}

func TestWorkplaneBoolean(t *testing.T) {
	t.Run("union", func(t *testing.T) {
		wp1 := NewNamedWorkplane("XY")
		r1 := wp1.BoxCentered(10, 10, 10)
		wp2 := NewNamedWorkplane("XY")
		r2 := wp2.BoxCentered(5, 5, 20)
		r3 := r1.Union(r2, true, false, 0.001)
		if err := r3.Err(); err != nil {
			t.Fatalf("Union error: %v", err)
		}
	})

	t.Run("cut", func(t *testing.T) {
		wp1 := NewNamedWorkplane("XY")
		r1 := wp1.BoxCentered(10, 10, 10)
		wp2 := NewNamedWorkplane("XY")
		r2 := wp2.CylinderCentered(20, 3)
		r3 := r1.Cut(r2, true, 0.001)
		if err := r3.Err(); err != nil {
			t.Fatalf("Cut error: %v", err)
		}
	})
}

func TestWorkplaneSection(t *testing.T) {
	t.Run("section box", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		section := r1.Section(0)
		if err := section.Err(); err != nil {
			t.Fatalf("Section error: %v", err)
		}
		val := section.Value()
		if val == nil {
			t.Fatal("Section produced nil value")
		}
	})
}

func TestWorkplaneCombine(t *testing.T) {
	t.Run("combine", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		wp2 := NewNamedWorkplane("XY")
		r2 := wp2.CylinderCentered(20, 3)
		wp.Add(r2)
		combined := r1.Combine(true, false, 0.001)
		if err := combined.Err(); err != nil {
			t.Fatalf("Combine error: %v", err)
		}
	})
}

func TestWorkplaneConsolidateWires(t *testing.T) {
	t.Run("consolidate wires", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r := wp.MoveTo(-5, -5).LineTo(5, -5, false).LineTo(5, 5, false).LineTo(-5, 5, false).Close()
		cons := r.ConsolidateWires()
		if err := cons.Err(); err != nil {
			t.Fatalf("ConsolidateWires error: %v", err)
		}
	})
}

func TestWorkplaneOffset2D(t *testing.T) {
	t.Run("offset2d", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.RectCentered(10, 10)
		off := r1.Offset2D(2, 0, false)
		if err := off.Err(); err != nil {
			t.Fatalf("Offset2D error: %v", err)
		}
	})
}

func TestWorkplaneLargestDimension(t *testing.T) {
	t.Run("largest dim", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 20, 30)
		dim := r1.LargestDimension()
		if dim <= 0 {
			t.Fatalf("LargestDimension is %f, expected > 0", dim)
		}
	})
}

func TestWorkplaneNilSafety(t *testing.T) {
	t.Run("NewWorkplaneFromName nil origin", func(t *testing.T) {
		wp := NewWorkplaneFromName("XY", nil)
		if wp == nil {
			t.Fatal("expected non-nil workplane")
		}
	})

	t.Run("NewWorkplaneFromPlane nil origin", func(t *testing.T) {
		originPt := NewPoint3([3]float64{0, 0, 0})
		plane := NewTopoPlaneFromNamed("XY", &originPt)
		wp := NewWorkplaneFromPlane(plane, nil)
		if wp == nil {
			t.Fatal("expected non-nil workplane")
		}
	})

	t.Run("Workplane nil origin", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sub := wp.Workplane(0, false, 0, nil)
		if sub == nil {
			t.Fatal("expected non-nil sub-workplane")
		}
	})

	t.Run("Sphere nil direct", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r := wp.Sphere(10, nil, -90, 90, 360, false, false, false, true, true)
		if err := r.Err(); err != nil {
			t.Fatalf("Sphere with nil direct error: %v", err)
		}
	})

	t.Run("Cylinder nil direct", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r := wp.Cylinder(20, 5, nil, 360, false, false, false, true, true)
		if err := r.Err(); err != nil {
			t.Fatalf("Cylinder with nil direct error: %v", err)
		}
	})
}

func TestWorkplaneHoleNilDepth(t *testing.T) {
	t.Run("Hole nil depth = through", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCorners(20, 20, 20)
		r2 := r1.Faces(">Z", "")
		sub := r2.Workplane(0, false, 0, nil)
		r3 := sub.HoleThrough(5)
		if err := r3.Err(); err != nil {
			t.Fatalf("HoleThrough error: %v", err)
		}
	})
}

func TestWorkplaneHoleWithDepth(t *testing.T) {
	t.Run("Hole with explicit depth", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCorners(20, 20, 20)
		r2 := r1.Faces(">Z", "")
		sub := r2.Workplane(0, false, 0, nil)
		r3 := sub.HoleThroughWithDepth(5, 25)
		if err := r3.Err(); err != nil {
			t.Fatalf("HoleThroughWithDepth error: %v", err)
		}
	})
}

func TestWorkplanePushPoints(t *testing.T) {
	t.Run("push points and circle", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		id := NewTrsfTranslationFromVector(NewVector3([3]float64{0, 0, 0}))
		loc1 := NewTopoLocation(id)
		loc2 := NewTopoLocation(id)
		r1 := wp.PushPoints([]*TopoLocation{loc1, loc2})
		r2 := r1.CircleCentered(3)
		if err := r2.Err(); err != nil {
			t.Fatalf("PushPoints+Circle error: %v", err)
		}
	})
}

func TestWorkplaneFirstLastItem(t *testing.T) {
	t.Run("first/last/item", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.RectCentered(10, 10)
		r2 := r1.ExtrudeSimple(10)
		first := r2.First()
		if err := first.Err(); err != nil {
			t.Fatalf("First error: %v", err)
		}
		last := r2.Last()
		if err := last.Err(); err != nil {
			t.Fatalf("Last error: %v", err)
		}
		item := r2.Item(0)
		if err := item.Err(); err != nil {
			t.Fatalf("Item error: %v", err)
		}
	})
}

func TestWorkplaneShapesVals(t *testing.T) {
	t.Run("Shapes after box", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		shapes := r1.Shapes()
		if len(shapes) == 0 {
			t.Fatal("expected at least one shape after BoxCentered")
		}
	})

	t.Run("Vals after box", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		vals := r1.Vals()
		if len(vals) == 0 {
			t.Fatal("expected at least one val after BoxCentered")
		}
	})

	t.Run("Size", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		_ = wp.BoxCentered(10, 10, 10)
		s := wp.Size()
		if s < 0 {
			t.Fatalf("negative Size: %d", s)
		}
	})
}

func TestWorkplaneEnd(t *testing.T) {
	t.Run("End from Workplane", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.CircleCentered(5)
		parent := r1.End(0)
		if err := parent.Err(); err != nil {
			t.Fatalf("End error: %v", err)
		}
	})
}

func TestWorkplaneClean(t *testing.T) {
	t.Run("Clean", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		cleaned := r1.Clean()
		if err := cleaned.Err(); err != nil {
			t.Fatalf("Clean error: %v", err)
		}
	})
}

func TestWorkplanePolarArray(t *testing.T) {
	t.Run("PolarArray", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r := wp.PolarArray(10, 0, 360, 6, true, false)
		if err := r.Err(); err != nil {
			t.Fatalf("PolarArray error: %v", err)
		}
	})
}

func TestWorkplaneCenter(t *testing.T) {
	t.Run("Center", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.Center(5, 10)
		r2 := r1.CircleCentered(3)
		if err := r2.Err(); err != nil {
			t.Fatalf("Center+Circle error: %v", err)
		}
	})
}

func TestWorkplaneMove(t *testing.T) {
	t.Run("MoveTo and LineTo chain", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r := wp.MoveTo(0, 0).LineTo(10, 0, false).LineTo(10, 10, false).LineTo(0, 10, false)
		if err := r.Err(); err != nil {
			t.Fatalf("MoveTo/LineTo error: %v", err)
		}
	})
}

func TestWorkplaneTwistExtrude(t *testing.T) {
	t.Run("TwistExtrude", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.CircleCentered(5)
		r2 := r1.TwistExtrude(20, 45, true, true)
		if err := r2.Err(); err != nil {
			t.Fatalf("TwistExtrude error: %v", err)
		}
	})
}

func TestWorkplaneVLineHLine(t *testing.T) {
	t.Run("VLine and HLine", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r := wp.MoveTo(0, 0).VLine(10, false).HLine(10, false).VLineTo(0, false).HLineTo(0, false)
		if err := r.Err(); err != nil {
			t.Fatalf("VLine/HLine error: %v", err)
		}
	})
}

func TestWorkplaneSpline(t *testing.T) {
	t.Run("Spline", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		pts := []*TopoVector{
			NewTopoVector(0, 0, 0),
			NewTopoVector(10, 5, 0),
			NewTopoVector(20, 0, 0),
		}
		r := wp.Spline(pts, false, nil, false, 0.01, false, false, false)
		if err := r.Err(); err != nil {
			t.Fatalf("Spline error: %v", err)
		}
	})
}

func TestWorkplanePolygonByVertices(t *testing.T) {
	t.Run("Polyline and Close", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		pts := []*TopoVector{
			NewTopoVector(0, 0, 0),
			NewTopoVector(10, 0, 0),
			NewTopoVector(10, 10, 0),
			NewTopoVector(0, 10, 0),
		}
		r := wp.Polyline(pts, false, false).Close()
		if err := r.Err(); err != nil {
			t.Fatalf("Polyline+Close error: %v", err)
		}
	})
}

func TestWorkplaneRarray(t *testing.T) {
	t.Run("Rarray", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r := wp.Rarray(10, 10, 3, 2, false, false)
		if err := r.Err(); err != nil {
			t.Fatalf("Rarray error: %v", err)
		}
	})
}

func TestWorkplaneGetSet(t *testing.T) {
	t.Run("Get/GetRange/GetIndices", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		g := r1.Get(0)
		if err := g.Err(); err != nil {
			t.Fatalf("Get error: %v", err)
		}
		gr := r1.GetRange(0, 1)
		if err := gr.Err(); err != nil {
			t.Fatalf("GetRange error: %v", err)
		}
		gi := r1.GetIndices([]int{0})
		if err := gi.Err(); err != nil {
			t.Fatalf("GetIndices error: %v", err)
		}
	})
}

func TestWorkplaneOCCVecMath(t *testing.T) {
	t.Run("NewTopoVector", func(t *testing.T) {
		v := NewTopoVector(1, 2, 3)
		if v == nil {
			t.Fatal("NewTopoVector returned nil")
		}
		if math.Abs(v.X()-1) > 1e-10 || math.Abs(v.Y()-2) > 1e-10 || math.Abs(v.Z()-3) > 1e-10 {
			t.Fatal("unexpected vector values")
		}
	})
}

func TestWorkplaneLocation(t *testing.T) {
	t.Run("NewTopoLocation", func(t *testing.T) {
		id := NewTrsfTranslationFromVector(NewVector3([3]float64{0, 0, 0}))
		loc := NewTopoLocation(id)
		if loc == nil {
			t.Fatal("NewTopoLocation returned nil")
		}
	})
}

func TestWorkplaneSketchBridge(t *testing.T) {
	t.Run("Sketch from workplane", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		sk := wp.Sketch()
		if sk == nil {
			t.Fatal("Sketch() returned nil")
		}
	})
}

func TestWorkplaneTag(t *testing.T) {
	t.Run("Tag", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		wp.Tag("base")
		if err := wp.Err(); err != nil {
			t.Fatalf("Tag error: %v", err)
		}
	})
}

func TestWorkplaneExport(t *testing.T) {
	t.Run("ExportTo step", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		r1.ExportTo("/tmp/test_go_topo_export.step")
	})
}

func TestWorkplaneHasParent(t *testing.T) {
	t.Run("HasParent", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		if wp.HasParent() {
			t.Fatal("root workplane should not have parent")
		}
	})
}

func TestWorkplaneSectionHeight(t *testing.T) {
	t.Run("Section with height", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		sec := r1.Section(2)
		if err := sec.Err(); err != nil {
			t.Fatalf("Section error: %v", err)
		}
	})
}

func TestWorkplanePolarLine(t *testing.T) {
	t.Run("PolarLine", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r := wp.MoveTo(0, 0).PolarLine(10, 45, false)
		if err := r.Err(); err != nil {
			t.Fatalf("PolarLine error: %v", err)
		}
	})
	t.Run("PolarLineTo", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r := wp.MoveTo(0, 0).PolarLineTo(10, 45, false)
		if err := r.Err(); err != nil {
			t.Fatalf("PolarLineTo error: %v", err)
		}
	})
}

func TestWorkplaneBezier(t *testing.T) {
	t.Run("Bezier", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		pts := []*TopoVector{
			NewTopoVector(0, 0, 0), NewTopoVector(5, 10, 0), NewTopoVector(10, 0, 0),
		}
		r := wp.Bezier(pts, false, false, false)
		if err := r.Err(); err != nil {
			t.Fatalf("Bezier error: %v", err)
		}
	})
}

func TestWorkplaneEllipse(t *testing.T) {
	t.Run("EllipseCentered", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r := wp.EllipseCentered(10, 5, 0)
		if err := r.Err(); err != nil {
			t.Fatalf("EllipseCentered error: %v", err)
		}
	})
	t.Run("EllipseArc", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r := wp.EllipseArc(10, 5, 0, 180, 0, 1, false, false, false)
		if err := r.Err(); err != nil {
			t.Fatalf("EllipseArc error: %v", err)
		}
	})
}

func TestWorkplaneSplineApprox(t *testing.T) {
	t.Run("SplineApprox", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		pts := []*TopoVector{NewTopoVector(0, 0, 0), NewTopoVector(10, 5, 0), NewTopoVector(20, 0, 0)}
		r := wp.SplineApprox(pts, 0.01, 1, 3, nil, false, false, false)
		if err := r.Err(); err != nil {
			t.Fatalf("SplineApprox error: %v", err)
		}
	})
}

func TestWorkplaneSagittaArc(t *testing.T) {
	t.Run("SagittaArc", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		ep := NewTopoVector(10, 0, 0)
		r := wp.MoveTo(0, 0).SagittaArc(ep, 5, false)
		if err := r.Err(); err != nil {
			t.Fatalf("SagittaArc error: %v", err)
		}
	})
	t.Run("RadiusArc", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		ep := NewTopoVector(10, 0, 0)
		r := wp.MoveTo(0, 0).RadiusArc(ep, 10, false)
		if err := r.Err(); err != nil {
			t.Fatalf("RadiusArc error: %v", err)
		}
	})
	t.Run("TangentArcPoint", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		ep := NewTopoVector(10, 10, 0)
		r := wp.MoveTo(0, 0).LineTo(10, 0, false).TangentArcPoint(ep, false, false)
		if err := r.Err(); err != nil {
			t.Fatalf("TangentArcPoint error: %v", err)
		}
	})
}

func TestWorkplaneShellSolidsCompounds(t *testing.T) {
	t.Run("Shells with selector", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCorners(10, 10, 10)
		r2 := r1.Shells("", "")
		if err := r2.Err(); err != nil {
			t.Fatalf("Shells error: %v", err)
		}
	})
	t.Run("Solids with selector", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCorners(10, 10, 10)
		r2 := r1.Solids("", "")
		if err := r2.Err(); err != nil {
			t.Fatalf("Solids error: %v", err)
		}
	})
}

func TestWorkplaneWiresSelection(t *testing.T) {
	t.Run("Wires", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r := wp.RectCentered(10, 10)
		w := r.Wires("", "")
		if err := w.Err(); err != nil {
			t.Fatalf("Wires error: %v", err)
		}
	})
}

func TestWorkplaneCompoundsSelection(t *testing.T) {
	t.Run("Compounds", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r := wp.BoxCentered(10, 10, 10)
		c := r.Compounds("", "")
		if err := c.Err(); err != nil {
			t.Fatalf("Compounds error: %v", err)
		}
	})
}

func TestWorkplaneAddShapesOps(t *testing.T) {
	t.Run("Add and AddShape", func(t *testing.T) {
		wp1 := NewNamedWorkplane("XY")
		r1 := wp1.RectCentered(10, 10)
		wp2 := NewNamedWorkplane("XY")
		r2 := wp2.CircleCentered(5)
		wp1.Add(r2)
		shapes := wp1.Shapes()
		if len(shapes) == 0 {
			t.Fatal("expected shapes after Add")
		}
		_ = r1
	})
	t.Run("AddShapes", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		wp.AddShapes(nil)
	})
}




func TestWorkplaneWedgeTest(t *testing.T) {
	t.Run("Wedge", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r := wp.Wedge(10, 20, 15, 0, 0, 10, 15, nil, nil, false, false, false, true, true)
		if err := r.Err(); err != nil {
			t.Fatalf("Wedge error: %v", err)
		}
	})
	t.Run("Wedge centered", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r := wp.WedgeAll(10, 20, 15, 0, 0, 10, 15, nil, nil, true, true, true)
		if err := r.Err(); err != nil {
			t.Fatalf("WedgeAll error: %v", err)
		}
	})
}

func TestWorkplaneFindSolid(t *testing.T) {
	t.Run("FindSolid", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCorners(10, 10, 10)
		s := r1.FindSolid(true, true)
		if s == nil {
			t.Log("FindSolid returned nil (expected if no solid in chain)")
		}
	})
}

func TestWorkplaneAllMethod(t *testing.T) {
	t.Run("All", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.RectCentered(10, 10)
		all := r1.All()
		if len(all) == 0 {
			t.Fatal("expected at least one from All()")
		}
	})
}

func TestWorkplaneToPending(t *testing.T) {
	t.Run("ToPending", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.RectCentered(10, 10)
		r1.ToPending()
	})
}

func TestWorkplaneRadiusArc(t *testing.T) {
	t.Run("RadiusArc", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		ep := NewTopoVector(10, 0, 0)
		r := wp.MoveTo(0, 0).RadiusArc(ep, 10, false)
		if err := r.Err(); err != nil {
			t.Fatalf("RadiusArc error: %v", err)
		}
	})
}


func TestWorkplaneLine(t *testing.T) {
	t.Run("Line", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r := wp.MoveTo(0, 0).Line(10, 5, false)
		if err := r.Err(); err != nil {
			t.Fatalf("Line error: %v", err)
		}
	})
}
