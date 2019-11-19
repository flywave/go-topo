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

struct _geom_parabola_t {
  Handle(Geom_Parabola) handle;
};

struct _geom_hyperbola_t {
  Handle(Geom_Hyperbola) handle;
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

inline Handle(Geom_Geometry) cast_to_geom(const _geom_geometry_t &p) {
  return p.handle;
}

inline _geom_geometry_t cast_from_geom(const Handle(Geom_Geometry) & d) {
  return _geom_geometry_t{d};
}

inline Handle(Geom_Transformation)
    cast_to_geom(const _geom_transformation_t &p) {
  return p.handle;
}

inline _geom_transformation_t cast_from_geom(const Handle(Geom_Transformation) &
                                             d) {
  return _geom_transformation_t{d};
}

inline Handle(Geom_AxisPlacement)
    cast_to_geom(const _geom_axis_placement_t &p) {
  return p.handle;
}

inline _geom_axis_placement_t cast_from_geom(const Handle(Geom_AxisPlacement) &
                                             d) {
  return _geom_axis_placement_t{d};
}

inline Handle(Geom_Axis1Placement)
    cast_to_geom(const _geom_axis1_placement_t &p) {
  return p.handle;
}

inline _geom_axis1_placement_t
cast_from_geom(const Handle(Geom_Axis1Placement) & d) {
  return _geom_axis1_placement_t{d};
}

inline Handle(Geom_Axis2Placement)
    cast_to_geom(const _geom_axis2_placement_t &p) {
  return p.handle;
}

inline _geom_axis2_placement_t
cast_from_geom(const Handle(Geom_Axis2Placement) & d) {
  return _geom_axis2_placement_t{d};
}

inline Handle(Geom_Curve) cast_to_geom(const _geom_curve_t &p) {
  return p.handle;
}

inline _geom_curve_t cast_from_geom(const Handle(Geom_Curve) & d) {
  return _geom_curve_t{d};
}

inline Handle(Geom_BoundedCurve) cast_to_geom(const _geom_bounded_curve_t &p) {
  return p.handle;
}

inline _geom_bounded_curve_t cast_from_geom(const Handle(Geom_BoundedCurve) &
                                            d) {
  return _geom_bounded_curve_t{d};
}

inline Handle(Geom_BezierCurve) cast_to_geom(const _geom_bezier_curve_t &p) {
  return p.handle;
}

inline _geom_bezier_curve_t cast_from_geom(const Handle(Geom_BezierCurve) & d) {
  return _geom_bezier_curve_t{d};
}

inline Handle(Geom_BSplineCurve) cast_to_geom(const _geom_bspline_curve_t &p) {
  return p.handle;
}

inline _geom_bspline_curve_t cast_from_geom(const Handle(Geom_BSplineCurve) &
                                            d) {
  return _geom_bspline_curve_t{d};
}

inline Handle(Geom_TrimmedCurve) cast_to_geom(const _geom_trimmed_curve_t &p) {
  return p.handle;
}

inline _geom_trimmed_curve_t cast_from_geom(const Handle(Geom_TrimmedCurve) &
                                            d) {
  return _geom_trimmed_curve_t{d};
}

inline Handle(Geom_Conic) cast_to_geom(const _geom_conic_t &p) {
  return p.handle;
}

inline _geom_conic_t cast_from_geom(const Handle(Geom_Conic) & d) {
  return _geom_conic_t{d};
}

inline Handle(Geom_Circle) cast_to_geom(const _geom_circle_t &p) {
  return p.handle;
}

inline _geom_circle_t cast_from_geom(const Handle(Geom_Circle) & d) {
  return _geom_circle_t{d};
}

inline Handle(Geom_Ellipse) cast_to_geom(const _geom_ellipse_t &p) {
  return p.handle;
}

inline _geom_ellipse_t cast_from_geom(const Handle(Geom_Ellipse) & d) {
  return _geom_ellipse_t{d};
}

inline Handle(Geom_Hyperbola) cast_to_geom(const _geom_hyperbola_t &p) {
  return p.handle;
}

inline _geom_hyperbola_t cast_from_geom(const Handle(Geom_Hyperbola) & d) {
  return _geom_hyperbola_t{d};
}

inline Handle(Geom_Parabola) cast_to_geom(const _geom_parabola_t &p) {
  return p.handle;
}

inline _geom_parabola_t cast_from_geom(const Handle(Geom_Parabola) & d) {
  return _geom_parabola_t{d};
}

inline Handle(Geom_Line) cast_to_geom(const _geom_line_t &p) {
  return p.handle;
}

inline _geom_line_t cast_from_geom(const Handle(Geom_Line) & d) {
  return _geom_line_t{d};
}

inline Handle(Geom_OffsetCurve) cast_to_geom(const _geom_offset_curve_t &p) {
  return p.handle;
}

inline _geom_offset_curve_t cast_from_geom(const Handle(Geom_OffsetCurve) & d) {
  return _geom_offset_curve_t{d};
}

inline Handle(Geom_Point) cast_to_geom(const _geom_point_t &p) {
  return p.handle;
}

inline _geom_point_t cast_from_geom(const Handle(Geom_Point) & d) {
  return _geom_point_t{d};
}

inline Handle(Geom_CartesianPoint)
    cast_to_geom(const _geom_cartesian_point_t &p) {
  return p.handle;
}

inline _geom_cartesian_point_t
cast_from_geom(const Handle(Geom_CartesianPoint) & d) {
  return _geom_cartesian_point_t{d};
}

inline Handle(Geom_Surface) cast_to_geom(const _geom_surface_t &p) {
  return p.handle;
}

inline _geom_surface_t cast_from_geom(const Handle(Geom_Surface) & d) {
  return _geom_surface_t{d};
}

inline Handle(Geom_BoundedSurface)
    cast_to_geom(const _geom_bounded_surface_t &p) {
  return p.handle;
}

inline _geom_bounded_surface_t
cast_from_geom(const Handle(Geom_BoundedSurface) & d) {
  return _geom_bounded_surface_t{d};
}

inline Handle(Geom_BezierSurface)
    cast_to_geom(const _geom_bezier_surface_t &p) {
  return p.handle;
}

inline _geom_bezier_surface_t cast_from_geom(const Handle(Geom_BezierSurface) &
                                             d) {
  return _geom_bezier_surface_t{d};
}

inline Handle(Geom_BSplineSurface)
    cast_to_geom(const _geom_bspline_surface_t &p) {
  return p.handle;
}

inline _geom_bspline_surface_t
cast_from_geom(const Handle(Geom_BSplineSurface) & d) {
  return _geom_bspline_surface_t{d};
}

inline Handle(Geom_RectangularTrimmedSurface)
    cast_to_geom(const _geom_rectangular_trimmed_surface_t &p) {
  return p.handle;
}

inline _geom_rectangular_trimmed_surface_t
cast_from_geom(const Handle(Geom_RectangularTrimmedSurface) & d) {
  return _geom_rectangular_trimmed_surface_t{d};
}

inline Handle(Geom_ElementarySurface)
    cast_to_geom(const _geom_elementary_surface_t &p) {
  return p.handle;
}

inline _geom_elementary_surface_t
cast_from_geom(const Handle(Geom_ElementarySurface) & d) {
  return _geom_elementary_surface_t{d};
}
inline Handle(Geom_CylindricalSurface)
    cast_to_geom(const _geom_cylindrical_surface_t &p) {
  return p.handle;
}

inline _geom_cylindrical_surface_t
cast_from_geom(const Handle(Geom_CylindricalSurface) & d) {
  return _geom_cylindrical_surface_t{d};
}

inline Handle(Geom_Plane) cast_to_geom(const _geom_plane_surface_t &p) {
  return p.handle;
}

inline _geom_plane_surface_t cast_from_geom(const Handle(Geom_Plane) & d) {
  return _geom_plane_surface_t{d};
}

inline Handle(Geom_ConicalSurface)
    cast_to_geom(const _geom_conical_surface_t &p) {
  return p.handle;
}

inline _geom_conical_surface_t
cast_from_geom(const Handle(Geom_ConicalSurface) & d) {
  return _geom_conical_surface_t{d};
}

inline Handle(Geom_SphericalSurface)
    cast_to_geom(const _geom_spherical_surface_t &p) {
  return p.handle;
}

inline _geom_spherical_surface_t
cast_from_geom(const Handle(Geom_SphericalSurface) & d) {
  return _geom_spherical_surface_t{d};
}

inline Handle(Geom_ToroidalSurface)
    cast_to_geom(const _geom_toroidal_surface_t &p) {
  return p.handle;
}

inline _geom_toroidal_surface_t
cast_from_geom(const Handle(Geom_ToroidalSurface) & d) {
  return _geom_toroidal_surface_t{d};
}

inline Handle(Geom_OffsetSurface)
    cast_to_geom(const _geom_offset_surface_t &p) {
  return p.handle;
}

inline _geom_offset_surface_t cast_from_geom(const Handle(Geom_OffsetSurface) &
                                             d) {
  return _geom_offset_surface_t{d};
}

inline Handle(Geom_SweptSurface) cast_to_geom(const _geom_swept_surface_t &p) {
  return p.handle;
}

inline _geom_swept_surface_t cast_from_geom(const Handle(Geom_SweptSurface) &
                                            d) {
  return _geom_swept_surface_t{d};
}

inline Handle(Geom_SurfaceOfLinearExtrusion)
    cast_to_geom(const _geom_surface_of_linear_extrusion_t &p) {
  return p.handle;
}

inline _geom_surface_of_linear_extrusion_t
cast_from_geom(const Handle(Geom_SurfaceOfLinearExtrusion) & d) {
  return _geom_surface_of_linear_extrusion_t{d};
}

inline Handle(Geom_SurfaceOfRevolution)
    cast_to_geom(const _geom_surface_of_revolution_extrusion_t &p) {
  return p.handle;
}

inline _geom_surface_of_revolution_extrusion_t
cast_from_geom(const Handle(Geom_SurfaceOfRevolution) & d) {
  return _geom_surface_of_revolution_extrusion_t{d};
}

inline Handle(GeomPlate_Surface) cast_to_geom(const _geom_plate_surface_t &p) {
  return p.handle;
}

inline _geom_plate_surface_t cast_from_geom(const Handle(GeomPlate_Surface) &
                                            d) {
  return _geom_plate_surface_t{d};
}

inline Handle(Geom_Vector) cast_to_geom(const _geom_vector_t &p) {
  return p.handle;
}

inline _geom_vector_t cast_from_geom(const Handle(Geom_Vector) & d) {
  return _geom_vector_t{d};
}

inline Handle(Geom_Direction) cast_to_geom(const _geom_direction_t &p) {
  return p.handle;
}

inline _geom_direction_t cast_from_geom(const Handle(Geom_Direction) & d) {
  return _geom_direction_t{d};
}

inline Handle(Geom_VectorWithMagnitude)
    cast_to_geom(const _geom_vector_with_magnitude_t &p) {
  return p.handle;
}

inline _geom_vector_with_magnitude_t
cast_from_geom(const Handle(Geom_VectorWithMagnitude) & d) {
  return _geom_vector_with_magnitude_t{d};
}

inline Handle(Geom2d_Geometry) cast_to_geom(const _geom2d_geometry_t &p) {
  return p.handle;
}

inline _geom2d_geometry_t cast_from_geom(const Handle(Geom2d_Geometry) & d) {
  return _geom2d_geometry_t{d};
}

inline Handle(Geom2d_Transformation)
    cast_to_geom(const _geom2d_transformation_t &p) {
  return p.handle;
}

inline _geom2d_transformation_t
cast_from_geom(const Handle(Geom2d_Transformation) & d) {
  return _geom2d_transformation_t{d};
}

inline Handle(Geom2d_AxisPlacement)
    cast_to_geom(const _geom2d_axis_placement_t &p) {
  return p.handle;
}

inline _geom2d_axis_placement_t
cast_from_geom(const Handle(Geom2d_AxisPlacement) & d) {
  return _geom2d_axis_placement_t{d};
}

inline Handle(Geom2d_Curve) cast_to_geom(const _geom2d_curve_t &p) {
  return p.handle;
}

inline _geom2d_curve_t cast_from_geom(const Handle(Geom2d_Curve) & d) {
  return _geom2d_curve_t{d};
}

inline Handle(Bisector_Curve) cast_to_geom(const _geom2d_bisector_curve_t &p) {
  return p.handle;
}

inline _geom2d_bisector_curve_t cast_from_geom(const Handle(Bisector_Curve) &
                                               d) {
  return _geom2d_bisector_curve_t{d};
}

inline Handle(Bisector_BisecAna)
    cast_to_geom(const _geom2d_bezier_bisec_ana_curve_t &p) {
  return p.handle;
}

inline _geom2d_bezier_bisec_ana_curve_t
cast_from_geom(const Handle(Bisector_BisecAna) & d) {
  return _geom2d_bezier_bisec_ana_curve_t{d};
}

inline Handle(Bisector_BisecCC)
    cast_to_geom(const _geom2d_bezier_bisec_cc_curve_t &p) {
  return p.handle;
}

inline _geom2d_bezier_bisec_cc_curve_t
cast_from_geom(const Handle(Bisector_BisecCC) & d) {
  return _geom2d_bezier_bisec_cc_curve_t{d};
}

inline Handle(Bisector_BisecPC)
    cast_to_geom(const _geom2d_bezier_bisec_pc_curve_t &p) {
  return p.handle;
}

inline _geom2d_bezier_bisec_pc_curve_t
cast_from_geom(const Handle(Bisector_BisecPC) & d) {
  return _geom2d_bezier_bisec_pc_curve_t{d};
}

inline Handle(Geom2d_BoundedCurve)
    cast_to_geom(const _geom2d_bounded_curve_t &p) {
  return p.handle;
}

inline _geom2d_bounded_curve_t
cast_from_geom(const Handle(Geom2d_BoundedCurve) & d) {
  return _geom2d_bounded_curve_t{d};
}

inline Handle(Geom2d_BezierCurve)
    cast_to_geom(const _geom2d_bezier_curve_t &p) {
  return p.handle;
}

inline _geom2d_bezier_curve_t cast_from_geom(const Handle(Geom2d_BezierCurve) &
                                             d) {
  return _geom2d_bezier_curve_t{d};
}

inline Handle(Geom2d_BSplineCurve)
    cast_to_geom(const _geom2d_bspline_curve_t &p) {
  return p.handle;
}

inline _geom2d_bspline_curve_t
cast_from_geom(const Handle(Geom2d_BSplineCurve) & d) {
  return _geom2d_bspline_curve_t{d};
}

inline Handle(Geom2d_TrimmedCurve)
    cast_to_geom(const _geom2d_trimmed_curve_t &p) {
  return p.handle;
}

inline _geom2d_trimmed_curve_t
cast_from_geom(const Handle(Geom2d_TrimmedCurve) & d) {
  return _geom2d_trimmed_curve_t{d};
}

inline Handle(Geom2d_Conic) cast_to_geom(const _geom2d_conic_t &p) {
  return p.handle;
}

inline _geom2d_conic_t cast_from_geom(const Handle(Geom2d_Conic) & d) {
  return _geom2d_conic_t{d};
}

inline Handle(Geom2d_Circle) cast_to_geom(const _geom2d_circle_t &p) {
  return p.handle;
}

inline _geom2d_circle_t cast_from_geom(const Handle(Geom2d_Circle) & d) {
  return _geom2d_circle_t{d};
}

inline Handle(Geom2d_Ellipse) cast_to_geom(const _geom2d_ellipse_t &p) {
  return p.handle;
}

inline _geom2d_ellipse_t cast_from_geom(const Handle(Geom2d_Ellipse) & d) {
  return _geom2d_ellipse_t{d};
}

inline Handle(Geom2d_Hyperbola) cast_to_geom(const _geom2d_hyperbola_t &p) {
  return p.handle;
}

inline _geom2d_hyperbola_t cast_from_geom(const Handle(Geom2d_Hyperbola) & d) {
  return _geom2d_hyperbola_t{d};
}

inline Handle(Geom2d_Parabola) cast_to_geom(const _geom2d_parabola_t &p) {
  return p.handle;
}

inline _geom2d_parabola_t cast_from_geom(const Handle(Geom2d_Parabola) & d) {
  return _geom2d_parabola_t{d};
}

inline Handle(Geom2d_Line) cast_to_geom(const _geom2d_line_t &p) {
  return p.handle;
}

inline _geom2d_line_t cast_from_geom(const Handle(Geom2d_Line) & d) {
  return _geom2d_line_t{d};
}

inline Handle(Geom2d_OffsetCurve)
    cast_to_geom(const _geom2d_offset_curve_t &p) {
  return p.handle;
}

inline _geom2d_offset_curve_t cast_from_geom(const Handle(Geom2d_OffsetCurve) &
                                             d) {
  return _geom2d_offset_curve_t{d};
}

inline Handle(Geom2d_Point) cast_to_geom(const _geom2d_point_t &p) {
  return p.handle;
}

inline _geom2d_point_t cast_from_geom(const Handle(Geom2d_Point) & d) {
  return _geom2d_point_t{d};
}

inline Handle(Geom2d_CartesianPoint)
    cast_to_geom(const _geom2d_cartesian_point_t &p) {
  return p.handle;
}

inline _geom2d_cartesian_point_t
cast_from_geom(const Handle(Geom2d_CartesianPoint) & d) {
  return _geom2d_cartesian_point_t{d};
}

inline Handle(Geom2d_Vector) cast_to_geom(const _geom2d_vector_t &p) {
  return p.handle;
}

inline _geom2d_vector_t cast_from_geom(const Handle(Geom2d_Vector) & d) {
  return _geom2d_vector_t{d};
}

inline Handle(Geom2d_Direction) cast_to_geom(const _geom2d_direction_t &p) {
  return p.handle;
}

inline _geom2d_direction_t cast_from_geom(const Handle(Geom2d_Direction) & d) {
  return _geom2d_direction_t{d};
}

inline Handle(Geom2d_VectorWithMagnitude)
    cast_to_geom(const _geom2d_vector_with_magnitude_t &p) {
  return p.handle;
}

inline _geom2d_vector_with_magnitude_t
cast_from_geom(const Handle(Geom2d_VectorWithMagnitude) & d) {
  return _geom2d_vector_with_magnitude_t{d};
}

#endif
