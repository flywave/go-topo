#include "bnd_utils.hh"
#include "version.hh"

namespace flywave {

gp_Pnt bnd_box_coords::center() const {
  return {(this->xmax + this->xmin) / 2., (this->ymax + this->ymin) / 2.,
          (this->zmax + this->zmin) / 2.};
}

std::array<gp_Pnt, 8> bnd_box_coords::vertices() const {
  return {{{this->xmin, this->ymin, this->zmax},
           {this->xmax, this->ymin, this->zmax},
           {this->xmin, this->ymin, this->zmin},
           {this->xmax, this->ymin, this->zmin},
           {this->xmin, this->ymax, this->zmax},
           {this->xmax, this->ymax, this->zmax},
           {this->xmin, this->ymax, this->zmin},
           {this->xmax, this->ymax, this->zmin}}};
}

gp_Pnt bnd_box_coords::min_vertex() const {
  return {this->xmin, this->ymin, this->zmin};
}

gp_Pnt bnd_box_coords::max_vertex() const {
  return {this->xmax, this->ymax, this->zmax};
}

bnd_box_coords bnd_box_coords::get(const Bnd_Box &box) {
  bnd_box_coords bbc = {};
  if (!box.IsVoid())
    box.Get(bbc.xmin, bbc.ymin, bbc.zmin, bbc.xmax, bbc.ymax, bbc.zmax);
  return bbc;
}

void bnd_utils::add(Bnd_Box *box, const Bnd_Box &other) {
  const auto bbc = bnd_box_coords::get(other);
  for (const gp_Pnt &pnt : bbc.vertices())
    box->Add(pnt);
}

bool bnd_utils::is_open(const Bnd_Box &bndBox) {
#if OCC_VERSION_HEX >= OCC_VERSION_CHECK(7, 4, 0)
  return bndBox.IsOpen();
#else
  return bndBox.IsOpenXmax() || bndBox.IsOpenXmin() || bndBox.IsOpenYmax() ||
         bndBox.IsOpenYmin() || bndBox.IsOpenZmax() || bndBox.IsOpenZmin();
#endif
}

bool bnd_utils::has_finite_part(const Bnd_Box &bndBox) {
#if OCC_VERSION_HEX >= OCC_VERSION_CHECK(7, 4, 0)
  return bndBox.HasFinitePart();
#else
  const auto coords = bnd_box_coords::get(bndBox);
  return !bndBox.IsVoid() && coords.xmax >= coords.xmin;
#endif
}

Bnd_Box bnd_utils::finite_part(const Bnd_Box &bndBox) {
#if OCC_VERSION_HEX >= OCC_VERSION_CHECK(7, 4, 0)
  return bndBox.FinitePart();
#else
  if (!bnd_utils::has_finite_part(bndBox))
    return Bnd_Box();

  const auto coords = bnd_box_coords::get(bndBox);
  Bnd_Box otherBox;
  otherBox.Update(coords.xmin, coords.ymin, coords.zmin, coords.xmax,
                  coords.ymax, coords.zmax);
  otherBox.SetGap(bndBox.GetGap());
  return otherBox;
#endif
}

} // namespace flywave
