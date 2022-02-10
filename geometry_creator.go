package topo

/*
#include <stdlib.h>
#include "geometry_c_api.h"
#cgo CFLAGS: -I ./libs
#cgo linux CXXFLAGS: -I ./libs -std=gnu++14
#cgo darwin CXXFLAGS: -I ./libs -std=gnu++14
#cgo windows CXXFLAGS:  -I ./libs -std=gnu++14
*/
import "C"
import "unsafe"

func GeomMakeAxis1Placement(a Axis1) *GeomAxis1Placement {
	return &GeomAxis1Placement{inner: &innerGeomAxis1Placement{geom: C.geom_make_axis1_placement(a.val)}}
}

func GeomMakeAxis1PlacementFromPointDir(p Point3, d Dir3) *GeomAxis1Placement {
	return &GeomAxis1Placement{inner: &innerGeomAxis1Placement{geom: C.geom_make_axis1_placement_of_point_dir(p.val, d.val)}}
}

func GeomMakeAxis2Placement(a Axis2) *GeomAxis2Placement {
	return &GeomAxis2Placement{inner: &innerGeomAxis2Placement{geom: C.geom_make_axis2_placement(a.val)}}
}

func GeomMakeAxis2PlacementForPointNVX(p Point3, n Dir3, vx Dir3) *GeomAxis2Placement {
	return &GeomAxis2Placement{inner: &innerGeomAxis2Placement{geom: C.geom_make_axis2_placement_of_point_nvx(p.val, n.val, vx.val)}}
}

func GeomMakeBezierCurve(poles []Point3) *GeomBezierCurve {
	in := make([]C.struct__pnt3d_t, len(poles))
	for i := range poles {
		in[i] = poles[i].val
	}
	return &GeomBezierCurve{inner: &innerGeomBezierCurve{geom: C.geom_make_bezier_curve(&in[0], C.int(len(poles)))}}
}

func GeomMakeBezierCurveFromWeight(poles []Point3, Weights []float64) *GeomBezierCurve {
	in := make([]C.struct__pnt3d_t, len(poles))
	for i := range poles {
		in[i] = poles[i].val
	}
	return &GeomBezierCurve{inner: &innerGeomBezierCurve{geom: C.geom_make_bezier_curve_from_weight(&in[0], (*C.double)(unsafe.Pointer(&Weights[0])), C.int(len(poles)))}}
}

func GeomMakeBSplineCurve(poles []Point3, Knots []float64, Multiplicities []int, Degree int, Periodic bool) *GeomBSplineCurve {
	in := make([]C.struct__pnt3d_t, len(poles))
	for i := range poles {
		in[i] = poles[i].val
	}
	return &GeomBSplineCurve{inner: &innerGeomBSplineCurve{geom: C.geom_make_bspline_curve(&in[0], (*C.double)(unsafe.Pointer(&Knots[0])), (*C.int)(unsafe.Pointer(&Multiplicities[0])), C.int(len(poles)), C.int(Degree), C.bool(Periodic))}}
}

func GeomMakeBSplineCurveFromWeight(poles []Point3, weights []float64, Knots []float64, Multiplicities []int, Degree int, Periodic bool) *GeomBSplineCurve {
	in := make([]C.struct__pnt3d_t, len(poles))
	for i := range poles {
		in[i] = poles[i].val
	}
	return &GeomBSplineCurve{inner: &innerGeomBSplineCurve{geom: C.geom_make_bspline_curve_from_weight(&in[0], (*C.double)(unsafe.Pointer(&weights[0])), (*C.double)(unsafe.Pointer(&Knots[0])), (*C.int)(unsafe.Pointer(&Multiplicities[0])), C.int(len(poles)), C.int(Degree), C.bool(Periodic), C.bool(false))}}
}

func GeomMakeBezierSurface(poles [][]Point3) *GeomBezierSurface {
	row := len(poles)
	col := len(poles[0])
	in := make([]C.struct__pnt3d_t, col*row)
	for i := 0; i < row; i++ {
		for j := 0; j < col; j++ {
			in[i*col+j] = poles[i][j].val
		}
	}
	return &GeomBezierSurface{inner: &innerGeomBezierSurface{geom: C.geom_make_bezier_surface(&in[0], C.int(row), C.int(col))}}
}

func GeomMakeBezierSurfaceFromWeight(poles [][]Point3, weights [][]float64) *GeomBezierSurface {
	row := len(poles)
	col := len(poles[0])
	in := make([]C.struct__pnt3d_t, col*row)
	inw := make([]C.double, col*row)

	for i := 0; i < row; i++ {
		for j := 0; j < col; j++ {
			in[i*col+j] = poles[i][j].val
			inw[i*col+j] = C.double(weights[j][i])
		}
	}
	return &GeomBezierSurface{inner: &innerGeomBezierSurface{geom: C.geom_make_bezier_surface_from_weight(&in[0], &inw[0], C.int(row), C.int(col))}}
}

func GeomMakeBSplineSurface(poles [][]Point3, UKnots, VKnots []float64, UMults, VMults []int, UDegree, VDegree int, UPeriodic, VPeriodic bool) *GeomBSplineSurface {
	row := len(poles)
	col := len(poles[0])
	in := make([]C.struct__pnt3d_t, col*row)
	for i := 0; i < row; i++ {
		for j := 0; j < col; j++ {
			if j < len(poles[i]) {
				in[i*col+j] = poles[i][j].val
			}
		}
	}
	return &GeomBSplineSurface{inner: &innerGeomBSplineSurface{geom: C.geom_make_bspline_surface(&in[0], (*C.double)(unsafe.Pointer(&UKnots[0])), (*C.double)(unsafe.Pointer(&VKnots[0])), (*C.int)(unsafe.Pointer(&UMults[0])), (*C.int)(unsafe.Pointer(&VMults[0])), C.int(row), C.int(col), C.int(len(UKnots)), C.int(len(VKnots)), C.int(UDegree), C.int(VDegree), C.bool(UPeriodic), C.bool(VPeriodic))}}
}

func GeomMakeBSplineSurfaceFromWeight(poles [][]Point3, weights [][]float64, UKnots, VKnots []float64, UMults, VMults []int, UDegree, VDegree int, UPeriodic, VPeriodic bool) *GeomBSplineSurface {
	row := len(poles)
	col := len(poles[0])
	in := make([]C.struct__pnt3d_t, col*row)
	inw := make([]C.double, col*row)

	for i := 0; i < row; i++ {
		for j := 0; j < col; j++ {
			if j < len(poles[i]) {
				in[i*col+j] = poles[i][j].val
				inw[i*col+j] = C.double(weights[j][i])
			}
		}
	}
	return &GeomBSplineSurface{inner: &innerGeomBSplineSurface{geom: C.geom_make_bspline_surface_from_weight(&in[0], (*C.double)(unsafe.Pointer(&inw[0])), (*C.double)(unsafe.Pointer(&UKnots[0])), (*C.double)(unsafe.Pointer(&VKnots[0])), (*C.int)(unsafe.Pointer(&UMults[0])), (*C.int)(unsafe.Pointer(&VMults[0])), C.int(row), C.int(col), C.int(len(UKnots)), C.int(len(VKnots)), C.int(UDegree), C.int(VDegree), C.bool(UPeriodic), C.bool(VPeriodic))}}
}

func GeomMakeRectangularTrimmedSurfaceFromLRUD(s *GeomSurface, u1, u2, v1, v2 float64, UTrim, Sense bool) *GeomRectangularTrimmedSurface {
	return &GeomRectangularTrimmedSurface{inner: &innerGeomRectangularTrimmedSurface{geom: C.geom_make_rectangular_trimmed_surface_from_lrud(s.inner.geom, C.double(u1), C.double(u2), C.double(v1), C.double(v2), C.bool(UTrim), C.bool(Sense))}}
}

func GeomMakeRectangularTrimmedSurface(s *GeomSurface, Param1, Param2 float64, UTrim, Sense bool) *GeomRectangularTrimmedSurface {
	return &GeomRectangularTrimmedSurface{inner: &innerGeomRectangularTrimmedSurface{geom: C.geom_make_rectangular_trimmed_surface(s.inner.geom, C.double(Param1), C.double(Param2), C.bool(UTrim), C.bool(Sense))}}
}

func GeomMakeSurfaceOfLinearExtrusion(c *GeomCurve, V Dir3) *GeomSurfaceOfLinearExtrusion {
	return &GeomSurfaceOfLinearExtrusion{inner: &innerGeomSurfaceOfLinearExtrusion{geom: C.geom_make_surface_of_linear_extrusion(c.inner.geom, V.val)}}
}

func GeomMakeSurfaceOfRevolution(c *GeomCurve, V Axis1) *GeomSurfaceOfRevolution {
	return &GeomSurfaceOfRevolution{inner: &innerGeomSurfaceOfRevolution{geom: C.geom_make_surface_of_revolution_extrusion(c.inner.geom, V.val)}}
}

func GeomMakePlateSurface(s *GeomSurface, p *Plate) *GeomPlateSurface {
	return &GeomPlateSurface{inner: &innerGeomPlateSurface{geom: C.geom_make_plate_surface(s.inner.geom, p.inner.val)}}
}

func GeomMakeDirection(x, y, z float64) *GeomDirection {
	return &GeomDirection{inner: &innerGeomDirection{geom: C.geom_make_direction(C.double(x), C.double(y), C.double(z))}}
}

func GeomMakeDirectionFromDir(V Dir3) *GeomDirection {
	return &GeomDirection{inner: &innerGeomDirection{geom: C.geom_make_direction_with_dir(V.val)}}
}

func GeomMakeVectorWithMagnitudeFromVector(V Vector3) *GeomVectorWithMagnitude {
	return &GeomVectorWithMagnitude{inner: &innerGeomVectorWithMagnitude{geom: C.geom_make_vector_with_magnitude_with_vector(V.val)}}
}

func GeomMakeVectorWithMagnitude(x, y, z float64) *GeomVectorWithMagnitude {
	return &GeomVectorWithMagnitude{inner: &innerGeomVectorWithMagnitude{geom: C.geom_make_vector_with_magnitude_with_xyz(C.double(x), C.double(y), C.double(z))}}
}

func GeomMakeVectorWithMagnitudeFromPoint(p1, p2 Point3) *GeomVectorWithMagnitude {
	return &GeomVectorWithMagnitude{inner: &innerGeomVectorWithMagnitude{geom: C.geom_make_vector_with_magnitude_with_point(p1.val, p2.val)}}
}

func GeomMakeArcOfCircleTwoPoint(c *Circ, P1, P2 Point3, sense bool) *GeomTrimmedCurve {
	return &GeomTrimmedCurve{inner: &innerGeomTrimmedCurve{geom: C.geom_make_arc_of_circle_two_point(c.val, P1.val, P2.val, C.bool(sense))}}
}

func GeomMakeArcOfPoint(P1, P2, P3 Point3) *GeomTrimmedCurve {
	return &GeomTrimmedCurve{inner: &innerGeomTrimmedCurve{geom: C.geom_make_arc_of_point(P1.val, P2.val, P3.val)}}
}

func GeomMakeArcOfTwoPointsVector(P1 Point3, V Vector3, P2 Point3) *GeomTrimmedCurve {
	return &GeomTrimmedCurve{inner: &innerGeomTrimmedCurve{geom: C.geom_make_arc_of_two_points_vector(P1.val, V.val, P2.val)}}
}

func GeomMakeArcOfEllipseeTwoAngles(e Elips, Alpha1, Alpha2 float64, sense bool) *GeomTrimmedCurve {
	return &GeomTrimmedCurve{inner: &innerGeomTrimmedCurve{geom: C.geom_make_arc_of_ellipsee_two_angles(e.val, C.double(Alpha1), C.double(Alpha2), C.bool(sense))}}
}

func GeomMakeArcOfEllipseeAngles(e Elips, p Point3, Alpha float64, sense bool) *GeomTrimmedCurve {
	return &GeomTrimmedCurve{inner: &innerGeomTrimmedCurve{geom: C.geom_make_arc_of_ellipse_angle(e.val, p.val, C.double(Alpha), C.bool(sense))}}
}

func GeomMakeArcOfEllipseePoint(e Elips, P1, P2 Point3, sense bool) *GeomTrimmedCurve {
	return &GeomTrimmedCurve{inner: &innerGeomTrimmedCurve{geom: C.geom_make_arc_of_ellipse_point(e.val, P1.val, P2.val, C.bool(sense))}}
}

func GeomMakeArcOfHyperbolaTwoAngles(e Hyperbola, Alpha1, Alpha2 float64, sense bool) *GeomTrimmedCurve {
	return &GeomTrimmedCurve{inner: &innerGeomTrimmedCurve{geom: C.geom_make_arc_of_hyperbola_two_angles(e.val, C.double(Alpha1), C.double(Alpha2), C.bool(sense))}}
}

func GeomMakeArcOfHyperbolaAngles(e Hyperbola, p Point3, Alpha float64, sense bool) *GeomTrimmedCurve {
	return &GeomTrimmedCurve{inner: &innerGeomTrimmedCurve{geom: C.geom_make_arc_of_hyperbola_angle(e.val, p.val, C.double(Alpha), C.bool(sense))}}
}

func GeomMakeArcOfHyperbolaPoint(e Hyperbola, P1, P2 Point3, sense bool) *GeomTrimmedCurve {
	return &GeomTrimmedCurve{inner: &innerGeomTrimmedCurve{geom: C.geom_make_arc_of_hyperbola_point(e.val, P1.val, P2.val, C.bool(sense))}}
}

func GeomMakeArcOfParabolaTwoAngles(e Parabola, Alpha1, Alpha2 float64, sense bool) *GeomTrimmedCurve {
	return &GeomTrimmedCurve{inner: &innerGeomTrimmedCurve{geom: C.geom_make_arc_of_parabola_two_angles(e.val, C.double(Alpha1), C.double(Alpha2), C.bool(sense))}}
}

func GeomMakeArcOfParabolaAngles(e Parabola, p Point3, Alpha float64, sense bool) *GeomTrimmedCurve {
	return &GeomTrimmedCurve{inner: &innerGeomTrimmedCurve{geom: C.geom_make_arc_of_parabola_angle(e.val, p.val, C.double(Alpha), C.bool(sense))}}
}

func GeomMakeArcOfParabolaPoint(e Parabola, P1, P2 Point3, sense bool) *GeomTrimmedCurve {
	return &GeomTrimmedCurve{inner: &innerGeomTrimmedCurve{geom: C.geom_make_arc_of_parabola_point(e.val, P1.val, P2.val, C.bool(sense))}}
}

func GeomMakeCircle(e Circ) *GeomCircle {
	return &GeomCircle{inner: &innerGeomCircle{geom: C.geom_make_circle(e.val)}}
}

func GeomMakeCircleOfAxis2(A2 Axis2, Radius float64) *GeomCircle {
	return &GeomCircle{inner: &innerGeomCircle{geom: C.geom_make_circle_of_axis2(A2.val, C.double(Radius))}}
}

func GeomMakeCircleOfDist(e Circ, Dist float64) *GeomCircle {
	return &GeomCircle{inner: &innerGeomCircle{geom: C.geom_make_circle_of_dist(e.val, C.double(Dist))}}
}

func GeomMakeCircleOfPoint(e Circ, p Point3) *GeomCircle {
	return &GeomCircle{inner: &innerGeomCircle{geom: C.geom_make_circle_of_point(e.val, p.val)}}
}

func GeomMakeCircleOfThreePoint(p1, p2, p3 Point3) *GeomCircle {
	return &GeomCircle{inner: &innerGeomCircle{geom: C.geom_make_circle_of_three_point(p1.val, p2.val, p3.val)}}
}

func GeomMakeCircleOfCenterNorm(center Point3, Norm Dir3, Radius float64) *GeomCircle {
	return &GeomCircle{inner: &innerGeomCircle{geom: C.geom_make_circle_of_center_norm(center.val, Norm.val, C.double(Radius))}}
}

func GeomMakeCircleOfCenterAxis(center, PtAxis Point3, Radius float64) *GeomCircle {
	return &GeomCircle{inner: &innerGeomCircle{geom: C.geom_make_circle_center_axis(center.val, PtAxis.val, C.double(Radius))}}
}

func GeomMakeCircleOfAxis1(a Axis1, Radius float64) *GeomCircle {
	return &GeomCircle{inner: &innerGeomCircle{geom: C.geom_make_circle_of_axis1(a.val, C.double(Radius))}}
}

func GeomMakeEllipse(E Elips) *GeomEllipse {
	return &GeomEllipse{inner: &innerGeomEllipse{geom: C.geom_make_ellipse(E.val)}}
}

func GeomMakeEllipseOfAxis2(A2 Axis2, MajorRadius, MinorRadius float64) *GeomEllipse {
	return &GeomEllipse{inner: &innerGeomEllipse{geom: C.geom_make_ellipse_of_axis2(A2.val, C.double(MajorRadius), C.double(MinorRadius))}}
}

func GeomMakeEllipseOfPointCenter(S1, S2, Center Point3) *GeomEllipse {
	return &GeomEllipse{inner: &innerGeomEllipse{geom: C.geom_make_ellipse_point_center(S1.val, S2.val, Center.val)}}
}

func GeomMakeHyperbola(E Hyperbola) *GeomHyperbola {
	return &GeomHyperbola{inner: &innerGeomHyperbola{geom: C.geom_make_hyperbola(E.val)}}
}

func GeomMakeHyperbolaOfAxis2(A2 Axis2, MajorRadius, MinorRadius float64) *GeomHyperbola {
	return &GeomHyperbola{inner: &innerGeomHyperbola{geom: C.geom_make_hyperbola_of_axis2(A2.val, C.double(MajorRadius), C.double(MinorRadius))}}
}

func GeomMakeHyperbolaOfPointCenter(S1, S2, Center Point3) *GeomHyperbola {
	return &GeomHyperbola{inner: &innerGeomHyperbola{geom: C.geom_make_hyperbola_point_center(S1.val, S2.val, Center.val)}}
}

func GeomMakeConicalSurfaceOfAxis2(A2 Axis2, Ang, Radius float64) *GeomConicalSurface {
	return &GeomConicalSurface{inner: &innerGeomConicalSurface{geom: C.geom_make_conical_surface_axis2(A2.val, C.double(Ang), C.double(Radius))}}
}

func GeomMakeConicalSurface(c Cone) *GeomConicalSurface {
	return &GeomConicalSurface{inner: &innerGeomConicalSurface{geom: C.geom_make_conical_surface(c.val)}}
}

func GeomMakeConicalSurfaceOfPoint(p1, p2, p3, p4 Point3) *GeomConicalSurface {
	return &GeomConicalSurface{inner: &innerGeomConicalSurface{geom: C.geom_make_conical_surface_of_point(p1.val, p2.val, p3.val, p4.val)}}
}

func GeomMakeConicalSurfaceOfPointRadius(p1, p2 Point3, R1, R2 float64) *GeomConicalSurface {
	return &GeomConicalSurface{inner: &innerGeomConicalSurface{geom: C.geom_make_conical_surface_of_point_radius(p1.val, p2.val, C.double(R1), C.double(R2))}}
}

func GeomMakeCylindricalSurface(cy Cylinder) *GeomCylindricalSurface {
	return &GeomCylindricalSurface{inner: &innerGeomCylindricalSurface{geom: C.geom_make_cylindrical_surface(cy.val)}}
}

func GeomMakeCylindricalSurfaceOfAxis2(A2 Axis2, Radius float64) *GeomCylindricalSurface {
	return &GeomCylindricalSurface{inner: &innerGeomCylindricalSurface{geom: C.geom_make_cylindrical_surface_of_axis2(A2.val, C.double(Radius))}}
}

func GeomMakeCylindricalSurfaceOfPoint(cy Cylinder, p Point3) *GeomCylindricalSurface {
	return &GeomCylindricalSurface{inner: &innerGeomCylindricalSurface{geom: C.geom_make_cylindrical_surface_of_point(cy.val, p.val)}}
}

func GeomMakeCylindricalSurfaceOfDist(cy Cylinder, dist float64) *GeomCylindricalSurface {
	return &GeomCylindricalSurface{inner: &innerGeomCylindricalSurface{geom: C.geom_make_cylindrical_surface_of_dist(cy.val, C.double(dist))}}
}

func GeomMakeCylindricalSurfaceOfThreePoint(p1, p2, p3 Point3) *GeomCylindricalSurface {
	return &GeomCylindricalSurface{inner: &innerGeomCylindricalSurface{geom: C.geom_make_cylindrical_surface_of_three_point(p1.val, p2.val, p3.val)}}
}

func GeomMakeCylindricalSurfaceOfAxisRadius(a Axis1, Radius float64) *GeomCylindricalSurface {
	return &GeomCylindricalSurface{inner: &innerGeomCylindricalSurface{geom: C.geom_make_cylindrical_surface_of_axis_radius(a.val, C.double(Radius))}}
}

func GeomMakeCylindricalSurfaceOfCirc(cy Circ) *GeomCylindricalSurface {
	return &GeomCylindricalSurface{inner: &innerGeomCylindricalSurface{geom: C.geom_make_cylindrical_surface_of_circ(cy.val)}}
}

func GeomMakeLine(l Line) *GeomLine {
	return &GeomLine{inner: &innerGeomLine{geom: C.geom_make_line(l.val)}}
}

func GeomMakeLineOfAxis1(a Axis1) *GeomLine {
	return &GeomLine{inner: &innerGeomLine{geom: C.geom_make_line_of_axis1(a.val)}}
}

func GeomMakeLineOfPointDir(p Point3, v Dir3) *GeomLine {
	return &GeomLine{inner: &innerGeomLine{geom: C.geom_make_line_of_point_dir(p.val, v.val)}}
}

func GeomMakeLineOfPoint(l Line, p Point3) *GeomLine {
	return &GeomLine{inner: &innerGeomLine{geom: C.geom_make_line_point(l.val, p.val)}}
}

func GeomMakeLineOfTwoPoint(p1, p2 Point3) *GeomLine {
	return &GeomLine{inner: &innerGeomLine{geom: C.geom_make_line_of_two_point(p1.val, p2.val)}}
}

func GeomMakeMirrorOfPoint(p Point3) *GeomTransformation {
	return NewGeomTransformation(C.geom_make_mirror_of_point(p.val))
}

func GeomMakeMirrorOfAxis1(a Axis1) *GeomTransformation {
	return NewGeomTransformation(C.geom_make_mirror_of_axis1(a.val))
}

func GeomMakeMirrorOfLine(l Line) *GeomTransformation {
	return NewGeomTransformation(C.geom_make_mirror_of_line(l.val))
}

func GeomMakeMirrorOfPointDir(p Point3, d Dir3) *GeomTransformation {
	return NewGeomTransformation(C.geom_make_mirror_of_point_dir(p.val, d.val))
}

func GeomMakeMirrorOfPlane(p Plane) *GeomTransformation {
	return NewGeomTransformation(C.geom_make_mirror_of_plane(p.val))
}

func GeomMakeMirrorOfAxis2(p Axis2) *GeomTransformation {
	return NewGeomTransformation(C.geom_make_mirror_of_axis2(p.val))
}

func GeomMakeRotationOfLine(l Line, ang float64) *GeomTransformation {
	return NewGeomTransformation(C.geom_make_rotation_of_line(l.val, C.double(ang)))
}

func GeomMakeRotationOfAxis1(l Axis1, ang float64) *GeomTransformation {
	return NewGeomTransformation(C.geom_make_rotation_of_axis1(l.val, C.double(ang)))
}

func GeomMakeRotationOfPointDir(p Point3, d Dir3, ang float64) *GeomTransformation {
	return NewGeomTransformation(C.geom_make_rotation_of_point_dir(p.val, d.val, C.double(ang)))
}

func GeomMakeTranslationOfVector(v Vector3) *GeomTransformation {
	return NewGeomTransformation(C.geom_make_translation_of_vect(v.val))
}

func GeomMakeTranslationOfTwoPoint(p1, p2 Point3) *GeomTransformation {
	return NewGeomTransformation(C.geom_make_translation_of_two_point(p1.val, p2.val))
}

func GeomMakeScaleOfPoint(p Point3, s float64) *GeomTransformation {
	return NewGeomTransformation(C.geom_make_scale_of_point_scale(p.val, C.double(s)))
}

func GeomMakePlane(p Plane) *GeomPlane {
	return &GeomPlane{inner: &innerGeomPlane{geom: C.geom_make_plane(p.val)}}
}

func GeomMakePlaneOfPointDir(p Point3, d Dir3) *GeomPlane {
	return &GeomPlane{inner: &innerGeomPlane{geom: C.geom_make_plane_of_point_dir(p.val, d.val)}}
}

func GeomMakePlaneOfLRUD(a, b, c, d float64) *GeomPlane {
	return &GeomPlane{inner: &innerGeomPlane{geom: C.geom_make_plane_of_lrud(C.double(a), C.double(b), C.double(c), C.double(d))}}
}

func GeomMakePlaneOfPoint(pl Plane, p Point3) *GeomPlane {
	return &GeomPlane{inner: &innerGeomPlane{geom: C.geom_make_plane_of_point(pl.val, p.val)}}
}

func GeomMakePlaneOfDist(pl Plane, d float64) *GeomPlane {
	return &GeomPlane{inner: &innerGeomPlane{geom: C.geom_make_plane_of_dist(pl.val, C.double(d))}}
}

func GeomMakePlaneOfThreePoint(p1, p2, p3 Point3) *GeomPlane {
	return &GeomPlane{inner: &innerGeomPlane{geom: C.geom_make_plane_of_three_point(p1.val, p2.val, p3.val)}}
}

func GeomMakePlaneOfAxis1(a Axis1) *GeomPlane {
	return &GeomPlane{inner: &innerGeomPlane{geom: C.geom_make_plane_of_axis1(a.val)}}
}

func GeomMakeSegmentOfTwoPoint(p1, p2 Point3) *GeomTrimmedCurve {
	return &GeomTrimmedCurve{inner: &innerGeomTrimmedCurve{geom: C.geom_make_segment_of_two_point(p1.val, p2.val)}}
}

func GeomMakeSegmentOfLineU(l Line, U1, U2 float64) *GeomTrimmedCurve {
	return &GeomTrimmedCurve{inner: &innerGeomTrimmedCurve{geom: C.geom_make_segment_of_line_u(l.val, C.double(U1), C.double(U2))}}
}

func GeomMakeSegmentOfLinePoint(l Line, p Point3, Ulast float64) *GeomTrimmedCurve {
	return &GeomTrimmedCurve{inner: &innerGeomTrimmedCurve{geom: C.geom_make_segment_of_line_point(l.val, p.val, C.double(Ulast))}}
}

func GeomMakeSegmentOfPoint(l Line, p1, p2 Point3) *GeomTrimmedCurve {
	return &GeomTrimmedCurve{inner: &innerGeomTrimmedCurve{geom: C.geom_make_segment_of_point(l.val, p1.val, p2.val)}}
}

func GeomMakeTrimmedConeOfPoint(p1, p2, p3, p4 Point3) *GeomRectangularTrimmedSurface {
	return &GeomRectangularTrimmedSurface{inner: &innerGeomRectangularTrimmedSurface{geom: C.geom_make_trimmed_cone_of_point(p1.val, p2.val, p3.val, p3.val)}}
}

func GeomMakeTrimmedConeOfPointRadius(p1, p2 Point3, R1, R2 float64) *GeomRectangularTrimmedSurface {
	return &GeomRectangularTrimmedSurface{inner: &innerGeomRectangularTrimmedSurface{geom: C.geom_make_trimmed_cone_of_point_radius(p1.val, p2.val, C.double(R1), C.double(R2))}}
}

func GeomMakeTrimmedCylinderOfPoint(p1, p2, p3 Point3) *GeomRectangularTrimmedSurface {
	return &GeomRectangularTrimmedSurface{inner: &innerGeomRectangularTrimmedSurface{geom: C.geom_make_trimmed_cylinder_of_point(p1.val, p2.val, p3.val)}}
}

func GeomMakeTrimmedCylinderOfCircHeight(cr Circ, height float64) *GeomRectangularTrimmedSurface {
	return &GeomRectangularTrimmedSurface{inner: &innerGeomRectangularTrimmedSurface{geom: C.geom_make_trimmed_cylinder_of_circ_height(cr.val, C.double(height))}}
}

func GeomMakeTrimmedCylinderOfAxisRadius(a Axis1, radius, height float64) *GeomRectangularTrimmedSurface {
	return &GeomRectangularTrimmedSurface{inner: &innerGeomRectangularTrimmedSurface{geom: C.geom_make_trimmed_cylinder_axis_radius(a.val, C.double(radius), C.double(height))}}
}

func Geom2dMakeAxisPlacement(A Axis2d) *Geom2dAxisPlacement {
	return &Geom2dAxisPlacement{inner: &innerGeom2dAxisPlacement{geom: C.geom2d_make_axis_placement(A.val)}}
}

func Geom2dMakeAxisPlacementFromPoint(P Point2, V Dir2) *Geom2dAxisPlacement {
	return &Geom2dAxisPlacement{inner: &innerGeom2dAxisPlacement{geom: C.geom2d_make_axis_placement_from_point(P.val, V.val)}}
}

func Geom2dMakeBisectorBisecCC(Cu1, Cu2 *Geom2dCurve, Side1, Side2 float64, Origin Point2, DistMax float64) *Geom2dBisectorBisecCC {
	return &Geom2dBisectorBisecCC{inner: &innerGeom2dBisectorBisecCC{geom: C.geom2d_make_bezier_bisec_cc_curve(Cu1.inner.geom, Cu2.inner.geom, C.double(Side1), C.double(Side2), Origin.val, C.double(DistMax))}}
}

func Geom2dMakeBisectorBisecPCFromDist(Cu1 *Geom2dCurve, p Point2, side2, distMax float64) *Geom2dBisectorBisecPC {
	return &Geom2dBisectorBisecPC{inner: &innerGeom2dBisectorBisecPC{geom: C.geom2d_make_bezier_bisec_pc_curve_with_dist(Cu1.inner.geom, p.val, C.double(side2), C.double(distMax))}}
}

func Geom2dMakeBisectorBisecPC(Cu1 *Geom2dCurve, p Point2, side2, UMin, UMax float64) *Geom2dBisectorBisecPC {
	return &Geom2dBisectorBisecPC{inner: &innerGeom2dBisectorBisecPC{geom: C.geom2d_make_bezier_bisec_pc_curve(Cu1.inner.geom, p.val, C.double(side2), C.double(UMin), C.double(UMax))}}
}

func Geom2dMakeBezierCurve(poles []Point2) *Geom2dBezierCurve {
	in := make([]C.struct__pnt2d_t, len(poles))
	for i := range poles {
		in[i] = poles[i].val
	}
	return &Geom2dBezierCurve{inner: &innerGeom2dBezierCurve{geom: C.geom2d_make_bezier_curve(&in[0], C.int(len(poles)))}}
}

func Geom2dMakeBezierCurveFromWeight(poles []Point2, weights []float64) *Geom2dBezierCurve {
	in := make([]C.struct__pnt2d_t, len(poles))
	for i := range poles {
		in[i] = poles[i].val
	}
	return &Geom2dBezierCurve{inner: &innerGeom2dBezierCurve{geom: C.geom2d_make_bezier_curve_with_weight(&in[0], (*C.double)(unsafe.Pointer(&weights[0])), C.int(len(poles)))}}
}

func Geom2dMakeBSplineCurve(poles []Point2, Knots []float64, Multiplicities []int, Degree int, Periodic bool) *Geom2dBSplineCurve {
	in := make([]C.struct__pnt2d_t, len(poles))
	for i := range poles {
		in[i] = poles[i].val
	}
	return &Geom2dBSplineCurve{inner: &innerGeom2dBSplineCurve{geom: C.geom2d_make_bspline_curve(&in[0], (*C.double)(unsafe.Pointer(&Knots[0])), (*C.int)(unsafe.Pointer(&Multiplicities[0])), C.int(len(poles)), C.int(Degree), C.bool(Periodic))}}
}

func Geom2dMakeBSplineCurveFromWeight(poles []Point2, weights []float64, Knots []float64, Multiplicities []int, Degree int, Periodic bool) *Geom2dBSplineCurve {
	in := make([]C.struct__pnt2d_t, len(poles))
	for i := range poles {
		in[i] = poles[i].val
	}
	return &Geom2dBSplineCurve{inner: &innerGeom2dBSplineCurve{geom: C.geom2d_make_bspline_curve_with_weight(&in[0], (*C.double)(unsafe.Pointer(&weights[0])), (*C.double)(unsafe.Pointer(&Knots[0])), (*C.int)(unsafe.Pointer(&Multiplicities[0])), C.int(len(poles)), C.int(Degree), C.bool(Periodic))}}
}

func Geom2dMakeTrimmedCurve(g *Geom2dCurve, u1, u2 float64, sense, adj bool) *Geom2dTrimmedCurve {
	return &Geom2dTrimmedCurve{inner: &innerGeom2dTrimmedCurve{geom: C.geom2d_make_trimmed_curve(g.inner.geom, C.double(u1), C.double(u2), C.bool(sense), C.bool(adj))}}
}

func Geom2dMakeOffsetCurve(g *Geom2dCurve, offset float64, nocheck bool) *Geom2dOffsetCurve {
	return &Geom2dOffsetCurve{inner: &innerGeom2dOffsetCurve{geom: C.geom2d_make_offset_curve(g.inner.geom, C.double(offset), C.bool(nocheck))}}
}

func Geom2dMakeCartesianPointp1(p Point2) *Geom2dCartesianPoint {
	return &Geom2dCartesianPoint{inner: &innerGeom2dCartesianPoint{geom: C.geom2d_make_cartesian_point(p.val)}}
}

func Geom2dMakeCartesianPointFromXY(x, y float64) *Geom2dCartesianPoint {
	return &Geom2dCartesianPoint{inner: &innerGeom2dCartesianPoint{geom: C.geom2d_make_cartesian_point_xy(C.double(x), C.double(y))}}
}

func Geom2dMakeDirectionFromFromDir(p Dir2) *Geom2dDirection {
	return &Geom2dDirection{inner: &innerGeom2dDirection{geom: C.geom2d_make_direction_with_dir(p.val)}}
}

func Geom2dMakeDirection(x, y float64) *Geom2dDirection {
	return &Geom2dDirection{inner: &innerGeom2dDirection{geom: C.geom2d_make_direction(C.double(x), C.double(y))}}
}

func Geom2dMakeDirectionFromFromVector(p Vector2) *Geom2dVectorWithMagnitude {
	return &Geom2dVectorWithMagnitude{inner: &innerGeom2dVectorWithMagnitude{geom: C.geom2d_make_vector_with_magnitude_with_vector(p.val)}}
}

func Geom2dMakeDirectionFromFromXY(x, y float64) *Geom2dVectorWithMagnitude {
	return &Geom2dVectorWithMagnitude{inner: &innerGeom2dVectorWithMagnitude{geom: C.geom2d_make_vector_with_magnitude_with_xy(C.double(x), C.double(y))}}
}

func Geom2dMakeDirectionFromFromPoint(p1, p2 Point2) *Geom2dVectorWithMagnitude {
	return &Geom2dVectorWithMagnitude{inner: &innerGeom2dVectorWithMagnitude{geom: C.geom2d_make_vector_with_magnitude_with_point(p1.val, p2.val)}}
}

func Geom2dMakeArcOfCircleTwoAngles(cr Circ2d, Alpha1, Alpha2 float64, sense bool) *Geom2dTrimmedCurve {
	return &Geom2dTrimmedCurve{inner: &innerGeom2dTrimmedCurve{geom: C.geom2d_make_arc_of_circle_two_angles(cr.val, C.double(Alpha1), C.double(Alpha2), C.bool(sense))}}
}

func Geom2dMakeArcOfCircleAngles(cr Circ2d, P Point2, Alpha float64, sense bool) *Geom2dTrimmedCurve {
	return &Geom2dTrimmedCurve{inner: &innerGeom2dTrimmedCurve{geom: C.geom2d_make_arc_of_circle_angle(cr.val, P.val, C.double(Alpha), C.bool(sense))}}
}

func Geom2dMakeArcOfCircleTwoPoint(cr Circ2d, p1, p2 Point2, sense bool) *Geom2dTrimmedCurve {
	return &Geom2dTrimmedCurve{inner: &innerGeom2dTrimmedCurve{geom: C.geom2d_make_arc_of_circle_two_point(cr.val, p1.val, p2.val, C.bool(sense))}}
}

func Geom2dMakeArcOfCircleThreePoint(p1, p2, p3 Point2) *Geom2dTrimmedCurve {
	return &Geom2dTrimmedCurve{inner: &innerGeom2dTrimmedCurve{geom: C.geom2d_make_arc_of_circle_point(p1.val, p2.val, p3.val)}}
}

func Geom2dMakeArcOfCircleVector(p1 Point2, v Vector2, p2 Point2) *Geom2dTrimmedCurve {
	return &Geom2dTrimmedCurve{inner: &innerGeom2dTrimmedCurve{geom: C.geom2d_make_arc_of_circle_vector(p1.val, v.val, p2.val)}}
}

func Geom2dMakeArcOfEllipseTwoAngles(e Elips2d, Alpha1, Alpha2 float64, sense bool) *Geom2dTrimmedCurve {
	return &Geom2dTrimmedCurve{inner: &innerGeom2dTrimmedCurve{geom: C.geom2d_make_arc_of_ellipse_two_angles(e.val, C.double(Alpha1), C.double(Alpha2), C.bool(sense))}}
}

func Geom2dMakeArcOfEllipseAngles(e Elips2d, P Point2, Alpha float64, sense bool) *Geom2dTrimmedCurve {
	return &Geom2dTrimmedCurve{inner: &innerGeom2dTrimmedCurve{geom: C.geom2d_make_arc_of_ellipse_angle(e.val, P.val, C.double(Alpha), C.bool(sense))}}
}

func Geom2dMakeArcOfEllipseTwoPoint(cr Elips2d, p1, p2 Point2, sense bool) *Geom2dTrimmedCurve {
	return &Geom2dTrimmedCurve{inner: &innerGeom2dTrimmedCurve{geom: C.geom2d_make_arc_of_ellipse_point(cr.val, p1.val, p2.val, C.bool(sense))}}
}

func Geom2dMakeArcOfHyperbolaTwoAngles(e Hyperbola2d, Alpha1, Alpha2 float64, sense bool) *Geom2dTrimmedCurve {
	return &Geom2dTrimmedCurve{inner: &innerGeom2dTrimmedCurve{geom: C.geom2d_make_arc_of_hyperbola_two_angles(e.val, C.double(Alpha1), C.double(Alpha2), C.bool(sense))}}
}

func Geom2dMakeArcOfHyperbolaAngles(e Hyperbola2d, P Point2, Alpha float64, sense bool) *Geom2dTrimmedCurve {
	return &Geom2dTrimmedCurve{inner: &innerGeom2dTrimmedCurve{geom: C.geom2d_make_arc_of_hyperbola_angle(e.val, P.val, C.double(Alpha), C.bool(sense))}}
}

func Geom2dMakeArcOfHyperbolaTwoPoint(cr Hyperbola2d, p1, p2 Point2, sense bool) *Geom2dTrimmedCurve {
	return &Geom2dTrimmedCurve{inner: &innerGeom2dTrimmedCurve{geom: C.geom2d_make_arc_of_hyperbola_point(cr.val, p1.val, p2.val, C.bool(sense))}}
}

func Geom2dMakeArcOfParabolaTwoAngles(e Parabola2d, Alpha1, Alpha2 float64, sense bool) *Geom2dTrimmedCurve {
	return &Geom2dTrimmedCurve{inner: &innerGeom2dTrimmedCurve{geom: C.geom2d_make_arc_of_parabola_two_angles(e.val, C.double(Alpha1), C.double(Alpha2), C.bool(sense))}}
}

func Geom2dMakeArcOfParabolaAngles(e Parabola2d, P Point2, Alpha float64, sense bool) *Geom2dTrimmedCurve {
	return &Geom2dTrimmedCurve{inner: &innerGeom2dTrimmedCurve{geom: C.geom2d_make_arc_of_parabola_angle_angle(e.val, P.val, C.double(Alpha), C.bool(sense))}}
}

func Geom2dMakeArcOfParabolaTwoPoint(cr Parabola2d, p1, p2 Point2, sense bool) *Geom2dTrimmedCurve {
	return &Geom2dTrimmedCurve{inner: &innerGeom2dTrimmedCurve{geom: C.geom2d_make_arc_of_parabola_point(cr.val, p1.val, p2.val, C.bool(sense))}}
}

func Geom2dMakeCircle(cr Circ2d) *Geom2dCircle {
	return &Geom2dCircle{inner: &innerGeom2dCircle{geom: C.geom2d_make_circle(cr.val)}}
}

func Geom2dMakeCircleOfAxis2d(A Axis2d, Radius float64, sense bool) *Geom2dCircle {
	return &Geom2dCircle{inner: &innerGeom2dCircle{geom: C.geom2d_make_circle_of_axis2d(A.val, C.double(Radius), C.bool(sense))}}
}

func Geom2dMakeCircleOfAxis22d(A Axis22d, Radius float64) *Geom2dCircle {
	return &Geom2dCircle{inner: &innerGeom2dCircle{geom: C.geom2d_make_circle_of_axis22d(A.val, C.double(Radius))}}
}

func Geom2dMakeCircleOfCirc2dDist(cr Circ2d, Dist float64) *Geom2dCircle {
	return &Geom2dCircle{inner: &innerGeom2dCircle{geom: C.geom2d_make_circle_of_circ2d_dist(cr.val, C.double(Dist))}}
}

func Geom2dMakeCircleOfCirc2dPoint(cr Circ2d, p Point2) *Geom2dCircle {
	return &Geom2dCircle{inner: &innerGeom2dCircle{geom: C.geom2d_make_circle_of_circ2d_point(cr.val, p.val)}}
}

func Geom2dMakeCircleOfThreePoint(p1, p2, p3 Point2) *Geom2dCircle {
	return &Geom2dCircle{inner: &innerGeom2dCircle{geom: C.geom2d_make_circle_of_three_point(p1.val, p2.val, p3.val)}}
}

func Geom2dMakeCircleOfPointRadius(p Point2, Radius float64, sense bool) *Geom2dCircle {
	return &Geom2dCircle{inner: &innerGeom2dCircle{geom: C.geom2d_make_circle_of_point_radius(p.val, C.double(Radius), C.bool(sense))}}
}

func Geom2dMakeCircleOfCenterRadius(Center Point2, p Point2, sense bool) *Geom2dCircle {
	return &Geom2dCircle{inner: &innerGeom2dCircle{geom: C.geom2d_make_circle_of_center_radius(Center.val, p.val, C.bool(sense))}}
}

func Geom2dMakeEllipse(e Elips2d) *Geom2dEllipse {
	return &Geom2dEllipse{inner: &innerGeom2dEllipse{geom: C.geom2d_make_ellipse(e.val)}}
}

func Geom2dMakeEllipseOfAxis2dRadius(a Axis2d, MajorRadius, MinorRadius float64, sense bool) *Geom2dEllipse {
	return &Geom2dEllipse{inner: &innerGeom2dEllipse{geom: C.geom2d_make_ellipse_of_axis2d_radius(a.val, C.double(MajorRadius), C.double(MinorRadius), C.bool(sense))}}
}

func Geom2dMakeEllipseOfAxis22dRadius(a Axis22d, MajorRadius, MinorRadius float64) *Geom2dEllipse {
	return &Geom2dEllipse{inner: &innerGeom2dEllipse{geom: C.geom2d_make_ellipse_of_axis22d_radius(a.val, C.double(MajorRadius), C.double(MinorRadius))}}
}

func Geom2dMakeEllipseOfThreePoint(S1, S2, Center Point2) *Geom2dEllipse {
	return &Geom2dEllipse{inner: &innerGeom2dEllipse{geom: C.geom2d_make_ellipse_of_three_point(S1.val, S2.val, Center.val)}}
}

func Geom2dMakeHyperbola(e Hyperbola2d) *Geom2dHyperbola {
	return &Geom2dHyperbola{inner: &innerGeom2dHyperbola{geom: C.geom2d_make_hyperbola(e.val)}}
}

func Geom2dMakeHyperbolaOfAxis2dRadius(a Axis2d, MajorRadius, MinorRadius float64, sense bool) *Geom2dHyperbola {
	return &Geom2dHyperbola{inner: &innerGeom2dHyperbola{geom: C.geom2d_make_hyperbola_of_axis2d_radius(a.val, C.double(MajorRadius), C.double(MinorRadius), C.bool(sense))}}
}

func Geom2dMakeHyperbolaOfAxis22dRadius(a Axis22d, MajorRadius, MinorRadius float64) *Geom2dHyperbola {
	return &Geom2dHyperbola{inner: &innerGeom2dHyperbola{geom: C.geom2d_make_hyperbola_of_axis22d_radius(a.val, C.double(MajorRadius), C.double(MinorRadius))}}
}

func Geom2dMakeHyperbolaOfThreePoint(S1, S2, Center Point2) *Geom2dHyperbola {
	return &Geom2dHyperbola{inner: &innerGeom2dHyperbola{geom: C.geom2d_make_hyperbola_of_three_point(S1.val, S2.val, Center.val)}}
}

func Geom2dMakeLine(l Line2d) *Geom2dLine {
	return &Geom2dLine{inner: &innerGeom2dLine{geom: C.geom2d_make_line(l.val)}}
}

func Geom2dMakeLineOfAxis2d(A Axis2d) *Geom2dLine {
	return &Geom2dLine{inner: &innerGeom2dLine{geom: C.geom2d_make_line_of_axis2d(A.val)}}
}

func Geom2dMakeLineOfPointDir(P Point2, v Dir2) *Geom2dLine {
	return &Geom2dLine{inner: &innerGeom2dLine{geom: C.geom2d_make_line_of_point_dir(P.val, v.val)}}
}

func Geom2dMakeLineOfPoint(l Line2d, P Point2) *Geom2dLine {
	return &Geom2dLine{inner: &innerGeom2dLine{geom: C.geom2d_make_line_of_point(l.val, P.val)}}
}

func Geom2dMakeLineOfDist(l Line2d, Dist float64) *Geom2dLine {
	return &Geom2dLine{inner: &innerGeom2dLine{geom: C.geom2d_make_line_of_dist(l.val, C.double(Dist))}}
}

func Geom2dMakeLineOfTwoPoint(p1, p2 Point2) *Geom2dLine {
	return &Geom2dLine{inner: &innerGeom2dLine{geom: C.geom2d_make_line_of_two_point(p1.val, p2.val)}}
}

func Geom2dMakeParabola(p Parabola2d) *Geom2dParabola {
	return &Geom2dParabola{inner: &innerGeom2dParabola{geom: C.geom2d_make_parabola(p.val)}}
}

func Geom2dMakeParabolaOfAxis22d(a Axis22d, Focal float64) *Geom2dParabola {
	return &Geom2dParabola{inner: &innerGeom2dParabola{geom: C.geom2d_make_parabola_of_axis22d(a.val, C.double(Focal))}}
}

func Geom2dMakeParabolaOfAxis2d(a Axis2d, Focal float64, sense bool) *Geom2dParabola {
	return &Geom2dParabola{inner: &innerGeom2dParabola{geom: C.geom2d_make_parabola_of_axis2d(a.val, C.double(Focal), C.bool(sense))}}
}

func Geom2dMakeParabolaOfAxis2dPoint(a Axis2d, f Point2, sense bool) *Geom2dParabola {
	return &Geom2dParabola{inner: &innerGeom2dParabola{geom: C.geom2d_make_parabola_of_axis2d_point(a.val, f.val, C.bool(sense))}}
}

func Geom2dMakeParabolaOfPoint(S1, O Point2) *Geom2dParabola {
	return &Geom2dParabola{inner: &innerGeom2dParabola{geom: C.geom2d_make_parabola_point(S1.val, O.val)}}
}

func Geom2dMakeSegmentOfTwoPoint(p1, p2 Point2) *Geom2dTrimmedCurve {
	return &Geom2dTrimmedCurve{inner: &innerGeom2dTrimmedCurve{geom: C.geom2d_make_segment_of_point(p1.val, p2.val)}}
}

func Geom2dMakeSegmentOfPointDir(p1 Point2, v Dir2, p2 Point2) *Geom2dTrimmedCurve {
	return &Geom2dTrimmedCurve{inner: &innerGeom2dTrimmedCurve{geom: C.geom2d_make_segment_of_point_dir(p1.val, v.val, p2.val)}}
}

func Geom2dMakeSegmentOfLine(l Line2d, U1, U2 float64) *Geom2dTrimmedCurve {
	return &Geom2dTrimmedCurve{inner: &innerGeom2dTrimmedCurve{geom: C.geom2d_make_segment_of_line(l.val, C.double(U1), C.double(U2))}}
}

func Geom2dMakeSegmentOfLinePoint(l Line2d, p Point2, U float64) *Geom2dTrimmedCurve {
	return &Geom2dTrimmedCurve{inner: &innerGeom2dTrimmedCurve{geom: C.geom2d_make_segment_of_line_point(l.val, p.val, C.double(U))}}
}

func Geom2dMakeSegmentOfLineTwoPoint(l Line2d, p1, p2 Point2) *Geom2dTrimmedCurve {
	return &Geom2dTrimmedCurve{inner: &innerGeom2dTrimmedCurve{geom: C.geom2d_make_segment_of_line_two_point(l.val, p1.val, p2.val)}}
}

func Geom2dMakeMirrorOfPoint(p Point2) *Geom2dTransformation {
	return &Geom2dTransformation{inner: &innerGeom2dTransformation{geom: C.geom2d_make_mirror_of_point(p.val)}}
}

func Geom2dMakeMirrorOfAxis2d(a Axis2d) *Geom2dTransformation {
	return &Geom2dTransformation{inner: &innerGeom2dTransformation{geom: C.geom2d_make_mirror_of_axis2d(a.val)}}
}

func Geom2dMakeMirrorOfLine2d(l Line2d) *Geom2dTransformation {
	return &Geom2dTransformation{inner: &innerGeom2dTransformation{geom: C.geom2d_make_mirror_of_line2d(l.val)}}
}

func Geom2dMakeMirrorOfPointDir(p Point2, dir Dir2) *Geom2dTransformation {
	return &Geom2dTransformation{inner: &innerGeom2dTransformation{geom: C.geom2d_make_mirror_of_point_dir(p.val, dir.val)}}
}

func Geom2dMakeRotationOfPoint(p Point2, ang float64) *Geom2dTransformation {
	return &Geom2dTransformation{inner: &innerGeom2dTransformation{geom: C.geom2d_make_rotation_of_point_angle(p.val, C.double(ang))}}
}

func Geom2dMakeScaleOfPoint(p Point2, s float64) *Geom2dTransformation {
	return &Geom2dTransformation{inner: &innerGeom2dTransformation{geom: C.geom2d_make_scale_point_scale(p.val, C.double(s))}}
}

func Geom2dMakeTranslationOfVector(v Vector2) *Geom2dTransformation {
	return &Geom2dTransformation{inner: &innerGeom2dTransformation{geom: C.geom2d_make_translation_of_vector(v.val)}}
}

func Geom2dMakeTranslationOfPoint(p1, p2 Point2) *Geom2dTransformation {
	return &Geom2dTransformation{inner: &innerGeom2dTransformation{geom: C.geom2d_make_translation_of_point(p1.val, p2.val)}}
}
