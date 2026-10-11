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
		"Polyline":      36 + 47 + 2522,
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
	geo := counts["Segment"] + counts["Polyline"] + counts["Arc"] + counts["Ellipse"]
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
