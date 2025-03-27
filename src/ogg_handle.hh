#pragma once

#include <Standard_Handle.hxx>
#include <Standard_Version.hxx>
#include <utility>

namespace flywave {

template <typename T> using ogg_handle = opencascade::handle<T>;

template <typename T, typename... Args>
ogg_handle<T> make_ogg_handle(Args &&...args) {
  return new T(std::forward<Args>(args)...);
}

} // namespace flywave

#if OCC_VERSION_HEX < 0x070800
namespace std {

template <typename T> struct hash<opencascade::handle<T>> {
  inline std::size_t operator()(const opencascade::handle<T> &hnd) const {
    return hash<T *>{}(hnd.get());
  }
};

} // namespace std
#endif