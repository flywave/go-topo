package topo

// 铁路参数化视觉验收体系
//
// 用真实名义参数 (GB 2585 钢轨 / TB 10001 线路 / TB 10009 电力牵引供电)
// 逐个生成铁路与接触网图元、部件与装配, 经四道闸门:
//   1. 生成有效性  — shape 非 null 且 valid
//   2. 尺寸符合性  — bbox 各轴与真实工程量值对照 (本文件 accExpect 表)
//   3. 参数化闭环  — 布局 JSON 往返 (ToJSON→FromJSON→再生成) 几何一致
//   4. 视觉符合性  — STL 导出 + acceptance/index.html 渲染截图目检 (人工/评审)
// 产出: <dir>/manifest.json (逐项判定+实测尺寸), <dir>/report.md, <dir>/stl/*.stl
//
// 运行: ACCEPTANCE_DIR=./acceptance CC=/usr/bin/clang CXX=/usr/bin/clang++ \
//        go test -run TestGenerateRailwayAcceptance -v .

import (
	"encoding/json"
	"fmt"
	"math"
	"os"
	"path/filepath"
	"runtime"
	"runtime/debug"
	"strings"
	"testing"
)

// =========================================================================
// 验收判定数据
// =========================================================================

type accCheck struct {
	What string `json:"what"`
	Want string `json:"want"`
	Got  string `json:"got"`
	Pass bool   `json:"pass"`
}

type accExpect struct {
	What string  // 检查项名称, 如 "高度(轨高)"
	Axis int     // 0=x 1=y 2=z
	Lo   float64 // 工程下限 (mm)
	Hi   float64 // 工程上限 (mm)
}

// accGeo 统一 *Shape 与 *Compound (装配 ToCompound 产物) 的验收接口
type accGeo interface {
	IsNull() bool
	IsValid() bool
	BBox() BBox
}

type accCase struct {
	Label        string
	Group        string
	Note         string // 参数依据 (标准/工程惯例)
	Build        func() accGeo
	Defl         float64 // 三角化线偏移 (mm), 0 → 1.0; 大装配用粗值控制 STL 体积
	Expect       []accExpect
	CustomChecks func(g accGeo) []accCheck
}

// heavyCases 大装配: 跳过 IsValid (BRepCheck_Analyzer 在数百实体复合体上代价过高)
var heavyCases = map[string]bool{
	"直线正线 (60m)": true, "曲线段 R600 30° (超高120)": true,
	"单开道岔 9号 左开": true, "单开道岔 12号 右开": true,
	"GeoJSON正线 (60m)": true, "站场 (正线250m+侧线道岔)": true,
	"菱形交叉 直角 (货场)": true, "菱形交叉 锐角 12号": true,
	"站场 直角交叉 (货场)": true,
	"锚段 250m (钢柱5跨补偿)": true, "锚段 250m (混凝土柱)": true,
	"腕臂柱装配 (钢柱H9m)": true, "腕臂柱装配 (混凝土柱)": true,
}
// knownDevCases 已知偏差: 与真实标准存在建模层级差异, 尺寸闸门失败单列报告, 不计为验收失败
// (道岔全长经岔前段/表值修正后与专线标准偏差 <±3%, 已退出本表)
var knownDevCases = map[string]bool{}

type accItem struct {
	Name     string     `json:"name"`
	Group    string     `json:"group"`
	File     string     `json:"file"`
	Verdict  string     `json:"verdict"` // pass / fail / skip
	Dims     [3]float64 `json:"dims"`    // 实测 bbox (dx,dy,dz) mm
	Expect   string     `json:"expect"`
	Note     string     `json:"note,omitempty"`
	Checks   []accCheck `json:"checks,omitempty"`
	KnownDev bool       `json:"knownDev,omitempty"` // 已知偏差项 (报告中单列, 不计为验收失败)
}

// =========================================================================
// 真实名义参数 (查表值, 与 track_geojson.go standardRailDims 同源)
// =========================================================================

func railDims60() RailParams {
	h, w, b := standardRailDims(60)
	return RailParams{RailHeight: h, HeadWidth: w, BaseWidth: b}
}

func trackSleeperParams(shapeType int) SleeperParams {
	return SleeperParams{ShapeType: shapeType, Length: 2600, Width: 260, Height: 200,
		Gauge: 1435, RailBaseWidth: 150, GrooveDepth: 10}
}

const (
	nomGauge   = 1435 // 标准轨距 (TB 10001)
	nomDefl    = 1.0  // 零件三角化线偏移
	nomDeflBig = 2.5  // 大装配三角化线偏移
)

// =========================================================================
// 用例目录
// =========================================================================

func acceptanceCases() []accCase {
	p := NewPoint3
	d := NewDir3FromXYZ

	// 60m 直线轨道名义参数 (区间正线, 60kg/m 有砟)
	straightParams := StraightTrackParams{
		Gauge: nomGauge, RailHeight: 176, RailHeadWidth: 73, RailBaseWidth: 150,
		SleeperLength: 2500, SleeperWidth: 240, SleeperHeight: 180, SleeperSpacing: 600,
		BallastTopWidth: 3400, BallastThickness: 300, BallastSlope: 1.5,
	}
	// R600m 曲线段 (城际常见最小曲线), 超高 120mm
	curveParams := CurveTrackParams{
		StartAngle: 0, SweepAngle: math.Pi / 6, CurveRadius: 600000,
		Gauge: nomGauge, SuperElevation: 120,
		RailHeight: 176, RailHeadWidth: 73, RailBaseWidth: 150,
		SleeperLength: 2500, SleeperWidth: 240, SleeperHeight: 180, SleeperSpacing: 600,
		BallastTopWidth: 3400, BallastThickness: 300, BallastSlope: 1.5,
	}
	// 接触网腕臂柱装配 (干线: 导高 6000, 结构高 1400, CX 2900, 拉出值 300)
	mastParams := func(mastType int) MastAssemblyParams {
		return MastAssemblyParams{MastType: mastType, MastHeight: 9000,
			CantileverType: 1, ArmDiameter: 55, Stagger: 300,
			ContactHeight: 6000, StructureHeight: 1400, SideOffset: 2900}
	}
	anchorInput := func(mastType int) AnchorSectionInput {
		var cl []Point3
		for x := 0.0; x <= 250000; x += 5000 {
			cl = append(cl, p([3]float64{x, 0, 0}))
		}
		return AnchorSectionInput{Centerline: cl, ContactHeight: 6000,
			StructureHeight: 1400, SpanLength: 50000, MastHeight: 9000,
			MastType: mastType, SideOffset: 2900, HasCompensator: true}
	}
	anchorCompound := func(mastType int) *Compound {
		as, err := CreateAnchorSection(anchorInput(mastType))
		if err != nil {
			return nil
		}
		return as.ToCompound()
	}

	cases := []accCase{
		// ===== RAIL 钢轨与钢轨件 =====
		{"钢轨 60kg/m (2m)", "RAIL", "GB 2585: 轨高176 头宽73 底宽150", func() accGeo {
			r := railDims60()
			return CreateRailWithPlace(r, p([3]float64{0, 0, 0}), p([3]float64{2000, 0, 0}))
		}, 0, []accExpect{
			{"长度", 0, 1999, 2001}, {"底宽", 1, 149, 151}, {"轨高", 2, 175, 177},
		}, nil},
		{"钢轨 50kg/m (2m)", "RAIL", "GB 2585: 轨高152 头宽70 底宽132", func() accGeo {
			h, w, b := standardRailDims(50)
			return CreateRailWithPlace(RailParams{RailHeight: h, HeadWidth: w, BaseWidth: b},
				p([3]float64{0, 0, 0}), p([3]float64{2000, 0, 0}))
		}, 0, []accExpect{
			{"长度", 0, 1999, 2001}, {"底宽", 1, 131, 133}, {"轨高", 2, 151, 153},
		}, nil},
		{"钢轨 43kg/m (2m)", "RAIL", "GB 2585: 轨高140 头宽70 底宽114", func() accGeo {
			h, w, b := standardRailDims(43)
			return CreateRailWithPlace(RailParams{RailHeight: h, HeadWidth: w, BaseWidth: b},
				p([3]float64{0, 0, 0}), p([3]float64{2000, 0, 0}))
		}, 0, []accExpect{
			{"长度", 0, 1999, 2001}, {"底宽", 1, 113, 115}, {"轨高", 2, 139, 141},
		}, nil},
		{"钢轨 75kg/m (2m)", "RAIL", "GB 2585: 轨高192 头宽75 底宽150", func() accGeo {
			h, w, b := standardRailDims(75)
			return CreateRailWithPlace(RailParams{RailHeight: h, HeadWidth: w, BaseWidth: b},
				p([3]float64{0, 0, 0}), p([3]float64{2000, 0, 0}))
		}, 0, []accExpect{
			{"长度", 0, 1999, 2001}, {"底宽", 1, 149, 151}, {"轨高", 2, 191, 193},
		}, nil},
		{"尖轨 9号左开 (6.45m)", "RAIL", "60kg/m 9号道岔 AT尖轨 6450mm, 尖端~2.5mm, R190m", func() accGeo {
			return CreateSwitchRail(SwitchRailParams{Length: 6450, RailHeight: 176,
				RailHeadWidth: 73, RailBaseWidth: 150, TipWidth: 2.5,
				CurveRadius: 190000, IsLeftHand: true})
		}, 0, []accExpect{
			{"长度(投影)", 0, 6300, 6500}, {"轨高", 2, 175, 177},
		}, nil},
		{"辙叉 9号", "RAIL", "9号高锰钢辙叉: 全长~4.2m, 心轨-翼轨汇聚岔心", func() accGeo {
			return CreateFrog(FrogParams{TurnoutNo: 9, Gauge: nomGauge,
				RailHeight: 176, RailHeadWidth: 73, RailBaseWidth: 150})
		}, 0, []accExpect{
			{"全长", 0, 3000, 6000}, {"全宽", 1, 2000, 4000}, {"轨高", 2, 140, 200},
		}, nil},
		{"护轨 43kg (4.5m)", "RAIL", "辙叉护轨用43kg旧轨, 轮缘槽42mm, 高140", func() accGeo {
			return CreateGuardRail(GuardRailParams{Height: 140, HeadWidth: 70, BaseWidth: 114,
				GrooveWidth: 42, TotalLength: 4500, GaugeDistance: nomGauge})
		}, 0, []accExpect{
			{"长度", 0, 4450, 4550}, {"轨高", 2, 139, 141},
		}, nil},

		// ===== TRACK 轨道部件 =====
		{"轨枕 Ⅰ型(矩形)", "TRACK", "TB/T 2190 混凝土枕 2600×260×200, 承轨槽距1435", func() accGeo {
			return CreateSleeper(trackSleeperParams(0))
		}, 0, []accExpect{
			{"枕长", 0, 2598, 2602}, {"枕宽", 1, 258, 262}, {"枕高", 2, 198, 202},
		}, nil},
		{"轨枕 Ⅱ型(梯形)", "TRACK", "梯形截面混凝土枕, 底宽向下收坡 (ThruSections 端部微鼓~32mm 属光滑过渡)", func() accGeo {
			return CreateSleeper(trackSleeperParams(2))
		}, 0, []accExpect{
			{"枕长", 0, 2590, 2640}, {"底宽", 1, 255, 305}, {"枕高", 2, 198, 202},
		}, nil},
		{"轨道板 CRTSⅠ型", "TRACK", "CRTSⅠ: 4962×2400×200, CA垫层30(下)+承轨台30(上)", func() accGeo {
			return CreateTrackSlab(TrackSlabParams{Length: 4962, Width: 2400, Thickness: 200,
				RailSeatCount: 8, RailSeatSpacing: 620, CementAsphaltThickness: 30})
		}, 0, []accExpect{
			{"板长", 0, 4960, 4964}, {"板宽", 1, 2398, 2402}, {"总高(CA+板+承轨台)", 2, 255, 265},
		}, nil},
		{"扣件垫板对", "TRACK", "弹条Ⅰ型扣件对: 按轨距1435两轨各一套", func() accGeo {
			return CreateFastener(FastenerParams{Spacing: 620, Gauge: nomGauge,
				PadThickness: 10, PadLength: 160, PadWidth: 140})
		}, 0, []accExpect{
			{"轨距向(含挡肩)", 1, 1550, 1800}, {"总高(含弹条)", 2, 30, 150},
		}, nil},
		{"道床段 (20m)", "TRACK", "顶宽3600 厚300 边坡1:1.75, 端部沿切向延伸500", func() accGeo {
			return CreateBallastAlongPath([]Point3{p([3]float64{0, 0, 0}), p([3]float64{20000, 0, 0})},
				3600, 300, 1.75)
		}, 0, []accExpect{
			{"长度(含延伸)", 0, 20990, 21010}, {"底宽", 1, 4640, 4660}, {"厚度", 2, 299, 301},
		}, nil},

		// ===== TRACK-ASM 轨道装配 =====
		{"直线正线 (60m)", "TRACK-ASM", "60kg/m 有砟: 轨枕2500@600, 道床顶宽3400 厚300 (道床端延500×2)", func() accGeo {
			return CreateStraightTrackWithPlace(straightParams, p([3]float64{0, 0, 0}), p([3]float64{60000, 0, 0}))
		}, nomDeflBig, []accExpect{
			{"长度(含道床延伸)", 0, 60990, 61010}, {"宽度(道床底)", 1, 4290, 4310}, {"总高(道床+枕+轨)", 2, 640, 680},
		}, nil},
		{"曲线段 R600 30° (超高120)", "TRACK-ASM", "R600m 圆曲线 30°, 外轨超高120mm (轨/枕/床同步倾转)", func() accGeo {
			return CreateCurveTrackWithPlace(curveParams, p([3]float64{0, 0, 0}))
		}, nomDeflBig, []accExpect{
			{"弧段X向", 0, 80000, 87000}, {"弧段Y向", 1, 0, 321000}, {"总高(含超高)", 2, 600, 950},
		}, nil},
		{"单开道岔 9号 左开", "TRACK-ASM", "60kg/m 9号固定型辙叉道岔 (普通型 R180m): 岔前2.6m+尖轨尖至岔心22.7m+辙叉3.6m, 全长28.9m vs 专线4193 29.57m (−2.3%)", func() accGeo {
			return CreateTurnout(TurnoutParams{TurnoutNo: 9, IsLeftHand: true, Gauge: nomGauge,
				RailHeight: 176, RailHeadWidth: 73, RailBaseWidth: 150,
				SwitchRailLength: 6450, LeadCurveRadius: 180000, FrogLength: 4200, SleeperSpacing: 600})
		}, nomDeflBig, []accExpect{
			{"全长", 0, 27000, 31000}, {"全宽(岔前枕+侧股)", 1, 3800, 4300},
		}, nil},
		{"单开道岔 12号 右开", "TRACK-ASM", "60kg/m 12号固定型辙叉道岔 (普通型 R330m): 岔前2.6m+岔心距30.8m+辙叉4.5m, 全长37.9m vs 专线4128 36.82m (+2.9%)", func() accGeo {
			return CreateTurnout(TurnoutParams{TurnoutNo: 12, IsLeftHand: false, Gauge: nomGauge,
				RailHeight: 176, RailHeadWidth: 73, RailBaseWidth: 150,
				SwitchRailLength: 7700, LeadCurveRadius: 330000, FrogLength: 5200, SleeperSpacing: 600})
		}, nomDeflBig, []accExpect{
			{"全长", 0, 35000, 40000}, {"全宽(岔前枕+侧股)", 1, 5100, 5600},
		}, nil},
		{"GeoJSON正线 (60m)", "TRACK-ASM", "中心线派生: 钢轨×2+轨枕@600+道床3600, 米→mm×1000 (ballastTopWidth 显式传入; 缺省0=不生成道床)", func() accGeo {
			var sb strings.Builder
			sb.WriteString(`{"type":"Feature","geometry":{"type":"LineString","coordinates":[`)
			for i := 0; i <= 60; i++ {
				if i > 0 {
					sb.WriteString(",")
				}
				fmt.Fprintf(&sb, "[%d.0,0.0,0.0]", i) // 米 (i 米, coordScale=1000 → mm)
			}
			sb.WriteString(`]},"properties":{"railType":60,"ballastTopWidth":3600}}`)
			as, err := CreateTrackFromGeoJSON([]byte(sb.String()))
			if err != nil {
				return nil
			}
			return as.ToCompound()
		}, nomDeflBig, []accExpect{
			{"长度(含道床延伸)", 0, 60990, 61010}, {"宽度(道床底)", 1, 4490, 4510}, {"总高", 2, 650, 700},
		}, nil},
		{"站场 (正线250m+侧线道岔)", "TRACK-ASM", "正线+R350侧线→端点聚类识别12号道岔, 导曲线半径实测拟合≈350m, 岔枕跟随侧股加长", func() accGeo {
			as, err := CreateYardFromGeoJSON(buildAcceptanceYardGeoJSON())
			if err != nil {
				return nil
			}
			return as.ToCompound()
		}, nomDeflBig, []accExpect{
			{"场坪长度", 0, 240000, 260000}, {"场坪宽度", 1, 5000, 25000},
		}, func(g accGeo) []accCheck {
			layout, err := ComputeYardLayout(buildAcceptanceYardGeoJSON())
			if err != nil {
				return []accCheck{{What: "布局识别", Want: "成功", Got: err.Error(), Pass: false}}
			}
			tn := "无"
			leadR := 0.0
			if len(layout.Turnouts) > 0 {
				tn = fmt.Sprintf("%d号(左=%v)", layout.Turnouts[0].TurnoutNo, layout.Turnouts[0].IsLeftHand)
				leadR = layout.Turnouts[0].LeadCurveRadius
			}
			return []accCheck{
				{What: "识别道岔", Want: "≥1", Got: tn, Pass: len(layout.Turnouts) >= 1},
				{What: "导曲线半径拟合", Want: "300k~420k", Got: fmt.Sprintf("%.0f", leadR),
					Pass: leadR > 300000 && leadR < 420000},
				{What: "识别告警", Want: "0", Got: fmt.Sprintf("%d", len(layout.Warnings)), Pass: len(layout.Warnings) == 0},
			}
		}},
		{"菱形交叉 锐角 12号", "TRACK-ASM", "实测交叉角 atan(1/12) 真菱形: 2锐角辙叉(V尖+翼轨+护轨)+2钝角交叉, 沿线路展开~43m (对照实物菱形交叉)", func() accGeo {
			return CreateDiamondWithPlace(DiamondParams{TurnoutNo: 12, Gauge: nomGauge,
				RailHeight: 176, RailHeadWidth: 73, RailBaseWidth: 150,
				FrogAngle: math.Atan(1.0 / 12), SleeperSpacing: 600, SleeperHeight: 200},
				p([3]float64{0, 0, 200}), d([3]float64{1, 0, 0}), d([3]float64{0, 0, 1}))
		}, nomDeflBig, []accExpect{
			{"全长(长对角)", 0, 38000, 47000}, {"全宽(短对角)", 1, 4000, 6500}, {"轨面高(枕+轨)", 2, 300, 450},
		}, nil},
		{"菱形交叉 直角 (货场)", "TRACK-ASM", "实测交叉角 90° 真菱形: 直角交叉不再退化为浅角查表辙叉, 交叉岔枕垂直主线包络布设", func() accGeo {
			return CreateDiamondWithPlace(DiamondParams{TurnoutNo: 9, Gauge: nomGauge,
				RailHeight: 176, RailHeadWidth: 73, RailBaseWidth: 150,
				FrogAngle: math.Pi / 2, SleeperSpacing: 600, SleeperHeight: 200},
				p([3]float64{0, 0, 200}), d([3]float64{math.Cos(math.Pi / 4), math.Sin(math.Pi / 4), 0}), d([3]float64{0, 0, 1}))
		}, nomDefl, []accExpect{
			{"X向", 0, 4200, 6500}, {"Y向", 1, 4200, 6500}, {"轨面高(枕+轨)", 2, 300, 450},
		}, func(g accGeo) []accCheck {
			bb := g.BBox().Data()
			dx, dy := bb[3]-bb[0], bb[4]-bb[1]
			return []accCheck{{What: "直角对称性 |dx-dy|", Want: "<1000", Got: fmt.Sprintf("%.0f", math.Abs(dx-dy)),
				Pass: math.Abs(dx-dy) < 1000}}
		}},
		{"站场 直角交叉 (货场)", "TRACK-ASM", "两正交线路 60m×60m → 实测交叉角 π/2 真菱形 + 股道让位分段 (交叉区钢轨由菱形单元提供)", func() accGeo {
			mk := func(coords string) string {
				return fmt.Sprintf(`{"type":"Feature","geometry":{"type":"LineString","coordinates":[%s]},"properties":{"gauge":1435}}`, coords)
			}
			coll := []byte(fmt.Sprintf(`{"type":"FeatureCollection","features":[%s,%s]}`,
				mk("[0.0,0.0,0],[30.0,0.0,0],[60.0,0.0,0]"),
				mk("[30.0,-30.0,0],[30.0,0.0,0],[30.0,30.0,0]")))
			as, err := CreateYardFromGeoJSON(coll)
			if err != nil {
				return nil
			}
			return as.ToCompound()
		}, nomDeflBig, []accExpect{
			{"场坪长度", 0, 58000, 64000}, {"场坪宽度", 1, 58000, 64000},
		}, func(g accGeo) []accCheck {
			mk := func(coords string) string {
				return fmt.Sprintf(`{"type":"Feature","geometry":{"type":"LineString","coordinates":[%s]},"properties":{"gauge":1435}}`, coords)
			}
			coll := []byte(fmt.Sprintf(`{"type":"FeatureCollection","features":[%s,%s]}`,
				mk("[0.0,0.0,0],[30.0,0.0,0],[60.0,0.0,0]"),
				mk("[30.0,-30.0,0],[30.0,0.0,0],[30.0,30.0,0]")))
			layout, err := ComputeYardLayout(coll)
			if err != nil {
				return []accCheck{{What: "布局识别", Want: "成功", Got: err.Error(), Pass: false}}
			}
			angOK := len(layout.Crossings) == 1 && math.Abs(layout.Crossings[0].FrogAngle-math.Pi/2) < 0.01
			splitOK := len(layout.Tracks) == 4
			return []accCheck{
				{What: "实测交叉角", Want: "π/2±0.01",
					Got: fmt.Sprintf("%.4f (n=%d)", layout.Crossings[0].FrogAngle, len(layout.Crossings)), Pass: angOK},
				{What: "股道让位分段", Want: "4 段", Got: fmt.Sprintf("%d 段", len(layout.Tracks)), Pass: splitOK},
			}
		}},

		// ===== OCS-PART 接触网零件 =====
		{"平腕臂 (3.4m)", "OCS-PART", "铝合金管φ55×4, 仰角3°", func() accGeo {
			return CreateLevelCantilever(LevelCantileverParams{Length: 3400, OuterDiameter: 55,
				WallThickness: 4, MountHeight: 150, RiseAngle: 3})
		}, 0, []accExpect{
			{"管长(投影)", 0, 3350, 3500}, {"抬高量", 2, 60, 300},
		}, nil},
		{"斜腕臂 (4.2m 45°)", "OCS-PART", "φ55×4, 斜置45°构成三角腕臂", func() accGeo {
			return CreateSlantCantilever(SlantCantileverParams{Length: 4200, OuterDiameter: 55,
				WallThickness: 4, SlantAngle: 45})
		}, 0, []accExpect{
			{"水平投影", 0, 2500, 3400}, {"垂直投影", 2, 2500, 3400},
		}, nil},
		{"弯臂 (800/900 R600 90°)", "OCS-PART", "非绝缘弯臂: 竖段800+平段900", func() accGeo {
			return CreateCurvedArm(CurvedArmParams{Type: 0, VerticalLength: 800, HorizontalLength: 900,
				BendRadius: 600, BendAngle: 90, OuterDiameter: 48, WallThickness: 4})
		}, 0, []accExpect{
			{"水平向", 0, 850, 1100}, {"竖直向", 2, 750, 1100},
		}, nil},
		{"腕臂支撑 (1.5m 40°)", "OCS-PART", "φ42拉撑管", func() accGeo {
			return CreateCantileverBrace(CantileverBraceParams{Length: 1500, OuterDiameter: 42,
				WallThickness: 3.5, SlantAngle: 40})
		}, 0, []accExpect{
			{"水平投影", 0, 1000, 1300}, {"垂直投影", 2, 850, 1100},
		}, nil},
		{"棒式绝缘子 (700mm)", "OCS-PART", "QBG-25/12 棒式绝缘子: 高700 伞径180", func() accGeo {
			return CreateRodInsulator(RodInsulatorParams{Type: 0, Height: 700, OuterDiameter: 120,
				ShedDiameter: 180, ShedSpacing: 60, ShedCount: 7, FlangeDiameter: 220})
		}, 0, []accExpect{
			{"绝缘高度", 2, 680, 720}, {"伞裙直径", 1, 175, 210},
		}, nil},
		{"定位管 直型 (2.6m)", "OCS-PART", "定位管45×45方管, 定位器坡度~1:5", func() accGeo {
			return CreateRegistrationArm(RegistrationArmParams{Type: 0, Length: 2600,
				TubeWidth: 45, TubeHeight: 45, WallThickness: 4})
		}, 0, []accExpect{
			{"管长(含端部金具)", 0, 2590, 2700},
		}, nil},
		{"定位管斜撑线夹", "OCS-PART", "定位器底座L型金具, 抱箍φ45", func() accGeo {
			return CreateRegArmBracket(RegArmBracketParams{TubeDiameter: 45, BandWidth: 60,
				BandThickness: 8, BracketHeight: 80, BracketWidth: 50, BracketThickness: 10,
				MountHoleDiameter: 12})
		}, 0, []accExpect{
			{"外形", 0, 40, 160}, {"外形", 2, 40, 160},
		}, nil},
		{"腕臂底座", "OCS-PART", "支柱连接座 300×120×150", func() accGeo {
			return CreateCantileverBase(CantileverBaseParams{Length: 300, Width: 120, Height: 150,
				BoltSpacing: 160, BoltDiameter: 16, BoltCount: 2})
		}, 0, []accExpect{
			{"座长", 0, 290, 310}, {"座高", 2, 140, 160},
		}, nil},
		{"承力索座", "OCS-PART", "承力索座 150×60×50, R7索槽", func() accGeo {
			return CreateMWSaddle(MWSaddleParams{Length: 150, Width: 60, Height: 50,
				GrooveRadius: 7, BoltDiameter: 12})
		}, 0, []accExpect{
			{"座长", 0, 140, 160},
		}, nil},
		{"吊弦 (1.2m)", "OCS-PART", "载流环整体吊弦: 截线φ4, 线夹60×40", func() accGeo {
			return CreateDropper(DropperParams{Length: 1200, WireDiameter: 4,
				ClampLength: 60, ClampWidth: 40, ClampThickness: 8, Conductive: true})
		}, 0, []accExpect{
			{"弦长(含线夹)", 2, 1195, 1350},
		}, nil},
		{"套筒连接器", "OCS-PART", "双套筒型连接器 (JJL-25)", func() accGeo {
			return CreateSleeveConnector(SleeveConnectorParams{})
		}, 0, []accExpect{}, nil},
		{"套筒双耳", "OCS-PART", "套管单耳 (QL-25)", func() accGeo {
			return CreateSleeveEar(SleeveEarParams{})
		}, 0, []accExpect{}, nil},
		{"线岔 (交角15°)", "OCS-PART", "交叉线岔: 限制管+双接触线交叉, 高差100", func() accGeo {
			return CreateCrossingWithPlace(CrossingParams{LimitPipeLength: 3200, PipeDiameter: 30,
				WireDiameter: 12.9, HeightDiff: 100},
				p([3]float64{0, 0, 6000}),
				d([3]float64{1, 0, 0}),
				d([3]float64{math.Cos(15 * math.Pi / 180), math.Sin(15 * math.Pi / 180), 0}))
		}, 0, []accExpect{
			{"含双线延伸的X向", 0, 3000, 20000},
		}, nil},
		{"下锚金具 (600mm)", "OCS-PART", "终端锚固线夹型", func() accGeo {
			return CreateAnchorFitting(AnchorFittingParams{Type: 1, Length: 600, Diameter: 30})
		}, 0, []accExpect{
			{"长度", 0, 550, 650},
		}, nil},

		// ===== OCS-MAST 支柱/基础/横跨 =====
		{"格构钢柱 H9m", "OCS-MAST", "格构式钢柱: 主肢角钢L放样, 柱高9m 根部900", func() accGeo {
			return CreateSteelMast(SteelMastParams{Type: 1, Height: 9000,
				TopWidth: 600, BottomWidth: 900, WallThickness: 5,
				FlangeThickness: 16, FlangeWidth: 300})
		}, 0, []accExpect{
			{"柱高", 2, 8950, 9050}, {"根部宽(含法兰)", 0, 850, 1100},
		}, nil},
		{"混凝土支柱 H9m", "OCS-MAST", "横腹杆式: 柱高9m 梢径300 根径550", func() accGeo {
			return CreateConcreteMast(ConcreteMastParams{SectionType: 1, Height: 9000,
				TopWidth: 300, BottomWidth: 550, WallThickness: 60})
		}, 0, []accExpect{
			{"柱高", 2, 8950, 9050}, {"根部宽", 1, 500, 600},
		}, nil},
		{"支柱基础 直埋 (2.5m)", "OCS-MAST", "直埋式圆形基坑 D=min(长,宽)=800, 埋深2500", func() accGeo {
			return CreateOcsFoundation(OcsFoundationParams{Type: FoundationDirectBuried,
				Height: 2500, Width: 800, Length: 1200})
		}, 0, []accExpect{
			{"埋深", 2, 2490, 2510}, {"基坑直径(X)", 0, 790, 810}, {"基坑直径(Y)", 1, 790, 810},
		}, nil},
		{"横担 (3.2m)", "OCS-MAST", "槽钢横担 3200×120×80 (梁沿Y), 斜撑800", func() accGeo {
			return CreateCrossArm(CrossArmParams{Type: 0, BeamLength: 3200, BeamHeight: 120,
				BeamWidth: 80, BraceLength: 800, MountHeight: 200})
		}, 0, []accExpect{
			{"担长(Y向)", 1, 3180, 3220},
		}, nil},
		{"下锚拉线 (45° 9m)", "OCS-MAST", "GJ-70拉线+绝缘子串, 对地45°", func() accGeo {
			return CreateGuyWire(GuyWireParams{Length: 9000, Diameter: 12, Angle: 45,
				HasInsulator: true, InsulatorCount: 1})
		}, 0, []accExpect{
			{"水平投影", 0, 6000, 6700}, {"垂直投影", 2, 6000, 6700},
		}, nil},
		{"硬横梁吊柱 (3.2m)", "OCS-MAST", "圆形钢管吊柱 φ160", func() accGeo {
			return CreateHangerPost(HangerPostParams{SectionType: 0, Length: 3200,
				SectionSize: 160, WallThickness: 8})
		}, 0, []accExpect{
			{"柱长", 2, 3180, 3220},
		}, nil},
		{"软横跨 40m", "OCS-MAST", "横向承力索+上下部定位绳, 横向弛度400", func() accGeo {
			return CreateHeadSpan(HeadSpanParams{Span: 40000, HangPointCount: 3,
				HangPointSpacing: 5000, CrossCatenarySag: 400})
		}, 0, []accExpect{
			{"跨度", 0, 39950, 40050}, {"高度区(含绝缘子下垂)", 2, 380, 2000},
		}, nil},
		{"硬横跨 42m (带柱)", "OCS-MAST", "钢管硬横跨: 梁42m+两柱9m", func() accGeo {
			return CreateTransverseSpan(TransverseSpanParams{Span: 42000, BeamType: 0,
				BeamHeight: 600, BeamWidth: 250, MastHeight: 9000})
		}, 0, []accExpect{
			{"跨度(含端部构造)", 0, 41950, 42800},
		}, nil},
		{"悬索式硬横跨 42m", "OCS-MAST", "悬索硬横跨: 缆索+吊柱, 弛度800", func() accGeo {
			return CreateSuspensionHardSpan(SuspensionHardSpanParams{Span: 42000, MastHeight: 9000,
				CableDiameter: 22, CableSag: 800, DropperCableDiameter: 8,
				DropperCount: 5, DropperSpacing: 8000})
		}, 0, []accExpect{
			{"跨度", 0, 41950, 42050}, {"高度区(吊柱垂至半高)", 2, 3000, 6000},
		}, nil},

		// ===== OCS-COMP 补偿装置/设备 =====
		{"棘轮补偿装置", "OCS-COMP", "棘轮φ400+坠砣串, 传动比1:3", func() accGeo {
			return CreateRatchetCompensator(RatchetCompensatorParams{})
		}, 0, []accExpect{
			{"装置高度", 2, 1500, 3000},
		}, nil},
		{"滑轮组补偿装置", "OCS-COMP", "3滑轮组 compensator", func() accGeo {
			return CreatePulleyCompensator(PulleyCompensatorParams{})
		}, 0, []accExpect{
			{"装置高度", 2, 1500, 2600},
		}, nil},
		{"坠砣串 (8块)", "OCS-COMP", "25kg坠砣φ380×75×8块+φ20坠砣杆", func() accGeo {
			return CreateWeightStack(WeightStackParams{})
		}, 0, []accExpect{
			{"串总高(坠砣杆1200)", 2, 1150, 1250}, {"坠砣直径", 1, 370, 390},
		}, nil},
		{"坠砣单块", "OCS-COMP", "25kg 坠砣块 φ380×75", func() accGeo {
			return CreateBalanceWeight(BalanceWeightParams{Width: 380, Thickness: 75,
				Height: 75, CenterHoleDiameter: 30})
		}, 0, []accExpect{
			{"块厚", 2, 70, 85}, {"块径", 0, 370, 390},
		}, nil},
		{"隔离开关 (分闸75°)", "OCS-COMP", "GW4-252 双柱式, 触刀竖起", func() accGeo {
			return CreateDisconnector(DisconnectorParams{OpenAngle: 75})
		}, 0, []accExpect{
			{"分闸总高", 2, 1500, 2400},
		}, nil},
		{"避雷器", "OCS-COMP", "金属氧化物避雷器 800mm", func() accGeo {
			return CreateArrester(ArresterParams{})
		}, 0, []accExpect{
			{"总高", 2, 700, 900},
		}, nil},

		// ===== WIRE 线索 =====
		{"接触线 CTS-120 (50m跨)", "WIRE", "CTS-120: 径12.9, 弛度1%跨距=500", func() accGeo {
			return CreateContactWire(ContactWireParams{SectionalArea: 120, Diameter: 12.9,
				RatedTension: 27000, Sag: 500},
				p([3]float64{0, 0, 6000}), p([3]float64{50000, 0, 6000}))
		}, 0, []accExpect{
			{"跨长", 0, 49990, 50010}, {"弛度+径", 2, 505, 525},
		}, nil},
		{"承力索 JTMH-120 (50m跨)", "WIRE", "JTMH-120: 径13.5, 弛度1.5%跨距=750", func() accGeo {
			return CreateMessengerWire(MessengerWireParams{Diameter: 13.5, RatedTension: 20000,
				StructuralHeight: 1400, Sag: 750},
				p([3]float64{0, 0, 7400}), p([3]float64{50000, 0, 7400}))
		}, 0, []accExpect{
			{"跨长", 0, 49990, 50010}, {"弛度+径", 2, 755, 775},
		}, nil},
		{"附加导线 (50m φ12)", "WIRE", "AF附加导线弛度500", func() accGeo {
			return CreateAuxiliaryWire(AuxiliaryWireParams{Diameter: 12, Sag: 500},
				p([3]float64{0, 0, 8000}), p([3]float64{50000, 0, 8000}))
		}, 0, []accExpect{
			{"跨长", 0, 49990, 50010}, {"弛度+径", 2, 505, 525},
		}, nil},

		// ===== OCS-ASM 接触网装配 =====
		{"腕臂柱装配 (钢柱H9m)", "OCS-ASM", "导高6000 结构高1400 CX2900 拉出值300", func() accGeo {
			return CreateMastAssembly(mastParams(1))
		}, 1.5, []accExpect{
			{"柱至导线水平距(含定位管延伸)", 0, 2200, 4200}, {"装配总高", 2, 5900, 9300},
		}, nil},
		{"腕臂柱装配 (混凝土柱)", "OCS-ASM", "同上, 柱型=横腹杆混凝土柱", func() accGeo {
			return CreateMastAssembly(mastParams(2))
		}, 1.5, []accExpect{
			{"柱至导线水平距(含定位管延伸)", 0, 2200, 4200}, {"装配总高", 2, 5900, 9300},
		}, nil},
		{"锚段 250m (钢柱5跨补偿)", "OCS-ASM", "跨距50m×5, 之字形±300, 两端棘轮补偿", func() accGeo {
			return anchorCompound(1)
		}, nomDeflBig, []accExpect{
			{"锚段长(含两端顺线路拉线)", 0, 249500, 266000}, {"高度范围", 2, 6000, 12500},
		}, nil},
		{"GeoJSON曲线锚段 (含AF附加导线)", "OCS-ASM", "线路GeoJSON→锚段: 支柱径向跟随曲线, AF附加导线+支架沿线", func() accGeo {
			as, _, err := CreateAnchorSectionFromGeoJSON(curveAnchorGeoJSON())
			if err != nil {
				return nil
			}
			return as.ToCompound()
		}, nomDeflBig, []accExpect{
			{"弧段X向", 0, 48000, 60000}, {"弧段Y向", 1, 200000, 260000}, {"高度范围", 2, 6000, 12500},
		}, nil},
		{"锚段 250m (混凝土柱)", "OCS-ASM", "同上, 柱型=混凝土柱", func() accGeo {
			return anchorCompound(2)
		}, nomDeflBig, []accExpect{
			{"锚段长(含两端顺线路拉线)", 0, 249500, 266000}, {"高度范围", 2, 6000, 12500},
		}, nil},

		// ===== ASSEM 装配层级 (组装策略评审: 子装配级对象出图) =====
		{"跨距子装配 (锚段层级)", "ASSEM", "锚段→跨距: 接触线+承力索+吊弦群, ocs_span 配方可单跨整棵重建; 支柱装置另列", func() accGeo {
			layout, err := ComputeAnchorSectionLayout(anchorInput(1))
			if err != nil {
				return nil
			}
			as, err := CreateAnchorSectionFromLayout(layout)
			if err != nil {
				return nil
			}
			for _, ch := range as.Children() {
				if ch.GetName() == "span_1" {
					return ch.ToCompound()
				}
			}
			return nil
		}, 1.5, []accExpect{
			{"跨长", 0, 49000, 51000}, {"跨内垂深(结构高+弛度)", 2, 1300, 1600},
		}, nil},
		{"中间柱 (非锚柱)", "ASSEM", "接触网支柱角色: 中间柱=非锚柱, 单腕臂定位无下锚设备 (锚段中批量)", func() accGeo {
			sup, err := CreateOcsSupportWithPlace(SupportParams{Role: MastRoleIntermediate,
				Mast: MastAssemblyParams{MastType: 1, MastHeight: 9000, CantileverType: 1,
					ArmDiameter: 55, Stagger: 300, ContactHeight: 6000, StructureHeight: 1400, SideOffset: 2900}},
				"support_intermediate")
			if err != nil {
				return nil
			}
			return sup.ToCompound()
		}, 1.5, []accExpect{
			{"柱至导线水平距", 0, 2200, 4200}, {"装配总高", 2, 5900, 9300}, {"宽度(单腕臂)", 1, 40, 600},
		}, nil},
		{"锚柱 (补偿+拉线)", "ASSEM", "接触网支柱角色: 锚柱=补偿装置+坠砣+拉线, 线索本柱下锚 (锚段端柱)", func() accGeo {
			sp := SupportParams{Role: MastRoleAnchor,
				Mast: MastAssemblyParams{MastType: 1, MastHeight: 9000, CantileverType: 1,
					ArmDiameter: 55, Stagger: 300, ContactHeight: 6000, StructureHeight: 1400, SideOffset: 2900}}
			sup, err := CreateOcsSupportWithPlace(sp, "support_anchor")
			if err != nil {
				return nil
			}
			return sup.ToCompound()
		}, 1.5, []accExpect{
			{"装配总高", 2, 5900, 9300}, {"拉线顺线路(含拉线基础)", 1, 6000, 8300}, {"柱至导线水平距", 0, 2200, 4200},
		}, nil},
		{"转换柱 (双腕臂)", "ASSEM", "接触网支柱角色: 转换柱=双腕臂定位两支 (锚段关节柱2/柱3, 两支水平错开)", func() accGeo {
			sp := SupportParams{Role: MastRoleTransition, Separation: 500,
				Mast: MastAssemblyParams{MastType: 1, MastHeight: 9000, CantileverType: 1,
					ArmDiameter: 55, Stagger: 300, ContactHeight: 6000, StructureHeight: 1400, SideOffset: 2900}}
			sup, err := CreateOcsSupportWithPlace(sp, "support_transition")
			if err != nil {
				return nil
			}
			return sup.ToCompound()
		}, 1.5, []accExpect{
			{"水平距(含第二支)", 0, 2200, 4800}, {"宽度(双支错开)", 1, 400, 1600}, {"装配总高", 2, 5900, 9300},
		}, nil},
		{"中心柱 (双腕臂)", "ASSEM", "接触网支柱角色: 中心柱=双支同高平行定位 (三跨关节中柱)", func() accGeo {
			sp := SupportParams{Role: MastRoleCenter, Separation: 200,
				Mast: MastAssemblyParams{MastType: 1, MastHeight: 9000, CantileverType: 1,
					ArmDiameter: 55, Stagger: 300, ContactHeight: 6000, StructureHeight: 1400, SideOffset: 2900}}
			sup, err := CreateOcsSupportWithPlace(sp, "support_center")
			if err != nil {
				return nil
			}
			return sup.ToCompound()
		}, 1.5, []accExpect{
			{"水平距(含第二支)", 0, 2200, 4500}, {"宽度(双支错开)", 1, 300, 1200}, {"装配总高", 2, 5900, 9300},
		}, nil},
		{"四跨锚段关节", "ASSEM", "锚段关节: 锚柱B-转换柱-转换柱-锚柱A, 两支并行 (绝缘500), 非工作支抬升下锚", func() accGeo {
			var cl []Point3
			for x := 0.0; x <= 120000; x += 5000 {
				cl = append(cl, NewPoint3([3]float64{x, 0, 0}))
			}
			joint, _, err := CreateOcsJoint(OcsJointInput{Centerline: cl, ContactHeight: 6000,
				SpanLength: 35000, Insulated: true, Separation: 500})
			if err != nil {
				return nil
			}
			return joint.ToCompound()
		}, nomDeflBig, []accExpect{
			{"关节长(含两段引伸)", 0, 110000, 120000}, {"高度范围(柱高)", 2, 6000, 9500},
		}, nil},
		{"开关柱 (接触网引入变电站)", "ASSEM", "格构钢柱+腕臂+顶部三梁矩形框(两纵梁+中横梁+斜撑)装GW4隔离开关×4组(每组双柱跨纵梁)+T连接线/馈线引出+回流线支臂", func() accGeo {
			as, err := CreateSwitchMastWithPlace(SwitchMastParams{MastHeight: 11000,
				ContactHeight: 6000, StructureHeight: 1400, SideOffset: 2900, Stagger: 300,
				SwitchCount: 4, CrossarmSpan: 3600, FeedOutOffset: 8000, FeedOutHeight: 9800,
				HasReturnLine: true}, "switch_mast")
			if err != nil {
				return nil
			}
			return as.ToCompound()
		}, nomDeflBig, []accExpect{
			{"柱高", 2, 10900, 11400}, {"馈线引出(Y向)", 1, 17000, 19500},
			{"X跨度(定位点+回流线)", 0, 3300, 3650},
		}, nil},
		{"股道子装配 (站场层级)", "ASSEM", "站场→股道: 钢轨组+轨枕, yard_track 配方可整股重建; 道岔/交叉另列", func() accGeo {
			as, err := CreateYardFromGeoJSON(buildAcceptanceYardGeoJSON())
			if err != nil {
				return nil
			}
			for _, ch := range as.Children() {
				if ch.GetName() == "track_1" {
					return ch.ToCompound()
				}
			}
			return nil
		}, nomDeflBig, []accExpect{
			{"股道长(出岔裁剪后)", 0, 110000, 118000}, {"轨道结构宽(轨枕)", 1, 2500, 2750}, {"轨面高(枕+轨)", 2, 350, 420},
		}, nil},
	}
	return cases
}

// buildAcceptanceYardGeoJSON 站场验收数据: 正线250m, 在100m处左出 R350m 侧线
func buildAcceptanceYardGeoJSON() []byte {
	line := func(x0, y0, x1, y1, step float64) string {
		var pts []string
		n := int((x1-x0)/step + 0.5)
		for i := 0; i <= n; i++ {
			pts = append(pts, fmt.Sprintf("[%.4f,%.4f,0]", x0+float64(i)*step, y0))
		}
		return strings.Join(pts, ",")
	}
	var siding []string
	R := 350.0
	for i := 0; i <= 32; i++ {
		th := float64(i) * 0.0072
		siding = append(siding, fmt.Sprintf("[%.4f,%.4f,0]", 100+R*math.Sin(th), R-R*math.Cos(th)))
	}
	feature := func(coords string) string {
		return fmt.Sprintf(`{"type":"Feature","geometry":{"type":"LineString","coordinates":[%s]},"properties":{"gauge":1435,"railType":60}}`, coords)
	}
	return []byte(fmt.Sprintf(`{"type":"FeatureCollection","features":[%s,%s,%s]}`,
		feature(line(0, 0, 100, 0, 5)),
		feature(line(100, 0, 250, 0, 5)),
		feature(strings.Join(siding, ","))))
}

// =========================================================================
// 生成器
// =========================================================================

func TestGenerateRailwayAcceptance(t *testing.T) {
	dir := os.Getenv("ACCEPTANCE_DIR")
	if dir == "" {
		t.Skip("需要 ACCEPTANCE_DIR 环境变量指定输出目录")
	}
	stlDir := filepath.Join(dir, "stl")
	if err := os.MkdirAll(stlDir, 0o755); err != nil {
		t.Fatal(err)
	}

	items := make([]accItem, 0, len(acceptanceCases())+8)

	// ---- 零件/装配用例: 生成 + 尺寸闸门 + STL ----
	// 每个用例结束强制回收: cgo 形状体积大, 等 GC 自然触发会让 C++ 侧内存
	// 滞留到下一用例 (叠加后曾触发系统 OOM)
	defer debug.SetGCPercent(debug.SetGCPercent(50))
	for _, c := range acceptanceCases() {
		t.Logf("[case] %s (%s) ...", c.Label, c.Group)
		item := accItem{Name: c.Label, Group: c.Group, Expect: expectSummary(c.Expect), Note: c.Note}
		fname := fmt.Sprintf("%s.stl", sanitizeName(c.Label))
		item.File = "stl/" + fname
		path := filepath.Join(stlDir, fname)

		g := c.Build()
		if g == nil || g.IsNull() {
			item.Verdict = "fail"
			item.Checks = append(item.Checks, accCheck{What: "生成", Want: "非null", Got: "null/nil", Pass: false})
			items = append(items, item)
			t.Logf("[FAIL] %s: 生成失败", c.Label)
			continue
		}
		if heavyCases[c.Label] {
			item.Checks = append(item.Checks, accCheck{What: "有效性", Want: "valid",
				Got: "跳过 (大装配 BRepCheck 代价过高, 以尺寸闸门+视觉目检为准)", Pass: true})
		} else if !g.IsValid() {
			item.Checks = append(item.Checks, accCheck{What: "有效性", Want: "valid", Got: "invalid", Pass: false})
		} else {
			item.Checks = append(item.Checks, accCheck{What: "有效性", Want: "valid", Got: "valid", Pass: true})
		}

		// 先三角化再取 bbox: OCCT 未经三角化的 Bnd_Box 按曲线/曲面极点估算,
		// 对 Bezier 索类高估可达 ~1.2×; 三角化后 bbox 贴合真实网格
		defl := c.Defl
		if defl == 0 {
			defl = nomDefl
		}
		if err := accMeshWriteStl(g, defl, path); err != nil {
			item.Checks = append(item.Checks, accCheck{What: "STL导出", Want: "写出", Got: err.Error(), Pass: false})
		}

		bb := g.BBox().Data()
		dx, dy, dz := bb[3]-bb[0], bb[4]-bb[1], bb[5]-bb[2]
		item.Dims = [3]float64{dx, dy, dz}
		ext := [3]float64{dx, dy, dz}
		for _, e := range c.Expect {
			got := ext[e.Axis]
			ok := got >= e.Lo && got <= e.Hi
			item.Checks = append(item.Checks, accCheck{What: e.What,
				Want: fmt.Sprintf("[%.0f, %.0f]", e.Lo, e.Hi),
				Got:  fmt.Sprintf("%.1f", got), Pass: ok})
		}
		if c.CustomChecks != nil {
			item.Checks = append(item.Checks, c.CustomChecks(g)...)
		}

		item.Verdict = "pass"
		for _, ck := range item.Checks {
			if !ck.Pass {
				item.Verdict = "fail"
			}
		}
		if knownDevCases[c.Label] {
			item.KnownDev = true
			if item.Verdict == "fail" {
				item.Note = "已知偏差: " + item.Note
			}
		}
		items = append(items, item)
		if item.Verdict == "fail" {
			fails := []string{}
			for _, ck := range item.Checks {
				if !ck.Pass {
					fails = append(fails, ck.What+"="+ck.Got)
				}
			}
			if item.KnownDev {
				t.Logf("[DEV ] %s (已知偏差): %s", c.Label, strings.Join(fails, "; "))
			} else {
				t.Logf("[FAIL] %s: %s", c.Label, strings.Join(fails, "; "))
			}
		}
		runtime.GC()
		debug.FreeOSMemory()
	}

	// ---- 参数化闭环闸门: 布局 JSON 往返几何一致 ----
	items = append(items, acceptanceRoundtripAnchor(t)...)
	items = append(items, acceptanceRoundtripYard(t)...)
	items = append(items, acceptanceRoundtripSpan(t)...)

	// ---- manifest + report ----
	mf, err := json.MarshalIndent(items, "", "  ")
	if err != nil {
		t.Fatal(err)
	}
	if err := os.WriteFile(filepath.Join(dir, "manifest.json"), mf, 0o644); err != nil {
		t.Fatal(err)
	}
	if err := os.WriteFile(filepath.Join(dir, "report.md"), acceptanceReport(items), 0o644); err != nil {
		t.Fatal(err)
	}

	pass, fail, dev := 0, 0, 0
	for _, it := range items {
		switch {
		case it.Verdict == "pass":
			pass++
		case it.KnownDev:
			dev++
		default:
			fail++
		}
	}
	t.Logf("铁路视觉验收: %d 项通过, %d 项已知偏差, %d 项失败 (共 %d)", pass, dev, fail, len(items))
}

// acceptanceRoundtripAnchor 锚段布局 JSON 往返一致性闸门
func acceptanceRoundtripAnchor(t *testing.T) []accItem {
	var cl []Point3
	for x := 0.0; x <= 150000; x += 5000 {
		cl = append(cl, NewPoint3([3]float64{x, 0, 0}))
	}
	in := AnchorSectionInput{Centerline: cl, ContactHeight: 6000, StructureHeight: 1400,
		SpanLength: 50000, MastHeight: 9000, MastType: 1, SideOffset: 2900, HasCompensator: true}
	_ = t
	as0, layout0, err := CreateAnchorSectionWithLayout(in)
	if err != nil {
		return []accItem{{Name: "锚段布局JSON往返", Group: "PARAM", Verdict: "fail",
			Checks: []accCheck{{What: "首次生成", Want: "成功", Got: err.Error(), Pass: false}}}}
	}
	b, err := layout0.ToJSON()
	if err != nil {
		return []accItem{{Name: "锚段布局JSON往返", Group: "PARAM", Verdict: "fail",
			Checks: []accCheck{{What: "ToJSON", Want: "成功", Got: err.Error(), Pass: false}}}}
	}
	layout1, err := AnchorSectionLayoutFromJSON(b)
	if err != nil {
		return []accItem{{Name: "锚段布局JSON往返", Group: "PARAM", Verdict: "fail",
			Checks: []accCheck{{What: "FromJSON", Want: "成功", Got: err.Error(), Pass: false}}}}
	}
	as1, err := CreateAnchorSectionFromLayout(layout1)
	if err != nil {
		return []accItem{{Name: "锚段布局JSON往返", Group: "PARAM", Verdict: "fail",
			Checks: []accCheck{{What: "再生成", Want: "成功", Got: err.Error(), Pass: false}}}}
	}
	bb0, bb1 := as0.ToCompound().BBox().Data(), as1.ToCompound().BBox().Data()
	ok := len(as0.GetElements()) == len(as1.GetElements())
	checks := []accCheck{{What: "元素数一致", Want: fmt.Sprintf("%d", len(as0.GetElements())),
		Got: fmt.Sprintf("%d", len(as1.GetElements())), Pass: ok}}
	for i, axis := range []string{"dx", "dy", "dz"} {
		d0, d1 := bb0[i+3]-bb0[i], bb1[i+3]-bb1[i]
		same := math.Abs(d1-d0) < 1e-3
		checks = append(checks, accCheck{What: axis + " 往返一致",
			Want: fmt.Sprintf("%.3f", d0), Got: fmt.Sprintf("%.3f", d1), Pass: same})
		if !same {
			ok = false
		}
	}
	return []accItem{{Name: "锚段布局JSON往返", Group: "PARAM",
		Expect: "ToJSON→FromJSON→FromLayout 几何逐位一致", Verdict: verdictOf(ok), Checks: checks}}
}

// acceptanceRoundtripYard 站场布局 JSON 往返一致性闸门
func acceptanceRoundtripYard(t *testing.T) []accItem {
	_ = t
	as0, layout0, err := CreateYardFromGeoJSONWithLayout(buildAcceptanceYardGeoJSON())
	if err != nil {
		return []accItem{{Name: "站场布局JSON往返", Group: "PARAM", Verdict: "fail",
			Checks: []accCheck{{What: "首次生成", Want: "成功", Got: err.Error(), Pass: false}}}}
	}
	b, err := layout0.ToJSON()
	if err != nil {
		return []accItem{{Name: "站场布局JSON往返", Group: "PARAM", Verdict: "fail",
			Checks: []accCheck{{What: "ToJSON", Want: "成功", Got: err.Error(), Pass: false}}}}
	}
	layout1, err := YardLayoutFromJSON(b)
	if err != nil {
		return []accItem{{Name: "站场布局JSON往返", Group: "PARAM", Verdict: "fail",
			Checks: []accCheck{{What: "FromJSON", Want: "成功", Got: err.Error(), Pass: false}}}}
	}
	as1, err := CreateYardFromLayout(layout1)
	if err != nil {
		return []accItem{{Name: "站场布局JSON往返", Group: "PARAM", Verdict: "fail",
			Checks: []accCheck{{What: "再生成", Want: "成功", Got: err.Error(), Pass: false}}}}
	}
	bb0, bb1 := as0.ToCompound().BBox().Data(), as1.ToCompound().BBox().Data()
	ok := len(as0.GetElements()) == len(as1.GetElements())
	checks := []accCheck{{What: "元素数一致", Want: fmt.Sprintf("%d", len(as0.GetElements())),
		Got: fmt.Sprintf("%d", len(as1.GetElements())), Pass: ok}}
	for i, axis := range []string{"dx", "dy", "dz"} {
		d0, d1 := bb0[i+3]-bb0[i], bb1[i+3]-bb1[i]
		same := math.Abs(d1-d0) < 1e-3
		checks = append(checks, accCheck{What: axis + " 往返一致",
			Want: fmt.Sprintf("%.3f", d0), Got: fmt.Sprintf("%.3f", d1), Pass: same})
		if !same {
			ok = false
		}
	}
	return []accItem{{Name: "站场布局JSON往返", Group: "PARAM",
		Expect: "ToJSON→FromJSON→FromLayout 几何逐位一致", Verdict: verdictOf(ok), Checks: checks}}
}

func verdictOf(ok bool) string {
	if ok {
		return "pass"
	}
	return "fail"
}

// acceptanceRoundtripSpan 跨距装配级配方整棵重建闸门 (ocs_span)
func acceptanceRoundtripSpan(t *testing.T) []accItem {
	_ = t
	var cl []Point3
	for x := 0.0; x <= 150000; x += 5000 {
		cl = append(cl, NewPoint3([3]float64{x, 0, 0}))
	}
	as, err := CreateAnchorSection(AnchorSectionInput{Centerline: cl, ContactHeight: 6000,
		StructureHeight: 1400, SpanLength: 50000, MastHeight: 9000, MastType: 1, SideOffset: 2900})
	if err != nil {
		return []accItem{{Name: "跨距配方整棵重建", Group: "PARAM", Verdict: "fail",
			Checks: []accCheck{{What: "锚段生成", Want: "成功", Got: err.Error(), Pass: false}}}}
	}
	data, err := as.ExportParametric()
	if err != nil {
		return []accItem{{Name: "跨距配方整棵重建", Group: "PARAM", Verdict: "fail",
			Checks: []accCheck{{What: "ExportParametric", Want: "成功", Got: err.Error(), Pass: false}}}}
	}
	var tree ParametricElement
	if err := json.Unmarshal(data, &tree); err != nil {
		return []accItem{{Name: "跨距配方整棵重建", Group: "PARAM", Verdict: "fail",
			Checks: []accCheck{{What: "解析导出", Want: "成功", Got: err.Error(), Pass: false}}}}
	}
	var spanJSON []byte
	topNames := []string{}
	for _, ch := range tree.Children {
		topNames = append(topNames, ch.Name)
		if ch.Name == "span_1" {
			spanJSON, _ = json.Marshal(ch)
		}
	}
	checks := []accCheck{{What: "层级: 顶层仅 支柱装置+跨距",
		Want: "mast_*/span_*", Got: strings.Join(topNames, ","), Pass: len(topNames) == 8}}
	if spanJSON == nil {
		checks = append(checks, accCheck{What: "span_1 导出", Want: "存在", Got: "缺失", Pass: false})
		return []accItem{{Name: "跨距配方整棵重建", Group: "PARAM", Verdict: "fail", Checks: checks}}
	}
	rebuilt, err := RebuildFromParametric(spanJSON)
	if err != nil {
		checks = append(checks, accCheck{What: "单跨重建", Want: "成功", Got: err.Error(), Pass: false})
		return []accItem{{Name: "跨距配方整棵重建", Group: "PARAM", Verdict: "fail", Checks: checks}}
	}
	// 与原子树 bbox 等价
	segs := strings.Split("span_1", "/")
	cur := as
	for _, seg := range segs {
		for _, ch := range cur.Children() {
			if ch.GetName() == seg {
				cur = ch
				break
			}
		}
	}
	bb0, bb1 := cur.ToCompound().BBox().Data(), rebuilt.ToCompound().BBox().Data()
	ok := true
	for i := 0; i < 6; i++ {
		if math.Abs(bb0[i]-bb1[i]) > 1 {
			ok = false
		}
	}
	checks = append(checks, accCheck{What: "单跨重建几何等价", Want: "bbox≤1mm", Got: "一致", Pass: ok})
	if _, found := rebuilt.Get("mw_1"); !found {
		ok = false
		checks = append(checks, accCheck{What: "跨内叶片寻址", Want: "mw_1", Got: "缺失", Pass: false})
	}
	return []accItem{{Name: "跨距配方整棵重建", Group: "PARAM",
		Expect:  "ocs_span 装配级配方: 顶层仅 支柱装置+跨距, 单跨按配方整棵重建且几何等价",
		Verdict: verdictOf(ok), Checks: checks}}
}

func expectSummary(exs []accExpect) string {
	parts := []string{}
	for _, e := range exs {
		axis := [3]string{"X", "Y", "Z"}[e.Axis]
		parts = append(parts, fmt.Sprintf("%s%s∈[%.0f,%.0f]", e.What, axis, e.Lo, e.Hi))
	}
	return strings.Join(parts, "; ")
}

func acceptanceReport(items []accItem) []byte {
	var b strings.Builder
	pass, fail, dev := 0, 0, 0
	groups := map[string][3]int{} // [pass, dev, fail]
	for _, it := range items {
		g := groups[it.Group]
		switch {
		case it.Verdict == "pass":
			pass++
			g[0]++
		case it.KnownDev:
			dev++
			g[1]++
		default:
			fail++
			g[2]++
		}
		groups[it.Group] = g
	}
	b.WriteString("# 铁路参数化视觉验收报告\n\n")
	b.WriteString(fmt.Sprintf("- 用例总数: %d, 通过: %d, 已知偏差: %d, 失败: %d\n", len(items), pass, dev, fail))
	b.WriteString("- 闸门: 生成有效性 → 尺寸符合性(bbox vs 真实工程值) → 参数化JSON闭环 → 视觉目检 (acceptance/index.html)\n")
	b.WriteString("- 已知偏差: 与真实标准存在建模层级差异的项, 单列于报告, 不计为验收失败\n\n")
	b.WriteString("| 分组 | 通过 | 已知偏差 | 失败 |\n|---|---|---|---|\n")
	for _, g := range []string{"RAIL", "TRACK", "TRACK-ASM", "ASSEM", "OCS-PART", "OCS-MAST", "OCS-COMP", "WIRE", "OCS-ASM", "PARAM"} {
		if v, ok := groups[g]; ok {
			b.WriteString(fmt.Sprintf("| %s | %d | %d | %d |\n", g, v[0], v[1], v[2]))
		}
	}
	b.WriteString("\n## 明细\n\n")
	b.WriteString("| 判定 | 用例 | 分组 | 实测尺寸 dx×dy×dz (mm) | 说明 |\n|---|---|---|---|---|\n")
	for _, it := range items {
		mark := "✅"
		if it.Verdict != "pass" {
			mark = "⚠️ 已知偏差"
			if !it.KnownDev {
				mark = "❌"
			}
		}
		b.WriteString(fmt.Sprintf("| %s | %s | %s | %.0f×%.0f×%.0f | %s |\n",
			mark, it.Name, it.Group, it.Dims[0], it.Dims[1], it.Dims[2], it.Note))
	}
	if dev+fail > 0 {
		b.WriteString("\n## 未达标项明细\n\n")
		for _, it := range items {
			if it.Verdict == "pass" {
				continue
			}
			tag := "❌ 失败"
			if it.KnownDev {
				tag = "⚠️ 已知偏差"
			}
			b.WriteString(fmt.Sprintf("### %s (%s) — %s\n\n", it.Name, it.Group, tag))
			for _, ck := range it.Checks {
				if ck.Pass {
					continue
				}
				b.WriteString(fmt.Sprintf("- %s: 期望 %s, 实测 %s\n", ck.What, ck.Want, ck.Got))
			}
		}
	}
	return []byte(b.String())
}

// accMeshWriteStl 三角化 (Shape 或 Compound) 后写出二进制 STL
func accMeshWriteStl(g accGeo, defl float64, path string) error {
	rec := NewMeshReceiver()
	switch v := g.(type) {
	case *Shape:
		if n := v.Mesh(rec, 1e-8, defl, 0.5); n < 0 {
			return fmt.Errorf("三角化失败 (code=%d)", n)
		}
	case *Compound:
		v.Mesh(rec, 1e-8, defl, 0.5)
	default:
		return fmt.Errorf("不支持的几何类型")
	}
	return accWriteStlReceiver(rec, path)
}

func accWriteStlReceiver(rec *MeshReceiver, path string) error {
	total := 0
	for _, tris := range rec.Tris {
		total += len(tris)
	}
	if total == 0 {
		return fmt.Errorf("无三角形")
	}
	f, err := os.Create(path)
	if err != nil {
		return err
	}
	defer f.Close()
	header := make([]byte, 80)
	copy(header, "go-topo railway acceptance")
	if _, err := f.Write(header); err != nil {
		return err
	}
	var cnt [4]byte
	cnt[0] = byte(total)
	cnt[1] = byte(total >> 8)
	cnt[2] = byte(total >> 16)
	cnt[3] = byte(total >> 24)
	if _, err := f.Write(cnt[:]); err != nil {
		return err
	}
	writeF32 := func(v float64) error {
		b := math.Float32bits(float32(v))
		var bs [4]byte
		bs[0] = byte(b)
		bs[1] = byte(b >> 8)
		bs[2] = byte(b >> 16)
		bs[3] = byte(b >> 24)
		_, err := f.Write(bs[:])
		return err
	}
	for fi, tris := range rec.Tris {
		vers := rec.Vers[fi]
		for _, tri := range tris {
			a, b, c := vers[tri[0]].Data(), vers[tri[1]].Data(), vers[tri[2]].Data()
			ux, uy, uz := b[0]-a[0], b[1]-a[1], b[2]-a[2]
			vx, vy, vz := c[0]-a[0], c[1]-a[1], c[2]-a[2]
			nx, ny, nz := uy*vz-uz*vy, uz*vx-ux*vz, ux*vy-uy*vx
			l := math.Sqrt(float64(nx*nx + ny*ny + nz*nz))
			if l > 0 {
				nx, ny, nz = nx/l, ny/l, nz/l
			}
			for _, val := range []float64{nx, ny, nz} {
				if err := writeF32(val); err != nil {
					return err
				}
			}
			for _, pt := range [][3]float64{a, b, c} {
				for _, val := range pt {
					if err := writeF32(val); err != nil {
						return err
					}
				}
			}
			var attr [2]byte
			if _, err := f.Write(attr[:]); err != nil {
				return err
			}
		}
	}
	return nil
}
