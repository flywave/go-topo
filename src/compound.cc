#include "compound.hh"
#include "face.hh"
#include "shape_ops.hh"
#include "wire.hh"

#include <BRepAdaptor_Curve.hxx>
#include <BRepAdaptor_Surface.hxx>
#include <BRepAlgoAPI_Common.hxx>
#include <BRepAlgoAPI_Cut.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepBndLib.hxx>
#include <BRepBuilderAPI_Copy.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_Transform.hxx>
#include <BRepGProp.hxx>
#include <BRepPrimAPI_MakePrism.hxx>
#include <BRepProj_Projection.hxx>
#include <BRep_Tool.hxx>
#include <Font_BRepTextBuilder.hxx>
#include <Font_FontMgr.hxx>
#include <Font_SystemFont.hxx>
#include <GCPnts_AbscissaPoint.hxx>
#include <GProp_GProps.hxx>
#include <Graphic3d_HorizontalTextAlignment.hxx>
#include <Graphic3d_VerticalTextAlignment.hxx>
#include <StdPrs_BRepFont.hxx>
#include <TCollection_AsciiString.hxx>
#include <TopExp.hxx>
#include <TopExp_Explorer.hxx>
#include <TopTools_IndexedDataMapOfShapeListOfShape.hxx>
#include <TopTools_MapOfShape.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Shape.hxx>
#include <boost/variant.hpp>
#include <gp_Ax1.hxx>
#include <gp_Trsf.hxx>
#include <vector>

namespace flywave {
namespace topo {
namespace {

static Font_FontAspect ConvertFontKind(font_kind kind) {
  switch (kind) {
  case font_kind::BOLD:
    return Font_FA_Bold;
  case font_kind::ITALIC:
    return Font_FA_Italic;
  default:
    return Font_FA_Regular;
  }
}

static Graphic3d_HorizontalTextAlignment ConvertHAlign(horizontal_align align) {
  switch (align) {
  case horizontal_align::LEFT:
    return Graphic3d_HTA_LEFT;
  case horizontal_align::RIGHT:
    return Graphic3d_HTA_RIGHT;
  default:
    return Graphic3d_HTA_CENTER;
  }
}

static Graphic3d_VerticalTextAlignment ConvertVAlign(vertical_align align) {
  switch (align) {
  case vertical_align::TOP:
    return Graphic3d_VTA_TOP;
  case vertical_align::BOTTOM:
    return Graphic3d_VTA_BOTTOM;
  default:
    return Graphic3d_VTA_CENTER;
  }
}

static Handle(Font_SystemFont)
    LoadFont(const Handle(Font_FontMgr) & mgr, const std::string &fontName,
             const std::string &path, Font_FontAspect aspect) {
  if (!path.empty() && mgr->CheckFont(path.c_str())) {
    Handle(Font_SystemFont) font =
        new Font_SystemFont(TCollection_AsciiString(path.c_str()));
    font->SetFontPath(aspect, TCollection_AsciiString(path.c_str()));
    mgr->RegisterFont(font, true);
    return font;
  }
  return mgr->FindFont(TCollection_AsciiString(fontName.c_str()), aspect);
}

static TopoDS_Shape CleanAndFuse(const TopoDS_Shape &shp) {
  BRepAlgoAPI_Fuse fuser;
  TopTools_ListOfShape shapesToFuse;

  for (TopExp_Explorer exp(shp, TopAbs_FACE); exp.More(); exp.Next()) {
    shapesToFuse.Append(exp.Current());
  }

  fuser.SetArguments(shapesToFuse);
  fuser.Build();

  if (fuser.IsDone()) {
    return fuser.Shape();
  }
  return shp;
}

TopoDS_Shape normalize_shape(const TopoDS_Shape &shape) {
  if (shape.IsNull()) {
    return shape;
  }

  const TopAbs_ShapeEnum shapeType = shape.ShapeType();
  TopoDS_Shape result = shape;

  if (shapeType == TopAbs_COMPOUND) {
    // Check if compound has only one element
    TopExp_Explorer compExp(shape, TopAbs_SHAPE);
    if (compExp.More()) {
      compExp.Next();
      if (!compExp.More()) { // Only one element
        result = TopExp_Explorer(shape, TopAbs_SHAPE).Current();
      }
    }
  }

  return result;
}
} // namespace

compound compound::make_compound(const std::vector<shape> &shapes) {
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

compound compound::ancestors(const shape &s, TopAbs_ShapeEnum kind) const {
  TopTools_IndexedDataMapOfShapeListOfShape shapeMap;

  std::set<TopAbs_ShapeEnum> shapeTypes;
  for (const auto &child : this->children()) {
    shapeTypes.insert(child.value().ShapeType());
  }

  for (TopAbs_ShapeEnum t : shapeTypes) {
    TopExp::MapShapesAndAncestors(s.value(), t, kind, shapeMap);
  }

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

  if (level > 1) {
    shape nextLevel = compound::make_compound(results);
    _collectSiblings(nextLevel, shapeMap, exclude, kind, level - 1, results);
  }
}

compound compound::siblings(const shape &s, TopAbs_ShapeEnum kind,
                            int level) const {
  TopTools_IndexedDataMapOfShapeListOfShape shapeMap;
  TopTools_MapOfShape exclude;

  std::set<TopAbs_ShapeEnum> shapeTypes;
  for (const auto &child : this->children()) {
    shapeTypes.insert(child.value().ShapeType());
  }

  for (TopAbs_ShapeEnum t : shapeTypes) {
    TopExp::MapShapesAndAncestors(s.value(), kind, t, shapeMap);
  }

  std::vector<shape> results;
  _collectSiblings(*this, shapeMap, exclude, kind, level, results);

  return compound::make_compound(results);
}

compound compound::make_text(const std::string &text, double size,
                             const std::string &font,
                             const std::string &fontPath, font_kind kind,
                             horizontal_align halign, vertical_align valign,
                             const topo_plane &position) {
  Font_FontAspect fontAspect = ConvertFontKind(kind);

  Handle(Font_FontMgr) fontMgr = Font_FontMgr::GetInstance();
  Handle(Font_SystemFont) systemFont =
      LoadFont(fontMgr, font, fontPath, fontAspect);

  Graphic3d_HorizontalTextAlignment hAlignment = ConvertHAlign(halign);
  Graphic3d_VerticalTextAlignment vAlignment = ConvertVAlign(valign);

  StdPrs_BRepFont brepFont(
      NCollection_Utf8String(systemFont->FontName().ToCString()), fontAspect,
      size);

  Font_BRepTextBuilder builder;
  TopoDS_Shape textShape =
      builder.Perform(brepFont, NCollection_Utf8String(text.c_str()), gp_Ax3(),
                      hAlignment, vAlignment);

  auto shp = CleanAndFuse(textShape);
  return *position.to_world_coords(shp).cast<compound>();
}

compound compound::make_text(const std::string &text, double size,
                             const wire &spine, bool planar,
                             const std::string &font, const std::string &path,
                             font_kind kind, horizontal_align halign,
                             vertical_align valign) {
  TopoDS_Wire wire = spine.value();
  double length = spine.length();

  compound flatText =
      compound::make_text(text, size, font, path, kind, halign, valign);

  BRep_Builder builder;
  TopoDS_Compound result;
  builder.MakeCompound(result);

  for (TopExp_Explorer exp(flatText, TopAbs_FACE); exp.More(); exp.Next()) {
    TopoDS_Face face = TopoDS::Face(exp.Current());

    Bnd_Box bbox;
    BRepBndLib::Add(face, bbox);
    double xPos = (bbox.CornerMin().X() + bbox.CornerMax().X()) / 2.0;

    gp_Trsf moveToOrigin;
    moveToOrigin.SetTranslation(gp_Vec(-xPos, 0, 0));

    gp_Trsf rotate;
    if (planar) {
      rotate.SetRotation(gp_Ax1(gp_Pnt(), gp_Dir(1, 0, 0)), -M_PI_2);
    }
    gp_Trsf rotateY;
    rotateY.SetRotation(gp_Ax1(gp_Pnt(), gp_Dir(0, 1, 0)), -M_PI_2);

    gp_Pnt spinePoint = spine.position_at(xPos / length);
    gp_Trsf moveToSpine;
    moveToSpine.SetTranslation(gp_Vec(spinePoint.XYZ()));

    gp_Trsf finalTransform = moveToOrigin * rotate * rotateY * moveToSpine;

    TopoDS_Shape movedFace = face.Moved(finalTransform);
    builder.Add(result, movedFace);
  }

  return normalize_shape(result);
}

compound compound::make_text(const std::string &text, double size,
                             const wire &spine, const face &base,
                             const std::string &font, const std::string &path,
                             font_kind kind, horizontal_align halign,
                             vertical_align valign) {
  TopoDS_Face baseFace = base.value();

  compound spineText = compound::make_text(text, size, spine, false, font, path,
                                           kind, halign, valign);

  BRep_Builder builder;
  TopoDS_Compound result;
  builder.MakeCompound(result);

  for (TopExp_Explorer exp(spineText, TopAbs_FACE); exp.More(); exp.Next()) {
    TopoDS_Face face = TopoDS::Face(exp.Current());
    gp_Dir normal = base.normal_at();

    BRepProj_Projection projection(face, baseFace, normal);
    if (projection.IsDone()) {
      builder.Add(result, projection.Shape());
    }
  }

  return normalize_shape(result);
}

compound compound::make_text(const std::string &text, double size,
                             double height, const std::string &font,
                             const std::string &fontPath, font_kind kind,
                             horizontal_align halign, vertical_align valign,
                             const topo_plane &position) {
  Font_FontAspect fontAspect;
  switch (kind) {
  case font_kind::BOLD:
    fontAspect = Font_FontAspect_Bold;
    break;
  case font_kind::ITALIC:
    fontAspect = Font_FontAspect_Italic;
    break;
  default:
    fontAspect = Font_FontAspect_Regular;
    break;
  }

  Handle(Font_FontMgr) fontMgr = Font_FontMgr::GetInstance();

  Handle(Font_SystemFont) systemFont;
  if (!fontPath.empty() && fontMgr->CheckFont(fontPath.c_str())) {
    systemFont = new Font_SystemFont(TCollection_AsciiString(fontPath.c_str()));
    systemFont->SetFontPath(fontAspect,
                            TCollection_AsciiString(fontPath.c_str()));
    fontMgr->RegisterFont(systemFont, true);
  } else {
    systemFont =
        fontMgr->FindFont(TCollection_AsciiString(font.c_str()), fontAspect);
    if (systemFont.IsNull()) {
      throw std::runtime_error("Font not found: " + font);
    }
  }

  Graphic3d_HorizontalTextAlignment hAlignment;
  switch (halign) {
  case horizontal_align::LEFT:
    hAlignment = Graphic3d_HTA_LEFT;
    break;
  case horizontal_align::RIGHT:
    hAlignment = Graphic3d_HTA_RIGHT;
    break;
  default:
    hAlignment = Graphic3d_HTA_CENTER;
    break;
  }

  Graphic3d_VerticalTextAlignment vAlignment;
  switch (valign) {
  case vertical_align::TOP:
    vAlignment = Graphic3d_VTA_TOP;
    break;
  case vertical_align::BOTTOM:
    vAlignment = Graphic3d_VTA_BOTTOM;
    break;
  default:
    vAlignment = Graphic3d_VTA_CENTER;
    break;
  }

  StdPrs_BRepFont brepFont(
      NCollection_Utf8String(systemFont->FontName().ToCString()), fontAspect,
      size);

  Font_BRepTextBuilder textBuilder;
  TopoDS_Shape textShape =
      textBuilder.Perform(brepFont, NCollection_Utf8String(text.c_str()),
                          gp_Ax3(), hAlignment, vAlignment);

  if (std::abs(height) > Precision::Confusion()) {
    TopExp_Explorer faceExplorer(textShape, TopAbs_FACE);
    if (!faceExplorer.More()) {
      throw std::runtime_error("Text shape has no faces");
    }

    TopoDS_Face firstFace = TopoDS::Face(faceExplorer.Current());
    BRepAdaptor_Surface surface(firstFace);
    gp_Dir normal = surface.Plane().Axis().Direction();

    BRepPrimAPI_MakePrism prismMaker(textShape, gp_Vec(normal) * height,
                                     false // Don't copy the shape
    );

    textShape = prismMaker.Shape();
  }

  auto shp = normalize_shape(textShape);
  return *position.to_world_coords(shp).cast<compound>();
}
} // namespace topo
} // namespace flywave
