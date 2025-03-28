#include "mesh.hh"
#include "point3d_with_tolerance.hh"

#include <BRepBndLib.hxx>
#include <BRepBuilderAPI_MakeSolid.hxx>
#include <BRepCheck_Analyzer.hxx>
#include <BRepGProp.hxx>
#include <BRepLib.hxx>
#include <BRepMesh_IncrementalMesh.hxx>
#include <BRepOffsetAPI_Sewing.hxx>
#include <BRepTools.hxx>
#include <BRep_Builder.hxx>
#include <BRep_Tool.hxx>
#include <Bnd_Box.hxx>
#include <GProp_GProps.hxx>
#include <Geom_Curve.hxx>
#include <Geom_Surface.hxx>
#include <Poly.hxx>
#include <Poly_Triangulation.hxx>
#include <Quantity_Color.hxx>
#include <ShapeAnalysis.hxx>
#include <ShapeAnalysis_Curve.hxx>
#include <ShapeBuild_ReShape.hxx>
#include <ShapeFix_FixSmallFace.hxx>
#include <ShapeFix_Shape.hxx>
#include <ShapeFix_Wire.hxx>
#include <ShapeFix_Wireframe.hxx>
#include <Standard_ConstructionError.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <TColgp_SequenceOfPnt.hxx>
#include <TDF_ChildIterator.hxx>
#include <TDF_LabelSequence.hxx>
#include <TDF_Tool.hxx>
#include <TDataStd_Name.hxx>
#include <TDocStd_Document.hxx>
#include <TShort_Array1OfShortReal.hxx>
#include <TopExp.hxx>
#include <TopExp_Explorer.hxx>
#include <TopTools_HSequenceOfShape.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Shell.hxx>
#include <TopoDS_Solid.hxx>
#include <TopoDS_Vertex.hxx>
#include <TopoDS_Wire.hxx>
#include <XCAFDoc_ColorTool.hxx>
#include <XCAFDoc_DocumentTool.hxx>
#include <XCAFDoc_LayerTool.hxx>
#include <XCAFDoc_ShapeTool.hxx>
#include <XCAFPrs.hxx>
#include <XCAFPrs_DataMapIteratorOfDataMapOfStyleShape.hxx>
#include <XCAFPrs_DataMapOfStyleShape.hxx>
#include <XCAFPrs_IndexedDataMapOfShapeStyle.hxx>
#include <XCAFPrs_Style.hxx>
#include <gp_Pnt.hxx>
#include <gp_Quaternion.hxx>

#include <TDF_Label.hxx>
#include <TDocStd_Document.hxx>
#include <XCAFApp_Application.hxx>
#include <XCAFDoc.hxx>
#include <XCAFDoc_ColorTool.hxx>
#include <XCAFDoc_DocumentTool.hxx>
#include <XCAFDoc_ShapeTool.hxx>

#include <unordered_map>

namespace flywave {
namespace topo {

mesh::mesh() {
  _app = XCAFApp_Application::GetApplication();
  _doc.Nullify();
}

mesh::mesh(const shape &shp) {
  _app = XCAFApp_Application::GetApplication();
  _doc.Nullify();
  map_shape(shp);
}

mesh::mesh(TopoDS_Shape shp) {
  _app = XCAFApp_Application::GetApplication();
  _doc.Nullify();
  map_shape(shp);
}

mesh::mesh(Handle_TDocStd_Document doc) : _doc(doc) {
  _app = XCAFApp_Application::GetApplication();

  _shape_tool = XCAFDoc_DocumentTool::ShapeTool(_doc->Main());
  _color_tool = XCAFDoc_DocumentTool::ColorTool(_doc->Main());
  _layer_tool = XCAFDoc_DocumentTool::LayerTool(_doc->Main());
  map_shapes(_doc);
}

void mesh::triangulation(mesh_receiver &meshReceiver, double deflection,
                         double tolerance) {
  int faceCount = _fmap.Extent();
  if (faceCount == 0)
    return;

  if (deflection <= 0)
    deflection = 0.01;

  std::vector<bool> hasSeams;
  hasSeams.resize(faceCount);
  for (int f = 0; f < _fmap.Extent(); f++) {
    TopTools_IndexedMapOfShape edgeMap;
    TopExp::MapShapes(_fmap(f + 1), TopAbs_EDGE, edgeMap);
    hasSeams[f] = false;
    for (Standard_Integer i = 1; i <= _emap.Extent(); i++) {
      hasSeams[f] = (BRep_Tool::IsClosed(_emap(i)) == Standard_True);
      if (hasSeams[f])
        break;
    }
  }

  Quantity_Color color(1., 1., 1., Quantity_TOC_RGB);
  for (int f = 1; f <= _fmap.Extent(); f++) {
    const TopoDS_Face &face = TopoDS::Face(_fmap(f));
    TopLoc_Location aLoc;
    bool alreadymeshed = true;
    Quantity_Color localColor;
    if (query_color(face, localColor)) {
      color = localColor;
    }

    Handle(Poly_Triangulation) aPoly = BRep_Tool::Triangulation(face, aLoc);
    if (aPoly.IsNull()) {
      alreadymeshed = false;
    }

    if (!alreadymeshed) {
      Bnd_Box B;
      BRepBndLib::Add(face, B);
      if (B.IsVoid())
        return;
      Standard_Real aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
      B.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);

      float aDeflection =
          std::max(aXmax - aXmin, std::max(aYmax - aYmin, aZmax - aZmin)) *
          deflection * 4;

      BRepTools::Clean(face);
      BRepMesh_IncrementalMesh MESH(face, aDeflection);
    }

    int faceId = meshReceiver.append_face(color);
    bool faceReversed = (face.Orientation() == TopAbs_REVERSED);

    TopLoc_Location loc;
    const Handle(Poly_Triangulation) &mesh =
        BRep_Tool::Triangulation(face, loc);
    if (mesh.IsNull())
      continue;
    bool hasSeam = hasSeams[f - 1];
    gp_Trsf transform = loc.Transformation();
    gp_Quaternion quaternion = transform.GetRotation();
    Handle(TColgp_HArray1OfPnt) nodes = mesh->MapNodeArray();
    Poly::ComputeNormals(mesh);

    if (hasSeam) {
      TColStd_Array1OfReal norms(1, mesh->MapNormalArray()->Length());
      for (Standard_Integer i = 1; i <= mesh->NbNodes() * 3; i += 3) {
        gp_Dir dir(mesh->MapNormalArray()->Value(i),
                   mesh->MapNormalArray()->Value(i + 1),
                   mesh->MapNormalArray()->Value(i + 2));
        if (faceReversed)
          dir.Reverse();
        dir = quaternion.Multiply(dir);
        norms.SetValue(i, dir.X());
        norms.SetValue(i + 1, dir.Y());
        norms.SetValue(i + 2, dir.Z());
      }
      std::unordered_map<point3d_with_tolerance, int> uniquePointsOnFace;
      for (Standard_Integer j = 1; j <= mesh->NbNodes(); j++) {
        gp_Pnt p = nodes->Value(j);
        point3d_with_tolerance pt(p.X(), p.Y(), p.Z(), tolerance);
        int nodeIndex;
        if (uniquePointsOnFace.find(pt) != uniquePointsOnFace.end()) {
          nodeIndex = uniquePointsOnFace[pt];
          gp_Vec normalA(norms.Value(nodeIndex), norms.Value(nodeIndex) + 1,
                         norms.Value(nodeIndex) + 2);
          gp_Vec normalB(norms.Value(j), norms.Value(j) + 1,
                         norms.Value(j) + 2);
          gp_Vec normalBalanced = normalA + normalB;
          normalBalanced.Normalize();
          norms.SetValue(nodeIndex, normalBalanced.X());
          norms.SetValue(nodeIndex + 1, normalBalanced.Y());
          norms.SetValue(nodeIndex + 2, normalBalanced.Z());
          norms.SetValue(j, normalBalanced.X());
          norms.SetValue(j + 1, normalBalanced.Y());
          norms.SetValue(j + 2, normalBalanced.Z());
        } else
          uniquePointsOnFace.emplace(pt, j);
      }

      for (Standard_Integer j = 0; j < mesh->NbNodes(); j++) {
        gp_Pnt p = nodes->Value(j + 1);
        Standard_Real px = p.X();
        Standard_Real py = p.Y();
        Standard_Real pz = p.Z();
        transform.Transforms(px, py, pz);
        gp_Dir dir(norms.Value((j * 3) + 1), norms.Value((j * 3) + 2),
                   norms.Value((j * 3) + 3));
        meshReceiver.append_node(faceId, gp_Pnt{px, py, pz},
                                 gp_Pnt{dir.X(), dir.Y(), dir.Z()});
      }
    } else {
      for (Standard_Integer j = 0; j < mesh->NbNodes(); j++) {
        gp_Pnt p = nodes->Value(j + 1);
        Standard_Real px = p.X();
        Standard_Real py = p.Y();
        Standard_Real pz = p.Z();
        transform.Transforms(px, py, pz);
        gp_Dir dir(mesh->MapNormalArray()->Value((j * 3) + 1),
                   mesh->MapNormalArray()->Value((j * 3) + 2),
                   mesh->MapNormalArray()->Value((j * 3) + 3));
        if (faceReversed)
          dir.Reverse();
        dir = quaternion.Multiply(dir);
        meshReceiver.append_node(faceId, gp_Pnt{px, py, pz},
                                 gp_Pnt{dir.X(), dir.Y(), dir.Z()});
      }
    }

    Standard_Integer t[3];
    Handle(Poly_HArray1OfTriangle) triangles = mesh->MapTriangleArray();

    for (Standard_Integer j = 1; j <= mesh->NbTriangles(); j++) {
      if (faceReversed)
        triangles->Value(j).Get(t[2], t[1], t[0]);
      else
        triangles->Value(j).Get(t[0], t[1], t[2]);
      int tri[3];
      tri[0] = t[0] - 1;
      tri[1] = t[1] - 1;
      tri[2] = t[2] - 1;
      meshReceiver.append_triangle(faceId, tri);
    }
  }
}

void print_tdf_label(const TDF_Label &label) {
  Handle_XCAFDoc_ColorTool colourTool = XCAFDoc_DocumentTool::ColorTool(label);
  Handle_TDataStd_Name N;
  if (label.FindAttribute(TDataStd_Name::GetID(), N)) {
    char *string =
        (char *)malloc((N->Get().LengthOfCString() + 1) * sizeof(char));
    N->Get().ToUTF8CString(string);
    free(string);
  }
  TCollection_AsciiString entry;
  TDF_Tool::Entry(label, entry);
  std::cout << ", " << entry;
  TDF_Label colourLabel;
  if (colourTool->GetColor(label, XCAFDoc_ColorGen, colourLabel) ||
      colourTool->GetColor(label, XCAFDoc_ColorSurf, colourLabel) ||
      colourTool->GetColor(label, XCAFDoc_ColorCurv, colourLabel)) {
    Quantity_Color colour;
    if (colourTool->GetColor(colourLabel, colour)) {
      std::cout << ", " << Quantity_Color::StringName(colour.Name());
    }
  }
  std::cout << std::endl;
}

bool mesh::extract_colour(const TDF_Label &label,
                          const Handle_XCAFDoc_ColorTool &colourTool,
                          Quantity_Color &colour) {
  bool okCurve = false;
  bool okSurface = false;
  bool okGeneral = false;

  okCurve = colourTool->GetColor(label, XCAFDoc_ColorCurv, colour);
  if (!okCurve) {
    okSurface = colourTool->GetColor(label, XCAFDoc_ColorSurf, colour);
    if (!okSurface) {
      okGeneral = colourTool->GetColor(label, XCAFDoc_ColorGen, colour);
    }
  }

  return (okCurve || okSurface || okGeneral);
}

bool mesh::extract_colour(const TDF_Label &label, Quantity_Color &colour) {
  return false;
}

bool mesh::extract_colour(const TopoDS_Shape &shape,
                          const Handle_XCAFDoc_ColorTool &colourTool,
                          Quantity_Color &colour) {
  bool ok = false;
  ok |= colourTool->GetColor(shape, XCAFDoc_ColorCurv, colour);
  ok |= colourTool->GetColor(shape, XCAFDoc_ColorSurf, colour);
  ok |= colourTool->GetColor(shape, XCAFDoc_ColorGen, colour);
  return ok;
}

void mesh::traverse_shape(const TopoDS_Shape &shape) {
  TopoDS_Iterator it(shape);
  for (; it.More(); it.Next()) {
    const TopoDS_Shape &child = it.Value();
    if (child.ShapeType() < TopAbs_EDGE)
      traverse_shape(child);

    map_shape(child);
  }
}

bool mesh::has_children(const TDF_Label &label) {
  TDF_ChildIterator it(label);
  return (it.More() == (bool)1);
}

void mesh::add_label_contents(const TDF_Label &label) {
  Quantity_Color colour;

  TopoDS_Shape shape = XCAFDoc_ShapeTool::GetShape(label);
  if (extract_colour(label, _color_tool, colour)) {
    _shape_stack.push_back(shape);
    _colour_stack.push_back(colour);
  } else {
    if (XCAFDoc_ShapeTool::IsReference(label)) {
      TDF_Label ref;
      XCAFDoc_ShapeTool::GetReferredShape(label, ref);
      if (XCAFDoc_ShapeTool::IsAssembly(ref)) {
        size_t stackIndex = _shape_stack.size();
        create_shape_colour_stacks(ref);
        for (size_t i = stackIndex; i < _shape_stack.size(); i++) {
          _shape_stack[i].Move(XCAFDoc_ShapeTool::GetLocation(label));
        }
      } else {
        if (extract_colour(ref, _color_tool, colour)) {
          shape = XCAFDoc_ShapeTool::GetShape(ref);
          shape.Move(XCAFDoc_ShapeTool::GetLocation(label));
          _shape_stack.push_back(shape);
          _colour_stack.push_back(colour);
        } else {
          if (XCAFDoc_ShapeTool::IsAssembly(label)) {
            create_shape_colour_stacks(label);
          } else {
            if (has_children(ref)) {
              create_shape_colour_stacks(ref);
            } else {
              shape = XCAFDoc_ShapeTool::GetShape(ref);
              shape.Move(XCAFDoc_ShapeTool::GetLocation(label));
              _shape_stack.push_back(shape);
              _colour_stack.push_back(colour);
            }
          }
        }
      }
    }
  }
}

void mesh::create_shape_colour_stacks(const TDF_Label &label) {
  Quantity_Color colour;
  TopoDS_Shape S;
  TDF_Label refLabel;
  static int depth = 0;

  depth++;
  if (has_children(label)) {
    int count = 0;
    for (TDF_ChildIterator it(label); it.More(); it.Next()) {
      count++;
      add_label_contents(it.Value());
    }
  } else {
    add_label_contents(label);
  }
  depth--;
}

bool mesh::map_stacks() {
  if (_shape_stack.size() == 0)
    return false;

  if (_shape_stack.size() != _colour_stack.size())
    return false;

  while (!_shape_stack.empty()) {
    _current_colour = _colour_stack.back();
    map_shape(_shape_stack.back());
    _shape_stack.pop_back();
    _colour_stack.pop_back();
  }

  return true;
}

void mesh::traverse_label(const TDF_Label &label) {
  static int depth = 0;
  depth++;
  TDF_LabelSequence subShapes;
  if (_shape_tool->GetSubShapes(label, subShapes)) {
    for (Standard_Integer i = 1; i <= subShapes.Length(); i++) {
      TDF_Label subLabel = subShapes.Value(i);
      traverse_label(subLabel);
    }
  }
  if (_shape_tool->IsAssembly(label)) {
    TDF_LabelSequence components;
    _shape_tool->GetComponents(label, components);
    for (Standard_Integer i = 1; i <= components.Length(); i++) {
      TDF_Label componentLabel = components.Value(i);
      traverse_label(componentLabel);
    }
  }
  if (_shape_tool->IsReference(label)) {
    TDF_Label refLabel;
    _shape_tool->GetReferredShape(label, refLabel);
    traverse_label(refLabel);
  }
  depth--;
}

void mesh::basic_traversal() {
  TDF_LabelSequence root_labels;
  _shape_tool->GetFreeShapes(root_labels);

  for (Standard_Integer i = 1; i <= root_labels.Length(); i++) {
    TDF_Label label = root_labels.Value(i);
    traverse_label(label);
  }
}

void mesh::label_traversal(const TDF_Label &aLabel,
                           const TopLoc_Location &aLocation, shape *parent) {
  if (style_print(aLabel, aLocation, parent)) {
    //
  }
  TDF_LabelSequence seq;

  if (XCAFDoc_ShapeTool::GetSubShapes(aLabel, seq)) {
    Standard_Integer i = 1;
    for (i = 1; i <= seq.Length(); i++) {
      TDF_Label aL = seq.Value(i);
      label_traversal(aL, aLocation, parent);
    }
  }

  seq.Clear();
  if (XCAFDoc_ShapeTool::GetComponents(aLabel, seq)) {
    Standard_Integer i = 1;
    for (i = 1; i <= seq.Length(); i++) {
      TDF_Label aL = seq.Value(i);
      label_traversal(aL, aLocation, parent);
    }
  }
}

static bool merge_styles(XCAFPrs_Style &style, const XCAFPrs_Style &father) {
  if (!style.IsSetColorCurv() && father.IsSetColorCurv())
    style.SetColorCurv(father.GetColorCurv());
  if (!style.IsSetColorSurf() && father.IsSetColorSurf())
    style.SetColorSurf(father.GetColorSurf());
  return style == father;
}

static bool dispatch_styles(const TopoDS_Shape &shape,
                            const XCAFPrs_IndexedDataMapOfShapeStyle &settings,
                            XCAFPrs_DataMapOfStyleShape &items,
                            const XCAFPrs_Style &DefStyle,
                            const bool force = true,
                            const TopAbs_ShapeEnum context = TopAbs_SHAPE) {
  const XCAFPrs_Style *style = &DefStyle;
  XCAFPrs_Style ownstyle;

  bool overriden = false;
  if (settings.Contains(shape)) {
    ownstyle = settings.FindFromKey(shape);
    if (!merge_styles(ownstyle, DefStyle)) {
      overriden = true;
      style = &ownstyle;
    }
  }

  BRep_Builder B;
  TopoDS_Shape copy = shape.EmptyCopied();
  bool suboverride = false;
  Standard_Integer nbDef = 0;
  for (TopoDS_Iterator it(shape); it.More(); it.Next()) {
    if (dispatch_styles(it.Value(), settings, items, *style, false,
                        shape.ShapeType())) {
      suboverride = true;
    } else {
      B.Add(copy, it.Value());
      nbDef++;
    }
  }
  if (shape.ShapeType() == TopAbs_FACE || !suboverride)
    copy = shape;
  else if (!nbDef)
    return overriden || suboverride;

  if (overriden || force || (suboverride && context != TopAbs_FACE)) {
    TopoDS_Compound C;
    if (items.IsBound(*style))
      C = TopoDS::Compound(items.Find(*style));
    else {
      B.MakeCompound(C);
      items.Bind(*style, C);
    }
    B.Add(C, copy);
  }
  return overriden || suboverride;
}

bool mesh::style_print(const TDF_Label &aLabel,
                       const TopLoc_Location &aLocation, shape *parent) {
  bool addedShape = false;
  print_tdf_label(aLabel);
  TopoDS_Shape shape;
  if (!XCAFDoc_ShapeTool::GetShape(aLabel, shape) || shape.IsNull())
    return addedShape;

  if (shape.ShapeType() == TopAbs_COMPOUND) {
    TopoDS_Iterator anExplor(shape);
    if (!anExplor.More())
      return addedShape;
  }
  TCollection_AsciiString labelName;
  TDF_Tool::Entry(aLabel, labelName);

  TopLoc_Location L;
  XCAFPrs_IndexedDataMapOfShapeStyle settings;
  XCAFPrs::CollectStyleSettings(aLabel, L, settings);

  XCAFPrs_DataMapOfStyleShape items;
  XCAFPrs_Style DefStyle;
  Quantity_Color White(Quantity_NOC_WHITE);
  DefStyle.SetColorSurf(White);
  DefStyle.SetColorCurv(White);
  dispatch_styles(shape, settings, items, DefStyle);

  XCAFPrs_DataMapIteratorOfDataMapOfStyleShape it(items);
  Standard_Integer i = 1;
  for (; it.More(); it.Next()) {
    XCAFPrs_Style s = it.Key();
    i++;
    auto oshp = shape::make_shape(it.Value());
    if (oshp) {
      oshp->set_label(labelName.ToCString());
      if (s.IsSetColorSurf())
        oshp->set_surface_colour(s.GetColorSurf());
      if (s.IsSetColorCurv())
        oshp->set_curve_colour(s.GetColorCurv());
      _label_shapes.emplace_back(oshp.value());
      addedShape = true;
    }
  }

  return addedShape;
}

void mesh::map_shapes(Handle_TDocStd_Document doc) {
  clear_maps();

  Quantity_Color colour;
  TCollection_ExtendedString layer;
  TDF_LabelSequence root_labels;
  _shape_tool->GetFreeShapes(root_labels);
  TopoDS_Shape S;
  TDF_Label refLabel;
  TopLoc_Location location;

  for (Standard_Integer i = 1; i <= root_labels.Length(); i++) {
    TDF_Label label = root_labels.Value(i);
    label_traversal(label, location, 0);
    create_shape_colour_stacks(label);
    map_stacks();
  }
}

void mesh::map_shapes(Handle_TopTools_HSequenceOfShape shapes) {
  _doc.Nullify();
  clear_maps();
  for (int i = 1; i <= shapes->Length(); i++) {
    map_shape(shapes->Value(i));
  }
}

void mesh::map_shape(TopoDS_Shape shape) {
  bool fix_shape = false;
  if (!shape.IsNull()) {
    if (fix_shape) {
      ShapeFix_Shape fixer(shape);
      fixer.Perform();
      BRepBuilderAPI_Sewing sew;
      sew.Add(fixer.Shape());
      sew.Perform();
      shape = sew.SewedShape();
    }

    build_maps(shape);
    heal_geometry(shape, 1.e-6, true, true, false);
  }
}

void mesh::map_shape(const shape &shp) { return map_shape(shp); }

void mesh::map_shape(const std::vector<shape> &shapes) {
  for (auto &shp : shapes) {
    map_shape(shp);
  }
}

void mesh::clear_maps() {
  _fmap.Clear();
  _emap.Clear();
  _vmap.Clear();
  _shmap.Clear();
  _somap.Clear();
  _csmap.Clear();
  _cmap.Clear();
}

void mesh::build_maps(const TopoDS_Shape &shape) {
  TopExp::MapShapes(shape, TopAbs_VERTEX, _vmap);
  TopExp::MapShapes(shape, TopAbs_EDGE, _emap);
  TopExp::MapShapes(shape, TopAbs_FACE, _fmap);
  TopExp::MapShapes(shape, TopAbs_SHELL, _shmap);
  TopExp::MapShapes(shape, TopAbs_SOLID, _somap);
  TopExp::MapShapes(shape, TopAbs_COMPSOLID, _csmap);
  TopExp::MapShapes(shape, TopAbs_COMPOUND, _cmap);
}

void mesh::heal_geometry(TopoDS_Shape shape, double tolerance,
                         bool fixsmalledges, bool fixspotstripfaces,
                         bool sewfaces, bool makesolids) {
  int nrc = 0, nrcs = 0;
  TopExp_Explorer e;
  for (e.Init(shape, TopAbs_COMPOUND); e.More(); e.Next())
    nrc++;
  for (e.Init(shape, TopAbs_COMPSOLID); e.More(); e.Next())
    nrcs++;

  double surfacecont = 0;

  for (int i = 1; i <= _fmap.Extent(); i++) {
    GProp_GProps system;
    BRepGProp::LinearProperties(_fmap(i), system);
    surfacecont += system.Mass();
  }

  if (fixsmalledges) {
    Handle(ShapeFix_Wire) sfw;
    Handle_ShapeBuild_ReShape rebuild = new ShapeBuild_ReShape;
    rebuild->Apply(shape);

    for (int i = 1; i <= _fmap.Extent(); i++) {
      TopExp_Explorer exp1;
      for (exp1.Init(_fmap(i), TopAbs_WIRE); exp1.More(); exp1.Next()) {
        TopoDS_Wire oldwire = TopoDS::Wire(exp1.Current());
        sfw = new ShapeFix_Wire(oldwire, TopoDS::Face(_fmap(i)), tolerance);
        sfw->ModifyTopologyMode() = Standard_True;

        if (sfw->FixSmall(false, tolerance)) {
          TopoDS_Wire newwire = sfw->Wire();
          rebuild->Replace(oldwire, newwire);
        }
      }
    }
    shape = rebuild->Apply(shape);
  }

  {
    Handle_ShapeBuild_ReShape rebuild = new ShapeBuild_ReShape;
    rebuild->Apply(shape);
    TopExp_Explorer exp1;
    for (exp1.Init(shape, TopAbs_EDGE); exp1.More(); exp1.Next()) {
      TopoDS_Edge edge = TopoDS::Edge(exp1.Current());
      if (_vmap.FindIndex(TopExp::FirstVertex(edge)) ==
          _vmap.FindIndex(TopExp::LastVertex(edge))) {
        GProp_GProps system;
        BRepGProp::LinearProperties(edge, system);
        if (system.Mass() < tolerance) {
          rebuild->Remove(edge);
        }
      }
    }
    shape = rebuild->Apply(shape);
  }

  Handle(ShapeFix_Wireframe) sfwf = new ShapeFix_Wireframe;
  sfwf->SetPrecision(tolerance);
  sfwf->Load(shape);

  shape = sfwf->Shape();

  if (fixspotstripfaces) {
    Handle(ShapeFix_FixSmallFace) sffsm = new ShapeFix_FixSmallFace;
    sffsm->Init(shape);
    sffsm->SetPrecision(tolerance);
    sffsm->Perform();

    shape = sffsm->FixShape();
  }

  if (sewfaces) {
    TopExp_Explorer exp0;

    BRepOffsetAPI_Sewing sewedObj(tolerance);

    for (exp0.Init(shape, TopAbs_FACE); exp0.More(); exp0.Next()) {
      TopoDS_Face face = TopoDS::Face(exp0.Current());
      sewedObj.Add(face);
    }

    sewedObj.Perform();

    if (!sewedObj.SewedShape().IsNull())
      shape = sewedObj.SewedShape();
  }

  if (makesolids) {
    TopExp_Explorer exp0;

    BRepBuilderAPI_MakeSolid ms;
    int count = 0;
    for (exp0.Init(shape, TopAbs_SHELL); exp0.More(); exp0.Next()) {
      count++;
      ms.Add(TopoDS::Shell(exp0.Current()));
    }

    if (count) {
      BRepCheck_Analyzer ba(ms);
      if (ba.IsValid()) {
        Handle(ShapeFix_Shape) sfs = new ShapeFix_Shape;
        sfs->Init(ms);
        sfs->SetPrecision(tolerance);
        sfs->SetMaxTolerance(tolerance);
        sfs->Perform();
        shape = sfs->Shape();

        for (exp0.Init(shape, TopAbs_SOLID); exp0.More(); exp0.Next()) {
          TopoDS_Solid solid = TopoDS::Solid(exp0.Current());
          TopoDS_Solid newsolid = solid;
          BRepLib::OrientClosedSolid(newsolid);
          Handle_ShapeBuild_ReShape rebuild = new ShapeBuild_ReShape;
          rebuild->Replace(solid, newsolid);
          TopoDS_Shape newshape = rebuild->Apply(shape, TopAbs_COMPSOLID, 1);
          shape = newshape;
        }
      }
    }
  }
}

bool mesh::query_color(const TopoDS_Shape &shape, Quantity_Color &color) {
  TDF_Label L;
  if (_doc.IsNull())
    return false;

  color.SetValues(0.5, 0.5, 0.5, Quantity_TOC_RGB);
  if (!_color_tool->ShapeTool()->Search(shape, L))
    return false;

  if (_color_tool->GetColor(shape, XCAFDoc_ColorGen, color))
    return true;
  else if (_color_tool->GetColor(shape, XCAFDoc_ColorCurv, color))
    return true;
  else if (_color_tool->GetColor(shape, XCAFDoc_ColorSurf, color))
    return true;

  return false;
}

} // namespace topo
} // namespace flywave
