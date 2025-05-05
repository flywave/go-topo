package topo

import "testing"

func TestMakeArc(t *testing.T) {

	points := []Point3{
		NewPoint3([3]float64{88.27510582562536, 47.17234171088785, 1.3518126332201064}),
		NewPoint3([3]float64{-2.002824238501489, 61.12643328495324, -79.24088457413018}),
		NewPoint3([3]float64{0, 0, 0}),
	}

	// 创建圆弧
	curve := GeomMakeArcOfPoint(points[0], points[1], points[2])
	if curve == nil {
		t.Fatal("Failed to create curve")
	}

	c := curve.Curve()

	// 创建边
	edge := TopoMakeEdgeFromCurve(*c)
	if edge == nil || edge.IsNull() {
		t.Fatal("Failed to create edge")
	}
}
