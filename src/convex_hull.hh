#pragma once

#include "edge.hh"
#include "vector.hh"
#include "wire.hh"

#include <algorithm>
#include <boost/variant.hpp>
#include <boost/variant/get.hpp>
#include <cmath>
#include <limits>
#include <memory>
#include <stdexcept>
#include <unordered_set>
#include <variant>
#include <vector>

namespace flywave {
namespace topo {

class point {
public:
  double x;
  double y;
  static constexpr double kTolerance = 1e-6;

  point(double x = 0, double y = 0);
  bool operator==(const point &other) const;

  bool operator<(const point &other) const;

  bool equals(const point &other, double tol = kTolerance) const;

  struct hash {
    size_t operator()(const point &p) const;
  };
};

class segment {
public:
  point a;
  point b;

  segment(const point &a, const point &b);
};

class arc {
public:
  point c;
  point s;
  point e;
  double r;
  double a1;
  double a2;
  double ac;
  static constexpr double kTolerance = 1e-6;

  arc() = default;
  arc(const point &c, double r, double a1, double a2);
  bool operator==(const arc &other) const;

  bool equals(const arc &other, double tol = kTolerance) const;

  struct hash {
    size_t operator()(const arc &a) const;
  };
};

using entity = boost::variant<arc, point>;
using hull = std::vector<boost::variant<arc, point, segment>>;

double atan2p(double x, double y);

std::pair<std::vector<arc>, std::vector<point>>
convert_and_validate(const std::vector<edge> &edges);

std::pair<point, size_t> select_lowest_point(const std::vector<point> &points);
std::pair<point, arc> select_lowest_arc(const std::vector<arc> &arcs);
entity select_lowest(const std::vector<arc> &arcs,
                     const std::vector<point> &points);

std::pair<double, segment> pt_pt(const point &p1, const point &p2);
std::tuple<double, double, double, double> _pt_arc(const point &p,
                                                   const arc &a);
std::pair<double, segment> pt_arc(const point &p, const arc &a);
std::pair<double, segment> arc_pt(const arc &a, const point &p);
std::pair<double, segment> arc_arc(const arc &a1, const arc &a2);

std::pair<double, segment> get_angle(const entity &current, const entity &e);

std::tuple<entity, double, bool>
update_hull(entity current_e, size_t ix, std::vector<entity> &entities,
            const std::vector<double> &angles,
            const std::vector<segment> &segments, hull &hull);

wire finalize_hull(const hull &h);
wire find_hull(const std::vector<edge> &edges);

} // namespace topo
} // namespace flywave
