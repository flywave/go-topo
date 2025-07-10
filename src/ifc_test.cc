#include "ifc.hh"
#include "ifc_c_api.h"

#include <iostream>
#include <memory>
#include <string>

int main() {
  std::string path{"./tests/模型整合-主管道.ifc"};
  auto ct = flywave::ifc::get_convert(path);
  ct->load();
  auto v = ct->get_version();
  std::cout << v << std::endl;
  auto ents = ct->get_element_infos();
  for (auto &ent : ents) {
    std::cout << ent.name << std::endl;
  }
  auto tris = ct->get_geometry();
  for (auto &tri : tris) {
     std::cout << tri.triangulation << std::endl;
  }
  auto data = ct->get_data();
  std::cout << data->header.file_name.name << std::endl;

  return 0;
}
