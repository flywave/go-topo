package topo

import (
	"math"
	"testing"
)

func TestCreateTruncatedCone(t *testing.T) {
	shp := CreateTruncatedCone(TruncatedConeParams{
		TopRadius:    5.0,
		BottomRadius: 10.0,
		Height:       15.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create truncated cone")
	}
	if !shp.IsValid() {
		t.Fatal("Truncated cone is not valid")
	}
}

func TestCreateTruncatedConeExtreme(t *testing.T) {
	shp := CreateTruncatedCone(TruncatedConeParams{
		TopRadius:    0.1,
		BottomRadius: 20.0,
		Height:       30.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create extreme truncated cone")
	}
}

func TestCreateTruncatedConeWithPlace(t *testing.T) {
	base := NewPoint3([3]float64{0, 0, 0})
	axis := NewDir3FromXYZ([3]float64{0, 0, 1})
	shp := CreateTruncatedConeWithPlace(TruncatedConeParams{
		TopRadius:    5.0,
		BottomRadius: 10.0,
		Height:       15.0,
	}, base, axis)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create truncated cone with place")
	}
}

func TestCreateEccentricTruncatedCone(t *testing.T) {
	shp := CreateEccentricTruncatedCone(EccentricTruncatedConeParams{
		TopRadius:    5.0,
		BottomRadius: 10.0,
		Height:       15.0,
		TopXOffset:   2.0,
		TopYOffset:   3.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create eccentric truncated cone")
	}
}

func TestCreateEccentricTruncatedConeExtreme(t *testing.T) {
	shp := CreateEccentricTruncatedCone(EccentricTruncatedConeParams{
		TopRadius:    1.0,
		BottomRadius: 20.0,
		Height:       30.0,
		TopXOffset:   5.0,
		TopYOffset:   8.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create extreme eccentric truncated cone")
	}
}

func TestCreateEccentricTruncatedConeWithPlace(t *testing.T) {
	base := NewPoint3([3]float64{0, 0, 0})
	axis := NewDir3FromXYZ([3]float64{0, 0, 1})
	shp := CreateEccentricTruncatedConeWithPlace(EccentricTruncatedConeParams{
		TopRadius:    5.0,
		BottomRadius: 10.0,
		Height:       15.0,
		TopXOffset:   2.0,
		TopYOffset:   3.0,
	}, base, axis)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create eccentric truncated cone with place")
	}
}

func TestCreateRing(t *testing.T) {
	shp := CreateRing(RingParams{
		RingRadius: 20.0,
		TubeRadius: 5.0,
		Angle:      float32(math.Pi * 1.5),
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create ring")
	}
}

func TestCreateRingFull(t *testing.T) {
	shp := CreateRing(RingParams{
		RingRadius: 15.0,
		TubeRadius: 3.0,
		Angle:      float32(math.Pi * 2.0),
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create full ring")
	}
}

func TestCreateRingWithPlace(t *testing.T) {
	center := NewPoint3([3]float64{0, 0, 0})
	normal := NewDir3FromXYZ([3]float64{0, 0, 1})
	xDir := NewDir3FromXYZ([3]float64{1, 0, 0})
	shp := CreateRingWithPlace(RingParams{
		RingRadius: 20.0,
		TubeRadius: 5.0,
		Angle:      float32(math.Pi * 1.5),
	}, center, normal, xDir)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create ring with place")
	}
}

func TestCreateRectangularRing(t *testing.T) {
	shp := CreateRectangularRing(RectangularRingParams{
		TubeRadius:   5.0,
		FilletRadius: 0.0,
		Length:       100.0,
		Width:        80.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create rectangular ring")
	}
}

func TestCreateRectangularRingRound(t *testing.T) {
	shp := CreateRectangularRing(RectangularRingParams{
		TubeRadius:   5.0,
		FilletRadius: 12.0,
		Length:       100.0,
		Width:        80.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create round rectangular ring")
	}
}

func TestCreateRectangularRingWithPlace(t *testing.T) {
	center := NewPoint3([3]float64{0, 0, 0})
	normal := NewDir3FromXYZ([3]float64{0, 0, 1})
	xDir := NewDir3FromXYZ([3]float64{1, 0, 0})
	shp := CreateRectangularRingWithPlace(RectangularRingParams{
		TubeRadius:   5.0,
		FilletRadius: 0.0,
		Length:       100.0,
		Width:        80.0,
	}, center, normal, xDir)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create rectangular ring with place")
	}
}

func TestCreateEllipticRing(t *testing.T) {
	shp := CreateEllipticRing(EllipticRingParams{
		TubeRadius:  3.0,
		MajorRadius: 20.0,
		MinorRadius: 10.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create elliptic ring")
	}
}

func TestCreateEllipticRingExtreme(t *testing.T) {
	shp := CreateEllipticRing(EllipticRingParams{
		TubeRadius:  1.0,
		MajorRadius: 30.0,
		MinorRadius: 5.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create extreme elliptic ring")
	}
}

func TestCreateEllipticRingWithPlace(t *testing.T) {
	center := NewPoint3([3]float64{0, 0, 0})
	normal := NewDir3FromXYZ([3]float64{0, 0, 1})
	xDir := NewDir3FromXYZ([3]float64{1, 0, 0})
	shp := CreateEllipticRingWithPlace(EllipticRingParams{
		TubeRadius:  3.0,
		MajorRadius: 20.0,
		MinorRadius: 10.0,
	}, center, normal, xDir)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create elliptic ring with place")
	}
}

func TestCreateCircularGasket(t *testing.T) {
	shp := CreateCircularGasket(CircularGasketParams{
		OuterRadius: 20.0,
		InnerRadius: 15.0,
		Height:      5.0,
		Angle:       float32(math.Pi * 1.5),
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create circular gasket")
	}
}

func TestCreateCircularGasketFull(t *testing.T) {
	shp := CreateCircularGasket(CircularGasketParams{
		OuterRadius: 25.0,
		InnerRadius: 20.0,
		Height:      8.0,
		Angle:       float32(math.Pi * 2.0),
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create full circular gasket")
	}
}

func TestCreateCircularGasketWithPlace(t *testing.T) {
	center := NewPoint3([3]float64{0, 0, 0})
	normal := NewDir3FromXYZ([3]float64{0, 0, 1})
	xDir := NewDir3FromXYZ([3]float64{1, 0, 0})
	shp := CreateCircularGasketWithPlace(CircularGasketParams{
		OuterRadius: 20.0,
		InnerRadius: 15.0,
		Height:      5.0,
		Angle:       float32(math.Pi * 1.5),
	}, center, normal, xDir)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create circular gasket with place")
	}
}

func TestCreateTableGasket(t *testing.T) {
	shp := CreateTableGasket(TableGasketParams{
		TopRadius:   15.0,
		OuterRadius: 20.0,
		InnerRadius: 10.0,
		Height:      6.0,
		Angle:       float32(math.Pi * 1.5),
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create table gasket")
	}
}

func TestCreateTableGasketFull(t *testing.T) {
	shp := CreateTableGasket(TableGasketParams{
		TopRadius:   18.0,
		OuterRadius: 25.0,
		InnerRadius: 12.0,
		Height:      8.0,
		Angle:       float32(math.Pi * 2.0),
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create full table gasket")
	}
}

func TestCreateTableGasketWithPlace(t *testing.T) {
	center := NewPoint3([3]float64{0, 0, 0})
	normal := NewDir3FromXYZ([3]float64{0, 0, 1})
	xDir := NewDir3FromXYZ([3]float64{1, 0, 0})
	shp := CreateTableGasketWithPlace(TableGasketParams{
		TopRadius:   15.0,
		OuterRadius: 20.0,
		InnerRadius: 10.0,
		Height:      6.0,
		Angle:       float32(math.Pi * 1.5),
	}, center, normal, xDir)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create table gasket with place")
	}
}

func TestCreateSquareGasket(t *testing.T) {
	shp := CreateSquareGasket(SquareGasketParams{
		OuterLength: 30.0,
		OuterWidth:  20.0,
		InnerLength: 25.0,
		InnerWidth:  15.0,
		Height:      5.0,
		CornerType:  1,
		CornerParam: 0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create square gasket")
	}
}

func TestCreateSquareGasketRoundCorner(t *testing.T) {
	shp := CreateSquareGasket(SquareGasketParams{
		OuterLength: 40.0,
		OuterWidth:  30.0,
		InnerLength: 15.0,
		InnerWidth:  10.0,
		Height:      8.0,
		CornerType:  2,
		CornerParam: 3.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create round corner square gasket")
	}
}

func TestCreateSquareGasketCutCorner(t *testing.T) {
	shp := CreateSquareGasket(SquareGasketParams{
		OuterLength: 40.0,
		OuterWidth:  30.0,
		InnerLength: 15.0,
		InnerWidth:  10.0,
		Height:      8.0,
		CornerType:  3,
		CornerParam: 5.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create cut corner square gasket")
	}
}

func TestCreateSquareGasketWithPlace(t *testing.T) {
	center := NewPoint3([3]float64{0, 0, 0})
	normal := NewDir3FromXYZ([3]float64{0, 0, 1})
	xDir := NewDir3FromXYZ([3]float64{1, 0, 0})
	shp := CreateSquareGasketWithPlace(SquareGasketParams{
		OuterLength: 30.0,
		OuterWidth:  20.0,
		InnerLength: 25.0,
		InnerWidth:  15.0,
		Height:      5.0,
		CornerType:  1,
		CornerParam: 0,
	}, center, normal, xDir)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create square gasket with place")
	}
}
