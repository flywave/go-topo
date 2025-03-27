#pragma once

#include <Bnd_Box.hxx>
#include <array>
#include <gp_Pnt.hxx>

namespace flywave {

struct bnd_utils {
  static void add(Bnd_Box *box, const Bnd_Box &other);
  static bool is_open(const Bnd_Box &bndBox);
  static bool has_finite_part(const Bnd_Box &bndBox);
  static Bnd_Box finite_part(const Bnd_Box &bndBox);
};

struct bnd_box_coords {
  double xmin;
  double ymin;
  double zmin;
  double xmax;
  double ymax;
  double zmax;

  gp_Pnt center() const;

  std::array<gp_Pnt, 8> vertices() const;

  gp_Pnt min_vertex() const;

  gp_Pnt max_vertex() const;

  static bnd_box_coords get(const Bnd_Box &box);
};

} // namespace flywave