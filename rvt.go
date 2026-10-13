package topo

// RVT bridge: pure-Go parsing via github.com/flywave/go-rvt, converted to
// topo Wire primitives (cgo). Mirrors the DGN converter pattern (dgn.go):
// a reader object loads a file and hands out every geometry-bearing
// element with identity, spatial envelope and curve geometry.
//
// Coverage contract (go-rvt GeometryManifest): every element of the RVT
// that carries geometry evidence — a GElement tree, attributed curves/arcs
// or an attributed BRep topology skeleton — yields exactly one RvtElement.
// Elements without geometry evidence (datums, parameters, tables) are
// metadata-only in the file and are not emitted.
//
// Geometry fidelity is bounded by what go-rvt decodes today:
//   - straight segments and circular arcs are exact (topo Wire edges);
//   - the element envelope BBox is exact (G-tree GeomBBox);
//   - solid BReps are bridged as topology skeletons (face/edge counts) —
//     Revit's cached face surfaces are not yet decoded (go-rvt M7+ wall,
//     findings R94/R97a), so no solid Shape is built from them.
//
// Units: Revit internal units are feet; SetScale converts (e.g. 0.3048
// for meters). Default 1 (feet preserved).

import (
	"fmt"
	"math"
	"os"
	"sort"
	"strings"

	"github.com/flywave/go-rvt/rvt"
	"github.com/flywave/go-rvt/rvt/geom"
)

// RvtElement is one geometry-bearing Revit element. Wires carry the exact
// decoded curve geometry (segments and arcs); BBox carries the world
// envelope. ClassName is the resolved OdBm* class (e.g. OdBmWall).
//
// The record-derived fields (Category, HostId, OwnerId, ContainerId,
// placement flags) are populated on Revit 2023 files from the partition
// element records (cross-validated against the rvt-rs reference
// implementation); they are zero/false on releases whose record shape is
// not proven.
type RvtElement struct {
	Id         uint64
	ClassName  string
	CategoryID int32
	FamilyID   int32
	BBox       *BBox
	Wires      []*Wire
	LineCount  int
	ArcCount   int
	FaceCount  int // BRep topology skeleton size (0 when none)
	EdgeCount  int

	// Element-record enrichment (2023+):
	Category    int64  // Autodesk BuiltInCategory (negative constant)
	HostId      uint64 // host wall for doors/windows (preceding reference)
	OwnerId     uint64 // sketch owner (second reference list's last slot)
	ContainerId uint64 // container element, 0 when none
	Placed      bool   // placed instance placement kind
	TypeSymbol  bool   // type/symbol envelope placement kind

	// Profile is the element's reconstructed sketch plan profile (from
	// its OST_SKETCH_LINES records — floors, roofs, ceilings, pads; 2023+).
	// Shape is the profile extruded through the record's Z extent — the
	// element's real slab solid when the sketch closes unambiguously.
	Profile *rvt.PlanProfile
	Shape   *Shape

	// TypeName is the element's type name from its type element's
	// framed data name (system families: "Generic 150mm"; family
	// instances: the family symbol's name; 2023+).
	TypeName string
}

// RvtReader loads an RVT file (OLE/CFB) and converts it to topo elements.
type RvtReader struct {
	scale    float64
	version  string // BasicFileInfo.SavedInVersion as stored
	elements []*RvtElement
	records  int // element records decoded (2023+)
}

func NewRvtReader() *RvtReader { return &RvtReader{scale: 1} }

// SetScale sets the unit multiplier applied to Revit internal units
// (feet). Call before Load. 0.3048 converts to meters.
func (r *RvtReader) SetScale(feetToTarget float64) { r.scale = feetToTarget }

// RevitVersion returns the source file's Revit version string (valid
// after Load).
func (r *RvtReader) RevitVersion() string { return r.version }

// Load parses the RVT file at path.
func (r *RvtReader) Load(path string) error {
	b, err := os.ReadFile(path)
	if err != nil {
		return err
	}
	return r.LoadBytes(b)
}

// LoadBytes parses an in-memory RVT file.
func (r *RvtReader) LoadBytes(b []byte) error {
	r.elements = nil
	f, err := rvt.OpenCFB(b)
	if err != nil {
		return fmt.Errorf("rvt: cfb: %w", err)
	}
	var biggest string
	var sz uint64
	for _, sp := range f.StreamPaths() {
		if strings.HasPrefix(sp, "Partitions/") {
			s, _ := f.Size(sp)
			if s > sz {
				sz, biggest = s, sp
			}
		}
	}
	if biggest == "" {
		return fmt.Errorf("rvt: no geometry partition")
	}
	raw, err := f.Stream(biggest)
	if err != nil {
		return fmt.Errorf("rvt: partition stream: %w", err)
	}
	part, err := rvt.ReadPartition(strings.TrimPrefix(biggest, "Partitions/"), raw)
	if err != nil {
		return fmt.Errorf("rvt: partition: %w", err)
	}
	version := ""
	if md, err := rvt.Open(b); err == nil {
		version = md.RevitVersion
	}
	r.version = version
	m := part.Model(version)
	r.build(m)
	// Element-record enrichment (Revit 2023 layout): BuiltInCategory,
	// host/owner/container references and placement kinds, sketch
	// profiles and wall location curves.
	if rep, err := rvt.RecordsFromContainer(f, version); err == nil {
		byID := make(map[uint32]*rvt.ElementRecord, len(rep.Records))
		walls := make(map[uint32]bool)
		for i := range rep.Records {
			rec := &rep.Records[i]
			byID[rec.ElementID] = rec
			if rec.Category == rvtCategoryWalls && rec.IsPlacedInstance() {
				walls[rec.ElementID] = true
			}
		}
		r.records = len(rep.Records)
		var wallLines map[uint32]*rvt.BoundedLine
		var wallArcs map[uint32]*rvt.BoundedArc
		var typeThickness map[uint32]float64
		var typeJoin map[uint32]uint32
		var typeNames map[uint32]string
		if rep.Version >= 2023 {
			wallLines = rvt.ScanFirstBoundedLines(part, rep.Schema, walls, rep.Version)
			wallArcs = rvt.ScanFirstBoundedArcs(part, rep.Schema, walls, rep.Version)
			// exact wall thickness: the type element's compound layer sum,
			// joined through the instance's reference list
			if len(rep.Declared) > 0 {
				typeThickness = rvt.TypeLayerThickness(part, rep.Schema, rep.Declared, rep.Version)
				if len(typeThickness) > 0 {
					typeJoin = rvt.TypeJoinByReference(rep.Records, typeThickness)
				}
			}
		}
		wallThk := func(rec *rvt.ElementRecord) float64 {
			if typeJoin != nil {
				if ty, ok := typeJoin[rec.ElementID]; ok {
					return typeThickness[ty] * r.scale
				}
			}
			return r.wallThickness(rec.BBox)
		}
		// type names: every framed record type (FamilySymbol envelopes)
		// plus every layer-carrying type element
		nameIDs := make(map[uint32]bool, len(byID))
		for i := range rep.Records {
			if rep.Records[i].IsTypeSymbol() {
				nameIDs[rep.Records[i].ElementID] = true
			}
		}
		for id := range typeThickness {
			nameIDs[id] = true
		}
		if len(nameIDs) > 0 {
			typeNames = rvt.ScanElementDataNames(part, rep.Schema, nameIDs, rep.Version)
		}
		for _, re := range r.elements {
			rec, ok := byID[uint32(re.Id)]
			if !ok {
				continue
			}
			re.Category = rec.Category
			re.HostId = uint64(rec.PrecedingRef)
			re.OwnerId = uint64(rec.OwnerRef)
			if rec.HasContainer() {
				re.ContainerId = uint64(rec.Container)
			}
			re.Placed = rec.IsPlacedInstance()
			re.TypeSymbol = rec.IsTypeSymbol()
			if typeNames != nil {
				if ty, ok := typeJoin[uint32(re.Id)]; ok {
					re.TypeName = typeNames[ty]
				} else if rec.IsTypeSymbol() {
					re.TypeName = typeNames[uint32(re.Id)]
				}
			}
			if profile := rep.Profiles[uint32(re.Id)]; profile != nil {
				re.Profile = profile
				re.Shape = r.profileShape(profile, rec.BBox[2], rec.BBox[5])
			}
			if re.Shape == nil {
				if l, has := wallLines[uint32(re.Id)]; has {
					re.Shape = r.wallShapeFromLine(l, wallThk(rec), rec.BBox)
				} else if a, has := wallArcs[uint32(re.Id)]; has {
					re.Shape = r.wallShapeFromArc(a, wallThk(rec), rec.BBox)
				}
			}
		}
	}
	return nil
}

// rvtCategoryWalls is Autodesk BuiltInCategory.OST_Walls.
const rvtCategoryWalls = -2_000_011

// wallThickness falls back to the record bbox's thin plan extent (exact
// for axis-aligned walls, approximate for oblique ones). The precise
// thickness is the type's compound layer sum, joined by the caller.
func (r *RvtReader) wallThickness(bbox [6]float64) float64 {
	dx := bbox[3] - bbox[0]
	dy := bbox[4] - bbox[1]
	t := math.Min(dx, dy)
	if t <= 0 || !isFiniteBox(t) {
		return 0
	}
	return t * r.scale
}

func isFiniteBox(v float64) bool { return !math.IsNaN(v) && !math.IsInf(v, 0) }

// wallShapeFromLine extrudes the wall's rectangular body along its
// location line, through the record's Z extent.
func (r *RvtReader) wallShapeFromLine(l *rvt.BoundedLine, thickness float64, bbox [6]float64) *Shape {
	z0, z1 := bbox[2], bbox[5]
	a, b := l.Endpoints()
	if thickness <= 0 || z1-z0 <= 1e-9 {
		return nil
	}
	dx, dy := b[0]-a[0], b[1]-a[1]
	length := math.Hypot(dx, dy)
	if length < 1e-9 {
		return nil
	}
	ux, uy := dx/length, dy/length
	px, py := -uy, ux
	half := thickness / 2
	corner := func(s, o float64) Point3 {
		return NewPoint3([3]float64{(a[0] + s*ux + o*px) * r.scale, (a[1] + s*uy + o*py) * r.scale, z0 * r.scale})
	}
	wire := rectWire(corner(-half, -half), corner(length+half, -half), corner(length+half, half), corner(-half, half))
	if wire == nil {
		return nil
	}
	s := ExtrudeLinear(wire, nil, NewVector3([3]float64{0, 0, (z1 - z0) * r.scale}), 0)
	if s == nil || s.IsNull() {
		return nil
	}
	return s
}

// wallShapeFromArc extrudes a curved wall's ring-sector body along its
// location arc.
func (r *RvtReader) wallShapeFromArc(a *rvt.BoundedArc, thickness float64, bbox [6]float64) *Shape {
	z0, z1 := bbox[2], bbox[5]
	if thickness <= 0 || z1-z0 <= 1e-9 {
		return nil
	}
	span := a.EndAngle - a.StartAngle
	if span <= 0 || span > 2*math.Pi {
		return nil
	}
	outer := arcWirePts(a.Center, a.Radius+thickness/2, a.XAxis, a.YAxis, a.StartAngle, a.EndAngle, r.scale, z0*r.scale)
	inner := arcWirePts(a.Center, a.Radius-thickness/2, a.XAxis, a.YAxis, a.StartAngle, a.EndAngle, r.scale, z0*r.scale)
	if outer == nil || inner == nil {
		return nil
	}
	w := TopoMakeWireFromEdges(outer)
	if w == nil || w.IsNull() {
		return nil
	}
	s := ExtrudeLinear(w, nil, NewVector3([3]float64{0, 0, (z1 - z0) * r.scale}), 0)
	if s == nil || s.IsNull() {
		return nil
	}
	return s
}

// arcWirePts samples a circular arc into chained edges.
func arcWirePts(center [3]float64, radius float64, xaxis, yaxis [3]float64, start, end, scale, z float64) []Edge {
	span := end - start
	steps := int(span/0.1) + 2
	if steps > 256 {
		steps = 256
	}
	var edges []Edge
	prev := [3]float64{
		(center[0] + radius*(math.Cos(start)*xaxis[0]+math.Sin(start)*yaxis[0])) * scale,
		(center[1] + radius*(math.Cos(start)*xaxis[1]+math.Sin(start)*yaxis[1])) * scale,
		z,
	}
	for i := 1; i <= steps; i++ {
		t := start + span*float64(i)/float64(steps)
		p := [3]float64{
			(center[0] + radius*(math.Cos(t)*xaxis[0]+math.Sin(t)*yaxis[0])) * scale,
			(center[1] + radius*(math.Cos(t)*xaxis[1]+math.Sin(t)*yaxis[1])) * scale,
			z,
		}
		ed := TopoMakeEdgeFromTwoPoint(NewPoint3(prev), NewPoint3(p))
		if !edgeValid(ed) {
			return nil
		}
		edges = append(edges, *ed)
		prev = p
	}
	return edges
}

// rectWire chains four corners into a closed wire.
func rectWire(c1, c2, c3, c4 Point3) *Wire {
	var edges []Edge
	pts := []Point3{c1, c2, c3, c4}
	for i := 0; i < 4; i++ {
		ed := TopoMakeEdgeFromTwoPoint(pts[i], pts[(i+1)%4])
		if !edgeValid(ed) {
			return nil
		}
		edges = append(edges, *ed)
	}
	w := TopoMakeWireFromEdges(edges)
	if w == nil || w.IsNull() {
		return nil
	}
	return w
}

// profileShape extrudes a plan profile through [z0, z1] (record Z extent,
// feet) into a prism solid. nil when the loop is degenerate or the OCCT
// extrude fails.
func (r *RvtReader) profileShape(p *rvt.PlanProfile, z0, z1 float64) *Shape {
	if len(p.OuterXY) < 3 || !finitePt([3]float64{z0, 0, z1}) || z1-z0 <= 1e-9 {
		return nil
	}
	ring := func(loop []rvt.Point2) (*Wire, bool) {
		edges := make([]Edge, 0, len(loop))
		for i := 0; i < len(loop); i++ {
			a := loop[i]
			b := loop[(i+1)%len(loop)]
			p1 := NewPoint3([3]float64{a.X * r.scale, a.Y * r.scale, z0 * r.scale})
			p2 := NewPoint3([3]float64{b.X * r.scale, b.Y * r.scale, z0 * r.scale})
			if dist3(p1.Data(), p2.Data()) < 1e-12 {
				return nil, false
			}
			ed := TopoMakeEdgeFromTwoPoint(p1, p2)
			if !edgeValid(ed) {
				return nil, false
			}
			edges = append(edges, *ed)
		}
		w := TopoMakeWireFromEdges(edges)
		if w == nil || w.IsNull() {
			return nil, false
		}
		return w, true
	}
	outer, ok := ring(p.OuterXY)
	if !ok {
		return nil
	}
	var inners []*Wire
	for _, inner := range p.InnerXY {
		if w, ok := ring(inner); ok {
			inners = append(inners, w)
		}
	}
	s := ExtrudeLinear(outer, inners, NewVector3([3]float64{0, 0, (z1 - z0) * r.scale}), 0)
	if s == nil || s.IsNull() {
		return nil
	}
	return s
}

// GetElements returns the converted elements (valid after Load).
func (r *RvtReader) GetElements() []*RvtElement { return r.elements }

// RecordCount returns the number of partition element records decoded
// (Revit 2023 layout; 0 on unproven releases).
func (r *RvtReader) RecordCount() int { return r.records }

func (r *RvtReader) build(m *rvt.Model) {
	manifest := m.GeometryManifest()
	byID := make(map[uint32]*geom.Element, len(m.Elements))
	for i := range m.Elements {
		byID[m.Elements[i].ID] = &m.Elements[i]
	}
	ids := make([]int, 0, len(manifest))
	for id := range manifest {
		ids = append(ids, int(id))
	}
	sort.Ints(ids)
	r.elements = make([]*RvtElement, 0, len(ids))
	for _, id := range ids {
		g := manifest[uint32(id)]
		re := &RvtElement{
			Id:        uint64(g.ElementID),
			LineCount: len(g.Lines),
			ArcCount:  len(g.Arcs),
		}
		if e := byID[g.ElementID]; e != nil {
			re.ClassName = e.ClassName
			re.CategoryID = e.CategoryID
			re.FamilyID = e.FamilyID
		}
		if g.BBox != nil {
			bb := NewBBox([6]float64{
				g.BBox.Min.X * r.scale, g.BBox.Min.Y * r.scale, g.BBox.Min.Z * r.scale,
				g.BBox.Max.X * r.scale, g.BBox.Max.Y * r.scale, g.BBox.Max.Z * r.scale,
			})
			re.BBox = &bb
		}
		re.Wires = r.wiresFor(g)
		if g.BRep != nil {
			re.FaceCount = len(g.BRep.FaceIDs)
			re.EdgeCount = len(g.BRep.EdgeIDs)
		}
		r.elements = append(r.elements, re)
	}
}

// wiresFor builds wires from the element's curves: consecutive segments
// chain into one polyline wire only when endpoints actually connect
// (MakeWire requires connectivity); arcs become one wire each.
func (r *RvtReader) wiresFor(g *geom.ElementGeometry) []*Wire {
	var out []*Wire
	var run []Edge
	var runEnd [3]float64
	haveEnd := false
	flush := func() {
		if len(run) == 0 {
			return
		}
		var w *Wire
		if len(run) == 1 {
			w = TopoMakeWireFromEdge(run[0])
		} else {
			w = TopoMakeWireFromEdges(run)
		}
		if w != nil && !w.IsNull() {
			out = append(out, w)
		}
		run = run[:0]
		haveEnd = false
	}
	for _, ln := range g.Lines {
		// Line.Direction stores the second endpoint triple as decoded
		// (go-rvt R86/R88: on-disk values read as endpoint pairs).
		p1 := r.pt(ln.Origin)
		p2 := r.pt(ln.Direction)
		if !finitePt(p1) || !finitePt(p2) || dist3(p1, p2) < 1e-12 {
			continue
		}
		if haveEnd && dist3(runEnd, p1) > 1e-6 {
			flush()
		}
		if ed := TopoMakeEdgeFromTwoPoint(NewPoint3(p1), NewPoint3(p2)); edgeValid(ed) {
			run = append(run, *ed)
			runEnd = p2
			haveEnd = true
		}
	}
	flush()
	for _, a := range g.Arcs {
		if w := r.arcWire(a); w != nil {
			out = append(out, w)
		}
	}
	return out
}

// arcWire builds an exact circle/arc edge. GArc axes are orthonormal plane
// vectors; StartAngle/EndAngle are the curve parameters when decoded —
// equal or implausible values mean the angular span is unknown and the
// arc bridges as a full circle. All inputs are re-validated here: the
// content-anchored scans can pass marginal values and the OCCT edge
// constructors segfault on degenerate/garbage geometry.
func (r *RvtReader) arcWire(a geom.Arc) *Wire {
	if !arcSane(a) {
		return nil
	}
	center := NewPoint3(r.pt(a.Center))
	normal := NewVector3([3]float64{
		a.XDir.Y*a.YDir.Z - a.XDir.Z*a.YDir.Y,
		a.XDir.Z*a.YDir.X - a.XDir.X*a.YDir.Z,
		a.XDir.X*a.YDir.Y - a.XDir.Y*a.YDir.X,
	})
	radius := a.Radius * r.scale
	span := a.EndAngle - a.StartAngle
	usable := !math.IsNaN(span) && !math.IsInf(span, 0) &&
		math.Abs(span) > 1e-9 && math.Abs(span) < 2*math.Pi-1e-9 &&
		math.Abs(a.StartAngle) < 100 && math.Abs(a.EndAngle) < 100
	if !usable {
		if ed := TopoMakeCircle(radius, center, normal, 0, 2*math.Pi, true); edgeValid(ed) {
			return TopoMakeWireFromEdge(*ed)
		}
		return nil
	}
	a0, a1 := a.StartAngle, a.EndAngle
	if a1 < a0 {
		a1 += 2 * math.Pi
	}
	pt := func(t float64) Point3 {
		return NewPoint3([3]float64{
			(a.Center.X + a.Radius*(math.Cos(t)*a.XDir.X+math.Sin(t)*a.YDir.X)) * r.scale,
			(a.Center.Y + a.Radius*(math.Cos(t)*a.XDir.Y+math.Sin(t)*a.YDir.Y)) * r.scale,
			(a.Center.Z + a.Radius*(math.Cos(t)*a.XDir.Z+math.Sin(t)*a.YDir.Z)) * r.scale,
		})
	}
	p1, p2, p3 := pt(a0), pt((a0+a1)/2), pt(a1)
	for _, p := range [][3]float64{p1.Data(), p2.Data(), p3.Data()} {
		if !finitePt(p) {
			return nil
		}
	}
	if ed := TopoMakeThreePointArc(p1, p2, p3); edgeValid(ed) {
		return TopoMakeWireFromEdge(*ed)
	}
	return nil
}

// arcSane rejects arcs whose decoded values are outside plausible Revit
// geometry ranges (internal feet): axes near-unit and orthogonal, radius
// positive and bounded, center finite within model extent.
func arcSane(a geom.Arc) bool {
	fin := func(v float64) bool { return !math.IsNaN(v) && !math.IsInf(v, 0) }
	mag := func(p geom.Point3) float64 { return math.Hypot(math.Hypot(p.X, p.Y), p.Z) }
	if !fin(a.Radius) || a.Radius <= 1e-9 || a.Radius > 1e4 {
		return false
	}
	if !fin(a.Center.X) || !fin(a.Center.Y) || !fin(a.Center.Z) || mag(a.Center) > 1e6 {
		return false
	}
	if !fin(a.XDir.X) || !fin(a.XDir.Y) || !fin(a.XDir.Z) {
		return false
	}
	if !fin(a.YDir.X) || !fin(a.YDir.Y) || !fin(a.YDir.Z) {
		return false
	}
	xm, ym := mag(a.XDir), mag(a.YDir)
	if xm < 0.5 || xm > 2 || ym < 0.5 || ym > 2 {
		return false
	}
	dot := a.XDir.X*a.YDir.X + a.XDir.Y*a.YDir.Y + a.XDir.Z*a.YDir.Z
	if math.Abs(dot) > 0.05*xm*ym {
		return false
	}
	return true
}

func finitePt(p [3]float64) bool {
	for _, v := range p {
		if math.IsNaN(v) || math.IsInf(v, 0) || math.Abs(v) > 1e8 {
			return false
		}
	}
	return true
}

func (r *RvtReader) pt(p geom.Point3) [3]float64 {
	return [3]float64{p.X * r.scale, p.Y * r.scale, p.Z * r.scale}
}
