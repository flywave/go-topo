#include "dxf_shape.hh"

#include "aci_table.hh"
#include "brep_utils.hh"
#include "dxf.hh"
#include "math_utils.hh"
#include "mesh_utils.hh"
#include "ogg_handle.hh"
#include "string_conv.hh"

#include <BRepAdaptor_Curve.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_MakeVertex.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_Transform.hxx>
#include <BRepMesh_IncrementalMesh.hxx>
#include <BRep_Builder.hxx>
#include <BRep_Tool.hxx>
#include <BSplCLib.hxx>
#include <Font_BRepTextBuilder.hxx>
#include <Font_FontMgr.hxx>
#include <GeomAPI_Interpolate.hxx>
#include <Geom_BSplineCurve.hxx>
#include <Geom_Circle.hxx>
#include <Geom_Ellipse.hxx>
#include <Geom_Line.hxx>
#include <Graphic3d_HorizontalTextAlignment.hxx>
#include <Graphic3d_VerticalTextAlignment.hxx>
#include <Poly_Triangulation.hxx>
#include <Precision.hxx>
#include <Resource_FormatType.hxx>
#include <Resource_Unicode.hxx>
#include <TDataStd_Name.hxx>
#include <TopoDS_Edge.hxx>
#include <XCAFDoc_ShapeTool.hxx>
#include <gp_Circ.hxx>
#include <gp_Elips.hxx>
#include <gp_Pnt.hxx>
#include <gp_Trsf.hxx>

#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <optional>
#include <sstream>

#ifndef OCC_VERSION_CHECK
#define OCC_VERSION_CHECK(major, minor, patch)                                 \
  ((major << 16) | (minor << 8) | (patch))
#endif

namespace flywave {
namespace dxf {
namespace {

std::streampos fileSize(const std::string &path) {
  std::ifstream in(path.c_str());
  in.seekg(0, std::ios::end);
  return in.tellg();
}

bool startsWith(const std::string &str, const std::string &prefix) {
  return str.substr(0, prefix.size()) == prefix;
}

std::string toLowerCase_C(const std::string &str) {
  std::string lstr = str;
  for (char &c : lstr)
    c = std::tolower(c, std::locale::classic());

  return lstr;
}

const std::vector<std::string> &systemFontNames() {
  static std::vector<std::string> fontNames;
  static TColStd_SequenceOfHAsciiString seqFontName;
  if (fontNames.empty()) {
    ogg_handle<Font_FontMgr> fontMgr = Font_FontMgr::GetInstance();
    fontMgr->GetAvailableFontsNames(seqFontName);
    int i = 0;
    for (const ogg_handle<TCollection_HAsciiString> &fontName : seqFontName)
      fontNames.push_back(fontName->String().ToCString());
  }

  return fontNames;
}

gp_Vec toOccVec(const dxf_coords &coords) {
  return {coords.x, coords.y, coords.z};
}

} // namespace

void dxf_shape_reader::get_line() {
  dxf_read::get_line();
  _file_read_size += this->gcount();
}

bool dxf_shape_reader::set_source_encoding(const std::string &codepage) {
  Resource_FormatType encoding = Resource_ANSI;

#if OCC_VERSION_HEX >= OCC_VERSION_CHECK(7, 4, 0)
  if (codepage == "UTF8")
    encoding = Resource_FormatType_UTF8;
  else if (codepage == "ANSI_932") // Japanese
    encoding = Resource_FormatType_SJIS;
  else if (codepage == "ANSI_936") // UnifiedChinese
    encoding = Resource_FormatType_GB;
  else if (codepage == "ANSI_949") // Korean
    encoding = Resource_FormatType_EUC;
#endif

#if OCC_VERSION_HEX >= OCC_VERSION_CHECK(7, 5, 0)
  if (encoding)
    ;                              // Encoding already found above
  else if (codepage == "ANSI_936") // UnifiedChinese
    encoding = Resource_FormatType_GBK;
  else if (codepage == "ANSI_950") // TradChinese
    encoding = Resource_FormatType_Big5;
  else if (codepage == "ANSI_1250")
    encoding = Resource_FormatType_CP1250;
  else if (codepage == "ANSI_1251")
    encoding = Resource_FormatType_CP1251;
  else if (codepage == "ANSI_1252")
    encoding = Resource_FormatType_CP1252;
  else if (codepage == "ANSI_1253")
    encoding = Resource_FormatType_CP1253;
  else if (codepage == "ANSI_1254")
    encoding = Resource_FormatType_CP1254;
  else if (codepage == "ANSI_1255")
    encoding = Resource_FormatType_CP1255;
  else if (codepage == "ANSI_1256")
    encoding = Resource_FormatType_CP1256;
  else if (codepage == "ANSI_1257")
    encoding = Resource_FormatType_CP1257;
  else if (codepage == "ANSI_1258")
    encoding = Resource_FormatType_CP1258;
#endif

#if OCC_VERSION_HEX >= OCC_VERSION_CHECK(7, 6, 0)
  if (encoding)
    ; // Encoding already found above
  else if (codepage == "ANSI_850" || codepage == "DOS850")
    encoding = Resource_FormatType_CP850;
#endif

  _src_encoding = encoding;

  return true;
}

std::string dxf_shape_reader::to_utf8(const std::string &strSource) {
  if (_src_encoding == Resource_ANSI)
    return strSource;

#if OCC_VERSION_HEX >= OCC_VERSION_CHECK(7, 4, 0)
  if (_src_encoding == Resource_FormatType_UTF8)
    return strSource;

  TCollection_ExtendedString extStr;
  Resource_Unicode::ConvertFormatToUnicode(_src_encoding, strSource.c_str(),
                                           extStr);
  return to_std_string(extStr);
#else
  return strSource;
#endif
}

dxf_shape_reader::dxf_shape_reader(const std::string &filepath)
    : dxf_read(filepath.c_str()) {
  if (!this->failed())
    _file_size = fileSize(filepath);
}

void dxf_shape_reader::on_read_line(const dxf_coords &s, const dxf_coords &e,
                                    bool /*hidden*/) {
  const gp_Pnt p0 = this->to_pnt(s);
  const gp_Pnt p1 = this->to_pnt(e);
  if (p0.IsEqual(p1, Precision::Confusion()))
    return;

  const TopoDS_Edge edge = BRepBuilderAPI_MakeEdge(p0, p1);
  this->add_shape(edge);
}

void dxf_shape_reader::on_read_polyline(const dxf_polyline &polyline) {
  const auto &vertices = polyline.vertices;
  if (polyline.flags & dxf_polyline::Flag::PolyfaceMesh) {
    const int meshVertexCount = polyline.polygon_mesh_m_vertex_count;
    TColgp_Array1OfPnt nodes(1, meshVertexCount);
    for (int i = 0; i < meshVertexCount; ++i)
      nodes.ChangeValue(i + 1) = this->to_pnt(vertices.at(i).point);

    const int meshFaceCount = polyline.polygon_mesh_n_vertex_count;
    std::vector<Poly_Triangle> vecTriangle;
    vecTriangle.reserve(meshFaceCount);
    for (int i = 0; i < meshFaceCount; ++i) {
      const dxf_vertex &face = vertices.at(meshVertexCount + i);
      const auto meshVertex1 = std::abs(face.polyface_mesh_vertex1);
      const auto meshVertex2 = std::abs(face.polyface_mesh_vertex2);
      const auto meshVertex3 = std::abs(face.polyface_mesh_vertex3);
      const auto meshVertex4 = std::abs(face.polyface_mesh_vertex4);
      vecTriangle.emplace_back(meshVertex1, meshVertex2, meshVertex3);
      if (meshVertex4 != 0 && meshVertex3 != meshVertex4)
        vecTriangle.emplace_back(meshVertex1, meshVertex3, meshVertex4);
    }

    Poly_Array1OfTriangle triangles(1, static_cast<int>(vecTriangle.size()));
    for (unsigned i = 0; i < vecTriangle.size(); ++i)
      triangles.ChangeValue(i + 1) = vecTriangle.at(i);

    this->add_shape(
        brep_utils::make_face(new Poly_Triangulation(nodes, triangles)));
  } else {
    const bool isPolylineClosed = polyline.flags & dxf_polyline::Flag::Closed;
    const int nodeCount =
        static_cast<int>(vertices.size() + (isPolylineClosed ? 1 : 0));
    mesh_utils::polygon3d_builder polygonBuilder(nodeCount);
    for (unsigned i = 0; i < vertices.size(); ++i)
      polygonBuilder.set_node(i + 1, this->to_pnt(vertices.at(i).point));

    if (isPolylineClosed)
      polygonBuilder.set_node(nodeCount, this->to_pnt(vertices.at(0).point));

    polygonBuilder.finalize();
    this->add_shape(brep_utils::make_edge(polygonBuilder.get()));
  }
}

void dxf_shape_reader::on_read_point(const dxf_coords &s) {
  const TopoDS_Vertex vertex = BRepBuilderAPI_MakeVertex(this->to_pnt(s));
  this->add_shape(vertex);
}

void dxf_shape_reader::on_read_text(const dxf_text &text) {
  const std::string layerName = this->layer_name();
  if (startsWith(layerName, "BLOCKS"))
    return;

  using DxfHJustification = dxf_text::horizontal_justification_type;
  using DxfVJustification = dxf_text::vertical_justification_type;

  const DxfHJustification hjust = text.horizontal_justification;
  Graphic3d_HorizontalTextAlignment hAlign = Graphic3d_HTA_LEFT;
  if (hjust == DxfHJustification::Center || hjust == DxfHJustification::Middle)
    hAlign = Graphic3d_HTA_CENTER;
  else if (hjust == DxfHJustification::Right)
    hAlign = Graphic3d_HTA_RIGHT;

  const DxfVJustification vjust = text.vertical_justification;
  Graphic3d_VerticalTextAlignment vAlign = Graphic3d_VTA_TOP;
  if (vjust == DxfVJustification::Baseline)
    vAlign = Graphic3d_VTA_TOPFIRSTLINE;
  else if (vjust == DxfVJustification::Bottom)
    vAlign = Graphic3d_VTA_BOTTOM;
  else if (vjust == DxfVJustification::Middle)
    vAlign = Graphic3d_VTA_CENTER;

  gp_Vec extDir = toOccVec(text.extrusion_direction);
  if (extDir.Magnitude() < gp::Resolution())
    extDir = gp::DZ();

  const bool applyFirstAlignPnt =
      hjust == DxfHJustification::Left || vjust == DxfVJustification::Baseline;

  const dxf_coords &alignPnt = applyFirstAlignPnt ? text.first_alignment_point
                                                  : text.second_alignment_point;
  const gp_Pnt pt = this->to_pnt(alignPnt);

  gp_Vec xAxisDir = gp::DX();
  if (hjust == DxfHJustification::Aligned || hjust == DxfHJustification::Fit) {
    const gp_Pnt p1 = this->to_pnt(text.first_alignment_point);
    const gp_Pnt p2 = this->to_pnt(text.second_alignment_point);
    xAxisDir = gp_Vec{p1, p2};

    if (xAxisDir.Magnitude() < gp::Resolution())
      xAxisDir = gp::DX();
  }

  xAxisDir.Normalize();
  if (!math_utils::fuzzy_is_null(text.rotation_angle) &&
      xAxisDir.IsEqual(gp::DX(), Precision::Confusion(),
                       Precision::Angular())) {
    gp_Trsf rotTrsf;
    rotTrsf.SetRotation(gp_Ax1(pt, gp::DZ()), text.rotation_angle);
    xAxisDir = gp::DX().Transformed(rotTrsf);
  }

  this->add_text(dxf_text_entity{
      .text = text.str,
      .position = pt,
      .normal = extDir,
      .x_axis_dir = xAxisDir,
      .height = text.height,
      .rotation = text.rotation_angle,
  });
}

void dxf_shape_reader::on_read_mtext(const dxf_mtext &text) {
  const gp_Pnt pt = this->to_pnt(text.insertion_point);
  const std::string layerName = this->layer_name();
  if (startsWith(layerName, "BLOCKS"))
    return;

  const int ap = static_cast<int>(text.attachment_point);
  Graphic3d_HorizontalTextAlignment hAlign = Graphic3d_HTA_LEFT;
  if (ap == 2 || ap == 5 || ap == 8)
    hAlign = Graphic3d_HTA_CENTER;
  else if (ap == 3 || ap == 6 || ap == 9)
    hAlign = Graphic3d_HTA_RIGHT;

  Graphic3d_VerticalTextAlignment vAlign = Graphic3d_VTA_TOP;
  if (ap == 4 || ap == 5 || ap == 6)
    vAlign = Graphic3d_VTA_CENTER;
  else if (ap == 7 || ap == 8 || ap == 9)
    vAlign = Graphic3d_VTA_BOTTOM;

  gp_Vec extDir = toOccVec(text.extrusion_direction);
  if (extDir.Magnitude() < gp::Resolution())
    extDir = gp::DZ();

  gp_Vec xAxisDir = toOccVec(text.x_axis_direction);
  if (xAxisDir.Magnitude() < gp::Resolution())
    xAxisDir = gp::DX();

  xAxisDir.Normalize();
  if (!math_utils::fuzzy_is_null(text.rotation_angle) &&
      xAxisDir.IsEqual(gp::DX(), Precision::Confusion(),
                       Precision::Angular())) {
    gp_Trsf rotTrsf;
    rotTrsf.SetRotation(gp_Ax1(pt, gp::DZ()), text.rotation_angle);
    xAxisDir = gp::DX().Transformed(rotTrsf);
  }

  this->add_text(dxf_text_entity{
      .text = text.str,
      .position = pt,
      .normal = extDir,
      .x_axis_dir = xAxisDir,
      .height = text.height,
      .rotation = text.rotation_angle,
  });
}

void dxf_shape_reader::on_read_arc(const dxf_coords &s, const dxf_coords &e,
                                   const dxf_coords &c, bool dir,
                                   bool /*hidden*/) {
  const gp_Pnt p0 = this->to_pnt(s);
  const gp_Pnt p1 = this->to_pnt(e);
  const gp_Dir up = dir ? gp::DZ() : -gp::DZ();
  const gp_Pnt pc = this->to_pnt(c);
  const gp_Circ circle(gp_Ax2(pc, up), p0.Distance(pc));
  if (circle.Radius() > 0) {
    const TopoDS_Edge edge = BRepBuilderAPI_MakeEdge(circle, p0, p1);
    this->add_shape(edge);
  }
}

void dxf_shape_reader::on_read_circle(const dxf_coords &s, const dxf_coords &c,
                                      bool dir, bool /*hidden*/) {
  const gp_Pnt p0 = this->to_pnt(s);
  const gp_Dir up = dir ? gp::DZ() : -gp::DZ();
  const gp_Pnt pc = this->to_pnt(c);
  const gp_Circ circle(gp_Ax2(pc, up), p0.Distance(pc));
  if (circle.Radius() > 0) {
    const TopoDS_Edge edge = BRepBuilderAPI_MakeEdge(circle);
    this->add_shape(edge);
  }
}

void dxf_shape_reader::on_read_ellipse(const dxf_coords &c, double major_radius,
                                       double minor_radius, double rotation,
                                       double /*start_angle*/,
                                       double /*end_angle*/, bool dir) {
  const gp_Dir up = dir ? gp::DZ() : -gp::DZ();
  const gp_Pnt pc = this->to_pnt(c);
  gp_Elips ellipse(gp_Ax2(pc, up), major_radius * _params.scaling,
                   minor_radius * _params.scaling);
  ellipse.Rotate(gp_Ax1(pc, up), rotation);
  if (ellipse.MinorRadius() > 0) {
    const TopoDS_Edge edge = BRepBuilderAPI_MakeEdge(ellipse);
    this->add_shape(edge);
  }
}

void dxf_shape_reader::on_read_spline(const dxf_spline &spline) {
  try {
    ogg_handle<Geom_BSplineCurve> geom;
    if (!spline.control_points.empty())
      geom = create_spline_from_poles_and_knots(spline);
    else if (!spline.fit_points.empty())
      geom = create_interpolation_spline(spline);

    if (geom.IsNull())
      throw Standard_Failure("Geom_BSplineCurve object is null");

    const TopoDS_Edge edge = BRepBuilderAPI_MakeEdge(geom);
    this->add_shape(edge);
  } catch (const Standard_Failure &err) {
    //
  }
}

void dxf_shape_reader::on_read_insert(const dxf_insert &ins) {
  const std::string prefix = "BLOCKS " + ins.block_name + " ";
  for (const auto &pair : _layers) {
    auto &vecEntity = pair.second;
    if (!startsWith(pair.first, prefix))
      continue; // Skip

    TopoDS_Shape comp = brep_utils::make_empty_compound();
    for (const dxf_shape_entity &entity : vecEntity) {
      if (!entity.shape.IsNull())
        brep_utils::add_shape(&comp, entity.shape);
    }

    if (comp.IsNull())
      continue; // Skip

    if (!math_utils::fuzzy_equal(ins.scale_factor.x, ins.scale_factor.y) ||
        !math_utils::fuzzy_equal(ins.scale_factor.x, ins.scale_factor.y)) {
      // logo
    }

    auto fnNonNull = [](double v) {
      return !math_utils::fuzzy_is_null(v) ? v : 1.;
    };
    const double avgScale = std::abs(fnNonNull(
        (ins.scale_factor.x + ins.scale_factor.y + ins.scale_factor.z) / 3.));
    if (!math_utils::fuzzy_equal(avgScale, 1.)) {
      gp_Trsf trsf;
      trsf.SetScaleFactor(avgScale);
      BRepBuilderAPI_Transform brepTrsf(comp, trsf);
      if (brepTrsf.IsDone()) {
        comp = brepTrsf.Shape();
      }
    }

    gp_Trsf trsfRotZ;
    if (!math_utils::fuzzy_is_null(ins.rotation_angle))
      trsfRotZ.SetRotation(gp::OZ(), ins.rotation_angle);

    gp_Trsf trsfMove;
    trsfMove.SetTranslation(this->to_pnt(ins.insert_point).XYZ());

    comp.Location(trsfRotZ * trsfMove);
    this->add_shape(comp);
  }
}

void dxf_shape_reader::on_read_dimension(const dxf_coords &s,
                                         const dxf_coords &e,
                                         const dxf_coords &point,
                                         double rotation) {}

void dxf_shape_reader::on_read_solid(const dxf_solid &solid) {
  dxf_quad_base quad = solid;
  if (solid.has_corner4) {
    std::swap(quad.corner3, quad.corner4);
  }

  try {
    const TopoDS_Face face = make_face(quad);
    if (!face.IsNull())
      this->add_shape(face);
  } catch (...) {
    //
  }
}

void dxf_shape_reader::on_read_3d_face(const dxf_3d_face &face) {
  try {
    const TopoDS_Face brepFace = make_face(face);
    if (!brepFace.IsNull())
      this->add_shape(brepFace);
  } catch (...) {
    // m_messenger->emitError("OnReadFace() failed");
  }
}

void dxf_shape_reader::report_error(const std::string &msg) {
  this->_error = msg;
}

void dxf_shape_reader::add_graphics() const {
  // Nothing
}

gp_Pnt dxf_shape_reader::to_pnt(const dxf_coords &coords) const {
  double sp1(coords.x);
  double sp2(coords.y);
  double sp3(coords.z);
  if (!math_utils::fuzzy_equal(_params.scaling, 1.)) {
    sp1 = sp1 * _params.scaling;
    sp2 = sp2 * _params.scaling;
    sp3 = sp3 * _params.scaling;
  }

  return gp_Pnt(sp1, sp2, sp3);
}

void dxf_shape_reader::add_text(const dxf_text_entity &text) {
  const std::string layerName = this->layer_name();
  if (this->_layer_names.find(layerName) == this->_layer_names.end()) {
    this->_layer_names.insert(layerName);
  }
  auto itFound = _texts.find(layerName);
  if (itFound != _texts.end()) {
    std::vector<dxf_text_entity> &vecEntity = itFound->second;
    vecEntity.push_back(text);
  } else {
    decltype(_texts)::value_type pair(std::move(layerName), {text});
    _texts.insert(std::move(pair));
  }
}

void dxf_shape_reader::add_shape(const TopoDS_Shape &shape) {
  const dxf_shape_entity newEntity{_color_index, shape};
  const std::string layerName = this->layer_name();
  if (this->_layer_names.find(layerName) == this->_layer_names.end()) {
    this->_layer_names.insert(layerName);
  }
  auto itFound = _layers.find(layerName);
  if (itFound != _layers.end()) {
    std::vector<dxf_shape_entity> &vecEntity = itFound->second;
    vecEntity.push_back(newEntity);
  } else {
    decltype(_layers)::value_type pair(std::move(layerName), {newEntity});
    _layers.insert(std::move(pair));
  }
}

TopoDS_Face dxf_shape_reader::make_face(const dxf_quad_base &quad) const {
  const gp_Pnt p1 = this->to_pnt(quad.corner1);
  const gp_Pnt p2 = this->to_pnt(quad.corner2);
  const gp_Pnt p3 = this->to_pnt(quad.corner3);
  const gp_Pnt p4 = this->to_pnt(quad.corner4);

  const double pntTolerance = Precision::Confusion();
  if (p1.IsEqual(p2, pntTolerance) || p1.IsEqual(p3, pntTolerance) ||
      p2.IsEqual(p3, pntTolerance))
    return {};

  TopoDS_Face face;
  BRepBuilderAPI_MakeWire makeWire;
  makeWire.Add(BRepBuilderAPI_MakeEdge(p1, p2));
  makeWire.Add(BRepBuilderAPI_MakeEdge(p2, p3));
  if (quad.has_corner4 && !p3.IsEqual(p4, pntTolerance) &&
      !p1.IsEqual(p4, pntTolerance)) {
    makeWire.Add(BRepBuilderAPI_MakeEdge(p3, p4));
    makeWire.Add(BRepBuilderAPI_MakeEdge(p4, p1));
  } else {
    makeWire.Add(BRepBuilderAPI_MakeEdge(p3, p1));
  }

  if (makeWire.IsDone())
    face = BRepBuilderAPI_MakeFace(makeWire.Wire(), true /*onlyPlane*/);

  return face;
}

ogg_handle<Geom_BSplineCurve>
dxf_shape_reader::create_spline_from_poles_and_knots(const dxf_spline &spline) {
  if (spline.weights.size() > spline.control_points.size())
    return {};

  const bool isPeriodic = (spline.flags & dxf_spline::Periodic) != 0;

  const auto iNumPoles = static_cast<int>(spline.control_points.size());
  TColgp_Array1OfPnt occPoles(1, iNumPoles);
  for (const dxf_coords &pnt : spline.control_points) {
    const auto iPnt = static_cast<int>(&pnt - &spline.control_points.front());
    occPoles.ChangeValue(iPnt + 1) = gp_Pnt{pnt.x, pnt.y, pnt.z};
  }

  const auto iNumKnots = static_cast<int>(spline.knots.size());
  TColStd_Array1OfReal occKnots(1, iNumKnots);
  std::copy(spline.knots.cbegin(), spline.knots.cend(), occKnots.begin());

  const auto iNumUniqueKnots = BSplCLib::KnotsLength(occKnots, isPeriodic);
  TColStd_Array1OfReal occUniqueKnots(1, iNumUniqueKnots);
  TColStd_Array1OfInteger occMults(1, iNumUniqueKnots);
  BSplCLib::Knots(occKnots, std::ref(occUniqueKnots), std::ref(occMults),
                  isPeriodic);

  TColStd_Array1OfReal occWeights(1, iNumPoles);
  if (spline.weights.size() == spline.control_points.size())
    std::copy(spline.weights.cbegin(), spline.weights.cend(),
              occWeights.begin());
  else
    std::fill(occWeights.begin(), occWeights.end(), 1.);

  return new Geom_BSplineCurve(occPoles, occWeights, occUniqueKnots, occMults,
                               spline.degree, isPeriodic);
}

ogg_handle<Geom_BSplineCurve>
dxf_shape_reader::create_interpolation_spline(const dxf_spline &spline) {
  const auto iNumPoints = static_cast<int>(spline.fit_points.size());

  // Handle poles
  auto fitpoints = make_ogg_handle<TColgp_HArray1OfPnt>(1, iNumPoints);
  for (const dxf_coords &pnt : spline.fit_points) {
    const auto iPnt = static_cast<int>(&pnt - &spline.fit_points.front());
    fitpoints->ChangeValue(iPnt + 1) = gp_Pnt{pnt.x, pnt.y, pnt.z};
  }

  const bool isPeriodic = (spline.flags & dxf_spline::Periodic) != 0;
  GeomAPI_Interpolate interp(fitpoints, isPeriodic, Precision::Confusion());
  interp.Perform();
  return interp.Curve();
}

dxf_shape_writer::dxf_shape_writer(const std::string &filepath)
    : dxf_write(filepath.c_str()) {}

void dxf_shape_writer::add_text(const std::string &layer_name,
                                const dxf_text_entity &text) {
  auto &layer_texts = _texts[layer_name];
  layer_texts.push_back(text);
}

void dxf_shape_writer::add_shape(const std::string &layer_name,
                                 const TopoDS_Shape &shape,
                                 color_index_t color) {
  _layers[layer_name].push_back({color, shape});
}

void dxf_shape_writer::add_shape_layer(
    const std::string &layer_name,
    const std::vector<std::pair<TopoDS_Shape, color_index_t>> &shapes) {
  auto &layer_shapes = _layers[layer_name];
  layer_shapes.reserve(layer_shapes.size() + shapes.size());

  for (const auto &shape_pair : shapes) {
    layer_shapes.emplace_back(dxf_shape_entity{.color = shape_pair.second,
                                               .shape = shape_pair.first});
  }
}

void dxf_shape_writer::add_text_layer(
    const std::string &layer_name, const std::vector<dxf_text_entity> &texts) {
  auto &layer_texts = _texts[layer_name];
  layer_texts.insert(layer_texts.end(), texts.begin(), texts.end());
}

bool dxf_shape_writer::write() {
  try {
    init();

    for (const auto &layer : _layers) {
      set_layer_name(layer.first);
      for (const auto &entity : layer.second) {
        write_shape(entity.shape, entity.color);
      }
    }

    for (const auto &layer_pair : _texts) {
      set_layer_name(layer_pair.first);
      for (const dxf_text_entity &text : layer_pair.second) {
        put_text(text, get_entity_stream(), get_entity_handle(),
                 get_layer_handle());
      }
    }

    end_run();
    return !failed();
  } catch (...) {
    return false;
  }
}

void dxf_shape_writer::write_shape(const TopoDS_Shape &shape,
                                   color_index_t color) {
  switch (shape.ShapeType()) {
  case TopAbs_COMPOUND:
  case TopAbs_COMPSOLID:
    for (TopoDS_Iterator it(shape); it.More(); it.Next()) {
      write_shape(it.Value(), color);
    }
    break;
  case TopAbs_SOLID:
  case TopAbs_SHELL:
    for (TopoDS_Iterator it(shape); it.More(); it.Next()) {
      write_face(TopoDS::Face(it.Value()), color);
    }
    break;
  case TopAbs_FACE:
    write_face(TopoDS::Face(shape), color);
    break;
  case TopAbs_WIRE:
    write_wire(TopoDS::Wire(shape), color);
    break;
  case TopAbs_EDGE:
    write_edge(TopoDS::Edge(shape), color);
    break;
  case TopAbs_VERTEX:
    write_vertex(TopoDS::Vertex(shape), color);
    break;
  default:
    break;
  }
}

void dxf_shape_writer::write_edge(const TopoDS_Edge &edge,
                                  color_index_t color) {
  Standard_Real first, last;
  Handle(Geom_Curve) curve = BRep_Tool::Curve(edge, first, last);

  if (curve.IsNull())
    return;

  if (curve->DynamicType() == STANDARD_TYPE(Geom_Line)) {
    Handle(Geom_Line) line = Handle(Geom_Line)::DownCast(curve);
    write_line(line->Value(first), line->Value(last));
  } else if (curve->DynamicType() == STANDARD_TYPE(Geom_Ellipse)) {
    Handle(Geom_Ellipse) ellipse = Handle(Geom_Ellipse)::DownCast(curve);
    write_ellipse(ellipse->Elips());
  } else if (curve->DynamicType() == STANDARD_TYPE(Geom_BSplineCurve)) {
    Handle(Geom_BSplineCurve) spline =
        Handle(Geom_BSplineCurve)::DownCast(curve);
    write_spline(spline, color);
  } else if (curve->DynamicType() == STANDARD_TYPE(Geom_Circle)) {
    Handle(Geom_Circle) circle = Handle(Geom_Circle)::DownCast(curve);
    const double angle_tolerance = Precision::Angular();
    if (Abs(last - first - 2 * M_PI) > angle_tolerance) {
      write_arc(circle->Circ(), first, last);
    } else {
      write_circle(circle->Circ());
    }
  }
}

void dxf_shape_writer::write_wire(const TopoDS_Wire &wire,
                                  color_index_t color) {
  for (TopExp_Explorer exp(wire, TopAbs_EDGE); exp.More(); exp.Next()) {
    write_edge(TopoDS::Edge(exp.Current()), color);
  }
}

void dxf_shape_writer::write_face(const TopoDS_Face &face,
                                  color_index_t color) {
  if (_params.write_3d_face) {
    write_3d_face(face, color);
  }
  for (TopExp_Explorer exp(face, TopAbs_WIRE); exp.More(); exp.Next()) {
    write_wire(TopoDS::Wire(exp.Current()), color);
  }
}

void dxf_shape_writer::write_vertex(const TopoDS_Vertex &vertex,
                                    color_index_t color) {
  gp_Pnt p = BRep_Tool::Pnt(vertex);
  write_point(p);
}

void dxf_shape_writer::write_line(const gp_Pnt &start, const gp_Pnt &end) {
  put_line(start, end, get_entity_stream(), get_entity_handle(),
           get_layer_handle());
}

void dxf_shape_writer::write_circle(const gp_Circ &circle) {
  put_circle(circle, get_entity_stream(), get_entity_handle(),
             get_layer_handle());
}

void dxf_shape_writer::write_arc(const gp_Circ &circle, double start_angle,
                                 double end_angle) {
  const gp_Pnt center = circle.Location();
  const double radius = circle.Radius();
  dxf_coords c{center.X(), center.Y(), center.Z()};
  dxf_coords s{center.X() + radius * cos(start_angle),
               center.Y() + radius * sin(start_angle), center.Z()};
  dxf_coords e{center.X() + radius * cos(end_angle),
               center.Y() + radius * sin(end_angle), center.Z()};
  put_arc(c, s, e, get_entity_stream(), get_entity_handle(),
          get_layer_handle());
}

void dxf_shape_writer::write_ellipse(const gp_Elips &ellipse) {
  const gp_Pnt center = ellipse.Location();
  const double majorRadius = ellipse.MajorRadius();
  const double minorRadius = ellipse.MinorRadius();
  const double rotationAngle = ellipse.XAxis().Direction().Angle(gp::DX());

  dxf_coords c{center.X(), center.Y(), center.Z()};
  dxf_coords majorPoint{center.X() + majorRadius * cos(rotationAngle),
                        center.Y() + majorRadius * sin(rotationAngle),
                        center.Z()};
  put_ellipse(c, majorPoint, minorRadius / majorRadius, get_entity_stream(),
              get_entity_handle(), get_layer_handle());
}

void dxf_shape_writer::write_spline(const Handle(Geom_BSplineCurve) & spline,
                                    color_index_t color) {
  dxf_spline dxfSpline;
  dxfSpline.degree = spline->Degree();

  for (int i = 1; i <= spline->NbPoles(); ++i) {
    gp_Pnt p = spline->Pole(i);
    dxfSpline.control_points.push_back(dxf_coords{p.X(), p.Y(), p.Z()});
  }

  for (int i = 1; i <= spline->NbKnots(); ++i) {
    dxfSpline.knots.push_back(spline->Knot(i));
  }

  if (spline->IsRational()) {
    for (int i = 1; i <= spline->NbPoles(); ++i) {
      dxfSpline.weights.push_back(spline->Weight(i));
    }
  }

  dxfSpline.flags = 0;
  if (spline->IsPeriodic()) {
    dxfSpline.flags |= dxf_spline::Periodic;
  }
  if (spline->IsRational()) {
    dxfSpline.flags |= dxf_spline::Rational;
  }

  put_spline(dxfSpline, get_entity_stream(), get_entity_handle(),
             get_layer_handle());
}

void dxf_shape_writer::write_point(const gp_Pnt &point) {
  dxf_coords p{point.X(), point.Y(), point.Z()};
  put_point(p, get_entity_stream(), get_entity_handle(), get_layer_handle());
}

void dxf_shape_writer::put_line(const gp_Pnt &start, const gp_Pnt &end,
                                std::ostringstream &outStream,
                                const std::string &handle,
                                const std::string &ownerHandle) {
  vector3d s{start.X(), start.Y(), start.Z()};
  vector3d e{end.X(), end.Y(), end.Z()};
  dxf_write::put_line(s, e, outStream, handle, ownerHandle);
}
void dxf_shape_writer::write_3d_face(const TopoDS_Face &face,
                                     color_index_t color) {
  TopLoc_Location loc;
  Handle(Poly_Triangulation) triangulation =
      BRep_Tool::Triangulation(face, loc);
  if (!triangulation.IsNull()) {
    const Poly_ArrayOfNodes &nodes = triangulation->InternalNodes();
    for (int i = 1; i <= nodes.Length(); i += 3) {
      gp_Pnt p1 = nodes.Value(i).Transformed(loc);
      gp_Pnt p2 = nodes.Value(i + 1).Transformed(loc);
      gp_Pnt p3 = nodes.Value(i + 2).Transformed(loc);
      gp_Pnt p4 = p3;

      std::array<dxf_coords, 4> corners = {dxf_coords{p1.X(), p1.Y(), p1.Z()},
                                           dxf_coords{p2.X(), p2.Y(), p2.Z()},
                                           dxf_coords{p3.X(), p3.Y(), p3.Z()},
                                           dxf_coords{p4.X(), p4.Y(), p4.Z()}};
      put_3d_face(corners, get_entity_stream(), get_entity_handle(),
                  get_layer_handle());
    }
  }
}

void dxf_shape_writer::put_3d_face(const std::array<dxf_coords, 4> &corners,
                                   std::ostringstream &outStream,
                                   const std::string &handle,
                                   const std::string &ownerHandle) {
  outStream << "  0" << std::endl;
  outStream << "3DFACE" << std::endl;
  outStream << "  5" << std::endl;
  outStream << handle << std::endl;
  outStream << "  8" << std::endl;
  outStream << ownerHandle << std::endl;

  for (int i = 0; i < 4; i++) {
    outStream << " 1" << (i + 1) << std::endl;
    outStream << corners[i].x << std::endl;
    outStream << " 2" << (i + 1) << std::endl;
    outStream << corners[i].y << std::endl;
    outStream << " 3" << (i + 1) << std::endl;
    outStream << corners[i].z << std::endl;
  }

  if (corners[2] == corners[3]) {
    outStream << " 70" << std::endl;
    outStream << "1" << std::endl;
  }
}

void dxf_shape_writer::put_circle(const gp_Circ &circle,
                                  std::ostringstream &outStream,
                                  const std::string &handle,
                                  const std::string &ownerHandle) {
  outStream << "  0" << std::endl;
  outStream << "CIRCLE" << std::endl;
  outStream << "  5" << std::endl;
  outStream << handle << std::endl;
  outStream << "  8" << std::endl;
  outStream << ownerHandle << std::endl;

  const gp_Pnt center = circle.Location();
  outStream << " 10" << std::endl;
  outStream << center.X() << std::endl;
  outStream << " 20" << std::endl;
  outStream << center.Y() << std::endl;
  outStream << " 30" << std::endl;
  outStream << center.Z() << std::endl;

  outStream << " 40" << std::endl;
  outStream << circle.Radius() << std::endl;

  const gp_Dir normal = circle.Axis().Direction();
  if (!normal.IsEqual(gp::DZ(), Precision::Angular())) {
    outStream << "210" << std::endl;
    outStream << normal.X() << std::endl;
    outStream << "220" << std::endl;
    outStream << normal.Y() << std::endl;
    outStream << "230" << std::endl;
    outStream << normal.Z() << std::endl;
  }
}

void dxf_shape_writer::put_arc(const dxf_coords &center,
                               const dxf_coords &start, const dxf_coords &end,
                               std::ostringstream &outStream,
                               const std::string &handle,
                               const std::string &ownerHandle) {
  outStream << "  0" << std::endl;
  outStream << "ARC" << std::endl;
  outStream << "  5" << std::endl;
  outStream << handle << std::endl;
  outStream << "  8" << std::endl;
  outStream << ownerHandle << std::endl;

  outStream << " 10" << std::endl;
  outStream << center.x << std::endl;
  outStream << " 20" << std::endl;
  outStream << center.y << std::endl;
  outStream << " 30" << std::endl;
  outStream << center.z << std::endl;

  double radius = sqrt(pow(start.x - center.x, 2) + pow(start.y - center.y, 2));
  outStream << " 40" << std::endl;
  outStream << radius << std::endl;

  double start_angle =
      atan2(start.y - center.y, start.x - center.x) * 180.0 / M_PI;
  double end_angle = atan2(end.y - center.y, end.x - center.x) * 180.0 / M_PI;

  if (start_angle < 0)
    start_angle += 360.0;
  if (end_angle < 0)
    end_angle += 360.0;

  if (start_angle > end_angle) {
    end_angle += 360.0;
  }

  outStream << " 50" << std::endl;
  outStream << start_angle << std::endl;
  outStream << " 51" << std::endl;
  outStream << end_angle << std::endl;
}

void dxf_shape_writer::put_ellipse(const dxf_coords &center,
                                   const dxf_coords &majorPoint, double ratio,
                                   std::ostringstream &outStream,
                                   const std::string &handle,
                                   const std::string &ownerHandle) {
  outStream << "  0" << std::endl;
  outStream << "ELLIPSE" << std::endl;
  outStream << "  5" << std::endl;
  outStream << handle << std::endl;
  outStream << "  8" << std::endl;
  outStream << ownerHandle << std::endl;

  outStream << " 10" << std::endl;
  outStream << center.x << std::endl;
  outStream << " 20" << std::endl;
  outStream << center.y << std::endl;
  outStream << " 30" << std::endl;
  outStream << center.z << std::endl;

  outStream << " 11" << std::endl;
  outStream << majorPoint.x - center.x << std::endl;
  outStream << " 21" << std::endl;
  outStream << majorPoint.y - center.y << std::endl;
  outStream << " 31" << std::endl;
  outStream << majorPoint.z - center.z << std::endl;

  outStream << " 40" << std::endl;
  outStream << ratio << std::endl;

  outStream << " 41" << std::endl;
  outStream << "0.0" << std::endl;
  outStream << " 42" << std::endl;
  outStream << "6.283185307179586" << std::endl;

  const gp_Dir normal = gp::DZ();
  outStream << "210" << std::endl;
  outStream << normal.X() << std::endl;
  outStream << "220" << std::endl;
  outStream << normal.Y() << std::endl;
  outStream << "230" << std::endl;
  outStream << normal.Z() << std::endl;
}

void dxf_shape_writer::put_point(const dxf_coords &point,
                                 std::ostringstream &outStream,
                                 const std::string &handle,
                                 const std::string &ownerHandle) {
  outStream << std::setprecision(15);

  outStream << "  0" << std::endl;
  outStream << "POINT" << std::endl;
  outStream << "  5" << std::endl;
  outStream << handle << std::endl;
  outStream << "  8" << std::endl;
  outStream << ownerHandle << std::endl;

  outStream << " 10" << std::endl;
  outStream << point.x << std::endl;
  outStream << " 20" << std::endl;
  outStream << point.y << std::endl;
  outStream << " 30" << std::endl;
  outStream << point.z << std::endl;
}

void dxf_shape_writer::put_text(const dxf_text_entity &text,
                                std::ostringstream &outStream,
                                const std::string &handle,
                                const std::string &ownerHandle) {
  outStream << "  0" << std::endl;
  outStream << "TEXT" << std::endl;
  outStream << "  5" << std::endl;
  outStream << handle << std::endl;
  outStream << "  8" << std::endl;
  outStream << ownerHandle << std::endl;

  outStream << " 10" << std::endl;
  outStream << text.position.X() << std::endl;
  outStream << " 20" << std::endl;
  outStream << text.position.Y() << std::endl;
  outStream << " 30" << std::endl;
  outStream << text.position.Z() << std::endl;

  outStream << "  1" << std::endl;
  outStream << text.text << std::endl;

  outStream << " 40" << std::endl;
  outStream << text.height << std::endl;

  outStream << " 50" << std::endl;
  outStream << text.rotation << std::endl;

  outStream << " 62" << std::endl;
  outStream << text.color << std::endl;
}

void dxf_shape_writer::put_spline(const dxf_spline &spline,
                                  std::ostringstream &outStream,
                                  const std::string &handle,
                                  const std::string &ownerHandle) {
  outStream << "  0" << std::endl;
  outStream << "SPLINE" << std::endl;
  outStream << "  5" << std::endl;
  outStream << handle << std::endl;
  outStream << "  8" << std::endl;
  outStream << ownerHandle << std::endl;

  outStream << " 70" << std::endl;
  outStream << spline.flags << std::endl;

  outStream << " 71" << std::endl;
  outStream << spline.degree << std::endl;

  outStream << " 72" << std::endl;
  outStream << spline.knots.size() << std::endl;

  outStream << " 73" << std::endl;
  outStream << spline.control_points.size() << std::endl;

  for (const auto &knot : spline.knots) {
    outStream << " 40" << std::endl;
    outStream << knot << std::endl;
  }

  for (const auto &point : spline.control_points) {
    outStream << " 10" << std::endl;
    outStream << point.x << std::endl;
    outStream << " 20" << std::endl;
    outStream << point.y << std::endl;
    outStream << " 30" << std::endl;
    outStream << point.z << std::endl;
  }

  if (!spline.weights.empty()) {
    for (const auto &weight : spline.weights) {
      outStream << " 41" << std::endl;
      outStream << weight << std::endl;
    }
  }

  if (!spline.fit_points.empty()) {
    outStream << " 11" << std::endl;
    outStream << spline.fit_points.size() << std::endl;

    for (const auto &point : spline.fit_points) {
      outStream << " 11" << std::endl;
      outStream << point.x << std::endl;
      outStream << " 21" << std::endl;
      outStream << point.y << std::endl;
      outStream << " 31" << std::endl;
      outStream << point.z << std::endl;
    }
  }

  if (!spline.start_tangents.empty()) {
    for (const auto &t : spline.start_tangents) {
      outStream << " 12" << std::endl;
      outStream << t.x << std::endl;
      outStream << " 22" << std::endl;
      outStream << t.y << std::endl;
      outStream << " 32" << std::endl;
      outStream << t.z << std::endl;
    }
  }

  if (!spline.end_tangents.empty()) {
    for (const auto &t : spline.end_tangents) {
      outStream << " 13" << std::endl;
      outStream << t.x << std::endl;
      outStream << " 23" << std::endl;
      outStream << t.y << std::endl;
      outStream << " 33" << std::endl;
      outStream << t.z << std::endl;
    }
  }
}
} // namespace dxf
} // namespace flywave
