package topo

import (
	"math"
	"testing"
)

func TestCreateCableJoint(t *testing.T) {
	shp := CreateCableJoint(CableJointParams{
		Length:         100.0,
		OuterDiameter:  30.0,
		TerminalLength: 20.0,
		InnerDiameter:  20.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create standard cable joint")
	}
}

func TestCreateCableJointShort(t *testing.T) {
	shp := CreateCableJoint(CableJointParams{
		Length:         50.0,
		OuterDiameter:  20.0,
		TerminalLength: 10.0,
		InnerDiameter:  15.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create short cable joint")
	}
}

func TestCreateCableJointLongTerminal(t *testing.T) {
	shp := CreateCableJoint(CableJointParams{
		Length:         150.0,
		OuterDiameter:  40.0,
		TerminalLength: 50.0,
		InnerDiameter:  30.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create long terminal cable joint")
	}
}

func TestCreateCableJointWithPlace(t *testing.T) {
	pos := NewPoint3([3]float64{0, 0, 0})
	dir := NewDir3FromXYZ([3]float64{0, 0, 1})
	xDir := NewDir3FromXYZ([3]float64{1, 0, 0})
	shp := CreateCableJointWithPlace(CableJointParams{
		Length:         100.0,
		OuterDiameter:  30.0,
		TerminalLength: 20.0,
		InnerDiameter:  20.0,
	}, pos, dir, xDir)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create cable joint with place")
	}
}

func TestCreateOpticalFiberBox(t *testing.T) {
	shp := CreateOpticalFiberBox(OpticalFiberBoxParams{
		Length: 300.0,
		Height: 150.0,
		Width:  200.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create optical fiber box")
	}
}

func TestCreateOpticalFiberBoxWithPlace(t *testing.T) {
	pos := NewPoint3([3]float64{0, 0, 0})
	dir := NewDir3FromXYZ([3]float64{0, 0, 1})
	xDir := NewDir3FromXYZ([3]float64{1, 0, 0})
	shp := CreateOpticalFiberBoxWithPlace(OpticalFiberBoxParams{
		Length: 300.0,
		Height: 150.0,
		Width:  200.0,
	}, pos, dir, xDir)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create optical fiber box with place")
	}
}

func TestCreateCableTerminalOutdoor(t *testing.T) {
	shp := CreateCableTerminal(CableTerminalParams{
		Sort:                   CableTerminalTypeOutdoor,
		Height:                 1000,
		TopDiameter:            200,
		BottomDiameter:         300,
		TailDiameter:           350,
		TailHeight:             50,
		SkirtCount:             18,
		UpperSkirtTopDiameter:    330,
		UpperSkirtBottomDiameter: 340,
		LowerSkirtTopDiameter:    380,
		LowerSkirtBottomDiameter: 400,
		SkirtSectionHeight:     40,
		UpperTerminalLength:    100,
		UpperTerminalDiameter:  80,
		LowerTerminalLength:    120,
		LowerTerminalDiameter:  100,
		Hole1Diameter:          20,
		Hole2Diameter:          20,
		Hole1Distance:          30,
		HoleSpacing:            40,
		FlangeHoleDiameter:     25,
		FlangeHoleSpacing:      400,
		FlangeWidth:            450,
		FlangeCenterHoleRadius: 75,
		FlangeChamferRadius:    10,
		FlangeOpeningWidth:     120,
		FlangeBoltHeight:       40,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create outdoor cable terminal")
	}
}

func TestCreateCableTerminalGIS(t *testing.T) {
	shp := CreateCableTerminal(CableTerminalParams{
		Sort:                   CableTerminalTypeGIS,
		Height:                 800,
		TopDiameter:            180,
		BottomDiameter:         220,
		UpperTerminalLength:    80,
		UpperTerminalDiameter:  70,
		LowerTerminalLength:    100,
		LowerTerminalDiameter:  90,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create GIS cable terminal")
	}
}

func TestCreateCableTerminalWithPlace(t *testing.T) {
	pos := NewPoint3([3]float64{0, 0, 0})
	dir := NewDir3FromXYZ([3]float64{0, 0, 1})
	shp := CreateCableTerminalWithPlace(CableTerminalParams{
		Sort:                   CableTerminalTypeOutdoor,
		Height:                 1000,
		TopDiameter:            200,
		BottomDiameter:         300,
		TailDiameter:           350,
		TailHeight:             50,
		SkirtCount:             18,
		UpperSkirtTopDiameter:    330,
		UpperSkirtBottomDiameter: 340,
		LowerSkirtTopDiameter:    380,
		LowerSkirtBottomDiameter: 400,
		SkirtSectionHeight:     40,
		UpperTerminalLength:    100,
		UpperTerminalDiameter:  80,
		LowerTerminalLength:    120,
		LowerTerminalDiameter:  100,
		Hole1Diameter:          20,
		Hole2Diameter:          20,
		Hole1Distance:          30,
		HoleSpacing:            40,
		FlangeHoleDiameter:     25,
		FlangeHoleSpacing:      400,
		FlangeWidth:            450,
		FlangeCenterHoleRadius: 75,
		FlangeChamferRadius:    10,
		FlangeOpeningWidth:     120,
		FlangeBoltHeight:       40,
	}, pos, dir)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create cable terminal with place")
	}
}

func TestCreateCableAccessoryDirectGround(t *testing.T) {
	shp := CreateCableAccessory(CableAccessoryParams{
		Type:              CableAccessoryTypeDirectGround,
		Length:            500.0,
		Width:             400.0,
		Height:            300.0,
		PortCount:         3,
		PortDiameter:      100.0,
		BackPanelDistance: 50.0,
		SidePanelDistance: 60.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create direct ground box")
	}
}

func TestCreateCableAccessoryProtectiveGround(t *testing.T) {
	shp := CreateCableAccessory(CableAccessoryParams{
		Type:              CableAccessoryTypeProtectiveGround,
		Length:            600.0,
		Width:             500.0,
		Height:            400.0,
		PortCount:         6,
		PortDiameter:      120.0,
		BackPanelDistance: 60.0,
		SidePanelDistance: 70.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create protective ground box")
	}
}

func TestCreateCableAccessoryWithPlace(t *testing.T) {
	pos := NewPoint3([3]float64{0, 0, 0})
	normal := NewDir3FromXYZ([3]float64{0, 0, 1})
	xDir := NewDir3FromXYZ([3]float64{1, 0, 0})
	shp := CreateCableAccessoryWithPlace(CableAccessoryParams{
		Type:              CableAccessoryTypeDirectGround,
		Length:            500.0,
		Width:             400.0,
		Height:            300.0,
		PortCount:         3,
		PortDiameter:      100.0,
		BackPanelDistance: 50.0,
		SidePanelDistance: 60.0,
	}, pos, normal, xDir)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create cable accessory with place")
	}
}

func TestCreateCableClampSingle(t *testing.T) {
	shp := CreateCableClamp(CableClampParams{
		Type:      CableClampSingle,
		Diameter:  50.0,
		Thickness: 10.0,
		Width:     30.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create single cable clamp")
	}
}

func TestCreateCableClampLinear(t *testing.T) {
	shp := CreateCableClamp(CableClampParams{
		Type:      CableClampLinear,
		Diameter:  60.0,
		Thickness: 12.0,
		Width:     40.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create linear cable clamp")
	}
}

func TestCreateCableClampContactTriple(t *testing.T) {
	shp := CreateCableClamp(CableClampParams{
		Type:      CableClampContactTriple,
		Diameter:  70.0,
		Thickness: 15.0,
		Width:     50.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create contact triple cable clamp")
	}
}

func TestCreateCableClampSeparateTriple(t *testing.T) {
	shp := CreateCableClamp(CableClampParams{
		Type:      CableClampSeparateTriple,
		Diameter:  80.0,
		Thickness: 18.0,
		Width:     60.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create separate triple cable clamp")
	}
}

func TestCreateCableClampWithPlace(t *testing.T) {
	pos := NewPoint3([3]float64{0, 0, 0})
	normal := NewDir3FromXYZ([3]float64{0, 0, 1})
	xDir := NewDir3FromXYZ([3]float64{1, 0, 0})
	shp := CreateCableClampWithPlace(CableClampParams{
		Type:      CableClampSingle,
		Diameter:  50.0,
		Thickness: 10.0,
		Width:     30.0,
	}, pos, normal, xDir)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create cable clamp with place")
	}
}

func TestCreateCableBracket(t *testing.T) {
	shp := CreateCableBracket(CableBracketParams{
		Length:        100.0,
		RootHeight:    50.0,
		RootWidth:     20.0,
		Width:         15.0,
		TopThickness:  5.0,
		RootThickness: 8.0,
		ColumnMountPoints: []Point3{
			NewPoint3([3]float64{10, -8.0, -10}),
			NewPoint3([3]float64{10, -8.0, -35}),
		},
		ClampMountPoints: []Point3{
			NewPoint3([3]float64{90, -5.0, -7.5}),
			NewPoint3([3]float64{50, -5.0, -7.5}),
		},
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create cable bracket")
	}
}

func TestCreateCableBracketWithPlace(t *testing.T) {
	pos := NewPoint3([3]float64{0, 0, 0})
	normal := NewDir3FromXYZ([3]float64{0, 0, 1})
	xDir := NewDir3FromXYZ([3]float64{1, 0, 0})
	shp := CreateCableBracketWithPlace(CableBracketParams{
		Length:        100.0,
		RootHeight:    50.0,
		RootWidth:     20.0,
		Width:         15.0,
		TopThickness:  5.0,
		RootThickness: 8.0,
		ColumnMountPoints: []Point3{
			NewPoint3([3]float64{10, -8.0, -10}),
			NewPoint3([3]float64{10, -8.0, -35}),
		},
		ClampMountPoints: []Point3{
			NewPoint3([3]float64{90, -5.0, -7.5}),
			NewPoint3([3]float64{50, -5.0, -7.5}),
		},
	}, pos, normal, xDir)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create cable bracket with place")
	}
}

func TestCreateCablePoleStraight(t *testing.T) {
	shp := CreateCablePole(CablePoleParams{
		Specification:  "GJ-DLLZ-1",
		Length:         200.0,
		ArcAngle:       math.Pi / 4,
		Width:          20.0,
		FixedLegLength: 20.0,
		FixedLegWidth:  10.0,
		Thickness:      5.0,
		MountPoints: []Point3{
			NewPoint3([3]float64{-20, 0, 50}),
			NewPoint3([3]float64{20, 0, 50}),
			NewPoint3([3]float64{-20, 0, 100}),
			NewPoint3([3]float64{20, 0, 100}),
			NewPoint3([3]float64{-20, 0, 150}),
			NewPoint3([3]float64{20, 0, 150}),
		},
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create cable pole")
	}
}

func TestCreateCablePoleArc(t *testing.T) {
	params := CablePoleParams{
		Specification:  "GJ-DLLZ-2",
		Length:         200.0,
		Radius:         50.0,
		ArcAngle:       math.Pi / 2,
		Width:          20.0,
		FixedLegLength: 16.0,
		FixedLegWidth:  8.0,
		Thickness:      3.0,
	}
	for i := 0; i < 6; i++ {
		angle := params.ArcAngle * float64(i) / 5.0
		x := params.Radius * math.Sin(angle)
		z := params.Radius * (1 - math.Cos(angle))
		params.MountPoints = append(params.MountPoints,
			NewPoint3([3]float64{x, params.Width/2 + 8, z}),
			NewPoint3([3]float64{x, -params.Width/2 - 8, z}),
		)
	}
	shp := CreateCablePole(params)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create arc cable pole")
	}
}

func TestCreateCablePoleWithPlace(t *testing.T) {
	pos := NewPoint3([3]float64{0, 0, 0})
	dir := NewDir3FromXYZ([3]float64{0, 0, 1})
	shp := CreateCablePoleWithPlace(CablePoleParams{
		Specification:  "GJ-DLLZ-1",
		Length:         200.0,
		ArcAngle:       math.Pi / 4,
		Width:          20.0,
		FixedLegLength: 20.0,
		FixedLegWidth:  10.0,
		Thickness:      5.0,
	}, pos, dir)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create cable pole with place")
	}
}

func TestCreateGroundFlatIron(t *testing.T) {
	shp := CreateGroundFlatIron(GroundFlatIronParams{
		Length:    100.0,
		Height:    20.0,
		Thickness: 10.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create ground flat iron")
	}
}

func TestCreateGroundFlatIronWithPlace(t *testing.T) {
	pos := NewPoint3([3]float64{0, 0, 0})
	normal := NewDir3FromXYZ([3]float64{0, 0, 1})
	xDir := NewDir3FromXYZ([3]float64{1, 0, 0})
	shp := CreateGroundFlatIronWithPlace(GroundFlatIronParams{
		Length:    100.0,
		Height:    20.0,
		Thickness: 10.0,
	}, pos, normal, xDir)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create ground flat iron with place")
	}
}

func TestCreateEmbeddedPart(t *testing.T) {
	shp := CreateEmbeddedPart(EmbeddedPartParams{
		Length:         100.0,
		Radius:         10.0,
		Height:         50.0,
		MaterialRadius: 5.0,
		LowerLength:    30.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create embedded part")
	}
}

func TestCreateEmbeddedPartWithPlace(t *testing.T) {
	pos := NewPoint3([3]float64{0, 0, 0})
	normal := NewDir3FromXYZ([3]float64{0, 0, 1})
	xDir := NewDir3FromXYZ([3]float64{1, 0, 0})
	shp := CreateEmbeddedPartWithPlace(EmbeddedPartParams{
		Length:         100.0,
		Radius:         10.0,
		Height:         50.0,
		MaterialRadius: 5.0,
		LowerLength:    30.0,
	}, pos, normal, xDir)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create embedded part with place")
	}
}
