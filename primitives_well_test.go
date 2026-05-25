package topo

import (
	"testing"
)

func TestCreateLiftingEye(t *testing.T) {
	shp := CreateLiftingEye(LiftingEyeParams{
		Height:       100.0,
		RingRadius:   25.0,
		PipeDiameter: 10.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create lifting eye")
	}
}

func TestCreateTunnelWellStraight(t *testing.T) {
	shp := CreateTunnelWell(TunnelWellParams{
		Type:              TunnelWellStraight,
		Length:            800.0,
		Width:             150.0,
		Height:            180.0,
		TopThickness:      20.0,
		BottomThickness:   25.0,
		OuterWallThickness: 30.0,
		CushionExtension:  10.0,
		CushionThickness:  15.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create straight tunnel well")
	}
}

func TestCreateTunnelWellCircular(t *testing.T) {
	shp := CreateTunnelWell(TunnelWellParams{
		Type:               TunnelWellStraightTunnel,
		Length:             150.0,
		Width:              120.0,
		Height:             140.0,
		Radius:             60.0,
		TopThickness:       15.0,
		BottomThickness:    20.0,
		LeftSectionType:    ConnectionSectionCircular,
		LeftLength:         800.0,
		LeftWidth:          100.0,
		LeftHeight:         140.0,
		RightSectionType:   ConnectionSectionCircular,
		RightLength:        600.0,
		RightWidth:         80.0,
		RightHeight:        100.0,
		OuterWallThickness: 20.0,
		InnerWallThickness: 20.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create circular tunnel well")
	}
}

func TestCreateTunnelWellRectangular(t *testing.T) {
	shp := CreateTunnelWell(TunnelWellParams{
		Type:               TunnelWellStraightTunnel,
		Length:             150.0,
		Width:              120.0,
		Height:             140.0,
		Radius:             60.0,
		TopThickness:       15.0,
		BottomThickness:    20.0,
		LeftSectionType:    ConnectionSectionRectangular,
		LeftLength:         800.0,
		LeftWidth:          100.0,
		LeftHeight:         140.0,
		RightSectionType:   ConnectionSectionRectangular,
		RightLength:        600.0,
		RightWidth:         80.0,
		RightHeight:        100.0,
		OuterWallThickness: 20.0,
		InnerWallThickness: 20.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create rectangular tunnel well")
	}
}

func TestCreateTunnelWellHorseshoe(t *testing.T) {
	shp := CreateTunnelWell(TunnelWellParams{
		Type:               TunnelWellStraightTunnel,
		Length:             150.0,
		Width:              120.0,
		Height:             140.0,
		Radius:             50.0,
		TopThickness:       15.0,
		BottomThickness:    20.0,
		LeftSectionType:    ConnectionSectionHorseshoe,
		LeftLength:         800.0,
		LeftWidth:          100.0,
		LeftHeight:         140.0,
		LeftArcHeight:      30.0,
		RightSectionType:   ConnectionSectionHorseshoe,
		RightLength:        600.0,
		RightWidth:         80.0,
		RightHeight:        100.0,
		RightArcHeight:     25.0,
		OuterWallThickness: 20.0,
		InnerWallThickness: 20.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create horseshoe tunnel well")
	}
}

func TestCreateCornerWell(t *testing.T) {
	shp := CreateCornerWell(CornerWellParams{
		LeftLength:       800.0,
		RightLength:      600.0,
		Width:            150.0,
		Height:           180.0,
		TopThickness:     20.0,
		BottomThickness:  25.0,
		WallThickness:    30.0,
		Angle:            90.0,
		CornerRadius:     100.0,
		CushionExtension: 10.0,
		CushionThickness: 15.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create corner well")
	}
}

func TestCreateCornerWell120Deg(t *testing.T) {
	shp := CreateCornerWell(CornerWellParams{
		LeftLength:       800.0,
		RightLength:      600.0,
		Width:            150.0,
		Height:           180.0,
		TopThickness:     20.0,
		BottomThickness:  25.0,
		WallThickness:    30.0,
		Angle:            120.0,
		CornerRadius:     100.0,
		CushionExtension: 10.0,
		CushionThickness: 15.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create corner well 120deg")
	}
}

func TestCreateCornerWellLargeRadius(t *testing.T) {
	shp := CreateCornerWell(CornerWellParams{
		LeftLength:       800.0,
		RightLength:      600.0,
		Width:            150.0,
		Height:           180.0,
		TopThickness:     20.0,
		BottomThickness:  25.0,
		WallThickness:    30.0,
		Angle:            90.0,
		CornerRadius:     150.0,
		CushionExtension: 10.0,
		CushionThickness: 15.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create corner well large radius")
	}
}

func TestCreateThreeWayWorkingWellRound(t *testing.T) {
	shp := CreateThreeWayWell(ThreeWayWellParams{
		Ctype:            ThreeWayWellWorking,
		CornerType:       CornerStyleRounded,
		ShaftType:        ShaftStyleRectangular,
		Length:           200.0,
		Width:            80.0,
		Height:           60.0,
		CornerRadius:     30.0,
		Angle:            90.0,
		BranchLength:     100.0,
		BranchWidth:      80.0,
		TopThickness:     10.0,
		BottomThickness:  10.0,
		OuterWallThickness: 5.0,
		InnerWallThickness: 3.0,
		CushionExtension: 10.0,
		CushionThickness: 15.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create round corner three way working well")
	}
}

func TestCreateThreeWayWorkingWellAngled(t *testing.T) {
	shp := CreateThreeWayWell(ThreeWayWellParams{
		Ctype:            ThreeWayWellWorking,
		CornerType:       CornerStyleAngled,
		ShaftType:        ShaftStyleRectangular,
		Length:           200.0,
		Width:            80.0,
		Height:           60.0,
		CornerLength:     20.0,
		CornerWidth:      20.0,
		Angle:            90.0,
		BranchLength:     100.0,
		BranchWidth:      80.0,
		TopThickness:     10.0,
		BottomThickness:  10.0,
		OuterWallThickness: 5.0,
		InnerWallThickness: 3.0,
		CushionExtension: 10.0,
		CushionThickness: 15.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create angled corner three way working well")
	}
}

func TestCreateThreeWayWorkingWellChamferRound(t *testing.T) {
	shp := CreateThreeWayWell(ThreeWayWellParams{
		Ctype:            ThreeWayWellWorking,
		CornerType:       CornerStyleRounded,
		ShaftType:        ShaftStyleRectangular,
		Length:           200.0,
		Width:            80.0,
		Height:           60.0,
		CornerRadius:     80.0,
		Angle:            70.0,
		BranchLength:     100.0,
		BranchLeftLength: 30.0,
		BranchWidth:      80.0,
		TopThickness:     10.0,
		BottomThickness:  10.0,
		OuterWallThickness: 5.0,
		InnerWallThickness: 3.0,
		CushionExtension: 5.0,
		CushionThickness: 5.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create chamfer round corner three way working well")
	}
}

func TestCreateThreeWayOpenCutTunnel(t *testing.T) {
	shp := CreateThreeWayWell(ThreeWayWellParams{
		Ctype:                  ThreeWayWellOpenCut,
		CornerType:             CornerStyleRounded,
		ShaftType:              ShaftStyleRectangular,
		Length:                 200.0,
		Width:                  80.0,
		Height:                 60.0,
		CornerRadius:           30.0,
		Angle:                  90.0,
		BranchLength:           100.0,
		BranchWidth:            80.0,
		TopThickness:           10.0,
		BottomThickness:        10.0,
		LeftSectionStyle:       ConnectionSectionRectangular,
		LeftSectionLength:      60.0,
		LeftSectionWidth:       80.0,
		LeftSectionHeight:      90.0,
		LeftSectionArcHeight:   15.0,
		RightSectionStyle:      ConnectionSectionRectangular,
		RightSectionLength:     60.0,
		RightSectionWidth:      80.0,
		RightSectionHeight:     90.0,
		RightSectionArcHeight:  15.0,
		BranchSectionStyle:     ConnectionSectionHorseshoe,
		BranchSectionLength:    80.0,
		BranchSectionWidth:     80.0,
		BranchSectionHeight:    50.0,
		BranchSectionArcHeight: 15.0,
		OuterWallThickness:     5.0,
		InnerWallThickness:     3.0,
		IsDoubleShaft:          false,
		DoubleShaftSpacing:     0.0,
		OuterWallExtension:     10.0,
		InnerWallExtension:     5.0,
		CushionExtension:       10.0,
		CushionThickness:       10.0,
		InnerBottomThickness:   18.0,
		OuterBottomThickness:   20.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create three way open cut tunnel")
	}
}

func TestCreateThreeWayUndergroundTunnel(t *testing.T) {
	shp := CreateThreeWayWell(ThreeWayWellParams{
		Ctype:                  ThreeWayWellUnderground,
		CornerType:             CornerStyleRounded,
		ShaftType:              ShaftStyleCircular,
		Length:                 200.0,
		Width:                  80.0,
		Height:                 60.0,
		ShaftRadius:            80.0,
		CornerRadius:           30.0,
		CornerLength:           40.0,
		CornerWidth:            35.0,
		BranchLength:           120.0,
		BranchLeftLength:       80.0,
		BranchWidth:            100.0,
		TopThickness:           20.0,
		BottomThickness:        25.0,
		LeftSectionStyle:       ConnectionSectionRectangular,
		LeftSectionLength:      60.0,
		LeftSectionWidth:       80.0,
		LeftSectionHeight:      90.0,
		LeftSectionArcHeight:   15.0,
		RightSectionStyle:      ConnectionSectionRectangular,
		RightSectionLength:     60.0,
		RightSectionWidth:      80.0,
		RightSectionHeight:     90.0,
		RightSectionArcHeight:  15.0,
		BranchSectionStyle:     ConnectionSectionHorseshoe,
		BranchSectionLength:    80.0,
		BranchSectionWidth:     80.0,
		BranchSectionHeight:    50.0,
		BranchSectionArcHeight: 15.0,
		OuterWallThickness:     5.0,
		InnerWallThickness:     3.0,
		IsDoubleShaft:          false,
		DoubleShaftSpacing:     0.0,
		OuterWallExtension:     10.0,
		InnerWallExtension:     5.0,
		CushionExtension:       15.0,
		CushionThickness:       10.0,
		InnerBottomThickness:   18.0,
		OuterBottomThickness:   20.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create three way underground tunnel")
	}
}

func TestCreateThreeWayDoubleShaftTunnel(t *testing.T) {
	shp := CreateThreeWayWell(ThreeWayWellParams{
		Ctype:                  ThreeWayWellUnderground,
		CornerType:             CornerStyleRounded,
		ShaftType:              ShaftStyleCircular,
		Length:                 200.0,
		Width:                  80.0,
		Height:                 60.0,
		ShaftRadius:            80.0,
		CornerRadius:           30.0,
		CornerLength:           40.0,
		CornerWidth:            35.0,
		BranchLength:           120.0,
		BranchLeftLength:       80.0,
		BranchWidth:            100.0,
		TopThickness:           20.0,
		BottomThickness:        25.0,
		LeftSectionStyle:       ConnectionSectionRectangular,
		LeftSectionLength:      60.0,
		LeftSectionWidth:       80.0,
		LeftSectionHeight:      90.0,
		LeftSectionArcHeight:   15.0,
		RightSectionStyle:      ConnectionSectionRectangular,
		RightSectionLength:     60.0,
		RightSectionWidth:      80.0,
		RightSectionHeight:     90.0,
		RightSectionArcHeight:  15.0,
		BranchSectionStyle:     ConnectionSectionHorseshoe,
		BranchSectionLength:    80.0,
		BranchSectionWidth:     80.0,
		BranchSectionHeight:    50.0,
		BranchSectionArcHeight: 15.0,
		OuterWallThickness:     5.0,
		InnerWallThickness:     3.0,
		IsDoubleShaft:          true,
		DoubleShaftSpacing:     0.0,
		OuterWallExtension:     10.0,
		InnerWallExtension:     5.0,
		CushionExtension:       15.0,
		CushionThickness:       10.0,
		InnerBottomThickness:   18.0,
		OuterBottomThickness:   20.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create three way double shaft tunnel")
	}
}

func TestCreateFourWayWorkingWellRound(t *testing.T) {
	shp := CreateFourWayWell(FourWayWellParams{
		Ctype:              FourWayWellWorking,
		Length:             200.0,
		Width:              80.0,
		Height:             60.0,
		CornerStyle:        CornerStyleRounded,
		CornerRadius:       30.0,
		BranchLength:       100.0,
		BranchWidth:        80.0,
		TopThickness:       10.0,
		BottomThickness:    10.0,
		OuterWallThickness: 5.0,
		InnerWallThickness: 3.0,
		CushionExtension:   10.0,
		CushionThickness:   15.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create round corner four way working well")
	}
}

func TestCreateFourWayWorkingWellAngled(t *testing.T) {
	shp := CreateFourWayWell(FourWayWellParams{
		Ctype:              FourWayWellWorking,
		Length:             200.0,
		Width:              80.0,
		Height:             60.0,
		CornerStyle:        CornerStyleAngled,
		CornerLength:       20.0,
		CornerWidth:        20.0,
		BranchLength:       100.0,
		BranchWidth:        80.0,
		TopThickness:       10.0,
		BottomThickness:    10.0,
		OuterWallThickness: 5.0,
		InnerWallThickness: 3.0,
		CushionExtension:   10.0,
		CushionThickness:   15.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create angled corner four way working well")
	}
}

func TestCreateFourWayOpenCutTunnel(t *testing.T) {
	shp := CreateFourWayWell(FourWayWellParams{
		Ctype:           FourWayWellOpenCut,
		Length:          200.0,
		Width:           80.0,
		Height:          60.0,
		CornerStyle:     CornerStyleRounded,
		CornerRadius:    30.0,
		BranchLength:    100.0,
		BranchWidth:     80.0,
		TopThickness:    10.0,
		BottomThickness: 10.0,
		LeftSection: FourWayWellSection{
			SectionType: ConnectionSectionRectangular,
			Length:      60.0,
			Width:       80.0,
			Height:      90.0,
			ArcHeight:   15.0,
		},
		RightSection: FourWayWellSection{
			SectionType: ConnectionSectionRectangular,
			Length:      60.0,
			Width:       80.0,
			Height:      90.0,
			ArcHeight:   15.0,
		},
		BranchSection1: FourWayWellSection{
			SectionType: ConnectionSectionHorseshoe,
			Length:      80.0,
			Width:       80.0,
			Height:      50.0,
			ArcHeight:   15.0,
		},
		BranchSection2: FourWayWellSection{
			SectionType: ConnectionSectionHorseshoe,
			Length:      80.0,
			Width:       80.0,
			Height:      50.0,
			ArcHeight:   15.0,
		},
		OuterWallThickness: 5.0,
		InnerWallThickness: 3.0,
		CushionExtension:   10.0,
		CushionThickness:   10.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create four way open cut tunnel")
	}
}

func TestCreateFourWayUndergroundTunnel(t *testing.T) {
	shp := CreateFourWayWell(FourWayWellParams{
		Ctype:           FourWayWellUnderground,
		Length:          200.0,
		Width:           80.0,
		Height:          60.0,
		ShaftRadius:     80.0,
		CornerStyle:     CornerStyleRounded,
		CornerRadius:    30.0,
		BranchLength:    100.0,
		BranchWidth:     80.0,
		TopThickness:    10.0,
		BottomThickness: 10.0,
		LeftSection: FourWayWellSection{
			SectionType: ConnectionSectionRectangular,
			Length:      60.0,
			Width:       80.0,
			Height:      90.0,
			ArcHeight:   15.0,
		},
		RightSection: FourWayWellSection{
			SectionType: ConnectionSectionRectangular,
			Length:      60.0,
			Width:       80.0,
			Height:      90.0,
			ArcHeight:   15.0,
		},
		BranchSection1: FourWayWellSection{
			SectionType: ConnectionSectionHorseshoe,
			Length:      80.0,
			Width:       80.0,
			Height:      50.0,
			ArcHeight:   15.0,
		},
		BranchSection2: FourWayWellSection{
			SectionType: ConnectionSectionHorseshoe,
			Length:      80.0,
			Width:       80.0,
			Height:      50.0,
			ArcHeight:   15.0,
		},
		OuterWallThickness: 5.0,
		InnerWallThickness: 3.0,
		CushionExtension:   10.0,
		CushionThickness:   10.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create four way underground tunnel")
	}
}
