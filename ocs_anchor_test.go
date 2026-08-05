package topo

import (
	"testing"
)

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
