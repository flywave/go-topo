
#pragma once

#include "brep_mesh_parameters.hh"
#include "ogg_handle.hh"

#include <Poly_Polygon3D.hxx>
#include <Poly_Triangulation.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Face.hxx>
#include <string>

namespace flywave {

struct brep_utils {
  static TopoDS_Compound make_empty_compound();

  static void add_shape(TopoDS_Shape *ptrTargetShape,
                        const TopoDS_Shape &shape);

  static TopoDS_Edge make_edge(const ogg_handle<Poly_Polygon3D> &polygon);

  static TopoDS_Face make_face(const ogg_handle<Poly_Triangulation> &mesh);

  template <typename Function>
  static void for_each_sub_shape(TopExp_Explorer &explorer, Function fn);

  template <typename Function>
  static void for_each_sub_shape(const TopoDS_Shape &shape,
                                 TopAbs_ShapeEnum shapeType, Function fn);

  template <typename Function>
  static void for_each_sub_face(const TopoDS_Shape &shape, Function fn);

  static bool more_complex(TopAbs_ShapeEnum lhs, TopAbs_ShapeEnum rhs);

  static size_t hash_code(const TopoDS_Shape &shape);

  static std::string shape_to_string(const TopoDS_Shape &shape);

  static TopoDS_Shape shape_from_string(const std::string &str);

  static bool is_geometric(const TopoDS_Edge &edge);

  static bool is_geometric(const TopoDS_Face &face);

  static void compute_mesh(const TopoDS_Shape &shape,
                           const brep_mesh_parameters &params);
};

template <typename Function>
void brep_utils::for_each_sub_shape(TopExp_Explorer &explorer, Function fn) {
  while (explorer.More()) {
    fn(explorer.Current());
    explorer.Next();
  }
}

template <typename Function>
void brep_utils::for_each_sub_shape(const TopoDS_Shape &shape,
                                    TopAbs_ShapeEnum shapeType, Function fn) {
  TopExp_Explorer expl(shape, shapeType);
  brep_utils::for_each_sub_shape(expl, std::move(fn));
}

template <typename Function>
void brep_utils::for_each_sub_face(const TopoDS_Shape &shape, Function fn) {
  for (TopExp_Explorer expl(shape, TopAbs_FACE); expl.More(); expl.Next())
    fn(TopoDS::Face(expl.Current()));
}

} // namespace flywave