package topo

import (
	"math"
	"reflect"
	"sort"
	"testing"
)

// 250m 直线中心线 (跨距 50m → 6 支柱 5 跨)
func anchorTestInput() AnchorSectionInput {
	var cl []Point3
	for x := 0.0; x <= 250000; x += 5000 {
		cl = append(cl, NewPoint3([3]float64{x, 0, 0}))
	}
	return AnchorSectionInput{
		Centerline:     cl,
		ContactHeight:  5300,
		SpanLength:     50000,
		MastHeight:     8000,
		MastType:       1,
		HasCompensator: true,
	}
}

// 锚段生成器: 250m 直线, 跨距 50m → 6 支柱 + 承力索/接触线/吊弦
func TestCreateAnchorSection(t *testing.T) {
	var cl []Point3
	for x := 0.0; x <= 250000; x += 5000 {
		cl = append(cl, NewPoint3([3]float64{x, 0, 0}))
	}
	as, err := CreateAnchorSection(AnchorSectionInput{
		Centerline:     cl,
		ContactHeight:  5300,
		SpanLength:     50000,
		MastHeight:     8000,
		MastType:       1,
		HasCompensator: true,
	})
	if err != nil {
		t.Fatalf("anchor section failed: %v", err)
	}
	if as == nil {
		t.Fatal("nil assembly")
	}
	n := len(as.GetElements())
	t.Logf("anchor section elements: %d", n)
	// 6 支柱 + 5 接触线 + 5 承力索 + 吊弦群
	if n < 16 {
		t.Fatalf("too few elements: %d", n)
	}
	bb := as.ToCompound().BBox().Data()
	dx := bb[3] - bb[0]
	dz := bb[5] - bb[2]
	t.Logf("anchor bbox: %.0f x %.0f x %.0f", dx, bb[4]-bb[1], dz)
	if dx < 240000 {
		t.Fatalf("anchor length wrong: %.0f", dx)
	}
	// 高度应覆盖 坠砣串底部 ~ 承力索+补偿轮
	if dz < 6000 || dz > 12000 {
		t.Fatalf("anchor height wrong: %.0f", dz)
	}
}

// 棘轮补偿装置单体
func TestRatchetCompensator(t *testing.T) {
	s := CreateRatchetCompensator(RatchetCompensatorParams{})
	if s == nil || s.IsNull() {
		t.Fatal("nil ratchet compensator")
	}
	bb := s.BBox().Data()
	if bb[5]-bb[2] < 1500 {
		t.Fatalf("compensator height wrong: %.0f", bb[5]-bb[2])
	}
}

// 附加导线
func TestAuxiliaryWire(t *testing.T) {
	s := CreateAuxiliaryWire(AuxiliaryWireParams{Diameter: 12, Sag: 500},
		NewPoint3([3]float64{0, 0, 8000}), NewPoint3([3]float64{50000, 0, 8000}))
	if s == nil || s.IsNull() {
		t.Fatal("nil auxiliary wire")
	}
}

// 滑轮补偿装置
func TestPulleyCompensator(t *testing.T) {
	s := CreatePulleyCompensator(PulleyCompensatorParams{})
	if s == nil || s.IsNull() {
		t.Fatal("nil pulley compensator")
	}
	bb := s.BBox().Data()
	if bb[5]-bb[2] < 1500 {
		t.Fatalf("pulley compensator height wrong: %.0f", bb[5]-bb[2])
	}
}

// 隔离开关 (分闸状态)
func TestDisconnector(t *testing.T) {
	s := CreateDisconnector(DisconnectorParams{})
	if s == nil || s.IsNull() {
		t.Fatal("nil disconnector")
	}
	bb := s.BBox().Data()
	// 分闸 75°: 触刀竖起, 总高应明显大于绝缘子高
	if bb[5]-bb[2] < 1000 {
		t.Fatalf("disconnector height wrong: %.0f", bb[5]-bb[2])
	}
}

// 避雷器
func TestArrester(t *testing.T) {
	s := CreateArrester(ArresterParams{})
	if s == nil || s.IsNull() {
		t.Fatal("nil arrester")
	}
	bb := s.BBox().Data()
	if bb[5]-bb[2] < 700 || bb[5]-bb[2] > 900 {
		t.Fatalf("arrester height wrong: %.0f", bb[5]-bb[2])
	}
}

// 双套筒连接器 / 套管单耳
func TestCantileverFittings(t *testing.T) {
	s1 := CreateSleeveConnector(SleeveConnectorParams{})
	if s1 == nil || s1.IsNull() {
		t.Fatal("nil sleeve connector")
	}
	s2 := CreateSleeveEar(SleeveEarParams{})
	if s2 == nil || s2.IsNull() {
		t.Fatal("nil sleeve ear")
	}
}

// 布局计算: 柱数/跨距/吊弦数量与长度 与手算一致
func TestAnchorLayoutCompute(t *testing.T) {
	layout, err := ComputeAnchorSectionLayout(anchorTestInput())
	if err != nil {
		t.Fatalf("compute layout failed: %v", err)
	}
	if len(layout.Masts) != 6 {
		t.Fatalf("expected 6 masts, got %d", len(layout.Masts))
	}
	if len(layout.Spans) != 5 {
		t.Fatalf("expected 5 spans, got %d", len(layout.Spans))
	}
	for i, m := range layout.Masts {
		if math.Abs(m.Position[0]-float64(i)*50000) > 1e-6 {
			t.Fatalf("mast %d x wrong: %v", i, m.Position[0])
		}
		if math.Abs(m.Position[1]-2900) > 1e-6 {
			t.Fatalf("mast %d y (CX) wrong: %v", i, m.Position[1])
		}
		// 拉出值之字 ±300, 接触线悬挂点 y = stagger
		wantStagger := 300.0
		if i%2 == 1 {
			wantStagger = -300
		}
		if m.Stagger != wantStagger {
			t.Fatalf("mast %d stagger wrong: %v", i, m.Stagger)
		}
		if math.Abs(m.ContactPoint[1]-wantStagger) > 1e-6 {
			t.Fatalf("mast %d contact point y wrong: %v", i, m.ContactPoint[1])
		}
		if m.ContactPoint[2] != 5300 || m.MessengerPoint[2] != 6700 {
			t.Fatalf("mast %d wire z wrong: %v / %v", i, m.ContactPoint[2], m.MessengerPoint[2])
		}
	}
	if !layout.Masts[0].IsTensionMast || !layout.Masts[5].IsTensionMast || layout.Masts[2].IsTensionMast {
		t.Fatal("tension mast flags wrong")
	}
	for i, sp := range layout.Spans {
		if sp.FromMast != i || sp.ToMast != i+1 {
			t.Fatalf("span %d mast refs wrong: %d,%d", i, sp.FromMast, sp.ToMast)
		}
		// 跨距 = 两端接触线悬挂点间距: 纵向 50000, 横向拉出值 300→-300 差 600
		if math.Abs(sp.Length-math.Hypot(50000, 600)) > 1 {
			t.Fatalf("span %d length wrong: %v", i, sp.Length)
		}
		// 弛度: 接触线 50000*0.0005=25, 承力索 50000*0.015=750
		if sp.ContactSag != 25 || sp.MessengerSag != 750 {
			t.Fatalf("span %d sag wrong: %v / %v", i, sp.ContactSag, sp.MessengerSag)
		}
		// 吊弦: n = 跨距/8000 = 6 根, t = k/7; 长度 = 1400 - 4*(750-25)*t*(1-t)
		if len(sp.Droppers) != 6 {
			t.Fatalf("span %d expected 6 droppers, got %d", i, len(sp.Droppers))
		}
		mid := sp.Droppers[2]
		if math.Abs(mid.T-3.0/7.0) > 1e-9 {
			t.Fatalf("span %d dropper t wrong: %v", i, mid.T)
		}
		wantLen := 1400 - 4*(750-25)*mid.T*(1-mid.T)
		if math.Abs(mid.Length-wantLen) > 1e-6 {
			t.Fatalf("span %d dropper length wrong: %v, want %v", i, mid.Length, wantLen)
		}
	}
}

// 布局 JSON 往返
func TestAnchorLayoutJSONRoundTrip(t *testing.T) {
	layout, err := ComputeAnchorSectionLayout(anchorTestInput())
	if err != nil {
		t.Fatalf("compute layout failed: %v", err)
	}
	data, err := layout.ToJSON()
	if err != nil {
		t.Fatalf("ToJSON failed: %v", err)
	}
	back, err := AnchorSectionLayoutFromJSON(data)
	if err != nil {
		t.Fatalf("FromJSON failed: %v", err)
	}
	if !reflect.DeepEqual(layout, back) {
		t.Fatalf("layout JSON round trip mismatch")
	}
}

// FromLayout 装配: 命名唯一 + 关键子件可按名寻址
func TestAnchorFromLayoutNaming(t *testing.T) {
	_, layout, err := CreateAnchorSectionWithLayout(anchorTestInput())
	if err != nil {
		t.Fatalf("create with layout failed: %v", err)
	}
	as, err := CreateAnchorSectionFromLayout(layout)
	if err != nil {
		t.Fatalf("from layout failed: %v", err)
	}
	if as.GetName() != "anchor_section" {
		t.Fatalf("root name wrong: %q", as.GetName())
	}
	seen := map[string]bool{}
	for _, el := range as.GetElements() {
		n := el.GetName()
		if seen[n] {
			t.Fatalf("duplicate element name: %q", n)
		}
		seen[n] = true
	}
	// 根容器 + 6 支柱 + 5 接触线 + 5 承力索 + 30 吊弦 = 47
	if len(seen) != 47 {
		t.Fatalf("expected 47 elements, got %d", len(seen))
	}
	for _, name := range []string{"mast_0", "mast_5", "cw_0", "mw_4", "dropper_0_0", "dropper_4_5"} {
		if _, ok := as.Get(name); !ok {
			t.Fatalf("element %q not found", name)
		}
	}
}

// 编辑场景: 改拉出值/柱位 → FromLayout 再生成 → 对应子件几何/放置变化
func TestAnchorLayoutEditRegenerate(t *testing.T) {
	_, layout, err := CreateAnchorSectionWithLayout(anchorTestInput())
	if err != nil {
		t.Fatalf("create with layout failed: %v", err)
	}
	as0, err := CreateAnchorSectionFromLayout(layout)
	if err != nil {
		t.Fatalf("from layout failed: %v", err)
	}
	cw0, _ := as0.Get("cw_0")
	yMax0 := cw0.GetShape().BBox().Data()[4]

	// 改 mast_1 拉出值 -300 → +500: cw_0 终点随之移动
	layout.Masts[1].Stagger = 500
	// 移动 mast_2 沿线路 +5000
	layout.Masts[2].Position[0] += 5000

	as1, err := CreateAnchorSectionFromLayout(layout)
	if err != nil {
		t.Fatalf("from edited layout failed: %v", err)
	}
	cw1, _ := as1.Get("cw_0")
	yMax1 := cw1.GetShape().BBox().Data()[4]
	// yMax 应从 ~300+线径 移到 ~500+线径
	if math.Abs((yMax1-yMax0)-200) > 20 {
		t.Fatalf("cw_0 did not follow stagger edit: yMax %v -> %v", yMax0, yMax1)
	}
	m2, ok := as1.Get("mast_2")
	if !ok {
		t.Fatal("mast_2 not found")
	}
	tr := m2.GetLocation().Trsf().Data()
	if math.Abs(tr[3]-105000) > 1e-6 {
		t.Fatalf("mast_2 location x wrong: %v", tr[3])
	}
}

// 支柱放置: 局部生成 + Location 与 WithPlace 直接烘焙的世界 bbox 一致
func TestAnchorMastPlacementMatchesWithPlace(t *testing.T) {
	mp := MastAssemblyParams{
		MastType: 1, MastHeight: 8000, CantileverType: 1, ArmDiameter: 60,
		Stagger: 300, ContactHeight: 5300, StructureHeight: 1400, SideOffset: 2900,
	}
	pos := [3]float64{50000, 2900, 0}
	dir := [3]float64{0, -1, 0}
	ref := CreateMastAssemblyWithPlace(mp, NewPoint3(pos),
		NewDir3FromXYZ(dir), NewDir3FromXYZ([3]float64{0, 0, 1})).BBox().Data()
	got := CreateMastAssembly(mp).Transformed(
		mastPlacementTrsf(AnchorMastLayout{Position: pos, Direction: dir})).BBox().Data()
	for i := range ref {
		if math.Abs(ref[i]-got[i]) > 1 {
			t.Fatalf("mast placement mismatch at bbox[%d]: %v vs %v", i, ref, got)
		}
	}
}

// ExportParametric → RebuildFromParametric 往返: 子件数量/名字一致, 几何确定性重建
func TestAnchorParametricRoundTrip(t *testing.T) {
	as, err := CreateAnchorSection(anchorTestInput())
	if err != nil {
		t.Fatalf("create anchor section failed: %v", err)
	}
	data, err := as.ExportParametric()
	if err != nil {
		t.Fatalf("ExportParametric failed: %v", err)
	}
	rebuilt, err := RebuildFromParametric(data)
	if err != nil {
		t.Fatalf("RebuildFromParametric failed: %v", err)
	}
	if rebuilt.GetName() != as.GetName() {
		t.Fatalf("root name mismatch: %q vs %q", rebuilt.GetName(), as.GetName())
	}
	names := func(a *Assembly) []string {
		var out []string
		for _, el := range a.GetElements() {
			out = append(out, el.GetName())
		}
		sort.Strings(out)
		return out
	}
	n0, n1 := names(as), names(rebuilt)
	if !reflect.DeepEqual(n0, n1) {
		t.Fatalf("element names mismatch:\n%v\n%v", n0, n1)
	}
	// 几何一致性: cw_0 bbox 相同, mast_2 放置相同
	cw0, _ := as.Get("cw_0")
	cw1, _ := rebuilt.Get("cw_0")
	b0, b1 := cw0.GetShape().BBox().Data(), cw1.GetShape().BBox().Data()
	for i := range b0 {
		if math.Abs(b0[i]-b1[i]) > 1e-6 {
			t.Fatalf("cw_0 bbox mismatch: %v vs %v", b0, b1)
		}
	}
	m0, _ := as.Get("mast_2")
	m1, _ := rebuilt.Get("mast_2")
	t0, t1 := m0.GetLocation().Trsf().Data(), m1.GetLocation().Trsf().Data()
	for i := range t0 {
		if math.Abs(t0[i]-t1[i]) > 1e-6 {
			t.Fatalf("mast_2 location mismatch: %v vs %v", t0, t1)
		}
	}
	// 重建树仍带配方, 可再次导出重建
	if _, ok := rebuilt.GetParametric("mast_2"); !ok {
		t.Fatal("rebuilt tree lost mast_2 parametric recipe")
	}
	data2, err := rebuilt.ExportParametric()
	if err != nil {
		t.Fatalf("re-export failed: %v", err)
	}
	if _, err := RebuildFromParametric(data2); err != nil {
		t.Fatalf("second round trip failed: %v", err)
	}
}
