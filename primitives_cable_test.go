package topo

import (
	"math"
	"testing"
)

func TestCreateWireStraight(t *testing.T) {
	shp := CreateWire(WireParams{
		StartPoint: NewPoint3([3]float64{0, 0, 0}),
		EndPoint:   NewPoint3([3]float64{100, 100, 50}),
		StartDir:   NewDir3FromXYZ([3]float64{1, 1, 0.5}),
		EndDir:     NewDir3FromXYZ([3]float64{1, 1, 0.5}),
		Sag:        10.0,
		Diameter:   5.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create straight wire")
	}
}

func TestCreateWireCurved(t *testing.T) {
	shp := CreateWire(WireParams{
		StartPoint: NewPoint3([3]float64{0, 0, 0}),
		EndPoint:   NewPoint3([3]float64{300, 0, 150}),
		StartDir:   NewDir3FromXYZ([3]float64{1, 0, 0}),
		EndDir:     NewDir3FromXYZ([3]float64{0, 0, 1}),
		Sag:        25.0,
		Diameter:   8.0,
		FitPoints: []Point3{
			NewPoint3([3]float64{0, 0, 0}),
			NewPoint3([3]float64{100, 100, 50}),
			NewPoint3([3]float64{200, 50, 100}),
			NewPoint3([3]float64{300, 0, 150}),
		},
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create curved wire")
	}
}

func TestCreateWireExtreme(t *testing.T) {
	shp := CreateWire(WireParams{
		StartPoint: NewPoint3([3]float64{0, 0, 0}),
		EndPoint:   NewPoint3([3]float64{200, 0, 0}),
		StartDir:   NewDir3FromXYZ([3]float64{1, 0, 0}),
		EndDir:     NewDir3FromXYZ([3]float64{1, 0, 0}),
		Sag:        50.0,
		Diameter:   2.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create extreme wire")
	}
}

func TestCreateWireWithPlace(t *testing.T) {
	pos := NewPoint3([3]float64{0, 0, 0})
	dir := NewDir3FromXYZ([3]float64{0, 0, 1})
	up := NewDir3FromXYZ([3]float64{0, 1, 0})
	shp := CreateWireWithPlace(WireParams{
		StartPoint: NewPoint3([3]float64{0, 0, 0}),
		EndPoint:   NewPoint3([3]float64{100, 100, 50}),
		StartDir:   NewDir3FromXYZ([3]float64{1, 1, 0.5}),
		EndDir:     NewDir3FromXYZ([3]float64{1, 1, 0.5}),
		Sag:        10.0,
		Diameter:   5.0,
	}, pos, dir, up)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create wire with place")
	}
}

func TestCreateWireCenterline(t *testing.T) {
	w := CreateWireCenterline(WireParams{
		StartPoint: NewPoint3([3]float64{0, 0, 0}),
		EndPoint:   NewPoint3([3]float64{100, 100, 50}),
		StartDir:   NewDir3FromXYZ([3]float64{1, 1, 0.5}),
		EndDir:     NewDir3FromXYZ([3]float64{1, 1, 0.5}),
		Sag:        10.0,
		Diameter:   5.0,
	})
	if w == nil || w.IsNull() {
		t.Fatal("Failed to create wire centerline")
	}
}

func TestSampleWirePoints(t *testing.T) {
	points := SampleWirePoints(WireParams{
		StartPoint: NewPoint3([3]float64{0, 0, 0}),
		EndPoint:   NewPoint3([3]float64{100, 0, 0}),
		StartDir:   NewDir3FromXYZ([3]float64{1, 0, 0}),
		EndDir:     NewDir3FromXYZ([3]float64{1, 0, 0}),
		Sag:        10.0,
		Diameter:   5.0,
	}, 10.0)
	if len(points) == 0 {
		t.Fatal("Expected non-empty sample points")
	}
}

func TestCreateCableStraight(t *testing.T) {
	shp := CreateCable(CableParams{
		StartPoint: NewPoint3([3]float64{0, 0, 0}),
		EndPoint:   NewPoint3([3]float64{100, 0, 0}),
		Diameter:   10.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create straight cable")
	}
}

func TestCreateCableCurved(t *testing.T) {
	shp := CreateCable(CableParams{
		StartPoint: NewPoint3([3]float64{0, 0, 0}),
		EndPoint:   NewPoint3([3]float64{150, 50, 50}),
		InflectionPoints: []Point3{
			NewPoint3([3]float64{50, 50, 0}),
			NewPoint3([3]float64{100, 50, 50}),
		},
		Radii:    []float32{20.0, 15.0},
		Diameter: 8.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create curved cable")
	}
}

func TestCreateCableExtreme(t *testing.T) {
	shp := CreateCable(CableParams{
		StartPoint: NewPoint3([3]float64{0, 0, 0}),
		EndPoint:   NewPoint3([3]float64{200, 100, 100}),
		InflectionPoints: []Point3{
			NewPoint3([3]float64{50, 100, 0}),
			NewPoint3([3]float64{100, 100, 100}),
		},
		Radii:    []float32{50.0, 30.0},
		Diameter: 2.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create extreme cable")
	}
}

func TestCreateCableWithPlace(t *testing.T) {
	pos := NewPoint3([3]float64{0, 0, 0})
	dir := NewDir3FromXYZ([3]float64{0, 0, 1})
	up := NewDir3FromXYZ([3]float64{0, 1, 0})
	shp := CreateCableWithPlace(CableParams{
		StartPoint: NewPoint3([3]float64{0, 0, 0}),
		EndPoint:   NewPoint3([3]float64{100, 0, 0}),
		Diameter:   10.0,
	}, pos, dir, up)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create cable with place")
	}
}

func TestCreateCableCenterline(t *testing.T) {
	w := CreateCableCenterline(CableParams{
		StartPoint: NewPoint3([3]float64{0, 0, 0}),
		EndPoint:   NewPoint3([3]float64{100, 0, 0}),
		Diameter:   10.0,
	})
	if w == nil || w.IsNull() {
		t.Fatal("Failed to create cable centerline")
	}
}

func TestSampleCablePoints(t *testing.T) {
	points := SampleCablePoints(CableParams{
		StartPoint: NewPoint3([3]float64{0, 0, 0}),
		EndPoint:   NewPoint3([3]float64{100, 0, 0}),
		Diameter:   10.0,
	}, 10.0)
	if len(points) == 0 {
		t.Fatal("Expected non-empty sample points")
	}
}

func TestCreateCurveCableStraight(t *testing.T) {
	shp := CreateCurveCable(CurveCableParams{
		Segments: []CurveSegment{
			{ControlPoints: []Point3{
				NewPoint3([3]float64{0, 0, 0}),
				NewPoint3([3]float64{100, 0, 0}),
			}},
		},
		CurveTypes: []CurveType{CurveTypeLine},
		Diameter:   10.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create straight curve cable")
	}
}

func TestCreateCurveCableMixed(t *testing.T) {
	shp := CreateCurveCable(CurveCableParams{
		Segments: []CurveSegment{
			{ControlPoints: []Point3{
				NewPoint3([3]float64{0, 0, 0}),
				NewPoint3([3]float64{100, 0, 0}),
			}},
			{ControlPoints: []Point3{
				NewPoint3([3]float64{100, 0, 0}),
				NewPoint3([3]float64{150, 50, 0}),
				NewPoint3([3]float64{200, 0, 0}),
			}},
			{ControlPoints: []Point3{
				NewPoint3([3]float64{200, 0, 0}),
				NewPoint3([3]float64{300, 0, 100}),
				NewPoint3([3]float64{350, -50, 150}),
			}},
		},
		CurveTypes: []CurveType{CurveTypeLine, CurveTypeArc, CurveTypeBezier},
		Diameter:   8.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create mixed curve cable")
	}
}

func TestCreateCurveCableWithPlace(t *testing.T) {
	pos := NewPoint3([3]float64{0, 0, 0})
	dir := NewDir3FromXYZ([3]float64{0, 0, 1})
	up := NewDir3FromXYZ([3]float64{0, 1, 0})
	shp := CreateCurveCableWithPlace(CurveCableParams{
		Segments: []CurveSegment{
			{ControlPoints: []Point3{
				NewPoint3([3]float64{0, 0, 0}),
				NewPoint3([3]float64{100, 0, 0}),
			}},
		},
		CurveTypes: []CurveType{CurveTypeLine},
		Diameter:   10.0,
	}, pos, dir, up)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create curve cable with place")
	}
}

func TestCreateCurveCableCenterline(t *testing.T) {
	w := CreateCurveCableCenterline(CurveCableParams{
		Segments: []CurveSegment{
			{ControlPoints: []Point3{
				NewPoint3([3]float64{0, 0, 0}),
				NewPoint3([3]float64{100, 0, 0}),
			}},
		},
		CurveTypes: []CurveType{CurveTypeLine},
		Diameter:   10.0,
	})
	if w == nil || w.IsNull() {
		t.Fatal("Failed to create curve cable centerline")
	}
}

func TestSampleCurvePoints(t *testing.T) {
	points := SampleCurvePoints(
		[][]Point3{
			{NewPoint3([3]float64{0, 0, 0}), NewPoint3([3]float64{100, 0, 0})},
		},
		[]CurveType{CurveTypeLine},
		10.0,
	)
	if len(points) == 0 {
		t.Fatal("Expected non-empty sample curve points")
	}
}

func TestCreateCableWireStraight(t *testing.T) {
	shp := CreateCableWire(CableWireParams{
		Points: []Point3{
			NewPoint3([3]float64{0, 0, 0}),
			NewPoint3([3]float64{100, 0, 0}),
		},
		OutsideDiameter: 10.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create straight cable wire")
	}
}

func TestCreateCableWireCurved(t *testing.T) {
	shp := CreateCableWire(CableWireParams{
		Points: []Point3{
			NewPoint3([3]float64{0, 0, 0}),
			NewPoint3([3]float64{50, 50, 0}),
			NewPoint3([3]float64{100, 50, 50}),
			NewPoint3([3]float64{150, 0, 100}),
		},
		OutsideDiameter: 8.0,
	})
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create curved cable wire")
	}
}

func TestCreateCableWireCenterline(t *testing.T) {
	w := CreateCableWireCenterline(CableWireParams{
		Points: []Point3{
			NewPoint3([3]float64{0, 0, 0}),
			NewPoint3([3]float64{100, 0, 0}),
		},
		OutsideDiameter: 10.0,
	})
	if w == nil || w.IsNull() {
		t.Fatal("Failed to create cable wire centerline")
	}
}

func TestCreateCableWireWithPlace(t *testing.T) {
	pos := NewPoint3([3]float64{0, 0, 0})
	dir := NewDir3FromXYZ([3]float64{0, 0, 1})
	up := NewDir3FromXYZ([3]float64{0, 1, 0})
	shp := CreateCableWireWithPlace(CableWireParams{
		Points: []Point3{
			NewPoint3([3]float64{0, 0, 0}),
			NewPoint3([3]float64{100, 0, 0}),
		},
		OutsideDiameter: 10.0,
	}, pos, dir, up)
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create cable wire with place")
	}
}

func TestCreateTransmissionLine(t *testing.T) {
	shp := CreateTransmissionLine(TransmissionLineParams{
		Type:                    "LGJ-400/35",
		SectionalArea:           425.24,
		OutsideDiameter:         26.82,
		WireWeight:              1349,
		CoefficientOfElasticity: 65000,
		ExpansionCoefficient:    0.0000205,
		RatedStrength:           103900,
	}, NewPoint3([3]float64{0, 0, 0}), NewPoint3([3]float64{1000, 0, 50}))
	if shp == nil || shp.IsNull() {
		t.Fatal("Failed to create transmission line")
	}
}

func TestCreateTransmissionCenterline(t *testing.T) {
	w := CreateTransmissionCenterline(TransmissionLineParams{
		Type:                    "LGJ-400/35",
		SectionalArea:           425.24,
		OutsideDiameter:         26.82,
		WireWeight:              1349,
		CoefficientOfElasticity: 65000,
		ExpansionCoefficient:    0.0000205,
		RatedStrength:           103900,
	}, NewPoint3([3]float64{0, 0, 0}), NewPoint3([3]float64{1000, 0, 50}))
	if w == nil || w.IsNull() {
		t.Fatal("Failed to create transmission centerline")
	}
}

func TestSampleTransmissionLinePoints(t *testing.T) {
	points := SampleTransmissionLinePoints(
		TransmissionLineParams{
			Type:                    "LGJ-400/35",
			SectionalArea:           425.24,
			OutsideDiameter:         26.82,
			WireWeight:              1349,
			CoefficientOfElasticity: 65000,
			ExpansionCoefficient:    0.0000205,
			RatedStrength:           103900,
		},
		NewPoint3([3]float64{0, 0, 0}),
		NewPoint3([3]float64{1000, 0, 50}),
		10.0,
	)
	if len(points) == 0 {
		t.Fatal("Expected non-empty transmission line sample points")
	}
	_ = math.Pi
}
