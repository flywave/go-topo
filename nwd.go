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
//     yet located (U21). Only the unambiguous small polygons are built:
//     3 vertices -> one triangle, 4 -> one quad. Larger elements
//     (fans/strips) emit vertices only, never wrong geometry;
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

// shapeFor builds a topo Shape for a geometry block.
//   - LineSet (95): vertices → edge compound (exact for the dominant
//     2-vertex segments; longer elements chain as a polyline).
//   - TriangleSet (94): only the unambiguous small polygons are built —
//     3 vertices → one triangle, 4 vertices → one quad (two triangles).
//     Larger elements (6/10-vertex fans/strips) require the quantized
//     index table that go-nwd does not yet locate (U21), so they emit no
//     Shape (vertices + BBox only) rather than wrong geometry.
//   - PointSet (96): no Shape.
func (r *NwdReader) shapeFor(el *NwdElement, pts []Point3) *Shape {
	switch el.ElementType {
	case 95:
		return edgeCompound(pts)
	case 94:
		switch len(pts) {
		case 3:
			if s := faceCompound([]Point3{pts[0], pts[1], pts[2]}); s != nil {
				el.TriangleCount = 1
				return s
			}
		case 4:
			if s := faceCompound([]Point3{pts[0], pts[1], pts[2], pts[0], pts[2], pts[3]}); s != nil {
				el.TriangleCount = 2
				return s
			}
		}
		return nil
	default:
		return nil
	}
}

// faceCompound builds planar triangle faces from consecutive vertex
// triples and returns them as a compound Shape.
func faceCompound(tris []Point3) *Shape {
	shapes := make([]Shape, 0, len(tris)/3)
	for i := 0; i+2 < len(tris); i += 3 {
		f := TopoMakeFaceFromPoints([]Point3{tris[i], tris[i+1], tris[i+2]})
		if !faceValid(f) {
			continue
		}
		if s := f.ToShape(); s != nil && !s.IsNull() {
			shapes = append(shapes, *s)
		}
	}
	return compoundShape(shapes)
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
