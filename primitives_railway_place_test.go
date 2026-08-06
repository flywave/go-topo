package topo

import (
	"math"
	"testing"
)

// 定位索 WithPlace: params 纯参数, 两点外置
func TestPositioningCableWithPlace(t *testing.T) {
	top := NewPoint3([3]float64{0, 0, 6000})
	bottom := NewPoint3([3]float64{1000, 0, 0})
	s := CreatePositioningCableWithPlace(PositioningCableParams{Diameter: 10}, top, bottom)
	if s == nil || s.IsNull() {
		t.Fatal("nil positioning cable")
	}
	bb := s.BBox().Data()
	if bb[2] > 0 || bb[5] < 6000 {
		t.Fatalf("bbox does not cover endpoints: %v", bb)
	}
}

// 直线轨道 WithPlace (小尺寸)
func TestStraightTrackWithPlace(t *testing.T) {
	params := StraightTrackParams{
		Gauge: 1435, RailHeight: 176, RailHeadWidth: 73, RailBaseWidth: 150,
		SleeperLength: 2500, SleeperWidth: 240, SleeperHeight: 180, SleeperSpacing: 1000,
		BallastTopWidth: 3400, BallastThickness: 300, BallastSlope: 1.5,
	}
	start := NewPoint3([3]float64{0, 0, 0})
	end := NewPoint3([3]float64{5000, 0, 0})
	s := CreateStraightTrackWithPlace(params, start, end)
	if s == nil || s.IsNull() {
		t.Fatal("nil straight track")
	}
	bb := s.BBox().Data()
	if bb[0] > 0 || bb[3] < 5000 {
		t.Fatalf("bbox does not cover endpoints: %v", bb)
	}
}

// 曲线轨道 WithPlace (小角度)
func TestCurveTrackWithPlace(t *testing.T) {
	params := CurveTrackParams{
		StartAngle: 0, SweepAngle: math.Pi / 6, CurveRadius: 10000,
		Gauge: 1435, RailHeight: 176, RailHeadWidth: 73, RailBaseWidth: 150,
		SleeperLength: 2500, SleeperWidth: 240, SleeperHeight: 180, SleeperSpacing: 1000,
		BallastTopWidth: 3400, BallastThickness: 300, BallastSlope: 1.5,
	}
	center := NewPoint3([3]float64{0, 0, 0})
	s := CreateCurveTrackWithPlace(params, center)
	if s == nil || s.IsNull() {
		t.Fatal("nil curve track")
	}
	bb := s.BBox().Data()
	// 30° 扇形, 半径 10000±gauge/2: bbox 应覆盖起始点 (10000,0) 与终点 (8660,5000) 附近
	if bb[0] > 8660 || bb[3] < 10000 || bb[4] < 5000 {
		t.Fatalf("bbox does not cover expected arc extents: %v", bb)
	}
}

// TRAPEZOIDAL 轨枕 (ShapeType=2) 应放置在 startPoint→endPoint 位置而非原点
// (经 create_sleeper 的对称端点 + with_place 路径验证放置语义)
func TestSleeperTrapezoidalPlacement(t *testing.T) {
	params := SleeperParams{
		ShapeType: 2, Length: 2500, Width: 260, Height: 200,
		Gauge: 1435, RailBaseWidth: 150, GrooveDepth: 10,
	}
	pos := NewPoint3([3]float64{10000, 20000, 500})
	s := CreateSleeperWithPlace(params, pos,
		NewDir3FromXYZ([3]float64{1, 0, 0}), NewDir3FromXYZ([3]float64{0, 0, 1}))
	if s == nil || s.IsNull() {
		t.Fatal("nil trapezoidal sleeper")
	}
	bb := s.BBox().Data()
	// 轨枕沿 X 长 2500, 中心应在 pos 附近 (而非原点)
	cx, cy := (bb[0]+bb[3])/2, (bb[1]+bb[4])/2
	if math.Abs(cx-10000) > 100 || math.Abs(cy-20000) > 100 {
		t.Fatalf("trapezoidal sleeper not placed at position: %v", bb)
	}
	if dx := bb[3] - bb[0]; dx < 2400 || dx > 2600 {
		t.Fatalf("trapezoidal sleeper length wrong: %v", bb)
	}
	if bb[2] < 400 { // 底面应在 pos.Z 附近, 不在原点
		t.Fatalf("trapezoidal sleeper z misplaced: %v", bb)
	}
}

// 棘轮补偿装置 WithPlace: wheelAxis 应决定轮轴方向 (Y 轴与 X 轴 bbox 应明显不同)
func TestRatchetCompensatorWheelAxis(t *testing.T) {
	center := NewPoint3([3]float64{0, 0, 5000})
	sy := CreateRatchetCompensatorAt(RatchetCompensatorParams{}, center,
		NewDir3FromXYZ([3]float64{0, 1, 0}))
	sx := CreateRatchetCompensatorAt(RatchetCompensatorParams{}, center,
		NewDir3FromXYZ([3]float64{1, 0, 0}))
	if sy == nil || sx == nil || sy.IsNull() || sx.IsNull() {
		t.Fatal("nil ratchet compensator")
	}
	by, bx := sy.BBox().Data(), sx.BBox().Data()
	// 轮轴切换后横向尺寸应随之互换 (轮盘+支架侧宽 420, 坠砣串侧 380)
	extXY := func(b [6]float64) (float64, float64) { return b[3] - b[0], b[4] - b[1] }
	yx, yy := extXY(by)
	xx, xy := extXY(bx)
	if !(yx > yy+20 && xy > xx+20) {
		t.Fatalf("wheelAxis not respected: axis=Y bbox=%v axis=X bbox=%v", by, bx)
	}
}

// 下锚金具原点约定: 连接点在原点 — ROD_AND_RING 环心在原点 (bbox 含负 X),
// 杆体沿 +X 伸展至 ~length
func TestAnchorFittingOrigin(t *testing.T) {
	s := CreateAnchorFitting(AnchorFittingParams{Type: 1, Length: 800, Diameter: 24})
	if s == nil || s.IsNull() {
		t.Fatal("nil anchor fitting")
	}
	bb := s.BBox().Data()
	if bb[0] > -5 || bb[0] < -100 {
		t.Fatalf("ring should be centered at origin: %v", bb)
	}
	if bb[3] < 700 {
		t.Fatalf("rod should extend along +X to ~length: %v", bb)
	}
}

// 道床沿曲线中心线放样: 1/4 圆弧折线输入, bbox 应包络曲线范围
// (旧实现只按 X 包围盒单向拉伸, y 到不了弧形区域)
func TestBallastCurvedPath(t *testing.T) {
	R := 20000.0
	var cl []Point3
	for i := 0; i <= 12; i++ {
		a := math.Pi / 2 * float64(i) / 12
		cl = append(cl, NewPoint3([3]float64{R * math.Cos(a), R * math.Sin(a), 0}))
	}
	s := CreateBallastAlongPath(cl, 3400, 300, 1.5)
	if s == nil || s.IsNull() {
		t.Fatal("nil curved ballast")
	}
	bb := s.BBox().Data()
	// 曲线两端 (20000,0) / (0,20000), 道床横向外扩后 x/y 均应超过 15000
	if bb[3] < 15000 || bb[4] < 15000 {
		t.Fatalf("ballast bbox does not follow the curve: %v", bb)
	}
	// 顶面与中心线齐平(z=0), 底面 = -thickness
	if math.Abs(bb[5]) > 5 || math.Abs(bb[2]+300) > 5 {
		t.Fatalf("ballast z range wrong: %v", bb)
	}
}

// 超高倾角生效: 相同曲线轨道, 有/无超高的 bbox z 范围应不同;
// 且 curve_track 现含道床 (bbox z 下探到道床底 -thickness)
func TestCurveTrackBallastAndTilt(t *testing.T) {
	base := CurveTrackParams{
		StartAngle: 0, SweepAngle: math.Pi / 6, CurveRadius: 10000,
		Gauge: 1435, RailHeight: 176, RailHeadWidth: 73, RailBaseWidth: 150,
		SleeperLength: 2500, SleeperWidth: 240, SleeperHeight: 180, SleeperSpacing: 1000,
		BallastTopWidth: 3400, BallastThickness: 300, BallastSlope: 1.5,
	}
	flat := CreateCurveTrack(base)
	if flat == nil || flat.IsNull() {
		t.Fatal("nil curve track")
	}
	bf := flat.BBox().Data()
	// 无道床时最低点是轨枕底 (~-180), 含道床应下探到 ~-300
	if bf[2] > -250 {
		t.Fatalf("curve track has no ballast (min z = %v): %v", bf[2], bf)
	}
	sup := base
	sup.SuperElevation = 150
	tilted := CreateCurveTrack(sup)
	if tilted == nil || tilted.IsNull() {
		t.Fatal("nil superelevated curve track")
	}
	bt := tilted.BBox().Data()
	// 倾角 atan(150/1435)≈0.104, 半底宽 2150 → z 范围变化约 ±220
	if math.Abs(bt[2]-bf[2]) < 50 && math.Abs(bt[5]-bf[5]) < 50 {
		t.Fatalf("superElevation tilt has no effect: flat=%v tilted=%v", bf, bt)
	}
}

// 线岔交角参数化: 不同交角应产生不同布局 (bbox 不同)
func TestCrossingAngleParametric(t *testing.T) {
	p := CrossingParams{LimitPipeLength: 1200, PipeDiameter: 24, WireDiameter: 12}
	cross := NewPoint3([3]float64{0, 0, 5600})
	main := NewDir3FromXYZ([3]float64{1, 0, 0})
	b30 := NewDir3FromXYZ([3]float64{math.Cos(math.Pi / 6), math.Sin(math.Pi / 6), 0})
	b90 := NewDir3FromXYZ([3]float64{0, 1, 0})
	s30 := CreateCrossingWithPlace(p, cross, main, b30)
	s90 := CreateCrossingWithPlace(p, cross, main, b90)
	if s30 == nil || s90 == nil || s30.IsNull() || s90.IsNull() {
		t.Fatal("nil crossing")
	}
	bb30, bb90 := s30.BBox().Data(), s90.BBox().Data()
	diff := false
	for i := 0; i < 6; i++ {
		if math.Abs(bb30[i]-bb90[i]) > 50 {
			diff = true
		}
	}
	if !diff {
		t.Fatalf("crossing layout ignores branch angle: 30deg=%v 90deg=%v", bb30, bb90)
	}
}

// 格构式钢柱 (角钢主肢) 应生成非空几何, 高度与参数一致
func TestSteelMastLattice(t *testing.T) {
	s := CreateSteelMast(SteelMastParams{
		Type: 1, Height: 8000, BottomWidth: 800, TopWidth: 500, WallThickness: 8,
	})
	if s == nil || s.IsNull() {
		t.Fatal("nil lattice mast")
	}
	bb := s.BBox().Data()
	if bb[5] < 7900 {
		t.Fatalf("lattice mast height wrong: %v", bb)
	}
	if bb[3]-bb[0] < 700 || bb[4]-bb[1] < 700 {
		t.Fatalf("lattice mast footprint wrong: %v", bb)
	}
}
