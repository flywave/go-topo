#include "convex_hull.hh"

namespace flywave {
namespace topo {

point::point(double x, double y) : x(x), y(y) {}

bool point::operator==(const point &other) const {
  return x == other.x && y == other.y;
}

size_t point::hash::operator()(const point &p) const {
  return std::hash<double>()(p.x) ^ std::hash<double>()(p.y);
}

segment::segment(const point &a, const point &b) : a(a), b(b) {}

arc::arc(const point &c, double r, double a1, double a2)
    : c(c), r(r), a1(a1), a2(a2) {
  s = point(r * std::cos(a1), r * std::sin(a1));
  e = point(r * std::cos(a2), r * std::sin(a2));
  ac = 2 * M_PI - (a1 - a2);
}

bool arc::operator==(const arc &other) const {
  return c == other.c && r == other.r && a1 == other.a1 && a2 == other.a2;
}

size_t arc::hash::operator()(const arc &a) const {
  return std::hash<double>()(a.c.x) ^ std::hash<double>()(a.c.y) ^
         std::hash<double>()(a.r) ^ std::hash<double>()(a.a1) ^
         std::hash<double>()(a.a2);
}

double atan2p(double x, double y) {
  double rv = std::atan2(y, x);
  if (rv < 0) {
    rv = std::fmod(2 * M_PI + rv, 2 * M_PI);
  }
  return rv;
}

std::pair<std::vector<arc>, std::vector<point>>
convert_and_validate(const std::vector<edge> &edges) {
  std::unordered_set<arc, arc::hash> arcs;
  std::unordered_set<point, point::hash> points;

  for (const auto &e : edges) {
    auto gt = e.geom_type();

    if (gt == "LINE") {
      auto p1 = e.start_point();
      auto p2 = e.end_point();

      points.insert(point(p1.X(), p1.Y()));
      points.insert(point(p2.X(), p2.Y()));
    } else if (gt == "CIRCLE") {
      auto c = e.arc_center();
      auto r = e.radius();
      auto bounds = e.bounds();

      arcs.insert(arc{point(c.X(), c.Y()), r, bounds.first, bounds.second});
    } else {
      throw std::runtime_error("Unsupported geometry " + gt);
    }
  }

  return {std::vector<arc>(arcs.begin(), arcs.end()),
          std::vector<point>(points.begin(), points.end())};
}

std::pair<point, size_t> select_lowest_point(const std::vector<point> &points) {
  std::vector<double> x, y;
  for (const auto &p : points) {
    x.push_back(p.x);
    y.push_back(p.y);
  }

  std::vector<size_t> indices(points.size());
  std::iota(indices.begin(), indices.end(), 0);

  std::sort(indices.begin(), indices.end(), [&y, &x](size_t i1, size_t i2) {
    return std::tie(y[i1], x[i1]) < std::tie(y[i2], x[i2]);
  });

  return {points[indices[0]], indices[0]};
}

std::pair<point, arc> select_lowest_arc(const std::vector<arc> &arcs) {
  std::vector<double> x, y;

  for (const auto &a : arcs) {
    if (a.a1 < 1.5 * M_PI && a.a2 > 1.5 * M_PI) {
      x.push_back(a.c.x);
      y.push_back(a.c.y - a.r);
    } else {
      auto pair =
          select_lowest_point({point(a.s.x, a.s.y), point(a.e.x, a.e.y)});
      x.push_back(pair.first.x);
      y.push_back(pair.first.y);
    }
  }

  std::vector<size_t> indices(arcs.size());
  std::iota(indices.begin(), indices.end(), 0);

  std::sort(indices.begin(), indices.end(), [&y, &x](size_t i1, size_t i2) {
    return std::tie(y[i1], x[i1]) < std::tie(y[i2], x[i2]);
  });

  return {point(x[indices[0]], y[indices[0]]), arcs[indices[0]]};
}

entity select_lowest(const std::vector<arc> &arcs,
                     const std::vector<point> &points) {
  auto p_lowest = points.empty() ? boost::optional<std::pair<point, size_t>>()
                                 : select_lowest_point(points);
  auto a_lowest = arcs.empty() ? boost::optional<std::pair<point, arc>>()
                               : select_lowest_arc(arcs);

  if (!p_lowest && a_lowest) {
    return a_lowest->second;
  } else if (p_lowest && !a_lowest) {
    return p_lowest->first;
  } else if (p_lowest && a_lowest) {
    auto pair = select_lowest_point({p_lowest->first, a_lowest->first});
    return pair.second == 0 ? entity(p_lowest->first)
                            : entity(a_lowest->second);
  } else {
    throw std::runtime_error("No entities specified");
  }
}

std::pair<double, segment> pt_pt(const point &p1, const point &p2) {
  double angle = 0;
  double dx = p2.x - p1.x;
  double dy = p2.y - p1.y;

  if (dx != 0 || dy != 0) {
    angle = atan2p(dx, dy);
  }

  return {angle, segment(p1, p2)};
}

std::tuple<double, double, double, double> _pt_arc(const point &p,
                                                   const arc &a) {
  double x = p.x, y = p.y;
  double r = a.r;
  double xc = a.c.x, yc = a.c.y;
  double dx = x - xc, dy = y - yc;
  double l = std::sqrt(dx * dx + dy * dy);

  double x1 =
      r * r / (l * l) * dx - r / (l * l) * std::sqrt(l * l - r * r) * dy + xc;
  double y1 =
      r * r / (l * l) * dy + r / (l * l) * std::sqrt(l * l - r * r) * dx + yc;
  double x2 =
      r * r / (l * l) * dx + r / (l * l) * std::sqrt(l * l - r * r) * dy + xc;
  double y2 =
      r * r / (l * l) * dy - r / (l * l) * std::sqrt(l * l - r * r) * dx + yc;

  return {x1, y1, x2, y2};
}

std::pair<double, segment> pt_arc(const point &p, const arc &a) {
  double x1, y1, x2, y2;
  std::tie(x1, y1, x2, y2) = _pt_arc(p, a);

  double angle1 = atan2p(x1 - p.x, y1 - p.y);
  double angle2 = atan2p(x2 - p.x, y2 - p.y);

  std::vector<double> angles = {angle1, angle2};
  std::vector<point> points = {point(x1, y1), point(x2, y2)};

  size_t ix = std::distance(angles.begin(),
                            std::min_element(angles.begin(), angles.end()));

  return {angles[ix], segment(p, points[ix])};
}

std::pair<double, segment> arc_pt(const arc &a, const point &p) {
  double x1, y1, x2, y2;
  std::tie(x1, y1, x2, y2) = _pt_arc(p, a);

  double angle1 = atan2p(p.x - x1, p.y - y1);
  double angle2 = atan2p(p.x - x2, p.y - y2);

  std::vector<double> angles = {angle1, angle2};
  std::vector<point> points = {point(x1, y1), point(x2, y2)};

  size_t ix = std::distance(angles.begin(),
                            std::max_element(angles.begin(), angles.end()));

  return {angles[ix], segment(points[ix], p)};
}

std::pair<double, segment> arc_arc(const arc &a1, const arc &a2) {
  double r1 = a1.r;
  double xc1 = a1.c.x, yc1 = a1.c.y;

  double r2 = a2.r;
  double xc2 = a2.c.x, yc2 = a2.c.y;

  double dx1, dy1, dx2, dy2;

  if (r1 > r2) {
    auto arc_tmp = arc(a1.c, r1 - r2, a1.a1, a1.a2);
    double xtmp1, ytmp1, xtmp2, ytmp2;

    std::tie(xtmp1, ytmp1, xtmp2, ytmp2) = _pt_arc(a2.c, arc_tmp);

    double delta_r = r1 - r2;

    dx1 = (xtmp1 - xc1) / delta_r;
    dy1 = (ytmp1 - yc1) / delta_r;

    dx2 = (xtmp2 - xc1) / delta_r;
    dy2 = (ytmp2 - yc1) / delta_r;
  } else if (r1 < r2) {
    auto arc_tmp = arc(a2.c, r2 - r1, a2.a1, a2.a2);
    double xtmp1, ytmp1, xtmp2, ytmp2;
    std::tie(xtmp1, ytmp1, xtmp2, ytmp2) = _pt_arc(a1.c, arc_tmp);

    double delta_r = r2 - r1;

    dx1 = (xtmp1 - xc2) / delta_r;
    dy1 = (ytmp1 - yc2) / delta_r;

    dx2 = (xtmp2 - xc2) / delta_r;
    dy2 = (ytmp2 - yc2) / delta_r;
  } else {
    double dx = xc2 - xc1;
    double dy = yc2 - yc1;
    double l = std::sqrt(dx * dx + dy * dy);

    dx /= l;
    dy /= l;

    dx1 = -dy;
    dy1 = dx;
    dx2 = dy;
    dy2 = -dx;
  }

  double x11 = xc1 + dx1 * r1;
  double y11 = yc1 + dy1 * r1;
  double x12 = xc1 + dx2 * r1;
  double y12 = yc1 + dy2 * r1;

  double x21 = xc2 + dx1 * r2;
  double y21 = yc2 + dy1 * r2;
  double x22 = xc2 + dx2 * r2;
  double y22 = yc2 + dy2 * r2;

  double a1_out = atan2p(x21 - x11, y21 - y11);
  double a2_out = atan2p(x22 - x12, y22 - y12);

  double a11 = std::fmod(atan2p(x11 - xc1, y11 - yc1) + M_PI_2, 2 * M_PI);
  double a21 = std::fmod(atan2p(x12 - xc1, y12 - yc1) + M_PI_2, 2 * M_PI);

  std::vector<double> diffs = {std::abs(a11 - a1_out), std::abs(a21 - a2_out)};

  size_t ix = std::distance(diffs.begin(),
                            std::min_element(diffs.begin(), diffs.end()));

  std::vector<double> angles = {a1_out, a2_out};
  std::vector<segment> segments = {segment(point(x11, y11), point(x21, y21)),
                                   segment(point(x12, y12), point(x22, y22))};

  return {angles[ix], segments[ix]};
}

std::pair<double, segment> get_angle(const entity &current, const entity &e) {
  if (current == e) {
    return {std::numeric_limits<double>::infinity(),
            segment(point(std::numeric_limits<double>::infinity(),
                          std::numeric_limits<double>::infinity()),
                    point(std::numeric_limits<double>::infinity(),
                          std::numeric_limits<double>::infinity()))};
  }

  if (boost::get<point>(&current)) {
    auto p = *boost::get<point>(&current);
    if (boost::get<point>(&e)) {
      return pt_pt(p, *boost::get<point>(&e));
    } else {
      return pt_arc(p, *boost::get<arc>(&e));
    }
  } else {
    auto a = *boost::get<arc>(&current);
    if (boost::get<point>(&e)) {
      return arc_pt(a, *boost::get<point>(&e));
    } else {
      return arc_arc(a, *boost::get<arc>(&e));
    }
  }
}

std::tuple<entity, double, bool>
update_hull(entity current_e, size_t ix, std::vector<entity> &entities,
            const std::vector<double> &angles,
            const std::vector<segment> &segments, hull &hull) {
  auto next_e = entities[ix];
  auto connecting_seg = segments[ix];

  if (boost::get<point>(&next_e)) {
    entities.erase(entities.begin() + ix);
  }

  hull.push_back(connecting_seg);
  hull.push_back(next_e);

  bool finished = false;
  if (hull.size() > 0) {
    auto visitor =
        [&next_e](const boost::variant<flywave::topo::arc, flywave::topo::point,
                                       flywave::topo::segment> &first_elem) {
          if (auto p1 = boost::get<point>(&first_elem)) {
            if (auto p2 = boost::get<point>(&next_e)) {
              return *p1 == *p2;
            }
          } else if (auto a1 = boost::get<arc>(&first_elem)) {
            if (auto a2 = boost::get<arc>(&next_e)) {
              return *a1 == *a2;
            }
          }
          return false;
        };
    finished = boost::apply_visitor(visitor, hull[0]);
  }

  return {next_e, angles[ix], finished};
}

wire finalize_hull(const hull &h) {
  std::vector<edge> edges;

  for (size_t i = 0; i + 2 < h.size(); ++i) {
    const auto &el_p = h[i];
    const auto &el = h[i + 1];
    const auto &el_n = h[i + 2];

    if (boost::get<segment>(&el)) {
      auto seg = *boost::get<segment>(&el);
      edges.emplace_back(edge::make_edge(gp_Pnt(seg.a.x, seg.a.y, 0),
                                         gp_Pnt(seg.b.x, seg.b.y, 0)));
    } else if (boost::get<arc>(&el) && boost::get<segment>(&el_p) &&
               boost::get<segment>(&el_n)) {
      auto a = *boost::get<arc>(&el);
      auto seg_p = *boost::get<segment>(&el_p);
      auto seg_n = *boost::get<segment>(&el_n);

      double a1 = atan2p(seg_p.b.x - a.c.x, seg_p.b.y - a.c.y) * 180.0 / M_PI;
      double a2 = atan2p(seg_n.a.x - a.c.x, seg_n.a.y - a.c.y) * 180.0 / M_PI;

      edges.emplace_back(edge::make_circle(a.r, gp_Pnt(a.c.x, a.c.y, 0),
                                           gp_Dir(0, 0, 1), a1, a2));
    }
  }

  if (h.size() > 2) {
    const auto &el = h[h.size() - 2];
    const auto &el_n = h[h.size() - 1];
    const auto &el1 = h[1];

    if (boost::get<segment>(&el) && boost::get<arc>(&el_n) &&
        boost::get<segment>(&el1)) {
      auto seg = *boost::get<segment>(&el);
      auto a = *boost::get<arc>(&el_n);
      auto seg1 = *boost::get<segment>(&el1);

      double a1 = atan2p(seg.b.x - a.c.x, seg.b.y - a.c.y) * 180.0 / M_PI;
      double a2 = atan2p(seg1.a.x - a.c.x, seg1.a.y - a.c.y) * 180.0 / M_PI;

      edges.emplace_back(edge::make_circle(a.r, gp_Pnt(a.c.x, a.c.y, 0),
                                           gp_Dir(0, 0, 1), a1, a2));
    }
  }

  return wire::make_wire(edges);
}

wire find_hull(const std::vector<edge> &edges) {
  hull rv;

  auto pair = convert_and_validate(edges);
  auto arcs = pair.first;
  auto points = pair.second;
  auto start = select_lowest(arcs, points);
  rv.push_back(start);

  std::vector<entity> entities;
  entities.insert(entities.end(), arcs.begin(), arcs.end());
  entities.insert(entities.end(), points.begin(), points.end());

  entity current_e = start;
  double current_angle = 0.0;
  bool finished = false;

  while (!finished) {
    std::vector<double> angles;
    std::vector<segment> segments;

    for (const auto &e : entities) {
      auto pair = get_angle(current_e, e);
      auto angle = pair.first;
      auto segment = pair.second;
      angles.push_back(angle >= current_angle
                           ? angle
                           : std::numeric_limits<double>::infinity());
      segments.push_back(segment);
    }

    auto min_it = std::min_element(angles.begin(), angles.end());
    size_t next_ix = std::distance(angles.begin(), min_it);

    std::tie(current_e, current_angle, finished) =
        update_hull(current_e, next_ix, entities, angles, segments, rv);
  }

  return finalize_hull(rv);
}

} // namespace topo
} // namespace flywave
