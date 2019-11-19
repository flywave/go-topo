#ifndef GO_GEOMETRY_IMPL_H
#define GO_GEOMETRY_IMPL_H

#include <Standard_Version.hxx>

#include <GeomPlate_Surface.hxx>
#include <Geom_Axis1Placement.hxx>
#include <Geom_Axis2Placement.hxx>
#include <Geom_AxisPlacement.hxx>
#include <Geom_BSplineCurve.hxx>
#include <Geom_BSplineSurface.hxx>
#include <Geom_BezierCurve.hxx>
#include <Geom_BezierSurface.hxx>
#include <Geom_BoundedCurve.hxx>
#include <Geom_BoundedSurface.hxx>
#include <Geom_CartesianPoint.hxx>
#include <Geom_Circle.hxx>
#include <Geom_Conic.hxx>
#include <Geom_ConicalSurface.hxx>
#include <Geom_Curve.hxx>
#include <Geom_CylindricalSurface.hxx>
#include <Geom_Direction.hxx>
#include <Geom_ElementarySurface.hxx>
#include <Geom_Ellipse.hxx>
#include <Geom_Geometry.hxx>
#include <Geom_Hyperbola.hxx>
#include <Geom_Line.hxx>
#include <Geom_OffsetCurve.hxx>
#include <Geom_OffsetSurface.hxx>
#include <Geom_Parabola.hxx>
#include <Geom_Plane.hxx>
#include <Geom_RectangularTrimmedSurface.hxx>
#include <Geom_SphericalSurface.hxx>
#include <Geom_Surface.hxx>
#include <Geom_SurfaceOfLinearExtrusion.hxx>
#include <Geom_SurfaceOfRevolution.hxx>
#include <Geom_SweptSurface.hxx>
#include <Geom_ToroidalSurface.hxx>
#include <Geom_Transformation.hxx>
#include <Geom_TrimmedCurve.hxx>
#include <Geom_VectorWithMagnitude.hxx>

#include <TColGeom_Array1OfBSplineCurve.hxx>
#include <TColGeom_Array1OfBezierCurve.hxx>
#include <TColGeom_Array1OfCurve.hxx>
#include <TColGeom_Array1OfSurface.hxx>
#include <TColGeom_Array2OfBezierSurface.hxx>
#include <TColGeom_Array2OfSurface.hxx>

#include <TColGeom_SequenceOfBoundedCurve.hxx>
#include <TColGeom_SequenceOfCurve.hxx>
#include <TColGeom_SequenceOfSurface.hxx>

#include <Bisector_BisecAna.hxx>
#include <Bisector_BisecCC.hxx>
#include <Bisector_BisecPC.hxx>
#include <Bisector_Curve.hxx>
#include <Geom2d_AxisPlacement.hxx>
#include <Geom2d_BSplineCurve.hxx>
#include <Geom2d_BezierCurve.hxx>
#include <Geom2d_BoundedCurve.hxx>
#include <Geom2d_CartesianPoint.hxx>
#include <Geom2d_Circle.hxx>
#include <Geom2d_Conic.hxx>
#include <Geom2d_Curve.hxx>
#include <Geom2d_Direction.hxx>
#include <Geom2d_Ellipse.hxx>
#include <Geom2d_Geometry.hxx>
#include <Geom2d_Hyperbola.hxx>
#include <Geom2d_Line.hxx>
#include <Geom2d_OffsetCurve.hxx>
#include <Geom2d_Parabola.hxx>
#include <Geom2d_Transformation.hxx>
#include <Geom2d_TrimmedCurve.hxx>
#include <Geom2d_VectorWithMagnitude.hxx>

#include <TColGeom2d_Array1OfBSplineCurve.hxx>
#include <TColGeom2d_Array1OfBezierCurve.hxx>
#include <TColGeom2d_Array1OfCurve.hxx>
#include <TColGeom2d_SequenceOfBoundedCurve.hxx>
#include <TColGeom2d_SequenceOfCurve.hxx>
#include <TColGeom2d_SequenceOfGeometry.hxx>

#ifdef __cplusplus
extern "C" {
#endif

struct _geom_geometry_t {
  Handle(Geom_Geometry) handle;
};

struct _geom_transformation_t {
  Handle(Geom_Transformation) handle;
};

struct _geom_axis_placement_t {
  Handle(Geom_AxisPlacement) handle;
};

struct _geom_axis1_placement_t {
  Handle(Geom_Axis1Placement) handle;
};

struct _geom_axis2_placement_t {
  Handle(Geom_Axis2Placement) handle;
};

struct _geom_curve_t {
  Handle(Geom_Curve) handle;
};

struct _geom_bounded_curve_t {
  Handle(Geom_BoundedCurve) handle;
};

struct _geom_bezier_curve_t {
  Handle(Geom_BezierCurve) handle;
};

struct _geom_bspline_curve_t {
  Handle(Geom_BSplineCurve) handle;
};

struct _geom_trimmed_curve_t {
  Handle(Geom_TrimmedCurve) handle;
};

struct _geom_conic_t {
  Handle(Geom_Conic) handle;
};

struct _geom_circle_t {
  Handle(Geom_Circle) handle;
};

struct _geom_ellipse_t {
  Handle(Geom_Ellipse) handle;
};

struct _geom_hyperbola_t {
  Handle(Geom_Hyperbola) handle;
};

struct _geom_parabola_t {
  Handle(Geom_Parabola) handle;
};

struct _geom_line_t {
  Handle(Geom_Line) handle;
};

struct _geom_offset_curve_t {
  Handle(Geom_OffsetCurve) handle;
};

struct _geom_point_t {
  Handle(Geom_Point) handle;
};

struct _geom_cartesian_point_t {
  Handle(Geom_CartesianPoint) handle;
};

struct _geom_surface_t {
  Handle(Geom_Surface) handle;
};

struct _geom_bounded_surface_t {
  Handle(Geom_BoundedSurface) handle;
};

struct _geom_bezier_surface_t {
  Handle(Geom_BezierSurface) handle;
};

struct _geom_bspline_surface_t {
  Handle(Geom_BSplineSurface) handle;
};

struct _geom_rectangular_trimmed_surface_t {
  Handle(Geom_RectangularTrimmedSurface) handle;
};

struct _geom_elementary_surface_t {
  Handle(Geom_ElementarySurface) handle;
};

struct _geom_cylindrical_surface_t {
  Handle(Geom_CylindricalSurface) handle;
};

struct _geom_plane_surface_t {
  Handle(Geom_Plane) handle;
};

struct _geom_conical_surface_t {
  Handle(Geom_ConicalSurface) handle;
};

struct _geom_spherical_surface_t {
  Handle(Geom_SphericalSurface) handle;
};

struct _geom_toroidal_surface_t {
  Handle(Geom_ToroidalSurface) handle;
};

struct _geom_offset_surface_t {
  Handle(Geom_OffsetSurface) handle;
};

struct _geom_swept_surface_t {
  Handle(Geom_SweptSurface) handle;
};

struct _geom_surface_of_linear_extrusion_t {
  Handle(Geom_SurfaceOfLinearExtrusion) handle;
};

struct _geom_surface_of_revolution_extrusion_t {
  Handle(Geom_SurfaceOfRevolution) handle;
};

struct _geom_plate_surface_t {
  Handle(GeomPlate_Surface) handle;
};

struct _geom_vector_t {
  Handle(Geom_Vector) handle;
};

struct _geom_direction_t {
  Handle(Geom_Direction) handle;
};

struct _geom_vector_with_magnitude_t {
  Handle(Geom_VectorWithMagnitude) handle;
};

struct _geom2d_geometry_t {
  Handle(Geom2d_Geometry) handle;
};

struct _geom2d_transformation_t {
  Handle(Geom2d_Transformation) handle;
};

struct _geom2d_axis_placement_t {
  Handle(Geom2d_AxisPlacement) handle;
};

struct _geom2d_curve_t {
  Handle(Geom2d_Curve) handle;
};

struct _geom2d_bisector_curve_t {
  Handle(Bisector_Curve) handle;
};

struct _geom2d_bezier_bisec_ana_curve_t {
  Handle(Bisector_BisecAna) handle;
};

struct _geom2d_bezier_bisec_cc_curve_t {
  Handle(Bisector_BisecCC) handle;
};

struct _geom2d_bezier_bisec_pc_curve_t {
  Handle(Bisector_BisecPC) handle;
};

struct _geom2d_bounded_curve_t {
  Handle(Geom2d_BoundedCurve) handle;
};

struct _geom2d_bezier_curve_t {
  Handle(Geom2d_BezierCurve) handle;
};

struct _geom2d_bspline_curve_t {
  Handle(Geom2d_BSplineCurve) handle;
};

struct _geom2d_trimmed_curve_t {
  Handle(Geom2d_TrimmedCurve) handle;
};

struct _geom2d_conic_t {
  Handle(Geom2d_Conic) handle;
};

struct _geom2d_circle_t {
  Handle(Geom2d_Circle) handle;
};

struct _geom2d_ellipse_t {
  Handle(Geom2d_Ellipse) handle;
};

struct _geom2d_hyperbola_t {
  Handle(Geom2d_Hyperbola) handle;
};

struct _geom2d_parabola_t {
  Handle(Geom2d_Parabola) handle;
};

struct _geom2d_line_t {
  Handle(Geom2d_Line) handle;
};

struct _geom2d_offset_curve_t {
  Handle(Geom2d_OffsetCurve) handle;
};

struct _geom2d_point_t {
  Handle(Geom2d_Point) handle;
};

struct _geom2d_cartesian_point_t {
  Handle(Geom2d_CartesianPoint) handle;
};

struct _geom2d_vector_t {
  Handle(Geom2d_Vector) handle;
};

struct _geom2d_direction_t {
  Handle(Geom2d_Direction) handle;
};

struct _geom2d_vector_with_magnitude_t {
  Handle(Geom2d_VectorWithMagnitude) handle;
};

#ifdef __cplusplus
}
#endif

#endif
