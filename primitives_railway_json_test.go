package topo

import (
	"encoding/json"
	"strings"
	"testing"
)

// 断言 map 的所有键 (含嵌套) 均为 camelCase (首字母小写)
func assertCamelKeys(t *testing.T, v interface{}, path string) {
	t.Helper()
	m, ok := v.(map[string]interface{})
	if !ok {
		return
	}
	for k, sub := range m {
		if k == "" || k[0] < 'a' || k[0] > 'z' {
			t.Errorf("%s: key %q is not camelCase", path, k)
		}
		assertCamelKeys(t, sub, path+"."+k)
	}
}

func marshalToMap(t *testing.T, v interface{}) map[string]interface{} {
	t.Helper()
	raw, err := json.Marshal(v)
	if err != nil {
		t.Fatalf("marshal failed: %v", err)
	}
	var m map[string]interface{}
	if err := json.Unmarshal(raw, &m); err != nil {
		t.Fatalf("remarshal failed: %v", err)
	}
	return m
}

// 铁路 params struct 的 JSON 键必须全 camelCase (与 topotypes 对齐), 且能双向往返
func TestRailwayParamsCamelCaseJSON(t *testing.T) {
	// ContactWireParams: marshal → camelCase 键
	cw := ContactWireParams{
		SectionalArea: 120, Diameter: 12.9, RatedTension: 15,
		GrooveDepth: 4.1, GrooveWidth: 6.8, BottomRadius: 8, TopRadius: 3, Sag: 25,
	}
	m := marshalToMap(t, cw)
	for _, k := range []string{"sectionalArea", "diameter", "ratedTension", "grooveDepth",
		"grooveWidth", "bottomRadius", "topRadius", "sag"} {
		if _, ok := m[k]; !ok {
			t.Errorf("ContactWireParams missing camelCase key %q, got %v", k, m)
		}
	}
	assertCamelKeys(t, m, "ContactWireParams")

	// unmarshal camelCase JSON 回来字段正确 (双向)
	var cw2 ContactWireParams
	if err := json.Unmarshal([]byte(`{"sectionalArea":150,"diameter":13.5,"ratedTension":20,"sag":30}`), &cw2); err != nil {
		t.Fatalf("unmarshal camelCase failed: %v", err)
	}
	if cw2.SectionalArea != 150 || cw2.Diameter != 13.5 || cw2.RatedTension != 20 || cw2.Sag != 30 {
		t.Fatalf("unmarshal field mismatch: %+v", cw2)
	}

	// Type 字段按 topotypes 语义命名: crossArmType / insulatorType / fittingType / bracketType / armType / mastType / foundationType / curvedArmType
	typeCases := []struct {
		name string
		v    interface{}
		key  string
	}{
		{"CrossArmParams", CrossArmParams{Type: 2}, "crossArmType"},
		{"RodInsulatorParams", RodInsulatorParams{Type: 1}, "insulatorType"},
		{"AnchorFittingParams", AnchorFittingParams{Type: 3}, "fittingType"},
		{"AuxBracketParams", AuxBracketParams{Type: 1}, "bracketType"},
		{"RegistrationArmParams", RegistrationArmParams{Type: 2}, "armType"},
		{"SteelMastParams", SteelMastParams{Type: 1}, "mastType"},
		{"OcsFoundationParams", OcsFoundationParams{Type: 2}, "foundationType"},
		{"CurvedArmParams", CurvedArmParams{Type: 1}, "curvedArmType"},
	}
	for _, tc := range typeCases {
		m := marshalToMap(t, tc.v)
		if _, ok := m[tc.key]; !ok {
			t.Errorf("%s: missing semantic key %q, got %v", tc.name, tc.key, m)
		}
		if _, ok := m["type"]; ok {
			t.Errorf("%s: should not emit plain \"type\" key", tc.name)
		}
		if _, ok := m["Type"]; ok {
			t.Errorf("%s: should not emit PascalCase \"Type\" key", tc.name)
		}
	}

	// 嵌套结构: RatchetCompensatorParams.Stack → "stack" 内 camelCase
	rc := RatchetCompensatorParams{WheelDiameter: 400, Stack: WeightStackParams{BlockCount: 8, BlockDiameter: 380}}
	m = marshalToMap(t, rc)
	assertCamelKeys(t, m, "RatchetCompensatorParams")
	stack, ok := m["stack"].(map[string]interface{})
	if !ok {
		t.Fatalf("RatchetCompensatorParams missing nested \"stack\" object: %v", m)
	}
	if _, ok := stack["blockCount"]; !ok {
		t.Errorf("WeightStackParams nested key blockCount missing: %v", stack)
	}

	// 道岔/轨道段: 抽查代表性键
	m = marshalToMap(t, TurnoutParams{TurnoutNo: 12, IsLeftHand: true, SwitchRailLength: 7700})
	assertCamelKeys(t, m, "TurnoutParams")
	for _, k := range []string{"turnoutNo", "isLeftHand", "switchRailLength", "leadCurveRadius", "sleeperSpacing"} {
		if _, ok := m[k]; !ok {
			t.Errorf("TurnoutParams missing key %q", k)
		}
	}
	m = marshalToMap(t, MastAssemblyParams{MastType: 1, ContactHeight: 5300})
	assertCamelKeys(t, m, "MastAssemblyParams")
	for _, k := range []string{"mastType", "cantileverType", "hasCrossArm", "contactHeight", "structureHeight", "sideOffset"} {
		if _, ok := m[k]; !ok {
			t.Errorf("MastAssemblyParams missing key %q", k)
		}
	}
	m = marshalToMap(t, StraightTrackParams{Gauge: 1435, BallastSlope: 1.5})
	assertCamelKeys(t, m, "StraightTrackParams")
	for _, k := range []string{"startPoint", "endPoint", "gauge", "ballastTopWidth", "ballastThickness", "ballastSlope"} {
		if _, ok := m[k]; !ok {
			t.Errorf("StraightTrackParams missing key %q", k)
		}
	}
}

// ExportParametric 导出的配方 params 载荷必须为 camelCase (供前端/topotypes 消费)
func TestAnchorParametricExportCamelCase(t *testing.T) {
	as, err := CreateAnchorSection(anchorTestInput())
	if err != nil {
		t.Fatalf("create anchor section failed: %v", err)
	}
	data, err := as.ExportParametric()
	if err != nil {
		t.Fatalf("ExportParametric failed: %v", err)
	}
	s := string(data)
	// ocs_mast 配方内嵌 MastAssemblyParams, ocs_dropper 内嵌 DropperParams
	for _, k := range []string{`"mastType"`, `"mastHeight"`, `"contactHeight"`, `"wireDiameter"`, `"clampLength"`} {
		if !strings.Contains(s, k) {
			t.Errorf("exported parametric missing camelCase key %s", k)
		}
	}
	for _, k := range []string{`"MastType"`, `"MastHeight"`, `"ContactHeight"`, `"WireDiameter"`, `"ClampLength"`} {
		if strings.Contains(s, k) {
			t.Errorf("exported parametric still contains PascalCase key %s", k)
		}
	}
	// 往返不破坏
	if _, err := RebuildFromParametric(data); err != nil {
		t.Fatalf("RebuildFromParametric failed: %v", err)
	}
}
