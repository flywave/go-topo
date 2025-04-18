#include <BRepBuilderAPI_Copy.hxx>
#include <TopExp.hxx>
#include <TopoDS.hxx>

#include "comp_solid.hh"

namespace flywave {
namespace topo {

comp_solid comp_solid::make_comp_solid(std::vector<solid> &shapes) {
  BRep_Builder B;
  TopoDS_CompSolid C;
  B.MakeCompSolid(C);
  for (unsigned i = 0; i < shapes.size(); i++) {
    B.Add(C, shapes[i].value());
  }
  return comp_solid{C};
}

comp_solid comp_solid::make_comp_solid(std::initializer_list<solid> &shapes) {
  BRep_Builder B;
  TopoDS_CompSolid C;
  B.MakeCompSolid(C);
  for (auto _shp : shapes) {
    B.Add(C, _shp.value());
  }
  return comp_solid{C};
}

TopoDS_CompSolid &comp_solid::value() { return TopoDS::CompSolid(_shape); }

const TopoDS_CompSolid &comp_solid::value() const {
  return TopoDS::CompSolid(_shape);
}

shape comp_solid::copy(bool deep) const {
  try {
    BRepBuilderAPI_Copy _copy(_shape, deep);
    _copy.Build();

    if (!_copy.IsDone())
      throw std::runtime_error("Section operation failed");

    auto shp = _copy.Shape();

    if (shp.IsNull())
      throw std::runtime_error("Shell operation resulted in Null shape");

    return comp_solid{*this, shp};
  } catch (Standard_Failure &e) {
    const Standard_CString msg = e.GetMessageString();
    if (msg != nullptr && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to offset face");
    }
  }
  return comp_solid{};
}

} // namespace topo
} // namespace flywave
