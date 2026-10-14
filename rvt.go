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
	"regexp"
	"sort"
	"strconv"
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

	// Transform is the family instance's placement as a column-major 4×4
	// (rotation from the instance's X/Y/Z axes, translation from its
	// origin; 2023+, nil when the data holds none).
	Transform *[16]float64
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
		var instTransforms map[uint32]rvt.InstanceTransform
		if rep.Version >= 2023 {
			// family-instance placements (doors, windows, furniture, …)
			fiTag := rep.Schema.ByName("FamilyInstance")
			if fiTag != nil {
				fiIDs := make(map[uint32]bool)
				for i := range rep.Records {
					if rep.Records[i].ClassTag == fiTag.Tag && rep.Records[i].IsPlacedInstance() {
						fiIDs[rep.Records[i].ElementID] = true
					}
				}
				instTransforms = rvt.ScanInstanceTransforms(part, rep.Schema, fiIDs, rep.Version)
			}
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
		symJoin := rvt.SymbolTypeJoin(rep.Records, part, rep.Schema, rep.Version)
		nameIDs := make(map[uint32]bool, len(byID))
		for i := range rep.Records {
			if rep.Records[i].IsTypeSymbol() {
				nameIDs[rep.Records[i].ElementID] = true
			}
		}
		for id := range typeThickness {
			nameIDs[id] = true
		}
		for _, sym := range symJoin {
			nameIDs[sym] = true
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
				// family dimension first: a hosted instance's type is its
				// FamilySymbol, not the host's system-family type
				if sym, ok := symJoin[uint32(re.Id)]; ok {
					re.TypeName = typeNames[sym]
				} else if ty, ok := typeJoin[uint32(re.Id)]; ok {
					re.TypeName = typeNames[ty]
				} else if rec.IsTypeSymbol() {
					re.TypeName = typeNames[uint32(re.Id)]
				}
			}
			if t, ok := instTransforms[uint32(re.Id)]; ok {
				// column-major 4×4 (the DgnElement convention): columns
				// are the instance's X, Y, Z axes, column 3 = translation
				m := [16]float64{
					t.Axes[0][0], t.Axes[0][1], t.Axes[0][2], 0,
					t.Axes[1][0], t.Axes[1][1], t.Axes[1][2], 0,
					t.Axes[2][0], t.Axes[2][1], t.Axes[2][2], 0,
					t.Origin[0] * r.scale, t.Origin[1] * r.scale, t.Origin[2] * r.scale, 1,
				}
				re.Transform = &m
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
		r.proxyAndOpenings(rep, byID, wallLines)
		symJoinForDims := symJoin
		votedDims := rvt.VoteInstanceDims(part, rep.Schema, symJoinForDims, rep.Version)
		r.dimLeafBoxesAndOpenings(part, rep, byID, wallLines, instTransforms, symJoinForDims, votedDims)
	}
	return nil
}

// rvtDimRe matches type names carrying their dimensions in millimetres
// ("800 x 2100").
var rvtDimRe = regexp.MustCompile(`^(\d{3,4})\s*[xX]\s*(\d{3,4})$`)

// dimFeet parses a "W x H" millimetre type name into feet (0,0 when the
// name carries no dimensions).
func dimFeet(name string) (float64, float64) {
	m := rvtDimRe.FindStringSubmatch(strings.TrimSpace(name))
	if m == nil {
		return 0, 0
	}
	w, err1 := strconv.Atoi(m[1])
	h, err2 := strconv.Atoi(m[2])
	if err1 != nil || err2 != nil {
		return 0, 0
	}
	const mmToFeet = 0.003280839895013123
	return float64(w) * mmToFeet, float64(h) * mmToFeet
}

// dimLeafBoxesAndOpenings upgrades placed doors/windows whose type name
// carries their dimensions: the element's shape becomes an oriented leaf
// box (type width × host thickness × type height, placed at the instance
// transform), and a precise opening is cut from the resolved host wall.
func (r *RvtReader) dimLeafBoxesAndOpenings(part *rvt.Partition, rep *rvt.RecordsReport, byID map[uint32]*rvt.ElementRecord, wallLines map[uint32]*rvt.BoundedLine, transforms map[uint32]rvt.InstanceTransform, symJoin map[uint32]uint32, votedDims map[uint32][2]float64) {
	_ = part // reserved: pair-scan windows
	for i := range rep.Records {
		rec := &rep.Records[i]
		if rec.Category != rvtCategoryDoors && rec.Category != rvtCategoryWindows {
			continue
		}
		if !rec.IsPlacedInstance() || rec.PrecedingRef == 0 {
			continue
		}
		re := byElemOf(r.elements, rec.ElementID)
		if re == nil {
			continue
		}
		w, h := dimFeet(re.TypeName)
		isWindow := rec.Category == rvtCategoryWindows
		trusted := w > 0
		if w <= 0 {
			// symbol-voted dimensions (same-type instances agree on the
			// type's width/height constants) — trusted: the constants are
			// agreed by nearly every instance of the type
			if vd, ok := votedDims[symJoin[rec.ElementID]]; ok && (!isWindow || recHasPositiveZ(rec)) {
				w, h = vd[0], vd[1]
				trusted = true
			}
		}
		if w <= 0 && !isWindow {
			// last resort for single-instance door types: the symbol's
			// first plausible (height, width) f64 pair (heuristic — the
			// layout is verified on only 1 of 15 door symbols, R121).
			// The leaf is built best-effort; the wall is NOT cut (the
			// heuristic pair can misplace the opening and OCCT booleans
			// on misplaced slivers hang).
			if sw, sh, ok2 := rvt.ScanFirstDimPair(part, rep.Schema, symJoin[rec.ElementID], rep.Version); ok2 {
				w, h = sw, sh
			}
		}
		if w <= 0 || h <= 0 {
			continue
		}
		t, hasT := transforms[rec.ElementID]
		if !hasT {
			continue
		}
		host, line := r.resolveHost(rec, byID, wallLines, transforms, isWindow)
		if host == nil || line == nil {
			continue
		}
		wallElem := byElemOf(r.elements, host.ElementID)
		if wallElem == nil {
			continue
		}
		thk := r.wallThickness(host.BBox)
		if thk <= 0 {
			continue
		}
		// windows: the record bbox z center is the leaf's z center (the
		// instance origin z is the sill measured from an unknown base —
		// R115); doors: the origin is the leaf base
		var leaf *Shape
		if isWindow && re.BBox != nil {
			leaf = r.orientedBoxCenterZ(t, w, thk, h, re.BBox.Data()[2], re.BBox.Data()[5])
		} else {
			leaf = r.orientedBox(t, w, thk, h)
		}
		if leaf == nil {
			continue
		}
		re.Shape = leaf
		if wallElem.Shape == nil {
			continue
		}
		// boolean cut gates:
		//   trusted dims (name- or vote-verified): AABB overlap suffices;
		//   heuristic pair-scan dims: require geometry consistency — the
		//   leaf's z span must fit within the wall's z range and the
		//   wall's location line must cross the leaf's plan footprint
		//   (OCCT booleans on misplaced slivers hang, R122)
		allowed := false
		if trusted {
			allowed = r.leafOverlapsWall(t, w, thk, h, host.BBox)
		} else {
			a0, b0 := line.Endpoints()
			zFit := t.Origin[2] >= host.BBox[2]-0.1 && t.Origin[2]+h <= host.BBox[5]+0.5
			allowed = zFit && lineCutsBBox(a0, b0, leafPlanBBox(t, w, thk))
		}
		if allowed {
			if cut := Cut(wallElem.Shape, leaf, 1e-3, false); cut != nil && !cut.IsNull() {
				wallElem.Shape = cut
			}
		}
	}
}

// leafPlanBBox is the leaf's plan AABB (origin-centered, rotated).
func leafPlanBBox(t rvt.InstanceTransform, w, thk float64) [6]float64 {
	ux, uy := t.Axes[0][0], t.Axes[0][1]
	mag := math.Hypot(ux, uy)
	if mag < 1e-9 {
		return [6]float64{}
	}
	ux, uy = ux/mag, uy/mag
	px, py := -uy, ux
	hw, half := w/2, thk/2
	minX, minY := math.Inf(1), math.Inf(1)
	maxX, maxY := math.Inf(-1), math.Inf(-1)
	for _, sa := range []float64{-hw, hw} {
		for _, ac := range []float64{-half, half} {
			x := t.Origin[0] + sa*ux + ac*px
			y := t.Origin[1] + sa*uy + ac*py
			minX, maxX = math.Min(minX, x), math.Max(maxX, x)
			minY, maxY = math.Min(minY, y), math.Max(maxY, y)
		}
	}
	return [6]float64{minX, minY, 0, maxX, maxY, 0}
}

// leafOverlapsWall gates the boolean cut: the leaf's world AABB must
// overlap the host wall's bbox — heuristic dim pairs can land far from
// the wall and OCCT booleans on non-intersecting slivers can hang.
func (r *RvtReader) leafOverlapsWall(t rvt.InstanceTransform, w, thk, h float64, hostBBox [6]float64) bool {
	ux, uy := t.Axes[0][0], t.Axes[0][1]
	mag := math.Hypot(ux, uy)
	if mag < 1e-9 {
		return false
	}
	ux, uy = ux/mag, uy/mag
	px, py := -uy, ux
	hw, half := w/2, thk/2
	minX, minY := math.Inf(1), math.Inf(1)
	maxX, maxY := math.Inf(-1), math.Inf(-1)
	for _, sa := range []float64{-hw, hw} {
		for _, ac := range []float64{-half, half} {
			x := t.Origin[0] + sa*ux + ac*px
			y := t.Origin[1] + sa*uy + ac*py
			minX, maxX = math.Min(minX, x), math.Max(maxX, x)
			minY, maxY = math.Min(minY, y), math.Max(maxY, y)
		}
	}
	const tol = 0.05
	return maxX >= hostBBox[0]-tol && minX <= hostBBox[3]+tol &&
		maxY >= hostBBox[1]-tol && minY <= hostBBox[4]+tol &&
		t.Origin[2] >= hostBBox[2]-tol && t.Origin[2]+h <= hostBBox[5]+tol
}

// resolveHost finds a window's host wall: the preceding reference when it
// names a placed wall whose line cuts the opening's footprint, else the
// unique placed wall whose location line passes within 1.5 ft of the
// instance transform origin (the window sits ON its host's centerline).
func (r *RvtReader) resolveHost(rec *rvt.ElementRecord, byID map[uint32]*rvt.ElementRecord, wallLines map[uint32]*rvt.BoundedLine, transforms map[uint32]rvt.InstanceTransform, skipZ bool) (*rvt.ElementRecord, *rvt.BoundedLine) {
	if prev, has := byID[rec.PrecedingRef]; has && prev.Category == rvtCategoryWalls && prev.IsPlacedInstance() {
		if l, ok := wallLines[prev.ElementID]; ok {
			a, b := l.Endpoints()
			if lineCutsBBox(a, b, rec.BBox) {
				return prev, l
			}
		}
	}
	t, hasT := transforms[rec.ElementID]
	if !hasT {
		return nil, nil
	}
	ox, oy := t.Origin[0], t.Origin[1]
	oz := t.Origin[2]
	hits := 0
	var host *rvt.ElementRecord
	var best *rvt.BoundedLine
	for id, l := range wallLines {
		a, b := l.Endpoints()
		dx, dy := b[0]-a[0], b[1]-a[1]
		l2 := dx*dx + dy*dy
		if l2 < 1e-12 {
			continue
		}
		tp := ((ox-a[0])*dx + (oy-a[1])*dy) / l2
		if tp <= 0.001 || tp >= 0.999 {
			continue
		}
		cx, cy := a[0]+tp*dx, a[1]+tp*dy
		if math.Hypot(ox-cx, oy-cy) > 1.5 {
			continue
		}
		if !skipZ {
			// doors: the origin z is the leaf base and must sit within the
			// wall's z range; windows: the origin z is a sill measured from
			// an unknown base (R115) — the leaf z comes from the record
			// bbox center instead, so no z gate here
			if oz < math.Min(a[2], b[2])-1 || oz > math.Max(a[2], b[2])+1 {
				continue
			}
		}
		hits++
		host = byID[id]
		best = l
	}
	if hits == 1 {
		return host, best
	}
	return nil, nil
}

// recHasPositiveZ guards the window leaf placement: the record bbox must
// have a positive z extent to provide the leaf's z center.
func recHasPositiveZ(rec *rvt.ElementRecord) bool {
	return rec.BBox[5] > rec.BBox[2]
}

// byElemOf finds the bridged element by id.
func byElemOf(els []*RvtElement, id uint32) *RvtElement {
	for _, re := range els {
		if re.Id == uint64(id) {
			return re
		}
	}
	return nil
}

// orientedBoxCenterZ builds the W×T×H box with its plan frame at the
// transform origin but the z extent centered on zc (window leaves: the
// instance origin z is the sill measured from an unknown base, while the
// record bbox z center is the leaf's true center — findings R115).
func (r *RvtReader) orientedBoxCenterZ(t rvt.InstanceTransform, w, thk, h, zMin, zMax float64) *Shape {
	zc := (zMin + zMax) / 2
	ux, uy := t.Axes[0][0], t.Axes[0][1]
	mag := math.Hypot(ux, uy)
	if mag < 1e-9 {
		return nil
	}
	ux, uy = ux/mag, uy/mag
	px, py := -uy, ux
	half := thk / 2
	hw := w / 2
	hh := h / 2
	z0 := zc - hh
	if z0 <= 0 {
		return nil
	}
	corner := func(along, across float64) Point3 {
		return NewPoint3([3]float64{
			(t.Origin[0] + along*ux + across*px) * r.scale,
			(t.Origin[1] + along*uy + across*py) * r.scale,
			z0 * r.scale,
		})
	}
	var edges []Edge
	pts := []Point3{
		corner(-hw, -half),
		corner(hw, -half),
		corner(hw, half),
		corner(-hw, half),
	}
	for i := 0; i < 4; i++ {
		ed := TopoMakeEdgeFromTwoPoint(pts[i], pts[(i+1)%4])
		if !edgeValid(ed) {
			return nil
		}
		edges = append(edges, *ed)
	}
	wire := TopoMakeWireFromEdges(edges)
	if wire == nil || wire.IsNull() {
		return nil
	}
	s := ExtrudeLinear(wire, nil, NewVector3([3]float64{0, 0, h * r.scale}), 0)
	if s == nil || s.IsNull() {
		return nil
	}
	return s
}

// orientedBox builds a W×T×H box at the transform origin, rotated by the
// instance's plan X axis (W along X, T along the plan normal).
func (r *RvtReader) orientedBox(t rvt.InstanceTransform, w, thk, h float64) *Shape {
	ux, uy := t.Axes[0][0], t.Axes[0][1]
	mag := math.Hypot(ux, uy)
	if mag < 1e-9 {
		return nil
	}
	ux, uy = ux/mag, uy/mag
	px, py := -uy, ux
	half := thk / 2
	hw := w / 2
	corner := func(along, across, up float64) Point3 {
		return NewPoint3([3]float64{
			(t.Origin[0] + along*ux + across*px) * r.scale,
			(t.Origin[1] + along*uy + across*py) * r.scale,
			(t.Origin[2] + up) * r.scale,
		})
	}
	var edges []Edge
	pts := []Point3{
		corner(-hw, -half, 0),
		corner(hw, -half, 0),
		corner(hw, half, 0),
		corner(-hw, half, 0),
	}
	for i := 0; i < 4; i++ {
		ed := TopoMakeEdgeFromTwoPoint(pts[i], pts[(i+1)%4])
		if !edgeValid(ed) {
			return nil
		}
		edges = append(edges, *ed)
	}
	wire := TopoMakeWireFromEdges(edges)
	if wire == nil || wire.IsNull() {
		return nil
	}
	s := ExtrudeLinear(wire, nil, NewVector3([3]float64{0, 0, h * r.scale}), 0)
	if s == nil || s.IsNull() {
		return nil
	}
	return s
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
			// ElementHeader CategoryId lives in the same BuiltInCategory
			// space (verified 2022: wall-class 8/8 = OST_Walls); records
			// overwrite it on 2023 with the same value
			if e.CategoryID < 0 {
				re.Category = int64(e.CategoryID)
			}
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


// proxyAndOpenings gives every bbox-bearing element without a real shape
// a box proxy solid (the element's record envelope), then cuts
// door/window openings from their host walls where the host is
// unambiguous: the preceding reference names a placed wall whose
// location line passes through the opening's plan footprint (measured:
// 15 of 33 doors+windows on rac_basic_2023; the rest keep full walls
// rather than guess).
func (r *RvtReader) proxyAndOpenings(rep *rvt.RecordsReport, byID map[uint32]*rvt.ElementRecord, wallLines map[uint32]*rvt.BoundedLine) {
	byElem := make(map[uint64]*RvtElement, len(r.elements))
	for _, re := range r.elements {
		if re.BBox != nil && re.Shape == nil {
			d := re.BBox.Data()
			if d[3] > d[0] && d[4] > d[1] && d[5] > d[2] {
				re.Shape = CreateBoxShape(BoxShapeParams{
					Point1: NewPoint3([3]float64{d[0], d[1], d[2]}),
					Point2: NewPoint3([3]float64{d[3], d[4], d[5]}),
				})
			}
		}
		byElem[re.Id] = re
	}
	// openings: placed doors/windows whose preceding reference is a
	// placed wall with a location line through the opening's footprint
	for i := range rep.Records {
		rec := &rep.Records[i]
		if rec.Category != rvtCategoryDoors && rec.Category != rvtCategoryWindows {
			continue
		}
		if !rec.IsPlacedInstance() || rec.PrecedingRef == 0 {
			continue
		}
		host := byID[rec.PrecedingRef]
		if host == nil || host.Category != rvtCategoryWalls || !host.IsPlacedInstance() {
			continue
		}
		line, has := wallLines[host.ElementID]
		if !has {
			continue
		}
		a, b := line.Endpoints()
		if !lineCutsBBox(a, b, rec.BBox) {
			continue
		}
		wallElem := byElem[uint64(host.ElementID)]
		opening := byElem[uint64(rec.ElementID)]
		if wallElem == nil || opening == nil || wallElem.Shape == nil || opening.Shape == nil {
			continue
		}
		if cut := Cut(wallElem.Shape, opening.Shape, 1e-3, false); cut != nil && !cut.IsNull() {
			wallElem.Shape = cut
		}
	}
}

// rvtCategoryDoors / rvtCategoryWindows are Autodesk BuiltInCategory ids.
const (
	rvtCategoryDoors   = -2_000_023
	rvtCategoryWindows = -2_000_014
)

// lineCutsBBox reports whether the segment's plan projection crosses the
// bbox's plan footprint (slab method).
func lineCutsBBox(a, b [3]float64, bb [6]float64) bool {
	dx, dy := b[0]-a[0], b[1]-a[1]
	t0, t1 := 0.0, 1.0
	if math.Abs(dx) < 1e-12 {
		if a[0] < bb[0] || a[0] > bb[3] {
			return false
		}
	} else {
		ta := (bb[0] - a[0]) / dx
		tb := (bb[3] - a[0]) / dx
		if ta > tb {
			ta, tb = tb, ta
		}
		if ta > t0 {
			t0 = ta
		}
		if tb < t1 {
			t1 = tb
		}
		if t0 > t1 {
			return false
		}
	}
	if math.Abs(dy) < 1e-12 {
		if a[1] < bb[1] || a[1] > bb[4] {
			return false
		}
	} else {
		ta := (bb[1] - a[1]) / dy
		tb := (bb[4] - a[1]) / dy
		if ta > tb {
			ta, tb = tb, ta
		}
		if ta > t0 {
			t0 = ta
		}
		if tb < t1 {
			t1 = tb
		}
		if t0 > t1 {
			return false
		}
	}
	return true
}
