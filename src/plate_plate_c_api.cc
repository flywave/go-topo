#include "plate_plate_c_api.h"
#include "plate_plate_impl.hh"
#include "standard_impl.hh"

inline Plate_D1 cast_to_pp(const plate_d1_t &p) {
  return Plate_D1(cast_to_gp(p.du), cast_to_gp(p.dv));
}

inline Plate_D2 cast_to_pp(const plate_d2_t &p) {
  return Plate_D2(cast_to_gp(p.duu), cast_to_gp(p.duv), cast_to_gp(p.dvv));
}

inline Plate_D3 cast_to_pp(const plate_d3_t &p) {
  return Plate_D3(cast_to_gp(p.duuu), cast_to_gp(p.duuv), cast_to_gp(p.duvv),
                  cast_to_gp(p.dvvv));
}

#ifdef __cplusplus
extern "C" {
#endif

plate_plate_t *plate_plate_new() { return new plate_plate_t{}; }

void plate_plate_free(plate_plate_t *p) {
  if (p) {
    delete p;
  }
}

void plate_plate_load_plate_pinpoint_constraint(
    plate_plate_t *pp, plate_pinpoint_constraint_t *p) {
  if (pp && p) {
    pp->pp.Load(p->pc);
  }
}

void plate_plate_load_plate_linear_xyz_constraint(
    plate_plate_t *pp, plate_linear_xyz_constraint_t *p) {
  if (pp && p) {
    pp->pp.Load(p->pc);
  }
}

void plate_plate_load_plate_linear_scalar_constraint(
    plate_plate_t *pp, plate_linear_scalar_constraint_t *p) {
  if (pp && p) {
    pp->pp.Load(p->pc);
  }
}

void plate_plate_load_plate_global_translation_constraint(
    plate_plate_t *pp, plate_global_translation_constraint_t *p) {
  if (pp && p) {
    pp->pp.Load(p->pc);
  }
}

void plate_plate_load_plate_line_constraint(plate_plate_t *pp,
                                            plate_line_constraint_t *p) {
  if (pp && p) {
    pp->pp.Load(p->pc);
  }
}

void plate_plate_load_plate_plane_constraint(plate_plate_t *pp,
                                             plate_plane_constraint_t *p) {
  if (pp && p) {
    pp->pp.Load(p->pc);
  }
}

void plate_plate_load_plate_sampled_curve_constraint(
    plate_plate_t *pp, plate_sampled_curve_constraint_t *p) {
  if (pp && p) {
    pp->pp.Load(p->pc);
  }
}

void plate_plate_load_plate_g_to_c_constraint(plate_plate_t *pp,
                                              plate_g_to_c_constraint_t *p) {
  if (pp && p) {
    pp->pp.Load(p->pc);
  }
}

void plate_plate_load_plate_free_g_to_c_constraint(
    plate_plate_t *pp, plate_free_g_to_c_constraint_t *p) {
  if (pp && p) {
    pp->pp.Load(p->pc);
  }
}

void plate_plate_solveti(plate_plate_t *pp, int ord, double anisotropie) {
  if (pp) {
    pp->pp.SolveTI(ord, anisotropie);
  }
}

plate_pinpoint_constraint_t *plate_pinpoint_constraint_new(xy_t point2d,
                                                           xyz_t ImposedValue,
                                                           int iu, int iv) {
  return new plate_pinpoint_constraint_t{
      {cast_to_gp(point2d), cast_to_gp(ImposedValue), iu, iv}};
}

void plate_pinpoint_constraint_free(plate_pinpoint_constraint_t *p) {
  if (p) {
    delete p;
  }
}

plate_linear_xyz_constraint_t *
plate_linear_xyz_constraint_new_1dim(plate_pinpoint_constraint_t **ppc,
                                     int ppccount, double *coffe,
                                     int coffecount) {
  Plate_Array1OfPinpointConstraint cons(ppccount, ppccount);
  for (int i = 0; i < ppccount; i++) {
    cons.SetValue(i, ppc[i]->pc);
  }
  TColStd_Array1OfReal coffes(coffecount, coffecount);
  for (int i = 0; i < coffecount; i++) {
    coffes.SetValue(i, coffe[i]);
  }
  return new plate_linear_xyz_constraint_t{{cons, coffes}};
}

plate_linear_xyz_constraint_t *
plate_linear_xyz_constraint_new_2dim(plate_pinpoint_constraint_t **ppc,
                                     int ppccount, double *coffe, int cofferow,
                                     int coffecol) {
  Plate_Array1OfPinpointConstraint cons(ppccount, ppccount);
  for (int i = 0; i < ppccount; i++) {
    cons.SetValue(i, ppc[i]->pc);
  }
  TColStd_Array2OfReal coffes(cofferow, cofferow, coffecol, coffecol);

  for (int i = 0; i < cofferow; i++) {
    for (int j = 0; j < coffecol; j++) {
      coffes.SetValue(i, j, coffe[i * coffecol + j]);
    }
  }
  return new plate_linear_xyz_constraint_t{{cons, coffes}};
}

void plate_linear_xyz_constraint_free(plate_linear_xyz_constraint_t *p) {
  if (p) {
    delete p;
  }
}

plate_linear_scalar_constraint_t *
plate_linear_scalar_constraint_new(plate_pinpoint_constraint_t *ppc,
                                   xyz_t coffe) {
  return new plate_linear_scalar_constraint_t{{ppc->pc, cast_to_gp(coffe)}};
}

plate_linear_scalar_constraint_t *
plate_linear_scalar_constraint_new_1dim(plate_pinpoint_constraint_t **ppc,
                                        int ppccount, xyz_t *coffe,
                                        int coffecount) {
  Plate_Array1OfPinpointConstraint cons(ppccount, ppccount);
  for (int i = 0; i < ppccount; i++) {
    cons.SetValue(i, ppc[i]->pc);
  }
  TColgp_Array1OfXYZ coffes(coffecount, coffecount);
  for (int i = 0; i < coffecount; i++) {
    coffes.SetValue(i, cast_to_gp(coffe[i]));
  }
  return new plate_linear_scalar_constraint_t{{cons, coffes}};
}

plate_linear_scalar_constraint_t *
plate_linear_scalar_constraint_new_2dim(plate_pinpoint_constraint_t **ppc,
                                        int ppccount, xyz_t *coffe,
                                        int cofferow, int coffecol) {
  Plate_Array1OfPinpointConstraint cons(ppccount, ppccount);
  for (int i = 0; i < ppccount; i++) {
    cons.SetValue(i, ppc[i]->pc);
  }
  TColgp_Array2OfXYZ coffes(cofferow, cofferow, coffecol, coffecol);

  for (int i = 0; i < cofferow; i++) {
    for (int j = 0; j < coffecol; j++) {
      coffes.SetValue(i, j, cast_to_gp(coffe[i * coffecol + j]));
    }
  }
  return new plate_linear_scalar_constraint_t{{cons, coffes}};
}

void plate_linear_scalar_constraint_free(plate_linear_scalar_constraint_t *p) {
  if (p) {
    delete p;
  }
}

plate_global_translation_constraint_t *
plate_global_translation_constraint_new(xy_t *coffe, int coffecount) {
  TColgp_SequenceOfXY SOfXY;
  for (int i = 0; i < coffecount; i++) {
    SOfXY.Append(cast_to_gp(coffe[i]));
  }
  return new plate_global_translation_constraint_t{{SOfXY}};
}

void plate_global_translation_constraint_free(
    plate_global_translation_constraint_t *p) {
  if (p) {
    delete p;
  }
}

plate_line_constraint_t *plate_line_constraint_new(xy_t point2d, line_t l,
                                                   int iu, int iv) {
  return new plate_line_constraint_t{
      {cast_to_gp(point2d), cast_to_gp(l), iu, iv}};
}

void plate_line_constraint_free(plate_line_constraint_t *p) {
  if (p) {
    delete p;
  }
}

plate_plane_constraint_t *plate_plane_constraint_new(xy_t point2d, plane_t l,
                                                     int iu, int iv) {
  return new plate_plane_constraint_t{
      {cast_to_gp(point2d), cast_to_gp(l), iu, iv}};
}

void plate_plane_constraint_free(plate_plane_constraint_t *p) {
  if (p) {
    delete p;
  }
}

plate_sampled_curve_constraint_t *
plate_sampled_curve_constraint_new(plate_pinpoint_constraint_t **ppc,
                                   int count) {
  Plate_SequenceOfPinpointConstraint cons;
  for (int i = 0; i < count; i++) {
    cons.Append(ppc[i]->pc);
  }
  return new plate_sampled_curve_constraint_t{{cons, count}};
}

void plate_sampled_curve_constraint_free(plate_sampled_curve_constraint_t *p) {
  if (p) {
    delete p;
  }
}

plate_g_to_c_constraint_t *
plate_g_to_c_constraint_new_1(xy_t point2d, plate_d1_t D1S, plate_d1_t D1T) {
  return new plate_g_to_c_constraint_t{
      {cast_to_gp(point2d), cast_to_pp(D1S), cast_to_pp(D1T)}};
}

plate_g_to_c_constraint_t *plate_g_to_c_constraint_new_2(xy_t point2d,
                                                         plate_d1_t D1S,
                                                         plate_d1_t D1T,
                                                         xyz_t nP) {
  return new plate_g_to_c_constraint_t{
      {cast_to_gp(point2d), cast_to_pp(D1S), cast_to_pp(D1T), cast_to_gp(nP)}};
}

plate_g_to_c_constraint_t *
plate_g_to_c_constraint_new_3(xy_t point2d, plate_d1_t D1S, plate_d1_t D1T,
                              plate_d2_t D2S, plate_d2_t D2T) {
  return new plate_g_to_c_constraint_t{{cast_to_gp(point2d), cast_to_pp(D1S),
                                        cast_to_pp(D1T), cast_to_pp(D2S),
                                        cast_to_pp(D2T)}};
}

plate_g_to_c_constraint_t *
plate_g_to_c_constraint_new_4(xy_t point2d, plate_d1_t D1S, plate_d1_t D1T,
                              plate_d2_t D2S, plate_d2_t D2T, xyz_t nP) {
  return new plate_g_to_c_constraint_t{{cast_to_gp(point2d), cast_to_pp(D1S),
                                        cast_to_pp(D1T), cast_to_pp(D2S),
                                        cast_to_pp(D2T), cast_to_gp(nP)}};
}

plate_g_to_c_constraint_t *
plate_g_to_c_constraint_new_5(xy_t point2d, plate_d1_t D1S, plate_d1_t D1T,
                              plate_d2_t D2S, plate_d2_t D2T, plate_d3_t D3S,
                              plate_d3_t D3T) {
  return new plate_g_to_c_constraint_t{
      {cast_to_gp(point2d), cast_to_pp(D1S), cast_to_pp(D1T), cast_to_pp(D2S),
       cast_to_pp(D2T), cast_to_pp(D3S), cast_to_pp(D3T)}};
}

plate_g_to_c_constraint_t *
plate_g_to_c_constraint_new_6(xy_t point2d, plate_d1_t D1S, plate_d1_t D1T,
                              plate_d2_t D2S, plate_d2_t D2T, plate_d3_t D3S,
                              plate_d3_t D3T, xyz_t nP) {
  return new plate_g_to_c_constraint_t{
      {cast_to_gp(point2d), cast_to_pp(D1S), cast_to_pp(D1T), cast_to_pp(D2S),
       cast_to_pp(D2T), cast_to_pp(D3S), cast_to_pp(D3T), cast_to_gp(nP)}};
}

void plate_g_to_c_constraint_free(plate_g_to_c_constraint_t *p) {
  if (p) {
    delete p;
  }
}

plate_free_g_to_c_constraint_t *
plate_free_g_to_c_constraint_new_1(xy_t point2d, plate_d1_t D1S, plate_d1_t D1T,
                                   double IncrementalLoad, int orientation) {
  return new plate_free_g_to_c_constraint_t{{cast_to_gp(point2d),
                                             cast_to_pp(D1S), cast_to_pp(D1T),
                                             IncrementalLoad, orientation}};
}

plate_free_g_to_c_constraint_t *
plate_free_g_to_c_constraint_new_2(xy_t point2d, plate_d1_t D1S, plate_d1_t D1T,
                                   plate_d2_t D2S, plate_d2_t D2T,
                                   double IncrementalLoad, int orientation) {
  return new plate_free_g_to_c_constraint_t{
      {cast_to_gp(point2d), cast_to_pp(D1S), cast_to_pp(D1T), cast_to_pp(D2S),
       cast_to_pp(D2T), IncrementalLoad, orientation}};
}

plate_free_g_to_c_constraint_t *
plate_free_g_to_c_constraint_new_3(xy_t point2d, plate_d1_t D1S, plate_d1_t D1T,
                                   plate_d2_t D2S, plate_d2_t D2T,
                                   plate_d3_t D3S, plate_d3_t D3T,
                                   double IncrementalLoad, int orientation) {
  return new plate_free_g_to_c_constraint_t{
      {cast_to_gp(point2d), cast_to_pp(D1S), cast_to_pp(D1T), cast_to_pp(D2S),
       cast_to_pp(D2T), cast_to_pp(D3T), cast_to_pp(D3T), IncrementalLoad,
       orientation}};
}

void plate_free_g_to_c_constraint_free(plate_free_g_to_c_constraint_t *p) {
  if (p) {
    delete p;
  }
}

#ifdef __cplusplus
}
#endif
