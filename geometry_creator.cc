#include "geometry_creator.hh"

namespace flywave {
namespace topo {

Handle(Geom_TrimmedCurve) geometry_creator::make_arc_of_circle(
    const gp_Circ &Circ, const Standard_Real Alpha1, const Standard_Real Alpha2,
    const bool Sense) {
  GC_MakeArcOfCircle maoc(Circ, Alpha1, Alpha2, Sense);
  return Handle(Geom_TrimmedCurve)(maoc);
}

Handle(Geom_TrimmedCurve) geometry_creator::make_arc_of_circle(
    const gp_Circ &Circ, const gp_Pnt &P, const Standard_Real Alpha,
    const bool Sense) {
  GC_MakeArcOfCircle maoc(Circ, P, Alpha, Sense);
  return Handle(Geom_TrimmedCurve)(maoc);
}

Handle(Geom_TrimmedCurve) geometry_creator::make_arc_of_circle(
    const gp_Circ &Circ, const gp_Pnt &P1, const gp_Pnt &P2, const bool Sense) {
  GC_MakeArcOfCircle maoc(Circ, P1, P2, Sense);
  return Handle(Geom_TrimmedCurve)(maoc);
}

Handle(Geom_TrimmedCurve) geometry_creator::make_arc_of_circle(
    const gp_Pnt &P1, const gp_Pnt &P2, const gp_Pnt &P3) {
  GC_MakeArcOfCircle maoc(P1, P2, P3);
  return Handle(Geom_TrimmedCurve)(maoc);
}

Handle(Geom_TrimmedCurve) geometry_creator::make_arc_of_circle_vector(
    const gp_Pnt &P1, const gp_Vec &V, const gp_Pnt &P2) {
  GC_MakeArcOfCircle maoc(P1, gp_Vec(V), P2);
  return Handle(Geom_TrimmedCurve)(maoc);
}

Handle(Geom_TrimmedCurve) geometry_creator::make_arc_of_ellipse(
    const gp_Elips &Elips, const Standard_Real Alpha1,
    const Standard_Real Alpha2, const bool Sense) {
  GC_MakeArcOfEllipse maoe(Elips, Alpha1, Alpha2, Sense);
  return Handle(Geom_TrimmedCurve)(maoe);
}

Handle(Geom_TrimmedCurve) geometry_creator::make_arc_of_ellipse(
    const gp_Elips &Elips, const gp_Pnt &P, const Standard_Real Alpha,
    const bool Sense) {
  GC_MakeArcOfEllipse maoe(Elips, P, Alpha, Sense);
  return Handle(Geom_TrimmedCurve)(maoe);
}

Handle(Geom_TrimmedCurve) geometry_creator::make_arc_of_ellipse(
    const gp_Elips &Elips, const gp_Pnt &P1, const gp_Pnt &P2,
    const bool Sense) {
  GC_MakeArcOfEllipse maoe(Elips, P1, P2, Sense);
  return Handle(Geom_TrimmedCurve)(maoe);
}

Handle(Geom_TrimmedCurve) geometry_creator::make_arc_of_hyperbola(
    const gp_Hypr &Hypr, const Standard_Real Alpha1, const Standard_Real Alpha2,
    const bool Sense) {
  GC_MakeArcOfHyperbola maoe(Hypr, Alpha1, Alpha2, Sense);
  return Handle(Geom_TrimmedCurve)(maoe);
}

Handle(Geom_TrimmedCurve) geometry_creator::make_arc_of_hyperbola(
    const gp_Hypr &Hypr, const gp_Pnt &P, const Standard_Real Alpha,
    const bool Sense) {
  GC_MakeArcOfHyperbola maoe(Hypr, P, Alpha, Sense);
  return Handle(Geom_TrimmedCurve)(maoe);
}

Handle(Geom_TrimmedCurve) geometry_creator::make_arc_of_hyperbola(
    const gp_Hypr &Hypr, const gp_Pnt &P1, const gp_Pnt &P2, const bool Sense) {
  GC_MakeArcOfHyperbola maoe(Hypr, P1, P2, Sense);
  return Handle(Geom_TrimmedCurve)(maoe);
}

Handle(Geom_TrimmedCurve) geometry_creator::make_arc_of_parabola(
    const gp_Parab &Parab, const Standard_Real Alpha1,
    const Standard_Real Alpha2, const bool Sense) {
  GC_MakeArcOfParabola maoe(Parab, Alpha1, Alpha2, Sense);
  return Handle(Geom_TrimmedCurve)(maoe);
}

Handle(Geom_TrimmedCurve) geometry_creator::make_arc_of_parabola(
    const gp_Parab &Parab, const gp_Pnt &P, const Standard_Real Alpha,
    const bool Sense) {
  GC_MakeArcOfParabola maoe(Parab, P, Alpha, Sense);
  return Handle(Geom_TrimmedCurve)(maoe);
}

Handle(Geom_TrimmedCurve) geometry_creator::make_arc_of_parabola(
    const gp_Parab &Parab, const gp_Pnt &P1, const gp_Pnt &P2,
    const bool Sense) {
  GC_MakeArcOfParabola maoe(Parab, P1, P2, Sense);
  return Handle(Geom_TrimmedCurve)(maoe);
}

Handle(Geom_Circle) geometry_creator::make_circle(const gp_Circ &C) {
  GC_MakeCircle mc(C);
  return Handle(Geom_Circle)(mc);
}

Handle(Geom_Circle) geometry_creator::make_circle(const gp_Ax2 &A2,
                                                  const Standard_Real Radius) {
  GC_MakeCircle mc(A2, Radius);
  return Handle(Geom_Circle)(mc);
}

Handle(Geom_Circle) geometry_creator::make_circle(const gp_Circ &Circ,
                                                  const Standard_Real Dist) {
  GC_MakeCircle mc(Circ, Dist);
  return Handle(Geom_Circle)(mc);
}

Handle(Geom_Circle) geometry_creator::make_circle(const gp_Circ &Circ,
                                                  const gp_Pnt &Point) {
  GC_MakeCircle mc(Circ, Point);
  return Handle(Geom_Circle)(mc);
}

Handle(Geom_Circle) geometry_creator::make_circle(const gp_Pnt &P1,
                                                  const gp_Pnt &P2,
                                                  const gp_Pnt &P3) {
  GC_MakeCircle mc(P1, P2, P3);
  return Handle(Geom_Circle)(mc);
}

Handle(Geom_Circle) geometry_creator::make_circle(const gp_Pnt &Center,
                                                  const gp_Dir &Norm,
                                                  const Standard_Real Radius) {
  GC_MakeCircle mc(Center, Norm, Radius);
  return Handle(Geom_Circle)(mc);
}

Handle(Geom_Circle) geometry_creator::make_circle(const gp_Pnt &Center,
                                                  const gp_Pnt &PtAxis,
                                                  const Standard_Real Radius) {
  GC_MakeCircle mc(Center, PtAxis, Radius);
  return Handle(Geom_Circle)(mc);
}

Handle(Geom_Circle) geometry_creator::make_circle(const gp_Ax1 &Axis,
                                                  const Standard_Real Radius) {
  GC_MakeCircle mc(Axis, Radius);
  return Handle(Geom_Circle)(mc);
}

Handle(Geom_Ellipse) geometry_creator::make_ellipse(const gp_Elips &E) {
  GC_MakeEllipse mc(E);
  return Handle(Geom_Ellipse)(mc);
}

Handle(Geom_Ellipse) geometry_creator::make_ellipse(
    const gp_Ax2 &A2, const Standard_Real MajorRadius,
    const Standard_Real MinorRadius) {
  GC_MakeEllipse mc(A2, MajorRadius, MinorRadius);
  return Handle(Geom_Ellipse)(mc);
}

Handle(Geom_Ellipse) geometry_creator::make_ellipse(const gp_Pnt &S1,
                                                    const gp_Pnt &S2,
                                                    const gp_Pnt &Center) {
  GC_MakeEllipse mc(S1, S2, Center);
  return Handle(Geom_Ellipse)(mc);
}

Handle(Geom_Hyperbola) geometry_creator::make_hyperbola(const gp_Hypr &H) {
  GC_MakeHyperbola mc(H);
  return Handle(Geom_Hyperbola)(mc);
}

Handle(Geom_Hyperbola) geometry_creator::make_hyperbola(
    const gp_Ax2 &A2, const Standard_Real MajorRadius,
    const Standard_Real MinorRadius) {
  GC_MakeHyperbola mc(A2, MajorRadius, MinorRadius);
  return Handle(Geom_Hyperbola)(mc);
}

Handle(Geom_Hyperbola) geometry_creator::make_hyperbola(const gp_Pnt &S1,
                                                        const gp_Pnt &S2,
                                                        const gp_Pnt &Center) {
  GC_MakeHyperbola mc(S1, S2, Center);
  return Handle(Geom_Hyperbola)(mc);
}

Handle(Geom_ConicalSurface) geometry_creator::make_conical_surface(
    const gp_Ax2 &A2, const Standard_Real Ang, const Standard_Real Radius) {
  GC_MakeConicalSurface mcs(A2, Ang, Radius);
  return Handle(Geom_ConicalSurface)(mcs);
}

Handle(Geom_ConicalSurface)
    geometry_creator::make_conical_surface(const gp_Cone &C) {
  GC_MakeConicalSurface mcs(C);
  return Handle(Geom_ConicalSurface)(mcs);
}

Handle(Geom_ConicalSurface) geometry_creator::make_conical_surface(
    const gp_Pnt &P1, const gp_Pnt &P2, const gp_Pnt &P3, const gp_Pnt &P4) {
  GC_MakeConicalSurface mcs(P1, P2, P3, P4);
  return Handle(Geom_ConicalSurface)(mcs);
}

Handle(Geom_ConicalSurface) geometry_creator::make_conical_surface(
    const gp_Pnt &P1, const gp_Pnt &P2, const Standard_Real R1,
    const Standard_Real R2) {
  GC_MakeConicalSurface mcs(P1, P2, R1, R2);
  return Handle(Geom_ConicalSurface)(mcs);
}

Handle(Geom_CylindricalSurface) geometry_creator::make_cylindrical_surface(
    const gp_Ax2 &A2, const Standard_Real Radius) {
  GC_MakeCylindricalSurface mcs(A2, Radius);
  return Handle(Geom_CylindricalSurface)(mcs);
}

Handle(Geom_CylindricalSurface)
    geometry_creator::make_cylindrical_surface(const gp_Cylinder &C) {
  GC_MakeCylindricalSurface mcs(C);
  return Handle(Geom_CylindricalSurface)(mcs);
}

Handle(Geom_CylindricalSurface) geometry_creator::make_cylindrical_surface(
    const gp_Cylinder &Cyl, const gp_Pnt &Point) {
  GC_MakeCylindricalSurface mcs(Cyl, Point);
  return Handle(Geom_CylindricalSurface)(mcs);
}

Handle(Geom_CylindricalSurface) geometry_creator::make_cylindrical_surface(
    const gp_Cylinder &Cyl, const Standard_Real Dist) {
  GC_MakeCylindricalSurface mcs(Cyl, Dist);
  return Handle(Geom_CylindricalSurface)(mcs);
}

Handle(Geom_CylindricalSurface) geometry_creator::make_cylindrical_surface(
    const gp_Pnt &P1, const gp_Pnt &P2, const gp_Pnt &P3) {
  GC_MakeCylindricalSurface mcs(P1, P2, P3);
  return Handle(Geom_CylindricalSurface)(mcs);
}

Handle(Geom_CylindricalSurface) geometry_creator::make_cylindrical_surface(
    const gp_Ax1 &Axis, const Standard_Real Radius) {
  GC_MakeCylindricalSurface mcs(Axis, Radius);
  return Handle(Geom_CylindricalSurface)(mcs);
}

Handle(Geom_CylindricalSurface)
    geometry_creator::make_cylindrical_surface(const gp_Circ &Circ) {
  GC_MakeCylindricalSurface mcs(Circ);
  return Handle(Geom_CylindricalSurface)(mcs);
}

Handle(Geom_Line) geometry_creator::make_line(const gp_Ax1 &A1) {
  GC_MakeLine ml(A1);
  return Handle(Geom_Line)(ml);
}

Handle(Geom_Line) geometry_creator::make_line(const gp_Lin &L) {
  GC_MakeLine ml(L);
  return Handle(Geom_Line)(ml);
}

Handle(Geom_Line) geometry_creator::make_line(const gp_Pnt &P,
                                              const gp_Dir &V) {
  GC_MakeLine ml(P, V);
  return Handle(Geom_Line)(ml);
}

Handle(Geom_Line) geometry_creator::make_line(const gp_Lin &Lin,
                                              const gp_Pnt &Point) {
  GC_MakeLine ml(Lin, Point);
  return Handle(Geom_Line)(ml);
}

Handle(Geom_Line) geometry_creator::make_line(const gp_Pnt &P1,
                                              const gp_Pnt &P2) {
  GC_MakeLine ml(P1, P2);
  return Handle(Geom_Line)(ml);
}

Handle(Geom_Transformation) geometry_creator::make_mirror(const gp_Pnt &Point) {
  GC_MakeMirror ml(Point);
  return Handle(Geom_Transformation)(ml);
}

Handle(Geom_Transformation) geometry_creator::make_mirror(const gp_Ax1 &Axis) {
  GC_MakeMirror ml(Axis);
  return Handle(Geom_Transformation)(ml);
}

Handle(Geom_Transformation) geometry_creator::make_mirror(const gp_Lin &Line) {
  GC_MakeMirror ml(Line);
  return Handle(Geom_Transformation)(ml);
}

Handle(Geom_Transformation) geometry_creator::make_mirror(const gp_Pnt &Point,
                                                          const gp_Dir &Direc) {
  GC_MakeMirror ml(Point, Direc);
  return Handle(Geom_Transformation)(ml);
}

Handle(Geom_Transformation) geometry_creator::make_mirror(const gp_Pln &Plane) {
  GC_MakeMirror ml(Plane);
  return Handle(Geom_Transformation)(ml);
}

Handle(Geom_Transformation) geometry_creator::make_mirror(const gp_Ax2 &Plane) {
  GC_MakeMirror ml(Plane);
  return Handle(Geom_Transformation)(ml);
}

Handle(Geom_Transformation) geometry_creator::make_rotation(
    const gp_Lin &Line, const Standard_Real Angle) {
  GC_MakeRotation mr(Line, Angle);
  return Handle(Geom_Transformation)(mr);
}

Handle(Geom_Transformation) geometry_creator::make_rotation(
    const gp_Ax1 &Axis, const Standard_Real Angle) {
  GC_MakeRotation mr(Axis, Angle);
  return Handle(Geom_Transformation)(mr);
}

Handle(Geom_Transformation) geometry_creator::make_rotation(
    const gp_Pnt &Point, const gp_Dir &Direc, const Standard_Real Angle) {
  GC_MakeRotation mr(Point, Direc, Angle);
  return Handle(Geom_Transformation)(mr);
}

Handle(Geom_Transformation)
    geometry_creator::make_translation(const gp_Vec &Vect) {
  GC_MakeTranslation mr(Vect);
  return Handle(Geom_Transformation)(mr);
}

Handle(Geom_Transformation) geometry_creator::make_translation(
    const gp_Pnt &Point1, const gp_Pnt &Point2) {
  GC_MakeTranslation mr(Point1, Point2);
  return Handle(Geom_Transformation)(mr);
}

Handle(Geom_Transformation) geometry_creator::make_scale(
    const gp_Pnt &Point, const Standard_Real Scale) {
  GC_MakeScale mr(Point, Scale);
  return Handle(Geom_Transformation)(mr);
}

Handle(Geom_Plane) geometry_creator::make_plane(const gp_Pln &Pl) {
  GC_MakePlane mr(Pl);
  return Handle(Geom_Plane)(mr);
}

Handle(Geom_Plane) geometry_creator::make_plane(const gp_Pnt &P,
                                                const gp_Dir &V) {
  GC_MakePlane mr(P, V);
  return Handle(Geom_Plane)(mr);
}

Handle(Geom_Plane) geometry_creator::make_plane(const Standard_Real A,
                                                const Standard_Real B,
                                                const Standard_Real C,
                                                const Standard_Real D) {
  GC_MakePlane mr(A, B, C, D);
  return Handle(Geom_Plane)(mr);
}

Handle(Geom_Plane) geometry_creator::make_plane(const gp_Pln &Pln,
                                                const gp_Pnt &Point) {
  GC_MakePlane mr(Pln, Point);
  return Handle(Geom_Plane)(mr);
}

Handle(Geom_Plane) geometry_creator::make_plane(const gp_Pln &Pln,
                                                const Standard_Real Dist) {
  GC_MakePlane mr(Pln, Dist);
  return Handle(Geom_Plane)(mr);
}

Handle(Geom_Plane) geometry_creator::make_plane(const gp_Pnt &P1,
                                                const gp_Pnt &P2,
                                                const gp_Pnt &P3) {
  GC_MakePlane mr(P1, P2, P3);
  return Handle(Geom_Plane)(mr);
}

Handle(Geom_Plane) geometry_creator::make_plane(const gp_Ax1 &Axis) {
  GC_MakePlane mr(Axis);
  return Handle(Geom_Plane)(mr);
}

Handle(Geom_TrimmedCurve) geometry_creator::make_segment(const gp_Pnt &P1,
                                                         const gp_Pnt &P2) {
  GC_MakeSegment ms(P1, P2);
  return Handle(Geom_TrimmedCurve)(ms);
}

Handle(Geom_TrimmedCurve) geometry_creator::make_segment(
    const gp_Lin &Line, const Standard_Real U1, const Standard_Real U2) {
  GC_MakeSegment ms(Line, U1, U2);
  return Handle(Geom_TrimmedCurve)(ms);
}

Handle(Geom_TrimmedCurve) geometry_creator::make_segment(
    const gp_Lin &Line, const gp_Pnt &Point, const Standard_Real Ulast) {
  GC_MakeSegment ms(Line, Point, Ulast);
  return Handle(Geom_TrimmedCurve)(ms);
}

Handle(Geom_TrimmedCurve) geometry_creator::make_segment(const gp_Lin &Line,
                                                         const gp_Pnt &P1,
                                                         const gp_Pnt &P2) {
  GC_MakeSegment ms(Line, P1, P2);
  return Handle(Geom_TrimmedCurve)(ms);
}

Handle(Geom_RectangularTrimmedSurface) geometry_creator::make_trimmed_cone(
    const gp_Pnt &P1, const gp_Pnt &P2, const gp_Pnt &P3, const gp_Pnt &P4) {
  GC_MakeTrimmedCone mtc(P1, P2, P3, P4);
  return Handle(Geom_RectangularTrimmedSurface)(mtc);
}

Handle(Geom_RectangularTrimmedSurface) geometry_creator::make_trimmed_cone(
    const gp_Pnt &P1, const gp_Pnt &P2, const Standard_Real R1,
    const Standard_Real R2) {
  GC_MakeTrimmedCone mtc(P1, P2, R1, R2);
  return Handle(Geom_RectangularTrimmedSurface)(mtc);
}

Handle(Geom_RectangularTrimmedSurface) geometry_creator::make_trimmed_cylinder(
    const gp_Pnt &P1, const gp_Pnt &P2, const gp_Pnt &P3) {
  GC_MakeTrimmedCylinder mtc(P1, P2, P3);
  return Handle(Geom_RectangularTrimmedSurface)(mtc);
}

Handle(Geom_RectangularTrimmedSurface) geometry_creator::make_trimmed_cylinder(
    const gp_Circ &Circ, const Standard_Real Height) {
  GC_MakeTrimmedCylinder mtc(Circ, Height);
  return Handle(Geom_RectangularTrimmedSurface)(mtc);
}

Handle(Geom_RectangularTrimmedSurface) geometry_creator::make_trimmed_cylinder(
    const gp_Ax1 &A1, const Standard_Real Radius, const Standard_Real Height) {
  GC_MakeTrimmedCylinder mtc(A1, Radius, Height);
  return Handle(Geom_RectangularTrimmedSurface)(mtc);
}

Handle(Geom2d_TrimmedCurve) geometry_creator::make_arc_of_circle(
    const gp_Circ2d &Circ, const Standard_Real Alpha1,
    const Standard_Real Alpha2, const bool Sense) {
  GCE2d_MakeArcOfCircle maoc(Circ, Alpha1, Alpha2, Sense);
  return Handle(Geom2d_TrimmedCurve)(maoc);
}

Handle(Geom2d_TrimmedCurve) geometry_creator::make_arc_of_circle(
    const gp_Circ2d &Circ, const gp_Pnt2d &P, const Standard_Real Alpha,
    const bool Sense) {
  GCE2d_MakeArcOfCircle maoc(Circ, P, Alpha, Sense);
  return Handle(Geom2d_TrimmedCurve)(maoc);
}

Handle(Geom2d_TrimmedCurve) geometry_creator::make_arc_of_circle(
    const gp_Circ2d &Circ, const gp_Pnt2d &P1, const gp_Pnt2d &P2,
    const bool Sense) {
  GCE2d_MakeArcOfCircle maoc(Circ, P1, P2, Sense);
  return Handle(Geom2d_TrimmedCurve)(maoc);
}

Handle(Geom2d_TrimmedCurve) geometry_creator::make_arc_of_circle(
    const gp_Pnt2d &P1, const gp_Pnt2d &P2, const gp_Pnt2d &P3) {
  GCE2d_MakeArcOfCircle maoc(P1, P2, P3);
  return Handle(Geom2d_TrimmedCurve)(maoc);
}

Handle(Geom2d_TrimmedCurve) geometry_creator::make_arc_of_circle_vector(
    const gp_Pnt2d &P1, const gp_Vec2d &V, const gp_Pnt2d &P2) {
  GCE2d_MakeArcOfCircle maoc(P1, V, P2);
  return Handle(Geom2d_TrimmedCurve)(maoc);
}

Handle(Geom2d_TrimmedCurve) geometry_creator::make_arc_of_ellipse(
    const gp_Elips2d &Elips, const Standard_Real Alpha1,
    const Standard_Real Alpha2, const bool Sense) {
  GCE2d_MakeArcOfEllipse maoe(Elips, Alpha1, Alpha2, Sense);
  return Handle(Geom2d_TrimmedCurve)(maoe);
}

Handle(Geom2d_TrimmedCurve) geometry_creator::make_arc_of_ellipse(
    const gp_Elips2d &Elips, const gp_Pnt2d &P, const Standard_Real Alpha,
    const bool Sense) {
  GCE2d_MakeArcOfEllipse maoe(Elips, P, Alpha, Sense);
  return Handle(Geom2d_TrimmedCurve)(maoe);
}

Handle(Geom2d_TrimmedCurve) geometry_creator::make_arc_of_ellipse(
    const gp_Elips2d &Elips, const gp_Pnt2d &P1, const gp_Pnt2d &P2,
    const bool Sense) {
  GCE2d_MakeArcOfEllipse maoe(Elips, P1, P2, Sense);
  return Handle(Geom2d_TrimmedCurve)(maoe);
}

Handle(Geom2d_TrimmedCurve) geometry_creator::make_arc_of_hyperbola(
    const gp_Hypr2d &Hypr, const Standard_Real Alpha1,
    const Standard_Real Alpha2, const bool Sense) {
  GCE2d_MakeArcOfHyperbola maoe(Hypr, Alpha1, Alpha2, Sense);
  return Handle(Geom2d_TrimmedCurve)(maoe);
}

Handle(Geom2d_TrimmedCurve) geometry_creator::make_arc_of_hyperbola(
    const gp_Hypr2d &Hypr, const gp_Pnt2d &P, const Standard_Real Alpha,
    const bool Sense) {
  GCE2d_MakeArcOfHyperbola maoe(Hypr, P, Alpha, Sense);
  return Handle(Geom2d_TrimmedCurve)(maoe);
}

Handle(Geom2d_TrimmedCurve) geometry_creator::make_arc_of_hyperbola(
    const gp_Hypr2d &Hypr, const gp_Pnt2d &P1, const gp_Pnt2d &P2,
    const bool Sense) {
  GCE2d_MakeArcOfHyperbola maoe(Hypr, P1, P2, Sense);
  return Handle(Geom2d_TrimmedCurve)(maoe);
}

Handle(Geom2d_TrimmedCurve) geometry_creator::make_arc_of_parabola(
    const gp_Parab2d &Parab, const Standard_Real Alpha1,
    const Standard_Real Alpha2, const bool Sense) {
  GCE2d_MakeArcOfParabola maoe(Parab, Alpha1, Alpha2, Sense);
  return Handle(Geom2d_TrimmedCurve)(maoe);
}

Handle(Geom2d_TrimmedCurve) geometry_creator::make_arc_of_parabola(
    const gp_Parab2d &Parab, const gp_Pnt2d &P, const Standard_Real Alpha,
    const bool Sense) {
  GCE2d_MakeArcOfParabola maoe(Parab, P, Alpha, Sense);
  return Handle(Geom2d_TrimmedCurve)(maoe);
}

Handle(Geom2d_TrimmedCurve) geometry_creator::make_arc_of_parabola(
    const gp_Parab2d &Parab, const gp_Pnt2d &P1, const gp_Pnt2d &P2,
    const bool Sense) {
  GCE2d_MakeArcOfParabola maoe(Parab, P1, P2, Sense);
  return Handle(Geom2d_TrimmedCurve)(maoe);
}

Handle(Geom2d_Circle) geometry_creator::make_circle(const gp_Circ2d &C) {
  GCE2d_MakeCircle mc(C);
  return Handle(Geom2d_Circle)(mc);
}

Handle(Geom2d_Circle) geometry_creator::make_circle(const gp_Ax2d &A,
                                                    const Standard_Real Radius,
                                                    const bool Sense) {
  GCE2d_MakeCircle mc(A, Radius, Sense);
  return Handle(Geom2d_Circle)(mc);
}

Handle(Geom2d_Circle) geometry_creator::make_circle(
    const gp_Ax22d &A, const Standard_Real Radius) {
  GCE2d_MakeCircle mc(A, Radius);
  return Handle(Geom2d_Circle)(mc);
}

Handle(Geom2d_Circle) geometry_creator::make_circle(const gp_Circ2d &Circ,
                                                    const Standard_Real Dist) {
  GCE2d_MakeCircle mc(Circ, Dist);
  return Handle(Geom2d_Circle)(mc);
}

Handle(Geom2d_Circle) geometry_creator::make_circle(const gp_Circ2d &Circ,
                                                    const gp_Pnt2d &Point) {
  GCE2d_MakeCircle mc(Circ, Point);
  return Handle(Geom2d_Circle)(mc);
}

Handle(Geom2d_Circle) geometry_creator::make_circle(const gp_Pnt2d &P1,
                                                    const gp_Pnt2d &P2,
                                                    const gp_Pnt2d &P3) {
  GCE2d_MakeCircle mc(P1, P2, P3);
  return Handle(Geom2d_Circle)(mc);
}

Handle(Geom2d_Circle) geometry_creator::make_circle(const gp_Pnt2d &P,
                                                    const Standard_Real Radius,
                                                    const bool Sense) {
  GCE2d_MakeCircle mc(P, Radius, Sense);
  return Handle(Geom2d_Circle)(mc);
}

Handle(Geom2d_Circle) geometry_creator::make_circle(const gp_Pnt2d &Center,
                                                    const gp_Pnt2d &Point,
                                                    const bool Sense) {
  GCE2d_MakeCircle mc(Center, Point, Sense);
  return Handle(Geom2d_Circle)(mc);
}

Handle(Geom2d_Ellipse) geometry_creator::make_ellipse(const gp_Elips2d &E) {
  GCE2d_MakeEllipse mc(E);
  return Handle(Geom2d_Ellipse)(mc);
}

Handle(Geom2d_Ellipse) geometry_creator::make_ellipse(
    const gp_Ax2d &MajorAxis, const Standard_Real MajorRadius,
    const Standard_Real MinorRadius, const bool Sense) {
  GCE2d_MakeEllipse mc(MajorAxis, MajorRadius, MinorRadius, Sense);
  return Handle(Geom2d_Ellipse)(mc);
}

Handle(Geom2d_Ellipse) geometry_creator::make_ellipse(
    const gp_Ax22d &Axis, const Standard_Real MajorRadius,
    const Standard_Real MinorRadius) {
  GCE2d_MakeEllipse mc(Axis, MajorRadius, MinorRadius);
  return Handle(Geom2d_Ellipse)(mc);
}

Handle(Geom2d_Ellipse) geometry_creator::make_ellipse(const gp_Pnt2d &S1,
                                                      const gp_Pnt2d &S2,
                                                      const gp_Pnt2d &Center) {
  GCE2d_MakeEllipse mc(S1, S2, Center);
  return Handle(Geom2d_Ellipse)(mc);
}

Handle(Geom2d_Hyperbola) geometry_creator::make_hyperbola(const gp_Hypr2d &H) {
  GCE2d_MakeHyperbola mc(H);
  return Handle(Geom2d_Hyperbola)(mc);
}

Handle(Geom2d_Hyperbola) geometry_creator::make_hyperbola(
    const gp_Ax2d &MajorAxis, const Standard_Real MajorRadius,
    const Standard_Real MinorRadius, const bool Sense) {
  GCE2d_MakeHyperbola mc(MajorAxis, MajorRadius, MinorRadius, Sense);
  return Handle(Geom2d_Hyperbola)(mc);
}

Handle(Geom2d_Hyperbola) geometry_creator::make_hyperbola(
    const gp_Ax22d &Axis, const Standard_Real MajorRadius,
    const Standard_Real MinorRadius) {
  GCE2d_MakeHyperbola mc(Axis, MajorRadius, MinorRadius);
  return Handle(Geom2d_Hyperbola)(mc);
}

Handle(Geom2d_Hyperbola) geometry_creator::make_hyperbola(
    const gp_Pnt2d &S1, const gp_Pnt2d &S2, const gp_Pnt2d &Center) {
  GCE2d_MakeHyperbola mc(S1, S2, Center);
  return Handle(Geom2d_Hyperbola)(mc);
}

Handle(Geom2d_Line) geometry_creator::make_line(const gp_Ax2d &A) {
  GCE2d_MakeLine ml(A);
  return Handle(Geom2d_Line)(ml);
}

Handle(Geom2d_Line) geometry_creator::make_line(const gp_Lin2d &L) {
  GCE2d_MakeLine ml(L);
  return Handle(Geom2d_Line)(ml);
}

Handle(Geom2d_Line) geometry_creator::make_line(const gp_Pnt2d &P,
                                                const gp_Dir2d &V) {
  GCE2d_MakeLine ml(P, V);
  return Handle(Geom2d_Line)(ml);
}

Handle(Geom2d_Line) geometry_creator::make_line(const gp_Lin2d &Lin,
                                                const gp_Pnt2d &Point) {
  GCE2d_MakeLine ml(Lin, Point);
  return Handle(Geom2d_Line)(ml);
}

Handle(Geom2d_Line) geometry_creator::make_line(const gp_Lin2d &Lin,
                                                const Standard_Real Dist) {
  GCE2d_MakeLine ml(Lin, Dist);
  return Handle(Geom2d_Line)(ml);
}

Handle(Geom2d_Line) geometry_creator::make_line(const gp_Pnt2d &P1,
                                                const gp_Pnt2d &P2) {
  GCE2d_MakeLine ml(P1, P2);
  return Handle(Geom2d_Line)(ml);
}

Handle(Geom2d_Parabola) geometry_creator::make_parabola(const gp_Parab2d &Prb) {
  GCE2d_MakeParabola ml(Prb);
  return Handle(Geom2d_Parabola)(ml);
}

Handle(Geom2d_Parabola) geometry_creator::make_parabola(
    const gp_Ax22d &Axis, const Standard_Real Focal) {
  GCE2d_MakeParabola ml(Axis, Focal);
  return Handle(Geom2d_Parabola)(ml);
}

Handle(Geom2d_Parabola) geometry_creator::make_parabola(
    const gp_Ax2d &MirrorAxis, const Standard_Real Focal, const bool Sense) {
  GCE2d_MakeParabola ml(MirrorAxis, Focal, Sense);
  return Handle(Geom2d_Parabola)(ml);
}

Handle(Geom2d_Parabola) geometry_creator::make_parabola(const gp_Ax2d &D,
                                                        const gp_Pnt2d &F,
                                                        const bool Sense) {
  GCE2d_MakeParabola ml(D, F, Sense);
  return Handle(Geom2d_Parabola)(ml);
}

Handle(Geom2d_Parabola) geometry_creator::make_parabola(const gp_Pnt2d &S1,
                                                        const gp_Pnt2d &O) {
  GCE2d_MakeParabola ml(S1, O);
  return Handle(Geom2d_Parabola)(ml);
}

Handle(Geom2d_TrimmedCurve) geometry_creator::make_segment(const gp_Pnt2d &P1,
                                                           const gp_Pnt2d &P2) {
  GCE2d_MakeSegment ms(P1, P2);
  return Handle(Geom2d_TrimmedCurve)(ms);
}

Handle(Geom2d_TrimmedCurve) geometry_creator::make_segment(const gp_Pnt2d &P1,
                                                           const gp_Dir2d &V,
                                                           const gp_Pnt2d &P2) {
  GCE2d_MakeSegment ms(P1, V, P2);
  return Handle(Geom2d_TrimmedCurve)(ms);
}

Handle(Geom2d_TrimmedCurve) geometry_creator::make_segment(
    const gp_Lin2d &Line, const Standard_Real U1, const Standard_Real U2) {
  GCE2d_MakeSegment ms(Line, U1, U2);
  return Handle(Geom2d_TrimmedCurve)(ms);
}

Handle(Geom2d_TrimmedCurve) geometry_creator::make_segment(
    const gp_Lin2d &Line, const gp_Pnt2d &Point, const Standard_Real Ulast) {
  GCE2d_MakeSegment ms(Line, Point, Ulast);
  return Handle(Geom2d_TrimmedCurve)(ms);
}

Handle(Geom2d_TrimmedCurve) geometry_creator::make_segment(const gp_Lin2d &Line,
                                                           const gp_Pnt2d &P1,
                                                           const gp_Pnt2d &P2) {
  GCE2d_MakeSegment ms(Line, P1, P2);
  return Handle(Geom2d_TrimmedCurve)(ms);
}

Handle(Geom2d_Transformation)
    geometry_creator::make_mirror(const gp_Pnt2d &Point) {
  GCE2d_MakeMirror mr(Point);
  return Handle(Geom2d_Transformation)(mr);
}

Handle(Geom2d_Transformation)
    geometry_creator::make_mirror(const gp_Ax2d &Axis) {
  GCE2d_MakeMirror mr(Axis);
  return Handle(Geom2d_Transformation)(mr);
}

Handle(Geom2d_Transformation)
    geometry_creator::make_mirror(const gp_Lin2d &Line) {
  GCE2d_MakeMirror mr(Line);
  return Handle(Geom2d_Transformation)(mr);
}

Handle(Geom2d_Transformation) geometry_creator::make_mirror(
    const gp_Pnt2d &Point, const gp_Dir2d &Direc) {
  GCE2d_MakeMirror mr(Point, Direc);
  return Handle(Geom2d_Transformation)(mr);
}

Handle(Geom2d_Transformation) geometry_creator::make_rotation(
    const gp_Pnt2d &Point, const Standard_Real Angle) {
  GCE2d_MakeRotation mr(Point, Angle);
  return Handle(Geom2d_Transformation)(mr);
}

Handle(Geom2d_Transformation) geometry_creator::make_scale(
    const gp_Pnt2d &Point, const Standard_Real Scale) {
  GCE2d_MakeScale ms(Point, Scale);
  return Handle(Geom2d_Transformation)(ms);
}

Handle(Geom2d_Transformation)
    geometry_creator::make_translation(const gp_Vec2d &Vect) {
  GCE2d_MakeTranslation mt(Vect);
  return Handle(Geom2d_Transformation)(mt);
}

Handle(Geom2d_Transformation) geometry_creator::make_translation(
    const gp_Pnt2d &Point1, const gp_Pnt2d &Point2) {
  GCE2d_MakeTranslation mt(Point1, Point2);
  return Handle(Geom2d_Transformation)(mt);
}

Handle(Geom_BSplineCurve) geometry_creator::convert_approx_curve(
    const Handle(Geom_Curve) & Curve, const Standard_Real Tol3d,
    const GeomAbs_Shape Order, const Standard_Integer MaxSegments,
    const Standard_Integer MaxDegree) {
  GeomConvert_ApproxCurve cac(Curve, Tol3d, Order, MaxSegments, MaxDegree);
  return Handle(Geom_BSplineCurve)(cac.Curve());
}

Handle(Geom_BSplineSurface) geometry_creator::convert_approx_surface(
    const Handle(Geom_Surface) & Surf, const Standard_Real Tol3d,
    const GeomAbs_Shape UContinuity, const GeomAbs_Shape VContinuity,
    const Standard_Integer MaxDegU, const Standard_Integer MaxDegV,
    const Standard_Integer MaxSegments, const Standard_Integer PrecisCode) {
  GeomConvert_ApproxSurface cac(Surf, Tol3d, UContinuity, VContinuity, MaxDegU,
                                MaxDegV, MaxSegments, PrecisCode);
  return Handle(Geom_BSplineSurface)(cac.Surface());
}

} // namespace topo
} // namespace flywave
