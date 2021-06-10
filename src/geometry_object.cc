#include "geometry_object.hh"
#include "shape.hh"
#include <BRepTools.hxx>

namespace flywave {
namespace topo {

std::string geometry_object::to_brep() {
  if (!is_valid())
    return std::string{};
  std::ostringstream oss;
  if (dynamic_cast<shape *>(this)) {
    BRepTools::Write((TopoDS_Shape &)*this, oss);
    return std::string(oss.str().c_str());
  }

  return std::string{};
}
} // namespace topo
} // namespace flywave
