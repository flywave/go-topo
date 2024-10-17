#include "ifc.hh"
#include "ifc_c_api.h"

#include <iostream>
#include <memory>
#include <string>

struct visitor : flywave::ifc::visitor {
  virtual void
  apply(const ifc23::IfcGeom::TriangulationElement<double> *element) {
    std::cout <<  "name: "<< element->name() << "  id: "<< element->id() << "  guid: "<< element->guid() << "  type: "
              << element->type() << std::endl;
  }
  virtual void
  apply(const ifc4::IfcGeom::TriangulationElement<double> *element) {}
  virtual void
  apply(const ifc41::IfcGeom::TriangulationElement<double> *element) {}
  virtual void
  apply(const ifc42::IfcGeom::TriangulationElement<double> *element) {}
  virtual void
  apply(const ifc43_rc1::IfcGeom::TriangulationElement<double> *element) {}
};

int main() {
  std::string path{"./tests/BIM.ifc"};
  auto ct = flywave::ifc::get_convert(path);
  visitor vt{};
  ct->process_with_callback(&vt);
  return 0;
}