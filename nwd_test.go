package topo

import (
	"os"
	"testing"
)

// Real-sample NWD bridge test. The 25 MB sample lives in the sibling
// go-nwd repo; the test is skipped when absent.
const nwdSample = "../go-nwd/nwd/testdata/BCCCH_BIM Coordination Model_251024.nwd"

func TestNwdReaderRealSample(t *testing.T) {
	if _, err := os.Stat(nwdSample); err != nil {
		t.Skipf("real NWD sample not present: %v", err)
	}
	r := NewNwdReader()
	if err := r.Load(nwdSample); err != nil {
		t.Fatalf("Load: %v", err)
	}
	md := r.Model()
	if md == nil || md.Version != 8 || len(md.Streams) != 27 {
		t.Fatalf("metadata=%+v", md)
	}
	if root := r.PartitionRoot(); root == nil || root.ClassName != "LcOaPartition" {
		t.Errorf("partition root=%+v", root)
	}
	if len(r.PropertyNames()) < 100 {
		t.Errorf("property names=%d want >=100", len(r.PropertyNames()))
	}

	els := r.GetElements()
	if len(els) < 1000 {
		t.Fatalf("elements=%d want >=1000", len(els))
	}
	total := 0
	shaped := 0
	var tri, line, point int
	for _, e := range els {
		total += e.VertexCount
		if e.Shape != nil {
			shaped++
		}
		switch e.ElementType {
		case 94:
			tri++
		case 95:
			line++
		case 96:
			point++
		}
	}
	if total < 100000 {
		t.Errorf("total vertices=%d want >=100000", total)
	}
	// Line sets bridge to edge compounds; triangles wait on U21.
	if line == 0 || shaped == 0 {
		t.Errorf("line=%d shaped=%d (want >0)", line, shaped)
	}
	t.Logf("elements=%d vertices=%d shaped=%d triangle=%d line=%d point=%d",
		len(els), total, shaped, tri, line, point)
}

func TestNwdReaderTriangleSoup(t *testing.T) {
	if _, err := os.Stat(nwdSample); err != nil {
		t.Skipf("real NWD sample not present: %v", err)
	}
	r := NewNwdReader()
	r.SetTriangleSoup(true)
	if err := r.Load(nwdSample); err != nil {
		t.Fatalf("Load: %v", err)
	}
	built := 0
	for _, e := range r.GetElements() {
		if e.TriangleCount > 0 {
			built++
		}
	}
	// Best-effort soup only; must not panic and should build some faces
	// for the fraction of triangle blocks with vertex counts %3==0.
	t.Logf("triangle-soup blocks with faces: %d", built)
}
