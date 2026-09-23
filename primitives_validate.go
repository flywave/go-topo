package topo

// primitives_validate.go — GIM 参数化选项规范对齐层。
//
// 值域依据:
//   - Q/GDW 11809—2018《输变电工程三维设计模型交互规范》附录 B（基本图元/型钢驱动参数表）
//   - Q/GDW 11810.2—2018《建模规范 第 2 部分：架空输电线路》附录 A/E（基础/地脚螺栓/杆塔）
//   - T/CEC 5056.3—2021《建模规范 第 3 部分：电缆线路》附录 A/B
//
// 三个能力:
//   1. Validate() — 规范值域校验（逐参数, 给出违规字段明细）
//   2. normalizeSpecDefaults() — 规范默认值（如 Ring/CircularGasket/TableGasket 的 Rad 默认 2π）
//   3. rejectParams() — Create* 入口统一防御: hasNaN ∪ 规范值域违规 → 拒绝生成
//
// 对规范未给出显式值域的控制参数（GT 基础、EC 电缆类）按防御编程原则
// 施加正值/非负/数组一致性/枚举取值校验, 关系式(如 D≥d)按附录 E 注释执行。

import (
	"fmt"
	"math"
	"reflect"
	"strings"
)

const twoPiF = 2.0 * math.Pi

// specAngleTol 与 C++ 侧全角判定容差一致（float32 2π 精度问题, 见加固报告 #5）
const specAngleTol = 1e-6

// specValidator 逐字段收集违规项。
type specValidator struct{ errs []string }

func (v *specValidator) relation(cond bool, format string, args ...interface{}) {
	if !cond {
		v.errs = append(v.errs, fmt.Sprintf(format, args...))
	}
}

// positive 要求 > 0
func positive[T float32 | float64](v *specValidator, field string, val T) {
	v.relation(val > 0, "%s 必须 > 0 (当前 %v)", field, val)
}

// nonNegative 要求 >= 0
func nonNegative[T float32 | float64](v *specValidator, field string, val T) {
	v.relation(val >= 0, "%s 必须 >= 0 (当前 %v)", field, val)
}

// inRange 闭区间取值
func inRange[T float32 | float64](v *specValidator, field string, val, lo, hi T) {
	v.relation(val >= lo && val <= hi, "%s 必须在 [%v, %v] 内 (当前 %v)", field, lo, hi, val)
}

// enumIn 整型枚举取值
func enumIn(v *specValidator, field string, val int32, allowed ...int32) {
	ok := false
	for _, a := range allowed {
		if val == a {
			ok = true
			break
		}
	}
	v.relation(ok, "%s 取值须为 %v 之一 (当前 %d)", field, allowed, val)
}

func (v *specValidator) err() error {
	if len(v.errs) == 0 {
		return nil
	}
	return fmt.Errorf("primitives: 参数超出规范值域: %s", strings.Join(v.errs, "; "))
}

func validateSliceLen[T any](v *specValidator, field string, s []T, minLen int) {
	v.relation(len(s) >= minLen, "%s 长度须 >= %d (当前 %d)", field, minLen, len(s))
}

// ==================== 换流站基本图元（Q/GDW 11809—2018 附录 B） ====================

// Sphere: R>0
func (p *SphereParams) Validate() error {
	v := &specValidator{}
	positive(v, "R", p.Radius)
	return v.err()
}

// RotationalEllipsoid: LR>0, WR>0, 0<H≤2LR
func (p *RotationalEllipsoidParams) Validate() error {
	v := &specValidator{}
	positive(v, "LR", p.PolarRadius)
	positive(v, "WR", p.EquatorialRadius)
	positive(v, "H", p.Height)
	v.relation(float64(p.Height) <= 2*float64(p.PolarRadius)+specAngleTol, "H 须 <= 2*LR (当前 H=%v, LR=%v)", p.Height, p.PolarRadius)
	return v.err()
}

// Cuboid: L>0, W>0, H>0
func (p *CuboidParams) Validate() error {
	v := &specValidator{}
	positive(v, "L", p.Length)
	positive(v, "W", p.Width)
	positive(v, "H", p.Height)
	return v.err()
}

// Table(棱台锥): LL1>0, LL2>0, H>0, TL1≥0, TL2≥0, 顶底为相似菱形(TL1/LL1=TL2/LL2), 锥顶时 TL1=TL2=0
func (p *DiamondFrustumParams) Validate() error {
	v := &specValidator{}
	nonNegative(v, "TL1", p.TopDiag1)
	nonNegative(v, "TL2", p.TopDiag2)
	positive(v, "LL1", p.BottomDiag1)
	positive(v, "LL2", p.BottomDiag2)
	positive(v, "H", p.Height)
	v.relation(p.TopDiag1 <= p.BottomDiag1, "TL1 须 <= LL1 (当前 %v > %v)", p.TopDiag1, p.BottomDiag1)
	v.relation(p.TopDiag2 <= p.BottomDiag2, "TL2 须 <= LL2 (当前 %v > %v)", p.TopDiag2, p.BottomDiag2)
	v.relation((p.TopDiag1 == 0) == (p.TopDiag2 == 0), "锥顶时 TL1 与 TL2 应同时为 0")
	if p.TopDiag1 > 0 && p.BottomDiag1 > 0 && p.BottomDiag2 > 0 {
		r1 := float64(p.TopDiag1) / float64(p.BottomDiag1)
		r2 := float64(p.TopDiag2) / float64(p.BottomDiag2)
		v.relation(math.Abs(r1-r2) <= 1e-3, "顶底面须为相似菱形: TL1/LL1=%v 与 TL2/LL2=%v 不一致", r1, r2)
	}
	return v.err()
}

// OffsetRectangularTable: TL≥0, TW≥0, LL≥TL, LW≥TW, H>0
func (p *OffsetRectangularTableParams) Validate() error {
	v := &specValidator{}
	nonNegative(v, "TL", p.TopLength)
	nonNegative(v, "TW", p.TopWidth)
	positive(v, "LL", p.BottomLength)
	positive(v, "LW", p.BottomWidth)
	positive(v, "H", p.Height)
	v.relation(p.BottomLength >= p.TopLength, "LL 须 >= TL (当前 %v < %v)", p.BottomLength, p.TopLength)
	v.relation(p.BottomWidth >= p.TopWidth, "LW 须 >= TW (当前 %v < %v)", p.BottomWidth, p.TopWidth)
	return v.err()
}

// Cylinder: R>0, H>0
func (p *CylinderShapeParams) Validate() error {
	v := &specValidator{}
	positive(v, "R", p.Radius)
	positive(v, "H", p.Height)
	return v.err()
}

// BendingCylindrical(弯折圆柱): R>0, L>0, 0<Rad<2PI
func (p *SharpBentCylinderParams) Validate() error {
	v := &specValidator{}
	positive(v, "R", p.Radius)
	positive(v, "L", p.Length)
	v.relation(float64(p.BendAngle) > 0 && float64(p.BendAngle) < twoPiF, "Rad 须在 (0, 2π) 内 (当前 %v)", p.BendAngle)
	return v.err()
}

// TruncatedCone(圆台): TR≥0, BR≥TR, H>0
func (p *TruncatedConeParams) Validate() error {
	v := &specValidator{}
	nonNegative(v, "TR", p.TopRadius)
	positive(v, "BR", p.BottomRadius)
	positive(v, "H", p.Height)
	v.relation(p.BottomRadius >= p.TopRadius, "BR 须 >= TR (当前 %v < %v)", p.BottomRadius, p.TopRadius)
	return v.err()
}

// EccentricTruncatedCone(偏心圆台): TR≥0, BR≥TR, H>0, TOPXOFF≥0, TOPYOFF≥0
func (p *EccentricTruncatedConeParams) Validate() error {
	v := &specValidator{}
	nonNegative(v, "TR", p.TopRadius)
	positive(v, "BR", p.BottomRadius)
	positive(v, "H", p.Height)
	nonNegative(v, "TOPXOFF", p.TopXOffset)
	nonNegative(v, "TOPYOFF", p.TopYOffset)
	v.relation(p.BottomRadius >= p.TopRadius, "BR 须 >= TR (当前 %v < %v)", p.BottomRadius, p.TopRadius)
	return v.err()
}

// Ring(圆环): R>0, 0<DR<R, 0<Rad≤2PI（默认 2PI）
func (p *RingParams) Validate() error {
	v := &specValidator{}
	positive(v, "R", p.RingRadius)
	v.relation(float64(p.TubeRadius) > 0 && float64(p.TubeRadius) < float64(p.RingRadius), "DR 须在 (0, R) 内 (当前 DR=%v, R=%v)", p.TubeRadius, p.RingRadius)
	// Rad<=0 表示省略, 由 normalizeSpecDefaults 取规范默认 2π
	v.relation(float64(p.Angle) <= twoPiF+specAngleTol, "Rad 不得 > 2π (当前 %v)", p.Angle)
	return v.err()
}

// normalizeSpecDefaults Rad 缺省为整圆（规范"默认 2PI"）
func (p *RingParams) normalizeSpecDefaults() {
	if p.Angle <= 0 {
		p.Angle = float32(twoPiF)
	}
}

// RectangularRing(矩形环): W>0, L>W, 0<DR<W, R<W/2
func (p *RectangularRingParams) Validate() error {
	v := &specValidator{}
	positive(v, "W", p.Width)
	positive(v, "L", p.Length)
	v.relation(float64(p.TubeRadius) > 0 && float64(p.TubeRadius) < float64(p.Width), "DR 须在 (0, W) 内 (当前 DR=%v, W=%v)", p.TubeRadius, p.Width)
	v.relation(float64(p.FilletRadius) >= 0 && float64(p.FilletRadius) < float64(p.Width)/2, "R 须在 [0, W/2) 内 (当前 R=%v, W=%v)", p.FilletRadius, p.Width)
	v.relation(p.Length > p.Width, "L 须 > W (当前 L=%v, W=%v)", p.Length, p.Width)
	return v.err()
}

// EllipticRing(椭圆环): L>W>0, 0<DR<W
func (p *EllipticRingParams) Validate() error {
	v := &specValidator{}
	positive(v, "L(长半轴)", p.MajorRadius)
	positive(v, "W(短半轴)", p.MinorRadius)
	positive(v, "DR", p.TubeRadius)
	v.relation(p.MajorRadius > p.MinorRadius, "L 须 > W (当前 L=%v, W=%v)", p.MajorRadius, p.MinorRadius)
	v.relation(float64(p.TubeRadius) < float64(p.MinorRadius), "DR 须 < W (当前 DR=%v, W=%v)", p.TubeRadius, p.MinorRadius)
	return v.err()
}

// CircularGasket(圆形垫片): OR>IR>0, H>0, 0<Rad≤2PI（默认 2PI）
func (p *CircularGasketParams) Validate() error {
	v := &specValidator{}
	positive(v, "OR", p.OuterRadius)
	positive(v, "IR", p.InnerRadius)
	positive(v, "H", p.Height)
	v.relation(p.OuterRadius > p.InnerRadius, "OR 须 > IR (当前 %v <= %v)", p.OuterRadius, p.InnerRadius)
	// Rad<=0 表示省略, 由 normalizeSpecDefaults 取规范默认 2π
	v.relation(float64(p.Angle) <= twoPiF+specAngleTol, "Rad 不得 > 2π (当前 %v)", p.Angle)
	return v.err()
}

// normalizeSpecDefaults Rad 缺省为整圆
func (p *CircularGasketParams) normalizeSpecDefaults() {
	if p.Angle <= 0 {
		p.Angle = float32(twoPiF)
	}
}

// TableGasket(台型垫片): OR>TR>IR>0, H>0, 0<Rad≤2PI（默认 2PI）
func (p *TableGasketParams) Validate() error {
	v := &specValidator{}
	positive(v, "OR", p.OuterRadius)
	positive(v, "IR", p.InnerRadius)
	positive(v, "TR", p.TopRadius)
	positive(v, "H", p.Height)
	v.relation(p.InnerRadius < p.TopRadius && p.TopRadius < p.OuterRadius, "须 IR < TR < OR (当前 IR=%v, TR=%v, OR=%v)", p.InnerRadius, p.TopRadius, p.OuterRadius)
	// Rad<=0 表示省略, 由 normalizeSpecDefaults 取规范默认 2π
	v.relation(float64(p.Angle) <= twoPiF+specAngleTol, "Rad 不得 > 2π (当前 %v)", p.Angle)
	return v.err()
}

// normalizeSpecDefaults Rad 缺省为整圆
func (p *TableGasketParams) normalizeSpecDefaults() {
	if p.Angle <= 0 {
		p.Angle = float32(twoPiF)
	}
}

// SquareGasket(方形垫片): L1>L2>0, W1>W2>0, H>0, CT∈{1,2,3};
// CT=2(圆角)时 0<Rad≤PI; CT=3(切角)时 0≤CL<(L1-L2)+(W1-W2)
func (p *SquareGasketParams) Validate() error {
	v := &specValidator{}
	positive(v, "L2", p.InnerLength)
	positive(v, "W2", p.InnerWidth)
	positive(v, "H", p.Height)
	v.relation(p.OuterLength > p.InnerLength, "L1 须 > L2 (当前 %v <= %v)", p.OuterLength, p.InnerLength)
	v.relation(p.OuterWidth > p.InnerWidth, "W1 须 > W2 (当前 %v <= %v)", p.OuterWidth, p.InnerWidth)
	enumIn(v, "CT", p.CornerType, 1, 2, 3)
	if p.CornerType == 2 {
		v.relation(float64(p.CornerParam) > 0 && float64(p.CornerParam) <= math.Pi+specAngleTol, "圆角 Rad 须在 (0, π] 内 (当前 %v)", p.CornerParam)
	}
	if p.CornerType == 3 {
		maxCL := float64(p.OuterLength-p.InnerLength) + float64(p.OuterWidth-p.InnerWidth)
		v.relation(float64(p.CornerParam) >= 0 && float64(p.CornerParam) < maxCL, "切角 CL 须在 [0, (L1-L2)+(W1-W2)=%v) 内 (当前 %v)", maxCL, p.CornerParam)
	}
	return v.err()
}

// StretchedBody(拉伸体): 顶点数≥3, L>0
func (p *StretchedBodyParams) Validate() error {
	v := &specValidator{}
	validateSliceLen(v, "Array 顶点", p.Points, 3)
	positive(v, "L", p.Length)
	return v.err()
}

// PorcelainBushing(瓷套/绝缘子): H>0, R>0, R1≥R2, R2>R, N>0
func (p *PorcelainBushingParams) Validate() error {
	v := &specValidator{}
	positive(v, "H", p.Height)
	positive(v, "R", p.Radius)
	positive(v, "R1(大伞裙)", p.BigSkirtRadius)
	v.relation(p.BigSkirtRadius >= p.SmallSkirtRadius, "R1 须 >= R2 (当前 %v < %v)", p.BigSkirtRadius, p.SmallSkirtRadius)
	v.relation(float64(p.SmallSkirtRadius) > float64(p.Radius), "R2 须 > R (当前 %v <= %v)", p.SmallSkirtRadius, p.Radius)
	v.relation(p.Count > 0, "N 必须 > 0 (当前 %d)", p.Count)
	return v.err()
}

// ConePorcelainBushing(锥形瓷套): H>0, BR>0, TR>0, BR1>BR, BR2>BR, TR1>TR, TR2>TR, N>0
func (p *ConePorcelainBushingParams) Validate() error {
	v := &specValidator{}
	positive(v, "H", p.Height)
	positive(v, "BR", p.BottomRadius)
	positive(v, "TR", p.TopRadius)
	positive(v, "BR1", p.BottomSkirtRadius1)
	positive(v, "BR2", p.BottomSkirtRadius2)
	positive(v, "TR1", p.TopSkirtRadius1)
	positive(v, "TR2", p.TopSkirtRadius2)
	v.relation(p.BottomSkirtRadius1 > p.BottomRadius, "BR1 须 > BR (当前 %v <= %v)", p.BottomSkirtRadius1, p.BottomRadius)
	v.relation(p.BottomSkirtRadius2 > p.BottomRadius, "BR2 须 > BR (当前 %v <= %v)", p.BottomSkirtRadius2, p.BottomRadius)
	v.relation(p.TopSkirtRadius1 > p.TopRadius, "TR1 须 > TR (当前 %v <= %v)", p.TopSkirtRadius1, p.TopRadius)
	v.relation(p.TopSkirtRadius2 > p.TopRadius, "TR2 须 > TR (当前 %v <= %v)", p.TopSkirtRadius2, p.TopRadius)
	v.relation(p.Count > 0, "N 必须 > 0 (当前 %d)", p.Count)
	return v.err()
}

// Insulator(绝缘子串): N>0, D>2*R1, N1>0, H1>0, R1≥R2, R2>R, R>0, FL>0, AL>0, LN>0
func (p *InsulatorStringParams) Validate() error {
	v := &specValidator{}
	positive(v, "N(联数)", float32(p.Count))
	if p.Count >= 2 {
		positive(v, "D(双串间距)", p.Spacing)
	} else {
		nonNegative(v, "D(单联间距)", p.Spacing)
	}
	positive(v, "N1", float32(p.InsulatorCount))
	positive(v, "H1", p.Height)
	positive(v, "R1(大伞裙)", p.BigSkirtRadius)
	positive(v, "R", p.Radius)
	positive(v, "FL", p.FrontLength)
	positive(v, "AL", p.BackLength)
	positive(v, "LN", float32(p.SplitCount))
	v.relation(p.BigSkirtRadius >= p.SmallSkirtRadius, "R1 须 >= R2 (当前 %v < %v)", p.BigSkirtRadius, p.SmallSkirtRadius)
	v.relation(float64(p.SmallSkirtRadius) > float64(p.Radius), "R2 须 > R (当前 %v <= %v)", p.SmallSkirtRadius, p.Radius)
	if p.Count >= 2 {
		v.relation(float64(p.Spacing) > 2*float64(p.BigSkirtRadius), "D 须 > 2*R1 (当前 D=%v, R1=%v)", p.Spacing, p.BigSkirtRadius)
	}
	return v.err()
}

// VTypeInsulator(V型绝缘子串): X>0, AD>0, N1>0, H1>0, R>0, R1>R2, R2>0, FL>0, AL>0, LN>0
func (p *VTypeInsulatorParams) Validate() error {
	v := &specValidator{}
	positive(v, "X(前端间距)", p.FrontSpacing)
	positive(v, "AD(后端间距)", p.BackSpacing)
	positive(v, "N1", float32(p.InsulatorCount))
	positive(v, "H1", p.Height)
	positive(v, "R(伞顶面)", p.Radius)
	positive(v, "R1(大伞)", p.BigSkirtRadius)
	positive(v, "R2(小伞)", p.SmallSkirtRadius)
	positive(v, "FL", p.FrontLength)
	positive(v, "AL", p.BackLength)
	positive(v, "LN", float32(p.SplitCount))
	v.relation(p.BigSkirtRadius > p.SmallSkirtRadius, "R1 须 > R2 (当前 %v <= %v)", p.BigSkirtRadius, p.SmallSkirtRadius)
	return v.err()
}

// TerminalBlock(端子板): L>W, W>0, T>0, CL>0, CS>0, RS>0, R>0, BL>0
func (p *TerminalBlockParams) Validate() error {
	v := &specValidator{}
	positive(v, "W", p.Width)
	positive(v, "T", p.Thickness)
	positive(v, "CL", p.ChamferLength)
	positive(v, "CS", p.ColumnSpacing)
	positive(v, "RS", p.RowSpacing)
	positive(v, "R", p.HoleRadius)
	positive(v, "BL", p.BottomOffset)
	positive(v, "L", p.Length)
	v.relation(p.Length > p.Width, "L 须 > W (当前 L=%v, W=%v)", p.Length, p.Width)
	nonNegative(v, "CN", float32(p.ColumnCount))
	nonNegative(v, "RN", float32(p.RowCount))
	return v.err()
}

// RectangularFixedPlate(安装矩形开孔板): L>0, W>0, T>0, CS>0, RS>0, D>0, MH∈{0,1}
func (p *RectangularFixedPlateParams) Validate() error {
	v := &specValidator{}
	positive(v, "L", p.Length)
	positive(v, "W", p.Width)
	positive(v, "T", p.Thickness)
	positive(v, "CS", p.ColumnSpacing)
	positive(v, "RS", p.RowSpacing)
	positive(v, "D(孔径)", p.HoleDiameter)
	nonNegative(v, "CN", float32(p.ColumnCount))
	nonNegative(v, "RN", float32(p.RowCount))
	return v.err()
}

// CircularFixedPlate(安装圆形开孔板): L>0, W>0, T>0, CS>0, N>0, D>0
func (p *CircularFixedPlateParams) Validate() error {
	v := &specValidator{}
	positive(v, "L", p.Length)
	positive(v, "W", p.Width)
	positive(v, "T", p.Thickness)
	positive(v, "CS(开孔环半径)", p.RingRadius)
	positive(v, "N(开孔数)", float32(p.HoleCount))
	positive(v, "D(孔径)", p.HoleDiameter)
	return v.err()
}

// Wire(导线): Sag>0, D>0
func (p *WireParams) Validate() error {
	v := &specValidator{}
	positive(v, "Sag", p.Sag)
	positive(v, "D", p.Diameter)
	return v.err()
}

// Cable(电缆): D>0, 各虚交点转弯半径 IR>0, IRArray 与虚交点一一对应
func (p *CableParams) Validate() error {
	v := &specValidator{}
	positive(v, "D", p.Diameter)
	validateSliceLen(v, "路径点", append(p.InflectionPoints, p.StartPoint, p.EndPoint), 2)
	if len(p.InflectionPoints) > 0 {
		v.relation(len(p.Radii) == len(p.InflectionPoints), "IRArray 个数(%d) 须与虚交点个数(%d) 一一对应", len(p.Radii), len(p.InflectionPoints))
		for i, r := range p.Radii {
			v.relation(r > 0, "IRArray[%d] 必须 > 0 (当前 %v)", i, r)
		}
	}
	return v.err()
}

// ==================== 型钢构件（附录 B：所有型钢共用 Model+Length 语义） ====================

// AngleSteel: 各肢尺寸>0, 肢厚<min(L1,L2), L1≥L2（等边 L1=L2, 不等边长肢在前）
func (p *AngleSteelParams) Validate() error {
	v := &specValidator{}
	positive(v, "L1", p.L1)
	positive(v, "L2", p.L2)
	positive(v, "X(肢厚)", p.X)
	positive(v, "Length", p.Length)
	v.relation(float64(p.X) < math.Min(float64(p.L1), float64(p.L2)), "肢厚 X 须 < min(L1,L2) (当前 X=%v)", p.X)
	return v.err()
}

// normalizeSpecDefaults 不等边角钢长肢在前（L75X50X5 语义）
func (p *AngleSteelParams) normalizeSpecDefaults() {
	if p.L2 > p.L1 {
		p.L1, p.L2 = p.L2, p.L1
	}
}

// IShapedSteel / ILightbeams / H-beam: 各尺寸>0, 腹板厚/翼缘厚<截面高
func validateISection(v *specValidator, height, flangeWidth, web, flange float32) {
	positive(v, "H(截面高)", height)
	positive(v, "b(翼缘宽)", flangeWidth)
	positive(v, "tw(腹板厚)", web)
	positive(v, "tf(翼缘厚)", flange)
	v.relation(float64(web) < float64(height), "腹板厚 tw 须 < 截面高 H (当前 %v >= %v)", web, height)
	v.relation(float64(flange) < float64(height), "翼缘厚 tf 须 < 截面高 H (当前 %v >= %v)", flange, height)
}

func (p *IShapedSteelParams) Validate() error {
	v := &specValidator{}
	validateISection(v, p.Height, p.FlangeWidth, p.WebThickness, p.FlangeThickness)
	positive(v, "Length", p.Length)
	return v.err()
}

// ChannelSteel / LightBeamChannel(槽钢): 同工字钢
func (p *ChannelSteelParams) Validate() error {
	v := &specValidator{}
	validateISection(v, p.Height, p.FlangeWidth, p.WebThickness, p.FlangeThickness)
	positive(v, "Length", p.Length)
	return v.err()
}

// T-Steel(T型钢): 同工字钢
func (p *TSteelParams) Validate() error {
	v := &specValidator{}
	validateISection(v, p.Height, p.Width, p.WebThickness, p.FlangeThickness)
	positive(v, "Length", p.Length)
	return v.err()
}

// ==================== 架空输电线路（Q/GDW 11810.2 附录 A/E） ====================

// 挖孔桩/灌注桩单桩（表 E.1）: H1..H4>0, d>0, D≥d（无扩底时 D=d）
func (p *BoredPileParams) Validate() error {
	v := &specValidator{}
	positive(v, "H1", p.H1)
	positive(v, "H2", p.H2)
	positive(v, "H3", p.H3)
	positive(v, "H4", p.H4)
	positive(v, "d", p.Diameter)
	positive(v, "D", p.D)
	v.relation(p.D >= p.Diameter, "D 须 >= d (当前 D=%v < d=%v)", p.D, p.Diameter)
	return v.err()
}

// 承台挖孔桩/承台灌注桩（表 E.2）: 尺寸>0, cs∈{0,1}, ZCOUNT≥1, ZPOSTARRAY 与桩数一致
func (p *PileCapParams) Validate() error {
	v := &specValidator{}
	positive(v, "H1", p.H1)
	positive(v, "H2", p.H2)
	positive(v, "H3", p.H3)
	positive(v, "H4", p.H4)
	positive(v, "H5", p.H5)
	positive(v, "H6", p.H6)
	positive(v, "d", p.Diameter)
	positive(v, "D", p.D)
	positive(v, "b", p.B)
	positive(v, "B1", p.B1)
	positive(v, "L1", p.L1)
	nonNegative(v, "e1", p.E1)
	nonNegative(v, "e2", p.E2)
	enumIn(v, "cs", p.CS, 0, 1)
	v.relation(p.D >= p.Diameter, "D 须 >= d (当前 D=%v < d=%v)", p.D, p.Diameter)
	validateZPiles(v, p.ZCount, len(p.ZPosArray))
	return v.err()
}

func validateZPiles(v *specValidator, zcount int32, posLen int) {
	v.relation(zcount >= 1, "ZCOUNT 必须 >= 1 (当前 %d)", zcount)
	v.relation(posLen == int(zcount), "ZPOSTARRAY 个数(%d) 须与 ZCOUNT(%d) 一致", posLen, zcount)
}

// 直锚式岩石锚桩（表 E.3）
func (p *RockAnchorParams) Validate() error {
	v := &specValidator{}
	positive(v, "H1", p.H1)
	positive(v, "H2", p.H2)
	positive(v, "d", p.Diameter)
	positive(v, "B1", p.B1)
	positive(v, "L1", p.L1)
	validateZPiles(v, p.ZCount, len(p.ZPosArray))
	return v.err()
}

// 承台式岩石锚桩（表 E.4）
func (p *RockPileCapParams) Validate() error {
	v := &specValidator{}
	positive(v, "H1", p.H1)
	positive(v, "H2", p.H2)
	positive(v, "H3", p.H3)
	positive(v, "d", p.D)
	positive(v, "b", p.B)
	positive(v, "B1", p.B1)
	positive(v, "L1", p.L1)
	nonNegative(v, "e1", p.E1)
	nonNegative(v, "e2", p.E2)
	enumIn(v, "cs", p.CS, 0, 1)
	validateZPiles(v, p.ZCount, len(p.ZPosArray))
	return v.err()
}

// 嵌固式岩石锚桩（表 E.5）: D≥d
func (p *EmbeddedRockAnchorParams) Validate() error {
	v := &specValidator{}
	positive(v, "H1", p.H1)
	positive(v, "H2", p.H2)
	positive(v, "H3", p.H3)
	positive(v, "d", p.Diameter)
	positive(v, "D", p.D)
	v.relation(p.D >= p.Diameter, "D 须 >= d (当前 D=%v < d=%v)", p.D, p.Diameter)
	return v.err()
}

// 斜锚式岩石锚桩（表 E.6）
func (p *InclinedRockAnchorParams) Validate() error {
	v := &specValidator{}
	positive(v, "H1", p.H1)
	positive(v, "H2", p.H2)
	positive(v, "d", p.Diameter)
	positive(v, "D", p.D)
	positive(v, "B", p.B)
	positive(v, "L", p.L)
	nonNegative(v, "e1", p.E1)
	nonNegative(v, "e2", p.E2)
	nonNegative(v, "α1", p.Alpha1)
	nonNegative(v, "α2", p.Alpha2)
	return v.err()
}

// 掏挖基础（表 E.7）: D≥d, α1/α2 为 0 时为直柱
func (p *ExcavatedBaseParams) Validate() error {
	v := &specValidator{}
	positive(v, "H1", p.H1)
	positive(v, "H2", p.H2)
	positive(v, "H3", p.H3)
	positive(v, "d", p.Diameter)
	positive(v, "D", p.D)
	nonNegative(v, "α1", p.Alpha1)
	nonNegative(v, "α2", p.Alpha2)
	v.relation(p.D >= p.Diameter, "D 须 >= d (当前 D=%v < d=%v)", p.D, p.Diameter)
	return v.err()
}

// 台阶基础（表 E.8）: N≥1, 各阶 H/B/L>0
func (p *StepBaseParams) Validate() error {
	v := &specValidator{}
	positive(v, "H", p.H)
	positive(v, "H1", p.H1)
	positive(v, "H2", p.H2)
	positive(v, "b", p.B)
	positive(v, "B1", p.B1)
	positive(v, "B2", p.B2)
	positive(v, "L1", p.L1)
	positive(v, "L2", p.L2)
	nonNegative(v, "H3", p.H3)
	nonNegative(v, "B3", p.B3)
	nonNegative(v, "L3", p.L3)
	v.relation(p.N >= 1, "N(台阶数) 必须 >= 1 (当前 %d)", p.N)
	v.relation(p.N >= 3 || (p.H3 == 0 && p.B3 == 0 && p.L3 == 0), "第三阶参数仅在 N>=3 时参与, N<3 时须为 0")
	return v.err()
}

// 台阶底板基础（表 E.9）
func (p *StepPlateBaseParams) Validate() error {
	v := &specValidator{}
	positive(v, "H", p.H)
	positive(v, "H1", p.H1)
	positive(v, "H2", p.H2)
	positive(v, "b", p.B)
	positive(v, "B1", p.B1)
	positive(v, "B2", p.B2)
	positive(v, "L1", p.L1)
	positive(v, "L2", p.L2)
	nonNegative(v, "H3", p.H3)
	nonNegative(v, "α1", p.Alpha1)
	nonNegative(v, "α2", p.Alpha2)
	v.relation(p.N >= 1, "N(台阶数) 必须 >= 1 (当前 %d)", p.N)
	return v.err()
}

// 斜坡底板基础（表 E.10）
func (p *SlopedBaseBaseParams) Validate() error {
	v := &specValidator{}
	positive(v, "H1", p.H1)
	positive(v, "H2", p.H2)
	positive(v, "H3", p.H3)
	positive(v, "b", p.B)
	positive(v, "B1", p.B1)
	positive(v, "B2", p.B2)
	positive(v, "L1", p.L1)
	positive(v, "L2", p.L2)
	nonNegative(v, "α1", p.Alpha1)
	nonNegative(v, "α2", p.Alpha2)
	return v.err()
}

// 复合式沉井基础（表 E.11）
func (p *CompositeCaissonBaseParams) Validate() error {
	v := &specValidator{}
	positive(v, "H1", p.H1)
	positive(v, "H2", p.H2)
	positive(v, "H3", p.H3)
	positive(v, "H4", p.H4)
	positive(v, "b", p.B)
	positive(v, "D", p.D)
	positive(v, "t", p.T)
	positive(v, "B1", p.B1)
	positive(v, "B2", p.B2)
	positive(v, "L1", p.L1)
	positive(v, "L2", p.L2)
	return v.err()
}

// 筏板基础（表 E.12）: H3=0 为无主梁筏板
func (p *RaftBaseParams) Validate() error {
	v := &specValidator{}
	positive(v, "H1", p.H1)
	positive(v, "H2", p.H2)
	nonNegative(v, "H3", p.H3)
	positive(v, "b1", p.Beam1)
	positive(v, "b2", p.Beam2)
	positive(v, "B1", p.B1)
	positive(v, "B2", p.B2)
	positive(v, "L1", p.L1)
	positive(v, "L2", p.L2)
	return v.err()
}

// 直埋式基础（表 E.13）: D≥d, t>0
func (p *DirectBuriedBaseParams) Validate() error {
	v := &specValidator{}
	positive(v, "H1", p.H1)
	positive(v, "d", p.Diameter)
	positive(v, "t", p.T)
	nonNegative(v, "H2(固定盘高)", p.H2)
	nonNegative(v, "D(圆形盘直径)", p.D)
	nonNegative(v, "B(方形盘长)", p.B)
	return v.err()
}

// 钢套筒式基础（表 E.14）: 无卡盘时 D1/D2、B1/B2 可为 0
func (p *SteelSleeveBaseParams) Validate() error {
	v := &specValidator{}
	positive(v, "H1", p.H1)
	positive(v, "d", p.D)
	positive(v, "t", p.T)
	nonNegative(v, "H2", p.H2)
	nonNegative(v, "H3", p.H3)
	nonNegative(v, "H4", p.H4)
	nonNegative(v, "D1", p.D1)
	nonNegative(v, "D2", p.D2)
	nonNegative(v, "B1", p.B1)
	nonNegative(v, "B2", p.B2)
	v.relation(p.D1 > 0 || p.D2 == 0, "圆卡盘需同时给定 D1、D2")
	v.relation(p.B1 > 0 || p.B2 == 0, "方卡盘需同时给定 B1、B2")
	return v.err()
}

// 装配式直柱固接型基础（表 E.15）
func (p *PrecastColumnBaseParams) Validate() error {
	v := &specValidator{}
	positive(v, "H1", p.H1)
	positive(v, "H2", p.H2)
	positive(v, "H3", p.H3)
	positive(v, "d", p.D)
	positive(v, "B1", p.B1)
	positive(v, "B2", p.B2)
	positive(v, "L1", p.L1)
	positive(v, "L2", p.L2)
	return v.err()
}

// 装配式直柱铰接型基础（表 E.16）: 卡盘 L/H/B 可全 0
func (p *PrecastPinnedBaseParams) Validate() error {
	v := &specValidator{}
	positive(v, "H1", p.H1)
	positive(v, "H2", p.H2)
	positive(v, "H3", p.H3)
	positive(v, "d", p.D)
	positive(v, "B1", p.B1)
	positive(v, "B2", p.B2)
	positive(v, "L1", p.L1)
	positive(v, "L2", p.L2)
	hasChamfer := p.B > 0 || p.H > 0 || p.L > 0
	if hasChamfer {
		positive(v, "B(卡盘宽)", p.B)
		positive(v, "H(卡盘高)", p.H)
		positive(v, "L(卡盘长)", p.L)
	}
	return v.err()
}

// 装配式金属支架型基础（表 E.17）: N1 斜材组数≥0, N2 板条数量>0
func (p *PrecastMetalSupportBaseParams) Validate() error {
	v := &specValidator{}
	positive(v, "H1", p.H1)
	positive(v, "H2", p.H2)
	positive(v, "H3", p.H3)
	positive(v, "H4", p.H4)
	positive(v, "b1", p.Beam1)
	positive(v, "b2", p.Beam2)
	positive(v, "B1", p.B1)
	positive(v, "B2", p.B2)
	positive(v, "L1", p.L1)
	positive(v, "L2", p.L2)
	positive(v, "S1", p.S1)
	positive(v, "S2", p.S2)
	nonNegative(v, "N1(斜材组数)", float32(p.N1))
	positive(v, "N2(板条数量)", float32(p.N2))
	for i, hx := range p.HX {
		nonNegative(v, fmt.Sprintf("HX[%d](斜材层高)", i), hx)
	}
	return v.err()
}

// 装配式混凝土构件支架型基础（表 E.18）
func (p *PrecastConcreteSupportBaseParams) Validate() error {
	v := &specValidator{}
	positive(v, "H1", p.H1)
	positive(v, "H2", p.H2)
	positive(v, "H3", p.H3)
	positive(v, "H4", p.H4)
	positive(v, "H5", p.H5)
	positive(v, "b1", p.Beam1)
	positive(v, "b2", p.Beam2)
	positive(v, "b3", p.Beam3)
	positive(v, "B1", p.B1)
	positive(v, "B2", p.B2)
	positive(v, "L1", p.L1)
	positive(v, "L2", p.L2)
	positive(v, "S1", p.S1)
	positive(v, "N1", float32(p.N1))
	return v.err()
}

// 导地线（表 1）: 截面积/外径>0, 其余非负
func (p *TransmissionLineParams) Validate() error {
	v := &specValidator{}
	positive(v, "SECTIONALAREA", p.SectionalArea)
	positive(v, "OUTSIDEDIAMETER", p.OutsideDiameter)
	nonNegative(v, "WIREWEIGHT", p.WireWeight)
	nonNegative(v, "COEFFICIENTOFELASTICITY", p.CoefficientOfElasticity)
	nonNegative(v, "EXPANSIONCOEFFICIENTOFWIRE", p.ExpansionCoefficient)
	nonNegative(v, "RATEDSTRENGTH", p.RatedStrength)
	return v.err()
}

// 绝缘子串（表 2, 复合绝缘子分支走 RadiusData 动态结构, 此处校验公共项）
func (p *InsulatorCompositeParams) Validate() error {
	v := &specValidator{}
	positive(v, "SUBNUM(导线分裂数)", float32(p.SubNum))
	nonNegative(v, "SUBDISTANCE(分裂间距)", p.SplitDistance)
	nonNegative(v, "ANGLEL", p.VAngleLeft)
	nonNegative(v, "ANGLEL(右)", p.VAngleRight)
	nonNegative(v, "HORIZONTALLENGTH", p.ULinkLength)
	nonNegative(v, "WEIGHT", p.Weight)
	if p.Insulator.Height > 0 {
		positive(v, "INSULATORHIGH(结构高度)", p.Insulator.Height)
		v.relation(p.Insulator.LeftCount > 0 || p.Insulator.RightCount > 0, "INSULATORCOUNT 左/右片数至少一项 > 0")
	}
	if p.MultiLink.Count > 0 {
		v.relation(p.MultiLink.Count > 0, "LINECOUNT(联数) 必须 > 0 (当前 %d)", p.MultiLink.Count)
	}
	if p.GradingRing.Count > 0 {
		v.relation(p.GradingRing.Count >= 0, "GRADINGRINGCOUNT(均压环个数) 必须 >= 0")
	}
	return v.err()
}

// 杆塔（附录 A: P/R/G 结构完整, 成员端点非空）
func (p *PoleTowerParams) Validate() error {
	v := &specValidator{}
	validateSliceLen(v, "Heights(呼高)", p.Heights, 1)
	validateSliceLen(v, "Bodies(本体)", p.Bodies, 1)
	validateSliceLen(v, "Members(杆件)", p.Members, 1)
	for i, h := range p.Heights {
		v.relation(h.Value > 0, "Heights[%d].Value(呼高) 必须 > 0 (当前 %v)", i, h.Value)
		v.relation(h.BodyID != "", "Heights[%d].BodyID 不能为空", i)
	}
	for i, b := range p.Bodies {
		v.relation(b.ID != "", "Bodies[%d].ID 不能为空", i)
		validateSliceLen(v, fmt.Sprintf("Bodies[%d].Nodes", i), b.Nodes, 1)
		for j, leg := range b.Legs {
			v.relation(leg.ID != "", "Bodies[%d].Legs[%d].ID 不能为空", i, j)
			validateSliceLen(v, fmt.Sprintf("Bodies[%d].Legs[%d].Nodes", i, j), leg.Nodes, 1)
		}
	}
	for i, m := range p.Members {
		v.relation(m.StartNodeID != "" && m.EndNodeID != "", "Members[%d] 起止节点号不能为空", i)
	}
	return v.err()
}

// 地脚螺栓类锚具（表 8/附录 A 防御性正值）
func validateAnchorCommon(v *specValidator, boltDia, exposed, nutHeight, nutOD float32, nutCount int32, anchorLength float32) {
	positive(v, "BoltDiameter", boltDia)
	positive(v, "ExposedLength", exposed)
	v.relation(nutCount >= 0, "NutCount 必须 >= 0 (当前 %d)", nutCount)
	if nutCount > 0 {
		positive(v, "NutHeight", nutHeight)
		positive(v, "NutOD", nutOD)
	}
	positive(v, "AnchorLength", anchorLength)
}

func (p *SingleHookAnchorParams) Validate() error {
	v := &specValidator{}
	validateAnchorCommon(v, p.BoltDiameter, p.ExposedLength, p.NutHeight, p.NutOD, p.NutCount, p.AnchorLength)
	positive(v, "HookStraightLength", p.HookStraightLength)
	positive(v, "HookDiameter", p.HookDiameter)
	return v.err()
}

func (p *TripleHookAnchorParams) Validate() error {
	v := &specValidator{}
	validateAnchorCommon(v, p.BoltDiameter, p.ExposedLength, p.NutHeight, p.NutOD, p.NutCount, p.AnchorLength)
	positive(v, "HookStraightLengthA", p.HookStraightLengthA)
	positive(v, "HookStraightLengthB", p.HookStraightLengthB)
	positive(v, "HookDiameter", p.HookDiameter)
	positive(v, "AnchorBarDiameter", p.AnchorBarDiameter)
	return v.err()
}

func (p *RibbedAnchorParams) Validate() error {
	v := &specValidator{}
	validateAnchorCommon(v, p.BoltDiameter, p.ExposedLength, p.NutHeight, p.NutOD, p.NutCount, p.AnchorLength)
	positive(v, "BasePlateSize", p.BasePlateSize)
	positive(v, "BasePlateThickness", p.BasePlateThickness)
	positive(v, "RibTopWidth", p.RibTopWidth)
	positive(v, "RibHeight", p.RibHeight)
	positive(v, "RibThickness", p.RibThickness)
	return v.err()
}

func (p *NutAnchorParams) Validate() error {
	v := &specValidator{}
	validateAnchorCommon(v, p.BoltDiameter, p.ExposedLength, p.NutHeight, p.NutOD, p.NutCount, p.AnchorLength)
	positive(v, "BasePlateSize", p.BasePlateSize)
	positive(v, "BasePlateThickness", p.BasePlateThickness)
	return v.err()
}

func (p *TripleArmAnchorParams) Validate() error {
	v := &specValidator{}
	validateAnchorCommon(v, p.BoltDiameter, p.ExposedLength, p.NutHeight, p.NutOD, p.NutCount, p.AnchorLength)
	positive(v, "ArmDiameter", p.ArmDiameter)
	positive(v, "ArmStraightLength", p.ArmStraightLength)
	inRange(v, "ArmBendAngle(弧度)", p.ArmBendAngle, 0, float32(twoPiF))
	return v.err()
}

func (p *PositioningPlateAnchorParams) Validate() error {
	v := &specValidator{}
	validateAnchorCommon(v, p.BoltDiameter, p.ExposedLength, p.NutHeight, p.NutOD, p.NutCount, p.AnchorLength)
	positive(v, "PlateLength", p.PlateLength)
	positive(v, "PlateThickness", p.PlateThickness)
	nonNegative(v, "ToBaseDistance", p.ToBaseDistance)
	nonNegative(v, "ToBottomDistance", p.ToBottomDistance)
	return v.err()
}

// 塔脚插入角钢/插入管
func (p *StubAngleParams) Validate() error {
	v := &specValidator{}
	positive(v, "LegWidth", p.LegWidth)
	positive(v, "Thickness", p.Thickness)
	positive(v, "ExposedLength", p.ExposedLength)
	positive(v, "AnchorLength", p.AnchorLength)
	nonNegative(v, "Slope", p.Slope)
	v.relation(float64(p.Thickness) < float64(p.LegWidth), "Thickness 须 < LegWidth (当前 %v >= %v)", p.Thickness, p.LegWidth)
	return v.err()
}

func (p *StubTubeParams) Validate() error {
	v := &specValidator{}
	positive(v, "Diameter", p.Diameter)
	positive(v, "ExposedLength", p.ExposedLength)
	positive(v, "AnchorLength", p.AnchorLength)
	nonNegative(v, "Slope", p.Slope)
	v.relation(float64(p.Thickness) > 0 && float64(p.Thickness) < float64(p.Diameter), "Thickness 须在 (0, Diameter) 内 (当前 %v, D=%v)", p.Thickness, p.Diameter)
	return v.err()
}

// ==================== 电缆线路（T/CEC 5056.3 附录 A/B） ====================

// 电(光)缆: 外径>0, 路径≥2 点
func (p *CableWireParams) Validate() error {
	v := &specValidator{}
	positive(v, "OUTSIDEDIAMETER", p.OutsideDiameter)
	validateSliceLen(v, "Points(路径)", p.Points, 2)
	return v.err()
}

// 中间接头（表 A.1.2.1）: L/D/L1/d>0, 外径>内径
func (p *CableJointParams) Validate() error {
	v := &specValidator{}
	positive(v, "L(总长)", p.Length)
	positive(v, "D(外径)", p.OuterDiameter)
	positive(v, "L1(端子长)", p.TerminalLength)
	positive(v, "d(内径)", p.InnerDiameter)
	v.relation(p.OuterDiameter > p.InnerDiameter, "D(外径) 须 > d(内径) (当前 %v <= %v)", p.OuterDiameter, p.InnerDiameter)
	return v.err()
}

// 光缆接头盒（表 A.1.3.1）
func (p *OpticalFiberBoxParams) Validate() error {
	v := &specValidator{}
	positive(v, "L", p.Length)
	positive(v, "H", p.Height)
	positive(v, "W", p.Width)
	return v.err()
}

// 电缆终端（表 A.1.4.1）: 主体与尾管>0, 伞裙尺寸关系
func (p *CableTerminalParams) Validate() error {
	v := &specValidator{}
	positive(v, "H(长度)", p.Height)
	positive(v, "D1(上部直径)", p.TopDiameter)
	positive(v, "D2(下部直径)", p.BottomDiameter)
	nonNegative(v, "D3(尾管直径)", p.TailDiameter)
	v.relation(p.TailDiameter > 0 || p.TailHeight == 0, "尾管直径与高度须同时给定")
	v.relation(p.SkirtCount >= 0, "套管伞裙片数须 >= 0 (当前 %d)", p.SkirtCount)
	if p.SkirtCount > 0 {
		positive(v, "伞裙单元高度", p.SkirtSectionHeight)
		v.relation(p.UpperSkirtTopDiameter > 0 && p.UpperSkirtBottomDiameter > 0, "上伞裙直径须 > 0")
		v.relation(p.LowerSkirtTopDiameter > 0 && p.LowerSkirtBottomDiameter > 0, "下伞裙直径须 > 0")
	}
	nonNegative(v, "ZD1(上端子直径)", p.UpperTerminalDiameter)
	nonNegative(v, "L2(下端子长度)", p.LowerTerminalLength)
	nonNegative(v, "ZD2(下端子直径)", p.LowerTerminalDiameter)
	nonNegative(v, "Φ1", p.Hole1Diameter)
	nonNegative(v, "Φ2", p.Hole2Diameter)
	nonNegative(v, "d1", p.Hole1Distance)
	nonNegative(v, "d2", p.HoleSpacing)
	return v.err()
}

// 接地箱/护层保护箱/交叉互联箱（表 A.1.5.1）: 进出口数须为 3 或 6
func (p *CableAccessoryParams) Validate() error {
	v := &specValidator{}
	positive(v, "L", p.Length)
	positive(v, "W", p.Width)
	positive(v, "H", p.Height)
	positive(v, "d(进出口直径)", p.PortDiameter)
	v.relation(p.PortCount == 3 || p.PortCount == 6, "进出口数目须为 3 或 6 (当前 %d)", p.PortCount)
	nonNegative(v, "T1(距前面板)", p.SidePanelDistance)
	nonNegative(v, "T2(距后面板)", p.BackPanelDistance)
	return v.err()
}

// 电缆支架（表 A.2.4）
func (p *CableBracketParams) Validate() error {
	v := &specValidator{}
	positive(v, "L(支架长)", p.Length)
	positive(v, "H(根部高)", p.RootHeight)
	positive(v, "B(根部宽)", p.RootWidth)
	positive(v, "C(支架宽)", p.Width)
	positive(v, "t(端部厚)", p.TopThickness)
	positive(v, "T(根部厚)", p.RootThickness)
	return v.err()
}

// 电缆夹具（表 A.2.2）: D/t/B>0
func (p *CableClampParams) Validate() error {
	v := &specValidator{}
	positive(v, "D(直径)", p.Diameter)
	positive(v, "t(厚度)", p.Thickness)
	positive(v, "B(宽度)", p.Width)
	return v.err()
}

// 电缆立柱（表 A.2.6）: R=0 为直柱, R>0 需弧度 A
func (p *CablePoleParams) Validate() error {
	v := &specValidator{}
	positive(v, "L(立柱长)", p.Length)
	positive(v, "B(立柱宽)", p.Width)
	positive(v, "C(固定肢长)", p.FixedLegLength)
	positive(v, "S(固定肢宽)", p.FixedLegWidth)
	positive(v, "t(厚度)", p.Thickness)
	nonNegative(v, "R(半径)", p.Radius)
	nonNegative(v, "A(弧度)", p.ArcAngle)
	v.relation(p.Radius <= 0 || p.ArcAngle > 0, "弧形立柱需给定弧度 A")
	return v.err()
}

// 接地扁铁（表 A.1.7）
func (p *GroundFlatIronParams) Validate() error {
	v := &specValidator{}
	positive(v, "L", p.Length)
	positive(v, "H", p.Height)
	positive(v, "T", p.Thickness)
	return v.err()
}

// 预埋件（表 A.1.8）
func (p *EmbeddedPartParams) Validate() error {
	v := &specValidator{}
	positive(v, "L", p.Length)
	positive(v, "R", p.Radius)
	positive(v, "H", p.Height)
	positive(v, "R1(材料直径)", p.MaterialRadius)
	positive(v, "L1(下部长度)", p.LowerLength)
	return v.err()
}

// U 型拉环（表 A.1.9）
func (p *UShapedRingParams) Validate() error {
	v := &specValidator{}
	positive(v, "T(材料厚度)", p.Thickness)
	positive(v, "H(开口高度)", p.Height)
	positive(v, "R(拉环半径)", p.Radius)
	positive(v, "L(拉环长度)", p.Length)
	v.relation(float64(p.Radius) > float64(p.Thickness), "R 须 > T (当前 %v <= %v)", p.Radius, p.Thickness)
	return v.err()
}

// 吊攀（表 A.1.10）
func (p *LiftingEyeParams) Validate() error {
	v := &specValidator{}
	positive(v, "H(吊臂高度)", p.Height)
	positive(v, "R(圆环半径)", p.RingRadius)
	positive(v, "I(钢管直径)", p.PipeDiameter)
	return v.err()
}

// 转角井（表 A.3.3）
func (p *CornerWellParams) Validate() error {
	v := &specValidator{}
	positive(v, "L1(左段净长)", p.LeftLength)
	positive(v, "L2(右段净长)", p.RightLength)
	positive(v, "W(净宽)", p.Width)
	positive(v, "H(净高)", p.Height)
	positive(v, "H1(顶板厚)", p.TopThickness)
	positive(v, "H2(底板厚)", p.BottomThickness)
	positive(v, "T1(壁厚)", p.WallThickness)
	positive(v, "A(转角角度)", p.Angle)
	positive(v, "R(转角段半径)", p.CornerRadius)
	nonNegative(v, "T3(垫层溢出)", p.CushionExtension)
	nonNegative(v, "HB(垫层厚)", p.CushionThickness)
	return v.err()
}

// 直线井（表 A.3.1）: 连接段截面形式 PL/PR∈{1,2,3}
func validateWellSection(v *specValidator, prefix string, style int, length, width, height, arc float64) {
	if length == 0 && width == 0 && height == 0 {
		return // 未定义连接段
	}
	enumIn(v, prefix+"截面形式", int32(style), 1, 2, 3)
	positive(v, prefix+"长", length)
	positive(v, prefix+"宽", width)
	positive(v, prefix+"高", height)
	nonNegative(v, prefix+"拱高", arc)
}

func (p *TunnelWellParams) Validate() error {
	v := &specValidator{}
	positive(v, "L(井净长)", p.Length)
	positive(v, "W(井净宽)", p.Width)
	positive(v, "H(井净高)", p.Height)
	nonNegative(v, "R(井内径)", p.Radius)
	positive(v, "H1(顶板厚)", p.TopThickness)
	positive(v, "H2(底板厚)", p.BottomThickness)
	positive(v, "T1(外壁厚)", p.OuterWallThickness)
	nonNegative(v, "T2(内壁厚)", p.InnerWallThickness)
	nonNegative(v, "T3(垫层溢出)", p.CushionExtension)
	nonNegative(v, "H3(垫层厚)", p.CushionThickness)
	validateWellSection(v, "PL 左连接段", p.LeftSectionType, p.LeftLength, p.LeftWidth, p.LeftHeight, p.LeftArcHeight)
	validateWellSection(v, "PR 右连接段", p.RightSectionType, p.RightLength, p.RightWidth, p.RightHeight, p.RightArcHeight)
	return v.err()
}

// 三通井（表 A.3.5）
func validateWellSectionF32(v *specValidator, prefix string, style int32, length, width, height, arc float32) {
	validateWellSection(v, prefix, int(style), float64(length), float64(width), float64(height), float64(arc))
}

func (p *ThreeWayWellParams) Validate() error {
	v := &specValidator{}
	positive(v, "L(井净长)", p.Length)
	positive(v, "W(井净宽)", p.Width)
	positive(v, "H(井净高)", p.Height)
	positive(v, "H1(顶板厚)", p.TopThickness)
	positive(v, "H2(底板厚)", p.BottomThickness)
	positive(v, "T1(外壁厚)", p.OuterWallThickness)
	enumIn(v, "P1(转角样式)", int32(p.CornerType), 1, 2)
	enumIn(v, "P2(竖井样式)", int32(p.ShaftType), 1, 2)
	validateWellSectionF32(v, "PL 左连接段", int32(p.LeftSectionStyle), p.LeftSectionLength, p.LeftSectionWidth, p.LeftSectionHeight, p.LeftSectionArcHeight)
	validateWellSectionF32(v, "PR 右连接段", int32(p.RightSectionStyle), p.RightSectionLength, p.RightSectionWidth, p.RightSectionHeight, p.RightSectionArcHeight)
	validateWellSectionF32(v, "PZ 支线连接段", int32(p.BranchSectionStyle), p.BranchSectionLength, p.BranchSectionWidth, p.BranchSectionHeight, p.BranchSectionArcHeight)
	return v.err()
}

// 四通井（表 A.3.7）
func (p *FourWayWellParams) Validate() error {
	v := &specValidator{}
	positive(v, "L(井净长)", p.Length)
	positive(v, "W(井净宽)", p.Width)
	positive(v, "H(井净高)", p.Height)
	positive(v, "H1(顶板厚)", p.TopThickness)
	positive(v, "H2(底板厚)", p.BottomThickness)
	positive(v, "T1(外壁厚)", p.OuterWallThickness)
	enumIn(v, "P1(转角样式)", int32(p.CornerStyle), 1, 2)
	validateWellSectionF32(v, "PL 左连接段", int32(p.LeftSection.SectionType), p.LeftSection.Length, p.LeftSection.Width, p.LeftSection.Height, p.LeftSection.ArcHeight)
	validateWellSectionF32(v, "PR 右连接段", int32(p.RightSection.SectionType), p.RightSection.Length, p.RightSection.Width, p.RightSection.Height, p.RightSection.ArcHeight)
	validateWellSectionF32(v, "PZ2 支线段1", int32(p.BranchSection1.SectionType), p.BranchSection1.Length, p.BranchSection1.Width, p.BranchSection1.Height, p.BranchSection1.ArcHeight)
	validateWellSectionF32(v, "PZ3 支线段2", int32(p.BranchSection2.SectionType), p.BranchSection2.Length, p.BranchSection2.Width, p.BranchSection2.Height, p.BranchSection2.ArcHeight)
	return v.err()
}

// 排管（表 A.3.9）: POS/D1/T1 数组一一对应
func (p *PipeRowParams) Validate() error {
	v := &specValidator{}
	n := len(p.PipePositions)
	v.relation(n >= 1, "排管数量须 >= 1")
	v.relation(len(p.PipeInnerDiameters) == n, "D1 数组长度(%d) 须与 POS(%d) 一一对应", len(p.PipeInnerDiameters), n)
	v.relation(len(p.PipeWallThicknesses) == n, "T1 数组长度(%d) 须与 POS(%d) 一一对应", len(p.PipeWallThicknesses), n)
	for i, d := range p.PipeInnerDiameters {
		positive(v, fmt.Sprintf("D1[%d]", i), d)
	}
	for i, t := range p.PipeWallThicknesses {
		positive(v, fmt.Sprintf("T1[%d]", i), t)
	}
	if p.PullPipeInnerDiameter > 0 {
		positive(v, "T(拉管壁厚)", p.PullPipeThickness)
	}
	validateSliceLen(v, "路径 Points", p.Points, 2)
	if p.HasEnclosure {
		positive(v, "W(包封宽)", p.EnclosureWidth)
		positive(v, "H(包封高)", p.EnclosureHeight)
	}
	nonNegative(v, "W1(底板溢出)", p.BaseExtension)
	nonNegative(v, "H1(底板厚)", p.BaseThickness)
	nonNegative(v, "W2(垫层溢出)", p.CushionExtension)
	nonNegative(v, "H2(垫层厚)", p.CushionThickness)
	return v.err()
}

// 电缆沟（表 A.3.11）
func (p *CableTrenchParams) Validate() error {
	v := &specValidator{}
	positive(v, "W(沟内净宽)", p.Width)
	positive(v, "H(沟内净高)", p.Height)
	positive(v, "W1(盖板宽)", p.CoverWidth)
	positive(v, "H1(盖板厚)", p.CoverThickness)
	positive(v, "T(壁厚)", p.WallThickness)
	nonNegative(v, "T1(壁厚2)", p.WallThickness2)
	nonNegative(v, "W2(底板溢出)", p.BaseExtension)
	nonNegative(v, "H2(底板厚)", p.BaseThickness)
	nonNegative(v, "W3(垫层溢出)", p.CushionExtension)
	nonNegative(v, "HB(垫层厚)", p.CushionThickness)
	validateSliceLen(v, "路径 Points", p.Points, 2)
	return v.err()
}

// 电缆隧道（表 A.3.13）: 样式 P∈{1,2,3}
func (p *CableTunnelParams) Validate() error {
	v := &specValidator{}
	enumIn(v, "P(样式)", p.Style, 1, 2, 3)
	positive(v, "W(内净宽)", p.Width)
	positive(v, "H(内净高)", p.Height)
	nonNegative(v, "H1(顶板厚)", p.TopThickness)
	nonNegative(v, "H2(底板厚)", p.BottomThickness)
	positive(v, "T(壁厚)", p.OuterWallThickness)
	nonNegative(v, "T1(内壁厚)", p.InnerWallThickness)
	nonNegative(v, "H4(拱高)", p.ArcHeight)
	nonNegative(v, "H5(平台下底面高)", p.BottomPlatformHeight)
	nonNegative(v, "W2(垫层溢出)", p.CushionExtension)
	nonNegative(v, "HB(垫层厚)", p.CushionThickness)
	validateSliceLen(v, "路径 Points", p.Points, 2)
	return v.err()
}

// 电缆桥架（表 A.3.15）: 样式 P∈{1,2}
func (p *CableTrayParams) Validate() error {
	v := &specValidator{}
	enumIn(v, "P(样式)", p.Style, 1, 2)
	positive(v, "DZ(桥柱直径)", p.ColumnDiameter)
	positive(v, "HZ(桥柱高)", p.ColumnHeight)
	positive(v, "L(跨距)", p.Span)
	positive(v, "W", p.Width)
	positive(v, "H", p.Height)
	positive(v, "H1(顶板高)", p.TopPlateHeight)
	positive(v, "TQ(壁厚)", p.WallThickness)
	n := len(p.PipePositions)
	if n > 0 {
		v.relation(len(p.PipeInnerDiameters) == n, "D1 数组长度须与 POS 一一对应")
		v.relation(len(p.PipeWallThicknesses) == n, "T1 数组长度须与 POS 一一对应")
	}
	validateSliceLen(v, "路径 Points", p.Points, 2)
	return v.err()
}

// 梁（表 A.3.18）
func (p *CableLBeamParams) Validate() error {
	v := &specValidator{}
	positive(v, "L", p.Length)
	positive(v, "W", p.Width)
	positive(v, "H", p.Height)
	return v.err()
}

// 人孔（表 A.3.20）: 样式 P∈{1,2}
func (p *ManholeParams) Validate() error {
	v := &specValidator{}
	enumIn(v, "P(样式)", p.Style, 1, 2)
	positive(v, "L", p.Length)
	positive(v, "H", p.Height)
	positive(v, "T(壁厚)", p.WallThickness)
	if p.Style == 2 {
		positive(v, "W(方形人孔宽)", p.Width)
	} else {
		nonNegative(v, "W", p.Width)
	}
	return v.err()
}

// 井盖（表 A.3.22）: 圆形时 W=0
func (p *ManholeCoverParams) Validate() error {
	v := &specValidator{}
	enumIn(v, "P(样式)", p.Style, 1, 2)
	positive(v, "L", p.Length)
	positive(v, "H(厚)", p.Thickness)
	v.relation(p.Width >= 0, "W 必须 >= 0 (当前 %v)", p.Width)
	if p.Style == 2 {
		positive(v, "W(方形井盖宽)", p.Width)
	}
	return v.err()
}

// 爬梯（表 A.3.24）
func (p *LadderParams) Validate() error {
	v := &specValidator{}
	positive(v, "L", p.Length)
	positive(v, "W", p.Width)
	positive(v, "T", p.Thickness)
	return v.err()
}

// 集水坑（表 A.3.26）
func (p *SumpParams) Validate() error {
	v := &specValidator{}
	positive(v, "L", p.Length)
	positive(v, "W", p.Width)
	positive(v, "H(深)", p.Depth)
	positive(v, "T(底板厚)", p.BottomThickness)
	return v.err()
}

// 步道
func (p *FootpathParams) Validate() error {
	v := &specValidator{}
	positive(v, "H", p.Height)
	positive(v, "W", p.Width)
	validateSliceLen(v, "路径 Points", p.Points, 2)
	return v.err()
}

// 竖井仓（表 A.3.28）
func (p *ShaftChamberParams) Validate() error {
	v := &specValidator{}
	positive(v, "T1(支护壁厚)", p.SupportWallThickness)
	positive(v, "D1(支护直径)", p.SupportDiameter)
	positive(v, "H1(支护高)", p.SupportHeight)
	positive(v, "T2(顶板厚)", p.TopThickness)
	positive(v, "D(内壁直径)", p.InnerDiameter)
	positive(v, "H(工作仓高)", p.WorkingHeight)
	positive(v, "T3(外壁厚)", p.OuterWallThickness)
	positive(v, "T4(内壁厚)", p.InnerWallThickness)
	return v.err()
}

// 隧道分仓隔板（表 A.3.30）
func (p *TunnelCompartmentPartitionParams) Validate() error {
	v := &specValidator{}
	positive(v, "W", p.Width)
	positive(v, "T", p.Thickness)
	return v.err()
}

// 暗挖隧道井隔板（表 A.3.31）: 孔数组与 NUM 一一对应
func (p *TunnelPartitionBoardParams) Validate() error {
	v := &specValidator{}
	positive(v, "L", p.Length)
	positive(v, "T", p.Thickness)
	if p.Style == TunnelPartitionBoardStyleRectangular {
		positive(v, "W(方形隔板宽)", p.Width)
	} else {
		nonNegative(v, "W", p.Width)
	}
	n := int(p.HoleCount)
	if n > 0 {
		v.relation(len(p.HolePositions) == n, "POS 数组长度(%d) 须与 NUM(%d) 一致", len(p.HolePositions), n)
		v.relation(len(p.HoleStyles) == n, "P1 数组长度(%d) 须与 NUM(%d) 一致", len(p.HoleStyles), n)
		for i := range p.HoleStyles {
			if len(p.HoleDiameters) == n {
				positive(v, fmt.Sprintf("L%d(开孔直径)", i+1), p.HoleDiameters[i])
			}
		}
		v.relation(len(p.HoleDiameters) == n || len(p.HoleWidths) == n, "开孔直径/宽度数组须与 NUM 一致")
	}
	return v.err()
}

// 斜通风道（表 A.3.34）
func (p *ObliqueVentilationDuctParams) Validate() error {
	v := &specValidator{}
	positive(v, "L1(风帽室长)", p.HoodRoomLength)
	positive(v, "W1(风帽室宽)", p.HoodRoomWidth)
	positive(v, "H1(风帽室高)", p.HoodRoomHeight)
	positive(v, "T(风帽壁厚)", p.HoodWallThickness)
	positive(v, "D1(风通道直径)", p.DuctDiameter)
	positive(v, "T1(风通道壁厚)", p.DuctWallThickness)
	positive(v, "L4(风通道长)", p.DuctLength)
	positive(v, "L2(基座长)", p.BaseLength)
	positive(v, "W2(基座宽)", p.BaseWidth)
	positive(v, "H4(基座高)", p.BaseHeight)
	positive(v, "L3(基室长)", p.BaseRoomLength)
	positive(v, "W3(基室宽)", p.BaseRoomWidth)
	positive(v, "HB(基室高)", p.BaseRoomHeight)
	positive(v, "T2(基室壁厚)", p.BaseRoomWallThickness)
	nonNegative(v, "H5(圆心高)", p.DuctCenterHeight)
	nonNegative(v, "L5(圆心距左)", p.DuctLeftDistance)
	nonNegative(v, "H2(高差)", p.DuctHeightDifference)
	return v.err()
}

// 风亭（表 A.3.32）
func (p *VentilationPavilionParams) Validate() error {
	v := &specValidator{}
	positive(v, "L1(顶长)", p.TopLength)
	positive(v, "L2(长)", p.MiddleLength)
	positive(v, "L3(底长)", p.BottomLength)
	positive(v, "W1(顶宽)", p.TopWidth)
	positive(v, "W2(宽)", p.MiddleWidth)
	positive(v, "W3(底宽)", p.BottomWidth)
	positive(v, "H1(顶高)", p.TopHeight)
	positive(v, "H2(高)", p.Height)
	positive(v, "H3(底高)", p.BaseHeight)
	return v.err()
}

// 直通风道（表 A.3.33）: 0<T<D
func (p *StraightVentilationDuctParams) Validate() error {
	v := &specValidator{}
	positive(v, "D(直径)", p.Diameter)
	positive(v, "H", p.Height)
	v.relation(float64(p.WallThickness) > 0 && float64(p.WallThickness) < float64(p.Diameter), "T 须在 (0, D) 内 (当前 T=%v, D=%v)", p.WallThickness, p.Diameter)
	return v.err()
}

// 排水井（表 A.3.36）
func (p *DrainageWellParams) Validate() error {
	v := &specValidator{}
	positive(v, "L", p.Length)
	positive(v, "W", p.Width)
	positive(v, "H", p.Height)
	positive(v, "D(井脖直径)", p.NeckDiameter)
	positive(v, "H1(井脖高)", p.NeckHeight)
	positive(v, "H2(底板厚)", p.BottomThickness)
	positive(v, "T(壁厚)", p.WallThickness)
	nonNegative(v, "T1(垫层溢出)", p.CushionExtension)
	return v.err()
}

// 管枕（表 A.3.38）: POS/R 与 N 一致
func (p *PipeSupportParams) Validate() error {
	v := &specValidator{}
	v.relation(p.Count >= 1, "N(管枕数量) 必须 >= 1 (当前 %d)", p.Count)
	v.relation(len(p.Positions) == int(p.Count), "POS 数组长度(%d) 须与 N(%d) 一致", len(p.Positions), p.Count)
	v.relation(len(p.Radii) == int(p.Count), "R 数组长度(%d) 须与 N(%d) 一致", len(p.Radii), p.Count)
	positive(v, "L(管枕长)", p.Length)
	positive(v, "h(管枕高)", p.Height)
	return v.err()
}

// 盖板（表 A.3.40）: 形式 P 0-长方形 1-扇形
func (p *CoverPlateParams) Validate() error {
	v := &specValidator{}
	enumIn(v, "P(形式)", p.Style, 0, 1)
	positive(v, "H(厚度)", p.Thickness)
	if p.Style == 0 {
		positive(v, "L(长)", p.Length)
	} else {
		positive(v, "A(小半径)", p.SmallRadius)
		positive(v, "B(大半径)", p.LargeRadius)
		v.relation(p.LargeRadius > p.SmallRadius, "B(大半径) 须 > A(小半径) (当前 %v <= %v)", p.LargeRadius, p.SmallRadius)
	}
	return v.err()
}

// 光缆槽盒（表 A.3.42）: 外轮廓>内轮廓
func (p *CableRayParams) Validate() error {
	v := &specValidator{}
	positive(v, "L1(外长)", p.OuterLength)
	positive(v, "H1(外高)", p.OuterHeight)
	positive(v, "L2(内长)", p.InnerLength)
	positive(v, "H2(内高)", p.InnerHeight)
	positive(v, "D(盖板厚)", p.CoverThickness)
	v.relation(p.OuterLength > p.InnerLength, "L1 须 > L2 (当前 %v <= %v)", p.OuterLength, p.InnerLength)
	v.relation(p.OuterHeight > p.InnerHeight, "H1 须 > H2 (当前 %v <= %v)", p.OuterHeight, p.InnerHeight)
	return v.err()
}

// ==================== 统一入口 ====================

// specValidationError 按 Params 具体类型分发规范校验; 非 GIM 类型返回 nil(仅保留 NaN 防御)。
func specValidationError(params interface{}) error {
	// Create* 以值类型传参, 单测/调用方可能传指针: 统一解引用后再分发
	if params != nil {
		if v := reflect.ValueOf(params); v.Kind() == reflect.Ptr {
			if v.IsNil() {
				return nil
			}
			params = v.Elem().Interface()
		}
	}
	switch p := params.(type) {
	// ---- 换流站基本图元 ----
	case SphereParams:
		return p.Validate()
	case RotationalEllipsoidParams:
		return p.Validate()
	case CuboidParams:
		return p.Validate()
	case DiamondFrustumParams:
		return p.Validate()
	case OffsetRectangularTableParams:
		return p.Validate()
	case CylinderShapeParams:
		return p.Validate()
	case SharpBentCylinderParams:
		return p.Validate()
	case TruncatedConeParams:
		return p.Validate()
	case EccentricTruncatedConeParams:
		return p.Validate()
	case RingParams:
		return p.Validate()
	case RectangularRingParams:
		return p.Validate()
	case EllipticRingParams:
		return p.Validate()
	case CircularGasketParams:
		return p.Validate()
	case TableGasketParams:
		return p.Validate()
	case SquareGasketParams:
		return p.Validate()
	case StretchedBodyParams:
		return p.Validate()
	case PorcelainBushingParams:
		return p.Validate()
	case ConePorcelainBushingParams:
		return p.Validate()
	case InsulatorStringParams:
		return p.Validate()
	case VTypeInsulatorParams:
		return p.Validate()
	case TerminalBlockParams:
		return p.Validate()
	case RectangularFixedPlateParams:
		return p.Validate()
	case CircularFixedPlateParams:
		return p.Validate()
	case WireParams:
		return p.Validate()
	case CableParams:
		return p.Validate()
	// ---- 型钢 ----
	case AngleSteelParams:
		return p.Validate()
	case IShapedSteelParams:
		return p.Validate()
	case ChannelSteelParams:
		return p.Validate()
	case TSteelParams:
		return p.Validate()
	// ---- 架空输电线路 ----
	case BoredPileParams:
		return p.Validate()
	case PileCapParams:
		return p.Validate()
	case RockAnchorParams:
		return p.Validate()
	case RockPileCapParams:
		return p.Validate()
	case EmbeddedRockAnchorParams:
		return p.Validate()
	case InclinedRockAnchorParams:
		return p.Validate()
	case ExcavatedBaseParams:
		return p.Validate()
	case StepBaseParams:
		return p.Validate()
	case StepPlateBaseParams:
		return p.Validate()
	case SlopedBaseBaseParams:
		return p.Validate()
	case CompositeCaissonBaseParams:
		return p.Validate()
	case RaftBaseParams:
		return p.Validate()
	case DirectBuriedBaseParams:
		return p.Validate()
	case SteelSleeveBaseParams:
		return p.Validate()
	case PrecastColumnBaseParams:
		return p.Validate()
	case PrecastPinnedBaseParams:
		return p.Validate()
	case PrecastMetalSupportBaseParams:
		return p.Validate()
	case PrecastConcreteSupportBaseParams:
		return p.Validate()
	case TransmissionLineParams:
		return p.Validate()
	case InsulatorCompositeParams:
		return p.Validate()
	case PoleTowerParams:
		return p.Validate()
	case SingleHookAnchorParams:
		return p.Validate()
	case TripleHookAnchorParams:
		return p.Validate()
	case RibbedAnchorParams:
		return p.Validate()
	case NutAnchorParams:
		return p.Validate()
	case TripleArmAnchorParams:
		return p.Validate()
	case PositioningPlateAnchorParams:
		return p.Validate()
	case StubAngleParams:
		return p.Validate()
	case StubTubeParams:
		return p.Validate()
	// ---- 电缆线路 ----
	case CableWireParams:
		return p.Validate()
	case CableJointParams:
		return p.Validate()
	case OpticalFiberBoxParams:
		return p.Validate()
	case CableTerminalParams:
		return p.Validate()
	case CableAccessoryParams:
		return p.Validate()
	case CableBracketParams:
		return p.Validate()
	case CableClampParams:
		return p.Validate()
	case CablePoleParams:
		return p.Validate()
	case GroundFlatIronParams:
		return p.Validate()
	case EmbeddedPartParams:
		return p.Validate()
	case UShapedRingParams:
		return p.Validate()
	case LiftingEyeParams:
		return p.Validate()
	case CornerWellParams:
		return p.Validate()
	case TunnelWellParams:
		return p.Validate()
	case ThreeWayWellParams:
		return p.Validate()
	case FourWayWellParams:
		return p.Validate()
	case PipeRowParams:
		return p.Validate()
	case CableTrenchParams:
		return p.Validate()
	case CableTunnelParams:
		return p.Validate()
	case CableTrayParams:
		return p.Validate()
	case CableLBeamParams:
		return p.Validate()
	case ManholeParams:
		return p.Validate()
	case ManholeCoverParams:
		return p.Validate()
	case LadderParams:
		return p.Validate()
	case SumpParams:
		return p.Validate()
	case FootpathParams:
		return p.Validate()
	case ShaftChamberParams:
		return p.Validate()
	case TunnelCompartmentPartitionParams:
		return p.Validate()
	case TunnelPartitionBoardParams:
		return p.Validate()
	case ObliqueVentilationDuctParams:
		return p.Validate()
	case VentilationPavilionParams:
		return p.Validate()
	case StraightVentilationDuctParams:
		return p.Validate()
	case DrainageWellParams:
		return p.Validate()
	case PipeSupportParams:
		return p.Validate()
	case CoverPlateParams:
		return p.Validate()
	case CableRayParams:
		return p.Validate()
	}
	return nil
}

// rejectParams Create* 入口统一防御: NaN 或规范值域违规均拒绝。
// 非 GIM 类型仅保留 hasNaN 行为, 与既有契约一致。
func rejectParams(params interface{}) bool {
	if hasNaN(params) {
		return true
	}
	return specValidationError(params) != nil
}
