#ifndef __FLYWAVE_MESH_TOPO_GEOMETRY_CREATOR_HH__
#define __FLYWAVE_MESH_TOPO_GEOMETRY_CREATOR_HH__

namespace flywave {
namespace topo {

class geometry_creator {
public:
  geometry_creator() = default;
  virtual ~geometry_creator() = default;

  static geom_trimmed_curve make_arc_of_circle(const circ &Circ,
                                               const Standard_Real Alpha1,
                                               const Standard_Real Alpha2,
                                               const bool Sense);

  static geom_trimmed_curve make_arc_of_circle(const circ &Circ,
                                               const vector3<Standard_Real> &P,
                                               const Standard_Real Alpha,
                                               const bool Sense);

  static geom_trimmed_curve make_arc_of_circle(const circ &Circ,
                                               const vector3<Standard_Real> &P1,
                                               const vector3<Standard_Real> &P2,
                                               const bool Sense);

  static geom_trimmed_curve
  make_arc_of_circle(const vector3<Standard_Real> &P1,
                     const vector3<Standard_Real> &P2,
                     const vector3<Standard_Real> &P3);

  static geom_trimmed_curve
  make_arc_of_circle_vector(const vector3<Standard_Real> &P1,
                            const vector3<Standard_Real> &V,
                            const vector3<Standard_Real> &P2);

  static geom_trimmed_curve make_arc_of_ellipse(const elips &Elips,
                                                const Standard_Real Alpha1,
                                                const Standard_Real Alpha2,
                                                const bool Sense);

  static geom_trimmed_curve make_arc_of_ellipse(const elips &Elips,
                                                const vector3<Standard_Real> &P,
                                                const Standard_Real Alpha,
                                                const bool Sense);

  static geom_trimmed_curve
  make_arc_of_ellipse(const elips &Elips, const vector3<Standard_Real> &P1,
                      const vector3<Standard_Real> &P2, const bool Sense);

  static geom_trimmed_curve make_arc_of_hyperbola(const hyperbola &Hypr,
                                                  const Standard_Real Alpha1,
                                                  const Standard_Real Alpha2,
                                                  const bool Sense);

  static geom_trimmed_curve
  make_arc_of_hyperbola(const hyperbola &Hypr, const vector3<Standard_Real> &P,
                        const Standard_Real Alpha, const bool Sense);

  static geom_trimmed_curve
  make_arc_of_hyperbola(const hyperbola &Hypr, const vector3<Standard_Real> &P1,
                        const vector3<Standard_Real> &P2, const bool Sense);

  static geom_trimmed_curve make_arc_of_parabola(const parabola &Parab,
                                                 const Standard_Real Alpha1,
                                                 const Standard_Real Alpha2,
                                                 const bool Sense);

  static geom_trimmed_curve
  make_arc_of_parabola(const parabola &Parab, const vector3<Standard_Real> &P,
                       const Standard_Real Alpha, const bool Sense);

  static geom_trimmed_curve
  make_arc_of_parabola(const parabola &Parab, const vector3<Standard_Real> &P1,
                       const vector3<Standard_Real> &P2, const bool Sense);

  static geom_circle make_circle(const circ &C);

  static geom_circle make_circle(const axis2 &A2, const Standard_Real Radius);

  static geom_circle make_circle(const circ &Circ, const Standard_Real Dist);

  static geom_circle make_circle(const circ &Circ,
                                 const vector3<Standard_Real> &Point);

  static geom_circle make_circle(const vector3<Standard_Real> &P1,
                                 const vector3<Standard_Real> &P2,
                                 const vector3<Standard_Real> &P3);

  static geom_circle make_circle(const vector3<Standard_Real> &Center,
                                 const dir &Norm, const Standard_Real Radius);

  static geom_circle make_circle(const vector3<Standard_Real> &Center,
                                 const vector3<Standard_Real> &PtAxis,
                                 const Standard_Real Radius);

  static geom_circle make_circle(const axis1 &Axis, const Standard_Real Radius);

  static geom_ellipse make_ellipse(const elips &E);

  static geom_ellipse make_ellipse(const axis2 &A2,
                                   const Standard_Real MajorRadius,
                                   const Standard_Real MinorRadius);

  static geom_ellipse make_ellipse(const vector3<Standard_Real> &S1,
                                   const vector3<Standard_Real> &S2,
                                   const vector3<Standard_Real> &Center);

  static geom_hyperbola make_hyperbola(const hyperbola &H);

  static geom_hyperbola make_hyperbola(const axis2 &A2,
                                       const Standard_Real MajorRadius,
                                       const Standard_Real MinorRadius);

  static geom_hyperbola make_hyperbola(const vector3<Standard_Real> &S1,
                                       const vector3<Standard_Real> &S2,
                                       const vector3<Standard_Real> &Center);

  static geom_conical_surface make_conical_surface(const axis2 &A2,
                                                   const Standard_Real Ang,
                                                   const Standard_Real Radius);

  static geom_conical_surface make_conical_surface(const cone &C);

  static geom_conical_surface make_conical_surface(
      const vector3<Standard_Real> &P1, const vector3<Standard_Real> &P2,
      const vector3<Standard_Real> &P3, const vector3<Standard_Real> &P4);

  static geom_conical_surface
  make_conical_surface(const vector3<Standard_Real> &P1,
                       const vector3<Standard_Real> &P2, const Standard_Real R1,
                       const Standard_Real R2);

  static geom_cylindrical_surface
  make_cylindrical_surface(const axis2 &A2, const Standard_Real Radius);

  static geom_cylindrical_surface make_cylindrical_surface(const cylinder &C);

  static geom_cylindrical_surface
  make_cylindrical_surface(const cylinder &Cyl,
                           const vector3<Standard_Real> &Point);

  static geom_cylindrical_surface
  make_cylindrical_surface(const cylinder &Cyl, const Standard_Real Dist);

  static geom_cylindrical_surface
  make_cylindrical_surface(const vector3<Standard_Real> &P1,
                           const vector3<Standard_Real> &P2,
                           const vector3<Standard_Real> &P3);

  static geom_cylindrical_surface
  make_cylindrical_surface(const axis1 &Axis, const Standard_Real Radius);

  static geom_cylindrical_surface make_cylindrical_surface(const circ &Circ);

  static geom_line make_line(const axis1 &A1);

  static geom_line make_line(const line &L);

  static geom_line make_line(const vector3<Standard_Real> &P, const dir &V);

  static geom_line make_line(const line &Lin,
                             const vector3<Standard_Real> &Point);

  static geom_line make_line(const vector3<Standard_Real> &P1,
                             const vector3<Standard_Real> &P2);

  static geom_transformation make_mirror(const vector3<Standard_Real> &Point);

  static geom_transformation make_mirror(const axis1 &Axis);

  static geom_transformation make_mirror(const line &Line);

  static geom_transformation make_mirror(const vector3<Standard_Real> &Point,
                                         const dir &Direc);

  static geom_transformation make_mirror(const plane &Plane);

  static geom_transformation make_mirror(const axis2 &Plane);

  static geom_transformation make_rotation(const line &Line,
                                           const Standard_Real Angle);

  static geom_transformation make_rotation(const axis1 &Axis,
                                           const Standard_Real Angle);

  static geom_transformation make_rotation(const vector3<Standard_Real> &Point,
                                           const dir &Direc,
                                           const Standard_Real Angle);

  static geom_transformation
  make_translation(const vector3<Standard_Real> &Vect);

  static geom_transformation
  make_translation(const vector3<Standard_Real> &Point1,
                   const vector3<Standard_Real> &Point2);

  static geom_transformation make_scale(const vector3<Standard_Real> &Point,
                                        const Standard_Real Scale);

  static geom_plane_surface make_plane(const plane &Pl);

  static geom_plane_surface make_plane(const vector3<Standard_Real> &P,
                                       const dir &V);

  static geom_plane_surface make_plane(const Standard_Real A,
                                       const Standard_Real B,
                                       const Standard_Real C,
                                       const Standard_Real D);

  static geom_plane_surface make_plane(const plane &Pln,
                                       const vector3<Standard_Real> &Point);

  static geom_plane_surface make_plane(const plane &Pln,
                                       const Standard_Real Dist);

  static geom_plane_surface make_plane(const vector3<Standard_Real> &P1,
                                       const vector3<Standard_Real> &P2,
                                       const vector3<Standard_Real> &P3);

  static geom_plane_surface make_plane(const axis1 &Axis);

  static geom_trimmed_curve make_segment(const vector3<Standard_Real> &P1,
                                         const vector3<Standard_Real> &P2);

  static geom_trimmed_curve make_segment(const line &Line,
                                         const Standard_Real U1,
                                         const Standard_Real U2);

  static geom_trimmed_curve make_segment(const line &Line,
                                         const vector3<Standard_Real> &Point,
                                         const Standard_Real Ulast);

  static geom_trimmed_curve make_segment(const line &Line,
                                         const vector3<Standard_Real> &P1,
                                         const vector3<Standard_Real> &P2);

  static geom_rectangular_trimmed_surface make_trimmed_cone(
      const vector3<Standard_Real> &P1, const vector3<Standard_Real> &P2,
      const vector3<Standard_Real> &P3, const vector3<Standard_Real> &P4);

  static geom_rectangular_trimmed_surface
  make_trimmed_cone(const vector3<Standard_Real> &P1,
                    const vector3<Standard_Real> &P2, const Standard_Real R1,
                    const Standard_Real R2);

  static geom_rectangular_trimmed_surface
  make_trimmed_cylinder(const vector3<Standard_Real> &P1,
                        const vector3<Standard_Real> &P2,
                        const vector3<Standard_Real> &P3);

  static geom_rectangular_trimmed_surface
  make_trimmed_cylinder(const circ &Circ, const Standard_Real Height);

  static geom_rectangular_trimmed_surface
  make_trimmed_cylinder(const axis1 &A1, const Standard_Real Radius,
                        const Standard_Real Height);

  static geom2d_trimmed_curve make_arc_of_circle(const circ2d &Circ,
                                                 const Standard_Real Alpha1,
                                                 const Standard_Real Alpha2,
                                                 const bool Sense = true);

  static geom2d_trimmed_curve
  make_arc_of_circle(const circ2d &Circ, const vector2<Standard_Real> &P,
                     const Standard_Real Alpha, const bool Sense = true);

  static geom2d_trimmed_curve
  make_arc_of_circle(const circ2d &Circ, const vector2<Standard_Real> &P1,
                     const vector2<Standard_Real> &P2, const bool Sense = true);

  static geom2d_trimmed_curve
  make_arc_of_circle(const vector2<Standard_Real> &P1,
                     const vector2<Standard_Real> &P2,
                     const vector2<Standard_Real> &P3);

  static geom2d_trimmed_curve
  make_arc_of_circle_vector(const vector2<Standard_Real> &P1,
                            const vector2<Standard_Real> &V,
                            const vector2<Standard_Real> &P2);

  static geom2d_trimmed_curve make_arc_of_ellipse(const elips2d &Elips,
                                                  const Standard_Real Alpha1,
                                                  const Standard_Real Alpha2,
                                                  const bool Sense = true);

  static geom2d_trimmed_curve
  make_arc_of_ellipse(const elips2d &Elips, const vector2<Standard_Real> &P,
                      const Standard_Real Alpha, const bool Sense = true);

  static geom2d_trimmed_curve
  make_arc_of_ellipse(const elips2d &Elips, const vector2<Standard_Real> &P1,
                      const vector2<Standard_Real> &P2,
                      const bool Sense = true);

  static geom2d_trimmed_curve make_arc_of_hyperbola(const hyperbola2d &Hypr,
                                                    const Standard_Real Alpha1,
                                                    const Standard_Real Alpha2,
                                                    const bool Sense = true);

  static geom2d_trimmed_curve
  make_arc_of_hyperbola(const hyperbola2d &Hypr,
                        const vector2<Standard_Real> &P,
                        const Standard_Real Alpha, const bool Sense = true);

  static geom2d_trimmed_curve make_arc_of_hyperbola(
      const hyperbola2d &Hypr, const vector2<Standard_Real> &P1,
      const vector2<Standard_Real> &P2, const bool Sense = true);

  static geom2d_trimmed_curve make_arc_of_parabola(const parabola2d &Parab,
                                                   const Standard_Real Alpha1,
                                                   const Standard_Real Alpha2,
                                                   const bool Sense = true);

  static geom2d_trimmed_curve
  make_arc_of_parabola(const parabola2d &Parab, const vector2<Standard_Real> &P,
                       const Standard_Real Alpha, const bool Sense = true);

  static geom2d_trimmed_curve make_arc_of_parabola(
      const parabola2d &Parab, const vector2<Standard_Real> &P1,
      const vector2<Standard_Real> &P2, const bool Sense = true);

  static geom2d_circle make_circle(const circ2d &C);

  static geom2d_circle make_circle(const axis2d &A, const Standard_Real Radius,
                                   const bool Sense = true);

  static geom2d_circle make_circle(const axis22d &A,
                                   const Standard_Real Radius);

  static geom2d_circle make_circle(const circ2d &Circ,
                                   const Standard_Real Dist);

  static geom2d_circle make_circle(const circ2d &Circ,
                                   const vector2<Standard_Real> &Point);

  static geom2d_circle make_circle(const vector2<Standard_Real> &P1,
                                   const vector2<Standard_Real> &P2,
                                   const vector2<Standard_Real> &P3);

  static geom2d_circle make_circle(const vector2<Standard_Real> &P,
                                   const Standard_Real Radius,
                                   const bool Sense = true);

  static geom2d_circle make_circle(const vector2<Standard_Real> &Center,
                                   const vector2<Standard_Real> &Point,
                                   const bool Sense = true);

  static geom2d_ellipse make_ellipse(const elips2d &E);

  static geom2d_ellipse make_ellipse(const axis2d &MajorAxis,
                                     const Standard_Real MajorRadius,
                                     const Standard_Real MinorRadius,
                                     const bool Sense = true);

  static geom2d_ellipse make_ellipse(const axis22d &Axis,
                                     const Standard_Real MajorRadius,
                                     const Standard_Real MinorRadius);

  static geom2d_ellipse make_ellipse(const vector2<Standard_Real> &S1,
                                     const vector2<Standard_Real> &S2,
                                     const vector2<Standard_Real> &Center);

  static geom2d_hyperbola make_hyperbola(const hyperbola2d &H);

  static geom2d_hyperbola make_hyperbola(const axis2d &MajorAxis,
                                         const Standard_Real MajorRadius,
                                         const Standard_Real MinorRadius,
                                         const bool Sense);

  static geom2d_hyperbola make_hyperbola(const axis22d &Axis,
                                         const Standard_Real MajorRadius,
                                         const Standard_Real MinorRadius);

  static geom2d_hyperbola make_hyperbola(const vector2<Standard_Real> &S1,
                                         const vector2<Standard_Real> &S2,
                                         const vector2<Standard_Real> &Center);

  static geom2d_line make_line(const axis2d &A);

  static geom2d_line make_line(const line2d &L);

  static geom2d_line make_line(const vector2<Standard_Real> &P, const dir2d &V);

  static geom2d_line make_line(const line2d &Lin,
                               const vector2<Standard_Real> &Point);

  static geom2d_line make_line(const line2d &Lin, const Standard_Real Dist);

  static geom2d_line make_line(const vector2<Standard_Real> &P1,
                               const vector2<Standard_Real> &P2);

  static geom2d_parabola make_parabola(const parabola2d &Prb);

  static geom2d_parabola make_parabola(const axis22d &Axis,
                                       const Standard_Real Focal);

  static geom2d_parabola make_parabola(const axis2d &MirrorAxis,
                                       const Standard_Real Focal,
                                       const bool Sense);

  static geom2d_parabola make_parabola(const axis2d &D,
                                       const vector2<Standard_Real> &F,
                                       const bool Sense = true);

  static geom2d_parabola make_parabola(const vector2<Standard_Real> &S1,
                                       const vector2<Standard_Real> &O);

  static geom2d_trimmed_curve make_segment(const vector2<Standard_Real> &P1,
                                           const vector2<Standard_Real> &P2);

  static geom2d_trimmed_curve make_segment(const vector2<Standard_Real> &P1,
                                           const dir2d &V,
                                           const vector2<Standard_Real> &P2);

  static geom2d_trimmed_curve make_segment(const line2d &Line,
                                           const Standard_Real U1,
                                           const Standard_Real U2);

  static geom2d_trimmed_curve make_segment(const line2d &Line,
                                           const vector2<Standard_Real> &Point,
                                           const Standard_Real Ulast);

  static geom2d_trimmed_curve make_segment(const line2d &Line,
                                           const vector2<Standard_Real> &P1,
                                           const vector2<Standard_Real> &P2);

  static geom2d_transformation make_mirror(const vector2<Standard_Real> &Point);

  static geom2d_transformation make_mirror(const axis2d &Axis);

  static geom2d_transformation make_mirror(const line2d &Line);

  static geom2d_transformation make_mirror(const vector2<Standard_Real> &Point,
                                           const dir2d &Direc);

  static geom2d_transformation
  make_rotation(const vector2<Standard_Real> &Point, const Standard_Real Angle);

  static geom2d_transformation make_scale(const vector2<Standard_Real> &Point,
                                          const Standard_Real Scale);

  static geom2d_transformation
  make_translation(const vector2<Standard_Real> &Vect);

  static geom2d_transformation
  make_translation(const vector2<Standard_Real> &Point1,
                   const vector2<Standard_Real> &Point2);

  static geom_bspline_curve
  convert_approx_curve(const geom_curve &Curve, const Standard_Real Tol3d,
                       const GeomAbs_Shape Order,
                       const Standard_Integer MaxSegments,
                       const Standard_Integer MaxDegree);

  static geom_bspline_surface convert_approx_surface(
      const geom_surface &Surf, const Standard_Real Tol3d,
      const GeomAbs_Shape UContinuity, const GeomAbs_Shape VContinuity,
      const Standard_Integer MaxDegU, const Standard_Integer MaxDegV,
      const Standard_Integer MaxSegments, const Standard_Integer PrecisCode);
};

} // namespace topo
} // namespace flywave

#endif // __FLYWAVE_MESH_TOPO_GEOMETRY_CREATOR_HH__
