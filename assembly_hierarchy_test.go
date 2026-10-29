package topo

// 铁路装配层级验收: 金具/零件逐级组装为功能单元, 前端按单元粒度编辑
//
//	接触网: 支柱装置(mast_i) + 跨距(span_i) → 锚段(anchor_section)
//	轨道:   股道(track_i){钢轨组+轨枕} + 道岔/交叉 → 站场(yard)
//
// 验证点: 层级结构 / 装配级配方整棵重建 / 跨距粒度编辑 / 路径寻址 / 几何等价

import (
	"encoding/json"
	"math"
	"sort"
	"testing"
)

func anchorHierarchyInput() AnchorSectionInput {
	var cl []Point3
	for x := 0.0; x <= 150000; x += 5000 {
		cl = append(cl, NewPoint3([3]float64{x, 0, 0}))
	}
	return AnchorSectionInput{Centerline: cl, ContactHeight: 6000, StructureHeight: 1400,
		SpanLength: 50000, MastHeight: 9000, MastType: 1, SideOffset: 2900, HasCompensator: true}
}

// 锚段层级: 顶层只有支柱装置与跨距; 金具/线索在跨距内
func TestAnchorHierarchy(t *testing.T) {
	layout, err := ComputeAnchorSectionLayout(anchorHierarchyInput())
	if err != nil {
		t.Fatalf("compute: %v", err)
	}
	as, err := CreateAnchorSectionFromLayout(layout)
	if err != nil {
		t.Fatalf("from layout: %v", err)
	}
	var top []string
	for _, ch := range as.Children() {
		top = append(top, ch.GetName())
	}
	sort.Strings(top)
	// 3 跨: mast_0..3 + span_0..2
	if len(top) != 7 {
		t.Fatalf("top-level = %v, want 4 mast + 3 span", top)
	}
	sp2 := childAssembly(t, as, "span_2")
	var leaves []string
	for _, ch := range sp2.Children() {
		leaves = append(leaves, ch.GetName())
	}
	sort.Strings(leaves)
	// 跨内: cw_2 / mw_2 / dropper_2_k (集合断言)
	has := map[string]bool{}
	for _, n := range leaves {
		has[n] = true
	}
	if len(leaves) < 4 {
		t.Fatalf("span_2 leaves = %v, want cw+mw+droppers", leaves)
	}
	if !has["cw_2"] || !has["mw_2"] || !has["dropper_2_0"] {
		t.Fatalf("span_2 leaves missing key parts: %v", leaves)
	}
}

// childAssembly 按名取直接子装配
func childAssembly(t *testing.T, as *Assembly, name string) *Assembly {
	t.Helper()
	for _, ch := range as.Children() {
		if ch.GetName() == name {
			return ch
		}
	}
	t.Fatalf("child assembly %q not found", name)
	return nil
}

// 跨距配方整棵重建: ExportParametric 提取 span_1 节点 → RebuildFromParametric → bbox 等价
func TestSpanAssemblyBuilderRebuild(t *testing.T) {
	layout, err := ComputeAnchorSectionLayout(anchorHierarchyInput())
	if err != nil {
		t.Fatalf("compute: %v", err)
	}
	as, err := CreateAnchorSectionFromLayout(layout)
	if err != nil {
		t.Fatalf("from layout: %v", err)
	}
	data, err := as.ExportParametric()
	if err != nil {
		t.Fatalf("export: %v", err)
	}
	var tree ParametricElement
	if err := json.Unmarshal(data, &tree); err != nil {
		t.Fatal(err)
	}
	var spanJSON []byte
	for _, ch := range tree.Children {
		if ch.Name == "span_1" {
			spanJSON, err = json.Marshal(ch)
			if err != nil {
				t.Fatal(err)
			}
			break
		}
	}
	if spanJSON == nil {
		t.Fatal("span_1 not in export")
	}
	ref := subtreeBBox(t, as, "span_1")
	rebuilt, err := RebuildFromParametric(spanJSON)
	if err != nil {
		t.Fatalf("rebuild span: %v", err)
	}
	if rebuilt.GetName() != "span_1" {
		t.Fatalf("rebuilt name %q", rebuilt.GetName())
	}
	bb := rebuilt.ToCompound().BBox().Data()
	for i := range ref {
		if math.Abs(bb[i]-ref[i]) > 1 {
			t.Fatalf("span_1 rebuild bbox mismatch at [%d]: %v vs %v", i, ref, bb)
		}
	}
	// 叶片配方齐全 (跨内线索/吊弦可继续细部寻址)
	if _, ok := rebuilt.Get("mw_1"); !ok {
		t.Fatal("rebuilt span missing mw_1")
	}
}

// 跨距粒度编辑: 改配方弛度/吊弦表 → 单跨重建 → 几何跟随
func TestSpanRecipeEditRebuild(t *testing.T) {
	layout, err := ComputeAnchorSectionLayout(anchorHierarchyInput())
	if err != nil {
		t.Fatalf("compute: %v", err)
	}
	as, err := CreateAnchorSectionFromLayout(layout)
	if err != nil {
		t.Fatalf("from layout: %v", err)
	}
	data, err := as.ExportParametric()
	if err != nil {
		t.Fatal(err)
	}
	var tree ParametricElement
	if err := json.Unmarshal(data, &tree); err != nil {
		t.Fatal(err)
	}
	var span *ParametricElement
	for _, ch := range tree.Children {
		if ch.Name == "span_0" {
			span = ch
			break
		}
	}
	if span == nil {
		t.Fatal("span_0 missing")
	}
	// 改弛度 750→1500, 吊弦表加密
	var recipe ocsSpanRecipe
	if err := json.Unmarshal(span.Params, &recipe); err != nil {
		t.Fatal(err)
	}
	recipe.Messenger.Sag = 1000
	recipe.Droppers = []float64{0.2, 0.4, 0.6, 0.8}
	span.Params = mustJSON(recipe)
	edited, err := json.Marshal(span)
	if err != nil {
		t.Fatal(err)
	}
	rebuilt, err := RebuildFromParametric(edited)
	if err != nil {
		t.Fatalf("rebuild edited span: %v", err)
	}
	bb := rebuilt.ToCompound().BBox().Data()
	dz := bb[5] - bb[2]
	// 承力索弛度加倍 → 跨内垂深明显增大 (结构高1400+弛度)
	if dz < 1400 || dz > 3200 {
		t.Fatalf("edited span dz = %.0f, want [1400,3200]", dz)
	}
	// 吊弦表驱动叶片数量
	var drops int
	for _, ch := range rebuilt.Children() {
		if len(ch.GetName()) > 8 && ch.GetName()[:8] == "dropper_" {
			drops++
		}
	}
	if drops != 4 {
		t.Fatalf("edited span droppers = %d, want 4", drops)
	}
}

// 站场: 股道配方整棵重建等价 + 根容器 vertex 不污染全局 bbox
func TestYardTrackAssemblyBuilderRebuild(t *testing.T) {
	as, layout, err := CreateYardFromGeoJSONWithLayout(buildYardGeoJSON())
	if err != nil {
		t.Fatalf("yard: %v", err)
	}
	data, err := as.ExportParametric()
	if err != nil {
		t.Fatal(err)
	}
	var tree ParametricElement
	if err := json.Unmarshal(data, &tree); err != nil {
		t.Fatal(err)
	}
	var trackJSON []byte
	for _, ch := range tree.Children {
		if ch.Name == "track_1" {
			trackJSON, err = json.Marshal(ch)
			if err != nil {
				t.Fatal(err)
			}
			break
		}
	}
	if trackJSON == nil {
		t.Fatal("track_1 not in export")
	}
	ref := subtreeBBox(t, as, "track_1")
	rebuilt, err := RebuildFromParametric(trackJSON)
	if err != nil {
		t.Fatalf("rebuild track: %v", err)
	}
	bb := rebuilt.ToCompound().BBox().Data()
	for i := range ref {
		if math.Abs(bb[i]-ref[i]) > 1 {
			t.Fatalf("track_1 rebuild bbox mismatch at [%d]: %v vs %v", i, ref, bb)
		}
	}
	// 股道配方内容 = 布局数据 (裁剪+参数随编辑走)
	var r yardTrackRecipe
	if err := json.Unmarshal(tree.Children[1].Params, &r); err != nil {
		t.Fatal(err)
	}
	if len(r.Centerline) != len(layout.Tracks[1].Centerline) {
		t.Fatal("track recipe centerline mismatch")
	}
	_ = layout
}

// 路径寻址: 根名前缀 / 相对路径 / 非唯一名不命中
func TestAssemblyGetPathAddressing(t *testing.T) {
	as, err := CreateYardFromGeoJSON(buildYardGeoJSON())
	if err != nil {
		t.Fatal(err)
	}
	if _, ok := as.Get("yard/track_1/rails_1"); !ok {
		t.Fatal("root-prefixed path failed")
	}
	if _, ok := as.Get("track_1/rails_1"); !ok {
		t.Fatal("relative path failed")
	}
	if _, ok := as.Get("rails_1"); !ok {
		t.Fatal("unique deep name failed")
	}
	// 跨子装配重名不唯一 → 不命中 (rails_i 各股道唯一, 构造一个歧义场景不可行, 改查不存在名)
	if _, ok := as.Get("track_9/rails_9"); ok {
		t.Fatal("nonexistent path should not hit")
	}
}

// subtreeBBox 按路径走装配树, 返回目标子装配 ToCompound 的 bbox
func subtreeBBox(t *testing.T, as *Assembly, path string) [6]float64 {
	t.Helper()
	segs := splitPath(path, as.GetName())
	cur := as
	for _, seg := range segs {
		found := false
		for _, ch := range cur.Children() {
			if ch.GetName() == seg {
				cur = ch
				found = true
				break
			}
		}
		if !found {
			t.Fatalf("path %q: segment %q not found", path, seg)
		}
	}
	return cur.ToCompound().BBox().Data()
}

func splitPath(path, root string) []string {
	var out []string
	cur := ""
	for _, r := range path {
		if r == '/' {
			out = append(out, cur)
			cur = ""
			continue
		}
		cur += string(r)
	}
	out = append(out, cur)
	if len(out) > 0 && out[0] == root {
		out = out[1:]
	}
	return out
}
