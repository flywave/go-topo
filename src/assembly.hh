#pragma once

#include <memory>
#include <string>

#include <boost/any.hpp>
#include <boost/variant.hpp>

#include <Quantity_Color.hxx>

#include "location.hh"
#include "solver.hh"

namespace flywave {
namespace topo {

class shape;
class compound;
class workplane;

using assembly_object =
    boost::variant<shape, std::shared_ptr<workplane>, std::nullptr_t>;

class assembly : public std::enable_shared_from_this<assembly> {
public:
  // Construction
  assembly(assembly_object obj = nullptr,
           std::shared_ptr<topo_location> loc = nullptr,
           const std::string &name = "",
           std::shared_ptr<Quantity_Color> color = nullptr,
           const std::unordered_map<std::string, boost::any> &metadata = {});

  // Copy control
  assembly(const assembly &) = delete;
  assembly &operator=(const assembly &) = delete;
  ~assembly() = default;

  std::shared_ptr<assembly> copy() const;

  // Tree operations
  assembly &
  add(assembly_object obj, std::shared_ptr<topo_location> loc = nullptr,
      const std::string &name = "",
      std::shared_ptr<Quantity_Color> color = nullptr,
      const std::unordered_map<std::string, boost::any> &metadata = {});

  assembly &add(std::shared_ptr<assembly> subAssembly,
                std::shared_ptr<topo_location> loc = nullptr,
                const std::string &name = "",
                std::shared_ptr<Quantity_Color> color = nullptr);

  assembly &remove(const std::string &name);

  assembly &constrain(const std::string &q1, const std::string &q2,
                      ConstraintKind kind, const ConstraintParam &param = {});

  assembly &constrain(const std::string &q1, ConstraintKind kind,
                      const ConstraintParam &param = {});

  assembly &constrain(const std::string &id1, const shape &s1,
                      const std::string &id2, const shape &s2,
                      ConstraintKind kind, const ConstraintParam &param = {});

  assembly &constrain(const std::string &id1, const shape &s1,
                      ConstraintKind kind, const ConstraintParam &param = {});

  assembly &solve(int verbosity = 0);

  assembly &
  export_to(const std::string &path, const std::string &exportType = "",
            const std::string &mode = "default", double tolerance = 0.1,
            double angularTolerance = 0.1,
            const std::unordered_map<std::string, boost::any> &kwargs = {});

  // Accessors
  std::vector<shape> shapes() const;

  void traverse(
      std::function<void(const std::string &, std::shared_ptr<const assembly>)>
          callback) const;

  compound to_compound() const;

  std::unordered_map<std::string, std::shared_ptr<assembly>> flatten();

  // Iterators
  using assembly_iterator = std::function<void(
      const shape &, const std::string &, std::shared_ptr<topo_location>,
      std::shared_ptr<Quantity_Color>)>;

  void iterate(const assembly_iterator &callback,
               std::shared_ptr<topo_location> loc = nullptr,
               const std::string &name = "",
               std::shared_ptr<Quantity_Color> color = nullptr) const;

private:
  // Internal methods
  std::pair<std::string, shape> query(const std::string &q) const;
  std::pair<topo_location, std::string>
  sub_location(const std::string &name) const;
  assembly &add_constraint_impl(const std::string &id1, const shape *s1,
                                const std::string &id2, const shape *s2,
                                ConstraintKind kind,
                                const ConstraintParam &param, bool isBinary);
  std::unordered_map<std::string, std::shared_ptr<assembly>>
  flatten(const std::vector<std::string> &parents);

  // Data members
  std::shared_ptr<topo_location> loc_;
  std::string name_;
  std::shared_ptr<Quantity_Color> color_;
  std::unordered_map<std::string, boost::any> metadata_;

  assembly_object obj_;
  std::weak_ptr<assembly> parent_;
  std::vector<std::shared_ptr<assembly>> children_;

  std::unordered_map<std::string, std::shared_ptr<assembly>> objects_;
  std::vector<std::shared_ptr<constraint_spec>> constraints_;

  boost::optional<std::map<std::string, double>> solveResult_;
};

} // namespace topo
} // namespace flywave
