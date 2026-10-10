package topo

import "testing"

// TestCgoProfilePointerArrays 回归: 传给 C 的"元素指针数组"曾用
// unsafe.Sizeof(前置声明的不完整 struct) 计算定长, 而 cgo 对不完整类型
// 生成 0 字节占位类型 (runtime/cgo.Incomplete), 导致 malloc(0) 后仍按
// 8 字节/元素写入。≥3 个元素即越过 malloc(0) 最小块的可用空间。
// 用 `go test -asan -run TestCgoProfilePointerArrays` 可直接检出越界写;
// 普通运行退化为冒烟测试。
func TestCgoProfilePointerArrays(t *testing.T) {
	profilePts := []Point3{
		NewPoint3([3]float64{-2, 0, 0}),
		NewPoint3([3]float64{2, 0, 0}),
		NewPoint3([3]float64{2, 0, 5}),
		NewPoint3([3]float64{-2, 0, 5}),
	}
	profileEdges := make([]Edge, 4)
	for i := 0; i < 4; i++ {
		e := TopoMakeEdgeFromTwoPoint(profilePts[i], profilePts[(i+1)%4])
		profileEdges[i] = *e
	}
	profileShape := TopoMakeWireFromEdges(profileEdges).ToShape()
	if profileShape == nil {
		t.Fatal("nil profile shape")
	}

	profiles := make([]Shape, 8)
	for i := range profiles {
		profiles[i] = *profileShape
	}

	p1 := NewPoint3([3]float64{0, 0, 0})
	p2 := NewPoint3([3]float64{0, 0, 20})
	pathWire := TopoMakeWireFromEdge(*TopoMakeEdgeFromTwoPoint(p1, p2))

	t.Run("shell_sweep", func(t *testing.T) {
		sh := TopoMakeShellFromCylinder(5, 20)
		if _, err := sh.Sweep(pathWire, profiles, 0); err != nil {
			t.Logf("Sweep error (geometry may be rejected, allocation path still exercised): %v", err)
		}
	})

	t.Run("solid_sweep", func(t *testing.T) {
		solid := TopoMakeSolidFromBox(10, 10, 10)
		solid.Sweep(pathWire, profiles, 0)
	})

	t.Run("solid_loft", func(t *testing.T) {
		solid := TopoMakeSolidFromBox(10, 10, 10)
		solid.Loft(profiles, false, 1e-6)
	})

	t.Run("plate_constraints", func(t *testing.T) {
		ppc := make([]PinpointConstraint, 8)
		for i := range ppc {
			c, err := NewPinpointConstraint(NewXY([2]float64{float64(i), 0}), NewXYZ([3]float64{1, 0, 0}), 1, 1)
			if err != nil {
				t.Fatalf("NewPinpointConstraint: %v", err)
			}
			ppc[i] = *c
		}
		if _, err := NewSampledCurveConstraint(ppc); err != nil {
			t.Logf("NewSampledCurveConstraint error: %v", err)
		}
		if _, err := NewLinearXYZConstraintDim1(ppc, make([]float64, 8)); err != nil {
			t.Logf("NewLinearXYZConstraintDim1 error: %v", err)
		}
	})
}
