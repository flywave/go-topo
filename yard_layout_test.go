package topo

import (
	"encoding/json"
	"fmt"
	"reflect"
	"strings"
	"testing"
)

// 菱形交叉测试输入 (与 TestCreateYardCrossing 一致)
func buildYardCrossingGeoJSON() []byte {
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
	return []byte(fmt.Sprintf(`{"type":"FeatureCollection","features":[%s,%s]}`,
		mk(strings.Join(a, ",")), mk(strings.Join(b, ","))))
}

// 收集装配树全部节点名
func collectAssemblyNames(as *Assembly, out map[string]bool) map[string]bool {
	if out == nil {
		out = map[string]bool{}
	}
	out[as.GetName()] = true
	for _, ch := range as.Children() {
		collectAssemblyNames(ch, out)
	}
	return out
}

func TestComputeYardLayout(t *testing.T) {
	layout, err := ComputeYardLayout(buildYardGeoJSON())
	if err != nil {
		t.Fatalf("ComputeYardLayout failed: %v", err)
	}
	if len(layout.Tracks) != 3 {
		t.Fatalf("expect 3 tracks, got %d", len(layout.Tracks))
	}
	if len(layout.Turnouts) != 1 {
		t.Fatalf("expect 1 turnout, got %d", len(layout.Turnouts))
	}
	if len(layout.Crossings) != 0 {
		t.Fatalf("expect 0 crossings, got %d", len(layout.Crossings))
	}
	tn := layout.Turnouts[0]
	if !tn.IsLeftHand {
		t.Fatal("expect left-hand turnout")
	}
	if tn.TurnoutNo != 12 { // 侧线 R=350m → 12 号
		t.Fatalf("expect turnout no 12, got %d", tn.TurnoutNo)
	}
	// 主入边 (0,0)→(100,0) 终点应被裁掉 岔前段 (swLen+2000)
	if layout.Tracks[0].TrimS != 0 || layout.Tracks[0].TrimE <= 0 {
		t.Fatalf("track0 trim wrong: S=%.0f E=%.0f", layout.Tracks[0].TrimS, layout.Tracks[0].TrimE)
	}
	full := 100000.0
	if layout.Tracks[0].TrimE >= full {
		t.Fatalf("track0 should be trimmed before node, TrimE=%.0f", layout.Tracks[0].TrimE)
	}
	// 关联边索引互不相同
	if tn.EdgeIn == tn.EdgeOut || tn.EdgeIn == tn.EdgeDiv || tn.EdgeOut == tn.EdgeDiv {
		t.Fatalf("turnout edge refs not distinct: %d/%d/%d", tn.EdgeIn, tn.EdgeOut, tn.EdgeDiv)
	}
}

func TestComputeYardLayoutCrossing(t *testing.T) {
	layout, err := ComputeYardLayout(buildYardCrossingGeoJSON())
	if err != nil {
		t.Fatalf("ComputeYardLayout failed: %v", err)
	}
	if len(layout.Tracks) != 2 {
		t.Fatalf("expect 2 tracks, got %d", len(layout.Tracks))
	}
	if len(layout.Turnouts) != 0 {
		t.Fatalf("expect 0 turnouts, got %d", len(layout.Turnouts))
	}
	if len(layout.Crossings) != 1 {
		t.Fatalf("expect 1 crossing, got %d", len(layout.Crossings))
	}
	cr := layout.Crossings[0]
	if cr.Position[0] < 199000 || cr.Position[0] > 201000 {
		t.Fatalf("crossing x wrong: %.0f", cr.Position[0])
	}
	// 未识别道岔, 两股道均不裁剪
	for i, tr := range layout.Tracks {
		if tr.TrimS != 0 {
			t.Fatalf("track%d TrimS should be 0, got %.0f", i, tr.TrimS)
		}
	}
}

func TestYardLayoutJSONRoundTrip(t *testing.T) {
	for name, input := range map[string][]byte{
		"turnout":  buildYardGeoJSON(),
		"crossing": buildYardCrossingGeoJSON(),
	} {
		layout, err := ComputeYardLayout(input)
		if err != nil {
			t.Fatalf("%s: %v", name, err)
		}
		raw, err := layout.ToJSON()
		if err != nil {
			t.Fatalf("%s: ToJSON: %v", name, err)
		}
		back, err := YardLayoutFromJSON(raw)
		if err != nil {
			t.Fatalf("%s: FromJSON: %v", name, err)
		}
		if !reflect.DeepEqual(layout, back) {
			t.Fatalf("%s: layout JSON round trip mismatch", name)
		}
	}
}

func TestCreateYardFromLayoutNaming(t *testing.T) {
	layout, err := ComputeYardLayout(buildYardGeoJSON())
	if err != nil {
		t.Fatalf("compute: %v", err)
	}
	as, err := CreateYardFromLayout(layout)
	if err != nil {
		t.Fatalf("from layout: %v", err)
	}
	names := collectAssemblyNames(as, nil)
	// 3 边 × (钢轨+轨枕) + 1 道岔 = 7, 且全部唯一
	if len(names) != 7 {
		t.Fatalf("expect 7 unique names, got %d: %v", len(names), names)
	}
	for _, want := range []string{"rails_0", "sleepers_0", "rails_1", "sleepers_1", "rails_2", "sleepers_2", "turnout_0"} {
		if !names[want] {
			t.Fatalf("missing element %q", want)
		}
	}
	// 与旧入口结果一致 (确定性)
	as2, err := CreateYardFromGeoJSON(buildYardGeoJSON())
	if err != nil {
		t.Fatalf("from geojson: %v", err)
	}
	if !reflect.DeepEqual(names, collectAssemblyNames(as2, nil)) {
		t.Fatal("FromLayout 与 FromGeoJSON 子件名集合不一致")
	}
}

func TestYardLayoutEditRegenerate(t *testing.T) {
	layout, err := ComputeYardLayout(buildYardGeoJSON())
	if err != nil {
		t.Fatalf("compute: %v", err)
	}
	as1, err := CreateYardFromLayout(layout)
	if err != nil {
		t.Fatalf("from layout: %v", err)
	}
	bb1 := as1.ToCompound().BBox().Data()

	// 编辑场景 1: 把正线首段 (0,0)→(100,0) 起点裁掉 50m
	layout.Tracks[0].TrimS = 50000
	as2, err := CreateYardFromLayout(layout)
	if err != nil {
		t.Fatalf("from edited layout: %v", err)
	}
	bb2 := as2.ToCompound().BBox().Data()
	dx1, dx2 := bb1[3]-bb1[0], bb2[3]-bb2[0]
	if dx1-dx2 < 40000 {
		t.Fatalf("trim edit should shrink bbox: before %.0f after %.0f", dx1, dx2)
	}

	// 编辑场景 2: 改道岔号数 12 → 9
	layout.Tracks[0].TrimS = 0
	layout.Turnouts[0].TurnoutNo = 9
	layout.Turnouts[0].SwitchRailLength = 0 // 置 0 让 FromLayout 按号数查表
	layout.Turnouts[0].LeadCurveRadius = 0
	as3, err := CreateYardFromLayout(layout)
	if err != nil {
		t.Fatalf("from edited layout: %v", err)
	}
	// 找到 turnout_0 子件, bbox 应与 12 号不同
	bbOf := func(as *Assembly) [6]float64 {
		for _, ch := range as.Children() {
			if ch.GetName() == "turnout_0" {
				return ch.ToCompound().BBox().Data()
			}
		}
		return [6]float64{}
	}
	bb12, bb9 := bbOf(as1), bbOf(as3)
	if bb12 == ([6]float64{}) || bb9 == ([6]float64{}) {
		t.Fatal("turnout_0 element not found")
	}
	if bb12 == bb9 {
		t.Fatal("turnout bbox unchanged after TurnoutNo edit")
	}
	t.Logf("turnout bbox 12号: %.0f x %.0f, 9号: %.0f x %.0f",
		bb12[3]-bb12[0], bb12[4]-bb12[1], bb9[3]-bb9[0], bb9[4]-bb9[1])
}

func TestYardParametricRoundTrip(t *testing.T) {
	as, err := CreateYardFromGeoJSON(buildYardGeoJSON())
	if err != nil {
		t.Fatalf("from geojson: %v", err)
	}
	raw, err := as.ExportParametric()
	if err != nil {
		t.Fatalf("export: %v", err)
	}
	rebuilt, err := RebuildFromParametric(raw)
	if err != nil {
		t.Fatalf("rebuild: %v", err)
	}
	names1 := collectAssemblyNames(as, nil)
	names2 := collectAssemblyNames(rebuilt, nil)
	if !reflect.DeepEqual(names1, names2) {
		t.Fatalf("name set mismatch:\n before: %v\n after: %v", names1, names2)
	}
	// 重建后配方仍在 (再导出与原导出一致)
	raw2, err := rebuilt.ExportParametric()
	if err != nil {
		t.Fatalf("re-export: %v", err)
	}
	var el1, el2 ParametricElement
	if err := json.Unmarshal(raw, &el1); err != nil {
		t.Fatalf("unmarshal export: %v", err)
	}
	if err := json.Unmarshal(raw2, &el2); err != nil {
		t.Fatalf("unmarshal re-export: %v", err)
	}
	if !reflect.DeepEqual(el1, el2) {
		t.Fatal("parametric export changed after rebuild round trip")
	}
	// 重建后整体 bbox 与原装配一致
	bb1 := as.ToCompound().BBox().Data()
	bb2 := rebuilt.ToCompound().BBox().Data()
	for i := 0; i < 6; i++ {
		if d := bb1[i] - bb2[i]; d > 1 || d < -1 {
			t.Fatalf("bbox mismatch at %d: %.1f vs %.1f", i, bb1[i], bb2[i])
		}
	}
}

func TestCreateYardFromGeoJSONWithLayout(t *testing.T) {
	as, layout, err := CreateYardFromGeoJSONWithLayout(buildYardGeoJSON())
	if err != nil {
		t.Fatalf("with layout: %v", err)
	}
	if as == nil || layout == nil {
		t.Fatal("nil result")
	}
	if len(layout.Turnouts) != 1 || len(layout.Tracks) != 3 {
		t.Fatalf("layout wrong: %d tracks, %d turnouts", len(layout.Tracks), len(layout.Turnouts))
	}
}
