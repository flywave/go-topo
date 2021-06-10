#ifndef __FLYWAVE_MESH_TOPO_GEOMETRY_CREATOR_HH__
#define __FLYWAVE_MESH_TOPO_GEOMETRY_CREATOR_HH__

#include <GC_MakeArcOfCircle.hxx>
#include <GC_MakeArcOfEllipse.hxx>
#include <GC_MakeArcOfHyperbola.hxx>
#include <GC_MakeArcOfParabola.hxx>
#include <GC_MakeCircle.hxx>
#include <GC_MakeConicalSurface.hxx>
#include <GC_MakeCylindricalSurface.hxx>
#include <GC_MakeEllipse.hxx>
#include <GC_MakeHyperbola.hxx>
#include <GC_MakeLine.hxx>
#include <GC_MakeMirror.hxx>
#include <GC_MakePlane.hxx>
#include <GC_MakeRotation.hxx>
#include <GC_MakeScale.hxx>
#include <GC_MakeSegment.hxx>
#include <GC_MakeTranslation.hxx>
#include <GC_MakeTrimmedCone.hxx>
#include <GC_MakeTrimmedCylinder.hxx>

#include <GCE2d_MakeArcOfCircle.hxx>
#include <GCE2d_MakeArcOfEllipse.hxx>
#include <GCE2d_MakeArcOfHyperbola.hxx>
#include <GCE2d_MakeArcOfParabola.hxx>
#include <GCE2d_MakeCircle.hxx>
#include <GCE2d_MakeEllipse.hxx>
#include <GCE2d_MakeHyperbola.hxx>
#include <GCE2d_MakeLine.hxx>
#include <GCE2d_MakeMirror.hxx>
#include <GCE2d_MakeParabola.hxx>
#include <GCE2d_MakeRotation.hxx>
#include <GCE2d_MakeScale.hxx>
#include <GCE2d_MakeSegment.hxx>
#include <GCE2d_MakeTranslation.hxx>

#include <GeomConvert_ApproxCurve.hxx>
#include <GeomConvert_ApproxSurface.hxx>
#include <GeomConvert_BSplineCurveKnotSplitting.hxx>
#include <GeomConvert_BSplineCurveToBezierCurve.hxx>
#include <GeomConvert_BSplineSurfaceKnotSplitting.hxx>
#include <GeomConvert_BSplineSurfaceToBezierSurface.hxx>
#include <GeomConvert_CompBezierSurfacesToBSplineSurface.hxx>
#include <GeomConvert_CompCurveToBSplineCurve.hxx>

#include <Geom2dConvert_ApproxCurve.hxx>
#include <Geom2dConvert_BSplineCurveKnotSplitting.hxx>
#include <Geom2dConvert_BSplineCurveToBezierCurve.hxx>
#include <Geom2dConvert_CompCurveToBSplineCurve.hxx>

namespace flywave {
namespace topo {

class geometry_creator {
public:
  geometry_creator() = default;
  virtual ~geometry_creator() = default;

  static Handle(Geom_TrimmedCurve)
      make_arc_of_circle(const gp_Circ &Circ, const Standard_Real Alpha1,
                         const Standard_Real Alpha2, const bool Sense);

  static Handle(Geom_TrimmedCurve)
      make_arc_of_circle(const gp_Circ &Circ, const gp_Pnt &P,
                         const Standard_Real Alpha, const bool Sense);

  static Handle(Geom_TrimmedCurve)
      make_arc_of_circle(const gp_Circ &Circ, const gp_Pnt &P1,
                         const gp_Pnt &P2, const bool Sense);

  static Handle(Geom_TrimmedCurve)
      make_arc_of_circle(const gp_Pnt &P1, const gp_Pnt &P2, const gp_Pnt &P3);

  static Handle(Geom_TrimmedCurve)
      make_arc_of_circle_vector(const gp_Pnt &P1, const gp_Vec &V,
                                const gp_Pnt &P2);

  static Handle(Geom_TrimmedCurve)
      make_arc_of_ellipse(const gp_Elips &Elips, const Standard_Real Alpha1,
                          const Standard_Real Alpha2, const bool Sense);

  static Handle(Geom_TrimmedCurve)
      make_arc_of_ellipse(const gp_Elips &Elips, const gp_Pnt &P,
                          const Standard_Real Alpha, const bool Sense);

  static Handle(Geom_TrimmedCurve)
      make_arc_of_ellipse(const gp_Elips &Elips, const gp_Pnt &P1,
                          const gp_Pnt &P2, const bool Sense);

  static Handle(Geom_TrimmedCurve)
      make_arc_of_hyperbola(const gp_Hypr &Hypr, const Standard_Real Alpha1,
                            const Standard_Real Alpha2, const bool Sense);

  static Handle(Geom_TrimmedCurve)
      make_arc_of_hyperbola(const gp_Hypr &Hypr, const gp_Pnt &P,
                            const Standard_Real Alpha, const bool Sense);

  static Handle(Geom_TrimmedCurve)
      make_arc_of_hyperbola(const gp_Hypr &Hypr, const gp_Pnt &P1,
                            const gp_Pnt &P2, const bool Sense);

  static Handle(Geom_TrimmedCurve)
      make_arc_of_parabola(const gp_Parab &Parab, const Standard_Real Alpha1,
                           const Standard_Real Alpha2, const bool Sense);

  static Handle(Geom_TrimmedCurve)
      make_arc_of_parabola(const gp_Parab &Parab, const gp_Pnt &P,
                           const Standard_Real Alpha, const bool Sense);

  static Handle(Geom_TrimmedCurve)
      make_arc_of_parabola(const gp_Parab &Parab, const gp_Pnt &P1,
                           const gp_Pnt &P2, const bool Sense);

  static Handle(Geom_Circle) make_circle(const gp_Circ &C);

  static Handle(Geom_Circle)
      make_circle(const gp_Ax2 &A2, const Standard_Real Radius);

  static Handle(Geom_Circle)
      make_circle(const gp_Circ &Circ, const Standard_Real Dist);

  static Handle(Geom_Circle)
      make_circle(const gp_Circ &Circ, const gp_Pnt &Point);

  static Handle(Geom_Circle)
      make_circle(const gp_Pnt &P1, const gp_Pnt &P2, const gp_Pnt &P3);

  static Handle(Geom_Circle)
      make_circle(const gp_Pnt &Center, const gp_Dir &Norm,
                  const Standard_Real Radius);

  static Handle(Geom_Circle)
      make_circle(const gp_Pnt &Center, const gp_Pnt &PtAxis,
                  const Standard_Real Radius);

  static Handle(Geom_Circle)
      make_circle(const gp_Ax1 &Axis, const Standard_Real Radius);

  static Handle(Geom_Ellipse) make_ellipse(const gp_Elips &E);

  static Handle(Geom_Ellipse)
      make_ellipse(const gp_Ax2 &A2, const Standard_Real MajorRadius,
                   const Standard_Real MinorRadius);

  static Handle(Geom_Ellipse)
      make_ellipse(const gp_Pnt &S1, const gp_Pnt &S2, const gp_Pnt &Center);

  static Handle(Geom_Hyperbola) make_hyperbola(const gp_Hypr &H);

  static Handle(Geom_Hyperbola)
      make_hyperbola(const gp_Ax2 &A2, const Standard_Real MajorRadius,
                     const Standard_Real MinorRadius);

  static Handle(Geom_Hyperbola)
      make_hyperbola(const gp_Pnt &S1, const gp_Pnt &S2, const gp_Pnt &Center);

  static Handle(Geom_ConicalSurface)
      make_conical_surface(const gp_Ax2 &A2, const Standard_Real Ang,
                           const Standard_Real Radius);

  static Handle(Geom_ConicalSurface) make_conical_surface(const gp_Cone &C);

  static Handle(Geom_ConicalSurface)
      make_conical_surface(const gp_Pnt &P1, const gp_Pnt &P2, const gp_Pnt &P3,
                           const gp_Pnt &P4);

  static Handle(Geom_ConicalSurface)
      make_conical_surface(const gp_Pnt &P1, const gp_Pnt &P2,
                           const Standard_Real R1, const Standard_Real R2);

  static Handle(Geom_CylindricalSurface)
      make_cylindrical_surface(const gp_Ax2 &A2, const Standard_Real Radius);

  static Handle(Geom_CylindricalSurface)
      make_cylindrical_surface(const gp_Cylinder &C);

  static Handle(Geom_CylindricalSurface)
      make_cylindrical_surface(const gp_Cylinder &Cyl, const gp_Pnt &Point);

  static Handle(Geom_CylindricalSurface)
      make_cylindrical_surface(const gp_Cylinder &Cyl,
                               const Standard_Real Dist);

  static Handle(Geom_CylindricalSurface)
      make_cylindrical_surface(const gp_Pnt &P1, const gp_Pnt &P2,
                               const gp_Pnt &P3);

  static Handle(Geom_CylindricalSurface)
      make_cylindrical_surface(const gp_Ax1 &Axis, const Standard_Real Radius);

  static Handle(Geom_CylindricalSurface)
      make_cylindrical_surface(const gp_Circ &Circ);

  static Handle(Geom_Line) make_line(const gp_Ax1 &A1);

  static Handle(Geom_Line) make_line(const gp_Lin &L);

  static Handle(Geom_Line) make_line(const gp_Pnt &P, const gp_Dir &V);

  static Handle(Geom_Line) make_line(const gp_Lin &Lin, const gp_Pnt &Point);

  static Handle(Geom_Line) make_line(const gp_Pnt &P1, const gp_Pnt &P2);

  static Handle(Geom_Transformation) make_mirror(const gp_Pnt &Point);

  static Handle(Geom_Transformation) make_mirror(const gp_Ax1 &Axis);

  static Handle(Geom_Transformation) make_mirror(const gp_Lin &Line);

  static Handle(Geom_Transformation)
      make_mirror(const gp_Pnt &Point, const gp_Dir &Direc);

  static Handle(Geom_Transformation) make_mirror(const gp_Pln &Plane);

  static Handle(Geom_Transformation) make_mirror(const gp_Ax2 &Plane);

  static Handle(Geom_Transformation)
      make_rotation(const gp_Lin &Line, const Standard_Real Angle);

  static Handle(Geom_Transformation)
      make_rotation(const gp_Ax1 &Axis, const Standard_Real Angle);

  static Handle(Geom_Transformation)
      make_rotation(const gp_Pnt &Point, const gp_Dir &Direc,
                    const Standard_Real Angle);

  static Handle(Geom_Transformation) make_translation(const gp_Vec &Vect);

  static Handle(Geom_Transformation)
      make_translation(const gp_Pnt &Point1, const gp_Pnt &Point2);

  static Handle(Geom_Transformation)
      make_scale(const gp_Pnt &Point, const Standard_Real Scale);

  static Handle(Geom_Plane) make_plane(const gp_Pln &Pl);

  static Handle(Geom_Plane) make_plane(const gp_Pnt &P, const gp_Dir &V);

  static Handle(Geom_Plane)
      make_plane(const Standard_Real A, const Standard_Real B,
                 const Standard_Real C, const Standard_Real D);

  static Handle(Geom_Plane) make_plane(const gp_Pln &Pln, const gp_Pnt &Point);

  static Handle(Geom_Plane)
      make_plane(const gp_Pln &Pln, const Standard_Real Dist);

  static Handle(Geom_Plane)
      make_plane(const gp_Pnt &P1, const gp_Pnt &P2, const gp_Pnt &P3);

  static Handle(Geom_Plane) make_plane(const gp_Ax1 &Axis);

  static Handle(Geom_TrimmedCurve)
      make_segment(const gp_Pnt &P1, const gp_Pnt &P2);

  static Handle(Geom_TrimmedCurve)
      make_segment(const gp_Lin &Line, const Standard_Real U1,
                   const Standard_Real U2);

  static Handle(Geom_TrimmedCurve)
      make_segment(const gp_Lin &Line, const gp_Pnt &Point,
                   const Standard_Real Ulast);

  static Handle(Geom_TrimmedCurve)
      make_segment(const gp_Lin &Line, const gp_Pnt &P1, const gp_Pnt &P2);

  static Handle(Geom_RectangularTrimmedSurface)
      make_trimmed_cone(const gp_Pnt &P1, const gp_Pnt &P2, const gp_Pnt &P3,
                        const gp_Pnt &P4);

  static Handle(Geom_RectangularTrimmedSurface)
      make_trimmed_cone(const gp_Pnt &P1, const gp_Pnt &P2,
                        const Standard_Real R1, const Standard_Real R2);

  static Handle(Geom_RectangularTrimmedSurface)
      make_trimmed_cylinder(const gp_Pnt &P1, const gp_Pnt &P2,
                            const gp_Pnt &P3);

  static Handle(Geom_RectangularTrimmedSurface)
      make_trimmed_cylinder(const gp_Circ &Circ, const Standard_Real Height);

  static Handle(Geom_RectangularTrimmedSurface)
      make_trimmed_cylinder(const gp_Ax1 &A1, const Standard_Real Radius,
                            const Standard_Real Height);

  static Handle(Geom2d_TrimmedCurve)
      make_arc_of_circle(const gp_Circ2d &Circ, const Standard_Real Alpha1,
                         const Standard_Real Alpha2, const bool Sense = true);

  static Handle(Geom2d_TrimmedCurve)
      make_arc_of_circle(const gp_Circ2d &Circ, const gp_Pnt2d &P,
                         const Standard_Real Alpha, const bool Sense = true);

  static Handle(Geom2d_TrimmedCurve)
      make_arc_of_circle(const gp_Circ2d &Circ, const gp_Pnt2d &P1,
                         const gp_Pnt2d &P2, const bool Sense = true);

  static Handle(Geom2d_TrimmedCurve)
      make_arc_of_circle(const gp_Pnt2d &P1, const gp_Pnt2d &P2,
                         const gp_Pnt2d &P3);

  static Handle(Geom2d_TrimmedCurve)
      make_arc_of_circle_vector(const gp_Pnt2d &P1, const gp_Vec2d &V,
                                const gp_Pnt2d &P2);

  static Handle(Geom2d_TrimmedCurve)
      make_arc_of_ellipse(const gp_Elips2d &Elips, const Standard_Real Alpha1,
                          const Standard_Real Alpha2, const bool Sense = true);

  static Handle(Geom2d_TrimmedCurve)
      make_arc_of_ellipse(const gp_Elips2d &Elips, const gp_Pnt2d &P,
                          const Standard_Real Alpha, const bool Sense = true);

  static Handle(Geom2d_TrimmedCurve)
      make_arc_of_ellipse(const gp_Elips2d &Elips, const gp_Pnt2d &P1,
                          const gp_Pnt2d &P2, const bool Sense = true);

  static Handle(Geom2d_TrimmedCurve)
      make_arc_of_hyperbola(const gp_Hypr2d &Hypr, const Standard_Real Alpha1,
                            const Standard_Real Alpha2,
                            const bool Sense = true);

  static Handle(Geom2d_TrimmedCurve)
      make_arc_of_hyperbola(const gp_Hypr2d &Hypr, const gp_Pnt2d &P,
                            const Standard_Real Alpha, const bool Sense = true);

  static Handle(Geom2d_TrimmedCurve)
      make_arc_of_hyperbola(const gp_Hypr2d &Hypr, const gp_Pnt2d &P1,
                            const gp_Pnt2d &P2, const bool Sense = true);

  static Handle(Geom2d_TrimmedCurve)
      make_arc_of_parabola(const gp_Parab2d &Parab, const Standard_Real Alpha1,
                           const Standard_Real Alpha2, const bool Sense = true);

  static Handle(Geom2d_TrimmedCurve)
      make_arc_of_parabola(const gp_Parab2d &Parab, const gp_Pnt2d &P,
                           const Standard_Real Alpha, const bool Sense = true);

  static Handle(Geom2d_TrimmedCurve)
      make_arc_of_parabola(const gp_Parab2d &Parab, const gp_Pnt2d &P1,
                           const gp_Pnt2d &P2, const bool Sense = true);

  static Handle(Geom2d_Circle) make_circle(const gp_Circ2d &C);

  static Handle(Geom2d_Circle)
      make_circle(const gp_Ax2d &A, const Standard_Real Radius,
                  const bool Sense = true);

  static Handle(Geom2d_Circle)
      make_circle(const gp_Ax22d &A, const Standard_Real Radius);

  static Handle(Geom2d_Circle)
      make_circle(const gp_Circ2d &Circ, const Standard_Real Dist);

  static Handle(Geom2d_Circle)
      make_circle(const gp_Circ2d &Circ, const gp_Pnt2d &Point);

  static Handle(Geom2d_Circle)
      make_circle(const gp_Pnt2d &P1, const gp_Pnt2d &P2, const gp_Pnt2d &P3);

  static Handle(Geom2d_Circle)
      make_circle(const gp_Pnt2d &P, const Standard_Real Radius,
                  const bool Sense = true);

  static Handle(Geom2d_Circle)
      make_circle(const gp_Pnt2d &Center, const gp_Pnt2d &Point,
                  const bool Sense = true);

  static Handle(Geom2d_Ellipse) make_ellipse(const gp_Elips2d &E);

  static Handle(Geom2d_Ellipse)
      make_ellipse(const gp_Ax2d &MajorAxis, const Standard_Real MajorRadius,
                   const Standard_Real MinorRadius, const bool Sense = true);

  static Handle(Geom2d_Ellipse)
      make_ellipse(const gp_Ax22d &Axis, const Standard_Real MajorRadius,
                   const Standard_Real MinorRadius);

  static Handle(Geom2d_Ellipse)
      make_ellipse(const gp_Pnt2d &S1, const gp_Pnt2d &S2,
                   const gp_Pnt2d &Center);

  static Handle(Geom2d_Hyperbola) make_hyperbola(const gp_Hypr2d &H);

  static Handle(Geom2d_Hyperbola)
      make_hyperbola(const gp_Ax2d &MajorAxis, const Standard_Real MajorRadius,
                     const Standard_Real MinorRadius, const bool Sense);

  static Handle(Geom2d_Hyperbola)
      make_hyperbola(const gp_Ax22d &Axis, const Standard_Real MajorRadius,
                     const Standard_Real MinorRadius);

  static Handle(Geom2d_Hyperbola)
      make_hyperbola(const gp_Pnt2d &S1, const gp_Pnt2d &S2,
                     const gp_Pnt2d &Center);

  static Handle(Geom2d_Line) make_line(const gp_Ax2d &A);

  static Handle(Geom2d_Line) make_line(const gp_Lin2d &L);

  static Handle(Geom2d_Line) make_line(const gp_Pnt2d &P, const gp_Dir2d &V);

  static Handle(Geom2d_Line)
      make_line(const gp_Lin2d &Lin, const gp_Pnt2d &Point);

  static Handle(Geom2d_Line)
      make_line(const gp_Lin2d &Lin, const Standard_Real Dist);

  static Handle(Geom2d_Line) make_line(const gp_Pnt2d &P1, const gp_Pnt2d &P2);

  static Handle(Geom2d_Parabola) make_parabola(const gp_Parab2d &Prb);

  static Handle(Geom2d_Parabola)
      make_parabola(const gp_Ax22d &Axis, const Standard_Real Focal);

  static Handle(Geom2d_Parabola)
      make_parabola(const gp_Ax2d &MirrorAxis, const Standard_Real Focal,
                    const bool Sense);

  static Handle(Geom2d_Parabola)
      make_parabola(const gp_Ax2d &D, const gp_Pnt2d &F,
                    const bool Sense = true);

  static Handle(Geom2d_Parabola)
      make_parabola(const gp_Pnt2d &S1, const gp_Pnt2d &O);

  static Handle(Geom2d_TrimmedCurve)
      make_segment(const gp_Pnt2d &P1, const gp_Pnt2d &P2);

  static Handle(Geom2d_TrimmedCurve)
      make_segment(const gp_Pnt2d &P1, const gp_Dir2d &V, const gp_Pnt2d &P2);

  static Handle(Geom2d_TrimmedCurve)
      make_segment(const gp_Lin2d &Line, const Standard_Real U1,
                   const Standard_Real U2);

  static Handle(Geom2d_TrimmedCurve)
      make_segment(const gp_Lin2d &Line, const gp_Pnt2d &Point,
                   const Standard_Real Ulast);

  static Handle(Geom2d_TrimmedCurve)
      make_segment(const gp_Lin2d &Line, const gp_Pnt2d &P1,
                   const gp_Pnt2d &P2);

  static Handle(Geom2d_Transformation) make_mirror(const gp_Pnt2d &Point);

  static Handle(Geom2d_Transformation) make_mirror(const gp_Ax2d &Axis);

  static Handle(Geom2d_Transformation) make_mirror(const gp_Lin2d &Line);

  static Handle(Geom2d_Transformation)
      make_mirror(const gp_Pnt2d &Point, const gp_Dir2d &Direc);

  static Handle(Geom2d_Transformation)
      make_rotation(const gp_Pnt2d &Point, const Standard_Real Angle);

  static Handle(Geom2d_Transformation)
      make_scale(const gp_Pnt2d &Point, const Standard_Real Scale);

  static Handle(Geom2d_Transformation) make_translation(const gp_Vec2d &Vect);

  static Handle(Geom2d_Transformation)
      make_translation(const gp_Pnt2d &Point1, const gp_Pnt2d &Point2);

  static Handle(Geom_BSplineCurve)
      convert_approx_curve(const Handle(Geom_Curve) & Curve,
                           const Standard_Real Tol3d, const GeomAbs_Shape Order,
                           const Standard_Integer MaxSegments,
                           const Standard_Integer MaxDegree);

  static Handle(Geom_BSplineSurface) convert_approx_surface(
      const Handle(Geom_Surface) & Surf, const Standard_Real Tol3d,
      const GeomAbs_Shape UContinuity, const GeomAbs_Shape VContinuity,
      const Standard_Integer MaxDegU, const Standard_Integer MaxDegV,
      const Standard_Integer MaxSegments, const Standard_Integer PrecisCode);
};

} // namespace topo
} // namespace flywave

#endif // __FLYWAVE_MESH_TOPO_GEOMETRY_CREATOR_HH__
