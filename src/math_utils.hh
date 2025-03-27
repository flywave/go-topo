#pragma once

#include <algorithm>
#include <cmath>
#include <gp_Dir.hxx>
#include <gp_Pln.hxx>
#include <utility>

namespace flywave {

struct bnd_box_coords;

namespace math_utils {

template <typename T, typename T1, typename T2, typename T3, typename T4>
double mapped_value(T val, T1 omin, T2 omax, T3 nmin, T4 nmax);

template <typename T, typename T1, typename T2>
double to_percent(T val, T1 omin, T2 omax);

bool is_reversed_standard_dir(const gp_Dir &n);

double plane_position(const gp_Pln &plane);

std::pair<double, double> plane_range(const bnd_box_coords &bbc,
                                      const gp_Dir &planeNormal);

template <typename T, typename U> static T lerp(T a, T b, U t);

inline bool fuzzy_is_null(float f) { return std::abs(f) <= 0.00001f; }

inline bool fuzzy_is_null(double d) { return std::abs(d) <= 0.000000000001; }

inline bool fuzzy_equal(float f1, float f2) {
  return (std::abs(f1 - f2) * 100000.f <= std::min(std::abs(f1), std::abs(f2)));
}

inline bool fuzzy_equal(double d1, double d2) {
  return (std::abs(d1 - d2) * 1000000000000. <=
          std::min(std::abs(d1), std::abs(d2)));
}

template <typename T, typename T1, typename T2, typename T3, typename T4>
double mapped_value(T val, T1 omin, T2 omax, T3 nmin, T4 nmax) {
  const auto dist1 = static_cast<double>(omax - omin);
  const auto dist2 = nmax - nmin;
  const auto distVal = val - omin;
  return ((distVal * dist2) / dist1) + nmin;
}

template <typename T, typename T1, typename T2>
double to_percent(T val, T1 omin, T2 omax) {
  return mapped_value(val, omin, omax, 0, 100);
}

template <typename T, typename U> T lerp(T a, T b, U t) {
#ifdef __cpp_lib_interpolate
  return std::lerp(a, b, t);
#else
  return T(a * (1 - t) + b * t);
#endif
}

} // namespace math_utils
} // namespace flywave