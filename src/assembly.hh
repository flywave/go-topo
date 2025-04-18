#pragma once

#include <memory>
#include <mutex>
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
    boost::variant<shape, std::shared_ptr<workplane>, boost::blank>;

struct assembly_element {
  shape shp;
  std::string name;
  topo_location location;
  std::shared_ptr<Quantity_Color> color;
};

enum class assembly_export_mode {
  defalut_,
  fuse,
  per_part,
};

class assembly : public std::enable_shared_from_this<assembly> {
public:
  static std::shared_ptr<assembly>
  create(assembly_object obj = boost::blank{},
         std::shared_ptr<topo_location> loc = nullptr,
         const std::string &name = "",
         std::shared_ptr<Quantity_Color> color = nullptr,
         const std::unordered_map<std::string, boost::any> &metadata = {});

  assembly(const assembly &) = delete;
  assembly &operator=(const assembly &) = delete;

  ~assembly() = default;

  assembly(assembly &&) noexcept;
  assembly &operator=(assembly &&) noexcept;

  std::shared_ptr<assembly> copy() const;

  bool operator<(const assembly &other) const { return name_ < other.name_; }

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
                      constraint_kind kind, const constraint_param &param = {});

  assembly &constrain(const std::string &q1, constraint_kind kind,
                      const constraint_param &param = {});

  assembly &constrain(const std::string &id1, const shape &s1,
                      const std::string &id2, const shape &s2,
                      constraint_kind kind, const constraint_param &param = {});

  assembly &constrain(const std::string &id1, const shape &s1,
                      constraint_kind kind, const constraint_param &param = {});

  assembly &solve(int verbosity = 0);

  assembly &
  export_to(const std::string &path,
            const assembly_export_mode &mode = assembly_export_mode::defalut_);

  std::vector<shape> shapes() const;

  void traverse(std::function<void(const std::string &, const assembly &)>
                    callback) const;

  compound to_compound() const;

  std::unordered_map<std::string, std::shared_ptr<assembly>> flatten();

  std::vector<assembly_element> get_elements() const;

  const std::string &name() const { return name_; }

  const topo_location &location() const {
    if (!loc_)
      return topo_location{};
    return *loc_;
  }

  bool has_color() const { return color_ != nullptr; }

  const Quantity_Color &color() const {
    if (!color_)
      return Quantity_Color();
    return *color_;
  }

  bool has_obj() const { return !boost::get<boost::blank>(&obj_); }

  const assembly_object &obj() const { return obj_; }

  std::vector<std::shared_ptr<assembly>> children() const { return children_; }

  bool has_error() const;

  void set_error(const std::string &error) const;

  const std::string &error() const;

  void clear_error();

protected:
  assembly(assembly_object obj = boost::blank{},
           std::shared_ptr<topo_location> loc = nullptr,
           const std::string &name = "",
           std::shared_ptr<Quantity_Color> color = nullptr,
           const std::unordered_map<std::string, boost::any> &metadata = {});

  std::pair<std::string, shape> query(const std::string &q) const;
  std::pair<topo_location, std::string>
  sub_location(const std::string &name) const;
  assembly &add_constraint_impl(const std::string &id1, const shape *s1,
                                const std::string &id2, const shape *s2,
                                constraint_kind kind,
                                const constraint_param &param, bool isBinary);
  std::unordered_map<std::string, std::shared_ptr<assembly>>
  flatten(const std::vector<std::string> &parents);
  std::vector<assembly_element>
  _get_elements(std::shared_ptr<topo_location> loc = nullptr,
                const std::string &name = "",
                std::shared_ptr<Quantity_Color> color = nullptr) const;

private:
  mutable std::mutex solve_mutex_;
  std::shared_ptr<topo_location> loc_;
  std::string name_;
  std::shared_ptr<Quantity_Color> color_;
  std::unordered_map<std::string, boost::any> metadata_;

  assembly_object obj_;
  std::weak_ptr<assembly> parent_;
  std::vector<std::shared_ptr<assembly>> children_;

  std::unordered_map<std::string, std::shared_ptr<assembly>> objects_;
  std::vector<constraint_spec> constraints_;
  mutable boost::optional<std::string> error_;

  boost::optional<std::map<std::string, double>> solve_result_;
};

} // namespace topo
} // namespace flywave
