package topo

/*
#include <stdlib.h>
#include "primitives_railway_c_api.h"
*/
import "C"
import (
	"math"
	"runtime"
)

// =========================================================================
// 1. Contact Wire (接触线)
// =========================================================================

type ContactWireParams struct {
	SectionalArea float64
	Diameter      float64
	RatedTension  float64
	GrooveDepth   float64
	GrooveWidth   float64
	BottomRadius  float64
	TopRadius     float64
}

func (p *ContactWireParams) to_struct() C.contact_wire_params_t {
	var c C.contact_wire_params_t
	c.sectionalArea = C.double(p.SectionalArea)
	c.diameter = C.double(p.Diameter)
	c.ratedTension = C.double(p.RatedTension)
	c.grooveDepth = C.double(p.GrooveDepth)
	c.grooveWidth = C.double(p.GrooveWidth)
	c.bottomRadius = C.double(p.BottomRadius)
	c.topRadius = C.double(p.TopRadius)
	return c
}

func CreateContactWire(params ContactWireParams, startPoint, endPoint Point3) *Shape {
	shp := C.create_contact_wire(params.to_struct(), startPoint.val, endPoint.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

// =========================================================================
// 2. Messenger Wire (承力索)
// =========================================================================

type MessengerWireParams struct {
	Diameter         float64
	RatedTension     float64
	StructuralHeight float64
}

func (p *MessengerWireParams) to_struct() C.messenger_wire_params_t {
	var c C.messenger_wire_params_t
	c.diameter = C.double(p.Diameter)
	c.ratedTension = C.double(p.RatedTension)
	c.structuralHeight = C.double(p.StructuralHeight)
	return c
}

func CreateMessengerWire(params MessengerWireParams, startPoint, endPoint Point3) *Shape {
	shp := C.create_messenger_wire(params.to_struct(), startPoint.val, endPoint.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

// =========================================================================
// 3. Cross Arm (横担)
// =========================================================================

type CrossArmParams struct {
	Type          int
	BeamLength    float64
	BeamHeight    float64
	BeamWidth     float64
	BeamThickness float64
	BeamSpacing  float64
	BraceLength   float64
	BraceDiameter float64
	MountHeight   float64
	BoltSpacing   float64
	BoltDiameter  float64
	BoltCount     int
}

func (p *CrossArmParams) to_struct() C.cross_arm_params_t {
	var c C.cross_arm_params_t
	c.ctype = C.int(p.Type)
	c.beamLength = C.double(p.BeamLength)
	c.beamHeight = C.double(p.BeamHeight)
	c.beamWidth = C.double(p.BeamWidth)
	c.beamThickness = C.double(p.BeamThickness)
	c.beamSpacing = C.double(p.BeamSpacing)
	c.braceLength = C.double(p.BraceLength)
	c.braceDiameter = C.double(p.BraceDiameter)
	c.mountHeight = C.double(p.MountHeight)
	c.boltSpacing = C.double(p.BoltSpacing)
	c.boltDiameter = C.double(p.BoltDiameter)
	c.boltCount = C.int(p.BoltCount)
	return c
}

func CreateCrossArm(params CrossArmParams) *Shape {
	shp := C.create_cross_arm(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateCrossArmWithPlace(params CrossArmParams, position Point3, normal, xDir Dir3) *Shape {
	shp := C.create_cross_arm_with_place(params.to_struct(), position.val, normal.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

// =========================================================================
// 4. Level Cantilever (平腕臂)
// =========================================================================

type LevelCantileverParams struct {
	Length        float64
	OuterDiameter float64
	WallThickness float64
	MountHeight   float64
	RiseAngle     float64
}

func (p *LevelCantileverParams) to_struct() C.level_cantilever_params_t {
	var c C.level_cantilever_params_t
	c.length = C.double(p.Length)
	c.outerDiameter = C.double(p.OuterDiameter)
	c.wallThickness = C.double(p.WallThickness)
	c.mountHeight = C.double(p.MountHeight)
	c.riseAngle = C.double(p.RiseAngle)
	return c
}

func CreateLevelCantilever(params LevelCantileverParams) *Shape {
	shp := C.create_level_cantilever(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateLevelCantileverWithPlace(params LevelCantileverParams, basePoint Point3, axisDir, upDir Dir3) *Shape {
	shp := C.create_level_cantilever_with_place(params.to_struct(), basePoint.val, axisDir.val, upDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

// =========================================================================
// 5. Slanted Cantilever (斜腕臂)
// =========================================================================

type SlantCantileverParams struct {
	Length        float64
	OuterDiameter float64
	WallThickness float64
	SlantAngle    float64
}

func (p *SlantCantileverParams) to_struct() C.slant_cantilever_params_t {
	var c C.slant_cantilever_params_t
	c.length = C.double(p.Length)
	c.outerDiameter = C.double(p.OuterDiameter)
	c.wallThickness = C.double(p.WallThickness)
	c.slantAngle = C.double(p.SlantAngle)
	return c
}

func CreateSlantCantilever(params SlantCantileverParams) *Shape {
	shp := C.create_slant_cantilever(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateSlantCantileverWithPlace(params SlantCantileverParams, basePoint Point3, axisDir, upDir Dir3) *Shape {
	shp := C.create_slant_cantilever_with_place(params.to_struct(), basePoint.val, axisDir.val, upDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

// =========================================================================
// 6. Curved Arm (弯臂)
// =========================================================================

type CurvedArmParams struct {
	Type            int
	VerticalLength  float64
	HorizontalLength float64
	BendRadius      float64
	BendAngle       float64
	OuterDiameter   float64
	WallThickness   float64
	FlangeThickness float64
	BoltSpacing     float64
	BoltDiameter    float64
}

func (p *CurvedArmParams) to_struct() C.curved_arm_params_t {
	var c C.curved_arm_params_t
	c.ctype = C.int(p.Type)
	c.verticalLength = C.double(p.VerticalLength)
	c.horizontalLength = C.double(p.HorizontalLength)
	c.bendRadius = C.double(p.BendRadius)
	c.bendAngle = C.double(p.BendAngle)
	c.outerDiameter = C.double(p.OuterDiameter)
	c.wallThickness = C.double(p.WallThickness)
	c.flangeThickness = C.double(p.FlangeThickness)
	c.boltSpacing = C.double(p.BoltSpacing)
	c.boltDiameter = C.double(p.BoltDiameter)
	return c
}

func CreateCurvedArm(params CurvedArmParams) *Shape {
	shp := C.create_curved_arm(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateCurvedArmWithPlace(params CurvedArmParams, position Point3, normal, xDir Dir3) *Shape {
	shp := C.create_curved_arm_with_place(params.to_struct(), position.val, normal.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

// =========================================================================
// 7. Rod Insulator (棒式绝缘子)
// =========================================================================

type RodInsulatorParams struct {
	Type              int
	Height            float64
	OuterDiameter     float64
	InnerDiameter     float64
	ShedDiameter      float64
	ShedSpacing       float64
	ShedCount         int
	EndFitting        int
	FlangeDiameter    float64
	FlangeBoltSpacing float64
	FlangeBoltDiameter float64
}

func (p *RodInsulatorParams) to_struct() C.rod_insulator_params_t {
	var c C.rod_insulator_params_t
	c.ctype = C.int(p.Type)
	c.height = C.double(p.Height)
	c.outerDiameter = C.double(p.OuterDiameter)
	c.innerDiameter = C.double(p.InnerDiameter)
	c.shedDiameter = C.double(p.ShedDiameter)
	c.shedSpacing = C.double(p.ShedSpacing)
	c.shedCount = C.int(p.ShedCount)
	c.endFitting = C.int(p.EndFitting)
	c.flangeDiameter = C.double(p.FlangeDiameter)
	c.flangeBoltSpacing = C.double(p.FlangeBoltSpacing)
	c.flangeBoltDiameter = C.double(p.FlangeBoltDiameter)
	return c
}

func CreateRodInsulator(params RodInsulatorParams) *Shape {
	shp := C.create_rod_insulator(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateRodInsulatorWithPlace(params RodInsulatorParams, basePoint Point3, axisDir Dir3) *Shape {
	shp := C.create_rod_insulator_with_place(params.to_struct(), basePoint.val, axisDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

// =========================================================================
// 8. Mast Bracket (支柱连接座)
// =========================================================================

type MastBracketParams struct {
	BoltSpacing          float64
	BoltDiameter         float64
	Height               float64
	Width                float64
	Thickness            float64
	InsulatorBoltSpacing  float64
	InsulatorBoltDiameter float64
	MountAngle           float64
}

func (p *MastBracketParams) to_struct() C.mast_bracket_params_t {
	var c C.mast_bracket_params_t
	c.boltSpacing = C.double(p.BoltSpacing)
	c.boltDiameter = C.double(p.BoltDiameter)
	c.height = C.double(p.Height)
	c.width = C.double(p.Width)
	c.thickness = C.double(p.Thickness)
	c.insulatorBoltSpacing = C.double(p.InsulatorBoltSpacing)
	c.insulatorBoltDiameter = C.double(p.InsulatorBoltDiameter)
	c.mountAngle = C.double(p.MountAngle)
	return c
}

func CreateMastBracket(params MastBracketParams) *Shape {
	shp := C.create_mast_bracket(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateMastBracketWithPlace(params MastBracketParams, position Point3, normal, upDir Dir3) *Shape {
	shp := C.create_mast_bracket_with_place(params.to_struct(), position.val, normal.val, upDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

// =========================================================================
// 9. Registration Arm (定位器)
// =========================================================================

type RegistrationArmParams struct {
	Type          int
	Length        float64
	TubeWidth     float64
	TubeHeight    float64
	WallThickness float64
	Angle         float64
	IsReverse     bool
}

func (p *RegistrationArmParams) to_struct() C.registration_arm_params_t {
	var c C.registration_arm_params_t
	c.ctype = C.int(p.Type)
	c.length = C.double(p.Length)
	c.tubeWidth = C.double(p.TubeWidth)
	c.tubeHeight = C.double(p.TubeHeight)
	c.wallThickness = C.double(p.WallThickness)
	c.angle = C.double(p.Angle)
	c.isReverse = C.bool(p.IsReverse)
	return c
}

func CreateRegistrationArm(params RegistrationArmParams) *Shape {
	shp := C.create_registration_arm(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateRegistrationArmWithPlace(params RegistrationArmParams, basePoint Point3, axisDir, upDir Dir3) *Shape {
	shp := C.create_registration_arm_with_place(params.to_struct(), basePoint.val, axisDir.val, upDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

// =========================================================================
// 9b. Registration Arm Bracket (定位器底座 L型金具)
// =========================================================================

type RegArmBracketParams struct {
	TubeDiameter      float64
	BandWidth         float64
	BandThickness     float64
	BracketHeight     float64
	BracketThickness  float64
	BracketWidth      float64
	MountHoleDiameter float64
}

func CreateRegArmBracket(params RegArmBracketParams) *Shape {
	var c C.reg_arm_bracket_params_t
	c.tubeDiameter = C.double(params.TubeDiameter)
	c.bandWidth = C.double(params.BandWidth)
	c.bandThickness = C.double(params.BandThickness)
	c.bracketHeight = C.double(params.BracketHeight)
	c.bracketThickness = C.double(params.BracketThickness)
	c.bracketWidth = C.double(params.BracketWidth)
	c.mountHoleDiameter = C.double(params.MountHoleDiameter)
	s := &Shape{inner: &innerShape{val: C.create_reg_arm_bracket(c)}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

// =========================================================================
// 10. Guy Wire (下锚拉线)
// =========================================================================

type GuyWireParams struct {
	Length            float64
	Diameter          float64
	Angle             float64
	RatedTension      float64
	HasInsulator      bool
	AnchorRodDiameter float64
	AnchorRodLength   float64
	AnchorPlateLength float64
	AnchorPlateWidth  float64
}

func (p *GuyWireParams) to_struct() C.guy_wire_params_t {
	var c C.guy_wire_params_t
	c.length = C.double(p.Length)
	c.diameter = C.double(p.Diameter)
	c.angle = C.double(p.Angle)
	c.ratedTension = C.double(p.RatedTension)
	c.hasInsulator = C.bool(p.HasInsulator)
	c.anchorRodDiameter = C.double(p.AnchorRodDiameter)
	c.anchorRodLength = C.double(p.AnchorRodLength)
	c.anchorPlateLength = C.double(p.AnchorPlateLength)
	c.anchorPlateWidth = C.double(p.AnchorPlateWidth)
	return c
}

func CreateGuyWire(params GuyWireParams) *Shape {
	shp := C.create_guy_wire(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateGuyWireWithPlace(params GuyWireParams, anchorPoint, mastPoint Point3, upDir Dir3) *Shape {
	shp := C.create_guy_wire_with_place(params.to_struct(), anchorPoint.val, mastPoint.val, upDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

// =========================================================================
// 11. Steel Mast (钢支柱)
// =========================================================================

type SteelMastParams struct {
	Type            int
	Height          float64
	TopWidth        float64
	BottomWidth     float64
	WallThickness   float64
	FlangeThickness float64
	FlangeWidth     float64
	AnchorSpacing   float64
	AnchorDiameter  float64
	SegmentCount    int
}

func (p *SteelMastParams) to_struct() C.steel_mast_params_t {
	var c C.steel_mast_params_t
	c.ctype = C.int(p.Type)
	c.height = C.double(p.Height)
	c.topWidth = C.double(p.TopWidth)
	c.bottomWidth = C.double(p.BottomWidth)
	c.wallThickness = C.double(p.WallThickness)
	c.flangeThickness = C.double(p.FlangeThickness)
	c.flangeWidth = C.double(p.FlangeWidth)
	c.anchorSpacing = C.double(p.AnchorSpacing)
	c.anchorDiameter = C.double(p.AnchorDiameter)
	c.segmentCount = C.int(p.SegmentCount)
	return c
}

func CreateSteelMast(params SteelMastParams) *Shape {
	shp := C.create_steel_mast(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateSteelMastWithPlace(params SteelMastParams, baseCenter Point3, axisDir Dir3) *Shape {
	shp := C.create_steel_mast_with_place(params.to_struct(), baseCenter.val, axisDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

// =========================================================================
// 12. Concrete Mast (混凝土支柱)
// =========================================================================

type ConcreteMastParams struct {
	SectionType     int
	Height          float64
	TopWidth        float64
	BottomWidth     float64
	WallThickness   float64
	HoleDiameter    float64
	HoleSpacingV    float64
	HoleSpacingH    float64
	FirstHoleOffset float64
	HoleRowCount    int
	HolesPerRow     int
}

func (p *ConcreteMastParams) to_struct() C.concrete_mast_params_t {
	var c C.concrete_mast_params_t
	c.sectionType = C.int(p.SectionType)
	c.height = C.double(p.Height)
	c.topWidth = C.double(p.TopWidth)
	c.bottomWidth = C.double(p.BottomWidth)
	c.wallThickness = C.double(p.WallThickness)
	c.holeDiameter = C.double(p.HoleDiameter)
	c.holeSpacingV = C.double(p.HoleSpacingV)
	c.holeSpacingH = C.double(p.HoleSpacingH)
	c.firstHoleOffset = C.double(p.FirstHoleOffset)
	c.holeRowCount = C.int(p.HoleRowCount)
	c.holesPerRow = C.int(p.HolesPerRow)
	return c
}

func CreateConcreteMast(params ConcreteMastParams) *Shape {
	shp := C.create_concrete_mast(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateConcreteMastWithPlace(params ConcreteMastParams, baseCenter Point3, axisDir Dir3) *Shape {
	shp := C.create_concrete_mast_with_place(params.to_struct(), baseCenter.val, axisDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

// =========================================================================
// 13. OCS Foundation (支柱基础)
// =========================================================================

type OcsFoundationParams struct {
	Type            int
	Height          float64
	Width           float64
	Length          float64
	FlangeThickness float64
	AnchorCount     int
	AnchorDiameter  float64
	AnchorLength    float64
	AnchorSpacing   float64
}

func (p *OcsFoundationParams) to_struct() C.ocs_foundation_params_t {
	var c C.ocs_foundation_params_t
	c.ctype = C.int(p.Type)
	c.height = C.double(p.Height)
	c.width = C.double(p.Width)
	c.length = C.double(p.Length)
	c.flangeThickness = C.double(p.FlangeThickness)
	c.anchorCount = C.int(p.AnchorCount)
	c.anchorDiameter = C.double(p.AnchorDiameter)
	c.anchorLength = C.double(p.AnchorLength)
	c.anchorSpacing = C.double(p.AnchorSpacing)
	return c
}

func CreateOcsFoundation(params OcsFoundationParams) *Shape {
	shp := C.create_ocs_foundation(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateOcsFoundationWithPlace(params OcsFoundationParams, position Point3, normal, xDir Dir3) *Shape {
	shp := C.create_ocs_foundation_with_place(params.to_struct(), position.val, normal.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

// =========================================================================
// 14. Dropper (吊弦)
// =========================================================================

type DropperParams struct {
	Length         float64
	WireDiameter   float64
	ClampLength    float64
	ClampWidth     float64
	ClampThickness float64
	Conductive     bool
}

func (p *DropperParams) to_struct() C.dropper_params_t {
	var c C.dropper_params_t
	c.length = C.double(p.Length)
	c.wireDiameter = C.double(p.WireDiameter)
	c.clampLength = C.double(p.ClampLength)
	c.clampWidth = C.double(p.ClampWidth)
	c.clampThickness = C.double(p.ClampThickness)
	c.conductive = C.bool(p.Conductive)
	return c
}

func CreateDropper(params DropperParams) *Shape {
	shp := C.create_dropper(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateDropperWithPlace(params DropperParams, topPoint Point3, direction Dir3) *Shape {
	shp := C.create_dropper_with_place(params.to_struct(), topPoint.val, direction.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

// =========================================================================
// 15. Cantilever Base (腕臂底座)
// =========================================================================

type CantileverBaseParams struct {
	Length      float64
	Width       float64
	Height      float64
	BoltSpacing float64
	BoltDiameter float64
	BoltCount   int
}

func (p *CantileverBaseParams) to_struct() C.cantilever_base_params_t {
	var c C.cantilever_base_params_t
	c.length = C.double(p.Length)
	c.width = C.double(p.Width)
	c.height = C.double(p.Height)
	c.boltSpacing = C.double(p.BoltSpacing)
	c.boltDiameter = C.double(p.BoltDiameter)
	c.boltCount = C.int(p.BoltCount)
	return c
}

func CreateCantileverBase(params CantileverBaseParams) *Shape {
	shp := C.create_cantilever_base(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateCantileverBaseWithPlace(params CantileverBaseParams, position Point3, normal, upDir Dir3) *Shape {
	shp := C.create_cantilever_base_with_place(params.to_struct(), position.val, normal.val, upDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

// =========================================================================
// 16. Messenger Wire Saddle (承力索座)
// =========================================================================

type MWSaddleParams struct {
	Length       float64
	Width        float64
	Height       float64
	GrooveRadius float64
	BoltDiameter float64
}

func (p *MWSaddleParams) to_struct() C.mw_saddle_params_t {
	var c C.mw_saddle_params_t
	c.length = C.double(p.Length)
	c.width = C.double(p.Width)
	c.height = C.double(p.Height)
	c.grooveRadius = C.double(p.GrooveRadius)
	c.boltDiameter = C.double(p.BoltDiameter)
	return c
}

func CreateMWSaddle(params MWSaddleParams) *Shape {
	shp := C.create_mw_saddle(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateMWSaddleWithPlace(params MWSaddleParams, position Point3, normal, xDir Dir3) *Shape {
	shp := C.create_mw_saddle_with_place(params.to_struct(), position.val, normal.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

// =========================================================================
// 17. Balance Weight (坠砣)
// =========================================================================

type BalanceWeightParams struct {
	Width             float64
	Thickness         float64
	Height            float64
	CenterHoleDiameter float64
}

func (p *BalanceWeightParams) to_struct() C.balance_weight_params_t {
	var c C.balance_weight_params_t
	c.width = C.double(p.Width)
	c.thickness = C.double(p.Thickness)
	c.height = C.double(p.Height)
	c.centerHoleDiameter = C.double(p.CenterHoleDiameter)
	return c
}

func CreateBalanceWeight(params BalanceWeightParams) *Shape {
	shp := C.create_balance_weight(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateBalanceWeightWithPlace(params BalanceWeightParams, position Point3, normal, xDir Dir3) *Shape {
	shp := C.create_balance_weight_with_place(params.to_struct(), position.val, normal.val, xDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

// =========================================================================
// 18. Weight Rod (坠砣杆)
// =========================================================================

type WeightRodParams struct {
	RodDiameter   float64
	RodLength     float64
	TopHoleDiameter float64
}

func (p *WeightRodParams) to_struct() C.weight_rod_params_t {
	var c C.weight_rod_params_t
	c.rodDiameter = C.double(p.RodDiameter)
	c.rodLength = C.double(p.RodLength)
	c.topHoleDiameter = C.double(p.TopHoleDiameter)
	return c
}

func CreateWeightRod(params WeightRodParams) *Shape {
	shp := C.create_weight_rod(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateWeightRodWithPlace(params WeightRodParams, position Point3, axisDir Dir3) *Shape {
	shp := C.create_weight_rod_with_place(params.to_struct(), position.val, axisDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

// =========================================================================
// 19. Anchor Fitting (下锚金具)
// =========================================================================

type AnchorFittingParams struct {
	Type     int
	Length   float64
	Diameter float64
}

func (p *AnchorFittingParams) to_struct() C.anchor_fitting_params_t {
	var c C.anchor_fitting_params_t
	c.ctype = C.int(p.Type)
	c.length = C.double(p.Length)
	c.diameter = C.double(p.Diameter)
	return c
}

func CreateAnchorFitting(params AnchorFittingParams) *Shape {
	shp := C.create_anchor_fitting(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateAnchorFittingWithPlace(params AnchorFittingParams, position Point3, direction, upDir Dir3) *Shape {
	shp := C.create_anchor_fitting_with_place(params.to_struct(), position.val, direction.val, upDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

// =========================================================================
// 20. Crossing (线岔)
// =========================================================================

type CrossingParams struct {
	LimitPipeLength float64
	PipeDiameter   float64
	WireDiameter   float64
	HeightDiff     float64
}

func (p *CrossingParams) to_struct() C.crossing_params_t {
	var c C.crossing_params_t
	c.limitPipeLength = C.double(p.LimitPipeLength)
	c.pipeDiameter = C.double(p.PipeDiameter)
	c.wireDiameter = C.double(p.WireDiameter)
	c.heightDiff = C.double(p.HeightDiff)
	return c
}

func CreateCrossing(params CrossingParams) *Shape {
	shp := C.create_crossing(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateCrossingWithPlace(params CrossingParams, crossPoint Point3, mainDir, branchDir Dir3) *Shape {
	shp := C.create_crossing_with_place(params.to_struct(), crossPoint.val, mainDir.val, branchDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

// =========================================================================
// 21. Head Span (软横跨)
// =========================================================================

type HeadSpanParams struct {
	Span                float64
	HangPointCount      int
	HangPointSpacing    float64
	CrossCatenaryDiameter float64
	CrossCatenarySag    float64
	UpperRopeDiameter   float64
	LowerRopeDiameter   float64
	InsulatorLength     float64
}

func (p *HeadSpanParams) to_struct() C.head_span_params_t {
	var c C.head_span_params_t
	c.span = C.double(p.Span)
	c.hangPointCount = C.int(p.HangPointCount)
	c.hangPointSpacing = C.double(p.HangPointSpacing)
	c.crossCatenaryDiameter = C.double(p.CrossCatenaryDiameter)
	c.crossCatenarySag = C.double(p.CrossCatenarySag)
	c.upperRopeDiameter = C.double(p.UpperRopeDiameter)
	c.lowerRopeDiameter = C.double(p.LowerRopeDiameter)
	c.insulatorLength = C.double(p.InsulatorLength)
	return c
}

func CreateHeadSpan(params HeadSpanParams) *Shape {
	shp := C.create_head_span(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateHeadSpanWithPlace(params HeadSpanParams, leftMast, rightMast Point3, upDir Dir3) *Shape {
	shp := C.create_head_span_with_place(params.to_struct(), leftMast.val, rightMast.val, upDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

// =========================================================================
// 22. Transverse Span (硬横跨)
// =========================================================================

type TransverseSpanParams struct {
	Span          float64
	BeamType      int
	BeamHeight    float64
	BeamWidth     float64
	BeamThickness float64
	MastHeight    float64
	MastWidth     float64
}

func (p *TransverseSpanParams) to_struct() C.transverse_span_params_t {
	var c C.transverse_span_params_t
	c.span = C.double(p.Span)
	c.beamType = C.int(p.BeamType)
	c.beamHeight = C.double(p.BeamHeight)
	c.beamWidth = C.double(p.BeamWidth)
	c.beamThickness = C.double(p.BeamThickness)
	c.mastHeight = C.double(p.MastHeight)
	c.mastWidth = C.double(p.MastWidth)
	return c
}

func CreateTransverseSpan(params TransverseSpanParams) *Shape {
	shp := C.create_transverse_span(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateTransverseSpanWithPlace(params TransverseSpanParams, position Point3, direction, upDir Dir3) *Shape {
	shp := C.create_transverse_span_with_place(params.to_struct(), position.val, direction.val, upDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
 	return s
}

// =========================================================================
// 22b. Hanger Post (硬横跨吊柱)
// =========================================================================

type HangerPostParams struct {
	SectionType        int
	Length             float64
	SectionSize        float64
	WallThickness      float64
	TopFlangeSize      float64
	TopFlangeThick     float64
	BottomFlangeSize   float64
	BottomFlangeThick  float64
	BoltDiameter       float64
	BoltSpacing        float64
}

func (p *HangerPostParams) to_struct() C.hanger_post_params_t {
	var c C.hanger_post_params_t
	c.sectionType = C.int(p.SectionType)
	c.length = C.double(p.Length)
	c.sectionSize = C.double(p.SectionSize)
	c.wallThickness = C.double(p.WallThickness)
	c.topFlangeSize = C.double(p.TopFlangeSize)
	c.topFlangeThick = C.double(p.TopFlangeThick)
	c.bottomFlangeSize = C.double(p.BottomFlangeSize)
	c.bottomFlangeThick = C.double(p.BottomFlangeThick)
	c.boltDiameter = C.double(p.BoltDiameter)
	c.boltSpacing = C.double(p.BoltSpacing)
	return c
}

func CreateHangerPost(params HangerPostParams) *Shape {
	shp := C.create_hanger_post(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateHangerPostWithPlace(params HangerPostParams, position Point3, direction Dir3) *Shape {
	shp := C.create_hanger_post_with_place(params.to_struct(), position.val, direction.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

// =========================================================================
// 22c. Portal Frame (梁顶门型架)
// =========================================================================

type PortalFrameParams struct {
	FrameHeight      float64
	FrameWidth       float64
	PostDiameter     float64
	PostWallThick    float64
	BeamDiameter     float64
	BeamWallThick    float64
	BeamLength       float64
	BasePlateLength  float64
	BasePlateWidth   float64
	BasePlateThick   float64
	HangPointCount   int
	HangPointSpacing float64
	BoltSpacing      float64
	BoltDiameter     float64
}

func (p *PortalFrameParams) to_struct() C.portal_frame_params_t {
	var c C.portal_frame_params_t
	c.frameHeight = C.double(p.FrameHeight)
	c.frameWidth = C.double(p.FrameWidth)
	c.postDiameter = C.double(p.PostDiameter)
	c.postWallThick = C.double(p.PostWallThick)
	c.beamDiameter = C.double(p.BeamDiameter)
	c.beamWallThick = C.double(p.BeamWallThick)
	c.beamLength = C.double(p.BeamLength)
	c.basePlateLength = C.double(p.BasePlateLength)
	c.basePlateWidth = C.double(p.BasePlateWidth)
	c.basePlateThick = C.double(p.BasePlateThick)
	c.hangPointCount = C.int(p.HangPointCount)
	c.hangPointSpacing = C.double(p.HangPointSpacing)
	c.boltSpacing = C.double(p.BoltSpacing)
	c.boltDiameter = C.double(p.BoltDiameter)
	return c
}

func CreatePortalFrame(params PortalFrameParams) *Shape {
	shp := C.create_portal_frame(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreatePortalFrameWithPlace(params PortalFrameParams, position Point3, direction, upDir Dir3) *Shape {
	shp := C.create_portal_frame_with_place(params.to_struct(), position.val, direction.val, upDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

// =========================================================================
// 22e. Suspension Hard Span (悬索式硬横跨)
// =========================================================================

type SuspensionHardSpanParams struct {
	Span                float64
	MastHeight          float64
	MastWidth           float64
	CableDiameter       float64
	CableSag            float64
	DropperCableDiameter float64
	DropperCount        int
	DropperSpacing      float64
	InsulatorLength     float64
	InsulatorDiameter   float64
}

func (p *SuspensionHardSpanParams) to_struct() C.suspension_hard_span_params_t {
	var c C.suspension_hard_span_params_t
	c.span = C.double(p.Span)
	c.mastHeight = C.double(p.MastHeight)
	c.mastWidth = C.double(p.MastWidth)
	c.cableDiameter = C.double(p.CableDiameter)
	c.cableSag = C.double(p.CableSag)
	c.dropperCableDiameter = C.double(p.DropperCableDiameter)
	c.dropperCount = C.int(p.DropperCount)
	c.dropperSpacing = C.double(p.DropperSpacing)
	c.insulatorLength = C.double(p.InsulatorLength)
	c.insulatorDiameter = C.double(p.InsulatorDiameter)
	return c
}

func CreateSuspensionHardSpan(params SuspensionHardSpanParams) *Shape {
	shp := C.create_suspension_hard_span(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateSuspensionHardSpanWithPlace(params SuspensionHardSpanParams, position Point3, direction, upDir Dir3) *Shape {
	shp := C.create_suspension_hard_span_with_place(params.to_struct(), position.val, direction.val, upDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

// =========================================================================
// 22f. Positioning Cable (定位索)
// =========================================================================

type PositioningCableParams struct {
	Diameter    float64
	TopPoint    Point3
	BottomPoint Point3
	Adjustable  bool
}

func (p *PositioningCableParams) to_struct() C.positioning_cable_params_t {
	var c C.positioning_cable_params_t
	c.diameter = C.double(p.Diameter)
	c.topPoint = p.TopPoint.val
	c.bottomPoint = p.BottomPoint.val
	c.adjustable = C.bool(p.Adjustable)
	return c
}

func CreatePositioningCable(params PositioningCableParams) *Shape {
	shp := C.create_positioning_cable(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

// =========================================================================
// 23. Auxiliary Bracket (附加导线安装支架)
// =========================================================================

type AuxBracketParams struct {
	Type          int
	MountHeight   float64
	OverhangLength float64
	BracketLength float64
	BracketWidth  float64
	BoltSpacing   float64
	BoltDiameter  float64
}

func (p *AuxBracketParams) to_struct() C.aux_bracket_params_t {
	var c C.aux_bracket_params_t
	c.ctype = C.int(p.Type)
	c.mountHeight = C.double(p.MountHeight)
	c.overhangLength = C.double(p.OverhangLength)
	c.bracketLength = C.double(p.BracketLength)
	c.bracketWidth = C.double(p.BracketWidth)
	c.boltSpacing = C.double(p.BoltSpacing)
	c.boltDiameter = C.double(p.BoltDiameter)
	return c
}

func CreateAuxBracket(params AuxBracketParams) *Shape {
	shp := C.create_aux_bracket(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateAuxBracketWithPlace(params AuxBracketParams, position Point3, normal, upDir Dir3) *Shape {
	shp := C.create_aux_bracket_with_place(params.to_struct(), position.val, normal.val, upDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

// =========================================================================
// 24. Rail (钢轨)
// =========================================================================

type RailParams struct {
	RailHeight    float64
	HeadWidth     float64
	BaseWidth     float64
	WebThickness  float64
	HeadHeight    float64
	BaseHeight    float64
	HeadRadius    float64
	StandardLength float64
}

func (p *RailParams) to_struct() C.rail_params_t {
	var c C.rail_params_t
	c.railHeight = C.double(p.RailHeight)
	c.headWidth = C.double(p.HeadWidth)
	c.baseWidth = C.double(p.BaseWidth)
	c.webThickness = C.double(p.WebThickness)
	c.headHeight = C.double(p.HeadHeight)
	c.baseHeight = C.double(p.BaseHeight)
	c.headRadius = C.double(p.HeadRadius)
	c.standardLength = C.double(p.StandardLength)
	return c
}

func CreateRail(params RailParams) *Shape {
	shp := C.create_rail(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateRailWithPlace(params RailParams, startPoint, endPoint Point3) *Shape {
	shp := C.create_rail_with_place(params.to_struct(), startPoint.val, endPoint.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

// =========================================================================
// 25. Sleeper (轨枕)
// =========================================================================

type SleeperParams struct {
	ShapeType   int
	Length      float64
	Width       float64
	Height      float64
	Gauge       float64
	GrooveDepth float64
	Spacing     float64
}

func (p *SleeperParams) to_struct() C.sleeper_params_t {
	var c C.sleeper_params_t
	c.shapeType = C.int(p.ShapeType)
	c.length = C.double(p.Length)
	c.width = C.double(p.Width)
	c.height = C.double(p.Height)
	c.gauge = C.double(p.Gauge)
	c.grooveDepth = C.double(p.GrooveDepth)
	c.spacing = C.double(p.Spacing)
	return c
}

func CreateSleeper(params SleeperParams) *Shape {
	shp := C.create_sleeper(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateSleeperWithPlace(params SleeperParams, position Point3, direction, upDir Dir3) *Shape {
	shp := C.create_sleeper_with_place(params.to_struct(), position.val, direction.val, upDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

// =========================================================================
// 26. Ballast (道床)
// =========================================================================

// BallastParams — 梯形道床，沿中心线路径扫掠生成

func CreateBallastAlongPath(centerline []Point3, topWidth, thickness, sideSlope float64) *Shape {
	pts := make([]C.pnt3d_t, len(centerline))
	for i, p := range centerline { pts[i] = p.val }
	var cp C.ballast_params_t
	cp.topWidth = C.double(topWidth)
	cp.thickness = C.double(thickness)
	cp.sideSlope = C.double(sideSlope)
	cp.centerline = &pts[0]
	cp.pointCount = C.int(len(pts))
	s := &Shape{inner: &innerShape{val: C.create_ballast(cp)}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

// =========================================================================
// 27. Track Slab (轨道板)
// =========================================================================

type TrackSlabParams struct {
	Length                float64
	Width                 float64
	Thickness             float64
	RailSeatCount         int
	RailSeatSpacing       float64
	CementAsphaltThickness float64
}

func (p *TrackSlabParams) to_struct() C.track_slab_params_t {
	var c C.track_slab_params_t
	c.length = C.double(p.Length)
	c.width = C.double(p.Width)
	c.thickness = C.double(p.Thickness)
	c.railSeatCount = C.int(p.RailSeatCount)
	c.railSeatSpacing = C.double(p.RailSeatSpacing)
	c.cementAsphaltThickness = C.double(p.CementAsphaltThickness)
	return c
}

func CreateTrackSlab(params TrackSlabParams) *Shape {
	shp := C.create_track_slab(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateTrackSlabWithPlace(params TrackSlabParams, position Point3, direction, upDir Dir3) *Shape {
	shp := C.create_track_slab_with_place(params.to_struct(), position.val, direction.val, upDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

// =========================================================================
// 28. Fastener (扣件)
// =========================================================================

type FastenerParams struct {
	Spacing      float64
	Gauge        float64
	PadThickness float64
	PadLength    float64
	PadWidth     float64
}

func (p *FastenerParams) to_struct() C.fastener_params_t {
	var c C.fastener_params_t
	c.spacing = C.double(p.Spacing)
	c.gauge = C.double(p.Gauge)
	c.padThickness = C.double(p.PadThickness)
	c.padLength = C.double(p.PadLength)
	c.padWidth = C.double(p.PadWidth)
	return c
}

func CreateFastener(params FastenerParams) *Shape {
	shp := C.create_fastener(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateFastenerWithPlace(params FastenerParams, position Point3, direction, upDir Dir3) *Shape {
	shp := C.create_fastener_with_place(params.to_struct(), position.val, direction.val, upDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

// =========================================================================
// 29. Guard Rail (护轨)
// =========================================================================

type GuardRailParams struct {
	Height       float64
	HeadWidth    float64
	BaseWidth    float64
	GrooveWidth  float64
	TotalLength  float64
	GaugeDistance float64
}

func (p *GuardRailParams) to_struct() C.guard_rail_params_t {
	var c C.guard_rail_params_t
	c.height = C.double(p.Height)
	c.headWidth = C.double(p.HeadWidth)
	c.baseWidth = C.double(p.BaseWidth)
	c.grooveWidth = C.double(p.GrooveWidth)
	c.totalLength = C.double(p.TotalLength)
	c.gaugeDistance = C.double(p.GaugeDistance)
	return c
}

func CreateGuardRail(params GuardRailParams) *Shape {
	shp := C.create_guard_rail(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateGuardRailWithPlace(params GuardRailParams, startPoint, endPoint Point3) *Shape {
	shp := C.create_guard_rail_with_place(params.to_struct(), startPoint.val, endPoint.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

// =========================================================================
// 30. Mast Assembly (支柱装配)
// =========================================================================

type MastAssemblyParams struct {
	MastType        int
	MastHeight      float64
	CantileverType  int
	HasCrossArm     bool
	ArmDiameter     float64
	Stagger         float64
	CompType        int
	RatedTension    float64
	HasGuyWire      bool
}

func (p *MastAssemblyParams) to_struct() C.mast_assembly_params_t {
	var c C.mast_assembly_params_t
	c.mastType = C.int(p.MastType)
	c.mastHeight = C.double(p.MastHeight)
	c.cantileverType = C.int(p.CantileverType)
	c.hasCrossArm = C.bool(p.HasCrossArm)
	c.armDiameter = C.double(p.ArmDiameter)
	c.stagger = C.double(p.Stagger)
	c.compType = C.int(p.CompType)
	c.ratedTension = C.double(p.RatedTension)
	c.hasGuyWire = C.bool(p.HasGuyWire)
	return c
}

func CreateMastAssembly(params MastAssemblyParams) *Shape {
	shp := C.create_mast_assembly(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateMastAssemblyWithPlace(params MastAssemblyParams, position Point3, direction, upDir Dir3) *Shape {
	shp := C.create_mast_assembly_with_place(params.to_struct(), position.val, direction.val, upDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

// =========================================================================
// 31. Switch Rail (尖轨)
// =========================================================================

type SwitchRailParams struct {
	Length        float64
	RailHeight    float64
	RailHeadWidth float64
	RailBaseWidth float64
	TipWidth      float64
	CurveRadius   float64
	IsLeftHand    bool
}

func (p *SwitchRailParams) to_struct() C.switch_rail_params_t {
	return C.switch_rail_params_t{
		length:        C.double(p.Length),
		railHeight:    C.double(p.RailHeight),
		railHeadWidth: C.double(p.RailHeadWidth),
		railBaseWidth: C.double(p.RailBaseWidth),
		tipWidth:      C.double(p.TipWidth),
		curveRadius:   C.double(p.CurveRadius),
		isLeftHand:    C.bool(p.IsLeftHand),
	}
}

func CreateSwitchRail(params SwitchRailParams) *Shape {
	shp := C.create_switch_rail(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateSwitchRailWithPlace(params SwitchRailParams, position Point3, direction, upDir Dir3) *Shape {
	shp := C.create_switch_rail_with_place(params.to_struct(), position.val, direction.val, upDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

// =========================================================================
// 32. Frog (辙叉)
// =========================================================================

type FrogParams struct {
	TurnoutNo     int
	Gauge         float64
	RailHeight    float64
	RailHeadWidth float64
	RailBaseWidth float64
}

func (p *FrogParams) to_struct() C.frog_params_t {
	return C.frog_params_t{
		turnoutNo:     C.int(p.TurnoutNo),
		gauge:         C.double(p.Gauge),
		railHeight:    C.double(p.RailHeight),
		railHeadWidth: C.double(p.RailHeadWidth),
		railBaseWidth: C.double(p.RailBaseWidth),
	}
}

func CreateFrog(params FrogParams) *Shape {
	shp := C.create_frog(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateFrogWithPlace(params FrogParams, position Point3, direction, upDir Dir3) *Shape {
	shp := C.create_frog_with_place(params.to_struct(), position.val, direction.val, upDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

// =========================================================================
// 33. Turnout (单开道岔)
// =========================================================================

type TurnoutParams struct {
	TurnoutNo        int
	IsLeftHand       bool
	Gauge            float64
	RailHeight       float64
	RailHeadWidth    float64
	RailBaseWidth    float64
	SwitchRailLength float64
	LeadCurveRadius  float64
	FrogLength       float64
	SleeperCount     int
	SleeperSpacing   float64
}

func (p *TurnoutParams) to_struct() C.turnout_params_t {
	return C.turnout_params_t{
		turnoutNo:        C.int(p.TurnoutNo),
		isLeftHand:       C.bool(p.IsLeftHand),
		gauge:            C.double(p.Gauge),
		railHeight:       C.double(p.RailHeight),
		railHeadWidth:    C.double(p.RailHeadWidth),
		railBaseWidth:    C.double(p.RailBaseWidth),
		switchRailLength: C.double(p.SwitchRailLength),
		leadCurveRadius:  C.double(p.LeadCurveRadius),
		frogLength:       C.double(p.FrogLength),
		sleeperCount:     C.int(p.SleeperCount),
		sleeperSpacing:   C.double(p.SleeperSpacing),
	}
}

func CreateTurnout(params TurnoutParams) *Shape {
	shp := C.create_turnout(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateTurnoutWithPlace(params TurnoutParams, position Point3, direction, upDir Dir3) *Shape {
	shp := C.create_turnout_with_place(params.to_struct(), position.val, direction.val, upDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

// =========================================================================
// GeoJSON 中心线 → 轨道区段/道岔段参数推算
// =========================================================================

// 线段类型
type TrackSegmentType int

const (
	SegmentStraight   TrackSegmentType = 0 // 直线
	SegmentCurve      TrackSegmentType = 1 // 圆曲线
	SegmentTransition TrackSegmentType = 2 // 缓和曲线
	SegmentTurnout    TrackSegmentType = 3 // 道岔分岔点
)

// 轨道区段描述
type TrackSegment struct {
	SegType      TrackSegmentType
	Points       []Point3  // 本段坐标序列
	Length       float64   // 弧长(mm)
	CurveRadius  float64   // 曲线半径(mm), 直线=0
	SuperElevation float64 // 超高(mm)
	StartMileage float64   // 起始里程(m)
}

// 道岔段参数 — 从中心线分岔点 + GeoJSON 属性推算
type TurnoutSegment struct {
	Position        Point3  // 岔心位置 (理论中心)
	MainDirection   Dir3    // 直股方向
	BranchDirection Dir3    // 侧股方向
	Hand            string  // "left" / "right"
	TurnoutNo       int     // 道岔号数
	FrogAngle       float64 // 辙叉角(rad)
	FrogLength      float64 // 辙叉长度
	SwitchRailLen   float64 // 尖轨长度
	LeadCurveRadius float64 // 导曲线半径
	TotalLength     float64 // 道岔全长
}

// DetectTrackSegments 从中心线点序列识别曲线段类型: 直线/圆曲线/缓和曲线/道岔
// 使用三点圆拟合法: 对每三个连续点拟合圆, 曲率≈0→直线, 曲率恒定→圆曲线, 曲率变化→缓和曲线
func DetectTrackSegments(centerline []Point3) []TrackSegment {
	if len(centerline) < 3 {
		return []TrackSegment{{SegType: SegmentStraight, Points: centerline, Length: 0, StartMileage: 0}}
	}

	// 对每个内部点拟合三点圆, 计算曲率和圆心
	type curveInfo struct {
		radius   float64 // 曲率半径, 1e8=近视直线
		centerX  float64
		centerY  float64
		curvature float64 // 1/radius
	}
	infos := make([]curveInfo, len(centerline))

	for i := 1; i < len(centerline)-1; i++ {
		x1 := float64(centerline[i-1].val.x); y1 := float64(centerline[i-1].val.y)
		x2 := float64(centerline[i].val.x); y2 := float64(centerline[i].val.y)
		x3 := float64(centerline[i+1].val.x); y3 := float64(centerline[i+1].val.y)

		// 三点共线判定
		cross := (x2-x1)*(y3-y1) - (y2-y1)*(x3-x1)
		if math.Abs(cross) < 1e-6 {
			infos[i].radius = 1e8
			infos[i].curvature = 0
			continue
		}

		// 三点圆拟合: 中垂线交点法求圆心
		mx1, my1 := (x1+x2)/2, (y1+y2)/2
		mx2, my2 := (x2+x3)/2, (y2+y3)/2
		k1 := (x2 - x1) / (y1 - y2)
		k2 := (x3 - x2) / (y2 - y3)

		cx := (my2 - my1 + k1*mx1 - k2*mx2) / (k1 - k2)
		cy := k1*(cx-mx1) + my1
		r := math.Sqrt((cx-x1)*(cx-x1) + (cy-y1)*(cy-y1))

		infos[i].radius = r
		infos[i].centerX = cx
		infos[i].centerY = cy
		infos[i].curvature = 1.0 / math.Max(r, 1)
	}
	infos[0] = infos[1]
	infos[len(infos)-1] = infos[len(infos)-2]

	// 曲率分类阈值
	const kStraight = 0.000005  // 曲率<此值→直线 (r>200km)
	const kMergeTol = 0.000001  // 相邻点曲率差<此值→同类

	// 区分段类型: 0=直线, 1=圆曲线, 2=缓和曲线
	types := make([]int, len(infos))
	for i := 0; i < len(infos); i++ {
		if infos[i].curvature < kStraight {
			types[i] = 0 // 直线
		} else {
			// 检查前后两点曲率差: 恒定→圆曲线, 变化→缓和曲线
			if i > 0 && i < len(infos)-1 {
				diff1 := math.Abs(infos[i].curvature - infos[i-1].curvature)
				diff2 := math.Abs(infos[i+1].curvature - infos[i].curvature)
				if diff1 > kMergeTol*3 || diff2 > kMergeTol*3 {
					types[i] = 2 // 缓和曲线
				} else {
					types[i] = 1 // 圆曲线
				}
			} else {
				types[i] = 1
			}
		}
	}

	// 合并相邻同类型段
	var segs []TrackSegment
	start := 0
	mileage := 0.0

	addSegment := func(s, e int, t int) {
		if e <= s { return }
		pts := make([]Point3, e-s+2)
		copy(pts, centerline[s:min(e+2, len(centerline))])
		l := 0.0
		for j := 1; j < len(pts); j++ {
			dx := float64(pts[j].val.x - pts[j-1].val.x)
			dy := float64(pts[j].val.y - pts[j-1].val.y)
			l += math.Sqrt(dx*dx + dy*dy)
		}
		segType := SegmentStraight
		if t == 1 { segType = SegmentCurve }
		if t == 2 { segType = SegmentTransition }
		mid := (s + e) / 2
		seg := TrackSegment{
			SegType:     segType,
			Points:      pts,
			Length:      l,
			CurveRadius: infos[mid].radius,
			StartMileage: mileage / 1000,
		}
		// 曲线段补充圆心方向
		if segType == SegmentCurve && infos[mid].radius < 1e7 {
			seg.CurveRadius = infos[mid].radius
		}
		segs = append(segs, seg)
		mileage += l
	}

	for i := 1; i < len(types); i++ {
		if types[i] != types[i-1] {
			addSegment(start, i-1, types[i-1])
			start = i - 1
		}
	}
	addSegment(start, len(types)-1, types[start])

	return segs
}

// CalcTurnoutSegment 从 GeoJSON 分岔点推算道岔段参数
// 输入: 岔心坐标 + 直股方向 + 侧线方向 + 道岔属性
// 输出: TurnoutSegment 含所有计算参数
func CalcTurnoutSegment(
	crossPoint Point3,
	mainDir, branchDir Dir3,
	hand string, turnoutNo int,
	gauge float64,
) TurnoutSegment {
	t := TurnoutSegment{
		Position:      crossPoint,
		MainDirection: mainDir,
		BranchDirection: branchDir,
		Hand:          hand,
		TurnoutNo:     turnoutNo,
	}

	// 辙叉角 α = arctan(1/N)
	t.FrogAngle = math.Atan(1.0 / float64(turnoutNo))

	// 参数查表
	switch turnoutNo {
	case 9:
		t.LeadCurveRadius = 180000; t.SwitchRailLen = 6450; t.TotalLength = 29569
	case 12:
		t.LeadCurveRadius = 350000; t.SwitchRailLen = 7700; t.TotalLength = 37800
	case 18:
		t.LeadCurveRadius = 800000; t.SwitchRailLen = 12500; t.TotalLength = 56700
	case 30:
		t.LeadCurveRadius = 2700000; t.SwitchRailLen = 15400; t.TotalLength = 94500
	case 42:
		t.LeadCurveRadius = 5000000; t.SwitchRailLen = 19200; t.TotalLength = 132300
	default:
		t.LeadCurveRadius = 350000; t.SwitchRailLen = 7700; t.TotalLength = 37800
	}

	// 辙叉长度= 轨距 × 号数 / 2
	t.FrogLength = gauge * float64(turnoutNo) * 0.28

	return t
}

// CalcFrogTable 辙叉参数查表 (独立调用)
func CalcFrogTable(turnoutNo int, gauge float64) (frogAngleRad, frogLength, leadCurveR, switchLen, totalLen float64) {
	frogAngleRad = math.Atan(1.0 / float64(turnoutNo))
	switch turnoutNo {
	case 9: leadCurveR = 180000; switchLen = 6450; totalLen = 29569
	case 12: leadCurveR = 350000; switchLen = 7700; totalLen = 37800
	case 18: leadCurveR = 800000; switchLen = 12500; totalLen = 56700
	case 30: leadCurveR = 2700000; switchLen = 15400; totalLen = 94500
	case 42: leadCurveR = 5000000; switchLen = 19200; totalLen = 132300
	default: leadCurveR = 350000; switchLen = 7700; totalLen = 37800
	}
	frogLength = gauge * float64(turnoutNo) * 0.28
	return
}

type OcsMastPosition struct {
	Mileage           float64 // 里程(m)
	Position          Point3  // 柱底中心
	MastHeight        float64 // 柱高(mm)
	BeamBottomZ       float64 // 横梁底部 Z
	ContactWireZ      float64 // 接触线 Z
	MessengerWireZ    float64 // 承力索 Z
	Stagger           float64 // 拉出值(mm)
	HangerPostLength  float64 // 吊柱长度
	BracketMountZ     float64 // 腕臂底座 Z
	InsulatorMountZ   float64 // 绝缘子 Z
	RegistrationArmZ  float64 // 定位器 Z
	IsTensionMast     bool   // 是否锚柱
}

type OcsSpanInput struct {
	Centerline      []Point3 // 线路中心线
	ContactHeight   float64  // 导高 默认 5300
	StructureHeight float64  // 结构高度 默认 1400
	StaggerTable    []float64 // 拉出值
	SpanLength      float64  // 标准跨距 默认 50000
	MastHeight      float64  // 支柱高度
	HasCompensator  bool     // 两端设补偿
}

type OcsSpanOutput struct {
	Masts          []OcsMastPosition
	TotalLength    float64
	MastCount      int
	BeamBottomZ    float64
	ContactWireZ   float64
	MessengerWireZ float64
}

func CalcOcsSpanPositions(input OcsSpanInput) OcsSpanOutput {
	out := OcsSpanOutput{}
	if len(input.Centerline) < 2 || input.SpanLength <= 0 {
		return out
	}

	CH := input.ContactHeight
	if CH <= 0 { CH = 5300 }
	SH := input.StructureHeight
	if SH <= 0 { SH = 1400 }
	MH := input.MastHeight
	if MH <= 0 { MH = 8000 }
	spanLen := input.SpanLength
	if spanLen <= 0 { spanLen = 50000 }

	beamBottomZ := CH + SH
	systemMargin := 800.0

	out.ContactWireZ = CH
	out.MessengerWireZ = CH + SH
	out.BeamBottomZ = beamBottomZ

	if MH < beamBottomZ+systemMargin {
		return out
	}

	// 计算总弧长
	totalLen := 0.0
	for i := 0; i < len(input.Centerline)-1; i++ {
		dx := input.Centerline[i+1].val.x - input.Centerline[i].val.x
		dy := input.Centerline[i+1].val.y - input.Centerline[i].val.y
		dz := input.Centerline[i+1].val.z - input.Centerline[i].val.z
		totalLen += math.Sqrt(float64(dx*dx + dy*dy + dz*dz))
	}
	out.TotalLength = totalLen
	out.MastCount = int(totalLen/spanLen) + 1
	if out.MastCount < 2 { out.MastCount = 2 }

	mastSpacing := totalLen / float64(out.MastCount-1)

	for m := 0; m < out.MastCount; m++ {
		dist := float64(m) * mastSpacing
		acc := 0.0
		pos := input.Centerline[0]
		for j := 0; j < len(input.Centerline)-1; j++ {
			dx := float64(input.Centerline[j+1].val.x - input.Centerline[j].val.x)
			dy := float64(input.Centerline[j+1].val.y - input.Centerline[j].val.y)
			dz := float64(input.Centerline[j+1].val.z - input.Centerline[j].val.z)
			segLen := math.Sqrt(dx*dx + dy*dy + dz*dz)
			if acc+segLen >= dist || j == len(input.Centerline)-2 {
				t := 0.0
				if segLen > 0 { t = (dist - acc) / segLen }
				if t < 0 { t = 0 }; if t > 1 { t = 1 }
				px := float64(input.Centerline[j].val.x) + dx*t
				py := float64(input.Centerline[j].val.y) + dy*t
				pz := float64(input.Centerline[j].val.z) + dz*t
				pos = NewPoint3([3]float64{px, py, pz})
				break
			}
			acc += segLen
		}
		stagger := 0.0
		if m < len(input.StaggerTable) { stagger = input.StaggerTable[m] }

		mp := OcsMastPosition{
			Mileage:         dist / 1000,
			Position:        pos,
			MastHeight:      MH,
			BeamBottomZ:     beamBottomZ,
			ContactWireZ:    CH,
			MessengerWireZ:  CH + SH,
			Stagger:         stagger,
			HangerPostLength: MH - beamBottomZ - float64(systemMargin)*0.5,
			BracketMountZ:   beamBottomZ - 100,
			InsulatorMountZ: beamBottomZ - 600,
			RegistrationArmZ: CH,
			IsTensionMast:   input.HasCompensator && (m == 0 || m == out.MastCount-1),
		}
		out.Masts = append(out.Masts, mp)
	}
	return out
}

// =========================================================================
// 37. Straight Track (直线轨道段)
// =========================================================================

type StraightTrackParams struct {
	StartPoint       Point3
	EndPoint         Point3
	Gauge            float64
	RailHeight       float64
	RailHeadWidth    float64
	RailBaseWidth    float64
	SleeperLength    float64
	SleeperWidth     float64
	SleeperHeight    float64
	SleeperSpacing   float64
	BallastTopWidth  float64
	BallastThickness float64
	BallastSlope     float64
}

func CreateStraightTrack(params StraightTrackParams) *Shape {
	var cp C.straight_track_params_t
	cp.startPoint = params.StartPoint.val
	cp.endPoint = params.EndPoint.val
	cp.gauge = C.double(params.Gauge)
	cp.railHeight = C.double(params.RailHeight)
	cp.railHeadWidth = C.double(params.RailHeadWidth)
	cp.railBaseWidth = C.double(params.RailBaseWidth)
	cp.sleeperLength = C.double(params.SleeperLength)
	cp.sleeperWidth = C.double(params.SleeperWidth)
	cp.sleeperHeight = C.double(params.SleeperHeight)
	cp.sleeperSpacing = C.double(params.SleeperSpacing)
	cp.ballastTopWidth = C.double(params.BallastTopWidth)
	cp.ballastThickness = C.double(params.BallastThickness)
	cp.ballastSlope = C.double(params.BallastSlope)
	s := &Shape{inner: &innerShape{val: C.create_straight_track(cp)}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

// =========================================================================
// 38. Curve Track (曲线轨道段)
// =========================================================================

type CurveTrackParams struct {
	CurveCenter      Point3
	StartAngle       float64
	SweepAngle       float64
	CurveRadius      float64
	Gauge            float64
	SuperElevation   float64
	RailHeight       float64
	RailHeadWidth    float64
	RailBaseWidth    float64
	SleeperLength    float64
	SleeperWidth     float64
	SleeperHeight    float64
	SleeperSpacing   float64
	BallastTopWidth  float64
	BallastThickness float64
	BallastSlope     float64
}

func CreateCurveTrack(params CurveTrackParams) *Shape {
	var cp C.curve_track_params_t
	cp.curveCenter = params.CurveCenter.val
	cp.startAngle = C.double(params.StartAngle)
	cp.sweepAngle = C.double(params.SweepAngle)
	cp.curveRadius = C.double(params.CurveRadius)
	cp.gauge = C.double(params.Gauge)
	cp.superElevation = C.double(params.SuperElevation)
	cp.railHeight = C.double(params.RailHeight)
	cp.railHeadWidth = C.double(params.RailHeadWidth)
	cp.railBaseWidth = C.double(params.RailBaseWidth)
	cp.sleeperLength = C.double(params.SleeperLength)
	cp.sleeperWidth = C.double(params.SleeperWidth)
	cp.sleeperHeight = C.double(params.SleeperHeight)
	cp.sleeperSpacing = C.double(params.SleeperSpacing)
	cp.ballastTopWidth = C.double(params.BallastTopWidth)
	cp.ballastThickness = C.double(params.BallastThickness)
	cp.ballastSlope = C.double(params.BallastSlope)
	s := &Shape{inner: &innerShape{val: C.create_curve_track(cp)}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

// =========================================================================
// 35. Rail Pair (轨排对)
// =========================================================================

func CreateRailPairFromPoints(centerline []Point3, gauge, superElevation, railHeight, railHeadWidth, railBaseWidth float64) *Shape {
	pts := make([]C.pnt3d_t, len(centerline))
	for i, p := range centerline { pts[i] = p.val }
	var cParams C.rail_pair_params_t
	cParams.centerline = &pts[0]
	cParams.pointCount = C.int(len(pts))
	cParams.gauge = C.double(gauge)
	cParams.superElevation = C.double(superElevation)
	cParams.railHeight = C.double(railHeight)
	cParams.railHeadWidth = C.double(railHeadWidth)
	cParams.railBaseWidth = C.double(railBaseWidth)
	s := &Shape{inner: &innerShape{val: C.create_rail_pair(cParams)}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

// =========================================================================
// 36. Sleeper Layout (轨枕阵列)
// =========================================================================

func CreateSleeperLayout(centerline []Point3, length, width, height, spacing, gauge float64) *Shape {
	pts := make([]C.pnt3d_t, len(centerline))
	for i, p := range centerline { pts[i] = p.val }
	var cParams C.sleeper_layout_params_t
	cParams.centerline = &pts[0]
	cParams.pointCount = C.int(len(pts))
	cParams.length = C.double(length)
	cParams.width = C.double(width)
	cParams.height = C.double(height)
	cParams.spacing = C.double(spacing)
	cParams.gauge = C.double(gauge)
	s := &Shape{inner: &innerShape{val: C.create_sleeper_layout(cParams)}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

