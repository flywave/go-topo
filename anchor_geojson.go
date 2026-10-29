package topo

// =========================================================================
// 锚段 GeoJSON 入口: 线路中心线 (GeoJSON) → 接触网锚段
//
//	{"type":"Feature","geometry":{"type":"LineString","coordinates":[[x,y,z]...]},
//	 "properties":{
//	   "contactHeight":6000,"structureHeight":1400,"spanLength":50000,
//	   "mastHeight":9000,"mastType":1,"sideOffset":2900,"mastSide":1,
//	   "hasCompensator":true,"staggerTable":[300,-300,...],
//	   "dropperSpacing":8000,"coordScale":1000,
//	   "auxWires":[{"kind":"AF","offset":5000,"height":8000,"bracket":true}]
//	 }}
//
// 几何方向跟随线路: 支柱以各柱里程处法向朝向线路 (frameAt), 腕臂/悬挂点/
// 附加导线折线全部沿曲线布置; 整体布置由 properties 参数化决定,
// 布局 JSON (AnchorSectionLayout) 为前端编辑面。
// =========================================================================

import (
	"encoding/json"
	"fmt"
)

// AnchorGeoProperties 锚段 GeoJSON Feature 属性 (整体布置参数)
type AnchorGeoProperties struct {
	ContactHeight   float64        `json:"contactHeight"`   // 导高, 默认 5300
	StructureHeight float64        `json:"structureHeight"` // 结构高度, 默认 1400
	SpanLength      float64        `json:"spanLength"`      // 标准跨距 (mm), 默认 50000
	MastHeight      float64        `json:"mastHeight"`      // 柱高 (mm), 默认 8000
	MastType        int            `json:"mastType"`        // 1-钢柱, 2-混凝土柱
	SideOffset      float64        `json:"sideOffset"`      // 侧面限界 CX (mm), 默认 2900
	MastSide        float64        `json:"mastSide"`        // 支柱在线路左(+1)/右(-1), 默认 +1
	HasCompensator  bool           `json:"hasCompensator"`  // 两端锚柱设补偿装置
	StaggerTable    []float64      `json:"staggerTable"`    // 各定位点拉出值; 空则之字 ±300
	DropperSpacing  float64        `json:"dropperSpacing"`  // 吊弦间距, 默认 8000
	CoordScale      float64        `json:"coordScale"`      // 坐标→mm 缩放, 默认 1000 (米输入)
	AuxWires        []AuxWireInput `json:"auxWires"`        // 附加导线配置 (可选)
}

func (p *AnchorGeoProperties) withDefaults() {
	if p.CoordScale <= 0 {
		p.CoordScale = 1000
	}
	for i := range p.AuxWires {
		p.AuxWires[i].withDefaults(p.MastSide)
	}
}

type anchorGeoInput struct {
	Type     string `json:"type"`
	Geometry *struct {
		Type        string      `json:"type"`
		Coordinates [][]float64 `json:"coordinates"`
	} `json:"geometry"`
	Coordinates [][]float64         `json:"coordinates"`
	Properties  AnchorGeoProperties `json:"properties"`
}

// ParseAnchorSectionGeoJSON 解析锚段 GeoJSON (Feature 或裸 LineString),
// 返回毫米单位的线路中心线与布置参数
func ParseAnchorSectionGeoJSON(data []byte) ([]Point3, AnchorGeoProperties, error) {
	var in anchorGeoInput
	if err := json.Unmarshal(data, &in); err != nil {
		return nil, AnchorGeoProperties{}, fmt.Errorf("anchor geojson: invalid JSON: %w", err)
	}
	var coords [][]float64
	switch in.Type {
	case "Feature":
		if in.Geometry == nil || in.Geometry.Type != "LineString" {
			return nil, AnchorGeoProperties{}, fmt.Errorf("anchor geojson: Feature geometry must be LineString")
		}
		coords = in.Geometry.Coordinates
	case "LineString":
		coords = in.Coordinates
	default:
		return nil, AnchorGeoProperties{}, fmt.Errorf("anchor geojson: unsupported type %q", in.Type)
	}
	if len(coords) < 2 {
		return nil, AnchorGeoProperties{}, fmt.Errorf("anchor geojson: LineString needs >= 2 points")
	}
	p := in.Properties
	p.withDefaults()
	if p.SpanLength > 0 && p.SpanLength < 20000 {
		return nil, AnchorGeoProperties{}, fmt.Errorf("anchor geojson: spanLength %.0f too small (<20m)", p.SpanLength)
	}
	pts := make([]Point3, len(coords))
	for i, c := range coords {
		if len(c) < 2 {
			return nil, AnchorGeoProperties{}, fmt.Errorf("anchor geojson: coordinate %d needs >= 2 elements", i)
		}
		z := 0.0
		if len(c) >= 3 {
			z = c[2]
		}
		pts[i] = NewPoint3([3]float64{c[0] * p.CoordScale, c[1] * p.CoordScale, z * p.CoordScale})
	}
	return pts, p, nil
}

// anchorInputFromProps 属性 → 锚段输入
func anchorInputFromProps(pts []Point3, p AnchorGeoProperties) AnchorSectionInput {
	return AnchorSectionInput{
		Centerline:      pts,
		ContactHeight:   p.ContactHeight,
		StructureHeight: p.StructureHeight,
		SpanLength:      p.SpanLength,
		MastHeight:      p.MastHeight,
		MastType:        p.MastType,
		SideOffset:      p.SideOffset,
		MastSide:        p.MastSide,
		HasCompensator:  p.HasCompensator,
		StaggerTable:    p.StaggerTable,
		DropperSpacing:  p.DropperSpacing,
		AuxWires:        p.AuxWires,
	}
}

// CreateAnchorSectionFromGeoJSON 从线路 GeoJSON 生成接触网锚段装配
// (= ParseAnchorSectionGeoJSON + ComputeAnchorSectionLayout + CreateAnchorSectionFromLayout)
func CreateAnchorSectionFromGeoJSON(data []byte) (*Assembly, *AnchorSectionLayout, error) {
	pts, props, err := ParseAnchorSectionGeoJSON(data)
	if err != nil {
		return nil, nil, err
	}
	layout, err := ComputeAnchorSectionLayout(anchorInputFromProps(pts, props))
	if err != nil {
		return nil, nil, err
	}
	as, err := CreateAnchorSectionFromLayout(layout)
	if err != nil {
		return nil, nil, err
	}
	return as, layout, nil
}
