#include "shape.hh"
#include "solid.hh"

#include <iostream>
#include <memory>
#include <string>

using namespace flywave::topo;

class mock_mesh_receiver : public flywave::topo::mesh_receiver {
public:
  mock_mesh_receiver() {}
  virtual ~mock_mesh_receiver() {}

  void begin() override {}

  void end() override {}

  int append_face(Quantity_Color color) override { return 1; }

  void append_node(int face, gp_Pnt p, gp_Pnt n) override {}

  void append_node(int face, gp_Pnt p, gp_Pnt n, gp_Pnt2d uv) override {}

  void append_node(int face, gp_Pnt p) override {}

  void append_triangle(int face, int tri[3]) override {}
};

int main() {
  mock_mesh_receiver recv;
  auto _solid = solid::make_solid_from_sphere(10);
  int res = _solid.mesh(recv, 1.0e-06, 0.1, 0.5, true);
  if (res != 0) {
    printf("error!");
  }
  return 0;
}