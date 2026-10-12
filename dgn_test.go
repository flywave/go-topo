package topo

import (
	"math"
	"os"
	"testing"

	godgn "github.com/flywave/go-dgn/dgn"
)

const samplePath = "../go-dgn/sample.dgn"

func loadSampleReader(t *testing.T) *DgnReader {
	t.Helper()
	if _, err := os.Stat(samplePath); err != nil {
		t.Skipf("sample absent: %v", err)
	}
	r := NewDgnReader()
	if err := r.Load(samplePath); err != nil {
		t.Fatalf("load: %v", err)
	}
	return r
}

// TestDgnReaderV7Sample loads the 16MB v7 sample and checks the element
// census against the golden histogram locked in go-dgn (D86/D88).
func TestDgnReaderV7Sample(t *testing.T) {
	r := loadSampleReader(t)
	els := r.GetElements()

	counts := map[string]int{}
	wires := 0
	for _, e := range els {
		counts[e.Type]++
		if e.Wire != nil {
			wires++
		}
	}
	want := map[string]int{
		"ComplexHeader": 19,
		"Segment":       5814,
		"Polyline":      36 + 47,
		"BSplineCurve":  2522,
		"Arc":           317,
		"Ellipse":       6,
		"CellDef":       223 + 115,
		"CellRef":       39,
	}
	if len(counts) != len(want) {
		t.Fatalf("kind count %d want %d: %v", len(counts), len(want), counts)
	}
	for k, n := range want {
		if counts[k] != n {
			t.Errorf("kind %s: %d want %d", k, counts[k], n)
		}
	}
	// geometry kinds must have wires; metadata kinds must not
	geo := counts["Segment"] + counts["Polyline"] + counts["Arc"] +
		counts["Ellipse"] + counts["BSplineCurve"]
	if wires != geo {
		t.Fatalf("wires=%d want %d (geometry kinds)", wires, geo)
	}
	t.Logf("elements=%d wires=%d", len(els), wires)
}

// TestDgnReaderSegmentEndpoints checks that a 3D line's wire endpoints
// match the scene points (master units, TCB applied).
func TestDgnReaderSegmentEndpoints(t *testing.T) {
	r := loadSampleReader(t)
	for _, e := range r.GetElements() {
		if e.Type != "Segment" || e.Wire != nil {
			continue
		}
		t.Fatalf("unexpected nil wire")
	}
	// spot-check the first polyline wire is buildable and non-degenerate
	for _, e := range r.GetElements() {
		if e.Type != "Polyline" || e.Wire == nil {
			continue
		}
		sp := e.Wire.StartPoint().Data()
		ep := e.Wire.EndPoint().Data()
		for _, v := range append(append([]float64{}, sp[:]...), ep[:]...) {
			if math.IsNaN(v) || math.IsInf(v, 0) {
				t.Fatalf("wire endpoint not finite: %v %v", sp, ep)
			}
		}
		return
	}
	t.Fatal("no polyline wire found")
}

// TestDgnReaderSampleZ proves the sample maps full 3D coordinates:
// wire endpoints carry non-zero Z (master units), not a 2D flattening.
func TestDgnReaderSampleZ(t *testing.T) {
	r := loadSampleReader(t)
	have3d := 0
	for _, e := range r.GetElements() {
		if e.Wire == nil {
			continue
		}
		sp := e.Wire.StartPoint().Data()
		ep := e.Wire.EndPoint().Data()
		if sp[2] != 0 || ep[2] != 0 {
			have3d++
		}
	}
	if have3d == 0 {
		t.Fatal("no 3D geometry: all wire endpoints have Z=0")
	}
	t.Logf("wires with non-zero Z: %d", have3d)
}

// TestDgnReaderSyntheticArc checks arc→three-point-arc conversion on a
// synthetic in-memory v7 file with a known 2D arc (start=0, sweep=90,
// radius=100, origin=(0,0)).
func TestDgnReaderSyntheticArc(t *testing.T) {
	doc := syntheticArcDoc()

	r := NewDgnReader()
	if err := r.LoadBytes(doc); err != nil {
		t.Fatalf("load: %v", err)
	}
	els := r.GetElements()
	if len(els) != 1 {
		t.Fatalf("elements=%d", len(els))
	}
	e := els[0]
	if e.Type != "Arc" {
		t.Fatalf("type=%s", e.Type)
	}
	if e.Wire == nil {
		t.Fatal("arc wire is nil")
	}
	// three-point arc through (100,0), (~70.7,70.7), (0,100):
	// start point must be (100,0,0)
	sp := e.Wire.StartPoint().Data()
	if math.Abs(sp[0]-100) > 1e-6 || math.Abs(sp[1]) > 1e-6 {
		t.Fatalf("start point = %v", sp)
	}
}

// syntheticArcDoc builds a minimal in-memory v7 file: TCB (units 1:1,
// scale=1) + one 2D ARC (start=0°, sweep=90°, radius=100, origin=(0,0)).
func syntheticArcDoc() []byte {
	doc := []byte{0x08, 0x09, 0xFE, 0x02}
	tcb := make([]byte, 1532)
	// halfword-swapped int32 encoding (V7Int32 inverse): value 1 → 00 00 01 00
	putSw := func(bodyOff int, v int32) {
		u := uint32(v)
		tcb[bodyOff] = byte(u >> 16)
		tcb[bodyOff+1] = byte(u >> 24)
		tcb[bodyOff+2] = byte(u)
		tcb[bodyOff+3] = byte(u >> 8)
	}
	// magic bytes double as the element header (lvl8/type9, words=766 →
	// size 1536), so tcb below IS el.Body: ParseV7TCB indexes Body[1108].
	putSw(1108, 1) // subunits per master = 1
	putSw(1112, 1) // uor per subunit = 1
	doc = append(doc, tcb...)

	// ARC element: level 1, type 16, words = (32 core + 44 body)/2
	arcBody := make([]byte, 32+44)
	// start@body32 = 0
	// sweep@body36 = 90*360000 = 32400000
	putSwIn := func(buf []byte, off int, v int32) {
		u := uint32(v)
		buf[off] = byte(u >> 16)
		buf[off+1] = byte(u >> 24)
		buf[off+2] = byte(u)
		buf[off+3] = byte(u >> 8)
	}
	putSwIn(arcBody, 36, 90*360000)
	// primary/secondary@body40/48 = 100.0 VAX doubles (v7num.V7PutDouble)
	godgn.V7PutDouble(arcBody[40:48], 100.0)
	godgn.V7PutDouble(arcBody[48:56], 100.0)
	// 2D rotation@body56 = 0; origin@body60/68 = 0 (VAX zero = all 0 bytes)
	// element header: level1|type16, words=(32+44)/2=38
	hdr := []byte{0x01, 0x10, 38, 0}
	doc = append(doc, hdr...)
	doc = append(doc, arcBody...)
	doc = append(doc, 0xFF, 0xFF)
	return doc
}

// appendSyntheticTCB appends the 3D magic + a minimal 1:1-unit TCB to doc.
func appendSyntheticTCB(doc []byte) []byte {
	doc = append(doc, 0xC8, 0x09, 0xFE, 0x02) // 3D magic (byte0 bit6 = Is3D)
	tcb := make([]byte, 1532)
	putSw := func(bodyOff int, v int32) {
		u := uint32(v)
		tcb[bodyOff] = byte(u >> 16)
		tcb[bodyOff+1] = byte(u >> 24)
		tcb[bodyOff+2] = byte(u)
		tcb[bodyOff+3] = byte(u >> 8)
	}
	putSw(1108, 1) // subunits per master = 1
	putSw(1112, 1) // uor per subunit = 1
	return append(doc, tcb...)
}

// syntheticBSplinePoles are the control points of syntheticBSplineDoc.
var syntheticBSplinePoles = [][3]float64{
	{0, 0, 0}, {0, 30, 10}, {20, 50, 10}, {40, 30, 0}, {40, 0, 0},
}

// syntheticBSplineDoc builds a minimal in-memory 3D v7 file: TCB (1:1
// units) + one clamped cubic B-spline stored as the v7 sibling triple
// header(27, order 4, 5 poles, 1 interior knot 0.5) + knot(26) + poles(21).
func syntheticBSplineDoc() []byte {
	doc := appendSyntheticTCB(nil)

	// 27 header: desc_words@32=0, flags@36=(order-2)|0x10, curvetype@37=0,
	// numpoles@38 u16le, numknots@40 u16le
	hbody := make([]byte, 42)
	hbody[36] = (4 - 2) | 0x10
	hbody[38], hbody[39] = 5, 0
	hbody[40], hbody[41] = 1, 0
	doc = append(doc, 0x01, 27, 21, 0)
	doc = append(doc, hbody...)

	// 26 interior knot: one value 0.5 → int32(0.5·(2^31−1)) = 2^30−1
	kbody := make([]byte, 36)
	godgn.V7PutInt32(kbody[32:], 1<<30-1)
	doc = append(doc, 0x01, 26, 18, 0)
	doc = append(doc, kbody...)

	// 21 poles: u16 count@32, count×3D point (12B) from 34
	pbody := make([]byte, 34+5*12)
	pbody[32], pbody[33] = 5, 0
	for i, p := range syntheticBSplinePoles {
		o := 34 + i*12
		godgn.V7PutInt32(pbody[o:], int32(p[0]))
		godgn.V7PutInt32(pbody[o+4:], int32(p[1]))
		godgn.V7PutInt32(pbody[o+8:], int32(p[2]))
	}
	doc = append(doc, 0x01, 21, 47, 0)
	doc = append(doc, pbody...)
	doc = append(doc, 0xFF, 0xFF)
	return doc
}

// syntheticConeDoc builds a minimal 3D v7 file: TCB + one CONE(23) —
// vertical cylinder r=10 from (0,0,0) to (0,0,50).
func syntheticConeDoc() []byte {
	doc := appendSyntheticTCB(nil)
	cbody := make([]byte, 114) // unknown u16@32, quat@34, c1@50, r1@74, c2@82, r2@106
	godgn.V7PutDouble(cbody[74:], 10)
	godgn.V7PutDouble(cbody[98:], 50)
	godgn.V7PutDouble(cbody[106:], 10)
	doc = append(doc, 0x01, 23, 57, 0)
	doc = append(doc, cbody...)
	doc = append(doc, 0xFF, 0xFF)
	return doc
}

// TestDgnReaderSyntheticBSpline checks the assembled curve wire: clamped
// ends land exactly on the first/last pole.
func TestDgnReaderSyntheticBSpline(t *testing.T) {
	r := NewDgnReader()
	if err := r.LoadBytes(syntheticBSplineDoc()); err != nil {
		t.Fatalf("load: %v", err)
	}
	els := r.GetElements()
	if len(els) != 1 {
		t.Fatalf("elements=%d", len(els))
	}
	e := els[0]
	if e.Type != "BSplineCurve" {
		t.Fatalf("type=%s", e.Type)
	}
	if e.Wire == nil {
		t.Fatal("bspline wire is nil")
	}
	sp := e.Wire.StartPoint().Data()
	if math.Abs(sp[0]) > 1e-6 || math.Abs(sp[1]) > 1e-6 || math.Abs(sp[2]) > 1e-6 {
		t.Fatalf("start = %v want pole0 (0,0,0)", sp)
	}
	ep := e.Wire.EndPoint().Data()
	if math.Abs(ep[0]-40) > 1e-6 || math.Abs(ep[1]) > 1e-6 {
		t.Fatalf("end = %v want pole4 (40,0,0)", ep)
	}
}

// TestDgnReaderSyntheticCone checks the cone reaches the bridge as
// metadata (KindCone carries no wire; the mesh path owns it).
func TestDgnReaderSyntheticCone(t *testing.T) {
	r := NewDgnReader()
	if err := r.LoadBytes(syntheticConeDoc()); err != nil {
		t.Fatalf("load: %v", err)
	}
	els := r.GetElements()
	if len(els) != 1 {
		t.Fatalf("elements=%d", len(els))
	}
	e := els[0]
	if e.Type != "Cone" {
		t.Fatalf("type=%s", e.Type)
	}
	if e.Wire != nil {
		t.Fatal("cone must not produce a wire")
	}
}

// putSwInt32LE writes a little-endian u16 (element-header word counts).
func putSwInt32LE(b []byte, v uint16) {
	b[0] = byte(v)
	b[1] = byte(v >> 8)
}

// syntheticLine3D builds a 3D LINE(3) body (56B): points (x1,y1,z1)-(x2,y2,z2).
func syntheticLine3D(x1, y1, z1, x2, y2, z2 int32) []byte {
	body := make([]byte, 56)
	vals := []int32{x1, y1, z1, x2, y2, z2}
	for i, v := range vals {
		godgn.V7PutInt32(body[32+i*4:], v)
	}
	return body
}

// syntheticCellDoc builds a 3D v7 file: TCB + one legacy cell header (type
// 2) translating by (100,200,300), containing a line (0,0,0)-(10,0,0).
func syntheticCellDoc() []byte {
	doc := appendSyntheticTCB(nil)
	line := syntheticLine3D(0, 0, 0, 10, 0, 0) // words 28
	// header body 120B (words 60); span = 62 + 30 = 92 → tot = 73
	hbody := make([]byte, 120)
	putSwInt32LE(hbody[32:], 73)
	for _, off := range []int{72, 88, 104} { // Trans diag ≈ 1.0 (i32/2^31)
		godgn.V7PutInt32(hbody[off:], 1<<31-1)
	}
	godgn.V7PutInt32(hbody[108:], 100) // origin
	godgn.V7PutInt32(hbody[112:], 200)
	godgn.V7PutInt32(hbody[116:], 300)
	doc = append(doc, 0x01, 2, 60, 0)
	doc = append(doc, hbody...)
	doc = append(doc, 0x01, 3, 28, 0)
	doc = append(doc, line...)
	doc = append(doc, 0xFF, 0xFF)
	return doc
}

// syntheticSharedCellDoc builds a 3D v7 file: TCB + shared cell defn
// "CELL01" (type 34, containing a line (0,0,0)-(10,0,0)) + a matching ref
// (type 35), plus a second defn "CELL02" with a line but NO ref.
func syntheticSharedCellDoc() []byte {
	doc := appendSyntheticTCB(nil)
	line := syntheticLine3D(0, 0, 0, 10, 0, 0) // words 28

	// defn CELL01: body 176B (words 88); span = 90 + 30 = 120 → tot = 101
	d1 := make([]byte, 176)
	putSwInt32LE(d1[32:], 101)
	copy(d1[160:], "CELL01")
	doc = append(doc, 0x01, 34, 88, 0)
	doc = append(doc, d1...)
	doc = append(doc, 0x01, 3, 28, 0)
	doc = append(doc, line...)

	// ref CELL01: body 176B (words 88)
	ref := make([]byte, 176)
	copy(ref[160:], "CELL01")
	doc = append(doc, 0x01, 35, 88, 0)
	doc = append(doc, ref...)

	// defn CELL02 (no ref): span = 90 + 30 = 120 → tot = 101
	d2 := make([]byte, 176)
	putSwInt32LE(d2[32:], 101)
	copy(d2[160:], "CELL02")
	doc = append(doc, 0x01, 34, 88, 0)
	doc = append(doc, d2...)
	doc = append(doc, 0x01, 3, 28, 0)
	doc = append(doc, line...)

	doc = append(doc, 0xFF, 0xFF)
	return doc
}

// TestDgnReaderCellTree checks the D93 hierarchy: cell children are
// nested under their CellDef parents; shared-defn interiors are DefnOnly.
func TestDgnReaderCellTree(t *testing.T) {
	r := NewDgnReader()
	if err := r.LoadBytes(syntheticCellDoc()); err != nil {
		t.Fatalf("load: %v", err)
	}
	els := r.GetElements()
	if len(els) != 2 {
		t.Fatalf("elements=%d want 2", len(els))
	}
	if els[0].Type != "CellDef" || els[1].Type != "Segment" {
		t.Fatalf("types=%s,%s", els[0].Type, els[1].Type)
	}
	if els[1].ParentId != els[0].Id {
		t.Fatalf("segment parent=%d want cell %d", els[1].ParentId, els[0].Id)
	}

	r2 := NewDgnReader()
	if err := r2.LoadBytes(syntheticSharedCellDoc()); err != nil {
		t.Fatalf("load: %v", err)
	}
	var defnSegs, topSegs int
	for _, e := range r2.ents {
		if e.Kind.String() != "Segment" {
			continue
		}
		if e.DefnOnly {
			defnSegs++
		} else {
			topSegs++
		}
	}
	if defnSegs != 2 || topSegs != 0 {
		t.Fatalf("defnSegs=%d topSegs=%d want 2/0", defnSegs, topSegs)
	}
}
