#include "compound.hh"

#include <BRepBuilderAPI_Copy.hxx>
#include <TopoDS.hxx>

namespace flywave {
namespace topo {

compound compound::make_compound(std::vector<shape> &shapes) {
  BRep_Builder B;
  TopoDS_Compound C;
  B.MakeCompound(C);
  for (unsigned i = 0; i < shapes.size(); i++) {
    B.Add(C, shapes[i].value());
  }
  return compound{C};
}

compound compound::make_compound(std::initializer_list<shape> &shapes) {
  BRep_Builder B;
  TopoDS_Compound C;
  B.MakeCompound(C);
  for (auto _shp : shapes) {
    B.Add(C, _shp.value());
  }
  return compound{C};
}

TopoDS_Compound &compound::value() { return TopoDS::Compound(_shape); }

const TopoDS_Compound &compound::value() const {
  return TopoDS::Compound(_shape);
}

shape compound::copy(bool deep) const {
  try {
    BRepBuilderAPI_Copy _copy(_shape, deep);
    _copy.Build();

    if (!_copy.IsDone())
      throw std::runtime_error("Section operation failed");

    auto shp = _copy.Shape();

    if (shp.IsNull())
      throw std::runtime_error("Shell operation resulted in Null shape");

    return compound{*this, shp};
  } catch (Standard_Failure &e) {
    const Standard_CString msg = e.GetMessageString();
    if (msg != nullptr && strlen(msg) > 1) {
      throw std::runtime_error(msg);
    } else {
      throw std::runtime_error("Failed to offset face");
    }
  }
  return compound{};
}

} // namespace topo
} // namespace flywave
