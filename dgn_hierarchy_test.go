package topo

import (
	"testing"

	"github.com/flywave/go-dgn/dgn/scene"
)

// TestDgnHierarchySample locks the complex-group / cell hierarchy of the
// v7 sample against the bridge contract (topo-bridge.md §6.5):
//   - every ParentId > 0 resolves to an existing element whose kind is
//     ComplexHeader (complex group) or CellDef (cell header children)
//   - CellDef / CellRef elements carry their names; cell headers carry a
//     placement Transform (shared-cell defns type-34 do not)
//
// The sample census (D86/D88 golden): ComplexHeader 19, CellDef 338
// (223 type-2 headers + 115 type-34 defns), CellRef 39.
func TestDgnHierarchySample(t *testing.T) {
	r := loadSampleReader(t)
	els := r.GetElements()

	byID := make(map[int]*DgnElement, len(els))
	for _, e := range els {
		byID[e.Id] = e
	}

	children := 0
	parentKinds := map[string]int{}
	for _, e := range els {
		if e.ParentId == 0 {
			continue
		}
		children++
		p, ok := byID[e.ParentId]
		if !ok {
			t.Fatalf("element %d (type %s): missing parent %d", e.Id, e.Type, e.ParentId)
		}
		parentKinds[p.Type]++
		switch p.Type {
		case "ComplexHeader", "CellDef":
		default:
			t.Errorf("element %d: parent %d has kind %s (want ComplexHeader/CellDef)",
				e.Id, e.ParentId, p.Type)
		}
	}
	if children == 0 {
		t.Fatal("no elements with ParentId > 0 — grouping broken")
	}
	if children != 56 {
		t.Errorf("children=%d want 56 (sample grouping golden)", children)
	}
	t.Logf("children=%d parentKinds=%v", children, parentKinds)

	// cell kinds: names and placement transforms
	cellDefs, cellRefs := 0, 0
	namedDefs, namedRefs, defsXform := 0, 0, 0
	for _, e := range els {
		switch e.Type {
		case "CellDef":
			cellDefs++
			if e.Name != "" {
				namedDefs++
			}
			if e.Transform != nil {
				defsXform++
			}
		case "CellRef":
			cellRefs++
			if e.Name != "" {
				namedRefs++
			}
		}
	}
	if cellDefs != 338 {
		t.Errorf("CellDef=%d want 338", cellDefs)
	}
	if cellRefs != 39 {
		t.Errorf("CellRef=%d want 39", cellRefs)
	}
	if namedDefs != cellDefs {
		t.Errorf("named CellDef=%d want %d", namedDefs, cellDefs)
	}
	if namedRefs != cellRefs {
		t.Errorf("named CellRef=%d want %d", namedRefs, cellRefs)
	}
	// type-2 cell headers carry the placement; type-34 shared defns don't
	if defsXform != 223 {
		t.Errorf("CellDef with Transform=%d want 223 (type-2 headers)", defsXform)
	}
	t.Logf("cellDefs=%d (withTransform=%d) cellRefs=%d", cellDefs, defsXform, cellRefs)
}

// TestDgnSetUnitsScalePoint documents the v8 unit-injection contract
// (topo-bridge.md §6.3): SetUnits(uorPerMaster) divides raw UOR by the
// factor; unset (0) leaves raw UOR untouched. Full-file v8 goldens wait
// for a real sample (U10/v8 样例固化).
func TestDgnSetUnitsScalePoint(t *testing.T) {
	r := NewDgnReader()
	p := scene.Point{X: 2000, Y: 3000, Z: 4000}
	if got := r.scalePoint(p); got != [3]float64{2000, 3000, 4000} {
		t.Fatalf("unset units: %v want raw UOR", got)
	}
	r.SetUnits(1000)
	if got := r.scalePoint(p); got != [3]float64{2, 3, 4} {
		t.Fatalf("units=1000: %v want (2,3,4)", got)
	}
}
