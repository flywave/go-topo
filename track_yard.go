package topo

import (
	"encoding/json"
	"fmt"
	"math"
)

// =========================================================================
// 站场生成器: 多条轨道中心线 (GeoJSON FeatureCollection) 组为中心线图,
// 自动识别道岔 (三叉节点) 与菱形交叉 (边相交节点), 并布置对应三维构件。
//
// 拓扑规则 (对应 AGENTS.md centerline_graph 方案):
//   - 节点度=3 (一条边终止于另两条之间) → 单开道岔 (转辙器+导曲线+辙叉)
//   - 两条边中部相交 → 菱形交叉 (辙叉)
// =========================================================================

type yardEdge struct {
	pts   []Point3 // 毫米
	props TrackGeoProperties
}

type yardNode struct {
	p    Point3
	ends [][2]int // {边索引, 端点 (0=起点, 1=终点)}
}

func ptVec(p Point3) [3]float64 { return p.Data() }

func ptSub(a, b Point3) [3]float64 {
	da, db := a.Data(), b.Data()
	return [3]float64{da[0] - db[0], da[1] - db[1], da[2] - db[2]}
}

func ptDist(a, b Point3) float64 {
	d := ptSub(a, b)
	return math.Sqrt(d[0]*d[0] + d[1]*d[1] + d[2]*d[2])
}

// 点列累计弧长
func polyArcLens(pts []Point3) []float64 {
	acc := make([]float64, len(pts))
	for i := 1; i < len(pts); i++ {
		acc[i] = acc[i-1] + ptDist(pts[i-1], pts[i])
	}
	return acc
}

// 按弧长截取点列 [s0, s1]
func trimPolyline(pts []Point3, s0, s1 float64) []Point3 {
	acc := polyArcLens(pts)
	total := acc[len(acc)-1]
	if s0 < 0 {
		s0 = 0
	}
	if s1 > total {
		s1 = total
	}
	if s1-s0 < 100 {
		return nil
	}
	at := func(s float64) Point3 {
		for i := 1; i < len(pts); i++ {
			if acc[i] >= s {
				seg := acc[i] - acc[i-1]
				if seg < 1e-9 {
					return pts[i]
				}
				t := (s - acc[i-1]) / seg
				d0, d1 := pts[i-1].Data(), pts[i].Data()
				return NewPoint3([3]float64{d0[0] + (d1[0]-d0[0])*t, d0[1] + (d1[1]-d0[1])*t, d0[2] + (d1[2]-d0[2])*t})
			}
		}
		return pts[len(pts)-1]
	}
	out := []Point3{at(s0)}
	for i := 1; i < len(pts)-1; i++ {
		if acc[i] > s0 && acc[i] < s1 {
			out = append(out, pts[i])
		}
	}
	out = append(out, at(s1))
	return out
}

// 距端点 arcLen 处的切向单位向量 (指向边内部)
func dirAtEnd(pts []Point3, fromStart bool, arcLen float64) [3]float64 {
	acc := polyArcLens(pts)
	total := acc[len(acc)-1]
	if arcLen > total {
		arcLen = total
	}
	at := func(s float64) Point3 {
		for i := 1; i < len(pts); i++ {
			if acc[i] >= s {
				seg := acc[i] - acc[i-1]
				t := (s - acc[i-1]) / math.Max(seg, 1e-9)
				d0, d1 := pts[i-1].Data(), pts[i].Data()
				return NewPoint3([3]float64{d0[0] + (d1[0]-d0[0])*t, d0[1] + (d1[1]-d0[1])*t, d0[2] + (d1[2]-d0[2])*t})
			}
		}
		return pts[len(pts)-1]
	}
	var a, b Point3
	if fromStart {
		a, b = pts[0], at(arcLen)
	} else {
		a, b = pts[len(pts)-1], at(total-arcLen)
	}
	d := ptSub(b, a)
	l := math.Sqrt(d[0]*d[0] + d[1]*d[1])
	if l < 1e-9 {
		return [3]float64{1, 0, 0}
	}
	return [3]float64{d[0] / l, d[1] / l, 0}
}

// 两点处方向采样: 距端点 s0 与 s1 之间的弦方向 (用于估计道岔号数)
func chordDir(pts []Point3, fromStart bool, s0, s1 float64) [3]float64 {
	acc := polyArcLens(pts)
	total := acc[len(acc)-1]
	if !fromStart {
		s0, s1 = total-s1, total-s0
	}
	at := func(s float64) Point3 {
		if s < 0 {
			s = 0
		}
		if s > total {
			s = total
		}
		for i := 1; i < len(pts); i++ {
			if acc[i] >= s {
				seg := acc[i] - acc[i-1]
				t := (s - acc[i-1]) / math.Max(seg, 1e-9)
				d0, d1 := pts[i-1].Data(), pts[i].Data()
				return NewPoint3([3]float64{d0[0] + (d1[0]-d0[0])*t, d0[1] + (d1[1]-d0[1])*t, d0[2] + (d1[2]-d0[2])*t})
			}
		}
		return pts[len(pts)-1]
	}
	d := ptSub(at(s1), at(s0))
	l := math.Sqrt(d[0]*d[0] + d[1]*d[1])
	if l < 1e-9 {
		return [3]float64{1, 0, 0}
	}
	return [3]float64{d[0] / l, d[1] / l, 0}
}

// 辙叉查表 (与 C++ calculate_frog_params 一致)
type frogTable struct {
	leadR, swLen, frogTotal float64
}

func frogTableFor(n int) frogTable {
	t := frogTable{}
	switch n {
	case 9:
		t.leadR, t.swLen = 180000, 6450
	case 18:
		t.leadR, t.swLen = 800000, 12500
	case 30:
		t.leadR, t.swLen = 2700000, 15400
	case 42:
		t.leadR, t.swLen = 5000000, 19200
	default: // 12
		n = 12
		t.leadR, t.swLen = 350000, 7700
	}
	t.frogTotal = 1435 * float64(n) * 0.28
	return t
}

// 角度 → 最近标准道岔号数
func snapTurnoutNo(alpha float64) int {
	best, bestD := 12, 1e9
	for _, n := range []int{9, 12, 18, 30, 42} {
		d := math.Abs(math.Atan(1.0/float64(n)) - alpha)
		if d < bestD {
			bestD, best = d, n
		}
	}
	return best
}

// CreateYardFromGeoJSON 从多中心线 GeoJSON 生成站场装配
func CreateYardFromGeoJSON(data []byte) (*Assembly, error) {
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
	edgeNode := make(map[[2]int]int) // {edge, end} → node idx
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
			edgeNode[[2]int{ei, end}] = found
		}
	}

	// 2. 道岔识别: 度=3 的节点
	type turnoutInfo struct {
		node     yardNode
		pos      Point3
		mainDir  [3]float64
		isLeft   bool
		no       int
		ft       frogTable
		// 各边裁剪弧长: {edgeIdx: {trimStart, trimEnd}}
	}
	var turnouts []turnoutInfo
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
		turnouts = append(turnouts, turnoutInfo{nd, nd.p, mainDir, cross > 0, no, ft})
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
	type crossingInfo struct {
		p   Point3
		dir [3]float64
		no  int
	}
	var crossings []crossingInfo
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
							if ptDist(cr.p, cp) < 500 {
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
						crossings = append(crossings, crossingInfo{cp, [3]float64{bs[0] / bl, bs[1] / bl, 0}, snapTurnoutNo(ang)})
					}
				}
			}
		}
	}

	// 4. 生成: 各边 (裁剪后) 钢轨对 + 轨枕
	var root *Assembly
	addShape := func(s *Shape, name string) {
		if s == nil {
			return
		}
		obj := NewAssemblyObjectFromShpe(*s)
		if root == nil {
			root = NewAssembly(obj, nil, name, nil)
		} else {
			root.AddObject(obj, nil, name, nil)
		}
	}
	for ei, e := range edges {
		acc := polyArcLens(e.pts)
		total := acc[len(acc)-1]
		s0, s1 := 0.0, total
		if v, ok := trimS[ei]; ok {
			s0 = v
		}
		if v, ok := trimE[ei]; ok {
			s1 = v
		}
		seg := trimPolyline(e.pts, s0, s1)
		if len(seg) < 2 {
			continue
		}
		railH, headW, baseW := standardRailDims(e.props.RailType)
		addShape(CreateRailPairFromPoints(seg, e.props.Gauge, e.props.SuperElevation, railH, headW, baseW), fmt.Sprintf("rails_%d", ei))
		if !e.props.NoSleepers {
			addShape(CreateSleeperLayout(seg, e.props.SleeperLength, e.props.SleeperWidth,
				e.props.SleeperHeight, e.props.SleeperSpacing, e.props.Gauge), fmt.Sprintf("sleepers_%d", ei))
		}
	}
	// 5. 道岔
	for i, tn := range turnouts {
		railH, headW, baseW := standardRailDims(60)
		tp := TurnoutParams{
			TurnoutNo: tn.no, IsLeftHand: tn.isLeft, Gauge: 1435,
			RailHeight: railH, RailHeadWidth: headW, RailBaseWidth: baseW,
			SwitchRailLength: tn.ft.swLen, LeadCurveRadius: tn.ft.leadR,
		}
		addShape(CreateTurnoutWithPlace(tp, tn.pos,
			NewDir3FromXYZ([3]float64{tn.mainDir[0], tn.mainDir[1], 0}),
			NewDir3FromXYZ([3]float64{0, 0, 1})), fmt.Sprintf("turnout_%d", i))
	}
	// 6. 菱形交叉
	for i, cr := range crossings {
		fp := FrogParams{TurnoutNo: cr.no, Gauge: 1435, RailHeight: 176, RailHeadWidth: 73, RailBaseWidth: 150}
		addShape(CreateFrogWithPlace(fp, cr.p,
			NewDir3FromXYZ(cr.dir), NewDir3FromXYZ([3]float64{0, 0, 1})), fmt.Sprintf("crossing_%d", i))
	}

	if root == nil {
		return nil, fmt.Errorf("no geometry generated")
	}
	return root, nil
}
