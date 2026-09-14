package topo

// TEMPORARY golden-dump instrumentation — removed again once the goldens for the
// current go-topo revision have been captured.
//
// 口径 matches topo.js's test/cq/goldens.json exactly: the bounding box of
// `Workplane.Value()`, the object on top of the stack. (STEP round-trip is NOT
// equivalent — mirrored/offset examples come back with different boxes — which is
// why the goldens are captured from the in-memory shape rather than from the
// exported .step files.)
//
// Enable with GOLDEN_DUMP=<path>. Without it nothing is written.

import (
	"encoding/json"
	"os"
	"testing"
)

var goldenBBoxes = map[string][6]float64{}

// recordGolden captures the Value() bbox of the example's final workplane.
func recordGolden(t *testing.T, key string, wp *Workplane) {
	t.Helper()
	if os.Getenv("GOLDEN_DUMP") == "" {
		return
	}
	sh := wp.Value()
	if sh == nil {
		t.Fatalf("recordGolden(%s): Value() is nil", key)
	}
	goldenBBoxes[key] = sh.BBox().Data()
}

// writeGoldenDump is called from TestMain after the suite has run.
func writeGoldenDump() error {
	path := os.Getenv("GOLDEN_DUMP")
	if path == "" || len(goldenBBoxes) == 0 {
		return nil
	}
	b, err := json.MarshalIndent(goldenBBoxes, "", "  ")
	if err != nil {
		return err
	}
	return os.WriteFile(path, append(b, '\n'), 0o644)
}
