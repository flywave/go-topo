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

func TestMakeDir(t *testing.T) {
	dir := NewDir3FromXYZ([3]float64{0, 0, 0})
	fmt.Println(dir.Data())
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

func TestBug2(t *testing.T) {
	// 创建导线数据
	wires := [][]Point3{
		{
			NewPoint3([3]float64{0.000000, 0.000000, 0.000000}),
			NewPoint3([3]float64{-18.381608, -16.456729, 23.967570}),
		},
		{
			NewPoint3([3]float64{-18.381608, -16.456729, 23.967570}),
			NewPoint3([3]float64{-20.049600, -17.830275, 26.141186}),
		},
		{
			NewPoint3([3]float64{-20.049600, -17.830275, 26.141186}),
			NewPoint3([3]float64{-29.312281, -23.429547, 34.741874}),
			NewPoint3([3]float64{-55.277435, -31.565721, 41.815130}),
		},
		{
			NewPoint3([3]float64{-55.277435, -31.565721, 41.815130}),
			NewPoint3([3]float64{-255.585003, -75.656772, 31.748227}),
		},
		{
			NewPoint3([3]float64{-255.585003, -75.656772, 31.748227}),
			NewPoint3([3]float64{-328.386169, -107.483284, 77.701580}),
			NewPoint3([3]float64{-331.303108, -111.641479, 87.604189}),
		},
		{
			NewPoint3([3]float64{-331.303108, -111.641479, 87.604189}),
			NewPoint3([3]float64{-334.263097, -118.631098, 102.370422}),
		},
	}

	// 创建多边形剖面数据
	polygonPoints := []Point3{
		NewPoint3([3]float64{-3.900000, 4.000000, 0.000000}),
		NewPoint3([3]float64{-2.652000, 5.403000, 0.000000}),
		NewPoint3([3]float64{-0.939000, 6.172000, 0.000000}),
		NewPoint3([3]float64{0.939000, 6.172000, 0.000000}),
		NewPoint3([3]float64{2.652000, 5.403000, 0.000000}),
		NewPoint3([3]float64{3.900000, 4.000000, 0.000000}),
		NewPoint3([3]float64{3.900000, 0.000000, 0.000000}),
		NewPoint3([3]float64{-3.900000, 0.000000, 0.000000}),
		NewPoint3([3]float64{-3.900000, 4.000000, 0.000000}),
	}

	// 创建剖面
	profiles := []ShapeProfile{
		{
			Type: ProfileTypePolygon,
			Data: ProfileData{
				Polygon: PolygonProfile{
					Edges: polygonPoints,
				},
			},
		},
		{
			Type: ProfileTypePolygon,
			Data: ProfileData{
				Polygon: PolygonProfile{
					Edges: polygonPoints,
				},
			},
		},
		{
			Type: ProfileTypePolygon,
			Data: ProfileData{
				Polygon: PolygonProfile{
					Edges: polygonPoints,
				},
			},
		},
		{
			Type: ProfileTypePolygon,
			Data: ProfileData{
				Polygon: PolygonProfile{
					Edges: polygonPoints,
				},
			},
		},
		{
			Type: ProfileTypePolygon,
			Data: ProfileData{
				Polygon: PolygonProfile{
					Edges: polygonPoints,
				},
			},
		},
		{
			Type: ProfileTypePolygon,
			Data: ProfileData{
				Polygon: PolygonProfile{
					Edges: polygonPoints,
				},
			},
		},
	}

	// 创建线段类型
	segmentTypes := []SegmentType{
		SegmentTypeLine,
		SegmentTypeLine,
		SegmentTypeThreePointArc,
		SegmentTypeLine,
		SegmentTypeThreePointArc,
		SegmentTypeLine,
	}

	// 设置过渡模式
	transitionMode := TransitionTransformed

	// 创建上方向
	upDir := NewDir3FromXYZ([3]float64{-0.301612, 0.874964, 0.378773})

	params := MultiSegmentPipeParams{
		Wires:          wires,
		Profiles:       profiles,
		SegmentTypes:   segmentTypes,
		TransitionMode: transitionMode,
		UpDir:          &upDir,
	}

	shp := CreateMultiSegmentPipe(params)
	if !shp.IsValid() {
		t.Fatal("Failed to create pipe")
	}
}

func TestBug3(t *testing.T) {
	// 创建导线数据
	wires := [][]Point3{
		{
			NewPoint3([3]float64{0.000000, 0.000000, 0.000000}),
			NewPoint3([3]float64{-35.691625, -32.978268, 46.548679}),
		},
		{
			NewPoint3([3]float64{-35.691625, -32.978268, 46.548679}),
			NewPoint3([3]float64{-37.229320, -36.179758, 52.584004}),
			NewPoint3([3]float64{-33.071860, -37.840417, 59.567516}),
		},
		{
			NewPoint3([3]float64{-33.071860, -37.840417, 59.567516}),
			NewPoint3([3]float64{150.857507, -37.395352, 200.922442}),
		},
	}

	// 创建多边形剖面数据
	polygonPoints := []Point3{
		NewPoint3([3]float64{-1.500000, 2.100000, 0.000000}),
		NewPoint3([3]float64{-0.875000, 2.758000, 0.000000}),
		NewPoint3([3]float64{0.000000, 3.000000, 0.000000}),
		NewPoint3([3]float64{0.875000, 2.758000, 0.000000}),
		NewPoint3([3]float64{1.500000, 2.100000, 0.000000}),
		NewPoint3([3]float64{1.500000, 0.000000, 0.000000}),
		NewPoint3([3]float64{-1.500000, 0.000000, 0.000000}),
		NewPoint3([3]float64{-1.500000, 2.100000, 0.000000}),
	}

	// 创建剖面
	profiles := []ShapeProfile{
		{
			Type: ProfileTypePolygon,
			Data: ProfileData{
				Polygon: PolygonProfile{
					Edges: polygonPoints,
				},
			},
		},
		{
			Type: ProfileTypePolygon,
			Data: ProfileData{
				Polygon: PolygonProfile{
					Edges: polygonPoints,
				},
			},
		},
		{
			Type: ProfileTypePolygon,
			Data: ProfileData{
				Polygon: PolygonProfile{
					Edges: polygonPoints,
				},
			},
		},
	}

	// 创建线段类型
	segmentTypes := []SegmentType{
		SegmentTypeLine,
		SegmentTypeThreePointArc,
		SegmentTypeLine,
	}

	// 设置过渡模式
	transitionMode := TransitionTransformed

	// 创建上方向
	upDir := NewDir3FromXYZ([3]float64{-0.301639, 0.874967, 0.378744})

	params := MultiSegmentPipeParams{
		Wires:          wires,
		Profiles:       profiles,
		InnerProfiles:  nil, // 根据数据，InnerProfiles 为 nil
		SegmentTypes:   segmentTypes,
		TransitionMode: transitionMode,
		UpDir:          &upDir,
	}

	shp := CreateMultiSegmentPipe(params)
	if !shp.IsValid() {
		t.Fatal("Failed to create pipe")
	}

}

func TestBug4(t *testing.T) {
	// 创建导线数据 - 单一直线段
	wires := [][]Point3{
		{
			NewPoint3([3]float64{0.000000, 0.000000, 0.000000}),
			NewPoint3([3]float64{-128.976600, -1.038238, -99.629249}),
		},
	}

	// 创建外多边形剖面数据 (20个点)
	outerPolygonPoints := []Point3{
		NewPoint3([3]float64{0.000000, 16.100000, 0.000000}),
		NewPoint3([3]float64{14.250000, 16.100000, 0.000000}),
		NewPoint3([3]float64{14.250000, 17.980000, 0.000000}),
		NewPoint3([3]float64{14.049000, 18.948000, 0.000000}),
		NewPoint3([3]float64{13.701000, 19.873000, 0.000000}),
		NewPoint3([3]float64{13.213000, 20.734000, 0.000000}),
		NewPoint3([3]float64{12.599000, 21.508000, 0.000000}),
		NewPoint3([3]float64{9.375000, 23.710000, 0.000000}),
		NewPoint3([3]float64{5.778000, 25.228000, 0.000000}),
		NewPoint3([3]float64{1.952000, 26.002000, 0.000000}),
		NewPoint3([3]float64{-1.952000, 26.002000, 0.000000}),
		NewPoint3([3]float64{-5.778000, 25.228000, 0.000000}),
		NewPoint3([3]float64{-9.375000, 23.710000, 0.000000}),
		NewPoint3([3]float64{-12.599000, 21.508000, 0.000000}),
		NewPoint3([3]float64{-13.213000, 20.734000, 0.000000}),
		NewPoint3([3]float64{-13.701000, 19.873000, 0.000000}),
		NewPoint3([3]float64{-14.049000, 18.948000, 0.000000}),
		NewPoint3([3]float64{-14.250000, 17.980000, 0.000000}),
		NewPoint3([3]float64{-14.259000, 16.100000, 0.000000}),
		NewPoint3([3]float64{0.000000, 16.100000, 0.000000}),
	}

	// 创建内多边形剖面数据 (20个点)
	innerPolygonPoints := []Point3{
		NewPoint3([3]float64{-0.000010, 16.200000, 0.000000}),
		NewPoint3([3]float64{14.154677, 16.130224, 0.000000}),
		NewPoint3([3]float64{14.151671, 17.998204, 0.000000}),
		NewPoint3([3]float64{13.949699, 18.959806, 0.000000}),
		NewPoint3([3]float64{13.601148, 19.878432, 0.000000}),
		NewPoint3([3]float64{13.113004, 20.733124, 0.000000}),
		NewPoint3([3]float64{12.499248, 21.500956, 0.000000}),
		NewPoint3([3]float64{9.280031, 23.678682, 0.000000}),
		NewPoint3([3]float64{5.699827, 25.165638, 0.000000}),
		NewPoint3([3]float64{1.917907, 25.907991, 0.000000}),
		NewPoint3([3]float64{-1.917921, 25.907986, 0.000000}),
		NewPoint3([3]float64{-5.699832, 25.165632, 0.000000}),
		NewPoint3([3]float64{-9.280031, 23.678680, 0.000000}),
		NewPoint3([3]float64{-12.499248, 21.500956, 0.000000}),
		NewPoint3([3]float64{-13.113004, 20.733124, 0.000000}),
		NewPoint3([3]float64{-13.601148, 19.878432, 0.000000}),
		NewPoint3([3]float64{-13.949699, 18.959806, 0.000000}),
		NewPoint3([3]float64{-14.151671, 17.998206, 0.000000}),
		NewPoint3([3]float64{-14.163672, 16.130208, 0.000000}),
		NewPoint3([3]float64{-0.000010, 16.200000, 0.000000}),
	}

	// 创建外剖面
	outerProfile := ShapeProfile{
		Type: ProfileTypePolygon,
		Data: ProfileData{
			Polygon: PolygonProfile{
				Edges: outerPolygonPoints,
			},
		},
	}

	// 创建内剖面
	innerProfile := ShapeProfile{
		Type: ProfileTypePolygon,
		Data: ProfileData{
			Polygon: PolygonProfile{
				Edges: innerPolygonPoints,
			},
		},
	}

	// 创建剖面数组 (只有一个剖面)
	profiles := []ShapeProfile{outerProfile}

	// 创建内剖面数组
	innerProfiles := []ShapeProfile{innerProfile}

	// 创建线段类型 (只有直线段)
	segmentTypes := []SegmentType{
		SegmentTypeLine,
	}

	// 设置过渡模式
	transitionMode := TransitionTransformed

	// 创建上方向
	upDir := NewDir3FromXYZ([3]float64{-0.301619, 0.874963, 0.378768})

	params := MultiSegmentPipeParams{
		Wires:          wires,
		Profiles:       profiles,
		InnerProfiles:  innerProfiles,
		SegmentTypes:   segmentTypes,
		TransitionMode: transitionMode,
		UpDir:          &upDir,
	}

	// 使用分割距离创建管道
	shp := CreateMultiSegmentPipeWithSplitDistances(params, 64.300000, 68.400000)
	if !shp.IsValid() {
		t.Fatal("Failed to create pipe with split distances")
	}
}
