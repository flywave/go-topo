package topo

/*
#include <stdlib.h>
#include "primitives_railway_c_api.h"
*/
import "C"
import (
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
	OuterDiameter float64
	WallThickness float64
	Angle         float64
}

func (p *RegistrationArmParams) to_struct() C.registration_arm_params_t {
	var c C.registration_arm_params_t
	c.ctype = C.int(p.Type)
	c.length = C.double(p.Length)
	c.outerDiameter = C.double(p.OuterDiameter)
	c.wallThickness = C.double(p.WallThickness)
	c.angle = C.double(p.Angle)
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
	Length      float64
	Width       float64
	Height      float64
	Gauge       float64
	GrooveDepth float64
	Spacing     float64
}

func (p *SleeperParams) to_struct() C.sleeper_params_t {
	var c C.sleeper_params_t
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

type BallastParams struct {
	TopWidth  float64
	Thickness float64
	SideSlope float64
	Length    float64
}

func (p *BallastParams) to_struct() C.ballast_params_t {
	var c C.ballast_params_t
	c.topWidth = C.double(p.TopWidth)
	c.thickness = C.double(p.Thickness)
	c.sideSlope = C.double(p.SideSlope)
	c.length = C.double(p.Length)
	return c
}

func CreateBallast(params BallastParams) *Shape {
	shp := C.create_ballast(params.to_struct())
	s := &Shape{inner: &innerShape{val: shp}}
	runtime.SetFinalizer(s.inner, (*innerShape).free)
	return s
}

func CreateBallastWithPlace(params BallastParams, position Point3, direction, upDir Dir3) *Shape {
	shp := C.create_ballast_with_place(params.to_struct(), position.val, direction.val, upDir.val)
	s := &Shape{inner: &innerShape{val: shp}}
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
