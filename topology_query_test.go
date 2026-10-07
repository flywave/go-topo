package topo

import (
	"math"
	"os"
	"path/filepath"
	"strings"
	"testing"
)

// queryFixtureBox: 10(x) × 20(y) × 30(z), 从原点起: x 0..10, y 0..20, z 0..30
func queryFixtureBox(t *testing.T) *Shape {
	t.Helper()
	s := TopoMakeSolidFromBox(10, 20, 30)
	if s == nil {
		t.Fatal("TopoMakeSolidFromBox returned nil")
	}
	shape := s.ToShape()
	if shape == nil {
		t.Fatal("ToShape returned nil")
	}
	return shape
}

// collectEdges 收集 shape 的全部去重边 (TopExp_Explorer 语义会把共享边
// 按面出现次数重复产出, box 的 12 条边迭代出 24 条, 按 TShape 哈希去重)
func collectEdges(t *testing.T, shp *Shape) []*Edge {
	t.Helper()
	it := TopoMakeEdgeIterator(*shp)
	if it == nil {
		t.Fatal("TopoMakeEdgeIterator returned nil")
	}
	var edges []*Edge
	seen := map[int]bool{}
	for {
		e := it.Next()
		if e == nil {
			break
		}
		h := e.Hash()
		if seen[h] {
			continue
		}
		seen[h] = true
		edges = append(edges, e)
	}
	return edges
}

func collectFaces(t *testing.T, shp *Shape) []*Face {
	t.Helper()
	it := TopoMakeFaceIterator(*shp)
	if it == nil {
		t.Fatal("TopoMakeFaceIterator returned nil")
	}
	var faces []*Face
	for {
		f := it.Next()
		if f == nil {
			break
		}
		faces = append(faces, f)
	}
	return faces
}

// edgeBBox: [minx, miny, minz, maxx, maxy, maxz]
func edgeBBox(e *Edge) [6]float64 {
	return e.BBox().Data()
}

// edgeAlongXAt 返回位于 (y0, z0)、沿 x 方向的边 (bbox 判定, 容差 1e-6)
func edgeAlongXAt(t *testing.T, shp *Shape, y0, z0 float64) *Edge {
	t.Helper()
	for _, e := range collectEdges(t, shp) {
		bb := edgeBBox(e)
		if math.Abs(bb[1]-y0) < 1e-6 && math.Abs(bb[4]-y0) < 1e-6 &&
			math.Abs(bb[2]-z0) < 1e-6 && math.Abs(bb[5]-z0) < 1e-6 {
			return e
		}
	}
	t.Fatalf("no edge along x at y=%v z=%v", y0, z0)
	return nil
}

func TestGetEdgeFaces(t *testing.T) {
	shp := queryFixtureBox(t)
	edges := collectEdges(t, shp)
	if len(edges) != 12 {
		t.Fatalf("box should have 12 edges, got %d", len(edges))
	}
	for i, e := range edges {
		faces := GetEdgeFaces(shp, e)
		if len(faces) != 2 {
			t.Fatalf("edge %d: box edge should have 2 adjacent faces, got %d", i, len(faces))
		}
	}
}

func TestGetCommonEdge(t *testing.T) {
	shp := queryFixtureBox(t)
	faces := collectFaces(t, shp)
	if len(faces) != 6 {
		t.Fatalf("box should have 6 faces, got %d", len(faces))
	}
	// 每个面应与其余 4 个面相邻 (共享边), 与 1 个面相对 (无公共边)
	for i, f := range faces {
		shared := 0
		for j, other := range faces {
			if i == j {
				continue
			}
			if GetCommonEdge(f, other) != nil {
				shared++
			}
		}
		if shared != 4 {
			t.Fatalf("face %d should share edges with 4 others, got %d", i, shared)
		}
	}
}

func TestFaceIsPlanar(t *testing.T) {
	shp := queryFixtureBox(t)
	for i, f := range collectFaces(t, shp) {
		if !FaceIsPlanar(f) {
			t.Fatalf("box face %d should be planar", i)
		}
	}
	cyl := TopoMakeSolidFromCylinder(5, 20).ToShape()
	it := TopoMakeFaceIterator(*cyl)
	planarCount, curvedCount := 0, 0
	for {
		f := it.Next()
		if f == nil {
			break
		}
		if FaceIsPlanar(f) {
			planarCount++
		} else {
			curvedCount++
		}
	}
	if planarCount != 2 || curvedCount != 1 {
		t.Fatalf("cylinder: expect 2 planar caps + 1 curved side, got %d planar + %d curved",
			planarCount, curvedCount)
	}
}

func TestGetOppositeEdge(t *testing.T) {
	shp := queryFixtureBox(t)
	bottom := edgeAlongXAt(t, shp, 20, 0) // y=20, z=0, 沿 x
	opposite := GetOppositeEdge(shp, bottom, 1e-6, NewDir3FromXYZ([3]float64{0, 0, 1}), true)
	if opposite == nil {
		t.Fatal("opposite edge not found")
	}
	bb := edgeBBox(opposite)
	// 应是 y=20, z=+30 的对面边
	if math.Abs(bb[2]-30) > 1e-6 || math.Abs(bb[1]-20) > 1e-6 {
		t.Fatalf("opposite edge at wrong position: z=%v y=%v", bb[2], bb[1])
	}
	// along = -z 时应找不到 (偏移方向不符)
	none := GetOppositeEdge(shp, bottom, 1e-6, NewDir3FromXYZ([3]float64{0, 0, -1}), true)
	if none != nil {
		t.Fatal("opposite edge should not exist along -z")
	}
}

func TestNextPrevAdjacentEdge(t *testing.T) {
	shp := queryFixtureBox(t)
	seed := edgeAlongXAt(t, shp, 20, 30) // 顶面 y=20, z=30 的边

	next := GetNextAdjacentEdge(shp, seed, 1e-6)
	prev := GetPrevAdjacentEdge(shp, seed, 1e-6)
	if next == nil || prev == nil {
		t.Fatalf("next/prev adjacent edges not found: next=%v prev=%v", next != nil, prev != nil)
	}
	if next.Equals(seed.ToShape()) || prev.Equals(seed.ToShape()) {
		t.Fatal("next/prev must differ from seed")
	}
}

func TestClosestEdge(t *testing.T) {
	shp := queryFixtureBox(t)
	// 靠近 (10, 20, 30) 这个角点的边: 命中的边必须贴着该角 (至少两维在该角的面上)
	e := ClosestEdge(shp, NewPoint3([3]float64{10.5, 20.5, 30.5}))
	if e == nil {
		t.Fatal("closest edge not found")
	}
	bb := edgeBBox(e)
	touches := 0
	if math.Abs(bb[3]-10) < 1e-6 { // maxx = 10
		touches++
	}
	if math.Abs(bb[4]-20) < 1e-6 { // maxy = 20
		touches++
	}
	if math.Abs(bb[5]-30) < 1e-6 { // maxz = 30
		touches++
	}
	if touches < 2 {
		t.Fatalf("closest edge not near the corner: bbox=%v", bb)
	}
}

func TestTangentEdgeChain(t *testing.T) {
	// 共线三段线框: 链应覆盖全部 3 条边
	mkP := func(x float64) Point3 { return NewPoint3([3]float64{x, 0, 0}) }
	e1 := TopoMakeEdgeFromTwoPoint(mkP(0), mkP(5))
	e2 := TopoMakeEdgeFromTwoPoint(mkP(5), mkP(10))
	e3 := TopoMakeEdgeFromTwoPoint(mkP(10), mkP(15))
	if e1 == nil || e2 == nil || e3 == nil {
		t.Fatal("failed to create edges")
	}
	wire := TopoMakeWireFromThreeEdge(*e1, *e2, *e3)
	if wire == nil {
		t.Fatal("failed to create wire")
	}
	chain := TangentEdgeChain(wire.ToShape(), e2, 1e-6)
	if len(chain) != 3 {
		t.Fatalf("collinear chain should cover 3 edges, got %d", len(chain))
	}

	// 矩形线框四角都是 90°: 链只含种子自己
	b0 := NewPoint3([3]float64{0, 0, 0})
	b1 := NewPoint3([3]float64{10, 0, 0})
	b2 := NewPoint3([3]float64{10, 10, 0})
	b3 := NewPoint3([3]float64{0, 10, 0})
	r1 := TopoMakeEdgeFromTwoPoint(b0, b1)
	r2 := TopoMakeEdgeFromTwoPoint(b1, b2)
	r3 := TopoMakeEdgeFromTwoPoint(b2, b3)
	r4 := TopoMakeEdgeFromTwoPoint(b3, b0)
	rect := TopoMakeWireFromFourEdge(*r1, *r2, *r3, *r4)
	if rect == nil {
		t.Fatal("failed to create rect wire")
	}
	rectChain := TangentEdgeChain(rect.ToShape(), r1, 1e-6)
	if len(rectChain) != 1 {
		t.Fatalf("right-angle chain should be 1 edge, got %d", len(rectChain))
	}
}

func TestChamferAngle(t *testing.T) {
	shp := queryFixtureBox(t)
	seed := edgeAlongXAt(t, shp, 20, 30)
	baseVol := shp.ComputeMass()

	ch := ChamferAngle(shp, []*Edge{seed}, 2, 45, nil)
	if ch == nil {
		t.Fatal("chamfer_angle returned nil")
	}
	if !ch.IsValid() {
		t.Fatal("chamfer_angle result is not valid")
	}
	if ch.ComputeMass() >= baseVol {
		t.Fatalf("chamfer should remove material: %v >= %v", ch.ComputeMass(), baseVol)
	}

	// 同一基准面, 30° 与 60° 的材料去除量不同 (角度确实参与几何)
	ch30 := ChamferAngle(shp, []*Edge{seed}, 2, 30, nil)
	ch60 := ChamferAngle(shp, []*Edge{seed}, 2, 60, nil)
	if ch30 == nil || ch60 == nil {
		t.Fatal("chamfer_angle 30/60 returned nil")
	}
	if math.Abs(ch30.ComputeMass()-ch60.ComputeMass()) < 1e-6 {
		t.Fatalf("30° and 60° chamfers should differ in volume: %v vs %v",
			ch30.ComputeMass(), ch60.ComputeMass())
	}
}

func TestExportStepUnit(t *testing.T) {
	shp := queryFixtureBox(t)
	dir := t.TempDir()

	mmPath := filepath.Join(dir, "box_mm.step")
	if !shp.ExportStepUnit(mmPath, true, 0, "MM") {
		t.Fatal("export MM step failed")
	}
	mmData, err := os.ReadFile(mmPath)
	if err != nil {
		t.Fatal(err)
	}
	if !strings.Contains(string(mmData), "DATA;") {
		t.Fatal("MM step file missing DATA section")
	}

	inchPath := filepath.Join(dir, "box_inch.step")
	if !shp.ExportStepUnit(inchPath, true, 0, "INCH") {
		t.Fatal("export INCH step failed")
	}
	inchData, err := os.ReadFile(inchPath)
	if err != nil {
		t.Fatal(err)
	}
	if !strings.Contains(string(inchData), "INCH") {
		t.Fatal("INCH step file does not declare INCH unit")
	}

	if shp.ExportStepUnit(filepath.Join(dir, "bad.step"), true, 0, "PARSEC") {
		t.Fatal("invalid unit should be rejected")
	}
}
