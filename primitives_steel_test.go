package topo

import (
	"testing"
)

func TestCreateAngleSteel(t *testing.T) {
	shp := CreateAngleSteel(AngleSteelParams{
		L1:     60.0,
		L2:     40.0,
		X:      5.0,
		Length: 200.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create angle steel")
	}
}

func TestCreateAngleSteelExtreme(t *testing.T) {
	shp := CreateAngleSteel(AngleSteelParams{
		L1:     100.0,
		L2:     30.0,
		X:      3.0,
		Length: 500.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create extreme angle steel")
	}
}

func TestCreateAngleSteelWithPlace(t *testing.T) {
	pos := NewPoint3([3]float64{0, 0, 0})
	xDir := NewDir3FromXYZ([3]float64{1, 0, 0})
	longEdgeDir := NewDir3FromXYZ([3]float64{0, 0, 1})
	shp := CreateAngleSteelWithPlace(AngleSteelParams{
		L1:     60.0,
		L2:     40.0,
		X:      5.0,
		Length: 200.0,
	}, pos, xDir, longEdgeDir)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create angle steel with place")
	}
}

func TestCreateIShapedSteel(t *testing.T) {
	shp := CreateIShapedSteel(IShapedSteelParams{
		Height:          200.0,
		FlangeWidth:     150.0,
		WebThickness:    12.0,
		FlangeThickness: 8.0,
		Length:          1000.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create I-shaped steel")
	}
}

func TestCreateIShapedSteelWithPlace(t *testing.T) {
	pos := NewPoint3([3]float64{0, 0, 0})
	xDir := NewDir3FromXYZ([3]float64{1, 0, 0})
	zDir := NewDir3FromXYZ([3]float64{0, 0, 1})
	shp := CreateIShapedSteelWithPlace(IShapedSteelParams{
		Height:          200.0,
		FlangeWidth:     150.0,
		WebThickness:    12.0,
		FlangeThickness: 8.0,
		Length:          1000.0,
	}, pos, xDir, zDir)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create I-shaped steel with place")
	}
}

func TestCreateChannelSteel(t *testing.T) {
	shp := CreateChannelSteel(ChannelSteelParams{
		Height:          100.0,
		FlangeWidth:     50.0,
		WebThickness:    6.0,
		FlangeThickness: 8.0,
		Length:          500.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create channel steel")
	}
}

func TestCreateChannelSteelExtreme(t *testing.T) {
	shp := CreateChannelSteel(ChannelSteelParams{
		Height:          200.0,
		FlangeWidth:     30.0,
		WebThickness:    4.0,
		FlangeThickness: 5.0,
		Length:          1000.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create extreme channel steel")
	}
}

func TestCreateChannelSteelWithPlace(t *testing.T) {
	pos := NewPoint3([3]float64{0, 0, 0})
	xDir := NewDir3FromXYZ([3]float64{1, 0, 0})
	zDir := NewDir3FromXYZ([3]float64{0, 0, 1})
	shp := CreateChannelSteelWithPlace(ChannelSteelParams{
		Height:          100.0,
		FlangeWidth:     50.0,
		WebThickness:    6.0,
		FlangeThickness: 8.0,
		Length:          500.0,
	}, pos, xDir, zDir)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create channel steel with place")
	}
}

func TestCreateTSteel(t *testing.T) {
	shp := CreateTSteel(TSteelParams{
		Height:          120.0,
		Width:           60.0,
		WebThickness:    8.0,
		FlangeThickness: 10.0,
		Length:          600.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create T-steel")
	}
}

func TestCreateTSteelExtreme(t *testing.T) {
	shp := CreateTSteel(TSteelParams{
		Height:          150.0,
		Width:           40.0,
		WebThickness:    5.0,
		FlangeThickness: 6.0,
		Length:          800.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create extreme T-steel")
	}
}

func TestCreateTSteelWithPlace(t *testing.T) {
	pos := NewPoint3([3]float64{0, 0, 0})
	xDir := NewDir3FromXYZ([3]float64{1, 0, 0})
	zDir := NewDir3FromXYZ([3]float64{0, 0, 1})
	shp := CreateTSteelWithPlace(TSteelParams{
		Height:          120.0,
		Width:           60.0,
		WebThickness:    8.0,
		FlangeThickness: 10.0,
		Length:          600.0,
	}, pos, xDir, zDir)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create T-steel with place")
	}
}
