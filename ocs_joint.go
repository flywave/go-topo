package topo

// =========================================================================
// 锚段关节组装器: 两个锚段的过渡区 (TB 10009 锚段关节)
//
//	四跨关节: 柱1(锚柱B) - 柱2(转换柱) - 柱3(转换柱) - 柱4(锚柱A)
//	  - 柱2~柱3 之间 A/B 两支接触线以工作高度并行 (水平间距: 非绝缘 200 / 绝缘 500)
//	  - A 段工作支越过柱3 后抬升, 在柱4 下锚 (补偿); B 段从柱1 下锚 (补偿) 降坡进入
//	  - 转换柱为双腕臂 (cantilever_a/cantilever_b), 锚柱为补偿柱体+单腕臂
//
// 受流过渡: 受电弓在柱2~柱3 平行区从 A 段滑到 B 段。
// =========================================================================

import (
	"encoding/json"
	"fmt"
	"math"
)

// OcsJointInput 锚段关节输入
type OcsJointInput struct {
	Centerline      []Point3 `json:"centerline"`      // 关节区线路中心线 (mm, ≥3 点)
	ContactHeight   float64  `json:"contactHeight"`   // 导高, 默认 6000
	StructureHeight float64  `json:"structureHeight"` // 结构高度, 默认 1400
	SpanLength      float64  `json:"spanLength"`      // 关节跨距, 默认 0.6×正线 (取 30000)
	MastHeight      float64  `json:"mastHeight"`      // 柱高, 默认 9000
	MastType        int      `json:"mastType"`        // 1-钢柱, 2-混凝土柱
	SideOffset      float64  `json:"sideOffset"`      // 侧面限界 CX, 默认 2900
	Stagger         float64  `json:"stagger"`         // A 支拉出值, 默认 300
	Separation      float64  `json:"separation"`      // 两支水平间距, 默认 200 (非绝缘; 绝缘 500)
	Insulated       bool     `json:"insulated"`       // 绝缘关节 (Separation=500, 并装隔离开关)
	AnchorDrop      float64  `json:"anchorDrop"`      // 下锚点抬升高度, 默认 800
	RatedTension    float64  `json:"ratedTension"`    // 补偿额定张力 (kN), 默认 15
	ContactWireDia  float64  `json:"contactWireDia"`  // 接触线直径, 默认 12.9
	MessengerDia    float64  `json:"messengerDia"`    // 承力索直径, 默认 13.5
	ArmYOffset      float64  `json:"armYOffset"`      // 转换柱双叉臂沿线路错位, 默认 300 (导线定位点同步错开)
}

func (in *OcsJointInput) withDefaults() {
	if in.ContactHeight <= 0 {
		in.ContactHeight = 6000
	}
	if in.StructureHeight <= 0 {
		in.StructureHeight = 1400
	}
	if in.SpanLength <= 0 {
		in.SpanLength = 30000
	}
	if in.MastHeight <= 0 {
		in.MastHeight = 9000
	}
	if in.SideOffset <= 0 {
		in.SideOffset = 2900
	}
	if in.Stagger <= 0 {
		in.Stagger = 300
	}
	if in.Separation <= 0 {
		if in.Insulated {
			in.Separation = 500
		} else {
			in.Separation = 200
		}
	}
	if in.AnchorDrop <= 0 {
		in.AnchorDrop = 800
	}
	if in.RatedTension <= 0 {
		in.RatedTension = 15
	}
	if in.ContactWireDia <= 0 {
		in.ContactWireDia = 12.9
	}
	if in.MessengerDia <= 0 {
		in.MessengerDia = 13.5
	}
	if in.ArmYOffset <= 0 {
		in.ArmYOffset = 300
	}
}

// OcsJointMast 关节单柱布局
type OcsJointMast struct {
	Index    int        `json:"index"`
	Role     string     `json:"role"`    // anchor / transition
	Mileage  float64    `json:"mileage"` // m
	Position [3]float64 `json:"position"`
	StaggerA float64    `json:"staggerA"` // A 支拉出值
	StaggerB float64    `json:"staggerB"` // B 支拉出值 (单腕臂锚柱时等于 A)
}

// OcsJointLayout 锚段关节布局 (可序列化, 编辑后经 CreateOcsJointFromLayout 再生成)
type OcsJointLayout struct {
	Input OcsJointInput  `json:"input"`
	Masts []OcsJointMast `json:"masts"`
	AWire [][3]float64   `json:"aWire"` // A 段接触线折线 (含下锚抬升点)
	BWire [][3]float64   `json:"bWire"` // B 段接触线折线
}

// ToJSON 序列化关节布局
func (l *OcsJointLayout) ToJSON() ([]byte, error) { return json.Marshal(l) }

// OcsJointLayoutFromJSON 反序列化关节布局
func OcsJointLayoutFromJSON(data []byte) (*OcsJointLayout, error) {
	var l OcsJointLayout
	if err := json.Unmarshal(data, &l); err != nil {
		return nil, fmt.Errorf("ocs joint: invalid layout JSON: %w", err)
	}
	return &l, nil
}

// ComputeOcsJointLayout 由输入纯计算四跨关节布局
func ComputeOcsJointLayout(in OcsJointInput) (*OcsJointLayout, error) {
	in.withDefaults()
	if len(in.Centerline) < 2 {
		return nil, errInvalidInput("ocs joint: centerline needs >= 2 points")
	}
	acc := polyArcLens(in.Centerline)
	total := acc[len(acc)-1]
	if total < 3*in.SpanLength {
		return nil, errInvalidInput("ocs joint: centerline too short for 4 masts (need 3 spans)")
	}
	// 柱位: 等跨距 4 柱 (mm 弧长直算, Mileage 字段对外为米)
	miMm := []float64{0, in.SpanLength, 2 * in.SpanLength, 3 * in.SpanLength}
	roles := []MastRole{MastRoleAnchor, MastRoleTransition, MastRoleTransition, MastRoleAnchor}
	layout := &OcsJointLayout{Input: in}
	staggerB := in.Stagger - in.Separation
	for i, mm := range miMm {
		f := frameAt(in.Centerline, mm)
		perp := f.perp
		pos := [3]float64{f.pos.Data()[0] + perp[0]*in.SideOffset, f.pos.Data()[1] + perp[1]*in.SideOffset, f.pos.Data()[2]}
		m := OcsJointMast{Index: i, Role: roles[i].String(), Mileage: mm / 1000, Position: pos,
			StaggerA: in.Stagger, StaggerB: staggerB}
		if roles[i] == MastRoleAnchor {
			m.StaggerB = in.Stagger
		}
		layout.Masts = append(layout.Masts, m)
	}
	layout.AWire, layout.BWire = jointWirePolylines(layout)
	return layout, nil
}

// jointWirePolylines 计算 A/B 段接触线折线 (工作支-抬升-下锚)
// A: 从柱1 后方进入, 工作高经柱2/柱3 (拉出值 Stagger), 柱3 后抬升在柱4 下锚
// B: 柱1 下锚点降坡, 经柱2/柱3 (拉出值 Stagger-Separation), 向前工作支延伸
func jointWirePolylines(l *OcsJointLayout) (aWire, bWire [][3]float64) {
	in := l.Input
	d14 := jointDirAt(l, 0)
	perp := [3]float64{-d14[1], d14[0], 0} // 行进左侧
	at := func(i int, stagger, z float64) [3]float64 {
		p := l.Masts[i].Position
		return [3]float64{p[0] - perp[0]*stagger, p[1] - perp[1]*stagger, p[2] + z}
	}
	sa, sb, dz := in.Stagger, in.Stagger-in.Separation, in.AnchorDrop
	mastDir := [3]float64{-perp[0], -perp[1], 0} // 柱 +X 指向线路
	back := 0.15 * in.SpanLength                 // 关节外延伸段
	anchorPull := 400.0                          // 下锚点向柱身回收
	yA, yB := -in.ArmYOffset, in.ArmYOffset      // 转换柱双叉臂沿线路错位, 导线定位点同步错开
	shift := func(pt [3]float64, y float64) [3]float64 {
		return [3]float64{pt[0] + d14[0]*y, pt[1] + d14[1]*y, pt[2]}
	}

	// A 段: 后方延伸(工作高) → 柱1 → 柱2* → 柱3* → 抬升下锚(柱4)
	//   *转换柱处定位点随叉臂沿线路错开 yA (与叉臂 cantilever_a 对位)
	p := at(0, sa, in.ContactHeight)
	aWire = [][3]float64{
		{p[0] - d14[0]*back, p[1] - d14[1]*back, p[2]},
		p,
		shift(at(1, sa, in.ContactHeight), yA),
		shift(at(2, sa, in.ContactHeight), yA),
	}
	e := at(3, sa, in.ContactHeight+dz)
	aWire = append(aWire, [3]float64{e[0] + mastDir[0]*anchorPull, e[1] + mastDir[1]*anchorPull, e[2]})

	// B 段: 柱1 下锚点 → 降坡 → 柱2* → 柱3* → 前方延伸(工作高)
	//   *转换柱处定位点随叉臂错开 yB (与叉臂 cantilever_b 对位)
	q := at(0, sb, in.ContactHeight+dz)
	bWire = [][3]float64{
		{q[0] + mastDir[0]*anchorPull, q[1] + mastDir[1]*anchorPull, q[2]},
		at(0, sb, in.ContactHeight),
		shift(at(1, sb, in.ContactHeight), yB),
		shift(at(2, sb, in.ContactHeight), yB),
	}
	t := shift(at(2, sb, in.ContactHeight), yB)
	// B 段工作支向前延伸越过柱4 (1.2 跨), 保证关节外连续
	ext := 1.2 * in.SpanLength
	bWire = append(bWire, [3]float64{t[0] + d14[0]*ext, t[1] + d14[1]*ext, t[2]})
	return
}

// CreateOcsJointAssembly 由关节布局生成锚段关节装配:
//
//	joint (锚段关节)
//	├── mast_0      锚柱B (B段下锚补偿 + B支单腕臂)   [anchor]
//	├── mast_1      转换柱 (双腕臂: A支+B支)          [transition]
//	├── mast_2      转换柱 (双腕臂: A支+B支)          [transition]
//	├── mast_3      锚柱A (A段下锚补偿 + A支单腕臂)   [anchor]
//	└── wire_a_k / wire_b_k   A/B 段接触线分段 (弛度放样)
func CreateOcsJointAssembly(layout *OcsJointLayout) (*Assembly, error) {
	if layout == nil || len(layout.Masts) != 4 {
		return nil, errInvalidInput("ocs joint: layout needs 4 masts")
	}
	in := layout.Input
	in.withDefaults()

	fx := (layout.Masts[0].Position[0] + layout.Masts[3].Position[0]) / 2
	fy := (layout.Masts[0].Position[1] + layout.Masts[3].Position[1]) / 2
	root := NewAssembly(NewAssemblyObjectFromShpe(*NewVertex(fx, fy, in.ContactHeight).ToShape()),
		nil, "joint", nil)

	// 支柱装置 (角色化)
	for i, m := range layout.Masts {
		role := MastRoleTransition
		base := MastAssemblyParams{MastType: in.MastType, MastHeight: in.MastHeight,
			CantileverType: 1, ArmDiameter: 55, Stagger: m.StaggerA,
			ContactHeight: in.ContactHeight, StructureHeight: in.StructureHeight,
			SideOffset: in.SideOffset}
		sp := SupportParams{Role: role, Mast: base, Separation: in.Separation, ArmYOffset: in.ArmYOffset}
		if m.Role == "anchor" {
			sp.Role = MastRoleAnchor
			// 锚柱: 补偿+拉线; 单腕臂定位过柱支 (A 或 B)
			sp.Mast.CompType = 1
			sp.Mast.HasGuyWire = true
			sp.Mast.RatedTension = in.RatedTension
			sp.Mast.TensionPlaneY = 250 // 关节内侧 (跨距侧, 坠砣所在); 拉线自动布关节外侧
			if i == 0 {
				sp.Mast.Stagger = m.StaggerB // B 支过柱定位
			}
		}
		sup, err := CreateOcsSupportWithPlace(sp, "mast_"+itoa(i))
		if err != nil {
			return nil, err
		}
		sup.SetParametric(&ParametricData{Type: "ocs_support", Params: mustJSON(sp)})
		// 放置: 局部 +X 指向线路 (复用锚段支柱放置矩阵)
		d := jointDirAt(layout, i)
		facing := [3]float64{d[1], -d[0], 0}
		loc := NewTopoLocation(mastPlacementTrsf(AnchorMastLayout{Position: m.Position, Direction: facing}))
		root.AddAssembly(sup, loc, sup.GetName(), nil)
		if root.HasError() {
			return nil, errInvalidInput("add joint mast: " + root.Error())
		}
	}

	// A/B 接触线分段 (折线相邻点间弛度放样)
	addWire := func(pts [][3]float64, tag string) {
		for k := 0; k+1 < len(pts); k++ {
			p0, p1 := pts[k], pts[k+1]
			if dist3(p0, p1) < 100 {
				continue
			}
			wp := ContactWireParams{Diameter: in.ContactWireDia, BottomRadius: 8, TopRadius: 3,
				Sag: dist3(p0, p1) * 0.0005}
			s := CreateContactWire(wp, NewPoint3(p0), NewPoint3(p1))
			if s == nil || s.IsNull() {
				continue
			}
			recipe := ocsWireRecipe{Diameter: wp.Diameter, BottomRadius: wp.BottomRadius,
				TopRadius: wp.TopRadius, Sag: wp.Sag, Start: p0, End: p1}
			root.AddObjectParams(NewAssemblyObjectFromShpe(*s), nil,
				fmt.Sprintf("wire_%s_%d", tag, k), nil,
				&ParametricData{Type: "ocs_contact_wire", Params: mustJSON(recipe)})
		}
	}
	addWire(layout.AWire, "a")
	addWire(layout.BWire, "b")
	return root, nil
}

// jointDirAt 关节柱位处的行进方向 (柱1→柱4)
func jointDirAt(layout *OcsJointLayout, i int) [3]float64 {
	a := layout.Masts[i].Position
	bi := 3 - i
	if i == 0 {
		bi = 1
	} else if i == 3 {
		bi = 2
	}
	b := layout.Masts[bi].Position
	d := [3]float64{b[0] - a[0], b[1] - a[1], 0}
	n := math.Hypot(d[0], d[1])
	if n < 1e-9 {
		return [3]float64{1, 0, 0}
	}
	return [3]float64{d[0] / n, d[1] / n, 0}
}

// CreateOcsJoint 锚段关节一键生成 (= Compute + Create)
func CreateOcsJoint(in OcsJointInput) (*Assembly, *OcsJointLayout, error) {
	layout, err := ComputeOcsJointLayout(in)
	if err != nil {
		return nil, nil, err
	}
	as, err := CreateOcsJointAssembly(layout)
	if err != nil {
		return nil, nil, err
	}
	return as, layout, nil
}

// buildOcsJointAssembly ocs_joint 装配级 builder
func buildOcsJointAssembly(params json.RawMessage, name string) (*Assembly, error) {
	var l OcsJointLayout
	if err := json.Unmarshal(params, &l); err != nil {
		return nil, fmt.Errorf("ocs_joint: %w", err)
	}
	as, err := CreateOcsJointAssembly(&l)
	if err != nil {
		return nil, err
	}
	if name != "" && as.GetName() != name {
		// 名称保持导出值 (重建占根名, 关节固定为 joint 不影响层级)
		_ = name
	}
	return as, nil
}

func init() {
	RegisterAssemblyBuilder("ocs_joint", buildOcsJointAssembly)
}
