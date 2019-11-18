#ifndef __FLYWAVE_TOPO_GEOMETRY_OBJECT_HH__
#define __FLYWAVE_TOPO_GEOMETRY_OBJECT_HH__

#include "geometry_object_type.hh"

#include <boost/optional.hpp>

namespace flywave {
namespace topo {

class geometry_object : enable_shared_from_this<geometry_object> {
protected:
  void *tag;

public:
  geometry_object() = default;
  virtual ~geometry_object() {}

  virtual bool is_null() const = 0;
  virtual bool is_valid() const = 0;

  virtual geometry_object_type type() const = 0;

  virtual bbox3d bounding_box(double tolerance = 1e-12) const = 0;

  virtual bool equals(const geometry_object &) const = 0;

  std::string to_brep();

  void *get_tag() const { return tag; }
  void set_tag(void *_tag) { tag = _tag; }
};

} // namespace topo
} // namespace flywave

#endif // __FLYWAVE_TOPO_GEOMETRY_OBJECT_HH__
