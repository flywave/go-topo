package topo

import (
	"math"
	"testing"
)

func TestCreateSingleHookAnchor(t *testing.T) {
	shp := CreateSingleHookAnchor(SingleHookAnchorParams{
		BoltDiameter:       0.24,
		ExposedLength:      0.2,
		NutCount:           2,
		NutHeight:          0.075,
		NutOD:              0.6,
		WasherCount:        2,
		WasherShape:        WasherShapeTypeRound,
		WasherSize:         0.65,
		WasherThickness:    0.015,
		AnchorLength:       1.5,
		HookStraightLength: 0.6,
		HookDiameter:       0.6,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create single hook anchor")
	}
}

func TestCreateSingleHookAnchorWithPlace(t *testing.T) {
	pos := NewPoint3([3]float64{0, 0, 0})
	normal := NewDir3FromXYZ([3]float64{0, 0, 1})
	xDir := NewDir3FromXYZ([3]float64{1, 0, 0})
	shp := CreateSingleHookAnchorWithPlace(SingleHookAnchorParams{
		BoltDiameter:       0.24,
		ExposedLength:      0.2,
		NutCount:           2,
		NutHeight:          0.075,
		NutOD:              0.6,
		WasherCount:        2,
		WasherShape:        WasherShapeTypeRound,
		WasherSize:         0.65,
		WasherThickness:    0.015,
		AnchorLength:       1.5,
		HookStraightLength: 0.6,
		HookDiameter:       0.6,
	}, pos, normal, xDir)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create single hook anchor with place")
	}
}

func TestCreateTripleHookAnchor(t *testing.T) {
	shp := CreateTripleHookAnchor(TripleHookAnchorParams{
		BoltDiameter:        0.24,
		ExposedLength:       0.2,
		NutCount:            2,
		NutHeight:           0.1,
		NutOD:               0.6,
		WasherCount:         2,
		WasherShape:         WasherShapeTypeRound,
		WasherSize:          0.65,
		WasherThickness:     0.015,
		AnchorLength:        1.5,
		HookStraightLengthA: 0.6,
		HookStraightLengthB: 0.25,
		HookDiameter:        0.6,
		AnchorBarDiameter:   0.1,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create triple hook anchor")
	}
}

func TestCreateTripleHookAnchorWithPlace(t *testing.T) {
	pos := NewPoint3([3]float64{0, 0, 0})
	normal := NewDir3FromXYZ([3]float64{0, 0, 1})
	xDir := NewDir3FromXYZ([3]float64{1, 0, 0})
	shp := CreateTripleHookAnchorWithPlace(TripleHookAnchorParams{
		BoltDiameter:        0.24,
		ExposedLength:       0.2,
		NutCount:            2,
		NutHeight:           0.1,
		NutOD:               0.6,
		WasherCount:         2,
		WasherShape:         WasherShapeTypeRound,
		WasherSize:          0.65,
		WasherThickness:     0.015,
		AnchorLength:        1.5,
		HookStraightLengthA: 0.6,
		HookStraightLengthB: 0.25,
		HookDiameter:        0.6,
		AnchorBarDiameter:   0.1,
	}, pos, normal, xDir)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create triple hook anchor with place")
	}
}

func TestCreateRibbedAnchor(t *testing.T) {
	shp := CreateRibbedAnchor(RibbedAnchorParams{
		BoltDiameter:       0.2,
		ExposedLength:      0.40,
		NutCount:           0,
		NutHeight:          0.1,
		NutOD:              0.6,
		WasherCount:        0,
		WasherShape:        WasherShapeTypeRound,
		WasherSize:         0.65,
		WasherThickness:    0.015,
		AnchorLength:       1.5,
		BasePlateSize:      0.60,
		RibTopWidth:        0.1,
		RibBottomWidth:     0.2,
		BasePlateThickness: 0.030,
		RibHeight:          0.2,
		RibThickness:       0.025,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create ribbed anchor")
	}
}

func TestCreateRibbedAnchorWithPlace(t *testing.T) {
	pos := NewPoint3([3]float64{0, 0, 0})
	normal := NewDir3FromXYZ([3]float64{0, 0, 1})
	xDir := NewDir3FromXYZ([3]float64{1, 0, 0})
	shp := CreateRibbedAnchorWithPlace(RibbedAnchorParams{
		BoltDiameter:       0.2,
		ExposedLength:      0.40,
		NutCount:           0,
		NutHeight:          0.1,
		NutOD:              0.6,
		WasherCount:        0,
		WasherShape:        WasherShapeTypeRound,
		WasherSize:         0.65,
		WasherThickness:    0.015,
		AnchorLength:       1.5,
		BasePlateSize:      0.60,
		RibTopWidth:        0.1,
		RibBottomWidth:     0.2,
		BasePlateThickness: 0.030,
		RibHeight:          0.2,
		RibThickness:       0.025,
	}, pos, normal, xDir)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create ribbed anchor with place")
	}
}

func TestCreateNutAnchor(t *testing.T) {
	shp := CreateNutAnchor(NutAnchorParams{
		BoltDiameter:        0.2,
		ExposedLength:       0.40,
		NutCount:            2,
		NutHeight:           0.1,
		NutOD:               0.6,
		WasherCount:         2,
		WasherShape:         WasherShapeTypeRound,
		WasherSize:          0.65,
		WasherThickness:     0.015,
		AnchorLength:        1.5,
		BasePlateSize:       0.60,
		BasePlateThickness:  0.030,
		BoltToPlateDistance: 1.4,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create nut anchor")
	}
}

func TestCreateNutAnchorWithPlace(t *testing.T) {
	pos := NewPoint3([3]float64{0, 0, 0})
	normal := NewDir3FromXYZ([3]float64{0, 0, 1})
	xDir := NewDir3FromXYZ([3]float64{1, 0, 0})
	shp := CreateNutAnchorWithPlace(NutAnchorParams{
		BoltDiameter:        0.2,
		ExposedLength:       0.40,
		NutCount:            2,
		NutHeight:           0.1,
		NutOD:               0.6,
		WasherCount:         2,
		WasherShape:         WasherShapeTypeRound,
		WasherSize:          0.65,
		WasherThickness:     0.015,
		AnchorLength:        1.5,
		BasePlateSize:       0.60,
		BasePlateThickness:  0.030,
		BoltToPlateDistance: 1.4,
	}, pos, normal, xDir)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create nut anchor with place")
	}
}

func TestCreateTripleArmAnchor(t *testing.T) {
	shp := CreateTripleArmAnchor(TripleArmAnchorParams{
		BoltDiameter:      0.2,
		ExposedLength:     0.40,
		NutCount:          2,
		NutHeight:         0.1,
		NutOD:             0.6,
		WasherCount:       2,
		WasherShape:       WasherShapeTypeRound,
		WasherSize:        0.65,
		WasherThickness:   0.015,
		AnchorLength:      1.5,
		ArmDiameter:       0.12,
		ArmStraightLength: 0.6,
		ArmBendLength:     0.4,
		ArmBendAngle:      float32(math.Pi / 4),
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create triple arm anchor")
	}
}

func TestCreateTripleArmAnchorWithPlace(t *testing.T) {
	pos := NewPoint3([3]float64{0, 0, 0})
	normal := NewDir3FromXYZ([3]float64{0, 0, 1})
	xDir := NewDir3FromXYZ([3]float64{1, 0, 0})
	shp := CreateTripleArmAnchorWithPlace(TripleArmAnchorParams{
		BoltDiameter:      0.2,
		ExposedLength:     0.40,
		NutCount:          2,
		NutHeight:         0.1,
		NutOD:             0.6,
		WasherCount:       2,
		WasherShape:       WasherShapeTypeRound,
		WasherSize:        0.65,
		WasherThickness:   0.015,
		AnchorLength:      1.5,
		ArmDiameter:       0.12,
		ArmStraightLength: 0.6,
		ArmBendLength:     0.4,
		ArmBendAngle:      float32(math.Pi / 4),
	}, pos, normal, xDir)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create triple arm anchor with place")
	}
}

func TestCreatePositioningPlateAnchor(t *testing.T) {
	shp := CreatePositioningPlateAnchor(PositioningPlateAnchorParams{
		BoltDiameter:      0.2,
		ExposedLength:     0.40,
		NutCount:          2,
		NutHeight:         0.1,
		NutOD:             0.6,
		WasherCount:       2,
		WasherShape:       WasherShapeTypeRound,
		WasherSize:        0.65,
		WasherThickness:   0.015,
		AnchorLength:      1.5,
		PlateLength:       0.60,
		PlateThickness:    0.030,
		ToBaseDistance:    0.2,
		ToBottomDistance:  0.2,
		GroutHoleDiameter: 0.3,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create positioning plate anchor")
	}
}

func TestCreatePositioningPlateAnchorWithPlace(t *testing.T) {
	pos := NewPoint3([3]float64{0, 0, 0})
	normal := NewDir3FromXYZ([3]float64{0, 0, 1})
	xDir := NewDir3FromXYZ([3]float64{1, 0, 0})
	shp := CreatePositioningPlateAnchorWithPlace(PositioningPlateAnchorParams{
		BoltDiameter:      0.2,
		ExposedLength:     0.40,
		NutCount:          2,
		NutHeight:         0.1,
		NutOD:             0.6,
		WasherCount:       2,
		WasherShape:       WasherShapeTypeRound,
		WasherSize:        0.65,
		WasherThickness:   0.015,
		AnchorLength:      1.5,
		PlateLength:       0.60,
		PlateThickness:    0.030,
		ToBaseDistance:    0.2,
		ToBottomDistance:  0.2,
		GroutHoleDiameter: 0.3,
	}, pos, normal, xDir)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create positioning plate anchor with place")
	}
}

func TestCreateStubAngle(t *testing.T) {
	shp := CreateStubAngle(StubAngleParams{
		LegWidth:      0.1,
		Thickness:     0.01,
		Slope:         0.1,
		ExposedLength: 2.0,
		AnchorLength:  5.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create stub angle")
	}
}

func TestCreateStubAngleWithPlace(t *testing.T) {
	pos := NewPoint3([3]float64{0, 0, 0})
	normal := NewDir3FromXYZ([3]float64{0, 0, 1})
	xDir := NewDir3FromXYZ([3]float64{1, 0, 0})
	shp := CreateStubAngleWithPlace(StubAngleParams{
		LegWidth:      0.1,
		Thickness:     0.01,
		Slope:         0.1,
		ExposedLength: 2.0,
		AnchorLength:  5.0,
	}, pos, normal, xDir)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create stub angle with place")
	}
}

func TestCreateStubTube(t *testing.T) {
	shp := CreateStubTube(StubTubeParams{
		Diameter:      0.6,
		Thickness:     0.1,
		Slope:         0.1,
		ExposedLength: 2.0,
		AnchorLength:  10.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create stub tube")
	}
}

func TestCreateStubTubeSloped(t *testing.T) {
	shp := CreateStubTube(StubTubeParams{
		Diameter:      0.6,
		Thickness:     0.1,
		Slope:         0.2,
		ExposedLength: 2.0,
		AnchorLength:  10.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create sloped stub tube")
	}
}

func TestCreateStubTubeWithPlace(t *testing.T) {
	pos := NewPoint3([3]float64{0, 0, 0})
	normal := NewDir3FromXYZ([3]float64{0, 0, 1})
	xDir := NewDir3FromXYZ([3]float64{1, 0, 0})
	shp := CreateStubTubeWithPlace(StubTubeParams{
		Diameter:      0.6,
		Thickness:     0.1,
		Slope:         0.1,
		ExposedLength: 2.0,
		AnchorLength:  10.0,
	}, pos, normal, xDir)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create stub tube with place")
	}
}

func TestCreateUShapedRing(t *testing.T) {
	shp := CreateUShapedRing(UShapedRingParams{
		Thickness: 0.02,
		Height:    0.1,
		Radius:    0.08, // 必须 > (height+thickness)/2 = 0.06
		Length:    0.05,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create U-shaped ring")
	}
}

func TestCreateUShapedRingWithPlace(t *testing.T) {
	pos := NewPoint3([3]float64{0, 0, 0})
	normal := NewDir3FromXYZ([3]float64{0, 0, 1})
	xDir := NewDir3FromXYZ([3]float64{1, 0, 0})
	shp := CreateUShapedRingWithPlace(UShapedRingParams{
		Thickness: 0.02,
		Height:    0.1,
		Radius:    0.08, // 必须 > (height+thickness)/2 = 0.06
		Length:    0.05,
	}, pos, normal, xDir)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create U-shaped ring with place")
	}
}
