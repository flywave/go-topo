package topo

import (
	"math"
	"testing"
)

func TestProbeRing(t *testing.T) {
	shp := CreateRing(RingParams{RingRadius: 15.0, TubeRadius: 3.0, Angle: float32(math.Pi * 2.0)})
	if shp == nil {
		t.Fatal("nil")
	}
	t.Logf("IsNull=%v IsValid=%v", shp.IsNull(), shp.IsValid())
	shp2 := CreateRing(RingParams{RingRadius: 15.0, TubeRadius: 3.0, Angle: float32(math.Pi)})
	t.Logf("half angle: nil=%v IsNull=%v", shp2 == nil, shp2 != nil && shp2.IsNull())
}
