#ifndef __FLYWAVE_TOPO_GEOMETRY_OBJECT_HH__
#define __FLYWAVE_TOPO_GEOMETRY_OBJECT_HH__

#include "geometry_object_type.hh"

#include <Bnd_Box.hxx>

#include <boost/optional.hpp>

#include <memory>

namespace flywave {
namespace topo {

class geometry_object : public std::enable_shared_from_this<geometry_object> {
protected:
  void *tag;

public:
  geometry_object() = default;
  virtual ~geometry_object() {}

  virtual bool is_null() const = 0;
  virtual bool is_valid() const = 0;

  virtual geometry_object_type type() const = 0;

  virtual Bnd_Box bounding_box(double tolerance = 1e-12) const = 0;

  virtual bool equals(const geometry_object &) const = 0;

  std::string to_brep();

  void *get_tag() const { return tag; }
  void set_tag(void *_tag) { tag = _tag; }
};

} // namespace topo
} // namespace flywave

#endif // __FLYWAVE_TOPO_GEOMETRY_OBJECT_HH__
