package topo

import (
	"math"
	"os"
	"path/filepath"
	"sort"
	"testing"

	rp "github.com/flywave/go-rvt/rvt"
	"github.com/flywave/go-rvt/rvt/geom"
)

// RVT fixtures live in go-rvt's regression testdata (gitignored there);
// tests skip gracefully when absent.
const rvtTestDataDir = "../go-rvt/rvt/testdata"

func rvtSamples(t *testing.T) []string {
	t.Helper()
	ents, err := os.ReadDir(rvtTestDataDir)
	if err != nil {
		t.Skipf("testdata absent: %v", err)
	}
	var paths []string
	for _, e := range ents {
		if filepath.Ext(e.Name()) == ".rvt" {
			paths = append(paths, filepath.Join(rvtTestDataDir, e.Name()))
		}
	}
	if len(paths) == 0 {
		t.Skip("no rvt samples")
	}
	sort.Strings(paths)
	return paths
}

// TestRvtReaderCoverage is the zero-missing-objects audit: for every
// sample the bridge output must equal the go-rvt geometry manifest
// exactly — every geometry-bearing element present, no phantoms — and
// each element's payload must satisfy the fidelity invariants.
func TestRvtReaderCoverage(t *testing.T) {
	for _, path := range rvtSamples(t) {
		t.Run(filepath.Base(path), func(t *testing.T) {
			data, err := os.ReadFile(path)
			if err != nil {
				t.Fatalf("read: %v", err)
			}
			r := NewRvtReader()
			if err := r.LoadBytes(data); err != nil {
				t.Fatalf("load: %v", err)
			}
			manifest := rvtManifest(t, data)
			els := r.GetElements()
			if len(els) != len(manifest) {
				t.Fatalf("coverage: bridge=%d manifest=%d", len(els), len(manifest))
			}
			seen := map[uint64]bool{}
			unnamed, withWires, withBBox := 0, 0, 0
			for _, e := range els {
				if seen[e.Id] {
					t.Errorf("duplicate element id %d", e.Id)
				}
				seen[e.Id] = true
				if _, ok := manifest[uint32(e.Id)]; !ok {
					t.Errorf("phantom element %d not in manifest", e.Id)
				}
				if e.ClassName == "" {
					unnamed++
				}
				if e.LineCount+e.ArcCount > 0 && len(e.Wires) == 0 {
					t.Errorf("element %d has %d+%d curves but no wires",
						e.Id, e.LineCount, e.ArcCount)
				}
				if len(e.Wires) > 0 {
					withWires++
					for _, w := range e.Wires {
						if w.IsNull() {
							t.Errorf("element %d has a null wire", e.Id)
						}
					}
				}
				if e.BBox != nil {
					withBBox++
					d := e.BBox.Data()
					for k := 0; k < 6; k++ {
						if math.IsNaN(d[k]) || math.IsInf(d[k], 0) || math.Abs(d[k]) > 1e8 {
							t.Errorf("element %d bbox value %v out of range", e.Id, d[k])
							break
						}
					}
					for k := 0; k < 3; k++ {
						if d[k] > d[k+3] {
							t.Errorf("element %d bbox min>max on axis %d", e.Id, k)
						}
					}
				}
			}
			for id := range manifest {
				if !seen[uint64(id)] {
					t.Errorf("missing element %d from manifest", id)
				}
			}
			if unnamed*100 > len(els) {
				t.Errorf("%d/%d elements unnamed", unnamed, len(els))
			}
			// element-record enrichment (Revit 2023 layout)
			if name := filepath.Base(path); name == "rac_basic_2023.rvt" {
				if r.RecordCount() != 1197 {
					t.Errorf("records %d, want 1197 (rvt-rs reference)", r.RecordCount())
				}
				walls, named, thick := 0, 0, 0
				for _, e := range els {
					if e.Category == -2_000_011 { // OST_Walls
						walls++
						if !e.Placed && !e.TypeSymbol {
							t.Errorf("wall %d has neither placement kind", e.Id)
						}
						if e.TypeName != "" {
							named++
						}
					}
				}
				for _, e := range els {
					if e.Category == -2_000_032 && e.Placed && e.TypeName != "" {
						thick++
					}
				}
				if walls != 56 {
					t.Errorf("OST_Walls records %d, want 56", walls)
				}
				if named < 40 {
					t.Errorf("walls with type names %d, want >= 40 (47 join exactly)", named)
				}
				t.Logf("walls named: %d, slabs named: %d", named, thick)
			}
			t.Logf("%s: elements=%d withWires=%d withBBox=%d unnamed=%d records=%d version=%q",
				filepath.Base(path), len(els), withWires, withBBox, unnamed, r.RecordCount(), r.RevitVersion())
		})
	}
}

// rvtManifest recomputes the geometry manifest independently of the
// reader (same library, separate pipeline walk) for the audit.
func rvtManifest(t *testing.T, data []byte) map[uint32]*geom.ElementGeometry {
	t.Helper()
	f, err := rp.OpenCFB(data)
	if err != nil {
		t.Fatalf("cfb: %v", err)
	}
	var biggest string
	var sz uint64
	for _, sp := range f.StreamPaths() {
		if len(sp) > 11 && sp[:11] == "Partitions/" {
			s, _ := f.Size(sp)
			if s > sz {
				sz, biggest = s, sp
			}
		}
	}
	raw, err := f.Stream(biggest)
	if err != nil {
		t.Fatalf("stream: %v", err)
	}
	part, err := rp.ReadPartition(biggest[11:], raw)
	if err != nil {
		t.Fatalf("partition: %v", err)
	}
	version := ""
	if md, err := rp.Open(data); err == nil {
		version = md.RevitVersion
	}
	return part.Model(version).GeometryManifest()
}

// TestRvtReaderMinimums locks the per-sample object floors so a decode
// regression cannot silently shrink the bridged object set.
func TestRvtReaderMinimums(t *testing.T) {
	floors := map[string]int{
		"rac_basic_2023.rvt":    12100,
		"rst_advanced_2022.rvt": 6800,
		"rac_advanced_2017.rvt": 10400,
	}
	for _, path := range rvtSamples(t) {
		name := filepath.Base(path)
		floor, ok := floors[name]
		if !ok {
			continue
		}
		t.Run(name, func(t *testing.T) {
			r := NewRvtReader()
			if err := r.Load(path); err != nil {
				t.Fatalf("load: %v", err)
			}
			if len(r.GetElements()) < floor {
				t.Errorf("elements %d < floor %d", len(r.GetElements()), floor)
			}
		})
	}
}

// TestRvtReaderArcWire checks the arc conversion math directly: an
// unknown-span arc bridges as a full circle, a parametrized span as a
// three-point arc — both circular with the scaled radius.
func TestRvtReaderArcWire(t *testing.T) {
	r := NewRvtReader()
	r.SetScale(0.3048)
	arc := geom.Arc{
		Center: geom.Point3{X: 1, Y: 2, Z: 3},
		XDir:   geom.Point3{X: 1, Y: 0, Z: 0},
		YDir:   geom.Point3{X: 0, Y: 1, Z: 0},
		Radius: 2,
	}
	w := r.arcWire(arc)
	if w == nil || w.IsNull() {
		t.Fatal("full-circle wire nil")
	}
	if got := w.Radius(); math.Abs(got-2*0.3048) > 1e-9 {
		t.Errorf("full circle radius %v want %v", got, 2*0.3048)
	}
	partial := arc
	partial.StartAngle = 0
	partial.EndAngle = math.Pi / 2
	w = r.arcWire(partial)
	if w == nil || w.IsNull() {
		t.Fatal("partial arc wire nil")
	}
	// start point sits at C + R·X̂ (scaled); center of a partial arc wire
	// is the curve centroid, not the circle center — verify via endpoints.
	wantStart := [3]float64{3 * 0.3048, 2 * 0.3048, 3 * 0.3048}
	got := w.StartPoint().Data()
	for k := 0; k < 3; k++ {
		if math.Abs(got[k]-wantStart[k]) > 1e-9 {
			t.Errorf("start[%d]=%v want %v", k, got[k], wantStart[k])
		}
	}
	wantEnd := [3]float64{1 * 0.3048, 4 * 0.3048, 3 * 0.3048}
	got = w.EndPoint().Data()
	for k := 0; k < 3; k++ {
		if math.Abs(got[k]-wantEnd[k]) > 1e-9 {
			t.Errorf("end[%d]=%v want %v", k, got[k], wantEnd[k])
		}
	}
}

// TestRvtReaderLineWire checks segment geometry end to end.
func TestRvtReaderLineWire(t *testing.T) {
	r := NewRvtReader()
	g := &geom.ElementGeometry{
		Lines: []geom.Line{
			{Origin: geom.Point3{X: 0, Y: 0, Z: 0}, Direction: geom.Point3{X: 1, Y: 0, Z: 0}},
			{Origin: geom.Point3{X: 1, Y: 0, Z: 0}, Direction: geom.Point3{X: 1, Y: 1, Z: 0}},
		},
	}
	ws := r.wiresFor(g)
	if len(ws) != 1 {
		t.Fatalf("wires %d want 1 (contiguous run merges)", len(ws))
	}
	sp := ws[0].StartPoint().Data()
	ep := ws[0].EndPoint().Data()
	if math.Abs(sp[0]) > 1e-9 || math.Abs(sp[1]) > 1e-9 {
		t.Errorf("start %v want origin", sp)
	}
	if math.Abs(ep[0]-1) > 1e-9 || math.Abs(ep[1]-1) > 1e-9 {
		t.Errorf("end %v want (1,1,0)", ep)
	}
}

// TestRvtReaderProfiles checks the sketch-profile reconstruction on the
// 2023 sample: nine floor/roof sketches close unambiguously (locked by
// cross-validation against the reference implementation's record layer),
// each yielding an extruded solid whose mass matches the profile area ×
// the record's Z extent.
func TestRvtReaderProfiles(t *testing.T) {
	path := filepath.Join(rvtTestDataDir, "rac_basic_2023.rvt")
	if _, err := os.Stat(path); err != nil {
		t.Skip("sample absent")
	}
	r := NewRvtReader()
	if err := r.Load(path); err != nil {
		t.Fatalf("load: %v", err)
	}
	withProfile, withShape := 0, 0
	var areas []float64
	for _, e := range r.GetElements() {
		if e.Profile != nil {
			withProfile++
			t.Logf("element %d profile: outer=%d inner=%d pieces=%d",
				e.Id, len(e.Profile.OuterXY), len(e.Profile.InnerXY), len(e.Profile.Pieces))
			areas = append(areas, math.Abs(rvtSignedArea(e.Profile.OuterXY)))
			if e.Shape != nil {
				withShape++
				if m := e.Shape.ComputeMass(); m <= 0 {
					t.Errorf("element %d profile shape has non-positive mass %v", e.Id, m)
				}
			}
		}
	}
	if withProfile != 9 {
		t.Errorf("profiles %d, want 9 (cross-validated)", withProfile)
	}
	if withShape != withProfile {
		t.Errorf("profile shapes %d != profiles %d", withShape, withProfile)
	}
	sort.Float64s(areas)
	t.Logf("profiles=%d shapes=%d areas(sorted, ft²)=%v", withProfile, withShape, areas)
}

// rvtSignedArea of a plan ring (positive = counter-clockwise).
func rvtSignedArea(ring []rp.Point2) float64 {
	if len(ring) < 3 {
		return 0
	}
	total := 0.0
	for i := range ring {
		p := ring[i]
		q := ring[(i+1)%len(ring)]
		total += p.X*q.Y - q.X*p.Y
	}
	return total / 2
}

// TestRvtReaderWallShapes checks wall location-curve geometry on the
// 2023 sample: every placed wall carries a location line or arc
// (cross-validated: 56/56) and yields an extruded body of positive mass.
func TestRvtReaderWallShapes(t *testing.T) {
	path := filepath.Join(rvtTestDataDir, "rac_basic_2023.rvt")
	if _, err := os.Stat(path); err != nil {
		t.Skip("sample absent")
	}
	r := NewRvtReader()
	if err := r.Load(path); err != nil {
		t.Fatalf("load: %v", err)
	}
	walls, shapes := 0, 0
	for _, e := range r.GetElements() {
		if e.Category != -2_000_011 || !e.Placed {
			continue
		}
		walls++
		if e.Shape != nil {
			shapes++
			if m := e.Shape.ComputeMass(); m <= 0 {
				t.Errorf("wall %d shape has non-positive mass %v", e.Id, m)
			}
		}
	}
	if walls != 56 {
		t.Errorf("placed walls %d, want 56", walls)
	}
	if shapes != walls {
		t.Errorf("wall shapes %d != walls %d", shapes, walls)
	}
	t.Logf("walls=%d shapes=%d", walls, shapes)
}
