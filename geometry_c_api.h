#ifndef GO_GEOMETRY_C_API_H
#define GO_GEOMETRY_C_API_H

#if defined(WIN32) || defined(WINDOWS) || defined(_WIN32) || defined(_WINDOWS)
#define GEOMCAPICALL __declspec(dllexport)
#else
#define GEOMCAPICALL
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _geom_geometry_t geom_geometry_t;
typedef struct _geom_transformation_t geom_transformation_t;
typedef struct _geom_axis_placement_t geom_axis_placement_t;
typedef struct _geom_axis1_placement_t geom_axis1_placement_t;
typedef struct _geom_axis2_placement_t geom_axis2_placement_t;
typedef struct _geom_curve_t geom_curve_t;
typedef struct _geom_bounded_curve_t geom_bounded_curve_t;
typedef struct _geom_bezier_curve_t geom_bezier_curve_t;
typedef struct _geom_bspline_curve_t geom_bspline_curve_t;
typedef struct _geom_trimmed_curve_t geom_trimmed_curve_t;
typedef struct _geom_conic_t geom_conic_t;
typedef struct _geom_circle_t geom_circle_t;
typedef struct _geom_ellipse_t geom_ellipse_t;
typedef struct _geom_hyperbola_t geom_hyperbola_t;
typedef struct _geom_parabola_t geom_parabola_t;
typedef struct _geom_line_t geom_line_t;
typedef struct _geom_offset_curve_t geom_offset_curve_t;
typedef struct _geom_point_t geom_point_t;
typedef struct _geom_cartesian_point_t geom_cartesian_point_t;
typedef struct _geom_surface_t geom_surface_t;
typedef struct _geom_bounded_surface_t geom_bounded_surface_t;
typedef struct _geom_bezier_surface_t geom_bezier_surface_t;
typedef struct _geom_bspline_surface_t geom_bspline_surface_t;
typedef struct _geom_rectangular_trimmed_surface_t
    geom_rectangular_trimmed_surface_t;
typedef struct _geom_elementary_surface_t geom_elementary_surface_t;
typedef struct _geom_cylindrical_surface_t geom_cylindrical_surface_t;
typedef struct _geom_plane_surface_t geom_plane_surface_t;
typedef struct _geom_conical_surface_t geom_conical_surface_t;
typedef struct _geom_spherical_surface_t geom_spherical_surface_t;
typedef struct _geom_toroidal_surface_t geom_toroidal_surface_t;
typedef struct _geom_offset_surface_t geom_offset_surface_t;
typedef struct _geom_swept_surface_t geom_swept_surface_t;
typedef struct _geom_surface_of_linear_extrusion_t
    geom_surface_of_linear_extrusion_t;
typedef struct _geom_surface_of_revolution_extrusion_t
    geom_surface_of_revolution_extrusion_t;
typedef struct _geom_plate_surface_t geom_plate_surface_t;
typedef struct _geom_vector_t geom_vector_t;
typedef struct _geom_direction_t geom_direction_t;
typedef struct _geom_vector_with_magnitude_t geom_vector_with_magnitude_t;

typedef struct _geom2d_geometry_t geom2d_geometry_t;
typedef struct _geom2d_transformation_t geom2d_transformation_t;
typedef struct _geom2d_axis_placement_t geom2d_axis_placement_t;
typedef struct _geom2d_curve_t geom2d_curve_t;
typedef struct _geom2d_bisector_curve_t geom2d_bisector_curve_t;
typedef struct _geom2d_bezier_bisec_ana_curve_t geom2d_bezier_bisec_ana_curve_t;
typedef struct _geom2d_bezier_bisec_cc_curve_t geom2d_bezier_bisec_cc_curve_t;
typedef struct _geom2d_bezier_bisec_pc_curve_t geom2d_bezier_bisec_pc_curve_t;
typedef struct _geom2d_bounded_curve_t geom2d_bounded_curve_t;
typedef struct _geom2d_bezier_curve_t geom2d_bezier_curve_t;
typedef struct _geom2d_bspline_curve_t geom2d_bspline_curve_t;
typedef struct _geom2d_trimmed_curve_t geom2d_trimmed_curve_t;
typedef struct _geom2d_conic_t geom2d_conic_t;
typedef struct _geom2d_circle_t geom2d_circle_t;
typedef struct _geom2d_ellipse_t geom2d_ellipse_t;
typedef struct _geom2d_hyperbola_t geom2d_hyperbola_t;
typedef struct _geom2d_parabola_t geom2d_parabola_t;
typedef struct _geom2d_line_t geom2d_line_t;
typedef struct _geom2d_offset_curve_t geom2d_offset_curve_t;
typedef struct _geom2d_point_t geom2d_point_t;
typedef struct _geom2d_cartesian_point_t geom2d_cartesian_point_t;
typedef struct _geom2d_vector_t geom2d_vector_t;
typedef struct _geom2d_direction_t geom2d_direction_t;
typedef struct _geom2d_vector_with_magnitude_t geom2d_vector_with_magnitude_t;

typedef struct _circ_t circ_t;
typedef struct _pnt3d_t pnt3d_t;
typedef struct _vec3d_t vec3d_t;
typedef struct _pnt2d_t pnt2d_t;
typedef struct _vec2d_t vec2d_t;
typedef struct _elips_t elips_t;
typedef struct _hyperbola_t hyperbola_t;
typedef struct _parabola_t parabola_t;
typedef struct _dir3d_t dir3d_t;
typedef struct _dir2d_t dir2d_t;
typedef struct _axis2_t axis2_t;
typedef struct _cone_t cone_t;
typedef struct _axis1_t axis1_t;
typedef struct _cylinder_t cylinder_t;
typedef struct _line_t line_t;
typedef struct _plane_t plane_t;
typedef struct _circ2d_t circ2d_t;
typedef struct _elips2d_t elips2d_t;
typedef struct _hyperbola2d_t hyperbola2d_t;
typedef struct _parabola2d_t parabola2d_t;
typedef struct _axis2d_t axis2d_t;
typedef struct _axis22d_t axis22d_t;
typedef struct _line2d_t line2d_t;

GEOMCAPICALL geom_trimmed_curve_t geom_make_arc_of_circle_two_alpha(
    circ_t Circ, double Alpha1, double Alpha2, bool Sense);

GEOMCAPICALL geom_trimmed_curve_t geom_make_arc_of_circle_alpha(circ_t Circ,
                                                                pnt3d_t P,
                                                                double Alpha,
                                                                bool Sense);

GEOMCAPICALL geom_trimmed_curve_t geom_make_arc_of_circle_point(circ_t Circ,
                                                                pnt3d_t P1,
                                                                pnt3d_t P2,
                                                                bool Sense);

GEOMCAPICALL geom_trimmed_curve_t geom_make_arc_of_point(pnt3d_t P1, pnt3d_t P2,
                                                         pnt3d_t P3);

GEOMCAPICALL geom_trimmed_curve_t geom_make_arc_of_circle_vector(pnt3d_t P1,
                                                                 vec3d_t V,
                                                                 pnt3d_t P2);

GEOMCAPICALL geom_trimmed_curve_t geom_make_arc_of_ellipsee_two_alpha(
    elips_t Elips, double Alpha1, double Alpha2, bool Sense);

GEOMCAPICALL geom_trimmed_curve_t geom_make_arc_of_ellipse_alpha(elips_t Elips,
                                                                 pnt3d_t P,
                                                                 double Alpha,
                                                                 bool Sense);

GEOMCAPICALL geom_trimmed_curve_t geom_make_arc_of_ellipse_point(elips_t Elips,
                                                                 pnt3d_t P1,
                                                                 pnt3d_t P2,
                                                                 bool Sense);

GEOMCAPICALL geom_trimmed_curve_t geom_make_arc_of_hyperbola_two_alpha(
    hyperbola_t Hypr, double Alpha1, double Alpha2, bool Sense);

GEOMCAPICALL geom_trimmed_curve_t geom_make_arc_of_hyperbola_alpha(
    hyperbola_t Hypr, pnt3d_t P, double Alpha, bool Sense);

GEOMCAPICALL geom_trimmed_curve_t geom_make_arc_of_hyperbola_point(
    hyperbola_t Hypr, pnt3d_t P1, pnt3d_t P2, bool Sense);

GEOMCAPICALL geom_trimmed_curve_t geom_make_arc_of_parabola_two_alpha(
    parabola_t Parab, double Alpha1, double Alpha2, bool Sense);

GEOMCAPICALL geom_trimmed_curve_t geom_make_arc_of_parabola_alpha(
    parabola_t Parab, pnt3d_t P, double Alpha, bool Sense);

GEOMCAPICALL geom_trimmed_curve_t geom_make_arc_of_parabola_point(
    parabola_t Parab, pnt3d_t P1, pnt3d_t P2, bool Sense);

GEOMCAPICALL geom_circle_t geom_make_circle(circ_t C);

GEOMCAPICALL geom_circle_t geom_make_circle_of_axis2(axis2_t A2, double Radius);

GEOMCAPICALL geom_circle_t geom_make_circle_of_dist(circ_t Circ, double Dist);

GEOMCAPICALL geom_circle_t geom_make_circle_of_point(circ_t Circ,
                                                     pnt3d_t Point);

GEOMCAPICALL geom_circle_t geom_make_circle_of_three_point(pnt3d_t P1,
                                                           pnt3d_t P2,
                                                           pnt3d_t P3);

GEOMCAPICALL geom_circle_t geom_make_circle_of_center_norm(pnt3d_t Center,
                                                           dir3d_t Norm,
                                                           double Radius);

GEOMCAPICALL geom_circle_t geom_make_circle_center_axis(pnt3d_t Center,
                                                        pnt3d_t PtAxis,
                                                        double Radius);

GEOMCAPICALL geom_circle_t geom_make_circle_of_axis1(axis1_t Axis,
                                                     double Radius);

GEOMCAPICALL geom_ellipse_t geom_make_ellipse(elips_t E);

GEOMCAPICALL geom_ellipse_t geom_make_ellipse_of_axis2(axis2_t A2,
                                                       double MajorRadius,
                                                       double MinorRadius);

GEOMCAPICALL geom_ellipse_t geom_make_ellipse_point_center(pnt3d_t S1,
                                                           pnt3d_t S2,
                                                           pnt3d_t Center);

GEOMCAPICALL geom_hyperbola_t geom_make_hyperbola(hyperbola_t H);

GEOMCAPICALL geom_hyperbola_t geom_make_hyperbola_of_axis2(axis2_t A2,
                                                           double MajorRadius,
                                                           double MinorRadius);

GEOMCAPICALL geom_hyperbola_t geom_make_hyperbola_point_center(pnt3d_t S1,
                                                               pnt3d_t S2,
                                                               pnt3d_t Center);

GEOMCAPICALL geom_conical_surface_t
geom_make_conical_surface_axis2(axis2_t A2, double Ang, double Radius);

GEOMCAPICALL geom_conical_surface_t geom_make_conical_surface(cone_t C);

GEOMCAPICALL geom_conical_surface_t geom_make_conical_surface_of_point(
    pnt3d_t P1, pnt3d_t P2, pnt3d_t P3, pnt3d_t P4);

GEOMCAPICALL geom_conical_surface_t geom_make_conical_surface_of_point_radius(
    pnt3d_t P1, pnt3d_t P2, double R1, double R2);

GEOMCAPICALL geom_cylindrical_surface_t
geom_make_cylindrical_surface_of_axis2(axis2_t A2, double Radius);

GEOMCAPICALL geom_cylindrical_surface_t
geom_make_cylindrical_surface(cylinder_t C);

GEOMCAPICALL geom_cylindrical_surface_t
geom_make_cylindrical_surface_of_point(cylinder_t Cyl, pnt3d_t Point);

GEOMCAPICALL geom_cylindrical_surface_t
geom_make_cylindrical_surface_of_dist(cylinder_t Cyl, double Dist);

GEOMCAPICALL geom_cylindrical_surface_t
geom_make_cylindrical_surface_of_three_point(pnt3d_t P1, pnt3d_t P2,
                                             pnt3d_t P3);

GEOMCAPICALL geom_cylindrical_surface_t
geom_make_cylindrical_surface_of_axis_radius(axis1_t Axis, double Radius);

GEOMCAPICALL geom_cylindrical_surface_t
geom_make_cylindrical_surface_of_circ(circ_t Circ);

GEOMCAPICALL geom_line_t geom_make_line_of_axis1(axis1_t A1);

GEOMCAPICALL geom_line_t geom_make_line(line_t L);

GEOMCAPICALL geom_line_t geom_make_line_of_point_dir(pnt3d_t P, dir3d_t V);

GEOMCAPICALL geom_line_t geom_make_line_point(line_t Lin, pnt3d_t Point);

GEOMCAPICALL geom_line_t geom_make_line_of_two_point(pnt3d_t P1, pnt3d_t P2);

GEOMCAPICALL geom_transformation_t geom_make_mirror_of_point(pnt3d_t Point);

GEOMCAPICALL geom_transformation_t geom_make_mirror_of_axis1(axis1_t Axis);

GEOMCAPICALL geom_transformation_t geom_make_mirror_of_line(line_t Line);

GEOMCAPICALL geom_transformation_t geom_make_mirror_of_point_dir(pnt3d_t Point,
                                                                 dir3d_t Direc);

GEOMCAPICALL geom_transformation_t geom_make_mirror_of_plane(plane_t Plane);

GEOMCAPICALL geom_transformation_t geom_make_mirror_of_axis2(axis2_t Plane);

GEOMCAPICALL geom_transformation_t geom_make_rotation_of_line(line_t Line,
                                                              double Angle);

GEOMCAPICALL geom_transformation_t geom_make_rotation_of_axis1(axis1_t Axis,
                                                               double Angle);

GEOMCAPICALL geom_transformation_t
geom_make_rotation_of_point_dir(pnt3d_t Point, dir3d_t Direc, double Angle);

GEOMCAPICALL geom_transformation_t geom_make_translation_of_vect(vec3d_t Vect);

GEOMCAPICALL geom_transformation_t
geom_make_translation_of_two_point(pnt3d_t Point1, pnt3d_t Point2);

GEOMCAPICALL geom_transformation_t geom_make_scale_of_point_scale(pnt3d_t Point,
                                                                  double Scale);

GEOMCAPICALL geom_plane_surface_t geom_make_plane(plane_t Pl);

GEOMCAPICALL geom_plane_surface_t geom_make_plane_of_point_dir(pnt3d_t P,
                                                               dir3d_t V);

GEOMCAPICALL geom_plane_surface_t geom_make_plane_of_lrud(double A, double B,
                                                          double C, double D);

GEOMCAPICALL geom_plane_surface_t geom_make_plane_of_point(plane_t Pln,
                                                           pnt3d_t Point);

GEOMCAPICALL geom_plane_surface_t geom_make_plane_of_dist(plane_t Pln,
                                                          double Dist);

GEOMCAPICALL geom_plane_surface_t geom_make_plane_of_three_point(pnt3d_t P1,
                                                                 pnt3d_t P2,
                                                                 pnt3d_t P3);

GEOMCAPICALL geom_plane_surface_t geom_make_plane_of_axis1(axis1_t Axis);

GEOMCAPICALL geom_trimmed_curve_t geom_make_segment_of_two_point(pnt3d_t P1,
                                                                 pnt3d_t P2);

GEOMCAPICALL geom_trimmed_curve_t geom_make_segment_of_line_u(line_t Line,
                                                              double U1,
                                                              double U2);

GEOMCAPICALL geom_trimmed_curve_t geom_make_segment_of_line_point(line_t Line,
                                                                  pnt3d_t Point,
                                                                  double Ulast);

GEOMCAPICALL geom_trimmed_curve_t geom_make_segment_of_point(line_t Line,
                                                             pnt3d_t P1,
                                                             pnt3d_t P2);

GEOMCAPICALL geom_rectangular_trimmed_surface_t
geom_make_trimmed_cone_of_point(pnt3d_t P1, pnt3d_t P2, pnt3d_t P3, pnt3d_t P4);

GEOMCAPICALL geom_rectangular_trimmed_surface_t
geom_make_trimmed_cone_of_point_radius(pnt3d_t P1, pnt3d_t P2, double R1,
                                       double R2);

GEOMCAPICALL geom_rectangular_trimmed_surface_t
geom_make_trimmed_cylinder_of_point(pnt3d_t P1, pnt3d_t P2, pnt3d_t P3);

GEOMCAPICALL geom_rectangular_trimmed_surface_t
geom_make_trimmed_cylinder_of_circ_height(circ_t Circ, double Height);

GEOMCAPICALL geom_rectangular_trimmed_surface_t
geom_make_trimmed_cylinder_axis_radius(axis1_t A1, double Radius,
                                       double Height);

GEOMCAPICALL geom2d_trimmed_curve_t geom2d_make_arc_of_circle_of_alpha(circ2d_t Circ,
                                                              double Alpha1,
                                                              double Alpha2,
                                                              bool Sense);

GEOMCAPICALL geom2d_trimmed_curve_t geom2d_make_arc_of_circle_alpha(circ2d_t Circ,
                                                              pnt2d_t P,
                                                              double Alpha,
                                                              bool Sense);

GEOMCAPICALL geom2d_trimmed_curve_t geom2d_make_arc_of_circle_alpha(circ2d_t Circ,
                                                              pnt2d_t P1,
                                                              pnt2d_t P2,
                                                              bool Sense);

GEOMCAPICALL geom2d_trimmed_curve_t geom2d_make_arc_of_circle(pnt2d_t P1,
                                                              pnt2d_t P2,
                                                              pnt2d_t P3);

GEOMCAPICALL geom2d_trimmed_curve_t
geom2d_make_arc_of_circle_vector(pnt2d_t P1, vec2d_t V, pnt2d_t P2);

GEOMCAPICALL geom2d_trimmed_curve_t geom2d_make_arc_of_ellipse(elips2d_t Elips,
                                                               double Alpha1,
                                                               double Alpha2,
                                                               bool Sense);

GEOMCAPICALL geom2d_trimmed_curve_t geom2d_make_arc_of_ellipse(elips2d_t Elips,
                                                               pnt2d_t P,
                                                               double Alpha,
                                                               bool Sense);

GEOMCAPICALL geom2d_trimmed_curve_t geom2d_make_arc_of_ellipse(elips2d_t Elips,
                                                               pnt2d_t P1,
                                                               pnt2d_t P2,
                                                               bool Sense);

GEOMCAPICALL geom2d_trimmed_curve_t geom2d_make_arc_of_hyperbola(
    hyperbola2d_t Hypr, double Alpha1, double Alpha2, bool Sense);

GEOMCAPICALL geom2d_trimmed_curve_t geom2d_make_arc_of_hyperbola(
    hyperbola2d_t Hypr, pnt2d_t P, double Alpha, bool Sense);

GEOMCAPICALL geom2d_trimmed_curve_t geom2d_make_arc_of_hyperbola(
    hyperbola2d_t Hypr, pnt2d_t P1, pnt2d_t P2, bool Sense);

GEOMCAPICALL geom2d_trimmed_curve_t geom2d_make_arc_of_parabola(
    parabola2d_t Parab, double Alpha1, double Alpha2, bool Sense);

GEOMCAPICALL geom2d_trimmed_curve_t geom2d_make_arc_of_parabola(
    parabola2d_t Parab, pnt2d_t P, double Alpha, bool Sense);

GEOMCAPICALL geom2d_trimmed_curve_t geom2d_make_arc_of_parabola(
    parabola2d_t Parab, pnt2d_t P1, pnt2d_t P2, bool Sense);

GEOMCAPICALL geom2d_circle_t geom2d_make_circle(circ2d_t C);

GEOMCAPICALL geom2d_circle_t geom2d_make_circle(axis2d_t A, double Radius,
                                                bool Sense);

GEOMCAPICALL geom2d_circle_t geom2d_make_circle(axis22d_t A, double Radius);

GEOMCAPICALL geom2d_circle_t geom2d_make_circle(circ2d_t Circ, double Dist);

GEOMCAPICALL geom2d_circle_t geom2d_make_circle(circ2d_t Circ, pnt2d_t Point);

GEOMCAPICALL geom2d_circle_t geom2d_make_circle(pnt2d_t P1, pnt2d_t P2,
                                                pnt2d_t P3);

GEOMCAPICALL geom2d_circle_t geom2d_make_circle(pnt2d_t P, double Radius,
                                                bool Sense);

GEOMCAPICALL geom2d_circle_t geom2d_make_circle(pnt2d_t Center, pnt2d_t Point,
                                                bool Sense);

GEOMCAPICALL geom2d_ellipse_t geom2d_make_ellipse(elips2d_t E);

GEOMCAPICALL geom2d_ellipse_t geom2d_make_ellipse(axis2d_t MajorAxis,
                                                  double MajorRadius,
                                                  double MinorRadius,
                                                  bool Sense);

GEOMCAPICALL geom2d_ellipse_t geom2d_make_ellipse(axis22d_t Axis,
                                                  double MajorRadius,
                                                  double MinorRadius);

GEOMCAPICALL geom2d_ellipse_t geom2d_make_ellipse(pnt2d_t S1, pnt2d_t S2,
                                                  pnt2d_t Center);

GEOMCAPICALL geom2d_hyperbola_t geom2d_make_hyperbola(hyperbola2d_t H);

GEOMCAPICALL geom2d_hyperbola_t geom2d_make_hyperbola(axis2d_t MajorAxis,
                                                      double MajorRadius,
                                                      double MinorRadius,
                                                      bool Sense);

GEOMCAPICALL geom2d_hyperbola_t geom2d_make_hyperbola(axis22d_t Axis,
                                                      double MajorRadius,
                                                      double MinorRadius);

GEOMCAPICALL geom2d_hyperbola_t geom2d_make_hyperbola(pnt2d_t S1, pnt2d_t S2,
                                                      pnt2d_t Center);

GEOMCAPICALL geom2d_line_t geom2d_make_line(axis2d_t A);

GEOMCAPICALL geom2d_line_t geom2d_make_line(line2d_t L);

GEOMCAPICALL geom2d_line_t geom2d_make_line(pnt2d_t P, dir2d_t V);

GEOMCAPICALL geom2d_line_t geom2d_make_line(line2d_t Lin, pnt2d_t Point);

GEOMCAPICALL geom2d_line_t geom2d_make_line(line2d_t Lin, double Dist);

GEOMCAPICALL geom2d_line_t geom2d_make_line(pnt2d_t P1, pnt2d_t P2);

GEOMCAPICALL geom2d_parabola_t geom2d_make_parabola(parabola2d_t Prb);

GEOMCAPICALL geom2d_parabola_t geom2d_make_parabola(axis22d_t Axis,
                                                    double Focal);

GEOMCAPICALL geom2d_parabola_t geom2d_make_parabola(axis2d_t MirrorAxis,
                                                    double Focal, bool Sense);

GEOMCAPICALL geom2d_parabola_t geom2d_make_parabola(axis2d_t D, pnt2d_t F,
                                                    bool Sense);

GEOMCAPICALL geom2d_parabola_t geom2d_make_parabola(pnt2d_t S1, pnt2d_t O);

GEOMCAPICALL geom2d_trimmed_curve_t geom2d_make_segment(pnt2d_t P1, pnt2d_t P2);

GEOMCAPICALL geom2d_trimmed_curve_t geom2d_make_segment(pnt2d_t P1, dir2d_t V,
                                                        pnt2d_t P2);

GEOMCAPICALL geom2d_trimmed_curve_t geom2d_make_segment(line2d_t Line,
                                                        double U1, double U2);

GEOMCAPICALL geom2d_trimmed_curve_t geom2d_make_segment(line2d_t Line,
                                                        pnt2d_t Point,
                                                        double Ulast);

GEOMCAPICALL geom2d_trimmed_curve_t geom2d_make_segment(line2d_t Line,
                                                        pnt2d_t P1, pnt2d_t P2);

GEOMCAPICALL geom2d_transformation_t geom2d_make_mirror(pnt2d_t Point);

GEOMCAPICALL geom2d_transformation_t geom2d_make_mirror(axis2d_t Axis);

GEOMCAPICALL geom2d_transformation_t geom2d_make_mirror(line2d_t Line);

GEOMCAPICALL geom2d_transformation_t geom2d_make_mirror(pnt2d_t Point,
                                                        dir2d_t Direc);

GEOMCAPICALL geom2d_transformation_t geom2d_make_rotation(pnt2d_t Point,
                                                          double Angle);

GEOMCAPICALL geom2d_transformation_t geom2d_make_scale(pnt2d_t Point,
                                                       double Scale);

GEOMCAPICALL geom2d_transformation_t geom2d_make_translation(vec2d_t Vect);

GEOMCAPICALL geom2d_transformation_t geom2d_make_translation(pnt2d_t Point1,
                                                             pnt2d_t Point2);

#ifdef __cplusplus
}
#endif

#endif
