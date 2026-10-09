// 矿山专业参数化图元 Go 封装 (minebim P 线, Q/SHJ 0035.3-2012 图例台账):
// 造型全在 C++ (primitives_mine*.cc, GIM 模式), 本文件只做参数搬运 + 值域防御。
// 单位: m (minebim 场景口径; 轨件沿用铁路图元声明单位)。
package topo

/*
#include <stdlib.h>
#include <string.h>
#include "primitives_c_api.h"
#cgo CFLAGS: -I  ./libs
#cgo linux CXXFLAGS: -I ./libs  -std=gnu++14
#cgo darwin,amd64 CXXFLAGS: -I ./libs  -std=gnu++14
#cgo darwin,arm64 CXXFLAGS: -I ./libs  -std=gnu++14
#cgo windows CXXFLAGS: -I ./libs  -std=gnu++14
*/
import "C"
import (
	"runtime"
	"unsafe"
)

// MineSection 断面族 (值与 C++ mine_section 枚举对齐)。
type MineSection int

const (
	MineSectionRect      MineSection = 0 // 矩形
	MineSectionTrap      MineSection = 1 // 梯形
	MineSectionArch      MineSection = 2 // 半圆拱
	MineSectionArcArch   MineSection = 3 // 圆弧拱
	MineSectionHorseshoe MineSection = 4 // 马蹄
	MineSectionCircle    MineSection = 5 // 圆形
	MineSectionEllipse   MineSection = 6 // 椭圆
)

// MineShaftShape 断面形状 (井筒专用: 圆/矩形)。
const (
	MineShaftCircle = 0
	MineShaftRect   = 1
)

// cPoints []Point3 → C 数组 (malloc; 调用方 free)。
func cPoints(pts []Point3) (*C.pnt3d_t, C.int) {
	if len(pts) == 0 {
		return nil, 0
	}
	arr := (*C.pnt3d_t)(C.malloc(C.size_t(len(pts)) * C.sizeof_pnt3d_t))
	for i, pt := range pts {
		*(*C.pnt3d_t)(unsafe.Pointer(uintptr(unsafe.Pointer(arr)) + uintptr(i)*C.sizeof_pnt3d_t)) = pt.val
	}
	return arr, C.int(len(pts))
}

func freePnts(p unsafe.Pointer) {
	if p != nil {
		C.free(p)
	}
}

func finish(shp *C.topo_shape_t) *Shape {
	if shp == nil {
		return nil
	}
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

// ================= 立井井筒 (图例 2/3/4/5/9) =================

type MineShaftParams struct {
	Shape       int
	InnerRadius float32
	OuterRadius float32
	InnerLength float32
	InnerWidth  float32
	OuterLength float32
	OuterWidth  float32
	Depth       float32
}

func (p *MineShaftParams) to_struct() C.mine_shaft_params_t {
	var c C.mine_shaft_params_t
	c.shape = C.int(p.Shape)
	c.innerRadius = C.double(p.InnerRadius)
	c.outerRadius = C.double(p.OuterRadius)
	c.innerLength = C.double(p.InnerLength)
	c.innerWidth = C.double(p.InnerWidth)
	c.outerLength = C.double(p.OuterLength)
	c.outerWidth = C.double(p.OuterWidth)
	c.depth = C.double(p.Depth)
	return c
}

// CreateMineShaft 立井井筒 (井口在原点, 向 -Z)。
func CreateMineShaft(params MineShaftParams) *Shape {
	if rejectParams(params) {
		return nil
	}
	return finish(C.create_mine_shaft(params.to_struct()))
}

// CreateMineShaftAt 立井井筒 (井口在世界坐标 collarCenter, 向 -Z)。
func CreateMineShaftAt(params MineShaftParams, collarCenter Point3) *Shape {
	if rejectParams(params) {
		return nil
	}
	return finish(C.create_mine_shaft_at(params.to_struct(), collarCenter.val))
}

// ================= 煤仓/溜煤眼 (图例 16) =================

type MineOrepassStation struct {
	Depth  float32
	Radius float32
}

type MineOrepassParams struct {
	Center   Point3
	Stations []MineOrepassStation
}

func (p *MineOrepassParams) to_struct() C.mine_orepass_params_t {
	var c C.mine_orepass_params_t
	c.center = p.Center.val
	c.numStations = C.int(len(p.Stations))
	if len(p.Stations) > 0 {
		c.stations = (*C.mine_orepass_station_t)(C.malloc(C.size_t(len(p.Stations)) * C.sizeof_mine_orepass_station_t))
		for i, st := range p.Stations {
			cs := (*C.mine_orepass_station_t)(unsafe.Pointer(uintptr(unsafe.Pointer(c.stations)) + uintptr(i)*C.sizeof_mine_orepass_station_t))
			cs.depth = C.double(st.Depth)
			cs.radius = C.double(st.Radius)
		}
	}
	return c
}

func CreateMineOrepass(params MineOrepassParams) *Shape {
	if rejectParams(params) {
		return nil
	}
	cParams := params.to_struct()
	defer freePnts(unsafe.Pointer(cParams.stations))
	return finish(C.create_mine_orepass(cParams))
}

// ================= 断层破碎带透镜体 (图例 345-355) =================

type MineFaultLensParams struct {
	Center     Point3
	Strike     Dir3
	DipAzimuth Dir3
	DipAngle   float32
	ZoneWidth  float32
	ZoneLength float32
	TopElev    float32
	BottomElev float32
}

func (p *MineFaultLensParams) to_struct() C.mine_fault_lens_params_t {
	var c C.mine_fault_lens_params_t
	c.center = p.Center.val
	c.strike = p.Strike.val
	c.dipAzimuth = p.DipAzimuth.val
	c.dipAngle = C.double(p.DipAngle)
	c.zoneWidth = C.double(p.ZoneWidth)
	c.zoneLength = C.double(p.ZoneLength)
	c.topElev = C.double(p.TopElev)
	c.bottomElev = C.double(p.BottomElev)
	return c
}

func CreateMineFaultLens(params MineFaultLensParams) *Shape {
	if rejectParams(params) {
		return nil
	}
	return finish(C.create_mine_fault_lens(params.to_struct()))
}

// ================= 支护衬砌壳 (喷浆/砌碹/U型钢环) =================

type MineLiningParams struct {
	Points    []Point3
	Thickness float32
	Length    float32
	Dir       Dir3
}

func (p *MineLiningParams) to_struct() C.mine_lining_params_t {
	var c C.mine_lining_params_t
	c.points, c.numPoints = cPoints(p.Points)
	c.thickness = C.double(p.Thickness)
	c.length = C.double(p.Length)
	c.dir = p.Dir.val
	return c
}

func CreateMineLining(params MineLiningParams) *Shape {
	if rejectParams(params) {
		return nil
	}
	cParams := params.to_struct()
	defer freePnts(unsafe.Pointer(cParams.points))
	return finish(C.create_mine_lining(cParams))
}

// ================= A 井巷: 巷道/硐室/工作面/迎头/面状体 =================

type MineRoadwayParams struct {
	Section MineSection
	Width   float32
	Height  float32
	Path    []Point3 // 中心线 3D (含标高)
}

func (p *MineRoadwayParams) to_struct() C.mine_roadway_params_t {
	var c C.mine_roadway_params_t
	c.section = C.int(p.Section)
	c.width = C.double(p.Width)
	c.height = C.double(p.Height)
	c.path, c.numPath = cPoints(p.Path)
	return c
}

func CreateMineRoadway(params MineRoadwayParams) *Shape {
	if rejectParams(params) {
		return nil
	}
	cParams := params.to_struct()
	defer freePnts(unsafe.Pointer(cParams.path))
	return finish(C.create_mine_roadway(cParams))
}

type MineChamberParams struct {
	Center        Point3
	Length, Width float32
	Height        float32
}

func (p *MineChamberParams) to_struct() C.mine_chamber_params_t {
	var c C.mine_chamber_params_t
	c.center = p.Center.val
	c.length = C.double(p.Length)
	c.width = C.double(p.Width)
	c.height = C.double(p.Height)
	return c
}

func CreateMineChamber(params MineChamberParams) *Shape {
	if rejectParams(params) {
		return nil
	}
	return finish(C.create_mine_chamber(params.to_struct()))
}

type MineWorkingfaceParams struct {
	Origin        Point3
	Dir           Dir3
	FaceLength    float32
	Advance       float32
	SeamThickness float32
}

func (p *MineWorkingfaceParams) to_struct() C.mine_workingface_params_t {
	var c C.mine_workingface_params_t
	c.origin = p.Origin.val
	c.dir = p.Dir.val
	c.faceLength = C.double(p.FaceLength)
	c.advance = C.double(p.Advance)
	c.seamThickness = C.double(p.SeamThickness)
	return c
}

func CreateMineWorkingface(params MineWorkingfaceParams) *Shape {
	if rejectParams(params) {
		return nil
	}
	return finish(C.create_mine_workingface(params.to_struct()))
}

type MineHeadingParams struct {
	Center  Point3
	Dir     Dir3
	Section MineSection
	Width   float32
	Height  float32
}

func (p *MineHeadingParams) to_struct() C.mine_heading_params_t {
	var c C.mine_heading_params_t
	c.center = p.Center.val
	c.dir = p.Dir.val
	c.section = C.int(p.Section)
	c.width = C.double(p.Width)
	c.height = C.double(p.Height)
	return c
}

func CreateMineHeading(params MineHeadingParams) *Shape {
	if rejectParams(params) {
		return nil
	}
	return finish(C.create_mine_heading(params.to_struct()))
}

type MineAreaBodyParams struct {
	Boundary []Point3 // XY 边界 (z 忽略)
	BaseZ    float32
	Height   float32
}

func (p *MineAreaBodyParams) to_struct() C.mine_area_body_params_t {
	var c C.mine_area_body_params_t
	c.boundary, c.numBoundary = cPoints(p.Boundary)
	c.baseZ = C.double(p.BaseZ)
	c.height = C.double(p.Height)
	return c
}

func CreateMineAreaBody(params MineAreaBodyParams) *Shape {
	if rejectParams(params) {
		return nil
	}
	cParams := params.to_struct()
	defer freePnts(unsafe.Pointer(cParams.boundary))
	return finish(C.create_mine_area_body(cParams))
}

// ================= B 支护系统 =================

type MineBoltRowParams struct {
	Origin    Point3
	Axis      Dir3
	Section   MineSection
	Width     float32
	Height    float32
	RowCount  int
	PerRow    int
	Spacing   float32
	BoltLen   float32
	Diameter  float32
	Cable     bool
}

func (p *MineBoltRowParams) to_struct() C.mine_bolt_row_params_t {
	var c C.mine_bolt_row_params_t
	c.origin = p.Origin.val
	c.axis = p.Axis.val
	c.section = C.int(p.Section)
	c.width = C.double(p.Width)
	c.height = C.double(p.Height)
	c.rowCount = C.int(p.RowCount)
	c.perRow = C.int(p.PerRow)
	c.spacing = C.double(p.Spacing)
	c.boltLength = C.double(p.BoltLen)
	c.diameter = C.double(p.Diameter)
	c.cable = C.int(boolToInt(p.Cable))
	return c
}

func boolToInt(b bool) int {
	if b {
		return 1
	}
	return 0
}

func CreateMineBoltRow(params MineBoltRowParams) *Shape {
	if rejectParams(params) {
		return nil
	}
	return finish(C.create_mine_bolt_row(params.to_struct()))
}

type MineUsteelRowParams struct {
	Origin    Point3
	Axis      Dir3
	Section   MineSection
	Width     float32
	Height    float32
	Thickness float32
	Spacing   float32
	Count     int
}

func (p *MineUsteelRowParams) to_struct() C.mine_usteel_row_params_t {
	var c C.mine_usteel_row_params_t
	c.origin = p.Origin.val
	c.axis = p.Axis.val
	c.section = C.int(p.Section)
	c.width = C.double(p.Width)
	c.height = C.double(p.Height)
	c.thickness = C.double(p.Thickness)
	c.spacing = C.double(p.Spacing)
	c.count = C.int(p.Count)
	return c
}

func CreateMineUsteelRow(params MineUsteelRowParams) *Shape {
	if rejectParams(params) {
		return nil
	}
	return finish(C.create_mine_usteel_row(params.to_struct()))
}

type MineShieldRowParams struct {
	Origin      Point3
	Dir         Dir3
	Count       int
	CenterDist  float32
	BeamWidth   float32
	BeamThick   float32
	Height      float32
	MaxLegPairs int
}

func (p *MineShieldRowParams) to_struct() C.mine_shield_row_params_t {
	var c C.mine_shield_row_params_t
	c.origin = p.Origin.val
	c.dir = p.Dir.val
	c.count = C.int(p.Count)
	c.centerDist = C.double(p.CenterDist)
	c.beamWidth = C.double(p.BeamWidth)
	c.beamThick = C.double(p.BeamThick)
	c.height = C.double(p.Height)
	c.maxLegPairs = C.int(p.MaxLegPairs)
	return c
}

func CreateMineShieldRow(params MineShieldRowParams) *Shape {
	if rejectParams(params) {
		return nil
	}
	return finish(C.create_mine_shield_row(params.to_struct()))
}

// ================= C 通风设施 =================

type MineVentWallParams struct {
	Section   MineSection
	Width     float32
	Height    float32
	Thickness float32
	Center    Point3
	Axis      Dir3
}

func (p *MineVentWallParams) to_struct() C.mine_vent_wall_params_t {
	var c C.mine_vent_wall_params_t
	c.section = C.int(p.Section)
	c.width = C.double(p.Width)
	c.height = C.double(p.Height)
	c.thickness = C.double(p.Thickness)
	c.center = p.Center.val
	c.axis = p.Axis.val
	return c
}

func CreateMineVentWall(params MineVentWallParams) *Shape {
	if rejectParams(params) {
		return nil
	}
	return finish(C.create_mine_vent_wall(params.to_struct()))
}

type MineBoxWallParams struct {
	Width, Height, Thickness float32
	Center                   Point3
	Axis                     Dir3
}

func (p *MineBoxWallParams) to_struct() C.mine_box_wall_params_t {
	var c C.mine_box_wall_params_t
	c.width = C.double(p.Width)
	c.height = C.double(p.Height)
	c.thickness = C.double(p.Thickness)
	c.center = p.Center.val
	c.axis = p.Axis.val
	return c
}

func CreateMineBoxWall(params MineBoxWallParams) *Shape {
	if rejectParams(params) {
		return nil
	}
	return finish(C.create_mine_box_wall(params.to_struct()))
}

type MineVentDoorParams struct {
	Width, Height         float32
	DoorWidth, DoorHeight float32
	DoorThick, FrameWidth float32
	OpenAngleDeg          float32
	Center                Point3
	Axis                  Dir3
}

func (p *MineVentDoorParams) to_struct() C.mine_vent_door_params_t {
	var c C.mine_vent_door_params_t
	c.width = C.double(p.Width)
	c.height = C.double(p.Height)
	c.doorWidth = C.double(p.DoorWidth)
	c.doorHeight = C.double(p.DoorHeight)
	c.doorThick = C.double(p.DoorThick)
	c.frameWidth = C.double(p.FrameWidth)
	c.openAngleDeg = C.double(p.OpenAngleDeg)
	c.center = p.Center.val
	c.axis = p.Axis.val
	return c
}

func CreateMineVentDoor(params MineVentDoorParams) *Shape {
	if rejectParams(params) {
		return nil
	}
	return finish(C.create_mine_vent_door(params.to_struct()))
}

type MineVentWindowParams struct {
	Width, Height, Thickness float32
	WinWidth, WinHeight      float32
	WinSill                  float32
	Bars                     int
	Center                   Point3
	Axis                     Dir3
}

func (p *MineVentWindowParams) to_struct() C.mine_vent_window_params_t {
	var c C.mine_vent_window_params_t
	c.width = C.double(p.Width)
	c.height = C.double(p.Height)
	c.thickness = C.double(p.Thickness)
	c.winWidth = C.double(p.WinWidth)
	c.winHeight = C.double(p.WinHeight)
	c.winSill = C.double(p.WinSill)
	c.bars = C.int(p.Bars)
	c.center = p.Center.val
	c.axis = p.Axis.val
	return c
}

func CreateMineVentWindow(params MineVentWindowParams) *Shape {
	if rejectParams(params) {
		return nil
	}
	return finish(C.create_mine_vent_window(params.to_struct()))
}

type MineVentBridgeParams struct {
	Span, Width, Thickness, Apex float32
	Center                       Point3
	Axis                         Dir3
}

func (p *MineVentBridgeParams) to_struct() C.mine_vent_bridge_params_t {
	var c C.mine_vent_bridge_params_t
	c.span = C.double(p.Span)
	c.width = C.double(p.Width)
	c.thickness = C.double(p.Thickness)
	c.apex = C.double(p.Apex)
	c.center = p.Center.val
	c.axis = p.Axis.val
	return c
}

func CreateMineVentBridge(params MineVentBridgeParams) *Shape {
	if rejectParams(params) {
		return nil
	}
	return finish(C.create_mine_vent_bridge(params.to_struct()))
}

type MineVentDuctParams struct {
	Path     []Point3
	Diameter float32
}

func (p *MineVentDuctParams) to_struct() C.mine_vent_duct_params_t {
	var c C.mine_vent_duct_params_t
	c.path, c.numPath = cPoints(p.Path)
	c.diameter = C.double(p.Diameter)
	return c
}

func CreateMineVentDuct(params MineVentDuctParams) *Shape {
	if rejectParams(params) {
		return nil
	}
	cParams := params.to_struct()
	defer freePnts(unsafe.Pointer(cParams.path))
	return finish(C.create_mine_vent_duct(cParams))
}

// ================= D 防治水与地质 =================

type MineCollapsePillarParams struct {
	BottomCenter                Point3
	BottomLong, BottomShort     float32
	TopLong, TopShort           float32
	Height                      float32
}

func (p *MineCollapsePillarParams) to_struct() C.mine_collapse_pillar_params_t {
	var c C.mine_collapse_pillar_params_t
	c.bottomCenter = p.BottomCenter.val
	c.bottomLong = C.double(p.BottomLong)
	c.bottomShort = C.double(p.BottomShort)
	c.topLong = C.double(p.TopLong)
	c.topShort = C.double(p.TopShort)
	c.height = C.double(p.Height)
	return c
}

func CreateMineCollapsePillar(params MineCollapsePillarParams) *Shape {
	if rejectParams(params) {
		return nil
	}
	return finish(C.create_mine_collapse_pillar(params.to_struct()))
}

type MineWaterGateWallParams struct {
	Width, Height, Thickness     float32
	DoorWidth, DoorHeight        float32
	Center                       Point3
	Axis                         Dir3
}

func (p *MineWaterGateWallParams) to_struct() C.mine_water_gate_wall_params_t {
	var c C.mine_water_gate_wall_params_t
	c.width = C.double(p.Width)
	c.height = C.double(p.Height)
	c.thickness = C.double(p.Thickness)
	c.doorWidth = C.double(p.DoorWidth)
	c.doorHeight = C.double(p.DoorHeight)
	c.center = p.Center.val
	c.axis = p.Axis.val
	return c
}

func CreateMineWaterGateWall(params MineWaterGateWallParams) *Shape {
	if rejectParams(params) {
		return nil
	}
	return finish(C.create_mine_water_gate_wall(params.to_struct()))
}

type MineWaterGateParams struct {
	Width, Height         float32
	DoorWidth, DoorHeight float32
	DoorThick, FrameWidth float32
	Center                Point3
	Axis                  Dir3
}

func (p *MineWaterGateParams) to_struct() C.mine_water_gate_params_t {
	var c C.mine_water_gate_params_t
	c.width = C.double(p.Width)
	c.height = C.double(p.Height)
	c.doorWidth = C.double(p.DoorWidth)
	c.doorHeight = C.double(p.DoorHeight)
	c.doorThick = C.double(p.DoorThick)
	c.frameWidth = C.double(p.FrameWidth)
	c.center = p.Center.val
	c.axis = p.Axis.val
	return c
}

func CreateMineWaterGate(params MineWaterGateParams) *Shape {
	if rejectParams(params) {
		return nil
	}
	return finish(C.create_mine_water_gate(params.to_struct()))
}

type MineBoreholeLayer struct {
	From, To float32
}

type MineBoreholeParams struct {
	Collar   Point3
	Axis     Dir3
	Diameter float32
	Layers   []MineBoreholeLayer
}

func (p *MineBoreholeParams) to_struct() C.mine_borehole_params_t {
	var c C.mine_borehole_params_t
	c.collar = p.Collar.val
	c.axis = p.Axis.val
	c.diameter = C.double(p.Diameter)
	c.numLayers = C.int(len(p.Layers))
	if len(p.Layers) > 0 {
		c.layers = (*C.mine_borehole_layer_t)(C.malloc(C.size_t(len(p.Layers)) * C.sizeof_mine_borehole_layer_t))
		for i, ly := range p.Layers {
			cl := (*C.mine_borehole_layer_t)(unsafe.Pointer(uintptr(unsafe.Pointer(c.layers)) + uintptr(i)*C.sizeof_mine_borehole_layer_t))
			cl.from = C.double(ly.From)
			cl.to = C.double(ly.To)
		}
	}
	return c
}

func CreateMineBorehole(params MineBoreholeParams) *Shape {
	if rejectParams(params) {
		return nil
	}
	cParams := params.to_struct()
	defer freePnts(unsafe.Pointer(cParams.layers))
	return finish(C.create_mine_borehole(cParams))
}

// ================= E 运输系统 =================

type MineRailTrackParams struct {
	Path           []Point3 // z = 轨面标高
	Gauge          float64
	DoubleTrack    bool
	CenterDistance float64
	SleeperSpacing float64
	SleeperMax     int
}

func (p *MineRailTrackParams) to_struct() C.mine_rail_track_params_t {
	var c C.mine_rail_track_params_t
	c.path, c.numPath = cPoints(p.Path)
	c.gauge = C.double(p.Gauge)
	c.doubleTrack = C.int(boolToInt(p.DoubleTrack))
	c.centerDistance = C.double(p.CenterDistance)
	c.sleeperSpacing = C.double(p.SleeperSpacing)
	c.sleeperMax = C.int(p.SleeperMax)
	return c
}

func CreateMineRailTrack(params MineRailTrackParams) *Shape {
	if rejectParams(params) {
		return nil
	}
	cParams := params.to_struct()
	defer freePnts(unsafe.Pointer(cParams.path))
	return finish(C.create_mine_rail_track(cParams))
}

type MineTurnoutParams struct {
	Origin Point3
	Axis   Dir3
	Gauge  float64
	FrogNo float64
	Length float64
}

func (p *MineTurnoutParams) to_struct() C.mine_turnout_params_t {
	var c C.mine_turnout_params_t
	c.origin = p.Origin.val
	c.axis = p.Axis.val
	c.gauge = C.double(p.Gauge)
	c.frogNo = C.double(p.FrogNo)
	c.length = C.double(p.Length)
	return c
}

func CreateMineTurnout(params MineTurnoutParams) *Shape {
	if rejectParams(params) {
		return nil
	}
	return finish(C.create_mine_turnout(params.to_struct()))
}

type MineBeltParams struct {
	Path        []Point3 // z = 底板标高
	BeltWidth   float32
	FrameHeight float32
}

func (p *MineBeltParams) to_struct() C.mine_belt_params_t {
	var c C.mine_belt_params_t
	c.path, c.numPath = cPoints(p.Path)
	c.beltWidth = C.double(p.BeltWidth)
	c.frameHeight = C.double(p.FrameHeight)
	return c
}

func CreateMineBelt(params MineBeltParams) *Shape {
	if rejectParams(params) {
		return nil
	}
	cParams := params.to_struct()
	defer freePnts(unsafe.Pointer(cParams.path))
	return finish(C.create_mine_belt(cParams))
}

type MineScraperParams struct {
	Path                []Point3
	PanWidth, PanHeight float32
}

func (p *MineScraperParams) to_struct() C.mine_scraper_params_t {
	var c C.mine_scraper_params_t
	c.path, c.numPath = cPoints(p.Path)
	c.panWidth = C.double(p.PanWidth)
	c.panHeight = C.double(p.PanHeight)
	return c
}

func CreateMineScraper(params MineScraperParams) *Shape {
	if rejectParams(params) {
		return nil
	}
	cParams := params.to_struct()
	defer freePnts(unsafe.Pointer(cParams.path))
	return finish(C.create_mine_scraper(cParams))
}

type MineMonorailParams struct {
	Path                    []Point3
	RailHeight, FlangeWidth float32
}

func (p *MineMonorailParams) to_struct() C.mine_monorail_params_t {
	var c C.mine_monorail_params_t
	c.path, c.numPath = cPoints(p.Path)
	c.railHeight = C.double(p.RailHeight)
	c.flangeWidth = C.double(p.FlangeWidth)
	return c
}

func CreateMineMonorail(params MineMonorailParams) *Shape {
	if rejectParams(params) {
		return nil
	}
	cParams := params.to_struct()
	defer freePnts(unsafe.Pointer(cParams.path))
	return finish(C.create_mine_monorail(cParams))
}

// ================= F 管线系统 =================

type MinePipeRunParams struct {
	Path           []Point3
	Diameter       float32
	BracketSpacing float32
}

func (p *MinePipeRunParams) to_struct() C.mine_pipe_run_params_t {
	var c C.mine_pipe_run_params_t
	c.path, c.numPath = cPoints(p.Path)
	c.diameter = C.double(p.Diameter)
	c.bracketSpacing = C.double(p.BracketSpacing)
	return c
}

func CreateMinePipeRun(params MinePipeRunParams) *Shape {
	if rejectParams(params) {
		return nil
	}
	cParams := params.to_struct()
	defer freePnts(unsafe.Pointer(cParams.path))
	return finish(C.create_mine_pipe_run(cParams))
}

type MineCableRunParams struct {
	Path     []Point3
	Diameter float32
	Lines    int
}

func (p *MineCableRunParams) to_struct() C.mine_cable_run_params_t {
	var c C.mine_cable_run_params_t
	c.path, c.numPath = cPoints(p.Path)
	c.diameter = C.double(p.Diameter)
	c.lines = C.int(p.Lines)
	return c
}

func CreateMineCableRun(params MineCableRunParams) *Shape {
	if rejectParams(params) {
		return nil
	}
	cParams := params.to_struct()
	defer freePnts(unsafe.Pointer(cParams.path))
	return finish(C.create_mine_cable_run(cParams))
}

// ================= 喷浆/砌碹衬砌 (断面枚举式) =================

type MineShotcreteParams struct {
	Origin    Point3
	Axis      Dir3
	Section   MineSection
	Width     float32
	Height    float32
	Thickness float32
	Length    float32
}

func (p *MineShotcreteParams) to_struct() C.mine_shotcrete_params_t {
	var c C.mine_shotcrete_params_t
	c.origin = p.Origin.val
	c.axis = p.Axis.val
	c.section = C.int(p.Section)
	c.width = C.double(p.Width)
	c.height = C.double(p.Height)
	c.thickness = C.double(p.Thickness)
	c.length = C.double(p.Length)
	return c
}

func CreateMineShotcrete(params MineShotcreteParams) *Shape {
	if rejectParams(params) {
		return nil
	}
	return finish(C.create_mine_shotcrete(params.to_struct()))
}

// ================= 补齐图元 (水沟/交岔点/测风站/钢带/三通) =================

type MineTrenchParams struct {
	Path       []Point3
	Section    MineSection
	Width      float32
	Height     float32
	SideOffset float32
}

func (p *MineTrenchParams) to_struct() C.mine_trench_params_t {
	var c C.mine_trench_params_t
	c.path, c.numPath = cPoints(p.Path)
	c.section = C.int(p.Section)
	c.width = C.double(p.Width)
	c.height = C.double(p.Height)
	c.sideOffset = C.double(p.SideOffset)
	return c
}

func CreateMineTrench(params MineTrenchParams) *Shape {
	if rejectParams(params) {
		return nil
	}
	cParams := params.to_struct()
	defer freePnts(unsafe.Pointer(cParams.path))
	return finish(C.create_mine_trench(cParams))
}

type MineJunctionParams struct {
	Center           Point3
	MainAxis         Dir3
	BranchAngleDeg   float32
	Section          MineSection
	Width, Height    float32
	MainLength       float32
	BranchLength     float32
	ReinforceLength  float32
}

func (p *MineJunctionParams) to_struct() C.mine_junction_params_t {
	var c C.mine_junction_params_t
	c.center = p.Center.val
	c.mainAxis = p.MainAxis.val
	c.branchAngleDeg = C.double(p.BranchAngleDeg)
	c.section = C.int(p.Section)
	c.width = C.double(p.Width)
	c.height = C.double(p.Height)
	c.mainLength = C.double(p.MainLength)
	c.branchLength = C.double(p.BranchLength)
	c.reinforceLength = C.double(p.ReinforceLength)
	return c
}

func CreateMineJunction(params MineJunctionParams) *Shape {
	if rejectParams(params) {
		return nil
	}
	return finish(C.create_mine_junction(params.to_struct()))
}

type MineVentStationParams struct {
	Section   MineSection
	Width     float32
	Height    float32
	PostWidth float32
	Depth     float32
	Center    Point3
	Axis      Dir3
}

func (p *MineVentStationParams) to_struct() C.mine_vent_station_params_t {
	var c C.mine_vent_station_params_t
	c.section = C.int(p.Section)
	c.width = C.double(p.Width)
	c.height = C.double(p.Height)
	c.postWidth = C.double(p.PostWidth)
	c.depth = C.double(p.Depth)
	c.center = p.Center.val
	c.axis = p.Axis.val
	return c
}

func CreateMineVentStation(params MineVentStationParams) *Shape {
	if rejectParams(params) {
		return nil
	}
	return finish(C.create_mine_vent_station(params.to_struct()))
}

type MineSteelBandParams struct {
	Length, Width, Thickness float32
	HoleCount                int
	HoleDia, HoleEdge        float32
}

func (p *MineSteelBandParams) to_struct() C.mine_steel_band_params_t {
	var c C.mine_steel_band_params_t
	c.length = C.double(p.Length)
	c.width = C.double(p.Width)
	c.thickness = C.double(p.Thickness)
	c.holeCount = C.int(p.HoleCount)
	c.holeDia = C.double(p.HoleDia)
	c.holeEdge = C.double(p.HoleEdge)
	return c
}

func CreateMineSteelBand(params MineSteelBandParams) *Shape {
	if rejectParams(params) {
		return nil
	}
	return finish(C.create_mine_steel_band(params.to_struct()))
}

type MinePipeFittingParams struct {
	Center         Point3
	MainAxis       Dir3
	BranchAngleDeg float32
	MainLength     float32
	BranchLength   float32
	Diameter       float32
}

func (p *MinePipeFittingParams) to_struct() C.mine_pipe_fitting_params_t {
	var c C.mine_pipe_fitting_params_t
	c.center = p.Center.val
	c.mainAxis = p.MainAxis.val
	c.branchAngleDeg = C.double(p.BranchAngleDeg)
	c.mainLength = C.double(p.MainLength)
	c.branchLength = C.double(p.BranchLength)
	c.diameter = C.double(p.Diameter)
	return c
}

func CreateMinePipeFitting(params MinePipeFittingParams) *Shape {
	if rejectParams(params) {
		return nil
	}
	return finish(C.create_mine_pipe_fitting(params.to_struct()))
}

// ================= 栅栏/栅栏门 =================

type MineFenceParams struct {
	Width, Height       float32
	PostWidth, BarWidth float32
	Thickness           float32
	Bars                int
	Center              Point3
	Axis                Dir3
}

func (p *MineFenceParams) to_struct() C.mine_fence_params_t {
	var c C.mine_fence_params_t
	c.width = C.double(p.Width)
	c.height = C.double(p.Height)
	c.postWidth = C.double(p.PostWidth)
	c.barWidth = C.double(p.BarWidth)
	c.thickness = C.double(p.Thickness)
	c.bars = C.int(p.Bars)
	c.center = p.Center.val
	c.axis = p.Axis.val
	return c
}

func CreateMineFence(params MineFenceParams) *Shape {
	if rejectParams(params) {
		return nil
	}
	return finish(C.create_mine_fence(params.to_struct()))
}
