#pragma once

#include "shape_geom_type.hh"
#include "vector.hh"

#include <algorithm>
#include <functional>
#include <memory>
#include <vector>

namespace flywave {
namespace topo {

class shape;
class selector;

using selector_ptr = std::shared_ptr<selector>;

class selector : public std::enable_shared_from_this<selector> {
public:
  virtual ~selector() = default;
  virtual std::vector<shape> filter(const std::vector<shape> &shapes) const = 0;

  selector_ptr operator&&(const selector_ptr &other) const;
  selector_ptr operator||(const selector_ptr &other) const;
  selector_ptr operator-(const selector_ptr &other) const;
  selector_ptr operator!() const;
};

class custom_selector : public selector {
public:
  using func_t = std::function<std::vector<shape>(const std::vector<shape> &)>;

private:
  func_t func_;

public:
  explicit custom_selector(func_t &&func) : func_(std::move(func)) {}

  std::vector<shape> filter(const std::vector<shape> &shapes) const override {
    return func_(shapes);
  }
};

class nearest_to_point_selector : public selector {
  topo_vector point_;

public:
  explicit nearest_to_point_selector(const topo_vector &p);

  std::vector<shape> filter(const std::vector<shape> &objects) const override;
};

class box_selector : public selector {
  topo_vector p0_, p1_;
  bool use_bounding_box_;

  bool is_inside(const topo_vector &p) const {
    return ((p.x() < p0_.x()) != (p.x() < p1_.x())) &&
           ((p.y() < p0_.y()) != (p.y() < p1_.y())) &&
           ((p.z() < p0_.z()) != (p.z() < p1_.z()));
  }

public:
  box_selector(const topo_vector &p0, const topo_vector &p1,
               bool use_bb = false);

  std::vector<shape> filter(const std::vector<shape> &objects) const override;
};

using clustered_shapes = std::vector<std::vector<shape>>;

class nth_selector : public selector {
protected:
  int n_;
  bool direction_max_;
  double tolerance_;

  virtual double get_key(const shape &obj) const = 0;

  clustered_shapes cluster(const std::vector<shape> &objects) const;

public:
  nth_selector(int n, bool direction_max = true, double tolerance = 1e-4);

  std::vector<shape> filter(const std::vector<shape> &objects) const override;
};

class radius_nth_selector : public nth_selector {
protected:
  double get_key(const shape &obj) const override;

public:
  radius_nth_selector(int n, bool direction_max = true, double tolerance = 1e-4)
      : nth_selector(n, direction_max, tolerance) {}

  using nth_selector::nth_selector;
};

class center_nth_selector : public nth_selector {
  topo_vector direction_;

protected:
  double get_key(const shape &obj) const override;

public:
  center_nth_selector(const topo_vector &dir, int n, bool direction_max = true,
                      double tolerance = 1e-4)
      : nth_selector(n, direction_max, tolerance),
        direction_(dir.normalized()) {}
};

class direction_minmax_selector : public center_nth_selector {
public:
  direction_minmax_selector(const topo_vector &dir, bool direction_max = true,
                            double tolerance = 1e-4)
      : center_nth_selector(dir, -1, direction_max, tolerance) {}
};

class direction_selector : public selector {
private:
  friend class string_syntax_selector;

protected:
  topo_vector direction_;
  double tolerance_;

public:
  direction_selector(const topo_vector &dir, double tol = 1e-4)
      : direction_(dir.normalized()), tolerance_(tol) {}

  virtual bool test(const topo_vector &vec) const = 0;

  std::vector<shape> filter(const std::vector<shape> &objects) const override;
};

class parallel_dir_selector : public direction_selector {
public:
  using direction_selector::direction_selector;

  bool test(const topo_vector &vec) const override {
    return direction_.cross(vec).length() < tolerance_;
  }
};

class dir_selector : public direction_selector {
public:
  using direction_selector::direction_selector;

  bool test(const topo_vector &vec) const override {
    return std::abs(direction_.angle(vec)) < tolerance_;
  }
};

class perpendicular_dir_selector : public direction_selector {
public:
  using direction_selector::direction_selector;

  bool test(const topo_vector &vec) const override {
    return std::abs(direction_.angle(vec) - M_PI_2) < tolerance_;
  }
};

class direction_nth_selector : public selector {
  parallel_dir_selector _dir_selector;
  center_nth_selector _nth_selector;

public:
  direction_nth_selector(const topo_vector &dir, int n,
                         bool direction_max = true, double tolerance = 1e-4)
      : _dir_selector(dir, tolerance),
        _nth_selector(dir, n, direction_max, tolerance) {}

  std::vector<shape> filter(const std::vector<shape> &objects) const override;
};

class length_nth_selector : public nth_selector {
protected:
  double get_key(const shape &obj) const override;

public:
  using nth_selector::nth_selector;
};

class type_selector : public selector {
  shape_geom_type type_;

public:
  type_selector(const shape_geom_type &type) : type_(type) {}

  std::vector<shape> filter(const std::vector<shape> &objects) const override;
};

class area_nth_selector : public nth_selector {
protected:
  double get_key(const shape &obj) const override;

public:
  using nth_selector::nth_selector;
};

class binary_selector : public selector {
protected:
  selector_ptr left_;
  selector_ptr right_;

public:
  binary_selector(selector_ptr left, selector_ptr right)
      : left_(left), right_(right) {}

  virtual std::vector<shape>
  filter_results(const std::vector<shape> &left,
                 const std::vector<shape> &right) const = 0;

  std::vector<shape> filter(const std::vector<shape> &objects) const override;
};

class and_selector : public binary_selector {
public:
  using binary_selector::binary_selector;

  std::vector<shape>
  filter_results(const std::vector<shape> &left,
                 const std::vector<shape> &right) const override;
};

class or_selector : public binary_selector {
public:
  using binary_selector::binary_selector;

  std::vector<shape>
  filter_results(const std::vector<shape> &left,
                 const std::vector<shape> &right) const override;
};

class subtract_selector : public binary_selector {
public:
  using binary_selector::binary_selector;

  std::vector<shape>
  filter_results(const std::vector<shape> &left,
                 const std::vector<shape> &right) const override;
};

class not_selector : public selector {
  selector_ptr selector_;

public:
  explicit not_selector(selector_ptr sel) : selector_(sel) {}

  std::vector<shape> filter(const std::vector<shape> &objects) const override;
};

class string_syntax_selector : public selector {
  selector_ptr selector_;

public:
  string_syntax_selector(const std::string &selector_str);

  std::vector<shape> filter(const std::vector<shape> &objects) const override {
    return selector_->filter(objects);
  }
};

} // namespace topo
} // namespace flywave
