package topo

/*
#include <stdlib.h>
#include "plate_plate_c_api.h"
#cgo CFLAGS: -I  ./libs
#cgo linux CXXFLAGS: -I ./libs  -std=gnu++14
#cgo darwin CXXFLAGS: -I ./libs  -std=gnu++14
#cgo darwin,arm CXXFLAGS: -I ./libs  -std=gnu++14
#cgo windows CXXFLAGS: -I ./libs  -std=gnu++14
*/
import "C"
import (
	"runtime"
	"unsafe"
)

type PlateD1 struct {
	val C.struct__plate_d1_t
}

func NewPlateD1(du, dv XYZ) PlateD1 {
	var val C.struct__plate_d1_t
	val.du = du.val
	val.dv = dv.val
	return PlateD1{val: val}
}

type PlateD2 struct {
	val C.struct__plate_d2_t
}

func NewPlateD2(duu, duv, dvv XYZ) PlateD2 {
	var val C.struct__plate_d2_t
	val.duu = duu.val
	val.duv = duv.val
	val.dvv = dvv.val
	return PlateD2{val: val}
}

type PlateD3 struct {
	val C.struct__plate_d3_t
}

func NewPlateD3(duuu, duuv, duvv, dvvv XYZ) PlateD3 {
	var val C.struct__plate_d3_t
	val.duuu = duuu.val
	val.duuv = duuv.val
	val.duvv = duvv.val
	val.dvvv = dvvv.val
	return PlateD3{val: val}
}

type Plate struct {
	val *C.struct__plate_plate_t
}

func NewPlate() *Plate {
	p := &Plate{val: C.plate_plate_new()}
	runtime.SetFinalizer(p, (*Plate).free)
	return p

}

func (p *Plate) free() {
	C.plate_plate_free(p.val)
	p.val = nil
}

func (p *Plate) LoadPinpointConstraint(pc *PinpointConstraint) {
	C.plate_plate_load_plate_pinpoint_constraint(p.val, pc.val)
}

func (p *Plate) LoadLinearXYZConstraint(pc *LinearXYZConstraint) {
	C.plate_plate_load_plate_linear_xyz_constraint(p.val, pc.val)
}

func (p *Plate) LoadLinearScalarConstraint(pc *LinearScalarConstraint) {
	C.plate_plate_load_plate_linear_scalar_constraint(p.val, pc.val)
}

func (p *Plate) LoadGlobalTranslationConstraint(pc *GlobalTranslationConstraint) {
	C.plate_plate_load_plate_global_translation_constraint(p.val, pc.val)
}

func (p *Plate) LoadLineConstraint(pc *LineConstraint) {
	C.plate_plate_load_plate_line_constraint(p.val, pc.val)
}

func (p *Plate) LoadPlaneConstraint(pc *PlaneConstraint) {
	C.plate_plate_load_plate_plane_constraint(p.val, pc.val)
}

func (p *Plate) LoadSampledCurveConstraint(pc *SampledCurveConstraint) {
	C.plate_plate_load_plate_sampled_curve_constraint(p.val, pc.val)
}

func (p *Plate) LoadGtoCConstraint(pc *GtoCConstraint) {
	C.plate_plate_load_plate_g_to_c_constraint(p.val, pc.val)
}

func (p *Plate) LoadFreeGtoCConstraint(pc *FreeGtoCConstraint) {
	C.plate_plate_load_plate_free_g_to_c_constraint(p.val, pc.val)
}

func (p *Plate) SolveTI(ord int, anisotropie float64) {
	C.plate_plate_solveti(p.val, C.int(ord), C.double(anisotropie))
}

type PinpointConstraint struct {
	val *C.struct__plate_pinpoint_constraint_t
}

func (p *PinpointConstraint) free() {
	C.plate_pinpoint_constraint_free(p.val)
	p.val = nil
}

func NewPinpointConstraint(p XY, v XYZ, iu, iv int) *PinpointConstraint {
	pt := &PinpointConstraint{val: C.plate_pinpoint_constraint_new(p.val, v.val, C.int(iu), C.int(iv))}
	runtime.SetFinalizer(p, (*PinpointConstraint).free)
	return pt
}

type LinearXYZConstraint struct {
	val *C.struct__plate_linear_xyz_constraint_t
}

func (p *LinearXYZConstraint) free() {
	C.plate_linear_xyz_constraint_free(p.val)
	p.val = nil
}

func NewLinearXYZConstraintDim1(ppc []PinpointConstraint, coffes []float64) *LinearXYZConstraint {
	ppcc := make([]*C.struct__plate_pinpoint_constraint_t, len(ppc))
	for i := range ppc {
		ppcc[i] = ppc[i].val
	}
	p := &LinearXYZConstraint{val: C.plate_linear_xyz_constraint_new_1dim(&ppcc[0], C.int(len(ppc)), (*C.double)(unsafe.Pointer(&coffes[0])), C.int(len(coffes)))}
	runtime.SetFinalizer(p, (*LinearXYZConstraint).free)
	return p
}

func NewLinearXYZConstraintDim2(ppc []PinpointConstraint, coffes [][]float64) *LinearXYZConstraint {
	ppcc := make([]*C.struct__plate_pinpoint_constraint_t, len(ppc))
	for i := range ppc {
		ppcc[i] = ppc[i].val
	}
	row := len(coffes)
	col := len(coffes[0])
	inw := make([]C.double, col*row)

	for i := 0; i < row; i++ {
		for j := 0; j < col; j++ {
			inw[i*col+j] = C.double(coffes[j][i])
		}
	}
	p := &LinearXYZConstraint{val: C.plate_linear_xyz_constraint_new_2dim(&ppcc[0], C.int(len(ppc)), &inw[0], C.int(row), C.int(col))}
	runtime.SetFinalizer(p, (*LinearXYZConstraint).free)
	return p
}

type LinearScalarConstraint struct {
	val *C.struct__plate_linear_scalar_constraint_t
}

func (p *LinearScalarConstraint) free() {
	C.plate_linear_scalar_constraint_free(p.val)
	p.val = nil
}

func NewLinearScalarConstraint(ppc *PinpointConstraint, x XYZ) *LinearScalarConstraint {
	p := &LinearScalarConstraint{val: C.plate_linear_scalar_constraint_new(ppc.val, x.val)}
	runtime.SetFinalizer(p, (*LinearScalarConstraint).free)
	return p
}

func NewLinearScalarConstraintDim1(ppc []PinpointConstraint, coffes []XYZ) *LinearScalarConstraint {
	ppcc := make([]*C.struct__plate_pinpoint_constraint_t, len(ppc))
	for i := range ppc {
		ppcc[i] = ppc[i].val
	}
	xyzc := make([]C.struct__xyz_t, len(coffes))
	for i := range coffes {
		xyzc[i] = coffes[i].val
	}
	p := &LinearScalarConstraint{val: C.plate_linear_scalar_constraint_new_1dim(&ppcc[0], C.int(len(ppc)), &xyzc[0], C.int(len(coffes)))}
	runtime.SetFinalizer(p, (*LinearScalarConstraint).free)
	return p
}

func NewLinearScalarConstraintDim2(ppc []PinpointConstraint, coffes [][]XYZ) *LinearScalarConstraint {
	ppcc := make([]*C.struct__plate_pinpoint_constraint_t, len(ppc))
	for i := range ppc {
		ppcc[i] = ppc[i].val
	}
	row := len(coffes)
	col := len(coffes[0])
	inw := make([]C.struct__xyz_t, col*row)

	for i := 0; i < row; i++ {
		for j := 0; j < col; j++ {
			inw[i*col+j] = coffes[j][i].val
		}
	}
	p := &LinearScalarConstraint{val: C.plate_linear_scalar_constraint_new_2dim(&ppcc[0], C.int(len(ppc)), &inw[0], C.int(row), C.int(col))}
	runtime.SetFinalizer(p, (*LinearScalarConstraint).free)
	return p
}

type GlobalTranslationConstraint struct {
	val *C.struct__plate_global_translation_constraint_t
}

func (p *GlobalTranslationConstraint) free() {
	C.plate_global_translation_constraint_free(p.val)
	p.val = nil
}

func NewGlobalTranslationConstraint(coffes []XY) *GlobalTranslationConstraint {
	xyc := make([]C.struct__xy_t, len(coffes))
	for i := range coffes {
		xyc[i] = coffes[i].val
	}
	p := &GlobalTranslationConstraint{val: C.plate_global_translation_constraint_new(&xyc[0], C.int(len(coffes)))}
	runtime.SetFinalizer(p, (*GlobalTranslationConstraint).free)
	return p
}

type LineConstraint struct {
	val *C.struct__plate_line_constraint_t
}

func (p *LineConstraint) free() {
	C.plate_line_constraint_free(p.val)
	p.val = nil
}

func NewLineConstraint(p XY, v Line, iu, iv int) *LineConstraint {
	pt := &LineConstraint{val: C.plate_line_constraint_new(p.val, v.val, C.int(iu), C.int(iv))}
	runtime.SetFinalizer(p, (*LineConstraint).free)
	return pt
}

type PlaneConstraint struct {
	val *C.struct__plate_plane_constraint_t
}

func (p *PlaneConstraint) free() {
	C.plate_plane_constraint_free(p.val)
	p.val = nil
}

func NewPlaneConstraint(p XY, v Plane, iu, iv int) *PlaneConstraint {
	pt := &PlaneConstraint{val: C.plate_plane_constraint_new(p.val, v.val, C.int(iu), C.int(iv))}
	runtime.SetFinalizer(p, (*PlaneConstraint).free)
	return pt
}

type SampledCurveConstraint struct {
	val *C.struct__plate_sampled_curve_constraint_t
}

func (p *SampledCurveConstraint) free() {
	C.plate_sampled_curve_constraint_free(p.val)
	p.val = nil
}

func NewSampledCurveConstraint(ppc []PinpointConstraint) *SampledCurveConstraint {
	ppcc := make([]*C.struct__plate_pinpoint_constraint_t, len(ppc))
	for i := range ppc {
		ppcc[i] = ppc[i].val
	}

	p := &SampledCurveConstraint{val: C.plate_sampled_curve_constraint_new(&ppcc[0], C.int(len(ppc)))}
	runtime.SetFinalizer(p, (*SampledCurveConstraint).free)
	return p
}

type GtoCConstraint struct {
	val *C.struct__plate_g_to_c_constraint_t
}

func (p *GtoCConstraint) free() {
	C.plate_g_to_c_constraint_free(p.val)
	p.val = nil
}

func NewGtoCConstraintNew1(point2d XY, D1S, D1T PlateD1) *GtoCConstraint {
	p := &GtoCConstraint{val: C.plate_g_to_c_constraint_new_1(point2d.val, D1S.val, D1T.val)}
	runtime.SetFinalizer(p, (*GtoCConstraint).free)
	return p
}

func NewGtoCConstraintNew2(point2d XY, D1S, D1T PlateD1, nP XYZ) *GtoCConstraint {
	p := &GtoCConstraint{val: C.plate_g_to_c_constraint_new_2(point2d.val, D1S.val, D1T.val, nP.val)}
	runtime.SetFinalizer(p, (*GtoCConstraint).free)
	return p
}

func NewGtoCConstraintNew3(point2d XY, D1S, D1T PlateD1, D2S, D2T PlateD2) *GtoCConstraint {
	p := &GtoCConstraint{val: C.plate_g_to_c_constraint_new_3(point2d.val, D1S.val, D1T.val, D2S.val, D2T.val)}
	runtime.SetFinalizer(p, (*GtoCConstraint).free)
	return p
}

func NewGtoCConstraintNew4(point2d XY, D1S, D1T PlateD1, D2S, D2T PlateD2, nP XYZ) *GtoCConstraint {
	p := &GtoCConstraint{val: C.plate_g_to_c_constraint_new_4(point2d.val, D1S.val, D1T.val, D2S.val, D2T.val, nP.val)}
	runtime.SetFinalizer(p, (*GtoCConstraint).free)
	return p
}

func NewGtoCConstraintNew5(point2d XY, D1S, D1T PlateD1, D2S, D2T PlateD2, D3S, D3T PlateD3) *GtoCConstraint {
	p := &GtoCConstraint{val: C.plate_g_to_c_constraint_new_5(point2d.val, D1S.val, D1T.val, D2S.val, D2T.val, D3S.val, D3T.val)}
	runtime.SetFinalizer(p, (*GtoCConstraint).free)
	return p
}

func NewGtoCConstraintNew6(point2d XY, D1S, D1T PlateD1, D2S, D2T PlateD2, D3S, D3T PlateD3, nP XYZ) *GtoCConstraint {
	p := &GtoCConstraint{val: C.plate_g_to_c_constraint_new_6(point2d.val, D1S.val, D1T.val, D2S.val, D2T.val, D3S.val, D3T.val, nP.val)}
	runtime.SetFinalizer(p, (*GtoCConstraint).free)
	return p
}

type FreeGtoCConstraint struct {
	val *C.struct__plate_free_g_to_c_constraint_t
}

func (p *FreeGtoCConstraint) free() {
	C.plate_free_g_to_c_constraint_free(p.val)
	p.val = nil
}

func NewFreeGtoCConstraintNew1(point2d XY, D1S, D1T PlateD1, IncrementalLoad float64, orientation int) *FreeGtoCConstraint {
	p := &FreeGtoCConstraint{val: C.plate_free_g_to_c_constraint_new_1(point2d.val, D1S.val, D1T.val, C.double(IncrementalLoad), C.int(orientation))}
	runtime.SetFinalizer(p, (*FreeGtoCConstraint).free)
	return p
}

func NewFreeGtoCConstraintNew2(point2d XY, D1S, D1T PlateD1, D2S, D2T PlateD2, IncrementalLoad float64, orientation int) *FreeGtoCConstraint {
	p := &FreeGtoCConstraint{val: C.plate_free_g_to_c_constraint_new_2(point2d.val, D1S.val, D1T.val, D2S.val, D2T.val, C.double(IncrementalLoad), C.int(orientation))}
	runtime.SetFinalizer(p, (*FreeGtoCConstraint).free)
	return p
}

func NewFreeGtoCConstraintNew3(point2d XY, D1S, D1T PlateD1, D2S, D2T PlateD2, D3S, D3T PlateD3, IncrementalLoad float64, orientation int) *FreeGtoCConstraint {
	p := &FreeGtoCConstraint{val: C.plate_free_g_to_c_constraint_new_3(point2d.val, D1S.val, D1T.val, D2S.val, D2T.val, D3S.val, D3T.val, C.double(IncrementalLoad), C.int(orientation))}
	runtime.SetFinalizer(p, (*FreeGtoCConstraint).free)
	return p
}
