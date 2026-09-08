package topo

import (
	"math"
	"testing"
)

func TestCreateRevol(t *testing.T) {
	origin := NewPoint3([3]float64{0, 0, 0})
	zDir := NewDir3FromXYZ([3]float64{0, 0, 1})
	axis := NewAxis1(origin, zDir)
	angle := float32(math.Pi / 4)

	triShp := CreateRevol(RevolParams{
		Profile: ShapeProfile{
			Type: ProfileTypeTriangle,
			Data: ProfileData{Triangle: TriangleProfile{
				P1: NewPoint3([3]float64{0, 0, 0}),
				P2: NewPoint3([3]float64{10, 0, 0}),
				P3: NewPoint3([3]float64{5, 0, 8}),
			}},
		},
		Axis:  axis,
		Angle: angle,
	})
	if triShp == nil || triShp.IsNull() {
		t.Fatal("Failed to create triangle profile revol")
	}

	rectShp := CreateRevol(RevolParams{
		Profile: ShapeProfile{
			Type: ProfileTypeRectangle,
			Data: ProfileData{Rectangle: RectangleProfile{
				P1: NewPoint3([3]float64{0, 0, 0}),
				P2: NewPoint3([3]float64{10, 0, 5}),
			}},
		},
		Axis:  axis,
		Angle: angle,
	})
	if rectShp == nil || rectShp.IsNull() {
		t.Fatal("Failed to create rectangle profile revol")
	}

	circShp := CreateRevol(RevolParams{
		Profile: ShapeProfile{
			Type: ProfileTypeCirc,
			Data: ProfileData{Circ: CircProfile{
				Center: NewPoint3([3]float64{10, 0, 0}),
				Norm:   NewDir3FromXYZ([3]float64{0, 1, 0}),
				Radius: 5.0,
			}},
		},
		Axis:  axis,
		Angle: angle,
	})
	if circShp == nil || circShp.IsNull() {
		t.Fatal("Failed to create circle profile revol")
	}

	elipsShp := CreateRevol(RevolParams{
		Profile: ShapeProfile{
			Type: ProfileTypeElips,
			Data: ProfileData{Elips: ElipsProfile{
				S1:     NewPoint3([3]float64{20, 0, 0}),
				S2:     NewPoint3([3]float64{10, 0, 5}),
				Center: NewPoint3([3]float64{10, 0, 0}),
			}},
		},
		Axis:  axis,
		Angle: angle,
	})
	if elipsShp == nil || elipsShp.IsNull() {
		t.Fatal("Failed to create ellipse profile revol")
	}

	polyShp := CreateRevol(RevolParams{
		Profile: ShapeProfile{
			Type: ProfileTypePolygon,
			Data: ProfileData{Polygon: PolygonProfile{Edges: []Point3{
				NewPoint3([3]float64{0, 0, 0}),
				NewPoint3([3]float64{10, 0, 0}),
				NewPoint3([3]float64{15, 0, 5}),
				NewPoint3([3]float64{10, 0, 10}),
				NewPoint3([3]float64{0, 0, 10}),
			}}},
		},
		Axis:  axis,
		Angle: angle,
	})
	if polyShp == nil || polyShp.IsNull() {
		t.Fatal("Failed to create polygon profile revol")
	}
}

func TestCreatePrism(t *testing.T) {
	zDir := NewDir3FromXYZ([3]float64{0, 0, 1})

	triShp := CreatePrism(PrismParams{
		Profile: ShapeProfile{
			Type: ProfileTypeTriangle,
			Data: ProfileData{Triangle: TriangleProfile{
				P1: NewPoint3([3]float64{0, 0, 0}),
				P2: NewPoint3([3]float64{10, 0, 0}),
				P3: NewPoint3([3]float64{5, 8, 0}),
			}},
		},
		Direction: zDir,
		Height:    20,
	})
	if triShp == nil || triShp.IsNull() {
		t.Fatal("Failed to create triangle profile prism")
	}

	rectShp := CreatePrism(PrismParams{
		Profile: ShapeProfile{
			Type: ProfileTypeRectangle,
			Data: ProfileData{Rectangle: RectangleProfile{
				P1: NewPoint3([3]float64{0, 0, 0}),
				P2: NewPoint3([3]float64{10, 5, 0}),
			}},
		},
		Direction: zDir,
		Height:    20,
	})
	if rectShp == nil || rectShp.IsNull() {
		t.Fatal("Failed to create rectangle profile prism")
	}

	circShp := CreatePrism(PrismParams{
		Profile: ShapeProfile{
			Type: ProfileTypeCirc,
			Data: ProfileData{Circ: CircProfile{
				Center: NewPoint3([3]float64{0, 0, 0}),
				Norm:   NewDir3FromXYZ([3]float64{0, 0, 1}),
				Radius: 5.0,
			}},
		},
		Direction: zDir,
		Height:    20,
	})
	if circShp == nil || circShp.IsNull() {
		t.Fatal("Failed to create circle profile prism")
	}

	elipsShp := CreatePrism(PrismParams{
		Profile: ShapeProfile{
			Type: ProfileTypeElips,
			Data: ProfileData{Elips: ElipsProfile{
				S1:     NewPoint3([3]float64{10, 0, 0}),
				S2:     NewPoint3([3]float64{0, 5, 0}),
				Center: NewPoint3([3]float64{0, 0, 0}),
			}},
		},
		Direction: zDir,
		Height:    20,
	})
	if elipsShp == nil || elipsShp.IsNull() {
		t.Fatal("Failed to create ellipse profile prism")
	}

	polyShp := CreatePrism(PrismParams{
		Profile: ShapeProfile{
			Type: ProfileTypePolygon,
			Data: ProfileData{Polygon: PolygonProfile{Edges: []Point3{
				NewPoint3([3]float64{0, 0, 0}),
				NewPoint3([3]float64{10, 0, 0}),
				NewPoint3([3]float64{15, 5, 0}),
				NewPoint3([3]float64{10, 10, 0}),
				NewPoint3([3]float64{0, 10, 0}),
			}}},
		},
		Direction: zDir,
		Height:    20,
	})
	if polyShp == nil || polyShp.IsNull() {
		t.Fatal("Failed to create polygon profile prism")
	}
}

func circProfile(center [3]float64, norm [3]float64, radius float32) ShapeProfile {
	return ShapeProfile{
		Type: ProfileTypeCirc,
		Data: ProfileData{Circ: CircProfile{
			Center: NewPoint3(center),
			Norm:   NewDir3FromXYZ(norm),
			Radius: radius,
		}},
	}
}

func TestCreatePipe(t *testing.T) {
	circProf5 := circProfile([3]float64{0, 0, 0}, [3]float64{0, 0, 1}, 5.0)
	circProf10 := circProfile([3]float64{0, 0, 0}, [3]float64{0, 0, 1}, 10.0)
	circProf3 := circProfile([3]float64{0, 0, 0}, [3]float64{0, 0, 1}, 3.0)
	circProf6 := circProfile([3]float64{50, 0, 0}, [3]float64{0, 0, 1}, 6.0)

	t.Run("CircularLinePipe", func(t *testing.T) {
		shp := CreatePipe(PipeParams{
			Wire:           []Point3{NewPoint3([3]float64{0, 0, 0}), NewPoint3([3]float64{100, 0, 0})},
			Profiles:       []ShapeProfile{circProf5, circProf10},
			SegmentType:    SegmentTypeLine,
			TransitionMode: TransitionTransformed,
		})
		if shp == nil || shp.IsNull() {
			t.Fatal("Failed to create circular line pipe")
		}
	})

	t.Run("CircularArcPipe", func(t *testing.T) {
		shp := CreatePipe(PipeParams{
			Wire:           []Point3{NewPoint3([3]float64{0, 0, 0}), NewPoint3([3]float64{50, 50, 0}), NewPoint3([3]float64{100, 0, 0})},
			Profiles:       []ShapeProfile{circProf5, circProf10},
			SegmentType:    SegmentTypeThreePointArc,
			TransitionMode: TransitionTransformed,
		})
		if shp == nil || shp.IsNull() {
			t.Fatal("Failed to create circular arc pipe")
		}
	})

	t.Run("CircularCenterArcPipe", func(t *testing.T) {
		shp := CreatePipe(PipeParams{
			Wire:           []Point3{NewPoint3([3]float64{0, 0, 0}), NewPoint3([3]float64{50, 0, 0}), NewPoint3([3]float64{100, 0, 0})},
			Profiles:       []ShapeProfile{circProf6, circProf10},
			SegmentType:    SegmentTypeCircleCenterArc,
			TransitionMode: TransitionTransformed,
		})
		if shp == nil || shp.IsNull() {
			t.Fatal("Failed to create circular center arc pipe")
		}
	})

	t.Run("CircularSplinePipe", func(t *testing.T) {
		shp := CreatePipe(PipeParams{
			Wire: []Point3{
				NewPoint3([3]float64{0, 0, 0}),
				NewPoint3([3]float64{30, 30, 20}),
				NewPoint3([3]float64{70, 30, 40}),
				NewPoint3([3]float64{100, 0, 50}),
			},
			Profiles:       []ShapeProfile{circProf5, circProf10},
			SegmentType:    SegmentTypeSpline,
			TransitionMode: TransitionTransformed,
		})
		if shp == nil || shp.IsNull() {
			t.Fatal("Failed to create circular spline pipe")
		}
	})

	t.Run("PolygonLinePipe", func(t *testing.T) {
		shp := CreatePipe(PipeParams{
			Wire: []Point3{NewPoint3([3]float64{0, 0, 0}), NewPoint3([3]float64{100, 0, 0})},
			Profiles: []ShapeProfile{{
				Type: ProfileTypePolygon,
				Data: ProfileData{Polygon: PolygonProfile{Edges: []Point3{
					NewPoint3([3]float64{0, 0, 0}),
					NewPoint3([3]float64{10, 0, 0}),
					NewPoint3([3]float64{10, 5, 0}),
					NewPoint3([3]float64{0, 5, 0}),
					NewPoint3([3]float64{0, 0, 0}),
				}}},
			}},
			SegmentType:    SegmentTypeLine,
			TransitionMode: TransitionTransformed,
		})
		if shp == nil || shp.IsNull() {
			t.Fatal("Failed to create polygon line pipe")
		}
	})

	t.Run("CircularSplineInnerPipe", func(t *testing.T) {
		shp := CreatePipe(PipeParams{
			Wire: []Point3{
				NewPoint3([3]float64{0, 0, 0}),
				NewPoint3([3]float64{30, 30, 20}),
				NewPoint3([3]float64{70, 30, 40}),
				NewPoint3([3]float64{100, 0, 50}),
			},
			Profiles:       []ShapeProfile{circProf5},
			InnerProfiles:  []ShapeProfile{circProf3},
			SegmentType:    SegmentTypeSpline,
			TransitionMode: TransitionTransformed,
		})
		if shp == nil || shp.IsNull() {
			t.Fatal("Failed to create circular spline inner pipe")
		}
	})

	t.Run("CircularLinePipeSplit", func(t *testing.T) {
		shp := CreatePipeWithSplitDistances(PipeParams{
			Wire:           []Point3{NewPoint3([3]float64{0, 0, 0}), NewPoint3([3]float64{100, 0, 0})},
			Profiles:       []ShapeProfile{circProf5, circProf10},
			SegmentType:    SegmentTypeLine,
			TransitionMode: TransitionTransformed,
		}, 20.0, 80.0)
		if shp == nil || shp.IsNull() {
			t.Fatal("Failed to create circular line pipe with split distances")
		}
	})

	t.Run("CircularSplineInnerPipeSplit", func(t *testing.T) {
		shp := CreatePipeWithSplitDistances(PipeParams{
			Wire: []Point3{
				NewPoint3([3]float64{0, 0, 0}),
				NewPoint3([3]float64{30, 30, 20}),
				NewPoint3([3]float64{70, 30, 40}),
				NewPoint3([3]float64{100, 0, 50}),
			},
			Profiles:       []ShapeProfile{circProf5},
			InnerProfiles:  []ShapeProfile{circProf3},
			SegmentType:    SegmentTypeSpline,
			TransitionMode: TransitionTransformed,
		}, 10.0, 80.0)
		if shp == nil || shp.IsNull() {
			t.Fatal("Failed to create split circular spline pipe")
		}
	})
}

func TestCreateMultiSegmentPipe(t *testing.T) {
	linePoints := []Point3{NewPoint3([3]float64{50, -50, 0}), NewPoint3([3]float64{100, 0, 0})}
	arcPoints := []Point3{NewPoint3([3]float64{100, 0, 0}), NewPoint3([3]float64{150, 50, 0}), NewPoint3([3]float64{200, 0, 0})}
	centerArcPoints := []Point3{NewPoint3([3]float64{200, 0, 0}), NewPoint3([3]float64{250, 0, 0}), NewPoint3([3]float64{300, 0, 0})}
	splinePoints := []Point3{NewPoint3([3]float64{300, 0, 0}), NewPoint3([3]float64{350, 50, 50}), NewPoint3([3]float64{400, 0, 100})}

	circProf := circProfile([3]float64{0, 0, 0}, [3]float64{0, 0, 1}, 10.0)
	innerProf := circProfile([3]float64{0, 0, 0}, [3]float64{0, 0, 1}, 8.0)

	t.Run("BasicMultiSegment", func(t *testing.T) {
		shp := CreateMultiSegmentPipe(MultiSegmentPipeParams{
			Wires:          [][]Point3{linePoints, arcPoints, centerArcPoints, splinePoints},
			Profiles:       []ShapeProfile{circProf, circProf, circProf, circProf},
			InnerProfiles:  []ShapeProfile{innerProf, innerProf, innerProf, innerProf},
			SegmentTypes:   []SegmentType{SegmentTypeLine, SegmentTypeThreePointArc, SegmentTypeCircleCenterArc, SegmentTypeSpline},
			TransitionMode: TransitionRound,
		})
		if shp == nil || shp.IsNull() {
			t.Fatal("Failed to create multi-segment pipe")
		}
	})

	t.Run("BugCase", func(t *testing.T) {
		points := [][]Point3{
			{NewPoint3([3]float64{0, 0, 0}), NewPoint3([3]float64{13.363751136232167, -26.227833716198802, 40.422308564186096})},
			{NewPoint3([3]float64{13.363751136232167, -26.227833716198802, 40.422308564186096}), NewPoint3([3]float64{46.29231750732288, -90.69991450663656, 108.94551491551101})},
			{NewPoint3([3]float64{46.29231750732288, -90.69991450663656, 108.94551491551101}), NewPoint3([3]float64{132.02422594139352, -257.1274096108973, -1.525045077316463})},
			{NewPoint3([3]float64{132.02422594139352, -257.1274096108973, -1.525045077316463}), NewPoint3([3]float64{155.7862730268389, -461.9796159574762, 275.57995436759666})},
			{NewPoint3([3]float64{155.7862730268389, -461.9796159574762, 275.57995436759666}), NewPoint3([3]float64{277.5595232350752, -1029.277987377718, 560.3984563779086})},
		}
		upDir := NewDir3FromVector(NewVector3([3]float64{-2365550.686973459, 4588616.347934356, 3734082.7681595744}))
		polygonProf := ShapeProfile{
			Type: ProfileTypePolygon,
			Data: ProfileData{Polygon: PolygonProfile{Edges: []Point3{
				NewPoint3([3]float64{-3.171, 2.538, 0}),
				NewPoint3([3]float64{-3.136, 3.954, 0}),
				NewPoint3([3]float64{-2.498, 5.219, 0}),
				NewPoint3([3]float64{-1.382, 6.09, 0}),
				NewPoint3([3]float64{0, 6.4, 0}),
				NewPoint3([3]float64{1.382, 6.09, 0}),
				NewPoint3([3]float64{2.498, 5.219, 0}),
				NewPoint3([3]float64{3.136, 3.954, 0}),
				NewPoint3([3]float64{3.171, 2.538, 0}),
				NewPoint3([3]float64{2.5, 0, 0}),
				NewPoint3([3]float64{-2.5, 0, 0}),
				NewPoint3([3]float64{-3.171, 2.538, 0}),
			}}},
		}

		shp := CreateMultiSegmentPipe(MultiSegmentPipeParams{
			Wires:          points,
			Profiles:       []ShapeProfile{polygonProf, polygonProf, polygonProf, polygonProf, polygonProf},
			SegmentTypes:   []SegmentType{SegmentTypeLine, SegmentTypeLine, SegmentTypeLine, SegmentTypeLine, SegmentTypeLine},
			TransitionMode: TransitionTransformed,
			UpDir:          &upDir,
		})
		if shp == nil || shp.IsNull() {
			t.Fatal("Failed to create multi-segment bug pipe")
		}
	})

	t.Run("FrontCut", func(t *testing.T) {
		shp := CreateMultiSegmentPipeWithSplitDistances(MultiSegmentPipeParams{
			Wires:          [][]Point3{linePoints, arcPoints, centerArcPoints, splinePoints},
			Profiles:       []ShapeProfile{circProf, circProf, circProf, circProf},
			InnerProfiles:  []ShapeProfile{innerProf, innerProf, innerProf, innerProf},
			SegmentTypes:   []SegmentType{SegmentTypeLine, SegmentTypeThreePointArc, SegmentTypeCircleCenterArc, SegmentTypeSpline},
			TransitionMode: TransitionRound,
		}, 50.0, -1)
		if shp == nil || shp.IsNull() {
			t.Fatal("Failed to create pipe with front cut")
		}
	})

	t.Run("BackCut", func(t *testing.T) {
		shp := CreateMultiSegmentPipeWithSplitDistances(MultiSegmentPipeParams{
			Wires:          [][]Point3{linePoints, arcPoints, centerArcPoints, splinePoints},
			Profiles:       []ShapeProfile{circProf, circProf, circProf, circProf},
			InnerProfiles:  []ShapeProfile{innerProf, innerProf, innerProf, innerProf},
			SegmentTypes:   []SegmentType{SegmentTypeLine, SegmentTypeThreePointArc, SegmentTypeCircleCenterArc, SegmentTypeSpline},
			TransitionMode: TransitionRound,
		}, 0.0, 250.0)
		if shp == nil || shp.IsNull() {
			t.Fatal("Failed to create pipe with back cut")
		}
	})

	t.Run("BothCuts", func(t *testing.T) {
		shp := CreateMultiSegmentPipeWithSplitDistances(MultiSegmentPipeParams{
			Wires:          [][]Point3{linePoints, arcPoints, centerArcPoints, splinePoints},
			Profiles:       []ShapeProfile{circProf, circProf, circProf, circProf},
			InnerProfiles:  []ShapeProfile{innerProf, innerProf, innerProf, innerProf},
			SegmentTypes:   []SegmentType{SegmentTypeLine, SegmentTypeThreePointArc, SegmentTypeCircleCenterArc, SegmentTypeSpline},
			TransitionMode: TransitionRound,
		}, 50.0, 250.0)
		if shp == nil || shp.IsNull() {
			t.Fatal("Failed to create pipe with both cuts")
		}
	})

	t.Run("MiddleSegmentCut", func(t *testing.T) {
		shp := CreateMultiSegmentPipeWithSplitDistances(MultiSegmentPipeParams{
			Wires:          [][]Point3{linePoints, arcPoints, centerArcPoints, splinePoints},
			Profiles:       []ShapeProfile{circProf, circProf, circProf, circProf},
			InnerProfiles:  []ShapeProfile{innerProf, innerProf, innerProf, innerProf},
			SegmentTypes:   []SegmentType{SegmentTypeLine, SegmentTypeThreePointArc, SegmentTypeCircleCenterArc, SegmentTypeSpline},
			TransitionMode: TransitionRound,
		}, 120.0, 180.0)
		if shp == nil || shp.IsNull() {
			t.Fatal("Failed to create pipe with middle segment cut")
		}
	})
}

func TestCreatePipeJoint(t *testing.T) {
	circProf10 := circProfile([3]float64{0, 0, 0}, [3]float64{0, 0, 1}, 10.0)
	circProf8 := circProfile([3]float64{0, 0, 0}, [3]float64{0, 0, 1}, 8.0)
	circProf8outer := circProfile([3]float64{0, 0, 0}, [3]float64{0, 0, 1}, 8.0)
	circProf4 := circProfile([3]float64{0, 0, 0}, [3]float64{0, 0, 1}, 4.0)

	t.Run("TwoWayStraight", func(t *testing.T) {
		shp := CreatePipeJoint(PipeJointParams{
			Ins: []PipeEndpoint{
				{
					Offset:       NewPoint3([3]float64{-50, 0, 0}),
					Normal:       NewDir3FromXYZ([3]float64{1, 0, 0}),
					Profile:      circProf10,
					InnerProfile: &circProf8,
				},
			},
			Outs: []PipeEndpoint{
				{
					Offset:       NewPoint3([3]float64{50, 0, 0}),
					Normal:       NewDir3FromXYZ([3]float64{-1, 0, 0}),
					Profile:      circProf10,
					InnerProfile: &circProf8,
				},
			},
			Mode:    JointShapeModeSphere,
			Flanged: true,
		})
		if shp == nil || shp.IsNull() {
			t.Fatal("Failed to create 2-way pipe joint")
		}
	})

	t.Run("TJoint", func(t *testing.T) {
		shp := CreatePipeJoint(PipeJointParams{
			Ins: []PipeEndpoint{
				{
					Offset:       NewPoint3([3]float64{-50, 0, 0}),
					Normal:       NewDir3FromXYZ([3]float64{1, 0, 0}),
					Profile:      circProf10,
					InnerProfile: &circProf8,
				},
				{
					Offset:       NewPoint3([3]float64{0, -50, 0}),
					Normal:       NewDir3FromXYZ([3]float64{0, 1, 0}),
					Profile:      circProf10,
					InnerProfile: &circProf8,
				},
			},
			Outs: []PipeEndpoint{
				{
					Offset:       NewPoint3([3]float64{50, 0, 0}),
					Normal:       NewDir3FromXYZ([3]float64{-1, 0, 0}),
					Profile:      circProf8outer,
					InnerProfile: &circProf4,
				},
			},
			Mode:    JointShapeModeBox,
			Flanged: true,
		})
		if shp == nil || shp.IsNull() {
			t.Fatal("Failed to create T pipe joint")
		}
	})

	t.Run("CrossJoint", func(t *testing.T) {
		shp := CreatePipeJoint(PipeJointParams{
			Ins: []PipeEndpoint{
				{
					Offset:       NewPoint3([3]float64{-50, 0, 0}),
					Normal:       NewDir3FromXYZ([3]float64{1, 0, 0}),
					Profile:      circProf10,
					InnerProfile: &circProf8,
				},
				{
					Offset:       NewPoint3([3]float64{0, -50, 0}),
					Normal:       NewDir3FromXYZ([3]float64{0, 1, 0}),
					Profile:      circProf8outer,
					InnerProfile: &circProf4,
				},
			},
			Outs: []PipeEndpoint{
				{
					Offset:       NewPoint3([3]float64{50, 0, 0}),
					Normal:       NewDir3FromXYZ([3]float64{-1, 0, 0}),
					Profile:      circProf10,
					InnerProfile: &circProf8,
				},
				{
					Offset:       NewPoint3([3]float64{0, 50, 0}),
					Normal:       NewDir3FromXYZ([3]float64{0, -1, 0}),
					Profile:      circProf8outer,
					InnerProfile: &circProf4,
				},
			},
			Mode:    JointShapeModeCylinder,
			Flanged: false,
		})
		if shp == nil || shp.IsNull() {
			t.Fatal("Failed to create cross pipe joint")
		}
	})

	t.Run("YJoint", func(t *testing.T) {
		dir11 := NewDir3FromVector(NewVector3([3]float64{1, 1, 0}))
		dir1n1 := NewDir3FromVector(NewVector3([3]float64{1, -1, 0}))
		shp := CreatePipeJoint(PipeJointParams{
			Ins: []PipeEndpoint{
				{
					Offset:       NewPoint3([3]float64{-50, -50, 0}),
					Normal:       dir11,
					Profile:      circProf8outer,
					InnerProfile: &circProf4,
				},
				{
					Offset:       NewPoint3([3]float64{-50, 50, 0}),
					Normal:       dir1n1,
					Profile:      circProf8outer,
					InnerProfile: &circProf4,
				},
			},
			Outs: []PipeEndpoint{
				{
					Offset:       NewPoint3([3]float64{50, 0, 0}),
					Normal:       NewDir3FromXYZ([3]float64{-1, 0, 0}),
					Profile:      circProf10,
					InnerProfile: &circProf8,
				},
			},
			Mode:    JointShapeModeSphere,
			Flanged: true,
		})
		if shp == nil || shp.IsNull() {
			t.Fatal("Failed to create Y pipe joint")
		}
	})
}

func TestCreateMultiLayerExtrusionStructure(t *testing.T) {
	linePoints := []Point3{NewPoint3([3]float64{50, -50, 0}), NewPoint3([3]float64{100, 0, 0})}
	arcPoints := []Point3{NewPoint3([3]float64{100, 0, 0}), NewPoint3([3]float64{150, 50, 0}), NewPoint3([3]float64{200, 0, 0})}
	centerArcPoints := []Point3{NewPoint3([3]float64{200, 0, 0}), NewPoint3([3]float64{250, 0, 0}), NewPoint3([3]float64{300, 0, 0})}
	splinePoints := []Point3{NewPoint3([3]float64{300, 0, 0}), NewPoint3([3]float64{350, 50, 50}), NewPoint3([3]float64{400, 0, 100})}
	upDir := NewDir3FromXYZ([3]float64{0, 0, 1})

	shapes, err := CreateMultiLayerExtrusionStructure(MultiLayerExtrusionStructureParams{
		Wires:        [][]Point3{linePoints, arcPoints, centerArcPoints, splinePoints},
		SegmentTypes: []SegmentType{SegmentTypeLine, SegmentTypeThreePointArc, SegmentTypeCircleCenterArc, SegmentTypeSpline},
		Layers: []ProfileLayer{
			{
				Name: "base_layer",
				Profiles: []ShapeProfile{{
					Type: ProfileTypeRectangle,
					Data: ProfileData{Rectangle: RectangleProfile{
						P1: NewPoint3([3]float64{-10, -50, 0}),
						P2: NewPoint3([3]float64{10, -30, 0}),
					}},
				}},
			},
			{
				Name: "middle_layer",
				Profiles: []ShapeProfile{{
					Type: ProfileTypeCirc,
					Data: ProfileData{Circ: CircProfile{
						Center: NewPoint3([3]float64{0, -20, 0}),
						Norm:   NewDir3FromXYZ([3]float64{0, 0, 1}),
						Radius: 16.0,
					}},
				}},
			},
			{
				Name: "top_layer",
				Profiles: []ShapeProfile{{
					Type: ProfileTypePolygon,
					Data: ProfileData{Polygon: PolygonProfile{Edges: []Point3{
						NewPoint3([3]float64{-5, -5, 0}),
						NewPoint3([3]float64{5, -5, 0}),
						NewPoint3([3]float64{5, 5, 0}),
						NewPoint3([3]float64{0, 8, 0}),
						NewPoint3([3]float64{-5, 5, 0}),
					}}},
				}},
			},
		},
		TransitionMode: TransitionTransformed,
		UpDir:          &upDir,
	})
	if err != nil {
		t.Fatalf("Failed to create multi-layer extrusion structure: %v", err)
	}
	if len(shapes) != 3 {
		t.Fatalf("Expected 3 layers, got %d", len(shapes))
	}
	for name, shp := range shapes {
		if shp == nil || shp.IsNull() {
			t.Fatalf("Layer %s is null", name)
		}
	}
}

func TestCreateCatenary(t *testing.T) {
	circProf := circProfile([3]float64{0, 0, 0}, [3]float64{0, 0, 1}, 0.2)

	t.Run("Standard", func(t *testing.T) {
		shp := CreateCatenary(CatenaryParams{
			P1:           NewPoint3([3]float64{0, 0, 0}),
			P2:           NewPoint3([3]float64{100, 100, 0}),
			Profile:      circProf,
			Slack:        2,
			MaxSag:       10.0,
			Tessellation: 0.0,
		})
		if shp == nil || shp.IsNull() {
			t.Fatal("Failed to create catenary")
		}
	})

	t.Run("WithHeight", func(t *testing.T) {
		shp := CreateCatenary(CatenaryParams{
			P1:           NewPoint3([3]float64{0, 0, 0}),
			P2:           NewPoint3([3]float64{100, 50, 20}),
			Profile:      circProf,
			Slack:        2.0,
			MaxSag:       10.0,
			Tessellation: 0.0,
		})
		if shp == nil || shp.IsNull() {
			t.Fatal("Failed to create height catenary")
		}
	})

	t.Run("BugCase", func(t *testing.T) {
		upDir := NewDir3FromVector(NewVector3([3]float64{-2365550.686973459, 4588616.347934356, 3734082.7681595744}))
		shp := CreateCatenary(CatenaryParams{
			P1:           NewPoint3([3]float64{0, 0, 0}),
			P2:           NewPoint3([3]float64{26.363751136232167, -26.227833716198802, 30.422308564186096}),
			Profile:      circProf,
			Slack:        2,
			MaxSag:       10.0,
			Tessellation: 0.0,
			UpDir:        &upDir,
		})
		if shp == nil || shp.IsNull() {
			t.Fatal("Failed to create bug catenary")
		}
	})
}

func TestCreateBoxShape(t *testing.T) {
	shp := CreateBoxShape(BoxShapeParams{
		Point1: NewPoint3([3]float64{0, 0, 0}),
		Point2: NewPoint3([3]float64{100, 50, 30}),
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create box shape")
	}
}

func TestCreateConeShape(t *testing.T) {
	t.Run("FullCone", func(t *testing.T) {
		shp := CreateConeShape(ConeShapeParams{
			Radius1: 20.0,
			Radius2: 10.0,
			Height:  30.0,
		})
		if shp == nil || shp.IsNull() {
			t.Fatal("Failed to create full cone")
		}
	})

	t.Run("PartialCone", func(t *testing.T) {
		angle := 270.0 * math.Pi / 180
		shp := CreateConeShape(ConeShapeParams{
			Radius1: 15.0,
			Radius2: 5.0,
			Height:  25.0,
			Angle:   &angle,
		})
		if shp == nil || shp.IsNull() {
			t.Fatal("Failed to create partial cone")
		}
	})
}

func TestCreateCylinderShapeFromPrimitives(t *testing.T) {
	t.Run("FullCylinder", func(t *testing.T) {
		shp := CreateCylinderShape(CylinderShapeParams{
			Radius: 15.0,
			Height: 25.0,
		})
		if shp == nil || shp.IsNull() {
			t.Fatal("Failed to create full cylinder")
		}
	})

	t.Run("PartialCylinder", func(t *testing.T) {
		angle := 270.0 * math.Pi / 180
		shp := CreateCylinderShape(CylinderShapeParams{
			Radius: 10.0,
			Height: 20.0,
			Angle:  &angle,
		})
		if shp == nil || shp.IsNull() {
			t.Fatal("Failed to create partial cylinder")
		}
	})
}

func TestCreateRevolutionShape(t *testing.T) {
	meridian := []Point3{
		NewPoint3([3]float64{0, 0, 0}),
		NewPoint3([3]float64{10, 0, 0}),
		NewPoint3([3]float64{15, 5, 0}),
		NewPoint3([3]float64{10, 10, 0}),
		NewPoint3([3]float64{0, 10, 0}),
	}

	t.Run("FullRevolution", func(t *testing.T) {
		shp := CreateRevolutionShape(RevolutionShapeParams{
			Meridian: meridian,
		})
		if shp == nil || shp.IsNull() {
			t.Fatal("Failed to create full revolution shape")
		}
	})

	t.Run("PartialRevolution", func(t *testing.T) {
		angle := 270.0 * math.Pi / 180
		shp := CreateRevolutionShape(RevolutionShapeParams{
			Meridian: meridian,
			Angle:    &angle,
		})
		if shp == nil || shp.IsNull() {
			t.Fatal("Failed to create partial revolution shape")
		}
	})

	t.Run("RangedRevolution", func(t *testing.T) {
		angle := 180.0 * math.Pi / 180
		maxV := 8.0
		minV := 2.0
		shp := CreateRevolutionShape(RevolutionShapeParams{
			Meridian: meridian,
			Angle:    &angle,
			Max:      &maxV,
			Min:      &minV,
		})
		if shp == nil || shp.IsNull() {
			t.Fatal("Failed to create ranged revolution shape")
		}
	})
}

func TestCreateSphereShape(t *testing.T) {
	t.Run("FullSphere", func(t *testing.T) {
		shp := CreateSphereShape(SphereShapeParams{
			Radius: 20.0,
		})
		if shp == nil || shp.IsNull() {
			t.Fatal("Failed to create full sphere")
		}
	})

	t.Run("PartialSphere", func(t *testing.T) {
		angle1 := 0.0
		angle2 := 90.0 * math.Pi / 180
		angle := 270.0 * math.Pi / 180
		shp := CreateSphereShape(SphereShapeParams{
			Radius: 15.0,
			Angle1: &angle1,
			Angle2: &angle2,
			Angle:  &angle,
		})
		if shp == nil || shp.IsNull() {
			t.Fatal("Failed to create partial sphere")
		}
	})
}

func TestCreateTorusShape(t *testing.T) {
	t.Run("FullTorus", func(t *testing.T) {
		shp := CreateTorusShape(TorusShapeParams{
			Radius1: 30.0,
			Radius2: 10.0,
		})
		if shp == nil || shp.IsNull() {
			t.Fatal("Failed to create full torus")
		}
	})

	t.Run("PartialTorus", func(t *testing.T) {
		angle1 := -30.0 * math.Pi / 180
		angle2 := 30.0 * math.Pi / 180
		angle := 270.0 * math.Pi / 180
		shp := CreateTorusShape(TorusShapeParams{
			Radius1: 25.0,
			Radius2: 8.0,
			Angle1:  &angle1,
			Angle2:  &angle2,
			Angle:   &angle,
		})
		if shp == nil || shp.IsNull() {
			t.Fatal("Failed to create partial torus")
		}
	})
}

func TestCreateWedgeShape(t *testing.T) {
	t.Run("FullWedge", func(t *testing.T) {
		shp := CreateWedgeShape(WedgeShapeParams{
			Edge: NewPoint3([3]float64{30, 20, 10}),
		})
		if shp == nil || shp.IsNull() {
			t.Fatal("Failed to create full wedge")
		}
	})

	t.Run("LimitedWedge", func(t *testing.T) {
		ltx := 12.0
		shp := CreateWedgeShape(WedgeShapeParams{
			Edge:  NewPoint3([3]float64{25, 15, 8}),
			Limit: &WedgeFaceLimit{Values: [4]float64{10.0, 5.0, 15.0, 7.0}},
			Ltx:   &ltx,
		})
		if shp == nil || shp.IsNull() {
			t.Fatal("Failed to create limited wedge")
		}
	})
}

func TestCreatePipeShape(t *testing.T) {
	t.Run("BasicPipeShape", func(t *testing.T) {
		shp := CreatePipeShape(PipeShapeParams{
			Wire: [2]Point3{NewPoint3([3]float64{0, 0, 0}), NewPoint3([3]float64{100, 0, 0})},
			Profile: ShapeProfile{
				Type: ProfileTypeCirc,
				Data: ProfileData{Circ: CircProfile{
					Center: NewPoint3([3]float64{0, 0, 0}),
					Norm:   NewDir3FromXYZ([3]float64{0, 0, 1}),
					Radius: 10.0,
				}},
			},
		})
		if shp == nil || shp.IsNull() {
			t.Fatal("Failed to create basic pipe shape")
		}
	})

	t.Run("DirectedPipeShape", func(t *testing.T) {
		upDir := NewDir3FromXYZ([3]float64{1, 0, 0})
		shp := CreatePipeShape(PipeShapeParams{
			Wire: [2]Point3{NewPoint3([3]float64{0, 0, 0}), NewPoint3([3]float64{0, 100, 50})},
			Profile: ShapeProfile{
				Type: ProfileTypeCirc,
				Data: ProfileData{Circ: CircProfile{
					Center: NewPoint3([3]float64{0, 0, 0}),
					Norm:   NewDir3FromXYZ([3]float64{0, 0, 1}),
					Radius: 8.0,
				}},
			},
			UpDir: &upDir,
		})
		if shp == nil || shp.IsNull() {
			t.Fatal("Failed to create directed pipe shape")
		}
	})

	t.Run("ComplexProfilePipeShape", func(t *testing.T) {
		shp := CreatePipeShape(PipeShapeParams{
			Wire: [2]Point3{NewPoint3([3]float64{0, 0, 0}), NewPoint3([3]float64{50, 50, 30})},
			Profile: ShapeProfile{
				Type: ProfileTypePolygon,
				Data: ProfileData{Polygon: PolygonProfile{Edges: []Point3{
					NewPoint3([3]float64{0, 0, 0}),
					NewPoint3([3]float64{10, 0, 0}),
					NewPoint3([3]float64{15, 5, 0}),
					NewPoint3([3]float64{10, 10, 0}),
					NewPoint3([3]float64{0, 10, 0}),
				}}},
			},
		})
		if shp == nil || shp.IsNull() {
			t.Fatal("Failed to create complex profile pipe shape")
		}
	})
}

func TestMultiSegmentPipeWithSplitDistances(t *testing.T) {
	segment1 := []Point3{
		NewPoint3([3]float64{0, 0, 0}),
		NewPoint3([3]float64{13.363751136232167, -26.227833716198802, 40.422308564186096}),
	}
	segment2 := []Point3{
		NewPoint3([3]float64{13.363751136232167, -26.227833716198802, 40.422308564186096}),
		NewPoint3([3]float64{46.29231750732288, -90.69991450663656, 108.94551491551101}),
	}

	polygon1 := ShapeProfile{
		Type: ProfileTypePolygon,
		Data: ProfileData{Polygon: PolygonProfile{Edges: []Point3{
			NewPoint3([3]float64{-3.171, 2.538, 0}),
			NewPoint3([3]float64{-3.136, 3.954, 0}),
			NewPoint3([3]float64{-2.498, 5.219, 0}),
			NewPoint3([3]float64{-1.382, 6.09, 0}),
			NewPoint3([3]float64{0, 6.4, 0}),
			NewPoint3([3]float64{1.382, 6.09, 0}),
			NewPoint3([3]float64{2.498, 5.219, 0}),
			NewPoint3([3]float64{3.136, 3.954, 0}),
			NewPoint3([3]float64{3.171, 2.538, 0}),
			NewPoint3([3]float64{2.5, 0, 0}),
			NewPoint3([3]float64{-2.5, 0, 0}),
			NewPoint3([3]float64{-3.171, 2.538, 0}),
		}}},
	}

	polygon2 := ShapeProfile{
		Type: ProfileTypePolygon,
		Data: ProfileData{Polygon: PolygonProfile{Edges: []Point3{
			NewPoint3([3]float64{-3.4, 3.25, 0}),
			NewPoint3([3]float64{-2.773, 4.717, 0}),
			NewPoint3([3]float64{-1.553, 5.746, 0}),
			NewPoint3([3]float64{0, 6.115, 0}),
			NewPoint3([3]float64{1.553, 5.746, 0}),
			NewPoint3([3]float64{2.773, 4.717, 0}),
			NewPoint3([3]float64{3.4, 3.25, 0}),
			NewPoint3([3]float64{3.4, 0, 0}),
			NewPoint3([3]float64{-3.4, 0, 0}),
			NewPoint3([3]float64{-3.4, 3.25, 0}),
		}}},
	}

	polygon3 := ShapeProfile{
		Type: ProfileTypePolygon,
		Data: ProfileData{Polygon: PolygonProfile{Edges: []Point3{
			NewPoint3([3]float64{-3.078273455639578, 2.575440459011272, 0}),
			NewPoint3([3]float64{-3.036354153205542, 3.945591360596666, 0}),
			NewPoint3([3]float64{-2.415107425541498, 5.163064134049417, 0}),
			NewPoint3([3]float64{-1.339465963909452, 5.999496653245043, 0}),
			NewPoint3([3]float64{-0.00978236558095332, 6.3004796235756695, 0}),
			NewPoint3([3]float64{1.3250857438602934, 6.007776113883715, 0}),
			NewPoint3([3]float64{2.410219147892808, 5.171098830877157, 0}),
			NewPoint3([3]float64{3.0362530020384777, 3.946891104328797, 0}),
			NewPoint3([3]float64{3.0763705290048873, 2.57033053075941, 0}),
			NewPoint3([3]float64{2.4402700090676666, 0.08020179663338835, 0}),
			NewPoint3([3]float64{-2.4484020179459174, 0.08566007382641323, 0}),
			NewPoint3([3]float64{-3.078273455639578, 2.575440459011272, 0}),
		}}},
	}

	polygon4 := ShapeProfile{
		Type: ProfileTypePolygon,
		Data: ProfileData{Polygon: PolygonProfile{Edges: []Point3{
			NewPoint3([3]float64{-3.3009689384399516, 3.2638870027828157, 0}),
			NewPoint3([3]float64{-2.681019727080062, 4.6777618885065335, 0}),
			NewPoint3([3]float64{-1.5023855429647655, 5.659755134999072, 0}),
			NewPoint3([3]float64{-0.013823869618346543, 6.0159601058725585, 0}),
			NewPoint3([3]float64{1.4854596950468153, 5.672255120809437, 0}),
			NewPoint3([3]float64{2.678133803605064, 4.68537082388747, 0}),
			NewPoint3([3]float64{3.30065175118932, 3.2613984849103375, 0}),
			NewPoint3([3]float64{3.328711291934881, 0.07012788391507485, 0}),
			NewPoint3([3]float64{-3.336054557835377, 0.07688290074113246, 0}),
			NewPoint3([3]float64{-3.3009689384399516, 3.2638870027828157, 0}),
		}}},
	}

	upDir := NewDir3FromXYZ([3]float64{-0.37127704827582503, 0.7201908387390975, 0.586070396129907})

	shp := CreateMultiSegmentPipeWithSplitDistances(MultiSegmentPipeParams{
		Wires:          [][]Point3{segment1, segment2},
		Profiles:       []ShapeProfile{polygon1, polygon2},
		InnerProfiles:  []ShapeProfile{polygon3, polygon4},
		SegmentTypes:   []SegmentType{SegmentTypeLine, SegmentTypeLine},
		TransitionMode: TransitionTransformed,
		UpDir:          &upDir,
	}, 2.0, 5.0)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create polygonal profile pipe with split distances")
	}
}

// bim4d 工作量依赖体积统计: 拆分段必须产出正质量实体且体积占比精确
func TestCreatePipeSplitVolumeRatio(t *testing.T) {
	prof := circProfile([3]float64{0, 0, 0}, [3]float64{0, 0, 1}, 5.0)
	params := PipeParams{
		Wire:           []Point3{NewPoint3([3]float64{0, 0, 0}), NewPoint3([3]float64{100, 0, 0})},
		Profiles:       []ShapeProfile{prof},
		SegmentType:    SegmentTypeLine,
		TransitionMode: TransitionTransformed,
	}

	full := CreatePipe(params)
	if full == nil || full.IsNull() {
		t.Fatal("Failed to create full pipe")
	}
	fullVol := full.ComputeMass()
	// 直线段曾产出负质量壳体, 必须为正实体 (期望 ≈ π·25·100 ≈ 7854)
	if fullVol <= 0 {
		t.Fatalf("straight pipe mass %.2f is not positive", fullVol)
	}
	if fullVol < 0.9*math.Pi*25*100 || fullVol > 1.1*math.Pi*25*100 {
		t.Errorf("straight pipe volume %.1f not near π·25·100 ≈ %.1f", fullVol, math.Pi*25*100)
	}

	cases := []struct {
		name       string
		start, end float64
		expect     float64
	}{
		{"split[0,80]", 0.0, 80.0, 0.8},
		{"split[20,80]", 20.0, 80.0, 0.6},
		{"split[40,100]", 40.0, 100.0, 0.6},
		{"split[0,-1] full", 0.0, -1.0, 1.0},
	}
	for _, c := range cases {
		part := CreatePipeWithSplitDistances(params, c.start, c.end)
		if part == nil || part.IsNull() {
			t.Errorf("%s: returned nil", c.name)
			continue
		}
		v := part.ComputeMass()
		ratio := v / fullVol
		if math.Abs(ratio-c.expect) > 0.02 {
			t.Errorf("%s: volume ratio %.4f not near %.2f (vol=%.1f)", c.name, ratio, c.expect, v)
		}
	}
}
