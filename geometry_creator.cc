#include "geometry_creator.hh"

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

geom_trimmed_curve geometry_creator::make_arc_of_circle(
    const circ &Circ, const Standard_Real Alpha1, const Standard_Real Alpha2,
    const bool Sense) {
  GC_MakeArcOfCircle maoc(cast_to_gp(Circ), Alpha1, Alpha2, Sense);
  return geom_trimmed_curve(maoc);
}

geom_trimmed_curve geometry_creator::make_arc_of_circle(
    const circ &Circ, const vector3<Standard_Real> &P,
    const Standard_Real Alpha, const bool Sense) {
  GC_MakeArcOfCircle maoc(cast_to_gp(Circ), cast_to_gp(P), Alpha, Sense);
  return geom_trimmed_curve(maoc);
}

geom_trimmed_curve geometry_creator::make_arc_of_circle(
    const circ &Circ, const vector3<Standard_Real> &P1,
    const vector3<Standard_Real> &P2, const bool Sense) {
  GC_MakeArcOfCircle maoc(cast_to_gp(Circ), cast_to_gp(P1), cast_to_gp(P2),
                          Sense);
  return geom_trimmed_curve(maoc);
}

geom_trimmed_curve
geometry_creator::make_arc_of_circle(const vector3<Standard_Real> &P1,
                                     const vector3<Standard_Real> &P2,
                                     const vector3<Standard_Real> &P3) {
  GC_MakeArcOfCircle maoc(cast_to_gp(P1), gp_Pnt(cast_to_gp(P2)),
                          cast_to_gp(P3));
  return geom_trimmed_curve(maoc);
}

geom_trimmed_curve
geometry_creator::make_arc_of_circle_vector(const vector3<Standard_Real> &P1,
                                            const vector3<Standard_Real> &V,
                                            const vector3<Standard_Real> &P2) {
  GC_MakeArcOfCircle maoc(cast_to_gp(P1), gp_Vec(cast_to_gp(V)),
                          cast_to_gp(P2));
  return geom_trimmed_curve(maoc);
}

geom_trimmed_curve geometry_creator::make_arc_of_ellipse(
    const elips &Elips, const Standard_Real Alpha1, const Standard_Real Alpha2,
    const bool Sense) {
  GC_MakeArcOfEllipse maoe(cast_to_gp(Elips), Alpha1, Alpha2, Sense);
  return geom_trimmed_curve(maoe);
}

geom_trimmed_curve geometry_creator::make_arc_of_ellipse(
    const elips &Elips, const vector3<Standard_Real> &P,
    const Standard_Real Alpha, const bool Sense) {
  GC_MakeArcOfEllipse maoe(cast_to_gp(Elips), cast_to_gp(P), Alpha, Sense);
  return geom_trimmed_curve(maoe);
}

geom_trimmed_curve geometry_creator::make_arc_of_ellipse(
    const elips &Elips, const vector3<Standard_Real> &P1,
    const vector3<Standard_Real> &P2, const bool Sense) {
  GC_MakeArcOfEllipse maoe(cast_to_gp(Elips), cast_to_gp(P1), cast_to_gp(P2),
                           Sense);
  return geom_trimmed_curve(maoe);
}

geom_trimmed_curve geometry_creator::make_arc_of_hyperbola(
    const hyperbola &Hypr, const Standard_Real Alpha1,
    const Standard_Real Alpha2, const bool Sense) {
  GC_MakeArcOfHyperbola maoe(cast_to_gp(Hypr), Alpha1, Alpha2, Sense);
  return geom_trimmed_curve(maoe);
}

geom_trimmed_curve geometry_creator::make_arc_of_hyperbola(
    const hyperbola &Hypr, const vector3<Standard_Real> &P,
    const Standard_Real Alpha, const bool Sense) {
  GC_MakeArcOfHyperbola maoe(cast_to_gp(Hypr), cast_to_gp(P), Alpha, Sense);
  return geom_trimmed_curve(maoe);
}

geom_trimmed_curve geometry_creator::make_arc_of_hyperbola(
    const hyperbola &Hypr, const vector3<Standard_Real> &P1,
    const vector3<Standard_Real> &P2, const bool Sense) {
  GC_MakeArcOfHyperbola maoe(cast_to_gp(Hypr), cast_to_gp(P1), cast_to_gp(P2),
                             Sense);
  return geom_trimmed_curve(maoe);
}

geom_trimmed_curve geometry_creator::make_arc_of_parabola(
    const parabola &Parab, const Standard_Real Alpha1,
    const Standard_Real Alpha2, const bool Sense) {
  GC_MakeArcOfParabola maoe(cast_to_gp(Parab), Alpha1, Alpha2, Sense);
  return geom_trimmed_curve(maoe);
}

geom_trimmed_curve geometry_creator::make_arc_of_parabola(
    const parabola &Parab, const vector3<Standard_Real> &P,
    const Standard_Real Alpha, const bool Sense) {
  GC_MakeArcOfParabola maoe(cast_to_gp(Parab), cast_to_gp(P), Alpha, Sense);
  return geom_trimmed_curve(maoe);
}

geom_trimmed_curve geometry_creator::make_arc_of_parabola(
    const parabola &Parab, const vector3<Standard_Real> &P1,
    const vector3<Standard_Real> &P2, const bool Sense) {
  GC_MakeArcOfParabola maoe(cast_to_gp(Parab), cast_to_gp(P1), cast_to_gp(P2),
                            Sense);
  return geom_trimmed_curve(maoe);
}

geom_circle geometry_creator::make_circle(const circ &C) {
  GC_MakeCircle mc(cast_to_gp(C));
  return geom_circle(mc);
}

geom_circle geometry_creator::make_circle(const axis2 &A2,
                                          const Standard_Real Radius) {
  GC_MakeCircle mc(cast_to_gp(A2), Radius);
  return geom_circle(mc);
}

geom_circle geometry_creator::make_circle(const circ &Circ,
                                          const Standard_Real Dist) {
  GC_MakeCircle mc(cast_to_gp(Circ), Dist);
  return geom_circle(mc);
}

geom_circle geometry_creator::make_circle(const circ &Circ,
                                          const vector3<Standard_Real> &Point) {
  GC_MakeCircle mc(cast_to_gp(Circ), cast_to_gp(Point));
  return geom_circle(mc);
}

geom_circle geometry_creator::make_circle(const vector3<Standard_Real> &P1,
                                          const vector3<Standard_Real> &P2,
                                          const vector3<Standard_Real> &P3) {
  GC_MakeCircle mc(cast_to_gp(P1), cast_to_gp(P2), cast_to_gp(P3));
  return geom_circle(mc);
}

geom_circle geometry_creator::make_circle(const vector3<Standard_Real> &Center,
                                          const dir &Norm,
                                          const Standard_Real Radius) {
  GC_MakeCircle mc(cast_to_gp(Center), cast_to_gp(Norm), Radius);
  return geom_circle(mc);
}

geom_circle geometry_creator::make_circle(const vector3<Standard_Real> &Center,
                                          const vector3<Standard_Real> &PtAxis,
                                          const Standard_Real Radius) {
  GC_MakeCircle mc(cast_to_gp(Center), gp_Pnt(cast_to_gp(PtAxis)), Radius);
  return geom_circle(mc);
}

geom_circle geometry_creator::make_circle(const axis1 &Axis,
                                          const Standard_Real Radius) {
  GC_MakeCircle mc(cast_to_gp(Axis), Radius);
  return geom_circle(mc);
}

geom_ellipse geometry_creator::make_ellipse(const elips &E) {
  GC_MakeEllipse mc(cast_to_gp(E));
  return geom_ellipse(mc);
}

geom_ellipse geometry_creator::make_ellipse(const axis2 &A2,
                                            const Standard_Real MajorRadius,
                                            const Standard_Real MinorRadius) {
  GC_MakeEllipse mc(cast_to_gp(A2), MajorRadius, MinorRadius);
  return geom_ellipse(mc);
}

geom_ellipse
geometry_creator::make_ellipse(const vector3<Standard_Real> &S1,
                               const vector3<Standard_Real> &S2,
                               const vector3<Standard_Real> &Center) {
  GC_MakeEllipse mc(cast_to_gp(S1), cast_to_gp(S2), cast_to_gp(Center));
  return geom_ellipse(mc);
}

geom_hyperbola geometry_creator::make_hyperbola(const hyperbola &H) {
  GC_MakeHyperbola mc(cast_to_gp(H));
  return geom_hyperbola(mc);
}

geom_hyperbola
geometry_creator::make_hyperbola(const axis2 &A2,
                                 const Standard_Real MajorRadius,
                                 const Standard_Real MinorRadius) {
  GC_MakeHyperbola mc(cast_to_gp(A2), MajorRadius, MinorRadius);
  return geom_hyperbola(mc);
}

geom_hyperbola
geometry_creator::make_hyperbola(const vector3<Standard_Real> &S1,
                                 const vector3<Standard_Real> &S2,
                                 const vector3<Standard_Real> &Center) {
  GC_MakeHyperbola mc(cast_to_gp(S1), cast_to_gp(S2), cast_to_gp(Center));
  return geom_hyperbola(mc);
}

geom_conical_surface
geometry_creator::make_conical_surface(const axis2 &A2, const Standard_Real Ang,
                                       const Standard_Real Radius) {
  GC_MakeConicalSurface mcs(cast_to_gp(A2), Ang, Radius);
  return geom_conical_surface(mcs);
}

geom_conical_surface geometry_creator::make_conical_surface(const cone &C) {
  GC_MakeConicalSurface mcs(cast_to_gp(C));
  return geom_conical_surface(mcs);
}

geom_conical_surface geometry_creator::make_conical_surface(
    const vector3<Standard_Real> &P1, const vector3<Standard_Real> &P2,
    const vector3<Standard_Real> &P3, const vector3<Standard_Real> &P4) {
  GC_MakeConicalSurface mcs(cast_to_gp(P1), cast_to_gp(P2), cast_to_gp(P3),
                            cast_to_gp(P4));
  return geom_conical_surface(mcs);
}

geom_conical_surface geometry_creator::make_conical_surface(
    const vector3<Standard_Real> &P1, const vector3<Standard_Real> &P2,
    const Standard_Real R1, const Standard_Real R2) {
  GC_MakeConicalSurface mcs(cast_to_gp(P1), cast_to_gp(P2), cast_to_gp(R1),
                            cast_to_gp(R2));
  return geom_conical_surface(mcs);
}

geom_cylindrical_surface
geometry_creator::make_cylindrical_surface(const axis2 &A2,
                                           const Standard_Real Radius) {
  GC_MakeCylindricalSurface mcs(cast_to_gp(A2), Radius);
  return geom_cylindrical_surface(mcs);
}

geom_cylindrical_surface
geometry_creator::make_cylindrical_surface(const cylinder &C) {
  GC_MakeCylindricalSurface mcs(cast_to_gp(C));
  return geom_cylindrical_surface(mcs);
}

geom_cylindrical_surface geometry_creator::make_cylindrical_surface(
    const cylinder &Cyl, const vector3<Standard_Real> &Point) {
  GC_MakeCylindricalSurface mcs(cast_to_gp(Cyl), cast_to_gp(Point));
  return geom_cylindrical_surface(mcs);
}

geom_cylindrical_surface
geometry_creator::make_cylindrical_surface(const cylinder &Cyl,
                                           const Standard_Real Dist) {
  GC_MakeCylindricalSurface mcs(cast_to_gp(Cyl), Dist);
  return geom_cylindrical_surface(mcs);
}

geom_cylindrical_surface
geometry_creator::make_cylindrical_surface(const vector3<Standard_Real> &P1,
                                           const vector3<Standard_Real> &P2,
                                           const vector3<Standard_Real> &P3) {
  GC_MakeCylindricalSurface mcs(cast_to_gp(P1), cast_to_gp(P2), cast_to_gp(P3));
  return geom_cylindrical_surface(mcs);
}

geom_cylindrical_surface
geometry_creator::make_cylindrical_surface(const axis1 &Axis,
                                           const Standard_Real Radius) {
  GC_MakeCylindricalSurface mcs(cast_to_gp(Axis), Radius);
  return geom_cylindrical_surface(mcs);
}

geom_cylindrical_surface
geometry_creator::make_cylindrical_surface(const circ &Circ) {
  GC_MakeCylindricalSurface mcs(cast_to_gp(Circ));
  return geom_cylindrical_surface(mcs);
}

geom_line geometry_creator::make_line(const axis1 &A1) {
  GC_MakeLine ml(cast_to_gp(A1));
  return geom_line(ml);
}

geom_line geometry_creator::make_line(const line &L) {
  GC_MakeLine ml(cast_to_gp(L));
  return geom_line(ml);
}

geom_line geometry_creator::make_line(const vector3<Standard_Real> &P,
                                      const dir &V) {
  GC_MakeLine ml(cast_to_gp(P), cast_to_gp(V));
  return geom_line(ml);
}

geom_line geometry_creator::make_line(const line &Lin,
                                      const vector3<Standard_Real> &Point) {
  GC_MakeLine ml(cast_to_gp(Lin), cast_to_gp(Point));
  return geom_line(ml);
}

geom_line geometry_creator::make_line(const vector3<Standard_Real> &P1,
                                      const vector3<Standard_Real> &P2) {
  GC_MakeLine ml(gp_Pnt(cast_to_gp(P1)), gp_Pnt(cast_to_gp(P2)));
  return geom_line(ml);
}

geom_transformation
geometry_creator::make_mirror(const vector3<Standard_Real> &Point) {
  GC_MakeMirror ml(cast_to_gp(Point));
  return geom_transformation(ml);
}

geom_transformation geometry_creator::make_mirror(const axis1 &Axis) {
  GC_MakeMirror ml(cast_to_gp(Axis));
  return geom_transformation(ml);
}

geom_transformation geometry_creator::make_mirror(const line &Line) {
  GC_MakeMirror ml(cast_to_gp(Line));
  return geom_transformation(ml);
}

geom_transformation
geometry_creator::make_mirror(const vector3<Standard_Real> &Point,
                              const dir &Direc) {
  GC_MakeMirror ml(cast_to_gp(Point), cast_to_gp(Direc));
  return geom_transformation(ml);
}

geom_transformation geometry_creator::make_mirror(const plane &Plane) {
  GC_MakeMirror ml(cast_to_gp(Plane));
  return geom_transformation(ml);
}

geom_transformation geometry_creator::make_mirror(const axis2 &Plane) {
  GC_MakeMirror ml(cast_to_gp(Plane));
  return geom_transformation(ml);
}

geom_transformation geometry_creator::make_rotation(const line &Line,
                                                    const Standard_Real Angle) {
  GC_MakeRotation mr(cast_to_gp(Line), Angle);
  return geom_transformation(mr);
}

geom_transformation geometry_creator::make_rotation(const axis1 &Axis,
                                                    const Standard_Real Angle) {
  GC_MakeRotation mr(cast_to_gp(Axis), Angle);
  return geom_transformation(mr);
}

geom_transformation
geometry_creator::make_rotation(const vector3<Standard_Real> &Point,
                                const dir &Direc, const Standard_Real Angle) {
  GC_MakeRotation mr(cast_to_gp(Point), cast_to_gp(Direc), Angle);
  return geom_transformation(mr);
}

geom_transformation
geometry_creator::make_translation(const vector3<Standard_Real> &Vect) {
  GC_MakeTranslation mr(cast_to_gp(Vect));
  return geom_transformation(mr);
}

geom_transformation
geometry_creator::make_translation(const vector3<Standard_Real> &Point1,
                                   const vector3<Standard_Real> &Point2) {
  GC_MakeTranslation mr(cast_to_gp(Point1), cast_to_gp(Point2));
  return geom_transformation(mr);
}

geom_transformation
geometry_creator::make_scale(const vector3<Standard_Real> &Point,
                             const Standard_Real Scale) {
  GC_MakeScale mr(cast_to_gp(Point), Scale);
  return geom_transformation(mr);
}

geom_plane_surface geometry_creator::make_plane(const plane &Pl) {
  GC_MakePlane mr(cast_to_gp(Pl));
  return geom_plane_surface(mr);
}

geom_plane_surface geometry_creator::make_plane(const vector3<Standard_Real> &P,
                                                const dir &V) {
  GC_MakePlane mr(cast_to_gp(P), cast_to_gp(V));
  return geom_plane_surface(mr);
}

geom_plane_surface geometry_creator::make_plane(const Standard_Real A,
                                                const Standard_Real B,
                                                const Standard_Real C,
                                                const Standard_Real D) {
  GC_MakePlane mr(cast_to_gp(A), cast_to_gp(B), cast_to_gp(C), cast_to_gp(D));
  return geom_plane_surface(mr);
}

geom_plane_surface
geometry_creator::make_plane(const plane &Pln,
                             const vector3<Standard_Real> &Point) {
  GC_MakePlane mr(cast_to_gp(Pln), cast_to_gp(Point));
  return geom_plane_surface(mr);
}

geom_plane_surface geometry_creator::make_plane(const plane &Pln,
                                                const Standard_Real Dist) {
  GC_MakePlane mr(cast_to_gp(Pln), Dist);
  return geom_plane_surface(mr);
}

geom_plane_surface
geometry_creator::make_plane(const vector3<Standard_Real> &P1,
                             const vector3<Standard_Real> &P2,
                             const vector3<Standard_Real> &P3) {
  GC_MakePlane mr(cast_to_gp(P1), cast_to_gp(P2), cast_to_gp(P3));
  return geom_plane_surface(mr);
}

geom_plane_surface geometry_creator::make_plane(const axis1 &Axis) {
  GC_MakePlane mr(cast_to_gp(Axis));
  return geom_plane_surface(mr);
}

geom_trimmed_curve
geometry_creator::make_segment(const vector3<Standard_Real> &P1,
                               const vector3<Standard_Real> &P2) {
  GC_MakeSegment ms(cast_to_gp(P1), cast_to_gp(P2));
  return geom_trimmed_curve(ms);
}

geom_trimmed_curve geometry_creator::make_segment(const line &Line,
                                                  const Standard_Real U1,
                                                  const Standard_Real U2) {
  GC_MakeSegment ms(cast_to_gp(Line), U1, U2);
  return geom_trimmed_curve(ms);
}

geom_trimmed_curve
geometry_creator::make_segment(const line &Line,
                               const vector3<Standard_Real> &Point,
                               const Standard_Real Ulast) {
  GC_MakeSegment ms(cast_to_gp(Line), cast_to_gp(Point), Ulast);
  return geom_trimmed_curve(ms);
}

geom_trimmed_curve
geometry_creator::make_segment(const line &Line,
                               const vector3<Standard_Real> &P1,
                               const vector3<Standard_Real> &P2) {
  GC_MakeSegment ms(cast_to_gp(Line), cast_to_gp(P1), cast_to_gp(P2));
  return geom_trimmed_curve(ms);
}

geom_rectangular_trimmed_surface geometry_creator::make_trimmed_cone(
    const vector3<Standard_Real> &P1, const vector3<Standard_Real> &P2,
    const vector3<Standard_Real> &P3, const vector3<Standard_Real> &P4) {
  GC_MakeTrimmedCone mtc(cast_to_gp(P1), cast_to_gp(P2), cast_to_gp(P3),
                         cast_to_gp(P4));
  return geom_rectangular_trimmed_surface(mtc);
}

geom_rectangular_trimmed_surface geometry_creator::make_trimmed_cone(
    const vector3<Standard_Real> &P1, const vector3<Standard_Real> &P2,
    const Standard_Real R1, const Standard_Real R2) {
  GC_MakeTrimmedCone mtc(cast_to_gp(P1), cast_to_gp(P2), R1, R2);
  return geom_rectangular_trimmed_surface(mtc);
}

geom_rectangular_trimmed_surface
geometry_creator::make_trimmed_cylinder(const vector3<Standard_Real> &P1,
                                        const vector3<Standard_Real> &P2,
                                        const vector3<Standard_Real> &P3) {
  GC_MakeTrimmedCylinder mtc(cast_to_gp(P1), cast_to_gp(P2), cast_to_gp(P3));
  return geom_rectangular_trimmed_surface(mtc);
}

geom_rectangular_trimmed_surface
geometry_creator::make_trimmed_cylinder(const circ &Circ,
                                        const Standard_Real Height) {
  GC_MakeTrimmedCylinder mtc(cast_to_gp(Circ), Height);
  return geom_rectangular_trimmed_surface(mtc);
}

geom_rectangular_trimmed_surface geometry_creator::make_trimmed_cylinder(
    const axis1 &A1, const Standard_Real Radius, const Standard_Real Height) {
  GC_MakeTrimmedCylinder mtc(cast_to_gp(A1), Radius, Height);
  return geom_rectangular_trimmed_surface(mtc);
}

geom2d_trimmed_curve geometry_creator::make_arc_of_circle(
    const circ2d &Circ, const Standard_Real Alpha1, const Standard_Real Alpha2,
    const bool Sense) {
  GCE2d_MakeArcOfCircle maoc(cast_to_gp(Circ), Alpha1, Alpha2, Sense);
  return geom2d_trimmed_curve(maoc);
}

geom2d_trimmed_curve geometry_creator::make_arc_of_circle(
    const circ2d &Circ, const vector2<Standard_Real> &P,
    const Standard_Real Alpha, const bool Sense) {
  GCE2d_MakeArcOfCircle maoc(cast_to_gp(Circ), cast_to_gp(P), Alpha, Sense);
  return geom2d_trimmed_curve(maoc);
}

geom2d_trimmed_curve geometry_creator::make_arc_of_circle(
    const circ2d &Circ, const vector2<Standard_Real> &P1,
    const vector2<Standard_Real> &P2, const bool Sense) {
  GCE2d_MakeArcOfCircle maoc(cast_to_gp(Circ), cast_to_gp(P1), cast_to_gp(P2),
                             Sense);
  return geom2d_trimmed_curve(maoc);
}

geom2d_trimmed_curve
geometry_creator::make_arc_of_circle(const vector2<Standard_Real> &P1,
                                     const vector2<Standard_Real> &P2,
                                     const vector2<Standard_Real> &P3) {
  GCE2d_MakeArcOfCircle maoc(cast_to_gp(P1), gp_Pnt2d(cast_to_gp(P2)),
                             cast_to_gp(P3));
  return geom2d_trimmed_curve(maoc);
}

geom2d_trimmed_curve
geometry_creator::make_arc_of_circle_vector(const vector2<Standard_Real> &P1,
                                            const vector2<Standard_Real> &V,
                                            const vector2<Standard_Real> &P2) {
  GCE2d_MakeArcOfCircle maoc(cast_to_gp(P1), gp_Vec2d(cast_to_gp(V)),
                             cast_to_gp(P2));
  return geom2d_trimmed_curve(maoc);
}

geom2d_trimmed_curve geometry_creator::make_arc_of_ellipse(
    const elips2d &Elips, const Standard_Real Alpha1,
    const Standard_Real Alpha2, const bool Sense) {
  GCE2d_MakeArcOfEllipse maoe(cast_to_gp(Elips), Alpha1, Alpha2, Sense);
  return geom2d_trimmed_curve(maoe);
}

geom2d_trimmed_curve geometry_creator::make_arc_of_ellipse(
    const elips2d &Elips, const vector2<Standard_Real> &P,
    const Standard_Real Alpha, const bool Sense) {
  GCE2d_MakeArcOfEllipse maoe(cast_to_gp(Elips), cast_to_gp(P), Alpha, Sense);
  return geom2d_trimmed_curve(maoe);
}

geom2d_trimmed_curve geometry_creator::make_arc_of_ellipse(
    const elips2d &Elips, const vector2<Standard_Real> &P1,
    const vector2<Standard_Real> &P2, const bool Sense) {
  GCE2d_MakeArcOfEllipse maoe(cast_to_gp(Elips), cast_to_gp(P1), cast_to_gp(P2),
                              Sense);
  return geom2d_trimmed_curve(maoe);
}

geom2d_trimmed_curve geometry_creator::make_arc_of_hyperbola(
    const hyperbola2d &Hypr, const Standard_Real Alpha1,
    const Standard_Real Alpha2, const bool Sense) {
  GCE2d_MakeArcOfHyperbola maoe(cast_to_gp(Hypr), Alpha1, Alpha2, Sense);
  return geom2d_trimmed_curve(maoe);
}

geom2d_trimmed_curve geometry_creator::make_arc_of_hyperbola(
    const hyperbola2d &Hypr, const vector2<Standard_Real> &P,
    const Standard_Real Alpha, const bool Sense) {
  GCE2d_MakeArcOfHyperbola maoe(cast_to_gp(Hypr), cast_to_gp(P), Alpha, Sense);
  return geom2d_trimmed_curve(maoe);
}

geom2d_trimmed_curve geometry_creator::make_arc_of_hyperbola(
    const hyperbola2d &Hypr, const vector2<Standard_Real> &P1,
    const vector2<Standard_Real> &P2, const bool Sense) {
  GCE2d_MakeArcOfHyperbola maoe(cast_to_gp(Hypr), cast_to_gp(P1),
                                cast_to_gp(P2), Sense);
  return geom2d_trimmed_curve(maoe);
}

geom2d_trimmed_curve geometry_creator::make_arc_of_parabola(
    const parabola2d &Parab, const Standard_Real Alpha1,
    const Standard_Real Alpha2, const bool Sense) {
  GCE2d_MakeArcOfParabola maoe(cast_to_gp(Parab), Alpha1, Alpha2, Sense);
  return geom2d_trimmed_curve(maoe);
}

geom2d_trimmed_curve geometry_creator::make_arc_of_parabola(
    const parabola2d &Parab, const vector2<Standard_Real> &P,
    const Standard_Real Alpha, const bool Sense) {
  GCE2d_MakeArcOfParabola maoe(cast_to_gp(Parab), cast_to_gp(P), Alpha, Sense);
  return geom2d_trimmed_curve(maoe);
}

geom2d_trimmed_curve geometry_creator::make_arc_of_parabola(
    const parabola2d &Parab, const vector2<Standard_Real> &P1,
    const vector2<Standard_Real> &P2, const bool Sense) {
  GCE2d_MakeArcOfParabola maoe(cast_to_gp(Parab), cast_to_gp(P1),
                               cast_to_gp(P2), Sense);
  return geom2d_trimmed_curve(maoe);
}

geom2d_circle geometry_creator::make_circle(const circ2d &C) {
  GCE2d_MakeCircle mc(cast_to_gp(C));
  return geom2d_circle(mc);
}

geom2d_circle geometry_creator::make_circle(const axis2d &A,
                                            const Standard_Real Radius,
                                            const bool Sense) {
  GCE2d_MakeCircle mc(cast_to_gp(A), Radius, Sense);
  return geom2d_circle(mc);
}

geom2d_circle geometry_creator::make_circle(const axis22d &A,
                                            const Standard_Real Radius) {
  GCE2d_MakeCircle mc(cast_to_gp(A), Radius);
  return geom2d_circle(mc);
}

geom2d_circle geometry_creator::make_circle(const circ2d &Circ,
                                            const Standard_Real Dist) {
  GCE2d_MakeCircle mc(cast_to_gp(Circ), Dist);
  return geom2d_circle(mc);
}

geom2d_circle
geometry_creator::make_circle(const circ2d &Circ,
                              const vector2<Standard_Real> &Point) {
  GCE2d_MakeCircle mc(cast_to_gp(Circ), cast_to_gp(Point));
  return geom2d_circle(mc);
}

geom2d_circle geometry_creator::make_circle(const vector2<Standard_Real> &P1,
                                            const vector2<Standard_Real> &P2,
                                            const vector2<Standard_Real> &P3) {
  GCE2d_MakeCircle mc(cast_to_gp(P1), cast_to_gp(P2), cast_to_gp(P3));
  return geom2d_circle(mc);
}

geom2d_circle geometry_creator::make_circle(const vector2<Standard_Real> &P,
                                            const Standard_Real Radius,
                                            const bool Sense) {
  GCE2d_MakeCircle mc(cast_to_gp(P), Radius, Sense);
  return geom2d_circle(mc);
}

geom2d_circle
geometry_creator::make_circle(const vector2<Standard_Real> &Center,
                              const vector2<Standard_Real> &Point,
                              const bool Sense) {
  GCE2d_MakeCircle mc(cast_to_gp(Center), cast_to_gp(Point), Sense);
  return geom2d_circle(mc);
}

geom2d_ellipse geometry_creator::make_ellipse(const elips2d &E) {
  GCE2d_MakeEllipse mc(cast_to_gp(E));
  return geom2d_ellipse(mc);
}

geom2d_ellipse geometry_creator::make_ellipse(const axis2d &MajorAxis,
                                              const Standard_Real MajorRadius,
                                              const Standard_Real MinorRadius,
                                              const bool Sense) {
  GCE2d_MakeEllipse mc(cast_to_gp(MajorAxis), MajorRadius, MinorRadius, Sense);
  return geom2d_ellipse(mc);
}

geom2d_ellipse geometry_creator::make_ellipse(const axis22d &Axis,
                                              const Standard_Real MajorRadius,
                                              const Standard_Real MinorRadius) {
  GCE2d_MakeEllipse mc(cast_to_gp(Axis), MajorRadius, MinorRadius);
  return geom2d_ellipse(mc);
}

geom2d_ellipse
geometry_creator::make_ellipse(const vector2<Standard_Real> &S1,
                               const vector2<Standard_Real> &S2,
                               const vector2<Standard_Real> &Center) {
  GCE2d_MakeEllipse mc(cast_to_gp(S1), cast_to_gp(S2), cast_to_gp(Center));
  return geom2d_ellipse(mc);
}

geom2d_hyperbola geometry_creator::make_hyperbola(const hyperbola2d &H) {
  GCE2d_MakeHyperbola mc(cast_to_gp(H));
  return geom2d_hyperbola(mc);
}

geom2d_hyperbola geometry_creator::make_hyperbola(
    const axis2d &MajorAxis, const Standard_Real MajorRadius,
    const Standard_Real MinorRadius, const bool Sense) {
  GCE2d_MakeHyperbola mc(cast_to_gp(MajorAxis), MajorRadius, MinorRadius,
                         Sense);
  return geom2d_hyperbola(mc);
}

geom2d_hyperbola
geometry_creator::make_hyperbola(const axis22d &Axis,
                                 const Standard_Real MajorRadius,
                                 const Standard_Real MinorRadius) {
  GCE2d_MakeHyperbola mc(cast_to_gp(Axis), MajorRadius, MinorRadius);
  return geom2d_hyperbola(mc);
}

geom2d_hyperbola
geometry_creator::make_hyperbola(const vector2<Standard_Real> &S1,
                                 const vector2<Standard_Real> &S2,
                                 const vector2<Standard_Real> &Center) {
  GCE2d_MakeHyperbola mc(cast_to_gp(S1), cast_to_gp(S2), cast_to_gp(Center));
  return geom2d_hyperbola(mc);
}

geom2d_line geometry_creator::make_line(const axis2d &A) {
  GCE2d_MakeLine ml(cast_to_gp(A));
  return geom2d_line(ml);
}

geom2d_line geometry_creator::make_line(const line2d &L) {
  GCE2d_MakeLine ml(cast_to_gp(L));
  return geom2d_line(ml);
}

geom2d_line geometry_creator::make_line(const vector2<Standard_Real> &P,
                                        const dir2d &V) {
  GCE2d_MakeLine ml(cast_to_gp(P), cast_to_gp(V));
  return geom2d_line(ml);
}

geom2d_line geometry_creator::make_line(const line2d &Lin,
                                        const vector2<Standard_Real> &Point) {
  GCE2d_MakeLine ml(cast_to_gp(Lin), cast_to_gp(Point));
  return geom2d_line(ml);
}

geom2d_line geometry_creator::make_line(const line2d &Lin,
                                        const Standard_Real Dist) {
  GCE2d_MakeLine ml(cast_to_gp(Lin), Dist);
  return geom2d_line(ml);
}

geom2d_line geometry_creator::make_line(const vector2<Standard_Real> &P1,
                                        const vector2<Standard_Real> &P2) {
  GCE2d_MakeLine ml(gp_Pnt2d(cast_to_gp(P1)), gp_Pnt2d(cast_to_gp(P2)));
  return geom2d_line(ml);
}

geom2d_parabola geometry_creator::make_parabola(const parabola2d &Prb) {
  GCE2d_MakeParabola ml(cast_to_gp(Prb));
  return geom2d_parabola(ml);
}

geom2d_parabola geometry_creator::make_parabola(const axis22d &Axis,
                                                const Standard_Real Focal) {
  GCE2d_MakeParabola ml(cast_to_gp(Axis), Focal);
  return geom2d_parabola(ml);
}

geom2d_parabola geometry_creator::make_parabola(const axis2d &MirrorAxis,
                                                const Standard_Real Focal,
                                                const bool Sense) {
  GCE2d_MakeParabola ml(cast_to_gp(MirrorAxis), Focal, Sense);
  return geom2d_parabola(ml);
}

geom2d_parabola geometry_creator::make_parabola(const axis2d &D,
                                                const vector2<Standard_Real> &F,
                                                const bool Sense) {
  GCE2d_MakeParabola ml(cast_to_gp(D), cast_to_gp(F), Sense);
  return geom2d_parabola(ml);
}

geom2d_parabola
geometry_creator::make_parabola(const vector2<Standard_Real> &S1,
                                const vector2<Standard_Real> &O) {
  GCE2d_MakeParabola ml(cast_to_gp(S1), cast_to_gp(O));
  return geom2d_parabola(ml);
}

geom2d_trimmed_curve
geometry_creator::make_segment(const vector2<Standard_Real> &P1,
                               const vector2<Standard_Real> &P2) {
  GCE2d_MakeSegment ms(gp_Pnt2d(cast_to_gp(P1)), gp_Pnt2d(cast_to_gp(P2)));
  return geom2d_trimmed_curve(ms);
}

geom2d_trimmed_curve
geometry_creator::make_segment(const vector2<Standard_Real> &P1, const dir2d &V,
                               const vector2<Standard_Real> &P2) {
  GCE2d_MakeSegment ms(cast_to_gp(P1), cast_to_gp(V), cast_to_gp(P2));
  return geom2d_trimmed_curve(ms);
}

geom2d_trimmed_curve geometry_creator::make_segment(const line2d &Line,
                                                    const Standard_Real U1,
                                                    const Standard_Real U2) {
  GCE2d_MakeSegment ms(cast_to_gp(Line), U1, U2);
  return geom2d_trimmed_curve(ms);
}

geom2d_trimmed_curve
geometry_creator::make_segment(const line2d &Line,
                               const vector2<Standard_Real> &Point,
                               const Standard_Real Ulast) {
  GCE2d_MakeSegment ms(cast_to_gp(Line), cast_to_gp(Point), Ulast);
  return geom2d_trimmed_curve(ms);
}

geom2d_trimmed_curve
geometry_creator::make_segment(const line2d &Line,
                               const vector2<Standard_Real> &P1,
                               const vector2<Standard_Real> &P2) {
  GCE2d_MakeSegment ms(cast_to_gp(Line), cast_to_gp(P1), cast_to_gp(P2));
  return geom2d_trimmed_curve(ms);
}

geom2d_transformation
geometry_creator::make_mirror(const vector2<Standard_Real> &Point) {
  GCE2d_MakeMirror mr(cast_to_gp(Point));
  return geom2d_transformation(mr);
}

geom2d_transformation geometry_creator::make_mirror(const axis2d &Axis) {
  GCE2d_MakeMirror mr(cast_to_gp(Axis));
  return geom2d_transformation(mr);
}

geom2d_transformation geometry_creator::make_mirror(const line2d &Line) {
  GCE2d_MakeMirror mr(cast_to_gp(Line));
  return geom2d_transformation(mr);
}

geom2d_transformation
geometry_creator::make_mirror(const vector2<Standard_Real> &Point,
                              const dir2d &Direc) {
  GCE2d_MakeMirror mr(cast_to_gp(Point), cast_to_gp(Direc));
  return geom2d_transformation(mr);
}

geom2d_transformation
geometry_creator::make_rotation(const vector2<Standard_Real> &Point,
                                const Standard_Real Angle) {
  GCE2d_MakeRotation mr(cast_to_gp(Point), Angle);
  return geom2d_transformation(mr);
}

geom2d_transformation
geometry_creator::make_scale(const vector2<Standard_Real> &Point,
                             const Standard_Real Scale) {
  GCE2d_MakeScale ms(cast_to_gp(Point), Scale);
  return geom2d_transformation(ms);
}

geom2d_transformation
geometry_creator::make_translation(const vector2<Standard_Real> &Vect) {
  GCE2d_MakeTranslation mt(cast_to_gp(Vect));
  return geom2d_transformation(mt);
}

geom2d_transformation
geometry_creator::make_translation(const vector2<Standard_Real> &Point1,
                                   const vector2<Standard_Real> &Point2) {
  GCE2d_MakeTranslation mt(cast_to_gp(Point1), cast_to_gp(Point2));
  return geom2d_transformation(mt);
}

geom_bspline_curve geometry_creator::convert_approx_curve(
    const geom_curve &Curve, const Standard_Real Tol3d,
    const GeomAbs_Shape Order, const Standard_Integer MaxSegments,
    const Standard_Integer MaxDegree) {
  GeomConvert_ApproxCurve cac(Curve, Tol3d, Order, MaxSegments, MaxDegree);
  return geom_bspline_curve(cac.Curve());
}

geom_bspline_surface geometry_creator::convert_approx_surface(
    const geom_surface &Surf, const Standard_Real Tol3d,
    const GeomAbs_Shape UContinuity, const GeomAbs_Shape VContinuity,
    const Standard_Integer MaxDegU, const Standard_Integer MaxDegV,
    const Standard_Integer MaxSegments, const Standard_Integer PrecisCode) {
  GeomConvert_ApproxSurface cac(Surf, Tol3d, UContinuity, VContinuity, MaxDegU,
                                MaxDegV, MaxSegments, PrecisCode);
  return geom_bspline_surface(cac.Surface());
}

} // namespace topo
} // namespace flywave
