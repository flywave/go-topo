#ifndef __FLYWAVE_MESH_TOPO_OCC_LOCATION_HH__
#define __FLYWAVE_MESH_TOPO_OCC_LOCATION_HH__

#include <TopLoc_Datum3D.hxx>
#include <TopLoc_Location.hxx>
#include <gp_Pln.hxx>
#include <gp_Quaternion.hxx>
#include <gp_Trsf.hxx>
#include <gp_Vec.hxx>

#include "vector.hh"
#include <vector>

namespace flywave {
namespace topo {

class topo_location {
public:
  topo_location() : _loc() {}
  topo_location(gp_Trsf t) : _loc(t) {}
  topo_location(TopLoc_Location l) : _loc(l) {}

  topo_location(const gp_Pnt &p);
  topo_location(const gp_Vec &t);
  topo_location(const gp_Vec &t, double rx, double ry, double rz);
  topo_location(const gp_Pln &pln);
  topo_location(const gp_Pln &pln, const gp_Pnt &pos);
  topo_location(const gp_Vec &t, const gp_Vec &axis, double angle);
  topo_location(const topo_vector &v);

  topo_location(const topo_location &other) : _loc(other._loc) {}
  topo_location &operator=(const topo_location &other) {
    _loc = other._loc;
    return *this;
  }

  topo_location(topo_location &&) noexcept;
  topo_location &operator=(topo_location &&) noexcept;

  virtual ~topo_location() = default;

  operator const TopLoc_Location &() const { return _loc; }

  operator gp_Trsf() const { return gp_Trsf(_loc); }

  size_t hash_code() const { return _loc.HashCode(1); }

  topo_location inverted() const { return topo_location{_loc.Inverted()}; }
  topo_location operator/(const topo_location &o) const {
    return topo_location{_loc / o._loc};
  }

  topo_location operator*(const topo_location &o) const {
    return topo_location{_loc * o._loc};
  }

  topo_location pow(int exponent) const {
    return topo_location{_loc.Powered(exponent)};
  }

  std::vector<std::vector<double>> to_vector() const {
    std::vector<std::vector<double>> result(3, std::vector<double>(4));
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 4; ++j) {
        result[i][j] = _loc.Transformation().Value(i + 1, j + 1);
      }
    }
    return result;
  }

  std::tuple<std::tuple<double, double, double>,
             std::tuple<double, double, double>>
  to_tuple() const {
    gp_Trsf T = _loc.Transformation();
    gp_XYZ trans = T.TranslationPart();
    gp_Quaternion rot = T.GetRotation();

    double rx, ry, rz;
    rot.GetEulerAngles(gp_Extrinsic_XYZ, rx, ry, rz);

    return std::make_tuple(std::make_tuple(trans.X(), trans.Y(), trans.Z()),
                           std::make_tuple(rx, ry, rz));
  }

  friend bool operator==(const topo_location &left,
                         const topo_location &right) {
    return left._loc == right._loc;
  }

  friend bool operator!=(const topo_location &left,
                         const topo_location &right) {
    return !(left == right);
  }

private:
  TopLoc_Location _loc;
};

} // namespace topo
} // namespace flywave

#endif // __FLYWAVE_MESH_TOPO_OCC_LOCATION_HH__
