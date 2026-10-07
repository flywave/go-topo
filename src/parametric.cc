#include "parametric.hh"

#include <boost/any.hpp>

#include "vertex.hh"

namespace flywave {
namespace topo {

namespace {

std::shared_mutex &registry_mutex() {
  static std::shared_mutex mu;
  return mu;
}

std::unordered_map<std::string, parametric_builder> &registry() {
  static std::unordered_map<std::string, parametric_builder> reg;
  return reg;
}

} // namespace

void register_parametric_builder(const std::string &type_name,
                                 parametric_builder fn) {
  std::unique_lock<std::shared_mutex> lock(registry_mutex());
  if (fn) {
    registry()[type_name] = std::move(fn);
  } else {
    registry().erase(type_name);
  }
}

bool has_parametric_builder(const std::string &type_name) {
  std::shared_lock<std::shared_mutex> lock(registry_mutex());
  return registry().count(type_name) > 0;
}

parametric_build_result build_parametric(const std::string &type_name,
                                         const std::string &params) {
  parametric_builder fn;
  {
    std::shared_lock<std::shared_mutex> lock(registry_mutex());
    auto it = registry().find(type_name);
    if (it == registry().end()) {
      throw std::runtime_error("assembly: no parametric builder registered for type \"" +
                               type_name + "\"");
    }
    fn = it->second;
  }
  // builder 在锁外执行: 注册表热更新不阻塞长构建
  auto result = fn(params);
  if (result.shp.is_null()) {
    throw std::runtime_error("assembly: builder for type \"" + type_name +
                             "\" returned a null shape");
  }
  return result;
}

void set_parametric(assembly &a, const parametric_data &data) {
  a.set_metadata(parametric_metadata_key, parametric_data{data});
}

std::optional<parametric_data> get_parametric(const assembly &a) {
  // assembly::metadata() 的访问口在 C++ 侧走 const 查询
  const auto &meta = a.metadata();
  auto it = meta.find(parametric_metadata_key);
  if (it == meta.end()) {
    return std::nullopt;
  }
  if (auto *p = boost::any_cast<parametric_data>(&it->second)) {
    return *p;
  }
  return std::nullopt;
}

std::shared_ptr<assembly>
rebuild_parametric_node(const std::string &name,
                        const std::optional<parametric_data> &data,
                        const std::optional<topo_location> &loc,
                        std::optional<Quantity_Color> color,
                        const std::vector<std::shared_ptr<assembly>> &children) {
  shape shp;
  std::shared_ptr<topo_location> default_loc;
  if (data && !data->type.empty()) {
    auto result = build_parametric(data->type, data->params);
    shp = result.shp;
    default_loc = result.loc;
  } else {
    // 无配方: 容器节点, 用原点 vertex 占位 (与 go rebuildParametricNode 一致)
    shp = vertex(0, 0, 0);
  }
  std::shared_ptr<topo_location> effective =
      loc ? std::make_shared<topo_location>(*loc) : default_loc;
  std::shared_ptr<Quantity_Color> color_ptr =
      color ? std::make_shared<Quantity_Color>(*color) : nullptr;

  auto node = assembly::create(shp, effective, name, color_ptr);
  if (data && !data->type.empty()) {
    set_parametric(*node, *data);
  }
  for (auto &child : children) {
    // loc/color 传 nullptr: 保留子节点自身构造时的值 (与 go 一致)
    node->add(child, nullptr, "", nullptr);
  }
  return node;
}

} // namespace topo
} // namespace flywave
