package topo

import (
	"fmt"
	"math"
	"strconv"
)

// =========================================================================
// 锚段生成器: 线路中心线 + 锚段规格 → 完整接触网锚段
//   支柱装配 ×N (calc_ocs_span_positions 柱位) + 承力索 + 接触线 + 吊弦群
// 局部约定: 支柱装配 +X 指向线路, 接触线点 = (CX - stagger, 0, contactZ)
// 布局数据与确定性再生成见 ocs_layout.go:
//   ComputeAnchorSectionLayout → (存库/前端编辑) → CreateAnchorSectionFromLayout
// =========================================================================

type AnchorSectionInput struct {
	Centerline      []Point3  `json:"centerline"`      // 线路中心线 (mm)
	ContactHeight   float64   `json:"contactHeight"`   // 导高, 默认 5300
	StructureHeight float64   `json:"structureHeight"` // 结构高度, 默认 1400
	SpanLength      float64   `json:"spanLength"`      // 标准跨距, 默认 50000
	MastHeight      float64   `json:"mastHeight"`      // 柱高, 默认 8000
	MastType        int       `json:"mastType"`        // 1-钢柱, 2-混凝土柱
	SideOffset      float64   `json:"sideOffset"`      // 侧面限界 CX, 默认 2900
	MastSide        float64   `json:"mastSide"`        // 支柱在线路左侧(+1)/右侧(-1), 默认 +1
	StaggerTable    []float64 `json:"staggerTable"`    // 各定位点拉出值; 空则自动之字 ±300
	HasCompensator  bool      `json:"hasCompensator"`  // 两端锚柱设补偿装置
	ContactWireDia  float64   `json:"contactWireDia"`  // 接触线直径, 默认 12.9
	MessengerDia    float64   `json:"messengerDia"`    // 承力索直径, 默认 13.5
	DropperSpacing  float64   `json:"dropperSpacing"`  // 吊弦间距, 默认 8000
}

// 线上点 + 横向单位向量 (left of travel)
type trackFrame struct {
	pos  Point3
	perp [3]float64
}

func frameAt(pts []Point3, mileage float64) trackFrame {
	acc := polyArcLens(pts)
	total := acc[len(acc)-1]
	if mileage < 0 {
		mileage = 0
	}
	if mileage > total {
		mileage = total
	}
	for i := 1; i < len(pts); i++ {
		if acc[i] >= mileage {
			seg := acc[i] - acc[i-1]
			t := (mileage - acc[i-1]) / math.Max(seg, 1e-9)
			d0, d1 := pts[i-1].Data(), pts[i].Data()
			p := NewPoint3([3]float64{d0[0] + (d1[0]-d0[0])*t, d0[1] + (d1[1]-d0[1])*t, d0[2] + (d1[2]-d0[2])*t})
			dx, dy := d1[0]-d0[0], d1[1]-d0[1]
			l := math.Hypot(dx, dy)
			if l < 1e-9 {
				return trackFrame{p, [3]float64{0, 1, 0}}
			}
			return trackFrame{p, [3]float64{-dy / l, dx / l, 0}} // 行进左侧
		}
	}
	last := pts[len(pts)-1]
	return trackFrame{last, [3]float64{0, 1, 0}}
}

// CreateAnchorSection 一键生成锚段装配 (布局数据见 CreateAnchorSectionWithLayout)
func CreateAnchorSection(in AnchorSectionInput) (*Assembly, error) {
	as, _, err := CreateAnchorSectionWithLayout(in)
	return as, err
}

// CreateAnchorSectionWithLayout 同 CreateAnchorSection, 同时返回中间布局数据,
// 供编辑器存库/前端编辑后经 CreateAnchorSectionFromLayout 确定性再生成
func CreateAnchorSectionWithLayout(in AnchorSectionInput) (*Assembly, *AnchorSectionLayout, error) {
	layout, err := ComputeAnchorSectionLayout(in)
	if err != nil {
		return nil, nil, err
	}
	as, err := CreateAnchorSectionFromLayout(layout)
	if err != nil {
		return nil, nil, err
	}
	return as, layout, nil
}

type simpleError string

func (e simpleError) Error() string    { return string(e) }
func errInvalidInput(msg string) error { return fmt.Errorf("ocs anchor: %s", msg) }

func itoa(i int) string { return strconv.Itoa(i) }
