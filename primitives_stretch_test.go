package topo

import (
	"testing"
)

func TestCreateStretchedBodyTriangle(t *testing.T) {
	shp := CreateStretchedBody(StretchedBodyParams{
		Points: []Point3{
			NewPoint3([3]float64{0, 0, 0}),
			NewPoint3([3]float64{10, 0, 0}),
			NewPoint3([3]float64{5, 8, 0}),
		},
		Normal: NewDir3FromXYZ([3]float64{0, 0, 1}),
		Length: 15.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create triangle stretched body")
	}
}

func TestCreateStretchedBodyQuadrilateral(t *testing.T) {
	shp := CreateStretchedBody(StretchedBodyParams{
		Points: []Point3{
			NewPoint3([3]float64{0, 0, 0}),
			NewPoint3([3]float64{20, 0, 0}),
			NewPoint3([3]float64{20, 10, 0}),
			NewPoint3([3]float64{0, 10, 0}),
		},
		Normal: NewDir3FromXYZ([3]float64{0, 1, 1}),
		Length: 25.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create quadrilateral stretched body")
	}
}

func TestCreateStretchedBodyPentagon(t *testing.T) {
	shp := CreateStretchedBody(StretchedBodyParams{
		Points: []Point3{
			NewPoint3([3]float64{0, 0, 0}),
			NewPoint3([3]float64{15, 0, 0}),
			NewPoint3([3]float64{20, 10, 0}),
			NewPoint3([3]float64{10, 15, 0}),
			NewPoint3([3]float64{-5, 8, 0}),
		},
		Normal: NewDir3FromXYZ([3]float64{1, 0, 1}),
		Length: 12.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create pentagon stretched body")
	}
}

func TestCreateStretchedBodyWithPlace(t *testing.T) {
	base := NewPoint3([3]float64{0, 0, 0})
	axis := NewDir3FromXYZ([3]float64{0, 0, 1})
	shp := CreateStretchedBodyWithPlace(StretchedBodyParams{
		Points: []Point3{
			NewPoint3([3]float64{0, 0, 0}),
			NewPoint3([3]float64{10, 0, 0}),
			NewPoint3([3]float64{5, 8, 0}),
		},
		Normal: NewDir3FromXYZ([3]float64{0, 0, 1}),
		Length: 15.0,
	}, base, axis)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create stretched body with place")
	}
}

func TestCreatePorcelainBushing(t *testing.T) {
	shp := CreatePorcelainBushing(PorcelainBushingParams{
		Height:           100.0,
		Radius:           10.0,
		BigSkirtRadius:   15.0,
		SmallSkirtRadius: 12.0,
		Count:            20,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create porcelain bushing")
	}
}

func TestCreatePorcelainBushingWithPlace(t *testing.T) {
	base := NewPoint3([3]float64{0, 0, 0})
	axis := NewDir3FromXYZ([3]float64{0, 0, 1})
	shp := CreatePorcelainBushingWithPlace(PorcelainBushingParams{
		Height:           100.0,
		Radius:           10.0,
		BigSkirtRadius:   15.0,
		SmallSkirtRadius: 12.0,
		Count:            20,
	}, base, axis)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create porcelain bushing with place")
	}
}

func TestCreateConePorcelainBushing(t *testing.T) {
	shp := CreateConePorcelainBushing(ConePorcelainBushingParams{
		Height:             100.0,
		BottomRadius:       15.0,
		TopRadius:          10.0,
		BottomSkirtRadius1: 20.0,
		BottomSkirtRadius2: 18.0,
		TopSkirtRadius1:    15.0,
		TopSkirtRadius2:    12.0,
		Count:              20,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create cone porcelain bushing")
	}
}

func TestCreateConePorcelainBushingWithPlace(t *testing.T) {
	base := NewPoint3([3]float64{0, 0, 0})
	axis := NewDir3FromXYZ([3]float64{0, 0, 1})
	shp := CreateConePorcelainBushingWithPlace(ConePorcelainBushingParams{
		Height:             100.0,
		BottomRadius:       15.0,
		TopRadius:          10.0,
		BottomSkirtRadius1: 20.0,
		BottomSkirtRadius2: 18.0,
		TopSkirtRadius1:    15.0,
		TopSkirtRadius2:    12.0,
		Count:              20,
	}, base, axis)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create cone porcelain bushing with place")
	}
}

func TestCreateInsulatorString(t *testing.T) {
	shp := CreateInsulatorString(InsulatorStringParams{
		Count:            2,
		Spacing:          30.0,
		InsulatorCount:   22,
		Height:           5.0,
		BigSkirtRadius:   8.0,
		SmallSkirtRadius: 6.0,
		Radius:           2,
		FrontLength:      15.0,
		BackLength:       10.0,
		SplitCount:       2,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create insulator string")
	}
}

func TestCreateInsulatorStringSingle(t *testing.T) {
	shp := CreateInsulatorString(InsulatorStringParams{
		Count:            1,
		Spacing:          0.0,
		InsulatorCount:   22,
		Height:           4.0,
		BigSkirtRadius:   7.0,
		SmallSkirtRadius: 5.0,
		Radius:           2,
		FrontLength:      6.0,
		BackLength:       5.0,
		SplitCount:       2,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create single insulator string")
	}
}

func TestCreateInsulatorStringWithPlace(t *testing.T) {
	pos := NewPoint3([3]float64{0, 0, 0})
	dir := NewDir3FromXYZ([3]float64{0, 0, 1})
	up := NewDir3FromXYZ([3]float64{0, 1, 0})
	shp := CreateInsulatorStringWithPlace(InsulatorStringParams{
		Count:            2,
		Spacing:          30.0,
		InsulatorCount:   22,
		Height:           5.0,
		BigSkirtRadius:   8.0,
		SmallSkirtRadius: 6.0,
		Radius:           2,
		FrontLength:      15.0,
		BackLength:       10.0,
		SplitCount:       2,
	}, pos, dir, up)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create insulator string with place")
	}
}

func TestCreateVTypeInsulator(t *testing.T) {
	shp := CreateVTypeInsulator(VTypeInsulatorParams{
		FrontSpacing:     50.0,
		BackSpacing:      20.0,
		InsulatorCount:   22,
		Height:           5.0,
		Radius:           2.0,
		BigSkirtRadius:   6.0,
		SmallSkirtRadius: 5.0,
		FrontLength:      10.0,
		BackLength:       8.0,
		SplitCount:       2,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create V-type insulator")
	}
}

func TestCreateVTypeInsulatorAlternative(t *testing.T) {
	shp := CreateVTypeInsulator(VTypeInsulatorParams{
		FrontSpacing:     40.0,
		BackSpacing:      15.0,
		InsulatorCount:   6,
		Height:           4.0,
		Radius:           2.5,
		BigSkirtRadius:   5.0,
		SmallSkirtRadius: 4.0,
		FrontLength:      8.0,
		BackLength:       6.0,
		SplitCount:       1,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create alternative V-type insulator")
	}
}

func TestCreateVTypeInsulatorWithPlace(t *testing.T) {
	pos := NewPoint3([3]float64{0, 0, 0})
	dir := NewDir3FromXYZ([3]float64{0, 0, 1})
	up := NewDir3FromXYZ([3]float64{0, 1, 0})
	shp := CreateVTypeInsulatorWithPlace(VTypeInsulatorParams{
		FrontSpacing:     50.0,
		BackSpacing:      20.0,
		InsulatorCount:   22,
		Height:           5.0,
		Radius:           2.0,
		BigSkirtRadius:   6.0,
		SmallSkirtRadius: 5.0,
		FrontLength:      10.0,
		BackLength:       8.0,
		SplitCount:       2,
	}, pos, dir, up)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create V-type insulator with place")
	}
}
