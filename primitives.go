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
	"errors"
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

type SharpBentCylinderParams struct {
	Radius    float32
	Length    float32
	BendAngle float32
}

func (p *SharpBentCylinderParams) to_struct() C.sharp_bent_cylinder_params_t {
	var c C.sharp_bent_cylinder_params_t
	c.radius = C.double(p.Radius)
	c.length = C.double(p.Length)
	c.bendAngle = C.double(p.BendAngle)
	return c
}

func CreateSharpBentCylinder(params SharpBentCylinderParams) *Shape {
	shp := C.create_sharp_bent_cylinder(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateSharpBentCylinderWithPlace(params SharpBentCylinderParams, position Point3, normal Dir3, xDir Dir3) *Shape {
	shp := C.create_sharp_bent_cylinder_with_place(params.to_struct(), position.val, normal.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type TruncatedConeParams struct {
	TopRadius    float32
	BottomRadius float32
	Height       float32
}

func (p *TruncatedConeParams) to_struct() C.truncated_cone_params_t {
	var c C.truncated_cone_params_t
	c.topRadius = C.double(p.TopRadius)
	c.bottomRadius = C.double(p.BottomRadius)
	c.height = C.double(p.Height)
	return c
}

func CreateTruncatedCone(params TruncatedConeParams) *Shape {
	shp := C.create_truncated_cone(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateTruncatedConeWithPlace(params TruncatedConeParams, basePoint Point3, axisDir Dir3) *Shape {
	shp := C.create_truncated_cone_with_place(params.to_struct(), basePoint.val, axisDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type EccentricTruncatedConeParams struct {
	TopRadius    float32
	BottomRadius float32
	Height       float32
	TopXOffset   float32
	TopYOffset   float32
}

func (p *EccentricTruncatedConeParams) to_struct() C.eccentric_truncated_cone_params_t {
	var c C.eccentric_truncated_cone_params_t
	c.topRadius = C.double(p.TopRadius)
	c.bottomRadius = C.double(p.BottomRadius)
	c.height = C.double(p.Height)
	c.topXOffset = C.double(p.TopXOffset)
	c.topYOffset = C.double(p.TopYOffset)
	return c
}

func CreateEccentricTruncatedCone(params EccentricTruncatedConeParams) *Shape {
	shp := C.create_eccentric_truncated_cone(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateEccentricTruncatedConeWithPlace(params EccentricTruncatedConeParams, basePoint Point3, axisDir Dir3) *Shape {
	shp := C.create_eccentric_truncated_cone_with_place(params.to_struct(), basePoint.val, axisDir.val)
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

type StretchedBodyParams struct {
	Points []Point3
	Normal Dir3
	Length float32
}

func (p *StretchedBodyParams) to_struct() C.stretched_body_params_t {
	var c C.stretched_body_params_t
	c.numPoints = C.int(len(p.Points))
	c.normal = p.Normal.val
	c.length = C.double(p.Length)
	if len(p.Points) > 0 {
		c.points = (*C.pnt3d_t)(C.malloc(C.size_t(len(p.Points)) * C.sizeof_pnt3d_t))
		for i, pt := range p.Points {
			*(*C.pnt3d_t)(unsafe.Pointer(uintptr(unsafe.Pointer(c.points)) + uintptr(i)*C.sizeof_pnt3d_t)) = pt.val
		}
	}
	return c
}

func CreateStretchedBody(params StretchedBodyParams) *Shape {
	shp := C.create_stretched_body(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateStretchedBodyWithPlace(params StretchedBodyParams, basePoint Point3, axisDir Dir3) *Shape {
	shp := C.create_stretched_body_with_place(params.to_struct(), basePoint.val, axisDir.val)
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

type InsulatorStringParams struct {
	Count            int32
	Spacing          float32
	InsulatorCount   int32
	Height           float32
	BigSkirtRadius   float32
	SmallSkirtRadius float32
	Radius           float32
	FrontLength      float32
	BackLength       float32
	SplitCount       int32
}

func (p *InsulatorStringParams) to_struct() C.insulator_string_params_t {
	var c C.insulator_string_params_t
	c.count = C.int(p.Count)
	c.spacing = C.double(p.Spacing)
	c.insulatorCount = C.int(p.InsulatorCount)
	c.height = C.double(p.Height)
	c.bigSkirtRadius = C.double(p.BigSkirtRadius)
	c.smallSkirtRadius = C.double(p.SmallSkirtRadius)
	c.radius = C.double(p.Radius)
	c.frontLength = C.double(p.FrontLength)
	c.backLength = C.double(p.BackLength)
	c.splitCount = C.int(p.SplitCount)
	return c
}

func CreateInsulatorString(params InsulatorStringParams) *Shape {
	shp := C.create_insulator_string(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateInsulatorStringWithPlace(params InsulatorStringParams, position Point3, direction Dir3, upDirection Dir3) *Shape {
	shp := C.create_insulator_string_with_place(params.to_struct(), position.val, direction.val, upDirection.val)
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

type RectangularFixedPlateParams struct {
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

func (p *RectangularFixedPlateParams) to_struct() C.rectangular_fixed_plate_params_t {
	var c C.rectangular_fixed_plate_params_t
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

func CreateRectangularFixedPlate(params RectangularFixedPlateParams) *Shape {
	shp := C.create_rectangular_fixed_plate(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateRectangularFixedPlateWithPlace(params RectangularFixedPlateParams, position Point3, lengthDir Dir3, widthDir Dir3) *Shape {
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

func CreateWireCenterline(params WireParams) *Wire {
	cParams := params.to_struct()
	defer freeWireParams(cParams)

	wire := C.create_wire_centerline(cParams)
	w := &Wire{inner: &innerWire{val: wire}}
	runtime.SetFinalizer(w.inner, (*innerWire).free)
	return w
}

func SampleWirePoints(params WireParams, tessellation float64) []Point3 {
	cParams := params.to_struct()
	defer freeWireParams(cParams)

	var outCount C.int
	cPoints := C.sample_wire_points(cParams, C.double(tessellation), &outCount)
	defer C.free(unsafe.Pointer(cPoints))

	points := make([]Point3, outCount)
	for i := 0; i < int(outCount); i++ {
		points[i] = Point3{
			val: *(*C.pnt3d_t)(unsafe.Pointer(uintptr(unsafe.Pointer(cPoints)) + uintptr(i)*C.sizeof_pnt3d_t)),
		}
	}
	return points
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

func CreateCableCenterline(params CableParams) *Wire {
	cParams := params.to_struct()
	defer freeCableParams(cParams)
	wire := C.create_cable_centerline(cParams)
	w := &Wire{inner: &innerWire{val: wire}}
	runtime.SetFinalizer(w.inner, (*innerWire).free)
	return w
}

func CreateCableWithPlace(params CableParams, position Point3, direction Dir3, upDirection Dir3) *Shape {
	cParams := params.to_struct()
	defer freeCableParams(cParams)

	shp := C.create_cable_with_place(cParams, position.val, direction.val, upDirection.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func SampleCablePoints(params CableParams, tessellation float64) []Point3 {
	cParams := params.to_struct()
	defer freeCableParams(cParams)

	var outCount C.int
	cPoints := C.sample_cable_points(cParams, C.double(tessellation), &outCount)
	defer C.free(unsafe.Pointer(cPoints))

	points := make([]Point3, outCount)
	for i := 0; i < int(outCount); i++ {
		points[i] = Point3{
			val: *(*C.pnt3d_t)(unsafe.Pointer(uintptr(unsafe.Pointer(cPoints)) + uintptr(i)*C.sizeof_pnt3d_t)),
		}
	}
	return points
}

type CurveType int

const (
	CurveTypeLine   CurveType = 0
	CurveTypeArc    CurveType = 1
	CurveTypeBezier CurveType = 2
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

func CreateCurveCableCenterline(params CurveCableParams) *Wire {
	cParams := params.to_struct()
	defer freeCurveCableParams(cParams)
	wire := C.create_curve_cable_centerline(cParams)
	w := &Wire{inner: &innerWire{val: wire}}
	runtime.SetFinalizer(w.inner, (*innerWire).free)
	return w
}

func CreateCurveCableWithPlace(params CurveCableParams, position Point3, direction Dir3, upDirection Dir3) *Shape {
	cParams := params.to_struct()
	defer freeCurveCableParams(cParams)

	shp := C.create_curve_cable_with_place(cParams, position.val, direction.val, upDirection.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func SampleCurvePoints(controlPoints [][]Point3, curveTypes []CurveType, tessellation float64) []Point3 {
	var pointCounts []C.int
	var allPoints []C.pnt3d_t
	for _, points := range controlPoints {
		pointCounts = append(pointCounts, C.int(len(points)))
		for _, pt := range points {
			allPoints = append(allPoints, pt.val)
		}
	}

	var cCurveTypes []C.curve_type_t
	for _, t := range curveTypes {
		cCurveTypes = append(cCurveTypes, C.curve_type_t(t))
	}

	var outCount C.int
	cPoints := C.sample_curve_points(
		&allPoints[0],
		&pointCounts[0],
		C.int(len(controlPoints)),
		&cCurveTypes[0],
		C.int(len(curveTypes)),
		C.double(tessellation),
		&outCount,
	)
	defer C.free(unsafe.Pointer(cPoints))

	result := make([]Point3, outCount)
	for i := 0; i < int(outCount); i++ {
		result[i] = Point3{val: *(*C.pnt3d_t)(unsafe.Pointer(uintptr(unsafe.Pointer(cPoints)) + uintptr(i)*C.sizeof_pnt3d_t))}
	}

	return result
}

type AngleSteelParams struct {
	L1     float32
	L2     float32
	X      float32
	Length float32
}

func (p *AngleSteelParams) to_struct() C.angle_steel_params_t {
	var c C.angle_steel_params_t
	c.L1 = C.double(p.L1)
	c.L2 = C.double(p.L2)
	c.X = C.double(p.X)
	c.length = C.double(p.Length)
	return c
}

func CreateAngleSteel(params AngleSteelParams) *Shape {
	shp := C.create_angle_steel(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateAngleSteelWithPlace(params AngleSteelParams, position Point3, xDir Dir3, longEdgeDir Dir3) *Shape {
	shp := C.create_angle_steel_with_place(params.to_struct(), position.val, xDir.val, longEdgeDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type IShapedSteelParams struct {
	Height          float32
	FlangeWidth     float32
	WebThickness    float32
	FlangeThickness float32
	Length          float32
}

func (p *IShapedSteelParams) to_struct() C.i_shaped_steel_params_t {
	var c C.i_shaped_steel_params_t
	c.height = C.double(p.Height)
	c.flangeWidth = C.double(p.FlangeWidth)
	c.webThickness = C.double(p.WebThickness)
	c.flangeThickness = C.double(p.FlangeThickness)
	c.length = C.double(p.Length)
	return c
}

func CreateIShapedSteel(params IShapedSteelParams) *Shape {
	shp := C.create_i_shaped_steel(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateIShapedSteelWithPlace(params IShapedSteelParams, position Point3, xDir Dir3, zDir Dir3) *Shape {
	shp := C.create_i_shaped_steel_with_place(params.to_struct(), position.val, xDir.val, zDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type ChannelSteelParams struct {
	Height          float32
	FlangeWidth     float32
	WebThickness    float32
	FlangeThickness float32
	Length          float32
}

func (p *ChannelSteelParams) to_struct() C.channel_steel_params_t {
	var c C.channel_steel_params_t
	c.height = C.double(p.Height)
	c.flangeWidth = C.double(p.FlangeWidth)
	c.webThickness = C.double(p.WebThickness)
	c.flangeThickness = C.double(p.FlangeThickness)
	c.length = C.double(p.Length)
	return c
}

func CreateChannelSteel(params ChannelSteelParams) *Shape {
	shp := C.create_channel_steel(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateChannelSteelWithPlace(params ChannelSteelParams, position Point3, xDir Dir3, zDir Dir3) *Shape {
	shp := C.create_channel_steel_with_place(params.to_struct(), position.val, xDir.val, zDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type TSteelParams struct {
	Height          float32
	Width           float32
	WebThickness    float32
	FlangeThickness float32
	Length          float32
}

func (p *TSteelParams) to_struct() C.t_steel_params_t {
	var c C.t_steel_params_t
	c.height = C.double(p.Height)
	c.width = C.double(p.Width)
	c.webThickness = C.double(p.WebThickness)
	c.flangeThickness = C.double(p.FlangeThickness)
	c.length = C.double(p.Length)
	return c
}

func CreateTSteel(params TSteelParams) *Shape {
	shp := C.create_t_steel(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateTSteelWithPlace(params TSteelParams, position Point3, xDir Dir3, zDir Dir3) *Shape {
	shp := C.create_t_steel_with_place(params.to_struct(), position.val, xDir.val, zDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type BoredPileParams struct {
	H1       float32
	H2       float32
	H3       float32
	H4       float32
	D        float32
	Diameter float32
}

func (p *BoredPileParams) to_struct() C.bored_pile_params_t {
	var c C.bored_pile_params_t
	c.H1 = C.double(p.H1)
	c.H2 = C.double(p.H2)
	c.H3 = C.double(p.H3)
	c.H4 = C.double(p.H4)
	c.d = C.double(p.Diameter)
	c.D = C.double(p.D)
	return c
}

func CreateBoredPileBase(params BoredPileParams) *Shape {
	shp := C.create_bored_pile_base(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateBoredPileBaseWithPlace(params BoredPileParams, position Point3, direction Dir3) *Shape {
	shp := C.create_bored_pile_base_with_place(params.to_struct(), position.val, direction.val)
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

func CreateRockPileCapBase(params RockPileCapParams) *Shape {
	cParams := params.to_struct()
	defer func() {
		if cParams.ZPOSTARRAY != nil {
			C.free(unsafe.Pointer(cParams.ZPOSTARRAY))
		}
	}()

	shp := C.create_rock_pile_cap_base(cParams)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateRockPileCapBaseWithPlace(params RockPileCapParams, position Point3, direction Dir3) *Shape {
	cParams := params.to_struct()
	defer func() {
		if cParams.ZPOSTARRAY != nil {
			C.free(unsafe.Pointer(cParams.ZPOSTARRAY))
		}
	}()

	shp := C.create_rock_pile_cap_base_with_place(cParams, position.val, direction.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type PileCapParams struct {
	H1        float32
	H2        float32
	H3        float32
	H4        float32
	H5        float32
	H6        float32
	D         float32
	Diameter  float32
	B         float32
	B1        float32
	L1        float32
	E1        float32
	E2        float32
	CS        int32
	ZCount    int32
	ZPosArray []Point3
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

	if len(p.ZPosArray) > 0 {
		c.ZPOSTARRAY = (*C.pnt3d_t)(C.malloc(C.size_t(len(p.ZPosArray)) * C.sizeof_pnt3d_t))
		for i, pos := range p.ZPosArray {
			*(*C.pnt3d_t)(unsafe.Pointer(uintptr(unsafe.Pointer(c.ZPOSTARRAY)) + uintptr(i)*C.sizeof_pnt3d_t)) = pos.val
		}
	}
	return c
}

func CreatePileCapBase(params PileCapParams) *Shape {
	cParams := params.to_struct()
	defer func() {
		if cParams.ZPOSTARRAY != nil {
			C.free(unsafe.Pointer(cParams.ZPOSTARRAY))
		}
	}()

	shp := C.create_pile_cap_base(cParams)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreatePileCapBaseWithPlace(params PileCapParams, position Point3, direction Dir3) *Shape {
	cParams := params.to_struct()
	defer func() {
		if cParams.ZPOSTARRAY != nil {
			C.free(unsafe.Pointer(cParams.ZPOSTARRAY))
		}
	}()

	shp := C.create_pile_cap_base_with_place(cParams, position.val, direction.val)
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

func CreateRockAnchorBase(params RockAnchorParams) *Shape {
	cParams := params.to_struct()
	defer func() {
		if cParams.ZPOSTARRAY != nil {
			C.free(unsafe.Pointer(cParams.ZPOSTARRAY))
		}
	}()

	shp := C.create_rock_anchor_base(cParams)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateRockAnchorBaseWithPlace(params RockAnchorParams, position Point3, direction Dir3) *Shape {
	cParams := params.to_struct()
	defer func() {
		if cParams.ZPOSTARRAY != nil {
			C.free(unsafe.Pointer(cParams.ZPOSTARRAY))
		}
	}()

	shp := C.create_rock_anchor_base_with_place(cParams, position.val, direction.val)
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

func CreateEmbeddedRockAnchorBase(params EmbeddedRockAnchorParams) *Shape {
	shp := C.create_embedded_rock_anchor_base(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateEmbeddedRockAnchorBaseWithPlace(params EmbeddedRockAnchorParams, position Point3, direction Dir3) *Shape {
	shp := C.create_embedded_rock_anchor_base_with_place(params.to_struct(), position.val, direction.val)
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

func CreateInclinedRockAnchorBase(params InclinedRockAnchorParams) *Shape {
	shp := C.create_inclined_rock_anchor_base(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateInclinedRockAnchorBaseWithPlace(params InclinedRockAnchorParams, position Point3, direction Dir3) *Shape {
	shp := C.create_inclined_rock_anchor_base_with_place(params.to_struct(), position.val, direction.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type ExcavatedBaseParams struct {
	H1       float32
	H2       float32
	H3       float32
	D        float32
	Diameter float32
	Alpha1   float32
	Alpha2   float32
}

func (p *ExcavatedBaseParams) to_struct() C.excavated_base_params_t {
	var c C.excavated_base_params_t
	c.H1 = C.double(p.H1)
	c.H2 = C.double(p.H2)
	c.H3 = C.double(p.H3)
	c.d = C.double(p.Diameter)
	c.D = C.double(p.D)
	c.alpha1 = C.double(p.Alpha1)
	c.alpha2 = C.double(p.Alpha2)
	return c
}

func CreateExcavatedBase(params ExcavatedBaseParams) *Shape {
	shp := C.create_excavated_base(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateExcavatedBaseWithPlace(params ExcavatedBaseParams, position Point3, direction Dir3) *Shape {
	shp := C.create_excavated_base_with_place(params.to_struct(), position.val, direction.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type StepBaseParams struct {
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

func (p *StepBaseParams) to_struct() C.step_base_params_t {
	var c C.step_base_params_t
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

func CreateStepBase(params StepBaseParams) *Shape {
	shp := C.create_step_base(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateStepBaseWithPlace(params StepBaseParams, position Point3, direction Dir3) *Shape {
	shp := C.create_step_base_with_place(params.to_struct(), position.val, direction.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type StepPlateBaseParams struct {
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

func (p *StepPlateBaseParams) to_struct() C.step_plate_base_params_t {
	var c C.step_plate_base_params_t
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

func CreateStepPlateBase(params StepPlateBaseParams) *Shape {
	shp := C.create_step_plate_base(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateStepPlateBaseWithPlace(params StepPlateBaseParams, position Point3, direction Dir3) *Shape {
	shp := C.create_step_plate_base_with_place(params.to_struct(), position.val, direction.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type SlopedBaseBaseParams struct {
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

func (p *SlopedBaseBaseParams) to_struct() C.sloped_base_base_params_t {
	var c C.sloped_base_base_params_t
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

func CreateSlopedBaseBase(params SlopedBaseBaseParams) *Shape {
	shp := C.create_sloped_base_base(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateSlopedBaseBaseWithPlace(params SlopedBaseBaseParams, position Point3, direction Dir3) *Shape {
	shp := C.create_sloped_base_base_with_place(params.to_struct(), position.val, direction.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type CompositeCaissonBaseParams struct {
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

func (p *CompositeCaissonBaseParams) to_struct() C.composite_caisson_base_params_t {
	var c C.composite_caisson_base_params_t
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

func CreateCompositeCaissonBase(params CompositeCaissonBaseParams) *Shape {
	shp := C.create_composite_caisson_base(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateCompositeCaissonBaseWithPlace(params CompositeCaissonBaseParams, position Point3, direction Dir3) *Shape {
	shp := C.create_composite_caisson_base_with_place(params.to_struct(), position.val, direction.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type RaftBaseParams struct {
	H1    float32
	H2    float32
	H3    float32
	Beam1 float32
	Beam2 float32
	B1    float32
	B2    float32
	L1    float32
	L2    float32
}

func (p *RaftBaseParams) to_struct() C.raft_base_params_t {
	var c C.raft_base_params_t
	c.H1 = C.double(p.H1)
	c.H2 = C.double(p.H2)
	c.H3 = C.double(p.H3)
	c.b1 = C.double(p.Beam1)
	c.b2 = C.double(p.Beam2)
	c.B1 = C.double(p.B1)
	c.B2 = C.double(p.B2)
	c.L1 = C.double(p.L1)
	c.L2 = C.double(p.L2)
	return c
}

func CreateRaftBase(params RaftBaseParams) *Shape {
	shp := C.create_raft_base(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateRaftBaseWithPlace(params RaftBaseParams, position Point3, direction Dir3) *Shape {
	shp := C.create_raft_base_with_place(params.to_struct(), position.val, direction.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type DirectBuriedBaseParams struct {
	H1       float32
	H2       float32
	D        float32
	Diameter float32
	B        float32
	T        float32
}

func (p *DirectBuriedBaseParams) to_struct() C.direct_buried_base_params_t {
	var c C.direct_buried_base_params_t
	c.H1 = C.double(p.H1)
	c.H2 = C.double(p.H2)
	c.d = C.double(p.Diameter)
	c.D = C.double(p.D)
	c.B = C.double(p.B)
	c.t = C.double(p.T)
	return c
}

func CreateDirectBuriedBase(params DirectBuriedBaseParams) *Shape {
	shp := C.create_direct_buried_base(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateDirectBuriedBaseWithPlace(params DirectBuriedBaseParams, position Point3, direction Dir3) *Shape {
	shp := C.create_direct_buried_base_with_place(params.to_struct(), position.val, direction.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type SteelSleeveBaseParams struct {
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

func (p *SteelSleeveBaseParams) to_struct() C.steel_sleeve_base_params_t {
	var c C.steel_sleeve_base_params_t
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

func CreateSteelSleeveBase(params SteelSleeveBaseParams) *Shape {
	shp := C.create_steel_sleeve_base(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateSteelSleeveBaseWithPlace(params SteelSleeveBaseParams, position Point3, direction Dir3) *Shape {
	shp := C.create_steel_sleeve_base_with_place(params.to_struct(), position.val, direction.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type PrecastColumnBaseParams struct {
	H1 float32
	H2 float32
	H3 float32
	D  float32
	B1 float32
	B2 float32
	L1 float32
	L2 float32
}

func (p *PrecastColumnBaseParams) to_struct() C.precast_column_base_params_t {
	var c C.precast_column_base_params_t
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

func CreatePrecastColumnBase(params PrecastColumnBaseParams) *Shape {
	shp := C.create_precast_column_base(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreatePrecastColumnBaseWithPlace(params PrecastColumnBaseParams, position Point3, direction Dir3) *Shape {
	shp := C.create_precast_column_base_with_place(params.to_struct(), position.val, direction.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type PrecastPinnedBaseParams struct {
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

func (p *PrecastPinnedBaseParams) to_struct() C.precast_pinned_base_params_t {
	var c C.precast_pinned_base_params_t
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

func CreatePrecastPinnedBase(params PrecastPinnedBaseParams) *Shape {
	shp := C.create_precast_pinned_base(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreatePrecastPinnedBaseWithPlace(params PrecastPinnedBaseParams, position Point3, direction Dir3) *Shape {
	shp := C.create_precast_pinned_base_with_place(params.to_struct(), position.val, direction.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type PrecastMetalSupportBaseParams struct {
	H1    float32
	H2    float32
	H3    float32
	H4    float32
	B1    float32
	B2    float32
	Beam1 float32
	Beam2 float32
	L1    float32
	L2    float32
	S1    float32
	S2    float32
	N1    int32
	N2    int32
	HX    []float32
}

func (p *PrecastMetalSupportBaseParams) to_struct() C.precast_metal_support_base_params_t {
	var c C.precast_metal_support_base_params_t
	c.H1 = C.double(p.H1)
	c.H2 = C.double(p.H2)
	c.H3 = C.double(p.H3)
	c.H4 = C.double(p.H4)
	c.b1 = C.double(p.Beam1)
	c.b2 = C.double(p.Beam2)
	c.B1 = C.double(p.B1)
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

func CreatePrecastMetalSupportBase(params PrecastMetalSupportBaseParams) *Shape {
	cParams := params.to_struct()
	defer func() {
		if cParams.HX != nil {
			C.free(unsafe.Pointer(cParams.HX))
		}
	}()

	shp := C.create_precast_metal_support_base(cParams)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreatePrecastMetalSupportBaseWithPlace(params PrecastMetalSupportBaseParams, position Point3, direction Dir3) *Shape {
	cParams := params.to_struct()
	defer func() {
		if cParams.HX != nil {
			C.free(unsafe.Pointer(cParams.HX))
		}
	}()

	shp := C.create_precast_metal_support_base_with_place(cParams, position.val, direction.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type PrecastConcreteSupportBaseParams struct {
	H1    float32
	H2    float32
	H3    float32
	H4    float32
	H5    float32
	Beam1 float32
	Beam2 float32
	Beam3 float32
	B1    float32
	B2    float32
	L1    float32
	L2    float32
	S1    float32
	N1    int32
}

func (p *PrecastConcreteSupportBaseParams) to_struct() C.precast_concrete_support_base_params_t {
	var c C.precast_concrete_support_base_params_t
	c.H1 = C.double(p.H1)
	c.H2 = C.double(p.H2)
	c.H3 = C.double(p.H3)
	c.H4 = C.double(p.H4)
	c.H5 = C.double(p.H5)
	c.b1 = C.double(p.Beam1)
	c.b2 = C.double(p.Beam2)
	c.b3 = C.double(p.Beam3)
	c.B1 = C.double(p.B1)
	c.B2 = C.double(p.B2)
	c.L1 = C.double(p.L1)
	c.L2 = C.double(p.L2)
	c.S1 = C.double(p.S1)
	c.n1 = C.int(p.N1)
	return c
}

func CreatePrecastConcreteSupportBase(params PrecastConcreteSupportBaseParams) *Shape {
	shp := C.create_precast_concrete_support_base(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreatePrecastConcreteSupportBaseWithPlace(params PrecastConcreteSupportBaseParams, position Point3, direction Dir3) *Shape {
	shp := C.create_precast_concrete_support_base_with_place(params.to_struct(), position.val, direction.val)
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

func CreateTransmissionCenterline(params TransmissionLineParams, startPoint Point3, endPoint Point3) *Wire {
	cParams := params.to_struct()
	wire := C.create_transmission_centerline(cParams, startPoint.val, endPoint.val)
	w := &Wire{inner: &innerWire{val: wire}}
	runtime.SetFinalizer(w.inner, (*innerWire).free)
	return w
}

func SampleTransmissionLinePoints(params TransmissionLineParams, startPoint, endPoint Point3, tessellation float64) []Point3 {
	cParams := params.to_struct()
	defer C.free(unsafe.Pointer(cParams.ctype))

	var outCount C.int
	cPoints := C.sample_transmission_line_points(
		cParams,
		startPoint.val,
		endPoint.val,
		C.double(tessellation),
		&outCount,
	)
	defer C.free(unsafe.Pointer(cPoints))

	points := make([]Point3, outCount)
	for i := 0; i < int(outCount); i++ {
		points[i] = Point3{
			val: *(*C.pnt3d_t)(unsafe.Pointer(uintptr(unsafe.Pointer(cPoints)) + uintptr(i)*C.sizeof_pnt3d_t)),
		}
	}
	return points
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

type WasherShapeType int32

const (
	WasherShapeTypeSquare WasherShapeType = 1 // 方形垫片
	WasherShapeTypeRound  WasherShapeType = 2 // 圆形垫片
)

type SingleHookAnchorParams struct {
	BoltDiameter       float32
	ExposedLength      float32
	NutCount           int32
	NutHeight          float32
	NutOD              float32
	WasherCount        int32
	WasherShape        WasherShapeType
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
	WasherShape         WasherShapeType
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
	WasherShape        WasherShapeType
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
	WasherShape         WasherShapeType
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
	WasherShape       WasherShapeType
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
	WasherShape       WasherShapeType
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

type CableWireParams struct {
	Points          []Point3 // 电缆路径点集
	OutsideDiameter float32  // 电缆外径(mm)
}

func (p *CableWireParams) to_struct() C.cable_wire_params_t {
	var c C.cable_wire_params_t
	c.numPoints = C.int(len(p.Points))
	c.outsideDiameter = C.double(p.OutsideDiameter)

	if len(p.Points) > 0 {
		c.points = (*C.pnt3d_t)(C.malloc(C.size_t(len(p.Points)) * C.sizeof_pnt3d_t))
		for i, pt := range p.Points {
			*(*C.pnt3d_t)(unsafe.Pointer(uintptr(unsafe.Pointer(c.points)) + uintptr(i)*C.sizeof_pnt3d_t)) = pt.val
		}
	}
	return c
}

func CreateCableWire(params CableWireParams) *Shape {
	cParams := params.to_struct()
	defer C.free(unsafe.Pointer(cParams.points))

	shp := C.create_cable_wire(cParams)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateCableWireWithPlace(params CableWireParams, position Point3, direction Dir3, upDirection Dir3) *Shape {
	cParams := params.to_struct()
	defer C.free(unsafe.Pointer(cParams.points))

	shp := C.create_cable_wire_with_place(cParams, position.val, direction.val, upDirection.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type PoleTowerNode struct {
	ID       string
	Position Point3
}

type PoleTowerMember struct {
	ID            string
	StartNodeID   string
	EndNodeID     string
	Type          int32
	Specification string
	Material      string
	XDirection    Dir3
	YDirection    Dir3
	End1Diameter  float32
	End2Diameter  float32
	Thickness     float32
	Sides         int32
}

type PoleTowerAttachment struct {
	Name     string
	Type     int32
	Position Point3
}

type PoleTowerLeg struct {
	ID             string
	CommonHeight   float32
	SpecificHeight float32
	Nodes          []PoleTowerNode
}

type PoleTowerBody struct {
	ID     string
	Height float32
	Nodes  []PoleTowerNode
	Legs   []PoleTowerLeg
}

type PoleTowerHeight struct {
	Value  float32
	BodyID string
	LegID  string
}

type PoleTowerParams struct {
	Heights     []PoleTowerHeight
	Bodies      []PoleTowerBody
	Members     []PoleTowerMember
	Attachments []PoleTowerAttachment
}

func (p *PoleTowerNode) to_struct() C.pole_tower_node_t {
	var c C.pole_tower_node_t
	c.id = C.CString(p.ID)
	c.position = p.Position.val
	return c
}

func (p *PoleTowerMember) to_struct() C.pole_tower_member_t {
	var c C.pole_tower_member_t
	c.id = C.CString(p.ID)
	c.startNodeId = C.CString(p.StartNodeID)
	c.endNodeId = C.CString(p.EndNodeID)
	c.ctype = C.int(p.Type)
	c.specification = C.CString(p.Specification)
	c.material = C.CString(p.Material)
	c.xDirection = p.XDirection.val
	c.yDirection = p.YDirection.val
	c.end1Diameter = C.double(p.End1Diameter)
	c.end2Diameter = C.double(p.End2Diameter)
	c.thickness = C.double(p.Thickness)
	c.sides = C.int(p.Sides)
	return c
}

func (p *PoleTowerAttachment) to_struct() C.pole_tower_attachment_t {
	var c C.pole_tower_attachment_t
	c.name = C.CString(p.Name)
	c.ctype = C.int(p.Type)
	c.position = p.Position.val
	return c
}

func (p *PoleTowerLeg) to_struct() C.pole_tower_leg_t {
	var c C.pole_tower_leg_t
	c.id = C.CString(p.ID)
	c.commonHeight = C.double(p.CommonHeight)
	c.specificHeight = C.double(p.SpecificHeight)

	if len(p.Nodes) > 0 {
		c.nodes = (*C.pole_tower_node_t)(C.malloc(C.size_t(len(p.Nodes)) * C.sizeof_pole_tower_node_t))
		for i, node := range p.Nodes {
			*(*C.pole_tower_node_t)(unsafe.Pointer(uintptr(unsafe.Pointer(c.nodes)) + uintptr(i)*C.sizeof_pole_tower_node_t)) = node.to_struct()
		}
	}
	c.nodeCount = C.int(len(p.Nodes))
	return c
}

func (p *PoleTowerBody) to_struct() C.pole_tower_body_t {
	var c C.pole_tower_body_t
	c.id = C.CString(p.ID)
	c.height = C.double(p.Height)

	if len(p.Nodes) > 0 {
		c.nodes = (*C.pole_tower_node_t)(C.malloc(C.size_t(len(p.Nodes)) * C.sizeof_pole_tower_node_t))
		for i, node := range p.Nodes {
			*(*C.pole_tower_node_t)(unsafe.Pointer(uintptr(unsafe.Pointer(c.nodes)) + uintptr(i)*C.sizeof_pole_tower_node_t)) = node.to_struct()
		}
	}
	c.nodeCount = C.int(len(p.Nodes))

	if len(p.Legs) > 0 {
		c.legs = (*C.pole_tower_leg_t)(C.malloc(C.size_t(len(p.Legs)) * C.sizeof_pole_tower_leg_t))
		for i, leg := range p.Legs {
			*(*C.pole_tower_leg_t)(unsafe.Pointer(uintptr(unsafe.Pointer(c.legs)) + uintptr(i)*C.sizeof_pole_tower_leg_t)) = leg.to_struct()
		}
	}
	c.legCount = C.int(len(p.Legs))
	return c
}

func (p *PoleTowerHeight) to_struct() C.pole_tower_height_t {
	var c C.pole_tower_height_t
	c.value = C.double(p.Value)
	c.bodyId = C.CString(p.BodyID)
	c.legId = C.CString(p.LegID)
	return c
}

func (p *PoleTowerParams) to_struct() C.pole_tower_params_t {
	var c C.pole_tower_params_t

	if len(p.Heights) > 0 {
		c.heights = (*C.pole_tower_height_t)(C.malloc(C.size_t(len(p.Heights)) * C.sizeof_pole_tower_height_t))
		for i, height := range p.Heights {
			*(*C.pole_tower_height_t)(unsafe.Pointer(uintptr(unsafe.Pointer(c.heights)) + uintptr(i)*C.sizeof_pole_tower_height_t)) = height.to_struct()
		}
	}
	c.heightCount = C.int(len(p.Heights))

	if len(p.Bodies) > 0 {
		c.bodies = (*C.pole_tower_body_t)(C.malloc(C.size_t(len(p.Bodies)) * C.sizeof_pole_tower_body_t))
		for i, body := range p.Bodies {
			*(*C.pole_tower_body_t)(unsafe.Pointer(uintptr(unsafe.Pointer(c.bodies)) + uintptr(i)*C.sizeof_pole_tower_body_t)) = body.to_struct()
		}
	}
	c.bodyCount = C.int(len(p.Bodies))

	if len(p.Members) > 0 {
		c.members = (*C.pole_tower_member_t)(C.malloc(C.size_t(len(p.Members)) * C.sizeof_pole_tower_member_t))
		for i, member := range p.Members {
			*(*C.pole_tower_member_t)(unsafe.Pointer(uintptr(unsafe.Pointer(c.members)) + uintptr(i)*C.sizeof_pole_tower_member_t)) = member.to_struct()
		}
	}
	c.memberCount = C.int(len(p.Members))

	if len(p.Attachments) > 0 {
		c.attachments = (*C.pole_tower_attachment_t)(C.malloc(C.size_t(len(p.Attachments)) * C.sizeof_pole_tower_attachment_t))
		for i, attachment := range p.Attachments {
			*(*C.pole_tower_attachment_t)(unsafe.Pointer(uintptr(unsafe.Pointer(c.attachments)) + uintptr(i)*C.sizeof_pole_tower_attachment_t)) = attachment.to_struct()
		}
	}
	c.attachmentCount = C.int(len(p.Attachments))

	return c
}

func CreatePoleTower(params PoleTowerParams) *Shape {
	cParams := params.to_struct()
	defer func() {
		if cParams.heights != nil {
			for i := 0; i < int(cParams.heightCount); i++ {
				height := *(*C.pole_tower_height_t)(unsafe.Pointer(uintptr(unsafe.Pointer(cParams.heights)) + uintptr(i)*C.sizeof_pole_tower_height_t))
				C.free(unsafe.Pointer(height.bodyId))
				C.free(unsafe.Pointer(height.legId))
			}
			C.free(unsafe.Pointer(cParams.heights))
		}
		if cParams.bodies != nil {
			for i := 0; i < int(cParams.bodyCount); i++ {
				body := *(*C.pole_tower_body_t)(unsafe.Pointer(uintptr(unsafe.Pointer(cParams.bodies)) + uintptr(i)*C.sizeof_pole_tower_body_t))
				C.free(unsafe.Pointer(body.id))
				if body.nodes != nil {
					for j := 0; j < int(body.nodeCount); j++ {
						node := *(*C.pole_tower_node_t)(unsafe.Pointer(uintptr(unsafe.Pointer(body.nodes)) + uintptr(j)*C.sizeof_pole_tower_node_t))
						C.free(unsafe.Pointer(node.id))
					}
					C.free(unsafe.Pointer(body.nodes))
				}
				if body.legs != nil {
					for j := 0; j < int(body.legCount); j++ {
						leg := *(*C.pole_tower_leg_t)(unsafe.Pointer(uintptr(unsafe.Pointer(body.legs)) + uintptr(j)*C.sizeof_pole_tower_leg_t))
						C.free(unsafe.Pointer(leg.id))
						if leg.nodes != nil {
							for k := 0; k < int(leg.nodeCount); k++ {
								node := *(*C.pole_tower_node_t)(unsafe.Pointer(uintptr(unsafe.Pointer(leg.nodes)) + uintptr(k)*C.sizeof_pole_tower_node_t))
								C.free(unsafe.Pointer(node.id))
							}
							C.free(unsafe.Pointer(leg.nodes))
						}
					}
					C.free(unsafe.Pointer(body.legs))
				}
			}
			C.free(unsafe.Pointer(cParams.bodies))
		}
		if cParams.members != nil {
			for i := 0; i < int(cParams.memberCount); i++ {
				member := *(*C.pole_tower_member_t)(unsafe.Pointer(uintptr(unsafe.Pointer(cParams.members)) + uintptr(i)*C.sizeof_pole_tower_member_t))
				C.free(unsafe.Pointer(member.id))
				C.free(unsafe.Pointer(member.startNodeId))
				C.free(unsafe.Pointer(member.endNodeId))
				C.free(unsafe.Pointer(member.specification))
				C.free(unsafe.Pointer(member.material))
			}
			C.free(unsafe.Pointer(cParams.members))
		}
		if cParams.attachments != nil {
			for i := 0; i < int(cParams.attachmentCount); i++ {
				attachment := *(*C.pole_tower_attachment_t)(unsafe.Pointer(uintptr(unsafe.Pointer(cParams.attachments)) + uintptr(i)*C.sizeof_pole_tower_attachment_t))
				C.free(unsafe.Pointer(attachment.name))
			}
			C.free(unsafe.Pointer(cParams.attachments))
		}
	}()

	shp := C.create_pole_tower(cParams)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreatePoleTowerWithPlace(params PoleTowerParams, position Point3, normal Dir3, xDir Dir3) *Shape {
	cParams := params.to_struct()
	defer func() {
		if cParams.heights != nil {
			for i := 0; i < int(cParams.heightCount); i++ {
				height := *(*C.pole_tower_height_t)(unsafe.Pointer(uintptr(unsafe.Pointer(cParams.heights)) + uintptr(i)*C.sizeof_pole_tower_height_t))
				C.free(unsafe.Pointer(height.bodyId))
				C.free(unsafe.Pointer(height.legId))
			}
			C.free(unsafe.Pointer(cParams.heights))
		}
		if cParams.bodies != nil {
			for i := 0; i < int(cParams.bodyCount); i++ {
				body := *(*C.pole_tower_body_t)(unsafe.Pointer(uintptr(unsafe.Pointer(cParams.bodies)) + uintptr(i)*C.sizeof_pole_tower_body_t))
				C.free(unsafe.Pointer(body.id))
				if body.nodes != nil {
					for j := 0; j < int(body.nodeCount); j++ {
						node := *(*C.pole_tower_node_t)(unsafe.Pointer(uintptr(unsafe.Pointer(body.nodes)) + uintptr(j)*C.sizeof_pole_tower_node_t))
						C.free(unsafe.Pointer(node.id))
					}
					C.free(unsafe.Pointer(body.nodes))
				}
				if body.legs != nil {
					for j := 0; j < int(body.legCount); j++ {
						leg := *(*C.pole_tower_leg_t)(unsafe.Pointer(uintptr(unsafe.Pointer(body.legs)) + uintptr(j)*C.sizeof_pole_tower_leg_t))
						C.free(unsafe.Pointer(leg.id))
						if leg.nodes != nil {
							for k := 0; k < int(leg.nodeCount); k++ {
								node := *(*C.pole_tower_node_t)(unsafe.Pointer(uintptr(unsafe.Pointer(leg.nodes)) + uintptr(k)*C.sizeof_pole_tower_node_t))
								C.free(unsafe.Pointer(node.id))
							}
							C.free(unsafe.Pointer(leg.nodes))
						}
					}
					C.free(unsafe.Pointer(body.legs))
				}
			}
			C.free(unsafe.Pointer(cParams.bodies))
		}
		if cParams.members != nil {
			for i := 0; i < int(cParams.memberCount); i++ {
				member := *(*C.pole_tower_member_t)(unsafe.Pointer(uintptr(unsafe.Pointer(cParams.members)) + uintptr(i)*C.sizeof_pole_tower_member_t))
				C.free(unsafe.Pointer(member.id))
				C.free(unsafe.Pointer(member.startNodeId))
				C.free(unsafe.Pointer(member.endNodeId))
				C.free(unsafe.Pointer(member.specification))
				C.free(unsafe.Pointer(member.material))
			}
			C.free(unsafe.Pointer(cParams.members))
		}
		if cParams.attachments != nil {
			for i := 0; i < int(cParams.attachmentCount); i++ {
				attachment := *(*C.pole_tower_attachment_t)(unsafe.Pointer(uintptr(unsafe.Pointer(cParams.attachments)) + uintptr(i)*C.sizeof_pole_tower_attachment_t))
				C.free(unsafe.Pointer(attachment.name))
			}
			C.free(unsafe.Pointer(cParams.attachments))
		}
	}()

	shp := C.create_pole_tower_with_place(cParams, position.val, normal.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type CableJointParams struct {
	Length         float32
	OuterDiameter  float32
	TerminalLength float32
	InnerDiameter  float32
}

func (p *CableJointParams) to_struct() C.cable_joint_params_t {
	var c C.cable_joint_params_t
	c.length = C.double(p.Length)
	c.outerDiameter = C.double(p.OuterDiameter)
	c.terminalLength = C.double(p.TerminalLength)
	c.innerDiameter = C.double(p.InnerDiameter)
	return c
}

func CreateCableJoint(params CableJointParams) *Shape {
	shp := C.create_cable_joint(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateCableJointWithPlace(params CableJointParams, position Point3, direction Dir3, xDir Dir3) *Shape {
	shp := C.create_cable_joint_with_place(params.to_struct(), position.val, direction.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type OpticalFiberBoxParams struct {
	Length float32
	Height float32
	Width  float32
}

func (p *OpticalFiberBoxParams) to_struct() C.optical_fiber_box_params_t {
	var c C.optical_fiber_box_params_t
	c.length = C.double(p.Length)
	c.height = C.double(p.Height)
	c.width = C.double(p.Width)
	return c
}

func CreateOpticalFiberBox(params OpticalFiberBoxParams) *Shape {
	shp := C.create_optical_fiber_box(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateOpticalFiberBoxWithPlace(params OpticalFiberBoxParams, position Point3, direction Dir3, xDir Dir3) *Shape {
	shp := C.create_optical_fiber_box_with_place(params.to_struct(), position.val, direction.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type CableTerminalType int

const (
	CableTerminalTypeOutdoor CableTerminalType = 1 // 户外
	CableTerminalTypeGIS     CableTerminalType = 2 // 户内
	CableTerminalTypeDry     CableTerminalType = 3 // 干式
)

type CableTerminalParams struct {
	Sort           CableTerminalType // 类型 SORT: 1-户外, 2-户内(GIS), 3-干式
	Height         float32           // 总高度 H (mm)
	TopDiameter    float32           // 上部直径 L1 (mm)
	BottomDiameter float32           // 下部直径 d (mm)
	TailDiameter   float32           // 尾管直径 D3 (mm)
	TailHeight     float32           // 尾管高度 WH (mm)

	// 伞裙参数 (仅户外和干式终端使用)
	SkirtCount               int32   // 伞裙片数 N
	UpperSkirtTopDiameter    float32 // 伞裙1上部直径 SD (mm)
	UpperSkirtBottomDiameter float32 // 伞裙1下部直径 SDI (mm)
	LowerSkirtTopDiameter    float32 // 伞裙2上部直径 BD (mm)
	LowerSkirtBottomDiameter float32 // 伞裙2下部直径 BDI (mm)
	SkirtSectionHeight       float32 // 伞裙节高度 h (mm)

	// 端子参数
	UpperTerminalLength   float32 // 上端子长度 LI (mm)
	UpperTerminalDiameter float32 // 上端子直径 ZDI (mm)
	LowerTerminalLength   float32 // 下端子长度 L2 (mm)
	LowerTerminalDiameter float32 // 下端子直径 ZD2 (mm)

	// 连接孔参数
	Hole1Diameter float32 // 连接孔1直径 Φ1 (mm)
	Hole2Diameter float32 // 连接孔2直径 Φ2 (mm)
	Hole1Distance float32 // 连接孔1端距离 dl (mm)
	HoleSpacing   float32 // 连接孔1到2间距 d2 (mm)

	// 户外终端专用参数
	FlangeHoleDiameter     float32 // 法兰盘连接孔直径 FD (mm)
	FlangeHoleSpacing      float32 // 法兰盘连接孔间距 KD (mm)
	FlangeWidth            float32 // 法兰盘宽度 PD (mm)
	FlangeCenterHoleRadius float32 // 法兰盘中心孔半径 PR (mm)
	FlangeChamferRadius    float32 // 法兰盘边缘倒角半径 BR (mm)
	FlangeOpeningWidth     float32 // 法兰盘开口宽度 K (mm)
	FlangeBoltHeight       float32 // 法兰盘螺栓高度 H (mm)
}

func (p *CableTerminalParams) to_struct() C.cable_terminal_params_t {
	var c C.cable_terminal_params_t
	c.sort = C.int(p.Sort)
	c.height = C.double(p.Height)
	c.topDiameter = C.double(p.TopDiameter)
	c.bottomDiameter = C.double(p.BottomDiameter)
	c.tailDiameter = C.double(p.TailDiameter)
	c.tailHeight = C.double(p.TailHeight)
	c.skirtCount = C.int(p.SkirtCount)
	c.upperSkirtTopDiameter = C.double(p.UpperSkirtTopDiameter)
	c.upperSkirtBottomDiameter = C.double(p.UpperSkirtBottomDiameter)
	c.lowerSkirtTopDiameter = C.double(p.LowerSkirtTopDiameter)
	c.lowerSkirtBottomDiameter = C.double(p.LowerSkirtBottomDiameter)
	c.skirtSectionHeight = C.double(p.SkirtSectionHeight)
	c.upperTerminalLength = C.double(p.UpperTerminalLength)
	c.upperTerminalDiameter = C.double(p.UpperTerminalDiameter)
	c.lowerTerminalLength = C.double(p.LowerTerminalLength)
	c.lowerTerminalDiameter = C.double(p.LowerTerminalDiameter)
	c.hole1Diameter = C.double(p.Hole1Diameter)
	c.hole2Diameter = C.double(p.Hole2Diameter)
	c.hole1Distance = C.double(p.Hole1Distance)
	c.holeSpacing = C.double(p.HoleSpacing)
	c.flangeHoleDiameter = C.double(p.FlangeHoleDiameter)
	c.flangeHoleSpacing = C.double(p.FlangeHoleSpacing)
	c.flangeWidth = C.double(p.FlangeWidth)
	c.flangeCenterHoleRadius = C.double(p.FlangeCenterHoleRadius)
	c.flangeChamferRadius = C.double(p.FlangeChamferRadius)
	c.flangeOpeningWidth = C.double(p.FlangeOpeningWidth)
	c.flangeBoltHeight = C.double(p.FlangeBoltHeight)
	return c
}

func CreateCableTerminal(params CableTerminalParams) *Shape {
	shp := C.create_cable_terminal(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateCableTerminalWithPlace(params CableTerminalParams, position Point3, direction Dir3) *Shape {
	shp := C.create_cable_terminal_with_place(params.to_struct(), position.val, direction.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type CableAccessoryType int

const (
	CableAccessoryTypeDirectGround      CableAccessoryType = 1
	CableAccessoryTypeProtectiveGround  CableAccessoryType = 2
	CableAccessoryTypeCrossInterconnect CableAccessoryType = 3
)

type CableAccessoryParams struct {
	Type              CableAccessoryType
	Length            float32
	Width             float32
	Height            float32
	PortCount         int32
	PortDiameter      float32
	BackPanelDistance float32
	SidePanelDistance float32
}

func (p *CableAccessoryParams) to_struct() C.cable_accessory_params_t {
	var c C.cable_accessory_params_t
	c.ctype = C.int(p.Type)
	c.length = C.double(p.Length)
	c.width = C.double(p.Width)
	c.height = C.double(p.Height)
	c.portCount = C.int(p.PortCount)
	c.portDiameter = C.double(p.PortDiameter)
	c.backPanelDistance = C.double(p.BackPanelDistance)
	c.sidePanelDistance = C.double(p.SidePanelDistance)
	return c
}

func CreateCableAccessory(params CableAccessoryParams) *Shape {
	shp := C.create_cable_accessory(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateCableAccessoryWithPlace(params CableAccessoryParams, position Point3, normal Dir3, xDir Dir3) *Shape {
	shp := C.create_cable_accessory_with_place(params.to_struct(), position.val, normal.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type CableBracketParams struct {
	Length            float32
	RootHeight        float32
	RootWidth         float32
	Width             float32
	TopThickness      float32
	RootThickness     float32
	ColumnMountPoints []Point3
	ClampMountPoints  []Point3
}

func (p *CableBracketParams) to_struct() C.cable_bracket_params_t {
	var c C.cable_bracket_params_t
	c.length = C.double(p.Length)
	c.rootHeight = C.double(p.RootHeight)
	c.rootWidth = C.double(p.RootWidth)
	c.width = C.double(p.Width)
	c.topThickness = C.double(p.TopThickness)
	c.rootThickness = C.double(p.RootThickness)

	if len(p.ColumnMountPoints) > 0 {
		c.columnMountPoints = (*C.pnt3d_t)(C.malloc(C.size_t(len(p.ColumnMountPoints)) * C.sizeof_pnt3d_t))
		for i, pos := range p.ColumnMountPoints {
			*(*C.pnt3d_t)(unsafe.Pointer(uintptr(unsafe.Pointer(c.columnMountPoints)) + uintptr(i)*C.sizeof_pnt3d_t)) = pos.val
		}
		c.columnMountCount = C.int(len(p.ColumnMountPoints))
	}

	if len(p.ClampMountPoints) > 0 {
		c.clampMountPoints = (*C.pnt3d_t)(C.malloc(C.size_t(len(p.ClampMountPoints)) * C.sizeof_pnt3d_t))
		for i, pos := range p.ClampMountPoints {
			*(*C.pnt3d_t)(unsafe.Pointer(uintptr(unsafe.Pointer(c.clampMountPoints)) + uintptr(i)*C.sizeof_pnt3d_t)) = pos.val
		}
		c.clampMountCount = C.int(len(p.ClampMountPoints))
	}
	return c
}

func CreateCableBracket(params CableBracketParams) *Shape {
	cParams := params.to_struct()
	defer func() {
		if cParams.columnMountPoints != nil {
			C.free(unsafe.Pointer(cParams.columnMountPoints))
		}
		if cParams.clampMountPoints != nil {
			C.free(unsafe.Pointer(cParams.clampMountPoints))
		}
	}()

	shp := C.create_cable_bracket(cParams)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateCableBracketWithPlace(params CableBracketParams, position Point3, normal Dir3, xDir Dir3) *Shape {
	cParams := params.to_struct()
	defer func() {
		if cParams.columnMountPoints != nil {
			C.free(unsafe.Pointer(cParams.columnMountPoints))
		}
		if cParams.clampMountPoints != nil {
			C.free(unsafe.Pointer(cParams.clampMountPoints))
		}
	}()

	shp := C.create_cable_bracket_with_place(cParams, position.val, normal.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type CableClampType int

const (
	CableClampSingle         CableClampType = 1
	CableClampLinear         CableClampType = 2
	CableClampContactTriple  CableClampType = 3
	CableClampSeparateTriple CableClampType = 4
)

type CableClampParams struct {
	Type      CableClampType
	Diameter  float32
	Thickness float32
	Width     float32
}

func (p *CableClampParams) to_struct() C.cable_clamp_params_t {
	var c C.cable_clamp_params_t
	c.ctype = C.int(p.Type)
	c.diameter = C.double(p.Diameter)
	c.thickness = C.double(p.Thickness)
	c.width = C.double(p.Width)
	return c
}

func CreateCableClamp(params CableClampParams) *Shape {
	shp := C.create_cable_clamp(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateCableClampWithPlace(params CableClampParams, position Point3, normal Dir3, xDir Dir3) *Shape {
	shp := C.create_cable_clamp_with_place(params.to_struct(), position.val, normal.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type CablePoleParams struct {
	Specification  string
	Length         float64
	Radius         float64
	ArcAngle       float64
	Width          float64
	FixedLegLength float64
	FixedLegWidth  float64
	Thickness      float64
	MountPoints    []Point3
}

func (p *CablePoleParams) to_struct() C.cable_pole_params_t {
	var c C.cable_pole_params_t
	c.specification = C.CString(p.Specification)
	c.length = C.double(p.Length)
	c.radius = C.double(p.Radius)
	c.arcAngle = C.double(p.ArcAngle)
	c.width = C.double(p.Width)
	c.fixedLegLength = C.double(p.FixedLegLength)
	c.fixedLegWidth = C.double(p.FixedLegWidth)
	c.thickness = C.double(p.Thickness)
	if len(p.MountPoints) > 0 {
		c.mountPoints = (*C.pnt3d_t)(C.malloc(C.size_t(len(p.MountPoints)) * C.sizeof_pnt3d_t))
		for i, pt := range p.MountPoints {
			*(*C.pnt3d_t)(unsafe.Pointer(uintptr(unsafe.Pointer(c.mountPoints)) + uintptr(i)*C.sizeof_pnt3d_t)) = pt.val
		}
		c.mountCount = C.int(len(p.MountPoints))
	}
	return c
}

func CreateCablePole(params CablePoleParams) *Shape {
	cParams := params.to_struct()
	defer func() {
		C.free(unsafe.Pointer(cParams.specification))
		if cParams.mountPoints != nil {
			C.free(unsafe.Pointer(cParams.mountPoints))
		}
	}()

	shp := C.create_cable_pole(cParams)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateCablePoleWithPlace(params CablePoleParams, position Point3, direction Dir3) *Shape {
	cParams := params.to_struct()
	defer func() {
		C.free(unsafe.Pointer(cParams.specification))
		if cParams.mountPoints != nil {
			C.free(unsafe.Pointer(cParams.mountPoints))
		}
	}()

	shp := C.create_cable_pole_with_place(cParams, position.val, direction.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type GroundFlatIronParams struct {
	Length    float64
	Height    float64
	Thickness float64
}

func (p *GroundFlatIronParams) to_struct() C.ground_flat_iron_params_t {
	var c C.ground_flat_iron_params_t
	c.length = C.double(p.Length)
	c.height = C.double(p.Height)
	c.thickness = C.double(p.Thickness)
	return c
}

func CreateGroundFlatIron(params GroundFlatIronParams) *Shape {
	cParams := params.to_struct()
	shp := C.create_ground_flat_iron(cParams)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateGroundFlatIronWithPlace(params GroundFlatIronParams, position Point3, normal Dir3, xDir Dir3) *Shape {
	cParams := params.to_struct()
	shp := C.create_ground_flat_iron_with_place(cParams, position.val, normal.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type EmbeddedPartParams struct {
	Length         float64
	Radius         float64
	Height         float64
	MaterialRadius float64
	LowerLength    float64
}

func (p *EmbeddedPartParams) to_struct() C.embedded_part_params_t {
	var c C.embedded_part_params_t
	c.length = C.double(p.Length)
	c.radius = C.double(p.Radius)
	c.height = C.double(p.Height)
	c.materialRadius = C.double(p.MaterialRadius)
	c.lowerLength = C.double(p.LowerLength)
	return c
}

func CreateEmbeddedPart(params EmbeddedPartParams) *Shape {
	cParams := params.to_struct()
	shp := C.create_embedded_part(cParams)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateEmbeddedPartWithPlace(params EmbeddedPartParams, position Point3, normal Dir3, xDir Dir3) *Shape {
	cParams := params.to_struct()
	shp := C.create_embedded_part_with_place(cParams, position.val, normal.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type UShapedRingParams struct {
	Thickness float64
	Height    float64
	Radius    float64
	Length    float64
}

func (p *UShapedRingParams) to_struct() C.u_shaped_ring_params_t {
	var c C.u_shaped_ring_params_t
	c.thickness = C.double(p.Thickness)
	c.height = C.double(p.Height)
	c.radius = C.double(p.Radius)
	c.length = C.double(p.Length)
	return c
}

func CreateUShapedRing(params UShapedRingParams) *Shape {
	cParams := params.to_struct()
	shp := C.create_u_shaped_ring(cParams)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateUShapedRingWithPlace(params UShapedRingParams, position Point3, normal Dir3, xDir Dir3) *Shape {
	cParams := params.to_struct()
	shp := C.create_u_shaped_ring_with_place(cParams, position.val, normal.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

const (
	ConnectionSectionRectangular = C.CONNECTION_SECTION_RECTANGULAR
	ConnectionSectionHorseshoe   = C.CONNECTION_SECTION_HORSESHOE
	ConnectionSectionCircular    = C.CONNECTION_SECTION_CIRCULAR
)

const (
	TunnelWellStraight       = C.TUNNEL_WELL_STRAIGHT
	TunnelWellStraightTunnel = C.TUNNEL_WELL_STRAIGHT_TUNNEL
)

const (
	ThreeWayWellWorking     = C.THREE_WAY_WELL_WORKING
	ThreeWayWellOpenCut     = C.THREE_WAY_WELL_OPEN_CUT
	ThreeWayWellUnderground = C.THREE_WAY_WELL_UNDERGROUND
)

const (
	CornerStyleRounded = C.CORNER_STYLE_ROUNDED
	CornerStyleAngled  = C.CORNER_STYLE_ANGLED
)

const (
	ShaftStyleCircular    = C.SHAFT_STYLE_CIRCULAR
	ShaftStyleRectangular = C.SHAFT_STYLE_RECTANGULAR
)

type LiftingEyeParams struct {
	Height       float64
	RingRadius   float64
	PipeDiameter float64
}

func (p *LiftingEyeParams) to_struct() C.lifting_eye_params_t {
	var c C.lifting_eye_params_t
	c.height = C.double(p.Height)
	c.ringRadius = C.double(p.RingRadius)
	c.pipeDiameter = C.double(p.PipeDiameter)
	return c
}

func CreateLiftingEye(params LiftingEyeParams) *Shape {
	cParams := params.to_struct()
	shp := C.create_lifting_eye(cParams)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateLiftingEyeWithPlace(params LiftingEyeParams, position Point3, normal Dir3, xDir Dir3) *Shape {
	cParams := params.to_struct()
	shp := C.create_lifting_eye_with_place(cParams, position.val, normal.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type CornerWellParams struct {
	LeftLength       float64
	RightLength      float64
	Width            float64
	Height           float64
	TopThickness     float64
	BottomThickness  float64
	WallThickness    float64
	Angle            float64
	CornerRadius     float64
	CushionExtension float64
	CushionThickness float64
}

func (p *CornerWellParams) to_struct() C.corner_well_params_t {
	var c C.corner_well_params_t
	c.leftLength = C.double(p.LeftLength)
	c.rightLength = C.double(p.RightLength)
	c.width = C.double(p.Width)
	c.height = C.double(p.Height)
	c.topThickness = C.double(p.TopThickness)
	c.bottomThickness = C.double(p.BottomThickness)
	c.wallThickness = C.double(p.WallThickness)
	c.angle = C.double(p.Angle)
	c.cornerRadius = C.double(p.CornerRadius)
	c.cushionExtension = C.double(p.CushionExtension)
	c.cushionThickness = C.double(p.CushionThickness)
	return c
}

func CreateCornerWell(params CornerWellParams) *Shape {
	cParams := params.to_struct()
	shp := C.create_corner_well(cParams)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateCornerWellWithPlace(params CornerWellParams, position Point3, direction Dir3, xDir Dir3) *Shape {
	cParams := params.to_struct()
	shp := C.create_corner_well_with_place(cParams, position.val, direction.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type TunnelWellParams struct {
	Type               int
	Length             float64
	Width              float64
	Height             float64
	Radius             float64
	TopThickness       float64
	BottomThickness    float64
	LeftSectionType    int
	LeftLength         float64
	LeftWidth          float64
	LeftHeight         float64
	LeftArcHeight      float64
	RightSectionType   int
	RightLength        float64
	RightWidth         float64
	RightHeight        float64
	RightArcHeight     float64
	OuterWallThickness float64
	InnerWallThickness float64
	CushionExtension   float64
	CushionThickness   float64
}

func (p *TunnelWellParams) to_struct() C.tunnel_well_params_t {
	var c C.tunnel_well_params_t
	c.ctype = C.int(p.Type)
	c.length = C.double(p.Length)
	c.width = C.double(p.Width)
	c.height = C.double(p.Height)
	c.radius = C.double(p.Radius)
	c.topThickness = C.double(p.TopThickness)
	c.bottomThickness = C.double(p.BottomThickness)
	c.leftSectionType = C.int(p.LeftSectionType)
	c.leftLength = C.double(p.LeftLength)
	c.leftWidth = C.double(p.LeftWidth)
	c.leftHeight = C.double(p.LeftHeight)
	c.leftArcHeight = C.double(p.LeftArcHeight)
	c.rightSectionType = C.int(p.RightSectionType)
	c.rightLength = C.double(p.RightLength)
	c.rightWidth = C.double(p.RightWidth)
	c.rightHeight = C.double(p.RightHeight)
	c.rightArcHeight = C.double(p.RightArcHeight)
	c.outerWallThickness = C.double(p.OuterWallThickness)
	c.innerWallThickness = C.double(p.InnerWallThickness)
	c.cushionExtension = C.double(p.CushionExtension)
	c.cushionThickness = C.double(p.CushionThickness)
	return c
}

func CreateTunnelWell(params TunnelWellParams) *Shape {
	cParams := params.to_struct()
	shp := C.create_tunnel_well(cParams)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateTunnelWellWithPlace(params TunnelWellParams, position Point3, direction Dir3, xDir Dir3) *Shape {
	cParams := params.to_struct()
	shp := C.create_tunnel_well_with_place(cParams, position.val, direction.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type ThreeWayWellParams struct {
	Ctype                  int
	CornerType             int
	ShaftType              int
	Length                 float32
	Width                  float32
	Height                 float32
	ShaftRadius            float32
	CornerRadius           float32
	CornerLength           float32
	CornerWidth            float32
	Angle                  float32
	BranchLength           float32
	BranchLeftLength       float32
	BranchWidth            float32
	TopThickness           float32
	BottomThickness        float32
	LeftSectionStyle       int
	LeftSectionLength      float32
	LeftSectionWidth       float32
	LeftSectionHeight      float32
	LeftSectionArcHeight   float32
	RightSectionStyle      int
	RightSectionLength     float32
	RightSectionWidth      float32
	RightSectionHeight     float32
	RightSectionArcHeight  float32
	BranchSectionStyle     int
	BranchSectionLength    float32
	BranchSectionWidth     float32
	BranchSectionHeight    float32
	BranchSectionArcHeight float32
	OuterWallThickness     float32
	InnerWallThickness     float32
	IsDoubleShaft          bool
	DoubleShaftSpacing     float32
	OuterWallExtension     float32
	InnerWallExtension     float32
	CushionExtension       float32
	CushionThickness       float32
	InnerBottomThickness   float32
	OuterBottomThickness   float32
}

func (p *ThreeWayWellParams) to_struct() C.three_way_well_params_t {
	var c C.three_way_well_params_t
	c.ctype = C.int(p.Ctype)
	c.cornerType = C.int(p.CornerType)
	c.shaftType = C.int(p.ShaftType)
	c.length = C.double(p.Length)
	c.width = C.double(p.Width)
	c.height = C.double(p.Height)
	c.shaftRadius = C.double(p.ShaftRadius)
	c.cornerRadius = C.double(p.CornerRadius)
	c.cornerLength = C.double(p.CornerLength)
	c.cornerWidth = C.double(p.CornerWidth)
	c.angle = C.double(p.Angle)
	c.branchLength = C.double(p.BranchLength)
	c.branchLeftLength = C.double(p.BranchLeftLength)
	c.branchWidth = C.double(p.BranchWidth)
	c.topThickness = C.double(p.TopThickness)
	c.bottomThickness = C.double(p.BottomThickness)
	c.leftSectionStyle = C.int(p.LeftSectionStyle)
	c.leftSectionLength = C.double(p.LeftSectionLength)
	c.leftSectionWidth = C.double(p.LeftSectionWidth)
	c.leftSectionHeight = C.double(p.LeftSectionHeight)
	c.leftSectionArcHeight = C.double(p.LeftSectionArcHeight)
	c.rightSectionStyle = C.int(p.RightSectionStyle)
	c.rightSectionLength = C.double(p.RightSectionLength)
	c.rightSectionWidth = C.double(p.RightSectionWidth)
	c.rightSectionHeight = C.double(p.RightSectionHeight)
	c.rightSectionArcHeight = C.double(p.RightSectionArcHeight)
	c.branchSectionStyle = C.int(p.BranchSectionStyle)
	c.branchSectionLength = C.double(p.BranchSectionLength)
	c.branchSectionWidth = C.double(p.BranchSectionWidth)
	c.branchSectionHeight = C.double(p.BranchSectionHeight)
	c.branchSectionArcHeight = C.double(p.BranchSectionArcHeight)
	c.outerWallThickness = C.double(p.OuterWallThickness)
	c.innerWallThickness = C.double(p.InnerWallThickness)
	c.isDoubleShaft = C.bool(p.IsDoubleShaft)
	c.doubleShaftSpacing = C.double(p.DoubleShaftSpacing)
	c.outerWallExtension = C.double(p.OuterWallExtension)
	c.innerWallExtension = C.double(p.InnerWallExtension)
	c.cushionExtension = C.double(p.CushionExtension)
	c.cushionThickness = C.double(p.CushionThickness)
	c.innerBottomThickness = C.double(p.InnerBottomThickness)
	c.outerBottomThickness = C.double(p.OuterBottomThickness)
	return c
}

func CreateThreeWayWell(params ThreeWayWellParams) *Shape {
	shp := C.create_three_way_well(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateThreeWayWellWithPlace(params ThreeWayWellParams, position Point3, mainDirection Dir3, branchDirection Dir3) *Shape {
	shp := C.create_three_way_well_with_place(params.to_struct(), position.val, mainDirection.val, branchDirection.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

const (
	FourWayWellWorking     = C.FOUR_WAY_WELL_WORKING
	FourWayWellOpenCut     = C.FOUR_WAY_WELL_OPEN_CUT
	FourWayWellUnderground = C.FOUR_WAY_WELL_UNDERGROUND
)

type FourWayWellSection struct {
	SectionType int
	Length      float32
	Width       float32
	Height      float32
	ArcHeight   float32
}

type FourWayWellParams struct {
	Ctype              int
	Length             float32
	Width              float32
	Height             float32
	ShaftRadius        float32
	CornerStyle        int
	CornerRadius       float32
	CornerLength       float32
	CornerWidth        float32
	BranchLength       float32
	BranchWidth        float32
	TopThickness       float32
	BottomThickness    float32
	LeftSection        FourWayWellSection
	RightSection       FourWayWellSection
	BranchSection1     FourWayWellSection
	BranchSection2     FourWayWellSection
	OuterWallThickness float32
	InnerWallThickness float32
	CushionExtension   float32
	CushionThickness   float32
}

func (p *FourWayWellParams) to_struct() C.four_way_well_params_t {
	var c C.four_way_well_params_t
	c.ctype = C.int(p.Ctype)
	c.length = C.double(p.Length)
	c.width = C.double(p.Width)
	c.height = C.double(p.Height)
	c.shaftRadius = C.double(p.ShaftRadius)
	c.cornerStyle = C.int(p.CornerStyle)
	c.cornerRadius = C.double(p.CornerRadius)
	c.cornerLength = C.double(p.CornerLength)
	c.cornerWidth = C.double(p.CornerWidth)
	c.branchLength = C.double(p.BranchLength)
	c.branchWidth = C.double(p.BranchWidth)
	c.topThickness = C.double(p.TopThickness)
	c.bottomThickness = C.double(p.BottomThickness)

	c.leftSection.sectionType = C.int(p.LeftSection.SectionType)
	c.leftSection.length = C.double(p.LeftSection.Length)
	c.leftSection.width = C.double(p.LeftSection.Width)
	c.leftSection.height = C.double(p.LeftSection.Height)
	c.leftSection.arcHeight = C.double(p.LeftSection.ArcHeight)

	c.rightSection.sectionType = C.int(p.RightSection.SectionType)
	c.rightSection.length = C.double(p.RightSection.Length)
	c.rightSection.width = C.double(p.RightSection.Width)
	c.rightSection.height = C.double(p.RightSection.Height)
	c.rightSection.arcHeight = C.double(p.RightSection.ArcHeight)

	c.branchSection1.sectionType = C.int(p.BranchSection1.SectionType)
	c.branchSection1.length = C.double(p.BranchSection1.Length)
	c.branchSection1.width = C.double(p.BranchSection1.Width)
	c.branchSection1.height = C.double(p.BranchSection1.Height)
	c.branchSection1.arcHeight = C.double(p.BranchSection1.ArcHeight)

	c.branchSection2.sectionType = C.int(p.BranchSection2.SectionType)
	c.branchSection2.length = C.double(p.BranchSection2.Length)
	c.branchSection2.width = C.double(p.BranchSection2.Width)
	c.branchSection2.height = C.double(p.BranchSection2.Height)
	c.branchSection2.arcHeight = C.double(p.BranchSection2.ArcHeight)

	c.outerWallThickness = C.double(p.OuterWallThickness)
	c.innerWallThickness = C.double(p.InnerWallThickness)
	c.cushionExtension = C.double(p.CushionExtension)
	c.cushionThickness = C.double(p.CushionThickness)
	return c
}

func CreateFourWayWell(params FourWayWellParams) *Shape {
	shp := C.create_four_way_well(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateFourWayWellWithPlace(params FourWayWellParams, position Point3, direction Dir3, xDirection Dir3) *Shape {
	shp := C.create_four_way_well_with_place(params.to_struct(), position.val, direction.val, xDirection.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

const (
	TunnelSectionRectangular = 1
	TunnelSectionHorseshoe   = 2
	TunnelSectionCircular    = 3
)

const (
	CableTunnelTypeLine = 0 // 直道
	CableTunnelTypeArc  = 1 // 弧形
)

type ChannelPoint struct {
	Position Point3
	Ctype    int
}

func CreateChannelCenterline(points []ChannelPoint) *Wire {
	cPoints := make([]C.channel_point_t, len(points))
	for i, pt := range points {
		cPoints[i] = C.channel_point_t{
			position: pt.Position.val,
			ctype:    C.int(pt.Ctype),
		}
	}

	wire := C.create_channel_centerline(&cPoints[0], C.int(len(points)))
	w := &Wire{inner: &innerWire{val: wire}}
	runtime.SetFinalizer(w.inner, (*innerWire).free)
	return w
}

func SampleChannelPoints(points []ChannelPoint, tessellation float64) []Point3 {
	cPoints := make([]C.channel_point_t, len(points))
	for i, pt := range points {
		cPoints[i] = C.channel_point_t{
			position: pt.Position.val,
			ctype:    C.int(pt.Ctype),
		}
	}

	var outCount C.int
	cResult := C.sample_channel_points(
		&cPoints[0],
		C.int(len(points)),
		C.double(tessellation),
		&outCount,
	)
	defer C.free(unsafe.Pointer(cResult))

	// 转换结果
	result := make([]Point3, outCount)
	for i := 0; i < int(outCount); i++ {
		result[i] = Point3{val: *(*C.pnt3d_t)(unsafe.Pointer(uintptr(unsafe.Pointer(cResult)) + uintptr(i)*C.sizeof_pnt3d_t))}
	}

	return result
}

const (
	PipeRowTypeNormal = 1 // 普通排管
	PipeRowTypePull   = 2 // 拉管
)

type PipeRowParams struct {
	PipeType              int
	HasEnclosure          bool
	EnclosureWidth        float32
	EnclosureHeight       float32
	BaseExtension         float32
	BaseThickness         float32
	CushionExtension      float32
	CushionThickness      float32
	PipePositions         []Point2
	PipeInnerDiameters    []float32
	PipeWallThicknesses   []float32
	PullPipeInnerDiameter float32
	PullPipeThickness     float32
	Points                []ChannelPoint
}

func (p *PipeRowParams) to_struct() C.pipe_row_params_t {
	var c C.pipe_row_params_t
	c.pipeType = C.int(p.PipeType)
	c.hasEnclosure = C.bool(p.HasEnclosure)
	c.enclosureWidth = C.double(p.EnclosureWidth)
	c.enclosureHeight = C.double(p.EnclosureHeight)
	c.baseExtension = C.double(p.BaseExtension)
	c.baseThickness = C.double(p.BaseThickness)
	c.cushionExtension = C.double(p.CushionExtension)
	c.cushionThickness = C.double(p.CushionThickness)
	c.pipeCount = C.int(len(p.PipePositions))
	c.pointCount = C.int(len(p.Points))

	if len(p.PipePositions) > 0 {
		c.pipePositions = (*C.pnt2d_t)(C.malloc(C.size_t(len(p.PipePositions)) * C.sizeof_pnt2d_t))
		for i, pos := range p.PipePositions {
			*(*C.pnt2d_t)(unsafe.Pointer(uintptr(unsafe.Pointer(c.pipePositions)) + uintptr(i)*C.sizeof_pnt2d_t)) = pos.val
		}
	}

	if len(p.PipeInnerDiameters) > 0 {
		c.pipeInnerDiameters = (*C.double)(C.malloc(C.size_t(len(p.PipeInnerDiameters)) * C.sizeof_double))
		for i, dia := range p.PipeInnerDiameters {
			*(*C.double)(unsafe.Pointer(uintptr(unsafe.Pointer(c.pipeInnerDiameters)) + uintptr(i)*C.sizeof_double)) = C.double(dia)
		}
	}

	if len(p.PipeWallThicknesses) > 0 {
		c.pipeWallThicknesses = (*C.double)(C.malloc(C.size_t(len(p.PipeWallThicknesses)) * C.sizeof_double))
		for i, thick := range p.PipeWallThicknesses {
			*(*C.double)(unsafe.Pointer(uintptr(unsafe.Pointer(c.pipeWallThicknesses)) + uintptr(i)*C.sizeof_double)) = C.double(thick)
		}
	}

	c.pullPipeInnerDiameter = C.double(p.PullPipeInnerDiameter)
	c.pullPipeThickness = C.double(p.PullPipeThickness)

	if len(p.Points) > 0 {
		c.points = (*C.channel_point_t)(C.malloc(C.size_t(len(p.Points)) * C.sizeof_channel_point_t))
		for i, point := range p.Points {
			cp := C.channel_point_t{
				position: point.Position.val,
				ctype:    C.int(point.Ctype),
			}
			*(*C.channel_point_t)(unsafe.Pointer(uintptr(unsafe.Pointer(c.points)) + uintptr(i)*C.sizeof_channel_point_t)) = cp
		}
	}

	return c
}

func CreatePipeRow(params PipeRowParams) *Shape {
	shp := C.create_pipe_row(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreatePipeRowWithPlace(params PipeRowParams, position Point3, normal Dir3, xDir Dir3) *Shape {
	shp := C.create_pipe_row_with_place(params.to_struct(), position.val, normal.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type CableTrenchParams struct {
	Width            float32
	Height           float32
	CoverWidth       float32
	CoverThickness   float32
	BaseExtension    float32
	BaseThickness    float32
	CushionExtension float32
	CushionThickness float32
	WallThickness    float32
	WallThickness2   float32
	Points           []ChannelPoint
}

func (p *CableTrenchParams) to_struct() C.cable_trench_params_t {
	var c C.cable_trench_params_t
	c.width = C.double(p.Width)
	c.height = C.double(p.Height)
	c.coverWidth = C.double(p.CoverWidth)
	c.coverThickness = C.double(p.CoverThickness)
	c.baseExtension = C.double(p.BaseExtension)
	c.baseThickness = C.double(p.BaseThickness)
	c.cushionExtension = C.double(p.CushionExtension)
	c.cushionThickness = C.double(p.CushionThickness)
	c.wallThickness = C.double(p.WallThickness)
	c.wallThickness2 = C.double(p.WallThickness2)

	if len(p.Points) > 0 {
		c.points = (*C.channel_point_t)(C.malloc(C.size_t(len(p.Points)) * C.sizeof_channel_point_t))
		for i, point := range p.Points {
			cp := C.channel_point_t{
				position: point.Position.val,
				ctype:    C.int(point.Ctype),
			}
			*(*C.channel_point_t)(unsafe.Pointer(uintptr(unsafe.Pointer(c.points)) + uintptr(i)*C.sizeof_channel_point_t)) = cp
		}
		c.pointCount = C.int(len(p.Points))
	}
	return c
}

func CreateCableTrench(params CableTrenchParams) *Shape {
	cParams := params.to_struct()
	defer func() {
		if cParams.points != nil {
			C.free(unsafe.Pointer(cParams.points))
		}
	}()

	shp := C.create_cable_trench(cParams)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateCableTrenchWithPlace(params CableTrenchParams, position Point3, direction Dir3, xDir Dir3) *Shape {
	cParams := params.to_struct()
	defer func() {
		if cParams.points != nil {
			C.free(unsafe.Pointer(cParams.points))
		}
	}()

	shp := C.create_cable_trench_with_place(cParams, position.val, direction.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type CableTunnelParams struct {
	Style                int32
	Width                float32
	Height               float32
	TopThickness         float32
	BottomThickness      float32
	OuterWallThickness   float32
	InnerWallThickness   float32
	ArcHeight            float32
	BottomPlatformHeight float32
	CushionExtension     float32
	CushionThickness     float32
	Points               []ChannelPoint
}

func (p *CableTunnelParams) to_struct() C.cable_tunnel_params_t {
	var c C.cable_tunnel_params_t
	c.style = C.int(p.Style)
	c.width = C.double(p.Width)
	c.height = C.double(p.Height)
	c.topThickness = C.double(p.TopThickness)
	c.bottomThickness = C.double(p.BottomThickness)
	c.outerWallThickness = C.double(p.OuterWallThickness)
	c.innerWallThickness = C.double(p.InnerWallThickness)
	c.arcHeight = C.double(p.ArcHeight)
	c.bottomPlatformHeight = C.double(p.BottomPlatformHeight)
	c.cushionExtension = C.double(p.CushionExtension)
	c.cushionThickness = C.double(p.CushionThickness)

	if len(p.Points) > 0 {
		c.points = (*C.channel_point_t)(C.malloc(C.size_t(len(p.Points)) * C.sizeof_channel_point_t))
		for i, point := range p.Points {
			cp := C.channel_point_t{
				position: point.Position.val,
				ctype:    C.int(point.Ctype),
			}
			*(*C.channel_point_t)(unsafe.Pointer(uintptr(unsafe.Pointer(c.points)) + uintptr(i)*C.sizeof_channel_point_t)) = cp
		}
		c.pointCount = C.int(len(p.Points))
	}
	return c
}

func CreateCableTunnel(params CableTunnelParams) *Shape {
	cParams := params.to_struct()
	defer func() {
		if cParams.points != nil {
			C.free(unsafe.Pointer(cParams.points))
		}
	}()

	shp := C.create_cable_tunnel(cParams)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateCableTunnelWithPlace(params CableTunnelParams, position Point3, direction Dir3, xDir Dir3) *Shape {
	cParams := params.to_struct()
	defer func() {
		if cParams.points != nil {
			C.free(unsafe.Pointer(cParams.points))
		}
	}()

	shp := C.create_cable_tunnel_with_place(cParams, position.val, direction.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type CableTrayParams struct {
	Style               int32
	ColumnDiameter      float32
	ColumnHeight        float32
	Span                float32
	Width               float32
	Height              float32
	TopPlateHeight      float32
	ArcHeight           float32
	WallThickness       float32
	PipePositions       []Point2
	PipeInnerDiameters  []float32
	PipeWallThicknesses []float32
	HasProtectionPlate  bool
	Points              []ChannelPoint
}

func (p *CableTrayParams) to_struct() C.cable_tray_params_t {
	var c C.cable_tray_params_t
	c.style = C.int(p.Style)
	c.columnDiameter = C.double(p.ColumnDiameter)
	c.columnHeight = C.double(p.ColumnHeight)
	c.span = C.double(p.Span)
	c.width = C.double(p.Width)
	c.height = C.double(p.Height)
	c.topPlateHeight = C.double(p.TopPlateHeight)
	c.arcHeight = C.double(p.ArcHeight)
	c.wallThickness = C.double(p.WallThickness)
	c.pipeCount = C.int(len(p.PipePositions))

	if len(p.PipePositions) > 0 {
		c.pipePositions = (*C.pnt2d_t)(C.malloc(C.size_t(len(p.PipePositions)) * C.sizeof_pnt2d_t))
		for i, pos := range p.PipePositions {
			*(*C.pnt2d_t)(unsafe.Pointer(uintptr(unsafe.Pointer(c.pipePositions)) + uintptr(i)*C.sizeof_pnt2d_t)) = pos.val
		}
	}
	if len(p.PipeInnerDiameters) > 0 {
		c.pipeInnerDiameters = (*C.double)(C.malloc(C.size_t(len(p.PipeInnerDiameters)) * C.sizeof_double))
		for i, radius := range p.PipeInnerDiameters {
			C.double_array_set(c.pipeInnerDiameters, C.int(i), C.double(radius))
		}
	}

	if len(p.PipeWallThicknesses) > 0 {
		c.pipeWallThicknesses = (*C.double)(C.malloc(C.size_t(len(p.PipeWallThicknesses)) * C.sizeof_double))
		for i, thinckness := range p.PipeWallThicknesses {
			C.double_array_set(c.pipeWallThicknesses, C.int(i), C.double(thinckness))
		}
	}

	if C.bool(p.HasProtectionPlate) {
		c.hasProtectionPlate = C.int(1)
	} else {
		c.hasProtectionPlate = C.int(0)
	}

	if len(p.Points) > 0 {
		c.points = (*C.channel_point_t)(C.malloc(C.size_t(len(p.Points)) * C.sizeof_channel_point_t))
		for i, point := range p.Points {
			cp := C.channel_point_t{
				position: point.Position.val,
				ctype:    C.int(point.Ctype),
			}
			*(*C.channel_point_t)(unsafe.Pointer(uintptr(unsafe.Pointer(c.points)) + uintptr(i)*C.sizeof_channel_point_t)) = cp
		}
		c.pointCount = C.int(len(p.Points))
	}
	return c
}

func CreateCableTray(params CableTrayParams) *Shape {
	cParams := params.to_struct()
	defer func() {
		if cParams.pipePositions != nil {
			C.free(unsafe.Pointer(cParams.pipePositions))
		}

		if cParams.points != nil {
			C.free(unsafe.Pointer(cParams.points))
		}
		if cParams.pipeInnerDiameters != nil {
			C.free(unsafe.Pointer(cParams.pipeInnerDiameters))
		}
		if cParams.pipeWallThicknesses != nil {
			C.free(unsafe.Pointer(cParams.pipeWallThicknesses))
		}
	}()

	shp := C.create_cable_tray(cParams)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateCableTrayWithPlace(params CableTrayParams, position Point3, direction Dir3, xDir Dir3) *Shape {
	cParams := params.to_struct()
	defer func() {
		if cParams.pipePositions != nil {
			C.free(unsafe.Pointer(cParams.pipePositions))
		}
		if cParams.pipeInnerDiameters != nil {
			C.free(unsafe.Pointer(cParams.pipeInnerDiameters))
		}
		if cParams.pipeWallThicknesses != nil {
			C.free(unsafe.Pointer(cParams.pipeWallThicknesses))
		}
		if cParams.points != nil {
			C.free(unsafe.Pointer(cParams.points))
		}
	}()

	shp := C.create_cable_tray_with_place(cParams, position.val, direction.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type CableLBeamParams struct {
	Length float32
	Width  float32
	Height float32
}

func (p *CableLBeamParams) to_struct() C.cable_L_beam_params_t {
	var c C.cable_L_beam_params_t
	c.length = C.double(p.Length)
	c.width = C.double(p.Width)
	c.height = C.double(p.Height)
	return c
}

func CreateCableLBeam(params CableLBeamParams) *Shape {
	shp := C.create_cable_L_beam(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateCableLBeamWithPlace(params CableLBeamParams, position Point3, xDir Dir3, zDir Dir3) *Shape {
	shp := C.create_cable_L_beam_with_place(params.to_struct(), position.val, xDir.val, zDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type ManholeParams struct {
	Style         int32
	Length        float32
	Width         float32
	Height        float32
	WallThickness float32
}

func (p *ManholeParams) to_struct() C.manhole_params_t {
	var c C.manhole_params_t
	c.style = C.int(p.Style)
	c.length = C.double(p.Length)
	c.width = C.double(p.Width)
	c.height = C.double(p.Height)
	c.wallThickness = C.double(p.WallThickness)
	return c
}

func CreateManhole(params ManholeParams) *Shape {
	shp := C.create_manhole(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateManholeWithPlace(params ManholeParams, position Point3, direction Dir3, xDir Dir3) *Shape {
	shp := C.create_manhole_with_place(params.to_struct(), position.val, direction.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type ManholeCoverParams struct {
	Style     int32
	Length    float32
	Width     float32
	Thickness float32
}

func (p *ManholeCoverParams) to_struct() C.manhole_cover_params_t {
	var c C.manhole_cover_params_t
	c.style = C.int(p.Style)
	c.length = C.double(p.Length)
	c.width = C.double(p.Width)
	c.thickness = C.double(p.Thickness)
	return c
}

func CreateManholeCover(params ManholeCoverParams) *Shape {
	shp := C.create_manhole_cover(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateManholeCoverWithPlace(params ManholeCoverParams, position Point3, direction Dir3, xDir Dir3) *Shape {
	shp := C.create_manhole_cover_with_place(params.to_struct(), position.val, direction.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type LadderParams struct {
	Length    float32
	Width     float32
	Thickness float32
}

func (p *LadderParams) to_struct() C.ladder_params_t {
	var c C.ladder_params_t
	c.length = C.double(p.Length)
	c.width = C.double(p.Width)
	c.thickness = C.double(p.Thickness)
	return c
}

func CreateLadder(params LadderParams) *Shape {
	shp := C.create_ladder(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateLadderWithPlace(params LadderParams, position Point3, direction Dir3, xDir Dir3) *Shape {
	shp := C.create_ladder_with_place(params.to_struct(), position.val, direction.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type SumpParams struct {
	Length          float32
	Width           float32
	Depth           float32
	BottomThickness float32
}

func (p *SumpParams) to_struct() C.sump_params_t {
	var c C.sump_params_t
	c.length = C.double(p.Length)
	c.width = C.double(p.Width)
	c.depth = C.double(p.Depth)
	c.bottomThickness = C.double(p.BottomThickness)
	return c
}

func CreateSump(params SumpParams) *Shape {
	shp := C.create_sump(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateSumpWithPlace(params SumpParams, position Point3, normal Dir3, xDir Dir3) *Shape {
	shp := C.create_sump_with_place(params.to_struct(), position.val, normal.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type FootpathParams struct {
	Height float32
	Width  float32
	Points []ChannelPoint
}

func (p *FootpathParams) to_struct() C.footpath_params_t {
	var c C.footpath_params_t
	c.height = C.double(p.Height)
	c.width = C.double(p.Width)

	if len(p.Points) > 0 {
		c.points = (*C.channel_point_t)(C.malloc(C.size_t(len(p.Points)) * C.sizeof_channel_point_t))
		for i, point := range p.Points {
			cp := C.channel_point_t{
				position: point.Position.val,
				ctype:    C.int(point.Ctype),
			}
			*(*C.channel_point_t)(unsafe.Pointer(uintptr(unsafe.Pointer(c.points)) + uintptr(i)*C.sizeof_channel_point_t)) = cp
		}
		c.pointCount = C.int(len(p.Points))
	}
	c.pointCount = C.int(len(p.Points))
	return c
}

func CreateFootpath(params FootpathParams) *Shape {
	shp := C.create_footpath(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateFootpathWithPlace(params FootpathParams, position Point3, direction Dir3, xDir Dir3) *Shape {
	shp := C.create_footpath_with_place(params.to_struct(), position.val, direction.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type ShaftChamberParams struct {
	SupportWallThickness float32
	SupportDiameter      float32
	SupportHeight        float32
	TopThickness         float32
	InnerDiameter        float32
	WorkingHeight        float32
	OuterWallThickness   float32
	InnerWallThickness   float32
}

func (p *ShaftChamberParams) to_struct() C.shaft_chamber_params_t {
	var c C.shaft_chamber_params_t
	c.supportWallThickness = C.double(p.SupportWallThickness)
	c.supportDiameter = C.double(p.SupportDiameter)
	c.supportHeight = C.double(p.SupportHeight)
	c.topThickness = C.double(p.TopThickness)
	c.innerDiameter = C.double(p.InnerDiameter)
	c.workingHeight = C.double(p.WorkingHeight)
	c.outerWallThickness = C.double(p.OuterWallThickness)
	c.innerWallThickness = C.double(p.InnerWallThickness)
	return c
}

func CreateShaftChamber(params ShaftChamberParams) *Shape {
	shp := C.create_shaft_chamber(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateShaftChamberWithPlace(params ShaftChamberParams, position Point3, direction Dir3, xDir Dir3) *Shape {
	shp := C.create_shaft_chamber_with_place(params.to_struct(), position.val, direction.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type TunnelCompartmentPartitionParams struct {
	Width     float32 // 隔板宽 (mm)
	Thickness float32 // 隔板厚 (mm)
}

func (p *TunnelCompartmentPartitionParams) to_struct() C.tunnel_compartment_partition_params_t {
	var c C.tunnel_compartment_partition_params_t
	c.width = C.double(p.Width)
	c.thickness = C.double(p.Thickness)
	return c
}

func CreateTunnelCompartmentPartition(params TunnelCompartmentPartitionParams) *Shape {
	shp := C.create_tunnel_compartment_partition(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateTunnelCompartmentPartitionWithPlace(params TunnelCompartmentPartitionParams, position Point3, normal Dir3, xDir Dir3) *Shape {
	shp := C.create_tunnel_compartment_partition_with_place(params.to_struct(), position.val, normal.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type TunnelPartitionBoardStyle int32

const (
	TunnelPartitionBoardStyleCircular    TunnelPartitionBoardStyle = 1 // 圆形
	TunnelPartitionBoardStyleRectangular TunnelPartitionBoardStyle = 2 // 方形
)

type TunnelPartitionBoardParams struct {
	Style         TunnelPartitionBoardStyle
	Length        float32
	Width         float32
	Thickness     float32
	HoleCount     int32
	HolePositions []Point2
	HoleStyles    []int32
	HoleDiameters []float32
	HoleWidths    []float32
}

func (p *TunnelPartitionBoardParams) to_struct() C.tunnel_partition_board_params_t {
	var c C.tunnel_partition_board_params_t
	c.style = C.int(p.Style)
	c.length = C.double(p.Length)
	c.width = C.double(p.Width)
	c.thickness = C.double(p.Thickness)
	c.holeCount = C.int(p.HoleCount)

	if len(p.HolePositions) > 0 {
		c.holePositions = (*C.pnt2d_t)(C.malloc(C.size_t(len(p.HolePositions)) * C.sizeof_pnt2d_t))
		for i, pos := range p.HolePositions {
			*(*C.pnt2d_t)(unsafe.Pointer(uintptr(unsafe.Pointer(c.holePositions)) + uintptr(i)*C.sizeof_pnt2d_t)) = pos.val
		}
	}

	if len(p.HoleStyles) > 0 {
		size := C.size_t(C.int(0))
		c.holeStyles = (*C.int)(C.malloc(C.size_t(len(p.HoleStyles)) * size))
		for i, style := range p.HoleStyles {
			C.int_array_set(c.holeStyles, C.int(i), C.int(style))
		}
	}
	if len(p.HoleDiameters) > 0 {
		c.holeDiameters = (*C.double)(C.malloc(C.size_t(len(p.HoleDiameters)) * C.sizeof_double))
		for i, diameter := range p.HoleDiameters {
			C.double_array_set(c.holeDiameters, C.int(i), C.double(diameter))
		}
	}
	if len(p.HoleWidths) > 0 {
		c.holeWidths = (*C.double)(C.malloc(C.size_t(len(p.HoleWidths)) * C.sizeof_double))
		for i, width := range p.HoleWidths {
			C.double_array_set(c.holeWidths, C.int(i), C.double(width))
		}
	}
	return c
}

func CreateTunnelPartitionBoard(params TunnelPartitionBoardParams) *Shape {
	cParams := params.to_struct()
	defer func() {
		if cParams.holePositions != nil {
			C.free(unsafe.Pointer(cParams.holePositions))
		}
		if cParams.holeStyles != nil {
			C.free(unsafe.Pointer(cParams.holeStyles))
		}
		if cParams.holeDiameters != nil {
			C.free(unsafe.Pointer(cParams.holeDiameters))
		}
		if cParams.holeWidths != nil {
			C.free(unsafe.Pointer(cParams.holeWidths))
		}
	}()

	shp := C.create_tunnel_partition_board(cParams)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateTunnelPartitionBoardWithPlace(params TunnelPartitionBoardParams, position Point3, normal Dir3, xDir Dir3) *Shape {
	cParams := params.to_struct()
	defer func() {
		if cParams.holePositions != nil {
			C.free(unsafe.Pointer(cParams.holePositions))
		}
		if cParams.holeStyles != nil {
			C.free(unsafe.Pointer(cParams.holeStyles))
		}
		if cParams.holeDiameters != nil {
			C.free(unsafe.Pointer(cParams.holeDiameters))
		}
		if cParams.holeWidths != nil {
			C.free(unsafe.Pointer(cParams.holeWidths))
		}
	}()

	shp := C.create_tunnel_partition_board_with_place(cParams, position.val, normal.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type ObliqueVentilationDuctParams struct {
	HoodRoomLength        float64
	HoodRoomWidth         float64
	HoodRoomHeight        float64
	HoodWallThickness     float64
	DuctCenterHeight      float64
	DuctLeftDistance      float64
	DuctDiameter          float64
	DuctWallThickness     float64
	DuctLength            float64
	DuctHeightDifference  float64
	BaseLength            float64
	BaseWidth             float64
	BaseHeight            float64
	BaseRoomLength        float64
	BaseRoomWallThickness float64
	BaseRoomWidth         float64
	BaseRoomHeight        float64
}

func (p *ObliqueVentilationDuctParams) to_struct() C.oblique_ventilation_duct_params_t {
	var c C.oblique_ventilation_duct_params_t
	c.hoodRoomLength = C.double(p.HoodRoomLength)
	c.hoodRoomWidth = C.double(p.HoodRoomWidth)
	c.hoodRoomHeight = C.double(p.HoodRoomHeight)
	c.hoodWallThickness = C.double(p.HoodWallThickness)
	c.ductCenterHeight = C.double(p.DuctCenterHeight)
	c.ductLeftDistance = C.double(p.DuctLeftDistance)
	c.ductDiameter = C.double(p.DuctDiameter)
	c.ductWallThickness = C.double(p.DuctWallThickness)
	c.ductLength = C.double(p.DuctLength)
	c.ductHeightDifference = C.double(p.DuctHeightDifference)
	c.baseLength = C.double(p.BaseLength)
	c.baseWidth = C.double(p.BaseWidth)
	c.baseHeight = C.double(p.BaseHeight)
	c.baseRoomLength = C.double(p.BaseRoomLength)
	c.baseRoomWallThickness = C.double(p.BaseRoomWallThickness)
	c.baseRoomWidth = C.double(p.BaseRoomWidth)
	c.baseRoomHeight = C.double(p.BaseRoomHeight)
	return c
}

func CreateObliqueVentilationDuct(params ObliqueVentilationDuctParams) *Shape {
	shp := C.create_oblique_ventilation_duct(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateObliqueVentilationDuctWithPlace(params ObliqueVentilationDuctParams, position Point3, direction Dir3, xDir Dir3) *Shape {
	shp := C.create_oblique_ventilation_duct_with_place(params.to_struct(), position.val, direction.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type VentilationPavilionParams struct {
	TopLength    float32
	MiddleLength float32
	BottomLength float32
	TopWidth     float32
	MiddleWidth  float32
	BottomWidth  float32
	TopHeight    float32
	Height       float32
	BaseHeight   float32
}

func (p *VentilationPavilionParams) to_struct() C.ventilation_pavilion_params_t {
	var c C.ventilation_pavilion_params_t
	c.topLength = C.double(p.TopLength)
	c.middleLength = C.double(p.MiddleLength)
	c.bottomLength = C.double(p.BottomLength)
	c.topWidth = C.double(p.TopWidth)
	c.middleWidth = C.double(p.MiddleWidth)
	c.bottomWidth = C.double(p.BottomWidth)
	c.topHeight = C.double(p.TopHeight)
	c.height = C.double(p.Height)
	c.baseHeight = C.double(p.BaseHeight)
	return c
}

func CreateVentilationPavilion(params VentilationPavilionParams) *Shape {
	shp := C.create_ventilation_pavilion(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateVentilationPavilionWithPlace(params VentilationPavilionParams, position Point3, direction Dir3, xDir Dir3) *Shape {
	shp := C.create_ventilation_pavilion_with_place(params.to_struct(), position.val, direction.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type StraightVentilationDuctParams struct {
	Diameter      float32
	WallThickness float32
	Height        float32
}

func (p *StraightVentilationDuctParams) to_struct() C.straight_ventilation_duct_params_t {
	var c C.straight_ventilation_duct_params_t
	c.diameter = C.double(p.Diameter)
	c.wallThickness = C.double(p.WallThickness)
	c.height = C.double(p.Height)
	return c
}

func CreateStraightVentilationDuct(params StraightVentilationDuctParams) *Shape {
	shp := C.create_straight_ventilation_duct(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateStraightVentilationDuctWithPlace(params StraightVentilationDuctParams, position Point3, direction Dir3, xDir Dir3) *Shape {
	shp := C.create_straight_ventilation_duct_with_place(params.to_struct(), position.val, direction.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type DrainageWellParams struct {
	Length           float32
	Width            float32
	Height           float32
	NeckDiameter     float32
	NeckHeight       float32
	CushionExtension float32
	BottomThickness  float32
	WallThickness    float32
}

func (p *DrainageWellParams) to_struct() C.drainage_well_params_t {
	var c C.drainage_well_params_t
	c.length = C.double(p.Length)
	c.width = C.double(p.Width)
	c.height = C.double(p.Height)
	c.neckDiameter = C.double(p.NeckDiameter)
	c.neckHeight = C.double(p.NeckHeight)
	c.cushionExtension = C.double(p.CushionExtension)
	c.bottomThickness = C.double(p.BottomThickness)
	c.wallThickness = C.double(p.WallThickness)
	return c
}

func CreateDrainageWell(params DrainageWellParams) *Shape {
	shp := C.create_drainage_well(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateDrainageWellWithPlace(params DrainageWellParams, position Point3, direction Dir3, xDir Dir3) *Shape {
	shp := C.create_drainage_well_with_place(params.to_struct(), position.val, direction.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

const (
	PipeSupportSingleSide = 1
	PipeSupportDoubleSide = 2
)

type PipeSupportParams struct {
	Style     int32
	Count     int32
	Positions []Point2
	Radii     []float32
	Length    float32
	Width     float32
	Height    float32
}

func (p *PipeSupportParams) to_struct() C.pipe_support_params_t {
	var c C.pipe_support_params_t
	c.style = C.int(p.Style)
	c.count = C.int(p.Count)
	c.length = C.double(p.Length)
	c.height = C.double(p.Height)
	c.width = C.double(p.Width)
	if len(p.Positions) > 0 {
		c.positions = (*C.pnt2d_t)(C.malloc(C.size_t(len(p.Positions)) * C.sizeof_pnt2d_t))
		for i, pos := range p.Positions {
			C.pnt2d_t_array_set(c.positions, C.int(i), pos.val)
		}
	}

	if len(p.Radii) > 0 {
		c.radii = (*C.double)(C.malloc(C.size_t(len(p.Radii)) * C.sizeof_double))
		for i, radius := range p.Radii {
			C.double_array_set(c.radii, C.int(i), C.double(radius))
		}
	}

	return c
}

func CreatePipeSupport(params PipeSupportParams) *Shape {
	cParams := params.to_struct()
	defer func() {
		if cParams.positions != nil {
			C.free(unsafe.Pointer(cParams.positions))
		}
		if cParams.radii != nil {
			C.free(unsafe.Pointer(cParams.radii))
		}
	}()

	shp := C.create_pipe_support(cParams)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreatePipeSupportWithPlace(params PipeSupportParams, position Point3, direction Dir3, xDir Dir3) *Shape {
	cParams := params.to_struct()
	defer func() {
		if cParams.positions != nil {
			C.free(unsafe.Pointer(cParams.positions))
		}
		if cParams.radii != nil {
			C.free(unsafe.Pointer(cParams.radii))
		}
	}()

	shp := C.create_pipe_support_with_place(cParams, position.val, direction.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

const (
	CoverPlateRectangle = 0
	CoverPlateSector    = 1
)

type CoverPlateParams struct {
	Style       int32
	Length      float32
	Width       float32
	SmallRadius float32
	LargeRadius float32
	Thickness   float32
}

func (p *CoverPlateParams) to_struct() C.cover_plate_params_t {
	var c C.cover_plate_params_t
	c.style = C.int(p.Style)
	c.length = C.double(p.Length)
	c.width = C.double(p.Width)
	c.smallRadius = C.double(p.SmallRadius)
	c.largeRadius = C.double(p.LargeRadius)
	c.thickness = C.double(p.Thickness)
	return c
}

func CreateCoverPlate(params CoverPlateParams) *Shape {
	shp := C.create_cover_plate(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateCoverPlateWithPlace(params CoverPlateParams, position Point3, normal Dir3, xDir Dir3) *Shape {
	shp := C.create_cover_plate_with_place(params.to_struct(), position.val, normal.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type CableRayParams struct {
	OuterLength    float32
	OuterHeight    float32
	InnerLength    float32
	InnerHeight    float32
	CoverThickness float32
}

func (p *CableRayParams) to_struct() C.cable_ray_params_t {
	var c C.cable_ray_params_t
	c.outerLength = C.double(p.OuterLength)
	c.outerHeight = C.double(p.OuterHeight)
	c.innerLength = C.double(p.InnerLength)
	c.innerHeight = C.double(p.InnerHeight)
	c.coverThickness = C.double(p.CoverThickness)
	return c
}

func CreateCableRay(params CableRayParams) *Shape {
	shp := C.create_cable_ray(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateCableRayWithPlace(params CableRayParams, position Point3, direction Dir3, xDir Dir3) *Shape {
	shp := C.create_cable_ray_with_place(params.to_struct(), position.val, direction.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

// 剖面类型枚举
type ProfileType int

const (
	ProfileTypeNone      ProfileType = C.PROFILE_TYPE_NONE
	ProfileTypeTriangle  ProfileType = C.PROFILE_TYPE_TRIANGLE
	ProfileTypeRectangle ProfileType = C.PROFILE_TYPE_RECTANGLE
	ProfileTypeCirc      ProfileType = C.PROFILE_TYPE_CIRC
	ProfileTypeElips     ProfileType = C.PROFILE_TYPE_ELIPS
	ProfileTypePolygon   ProfileType = C.PROFILE_TYPE_POLYGON
)

// 三角形剖面
type TriangleProfile struct {
	P1 Point3
	P2 Point3
	P3 Point3
}

// 矩形剖面
type RectangleProfile struct {
	P1 Point3
	P2 Point3
}

// 圆形剖面
type CircProfile struct {
	Center Point3
	Norm   Dir3
	Radius float32
}

// 椭圆剖面
type ElipsProfile struct {
	S1     Point3
	S2     Point3
	Center Point3
}

// 多边形剖面
type PolygonProfile struct {
	Edges      []Point3
	InnerEdges [][]Point3
}

// 剖面数据联合体
type ProfileData struct {
	Triangle  TriangleProfile
	Rectangle RectangleProfile
	Circ      CircProfile
	Elips     ElipsProfile
	Polygon   PolygonProfile
}

// 剖面结构体
type ShapeProfile struct {
	Type ProfileType
	Data ProfileData
}

func (p *ShapeProfile) toStruct() C.shape_profile_t {
	var c C.shape_profile_t

	switch p.Type {
	case ProfileTypeTriangle:
		tri := p.Data.Triangle
		c.type_ = C.PROFILE_TYPE_TRIANGLE
		c.triangle.p1 = tri.P1.val
		c.triangle.p2 = tri.P2.val
		c.triangle.p3 = tri.P3.val
	case ProfileTypeRectangle:
		rect := p.Data.Rectangle
		c.type_ = C.PROFILE_TYPE_RECTANGLE
		c.rectangle.p1 = rect.P1.val
		c.rectangle.p2 = rect.P2.val
	case ProfileTypeCirc:
		circ := p.Data.Circ
		c.type_ = C.PROFILE_TYPE_CIRC
		c.circ.center = circ.Center.val
		c.circ.norm = circ.Norm.val
		c.circ.radius = C.double(circ.Radius)
	case ProfileTypeElips:
		elips := p.Data.Elips
		c.type_ = C.PROFILE_TYPE_ELIPS
		c.elips.s1 = elips.S1.val
		c.elips.s2 = elips.S2.val
		c.elips.center = elips.Center.val
	case ProfileTypePolygon:
		poly := p.Data.Polygon
		c.type_ = C.PROFILE_TYPE_POLYGON

		// 转换外边缘
		edges := make([]C.pnt3d_t, len(poly.Edges))
		for i, pt := range poly.Edges {
			edges[i] = pt.val
		}
		c.polygon.edges = &edges[0]
		c.polygon.edgeCount = C.int(len(poly.Edges))

		// 转换内边缘
		if len(poly.InnerEdges) > 0 {
			innerCounts := make([]C.int, len(poly.InnerEdges))
			innerPtrs := make([]*C.pnt3d_t, len(poly.InnerEdges))
			innerArrays := make([][]C.pnt3d_t, len(poly.InnerEdges))

			for i, inner := range poly.InnerEdges {
				innerCounts[i] = C.int(len(inner))
				innerArrays[i] = make([]C.pnt3d_t, len(inner))
				for j, pt := range inner {
					innerArrays[i][j] = pt.val
				}
				innerPtrs[i] = &innerArrays[i][0]
			}

			c.polygon.inners = &innerPtrs[0]
			c.polygon.innerCounts = &innerCounts[0]
			c.polygon.innerArrayCount = C.int(len(poly.InnerEdges))
		}
	}

	return c
}

// 旋转参数
type RevolParams struct {
	Profile ShapeProfile
	Axis    Axis1
	Angle   float32
}

func (p *RevolParams) to_struct() C.revol_params_t {
	var c C.revol_params_t

	c.profile = p.Profile.toStruct()

	// 转换旋转轴和角度
	c.axis = p.Axis.val
	c.angle = C.double(p.Angle)

	return c
}

func CreateRevol(params RevolParams) *Shape {
	cParams := params.to_struct()
	shp := C.create_revol(cParams)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateRevolWithPlace(params RevolParams, position Point3, direction Dir3, xDir Dir3) *Shape {
	cParams := params.to_struct()
	shp := C.create_revol_with_place(cParams, position.val, direction.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type PrismParams struct {
	Profile   ShapeProfile
	Direction Dir3
	Height    float64
}

func (p *PrismParams) to_struct() C.prism_params_t {
	var c C.prism_params_t

	c.profile = p.Profile.toStruct()

	// 转换拉伸方向
	c.direction = p.Direction.val
	c.height = C.double(p.Height)

	return c
}

func CreatePrism(params PrismParams) *Shape {
	cParams := params.to_struct()
	shp := C.create_prism(cParams)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreatePrismWithPlace(params PrismParams, position Point3, direction Dir3, xDir Dir3) *Shape {
	cParams := params.to_struct()
	shp := C.create_prism_with_place(cParams, position.val, direction.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

// 线段类型枚举
type SegmentType int

const (
	SegmentTypeLine SegmentType = iota
	SegmentTypeThreePointArc
	SegmentTypeCircleCenterArc
	SegmentTypeSpline
	SegmentTypeBezier
)

func SampleSegmentPoints(wires [][]Point3, segments []SegmentType, tessellation float64) []Point3 {
	var wireCounts []C.int
	var allPoints []C.pnt3d_t
	for _, wire := range wires {
		wireCounts = append(wireCounts, C.int(len(wire)))
		for _, pt := range wire {
			allPoints = append(allPoints, pt.val)
		}
	}

	var cSegments []C.segment_type_t
	for _, seg := range segments {
		cSegments = append(cSegments, C.segment_type_t(seg))
	}

	var outCount C.int
	cPoints := C.sample_segment_points(
		&allPoints[0],
		&wireCounts[0],
		C.int(len(wires)),
		&cSegments[0],
		C.int(len(segments)),
		C.double(tessellation),
		&outCount,
	)
	defer C.free(unsafe.Pointer(cPoints))

	result := make([]Point3, outCount)
	for i := 0; i < int(outCount); i++ {
		result[i] = Point3{val: *(*C.pnt3d_t)(unsafe.Pointer(uintptr(unsafe.Pointer(cPoints)) + uintptr(i)*C.sizeof_pnt3d_t))}
	}

	return result
}

// 连接形状模式枚举
type JointShapeMode int

const (
	JointShapeModeSphere JointShapeMode = iota
	JointShapeModeBox
	JointShapeModeCylinder
)

// 管道端点参数
type PipeEndpoint struct {
	Id           string
	Offset       Point3
	Normal       Dir3
	Profile      ShapeProfile
	InnerProfile *ShapeProfile // 可为nil
}

// 管道参数
type PipeParams struct {
	Wire           []Point3
	Profiles       []ShapeProfile
	InnerProfiles  []ShapeProfile // 可为nil
	SegmentType    SegmentType
	TransitionMode TransitionMode
	UpDir          *Dir3
}

func (p *PipeParams) to_struct() C.pipe_params_t {
	var c C.pipe_params_t

	// 转换路径点
	wire := make([]C.pnt3d_t, len(p.Wire))
	for i, pt := range p.Wire {
		wire[i] = pt.val
	}
	c.wire = &wire[0]
	c.wire_count = C.int(len(p.Wire))

	// 转换剖面数组
	cProfiles := make([]C.shape_profile_t, len(p.Profiles))
	for i, profile := range p.Profiles {
		cProfiles[i] = profile.toStruct()
	}

	c.profiles = &cProfiles[0]
	c.profile_count = C.int(len(p.Profiles))

	// 转换内剖面数组(如果存在)
	if len(p.InnerProfiles) > 0 {
		innerProfilePtrs := make([]*C.shape_profile_t, len(p.InnerProfiles))
		innerProfileArrays := make([]C.shape_profile_t, len(p.InnerProfiles))
		innerProfileCounts := make([]C.int, len(p.InnerProfiles))

		for i, innerProfile := range p.InnerProfiles {
			innerProfileArrays[i] = innerProfile.toStruct()
			innerProfilePtrs[i] = &innerProfileArrays[i]
			innerProfileCounts[i] = C.int(len(p.InnerProfiles))
		}

		c.inner_profiles = &innerProfilePtrs[0]
		c.inner_profile_counts = &innerProfileCounts[0]
	}

	if p.UpDir != nil {
		c.up_dir = &p.UpDir.val
	} else {
		c.up_dir = nil
	}

	// 转换线段类型和过渡模式
	c.segment_type = C.segment_type_t(p.SegmentType)
	c.transition_mode = C.transition_mode_t(p.TransitionMode)

	return c
}

func CreatePipe(params PipeParams) *Shape {
	cParams := params.to_struct()
	shp := C.create_pipe(cParams)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreatePipeWithSplitDistances(params PipeParams, startDistance, endDistance float64) *Shape {
	cParams := params.to_struct()
	shp := C.create_pipe_with_split_distances(cParams, C.double(startDistance), C.double(endDistance))
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreatePipeCenterline(params PipeParams) *Wire {
	cParams := params.to_struct()
	wire := C.create_pipe_centerline(cParams)
	w := &Wire{inner: &innerWire{val: wire}}
	runtime.SetFinalizer(w.inner, (*innerWire).free)
	return w
}

func CreatePipeWithPlace(params PipeParams, position Point3, direction Dir3, xDir Dir3) *Shape {
	cParams := params.to_struct()
	shp := C.create_pipe_with_place(cParams, position.val, direction.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type MultiSegmentPipeParams struct {
	Wires          [][]Point3
	Profiles       []ShapeProfile
	InnerProfiles  []ShapeProfile // 可为nil
	SegmentTypes   []SegmentType
	TransitionMode TransitionMode
	UpDir          *Dir3
}

func (p *MultiSegmentPipeParams) to_struct() C.multi_segment_pipe_params_t {
	var c C.multi_segment_pipe_params_t

	// 转换路径点数组
	wirePtrs := make([]*C.pnt3d_t, len(p.Wires))
	wireCounts := make([]C.int, len(p.Wires))
	wireArrays := make([][]C.pnt3d_t, len(p.Wires))

	for i, wire := range p.Wires {
		wireArrays[i] = make([]C.pnt3d_t, len(wire))
		for j, pt := range wire {
			wireArrays[i][j] = pt.val
		}
		wirePtrs[i] = &wireArrays[i][0]
		wireCounts[i] = C.int(len(wire))
	}

	c.wires = &wirePtrs[0]
	c.wire_counts = &wireCounts[0]
	c.wire_array_count = C.int(len(p.Wires))

	// 转换剖面数组
	cProfiles := make([]C.shape_profile_t, len(p.Profiles))
	for i, profile := range p.Profiles {
		cProfiles[i] = profile.toStruct()
	}

	c.profiles = &cProfiles[0]
	c.profile_count = C.int(len(p.Profiles))

	// 转换内剖面数组(如果存在)
	if len(p.InnerProfiles) > 0 {
		innerProfilePtrs := make([]*C.shape_profile_t, len(p.InnerProfiles))
		innerProfileArrays := make([]C.shape_profile_t, len(p.InnerProfiles))
		innerProfileCounts := make([]C.int, len(p.InnerProfiles))

		for i, innerProfile := range p.InnerProfiles {
			innerProfileArrays[i] = innerProfile.toStruct()
			innerProfilePtrs[i] = &innerProfileArrays[i]
			innerProfileCounts[i] = C.int(len(p.InnerProfiles))
		}

		c.inner_profiles = &innerProfilePtrs[0]
		c.inner_profile_counts = &innerProfileCounts[0]
	}

	// 转换线段类型数组
	if len(p.SegmentTypes) > 0 {
		cSegmentTypes := make([]C.segment_type_t, len(p.SegmentTypes))
		for i, st := range p.SegmentTypes {
			cSegmentTypes[i] = C.segment_type_t(st)
		}
		c.segment_types = &cSegmentTypes[0]
		c.segment_type_count = C.int(len(p.SegmentTypes))
	}

	if p.UpDir != nil {
		c.up_dir = &p.UpDir.val
	} else {
		c.up_dir = nil
	}

	// 转换过渡模式
	c.transition_mode = C.transition_mode_t(p.TransitionMode)

	return c
}

func CreateMultiSegmentPipe(params MultiSegmentPipeParams) *Shape {
	cParams := params.to_struct()
	shp := C.create_multi_segment_pipe(cParams)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateMultiSegmentPipeWithSplitDistances(params MultiSegmentPipeParams, startDistance, endDistance float64) *Shape {
	cParams := params.to_struct()
	shp := C.create_multi_segment_pipe_with_split_distances(cParams, C.double(startDistance), C.double(endDistance))
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateMultiSegmentPipeCenterline(params MultiSegmentPipeParams) *Wire {
	cParams := params.to_struct()
	wire := C.create_multi_segment_pipe_centerline(cParams)
	w := &Wire{inner: &innerWire{val: wire}}
	runtime.SetFinalizer(w.inner, (*innerWire).free)
	return w
}

func CreateMultiSegmentPipeWithPlace(params MultiSegmentPipeParams, position Point3, direction Dir3, xDir Dir3) *Shape {
	cParams := params.to_struct()
	shp := C.create_multi_segment_pipe_with_place(cParams, position.val, direction.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type ProfileLayer struct {
	Name          string
	Profiles      []ShapeProfile
	InnerProfiles []ShapeProfile
}

type MultiLayerExtrusionStructureParams struct {
	Wires          [][]Point3
	SegmentTypes   []SegmentType
	Layers         []ProfileLayer
	TransitionMode TransitionMode
	UpDir          *Dir3
}

func (p *ProfileLayer) toStruct() C.profile_layer_t {
	var c C.profile_layer_t
	c.name = C.CString(p.Name)

	// 转换profiles
	if len(p.Profiles) > 0 {
		c.profiles = (*C.shape_profile_t)(C.malloc(C.size_t(len(p.Profiles)) * C.sizeof_shape_profile_t))
		for i, profile := range p.Profiles {
			cProfile := profile.toStruct()
			*(*C.shape_profile_t)(unsafe.Pointer(uintptr(unsafe.Pointer(c.profiles)) + uintptr(i)*C.sizeof_shape_profile_t)) = cProfile
		}
		c.profile_count = C.int(len(p.Profiles))
	}

	// 转换inner_profiles
	if len(p.InnerProfiles) > 0 {
		c.inner_profiles = (*C.shape_profile_t)(C.malloc(C.size_t(len(p.InnerProfiles)) * C.sizeof_shape_profile_t))
		for i, profile := range p.InnerProfiles {
			cProfile := profile.toStruct()
			*(*C.shape_profile_t)(unsafe.Pointer(uintptr(unsafe.Pointer(c.inner_profiles)) + uintptr(i)*C.sizeof_shape_profile_t)) = cProfile
		}
		c.inner_profile_count = C.int(len(p.InnerProfiles))
	}

	return c
}

func (p *MultiLayerExtrusionStructureParams) toStruct() C.multi_layer_extrusion_structure_params_t {
	var c C.multi_layer_extrusion_structure_params_t

	// 转换wires
	if len(p.Wires) > 0 {
		wirePtrs := make([]*C.pnt3d_t, len(p.Wires))
		wireCounts := make([]C.int, len(p.Wires))
		wireArrays := make([][]C.pnt3d_t, len(p.Wires))

		for i, wire := range p.Wires {
			wireArrays[i] = make([]C.pnt3d_t, len(wire))
			for j, pt := range wire {
				wireArrays[i][j] = pt.val
			}
			wirePtrs[i] = &wireArrays[i][0]
			wireCounts[i] = C.int(len(wire))
		}

		c.wires = &wirePtrs[0]
		c.wire_counts = &wireCounts[0]
		c.wire_array_count = C.int(len(p.Wires))
	}

	// 转换segment_types
	if len(p.SegmentTypes) > 0 {
		c.segment_types = (*C.segment_type_t)(C.malloc(C.size_t(len(p.SegmentTypes)) * C.sizeof_segment_type_t))
		for i, st := range p.SegmentTypes {
			*(*C.segment_type_t)(unsafe.Pointer(uintptr(unsafe.Pointer(c.segment_types)) + uintptr(i)*C.sizeof_segment_type_t)) = C.segment_type_t(st)
		}
		c.segment_type_count = C.int(len(p.SegmentTypes))
	}

	// 转换layers
	if len(p.Layers) > 0 {
		c.layers = (*C.profile_layer_t)(C.malloc(C.size_t(len(p.Layers)) * C.sizeof_profile_layer_t))
		for i, layer := range p.Layers {
			cLayer := layer.toStruct()
			*(*C.profile_layer_t)(unsafe.Pointer(uintptr(unsafe.Pointer(c.layers)) + uintptr(i)*C.sizeof_profile_layer_t)) = cLayer
		}
		c.layer_count = C.int(len(p.Layers))
	}

	c.transition_mode = C.transition_mode_t(p.TransitionMode)

	if p.UpDir != nil {
		c.upDir = &p.UpDir.val
	}

	return c
}

func freeMultiLayerParams(c C.multi_layer_extrusion_structure_params_t) {
	// 释放layers内存
	if c.layers != nil {
		for i := 0; i < int(c.layer_count); i++ {
			layer := (*C.profile_layer_t)(unsafe.Pointer(uintptr(unsafe.Pointer(c.layers)) + uintptr(i)*C.sizeof_profile_layer_t))
			C.free(unsafe.Pointer(layer.name))
			if layer.profiles != nil {
				C.free(unsafe.Pointer(layer.profiles))
			}
			if layer.inner_profiles != nil {
				C.free(unsafe.Pointer(layer.inner_profiles))
			}
		}
		C.free(unsafe.Pointer(c.layers))
	}
}

func CreateMultiLayerExtrusionStructure(params MultiLayerExtrusionStructureParams) (map[string]*Shape, error) {
	cParams := params.toStruct()
	defer freeMultiLayerParams(cParams)

	var outCount C.int
	cShapes := C.create_multi_layer_extrusion_structure(cParams, &outCount)
	defer C.free(unsafe.Pointer(cShapes))

	if cShapes == nil || outCount == 0 {
		return nil, errors.New("failed to create multi-layer extrusion structure")
	}

	shapes := make(map[string]*Shape)
	for i := 0; i < int(outCount); i++ {
		cShape := *(**C.topo_shape_t)(unsafe.Pointer(uintptr(unsafe.Pointer(cShapes)) + uintptr(i)*unsafe.Sizeof(cShapes)))
		if cShape != nil {
			name := params.Layers[i].Name
			shapes[name] = &Shape{
				inner: &innerShape{val: cShape},
			}
			runtime.SetFinalizer(shapes[name].inner, (*innerShape).free)
		}
	}

	return shapes, nil
}

func CreateMultiLayerExtrusionStructureCenterline(params MultiLayerExtrusionStructureParams) *Wire {
	cParams := params.toStruct()
	defer freeMultiLayerParams(cParams)

	wire := C.create_multi_layer_extrusion_structure_centerline(cParams)
	w := &Wire{inner: &innerWire{val: wire}}
	runtime.SetFinalizer(w.inner, (*innerWire).free)
	return w
}

func CreateMultiLayerExtrusionStructureWithPlace(params MultiLayerExtrusionStructureParams, position Point3, direction Dir3, xDir Dir3) (map[string]*Shape, error) {
	cParams := params.toStruct()
	defer freeMultiLayerParams(cParams)

	var outCount C.int
	cShapes := C.create_multi_layer_extrusion_structure_with_place(cParams, position.val, direction.val, xDir.val, &outCount)
	defer C.free(unsafe.Pointer(cShapes))

	if cShapes == nil || outCount == 0 {
		return nil, errors.New("failed to create multi-layer extrusion structure with place")
	}

	shapes := make(map[string]*Shape)
	for i := 0; i < int(outCount); i++ {
		cShape := *(**C.topo_shape_t)(unsafe.Pointer(uintptr(unsafe.Pointer(cShapes)) + uintptr(i)*unsafe.Sizeof(cShapes)))
		if cShape != nil {
			name := params.Layers[i].Name
			shapes[name] = &Shape{
				inner: &innerShape{val: cShape},
			}
			runtime.SetFinalizer(shapes[name].inner, (*innerShape).free)
		}
	}

	return shapes, nil
}

// 管道连接参数
type PipeJointParams struct {
	Ins     []PipeEndpoint
	Outs    []PipeEndpoint
	Mode    JointShapeMode
	Flanged bool
	UpDir   *Dir3
}

func (p *PipeJointParams) to_struct() C.pipe_joint_params_t {
	var c C.pipe_joint_params_t

	// 转换输入端点
	if len(p.Ins) > 0 {
		ins := make([]C.pipe_endpoint_t, len(p.Ins))
		for i, in := range p.Ins {
			ins[i].id = C.CString(in.Id)
			ins[i].offset = in.Offset.val
			ins[i].normal = in.Normal.val

			// 转换输入剖面
			switch in.Profile.Type {
			case ProfileTypeTriangle:
				tri := in.Profile.Data.Triangle
				ins[i].profile.type_ = C.PROFILE_TYPE_TRIANGLE
				ins[i].profile.triangle.p1 = tri.P1.val
				ins[i].profile.triangle.p2 = tri.P2.val
				ins[i].profile.triangle.p3 = tri.P3.val
			case ProfileTypeRectangle:
				rect := in.Profile.Data.Rectangle
				ins[i].profile.type_ = C.PROFILE_TYPE_RECTANGLE
				ins[i].profile.rectangle.p1 = rect.P1.val
				ins[i].profile.rectangle.p2 = rect.P2.val
			case ProfileTypeCirc:
				circ := in.Profile.Data.Circ
				ins[i].profile.type_ = C.PROFILE_TYPE_CIRC
				ins[i].profile.circ.center = circ.Center.val
				ins[i].profile.circ.norm = circ.Norm.val
				ins[i].profile.circ.radius = C.double(circ.Radius)
			case ProfileTypeElips:
				elips := in.Profile.Data.Elips
				ins[i].profile.type_ = C.PROFILE_TYPE_ELIPS
				ins[i].profile.elips.s1 = elips.S1.val
				ins[i].profile.elips.s2 = elips.S2.val
				ins[i].profile.elips.center = elips.Center.val
			case ProfileTypePolygon:
				poly := in.Profile.Data.Polygon
				ins[i].profile.type_ = C.PROFILE_TYPE_POLYGON

				edges := make([]C.pnt3d_t, len(poly.Edges))
				for j, pt := range poly.Edges {
					edges[j] = pt.val
				}
				ins[i].profile.polygon.edges = &edges[0]
				ins[i].profile.polygon.edgeCount = C.int(len(poly.Edges))

				if len(poly.InnerEdges) > 0 {
					innerCounts := make([]C.int, len(poly.InnerEdges))
					innerPtrs := make([]*C.pnt3d_t, len(poly.InnerEdges))
					innerArrays := make([][]C.pnt3d_t, len(poly.InnerEdges))

					for j, inner := range poly.InnerEdges {
						innerCounts[j] = C.int(len(inner))
						innerArrays[j] = make([]C.pnt3d_t, len(inner))
						for k, pt := range inner {
							innerArrays[j][k] = pt.val
						}
						innerPtrs[j] = &innerArrays[j][0]
					}

					ins[i].profile.polygon.inners = &innerPtrs[0]
					ins[i].profile.polygon.innerCounts = &innerCounts[0]
					ins[i].profile.polygon.innerArrayCount = C.int(len(poly.InnerEdges))
				}
			}

			// 转换内剖面(如果存在)
			if in.InnerProfile != nil {
				innerProfile := new(C.shape_profile_t)
				switch in.InnerProfile.Type {
				case ProfileTypeTriangle:
					tri := in.InnerProfile.Data.Triangle
					innerProfile.type_ = C.PROFILE_TYPE_TRIANGLE
					innerProfile.triangle.p1 = tri.P1.val
					innerProfile.triangle.p2 = tri.P2.val
					innerProfile.triangle.p3 = tri.P3.val
				case ProfileTypeRectangle:
					rect := in.InnerProfile.Data.Rectangle
					innerProfile.type_ = C.PROFILE_TYPE_RECTANGLE
					innerProfile.rectangle.p1 = rect.P1.val
					innerProfile.rectangle.p2 = rect.P2.val
				case ProfileTypeCirc:
					circ := in.InnerProfile.Data.Circ
					innerProfile.type_ = C.PROFILE_TYPE_CIRC
					innerProfile.circ.center = circ.Center.val
					innerProfile.circ.norm = circ.Norm.val
					innerProfile.circ.radius = C.double(circ.Radius)
				case ProfileTypeElips:
					elips := in.InnerProfile.Data.Elips
					innerProfile.type_ = C.PROFILE_TYPE_ELIPS
					innerProfile.elips.s1 = elips.S1.val
					innerProfile.elips.s2 = elips.S2.val
					innerProfile.elips.center = elips.Center.val
				case ProfileTypePolygon:
					poly := in.InnerProfile.Data.Polygon
					innerProfile.type_ = C.PROFILE_TYPE_POLYGON

					edges := make([]C.pnt3d_t, len(poly.Edges))
					for j, pt := range poly.Edges {
						edges[j] = pt.val
					}
					innerProfile.polygon.edges = &edges[0]
					innerProfile.polygon.edgeCount = C.int(len(poly.Edges))

					if len(poly.InnerEdges) > 0 {
						innerCounts := make([]C.int, len(poly.InnerEdges))
						innerPtrs := make([]*C.pnt3d_t, len(poly.InnerEdges))
						innerArrays := make([][]C.pnt3d_t, len(poly.InnerEdges))

						for j, inner := range poly.InnerEdges {
							innerCounts[j] = C.int(len(inner))
							innerArrays[j] = make([]C.pnt3d_t, len(inner))
							for k, pt := range inner {
								innerArrays[j][k] = pt.val
							}
							innerPtrs[j] = &innerArrays[j][0]
						}

						innerProfile.polygon.inners = &innerPtrs[0]
						innerProfile.polygon.innerCounts = &innerCounts[0]
						innerProfile.polygon.innerArrayCount = C.int(len(poly.InnerEdges))
					}
				}
				ins[i].inner_profile = innerProfile
			}
		}
		c.ins = &ins[0]
		c.in_count = C.int(len(p.Ins))
	}

	// 转换输出端点(与输入端点类似)
	if len(p.Outs) > 0 {
		outs := make([]C.pipe_endpoint_t, len(p.Outs))
		for i, out := range p.Outs {
			outs[i].id = C.CString(out.Id)
			outs[i].offset = out.Offset.val
			outs[i].normal = out.Normal.val

			// 转换输出剖面(与输入剖面类似)
			switch out.Profile.Type {
			case ProfileTypeTriangle:
				tri := out.Profile.Data.Triangle
				outs[i].profile.type_ = C.PROFILE_TYPE_TRIANGLE
				outs[i].profile.triangle.p1 = tri.P1.val
				outs[i].profile.triangle.p2 = tri.P2.val
				outs[i].profile.triangle.p3 = tri.P3.val
			case ProfileTypeRectangle:
				rect := out.Profile.Data.Rectangle
				outs[i].profile.type_ = C.PROFILE_TYPE_RECTANGLE
				outs[i].profile.rectangle.p1 = rect.P1.val
				outs[i].profile.rectangle.p2 = rect.P2.val
			case ProfileTypeCirc:
				circ := out.Profile.Data.Circ
				outs[i].profile.type_ = C.PROFILE_TYPE_CIRC
				outs[i].profile.circ.center = circ.Center.val
				outs[i].profile.circ.norm = circ.Norm.val
				outs[i].profile.circ.radius = C.double(circ.Radius)
			case ProfileTypeElips:
				elips := out.Profile.Data.Elips
				outs[i].profile.type_ = C.PROFILE_TYPE_ELIPS
				outs[i].profile.elips.s1 = elips.S1.val
				outs[i].profile.elips.s2 = elips.S2.val
				outs[i].profile.elips.center = elips.Center.val
			case ProfileTypePolygon:
				poly := out.Profile.Data.Polygon
				outs[i].profile.type_ = C.PROFILE_TYPE_POLYGON

				edges := make([]C.pnt3d_t, len(poly.Edges))
				for j, pt := range poly.Edges {
					edges[j] = pt.val
				}
				outs[i].profile.polygon.edges = &edges[0]
				outs[i].profile.polygon.edgeCount = C.int(len(poly.Edges))

				if len(poly.InnerEdges) > 0 {
					innerCounts := make([]C.int, len(poly.InnerEdges))
					innerPtrs := make([]*C.pnt3d_t, len(poly.InnerEdges))
					innerArrays := make([][]C.pnt3d_t, len(poly.InnerEdges))

					for j, inner := range poly.InnerEdges {
						innerCounts[j] = C.int(len(inner))
						innerArrays[j] = make([]C.pnt3d_t, len(inner))
						for k, pt := range inner {
							innerArrays[j][k] = pt.val
						}
						innerPtrs[j] = &innerArrays[j][0]
					}

					outs[i].profile.polygon.inners = &innerPtrs[0]
					outs[i].profile.polygon.innerCounts = &innerCounts[0]
					outs[i].profile.polygon.innerArrayCount = C.int(len(poly.InnerEdges))
				}
			}

			// 转换内剖面(如果存在)
			if out.InnerProfile != nil {
				innerProfile := new(C.shape_profile_t)
				switch out.InnerProfile.Type {
				case ProfileTypeTriangle:
					tri := out.InnerProfile.Data.Triangle
					innerProfile.type_ = C.PROFILE_TYPE_TRIANGLE
					innerProfile.triangle.p1 = tri.P1.val
					innerProfile.triangle.p2 = tri.P2.val
					innerProfile.triangle.p3 = tri.P3.val
				case ProfileTypeRectangle:
					rect := out.InnerProfile.Data.Rectangle
					innerProfile.type_ = C.PROFILE_TYPE_RECTANGLE
					innerProfile.rectangle.p1 = rect.P1.val
					innerProfile.rectangle.p2 = rect.P2.val
				case ProfileTypeCirc:
					circ := out.InnerProfile.Data.Circ
					innerProfile.type_ = C.PROFILE_TYPE_CIRC
					innerProfile.circ.center = circ.Center.val
					innerProfile.circ.norm = circ.Norm.val
					innerProfile.circ.radius = C.double(circ.Radius)
				case ProfileTypeElips:
					elips := out.InnerProfile.Data.Elips
					innerProfile.type_ = C.PROFILE_TYPE_ELIPS
					innerProfile.elips.s1 = elips.S1.val
					innerProfile.elips.s2 = elips.S2.val
					innerProfile.elips.center = elips.Center.val
				case ProfileTypePolygon:
					poly := out.InnerProfile.Data.Polygon
					innerProfile.type_ = C.PROFILE_TYPE_POLYGON

					edges := make([]C.pnt3d_t, len(poly.Edges))
					for j, pt := range poly.Edges {
						edges[j] = pt.val
					}
					innerProfile.polygon.edges = &edges[0]
					innerProfile.polygon.edgeCount = C.int(len(poly.Edges))

					if len(poly.InnerEdges) > 0 {
						innerCounts := make([]C.int, len(poly.InnerEdges))
						innerPtrs := make([]*C.pnt3d_t, len(poly.InnerEdges))
						innerArrays := make([][]C.pnt3d_t, len(poly.InnerEdges))

						for j, inner := range poly.InnerEdges {
							innerCounts[j] = C.int(len(inner))
							innerArrays[j] = make([]C.pnt3d_t, len(inner))
							for k, pt := range inner {
								innerArrays[j][k] = pt.val
							}
							innerPtrs[j] = &innerArrays[j][0]
						}

						innerProfile.polygon.inners = &innerPtrs[0]
						innerProfile.polygon.innerCounts = &innerCounts[0]
						innerProfile.polygon.innerArrayCount = C.int(len(poly.InnerEdges))
					}
				}
				outs[i].inner_profile = innerProfile
			}
		}
		c.outs = &outs[0]
		c.out_count = C.int(len(p.Outs))
	}

	// 转换连接模式和边缘平滑
	c.mode = C.joint_shape_mode_t(p.Mode)
	if p.Flanged {
		c.flanged = C.bool(true)
	} else {
		c.flanged = C.bool(false)
	}

	if p.UpDir != nil {
		c.up_dir = &p.UpDir.val
	} else {
		c.up_dir = nil
	}
	return c
}

func CreatePipeJoint(params PipeJointParams) *Shape {
	cParams := params.to_struct()
	shp := C.create_pipe_joint(cParams)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreatePipeJointWithPlace(params PipeJointParams, position Point3, direction Dir3, xDir Dir3) *Shape {
	cParams := params.to_struct()
	shp := C.create_pipe_joint_with_place(cParams, position.val, direction.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

// 悬链线参数
type CatenaryParams struct {
	P1           Point3
	P2           Point3
	Profile      ShapeProfile
	Slack        float64
	MaxSag       float64
	UpDir        *Dir3
	Tessellation float64
}

func (p *CatenaryParams) to_struct() C.catenary_params_t {
	var c C.catenary_params_t

	// 转换端点坐标
	c.p1 = p.P1.val
	c.p2 = p.P2.val

	// 转换剖面数据
	switch p.Profile.Type {
	case ProfileTypeTriangle:
		tri := p.Profile.Data.Triangle
		c.profile.type_ = C.PROFILE_TYPE_TRIANGLE
		c.profile.triangle.p1 = tri.P1.val
		c.profile.triangle.p2 = tri.P2.val
		c.profile.triangle.p3 = tri.P3.val
	case ProfileTypeRectangle:
		rect := p.Profile.Data.Rectangle
		c.profile.type_ = C.PROFILE_TYPE_RECTANGLE
		c.profile.rectangle.p1 = rect.P1.val
		c.profile.rectangle.p2 = rect.P2.val
	case ProfileTypeCirc:
		circ := p.Profile.Data.Circ
		c.profile.type_ = C.PROFILE_TYPE_CIRC
		c.profile.circ.center = circ.Center.val
		c.profile.circ.norm = circ.Norm.val
		c.profile.circ.radius = C.double(circ.Radius)
	case ProfileTypeElips:
		elips := p.Profile.Data.Elips
		c.profile.type_ = C.PROFILE_TYPE_ELIPS
		c.profile.elips.s1 = elips.S1.val
		c.profile.elips.s2 = elips.S2.val
		c.profile.elips.center = elips.Center.val
	case ProfileTypePolygon:
		poly := p.Profile.Data.Polygon
		c.profile.type_ = C.PROFILE_TYPE_POLYGON

		edges := make([]C.pnt3d_t, len(poly.Edges))
		for i, pt := range poly.Edges {
			edges[i] = pt.val
		}
		c.profile.polygon.edges = &edges[0]
		c.profile.polygon.edgeCount = C.int(len(poly.Edges))

		if len(poly.InnerEdges) > 0 {
			innerCounts := make([]C.int, len(poly.InnerEdges))
			innerPtrs := make([]*C.pnt3d_t, len(poly.InnerEdges))
			innerArrays := make([][]C.pnt3d_t, len(poly.InnerEdges))

			for i, inner := range poly.InnerEdges {
				innerCounts[i] = C.int(len(inner))
				innerArrays[i] = make([]C.pnt3d_t, len(inner))
				for j, pt := range inner {
					innerArrays[i][j] = pt.val
				}
				innerPtrs[i] = &innerArrays[i][0]
			}

			c.profile.polygon.inners = &innerPtrs[0]
			c.profile.polygon.innerCounts = &innerCounts[0]
			c.profile.polygon.innerArrayCount = C.int(len(poly.InnerEdges))
		}
	}

	// 转换其他参数
	c.slack = C.double(p.Slack)
	c.max_sag = C.double(p.MaxSag)
	c.tessellation = C.double(p.Tessellation)

	if p.UpDir != nil {
		c.up_dir = &p.UpDir.val
	} else {
		c.up_dir = nil
	}
	return c
}

func CreateCatenary(params CatenaryParams) *Shape {
	cParams := params.to_struct()
	shp := C.create_catenary(cParams)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateCatenaryWithPlace(params CatenaryParams, position Point3, direction Dir3, xDir Dir3) *Shape {
	cParams := params.to_struct()
	shp := C.create_catenary_with_place(cParams, position.val, direction.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

// 长方体参数
type BoxShapeParams struct {
	Point1 Point3
	Point2 Point3
}

func (p *BoxShapeParams) to_struct() C.box_shape_params_t {
	var c C.box_shape_params_t
	c.point1 = p.Point1.val
	c.point2 = p.Point2.val
	return c
}

func CreateBoxShape(params BoxShapeParams) *Shape {
	cParams := params.to_struct()
	shp := C.create_box_shape(cParams)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateBoxShapeWithPlace(params BoxShapeParams, position Point3, direction Dir3, xDir Dir3) *Shape {
	cParams := params.to_struct()
	shp := C.create_box_shape_with_place(cParams, position.val, direction.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

// 圆锥参数
type ConeShapeParams struct {
	Radius1 float64
	Radius2 float64
	Height  float64
	Angle   *float64 // 可为nil
}

func (p *ConeShapeParams) to_struct() C.cone_shape_params_t {
	var c C.cone_shape_params_t
	c.radius1 = C.double(p.Radius1)
	c.radius2 = C.double(p.Radius2)
	c.height = C.double(p.Height)

	// 转换角度参数(如果存在)
	if p.Angle != nil {
		c.angle = (*C.double)(unsafe.Pointer(p.Angle))
	} else {
		c.angle = nil
	}

	return c
}

func CreateConeShape(params ConeShapeParams) *Shape {
	cParams := params.to_struct()
	shp := C.create_cone_shape(cParams)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateConeShapeWithPlace(params ConeShapeParams, position Point3, direction Dir3, xDir Dir3) *Shape {
	cParams := params.to_struct()
	shp := C.create_cone_shape_with_place(cParams, position.val, direction.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

// 圆柱参数
type CylinderShapeParams struct {
	Radius float64
	Height float64
	Angle  *float64 // 可为nil
}

func (p *CylinderShapeParams) to_struct() C.cylinder_shape_params_t {
	var c C.cylinder_shape_params_t
	c.radius = C.double(p.Radius)
	c.height = C.double(p.Height)

	// 转换角度参数(如果存在)
	if p.Angle != nil {
		c.angle = (*C.double)(unsafe.Pointer(p.Angle))
	} else {
		c.angle = nil
	}

	return c
}

func CreateCylinderShape(params CylinderShapeParams) *Shape {
	cParams := params.to_struct()
	shp := C.create_cylinder_shape(cParams)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateCylinderShapeWithPlace(params CylinderShapeParams, position Point3, direction Dir3, xDir Dir3) *Shape {
	cParams := params.to_struct()
	shp := C.create_cylinder_shape_with_place(cParams, position.val, direction.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

// 球体参数
type SphereShapeParams struct {
	Center *Point3  // 中心点(可为nil)
	Radius float64  // 半径
	Angle1 *float64 // 角度1(可为nil)
	Angle2 *float64 // 角度2(可为nil)
	Angle  *float64 // 角度(可为nil)
}

func (p *SphereShapeParams) to_struct() C.sphere_shape_params_t {
	var c C.sphere_shape_params_t

	// 转换中心点(如果存在)
	if p.Center != nil {
		c.center = &p.Center.val
	} else {
		c.center = nil
	}

	c.radius = C.double(p.Radius)

	// 转换可选角度参数
	if p.Angle1 != nil {
		c.angle1 = (*C.double)(unsafe.Pointer(p.Angle1))
	}
	if p.Angle2 != nil {
		c.angle2 = (*C.double)(unsafe.Pointer(p.Angle2))
	}
	if p.Angle != nil {
		c.angle = (*C.double)(unsafe.Pointer(p.Angle))
	}

	return c
}

func CreateSphereShape(params SphereShapeParams) *Shape {
	cParams := params.to_struct()
	shp := C.create_sphere_shape(cParams)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateSphereShapeWithPlace(params SphereShapeParams, position Point3, direction Dir3, xDir Dir3) *Shape {
	cParams := params.to_struct()
	shp := C.create_sphere_shape_with_place(cParams, position.val, direction.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

// 圆环参数
type TorusShapeParams struct {
	Radius1 float64  // 主半径
	Radius2 float64  // 次半径
	Angle1  *float64 // 起始角度(可为nil)
	Angle2  *float64 // 结束角度(可为nil)
	Angle   *float64 // 总角度(可为nil)
}

func (p *TorusShapeParams) to_struct() C.torus_shape_params_t {
	var c C.torus_shape_params_t
	c.radius1 = C.double(p.Radius1)
	c.radius2 = C.double(p.Radius2)

	// 转换可选角度参数
	if p.Angle1 != nil {
		c.angle1 = (*C.double)(unsafe.Pointer(p.Angle1))
	}
	if p.Angle2 != nil {
		c.angle2 = (*C.double)(unsafe.Pointer(p.Angle2))
	}
	if p.Angle != nil {
		c.angle = (*C.double)(unsafe.Pointer(p.Angle))
	}

	return c
}

func CreateTorusShape(params TorusShapeParams) *Shape {
	cParams := params.to_struct()
	shp := C.create_torus_shape(cParams)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateTorusShapeWithPlace(params TorusShapeParams, position Point3, direction Dir3, xDir Dir3) *Shape {
	cParams := params.to_struct()
	shp := C.create_torus_shape_with_place(cParams, position.val, direction.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

// 旋转体参数
type RevolutionShapeParams struct {
	Meridian []Point3
	Angle    *float64 // 可为nil
	Max      *float64 // 可为nil
	Min      *float64 // 可为nil
}

func (p *RevolutionShapeParams) to_struct() C.revolution_shape_params_t {
	var c C.revolution_shape_params_t

	// 转换母线点数组
	if len(p.Meridian) > 0 {
		c.meridian = (*C.pnt3d_t)(C.malloc(C.size_t(len(p.Meridian)) * C.sizeof_pnt3d_t))
		meridianSlice := (*[1 << 30]C.pnt3d_t)(unsafe.Pointer(c.meridian))[:len(p.Meridian):len(p.Meridian)]
		for i, pt := range p.Meridian {
			meridianSlice[i] = pt.val // 直接赋值
		}
		c.meridian_count = C.int(len(p.Meridian))
	}

	// 转换可选参数
	if p.Angle != nil {
		c.angle = (*C.double)(unsafe.Pointer(p.Angle))
	}
	if p.Max != nil {
		c.max = (*C.double)(unsafe.Pointer(p.Max))
	}
	if p.Min != nil {
		c.min = (*C.double)(unsafe.Pointer(p.Min))
	}

	return c
}

func CreateRevolutionShape(params RevolutionShapeParams) *Shape {
	cParams := params.to_struct()
	defer func() {
		if cParams.meridian != nil {
			C.free(unsafe.Pointer(cParams.meridian))
		}
	}()

	shp := C.create_revolution_shape(cParams)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateRevolutionShapeWithPlace(params RevolutionShapeParams, position Point3, direction Dir3, xDir Dir3) *Shape {
	cParams := params.to_struct()
	defer func() {
		if cParams.meridian != nil {
			C.free(unsafe.Pointer(cParams.meridian))
		}
	}()

	shp := C.create_revolution_shape_with_place(cParams, position.val, direction.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

// 楔形面限制
type WedgeFaceLimit struct {
	Values [4]float64
}

// 楔形体参数
type WedgeShapeParams struct {
	Edge  Point3          // 边缘点
	Limit *WedgeFaceLimit // 面限制(可为nil)
	Ltx   *float64        // 参数(可为nil)
}

func (p *WedgeShapeParams) to_struct() C.wedge_shape_params_t {
	var c C.wedge_shape_params_t
	c.edge = p.Edge.val

	// 转换面限制参数(如果存在)
	if p.Limit != nil {
		var limit C.wedge_face_limit_t
		for i := 0; i < 4; i++ {
			limit.values[i] = C.double(p.Limit.Values[i])
		}
		c.limit = &limit
	}

	// 转换ltx参数(如果存在)
	if p.Ltx != nil {
		c.ltx = (*C.double)(unsafe.Pointer(p.Ltx))
	}

	return c
}

func CreateWedgeShape(params WedgeShapeParams) *Shape {
	cParams := params.to_struct()
	shp := C.create_wedge_shape(cParams)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateWedgeShapeWithPlace(params WedgeShapeParams, position Point3, direction Dir3, xDir Dir3) *Shape {
	cParams := params.to_struct()
	shp := C.create_wedge_shape_with_place(cParams, position.val, direction.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

// 管道参数
type PipeShapeParams struct {
	Wire    [2]Point3    // 管道路径的两个端点
	Profile ShapeProfile // 管道剖面
	UpDir   *Dir3
}

func (p *PipeShapeParams) to_struct() C.pipe_shape_params_t {
	var c C.pipe_shape_params_t

	// 转换路径端点
	c.wire[0] = p.Wire[0].val
	c.wire[1] = p.Wire[1].val

	// 转换剖面数据
	switch p.Profile.Type {
	case ProfileTypeTriangle:
		tri := p.Profile.Data.Triangle
		c.profile.type_ = C.PROFILE_TYPE_TRIANGLE
		c.profile.triangle.p1 = tri.P1.val
		c.profile.triangle.p2 = tri.P2.val
		c.profile.triangle.p3 = tri.P3.val
	case ProfileTypeRectangle:
		rect := p.Profile.Data.Rectangle
		c.profile.type_ = C.PROFILE_TYPE_RECTANGLE
		c.profile.rectangle.p1 = rect.P1.val
		c.profile.rectangle.p2 = rect.P2.val
	case ProfileTypeCirc:
		circ := p.Profile.Data.Circ
		c.profile.type_ = C.PROFILE_TYPE_CIRC
		c.profile.circ.center = circ.Center.val
		c.profile.circ.norm = circ.Norm.val
		c.profile.circ.radius = C.double(circ.Radius)
	case ProfileTypeElips:
		elips := p.Profile.Data.Elips
		c.profile.type_ = C.PROFILE_TYPE_ELIPS
		c.profile.elips.s1 = elips.S1.val
		c.profile.elips.s2 = elips.S2.val
		c.profile.elips.center = elips.Center.val
	case ProfileTypePolygon:
		poly := p.Profile.Data.Polygon
		c.profile.type_ = C.PROFILE_TYPE_POLYGON

		// 转换外边缘
		edges := make([]C.pnt3d_t, len(poly.Edges))
		for i, pt := range poly.Edges {
			edges[i] = pt.val
		}
		c.profile.polygon.edges = &edges[0]
		c.profile.polygon.edgeCount = C.int(len(poly.Edges))

		// 转换内边缘
		if len(poly.InnerEdges) > 0 {
			innerCounts := make([]C.int, len(poly.InnerEdges))
			innerPtrs := make([]*C.pnt3d_t, len(poly.InnerEdges))
			innerArrays := make([][]C.pnt3d_t, len(poly.InnerEdges))

			for i, inner := range poly.InnerEdges {
				innerCounts[i] = C.int(len(inner))
				innerArrays[i] = make([]C.pnt3d_t, len(inner))
				for j, pt := range inner {
					innerArrays[i][j] = pt.val
				}
				innerPtrs[i] = &innerArrays[i][0]
			}

			c.profile.polygon.inners = &innerPtrs[0]
			c.profile.polygon.innerCounts = &innerCounts[0]
			c.profile.polygon.innerArrayCount = C.int(len(poly.InnerEdges))
		}
	}

	if p.UpDir != nil {
		c.up_dir = &p.UpDir.val
	} else {
		c.up_dir = nil
	}

	return c
}

func CreatePipeShape(params PipeShapeParams) *Shape {
	cParams := params.to_struct()
	shp := C.create_pipe_shape(cParams)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreatePipeShapeWithPlace(params PipeShapeParams, position Point3, direction Dir3, xDir Dir3) *Shape {
	cParams := params.to_struct()
	shp := C.create_pipe_shape_with_place(cParams, position.val, direction.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type StepShapeParams struct {
	Name string
	Step []byte
}

func (p *StepShapeParams) toStruct() C.step_shape_params_t {
	var c C.step_shape_params_t
	c.name = C.CString(p.Name)
	c.step = C.CString(string(p.Step))
	return c
}

func freeStepParams(c C.step_shape_params_t) {
	C.free(unsafe.Pointer(c.name))
	C.free(unsafe.Pointer(c.step))
}

func CreateStepShape(params StepShapeParams) *Shape {
	cParams := params.toStruct()
	defer freeStepParams(cParams)

	shp := C.create_step_shape(cParams)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateStepShapeWithPlace(params StepShapeParams, position Point3, direction Dir3, xDir Dir3) *Shape {
	cParams := params.toStruct()
	defer freeStepParams(cParams)

	shp := C.create_step_shape_with_place(cParams, position.val, direction.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

type BoreholeSample struct {
	Name      string
	DepthFrom float32
	DepthTo   float32
}

type BoreholeParams struct {
	Samples  []BoreholeSample
	Diameter float32
	UpDir    *Dir3
}

func (p *BoreholeSample) to_struct() C.borehole_sample_t {
	var c C.borehole_sample_t
	c.name = C.CString(p.Name)
	c.depth_from = C.double(p.DepthFrom)
	c.depth_to = C.double(p.DepthTo)
	return c
}

func (p *BoreholeParams) to_struct() C.borehole_params_t {
	var c C.borehole_params_t
	c.sample_count = C.int(len(p.Samples))
	c.diameter = C.double(p.Diameter)

	if len(p.Samples) > 0 {
		c.samples = (*C.borehole_sample_t)(C.malloc(C.size_t(len(p.Samples)) * C.sizeof_borehole_sample_t))
		for i, sample := range p.Samples {
			csample := sample.to_struct()
			*(*C.borehole_sample_t)(unsafe.Pointer(uintptr(unsafe.Pointer(c.samples)) + uintptr(i)*C.sizeof_borehole_sample_t)) = csample
		}
	}

	if p.UpDir != nil {
		c.up_dir = &p.UpDir.val
	} else {
		c.up_dir = nil
	}
	return c
}

func freeBoreholeParams(c C.borehole_params_t) {
	if c.samples != nil {
		for i := 0; i < int(c.sample_count); i++ {
			sample := (*C.borehole_sample_t)(unsafe.Pointer(uintptr(unsafe.Pointer(c.samples)) + uintptr(i)*C.sizeof_borehole_sample_t))
			C.free(unsafe.Pointer(sample.name))
		}
		C.free(unsafe.Pointer(c.samples))
	}
}

func CreateBorehole(params BoreholeParams) (map[string]*Shape, error) {
	cParams := params.to_struct()
	defer freeBoreholeParams(cParams)

	var outCount C.int
	cShapes := C.create_borehole(cParams, &outCount)
	defer C.free_borehole_results(cShapes, outCount)

	if cShapes == nil || outCount == 0 {
		return nil, errors.New("failed to create borehole")
	}

	shapes := make(map[string]*Shape)
	for i := 0; i < int(outCount); i++ {
		cShape := *(**C.topo_shape_t)(unsafe.Pointer(uintptr(unsafe.Pointer(cShapes)) + uintptr(i)*unsafe.Sizeof(cShapes)))
		if cShape != nil {
			name := params.Samples[i].Name
			shapes[name] = &Shape{
				inner: &innerShape{val: cShape},
			}
			runtime.SetFinalizer(shapes[name].inner, (*innerShape).free)
		}
	}

	return shapes, nil
}

type WaterTunnelParams struct {
	Style                int            // 截面样式
	Width                float32        // 内净宽/内径 W (mm)
	Height               float32        // 内净高 H (mm)
	TopThickness         float32        // 顶板厚 H1 (mm)
	BottomThickness      float32        // 底板厚 H2 (mm)
	OuterWallThickness   float32        // 外壁厚 T (mm)
	InnerWallThickness   float32        // 内壁厚 T1 (mm)
	ArcHeight            float32        // 拱高 H4 (mm)
	ArcRadius            float32        // 拱半径 R (mm)
	ArcAngle             float32        // 拱角 α (°)
	BottomPlatformHeight float32        // 底部平台高 H5 (mm)
	CushionExtension     float32        // 垫层滋出 W2 (mm)
	CushionThickness     float32        // 垫层厚 H3 (mm)
	Points               []ChannelPoint // 使用切片代替原始指针和计数
}

func (p *WaterTunnelParams) to_struct() C.water_tunnel_params_t {
	cParams := C.water_tunnel_params_t{
		style:                C.int(p.Style),
		width:                C.double(p.Width),
		height:               C.double(p.Height),
		topThickness:         C.double(p.TopThickness),
		bottomThickness:      C.double(p.BottomThickness),
		outerWallThickness:   C.double(p.OuterWallThickness),
		innerWallThickness:   C.double(p.InnerWallThickness),
		arcHeight:            C.double(p.ArcHeight),
		arcRadius:            C.double(p.ArcRadius),
		arcAngle:             C.double(p.ArcAngle),
		bottomPlatformHeight: C.double(p.BottomPlatformHeight),
		cushionExtension:     C.double(p.CushionExtension),
		cushionThickness:     C.double(p.CushionThickness),
		point_count:          C.int(len(p.Points)),
	}

	if len(p.Points) > 0 {
		cParams.points = (*C.channel_point_t)(C.malloc(C.size_t(len(p.Points)) * C.sizeof_channel_point_t))
		for i, point := range p.Points {
			cp := C.channel_point_t{
				position: point.Position.val,
				ctype:    C.int(point.Ctype),
			}
			*(*C.channel_point_t)(unsafe.Pointer(uintptr(unsafe.Pointer(cParams.points)) + uintptr(i)*C.sizeof_channel_point_t)) = cp
		}
	}
	return cParams
}

func CreateWaterTunnel(params WaterTunnelParams) *Shape {
	cParams := params.to_struct()
	defer func() {
		if cParams.points != nil {
			C.free(unsafe.Pointer(cParams.points))
		}
	}()
	shp := C.create_water_tunnel(cParams)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}
