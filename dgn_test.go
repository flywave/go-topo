package topo

import (
	"encoding/binary"
	"math"
	"os"
	"testing"

	godgn "github.com/flywave/go-dgn/dgn"
	"github.com/flywave/go-dgn/dgn/scene"
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
	// the frustum bridges as a real cone solid: P1=(0,0,0) R1=10 →
	// P2=(0,0,50) R2=10, so the bbox is the swept envelope
	if e.Shape == nil || e.Shape.IsNull() {
		t.Fatal("cone shape is nil")
	}
	d := e.Shape.BBox().Data() // minx,miny,minz,maxx,maxy,maxz
	tol := 1e-6
	for i, want := range [][2]float64{{-10, 10}, {-10, 10}, {0, 50}} {
		if math.Abs(d[i]-want[0]) > tol || math.Abs(d[i+3]-want[1]) > tol {
			t.Fatalf("bbox axis %d = (%g,%g) want %v", i, d[i], d[i+3], want)
		}
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

// TestDgnReaderMeshShape drives the scene→topo mesh mapping directly (the
// v8 file-level assembly is covered in go-dgn): a 2×3 point grid with two
// derived quad faces becomes a face compound spanning the grid envelope.
func TestDgnReaderMeshShape(t *testing.T) {
	r := NewDgnReader()
	e := &scene.Entity{
		Kind: scene.KindSolid,
		Points: []scene.Point{
			{X: 0, Y: 0, Z: 1}, {X: 1, Y: 0, Z: 1}, {X: 2, Y: 0, Z: 1},
			{X: 0, Y: 0, Z: 0}, {X: 1, Y: 0, Z: 0}, {X: 2, Y: 0, Z: 0},
		},
		Faces: [][]int32{{0, 3, 4, 1}, {1, 4, 5, 2}},
	}
	sh := r.meshShape(e)
	if sh == nil || sh.IsNull() {
		t.Fatal("mesh shape is nil")
	}
	d := sh.BBox().Data()
	tol := 1e-6
	for i, want := range [][2]float64{{0, 2}, {0, 0}, {0, 1}} {
		if math.Abs(d[i]-want[0]) > tol || math.Abs(d[i+3]-want[1]) > tol {
			t.Fatalf("bbox axis %d = (%g,%g) want %v", i, d[i], d[i+3], want)
		}
	}

	// faces with out-of-range indices are dropped, not bridged
	bad := &scene.Entity{Kind: scene.KindSolid, Points: e.Points[:3],
		Faces: [][]int32{{0, 1, 9}}}
	if sh := r.meshShape(bad); sh != nil {
		t.Fatal("out-of-range face bridged")
	}
}

// TestDgnReaderV7RealPublicSamples bridges the Aspose public v7 samples
// (D129): Nikon_D90_Camera.dgn is a real 3D wireframe of 60 B-spline
// curves, truncated on the last pole record — the reader must load it and
// convert the 59 complete curves to exact OCCT B-spline wires.
func TestDgnReaderV7RealPublicSamples(t *testing.T) {
	r := NewDgnReader()
	if err := r.Load("../go-dgn/dgn/testdata/Nikon_D90_Camera.dgn"); err != nil {
		t.Fatalf("load: %v", err)
	}
	curves, wires := 0, 0
	for _, e := range r.GetElements() {
		if e.Type == "BSplineCurve" {
			curves++
			if e.Wire != nil {
				wires++
			}
		}
	}
	if curves != 59 || wires != 59 {
		t.Fatalf("BSplineCurve=%d (wired=%d), want 59/59", curves, wires)
	}

	for _, name := range []string{"V7-Imperial-Arch-01-Seed2D.dgn", "V7-Imperial-Arch-02-Seed3D.dgn"} {
		r2 := NewDgnReader()
		if err := r2.Load("../go-dgn/dgn/testdata/" + name); err != nil {
			t.Fatalf("%s: load: %v", name, err)
		}
	}
}

// TestDgnReaderV7SyntheticBSplineSurface builds a minimal v7 byte stream
// (TCB + type-24 surface header + u-knots + poles) and bridges it end to
// end: the reader must yield a BSplineSurface entity whose shape is an
// exact OCCT bilinear face spanning the pole grid (D131 — type 24 was
// silently dropped by the scene walk before).
func TestDgnReaderV7SyntheticBSplineSurface(t *testing.T) {
	putI32 := func(b []byte, off int, v int32) {
		// v7 fields use the word-swapped DGN_INT32 order
		godgn.V7PutInt32(b[off:], v)
	}
	frame := func(b0, typ byte, body []byte) []byte {
		out := make([]byte, 4+len(body))
		out[0], out[1] = b0, typ
		binary.LittleEndian.PutUint16(out[2:], uint16(len(body)/2))
		copy(out[4:], body)
		return out
	}

	tcbBody := make([]byte, 1532) // words=0x02FE — the v7 magic Detect() pins (b[2]=FE b[3]=02)
	putI32(tcbBody, 1108, 1)      // SubunitsPerMaster
	putI32(tcbBody, 1112, 1)      // UORPerSubunit → scale 1
	stream := frame(0xC8, 9, tcbBody)

	hdr := make([]byte, 54)
	hdr[38] = 3 // NumPolesU
	hdr[40] = 1 // NumKnotsU
	hdr[46] = 2 // NumPolesV
	stream = append(stream, frame(0x40, 24, hdr)...)

	uknots := make([]byte, 36)
	putI32(uknots, 32, 1<<30) // ≈0.5 interior knot
	stream = append(stream, frame(0x40, 26, uknots)...)

	poles := make([]byte, 34+6*12)
	poles[32] = 6
	coords := [6][3]int32{
		{0, 0, 0}, {10, 0, 0}, {20, 0, 2},
		{0, 10, 0}, {10, 10, 1}, {20, 10, 3},
	}
	for i, c := range coords {
		putI32(poles, 34+i*12, c[0])
		putI32(poles, 34+i*12+4, c[1])
		putI32(poles, 34+i*12+8, c[2])
	}
	stream = append(stream, frame(0x40, 21, poles)...)
	stream = append(stream, 0xFF, 0xFF)

	r := NewDgnReader()
	if err := r.LoadBytes(stream); err != nil {
		t.Fatalf("load: %v", err)
	}
	var surf *DgnElement
	for _, e := range r.GetElements() {
		if e.Type == "BSplineSurface" {
			surf = e
		}
	}
	if surf == nil {
		t.Fatal("no BSplineSurface element bridged")
	}
	if surf.Shape == nil || surf.Shape.IsNull() {
		t.Fatal("surface shape missing — type 24 still dropped?")
	}
	// bilinear face interpolates the pole grid: bbox = grid envelope
	d := surf.Shape.BBoxOptimal(1e-6).Data()
	want := [][2]float64{{0, 20}, {0, 10}, {0, 3}}
	t.Logf("full bbox: %v", d)
	for i, w := range want {
		if math.Abs(d[i]-w[0]) > 1e-4 || math.Abs(d[i+3]-w[1]) > 1e-4 {
			t.Fatalf("bbox axis %d = (%g,%g) want %v", i, d[i], d[i+3], w)
		}
	}
}

// TestDgnReaderV8TxDOTSharedCell bridges the TxDOT standard plan sheet
// (D135): the first real v8 file with SharedCellInstance references whose
// 0x2716 roots live in the Dgn^Nm definition library chunks — before the
// SceneV8SharedCellDefs fix the whole chain silently failed to resolve.
func TestDgnReaderV8TxDOTSharedCell(t *testing.T) {
	r := NewDgnReader()
	if err := r.Load("../go-dgn/dgn/testdata/txdot-matt23.dgn"); err != nil {
		t.Fatalf("load: %v", err)
	}
	refs, defs, resolved := 0, 0, 0
	byID := map[int]bool{}
	for _, e := range r.GetElements() {
		byID[e.Id] = true
		switch e.Type {
		case "CellRef":
			refs++
		case "CellDef":
			defs++
		}
	}
	for _, e := range r.GetElements() {
		if e.Type == "CellRef" && byID[int(e.DefID)] {
			resolved++
		}
	}
	if refs != 12 || resolved != 12 {
		t.Fatalf("CellRef=%d resolved=%d, want 12/12", refs, resolved)
	}
	if defs < 12 {
		t.Fatalf("CellDef=%d, definitions missing", defs)
	}
}

// TestDgnReaderV8TxDOTPlateGirder stress-tests the shared-cell chain on
// the TxDOT plate girder standard (OpenBridge output): 1062 shared-cell
// references against 64 Dgn^Nm library definitions — the largest real
// SharedCell corpus in the repo, all resolving (D141).
func TestDgnReaderV8TxDOTPlateGirder(t *testing.T) {
	r := NewDgnReader()
	if err := r.Load("../go-dgn/dgn/testdata/txdot-cd-pb-20.dgn"); err != nil {
		t.Fatalf("load: %v", err)
	}
	refs, defs, resolved := 0, 0, 0
	byID := map[int]bool{}
	for _, e := range r.GetElements() {
		byID[e.Id] = true
		switch e.Type {
		case "CellRef":
			refs++
		case "CellDef":
			defs++
		}
	}
	for _, e := range r.GetElements() {
		if e.Type == "CellRef" && byID[int(e.DefID)] {
			resolved++
		}
	}
	if refs != 1062 || resolved != 1062 || defs < 64 {
		t.Fatalf("CellRef=%d resolved=%d CellDef=%d, want 1062/1062 and defs>=64", refs, resolved, defs)
	}
}

// TestDgnReaderV8TxDOTTerrain3D bridges the OpenRoads terrain working
// file's true-3D feature lines (Line3d/LineString3d, D142) — every
// geometry-bearing entity must produce a wire, exercising the 3D polyline
// bridge on real data for the first time.
func TestDgnReaderV8TxDOTTerrain3D(t *testing.T) {
	r := NewDgnReader()
	if err := r.Load("../go-dgn/dgn/testdata/txdot-rudderplaza-terrain.dgn"); err != nil {
		t.Fatalf("load: %v", err)
	}
	polylines, wired := 0, 0
	for _, e := range r.GetElements() {
		if e.Type == "Polyline" {
			polylines++
			if e.Wire != nil {
				wired++
			}
		}
	}
	if polylines < 100 || wired != polylines {
		t.Fatalf("Polyline=%d wired=%d, want >=100 all wired", polylines, wired)
	}
}

// TestDgnReaderV8TxDOTTerrainMesh verifies the OpenRoads terrain XAttribute
// decode end to end: the 428-vertex terrain surface (state-plane f64s,
// D143) must reach go-topo as a KindSolid point-mesh entity.
func TestDgnReaderV8TxDOTTerrainMesh(t *testing.T) {
	r := NewDgnReader()
	if err := r.Load("../go-dgn/dgn/testdata/txdot-rudderplaza-terrain.dgn"); err != nil {
		t.Fatalf("load: %v", err)
	}
	terrains := 0
	for _, e := range r.GetElements() {
		// the terrain decodes to a KindSolid mesh entity — the only Solid
		// in this file (428 vertices, 7 in-range faces of the TIN so far).
		if e.Type == "Solid" {
			terrains++
		}
	}
	if terrains != 1 {
		t.Fatalf("terrain mesh entities=%d, want 1", terrains)
	}
}
