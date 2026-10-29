package topo

import (
	"encoding/json"
	"fmt"
	"math"
	"sort"
	"strings"
)

// =========================================================================
// 锚段布局数据: 辅助算法生成 → 可序列化存库/前端编辑 → 确定性再生成
//   ComputeAnchorSectionLayout    纯计算, 输出全部中间数据 (柱位/悬挂点/弛度/吊弦表)
//   CreateAnchorSectionFromLayout 由布局确定性生成装配, 子件全部挂参数化配方
//   单位: 长度 mm, 里程 m; 支柱局部约定: 原点=柱底中心, +X 指向线路 (Direction)
// =========================================================================

// AnchorSectionSpec 锚段输入参数 (AnchorSectionInput 的可序列化形式)
type AnchorSectionSpec struct {
	Centerline      [][3]float64   `json:"centerline"`         // 线路中心线
	ContactHeight   float64        `json:"contactHeight"`      // 导高, 默认 5300
	StructureHeight float64        `json:"structureHeight"`    // 结构高度, 默认 1400
	SpanLength      float64        `json:"spanLength"`         // 标准跨距, 默认 50000
	MastHeight      float64        `json:"mastHeight"`         // 柱高, 默认 8000
	MastType        int            `json:"mastType"`           // 1-钢柱, 2-混凝土柱
	SideOffset      float64        `json:"sideOffset"`         // 侧面限界 CX, 默认 2900
	MastSide        float64        `json:"mastSide"`           // 支柱在线路左侧(+1)/右侧(-1), 默认 +1
	HasCompensator  bool           `json:"hasCompensator"`     // 两端锚柱设补偿装置
	ContactWireDia  float64        `json:"contactWireDia"`     // 接触线直径, 默认 12.9
	MessengerDia    float64        `json:"messengerDia"`       // 承力索直径, 默认 13.5
	DropperSpacing  float64        `json:"dropperSpacing"`     // 吊弦间距, 默认 8000
	AuxWires        []AuxWireInput `json:"auxWires,omitempty"` // 附加导线配置
}

// AnchorAuxWireLayout 一条附加导线的布局: 沿线折线 (支柱里程处采样, 几何方向跟随线路)
type AnchorAuxWireLayout struct {
	Input  AuxWireInput `json:"input"`
	Points [][3]float64 `json:"points"`
}

// AnchorMastLayout 单根支柱的布局数据
type AnchorMastLayout struct {
	Mileage        float64    `json:"mileage"`        // 里程 (m)
	Position       [3]float64 `json:"position"`       // 柱底中心 (世界坐标)
	Direction      [3]float64 `json:"direction"`      // 支柱朝向 (+X 指向线路, 水平单位向量)
	MastHeight     float64    `json:"mastHeight"`     // 柱高
	ContactWireZ   float64    `json:"contactWireZ"`   // 接触线相对轨面高
	MessengerWireZ float64    `json:"messengerWireZ"` // 承力索相对轨面高
	Stagger        float64    `json:"stagger"`        // 拉出值 (线路左侧为正)
	IsTensionMast  bool       `json:"isTensionMast"`  // 是否锚端柱 (带补偿装置)
	Role           string     `json:"role,omitempty"` // 支柱角色: anchor=锚柱 / intermediate=中间柱(非锚柱)
	ContactPoint   [3]float64 `json:"contactPoint"`   // 接触线悬挂点 (世界坐标, 由 position/direction/stagger 推导的缓存)
	MessengerPoint [3]float64 `json:"messengerPoint"` // 承力索悬挂点 (同上)
}

// AnchorDropperLayout 单根吊弦: T 为跨内参数 (0,1), Top/Bottom/Length 为计算缓存
// 再生成时按 T + 所在跨两端悬挂点/弛度重算, 编辑柱位/拉出值后吊弦自动跟随
type AnchorDropperLayout struct {
	T      float64    `json:"t"`
	Top    [3]float64 `json:"top"`    // 承力索侧挂点
	Bottom [3]float64 `json:"bottom"` // 接触线侧挂点
	Length float64    `json:"length"`
}

// AnchorSpanLayout 相邻两柱间一跨的布局数据
type AnchorSpanLayout struct {
	FromMast     int                   `json:"fromMast"`     // 起始柱索引
	ToMast       int                   `json:"toMast"`       // 终止柱索引
	Length       float64               `json:"length"`       // 跨距 (接触线悬挂点间距)
	ContactSag   float64               `json:"contactSag"`   // 接触线弛度
	MessengerSag float64               `json:"messengerSag"` // 承力索弛度
	Droppers     []AnchorDropperLayout `json:"droppers"`     // 空则再生成时按 Spec.DropperSpacing 自动布置
}

// AnchorSectionLayout 生成一个锚段所需的全部中间数据
type AnchorSectionLayout struct {
	Spec     AnchorSectionSpec     `json:"spec"`
	Masts    []AnchorMastLayout    `json:"masts"`
	Spans    []AnchorSpanLayout    `json:"spans"`
	AuxWires []AnchorAuxWireLayout `json:"auxWires,omitempty"` // 附加导线 (可选配置)
}

// ToJSON 序列化布局, 供存库/发前端编辑
func (l *AnchorSectionLayout) ToJSON() ([]byte, error) {
	return json.Marshal(l)
}

// AnchorSectionLayoutFromJSON 反序列化布局
func AnchorSectionLayoutFromJSON(data []byte) (*AnchorSectionLayout, error) {
	var l AnchorSectionLayout
	if err := json.Unmarshal(data, &l); err != nil {
		return nil, fmt.Errorf("ocs anchor: invalid layout JSON: %w", err)
	}
	return &l, nil
}

// 输入缺省值归一 (与历史 CreateAnchorSection 行为一致)
func normalizeAnchorInput(in AnchorSectionInput) AnchorSectionInput {
	if in.ContactHeight <= 0 {
		in.ContactHeight = 5300
	}
	if in.StructureHeight <= 0 {
		in.StructureHeight = 1400
	}
	if in.SpanLength <= 0 {
		in.SpanLength = 50000
	}
	if in.MastHeight <= 0 {
		in.MastHeight = 8000
	}
	if in.SideOffset <= 0 {
		in.SideOffset = 2900
	}
	if in.MastSide == 0 {
		in.MastSide = 1
	}
	if in.ContactWireDia <= 0 {
		in.ContactWireDia = 12.9
	}
	if in.MessengerDia <= 0 {
		in.MessengerDia = 13.5
	}
	if in.DropperSpacing <= 0 {
		in.DropperSpacing = 8000
	}
	return in
}

// ComputeAnchorSectionLayout 由输入纯计算锚段布局, 无副作用
// 柱位来自 CalcOcsSpanPositions; 弛度 = 标准跨距 × {0.0005 接触线, 0.015 承力索};
// 吊弦按 DropperSpacing 等分布置, 长度 = 两索抛物线弧垂差 (长度 <100 的跳过)
func ComputeAnchorSectionLayout(in AnchorSectionInput) (*AnchorSectionLayout, error) {
	if len(in.Centerline) < 2 {
		return nil, errInvalidInput("centerline needs >= 2 points")
	}
	in = normalizeAnchorInput(in)

	// 拉出值缺省时自动之字 ±300
	if len(in.StaggerTable) == 0 {
		totalLen := polyArcLens(in.Centerline)
		n := int(totalLen[len(totalLen)-1]/in.SpanLength) + 2
		in.StaggerTable = make([]float64, n)
		for i := range in.StaggerTable {
			if i%2 == 0 {
				in.StaggerTable[i] = 300
			} else {
				in.StaggerTable[i] = -300
			}
		}
	}
	span := CalcOcsSpanPositions(OcsSpanInput{
		Centerline:      in.Centerline,
		ContactHeight:   in.ContactHeight,
		StructureHeight: in.StructureHeight,
		StaggerTable:    in.StaggerTable,
		SpanLength:      in.SpanLength,
		MastHeight:      in.MastHeight,
		HasCompensator:  in.HasCompensator,
	})
	if span.MastCount == 0 {
		return nil, errInvalidInput("no mast positions computed")
	}

	cl := make([][3]float64, len(in.Centerline))
	for i, p := range in.Centerline {
		cl[i] = p.Data()
	}
	spec := AnchorSectionSpec{
		Centerline:      cl,
		ContactHeight:   in.ContactHeight,
		StructureHeight: in.StructureHeight,
		SpanLength:      in.SpanLength,
		MastHeight:      in.MastHeight,
		MastType:        in.MastType,
		SideOffset:      in.SideOffset,
		MastSide:        in.MastSide,
		HasCompensator:  in.HasCompensator,
		ContactWireDia:  in.ContactWireDia,
		MessengerDia:    in.MessengerDia,
		DropperSpacing:  in.DropperSpacing,
		AuxWires:        in.AuxWires,
	}
	layout := &AnchorSectionLayout{Spec: spec}

	side := in.MastSide
	for _, m := range span.Masts {
		f := frameAt(in.Centerline, m.Mileage*1000) // 里程 m → mm
		perp := [3]float64{f.perp[0] * side, f.perp[1] * side, 0}
		cp := f.pos.Data()
		role := MastRoleIntermediate
		if m.IsTensionMast {
			role = MastRoleAnchor
		}
		ml := AnchorMastLayout{
			Mileage:        m.Mileage,
			Position:       [3]float64{cp[0] + perp[0]*in.SideOffset, cp[1] + perp[1]*in.SideOffset, cp[2]},
			Direction:      [3]float64{-perp[0], -perp[1], 0}, // +X 指向线路
			MastHeight:     m.MastHeight,
			ContactWireZ:   m.ContactWireZ,
			MessengerWireZ: m.MessengerWireZ,
			Stagger:        m.Stagger,
			IsTensionMast:  m.IsTensionMast,
			Role:           role.String(),
		}
		ml.ContactPoint, ml.MessengerPoint = mastWirePoints(ml, in.SideOffset)
		layout.Masts = append(layout.Masts, ml)
	}

	// 跨: 弛度 + 吊弦表
	sagC := in.SpanLength * 0.0005 // 接触线预留弛度
	sagM := in.SpanLength * 0.015  // 承力索弛度
	for i := 0; i+1 < len(layout.Masts); i++ {
		cw0, cw1 := layout.Masts[i].ContactPoint, layout.Masts[i+1].ContactPoint
		mw0, mw1 := layout.Masts[i].MessengerPoint, layout.Masts[i+1].MessengerPoint
		sp := AnchorSpanLayout{
			FromMast:     i,
			ToMast:       i + 1,
			Length:       dist3(cw0, cw1),
			ContactSag:   sagC,
			MessengerSag: sagM,
		}
		n := int(sp.Length / in.DropperSpacing)
		if n < 1 {
			n = 1
		}
		for k := 1; k <= n; k++ {
			t := float64(k) / float64(n+1)
			top := evalSagPoint3(mw0, mw1, t, sagM)
			bot := evalSagPoint3(cw0, cw1, t, sagC)
			l := top[2] - bot[2]
			if l < 100 {
				continue
			}
			sp.Droppers = append(sp.Droppers, AnchorDropperLayout{T: t, Top: top, Bottom: bot, Length: l})
		}
		layout.Spans = append(layout.Spans, sp)
	}

	// 附加导线: 沿线折线, ≤10m 密采样 (消除直弦折角) 并并入支柱里程
	for _, aux := range layout.Spec.AuxWires {
		a := aux
		a.withDefaults(in.MastSide)
		aw := AnchorAuxWireLayout{Input: a}
		accM := polyArcLens(in.Centerline)
		total := accM[len(accM)-1] / 1000.0 // m
		mile := []float64{0}
		for x := 10000.0; x < total*1000; x += 10000 {
			mile = append(mile, x/1000)
		}
		mile = append(mile, total)
		for _, m := range span.Masts {
			mile = append(mile, m.Mileage)
		}
		sort.Float64s(mile)
		for _, mg := range mile {
			f := frameAt(in.Centerline, mg*1000)
			perp := [3]float64{f.perp[0] * a.Side, f.perp[1] * a.Side, 0}
			c := f.pos.Data()
			aw.Points = append(aw.Points, [3]float64{
				c[0] + perp[0]*a.Offset, c[1] + perp[1]*a.Offset, a.Height})
		}
		layout.AuxWires = append(layout.AuxWires, aw)
	}
	return layout, nil
}

// CreateAnchorSectionFromLayout 由布局确定性生成锚段装配 (铁路专业层级):
//
//	anchor_section (锚段)
//	├── mast_i    支柱装置 (柱+腕臂+定位[+补偿], ocs_mast 配方, Location 放置)
//	└── span_i    跨距子装配 (ocs_span 配方可整棵重建)
//	    ├── cw_i / mw_i        跨间接触线/承力索 (叶片配方)
//	    └── dropper_i_k        吊弦 (叶片配方)
//
// 全局地图编辑作用于 mast_i / span_i 粒度; 金具/线索零件只在 span 内展开。
// 支柱局部生成 + Location 放置 (可 SetLocation 移动单柱); 线索/吊弦世界坐标烘焙,
// 每个节点挂参数化配方, 支持 ExportParametric → RebuildFromParametric 往返。
func CreateAnchorSectionFromLayout(layout *AnchorSectionLayout) (*Assembly, error) {
	if layout == nil || len(layout.Masts) == 0 {
		return nil, errInvalidInput("layout has no masts")
	}
	spec := layout.Spec
	// 布局可能被手工编辑过, 缺省值再兜底一次
	if spec.ContactHeight <= 0 {
		spec.ContactHeight = 5300
	}
	if spec.StructureHeight <= 0 {
		spec.StructureHeight = 1400
	}
	if spec.SpanLength <= 0 {
		spec.SpanLength = 50000
	}
	if spec.MastHeight <= 0 {
		spec.MastHeight = 8000
	}
	if spec.SideOffset <= 0 {
		spec.SideOffset = 2900
	}
	if spec.MastSide == 0 {
		spec.MastSide = 1
	}
	if spec.ContactWireDia <= 0 {
		spec.ContactWireDia = 12.9
	}
	if spec.MessengerDia <= 0 {
		spec.MessengerDia = 13.5
	}
	if spec.DropperSpacing <= 0 {
		spec.DropperSpacing = 8000
	}

	// 根容器: 占位 vertex 放在首末柱中点 (容器节点无几何, vertex 不得污染全局 bbox)
	root := NewAssembly(NewAssemblyObjectFromShpe(*NewVertex(
		(layout.Masts[0].Position[0]+layout.Masts[len(layout.Masts)-1].Position[0])/2,
		(layout.Masts[0].Position[1]+layout.Masts[len(layout.Masts)-1].Position[1])/2,
		(layout.Masts[0].Position[2]+layout.Masts[len(layout.Masts)-1].Position[2])/2).ToShape()),
		nil, "anchor_section", nil)
	addShape := func(s *Shape, loc *TopoLocation, name string, data *ParametricData) {
		if s == nil || s.IsNull() {
			return
		}
		root.AddObjectParams(NewAssemblyObjectFromShpe(*s), loc, name, nil, data)
	}

	// 支柱装置: 局部生成 (原点=柱底中心, +X 指向线路) + Location 放置
	for i, m := range layout.Masts {
		role := MastRoleIntermediate
		if m.Role == MastRoleAnchor.String() {
			role = MastRoleAnchor
		} else if m.IsTensionMast && m.Role == "" {
			role = MastRoleAnchor
		}
		mp := MastAssemblyParams{
			MastType:        spec.MastType,
			MastHeight:      m.MastHeight,
			CantileverType:  1,
			ArmDiameter:     60,
			Stagger:         m.Stagger * spec.MastSide, // 局部 X 朝线路, 拉出值换算
			CompType:        0,
			ContactHeight:   spec.ContactHeight,
			StructureHeight: spec.StructureHeight,
			SideOffset:      spec.SideOffset,
		}
		if role == MastRoleAnchor && spec.HasCompensator {
			mp.CompType = 1
			mp.HasGuyWire = true
			mp.RatedTension = 15
			// 张力平面 (坠砣/下锚支) 朝锚段内侧, 拉线自动布在对侧顺线路
			interior := [3]float64{1, 0, 0}
			if i == len(layout.Masts)-1 {
				interior = [3]float64{-1, 0, 0}
			} else if i+1 < len(layout.Masts) {
				a, b := m.Position, layout.Masts[i+1].Position
				d := [3]float64{b[0] - a[0], b[1] - a[1], 0}
				n := math.Hypot(d[0], d[1])
				if n > 1e-9 {
					interior = [3]float64{d[0] / n, d[1] / n, 0}
				}
			}
			mp.TensionPlaneY = anchorTensionPlaneY(m, interior)
		}
		loc := NewTopoLocation(mastPlacementTrsf(m))
		addShape(CreateMastAssembly(mp), loc, "mast_"+itoa(i), mastParametricWithRole(mp, role))
	}

	// 跨距子装配: 线索 + 吊弦按跨分组, 跨粒度可编辑/重建
	for i, sp := range layout.Spans {
		if sp.FromMast < 0 || sp.ToMast >= len(layout.Masts) || sp.FromMast >= sp.ToMast {
			return nil, errInvalidInput(fmt.Sprintf("span %d references invalid masts [%d,%d]", i, sp.FromMast, sp.ToMast))
		}
		fm, tm := layout.Masts[sp.FromMast], layout.Masts[sp.ToMast]
		cw0, _ := mastWirePoints(fm, spec.SideOffset)
		cw1, _ := mastWirePoints(tm, spec.SideOffset)
		_, mw0 := mastWirePoints(fm, spec.SideOffset)
		_, mw1 := mastWirePoints(tm, spec.SideOffset)

		// 吊弦 T 表: 布局未给时按间距自动布置
		droppers := sp.Droppers
		if len(droppers) == 0 {
			n := int(dist3(cw0, cw1) / spec.DropperSpacing)
			if n < 1 {
				n = 1
			}
			droppers = make([]AnchorDropperLayout, 0, n)
			for k := 1; k <= n; k++ {
				droppers = append(droppers, AnchorDropperLayout{T: float64(k) / float64(n+1)})
			}
		}
		ts := make([]float64, 0, len(droppers))
		for _, d := range droppers {
			ts = append(ts, d.T)
		}

		recipe := ocsSpanRecipe{
			Contact:   ocsSpanWire{Diameter: spec.ContactWireDia, BottomRadius: 8, TopRadius: 3, Sag: sp.ContactSag, Start: cw0, End: cw1},
			Messenger: ocsSpanWire{Diameter: spec.MessengerDia, Sag: sp.MessengerSag, Start: mw0, End: mw1},
			Droppers:  ts,
		}
		// 端锚下引: 首跨起点端 / 末跨终点端, 锚柱处接触线/承力索下锚至柱身
		if i == 0 && layout.Masts[0].Role == MastRoleAnchor.String() {
			recipe.AnchorDrop = 1
			recipe.DropDir = [3]float64{-layout.Masts[0].Direction[0], -layout.Masts[0].Direction[1], 0}
		}
		if i == len(layout.Spans)-1 && layout.Masts[len(layout.Masts)-1].Role == MastRoleAnchor.String() {
			recipe.AnchorDrop = 2
			recipe.DropDir = [3]float64{-layout.Masts[len(layout.Masts)-1].Direction[0], -layout.Masts[len(layout.Masts)-1].Direction[1], 0}
		}
		span, err := buildOcsSpan(recipe, "span_"+itoa(i))
		if err != nil {
			return nil, err
		}
		span.SetParametric(&ParametricData{Type: "ocs_span", Params: mustJSON(recipe)})

		root.AddAssembly(span, nil, span.GetName(), nil)
		if root.HasError() {
			return nil, errInvalidInput("add span: " + root.Error())
		}
	}

	// 附加导线 (AF/回流线/加强线): 沿线分段弛度放样 + 支柱附加导线支架
	for _, aux := range layout.AuxWires {
		a := aux.Input
		kind := strings.ToLower(a.Kind)
		if kind == "" {
			kind = "af"
		}
		for k := 0; k+1 < len(aux.Points); k++ {
			p0, p1 := aux.Points[k], aux.Points[k+1]
			if dist3(p0, p1) < 100 {
				continue
			}
			wp := AuxiliaryWireParams{Diameter: a.Diameter, Sag: dist3(p0, p1) * a.SagRatio}
			s := CreateAuxiliaryWire(wp, NewPoint3(p0), NewPoint3(p1))
			if s == nil || s.IsNull() {
				continue
			}
			root.AddObjectParams(NewAssemblyObjectFromShpe(*s), nil,
				fmt.Sprintf("aux_wire_%s_%d", kind, k), nil,
				&ParametricData{Type: "ocs_aux_wire", Params: mustJSON(ocsWireRecipe{
					Diameter: a.Diameter, Sag: wp.Sag, Start: p0, End: p1})})
		}
		// 附加导线支架: 管臂 (水平管+斜撑) 对位柱位处导线采样点;
		// 弃用 CROSS_ARM 实心箱梁 (视觉为异常大板), 配方与 buildOcsAuxBracket 同构
		if a.Bracket {
			for i := range layout.Masts {
				m := layout.Masts[i]
				bestD, wirePt := math.MaxFloat64, [3]float64{}
				for _, pt := range aux.Points {
					// 平面距离 (柱位 z=轨面, 导线采样点 z=悬挂高, 不可比 3D)
					dx, dy := pt[0]-m.Position[0], pt[1]-m.Position[1]
					if d := math.Hypot(dx, dy); d < bestD {
						bestD, wirePt = d, pt
					}
				}
				if bestD > 3000 {
					continue // 柱位处无附加导线采样
				}
				shapes, dir, armLen := afBracketBuild(m, wirePt, a.Height)
				if len(shapes) == 0 {
					continue
				}
				comp := TopoCompoundMake(shapes).ToShape()
				if comp == nil || comp.IsNull() {
					continue
				}
				recipe := ocsAuxBracketRecipe{
					Params:   AuxBracketParams{OverhangLength: armLen, MountHeight: a.Height},
					Position: m.Position,
					Normal:   [3]float64{-dir[0], -dir[1], 0}, // 臂指向 (背离线路, 重建时取反还原)
				}
				root.AddObjectParams(NewAssemblyObjectFromShpe(*comp), nil,
					fmt.Sprintf("aux_bracket_%s_%d", kind, i), nil,
					&ParametricData{Type: "ocs_aux_bracket", Params: mustJSON(recipe)})
			}
		}
	}
	return root, nil
}

// buildOcsSpan 由跨距配方生成跨距子装配 (ocs_span 装配级 builder)
// 叶片命名 cw_i / mw_i / dropper_i_k (i 为跨号, 保持全局唯一约定)
func buildOcsSpan(recipe ocsSpanRecipe, name string) (*Assembly, error) {
	// 容器占位 vertex 放在接触线中点 (不得污染全局 bbox)
	span := NewAssembly(NewAssemblyObjectFromShpe(*NewVertex(
		(recipe.Contact.Start[0]+recipe.Contact.End[0])/2,
		(recipe.Contact.Start[1]+recipe.Contact.End[1])/2,
		(recipe.Contact.Start[2]+recipe.Contact.End[2])/2).ToShape()), nil, name, nil)
	add := func(s *Shape, leaf string, data *ParametricData) {
		if s == nil || s.IsNull() {
			return
		}
		span.AddObjectParams(NewAssemblyObjectFromShpe(*s), nil, leaf, nil, data)
	}
	// 叶片名沿用历史约定 cw_i / mw_i / dropper_i_k (i 为跨号, name 形如 span_i)
	idx := name
	if k := strings.LastIndex(name, "_"); k >= 0 && k+1 < len(name) {
		idx = name[k+1:]
	}
	cwp := ContactWireParams{Diameter: recipe.Contact.Diameter, BottomRadius: recipe.Contact.BottomRadius,
		TopRadius: recipe.Contact.TopRadius, Sag: recipe.Contact.Sag}
	add(CreateContactWire(cwp, NewPoint3(recipe.Contact.Start), NewPoint3(recipe.Contact.End)),
		"cw_"+idx, contactWireParametric(cwp, recipe.Contact.Start, recipe.Contact.End))
	mwp := MessengerWireParams{Diameter: recipe.Messenger.Diameter, Sag: recipe.Messenger.Sag}
	add(CreateMessengerWire(mwp, NewPoint3(recipe.Messenger.Start), NewPoint3(recipe.Messenger.End)),
		"mw_"+idx, messengerWireParametric(mwp, recipe.Messenger.Start, recipe.Messenger.End))

	for k, t := range recipe.Droppers {
		top := evalSagPoint3(recipe.Messenger.Start, recipe.Messenger.End, t, recipe.Messenger.Sag)
		bot := evalSagPoint3(recipe.Contact.Start, recipe.Contact.End, t, recipe.Contact.Sag)
		l := top[2] - bot[2]
		if l < 100 {
			continue
		}
		dp := DropperParams{Length: l, WireDiameter: 4.5, ClampLength: 60, ClampWidth: 40, ClampThickness: 6, Conductive: true}
		leaf := "dropper_" + idx + "_" + itoa(k)
		add(CreateDropperWithPlace(dp, NewPoint3(top), NewDir3FromXYZ([3]float64{0, 0, 1})),
			leaf, dropperParametric(dp, top))
	}

	// 端锚下引线 (锚段首/末跨): 悬挂点 → 柱身下锚点 (方向 DropDir, 抬升 500)
	if recipe.AnchorDrop == 1 || recipe.AnchorDrop == 2 {
		var hp, wp [3]float64
		if recipe.AnchorDrop == 1 {
			hp, wp = recipe.Contact.Start, recipe.Messenger.Start
		} else {
			hp, wp = recipe.Contact.End, recipe.Messenger.End
		}
		dv := [3]float64{recipe.DropDir[0] * 250, recipe.DropDir[1] * 250, 500}
		cEnd := [3]float64{hp[0] + dv[0], hp[1] + dv[1], hp[2] + dv[2]}
		mEnd := [3]float64{wp[0] + dv[0], wp[1] + dv[1], wp[2] + dv[2]}
		cwp := ContactWireParams{Diameter: recipe.Contact.Diameter, BottomRadius: 8,
			TopRadius: recipe.Contact.TopRadius, Sag: 60}
		add(CreateContactWire(cwp, NewPoint3(hp), NewPoint3(cEnd)), "anchor_drop_cw_"+idx,
			contactWireParametric(cwp, hp, cEnd))
		mwp := MessengerWireParams{Diameter: recipe.Messenger.Diameter, Sag: 60}
		add(CreateMessengerWire(mwp, NewPoint3(wp), NewPoint3(mEnd)), "anchor_drop_mw_"+idx,
			messengerWireParametric(mwp, wp, mEnd))
	}
	return span, nil
}

// anchorTensionPlaneY 锚柱张力平面 (坠砣/下锚支) 的局部 Y:
// 张力平面朝锚段内部一侧 (局部 +Y 系 Direction 的左侧像 (−dy,dx)), 拉线布对侧
func anchorTensionPlaneY(m AnchorMastLayout, interior [3]float64) float64 {
	ly := [3]float64{-m.Direction[1], m.Direction[0], 0}
	if ly[0]*interior[0]+ly[1]*interior[1] >= 0 {
		return 250
	}
	return -250
}

// 由柱位推导接触线/承力索悬挂点: 线路中心 = 柱位 + direction*CX, 悬挂点再向线路侧偏移 stagger
func mastWirePoints(m AnchorMastLayout, sideOffset float64) (contact, messenger [3]float64) {
	d := m.Direction
	off := sideOffset - m.Stagger
	contact = [3]float64{m.Position[0] + d[0]*off, m.Position[1] + d[1]*off, m.Position[2] + m.ContactWireZ}
	messenger = [3]float64{m.Position[0] + d[0]*off, m.Position[1] + d[1]*off, m.Position[2] + m.MessengerWireZ}
	return
}

// 支柱放置变换: 局部 +X → Direction (水平), +Z → 世界 +Z, 平移到柱底中心
// Trsf 12 分量行优先, 平移在 [3] [7] [11]
func mastPlacementTrsf(m AnchorMastLayout) Trsf {
	dx, dy := 1.0, 0.0
	if l := math.Hypot(m.Direction[0], m.Direction[1]); l > 1e-9 {
		dx, dy = m.Direction[0]/l, m.Direction[1]/l
	}
	return NewTrsf(dx, -dy, 0, m.Position[0],
		dy, dx, 0, m.Position[1],
		0, 0, 1, m.Position[2])
}

// 两点连线上 t 处 + 抛物线弛度
func evalSagPoint3(p0, p1 [3]float64, t, sag float64) [3]float64 {
	return [3]float64{
		p0[0] + (p1[0]-p0[0])*t,
		p0[1] + (p1[1]-p0[1])*t,
		p0[2] + (p1[2]-p0[2])*t - 4*sag*t*(1-t),
	}
}

func dist3(a, b [3]float64) float64 {
	dx, dy, dz := b[0]-a[0], b[1]-a[1], b[2]-a[2]
	return math.Sqrt(dx*dx + dy*dy + dz*dz)
}

// =========================================================================
// 参数化配方: ExportParametric → RebuildFromParametric 闭环
// =========================================================================

type ocsMastRecipe struct {
	Params MastAssemblyParams `json:"params"`
	Role   string             `json:"role,omitempty"` // 支柱角色: anchor/intermediate (非锚柱)
}

type ocsWireRecipe struct {
	Diameter     float64    `json:"diameter"`
	BottomRadius float64    `json:"bottomRadius,omitempty"` // 仅接触线
	TopRadius    float64    `json:"topRadius,omitempty"`    // 仅接触线
	Sag          float64    `json:"sag"`
	Start        [3]float64 `json:"start"`
	End          [3]float64 `json:"end"`
}

type ocsDropperRecipe struct {
	Params    DropperParams `json:"params"`
	Top       [3]float64    `json:"top"` // 承力索侧挂点 (世界坐标)
	Direction [3]float64    `json:"direction"`
}

func mastParametric(mp MastAssemblyParams) *ParametricData {
	raw, _ := json.Marshal(ocsMastRecipe{Params: mp})
	return &ParametricData{Type: "ocs_mast", Params: raw}
}

func mastParametricWithRole(mp MastAssemblyParams, role MastRole) *ParametricData {
	raw, _ := json.Marshal(ocsMastRecipe{Params: mp, Role: role.String()})
	return &ParametricData{Type: "ocs_mast", Params: raw}
}

// ocsSpanWire 跨内单条线索的几何/参数 (两点端点 + 弛度即编辑数据)
type ocsSpanWire struct {
	Diameter     float64    `json:"diameter"`
	BottomRadius float64    `json:"bottomRadius,omitempty"` // 仅接触线
	TopRadius    float64    `json:"topRadius,omitempty"`    // 仅接触线
	Sag          float64    `json:"sag"`
	Start        [3]float64 `json:"start"`
	End          [3]float64 `json:"end"`
}

// ocsSpanRecipe 跨距配方: 前端在跨粒度编辑 (改弛度/吊弦 T 表后整跨重建)
type ocsSpanRecipe struct {
	Contact    ocsSpanWire `json:"contact"`
	Messenger  ocsSpanWire `json:"messenger"`
	Droppers   []float64   `json:"droppers"`             // 跨内 T 表
	AnchorDrop int         `json:"anchorDrop,omitempty"` // 0=无 1=起点端下锚(跨距为锚段首跨) 2=终点端下锚(末跨)
	DropDir    [3]float64  `json:"dropDir,omitempty"`    // 下锚方向 (指向锚柱柱身)
}

func mustJSON(v any) json.RawMessage {
	raw, err := json.Marshal(v)
	if err != nil {
		panic(fmt.Sprintf("topo: marshal parametric recipe: %v", err))
	}
	return raw
}

func contactWireParametric(p ContactWireParams, start, end [3]float64) *ParametricData {
	raw, _ := json.Marshal(ocsWireRecipe{
		Diameter: p.Diameter, BottomRadius: p.BottomRadius, TopRadius: p.TopRadius,
		Sag: p.Sag, Start: start, End: end,
	})
	return &ParametricData{Type: "ocs_contact_wire", Params: raw}
}

func messengerWireParametric(p MessengerWireParams, start, end [3]float64) *ParametricData {
	raw, _ := json.Marshal(ocsWireRecipe{Diameter: p.Diameter, Sag: p.Sag, Start: start, End: end})
	return &ParametricData{Type: "ocs_messenger_wire", Params: raw}
}

func dropperParametric(p DropperParams, top [3]float64) *ParametricData {
	raw, _ := json.Marshal(ocsDropperRecipe{Params: p, Top: top, Direction: [3]float64{0, 0, 1}})
	return &ParametricData{Type: "ocs_dropper", Params: raw}
}

func buildOcsMast(params json.RawMessage) (*Shape, *TopoLocation, error) {
	var r ocsMastRecipe
	if err := json.Unmarshal(params, &r); err != nil {
		return nil, nil, fmt.Errorf("ocs_mast: %w", err)
	}
	s := CreateMastAssembly(r.Params)
	if s == nil || s.IsNull() {
		return nil, nil, errInvalidInput("ocs_mast: build failed")
	}
	return s, nil, nil // 放置由节点 location 提供
}

func buildOcsContactWire(params json.RawMessage) (*Shape, *TopoLocation, error) {
	var r ocsWireRecipe
	if err := json.Unmarshal(params, &r); err != nil {
		return nil, nil, fmt.Errorf("ocs_contact_wire: %w", err)
	}
	s := CreateContactWire(ContactWireParams{
		Diameter: r.Diameter, BottomRadius: r.BottomRadius, TopRadius: r.TopRadius, Sag: r.Sag,
	}, NewPoint3(r.Start), NewPoint3(r.End))
	if s == nil || s.IsNull() {
		return nil, nil, errInvalidInput("ocs_contact_wire: build failed")
	}
	return s, nil, nil
}

func buildOcsMessengerWire(params json.RawMessage) (*Shape, *TopoLocation, error) {
	var r ocsWireRecipe
	if err := json.Unmarshal(params, &r); err != nil {
		return nil, nil, fmt.Errorf("ocs_messenger_wire: %w", err)
	}
	s := CreateMessengerWire(MessengerWireParams{Diameter: r.Diameter, Sag: r.Sag}, NewPoint3(r.Start), NewPoint3(r.End))
	if s == nil || s.IsNull() {
		return nil, nil, errInvalidInput("ocs_messenger_wire: build failed")
	}
	return s, nil, nil
}

func buildOcsDropper(params json.RawMessage) (*Shape, *TopoLocation, error) {
	var r ocsDropperRecipe
	if err := json.Unmarshal(params, &r); err != nil {
		return nil, nil, fmt.Errorf("ocs_dropper: %w", err)
	}
	dir := r.Direction
	if dir == [3]float64{} {
		dir = [3]float64{0, 0, 1}
	}
	s := CreateDropperWithPlace(r.Params, NewPoint3(r.Top), NewDir3FromXYZ(dir))
	if s == nil || s.IsNull() {
		return nil, nil, errInvalidInput("ocs_dropper: build failed")
	}
	return s, nil, nil
}

// buildOcsSpanAssembly ocs_span 装配级 builder: 按跨距配方整棵重建跨距子装配
func buildOcsSpanAssembly(params json.RawMessage, name string) (*Assembly, error) {
	var r ocsSpanRecipe
	if err := json.Unmarshal(params, &r); err != nil {
		return nil, fmt.Errorf("ocs_span: %w", err)
	}
	return buildOcsSpan(r, name)
}

// afBracketBuild 柱位附加导线支架臂: 臂指向柱位处导线采样点 wirePt (水平),
// 返回 (shapes, 臂指向, 臂长) — 配方存 dir 取反/臂长, 重建经 auxBracketArmShapes 同构还原
func afBracketBuild(m AnchorMastLayout, wirePt [3]float64, height float64) ([]Shape, [3]float64, float64) {
	hv := [3]float64{wirePt[0] - m.Position[0], wirePt[1] - m.Position[1], 0}
	full := math.Hypot(hv[0], hv[1])
	if full < 450 { // 150 臂根 + 300 最短臂
		return nil, [3]float64{}, 0
	}
	dir := [3]float64{hv[0] / full, hv[1] / full, 0}
	armLen := full - 150 // 臂根 = 柱位沿臂指向 150mm (柱面)
	return auxBracketArmShapes(m.Position, dir, armLen, height), dir, armLen
}

// auxBracketArmShapes 附加导线管臂 (水平管+斜撑):
// 水平管自臂根 (pos + dir*150, 高 h-30) 伸至臂长 l, 斜撑自臂根下方 720mm 处
// 按真实三维对角方向撑至水平管 60% 处 (方向必须携带 z 分量 — slant cantilever
// 的放置重载倾角全靠 axisDirection, 给水平向量会退化成与主臂平行的第二根横管)
func auxBracketArmShapes(pos, dir [3]float64, l, h float64) []Shape {
	if l < 300 {
		return nil
	}
	upper := [3]float64{pos[0] + dir[0]*150, pos[1] + dir[1]*150, h - 30}
	lower := [3]float64{pos[0] + dir[0]*150, pos[1] + dir[1]*150, h - 720}
	shapes := []Shape{
		*CreateLevelCantileverWithPlace(
			LevelCantileverParams{Length: l, OuterDiameter: 48, WallThickness: 4},
			NewPoint3(upper), NewDir3FromXYZ(dir), NewDir3FromXYZ([3]float64{0, 0, 1})),
	}
	jx, jy := upper[0]+dir[0]*l*0.6, upper[1]+dir[1]*l*0.6
	sv := [3]float64{jx - lower[0], jy - lower[1], upper[2] - lower[2]}
	sl := math.Hypot(sv[0], math.Hypot(sv[1], sv[2]))
	if sl > 300 {
		shapes = append(shapes, *CreateSlantCantileverWithPlace(
			SlantCantileverParams{Length: sl, OuterDiameter: 42, WallThickness: 3.5},
			NewPoint3(lower), NewDir3FromXYZ([3]float64{sv[0] / sl, sv[1] / sl, sv[2] / sl}),
			NewDir3FromXYZ([3]float64{0, 0, 1})))
	}
	return shapes
}

// ocsAuxBracketRecipe 附加导线支架配方 (管臂: 水平管+斜撑, 可整臂重建)
//   Position=柱位, Normal=臂指向取反 (背离线路), OverhangLength=臂长 (臂根至臂尖), MountHeight=悬挂高
type ocsAuxBracketRecipe struct {
	Params   AuxBracketParams `json:"params"`
	Position [3]float64       `json:"position"`
	Normal   [3]float64       `json:"normal"`
}

func buildOcsAuxWire(params json.RawMessage) (*Shape, *TopoLocation, error) {
	var r ocsWireRecipe
	if err := json.Unmarshal(params, &r); err != nil {
		return nil, nil, fmt.Errorf("ocs_aux_wire: %w", err)
	}
	s := CreateAuxiliaryWire(AuxiliaryWireParams{Diameter: r.Diameter, Sag: r.Sag},
		NewPoint3(r.Start), NewPoint3(r.End))
	if s == nil || s.IsNull() {
		return nil, nil, errInvalidInput("ocs_aux_wire: build failed")
	}
	return s, nil, nil
}

func buildOcsAuxBracket(params json.RawMessage) (*Shape, *TopoLocation, error) {
	var r ocsAuxBracketRecipe
	if err := json.Unmarshal(params, &r); err != nil {
		return nil, nil, fmt.Errorf("ocs_aux_bracket: %w", err)
	}
	// 管臂重建: 与生成路径 afBracketBuild → auxBracketArmShapes 同构
	dir := [3]float64{-r.Normal[0], -r.Normal[1], 0}
	if l := math.Hypot(dir[0], dir[1]); l > 1e-9 {
		dir[0], dir[1] = dir[0]/l, dir[1]/l
	} else {
		dir = [3]float64{1, 0, 0}
	}
	h := r.Params.MountHeight
	if h <= 0 {
		h = 8000
	}
	l := r.Params.OverhangLength
	if l <= 0 {
		l = 2100
	}
	shapes := auxBracketArmShapes(r.Position, dir, l, h)
	if len(shapes) == 0 {
		return nil, nil, errInvalidInput("ocs_aux_bracket: arm too short")
	}
	comp := TopoCompoundMake(shapes).ToShape()
	if comp == nil || comp.IsNull() {
		return nil, nil, errInvalidInput("ocs_aux_bracket: build failed")
	}
	return comp, nil, nil
}

func init() {
	RegisterParametricBuilder("ocs_mast", buildOcsMast)
	RegisterParametricBuilder("ocs_contact_wire", buildOcsContactWire)
	RegisterParametricBuilder("ocs_messenger_wire", buildOcsMessengerWire)
	RegisterParametricBuilder("ocs_dropper", buildOcsDropper)
	RegisterParametricBuilder("ocs_aux_wire", buildOcsAuxWire)
	RegisterParametricBuilder("ocs_aux_bracket", buildOcsAuxBracket)
	RegisterAssemblyBuilder("ocs_span", buildOcsSpanAssembly)
}
