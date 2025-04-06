#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#pragma clang diagnostic ignored "-Wdocumentation"

#include "selector.hh"

#include <boost/fusion/adapted/std_tuple.hpp>
#include <boost/phoenix/object/construct.hpp>
#include <boost/phoenix/object/new.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/variant.hpp>

#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "edge.hh"
#include "face.hh"
#include "wire.hh"

namespace qi = boost::spirit::qi;
namespace phx = boost::phoenix;

namespace flywave {
namespace topo {

selector_ptr selector::operator&&(const selector_ptr &other) const {
  return std::make_shared<and_selector>(
      std::const_pointer_cast<selector>(this->shared_from_this()), other);
}

selector_ptr selector::operator||(const selector_ptr &other) const {
  return std::make_shared<or_selector>(
      std::const_pointer_cast<selector>(this->shared_from_this()), other);
}

selector_ptr selector::operator-(const selector_ptr &other) const {
  return std::make_shared<subtract_selector>(
      std::const_pointer_cast<selector>(this->shared_from_this()), other);
}

selector_ptr selector::operator!() const {
  return std::make_shared<not_selector>(
      std::const_pointer_cast<selector>(this->shared_from_this()));
}

nearest_to_point_selector::nearest_to_point_selector(const topo_vector &p)
    : point_(p) {}

std::vector<shape>
nearest_to_point_selector::filter(const std::vector<shape> &objects) const {
  if (objects.empty())
    return {};

  auto closest = *std::min_element(
      objects.begin(), objects.end(), [this](const shape &a, const shape &b) {
        return a.centre_of_mass().Distance(point_) <
               b.centre_of_mass().Distance(point_);
      });
  return {closest};
}

box_selector::box_selector(const topo_vector &p0, const topo_vector &p1,
                           bool use_bb)
    : p0_(p0), p1_(p1), use_bounding_box_(use_bb) {}

std::vector<shape>
box_selector::filter(const std::vector<shape> &objects) const {
  std::vector<shape> result;
  for (const auto &obj : objects) {
    if (use_bounding_box_) {
      auto bb = obj.bbox();
      if (is_inside(bb.min()) && is_inside(bb.max())) {
        result.push_back(obj);
      }
    } else if (is_inside(obj.centre_of_mass())) {
      result.push_back(obj);
    }
  }
  return result;
}

nth_selector::nth_selector(int n, bool direction_max, double tolerance)
    : n_(n), direction_max_(direction_max), tolerance_(tolerance) {}

clustered_shapes
nth_selector::cluster(const std::vector<shape> &objects) const {
  std::vector<std::pair<double, shape>> key_and_obj;
  for (const auto &obj : objects) {
    try {
      double key = get_key(obj);
      key_and_obj.emplace_back(key, obj);
    } catch (const std::exception &) {
      continue;
    }
  }

  std::sort(key_and_obj.begin(), key_and_obj.end(),
            [](const auto &a, const auto &b) { return a.first < b.first; });

  clustered_shapes clustered;
  if (key_and_obj.empty())
    return clustered;

  clustered.push_back({key_and_obj[0].second});
  double start = key_and_obj[0].first;

  for (size_t i = 1; i < key_and_obj.size(); ++i) {
    const auto &key = key_and_obj[i].first;
    const auto &obj = key_and_obj[i].second;
    if (std::abs(key - start) <= tolerance_) {
      clustered.back().push_back(obj);
    } else {
      clustered.push_back({obj});
      start = key;
    }
  }

  return clustered;
}

std::vector<shape>
nth_selector::filter(const std::vector<shape> &objects) const {
  if (objects.empty()) {
    throw std::runtime_error("Cannot return the Nth element of an empty list");
  }

  auto clustered = cluster(objects);
  if (!direction_max_) {
    std::reverse(clustered.begin(), clustered.end());
  }

  if (n_ < 0 || static_cast<size_t>(n_) >= clustered.size()) {
    throw std::out_of_range("Attempted to access index " + std::to_string(n_) +
                            " of a list with length " +
                            std::to_string(clustered.size()));
  }

  return clustered[n_];
}

double radius_nth_selector::get_key(const shape &obj) const {
  if (obj.shape_type() == TopAbs_EDGE) {
    return obj.cast<edge>()->radius();
  } else if (obj.shape_type() == TopAbs_WIRE) {
    return obj.cast<wire>()->radius();
  }
  throw std::runtime_error("Cannot get a radius from this object");
}

double center_nth_selector::get_key(const shape &obj) const {
  return topo_vector(obj.centre_of_mass()).dot(direction_);
}

std::vector<shape>
direction_nth_selector::filter(const std::vector<shape> &objects) const {
  auto filtered = _dir_selector.filter(objects);
  return _nth_selector.filter(filtered);
}

double length_nth_selector::get_key(const shape &obj) const {
  if (obj.shape_type() == TopAbs_EDGE || obj.shape_type() == TopAbs_WIRE) {
    return obj.cast<edge>()->length();
  }
  throw std::runtime_error("LengthNthSelector supports only Edges and Wires");
}

std::vector<shape>
type_selector::filter(const std::vector<shape> &objects) const {
  std::vector<shape> result;
  for (const auto &obj : objects) {
    if (obj.geom_type() == type_) {
      result.push_back(obj);
    }
  }
  return result;
}

std::vector<shape>
direction_selector::filter(const std::vector<shape> &objects) const {
  std::vector<shape> result;
  for (const auto &obj : objects) {
    topo_vector test_vec;

    if (obj.shape_type() == TopAbs_FACE &&
        obj.geom_type() == shape_geom_plane) {
      test_vec = obj.cast<face>()->normal_at();
    } else if (obj.shape_type() == TopAbs_EDGE &&
               obj.geom_type() == shape_geom_line) {
      test_vec = obj.cast<edge>()->tangent_at();
    } else {
      continue;
    }

    if (test(test_vec)) {
      result.push_back(obj);
    }
  }
  return result;
}

double area_nth_selector::get_key(const shape &obj) const {
  if (obj.shape_type() == TopAbs_FACE || obj.shape_type() == TopAbs_SHELL ||
      obj.shape_type() == TopAbs_SOLID) {
    return obj.compute_mass();
  } else if (obj.shape_type() == TopAbs_WIRE) {
    try {
      auto face = face::make_face(obj.cast<wire>().get());
      return std::abs(face.area());
    } catch (const std::exception &e) {
      throw std::runtime_error(
          "Cannot compute area of the Wire. area_nth_selector supports only "
          "closed planar Wires. Error: " +
          std::string(e.what()));
    }
  }
  throw std::runtime_error(
      "area_nth_selector supports only Wires, Faces, Shells and Solids");
}

std::vector<shape>
binary_selector::filter(const std::vector<shape> &objects) const {
  return filter_results(left_->filter(objects), right_->filter(objects));
}

std::vector<shape>
and_selector::filter_results(const std::vector<shape> &left,
                             const std::vector<shape> &right) const {
  std::vector<shape> result;
  std::set_intersection(left.begin(), left.end(), right.begin(), right.end(),
                        std::back_inserter(result));
  return result;
}

std::vector<shape>
or_selector::filter_results(const std::vector<shape> &left,
                            const std::vector<shape> &right) const {
  std::vector<shape> result = left;
  result.insert(result.end(), right.begin(), right.end());
  result.erase(std::unique(result.begin(), result.end()), result.end());
  return result;
}

std::vector<shape>
subtract_selector::filter_results(const std::vector<shape> &left,
                                  const std::vector<shape> &right) const {
  std::vector<shape> result;
  std::set_difference(left.begin(), left.end(), right.begin(), right.end(),
                      std::back_inserter(result));
  return result;
}

std::vector<shape>
not_selector::filter(const std::vector<shape> &objects) const {
  auto filtered = selector_->filter(objects);
  std::vector<shape> result;
  std::set_difference(objects.begin(), objects.end(), filtered.begin(),
                      filtered.end(), std::back_inserter(result));
  return result;
}

template <typename Iterator>
struct selector_grammar
    : qi::grammar<Iterator, selector_ptr(), qi::space_type> {
  typedef selector_ptr (selector_grammar::*dir_sel_func)(
      const std::string &,
      const boost::variant<std::vector<double>, std::string> &,
      const boost::optional<int> &);

  typedef selector_ptr (selector_grammar::*other_sel_func)(
      const std::string &,
      const boost::variant<std::vector<double>, std::string> &);

  selector_grammar() : selector_grammar::base_type(expression) {
    using qi::_1;
    using qi::_2;
    using qi::_3;
    using qi::_val;
    using qi::char_;
    using qi::double_;
    using qi::int_;
    using qi::lexeme;
    using qi::lit;
    using qi::no_case;
    namespace phx = boost::phoenix;

    identifier = lexeme[(char_("a-zA-Z") >> *char_("a-zA-Z0-9_"))];
    vector = '(' >> double_ >> ',' >> double_ >> ',' >> double_ >> ')';
    simple_dir = no_case[lit("x") | "y" | "z" | "xy" | "xz" | "yz"];
    direction = simple_dir | vector;
    cqtype = no_case[lit("plane") | "cylinder" | "cone" | "sphere" | "torus" |
                     "line" | "circle" | "ellipse" | "hyperbola" | "parabola"];
    index = '[' >> -int_ >> ']';
    named_view =
        no_case[lit("front") | "back" | "left" | "right" | "top" | "bottom"];

    type_op = lexeme[lit('%')];
    dir_op = lexeme[lit('>')] | lexeme[lit('<')];
    center_nth_op = lexeme[lit(">>")] | lexeme[lit("<<")];
    other_op = lexeme[lit('|')] | lexeme[lit('#')] | lexeme[lit('+')] |
               lexeme[lit('-')];

    only_dir = direction[_val = phx::bind(
                             &selector_grammar::create_dir_selector, this, _1)];
    type_sel = (type_op >>
                cqtype)[_val = phx::bind(
                            &selector_grammar::create_type_selector, this, _2)];

    dir_sel =
        (dir_op >> direction >>
         -index)[_val = phx::bind(static_cast<dir_sel_func>(
                                      &selector_grammar::build_dir_selector),
                                  this, _1, _2, _3)];

    other_sel = (other_op >>
                 direction)[_val = phx::bind(
                                static_cast<other_sel_func>(
                                    &selector_grammar::build_other_selector),
                                this, _1, _2)];

    named_sel =
        named_view[_val = phx::bind(&selector_grammar::build_named_selector,
                                    this, _1)];

    atom = only_dir | type_sel | dir_sel | other_sel | named_sel;

    factor = atom[_val = _1] | '(' >> expression[_val = _1] >> ')';

    term =
        factor[_val = _1] >>
        *((lit("and") >> factor)[_val = phx::construct<selector_ptr>(
                                     phx::new_<and_selector>(_val, _1))] |
          (lit("or") >> factor)[_val = phx::construct<selector_ptr>(
                                    phx::new_<or_selector>(_val, _1))] |
          (lit("exc") >> factor)[_val = phx::construct<selector_ptr>(
                                     phx::new_<subtract_selector>(_val, _1))]);

    expression =
        term[_val = _1] >>
        *((lit("and") >> term)[_val = phx::construct<selector_ptr>(
                                   phx::new_<and_selector>(_val, _1))] |
          (lit("or") >> term)[_val = phx::construct<selector_ptr>(
                                  phx::new_<or_selector>(_val, _1))] |
          (lit("exc") >> term)[_val = phx::construct<selector_ptr>(
                                   phx::new_<subtract_selector>(_val, _1))]);

    qi::on_error<qi::fail>(
        expression,
        std::cout << phx::val("Error! Expecting ") << qi::_4 << " here: \""
                  << phx::construct<std::string>(qi::_3, qi::_2) << "\"\n");
  }

private:
  topo_vector
  get_vector(const boost::variant<std::vector<double>, std::string> &dir) {
    struct visitor : boost::static_visitor<topo_vector> {
      topo_vector operator()(const std::vector<double> &v) const {
        return {v[0], v[1], v[2]};
      }
      topo_vector operator()(const std::string &s) const {
        static std::unordered_map<std::string, topo_vector> axes = {
            {"x", {1, 0, 0}},  {"y", {0, 1, 0}},  {"z", {0, 0, 1}},
            {"xy", {1, 1, 0}}, {"xz", {1, 0, 1}}, {"yz", {0, 1, 1}}};
        return axes.at(s);
      }
    };
    return boost::apply_visitor(visitor(), dir);
  }

  selector_ptr create_dir_selector(
      const boost::variant<std::vector<double>, std::string> &dir) {
    return std::make_shared<dir_selector>(get_vector(dir), 1e-4);
  }

  selector_ptr create_type_selector(const std::string &type) {
    static std::unordered_map<std::string, shape_geom_type> types = {
        {"plane", shape_geom_plane},         {"cylinder", shape_geom_cylinder},
        {"cone", shape_geom_cone},           {"sphere", shape_geom_sphere},
        {"torus", shape_geom_torus},         {"line", shape_geom_line},
        {"circle", shape_geom_circle},       {"ellipse", shape_geom_ellipse},
        {"hyperbola", shape_geom_hyperbola}, {"parabola", shape_geom_parabola}};
    auto &type_ = types.at(type);
    return std::make_shared<type_selector>(type_);
  }

  selector_ptr build_dir_selector(
      const std::string &op,
      const boost::variant<std::vector<double>, std::string> &dir,
      const boost::optional<int> &index) {
    auto vec = get_vector(dir);
    bool minmax = (op == ">");

    if (index) {
      return std::make_shared<direction_nth_selector>(vec, *index, minmax);
    }
    return std::make_shared<direction_minmax_selector>(vec, minmax);
  }

  selector_ptr build_other_selector(
      const std::string &op,
      const boost::variant<std::vector<double>, std::string> &dir) {
    auto vec = get_vector(dir);
    if (op == "+")
      return std::make_shared<dir_selector>(vec);
    if (op == "-")
      return std::make_shared<dir_selector>(-vec);
    if (op == "#")
      return std::make_shared<perpendicular_dir_selector>(vec);
    if (op == "|")
      return std::make_shared<parallel_dir_selector>(vec);
    throw std::runtime_error("Unknown operator: " + op);
  }

  selector_ptr build_named_selector(const std::string &view) {
    static std::unordered_map<std::string, std::pair<topo_vector, bool>> views =
        {{"front", {{0, 0, 1}, true}}, {"back", {{0, 0, 1}, false}},
         {"left", {{1, 0, 0}, false}}, {"right", {{1, 0, 0}, true}},
         {"top", {{0, 1, 0}, true}},   {"bottom", {{0, 1, 0}, false}}};
    auto &args = views.at(view);
    return std::make_shared<direction_minmax_selector>(args.first, args.second);
  }

  qi::rule<Iterator, selector_ptr(), qi::space_type> expression, term, factor,
      atom;
  qi::rule<Iterator, selector_ptr(), qi::space_type> only_dir, type_sel,
      dir_sel, other_sel, named_sel;
  qi::rule<Iterator, boost::variant<std::vector<double>, std::string>(),
           qi::space_type>
      direction, simple_dir;
  qi::rule<Iterator, std::string(), qi::space_type> identifier, cqtype,
      named_view;
  qi::rule<Iterator, std::vector<double>(), qi::space_type> vector;
  qi::rule<Iterator, boost::optional<int>(), qi::space_type> index;
  qi::rule<Iterator, std::string(), qi::space_type> type_op;
  qi::rule<Iterator, std::string(), qi::space_type> dir_op;
  qi::rule<Iterator, std::string(), qi::space_type> center_nth_op;
  qi::rule<Iterator, std::string(), qi::space_type> other_op;
};

class simple_string_selector : public selector {
  selector_ptr selector_;

public:
  simple_string_selector(const std::string &expr) {
    selector_grammar<std::string::const_iterator> grammar;
    std::string::const_iterator iter = expr.begin();
    std::string::const_iterator end = expr.end();

    selector_ptr result;
    bool success = qi::phrase_parse(iter, end, grammar, qi::space, result);

    if (!success || iter != end) {
      throw std::runtime_error("Invalid selector syntax");
    }

    selector_ = result;
  }

  std::vector<shape> filter(const std::vector<shape> &objects) const override {
    return selector_->filter(objects);
  }
};
string_syntax_selector::string_syntax_selector(
    const std::string &selector_str) {
  selector_ = std::make_shared<simple_string_selector>(selector_str);
}

} // namespace topo
} // namespace flywave

#pragma clang diagnostic pop
