#ifndef __FLYWAVE_MESH_TOPO_OCC_LOCATION_HH__
#define __FLYWAVE_MESH_TOPO_OCC_LOCATION_HH__

#include <TopLoc_Datum3D.hxx>
#include <TopLoc_Location.hxx>

namespace flywave {
namespace topo {

class topo_location {
public:
  topo_location() : _loc() {}
  topo_location(gp_Trsf t) : _loc(t) {}
  topo_location(TopLoc_Location l) : _loc(l) {}

  virtual ~topo_location() = default;

  operator const TopLoc_Location &() const { return _loc; }

  operator gp_Trsf() const { return gp_Trsf(_loc); }

  topo_location inverted() const { return topo_location{_loc.Inverted()}; }
  topo_location operator/(const topo_location &o) const {
    return topo_location{_loc / o._loc};
  }

  topo_location operator*(const topo_location &o) const {
    return topo_location{_loc / o._loc};
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
