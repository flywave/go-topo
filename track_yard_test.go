package topo

import (
	"fmt"
	"math"
	"reflect"
	"sort"
	"strings"
	"testing"
)

// 站场测试数据: 正线 (0,0)→(400,0) 在 x=100m 处接出一条侧线 (R=350m 左偏)
func buildYardGeoJSON() []byte {
	line := func(x0, y0, x1, y1, step float64) string {
		var pts []string
		n := int((x1-x0)/step + 0.5)
		for i := 0; i <= n; i++ {
			pts = append(pts, fmt.Sprintf("[%.4f,%.4f,0]", x0+float64(i)*step, y0))
		}
		return strings.Join(pts, ",")
	}
	// 侧线: 从 (100,0) 起, R=350m 向左弯, 弧长 ~80m
	var siding []string
	R := 350.0
	for i := 0; i <= 32; i++ {
		th := float64(i) * 0.0072 // 每步 2.52m 弧长
		siding = append(siding, fmt.Sprintf("[%.4f,%.4f,0]", 100+R*math.Sin(th), R-R*math.Cos(th)))
	}
	feature := func(coords string) string {
		return fmt.Sprintf(`{"type":"Feature","geometry":{"type":"LineString","coordinates":[%s]},"properties":{"gauge":1435,"railType":60}}`, coords)
	}
	return []byte(fmt.Sprintf(`{"type":"FeatureCollection","features":[%s,%s,%s]}`,
		feature(line(0, 0, 100, 0, 5)),
		feature(line(100, 0, 400, 0, 5)),
		feature(strings.Join(siding, ","))))
}

func TestCreateYardTurnout(t *testing.T) {
	as, err := CreateYardFromGeoJSON(buildYardGeoJSON())
	if err != nil {
		t.Fatalf("yard failed: %v", err)
	}
	if as == nil {
		t.Fatal("nil assembly")
	}
	// 层级: 根 yard + 3 track_i 子装配 + 1 turnout; 全树元素 11
	//      (每 track_i 内 rails_i + sleepers_i)
	if n := len(as.GetElements()); n != 11 {
		t.Fatalf("expect 11 elements (root+3 track+6 leaf+turnout), got %d", n)
	}
	var top []string
	for _, ch := range as.Children() {
		top = append(top, ch.GetName())
	}
	sort.Strings(top)
	want := []string{"track_0", "track_1", "track_2", "turnout_0"}
	if !reflect.DeepEqual(top, want) {
		t.Fatalf("top-level children = %v, want %v", top, want)
	}
	// 股道子装配内含钢轨组+轨枕 (叶片不暴露在顶层)
	var track0 *Assembly
	for _, ch := range as.Children() {
		if ch.GetName() == "track_0" {
			track0 = ch
			break
		}
	}
	if track0 == nil {
		t.Fatal("track_0 not found")
	}
	if n := len(track0.GetElements()); n != 3 { // 容器 + rails_0 + sleepers_0
		t.Fatalf("track_0 elements = %d, want 3", n)
	}
	bb := as.ToCompound().BBox().Data()
	dx, dy := bb[3]-bb[0], bb[4]-bb[1]
	t.Logf("yard bbox: %.0f x %.0f mm", dx, dy)
	if dx < 380000 || dx > 420000 {
		t.Fatalf("yard length wrong: %.0f", dx)
	}
	if dy < 4000 || dy > 20000 {
		t.Fatalf("yard width wrong: %.0f", dy)
	}
}

func TestCreateYardCrossing(t *testing.T) {
	// 菱形交叉: 两条独立线路中部相交
	mk := func(coords string) string {
		return fmt.Sprintf(`{"type":"Feature","geometry":{"type":"LineString","coordinates":[%s]},"properties":{"gauge":1435}}`, coords)
	}
	var a, b []string
	for x := 0.0; x <= 400; x += 10 {
		a = append(a, fmt.Sprintf("[%.2f,0,0]", x))
	}
	for y := -20.0; y <= 20; y += 4 {
		b = append(b, fmt.Sprintf("[200,%.2f,0]", y))
	}
	coll := []byte(fmt.Sprintf(`{"type":"FeatureCollection","features":[%s,%s]}`,
		mk(strings.Join(a, ",")), mk(strings.Join(b, ","))))
	as, err := CreateYardFromGeoJSON(coll)
	if err != nil {
		t.Fatalf("crossing yard failed: %v", err)
	}
	// 菱形让位分段: 两股道在交叉点附近断开, 各成 2 段
	// 层级: 根 yard + 4 track_i 子装配 (2 线 × 2 段) + 1 crossing
	//      (每 track_i 内 rails_i + sleepers_i) = 1 + 4*3 + 1 = 14
	if n := len(as.GetElements()); n != 14 {
		t.Fatalf("expect 14 elements (root+4 track*3+crossing), got %d", n)
	}
	var top []string
	for _, ch := range as.Children() {
		top = append(top, ch.GetName())
	}
	sort.Strings(top)
	want := []string{"crossing_0", "track_0", "track_1", "track_2", "track_3"}
	if !reflect.DeepEqual(top, want) {
		t.Fatalf("top-level children = %v, want %v", top, want)
	}
}

// TestYardTurnoutGeometryFit 侧股辙叉几何实测: 导曲线半径拟合 / 辙叉角 / 布岔参数
func TestYardTurnoutGeometryFit(t *testing.T) {
	layout, err := ComputeYardLayout(buildYardGeoJSON())
	if err != nil {
		t.Fatalf("layout failed: %v", err)
	}
	if len(layout.Turnouts) != 1 {
		t.Fatalf("expect 1 turnout, got %d", len(layout.Turnouts))
	}
	tn := layout.Turnouts[0]
	// 侧线 R350m 左偏 → 开向左, 辙叉角 atan(1/N) 附近, N 就近 12
	if !tn.IsLeftHand {
		t.Errorf("expect left-hand turnout, got right")
	}
	if tn.TurnoutNo != 12 {
		t.Errorf("turnoutNo = %d, want 12", tn.TurnoutNo)
	}
	if tn.FrogAngle < 0.06 || tn.FrogAngle > 0.12 {
		t.Errorf("frogAngle = %.4f, want ~0.09 (atan(1/11))", tn.FrogAngle)
	}
	// 导曲线半径实测拟合 ≈ 侧线实际 R350m (查表 12 号也是 350000, 但来源应为一侧 walks)
	if tn.LeadCurveRadius < 280000 || tn.LeadCurveRadius > 450000 {
		t.Errorf("leadCurveRadius = %.0f, want ~350000", tn.LeadCurveRadius)
	}
	// 布岔参数: 岔枕间距/枕高继承股道属性缺省
	if tn.SleeperSpacing != 600 {
		t.Errorf("sleeperSpacing = %.0f, want 600", tn.SleeperSpacing)
	}
	if tn.SleeperHeight != 200 {
		t.Errorf("sleeperHeight = %.0f, want 200", tn.SleeperHeight)
	}
}

// TestYardCrossingRightAngle 直角菱形交叉: 实测交叉角 + 辙叉抬到轨面 + 交叉岔枕
func TestYardCrossingRightAngle(t *testing.T) {
	mk := func(coords string) string {
		return fmt.Sprintf(`{"type":"Feature","geometry":{"type":"LineString","coordinates":[%s]},"properties":{"gauge":1435}}`, coords)
	}
	var a, b []string
	for x := 0.0; x <= 400; x += 10 {
		a = append(a, fmt.Sprintf("[%.2f,0,0]", x))
	}
	for y := -20.0; y <= 20; y += 4 {
		b = append(b, fmt.Sprintf("[200,%.2f,0]", y))
	}
	coll := []byte(fmt.Sprintf(`{"type":"FeatureCollection","features":[%s,%s]}`,
		mk(strings.Join(a, ",")), mk(strings.Join(b, ","))))
	layout, err := ComputeYardLayout(coll)
	if err != nil {
		t.Fatalf("layout failed: %v", err)
	}
	if len(layout.Crossings) != 1 {
		t.Fatalf("expect 1 crossing, got %d", len(layout.Crossings))
	}
	cr := layout.Crossings[0]
	if math.Abs(cr.FrogAngle-math.Pi/2) > 0.01 {
		t.Errorf("frogAngle = %.4f, want ≈ π/2", cr.FrogAngle)
	}
	if cr.SleeperSpacing != 600 || cr.SleeperHeight != 200 {
		t.Errorf("crossing布岔参数缺失: spacing=%.0f height=%.0f", cr.SleeperSpacing, cr.SleeperHeight)
	}
	as, err := CreateYardFromLayout(layout)
	if err != nil {
		t.Fatalf("build failed: %v", err)
	}
	// 股道让位分段: 两条边在交叉点断开 → 4 段
	if len(layout.Tracks) != 4 {
		t.Errorf("expect 4 split tracks, got %d", len(layout.Tracks))
	}
	if layout.Crossings[0].Span <= 0 || layout.Crossings[0].Span > 4000 {
		t.Errorf("crossing span = %.0f, want ~2500 (直角菱形半展长)", layout.Crossings[0].Span)
	}
	// 单独取 crossing_0: 真菱形 z 应抬到轨面 (枕高 200 + 轨高 176 ≈ 376), 直角对称
	var cross *Assembly
	for _, ch := range as.Children() {
		if ch.GetName() == "crossing_0" {
			cross = ch
			break
		}
	}
	if cross == nil {
		t.Fatal("crossing_0 not found")
	}
	bb := cross.ToCompound().BBox().Data()
	dz := bb[5] - bb[2]
	if dz < 300 || dz > 450 {
		t.Errorf("crossing dz = %.0f, want ≈ 376 (菱形轨底需抬到枕顶)", dz)
	}
	dx, dy := bb[3]-bb[0], bb[4]-bb[1]
	if dx < 4000 || dx > 9000 || dy < 4000 || dy > 9000 {
		t.Errorf("crossing footprint %.0f x %.0f, want 直角菱形 ~5.3k x ~5.3k", dx, dy)
	}
}

// TestYardCurvedMainGuard 曲线主向守卫: 主线弯曲超限的道岔节点跳过并告警
func TestYardCurvedMainGuard(t *testing.T) {
	// 主线 R1000m 在节点 (0,0) 处分成两段, 侧线 1:12 直线右偏 (坐标单位: 米)
	R := 1000.0
	arcPt := func(s float64) string {
		return fmt.Sprintf("[%.6f,%.6f,0]", R*math.Sin(s/R), R-R*math.Cos(s/R))
	}
	var mainIn, mainOut []string
	for s := -150.0; s <= 0; s += 5 {
		mainIn = append(mainIn, arcPt(s))
	}
	for s := 0.0; s <= 150; s += 5 {
		mainOut = append(mainOut, arcPt(s))
	}
	var siding []string
	for i := 0; i <= 20; i++ {
		s := float64(i) * 4
		siding = append(siding, fmt.Sprintf("[%.6f,%.6f,0]", s, -s/12.0))
	}
	feature := func(coords string) string {
		return fmt.Sprintf(`{"type":"Feature","geometry":{"type":"LineString","coordinates":[%s]},"properties":{"gauge":1435}}`, coords)
	}
	coll := []byte(fmt.Sprintf(`{"type":"FeatureCollection","features":[%s,%s,%s]}`,
		feature(strings.Join(mainIn, ",")), feature(strings.Join(mainOut, ",")), feature(strings.Join(siding, ","))))
	layout, err := ComputeYardLayout(coll)
	if err != nil {
		t.Fatalf("layout failed: %v", err)
	}
	if len(layout.Turnouts) != 0 {
		t.Errorf("R1000 主线道岔应跳过, got %d turnouts", len(layout.Turnouts))
	}
	if len(layout.Warnings) == 0 {
		t.Errorf("expect skip warnings, got none")
	}
	// 被跳过的边不裁剪 (TrimS=0 且 TrimE=全长)
	for i, tr := range layout.Tracks {
		full := polyArcLens(arraysToPts(tr.Centerline))[len(tr.Centerline)-1]
		if tr.TrimS != 0 || (tr.TrimE != 0 && math.Abs(tr.TrimE-full) > 1) {
			t.Errorf("track %d 应保持全长 (TrimS=%.0f TrimE=%.0f, 全长=%.0f)", i, tr.TrimS, tr.TrimE, full)
		}
	}
	if _, err := CreateYardFromLayout(layout); err != nil {
		t.Fatalf("fallback build failed: %v", err)
	}
}

// TestDiamondCrossingShallow 锐角 (1/12) 真菱形: 有限长度编织区
func TestDiamondCrossingShallow(t *testing.T) {
	ang := math.Atan(1.0 / 12.0)
	dp := DiamondParams{FrogAngle: ang, TurnoutNo: 12, Gauge: 1435,
		RailHeight: 176, RailHeadWidth: 73, RailBaseWidth: 150,
		SleeperSpacing: 600, SleeperHeight: 200}
	shp := CreateDiamondWithPlace(dp, NewPoint3([3]float64{0, 0, 200}),
		NewDir3FromXYZ([3]float64{1, 0, 0}), NewDir3FromXYZ([3]float64{0, 0, 1}))
	if shp == nil || shp.IsNull() {
		t.Fatal("diamond build failed")
	}
	bb := shp.BBox().Data()
	dx, dy, dz := bb[3]-bb[0], bb[4]-bb[1], bb[5]-bb[2]
	// 长对角 ≈ 2·(xa + Lp + 1500), xa ≈ 17.25m → 全长 ~42.8m; 短对角 ≈ 5m
	t.Logf("1/12 diamond: %.0f x %.0f x %.0f", dx, dy, dz)
	if dx < 38000 || dx > 47000 {
		t.Errorf("diamond dx = %.0f, want ~42800 (菱形沿线路展开)", dx)
	}
	if dy < 4000 || dy > 6500 {
		t.Errorf("diamond dy = %.0f, want ~5200", dy)
	}
	if dz < 300 || dz > 450 {
		t.Errorf("diamond dz = %.0f, want ≈ 376", dz)
	}
}

// TestYardLayoutJSONRoundTripNewFields 布局 JSON 往返保留新增字段并确定性重建
func TestYardLayoutJSONRoundTripNewFields(t *testing.T) {
	layout, err := ComputeYardLayout(buildYardGeoJSON())
	if err != nil {
		t.Fatalf("layout failed: %v", err)
	}
	raw, err := layout.ToJSON()
	if err != nil {
		t.Fatalf("marshal: %v", err)
	}
	rt, err := YardLayoutFromJSON(raw)
	if err != nil {
		t.Fatalf("unmarshal: %v", err)
	}
	if len(rt.Turnouts) != 1 {
		t.Fatalf("round-trip turnouts = %d", len(rt.Turnouts))
	}
	a, b := layout.Turnouts[0], rt.Turnouts[0]
	if a.LeadCurveRadius != b.LeadCurveRadius || a.FrogAngle != b.FrogAngle ||
		a.SleeperSpacing != b.SleeperSpacing || a.SleeperHeight != b.SleeperHeight {
		t.Errorf("round-trip 字段不一致: %+v vs %+v", a, b)
	}
	as1, err := CreateYardFromLayout(layout)
	if err != nil {
		t.Fatalf("build1: %v", err)
	}
	as2, err := CreateYardFromLayout(rt)
	if err != nil {
		t.Fatalf("build2: %v", err)
	}
	bb1, bb2 := as1.ToCompound().BBox().Data(), as2.ToCompound().BBox().Data()
	for k := 0; k < 6; k++ {
		if math.Abs(bb1[k]-bb2[k]) > 1.0 {
			t.Fatalf("round-trip bbox 轴 %d 不一致: %.3f vs %.3f", k, bb1[k], bb2[k])
		}
	}
}
