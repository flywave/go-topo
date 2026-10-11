package topo

import (
	"math"
	"os"
	"path/filepath"
	"testing"
)

// TestDgnToMstSample converts the 16MB v7 sample and locks the mesh
// golden: one mesh, one outline node per wire-bearing element (8742 =
// Segment 5814 + Polyline 2605 + Arc 317 + Ellipse 6, matching the
// DgnReader census) with consecutive-index edge pairs.
func TestDgnToMstSample(t *testing.T) {
	if _, err := os.Stat(samplePath); err != nil {
		t.Skipf("sample absent: %v", err)
	}
	meshes, err := DgnToMst(samplePath)
	if err != nil {
		t.Fatalf("DgnToMst: %v", err)
	}
	if len(meshes) != 1 {
		t.Fatalf("meshes=%d want 1", len(meshes))
	}
	m := meshes[0]
	if len(m.Nodes) != 8742 {
		t.Fatalf("nodes=%d want 8742", len(m.Nodes))
	}
	if len(m.Materials) != 1 {
		t.Errorf("materials=%d want 1 (default white)", len(m.Materials))
	}
	totalVerts, totalEdges, arcNodes := 0, 0, 0
	for i, nd := range m.Nodes {
		if len(nd.Vertices) < 2 {
			t.Fatalf("node %d: vertices=%d", i, len(nd.Vertices))
		}
		if len(nd.EdgeGroup) != 1 {
			t.Fatalf("node %d: edge groups=%d", i, len(nd.EdgeGroup))
		}
		eg := nd.EdgeGroup[0]
		if eg.Batchid != 0 {
			t.Errorf("node %d: batchid=%d want 0", i, eg.Batchid)
		}
		if len(eg.Edges) != len(nd.Vertices)-1 {
			t.Fatalf("node %d: edges=%d vertices=%d", i, len(eg.Edges), len(nd.Vertices))
		}
		for j, e := range eg.Edges {
			if e[0] != uint32(j) || e[1] != uint32(j+1) {
				t.Fatalf("node %d edge %d = %v want [%d %d]", i, j, e, j, j+1)
			}
		}
		for _, v := range nd.Vertices {
			if math.IsNaN(float64(v[0])) || math.IsInf(float64(v[0]), 0) {
				t.Fatalf("node %d: non-finite vertex %v", i, v)
			}
		}
		// arc/ellipse nodes are capped at 256 segments (257 vertices) by
		// arcSegments; polylines are unbounded — cap checked in
		// TestArcSegments / TestDgnToMstSyntheticArc instead.
		if len(nd.Vertices) > 64 { // tessellation heuristic for the log
			arcNodes++
		}
		totalVerts += len(nd.Vertices)
		totalEdges += len(eg.Edges)
	}
	t.Logf("nodes=%d verts=%d edges=%d arcs>64seg=%d",
		len(m.Nodes), totalVerts, totalEdges, arcNodes)
	// deterministic tessellation goldens (DefaultArcEpsilon = 0.1;
	// bspline curves sampled via de Boor, n = clamp(2·poles, 16, 128))
	if totalVerts != 202059 || totalEdges != 193317 {
		t.Errorf("verts/edges = %d/%d want 202059/193317", totalVerts, totalEdges)
	}
}

// TestDgnToMstSyntheticArc checks the §6.4 subdivision on the known
// synthetic arc (sweep=90°, r=100, eps=0.1):
//
//	step = 2*acos(1-eps/r) = 2*acos(0.999) → n = ceil((π/2)/step) = 18
//	segments, 19 vertices, first (100,0,0), last (0,100,0).
func TestDgnToMstSyntheticArc(t *testing.T) {
	path := filepath.Join(t.TempDir(), "arc.dgn")
	if err := os.WriteFile(path, syntheticArcDoc(), 0o644); err != nil {
		t.Fatal(err)
	}
	meshes, err := DgnToMst(path)
	if err != nil {
		t.Fatalf("DgnToMst: %v", err)
	}
	if len(meshes) != 1 || len(meshes[0].Nodes) != 1 {
		t.Fatalf("meshes/nodes wrong: %d/%d", len(meshes), len(meshes[0].Nodes))
	}
	nd := meshes[0].Nodes[0]
	if got, want := len(nd.Vertices), 19; got != want {
		t.Fatalf("vertices=%d want %d", got, want)
	}
	if got, want := len(nd.EdgeGroup[0].Edges), 18; got != want {
		t.Fatalf("edges=%d want %d", got, want)
	}
	first := nd.Vertices[0]
	if math.Abs(float64(first[0])-100) > 1e-4 || math.Abs(float64(first[1])) > 1e-4 {
		t.Errorf("first vertex = %v want (100,0)", first)
	}
	last := nd.Vertices[len(nd.Vertices)-1]
	if math.Abs(float64(last[0])) > 1e-4 || math.Abs(float64(last[1])-100) > 1e-4 {
		t.Errorf("last vertex = %v want (0,100)", last)
	}
}

// TestArcSegments covers the subdivision count clamp and math edges.
func TestArcSegments(t *testing.T) {
	cases := []struct {
		sweep, r, eps float64
		want          int
	}{
		{90, 100, 0.1, 18},  // ceil((π/2)/(2*acos(0.999)))
		{360, 100, 0.1, 71}, // full circle
		{360, 1e9, 0.1, 256},
		{90, 0.001, 0.1, 3}, // eps > r → clamp floor
		{-90, 100, 0.1, 18}, // sign-agnostic
		{0, 100, 0.1, 3},    // degenerate sweep → floor
	}
	for _, c := range cases {
		if got := arcSegments(c.sweep, c.r, c.eps); got != c.want {
			t.Errorf("arcSegments(%v,%v,%v)=%d want %d",
				c.sweep, c.r, c.eps, got, c.want)
		}
	}
}

// TestDgnToMstBSplineEndpoints checks de Boor sampling of the synthetic
// clamped cubic: n = clamp(2·5,16,128) = 16 segments → 17 vertices,
// first/last exactly on the clamped poles.
func TestDgnToMstBSplineEndpoints(t *testing.T) {
	path := filepath.Join(t.TempDir(), "spline.dgn")
	if err := os.WriteFile(path, syntheticBSplineDoc(), 0o644); err != nil {
		t.Fatal(err)
	}
	meshes, err := DgnToMst(path)
	if err != nil {
		t.Fatalf("DgnToMst: %v", err)
	}
	if len(meshes) != 1 || len(meshes[0].Nodes) != 1 {
		t.Fatalf("meshes/nodes wrong: %d/%d", len(meshes), len(meshes[0].Nodes))
	}
	nd := meshes[0].Nodes[0]
	if got, want := len(nd.Vertices), 17; got != want {
		t.Fatalf("vertices=%d want %d", got, want)
	}
	if got, want := len(nd.EdgeGroup[0].Edges), 16; got != want {
		t.Fatalf("edges=%d want %d", got, want)
	}
	first := nd.Vertices[0]
	last := nd.Vertices[len(nd.Vertices)-1]
	if math.Abs(float64(first[0])) > 1e-4 || math.Abs(float64(first[1])) > 1e-4 {
		t.Errorf("first vertex = %v want pole0 (0,0)", first)
	}
	if math.Abs(float64(last[0])-40) > 1e-4 || math.Abs(float64(last[1])) > 1e-4 {
		t.Errorf("last vertex = %v want pole4 (40,0)", last)
	}
	// the curve must lift off the control polygon mid-span (pole1 y=30)
	mid := nd.Vertices[len(nd.Vertices)/2]
	if mid[1] < 15 {
		t.Errorf("mid vertex %v too flat — sampling the control polygon?", mid)
	}
}

// TestDgnToMstCone checks the frustum triangulation: vertical cylinder
// r=10 h=50 → 68 vertices (two 33-vertex seam rings + 2 centers),
// 128 faces (64 side + 2×32 cap fans).
func TestDgnToMstCone(t *testing.T) {
	path := filepath.Join(t.TempDir(), "cone.dgn")
	if err := os.WriteFile(path, syntheticConeDoc(), 0o644); err != nil {
		t.Fatal(err)
	}
	meshes, err := DgnToMst(path)
	if err != nil {
		t.Fatalf("DgnToMst: %v", err)
	}
	if len(meshes) != 1 || len(meshes[0].Nodes) != 1 {
		t.Fatalf("meshes/nodes wrong: %d/%d", len(meshes), len(meshes[0].Nodes))
	}
	nd := meshes[0].Nodes[0]
	if got, want := len(nd.Vertices), 68; got != want {
		t.Fatalf("vertices=%d want %d", got, want)
	}
	if len(nd.FaceGroup) != 1 {
		t.Fatalf("face groups=%d want 1", len(nd.FaceGroup))
	}
	faces := nd.FaceGroup[0].Faces
	if got, want := len(faces), 128; got != want {
		t.Fatalf("faces=%d want %d", got, want)
	}
	for i, f := range faces {
		for _, v := range f.Vertex {
			if int(v) >= len(nd.Vertices) {
				t.Fatalf("face %d references vertex %d (have %d)", i, v, len(nd.Vertices))
			}
		}
	}
	// side ring vertices lie on the r=10 circles around the z axis
	for i := 0; i < 33; i++ {
		v := nd.Vertices[i]
		rad := math.Hypot(float64(v[0]), float64(v[1]))
		if math.Abs(rad-10) > 1e-3 {
			t.Fatalf("ring1 vertex %d radius %v want 10", i, rad)
		}
		if math.Abs(float64(v[2])) > 1e-6 {
			t.Fatalf("ring1 vertex %d z=%v want 0", i, v[2])
		}
	}
}
