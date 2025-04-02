#pragma once

#include <boost/optional.hpp>
#include <memory>
#include <stdexcept>
#include <unordered_map>
#include <vector>

#include <gp_Pnt.hxx>

#include "vector.hh"

namespace flywave {
namespace topo {

class wire;
class edge;
class workplane;

class context : public std::enable_shared_from_this<context> {
public:
  // 构造函数
  context();

  // 边操作
  std::vector<edge> pop_pending_edges(bool errorOnEmpty = true);

  // 线操作
  std::vector<wire> pop_pending_wires(bool errorOnEmpty = true);

  // 成员访问
  std::vector<wire> &pending_wires();

  void set_pending_wires(const std::vector<wire> &wires);

  std::vector<edge> &pending_edges();

  void set_pending_edges(const std::vector<edge> &edges);

  boost::optional<topo_vector> first_point();

  void set_first_point(boost::optional<topo_vector> point);

  double tolerance() const;
  void set_tolerance(double tol);
  std::unordered_map<std::string, std::shared_ptr<workplane>> &tags();

private:
  std::vector<wire> pending_wires_;
  std::vector<edge> pending_edges_;
  boost::optional<topo_vector> first_point_;
  double tolerance_;
  std::unordered_map<std::string, std::shared_ptr<workplane>> tags_;
};

} // namespace topo
} // namespace flywave