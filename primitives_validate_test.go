package topo

import (
	"math"
	"strings"
	"testing"
)

// 规范参数化选项对齐测试:
// 每类 Params: 名义参数应通过校验; 越界参数应被拒绝; 规范默认值应自动生效。

func expectValid(t *testing.T, params interface{}) {
	t.Helper()
	if err := specValidationError(params); err != nil {
		t.Fatalf("名义参数被误拒: %v", err)
	}
}

func expectInvalid(t *testing.T, params interface{}, fieldSubstring string) {
	t.Helper()
	err := specValidationError(params)
	if err == nil {
		t.Fatalf("越界参数未被拒绝: %+v", params)
	}
	if fieldSubstring != "" && !strings.Contains(err.Error(), fieldSubstring) {
		t.Fatalf("拒绝信息未指明违规字段 %q: %v", fieldSubstring, err)
	}
}

func TestSpecValidationBasicPrimitives(t *testing.T) {
	expectValid(t, &SphereParams{Radius: 10})
	expectInvalid(t, &SphereParams{Radius: 0}, "R")
	expectInvalid(t, &SphereParams{Radius: -1}, "R")

	expectValid(t, &RotationalEllipsoidParams{PolarRadius: 10, EquatorialRadius: 5, Height: 20})
	expectInvalid(t, &RotationalEllipsoidParams{PolarRadius: 10, EquatorialRadius: 5, Height: 21}, "2*LR")

	expectValid(t, &CuboidParams{Length: 10, Width: 5, Height: 3})
	expectInvalid(t, &CuboidParams{Length: 0, Width: 5, Height: 3}, "L")

	// 棱台: 相似菱形约束 + 锥顶一致性
	expectValid(t, &DiamondFrustumParams{TopDiag1: 50, TopDiag2: 60, BottomDiag1: 100, BottomDiag2: 120, Height: 30})
	expectInvalid(t, &DiamondFrustumParams{TopDiag1: 50, TopDiag2: 60, BottomDiag1: 100, BottomDiag2: 100, Height: 30}, "相似菱形")
	expectInvalid(t, &DiamondFrustumParams{TopDiag1: 0, TopDiag2: 60, BottomDiag1: 100, BottomDiag2: 120, Height: 30}, "同时为 0")
	expectInvalid(t, &DiamondFrustumParams{TopDiag1: 120, TopDiag2: 60, BottomDiag1: 100, BottomDiag2: 120, Height: 30}, "TL1")

	// 偏移矩形台: LL≥TL, LW≥TW
	expectValid(t, &OffsetRectangularTableParams{TopLength: 40, TopWidth: 30, BottomLength: 50, BottomWidth: 40, Height: 20, XOffset: 5, YOffset: 5})
	expectInvalid(t, &OffsetRectangularTableParams{TopLength: 60, TopWidth: 30, BottomLength: 50, BottomWidth: 40, Height: 20}, "LL 须 >= TL")

	// 弯折圆柱: 0<Rad<2PI
	expectValid(t, &SharpBentCylinderParams{Radius: 10, Length: 50, BendAngle: 1.57})
	expectInvalid(t, &SharpBentCylinderParams{Radius: 10, Length: 50, BendAngle: 6.5}, "Rad")

	// 圆台: BR≥TR
	expectValid(t, &TruncatedConeParams{TopRadius: 10, BottomRadius: 20, Height: 30})
	expectValid(t, &TruncatedConeParams{TopRadius: 0, BottomRadius: 20, Height: 30}) // 锥
	expectInvalid(t, &TruncatedConeParams{TopRadius: 30, BottomRadius: 20, Height: 30}, "BR 须 >= TR")

	// 偏心圆台
	expectValid(t, &EccentricTruncatedConeParams{TopRadius: 10, BottomRadius: 20, Height: 30, TopXOffset: 5, TopYOffset: 5})
	expectInvalid(t, &EccentricTruncatedConeParams{TopRadius: 10, BottomRadius: 20, Height: 30, TopXOffset: -1}, "TOPXOFF")
}

func TestSpecValidationRingsGaskets(t *testing.T) {
	// Ring: 0<DR<R
	expectValid(t, &RingParams{RingRadius: 100, TubeRadius: 10, Angle: 3.14})
	expectInvalid(t, &RingParams{RingRadius: 100, TubeRadius: 100, Angle: 3.14}, "DR")
	expectValid(t, &RingParams{RingRadius: 10, TubeRadius: 3, Angle: 0}) // 省略 → 默认 2π
	expectInvalid(t, &RingParams{RingRadius: 10, TubeRadius: 3, Angle: 7}, "Rad")

	// Ring 默认 2PI (Rad=0 合法, 表示取默认)
	expectValid(t, &RingParams{RingRadius: 100, TubeRadius: 10})
	ring := &RingParams{RingRadius: 100, TubeRadius: 10}
	ring.normalizeSpecDefaults()
	if ring.Angle != float32(twoPiF) {
		t.Fatalf("Ring 默认 Rad 应为 2π, 得到 %v", ring.Angle)
	}

	// RectangularRing: 0<DR<W, R<W/2, L>W
	expectValid(t, &RectangularRingParams{TubeRadius: 5, FilletRadius: 8, Length: 100, Width: 30})
	expectInvalid(t, &RectangularRingParams{TubeRadius: 5, FilletRadius: 16, Length: 100, Width: 30}, "W/2")
	expectInvalid(t, &RectangularRingParams{TubeRadius: 31, FilletRadius: 8, Length: 100, Width: 30}, "DR")

	// EllipticRing: L>W>0, DR<W
	expectValid(t, &EllipticRingParams{TubeRadius: 5, MajorRadius: 50, MinorRadius: 30})
	expectInvalid(t, &EllipticRingParams{TubeRadius: 5, MajorRadius: 30, MinorRadius: 50}, "L 须 > W")

	// CircularGasket: OR>IR>0
	expectValid(t, &CircularGasketParams{OuterRadius: 100, InnerRadius: 60, Height: 10, Angle: 3.0})
	expectInvalid(t, &CircularGasketParams{OuterRadius: 60, InnerRadius: 100, Height: 10, Angle: 3.0}, "OR 须 > IR")

	// TableGasket: IR<TR<OR
	expectValid(t, &TableGasketParams{TopRadius: 80, OuterRadius: 100, InnerRadius: 60, Height: 10, Angle: 3.0})
	expectInvalid(t, &TableGasketParams{TopRadius: 50, OuterRadius: 100, InnerRadius: 60, Height: 10, Angle: 3.0}, "IR < TR < OR")

	// SquareGasket: CT 分支取值
	expectValid(t, &SquareGasketParams{OuterLength: 40, OuterWidth: 30, InnerLength: 15, InnerWidth: 10, Height: 8, CornerType: 2, CornerParam: 3})
	expectValid(t, &SquareGasketParams{OuterLength: 40, OuterWidth: 30, InnerLength: 15, InnerWidth: 10, Height: 8, CornerType: 3, CornerParam: 5})
	expectInvalid(t, &SquareGasketParams{OuterLength: 40, OuterWidth: 30, InnerLength: 15, InnerWidth: 10, Height: 8, CornerType: 2, CornerParam: 4}, "圆角 Rad")
	expectInvalid(t, &SquareGasketParams{OuterLength: 40, OuterWidth: 30, InnerLength: 15, InnerWidth: 10, Height: 8, CornerType: 3, CornerParam: 100}, "切角 CL")
	expectInvalid(t, &SquareGasketParams{OuterLength: 40, OuterWidth: 30, InnerLength: 15, InnerWidth: 10, Height: 8, CornerType: 9}, "CT")

	// StretchedBody: 顶点≥3
	expectValid(t, &StretchedBodyParams{Points: []Point3{NewPoint3([3]float64{0, 0, 0}), NewPoint3([3]float64{10, 0, 0}), NewPoint3([3]float64{10, 10, 0})}, Normal: NewDir3FromXYZ([3]float64{0, 0, 1}), Length: 10})
	expectInvalid(t, &StretchedBodyParams{Points: []Point3{NewPoint3([3]float64{0, 0, 0}), NewPoint3([3]float64{10, 0, 0})}, Normal: NewDir3FromXYZ([3]float64{0, 0, 1}), Length: 10}, "顶点")
}

func TestSpecValidationBushingInsulator(t *testing.T) {
	// PorcelainBushing: R1≥R2>R
	expectValid(t, &PorcelainBushingParams{Height: 1000, Radius: 50, BigSkirtRadius: 100, SmallSkirtRadius: 80, Count: 10})
	expectInvalid(t, &PorcelainBushingParams{Height: 1000, Radius: 50, BigSkirtRadius: 80, SmallSkirtRadius: 100, Count: 10}, "R1 须 >= R2")
	expectInvalid(t, &PorcelainBushingParams{Height: 1000, Radius: 90, BigSkirtRadius: 100, SmallSkirtRadius: 80, Count: 10}, "R2 须 > R")

	// ConePorcelainBushing: 伞裙>对应锥半径
	expectValid(t, &ConePorcelainBushingParams{Height: 1200, BottomRadius: 60, TopRadius: 40, BottomSkirtRadius1: 100, BottomSkirtRadius2: 80, TopSkirtRadius1: 80, TopSkirtRadius2: 65, Count: 12})
	expectInvalid(t, &ConePorcelainBushingParams{Height: 1200, BottomRadius: 60, TopRadius: 40, BottomSkirtRadius1: 50, BottomSkirtRadius2: 80, TopSkirtRadius1: 80, TopSkirtRadius2: 65, Count: 12}, "BR1")

	// InsulatorString: D>2*R1
	expectValid(t, &InsulatorStringParams{Count: 2, Spacing: 600, InsulatorCount: 20, Height: 70, BigSkirtRadius: 125, SmallSkirtRadius: 100, Radius: 20, FrontLength: 100, BackLength: 100, SplitCount: 4})
	expectInvalid(t, &InsulatorStringParams{Count: 2, Spacing: 200, InsulatorCount: 20, Height: 70, BigSkirtRadius: 125, SmallSkirtRadius: 100, Radius: 20, FrontLength: 100, BackLength: 100, SplitCount: 4}, "D 须 > 2*R1")

	// VTypeInsulator: R1>R2
	expectValid(t, &VTypeInsulatorParams{FrontSpacing: 500, BackSpacing: 300, InsulatorCount: 15, Height: 70, Radius: 20, BigSkirtRadius: 100, SmallSkirtRadius: 80, FrontLength: 100, BackLength: 100, SplitCount: 2})
	expectInvalid(t, &VTypeInsulatorParams{FrontSpacing: 500, BackSpacing: 300, InsulatorCount: 15, Height: 70, Radius: 20, BigSkirtRadius: 80, SmallSkirtRadius: 100, FrontLength: 100, BackLength: 100, SplitCount: 2}, "R1 须 > R2")

	// TerminalBlock: L>W
	expectValid(t, &TerminalBlockParams{Length: 200, Width: 100, Thickness: 8, ChamferLength: 5, ColumnSpacing: 20, RowSpacing: 15, HoleRadius: 4, ColumnCount: 5, RowCount: 3, BottomOffset: 10})
	expectInvalid(t, &TerminalBlockParams{Length: 100, Width: 100, Thickness: 8, ChamferLength: 5, ColumnSpacing: 20, RowSpacing: 15, HoleRadius: 4, ColumnCount: 5, RowCount: 3, BottomOffset: 10}, "L 须 > W")

	// 固定板
	expectValid(t, &RectangularFixedPlateParams{Length: 200, Width: 150, Thickness: 10, ColumnSpacing: 50, RowSpacing: 40, ColumnCount: 3, RowCount: 2, HasMiddleHole: true, HoleDiameter: 12})
	expectInvalid(t, &RectangularFixedPlateParams{Length: 200, Width: 150, Thickness: 10, ColumnSpacing: 50, RowSpacing: 40, ColumnCount: 3, RowCount: 2, HoleDiameter: 0}, "D(孔径)")
	expectValid(t, &CircularFixedPlateParams{Length: 200, Width: 200, Thickness: 10, RingRadius: 70, HoleCount: 8, HasMiddleHole: true, HoleDiameter: 12})
	expectInvalid(t, &CircularFixedPlateParams{Length: 200, Width: 200, Thickness: 10, RingRadius: 70, HoleCount: 0, HoleDiameter: 12}, "N(开孔数)")
}

func TestSpecValidationWireCableSteels(t *testing.T) {
	expectValid(t, &WireParams{StartPoint: NewPoint3([3]float64{0, 0, 0}), EndPoint: NewPoint3([3]float64{1000, 0, -50}), Sag: 30, Diameter: 20})
	expectInvalid(t, &WireParams{StartPoint: NewPoint3([3]float64{0, 0, 0}), EndPoint: NewPoint3([3]float64{1000, 0, -50}), Sag: 0, Diameter: 20}, "Sag")

	expectValid(t, &CableParams{StartPoint: NewPoint3([3]float64{0, 0, 0}), EndPoint: NewPoint3([3]float64{2000, 0, 0}),
		InflectionPoints: []Point3{NewPoint3([3]float64{1000, 100, 0})}, Radii: []float32{500}, Diameter: 80})
	expectInvalid(t, &CableParams{StartPoint: NewPoint3([3]float64{0, 0, 0}), EndPoint: NewPoint3([3]float64{2000, 0, 0}),
		InflectionPoints: []Point3{NewPoint3([3]float64{1000, 100, 0})}, Radii: nil, Diameter: 80}, "一一对应")
	expectInvalid(t, &CableParams{StartPoint: NewPoint3([3]float64{0, 0, 0}), EndPoint: NewPoint3([3]float64{2000, 0, 0}),
		InflectionPoints: []Point3{NewPoint3([3]float64{1000, 100, 0})}, Radii: []float32{0}, Diameter: 80}, "IRArray[0]")

	// 型钢
	expectValid(t, &AngleSteelParams{L1: 50, L2: 50, X: 4, Length: 6000})
	expectValid(t, &AngleSteelParams{L1: 75, L2: 50, X: 5, Length: 6000})
	expectInvalid(t, &AngleSteelParams{L1: 50, L2: 50, X: 50, Length: 6000}, "肢厚")
	// 长肢归一化默认
	as := &AngleSteelParams{L1: 50, L2: 75, X: 5, Length: 6000}
	as.normalizeSpecDefaults()
	if as.L1 != 75 || as.L2 != 50 {
		t.Fatalf("不等边角钢应长肢在前, 得到 L1=%v L2=%v", as.L1, as.L2)
	}

	expectValid(t, &IShapedSteelParams{Height: 200, FlangeWidth: 100, WebThickness: 7, FlangeThickness: 11, Length: 6000})
	expectInvalid(t, &IShapedSteelParams{Height: 200, FlangeWidth: 100, WebThickness: 250, FlangeThickness: 11, Length: 6000}, "腹板厚")
	expectValid(t, &ChannelSteelParams{Height: 200, FlangeWidth: 75, WebThickness: 9, FlangeThickness: 11, Length: 6000})
	expectValid(t, &TSteelParams{Height: 100, Width: 100, WebThickness: 6, FlangeThickness: 8, Length: 3000})
}

func TestSpecValidationFoundations(t *testing.T) {
	// 挖孔桩: D≥d
	expectValid(t, &BoredPileParams{H1: 1200, H2: 300, H3: 4000, H4: 200, Diameter: 1000, D: 1800})
	expectInvalid(t, &BoredPileParams{H1: 1200, H2: 300, H3: 4000, H4: 200, Diameter: 1000, D: 800}, "D 须 >= d")

	// 承台: cs∈{0,1}, ZPOSTARRAY 与 ZCOUNT 一致
	expectValid(t, &PileCapParams{H1: 500, H2: 600, H3: 700, H4: 200, H5: 300, H6: 400, Diameter: 800, D: 1200, B: 900, B1: 3000, L1: 3000, E1: 10, E2: 10, CS: 0, ZCount: 4, ZPosArray: []Point3{
		NewPoint3([3]float64{0, 0, 0}), NewPoint3([3]float64{1, 0, 0}), NewPoint3([3]float64{0, 1, 0}), NewPoint3([3]float64{1, 1, 0}),
	}})
	expectInvalid(t, &PileCapParams{H1: 500, H2: 600, H3: 700, H4: 200, H5: 300, H6: 400, Diameter: 800, D: 1200, B: 900, B1: 3000, L1: 3000, CS: 2, ZCount: 4, ZPosArray: []Point3{
		NewPoint3([3]float64{0, 0, 0}), NewPoint3([3]float64{1, 0, 0}), NewPoint3([3]float64{0, 1, 0}), NewPoint3([3]float64{1, 1, 0}),
	}}, "cs")
	expectInvalid(t, &PileCapParams{H1: 500, H2: 600, H3: 700, H4: 200, H5: 300, H6: 400, Diameter: 800, D: 1200, B: 900, B1: 3000, L1: 3000, CS: 1, ZCount: 4, ZPosArray: []Point3{
		NewPoint3([3]float64{0, 0, 0}),
	}}, "ZPOSTARRAY")

	// 直锚式岩石锚桩
	expectValid(t, &RockAnchorParams{H1: 1500, H2: 3000, Diameter: 100, B1: 500, L1: 500, ZCount: 4, ZPosArray: []Point3{
		NewPoint3([3]float64{0, 0, 0}), NewPoint3([3]float64{1, 0, 0}), NewPoint3([3]float64{0, 1, 0}), NewPoint3([3]float64{1, 1, 0}),
	}})
	expectInvalid(t, &RockAnchorParams{H1: 1500, H2: 3000, Diameter: 100, B1: 500, L1: 500, ZCount: 4, ZPosArray: nil}, "ZCOUNT")

	// 台阶基础
	expectValid(t, &StepBaseParams{H: 800, H1: 300, H2: 300, H3: 200, B: 1000, B1: 1600, B2: 2200, B3: 2800, L1: 1600, L2: 2200, L3: 2800, N: 3})
	expectInvalid(t, &StepBaseParams{H: 800, H1: 300, H2: 300, H3: 200, B: 1000, B1: 1600, B2: 2200, B3: 2800, L1: 1600, L2: 2200, L3: 2800, N: 0}, "N(台阶数)")

	// 筏板: H3=0 无主梁
	expectValid(t, &RaftBaseParams{H1: 500, H2: 600, H3: 0, Beam1: 400, Beam2: 400, B1: 3000, B2: 2000, L1: 4000, L2: 3000})
	expectInvalid(t, &RaftBaseParams{H1: 500, H2: 600, H3: 0, Beam1: 0, Beam2: 400, B1: 3000, B2: 2000, L1: 4000, L2: 3000}, "b1")
}

func TestSpecValidationCableTypes(t *testing.T) {
	// 电(光)缆
	expectValid(t, &CableWireParams{Points: []Point3{NewPoint3([3]float64{0, 0, 0}), NewPoint3([3]float64{1000, 0, 0})}, OutsideDiameter: 100})
	expectInvalid(t, &CableWireParams{Points: []Point3{NewPoint3([3]float64{0, 0, 0})}, OutsideDiameter: 100}, "路径")

	// 中间接头: 外径>内径
	expectValid(t, &CableJointParams{Length: 500, OuterDiameter: 120, TerminalLength: 60, InnerDiameter: 80})
	expectInvalid(t, &CableJointParams{Length: 500, OuterDiameter: 80, TerminalLength: 60, InnerDiameter: 120}, "外径")

	// 接地箱: 进出口 3 或 6
	expectValid(t, &CableAccessoryParams{Type: CableAccessoryTypeDirectGround, Length: 600, Width: 400, Height: 300, PortCount: 6, PortDiameter: 80, BackPanelDistance: 50, SidePanelDistance: 50})
	expectInvalid(t, &CableAccessoryParams{Type: CableAccessoryTypeDirectGround, Length: 600, Width: 400, Height: 300, PortCount: 4, PortDiameter: 80}, "进出口数目")

	// 排管: 数组一致性
	expectValid(t, &PipeRowParams{PipeType: 0, PipePositions: []Point2{NewPoint2([2]float64{0, 0}), NewPoint2([2]float64{500, 0})},
		PipeInnerDiameters: []float32{200, 200}, PipeWallThicknesses: []float32{20, 20}, Points: []ChannelPoint{
			{Position: NewPoint3([3]float64{0, 0, 0}), Ctype: 0}, {Position: NewPoint3([3]float64{1000, 0, 0}), Ctype: 0},
		}})
	expectInvalid(t, &PipeRowParams{PipeType: 0, PipePositions: []Point2{NewPoint2([2]float64{0, 0}), NewPoint2([2]float64{500, 0})},
		PipeInnerDiameters: []float32{200}, PipeWallThicknesses: []float32{20, 20}, Points: []ChannelPoint{
			{Position: NewPoint3([3]float64{0, 0, 0}), Ctype: 0}, {Position: NewPoint3([3]float64{1000, 0, 0}), Ctype: 0},
		}}, "D1 数组长度")

	// 电缆隧道: 样式枚举
	expectValid(t, &CableTunnelParams{Style: 2, Width: 3000, Height: 3200, TopThickness: 300, BottomThickness: 300, OuterWallThickness: 250, InnerWallThickness: 0, ArcHeight: 800, Points: []ChannelPoint{
		{Position: NewPoint3([3]float64{0, 0, 0}), Ctype: 0}, {Position: NewPoint3([3]float64{5000, 0, 0}), Ctype: 0},
	}})
	expectInvalid(t, &CableTunnelParams{Style: 5, Width: 3000, Height: 3200, OuterWallThickness: 250, Points: []ChannelPoint{
		{Position: NewPoint3([3]float64{0, 0, 0}), Ctype: 0}, {Position: NewPoint3([3]float64{5000, 0, 0}), Ctype: 0},
	}}, "P(样式)")

	// 光缆槽盒: 外>内
	expectValid(t, &CableRayParams{OuterLength: 200, OuterHeight: 100, InnerLength: 180, InnerHeight: 80, CoverThickness: 5})
	expectInvalid(t, &CableRayParams{OuterLength: 200, OuterHeight: 100, InnerLength: 220, InnerHeight: 80, CoverThickness: 5}, "L1 须 > L2")

	// 盖板: 扇形 B>A
	expectValid(t, &CoverPlateParams{Style: 1, SmallRadius: 500, LargeRadius: 800, Thickness: 50})
	expectInvalid(t, &CoverPlateParams{Style: 1, SmallRadius: 900, LargeRadius: 800, Thickness: 50}, "B(大半径)")

	// 直通风道: T<D
	expectValid(t, &StraightVentilationDuctParams{Diameter: 800, WallThickness: 100, Height: 3000})
	expectInvalid(t, &StraightVentilationDuctParams{Diameter: 800, WallThickness: 900, Height: 3000}, "T 须在 (0, D)")
}

func TestSpecRejectParamsIntegration(t *testing.T) {
	// Create* 入口: 名义参数可生成, 越界参数被拒绝返回 nil
	shp := CreateCuboid(CuboidParams{Length: 100, Width: 50, Height: 30})
	if shp == nil || shp.IsNull() {
		t.Fatal("名义长方体应生成成功")
	}
	if shp := CreateCuboid(CuboidParams{Length: -100, Width: 50, Height: 30}); shp != nil && !shp.IsNull() {
		t.Fatal("负值长方体应被拒绝")
	}

	ring := CreateRing(RingParams{RingRadius: 100, TubeRadius: 10}) // Rad 缺省 → 2PI 整圆
	if ring == nil || ring.IsNull() {
		t.Fatal("Ring 默认 2π 应生成整圆")
	}

	if shp := CreateSphere(SphereParams{Radius: float32(math.NaN())}); shp != nil && !shp.IsNull() {
		t.Fatal("NaN 应被拒绝")
	}
}
