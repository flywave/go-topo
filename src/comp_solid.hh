#ifndef __FLYWAVE_MESH_TOPO_COMPSOLID_HH__
#define __FLYWAVE_MESH_TOPO_COMPSOLID_HH__

#include <BRep_Builder.hxx>
#include <TopoDS_CompSolid.hxx>

#include "solid.hh"

namespace flywave {
namespace topo {

class comp_solid_iterator;

class comp_solid : public solid {
public:
  comp_solid() = default;
  virtual ~comp_solid() = default;

  static comp_solid make_comp_solid(std::vector<solid> &shapes);

  static comp_solid make_comp_solid(std::initializer_list<solid> &shapes);

  template <typename TShp1, typename TShp2, typename... TShp>
  static comp_solid make_comp_solid(TShp1 &&shp1, TShp2 &&shp2, TShp &&...shps);

  TopoDS_CompSolid &value();
  const TopoDS_CompSolid &value() const;

  virtual geometry_object_type type() const override {
    return geometry_object_type::CompSolidType;
  }

  virtual shape copy(bool deep = true) const override;

  comp_solid(TopoDS_Shape shp, bool forConstruction = false)
      : solid(shp, forConstruction) {}
  comp_solid(const shape &s, TopoDS_Shape shp) : solid(s, shp) {}

protected:
  friend class comp_solid_iterator;
  friend class shape;
};

namespace _helper {
inline void make_compound_helper(BRep_Builder &aBuilder,
                                 TopoDS_CompSolid &aRes) {}

template <typename TShp1, typename... TShp>
void make_compound_helper(BRep_Builder &aBuilder, TopoDS_CompSolid &aRes,
                          TShp1 &&shp1, TShp &&...shps) {
  aBuilder.Add(aRes, shp1);
  make_compound_helper(aBuilder, aRes, std::forward<TShp>(shps)...);
}
} // namespace _helper

template <typename TShp1, typename TShp2, typename... TShp>
comp_solid comp_solid::make_comp_solid(TShp1 &&shp1, TShp2 &&shp2,
                                       TShp &&...shps) {
  TopoDS_CompSolid aRes;
  BRep_Builder aBuilder;
  aBuilder.MakeCompSolid(aRes);
  _helper::make_compound_helper(aBuilder, aRes, shp1, shp2,
                                std::forward<TShp>(shps)...);
  return comp_solid{aRes};
}

class comp_solid_iterator {
public:
  TopExp_Explorer ex;
  comp_solid_iterator(shape &arg) : ex(arg.value(), TopAbs_COMPSOLID) {}
  void reset() { ex.ReInit(); }
  boost::optional<comp_solid> next() {
    if (ex.More()) {
      comp_solid ret{ex.Current()};
      ex.Next();
      return {ret};
    } else {
      return boost::none;
    }
  }
};
} // namespace topo
} // namespace flywave

#endif // __FLYWAVE_MESH_TOPO_COMPSOLID_HH__
