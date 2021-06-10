#ifndef __FLYWAVE_MESH_TOPO_COMPOUND_HH__
#define __FLYWAVE_MESH_TOPO_COMPOUND_HH__

#include <BRep_Builder.hxx>
#include <TopoDS_Compound.hxx>

#include "solid.hh"

namespace flywave {
namespace topo {

class compound_iterator;

class compound : public solid {
public:
  compound() = default;
  virtual ~compound() = default;

  static compound make_compound(std::vector<shape> &shapes);

  static compound make_compound(std::initializer_list<shape> &shapes);

  template <typename TShp1, typename TShp2, typename... TShp>
  static compound make_compound(TShp1 &&shp1, TShp2 &&shp2, TShp &&... shps);

  TopoDS_Compound &value();
  const TopoDS_Compound &value() const;

  virtual geometry_object_type type() const override {
    return geometry_object_type::CompoundType;
  }

  virtual shape copy(bool deep = true) const override;

  compound(TopoDS_Shape shp) : solid(shp) {}

protected:
  friend class compound_iterator;
  friend class shape;
};

namespace _helper {
inline void make_compound_helper(BRep_Builder &aBuilder,
                                 TopoDS_Compound &aRes) {}

template <typename TShp1, typename... TShp>
void make_compound_helper(BRep_Builder &aBuilder, TopoDS_Compound &aRes,
                          TShp1 &&shp1, TShp &&... shps) {
  aBuilder.Add(aRes, shp1);
  make_compound_helper(aBuilder, aRes, std::forward<TShp>(shps)...);
}
} // namespace _helper

template <typename TShp1, typename TShp2, typename... TShp>
compound compound::make_compound(TShp1 &&shp1, TShp2 &&shp2, TShp &&... shps) {
  TopoDS_Compound aRes;
  BRep_Builder aBuilder;
  aBuilder.MakeCompound(aRes);
  _helper::make_compound_helper(aBuilder, aRes, shp1, shp2,
                                std::forward<TShp>(shps)...);
  return compound{aRes};
}

class compound_iterator {
public:
  TopExp_Explorer ex;
  compound_iterator(shape &arg) : ex(arg.value(), TopAbs_COMPOUND) {}
  void reset() { ex.ReInit(); }
  boost::optional<compound> next() {
    if (ex.More()) {
      compound ret{ex.Current()};
      ex.Next();
      return {ret};
    } else {
      return boost::none;
    }
  }
};
} // namespace topo
} // namespace flywave

#endif // __FLYWAVE_MESH_TOPO_COMPOUND_HH__
