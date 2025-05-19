#include "ifc.hh"
#include "ifc_c_api.h"

#include <iostream>
#include <memory>
#include <string>


int main() {
  std::string path{"./buildingElementProxy.ifc"};
  auto ct = flywave::ifc::get_convert(path);
  ct->load();
  auto v = ct->get_version();
  std::cout << v << std::endl;
  auto ents = ct->get_shape();
  for (auto &ent : ents) {
    std::cout << ent.name << std::endl;
  }
  auto tris = ct->get_geometry();
  for (auto &tri : tris) {
    std::cout << tri << std::endl;
  }
  return 0;
}
