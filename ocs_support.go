package topo

// =========================================================================
// 接触网支柱装置: 按功能角色分类组装 (TB 10009 支柱设置惯例)
//
//	中间柱/非锚柱 (intermediate)  单腕臂定位, 无下锚设备 — 锚段中间柱
//	锚柱 (anchor)                 补偿装置+坠砣+拉线, 线索在本柱下锚 — 锚段端柱
//	转换柱 (transition)           双腕臂: 两支接触线并行定位 (锚段关节柱2/柱3)
//	中心柱 (center)               双腕臂: 两支同高平行定位 (三跨关节中柱)
//
// 非锚柱 = 锚柱以外 (中间柱/转换柱/中心柱, IsAnchorMast()==false)。
// 装配形态: 支柱装置为子装配 — 单腕臂角色为 1 叶片 (柱体复合体);
// 双腕臂角色为 3 叶片 (柱体 + 腕臂A + 腕臂B), 零件不暴露到地图层。
// =========================================================================

import (
	"encoding/json"
	"fmt"
	"math"
)

// MastRole 支柱功能角色
type MastRole int

const (
	MastRoleIntermediate MastRole = 0 // 中间柱 (非锚柱)
	MastRoleAnchor       MastRole = 1 // 锚柱
	MastRoleTransition   MastRole = 2 // 转换柱 (双腕臂)
	MastRoleCenter       MastRole = 3 // 中心柱 (双腕臂)
)

func (r MastRole) String() string {
	switch r {
	case MastRoleAnchor:
		return "anchor" // 锚柱
	case MastRoleTransition:
		return "transition" // 转换柱
	case MastRoleCenter:
		return "center" // 中心柱
	default:
		return "intermediate" // 中间柱 (非锚柱)
	}
}

// IsAnchorMast 是否锚柱 (非锚柱返回 false)
func IsAnchorMast(r MastRole) bool { return r == MastRoleAnchor }

// IsDualCantilever 双腕臂角色 (转换柱/中心柱)
func IsDualCantilever(r MastRole) bool {
	return r == MastRoleTransition || r == MastRoleCenter
}

// SupportParams 支柱装置组装参数
type SupportParams struct {
	Role MastRole           `json:"role"`
	Mast MastAssemblyParams `json:"mast"` // 柱体/单腕臂参数 (stagger=工作支拉出值)
	// 双腕臂角色: 第二支水平间距 (转换柱: 绝缘关节 500, 非绝缘 200; 中心柱 ~200)
	// 第二支拉出值 = Mast.Stagger - Separation
	Separation float64 `json:"separation,omitempty"`
	// 双腕臂沿线路方向的前后错位 (柱上安装位避让, 默认 ±300)
	ArmYOffset float64 `json:"armYOffset,omitempty"`
}

func (p *SupportParams) withDefaults() {
	if p.Separation <= 0 {
		p.Separation = 200
	}
	if p.ArmYOffset <= 0 {
		p.ArmYOffset = 300
	}
	p.Mast.withDefaults()
}

// CreateOcsSupportWithPlace 组装支柱装置子装配 (局部坐标: 原点=柱底中心, +X 指向线路)
// 子装配命名 name; 叶片: 单腕臂角色 [mast], 双腕臂角色 [post, cantilever_a, cantilever_b]
func CreateOcsSupportWithPlace(p SupportParams, name string) (*Assembly, error) {
	p.withDefaults()
	if name == "" {
		name = "support"
	}
	// 容器占位 vertex 在柱体中部 (不污染全局 bbox)
	v := NewVertex(0, 0, p.Mast.MastHeight/2).ToShape()
	sup := NewAssembly(NewAssemblyObjectFromShpe(*v), nil, name, nil)
	add := func(s *Shape, leaf string, data *ParametricData) {
		if s == nil || s.IsNull() {
			return
		}
		sup.AddObjectParams(NewAssemblyObjectFromShpe(*s), nil, leaf, nil, data)
	}

	if !IsDualCantilever(p.Role) {
		// 中间柱/锚柱: 柱体+腕臂(+补偿+拉线) 为 C++ 单复合体
		// 角色→装备映射: 锚柱 = 补偿装置 + 坠砣 + 拉线 (非锚柱无下锚设备)
		m := p.Mast
		if p.Role == MastRoleAnchor {
			m.CompType = 1
			m.HasGuyWire = true
			if m.RatedTension <= 0 {
				m.RatedTension = 15
			}
		}
		s := CreateMastAssembly(m)
		add(s, "mast", mastParametricWithRole(m, p.Role))
	} else {
		// 转换柱/中心柱: 横担 + 双叉臂结构
		// 上/下横担沿线路方向贯通柱身, 承托两套叉臂根部 (叉臂不悬空);
		// 两支接触线的定位点随叉臂沿线路错开 (OcsJointInput.ArmYOffset 协调)。
		post := p.Mast
		post.CantileverType = 0
		add(CreateMastAssembly(post), "post", mastParametric(post))
		levelZ := p.Mast.ContactHeight + p.Mast.StructureHeight - 150
		lowerZ := levelZ - 1300
		span := 2 * (p.ArmYOffset + 250.0)
		for _, z := range []struct {
			z    float64
			leaf string
		}{{levelZ, "crossarm_upper"}, {lowerZ, "crossarm_lower"}} {
			cr := ocsCrossarmRecipe{Span: span, CenterX: 200, Width: 200, Height: 140, Z: z.z}
			add(crossarmShape(cr), z.leaf,
				&ParametricData{Type: "ocs_crossarm", Params: mustJSON(cr)})
		}
		s1 := p.Mast.Stagger
		s2 := p.Mast.Stagger - p.Separation
		if c := buildCantileverSet(p.Mast, s1, -p.ArmYOffset); c != nil {
			add(c, "cantilever_a", cantileverParametric(p.Mast, s1, -p.ArmYOffset))
		}
		if c := buildCantileverSet(p.Mast, s2, p.ArmYOffset); c != nil {
			add(c, "cantilever_b", cantileverParametric(p.Mast, s2, p.ArmYOffset))
		}
	}
	return sup, nil
}

// buildCantileverSet 组装单套腕臂 (局部坐标, 柱底原点, +X 指向线路)
// 镜像 C++ create_mast_assembly 的尺寸链: 平腕臂高=导高+结构高-150, 下底座-1300
func buildCantileverSet(m MastAssemblyParams, stagger, yOff float64) *Shape {
	const (
		mastHalf = 150.0
		bracketT = 80.0
		insLen   = 700.0
		rise     = 3.0 * math.Pi / 180.0
	)
	CH := m.ContactHeight
	SH := m.StructureHeight
	CX := m.SideOffset
	armD := m.ArmDiameter
	if armD <= 0 {
		armD = 60
	}
	levelZ := CH + SH - 150
	lowerZ := levelZ - 1300
	armStartX := mastHalf + bracketT + insLen
	tipX := CX - stagger
	armLen := tipX - armStartX
	if armLen < 300 {
		return nil
	}

	bld := []Shape{}
	b1 := CreateMastBracketWithPlace(MastBracketParams{BoltSpacing: 80, BoltDiameter: 16,
		Height: 150, Width: 120, Thickness: 12, InsulatorBoltSpacing: 60,
		InsulatorBoltDiameter: 14, MastDiameter: 0},
		NewPoint3([3]float64{mastHalf, yOff, levelZ}),
		NewDir3FromXYZ([3]float64{1, 0, 0}), NewDir3FromXYZ([3]float64{0, 0, 1}))
	bld = append(bld, *b1)
	b2 := CreateMastBracketWithPlace(MastBracketParams{BoltSpacing: 80, BoltDiameter: 16,
		Height: 150, Width: 120, Thickness: 12, InsulatorBoltSpacing: 60,
		InsulatorBoltDiameter: 14, MastDiameter: 0},
		NewPoint3([3]float64{mastHalf, yOff, lowerZ}),
		NewDir3FromXYZ([3]float64{1, 0, 0}), NewDir3FromXYZ([3]float64{0, 0, 1}))
	bld = append(bld, *b2)

	rip := RodInsulatorParams{Type: 0, Height: insLen, OuterDiameter: 80,
		ShedDiameter: 150, ShedSpacing: 65, ShedCount: 8, FlangeDiameter: 110}
	bld = append(bld, *CreateRodInsulatorWithPlace(rip,
		NewPoint3([3]float64{mastHalf + bracketT, yOff, levelZ}),
		NewDir3FromXYZ([3]float64{1, 0, 0})))
	bld = append(bld, *CreateRodInsulatorWithPlace(rip,
		NewPoint3([3]float64{mastHalf + bracketT, yOff, lowerZ}),
		NewDir3FromXYZ([3]float64{1, 0, 0})))

	lp := LevelCantileverParams{Length: armLen, OuterDiameter: armD, WallThickness: 4, RiseAngle: 3}
	bld = append(bld, *CreateLevelCantileverWithPlace(lp,
		NewPoint3([3]float64{armStartX, yOff, levelZ}),
		NewDir3FromXYZ([3]float64{1, 0, 0}), NewDir3FromXYZ([3]float64{0, 0, 1})))

	jointX := armStartX + armLen*0.65
	jointZ := levelZ + armLen*0.65*math.Tan(rise)
	dv := [3]float64{jointX - armStartX, 0, jointZ - lowerZ}
	l := math.Hypot(dv[0], dv[2])
	sp := SlantCantileverParams{Length: l, OuterDiameter: armD, WallThickness: 4, SlantAngle: 45}
	bld = append(bld, *CreateSlantCantileverWithPlace(sp,
		NewPoint3([3]float64{armStartX, yOff, lowerZ}),
		NewDir3FromXYZ(dv), NewDir3FromXYZ([3]float64{0, 0, 1})))

	saddle := MWSaddleParams{Length: 150, Width: 80, Height: 60, GrooveRadius: 7, BoltDiameter: 12}
	sz := CH + SH + 7 - 60
	bld = append(bld, *CreateMWSaddleWithPlace(saddle,
		NewPoint3([3]float64{tipX - 80, yOff, sz}),
		NewDir3FromXYZ([3]float64{0, 0, 1}), NewDir3FromXYZ([3]float64{1, 0, 0})))

	// 定位管 (内端=定位管座装斜腕臂 28% 下段, 坡度 ~9-13° 接近规范 1:5~1:10; 与 C++ 同构)
	sJ := [3]float64{armStartX, yOff, lowerZ}
	sT := [3]float64{jointX, yOff, jointZ}
	r0 := [3]float64{sJ[0] + (sT[0]-sJ[0])*0.28, yOff, sJ[2] + (sT[2]-sJ[2])*0.28}
	r1 := [3]float64{tipX, yOff, CH + 30}
	rv := [3]float64{r1[0] - r0[0], 0, r1[2] - r0[2]}
	rl := math.Hypot(rv[0], rv[2])
	rp := RegistrationArmParams{Type: 0, Length: rl, TubeWidth: 34, TubeHeight: 30, WallThickness: 3}
	bld = append(bld, *CreateRegistrationArmWithPlace(rp,
		NewPoint3(r0), NewDir3FromXYZ(rv), NewDir3FromXYZ([3]float64{0, 0, 1})))

	// 定位管斜撑 (斜腕臂 78% → 定位管 18% 短连杆) + 两端斜撑线夹短套 (与 C++ 柱装配同构)
	sb := [3]float64{armStartX + (jointX - armStartX) * 0.62, yOff, lowerZ + (jointZ - lowerZ) * 0.62}
	rb := [3]float64{r0[0] + (r1[0]-r0[0]) * 0.2, yOff, r0[2] + (r1[2]-r0[2]) * 0.2}
	bv := [3]float64{rb[0] - sb[0], 0, rb[2] - sb[2]}
	bl := math.Hypot(bv[0], bv[2])
	if bl > 200 {
		bld = append(bld, *CreateCantileverBraceWithPlace(
			CantileverBraceParams{Length: bl, OuterDiameter: 34, WallThickness: 3},
			NewPoint3(sb), NewDir3FromXYZ([3]float64{bv[0] / bl, 0, bv[2] / bl}),
			NewDir3FromXYZ([3]float64{0, 0, 1})))
		// 斜撑线夹: 母管轴向短套块。管轴作 zDir, xDir 取垂直参考 (定位管近垂直时
		// 若以管轴作 xDir 会与 zDir=Z 共线, 放置帧退化报错)。
		clampOrient := func(axis [3]float64) Dir3 {
			ref := [3]float64{0, 0, 1}
			if math.Abs(axis[2]) > 0.9 {
				ref = [3]float64{1, 0, 0}
			}
			x := [3]float64{axis[1]*ref[2] - axis[2]*ref[1], axis[2]*ref[0] - axis[0]*ref[2], axis[0]*ref[1] - axis[1]*ref[0]}
			l := math.Hypot(x[0], math.Hypot(x[1], x[2]))
			return NewDir3FromXYZ([3]float64{x[0] / l, x[1] / l, x[2] / l})
		}
		rn := [3]float64{rv[0] / rl, 0, rv[2] / rl}
		bld = append(bld, *CreateCuboidWithPlace(CuboidParams{Length: 46, Width: 46, Height: 70},
			NewPoint3([3]float64{rb[0], yOff, rb[2]}), clampOrient(rn), NewDir3FromXYZ(rn)))
		sv := [3]float64{jointX - armStartX, 0, jointZ - lowerZ}
		svl := math.Hypot(sv[0], sv[2])
		sn := [3]float64{sv[0] / svl, 0, sv[2] / svl}
		bld = append(bld, *CreateCuboidWithPlace(CuboidParams{Length: 46, Width: 46, Height: 70},
			NewPoint3([3]float64{sb[0], yOff, sb[2]}), clampOrient(sn), NewDir3FromXYZ(sn)))
	}

	// 合并为单 compound 叶片
	return TopoCompoundMake(bld).ToShape()
}

// ocsCrossarmRecipe 横担配方: 沿线路方向的承托梁 (上下双横担, 叉臂根部安装其上)
type ocsCrossarmRecipe struct {
	Span    float64 `json:"span"`    // 横担全长 (沿线路, 局部 Y)
	CenterX float64 `json:"centerX"` // 横截面中心 X (柱身外侧, 叉臂根部所在)
	Width   float64 `json:"width"`   // 截面宽 (局部 X)
	Height  float64 `json:"height"`  // 截面高 (局部 Z)
	Z       float64 `json:"z"`       // 安装高
}

func crossarmShape(r ocsCrossarmRecipe) *Shape {
	// Cuboid: Length 沿放置系局部 X (此处=线路方向), 中心定位
	return CreateCuboidWithPlace(CuboidParams{Length: float32(r.Span),
		Width: float32(r.Width), Height: float32(r.Height)},
		NewPoint3([3]float64{r.CenterX, 0, r.Z}),
		NewDir3FromXYZ([3]float64{0, 1, 0}), NewDir3FromXYZ([3]float64{0, 0, 1}))
}

func buildOcsCrossarm(params json.RawMessage) (*Shape, *TopoLocation, error) {
	var r ocsCrossarmRecipe
	if err := json.Unmarshal(params, &r); err != nil {
		return nil, nil, fmt.Errorf("ocs_crossarm: %w", err)
	}
	s := crossarmShape(r)
	if s == nil || s.IsNull() {
		return nil, nil, errInvalidInput("ocs_crossarm: build failed")
	}
	return s, nil, nil
}

// cantileverParametric 单套腕臂配方 (叶子级, 改拉出值/错位可重建)
type ocsCantileverRecipe struct {
	Mast    MastAssemblyParams `json:"mast"`
	Stagger float64            `json:"stagger"`
	YOffset float64            `json:"yOffset"`
}

func cantileverParametric(m MastAssemblyParams, stagger, yOff float64) *ParametricData {
	raw, _ := json.Marshal(ocsCantileverRecipe{Mast: m, Stagger: stagger, YOffset: yOff})
	return &ParametricData{Type: "ocs_cantilever", Params: raw}
}

func buildOcsCantilever(params json.RawMessage) (*Shape, *TopoLocation, error) {
	var r ocsCantileverRecipe
	if err := json.Unmarshal(params, &r); err != nil {
		return nil, nil, fmt.Errorf("ocs_cantilever: %w", err)
	}
	s := buildCantileverSet(r.Mast, r.Stagger, r.YOffset)
	if s == nil || s.IsNull() {
		return nil, nil, errInvalidInput("ocs_cantilever: build failed")
	}
	return s, nil, nil
}

// buildOcsSupportAssembly ocs_support 装配级 builder: 按角色整棵重建支柱装置
func buildOcsSupportAssembly(params json.RawMessage, name string) (*Assembly, error) {
	var p SupportParams
	if err := json.Unmarshal(params, &p); err != nil {
		return nil, fmt.Errorf("ocs_support: %w", err)
	}
	return CreateOcsSupportWithPlace(p, name)
}

func init() {
	RegisterParametricBuilder("ocs_cantilever", buildOcsCantilever)
	RegisterParametricBuilder("ocs_crossarm", buildOcsCrossarm)
	RegisterAssemblyBuilder("ocs_support", buildOcsSupportAssembly)
}
