#include "context.hh"
#include "edge.hh"
#include "wire.hh"

namespace flywave {
namespace topo {

context::context() : tolerance_(0.0001) {}

std::vector<edge> context::pop_pending_edges(bool errorOnEmpty) {
  if (errorOnEmpty && pending_edges_.empty()) {
    throw std::runtime_error("No pending edges present");
  }

  std::vector<edge> result;
  std::swap(result, pending_edges_);
  return result;
}

std::vector<wire> context::pop_pending_wires(bool errorOnEmpty) {
  if (errorOnEmpty && pending_wires_.empty()) {
    throw std::runtime_error("No pending wires present");
  }

  std::vector<wire> result;
  std::swap(result, pending_wires_);
  return result;
}

std::vector<wire> &context::pending_wires() { return pending_wires_; }

void context::set_pending_edges(const std::vector<edge> &edges) {
  pending_edges_ = edges;
}

std::vector<edge> &context::pending_edges() { return pending_edges_; }

void context::set_pending_wires(const std::vector<wire> &wires) {
  pending_wires_ = wires;
}

boost::optional<flywave::topo::topo_vector> context::first_point() {
  return first_point_;
}

void context::set_first_point(boost::optional<topo_vector> point) {
  first_point_ = point;
}

double context::tolerance() const { return tolerance_; }

void context::set_tolerance(double tol) { tolerance_ = tol; }

std::unordered_map<std::string, std::shared_ptr<workplane>> &context::tags() {
  return tags_;
}
} // namespace topo
} // namespace flywave
