package topo

/*
#include <stdlib.h>
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

type SphereParams struct {
	Radius float32
}

func (p *SphereParams) to_struct() C.sphere_params_t {
	var c C.sphere_params_t
	c.radius = C.double(p.Radius)
	return c
}

func CreateSphere(params SphereParams) *Shape {
	shp := C.create_sphere(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateSphereWithPlace(params SphereParams, center Point3) *Shape {
	shp := C.create_sphere_with_place(params.to_struct(), center.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type RotationalEllipsoidParams struct {
	PolarRadius      float32
	EquatorialRadius float32
	Height           float32
}

func (p *RotationalEllipsoidParams) to_struct() C.rotational_ellipsoid_params_t {
	var c C.rotational_ellipsoid_params_t
	c.polarRadius = C.double(p.PolarRadius)
	c.equatorialRadius = C.double(p.EquatorialRadius)
	c.height = C.double(p.Height)
	return c
}

func CreateRotationalEllipsoid(params RotationalEllipsoidParams) *Shape {
	shp := C.create_rotational_ellipsoid(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateRotationalEllipsoidWithPlace(params RotationalEllipsoidParams, center Point3, xDir Dir3) *Shape {
	shp := C.create_rotational_ellipsoid_with_place(params.to_struct(), center.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type CuboidParams struct {
	Length float32
	Width  float32
	Height float32
}

func (p *CuboidParams) to_struct() C.cuboid_params_t {
	var c C.cuboid_params_t
	c.length = C.double(p.Length)
	c.width = C.double(p.Width)
	c.height = C.double(p.Height)
	return c
}

func CreateCuboid(params CuboidParams) *Shape {
	shp := C.create_cuboid(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateCuboidWithPlace(params CuboidParams, center Point3, xDir Dir3, zDir Dir3) *Shape {
	shp := C.create_cuboid_with_place(params.to_struct(), center.val, xDir.val, zDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type DiamondFrustumParams struct {
	TopDiag1    float32
	TopDiag2    float32
	BottomDiag1 float32
	BottomDiag2 float32
	Height      float32
}

func (p *DiamondFrustumParams) to_struct() C.diamond_frustum_t {
	var c C.diamond_frustum_t
	c.topDiag1 = C.double(p.TopDiag1)
	c.topDiag2 = C.double(p.TopDiag2)
	c.bottomDiag1 = C.double(p.BottomDiag1)
	c.bottomDiag2 = C.double(p.BottomDiag2)
	c.height = C.double(p.Height)
	return c
}

func CreateDiamondFrustum(params DiamondFrustumParams) *Shape {
	shp := C.create_diamond_frustum(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateDiamondFrustumWithPlace(params DiamondFrustumParams, position Point3, normal Dir3, xDir Dir3) *Shape {
	shp := C.create_diamond_frustum_with_place(params.to_struct(), position.val, normal.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type OffsetRectangularTableParams struct {
	TopLength    float32
	TopWidth     float32
	BottomLength float32
	BottomWidth  float32
	Height       float32
	XOffset      float32
	YOffset      float32
}

func (p *OffsetRectangularTableParams) to_struct() C.offset_rectangular_table_params_t {
	var c C.offset_rectangular_table_params_t
	c.topLength = C.double(p.TopLength)
	c.topWidth = C.double(p.TopWidth)
	c.bottomLength = C.double(p.BottomLength)
	c.bottomWidth = C.double(p.BottomWidth)
	c.height = C.double(p.Height)
	c.xOffset = C.double(p.XOffset)
	c.yOffset = C.double(p.YOffset)
	return c
}

func CreateOffsetRectangularTable(params OffsetRectangularTableParams) *Shape {
	shp := C.create_offset_rectangular_table(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateOffsetRectangularTableWithPlace(params OffsetRectangularTableParams, position Point3, normal Dir3, xDir Dir3) *Shape {
	shp := C.create_offset_rectangular_table_with_place(params.to_struct(), position.val, normal.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type RingParams struct {
	RingRadius float32
	TubeRadius float32
	Angle      float32
}

func (p *RingParams) to_struct() C.ring_params_t {
	var c C.ring_params_t
	c.ringRadius = C.double(p.RingRadius)
	c.tubeRadius = C.double(p.TubeRadius)
	c.angle = C.double(p.Angle)
	return c
}

func CreateRing(params RingParams) *Shape {
	shp := C.create_ring(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateRingWithPlace(params RingParams, center Point3, normal Dir3, xDir Dir3) *Shape {
	shp := C.create_ring_with_place(params.to_struct(), center.val, normal.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type RectangularRingParams struct {
	TubeRadius   float32
	FilletRadius float32
	Length       float32
	Width        float32
}

func (p *RectangularRingParams) to_struct() C.rectangular_ring_params_t {
	var c C.rectangular_ring_params_t
	c.tubeRadius = C.double(p.TubeRadius)
	c.filletRadius = C.double(p.FilletRadius)
	c.length = C.double(p.Length)
	c.width = C.double(p.Width)
	return c
}

func CreateRectangularRing(params RectangularRingParams) *Shape {
	shp := C.create_rectangular_ring(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateRectangularRingWithPlace(params RectangularRingParams, center Point3, normal Dir3, xDir Dir3) *Shape {
	shp := C.create_rectangular_ring_with_place(params.to_struct(), center.val, normal.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type EllipticRingParams struct {
	TubeRadius  float32
	MajorRadius float32
	MinorRadius float32
}

func (p *EllipticRingParams) to_struct() C.elliptic_ring_params_t {
	var c C.elliptic_ring_params_t
	c.tubeRadius = C.double(p.TubeRadius)
	c.majorRadius = C.double(p.MajorRadius)
	c.minorRadius = C.double(p.MinorRadius)
	return c
}

func CreateEllipticRing(params EllipticRingParams) *Shape {
	shp := C.create_elliptic_ring(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateEllipticRingWithPlace(params EllipticRingParams, center Point3, normal Dir3, xDir Dir3) *Shape {
	shp := C.create_elliptic_ring_with_place(params.to_struct(), center.val, normal.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type CircularGasketParams struct {
	OuterRadius float32
	InnerRadius float32
	Height      float32
	Angle       float32
}

func (p *CircularGasketParams) to_struct() C.circular_gasket_params_t {
	var c C.circular_gasket_params_t
	c.outerRadius = C.double(p.OuterRadius)
	c.innerRadius = C.double(p.InnerRadius)
	c.height = C.double(p.Height)
	c.angle = C.double(p.Angle)
	return c
}

func CreateCircularGasket(params CircularGasketParams) *Shape {
	shp := C.create_circular_gasket(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateCircularGasketWithPlace(params CircularGasketParams, center Point3, normal Dir3, xDir Dir3) *Shape {
	shp := C.create_circular_gasket_with_place(params.to_struct(), center.val, normal.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type TableGasketParams struct {
	TopRadius   float32
	OuterRadius float32
	InnerRadius float32
	Height      float32
	Angle       float32
}

func (p *TableGasketParams) to_struct() C.table_gasket_params_t {
	var c C.table_gasket_params_t
	c.topRadius = C.double(p.TopRadius)
	c.outerRadius = C.double(p.OuterRadius)
	c.innerRadius = C.double(p.InnerRadius)
	c.height = C.double(p.Height)
	c.angle = C.double(p.Angle)
	return c
}

func CreateTableGasket(params TableGasketParams) *Shape {
	shp := C.create_table_gasket(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateTableGasketWithPlace(params TableGasketParams, center Point3, normal Dir3, xDir Dir3) *Shape {
	shp := C.create_table_gasket_with_place(params.to_struct(), center.val, normal.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type SquareGasketParams struct {
	OuterLength float32
	OuterWidth  float32
	InnerLength float32
	InnerWidth  float32
	Height      float32
	CornerType  int32
	CornerParam float32
}

func (p *SquareGasketParams) to_struct() C.square_gasket_params_t {
	var c C.square_gasket_params_t
	c.outerLength = C.double(p.OuterLength)
	c.outerWidth = C.double(p.OuterWidth)
	c.innerLength = C.double(p.InnerLength)
	c.innerWidth = C.double(p.InnerWidth)
	c.height = C.double(p.Height)
	c.cornerType = C.int(p.CornerType)
	c.cornerParam = C.double(p.CornerParam)
	return c
}

func CreateSquareGasket(params SquareGasketParams) *Shape {
	shp := C.create_square_gasket(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateSquareGasketWithPlace(params SquareGasketParams, center Point3, normal Dir3, xDir Dir3) *Shape {
	shp := C.create_square_gasket_with_place(params.to_struct(), center.val, normal.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type PorcelainBushingParams struct {
	Height           float32
	Radius           float32
	BigSkirtRadius   float32
	SmallSkirtRadius float32
	Count            int32
}

func (p *PorcelainBushingParams) to_struct() C.porcelain_bushing_params_t {
	var c C.porcelain_bushing_params_t
	c.height = C.double(p.Height)
	c.radius = C.double(p.Radius)
	c.bigSkirtRadius = C.double(p.BigSkirtRadius)
	c.smallSkirtRadius = C.double(p.SmallSkirtRadius)
	c.count = C.int(p.Count)
	return c
}

func CreatePorcelainBushing(params PorcelainBushingParams) *Shape {
	shp := C.create_porcelain_bushing(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreatePorcelainBushingWithPlace(params PorcelainBushingParams, basePoint Point3, axisDir Dir3) *Shape {
	shp := C.create_porcelain_bushing_with_place(params.to_struct(), basePoint.val, axisDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type ConePorcelainBushingParams struct {
	Height             float32
	BottomRadius       float32
	TopRadius          float32
	BottomSkirtRadius1 float32
	BottomSkirtRadius2 float32
	TopSkirtRadius1    float32
	TopSkirtRadius2    float32
	Count              int32
}

func (p *ConePorcelainBushingParams) to_struct() C.cone_porcelain_bushing_params_t {
	var c C.cone_porcelain_bushing_params_t
	c.height = C.double(p.Height)
	c.bottomRadius = C.double(p.BottomRadius)
	c.topRadius = C.double(p.TopRadius)
	c.bottomSkirtRadius1 = C.double(p.BottomSkirtRadius1)
	c.bottomSkirtRadius2 = C.double(p.BottomSkirtRadius2)
	c.topSkirtRadius1 = C.double(p.TopSkirtRadius1)
	c.topSkirtRadius2 = C.double(p.TopSkirtRadius2)
	c.count = C.int(p.Count)
	return c
}

func CreateConePorcelainBushing(params ConePorcelainBushingParams) *Shape {
	shp := C.create_cone_porcelain_bushing(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateConePorcelainBushingWithPlace(params ConePorcelainBushingParams, basePoint Point3, axisDir Dir3) *Shape {
	shp := C.create_cone_porcelain_bushing_with_place(params.to_struct(), basePoint.val, axisDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type VTypeInsulatorParams struct {
	FrontSpacing     float32
	BackSpacing      float32
	InsulatorCount   int32
	Height           float32
	Radius           float32
	BigSkirtRadius   float32
	SmallSkirtRadius float32
	FrontLength      float32
	BackLength       float32
	SplitCount       int32
}

func (p *VTypeInsulatorParams) to_struct() C.vtype_insulator_params_t {
	var c C.vtype_insulator_params_t
	c.frontSpacing = C.double(p.FrontSpacing)
	c.backSpacing = C.double(p.BackSpacing)
	c.insulatorCount = C.int(p.InsulatorCount)
	c.height = C.double(p.Height)
	c.radius = C.double(p.Radius)
	c.bigSkirtRadius = C.double(p.BigSkirtRadius)
	c.smallSkirtRadius = C.double(p.SmallSkirtRadius)
	c.frontLength = C.double(p.FrontLength)
	c.backLength = C.double(p.BackLength)
	c.splitCount = C.int(p.SplitCount)
	return c
}

func CreateVTypeInsulator(params VTypeInsulatorParams) *Shape {
	shp := C.create_vtype_insulator(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateVTypeInsulatorWithPlace(params VTypeInsulatorParams, position Point3, direction Dir3, upDirection Dir3) *Shape {
	shp := C.create_vtype_insulator_with_place(params.to_struct(), position.val, direction.val, upDirection.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type TerminalBlockParams struct {
	Length        float32
	Width         float32
	Thickness     float32
	ChamferLength float32
	ColumnSpacing float32
	RowSpacing    float32
	HoleRadius    float32
	ColumnCount   int32
	RowCount      int32
	BottomOffset  float32
	Phase         byte
}

func (p *TerminalBlockParams) to_struct() C.terminal_block_params_t {
	var c C.terminal_block_params_t
	c.length = C.double(p.Length)
	c.width = C.double(p.Width)
	c.thickness = C.double(p.Thickness)
	c.chamferLength = C.double(p.ChamferLength)
	c.columnSpacing = C.double(p.ColumnSpacing)
	c.rowSpacing = C.double(p.RowSpacing)
	c.holeRadius = C.double(p.HoleRadius)
	c.columnCount = C.int(p.ColumnCount)
	c.rowCount = C.int(p.RowCount)
	c.bottomOffset = C.double(p.BottomOffset)
	c.phase = C.char(p.Phase)
	return c
}

func CreateTerminalBlock(params TerminalBlockParams) *Shape {
	shp := C.create_terminal_block(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateTerminalBlockWithPlace(params TerminalBlockParams, position Point3, lengthDir Dir3, widthDir Dir3) *Shape {
	shp := C.create_terminal_block_with_place(params.to_struct(), position.val, lengthDir.val, widthDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type RectangularHolePlateParams struct {
	Length        float32
	Width         float32
	Thickness     float32
	ColumnSpacing float32
	RowSpacing    float32
	ColumnCount   int32
	RowCount      int32
	HasMiddleHole bool
	HoleDiameter  float32
}

func (p *RectangularHolePlateParams) to_struct() C.rectangular_hole_plate_params_t {
	var c C.rectangular_hole_plate_params_t
	c.length = C.double(p.Length)
	c.width = C.double(p.Width)
	c.thickness = C.double(p.Thickness)
	c.columnSpacing = C.double(p.ColumnSpacing)
	c.rowSpacing = C.double(p.RowSpacing)
	c.columnCount = C.int(p.ColumnCount)
	c.rowCount = C.int(p.RowCount)
	c.hasMiddleHole = C.bool(p.HasMiddleHole)
	c.holeDiameter = C.double(p.HoleDiameter)
	return c
}

func CreateRectangularFixedPlate(params RectangularHolePlateParams) *Shape {
	shp := C.create_rectangular_fixed_plate(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateRectangularFixedPlateWithPlace(params RectangularHolePlateParams, position Point3, lengthDir Dir3, widthDir Dir3) *Shape {
	shp := C.create_rectangular_fixed_plate_with_place(params.to_struct(), position.val, lengthDir.val, widthDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type CircularFixedPlateParams struct {
	Length        float32
	Width         float32
	Thickness     float32
	RingRadius    float32
	HoleCount     int32
	HasMiddleHole bool
	HoleDiameter  float32
}

func (p *CircularFixedPlateParams) to_struct() C.circular_fixed_plate_params_t {
	var c C.circular_fixed_plate_params_t
	c.length = C.double(p.Length)
	c.width = C.double(p.Width)
	c.thickness = C.double(p.Thickness)
	c.ringRadius = C.double(p.RingRadius)
	c.holeCount = C.int(p.HoleCount)
	c.hasMiddleHole = C.bool(p.HasMiddleHole)
	c.holeDiameter = C.double(p.HoleDiameter)
	return c
}

func CreateCircularFixedPlate(params CircularFixedPlateParams) *Shape {
	shp := C.create_circular_fixed_plate(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateCircularFixedPlateWithPlace(params CircularFixedPlateParams, position Point3, lengthDir Dir3, widthDir Dir3) *Shape {
	shp := C.create_circular_fixed_plate_with_place(params.to_struct(), position.val, lengthDir.val, widthDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type WireParams struct {
	StartPoint Point3
	EndPoint   Point3
	StartDir   Dir3
	EndDir     Dir3
	Sag        float32
	Diameter   float32
	FitPoints  []Point3
}

func (p *WireParams) to_struct() C.wire_params_t {
	var c C.wire_params_t
	c.startPoint = p.StartPoint.val
	c.endPoint = p.EndPoint.val
	c.startDir = p.StartDir.val
	c.endDir = p.EndDir.val
	c.sag = C.double(p.Sag)
	c.diameter = C.double(p.Diameter)
	c.numFitPoints = C.int(len(p.FitPoints))

	if len(p.FitPoints) > 0 {
		c.fitPoints = (*C.pnt3d_t)(C.malloc(C.size_t(len(p.FitPoints)) * C.sizeof_pnt3d_t))
		for i, pt := range p.FitPoints {
			*(*C.pnt3d_t)(unsafe.Pointer(uintptr(unsafe.Pointer(c.fitPoints)) + uintptr(i)*C.sizeof_pnt3d_t)) = pt.val
		}
	}

	return c
}

func freeWireParams(c C.wire_params_t) {
	if c.fitPoints != nil {
		C.free(unsafe.Pointer(c.fitPoints))
	}
}

func CreateWire(params WireParams) *Shape {
	cParams := params.to_struct()
	defer freeWireParams(cParams)

	shp := C.create_wire(cParams)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateWireWithPlace(params WireParams, position Point3, direction Dir3, upDirection Dir3) *Shape {
	cParams := params.to_struct()
	defer freeWireParams(cParams)

	shp := C.create_wire_with_place(cParams, position.val, direction.val, upDirection.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type CableParams struct {
	StartPoint       Point3
	EndPoint         Point3
	InflectionPoints []Point3
	Radii            []float32
	Diameter         float32
}

func (p *CableParams) to_struct() C.cable_params_t {
	var c C.cable_params_t
	c.startPoint = p.StartPoint.val
	c.endPoint = p.EndPoint.val
	c.numInflectionPoints = C.int(len(p.InflectionPoints))
	c.numRadii = C.int(len(p.Radii))
	c.diameter = C.double(p.Diameter)

	if len(p.InflectionPoints) > 0 {
		c.inflectionPoints = (*C.pnt3d_t)(C.malloc(C.size_t(len(p.InflectionPoints)) * C.sizeof_pnt3d_t))
		for i, pt := range p.InflectionPoints {
			*(*C.pnt3d_t)(unsafe.Pointer(uintptr(unsafe.Pointer(c.inflectionPoints)) + uintptr(i)*C.sizeof_pnt3d_t)) = pt.val
		}
	}

	if len(p.Radii) > 0 {
		c.radii = (*C.double)(C.malloc(C.size_t(len(p.Radii)) * C.sizeof_double))
		for i, r := range p.Radii {
			*(*C.double)(unsafe.Pointer(uintptr(unsafe.Pointer(c.radii)) + uintptr(i)*C.sizeof_double)) = C.double(r)
		}
	}

	return c
}

func freeCableParams(c C.cable_params_t) {
	if c.inflectionPoints != nil {
		C.free(unsafe.Pointer(c.inflectionPoints))
	}
	if c.radii != nil {
		C.free(unsafe.Pointer(c.radii))
	}
}

func CreateCable(params CableParams) *Shape {
	cParams := params.to_struct()
	defer freeCableParams(cParams)

	shp := C.create_cable(cParams)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateCableWithPlace(params CableParams, position Point3, direction Dir3, upDirection Dir3) *Shape {
	cParams := params.to_struct()
	defer freeCableParams(cParams)

	shp := C.create_cable_with_place(cParams, position.val, direction.val, upDirection.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type CurveType int

const (
	CurveTypeLine   CurveType = 0
	CurveTypeArc    CurveType = 1
	CurveTypeSpline CurveType = 2
)

type CurveSegment struct {
	ControlPoints []Point3
}

type CurveCableParams struct {
	Segments   []CurveSegment
	CurveTypes []CurveType
	Diameter   float32
}

func (p *CurveCableParams) to_struct() C.curve_cable_params_t {
	var c C.curve_cable_params_t
	c.numSegments = C.int(len(p.Segments))
	c.diameter = C.double(p.Diameter)

	if len(p.Segments) > 0 {
		// Allocate memory for segments
		c.segments = (*C.curve_segment_t)(C.malloc(C.size_t(len(p.Segments)) * C.sizeof_curve_segment_t))
		c.curveTypes = (*C.curve_type_t)(C.malloc(C.size_t(len(p.CurveTypes)) * C.sizeof_curve_type_t))

		for i, seg := range p.Segments {
			// Set curve type
			*(*C.curve_type_t)(unsafe.Pointer(uintptr(unsafe.Pointer(c.curveTypes)) + uintptr(i)*C.sizeof_curve_type_t)) =
				C.curve_type_t(p.CurveTypes[i])

			// Set segment data
			segmentPtr := (*C.curve_segment_t)(unsafe.Pointer(uintptr(unsafe.Pointer(c.segments)) + uintptr(i)*C.sizeof_curve_segment_t))
			segmentPtr.numPoints = C.int(len(seg.ControlPoints))

			if len(seg.ControlPoints) > 0 {
				segmentPtr.controlPoints = (*C.pnt3d_t)(C.malloc(C.size_t(len(seg.ControlPoints)) * C.sizeof_pnt3d_t))
				for j, pt := range seg.ControlPoints {
					*(*C.pnt3d_t)(unsafe.Pointer(uintptr(unsafe.Pointer(segmentPtr.controlPoints)) + uintptr(j)*C.sizeof_pnt3d_t)) = pt.val
				}
			}
		}
	}

	return c
}

func freeCurveCableParams(c C.curve_cable_params_t) {
	if c.segments != nil {
		for i := 0; i < int(c.numSegments); i++ {
			seg := (*C.curve_segment_t)(unsafe.Pointer(uintptr(unsafe.Pointer(c.segments)) + uintptr(i)*C.sizeof_curve_segment_t))
			if seg.controlPoints != nil {
				C.free(unsafe.Pointer(seg.controlPoints))
			}
		}
		C.free(unsafe.Pointer(c.segments))
	}
	if c.curveTypes != nil {
		C.free(unsafe.Pointer(c.curveTypes))
	}
}

func CreateCurveCable(params CurveCableParams) *Shape {
	cParams := params.to_struct()
	defer freeCurveCableParams(cParams)

	shp := C.create_curve_cable(cParams)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateCurveCableWithPlace(params CurveCableParams, position Point3, direction Dir3, upDirection Dir3) *Shape {
	cParams := params.to_struct()
	defer freeCurveCableParams(cParams)

	shp := C.create_curve_cable_with_place(cParams, position.val, direction.val, upDirection.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type EquilateralAngleSteelParams struct {
	L      float32
	X      float32
	Length float32
}

func (p *EquilateralAngleSteelParams) to_struct() C.equilateral_angle_steel_params_t {
	var c C.equilateral_angle_steel_params_t
	c.L = C.double(p.L)
	c.X = C.double(p.X)
	c.length = C.double(p.Length)
	return c
}

func CreateEquilateralAngleSteel(params EquilateralAngleSteelParams) *Shape {
	shp := C.create_equilateral_angle_steel(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateEquilateralAngleSteelWithPlace(params EquilateralAngleSteelParams, position Point3, xDir Dir3, yDir Dir3) *Shape {
	shp := C.create_equilateral_angle_steel_with_place(params.to_struct(), position.val, xDir.val, yDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type ScaleneAngleSteelParams struct {
	L1     float32
	L2     float32
	X      float32
	Length float32
}

func (p *ScaleneAngleSteelParams) to_struct() C.scalene_angle_steel_params_t {
	var c C.scalene_angle_steel_params_t
	c.L1 = C.double(p.L1)
	c.L2 = C.double(p.L2)
	c.X = C.double(p.X)
	c.length = C.double(p.Length)
	return c
}

func CreateScaleneAngleSteel(params ScaleneAngleSteelParams) *Shape {
	shp := C.create_scalene_angle_steel(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateScaleneAngleSteelWithPlace(params ScaleneAngleSteelParams, position Point3, xDir Dir3, longEdgeDir Dir3) *Shape {
	shp := C.create_scalene_angle_steel_with_place(params.to_struct(), position.val, xDir.val, longEdgeDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type IBeamParams struct {
	Height          float32
	FlangeWidth     float32
	WebThickness    float32
	FlangeThickness float32
	Radius          float32
	Length          float32
}

func (p *IBeamParams) to_struct() C.ibeam_params_t {
	var c C.ibeam_params_t
	c.height = C.double(p.Height)
	c.flangeWidth = C.double(p.FlangeWidth)
	c.webThickness = C.double(p.WebThickness)
	c.flangeThickness = C.double(p.FlangeThickness)
	c.radius = C.double(p.Radius)
	c.length = C.double(p.Length)
	return c
}

func CreateIBeam(params IBeamParams) *Shape {
	shp := C.create_ibeam(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateIBeamWithPlace(params IBeamParams, position Point3, xDir Dir3, zDir Dir3) *Shape {
	shp := C.create_ibeam_with_place(params.to_struct(), position.val, xDir.val, zDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type LightIBeamParams struct {
	Height          float32
	FlangeWidth     float32
	WebThickness    float32
	FlangeThickness float32
	Radius          float32
	Length          float32
	FlangeSlope     float32
}

func (p *LightIBeamParams) to_struct() C.light_ibeam_params_t {
	var c C.light_ibeam_params_t
	c.height = C.double(p.Height)
	c.flangeWidth = C.double(p.FlangeWidth)
	c.webThickness = C.double(p.WebThickness)
	c.flangeThickness = C.double(p.FlangeThickness)
	c.radius = C.double(p.Radius)
	c.length = C.double(p.Length)
	c.flangeSlope = C.double(p.FlangeSlope)
	return c
}

func CreateLightIBeam(params LightIBeamParams) *Shape {
	shp := C.create_light_ibeam(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateLightIBeamWithPlace(params LightIBeamParams, position Point3, xDir Dir3, zDir Dir3) *Shape {
	shp := C.create_light_ibeam_with_place(params.to_struct(), position.val, xDir.val, zDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type HBeamParams struct {
	Height          float32
	FlangeWidth     float32
	WebThickness    float32
	FlangeThickness float32
	Radius          float32
	Length          float32
}

func (p *HBeamParams) to_struct() C.hbeam_params_t {
	var c C.hbeam_params_t
	c.height = C.double(p.Height)
	c.flangeWidth = C.double(p.FlangeWidth)
	c.webThickness = C.double(p.WebThickness)
	c.flangeThickness = C.double(p.FlangeThickness)
	c.radius = C.double(p.Radius)
	c.length = C.double(p.Length)
	return c
}

func CreateHBeam(params HBeamParams) *Shape {
	shp := C.create_hbeam(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateHBeamWithPlace(params HBeamParams, position Point3, xDir Dir3, zDir Dir3) *Shape {
	shp := C.create_hbeam_with_place(params.to_struct(), position.val, xDir.val, zDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type BeamChannelParams struct {
	Height          float32
	FlangeWidth     float32
	WebThickness    float32
	FlangeThickness float32
	Radius          float32
	Length          float32
}

func (p *BeamChannelParams) to_struct() C.beam_channel_params_t {
	var c C.beam_channel_params_t
	c.height = C.double(p.Height)
	c.flangeWidth = C.double(p.FlangeWidth)
	c.webThickness = C.double(p.WebThickness)
	c.flangeThickness = C.double(p.FlangeThickness)
	c.radius = C.double(p.Radius)
	c.length = C.double(p.Length)
	return c
}

func CreateBeamChannel(params BeamChannelParams) *Shape {
	shp := C.create_beam_channel(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateBeamChannelWithPlace(params BeamChannelParams, position Point3, xDir Dir3, zDir Dir3) *Shape {
	shp := C.create_beam_channel_with_place(params.to_struct(), position.val, xDir.val, zDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type LightBeamChannelParams struct {
	Height          float32
	FlangeWidth     float32
	WebThickness    float32
	FlangeThickness float32
	Radius          float32
	Length          float32
	FlangeSlope     float32
}

func (p *LightBeamChannelParams) to_struct() C.light_beam_channel_params_t {
	var c C.light_beam_channel_params_t
	c.height = C.double(p.Height)
	c.flangeWidth = C.double(p.FlangeWidth)
	c.webThickness = C.double(p.WebThickness)
	c.flangeThickness = C.double(p.FlangeThickness)
	c.radius = C.double(p.Radius)
	c.length = C.double(p.Length)
	c.flangeSlope = C.double(p.FlangeSlope)
	return c
}

func CreateLightBeamChannel(params LightBeamChannelParams) *Shape {
	shp := C.create_light_beam_channel(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateLightBeamChannelWithPlace(params LightBeamChannelParams, position Point3, xDir Dir3, zDir Dir3) *Shape {
	shp := C.create_light_beam_channel_with_place(params.to_struct(), position.val, xDir.val, zDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type FlatSteelParams struct {
	Width     float32
	Thickness float32
	Length    float32
}

func (p *FlatSteelParams) to_struct() C.flat_steel_params_t {
	var c C.flat_steel_params_t
	c.width = C.double(p.Width)
	c.thickness = C.double(p.Thickness)
	c.length = C.double(p.Length)
	return c
}

func CreateFlatSteel(params FlatSteelParams) *Shape {
	shp := C.create_flat_steel(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateFlatSteelWithPlace(params FlatSteelParams, position Point3, xDir Dir3, zDir Dir3) *Shape {
	shp := C.create_flat_steel_with_place(params.to_struct(), position.val, xDir.val, zDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type LSteelParams struct {
	Height    float32
	Width     float32
	Thickness float32
	Radius    float32
	Length    float32
}

func (p *LSteelParams) to_struct() C.lsteel_params_t {
	var c C.lsteel_params_t
	c.height = C.double(p.Height)
	c.width = C.double(p.Width)
	c.thickness = C.double(p.Thickness)
	c.radius = C.double(p.Radius)
	c.length = C.double(p.Length)
	return c
}

func CreateLSteel(params LSteelParams) *Shape {
	shp := C.create_lsteel(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateLSteelWithPlace(params LSteelParams, position Point3, xDir Dir3, zDir Dir3) *Shape {
	shp := C.create_lsteel_with_place(params.to_struct(), position.val, xDir.val, zDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type TSteelParams struct {
	Height          float32
	Width           float32
	WebThickness    float32
	FlangeThickness float32
	Radius          float32
	Length          float32
}

func (p *TSteelParams) to_struct() C.tsteel_params_t {
	var c C.tsteel_params_t
	c.height = C.double(p.Height)
	c.width = C.double(p.Width)
	c.webThickness = C.double(p.WebThickness)
	c.flangeThickness = C.double(p.FlangeThickness)
	c.radius = C.double(p.Radius)
	c.length = C.double(p.Length)
	return c
}

func CreateTSteel(params TSteelParams) *Shape {
	shp := C.create_tsteel(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateTSteelWithPlace(params TSteelParams, position Point3, xDir Dir3, zDir Dir3) *Shape {
	shp := C.create_tsteel_with_place(params.to_struct(), position.val, xDir.val, zDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type RoundSteelParams struct {
	Diameter float32
	Length   float32
}

func (p *RoundSteelParams) to_struct() C.round_steel_params_t {
	var c C.round_steel_params_t
	c.diameter = C.double(p.Diameter)
	c.length = C.double(p.Length)
	return c
}

func CreateRoundSteel(params RoundSteelParams) *Shape {
	shp := C.create_round_steel(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateRoundSteelWithPlace(params RoundSteelParams, position Point3, xDir Dir3) *Shape {
	shp := C.create_round_steel_with_place(params.to_struct(), position.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type RoundSteelTubeParams struct {
	OuterDiameter float32
	InnerDiameter float32
	Length        float32
}

func (p *RoundSteelTubeParams) to_struct() C.round_steel_tube_params_t {
	var c C.round_steel_tube_params_t
	c.outerDiameter = C.double(p.OuterDiameter)
	c.innerDiameter = C.double(p.InnerDiameter)
	c.length = C.double(p.Length)
	return c
}

func CreateRoundSteelTube(params RoundSteelTubeParams) *Shape {
	shp := C.create_round_steel_tube(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateRoundSteelTubeWithPlace(params RoundSteelTubeParams, position Point3, xDir Dir3) *Shape {
	shp := C.create_round_steel_tube_with_place(params.to_struct(), position.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type RectangularSteelTubeParams struct {
	Height    float32
	Width     float32
	Thickness float32
	Length    float32
}

func (p *RectangularSteelTubeParams) to_struct() C.rectangular_steel_tube_params_t {
	var c C.rectangular_steel_tube_params_t
	c.height = C.double(p.Height)
	c.width = C.double(p.Width)
	c.thickness = C.double(p.Thickness)
	c.length = C.double(p.Length)
	return c
}

func CreateRectangularSteelTube(params RectangularSteelTubeParams) *Shape {
	shp := C.create_rectangular_steel_tube(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateRectangularSteelTubeWithPlace(params RectangularSteelTubeParams, position Point3, xDir Dir3, zDir Dir3) *Shape {
	shp := C.create_rectangular_steel_tube_with_place(params.to_struct(), position.val, xDir.val, zDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type SquareSteelTubeParams struct {
	Size      float32
	Thickness float32
	Length    float32
}

func (p *SquareSteelTubeParams) to_struct() C.square_steel_tube_params_t {
	var c C.square_steel_tube_params_t
	c.size = C.double(p.Size)
	c.thickness = C.double(p.Thickness)
	c.length = C.double(p.Length)
	return c
}

func CreateSquareSteelTube(params SquareSteelTubeParams) *Shape {
	shp := C.create_square_steel_tube(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateSquareSteelTubeWithPlace(params SquareSteelTubeParams, position Point3, xDir Dir3, zDir Dir3) *Shape {
	shp := C.create_square_steel_tube_with_place(params.to_struct(), position.val, xDir.val, zDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type DoubleChannelSteelParams struct {
	Base    BeamChannelParams
	Spacing float32
}

func (p *DoubleChannelSteelParams) to_struct() C.double_channel_steel_params_t {
	var c C.double_channel_steel_params_t
	c.base = p.Base.to_struct()
	c.spacing = C.double(p.Spacing)
	return c
}

func CreateDoubleChannelSteel(params DoubleChannelSteelParams) *Shape {
	shp := C.create_double_channel_steel(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateDoubleChannelSteelWithPlace(params DoubleChannelSteelParams, position Point3, xDir Dir3, zDir Dir3) *Shape {
	shp := C.create_double_channel_steel_with_place(params.to_struct(), position.val, xDir.val, zDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type EquilateralDoubleAngleSteelParams struct {
	Base    EquilateralAngleSteelParams
	Spacing float32
}

func (p *EquilateralDoubleAngleSteelParams) to_struct() C.equilateral_double_angle_steel_params_t {
	var c C.equilateral_double_angle_steel_params_t
	c.base = p.Base.to_struct()
	c.spacing = C.double(p.Spacing)
	return c
}

func CreateEquilateralDoubleAngleSteel(params EquilateralDoubleAngleSteelParams) *Shape {
	shp := C.create_equilateral_double_angle_steel(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateEquilateralDoubleAngleSteelWithPlace(params EquilateralDoubleAngleSteelParams, position Point3, xDir Dir3, zDir Dir3) *Shape {
	shp := C.create_equilateral_double_angle_steel_with_place(params.to_struct(), position.val, xDir.val, zDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type UnequalAngleSteelParams struct {
	Base    ScaleneAngleSteelParams
	Spacing float32
}

func (p *UnequalAngleSteelParams) to_struct() C.unequal_angle_steel_params_t {
	var c C.unequal_angle_steel_params_t
	c.base = p.Base.to_struct()
	c.spacing = C.double(p.Spacing)
	return c
}

func CreateUnequalAngleSteel(params UnequalAngleSteelParams) *Shape {
	shp := C.create_unequal_angle_steel(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateUnequalAngleSteelWithPlace(params UnequalAngleSteelParams, position Point3, xDir Dir3, zDir Dir3) *Shape {
	shp := C.create_unequal_angle_steel_with_place(params.to_struct(), position.val, xDir.val, zDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type PolygonTubeParams struct {
	SideLength float32
	Thickness  float32
	Length     float32
	Sides      int32
}

func (p *PolygonTubeParams) to_struct() C.polygon_tube_params_t {
	var c C.polygon_tube_params_t
	c.side_length = C.double(p.SideLength)
	c.thickness = C.double(p.Thickness)
	c.length = C.double(p.Length)
	c.sides = C.int(p.Sides)
	return c
}

func CreatePolygonTube(params PolygonTubeParams) *Shape {
	shp := C.create_polygon_tube(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreatePolygonTubeWithPlace(params PolygonTubeParams, position Point3, xDir Dir3) *Shape {
	shp := C.create_polygon_tube_with_place(params.to_struct(), position.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type BoredPileParams struct {
	H1           float32
	H2           float32
	H3           float32
	H4           float32
	D            float32
	Diameter     float32
	FilletRadius float32
}

func (p *BoredPileParams) to_struct() C.bored_pile_params_t {
	var c C.bored_pile_params_t
	c.H1 = C.double(p.H1)
	c.H2 = C.double(p.H2)
	c.H3 = C.double(p.H3)
	c.H4 = C.double(p.H4)
	c.d = C.double(p.Diameter)
	c.D = C.double(p.D)
	c.filletRadius = C.double(p.FilletRadius)
	return c
}

func CreateBoredPileFoundation(params BoredPileParams) *Shape {
	shp := C.create_bored_pile_foundation(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateBoredPileFoundationWithPlace(params BoredPileParams, position Point3, direction Dir3) *Shape {
	shp := C.create_bored_pile_foundation_with_place(params.to_struct(), position.val, direction.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type RockPileCapParams struct {
	H1        float32
	H2        float32
	H3        float32
	D         float32
	B         float32
	B1        float32
	L1        float32
	E1        float32
	E2        float32
	CS        int32
	ZCount    int32
	ZPosArray []Point3
}

func (p *RockPileCapParams) to_struct() C.rock_pile_cap_params_t {
	var c C.rock_pile_cap_params_t
	c.H1 = C.double(p.H1)
	c.H2 = C.double(p.H2)
	c.H3 = C.double(p.H3)
	c.d = C.double(p.D)
	c.b = C.double(p.B)
	c.B1 = C.double(p.B1)
	c.L1 = C.double(p.L1)
	c.e1 = C.double(p.E1)
	c.e2 = C.double(p.E2)
	c.cs = C.int(p.CS)
	c.ZCOUNT = C.int(p.ZCount)

	if len(p.ZPosArray) > 0 {
		c.ZPOSTARRAY = (*C.pnt3d_t)(C.malloc(C.size_t(len(p.ZPosArray)) * C.sizeof_pnt3d_t))
		for i, pos := range p.ZPosArray {
			*(*C.pnt3d_t)(unsafe.Pointer(uintptr(unsafe.Pointer(c.ZPOSTARRAY)) + uintptr(i)*C.sizeof_pnt3d_t)) = pos.val
		}
	}
	return c
}

func CreateRockPileCapFoundation(params RockPileCapParams) *Shape {
	cParams := params.to_struct()
	defer func() {
		if cParams.ZPOSTARRAY != nil {
			C.free(unsafe.Pointer(cParams.ZPOSTARRAY))
		}
	}()

	shp := C.create_rock_pile_cap_foundation(cParams)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateRockPileCapFoundationWithPlace(params RockPileCapParams, position Point3, direction Dir3) *Shape {
	cParams := params.to_struct()
	defer func() {
		if cParams.ZPOSTARRAY != nil {
			C.free(unsafe.Pointer(cParams.ZPOSTARRAY))
		}
	}()

	shp := C.create_rock_pile_cap_foundation_with_place(cParams, position.val, direction.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type PileCapParams struct {
	H1           float32
	H2           float32
	H3           float32
	H4           float32
	H5           float32
	H6           float32
	D            float32
	Diameter     float32
	B            float32
	B1           float32
	L1           float32
	E1           float32
	E2           float32
	CS           int32
	ZCount       int32
	ZPosArray    []Point3
	FilletRadius float32
}

func (p *PileCapParams) to_struct() C.pile_cap_params_t {
	var c C.pile_cap_params_t
	c.H1 = C.double(p.H1)
	c.H2 = C.double(p.H2)
	c.H3 = C.double(p.H3)
	c.H4 = C.double(p.H4)
	c.H5 = C.double(p.H5)
	c.H6 = C.double(p.H6)
	c.d = C.double(p.Diameter)
	c.D = C.double(p.D)
	c.b = C.double(p.B)
	c.B1 = C.double(p.B1)
	c.L1 = C.double(p.L1)
	c.e1 = C.double(p.E1)
	c.e2 = C.double(p.E2)
	c.cs = C.int(p.CS)
	c.ZCOUNT = C.int(p.ZCount)
	c.filletRadius = C.double(p.FilletRadius)

	if len(p.ZPosArray) > 0 {
		c.ZPOSTARRAY = (*C.pnt3d_t)(C.malloc(C.size_t(len(p.ZPosArray)) * C.sizeof_pnt3d_t))
		for i, pos := range p.ZPosArray {
			*(*C.pnt3d_t)(unsafe.Pointer(uintptr(unsafe.Pointer(c.ZPOSTARRAY)) + uintptr(i)*C.sizeof_pnt3d_t)) = pos.val
		}
	}
	return c
}

func CreatePileCapFoundation(params PileCapParams) *Shape {
	cParams := params.to_struct()
	defer func() {
		if cParams.ZPOSTARRAY != nil {
			C.free(unsafe.Pointer(cParams.ZPOSTARRAY))
		}
	}()

	shp := C.create_pile_cap_foundation(cParams)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreatePileCapFoundationWithPlace(params PileCapParams, position Point3, direction Dir3) *Shape {
	cParams := params.to_struct()
	defer func() {
		if cParams.ZPOSTARRAY != nil {
			C.free(unsafe.Pointer(cParams.ZPOSTARRAY))
		}
	}()

	shp := C.create_pile_cap_foundation_with_place(cParams, position.val, direction.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type RockAnchorParams struct {
	H1        float32
	H2        float32
	Diameter  float32
	B1        float32
	L1        float32
	ZCount    int32
	ZPosArray []Point3
}

func (p *RockAnchorParams) to_struct() C.rock_anchor_params_t {
	var c C.rock_anchor_params_t
	c.H1 = C.double(p.H1)
	c.H2 = C.double(p.H2)
	c.d = C.double(p.Diameter)
	c.B1 = C.double(p.B1)
	c.L1 = C.double(p.L1)
	c.ZCOUNT = C.int(p.ZCount)

	if len(p.ZPosArray) > 0 {
		c.ZPOSTARRAY = (*C.pnt3d_t)(C.malloc(C.size_t(len(p.ZPosArray)) * C.sizeof_pnt3d_t))
		for i, pos := range p.ZPosArray {
			*(*C.pnt3d_t)(unsafe.Pointer(uintptr(unsafe.Pointer(c.ZPOSTARRAY)) + uintptr(i)*C.sizeof_pnt3d_t)) = pos.val
		}
	}
	return c
}

func CreateRockAnchorFoundation(params RockAnchorParams) *Shape {
	cParams := params.to_struct()
	defer func() {
		if cParams.ZPOSTARRAY != nil {
			C.free(unsafe.Pointer(cParams.ZPOSTARRAY))
		}
	}()

	shp := C.create_rock_anchor_foundation(cParams)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateRockAnchorFoundationWithPlace(params RockAnchorParams, position Point3, direction Dir3) *Shape {
	cParams := params.to_struct()
	defer func() {
		if cParams.ZPOSTARRAY != nil {
			C.free(unsafe.Pointer(cParams.ZPOSTARRAY))
		}
	}()

	shp := C.create_rock_anchor_foundation_with_place(cParams, position.val, direction.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type EmbeddedRockAnchorParams struct {
	H1       float32
	H2       float32
	H3       float32
	Diameter float32
	D        float32
}

func (p *EmbeddedRockAnchorParams) to_struct() C.embedded_rock_anchor_params_t {
	var c C.embedded_rock_anchor_params_t
	c.H1 = C.double(p.H1)
	c.H2 = C.double(p.H2)
	c.H3 = C.double(p.H3)
	c.d = C.double(p.Diameter)
	c.D = C.double(p.D)
	return c
}

func CreateEmbeddedRockAnchorFoundation(params EmbeddedRockAnchorParams) *Shape {
	shp := C.create_embedded_rock_anchor_foundation(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateEmbeddedRockAnchorFoundationWithPlace(params EmbeddedRockAnchorParams, position Point3, direction Dir3) *Shape {
	shp := C.create_embedded_rock_anchor_foundation_with_place(params.to_struct(), position.val, direction.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type InclinedRockAnchorParams struct {
	H1       float32
	H2       float32
	Diameter float32
	D        float32
	B        float32
	L        float32
	E1       float32
	E2       float32
	Alpha1   float32
	Alpha2   float32
}

func (p *InclinedRockAnchorParams) to_struct() C.inclined_rock_anchor_params_t {
	var c C.inclined_rock_anchor_params_t
	c.H1 = C.double(p.H1)
	c.H2 = C.double(p.H2)
	c.d = C.double(p.Diameter)
	c.D = C.double(p.D)
	c.B = C.double(p.B)
	c.L = C.double(p.L)
	c.e1 = C.double(p.E1)
	c.e2 = C.double(p.E2)
	c.alpha1 = C.double(p.Alpha1)
	c.alpha2 = C.double(p.Alpha2)
	return c
}

func CreateInclinedRockAnchorFoundation(params InclinedRockAnchorParams) *Shape {
	shp := C.create_inclined_rock_anchor_foundation(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateInclinedRockAnchorFoundationWithPlace(params InclinedRockAnchorParams, position Point3, direction Dir3) *Shape {
	shp := C.create_inclined_rock_anchor_foundation_with_place(params.to_struct(), position.val, direction.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type ExcavatedFoundationParams struct {
	H1       float32
	H2       float32
	H3       float32
	D        float32
	Diameter float32
	Alpha1   float32
	Alpha2   float32
}

func (p *ExcavatedFoundationParams) to_struct() C.excavated_foundation_params_t {
	var c C.excavated_foundation_params_t
	c.H1 = C.double(p.H1)
	c.H2 = C.double(p.H2)
	c.H3 = C.double(p.H3)
	c.d = C.double(p.Diameter)
	c.D = C.double(p.D)
	c.alpha1 = C.double(p.Alpha1)
	c.alpha2 = C.double(p.Alpha2)
	return c
}

func CreateExcavatedFoundation(params ExcavatedFoundationParams) *Shape {
	shp := C.create_excavated_foundation(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateExcavatedFoundationWithPlace(params ExcavatedFoundationParams, position Point3, direction Dir3) *Shape {
	shp := C.create_excavated_foundation_with_place(params.to_struct(), position.val, direction.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type StepFoundationParams struct {
	H  float32
	H1 float32
	H2 float32
	H3 float32
	B  float32
	B1 float32
	B2 float32
	B3 float32
	L1 float32
	L2 float32
	L3 float32
	N  int32
}

func (p *StepFoundationParams) to_struct() C.step_foundation_params_t {
	var c C.step_foundation_params_t
	c.H = C.double(p.H)
	c.H1 = C.double(p.H1)
	c.H2 = C.double(p.H2)
	c.H3 = C.double(p.H3)
	c.b = C.double(p.B)
	c.B1 = C.double(p.B1)
	c.B2 = C.double(p.B2)
	c.B3 = C.double(p.B3)
	c.L1 = C.double(p.L1)
	c.L2 = C.double(p.L2)
	c.L3 = C.double(p.L3)
	c.N = C.int(p.N)
	return c
}

func CreateStepFoundation(params StepFoundationParams) *Shape {
	shp := C.create_step_foundation(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateStepFoundationWithPlace(params StepFoundationParams, position Point3, direction Dir3) *Shape {
	shp := C.create_step_foundation_with_place(params.to_struct(), position.val, direction.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type StepPlateFoundationParams struct {
	H      float32
	H1     float32
	H2     float32
	H3     float32
	B      float32
	L1     float32
	L2     float32
	B1     float32
	B2     float32
	Alpha1 float32
	Alpha2 float32
	N      int32
}

func (p *StepPlateFoundationParams) to_struct() C.step_plate_foundation_params_t {
	var c C.step_plate_foundation_params_t
	c.H = C.double(p.H)
	c.H1 = C.double(p.H1)
	c.H2 = C.double(p.H2)
	c.H3 = C.double(p.H3)
	c.b = C.double(p.B)
	c.L1 = C.double(p.L1)
	c.L2 = C.double(p.L2)
	c.B1 = C.double(p.B1)
	c.B2 = C.double(p.B2)
	c.alpha1 = C.double(p.Alpha1)
	c.alpha2 = C.double(p.Alpha2)
	c.N = C.int(p.N)
	return c
}

func CreateStepPlateFoundation(params StepPlateFoundationParams) *Shape {
	shp := C.create_step_plate_foundation(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateStepPlateFoundationWithPlace(params StepPlateFoundationParams, position Point3, direction Dir3) *Shape {
	shp := C.create_step_plate_foundation_with_place(params.to_struct(), position.val, direction.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type SlopedBaseFoundationParams struct {
	H1     float32
	H2     float32
	H3     float32
	B      float32
	L1     float32
	L2     float32
	B1     float32
	B2     float32
	Alpha1 float32
	Alpha2 float32
}

func (p *SlopedBaseFoundationParams) to_struct() C.sloped_base_foundation_params_t {
	var c C.sloped_base_foundation_params_t
	c.H1 = C.double(p.H1)
	c.H2 = C.double(p.H2)
	c.H3 = C.double(p.H3)
	c.b = C.double(p.B)
	c.L1 = C.double(p.L1)
	c.L2 = C.double(p.L2)
	c.B1 = C.double(p.B1)
	c.B2 = C.double(p.B2)
	c.alpha1 = C.double(p.Alpha1)
	c.alpha2 = C.double(p.Alpha2)
	return c
}

func CreateSlopedBaseFoundation(params SlopedBaseFoundationParams) *Shape {
	shp := C.create_sloped_base_foundation(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateSlopedBaseFoundationWithPlace(params SlopedBaseFoundationParams, position Point3, direction Dir3) *Shape {
	shp := C.create_sloped_base_foundation_with_place(params.to_struct(), position.val, direction.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type CompositeCaissonFoundationParams struct {
	H1 float32
	H2 float32
	H3 float32
	H4 float32
	B  float32
	D  float32
	T  float32
	B1 float32
	B2 float32
	L1 float32
	L2 float32
}

func (p *CompositeCaissonFoundationParams) to_struct() C.composite_caisson_foundation_params_t {
	var c C.composite_caisson_foundation_params_t
	c.H1 = C.double(p.H1)
	c.H2 = C.double(p.H2)
	c.H3 = C.double(p.H3)
	c.H4 = C.double(p.H4)
	c.b = C.double(p.B)
	c.D = C.double(p.D)
	c.t = C.double(p.T)
	c.B1 = C.double(p.B1)
	c.B2 = C.double(p.B2)
	c.L1 = C.double(p.L1)
	c.L2 = C.double(p.L2)
	return c
}

func CreateCompositeCaissonFoundation(params CompositeCaissonFoundationParams) *Shape {
	shp := C.create_composite_caisson_foundation(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateCompositeCaissonFoundationWithPlace(params CompositeCaissonFoundationParams, position Point3, direction Dir3) *Shape {
	shp := C.create_composite_caisson_foundation_with_place(params.to_struct(), position.val, direction.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type RaftFoundationParams struct {
	H1 float32
	H2 float32
	H3 float32
	B1 float32
	B2 float32
	B  float32
	L1 float32
	L2 float32
}

func (p *RaftFoundationParams) to_struct() C.raft_foundation_params_t {
	var c C.raft_foundation_params_t
	c.H1 = C.double(p.H1)
	c.H2 = C.double(p.H2)
	c.H3 = C.double(p.H3)
	c.b1 = C.double(p.B1)
	c.b2 = C.double(p.B2)
	c.B1 = C.double(p.B)
	c.B2 = C.double(p.B2)
	c.L1 = C.double(p.L1)
	c.L2 = C.double(p.L2)
	return c
}

func CreateRaftFoundation(params RaftFoundationParams) *Shape {
	shp := C.create_raft_foundation(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateRaftFoundationWithPlace(params RaftFoundationParams, position Point3, direction Dir3) *Shape {
	shp := C.create_raft_foundation_with_place(params.to_struct(), position.val, direction.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type DirectBuriedFoundationParams struct {
	H1              float32
	H2              float32
	D               float32
	Diameter        float32
	B               float32
	T               float32
	HasBasePlate    bool
	IsCircularPlate bool
}

func (p *DirectBuriedFoundationParams) to_struct() C.direct_buried_foundation_params_t {
	var c C.direct_buried_foundation_params_t
	c.H1 = C.double(p.H1)
	c.H2 = C.double(p.H2)
	c.d = C.double(p.Diameter)
	c.D = C.double(p.D)
	c.B = C.double(p.B)
	c.t = C.double(p.T)
	c.hasBasePlate = C.bool(p.HasBasePlate)
	c.isCircularPlate = C.bool(p.IsCircularPlate)
	return c
}

func CreateDirectBuriedFoundation(params DirectBuriedFoundationParams) *Shape {
	shp := C.create_direct_buried_foundation(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateDirectBuriedFoundationWithPlace(params DirectBuriedFoundationParams, position Point3, direction Dir3) *Shape {
	shp := C.create_direct_buried_foundation_with_place(params.to_struct(), position.val, direction.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type SteelSleeveFoundationParams struct {
	H1 float32
	H2 float32
	H3 float32
	H4 float32
	D  float32
	D1 float32
	D2 float32
	T  float32
	B1 float32
	B2 float32
}

func (p *SteelSleeveFoundationParams) to_struct() C.steel_sleeve_foundation_params_t {
	var c C.steel_sleeve_foundation_params_t
	c.H1 = C.double(p.H1)
	c.H2 = C.double(p.H2)
	c.H3 = C.double(p.H3)
	c.H4 = C.double(p.H4)
	c.d = C.double(p.D)
	c.D1 = C.double(p.D1)
	c.D2 = C.double(p.D2)
	c.t = C.double(p.T)
	c.B1 = C.double(p.B1)
	c.B2 = C.double(p.B2)
	return c
}

func CreateSteelSleeveFoundation(params SteelSleeveFoundationParams) *Shape {
	shp := C.create_steel_sleeve_foundation(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateSteelSleeveFoundationWithPlace(params SteelSleeveFoundationParams, position Point3, direction Dir3) *Shape {
	shp := C.create_steel_sleeve_foundation_with_place(params.to_struct(), position.val, direction.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type PrecastColumnFoundationParams struct {
	H1 float32
	H2 float32
	H3 float32
	D  float32
	B1 float32
	B2 float32
	L1 float32
	L2 float32
}

func (p *PrecastColumnFoundationParams) to_struct() C.precast_column_foundation_params_t {
	var c C.precast_column_foundation_params_t
	c.H1 = C.double(p.H1)
	c.H2 = C.double(p.H2)
	c.H3 = C.double(p.H3)
	c.d = C.double(p.D)
	c.B1 = C.double(p.B1)
	c.B2 = C.double(p.B2)
	c.L1 = C.double(p.L1)
	c.L2 = C.double(p.L2)
	return c
}

func CreatePrecastColumnFoundation(params PrecastColumnFoundationParams) *Shape {
	shp := C.create_precast_column_foundation(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreatePrecastColumnFoundationWithPlace(params PrecastColumnFoundationParams, position Point3, direction Dir3) *Shape {
	shp := C.create_precast_column_foundation_with_place(params.to_struct(), position.val, direction.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type PrecastPinnedFoundationParams struct {
	H1 float32
	H2 float32
	H3 float32
	D  float32
	B1 float32
	B2 float32
	L1 float32
	L2 float32
	B  float32
	H  float32
	L  float32
}

func (p *PrecastPinnedFoundationParams) to_struct() C.precast_pinned_foundation_params_t {
	var c C.precast_pinned_foundation_params_t
	c.H1 = C.double(p.H1)
	c.H2 = C.double(p.H2)
	c.H3 = C.double(p.H3)
	c.d = C.double(p.D)
	c.B1 = C.double(p.B1)
	c.B2 = C.double(p.B2)
	c.L1 = C.double(p.L1)
	c.L2 = C.double(p.L2)
	c.B = C.double(p.B)
	c.H = C.double(p.H)
	c.L = C.double(p.L)
	return c
}

func CreatePrecastPinnedFoundation(params PrecastPinnedFoundationParams) *Shape {
	shp := C.create_precast_pinned_foundation(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreatePrecastPinnedFoundationWithPlace(params PrecastPinnedFoundationParams, position Point3, direction Dir3) *Shape {
	shp := C.create_precast_pinned_foundation_with_place(params.to_struct(), position.val, direction.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type PrecastMetalSupportFoundationParams struct {
	H1 float32
	H2 float32
	H3 float32
	H4 float32
	B1 float32
	B2 float32
	B  float32
	L1 float32
	L2 float32
	S1 float32
	S2 float32
	N1 int32
	N2 int32
	HX []float32
}

func (p *PrecastMetalSupportFoundationParams) to_struct() C.precast_metal_support_foundation_params_t {
	var c C.precast_metal_support_foundation_params_t
	c.H1 = C.double(p.H1)
	c.H2 = C.double(p.H2)
	c.H3 = C.double(p.H3)
	c.H4 = C.double(p.H4)
	c.b1 = C.double(p.B1)
	c.b2 = C.double(p.B2)
	c.B1 = C.double(p.B)
	c.B2 = C.double(p.B2)
	c.L1 = C.double(p.L1)
	c.L2 = C.double(p.L2)
	c.S1 = C.double(p.S1)
	c.S2 = C.double(p.S2)
	c.n1 = C.int(p.N1)
	c.n2 = C.int(p.N2)

	if len(p.HX) > 0 {
		c.HX = (*C.double)(C.malloc(C.size_t(len(p.HX)) * C.sizeof_double))
		for i, val := range p.HX {
			*(*C.double)(unsafe.Pointer(uintptr(unsafe.Pointer(c.HX)) + uintptr(i)*C.sizeof_double)) = C.double(val)
		}
		c.HXCount = C.int(len(p.HX))
	}
	return c
}

func CreatePrecastMetalSupportFoundation(params PrecastMetalSupportFoundationParams) *Shape {
	cParams := params.to_struct()
	defer func() {
		if cParams.HX != nil {
			C.free(unsafe.Pointer(cParams.HX))
		}
	}()

	shp := C.create_precast_metal_support_foundation(cParams)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreatePrecastMetalSupportFoundationWithPlace(params PrecastMetalSupportFoundationParams, position Point3, direction Dir3) *Shape {
	cParams := params.to_struct()
	defer func() {
		if cParams.HX != nil {
			C.free(unsafe.Pointer(cParams.HX))
		}
	}()

	shp := C.create_precast_metal_support_foundation_with_place(cParams, position.val, direction.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type PrecastConcreteSupportFoundationParams struct {
	H1 float32
	H2 float32
	H3 float32
	H4 float32
	H5 float32
	B1 float32
	b2 float32
	B3 float32
	B  float32
	B2 float32
	L1 float32
	L2 float32
	S1 float32
	N1 int32
}

func (p *PrecastConcreteSupportFoundationParams) to_struct() C.precast_concrete_support_foundation_params_t {
	var c C.precast_concrete_support_foundation_params_t
	c.H1 = C.double(p.H1)
	c.H2 = C.double(p.H2)
	c.H3 = C.double(p.H3)
	c.H4 = C.double(p.H4)
	c.H5 = C.double(p.H5)
	c.b1 = C.double(p.B1)
	c.b2 = C.double(p.B2)
	c.b3 = C.double(p.B3)
	c.B1 = C.double(p.B)
	c.B2 = C.double(p.B2)
	c.L1 = C.double(p.L1)
	c.L2 = C.double(p.L2)
	c.S1 = C.double(p.S1)
	c.n1 = C.int(p.N1)
	return c
}

func CreatePrecastConcreteSupportFoundation(params PrecastConcreteSupportFoundationParams) *Shape {
	shp := C.create_precast_concrete_support_foundation(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreatePrecastConcreteSupportFoundationWithPlace(params PrecastConcreteSupportFoundationParams, position Point3, direction Dir3) *Shape {
	shp := C.create_precast_concrete_support_foundation_with_place(params.to_struct(), position.val, direction.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type TransmissionLineParams struct {
	Type                    string
	SectionalArea           float32
	OutsideDiameter         float32
	WireWeight              float32
	CoefficientOfElasticity float32
	ExpansionCoefficient    float32
	RatedStrength           float32
}

func (p *TransmissionLineParams) to_struct() C.transmission_line_params_t {
	var c C.transmission_line_params_t
	c.ctype = C.CString(p.Type)
	c.sectionalArea = C.double(p.SectionalArea)
	c.outsideDiameter = C.double(p.OutsideDiameter)
	c.wireWeight = C.double(p.WireWeight)
	c.coefficientOfElasticity = C.double(p.CoefficientOfElasticity)
	c.expansionCoefficient = C.double(p.ExpansionCoefficient)
	c.ratedStrength = C.double(p.RatedStrength)
	return c
}

func CreateTransmissionLine(params TransmissionLineParams, startPoint Point3, endPoint Point3) *Shape {
	cParams := params.to_struct()
	defer C.free(unsafe.Pointer(cParams.ctype))

	shp := C.create_transmission_line(cParams, startPoint.val, endPoint.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type InsulatorMaterial int

const (
	InsulatorMaterialCeramic   InsulatorMaterial = 1
	InsulatorMaterialGlass     InsulatorMaterial = 2
	InsulatorMaterialComposite InsulatorMaterial = 3
)

type InsulatorArrangement int

const (
	InsulatorArrangementHorizontal InsulatorArrangement = 1
	InsulatorArrangementVertical   InsulatorArrangement = 2
)

type InsulatorApplication int

const (
	InsulatorApplicationConductor  InsulatorApplication = 1
	InsulatorApplicationGroundWire InsulatorApplication = 2
)

type InsulatorStringType int

const (
	InsulatorStringTypeSuspension InsulatorStringType = 1
	InsulatorStringTypeTension    InsulatorStringType = 2
)

type CompositeInsulatorParams struct {
	MajorRadius float32
	MinorRadius float32
	Gap         float32
}

type FittingLengths struct {
	LeftUpper  float32
	RightUpper float32
	LeftLower  float32
	RightLower float32
}

type MultiLink struct {
	Count       int32
	Spacing     float32
	Arrangement InsulatorArrangement
}

type InsulatorParams struct {
	IsComposite bool
	RadiusData  interface{} // Either float32 or CompositeInsulatorParams
	Height      float32
	LeftCount   int32
	RightCount  int32
	Material    InsulatorMaterial
}

type GradingRing struct {
	Count    int32
	Position float32
	Height   float32
	Radius   float32
}

type InsulatorCompositeParams struct {
	Type           string
	SubNum         int32
	SubType        int32
	SplitDistance  float32
	VAngleLeft     float32
	VAngleRight    float32
	ULinkLength    float32
	Weight         float32
	FittingLengths FittingLengths
	MultiLink      MultiLink
	Insulator      InsulatorParams
	GradingRing    GradingRing
	Application    InsulatorApplication
	StringType     InsulatorStringType
}

func (p *InsulatorCompositeParams) to_struct() C.insulator_composite_params_t {
	var c C.insulator_composite_params_t
	c.ctype = C.CString(p.Type)
	c.subNum = C.int(p.SubNum)
	c.subType = C.int(p.SubType)
	c.splitDistance = C.double(p.SplitDistance)
	c.vAngleLeft = C.double(p.VAngleLeft)
	c.vAngleRight = C.double(p.VAngleRight)
	c.uLinkLength = C.double(p.ULinkLength)
	c.weight = C.double(p.Weight)

	c.fittingLengths.leftUpper = C.double(p.FittingLengths.LeftUpper)
	c.fittingLengths.rightUpper = C.double(p.FittingLengths.RightUpper)
	c.fittingLengths.leftLower = C.double(p.FittingLengths.LeftLower)
	c.fittingLengths.rightLower = C.double(p.FittingLengths.RightLower)

	c.multiLink.count = C.int(p.MultiLink.Count)
	c.multiLink.spacing = C.double(p.MultiLink.Spacing)
	c.multiLink.arrangement = C.int(p.MultiLink.Arrangement)

	switch v := p.Insulator.RadiusData.(type) {
	case float32:
		c.insulator.isComposite = C.bool(false)
		*(*C.double)(unsafe.Pointer(&c.insulator.radiusData)) = C.double(v)
	case CompositeInsulatorParams:
		c.insulator.isComposite = C.bool(true)
		composite := (*C.composite_insulator_params_t)(unsafe.Pointer(&c.insulator.radiusData))
		composite.majorRadius = C.double(v.MajorRadius)
		composite.minorRadius = C.double(v.MinorRadius)
		composite.gap = C.double(v.Gap)
	}
	c.insulator.height = C.double(p.Insulator.Height)
	c.insulator.leftCount = C.int(p.Insulator.LeftCount)
	c.insulator.rightCount = C.int(p.Insulator.RightCount)
	c.insulator.material = C.int(p.Insulator.Material)

	c.gradingRing.count = C.int(p.GradingRing.Count)
	c.gradingRing.position = C.double(p.GradingRing.Position)
	c.gradingRing.height = C.double(p.GradingRing.Height)
	c.gradingRing.radius = C.double(p.GradingRing.Radius)

	c.application = C.int(p.Application)
	c.stringType = C.int(p.StringType)

	return c
}

func CreateCompositeInsulator(params InsulatorCompositeParams) *Shape {
	cParams := params.to_struct()
	defer C.free(unsafe.Pointer(cParams.ctype))

	shp := C.create_composite_insulator(cParams)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateCompositeInsulatorWithPlace(params InsulatorCompositeParams, position Point3, direction Dir3) *Shape {
	cParams := params.to_struct()
	defer C.free(unsafe.Pointer(cParams.ctype))

	shp := C.create_composite_insulator_with_place(cParams, position.val, direction.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type SingleHookAnchorParams struct {
	BoltDiameter       float32
	ExposedLength      float32
	NutCount           int32
	NutHeight          float32
	NutOD              float32
	WasherCount        int32
	WasherShape        int32
	WasherSize         float32
	WasherThickness    float32
	AnchorLength       float32
	HookStraightLength float32
	HookDiameter       float32
}

func (p *SingleHookAnchorParams) to_struct() C.single_hook_anchor_params_t {
	var c C.single_hook_anchor_params_t
	c.boltDiameter = C.double(p.BoltDiameter)
	c.exposedLength = C.double(p.ExposedLength)
	c.nutCount = C.int(p.NutCount)
	c.nutHeight = C.double(p.NutHeight)
	c.nutOD = C.double(p.NutOD)
	c.washerCount = C.int(p.WasherCount)
	c.washerShape = C.int(p.WasherShape)
	c.washerSize = C.double(p.WasherSize)
	c.washerThickness = C.double(p.WasherThickness)
	c.anchorLength = C.double(p.AnchorLength)
	c.hookStraightLength = C.double(p.HookStraightLength)
	c.hookDiameter = C.double(p.HookDiameter)
	return c
}

func CreateSingleHookAnchor(params SingleHookAnchorParams) *Shape {
	shp := C.create_single_hook_anchor(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateSingleHookAnchorWithPlace(params SingleHookAnchorParams, position Point3, normal Dir3, xDir Dir3) *Shape {
	shp := C.create_single_hook_anchor_with_place(params.to_struct(), position.val, normal.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type TripleHookAnchorParams struct {
	BoltDiameter        float32
	ExposedLength       float32
	NutCount            int32
	NutHeight           float32
	NutOD               float32
	WasherCount         int32
	WasherShape         int32
	WasherSize          float32
	WasherThickness     float32
	AnchorLength        float32
	HookStraightLengthA float32
	HookStraightLengthB float32
	HookDiameter        float32
	AnchorBarDiameter   float32
}

func (p *TripleHookAnchorParams) to_struct() C.triple_hook_anchor_params_t {
	var c C.triple_hook_anchor_params_t
	c.boltDiameter = C.double(p.BoltDiameter)
	c.exposedLength = C.double(p.ExposedLength)
	c.nutCount = C.int(p.NutCount)
	c.nutHeight = C.double(p.NutHeight)
	c.nutOD = C.double(p.NutOD)
	c.washerCount = C.int(p.WasherCount)
	c.washerShape = C.int(p.WasherShape)
	c.washerSize = C.double(p.WasherSize)
	c.washerThickness = C.double(p.WasherThickness)
	c.anchorLength = C.double(p.AnchorLength)
	c.hookStraightLengthA = C.double(p.HookStraightLengthA)
	c.hookStraightLengthB = C.double(p.HookStraightLengthB)
	c.hookDiameter = C.double(p.HookDiameter)
	c.anchorBarDiameter = C.double(p.AnchorBarDiameter)
	return c
}

func CreateTripleHookAnchor(params TripleHookAnchorParams) *Shape {
	shp := C.create_triple_hook_anchor(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateTripleHookAnchorWithPlace(params TripleHookAnchorParams, position Point3, normal Dir3, xDir Dir3) *Shape {
	shp := C.create_triple_hook_anchor_with_place(params.to_struct(), position.val, normal.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type RibbedAnchorParams struct {
	BoltDiameter       float32
	ExposedLength      float32
	NutCount           int32
	NutHeight          float32
	NutOD              float32
	WasherCount        int32
	WasherShape        int32
	WasherSize         float32
	WasherThickness    float32
	AnchorLength       float32
	BasePlateSize      float32
	RibTopWidth        float32
	RibBottomWidth     float32
	BasePlateThickness float32
	RibHeight          float32
	RibThickness       float32
}

func (p *RibbedAnchorParams) to_struct() C.ribbed_anchor_params_t {
	var c C.ribbed_anchor_params_t
	c.boltDiameter = C.double(p.BoltDiameter)
	c.exposedLength = C.double(p.ExposedLength)
	c.nutCount = C.int(p.NutCount)
	c.nutHeight = C.double(p.NutHeight)
	c.nutOD = C.double(p.NutOD)
	c.washerCount = C.int(p.WasherCount)
	c.washerShape = C.int(p.WasherShape)
	c.washerSize = C.double(p.WasherSize)
	c.washerThickness = C.double(p.WasherThickness)
	c.anchorLength = C.double(p.AnchorLength)
	c.basePlateSize = C.double(p.BasePlateSize)
	c.ribTopWidth = C.double(p.RibTopWidth)
	c.ribBottomWidth = C.double(p.RibBottomWidth)
	c.basePlateThickness = C.double(p.BasePlateThickness)
	c.ribHeight = C.double(p.RibHeight)
	c.ribThickness = C.double(p.RibThickness)
	return c
}

func CreateRibbedAnchor(params RibbedAnchorParams) *Shape {
	shp := C.create_ribbed_anchor(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateRibbedAnchorWithPlace(params RibbedAnchorParams, position Point3, normal Dir3, xDir Dir3) *Shape {
	shp := C.create_ribbed_anchor_with_place(params.to_struct(), position.val, normal.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type NutAnchorParams struct {
	BoltDiameter        float32
	ExposedLength       float32
	NutCount            int32
	NutHeight           float32
	NutOD               float32
	WasherCount         int32
	WasherShape         int32
	WasherSize          float32
	WasherThickness     float32
	AnchorLength        float32
	BasePlateSize       float32
	BasePlateThickness  float32
	BoltToPlateDistance float32
}

func (p *NutAnchorParams) to_struct() C.nut_anchor_params_t {
	var c C.nut_anchor_params_t
	c.boltDiameter = C.double(p.BoltDiameter)
	c.exposedLength = C.double(p.ExposedLength)
	c.nutCount = C.int(p.NutCount)
	c.nutHeight = C.double(p.NutHeight)
	c.nutOD = C.double(p.NutOD)
	c.washerCount = C.int(p.WasherCount)
	c.washerShape = C.int(p.WasherShape)
	c.washerSize = C.double(p.WasherSize)
	c.washerThickness = C.double(p.WasherThickness)
	c.anchorLength = C.double(p.AnchorLength)
	c.basePlateSize = C.double(p.BasePlateSize)
	c.basePlateThickness = C.double(p.BasePlateThickness)
	c.boltToPlateDistance = C.double(p.BoltToPlateDistance)
	return c
}

func CreateNutAnchor(params NutAnchorParams) *Shape {
	shp := C.create_nut_anchor(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateNutAnchorWithPlace(params NutAnchorParams, position Point3, normal Dir3, xDir Dir3) *Shape {
	shp := C.create_nut_anchor_with_place(params.to_struct(), position.val, normal.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type TripleArmAnchorParams struct {
	BoltDiameter      float32
	ExposedLength     float32
	NutCount          int32
	NutHeight         float32
	NutOD             float32
	WasherCount       int32
	WasherShape       int32
	WasherSize        float32
	WasherThickness   float32
	AnchorLength      float32
	ArmDiameter       float32
	ArmStraightLength float32
	ArmBendLength     float32
	ArmBendAngle      float32
}

func (p *TripleArmAnchorParams) to_struct() C.triple_arm_anchor_params_t {
	var c C.triple_arm_anchor_params_t
	c.boltDiameter = C.double(p.BoltDiameter)
	c.exposedLength = C.double(p.ExposedLength)
	c.nutCount = C.int(p.NutCount)
	c.nutHeight = C.double(p.NutHeight)
	c.nutOD = C.double(p.NutOD)
	c.washerCount = C.int(p.WasherCount)
	c.washerShape = C.int(p.WasherShape)
	c.washerSize = C.double(p.WasherSize)
	c.washerThickness = C.double(p.WasherThickness)
	c.anchorLength = C.double(p.AnchorLength)
	c.armDiameter = C.double(p.ArmDiameter)
	c.armStraightLength = C.double(p.ArmStraightLength)
	c.armBendLength = C.double(p.ArmBendLength)
	c.armBendAngle = C.double(p.ArmBendAngle)
	return c
}

func CreateTripleArmAnchor(params TripleArmAnchorParams) *Shape {
	shp := C.create_triple_arm_anchor(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateTripleArmAnchorWithPlace(params TripleArmAnchorParams, position Point3, normal Dir3, xDir Dir3) *Shape {
	shp := C.create_triple_arm_anchor_with_place(params.to_struct(), position.val, normal.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type PositioningPlateAnchorParams struct {
	BoltDiameter      float32
	ExposedLength     float32
	NutCount          int32
	NutHeight         float32
	NutOD             float32
	WasherCount       int32
	WasherShape       int32
	WasherSize        float32
	WasherThickness   float32
	AnchorLength      float32
	PlateLength       float32
	PlateThickness    float32
	ToBaseDistance    float32
	ToBottomDistance  float32
	GroutHoleDiameter float32
}

func (p *PositioningPlateAnchorParams) to_struct() C.positioning_plate_anchor_params_t {
	var c C.positioning_plate_anchor_params_t
	c.boltDiameter = C.double(p.BoltDiameter)
	c.exposedLength = C.double(p.ExposedLength)
	c.nutCount = C.int(p.NutCount)
	c.nutHeight = C.double(p.NutHeight)
	c.nutOD = C.double(p.NutOD)
	c.washerCount = C.int(p.WasherCount)
	c.washerShape = C.int(p.WasherShape)
	c.washerSize = C.double(p.WasherSize)
	c.washerThickness = C.double(p.WasherThickness)
	c.anchorLength = C.double(p.AnchorLength)
	c.plateLength = C.double(p.PlateLength)
	c.plateThickness = C.double(p.PlateThickness)
	c.toBaseDistance = C.double(p.ToBaseDistance)
	c.toBottomDistance = C.double(p.ToBottomDistance)
	c.groutHoleDiameter = C.double(p.GroutHoleDiameter)
	return c
}

func CreatePositioningPlateAnchor(params PositioningPlateAnchorParams) *Shape {
	shp := C.create_positioning_plate_anchor(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreatePositioningPlateAnchorWithPlace(params PositioningPlateAnchorParams, position Point3, normal Dir3, xDir Dir3) *Shape {
	shp := C.create_positioning_plate_anchor_with_place(params.to_struct(), position.val, normal.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type StubAngleParams struct {
	LegWidth      float32
	Thickness     float32
	Slope         float32
	ExposedLength float32
	AnchorLength  float32
}

func (p *StubAngleParams) to_struct() C.stub_angle_params_t {
	var c C.stub_angle_params_t
	c.legWidth = C.double(p.LegWidth)
	c.thickness = C.double(p.Thickness)
	c.slope = C.double(p.Slope)
	c.exposedLength = C.double(p.ExposedLength)
	c.anchorLength = C.double(p.AnchorLength)
	return c
}

func CreateStubAngle(params StubAngleParams) *Shape {
	cParams := params.to_struct()
	shp := C.create_stub_angle(cParams)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateStubAngleWithPlace(params StubAngleParams, position Point3, normal Dir3, xDir Dir3) *Shape {
	cParams := params.to_struct()
	shp := C.create_stub_angle_with_place(cParams, position.val, normal.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type StubTubeParams struct {
	Diameter      float32
	Thickness     float32
	Slope         float32
	ExposedLength float32
	AnchorLength  float32
}

func (p *StubTubeParams) to_struct() C.stub_tube_params_t {
	var c C.stub_tube_params_t
	c.diameter = C.double(p.Diameter)
	c.thickness = C.double(p.Thickness)
	c.slope = C.double(p.Slope)
	c.exposedLength = C.double(p.ExposedLength)
	c.anchorLength = C.double(p.AnchorLength)
	return c
}

func CreateStubTube(params StubTubeParams) *Shape {
	cParams := params.to_struct()
	shp := C.create_stub_tube(cParams)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateStubTubeWithPlace(params StubTubeParams, position Point3, normal Dir3, xDir Dir3) *Shape {
	cParams := params.to_struct()
	shp := C.create_stub_tube_with_place(cParams, position.val, normal.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}
