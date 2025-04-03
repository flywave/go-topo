#pragma once

#include <algorithm>
#include <cfloat>
#include <cmath>
#include <limits>

namespace flywave {
namespace dxf {

class vector3d {
public:
  double x;
  double y;
  double z;

  vector3d() = default;
  vector3d(double ax, double ay, double az) : x(ax), y(ay), z(az) {}

  vector3d operator-(const vector3d &other) const {
    return vector3d(this->x - other.x, this->y - other.y, this->z - other.z);
  }

  vector3d operator+(const vector3d &other) const {
    return vector3d(this->x + other.x, this->y + other.y, this->z + other.z);
  }

  vector3d operator*(double k) const {
    return vector3d(this->x * k, this->y * k, this->z * k);
  }

  double operator*(const vector3d &other) const {
    return this->x * other.x + this->y * other.y + this->z * other.z;
  }

  inline vector3d &normalize();

  inline double length() const {
    return std::sqrt((x * x) + (y * y) + (z * z));
  }
  inline double get_angle(const vector3d &rcVect) const;
  inline vector3d distance_to_line_segment(const vector3d &rclP1,
                                           const vector3d &rclP2) const;
};

template <class T> T clamp(T num, T lower, T upper) {
  return std::max<T>(std::min<T>(upper, num), lower);
}

inline double distance_p2(const vector3d &v1, const vector3d &v2) {
  const double x = v1.x - v2.x;
  const double y = v1.y - v2.y;
  const double z = v1.z - v2.z;
  return x * x + y * y + z * z;
}

vector3d &vector3d::normalize() {
  double fLen = length();
  if (fLen != 0.0 && fLen != 1.0) { // Suspicious
    x /= fLen;
    y /= fLen;
    z /= fLen;
  }

  return *this;
}

double vector3d::get_angle(const vector3d &rcVect) const {
  double len1 = length();
  double len2 = rcVect.length();
  if (len1 <= DBL_EPSILON || len2 <= DBL_EPSILON)
    return std::numeric_limits<double>::quiet_NaN(); // division by zero

  double dot = (*this) * rcVect;
  dot /= len1;
  dot /= len2;

  if (dot <= -1.0)
    return 3.141592653589793;
  else if (dot >= 1.0)
    return 0.0;

  return std::acos(dot);
}

vector3d vector3d::distance_to_line_segment(const vector3d &rclP1,
                                            const vector3d &rclP2) const {
  double len2 = dxf::distance_p2(rclP1, rclP2);
  if (len2 <= DBL_EPSILON)
    return rclP1;

  vector3d p2p1 = rclP2 - rclP1;
  vector3d pXp1 = *this - rclP1;
  double dot = pXp1 * p2p1;
  double t = clamp<double>(dot / len2, 0, 1);
  vector3d dist = p2p1 * t - pXp1;
  return dist;
}

} // namespace dxf
} // namespace flywave
