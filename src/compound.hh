#ifndef __FLYWAVE_MESH_TOPO_COMPOUND_HH__
#define __FLYWAVE_MESH_TOPO_COMPOUND_HH__

#include <BRepAlgoAPI_BooleanOperation.hxx>
#include <BRep_Builder.hxx>
#include <TopoDS_Compound.hxx>

#include "font_type.hh"
#include "plane.hh"
#include "shape3d.hh"

namespace flywave {
namespace topo {

class compound_iterator;
class wire;

class compound : public shape3d {
public:
  compound() = default;
  virtual ~compound() = default;

  static compound make_compound(const std::vector<shape> &shapes);

  static compound make_compound(std::initializer_list<shape> &shapes);

  static compound
  make_text(const std::string &text, double size,
            const std::string &font = "Arial", const std::string &fontPath = "",
            font_kind kind = font_kind::REGULAR,
            horizontal_align halign = horizontal_align::CENTER,
            vertical_align valign = vertical_align::CENTER,
            const topo_plane &position = topo_plane::named("XY"));

  static compound make_text(const std::string &text, double size,
                            const wire &spine, bool planar = false,
                            const std::string &font = "Arial",
                            const std::string &path = "",
                            font_kind kind = font_kind::REGULAR,
                            horizontal_align halign = horizontal_align::CENTER,
                            vertical_align valign = vertical_align::CENTER);

  static compound make_text(const std::string &text, double size,
                            const wire &spine, const face &base,
                            const std::string &font = "Arial",
                            const std::string &path = "",
                            font_kind kind = font_kind::REGULAR,
                            horizontal_align halign = horizontal_align::CENTER,
                            vertical_align valign = vertical_align::CENTER);

  static compound
  make_text(const std::string &text, double size, double height,
            const std::string &font = "Arial", const std::string &fontPath = "",
            font_kind kind = font_kind::REGULAR,
            horizontal_align halign = horizontal_align::CENTER,
            vertical_align valign = vertical_align::CENTER,
            const topo_plane &position = topo_plane::named("XY"));

  template <typename TShp1, typename TShp2, typename... TShp>
  static compound make_compound(TShp1 &&shp1, TShp2 &&shp2, TShp &&...shps);

  TopoDS_Compound &value();
  const TopoDS_Compound &value() const;

  virtual geometry_object_type type() const override {
    return geometry_object_type::CompoundType;
  }

  virtual shape copy(bool deep = true) const override;

  void remove(const shape &shapeToRemove);

  compound(TopoDS_Shape shp, bool forConstruction = false)
      : shape3d(shp, forConstruction) {}
      
  compound(const shape &c, TopoDS_Shape shp) : shape3d(c, shp) {}

  compound cut(const std::vector<shape> &toCut, double tol = 0.0) const;

  compound fuse(const std::vector<shape> &toFuse, bool glue = false,
                double tol = 0.0) const;

  compound intersect(const std::vector<shape> &toIntersect,
                     double tol = 0.0) const;

  compound ancestors(const shape &s, TopAbs_ShapeEnum kind) const;

  compound siblings(const shape &shape, TopAbs_ShapeEnum kind,
                    int level = 1) const;

protected:
  compound bool_op(const std::vector<shape> &objects,
                   const std::vector<shape> &tools,
                   BRepAlgoAPI_BooleanOperation &op) const;

  friend class compound_iterator;
  friend class shape;
};

namespace _helper {
inline void make_compound_helper(BRep_Builder &aBuilder,
                                 TopoDS_Compound &aRes) {}

template <typename TShp1, typename... TShp>
void make_compound_helper(BRep_Builder &aBuilder, TopoDS_Compound &aRes,
                          TShp1 &&shp1, TShp &&...shps) {
  aBuilder.Add(aRes, shp1);
  make_compound_helper(aBuilder, aRes, std::forward<TShp>(shps)...);
}
} // namespace _helper

template <typename TShp1, typename TShp2, typename... TShp>
compound compound::make_compound(TShp1 &&shp1, TShp2 &&shp2, TShp &&...shps) {
  TopoDS_Compound aRes;
  BRep_Builder aBuilder;
  aBuilder.MakeCompound(aRes);
  _helper::make_compound_helper(aBuilder, aRes, shp1, shp2,
                                std::forward<TShp>(shps)...);
  return {aRes};
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
