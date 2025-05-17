#include "ifc.hh"
#include "ifc_c_api.h"

#include <iostream>
#include <memory>
#include <string>

struct visitor : flywave::ifc::visitor {
  virtual void apply(const IfcGeom::TriangulationElement *element) {
    std::cout << "name: " << element->name() << "  id: " << element->id()
              << "  guid: " << element->guid() << "  type: " << element->type()
              << std::endl;
  }
};

int main() {
  std::string path{"./tests/BIM.ifc"};
  auto ct = flywave::ifc::get_convert(path);
  visitor vt{};
  ct->process_with_callback(&vt);
  return 0;
}