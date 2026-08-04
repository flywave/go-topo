package topo

import (
	"fmt"
	"math"
	"strings"
	"testing"
)

// 站场测试数据: 正线 (0,0)→(400,0) 在 x=100m 处接出一条侧线 (R=350m 左偏)
func buildYardGeoJSON() []byte {
	line := func(x0, y0, x1, y1, step float64) string {
		var pts []string
		n := int((x1-x0)/step + 0.5)
		for i := 0; i <= n; i++ {
			pts = append(pts, fmt.Sprintf("[%.4f,%.4f,0]", x0+float64(i)*step, y0))
		}
		return strings.Join(pts, ",")
	}
	// 侧线: 从 (100,0) 起, R=350m 向左弯, 弧长 ~80m
	var siding []string
	R := 350.0
	for i := 0; i <= 32; i++ {
		th := float64(i) * 0.0072 // 每步 2.52m 弧长
		siding = append(siding, fmt.Sprintf("[%.4f,%.4f,0]", 100+R*math.Sin(th), R-R*math.Cos(th)))
	}
	feature := func(coords string) string {
		return fmt.Sprintf(`{"type":"Feature","geometry":{"type":"LineString","coordinates":[%s]},"properties":{"gauge":1435,"railType":60}}`, coords)
	}
	return []byte(fmt.Sprintf(`{"type":"FeatureCollection","features":[%s,%s,%s]}`,
		feature(line(0, 0, 100, 0, 5)),
		feature(line(100, 0, 400, 0, 5)),
		feature(strings.Join(siding, ","))))
}

func TestCreateYardTurnout(t *testing.T) {
	as, err := CreateYardFromGeoJSON(buildYardGeoJSON())
	if err != nil {
		t.Fatalf("yard failed: %v", err)
	}
	if as == nil {
		t.Fatal("nil assembly")
	}
	n := len(as.GetElements())
	t.Logf("elements: %d", n)
	// 3 边 × (钢轨+轨枕) + 1 道岔 = 7
	if n != 7 {
		t.Fatalf("expect 7 elements, got %d", n)
	}
	bb := as.ToCompound().BBox().Data()
	dx, dy := bb[3]-bb[0], bb[4]-bb[1]
	t.Logf("yard bbox: %.0f x %.0f mm", dx, dy)
	if dx < 380000 || dx > 420000 {
		t.Fatalf("yard length wrong: %.0f", dx)
	}
	if dy < 4000 || dy > 20000 {
		t.Fatalf("yard width wrong: %.0f", dy)
	}
}

func TestCreateYardCrossing(t *testing.T) {
	// 菱形交叉: 两条独立线路中部相交
	mk := func(coords string) string {
		return fmt.Sprintf(`{"type":"Feature","geometry":{"type":"LineString","coordinates":[%s]},"properties":{"gauge":1435}}`, coords)
	}
	var a, b []string
	for x := 0.0; x <= 400; x += 10 {
		a = append(a, fmt.Sprintf("[%.2f,0,0]", x))
	}
	for y := -20.0; y <= 20; y += 4 {
		b = append(b, fmt.Sprintf("[200,%.2f,0]", y))
	}
	coll := []byte(fmt.Sprintf(`{"type":"FeatureCollection","features":[%s,%s]}`,
		mk(strings.Join(a, ",")), mk(strings.Join(b, ","))))
	as, err := CreateYardFromGeoJSON(coll)
	if err != nil {
		t.Fatalf("crossing yard failed: %v", err)
	}
	// 2 边 × (钢轨+轨枕) + 1 辙叉 = 5
	if n := len(as.GetElements()); n != 5 {
		t.Fatalf("expect 5 elements, got %d", n)
	}
}
