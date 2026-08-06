package topo

import (
	"encoding/json"
	"fmt"
	"math"
)

// =========================================================================
// 站场布局数据: GeoJSON 识别 → 可序列化存库/前端编辑校正 → 确定性再生成
//   ComputeYardLayout    纯识别计算, 输出全部中间数据 (股道裁剪/道岔/菱形交叉)
//   CreateYardFromLayout 由布局确定性生成装配, 子件全部挂参数化配方
//   单位: mm; 道岔局部约定: 原点=岔心节点, 主行进方向 MainDir (水平单位向量)
// =========================================================================

// YardTrackLayout 一条股道的布局数据
// Centerline 为未裁剪的原始中心线; TrimS/TrimE 为识别出的裁剪弧长
// (TrimS=起点裁掉的长度, TrimE=终点保留到的累计弧长, 默认=全长)
type YardTrackLayout struct {
	Centerline [][3]float64       `json:"centerline"` // 原始中心线点列 (mm)
	TrimS      float64            `json:"trimS"`      // 起点裁剪弧长 (mm)
	TrimE      float64            `json:"trimE"`      // 终点保留弧长 (自起点累计, mm; 0=全长)
	Props      TrackGeoProperties `json:"props"`      // 轨距/超高/钢轨/轨枕等生成参数
}

// YardTurnoutLayout 一组单开道岔的布局数据 (CreateTurnoutWithPlace 所需全部参数)
type YardTurnoutLayout struct {
	Position         [3]float64 `json:"position"`         // 岔心节点位置 (世界坐标)
	MainDir          [3]float64 `json:"mainDir"`          // 主行进方向 (水平单位向量)
	IsLeftHand       bool       `json:"isLeftHand"`       // 开向: true=左开
	TurnoutNo        int        `json:"turnoutNo"`        // 道岔号数 {9,12,18,30,42}
	SwitchRailLength float64    `json:"switchRailLength"` // 尖轨长度
	LeadCurveRadius  float64    `json:"leadCurveRadius"`  // 导曲线半径
	Gauge            float64    `json:"gauge"`            // 轨距
	RailHeight       float64    `json:"railHeight"`       // 钢轨断面尺寸
	RailHeadWidth    float64    `json:"railHeadWidth"`
	RailBaseWidth    float64    `json:"railBaseWidth"`
	EdgeIn           int        `json:"edgeIn"`  // 主入边索引 (Tracks 下标, 信息用)
	EdgeOut          int        `json:"edgeOut"` // 主出边索引
	EdgeDiv          int        `json:"edgeDiv"` // 侧股边索引
}

// YardCrossingLayout 一个菱形交叉的布局数据 (CreateFrogWithPlace 所需全部参数)
type YardCrossingLayout struct {
	Position      [3]float64 `json:"position"`      // 交点位置 (世界坐标)
	Direction     [3]float64 `json:"direction"`     // 辙叉角平分线方向 (水平单位向量)
	TurnoutNo     int        `json:"turnoutNo"`     // 辙叉号数
	Gauge         float64    `json:"gauge"`         // 轨距
	RailHeight    float64    `json:"railHeight"`    // 钢轨断面尺寸
	RailHeadWidth float64    `json:"railHeadWidth"`
	RailBaseWidth float64    `json:"railBaseWidth"`
	EdgeA         int        `json:"edgeA"` // 相交边索引 (Tracks 下标, 信息用)
	EdgeB         int        `json:"edgeB"`
}

// YardLayout 生成一个站场所需的全部中间数据
type YardLayout struct {
	Tracks    []YardTrackLayout    `json:"tracks"`
	Turnouts  []YardTurnoutLayout  `json:"turnouts,omitempty"`
	Crossings []YardCrossingLayout `json:"crossings,omitempty"`
}

// ToJSON 序列化布局, 供存库/发前端编辑
func (l *YardLayout) ToJSON() ([]byte, error) {
	return json.Marshal(l)
}

// YardLayoutFromJSON 反序列化布局
func YardLayoutFromJSON(data []byte) (*YardLayout, error) {
	var l YardLayout
	if err := json.Unmarshal(data, &l); err != nil {
		return nil, fmt.Errorf("yard: invalid layout JSON: %w", err)
	}
	return &l, nil
}

func ptsToArrays(pts []Point3) [][3]float64 {
	out := make([][3]float64, len(pts))
	for i, p := range pts {
		out[i] = p.Data()
	}
	return out
}

func arraysToPts(a [][3]float64) []Point3 {
	out := make([]Point3, len(a))
	for i, p := range a {
		out[i] = NewPoint3(p)
	}
	return out
}

// ComputeYardLayout 由 GeoJSON FeatureCollection 纯计算站场布局, 无副作用
// 识别规则 (与历史 CreateYardFromGeoJSON 一致):
//   - 端点聚类为节点 (容差 50mm), 度=3 → 单开道岔 (自动判开向/号数, 裁剪邻边)
//   - 两条边中部相交 (距节点 2m 以外) → 菱形交叉
func ComputeYardLayout(data []byte) (*YardLayout, error) {
	var in geoJSONInput
	if err := json.Unmarshal(data, &in); err != nil {
		return nil, fmt.Errorf("invalid GeoJSON: %w", err)
	}
	if in.Type != "FeatureCollection" {
		return nil, fmt.Errorf("站场输入需要 FeatureCollection")
	}

	var edges []yardEdge
	for _, f := range in.Features {
		if f.Geometry.Type != "LineString" || len(f.Geometry.Coordinates) < 2 {
			continue
		}
		raw, _ := json.Marshal(f)
		pts, props, err := ParseTrackGeoJSON(raw)
		if err != nil {
			return nil, err
		}
		edges = append(edges, yardEdge{pts, props})
	}
	if len(edges) == 0 {
		return nil, fmt.Errorf("no valid LineString features")
	}

	// 1. 端点聚类为节点 (容差 50mm)
	const nodeTol = 50.0
	var nodes []yardNode
	for ei, e := range edges {
		for end, p := range []Point3{e.pts[0], e.pts[len(e.pts)-1]} {
			found := -1
			for ni, nd := range nodes {
				if ptDist(nd.p, p) < nodeTol {
					found = ni
					break
				}
			}
			if found < 0 {
				nodes = append(nodes, yardNode{p: p})
				found = len(nodes) - 1
			}
			nodes[found].ends = append(nodes[found].ends, [2]int{ei, end})
		}
	}

	// 2. 道岔识别: 度=3 的节点
	var turnouts []YardTurnoutLayout
	trimS := make(map[int]float64) // edge → 起点裁剪
	trimE := make(map[int]float64) // edge → 终点裁剪

	for _, nd := range nodes {
		if len(nd.ends) != 3 {
			continue
		}
		// 各端点方向 (指向边内部)
		dirs := make([][3]float64, 3)
		for i, ee := range nd.ends {
			dirs[i] = dirAtEnd(edges[ee[0]].pts, ee[1] == 0, 1000)
		}
		// 主方向对 = 点积最小 (最接近反向共线)
		pair, minDot := [2]int{0, 1}, 1e9
		for i := 0; i < 3; i++ {
			for j := i + 1; j < 3; j++ {
				d := dirs[i][0]*dirs[j][0] + dirs[i][1]*dirs[j][1]
				if d < minDot {
					minDot, pair = d, [2]int{i, j}
				}
			}
		}
		div := 3 - pair[0] - pair[1]
		// 主行进方向: 从主入边指向主出边
		inD, outD := dirs[pair[0]], dirs[pair[1]]
		mainDir := [3]float64{outD[0] - inD[0], outD[1] - inD[1], 0}
		l := math.Hypot(mainDir[0], mainDir[1])
		if l < 1e-9 {
			continue
		}
		mainDir[0], mainDir[1] = mainDir[0]/l, mainDir[1]/l
		// 道岔号数: 侧股 15m~35m 弦方向与主向夹角
		divEdge := edges[nd.ends[div][0]]
		farDir := chordDir(divEdge.pts, nd.ends[div][1] == 0, 15000, 35000)
		cross := mainDir[0]*farDir[1] - mainDir[1]*farDir[0]
		dot := mainDir[0]*farDir[0] + mainDir[1]*farDir[1]
		alpha := math.Atan2(math.Abs(cross), dot)
		if alpha < 0.005 { // 近似共线, 无法判定
			alpha = math.Atan(1.0 / 12)
		}
		no := snapTurnoutNo(alpha)
		ft := frogTableFor(no)
		hg := 1435.0 / 2
		if g := divEdge.props.Gauge; g > 0 {
			hg = g / 2
		}
		frogX := 2 * math.Sqrt(ft.leadR*hg)
		railH, headW, baseW := standardRailDims(60)
		turnouts = append(turnouts, YardTurnoutLayout{
			Position:         nd.p.Data(),
			MainDir:          mainDir,
			IsLeftHand:       cross > 0,
			TurnoutNo:        no,
			SwitchRailLength: ft.swLen,
			LeadCurveRadius:  ft.leadR,
			Gauge:            1435,
			RailHeight:       railH,
			RailHeadWidth:    headW,
			RailBaseWidth:    baseW,
			EdgeIn:           nd.ends[pair[0]][0],
			EdgeOut:          nd.ends[pair[1]][0],
			EdgeDiv:          nd.ends[div][0],
		})
		// 裁剪: 按边离站方向与主向的点积判定主入/主出边
		for _, pi := range pair {
			ee := nd.ends[pi]
			d := dirs[pi]
			isOut := d[0]*mainDir[0]+d[1]*mainDir[1] > 0
			acc := polyArcLens(edges[ee[0]].pts)
			total := acc[len(acc)-1]
			trim := ft.swLen + 2000 // 主入边: 岔前段
			if isOut {
				trim = frogX + ft.frogTotal // 主出边: 岔尾段
			}
			if ee[1] == 0 { // 边起点在节点
				if trim > trimS[ee[0]] {
					trimS[ee[0]] = trim
				}
			} else { // 边终点在节点
				v := total - trim
				if cur, ok := trimE[ee[0]]; !ok || v < cur {
					trimE[ee[0]] = v
				}
			}
		}
		// 侧股边: 沿曲线弧长 ≈ frogX + tail + 裕量
		ee := nd.ends[div]
		divTrim := frogX + ft.frogTotal + 500
		if ee[1] == 0 {
			if divTrim > trimS[ee[0]] {
				trimS[ee[0]] = divTrim
			}
		} else {
			acc := polyArcLens(edges[ee[0]].pts)
			v := acc[len(acc)-1] - divTrim
			if cur, ok := trimE[ee[0]]; !ok || v < cur {
				trimE[ee[0]] = v
			}
		}
	}

	// 3. 菱形交叉: 边中部相交
	var crossings []YardCrossingLayout
	segIntersect := func(a1, a2, b1, b2 Point3) (Point3, bool) {
		p1, p2, p3, p4 := a1.Data(), a2.Data(), b1.Data(), b2.Data()
		d1x, d1y := p2[0]-p1[0], p2[1]-p1[1]
		d2x, d2y := p4[0]-p3[0], p4[1]-p3[1]
		den := d1x*d2y - d1y*d2x
		if math.Abs(den) < 1e-9 {
			return Point3{}, false
		}
		t := ((p3[0]-p1[0])*d2y - (p3[1]-p1[1])*d2x) / den
		u := ((p3[0]-p1[0])*d1y - (p3[1]-p1[1])*d1x) / den
		if t > -0.001 && t < 1.001 && u > -0.001 && u < 1.001 {
			return NewPoint3([3]float64{p1[0] + t*d1x, p1[1] + t*d1y, p1[2] + t * (p2[2] - p1[2])}), true
		}
		return Point3{}, false
	}
	for i := 0; i < len(edges); i++ {
		for j := i + 1; j < len(edges); j++ {
			for a := 0; a+1 < len(edges[i].pts); a++ {
				for b := 0; b+1 < len(edges[j].pts); b++ {
					if cp, ok := segIntersect(edges[i].pts[a], edges[i].pts[a+1], edges[j].pts[b], edges[j].pts[b+1]); ok {
						// 距节点 2m 内视为道岔区, 不算菱形交叉
						nearNode := false
						for _, nd := range nodes {
							if ptDist(nd.p, cp) < 2000 {
								nearNode = true
								break
							}
						}
						if nearNode {
							continue
						}
						// 顶点处相交会被多个线段对重复发现, 去重
						dup := false
						for _, cr := range crossings {
							if ptDist(NewPoint3(cr.Position), cp) < 500 {
								dup = true
								break
							}
						}
						if dup {
							continue
						}
						d1 := dirAtEnd(edges[i].pts, true, 1000)
						d2 := dirAtEnd(edges[j].pts, true, 1000)
						if d1[0]*d2[0]+d1[1]*d2[1] < 0 {
							d2[0], d2[1] = -d2[0], -d2[1]
						}
						bs := [3]float64{d1[0] + d2[0], d1[1] + d2[1], 0}
						bl := math.Hypot(bs[0], bs[1])
						if bl < 1e-9 {
							continue
						}
						ang := math.Atan2(math.Abs(d1[0]*d2[1]-d1[1]*d2[0]), d1[0]*d2[0]+d1[1]*d2[1])
						crossings = append(crossings, YardCrossingLayout{
							Position:      cp.Data(),
							Direction:     [3]float64{bs[0] / bl, bs[1] / bl, 0},
							TurnoutNo:     snapTurnoutNo(ang),
							Gauge:         1435,
							RailHeight:    176,
							RailHeadWidth: 73,
							RailBaseWidth: 150,
							EdgeA:         i,
							EdgeB:         j,
						})
					}
				}
			}
		}
	}

	// 4. 股道: 原始中心线 + 识别出的裁剪弧长
	layout := &YardLayout{Turnouts: turnouts, Crossings: crossings}
	for ei, e := range edges {
		acc := polyArcLens(e.pts)
		tr := YardTrackLayout{
			Centerline: ptsToArrays(e.pts),
			TrimE:      acc[len(acc)-1],
			Props:      e.props,
		}
		if v, ok := trimS[ei]; ok {
			tr.TrimS = v
		}
		if v, ok := trimE[ei]; ok {
			tr.TrimE = v
		}
		layout.Tracks = append(layout.Tracks, tr)
	}
	return layout, nil
}

// CreateYardFromLayout 由布局确定性生成站场装配
// 子件命名 rails_i / sleepers_i / turnout_i / crossing_i, 均唯一;
// 每个子件经 AddObjectParams 挂参数化配方, 支持 ExportParametric → RebuildFromParametric 往返
func CreateYardFromLayout(layout *YardLayout) (*Assembly, error) {
	if layout == nil || len(layout.Tracks) == 0 {
		return nil, fmt.Errorf("yard: layout has no tracks")
	}

	var root *Assembly
	addShape := func(s *Shape, name string, data *ParametricData) {
		if s == nil {
			return
		}
		obj := NewAssemblyObjectFromShpe(*s)
		if root == nil {
			root = NewAssembly(obj, nil, name, nil)
			if data != nil {
				root.SetParametric(data)
			}
		} else {
			root.AddObjectParams(obj, nil, name, nil, data)
		}
	}

	// 股道: 按 TrimS/TrimE 裁剪中心线后生成钢轨对 + 轨枕
	for ti, tr := range layout.Tracks {
		props := tr.Props
		props.withDefaults()
		pts := arraysToPts(tr.Centerline)
		if len(pts) < 2 {
			continue
		}
		acc := polyArcLens(pts)
		total := acc[len(acc)-1]
		s0, s1 := tr.TrimS, tr.TrimE
		if s0 < 0 {
			s0 = 0
		}
		if s1 <= 0 || s1 > total { // 布局可能被手工编辑过, 缺省为全长
			s1 = total
		}
		seg := trimPolyline(pts, s0, s1)
		if len(seg) < 2 {
			continue
		}
		railH, headW, baseW := standardRailDims(props.RailType)
		addShape(CreateRailPairFromPoints(seg, props.Gauge, props.SuperElevation, railH, headW, baseW),
			fmt.Sprintf("rails_%d", ti), yardRailsParametric(seg, props, railH, headW, baseW))
		if !props.NoSleepers {
			addShape(CreateSleeperLayout(seg, props.SleeperLength, props.SleeperWidth,
				props.SleeperHeight, props.SleeperSpacing, props.Gauge),
				fmt.Sprintf("sleepers_%d", ti), yardSleepersParametric(seg, props))
		}
	}
	// 道岔
	for i, tn := range layout.Turnouts {
		tp := TurnoutParams{
			TurnoutNo: tn.TurnoutNo, IsLeftHand: tn.IsLeftHand, Gauge: tn.Gauge,
			RailHeight: tn.RailHeight, RailHeadWidth: tn.RailHeadWidth, RailBaseWidth: tn.RailBaseWidth,
			SwitchRailLength: tn.SwitchRailLength, LeadCurveRadius: tn.LeadCurveRadius,
		}
		// 布局可能被手工编辑过, 缺省值兜底
		if tp.TurnoutNo == 0 {
			tp.TurnoutNo = 12
		}
		if tp.Gauge <= 0 {
			tp.Gauge = 1435
		}
		if tp.RailHeight <= 0 {
			tp.RailHeight, tp.RailHeadWidth, tp.RailBaseWidth = standardRailDims(60)
		}
		if tp.SwitchRailLength <= 0 || tp.LeadCurveRadius <= 0 {
			ft := frogTableFor(tp.TurnoutNo)
			if tp.SwitchRailLength <= 0 {
				tp.SwitchRailLength = ft.swLen
			}
			if tp.LeadCurveRadius <= 0 {
				tp.LeadCurveRadius = ft.leadR
			}
		}
		dir := tn.MainDir
		if math.Hypot(dir[0], dir[1]) < 1e-9 {
			return nil, fmt.Errorf("yard: turnout %d has zero mainDir", i)
		}
		addShape(CreateTurnoutWithPlace(tp, NewPoint3(tn.Position),
			NewDir3FromXYZ([3]float64{dir[0], dir[1], 0}),
			NewDir3FromXYZ([3]float64{0, 0, 1})),
			fmt.Sprintf("turnout_%d", i), yardTurnoutParametric(tp, tn.Position, dir))
	}
	// 菱形交叉
	for i, cr := range layout.Crossings {
		fp := FrogParams{
			TurnoutNo: cr.TurnoutNo, Gauge: cr.Gauge,
			RailHeight: cr.RailHeight, RailHeadWidth: cr.RailHeadWidth, RailBaseWidth: cr.RailBaseWidth,
		}
		if fp.TurnoutNo == 0 {
			fp.TurnoutNo = 12
		}
		if fp.Gauge <= 0 {
			fp.Gauge = 1435
		}
		if fp.RailHeight <= 0 {
			fp.RailHeight, fp.RailHeadWidth, fp.RailBaseWidth = 176, 73, 150
		}
		dir := cr.Direction
		if math.Hypot(dir[0], dir[1]) < 1e-9 {
			return nil, fmt.Errorf("yard: crossing %d has zero direction", i)
		}
		addShape(CreateFrogWithPlace(fp, NewPoint3(cr.Position),
			NewDir3FromXYZ(dir), NewDir3FromXYZ([3]float64{0, 0, 1})),
			fmt.Sprintf("crossing_%d", i), yardCrossingParametric(fp, cr.Position, dir))
	}

	if root == nil {
		return nil, fmt.Errorf("no geometry generated")
	}
	return root, nil
}

// CreateYardFromGeoJSON 从多中心线 GeoJSON 生成站场装配 (= ComputeYardLayout + CreateYardFromLayout)
func CreateYardFromGeoJSON(data []byte) (*Assembly, error) {
	layout, err := ComputeYardLayout(data)
	if err != nil {
		return nil, err
	}
	return CreateYardFromLayout(layout)
}

// CreateYardFromGeoJSONWithLayout 同 CreateYardFromGeoJSON, 同时返回识别出的布局
func CreateYardFromGeoJSONWithLayout(data []byte) (*Assembly, *YardLayout, error) {
	layout, err := ComputeYardLayout(data)
	if err != nil {
		return nil, nil, err
	}
	as, err := CreateYardFromLayout(layout)
	if err != nil {
		return nil, nil, err
	}
	return as, layout, nil
}

// =========================================================================
// 参数化配方: ExportParametric → RebuildFromParametric 闭环
// =========================================================================

type yardRailsRecipe struct {
	Centerline     [][3]float64 `json:"centerline"` // 裁剪后中心线
	Gauge          float64      `json:"gauge"`
	SuperElevation float64      `json:"superElevation"`
	RailHeight     float64      `json:"railHeight"`
	RailHeadWidth  float64      `json:"railHeadWidth"`
	RailBaseWidth  float64      `json:"railBaseWidth"`
}

type yardSleepersRecipe struct {
	Centerline [][3]float64 `json:"centerline"` // 裁剪后中心线
	Length     float64      `json:"length"`
	Width      float64      `json:"width"`
	Height     float64      `json:"height"`
	Spacing    float64      `json:"spacing"`
	Gauge      float64      `json:"gauge"`
}

type yardTurnoutRecipe struct {
	Params    TurnoutParams `json:"params"`
	Position  [3]float64    `json:"position"`
	Direction [3]float64    `json:"direction"`
	UpDir     [3]float64    `json:"upDir"`
}

type yardCrossingRecipe struct {
	Params    FrogParams `json:"params"`
	Position  [3]float64 `json:"position"`
	Direction [3]float64 `json:"direction"`
	UpDir     [3]float64 `json:"upDir"`
}

func yardRailsParametric(seg []Point3, props TrackGeoProperties, railH, headW, baseW float64) *ParametricData {
	raw, _ := json.Marshal(yardRailsRecipe{
		Centerline: ptsToArrays(seg), Gauge: props.Gauge, SuperElevation: props.SuperElevation,
		RailHeight: railH, RailHeadWidth: headW, RailBaseWidth: baseW,
	})
	return &ParametricData{Type: "yard_rails", Params: raw}
}

func yardSleepersParametric(seg []Point3, props TrackGeoProperties) *ParametricData {
	raw, _ := json.Marshal(yardSleepersRecipe{
		Centerline: ptsToArrays(seg), Length: props.SleeperLength, Width: props.SleeperWidth,
		Height: props.SleeperHeight, Spacing: props.SleeperSpacing, Gauge: props.Gauge,
	})
	return &ParametricData{Type: "yard_sleepers", Params: raw}
}

func yardTurnoutParametric(tp TurnoutParams, pos, dir [3]float64) *ParametricData {
	raw, _ := json.Marshal(yardTurnoutRecipe{
		Params: tp, Position: pos, Direction: dir, UpDir: [3]float64{0, 0, 1},
	})
	return &ParametricData{Type: "yard_turnout", Params: raw}
}

func yardCrossingParametric(fp FrogParams, pos, dir [3]float64) *ParametricData {
	raw, _ := json.Marshal(yardCrossingRecipe{
		Params: fp, Position: pos, Direction: dir, UpDir: [3]float64{0, 0, 1},
	})
	return &ParametricData{Type: "yard_crossing", Params: raw}
}

func buildYardRails(params json.RawMessage) (*Shape, *TopoLocation, error) {
	var r yardRailsRecipe
	if err := json.Unmarshal(params, &r); err != nil {
		return nil, nil, fmt.Errorf("yard_rails: %w", err)
	}
	if r.Gauge <= 0 {
		r.Gauge = 1435
	}
	if r.RailHeight <= 0 {
		r.RailHeight, r.RailHeadWidth, r.RailBaseWidth = standardRailDims(60)
	}
	s := CreateRailPairFromPoints(arraysToPts(r.Centerline), r.Gauge, r.SuperElevation,
		r.RailHeight, r.RailHeadWidth, r.RailBaseWidth)
	if s == nil || s.IsNull() {
		return nil, nil, fmt.Errorf("yard_rails: build failed")
	}
	return s, nil, nil
}

func buildYardSleepers(params json.RawMessage) (*Shape, *TopoLocation, error) {
	var r yardSleepersRecipe
	if err := json.Unmarshal(params, &r); err != nil {
		return nil, nil, fmt.Errorf("yard_sleepers: %w", err)
	}
	if r.Gauge <= 0 {
		r.Gauge = 1435
	}
	if r.Spacing <= 0 {
		r.Spacing = 600
	}
	s := CreateSleeperLayout(arraysToPts(r.Centerline), r.Length, r.Width, r.Height, r.Spacing, r.Gauge)
	if s == nil || s.IsNull() {
		return nil, nil, fmt.Errorf("yard_sleepers: build failed")
	}
	return s, nil, nil
}

func buildYardTurnout(params json.RawMessage) (*Shape, *TopoLocation, error) {
	var r yardTurnoutRecipe
	if err := json.Unmarshal(params, &r); err != nil {
		return nil, nil, fmt.Errorf("yard_turnout: %w", err)
	}
	dir := r.Direction
	if math.Hypot(dir[0], dir[1]) < 1e-9 {
		dir = [3]float64{1, 0, 0}
	}
	up := r.UpDir
	if up == [3]float64{} {
		up = [3]float64{0, 0, 1}
	}
	s := CreateTurnoutWithPlace(r.Params, NewPoint3(r.Position), NewDir3FromXYZ(dir), NewDir3FromXYZ(up))
	if s == nil || s.IsNull() {
		return nil, nil, fmt.Errorf("yard_turnout: build failed")
	}
	return s, nil, nil
}

func buildYardCrossing(params json.RawMessage) (*Shape, *TopoLocation, error) {
	var r yardCrossingRecipe
	if err := json.Unmarshal(params, &r); err != nil {
		return nil, nil, fmt.Errorf("yard_crossing: %w", err)
	}
	dir := r.Direction
	if math.Hypot(dir[0], dir[1]) < 1e-9 {
		dir = [3]float64{1, 0, 0}
	}
	up := r.UpDir
	if up == [3]float64{} {
		up = [3]float64{0, 0, 1}
	}
	s := CreateFrogWithPlace(r.Params, NewPoint3(r.Position), NewDir3FromXYZ(dir), NewDir3FromXYZ(up))
	if s == nil || s.IsNull() {
		return nil, nil, fmt.Errorf("yard_crossing: build failed")
	}
	return s, nil, nil
}

func init() {
	RegisterParametricBuilder("yard_rails", buildYardRails)
	RegisterParametricBuilder("yard_sleepers", buildYardSleepers)
	RegisterParametricBuilder("yard_turnout", buildYardTurnout)
	RegisterParametricBuilder("yard_crossing", buildYardCrossing)
}
