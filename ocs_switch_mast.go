package topo

// =========================================================================
// 开关柱 (接触网接入变电站):
//
//	杆型可选 (格构钢柱/H型钢柱/混凝土支柱) + 腕臂(定位接触线)
//	+ 顶部三梁矩形框 (两纵梁沿线路 + 中横梁联接, 斜撑落地)
//	   装 GW4 双柱式隔离开关×3~4 组 (每组两绝缘子各坐一纵梁, 刀闸横跨)
//	+ T连接线(承力索挂点→开关进线端) + 馈线引出线(开关出线端→沿线上/下行)
//	+ 回流线支臂/回流线/引下线 (连通接触网与回流线)
//
// 局部约定: 原点=柱底中心, +X 指向线路, +Y 沿线路, Z 向上。
// 参数化: ocs_switch_mast 装配级 builder, 整棵重建。
// =========================================================================

import (
	"encoding/json"
	"fmt"
	"math"
)

// SwitchMastParams 开关柱参数
type SwitchMastParams struct {
	MastType        int     `json:"mastType"`        // 杆型: 1=格构钢柱(默认) 2=H型钢柱 3=混凝土支柱
	MastHeight      float64 `json:"mastHeight"`      // 柱高, 默认 11000
	ContactHeight   float64 `json:"contactHeight"`   // 导高, 默认 6000
	StructureHeight float64 `json:"structureHeight"` // 结构高度, 默认 1400
	SideOffset      float64 `json:"sideOffset"`      // 侧面限界 CX, 默认 2900
	Stagger         float64 `json:"stagger"`         // 拉出值, 默认 300
	SwitchCount     int     `json:"switchCount"`     // 隔离开关组数 (GW4 双柱式: 3/4 组), 默认 4
	SwitchOpen      float64 `json:"switchOpen"`      // 开关分闸角度, 0=合闸, 默认 0
	CrossarmSpan    float64 `json:"crossarmSpan"`    // 开关框纵梁长 (沿线路), 默认 3600
	FrameWidth      float64 `json:"frameWidth"`      // 开关框两纵梁间距, 默认 1200
	FeedOutOffset   float64 `json:"feedOutOffset"`   // 馈线引出沿线路距离, 默认 8000
	FeedOutHeight   float64 `json:"feedOutHeight"`   // 馈线挂点高, 默认 9800
	HasReturnLine   bool    `json:"hasReturnLine"`   // 装回流线支臂/回流线/引下线, 默认 true
}

func (p *SwitchMastParams) withDefaults() {
	if p.MastType != 2 && p.MastType != 3 {
		p.MastType = 1
	}
	if p.MastHeight <= 0 {
		p.MastHeight = 11000
	}
	if p.ContactHeight <= 0 {
		p.ContactHeight = 6000
	}
	if p.StructureHeight <= 0 {
		p.StructureHeight = 1400
	}
	if p.SideOffset <= 0 {
		p.SideOffset = 2900
	}
	if p.Stagger == 0 {
		p.Stagger = 300
	}
	if p.SwitchCount != 3 && p.SwitchCount != 4 {
		p.SwitchCount = 4
	}
	if p.CrossarmSpan <= 0 {
		p.CrossarmSpan = 3600
	}
	if p.FrameWidth <= 0 {
		p.FrameWidth = 1200
	}
	if p.FeedOutOffset <= 0 {
		p.FeedOutOffset = 8000
	}
	if p.FeedOutHeight <= 0 {
		p.FeedOutHeight = 9800
	}
}

// switchMastPost 杆型可选: 1=格构钢柱 2=H型钢柱 3=混凝土支柱
func switchMastPost(p SwitchMastParams) *Shape {
	switch p.MastType {
	case 2:
		return CreateSteelMast(SteelMastParams{Type: 0, Height: p.MastHeight,
			TopWidth: 300, BottomWidth: 500, WallThickness: 10,
			FlangeThickness: 16, FlangeWidth: 300})
	case 3:
		return CreateConcreteMast(ConcreteMastParams{SectionType: 1, Height: p.MastHeight,
			TopWidth: 300, BottomWidth: 550, WallThickness: 60})
	default:
		return CreateSteelMast(SteelMastParams{Type: 1, Height: p.MastHeight,
			TopWidth: 300, BottomWidth: 900, WallThickness: 5,
			FlangeThickness: 16, FlangeWidth: 300})
	}
}

// switchMastFrame 顶部三梁矩形框 (两纵梁沿线路 + 中横梁联接, 四角斜撑落地):
// 隔离开关底座坐在纵梁上。返回合并后的单 compound。
func switchMastFrame(span, frameW, z float64) *Shape {
	beamX := []float64{200 - frameW/2, 200 + frameW/2}
	parts := []Shape{}
	// 纵梁 ×2 (沿线路)
	for _, bx := range beamX {
		parts = append(parts, *crossarmShape(ocsCrossarmRecipe{Span: span, CenterX: bx, Width: 140, Height: 140, Z: z}))
	}
	// 中横梁 (垂直线路, 联接两纵梁)
	parts = append(parts, *CreateCuboidWithPlace(CuboidParams{Length: float32(frameW + 140), Width: 140, Height: 140},
		NewPoint3([3]float64{200, 0, z}), NewDir3FromXYZ([3]float64{1, 0, 0}),
		NewDir3FromXYZ([3]float64{0, 0, 1})))
	// 四角斜撑: 纵梁端部 → 柱身 (向下收拢)
	for _, bx := range beamX {
		for _, sy := range []float64{-1, 1} {
			bx0, by0 := bx, sy*span*0.375
			sv := [3]float64{80 - bx0, -by0, -850}
			sl := math.Hypot(sv[0], math.Hypot(sv[1], sv[2]))
			if sl < 200 {
				continue
			}
			parts = append(parts, *CreateSlantCantileverWithPlace(
				SlantCantileverParams{Length: sl, OuterDiameter: 42, WallThickness: 3.5},
				NewPoint3([3]float64{bx0, by0, z - 70}),
				NewDir3FromXYZ([3]float64{sv[0] / sl, sv[1] / sl, sv[2] / sl}),
				NewDir3FromXYZ([3]float64{0, 0, 1})))
		}
	}
	return TopoCompoundMake(parts).ToShape()
}

// CreateSwitchMastWithPlace 组装开关柱 (局部坐标: 原点=柱底中心, +X 指向线路)
func CreateSwitchMastWithPlace(p SwitchMastParams, name string) (*Assembly, error) {
	p.withDefaults()
	if name == "" {
		name = "switch_mast"
	}
	root := NewAssembly(NewAssemblyObjectFromShpe(*NewVertex(0, 0, p.MastHeight/2).ToShape()),
		nil, name, nil)
	add := func(s *Shape, leaf string, data *ParametricData) {
		if s == nil || s.IsNull() {
			return
		}
		root.AddObjectParams(NewAssemblyObjectFromShpe(*s), nil, leaf, nil, data)
	}

	// 1. 杆柱 (杆型可选)
	add(switchMastPost(p), "post", nil)

	// 2. 腕臂组 (定位接触线, 与支柱装置同构)
	ch, sh, cx := p.ContactHeight, p.StructureHeight, p.SideOffset
	cant := buildCantileverSet(MastAssemblyParams{MastType: 1, MastHeight: p.MastHeight,
		CantileverType: 1, ArmDiameter: 55, Stagger: p.Stagger,
		ContactHeight: ch, StructureHeight: sh, SideOffset: cx}, p.Stagger, 0)
	add(cant, "cantilever", nil)

	// 3. 顶部三梁矩形框 (两纵梁沿线路 + 中横梁联接, 四角斜撑落地)
	frameZ := p.MastHeight - 1200
	add(switchMastFrame(p.CrossarmSpan, p.FrameWidth, frameZ), "frame", nil)

	// 4. 隔离开关 ×N (GW4 双柱式: 每组两支柱绝缘子分别坐在两根纵梁上,
	//    刀闸横跨两梁之间; 沿线路一排均布。BaseLength = FrameWidth+200
	//    使两支柱恰好落在纵梁中心, 底座两端搭在梁上)
	frameZtop := frameZ + 70
	span := p.CrossarmSpan
	dGap := 900.0
	if avail := span - 900.0; dGap*(float64(p.SwitchCount)-1) > avail {
		dGap = avail / float64(p.SwitchCount-1)
	}
	for k := 0; k < p.SwitchCount; k++ {
		yG := (float64(k) - float64(p.SwitchCount-1)/2) * dGap
		dp := DisconnectorParams{BaseLength: p.FrameWidth + 200, BaseWidth: 220,
			InsulatorHeight: 600, BladeLength: 800, OpenAngle: p.SwitchOpen}
		add(CreateDisconnectorWithPlace(dp, NewPoint3([3]float64{200, yG, frameZtop}),
			NewDir3FromXYZ([3]float64{1, 0, 0}), NewDir3FromXYZ([3]float64{0, 0, 1})),
			fmt.Sprintf("switch_%d", k), nil)
	}

	// 5. T 连接线 (承力索挂点 → 开关进线柱顶) + 馈线引出线 (出线柱顶 → 沿线上/下行)
	mp := [3]float64{cx - p.Stagger, 0, ch + sh} // 承力索挂点
	for k := 0; k < p.SwitchCount; k++ {
		yG := (float64(k) - float64(p.SwitchCount-1)/2) * dGap
		pxIn := 200 - p.FrameWidth/2  // 线路侧柱 (进线)
		pxOut := 200 + p.FrameWidth/2 // field 侧柱 (出线)
		sign := 1.0
		if yG < 0 {
			sign = -1.0
		}
		add(CreateAuxiliaryWire(AuxiliaryWireParams{Diameter: 16, Sag: 180},
			NewPoint3(mp), NewPoint3([3]float64{pxIn, yG, frameZtop + 660})),
			fmt.Sprintf("link_t_%d", k), nil)
		add(CreateAuxiliaryWire(AuxiliaryWireParams{Diameter: 16, Sag: 260},
			NewPoint3([3]float64{pxOut, yG, frameZtop + 660}),
			NewPoint3([3]float64{pxOut, yG + sign*p.FeedOutOffset, p.FeedOutHeight})),
			fmt.Sprintf("feed_out_%d", k), nil)
	}

	// 6. 回流线支臂 + 回流线 + 引下线 (连通接触网与回流线)
	if p.HasReturnLine {
		pwX := -800.0 // field 侧 (背离线路)
		pwZ := 7000.0
		add(CreateLevelCantileverWithPlace(LevelCantileverParams{Length: 650, OuterDiameter: 48, WallThickness: 4},
			NewPoint3([3]float64{-150, 0, pwZ}), NewDir3FromXYZ([3]float64{-1, 0, 0}),
			NewDir3FromXYZ([3]float64{0, 0, 1})), "pw_arm", nil)
		add(CreateAuxiliaryWire(AuxiliaryWireParams{Diameter: 14, Sag: 120},
			NewPoint3([3]float64{pwX, -3000, pwZ}), NewPoint3([3]float64{pwX, 3000, pwZ})),
			"pw_wire", nil)
		add(CreateAuxiliaryWire(AuxiliaryWireParams{Diameter: 14, Sag: 60},
			NewPoint3([3]float64{pwX, 0, pwZ}), NewPoint3([3]float64{-150, 0, lowerBracketZ(ch, sh)})),
			"pw_lead", nil)
	}
	return root, nil
}

// lowerBracketZ 腕臂下底座高 (与 buildCantileverSet 尺寸链一致: 平腕臂高-1300)
func lowerBracketZ(ch, sh float64) float64 {
	return ch + sh - 150 - 1300
}

// buildOcsSwitchMastAssembly ocs_switch_mast 装配级 builder: 按参数整棵重建开关柱
func buildOcsSwitchMastAssembly(params json.RawMessage, name string) (*Assembly, error) {
	var p SwitchMastParams
	if err := json.Unmarshal(params, &p); err != nil {
		return nil, fmt.Errorf("ocs_switch_mast: %w", err)
	}
	return CreateSwitchMastWithPlace(p, name)
}

func init() {
	RegisterAssemblyBuilder("ocs_switch_mast", buildOcsSwitchMastAssembly)
}
