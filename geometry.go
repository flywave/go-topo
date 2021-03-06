package topo

/*
#include <stdlib.h>
#include "geometry_c_api.h"
#cgo CFLAGS: -I  ./libs
#cgo linux CXXFLAGS: -I ./libs  -std=gnu++14
#cgo darwin CXXFLAGS: -I ./libs  -std=gnu++14
#cgo windows CXXFLAGS: -I ./libs  -std=gnu++14
*/
import "C"
import "runtime"

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

func NewGeomGeometry(geom *C.struct__geom_geometry_t) *GeomGeometry {
	g := &GeomGeometry{geom: geom}
	runtime.SetFinalizer(g, (*GeomGeometry).free)
	return g
}

func (g *GeomGeometry) free() {
	C.geom_geometry_free(g.geom)
	g.geom = nil
}

func (g *GeomGeometry) Type() int {
	return int(C.geom_geometry_type(g.geom))
}

func (g *GeomGeometry) Copy() *GeomGeometry {
	return NewGeomGeometry(C.geom_geometry_copy(g.geom))
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
	return NewGeomGeometry(C.geom_mirror_with_point(g.geom, p.val))
}

func (g *GeomGeometry) MirroredWithAxis1(a Axis1) *GeomGeometry {
	return NewGeomGeometry(C.geom_mirror_with_axis1(g.geom, a.val))
}

func (g *GeomGeometry) MirroredWithAxis2(a Axis2) *GeomGeometry {
	return NewGeomGeometry(C.geom_mirror_with_axis2(g.geom, a.val))
}

func (g *GeomGeometry) Rotated(a Axis1, ang float64) *GeomGeometry {
	return NewGeomGeometry(C.geom_rotate(g.geom, a.val, C.double(ang)))
}

func (g *GeomGeometry) Scaled(p Point3, ang float64) *GeomGeometry {
	return NewGeomGeometry(C.geom_scale(g.geom, p.val, C.double(ang)))
}

func (g *GeomGeometry) TranslatedWithVector(v Vector3) *GeomGeometry {
	return NewGeomGeometry(C.geom_translate_with_vector(g.geom, v.val))
}

func (g *GeomGeometry) TranslatedWithPoint(p1, p2 Point3) *GeomGeometry {
	return NewGeomGeometry(C.geom_translate_with_point(g.geom, p1.val, p2.val))
}

func (g *GeomGeometry) Transformed(t Trsf) *GeomGeometry {
	return NewGeomGeometry(C.geom_transform(g.geom, t.val))
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

func NewGeomTransformation(geom *C.struct__geom_transformation_t) *GeomTransformation {
	g := &GeomTransformation{geom: geom}
	runtime.SetFinalizer(g, (*GeomTransformation).free)
	return g
}

func (g *GeomTransformation) free() {
	C.geom_transformation_free(g.geom)
	g.geom = nil
}

func (g *GeomTransformation) Copy() *GeomTransformation {
	return NewGeomTransformation(C.geom_transformation_copy(g.geom))
}

type GeomAxisPlacement struct {
	geom *C.struct__geom_axis_placement_t
}

func NewGeomAxisPlacement(geom *C.struct__geom_axis_placement_t) *GeomAxisPlacement {
	g := &GeomAxisPlacement{geom: geom}
	runtime.SetFinalizer(g, (*GeomAxisPlacement).free)
	return g
}

func (g *GeomAxisPlacement) Geometry() *GeomGeometry {
	return NewGeomGeometry(C.geom_axis_placement_to_geometry(g.geom))
}

func (g *GeomAxisPlacement) free() {
	C.geom_axis_placement_free(g.geom)
	g.geom = nil
}

func (g *GeomAxisPlacement) Copy() *GeomAxisPlacement {
	return NewGeomAxisPlacement(C.geom_axis_placement_copy(g.geom))
}

func NewGeomAxisPlacementFromGeometry(g *GeomGeometry) *GeomAxisPlacement {
	if p := C.geom_axis_placement_from_geometry(g.geom); p != nil {
		return NewGeomAxisPlacement(p)
	}
	return nil
}

type GeomAxis1Placement struct {
	geom *C.struct__geom_axis1_placement_t
}

func NewGeomAxis1Placement(geom *C.struct__geom_axis1_placement_t) *GeomAxis1Placement {
	g := &GeomAxis1Placement{geom: geom}
	runtime.SetFinalizer(g, (*GeomAxis1Placement).free)
	return g
}

func (g *GeomAxis1Placement) Geometry() *GeomGeometry {
	return NewGeomGeometry(C.geom_axis1_placement_to_geometry(g.geom))
}

func (g *GeomAxis1Placement) free() {
	C.geom_axis1_placement_free(g.geom)
	g.geom = nil
}

func (g *GeomAxis1Placement) Copy() *GeomAxis1Placement {
	return NewGeomAxis1Placement(C.geom_axis1_placement_copy(g.geom))
}

func NewGeomAxis1PlacementFromGeometry(g *GeomGeometry) *GeomAxis1Placement {
	if p := C.geom_axis1_placement_from_geometry(g.geom); p != nil {
		return NewGeomAxis1Placement(p)
	}
	return nil
}

type GeomAxis2Placement struct {
	geom *C.struct__geom_axis2_placement_t
}

func NewGeomAxis2Placement(geom *C.struct__geom_axis2_placement_t) *GeomAxis2Placement {
	g := &GeomAxis2Placement{geom: geom}
	runtime.SetFinalizer(g, (*GeomAxis2Placement).free)
	return g
}

func (g *GeomAxis2Placement) Geometry() *GeomGeometry {
	return NewGeomGeometry(C.geom_axis2_placement_to_geometry(g.geom))
}

func (g *GeomAxis2Placement) free() {
	C.geom_axis2_placement_free(g.geom)
	g.geom = nil
}

func (g *GeomAxis2Placement) Copy() *GeomAxis2Placement {
	return NewGeomAxis2Placement(C.geom_axis2_placement_copy(g.geom))
}

func NewGeomAxis2PlacementFromGeometry(g *GeomGeometry) *GeomAxis2Placement {
	if p := C.geom_axis2_placement_from_geometry(g.geom); p != nil {
		return NewGeomAxis2Placement(p)
	}
	return nil
}

type GeomCurve struct {
	geom *C.struct__geom_curve_t
}

func NewGeomCurve(geom *C.struct__geom_curve_t) *GeomCurve {
	g := &GeomCurve{geom: geom}
	runtime.SetFinalizer(g, (*GeomCurve).free)
	return g
}

func (g *GeomCurve) Geometry() *GeomGeometry {
	return NewGeomGeometry(C.geom_curve_to_geometry(g.geom))
}

func (g *GeomCurve) free() {
	C.geom_curve_free(g.geom)
	g.geom = nil
}

func (g *GeomCurve) Copy() *GeomCurve {
	return NewGeomCurve(C.geom_curve_copy(g.geom))
}

func NewGeomCurveFromGeometry(g *GeomGeometry) *GeomCurve {
	if p := C.geom_curve_from_geometry(g.geom); p != nil {
		return NewGeomCurve(p)
	}
	return nil
}

type GeomBoundedCurve struct {
	geom *C.struct__geom_bounded_curve_t
}

func NewGeomBoundedCurve(geom *C.struct__geom_bounded_curve_t) *GeomBoundedCurve {
	g := &GeomBoundedCurve{geom: geom}
	runtime.SetFinalizer(g, (*GeomBoundedCurve).free)
	return g
}

func (g *GeomBoundedCurve) Curve() *GeomCurve {
	return NewGeomCurve(C.geom_bounded_curve_to_geom_curve(g.geom))
}

func (g *GeomBoundedCurve) Geometry() *GeomGeometry {
	return NewGeomGeometry(C.geom_bounded_curve_to_geometry(g.geom))
}

func (g *GeomBoundedCurve) free() {
	C.geom_bounded_curve_free(g.geom)
	g.geom = nil
}

func (g *GeomBoundedCurve) Copy() *GeomBoundedCurve {
	return NewGeomBoundedCurve(C.geom_bounded_curve_copy(g.geom))
}

func NewGeomBoundedCurveFromGeometry(g *GeomGeometry) *GeomBoundedCurve {
	if p := C.geom_bounded_curve_from_geometry(g.geom); p != nil {
		return NewGeomBoundedCurve(p)
	}
	return nil
}

type GeomBezierCurve struct {
	geom *C.struct__geom_bezier_curve_t
}

func NewGeomBezierCurve(geom *C.struct__geom_bezier_curve_t) *GeomBezierCurve {
	g := &GeomBezierCurve{geom: geom}
	runtime.SetFinalizer(g, (*GeomBezierCurve).free)
	return g
}

func (g *GeomBezierCurve) Curve() *GeomCurve {
	return NewGeomCurve(C.geom_bezier_curve_to_geom_curve(g.geom))
}

func (g *GeomBezierCurve) Geometry() *GeomGeometry {
	return NewGeomGeometry(C.geom_bezier_curve_to_geometry(g.geom))
}

func (g *GeomBezierCurve) free() {
	C.geom_bezier_curve_free(g.geom)
	g.geom = nil
}

func (g *GeomBezierCurve) Copy() *GeomBezierCurve {
	return NewGeomBezierCurve(C.geom_bezier_curve_copy(g.geom))
}

func NewGeomBezierCurveFromGeometry(g *GeomGeometry) *GeomBezierCurve {
	if p := C.geom_bezier_curve_from_geometry(g.geom); p != nil {
		return NewGeomBezierCurve(p)
	}
	return nil
}

type GeomBSplineCurve struct {
	geom *C.struct__geom_bspline_curve_t
}

func NewGeomBSplineCurve(geom *C.struct__geom_bspline_curve_t) *GeomBSplineCurve {
	g := &GeomBSplineCurve{geom: geom}
	runtime.SetFinalizer(g, (*GeomBSplineCurve).free)
	return g
}

func (g *GeomBSplineCurve) Curve() *GeomCurve {
	return NewGeomCurve(C.geom_bspline_curve_to_geom_curve(g.geom))
}

func (g *GeomBSplineCurve) Geometry() *GeomGeometry {
	return NewGeomGeometry(C.geom_bspline_curve_to_geometry(g.geom))
}

func (g *GeomBSplineCurve) free() {
	C.geom_bspline_curve_free(g.geom)
	g.geom = nil
}

func (g *GeomBSplineCurve) Copy() *GeomBSplineCurve {
	return NewGeomBSplineCurve(C.geom_bspline_curve_copy(g.geom))
}

func NewGeomBSplineCurveFromGeometry(g *GeomGeometry) *GeomBSplineCurve {
	if p := C.geom_bspline_curve_from_geometry(g.geom); p != nil {
		return NewGeomBSplineCurve(p)
	}
	return nil
}

func NewGeomBSplineCurveFromPoints(pts []Point3) *GeomBSplineCurve {
	ptr := &pts[0].val
	if p := C.geom_bspline_curve_from_points(ptr, C.int(len(pts))); p != nil {
		return NewGeomBSplineCurve(p)
	}
	return nil
}

type GeomTrimmedCurve struct {
	geom *C.struct__geom_trimmed_curve_t
}

func NewGeomTrimmedCurve(geom *C.struct__geom_trimmed_curve_t) *GeomTrimmedCurve {
	g := &GeomTrimmedCurve{geom: geom}
	runtime.SetFinalizer(g, (*GeomTrimmedCurve).free)
	return g
}

func (g *GeomTrimmedCurve) Curve() *GeomCurve {
	return NewGeomCurve(C.geom_trimmed_curve_to_geom_curve(g.geom))
}

func (g *GeomTrimmedCurve) Geometry() *GeomGeometry {
	return NewGeomGeometry(C.geom_trimmed_curve_to_geometry(g.geom))
}

func (g *GeomTrimmedCurve) free() {
	C.geom_trimmed_curve_free(g.geom)
	g.geom = nil
}

func (g *GeomTrimmedCurve) Copy() *GeomTrimmedCurve {
	return NewGeomTrimmedCurve(C.geom_trimmed_curve_copy(g.geom))
}

func NewGeomTrimmedCurveFromGeometry(g *GeomGeometry) *GeomTrimmedCurve {
	if p := C.geom_trimmed_curve_from_geometry(g.geom); p != nil {
		return NewGeomTrimmedCurve(p)
	}
	return nil
}

type GeomConic struct {
	geom *C.struct__geom_conic_t
}

func NewGeomConic(geom *C.struct__geom_conic_t) *GeomConic {
	g := &GeomConic{geom: geom}
	runtime.SetFinalizer(g, (*GeomConic).free)
	return g
}

func (g *GeomConic) Curve() *GeomCurve {
	return NewGeomCurve(C.geom_conic_to_geom_curve(g.geom))
}

func (g *GeomConic) Geometry() *GeomGeometry {
	return NewGeomGeometry(C.geom_conic_to_geometry(g.geom))
}

func (g *GeomConic) free() {
	C.geom_conic_free(g.geom)
	g.geom = nil
}

func (g *GeomConic) Copy() *GeomConic {
	return NewGeomConic(C.geom_conic_copy(g.geom))
}

func NewGeomConicFromGeometry(g *GeomGeometry) *GeomConic {
	if p := C.geom_conic_from_geometry(g.geom); p != nil {
		return NewGeomConic(p)
	}
	return nil
}

type GeomCircle struct {
	geom *C.struct__geom_circle_t
}

func NewGeomCircle(geom *C.struct__geom_circle_t) *GeomCircle {
	g := &GeomCircle{geom: geom}
	runtime.SetFinalizer(g, (*GeomCircle).free)
	return g
}

func (g *GeomCircle) Curve() *GeomCurve {
	return NewGeomCurve(C.geom_circle_to_geom_curve(g.geom))
}

func (g *GeomCircle) Geometry() *GeomGeometry {
	return NewGeomGeometry(C.geom_circle_to_geometry(g.geom))
}

func (g *GeomCircle) free() {
	C.geom_circle_free(g.geom)
	g.geom = nil
}

func (g *GeomCircle) Copy() *GeomCircle {
	return NewGeomCircle(C.geom_circle_copy(g.geom))
}

func NewGeomCircleFromGeometry(g *GeomGeometry) *GeomCircle {
	if p := C.geom_circle_from_geometry(g.geom); p != nil {
		return NewGeomCircle(p)
	}
	return nil
}

type GeomEllipse struct {
	geom *C.struct__geom_ellipse_t
}

func NewGeomEllipse(geom *C.struct__geom_ellipse_t) *GeomEllipse {
	g := &GeomEllipse{geom: geom}
	runtime.SetFinalizer(g, (*GeomEllipse).free)
	return g
}

func (g *GeomEllipse) Curve() *GeomCurve {
	return NewGeomCurve(C.geom_ellipse_to_geom_curve(g.geom))
}

func (g *GeomEllipse) Geometry() *GeomGeometry {
	return NewGeomGeometry(C.geom_ellipse_to_geometry(g.geom))
}

func (g *GeomEllipse) free() {
	C.geom_ellipse_free(g.geom)
	g.geom = nil
}

func (g *GeomEllipse) Copy() *GeomEllipse {
	return NewGeomEllipse(C.geom_ellipse_copy(g.geom))
}

func NewGeomEllipseFromGeometry(g *GeomGeometry) *GeomEllipse {
	if p := C.geom_ellipse_from_geometry(g.geom); p != nil {
		return NewGeomEllipse(p)
	}
	return nil
}

type GeomHyperbola struct {
	geom *C.struct__geom_hyperbola_t
}

func NewGeomHyperbola(geom *C.struct__geom_hyperbola_t) *GeomHyperbola {
	g := &GeomHyperbola{geom: geom}
	runtime.SetFinalizer(g, (*GeomHyperbola).free)
	return g
}

func (g *GeomHyperbola) Curve() *GeomCurve {
	return NewGeomCurve(C.geom_hyperbola_to_geom_curve(g.geom))
}

func (g *GeomHyperbola) Geometry() *GeomGeometry {
	return NewGeomGeometry(C.geom_hyperbola_to_geometry(g.geom))
}

func (g *GeomHyperbola) free() {
	C.geom_hyperbola_free(g.geom)
	g.geom = nil
}

func (g *GeomHyperbola) Copy() *GeomHyperbola {
	return NewGeomHyperbola(C.geom_hyperbola_copy(g.geom))
}

func NewGeomHyperbolaFromGeometry(g *GeomGeometry) *GeomHyperbola {
	if p := C.geom_hyperbola_from_geometry(g.geom); p != nil {
		return NewGeomHyperbola(p)
	}
	return nil
}

type GeomParabola struct {
	geom *C.struct__geom_parabola_t
}

func NewGeomParabola(geom *C.struct__geom_parabola_t) *GeomParabola {
	g := &GeomParabola{geom: geom}
	runtime.SetFinalizer(g, (*GeomParabola).free)
	return g
}

func (g *GeomParabola) Curve() *GeomCurve {
	return NewGeomCurve(C.geom_parabola_to_geom_curve(g.geom))
}

func (g *GeomParabola) Geometry() *GeomGeometry {
	return NewGeomGeometry(C.geom_parabola_to_geometry(g.geom))
}

func (g *GeomParabola) free() {
	C.geom_parabola_free(g.geom)
	g.geom = nil
}

func (g *GeomParabola) Copy() *GeomParabola {
	return NewGeomParabola(C.geom_parabola_copy(g.geom))
}

func NewGeomParabolaFromGeometry(g *GeomGeometry) *GeomParabola {
	if p := C.geom_parabola_from_geometry(g.geom); p != nil {
		return NewGeomParabola(p)
	}
	return nil
}

type GeomLine struct {
	geom *C.struct__geom_line_t
}

func NewGeomLine(geom *C.struct__geom_line_t) *GeomLine {
	g := &GeomLine{geom: geom}
	runtime.SetFinalizer(g, (*GeomLine).free)
	return g
}

func (g *GeomLine) Curve() *GeomCurve {
	return NewGeomCurve(C.geom_line_to_geom_curve(g.geom))
}

func (g *GeomLine) Geometry() *GeomGeometry {
	return NewGeomGeometry(C.geom_line_to_geometry(g.geom))
}

func (g *GeomLine) free() {
	C.geom_line_free(g.geom)
	g.geom = nil
}

func (g *GeomLine) Copy() *GeomLine {
	return NewGeomLine(C.geom_line_copy(g.geom))
}

func NewGeomLineFromGeometry(g *GeomGeometry) *GeomLine {
	if p := C.geom_line_from_geometry(g.geom); p != nil {
		return NewGeomLine(p)
	}
	return nil
}

type GeomOffsetCurve struct {
	geom *C.struct__geom_offset_curve_t
}

func NewGeomOffsetCurve(geom *C.struct__geom_offset_curve_t) *GeomOffsetCurve {
	g := &GeomOffsetCurve{geom: geom}
	runtime.SetFinalizer(g, (*GeomOffsetCurve).free)
	return g
}

func (g *GeomOffsetCurve) Curve() *GeomCurve {
	return NewGeomCurve(C.geom_offset_curve_to_geom_curve(g.geom))
}

func (g *GeomOffsetCurve) Geometry() *GeomGeometry {
	return NewGeomGeometry(C.geom_offset_curve_to_geometry(g.geom))
}

func (g *GeomOffsetCurve) free() {
	C.geom_offset_curve_free(g.geom)
	g.geom = nil
}

func (g *GeomOffsetCurve) Copy() *GeomOffsetCurve {
	return NewGeomOffsetCurve(C.geom_offset_curve_copy(g.geom))
}

func NewGeomOffsetCurveFromGeometry(g *GeomGeometry) *GeomOffsetCurve {
	if p := C.geom_offset_curve_from_geometry(g.geom); p != nil {
		return NewGeomOffsetCurve(p)
	}
	return nil
}

type GeomPoint struct {
	geom *C.struct__geom_point_t
}

func NewGeomPoint(geom *C.struct__geom_point_t) *GeomPoint {
	g := &GeomPoint{geom: geom}
	runtime.SetFinalizer(g, (*GeomPoint).free)
	return g
}

func (g *GeomPoint) Geometry() *GeomGeometry {
	return NewGeomGeometry(C.geom_point_to_geometry(g.geom))
}

func (g *GeomPoint) free() {
	C.geom_point_free(g.geom)
	g.geom = nil
}

func (g *GeomPoint) Copy() *GeomPoint {
	return &GeomPoint{geom: C.geom_point_copy(g.geom)}
}

func NewGeomPointFromGeometry(g *GeomGeometry) *GeomPoint {
	if p := C.geom_point_from_geometry(g.geom); p != nil {
		return NewGeomPoint(p)
	}
	return nil
}

type GeomCartesianPoint struct {
	geom *C.struct__geom_cartesian_point_t
}

func NewGeomCartesianPoint(geom *C.struct__geom_cartesian_point_t) *GeomCartesianPoint {
	g := &GeomCartesianPoint{geom: geom}
	runtime.SetFinalizer(g, (*GeomCartesianPoint).free)
	return g
}

func (g *GeomCartesianPoint) Geometry() *GeomGeometry {
	return NewGeomGeometry(C.geom_cartesian_point_to_geometry(g.geom))
}

func (g *GeomCartesianPoint) free() {
	C.geom_cartesian_point_free(g.geom)
	g.geom = nil
}

func (g *GeomCartesianPoint) Copy() *GeomCartesianPoint {
	return NewGeomCartesianPoint(C.geom_cartesian_point_copy(g.geom))
}

func NewGeomCartesianPointFromGeometry(g *GeomGeometry) *GeomCartesianPoint {
	if p := C.geom_cartesian_point_from_geometry(g.geom); p != nil {
		return NewGeomCartesianPoint(p)
	}
	return nil
}

type GeomSurface struct {
	geom *C.struct__geom_surface_t
}

func NewGeomSurface(geom *C.struct__geom_surface_t) *GeomSurface {
	g := &GeomSurface{geom: geom}
	runtime.SetFinalizer(g, (*GeomSurface).free)
	return g
}

func (g *GeomSurface) Geometry() *GeomGeometry {
	return NewGeomGeometry(C.geom_surface_to_geometry(g.geom))
}

func (g *GeomSurface) free() {
	C.geom_surface_free(g.geom)
	g.geom = nil
}

func (g *GeomSurface) Copy() *GeomSurface {
	return NewGeomSurface(C.geom_surface_copy(g.geom))
}

func NewGeomSurfaceFromGeometry(g *GeomGeometry) *GeomSurface {
	if p := C.geom_surface_from_geometry(g.geom); p != nil {
		return NewGeomSurface(p)
	}
	return nil
}

type GeomBoundedSurface struct {
	geom *C.struct__geom_bounded_surface_t
}

func NewGeomBoundedSurface(geom *C.struct__geom_bounded_surface_t) *GeomBoundedSurface {
	g := &GeomBoundedSurface{geom: geom}
	runtime.SetFinalizer(g, (*GeomBoundedSurface).free)
	return g
}

func (g *GeomBoundedSurface) Surface() *GeomSurface {
	return NewGeomSurface(C.geom_bounded_surface_to_geom_surface(g.geom))
}

func (g *GeomBoundedSurface) Geometry() *GeomGeometry {
	return NewGeomGeometry(C.geom_bounded_surface_to_geometry(g.geom))
}

func (g *GeomBoundedSurface) free() {
	C.geom_bounded_surface_free(g.geom)
	g.geom = nil
}

func (g *GeomBoundedSurface) Copy() *GeomBoundedSurface {
	return NewGeomBoundedSurface(C.geom_bounded_surface_copy(g.geom))
}

func NewGeomBoundedSurfaceFromGeometry(g *GeomGeometry) *GeomBoundedSurface {
	if p := C.geom_bounded_surface_from_geometry(g.geom); p != nil {
		return NewGeomBoundedSurface(p)
	}
	return nil
}

type GeomBezierSurface struct {
	geom *C.struct__geom_bezier_surface_t
}

func NewGeomBezierSurface(geom *C.struct__geom_bezier_surface_t) *GeomBezierSurface {
	g := &GeomBezierSurface{geom: geom}
	runtime.SetFinalizer(g, (*GeomBezierSurface).free)
	return g
}

func (g *GeomBezierSurface) Surface() *GeomSurface {
	return NewGeomSurface(C.geom_bezier_surface_to_geom_surface(g.geom))
}

func (g *GeomBezierSurface) Geometry() *GeomGeometry {
	return NewGeomGeometry(C.geom_bezier_surface_to_geometry(g.geom))
}

func (g *GeomBezierSurface) free() {
	C.geom_bezier_surface_free(g.geom)
	g.geom = nil
}

func (g *GeomBezierSurface) Copy() *GeomBezierSurface {
	return NewGeomBezierSurface(C.geom_bezier_surface_copy(g.geom))
}

func NewGeomBezierSurfaceFromGeometry(g *GeomGeometry) *GeomBezierSurface {
	if p := C.geom_bezier_surface_from_geometry(g.geom); p != nil {
		return NewGeomBezierSurface(p)
	}
	return nil
}

type GeomBSplineSurface struct {
	geom *C.struct__geom_bspline_surface_t
}

func NewGeomBSplineSurface(geom *C.struct__geom_bspline_surface_t) *GeomBSplineSurface {
	g := &GeomBSplineSurface{geom: geom}
	runtime.SetFinalizer(g, (*GeomBSplineSurface).free)
	return g
}

func (g *GeomBSplineSurface) Surface() *GeomSurface {
	return NewGeomSurface(C.geom_bspline_surface_to_geom_surface(g.geom))
}

func (g *GeomBSplineSurface) Geometry() *GeomGeometry {
	return NewGeomGeometry(C.geom_bspline_surface_to_geometry(g.geom))
}

func (g *GeomBSplineSurface) free() {
	C.geom_bspline_surface_free(g.geom)
	g.geom = nil
}

func (g *GeomBSplineSurface) Copy() *GeomBSplineSurface {
	return NewGeomBSplineSurface(C.geom_bspline_surface_copy(g.geom))
}

func NewGeomBSplineSurfaceFromGeometry(g *GeomGeometry) *GeomBSplineSurface {
	if p := C.geom_bspline_surface_from_geometry(g.geom); p != nil {
		return NewGeomBSplineSurface(p)
	}
	return nil
}

type GeomRectangularTrimmedSurface struct {
	geom *C.struct__geom_rectangular_trimmed_surface_t
}

func NewGeomRectangularTrimmedSurface(geom *C.struct__geom_rectangular_trimmed_surface_t) *GeomRectangularTrimmedSurface {
	g := &GeomRectangularTrimmedSurface{geom: geom}
	runtime.SetFinalizer(g, (*GeomRectangularTrimmedSurface).free)
	return g
}

func (g *GeomRectangularTrimmedSurface) Surface() *GeomSurface {
	return NewGeomSurface(C.geom_rectangular_trimmed_surface_to_geom_surface(g.geom))
}

func (g *GeomRectangularTrimmedSurface) Geometry() *GeomGeometry {
	return NewGeomGeometry(C.geom_rectangular_trimmed_surface_to_geometry(g.geom))
}

func (g *GeomRectangularTrimmedSurface) free() {
	C.geom_rectangular_trimmed_surface_free(g.geom)
	g.geom = nil
}

func (g *GeomRectangularTrimmedSurface) Copy() *GeomRectangularTrimmedSurface {
	return NewGeomRectangularTrimmedSurface(C.geom_rectangular_trimmed_surface_copy(g.geom))
}

func NewGeomRectangularTrimmedSurfaceFromGeometry(g *GeomGeometry) *GeomRectangularTrimmedSurface {
	if p := C.geom_rectangular_trimmed_surface_from_geometry(g.geom); p != nil {
		return NewGeomRectangularTrimmedSurface(p)
	}
	return nil
}

type GeomElementarySurface struct {
	geom *C.struct__geom_elementary_surface_t
}

func NewGeomElementarySurface(geom *C.struct__geom_elementary_surface_t) *GeomElementarySurface {
	g := &GeomElementarySurface{geom: geom}
	runtime.SetFinalizer(g, (*GeomElementarySurface).free)
	return g
}

func (g *GeomElementarySurface) Surface() *GeomSurface {
	return NewGeomSurface(C.geom_elementary_surface_to_geom_surface(g.geom))
}

func (g *GeomElementarySurface) Geometry() *GeomGeometry {
	return NewGeomGeometry(C.geom_elementary_surface_to_geometry(g.geom))
}

func (g *GeomElementarySurface) free() {
	C.geom_elementary_surface_free(g.geom)
	g.geom = nil
}

func (g *GeomElementarySurface) Copy() *GeomElementarySurface {
	return NewGeomElementarySurface(C.geom_elementary_surface_copy(g.geom))
}

func NewGeomElementarySurfaceFromGeometry(g *GeomGeometry) *GeomElementarySurface {
	if p := C.geom_elementary_surface_from_geometry(g.geom); p != nil {
		return NewGeomElementarySurface(p)
	}
	return nil
}

type GeomCylindricalSurface struct {
	geom *C.struct__geom_cylindrical_surface_t
}

func NewGeomCylindricalSurface(geom *C.struct__geom_cylindrical_surface_t) *GeomCylindricalSurface {
	g := &GeomCylindricalSurface{geom: geom}
	runtime.SetFinalizer(g, (*GeomCylindricalSurface).free)
	return g
}

func (g *GeomCylindricalSurface) Surface() *GeomSurface {
	return NewGeomSurface(C.geom_cylindrical_surface_to_geom_surface(g.geom))
}

func (g *GeomCylindricalSurface) Geometry() *GeomGeometry {
	return NewGeomGeometry(C.geom_cylindrical_surface_to_geometry(g.geom))
}

func (g *GeomCylindricalSurface) free() {
	C.geom_cylindrical_surface_free(g.geom)
	g.geom = nil
}

func (g *GeomCylindricalSurface) Copy() *GeomCylindricalSurface {
	return NewGeomCylindricalSurface(C.geom_cylindrical_surface_copy(g.geom))
}

func NewGeomCylindricalSurfaceFromGeometry(g *GeomGeometry) *GeomCylindricalSurface {
	if p := C.geom_cylindrical_surface_from_geometry(g.geom); p != nil {
		return NewGeomCylindricalSurface(p)
	}
	return nil
}

type GeomPlane struct {
	geom *C.struct__geom_plane_surface_t
}

func NewGeomPlane(geom *C.struct__geom_plane_surface_t) *GeomPlane {
	g := &GeomPlane{geom: geom}
	runtime.SetFinalizer(g, (*GeomPlane).free)
	return g
}

func (g *GeomPlane) Surface() *GeomSurface {
	return NewGeomSurface(C.geom_plane_surface_to_geom_surface(g.geom))
}

func (g *GeomPlane) Geometry() *GeomGeometry {
	return NewGeomGeometry(C.geom_plane_surface_to_geometry(g.geom))
}

func (g *GeomPlane) free() {
	C.geom_plane_surface_free(g.geom)
	g.geom = nil
}

func (g *GeomPlane) Copy() *GeomPlane {
	return NewGeomPlane(C.geom_plane_surface_copy(g.geom))
}

func NewGeomPlaneFromGeometry(g *GeomGeometry) *GeomPlane {
	if p := C.geom_plane_surface_from_geometry(g.geom); p != nil {
		return NewGeomPlane(p)
	}
	return nil
}

type GeomConicalSurface struct {
	geom *C.struct__geom_conical_surface_t
}

func NewGeomConicalSurface(geom *C.struct__geom_conical_surface_t) *GeomConicalSurface {
	g := &GeomConicalSurface{geom: geom}
	runtime.SetFinalizer(g, (*GeomConicalSurface).free)
	return g
}

func (g *GeomConicalSurface) Surface() *GeomSurface {
	return NewGeomSurface(C.geom_conical_surface_to_geom_surface(g.geom))
}

func (g *GeomConicalSurface) Geometry() *GeomGeometry {
	return NewGeomGeometry(C.geom_conical_surface_to_geometry(g.geom))
}

func (g *GeomConicalSurface) free() {
	C.geom_conical_surface_free(g.geom)
	g.geom = nil
}

func (g *GeomConicalSurface) Copy() *GeomConicalSurface {
	return NewGeomConicalSurface(C.geom_conical_surface_copy(g.geom))
}

func NewGeomConicalSurfaceFromGeometry(g *GeomGeometry) *GeomConicalSurface {
	if p := C.geom_conical_surface_from_geometry(g.geom); p != nil {
		return NewGeomConicalSurface(p)
	}
	return nil
}

type GeomSphericalSurface struct {
	geom *C.struct__geom_spherical_surface_t
}

func NewGeomSphericalSurface(geom *C.struct__geom_spherical_surface_t) *GeomSphericalSurface {
	g := &GeomSphericalSurface{geom: geom}
	runtime.SetFinalizer(g, (*GeomSphericalSurface).free)
	return g
}

func (g *GeomSphericalSurface) Surface() *GeomSurface {
	return NewGeomSurface(C.geom_spherical_surface_to_geom_surface(g.geom))
}

func (g *GeomSphericalSurface) Geometry() *GeomGeometry {
	return NewGeomGeometry(C.geom_spherical_surface_to_geometry(g.geom))
}

func (g *GeomSphericalSurface) free() {
	C.geom_spherical_surface_free(g.geom)
	g.geom = nil
}

func (g *GeomSphericalSurface) Copy() *GeomSphericalSurface {
	return NewGeomSphericalSurface(C.geom_spherical_surface_copy(g.geom))
}

func NewGeomSphericalSurfaceFromGeometry(g *GeomGeometry) *GeomSphericalSurface {
	if p := C.geom_spherical_surface_from_geometry(g.geom); p != nil {
		return NewGeomSphericalSurface(p)
	}
	return nil
}

type GeomToroidalSurface struct {
	geom *C.struct__geom_toroidal_surface_t
}

func NewGeomToroidalSurface(geom *C.struct__geom_toroidal_surface_t) *GeomToroidalSurface {
	g := &GeomToroidalSurface{geom: geom}
	runtime.SetFinalizer(g, (*GeomToroidalSurface).free)
	return g
}

func (g *GeomToroidalSurface) Surface() *GeomSurface {
	return NewGeomSurface(C.geom_toroidal_surface_to_geom_surface(g.geom))
}

func (g *GeomToroidalSurface) Geometry() *GeomGeometry {
	return NewGeomGeometry(C.geom_toroidal_surface_to_geometry(g.geom))
}

func (g *GeomToroidalSurface) free() {
	C.geom_toroidal_surface_free(g.geom)
	g.geom = nil
}

func (g *GeomToroidalSurface) Copy() *GeomToroidalSurface {
	return NewGeomToroidalSurface(C.geom_toroidal_surface_copy(g.geom))
}

func NewGeomToroidalSurfaceFromGeometry(g *GeomGeometry) *GeomToroidalSurface {
	if p := C.geom_toroidal_surface_from_geometry(g.geom); p != nil {
		return NewGeomToroidalSurface(p)
	}
	return nil
}

type GeomOffsetSurface struct {
	geom *C.struct__geom_offset_surface_t
}

func NewGeomOffsetSurface(geom *C.struct__geom_offset_surface_t) *GeomOffsetSurface {
	g := &GeomOffsetSurface{geom: geom}
	runtime.SetFinalizer(g, (*GeomOffsetSurface).free)
	return g
}

func (g *GeomOffsetSurface) Surface() *GeomSurface {
	return NewGeomSurface(C.geom_offset_surface_to_geom_surface(g.geom))
}

func (g *GeomOffsetSurface) Geometry() *GeomGeometry {
	return NewGeomGeometry(C.geom_offset_surface_to_geometry(g.geom))
}

func (g *GeomOffsetSurface) free() {
	C.geom_offset_surface_free(g.geom)
	g.geom = nil
}

func (g *GeomOffsetSurface) Copy() *GeomOffsetSurface {
	return NewGeomOffsetSurface(C.geom_offset_surface_copy(g.geom))
}

func NewGeomOffsetSurfaceFromGeometry(g *GeomGeometry) *GeomOffsetSurface {
	if p := C.geom_offset_surface_from_geometry(g.geom); p != nil {
		return NewGeomOffsetSurface(p)
	}
	return nil
}

type GeomSweptSurface struct {
	geom *C.struct__geom_swept_surface_t
}

func NewGeomSweptSurface(geom *C.struct__geom_swept_surface_t) *GeomSweptSurface {
	g := &GeomSweptSurface{geom: geom}
	runtime.SetFinalizer(g, (*GeomSweptSurface).free)
	return g
}

func (g *GeomSweptSurface) Surface() *GeomSurface {
	return NewGeomSurface(C.geom_swept_surface_to_geom_surface(g.geom))
}

func (g *GeomSweptSurface) Geometry() *GeomGeometry {
	return NewGeomGeometry(C.geom_swept_surface_to_geometry(g.geom))
}

func (g *GeomSweptSurface) free() {
	C.geom_swept_surface_free(g.geom)
	g.geom = nil
}

func (g *GeomSweptSurface) Copy() *GeomSweptSurface {
	return NewGeomSweptSurface(C.geom_swept_surface_copy(g.geom))
}

func NewGeomSweptSurfaceFromGeometry(g *GeomGeometry) *GeomSweptSurface {
	if p := C.geom_swept_surface_from_geometry(g.geom); p != nil {
		return NewGeomSweptSurface(p)
	}
	return nil
}

type GeomSurfaceOfLinearExtrusion struct {
	geom *C.struct__geom_surface_of_linear_extrusion_t
}

func NewGeomSurfaceOfLinearExtrusion(geom *C.struct__geom_surface_of_linear_extrusion_t) *GeomSurfaceOfLinearExtrusion {
	g := &GeomSurfaceOfLinearExtrusion{geom: geom}
	runtime.SetFinalizer(g, (*GeomSurfaceOfLinearExtrusion).free)
	return g
}

func (g *GeomSurfaceOfLinearExtrusion) Surface() *GeomSurface {
	return NewGeomSurface(C.geom_surface_of_linear_extrusion_to_geom_surface(g.geom))
}

func (g *GeomSurfaceOfLinearExtrusion) Geometry() *GeomGeometry {
	return NewGeomGeometry(C.geom_surface_of_linear_extrusion_to_geometry(g.geom))
}

func (g *GeomSurfaceOfLinearExtrusion) free() {
	C.geom_surface_of_linear_extrusion_free(g.geom)
	g.geom = nil
}

func (g *GeomSurfaceOfLinearExtrusion) Copy() *GeomSurfaceOfLinearExtrusion {
	return NewGeomSurfaceOfLinearExtrusion(C.geom_surface_of_linear_extrusion_copy(g.geom))
}

func NewGeomSurfaceOfLinearExtrusionFromGeometry(g *GeomGeometry) *GeomSurfaceOfLinearExtrusion {
	if p := C.geom_surface_of_linear_extrusion_from_geometry(g.geom); p != nil {
		return NewGeomSurfaceOfLinearExtrusion(p)
	}
	return nil
}

type GeomSurfaceOfRevolution struct {
	geom *C.struct__geom_surface_of_revolution_extrusion_t
}

func NewGeomSurfaceOfRevolution(geom *C.struct__geom_surface_of_revolution_extrusion_t) *GeomSurfaceOfRevolution {
	g := &GeomSurfaceOfRevolution{geom: geom}
	runtime.SetFinalizer(g, (*GeomSurfaceOfRevolution).free)
	return g
}

func (g *GeomSurfaceOfRevolution) Surface() *GeomSurface {
	return NewGeomSurface(C.geom_surface_of_revolution_extrusion_to_geom_surface(g.geom))
}

func (g *GeomSurfaceOfRevolution) Geometry() *GeomGeometry {
	return NewGeomGeometry(C.geom_surface_of_revolution_extrusion_to_geometry(g.geom))
}

func (g *GeomSurfaceOfRevolution) free() {
	C.geom_surface_of_revolution_extrusion_free(g.geom)
	g.geom = nil
}

func (g *GeomSurfaceOfRevolution) Copy() *GeomSurfaceOfRevolution {
	return NewGeomSurfaceOfRevolution(C.geom_surface_of_revolution_extrusion_copy(g.geom))
}

func NewGeomSurfaceOfRevolutionFromGeometry(g *GeomGeometry) *GeomSurfaceOfRevolution {
	if p := C.geom_surface_of_revolution_extrusion_from_geometry(g.geom); p != nil {
		return NewGeomSurfaceOfRevolution(p)
	}
	return nil
}

type GeomPlateSurface struct {
	geom *C.struct__geom_plate_surface_t
}

func NewGeomPlateSurface(geom *C.struct__geom_plate_surface_t) *GeomPlateSurface {
	g := &GeomPlateSurface{geom: geom}
	runtime.SetFinalizer(g, (*GeomPlateSurface).free)
	return g
}

func (g *GeomPlateSurface) Surface() *GeomSurface {
	return NewGeomSurface(C.geom_plate_surface_to_geom_surface(g.geom))
}

func (g *GeomPlateSurface) Geometry() *GeomGeometry {
	return NewGeomGeometry(C.geom_plate_surface_to_geometry(g.geom))
}

func (g *GeomPlateSurface) free() {
	C.geom_plate_surface_free(g.geom)
	g.geom = nil
}

func (g *GeomPlateSurface) Copy() *GeomPlateSurface {
	return NewGeomPlateSurface(C.geom_plate_surface_copy(g.geom))
}

func NewGeomPlateSurfaceFromGeometry(g *GeomGeometry) *GeomPlateSurface {
	if p := C.geom_plate_surface_from_geometry(g.geom); p != nil {
		return NewGeomPlateSurface(p)
	}
	return nil
}

type GeomVector struct {
	geom *C.struct__geom_vector_t
}

func NewGeomVector(geom *C.struct__geom_vector_t) *GeomVector {
	g := &GeomVector{geom: geom}
	runtime.SetFinalizer(g, (*GeomVector).free)
	return g
}

func (g *GeomVector) Geometry() *GeomGeometry {
	return NewGeomGeometry(C.geom_vector_to_geometry(g.geom))
}

func (g *GeomVector) free() {
	C.geom_vector_free(g.geom)
	g.geom = nil
}

func (g *GeomVector) Copy() *GeomVector {
	return NewGeomVector(C.geom_vector_copy(g.geom))
}

func NewGeomVectorFromGeometry(g *GeomGeometry) *GeomVector {
	if p := C.geom_vector_from_geometry(g.geom); p != nil {
		return NewGeomVector(p)
	}
	return nil
}

type GeomDirection struct {
	geom *C.struct__geom_direction_t
}

func NewGeomDirection(geom *C.struct__geom_direction_t) *GeomDirection {
	g := &GeomDirection{geom: geom}
	runtime.SetFinalizer(g, (*GeomDirection).free)
	return g
}

func (g *GeomDirection) Geometry() *GeomGeometry {
	return NewGeomGeometry(C.geom_direction_to_geometry(g.geom))
}

func (g *GeomDirection) free() {
	C.geom_direction_free(g.geom)
	g.geom = nil
}

func (g *GeomDirection) Copy() *GeomDirection {
	return NewGeomDirection(C.geom_direction_copy(g.geom))
}

func NewGeomDirectionFromGeometry(g *GeomGeometry) *GeomDirection {
	if p := C.geom_direction_from_geometry(g.geom); p != nil {
		return NewGeomDirection(p)
	}
	return nil
}

type GeomVectorWithMagnitude struct {
	geom *C.struct__geom_vector_with_magnitude_t
}

func NewGeomVectorWithMagnitude(geom *C.struct__geom_vector_with_magnitude_t) *GeomVectorWithMagnitude {
	g := &GeomVectorWithMagnitude{geom: geom}
	runtime.SetFinalizer(g, (*GeomVectorWithMagnitude).free)
	return g
}

func (g *GeomVectorWithMagnitude) Geometry() *GeomGeometry {
	return NewGeomGeometry(C.geom_vector_with_magnitude_to_geometry(g.geom))
}

func (g *GeomVectorWithMagnitude) free() {
	C.geom_vector_with_magnitude_free(g.geom)
	g.geom = nil
}

func (g *GeomVectorWithMagnitude) Copy() *GeomVectorWithMagnitude {
	return NewGeomVectorWithMagnitude(C.geom_vector_with_magnitude_copy(g.geom))
}

func NewGeomVectorWithMagnitudeFromGeometry(g *GeomGeometry) *GeomVectorWithMagnitude {
	if p := C.geom_vector_with_magnitude_from_geometry(g.geom); p != nil {
		return NewGeomVectorWithMagnitude(p)
	}
	return nil
}

type Geom2dGeometry struct {
	geom *C.struct__geom2d_geometry_t
}

func NewGeom2dGeometry(geom *C.struct__geom2d_geometry_t) *Geom2dGeometry {
	g := &Geom2dGeometry{geom: geom}
	runtime.SetFinalizer(g, (*Geom2dGeometry).free)
	return g
}

func (g *Geom2dGeometry) Type() int {
	return int(C.geom2d_geometry_type(g.geom))
}

func (g *Geom2dGeometry) free() {
	C.geom2d_geometry_free(g.geom)
	g.geom = nil
}

func (g *Geom2dGeometry) Copy() *Geom2dGeometry {
	return NewGeom2dGeometry(C.geom2d_geometry_copy(g.geom))
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
	return NewGeom2dGeometry(C.geom2d_mirror_with_point(g.geom, p.val))
}

func (g *Geom2dGeometry) MirroredWithAxis2d(p Axis2d) *Geom2dGeometry {
	return NewGeom2dGeometry(C.geom2d_mirror_with_axis2(g.geom, p.val))
}

func (g *Geom2dGeometry) Rotated(p Point2, ang float64) *Geom2dGeometry {
	return NewGeom2dGeometry(C.geom2d_rotate(g.geom, p.val, C.double(ang)))
}

func (g *Geom2dGeometry) Scaled(p Point2, s float64) *Geom2dGeometry {
	return NewGeom2dGeometry(C.geom2d_scale(g.geom, p.val, C.double(s)))
}

func (g *Geom2dGeometry) TranslatedWithVector(p Vector2) *Geom2dGeometry {
	return NewGeom2dGeometry(C.geom2d_translate_with_vector(g.geom, p.val))
}

func (g *Geom2dGeometry) TranslatedWithPoint(p1, p2 Point2) *Geom2dGeometry {
	return NewGeom2dGeometry(C.geom2d_translate_with_point(g.geom, p1.val, p2.val))
}

func (g *Geom2dGeometry) Transformed(t Trsf2d) *Geom2dGeometry {
	return NewGeom2dGeometry(C.geom2d_transform(g.geom, t.val))
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

func NewGeom2dTransformation(geom *C.struct__geom2d_transformation_t) *Geom2dTransformation {
	g := &Geom2dTransformation{geom: geom}
	runtime.SetFinalizer(g, (*Geom2dTransformation).free)
	return g
}

func (g *Geom2dTransformation) free() {
	C.geom2d_transformation_free(g.geom)
	g.geom = nil
}

func (g *Geom2dTransformation) Copy() *Geom2dTransformation {
	return NewGeom2dTransformation(C.geom2d_transformation_copy(g.geom))
}

type Geom2dAxisPlacement struct {
	geom *C.struct__geom2d_axis_placement_t
}

func NewGeom2dAxisPlacement(geom *C.struct__geom2d_axis_placement_t) *Geom2dAxisPlacement {
	g := &Geom2dAxisPlacement{geom: geom}
	runtime.SetFinalizer(g, (*Geom2dAxisPlacement).free)
	return g
}

func (g *Geom2dAxisPlacement) Geometry() *Geom2dGeometry {
	return NewGeom2dGeometry(C.geom2d_axis_placement_to_geometry(g.geom))
}

func (g *Geom2dAxisPlacement) free() {
	C.geom2d_axis_placement_free(g.geom)
	g.geom = nil
}

func (g *Geom2dAxisPlacement) Copy() *Geom2dAxisPlacement {
	return NewGeom2dAxisPlacement(C.geom2d_axis_placement_copy(g.geom))
}

func NewGeom2dAxisPlacementFromGeometry(g *Geom2dGeometry) *Geom2dAxisPlacement {
	if p := C.geom2d_axis_placement_from_geometry(g.geom); p != nil {
		return NewGeom2dAxisPlacement(p)
	}
	return nil
}

type Geom2dCurve struct {
	geom *C.struct__geom2d_curve_t
}

func NewGeom2dCurve(geom *C.struct__geom2d_curve_t) *Geom2dCurve {
	g := &Geom2dCurve{geom: geom}
	runtime.SetFinalizer(g, (*Geom2dCurve).free)
	return g
}

func (g *Geom2dCurve) Geometry() *Geom2dGeometry {
	return NewGeom2dGeometry(C.geom2d_curve_to_geometry(g.geom))
}

func (g *Geom2dCurve) free() {
	C.geom2d_curve_free(g.geom)
	g.geom = nil
}

func (g *Geom2dCurve) Copy() *Geom2dCurve {
	return NewGeom2dCurve(C.geom2d_curve_copy(g.geom))
}

func NewGeom2dCurveFromGeometry(g *Geom2dGeometry) *Geom2dCurve {
	if p := C.geom2d_curve_from_geometry(g.geom); p != nil {
		return NewGeom2dCurve(p)
	}
	return nil
}

type Geom2dBisectorCurve struct {
	geom *C.struct__geom2d_bisector_curve_t
}

func NewGeom2dBisectorCurve(geom *C.struct__geom2d_bisector_curve_t) *Geom2dBisectorCurve {
	g := &Geom2dBisectorCurve{geom: geom}
	runtime.SetFinalizer(g, (*Geom2dBisectorCurve).free)
	return g
}

func (g *Geom2dBisectorCurve) Curve() *Geom2dCurve {
	return NewGeom2dCurve(C.geom2d_bisector_curve_to_geom2d_curve(g.geom))
}

func (g *Geom2dBisectorCurve) Geometry() *Geom2dGeometry {
	return NewGeom2dGeometry(C.geom2d_bisector_curve_to_geometry(g.geom))
}

func (g *Geom2dBisectorCurve) free() {
	C.geom2d_bisector_curve_free(g.geom)
	g.geom = nil
}

func (g *Geom2dBisectorCurve) Copy() *Geom2dBisectorCurve {
	return NewGeom2dBisectorCurve(C.geom2d_bisector_curve_copy(g.geom))
}

func NewGeom2dBisectorCurveFromGeometry(g *Geom2dGeometry) *Geom2dBisectorCurve {
	if p := C.geom2d_bisector_curve_from_geometry(g.geom); p != nil {
		return NewGeom2dBisectorCurve(p)
	}
	return nil
}

type Geom2dBisectorBisecAna struct {
	geom *C.struct__geom2d_bezier_bisec_ana_curve_t
}

func NewGeom2dBisectorBisecAna(geom *C.struct__geom2d_bezier_bisec_ana_curve_t) *Geom2dBisectorBisecAna {
	g := &Geom2dBisectorBisecAna{geom: geom}
	runtime.SetFinalizer(g, (*Geom2dBisectorBisecAna).free)
	return g
}

func (g *Geom2dBisectorBisecAna) Curve() *Geom2dCurve {
	return NewGeom2dCurve(C.geom2d_bezier_bisec_ana_curve_to_geom2d_curve(g.geom))
}

func (g *Geom2dBisectorBisecAna) Geometry() *Geom2dGeometry {
	return NewGeom2dGeometry(C.geom2d_bezier_bisec_ana_curve_to_geometry(g.geom))
}

func (g *Geom2dBisectorBisecAna) free() {
	C.geom2d_bezier_bisec_ana_curve_free(g.geom)
	g.geom = nil
}

func (g *Geom2dBisectorBisecAna) Copy() *Geom2dBisectorBisecAna {
	return NewGeom2dBisectorBisecAna(C.geom2d_bezier_bisec_ana_curve_copy(g.geom))
}

func NewGeom2dBisectorBisecAnaFromGeometry(g *Geom2dGeometry) *Geom2dBisectorBisecAna {
	if p := C.geom2d_bezier_bisec_ana_curve_from_geometry(g.geom); p != nil {
		return NewGeom2dBisectorBisecAna(p)
	}
	return nil
}

type Geom2dBisectorBisecCC struct {
	geom *C.struct__geom2d_bezier_bisec_cc_curve_t
}

func NewGeom2dBisectorBisecCC(geom *C.struct__geom2d_bezier_bisec_cc_curve_t) *Geom2dBisectorBisecCC {
	g := &Geom2dBisectorBisecCC{geom: geom}
	runtime.SetFinalizer(g, (*Geom2dBisectorBisecCC).free)
	return g
}

func (g *Geom2dBisectorBisecCC) Curve() *Geom2dCurve {
	return NewGeom2dCurve(C.geom2d_bezier_bisec_cc_curve_to_geom2d_curve(g.geom))
}

func (g *Geom2dBisectorBisecCC) Geometry() *Geom2dGeometry {
	return NewGeom2dGeometry(C.geom2d_bezier_bisec_cc_curve_to_geometry(g.geom))
}

func (g *Geom2dBisectorBisecCC) free() {
	C.geom2d_bezier_bisec_cc_curve_free(g.geom)
	g.geom = nil
}

func (g *Geom2dBisectorBisecCC) Copy() *Geom2dBisectorBisecCC {
	return NewGeom2dBisectorBisecCC(C.geom2d_bezier_bisec_cc_curve_copy(g.geom))
}

func NewGeom2dBisectorBisecCCFromGeometry(g *Geom2dGeometry) *Geom2dBisectorBisecCC {
	if p := C.geom2d_bezier_bisec_cc_curve_from_geometry(g.geom); p != nil {
		return NewGeom2dBisectorBisecCC(p)
	}
	return nil
}

type Geom2dBisectorBisecPC struct {
	geom *C.struct__geom2d_bezier_bisec_pc_curve_t
}

func NewGeom2dBisectorBisecPC(geom *C.struct__geom2d_bezier_bisec_pc_curve_t) *Geom2dBisectorBisecPC {
	g := &Geom2dBisectorBisecPC{geom: geom}
	runtime.SetFinalizer(g, (*Geom2dBisectorBisecPC).free)
	return g
}

func (g *Geom2dBisectorBisecPC) Curve() *Geom2dCurve {
	return NewGeom2dCurve(C.geom2d_bezier_bisec_pc_curve_to_geom2d_curve(g.geom))
}

func (g *Geom2dBisectorBisecPC) Geometry() *Geom2dGeometry {
	return NewGeom2dGeometry(C.geom2d_bezier_bisec_pc_curve_to_geometry(g.geom))
}

func (g *Geom2dBisectorBisecPC) free() {
	C.geom2d_bezier_bisec_pc_curve_free(g.geom)
	g.geom = nil
}

func (g *Geom2dBisectorBisecPC) Copy() *Geom2dBisectorBisecPC {
	return NewGeom2dBisectorBisecPC(C.geom2d_bezier_bisec_pc_curve_copy(g.geom))
}

func NewGeom2dBisectorBisecPCFromGeometry(g *Geom2dGeometry) *Geom2dBisectorBisecPC {
	if p := C.geom2d_bezier_bisec_pc_curve_from_geometry(g.geom); p != nil {
		return NewGeom2dBisectorBisecPC(p)
	}
	return nil
}

type Geom2dBoundedCurve struct {
	geom *C.struct__geom2d_bounded_curve_t
}

func NewGeom2dBoundedCurve(geom *C.struct__geom2d_bounded_curve_t) *Geom2dBoundedCurve {
	g := &Geom2dBoundedCurve{geom: geom}
	runtime.SetFinalizer(g, (*Geom2dBoundedCurve).free)
	return g
}

func (g *Geom2dBoundedCurve) Curve() *Geom2dCurve {
	return NewGeom2dCurve(C.geom2d_bounded_curve_to_geom2d_curve(g.geom))
}

func (g *Geom2dBoundedCurve) Geometry() *Geom2dGeometry {
	return NewGeom2dGeometry(C.geom2d_bounded_curve_to_geometry(g.geom))
}

func (g *Geom2dBoundedCurve) free() {
	C.geom2d_bounded_curve_free(g.geom)
	g.geom = nil
}

func (g *Geom2dBoundedCurve) Copy() *Geom2dBoundedCurve {
	return NewGeom2dBoundedCurve(C.geom2d_bounded_curve_copy(g.geom))
}

func NewGeom2dBoundedCurveFromGeometry(g *Geom2dGeometry) *Geom2dBoundedCurve {
	if p := C.geom2d_bounded_curve_from_geometry(g.geom); p != nil {
		return NewGeom2dBoundedCurve(p)
	}
	return nil
}

type Geom2dBezierCurve struct {
	geom *C.struct__geom2d_bezier_curve_t
}

func NewGeom2dBezierCurve(geom *C.struct__geom2d_bezier_curve_t) *Geom2dBezierCurve {
	g := &Geom2dBezierCurve{geom: geom}
	runtime.SetFinalizer(g, (*Geom2dBezierCurve).free)
	return g
}

func (g *Geom2dBezierCurve) Curve() *Geom2dCurve {
	return NewGeom2dCurve(C.geom2d_bezier_curve_to_geom2d_curve(g.geom))
}

func (g *Geom2dBezierCurve) Geometry() *Geom2dGeometry {
	return NewGeom2dGeometry(C.geom2d_bezier_curve_to_geometry(g.geom))
}

func (g *Geom2dBezierCurve) free() {
	C.geom2d_bezier_curve_free(g.geom)
	g.geom = nil
}

func (g *Geom2dBezierCurve) Copy() *Geom2dBezierCurve {
	return NewGeom2dBezierCurve(C.geom2d_bezier_curve_copy(g.geom))
}

func NewGeom2dBezierCurveFromGeometry(g *Geom2dGeometry) *Geom2dBezierCurve {
	if p := C.geom2d_bezier_curve_from_geometry(g.geom); p != nil {
		return NewGeom2dBezierCurve(p)
	}
	return nil
}

type Geom2dBSplineCurve struct {
	geom *C.struct__geom2d_bspline_curve_t
}

func NewGeom2dBSplineCurve(geom *C.struct__geom2d_bspline_curve_t) *Geom2dBSplineCurve {
	g := &Geom2dBSplineCurve{geom: geom}
	runtime.SetFinalizer(g, (*Geom2dBSplineCurve).free)
	return g
}

func (g *Geom2dBSplineCurve) Curve() *Geom2dCurve {
	return NewGeom2dCurve(C.geom2d_bspline_curve_to_geom2d_curve(g.geom))
}

func (g *Geom2dBSplineCurve) Geometry() *Geom2dGeometry {
	return NewGeom2dGeometry(C.geom2d_bspline_curve_to_geometry(g.geom))
}

func (g *Geom2dBSplineCurve) free() {
	C.geom2d_bspline_curve_free(g.geom)
	g.geom = nil
}

func (g *Geom2dBSplineCurve) Copy() *Geom2dBSplineCurve {
	return NewGeom2dBSplineCurve(C.geom2d_bspline_curve_copy(g.geom))
}

func NewGeom2dBSplineCurveFromGeometry(g *Geom2dGeometry) *Geom2dBSplineCurve {
	if p := C.geom2d_bspline_curve_from_geometry(g.geom); p != nil {
		return NewGeom2dBSplineCurve(p)
	}
	return nil
}

type Geom2dTrimmedCurve struct {
	geom *C.struct__geom2d_trimmed_curve_t
}

func NewGeom2dTrimmedCurve(geom *C.struct__geom2d_trimmed_curve_t) *Geom2dTrimmedCurve {
	g := &Geom2dTrimmedCurve{geom: geom}
	runtime.SetFinalizer(g, (*Geom2dTrimmedCurve).free)
	return g
}

func (g *Geom2dTrimmedCurve) Curve() *Geom2dCurve {
	return NewGeom2dCurve(C.geom2d_trimmed_curve_to_geom2d_curve(g.geom))
}

func (g *Geom2dTrimmedCurve) Geometry() *Geom2dGeometry {
	return NewGeom2dGeometry(C.geom2d_trimmed_curve_to_geometry(g.geom))
}

func (g *Geom2dTrimmedCurve) free() {
	C.geom2d_trimmed_curve_free(g.geom)
	g.geom = nil
}

func (g *Geom2dTrimmedCurve) Copy() *Geom2dTrimmedCurve {
	return NewGeom2dTrimmedCurve(C.geom2d_trimmed_curve_copy(g.geom))
}

func NewGeom2dTrimmedCurveFromGeometry(g *Geom2dGeometry) *Geom2dTrimmedCurve {
	if p := C.geom2d_trimmed_curve_from_geometry(g.geom); p != nil {
		return NewGeom2dTrimmedCurve(p)
	}
	return nil
}

type Geom2dConic struct {
	geom *C.struct__geom2d_conic_t
}

func NewGeom2dConic(geom *C.struct__geom2d_conic_t) *Geom2dConic {
	g := &Geom2dConic{geom: geom}
	runtime.SetFinalizer(g, (*Geom2dConic).free)
	return g
}

func (g *Geom2dConic) Curve() *Geom2dCurve {
	return NewGeom2dCurve(C.geom2d_conic_to_geom2d_curve(g.geom))
}

func (g *Geom2dConic) Geometry() *Geom2dGeometry {
	return NewGeom2dGeometry(C.geom2d_conic_to_geometry(g.geom))
}

func (g *Geom2dConic) free() {
	C.geom2d_conic_free(g.geom)
	g.geom = nil
}

func (g *Geom2dConic) Copy() *Geom2dConic {
	return NewGeom2dConic(C.geom2d_conic_copy(g.geom))
}

func NewGeom2dConicFromGeometry(g *Geom2dGeometry) *Geom2dConic {
	if p := C.geom2d_conic_from_geometry(g.geom); p != nil {
		return NewGeom2dConic(p)
	}
	return nil
}

type Geom2dCircle struct {
	geom *C.struct__geom2d_circle_t
}

func NewGeom2dCircle(geom *C.struct__geom2d_circle_t) *Geom2dCircle {
	g := &Geom2dCircle{geom: geom}
	runtime.SetFinalizer(g, (*Geom2dCircle).free)
	return g
}

func (g *Geom2dCircle) Curve() *Geom2dCurve {
	return NewGeom2dCurve(C.geom2d_circle_to_geom2d_curve(g.geom))
}

func (g *Geom2dCircle) Geometry() *Geom2dGeometry {
	return NewGeom2dGeometry(C.geom2d_circle_to_geometry(g.geom))
}

func (g *Geom2dCircle) free() {
	C.geom2d_circle_free(g.geom)
	g.geom = nil
}

func (g *Geom2dCircle) Copy() *Geom2dCircle {
	return NewGeom2dCircle(C.geom2d_circle_copy(g.geom))
}

func NewGeom2dCircleFromGeometry(g *Geom2dGeometry) *Geom2dCircle {
	if p := C.geom2d_circle_from_geometry(g.geom); p != nil {
		return NewGeom2dCircle(p)
	}
	return nil
}

type Geom2dEllipse struct {
	geom *C.struct__geom2d_ellipse_t
}

func NewGeom2dEllipse(geom *C.struct__geom2d_ellipse_t) *Geom2dEllipse {
	g := &Geom2dEllipse{geom: geom}
	runtime.SetFinalizer(g, (*Geom2dEllipse).free)
	return g
}

func (g *Geom2dEllipse) Curve() *Geom2dCurve {
	return NewGeom2dCurve(C.geom2d_ellipse_to_geom2d_curve(g.geom))
}

func (g *Geom2dEllipse) Geometry() *Geom2dGeometry {
	return NewGeom2dGeometry(C.geom2d_ellipse_to_geometry(g.geom))
}

func (g *Geom2dEllipse) free() {
	C.geom2d_ellipse_free(g.geom)
	g.geom = nil
}

func (g *Geom2dEllipse) Copy() *Geom2dEllipse {
	return NewGeom2dEllipse(C.geom2d_ellipse_copy(g.geom))
}

func NewGeom2dEllipseFromGeometry(g *Geom2dGeometry) *Geom2dEllipse {
	if p := C.geom2d_ellipse_from_geometry(g.geom); p != nil {
		return NewGeom2dEllipse(p)
	}
	return nil
}

type Geom2dHyperbola struct {
	geom *C.struct__geom2d_hyperbola_t
}

func NewGeom2dHyperbola(geom *C.struct__geom2d_hyperbola_t) *Geom2dHyperbola {
	g := &Geom2dHyperbola{geom: geom}
	runtime.SetFinalizer(g, (*Geom2dHyperbola).free)
	return g
}

func (g *Geom2dHyperbola) Curve() *Geom2dCurve {
	return NewGeom2dCurve(C.geom2d_hyperbola_to_geom2d_curve(g.geom))
}

func (g *Geom2dHyperbola) Geometry() *Geom2dGeometry {
	return NewGeom2dGeometry(C.geom2d_hyperbola_to_geometry(g.geom))
}

func (g *Geom2dHyperbola) free() {
	C.geom2d_hyperbola_free(g.geom)
	g.geom = nil
}

func (g *Geom2dHyperbola) Copy() *Geom2dHyperbola {
	return NewGeom2dHyperbola(C.geom2d_hyperbola_copy(g.geom))
}

func NewGeom2dHyperbolaFromGeometry(g *Geom2dGeometry) *Geom2dHyperbola {
	if p := C.geom2d_hyperbola_from_geometry(g.geom); p != nil {
		return NewGeom2dHyperbola(p)
	}
	return nil
}

type Geom2dParabola struct {
	geom *C.struct__geom2d_parabola_t
}

func NewGeom2dParabola(geom *C.struct__geom2d_parabola_t) *Geom2dParabola {
	g := &Geom2dParabola{geom: geom}
	runtime.SetFinalizer(g, (*Geom2dParabola).free)
	return g
}

func (g *Geom2dParabola) Curve() *Geom2dCurve {
	return NewGeom2dCurve(C.geom2d_parabola_to_geom2d_curve(g.geom))
}

func (g *Geom2dParabola) Geometry() *Geom2dGeometry {
	return NewGeom2dGeometry(C.geom2d_parabola_to_geometry(g.geom))
}

func (g *Geom2dParabola) free() {
	C.geom2d_parabola_free(g.geom)
	g.geom = nil
}

func (g *Geom2dParabola) Copy() *Geom2dParabola {
	return NewGeom2dParabola(C.geom2d_parabola_copy(g.geom))
}

func NewGeom2dParabolaFromGeometry(g *Geom2dGeometry) *Geom2dParabola {
	if p := C.geom2d_parabola_from_geometry(g.geom); p != nil {
		return NewGeom2dParabola(p)
	}
	return nil
}

type Geom2dLine struct {
	geom *C.struct__geom2d_line_t
}

func NewGeom2dLine(geom *C.struct__geom2d_line_t) *Geom2dLine {
	g := &Geom2dLine{geom: geom}
	runtime.SetFinalizer(g, (*Geom2dLine).free)
	return g
}

func (g *Geom2dLine) Curve() *Geom2dCurve {
	return NewGeom2dCurve(C.geom2d_line_to_geom2d_curve(g.geom))
}

func (g *Geom2dLine) Geometry() *Geom2dGeometry {
	return NewGeom2dGeometry(C.geom2d_line_to_geometry(g.geom))
}

func (g *Geom2dLine) free() {
	C.geom2d_line_free(g.geom)
	g.geom = nil
}

func (g *Geom2dLine) Copy() *Geom2dLine {
	return NewGeom2dLine(C.geom2d_line_copy(g.geom))
}

func NewGeom2dLineFromGeometry(g *Geom2dGeometry) *Geom2dLine {
	if p := C.geom2d_line_from_geometry(g.geom); p != nil {
		return NewGeom2dLine(p)
	}
	return nil
}

type Geom2dOffsetCurve struct {
	geom *C.struct__geom2d_offset_curve_t
}

func NewGeom2dOffsetCurve(geom *C.struct__geom2d_offset_curve_t) *Geom2dOffsetCurve {
	g := &Geom2dOffsetCurve{geom: geom}
	runtime.SetFinalizer(g, (*Geom2dOffsetCurve).free)
	return g
}

func (g *Geom2dOffsetCurve) Curve() *Geom2dCurve {
	return NewGeom2dCurve(C.geom2d_offset_curve_to_geom2d_curve(g.geom))
}

func (g *Geom2dOffsetCurve) Geometry() *Geom2dGeometry {
	return NewGeom2dGeometry(C.geom2d_offset_curve_to_geometry(g.geom))
}

func (g *Geom2dOffsetCurve) free() {
	C.geom2d_offset_curve_free(g.geom)
	g.geom = nil
}

func (g *Geom2dOffsetCurve) Copy() *Geom2dOffsetCurve {
	return NewGeom2dOffsetCurve(C.geom2d_offset_curve_copy(g.geom))
}

func NewGeom2dOffsetCurveFromGeometry(g *Geom2dGeometry) *Geom2dOffsetCurve {
	if p := C.geom2d_offset_curve_from_geometry(g.geom); p != nil {
		return NewGeom2dOffsetCurve(p)
	}
	return nil
}

type Geom2dPoint struct {
	geom *C.struct__geom2d_point_t
}

func NewGeom2dPoint(geom *C.struct__geom2d_point_t) *Geom2dPoint {
	g := &Geom2dPoint{geom: geom}
	runtime.SetFinalizer(g, (*Geom2dPoint).free)
	return g
}

func (g *Geom2dPoint) Geometry() *Geom2dGeometry {
	return NewGeom2dGeometry(C.geom2d_point_to_geometry(g.geom))
}

func (g *Geom2dPoint) free() {
	C.geom2d_point_free(g.geom)
	g.geom = nil
}

func (g *Geom2dPoint) Copy() *Geom2dPoint {
	return NewGeom2dPoint(C.geom2d_point_copy(g.geom))
}

func NewGeom2dPointFromGeometry(g *Geom2dGeometry) *Geom2dPoint {
	if p := C.geom2d_point_from_geometry(g.geom); p != nil {
		return NewGeom2dPoint(p)
	}
	return nil
}

type Geom2dCartesianPoint struct {
	geom *C.struct__geom2d_cartesian_point_t
}

func NewGeom2dCartesianPoint(geom *C.struct__geom2d_cartesian_point_t) *Geom2dCartesianPoint {
	g := &Geom2dCartesianPoint{geom: geom}
	runtime.SetFinalizer(g, (*Geom2dCartesianPoint).free)
	return g
}

func (g *Geom2dCartesianPoint) Geometry() *Geom2dGeometry {
	return NewGeom2dGeometry(C.geom2d_cartesian_point_to_geometry(g.geom))
}

func (g *Geom2dCartesianPoint) free() {
	C.geom2d_cartesian_point_free(g.geom)
	g.geom = nil
}

func (g *Geom2dCartesianPoint) Copy() *Geom2dCartesianPoint {
	return NewGeom2dCartesianPoint(C.geom2d_cartesian_point_copy(g.geom))
}

func NewGeom2dCartesianPointFromGeometry(g *Geom2dGeometry) *Geom2dCartesianPoint {
	if p := C.geom2d_cartesian_point_from_geometry(g.geom); p != nil {
		return NewGeom2dCartesianPoint(p)
	}
	return nil
}

type Geom2dVector struct {
	geom *C.struct__geom2d_vector_t
}

func NewGeom2dVector(geom *C.struct__geom2d_vector_t) *Geom2dVector {
	g := &Geom2dVector{geom: geom}
	runtime.SetFinalizer(g, (*Geom2dVector).free)
	return g
}

func (g *Geom2dVector) Geometry() *Geom2dGeometry {
	return NewGeom2dGeometry(C.geom2d_vector_to_geometry(g.geom))
}

func (g *Geom2dVector) free() {
	C.geom2d_vector_free(g.geom)
	g.geom = nil
}

func (g *Geom2dVector) Copy() *Geom2dVector {
	return NewGeom2dVector(C.geom2d_vector_copy(g.geom))
}

func NewGeom2dVectorFromGeometry(g *Geom2dGeometry) *Geom2dVector {
	if p := C.geom2d_vector_from_geometry(g.geom); p != nil {
		return NewGeom2dVector(p)
	}
	return nil
}

type Geom2dDirection struct {
	geom *C.struct__geom2d_direction_t
}

func NewGeom2dDirection(geom *C.struct__geom2d_direction_t) *Geom2dDirection {
	g := &Geom2dDirection{geom: geom}
	runtime.SetFinalizer(g, (*Geom2dDirection).free)
	return g
}

func (g *Geom2dDirection) Geometry() *Geom2dGeometry {
	return NewGeom2dGeometry(C.geom2d_direction_to_geometry(g.geom))
}

func (g *Geom2dDirection) free() {
	C.geom2d_direction_free(g.geom)
	g.geom = nil
}

func (g *Geom2dDirection) Copy() *Geom2dDirection {
	return NewGeom2dDirection(C.geom2d_direction_copy(g.geom))
}

func NewGeom2dDirectionFromGeometry(g *Geom2dGeometry) *Geom2dDirection {
	if p := C.geom2d_direction_from_geometry(g.geom); p != nil {
		return NewGeom2dDirection(p)
	}
	return nil
}

type Geom2dVectorWithMagnitude struct {
	geom *C.struct__geom2d_vector_with_magnitude_t
}

func NewGeom2dVectorWithMagnitude(geom *C.struct__geom2d_vector_with_magnitude_t) *Geom2dVectorWithMagnitude {
	g := &Geom2dVectorWithMagnitude{geom: geom}
	runtime.SetFinalizer(g, (*Geom2dVectorWithMagnitude).free)
	return g
}

func (g *Geom2dVectorWithMagnitude) Geometry() *Geom2dGeometry {
	return NewGeom2dGeometry(C.geom2d_vector_with_magnitude_to_geometry(g.geom))
}

func (g *Geom2dVectorWithMagnitude) free() {
	C.geom2d_vector_with_magnitude_free(g.geom)
	g.geom = nil
}

func (g *Geom2dVectorWithMagnitude) Copy() *Geom2dVectorWithMagnitude {
	return NewGeom2dVectorWithMagnitude(C.geom2d_vector_with_magnitude_copy(g.geom))
}

func NewGeom2dVectorWithMagnitudeFromGeometry(g *Geom2dGeometry) *Geom2dVectorWithMagnitude {
	if p := C.geom2d_vector_with_magnitude_from_geometry(g.geom); p != nil {
		return NewGeom2dVectorWithMagnitude(p)
	}
	return nil
}
