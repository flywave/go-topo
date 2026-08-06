package topo

import (
	"math"
)

// =========================================================================
// 站场生成器: 多条轨道中心线 (GeoJSON FeatureCollection) 组为中心线图,
// 自动识别道岔 (三叉节点) 与菱形交叉 (边相交节点), 并布置对应三维构件。
//
// 拓扑规则 (对应 AGENTS.md centerline_graph 方案):
//   - 节点度=3 (一条边终止于另两条之间) → 单开道岔 (转辙器+导曲线+辙叉)
//   - 两条边中部相交 → 菱形交叉 (辙叉)
//
// 本文件为识别/裁剪的共用辅助函数; 识别入口 ComputeYardLayout 与
// 生成入口 CreateYardFromLayout / CreateYardFromGeoJSON 见 yard_layout.go
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
