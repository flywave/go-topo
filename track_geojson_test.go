package topo

import (
	"fmt"
	"math"
	"testing"
)

// 构造测试用 GeoJSON: 直线 50m + 800m 半径圆弧 (米单位坐标)
func buildTestTrackGeoJSON() []byte {
	coords := ""
	// 直线段
	for x := 0.0; x <= 50; x += 5 {
		coords += fmt.Sprintf("[%.3f,%.3f,0],", x, 0.0)
	}
	// 圆弧段 (R=800m, 转角 10°)
	R := 800.0
	cx, cy := 50.0, R // 圆心在 +Y
	for i := 1; i <= 20; i++ {
		th := float64(i) * 10.0 * math.Pi / 180.0 / 20
		x := cx + R*math.Sin(th)
		y := cy - R*math.Cos(th)
		coords += fmt.Sprintf("[%.3f,%.3f,0],", x, y)
	}
	coords = coords[:len(coords)-1]
	return []byte(fmt.Sprintf(`{
  "type": "Feature",
  "geometry": {"type": "LineString", "coordinates": [%s]},
  "properties": {
    "gauge": 1435,
    "railType": 60,
    "superElevation": 0,
    "sleeperSpacing": 600,
    "ballastTopWidth": 3600
  }
}`, coords))
}

func TestParseTrackGeoJSON(t *testing.T) {
	pts, props, err := ParseTrackGeoJSON(buildTestTrackGeoJSON())
	if err != nil {
		t.Fatalf("parse failed: %v", err)
	}
	if len(pts) != 31 {
		t.Fatalf("expect 31 points, got %d", len(pts))
	}
	// 米 → 毫米缩放
	d := pts[1].Data()
	if math.Abs(d[0]-5000) > 1 {
		t.Fatalf("coord scale wrong: x=%v (expect 5000)", d[0])
	}
	if props.Gauge != 1435 || props.RailType != 60 {
		t.Fatalf("props wrong: %+v", props)
	}
}

func TestCreateTrackFromGeoJSON(t *testing.T) {
	as, err := CreateTrackFromGeoJSON(buildTestTrackGeoJSON())
	if err != nil {
		t.Fatalf("create failed: %v", err)
	}
	if as == nil {
		t.Fatal("nil assembly")
	}
	elems := as.GetElements()
	if len(elems) != 3 {
		t.Fatalf("expect 3 elements (rails+sleepers+ballast), got %d", len(elems))
	}
	// 整体包围盒: 长度约 190m (直线 50 + 弧长 140), 含道床边坡外扩
	cmp := as.ToCompound()
	if cmp == nil {
		t.Fatal("nil compound")
	}
	bb := cmp.BBox().Data()
	dx := bb[3] - bb[0]
	dy := bb[4] - bb[1]
	dz := bb[5] - bb[2]
	t.Logf("track bbox: %.0f x %.0f x %.0f mm", dx, dy, dz)
	if dx < 150000 || dx > 220000 {
		t.Fatalf("track length out of range: %.0f", dx)
	}
	if dy < 2000 || dy > 30000 {
		t.Fatalf("track width out of range: %.0f", dy)
	}
	if dz < 300 || dz > 2000 {
		t.Fatalf("track height out of range: %.0f", dz)
	}
	// 钢轨元素自身长度应接近全线长 (防止只覆盖首段)
	for _, el := range as.GetElements() {
		if el.GetName() == "track" {
			rb := el.GetShape().BBox().Data()
			if rb[3]-rb[0] < 150000 {
				t.Fatalf("rails too short: %.0f (只覆盖了首段?)", rb[3]-rb[0])
			}
		}
		if el.GetName() == "sleepers" {
			// 曲线上轨枕应垂直于线路切向: 枕木群整体宽度应包含曲线偏移
			sb := el.GetShape().BBox().Data()
			if sb[4]-sb[1] < 8000 {
				t.Fatalf("sleepers 未随曲线偏转: 宽度 %.0f", sb[4]-sb[1])
			}
		}
	}
}

func TestCreateTrackFromGeoJSONCollection(t *testing.T) {
	feat := string(buildTestTrackGeoJSON())
	coll := []byte(fmt.Sprintf(`{"type":"FeatureCollection","features":[%s,%s]}`, feat, feat))
	as, err := CreateTrackFromGeoJSON(coll)
	if err != nil {
		t.Fatalf("collection failed: %v", err)
	}
	if as == nil {
		t.Fatal("nil assembly for collection")
	}
}
