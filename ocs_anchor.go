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
// =========================================================================

type AnchorSectionInput struct {
	Centerline      []Point3  // 线路中心线 (mm)
	ContactHeight   float64   // 导高, 默认 5300
	StructureHeight float64   // 结构高度, 默认 1400
	SpanLength      float64   // 标准跨距, 默认 50000
	MastHeight      float64   // 柱高, 默认 8000
	MastType        int       // 1-钢柱, 2-混凝土柱
	SideOffset      float64   // 侧面限界 CX, 默认 2900
	MastSide        float64   // 支柱在线路左侧(+1)/右侧(-1), 默认 +1
	StaggerTable    []float64 // 各定位点拉出值; 空则自动之字 ±300
	HasCompensator  bool      // 两端锚柱设补偿装置
	ContactWireDia  float64   // 接触线直径, 默认 12.9
	MessengerDia    float64   // 承力索直径, 默认 13.5
	DropperSpacing  float64   // 吊弦间距, 默认 8000
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

func CreateAnchorSection(in AnchorSectionInput) (*Assembly, error) {
	if len(in.Centerline) < 2 {
		return nil, errInvalidInput("centerline needs >= 2 points")
	}
	if in.ContactHeight <= 0 {
		in.ContactHeight = 5300
	}
	if in.StructureHeight <= 0 {
		in.StructureHeight = 1400
	}
	if in.SpanLength <= 0 {
		in.SpanLength = 50000
	}
	if in.MastHeight <= 0 {
		in.MastHeight = 8000
	}
	if in.SideOffset <= 0 {
		in.SideOffset = 2900
	}
	if in.MastSide == 0 {
		in.MastSide = 1
	}
	if in.ContactWireDia <= 0 {
		in.ContactWireDia = 12.9
	}
	if in.MessengerDia <= 0 {
		in.MessengerDia = 13.5
	}
	if in.DropperSpacing <= 0 {
		in.DropperSpacing = 8000
	}

	// 柱位计算 (拉出值缺省时自动之字 ±300)
	if len(in.StaggerTable) == 0 {
		totalLen := polyArcLens(in.Centerline)
		n := int(totalLen[len(totalLen)-1]/in.SpanLength) + 2
		in.StaggerTable = make([]float64, n)
		for i := range in.StaggerTable {
			if i%2 == 0 {
				in.StaggerTable[i] = 300
			} else {
				in.StaggerTable[i] = -300
			}
		}
	}
	span := CalcOcsSpanPositions(OcsSpanInput{
		Centerline:      in.Centerline,
		ContactHeight:   in.ContactHeight,
		StructureHeight: in.StructureHeight,
		StaggerTable:    in.StaggerTable,
		SpanLength:      in.SpanLength,
		MastHeight:      in.MastHeight,
		HasCompensator:  in.HasCompensator,
	})
	if span.MastCount == 0 {
		return nil, errInvalidInput("no mast positions computed")
	}

	var root *Assembly
	addShape := func(s *Shape, name string) {
		if s == nil || s.IsNull() {
			return
		}
		obj := NewAssemblyObjectFromShpe(*s)
		if root == nil {
			root = NewAssembly(obj, nil, name, nil)
		} else {
			root.AddObject(obj, nil, name, nil)
		}
	}

	side := in.MastSide
	// 各支柱的接触线点 (世界坐标) + 承力索点
	type wirePts struct{ contact, messenger Point3 }
	wpts := make([]wirePts, len(span.Masts))

	for i, m := range span.Masts {
		f := frameAt(in.Centerline, m.Mileage*1000) // 里程 m → mm
		perp := [3]float64{f.perp[0] * side, f.perp[1] * side, 0}
		// 支柱位置: 线路中心 + perp*(CX) (柱中心)
		cp := f.pos.Data()
		mastPos := NewPoint3([3]float64{cp[0] + perp[0]*in.SideOffset, cp[1] + perp[1]*in.SideOffset, cp[2]})
		// 接触线点: 线路中心 + perp*stagger
		cw := NewPoint3([3]float64{cp[0] + perp[0]*m.Stagger, cp[1] + perp[1]*m.Stagger, cp[2] + m.ContactWireZ})
		mw := NewPoint3([3]float64{cp[0] + perp[0]*m.Stagger, cp[1] + perp[1]*m.Stagger, cp[2] + m.MessengerWireZ})
		wpts[i] = wirePts{cw, mw}

		// 支柱装配: 局部 +X 指向线路 = -perp
		mp := MastAssemblyParams{
			MastType:        in.MastType,
			MastHeight:      m.MastHeight,
			CantileverType:  1,
			ArmDiameter:     60,
			Stagger:         m.Stagger * side, // 局部 X 朝线路, 拉出值换算
			CompType:        0,
			ContactHeight:   in.ContactHeight,
			StructureHeight: in.StructureHeight,
			SideOffset:      in.SideOffset,
		}
		if in.HasCompensator && m.IsTensionMast {
			mp.CompType = 1
			mp.HasGuyWire = true
			mp.RatedTension = 15
		}
		addShape(CreateMastAssemblyWithPlace(mp, mastPos,
			NewDir3FromXYZ([3]float64{-perp[0], -perp[1], 0}),
			NewDir3FromXYZ([3]float64{0, 0, 1})), "mast_"+itoa(i))
	}

	// 跨间线索 + 吊弦
	sagC := in.SpanLength * 0.0005 // 接触线预留弛度
	sagM := in.SpanLength * 0.015  // 承力索弛度
	cwp := ContactWireParams{Diameter: in.ContactWireDia, BottomRadius: 8, TopRadius: 3}
	mwp := MessengerWireParams{Diameter: in.MessengerDia}
	for i := 0; i+1 < len(wpts); i++ {
		cw0, cw1 := wpts[i].contact, wpts[i+1].contact
		mw0, mw1 := wpts[i].messenger, wpts[i+1].messenger
		cwp.Sag = sagC
		addShape(CreateContactWire(cwp, cw0, cw1), "cw_"+itoa(i))
		mwp.Sag = sagM
		addShape(CreateMessengerWire(mwp, mw0, mw1), "mw_"+itoa(i))

		// 吊弦: 沿跨按间距布置, 长度 = 承力索弧垂 - 接触线弧垂
		spanLen := ptDist(cw0, cw1)
		n := int(spanLen / in.DropperSpacing)
		if n < 1 {
			n = 1
		}
		for k := 1; k <= n; k++ {
			t := float64(k) / float64(n+1)
			top := evalSagPoint(mw0, mw1, t, sagM)
			bot := evalSagPoint(cw0, cw1, t, sagC)
			l := top.Data()[2] - bot.Data()[2]
			if l < 100 {
				continue
			}
			dp := DropperParams{Length: l, WireDiameter: 4.5, ClampLength: 60, ClampWidth: 40, ClampThickness: 6, Conductive: true}
			addShape(CreateDropperWithPlace(dp, top, NewDir3FromXYZ([3]float64{0, 0, 1})), "dropper")
		}
	}

	if root == nil {
		return nil, errInvalidInput("no geometry generated")
	}
	return root, nil
}

// 两点连线上 t 处 + 抛物线弛度
func evalSagPoint(p0, p1 Point3, t, sag float64) Point3 {
	a, b := p0.Data(), p1.Data()
	return NewPoint3([3]float64{
		a[0] + (b[0]-a[0])*t,
		a[1] + (b[1]-a[1])*t,
		a[2] + (b[2]-a[2])*t - 4*sag*t*(1-t),
	})
}

type simpleError string

func (e simpleError) Error() string { return string(e) }
func errInvalidInput(msg string) error { return fmt.Errorf("ocs anchor: %s", msg) }

func itoa(i int) string { return strconv.Itoa(i) }
