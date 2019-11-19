package topovis

/*
#include <stdlib.h>
#include "geometry_c_api.h"
#cgo CFLAGS: -I ./
#cgo linux CXXFLAGS: -I ./include/oce -I ./include/linux/oce -I ./
#cgo darwin CXXFLAGS: -I ./include/oce -I ./include/darwin/oce -I ./
#cgo windows CXXFLAGS:  -I ./include/oce -I ./include/windows/oce -I ./
*/
import "C"

type GeomGeometry struct {
	geom *C.struct__geom_geometry_t
}

func (g *GeomGeometry) Free() {
	C.geom_geometry_free(g.geom)
	g.geom = nil
}

func (g *GeomGeometry) Copy() *GeomGeometry {
	return &GeomGeometry{geom: C.geom_geometry_copy(g.geom)}
}

type GeomTransformation struct {
	geom *C.struct__geom_transformation_t
}

func (g *GeomTransformation) Free() {
	C.geom_transformation_free(g.geom)
	g.geom = nil
}

func (g *GeomTransformation) Copy() *GeomTransformation {
	return &GeomTransformation{geom: C.geom_transformation_copy(g.geom)}
}

type GeomAxisPlacement struct {
	geom *C.struct__geom_axis_placement_t
}

func (g *GeomAxisPlacement) Free() {
	C.geom_axis_placement_free(g.geom)
	g.geom = nil
}

func (g *GeomAxisPlacement) Copy() *GeomAxisPlacement {
	return &GeomAxisPlacement{geom: C.geom_axis_placement_copy(g.geom)}
}

type GeomAxis1Placement struct {
	geom *C.struct__geom_axis1_placement_t
}

func (g *GeomAxis1Placement) Free() {
	C.geom_axis1_placement_free(g.geom)
	g.geom = nil
}

func (g *GeomAxis1Placement) Copy() *GeomAxis1Placement {
	return &GeomAxis1Placement{geom: C.geom_axis1_placement_copy(g.geom)}
}

type GeomAxis2Placement struct {
	geom *C.struct__geom_axis2_placement_t
}

func (g *GeomAxis2Placement) Free() {
	C.geom_axis2_placement_free(g.geom)
	g.geom = nil
}

func (g *GeomAxis2Placement) Copy() *GeomAxis2Placement {
	return &GeomAxis2Placement{geom: C.geom_axis2_placement_copy(g.geom)}
}

type GeomCurve struct {
	geom *C.struct__geom_curve_t
}

func (g *GeomCurve) Free() {
	C.geom_curve_free(g.geom)
	g.geom = nil
}

func (g *GeomCurve) Copy() *GeomCurve {
	return &GeomCurve{geom: C.geom_curve_copy(g.geom)}
}

type GeomBoundedCurve struct {
	geom *C.struct__geom_bounded_curve_t
}

func (g *GeomBoundedCurve) Free() {
	C.geom_bounded_curve_free(g.geom)
	g.geom = nil
}

func (g *GeomBoundedCurve) Copy() *GeomBoundedCurve {
	return &GeomBoundedCurve{geom: C.geom_bounded_curve_copy(g.geom)}
}

type GeomBezierCurve struct {
	geom *C.struct__geom_bezier_curve_t
}

func (g *GeomBezierCurve) Free() {
	C.geom_bezier_curve_free(g.geom)
	g.geom = nil
}

func (g *GeomBezierCurve) Copy() *GeomBezierCurve {
	return &GeomBezierCurve{geom: C.geom_bezier_curve_copy(g.geom)}
}

type GeomBSplineCurve struct {
	geom *C.struct__geom_bspline_curve_t
}

func (g *GeomBSplineCurve) Free() {
	C.geom_bspline_curve_free(g.geom)
	g.geom = nil
}

func (g *GeomBSplineCurve) Copy() *GeomBSplineCurve {
	return &GeomBSplineCurve{geom: C.geom_bspline_curve_copy(g.geom)}
}

type GeomTrimmedCurve struct {
	geom *C.struct__geom_trimmed_curve_t
}

func (g *GeomTrimmedCurve) Free() {
	C.geom_trimmed_curve_free(g.geom)
	g.geom = nil
}

func (g *GeomTrimmedCurve) Copy() *GeomTrimmedCurve {
	return &GeomTrimmedCurve{geom: C.geom_trimmed_curve_copy(g.geom)}
}

type GeomConic struct {
	geom *C.struct__geom_conic_t
}

func (g *GeomConic) Free() {
	C.geom_conic_free(g.geom)
	g.geom = nil
}

func (g *GeomConic) Copy() *GeomConic {
	return &GeomConic{geom: C.geom_conic_copy(g.geom)}
}

type GeomCircle struct {
	geom *C.struct__geom_circle_t
}

func (g *GeomCircle) Free() {
	C.geom_circle_free(g.geom)
	g.geom = nil
}

func (g *GeomCircle) Copy() *GeomCircle {
	return &GeomCircle{geom: C.geom_circle_copy(g.geom)}
}

type GeomEllipse struct {
	geom *C.struct__geom_ellipse_t
}

func (g *GeomEllipse) Free() {
	C.geom_ellipse_free(g.geom)
	g.geom = nil
}

func (g *GeomEllipse) Copy() *GeomEllipse {
	return &GeomEllipse{geom: C.geom_ellipse_copy(g.geom)}
}

type GeomHyperbola struct {
	geom *C.struct__geom_hyperbola_t
}

func (g *GeomHyperbola) Free() {
	C.geom_hyperbola_free(g.geom)
	g.geom = nil
}

func (g *GeomHyperbola) Copy() *GeomHyperbola {
	return &GeomHyperbola{geom: C.geom_hyperbola_copy(g.geom)}
}

type GeomParabola struct {
	geom *C.struct__geom_parabola_t
}

func (g *GeomParabola) Free() {
	C.geom_parabola_free(g.geom)
	g.geom = nil
}

func (g *GeomParabola) Copy() *GeomParabola {
	return &GeomParabola{geom: C.geom_parabola_copy(g.geom)}
}

type GeomLine struct {
	geom *C.struct__geom_line_t
}

func (g *GeomLine) Free() {
	C.geom_line_free(g.geom)
	g.geom = nil
}

func (g *GeomLine) Copy() *GeomLine {
	return &GeomLine{geom: C.geom_line_copy(g.geom)}
}

type GeomOffsetCurve struct {
	geom *C.struct__geom_offset_curve_t
}

func (g *GeomOffsetCurve) Free() {
	C.geom_offset_curve_free(g.geom)
	g.geom = nil
}

func (g *GeomOffsetCurve) Copy() *GeomOffsetCurve {
	return &GeomOffsetCurve{geom: C.geom_offset_curve_copy(g.geom)}
}

type GeomPoint struct {
	geom *C.struct__geom_point_t
}

func (g *GeomPoint) Free() {
	C.geom_point_free(g.geom)
	g.geom = nil
}

func (g *GeomPoint) Copy() *GeomPoint {
	return &GeomPoint{geom: C.geom_point_copy(g.geom)}
}

type GeomCartesianPoint struct {
	geom *C.struct__geom_cartesian_point_t
}

func (g *GeomCartesianPoint) Free() {
	C.geom_cartesian_point_free(g.geom)
	g.geom = nil
}

func (g *GeomCartesianPoint) Copy() *GeomCartesianPoint {
	return &GeomCartesianPoint{geom: C.geom_cartesian_point_copy(g.geom)}
}

type GeomSurface struct {
	geom *C.struct__geom_surface_t
}

func (g *GeomSurface) Free() {
	C.geom_surface_free(g.geom)
	g.geom = nil
}

func (g *GeomSurface) Copy() *GeomSurface {
	return &GeomSurface{geom: C.geom_surface_copy(g.geom)}
}

type GeomBoundedSurface struct {
	geom *C.struct__geom_bounded_surface_t
}

func (g *GeomBoundedSurface) Free() {
	C.geom_bounded_surface_free(g.geom)
	g.geom = nil
}

func (g *GeomBoundedSurface) Copy() *GeomBoundedSurface {
	return &GeomBoundedSurface{geom: C.geom_bounded_surface_copy(g.geom)}
}

type GeomBezierSurface struct {
	geom *C.struct__geom_bezier_surface_t
}

func (g *GeomBezierSurface) Free() {
	C.geom_bezier_surface_free(g.geom)
	g.geom = nil
}

func (g *GeomBezierSurface) Copy() *GeomBezierSurface {
	return &GeomBezierSurface{geom: C.geom_bezier_surface_copy(g.geom)}
}

type GeomBSplineSurface struct {
	geom *C.struct__geom_bspline_surface_t
}

func (g *GeomBSplineSurface) Free() {
	C.geom_bspline_surface_free(g.geom)
	g.geom = nil
}

func (g *GeomBSplineSurface) Copy() *GeomBSplineSurface {
	return &GeomBSplineSurface{geom: C.geom_bspline_surface_copy(g.geom)}
}

type GeomRectangularTrimmedSurface struct {
	geom *C.struct__geom_rectangular_trimmed_surface_t
}

func (g *GeomRectangularTrimmedSurface) Free() {
	C.geom_rectangular_trimmed_surface_free(g.geom)
	g.geom = nil
}

func (g *GeomRectangularTrimmedSurface) Copy() *GeomRectangularTrimmedSurface {
	return &GeomRectangularTrimmedSurface{geom: C.geom_rectangular_trimmed_surface_copy(g.geom)}
}

type GeomElementarySurface struct {
	geom *C.struct__geom_elementary_surface_t
}

func (g *GeomElementarySurface) Free() {
	C.geom_elementary_surface_free(g.geom)
	g.geom = nil
}

func (g *GeomElementarySurface) Copy() *GeomElementarySurface {
	return &GeomElementarySurface{geom: C.geom_elementary_surface_copy(g.geom)}
}

type GeomCylindricalSurface struct {
	geom *C.struct__geom_cylindrical_surface_t
}

func (g *GeomCylindricalSurface) Free() {
	C.geom_cylindrical_surface_free(g.geom)
	g.geom = nil
}

func (g *GeomCylindricalSurface) Copy() *GeomCylindricalSurface {
	return &GeomCylindricalSurface{geom: C.geom_cylindrical_surface_copy(g.geom)}
}

type GeomPlane struct {
	geom *C.struct__geom_plane_surface_t
}

func (g *GeomPlane) Free() {
	C.geom_plane_surface_free(g.geom)
	g.geom = nil
}

func (g *GeomPlane) Copy() *GeomPlane {
	return &GeomPlane{geom: C.geom_plane_surface_copy(g.geom)}
}

type GeomConicalSurface struct {
	geom *C.struct__geom_conical_surface_t
}

func (g *GeomConicalSurface) Free() {
	C.geom_conical_surface_free(g.geom)
	g.geom = nil
}

func (g *GeomConicalSurface) Copy() *GeomConicalSurface {
	return &GeomConicalSurface{geom: C.geom_conical_surface_copy(g.geom)}
}

type GeomSphericalSurface struct {
	geom *C.struct__geom_spherical_surface_t
}

func (g *GeomSphericalSurface) Free() {
	C.geom_spherical_surface_free(g.geom)
	g.geom = nil
}

func (g *GeomSphericalSurface) Copy() *GeomSphericalSurface {
	return &GeomSphericalSurface{geom: C.geom_spherical_surface_copy(g.geom)}
}

type GeomToroidalSurface struct {
	geom *C.struct__geom_toroidal_surface_t
}

func (g *GeomToroidalSurface) Free() {
	C.geom_toroidal_surface_free(g.geom)
	g.geom = nil
}

func (g *GeomToroidalSurface) Copy() *GeomToroidalSurface {
	return &GeomToroidalSurface{geom: C.geom_toroidal_surface_copy(g.geom)}
}

type GeomOffsetSurface struct {
	geom *C.struct__geom_offset_surface_t
}

func (g *GeomOffsetSurface) Free() {
	C.geom_offset_surface_free(g.geom)
	g.geom = nil
}

func (g *GeomOffsetSurface) Copy() *GeomOffsetSurface {
	return &GeomOffsetSurface{geom: C.geom_offset_surface_copy(g.geom)}
}

type GeomSweptSurface struct {
	geom *C.struct__geom_swept_surface_t
}

func (g *GeomSweptSurface) Free() {
	C.geom_swept_surface_free(g.geom)
	g.geom = nil
}

func (g *GeomSweptSurface) Copy() *GeomSweptSurface {
	return &GeomSweptSurface{geom: C.geom_swept_surface_copy(g.geom)}
}

type GeomSurfaceOfLinearExtrusion struct {
	geom *C.struct__geom_surface_of_linear_extrusion_t
}

func (g *GeomSurfaceOfLinearExtrusion) Free() {
	C.geom_surface_of_linear_extrusion_free(g.geom)
	g.geom = nil
}

func (g *GeomSurfaceOfLinearExtrusion) Copy() *GeomSurfaceOfLinearExtrusion {
	return &GeomSurfaceOfLinearExtrusion{geom: C.geom_surface_of_linear_extrusion_copy(g.geom)}
}

type GeomSurfaceOfRevolution struct {
	geom *C.struct__geom_surface_of_revolution_extrusion_t
}

func (g *GeomSurfaceOfRevolution) Free() {
	C.geom_surface_of_revolution_extrusion_free(g.geom)
	g.geom = nil
}

func (g *GeomSurfaceOfRevolution) Copy() *GeomSurfaceOfRevolution {
	return &GeomSurfaceOfRevolution{geom: C.geom_surface_of_revolution_extrusion_copy(g.geom)}
}

type GeomPlateSurface struct {
	geom *C.struct__geom_plate_surface_t
}

func (g *GeomPlateSurface) Free() {
	C.geom_plate_surface_free(g.geom)
	g.geom = nil
}

func (g *GeomPlateSurface) Copy() *GeomPlateSurface {
	return &GeomPlateSurface{geom: C.geom_plate_surface_copy(g.geom)}
}

type GeomVector struct {
	geom *C.struct__geom_vector_t
}

func (g *GeomVector) Free() {
	C.geom_vector_free(g.geom)
	g.geom = nil
}

func (g *GeomVector) Copy() *GeomVector {
	return &GeomVector{geom: C.geom_vector_copy(g.geom)}
}

type GeomDirection struct {
	geom *C.struct__geom_direction_t
}

func (g *GeomDirection) Free() {
	C.geom_direction_free(g.geom)
	g.geom = nil
}

func (g *GeomDirection) Copy() *GeomDirection {
	return &GeomDirection{geom: C.geom_direction_copy(g.geom)}
}

type GeomVectorWithMagnitude struct {
	geom *C.struct__geom_vector_with_magnitude_t
}

func (g *GeomVectorWithMagnitude) Free() {
	C.geom_vector_with_magnitude_free(g.geom)
	g.geom = nil
}

func (g *GeomVectorWithMagnitude) Copy() *GeomVectorWithMagnitude {
	return &GeomVectorWithMagnitude{geom: C.geom_vector_with_magnitude_copy(g.geom)}
}

type Geom2dGeometry struct {
	geom *C.struct__geom2d_geometry_t
}

func (g *Geom2dGeometry) Free() {
	C.geom2d_geometry_free(g.geom)
	g.geom = nil
}

func (g *Geom2dGeometry) Copy() *Geom2dGeometry {
	return &Geom2dGeometry{geom: C.geom2d_geometry_copy(g.geom)}
}

type Geom2dTransformation struct {
	geom *C.struct__geom2d_transformation_t
}

func (g *Geom2dTransformation) Free() {
	C.geom2d_transformation_free(g.geom)
	g.geom = nil
}

func (g *Geom2dTransformation) Copy() *Geom2dTransformation {
	return &Geom2dTransformation{geom: C.geom2d_transformation_copy(g.geom)}
}

type Geom2dAxisPlacement struct {
	geom *C.struct__geom2d_axis_placement_t
}

func (g *Geom2dAxisPlacement) Free() {
	C.geom2d_axis_placement_free(g.geom)
	g.geom = nil
}

func (g *Geom2dAxisPlacement) Copy() *Geom2dAxisPlacement {
	return &Geom2dAxisPlacement{geom: C.geom2d_axis_placement_copy(g.geom)}
}

type Geom2dCurve struct {
	geom *C.struct__geom2d_curve_t
}

func (g *Geom2dCurve) Free() {
	C.geom2d_curve_free(g.geom)
	g.geom = nil
}

func (g *Geom2dCurve) Copy() *Geom2dCurve {
	return &Geom2dCurve{geom: C.geom2d_curve_copy(g.geom)}
}

type Geom2dBisectorCurve struct {
	geom *C.struct__geom2d_bisector_curve_t
}

func (g *Geom2dBisectorCurve) Free() {
	C.geom2d_bisector_curve_free(g.geom)
	g.geom = nil
}

func (g *Geom2dBisectorCurve) Copy() *Geom2dBisectorCurve {
	return &Geom2dBisectorCurve{geom: C.geom2d_bisector_curve_copy(g.geom)}
}

type Geom2dBisectorBisecAna struct {
	geom *C.struct__geom2d_bezier_bisec_ana_curve_t
}

func (g *Geom2dBisectorBisecAna) Free() {
	C.geom2d_bezier_bisec_ana_curve_free(g.geom)
	g.geom = nil
}

func (g *Geom2dBisectorBisecAna) Copy() *Geom2dBisectorBisecAna {
	return &Geom2dBisectorBisecAna{geom: C.geom2d_bezier_bisec_ana_curve_copy(g.geom)}
}

type Geom2dBisectorBisecCC struct {
	geom *C.struct__geom2d_bezier_bisec_cc_curve_t
}

func (g *Geom2dBisectorBisecCC) Free() {
	C.geom2d_bezier_bisec_cc_curve_free(g.geom)
	g.geom = nil
}

func (g *Geom2dBisectorBisecCC) Copy() *Geom2dBisectorBisecCC {
	return &Geom2dBisectorBisecCC{geom: C.geom2d_bezier_bisec_cc_curve_copy(g.geom)}
}

type Geom2dBisectorBisecPC struct {
	geom *C.struct__geom2d_bezier_bisec_pc_curve_t
}

func (g *Geom2dBisectorBisecPC) Free() {
	C.geom2d_bezier_bisec_pc_curve_free(g.geom)
	g.geom = nil
}

func (g *Geom2dBisectorBisecPC) Copy() *Geom2dBisectorBisecPC {
	return &Geom2dBisectorBisecPC{geom: C.geom2d_bezier_bisec_pc_curve_copy(g.geom)}
}

type Geom2dBoundedCurve struct {
	geom *C.struct__geom2d_bounded_curve_t
}

func (g *Geom2dBoundedCurve) Free() {
	C.geom2d_bounded_curve_free(g.geom)
	g.geom = nil
}

func (g *Geom2dBoundedCurve) Copy() *Geom2dBoundedCurve {
	return &Geom2dBoundedCurve{geom: C.geom2d_bounded_curve_copy(g.geom)}
}

type Geom2dBezierCurve struct {
	geom *C.struct__geom2d_bezier_curve_t
}

func (g *Geom2dBezierCurve) Free() {
	C.geom2d_bezier_curve_free(g.geom)
	g.geom = nil
}

func (g *Geom2dBezierCurve) Copy() *Geom2dBezierCurve {
	return &Geom2dBezierCurve{geom: C.geom2d_bezier_curve_copy(g.geom)}
}

type Geom2dBSplineCurve struct {
	geom *C.struct__geom2d_bspline_curve_t
}

func (g *Geom2dBSplineCurve) Free() {
	C.geom2d_bspline_curve_free(g.geom)
	g.geom = nil
}

func (g *Geom2dBSplineCurve) Copy() *Geom2dBSplineCurve {
	return &Geom2dBSplineCurve{geom: C.geom2d_bspline_curve_copy(g.geom)}
}

type Geom2dTrimmedCurve struct {
	geom *C.struct__geom2d_trimmed_curve_t
}

func (g *Geom2dTrimmedCurve) Free() {
	C.geom2d_trimmed_curve_free(g.geom)
	g.geom = nil
}

func (g *Geom2dTrimmedCurve) Copy() *Geom2dTrimmedCurve {
	return &Geom2dTrimmedCurve{geom: C.geom2d_trimmed_curve_copy(g.geom)}
}

type Geom2dConic struct {
	geom *C.struct__geom2d_conic_t
}

func (g *Geom2dConic) Free() {
	C.geom2d_conic_free(g.geom)
	g.geom = nil
}

func (g *Geom2dConic) Copy() *Geom2dConic {
	return &Geom2dConic{geom: C.geom2d_conic_copy(g.geom)}
}

type Geom2dCircle struct {
	geom *C.struct__geom2d_circle_t
}

func (g *Geom2dCircle) Free() {
	C.geom2d_circle_free(g.geom)
	g.geom = nil
}

func (g *Geom2dCircle) Copy() *Geom2dCircle {
	return &Geom2dCircle{geom: C.geom2d_circle_copy(g.geom)}
}

type Geom2dEllipse struct {
	geom *C.struct__geom2d_ellipse_t
}

func (g *Geom2dEllipse) Free() {
	C.geom2d_ellipse_free(g.geom)
	g.geom = nil
}

func (g *Geom2dEllipse) Copy() *Geom2dEllipse {
	return &Geom2dEllipse{geom: C.geom2d_ellipse_copy(g.geom)}
}

type Geom2dHyperbola struct {
	geom *C.struct__geom2d_hyperbola_t
}

func (g *Geom2dHyperbola) Free() {
	C.geom2d_hyperbola_free(g.geom)
	g.geom = nil
}

func (g *Geom2dHyperbola) Copy() *Geom2dHyperbola {
	return &Geom2dHyperbola{geom: C.geom2d_hyperbola_copy(g.geom)}
}

type Geom2dParabola struct {
	geom *C.struct__geom2d_parabola_t
}

func (g *Geom2dParabola) Free() {
	C.geom2d_parabola_free(g.geom)
	g.geom = nil
}

func (g *Geom2dParabola) Copy() *Geom2dParabola {
	return &Geom2dParabola{geom: C.geom2d_parabola_copy(g.geom)}
}

type Geom2dLine struct {
	geom *C.struct__geom2d_line_t
}

func (g *Geom2dLine) Free() {
	C.geom2d_line_free(g.geom)
	g.geom = nil
}

func (g *Geom2dLine) Copy() *Geom2dLine {
	return &Geom2dLine{geom: C.geom2d_line_copy(g.geom)}
}

type Geom2dOffsetCurve struct {
	geom *C.struct__geom2d_offset_curve_t
}

func (g *Geom2dOffsetCurve) Free() {
	C.geom2d_offset_curve_free(g.geom)
	g.geom = nil
}

func (g *Geom2dOffsetCurve) Copy() *Geom2dOffsetCurve {
	return &Geom2dOffsetCurve{geom: C.geom2d_offset_curve_copy(g.geom)}
}

type Geom2dPoint struct {
	geom *C.struct__geom2d_point_t
}

func (g *Geom2dPoint) Free() {
	C.geom2d_point_free(g.geom)
	g.geom = nil
}

func (g *Geom2dPoint) Copy() *Geom2dPoint {
	return &Geom2dPoint{geom: C.geom2d_point_copy(g.geom)}
}

type Geom2dCartesianPoint struct {
	geom *C.struct__geom2d_cartesian_point_t
}

func (g *Geom2dCartesianPoint) Free() {
	C.geom2d_cartesian_point_free(g.geom)
	g.geom = nil
}

func (g *Geom2dCartesianPoint) Copy() *Geom2dCartesianPoint {
	return &Geom2dCartesianPoint{geom: C.geom2d_cartesian_point_copy(g.geom)}
}

type Geom2dVector struct {
	geom *C.struct__geom2d_vector_t
}

func (g *Geom2dVector) Free() {
	C.geom2d_vector_free(g.geom)
	g.geom = nil
}

func (g *Geom2dVector) Copy() *Geom2dVector {
	return &Geom2dVector{geom: C.geom2d_vector_copy(g.geom)}
}

type Geom2dDirection struct {
	geom *C.struct__geom2d_direction_t
}

func (g *Geom2dDirection) Free() {
	C.geom2d_direction_free(g.geom)
	g.geom = nil
}

func (g *Geom2dDirection) Copy() *Geom2dDirection {
	return &Geom2dDirection{geom: C.geom2d_direction_copy(g.geom)}
}

type Geom2dVectorWithMagnitude struct {
	geom *C.struct__geom2d_vector_with_magnitude_t
}

func (g *Geom2dVectorWithMagnitude) Free() {
	C.geom2d_vector_with_magnitude_free(g.geom)
	g.geom = nil
}

func (g *Geom2dVectorWithMagnitude) Copy() *Geom2dVectorWithMagnitude {
	return &Geom2dVectorWithMagnitude{geom: C.geom2d_vector_with_magnitude_copy(g.geom)}
}
