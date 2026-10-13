package topo

// NWD bridge: pure-Go parsing via github.com/flywave/go-nwd, converted to
// topo primitives (cgo). Mirrors the DGN/RVT converter pattern
// (dgn.go, rvt.go): a reader loads a Navisworks .nwd file and hands out
// every geometry-bearing block with identity, spatial envelope and the
// decoded geometry.
//
// Coverage contract (go-nwd real-file findings N47/N48/N56/N59):
//   - the container, stream inventory, partition root and its attributes
//     (e.g. PublishAttribute) are decoded exactly;
//   - each geometry block's VertexSet is decoded exactly → vertices and
//     world-envelope BBox are exact;
//   - LineSetElement (type 95) vertices are endpoint pairs → exact edge
//     geometry is bridged as a Shape (compound of edges);
//   - TriangleSetElement (type 94) triangle indices use a quantized,
//     compressed index table that go-nwd decodes structurally
//     (DecodeIndexTable, findings N58) but whose per-element region is not
//     yet located (U21). Vertices are emitted; triangle faces are built
//     only when SetTriangleSoup(true) and the block vertex count is a
//     multiple of 3 (triangle-soup convention — best effort);
//   - PointSetElement (type 96) emits vertices with no Shape.
//
// Units: NWD geometry is stored in the file's model units (typically
// meters). Default scale 1; SetScale converts to the target unit.

import (
	"fmt"
	"math"
	"os"

	"github.com/flywave/go-nwd/nwd"
)

// NwdElement is one geometry-bearing NWD block (one geometry element).
type NwdElement struct {
	// Kind is "TriangleSet", "LineSet" or "PointSet".
	Kind        string
	ElementType int // raw element typeID (94/95/96)
	// BBox is the block's world-space envelope (scaled).
	BBox *BBox
	// VertexCount is the number of decoded vertices.
	VertexCount int
	// TriangleCount is non-zero only when triangle faces were built.
	TriangleCount int
	// Vertices are the decoded, scaled vertex coordinates.
	Vertices [][3]float64
	// Shape is the bridged solid/compound: an edge compound for line sets,
	// a face compound for triangle soup (when enabled), nil otherwise.
	Shape *Shape
	// Name is a synthetic label (kind + ordinal).
	Name string
}

// NwdReader loads a Navisworks .nwd file and converts its geometry to topo
// elements.
type NwdReader struct {
	scale    float64
	triSoup  bool
	file     *nwd.File
	elements []*NwdElement

	root  *nwd.PartitionRoot
	props []nwd.NameRecord
}

// NewNwdReader returns a reader with unit scale 1 and triangle soup off.
func NewNwdReader() *NwdReader { return &NwdReader{scale: 1} }

// SetScale sets the unit multiplier applied to NWD geometry. Call before
// Load. (NWD is commonly in meters; 1 preserves it.)
func (r *NwdReader) SetScale(f float64) { r.scale = f }

// SetTriangleSoup enables best-effort face construction for triangle
// elements whose vertex count is a multiple of 3 (non-indexed triangle
// soup). Off by default because NWD triangle indices are not yet decoded
// (go-nwd U21); enable only when the source is known to be soup.
func (r *NwdReader) SetTriangleSoup(v bool) { r.triSoup = v }

// Load parses the NWD file at path.
func (r *NwdReader) Load(path string) error {
	b, err := os.ReadFile(path)
	if err != nil {
		return err
	}
	return r.LoadBytes(b)
}

// LoadBytes parses an in-memory NWD file.
func (r *NwdReader) LoadBytes(b []byte) error {
	r.elements = nil
	f, err := nwd.Open(b)
	if err != nil {
		return fmt.Errorf("nwd: open: %w", err)
	}
	r.file = f

	if idx := f.StreamByName("LcOpNwdPartition"); idx >= 0 {
		r.root, _ = f.DecodePartitionRoot(idx)
	}
	if idx := f.StreamByName("LcOaPartitionProps"); idx >= 0 {
		r.props, _ = f.ScanStreamNames(idx, 20000)
	}

	gi := f.StreamByName("LcOpNwdGeometry")
	if gi < 0 {
		return fmt.Errorf("nwd: no geometry stream")
	}
	blocks, err := f.DecodeGeometryVertices(gi, 0)
	if err != nil {
		return fmt.Errorf("nwd: geometry: %w", err)
	}
	r.build(blocks)
	return nil
}

// GetElements returns the converted geometry elements (valid after Load).
func (r *NwdReader) GetElements() []*NwdElement { return r.elements }

// Model returns the container metadata (valid after Load).
func (r *NwdReader) Model() *nwd.Metadata {
	if r.file == nil {
		return nil
	}
	return r.file.Metadata
}

// PartitionRoot returns the decoded partition root (nil when absent).
func (r *NwdReader) PartitionRoot() *nwd.PartitionRoot { return r.root }

// PropertyNames returns the CDA property keys extracted from the property
// stream.
func (r *NwdReader) PropertyNames() []nwd.NameRecord { return r.props }

func (r *NwdReader) build(blocks []nwd.VertexBlock) {
	r.elements = make([]*NwdElement, 0, len(blocks))
	for i := range blocks {
		b := &blocks[i]
		if len(b.Vertices) == 0 {
			continue
		}
		el := &NwdElement{
			Kind:        nwdKind(b.ElementType),
			ElementType: b.ElementType,
			VertexCount: b.VertexCount,
			Name:        fmt.Sprintf("%s[%d]", nwdKind(b.ElementType), i),
		}
		el.Vertices = make([][3]float64, len(b.Vertices))
		var mn = [3]float64{math.Inf(1), math.Inf(1), math.Inf(1)}
		var mx = [3]float64{math.Inf(-1), math.Inf(-1), math.Inf(-1)}
		pts := make([]Point3, len(b.Vertices))
		for j, v := range b.Vertices {
			p := [3]float64{v[0] * r.scale, v[1] * r.scale, v[2] * r.scale}
			el.Vertices[j] = p
			pts[j] = NewPoint3(p)
			for k := 0; k < 3; k++ {
				if p[k] < mn[k] {
					mn[k] = p[k]
				}
				if p[k] > mx[k] {
					mx[k] = p[k]
				}
			}
		}
		if mn[0] <= mx[0] {
			bb := NewBBox([6]float64{mn[0], mn[1], mn[2], mx[0], mx[1], mx[2]})
			el.BBox = &bb
		}
		el.Shape = r.shapeFor(el, pts)
		r.elements = append(r.elements, el)
	}
}

func nwdKind(t int) string {
	switch t {
	case 94:
		return "TriangleSet"
	case 95:
		return "LineSet"
	case 96:
		return "PointSet"
	default:
		return fmt.Sprintf("Element%d", t)
	}
}

// shapeFor builds a topo Shape for a geometry block. Line sets become an
// edge compound; triangle sets become a face compound only in
// triangle-soup mode with a vertex count divisible by 3.
func (r *NwdReader) shapeFor(el *NwdElement, pts []Point3) *Shape {
	switch el.ElementType {
	case 95: // LineSet: consecutive vertex pairs are segments.
		return edgeCompound(pts)
	case 94: // TriangleSet
		if !r.triSoup || len(pts)%3 != 0 {
			return nil
		}
		return triangleCompound(pts, &el.TriangleCount)
	default:
		return nil
	}
}

// edgeCompound chains consecutive vertex pairs into edges and returns them
// as a compound Shape.
func edgeCompound(pts []Point3) *Shape {
	if len(pts) < 2 {
		return nil
	}
	shapes := make([]Shape, 0, len(pts)/2)
	for i := 0; i+1 < len(pts); i += 2 {
		ed := TopoMakeEdgeFromTwoPoint(pts[i], pts[i+1])
		if !edgeValid(ed) {
			continue
		}
		if s := ed.ToShape(); s != nil && !s.IsNull() {
			shapes = append(shapes, *s)
		}
	}
	return compoundShape(shapes)
}

// triangleCompound builds one planar face per 3 consecutive vertices.
func triangleCompound(pts []Point3, triCount *int) *Shape {
	shapes := make([]Shape, 0, len(pts)/3)
	for i := 0; i+2 < len(pts); i += 3 {
		f := TopoMakeFaceFromPoints([]Point3{pts[i], pts[i+1], pts[i+2]})
		if !faceValid(f) {
			continue
		}
		if s := f.ToShape(); s != nil && !s.IsNull() {
			shapes = append(shapes, *s)
		}
	}
	if len(shapes) == 0 {
		return nil
	}
	*triCount = len(shapes)
	return compoundShape(shapes)
}

func compoundShape(shapes []Shape) *Shape {
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
