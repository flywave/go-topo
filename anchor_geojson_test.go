package topo

// 锚段 GeoJSON 入口 + 线路方向跟随 + 附加导线配置

import (
	"fmt"
	"math"
	"strings"
	"testing"
)

// 曲线锚段 GeoJSON: R=600m 圆曲线 24° (弧长 ~251m), 6 柱 5 跨, AF 附加导线
func curveAnchorGeoJSON() []byte {
	R, sweep := 600000.0, 24.0*math.Pi/180.0
	n := 48
	coords := make([]string, 0, n+1)
	for i := 0; i <= n; i++ {
		th := sweep * float64(i) / float64(n)
		coords = append(coords, fmt.Sprintf("[%.6f,%.6f,0]", R*math.Cos(th), R*math.Sin(th)))
	}
	return []byte(`{"type":"Feature","geometry":{"type":"LineString","coordinates":[` +
		strings.Join(coords, ",") + `]},"properties":{
		"contactHeight":6000,"structureHeight":1400,"spanLength":50000,
		"mastHeight":9000,"mastType":1,"sideOffset":2900,"mastSide":1,
		"hasCompensator":true,"coordScale":1,
		"auxWires":[{"kind":"AF","offset":5000,"height":8000,"bracket":true}]}}`)
}

// 曲线方向跟随: 支柱朝向 ⟂ 当地切向、柱位距线路 CX; 附加导线沿线; 往返含附加导线
func TestAnchorGeoJSONCurveDirection(t *testing.T) {
	data := curveAnchorGeoJSON()
	pts, props, err := ParseAnchorSectionGeoJSON(data)
	if err != nil {
		t.Fatalf("parse: %v", err)
	}
	if props.CoordScale != 1 {
		t.Fatalf("coordScale=%v", props.CoordScale)
	}
	if len(props.AuxWires) != 1 || props.AuxWires[0].Kind != "AF" || !props.AuxWires[0].Bracket {
		t.Fatalf("aux config not parsed: %+v", props.AuxWires)
	}
	as, layout, err := CreateAnchorSectionFromGeoJSON(data)
	if err != nil {
		t.Fatalf("create: %v", err)
	}
	if len(layout.Masts) != 7 { // 251.3m / 50m = 5.03 → 6 跨 7 柱
		t.Fatalf("masts=%d want 7", len(layout.Masts))
	}
	// 支柱朝向 ⟂ 当地切向 (切向 = 法向旋转 90°)
	for i, m := range layout.Masts {
		f := frameAt(pts, m.Mileage*1000)
		tan := [3]float64{-f.perp[1], f.perp[0], 0}
		dot := math.Abs(m.Direction[0]*tan[0] + m.Direction[1]*tan[1])
		if dot > 1e-6 {
			t.Fatalf("mast %d direction not perpendicular to tangent: dot=%v", i, dot)
		}
		rad := math.Abs(m.Direction[0]*f.perp[0] + m.Direction[1]*f.perp[1])
		if math.Abs(rad-1) > 1e-9 {
			t.Fatalf("mast %d direction not radial: |dot|=%v", i, rad)
		}
	}
	// 支柱位置距线路中心 ≈ CX
	p0 := layout.Masts[2].Position
	best := math.MaxFloat64
	for _, p := range pts {
		d := p.Data()
		dx, dy := p0[0]-d[0], p0[1]-d[1]
		if v := math.Sqrt(dx*dx + dy*dy); v < best {
			best = v
		}
	}
	if math.Abs(best-2900) > 300 {
		t.Fatalf("mast distance to line %.0f != CX 2900", best)
	}
	// 附加导线: ≤10m 密采样 (251m → ~27 点), 悬挂高 8000
	if len(layout.AuxWires) != 1 {
		t.Fatalf("aux wires=%d", len(layout.AuxWires))
	}
	aw := layout.AuxWires[0]
	if len(aw.Points) < 30 || len(aw.Points) > 40 || math.Abs(aw.Points[0][2]-8000) > 1e-6 {
		t.Fatalf("AF points=%d z0=%.0f", len(aw.Points), aw.Points[0][2])
	}
	// 元素: AF 线分段 (点数-1) + 支架 7
	found := map[string]int{}
	for _, el := range as.GetElements() {
		// GetElements 返回路径限定名 (root/child/...)
		if strings.Contains(el.GetName(), "aux_wire_af_") {
			found["wire"]++
		}
		if strings.Contains(el.GetName(), "aux_bracket_af_") {
			found["bracket"]++
		}
	}
	if found["bracket"] != 7 {
		t.Fatalf("AF leaves=%v want bracket:7", found)
	}
	if found["wire"] != len(aw.Points)-1-2 { // 首末零长段 (端柱里程=折线端点) 跳过
		t.Fatalf("AF wire segs=%d want %d", found["wire"], len(aw.Points)-3)
	}
	// 布局 JSON 往返保留附加导线
	b, err := layout.ToJSON()
	if err != nil {
		t.Fatal(err)
	}
	back, err := AnchorSectionLayoutFromJSON(b)
	if err != nil {
		t.Fatal(err)
	}
	if len(back.AuxWires) != 1 || len(back.AuxWires[0].Points) != len(layout.AuxWires[0].Points) {
		t.Fatal("aux wires lost in layout roundtrip")
	}
	// 装配级往返: RebuildFromParametric 含附加导线叶片且几何一致
	data2, err := as.ExportParametric()
	if err != nil {
		t.Fatal(err)
	}
	rebuilt, err := RebuildFromParametric(data2)
	if err != nil {
		t.Fatalf("parametric rebuild: %v", err)
	}
	n := 0
	for _, el := range rebuilt.GetElements() {
		if strings.Contains(el.GetName(), "/aux_") || strings.HasPrefix(el.GetName(), "aux_") {
			n++
		}
	}
	if n != found["wire"]+7 {
		t.Fatalf("rebuilt aux leaves=%d want %d", n, found["wire"]+7)
	}
	bb1, bb2 := as.ToCompound().BBox().Data(), rebuilt.ToCompound().BBox().Data()
	for i := range bb1 {
		d := math.Abs(bb1[i] - bb2[i])
		if d > 1 {
			t.Logf("bbox[%d]: orig=%.3f rebuilt=%.3f (diff=%.3f)", i, bb1[i], bb2[i], d)
		}
	}
	// 三角化网格差异: X 向容差放宽到 5mm, 其余 1mm
	tol := [6]float64{5, 1, 1, 5, 1, 1}
	for i := range bb1 {
		if math.Abs(bb1[i]-bb2[i]) > tol[i] {
			t.Fatalf("rebuild bbox mismatch [%d]: %.3f vs %.3f", i, bb1[i], bb2[i])
		}
	}
}
