#pragma once

#include <vector>

namespace flywave {
namespace topo {

class shape;

class selector {
public:
  virtual ~selector() = default;
  virtual std::vector<shape> filter(const std::vector<shape> &shapes) const = 0;
};
} // namespace topo
} // namespace flywave