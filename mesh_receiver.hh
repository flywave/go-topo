#ifndef __FLYWAVE_MESH_TOPO_MESH_RECEIVER_HH__
#define __FLYWAVE_MESH_TOPO_MESH_RECEIVER_HH__

namespace flywave {
namespace topo {

class mesh_receiver {
public:
  mesh_receiver() = default;
  virtual ~mesh_receiver() = default;

  virtual void begin() = 0;

  virtual void end() = 0;

  virtual int append_face(color4i color) = 0;

  virtual void append_node(int face, gp_Pnt p, gp_Pnt n, double2 uv) = 0;

  virtual void append_node(int face, gp_Pnt p, gp_Pnt n) = 0;

  virtual void append_node(int face, gp_Pnt p) = 0;

  virtual void append_triangle(int face, uint3 tri) = 0;

  virtual void append_quad(int face, uint4 quad) = 0;
};

} // namespace topo
} // namespace flywave

#endif // __FLYWAVE_MESH_TOPO_MESH_RECEIVER_HH__
