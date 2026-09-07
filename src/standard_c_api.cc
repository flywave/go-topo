#include "standard_c_api.h"
#include "cgo_lock.hh"
#include "standard_impl.hh"

#ifdef __cplusplus
extern "C" {
#endif

dir3d_t make_dir(vec3d_t p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeDir md(cast_to_gp(p));
  try {
    return cast_from_gp(md.Value());
  } catch (...) {
    return dir3d_t{};
  }
}

dir3d_t make_dir_from_xyz(double x, double y, double z) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeDir md(x, y, z);
  try {
    return cast_from_gp(md.Value());
  } catch (...) {
    return dir3d_t{};
  }
}

dir3d_t make_dir_from_point(pnt3d_t p1, pnt3d_t p2) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeDir md(gp_Pnt(cast_to_gp(p1)), gp_Pnt(cast_to_gp(p2)));
  try {
    return cast_from_gp(md.Value());
  } catch (...) {
    return dir3d_t{};
  }
}

dir2d_t make_dir2d(vec2d_t p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeDir2d md(cast_to_gp(p));
  try {
    return cast_from_gp(md.Value());
  } catch (...) {
    return dir2d_t{};
  }
}

dir2d_t make_dir2d_from_xy(double x, double y) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeDir2d md(x, y);
  try {
    return cast_from_gp(md.Value());
  } catch (...) {
    return dir2d_t{};
  }
}

dir2d_t make_dir2d_from_point(pnt2d_t p1, pnt2d_t p2) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeDir2d md(gp_Pnt2d(cast_to_gp(p1)), gp_Pnt2d(cast_to_gp(p2)));
  try {
    return cast_from_gp(md.Value());
  } catch (...) {
    return dir2d_t{};
  }
}

axis1_t make_axis(pnt3d_t p, dir3d_t v) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  gp_Ax1 ax1{cast_to_gp(p), cast_to_gp(v)};
  return cast_from_gp(ax1);
  }
  catch (const std::exception &e) {
    (void)e;
    return axis1_t{};
  }
  catch (...) {
    return axis1_t{};
  }
}

axis2_t make_axis2_from_nvx(pnt3d_t p, dir3d_t N, dir3d_t Vx) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  gp_Ax2 ax2{gp_Pnt(cast_to_gp(p)), cast_to_gp(N), cast_to_gp(Vx)};
  return cast_from_gp(ax2);
  }
  catch (const std::exception &e) {
    (void)e;
    return axis2_t{};
  }
  catch (...) {
    return axis2_t{};
  }
}

axis2_t make_axis2(pnt3d_t p, dir3d_t v) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  gp_Ax2 ax2{gp_Pnt(cast_to_gp(p)), cast_to_gp(v)};
  return cast_from_gp(ax2);
  }
  catch (const std::exception &e) {
    (void)e;
    return axis2_t{};
  }
  catch (...) {
    return axis2_t{};
  }
}

axis3_t make_axis3(axis2_t a) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  gp_Ax3 ax3{cast_to_gp(a)};
  return cast_from_gp(ax3);
  }
  catch (const std::exception &e) {
    (void)e;
    return axis3_t{};
  }
  catch (...) {
    return axis3_t{};
  }
}

axis3_t make_axis3_from_nvx(pnt3d_t p, dir3d_t N, dir3d_t Vx) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  gp_Ax3 ax3{gp_Pnt(cast_to_gp(p)), cast_to_gp(N), cast_to_gp(Vx)};
  return cast_from_gp(ax3);
  }
  catch (const std::exception &e) {
    (void)e;
    return axis3_t{};
  }
  catch (...) {
    return axis3_t{};
  }
}

axis3_t make_axis3_from_v(pnt3d_t p, dir3d_t v) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  gp_Ax3 ax3{gp_Pnt(cast_to_gp(p)), cast_to_gp(v)};
  return cast_from_gp(ax3);
  }
  catch (const std::exception &e) {
    (void)e;
    return axis3_t{};
  }
  catch (...) {
    return axis3_t{};
  }
}

axis2d_t make_axis2d(pnt2d_t p, dir2d_t v) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  gp_Ax2d ax2{gp_Pnt2d(cast_to_gp(p)), cast_to_gp(v)};
  return cast_from_gp(ax2);
  }
  catch (const std::exception &e) {
    (void)e;
    return axis2d_t{};
  }
  catch (...) {
    return axis2d_t{};
  }
}

axis22d_t make_axis22d(axis2d_t a) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  gp_Ax22d ax2{cast_to_gp(a)};
  return cast_from_gp(ax2);
  }
  catch (const std::exception &e) {
    (void)e;
    return axis22d_t{};
  }
  catch (...) {
    return axis22d_t{};
  }
}

axis22d_t make_axis22d_from_v(pnt2d_t p, dir2d_t v) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  gp_Ax22d ax2{gp_Pnt2d(cast_to_gp(p)), cast_to_gp(v)};
  return cast_from_gp(ax2);
  }
  catch (const std::exception &e) {
    (void)e;
    return axis22d_t{};
  }
  catch (...) {
    return axis22d_t{};
  }
}

axis22d_t make_axis22d_from_vxy(pnt2d_t p, dir2d_t vx, dir2d_t vy) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  gp_Ax22d ax2{gp_Pnt2d(cast_to_gp(p)), cast_to_gp(vx), cast_to_gp(vy)};
  return cast_from_gp(ax2);
  }
  catch (const std::exception &e) {
    (void)e;
    return axis22d_t{};
  }
  catch (...) {
    return axis22d_t{};
  }
}

circ_t make_circ_from_axis2(axis2_t a, double radius) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeCirc mc(cast_to_gp(a), radius);
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return circ_t{};
  }
}

circ_t make_circ_from_circ_dist(circ_t a, double Dist) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeCirc mc(cast_to_gp(a), Dist);
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return circ_t{};
  }
}

circ_t make_circ_from_circ_point(circ_t a, pnt3d_t p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeCirc mc(cast_to_gp(a), cast_to_gp(p));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return circ_t{};
  }
}

circ_t make_circ_from_point(pnt3d_t p1, pnt3d_t p2, pnt3d_t p3) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeCirc mc(gp_Pnt(cast_to_gp(p1)), gp_Pnt(cast_to_gp(p2)),
                  gp_Pnt(cast_to_gp(p3)));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return circ_t{};
  }
}

circ_t make_circ_from_center_norm(pnt3d_t center, dir3d_t Norm, double radius) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeCirc mc(gp_Pnt(cast_to_gp(center)), gp_Dir(cast_to_gp(Norm)), radius);
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return circ_t{};
  }
}

circ_t make_circ_from_center_plan(pnt3d_t center, plane_t pl, double radius) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeCirc mc(gp_Pnt(cast_to_gp(center)), cast_to_gp(pl), radius);
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return circ_t{};
  }
}

circ_t make_circ_from_axis1(axis1_t a, double radius) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeCirc mc(cast_to_gp(a), radius);
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return circ_t{};
  }
}

circ2d_t make_circ2d_from_axis2(axis2d_t a, double radius) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeCirc2d mc(cast_to_gp(a), radius);
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return circ2d_t{};
  }
}

circ2d_t make_circ2d_from_axis22d(axis22d_t a, double radius) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeCirc2d mc(cast_to_gp(a), radius);
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return circ2d_t{};
  }
}

circ2d_t make_circ2d_from_circ_dist(circ2d_t a, double Dist) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeCirc2d mc(cast_to_gp(a), Dist);
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return circ2d_t{};
  }
}

circ2d_t make_circ2d_from_circ2d(circ2d_t a, pnt2d_t p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeCirc2d mc(cast_to_gp(a), gp_Pnt2d(cast_to_gp(p)));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return circ2d_t{};
  }
}

circ2d_t make_circ2d_from_point(pnt2d_t p1, pnt2d_t p2, pnt2d_t p3) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeCirc2d mc(gp_Pnt2d(cast_to_gp(p1)), gp_Pnt2d(cast_to_gp(p2)),
                    gp_Pnt2d(cast_to_gp(p3)));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return circ2d_t{};
  }
}

circ2d_t make_circ2d_from_center_radius(pnt2d_t center, double radius) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeCirc2d mc(gp_Pnt2d(cast_to_gp(center)), radius);
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return circ2d_t{};
  }
}

circ2d_t make_circ2d_from_center_point(pnt2d_t center, pnt2d_t p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeCirc2d mc(gp_Pnt2d(cast_to_gp(center)), gp_Pnt2d(cast_to_gp(center)));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return circ2d_t{};
  }
}

cone_t make_cone_from_axis2(axis2_t a, double ang, double radius) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeCone mc(cast_to_gp(a), ang, radius);
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return cone_t{};
  }
}

cone_t make_cone_from_cone_point(cone_t a, pnt3d_t p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeCone mc(cast_to_gp(a), gp_Pnt(cast_to_gp(p)));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return cone_t{};
  }
}

cone_t make_cone_from_cone_dist(cone_t a, double dist) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeCone mc(cast_to_gp(a), dist);
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return cone_t{};
  }
}

cone_t make_cone_from_point(pnt3d_t p1, pnt3d_t p2, pnt3d_t p3, pnt3d_t p4) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeCone mc(gp_Pnt(cast_to_gp(p1)), gp_Pnt(cast_to_gp(p2)),
                  gp_Pnt(cast_to_gp(p3)), gp_Pnt(cast_to_gp(p3)));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return cone_t{};
  }
}

cone_t make_cone_from_axis1_point(axis1_t a, pnt3d_t p1, pnt3d_t p2) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeCone mc(cast_to_gp(a), gp_Pnt(cast_to_gp(p1)),
                  gp_Pnt(cast_to_gp(p2)));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return cone_t{};
  }
}

cone_t make_cone_from_line_point(line_t l, pnt3d_t p1, pnt3d_t p2) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeCone mc(cast_to_gp(l), gp_Pnt(cast_to_gp(p1)),
                  gp_Pnt(cast_to_gp(p2)));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return cone_t{};
  }
}

cone_t make_cone_point_radius(pnt3d_t p1, pnt3d_t p2, double r1, double r2) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeCone mc(gp_Pnt(cast_to_gp(p1)), gp_Pnt(cast_to_gp(p2)), r1, r2);
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return cone_t{};
  }
}

cylinder_t make_cylinder_from_axis2(axis2_t a, double radius) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeCylinder mc(cast_to_gp(a), radius);
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return cylinder_t{};
  }
}

cylinder_t make_cylinder_from_cylinder_point(cylinder_t a, pnt3d_t p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  gce_MakeCylinder mc(cast_to_gp(a), gp_Pnt(cast_to_gp(p)));
  return cast_from_gp(mc.Value());
  }
  catch (const std::exception &e) {
    (void)e;
    return cylinder_t{};
  }
  catch (...) {
    return cylinder_t{};
  }
}

cylinder_t make_cylinder_from_cylinder_dist(cylinder_t a, double dist) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeCylinder mc(cast_to_gp(a), dist);
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return cylinder_t{};
  }
}

cylinder_t make_cylinder_from_point(pnt3d_t p1, pnt3d_t p2, pnt3d_t p3) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeCylinder mc(gp_Pnt(cast_to_gp(p1)), gp_Pnt(cast_to_gp(p2)),
                      gp_Pnt(cast_to_gp(p3)));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return cylinder_t{};
  }
}

cylinder_t make_cylinder_from_axis1_radius(axis1_t a, double radius) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeCylinder mc(cast_to_gp(a), radius);
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return cylinder_t{};
  }
}

cylinder_t make_cylinder_from_circ(circ_t a) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeCylinder mc(cast_to_gp(a));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return cylinder_t{};
  }
}

elips_t make_elips_from_axis2_radius(axis2_t a, double major_radius,
                                     double minor_radius) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeElips mc(cast_to_gp(a), major_radius, minor_radius);
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return elips_t{};
  }
}

elips_t make_elips_point(pnt3d_t s1, pnt3d_t s2, pnt3d_t center) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
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
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeElips2d mc(cast_to_gp(a), major_radius, minor_radius);
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return elips2d_t{};
  }
}

elips2d_t make_elips2d_point(pnt2d_t s1, pnt2d_t s2, pnt2d_t center) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
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
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeHypr mc(cast_to_gp(a), major_radius, minor_radius);
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return hyperbola_t{};
  }
}

hyperbola_t make_hyperbola_from_point(pnt3d_t s1, pnt3d_t s2, pnt3d_t center) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
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
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeHypr2d mc(cast_to_gp(a), major_radius, minor_radius);
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return hyperbola2d_t{};
  }
}

hyperbola2d_t make_hyperbola2d_from_point(pnt2d_t s1, pnt2d_t s2,
                                          pnt2d_t center) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeHypr2d mc(gp_Pnt2d(cast_to_gp(s1)), gp_Pnt2d(cast_to_gp(s2)),
                    gp_Pnt2d(cast_to_gp(center)));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return hyperbola2d_t{};
  }
}

line_t make_line_from_axis1(axis1_t a) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeLin mc(cast_to_gp(a));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return line_t{};
  }
}

line_t make_line_from_point_dir(pnt3d_t p, dir3d_t v) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeLin mc(gp_Pnt(cast_to_gp(p)), cast_to_gp(v));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return line_t{};
  }
}

line_t make_line_from_line_point(line_t l, pnt3d_t p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeLin mc(cast_to_gp(l), gp_Pnt(cast_to_gp(p)));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return line_t{};
  }
}

line_t make_line_from_point(pnt3d_t p1, pnt3d_t p2) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeLin mc(gp_Pnt(cast_to_gp(p1)), gp_Pnt(cast_to_gp(p2)));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return line_t{};
  }
}

line2d_t make_line2d_from_axis2d(axis2d_t a) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeLin2d mc(cast_to_gp(a));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return line2d_t{};
  }
}

line2d_t make_line2d_point_dir(pnt2d_t p, dir2d_t v) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeLin2d mc(gp_Pnt2d(cast_to_gp(p)), cast_to_gp(v));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return line2d_t{};
  }
}

line2d_t make_line2d_from_line_dist(line2d_t l, double dist) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeLin2d mc(cast_to_gp(l), dist);
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return line2d_t{};
  }
}

line2d_t make_line2d_line_point(line2d_t l, pnt2d_t p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeLin2d mc(cast_to_gp(l), gp_Pnt2d(cast_to_gp(p)));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return line2d_t{};
  }
}

line2d_t make_line2d_from_point(pnt2d_t p1, pnt2d_t p2) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeLin2d mc(gp_Pnt2d(cast_to_gp(p1)), gp_Pnt2d(cast_to_gp(p2)));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return line2d_t{};
  }
}

trsf_t make_trsf_mirror_from_point(pnt3d_t p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeMirror mc(gp_Pnt(cast_to_gp(p)));
  try {
    return trsf_t{cast_from_gp(mc.Value())};
  } catch (...) {
    return trsf_t{};
  }
}

trsf_t make_trsf_mirror_from_axis1(axis1_t a) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeMirror mc(cast_to_gp(a));
  try {
    return trsf_t{cast_from_gp(mc.Value())};
  } catch (...) {
    return trsf_t{};
  }
}

trsf_t make_trsf_mirror_from_line(line_t a) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeMirror mc(cast_to_gp(a));
  try {
    return trsf_t{cast_from_gp(mc.Value())};
  } catch (...) {
    return trsf_t{};
  }
}

trsf_t make_trsf_mirror_from_point_dir(pnt3d_t p, dir3d_t v) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeMirror mc(gp_Pnt(cast_to_gp(p)), cast_to_gp(v));
  try {
    return trsf_t{cast_from_gp(mc.Value())};
  } catch (...) {
    return trsf_t{};
  }
}

trsf_t make_trsf_mirror_from_axis2(axis2_t a) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeMirror mc(cast_to_gp(a));
  try {
    return trsf_t{cast_from_gp(mc.Value())};
  } catch (...) {
    return trsf_t{};
  }
}

trsf_t make_trsf_mirror_from_plane(plane_t a) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeMirror mc(cast_to_gp(a));
  try {
    return trsf_t{cast_from_gp(mc.Value())};
  } catch (...) {
    return trsf_t{};
  }
}

trsf_t make_trsf_rotation_from_line(line_t a, double Angle) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeRotation mc(cast_to_gp(a), Angle);
  try {
    return trsf_t{cast_from_gp(mc.Value())};
  } catch (...) {
    return trsf_t{};
  }
}

trsf_t make_trsf_rotation_from_axis1(axis1_t a, double Angle) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeRotation mc(cast_to_gp(a), Angle);
  try {
    return trsf_t{cast_from_gp(mc.Value())};
  } catch (...) {
    return trsf_t{};
  }
}

trsf_t make_trsf_rotation_point_dir(pnt3d_t p, dir3d_t v, double Angle) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeRotation mc(gp_Pnt(cast_to_gp(p)), cast_to_gp(v), Angle);
  try {
    return trsf_t{cast_from_gp(mc.Value())};
  } catch (...) {
    return trsf_t{};
  }
}

trsf_t make_trsf_scale_from_point(pnt3d_t p, double Scale) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeScale mc(gp_Pnt(cast_to_gp(p)), Scale);
  try {
    return trsf_t{cast_from_gp(mc.Value())};
  } catch (...) {
    return trsf_t{};
  }
}

trsf_t make_trsf_translation_from_vector(vec3d_t v) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeTranslation mc(gp_Vec(cast_to_gp(v)));
  try {
    return trsf_t{cast_from_gp(mc.Value())};
  } catch (...) {
    return trsf_t{};
  }
}

trsf_t make_trsf_translation_from_point(pnt3d_t p1, pnt3d_t p2) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeTranslation mc(gp_Pnt(cast_to_gp(p1)), gp_Pnt(cast_to_gp(p2)));
  try {
    return trsf_t{cast_from_gp(mc.Value())};
  } catch (...) {
    return trsf_t{};
  }
}

trsf2d_t make_trsf2d_mirror_from_point(pnt2d_t p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeMirror2d mc(gp_Pnt2d(cast_to_gp(p)));
  try {
    return trsf2d_t{cast_from_gp(mc.Value())};
  } catch (...) {
    return trsf2d_t{};
  }
}

trsf2d_t make_trsf2d_mirror_from_axis2d(axis2d_t a) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeMirror2d mc(cast_to_gp(a));
  try {
    return trsf2d_t{cast_from_gp(mc.Value())};
  } catch (...) {
    return trsf2d_t{};
  }
}

trsf2d_t make_trsf2d_mirror_from_line(line2d_t a) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeMirror2d mc(cast_to_gp(a));
  try {
    return trsf2d_t{cast_from_gp(mc.Value())};
  } catch (...) {
    return trsf2d_t{};
  }
}

trsf2d_t make_trsf2d_mirror_from_point_dir(pnt2d_t p, dir2d_t v) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeMirror2d mc(gp_Pnt2d(cast_to_gp(p)), cast_to_gp(v));
  try {
    return trsf2d_t{cast_from_gp(mc.Value())};
  } catch (...) {
    return trsf2d_t{};
  }
}

trsf2d_t make_trsf2d_rotation_from_point(pnt2d_t p, double Angle) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeRotation2d mc(gp_Pnt2d(cast_to_gp(p)), Angle);
  try {
    return trsf2d_t{cast_from_gp(mc.Value())};
  } catch (...) {
    return trsf2d_t{};
  }
}

trsf2d_t make_trsf2d_scale_from_point(pnt2d_t p, double Scale) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeScale2d mc(gp_Pnt2d(cast_to_gp(p)), Scale);
  try {
    return trsf2d_t{cast_from_gp(mc.Value())};
  } catch (...) {
    return trsf2d_t{};
  }
}

trsf2d_t make_trsf2d_translation_from_vector(vec2d_t v) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeTranslation2d mc(gp_Vec2d(cast_to_gp(v)));
  try {
    return trsf2d_t{cast_from_gp(mc.Value())};
  } catch (...) {
    return trsf2d_t{};
  }
}

trsf2d_t make_trsf2d_translation_from_point(pnt2d_t p1, pnt2d_t p2) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeTranslation2d mc(gp_Pnt2d(cast_to_gp(p1)), gp_Pnt2d(cast_to_gp(p2)));
  try {
    return trsf2d_t{cast_from_gp(mc.Value())};
  } catch (...) {
    return trsf2d_t{};
  }
}

parabola_t make_parabola_from_axis2(axis2_t a, double Focal) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeParab mc(cast_to_gp(a), Focal);
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return parabola_t{};
  }
}

parabola_t make_parabola_from_axis1(axis1_t a, pnt3d_t v) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeParab mc(cast_to_gp(a), gp_Pnt(cast_to_gp(v)));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return parabola_t{};
  }
}

parabola2d_t make_parabola2d_from_axis2d(axis2d_t a, double Focal) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeParab2d mc(cast_to_gp(a), Focal);
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return parabola2d_t{};
  }
}

parabola2d_t make_parabola2d_from_axis22d(axis22d_t a, double Focal) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeParab2d mc(cast_to_gp(a), Focal);
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return parabola2d_t{};
  }
}

parabola2d_t make_parabola2d_from_axis2d_point(axis2d_t a, pnt2d_t F) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeParab2d mc(cast_to_gp(a), gp_Pnt2d(cast_to_gp(F)));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return parabola2d_t{};
  }
}

parabola2d_t make_parabola2d_point(pnt2d_t S1, pnt2d_t center) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakeParab2d mc(gp_Pnt2d(cast_to_gp(S1)), gp_Pnt2d(cast_to_gp(center)));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return parabola2d_t{};
  }
}

plane_t make_plane_from_axis2(axis2_t a) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakePln mc(cast_to_gp(a));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return plane_t{};
  }
}

plane_t make_plane_from_point_dir(pnt3d_t p, dir3d_t v) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakePln mc(gp_Pnt(cast_to_gp(p)), cast_to_gp(v));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return plane_t{};
  }
}

plane_t make_plane_from_lrud(double a, double b, double c, double d) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakePln mc(a, b, c, d);
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return plane_t{};
  }
}

plane_t make_plane_from_plane_point(plane_t pln, pnt3d_t p) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakePln mc(cast_to_gp(pln), gp_Pnt(cast_to_gp(p)));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return plane_t{};
  }
}

plane_t make_plane_from_plane_dist(plane_t pln, double dist) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakePln mc(cast_to_gp(pln), dist);
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return plane_t{};
  }
}

plane_t make_plane_from_point(pnt3d_t p1, pnt3d_t p2, pnt3d_t p3) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakePln mc(gp_Pnt(cast_to_gp(p1)), gp_Pnt(cast_to_gp(p2)),
                 gp_Pnt(cast_to_gp(p3)));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return plane_t{};
  }
}

plane_t make_plane_from_two_point(pnt3d_t p1, pnt3d_t p2) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakePln mc(gp_Pnt(cast_to_gp(p1)), gp_Pnt(cast_to_gp(p2)));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return plane_t{};
  }
}

plane_t make_plane_from_axis1(axis1_t a) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock());
  gce_MakePln mc(cast_to_gp(a));
  try {
    return cast_from_gp(mc.Value());
  } catch (...) {
    return plane_t{};
  }
}

sphere_t make_sphere_from_axis3(axis3_t a, double radius) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return cast_from_gp(gp_Sphere(cast_to_gp(a), radius));
  }
  catch (const std::exception &e) {
    (void)e;
    return sphere_t{};
  }
  catch (...) {
    return sphere_t{};
  }
}

torus_t make_torus_from_axis3(axis3_t a, double major_radius,
                              double minor_radius) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return cast_from_gp(gp_Torus(cast_to_gp(a), major_radius, minor_radius));
  }
  catch (const std::exception &e) {
    (void)e;
    return torus_t{};
  }
  catch (...) {
    return torus_t{};
  }
}

torus_t make_torus_from_elips(elips_t el) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return make_torus_from_axis3(make_axis3(el.a2), el.major_radius,
                               el.minor_radius);
  }
  catch (const std::exception &e) {
    (void)e;
    return torus_t{};
  }
  catch (...) {
    return torus_t{};
  }
}

#ifdef __cplusplus
}
#endif
