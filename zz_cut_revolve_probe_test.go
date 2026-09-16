package topo

import "testing"

func Test_zz_cut_revolve_probe(t *testing.T) {
	wp := NewWorkplane()
	base := wp.BoxCentered(4, 4, 1)
	wp2 := NewWorkplaneFromName("XY", NewTopoVector(1, 0, 0))
	pillar := wp2.BoxCentered(1, 1, 3)
	fused := base.Union(pillar, true, false, 0.001)
	t.Logf("fused bbox: %v", fused.Value().BBox().Data())

	cutter := NewWorkplane().CircleCentered(0.5).ExtrudeSimple(5)
	t.Logf("cutter bbox: %v", cutter.Value().BBox().Data())
	result := fused.Cut(cutter, true, 0.001)
	v := result.Value()
	if v == nil || v.IsNull() {
		t.Log("cut 结果为空")
	} else {
		t.Logf("cut bbox: %v", v.BBox().Data())
	}

	rv := NewWorkplane().CircleCentered(2).RevolveSimple(180)
	rv2 := rv.Value()
	if rv2 == nil || rv2.IsNull() {
		t.Log("revolve 结果为空")
	} else {
		t.Logf("revolve bbox: %v", rv2.BBox().Data())
	}
}
