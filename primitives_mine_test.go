package topo

// 矿山专业图元测试 (minebim P 线): 表驱动创建 + 网格非空 + 值域拒绝。
// 运行: CC=/usr/bin/clang CXX=/usr/bin/clang++ go test -run TestMine -v .

import (
	"math"
	"testing"
)

func meshTriangles(t *testing.T, s *Shape) int {
	t.Helper()
	if s == nil {
		return 0
	}
	m := NewMeshReceiver()
	s.Mesh(m, 0.1, 0.1, 0.5)
	n := 0
	for _, tris := range m.Tris {
		n += len(tris)
	}
	return n
}

func TestMineShaft(t *testing.T) {
	cases := []struct {
		name   string
		params MineShaftParams
	}{
		{"圆形立井", MineShaftParams{Shape: MineShaftCircle, InnerRadius: 3.0, OuterRadius: 3.5, Depth: 300}},
		{"矩形立井", MineShaftParams{Shape: MineShaftRect, InnerLength: 4, InnerWidth: 3, OuterLength: 5, OuterWidth: 4, Depth: 250}},
	}
	for _, c := range cases {
		s := CreateMineShaft(c.params)
		if n := meshTriangles(t, s); n == 0 {
			t.Errorf("%s: empty mesh", c.name)
		} else {
			t.Logf("%s tris=%d", c.name, n)
		}
		// 井口放置
		s2 := CreateMineShaftAt(c.params, NewPoint3([3]float64{1000, 2000, 1200}))
		if n := meshTriangles(t, s2); n == 0 {
			t.Errorf("%s: at-place empty mesh", c.name)
		}
	}
	// 值域拒绝
	if s := CreateMineShaft(MineShaftParams{Shape: MineShaftCircle, InnerRadius: 3.5, OuterRadius: 3.0, Depth: 100}); s != nil {
		t.Errorf("outer<=inner 应拒绝")
	}
	if s := CreateMineShaft(MineShaftParams{Shape: 7, Depth: 100}); s != nil {
		t.Errorf("非法枚举应拒绝")
	}
}

func TestMineOrepass(t *testing.T) {
	p := MineOrepassParams{
		Center: NewPoint3([3]float64{0, 0, 0}),
		Stations: []MineOrepassStation{
			{Depth: 0, Radius: 2.5},
			{Depth: 20, Radius: 2.5},
			{Depth: 35, Radius: 1.5}, // 变径位置
			{Depth: 60, Radius: 1.5},
		},
	}
	s := CreateMineOrepass(p)
	if n := meshTriangles(t, s); n == 0 {
		t.Errorf("orepass empty mesh")
	} else {
		t.Logf("orepass tris=%d", n)
	}
	// 站位深度回退应拒绝
	bad := MineOrepassParams{Center: p.Center, Stations: []MineOrepassStation{{Depth: 10, Radius: 2}, {Depth: 5, Radius: 2}}}
	if s := CreateMineOrepass(bad); s != nil {
		t.Errorf("深度回退应拒绝")
	}
}

func TestMineFaultLens(t *testing.T) {
	p := MineFaultLensParams{
		Center:     NewPoint3([3]float64{500, 800, -150}),
		Strike:     NewDir3FromXYZ([3]float64{1, 0, 0}),
		DipAzimuth: NewDir3FromXYZ([3]float64{0, 1, 0}),
		DipAngle:   30,
		ZoneWidth:  8,
		ZoneLength: 400,
		TopElev:    -100,
		BottomElev: -400,
	}
	s := CreateMineFaultLens(p)
	if n := meshTriangles(t, s); n == 0 {
		t.Errorf("fault lens empty mesh")
	} else {
		t.Logf("fault lens tris=%d", n)
	}
	// 倾角越界拒绝
	p.DipAngle = 95
	if s := CreateMineFaultLens(p); s != nil {
		t.Errorf("dip>=90 应拒绝")
	}
}

func TestMineLining(t *testing.T) {
	// 半圆拱断面 (直墙 + 半圆顶, 对齐 minebim SectionLoop arch)
	w, h := 4.6, 3.6
	hw := w / 2
	wall := h - hw
	arch := [][2]float64{{-hw, 0}, {-hw, wall}}
	for i := 1; i <= 10; i++ {
		a := math.Pi - float64(i)/10*math.Pi
		arch = append(arch, [2]float64{hw * math.Cos(a), wall + hw*math.Sin(a)})
	}
	arch = append(arch, [2]float64{hw, 0})
	pts := make([]Point3, 0, len(arch))
	for _, q := range arch {
		pts = append(pts, NewPoint3([3]float64{q[0], q[1], 0}))
	}
	s := CreateMineLining(MineLiningParams{Points: pts, Thickness: 0.12, Length: 20, Dir: NewDir3FromXYZ([3]float64{0, 0, 1})})
	if n := meshTriangles(t, s); n == 0 {
		t.Errorf("lining empty mesh")
	} else {
		t.Logf("lining tris=%d", n)
	}
	if s := CreateMineLining(MineLiningParams{Points: pts[:2], Thickness: 0.1, Length: 5, Dir: NewDir3FromXYZ([3]float64{0, 0, 1})}); s != nil {
		t.Errorf("点数<3 应拒绝")
	}
}

func TestMineFullCatalog(t *testing.T) {
	p3 := NewPoint3
	d3 := NewDir3FromXYZ
	path := []Point3{p3([3]float64{0, 0, 0}), p3([3]float64{200, 0, -5}), p3([3]float64{200, 120, -5})}
	bound := []Point3{p3([3]float64{0, 0, 0}), p3([3]float64{40, 0, 0}), p3([3]float64{40, 12, 0}), p3([3]float64{0, 12, 0})}
	cases := []struct {
		name  string
		shape *Shape
	}{
		{"roadway", CreateMineRoadway(MineRoadwayParams{Section: MineSectionArch, Width: 4.6, Height: 3.6, Path: path})},
		{"roadway-arcarch", CreateMineRoadway(MineRoadwayParams{Section: MineSectionArcArch, Width: 4.6, Height: 3.8, Path: path[:2]})},
		{"roadway-ellipse", CreateMineRoadway(MineRoadwayParams{Section: MineSectionEllipse, Width: 4.2, Height: 3.8, Path: path[:2]})},
		{"chamber", CreateMineChamber(MineChamberParams{Center: p3([3]float64{50, 50, 0}), Length: 8, Width: 5, Height: 4})},
		{"workingface", CreateMineWorkingface(MineWorkingfaceParams{Origin: p3([3]float64{0, 0, 0}), Dir: d3([3]float64{1, 0, 0}), FaceLength: 200, Advance: 60, SeamThickness: 3.2})},
		{"heading", CreateMineHeading(MineHeadingParams{Center: p3([3]float64{200, 0, -5}), Dir: d3([3]float64{1, 0, 0}), Section: MineSectionArch, Width: 4.6, Height: 3.6})},
		{"area-body", CreateMineAreaBody(MineAreaBodyParams{Boundary: bound, BaseZ: -350, Height: 3})},
		{"bolt-row", CreateMineBoltRow(MineBoltRowParams{Origin: p3([3]float64{0, 0, 0}), Axis: d3([3]float64{1, 0, 0}), Section: MineSectionArch, Width: 4.6, Height: 3.6, RowCount: 2, PerRow: 4, Spacing: 1.2, BoltLen: 2.2, Diameter: 0.022})},
		{"usteel-row", CreateMineUsteelRow(MineUsteelRowParams{Origin: p3([3]float64{0, 0, 0}), Axis: d3([3]float64{1, 0, 0}), Section: MineSectionArch, Width: 4.6, Height: 3.6, Thickness: 0.12, Spacing: 0.8, Count: 3})},
		{"shield-row", CreateMineShieldRow(MineShieldRowParams{Origin: p3([3]float64{0, 0, 0}), Dir: d3([3]float64{0, 1, 0}), Count: 10, CenterDist: 1.75, BeamWidth: 1.8, BeamThick: 0.3, Height: 3.2, MaxLegPairs: 24})},
		{"vent-wall", CreateMineVentWall(MineVentWallParams{Section: MineSectionArch, Width: 4.6, Height: 3.6, Thickness: 0.5, Center: p3([3]float64{100, 0, -5}), Axis: d3([3]float64{1, 0, 0})})},
		{"box-wall", CreateMineBoxWall(MineBoxWallParams{Width: 4.6, Height: 3.6, Thickness: 0.8, Center: p3([3]float64{150, 0, -5}), Axis: d3([3]float64{1, 0, 0})})},
		{"vent-door-closed", CreateMineVentDoor(MineVentDoorParams{Width: 4.6, Height: 3.6, DoorWidth: 2, DoorHeight: 2.2, DoorThick: 0.08, FrameWidth: 0.3, Center: p3([3]float64{50, 0, -5}), Axis: d3([3]float64{1, 0, 0})})},
		{"vent-door-open", CreateMineVentDoor(MineVentDoorParams{Width: 4.6, Height: 3.6, DoorWidth: 2, DoorHeight: 2.2, DoorThick: 0.08, FrameWidth: 0.3, OpenAngleDeg: 80, Center: p3([3]float64{50, 0, -5}), Axis: d3([3]float64{1, 0, 0})})},
		{"vent-window", CreateMineVentWindow(MineVentWindowParams{Width: 4.6, Height: 3.2, Thickness: 0.5, WinWidth: 1.2, WinHeight: 0.8, WinSill: 1.2, Bars: 4, Center: p3([3]float64{60, 0, -5}), Axis: d3([3]float64{1, 0, 0})})},
		{"vent-bridge", CreateMineVentBridge(MineVentBridgeParams{Span: 4, Width: 3.4, Thickness: 0.4, Apex: 3.2, Center: p3([3]float64{0, 0, -5}), Axis: d3([3]float64{1, 0, 0})})},
		{"vent-duct", CreateMineVentDuct(MineVentDuctParams{Path: []Point3{p3([3]float64{0, 0, 2.6}), p3([3]float64{120, 0, 2.6})}, Diameter: 0.8})},
		{"collapse-pillar", CreateMineCollapsePillar(MineCollapsePillarParams{BottomCenter: p3([3]float64{300, 300, -460}), BottomLong: 24, BottomShort: 15.6, TopLong: 40, TopShort: 26, Height: 150})},
		{"water-gate-wall", CreateMineWaterGateWall(MineWaterGateWallParams{Width: 4.2, Height: 3.4, Thickness: 1.2, DoorWidth: 0.8, DoorHeight: 1.8, Center: p3([3]float64{0, 700, -350}), Axis: d3([3]float64{1, 0, 0})})},
		{"water-gate", CreateMineWaterGate(MineWaterGateParams{Width: 4.2, Height: 3.4, DoorWidth: 1.6, DoorHeight: 2, DoorThick: 0.15, FrameWidth: 0.35, Center: p3([3]float64{0, 750, -350}), Axis: d3([3]float64{1, 0, 0})})},
		{"borehole-layered", CreateMineBorehole(MineBoreholeParams{Collar: p3([3]float64{100, 900, 1240}), Axis: d3([3]float64{0.25, 0.25, -0.94}), Diameter: 0.13, Layers: []MineBoreholeLayer{{From: 0, To: 200}, {From: 200, To: 350}, {From: 350, To: 500}}})},
		{"rail-track", CreateMineRailTrack(MineRailTrackParams{Path: path, Gauge: 0.9, SleeperSpacing: 0.7, SleeperMax: 300})},
		{"rail-track-double", CreateMineRailTrack(MineRailTrackParams{Path: path[:2], Gauge: 0.6, DoubleTrack: true, CenterDistance: 2.3, SleeperSpacing: 0, SleeperMax: 0})},
		{"turnout", CreateMineTurnout(MineTurnoutParams{Origin: p3([3]float64{50, 0, 0}), Axis: d3([3]float64{1, 0, 0}), Gauge: 0.9, FrogNo: 9, Length: 30})},
		{"belt", CreateMineBelt(MineBeltParams{Path: []Point3{p3([3]float64{0, 0, -350}), p3([3]float64{400, 0, -350})}, BeltWidth: 1.2, FrameHeight: 0.9})},
		{"scraper", CreateMineScraper(MineScraperParams{Path: []Point3{p3([3]float64{0, 0, -350}), p3([3]float64{180, 0, -350})}, PanWidth: 0.76, PanHeight: 0.19})},
		{"monorail", CreateMineMonorail(MineMonorailParams{Path: []Point3{p3([3]float64{0, 0, -347}), p3([3]float64{150, 0, -347})}, RailHeight: 0.155, FlangeWidth: 0.068})},
		{"pipe-run", CreateMinePipeRun(MinePipeRunParams{Path: []Point3{p3([3]float64{0, 0, 0.3}), p3([3]float64{300, 0, 0.3})}, Diameter: 0.15, BracketSpacing: 3})},
		{"cable-run", CreateMineCableRun(MineCableRunParams{Path: []Point3{p3([3]float64{0, 0, 2.2}), p3([3]float64{300, 0, 2.2})}, Diameter: 0.05, Lines: 3})},
	}
	for _, c := range cases {
		n := meshTriangles(t, c.shape)
		if n == 0 {
			t.Errorf("%s: empty mesh", c.name)
			continue
		}
		t.Logf("%-18s tris=%d", c.name, n)
	}
}

func TestMineRejects(t *testing.T) {
	d3 := NewDir3FromXYZ
	if s := CreateMineRoadway(MineRoadwayParams{Section: MineSection(9), Width: 4, Height: 3, Path: []Point3{NewPoint3([3]float64{0, 0, 0}), NewPoint3([3]float64{1, 0, 0})}}); s != nil {
		t.Errorf("非法断面枚举应拒绝")
	}
	if s := CreateMineVentDoor(MineVentDoorParams{Width: 2, Height: 3, DoorWidth: 3, DoorHeight: 2.2, DoorThick: 0.1, FrameWidth: 0.3, Center: NewPoint3([3]float64{0, 0, 0}), Axis: d3([3]float64{1, 0, 0})}); s != nil {
		t.Errorf("门洞大于断面应拒绝")
	}
	if s := CreateMineTurnout(MineTurnoutParams{Origin: NewPoint3([3]float64{0, 0, 0}), Axis: d3([3]float64{1, 0, 0}), Gauge: 0.9, FrogNo: 99, Length: 30}); s != nil {
		t.Errorf("辙叉号越界应拒绝")
	}
	if s := CreateMineRailTrack(MineRailTrackParams{Path: []Point3{NewPoint3([3]float64{0, 0, 0}), NewPoint3([3]float64{1, 0, 0})}, Gauge: 0.6, DoubleTrack: true, CenterDistance: 0.5, SleeperMax: 0}); s != nil {
		t.Errorf("双轨中心距小于轨距应拒绝")
	}
}

func TestMineGapFive(t *testing.T) {
	p3 := NewPoint3
	d3 := NewDir3FromXYZ
	cases := []struct {
		name  string
		shape *Shape
	}{
		{"trench", CreateMineTrench(MineTrenchParams{Path: []Point3{p3([3]float64{0, 0, 0}), p3([3]float64{100, 0, 0})},
			Section: MineSectionTrap, Width: 0.5, Height: 0.4, SideOffset: 1.6})},
		{"trench-rect", CreateMineTrench(MineTrenchParams{Path: []Point3{p3([3]float64{0, 0, 0}), p3([3]float64{60, 0, 0})},
			Section: MineSectionRect, Width: 0.4, Height: 0.35, SideOffset: -1.5})},
		{"junction", CreateMineJunction(MineJunctionParams{Center: p3([3]float64{100, 100, 0}),
			MainAxis: d3([3]float64{1, 0, 0}), BranchAngleDeg: 45, Section: MineSectionArch,
			Width: 4.2, Height: 3.4, MainLength: 60, BranchLength: 40, ReinforceLength: 0.6})},
		{"vent-station", CreateMineVentStation(MineVentStationParams{Section: MineSectionRect, Width: 4.2,
			Height: 3.2, PostWidth: 0.2, Depth: 0.15, Center: p3([3]float64{50, 0, 0}), Axis: d3([3]float64{1, 0, 0})})},
		{"steel-band", CreateMineSteelBand(MineSteelBandParams{Length: 3.0, Width: 0.28, Thickness: 0.003,
			HoleCount: 5, HoleDia: 0.043, HoleEdge: 0.15})},
		{"pipe-fitting", CreateMinePipeFitting(MinePipeFittingParams{Center: p3([3]float64{200, 0, 2.4}),
			MainAxis: d3([3]float64{1, 0, 0}), BranchAngleDeg: 90, MainLength: 4, BranchLength: 2.4, Diameter: 0.15})},
	}
	for _, c := range cases {
		n := meshTriangles(t, c.shape)
		if n == 0 {
			t.Errorf("%s: empty mesh", c.name)
			continue
		}
		t.Logf("%-14s tris=%d", c.name, n)
	}
	// 拒绝: 量纲/枚举/几何越界
	if s := CreateMineJunction(MineJunctionParams{Center: p3([3]float64{0, 0, 0}), MainAxis: d3([3]float64{1, 0, 0}),
		BranchAngleDeg: 200, Section: MineSectionRect, Width: 4, Height: 3, MainLength: 40, BranchLength: 30}); s != nil {
		t.Errorf("交岔角越界应拒绝")
	}
	if s := CreateMineSteelBand(MineSteelBandParams{Length: 1, Width: 0.2, Thickness: 0.003,
		HoleCount: 3, HoleDia: 0.04, HoleEdge: 0.6}); s != nil {
		t.Errorf("孔位超带长应拒绝")
	}
	if s := CreateMineTrench(MineTrenchParams{Path: []Point3{p3([3]float64{0, 0, 0})},
		Section: MineSectionRect, Width: 0.4, Height: 0.3}); s != nil {
		t.Errorf("水沟单点路径应拒绝")
	}
}

// TestMineAllDeterminism 全图元重放确定性: 每个参数化图元构建两次,
// 三角数与顶点面组数恒等 (对账可复现性, 同输入同输出)。
func TestMineAllDeterminism(t *testing.T) {
	p3 := NewPoint3
	d3 := NewDir3FromXYZ
	path := []Point3{p3([3]float64{0, 0, 0}), p3([3]float64{200, 0, -5}), p3([3]float64{200, 120, -5})}
	straight := []Point3{p3([3]float64{0, 0, 0}), p3([3]float64{120, 0, 0})}
	bound := []Point3{p3([3]float64{0, 0, 0}), p3([3]float64{40, 0, 0}), p3([3]float64{40, 12, 0}), p3([3]float64{0, 12, 0})}
	builds := map[string]func() *Shape{
		"shaft": func() *Shape {
			return CreateMineShaft(MineShaftParams{Shape: MineShaftCircle, InnerRadius: 3, OuterRadius: 3.5, Depth: 60})
		},
		"orepass": func() *Shape {
			return CreateMineOrepass(MineOrepassParams{Center: p3([3]float64{0, 0, 0}), Stations: []MineOrepassStation{{Depth: 0, Radius: 2.5}, {Depth: 30, Radius: 1.6}}})
		},
		"fault-lens": func() *Shape {
			return CreateMineFaultLens(MineFaultLensParams{Center: p3([3]float64{0, 0, 0}), Strike: d3([3]float64{1, 0, 0}), DipAzimuth: d3([3]float64{0, 1, 0}), DipAngle: 30, ZoneWidth: 8, ZoneLength: 120, TopElev: 50, BottomElev: -150})
		},
		"lining": func() *Shape {
			return CreateMineLining(MineLiningParams{Points: []Point3{p3([3]float64{-2.3, 0, 0}), p3([3]float64{-2.3, 1, 0}), p3([3]float64{0, 3.3, 0}), p3([3]float64{2.3, 1, 0}), p3([3]float64{2.3, 0, 0})}, Thickness: 0.12, Length: 20, Dir: d3([3]float64{0, 0, 1})})
		},
		"roadway": func() *Shape {
			return CreateMineRoadway(MineRoadwayParams{Section: MineSectionArch, Width: 4.6, Height: 3.6, Path: path})
		},
		"chamber": func() *Shape {
			return CreateMineChamber(MineChamberParams{Center: p3([3]float64{50, 50, 0}), Length: 8, Width: 5, Height: 4})
		},
		"workingface": func() *Shape {
			return CreateMineWorkingface(MineWorkingfaceParams{Origin: p3([3]float64{0, 0, 0}), Dir: d3([3]float64{1, 0, 0}), FaceLength: 200, Advance: 60, SeamThickness: 3.2})
		},
		"heading": func() *Shape {
			return CreateMineHeading(MineHeadingParams{Center: p3([3]float64{200, 0, -5}), Dir: d3([3]float64{1, 0, 0}), Section: MineSectionArch, Width: 4.6, Height: 3.6})
		},
		"area-body": func() *Shape { return CreateMineAreaBody(MineAreaBodyParams{Boundary: bound, BaseZ: -350, Height: 3}) },
		"bolt-row": func() *Shape {
			return CreateMineBoltRow(MineBoltRowParams{Origin: p3([3]float64{0, 0, 0}), Axis: d3([3]float64{1, 0, 0}), Section: MineSectionArch, Width: 4.6, Height: 3.6, RowCount: 2, PerRow: 4, Spacing: 1.2, BoltLen: 2.2, Diameter: 0.022})
		},
		"usteel-row": func() *Shape {
			return CreateMineUsteelRow(MineUsteelRowParams{Origin: p3([3]float64{0, 0, 0}), Axis: d3([3]float64{1, 0, 0}), Section: MineSectionArch, Width: 4.6, Height: 3.6, Thickness: 0.12, Spacing: 0.8, Count: 3})
		},
		"shield-row": func() *Shape {
			return CreateMineShieldRow(MineShieldRowParams{Origin: p3([3]float64{0, 0, 0}), Dir: d3([3]float64{0, 1, 0}), Count: 10, CenterDist: 1.75, BeamWidth: 1.8, BeamThick: 0.3, Height: 3.2, MaxLegPairs: 24})
		},
		"shotcrete": func() *Shape {
			return CreateMineShotcrete(MineShotcreteParams{Origin: p3([3]float64{0, 0, 0}), Axis: d3([3]float64{1, 0, 0}), Section: MineSectionArch, Width: 4.6, Height: 3.6, Thickness: 0.12, Length: 30})
		},
		"vent-wall": func() *Shape {
			return CreateMineVentWall(MineVentWallParams{Section: MineSectionArch, Width: 4.6, Height: 3.6, Thickness: 0.5, Center: p3([3]float64{100, 0, -5}), Axis: d3([3]float64{1, 0, 0})})
		},
		"box-wall": func() *Shape {
			return CreateMineBoxWall(MineBoxWallParams{Width: 4.6, Height: 3.6, Thickness: 0.8, Center: p3([3]float64{150, 0, -5}), Axis: d3([3]float64{1, 0, 0})})
		},
		"vent-door": func() *Shape {
			return CreateMineVentDoor(MineVentDoorParams{Width: 4.6, Height: 3.6, DoorWidth: 2, DoorHeight: 2.2, DoorThick: 0.08, FrameWidth: 0.3, OpenAngleDeg: 80, Center: p3([3]float64{50, 0, -5}), Axis: d3([3]float64{1, 0, 0})})
		},
		"vent-window": func() *Shape {
			return CreateMineVentWindow(MineVentWindowParams{Width: 4.6, Height: 3.2, Thickness: 0.5, WinWidth: 1.2, WinHeight: 0.8, WinSill: 1.2, Bars: 4, Center: p3([3]float64{60, 0, -5}), Axis: d3([3]float64{1, 0, 0})})
		},
		"vent-bridge": func() *Shape {
			return CreateMineVentBridge(MineVentBridgeParams{Span: 4, Width: 3.4, Thickness: 0.4, Apex: 3.2, Center: p3([3]float64{0, 0, -5}), Axis: d3([3]float64{1, 0, 0})})
		},
		"vent-duct": func() *Shape {
			return CreateMineVentDuct(MineVentDuctParams{Path: []Point3{p3([3]float64{0, 0, 2.6}), p3([3]float64{120, 0, 2.6})}, Diameter: 0.8})
		},
		"vent-station": func() *Shape {
			return CreateMineVentStation(MineVentStationParams{Section: MineSectionRect, Width: 4.2, Height: 3.2, PostWidth: 0.2, Depth: 0.15, Center: p3([3]float64{50, 0, 0}), Axis: d3([3]float64{1, 0, 0})})
		},
		"collapse-pillar": func() *Shape {
			return CreateMineCollapsePillar(MineCollapsePillarParams{BottomCenter: p3([3]float64{300, 300, -460}), BottomLong: 24, BottomShort: 15.6, TopLong: 40, TopShort: 26, Height: 150})
		},
		"water-gate-wall": func() *Shape {
			return CreateMineWaterGateWall(MineWaterGateWallParams{Width: 4.2, Height: 3.4, Thickness: 1.2, DoorWidth: 0.8, DoorHeight: 1.8, Center: p3([3]float64{0, 700, -350}), Axis: d3([3]float64{1, 0, 0})})
		},
		"water-gate": func() *Shape {
			return CreateMineWaterGate(MineWaterGateParams{Width: 4.2, Height: 3.4, DoorWidth: 1.6, DoorHeight: 2, DoorThick: 0.15, FrameWidth: 0.35, Center: p3([3]float64{0, 750, -350}), Axis: d3([3]float64{1, 0, 0})})
		},
		"borehole": func() *Shape {
			return CreateMineBorehole(MineBoreholeParams{Collar: p3([3]float64{100, 900, 1240}), Axis: d3([3]float64{0.25, 0.25, -0.94}), Diameter: 0.13, Layers: []MineBoreholeLayer{{From: 0, To: 200}, {From: 200, To: 350}, {From: 350, To: 500}}})
		},
		"rail-track": func() *Shape {
			return CreateMineRailTrack(MineRailTrackParams{Path: path, Gauge: 0.9, SleeperSpacing: 0.7, SleeperMax: 300})
		},
		"turnout": func() *Shape {
			return CreateMineTurnout(MineTurnoutParams{Origin: p3([3]float64{50, 0, 0}), Axis: d3([3]float64{1, 0, 0}), Gauge: 0.9, FrogNo: 9, Length: 30})
		},
		"belt": func() *Shape {
			return CreateMineBelt(MineBeltParams{Path: []Point3{p3([3]float64{0, 0, -350}), p3([3]float64{400, 0, -350})}, BeltWidth: 1.2, FrameHeight: 0.9})
		},
		"scraper": func() *Shape {
			return CreateMineScraper(MineScraperParams{Path: []Point3{p3([3]float64{0, 0, -350}), p3([3]float64{180, 0, -350})}, PanWidth: 0.76, PanHeight: 0.19})
		},
		"monorail": func() *Shape {
			return CreateMineMonorail(MineMonorailParams{Path: straight, RailHeight: 0.155, FlangeWidth: 0.068})
		},
		"pipe-run": func() *Shape {
			return CreateMinePipeRun(MinePipeRunParams{Path: []Point3{p3([3]float64{0, 0, 0.3}), p3([3]float64{120, 0, 0.3})}, Diameter: 0.15, BracketSpacing: 3})
		},
		"cable-run": func() *Shape {
			return CreateMineCableRun(MineCableRunParams{Path: []Point3{p3([3]float64{0, 0, 2.2}), p3([3]float64{120, 0, 2.2})}, Diameter: 0.05, Lines: 3})
		},
		"trench": func() *Shape {
			return CreateMineTrench(MineTrenchParams{Path: straight, Section: MineSectionTrap, Width: 0.5, Height: 0.4, SideOffset: 1.6})
		},
		"junction": func() *Shape {
			return CreateMineJunction(MineJunctionParams{Center: p3([3]float64{100, 100, 0}), MainAxis: d3([3]float64{1, 0, 0}), BranchAngleDeg: 45, Section: MineSectionArch, Width: 4.2, Height: 3.4, MainLength: 60, BranchLength: 40, ReinforceLength: 0.6})
		},
		"steel-band": func() *Shape {
			return CreateMineSteelBand(MineSteelBandParams{Length: 3, Width: 0.28, Thickness: 0.003, HoleCount: 5, HoleDia: 0.043, HoleEdge: 0.15})
		},
		"pipe-fitting": func() *Shape {
			return CreateMinePipeFitting(MinePipeFittingParams{Center: p3([3]float64{200, 0, 2.4}), MainAxis: d3([3]float64{1, 0, 0}), BranchAngleDeg: 90, MainLength: 4, BranchLength: 2.4, Diameter: 0.15})
		},
		"fence": func() *Shape {
			return CreateMineFence(MineFenceParams{Width: 4.2, Height: 2.0, PostWidth: 0.15, BarWidth: 0.08, Thickness: 0.05, Bars: 12, Center: p3([3]float64{0, 0, 0}), Axis: d3([3]float64{1, 0, 0})})
		},
	}
	if len(builds) != 36 {
		t.Fatalf("确定性矩阵应覆盖 36 图元, 实际 %d", len(builds))
	}
	for name, build := range builds {
		s1, s2 := build(), build()
		if s1 == nil || s2 == nil {
			t.Errorf("%s: build nil (s1=%v s2=%v)", name, s1 == nil, s2 == nil)
			continue
		}
		m1, m2 := meshTriangles(t, s1), meshTriangles(t, s2)
		if m1 == 0 {
			t.Errorf("%s: empty mesh", name)
			continue
		}
		if m1 != m2 {
			t.Errorf("%s: 重放不确定 (%d vs %d)", name, m1, m2)
		}
	}
}
