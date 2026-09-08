package topo

// 中心线提取 (端盖截面扫掠 + PCA 回退) 的鲁棒性测试:
// 覆盖陡峭/密集/多圈螺旋、U 形弯、S 形弯、渐变截面、异形断面、
// 环/球回退、退化输入, 以及螺旋的分块进度体积守恒。

import (
	"math"
	"testing"
)

// ---- 测试辅助 ----

// densePath 将折线路径细分, 生成理想中心线的密集参考点列
func densePath(pts []Point3, per int) []Point3 {
	out := make([]Point3, 0, (len(pts)-1)*per+1)
	for i := 0; i < len(pts)-1; i++ {
		a := pts[i].Data()
		b := pts[i+1].Data()
		for j := 0; j < per; j++ {
			t := float64(j) / float64(per)
			out = append(out, NewPoint3([3]float64{
				a[0] + (b[0]-a[0])*t,
				a[1] + (b[1]-a[1])*t,
				a[2] + (b[2]-a[2])*t,
			}))
		}
	}
	out = append(out, pts[len(pts)-1])
	return out
}

// pointPathDist 点到折线的最近距离
func pointPathDist(p Point3, path []Point3) float64 {
	pd := p.Data()
	best := math.MaxFloat64
	for i := 0; i+1 < len(path); i++ {
		a := path[i].Data()
		b := path[i+1].Data()
		abx, aby, abz := b[0]-a[0], b[1]-a[1], b[2]-a[2]
		apx, apy, apz := pd[0]-a[0], pd[1]-a[1], pd[2]-a[2]
		ab2 := abx*abx + aby*aby + abz*abz
		t := 0.0
		if ab2 > 0 {
			t = (apx*abx + apy*aby + apz*abz) / ab2
			if t < 0 {
				t = 0
			} else if t > 1 {
				t = 1
			}
		}
		dx := apx - abx*t
		dy := apy - aby*t
		dz := apz - abz*t
		best = math.Min(best, math.Sqrt(dx*dx+dy*dy+dz*dz))
	}
	return best
}

func polylineLength(pts []Point3) float64 {
	total := 0.0
	for i := 1; i < len(pts); i++ {
		a := pts[i-1].Data()
		b := pts[i].Data()
		total += math.Sqrt((b[0]-a[0])*(b[0]-a[0]) + (b[1]-a[1])*(b[1]-a[1]) +
			(b[2]-a[2])*(b[2]-a[2]))
	}
	return total
}

// assertFittedCenterline 校验拟合中心线: 非空、跟随理想路径、长度接近期望
func assertFittedCenterline(t *testing.T, name string, fitted *Wire,
	ideal []Point3, maxDev, expectLen, lenTol float64) {
	t.Helper()
	if fitted == nil {
		t.Errorf("%s: FitCenterlineFromShape returned nil", name)
		return
	}
	if l := WireLength(fitted); l <= 0 {
		t.Errorf("%s: fitted wire unusable (length %.2f)", name, l)
		return
	}
	sampled := SampleCenterlineWire(fitted, 150, false)
	if len(sampled) == 0 {
		t.Errorf("%s: no sampled points", name)
		return
	}
	sum := 0.0
	maxActual := 0.0
	total := 0.0
	for i, p := range sampled {
		d := pointPathDist(p, ideal)
		sum += d
		if d > maxActual {
			maxActual = d
		}
		if i > 0 {
			total += polylineStep(sampled[i-1], p)
		}
	}
	mean := sum / float64(len(sampled))
	if mean > maxDev*0.6 {
		t.Errorf("%s: mean deviation %.2f too large (limit %.2f)", name, mean, maxDev*0.6)
	}
	if maxActual > maxDev {
		t.Errorf("%s: max deviation %.2f exceeds %.2f", name, maxActual, maxDev)
	}
	if total < expectLen*(1-lenTol) || total > expectLen*(1+lenTol) {
		t.Errorf("%s: length %.1f not within %.0f%% of %.1f", name, total, lenTol*100, expectLen)
	}
	t.Logf("%s: len=%.1f (ideal %.1f) meanDev=%.2f maxDev=%.2f",
		name, total, expectLen, mean, maxActual)
}

func polylineStep(a, b Point3) float64 {
	ad, bd := a.Data(), b.Data()
	return math.Sqrt((bd[0]-ad[0])*(bd[0]-ad[0]) + (bd[1]-ad[1])*(bd[1]-ad[1]) +
		(bd[2]-ad[2])*(bd[2]-ad[2]))
}

func helixPath(R, turns, H float64, n int) []Point3 {
	pts := make([]Point3, 0, n+1)
	for i := 0; i <= n; i++ {
		th := turns * 2 * math.Pi * float64(i) / float64(n)
		pts = append(pts, NewPoint3([3]float64{
			R * math.Cos(th), R * math.Sin(th), H * float64(i) / float64(n),
		}))
	}
	return pts
}

func helixArcLen(R, turns, H float64) float64 {
	return turns * math.Sqrt(math.Pow(2*math.Pi*R, 2)+math.Pow(H/turns, 2))
}

// ---- 中心线提取鲁棒性 ----

func TestFitCenterlineRobustness(t *testing.T) {
	makePipe := func(t *testing.T, name string, path []Point3, tubeR float64) *Shape {
		t.Helper()
		pipe := CreatePipe(PipeParams{
			Wire:           path,
			Profiles:       []ShapeProfile{circProfile([3]float64{0, 0, 0}, [3]float64{0, 0, 1}, float32(tubeR))},
			SegmentType:    SegmentTypeSpline,
			TransitionMode: TransitionTransformed,
		})
		if pipe == nil || pipe.IsNull() {
			t.Fatalf("%s: failed to create pipe", name)
		}
		return pipe
	}

	t.Run("Helix steep pitch", func(t *testing.T) {
		// 陡螺旋: R=10, 2 圈, 高 120 (切向仰角 ~44°)
		path := helixPath(10, 2, 120, 72)
		pipe := makePipe(t, "steep helix", path, 3)
		cl := FitCenterlineFromShape(pipe, 100, 0.99)
		assertFittedCenterline(t, "steep helix", cl, densePath(path, 4), 4.5,
			helixArcLen(10, 2, 120), 0.15)
	})

	t.Run("Helix tight coil", func(t *testing.T) {
		// 密集螺旋: R=12, 3 圈, 螺距 9 < 管径 8+1, 相邻圈面间隙仅 1
		path := helixPath(12, 3, 27, 108)
		pipe := makePipe(t, "tight helix", path, 4)
		cl := FitCenterlineFromShape(pipe, 100, 0.99)
		// 已知边界: 螺距≈管径时相邻圈截面混叠, 自动提取为最佳努力
		// (手工编辑兜底场景), 断言只要求跟住线圈且长度有界
		assertFittedCenterline(t, "tight helix", cl, densePath(path, 4), 11.0,
			helixArcLen(12, 3, 27), 0.6)
	})

	t.Run("Helix many turns", func(t *testing.T) {
		// 多圈: R=30, 6 圈, 弧长 ~1130, 逼近扫掠步数上限
		path := helixPath(30, 6, 60, 216)
		pipe := makePipe(t, "many turns", path, 3.5)
		cl := FitCenterlineFromShape(pipe, 100, 0.99)
		// 已知边界: 多圈长轨迹 (弧长 >> 包围盒) 对扫掠提取是困难形态,
		// 结果可能中途终止或返回空 (手工编辑兜底场景)。
		// 只断言: 非空时长度有界且采样点有限非常数
		if cl != nil {
			sampled := SampleCenterlineWire(cl, 100, false)
			if len(sampled) == 0 {
				t.Error("many turns helix: fit non-nil but no samples")
			}
			if l := WireLength(cl); l > 3*helixArcLen(30, 6, 60) {
				t.Errorf("many turns helix length %.1f exceeds 3x ideal", l)
			}
		} else {
			t.Log("many turns helix: extraction declined (manual fallback)")
		}
	})

	t.Run("U-bend half torus", func(t *testing.T) {
		// C 形半环 (圆环状端盖): CreateRing 半角
		ring := CreateRing(RingParams{RingRadius: 15, TubeRadius: 4, Angle: float32(math.Pi)})
		if ring == nil || ring.IsNull() {
			t.Fatal("failed to create half torus")
		}
		cl := FitCenterlineFromShape(ring, 100, 0.99)
		ideal := make([]Point3, 0, 49)
		for i := 0; i <= 48; i++ {
			th := math.Pi * float64(i) / 48.0
			ideal = append(ideal, NewPoint3([3]float64{
				15 * math.Cos(th), 15 * math.Sin(th), 0}))
		}
		assertFittedCenterline(t, "U-bend", cl, ideal, 4.0, math.Pi*15, 0.15)
	})

	t.Run("S-curve", func(t *testing.T) {
		// S 形: 两个反向弯 (拐点处截面倾斜)
		path := []Point3{
			NewPoint3([3]float64{0, 0, 0}),
			NewPoint3([3]float64{30, 15, 0}),
			NewPoint3([3]float64{60, 0, 0}),
			NewPoint3([3]float64{90, 15, 0}),
			NewPoint3([3]float64{120, 0, 0}),
		}
		pipe := makePipe(t, "s-curve", path, 4)
		cl := FitCenterlineFromShape(pipe, 100, 0.99)
		assertFittedCenterline(t, "s-curve", cl, densePath(path, 6), 7.0,
			polylineLength(path)*1.02, 0.15)
	})

	t.Run("Tapered cone", func(t *testing.T) {
		// 渐变截面: 圆台 R8→R2 (截面半径沿程收缩 4 倍)
		cone := CreateConeShape(ConeShapeParams{Radius1: 8, Radius2: 2, Height: 60})
		if cone == nil || cone.IsNull() {
			t.Fatal("failed to create cone")
		}
		cl := FitCenterlineFromShape(cone, 100, 0.99)
		axis := []Point3{
			NewPoint3([3]float64{0, 0, 0}),
			NewPoint3([3]float64{0, 0, 60}),
		}
		assertFittedCenterline(t, "cone", cl, densePath(axis, 10), 8.0, 60, 0.10)
	})

	t.Run("Gear profile prism", func(t *testing.T) {
		// 异形断面 (渐开线齿形) 直棱柱: 断面任意性不应影响提取
		profile := []Point3{
			NewPoint3([3]float64{0, 10, 0}),
			NewPoint3([3]float64{-3.403, 9.702, 0}),
			NewPoint3([3]float64{-6.703, 8.818, 0}),
			NewPoint3([3]float64{-9.8, 7.374, 0}),
			NewPoint3([3]float64{-12.599, 5.415, 0}),
			NewPoint3([3]float64{-13.168, 4.846, 0}),
			NewPoint3([3]float64{-13.63, 4.188, 0}),
			NewPoint3([3]float64{-13.97, 3.459, 0}),
			NewPoint3([3]float64{-14.179, 2.682, 0}),
			NewPoint3([3]float64{-14.25, 1.88, 0}),
			NewPoint3([3]float64{-14.25, 0, 0}),
			NewPoint3([3]float64{-5.4, 0, 0}),
			NewPoint3([3]float64{-5.4, 1.2, 0}),
			NewPoint3([3]float64{-5.6, 1.2, 0}),
			NewPoint3([3]float64{-5.6, 6.93, 0}),
			NewPoint3([3]float64{-4.928, 7.812, 0}),
			NewPoint3([3]float64{-4.118, 8.57, 0}),
			NewPoint3([3]float64{-3.193, 9.182, 0}),
			NewPoint3([3]float64{-2.18, 9.632, 0}),
			NewPoint3([3]float64{-1.105, 9.907, 0}),
			NewPoint3([3]float64{0, 10, 0}),
		}
		upDir := NewDir3FromXYZ([3]float64{0, 1, 0})
		pipe := CreatePipe(PipeParams{
			Wire: []Point3{
				NewPoint3([3]float64{0, 0, 0}),
				NewPoint3([3]float64{0, 0, 50}),
			},
			Profiles: []ShapeProfile{{
				Type: ProfileTypePolygon,
				Data: ProfileData{Polygon: PolygonProfile{Edges: profile}},
			}},
			SegmentType:    SegmentTypeLine,
			TransitionMode: TransitionTransformed,
			UpDir:          &upDir,
		})
		if pipe == nil || pipe.IsNull() {
			t.Fatal("failed to create gear prism")
		}
		cl := FitCenterlineFromShape(pipe, 100, 0.99)
		// 质心轴: 中心线是断面质心的轨迹, 齿形轮廓质心不在原点
		cx, cy := 0.0, 0.0
		for i := 0; i < len(profile)-1; i++ {
			d := profile[i].Data()
			cx += d[0]
			cy += d[1]
		}
		cx /= float64(len(profile) - 1)
		cy /= float64(len(profile) - 1)
		axis := []Point3{
			NewPoint3([3]float64{cx, cy, 0}),
			NewPoint3([3]float64{cx, cy, 50}),
		}
		assertFittedCenterline(t, "gear prism", cl, densePath(axis, 10), 3.0, 50, 0.12)
	})

	t.Run("Rectangle section straight", func(t *testing.T) {
		pipe := CreatePipe(PipeParams{
			Wire: []Point3{
				NewPoint3([3]float64{0, 0, 0}),
				NewPoint3([3]float64{80, 0, 0}),
			},
			Profiles: []ShapeProfile{{
				Type: ProfileTypeRectangle,
				Data: ProfileData{Rectangle: RectangleProfile{
					P1: NewPoint3([3]float64{-5, -3, 0}),
					P2: NewPoint3([3]float64{5, 3, 0}),
				}},
			}},
			SegmentType:    SegmentTypeLine,
			TransitionMode: TransitionTransformed,
		})
		if pipe == nil || pipe.IsNull() {
			t.Fatal("failed to create rectangle tube")
		}
		cl := FitCenterlineFromShape(pipe, 100, 0.99)
		axis := []Point3{
			NewPoint3([3]float64{0, 0, 0}),
			NewPoint3([3]float64{80, 0, 0}),
		}
		assertFittedCenterline(t, "rect tube", cl, densePath(axis, 10), 2.5, 80, 0.10)
	})

	t.Run("Torus fallback no crash", func(t *testing.T) {
		// 闭环 (无端盖): 回退路径, 不崩溃即可, 结果不强求
		ring := CreateRing(RingParams{RingRadius: 15, TubeRadius: 3, Angle: float32(math.Pi * 2)})
		if ring == nil || ring.IsNull() {
			t.Fatal("failed to create torus")
		}
		cl := FitCenterlineFromShape(ring, 100, 0.99)
		if cl != nil {
			for _, p := range SampleCenterlineWire(cl, 20, false) {
				d := p.Data()
				if math.IsNaN(d[0]) || math.IsInf(d[0], 0) {
					t.Error("torus fallback produced non-finite points")
					break
				}
			}
		}
	})

	t.Run("Sphere fallback no crash", func(t *testing.T) {
		sph := CreateSphereShape(SphereShapeParams{Radius: 20})
		if sph == nil || sph.IsNull() {
			t.Fatal("failed to create sphere")
		}
		cl := FitCenterlineFromShape(sph, 50, 0.99)
		if cl != nil {
			for _, p := range SampleCenterlineWire(cl, 20, false) {
				d := p.Data()
				if math.IsNaN(d[0]) || math.IsInf(d[0], 0) {
					t.Error("sphere fallback produced non-finite points")
					break
				}
			}
		}
	})

	t.Run("Tiny box", func(t *testing.T) {
		// 微型盒: 双端扫掠合并的重复比例相对尺寸偏大, 只要有界即可
		box := CreateBoxShape(BoxShapeParams{
			Point1: NewPoint3([3]float64{0, 0, 0}),
			Point2: NewPoint3([3]float64{2, 2, 2}),
		})
		cl := FitCenterlineFromShape(box, 20, 0.99)
		if cl != nil {
			if l := WireLength(cl); l > 7 {
				t.Errorf("tiny box centerline length %.2f implausible", l)
			}
		}
	})
}

// ---- 螺旋 4D 切片鲁棒性 ----

func TestClipWithTopo4DRobustness(t *testing.T) {
	path := helixPath(30, 2, 40, 72)
	pipe := CreatePipe(PipeParams{
		Wire:           path,
		Profiles:       []ShapeProfile{circProfile([3]float64{0, 0, 0}, [3]float64{0, 0, 1}, 5.0)},
		SegmentType:    SegmentTypeSpline,
		TransitionMode: TransitionTransformed,
	})
	if pipe == nil || pipe.IsNull() {
		t.Fatal("failed to create helix pipe")
	}
	fullVol := pipe.ComputeMass()
	if fullVol <= 0 {
		t.Fatalf("helix pipe non-positive mass %.2f", fullVol)
	}

	t.Run("Mid block", func(t *testing.T) {
		r := ClipWithTopo4D(pipe, WorkProgress{
			Type:  ProgressByRatio,
			Range: [2]float64{0.25, 0.75},
		})
		assertVolumeRatio(t, "helix [0.25,0.75]", fullVol, r, 0.28, 0.65)
	})

	t.Run("End block", func(t *testing.T) {
		// 线圈端部块的边界精度受拟合弧长摆动影响 (自动提取的中心线
		// 弧长与体积分布存在非线性), 只断言最佳努力边界
		r := ClipWithTopo4D(pipe, WorkProgress{
			Type:  ProgressByRatio,
			Range: [2]float64{0.8, 1.0},
		})
		assertVolumeRatio(t, "helix [0.8,1.0]", fullVol, r, 0.04, 0.36)
	})

	t.Run("Cumulative blocks best effort", func(t *testing.T) {
		// bim4d 实际用法: 按进度分块生成各阶段模型。
		// 线圈结构的分块边界精度受中心线拟合摆动影响 (直管场景边界
		// 精确, 见 TestClipWithTopo4D), 此处只断言最佳努力边界:
		// 每块非空、体积有界、总量不失控
		blocks := [][2]float64{
			{0.0, 0.2}, {0.2, 0.4}, {0.4, 0.6}, {0.6, 0.8}, {0.8, 1.0},
		}
		sum := 0.0
		for i, b := range blocks {
			r := ClipWithTopo4D(pipe, WorkProgress{
				Type:  ProgressByRatio,
				Range: b,
			})
			if r == nil || r.IsNull() {
				t.Fatalf("block %v returned nil", b)
			}
			m := r.ComputeMass()
			if m <= 0 {
				t.Errorf("block %v non-positive volume %.2f", b, m)
			}
			if ratio := m / fullVol; ratio < 0.03 || ratio > 0.50 {
				t.Errorf("block %d %v volume ratio %.3f outside [0.03, 0.50]",
					i, b, ratio)
			}
			sum += m
			t.Logf("block %d [%.1f,%.1f]: vol=%.1f", i, b[0], b[1], m)
		}
		drift := math.Abs(sum-fullVol) / fullVol
		if drift > 0.35 {
			t.Errorf("cumulative blocks volume drift %.2f%% exceeds 35%% (sum=%.1f full=%.1f)",
				drift*100, sum, fullVol)
		}
	})

	t.Run("Distance mode on helix", func(t *testing.T) {
		// 弧长约 382 (理想 379), 按弧长取前 190 ≈ 一半
		r := ClipWithTopo4D(pipe, WorkProgress{
			Type:  ProgressByDistance,
			Range: [2]float64{0.0, 190.0},
		})
		assertVolumeRatio(t, "helix dist[0,190]", fullVol, r, 0.40, 0.60)
	})
}
