#pragma once

// parametric — 装配级参数化配方工厂 (go 侧 assembly_parametric.go 的 C++ 对应物)。
//
// 设计约束: C++ 核心不含 JSON 库 —— params 是不透明字符串, builder 各自解析;
// ParametricElement 导出/导入 JSON 树在各绑定层 (Embind/cgo) 组装。
// 配方数据挂 assembly 节点的 metadata (copy/move 携带), 不需要 go 侧
// "按节点名同步" 的变通 —— C++ 对象上直接可存。

#include <functional>
#include <optional>
#include <shared_mutex>
#include <string>
#include <vector>

#include "assembly.hh"

namespace flywave {
namespace topo {

// 参数化配方: primitive 类型 + 参数 (不透明 JSON 文本)
struct parametric_data {
  std::string type;
  std::string params;

  bool operator==(const parametric_data &o) const {
    return type == o.type && params == o.params;
  }
  bool operator!=(const parametric_data &o) const { return !(*this == o); }
};

// builder 的产出: 几何体 + 缺省放置。
// loc 仅在节点未携带 location 时作为缺省; 节点 location 优先 (与 go 一致)。
struct parametric_build_result {
  shape shp;
  std::shared_ptr<topo_location> loc;
};

// 由参数 (不透明 JSON 文本) 重建几何; 失败抛 std::runtime_error
using parametric_builder =
    std::function<parametric_build_result(const std::string &params)>;

// 注册 builder; 传空 fn 注销 (与 go RegisterParametricBuilder 语义一致)。
// 线程安全 (内部 shared_mutex)。
void register_parametric_builder(const std::string &type_name,
                                 parametric_builder fn);

bool has_parametric_builder(const std::string &type_name);

// 按 type 分发 builder; 未注册 / builder 失败 / 空产出 抛 std::runtime_error
// (错误文案与 go 侧逐字对齐, 便于上层统一呈现)
parametric_build_result build_parametric(const std::string &type_name,
                                         const std::string &params);

// ---- 节点挂载 (metadata 承载, 键为 parametric_metadata_key) ----

constexpr const char *parametric_metadata_key = "__parametric__";

void set_parametric(assembly &a, const parametric_data &data);

// 未设置返回 nullopt (与 go Parametric() 返回 nil 一致)
std::optional<parametric_data> get_parametric(const assembly &a);

// 重建一个装配节点 (含子树): 有配方的节点分发 builder, 无配方的容器节点
// 用原点 vertex 占位 (空 compound 是 null shape, assembly 构造不接受 ——
// 与 go rebuildParametricNode 同一处理)。
// location 规则: builder 缺省 loc 仅在节点未携带 location 时生效;
// 节点 location 优先。color 传入时设置节点颜色。
// 未注册的 type 抛 std::runtime_error。
std::shared_ptr<assembly>
rebuild_parametric_node(const std::string &name,
                        const std::optional<parametric_data> &data,
                        const std::optional<topo_location> &loc,
                        std::optional<Quantity_Color> color,
                        const std::vector<std::shared_ptr<assembly>> &children);

} // namespace topo
} // namespace flywave
