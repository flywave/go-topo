#include "assembly.hh"
#include <boost/fusion/adapted/struct.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/string/symbols.hpp>
#include <boost/spirit/include/support_istream_iterator.hpp>
#include <iomanip>
#include <random>
#include <sstream>
#include <unordered_set>

#include "compound.hh"
#include "workplane.hh"

namespace x3 = boost::spirit::x3;

// 定义解析结果数据结构
struct parse_result {
  std::string name;
  std::string tag;
  std::string selector_kind;
  std::string selector;
};

// clang-format off
// 必须在全局命名空间进行适配
BOOST_FUSION_ADAPT_STRUCT(parse_result,
  (std::string, name)
  (std::string, tag)
  (std::string, selector_kind)
  (std::string, selector)
)
// clang-format on

namespace flywave {
namespace topo {
namespace detail {

std::string generateUUID() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 255);

  std::stringstream ss;
  ss << std::hex << std::setfill('0');

  for (int i = 0; i < 16; ++i) {
    ss << std::setw(2) << dis(gen);
    if (i == 3 || i == 5 || i == 7 || i == 9) {
      ss << "-";
    }
  }

  return ss.str();
}
// 基本字符集定义
const std::string PATH_DELIM = "/";
const auto name_char = x3::alnum | x3::char_('_');
const auto tag_char = x3::alnum | x3::char_('_');

// 组合式路径名解析规则
struct name_rule : x3::parser<name_rule> {
  using attribute_type = std::string;

  template <typename Iterator, typename Context, typename Attribute>
  bool parse(Iterator &first, Iterator const &last, Context const &context,
             x3::unused_type, Attribute &attr) const {
    std::string result;
    bool first_segment = true;

    while (first != last) {
      std::string segment;
      auto seg_parser = +name_char;
      if (!seg_parser.parse(first, last, context, x3::unused, segment))
        break;

      if (!first_segment)
        result += PATH_DELIM;
      result += segment;
      first_segment = false;

      if (first == last || *first != PATH_DELIM[0])
        break;
      ++first; // 跳过分隔符
    }

    if (result.empty())
      return false;
    attr = result;
    return true;
  }
};

// 定义各解析规则
const name_rule name = {};
const auto tag = x3::rule<class tag_rule, std::string>{} = +tag_char;

const auto selector_type = x3::rule<class stype_rule, std::string>{} =
    x3::lit("solids") | "faces" | "edges" | "vertices";

const auto selector = x3::rule<class sel_rule, std::string>{} =
    +x3::char_; // 简化处理，实际需按_selector_grammar实现

// 组合完整语法规则
const auto grammar_def = name >> -('?' >> tag) >>
                         -('@' >> selector_type >> '@' >> selector);
} // namespace detail

// 对外暴露的解析接口
bool parse(const std::string &input, parse_result &result) {
  using iterator_type = std::string::const_iterator;

  iterator_type iter = input.begin();
  iterator_type end = input.end();

  return x3::parse(iter, end, detail::grammar_def, result) && iter == end;
}

assembly::assembly(assembly_object obj, std::shared_ptr<topo_location> loc,
                   const std::string &name,
                   std::shared_ptr<Quantity_Color> color,
                   const std::unordered_map<std::string, boost::any> &metadata)
    : obj_(std::move(obj)),
      loc_(loc ? std::move(loc) : std::make_shared<topo_location>()),
      name_(name.empty() ? detail::generateUUID() : name),
      color_(std::move(color)), metadata_(metadata), parent_(), children_(),
      objects_(), // 注意：需要在enable_shared_from_this派生类中使用
      constraints_(), solveResult_(boost::none) {

  objects_[name_] = shared_from_this();
  // 使用boost::variant的静态访问器进行类型安全检查
  struct validator : public boost::static_visitor<void> {
    void operator()(const std::shared_ptr<workplane> &wp) const {
      if (!wp)
        throw std::invalid_argument("Workplane object is null");
    }

    void operator()(const shape &sh) const {
      if (!sh)
        throw std::invalid_argument("Shape object is null");
    }

    void operator()(std::nullptr_t) const {} // 允许nullptr
  };

  // 应用验证器
  boost::apply_visitor(validator(), obj_);

  // 使用boost::variant的which()替代index()
  if (obj_.which() != -1) { // 确保variant已初始化
    // 预分配子节点空间（优化）
    children_.reserve(4);
  }
}

std::shared_ptr<assembly> assembly::copy() const {
  // Create new assembly with copied basic properties
  auto new_assembly = std::make_shared<assembly>(
      obj_, loc_ ? std::make_shared<topo_location>(*loc_) : nullptr, name_,
      color_ ? std::make_shared<Quantity_Color>(*color_) : nullptr, metadata_);

  // Deep copy children
  for (const auto &child : children_) {
    auto child_copy = child->copy();
    child_copy->parent_ = new_assembly;

    new_assembly->children_.push_back(child_copy);
    new_assembly->objects_[child_copy->name_] = child_copy;

    // Merge child's objects into the new assembly
    auto child_objects = child_copy->flatten();

    for (const auto &[name, obj] : child_objects) {
      new_assembly->objects_[name] = obj;
    }
  }

  // Copy constraints
  for (const auto &constraint : constraints_) {
    new_assembly->constraints_.push_back(
        std::make_shared<constraint_spec>(*constraint));
  }

  // Copy solve result if exists
  if (solveResult_) {
    new_assembly->solveResult_ = *solveResult_;
  }

  return new_assembly;
}

assembly &assembly::add(std::shared_ptr<assembly> subAssembly,
                        std::shared_ptr<topo_location> loc,
                        const std::string &name,
                        std::shared_ptr<Quantity_Color> color) {
  // Validate input
  if (!subAssembly) {
    throw std::invalid_argument("Cannot add null assembly");
  }

  // Determine final properties
  const std::string &finalName = name.empty() ? subAssembly->name_ : name;
  if (objects_.find(finalName) != objects_.end()) {
    throw std::invalid_argument("Duplicate assembly name: " + finalName);
  }

  // Create deep copy
  auto newAssembly = subAssembly->copy();

  // Apply overrides
  newAssembly->loc_ = loc ? loc : subAssembly->loc_;
  newAssembly->name_ = finalName;
  newAssembly->color_ = color ? color : subAssembly->color_;
  newAssembly->parent_ = shared_from_this();

  // Add to hierarchy
  children_.push_back(newAssembly);
  objects_[finalName] = newAssembly;

  // Merge child objects
  auto childObjects = newAssembly->flatten();
  for (const auto &[name, obj] : childObjects) {
    objects_[name] = obj;
  }

  return *this;
}

assembly &
assembly::add(assembly_object obj, std::shared_ptr<topo_location> loc,
              const std::string &name, std::shared_ptr<Quantity_Color> color,
              const std::unordered_map<std::string, boost::any> &metadata) {
  // Create new assembly from object
  auto newAssembly = std::make_shared<assembly>(
      std::move(obj), loc ? loc : std::make_shared<topo_location>(),
      name.empty() ? detail::generateUUID() : name, color, metadata);

  // Add using the assembly version
  return add(newAssembly);
}

assembly &assembly::remove(const std::string &name) {
  // Check if object exists
  auto it = objects_.find(name);
  if (it == objects_.end()) {
    throw std::invalid_argument("No object with name '" + name +
                                "' found in the assembly");
  }

  // Get the assembly to remove
  auto toRemove = it->second;

  // Remove from parent's children list
  if (auto parent = toRemove->parent_.lock()) {
    auto &children = parent->children_;
    children.erase(std::remove(children.begin(), children.end(), toRemove),
                   children.end());
  }

  // Remove from objects dictionary
  objects_.erase(it);

  // Remove all descendants
  auto descendants = toRemove->flatten();
  for (const auto &[descName, _] : descendants) {
    objects_.erase(descName);
  }

  // Reset parent reference
  toRemove->parent_.reset();

  return *this;
}

std::pair<std::string, shape> assembly::query(const std::string &q) const {
  parse_result rs;
  bool ok = parse(q, rs);

  auto obj_it = objects_.find(rs.name);
  if (obj_it == objects_.end()) {
    throw std::invalid_argument("Object not found: " + rs.name);
  }

  auto obj = obj_it->second->obj_;
  std::shared_ptr<workplane> tmp_wp;
  shape_object result;

  // 使用 boost::get 替代 std::get_if
  if (auto *wp = boost::get<std::shared_ptr<workplane>>(&obj)) {
    if (!rs.tag.empty()) {
      tmp_wp = (*wp)->getTagged(rs.tag);
    } else {
      tmp_wp = std::make_shared<workplane>();
      tmp_wp->add(**wp);
    }
  } else if (auto *sh = boost::get<shape>(&obj)) {
    tmp_wp = std::make_shared<workplane>();
    tmp_wp->add(*sh);
  } else if (!boost::get<std::nullptr_t>(&obj)) {
    throw std::invalid_argument("Invalid object type in assembly");
  } else {
    throw std::invalid_argument("Workplane or Shape required for query");
  }

  // Apply selector if specified
  if (!rs.selector_kind.empty()) {
    if (rs.selector_kind == "faces") {
      result =
          tmp_wp
              ->faces(boost::make_optional<
                      boost::variant<std::shared_ptr<selector>, std::string>>(
                  rs.selector))
              ->val();
    } else if (rs.selector_kind == "edges") {
      result =
          tmp_wp
              ->edges(boost::make_optional<
                      boost::variant<std::shared_ptr<selector>, std::string>>(
                  rs.selector))
              ->val();
    }
    // ... other selector kinds
    else {
      throw std::invalid_argument("Invalid selector kind: " + rs.selector_kind);
    }
  } else {
    auto val = tmp_wp->val();
    if (!val.empty())
      result = val;
  }

  return {rs.name, boost::get<shape>(result)};
}

// 公共重载方法实现
assembly &assembly::constrain(const std::string &q1, const std::string &q2,
                              ConstraintKind kind,
                              const ConstraintParam &param) {
  auto [id1, s1] = query(q1);
  auto [id2, s2] = query(q2);
  return add_constraint_impl(id1, &s1, id2, &s2, kind, param, true);
}

assembly &assembly::constrain(const std::string &q1, ConstraintKind kind,
                              const ConstraintParam &param) {
  auto [id1, s1] = query(q1);
  return add_constraint_impl(id1, &s1, "", nullptr,
                             static_cast<ConstraintKind>(kind), param, false);
}

assembly &assembly::constrain(const std::string &id1, const shape &s1,
                              const std::string &id2, const shape &s2,
                              ConstraintKind kind,
                              const ConstraintParam &param) {
  return add_constraint_impl(id1, &s1, id2, &s2, kind, param, true);
}

assembly &assembly::constrain(const std::string &id1, const shape &s1,
                              ConstraintKind kind,
                              const ConstraintParam &param) {
  return add_constraint_impl(id1, &s1, "", nullptr,
                             static_cast<ConstraintKind>(kind), param, false);
}

// 统一实现方法
assembly &assembly::add_constraint_impl(const std::string &id1, const shape *s1,
                                        const std::string &id2, const shape *s2,
                                        ConstraintKind kind,
                                        const ConstraintParam &param,
                                        bool isBinary) {

  // 运行时类型检查
  if (isBinary != is_binary(kind)) {
    throw std::invalid_argument(isBinary ? "Expected binary constraint type"
                                         : "Expected unary constraint type");
  }

  if (!s1) {
    throw std::invalid_argument("First shape cannot be null");
  }

  // 一元约束处理
  if (!isBinary) {
    auto [loc1, topId1] = sub_location(id1);
    constraints_.push_back(std::make_shared<constraint_spec>(
        std::vector<std::string>{topId1}, std::vector<shape>{*s1},
        std::vector<topo_location>{loc1}, kind, param));
  }
  // 二元约束处理
  else {
    if (!s2) {
      throw std::invalid_argument(
          "Second shape cannot be null for binary constraint");
    }

    auto [loc1, topId1] = sub_location(id1);
    auto [loc2, topId2] = sub_location(id2);
    constraints_.push_back(std::make_shared<constraint_spec>(
        std::vector<std::string>{topId1, topId2}, std::vector<shape>{*s1, *s2},
        std::vector<topo_location>{loc1, loc2}, kind, param));
  }

  return *this;
}

assembly &assembly::solve(int verbosity) {
  // Step 1: Collect and index entities with early exit
  if (constraints_.empty()) {
    throw std::runtime_error("At least one constraint required");
  }

  std::unordered_map<std::string, size_t> ents;
  std::vector<size_t> locked;
  size_t index = 0;

  // First pass: index entities and identify locked ones
  for (const auto &c : constraints_) {
    for (const auto &name : c->objects) {
      if (ents.find(name) == ents.end()) {
        ents[name] = index++;
      }
      // Lock fixed constraints or root assembly
      if ((c->kind == ConstraintKind::Fixed || name == name_) &&
          std::find(locked.begin(), locked.end(), ents[name]) == locked.end()) {
        locked.push_back(ents[name]);
      }
    }
  }

  // Step 2: Ensure at least one locked entity
  if (locked.empty()) {
    locked.push_back(0); // Lock first entity as fallback
  }

  // Step 3: Prepare data for solver
  std::vector<gp_Trsf> locs(ents.size());
  for (const auto &entry : ents) {
    locs[entry.second] = *objects_.find(entry.first)->second->loc_;
  }

  std::vector<Constraint> constraint_pods;
  constraint_pods.reserve(constraints_.size());
  for (const auto &c : constraints_) {
    auto pods = c->to_pods();
    for (const auto &pod : pods) {
      constraint_pods.push_back(pod);
    }
  }

  // Step 4: Solve constraints
  double scale = to_compound().bbox().GetDiagonalLength();
  constraint_solver solver(locs, constraint_pods, locked, scale);

  auto solve_result = solver.solve(verbosity);
  solveResult_ = solve_result.second;

  // Step 5: Update positions
  auto root_loc_inv = std::make_shared<topo_location>();
  if (obj_.which() != 2) { // Not nullptr
    for (const auto &entry : ents) {
      if (entry.first == name_) {
        *root_loc_inv = solve_result.first[entry.second].Inverted();
        break;
      }
    }
  }

  for (const auto &entry : ents) {
    if (entry.first != name_) {
      objects_.find(entry.first)->second->loc_ =
          std::make_shared<topo_location>(*root_loc_inv *
                                          solve_result.first[entry.second]);
    }
  }

  return *this;
}

assembly &
assembly::export_to(const std::string &path, const std::string &exportType,
                    const std::string &mode, double tolerance,
                    double angularTolerance,
                    const std::unordered_map<std::string, boost::any> &kwargs) {
  // Validate STEP export mode
  const std::vector<std::string> validStepModes = {"default", "fused",
                                                   "per_part"};
  if (std::find(validStepModes.begin(), validStepModes.end(), mode) ==
      validStepModes.end()) {
    throw std::invalid_argument("Invalid STEP export mode: " + mode);
  }

  return *this;
}

std::vector<shape> assembly::shapes() const {
  std::vector<shape> result;

  if (auto sh = boost::get<shape>(&obj_)) {
    result.push_back(*sh);
  } else if (auto wp = boost::get<std::shared_ptr<workplane>>(&obj_)) {
    for (const auto &val : (*wp)->vals()) {
      if (auto shape_val = boost::get<shape>(&val)) {
        result.push_back(*shape_val);
      }
    }
  }

  return result;
}

void assembly::traverse(
    std::function<void(const std::string &, std::shared_ptr<const assembly>)>
        callback) const {
  for (const auto &child : children_) {
    child->traverse(callback);
  }
  callback(name_, shared_from_this());
}

std::unordered_map<std::string, std::shared_ptr<assembly>> assembly::flatten() {
  return flatten({});
}

std::unordered_map<std::string, std::shared_ptr<assembly>>
assembly::flatten(const std::vector<std::string> &parents) {
  std::unordered_map<std::string, std::shared_ptr<assembly>> result;

  std::vector<std::string> current_path = parents;
  current_path.push_back(name_);

  for (const auto &child : children_) {
    auto child_flattened = child->flatten(current_path);
    result.insert(child_flattened.begin(), child_flattened.end());
  }

  std::string path;
  for (size_t i = 0; i < current_path.size(); ++i) {
    if (i != 0)
      path += "/";
    path += current_path[i];
  }
  result[path] = shared_from_this();

  return result;
}

void assembly::iterate(const assembly_iterator &callback,
                       std::shared_ptr<topo_location> loc,
                       const std::string &name,
                       std::shared_ptr<Quantity_Color> color) const {
  std::string current_name = name.empty() ? name_ : name + "/" + name_;
  auto current_loc = loc ? std::make_shared<topo_location>(*loc * *loc_) : loc_;
  auto current_color = color_ ? color_ : color;

  if (obj_.which() != 2) { // Not nullptr
    compound shape_obj;

    if (auto sh = boost::get<shape>(&obj_)) {
      shape_obj = *sh->cast<topo::compound>();
    } else if (auto wp = boost::get<std::shared_ptr<workplane>>(&obj_)) {
      std::vector<shape> shapes;
      for (const auto &val : (*wp)->vals()) {
        if (auto s = boost::get<shape>(&val)) {
          shapes.push_back(*s);
        }
      }
      shape_obj = compound::make_compound(shapes);
    }

    if (shape_obj) {
      callback(shape_obj, current_name, current_loc, current_color);
    }
  }

  for (const auto &child : children_) {
    child->iterate(callback, current_loc, current_name, current_color);
  }
}

compound assembly::to_compound() const {
  auto shapes = this->shapes();

  for (const auto &child : children_) {
    shapes.push_back(child->to_compound());
  }

  auto result = compound::make_compound(shapes);
  if (loc_) {
    result.transform(*loc_);
  }

  return result;
}

std::pair<topo_location, std::string>
assembly::sub_location(const std::string &name) const {
  // 1. Find target object
  auto it = objects_.find(name);
  if (it == objects_.end()) {
    throw std::invalid_argument("Object not found: " + name);
  }

  auto obj = it->second;
  topo_location result_loc; // Identity by default
  std::string top_name = name;

  // 2. Check if needs location calculation
  bool is_child =
      std::find(children_.begin(), children_.end(), obj) != children_.end();
  if (!is_child && obj.get() != this) {
    std::vector<topo_location> loc_chain;
    auto current = obj;

    // 3. Walk up the parent chain
    while (auto parent = current->parent_.lock()) {
      if (parent.get() == this)
        break;

      loc_chain.push_back(*current->loc_);
      current = parent;
      top_name = current->name_;
    }

    // 4. Combine locations in parent-to-child order
    for (auto it = loc_chain.rbegin(); it != loc_chain.rend(); ++it) {
      result_loc = (*it) * result_loc; // l2 * l1 composition
    }
  }

  return {result_loc, top_name};
}
} // namespace topo
} // namespace flywave
