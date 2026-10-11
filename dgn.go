package topo

// DGN bridge: pure-Go parsing via github.com/flywave/go-dgn, converted to
// topo Wire/Edge primitives (cgo). Mirrors the IFC converter pattern
// (ifc.go): a reader object loads a file and hands out elements with
// topology + metadata. Design: go-dgn analysis/05-go-design/topo-bridge.md.
//
// Coordinate contract:
//   - v7 files: TCB master-unit mapping applied (SceneV7AtMaster)
//   - v8 files: raw UOR unless SetUnits(uorPerMaster) is called first
//   - Transform is a column-major 4×4 for cell placements (nil otherwise)

import (
	"fmt"
	"math"
	"os"

	godgn "github.com/flywave/go-dgn/dgn"
	"github.com/flywave/go-dgn/dgn/scene"
)

// DgnElement is one geometry-bearing DGN element. Wire is nil for
// metadata-only kinds (text, cell defs, complex headers).
type DgnElement struct {
	Wire      *Wire
	Id        int
	ParentId  int
	Name      string
	Type      string // scene.Kind name
	Level     int
	Color     int
	Transform *[16]float64
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
		var all []scene.Entity
		for _, s := range f.ElementChunks() {
			chunk, err := f.Stream(s.Name)
			if err != nil {
				continue
			}
			idx := godgn.BuildChunkIndex(chunk)
			if len(idx.Offsets) == 0 {
				continue
			}
			ents, err := godgn.SceneV8(chunk, godgn.Dir{Base: 0, Offsets: idx.Offsets})
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
