package topo

import (
	"fmt"
	"testing"
)

func TestMakeArc(t *testing.T) {

	points := []Point3{
		NewPoint3([3]float64{88.27510582562536, 47.17234171088785, 1.3518126332201064}),
		NewPoint3([3]float64{-2.002824238501489, 61.12643328495324, -79.24088457413018}),
		NewPoint3([3]float64{0, 0, 0}),
	}

	// 创建圆弧
	curve := GeomMakeArcOfPoint(points[0], points[1], points[2])
	if curve == nil {
		t.Fatal("Failed to create curve")
	}

	c := curve.Curve()

	// 创建边
	edge := TopoMakeEdgeFromCurve(*c)
	if edge == nil || edge.IsNull() {
		t.Fatal("Failed to create edge")
	}
}

func TestMaakeWire(t *testing.T) {

	points := []Point3{
		NewPoint3([3]float64{0, 0, 0}),
		NewPoint3([3]float64{88.27510582562536, 47.17234171088785, 1.3518126332201064}),
	}

	pro := TopoMakeWireFromCircle(10, NewPoint3([3]float64{0, 0, 0}), NewDir3FromXYZ([3]float64{0, 0, 1}))
	length := WireLength(pro)
	fmt.Println(length)

	w := TopoMakeWireFromCombineCurve([][]Point3{points}, []SweepCurveType{0})
	sld := TopoMakeSolid()
	sld.SweepWire(w, []*Wire{pro}, 0)
	fmt.Println(sld.IsValid())
	// length := WireLength(w)
	// t.Log(length)
}

func TestMaakeWire2(t *testing.T) {
	points := []Point3{
		NewPoint3([3]float64{0, 0, 0}),
		NewPoint3([3]float64{46.3256, -90.7646, 108.893}),
		NewPoint3([3]float64{46.3256, -90.7646, 108.893}),
		NewPoint3([3]float64{131.694, -256.482, -2.52019}),
		NewPoint3([3]float64{131.694, -256.482, -2.52019}),
		NewPoint3([3]float64{176.996, -427.627, 247.322}),
		NewPoint3([3]float64{176.996, -427.627, 247.322}),
		NewPoint3([3]float64{300.229, -1026.2, 570.908}),
		NewPoint3([3]float64{300.229, -1026.2, 570.908}),
		NewPoint3([3]float64{314.317, -1038.7, 581.424}),
		NewPoint3([3]float64{314.317, -1038.7, 581.424}),
		NewPoint3([3]float64{329.994, -1060.71, 618.145}),
	}

	var edges []Edge
	for i := 0; i < len(points); i += 2 {
		edge := TopoMakeEdgeFromTwoPoint(points[i], points[i+1])
		edges = append(edges, *edge)
	}
	w := TopoMakeWireFromEdges(edges)
	if !w.IsValid() {
		t.Fatal("Failed to create wire")
	}
}

func TestBuge(t *testing.T) {
	points := [][]Point3{
		{
			NewPoint3([3]float64{0, 0, 0}),
			NewPoint3([3]float64{13.363751136232167, -26.227833716198802, 40.422308564186096}),
		},
		{
			NewPoint3([3]float64{13.363751136232167, -26.227833716198802, 40.422308564186096}),
			NewPoint3([3]float64{46.29231750732288, -90.69991450663656, 108.94551491551101}),
		},
	}

	profile1 := ShapeProfile{
		Type: ProfileTypePolygon,
		Data: ProfileData{
			Polygon: PolygonProfile{
				Edges: []Point3{
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
				},
			},
		},
	}

	profile2 := ShapeProfile{
		Type: ProfileTypePolygon,
		Data: ProfileData{
			Polygon: PolygonProfile{
				Edges: []Point3{
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
				},
			},
		},
	}

	innerProfile1 := ShapeProfile{
		Type: ProfileTypePolygon,
		Data: ProfileData{
			Polygon: PolygonProfile{
				Edges: []Point3{
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
				},
			},
		},
	}

	innerProfile2 := ShapeProfile{
		Type: ProfileTypePolygon,
		Data: ProfileData{
			Polygon: PolygonProfile{
				Edges: []Point3{
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
				},
			},
		},
	}

	_ = innerProfile1
	_ = innerProfile2

	dir := NewDir3FromXYZ([3]float64{-0.37127704827582503, 0.7201908387390975, 0.586070396129907})

	param := MultiSegmentPipeParams{
		Wires: points,
		SegmentTypes: []SegmentType{
			SegmentTypeLine,
			SegmentTypeLine,
		},
		Profiles:       []ShapeProfile{profile1, profile2},
		InnerProfiles:  []ShapeProfile{innerProfile1, innerProfile2},
		TransitionMode: TransitionTransformed,
		UpDir:          &dir,
	}

	shp := CreateMultiSegmentPipe(param)

	if shp == nil {
		t.Fatal("Failed to create shp")
	}
}
