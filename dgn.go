package topo

// DGN bridge: pure-Go parsing via github.com/flywave/go-dgn, converted to
// topo Wire/Edge primitives (cgo). Mirrors the IFC converter pattern
// (ifc.go): a reader object loads a file and hands out elements with
// topology + metadata. Design: go-dgn analysis/05-go-design/topo-bridge.md.
//
// Coordinate contract:
//   - v7 files: TCB master-unit mapping applied (SceneV7AtMaster)
//   - v8 files: master units via the document resolution
//     (SceneV8ModelAtMaster); SetUnits is no longer needed
//   - Transform is a column-major 4×4 for cell placements (nil otherwise)

import (
	"fmt"
	"math"
	"os"

	godgn "github.com/flywave/go-dgn/dgn"
	"github.com/flywave/go-dgn/dgn/scene"
)

// DgnElement is one geometry-bearing DGN element. Wire carries curve
// geometry; Shape carries face/solid geometry (KindCone frustum, KindSolid
// mesh face sets). Metadata-only kinds (text, cell defs, complex headers)
// have neither.
type DgnElement struct {
	Wire      *Wire
	Shape     *Shape
	Id        int
	ParentId  int
	Name      string
	Type      string // scene.Kind name
	Level     int
	Color     int
	Transform *[16]float64
	// BRep is non-nil for SmartSolid/SmartSurface entities (v8 type-2
	// cell header + 0x522E kernel BRep linkage): metadata-only solids —
	// the geometry stays native parasolid/ACIS, which no OCCT path
	// consumes, so Wire/Shape are nil.
	BRep *scene.BRep
	// DefID is the definition element a v8 shared-cell reference
	// instances (D112); 0 when the reference resolves by name only.
	DefID uint64
}

// DgnReader loads a DGN file (v7 or v8) and converts it to topo elements.
type DgnReader struct {
	ents     []scene.Entity
	units    float64 // uorPerMaster for v8; 0 = raw UOR
	elements []*DgnElement
}

func NewDgnReader() *DgnReader { return &DgnReader{} }

// SetUnits sets the v8 UOR-per-master scale. Call before Load.
func (r *DgnReader) SetUnits(uorPerMaster float64) { r.units = uorPerMaster }

// Load parses the DGN file at path (v7 or v8 auto-detected).
func (r *DgnReader) Load(path string) error {
	b, err := os.ReadFile(path)
	if err != nil {
		return err
	}
	return r.LoadBytes(b)
}

// LoadBytes parses an in-memory DGN file.
func (r *DgnReader) LoadBytes(b []byte) error {
	r.elements = nil
	r.ents = nil
	switch godgn.Detect(b) {
	case godgn.KindV7:
		doc, err := godgn.ParseV7Document(b)
		if err != nil {
			return fmt.Errorf("dgn: v7: %w", err)
		}
		r.ents = godgn.SceneV7AtMaster(doc)
	case godgn.KindV8:
		f, err := godgn.OpenBytes(b)
		if err != nil {
			return fmt.Errorf("dgn: v8: %w", err)
		}
		doc, err := f.V8()
		if err != nil {
			return fmt.Errorf("dgn: v8: %w", err)
		}
		// Per-model scene with UOR→master scaling applied by go-dgn
		// (D104). The old ElementChunks path missed model-nested graphics
		// chunks ("#NNNNNN/Dgn^G/$1") entirely.
		var all []scene.Entity
		for _, m := range doc.Models {
			ents, err := godgn.SceneV8ModelAtMaster(doc, m)
			if err != nil {
				continue
			}
			all = append(all, ents...)
		}
		r.ents = all
	default:
		return fmt.Errorf("dgn: unrecognized format")
	}
	r.build()
	return nil
}

// GetElements returns the converted elements (valid after Load).
func (r *DgnReader) GetElements() []*DgnElement { return r.elements }

func (r *DgnReader) build() {
	r.elements = make([]*DgnElement, 0, len(r.ents))
	for i := range r.ents {
		e := &r.ents[i]
		de := &DgnElement{
			Id:        int(e.ID),
			ParentId:  int(e.ParentID),
			Name:      e.Name,
			Type:      e.Kind.String(),
			Level:     e.Level,
			Color:     int(e.Color),
			Transform: e.Transform,
		}
		if w := r.wireFor(e); w != nil {
			de.Wire = w
		}
		if s := r.shapeFor(e); s != nil {
			de.Shape = s
		}
		de.BRep = e.BRep
		if de.BRep != nil && de.Shape == nil {
			// SmartSolid (v8 0x522E): rebuild the exact B-rep from the
			// ACIS SAT payload (D114). Parasolid payloads stay
			// metadata-only (no Go consumer path).
			de.Shape = AcisBRepToShape(de.BRep.Data)
		}
		de.DefID = e.DefID
		r.elements = append(r.elements, de)
	}
}

// scalePoint applies the optional v8 UOR scale to a scene point.
func (r *DgnReader) scalePoint(p scene.Point) [3]float64 {
	if r.units > 0 {
		return [3]float64{p.X / r.units, p.Y / r.units, p.Z / r.units}
	}
	return [3]float64{p.X, p.Y, p.Z}
}

func (r *DgnReader) wireFor(e *scene.Entity) *Wire {
	switch e.Kind {
	case scene.KindSegment:
		if len(e.Points) < 2 {
			return nil
		}
		p1 := NewPoint3(r.scalePoint(e.Points[0]))
		p2 := NewPoint3(r.scalePoint(e.Points[1]))
		return TopoMakeWireFromEdge(*TopoMakeEdgeFromTwoPoint(p1, p2))
	case scene.KindPolyline:
		if len(e.Points) < 2 {
			return nil
		}
		edges := make([]Edge, 0, len(e.Points)-1)
		for i := 0; i+1 < len(e.Points); i++ {
			p1 := NewPoint3(r.scalePoint(e.Points[i]))
			p2 := NewPoint3(r.scalePoint(e.Points[i+1]))
			edges = append(edges, *TopoMakeEdgeFromTwoPoint(p1, p2))
		}
		return TopoMakeWireFromEdges(edges)
	case scene.KindArc:
		return r.arcWire(e, false)
	case scene.KindEllipse:
		return r.arcWire(e, true)
	case scene.KindBSplineCurve:
		return r.bsplineWire(e)
	}
	return nil // text / celldef / cellref / complexheader: metadata only
}

// bsplineWire builds an exact OCCT B-spline edge from the assembled poles
// and full expanded knot vector (v7 type 27; scene.KindBSplineCurve).
// Knot multiplicities are recovered from the expanded vector; rational
// curves (weights present) go through the weighted constructor.
func (r *DgnReader) bsplineWire(e *scene.Entity) *Wire {
	if len(e.Points) < 2 || len(e.Knots) == 0 || e.Degree < 1 {
		return nil
	}
	poles := make([]Point3, len(e.Points))
	for i, p := range e.Points {
		poles[i] = NewPoint3(r.scalePoint(p))
	}
	uniq, mults := knotsToMults(e.Knots)
	var g *GeomBSplineCurve
	if len(e.Weights) == len(poles) {
		g = GeomMakeBSplineCurveFromWeight(poles, e.Weights, uniq, mults, e.Degree, false)
	} else {
		g = GeomMakeBSplineCurve(poles, uniq, mults, e.Degree, false)
	}
	if g == nil {
		return nil
	}
	c := g.Curve()
	if c == nil {
		return nil
	}
	edge := TopoMakeEdgeFromCurve(*c)
	if edge == nil || edge.IsNull() {
		return nil
	}
	return TopoMakeWireFromEdge(*edge)
}

// knotsToMults compresses an expanded knot vector into OCCT's
// (unique knots, multiplicities) form.
func knotsToMults(knots []float64) ([]float64, []int) {
	uniq := []float64{knots[0]}
	mults := []int{1}
	for _, k := range knots[1:] {
		if k == uniq[len(uniq)-1] {
			mults[len(mults)-1]++
			continue
		}
		uniq = append(uniq, k)
		mults = append(mults, 1)
	}
	return uniq, mults
}

// arcWire builds a wire for an arc/ellipse. Full circles/ellipses use the
// native circle/ellipse edges; partial arcs use a three-point arc through
// start/mid/end computed from center+radii+angles+rotation.
func (r *DgnReader) arcWire(e *scene.Entity, ellipse bool) *Wire {
	if e.Arc == nil {
		return nil
	}
	a := e.Arc
	c := r.scalePoint(a.Center)
	center := NewPoint3(c)
	rMajor := a.PrimaryAxis
	rMinor := a.SecondaryAxis
	if r.units > 0 {
		rMajor /= r.units
		rMinor /= r.units
	}

	startRad := a.Start * math.Pi / 180
	sweepRad := a.Sweep * math.Pi / 180

	if ellipse {
		rot := a.Rotation * math.Pi / 180
		normal := NewVector3([3]float64{0, 0, 1})
		xnormal := NewVector3([3]float64{math.Cos(rot), math.Sin(rot), 0})
		if a.Quat != [4]float64{} {
			normal, xnormal = quatBasis(a.Quat)
		}
		edge := TopoMakeEllipse(rMajor, rMinor, center, normal, xnormal,
			startRad, startRad+sweepRad, 1)
		return TopoMakeWireFromEdge(*edge)
	}

	if math.Abs(sweepRad) >= 2*math.Pi-1e-9 {
		// full circle
		normal := NewVector3([3]float64{0, 0, 1})
		if a.Quat != [4]float64{} {
			n, _ := quatBasis(a.Quat)
			normal = n
		}
		edge := TopoMakeCircle(rMajor, center, normal, 0, 2*math.Pi, true)
		return TopoMakeWireFromEdge(*edge)
	}

	// three-point arc: start, mid, end in the arc plane
	mid := startRad + sweepRad/2
	p1 := NewPoint3(arcPoint(a, c, rMajor, startRad))
	p2 := NewPoint3(arcPoint(a, c, rMajor, mid))
	p3 := NewPoint3(arcPoint(a, c, rMajor, startRad+sweepRad))
	return TopoMakeWireFromEdge(*TopoMakeThreePointArc(p1, p2, p3))
}

// arcPoint maps an angle on the arc plane to a world point: rotate the
// (r·cosθ, r·sinθ, 0) local vector by the arc's rotation (2D) or
// quaternion (3D), then translate by center.
func arcPoint(a *scene.Arc, c [3]float64, r, theta float64) [3]float64 {
	v := [3]float64{r * math.Cos(theta), r * math.Sin(theta), 0}
	if a.Quat != [4]float64{} {
		v = quatRotate(a.Quat, v)
	} else if a.Rotation != 0 {
		rot := a.Rotation * math.Pi / 180
		cs, sn := math.Cos(rot), math.Sin(rot)
		v = [3]float64{cs*v[0] - sn*v[1], sn*v[0] + cs*v[1], v[2]}
	}
	return [3]float64{c[0] + v[0], c[1] + v[1], c[2] + v[2]}
}

// quatRotate rotates v by unit quaternion q (w,x,y,z).
func quatRotate(q [4]float64, v [3]float64) [3]float64 {
	w, x, y, z := q[0], q[1], q[2], q[3]
	tx := 2 * (y*v[2] - z*v[1])
	ty := 2 * (z*v[0] - x*v[2])
	tz := 2 * (x*v[1] - y*v[0])
	return [3]float64{
		v[0] + w*tx + (y*tz - z*ty),
		v[1] + w*ty + (z*tx - x*tz),
		v[2] + w*tz + (x*ty - y*tx),
	}
}

// quatBasis returns the rotated Z (normal) and X (xnormal) axes of a
// quaternion, for building ellipse edges.
func quatBasis(q [4]float64) (normal, xnormal Vector3) {
	n := quatRotate(q, [3]float64{0, 0, 1})
	x := quatRotate(q, [3]float64{1, 0, 0})
	return NewVector3(n), NewVector3(x)
}

// shapeFor builds face/solid geometry: the KindCone frustum as a real
// cone solid, the KindSolid mesh as a compound of its face loops.
func (r *DgnReader) shapeFor(e *scene.Entity) *Shape {
	switch e.Kind {
	case scene.KindCone:
		return r.coneShape(e)
	case scene.KindSolid:
		return r.meshShape(e)
	}
	return nil
}

// coneShape builds the frustum P1/R1 → P2/R2 as an OCCT cone solid
// (planar caps included). Degenerate axes (zero height) and zero radii
// pairs produce no shape.
func (r *DgnReader) coneShape(e *scene.Entity) *Shape {
	if len(e.Points) < 2 {
		return nil
	}
	p1 := r.scalePoint(e.Points[0])
	p2 := r.scalePoint(e.Points[1])
	r1, r2 := e.Radii[0], e.Radii[1]
	if r.units > 0 {
		r1 /= r.units
		r2 /= r.units
	}
	if r1 < 0 {
		r1 = -r1
	}
	if r2 < 0 {
		r2 = -r2
	}
	axis := [3]float64{p2[0] - p1[0], p2[1] - p1[1], p2[2] - p1[2]}
	h := math.Sqrt(axis[0]*axis[0] + axis[1]*axis[1] + axis[2]*axis[2])
	if h == 0 || (r1 == 0 && r2 == 0) {
		return nil
	}
	n := [3]float64{axis[0] / h, axis[1] / h, axis[2] / h}
	a := NewAxis2(NewPoint3(p1), NewDir3FromXYZ(n))
	// OCCT BRepPrimAPI_MakeCone rejects equal radii (throws, leaving an
	// empty shell that crashes downstream) — bridge those as cylinders.
	var shell *Shell
	if math.Abs(r1-r2) <= 1e-12*(1+math.Abs(r1)) {
		shell = TopoMakeShellFromCylinderAxis2(a, r1, h)
	} else {
		shell = TopoMakeShellFromConeAxis2(a, r1, r2, h)
	}
	if shell == nil {
		return nil
	}
	if ss, err := shell.ToShape(); err != nil || ss == nil || ss.IsNull() {
		return nil // primitive construction failed inside OCCT
	}
	solid := TopoMakeSolidFromShell(shell)
	if solid == nil || solid.IsNull() {
		return nil
	}
	sh := solid.ToShape()
	if sh == nil || sh.IsNull() {
		return nil
	}
	return sh
}

// meshShape turns a KindSolid's face loops (vertex indices into Points)
// into polygon faces aggregated as one compound shape. Entities without
// decodable faces (clouds, ambiguous index streams) produce no shape —
// the vertices remain on the Entity.
func (r *DgnReader) meshShape(e *scene.Entity) *Shape {
	if len(e.Faces) == 0 || len(e.Points) == 0 {
		return nil
	}
	pts := make([]Point3, len(e.Points))
	for i, p := range e.Points {
		pts[i] = NewPoint3(r.scalePoint(p))
	}
	shapes := make([]Shape, 0, len(e.Faces))
	for _, f := range e.Faces {
		if len(f) < 3 {
			continue
		}
		fp := make([]Point3, 0, len(f))
		ok := true
		for _, idx := range f {
			if idx < 0 || int(idx) >= len(pts) {
				ok = false
				break
			}
			fp = append(fp, pts[idx])
		}
		if !ok {
			continue
		}
		face := TopoMakeFaceFromPoints(fp)
		if face == nil || face.IsNull() {
			continue
		}
		shapes = append(shapes, *face.ToShape())
	}
	if len(shapes) == 0 {
		return nil
	}
	comp := TopoCompoundMake(shapes)
	if comp == nil || comp.IsNull() {
		return nil
	}
	sh := comp.ToShape()
	if sh == nil || sh.IsNull() {
		return nil
	}
	return sh
}
