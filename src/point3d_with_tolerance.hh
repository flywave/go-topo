#ifndef __FLYWAVE_MESH_TOPO_POINT3D_WITH_TOLERANCE_HH__
#define __FLYWAVE_MESH_TOPO_POINT3D_WITH_TOLERANCE_HH__

#include <gp_Pnt.hxx>

namespace flywave {
namespace topo {

class point3d_with_tolerance {
public:
  point3d_with_tolerance() = default;
  point3d_with_tolerance(double x, double y, double z, double tolerance);
  point3d_with_tolerance(gp_Pnt point, double t);

  virtual ~point3d_with_tolerance() = default;

  inline double x() const { return _point.X(); }
  inline double y() const { return _point.Y(); }
  inline double z() const { return _point.Z(); }
  inline gp_Pnt point() const { return _point; }
  inline double tolerance() const { return _tolerance; }
  inline gp_Pnt vector() const { return {_point.X(), _point.Y(), _point.Z()}; }

  inline int hash_code() const { return _hashCode; }

  friend bool operator==(const point3d_with_tolerance &left,
                         const point3d_with_tolerance &right) {
    double d = 0, dd;
    double x1 = left.x(), y1 = left.y(), z1 = left.z(), x2 = right.x(),
           y2 = right.y(), z2 = right.z();
    dd = x1;
    dd -= x2;
    dd *= dd;
    d += dd;
    dd = y1;
    dd -= y2;
    dd *= dd;
    d += dd;
    dd = z1;
    dd -= z2;
    dd *= dd;
    d += dd;
    double mt = std::max(left.tolerance(), right.tolerance());
    return d <= mt * mt;
  }

  friend bool operator!=(const point3d_with_tolerance &left,
                         const point3d_with_tolerance &right) {
    return !(left == right);
  }

private:
  void calculate_hash_code();

  gp_Pnt _point;
  double _tolerance;
  int _hashCode;
};
} // namespace topo
} // namespace flywave

namespace std {

template <> struct hash<::flywave::topo::point3d_with_tolerance> {
  size_t operator()(const ::flywave::topo::point3d_with_tolerance &v) const {
    return v.hash_code();
  }
};
} // namespace std
#endif // __FLYWAVE_MESH_TOPO_POINT3D_WITH_TOLERANCE_HH__
