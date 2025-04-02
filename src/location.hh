#ifndef __FLYWAVE_MESH_TOPO_OCC_LOCATION_HH__
#define __FLYWAVE_MESH_TOPO_OCC_LOCATION_HH__

#include <TopLoc_Datum3D.hxx>
#include <TopLoc_Location.hxx>
#include <gp_Quaternion.hxx>
#include <gp_Trsf.hxx>
#include <gp_Vec.hxx>
#include <gp_Pln.hxx>

#include "vector.hh"

namespace flywave {
namespace topo {

class topo_location {
public:
  topo_location() : _loc() {}
  topo_location(gp_Trsf t) : _loc(t) {}
  topo_location(TopLoc_Location l) : _loc(l) {}

  // gp_Pnt
  topo_location(const gp_Pnt &p) {
    gp_Trsf T;
    T.SetTranslation(gp_Vec(p.X(), p.Y(), p.Z()));
    _loc = TopLoc_Location(T);
  }

  // topo_vector
  topo_location(const topo_vector &v) {
    gp_Trsf T;
    T.SetTranslation(gp_Vec(v.x(), v.y(), v.z()));
    _loc = TopLoc_Location(T);
  }

  // 从平移向量构造
  topo_location(const gp_Vec &t) {
    gp_Trsf T;
    T.SetTranslation(t);
    _loc = TopLoc_Location(T);
  }

  // 从平移和旋转角度构造
  topo_location(const gp_Vec &t, double rx, double ry, double rz) {
    gp_Trsf T;
    gp_Quaternion q;
    q.SetEulerAngles(gp_Extrinsic_XYZ, rx, ry, rz);
    T.SetRotation(q);
    T.SetTranslation(t);
    _loc = TopLoc_Location(T);
  }

  // 从平面构造
  topo_location(const gp_Pln &pln) {
    gp_Trsf T;
    T.SetTransformation(pln.Position());
    T.Invert();
    _loc = TopLoc_Location(T);
  }

  // 从平面和位置构造
  topo_location(const gp_Pln &pln, const gp_Pnt &pos) {
    gp_Trsf T;
    T.SetTransformation(
        gp_Ax3(pos, pln.Axis().Direction(), pln.XAxis().Direction()));
    T.Invert();
    _loc = TopLoc_Location(T);
  }

  // 从轴和角度构造
  topo_location(const gp_Vec &t, const gp_Vec &axis, double angle) {
    gp_Trsf T;
    T.SetRotation(gp_Ax1(gp_Pnt(), axis.Normalized()), angle);
    T.SetTranslation(t);
    _loc = TopLoc_Location(T);
  }

  virtual ~topo_location() = default;

  operator const TopLoc_Location &() const { return _loc; }

  operator gp_Trsf() const { return gp_Trsf(_loc); }

  size_t hash_code() const { return _loc.HashCode(1); }

  topo_location inverted() const { return topo_location{_loc.Inverted()}; }
  topo_location operator/(const topo_location &o) const {
    return topo_location{_loc / o._loc};
  }

  // 修正乘法运算符实现
  topo_location operator*(const topo_location &o) const {
    return topo_location{_loc * o._loc};
  }

  // 添加幂运算
  topo_location pow(int exponent) const {
    return topo_location{_loc.Powered(exponent)};
  }

  // 获取平移和旋转信息
  std::tuple<std::tuple<double, double, double>,
             std::tuple<double, double, double>>
  toTuple() const {
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
