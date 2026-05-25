package topo

import "testing"

var testChannelPoints = []ChannelPoint{
	{Position: NewPoint3([3]float64{0, 0, 0}), Ctype: 0},
	{Position: NewPoint3([3]float64{300, 0, 30}), Ctype: 0},
	{Position: NewPoint3([3]float64{500, 300, 50}), Ctype: 1},
	{Position: NewPoint3([3]float64{300, 600, 20}), Ctype: 0},
	{Position: NewPoint3([3]float64{300, 800, 0}), Ctype: 0},
}

var testArcPoints = []ChannelPoint{
	{Position: NewPoint3([3]float64{0, 0, 0}), Ctype: 0},
	{Position: NewPoint3([3]float64{900, 500, 0}), Ctype: 0},
}

var testTurnPoints = []ChannelPoint{
	{Position: NewPoint3([3]float64{0, 0, 0}), Ctype: 0},
	{Position: NewPoint3([3]float64{100, 0, 0}), Ctype: 0},
	{Position: NewPoint3([3]float64{150, 50, 0}), Ctype: 1},
	{Position: NewPoint3([3]float64{150, 100, 0}), Ctype: 0},
}

func TestCreatePipeRow(t *testing.T) {
	t.Run("no enclosure", func(t *testing.T) {
		params := PipeRowParams{
			PipeType:      PipeRowTypeNormal,
			HasEnclosure:  false,
			BaseExtension: 20,
			BaseThickness: 5,
			PipePositions: []Point2{
				NewPoint2([2]float64{-50, 40}),
				NewPoint2([2]float64{0, 40}),
				NewPoint2([2]float64{50, 40}),
			},
			PipeInnerDiameters:  []float32{20, 30, 20},
			PipeWallThicknesses: []float32{4, 4, 4},
			Points:              testChannelPoints,
		}
		shp := CreatePipeRow(params)
		if shp == nil {
			t.Fatal("CreatePipeRow returned nil (no enclosure)")
		}
	})

	t.Run("with enclosure", func(t *testing.T) {
		params := PipeRowParams{
			PipeType:        PipeRowTypeNormal,
			HasEnclosure:    true,
			EnclosureWidth:  200,
			EnclosureHeight: 200,
			BaseExtension:   5,
			BaseThickness:   10,
			CushionExtension: 5,
			CushionThickness: 10,
			PipePositions: []Point2{
				NewPoint2([2]float64{-50, 40}),
				NewPoint2([2]float64{0, 40}),
				NewPoint2([2]float64{50, 40}),
			},
			PipeInnerDiameters:  []float32{20, 30, 20},
			PipeWallThicknesses: []float32{4, 4, 4},
			Points:              testChannelPoints,
		}
		shp := CreatePipeRow(params)
		if shp == nil {
			t.Fatal("CreatePipeRow returned nil (with enclosure)")
		}
	})

	t.Run("pull pipe", func(t *testing.T) {
		params := PipeRowParams{
			PipeType: PipeRowTypePull,
			PipePositions: []Point2{
				NewPoint2([2]float64{-50, 40}),
				NewPoint2([2]float64{50, 40}),
			},
			PipeInnerDiameters:   []float32{50, 50},
			PipeWallThicknesses:  []float32{6, 6},
			PullPipeInnerDiameter: 200,
			PullPipeThickness:     8,
			Points:                testChannelPoints,
		}
		shp := CreatePipeRow(params)
		if shp == nil {
			t.Fatal("CreatePipeRow returned nil (pull pipe)")
		}
	})
}

func TestCreateCableTrench(t *testing.T) {
	params := CableTrenchParams{
		Width:            60,
		Height:           80,
		CoverWidth:       64,
		CoverThickness:   5,
		BaseExtension:    10,
		BaseThickness:    15,
		CushionExtension: 12,
		CushionThickness: 10,
		WallThickness:    15,
		WallThickness2:   10,
		Points:           testChannelPoints,
	}
	shp := CreateCableTrench(params)
	if shp == nil {
		t.Fatal("CreateCableTrench returned nil")
	}
}

func TestCreateCableTunnel(t *testing.T) {
	t.Run("rectangular", func(t *testing.T) {
		params := CableTunnelParams{
			Style:              1,
			Width:              60,
			Height:             80,
			TopThickness:       5,
			BottomThickness:    6,
			OuterWallThickness: 7,
			CushionExtension:   5,
			CushionThickness:   8,
			Points:             testChannelPoints,
		}
		shp := CreateCableTunnel(params)
		if shp == nil {
			t.Fatal("CreateCableTunnel rectangular returned nil")
		}
	})

	t.Run("horseshoe", func(t *testing.T) {
		params := CableTunnelParams{
			Style:              2,
			Width:              50,
			Height:             70,
			OuterWallThickness: 4,
			InnerWallThickness: 3,
			ArcHeight:          12,
			CushionExtension:   5,
			CushionThickness:   7,
			Points:             testChannelPoints,
		}
		shp := CreateCableTunnel(params)
		if shp == nil {
			t.Fatal("CreateCableTunnel horseshoe returned nil")
		}
	})

	t.Run("circular", func(t *testing.T) {
		params := CableTunnelParams{
			Style:                3,
			Width:                60,
			Height:               60,
			OuterWallThickness:   7,
			BottomPlatformHeight: 10,
			CushionExtension:     0,
			CushionThickness:     0,
			Points:               testChannelPoints,
		}
		shp := CreateCableTunnel(params)
		if shp == nil {
			t.Fatal("CreateCableTunnel circular returned nil")
		}
	})
}

func TestCreateCableTray(t *testing.T) {
	t.Run("arch", func(t *testing.T) {
		params := CableTrayParams{
			Style:          1,
			ColumnDiameter: 40,
			ColumnHeight:   100,
			Span:           400,
			Width:          60,
			Height:         30,
			TopPlateHeight: 5,
			ArcHeight:      55,
			WallThickness:  3,
			PipePositions: []Point2{
				NewPoint2([2]float64{-20, 15}),
				NewPoint2([2]float64{0, 15}),
				NewPoint2([2]float64{20, 15}),
			},
			PipeInnerDiameters:  []float32{10, 10, 10},
			PipeWallThicknesses: []float32{2, 2, 2},
			HasProtectionPlate:  true,
			Points:              testArcPoints,
		}
		shp := CreateCableTray(params)
		if shp == nil {
			t.Fatal("CreateCableTray arch returned nil")
		}
	})

	t.Run("beam", func(t *testing.T) {
		params := CableTrayParams{
			Style:          2,
			ColumnDiameter: 40,
			ColumnHeight:   100,
			Span:           200,
			Width:          60,
			Height:         30,
			TopPlateHeight: 5,
			ArcHeight:      15,
			WallThickness:  3,
			PipePositions: []Point2{
				NewPoint2([2]float64{-20, 15}),
				NewPoint2([2]float64{0, 15}),
				NewPoint2([2]float64{20, 15}),
			},
			PipeInnerDiameters:  []float32{10, 10, 10},
			PipeWallThicknesses: []float32{2, 2, 2},
			HasProtectionPlate:  true,
			Points:              testChannelPoints,
		}
		shp := CreateCableTray(params)
		if shp == nil {
			t.Fatal("CreateCableTray beam returned nil")
		}
	})
}

func TestCreateCableLBeam(t *testing.T) {
	t.Run("standard", func(t *testing.T) {
		params := CableLBeamParams{
			Length: 300,
			Width:  150,
			Height: 200,
		}
		shp := CreateCableLBeam(params)
		if shp == nil {
			t.Fatal("CreateCableLBeam standard returned nil")
		}
	})

	t.Run("extreme", func(t *testing.T) {
		params := CableLBeamParams{
			Length: 500,
			Width:  50,
			Height: 300,
		}
		shp := CreateCableLBeam(params)
		if shp == nil {
			t.Fatal("CreateCableLBeam extreme returned nil")
		}
	})
}

func TestCreateManhole(t *testing.T) {
	t.Run("circular", func(t *testing.T) {
		params := ManholeParams{
			Style:         1,
			Length:        100,
			Width:         0,
			Height:        150,
			WallThickness: 10,
		}
		shp := CreateManhole(params)
		if shp == nil {
			t.Fatal("CreateManhole circular returned nil")
		}
	})

	t.Run("rectangular", func(t *testing.T) {
		params := ManholeParams{
			Style:         2,
			Length:        120,
			Width:         80,
			Height:        150,
			WallThickness: 10,
		}
		shp := CreateManhole(params)
		if shp == nil {
			t.Fatal("CreateManhole rectangular returned nil")
		}
	})
}

func TestCreateManholeCover(t *testing.T) {
	t.Run("circular", func(t *testing.T) {
		params := ManholeCoverParams{
			Style:     1,
			Length:    100,
			Width:     0,
			Thickness: 10,
		}
		shp := CreateManholeCover(params)
		if shp == nil {
			t.Fatal("CreateManholeCover circular returned nil")
		}
	})

	t.Run("rectangular", func(t *testing.T) {
		params := ManholeCoverParams{
			Style:     2,
			Length:    120,
			Width:     80,
			Thickness: 10,
		}
		shp := CreateManholeCover(params)
		if shp == nil {
			t.Fatal("CreateManholeCover rectangular returned nil")
		}
	})
}

func TestCreateLadder(t *testing.T) {
	params := LadderParams{
		Length:    3000,
		Width:     400,
		Thickness: 20,
	}
	shp := CreateLadder(params)
	if shp == nil {
		t.Fatal("CreateLadder returned nil")
	}
}

func TestCreateSump(t *testing.T) {
	t.Run("standard", func(t *testing.T) {
		params := SumpParams{
			Length:          500,
			Width:           300,
			Depth:           400,
			BottomThickness: 50,
		}
		shp := CreateSump(params)
		if shp == nil {
			t.Fatal("CreateSump standard returned nil")
		}
	})

	t.Run("shallow", func(t *testing.T) {
		params := SumpParams{
			Length:          600,
			Width:           400,
			Depth:           200,
			BottomThickness: 30,
		}
		shp := CreateSump(params)
		if shp == nil {
			t.Fatal("CreateSump shallow returned nil")
		}
	})
}

func TestCreateFootpath(t *testing.T) {
	params := FootpathParams{
		Height: 15,
		Width:  80,
		Points: testArcPoints,
	}
	shp := CreateFootpath(params)
	if shp == nil {
		t.Fatal("CreateFootpath returned nil")
	}
}

func TestCreateShaftChamber(t *testing.T) {
	params := ShaftChamberParams{
		SupportWallThickness: 20,
		SupportDiameter:      110,
		SupportHeight:        50,
		TopThickness:         8,
		InnerDiameter:        80,
		WorkingHeight:        120,
		OuterWallThickness:   12,
		InnerWallThickness:   6,
	}
	shp := CreateShaftChamber(params)
	if shp == nil {
		t.Fatal("CreateShaftChamber returned nil")
	}
}

func TestCreateTunnelCompartmentPartition(t *testing.T) {
	params := TunnelCompartmentPartitionParams{
		Width:     300,
		Thickness: 15,
	}
	shp := CreateTunnelCompartmentPartition(params)
	if shp == nil {
		t.Fatal("CreateTunnelCompartmentPartition returned nil")
	}
}

func TestCreateTunnelPartitionBoard(t *testing.T) {
	t.Run("circular", func(t *testing.T) {
		params := TunnelPartitionBoardParams{
			Style:     TunnelPartitionBoardStyleCircular,
			Length:    200,
			Width:     0,
			Thickness: 10,
			HoleCount: 4,
			HolePositions: []Point2{
				NewPoint2([2]float64{50, 50}),
				NewPoint2([2]float64{-50, 50}),
				NewPoint2([2]float64{-50, -50}),
				NewPoint2([2]float64{50, -50}),
			},
			HoleStyles:    []int32{1, 1, 1, 1},
			HoleDiameters: []float32{20, 20, 20, 20},
			HoleWidths:    []float32{0, 0, 0, 0},
		}
		shp := CreateTunnelPartitionBoard(params)
		if shp == nil {
			t.Fatal("CreateTunnelPartitionBoard circular returned nil")
		}
	})

	t.Run("rectangular", func(t *testing.T) {
		params := TunnelPartitionBoardParams{
			Style:     TunnelPartitionBoardStyleRectangular,
			Length:    300,
			Width:     200,
			Thickness: 15,
			HoleCount: 3,
			HolePositions: []Point2{
				NewPoint2([2]float64{100, 50}),
				NewPoint2([2]float64{-100, 50}),
				NewPoint2([2]float64{0, -50}),
			},
			HoleStyles:    []int32{1, 2, 1},
			HoleDiameters: []float32{30, 40, 25},
			HoleWidths:    []float32{0, 20, 0},
		}
		shp := CreateTunnelPartitionBoard(params)
		if shp == nil {
			t.Fatal("CreateTunnelPartitionBoard rectangular returned nil")
		}
	})
}

func TestCreateVentilationPavilion(t *testing.T) {
	params := VentilationPavilionParams{
		TopLength:    400,
		MiddleLength: 300,
		BottomLength: 400,
		TopWidth:     350,
		MiddleWidth:  250,
		BottomWidth:  350,
		TopHeight:    50,
		Height:       150,
		BaseHeight:   30,
	}
	shp := CreateVentilationPavilion(params)
	if shp == nil {
		t.Fatal("CreateVentilationPavilion returned nil")
	}
}

func TestCreateStraightVentilationDuct(t *testing.T) {
	params := StraightVentilationDuctParams{
		Diameter:      200,
		WallThickness: 10,
		Height:        500,
	}
	shp := CreateStraightVentilationDuct(params)
	if shp == nil {
		t.Fatal("CreateStraightVentilationDuct returned nil")
	}
}

func TestCreateObliqueVentilationDuct(t *testing.T) {
	params := ObliqueVentilationDuctParams{
		HoodRoomLength:        200,
		HoodRoomWidth:         150,
		HoodRoomHeight:        200,
		HoodWallThickness:     10,
		DuctCenterHeight:      80,
		DuctLeftDistance:      80,
		DuctDiameter:          120,
		DuctWallThickness:     8,
		DuctLength:            300,
		DuctHeightDifference:  50,
		BaseLength:            220,
		BaseWidth:             180,
		BaseHeight:            10,
		BaseRoomLength:        200,
		BaseRoomWallThickness: 12,
		BaseRoomWidth:         150,
		BaseRoomHeight:        220,
	}
	shp := CreateObliqueVentilationDuct(params)
	if shp == nil {
		t.Fatal("CreateObliqueVentilationDuct returned nil")
	}
}

func TestCreateDrainageWell(t *testing.T) {
	params := DrainageWellParams{
		Length:           500,
		Width:            300,
		Height:           300,
		NeckDiameter:     150,
		NeckHeight:       400,
		CushionExtension: 50,
		BottomThickness:  60,
		WallThickness:    20,
	}
	shp := CreateDrainageWell(params)
	if shp == nil {
		t.Fatal("CreateDrainageWell returned nil")
	}
}

func TestCreatePipeSupport(t *testing.T) {
	t.Run("single sided", func(t *testing.T) {
		params := PipeSupportParams{
			Style: PipeSupportSingleSide,
			Count: 2,
			Positions: []Point2{
				NewPoint2([2]float64{-20, 16}),
				NewPoint2([2]float64{20, 16}),
			},
			Radii:  []float32{8, 8},
			Length: 100,
			Width:  18,
			Height: 20,
		}
		shp := CreatePipeSupport(params)
		if shp == nil {
			t.Fatal("CreatePipeSupport single sided returned nil")
		}
	})

	t.Run("double sided", func(t *testing.T) {
		params := PipeSupportParams{
			Style: PipeSupportDoubleSide,
			Count: 8,
			Positions: []Point2{
				NewPoint2([2]float64{-10, 12}),
				NewPoint2([2]float64{-30, 12}),
				NewPoint2([2]float64{10, 12}),
				NewPoint2([2]float64{30, 12}),
				NewPoint2([2]float64{-10, -12}),
				NewPoint2([2]float64{-30, -12}),
				NewPoint2([2]float64{10, -12}),
				NewPoint2([2]float64{30, -12}),
			},
			Radii:  []float32{8, 8, 8, 8, 8, 8, 8, 8},
			Length: 100,
			Width:  18,
			Height: 26,
		}
		shp := CreatePipeSupport(params)
		if shp == nil {
			t.Fatal("CreatePipeSupport double sided returned nil")
		}
	})
}

func TestCreateCoverPlate(t *testing.T) {
	t.Run("rectangular", func(t *testing.T) {
		params := CoverPlateParams{
			Style:       CoverPlateRectangle,
			Length:      200,
			Width:       100,
			SmallRadius: 0,
			LargeRadius: 0,
			Thickness:   10,
		}
		shp := CreateCoverPlate(params)
		if shp == nil {
			t.Fatal("CreateCoverPlate rectangular returned nil")
		}
	})

	t.Run("sector", func(t *testing.T) {
		params := CoverPlateParams{
			Style:       CoverPlateSector,
			Length:      250,
			Width:       0,
			SmallRadius: 20,
			LargeRadius: 100,
			Thickness:   8,
		}
		shp := CreateCoverPlate(params)
		if shp == nil {
			t.Fatal("CreateCoverPlate sector returned nil")
		}
	})
}

func TestCreateCableRay(t *testing.T) {
	params := CableRayParams{
		OuterLength:    300,
		OuterHeight:    100,
		InnerLength:    280,
		InnerHeight:    80,
		CoverThickness: 5,
	}
	shp := CreateCableRay(params)
	if shp == nil {
		t.Fatal("CreateCableRay returned nil")
	}
}

func TestCreateWaterTunnel(t *testing.T) {
	t.Run("rectangular", func(t *testing.T) {
		params := WaterTunnelParams{
			Style:              1,
			Width:              60,
			Height:             80,
			TopThickness:       5,
			BottomThickness:    6,
			OuterWallThickness: 7,
			CushionExtension:   5,
			CushionThickness:   8,
			Points:             testTurnPoints,
		}
		shp := CreateWaterTunnel(params)
		if shp == nil {
			t.Fatal("CreateWaterTunnel rectangular returned nil")
		}
	})

	t.Run("cityopening", func(t *testing.T) {
		params := WaterTunnelParams{
			Style:              2,
			Width:              50,
			Height:             70,
			OuterWallThickness: 4,
			InnerWallThickness: 3,
			ArcRadius:          40,
			CushionExtension:   5,
			CushionThickness:   7,
			Points:             testTurnPoints,
		}
		shp := CreateWaterTunnel(params)
		if shp == nil {
			t.Fatal("CreateWaterTunnel cityopening returned nil")
		}
	})

	t.Run("horseshoe", func(t *testing.T) {
		params := WaterTunnelParams{
			Style:              4,
			Width:              60,
			Height:             120,
			OuterWallThickness: 4,
			InnerWallThickness: 3,
			ArcRadius:          50,
			ArcAngle:           120,
			CushionExtension:   5,
			CushionThickness:   7,
			Points:             testTurnPoints,
		}
		shp := CreateWaterTunnel(params)
		if shp == nil {
			t.Fatal("CreateWaterTunnel horseshoe returned nil")
		}
	})

	t.Run("circular", func(t *testing.T) {
		params := WaterTunnelParams{
			Style:                3,
			Width:                60,
			Height:               60,
			OuterWallThickness:   7,
			BottomPlatformHeight: 10,
			CushionExtension:     0,
			CushionThickness:     0,
			Points:               testTurnPoints,
		}
		shp := CreateWaterTunnel(params)
		if shp == nil {
			t.Fatal("CreateWaterTunnel circular returned nil")
		}
	})
}
