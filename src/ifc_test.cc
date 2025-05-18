#include "ifc.hh"
#include "ifc_c_api.h"

#include <iostream>
#include <memory>
#include <string>


int main() {
  std::string path{"./tests/BIM.ifc"};
  auto ct = flywave::ifc::get_convert(path);
  return 0;
}