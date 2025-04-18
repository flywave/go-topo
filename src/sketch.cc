#include "sketch.hh"
#include "compound.hh"
#include "convex_hull.hh"
#include "edge.hh"
#include "face.hh"
#include "selector.hh"
#include "shape_ops.hh"
#include "vertex.hh"
#include "wire.hh"
#include "workplane.hh"

#include <ShapeAnalysis_FreeBounds.hxx>
#include <TopTools_HSequenceOfShape.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Wire.hxx>

#include <boost/math/constants/constants.hpp>
#include <boost/range/combine.hpp>
#include <boost/tuple/tuple.hpp>

#include <cmath>
#include <mutex>

namespace flywave {
namespace topo {
namespace detail {
std::mutex occt_mutex;

struct occt_handle_raii {
  Handle(TopTools_HSequenceOfShape) handle;

  occt_handle_raii() : handle(new TopTools_HSequenceOfShape()) {}

  ~occt_handle_raii() { handle.Nullify(); }
};

std::vector<wire> edges_to_wires(const std::vector<edge> &edges,
                                 double tolerance = 1e-6) {
  for (const auto &edge : edges) {
    if (!edge.is_valid()) {
      throw std::invalid_argument("Invalid edge in input");
    }
  }
  std::lock_guard<std::mutex> lock(occt_mutex);

  occt_handle_raii edges_in;
  occt_handle_raii wires_out;

  for (const auto &edge : edges) {
    edges_in.handle->Append(edge.value());
  }

  ShapeAnalysis_FreeBounds::ConnectEdgesToWires(edges_in.handle, tolerance,
                                                false, wires_out.handle);

  std::vector<wire> result;
  result.reserve(wires_out.handle->Length());

  for (int i = 1; i <= wires_out.handle->Length(); ++i) {
    const TopoDS_Shape &wire_shape = wires_out.handle->Value(i);
    if (wire_shape.ShapeType() != TopAbs_WIRE) {
      continue;
    }
    result.push_back(wire(TopoDS::Wire(wire_shape)));
  }

  return result;
}
} // namespace detail

sketch::sketch()
    : parent_(nullptr), locs_{topo_location()},
      faces_({topo::compound::make_compound({})}), edges_(),
      selection_(boost::none), constraints_(), tags_() {}

sketch::sketch(std::shared_ptr<workplane> parent,
               const std::vector<topo_location> &locs,
               boost::optional<compound> obj)
    : parent_(parent),
      locs_(locs.empty() ? std::vector<topo_location>{topo_location()} : locs),
      faces_(obj ? *obj : topo::compound::make_compound({})), edges_(),
      selection_(boost::none), constraints_(), tags_() {}

sketch::sketch(const std::vector<topo_location> &locs,
               boost::optional<compound> obj)
    : parent_(nullptr),
      locs_(locs.empty() ? std::vector<topo_location>{topo_location()} : locs),
      faces_(obj ? *obj : topo::compound::make_compound({})), edges_(),
      selection_(boost::none), constraints_(), tags_() {}

sketch::sketch(sketch &&o) noexcept {
  parent_ = o.parent_;
  locs_ = o.locs_;
  faces_ = std::move(o.faces_);
  edges_ = o.edges_;
  selection_ = o.selection_;
  constraints_ = o.constraints_;
  tags_ = o.tags_;
  o.parent_.reset();
  o.locs_.clear();
  o.faces_ = boost::none;
  o.edges_.clear();
  o.selection_ = boost::none;
  o.constraints_.clear();
  o.tags_.clear();
}

sketch &sketch::operator=(sketch &&o) noexcept {
  if (this != &o) {
    parent_ = o.parent_;
    locs_ = o.locs_;
    faces_ = std::move(o.faces_);
    edges_ = o.edges_;
    selection_ = o.selection_;
    constraints_ = o.constraints_;
    tags_ = o.tags_;
    o.parent_.reset();
    o.locs_.clear();
    o.faces_ = boost::none;
    o.edges_.clear();
    o.selection_ = boost::none;
    o.constraints_.clear();
    o.tags_.clear();
  }
  return *this;
}

int sketch::hash_code() const {
  if (!faces_) {
    return 0;
  }
  return faces_->hash_code();
}

std::vector<face> sketch::get_faces() const {
  std::vector<topo::face> result;
  for (auto &loc : locs_) {
    auto moved = faces_->moved(loc);
    auto faces = moved.faces();
    result.insert(result.end(), faces.begin(), faces.end());
  }
  return result;
}

void sketch::_tag(const std::vector<sketch_val> &val, const std::string &tag) {
  tags_[tag] = val;
}

void sketch::_tag(const std::vector<shape> &val, const std::string &tag) {
  std::vector<sketch_val> vals;
  for (auto &v : val) {
    vals.push_back(v);
  }
  tags_[tag] = vals;
}

sketch &sketch::face(const wire &w, double angle, Mode mode,
                     const std::string &tag, bool ignore_selection) {
  return _face(w, angle, mode,
               tag.empty() ? boost::none : boost::optional<std::string>(tag),
               ignore_selection);
}

sketch &sketch::face(const std::vector<topo::edge> &edges, double angle,
                     Mode mode, const std::string &tag, bool ignore_selection) {
  return _face(edges, angle, mode,
               tag.empty() ? boost::none : boost::optional<std::string>(tag),
               ignore_selection);
}

sketch &sketch::face(const shape &sh, double angle, Mode mode,
                     const std::string &tag, bool ignore_selection) {
  return _face(sh, angle, mode,
               tag.empty() ? boost::none : boost::optional<std::string>(tag),
               ignore_selection);
}

sketch &sketch::face(const std::shared_ptr<sketch> &sk, double angle, Mode mode,
                     const std::string &tag, bool ignore_selection) {
  return _face(sk, angle, mode,
               tag.empty() ? boost::none : boost::optional<std::string>(tag),
               ignore_selection);
}

sketch &sketch::_face(boost::variant<wire, std::vector<topo::edge>, shape,
                                     std::shared_ptr<sketch>>
                          b,
                      double angle, Mode mode,
                      const boost::optional<std::string> &tag,
                      bool ignore_selection) {
  boost::variant<topo::face, std::shared_ptr<sketch>, compound> res;
  if (b.which() == -1) {
    throw std::invalid_argument("Invalid variant state");
  }
  if (auto w = boost::get<wire>(&b)) {
    res = face::make_face(*w);
  } else if (auto s = boost::get<std::shared_ptr<sketch>>(&b)) {
    res = *s;
  } else if (auto sh = boost::get<shape>(&b)) {
    std::vector<shape> faces;
    for (auto &f : sh->faces()) {
      faces.push_back(f);
    }
    res = compound::make_compound(faces);
  } else if (auto edges = boost::get<std::vector<topo::edge>>(&b)) {
    auto wires = detail::edges_to_wires(*edges);
    std::vector<wire> wire_ptrs(wires.begin(), wires.end());
    res = face::make_face(wire_ptrs[0], std::vector<wire>(wire_ptrs.begin() + 1,
                                                          wire_ptrs.end()));
  } else {
    throw std::invalid_argument("Unsupported argument");
  }

  if (angle != 0) {
    if (auto f = boost::get<topo::face>(&res)) {
      *f = *f->moved(topo_location(topo_vector(), topo_vector(0, 0, 1), angle))
                .cast<topo::face>();
    } else if (auto c = boost::get<compound>(&res)) {
      *c = *c->moved(topo_location(topo_vector(), topo_vector(0, 0, 1), angle))
                .cast<topo::compound>();
    } else if (auto s = boost::get<std::shared_ptr<sketch>>(&res)) {
      // Handle sketch rotation if needed
    }
  }

  return _each(
      [res](const topo_location &loc)
          -> boost::variant<topo::face, std::shared_ptr<sketch>, compound> {
        if (auto f = boost::get<topo::face>(&res)) {
          return *f->moved(loc).cast<topo::face>();
        } else if (auto c = boost::get<compound>(&res)) {
          return *c->moved(loc).cast<compound>();
        } else if (auto s = boost::get<std::shared_ptr<sketch>>(&res)) {
          return (*s)->moved({loc});
        }
        return {}; // Shouldn't reach here
      },
      mode, tag, ignore_selection);
}

sketch &sketch::rect(double w, double h, double angle, Mode mode,
                     const boost::optional<std::string> &tag) {
  auto res = face::make_plane(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 0), h, w)
                 .rotated(angle, gp_Pnt(0, 0, 0), gp_Pnt(0, 0, 0));
  return _each(
      [res](const topo_location &loc) {
        return *res.located(loc).cast<topo::face>();
      },
      mode, tag);
}

sketch &sketch::circle(double r, Mode mode,
                       const boost::optional<std::string> &tag) {
  auto wire = wire::make_circle(r, topo_vector(), topo_vector(0, 0, 1));
  auto res = face::make_face(wire);

  return _each(
      [res](const topo_location &loc) {
        return *res.located(loc).cast<topo::face>();
      },
      mode, tag);
}

sketch &sketch::ellipse(double a1, double a2, double angle, Mode mode,
                        const boost::optional<std::string> &tag) {
  auto wire = wire::make_ellipse(a1, a2, topo_vector(), topo_vector(0, 0, 1),
                                 topo_vector(1, 0, 0), angle);
  auto res = face::make_face(wire);

  return _each(
      [res](const topo_location &loc) {
        return *res.located(loc).cast<topo::face>();
      },
      mode, tag);
}

sketch &sketch::trapezoid(double w, double h, double a1,
                          boost::optional<double> a2, double angle, Mode mode,
                          const boost::optional<std::string> &tag) {
  using namespace boost::math::constants;
  if (w <= 0 || h <= 0) {
    throw std::invalid_argument("Width and height must be positive");
  }

  if (a1 <= -90 || a1 >= 90) {
    throw std::invalid_argument("Angle a1 must be between -90 and 90 degrees");
  }

  if (a2 && (*a2 <= -90 || *a2 >= 90)) {
    throw std::invalid_argument("Angle a2 must be between -90 and 90 degrees");
  }
  auto tan_a1 = std::tan(a1 * pi<double>() / 180.0);
  auto tan_a2 = a2 ? std::tan(*a2 * pi<double>() / 180.0) : tan_a1;

  topo_vector v1(-w / 2, -h / 2);
  topo_vector v2(w / 2, -h / 2);
  topo_vector v3(-w / 2 + h / tan_a1, h / 2);
  topo_vector v4(w / 2 - h / tan_a2, h / 2);

  std::vector<topo_vector> pts = {v1, v2, v4, v3, v1};
  return polygon(pts, angle, mode, tag);
}

sketch &sketch::slot(double w, double h, double angle, Mode mode,
                     const boost::optional<std::string> &tag) {
  topo_vector p1(-w / 2, h / 2);
  topo_vector p2(w / 2, h / 2);
  topo_vector p3(-w / 2, -h / 2);
  topo_vector p4(w / 2, -h / 2);
  topo_vector p5(-w / 2 - h / 2, 0);
  topo_vector p6(w / 2 + h / 2, 0);

  auto e1 = edge::make_polygon(p1, p2);
  auto e2 = edge::make_three_point_arc(p2, p6, p4);
  auto e3 = edge::make_polygon(p4, p3);
  auto e4 = edge::make_three_point_arc(p3, p5, p1);

  auto wire = wire::make_wire({e1, e2, e3, e4});
  return _face(wire, angle, mode, tag);
}

sketch &sketch::regular_polygon(double r, int n, double angle, Mode mode,
                                const boost::optional<std::string> &tag) {
  using namespace boost::math::constants;

  std::vector<topo_vector> pts;
  pts.reserve(n + 1);

  for (int i = 0; i <= n; ++i) {
    double theta = i * 2 * pi<double>() / n;
    pts.emplace_back(r * std::sin(theta), r * std::cos(theta));
  }

  return polygon(pts, angle, mode, tag);
}

sketch &sketch::polygon(const std::vector<topo_vector> &pts, double angle,
                        Mode mode, const boost::optional<std::string> &tag) {
  std::vector<gp_Pnt> vertices;
  for (const auto &pt : pts) {
    vertices.push_back(gp_Pnt(pt.x(), pt.y(), pt.z()));
  }
  auto wire = wire::make_polygon(vertices, false);
  return _face(wire, angle, mode, tag);
}

sketch &sketch::rarray(double xs, double ys, int nx, int ny) {
  if (nx < 1 || ny < 1) {
    throw std::invalid_argument("At least 1 elements required");
  }

  std::vector<topo_location> locs;
  locs.reserve(nx * ny);

  auto offset = topo_vector((nx - 1) * xs, (ny - 1) * ys) * 0.5;

  for (int i = 0; i < nx; ++i) {
    for (int j = 0; j < ny; ++j) {
      auto loc = topo_location(topo_vector(i * xs, j * ys) - offset);
      locs.push_back(loc);
    }
  }

  std::vector<topo_location> selections;
  if (selection_) {
    for (auto &sel : *selection_) {
      if (auto loc = boost::get<topo_location>(&sel)) {
        selections.push_back(*loc);
      } else if (auto sh = boost::get<shape>(&sel)) {
        selections.push_back(topo_location(sh->centre_of_mass()));
      }
    }
  } else {
    selections.push_back(topo_location());
  }

  std::vector<topo_location> result_locs;
  for (auto &loc : locs) {
    for (auto &sel : selections) {
      result_locs.push_back(topo_location(loc * sel));
    }
  }

  return push(result_locs);
}

sketch &sketch::parray(double r, double a1, double da, int n, bool rotate) {
  using namespace boost::math::constants;

  if (n < 1) {
    throw std::invalid_argument("At least 1 element required");
  }

  double angle;
  if (std::fmod(da, 360.0) < TOL) {
    angle = da / n;
  } else {
    angle = (n > 1) ? da / (n - 1) : a1;
  }

  std::vector<topo_location> locs;
  locs.reserve(n);

  for (int i = 0; i < n; ++i) {
    double phi = a1 + (angle * i);
    double x = r * std::cos(phi * pi<double>() / 180.0);
    double y = r * std::sin(phi * pi<double>() / 180.0);

    auto loc = topo_location(topo_vector(x, y));
    locs.push_back(loc);
  }

  std::vector<topo_location> selections;
  if (selection_) {
    for (auto &sel : *selection_) {
      if (auto loc = boost::get<topo_location>(&sel)) {
        selections.push_back(*loc);
      } else if (auto sh = boost::get<shape>(&sel)) {
        selections.push_back(topo_location(sh->centre_of_mass()));
      }
    }
  } else {
    selections.push_back(topo_location());
  }

  std::vector<topo_location> result_locs;
  for (int i = 0; i < locs.size(); ++i) {
    for (auto &sel : selections) {
      auto rot = rotate ? (a1 + (angle * i)) : 0.0;
      auto final_loc = topo_location(
          locs[i] * sel *
          topo_location(topo_vector(), topo_vector(0, 0, 1), rot));
      result_locs.push_back(final_loc);
    }
  }

  return push(result_locs);
}

sketch &sketch::distribute(int n, double start, double stop, bool rotate) {
  if (n < 1) {
    throw std::invalid_argument("At least 1 element required");
  }

  if (stop < start) {
    throw std::invalid_argument("Stop value must be greater than start");
  }

  if (!selection_ || selection_->empty()) {
    throw std::invalid_argument("Selection is empty - nothing to distribute");
  }

  // 验证选择集中的类型
  for (const auto &sel : *selection_) {
    if (auto sh = boost::get<shape>(&sel)) {
      if (sh->shape_type() != TopAbs_EDGE && sh->shape_type() != TopAbs_WIRE) {
        throw std::invalid_argument(
            "Only edges and wires are supported for distribution");
      }
    }
  }

  if (!selection_ || selection_->empty()) {
    throw std::invalid_argument("Nothing selected to distribute over");
  }

  bool trimmed = (1.0 - std::abs(stop - start)) >= TOL;

  // Calculate parameters
  std::vector<double> params_closed;
  std::vector<double> params_open;

  if (!trimmed) {
    params_closed.reserve(n);
    for (int i = 0; i < n; ++i) {
      params_closed.push_back(start + i * (stop - start) / n);
    }
  } else {
    params_open.reserve(n);
    for (int i = 0; i < n; ++i) {
      params_open.push_back(n > 1 ? start + i * (stop - start) / (n - 1)
                                  : start);
    }
  }

  std::vector<topo_location> locs;
  for (auto &sel : *selection_) {
    if (auto sh = boost::get<shape>(&sel)) {
      if (sh->shape_type() == TopAbs_EDGE) {
        auto edge = sh->cast<topo::edge>();
        auto params =
            (!trimmed && edge->is_closed()) ? params_closed : params_open;

        if (rotate) {
          auto edge_locs = edge->locations(params, shape1d::ParamMode::LENGTH,
                                           shape1d::FrameMode::FRENET, true);
          locs.insert(locs.end(), edge_locs.begin(), edge_locs.end());
        } else {
          auto points = edge->positions(params);
          for (auto &p : points) {
            locs.push_back(topo_location(p));
          }
        }
      } else if (sh->shape_type() == TopAbs_WIRE) {
        auto wire = sh->cast<topo::wire>();
        auto params =
            (!trimmed && wire->is_closed()) ? params_closed : params_open;

        if (rotate) {
          auto wire_locs = wire->locations(params, shape1d::ParamMode::LENGTH,
                                           shape1d::FrameMode::FRENET, true);
          locs.insert(locs.end(), wire_locs.begin(), wire_locs.end());
        } else {
          auto points = wire->positions(params);
          for (auto &p : points) {
            locs.push_back(topo_location(p));
          }
        }
      }
    } else {
      throw std::invalid_argument("Unsupported selection type");
    }
  }

  return push(locs);
}

sketch &sketch::push(const std::vector<topo_location> &locs,
                     const boost::optional<std::string> &tag) {
  selection_.emplace();
  for (auto &loc : locs) {
    selection_->push_back(loc);
  }

  if (tag) {
    _tag(*selection_, *tag);
  }

  return *this;
}

sketch &sketch::each(std::function<topo::face(const topo_location &)> callback,
                     Mode mode, const std::string &tag, bool ignore_selection) {
  auto wrapped = [callback](const topo_location &loc)
      -> boost::variant<topo::face, std::shared_ptr<sketch>, compound> {
    return boost::variant<topo::face, std::shared_ptr<sketch>, compound>(
        callback(loc));
  };
  return _each(wrapped, mode,
               tag.empty() ? boost::none : boost::optional<std::string>(tag),
               ignore_selection);
}

sketch &sketch::each(
    std::function<std::shared_ptr<sketch>(const topo_location &)> callback,
    Mode mode, const std::string &tag, bool ignore_selection) {
  auto wrapped = [callback](const topo_location &loc)
      -> boost::variant<topo::face, std::shared_ptr<sketch>, compound> {
    return boost::variant<topo::face, std::shared_ptr<sketch>, compound>(
        callback(loc));
  };
  return _each(wrapped, mode,
               tag.empty() ? boost::none : boost::optional<std::string>(tag),
               ignore_selection);
}

sketch &sketch::each(std::function<compound(const topo_location &)> callback,
                     Mode mode, const std::string &tag, bool ignore_selection) {
  auto wrapped = [callback](const topo_location &loc)
      -> boost::variant<topo::face, std::shared_ptr<sketch>, compound> {
    return boost::variant<topo::face, std::shared_ptr<sketch>, compound>(
        callback(loc));
  };
  return _each(wrapped, mode,
               tag.empty() ? boost::none : boost::optional<std::string>(tag),
               ignore_selection);
}

sketch &sketch::_each(
    std::function<boost::variant<topo::face, std::shared_ptr<sketch>, compound>(
        const topo_location &)>
        callback,
    Mode mode, const boost::optional<std::string> &tag, bool ignore_selection) {
  std::vector<shape> res;
  std::vector<topo_location> locs;

  if (selection_ && !ignore_selection) {
    for (auto &sel : *selection_) {
      if (auto loc = boost::get<topo_location>(&sel)) {
        locs.push_back(*loc);
      } else if (auto sh = boost::get<shape>(&sel)) {
        locs.push_back(topo_location(sh->centre_of_mass()));
      }
    }
  } else {
    locs.push_back(topo_location());
  }

  for (auto &loc : locs) {
    auto tmp = callback(loc);

    if (auto sk = boost::get<std::shared_ptr<sketch>>(&tmp)) {
      auto faces = (*sk)->faces_->faces();
      res.insert(res.end(), faces.begin(), faces.end());
    } else if (auto comp = boost::get<compound>(&tmp)) {
      auto faces = comp->faces();
      res.insert(res.end(), faces.begin(), faces.end());
    } else if (auto f = boost::get<topo::face>(&tmp)) {
      res.push_back(*f);
    }
  }

  if (tag) {
    _tag(res, *tag);
  }

  switch (mode) {
  case Mode::ADD:
    faces_ = faces_->fuse(res);
    break;
  case Mode::SUBTRACT:
    faces_ = faces_->cut(res);
    break;
  case Mode::INTERSECT:
    faces_ = faces_->intersect(res);
    break;
  case Mode::REPLACE:
    faces_ = compound::make_compound(res);
    break;
  case Mode::CONSTRUCT:
    if (!tag)
      throw std::invalid_argument(
          "No tag specified - the geometry will be unreachable");
    break;
  default:
    throw std::invalid_argument("Invalid mode");
  }

  return *this;
}

sketch &sketch::hull(Mode mode, const boost::optional<std::string> &tag) {
  std::vector<topo::edge> edges;

  if (selection_) {
    for (auto &sel : *selection_) {
      if (auto shp = boost::get<shape>(&sel)) {
        if (shp->shape_type() == TopAbs_EDGE) {
          edges.push_back(*shp->cast<topo::edge>());
        }
      }
    }
  } else if (faces_ && faces_->num_faces() > 0) {
    edges = faces_->edges();
  } else if (!edges_.empty()) {
    edges = edges_;
  } else {
    throw std::invalid_argument("No objects available for hull construction");
  }

  auto hull_edges = find_hull(edges);
  return _face(hull_edges, 0.0, mode, tag, (bool)(selection_));
}

sketch &sketch::offset(double d, Mode mode,
                       const boost::optional<std::string> &tag) {
  if (!selection_ || selection_->empty()) {
    throw std::invalid_argument("Selection is needed to offset");
  }

  for (auto &sel : *selection_) {
    if (auto shp = boost::get<shape>(&sel)) {
      if (shp->shape_type() == TopAbs_WIRE) {
        auto wire = shp->cast<topo::wire>();
        auto offset_wires = wire->offset2d(d);
        for (auto &ow : offset_wires) {
          _face(ow, 0.0, mode, tag, true);
        }
      }
    }
  }

  return *this;
}

std::unordered_map<topo::face, std::vector<vertex>>
sketch::_match_faces_to_vertices() {
  std::unordered_map<topo::face, std::vector<vertex>> result;

  if (!selection_ || selection_->empty()) {
    throw std::invalid_argument(
        "Selection is needed to match vertices to faces");
  }

  auto faces = faces_->faces();
  for (auto &f : faces) {
    auto f_vertices = f.vertices();
    std::vector<vertex> matched_vertices;

    for (auto &sel : *selection_) {
      if (auto shp = boost::get<shape>(&sel)) {
        if (shp->shape_type() == TopAbs_VERTEX) {
          auto v = shp->cast<topo::vertex>();
          if (std::find(f_vertices.begin(), f_vertices.end(), *v) !=
              f_vertices.end()) {
            matched_vertices.push_back(*v);
          }
        }
      }
    }

    result[f] = matched_vertices;
  }

  return result;
}

sketch &sketch::fillet(double d) {
  auto f2v = _match_faces_to_vertices();

  std::vector<shape> new_faces;
  for (auto &pair : f2v) {
    if (!pair.second.empty()) {
      new_faces.push_back(pair.first.fillet2d(d, pair.second));
    } else {
      new_faces.push_back(pair.first);
    }
  }

  faces_ = compound::make_compound(new_faces);
  return *this;
}

sketch &sketch::chamfer(double d) {
  auto f2v = _match_faces_to_vertices();

  std::vector<shape> new_faces;
  for (auto &pair : f2v) {
    if (!pair.second.empty()) {
      new_faces.push_back(pair.first.chamfer2d(d, pair.second));
    } else {
      new_faces.push_back(pair.first);
    }
  }

  faces_ = compound::make_compound(new_faces);
  return *this;
}

sketch &sketch::clean() {
  faces_ = *faces_->clean().cast<compound>();
  return *this;
}

std::vector<sketch_val> sketch::_unique(const std::vector<sketch_val> &vals) {
  std::unordered_map<size_t, sketch_val> tmp;
  for (const auto &val : vals) {
    size_t hash = 0;
    if (auto sh = boost::get<shape>(&val)) {
      hash = sh->hash_code();
      tmp[hash] = *sh;
    } else if (auto loc = boost::get<topo_location>(&val)) {
      hash = loc->hash_code();
      tmp[hash] = *loc;
    }
  }

  std::vector<sketch_val> result;
  result.reserve(tmp.size());
  for (auto &pair : tmp) {
    result.push_back(pair.second);
  }
  return result;
}

sketch &sketch::select(
    const boost::optional<boost::variant<std::string, selector_ptr>> &s,
    const std::string &kind, const boost::optional<std::string> &tag) {
  std::vector<sketch_val> rv;

  if (tag) {
    auto it = tags_.find(*tag);
    if (it != tags_.end()) {
      for (auto &el : it->second) {
        if (auto sh = boost::get<shape>(&el)) {
          if (kind == "Faces") {
            auto faces = sh->faces();
            rv.insert(rv.end(), faces.begin(), faces.end());
          } else if (kind == "Wires") {
            auto wires = sh->wires();
            rv.insert(rv.end(), wires.begin(), wires.end());
          } else if (kind == "Edges") {
            auto edges = sh->edges();
            rv.insert(rv.end(), edges.begin(), edges.end());
          } else if (kind == "Vertices") {
            auto vertices = sh->vertices();
            rv.insert(rv.end(), vertices.begin(), vertices.end());
          }
        }
      }
    }
  } else if (selection_) {
    for (auto &el : *selection_) {
      if (auto sh = boost::get<shape>(&el)) {
        if (kind == "Faces") {
          auto faces = sh->faces();
          rv.insert(rv.end(), faces.begin(), faces.end());
        } else if (kind == "Wires") {
          auto wires = sh->wires();
          rv.insert(rv.end(), wires.begin(), wires.end());
        } else if (kind == "Edges") {
          auto edges = sh->edges();
          rv.insert(rv.end(), edges.begin(), edges.end());
        } else if (kind == "Vertices") {
          auto vertices = sh->vertices();
          rv.insert(rv.end(), vertices.begin(), vertices.end());
        }
      }
    }
  } else {
    if (kind == "Faces") {
      auto faces = faces_->faces();
      rv.insert(rv.end(), faces.begin(), faces.end());
    } else if (kind == "Wires") {
      auto wires = faces_->wires();
      rv.insert(rv.end(), wires.begin(), wires.end());
    } else if (kind == "Edges") {
      auto edges = faces_->edges();
      rv.insert(rv.end(), edges.begin(), edges.end());
    } else if (kind == "Vertices") {
      auto vertices = faces_->vertices();
      rv.insert(rv.end(), vertices.begin(), vertices.end());
    }

    for (auto &edge : edges_) {
      if (kind == "Edges") {
        rv.push_back(edge);
      } else if (kind == "Vertices") {
        auto vertices = edge.vertices();
        rv.insert(rv.end(), vertices.begin(), vertices.end());
      }
    }
  }

  std::vector<sketch_val> filtered;

  if (s) {
    if (auto str = boost::get<std::string>(&*s)) {
      string_syntax_selector selector_(*str);
      std::vector<shape> shapes;
      for (auto &val : rv) {
        if (auto sh = boost::get<shape>(&val)) {
          shapes.push_back(*sh);
        }
      }

      shapes = selector_.filter(shapes);
      for (auto &sh : shapes) {
        filtered.push_back(sh);
      }
    } else if (auto sel = boost::get<selector_ptr>(&*s)) {
      std::vector<shape> shapes;
      for (auto &val : rv) {
        if (auto sh = boost::get<shape>(&val)) {
          shapes.push_back(*sh);
        }
      }

      shapes = (*sel)->filter(shapes);
      for (auto &sh : shapes) {
        filtered.push_back(sh);
      }
    }
  } else {
    filtered = rv;
  }

  selection_ = _unique(filtered);

  return *this;
}

sketch &sketch::tag(const std::string &tag) {
  if (!selection_ || selection_->empty()) {
    throw std::invalid_argument("Selection is needed to tag");
  }

  tags_[tag] = *selection_;
  return *this;
}

sketch &sketch::select(const std::vector<std::string> &tags) {
  selection_.emplace();
  for (auto &tag : tags) {
    auto it = tags_.find(tag);
    if (it != tags_.end()) {
      selection_->insert(selection_->end(), it->second.begin(),
                         it->second.end());
    }
  }
  return *this;
}

sketch &sketch::faces(const std::string &sel, const std::string &tag) {
  return _faces(
      sel.empty()
          ? boost::none
          : boost::optional<boost::variant<std::string, selector_ptr>>(sel),
      tag.empty() ? boost::none : boost::optional<std::string>(tag));
}

sketch &sketch::faces(const selector_ptr &sel, const std::string &tag) {
  return _faces(boost::variant<std::string, selector_ptr>(sel),
                tag.empty() ? boost::none : boost::optional<std::string>(tag));
}

sketch &sketch::wires(const std::string &sel, const std::string &tag) {
  return _wires(
      sel.empty()
          ? boost::none
          : boost::optional<boost::variant<std::string, selector_ptr>>(sel),
      tag.empty() ? boost::none : boost::optional<std::string>(tag));
}

sketch &sketch::wires(const selector_ptr &sel, const std::string &tag) {
  return _wires(boost::variant<std::string, selector_ptr>(sel),
                tag.empty() ? boost::none : boost::optional<std::string>(tag));
}

sketch &sketch::edges(const std::string &sel, const std::string &tag) {
  return _edges(
      sel.empty()
          ? boost::none
          : boost::optional<boost::variant<std::string, selector_ptr>>(sel),
      tag.empty() ? boost::none : boost::optional<std::string>(tag));
}

sketch &sketch::edges(const selector_ptr &sel, const std::string &tag) {
  return _edges(boost::variant<std::string, selector_ptr>(sel),
                tag.empty() ? boost::none : boost::optional<std::string>(tag));
}

sketch &sketch::vertices(const std::string &sel, const std::string &tag) {
  return _vertices(
      sel.empty()
          ? boost::none
          : boost::optional<boost::variant<std::string, selector_ptr>>(sel),
      tag.empty() ? boost::none : boost::optional<std::string>(tag));
}

sketch &sketch::vertices(const selector_ptr &sel, const std::string &tag) {
  return _vertices(boost::variant<std::string, selector_ptr>(sel),
                   tag.empty() ? boost::none
                               : boost::optional<std::string>(tag));
}

sketch &sketch::_faces(
    const boost::optional<boost::variant<std::string, selector_ptr>> &s,
    const boost::optional<std::string> &tag) {
  return select(s, "Faces", tag);
}

sketch &sketch::_wires(
    const boost::optional<boost::variant<std::string, selector_ptr>> &s,
    const boost::optional<std::string> &tag) {
  return select(s, "Wires", tag);
}

sketch &sketch::_edges(
    const boost::optional<boost::variant<std::string, selector_ptr>> &s,
    const boost::optional<std::string> &tag) {
  return select(s, "Edges", tag);
}

sketch &sketch::_vertices(
    const boost::optional<boost::variant<std::string, selector_ptr>> &s,
    const boost::optional<std::string> &tag) {
  return select(s, "Vertices", tag);
}

sketch &sketch::reset() {
  selection_.reset();
  return *this;
}

sketch &sketch::delete_selected() {
  if (!selection_ || selection_->empty()) {
    throw std::invalid_argument("Selection is needed to delete");
  }

  for (auto &sel : *selection_) {
    if (auto sh = boost::get<shape>(&sel)) {
      if (sh->shape_type() == TopAbs_FACE) {
        faces_->cast<topo::compound>()->remove(*sh->cast<topo::face>());
      } else if (sh->shape_type() == TopAbs_EDGE) {
        auto edge = sh->cast<topo::edge>();
        edges_.erase(std::remove(edges_.begin(), edges_.end(), *edge),
                     edges_.end());
      }
    } else {
      throw std::invalid_argument("Deletion of this object type not supported");
    }
  }

  return reset();
}

topo_vector sketch::start_point() {
  if (edges_.empty()) {
    throw std::invalid_argument("No free edges available");
  }
  return edges_.front().start_point();
}

topo_vector sketch::end_point() {
  if (edges_.empty()) {
    throw std::invalid_argument("No free edges available");
  }
  return edges_.back().end_point();
}

sketch &sketch::edge(const topo::edge &val,
                     const boost::optional<std::string> &tag,
                     bool for_construction) {
  const_cast<topo::edge &>(val).set_for_construction(for_construction);
  edges_.push_back(val);

  if (tag) {
    _tag({sketch_val(val)}, *tag);
  }

  return *this;
}

sketch &sketch::segment(const topo_vector &p1, const topo_vector &p2,
                        const boost::optional<std::string> &tag,
                        bool for_construction) {
  auto val = edge::make_edge(p1, p2);
  return edge(val, tag, for_construction);
}

sketch &sketch::segment(const topo_vector &p2,
                        const boost::optional<std::string> &tag,
                        bool for_construction) {
  auto p1 = end_point();
  return segment(p1, p2, tag, for_construction);
}

sketch &sketch::segment(double length, double angle,
                        const boost::optional<std::string> &tag,
                        bool for_construction) {
  using namespace boost::math::constants;

  auto p1 = end_point();
  auto dx = length * std::cos(angle * pi<double>() / 180.0);
  auto dy = length * std::sin(angle * pi<double>() / 180.0);
  auto p2 = p1 + topo_vector(dx, dy);

  return segment(p1, p2, tag, for_construction);
}

sketch &sketch::arc(const topo_vector &p1, const topo_vector &p2,
                    const topo_vector &p3,
                    const boost::optional<std::string> &tag,
                    bool for_construction) {
  auto val = edge::make_three_point_arc(p1, p2, p3);
  return edge(val, tag, for_construction);
}

sketch &sketch::arc(const topo_vector &p2, const topo_vector &p3,
                    const boost::optional<std::string> &tag,
                    bool for_construction) {
  auto p1 = end_point();
  return arc(p1, p2, p3, tag, for_construction);
}

sketch &sketch::arc(const topo_vector &center, double radius,
                    double start_angle, double delta_angle,
                    const boost::optional<std::string> &tag,
                    bool for_construction) {
  using namespace boost::math::constants;

  if (std::abs(delta_angle) >= 360.0) {
    auto val = edge::make_circle(radius, center, gp_Dir(0, 0, 1), start_angle,
                                 start_angle, delta_angle > 0);
    return edge(val, tag, for_construction);
  } else {
    auto p0 = center;
    auto angle1 = start_angle * pi<double>() / 180.0;
    auto angle2 = (start_angle + delta_angle / 2) * pi<double>() / 180.0;
    auto angle3 = (start_angle + delta_angle) * pi<double>() / 180.0;

    auto p1 = p0 + radius * topo_vector(std::cos(angle1), std::sin(angle1));
    auto p2 = p0 + radius * topo_vector(std::cos(angle2), std::sin(angle2));
    auto p3 = p0 + radius * topo_vector(std::cos(angle3), std::sin(angle3));

    return arc(p1, p2, p3, tag, for_construction);
  }
}

sketch &sketch::spline(
    const std::vector<topo_vector> &points,
    const boost::optional<std::pair<topo_vector, topo_vector>> &tangents,
    bool periodic, const boost::optional<std::string> &tag,
    bool for_construction) {
  std::vector<gp_Pnt> vertices;
  for (const auto &p : points) {
    vertices.push_back(p);
  }
  std::pair<gp_Vec, gp_Vec> tangents_;
  if (tangents) {
    tangents_ = std::make_pair(tangents->first, tangents->second);
  }

  auto val = edge::make_spline(vertices, &tangents_, nullptr, 1.0E-6, periodic);
  return edge(val, tag, for_construction);
}

sketch &sketch::spline(const std::vector<topo_vector> &points,
                       const boost::optional<std::string> &tag,
                       bool for_construction) {
  return spline(points, boost::none, false, tag, for_construction);
}

sketch &sketch::bezier(const std::vector<topo_vector> &points,
                       const boost::optional<std::string> &tag,
                       bool for_construction) {
  std::vector<gp_Pnt> vertices;
  for (const auto &p : points) {
    vertices.push_back(p);
  }
  auto val = edge::make_bezier(vertices);
  return edge(val, tag, for_construction);
}

sketch &sketch::close(const boost::optional<std::string> &tag) {
  auto p1 = end_point();
  auto p2 = start_point();
  return segment(p1, p2, tag);
}

sketch &sketch::assemble(Mode mode, const boost::optional<std::string> &tag) {
  std::vector<topo::edge> construction_edges;
  for (const auto &e : edges_) {
    if (!e.for_construction()) {
      construction_edges.push_back(e);
    }
  }
  return _face(construction_edges, 0.0, mode, tag);
}

sketch &sketch::constrain(const std::string &tag,
                          sketch_constraint_kind constraint,
                          const sketch_constraint_value &arg) {
  auto it = tags_.find(tag);
  if (it == tags_.end() || it->second.empty()) {
    throw std::invalid_argument("Invalid tag specified");
  }

  auto edge = boost::get<shape>(&it->second[0]);
  if (!edge || edge->shape_type() != TopAbs_EDGE) {
    throw std::invalid_argument("Tag does not reference an edge");
  }

  constraints_.emplace_back(
      std::vector<std::string>({tag}),
      std::vector<topo::edge>({*edge->cast<topo::edge>()}), constraint, arg);
  return *this;
}

sketch &sketch::constrain(const std::string &tag1, const std::string &tag2,
                          sketch_constraint_kind constraint,
                          const sketch_constraint_value &arg) {
  auto it1 = tags_.find(tag1);
  auto it2 = tags_.find(tag2);
  if (it1 == tags_.end() || it1->second.empty() || it2 == tags_.end() ||
      it2->second.empty()) {
    throw std::invalid_argument("Invalid tags specified");
  }

  auto edge1 = boost::get<shape>(it1->second[0]);
  auto edge2 = boost::get<shape>(it2->second[0]);
  if (!edge1 || !edge2 || edge1.shape_type() != TopAbs_EDGE ||
      edge2.shape_type() != TopAbs_EDGE) {
    throw std::invalid_argument("Tags must reference edges");
  }

  constraints_.emplace_back(
      (tag1, tag2), (*edge1.cast<topo::edge>(), *edge2.cast<topo::edge>()),
      constraint, arg);
  return *this;
}

sketch &sketch::solve() {
  std::vector<sketch_dof> entities;
  std::unordered_map<std::string, size_t> e2i;
  std::vector<geom_type> geoms;

  for (const auto &pair : tags_) {
    if (pair.second.empty())
      continue;

    if (auto shp = boost::get<topo::shape>(pair.second[0])) {
      if (shp.shape_type() == TopAbs_EDGE) {
        auto edge = shp.cast<topo::edge>();
        auto geom_type = edge->geom_type();

        if (geom_type == shape_geom_line) {
          auto p1 = edge->start_point();
          auto p2 = edge->end_point();
          entities.push_back(segment_dof{p1.X(), p1.Y(), p2.X(), p2.Y()});
          e2i[pair.first] = entities.size() - 1;
          geoms.push_back(geom_type::LINE);
        } else if (geom_type == shape_geom_circle) {
          auto center = edge->arc_center();
          auto p1 = topo_vector(edge->start_point()) - center;
          auto p2 = topo_vector(edge->end_point()) - center;
          auto pm = topo_vector(edge->position_at(0.5)) - center;

          auto a1 = topo_vector(0, 1).get_signed_angle(p1);
          auto a2 = p1.get_signed_angle(p2);
          auto a3 = p1.get_signed_angle(pm);

          if (a3 > 0 && a2 < 0)
            a2 += 2 * M_PI;
          else if (a3 < 0 && a2 > 0)
            a2 -= 2 * M_PI;

          entities.push_back(
              arc_dof{center.X(), center.Y(), edge->radius(), a1, a2});
          e2i[pair.first] = entities.size() - 1;
          geoms.push_back(geom_type::CIRCLE);
        }
      }
    }
  }

  std::vector<sketch_constraint> constraint_list;
  for (const auto &c : constraints_) {
    auto tag1 = c.tags[0];
    auto idx1 = e2i[tag1];

    if (c.tags.size() == 1) {
      std::pair<size_t, boost::optional<size_t>> entities{
          idx1, boost::optional<size_t>()};
      sketch_constraint constraint = {entities, c.kind, c.param};
      constraint_list.emplace_back(constraint);
    } else {
      auto tag2 = c.tags[1];
      auto idx2 = e2i[tag2];
      std::pair<size_t, boost::optional<size_t>> entities{idx1, idx2};
      sketch_constraint constraint = {entities, c.kind, c.param};
      constraint_list.emplace_back(constraint);
    }
  }

  sketch_solver solver(entities, constraint_list, geoms);
  auto result = solver.solve();
  for (const auto &pair : result.second) {
    solve_status_[pair.first] = pair.second;
  }
  solve_status_["x"] = result.first;

  for (const auto &combined : boost::combine(geoms, e2i)) {
    const auto &geom_type = boost::get<0>(combined);
    const auto &kv = boost::get<1>(combined);
    const auto tag = kv.first;
    const auto idx = kv.second;
    const auto &sol = result.first[idx];

    if (geom_type == geom_type::LINE) {
      auto p1 = topo_vector(sol[0], sol[1]);
      auto p2 = topo_vector(sol[2], sol[3]);
      auto new_edge = edge::make_edge(p1, p2);
      tags_[tag][0] = new_edge;
    } else if (geom_type == geom_type::CIRCLE) {
      arc_dof dof = arc_dof{{sol[0], sol[1], sol[2], sol[3], sol[4]}};
      auto p1 = arc_first(dof);
      auto p2 = arc_point(dof, 0.5);
      auto p3 = arc_last(dof);
      auto new_edge = edge::make_three_point_arc(gp_Pnt(p1.X(), p1.Y(), 0),
                                                 gp_Pnt(p2.X(), p2.Y(), 0),
                                                 gp_Pnt(p3.X(), p3.Y(), 0));
      tags_[tag][0] = new_edge;
    }
  }

  return *this;
}

std::shared_ptr<sketch> sketch::copy() const {
  std::shared_ptr<sketch> result = std::make_shared<sketch>();
  result->faces_ = *faces_->copy().cast<compound>();
  return result;
}

std::shared_ptr<sketch>
sketch::moved(const std::vector<topo_location> &locs) const {
  std::shared_ptr<sketch> result = std::make_shared<sketch>();
  result->faces_ = *faces_->moved(locs).cast<topo::compound>();
  return result;
}

std::shared_ptr<sketch> sketch::located(const topo_location &loc) const {
  std::shared_ptr<sketch> result =
      std::make_shared<sketch>(std::vector<topo_location>({loc}));
  result->faces_ = *faces_->copy().cast<compound>();
  return result;
}

std::shared_ptr<workplane> sketch::finalize() { return parent_; }

sketch_val sketch::val() const {
  if (selection_ && !selection_->empty()) {
    return selection_->front();
  } else if (faces_ && !edges_.empty()) {
    return edges_.front();
  }
  if (faces_) {
    return *faces_;
  }
  return {};
}

std::vector<sketch_val> sketch::vals() const {
  if (selection_) {
    return *selection_;
  } else if (faces_ && !edges_.empty()) {
    return std::vector<sketch_val>(edges_.begin(), edges_.end());
  }
  if (faces_) {
    return std::vector<sketch_val>{*faces_};
  }
  return {};
}

sketch &sketch::add() {
  if (!selection_ || selection_->empty()) {
    throw std::invalid_argument("Nothing selected to add");
  }

  std::vector<shape> faces;
  for (const auto &sel : *selection_) {
    if (auto sh = boost::get<shape>(&sel)) {
      auto sel_faces = sh->faces();
      faces.insert(faces.end(), sel_faces.begin(), sel_faces.end());
    }
  }

  faces_ = faces_->fuse(faces);
  return *this;
}

sketch &sketch::subtract() {
  if (!selection_ || selection_->empty()) {
    throw std::invalid_argument("Nothing selected to subtract");
  }

  std::vector<shape> faces;
  for (const auto &sel : *selection_) {
    if (auto sh = boost::get<shape>(&sel)) {
      auto sel_faces = sh->faces();
      faces.insert(faces.end(), sel_faces.begin(), sel_faces.end());
    }
  }

  faces_ = faces_->cut(faces);
  return *this;
}

sketch &sketch::replace() {
  if (!selection_ || selection_->empty()) {
    throw std::invalid_argument("Nothing selected to replace with");
  }

  std::vector<topo::shape> faces;
  for (const auto &sel : *selection_) {
    if (auto sh = boost::get<shape>(&sel)) {
      auto sel_faces = sh->faces();
      faces.insert(faces.end(), sel_faces.begin(), sel_faces.end());
    }
  }

  faces_ = compound::make_compound(faces);
  return *this;
}

sketch sketch::operator+(const sketch &other) const {
  auto this_val = sanitize_for_bool(val());
  auto other_val = sanitize_for_bool(other.val());
  auto res = topo::fuse({this_val, other_val});
  return sketch(nullptr, {}, to_compound(*res));
}

sketch sketch::operator-(const sketch &other) const {
  auto this_val = sanitize_for_bool(val());
  auto other_val = sanitize_for_bool(other.val());
  auto res = topo::cut(this_val, other_val);
  return sketch(nullptr, {}, to_compound(*res));
}

sketch sketch::operator*(const sketch &other) const {
  auto this_val = sanitize_for_bool(val());
  auto other_val = sanitize_for_bool(other.val());
  auto res = topo::intersect(this_val, other_val);
  return sketch(nullptr, {}, to_compound(*res));
}

sketch sketch::operator/(const sketch &other) const {
  auto this_val = sanitize_for_bool(val());
  auto other_val = sanitize_for_bool(other.val());
  auto res = topo::split(this_val, other_val);
  return sketch(nullptr, {}, to_compound(*res));
}

// Selection operations
sketch &sketch::operator[](const std::vector<int> &indices) {
  auto all_vals = vals();
  selection_.emplace();
  for (auto i : indices) {
    if (i >= 0 && i < all_vals.size()) {
      selection_->push_back(all_vals[i]);
    }
  }
  return *this;
}

sketch &sketch::filter(std::function<bool(const sketch_val &)> pred) {
  auto all_vals = vals();
  selection_.emplace();
  std::copy_if(all_vals.begin(), all_vals.end(),
               std::back_inserter(*selection_), pred);
  return *this;
}

sketch &sketch::map(std::function<sketch_val(const sketch_val &)> f) {
  if (!selection_) {
    selection_ = vals();
  }

  for (auto &sel : *selection_) {
    sel = f(sel);
  }
  return *this;
}

sketch &sketch::apply(
    std::function<std::vector<sketch_val>(const std::vector<sketch_val> &)> f) {
  auto all_vals = vals();
  selection_ = f(all_vals);
  return *this;
}

sketch &
sketch::sort(std::function<bool(const sketch_val &, const sketch_val &)> comp) {
  if (!selection_) {
    selection_ = vals();
  }

  std::sort(selection_->begin(), selection_->end(), comp);
  return *this;
}

sketch &sketch::invoke(std::function<void()> f) {
  f();
  return *this;
}

sketch &sketch::invoke(std::function<void(sketch &)> f) {
  f(*this);
  return *this;
}

sketch &sketch::invoke(std::function<sketch &(sketch &)> f) { return f(*this); }

shape sketch::sanitize_for_bool(const sketch_val &val) const {
  if (auto loc = boost::get<topo_location>(&val)) {
    throw std::invalid_argument(
        "Location cannot be used in boolean operations");
  }
  return boost::get<shape>(val);
}

boost::optional<flywave::topo::compound>
sketch::to_compound(const shape &sh) const {
  if (sh.shape_type() == TopAbs_COMPOUND) {
    return sh.cast<flywave::topo::compound>();
  }
  return compound::make_compound({sh});
}

void sketch::set_error(const std::string &msg) {
  return this->parent_->ctx()->set_error(msg);
}

bool sketch::has_error() const { return this->parent_->has_error(); }

const std::string &sketch::error() const { return this->parent_->error(); }

} // namespace topo
} // namespace flywave
