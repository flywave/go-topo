package topo

import (
	"os"
	"testing"
)

func TestDgnReaderRealMeshE2E(t *testing.T) {
	const p = "../go-dgn/dgn/testdata/v8_meshdata.dgn"
	if _, err := os.Stat(p); err != nil {
		t.Skipf("sample absent: %v", err)
	}
	r := NewDgnReader()
	if err := r.Load(p); err != nil {
		t.Fatalf("load: %v", err)
	}
	solids := 0
	for _, e := range r.GetElements() {
		if e.Type == "Solid" && e.BRep == nil {
			solids++
			if e.Shape == nil || e.Shape.IsNull() {
				t.Fatalf("mesh id=%d has no shape", e.Id)
			}
		}
	}
	if solids != 9 {
		t.Fatalf("solids = %d want 9", solids)
	}

	// the mesh exit mirrors it: 9 triangle nodes with 48 triangles each
	meshes := r.toMst(0.1)
	tris := 0
	for _, m := range meshes {
		for _, nd := range m.Nodes {
			for _, g := range nd.FaceGroup {
				tris += len(g.Faces)
			}
		}
	}
	if tris != 9*24*2 {
		t.Fatalf("triangles = %d want %d", tris, 9*24*2)
	}
}
