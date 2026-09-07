#pragma once

// cgo 边界全局串行锁:
// Go 侧 finalizer 线程会在任意时刻调用 *_free 系列释放 C++ 对象,
// 与主 goroutine 正在执行的 C++ 调用 (OCC/IPOPT 深处) 并发时会产生
// 分配器/对象级数据竞争, 间歇性破坏堆 (实测 abort)。
// 此递归锁将所有 C API 调用串行化; 同线程内的 C 回调再入 C API
// 可重入, 无死锁。inline 函数保证跨编译单元单实例。

#include <mutex>

namespace flywave {
namespace topo {

inline std::recursive_mutex &topo_glock() {
  static std::recursive_mutex m;
  return m;
}

} // namespace topo
} // namespace flywave
