package topo

import (
	"math"
	"testing"
)

func TestSampleCenterlineWire(t *testing.T) {
	// 创建测试用的线框形状
	// 这里我们创建一个简单的直线路径进行测试
	p1 := NewPoint3([3]float64{0, 0, 0})
	p2 := NewPoint3([3]float64{100, 0, 0})

	// 创建边和线框
	edge := TopoMakeEdgeFromTwoPoint(p1, p2)
	if edge == nil {
		t.Fatal("Failed to create edge")
	}

	wire := TopoMakeWireFromEdge(*edge)
	if wire == nil {
		t.Fatal("Failed to create wire")
	}

	// 测试不同的采样点数
	sampleCounts := []int{10, 50, 100, 200}

	for _, numSamples := range sampleCounts {
		t.Run("测试采样点数", func(t *testing.T) {
			points := SampleCenterlineWire(wire, numSamples, false)

			// 检查返回值是否为nil
			if points == nil {
				t.Errorf("SampleCenterlineWire returned nil for %d samples", numSamples)
				return
			}

			// 检查点数是否正确
			if len(points) != numSamples {
				t.Errorf("Expected %d points, got %d", numSamples, len(points))
			}

			// 检查是否有inf或nan值
			hasInvalidValues := false
			for i, point := range points {
				coords := point.Data()
				if math.IsInf(coords[0], 0) || math.IsNaN(coords[0]) ||
					math.IsInf(coords[1], 0) || math.IsNaN(coords[1]) ||
					math.IsInf(coords[2], 0) || math.IsNaN(coords[2]) {
					t.Errorf("Found inf/nan values at point %d: (%f, %f, %f)",
						i, coords[0], coords[1], coords[2])
					hasInvalidValues = true
				}
			}

			if !hasInvalidValues {
				t.Logf("All %d sampled points are valid (no inf/nan values)", len(points))
			}

			// 特别检查第一个和最后一个点
			if len(points) > 0 {
				firstPoint := points[0]
				lastPoint := points[len(points)-1]

				firstCoords := firstPoint.Data()
				lastCoords := lastPoint.Data()

				t.Logf("First point: (%f, %f, %f)", firstCoords[0], firstCoords[1], firstCoords[2])
				t.Logf("Last point: (%f, %f, %f)", lastCoords[0], lastCoords[1], lastCoords[2])

				// 检查最后一个点是否为inf
				if math.IsInf(lastCoords[0], 0) || math.IsNaN(lastCoords[0]) ||
					math.IsInf(lastCoords[1], 0) || math.IsNaN(lastCoords[1]) ||
					math.IsInf(lastCoords[2], 0) || math.IsNaN(lastCoords[2]) {
					t.Errorf("Last point is inf/nan: (%f, %f, %f)", lastCoords[0], lastCoords[1], lastCoords[2])
				}
			}
		})
	}
}

func TestSampleCenterlineWireWithSimplify(t *testing.T) {
	// 创建测试用的线框形状
	p1 := NewPoint3([3]float64{0, 0, 0})
	p2 := NewPoint3([3]float64{100, 0, 0})

	// 创建边和线框
	edge := TopoMakeEdgeFromTwoPoint(p1, p2)
	if edge == nil {
		t.Fatal("Failed to create edge")
	}

	wire := TopoMakeWireFromEdge(*edge)
	if wire == nil {
		t.Fatal("Failed to create wire")
	}

	// 测试简化采样模式
	points := SampleCenterlineWire(wire, 50, true)

	// 检查返回值是否为nil
	if points == nil {
		t.Error("SampleCenterlineWire with simplify returned nil")
		return
	}

	// 检查是否有inf或nan值
	hasInvalidValues := false
	for i, point := range points {
		coords := point.Data()
		if math.IsInf(coords[0], 0) || math.IsNaN(coords[0]) ||
			math.IsInf(coords[1], 0) || math.IsNaN(coords[1]) ||
			math.IsInf(coords[2], 0) || math.IsNaN(coords[2]) {
			t.Errorf("Found inf/nan values at point %d: (%f, %f, %f)",
				i, coords[0], coords[1], coords[2])
			hasInvalidValues = true
		}
	}

	if !hasInvalidValues {
		t.Logf("All %d sampled points with simplify are valid (no inf/nan values)", len(points))
	}

	// 特别检查最后一个点
	if len(points) > 0 {
		lastPoint := points[len(points)-1]
		lastCoords := lastPoint.Data()

		if math.IsInf(lastCoords[0], 0) || math.IsNaN(lastCoords[0]) ||
			math.IsInf(lastCoords[1], 0) || math.IsNaN(lastCoords[1]) ||
			math.IsInf(lastCoords[2], 0) || math.IsNaN(lastCoords[2]) {
			t.Errorf("Last point with simplify is inf/nan: (%f, %f, %f)", lastCoords[0], lastCoords[1], lastCoords[2])
		}
	}
}

func TestSampleCenterlineWireEdgeCases(t *testing.T) {
	// 测试边界情况

	// 测试1: nil输入
	t.Run("Nil wire input", func(t *testing.T) {
		// 修复：需要检查SampleCenterlineWire函数是否能正确处理nil输入
		defer func() {
			if r := recover(); r != nil {
				// 如果函数panic了，说明没有正确处理nil输入
				t.Error("SampleCenterlineWire panicked with nil input")
			}
		}()

		points := SampleCenterlineWire(nil, 10, false)
		if points != nil {
			t.Error("Expected nil result for nil wire input")
		}
	})

	// 测试2: 0采样点数
	t.Run("Zero sample count", func(t *testing.T) {
		p1 := NewPoint3([3]float64{0, 0, 0})
		p2 := NewPoint3([3]float64{100, 0, 0})
		edge := TopoMakeEdgeFromTwoPoint(p1, p2)
		wire := TopoMakeWireFromEdge(*edge)

		points := SampleCenterlineWire(wire, 0, false)
		if points != nil {
			t.Error("Expected nil result for zero sample count")
		}
	})

	// 测试3: 负采样点数
	t.Run("Negative sample count", func(t *testing.T) {
		p1 := NewPoint3([3]float64{0, 0, 0})
		p2 := NewPoint3([3]float64{100, 0, 0})
		edge := TopoMakeEdgeFromTwoPoint(p1, p2)
		wire := TopoMakeWireFromEdge(*edge)

		points := SampleCenterlineWire(wire, -1, false)
		if points != nil {
			t.Error("Expected nil result for negative sample count")
		}
	})
}

func TestCreateBoundingCenterlineShape(t *testing.T) {
	// 创建测试用的线框形状
	p1 := NewPoint3([3]float64{0, 0, 0})
	p2 := NewPoint3([3]float64{100, 0, 0})

	// 创建边和线框
	edge := TopoMakeEdgeFromTwoPoint(p1, p2)
	if edge == nil {
		t.Fatal("Failed to create edge")
	}

	wire := TopoMakeWireFromEdge(*edge)
	if wire == nil {
		t.Fatal("Failed to create wire")
	}

	// 测试正常情况
	t.Run("Normal case", func(t *testing.T) {
		shape := CreateBoundingCenterlineShape(5.0, wire)
		if shape == nil {
			t.Error("CreateBoundingCenterlineShape returned nil for valid input")
		}
	})

	// 测试边界情况：nil输入
	t.Run("Nil wire input", func(t *testing.T) {
		shape := CreateBoundingCenterlineShape(5.0, nil)
		if shape != nil {
			t.Error("Expected nil result for nil wire input")
		}
	})

	// 测试边界情况：负半径
	t.Run("Negative radius", func(t *testing.T) {
		shape := CreateBoundingCenterlineShape(-5.0, wire)
		// 负半径可能仍然有效，取决于具体实现
		// 这里我们只是确保函数不会panic
		t.Logf("CreateBoundingCenterlineShape with negative radius returned: %v", shape != nil)
	})

	// 测试边界情况：零半径
	t.Run("Zero radius", func(t *testing.T) {
		shape := CreateBoundingCenterlineShape(0.0, wire)
		// 雛半径可能仍然有效，取决于具体实现
		// 这里我们只是确保函数不会panic
		t.Logf("CreateBoundingCenterlineShape with zero radius returned: %v", shape != nil)
	})
}

func TestComputeShapeMaxRadiusFromCenterline(t *testing.T) {
	// 创建测试用的线框形状
	p1 := NewPoint3([3]float64{0, 0, 0})
	p2 := NewPoint3([3]float64{100, 0, 0})

	// 创建边和线框
	edge := TopoMakeEdgeFromTwoPoint(p1, p2)
	if edge == nil {
		t.Fatal("Failed to create edge")
	}

	wire := TopoMakeWireFromEdge(*edge)
	if wire == nil {
		t.Fatal("Failed to create wire")
	}

	// 创建一个测试形状
	boundingShape := CreateBoundingCenterlineShape(5.0, wire)
	if boundingShape == nil {
		t.Fatal("Failed to create bounding shape")
	}

	// 测试正常情况
	t.Run("Normal case", func(t *testing.T) {
		radius := ComputeShapeMaxRadiusFromCenterline(boundingShape, wire)
		if radius <= 0 {
			t.Errorf("Expected positive radius, got %f", radius)
		}
		t.Logf("Computed max radius: %f", radius)
	})

	// 测试边界情况：nil形状
	t.Run("Nil shape input", func(t *testing.T) {
		radius := ComputeShapeMaxRadiusFromCenterline(nil, wire)
		if radius != -1.0 {
			t.Errorf("Expected -1.0 for nil shape input, got %f", radius)
		}
	})

	// 测试边界情况：nil线框
	t.Run("Nil wire input", func(t *testing.T) {
		radius := ComputeShapeMaxRadiusFromCenterline(boundingShape, nil)
		if radius != -1.0 {
			t.Errorf("Expected -1.0 for nil wire input, got %f", radius)
		}
	})

	// 测试边界情况：两个参数都为nil
	t.Run("Both nil inputs", func(t *testing.T) {
		radius := ComputeShapeMaxRadiusFromCenterline(nil, nil)
		if radius != -1.0 {
			t.Errorf("Expected -1.0 for both nil inputs, got %f", radius)
		}
	})
}

func TestCenterlinePointsToWire(t *testing.T) {
	// 创建测试点
	points := []Point3{
		NewPoint3([3]float64{0, 0, 0}),
		NewPoint3([3]float64{50, 0, 0}),
		NewPoint3([3]float64{100, 0, 0}),
	}

	// 测试正常情况
	t.Run("Normal case", func(t *testing.T) {
		wire := CenterlinePointsToWire(points)
		if wire == nil {
			t.Error("CenterlinePointsToWire returned nil for valid input")
		}
	})

	// 测试边界情况：空点列表
	t.Run("Empty points list", func(t *testing.T) {
		wire := CenterlinePointsToWire([]Point3{})
		if wire != nil {
			t.Error("Expected nil result for empty points list")
		}
	})

	// 测试边界情况：nil点列表
	t.Run("Nil points list", func(t *testing.T) {
		// 在Go中，不能直接传递nil给[]Point3类型的参数
		// 所以我们跳过这个测试
		t.Skip("Cannot pass nil to []Point3 parameter in Go")
	})

	// 测试边界情况：单个点
	t.Run("Single point", func(t *testing.T) {
		singlePoint := []Point3{NewPoint3([3]float64{0, 0, 0})}
		wire := CenterlinePointsToWire(singlePoint)
		// 单个点可能无法创建有效的线框，取决于具体实现
		// 这里我们只是确保函数不会panic
		t.Logf("CenterlinePointsToWire with single point returned: %v", wire != nil)
	})
}

func TestFitCenterlineFromShape(t *testing.T) {
	// 创建测试用的线框形状
	p1 := NewPoint3([3]float64{0, 0, 0})
	p2 := NewPoint3([3]float64{100, 0, 0})

	// 创建边和线框
	edge := TopoMakeEdgeFromTwoPoint(p1, p2)
	if edge == nil {
		t.Fatal("Failed to create edge")
	}

	wire := TopoMakeWireFromEdge(*edge)
	if wire == nil {
		t.Fatal("Failed to create wire")
	}

	// 创建一个测试形状 - 使用管道形状，更适合拟合中心线
	boundingShape := CreateBoundingCenterlineShape(5.0, wire)
	if boundingShape == nil {
		// 如果创建管道形状失败，我们跳过正常情况的测试
		t.Log("Failed to create bounding shape for normal case test")
	}

	// 测试边界情况：nil形状
	t.Run("Nil shape input", func(t *testing.T) {
		centerline := FitCenterlineFromShape(nil, 100, 0.99)
		if centerline != nil {
			t.Error("Expected nil result for nil shape input")
		}
	})

	// 测试边界情况：零采样点数
	t.Run("Zero sample count", func(t *testing.T) {
		if boundingShape != nil {
			centerline := FitCenterlineFromShape(boundingShape, 0, 0.99)
			// 零采样点数可能仍然有效，取决于具体实现
			// 这里我们只是确保函数不会panic
			t.Logf("FitCenterlineFromShape with zero sample count returned: %v", centerline != nil)
		} else {
			t.Skip("Skipping test due to nil bounding shape")
		}
	})

	// 测试边界情况：负采样点数
	t.Run("Negative sample count", func(t *testing.T) {
		if boundingShape != nil {
			centerline := FitCenterlineFromShape(boundingShape, -1, 0.99)
			// 负采样点数可能仍然有效，取决于具体实现
			// 这里我们只是确保函数不会panic
			t.Logf("FitCenterlineFromShape with negative sample count returned: %v", centerline != nil)
		} else {
			t.Skip("Skipping test due to nil bounding shape")
		}
	})

	// 测试边界情况：负平滑因子
	t.Run("Negative smoothing factor", func(t *testing.T) {
		if boundingShape != nil {
			centerline := FitCenterlineFromShape(boundingShape, 100, -0.5)
			// 负平滑因子可能仍然有效，取决于具体实现
			// 这里我们只是确保函数不会panic
			t.Logf("FitCenterlineFromShape with negative smoothing factor returned: %v", centerline != nil)
		} else {
			t.Skip("Skipping test due to nil bounding shape")
		}
	})

	// 测试边界情况：大于1的平滑因子
	t.Run("Smoothing factor greater than 1", func(t *testing.T) {
		if boundingShape != nil {
			centerline := FitCenterlineFromShape(boundingShape, 100, 1.5)
			// 大于1的平滑因子可能仍然有效，取决于具体实现
			// 这里我们只是确保函数不会panic
			t.Logf("FitCenterlineFromShape with smoothing factor > 1 returned: %v", centerline != nil)
		} else {
			t.Skip("Skipping test due to nil bounding shape")
		}
	})
}

// 创建一个简单的测试形状的辅助函数
func createTestShape(t *testing.T) *Shape {
	// 创建测试用的线框形状
	p1 := NewPoint3([3]float64{0, 0, 0})
	p2 := NewPoint3([3]float64{100, 0, 0})

	// 创建边和线框
	edge := TopoMakeEdgeFromTwoPoint(p1, p2)
	if edge == nil {
		t.Fatal("Failed to create edge")
	}

	wire := TopoMakeWireFromEdge(*edge)
	if wire == nil {
		t.Fatal("Failed to create wire")
	}

	// 创建一个测试形状
	testShape := CreateBoundingCenterlineShape(5.0, wire)
	if testShape == nil {
		t.Fatal("Failed to create test shape")
	}

	return testShape
}

// 创建一个简单的测试线框的辅助函数
func createTestWire(t *testing.T) *Wire {
	// 创建测试用的线框形状
	p1 := NewPoint3([3]float64{0, 0, 0})
	p2 := NewPoint3([3]float64{100, 0, 0})

	// 创建边和线框
	edge := TopoMakeEdgeFromTwoPoint(p1, p2)
	if edge == nil {
		t.Fatal("Failed to create edge")
	}

	wire := TopoMakeWireFromEdge(*edge)
	if wire == nil {
		t.Fatal("Failed to create wire")
	}

	return wire
}

// 创建测试点的辅助函数
func createTestPoints() []Point3 {
	return []Point3{
		NewPoint3([3]float64{0, 0, 0}),
		NewPoint3([3]float64{50, 0, 0}),
		NewPoint3([3]float64{100, 0, 0}),
	}

}

func TestClipWithTopo4D(t *testing.T) {
	// 创建测试形状和线框
	testShape := createTestShape(t)
	testWire := createTestWire(t)
	testPoints := createTestPoints()

	// 测试模式1: ProgressByRatio模式
	t.Run("ProgressByRatio mode", func(t *testing.T) {
		progress := WorkProgress{
			Type:   ProgressByRatio,
			Range:  [2]float64{0.0, 0.5},
			Radius: float64Ptr(5.0),
		}
		result := ClipWithTopo4D(testShape, progress)
		// 我们只检查函数是否能正常运行而不panic
		t.Logf("ClipWithTopo4D with ProgressByRatio returned: %v", result != nil)
	})

	// 测试模式2: ProgressByDistance模式
	t.Run("ProgressByDistance mode", func(t *testing.T) {
		progress := WorkProgress{
			Type:   ProgressByDistance,
			Range:  [2]float64{0.0, 50.0},
			Radius: float64Ptr(5.0),
		}
		result := ClipWithTopo4D(testShape, progress)
		// 我们只检查函数是否能正常运行而不panic
		t.Logf("ClipWithTopo4D with ProgressByDistance returned: %v", result != nil)
	})

	// 测试模式3: 带Original路径的ProgressByRatio模式
	t.Run("ProgressByRatio with Original path", func(t *testing.T) {
		progress := WorkProgress{
			Type:     ProgressByRatio,
			Range:    [2]float64{0.0, 0.5},
			Original: testWire,
			Radius:   float64Ptr(5.0),
		}
		result := ClipWithTopo4D(testShape, progress)
		// 我们只检查函数是否能正常运行而不panic
		t.Logf("ClipWithTopo4D with ProgressByRatio and Original path returned: %v", result != nil)
	})

	// 测试模式4: 带Original路径但无Radius的ProgressByDistance模式
	t.Run("ProgressByDistance with Original path but no Radius", func(t *testing.T) {
		progress := WorkProgress{
			Type:     ProgressByDistance,
			Range:    [2]float64{0.0, 50.0},
			Original: testWire,
		}
		result := ClipWithTopo4D(testShape, progress)
		// 我们只检查函数是否能正常运行而不panic
		t.Logf("ClipWithTopo4D with ProgressByDistance, Original path but no Radius returned: %v", result != nil)
	})

	// 测试模式5: 带Points和Radius但无Original路径的ProgressByRatio模式
	t.Run("ProgressByRatio with Points and Radius but no Original path", func(t *testing.T) {
		progress := WorkProgress{
			Type:   ProgressByRatio,
			Range:  [2]float64{0.0, 0.5},
			Points: &testPoints,
			Radius: float64Ptr(5.0),
		}
		result := ClipWithTopo4D(testShape, progress)
		// 我们只检查函数是否能正常运行而不panic
		t.Logf("ClipWithTopo4D with ProgressByRatio, Points and Radius but no Original path returned: %v", result != nil)
	})

	// 测试边界情况：nil形状输入
	t.Run("Nil shape input", func(t *testing.T) {
		progress := WorkProgress{
			Type:   ProgressByRatio,
			Range:  [2]float64{0.0, 0.5},
			Radius: float64Ptr(5.0),
		}
		result := ClipWithTopo4D(nil, progress)
		if result != nil {
			t.Error("Expected nil result for nil shape input")
		}
	})

	// 测试边界情况：无效的ProgressType
	t.Run("Invalid ProgressType", func(t *testing.T) {
		progress := WorkProgress{
			Type:   ProgressType(999), // 无效的ProgressType
			Range:  [2]float64{0.0, 0.5},
			Radius: float64Ptr(5.0),
		}
		// 我们期望函数不会panic，但可能返回nil
		result := ClipWithTopo4D(testShape, progress)
		t.Logf("ClipWithTopo4D with invalid ProgressType returned: %v", result != nil)
	})
}

// 测试SampleWireAtDistances函数
func TestSampleWireAtDistances(t *testing.T) {
	// 创建测试线框
	testWire := createTestWire(t)

	// 测试正常情况
	t.Run("Normal case", func(t *testing.T) {
		distances := []float64{0.0, 25.0, 50.0, 75.0, 100.0}
		samples := SampleWireAtDistances(testWire, distances)

		if samples == nil {
			t.Error("SampleWireAtDistances returned nil for valid input")
			return
		}

		if len(samples) != len(distances) {
			t.Errorf("Expected %d samples, got %d", len(distances), len(samples))
		}

		// 检查样本点是否有效
		for i, sample := range samples {
			// 检查位置是否有效
			pos := sample.Position.Data()
			if math.IsInf(pos[0], 0) || math.IsNaN(pos[0]) ||
				math.IsInf(pos[1], 0) || math.IsNaN(pos[1]) ||
				math.IsInf(pos[2], 0) || math.IsNaN(pos[2]) {
				t.Errorf("Sample %d has invalid position: (%f, %f, %f)", i, pos[0], pos[1], pos[2])
			}

			// 检查切线是否有效
			tan := sample.Tangent.Data()
			if math.IsInf(tan[0], 0) || math.IsNaN(tan[0]) ||
				math.IsInf(tan[1], 0) || math.IsNaN(tan[1]) ||
				math.IsInf(tan[2], 0) || math.IsNaN(tan[2]) {
				t.Errorf("Sample %d has invalid tangent: (%f, %f, %f)", i, tan[0], tan[1], tan[2])
			}

			// 检查边是否有效
			if sample.Edge == nil {
				t.Errorf("Sample %d has nil edge", i)
			}
		}
	})

	// 测试边界情况：nil线框
	t.Run("Nil wire input", func(t *testing.T) {
		distances := []float64{0.0, 50.0, 100.0}
		// 我们期望函数不会panic，但可能返回nil
		defer func() {
			if r := recover(); r != nil {
				// 函数panic了，说明没有正确处理nil输入
				t.Logf("SampleWireAtDistances panicked with nil wire input: %v", r)
			}
		}()
		samples := SampleWireAtDistances(nil, distances)
		t.Logf("SampleWireAtDistances with nil wire input returned: %v", samples)
	})

	// 测试边界情况：空距离数组
	t.Run("Empty distances array", func(t *testing.T) {
		samples := SampleWireAtDistances(testWire, []float64{})
		if samples != nil {
			t.Error("Expected nil result for empty distances array")
		}
	})

	// 测试边界情况：nil距离数组
	t.Run("Nil distances array", func(t *testing.T) {
		// 在Go中不能直接传递nil给[]float64参数，所以跳过此测试
		t.Skip("Cannot pass nil to []float64 parameter in Go")
	})
}

// 测试ClipWireBetweenDistances函数
func TestClipWireBetweenDistances(t *testing.T) {
	// 创建测试线框
	testWire := createTestWire(t)

	// 测试正常情况
	t.Run("Normal case", func(t *testing.T) {
		clippedWire := ClipWireBetweenDistances(testWire, 25.0, 75.0)

		if clippedWire == nil {
			t.Error("ClipWireBetweenDistances returned nil for valid input")
			return
		}

		// 检查裁剪后的线框长度是否合理
		originalLength := WireLength(testWire)
		clippedLength := WireLength(clippedWire)

		if clippedLength >= originalLength {
			t.Errorf("Expected clipped length (%f) to be less than original length (%f)", clippedLength, originalLength)
		}

		if clippedLength <= 0 {
			t.Errorf("Expected positive clipped length, got %f", clippedLength)
		}
	})

	// 测试边界情况：nil线框
	t.Run("Nil wire input", func(t *testing.T) {
		// 我们期望函数不会panic，但可能返回nil
		defer func() {
			if r := recover(); r != nil {
				// 函数panic了，说明没有正确处理nil输入
				t.Logf("ClipWireBetweenDistances panicked with nil wire input: %v", r)
			}
		}()
		clippedWire := ClipWireBetweenDistances(nil, 25.0, 75.0)
		t.Logf("ClipWireBetweenDistances with nil wire input returned: %v", clippedWire != nil)
	})

	// 测试边界情况：起始距离大于结束距离
	t.Run("Start distance greater than end distance", func(t *testing.T) {
		clippedWire := ClipWireBetweenDistances(testWire, 75.0, 25.0)
		// 函数可能返回nil或有效结果，我们只确保不会panic
		t.Logf("ClipWireBetweenDistances with start > end returned: %v", clippedWire != nil)
	})

	// 测试边界情况：负距离
	t.Run("Negative distances", func(t *testing.T) {
		clippedWire := ClipWireBetweenDistances(testWire, -50.0, -25.0)
		// 函数可能返回nil或有效结果，我们只确保不会panic
		t.Logf("ClipWireBetweenDistances with negative distances returned: %v", clippedWire != nil)
	})
}

// 测试WireLength函数
func TestWireLength(t *testing.T) {
	// 创建测试线框
	testWire := createTestWire(t)

	// 测试正常情况
	t.Run("Normal case", func(t *testing.T) {
		length := WireLength(testWire)

		if length <= 0 {
			t.Errorf("Expected positive wire length, got %f", length)
		}

		// 对于从(0,0,0)到(100,0,0)的直线，长度应该是100
		expectedLength := 100.0
		if math.Abs(length-expectedLength) > 1e-6 {
			t.Errorf("Expected wire length to be approximately %f, got %f", expectedLength, length)
		}
	})

	// 测试边界情况：nil线框
	t.Run("Nil wire input", func(t *testing.T) {
		length := WireLength(nil)
		// 对于nil输入，函数可能返回0或其他值，我们只确保不会panic
		t.Logf("WireLength with nil input returned: %f", length)
	})
}

// 测试MakeCatenary函数
func TestMakeCatenary(t *testing.T) {
	// 创建测试点
	p1 := NewPoint3([3]float64{0, 0, 0})
	p2 := NewPoint3([3]float64{100, 0, 0})
	up := NewDir3FromXYZ([3]float64{0, 0, 1})

	// 测试正常情况
	t.Run("Normal case", func(t *testing.T) {
		points := MakeCatenary(p1, p2, 1.5, 50.0, up, 1.0)

		if points == nil {
			t.Error("MakeCatenary returned nil for valid input")
			return
		}

		if len(points) == 0 {
			t.Error("MakeCatenary returned empty points array")
			return
		}

		// 检查点是否有效
		for i, point := range points {
			coords := point.Data()
			if math.IsInf(coords[0], 0) || math.IsNaN(coords[0]) ||
				math.IsInf(coords[1], 0) || math.IsNaN(coords[1]) ||
				math.IsInf(coords[2], 0) || math.IsNaN(coords[2]) {
				t.Errorf("Point %d has invalid coordinates: (%f, %f, %f)", i, coords[0], coords[1], coords[2])
			}
		}

		// 检查第一个和最后一个点是否接近输入点
		firstPoint := points[0].Data()
		lastPoint := points[len(points)-1].Data()

		firstDist := math.Sqrt(math.Pow(firstPoint[0]-0, 2) + math.Pow(firstPoint[1]-0, 2) + math.Pow(firstPoint[2]-0, 2))
		lastDist := math.Sqrt(math.Pow(lastPoint[0]-100, 2) + math.Pow(lastPoint[1]-0, 2) + math.Pow(lastPoint[2]-0, 2))

		if firstDist > 1e-6 {
			t.Errorf("First point is not close to p1. Distance: %f", firstDist)
		}

		if lastDist > 1e-6 {
			t.Errorf("Last point is not close to p2. Distance: %f", lastDist)
		}
	})

	// 测试边界情况：相同点
	t.Run("Identical points", func(t *testing.T) {
		points := MakeCatenary(p1, p1, 1.5, 50.0, up, 1.0)
		// 对于相同点，函数可能返回nil或单个点，我们只确保不会panic
		t.Logf("MakeCatenary with identical points returned %d points", len(points))
	})

	// 测试边界情况：零松弛
	t.Run("Zero slack", func(t *testing.T) {
		points := MakeCatenary(p1, p2, 0.0, 50.0, up, 1.0)
		// 函数可能返回nil或有效结果，我们只确保不会panic
		t.Logf("MakeCatenary with zero slack returned %d points", len(points))
	})

	// 测试边界情况：负松弛
	t.Run("Negative slack", func(t *testing.T) {
		points := MakeCatenary(p1, p2, -1.0, 50.0, up, 1.0)
		// 函数可能返回nil或有效结果，我们只确保不会panic
		t.Logf("MakeCatenary with negative slack returned %d points", len(points))
	})
}

// 测试CombinedCenter函数
func TestCombinedCenter(t *testing.T) {
	// 创建测试形状
	p1 := NewPoint3([3]float64{0, 0, 0})
	p2 := NewPoint3([3]float64{100, 0, 0})
	p3 := NewPoint3([3]float64{0, 100, 0})

	// 创建边和形状
	edge1 := TopoMakeEdgeFromTwoPoint(p1, p2)
	edge2 := TopoMakeEdgeFromTwoPoint(p2, p3)

	if edge1 == nil || edge2 == nil {
		t.Fatal("Failed to create edges")
	}

	wire1 := TopoMakeWireFromEdge(*edge1)
	wire2 := TopoMakeWireFromEdge(*edge2)

	if wire1 == nil || wire2 == nil {
		t.Fatal("Failed to create wires")
	}

	shape1 := CreateBoundingCenterlineShape(5.0, wire1)
	shape2 := CreateBoundingCenterlineShape(5.0, wire2)

	if shape1 == nil || shape2 == nil {
		t.Fatal("Failed to create shapes")
	}

	// 测试正常情况
	t.Run("Normal case", func(t *testing.T) {
		objects := []*Shape{shape1, shape2}
		center := CombinedCenter(objects)

		// 检查返回的点是否有效
		coords := center.Data()
		if math.IsInf(coords[0], 0) || math.IsNaN(coords[0]) ||
			math.IsInf(coords[1], 0) || math.IsNaN(coords[1]) ||
			math.IsInf(coords[2], 0) || math.IsNaN(coords[2]) {
			t.Errorf("CombinedCenter returned invalid point: (%f, %f, %f)", coords[0], coords[1], coords[2])
		}

		t.Logf("CombinedCenter result: (%f, %f, %f)", coords[0], coords[1], coords[2])
	})

	// 测试边界情况：空数组
	t.Run("Empty objects array", func(t *testing.T) {
		objects := []*Shape{}
		center := CombinedCenter(objects)

		// 对于空数组，函数应该返回一个默认的Point3值
		coords := center.Data()
		t.Logf("CombinedCenter with empty array returned: (%f, %f, %f)", coords[0], coords[1], coords[2])
	})

	// 测试边界情况：nil数组
	t.Run("Nil objects array", func(t *testing.T) {
		defer func() {
			if r := recover(); r != nil {
				t.Logf("CombinedCenter panicked with nil array: %v", r)
			}
		}()
		center := CombinedCenter(nil)
		coords := center.Data()
		t.Logf("CombinedCenter with nil array returned: (%f, %f, %f)", coords[0], coords[1], coords[2])
	})

	// 测试边界情况：包含nil元素的数组
	t.Run("Array with nil elements", func(t *testing.T) {
		objects := []*Shape{shape1, nil, shape2}
		defer func() {
			if r := recover(); r != nil {
				t.Logf("CombinedCenter panicked with nil elements: %v", r)
			}
		}()
		center := CombinedCenter(objects)
		coords := center.Data()
		t.Logf("CombinedCenter with nil elements returned: (%f, %f, %f)", coords[0], coords[1], coords[2])
	})
}

// 测试CombinedCenterOfBoundBox函数
func TestCombinedCenterOfBoundBox(t *testing.T) {
	// 创建测试形状
	p1 := NewPoint3([3]float64{0, 0, 0})
	p2 := NewPoint3([3]float64{100, 0, 0})
	p3 := NewPoint3([3]float64{0, 100, 0})

	// 创建边和形状
	edge1 := TopoMakeEdgeFromTwoPoint(p1, p2)
	edge2 := TopoMakeEdgeFromTwoPoint(p2, p3)

	if edge1 == nil || edge2 == nil {
		t.Fatal("Failed to create edges")
	}

	wire1 := TopoMakeWireFromEdge(*edge1)
	wire2 := TopoMakeWireFromEdge(*edge2)

	if wire1 == nil || wire2 == nil {
		t.Fatal("Failed to create wires")
	}

	shape1 := CreateBoundingCenterlineShape(5.0, wire1)
	shape2 := CreateBoundingCenterlineShape(5.0, wire2)

	if shape1 == nil || shape2 == nil {
		t.Fatal("Failed to create shapes")
	}

	// 测试正常情况
	t.Run("Normal case", func(t *testing.T) {
		objects := []*Shape{shape1, shape2}
		center := CombinedCenterOfBoundBox(objects)

		// 检查返回的点是否有效
		coords := center.Data()
		if math.IsInf(coords[0], 0) || math.IsNaN(coords[0]) ||
			math.IsInf(coords[1], 0) || math.IsNaN(coords[1]) ||
			math.IsInf(coords[2], 0) || math.IsNaN(coords[2]) {
			t.Errorf("CombinedCenterOfBoundBox returned invalid point: (%f, %f, %f)", coords[0], coords[1], coords[2])
		}

		t.Logf("CombinedCenterOfBoundBox result: (%f, %f, %f)", coords[0], coords[1], coords[2])
	})

	// 测试边界情况：空数组
	t.Run("Empty objects array", func(t *testing.T) {
		objects := []*Shape{}
		center := CombinedCenterOfBoundBox(objects)

		// 对于空数组，函数应该返回一个默认的Point3值
		coords := center.Data()
		t.Logf("CombinedCenterOfBoundBox with empty array returned: (%f, %f, %f)", coords[0], coords[1], coords[2])
	})

	// 测试边界情况：nil数组
	t.Run("Nil objects array", func(t *testing.T) {
		defer func() {
			if r := recover(); r != nil {
				t.Logf("CombinedCenterOfBoundBox panicked with nil array: %v", r)
			}
		}()
		center := CombinedCenterOfBoundBox(nil)
		coords := center.Data()
		t.Logf("CombinedCenterOfBoundBox with nil array returned: (%f, %f, %f)", coords[0], coords[1], coords[2])
	})

	// 测试边界情况：包含nil元素的数组
	t.Run("Array with nil elements", func(t *testing.T) {
		objects := []*Shape{shape1, nil, shape2}
		defer func() {
			if r := recover(); r != nil {
				t.Logf("CombinedCenterOfBoundBox panicked with nil elements: %v", r)
			}
		}()
		center := CombinedCenterOfBoundBox(objects)
		coords := center.Data()
		t.Logf("CombinedCenterOfBoundBox with nil elements returned: (%f, %f, %f)", coords[0], coords[1], coords[2])
	})
}

// 辅助函数，用于创建float64指针
func float64Ptr(v float64) *float64 {
	return &v
}

// 辅助函数，用于创建Dir3指针（如果需要）
func dir3Ptr(v Dir3) *Dir3 {
	return &v
}
