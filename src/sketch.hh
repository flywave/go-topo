#pragma once

#include <boost/any.hpp>
#include <boost/optional.hpp>
#include <boost/variant.hpp>

#include <cmath>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "compound.hh"
#include "edge.hh"
#include "face.hh"
#include "location.hh"
#include "selector.hh"
#include "sketch_solver.hh"
#include "vector.hh"
#include "vertex.hh"
#include "wire.hh"

namespace flywave {
namespace topo {

class shape;
class face;
class edge;
class wire;
class compound;
class vertex;
class topo_location;
class workplane;

using sketch_val = boost::variant<shape, topo_location>;

enum class Mode { ADD, SUBTRACT, INTERSECT, CONSTRUCT, REPLACE };

class sketch;

class sketch : public std::enable_shared_from_this<sketch> {
public:
  sketch();
  sketch(std::shared_ptr<workplane> inPlane,
         const std::vector<topo_location> &locs = {topo_location()},
         boost::optional<compound> obj = boost::none);
  sketch(const std::vector<topo_location> &locs,
         boost::optional<compound> obj = boost::none);

  sketch(const sketch &) = delete;
  sketch &operator=(const sketch &) = delete;

  ~sketch() = default;

  sketch(sketch &&) noexcept;
  sketch &operator=(sketch &&) noexcept;

  int hash_code() const;

  std::vector<topo::face> get_faces() const;

  sketch &face(const wire &w, double angle = 0, Mode mode = Mode::ADD,
               const std::string &tag = "", bool ignore_selection = false);
  sketch &face(const std::vector<topo::edge> &edges, double angle = 0,
               Mode mode = Mode::ADD, const std::string &tag = "",
               bool ignore_selection = false);
  sketch &face(const shape &sh, double angle = 0, Mode mode = Mode::ADD,
               const std::string &tag = "", bool ignore_selection = false);
  sketch &face(const std::shared_ptr<sketch> &sk, double angle = 0,
               Mode mode = Mode::ADD, const std::string &tag = "",
               bool ignore_selection = false);

  sketch &rect(double w, double h, double angle = 0, Mode mode = Mode::ADD,
               const boost::optional<std::string> &tag = boost::none);
  sketch &circle(double r, Mode mode,
                 const boost::optional<std::string> &tag = boost::none);
  sketch &ellipse(double a1, double a2, double angle, Mode mode,
                  const boost::optional<std::string> &tag = boost::none);
  sketch &trapezoid(double w, double h, double a1, boost::optional<double> a2,
                    double angle, Mode mode = Mode::ADD,
                    const boost::optional<std::string> &tag = boost::none);
  sketch &slot(double w, double h, double angle, Mode mode = Mode::ADD,
               const boost::optional<std::string> &tag = boost::none);
  sketch &
  regular_polygon(double r, int n, double angle, Mode mode = Mode::ADD,
                  const boost::optional<std::string> &tag = boost::none);
  sketch &polygon(const std::vector<topo_vector> &pts, double angle,
                  Mode mode = Mode::ADD,
                  const boost::optional<std::string> &tag = boost::none);

  sketch &rarray(double xs, double ys, int nx, int ny);
  sketch &parray(double r, double a1, double da, int n, bool rotate = true);
  sketch &distribute(int n, double start = 0, double stop = 1,
                     bool rotate = true);

  sketch &push(const std::vector<topo_location> &locs,
               const boost::optional<std::string> &tag = boost::none);

  sketch &each(std::function<topo::face(const topo_location &)> callback,
               Mode mode = Mode::ADD, const std::string &tag = "",
               bool ignore_selection = false);
  sketch &
  each(std::function<std::shared_ptr<sketch>(const topo_location &)> callback,
       Mode mode = Mode::ADD, const std::string &tag = "",
       bool ignore_selection = false);
  sketch &each(std::function<compound(const topo_location &)> callback,
               Mode mode = Mode::ADD, const std::string &tag = "",
               bool ignore_selection = false);

  sketch &hull(Mode mode,
               const boost::optional<std::string> &tag = boost::none);
  sketch &offset(double d, Mode mode,
                 const boost::optional<std::string> &tag = boost::none);
  sketch &fillet(double d);
  sketch &chamfer(double d);

  sketch &clean();

  sketch &tag(const std::string &tag);
  sketch &select(const std::vector<std::string> &tags);
  sketch &faces(const std::string &selector, const std::string &tag = "");
  sketch &faces(const selector_ptr &sel, const std::string &tag = "");
  sketch &wires(const std::string &selector, const std::string &tag = "");
  sketch &wires(const selector_ptr &sel, const std::string &tag = "");
  sketch &edges(const std::string &selector, const std::string &tag = "");
  sketch &edges(const selector_ptr &sel, const std::string &tag = "");
  sketch &vertices(const std::string &selector, const std::string &tag = "");
  sketch &vertices(const selector_ptr &sel, const std::string &tag = "");

  sketch &reset();

  sketch &delete_selected();

  sketch &edge(const topo::edge &val,
               const boost::optional<std::string> &tag = boost::none,
               bool forConstruction = false);

  sketch &segment(const topo_vector &p1, const topo_vector &p2,
                  const boost::optional<std::string> &tag = boost::none,
                  bool forConstruction = false);
  sketch &segment(const topo_vector &p2,
                  const boost::optional<std::string> &tag = boost::none,
                  bool forConstruction = false);
  sketch &segment(double l, double a,
                  const boost::optional<std::string> &tag = boost::none,
                  bool forConstruction = false);
  sketch &arc(const topo_vector &p1, const topo_vector &p2,
              const topo_vector &p3, const boost::optional<std::string> &tag,
              bool for_construction);
  sketch &arc(const topo_vector &p2, const topo_vector &p3,
              const boost::optional<std::string> &tag, bool for_construction);
  sketch &arc(const topo_vector &center, double radius, double start_angle,
              double delta_angle, const boost::optional<std::string> &tag,
              bool for_construction);
  sketch &
  spline(const std::vector<topo_vector> &points,
         const boost::optional<std::pair<topo_vector, topo_vector>> &tangents,
         bool periodic, const boost::optional<std::string> &tag,
         bool for_construction);
  sketch &spline(const std::vector<topo_vector> &points,
                 const boost::optional<std::string> &tag,
                 bool for_construction);
  sketch &bezier(const std::vector<topo_vector> &points,
                 const boost::optional<std::string> &tag,
                 bool for_construction);
  sketch &close(const boost::optional<std::string> &tag);
  sketch &assemble(Mode mode, const boost::optional<std::string> &tag);

  sketch &constrain(const std::string &tag, sketch_constraint_kind constraint,
                    const sketch_constraint_value &arg);
  sketch &constrain(const std::string &tag1, const std::string &tag2,
                    sketch_constraint_kind constraint,
                    const sketch_constraint_value &arg);
  sketch &solve();

  std::shared_ptr<sketch> copy() const;
  std::shared_ptr<sketch> moved(const std::vector<topo_location> &locs) const;
  std::shared_ptr<sketch> located(const topo_location &loc) const;
  std::shared_ptr<workplane> finalize();

  sketch_val val() const;
  std::vector<sketch_val> vals() const;

  sketch &add();
  sketch &subtract();
  sketch &replace();

  sketch operator+(const sketch &other) const;
  sketch operator-(const sketch &other) const;
  sketch operator*(const sketch &other) const;
  sketch operator/(const sketch &other) const;
  sketch &operator[](const std::vector<int> &indices);

  sketch &filter(std::function<bool(const sketch_val &)> pred);
  sketch &map(std::function<sketch_val(const sketch_val &)> f);

  sketch &
  apply(std::function<std::vector<sketch_val>(const std::vector<sketch_val> &)>
            f);
  sketch &
  sort(std::function<bool(const sketch_val &, const sketch_val &)> comp);

  sketch &invoke(std::function<void()> f);
  sketch &invoke(std::function<void(sketch &)> f);
  sketch &invoke(std::function<sketch &(sketch &)> f);

  void set_error(const std::string &msg);
  bool has_error() const;
  const std::string &error() const;

protected:
  sketch &
  _each(std::function<boost::variant<topo::face, std::shared_ptr<sketch>,
                                     compound>(const topo_location &)>
            callback,
        Mode mode = Mode::ADD,
        const boost::optional<std::string> &tag = boost::none,
        bool ignore_selection = false);
  sketch &_face(boost::variant<wire, std::vector<topo::edge>, shape,
                               std::shared_ptr<sketch>>
                    b,
                double angle = 0, Mode mode = Mode::ADD,
                const boost::optional<std::string> &tag = boost::none,
                bool ignore_selection = false);

  sketch &
  _faces(const boost::optional<boost::variant<std::string, selector_ptr>> &s =
             boost::none,
         const boost::optional<std::string> &tag = boost::none);
  sketch &
  _wires(const boost::optional<boost::variant<std::string, selector_ptr>> &s,
         const boost::optional<std::string> &tag = boost::none);
  sketch &
  _edges(const boost::optional<boost::variant<std::string, selector_ptr>> &s,
         const boost::optional<std::string> &tag = boost::none);
  sketch &
  _vertices(const boost::optional<boost::variant<std::string, selector_ptr>> &s,
            const boost::optional<std::string> &tag = boost::none);

  void _tag(const std::vector<sketch_val> &val, const std::string &tag);
  void _tag(const std::vector<shape> &val, const std::string &tag);
  std::unordered_map<topo::face, std::vector<vertex>>
  _match_faces_to_vertices();
  std::vector<sketch_val> _unique(const std::vector<sketch_val> &vals);
  sketch &
  select(const boost::optional<boost::variant<std::string, selector_ptr>> &s,
         const std::string &kind, const boost::optional<std::string> &tag);
  topo_vector start_point();
  topo_vector end_point();
  shape sanitize_for_bool(const sketch_val &val) const;
  boost::optional<flywave::topo::compound> to_compound(const shape &sh) const;

private:
  const double TOL = 1e-9;

  friend class workplane;

  class constraint_ {
  public:
    constraint_(const std::string &tags, topo::edge &&args,
                sketch_constraint_kind kind, sketch_constraint_value param)
        : tags({tags}), args({args}), kind(kind), param(param) {}

    constraint_(const std::vector<std::string> &tags,
                const std::vector<topo::edge> &args,
                sketch_constraint_kind kind, sketch_constraint_value param)
        : tags(tags), args(args), kind(kind), param(param) {}

    std::vector<std::string> tags;
    std::vector<topo::edge> args;
    sketch_constraint_kind kind;
    sketch_constraint_value param;
  };

  std::shared_ptr<workplane> parent_;
  std::vector<topo_location> locs_;
  boost::optional<compound> faces_;
  std::vector<topo::edge> edges_;

  boost::optional<std::vector<sketch_val>> selection_;
  std::vector<constraint_> constraints_;

  std::unordered_map<std::string, std::vector<sketch_val>> tags_;
  std::map<std::string, boost::variant<double, int, std::string,
                                       std::vector<std::vector<double>>>>
      solve_status_;
};

} // namespace topo
} // namespace flywave

namespace std {
template <> struct hash<flywave::topo::sketch> {
  size_t operator()(const flywave::topo::sketch &obj) const {
    return obj.hash_code();
  }
};
} // namespace std
