package topo

import (
	"encoding/json"
	"fmt"
	"math"
)

// =========================================================================
// GeoJSON 轨道中心线输入 → 三维轨道模型
//
// 设计原则: 区间正线只需轨道中心线一条 LineString, 钢轨(±gauge/2 偏移)、
// 轨枕、道床全部由中心线自动派生, 不需要逐根钢轨的数据。
// 坐标约定: GeoJSON 坐标默认为米 (CGCS2000 投影坐标), 模型为毫米 (1:1),
// 默认缩放 1000, 可通过 properties.coordScale 覆盖。
// =========================================================================

// TrackGeoProperties 轨道中心线 Feature 的属性表
type TrackGeoProperties struct {
	Gauge            float64 `json:"gauge"`            // 轨距(mm), 默认 1435
	RailType         float64 `json:"railType"`         // 钢轨类型 kg/m: 43/50/60/75, 默认 60
	SuperElevation   float64 `json:"superElevation"`   // 超高(mm), 默认 0
	CoordScale       float64 `json:"coordScale"`       // 坐标→mm 缩放, 默认 1000 (米输入)
	SleeperLength    float64 `json:"sleeperLength"`    // 轨枕长(mm), 默认 2600
	SleeperWidth     float64 `json:"sleeperWidth"`     // 默认 260
	SleeperHeight    float64 `json:"sleeperHeight"`    // 默认 200
	SleeperSpacing   float64 `json:"sleeperSpacing"`   // 默认 600
	BallastTopWidth  float64 `json:"ballastTopWidth"`  // 道床顶宽(mm), 默认 3600; 0=不生成道床
	BallastThickness float64 `json:"ballastThickness"` // 默认 300
	BallastSlope     float64 `json:"ballastSlope"`     // 边坡 1:n, 默认 1.5
	NoSleepers       bool    `json:"noSleepers"`       // true=不生成轨枕, 默认生成
}

func (p *TrackGeoProperties) withDefaults() {
	if p.Gauge <= 0 {
		p.Gauge = 1435
	}
	if p.RailType <= 0 {
		p.RailType = 60
	}
	if p.CoordScale <= 0 {
		p.CoordScale = 1000
	}
	if p.SleeperLength <= 0 {
		p.SleeperLength = 2600
	}
	if p.SleeperWidth <= 0 {
		p.SleeperWidth = 260
	}
	if p.SleeperHeight <= 0 {
		p.SleeperHeight = 200
	}
	if p.SleeperSpacing <= 0 {
		p.SleeperSpacing = 600
	}
	if p.BallastTopWidth < 0 {
		p.BallastTopWidth = 0
	}
	if p.BallastThickness <= 0 {
		p.BallastThickness = 300
	}
	if p.BallastSlope <= 0 {
		p.BallastSlope = 1.5
	}
}

// 标准钢轨断面查表 (与 C++ standard_rail_params 一致)
// 返回 railHeight, headWidth, baseWidth
func standardRailDims(kgPerMeter float64) (float64, float64, float64) {
	switch int(math.Round(kgPerMeter)) {
	case 43:
		return 140, 70, 114
	case 50:
		return 152, 70, 132
	case 75:
		return 192, 75, 150
	default: // 60
		return 176, 73, 150
	}
}

type geoJSONFeature struct {
	Type       string `json:"type"`
	Geometry   struct {
		Type        string          `json:"type"`
		Coordinates [][]float64     `json:"coordinates"`
	} `json:"geometry"`
	Properties TrackGeoProperties `json:"properties"`
}

type geoJSONInput struct {
	Type       string           `json:"type"`
	Features   []geoJSONFeature `json:"features"`
	Geometry   *struct {
		Type        string      `json:"type"`
		Coordinates [][]float64 `json:"coordinates"`
	} `json:"geometry"`
	Properties  TrackGeoProperties `json:"properties"`
	Coordinates [][]float64        `json:"coordinates"`
}

// ParseTrackGeoJSON 解析单个 LineString Feature (或裸 LineString),
// 返回毫米单位的中心线点列与属性
func ParseTrackGeoJSON(data []byte) ([]Point3, TrackGeoProperties, error) {
	var in geoJSONInput
	if err := json.Unmarshal(data, &in); err != nil {
		return nil, TrackGeoProperties{}, fmt.Errorf("invalid GeoJSON: %w", err)
	}
	var coords [][]float64
	props := in.Properties
	switch in.Type {
	case "Feature":
		if in.Geometry == nil || in.Geometry.Type != "LineString" {
			return nil, TrackGeoProperties{}, fmt.Errorf("Feature geometry must be LineString")
		}
		coords = in.Geometry.Coordinates
	case "LineString":
		coords = in.Coordinates
	case "FeatureCollection":
		return nil, TrackGeoProperties{}, fmt.Errorf("FeatureCollection 请用 CreateTrackFromGeoJSON")
	default:
		return nil, TrackGeoProperties{}, fmt.Errorf("unsupported GeoJSON type %q", in.Type)
	}
	if len(coords) < 2 {
		return nil, TrackGeoProperties{}, fmt.Errorf("LineString needs at least 2 points")
	}
	props.withDefaults()
	pts := make([]Point3, len(coords))
	for i, c := range coords {
		if len(c) < 2 {
			return nil, TrackGeoProperties{}, fmt.Errorf("coordinate %d has <2 elements", i)
		}
		z := 0.0
		if len(c) >= 3 {
			z = c[2]
		}
		pts[i] = NewPoint3([3]float64{c[0] * props.CoordScale, c[1] * props.CoordScale, z * props.CoordScale})
	}
	return pts, props, nil
}

// CreateTrackFromCenterline 由中心线派生完整正线: 钢轨×2 + 轨枕 + 道床
func CreateTrackFromCenterline(centerline []Point3, props TrackGeoProperties) *Assembly {
	props.withDefaults()
	railH, headW, baseW := standardRailDims(props.RailType)

	rails := CreateRailPairFromPoints(centerline, props.Gauge, props.SuperElevation, railH, headW, baseW)
	if rails == nil {
		return nil
	}
	root := NewAssemblyObjectFromShpe(*rails)
	as := NewAssembly(root, nil, "track", nil)

	if !props.NoSleepers {
		sleepers := CreateSleeperLayout(centerline, props.SleeperLength,
			props.SleeperWidth, props.SleeperHeight, props.SleeperSpacing, props.Gauge)
		if sleepers != nil {
			as.AddObject(NewAssemblyObjectFromShpe(*sleepers), nil, "sleepers", nil)
		}
	}
	if props.BallastTopWidth > 0 {
		ballast := CreateBallastAlongPath(centerline, props.BallastTopWidth,
			props.BallastThickness, props.BallastSlope)
		if ballast != nil {
			as.AddObject(NewAssemblyObjectFromShpe(*ballast), nil, "ballast", nil)
		}
	}
	return as
}

// CreateTrackFromGeoJSON 从 GeoJSON (Feature / LineString / FeatureCollection)
// 生成三维轨道装配
func CreateTrackFromGeoJSON(data []byte) (*Assembly, error) {
	var in geoJSONInput
	if err := json.Unmarshal(data, &in); err != nil {
		return nil, fmt.Errorf("invalid GeoJSON: %w", err)
	}
	if in.Type == "FeatureCollection" {
		var root *Assembly
		for i, f := range in.Features {
			if f.Geometry.Type != "LineString" || len(f.Geometry.Coordinates) < 2 {
				continue
			}
			raw, _ := json.Marshal(f)
			pts, props, err := ParseTrackGeoJSON(raw)
			if err != nil {
				return nil, err
			}
			sub := CreateTrackFromCenterline(pts, props)
			if sub == nil {
				continue
			}
			if root == nil {
				root = sub
			} else {
				root.AddAssembly(sub, nil, fmt.Sprintf("track_%d", i), nil)
			}
		}
		if root == nil {
			return nil, fmt.Errorf("no valid LineString features")
		}
		return root, nil
	}
	pts, props, err := ParseTrackGeoJSON(data)
	if err != nil {
		return nil, err
	}
	as := CreateTrackFromCenterline(pts, props)
	if as == nil {
		return nil, fmt.Errorf("failed to build track")
	}
	return as, nil
}
