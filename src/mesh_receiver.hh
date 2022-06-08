#ifndef __FLYWAVE_MESH_TOPO_MESH_RECEIVER_HH__
#define __FLYWAVE_MESH_TOPO_MESH_RECEIVER_HH__

#include <Quantity_Color.hxx>

namespace flywave {
namespace topo {

class mesh_receiver {
public:
  mesh_receiver() = default;
  virtual ~mesh_receiver() = default;

  virtual void begin() = 0;

  virtual void end() = 0;

  virtual int append_face(Quantity_Color color) = 0;

  virtual void append_node(int face, gp_Pnt p, gp_Pnt n) = 0;

  virtual void append_node(int face, gp_Pnt p) = 0;

  virtual void append_node(int face, gp_Pnt p, gp_Pnt n, gp_Pnt2d uv) = 0;

  virtual void append_triangle(int face, int tri[3]) = 0;
};

} // namespace topo
} // namespace flywave

#endif // __FLYWAVE_MESH_TOPO_MESH_RECEIVER_HH__
