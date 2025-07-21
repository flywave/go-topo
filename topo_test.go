package topo

import (
	"fmt"
	"testing"
)

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

func TestMaakeWire(t *testing.T) {

	points := []Point3{
		NewPoint3([3]float64{0, 0, 0}),
		NewPoint3([3]float64{88.27510582562536, 47.17234171088785, 1.3518126332201064}),
	}

	pro := TopoMakeWireFromCircle(10, NewPoint3([3]float64{0, 0, 0}), NewDir3FromXYZ([3]float64{0, 0, 1}))
	length := WireLength(pro)
	fmt.Println(length)

	w := TopoMakeWireFromCombineCurve([][]Point3{points}, []SweepCurveType{0})
	sld := TopoMakeSolid()
	sld.SweepWire(w, []*Wire{pro}, 0)
	fmt.Println(sld.IsValid())
	// length := WireLength(w)
	// t.Log(length)
}

func TestMaakeWire2(t *testing.T) {
	points := []Point3{
		NewPoint3([3]float64{0, 0, 0}),
		NewPoint3([3]float64{46.3256, -90.7646, 108.893}),
		NewPoint3([3]float64{46.3256, -90.7646, 108.893}),
		NewPoint3([3]float64{131.694, -256.482, -2.52019}),
		NewPoint3([3]float64{131.694, -256.482, -2.52019}),
		NewPoint3([3]float64{176.996, -427.627, 247.322}),
		NewPoint3([3]float64{176.996, -427.627, 247.322}),
		NewPoint3([3]float64{300.229, -1026.2, 570.908}),
		NewPoint3([3]float64{300.229, -1026.2, 570.908}),
		NewPoint3([3]float64{314.317, -1038.7, 581.424}),
		NewPoint3([3]float64{314.317, -1038.7, 581.424}),
		NewPoint3([3]float64{329.994, -1060.71, 618.145}),
	}

	var edges []Edge
	for i := 0; i < len(points); i += 2 {
		edge := TopoMakeEdgeFromTwoPoint(points[i], points[i+1])
		edges = append(edges, *edge)
	}
	w := TopoMakeWireFromEdges(edges)
	if !w.IsValid() {
		t.Fatal("Failed to create wire")
	}
}
