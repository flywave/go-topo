package topo

import (
	"testing"
)

func TestRetarderQuick(t *testing.T) {
	params := RetarderPointParams{
		Side:             1,
		DeviceType:       1,
		MountType:        1,
		Height:           200,
		BodyDiameter:     70,
		CapDiameter:      82,
		CapHeight:        28,
		TransitionHeight: 18,
		ArmLength:        85,
		ArmWidth:         28,
		ArmThickness:     14,
		BoltDiameter:     18,
		PortDiameter:     18,
	}
	s := CreateRetarderPoint(params)
	if s == nil {
		t.Fatal("nil shape")
	}
}
