package topo

// 图库生成器: 以规范名义参数逐个生成 GIM 参数化图元 STL,
// 供 three.js 加载截图做几何符合性目检。
//
// 运行: GALLERY_DIR=./gallery CC=/usr/bin/clang CXX=/usr/bin/clang++ go test -run TestGenerateGallery -v .

import (
	"encoding/json"
	"fmt"
	"math"
	"os"
	"path/filepath"
	"testing"
)

type galleryItem struct {
	Name  string `json:"name"`
	Group string `json:"group"`
	File  string `json:"file"`
	OK    bool   `json:"ok"`
	Note  string `json:"note,omitempty"`
}

type galleryEntry struct {
	Label   string
	Group   string
	Build   func() *Shape
	Skipped bool // 已知内核几何问题(见加固报告), 不参与截图
}

func galleryCases() []galleryEntry {
	p3 := NewPoint3
	d3 := NewDir3FromXYZ
	return []galleryEntry{
		// ===== 换流站基本图元 (Q/GDW 11809—2018 附录 B) =====
		{"Sphere", "GS", func() *Shape { return CreateSphere(SphereParams{Radius: 100}) }, false},
		{"RotationalEllipsoid", "GS", func() *Shape {
			return CreateRotationalEllipsoid(RotationalEllipsoidParams{PolarRadius: 120, EquatorialRadius: 70, Height: 160})
		}, false},
		{"Cuboid", "GS", func() *Shape { return CreateCuboid(CuboidParams{Length: 200, Width: 120, Height: 80}) }, false},
		{"Table(棱台)", "GS", func() *Shape {
			return CreateDiamondFrustum(DiamondFrustumParams{TopDiag1: 60, TopDiag2: 80, BottomDiag1: 120, BottomDiag2: 160, Height: 100})
		}, false},
		{"OffsetRectangularTable", "GS", func() *Shape {
			return CreateOffsetRectangularTable(OffsetRectangularTableParams{TopLength: 80, TopWidth: 60, BottomLength: 160, BottomWidth: 120, Height: 90, XOffset: 20, YOffset: 15})
		}, false},
		{"Cylinder", "GS", func() *Shape { return CreateCylinderShape(CylinderShapeParams{Radius: 60, Height: 150}) }, false},
		{"BendingCylindrical", "GS", func() *Shape {
			return CreateSharpBentCylinder(SharpBentCylinderParams{Radius: 25, Length: 80, BendAngle: 1.2})
		}, false},
		{"TruncatedCone", "GS", func() *Shape {
			return CreateTruncatedCone(TruncatedConeParams{TopRadius: 40, BottomRadius: 80, Height: 120})
		}, false},
		{"EccentricTruncatedCone", "GS", func() *Shape {
			return CreateEccentricTruncatedCone(EccentricTruncatedConeParams{TopRadius: 30, BottomRadius: 70, Height: 110, TopXOffset: 15, TopYOffset: 10})
		}, false},
		{"Ring", "GS", func() *Shape { return CreateRing(RingParams{RingRadius: 90, TubeRadius: 15, Angle: 4.2}) }, false},
		{"RectangularRing", "GS", func() *Shape {
			return CreateRectangularRing(RectangularRingParams{TubeRadius: 8, FilletRadius: 12, Length: 120, Width: 40})
		}, false},
		{"EllipticRing", "GS", func() *Shape {
			return CreateEllipticRing(EllipticRingParams{TubeRadius: 8, MajorRadius: 70, MinorRadius: 45})
		}, false},
		{"CircularGasket", "GS", func() *Shape {
			return CreateCircularGasket(CircularGasketParams{OuterRadius: 90, InnerRadius: 60, Height: 12, Angle: 4.5})
		}, false},
		{"TableGasket", "GS", func() *Shape {
			return CreateTableGasket(TableGasketParams{TopRadius: 70, OuterRadius: 95, InnerRadius: 45, Height: 12, Angle: 4.0})
		}, false},
		{"SquareGasket(圆角)", "GS", func() *Shape {
			return CreateSquareGasket(SquareGasketParams{OuterLength: 120, OuterWidth: 90, InnerLength: 80, InnerWidth: 55, Height: 10, CornerType: 2, CornerParam: 0.8})
		}, false},
		{"SquareGasket(切角)", "GS", func() *Shape {
			return CreateSquareGasket(SquareGasketParams{OuterLength: 120, OuterWidth: 90, InnerLength: 80, InnerWidth: 55, Height: 10, CornerType: 3, CornerParam: 12})
		}, false},
		{"StretchedBody", "GS", func() *Shape {
			return CreateStretchedBody(StretchedBodyParams{Points: []Point3{p3([3]float64{0, 0, 0}), p3([3]float64{120, 0, 0}), p3([3]float64{120, 90, 0}), p3([3]float64{60, 130, 0}), p3([3]float64{0, 90, 0})}, Normal: d3([3]float64{0, 0, 1}), Length: 60})
		}, false},
		{"PorcelainBushing", "GS", func() *Shape {
			return CreatePorcelainBushing(PorcelainBushingParams{Height: 400, Radius: 45, BigSkirtRadius: 90, SmallSkirtRadius: 70, Count: 6})
		}, false},
		{"ConePorcelainBushing", "GS", func() *Shape {
			return CreateConePorcelainBushing(ConePorcelainBushingParams{Height: 500, BottomRadius: 55, TopRadius: 35, BottomSkirtRadius1: 100, BottomSkirtRadius2: 78, TopSkirtRadius1: 70, TopSkirtRadius2: 52, Count: 8})
		}, false},
		{"InsulatorString", "GS", func() *Shape {
			return CreateInsulatorString(InsulatorStringParams{Count: 2, Spacing: 400, InsulatorCount: 10, Height: 55, BigSkirtRadius: 90, SmallSkirtRadius: 70, Radius: 18, FrontLength: 60, BackLength: 60, SplitCount: 2})
		}, false},
		{"VTypeInsulator", "GS", func() *Shape {
			return CreateVTypeInsulator(VTypeInsulatorParams{FrontSpacing: 320, BackSpacing: 160, InsulatorCount: 8, Height: 55, Radius: 18, BigSkirtRadius: 80, SmallSkirtRadius: 62, FrontLength: 50, BackLength: 50, SplitCount: 1})
		}, false},
		{"TerminalBlock", "GS", func() *Shape {
			return CreateTerminalBlock(TerminalBlockParams{Length: 220, Width: 130, Thickness: 12, ChamferLength: 8, ColumnSpacing: 30, RowSpacing: 24, HoleRadius: 6, ColumnCount: 5, RowCount: 3, BottomOffset: 15})
		}, false},
		{"RectangularFixedPlate", "GS", func() *Shape {
			return CreateRectangularFixedPlate(RectangularFixedPlateParams{Length: 240, Width: 160, Thickness: 12, ColumnSpacing: 60, RowSpacing: 45, ColumnCount: 3, RowCount: 2, HasMiddleHole: true, HoleDiameter: 14})
		}, false},
		{"CircularFixedPlate", "GS", func() *Shape {
			return CreateCircularFixedPlate(CircularFixedPlateParams{Length: 240, Width: 240, Thickness: 12, RingRadius: 80, HoleCount: 8, HasMiddleHole: true, HoleDiameter: 14})
		}, false},
		{"Wire", "GS", func() *Shape {
			return CreateWire(WireParams{StartPoint: p3([3]float64{0, 0, 0}), EndPoint: p3([3]float64{3000, 3000, 1500}), StartDir: d3([3]float64{1, 1, 0.5}), EndDir: d3([3]float64{1, 1, 0.5}), Sag: 300, Diameter: 100})
		}, false},
		{"Cable", "GS", func() *Shape {
			return CreateCable(CableParams{StartPoint: p3([3]float64{0, 0, 0}), EndPoint: p3([3]float64{1000, 0, 0}), InflectionPoints: []Point3{p3([3]float64{400, 200, 0}), p3([3]float64{700, 200, 0})}, Radii: []float32{300, 300}, Diameter: 60})
		}, false},
		// ===== 型钢 =====
		{"AngleSteel(等边)", "STEEL", func() *Shape { return CreateAngleSteel(AngleSteelParams{L1: 50, L2: 50, X: 5, Length: 800}) }, false},
		{"AngleSteel(不等边)", "STEEL", func() *Shape { return CreateAngleSteel(AngleSteelParams{L1: 75, L2: 50, X: 5, Length: 800}) }, false},
		{"I-beam(工字钢)", "STEEL", func() *Shape {
			return CreateIShapedSteel(IShapedSteelParams{Height: 200, FlangeWidth: 100, WebThickness: 7, FlangeThickness: 11, Length: 900})
		}, false},
		{"H-beam", "STEEL", func() *Shape {
			return CreateIShapedSteel(IShapedSteelParams{Height: 300, FlangeWidth: 200, WebThickness: 8, FlangeThickness: 13, Length: 900})
		}, false},
		{"BeamChannel(槽钢)", "STEEL", func() *Shape {
			return CreateChannelSteel(ChannelSteelParams{Height: 180, FlangeWidth: 70, WebThickness: 9, FlangeThickness: 11, Length: 900})
		}, false},
		{"T-Steel", "STEEL", func() *Shape {
			return CreateTSteel(TSteelParams{Height: 100, Width: 100, WebThickness: 6, FlangeThickness: 8, Length: 900})
		}, false},
		// ===== 架空输电线路 (Q/GDW 11810.2 附录 E) =====
		{"BoredPile(挖孔桩)", "GT", func() *Shape {
			return CreateBoredPileBase(BoredPileParams{H1: 1000, H2: 300, H3: 500, H4: 30, Diameter: 50, D: 200})
		}, false},
		{"PileCap(承台桩)", "GT", func() *Shape {
			return CreatePileCapBase(PileCapParams{H1: 700, H2: 500, H3: 2600, H4: 300, H5: 500, H6: 400, Diameter: 600, D: 1000, B: 800, B1: 2600, L1: 2600, E1: 50, E2: 50, CS: 0, ZCount: 4, ZPosArray: []Point3{p3([3]float64{-800, -800, 0}), p3([3]float64{800, -800, 0}), p3([3]float64{-800, 800, 0}), p3([3]float64{800, 800, 0})}})
		}, false},
		{"RockAnchor(直锚岩石)", "GT", func() *Shape {
			return CreateRockAnchorBase(RockAnchorParams{H1: 1200, H2: 2400, Diameter: 90, B1: 400, L1: 400, ZCount: 2, ZPosArray: []Point3{p3([3]float64{-300, 0, 0}), p3([3]float64{300, 0, 0})}})
		}, false},
		{"Excavated(掏挖)", "GT", func() *Shape {
			return CreateExcavatedBase(ExcavatedBaseParams{H1: 800, H2: 400, H3: 2200, Diameter: 700, D: 1200, Alpha1: 0, Alpha2: 0})
		}, false},
		{"StepBase(台阶)", "GT", func() *Shape {
			return CreateStepBase(StepBaseParams{H: 700, H1: 350, H2: 350, H3: 0, B: 900, B1: 1500, B2: 2100, B3: 0, L1: 1500, L2: 2100, L3: 0, N: 2})
		}, false},
		{"SlopedBase(斜坡底板)", "GT", func() *Shape {
			return CreateSlopedBaseBase(SlopedBaseBaseParams{H1: 600, H2: 400, H3: 2000, B: 800, B1: 1800, B2: 2600, L1: 1800, L2: 2600, Alpha1: 0.1, Alpha2: 0.1})
		}, false},
		{"Raft(筏板)", "GT", func() *Shape {
			return CreateRaftBase(RaftBaseParams{H1: 500, H2: 600, H3: 700, Beam1: 350, Beam2: 350, B1: 2600, B2: 1800, L1: 3200, L2: 2400})
		}, false},
		{"DirectBuried(直埋)", "GT", func() *Shape {
			return CreateDirectBuriedBase(DirectBuriedBaseParams{H1: 2400, H2: 300, Diameter: 400, D: 400, B: 700, T: 60})
		}, false},
		{"SteelSleeve(钢套筒)", "GT", func() *Shape {
			return CreateSteelSleeveBase(SteelSleeveBaseParams{H1: 600, H2: 400, H3: 2200, H4: 300, D: 500, D1: 0, D2: 0, T: 50, B1: 0, B2: 0})
		}, false},
		{"PrecastColumn(装配直柱)", "GT", func() *Shape {
			return CreatePrecastColumnBase(PrecastColumnBaseParams{H1: 600, H2: 300, H3: 2100, D: 450, B1: 900, B2: 1500, L1: 900, L2: 1500})
		}, false},
		{"PrecastPinned(装配铰接)", "GT", func() *Shape {
			return CreatePrecastPinnedBase(PrecastPinnedBaseParams{H1: 600, H2: 300, H3: 2100, D: 450, B1: 900, B2: 1500, L1: 900, L2: 1500, B: 0, H: 0, L: 0})
		}, false},
		{"PrecastConcreteSupport(装配支架)", "GT", func() *Shape {
			return CreatePrecastConcreteSupportBase(PrecastConcreteSupportBaseParams{H1: 500, H2: 400, H3: 1800, H4: 300, H5: 250, Beam1: 300, Beam2: 300, Beam3: 250, B1: 1800, B2: 1200, L1: 1800, L2: 1000, S1: 120, N1: 2})
		}, false},
		{"TransmissionLine(导地线)", "GT", func() *Shape {
			return CreateTransmissionLine(TransmissionLineParams{Type: "JL/G1A-400", SectionalArea: 400, OutsideDiameter: 27.6, WireWeight: 1300, CoefficientOfElasticity: 65000, ExpansionCoefficient: 20.5, RatedStrength: 90000},
				p3([3]float64{0, 0, 0}), p3([3]float64{2000, 0, 0}))
		}, false},
		{"SingleHookAnchor(地脚螺栓)", "GT", func() *Shape {
			return CreateSingleHookAnchor(SingleHookAnchorParams{BoltDiameter: 24, ExposedLength: 120, NutCount: 2, NutHeight: 18, NutOD: 40, WasherCount: 1, WasherShape: WasherShapeTypeRound, WasherSize: 50, WasherThickness: 6, AnchorLength: 300, HookStraightLength: 80, HookDiameter: 48})
		}, false},
		{"StubAngle(插入角钢)", "GT", func() *Shape {
			return CreateStubAngle(StubAngleParams{LegWidth: 80, Thickness: 8, Slope: 0.05, ExposedLength: 150, AnchorLength: 400})
		}, false},
		{"StubTube(插入钢管)", "GT", func() *Shape {
			return CreateStubTube(StubTubeParams{Diameter: 120, Thickness: 10, Slope: 0.05, ExposedLength: 150, AnchorLength: 400})
		}, false},
		// ===== 电缆线路 (T/CEC 5056.3 附录 A/B) =====
		{"CableWire(电缆)", "EC", func() *Shape {
			return CreateCableWire(CableWireParams{Points: []Point3{p3([3]float64{0, 0, 0}), p3([3]float64{400, 0, 0}), p3([3]float64{700, 150, 0}), p3([3]float64{1100, 150, 0})}, OutsideDiameter: 80})
		}, false},
		{"CableJoint(中间接头)", "EC", func() *Shape {
			return CreateCableJoint(CableJointParams{Length: 450, OuterDiameter: 115, TerminalLength: 55, InnerDiameter: 75})
		}, false},
		{"OpticalFiberBox(光缆接头盒)", "EC", func() *Shape {
			return CreateOpticalFiberBox(OpticalFiberBoxParams{Length: 420, Height: 130, Width: 110})
		}, false},
		{"CableTerminal(电缆终端)", "EC", func() *Shape {
			return CreateCableTerminal(CableTerminalParams{Sort: CableTerminalTypeOutdoor, Height: 1000, TopDiameter: 200, BottomDiameter: 300, TailDiameter: 350, TailHeight: 50, SkirtCount: 18, UpperSkirtTopDiameter: 330, UpperSkirtBottomDiameter: 340, LowerSkirtTopDiameter: 380, LowerSkirtBottomDiameter: 400, SkirtSectionHeight: 40, UpperTerminalLength: 100, UpperTerminalDiameter: 80, LowerTerminalLength: 120, LowerTerminalDiameter: 100, Hole1Diameter: 20, Hole2Diameter: 20, Hole1Distance: 30, HoleSpacing: 40, FlangeHoleDiameter: 25, FlangeHoleSpacing: 400, FlangeWidth: 450, FlangeCenterHoleRadius: 75, FlangeChamferRadius: 10, FlangeOpeningWidth: 120, FlangeBoltHeight: 40})
		}, false},
		{"CableAccessory(接地箱)", "EC", func() *Shape {
			return CreateCableAccessory(CableAccessoryParams{Type: CableAccessoryTypeDirectGround, Length: 700, Width: 400, Height: 320, PortCount: 6, PortDiameter: 90, BackPanelDistance: 60, SidePanelDistance: 60})
		}, false},
		{"CableClamp(电缆夹具)", "EC", func() *Shape {
			return CreateCableClamp(CableClampParams{Type: CableClampSingle, Diameter: 90, Thickness: 30, Width: 60})
		}, false},
		{"CablePole(电缆立柱)", "EC", func() *Shape {
			return CreateCablePole(CablePoleParams{Specification: "[10", Length: 2400, Radius: 0, ArcAngle: 0, Width: 300, FixedLegLength: 250, FixedLegWidth: 150, Thickness: 10, MountPoints: []Point3{p3([3]float64{0, 0, 600}), p3([3]float64{0, 0, 1200}), p3([3]float64{0, 0, 1800})}})
		}, false},
		{"GroundFlatIron(接地扁铁)", "EC", func() *Shape {
			return CreateGroundFlatIron(GroundFlatIronParams{Length: 1500, Height: 60, Thickness: 8})
		}, false},
		{"EmbeddedPart(预埋件)", "EC", func() *Shape {
			return CreateEmbeddedPart(EmbeddedPartParams{Length: 300, Radius: 60, Height: 250, MaterialRadius: 10, LowerLength: 150})
		}, false},
		{"UShapedRing(U型拉环)", "EC", func() *Shape {
			return CreateUShapedRing(UShapedRingParams{Thickness: 20, Height: 100, Radius: 80, Length: 50})
		}, false},
		{"LiftingEye(吊攀)", "EC", func() *Shape {
			return CreateLiftingEye(LiftingEyeParams{Height: 160, RingRadius: 55, PipeDiameter: 40})
		}, false},
		{"CornerWell(转角井)", "EC", func() *Shape {
			return CreateCornerWell(CornerWellParams{LeftLength: 2500, RightLength: 2500, Width: 2200, Height: 2800, TopThickness: 250, BottomThickness: 250, WallThickness: 220, Angle: 90, CornerRadius: 1200, CushionExtension: 100, CushionThickness: 100})
		}, false},
		{"TunnelWell(直线井)", "EC", func() *Shape {
			return CreateTunnelWell(TunnelWellParams{Type: TunnelWellStraight, Length: 1600, Width: 300, Height: 360, TopThickness: 40, BottomThickness: 50, OuterWallThickness: 60, CushionExtension: 20, CushionThickness: 30})
		}, false},
		{"CableTrench(电缆沟)", "EC", func() *Shape {
			return CreateCableTrench(CableTrenchParams{Width: 600, Height: 800, CoverWidth: 640, CoverThickness: 50, BaseExtension: 100, BaseThickness: 150, CushionExtension: 120, CushionThickness: 100, WallThickness: 150, WallThickness2: 100, Points: []ChannelPoint{{Position: p3([3]float64{0, 0, 0}), Ctype: 0}, {Position: p3([3]float64{4000, 0, 0}), Ctype: 0}}})
		}, false},
		{"CableTunnel(马蹄形隧道)", "EC", func() *Shape {
			return CreateCableTunnel(CableTunnelParams{Style: 2, Width: 2800, Height: 3000, TopThickness: 300, BottomThickness: 300, OuterWallThickness: 250, InnerWallThickness: 0, ArcHeight: 900, BottomPlatformHeight: 400, CushionExtension: 100, CushionThickness: 100, Points: []ChannelPoint{{Position: p3([3]float64{0, 0, 0}), Ctype: 0}, {Position: p3([3]float64{5000, 0, 0}), Ctype: 0}}})
		}, false},
		{"CableTray(拱形桥架)", "EC", func() *Shape {
			return CreateCableTray(CableTrayParams{Style: 1, ColumnDiameter: 220, ColumnHeight: 3200, Span: 3000, Width: 900, Height: 700, TopPlateHeight: 120, ArcHeight: 150, WallThickness: 80,
				PipePositions: []Point2{NewPoint2([2]float64{0, 0}), NewPoint2([2]float64{300, 0}), NewPoint2([2]float64{600, 0})}, PipeInnerDiameters: []float32{150, 150, 150}, PipeWallThicknesses: []float32{15, 15, 15}, HasProtectionPlate: false,
				Points: []ChannelPoint{{Position: p3([3]float64{0, 0, 0}), Ctype: 0}, {Position: p3([3]float64{3000, 0, 0}), Ctype: 0}}})
		}, false},
		{"CableLBeam(梁)", "EC", func() *Shape { return CreateCableLBeam(CableLBeamParams{Length: 2000, Width: 300, Height: 400}) }, false},
		{"Manhole(人孔)", "EC", func() *Shape {
			return CreateManhole(ManholeParams{Style: 2, Length: 800, Width: 700, Height: 900, WallThickness: 120})
		}, false},
		{"ManholeCover(井盖)", "EC", func() *Shape {
			return CreateManholeCover(ManholeCoverParams{Style: 2, Length: 750, Width: 750, Thickness: 60})
		}, false},
		{"Ladder(爬梯)", "EC", func() *Shape { return CreateLadder(LadderParams{Length: 450, Width: 400, Thickness: 30}) }, false},
		{"Sump(集水坑)", "EC", func() *Shape {
			return CreateSump(SumpParams{Length: 600, Width: 500, Depth: 700, BottomThickness: 120})
		}, false},
		{"ShaftChamber(竖井仓)", "EC", func() *Shape {
			return CreateShaftChamber(ShaftChamberParams{SupportWallThickness: 200, SupportDiameter: 900, SupportHeight: 3000, TopThickness: 250, InnerDiameter: 1400, WorkingHeight: 4200, OuterWallThickness: 250, InnerWallThickness: 200})
		}, false},
		{"TunnelPartitionBoard(井隔板)", "EC", func() *Shape {
			return CreateTunnelPartitionBoard(TunnelPartitionBoardParams{Style: TunnelPartitionBoardStyleCircular, Length: 700, Width: 500, Thickness: 200, HoleCount: 2, HolePositions: []Point2{NewPoint2([2]float64{150, 250}), NewPoint2([2]float64{450, 250})}, HoleStyles: []int32{1, 1}, HoleDiameters: []float32{200, 200}, HoleWidths: []float32{200, 200}})
		}, false},
		{"VentilationPavilion(风亭)", "EC", func() *Shape {
			return CreateVentilationPavilion(VentilationPavilionParams{TopLength: 1200, MiddleLength: 1600, BottomLength: 2000, TopWidth: 1000, MiddleWidth: 1400, BottomWidth: 1800, TopHeight: 600, Height: 2600, BaseHeight: 400})
		}, false},
		{"StraightVentilationDuct(直通风道)", "EC", func() *Shape {
			return CreateStraightVentilationDuct(StraightVentilationDuctParams{Diameter: 700, WallThickness: 100, Height: 2600})
		}, false},
		{"DrainageWell(排水井)", "EC", func() *Shape {
			return CreateDrainageWell(DrainageWellParams{Length: 500, Width: 450, Height: 600, NeckDiameter: 250, NeckHeight: 300, CushionExtension: 80, BottomThickness: 120, WallThickness: 100})
		}, false},
		{"PipeSupport(管枕)", "EC", func() *Shape {
			return CreatePipeSupport(PipeSupportParams{Style: 1, Count: 3, Positions: []Point2{NewPoint2([2]float64{0, 0}), NewPoint2([2]float64{500, 0}), NewPoint2([2]float64{1000, 0})}, Radii: []float32{90, 90, 90}, Length: 1100, Width: 200, Height: 120})
		}, false},
		{"CoverPlate(扇形盖板)", "EC", func() *Shape {
			return CreateCoverPlate(CoverPlateParams{Style: CoverPlateSector, Length: 250, Width: 0, SmallRadius: 200, LargeRadius: 1000, Thickness: 80})
		}, false},
		{"CableRay(光缆槽盒)", "EC", func() *Shape {
			return CreateCableRay(CableRayParams{OuterLength: 240, OuterHeight: 120, InnerLength: 200, InnerHeight: 90, CoverThickness: 6})
		}, false},
	}
}

func TestGenerateGallery(t *testing.T) {
	dir := os.Getenv("GALLERY_DIR")
	if dir == "" {
		t.Skip("需要 GALLERY_DIR 环境变量指定输出目录")
	}
	if err := os.MkdirAll(filepath.Join(dir, "stl"), 0o755); err != nil {
		t.Fatal(err)
	}
	items := []galleryItem{}
	for _, c := range galleryCases() {
		fname := fmt.Sprintf("%s.stl", sanitizeName(c.Label))
		path := filepath.Join(dir, "stl", fname)
		if c.Skipped {
			items = append(items, galleryItem{Name: c.Label, Group: c.Group, File: fname, OK: false, Note: "已知内核几何问题, 跳过(见加固报告)"})
			continue
		}
		shp := c.Build()
		if shp == nil || shp.IsNull() || !shp.IsValid() {
			items = append(items, galleryItem{Name: c.Label, Group: c.Group, File: fname, OK: false, Note: "生成失败(null/invalid)"})
			continue
		}
		if err := meshWriteStl(shp, path); err != nil {
			items = append(items, galleryItem{Name: c.Label, Group: c.Group, File: fname, OK: false, Note: "STL 写出失败: " + err.Error()})
			continue
		}
		if _, err := os.Stat(path); err != nil {
			items = append(items, galleryItem{Name: c.Label, Group: c.Group, File: fname, OK: false, Note: "STL 未写出"})
			continue
		}
		items = append(items, galleryItem{Name: c.Label, Group: c.Group, File: fname, OK: true})
	}
	mf, err := json.MarshalIndent(items, "", "  ")
	if err != nil {
		t.Fatal(err)
	}
	if err := os.WriteFile(filepath.Join(dir, "manifest.json"), mf, 0o644); err != nil {
		t.Fatal(err)
	}
	ok, fail, skip := 0, 0, 0
	for _, it := range items {
		switch {
		case it.OK:
			ok++
		case it.Note != "" && contains(it.Note, "跳过"):
			skip++
		default:
			fail++
			t.Logf("生成失败: %s (%s)", it.Name, it.Note)
		}
	}
	t.Logf("图库: %d 生成, %d 跳过, %d 失败", ok, skip, fail)
}

func sanitizeName(s string) string {
	out := []rune{}
	for _, r := range s {
		switch r {
		case '/', '\\', '(', ')', ' ', ':':
			out = append(out, '_')
		default:
			out = append(out, r)
		}
	}
	return string(out)
}

func contains(s, sub string) bool {
	return len(s) >= len(sub) && (s == sub || len(sub) == 0 || indexOf(s, sub) >= 0)
}

func indexOf(s, sub string) int {
	for i := 0; i+len(sub) <= len(s); i++ {
		if s[i:i+len(sub)] == sub {
			return i
		}
	}
	return -1
}

// meshWriteStl 先三角化再写出二进制 STL
// (StlAPI_Writer 需要既有三角化, 否则静默不产出)
func meshWriteStl(shp *Shape, path string) error {
	rec := NewMeshReceiver()
	if n := shp.Mesh(rec, 1e-8, 1.0, 0.5); n < 0 {
		return fmt.Errorf("三角化失败 (code=%d)", n)
	}
	total := 0
	for _, tris := range rec.Tris {
		total += len(tris)
	}
	if total == 0 {
		return fmt.Errorf("无三角形")
	}
	f, err := os.Create(path)
	if err != nil {
		return err
	}
	defer f.Close()
	header := make([]byte, 80)
	copy(header, "go-topo gallery")
	if _, err := f.Write(header); err != nil {
		return err
	}
	var cnt [4]byte
	cnt[0] = byte(total)
	cnt[1] = byte(total >> 8)
	cnt[2] = byte(total >> 16)
	cnt[3] = byte(total >> 24)
	if _, err := f.Write(cnt[:]); err != nil {
		return err
	}
	writeF32 := func(v float32) error {
		b := math.Float32bits(v)
		var bs [4]byte
		bs[0] = byte(b)
		bs[1] = byte(b >> 8)
		bs[2] = byte(b >> 16)
		bs[3] = byte(b >> 24)
		_, err := f.Write(bs[:])
		return err
	}
	for fi, tris := range rec.Tris {
		vers := rec.Vers[fi]
		for _, tri := range tris {
			a, b, c := vers[tri[0]].Data(), vers[tri[1]].Data(), vers[tri[2]].Data()
			// 法线由顶点叉乘计算
			ux, uy, uz := b[0]-a[0], b[1]-a[1], b[2]-a[2]
			vx, vy, vz := c[0]-a[0], c[1]-a[1], c[2]-a[2]
			nx, ny, nz := uy*vz-uz*vy, uz*vx-ux*vz, ux*vy-uy*vx
			l := math.Sqrt(float64(nx*nx + ny*ny + nz*nz))
			if l > 0 {
				nx, ny, nz = nx/l, ny/l, nz/l
			}
			for _, val := range []float64{nx, ny, nz} {
				if err := writeF32(float32(val)); err != nil {
					return err
				}
			}
			for _, pt := range [][3]float64{a, b, c} {
				for _, val := range pt {
					if err := writeF32(float32(val)); err != nil {
						return err
					}
				}
			}
			var attr [2]byte
			if _, err := f.Write(attr[:]); err != nil {
				return err
			}
		}
	}
	return nil
}
