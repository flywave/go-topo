#include "compound.hh"

#include <BRepAlgoAPI_Common.hxx>
#include <BRepAlgoAPI_Cut.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepBuilderAPI_Copy.hxx>
#include <TopExp.hxx>
#include <TopTools_IndexedDataMapOfShapeListOfShape.hxx>
#include <TopTools_MapOfShape.hxx>
#include <TopoDS.hxx>
#include <boost/variant.hpp>
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

void compound::remove(const shape &shapeToRemove) {
  if (shapeToRemove.is_null()) {
    throw std::invalid_argument("Shape to remove cannot be null");
  }

  TopoDS_Compound result;
  TopoDS_Builder builder;
  builder.MakeCompound(result);

  // 复制除了要移除的形状外的所有子形状
  bool found = false;
  for (TopoDS_Iterator it(_shape); it.More(); it.Next()) {
    const TopoDS_Shape &current = it.Value();
    if (!current.IsSame(shapeToRemove)) {
      builder.Add(result, current);
    } else {
      found = true;
    }
  }

  if (!found) {
    throw std::invalid_argument("Shape to remove not found in the compound");
  }

  _shape = result;
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

compound compound::bool_op(const std::vector<shape> &objects,
                           const std::vector<shape> &tools,
                           BRepAlgoAPI_BooleanOperation &op) const {
  if (objects.empty()) {
    throw std::invalid_argument("No objects provided for boolean operation");
  }

  TopTools_ListOfShape args;
  for (const auto &obj : objects) {
    args.Append(obj.value());
  }
  op.SetArguments(args);

  TopTools_ListOfShape _tools;

  for (const auto &tool : tools) {
    _tools.Append(tool.value());
  }

  op.SetTools(_tools);

  op.Build();
  if (!op.IsDone()) {
    throw std::runtime_error("Boolean operation failed");
  }

  return compound(op.Shape());
}

compound compound::cut(const std::vector<shape> &toCut, double tol) const {
  BRepAlgoAPI_Cut cutOp;

  if (tol > 0) {
    cutOp.SetFuzzyValue(tol);
  }

  return bool_op({shape(*this)}, toCut, cutOp);
}

// Boolean fuse operation
compound compound::fuse(const std::vector<shape> &toFuse, bool glue,
                        double tol) const {
  BRepAlgoAPI_Fuse fuseOp;

  if (glue) {
    fuseOp.SetGlue(BOPAlgo_GlueShift);
  }
  if (tol > 0) {
    fuseOp.SetFuzzyValue(tol);
  }

  std::vector<shape> args = {*this};
  args.insert(args.end(), toFuse.begin(), toFuse.end());

  if (args.size() <= 1) {
    return compound(args[0].value());
  }

  return bool_op({shape(args[0])},
                 std::vector<shape>(args.begin() + 1, args.end()), fuseOp);
}

compound compound::intersect(const std::vector<shape> &toIntersect,
                             double tol) const {
  BRepAlgoAPI_Common intersectOp;

  if (tol > 0) {
    intersectOp.SetFuzzyValue(tol);
  }

  return bool_op({shape(*this)}, toIntersect, intersectOp);
}

// Find ancestor shapes
compound compound::ancestors(const shape &s, TopAbs_ShapeEnum kind) const {
  TopTools_IndexedDataMapOfShapeListOfShape shapeMap;

  // Get unique shape types in this shape
  std::set<TopAbs_ShapeEnum> shapeTypes;
  for (const auto &child : this->children()) {
    shapeTypes.insert(child.value().ShapeType());
  }

  // Map shapes and ancestors
  for (TopAbs_ShapeEnum t : shapeTypes) {
    TopExp::MapShapesAndAncestors(s.value(), t, kind, shapeMap);
  }

  // Collect results
  std::vector<shape> results;
  for (const auto &s : this->children()) {
    const TopTools_ListOfShape &ancestors = shapeMap.FindFromKey(s.value());
    TopTools_ListIteratorOfListOfShape it(ancestors);
    for (; it.More(); it.Next()) {
      results.push_back(it.Value());
    }
  }

  return compound::make_compound(results);
}

void _collectSiblings(const shape &shp,
                      const TopTools_IndexedDataMapOfShapeListOfShape &shapeMap,
                      TopTools_MapOfShape &exclude, TopAbs_ShapeEnum kind,
                      int level, std::vector<shape> &results) {
  for (const auto &s : shp.children()) {
    exclude.Add(s.value());
  }

  // Collect
  for (const auto &s : shp.children()) {
    for (const auto &child : s.get_shapes(kind)) {
      const TopTools_ListOfShape &siblings =
          shapeMap.FindFromKey(child.value());
      TopTools_ListIteratorOfListOfShape it(siblings);
      for (; it.More(); it.Next()) {
        if (!exclude.Contains(it.Value())) {
          results.push_back(it.Value());
        }
      }
    }
  }

  // Recurse if needed
  if (level > 1) {
    shape nextLevel = compound::make_compound(results);
    _collectSiblings(nextLevel, shapeMap, exclude, kind, level - 1, results);
  }
}

// Find sibling shapes
compound compound::siblings(const shape &s, TopAbs_ShapeEnum kind,
                            int level) const {
  TopTools_IndexedDataMapOfShapeListOfShape shapeMap;
  TopTools_MapOfShape exclude;

  // Get unique shape types in this shape
  std::set<TopAbs_ShapeEnum> shapeTypes;
  for (const auto &child : this->children()) {
    shapeTypes.insert(child.value().ShapeType());
  }

  // Map shapes and ancestors
  for (TopAbs_ShapeEnum t : shapeTypes) {
    TopExp::MapShapesAndAncestors(s.value(), kind, t, shapeMap);
  }

  // Recursive sibling collection
  std::vector<shape> results;
  _collectSiblings(*this, shapeMap, exclude, kind, level, results);

  return compound::make_compound(results);
}

} // namespace topo
} // namespace flywave
