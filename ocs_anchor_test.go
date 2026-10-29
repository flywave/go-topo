package topo

import (
	"testing"
)

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
