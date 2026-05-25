package topo

import (
	"testing"
)

func TestCreateCompositeInsulatorSuspensionCeramic(t *testing.T) {
	shp := CreateCompositeInsulator(InsulatorCompositeParams{
		Type:           "XWP-70",
		SubNum:         1,
		SubType:        0,
		ULinkLength:    0,
		Weight:         5.2,
		FittingLengths: FittingLengths{LeftUpper: 0.7, RightUpper: 0.7, LeftLower: 1, RightLower: 1},
		MultiLink:      MultiLink{Count: 1, Spacing: 0, Arrangement: InsulatorArrangementVertical},
		Insulator: InsulatorParams{
			RadiusData: float32(0.475),
			Height:     10.146,
			LeftCount:  20,
			RightCount: 20,
			Material:   InsulatorMaterialCeramic,
		},
		GradingRing:    GradingRing{Count: 1, Position: 0.5, Height: 0.03, Radius: 0.15},
		Application:    InsulatorApplicationConductor,
		StringType:     InsulatorStringTypeSuspension,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create suspension insulator string")
	}
}

func TestCreateCompositeInsulatorSuspensionWithULink(t *testing.T) {
	shp := CreateCompositeInsulator(InsulatorCompositeParams{
		Type:           "XWP-70",
		SubNum:         1,
		SubType:        0,
		ULinkLength:    2,
		Weight:         5.2,
		FittingLengths: FittingLengths{LeftUpper: 0.7, RightUpper: 0.7, LeftLower: 1, RightLower: 1},
		MultiLink:      MultiLink{Count: 1, Spacing: 0, Arrangement: InsulatorArrangementVertical},
		Insulator: InsulatorParams{
			RadiusData: float32(0.475),
			Height:     10.146,
			LeftCount:  20,
			RightCount: 20,
			Material:   InsulatorMaterialCeramic,
		},
		GradingRing:    GradingRing{Count: 1, Position: 0.5, Height: 0.03, Radius: 0.15},
		Application:    InsulatorApplicationConductor,
		StringType:     InsulatorStringTypeSuspension,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create suspension insulator string with U-link")
	}
}

func TestCreateCompositeInsulatorVTypeTension(t *testing.T) {
	shp := CreateCompositeInsulator(InsulatorCompositeParams{
		Type:           "FXBW-110/100",
		SubNum:         2,
		SubType:        1,
		SplitDistance:   400,
		VAngleLeft:     40,
		VAngleRight:    30,
		Weight:         8.5,
		FittingLengths: FittingLengths{LeftUpper: 0.7, RightUpper: 0.7, LeftLower: 1, RightLower: 1},
		MultiLink:      MultiLink{Count: 1, Spacing: 0, Arrangement: InsulatorArrangementHorizontal},
		Insulator: InsulatorParams{
			IsComposite: true,
			RadiusData: CompositeInsulatorParams{
				MajorRadius: 0.47,
				MinorRadius: 0.55,
				Gap:         0.4,
			},
			Height:     20.146,
			LeftCount:  20,
			RightCount: 20,
			Material:   InsulatorMaterialComposite,
		},
		GradingRing:    GradingRing{Count: 2, Position: 0.4, Height: 0.04, Radius: 0.2},
		Application:    InsulatorApplicationGroundWire,
		StringType:     InsulatorStringTypeSuspension,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create V-type tension insulator string")
	}
}

func TestCreateCompositeInsulatorWithPlace(t *testing.T) {
	pos := NewPoint3([3]float64{0, 0, 0})
	dir := NewDir3FromXYZ([3]float64{0, 0, 1})
	shp := CreateCompositeInsulatorWithPlace(InsulatorCompositeParams{
		Type:           "XWP-70",
		SubNum:         1,
		SubType:        0,
		ULinkLength:    0,
		Weight:         5.2,
		FittingLengths: FittingLengths{LeftUpper: 0.7, RightUpper: 0.7, LeftLower: 1, RightLower: 1},
		MultiLink:      MultiLink{Count: 1, Spacing: 0, Arrangement: InsulatorArrangementVertical},
		Insulator: InsulatorParams{
			RadiusData: float32(0.475),
			Height:     10.146,
			LeftCount:  20,
			RightCount: 20,
			Material:   InsulatorMaterialCeramic,
		},
		GradingRing:    GradingRing{Count: 1, Position: 0.5, Height: 0.03, Radius: 0.15},
		Application:    InsulatorApplicationConductor,
		StringType:     InsulatorStringTypeSuspension,
	}, pos, dir)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create composite insulator with place")
	}
}


