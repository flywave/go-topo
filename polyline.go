package topo

import (
	"math"
)

// =========================================================================
// 折线几何助手 (基本图元共用: 扣件布点等; 无识别逻辑)。
// 生成规则层 flywave-topovis/railway/rules 有同源镜像 (rules 不 import
// go-topo 以保持无 cgo 可独立编译; 双份为解耦代价, 一致性由验收锁定)。
// =========================================================================

func ptSub(a, b Point3) [3]float64 {
	da, db := a.Data(), b.Data()
	return [3]float64{da[0] - db[0], da[1] - db[1], da[2] - db[2]}
}

func ptDist(a, b Point3) float64 {
	d := ptSub(a, b)
	return math.Sqrt(d[0]*d[0] + d[1]*d[1] + d[2]*d[2])
}

// polyArcLens 点列累计弧长
func polyArcLens(pts []Point3) []float64 {
	acc := make([]float64, len(pts))
	for i := 1; i < len(pts); i++ {
		acc[i] = acc[i-1] + ptDist(pts[i-1], pts[i])
	}
	return acc
}

// dist3 两点距离 (rvt 等模块共用)
func dist3(a, b [3]float64) float64 {
	dx, dy, dz := b[0]-a[0], b[1]-a[1], b[2]-a[2]
	return math.Sqrt(dx*dx + dy*dy + dz*dz)
}
