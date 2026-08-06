package topo

import (
	"encoding/json"
	"fmt"
	"math"
)

// =========================================================================
// 锚段布局数据: 辅助算法生成 → 可序列化存库/前端编辑 → 确定性再生成
//   ComputeAnchorSectionLayout    纯计算, 输出全部中间数据 (柱位/悬挂点/弛度/吊弦表)
//   CreateAnchorSectionFromLayout 由布局确定性生成装配, 子件全部挂参数化配方
//   单位: 长度 mm, 里程 m; 支柱局部约定: 原点=柱底中心, +X 指向线路 (Direction)
// =========================================================================

// AnchorSectionSpec 锚段输入参数 (AnchorSectionInput 的可序列化形式)
type AnchorSectionSpec struct {
	Centerline      [][3]float64 `json:"centerline"`      // 线路中心线
	ContactHeight   float64      `json:"contactHeight"`   // 导高, 默认 5300
	StructureHeight float64      `json:"structureHeight"` // 结构高度, 默认 1400
	SpanLength      float64      `json:"spanLength"`      // 标准跨距, 默认 50000
	MastHeight      float64      `json:"mastHeight"`      // 柱高, 默认 8000
	MastType        int          `json:"mastType"`        // 1-钢柱, 2-混凝土柱
	SideOffset      float64      `json:"sideOffset"`      // 侧面限界 CX, 默认 2900
	MastSide        float64      `json:"mastSide"`        // 支柱在线路左侧(+1)/右侧(-1), 默认 +1
	HasCompensator  bool         `json:"hasCompensator"`  // 两端锚柱设补偿装置
	ContactWireDia  float64      `json:"contactWireDia"`  // 接触线直径, 默认 12.9
	MessengerDia    float64      `json:"messengerDia"`    // 承力索直径, 默认 13.5
	DropperSpacing  float64      `json:"dropperSpacing"`  // 吊弦间距, 默认 8000
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
	Spec  AnchorSectionSpec  `json:"spec"`
	Masts []AnchorMastLayout `json:"masts"`
	Spans []AnchorSpanLayout `json:"spans"`
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
	layout := &AnchorSectionLayout{
		Spec: AnchorSectionSpec{
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
		},
	}

	side := in.MastSide
	for _, m := range span.Masts {
		f := frameAt(in.Centerline, m.Mileage*1000) // 里程 m → mm
		perp := [3]float64{f.perp[0] * side, f.perp[1] * side, 0}
		cp := f.pos.Data()
		ml := AnchorMastLayout{
			Mileage:        m.Mileage,
			Position:       [3]float64{cp[0] + perp[0]*in.SideOffset, cp[1] + perp[1]*in.SideOffset, cp[2]},
			Direction:      [3]float64{-perp[0], -perp[1], 0}, // +X 指向线路
			MastHeight:     m.MastHeight,
			ContactWireZ:   m.ContactWireZ,
			MessengerWireZ: m.MessengerWireZ,
			Stagger:        m.Stagger,
			IsTensionMast:  m.IsTensionMast,
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
	return layout, nil
}

// CreateAnchorSectionFromLayout 由布局确定性生成锚段装配
// 根节点为 "anchor_section" 容器; 子件命名 mast_i / cw_i / mw_i / dropper_{span}_{idx}, 均唯一
// 支柱局部生成 + Location 放置 (可 SetLocation 移动单柱); 线索/吊弦世界坐标烘焙,
// 每个子件经 AddObjectParams 挂参数化配方, 支持 ExportParametric → RebuildFromParametric 往返
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

	// 根容器: 占位 vertex (空 compound 是 null shape, assembly 构造不接受), 自身不带配方
	root := NewAssembly(NewAssemblyObjectFromShpe(*NewVertex(0, 0, 0).ToShape()), nil, "anchor_section", nil)
	addShape := func(s *Shape, loc *TopoLocation, name string, data *ParametricData) {
		if s == nil || s.IsNull() {
			return
		}
		root.AddObjectParams(NewAssemblyObjectFromShpe(*s), loc, name, nil, data)
	}

	// 支柱: 局部生成 (原点=柱底中心, +X 指向线路) + Location 放置
	for i, m := range layout.Masts {
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
		if spec.HasCompensator && m.IsTensionMast {
			mp.CompType = 1
			mp.HasGuyWire = true
			mp.RatedTension = 15
		}
		loc := NewTopoLocation(mastPlacementTrsf(m))
		addShape(CreateMastAssembly(mp), loc, "mast_"+itoa(i), mastParametric(mp))
	}

	// 跨间线索 + 吊弦 (两点端点 + 弛度即编辑数据, 写入配方)
	cwp := ContactWireParams{Diameter: spec.ContactWireDia, BottomRadius: 8, TopRadius: 3}
	mwp := MessengerWireParams{Diameter: spec.MessengerDia}
	for i, sp := range layout.Spans {
		if sp.FromMast < 0 || sp.ToMast >= len(layout.Masts) || sp.FromMast >= sp.ToMast {
			return nil, errInvalidInput(fmt.Sprintf("span %d references invalid masts [%d,%d]", i, sp.FromMast, sp.ToMast))
		}
		fm, tm := layout.Masts[sp.FromMast], layout.Masts[sp.ToMast]
		cw0, _ := mastWirePoints(fm, spec.SideOffset)
		cw1, _ := mastWirePoints(tm, spec.SideOffset)
		_, mw0 := mastWirePoints(fm, spec.SideOffset)
		_, mw1 := mastWirePoints(tm, spec.SideOffset)

		cwp.Sag = sp.ContactSag
		addShape(CreateContactWire(cwp, NewPoint3(cw0), NewPoint3(cw1)), nil, "cw_"+itoa(i), contactWireParametric(cwp, cw0, cw1))
		mwp.Sag = sp.MessengerSag
		addShape(CreateMessengerWire(mwp, NewPoint3(mw0), NewPoint3(mw1)), nil, "mw_"+itoa(i), messengerWireParametric(mwp, mw0, mw1))

		// 吊弦: 布局未给表时按间距自动布置; 位置/长度按两端悬挂点 + 弛度重算
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
		for k, d := range droppers {
			top := evalSagPoint3(mw0, mw1, d.T, sp.MessengerSag)
			bot := evalSagPoint3(cw0, cw1, d.T, sp.ContactSag)
			l := top[2] - bot[2]
			if l < 100 {
				continue
			}
			dp := DropperParams{Length: l, WireDiameter: 4.5, ClampLength: 60, ClampWidth: 40, ClampThickness: 6, Conductive: true}
			addShape(CreateDropperWithPlace(dp, NewPoint3(top), NewDir3FromXYZ([3]float64{0, 0, 1})),
				nil, "dropper_"+itoa(i)+"_"+itoa(k), dropperParametric(dp, top))
		}
	}
	return root, nil
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
	Top       [3]float64    `json:"top"`    // 承力索侧挂点 (世界坐标)
	Direction [3]float64    `json:"direction"`
}

func mastParametric(mp MastAssemblyParams) *ParametricData {
	raw, _ := json.Marshal(ocsMastRecipe{Params: mp})
	return &ParametricData{Type: "ocs_mast", Params: raw}
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

func init() {
	RegisterParametricBuilder("ocs_mast", buildOcsMast)
	RegisterParametricBuilder("ocs_contact_wire", buildOcsContactWire)
	RegisterParametricBuilder("ocs_messenger_wire", buildOcsMessengerWire)
	RegisterParametricBuilder("ocs_dropper", buildOcsDropper)
}
