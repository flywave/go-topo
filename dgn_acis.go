package topo

// ACIS branch of the DGN SmartSolid bridge (D113–D117,
// solid-kernel-path.md): kAcisData payloads are ACIS SAT text.
//
// Rebuild paths by surface record:
//   - cone-surface (sin==0, split-band cylinders — sweptsurf): one
//     extrusion parameter-domain band per face, v domain = signed
//     projections of the boundary loop ellipses on the cone axis (the
//     two faces of a split band tile the full cylinder exactly);
//   - cone-surface (sin!=0, tapered — loftedsurf): two-section ruled
//     loft (OCCT conical surfaces are circular-only);
//   - cylinder/plane: parameter-domain patches / boundary wires;
//   - sphere/torus without boundary loops: whole closed shells;
//   - spline-surface { rotsur }: exact revolution surface over the
//     embedded base ellipse with the recorded u/v bounds (revolvedsurf);
//   - plain NURBS (nubs) blocks: skipped (SAT-3).
// Parasolid payloads (kParasolidData) never parse as SAT and stay
// metadata-only (D111).

/*
#include "geometry_c_api.h"
#cgo CFLAGS: -I  ./libs
#cgo linux CXXFLAGS: -I ./libs  -std=gnu++14
#cgo darwin,amd64 CXXFLAGS: -I ./libs  -std=gnu++14
#cgo darwin,arm64 CXXFLAGS: -I ./libs  -std=gnu++14
#cgo windows CXXFLAGS: -I ./libs  -std=gnu++14
*/
import "C"

/*
#include "topo_c_api.h"
extern topo_shape_t *toposplit_split_by_edges(topo_shape_t *S, topo_shape_t **edges, int count);
extern topo_shape_t *toposplit_trim_band(topo_shape_t *band, topo_shape_t *wire, topo_shape_t *keep, double dx, double dy, double dz);
*/
import "C"

import (
	"math"

	"github.com/flywave/go-dgn/dgn/sat"
)

// splitByEdges splits a face-like shape by edges lying on it
// (BRepFeat_SplitShape; D120). Returns nil when the split fails.
// trimBand splits a band face by a wire lying on it (projected along the
// given direction) and keeps the piece containing keepRef. Returns nil
// when the split or piece selection fails (caller falls back).
func trimBand(band *Shape, wire *Shape, keepCenter [3]float64, dir [3]float64) *Shape {

	vtx := NewVertex(keepCenter[0], keepCenter[1], keepCenter[2])
	keep := vtx.ToShape()
	result := C.toposplit_trim_band(band.inner.val, wire.inner.val,
		keep.inner.val, C.double(dir[0]), C.double(dir[1]), C.double(dir[2]))
	if result == nil {
		return nil
	}
	return NewShape(result)
}

// vertexAt builds a single-vertex shape at p (keep-point probe for the
// band trim piece selection).
func vertexAt(p sat.Vec3) *Shape {
	return NewVertex(p[0], p[1], p[2]).ToShape()
}

func splitByEdges(shp *Shape, edges []*Shape) *Shape {
	if len(edges) == 0 {
		return nil
	}
	cEdges := make([]*C.struct__topo_shape_t, len(edges))
	for i, e := range edges {
		cEdges[i] = e.inner.val
	}
	result := C.toposplit_split_by_edges(shp.inner.val, &cEdges[0], C.int(len(edges)))
	if result == nil {
		return nil
	}
	return NewShape(result)
}

// --- param constructors missing from geometry.go ---

func geomMakeEllipseOfAxis2(a Axis2, majorR, minorR float64) *GeomEllipse {
	return NewGeomEllipse(C.geom_make_ellipse_of_axis2(a.val, C.double(majorR), C.double(minorR)))
}

func geomMakeCylindricalSurfaceOfAxis2(a Axis2, r float64) *GeomCylindricalSurface {
	return NewGeomCylindricalSurface(C.geom_make_cylindrical_surface_of_axis2(a.val, C.double(r)))
}

func geomMakeConicalSurfaceOfAxis2(a Axis2, ang, r float64) *GeomConicalSurface {
	return NewGeomConicalSurface(C.geom_make_conical_surface_axis2(a.val, C.double(ang), C.double(r)))
}

func geomMakePlaneSurfaceOfAxis2(a Axis2) *GeomPlane {
	return NewGeomPlane(C.geom_make_plane(NewPlaneFromAxis2(a).val))
}

func geomMakeSurfaceOfLinearExtrusion(c *GeomCurve, dir [3]float64) *GeomSurfaceOfLinearExtrusion {
	return NewGeomSurfaceOfLinearExtrusion(C.geom_make_surface_of_linear_extrusion(c.inner.geom, NewDir3FromXYZ(dir).val))
}

func geomMakeSurfaceOfRevolution(c *GeomCurve, axis Axis1) *GeomSurfaceOfRevolution {
	return NewGeomSurfaceOfRevolution(C.geom_make_surface_of_revolution_extrusion(c.inner.geom, axis.val))
}

// --- shared helpers ---

func parseVecTopo(r sat.Rec, base int) (sat.Vec3, bool) {
	var v sat.Vec3
	for k := 0; k < 3; k++ {
		x, err := r.Float(base + k)
		if err != nil {
			return v, false
		}
		v[k] = x
	}
	return v, true
}

func mustVec(r sat.Rec, base int) sat.Vec3 {
	v, _ := parseVecTopo(r, base)
	return v
}

func mustF(r sat.Rec, i int) float64 {
	v, _ := r.Float(i)
	return v
}

func vecLenTopo(v sat.Vec3) float64 {
	return math.Sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2])
}

func normalizeTopo(v sat.Vec3) sat.Vec3 {
	l := vecLenTopo(v)
	if l == 0 {
		return v
	}
	return sat.Vec3{v[0] / l, v[1] / l, v[2] / l}
}

func vecApproxEq(a, b sat.Vec3) bool {
	for i := 0; i < 3; i++ {
		tol := 1e-9 * (1 + math.Abs(a[i]) + math.Abs(b[i]))
		if math.Abs(a[i]-b[i]) > tol {
			return false
		}
	}
	return true
}

func parallelOpposite(a, b sat.Vec3) bool {
	dot := a[0]*b[0] + a[1]*b[1] + a[2]*b[2]
	la, lb := vecLenTopo(a), vecLenTopo(b)
	if la == 0 || lb == 0 {
		return false
	}
	return math.Abs(dot/(la*lb)+1) < 1e-6
}

func faceShape(f *Face) *Shape {
	if f == nil || f.IsNull() {
		return nil
	}
	return f.ToShape()
}

func shellShape(shell *Shell) *Shape {
	sh, err := shell.ToShape()
	if err != nil || sh == nil || sh.IsNull() {
		return nil
	}
	return sh
}

// --- rebuild pipeline ---

// AcisBRepToShape rebuilds an exact B-rep compound from an ACIS SAT
// payload. Returns nil for non-SAT data (parasolid), streams without
// rebuildable faces, or faces whose surfaces fail to construct.
func AcisBRepToShape(data []byte) *Shape {
	doc, err := sat.Parse(data)
	if err != nil {
		return nil
	}
	var shapes []Shape
	for _, f := range doc.Faces() {
		sh := rebuildAcisFace(doc, f)
		if sh == nil || sh.IsNull() {
			continue
		}
		shapes = append(shapes, *sh)
	}
	if len(shapes) == 0 {
		return nil
	}
	comp := TopoCompoundMake(shapes)
	if comp == nil || comp.IsNull() {
		return nil
	}
	out := comp.ToShape()
	if out == nil || out.IsNull() {
		return nil
	}
	return out
}

func rebuildAcisFace(doc *sat.Doc, f sat.Face) *Shape {
	sr, ok := doc.Rec(f.Surface)
	if !ok {
		return nil
	}
	loops := doc.FaceEdges(f.Index)
	if sr.Type == "cone-surface" {
		// split-band conical faces (sweptsurf, sin==0): one extrusion
		// band per boundary loop over the cone axis, trimmed along the
		// shared splitting ellipse (D120).
		if sin, _ := sr.Float(15); sin == 0 {
			if sh := coneBandShape(doc, f, sr, sharedCurveOf(doc, f)); sh != nil {
				return sh
			}
		}
	}
	if len(loops) == 0 {
		// boundary-less records: sphere/torus rebuild as whole closed
		// shells; cylinder/cone/plane fall back to the SAT-1
		// parameter-domain patch (bounded rebuild needs loops).
		if sh := wholeShellFace(sr); sh != nil {
			return sh
		}
		return paramPatchFace(sr)
	}
	return trimmedFace(doc, sr, f, loops)
}

// wholeShellFace rebuilds boundary-less sphere/torus records as complete
// closed shells.
// sharedCurveOf returns the ellipse-curve record index referenced by the
// face's boundary that is ALSO referenced by another face of the document
// (the splitting curve of a split band). -1 when no curve is shared.
func sharedCurveOf(doc *sat.Doc, f sat.Face) int {
	use := map[int]int{} // curve idx → face count
	for _, ff := range doc.Faces() {
		seen := map[int]bool{}
		for _, loop := range doc.FaceEdges(ff.Index) {
			for _, e := range loop {
				if e.Curve >= 0 && !seen[e.Curve] {
					seen[e.Curve] = true
					use[e.Curve]++
				}
			}
		}
	}
	best := -1
	for _, loop := range doc.FaceEdges(f.Index) {
		for _, e := range loop {
			if e.Curve >= 0 && use[e.Curve] > 1 {
				best = e.Curve
			}
		}
	}
	return best
}

func wholeShellFace(sr sat.Rec) *Shape {
	o, ok := parseVecTopo(sr, 3)
	if !ok {
		return nil
	}
	switch sr.Type {
	case "sphere-surface":
		r1, _ := sr.Float(12)
		if r1 <= 0 {
			return nil
		}
		return shellShape(TopoMakeShellFromSpereCenterRaduis(NewPoint3([3]float64(o)), r1))
	case "torus-surface":
		r1, _ := sr.Float(12)
		r2, _ := sr.Float(13)
		if r1 <= 0 || r2 <= 0 {
			return nil
		}
		axis := NewAxis2(NewPoint3([3]float64(o)), NewDir3FromXYZ([3]float64{0, 0, 1}))
		return shellShape(TopoMakeShellFromTorusAxis2(axis, r1, r2))
	}
	return nil
}

// paramPatchFace rebuilds boundary-less circular cylinder/plane records
// as parameter-domain patches over the full U circle (SAT-1 fallback;
// cone records carry no band height without loops).
func paramPatchFace(sr sat.Rec) *Shape {
	o, ok1 := parseVecTopo(sr, 3)
	n, ok2 := parseVecTopo(sr, 6)
	if !ok1 || !ok2 {
		return nil
	}
	origin := NewPoint3([3]float64(o))
	axis := NewAxis2(origin, NewDir3FromXYZ([3]float64(n)))
	twoPi := 2 * math.Pi
	switch sr.Type {
	case "cylinder-surface":
		r1, _ := sr.Float(12)
		if r1 <= 0 {
			return nil
		}
		return faceShape(TopoMakeFaceFromCylinderParm(NewCylinderFromAxis2(axis, r1), 0, twoPi, 0, twoPi*r1))
	case "plane-surface":
		return faceShape(TopoMakeFaceFromPlaneParm(NewPlaneFromAxis2(axis), -1, 1, -1, 1))
	}
	return nil
}

// trimmedFace rebuilds a bounded face: tapered cones via two-section
// ruled loft; other surfaces via the parameter domain (when the loops
// equal the surface's full parameter rectangle — the extruded/rotated
// band case) or via boundary wires.
func trimmedFace(doc *sat.Doc, sr sat.Rec, f sat.Face, loops [][]sat.EdgeNode) *Shape {
	// tapered elliptical cone (loftedsurf): two equal translated ellipse
	// loops, taper angle sin != 0 — exact rebuild via two-section ruled
	// loft (OCCT conical surfaces are circular-only).
	if sr.Type == "cone-surface" {
		sin, _ := sr.Float(15)
		ratio, _ := sr.Float(12)
		ell := faceEllipses(doc, f)
		if sin != 0 && ratio > 0 && len(ell) == 2 &&
			parallelOpposite(ell[0].Normal, ell[1].Normal) {
			wa, wb := ellipseWire(ell[0]), ellipseWire(ell[1])
			if wa != nil && wb != nil {
				p1, p2 := wa.ToShape(), wb.ToShape()
				if p1 != nil && p2 != nil {
					lofted := Loft([]*Shape{p1, p2}, false, true, "C2", "chordal", 3, false, false, [3]float64{})
					if lofted != nil && !lofted.IsNull() {
						return lofted
					}
				}
			}
		}
	}
	surf, dom := faceGeomSurface(doc, sr, f, loops)
	if surf == nil {
		return nil
	}
	// Faces whose boundary equals the surface's full parameter rectangle
	// (extrudedsurf-class extrusions: u 0..2π seam, v = signed loop
	// projections; revolvedsurf: u periodic 0..2π, v 0..π) rebuild as an
	// exact parameter-domain face; MakeFace with a bare 3D wire yields
	// unbounded UVs (±1e100, D115) on these surfaces.
	if dom != nil {
		return faceShape(TopoMakeFaceFromSurfaceParm(surf, dom[0], dom[1], dom[2], dom[3], 1e-6))
	}
	// generic path: build boundary wires and cut a trimmed face
	wireOf := func(loop []sat.EdgeNode) *Wire {
		if len(loop) == 1 {
			return loopWire(doc, loop[0])
		}
		var edges []Edge
		for _, e := range loop {
			we := loopEdge(doc, e)
			if we != nil {
				edges = append(edges, *we)
			}
		}
		if len(edges) < 2 {
			return nil
		}
		return TopoMakeWireFromEdges(edges)
	}
	var wires []*Wire
	for _, loop := range loops {
		if w := wireOf(loop); w != nil && !w.IsNull() {
			wires = append(wires, w)
		}
	}
	if len(wires) == 0 {
		return nil
	}
	face := TopoMakeFaceFromSurfaceWire(surf, *wires[0], true)
	if face == nil || face.IsNull() {
		return nil
	}
	for _, w := range wires[1:] {
		f2 := TopoMakeFaceFromFaceWire(face, *w)
		if f2 != nil && !f2.IsNull() {
			face = f2
		}
	}
	return face.ToShape()
}

// faceGeomSurface constructs the exact underlying surface for a bounded
// face. dom != nil selects the parameter-domain face (dom = u/v bounds);
// nil falls back to boundary-wire trimming.
func faceGeomSurface(doc *sat.Doc, sr sat.Rec, f sat.Face, loops [][]sat.EdgeNode) (*GeomSurface, []float64) {
	switch sr.Type {
	case "cylinder-surface":
		o, _ := parseVecTopo(sr, 3)
		n, _ := parseVecTopo(sr, 6)
		r1, _ := sr.Float(12)
		if r1 <= 0 {
			return nil, nil
		}
		axis := NewAxis2(NewPoint3([3]float64(o)), NewDir3FromXYZ([3]float64(n)))
		return geomMakeCylindricalSurfaceOfAxis2(axis, r1).Surface(),
			[]float64{0, 2 * math.Pi, 0, 2 * math.Pi * r1}
	case "plane-surface":
		o, _ := parseVecTopo(sr, 3)
		n, _ := parseVecTopo(sr, 6)
		axis := NewAxis2(NewPoint3([3]float64(o)), NewDir3FromXYZ([3]float64(n)))
		return geomMakePlaneSurfaceOfAxis2(axis).Surface(), nil
	case "cone-surface":
		// split-band conical faces (sweptsurf/extrudedsurf, sin==0): the
		// boundary loops reference one ellipse curve each (a loop may be
		// split into two half edges sharing one curve). Base = the loop
		// ellipse whose center projects closest to the cone origin; the
		// v domain covers all loop projections (signed) — the two faces
		// of a split band then tile the full cylinder exactly.
		sin, _ := sr.Float(15)
		if sin != 0 {
			return nil, nil
		}
		o, _ := parseVecTopo(sr, 3)
		n, _ := parseVecTopo(sr, 6)
		seen := map[int]bool{}
		var curves []sat.Ellipse
		for _, loop := range loops {
			for _, e := range loop {
				if e.Curve < 0 || seen[e.Curve] {
					continue
				}
				seen[e.Curve] = true
				if rec, ok := doc.Rec(e.Curve); ok && rec.Type == "ellipse-curve" {
					curves = append(curves, sat.Ellipse{
						Index:  rec.Index,
						Origin: mustVec(rec, 3), Normal: mustVec(rec, 6),
						Major: mustVec(rec, 9), Ratio: mustF(rec, 12),
					})
				}
			}
		}
		if len(curves) == 0 {
			return nil, nil
		}
		dot := func(c sat.Vec3) float64 {
			return (c[0]-o[0])*n[0] + (c[1]-o[1])*n[1] + (c[2]-o[2])*n[2]
		}
		base := curves[0]
		hBase := dot(base.Origin)
		hMin, hMax := 0.0, 0.0
		for _, c := range curves[1:] {
			h := dot(c.Origin) - hBase
			if h < hMin {
				hMin = h
			}
			if h > hMax {
				hMax = h
			}
		}
		if hMax-hMin <= 0 {
			return nil, nil
		}
		x := normalizeTopo(base.Major)
		axis := NewAxis2FromNVX(NewPoint3([3]float64(base.Origin)),
			NewDir3FromXYZ([3]float64(base.Normal)), NewDir3FromXYZ(x))
		el := geomMakeEllipseOfAxis2(axis, base.MajorRadius(), base.MinorRadius())
		if el == nil {
			return nil, nil
		}
		s2 := geomMakeSurfaceOfLinearExtrusion(el.Curve(), [3]float64{n[0], n[1], n[2]})
		if s2 == nil {
			return nil, nil
		}
		return s2.Surface(), []float64{0, 2 * math.Pi, hMin, hMax}
	case "spline-surface":
		// rotsur: exact revolution surface over the embedded base ellipse;
		// the parameter rectangle (u 0..umax, v 0..vmax) IS the face
		// (revolvedsurf: u periodic 2π, v 0..π).
		el0, umax, vmax, ok := sat.ParseRotsurBlock(sr.Block)
		if ok && umax > 0 && vmax > 0 && el0.MajorRadius() > 0 && el0.MinorRadius() > 0 {
			axis := NewAxis1(NewPoint3([3]float64(el0.Origin)), NewDir3FromXYZ([3]float64(el0.Normal)))
			x := normalizeTopo(el0.Major)
			el := geomMakeEllipseOfAxis2(NewAxis2FromNVX(NewPoint3([3]float64(el0.Origin)),
				NewDir3FromXYZ([3]float64(el0.Normal)), NewDir3FromXYZ(x)), el0.MajorRadius(), el0.MinorRadius())
			if el != nil {
				s2 := geomMakeSurfaceOfRevolution(el.Curve(), axis)
				if s2 != nil {
					return s2.Surface(), []float64{0, umax, 0, vmax}
				}
			}
		}
		return nil, nil
	}
	return nil, nil
}

// --- boundary wire helpers ---

// faceEllipses collects the ellipse curves of face f's boundary loops.
func faceEllipses(doc *sat.Doc, f sat.Face) []sat.Ellipse {
	return loopEllipses(doc, doc.FaceEdges(f.Index))
}

// loopWire builds the wire of a closed single-edge loop (full ellipse).
func loopWire(doc *sat.Doc, e sat.EdgeNode) *Wire {
	if e.Curve < 0 || e.StartVertex < 0 || e.StartVertex != e.EndVertex {
		return nil
	}
	rec, ok := doc.Rec(e.Curve)
	if !ok || rec.Type != "ellipse-curve" {
		return nil
	}
	return ellipseWire(sat.Ellipse{
		Index: rec.Index, Origin: mustVec(rec, 3), Normal: mustVec(rec, 6),
		Major: mustVec(rec, 9), Ratio: mustF(rec, 12),
	})
}

// loopEdge builds a parameter-trimmed edge for multi-edge loops.
func loopEdge(doc *sat.Doc, e sat.EdgeNode) *Edge {
	if e.Curve < 0 || e.StartVertex < 0 || e.EndVertex < 0 {
		return nil
	}
	rec, ok := doc.Rec(e.Curve)
	if !ok || rec.Type != "ellipse-curve" {
		return nil
	}
	el := sat.Ellipse{
		Index: rec.Index, Origin: mustVec(rec, 3), Normal: mustVec(rec, 6),
		Major: mustVec(rec, 9), Ratio: mustF(rec, 12),
	}
	x := normalizeTopo(el.Major)
	axis := NewAxis2FromNVX(NewPoint3([3]float64(el.Origin)),
		NewDir3FromXYZ([3]float64(el.Normal)), NewDir3FromXYZ(x))
	g := geomMakeEllipseOfAxis2(axis, el.MajorRadius(), el.MinorRadius())
	if g == nil {
		return nil
	}
	return TopoMakeEdgeFromCurveParm(*g.Curve(), e.StartP, e.EndP)
}

// ellipseWire builds a closed wire from an ellipse curve record.
func ellipseWire(e sat.Ellipse) *Wire {
	if e.Ratio <= 0 || e.MajorRadius() <= 0 {
		return nil
	}
	x := normalizeTopo(e.Major)
	axis := NewAxis2FromNVX(NewPoint3([3]float64(e.Origin)),
		NewDir3FromXYZ([3]float64(e.Normal)), NewDir3FromXYZ(x))
	el := geomMakeEllipseOfAxis2(axis, e.MajorRadius(), e.MinorRadius())
	if el == nil {
		return nil
	}
	edge := TopoMakeEdgeFromCurve(*el.Curve())
	if edge == nil || edge.IsNull() {
		return nil
	}
	return TopoMakeWireFromEdge(*edge)
}

// coneBandShape rebuilds a split-band conical face (sweptsurf, sin==0):
// the two boundary loops are the face's own end ellipse and the shared
// splitting ellipse (referenced by both faces of the split band — D117
// full-text census). The band rebuilds as an exact parameter-domain face
// over the END ellipse, v = signed projections of both loops, then is cut
// by the splitting wire (BRepFeat_SplitShape, D120); the piece containing
// the end-ellipse center is the real band — exact at the splitting edge
// instead of the parameter-rectangle approximation.
func coneBandShape(doc *sat.Doc, f sat.Face, sr sat.Rec, sharedCurve int) *Shape {
	sin, _ := sr.Float(15)
	if sin != 0 {
		return nil
	}
	ell := faceEllipses(doc, f)
	if len(ell) != 2 {
		return nil
	}
	o, ok1 := parseVecTopo(sr, 3)
	n, ok2 := parseVecTopo(sr, 6)
	if !ok1 || !ok2 {
		return nil
	}
	dot := func(c sat.Vec3) float64 {
		return (c[0]-o[0])*n[0] + (c[1]-o[1])*n[1] + (c[2]-o[2])*n[2]
	}
	// classify: end ellipse (exclusive to this face) vs shared splitting
	// ellipse (sharedCurve, referenced by both faces). No shared curve →
	// no interior cut position — the caller's rectangle path is exact.
	if sharedCurve < 0 {
		return nil
	}
	var end, split int
	if ell[0].Index == sharedCurve {
		end, split = ell[1].Index, ell[0].Index
	} else {
		end, split = ell[0].Index, ell[1].Index
	}
	byIdx := map[int]sat.Ellipse{}
	for _, e := range ell {
		byIdx[e.Index] = e
	}
	endEl, okE := byIdx[end]
	splitEl, okS := byIdx[split]
	if !okE || !okS {
		return nil
	}
	hEnd, hSplit := dot(endEl.Origin), dot(splitEl.Origin)
	span := math.Abs(hEnd - hSplit)
	if span <= 0 {
		return nil
	}
	// band face over the END ellipse, v = [-overshoot, span] (stretches
	// past the splitting edge; the far side is trimmed by the split)
	x := normalizeTopo(endEl.Major)
	axis := NewAxis2FromNVX(NewPoint3([3]float64(endEl.Origin)),
		NewDir3FromXYZ([3]float64(endEl.Normal)), NewDir3FromXYZ(x))
	el := geomMakeEllipseOfAxis2(axis, endEl.MajorRadius(), endEl.MinorRadius())
	if el == nil {
		return nil
	}
	s2 := geomMakeSurfaceOfLinearExtrusion(el.Curve(), [3]float64{n[0], n[1], n[2]})
	if s2 == nil {
		return nil
	}
	overshoot := 0.3 * span
	full := faceShape(TopoMakeFaceFromSurfaceParm(s2.Surface(), 0, 2*math.Pi, -overshoot, span, 1e-6))
	if full == nil || full.IsNull() {
		return nil
	}
	// cut by the splitting ellipse wire; keep the piece containing the
	// end-ellipse center (the real band between end and splitting edge)
	sw := ellipseWire(splitEl)
	if sw == nil || sw.IsNull() {
		return full
	}
	// cut by the splitting ellipse wire: project it along the cone axis
	// onto the band (D120 SplitShape + BRepProj path) and keep the piece
	// containing the end-ellipse center — the band then matches the real
	// boundary exactly along the splitting curve.
	if trimmed := trimBand(full, sw.ToShape(), [3]float64(splitEl.Origin),
		[3]float64{n[0], n[1], n[2]}); trimmed != nil && !trimmed.IsNull() {
		return trimmed
	}
	return full
}

// loopEllipses collects the ellipse curves referenced by boundary loops.
func loopEllipses(doc *sat.Doc, loops [][]sat.EdgeNode) []sat.Ellipse {
	var out []sat.Ellipse
	for _, loop := range loops {
		for _, e := range loop {
			if e.Curve < 0 {
				continue
			}
			if rec, ok := doc.Rec(e.Curve); ok && rec.Type == "ellipse-curve" {
				out = append(out, sat.Ellipse{
					Index:  rec.Index,
					Origin: mustVec(rec, 3), Normal: mustVec(rec, 6),
					Major: mustVec(rec, 9), Ratio: mustF(rec, 12),
				})
			}
		}
	}
	return out
}
