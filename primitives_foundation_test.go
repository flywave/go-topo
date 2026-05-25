package topo

import (
	"testing"
)

func TestCreateBoredPileBase(t *testing.T) {
	shp := CreateBoredPileBase(BoredPileParams{
		H1:       100.0,
		H2:       30.0,
		H3:       50.0,
		H4:       3.0,
		D:        20.0,
		Diameter: 5.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create bored pile base")
	}
}

func TestCreateBoredPileBaseWithPlace(t *testing.T) {
	pos := NewPoint3([3]float64{0, 0, 0})
	dir := NewDir3FromXYZ([3]float64{0, 0, 1})
	shp := CreateBoredPileBaseWithPlace(BoredPileParams{
		H1:       100.0,
		H2:       30.0,
		H3:       50.0,
		H4:       3.0,
		D:        20.0,
		Diameter: 5.0,
	}, pos, dir)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create bored pile base with place")
	}
}

func TestCreatePileCapBase(t *testing.T) {
	shp := CreatePileCapBase(PileCapParams{
		H1:        100.0,
		H2:        30.0,
		H3:        50.0,
		H4:        40.0,
		H5:        20.0,
		H6:        3.0,
		D:         20.0,
		Diameter:  5.0,
		B:         15.0,
		B1:        200.0,
		L1:        300.0,
		E1:        10.0,
		E2:        5.0,
		CS:        0,
		ZCount:    3,
		ZPosArray: []Point3{NewPoint3([3]float64{0, 0, 0}), NewPoint3([3]float64{100, 0, 0}), NewPoint3([3]float64{0, 100, 0})},
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create pile cap base")
	}
}

func TestCreatePileCapBaseWithPlace(t *testing.T) {
	pos := NewPoint3([3]float64{0, 0, 0})
	dir := NewDir3FromXYZ([3]float64{0, 0, 1})
	shp := CreatePileCapBaseWithPlace(PileCapParams{
		H1:       100.0,
		H2:       30.0,
		H3:       50.0,
		H4:       40.0,
		H5:       20.0,
		H6:       3.0,
		D:        20.0,
		Diameter: 5.0,
		B:        15.0,
		B1:       200.0,
		L1:       300.0,
		E1:       10.0,
		E2:       5.0,
		CS:       0,
		ZCount:   3,
		ZPosArray: []Point3{
			NewPoint3([3]float64{0, 0, 0}),
			NewPoint3([3]float64{100, 0, 0}),
			NewPoint3([3]float64{0, 100, 0}),
		},
	}, pos, dir)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create pile cap base with place")
	}
}

func TestCreateRockAnchorBase(t *testing.T) {
	shp := CreateRockAnchorBase(RockAnchorParams{
		H1:        20.0,
		H2:        50.0,
		Diameter:  5.0,
		B1:        100.0,
		L1:        150.0,
		ZCount:    4,
		ZPosArray: []Point3{NewPoint3([3]float64{-40, -60, 0}), NewPoint3([3]float64{40, -60, 0}), NewPoint3([3]float64{40, 60, 0}), NewPoint3([3]float64{-40, 60, 0})},
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create rock anchor base")
	}
}

func TestCreateRockAnchorBaseWithPlace(t *testing.T) {
	pos := NewPoint3([3]float64{0, 0, 0})
	dir := NewDir3FromXYZ([3]float64{0, 0, 1})
	shp := CreateRockAnchorBaseWithPlace(RockAnchorParams{
		H1:       20.0,
		H2:       50.0,
		Diameter: 5.0,
		B1:       100.0,
		L1:       150.0,
		ZCount:   4,
		ZPosArray: []Point3{
			NewPoint3([3]float64{-40, -60, 0}),
			NewPoint3([3]float64{40, -60, 0}),
			NewPoint3([3]float64{40, 60, 0}),
			NewPoint3([3]float64{-40, 60, 0}),
		},
	}, pos, dir)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create rock anchor base with place")
	}
}

func TestCreateRockPileCapBase(t *testing.T) {
	shp := CreateRockPileCapBase(RockPileCapParams{
		H1:     40.0,
		H2:     20.0,
		H3:     50.0,
		D:      5.0,
		B:      15.0,
		B1:     200.0,
		L1:     300.0,
		E1:     10.0,
		E2:     5.0,
		CS:     0,
		ZCount: 4,
		ZPosArray: []Point3{
			NewPoint3([3]float64{-50, -50, 0}),
			NewPoint3([3]float64{50, -50, 0}),
			NewPoint3([3]float64{50, 50, 0}),
			NewPoint3([3]float64{-50, 50, 0}),
		},
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create rock pile cap base")
	}
}

func TestCreateRockPileCapBaseWithPlace(t *testing.T) {
	pos := NewPoint3([3]float64{0, 0, 0})
	dir := NewDir3FromXYZ([3]float64{0, 0, 1})
	shp := CreateRockPileCapBaseWithPlace(RockPileCapParams{
		H1:     40.0,
		H2:     20.0,
		H3:     50.0,
		D:      5.0,
		B:      15.0,
		B1:     200.0,
		L1:     300.0,
		E1:     10.0,
		E2:     5.0,
		CS:     0,
		ZCount: 4,
		ZPosArray: []Point3{
			NewPoint3([3]float64{-50, -50, 0}),
			NewPoint3([3]float64{50, -50, 0}),
			NewPoint3([3]float64{50, 50, 0}),
			NewPoint3([3]float64{-50, 50, 0}),
		},
	}, pos, dir)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create rock pile cap base with place")
	}
}

func TestCreateEmbeddedRockAnchorBase(t *testing.T) {
	shp := CreateEmbeddedRockAnchorBase(EmbeddedRockAnchorParams{
		H1:       100.0,
		H2:       30.0,
		H3:       50.0,
		Diameter: 5.0,
		D:        20.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create embedded rock anchor base")
	}
}

func TestCreateEmbeddedRockAnchorBaseWithPlace(t *testing.T) {
	pos := NewPoint3([3]float64{0, 0, 0})
	dir := NewDir3FromXYZ([3]float64{0, 0, 1})
	shp := CreateEmbeddedRockAnchorBaseWithPlace(EmbeddedRockAnchorParams{
		H1:       100.0,
		H2:       30.0,
		H3:       50.0,
		Diameter: 5.0,
		D:        20.0,
	}, pos, dir)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create embedded rock anchor base with place")
	}
}

func TestCreateInclinedRockAnchorBase(t *testing.T) {
	shp := CreateInclinedRockAnchorBase(InclinedRockAnchorParams{
		H1:       20.0,
		H2:       50.0,
		Diameter: 5.0,
		D:        15.0,
		B:        100.0,
		L:        150.0,
		E1:       10.0,
		E2:       5.0,
		Alpha1:   15.0,
		Alpha2:   10.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create inclined rock anchor base")
	}
}

func TestCreateInclinedRockAnchorBaseWithPlace(t *testing.T) {
	pos := NewPoint3([3]float64{0, 0, 0})
	dir := NewDir3FromXYZ([3]float64{0, 0, 1})
	shp := CreateInclinedRockAnchorBaseWithPlace(InclinedRockAnchorParams{
		H1:       20.0,
		H2:       50.0,
		Diameter: 5.0,
		D:        15.0,
		B:        100.0,
		L:        150.0,
		E1:       10.0,
		E2:       5.0,
		Alpha1:   15.0,
		Alpha2:   10.0,
	}, pos, dir)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create inclined rock anchor base with place")
	}
}

func TestCreateExcavatedBaseStraight(t *testing.T) {
	shp := CreateExcavatedBase(ExcavatedBaseParams{
		H1:       100.0,
		H2:       30.0,
		H3:       50.0,
		D:        20.0,
		Diameter: 5.0,
		Alpha1:   0.0,
		Alpha2:   0.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create straight excavated base")
	}
}

func TestCreateExcavatedBaseSloped(t *testing.T) {
	shp := CreateExcavatedBase(ExcavatedBaseParams{
		H1:       150.0,
		H2:       40.0,
		H3:       60.0,
		D:        25.0,
		Diameter: 8.0,
		Alpha1:   15.0,
		Alpha2:   10.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create sloped excavated base")
	}
}

func TestCreateExcavatedBaseWithPlace(t *testing.T) {
	pos := NewPoint3([3]float64{0, 0, 0})
	dir := NewDir3FromXYZ([3]float64{0, 0, 1})
	shp := CreateExcavatedBaseWithPlace(ExcavatedBaseParams{
		H1:       100.0,
		H2:       30.0,
		H3:       50.0,
		D:        20.0,
		Diameter: 5.0,
		Alpha1:   0.0,
		Alpha2:   0.0,
	}, pos, dir)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create excavated base with place")
	}
}

func TestCreateStepBase3Step(t *testing.T) {
	shp := CreateStepBase(StepBaseParams{
		H:  150.0,
		H1: 50.0,
		H2: 50.0,
		H3: 50.0,
		B:  30.0,
		B1: 100.0,
		B2: 150.0,
		B3: 200.0,
		L1: 100.0,
		L2: 150.0,
		L3: 200.0,
		N:  3,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create 3-step base")
	}
}

func TestCreateStepBase2Step(t *testing.T) {
	shp := CreateStepBase(StepBaseParams{
		H:  100.0,
		H1: 40.0,
		H2: 60.0,
		B:  20.0,
		B1: 80.0,
		B2: 120.0,
		L1: 80.0,
		L2: 120.0,
		N:  2,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create 2-step base")
	}
}

func TestCreateStepBaseWithPlace(t *testing.T) {
	pos := NewPoint3([3]float64{0, 0, 0})
	dir := NewDir3FromXYZ([3]float64{0, 0, 1})
	shp := CreateStepBaseWithPlace(StepBaseParams{
		H:  150.0,
		H1: 50.0,
		H2: 50.0,
		H3: 50.0,
		B:  30.0,
		B1: 100.0,
		B2: 150.0,
		B3: 200.0,
		L1: 100.0,
		L2: 150.0,
		L3: 200.0,
		N:  3,
	}, pos, dir)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create step base with place")
	}
}

func TestCreateStepPlateBase3Step(t *testing.T) {
	shp := CreateStepPlateBase(StepPlateBaseParams{
		H:      150.0,
		H1:     50.0,
		H2:     50.0,
		H3:     50.0,
		B:      30.0,
		L1:     100.0,
		L2:     150.0,
		B1:     200.0,
		B2:     300.0,
		Alpha1: 15.0,
		Alpha2: 10.0,
		N:      3,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create 3-step plate base")
	}
}

func TestCreateStepPlateBase2Step(t *testing.T) {
	shp := CreateStepPlateBase(StepPlateBaseParams{
		H:      100.0,
		H1:     40.0,
		H2:     60.0,
		B:      20.0,
		L1:     80.0,
		L2:     120.0,
		B1:     180.0,
		B2:     200.0,
		Alpha1: 0.0,
		Alpha2: 0.0,
		N:      2,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create 2-step plate base")
	}
}

func TestCreateStepPlateBaseWithPlace(t *testing.T) {
	pos := NewPoint3([3]float64{0, 0, 0})
	dir := NewDir3FromXYZ([3]float64{0, 0, 1})
	shp := CreateStepPlateBaseWithPlace(StepPlateBaseParams{
		H:      150.0,
		H1:     50.0,
		H2:     50.0,
		H3:     50.0,
		B:      30.0,
		L1:     100.0,
		L2:     150.0,
		B1:     200.0,
		B2:     300.0,
		Alpha1: 15.0,
		Alpha2: 10.0,
		N:      3,
	}, pos, dir)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create step plate base with place")
	}
}

func TestCreateSlopedBaseBase(t *testing.T) {
	shp := CreateSlopedBaseBase(SlopedBaseBaseParams{
		H1:     100.0,
		H2:     30.0,
		H3:     50.0,
		B:      15.0,
		L1:     200.0,
		L2:     150.0,
		B1:     100.0,
		B2:     80.0,
		Alpha1: 15.0,
		Alpha2: 10.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create sloped base base")
	}
}

func TestCreateSlopedBaseBaseWithPlace(t *testing.T) {
	pos := NewPoint3([3]float64{0, 0, 0})
	dir := NewDir3FromXYZ([3]float64{0, 0, 1})
	shp := CreateSlopedBaseBaseWithPlace(SlopedBaseBaseParams{
		H1:     100.0,
		H2:     30.0,
		H3:     50.0,
		B:      15.0,
		L1:     200.0,
		L2:     150.0,
		B1:     100.0,
		B2:     80.0,
		Alpha1: 15.0,
		Alpha2: 10.0,
	}, pos, dir)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create sloped base base with place")
	}
}

func TestCreateCompositeCaissonBase(t *testing.T) {
	shp := CreateCompositeCaissonBase(CompositeCaissonBaseParams{
		H1: 100.0,
		H2: 30.0,
		H3: 50.0,
		H4: 200.0,
		B:  15.0,
		D:  200.0,
		T:  15.0,
		B1: 200.0,
		B2: 250.0,
		L1: 300.0,
		L2: 350.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create composite caisson base")
	}
}

func TestCreateCompositeCaissonBaseExtreme(t *testing.T) {
	shp := CreateCompositeCaissonBase(CompositeCaissonBaseParams{
		H1: 150.0,
		H2: 40.0,
		H3: 60.0,
		H4: 30.0,
		B:  20.0,
		D:  15.0,
		T:  1.5,
		B1: 250.0,
		B2: 300.0,
		L1: 350.0,
		L2: 400.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create extreme composite caisson base")
	}
}

func TestCreateCompositeCaissonBaseWithPlace(t *testing.T) {
	pos := NewPoint3([3]float64{0, 0, 0})
	dir := NewDir3FromXYZ([3]float64{0, 0, 1})
	shp := CreateCompositeCaissonBaseWithPlace(CompositeCaissonBaseParams{
		H1: 100.0,
		H2: 30.0,
		H3: 50.0,
		H4: 200.0,
		B:  15.0,
		D:  200.0,
		T:  15.0,
		B1: 200.0,
		B2: 250.0,
		L1: 300.0,
		L2: 350.0,
	}, pos, dir)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create composite caisson base with place")
	}
}

func TestCreateRaftBase(t *testing.T) {
	shp := CreateRaftBase(RaftBaseParams{
		H1:    100.0,
		H2:    100.0,
		H3:    50.0,
		Beam1: 30.0,
		Beam2: 30.0,
		B1:    500.0,
		B2:    400.0,
		L1:    800.0,
		L2:    600.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create raft base")
	}
}

func TestCreateRaftBaseWithPlace(t *testing.T) {
	pos := NewPoint3([3]float64{0, 0, 0})
	dir := NewDir3FromXYZ([3]float64{0, 0, 1})
	shp := CreateRaftBaseWithPlace(RaftBaseParams{
		H1:    100.0,
		H2:    100.0,
		H3:    50.0,
		Beam1: 30.0,
		Beam2: 30.0,
		B1:    500.0,
		B2:    400.0,
		L1:    800.0,
		L2:    600.0,
	}, pos, dir)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create raft base with place")
	}
}

func TestCreateDirectBuriedBaseCircular(t *testing.T) {
	shp := CreateDirectBuriedBase(DirectBuriedBaseParams{
		H1:       500.0,
		H2:       100.0,
		D:        600.0,
		Diameter: 300.0,
		T:        20.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create direct buried base with circular plate")
	}
}

func TestCreateDirectBuriedBaseSquare(t *testing.T) {
	shp := CreateDirectBuriedBase(DirectBuriedBaseParams{
		H1:       500.0,
		H2:       100.0,
		Diameter: 300.0,
		B:        600.0,
		T:        20.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create direct buried base with square plate")
	}
}

func TestCreateDirectBuriedBaseNoPlate(t *testing.T) {
	shp := CreateDirectBuriedBase(DirectBuriedBaseParams{
		H1:       500.0,
		Diameter: 300.0,
		T:        20.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create direct buried base without plate")
	}
}

func TestCreateDirectBuriedBaseWithPlace(t *testing.T) {
	pos := NewPoint3([3]float64{0, 0, 0})
	dir := NewDir3FromXYZ([3]float64{0, 0, 1})
	shp := CreateDirectBuriedBaseWithPlace(DirectBuriedBaseParams{
		H1:       500.0,
		H2:       100.0,
		D:        600.0,
		Diameter: 300.0,
		T:        20.0,
	}, pos, dir)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create direct buried base with place")
	}
}

func TestCreateSteelSleeveBaseCircular(t *testing.T) {
	shp := CreateSteelSleeveBase(SteelSleeveBaseParams{
		H1: 500.0,
		H2: 100.0,
		H3: 150.0,
		H4: 50.0,
		D:  300.0,
		D1: 600.0,
		D2: 400.0,
		T:  20.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create steel sleeve base with circular expansion")
	}
}

func TestCreateSteelSleeveBaseSquare(t *testing.T) {
	shp := CreateSteelSleeveBase(SteelSleeveBaseParams{
		H1: 500.0,
		H2: 100.0,
		H3: 150.0,
		H4: 50.0,
		D:  300.0,
		T:  20.0,
		B1: 600.0,
		B2: 400.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create steel sleeve base with square expansion")
	}
}

func TestCreateSteelSleeveBaseSimple(t *testing.T) {
	shp := CreateSteelSleeveBase(SteelSleeveBaseParams{
		H1: 500.0,
		H4: 50.0,
		D:  300.0,
		T:  20.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create simple steel sleeve base")
	}
}

func TestCreateSteelSleeveBaseWithPlace(t *testing.T) {
	pos := NewPoint3([3]float64{0, 0, 0})
	dir := NewDir3FromXYZ([3]float64{0, 0, 1})
	shp := CreateSteelSleeveBaseWithPlace(SteelSleeveBaseParams{
		H1: 500.0,
		H2: 100.0,
		H3: 150.0,
		H4: 50.0,
		D:  300.0,
		D1: 600.0,
		D2: 400.0,
		T:  20.0,
	}, pos, dir)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create steel sleeve base with place")
	}
}

func TestCreatePrecastColumnBase(t *testing.T) {
	shp := CreatePrecastColumnBase(PrecastColumnBaseParams{
		H1: 500.0,
		H2: 200.0,
		H3: 300.0,
		D:  100.0,
		B1: 200.0,
		B2: 400.0,
		L1: 300.0,
		L2: 600.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create precast column base")
	}
}

func TestCreatePrecastColumnBaseWithPlace(t *testing.T) {
	pos := NewPoint3([3]float64{0, 0, 0})
	dir := NewDir3FromXYZ([3]float64{0, 0, 1})
	shp := CreatePrecastColumnBaseWithPlace(PrecastColumnBaseParams{
		H1: 500.0,
		H2: 200.0,
		H3: 300.0,
		D:  100.0,
		B1: 200.0,
		B2: 400.0,
		L1: 300.0,
		L2: 600.0,
	}, pos, dir)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create precast column base with place")
	}
}

func TestCreatePrecastPinnedBaseWithClamp(t *testing.T) {
	shp := CreatePrecastPinnedBase(PrecastPinnedBaseParams{
		H1: 500.0,
		H2: 200.0,
		H3: 200.0,
		D:  100.0,
		B1: 200.0,
		B2: 400.0,
		L1: 300.0,
		L2: 600.0,
		B:  40.0,
		H:  40.0,
		L:  200.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create precast pinned base with clamp")
	}
}

func TestCreatePrecastPinnedBaseWithoutClamp(t *testing.T) {
	shp := CreatePrecastPinnedBase(PrecastPinnedBaseParams{
		H1: 500.0,
		H2: 200.0,
		H3: 200.0,
		D:  100.0,
		B1: 200.0,
		B2: 400.0,
		L1: 300.0,
		L2: 600.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create precast pinned base without clamp")
	}
}

func TestCreatePrecastPinnedBaseWithPlace(t *testing.T) {
	pos := NewPoint3([3]float64{0, 0, 0})
	dir := NewDir3FromXYZ([3]float64{0, 0, 1})
	shp := CreatePrecastPinnedBaseWithPlace(PrecastPinnedBaseParams{
		H1: 500.0,
		H2: 200.0,
		H3: 200.0,
		D:  100.0,
		B1: 200.0,
		B2: 400.0,
		L1: 300.0,
		L2: 600.0,
		B:  40.0,
		H:  40.0,
		L:  200.0,
	}, pos, dir)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create precast pinned base with place")
	}
}

func TestCreatePrecastMetalSupportBase(t *testing.T) {
	shp := CreatePrecastMetalSupportBase(PrecastMetalSupportBaseParams{
		H1:    40.0,
		H2:    400.0,
		H3:    20.0,
		H4:    20.0,
		B1:    800.0,
		B2:    600.0,
		Beam1: 30.0,
		Beam2: 30.0,
		L1:    1000.0,
		L2:    800.0,
		S1:    40.0,
		S2:    20.0,
		N1:    3,
		N2:    9,
		HX:    []float32{100.0, 100.0, 100.0},
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create precast metal support base")
	}
}

func TestCreatePrecastMetalSupportBaseWithPlace(t *testing.T) {
	pos := NewPoint3([3]float64{0, 0, 0})
	dir := NewDir3FromXYZ([3]float64{0, 0, 1})
	shp := CreatePrecastMetalSupportBaseWithPlace(PrecastMetalSupportBaseParams{
		H1:    40.0,
		H2:    400.0,
		H3:    20.0,
		H4:    20.0,
		B1:    800.0,
		B2:    600.0,
		Beam1: 30.0,
		Beam2: 30.0,
		L1:    1000.0,
		L2:    800.0,
		S1:    40.0,
		S2:    20.0,
		N1:    3,
		N2:    9,
		HX:    []float32{100.0, 100.0, 100.0},
	}, pos, dir)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create precast metal support base with place")
	}
}

func TestCreatePrecastConcreteSupportBase(t *testing.T) {
	shp := CreatePrecastConcreteSupportBase(PrecastConcreteSupportBaseParams{
		H1:    40.0,
		H2:    400.0,
		H3:    20.0,
		H4:    20.0,
		H5:    20.0,
		Beam1: 30.0,
		Beam2: 40.0,
		Beam3: 20.0,
		B1:    800.0,
		B2:    600.0,
		L1:    1000.0,
		L2:    800.0,
		S1:    40.0,
		N1:    9,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create precast concrete support base")
	}
}

func TestCreatePrecastConcreteSupportBaseWithPlace(t *testing.T) {
	pos := NewPoint3([3]float64{0, 0, 0})
	dir := NewDir3FromXYZ([3]float64{0, 0, 1})
	shp := CreatePrecastConcreteSupportBaseWithPlace(PrecastConcreteSupportBaseParams{
		H1:    40.0,
		H2:    400.0,
		H3:    20.0,
		H4:    20.0,
		H5:    20.0,
		Beam1: 30.0,
		Beam2: 40.0,
		Beam3: 20.0,
		B1:    800.0,
		B2:    600.0,
		L1:    1000.0,
		L2:    800.0,
		S1:    40.0,
		N1:    9,
	}, pos, dir)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create precast concrete support base with place")
	}
}
