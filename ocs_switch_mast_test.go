package topo

// 开关柱 (接触网接入变电站) 单元测试:
// 结构完整性 (柱/腕臂/横担/隔离开关/连接线/回流线) + 尺寸闸门 + 参数化往返

import (
	"math"
	"strings"
	"testing"
)

func switchMastParams() SwitchMastParams {
	return SwitchMastParams{MastHeight: 11000, ContactHeight: 6000, StructureHeight: 1400,
		SideOffset: 2900, Stagger: 300, SwitchCount: 2, SwitchOpen: 0,
		CrossarmSpan: 3600, FeedOutOffset: 8000, FeedOutHeight: 9800, HasReturnLine: true}
}

func TestSwitchMastAssembly(t *testing.T) {
	as, err := CreateSwitchMastWithPlace(switchMastParams(), "switch_mast")
	if err != nil {
		t.Fatalf("create: %v", err)
	}
	found := map[string]int{}
	for _, el := range as.GetElements() {
		n := el.GetName()
		for _, k := range []string{"post", "cantilever", "frame",
			"switch_0", "switch_1", "switch_2", "switch_3",
			"link_t_0", "link_t_1", "link_t_2", "link_t_3",
			"feed_out_0", "feed_out_1", "feed_out_2", "feed_out_3",
			"pw_arm", "pw_wire", "pw_lead"} {
			if strings.Contains(n, "/"+k) {
				found[k]++
			}
		}
	}
	for _, k := range []string{"post", "cantilever", "frame",
		"switch_0", "switch_1", "switch_2", "switch_3",
		"link_t_0", "link_t_1", "link_t_2", "link_t_3",
		"feed_out_0", "feed_out_1", "feed_out_2", "feed_out_3",
		"pw_arm", "pw_wire", "pw_lead"} {
		if found[k] != 1 {
			t.Fatalf("leaf %s count=%d want 1 (found=%v)", k, found[k], found)
		}
	}
	// 每组开关的两支柱应分别落在两纵梁中心 (±FrameWidth/2)
	sw0, ok := as.Get("switch_mast/switch_0")
	if !ok {
		t.Fatal("switch_0 missing")
	}
	bb := sw0.GetShape().BBox().Data()
	if w := bb[3] - bb[0]; w < 1350 || w > 1700 {
		t.Fatalf("switch_0 X span %.0f (底座跨两纵梁 1400 + 机构箱外伸)", w)
	}

	// 尺寸: 柱高 11m; 馈线引出到 ±9750 → Y 向跨度 ~19500; X 向 CX+拉出值侧 2600 / field 侧 -800
	comp := as.ToCompound()
	bb2 := comp.BBox().Data()
	h := bb2[5] - bb2[2]
	if h < 10900 || h > 11400 {
		t.Fatalf("height %.0f out of [10900,11400]", h)
	}
	ySpan := bb2[4] - bb2[1]
	if ySpan < 17000 || ySpan > 19500 {
		t.Fatalf("Y span %.0f out of [17000,19500] (馈线引出)", ySpan)
	}
	xMax := bb2[3]
	if xMax < 2400 || xMax > 2900 {
		t.Fatalf("X max %.0f out of [2400,2900] (定位点侧)", xMax)
	}
	xMin := bb2[0]
	if xMin > -200 || xMin < -1400 {
		t.Fatalf("X min %.0f out of [-1400,-200] (回流线 field 侧)", xMin)
	}
}

func TestSwitchMastParametricRoundTrip(t *testing.T) {
	as, err := CreateSwitchMastWithPlace(switchMastParams(), "switch_mast")
	if err != nil {
		t.Fatal(err)
	}
	as.SetParametric(&ParametricData{Type: "ocs_switch_mast", Params: mustJSON(switchMastParams())})
	data, err := as.ExportParametric()
	if err != nil {
		t.Fatal(err)
	}
	rebuilt, err := RebuildFromParametric(data)
	if err != nil {
		t.Fatalf("rebuild: %v", err)
	}
	bb1, bb2 := as.ToCompound().BBox().Data(), rebuilt.ToCompound().BBox().Data()
	for i := range bb1 {
		if math.Abs(bb1[i]-bb2[i]) > 2 {
			t.Fatalf("rebuild bbox mismatch [%d]: %.3f vs %.3f", i, bb1[i], bb2[i])
		}
	}
	// 叶片数一致
	if len(as.GetElements()) != len(rebuilt.GetElements()) {
		t.Fatalf("leaf count %d vs %d", len(as.GetElements()), len(rebuilt.GetElements()))
	}
}

func TestSwitchMastMastTypes(t *testing.T) {
	for _, mt := range []int{1, 2, 3} {
		p := switchMastParams()
		p.MastType = mt
		as, err := CreateSwitchMastWithPlace(p, "switch_mast")
		if err != nil {
			t.Fatalf("mastType %d: %v", mt, err)
		}
		bb := as.ToCompound().BBox().Data()
		h := bb[5] - bb[2]
		if h < 10900 || h > 11500 {
			t.Fatalf("mastType %d: height %.0f out of range", mt, h)
		}
		t.Logf("mastType %d: height=%.0f", mt, h)
	}
}

func TestSwitchMastThreeGroups(t *testing.T) {
	p := switchMastParams()
	p.SwitchCount = 3
	as, err := CreateSwitchMastWithPlace(p, "switch_mast")
	if err != nil {
		t.Fatal(err)
	}
	n := 0
	for _, el := range as.GetElements() {
		if strings.Contains(el.GetName(), "/switch_") {
			n++
		}
	}
	if n != 3 {
		t.Fatalf("switch count=%d want 3", n)
	}
}
