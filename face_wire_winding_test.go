package topo

// face::make_from_wires 内环绕向回归。
//
// 同向内环 (与外环同绕向) 会被 OCCT 当成凸台而非孔: 体积 1080 = (200+16)*5 而非
// 920 = (200-16)*5, 且 IsValid() == false。反向内环则正常。
//
// 判据用 IsValid(): 两种情况下 bbox 完全相同 (20x10x5), 只有有效性可区分。
// 参照实现见 face::make_face(wire, vector<wire>) —— 它不清洗绕向, 而是建面后交给
// ShapeFix_Face::FixOrientation() 处理。

import (
	"testing"
)

func windingQuad(x0, y0, x1, y1 float64) []*TopoVector {
	return []*TopoVector{
		NewTopoVector(x0, y0, 0),
		NewTopoVector(x1, y0, 0),
		NewTopoVector(x1, y1, 0),
		NewTopoVector(x0, y1, 0),
	}
}

func buildHoledPlate(t *testing.T, inner []*TopoVector) *Shape {
	t.Helper()
	wp := NewWorkplane()
	r := wp.Polyline(windingQuad(0, 0, 20, 10), false, false).Close()
	r = r.Polyline(inner, false, false).Close()
	s := r.ExtrudeSimple(5)
	if s == nil {
		t.Fatal("extrude returned nil")
	}
	return s.Value()
}

func TestFaceFromWiresHoleWinding(t *testing.T) {
	t.Run("inner wire wound opposite to the outer is a hole", func(t *testing.T) {
		// Clockwise inner: the orientation OCCT reads as a hole.
		sh := buildHoledPlate(t, []*TopoVector{
			NewTopoVector(8, 3, 0),
			NewTopoVector(8, 7, 0),
			NewTopoVector(12, 7, 0),
			NewTopoVector(12, 3, 0),
		})
		if !sh.IsValid() {
			t.Errorf("opposite-wound inner wire produced an invalid solid")
		}
		bb := sh.BBox().Data()
		for i, want := range []float64{0, 0, 0, 20, 10, 5} {
			if diff := bb[i] - want; diff > 1e-6 || diff < -1e-6 {
				t.Errorf("bbox[%d] = %v, want %v", i, bb[i], want)
			}
		}
	})

	// Known defect, deliberately not fixed. A counter-clockwise inner wire matches
	// the outer's winding and is read by OCCT as a boss: material is added instead
	// of removed and the solid is invalid.
	//
	// The repair is understood and verified — ShapeFix_Face::FixOrientation() makes
	// this case valid, provided it is gated on the added wires actually lying
	// inside the outer one (ungated, it flattens the braille example, where
	// workplane::get_faces() mislabels six disjoint circles as outer+holes). It is
	// not landed because it also moves example_29_enclosure, one of the examples
	// whose golden records WHERE go-topo's safe_call chain froze rather than any
	// geometry. Under the repair the WASM's frozen state diverges from Go's, so the
	// golden suite cannot be reconciled without first deciding how those degraded
	// examples should be asserted. See topo.js AGENTS.md and
	// test/workplane_full.test.ts (which tracks this as `it.fails`).
	t.Run("inner wire wound the same way as the outer is also a hole", func(t *testing.T) {
		t.Skip("known defect: fixable via ShapeFix_Face::FixOrientation + containment gate, " +
			"blocked on how degraded goldens are asserted")
		sh := buildHoledPlate(t, windingQuad(8, 3, 12, 7))
		if !sh.IsValid() {
			t.Errorf("same-wound inner wire produced an invalid solid")
		}
	})

	t.Run("no inner wires still builds", func(t *testing.T) {
		wp := NewWorkplane()
		s := wp.Polyline(windingQuad(0, 0, 20, 10), false, false).Close().ExtrudeSimple(5)
		if sh := s.Value(); !sh.IsValid() {
			t.Errorf("plain closed profile produced an invalid solid")
		}
	})
}
