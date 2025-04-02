#include "selector.hh"
#include <boost/fusion/adapted/std_tuple.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/variant.hpp>
#include <functional>
#include <map>
#include <string>
#include <vector>

#include "edge.hh"
#include "face.hh"
#include "wire.hh"

namespace qi = boost::spirit::qi;
namespace phx = boost::phoenix;

namespace flywave {
namespace topo {

// 实现基础选择器的运算符重载
selector_ptr selector::operator&&(const selector_ptr &other) const {
  return std::make_shared<and_selector>(std::make_shared<selector>(*this),
                                        other);
}

selector_ptr selector::operator||(const selector_ptr &other) const {
  return std::make_shared<or_selector>(std::make_shared<selector>(*this),
                                       other);
}

selector_ptr selector::operator-(const selector_ptr &other) const {
  return std::make_shared<subtract_selector>(std::make_shared<selector>(*this),
                                             other);
}

selector_ptr selector::operator!() const {
  return std::make_shared<not_selector>(std::make_shared<selector>(*this));
}

// nearest_to_point_selector 实现
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

// box_selector 实现
box_selector::box_selector(const topo_vector &p0, const topo_vector &p1,
                           bool use_bb)
    : p0_(p0), p1_(p1), use_bounding_box_(use_bb) {}

std::vector<shape>
box_selector::filter(const std::vector<shape> &objects) const {
  std::vector<shape> result;
  for (const auto &obj : objects) {
    if (use_bounding_box_) {
      auto bb = obj.bbox();
      if (is_inside(bb.Min()) && is_inside(bb.Max())) {
        result.push_back(obj);
      }
    } else if (is_inside(obj.centre_of_mass())) {
      result.push_back(obj);
    }
  }
  return result;
}

// nth_selector 实现
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

// 半径第N选择器实现
double radius_nth_selector::get_key(const shape &obj) const {
  if (obj.shape_type() == "Edge") {
    return obj.cast<edge>()->radius();
  } else if (obj.shape_type() == "Wire") {
    return obj.cast<wire>()->radius();
  }
  throw std::runtime_error("Cannot get a radius from this object");
}

// 中心第N选择器实现
double center_nth_selector::get_key(const shape &obj) const {
  return topo_vector(obj.centre_of_mass()).dot(direction_);
}

std::vector<shape>
direction_nth_selector::filter(const std::vector<shape> &objects) const {
  auto filtered = _dir_selector.filter(objects);
  return _nth_selector.filter(filtered);
}

// 长度第N选择器实现
double length_nth_selector::get_key(const shape &obj) const {
  if (obj.shape_type() == "Edge" || obj.shape_type() == "Wire") {
    return obj.cast<edge>()->length();
  }
  throw std::runtime_error("LengthNthSelector supports only Edges and Wires");
}

// 类型选择器实现
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

    if (obj.shape_type() == "Face" && obj.geom_type() == "PLANE") {
      test_vec = obj.cast<face>()->normal_at();
    } else if (obj.shape_type() == "Edge" && obj.geom_type() == "LINE") {
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

// 面积第N选择器实现
double area_nth_selector::get_key(const shape &obj) const {
  if (obj.shape_type() == "Face" || obj.shape_type() == "Shell" ||
      obj.shape_type() == "Solid") {
    return obj.compute_mass();
  } else if (obj.shape_type() == "Wire") {
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
  // 去重
  std::sort(result.begin(), result.end());
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

// 基础解析器类型
template <typename Iterator>
struct selector_grammar
    : qi::grammar<Iterator, selector_ptr(), qi::space_type> {
  struct parse_result {
    std::string type;
    std::string op;
    boost::variant<std::vector<double>, std::string> dir;
    boost::optional<int> index;
  };

  selector_grammar() : selector_grammar::base_type(expression) {
    using qi::_1;
    using qi::_val;
    using qi::char_;
    using qi::double_;
    using qi::int_;
    using qi::lexeme;
    using qi::lit;

    // 基本元素
    identifier = lexeme[(char_("a-zA-Z") >> *char_("a-zA-Z0-9"))];
    vector = '(' >> double_ >> ',' >> double_ >> ',' >> double_ >> ')';

    // 方向定义
    simple_dir = qi::no_case[lit("x") | "y" | "z" | "xy" | "xz" | "yz"];
    direction = simple_dir | vector;

    // 类型定义
    cqtype =
        qi::no_case[lit("plane") | "cylinder" | "cone" | "sphere" | "torus"];

    // 操作符
    type_op = '%';
    dir_op = '>' | '<';
    center_nth_op = ">>" | "<<";
    other_op = '|' | '#' | '+' | '-';

    // 索引
    index = '[' >> -int_ >> ']';

    // 命名视图
    named_view = qi::no_case[lit("front") | "back" | "left" | "right" | "top" |
                             "bottom"];

    // 原子选择器
    only_dir = direction[_val = phx::construct<parse_result>(
                             phx::val("only_dir"), "", _1, boost::none)];
    type_sel =
        (type_op >> cqtype)[_val = phx::construct<parse_result>(
                                phx::val("type_op"), "", _1, boost::none)];
    dir_sel =
        (dir_op >> direction >> -index)[_val = phx::construct<parse_result>(
                                            phx::val("dir_op"), _1, _2, _3)];
    center_sel = (center_nth_op >> direction >>
                  -index)[_val = phx::construct<parse_result>(
                              phx::val("center_nth_op"), _1, _2, _3)];
    other_sel =
        (other_op >> direction)[_val = phx::construct<parse_result>(
                                    phx::val("other_op"), _1, _2, boost::none)];
    named_sel = named_view[_val = phx::construct<parse_result>(
                               phx::val("named_view"), "", _1, boost::none)];

    atom = only_dir | type_sel | dir_sel | center_sel | other_sel | named_sel;

    // 表达式语法
    factor = atom[_val = _1] | '(' >> expression[_val = _1] >> ')';
    term = factor[_val = _1] >>
           *((lit("and") >> factor)[_val = phx::new_<and_selector>(_val, _1)] |
             (lit("or") >> factor)[_val = phx::new_<or_selector>(_val, _1)] |
             (lit("exc") >>
              factor)[_val = phx::new_<subtract_selector>(_val, _1)]);
    expression =
        term[_val = _1] >>
        *((lit("and") >> term)[_val = phx::new_<and_selector>(_val, _1)] |
          (lit("or") >> term)[_val = phx::new_<or_selector>(_val, _1)] |
          (lit("exc") >> term)[_val = phx::new_<subtract_selector>(_val, _1)]);

    qi::on_error<qi::fail>(
        expression, std::cout << phx::val("Error! Expecting ") << qi::_4
                              << phx::val(" here: \"")
                              << phx::construct<std::string>(qi::_3, qi::_2)
                              << phx::val("\"") << std::endl);
  }

  qi::rule<Iterator, selector_ptr(), qi::space_type> expression, term, factor;
  qi::rule<Iterator, parse_result(), qi::space_type> atom, only_dir, type_sel,
      dir_sel, center_sel, other_sel, named_sel;
  qi::rule<Iterator, std::string(), qi::space_type> identifier, simple_dir,
      cqtype, named_view;
  qi::rule<Iterator, std::vector<double>(), qi::space_type> vector;
  qi::rule<Iterator, boost::optional<int>(), qi::space_type> index;
  qi::rule<Iterator, std::string(), qi::space_type> direction;
};

// 简单字符串语法选择器
class simple_string_selector : public selector {
  struct selector_builder {
    std::unordered_map<std::string, topo_vector> axes = {
        {"X", {1, 0, 0}},  {"Y", {0, 1, 0}},  {"Z", {0, 0, 1}},
        {"XY", {1, 1, 0}}, {"XZ", {1, 0, 1}}, {"YZ", {0, 1, 1}}};

    std::unordered_map<std::string, std::pair<topo_vector, bool>> named_views =
        {{"front", {{0, 0, 1}, true}}, {"back", {{0, 0, 1}, false}},
         {"left", {{1, 0, 0}, false}}, {"right", {{1, 0, 0}, true}},
         {"top", {{0, 1, 0}, true}},   {"bottom", {{0, 1, 0}, false}}};

    std::unordered_map<std::string, std::function<selector_ptr(topo_vector)>>
        operators = {
            {"+",
             [](topo_vector v) { return std::make_shared<dir_selector>(v); }},
            {"-",
             [](topo_vector v) { return std::make_shared<dir_selector>(-v); }},
            {"#",
             [](topo_vector v) {
               return std::make_shared<perpendicular_dir_selector>(v);
             }},
            {"|", [](topo_vector v) {
               return std::make_shared<parallel_dir_selector>(v);
             }}};

    std::unordered_map<std::string, bool> operator_minmax = {
        {">", true}, {">>", true}, {"<", false}, {"<<", false}};

    selector_ptr build(
        const selector_grammar<std::string::const_iterator>::parse_result &pr) {
      if (pr.type == "only_dir") {
        return std::make_shared<dir_selector>(get_vector(pr.dir));
      } else if (pr.type == "type_op") {
        return std::make_shared<type_selector>(boost::get<std::string>(pr.dir));
      } else if (pr.type == "dir_op") {
        auto vec = get_vector(pr.dir);
        bool minmax = operator_minmax[pr.op];
        if (pr.index) {
          return std::make_shared<direction_nth_selector>(vec, *pr.index,
                                                          minmax);
        }
        return std::make_shared<direction_minmax_selector>(vec, minmax);
      } else if (pr.type == "center_nth_op") {
        auto vec = get_vector(pr.dir);
        bool minmax = operator_minmax[pr.op];
        if (pr.index) {
          return std::make_shared<center_nth_selector>(vec, *pr.index, minmax);
        }
        return std::make_shared<center_nth_selector>(vec, -1, minmax);
      } else if (pr.type == "other_op") {
        auto vec = get_vector(pr.dir);
        return operators[pr.op](vec);
      } else if (pr.type == "named_view") {
        auto view = named_views[boost::get<std::string>(pr.dir)];
        return std::make_shared<direction_minmax_selector>(view.first,
                                                           view.second);
      }
      throw std::runtime_error("Unknown selector type: " + pr.type);
    }

    topo_vector
    get_vector(const boost::variant<std::vector<double>, std::string> &pr) {
      if (pr.which() == 0) { // vector<double>
        auto v = boost::get<std::vector<double>>(pr);
        return {v[0], v[1], v[2]};
      }
      return axes[boost::get<std::string>(pr)];
    }
  };

  selector_ptr selector_;

public:
  simple_string_selector(const std::string &expr) {
    selector_grammar<std::string::const_iterator> grammar;
    selector_builder builder;
    std::string::const_iterator iter = expr.begin();
    std::string::const_iterator end = expr.end();

    selector_grammar<std::string::const_iterator>::parse_result pr;
    bool success = qi::phrase_parse(iter, end, grammar, qi::space, pr);

    if (!success || iter != end) {
      throw std::runtime_error("Invalid selector syntax");
    }

    selector_ = builder.build(pr);
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