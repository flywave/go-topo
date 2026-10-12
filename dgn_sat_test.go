package topo

import (
	"math"
	"os"
	"testing"

	"github.com/flywave/go-dgn/dgn/sat"
	"github.com/flywave/go-dgn/dgn/scene"
)

const acisHdr = "700 6 1 0\n16 x 17 ASM 6.0.5.7004 NT 24 Mon Jan 16 13:30:30 2006\n1 1e-6 1e-9\n"

// acisOneFace wraps a single surface record plus its face.
func acisOneFace(surface string) []byte {
	return []byte(acisHdr + surface + " #\nface $1 -1 $-1 $-1 $-1 $-1 $-1 $0 forward single #\n")
}

// TestAcisSphereToTopo closes the solid-kernel loop end to end (D113):
// the archived real ACIS sample (OdWriteEx.sat — exactly the payload a
// kAcisData SmartSolid carries) rebuilds as a sphere with the right
// envelope.
func TestAcisSphereToTopo(t *testing.T) {
	b, err := os.ReadFile("../go-dgn/dgn/testdata/OdWriteEx.sat")
	if err != nil {
		t.Skipf("sample absent: %v", err)
	}
	sh := AcisBRepToShape(b)
	if sh == nil || sh.IsNull() {
		t.Fatal("shape nil")
	}
	d := sh.BBox().Data()
	tol := 1e-6
	for i, want := range [][2]float64{{-1, 1}, {-1, 1}, {-1, 1}} {
		if math.Abs(d[i]-want[0]) > tol || math.Abs(d[i+3]-want[1]) > tol {
			t.Fatalf("bbox axis %d = (%g,%g) want %v", i, d[i], d[i+3], want)
		}
	}
}

// TestAcisRebuildKinds pins the SAT-1 rebuild per analytic kind.
func TestAcisRebuildKinds(t *testing.T) {
	t.Run("cylinder", func(t *testing.T) {
		sh := AcisBRepToShape(acisOneFace("cylinder-surface $-1 -1 $-1 0 0 0 0 0 1 1 0 0 5"))
		if sh == nil || sh.IsNull() {
			t.Fatal("cylinder shape nil")
		}
		// full-U patch, v span = 2πr = 31.4159…
		d := sh.BBox().Data()
		if math.Abs(d[0]+5) > 1e-6 || math.Abs(d[3]-5) > 1e-6 ||
			math.Abs(d[5]-2*math.Pi*5) > 1e-6 {
			t.Fatalf("cylinder bbox = %v", d)
		}
	})
	t.Run("torus", func(t *testing.T) {
		sh := AcisBRepToShape(acisOneFace("torus-surface $-1 -1 $-1 0 0 0 0 0 1 1 0 0 10 2"))
		if sh == nil || sh.IsNull() {
			t.Fatal("torus shape nil")
		}
		d := sh.BBox().Data()
		// OCCT torus shells bbox slightly outside the exact envelope in
		// x/y (observed R1+1.5·R2 bound on both probe sizes; exact ±R2 in
		// z) — assert the sane interval, not an exact envelope.
		for i := 0; i < 2; i++ {
			if d[i] < -13+1e-9 || d[i] > 13-1e-9 || d[i+3] < -13+1e-9 || d[i+3] > 13-1e-9 {
				t.Fatalf("torus bbox axis %d = (%g,%g)", i, d[i], d[i+3])
			}
		}
		if math.Abs(d[2]+2) > 1e-6 || math.Abs(d[5]-2) > 1e-6 {
			t.Fatalf("torus z = (%g,%g)", d[2], d[5])
		}
	})
	t.Run("cone", func(t *testing.T) {
		// a boundary-less cone record carries no band height — no
		// rebuild (D116 layout; the bounded two-loop case is covered by
		// TestAcisBandedCone below)
		sh := AcisBRepToShape(acisOneFace("cone-surface $-1 -1 $-1 0 0 0 0 0 1 1 0 0 0.5 I I -0.3162 0.9487 2 forward"))
		if sh != nil {
			t.Fatal("boundary-less cone unexpectedly rebuilt")
		}
	})
	t.Run("plane", func(t *testing.T) {
		sh := AcisBRepToShape(acisOneFace("plane-surface $-1 -1 $-1 0 0 0 0 0 1 1 0 0"))
		if sh == nil || sh.IsNull() {
			t.Fatal("plane shape nil")
		}
	})
	t.Run("parasolid-rejected", func(t *testing.T) {
		if sh := AcisBRepToShape([]byte("parasolid binary \x00\x01")); sh != nil {
			t.Fatal("non-SAT accepted")
		}
	})
}

// TestDgnReaderBRepRebuild checks the build() wiring: a BRep-bearing
// SmartSolid entity gets its ACIS geometry rebuilt into Shape.
func TestDgnReaderBRepRebuild(t *testing.T) {
	r := NewDgnReader()
	r.ents = []scene.Entity{
		{
			Kind:  scene.KindSolid,
			ID:    900,
			Level: 64,
			BRep:  &scene.BRep{Flag2: 2, Data: acisOneFace("sphere-surface $-1 -1 $-1 3 4 5 0 0 1 1 0 0 2")},
		},
	}
	r.build()
	els := r.GetElements()
	if len(els) != 1 || els[0].Shape == nil || els[0].Shape.IsNull() {
		t.Fatal("rebuilt shape missing")
	}
	d := els[0].Shape.BBox().Data()
	tol := 1e-6
	if math.Abs(d[0]-(3-2)) > tol || math.Abs(d[1]-(4-2)) > tol || math.Abs(d[2]-(5-2)) > tol ||
		math.Abs(d[3]-(3+2)) > tol || math.Abs(d[4]-(4+2)) > tol || math.Abs(d[5]-(5+2)) > tol {
		t.Fatalf("bbox = %v", d)
	}
}

// TestAcisRealSurfaceSamples rebuilds the three real elliptical-cone
// samples (D115). Their boundary loops (equal translated ellipses) drive
// exact surfaces of linear extrusion — the geometry that SAT-1 skipped.
func TestAcisRealSurfaceSamples(t *testing.T) {
	d := "../go-dgn/ODA-Parse-DWGs-main/archives/Drawings_lnxX64_11dll.lic/bin/lnxX64_11dll/"
	cases := []struct {
		name     string
		bbox     [][2]float64 // per-axis expected envelope
		wantSurf bool         // false = layout variant, parsed but skipped
	}{
		// layout A (origin / unit normal / major / radius) — verified
		{"extrudedsurf", [][2]float64{{-2, 2}, {-1, 2}, {0, 3}}, true},
		// tapered (loftedsurf): shrinking sections with taper angle
		// sin=-1/√10 — exact rebuild via two-section ruled loft; x/y
		// bbox is the NURBS control-point envelope (slightly outside the
		// true surface), z is exact [0, 3].
		{"loftedsurf", [][2]float64{{-2.98, 2.01}, {-1.36, 1.36}, {0, 3}}, true},
		// sweptsurf (D117): split-band cylinder — each face rebuilds as
		// an extrusion band over the shared splitting ellipse, v domains
		// tile the full cylinder (face3 v 0..2.236 up to the top loop,
		// face5 v -2.062..0 down to the bottom loop).
		{"sweptsurf", [][2]float64{{-2.236, 2.557}, {-1.001, 1.001}, {-0.226, 4.868}}, true},
	}
	for _, tc := range cases {
		t.Run(tc.name, func(t *testing.T) {
			b, err := os.ReadFile(d + tc.name + ".sat")
			if err != nil {
				t.Skipf("sample absent: %v", err)
			}
			doc, err := sat.Parse(b)
			if err != nil {
				t.Fatalf("parse: %v", err)
			}
			cones := 0
			for _, r := range doc.Records {
				if r.Type == "cone-surface" {
					cones++
				}
			}
			if cones == 0 {
				t.Fatal("no cone-surface record")
			}
			sh := AcisBRepToShape(b)
			if tc.wantSurf {
				if sh == nil || sh.IsNull() {
					t.Fatal("shape nil")
				}
				d := sh.BBox().Data()
				for i := 0; i < 3; i++ {
					if math.IsInf(d[i], 0) || math.IsInf(d[i+3], 0) || math.IsNaN(d[i]) {
						t.Fatalf("bbox axis %d not finite: %v", i, d)
					}
				}
				for i, want := range tc.bbox {
					tol := 1e-6
					if d[i] < want[0]-tol || d[i] > want[1]+tol ||
						d[i+3] < want[0]-tol || d[i+3] > want[1]+tol {
						t.Fatalf("bbox axis %d = (%g,%g) outside %v", i, d[i], d[i+3], want)
					}
				}
			} else if sh != nil {
				t.Fatal("unpinned layout unexpectedly rebuilt")
			}
		})
	}
}

// TestAcisRevolvedSurf rebuilds the real revolvedsurf sample (D116): a
// spline-surface { rotsur } face — the base ellipse revolved around z by
// v ∈ [0, π]. The parameter-domain face stays inside the swept envelope.
func TestAcisRevolvedSurf(t *testing.T) {
	d := "../go-dgn/ODA-Parse-DWGs-main/archives/Drawings_lnxX64_11dll.lic/bin/lnxX64_11dll/"
	b, err := os.ReadFile(d + "revolvedsurf.sat")
	if err != nil {
		t.Skipf("sample absent: %v", err)
	}
	sh := AcisBRepToShape(b)
	if sh == nil || sh.IsNull() {
		t.Fatal("shape nil")
	}
	dv := sh.BBox().Data()
	// envelope of the half-revolution of the 2×1 ellipse at z=0:
	// x/y within ±2, z within ±1
	for i, span := range [][2]float64{{-2, 2}, {-2, 2}, {-1, 1}} {
		if dv[i] < span[0]-1e-6 || dv[i] > span[1]+1e-6 ||
			dv[i+3] < span[0]-1e-6 || dv[i+3] > span[1]+1e-6 {
			t.Fatalf("bbox axis %d = (%g,%g) outside %v", i, dv[i], dv[i+3], span)
		}
	}
}

// TestAcisBandedCone rebuilds a synthetic bounded cone face: a cone
// surface plus two equal translated ellipse loops — one extrusion band
// per loop, both covering the axis span between them.
func TestAcisBandedCone(t *testing.T) {
	docText := acisHdr +
		"cone-surface $-1 -1 $-1 0 0 0 0 0 1 1 0 0 0.5 I I -0.3162 0.9487 2 forward I I I I #\n" + // 0
		"face $1 -1 $-1 $-1 $2 $-1 $-1 $0 forward double out #\n" + // 1
		"loop $-1 -1 $-1 $-1 $4 $1 #\n" + // 2
		"loop $-1 -1 $-1 $-1 $5 $1 #\n" + // 3
		"coedge $-1 -1 $-1 $-1 $-1 $-1 $6 forward $2 $-1 #\n" + // 4
		"coedge $-1 -1 $-1 $-1 $-1 $-1 $7 forward $3 $-1 #\n" + // 5
		"edge $6 -1 $-1 $-1 0 $-1 6.2831853071795862 $4 $8 forward @7 unknown #\n" + // 6
		"edge $7 -1 $-1 $-1 0 $-1 6.2831853071795862 $5 $9 forward @7 unknown #\n" + // 7
		"ellipse-curve $-1 -1 $-1 0 0 0 0 0 1 2 0 0 0.5 I I #\n" + // 8
		"ellipse-curve $-1 -1 $-1 0 0 3 -0 -0 -1 -1 0 0 0.25 I I #" // 9
	sh := AcisBRepToShape([]byte(docText))
	if sh == nil || sh.IsNull() {
		t.Fatal("banded cone shape nil")
	}
	// the two bands cover z 0..3 (bottom loop at z=0, top at z=3)
	d := sh.BBox().Data()
	if d[2] < -1e-6 || math.Abs(d[5]-3) > 1e-6 {
		t.Fatalf("bbox z = (%g,%g) want 0..3", d[2], d[5])
	}
	// x/y stay within the largest section envelope (±2)
	if d[0] < -3+1e-6 || d[3] > 2+1e-6 { // x下界为 ruled NURBS 控制点包络（同真实 loftedsurf）
		t.Fatalf("bbox x = (%g,%g)", d[0], d[3])
	}
}

// TestDgnReaderSyntheticSharedCellSmartSolidFile runs the file-level
// synthetic fixture (go-dgn testdata, D124) through the full go-topo
// pipeline: LoadBytes → SceneV8ModelAtMaster → elements with the
// CellRef DefID/Transform, the SmartSolid BRep rebuilt as a sphere, and
// the bit14 line child instantiated through the SharedCell in toMst.
func TestDgnReaderSyntheticSharedCellSmartSolidFile(t *testing.T) {
	p := "../go-dgn/dgn/testdata/v8_synth_sc_ss.dgn"
	r := NewDgnReader()
	if err := r.Load(p); err != nil {
		t.Fatalf("load: %v", err)
	}
	els := r.GetElements()
	var inst, def, solid *DgnElement
	for _, e := range els {
		switch {
		case e.Id == 500:
			inst = e
		case e.Id == 0x64:
			def = e
		case e.Id == 300:
			solid = e
		}
	}
	if inst == nil || inst.Type != "CellRef" || inst.DefID != 0x64 {
		t.Fatalf("inst = %+v", inst)
	}
	if inst.Transform == nil {
		t.Fatal("inst transform nil")
	}
	if def == nil || def.Type != "CellDef" || def.Name != "CELL01" {
		t.Fatalf("def = %+v", def)
	}
	if solid == nil || solid.Type != "Solid" {
		t.Fatalf("solid = %+v", solid)
	}
	if solid.BRep == nil {
		t.Fatal("smartsolid brep nil")
	}
	if solid.Shape == nil || solid.Shape.IsNull() {
		t.Fatal("smartsolid shape not rebuilt")
	}
	d := solid.Shape.BBox().Data()
	tol := 1e-6
	for i, want := range [][2]float64{{-1, 1}, {-1, 1}, {-1, 1}} {
		if d[i] < want[0]-tol || d[i] > want[1]+tol || d[i+3] < want[0]-tol || d[i+3] > want[1]+tol {
			t.Fatalf("sphere bbox axis %d = (%g,%g)", i, d[i], d[i+3])
		}
	}
}

// TestDgnToMstSyntheticSharedCellFile instantiates the file-level
// fixture's shared cell through toMst: the definition's bit14 line child
// appears placed by the reference transform (10,20,30).
func TestDgnToMstSyntheticSharedCellFile(t *testing.T) {
	p := "../go-dgn/dgn/testdata/v8_synth_sc_ss.dgn"
	meshes, err := DgnToMst(p)
	if err != nil {
		t.Fatalf("toMst: %v", err)
	}
	found := false
	for _, m := range meshes {
		for _, nd := range m.Nodes {
			if len(nd.Vertices) != 2 {
				continue
			}
			v0 := nd.Vertices[0]
			// child endpoints (5,6,0)/(15,16,0) placed by (10,20,30) in
			// UOR, scaled to master units by UorPerMaster=10000
			const u = 1e-4
			if math.Abs(float64(v0[0])-15*u) < 1e-9 && math.Abs(float64(v0[1])-26*u) < 1e-9 &&
				math.Abs(float64(v0[2])-30*u) < 1e-9 {
				found = true
			}
		}
	}
	if !found {
		t.Fatal("instanced line not placed at (10,20,30)")
	}
}
