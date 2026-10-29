package topo

import (
	"encoding/json"
	"fmt"
	"math"
	"sort"
	"strings"
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
	LeadCurveRadius  float64    `json:"leadCurveRadius"`  // 导曲线半径 (实测拟合, 非查表)
	FrogAngle        float64    `json:"frogAngle"`        // 实测辙叉角(rad), 信息用
	SleeperSpacing   float64    `json:"sleeperSpacing"`   // 岔枕间距 (缺省 600)
	SleeperHeight    float64    `json:"sleeperHeight"`    // 岔枕高=轨底抬高 (缺省 200, 与邻接股道齐平)
	Gauge            float64    `json:"gauge"`            // 轨距
	RailHeight       float64    `json:"railHeight"`       // 钢轨断面尺寸
	RailHeadWidth    float64    `json:"railHeadWidth"`
	RailBaseWidth    float64    `json:"railBaseWidth"`
	EdgeIn           int        `json:"edgeIn"`  // 主入边索引 (Tracks 下标, 信息用)
	EdgeOut          int        `json:"edgeOut"` // 主出边索引
	EdgeDiv          int        `json:"edgeDiv"` // 侧股边索引
}

// YardCrossingLayout 一个菱形交叉的布局数据 (CreateDiamondWithPlace 所需全部参数)
type YardCrossingLayout struct {
	Position       [3]float64 `json:"position"`       // 交点位置 (世界坐标)
	Direction      [3]float64 `json:"direction"`      // 辙叉角平分线方向 (水平单位向量)
	TurnoutNo      int        `json:"turnoutNo"`      // 交叉角就近号数 (信息用)
	FrogAngle      float64    `json:"frogAngle"`      // 实测交叉角(rad); 0=由号数推算 (旧行为)
	Span           float64    `json:"span"`           // 菱形沿线路半展长 (股道让位分段范围)
	SleeperSpacing float64    `json:"sleeperSpacing"` // 交叉区岔枕间距; 0=不生成
	SleeperHeight  float64    `json:"sleeperHeight"`  // 轨面抬高 (菱形轨底从中心线平面抬到枕顶)
	Gauge          float64    `json:"gauge"`          // 轨距
	RailHeight     float64    `json:"railHeight"`     // 钢轨断面尺寸
	RailHeadWidth  float64    `json:"railHeadWidth"`
	RailBaseWidth  float64    `json:"railBaseWidth"`
	EdgeA          int        `json:"edgeA"` // 相交边索引 (Tracks 下标, 信息用)
	EdgeB          int        `json:"edgeB"`
}

// YardLayout 生成一个站场所需的全部中间数据
type YardLayout struct {
	Tracks    []YardTrackLayout    `json:"tracks"`
	Turnouts  []YardTurnoutLayout  `json:"turnouts,omitempty"`
	Crossings []YardCrossingLayout `json:"crossings,omitempty"`
	Warnings  []string             `json:"warnings,omitempty"` // 识别阶段跳过的道岔等原因说明
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

// divergingFrogGeometry 沿侧股边 (从节点端起) 行走, 定位辙叉理论交点。
// 道岔模型中辙叉心位于侧股中心线横向偏出主向线 2hg 处, 该点方向角 ≈ 辙叉角,
// 弧长 ≈ 岔心横距 frogX (两者由导曲线几何推出: R ≈ arc/alpha)。
// 返回 alpha (rad), arc (mm), side (+1=主向左侧/-1=右侧), ok
func divergingFrogGeometry(pts []Point3, fromStart bool, mainDir [3]float64, hg float64) (alpha, arc, side float64, ok bool) {
	n := len(pts)
	get := func(i int) Point3 {
		if fromStart {
			return pts[i]
		}
		return pts[n-1-i]
	}
	p0 := get(0).Data()
	lat := func(p Point3) float64 { // 相对过节点主向直线的有向横向距离 (左正)
		d := p.Data()
		return mainDir[0]*(d[1]-p0[1]) - mainDir[1]*(d[0]-p0[0])
	}
	target := 2 * hg
	acc := 0.0
	for i := 0; i+1 < n; i++ {
		a, b := get(i), get(i+1)
		la, lb := lat(a), lat(b)
		for _, tg := range [2]float64{target, -target} {
			if (la-tg)*(lb-tg) < 0 {
				t := (tg - la) / (lb - la)
				ad, bd := a.Data(), b.Data()
				dx, dy := bd[0]-ad[0], bd[1]-ad[1]
				cr := mainDir[0]*dy - mainDir[1]*dx
				dt := mainDir[0]*dx + mainDir[1]*dy
				return math.Atan2(math.Abs(cr), dt), acc + t*ptDist(a, b), math.Copysign(1, tg), true
			}
		}
		acc += ptDist(a, b)
	}
	return 0, 0, 0, false
}

// mainCurveDeviation 节点端沿边行走 extent 弧长, 求点距主向直线的最大横向偏差 (mm)。
// 用于曲线主线上道岔布置守卫: 直基本轨模型与弯曲线形的偏差超限时不出岔。
func mainCurveDeviation(pts []Point3, fromStart bool, mainDir [3]float64, extent float64) float64 {
	n := len(pts)
	get := func(i int) Point3 {
		if fromStart {
			return pts[i]
		}
		return pts[n-1-i]
	}
	p0 := get(0).Data()
	lat := func(p Point3) float64 {
		d := p.Data()
		return mainDir[0]*(d[1]-p0[1]) - mainDir[1]*(d[0]-p0[0])
	}
	acc := 0.0
	dev := 0.0
	for i := 0; i+1 < n; i++ {
		a, b := get(i), get(i+1)
		seg := ptDist(a, b)
		if acc+seg > extent {
			d, ad := b.Data(), a.Data()
			t := (extent - acc) / math.Max(seg, 1e-9)
			b = NewPoint3([3]float64{ad[0] + (d[0]-ad[0])*t, ad[1] + (d[1]-ad[1])*t, ad[2] + (d[2]-ad[2])*t})
			seg = extent - acc
		}
		dev = math.Max(dev, math.Abs(lat(a)))
		acc += seg
		if acc >= extent {
			break
		}
	}
	return dev
}

// projectOnPolyline 点到折线的投影: 返回投影点累计弧长 (从指定端起) 与 2D 距离
func projectOnPolyline(pts []Point3, fromStart bool, p [3]float64) (float64, float64) {
	get := func(i int) Point3 {
		if fromStart {
			return pts[i]
		}
		return pts[len(pts)-1-i]
	}
	bestArc, bestDist := 0.0, 1e18
	acc := 0.0
	for i := 0; i+1 < len(pts); i++ {
		a := get(i).Data()
		b := get(i+1).Data()
		dx, dy := b[0]-a[0], b[1]-a[1]
		seg2 := dx*dx + dy*dy
		t := 0.0
		if seg2 > 1e-9 {
			t = ((p[0]-a[0])*dx + (p[1]-a[1])*dy) / seg2
			t = math.Min(math.Max(t, 0), 1)
		}
		px, py := a[0]+t*dx, a[1]+t*dy
		d := math.Hypot(p[0]-px, p[1]-py)
		if d < bestDist {
			bestDist = d
			bestArc = acc + t*math.Sqrt(seg2)
		}
		acc += math.Sqrt(seg2)
	}
	return bestArc, bestDist
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
	var warnings []string
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
		hg := 1435.0 / 2
		if g := edges[nd.ends[div][0]].props.Gauge; g > 0 {
			hg = g / 2
		}
		// 侧股辙叉几何实测: 行走到横向偏出主向线 2hg 处 (辙叉理论交点),
		// 该点方向角 ≈ 辙叉角, 弧长 ≈ 岔心横距 → 导曲线半径 R ≈ arc/alpha
		divEdge := edges[nd.ends[div][0]]
		alpha, arcFrog, side, ok := divergingFrogGeometry(divEdge.pts,
			nd.ends[div][1] == 0, mainDir, hg)
		if !ok || alpha < 0.005 { // 近似共线/数据太短, 退回弦方向估计
			farDir := chordDir(divEdge.pts, nd.ends[div][1] == 0, 15000, 35000)
			cr := mainDir[0]*farDir[1] - mainDir[1]*farDir[0]
			dt := mainDir[0]*farDir[0] + mainDir[1]*farDir[1]
			alpha = math.Atan2(math.Abs(cr), dt)
			arcFrog = 0
			if !ok {
				side = math.Copysign(1, cr)
			}
		}
		if alpha < 0.005 { // 仍无法判定, 按 12 号处理
			alpha = math.Atan(1.0 / 12)
		}
		no := snapTurnoutNo(alpha)
		ft := frogTableFor(no)
		leadR := ft.leadR
		if arcFrog > 0 && alpha > 1e-4 { // 实测拟合优先于查表 (岔后与侧线线形连续)
			// 直侧线 (前段弦角≈辙叉角): R = 4hg/tan²α — 模型自洽半径, 岔后出口角恰为侧线角
			// 曲侧线: R = arc/α — 圆弧弧长/圆心角
			chordA := chordDir(divEdge.pts, nd.ends[div][1] == 0, 5000, 15000)
			cAng := math.Atan2(math.Abs(mainDir[0]*chordA[1]-mainDir[1]*chordA[0]),
				mainDir[0]*chordA[0]+mainDir[1]*chordA[1])
			r := 0.0
			if math.Abs(alpha-cAng) < 0.004 {
				tn := math.Tan(alpha)
				r = 4 * hg / (tn * tn)
			} else {
				r = arcFrog / alpha
			}
			if r > 50000 && r < 8000000 {
				leadR = r
			}
		}
		frogX := 2 * math.Sqrt(leadR*hg)
		// 曲线主向守卫: 直基本轨模型与主线线形在道岔区内的横向偏差超限时不出岔
		extIn := 2600.0 // 岔前段 (基本轨前伸, 与 C++ create_turnout 的 x0 镜像)
		extOut := frogX + ft.frogTotal
		devIn := mainCurveDeviation(edges[nd.ends[pair[0]][0]].pts, nd.ends[pair[0]][1] == 0, mainDir, extIn)
		devOut := mainCurveDeviation(edges[nd.ends[pair[1]][0]].pts, nd.ends[pair[1]][1] == 0, mainDir, extOut)
		if dev := math.Max(devIn, devOut); dev > 100 {
			px, py := nd.p.Data()[0], nd.p.Data()[1]
			warnings = append(warnings, fmt.Sprintf(
				"道岔(节点 %.1f,%.1f) 跳过: 主线在道岔区内弯直偏差 %.0fmm > 100mm, 直股道岔模型不适用", px, py, dev))
			continue
		}
		railH, headW, baseW := standardRailDims(60)
		mainProps := edges[nd.ends[pair[0]][0]].props
		turnouts = append(turnouts, YardTurnoutLayout{
			Position:         nd.p.Data(),
			MainDir:          mainDir,
			IsLeftHand:       side > 0,
			TurnoutNo:        no,
			SwitchRailLength: ft.swLen,
			LeadCurveRadius:  leadR,
			FrogAngle:        alpha,
			SleeperSpacing:   mainProps.SleeperSpacing,
			SleeperHeight:    mainProps.SleeperHeight,
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
			trim := 2600.0 // 主入边: 岔前段 (基本轨前伸 ~2.6m, 与 C++ x0 镜像)
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
		// 侧股边: 优先按岔后出口点 (导曲线末端) 在侧股边上的投影定位裁剪弧长
		// (曲侧线投影与道岔线形重合; 直侧线取最近接续点); 投影不可靠时退回弧长估算
		ee := nd.ends[div]
		divTrim := frogX + ft.frogTotal + 500
		{
			// 岔后出口点 (导曲线在辙叉心切点收直, 岔后顺 thFrog 直段 — 与 C++ 镜像)
			Ro2 := leadR + hg
			thF := math.Asin(math.Min(frogX/Ro2, 1.0))
			exX := frogX + ft.frogTotal*math.Cos(thF)
			exY := leadR*(1-math.Cos(thF)) + ft.frogTotal*math.Sin(thF)
			perpX, perpY := -mainDir[1], mainDir[0]
			ndp := nd.p.Data()
			exitW := [3]float64{ndp[0] + mainDir[0]*exX + perpX*side*exY,
				ndp[1] + mainDir[1]*exX + perpY*side*exY, ndp[2]}
			if arc, dist := projectOnPolyline(divEdge.pts, ee[1] == 0, exitW); dist < 2000 && arc > 1000 {
				divTrim = arc + 300
			}
		}
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
			return NewPoint3([3]float64{p1[0] + t*d1x, p1[1] + t*d1y, p1[2] + t*(p2[2]-p1[2])}), true
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
						// 菱形半展长: 锐角交点距中心 ≈ hg·cot(α/2)·cosα + hg·sinα, 加端部裕量
						h := 717.5
						if g := edges[i].props.Gauge; g > 0 {
							h = g / 2
						}
						halfA := math.Atan(ang / 2)
						xa := h/math.Tan(halfA)*math.Cos(ang) + h*math.Sin(ang)
						crossings = append(crossings, YardCrossingLayout{
							Position:       cp.Data(),
							Direction:      [3]float64{bs[0] / bl, bs[1] / bl, 0},
							TurnoutNo:      snapTurnoutNo(ang),
							FrogAngle:      ang, // 实测交叉角 (直角交叉不再退化为浅角菱形)
							Span:           xa + 1800,
							SleeperSpacing: 600,
							SleeperHeight:  edges[i].props.SleeperHeight,
							Gauge:          1435,
							RailHeight:     176,
							RailHeadWidth:  73,
							RailBaseWidth:  150,
							EdgeA:          i,
							EdgeB:          j,
						})
					}
				}
			}
		}
	}

	// 4. 股道: 原始中心线 + 识别出的裁剪弧长;
	//    交叉点附近区间让位给菱形单元 — 股道在菱形范围内分段 (钢轨/岔枕由菱形提供),
	//    避免单元钢轨与股道钢轨四层重叠
	layout := &YardLayout{Turnouts: turnouts, Crossings: crossings, Warnings: warnings}
	type arcGap struct{ s0, s1 float64 }
	edgeGaps := make(map[int][]arcGap)
	for _, cr := range crossings {
		for _, ei := range []int{cr.EdgeA, cr.EdgeB} {
			if ei < 0 || ei >= len(edges) {
				continue
			}
			arc, dist := projectOnPolyline(edges[ei].pts, true, cr.Position)
			if dist > 5000 {
				continue
			}
			span := cr.Span
			if span <= 0 { // 旧布局无 Span, 不分段 (旧行为)
				continue
			}
			edgeGaps[ei] = append(edgeGaps[ei], arcGap{arc - span, arc + span})
		}
	}
	for ei, e := range edges {
		acc := polyArcLens(e.pts)
		total := acc[len(acc)-1]
		s0 := 0.0
		if v, ok := trimS[ei]; ok && v > 0 {
			s0 = v
		}
		s1 := total
		if v, ok := trimE[ei]; ok && v > 0 && v < total {
			s1 = v
		}
		gaps := edgeGaps[ei]
		if len(gaps) == 0 {
			layout.Tracks = append(layout.Tracks, YardTrackLayout{
				Centerline: ptsToArrays(e.pts), TrimS: s0, TrimE: s1, Props: e.props})
			continue
		}
		sort.Slice(gaps, func(a, b int) bool { return gaps[a].s0 < gaps[b].s0 })
		cur := s0
		emit := func(a, b float64) {
			if b-a < 2000 {
				return
			}
			sub := trimPolyline(e.pts, a, b)
			if len(sub) >= 2 {
				layout.Tracks = append(layout.Tracks, YardTrackLayout{
					Centerline: ptsToArrays(sub), Props: e.props})
			}
		}
		for _, g := range gaps {
			g0, g1 := g.s0, g.s1
			if g1 <= cur {
				continue
			}
			if g0 > cur {
				emit(cur, math.Min(g0, s1))
			}
			cur = math.Max(cur, g1)
			if cur >= s1 {
				break
			}
		}
		if cur < s1 {
			emit(cur, s1)
		}
	}
	return layout, nil
}

// CreateYardFromLayout 由布局确定性生成站场装配 (铁路专业层级):
//
//	yard (站场)
//	├── track_i     股道子装配 (yard_track 配方可整棵重建)
//	│   ├── rails_i / sleepers_i   轨道结构叶片 (叶片配方)
//	├── turnout_i   单开道岔 (功能单元, yard_turnout 配方)
//	└── crossing_i  菱形交叉 (功能单元, yard_crossing 配方)
//
// 全局地图编辑作用于 track_i / turnout_i / crossing_i 粒度;
// 每个节点挂参数化配方, 支持 ExportParametric → RebuildFromParametric 往返
func CreateYardFromLayout(layout *YardLayout) (*Assembly, error) {
	if layout == nil || len(layout.Tracks) == 0 {
		return nil, fmt.Errorf("yard: layout has no tracks")
	}

	// 根容器: 占位 vertex 放在站场对角中点 (容器节点无几何, vertex 不得污染全局 bbox)
	fx, fy := layout.Tracks[0].Centerline[0][0], layout.Tracks[0].Centerline[0][1]
	lx, ly := layout.Tracks[len(layout.Tracks)-1].Centerline[0][0], layout.Tracks[len(layout.Tracks)-1].Centerline[0][1]
	root := NewAssembly(NewAssemblyObjectFromShpe(*NewVertex((fx+lx)/2, (fy+ly)/2, 0).ToShape()), nil, "yard", nil)

	// 股道: 裁剪中心线 → 股道子装配 (钢轨组 + 轨枕)
	for ti, tr := range layout.Tracks {
		recipe := yardTrackRecipe{Centerline: tr.Centerline, TrimS: tr.TrimS, TrimE: tr.TrimE, Props: tr.Props}
		track, err := buildYardTrackAssembly(recipe, fmt.Sprintf("track_%d", ti))
		if err != nil {
			return nil, err
		}
		track.SetParametric(&ParametricData{Type: "yard_track", Params: mustJSON(recipe)})
		root.AddAssembly(track, nil, track.GetName(), nil)
		if root.HasError() {
			return nil, fmt.Errorf("yard: add track %d: %s", ti, root.Error())
		}
	}
	// 道岔
	for i, tn := range layout.Turnouts {
		tp := TurnoutParams{
			TurnoutNo: tn.TurnoutNo, IsLeftHand: tn.IsLeftHand, Gauge: tn.Gauge,
			RailHeight: tn.RailHeight, RailHeadWidth: tn.RailHeadWidth, RailBaseWidth: tn.RailBaseWidth,
			SwitchRailLength: tn.SwitchRailLength, LeadCurveRadius: tn.LeadCurveRadius,
			SleeperSpacing: tn.SleeperSpacing, SleeperHeight: tn.SleeperHeight,
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
		if tp.SleeperHeight <= 0 {
			tp.SleeperHeight = 200
		}
		if tp.SleeperSpacing <= 0 {
			tp.SleeperSpacing = 600
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
		root.AddObjectParams(NewAssemblyObjectFromShpe(*CreateTurnoutWithPlace(tp, NewPoint3(tn.Position),
			NewDir3FromXYZ([3]float64{dir[0], dir[1], 0}),
			NewDir3FromXYZ([3]float64{0, 0, 1}))),
			nil, fmt.Sprintf("turnout_%d", i), nil, yardTurnoutParametric(tp, tn.Position, dir))
	}
	// 菱形交叉
	for i, cr := range layout.Crossings {
		dp := DiamondParams{
			TurnoutNo: cr.TurnoutNo, Gauge: cr.Gauge,
			RailHeight: cr.RailHeight, RailHeadWidth: cr.RailHeadWidth, RailBaseWidth: cr.RailBaseWidth,
			FrogAngle: cr.FrogAngle, SleeperSpacing: cr.SleeperSpacing, SleeperHeight: cr.SleeperHeight,
		}
		if dp.Gauge <= 0 {
			dp.Gauge = 1435
		}
		if dp.RailHeight <= 0 {
			dp.RailHeight, dp.RailHeadWidth, dp.RailBaseWidth = 176, 73, 150
		}
		if dp.FrogAngle > 1e-6 {
			// 实测交叉角 (真菱形编织区)
		} else {
			// 旧行为兼容: 角度由号数推算
			dp.FrogAngle = math.Atan2(1.0, float64(dp.TurnoutNo))
		}
		dir := cr.Direction
		if math.Hypot(dir[0], dir[1]) < 1e-9 {
			return nil, fmt.Errorf("yard: crossing %d has zero direction", i)
		}
		// 轨面抬高: 股道钢轨基于枕顶 (+sleeperHeight), 菱形轨底平面随之
		pos := cr.Position
		if cr.SleeperHeight > 0 {
			pos[2] += cr.SleeperHeight
		}
		root.AddObjectParams(NewAssemblyObjectFromShpe(*CreateDiamondWithPlace(dp, NewPoint3(pos),
			NewDir3FromXYZ(dir), NewDir3FromXYZ([3]float64{0, 0, 1}))),
			nil, fmt.Sprintf("crossing_%d", i), nil, yardCrossingParametric(dp, pos, dir))
	}
	return root, nil
}

// buildYardTrackAssembly 由股道配方生成股道子装配 (叶片名 rails_i / sleepers_i)
func buildYardTrackAssembly(recipe yardTrackRecipe, name string) (*Assembly, error) {
	// 容器占位 vertex 放在原始中心线中点 (不得污染全局 bbox)
	mid := recipe.Centerline[len(recipe.Centerline)/2]
	track := NewAssembly(NewAssemblyObjectFromShpe(*NewVertex(mid[0], mid[1], mid[2]).ToShape()), nil, name, nil)
	// 叶片名索引: track_3 → rails_3 (保持全局唯一约定)
	idx := name
	if k := strings.LastIndex(name, "_"); k >= 0 && k+1 < len(name) {
		idx = name[k+1:]
	}
	props := recipe.Props
	props.withDefaults()
	pts := arraysToPts(recipe.Centerline)
	if len(pts) < 2 {
		return nil, fmt.Errorf("yard: %s centerline needs >= 2 points", name)
	}
	acc := polyArcLens(pts)
	total := acc[len(acc)-1]
	s0, s1 := recipe.TrimS, recipe.TrimE
	if s0 < 0 {
		s0 = 0
	}
	if s1 <= 0 || s1 > total { // 布局可能被手工编辑过, 缺省为全长
		s1 = total
	}
	seg := trimPolyline(pts, s0, s1)
	if len(seg) < 2 {
		return nil, fmt.Errorf("yard: %s trimmed segment too short", name)
	}
	railH, headW, baseW := standardRailDims(props.RailType)
	add := func(s *Shape, leaf string, data *ParametricData) {
		if s == nil || s.IsNull() {
			return
		}
		track.AddObjectParams(NewAssemblyObjectFromShpe(*s), nil, leaf, nil, data)
	}
	add(CreateRailPairFromPoints(raiseCenterlineToRailTop(seg, props.SleeperHeight),
		props.Gauge, props.SuperElevation, railH, headW, baseW),
		"rails_"+idx, yardRailsParametric(seg, props, railH, headW, baseW))
	if !props.NoSleepers {
		add(CreateSleeperLayout(seg, props.SleeperLength, props.SleeperWidth,
			props.SleeperHeight, props.SleeperSpacing, props.Gauge),
			"sleepers_"+idx, yardSleepersParametric(seg, props))
	}
	return track, nil
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
	SleeperHeight  float64      `json:"sleeperHeight"` // 轨底抬升量, 默认 200
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
	Params    DiamondParams `json:"params"`
	Position  [3]float64    `json:"position"`
	Direction [3]float64    `json:"direction"`
	UpDir     [3]float64    `json:"upDir"`
}

// yardTrackRecipe 股道配方: 未裁剪原始中心线 + 裁剪弧长 + 轨道生成参数
// 前端在股道粒度编辑 (改裁剪/轨枕参数后整股重建)
type yardTrackRecipe struct {
	Centerline [][3]float64       `json:"centerline"`
	TrimS      float64            `json:"trimS"`
	TrimE      float64            `json:"trimE"`
	Props      TrackGeoProperties `json:"props"`
}

func yardRailsParametric(seg []Point3, props TrackGeoProperties, railH, headW, baseW float64) *ParametricData {
	raw, _ := json.Marshal(yardRailsRecipe{
		Centerline: ptsToArrays(seg), Gauge: props.Gauge, SuperElevation: props.SuperElevation,
		RailHeight: railH, RailHeadWidth: headW, RailBaseWidth: baseW,
		SleeperHeight: props.SleeperHeight,
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

func yardCrossingParametric(dp DiamondParams, pos, dir [3]float64) *ParametricData {
	raw, _ := json.Marshal(yardCrossingRecipe{
		Params: dp, Position: pos, Direction: dir, UpDir: [3]float64{0, 0, 1},
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
	if r.SleeperHeight <= 0 {
		r.SleeperHeight = 200
	}
	s := CreateRailPairFromPoints(raiseCenterlineToRailTop(arraysToPts(r.Centerline), r.SleeperHeight),
		r.Gauge, r.SuperElevation, r.RailHeight, r.RailHeadWidth, r.RailBaseWidth)
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
	s := CreateDiamondWithPlace(r.Params, NewPoint3(r.Position), NewDir3FromXYZ(dir), NewDir3FromXYZ(up))
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
	RegisterAssemblyBuilder("yard_track", buildYardTrackBuilder)
}

// buildYardTrackBuilder yard_track 装配级 builder: 按股道配方整棵重建股道子装配
func buildYardTrackBuilder(params json.RawMessage, name string) (*Assembly, error) {
	var r yardTrackRecipe
	if err := json.Unmarshal(params, &r); err != nil {
		return nil, fmt.Errorf("yard_track: %w", err)
	}
	return buildYardTrackAssembly(r, name)
}
