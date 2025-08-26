#include "standard_c_api.h"
#include "standard_impl.hh"

#ifdef __cplusplus
extern "C" {
#endif

dir3d_t make_dir(vec3d_t p) {
  gce_MakeDir md(cast_to_gp(p));
  try {
    return cast_from_gp(md.Value());
  } catch (...) {
    return dir3d_t{};
  }
}

dir3d_t make_dir_from_xyz(double x, double y, double z) {
  gce_MakeDir md(x, y, z);
  try {
    return cast_from_gp(md.Value());
  } catch (...) {
    return dir3d_t{};
  }
}

dir3d_t make_dir_from_point(pnt3d_t p1, pnt3d_t p2) {
  gce_MakeDir md(gp_Pnt(cast_to_gp(p1)), gp_Pnt(cast_to_gp(p2)));
  try {
    return cast_from_gp(md.Value());
  } catch (...) {
    return dir3d_t{};
  }
}

dir2d_t make_dir2d(vec2d_t p) {
  gce_MakeDir2d md(cast_to_gp(p));
  try {
    return cast_from_gp(md.Value());
  } catch (...) {
    return dir2d_t{};
  }
}

dir2d_t make_dir2d_from_xy(double x, double y) {
  gce_MakeDir2d md(x, y);
  try {
    return cast_from_gp(md.Value());
  } catch (...) {
    return dir2d_t{};
  }
}

dir2d_t make_dir2d_from_point(pnt2d_t p1, pnt2d_t p2) {
  gce_MakeDir2d md(gp_Pnt2d(cast_to_gp(p1)), gp_Pnt2d(cast_to_gp(p2)));
  try {
    return cast_from_gp(md.Value());
  } catch (...) {
    return dir2d_t{};
  }
}

axis1_t make_axis(pnt3d_t p, dir3d_t v) {
  gp_Ax1 ax1{cast_to_gp(p), cast_to_gp(v)};
  return cast_from_gp(ax1);
}

axis2_t make_axis2_from_nvx(pnt3d_t p, dir3d_t N, dir3d_t Vx) {
  gp_Ax2 ax2{gp_Pnt(cast_to_gp(p)), cast_to_gp(N), cast_to_gp(Vx)};
  return cast_from_gp(ax2);
}

axis2_t make_axis2(pnt3d_t p, dir3d_t v) {
  gp_Ax2 ax2{gp_Pnt(cast_to_gp(p)), cast_to_gp(v)};
  return cast_from_gp(ax2);
}

axis3_t make_axis3(axis2_t a) {
  gp_Ax3 ax3{cast_to_gp(a)};
  return cast_from_gp(ax3);
}

axis3_t make_axis3_from_nvx(pnt3d_t p, dir3d_t N, dir3d_t Vx) {
  gp_Ax3 ax3{gp_Pnt(cast_to_gp(p)), cast_to_gp(N), cast_to_gp(Vx)};
  return cast_from_gp(ax3);
}

axis3_t make_axis3_from_v(pnt3d_t p, dir3d_t v) {
  gp_Ax3 ax3{gp_Pnt(cast_to_gp(p)), cast_to_gp(v)};
  return cast_from_gp(ax3);
}

axis2d_t make_axis2d(pnt2d_t p, dir2d_t v) {
  gp_Ax2d ax2{gp_Pnt2d(cast_to_gp(p)), cast_to_gp(v)};
  return cast_from_gp(ax2);
}

axis22d_t make_axis22d(axis2d_t a) {
  gp_Ax22d ax2{cast_to_gp(a)};
  return cast_from_gp(ax2);
}

axis22d_t make_axis22d_from_v(pnt2d_t p, dir2d_t v) {
  gp_Ax22d ax2{gp_Pnt2d(cast_to_gp(p)), cast_to_gp(v)};
  return cast_from_gp(ax2);
}

axis22d_t make_axis22d_from_vxy(pnt2d_t p, dir2d_t vx, dir2d_t vy) {
  gp_Ax22d ax2{gp_Pnt2d(cast_to_gp(p)), cast_to_gp(vx), cast_to_gp(vy)};
  return cast_from_gp(ax2);
}

circ_t make_circ_from_axis2(axis2_t a, double radius) {
  gce_MakeCirc mc(cast_to_gp(a), radius);
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return circ_t{};
  }
}

circ_t make_circ_from_circ_dist(circ_t a, double Dist) {
  gce_MakeCirc mc(cast_to_gp(a), Dist);
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return circ_t{};
  }
}

circ_t make_circ_from_circ_point(circ_t a, pnt3d_t p) {
  gce_MakeCirc mc(cast_to_gp(a), cast_to_gp(p));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return circ_t{};
  }
}

circ_t make_circ_from_point(pnt3d_t p1, pnt3d_t p2, pnt3d_t p3) {
  gce_MakeCirc mc(gp_Pnt(cast_to_gp(p1)), gp_Pnt(cast_to_gp(p2)),
                  gp_Pnt(cast_to_gp(p3)));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return circ_t{};
  }
}

circ_t make_circ_from_center_norm(pnt3d_t center, dir3d_t Norm, double radius) {
  gce_MakeCirc mc(gp_Pnt(cast_to_gp(center)), gp_Dir(cast_to_gp(Norm)), radius);
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return circ_t{};
  }
}

circ_t make_circ_from_center_plan(pnt3d_t center, plane_t pl, double radius) {
  gce_MakeCirc mc(gp_Pnt(cast_to_gp(center)), cast_to_gp(pl), radius);
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return circ_t{};
  }
}

circ_t make_circ_from_axis1(axis1_t a, double radius) {
  gce_MakeCirc mc(cast_to_gp(a), radius);
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return circ_t{};
  }
}

circ2d_t make_circ2d_from_axis2(axis2d_t a, double radius) {
  gce_MakeCirc2d mc(cast_to_gp(a), radius);
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return circ2d_t{};
  }
}

circ2d_t make_circ2d_from_axis22d(axis22d_t a, double radius) {
  gce_MakeCirc2d mc(cast_to_gp(a), radius);
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return circ2d_t{};
  }
}

circ2d_t make_circ2d_from_circ_dist(circ2d_t a, double Dist) {
  gce_MakeCirc2d mc(cast_to_gp(a), Dist);
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return circ2d_t{};
  }
}

circ2d_t make_circ2d_from_circ2d(circ2d_t a, pnt2d_t p) {
  gce_MakeCirc2d mc(cast_to_gp(a), gp_Pnt2d(cast_to_gp(p)));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return circ2d_t{};
  }
}

circ2d_t make_circ2d_from_point(pnt2d_t p1, pnt2d_t p2, pnt2d_t p3) {
  gce_MakeCirc2d mc(gp_Pnt2d(cast_to_gp(p1)), gp_Pnt2d(cast_to_gp(p2)),
                    gp_Pnt2d(cast_to_gp(p3)));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return circ2d_t{};
  }
}

circ2d_t make_circ2d_from_center_radius(pnt2d_t center, double radius) {
  gce_MakeCirc2d mc(gp_Pnt2d(cast_to_gp(center)), radius);
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return circ2d_t{};
  }
}

circ2d_t make_circ2d_from_center_point(pnt2d_t center, pnt2d_t p) {
  gce_MakeCirc2d mc(gp_Pnt2d(cast_to_gp(center)), gp_Pnt2d(cast_to_gp(center)));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return circ2d_t{};
  }
}

cone_t make_cone_from_axis2(axis2_t a, double ang, double radius) {
  gce_MakeCone mc(cast_to_gp(a), ang, radius);
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return cone_t{};
  }
}

cone_t make_cone_from_cone_point(cone_t a, pnt3d_t p) {
  gce_MakeCone mc(cast_to_gp(a), gp_Pnt(cast_to_gp(p)));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return cone_t{};
  }
}

cone_t make_cone_from_cone_dist(cone_t a, double dist) {
  gce_MakeCone mc(cast_to_gp(a), dist);
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return cone_t{};
  }
}

cone_t make_cone_from_point(pnt3d_t p1, pnt3d_t p2, pnt3d_t p3, pnt3d_t p4) {
  gce_MakeCone mc(gp_Pnt(cast_to_gp(p1)), gp_Pnt(cast_to_gp(p2)),
                  gp_Pnt(cast_to_gp(p3)), gp_Pnt(cast_to_gp(p3)));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return cone_t{};
  }
}

cone_t make_cone_from_axis1_point(axis1_t a, pnt3d_t p1, pnt3d_t p2) {
  gce_MakeCone mc(cast_to_gp(a), gp_Pnt(cast_to_gp(p1)),
                  gp_Pnt(cast_to_gp(p2)));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return cone_t{};
  }
}

cone_t make_cone_from_line_point(line_t l, pnt3d_t p1, pnt3d_t p2) {
  gce_MakeCone mc(cast_to_gp(l), gp_Pnt(cast_to_gp(p1)),
                  gp_Pnt(cast_to_gp(p2)));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return cone_t{};
  }
}

cone_t make_cone_point_radius(pnt3d_t p1, pnt3d_t p2, double r1, double r2) {
  gce_MakeCone mc(gp_Pnt(cast_to_gp(p1)), gp_Pnt(cast_to_gp(p2)), r1, r2);
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return cone_t{};
  }
}

cylinder_t make_cylinder_from_axis2(axis2_t a, double radius) {
  gce_MakeCylinder mc(cast_to_gp(a), radius);
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return cylinder_t{};
  }
}

cylinder_t make_cylinder_from_cylinder_point(cylinder_t a, pnt3d_t p) {
  gce_MakeCylinder mc(cast_to_gp(a), gp_Pnt(cast_to_gp(p)));
  return cast_from_gp(mc.Value());
}

cylinder_t make_cylinder_from_cylinder_dist(cylinder_t a, double dist) {
  gce_MakeCylinder mc(cast_to_gp(a), dist);
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return cylinder_t{};
  }
}

cylinder_t make_cylinder_from_point(pnt3d_t p1, pnt3d_t p2, pnt3d_t p3) {
  gce_MakeCylinder mc(gp_Pnt(cast_to_gp(p1)), gp_Pnt(cast_to_gp(p2)),
                      gp_Pnt(cast_to_gp(p3)));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return cylinder_t{};
  }
}

cylinder_t make_cylinder_from_axis1_radius(axis1_t a, double radius) {
  gce_MakeCylinder mc(cast_to_gp(a), radius);
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return cylinder_t{};
  }
}

cylinder_t make_cylinder_from_circ(circ_t a) {
  gce_MakeCylinder mc(cast_to_gp(a));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return cylinder_t{};
  }
}

elips_t make_elips_from_axis2_radius(axis2_t a, double major_radius,
                                     double minor_radius) {
  gce_MakeElips mc(cast_to_gp(a), major_radius, minor_radius);
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return elips_t{};
  }
}

elips_t make_elips_point(pnt3d_t s1, pnt3d_t s2, pnt3d_t center) {
  gce_MakeElips mc(gp_Pnt(cast_to_gp(s1)), gp_Pnt(cast_to_gp(s2)),
                   gp_Pnt(cast_to_gp(center)));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return elips_t{};
  }
}

elips2d_t make_elips2d_axis2d_radius(axis2d_t a, double major_radius,
                                     double minor_radius) {
  gce_MakeElips2d mc(cast_to_gp(a), major_radius, minor_radius);
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return elips2d_t{};
  }
}

elips2d_t make_elips2d_point(pnt2d_t s1, pnt2d_t s2, pnt2d_t center) {
  gce_MakeElips2d mc(gp_Pnt2d(cast_to_gp(s1)), gp_Pnt2d(cast_to_gp(s2)),
                     gp_Pnt2d(cast_to_gp(center)));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return elips2d_t{};
  }
}

hyperbola_t make_hyperbola_from_axis2(axis2_t a, double major_radius,
                                      double minor_radius) {
  gce_MakeHypr mc(cast_to_gp(a), major_radius, minor_radius);
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return hyperbola_t{};
  }
}

hyperbola_t make_hyperbola_from_point(pnt3d_t s1, pnt3d_t s2, pnt3d_t center) {
  gce_MakeHypr mc(gp_Pnt(cast_to_gp(s1)), gp_Pnt(cast_to_gp(s2)),
                  gp_Pnt(cast_to_gp(center)));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return hyperbola_t{};
  }
}

hyperbola2d_t make_hyperbola2d_from_axis2d(axis2d_t a, double major_radius,
                                           double minor_radius) {
  gce_MakeHypr2d mc(cast_to_gp(a), major_radius, minor_radius);
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return hyperbola2d_t{};
  }
}

hyperbola2d_t make_hyperbola2d_from_point(pnt2d_t s1, pnt2d_t s2,
                                          pnt2d_t center) {
  gce_MakeHypr2d mc(gp_Pnt2d(cast_to_gp(s1)), gp_Pnt2d(cast_to_gp(s2)),
                    gp_Pnt2d(cast_to_gp(center)));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return hyperbola2d_t{};
  }
}

line_t make_line_from_axis1(axis1_t a) {
  gce_MakeLin mc(cast_to_gp(a));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return line_t{};
  }
}

line_t make_line_from_point_dir(pnt3d_t p, dir3d_t v) {
  gce_MakeLin mc(gp_Pnt(cast_to_gp(p)), cast_to_gp(v));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return line_t{};
  }
}

line_t make_line_from_line_point(line_t l, pnt3d_t p) {
  gce_MakeLin mc(cast_to_gp(l), gp_Pnt(cast_to_gp(p)));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return line_t{};
  }
}

line_t make_line_from_point(pnt3d_t p1, pnt3d_t p2) {
  gce_MakeLin mc(gp_Pnt(cast_to_gp(p1)), gp_Pnt(cast_to_gp(p2)));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return line_t{};
  }
}

line2d_t make_line2d_from_axis2d(axis2d_t a) {
  gce_MakeLin2d mc(cast_to_gp(a));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return line2d_t{};
  }
}

line2d_t make_line2d_point_dir(pnt2d_t p, dir2d_t v) {
  gce_MakeLin2d mc(gp_Pnt2d(cast_to_gp(p)), cast_to_gp(v));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return line2d_t{};
  }
}

line2d_t make_line2d_from_line_dist(line2d_t l, double dist) {
  gce_MakeLin2d mc(cast_to_gp(l), dist);
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return line2d_t{};
  }
}

line2d_t make_line2d_line_point(line2d_t l, pnt2d_t p) {
  gce_MakeLin2d mc(cast_to_gp(l), gp_Pnt2d(cast_to_gp(p)));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return line2d_t{};
  }
}

line2d_t make_line2d_from_point(pnt2d_t p1, pnt2d_t p2) {
  gce_MakeLin2d mc(gp_Pnt2d(cast_to_gp(p1)), gp_Pnt2d(cast_to_gp(p2)));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return line2d_t{};
  }
}

trsf_t make_trsf_mirror_from_point(pnt3d_t p) {
  gce_MakeMirror mc(gp_Pnt(cast_to_gp(p)));
  try {
    return trsf_t{cast_from_gp(mc.Value())};
  } catch (...) {
    return trsf_t{};
  }
}

trsf_t make_trsf_mirror_from_axis1(axis1_t a) {
  gce_MakeMirror mc(cast_to_gp(a));
  try {
    return trsf_t{cast_from_gp(mc.Value())};
  } catch (...) {
    return trsf_t{};
  }
}

trsf_t make_trsf_mirror_from_line(line_t a) {
  gce_MakeMirror mc(cast_to_gp(a));
  try {
    return trsf_t{cast_from_gp(mc.Value())};
  } catch (...) {
    return trsf_t{};
  }
}

trsf_t make_trsf_mirror_from_point_dir(pnt3d_t p, dir3d_t v) {
  gce_MakeMirror mc(gp_Pnt(cast_to_gp(p)), cast_to_gp(v));
  try {
    return trsf_t{cast_from_gp(mc.Value())};
  } catch (...) {
    return trsf_t{};
  }
}

trsf_t make_trsf_mirror_from_axis2(axis2_t a) {
  gce_MakeMirror mc(cast_to_gp(a));
  try {
    return trsf_t{cast_from_gp(mc.Value())};
  } catch (...) {
    return trsf_t{};
  }
}

trsf_t make_trsf_mirror_from_plane(plane_t a) {
  gce_MakeMirror mc(cast_to_gp(a));
  try {
    return trsf_t{cast_from_gp(mc.Value())};
  } catch (...) {
    return trsf_t{};
  }
}

trsf_t make_trsf_rotation_from_line(line_t a, double Angle) {
  gce_MakeRotation mc(cast_to_gp(a), Angle);
  try {
    return trsf_t{cast_from_gp(mc.Value())};
  } catch (...) {
    return trsf_t{};
  }
}

trsf_t make_trsf_rotation_from_axis1(axis1_t a, double Angle) {
  gce_MakeRotation mc(cast_to_gp(a), Angle);
  try {
    return trsf_t{cast_from_gp(mc.Value())};
  } catch (...) {
    return trsf_t{};
  }
}

trsf_t make_trsf_rotation_point_dir(pnt3d_t p, dir3d_t v, double Angle) {
  gce_MakeRotation mc(gp_Pnt(cast_to_gp(p)), cast_to_gp(v), Angle);
  try {
    return trsf_t{cast_from_gp(mc.Value())};
  } catch (...) {
    return trsf_t{};
  }
}

trsf_t make_trsf_scale_from_point(pnt3d_t p, double Scale) {
  gce_MakeScale mc(gp_Pnt(cast_to_gp(p)), Scale);
  try {
    return trsf_t{cast_from_gp(mc.Value())};
  } catch (...) {
    return trsf_t{};
  }
}

trsf_t make_trsf_translation_from_vector(vec3d_t v) {
  gce_MakeTranslation mc(gp_Vec(cast_to_gp(v)));
  try {
    return trsf_t{cast_from_gp(mc.Value())};
  } catch (...) {
    return trsf_t{};
  }
}

trsf_t make_trsf_translation_from_point(pnt3d_t p1, pnt3d_t p2) {
  gce_MakeTranslation mc(gp_Pnt(cast_to_gp(p1)), gp_Pnt(cast_to_gp(p2)));
  try {
    return trsf_t{cast_from_gp(mc.Value())};
  } catch (...) {
    return trsf_t{};
  }
}

trsf2d_t make_trsf2d_mirror_from_point(pnt2d_t p) {
  gce_MakeMirror2d mc(gp_Pnt2d(cast_to_gp(p)));
  try {
    return trsf2d_t{cast_from_gp(mc.Value())};
  } catch (...) {
    return trsf2d_t{};
  }
}

trsf2d_t make_trsf2d_mirror_from_axis2d(axis2d_t a) {
  gce_MakeMirror2d mc(cast_to_gp(a));
  try {
    return trsf2d_t{cast_from_gp(mc.Value())};
  } catch (...) {
    return trsf2d_t{};
  }
}

trsf2d_t make_trsf2d_mirror_from_line(line2d_t a) {
  gce_MakeMirror2d mc(cast_to_gp(a));
  try {
    return trsf2d_t{cast_from_gp(mc.Value())};
  } catch (...) {
    return trsf2d_t{};
  }
}

trsf2d_t make_trsf2d_mirror_from_point_dir(pnt2d_t p, dir2d_t v) {
  gce_MakeMirror2d mc(gp_Pnt2d(cast_to_gp(p)), cast_to_gp(v));
  try {
    return trsf2d_t{cast_from_gp(mc.Value())};
  } catch (...) {
    return trsf2d_t{};
  }
}

trsf2d_t make_trsf2d_rotation_from_point(pnt2d_t p, double Angle) {
  gce_MakeRotation2d mc(gp_Pnt2d(cast_to_gp(p)), Angle);
  try {
    return trsf2d_t{cast_from_gp(mc.Value())};
  } catch (...) {
    return trsf2d_t{};
  }
}

trsf2d_t make_trsf2d_scale_from_point(pnt2d_t p, double Scale) {
  gce_MakeScale2d mc(gp_Pnt2d(cast_to_gp(p)), Scale);
  try {
    return trsf2d_t{cast_from_gp(mc.Value())};
  } catch (...) {
    return trsf2d_t{};
  }
}

trsf2d_t make_trsf2d_translation_from_vector(vec2d_t v) {
  gce_MakeTranslation2d mc(gp_Vec2d(cast_to_gp(v)));
  try {
    return trsf2d_t{cast_from_gp(mc.Value())};
  } catch (...) {
    return trsf2d_t{};
  }
}

trsf2d_t make_trsf2d_translation_from_point(pnt2d_t p1, pnt2d_t p2) {
  gce_MakeTranslation2d mc(gp_Pnt2d(cast_to_gp(p1)), gp_Pnt2d(cast_to_gp(p2)));
  try {
    return trsf2d_t{cast_from_gp(mc.Value())};
  } catch (...) {
    return trsf2d_t{};
  }
}

parabola_t make_parabola_from_axis2(axis2_t a, double Focal) {
  gce_MakeParab mc(cast_to_gp(a), Focal);
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return parabola_t{};
  }
}

parabola_t make_parabola_from_axis1(axis1_t a, pnt3d_t v) {
  gce_MakeParab mc(cast_to_gp(a), gp_Pnt(cast_to_gp(v)));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return parabola_t{};
  }
}

parabola2d_t make_parabola2d_from_axis2d(axis2d_t a, double Focal) {
  gce_MakeParab2d mc(cast_to_gp(a), Focal);
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return parabola2d_t{};
  }
}

parabola2d_t make_parabola2d_from_axis22d(axis22d_t a, double Focal) {
  gce_MakeParab2d mc(cast_to_gp(a), Focal);
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return parabola2d_t{};
  }
}

parabola2d_t make_parabola2d_from_axis2d_point(axis2d_t a, pnt2d_t F) {
  gce_MakeParab2d mc(cast_to_gp(a), gp_Pnt2d(cast_to_gp(F)));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return parabola2d_t{};
  }
}

parabola2d_t make_parabola2d_point(pnt2d_t S1, pnt2d_t center) {
  gce_MakeParab2d mc(gp_Pnt2d(cast_to_gp(S1)), gp_Pnt2d(cast_to_gp(center)));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return parabola2d_t{};
  }
}

plane_t make_plane_from_axis2(axis2_t a) {
  gce_MakePln mc(cast_to_gp(a));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return plane_t{};
  }
}

plane_t make_plane_from_point_dir(pnt3d_t p, dir3d_t v) {
  gce_MakePln mc(gp_Pnt(cast_to_gp(p)), cast_to_gp(v));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return plane_t{};
  }
}

plane_t make_plane_from_lrud(double a, double b, double c, double d) {
  gce_MakePln mc(a, b, c, d);
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return plane_t{};
  }
}

plane_t make_plane_from_plane_point(plane_t pln, pnt3d_t p) {
  gce_MakePln mc(cast_to_gp(pln), gp_Pnt(cast_to_gp(p)));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return plane_t{};
  }
}

plane_t make_plane_from_plane_dist(plane_t pln, double dist) {
  gce_MakePln mc(cast_to_gp(pln), dist);
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return plane_t{};
  }
}

plane_t make_plane_from_point(pnt3d_t p1, pnt3d_t p2, pnt3d_t p3) {
  gce_MakePln mc(gp_Pnt(cast_to_gp(p1)), gp_Pnt(cast_to_gp(p2)),
                 gp_Pnt(cast_to_gp(p3)));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return plane_t{};
  }
}

plane_t make_plane_from_two_point(pnt3d_t p1, pnt3d_t p2) {
  gce_MakePln mc(gp_Pnt(cast_to_gp(p1)), gp_Pnt(cast_to_gp(p2)));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return plane_t{};
  }
}

plane_t make_plane_from_axis1(axis1_t a) {
  gce_MakePln mc(cast_to_gp(a));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return plane_t{};
  }
}

sphere_t make_sphere_from_axis3(axis3_t a, double radius) {
  return cast_from_gp(gp_Sphere(cast_to_gp(a), radius));
}

torus_t make_torus_from_axis3(axis3_t a, double major_radius,
                              double minor_radius) {
  return cast_from_gp(gp_Torus(cast_to_gp(a), major_radius, minor_radius));
}

torus_t make_torus_from_elips(elips_t el) {
  return make_torus_from_axis3(make_axis3(el.a2), el.major_radius,
                               el.minor_radius);
}

#ifdef __cplusplus
}
#endif
