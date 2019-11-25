package topo

/*
#include <stdlib.h>
#include "geometry_c_api.h"
#cgo CFLAGS: -I ./
#cgo linux CXXFLAGS: -I ./include/oce -I ./include/linux/oce -I ./
#cgo darwin CXXFLAGS: -I ./include/oce -I ./include/darwin/oce -I ./  -std=gnu++14
#cgo windows CXXFLAGS:  -I ./include/oce -I ./include/windows/oce -I ./
*/
import "C"

const (
	GEOMAXIS1PLACEMENT            = int(C.GeomAxis1Placement)
	GEOMAXIS2PLACEMENT            = int(C.GeomAxis2Placement)
	GEOMBSPLINECURVE              = int(C.GeomBSplineCurve)
	GEOMBSPLINESURFACE            = int(C.GeomBSplineSurface)
	GEOMBEZIERCURVE               = int(C.GeomBezierCurve)
	GEOMBEZIERSURFACE             = int(C.GeomBezierSurface)
	GEOMCARTESIANPOINT            = int(C.GeomCartesianPoint)
	GEOMCIRCLE                    = int(C.GeomCircle)
	GEOMCONICALSURFACE            = int(C.GeomConicalSurface)
	GEOMCYLINDRICALSURFACE        = int(C.GeomCylindricalSurface)
	GEOMDIRECTION                 = int(C.GeomDirection)
	GEOMELEMENTARYSURFACE         = int(C.GeomElementarySurface)
	GEOMELLIPSE                   = int(C.GeomEllipse)
	GEOMHYPERBOLA                 = int(C.GeomHyperbola)
	GEOMLINE                      = int(C.GeomLine)
	GEOMOFFSETCURVE               = int(C.GeomOffsetCurve)
	GEOMOFFSETSURFACE             = int(C.GeomOffsetSurface)
	GEOMPARABOLA                  = int(C.GeomParabola)
	GEOMPLANE                     = int(C.GeomPlane)
	GEOMRECTANGULARTRIMMEDSURFACE = int(C.GeomRectangularTrimmedSurface)
	GEOMSPHERICALSURFACE          = int(C.GeomSphericalSurface)
	GEOMSURFACEOFLINEAREXTRUSION  = int(C.GeomSurfaceOfLinearExtrusion)
	GEOMSURFACEOFREVOLUTION       = int(C.GeomSurfaceOfRevolution)
	GEOMSWEPTSURFACE              = int(C.GeomSweptSurface)
	GEOMTOROIDALSURFACE           = int(C.GeomToroidalSurface)
	GEOMTRIMMEDCURVE              = int(C.GeomTrimmedCurve)
	GEOMVECTORWITHMAGNITUDE       = int(C.GeomVectorWithMagnitude)
	GEOMPLATESURFACE              = int(C.GeomPlateSurface)
)

const (
	GEOM2DBISECTORBISECANA    = int(C.Geom2dBisectorBisecAna)
	GEOM2DBISECTORBISECCC     = int(C.Geom2dBisectorBisecCC)
	GEOM2DBISECTORBISECPC     = int(C.Geom2dBisectorBisecPC)
	GEOM2DAXISPLACEMENT       = int(C.Geom2dAxisPlacement)
	GEOM2DBSPLINECURVE        = int(C.Geom2dBSplineCurve)
	GEOM2DBEZIERCURVE         = int(C.Geom2dBezierCurve)
	GEOM2DBOUNDEDCURVE        = int(C.Geom2dBoundedCurve)
	GEOM2DCARTESIANPOINT      = int(C.Geom2dCartesianPoint)
	GEOM2DCIRCLE              = int(C.Geom2dCircle)
	GEOM2DCONIC               = int(C.Geom2dConic)
	GEOM2DDIRECTION           = int(C.Geom2dDirection)
	GEOM2DELLIPSE             = int(C.Geom2dEllipse)
	GEOM2DHYPERBOLA           = int(C.Geom2dHyperbola)
	GEOM2DLINE                = int(C.Geom2dLine)
	GEOM2DOFFSETCURVE         = int(C.Geom2dOffsetCurve)
	GEOM2DPARABOLA            = int(C.Geom2dParabola)
	GEOM2DTRIMMEDCURVE        = int(C.Geom2dTrimmedCurve)
	GEOM2DVECTORWITHMAGNITUDE = int(C.Geom2dVectorWithMagnitude)
	GEOM2DBISECTORCURVE       = int(C.Geom2dBisectorCurve)
)

type GeomGeometry struct {
	geom *C.struct__geom_geometry_t
}

func (g *GeomGeometry) Free() {
	C.geom_geometry_free(g.geom)
	g.geom = nil
}

func (g *GeomGeometry) Type() int {
	return int(C.geom_geometry_type(g.geom))
}

func (g *GeomGeometry) Copy() *GeomGeometry {
	return &GeomGeometry{geom: C.geom_geometry_copy(g.geom)}
}

func (g *GeomGeometry) MirrorWithPoint(p Point3) {
	C.geom_apply_mirror_with_point(g.geom, p.val)
}

func (g *GeomGeometry) MirrorWithAxis1(a Axis1) {
	C.geom_apply_mirror_with_axis1(g.geom, a.val)
}

func (g *GeomGeometry) MirrorWithAxis2(a Axis2) {
	C.geom_apply_mirror_with_axis2(g.geom, a.val)
}

func (g *GeomGeometry) Rotate(a Axis1, ang float64) {
	C.geom_apply_rotate(g.geom, a.val, C.double(ang))
}

func (g *GeomGeometry) Scale(p Point3, ang float64) {
	C.geom_apply_scale(g.geom, p.val, C.double(ang))
}

func (g *GeomGeometry) TranslateWithVector(v Vector3) {
	C.geom_apply_translate_with_vector(g.geom, v.val)
}

func (g *GeomGeometry) TranslateWithPoint(p1, p2 Point3) {
	C.geom_apply_translate_with_point(g.geom, p1.val, p2.val)
}

func (g *GeomGeometry) Transform(t Trsf) {
	C.geom_apply_transform(g.geom, t.val)
}

func (g *GeomGeometry) MirroredWithPoint(p Point3) *GeomGeometry {
	return &GeomGeometry{geom: C.geom_mirror_with_point(g.geom, p.val)}
}

func (g *GeomGeometry) MirroredWithAxis1(a Axis1) *GeomGeometry {
	return &GeomGeometry{geom: C.geom_mirror_with_axis1(g.geom, a.val)}
}

func (g *GeomGeometry) MirroredWithAxis2(a Axis2) *GeomGeometry {
	return &GeomGeometry{geom: C.geom_mirror_with_axis2(g.geom, a.val)}
}

func (g *GeomGeometry) Rotated(a Axis1, ang float64) *GeomGeometry {
	return &GeomGeometry{geom: C.geom_rotate(g.geom, a.val, C.double(ang))}
}

func (g *GeomGeometry) Scaled(p Point3, ang float64) *GeomGeometry {
	return &GeomGeometry{geom: C.geom_scale(g.geom, p.val, C.double(ang))}
}

func (g *GeomGeometry) TranslatedWithVector(v Vector3) *GeomGeometry {
	return &GeomGeometry{geom: C.geom_translate_with_vector(g.geom, v.val)}
}

func (g *GeomGeometry) TranslatedWithPoint(p1, p2 Point3) *GeomGeometry {
	return &GeomGeometry{geom: C.geom_translate_with_point(g.geom, p1.val, p2.val)}
}

func (g *GeomGeometry) Transformed(t Trsf) *GeomGeometry {
	return &GeomGeometry{geom: C.geom_transform(g.geom, t.val)}
}

func (g *GeomGeometry) AutoCast() interface{} {
	switch g.Type() {
	case GEOMAXIS1PLACEMENT:
		return NewGeomAxis1PlacementFromGeometry(g)
	case GEOMAXIS2PLACEMENT:
		return NewGeomAxis2PlacementFromGeometry(g)
	case GEOMBSPLINECURVE:
		return NewGeomBSplineCurveFromGeometry(g)
	case GEOMBSPLINESURFACE:
		return NewGeomBSplineSurfaceFromGeometry(g)
	case GEOMBEZIERCURVE:
		return NewGeomBezierCurveFromGeometry(g)
	case GEOMBEZIERSURFACE:
		return NewGeomBezierSurfaceFromGeometry(g)
	case GEOMCARTESIANPOINT:
		return NewGeomCartesianPointFromGeometry(g)
	case GEOMCIRCLE:
		return NewGeomCircleFromGeometry(g)
	case GEOMCONICALSURFACE:
		return NewGeomConicalSurfaceFromGeometry(g)
	case GEOMCYLINDRICALSURFACE:
		return NewGeomCylindricalSurfaceFromGeometry(g)
	case GEOMDIRECTION:
		return NewGeomDirectionFromGeometry(g)
	case GEOMELEMENTARYSURFACE:
		return NewGeomElementarySurfaceFromGeometry(g)
	case GEOMELLIPSE:
		return NewGeomEllipseFromGeometry(g)
	case GEOMHYPERBOLA:
		return NewGeomHyperbolaFromGeometry(g)
	case GEOMLINE:
		return NewGeomLineFromGeometry(g)
	case GEOMOFFSETCURVE:
		return NewGeomOffsetCurveFromGeometry(g)
	case GEOMOFFSETSURFACE:
		return NewGeomOffsetSurfaceFromGeometry(g)
	case GEOMPARABOLA:
		return NewGeomParabolaFromGeometry(g)
	case GEOMPLANE:
		return NewGeomPlaneFromGeometry(g)
	case GEOMRECTANGULARTRIMMEDSURFACE:
		return NewGeomRectangularTrimmedSurfaceFromGeometry(g)
	case GEOMSPHERICALSURFACE:
		return NewGeomSphericalSurfaceFromGeometry(g)
	case GEOMSURFACEOFLINEAREXTRUSION:
		return NewGeomSurfaceOfLinearExtrusionFromGeometry(g)
	case GEOMSURFACEOFREVOLUTION:
		return NewGeomSurfaceOfRevolutionFromGeometry(g)
	case GEOMSWEPTSURFACE:
		return NewGeomSweptSurfaceFromGeometry(g)
	case GEOMTOROIDALSURFACE:
		return NewGeomToroidalSurfaceFromGeometry(g)
	case GEOMTRIMMEDCURVE:
		return NewGeomTrimmedCurveFromGeometry(g)
	case GEOMVECTORWITHMAGNITUDE:
		return NewGeomVectorWithMagnitudeFromGeometry(g)
	case GEOMPLATESURFACE:
		return NewGeomPlateSurfaceFromGeometry(g)
	}
	return nil
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

func (g *GeomAxisPlacement) Geometry() *GeomGeometry {
	return &GeomGeometry{geom: C.geom_axis_placement_to_geometry(g.geom)}
}

func (g *GeomAxisPlacement) Free() {
	C.geom_axis_placement_free(g.geom)
	g.geom = nil
}

func (g *GeomAxisPlacement) Copy() *GeomAxisPlacement {
	return &GeomAxisPlacement{geom: C.geom_axis_placement_copy(g.geom)}
}

func NewGeomAxisPlacementFromGeometry(g *GeomGeometry) *GeomAxisPlacement {
	if p := C.geom_axis_placement_from_geometry(g.geom); p != nil {
		return &GeomAxisPlacement{geom: p}
	}
	return nil
}

type GeomAxis1Placement struct {
	geom *C.struct__geom_axis1_placement_t
}

func (g *GeomAxis1Placement) Geometry() *GeomGeometry {
	return &GeomGeometry{geom: C.geom_axis1_placement_to_geometry(g.geom)}
}

func (g *GeomAxis1Placement) Free() {
	C.geom_axis1_placement_free(g.geom)
	g.geom = nil
}

func (g *GeomAxis1Placement) Copy() *GeomAxis1Placement {
	return &GeomAxis1Placement{geom: C.geom_axis1_placement_copy(g.geom)}
}

func NewGeomAxis1PlacementFromGeometry(g *GeomGeometry) *GeomAxis1Placement {
	if p := C.geom_axis1_placement_from_geometry(g.geom); p != nil {
		return &GeomAxis1Placement{geom: p}
	}
	return nil
}

type GeomAxis2Placement struct {
	geom *C.struct__geom_axis2_placement_t
}

func (g *GeomAxis2Placement) Geometry() *GeomGeometry {
	return &GeomGeometry{geom: C.geom_axis2_placement_to_geometry(g.geom)}
}

func (g *GeomAxis2Placement) Free() {
	C.geom_axis2_placement_free(g.geom)
	g.geom = nil
}

func (g *GeomAxis2Placement) Copy() *GeomAxis2Placement {
	return &GeomAxis2Placement{geom: C.geom_axis2_placement_copy(g.geom)}
}

func NewGeomAxis2PlacementFromGeometry(g *GeomGeometry) *GeomAxis2Placement {
	if p := C.geom_axis2_placement_from_geometry(g.geom); p != nil {
		return &GeomAxis2Placement{geom: p}
	}
	return nil
}

type GeomCurve struct {
	geom *C.struct__geom_curve_t
}

func (g *GeomCurve) Geometry() *GeomGeometry {
	return &GeomGeometry{geom: C.geom_curve_to_geometry(g.geom)}
}

func (g *GeomCurve) Free() {
	C.geom_curve_free(g.geom)
	g.geom = nil
}

func (g *GeomCurve) Copy() *GeomCurve {
	return &GeomCurve{geom: C.geom_curve_copy(g.geom)}
}

func NewGeomCurveFromGeometry(g *GeomGeometry) *GeomCurve {
	if p := C.geom_curve_from_geometry(g.geom); p != nil {
		return &GeomCurve{geom: p}
	}
	return nil
}

type GeomBoundedCurve struct {
	geom *C.struct__geom_bounded_curve_t
}

func (g *GeomBoundedCurve) Curve() *GeomCurve {
	return &GeomCurve{geom: C.geom_bounded_curve_to_geom_curve(g.geom)}
}

func (g *GeomBoundedCurve) Geometry() *GeomGeometry {
	return &GeomGeometry{geom: C.geom_bounded_curve_to_geometry(g.geom)}
}

func (g *GeomBoundedCurve) Free() {
	C.geom_bounded_curve_free(g.geom)
	g.geom = nil
}

func (g *GeomBoundedCurve) Copy() *GeomBoundedCurve {
	return &GeomBoundedCurve{geom: C.geom_bounded_curve_copy(g.geom)}
}

func NewGeomBoundedCurveFromGeometry(g *GeomGeometry) *GeomBoundedCurve {
	if p := C.geom_bounded_curve_from_geometry(g.geom); p != nil {
		return &GeomBoundedCurve{geom: p}
	}
	return nil
}

type GeomBezierCurve struct {
	geom *C.struct__geom_bezier_curve_t
}

func (g *GeomBezierCurve) Curve() *GeomCurve {
	return &GeomCurve{geom: C.geom_bezier_curve_to_geom_curve(g.geom)}
}

func (g *GeomBezierCurve) Geometry() *GeomGeometry {
	return &GeomGeometry{geom: C.geom_bezier_curve_to_geometry(g.geom)}
}

func (g *GeomBezierCurve) Free() {
	C.geom_bezier_curve_free(g.geom)
	g.geom = nil
}

func (g *GeomBezierCurve) Copy() *GeomBezierCurve {
	return &GeomBezierCurve{geom: C.geom_bezier_curve_copy(g.geom)}
}

func NewGeomBezierCurveFromGeometry(g *GeomGeometry) *GeomBezierCurve {
	if p := C.geom_bezier_curve_from_geometry(g.geom); p != nil {
		return &GeomBezierCurve{geom: p}
	}
	return nil
}

type GeomBSplineCurve struct {
	geom *C.struct__geom_bspline_curve_t
}

func (g *GeomBSplineCurve) Curve() *GeomCurve {
	return &GeomCurve{geom: C.geom_bspline_curve_to_geom_curve(g.geom)}
}

func (g *GeomBSplineCurve) Geometry() *GeomGeometry {
	return &GeomGeometry{geom: C.geom_bspline_curve_to_geometry(g.geom)}
}

func (g *GeomBSplineCurve) Free() {
	C.geom_bspline_curve_free(g.geom)
	g.geom = nil
}

func (g *GeomBSplineCurve) Copy() *GeomBSplineCurve {
	return &GeomBSplineCurve{geom: C.geom_bspline_curve_copy(g.geom)}
}

func NewGeomBSplineCurveFromGeometry(g *GeomGeometry) *GeomBSplineCurve {
	if p := C.geom_bspline_curve_from_geometry(g.geom); p != nil {
		return &GeomBSplineCurve{geom: p}
	}
	return nil
}

type GeomTrimmedCurve struct {
	geom *C.struct__geom_trimmed_curve_t
}

func (g *GeomTrimmedCurve) Curve() *GeomCurve {
	return &GeomCurve{geom: C.geom_trimmed_curve_to_geom_curve(g.geom)}
}

func (g *GeomTrimmedCurve) Geometry() *GeomGeometry {
	return &GeomGeometry{geom: C.geom_trimmed_curve_to_geometry(g.geom)}
}

func (g *GeomTrimmedCurve) Free() {
	C.geom_trimmed_curve_free(g.geom)
	g.geom = nil
}

func (g *GeomTrimmedCurve) Copy() *GeomTrimmedCurve {
	return &GeomTrimmedCurve{geom: C.geom_trimmed_curve_copy(g.geom)}
}

func NewGeomTrimmedCurveFromGeometry(g *GeomGeometry) *GeomTrimmedCurve {
	if p := C.geom_trimmed_curve_from_geometry(g.geom); p != nil {
		return &GeomTrimmedCurve{geom: p}
	}
	return nil
}

type GeomConic struct {
	geom *C.struct__geom_conic_t
}

func (g *GeomConic) Curve() *GeomCurve {
	return &GeomCurve{geom: C.geom_conic_to_geom_curve(g.geom)}
}

func (g *GeomConic) Geometry() *GeomGeometry {
	return &GeomGeometry{geom: C.geom_conic_to_geometry(g.geom)}
}

func (g *GeomConic) Free() {
	C.geom_conic_free(g.geom)
	g.geom = nil
}

func (g *GeomConic) Copy() *GeomConic {
	return &GeomConic{geom: C.geom_conic_copy(g.geom)}
}

func NewGeomConicFromGeometry(g *GeomGeometry) *GeomConic {
	if p := C.geom_conic_from_geometry(g.geom); p != nil {
		return &GeomConic{geom: p}
	}
	return nil
}

type GeomCircle struct {
	geom *C.struct__geom_circle_t
}

func (g *GeomCircle) Curve() *GeomCurve {
	return &GeomCurve{geom: C.geom_circle_to_geom_curve(g.geom)}
}

func (g *GeomCircle) Geometry() *GeomGeometry {
	return &GeomGeometry{geom: C.geom_circle_to_geometry(g.geom)}
}

func (g *GeomCircle) Free() {
	C.geom_circle_free(g.geom)
	g.geom = nil
}

func (g *GeomCircle) Copy() *GeomCircle {
	return &GeomCircle{geom: C.geom_circle_copy(g.geom)}
}

func NewGeomCircleFromGeometry(g *GeomGeometry) *GeomCircle {
	if p := C.geom_circle_from_geometry(g.geom); p != nil {
		return &GeomCircle{geom: p}
	}
	return nil
}

type GeomEllipse struct {
	geom *C.struct__geom_ellipse_t
}

func (g *GeomEllipse) Curve() *GeomCurve {
	return &GeomCurve{geom: C.geom_ellipse_to_geom_curve(g.geom)}
}

func (g *GeomEllipse) Geometry() *GeomGeometry {
	return &GeomGeometry{geom: C.geom_ellipse_to_geometry(g.geom)}
}

func (g *GeomEllipse) Free() {
	C.geom_ellipse_free(g.geom)
	g.geom = nil
}

func (g *GeomEllipse) Copy() *GeomEllipse {
	return &GeomEllipse{geom: C.geom_ellipse_copy(g.geom)}
}

func NewGeomEllipseFromGeometry(g *GeomGeometry) *GeomEllipse {
	if p := C.geom_ellipse_from_geometry(g.geom); p != nil {
		return &GeomEllipse{geom: p}
	}
	return nil
}

type GeomHyperbola struct {
	geom *C.struct__geom_hyperbola_t
}

func (g *GeomHyperbola) Curve() *GeomCurve {
	return &GeomCurve{geom: C.geom_hyperbola_to_geom_curve(g.geom)}
}

func (g *GeomHyperbola) Geometry() *GeomGeometry {
	return &GeomGeometry{geom: C.geom_hyperbola_to_geometry(g.geom)}
}

func (g *GeomHyperbola) Free() {
	C.geom_hyperbola_free(g.geom)
	g.geom = nil
}

func (g *GeomHyperbola) Copy() *GeomHyperbola {
	return &GeomHyperbola{geom: C.geom_hyperbola_copy(g.geom)}
}

func NewGeomHyperbolaFromGeometry(g *GeomGeometry) *GeomHyperbola {
	if p := C.geom_hyperbola_from_geometry(g.geom); p != nil {
		return &GeomHyperbola{geom: p}
	}
	return nil
}

type GeomParabola struct {
	geom *C.struct__geom_parabola_t
}

func (g *GeomParabola) Curve() *GeomCurve {
	return &GeomCurve{geom: C.geom_parabola_to_geom_curve(g.geom)}
}

func (g *GeomParabola) Geometry() *GeomGeometry {
	return &GeomGeometry{geom: C.geom_parabola_to_geometry(g.geom)}
}

func (g *GeomParabola) Free() {
	C.geom_parabola_free(g.geom)
	g.geom = nil
}

func (g *GeomParabola) Copy() *GeomParabola {
	return &GeomParabola{geom: C.geom_parabola_copy(g.geom)}
}

func NewGeomParabolaFromGeometry(g *GeomGeometry) *GeomParabola {
	if p := C.geom_parabola_from_geometry(g.geom); p != nil {
		return &GeomParabola{geom: p}
	}
	return nil
}

type GeomLine struct {
	geom *C.struct__geom_line_t
}

func (g *GeomLine) Curve() *GeomCurve {
	return &GeomCurve{geom: C.geom_line_to_geom_curve(g.geom)}
}

func (g *GeomLine) Geometry() *GeomGeometry {
	return &GeomGeometry{geom: C.geom_line_to_geometry(g.geom)}
}

func (g *GeomLine) Free() {
	C.geom_line_free(g.geom)
	g.geom = nil
}

func (g *GeomLine) Copy() *GeomLine {
	return &GeomLine{geom: C.geom_line_copy(g.geom)}
}

func NewGeomLineFromGeometry(g *GeomGeometry) *GeomLine {
	if p := C.geom_line_from_geometry(g.geom); p != nil {
		return &GeomLine{geom: p}
	}
	return nil
}

type GeomOffsetCurve struct {
	geom *C.struct__geom_offset_curve_t
}

func (g *GeomOffsetCurve) Curve() *GeomCurve {
	return &GeomCurve{geom: C.geom_offset_curve_to_geom_curve(g.geom)}
}

func (g *GeomOffsetCurve) Geometry() *GeomGeometry {
	return &GeomGeometry{geom: C.geom_offset_curve_to_geometry(g.geom)}
}

func (g *GeomOffsetCurve) Free() {
	C.geom_offset_curve_free(g.geom)
	g.geom = nil
}

func (g *GeomOffsetCurve) Copy() *GeomOffsetCurve {
	return &GeomOffsetCurve{geom: C.geom_offset_curve_copy(g.geom)}
}

func NewGeomOffsetCurveFromGeometry(g *GeomGeometry) *GeomOffsetCurve {
	if p := C.geom_offset_curve_from_geometry(g.geom); p != nil {
		return &GeomOffsetCurve{geom: p}
	}
	return nil
}

type GeomPoint struct {
	geom *C.struct__geom_point_t
}

func (g *GeomPoint) Geometry() *GeomGeometry {
	return &GeomGeometry{geom: C.geom_point_to_geometry(g.geom)}
}

func (g *GeomPoint) Free() {
	C.geom_point_free(g.geom)
	g.geom = nil
}

func (g *GeomPoint) Copy() *GeomPoint {
	return &GeomPoint{geom: C.geom_point_copy(g.geom)}
}

func NewGeomPointFromGeometry(g *GeomGeometry) *GeomPoint {
	if p := C.geom_point_from_geometry(g.geom); p != nil {
		return &GeomPoint{geom: p}
	}
	return nil
}

type GeomCartesianPoint struct {
	geom *C.struct__geom_cartesian_point_t
}

func (g *GeomCartesianPoint) Geometry() *GeomGeometry {
	return &GeomGeometry{geom: C.geom_cartesian_point_to_geometry(g.geom)}
}

func (g *GeomCartesianPoint) Free() {
	C.geom_cartesian_point_free(g.geom)
	g.geom = nil
}

func (g *GeomCartesianPoint) Copy() *GeomCartesianPoint {
	return &GeomCartesianPoint{geom: C.geom_cartesian_point_copy(g.geom)}
}

func NewGeomCartesianPointFromGeometry(g *GeomGeometry) *GeomCartesianPoint {
	if p := C.geom_cartesian_point_from_geometry(g.geom); p != nil {
		return &GeomCartesianPoint{geom: p}
	}
	return nil
}

type GeomSurface struct {
	geom *C.struct__geom_surface_t
}

func (g *GeomSurface) Geometry() *GeomGeometry {
	return &GeomGeometry{geom: C.geom_surface_to_geometry(g.geom)}
}

func (g *GeomSurface) Free() {
	C.geom_surface_free(g.geom)
	g.geom = nil
}

func (g *GeomSurface) Copy() *GeomSurface {
	return &GeomSurface{geom: C.geom_surface_copy(g.geom)}
}

func NewGeomSurfaceFromGeometry(g *GeomGeometry) *GeomSurface {
	if p := C.geom_surface_from_geometry(g.geom); p != nil {
		return &GeomSurface{geom: p}
	}
	return nil
}

type GeomBoundedSurface struct {
	geom *C.struct__geom_bounded_surface_t
}

func (g *GeomBoundedSurface) Surface() *GeomSurface {
	return &GeomSurface{geom: C.geom_bounded_surface_to_geom_surface(g.geom)}
}

func (g *GeomBoundedSurface) Geometry() *GeomGeometry {
	return &GeomGeometry{geom: C.geom_bounded_surface_to_geometry(g.geom)}
}

func (g *GeomBoundedSurface) Free() {
	C.geom_bounded_surface_free(g.geom)
	g.geom = nil
}

func (g *GeomBoundedSurface) Copy() *GeomBoundedSurface {
	return &GeomBoundedSurface{geom: C.geom_bounded_surface_copy(g.geom)}
}

func NewGeomBoundedSurfaceFromGeometry(g *GeomGeometry) *GeomBoundedSurface {
	if p := C.geom_bounded_surface_from_geometry(g.geom); p != nil {
		return &GeomBoundedSurface{geom: p}
	}
	return nil
}

type GeomBezierSurface struct {
	geom *C.struct__geom_bezier_surface_t
}

func (g *GeomBezierSurface) Surface() *GeomSurface {
	return &GeomSurface{geom: C.geom_bezier_surface_to_geom_surface(g.geom)}
}

func (g *GeomBezierSurface) Geometry() *GeomGeometry {
	return &GeomGeometry{geom: C.geom_bezier_surface_to_geometry(g.geom)}
}

func (g *GeomBezierSurface) Free() {
	C.geom_bezier_surface_free(g.geom)
	g.geom = nil
}

func (g *GeomBezierSurface) Copy() *GeomBezierSurface {
	return &GeomBezierSurface{geom: C.geom_bezier_surface_copy(g.geom)}
}

func NewGeomBezierSurfaceFromGeometry(g *GeomGeometry) *GeomBezierSurface {
	if p := C.geom_bezier_surface_from_geometry(g.geom); p != nil {
		return &GeomBezierSurface{geom: p}
	}
	return nil
}

type GeomBSplineSurface struct {
	geom *C.struct__geom_bspline_surface_t
}

func (g *GeomBSplineSurface) Surface() *GeomSurface {
	return &GeomSurface{geom: C.geom_bspline_surface_to_geom_surface(g.geom)}
}

func (g *GeomBSplineSurface) Geometry() *GeomGeometry {
	return &GeomGeometry{geom: C.geom_bspline_surface_to_geometry(g.geom)}
}

func (g *GeomBSplineSurface) Free() {
	C.geom_bspline_surface_free(g.geom)
	g.geom = nil
}

func (g *GeomBSplineSurface) Copy() *GeomBSplineSurface {
	return &GeomBSplineSurface{geom: C.geom_bspline_surface_copy(g.geom)}
}

func NewGeomBSplineSurfaceFromGeometry(g *GeomGeometry) *GeomBSplineSurface {
	if p := C.geom_bspline_surface_from_geometry(g.geom); p != nil {
		return &GeomBSplineSurface{geom: p}
	}
	return nil
}

type GeomRectangularTrimmedSurface struct {
	geom *C.struct__geom_rectangular_trimmed_surface_t
}

func (g *GeomRectangularTrimmedSurface) Surface() *GeomSurface {
	return &GeomSurface{geom: C.geom_rectangular_trimmed_surface_to_geom_surface(g.geom)}
}

func (g *GeomRectangularTrimmedSurface) Geometry() *GeomGeometry {
	return &GeomGeometry{geom: C.geom_rectangular_trimmed_surface_to_geometry(g.geom)}
}

func (g *GeomRectangularTrimmedSurface) Free() {
	C.geom_rectangular_trimmed_surface_free(g.geom)
	g.geom = nil
}

func (g *GeomRectangularTrimmedSurface) Copy() *GeomRectangularTrimmedSurface {
	return &GeomRectangularTrimmedSurface{geom: C.geom_rectangular_trimmed_surface_copy(g.geom)}
}

func NewGeomRectangularTrimmedSurfaceFromGeometry(g *GeomGeometry) *GeomRectangularTrimmedSurface {
	if p := C.geom_rectangular_trimmed_surface_from_geometry(g.geom); p != nil {
		return &GeomRectangularTrimmedSurface{geom: p}
	}
	return nil
}

type GeomElementarySurface struct {
	geom *C.struct__geom_elementary_surface_t
}

func (g *GeomElementarySurface) Surface() *GeomSurface {
	return &GeomSurface{geom: C.geom_elementary_surface_to_geom_surface(g.geom)}
}

func (g *GeomElementarySurface) Geometry() *GeomGeometry {
	return &GeomGeometry{geom: C.geom_elementary_surface_to_geometry(g.geom)}
}

func (g *GeomElementarySurface) Free() {
	C.geom_elementary_surface_free(g.geom)
	g.geom = nil
}

func (g *GeomElementarySurface) Copy() *GeomElementarySurface {
	return &GeomElementarySurface{geom: C.geom_elementary_surface_copy(g.geom)}
}

func NewGeomElementarySurfaceFromGeometry(g *GeomGeometry) *GeomElementarySurface {
	if p := C.geom_elementary_surface_from_geometry(g.geom); p != nil {
		return &GeomElementarySurface{geom: p}
	}
	return nil
}

type GeomCylindricalSurface struct {
	geom *C.struct__geom_cylindrical_surface_t
}

func (g *GeomCylindricalSurface) Surface() *GeomSurface {
	return &GeomSurface{geom: C.geom_cylindrical_surface_to_geom_surface(g.geom)}
}

func (g *GeomCylindricalSurface) Geometry() *GeomGeometry {
	return &GeomGeometry{geom: C.geom_cylindrical_surface_to_geometry(g.geom)}
}

func (g *GeomCylindricalSurface) Free() {
	C.geom_cylindrical_surface_free(g.geom)
	g.geom = nil
}

func (g *GeomCylindricalSurface) Copy() *GeomCylindricalSurface {
	return &GeomCylindricalSurface{geom: C.geom_cylindrical_surface_copy(g.geom)}
}

func NewGeomCylindricalSurfaceFromGeometry(g *GeomGeometry) *GeomCylindricalSurface {
	if p := C.geom_cylindrical_surface_from_geometry(g.geom); p != nil {
		return &GeomCylindricalSurface{geom: p}
	}
	return nil
}

type GeomPlane struct {
	geom *C.struct__geom_plane_surface_t
}

func (g *GeomPlane) Surface() *GeomSurface {
	return &GeomSurface{geom: C.geom_plane_surface_to_geom_surface(g.geom)}
}

func (g *GeomPlane) Geometry() *GeomGeometry {
	return &GeomGeometry{geom: C.geom_plane_surface_to_geometry(g.geom)}
}

func (g *GeomPlane) Free() {
	C.geom_plane_surface_free(g.geom)
	g.geom = nil
}

func (g *GeomPlane) Copy() *GeomPlane {
	return &GeomPlane{geom: C.geom_plane_surface_copy(g.geom)}
}

func NewGeomPlaneFromGeometry(g *GeomGeometry) *GeomPlane {
	if p := C.geom_plane_surface_from_geometry(g.geom); p != nil {
		return &GeomPlane{geom: p}
	}
	return nil
}

type GeomConicalSurface struct {
	geom *C.struct__geom_conical_surface_t
}

func (g *GeomConicalSurface) Surface() *GeomSurface {
	return &GeomSurface{geom: C.geom_conical_surface_to_geom_surface(g.geom)}
}

func (g *GeomConicalSurface) Geometry() *GeomGeometry {
	return &GeomGeometry{geom: C.geom_conical_surface_to_geometry(g.geom)}
}

func (g *GeomConicalSurface) Free() {
	C.geom_conical_surface_free(g.geom)
	g.geom = nil
}

func (g *GeomConicalSurface) Copy() *GeomConicalSurface {
	return &GeomConicalSurface{geom: C.geom_conical_surface_copy(g.geom)}
}

func NewGeomConicalSurfaceFromGeometry(g *GeomGeometry) *GeomConicalSurface {
	if p := C.geom_conical_surface_from_geometry(g.geom); p != nil {
		return &GeomConicalSurface{geom: p}
	}
	return nil
}

type GeomSphericalSurface struct {
	geom *C.struct__geom_spherical_surface_t
}

func (g *GeomSphericalSurface) Surface() *GeomSurface {
	return &GeomSurface{geom: C.geom_spherical_surface_to_geom_surface(g.geom)}
}

func (g *GeomSphericalSurface) Geometry() *GeomGeometry {
	return &GeomGeometry{geom: C.geom_spherical_surface_to_geometry(g.geom)}
}

func (g *GeomSphericalSurface) Free() {
	C.geom_spherical_surface_free(g.geom)
	g.geom = nil
}

func (g *GeomSphericalSurface) Copy() *GeomSphericalSurface {
	return &GeomSphericalSurface{geom: C.geom_spherical_surface_copy(g.geom)}
}

func NewGeomSphericalSurfaceFromGeometry(g *GeomGeometry) *GeomSphericalSurface {
	if p := C.geom_spherical_surface_from_geometry(g.geom); p != nil {
		return &GeomSphericalSurface{geom: p}
	}
	return nil
}

type GeomToroidalSurface struct {
	geom *C.struct__geom_toroidal_surface_t
}

func (g *GeomToroidalSurface) Surface() *GeomSurface {
	return &GeomSurface{geom: C.geom_toroidal_surface_to_geom_surface(g.geom)}
}

func (g *GeomToroidalSurface) Geometry() *GeomGeometry {
	return &GeomGeometry{geom: C.geom_toroidal_surface_to_geometry(g.geom)}
}

func (g *GeomToroidalSurface) Free() {
	C.geom_toroidal_surface_free(g.geom)
	g.geom = nil
}

func (g *GeomToroidalSurface) Copy() *GeomToroidalSurface {
	return &GeomToroidalSurface{geom: C.geom_toroidal_surface_copy(g.geom)}
}

func NewGeomToroidalSurfaceFromGeometry(g *GeomGeometry) *GeomToroidalSurface {
	if p := C.geom_toroidal_surface_from_geometry(g.geom); p != nil {
		return &GeomToroidalSurface{geom: p}
	}
	return nil
}

type GeomOffsetSurface struct {
	geom *C.struct__geom_offset_surface_t
}

func (g *GeomOffsetSurface) Surface() *GeomSurface {
	return &GeomSurface{geom: C.geom_offset_surface_to_geom_surface(g.geom)}
}

func (g *GeomOffsetSurface) Geometry() *GeomGeometry {
	return &GeomGeometry{geom: C.geom_offset_surface_to_geometry(g.geom)}
}

func (g *GeomOffsetSurface) Free() {
	C.geom_offset_surface_free(g.geom)
	g.geom = nil
}

func (g *GeomOffsetSurface) Copy() *GeomOffsetSurface {
	return &GeomOffsetSurface{geom: C.geom_offset_surface_copy(g.geom)}
}

func NewGeomOffsetSurfaceFromGeometry(g *GeomGeometry) *GeomOffsetSurface {
	if p := C.geom_offset_surface_from_geometry(g.geom); p != nil {
		return &GeomOffsetSurface{geom: p}
	}
	return nil
}

type GeomSweptSurface struct {
	geom *C.struct__geom_swept_surface_t
}

func (g *GeomSweptSurface) Surface() *GeomSurface {
	return &GeomSurface{geom: C.geom_swept_surface_to_geom_surface(g.geom)}
}

func (g *GeomSweptSurface) Geometry() *GeomGeometry {
	return &GeomGeometry{geom: C.geom_swept_surface_to_geometry(g.geom)}
}

func (g *GeomSweptSurface) Free() {
	C.geom_swept_surface_free(g.geom)
	g.geom = nil
}

func (g *GeomSweptSurface) Copy() *GeomSweptSurface {
	return &GeomSweptSurface{geom: C.geom_swept_surface_copy(g.geom)}
}

func NewGeomSweptSurfaceFromGeometry(g *GeomGeometry) *GeomSweptSurface {
	if p := C.geom_swept_surface_from_geometry(g.geom); p != nil {
		return &GeomSweptSurface{geom: p}
	}
	return nil
}

type GeomSurfaceOfLinearExtrusion struct {
	geom *C.struct__geom_surface_of_linear_extrusion_t
}

func (g *GeomSurfaceOfLinearExtrusion) Surface() *GeomSurface {
	return &GeomSurface{geom: C.geom_surface_of_linear_extrusion_to_geom_surface(g.geom)}
}

func (g *GeomSurfaceOfLinearExtrusion) Geometry() *GeomGeometry {
	return &GeomGeometry{geom: C.geom_surface_of_linear_extrusion_to_geometry(g.geom)}
}

func (g *GeomSurfaceOfLinearExtrusion) Free() {
	C.geom_surface_of_linear_extrusion_free(g.geom)
	g.geom = nil
}

func (g *GeomSurfaceOfLinearExtrusion) Copy() *GeomSurfaceOfLinearExtrusion {
	return &GeomSurfaceOfLinearExtrusion{geom: C.geom_surface_of_linear_extrusion_copy(g.geom)}
}

func NewGeomSurfaceOfLinearExtrusionFromGeometry(g *GeomGeometry) *GeomSurfaceOfLinearExtrusion {
	if p := C.geom_surface_of_linear_extrusion_from_geometry(g.geom); p != nil {
		return &GeomSurfaceOfLinearExtrusion{geom: p}
	}
	return nil
}

type GeomSurfaceOfRevolution struct {
	geom *C.struct__geom_surface_of_revolution_extrusion_t
}

func (g *GeomSurfaceOfRevolution) Surface() *GeomSurface {
	return &GeomSurface{geom: C.geom_surface_of_revolution_extrusion_to_geom_surface(g.geom)}
}

func (g *GeomSurfaceOfRevolution) Geometry() *GeomGeometry {
	return &GeomGeometry{geom: C.geom_surface_of_revolution_extrusion_to_geometry(g.geom)}
}

func (g *GeomSurfaceOfRevolution) Free() {
	C.geom_surface_of_revolution_extrusion_free(g.geom)
	g.geom = nil
}

func (g *GeomSurfaceOfRevolution) Copy() *GeomSurfaceOfRevolution {
	return &GeomSurfaceOfRevolution{geom: C.geom_surface_of_revolution_extrusion_copy(g.geom)}
}

func NewGeomSurfaceOfRevolutionFromGeometry(g *GeomGeometry) *GeomSurfaceOfRevolution {
	if p := C.geom_surface_of_revolution_extrusion_from_geometry(g.geom); p != nil {
		return &GeomSurfaceOfRevolution{geom: p}
	}
	return nil
}

type GeomPlateSurface struct {
	geom *C.struct__geom_plate_surface_t
}

func (g *GeomPlateSurface) Surface() *GeomSurface {
	return &GeomSurface{geom: C.geom_plate_surface_to_geom_surface(g.geom)}
}

func (g *GeomPlateSurface) Geometry() *GeomGeometry {
	return &GeomGeometry{geom: C.geom_plate_surface_to_geometry(g.geom)}
}

func (g *GeomPlateSurface) Free() {
	C.geom_plate_surface_free(g.geom)
	g.geom = nil
}

func (g *GeomPlateSurface) Copy() *GeomPlateSurface {
	return &GeomPlateSurface{geom: C.geom_plate_surface_copy(g.geom)}
}

func NewGeomPlateSurfaceFromGeometry(g *GeomGeometry) *GeomPlateSurface {
	if p := C.geom_plate_surface_from_geometry(g.geom); p != nil {
		return &GeomPlateSurface{geom: p}
	}
	return nil
}

type GeomVector struct {
	geom *C.struct__geom_vector_t
}

func (g *GeomVector) Geometry() *GeomGeometry {
	return &GeomGeometry{geom: C.geom_vector_to_geometry(g.geom)}
}

func (g *GeomVector) Free() {
	C.geom_vector_free(g.geom)
	g.geom = nil
}

func (g *GeomVector) Copy() *GeomVector {
	return &GeomVector{geom: C.geom_vector_copy(g.geom)}
}

func NewGeomVectorFromGeometry(g *GeomGeometry) *GeomVector {
	if p := C.geom_vector_from_geometry(g.geom); p != nil {
		return &GeomVector{geom: p}
	}
	return nil
}

type GeomDirection struct {
	geom *C.struct__geom_direction_t
}

func (g *GeomDirection) Geometry() *GeomGeometry {
	return &GeomGeometry{geom: C.geom_direction_to_geometry(g.geom)}
}

func (g *GeomDirection) Free() {
	C.geom_direction_free(g.geom)
	g.geom = nil
}

func (g *GeomDirection) Copy() *GeomDirection {
	return &GeomDirection{geom: C.geom_direction_copy(g.geom)}
}

func NewGeomDirectionFromGeometry(g *GeomGeometry) *GeomDirection {
	if p := C.geom_direction_from_geometry(g.geom); p != nil {
		return &GeomDirection{geom: p}
	}
	return nil
}

type GeomVectorWithMagnitude struct {
	geom *C.struct__geom_vector_with_magnitude_t
}

func (g *GeomVectorWithMagnitude) Geometry() *GeomGeometry {
	return &GeomGeometry{geom: C.geom_vector_with_magnitude_to_geometry(g.geom)}
}

func (g *GeomVectorWithMagnitude) Free() {
	C.geom_vector_with_magnitude_free(g.geom)
	g.geom = nil
}

func (g *GeomVectorWithMagnitude) Copy() *GeomVectorWithMagnitude {
	return &GeomVectorWithMagnitude{geom: C.geom_vector_with_magnitude_copy(g.geom)}
}

func NewGeomVectorWithMagnitudeFromGeometry(g *GeomGeometry) *GeomVectorWithMagnitude {
	if p := C.geom_vector_with_magnitude_from_geometry(g.geom); p != nil {
		return &GeomVectorWithMagnitude{geom: p}
	}
	return nil
}

type Geom2dGeometry struct {
	geom *C.struct__geom2d_geometry_t
}

func (g *Geom2dGeometry) Type() int {
	return int(C.geom2d_geometry_type(g.geom))
}

func (g *Geom2dGeometry) Free() {
	C.geom2d_geometry_free(g.geom)
	g.geom = nil
}

func (g *Geom2dGeometry) Copy() *Geom2dGeometry {
	return &Geom2dGeometry{geom: C.geom2d_geometry_copy(g.geom)}
}

func (g *Geom2dGeometry) MirrorWithPoint(p Point2) {
	C.geom2d_apply_mirror_with_point(g.geom, p.val)
}

func (g *Geom2dGeometry) MirrorWithAxis2d(p Axis2d) {
	C.geom2d_apply_mirror_with_axis2(g.geom, p.val)
}

func (g *Geom2dGeometry) Rotate(p Point2, ang float64) {
	C.geom2d_apply_rotate(g.geom, p.val, C.double(ang))
}

func (g *Geom2dGeometry) Scale(p Point2, s float64) {
	C.geom2d_apply_scale(g.geom, p.val, C.double(s))
}

func (g *Geom2dGeometry) TranslateWithVector(p Vector2) {
	C.geom2d_apply_translate_with_vector(g.geom, p.val)
}

func (g *Geom2dGeometry) TranslateWithPoint(p1, p2 Point2) {
	C.geom2d_apply_translate_with_point(g.geom, p1.val, p2.val)
}

func (g *Geom2dGeometry) Transform(t Trsf2d) {
	C.geom2d_apply_transform(g.geom, t.val)
}

func (g *Geom2dGeometry) MirroredWithPoint(p Point2) *Geom2dGeometry {
	return &Geom2dGeometry{geom: C.geom2d_mirror_with_point(g.geom, p.val)}
}

func (g *Geom2dGeometry) MirroredWithAxis2d(p Axis2d) *Geom2dGeometry {
	return &Geom2dGeometry{geom: C.geom2d_mirror_with_axis2(g.geom, p.val)}
}

func (g *Geom2dGeometry) Rotated(p Point2, ang float64) *Geom2dGeometry {
	return &Geom2dGeometry{geom: C.geom2d_rotate(g.geom, p.val, C.double(ang))}
}

func (g *Geom2dGeometry) Scaled(p Point2, s float64) *Geom2dGeometry {
	return &Geom2dGeometry{geom: C.geom2d_scale(g.geom, p.val, C.double(s))}
}

func (g *Geom2dGeometry) TranslatedWithVector(p Vector2) *Geom2dGeometry {
	return &Geom2dGeometry{geom: C.geom2d_translate_with_vector(g.geom, p.val)}
}

func (g *Geom2dGeometry) TranslatedWithPoint(p1, p2 Point2) *Geom2dGeometry {
	return &Geom2dGeometry{geom: C.geom2d_translate_with_point(g.geom, p1.val, p2.val)}
}

func (g *Geom2dGeometry) Transformed(t Trsf2d) *Geom2dGeometry {
	return &Geom2dGeometry{geom: C.geom2d_transform(g.geom, t.val)}
}

func (g *Geom2dGeometry) AutoCast() interface{} {
	switch g.Type() {
	case GEOM2DBISECTORBISECANA:
		return NewGeom2dBisectorBisecAnaFromGeometry(g)
	case GEOM2DBISECTORBISECCC:
		return NewGeom2dBisectorBisecCCFromGeometry(g)
	case GEOM2DBISECTORBISECPC:
		return NewGeom2dBisectorBisecPCFromGeometry(g)
	case GEOM2DAXISPLACEMENT:
		return NewGeom2dAxisPlacementFromGeometry(g)
	case GEOM2DBSPLINECURVE:
		return NewGeom2dBSplineCurveFromGeometry(g)
	case GEOM2DBEZIERCURVE:
		return NewGeom2dBezierCurveFromGeometry(g)
	case GEOM2DBOUNDEDCURVE:
		return NewGeom2dBoundedCurveFromGeometry(g)
	case GEOM2DCARTESIANPOINT:
		return NewGeom2dCartesianPointFromGeometry(g)
	case GEOM2DCIRCLE:
		return NewGeom2dCircleFromGeometry(g)
	case GEOM2DCONIC:
		return NewGeom2dConicFromGeometry(g)
	case GEOM2DDIRECTION:
		return NewGeom2dDirectionFromGeometry(g)
	case GEOM2DELLIPSE:
		return NewGeom2dEllipseFromGeometry(g)
	case GEOM2DHYPERBOLA:
		return NewGeom2dHyperbolaFromGeometry(g)
	case GEOM2DLINE:
		return NewGeom2dLineFromGeometry(g)
	case GEOM2DOFFSETCURVE:
		return NewGeom2dOffsetCurveFromGeometry(g)
	case GEOM2DPARABOLA:
		return NewGeom2dParabolaFromGeometry(g)
	case GEOM2DTRIMMEDCURVE:
		return NewGeom2dTrimmedCurveFromGeometry(g)
	case GEOM2DVECTORWITHMAGNITUDE:
		return NewGeom2dVectorWithMagnitudeFromGeometry(g)
	case GEOM2DBISECTORCURVE:
		return NewGeom2dBisectorCurveFromGeometry(g)
	}
	return nil
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

func (g *Geom2dAxisPlacement) Geometry() *Geom2dGeometry {
	return &Geom2dGeometry{geom: C.geom2d_axis_placement_to_geometry(g.geom)}
}

func (g *Geom2dAxisPlacement) Free() {
	C.geom2d_axis_placement_free(g.geom)
	g.geom = nil
}

func (g *Geom2dAxisPlacement) Copy() *Geom2dAxisPlacement {
	return &Geom2dAxisPlacement{geom: C.geom2d_axis_placement_copy(g.geom)}
}

func NewGeom2dAxisPlacementFromGeometry(g *Geom2dGeometry) *Geom2dAxisPlacement {
	if p := C.geom2d_axis_placement_from_geometry(g.geom); p != nil {
		return &Geom2dAxisPlacement{geom: p}
	}
	return nil
}

type Geom2dCurve struct {
	geom *C.struct__geom2d_curve_t
}

func (g *Geom2dCurve) Geometry() *Geom2dGeometry {
	return &Geom2dGeometry{geom: C.geom2d_curve_to_geometry(g.geom)}
}

func (g *Geom2dCurve) Free() {
	C.geom2d_curve_free(g.geom)
	g.geom = nil
}

func (g *Geom2dCurve) Copy() *Geom2dCurve {
	return &Geom2dCurve{geom: C.geom2d_curve_copy(g.geom)}
}

func NewGeom2dCurveFromGeometry(g *Geom2dGeometry) *Geom2dCurve {
	if p := C.geom2d_curve_from_geometry(g.geom); p != nil {
		return &Geom2dCurve{geom: p}
	}
	return nil
}

type Geom2dBisectorCurve struct {
	geom *C.struct__geom2d_bisector_curve_t
}

func (g *Geom2dBisectorCurve) Curve() *Geom2dCurve {
	return &Geom2dCurve{geom: C.geom2d_bisector_curve_to_geom2d_curve(g.geom)}
}

func (g *Geom2dBisectorCurve) Geometry() *Geom2dGeometry {
	return &Geom2dGeometry{geom: C.geom2d_bisector_curve_to_geometry(g.geom)}
}

func (g *Geom2dBisectorCurve) Free() {
	C.geom2d_bisector_curve_free(g.geom)
	g.geom = nil
}

func (g *Geom2dBisectorCurve) Copy() *Geom2dBisectorCurve {
	return &Geom2dBisectorCurve{geom: C.geom2d_bisector_curve_copy(g.geom)}
}

func NewGeom2dBisectorCurveFromGeometry(g *Geom2dGeometry) *Geom2dBisectorCurve {
	if p := C.geom2d_bisector_curve_from_geometry(g.geom); p != nil {
		return &Geom2dBisectorCurve{geom: p}
	}
	return nil
}

type Geom2dBisectorBisecAna struct {
	geom *C.struct__geom2d_bezier_bisec_ana_curve_t
}

func (g *Geom2dBisectorBisecAna) Curve() *Geom2dCurve {
	return &Geom2dCurve{geom: C.geom2d_bezier_bisec_ana_curve_to_geom2d_curve(g.geom)}
}

func (g *Geom2dBisectorBisecAna) Geometry() *Geom2dGeometry {
	return &Geom2dGeometry{geom: C.geom2d_bezier_bisec_ana_curve_to_geometry(g.geom)}
}

func (g *Geom2dBisectorBisecAna) Free() {
	C.geom2d_bezier_bisec_ana_curve_free(g.geom)
	g.geom = nil
}

func (g *Geom2dBisectorBisecAna) Copy() *Geom2dBisectorBisecAna {
	return &Geom2dBisectorBisecAna{geom: C.geom2d_bezier_bisec_ana_curve_copy(g.geom)}
}

func NewGeom2dBisectorBisecAnaFromGeometry(g *Geom2dGeometry) *Geom2dBisectorBisecAna {
	if p := C.geom2d_bezier_bisec_ana_curve_from_geometry(g.geom); p != nil {
		return &Geom2dBisectorBisecAna{geom: p}
	}
	return nil
}

type Geom2dBisectorBisecCC struct {
	geom *C.struct__geom2d_bezier_bisec_cc_curve_t
}

func (g *Geom2dBisectorBisecCC) Curve() *Geom2dCurve {
	return &Geom2dCurve{geom: C.geom2d_bezier_bisec_cc_curve_to_geom2d_curve(g.geom)}
}

func (g *Geom2dBisectorBisecCC) Geometry() *Geom2dGeometry {
	return &Geom2dGeometry{geom: C.geom2d_bezier_bisec_cc_curve_to_geometry(g.geom)}
}

func (g *Geom2dBisectorBisecCC) Free() {
	C.geom2d_bezier_bisec_cc_curve_free(g.geom)
	g.geom = nil
}

func (g *Geom2dBisectorBisecCC) Copy() *Geom2dBisectorBisecCC {
	return &Geom2dBisectorBisecCC{geom: C.geom2d_bezier_bisec_cc_curve_copy(g.geom)}
}

func NewGeom2dBisectorBisecCCFromGeometry(g *Geom2dGeometry) *Geom2dBisectorBisecCC {
	if p := C.geom2d_bezier_bisec_cc_curve_from_geometry(g.geom); p != nil {
		return &Geom2dBisectorBisecCC{geom: p}
	}
	return nil
}

type Geom2dBisectorBisecPC struct {
	geom *C.struct__geom2d_bezier_bisec_pc_curve_t
}

func (g *Geom2dBisectorBisecPC) Curve() *Geom2dCurve {
	return &Geom2dCurve{geom: C.geom2d_bezier_bisec_pc_curve_to_geom2d_curve(g.geom)}
}

func (g *Geom2dBisectorBisecPC) Geometry() *Geom2dGeometry {
	return &Geom2dGeometry{geom: C.geom2d_bezier_bisec_pc_curve_to_geometry(g.geom)}
}

func (g *Geom2dBisectorBisecPC) Free() {
	C.geom2d_bezier_bisec_pc_curve_free(g.geom)
	g.geom = nil
}

func (g *Geom2dBisectorBisecPC) Copy() *Geom2dBisectorBisecPC {
	return &Geom2dBisectorBisecPC{geom: C.geom2d_bezier_bisec_pc_curve_copy(g.geom)}
}

func NewGeom2dBisectorBisecPCFromGeometry(g *Geom2dGeometry) *Geom2dBisectorBisecPC {
	if p := C.geom2d_bezier_bisec_pc_curve_from_geometry(g.geom); p != nil {
		return &Geom2dBisectorBisecPC{geom: p}
	}
	return nil
}

type Geom2dBoundedCurve struct {
	geom *C.struct__geom2d_bounded_curve_t
}

func (g *Geom2dBoundedCurve) Curve() *Geom2dCurve {
	return &Geom2dCurve{geom: C.geom2d_bounded_curve_to_geom2d_curve(g.geom)}
}

func (g *Geom2dBoundedCurve) Geometry() *Geom2dGeometry {
	return &Geom2dGeometry{geom: C.geom2d_bounded_curve_to_geometry(g.geom)}
}

func (g *Geom2dBoundedCurve) Free() {
	C.geom2d_bounded_curve_free(g.geom)
	g.geom = nil
}

func (g *Geom2dBoundedCurve) Copy() *Geom2dBoundedCurve {
	return &Geom2dBoundedCurve{geom: C.geom2d_bounded_curve_copy(g.geom)}
}

func NewGeom2dBoundedCurveFromGeometry(g *Geom2dGeometry) *Geom2dBoundedCurve {
	if p := C.geom2d_bounded_curve_from_geometry(g.geom); p != nil {
		return &Geom2dBoundedCurve{geom: p}
	}
	return nil
}

type Geom2dBezierCurve struct {
	geom *C.struct__geom2d_bezier_curve_t
}

func (g *Geom2dBezierCurve) Curve() *Geom2dCurve {
	return &Geom2dCurve{geom: C.geom2d_bezier_curve_to_geom2d_curve(g.geom)}
}

func (g *Geom2dBezierCurve) Geometry() *Geom2dGeometry {
	return &Geom2dGeometry{geom: C.geom2d_bezier_curve_to_geometry(g.geom)}
}

func (g *Geom2dBezierCurve) Free() {
	C.geom2d_bezier_curve_free(g.geom)
	g.geom = nil
}

func (g *Geom2dBezierCurve) Copy() *Geom2dBezierCurve {
	return &Geom2dBezierCurve{geom: C.geom2d_bezier_curve_copy(g.geom)}
}

func NewGeom2dBezierCurveFromGeometry(g *Geom2dGeometry) *Geom2dBezierCurve {
	if p := C.geom2d_bezier_curve_from_geometry(g.geom); p != nil {
		return &Geom2dBezierCurve{geom: p}
	}
	return nil
}

type Geom2dBSplineCurve struct {
	geom *C.struct__geom2d_bspline_curve_t
}

func (g *Geom2dBSplineCurve) Curve() *Geom2dCurve {
	return &Geom2dCurve{geom: C.geom2d_bspline_curve_to_geom2d_curve(g.geom)}
}

func (g *Geom2dBSplineCurve) Geometry() *Geom2dGeometry {
	return &Geom2dGeometry{geom: C.geom2d_bspline_curve_to_geometry(g.geom)}
}

func (g *Geom2dBSplineCurve) Free() {
	C.geom2d_bspline_curve_free(g.geom)
	g.geom = nil
}

func (g *Geom2dBSplineCurve) Copy() *Geom2dBSplineCurve {
	return &Geom2dBSplineCurve{geom: C.geom2d_bspline_curve_copy(g.geom)}
}

func NewGeom2dBSplineCurveFromGeometry(g *Geom2dGeometry) *Geom2dBSplineCurve {
	if p := C.geom2d_bspline_curve_from_geometry(g.geom); p != nil {
		return &Geom2dBSplineCurve{geom: p}
	}
	return nil
}

type Geom2dTrimmedCurve struct {
	geom *C.struct__geom2d_trimmed_curve_t
}

func (g *Geom2dTrimmedCurve) Curve() *Geom2dCurve {
	return &Geom2dCurve{geom: C.geom2d_trimmed_curve_to_geom2d_curve(g.geom)}
}

func (g *Geom2dTrimmedCurve) Geometry() *Geom2dGeometry {
	return &Geom2dGeometry{geom: C.geom2d_trimmed_curve_to_geometry(g.geom)}
}

func (g *Geom2dTrimmedCurve) Free() {
	C.geom2d_trimmed_curve_free(g.geom)
	g.geom = nil
}

func (g *Geom2dTrimmedCurve) Copy() *Geom2dTrimmedCurve {
	return &Geom2dTrimmedCurve{geom: C.geom2d_trimmed_curve_copy(g.geom)}
}

func NewGeom2dTrimmedCurveFromGeometry(g *Geom2dGeometry) *Geom2dTrimmedCurve {
	if p := C.geom2d_trimmed_curve_from_geometry(g.geom); p != nil {
		return &Geom2dTrimmedCurve{geom: p}
	}
	return nil
}

type Geom2dConic struct {
	geom *C.struct__geom2d_conic_t
}

func (g *Geom2dConic) Curve() *Geom2dCurve {
	return &Geom2dCurve{geom: C.geom2d_conic_to_geom2d_curve(g.geom)}
}

func (g *Geom2dConic) Geometry() *Geom2dGeometry {
	return &Geom2dGeometry{geom: C.geom2d_conic_to_geometry(g.geom)}
}

func (g *Geom2dConic) Free() {
	C.geom2d_conic_free(g.geom)
	g.geom = nil
}

func (g *Geom2dConic) Copy() *Geom2dConic {
	return &Geom2dConic{geom: C.geom2d_conic_copy(g.geom)}
}

func NewGeom2dConicFromGeometry(g *Geom2dGeometry) *Geom2dConic {
	if p := C.geom2d_conic_from_geometry(g.geom); p != nil {
		return &Geom2dConic{geom: p}
	}
	return nil
}

type Geom2dCircle struct {
	geom *C.struct__geom2d_circle_t
}

func (g *Geom2dCircle) Curve() *Geom2dCurve {
	return &Geom2dCurve{geom: C.geom2d_circle_to_geom2d_curve(g.geom)}
}

func (g *Geom2dCircle) Geometry() *Geom2dGeometry {
	return &Geom2dGeometry{geom: C.geom2d_circle_to_geometry(g.geom)}
}

func (g *Geom2dCircle) Free() {
	C.geom2d_circle_free(g.geom)
	g.geom = nil
}

func (g *Geom2dCircle) Copy() *Geom2dCircle {
	return &Geom2dCircle{geom: C.geom2d_circle_copy(g.geom)}
}

func NewGeom2dCircleFromGeometry(g *Geom2dGeometry) *Geom2dCircle {
	if p := C.geom2d_circle_from_geometry(g.geom); p != nil {
		return &Geom2dCircle{geom: p}
	}
	return nil
}

type Geom2dEllipse struct {
	geom *C.struct__geom2d_ellipse_t
}

func (g *Geom2dEllipse) Curve() *Geom2dCurve {
	return &Geom2dCurve{geom: C.geom2d_ellipse_to_geom2d_curve(g.geom)}
}

func (g *Geom2dEllipse) Geometry() *Geom2dGeometry {
	return &Geom2dGeometry{geom: C.geom2d_ellipse_to_geometry(g.geom)}
}

func (g *Geom2dEllipse) Free() {
	C.geom2d_ellipse_free(g.geom)
	g.geom = nil
}

func (g *Geom2dEllipse) Copy() *Geom2dEllipse {
	return &Geom2dEllipse{geom: C.geom2d_ellipse_copy(g.geom)}
}

func NewGeom2dEllipseFromGeometry(g *Geom2dGeometry) *Geom2dEllipse {
	if p := C.geom2d_ellipse_from_geometry(g.geom); p != nil {
		return &Geom2dEllipse{geom: p}
	}
	return nil
}

type Geom2dHyperbola struct {
	geom *C.struct__geom2d_hyperbola_t
}

func (g *Geom2dHyperbola) Curve() *Geom2dCurve {
	return &Geom2dCurve{geom: C.geom2d_hyperbola_to_geom2d_curve(g.geom)}
}

func (g *Geom2dHyperbola) Geometry() *Geom2dGeometry {
	return &Geom2dGeometry{geom: C.geom2d_hyperbola_to_geometry(g.geom)}
}

func (g *Geom2dHyperbola) Free() {
	C.geom2d_hyperbola_free(g.geom)
	g.geom = nil
}

func (g *Geom2dHyperbola) Copy() *Geom2dHyperbola {
	return &Geom2dHyperbola{geom: C.geom2d_hyperbola_copy(g.geom)}
}

func NewGeom2dHyperbolaFromGeometry(g *Geom2dGeometry) *Geom2dHyperbola {
	if p := C.geom2d_hyperbola_from_geometry(g.geom); p != nil {
		return &Geom2dHyperbola{geom: p}
	}
	return nil
}

type Geom2dParabola struct {
	geom *C.struct__geom2d_parabola_t
}

func (g *Geom2dParabola) Curve() *Geom2dCurve {
	return &Geom2dCurve{geom: C.geom2d_parabola_to_geom2d_curve(g.geom)}
}

func (g *Geom2dParabola) Geometry() *Geom2dGeometry {
	return &Geom2dGeometry{geom: C.geom2d_parabola_to_geometry(g.geom)}
}

func (g *Geom2dParabola) Free() {
	C.geom2d_parabola_free(g.geom)
	g.geom = nil
}

func (g *Geom2dParabola) Copy() *Geom2dParabola {
	return &Geom2dParabola{geom: C.geom2d_parabola_copy(g.geom)}
}

func NewGeom2dParabolaFromGeometry(g *Geom2dGeometry) *Geom2dParabola {
	if p := C.geom2d_parabola_from_geometry(g.geom); p != nil {
		return &Geom2dParabola{geom: p}
	}
	return nil
}

type Geom2dLine struct {
	geom *C.struct__geom2d_line_t
}

func (g *Geom2dLine) Curve() *Geom2dCurve {
	return &Geom2dCurve{geom: C.geom2d_line_to_geom2d_curve(g.geom)}
}

func (g *Geom2dLine) Geometry() *Geom2dGeometry {
	return &Geom2dGeometry{geom: C.geom2d_line_to_geometry(g.geom)}
}

func (g *Geom2dLine) Free() {
	C.geom2d_line_free(g.geom)
	g.geom = nil
}

func (g *Geom2dLine) Copy() *Geom2dLine {
	return &Geom2dLine{geom: C.geom2d_line_copy(g.geom)}
}

func NewGeom2dLineFromGeometry(g *Geom2dGeometry) *Geom2dLine {
	if p := C.geom2d_line_from_geometry(g.geom); p != nil {
		return &Geom2dLine{geom: p}
	}
	return nil
}

type Geom2dOffsetCurve struct {
	geom *C.struct__geom2d_offset_curve_t
}

func (g *Geom2dOffsetCurve) Curve() *Geom2dCurve {
	return &Geom2dCurve{geom: C.geom2d_offset_curve_to_geom2d_curve(g.geom)}
}

func (g *Geom2dOffsetCurve) Geometry() *Geom2dGeometry {
	return &Geom2dGeometry{geom: C.geom2d_offset_curve_to_geometry(g.geom)}
}

func (g *Geom2dOffsetCurve) Free() {
	C.geom2d_offset_curve_free(g.geom)
	g.geom = nil
}

func (g *Geom2dOffsetCurve) Copy() *Geom2dOffsetCurve {
	return &Geom2dOffsetCurve{geom: C.geom2d_offset_curve_copy(g.geom)}
}

func NewGeom2dOffsetCurveFromGeometry(g *Geom2dGeometry) *Geom2dOffsetCurve {
	if p := C.geom2d_offset_curve_from_geometry(g.geom); p != nil {
		return &Geom2dOffsetCurve{geom: p}
	}
	return nil
}

type Geom2dPoint struct {
	geom *C.struct__geom2d_point_t
}

func (g *Geom2dPoint) Geometry() *Geom2dGeometry {
	return &Geom2dGeometry{geom: C.geom2d_point_to_geometry(g.geom)}
}

func (g *Geom2dPoint) Free() {
	C.geom2d_point_free(g.geom)
	g.geom = nil
}

func (g *Geom2dPoint) Copy() *Geom2dPoint {
	return &Geom2dPoint{geom: C.geom2d_point_copy(g.geom)}
}

func NewGeom2dPointFromGeometry(g *Geom2dGeometry) *Geom2dPoint {
	if p := C.geom2d_point_from_geometry(g.geom); p != nil {
		return &Geom2dPoint{geom: p}
	}
	return nil
}

type Geom2dCartesianPoint struct {
	geom *C.struct__geom2d_cartesian_point_t
}

func (g *Geom2dCartesianPoint) Geometry() *Geom2dGeometry {
	return &Geom2dGeometry{geom: C.geom2d_cartesian_point_to_geometry(g.geom)}
}

func (g *Geom2dCartesianPoint) Free() {
	C.geom2d_cartesian_point_free(g.geom)
	g.geom = nil
}

func (g *Geom2dCartesianPoint) Copy() *Geom2dCartesianPoint {
	return &Geom2dCartesianPoint{geom: C.geom2d_cartesian_point_copy(g.geom)}
}

func NewGeom2dCartesianPointFromGeometry(g *Geom2dGeometry) *Geom2dCartesianPoint {
	if p := C.geom2d_cartesian_point_from_geometry(g.geom); p != nil {
		return &Geom2dCartesianPoint{geom: p}
	}
	return nil
}

type Geom2dVector struct {
	geom *C.struct__geom2d_vector_t
}

func (g *Geom2dVector) Geometry() *Geom2dGeometry {
	return &Geom2dGeometry{geom: C.geom2d_vector_to_geometry(g.geom)}
}

func (g *Geom2dVector) Free() {
	C.geom2d_vector_free(g.geom)
	g.geom = nil
}

func (g *Geom2dVector) Copy() *Geom2dVector {
	return &Geom2dVector{geom: C.geom2d_vector_copy(g.geom)}
}

func NewGeom2dVectorFromGeometry(g *Geom2dGeometry) *Geom2dVector {
	if p := C.geom2d_vector_from_geometry(g.geom); p != nil {
		return &Geom2dVector{geom: p}
	}
	return nil
}

type Geom2dDirection struct {
	geom *C.struct__geom2d_direction_t
}

func (g *Geom2dDirection) Geometry() *Geom2dGeometry {
	return &Geom2dGeometry{geom: C.geom2d_direction_to_geometry(g.geom)}
}

func (g *Geom2dDirection) Free() {
	C.geom2d_direction_free(g.geom)
	g.geom = nil
}

func (g *Geom2dDirection) Copy() *Geom2dDirection {
	return &Geom2dDirection{geom: C.geom2d_direction_copy(g.geom)}
}

func NewGeom2dDirectionFromGeometry(g *Geom2dGeometry) *Geom2dDirection {
	if p := C.geom2d_direction_from_geometry(g.geom); p != nil {
		return &Geom2dDirection{geom: p}
	}
	return nil
}

type Geom2dVectorWithMagnitude struct {
	geom *C.struct__geom2d_vector_with_magnitude_t
}

func (g *Geom2dVectorWithMagnitude) Geometry() *Geom2dGeometry {
	return &Geom2dGeometry{geom: C.geom2d_vector_with_magnitude_to_geometry(g.geom)}
}

func (g *Geom2dVectorWithMagnitude) Free() {
	C.geom2d_vector_with_magnitude_free(g.geom)
	g.geom = nil
}

func (g *Geom2dVectorWithMagnitude) Copy() *Geom2dVectorWithMagnitude {
	return &Geom2dVectorWithMagnitude{geom: C.geom2d_vector_with_magnitude_copy(g.geom)}
}

func NewGeom2dVectorWithMagnitudeFromGeometry(g *Geom2dGeometry) *Geom2dVectorWithMagnitude {
	if p := C.geom2d_vector_with_magnitude_from_geometry(g.geom); p != nil {
		return &Geom2dVectorWithMagnitude{geom: p}
	}
	return nil
}
