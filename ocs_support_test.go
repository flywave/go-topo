package topo

// 接触网支柱角色覆盖验证: 中间柱(非锚柱) / 锚柱 / 转换柱 / 中心柱 + 四跨锚段关节

import (
	"strings"
	"testing"
)

func supportTestParams(role MastRole) SupportParams {
	return SupportParams{Role: role,
		Mast: MastAssemblyParams{MastType: 1, MastHeight: 9000, CantileverType: 1,
			ArmDiameter: 55, Stagger: 300, ContactHeight: 6000,
			StructureHeight: 1400, SideOffset: 2900},
		Separation: 500}
}

// 四类支柱装置全部可生成, 双腕臂角色层级正确
func TestSupportRoles(t *testing.T) {
	cases := []struct {
		role     MastRole
		name     string
		leaves   int
		dualYMin float64 // 双腕臂: 两支水平错开应使 Y 向尺寸明显大于单腕臂
	}{
		{MastRoleIntermediate, "intermediate", 1, 0},
		{MastRoleAnchor, "anchor", 1, 0},
		{MastRoleTransition, "transition", 5, 300}, // 柱体+上下横担+双叉臂
		{MastRoleCenter, "center", 5, 300},
	}
	for _, c := range cases {
		sup, err := CreateOcsSupportWithPlace(supportTestParams(c.role), "support_"+c.name)
		if err != nil {
			t.Fatalf("%s: %v", c.name, err)
		}
		if n := len(sup.Children()); n != c.leaves {
			t.Fatalf("%s: leaves=%d want %d", c.name, n, c.leaves)
		}
		bb := sup.ToCompound().BBox().Data()
		dy := bb[4] - bb[1]
		if c.dualYMin > 0 && dy < c.dualYMin {
			t.Fatalf("%s: y extent %.0f < %.0f (dual cantilevers not spread)", c.name, dy, c.dualYMin)
		}
		if bb[5]-bb[2] < 8500 {
			t.Fatalf("%s: height %.0f too small", c.name, bb[5]-bb[2])
		}
		// 配方可独立重建
		data, err := sup.ExportParametric()
		if err != nil {
			t.Fatalf("%s: export: %v", c.name, err)
		}
		rebuilt, err := RebuildFromParametric(data)
		if err != nil {
			t.Fatalf("%s: rebuild: %v", c.name, err)
		}
		rb := rebuilt.ToCompound().BBox().Data()
		for i := range bb {
			if absF(bb[i]-rb[i]) > 1 {
				t.Fatalf("%s: rebuild bbox mismatch [%d] %.1f vs %.1f", c.name, i, bb[i], rb[i])
			}
		}
	}
}

// 转换柱连接性: 横担承托叉臂根部 (不悬空), 叉臂定位管端在横担覆盖范围内
func TestTransitionMastConnectivity(t *testing.T) {
	sup, err := CreateOcsSupportWithPlace(supportTestParams(MastRoleTransition), "support_t")
	if err != nil {
		t.Fatal(err)
	}
	leaf := func(name string) [6]float64 {
		for _, ch := range sup.Children() {
			if ch.GetName() == name {
				return ch.ToCompound().BBox().Data()
			}
		}
		t.Fatalf("leaf %q not found", name)
		return [6]float64{}
	}
	cu, cl := leaf("crossarm_upper"), leaf("crossarm_lower")
	ca := leaf("cantilever_a")
	// 上横担沿线路覆盖 ±550 (叉臂根部 ±300 在其上)
	if cu[1] > -549 || cu[4] < 549 {
		t.Fatalf("crossarm_upper y span [%0.f,%0.f] does not carry both roots", cu[1], cu[4])
	}
	// 叉臂最高点 (平腕臂仰角端) 应落在上横担高度带内 (根部安装在横担上)
	if ca[5] < cu[2]-80 || ca[5] > cu[5]+80 {
		t.Fatalf("cantilever top %.0f not within upper crossarm band [%.0f,%.0f]", ca[5], cu[2], cu[5])
	}
	// 下横担与上横担高差 = 1300 (叉臂斜杆两端口)
	if absF((cu[2]-cl[2])-1300) > 5 {
		t.Fatalf("crossarm vertical spacing %.0f != 1300", cu[2]-cl[2])
	}
}

// 锚柱与非锚柱区分: 锚柱含补偿装置+拉线, X 向(含后拉线)显著更大
func TestAnchorVsNonAnchor(t *testing.T) {
	anchor := supportTestParams(MastRoleAnchor)
	mid := supportTestParams(MastRoleIntermediate)
	sa, err := CreateOcsSupportWithPlace(anchor, "anchor")
	if err != nil {
		t.Fatal(err)
	}
	sm, err := CreateOcsSupportWithPlace(mid, "intermediate")
	if err != nil {
		t.Fatal(err)
	}
	ba, bm := sa.ToCompound().BBox().Data(), sm.ToCompound().BBox().Data()
	dy := func(b [6]float64) float64 { return b[4] - b[1] }
	// 锚柱: 拉线顺线路布在张力平面对侧 (默认坠砣 y=-250, 拉线 y=+250..+7200),
	// Y 向尺寸显著大于中间柱; 补偿/坠砣与拉线共面 (受力平面一致)
	if dy(ba) < dy(bm)+3000 {
		t.Fatalf("anchor dy=%.0f should exceed intermediate dy=%.0f by >3000 (guy along track)", dy(ba), dy(bm))
	}
	if bm[4]-bm[1] > 700 {
		t.Fatalf("intermediate mast y extent %.0f too wide (no guy expected)", bm[4]-bm[1])
	}
}

// 锚柱张力平面定边: 跨距朝向决定坠砣侧, 拉线在对侧顺线路
func TestAnchorGuyPlane(t *testing.T) {
	mk := func(planeY float64) [6]float64 {
		sp := supportTestParams(MastRoleAnchor)
		sp.Mast.TensionPlaneY = planeY
		s, err := CreateOcsSupportWithPlace(sp, "support_a")
		if err != nil {
			t.Fatal(err)
		}
		return s.ToCompound().BBox().Data()
	}
	pos := mk(250) // 坠砣在 +250 (跨距侧), 拉线在对侧 (−Y, 顺线路 45° 下锚)
	neg := mk(-250)
	if pos[1] > -6000 || pos[4] < 150 || pos[4] > 600 {
		t.Fatalf("planeY=+250: y range [%.0f, %.0f], want guy to -Y (~-7200) and weight at +250", pos[1], pos[4])
	}
	if neg[4] < 6000 || neg[1] < -600 || neg[1] > -150 {
		t.Fatalf("planeY=-250: y range [%.0f, %.0f], want guy to +Y (~+7200) and weight at -250", neg[1], neg[4])
	}
}

// 角色字符串
func TestMastRoleString(t *testing.T) {
	for r, want := range map[MastRole]string{
		MastRoleIntermediate: "intermediate", MastRoleAnchor: "anchor",
		MastRoleTransition: "transition", MastRoleCenter: "center",
	} {
		if r.String() != want {
			t.Fatalf("role %d = %q want %q", r, r.String(), want)
		}
	}
	if IsAnchorMast(MastRoleIntermediate) || IsAnchorMast(MastRoleTransition) {
		t.Fatal("非锚柱角色被误判为锚柱")
	}
	if !IsAnchorMast(MastRoleAnchor) {
		t.Fatal("锚柱误判")
	}
}

// 四跨锚段关节: 层级/角色/双支并行/下锚抬升/配方往返
func TestOcsJointAssembly(t *testing.T) {
	var cl []Point3
	for x := 0.0; x <= 120000; x += 5000 {
		cl = append(cl, NewPoint3([3]float64{x, 0, 0}))
	}
	joint, layout, err := CreateOcsJoint(OcsJointInput{Centerline: cl, ContactHeight: 6000,
		SpanLength: 35000, Insulated: true, Separation: 500})
	if err != nil {
		t.Fatalf("joint: %v", err)
	}
	// 层级: 顶层 = 4 支柱装置 + 8 线分段
	//   全树 = 根 + 4 + (2 锚柱叶 + 10 转换柱叶[柱体+双横担+双叉臂]) + 8 = 25
	if n := len(joint.Children()); n != 12 {
		t.Fatalf("joint top-level=%d want 12 (4 mast + 8 wire)", n)
	}
	if n := len(joint.GetElements()); n != 25 {
		t.Fatalf("joint elements=%d want 25", n)
	}
	// 导线/叉臂对位: A 段在转换柱 (index 1) 的定位点沿行进方向错开 -ArmYOffset
	yOffA := layout.AWire[2][0] - layout.Masts[1].Position[0]
	if absF(yOffA-(-300)) > 1 {
		t.Fatalf("A wire not offset with cantilever_a: dx=%.1f", yOffA)
	}
	yOffB := layout.BWire[2][0] - layout.Masts[1].Position[0]
	if absF(yOffB-300) > 1 {
		t.Fatalf("B wire not offset with cantilever_b: dx=%.1f", yOffB)
	}
	var roles []string
	for _, m := range layout.Masts {
		roles = append(roles, m.Role)
	}
	if strings.Join(roles, ",") != "anchor,transition,transition,anchor" {
		t.Fatalf("joint roles=%v", roles)
	}
	// 绝缘关节两支间距 500: B 支拉出值 = A - 500
	if layout.Masts[1].StaggerB != layout.Masts[1].StaggerA-500 {
		t.Fatalf("insulated separation wrong: B=%.0f", layout.Masts[1].StaggerB)
	}
	// 下锚抬升: A 线末点高度 = 导高 + AnchorDrop
	ah := layout.AWire[len(layout.AWire)-1][2]
	if ah < 6000+700 || ah > 6000+900 {
		t.Fatalf("A anchor drop z=%.0f", ah)
	}
	// 往返: 布局 JSON → 再生成 → bbox 等价
	b, err := layout.ToJSON()
	if err != nil {
		t.Fatal(err)
	}
	back, err := OcsJointLayoutFromJSON(b)
	if err != nil {
		t.Fatal(err)
	}
	as2, err := CreateOcsJointAssembly(back)
	if err != nil {
		t.Fatal(err)
	}
	bb1 := joint.ToCompound().BBox().Data()
	bb2 := as2.ToCompound().BBox().Data()
	for i := range bb1 {
		if absF(bb1[i]-bb2[i]) > 1 {
			t.Fatalf("joint rebuild bbox mismatch [%d]", i)
		}
	}
	// 装配级配方往返
	data, err := joint.ExportParametric()
	if err != nil {
		t.Fatal(err)
	}
	rebuilt, err := RebuildFromParametric(data)
	if err != nil {
		t.Fatalf("parametric rebuild: %v", err)
	}
	if len(rebuilt.GetElements()) != 25 {
		t.Fatalf("rebuilt elements=%d", len(rebuilt.GetElements()))
	}
	if _, ok := rebuilt.Get("mast_1/cantilever_a"); !ok {
		t.Fatal("transition dual cantilever leaf not addressable")
	}
}

// 锚段内支柱角色标注: 端柱=锚柱, 中间柱=非锚柱 (intermediate)
func TestAnchorSectionRoleTagging(t *testing.T) {
	var cl []Point3
	for x := 0.0; x <= 150000; x += 5000 {
		cl = append(cl, NewPoint3([3]float64{x, 0, 0}))
	}
	layout, err := ComputeAnchorSectionLayout(AnchorSectionInput{Centerline: cl,
		ContactHeight: 6000, SpanLength: 50000, MastHeight: 9000, HasCompensator: true})
	if err != nil {
		t.Fatal(err)
	}
	roles := []string{}
	for _, m := range layout.Masts {
		roles = append(roles, m.Role)
	}
	if strings.Join(roles, ",") != "anchor,intermediate,intermediate,anchor" {
		t.Fatalf("anchor section roles=%v", roles)
	}
	// JSON 往返保留角色
	b, _ := layout.ToJSON()
	back, err := AnchorSectionLayoutFromJSON(b)
	if err != nil {
		t.Fatal(err)
	}
	if back.Masts[0].Role != "anchor" || back.Masts[2].Role != "intermediate" {
		t.Fatal("role lost in JSON roundtrip")
	}
}

func absF(v float64) float64 {
	if v < 0 {
		return -v
	}
	return v
}
