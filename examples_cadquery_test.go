package topo

import (
	"math"
	"testing"
)

func Test_example_rectangularPlate(t *testing.T) {
	wp := NewWorkplane()
	r := wp.BoxCentered(2.0, 2.0, 0.5)
	r.ExportTo("example_01_rectangular_plate.step")
}

func Test_example_plateWithHole(t *testing.T) {
	const length, height, thickness, centerHoleDia = 80.0, 60.0, 10.0, 22.0
	wp := NewWorkplane()
	r := wp.BoxCentered(length, height, thickness)
	r = r.Faces(">Z", "").Workplane(0, false, 0, nil).HoleThrough(centerHoleDia)
	r.ExportTo("example_02_plate_with_hole.step")
}

func Test_example_extrudePrism(t *testing.T) {
	wp := NewWorkplane()
	r := wp.CircleCentered(2.0).RectCentered(0.5, 0.75).ExtrudeSimple(0.5)
	r.ExportTo("example_03_extrude_prism.step")
}

func Test_example_lineAndArc(t *testing.T) {
	wp := NewWorkplane()
	r := wp.LineTo(2.0, 0, false)
	r = r.LineTo(2.0, 1.0, false)
	r = r.ThreePointArc(NewTopoVector(1.0, 1.5, 0), NewTopoVector(0.0, 1.0, 0), false)
	r = r.Close().ExtrudeSimple(0.25)
	r.ExportTo("example_04_line_and_arc.step")
}

func Test_example_moveWorkPoint(t *testing.T) {
	wp := NewWorkplane()
	r := wp.CircleCentered(3.0)
	r = r.Center(1.5, 0.0).RectCentered(0.5, 0.5)
	r = r.Center(-1.5, 1.5).CircleCentered(0.25)
	r = r.ExtrudeSimple(0.25)
	r.ExportTo("example_05_move_work_point.step")
}

func Test_example_pointList(t *testing.T) {
	wp := NewWorkplane()
	pts := []*TopoVector{
		NewTopoVector(1.5, 0, 0),
		NewTopoVector(0, 1.5, 0),
		NewTopoVector(-1.5, 0, 0),
		NewTopoVector(0, -1.5, 0),
	}
	r := wp.CircleCentered(2.0).PushPointsWithVector(pts).CircleCentered(0.25)
	r = r.ExtrudeSimple(0.125)
	r.ExportTo("example_06_point_list.step")
}

func Test_example_polygon(t *testing.T) {
	wp := NewWorkplane()
	r := wp.BoxCentered(3.0, 4.0, 0.25)
	pts := []*TopoVector{
		NewTopoVector(0, 0.75, 0),
		NewTopoVector(0, -0.75, 0),
	}
	r = r.Faces(">Z", "").Workplane(0, false, 0, nil).PushPointsWithVector(pts).PolygonSimple(6, 1.0).CutThruAll(0, true)
	r.ExportTo("example_07_polygon.step")
}

func Test_example_polyline(t *testing.T) {
	const L, H, W, thick = 100.0, 20.0, 20.0, 1.0
	pts := []*TopoVector{
		NewTopoVector(0, H/2.0, 0),
		NewTopoVector(W/2.0, H/2.0, 0),
		NewTopoVector(W/2.0, (H/2.0 - thick), 0),
		NewTopoVector(thick/2.0, (H/2.0 - thick), 0),
		NewTopoVector(thick/2.0, (thick - H/2.0), 0),
		NewTopoVector(W/2.0, (thick - H/2.0), 0),
		NewTopoVector(W/2.0, H/-2.0, 0),
		NewTopoVector(0, H/-2.0, 0),
	}
	wp := NewWorkplane()
	r := wp.Polyline(pts, false, false).MirrorY().ExtrudeSimple(L)
	r.ExportTo("example_08_polyline.step")
}

func Test_example_splineEdge(t *testing.T) {
	sPnts := []*TopoVector{
		NewTopoVector(2.75, 1.5, 0),
		NewTopoVector(2.5, 1.75, 0),
		NewTopoVector(2.0, 1.5, 0),
		NewTopoVector(1.5, 1.0, 0),
		NewTopoVector(1.0, 1.25, 0),
		NewTopoVector(0.5, 1.0, 0),
		NewTopoVector(0, 1.0, 0),
	}
	wp := NewWorkplane()
	r := wp.LineTo(3.0, 0, false).LineTo(3.0, 1.0, false)
	r = r.Spline(sPnts, false, nil, false, 0.01, false, true, false).Close()
	r = r.ExtrudeSimple(0.5)
	r.ExportTo("example_09_spline_edge.step")
}

func Test_example_mirrorGeometry2D(t *testing.T) {
	wp := NewWorkplane()
	r := wp.HLine(1.0, false)
	r = r.VLine(0.5, false).HLine(-0.25, false).VLine(-0.25, false).HLineTo(0.0, false)
	r = r.MirrorY().ExtrudeSimple(0.25)
	r.ExportTo("example_10_mirror_geometry_2d.step")
}

func Test_example_mirror3D(t *testing.T) {
	wp := NewWorkplane()
	r0 := wp.MoveTo(10, 0)
	r0 = r0.LineTo(5, 0, false)
	r0 = r0.ThreePointArc(NewTopoVector(3.9393, 0.4393, 0), NewTopoVector(3.5, 1.5, 0), false)
	r0 = r0.ThreePointArc(NewTopoVector(3.0607, 2.5607, 0), NewTopoVector(2, 3, 0), false)
	r0 = r0.LineTo(1.5, 3, false)
	r0 = r0.ThreePointArc(NewTopoVector(0.4393, 3.4393, 0), NewTopoVector(0, 4.5, 0), false)
	r0 = r0.LineTo(0, 13.5, false)
	r0 = r0.ThreePointArc(NewTopoVector(0.4393, 14.5607, 0), NewTopoVector(1.5, 15, 0), false)
	r0 = r0.LineTo(28, 15, false)
	r0 = r0.LineTo(28, 13.5, false)
	r0 = r0.LineTo(24, 13.5, false)
	r0 = r0.LineTo(24, 11.5, false)
	r0 = r0.LineTo(27, 11.5, false)
	r0 = r0.LineTo(27, 10, false)
	r0 = r0.LineTo(22, 10, false)
	r0 = r0.LineTo(22, 13.2, false)
	r0 = r0.LineTo(14.5, 13.2, false)
	r0 = r0.LineTo(14.5, 10, false)
	r0 = r0.LineTo(12.5, 10, false)
	r0 = r0.LineTo(12.5, 13.2, false)
	r0 = r0.LineTo(5.5, 13.2, false)
	r0 = r0.LineTo(5.5, 2, false)
	r0 = r0.ThreePointArc(NewTopoVector(5.793, 1.293, 0), NewTopoVector(6.5, 1, 0), false)
	r0 = r0.LineTo(10, 1, false).Close()
	result := r0.ExtrudeSimple(100)

	sh := result.Value()
	bb := sh.BBox().Data()
	cx := (bb[0] + bb[3]) / 2
	cy := (bb[1] + bb[4]) / 2
	cz := (bb[2] + bb[5]) / 2

	result = result.Translate(NewTopoVector(-cx, -cy, -cz))
	result = result.Rotate(NewTopoVector(0, 0, 0), NewTopoVector(1, 0, 0), 90)

	mirXYNeg := result.Mirror("XY", NewTopoVector(0, 0, -30))
	mirXYPos := result.Mirror("XY", NewTopoVector(0, 0, 30))
	mirZYNeg := result.Mirror("ZY", NewTopoVector(-30, 0, 0))
	mirZYPos := result.Mirror("ZY", NewTopoVector(30, 0, 0))

	result = result.Add(mirXYNeg).Add(mirXYPos).Add(mirZYNeg).Add(mirZYPos)
	result.ExportTo("example_11_mirror_3d.step")
}

func Test_example_mirrorByFace(t *testing.T) {
	wp := NewWorkplane()
	r := wp.Line(0, 1, false).Line(1, 0, false).Line(0, -0.5, false).Close().ExtrudeSimple(1)
	r = r.MirrorWithName("XY", NewTopoVector(1, 0, 0), true)
	r.ExportTo("example_12_mirror_by_face.step")
}

func Test_example_workplaneOnFace(t *testing.T) {
	wp := NewWorkplane()
	r := wp.BoxCentered(2, 3, 0.5)
	r = r.Faces(">Z", "").Workplane(0, false, 0, nil).HoleThrough(0.5)
	r.ExportTo("example_13_workplane_on_face.step")
}

func Test_example_workplaneOnVertex(t *testing.T) {
	wp := NewWorkplane()
	r := wp.BoxCentered(3, 2, 0.5)
	r = r.Faces(">Z", "").Vertices("<XY", "")
	r = r.Workplane(0, false, 1, nil).CircleCentered(1.0).CutThruAll(0, true)
	r.ExportTo("example_14_workplane_on_vertex.step")
}

func Test_example_offsetWorkplane(t *testing.T) {
	wp := NewWorkplane()
	r := wp.BoxCentered(3, 2, 0.5)
	r = r.Faces("<X", "").Workplane(0.75, false, 0, nil).CircleCentered(1.0).ExtrudeSimple(0.5)
	r.ExportTo("example_15_offset_workplane.step")
}

func Test_example_copyWorkplane(t *testing.T) {
	wp := NewWorkplane()
	r := wp.CircleCentered(1).ExtrudeSimple(10)
	wp2 := NewWorkplaneFromName("right", NewTopoVector(-5, 0, 0))
	r2 := wp2.CircleCentered(1).ExtrudeSimple(10)
	r = r.Add(r2)
	r.ExportTo("example_16_copy_workplane.step")
}

func Test_example_transformedWorkplane(t *testing.T) {
	wp := NewWorkplane()
	r := wp.BoxCentered(4.0, 4.0, 0.25)
	r = r.Faces(">Z", "").Workplane(0, false, 0, nil)
	r = r.Transform(NewTopoVector(60, 0, 0), NewTopoVector(0, -1.5, 1.0))
	r = r.RectAll(1.5, 1.5, true, true).Vertices("", "").HoleThrough(0.25)
	r.ExportTo("example_17_transformed_workplane.step")
}

func Test_example_constructionGeometry(t *testing.T) {
	wp := NewWorkplane()
	r := wp.BoxCentered(2, 2, 0.5)
	r = r.Faces(">Z", "").Workplane(0, false, 0, nil)
	r = r.RectAll(1.5, 1.5, true, true).Vertices("", "").HoleThrough(0.125)
	r.ExportTo("example_18_construction_geometry.step")
}

func Test_example_shell(t *testing.T) {
	wp := NewWorkplane()
	r1 := wp.BoxCentered(2, 2, 2).Shell(-0.1, "")
	r1.ExportTo("example_19_shell_negative.step")

	wp2 := NewWorkplane()
	r2 := wp2.BoxCentered(2, 2, 2).Shell(0.1, "")
	r2.ExportTo("example_19_shell_positive.step")

	wp3 := NewWorkplane()
	r3 := wp3.BoxCentered(2, 2, 2).Faces("+Z", "").Shell(0.1, "")
	r3.ExportTo("example_19_shell_face_removal.step")
}

func Test_example_loft(t *testing.T) {
	wp := NewWorkplane()
	r := wp.BoxCentered(4.0, 4.0, 0.25)
	r = r.Faces(">Z", "").CircleCentered(1.5)
	r = r.Workplane(3.0, false, 0, nil).RectCentered(0.75, 0.5).LoftSimple()
	r.ExportTo("example_20_loft.step")
}

func Test_example_extrudeToFace(t *testing.T) {
	wp := NewWorkplaneFromName("XY", NewTopoVector(20, 0, 0))
	r := wp.CircleCentered(2).RevolveSimple(180)
	r = r.Center(-20, 0).Workplane(0, false, 0, nil).RectCentered(20, 4).ExtrudeSimple(10)
	r.ExportTo("example_21_extrude_to_face.step")
}

func Test_example_cboreAndCskHole(t *testing.T) {
	wp := NewWorkplane()
	r := wp.BoxCentered(4, 2, 0.5)
	r = r.Faces(">Z", "").Workplane(0, false, 0, nil)
	r = r.RectAll(3.5, 1.5, true, true).Vertices("", "")
	r = r.CboreHole(0.125, 0.25, 0.125, nil, true)
	r.ExportTo("example_22_cbore_hole.step")
}

func Test_example_offset2D(t *testing.T) {
	wp := NewWorkplane()
	penta := wp.PolygonSimple(5, 10)

	original := penta.ExtrudeSimple(0.1).Translate(NewTopoVector(0, 0, 2))
	arc := wp.PolygonSimple(5, 10).Offset2D(1, 0, false).ExtrudeSimple(0.1).Translate(NewTopoVector(0, 0, 1))
	intersection := wp.PolygonSimple(5, 10).Offset2D(1, 1, false).ExtrudeSimple(0.1)

	result := original.Add(intersection).Add(arc)
	result.ExportTo("example_23_offset_2d.step")
}

func Test_example_fillet(t *testing.T) {
	wp := NewWorkplane()
	r := wp.BoxCentered(3, 3, 0.5).Edges("|Z", "").Fillet(0.125)
	r.ExportTo("example_24_fillet.step")
}

func Test_example_tag(t *testing.T) {
	wp := NewWorkplane()
	r := wp.BoxCentered(10, 10, 10).Faces(">Z", "").Workplane(0, false, 0, nil)
	r = r.Center(-3, 0).CircleCentered(1).ExtrudeSimple(3)
	r = r.Center(6, 0).CircleCentered(1).ExtrudeSimple(2)
	r.ExportTo("example_25_tag.step")
}

func Test_example_bearingHolder(t *testing.T) {
	const length, height, bearingDiam, thickness, padding = 30.0, 40.0, 22.0, 10.0, 8.0
	wp := NewWorkplane()
	r := wp.BoxCentered(length, height, thickness)
	r = r.Faces(">Z", "").Workplane(0, false, 0, nil).HoleThrough(bearingDiam)
	r = r.Faces(">Z", "").Workplane(0, false, 0, nil)
	r = r.RectAll(length-padding, height-padding, true, true).Vertices("", "")
	r = r.CboreHole(2.4, 4.4, 2.1, nil, true)
	r.ExportTo("example_26_bearing_holder.step")
}

func Test_example_split(t *testing.T) {
	wp := NewWorkplane()
	r := wp.BoxCentered(1, 1, 1)
	r = r.Faces(">Z", "").Workplane(0, false, 0, nil).CircleCentered(0.25).CutThruAll(0, true)
	r = r.Faces(">Y", "").Workplane(-0.5, false, 0, nil).Split(true, false)
	r.ExportTo("example_27_split.step")
}

func Test_example_occBottle(t *testing.T) {
	const L, wVal, thickVal = 20.0, 6.0, 3.0
	wp := NewWorkplane()
	p := wp.Center(-L/2.0, 0).VLine(wVal/2.0, false)
	p = p.ThreePointArc(NewTopoVector(L/2.0, wVal/2.0+thickVal, 0), NewTopoVector(L, wVal/2.0, 0), false)
	p = p.VLine(-wVal/2.0, false).MirrorX().ExtrudeSimple(30.0)
	p = p.Faces(">Z", "").Workplane(0, false, 1, nil).CircleCentered(3.0).ExtrudeSimple(2.0)
	r := p.Faces(">Z", "").Shell(0.3, "")
	r.ExportTo("example_28_occ_bottle.step")
}

func Test_example_enclosure(t *testing.T) {
	const (
		pOuterWidth         = 100.0
		pOuterLength        = 150.0
		pOuterHeight        = 50.0
		pThickness          = 3.0
		pSideRadius         = 10.0
		pTopAndBottomRadius = 2.0
		pScrewpostInset     = 12.0
		pScrewpostOD        = 10.0
		pScrewpostID        = 4.0
		pLipHeight          = 1.0
	)

	oshell := NewWorkplane().RectCentered(pOuterWidth, pOuterLength).ExtrudeSimple(pOuterHeight + pLipHeight)

	if pSideRadius > pTopAndBottomRadius {
		oshell = oshell.Edges("|Z", "").Fillet(pSideRadius)
		oshell = oshell.Edges("#Z", "").Fillet(pTopAndBottomRadius)
	} else {
		oshell = oshell.Edges("#Z", "").Fillet(pTopAndBottomRadius)
		oshell = oshell.Edges("|Z", "").Fillet(pSideRadius)
	}

	innerW := pOuterWidth - 2*pThickness
	innerL := pOuterLength - 2*pThickness
	innerH := pOuterHeight - 2*pThickness
	ishell := NewWorkplane().RectCentered(innerW, innerL).ExtrudeSimple(innerH + pLipHeight)
	ishell = ishell.Edges("|Z", "").Fillet(pSideRadius - pThickness)

	box := oshell.Cut(ishell, true, 0.001)

	const postW = pOuterWidth - 2*pScrewpostInset
	const postL = pOuterLength - 2*pScrewpostInset
	box = box.Faces(">Z", "").Workplane(-pThickness, false, 0, nil)
	box = box.RectAll(postW, postL, true, true).Vertices("", "")
	box = box.CircleCentered(pScrewpostOD / 2).CircleCentered(pScrewpostID / 2)
	box = box.ExtrudeSimple(-(pOuterHeight + pLipHeight - pThickness))

	box.ExportTo("example_29_enclosure.step")
}

func Test_example_legoBrick(t *testing.T) {
	const (
		lbumps     = 6
		wbumps     = 2
		pitch      = 8.0
		clearance  = 0.1
		bumpDiam   = 4.8
		bumpHeight = 1.8
		height     = 3.2
	)

	thick := (pitch - (2*clearance) - bumpDiam) / 2.0
	postDiam := pitch - thick
	totalLength := float64(lbumps)*pitch - 2.0*clearance
	totalWidth := float64(wbumps)*pitch - 2.0*clearance

	wp := NewWorkplane()
	s := wp.BoxCentered(totalLength, totalWidth, height)
	s = s.Faces("<Z", "").Shell(-thick, "")

	s = s.Faces(">Z", "").Workplane(0, false, 0, nil)
	s = s.Rarray(pitch, pitch, lbumps, wbumps, true, true).CircleCentered(bumpDiam / 2.0).ExtrudeSimple(bumpHeight)

	tmp := s.Faces("<Z", "").Workplane(0, true, 0, nil)
	if lbumps > 1 && wbumps > 1 {
		tmp = tmp.Rarray(pitch, pitch, lbumps-1, wbumps-1, true, true)
		tmp = tmp.CircleCentered(postDiam / 2.0).CircleCentered(bumpDiam / 2.0).ExtrudeSimple(height - thick)
	} else if lbumps > 1 {
		tmp = tmp.Rarray(pitch, pitch, lbumps-1, 1, true, true)
		tmp = tmp.CircleCentered(thick).ExtrudeSimple(height - thick)
	} else if wbumps > 1 {
		tmp = tmp.Rarray(pitch, pitch, 1, wbumps-1, true, true)
		tmp = tmp.CircleCentered(thick).ExtrudeSimple(height - thick)
	}
	s.ExportTo("example_30_lego_brick.step")
	_ = tmp
}

func Test_example_braille(t *testing.T) {
	const (
		dotHeight     = 0.5
		dotDiameter   = 1.3
		baseThickness = 1.5
		plateWidth    = 50.0
		plateHeight   = 30.0
	)

	wp := NewWorkplane()
	base := wp.BoxCentered(plateWidth, plateHeight, baseThickness)

	dotPositions := []*TopoVector{
		NewTopoVector(-10, 5, 0), NewTopoVector(-10, 0, 0), NewTopoVector(-10, -5, 0),
		NewTopoVector(10, 5, 0), NewTopoVector(10, 0, 0), NewTopoVector(10, -5, 0),
	}
	base = base.Faces(">Z", "").Workplane(0, false, 0, nil)
	base = base.PushPointsWithVector(dotPositions).CircleCentered(dotDiameter / 2).ExtrudeSimple(dotHeight)
	base.ExportTo("example_31_braille.step")
}

func Test_example_panelConnectors(t *testing.T) {
	const width, height, thickness = 400.0, 500.0, 2.0
	wp := NewWorkplane()
	result := wp.BoxCentered(width, height, thickness)

	hSep := 60.0
	for i := 0; i < 4; i++ {
		yOff := 210.0 - float64(i)*hSep
		result = result.Workplane(1, false, 1, nil).Center(157, yOff).CircleCentered(1.6).CutThruAll(0, true)
	}
	for i := 0; i < 4; i++ {
		yOff := -30.0 - float64(i)*hSep
		result = result.Workplane(1, false, 1, nil).Center(157, yOff).CircleCentered(1.6).CutThruAll(0, true)
	}
	for i := 0; i < 4; i++ {
		yOff := 210.0 - float64(i)*hSep
		result = result.Workplane(1, false, 1, nil).Center(25, yOff).CircleCentered(1.6).CutThruAll(0, true)
	}
	for i := 0; i < 4; i++ {
		yOff := -30.0 - float64(i)*hSep
		result = result.Workplane(1, false, 1, nil).Center(25, yOff).CircleCentered(1.6).CutThruAll(0, true)
	}
	result.ExportTo("example_32_panel_connectors.step")
}

func Test_example_cycloidalGear(t *testing.T) {
	hypocycloid := func(tVal, r1, r2 float64) (float64, float64) {
		return (r1-r2)*math.Cos(tVal) + r2*math.Cos(r1/r2*tVal-tVal),
			(r1-r2)*math.Sin(tVal) + r2*math.Sin(-(r1/r2*tVal - tVal))
	}
	epicycloid := func(tVal, r1, r2 float64) (float64, float64) {
		return (r1+r2)*math.Cos(tVal) - r2*math.Cos(r1/r2*tVal+tVal),
			(r1+r2)*math.Sin(tVal) - r2*math.Sin(r1/r2*tVal+tVal)
	}

	const r1, r2 = 6.0, 1.0
	n := 200

	pts := make([]*TopoVector, n+1)
	for i := 0; i <= n; i++ {
		tVal := float64(i) / float64(n) * 2 * math.Pi
		fl := math.Floor(tVal / (2 * math.Pi) * (r1 / r2))
		var x, y float64
		if int64(fl)%2 == 0 {
			x, y = epicycloid(tVal, r1, r2)
		} else {
			x, y = hypocycloid(tVal, r1, r2)
		}
		pts[i] = NewTopoVector(x, y, 0)
	}

	wp := NewWorkplane()
	r := wp.Polyline(pts, false, false).Close()
	r = r.TwistExtrude(15, 90, true, true)
	r = r.Faces(">Z", "").Workplane(0, false, 0, nil).CircleCentered(2).CutThruAll(0, true)
	r.ExportTo("example_33_cycloidal_gear.step")
}
