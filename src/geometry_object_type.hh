#ifndef __FLYWAVE_TOPO_GEOMETRY_OBJECT_TYPE_HH__
#define __FLYWAVE_TOPO_GEOMETRY_OBJECT_TYPE_HH__

namespace flywave {
namespace topo {

enum class geometry_object_type {
  SolidType,
  ShellType,
  FaceType,
  EdgeType,
  VertexType,
  WireType,
  CompoundType,
  CompSolidType,
  ShapeType,
};

} // namespace topo
} // namespace flywave

#endif // __FLYWAVE_TOPO_GEOMETRY_OBJECT_TYPE_HH__
