package topo

import (
	"testing"
)

func TestCreateTerminalBlock(t *testing.T) {
	shp := CreateTerminalBlock(TerminalBlockParams{
		Length:        100.0,
		Width:         50.0,
		Thickness:     10.0,
		ChamferLength: 5.0,
		ColumnSpacing: 15.0,
		RowSpacing:    20.0,
		HoleRadius:    3.0,
		ColumnCount:   3,
		RowCount:      4,
		BottomOffset:  20.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create terminal block")
	}
}

func TestCreateTerminalBlockExtreme(t *testing.T) {
	shp := CreateTerminalBlock(TerminalBlockParams{
		Length:        200.0,
		Width:         30.0,
		Thickness:     5.0,
		ChamferLength: 1.0,
		ColumnSpacing: 10.0,
		RowSpacing:    15.0,
		HoleRadius:    2.0,
		ColumnCount:   5,
		RowCount:      6,
		BottomOffset:  5.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create extreme terminal block")
	}
}

func TestCreateTerminalBlockWithPlace(t *testing.T) {
	pos := NewPoint3([3]float64{0, 0, 0})
	lDir := NewDir3FromXYZ([3]float64{1, 0, 0})
	wDir := NewDir3FromXYZ([3]float64{0, 1, 0})
	shp := CreateTerminalBlockWithPlace(TerminalBlockParams{
		Length:        100.0,
		Width:         50.0,
		Thickness:     10.0,
		ChamferLength: 5.0,
		ColumnSpacing: 15.0,
		RowSpacing:    20.0,
		HoleRadius:    3.0,
		ColumnCount:   3,
		RowCount:      4,
		BottomOffset:  20.0,
	}, pos, lDir, wDir)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create terminal block with place")
	}
}

func TestCreateRectangularFixedPlate(t *testing.T) {
	shp := CreateRectangularFixedPlate(RectangularFixedPlateParams{
		Length:        100.0,
		Width:         80.0,
		Thickness:     10.0,
		ColumnSpacing: 20.0,
		RowSpacing:    15.0,
		ColumnCount:   4,
		RowCount:      5,
		HasMiddleHole: true,
		HoleDiameter:  8.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create rectangular fixed plate")
	}
}

func TestCreateRectangularFixedPlateNoMiddle(t *testing.T) {
	shp := CreateRectangularFixedPlate(RectangularFixedPlateParams{
		Length:        120.0,
		Width:         120.0,
		Thickness:     8.0,
		ColumnSpacing: 25.0,
		RowSpacing:    20.0,
		ColumnCount:   3,
		RowCount:      5,
		HasMiddleHole: false,
		HoleDiameter:  6.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create rectangular fixed plate without middle hole")
	}
}

func TestCreateRectangularFixedPlateWithPlace(t *testing.T) {
	pos := NewPoint3([3]float64{0, 0, 0})
	lDir := NewDir3FromXYZ([3]float64{1, 0, 0})
	wDir := NewDir3FromXYZ([3]float64{0, 1, 0})
	shp := CreateRectangularFixedPlateWithPlace(RectangularFixedPlateParams{
		Length:        100.0,
		Width:         80.0,
		Thickness:     10.0,
		ColumnSpacing: 20.0,
		RowSpacing:    15.0,
		ColumnCount:   4,
		RowCount:      5,
		HasMiddleHole: true,
		HoleDiameter:  8.0,
	}, pos, lDir, wDir)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create rectangular fixed plate with place")
	}
}

func TestCreateCircularFixedPlate(t *testing.T) {
	shp := CreateCircularFixedPlate(CircularFixedPlateParams{
		Length:        200.0,
		Width:         200.0,
		Thickness:     12.0,
		RingRadius:    60.0,
		HoleCount:     8,
		HasMiddleHole: true,
		HoleDiameter:  15.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create circular fixed plate with middle hole")
	}
}

func TestCreateCircularFixedPlateNoMiddle(t *testing.T) {
	shp := CreateCircularFixedPlate(CircularFixedPlateParams{
		Length:        180.0,
		Width:         180.0,
		Thickness:     10.0,
		RingRadius:    50.0,
		HoleCount:     6,
		HasMiddleHole: false,
		HoleDiameter:  12.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create circular fixed plate without middle hole")
	}
}

func TestCreateCircularFixedPlateExtreme(t *testing.T) {
	shp := CreateCircularFixedPlate(CircularFixedPlateParams{
		Length:        100.0,
		Width:         100.0,
		Thickness:     5.0,
		RingRadius:    30.0,
		HoleCount:     12,
		HasMiddleHole: true,
		HoleDiameter:  8.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create extreme circular fixed plate")
	}
}

func TestCreateCircularFixedPlateWithPlace(t *testing.T) {
	pos := NewPoint3([3]float64{0, 0, 0})
	lDir := NewDir3FromXYZ([3]float64{1, 0, 0})
	wDir := NewDir3FromXYZ([3]float64{0, 1, 0})
	shp := CreateCircularFixedPlateWithPlace(CircularFixedPlateParams{
		Length:        200.0,
		Width:         200.0,
		Thickness:     12.0,
		RingRadius:    60.0,
		HoleCount:     8,
		HasMiddleHole: true,
		HoleDiameter:  15.0,
	}, pos, lDir, wDir)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create circular fixed plate with place")
	}
}
