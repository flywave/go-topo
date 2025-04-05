#include "location.hh"

namespace flywave {
namespace topo {

topo_location::topo_location(const gp_Pnt &p) {
  gp_Trsf T;
  T.SetTranslation(gp_Vec(p.X(), p.Y(), p.Z()));
  _loc = TopLoc_Location(T);
}

topo_location::topo_location(const topo_vector &v) {
  gp_Trsf T;
  T.SetTranslation(gp_Vec(v.x(), v.y(), v.z()));
  _loc = TopLoc_Location(T);
}

topo_location::topo_location(const gp_Vec &t) {
  gp_Trsf T;
  T.SetTranslation(t);
  _loc = TopLoc_Location(T);
}

topo_location::topo_location(const gp_Vec &t, double rx, double ry, double rz) {
  gp_Trsf T;
  gp_Quaternion q;
  q.SetEulerAngles(gp_Extrinsic_XYZ, rx, ry, rz);
  T.SetRotation(q);
  T.SetTranslation(t);
  _loc = TopLoc_Location(T);
}

topo_location::topo_location(const gp_Pln &pln) {
  gp_Trsf T;
  T.SetTransformation(pln.Position());
  T.Invert();
  _loc = TopLoc_Location(T);
}

topo_location::topo_location(const gp_Pln &pln, const gp_Pnt &pos) {
  gp_Trsf T;
  T.SetTransformation(
      gp_Ax3(pos, pln.Axis().Direction(), pln.XAxis().Direction()));
  T.Invert();
  _loc = TopLoc_Location(T);
}

topo_location::topo_location(const gp_Vec &t, const gp_Vec &axis,
                             double angle) {
  gp_Trsf T;
  T.SetRotation(gp_Ax1(gp_Pnt(), axis.Normalized()), angle);
  T.SetTranslation(t);
  _loc = TopLoc_Location(T);
}

topo_location::topo_location(topo_location &&other) noexcept
    : _loc(std::move(other._loc)) {}

topo_location &topo_location::operator=(topo_location &&other) noexcept {
  if (this != &other) {
    _loc = std::move(other._loc);
  }
  return *this;
}

} // namespace topo
} // namespace flywave
