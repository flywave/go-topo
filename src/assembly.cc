#include "assembly.hh"
#include <boost/fusion/adapted/struct.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/optional.hpp>
#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/string/symbols.hpp>
#include <boost/spirit/include/support_istream_iterator.hpp>
#include <boost/variant.hpp>

#include <BOPAlgo_Options.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <IFSelect_ReturnStatus.hxx>
#include <Interface_Static.hxx>
#include <STEPCAFControl_Writer.hxx>
#include <STEPControl_StepModelType.hxx>
#include <TColStd_IndexedDataMapOfStringString.hxx>
#include <TCollection_ExtendedString.hxx>
#include <TDF_Label.hxx>
#include <TDataStd_Name.hxx>
#include <TDocStd_Document.hxx>
#include <TopLoc_Location.hxx>
#include <TopTools_ListOfShape.hxx>
#include <TopoDS_Shape.hxx>
#include <XCAFApp_Application.hxx>
#include <XCAFDoc_ColorTool.hxx>
#include <XCAFDoc_DocumentTool.hxx>
#include <XCAFDoc_ShapeTool.hxx>
#include <XSControl_WorkSession.hxx>

#include <iomanip>
#include <map>
#include <memory>
#include <mutex>
#include <random>
#include <sstream>
#include <string>
#include <unordered_set>
#include <utility>

#include "compound.hh"
#include "workplane.hh"

namespace x3 = boost::spirit::x3;

struct parse_result {
  std::string name;
  std::string tag;
  std::string selector_kind;
  std::string selector;
};

// clang-format off
BOOST_FUSION_ADAPT_STRUCT(parse_result,
  (std::string, name)
  (std::string, tag)
  (std::string, selector_kind)
  (std::string, selector)
)
// clang-format on

namespace flywave {
namespace topo {
namespace detail {
std::mutex uuid_mutex;

std::string generate_uuid() {
  std::lock_guard<std::mutex> lock(uuid_mutex);
  static thread_local std::mt19937 gen(std::random_device{}());
  std::uniform_int_distribution<> dis(0, 255);

  std::stringstream ss;
  ss << std::hex << std::setfill('0');

  for (int i = 0; i < 16; ++i) {
    ss << std::setw(2) << dis(gen);
    if (i == 3 || i == 5 || i == 7 || i == 9) {
      ss << "-";
    }
  }

  return ss.str();
}

inline void set_doc_name(const TDF_Label &label, const std::string &name,
                         const Handle(XCAFDoc_ShapeTool) & tool) {
  TDataStd_Name::Set(label, TCollection_ExtendedString(name.c_str()));
}

inline void set_doc_color(const TDF_Label &label, const Quantity_Color &color,
                          const Handle(XCAFDoc_ColorTool) & tool) {
  tool->SetColor(label, color, XCAFDoc_ColorGen);
}

std::pair<TDF_Label, Handle(TDocStd_Document)>
toFusedCAF(const std::shared_ptr<assembly> &assy, bool glue = false,
           boost::optional<float> tol = boost::none) {
  Handle(XCAFApp_Application) app = XCAFApp_Application::GetApplication();
  Handle(TDocStd_Document) doc =
      new TDocStd_Document(TCollection_ExtendedString("XmlOcaf"));
  app->InitDocument(doc);

  Handle(XCAFDoc_ShapeTool) shape_tool =
      XCAFDoc_DocumentTool::ShapeTool(doc->Main());
  Handle(XCAFDoc_ColorTool) color_tool =
      XCAFDoc_DocumentTool::ColorTool(doc->Main());

  BRepAlgoAPI_Fuse fuse_op;
  TopTools_ListOfShape args;
  TopTools_ListOfShape tools;

  std::vector<std::pair<shape, std::shared_ptr<Quantity_Color>>>
      shape_color_pairs;

  auto elements = assy->get_elements();
  for (const auto &el : elements) {
    shape_color_pairs.emplace_back(el.shp.moved(el.location).copy(), el.color);
  }

  TopoDS_Shape top_level_shape;

  if (shape_color_pairs.empty()) {
    throw std::runtime_error("Error: Assembly " + assy->name() +
                             " has no shapes.");
  } else if (shape_color_pairs.size() == 1) {
    const auto &pair = shape_color_pairs[0];
    if (pair.first.shape_type() != TopAbs_COMPOUND) {
      if (glue) {
        auto fused = *topo::fuse({pair.first}, tol ? *tol : 0.0f, glue);
        top_level_shape = compound::make_compound({fused}).value();
        shape_color_pairs = {{fused, pair.second}};
      } else {
        top_level_shape = compound::make_compound({pair.first}).value();
      }
    } else {
      auto fused = *topo::fuse({pair.first}, tol ? *tol : 0.0f, glue);
      top_level_shape = compound::make_compound({fused}).value();
      shape_color_pairs = {{fused, pair.second}};
    }
  } else {
    args.Append(shape_color_pairs[0].first.value());
    for (size_t i = 1; i < shape_color_pairs.size(); ++i) {
      tools.Append(shape_color_pairs[i].first.value());
    }

    if (tol) {
      fuse_op.SetFuzzyValue(*tol);
    }
    if (glue) {
      fuse_op.SetGlue(BOPAlgo_GlueShift);
    }

    fuse_op.SetArguments(args);
    fuse_op.SetTools(tools);
    fuse_op.Build();

    top_level_shape = fuse_op.Shape();
  }

  TDF_Label top_level_lbl =
      shape_tool->AddShape(top_level_shape, Standard_False);
  TDataStd_Name::Set(top_level_lbl,
                     TCollection_ExtendedString(assy->name().c_str()));

  for (const auto &pair : shape_color_pairs) {
    const auto &shape = pair.first;
    const auto &color = pair.second;
    for (const auto &face : shape.faces()) {
      TDF_Label cur_lbl = shape_tool->AddSubShape(top_level_lbl, face.value());
      if (color && !cur_lbl.IsNull() && !fuse_op.IsDeleted(face.value())) {
        color_tool->SetColor(cur_lbl, *color, XCAFDoc_ColorGen);
      }

      const TopTools_ListOfShape &modded_list = fuse_op.Modified(face.value());
      for (TopTools_ListIteratorOfListOfShape it(modded_list); it.More();
           it.Next()) {
        const TopoDS_Shape &mod = it.Value();
        cur_lbl = shape_tool->AddSubShape(top_level_lbl, mod);
        if (color && !cur_lbl.IsNull() && !fuse_op.IsDeleted(mod)) {
          color_tool->SetColor(cur_lbl, *color, XCAFDoc_ColorGen);
        }
      }

      const TopTools_ListOfShape &gen_list = fuse_op.Generated(face.value());
      for (TopTools_ListIteratorOfListOfShape it(gen_list); it.More();
           it.Next()) {
        const TopoDS_Shape &gen = it.Value();
        cur_lbl = shape_tool->AddSubShape(top_level_lbl, gen);
        if (color && !cur_lbl.IsNull()) {
          color_tool->SetColor(cur_lbl, *color, XCAFDoc_ColorGen);
        }
      }
    }
  }

  return {top_level_lbl, doc};
}

struct document_raii {
  Handle(TDocStd_Document) doc;
  Handle(XCAFApp_Application) app;

  document_raii() : app(XCAFApp_Application::GetApplication()) {
    doc = new TDocStd_Document(TCollection_ExtendedString("XmlOcaf"));
    app->InitDocument(doc);
  }

  ~document_raii() {
    if (app && doc) {
      app->Close(doc);
    }
  }
};

std::pair<TDF_Label, Handle(TDocStd_Document)>
toCAF(const std::shared_ptr<assembly> &assy, bool coloredSTEP = false,
      float tolerance = 1e-3f, float angularTolerance = 0.1f) {
  document_raii wrapper;

  Handle(XCAFDoc_ShapeTool) tool =
      XCAFDoc_DocumentTool::ShapeTool(wrapper.doc->Main());
  tool->SetAutoNaming(Standard_False);
  Handle(XCAFDoc_ColorTool) ctool =
      XCAFDoc_DocumentTool::ColorTool(wrapper.doc->Main());

  struct ColorAssemblyKey {
    Quantity_Color color;
    assembly_object obj;

    bool operator<(const ColorAssemblyKey &other) const {
      if (color.Red() != other.color.Red())
        return color.Red() < other.color.Red();
      if (color.Green() != other.color.Green())
        return color.Green() < other.color.Green();
      if (color.Blue() != other.color.Blue())
        return color.Blue() < other.color.Blue();

      return obj < other.obj;
    }
  };

  std::map<ColorAssemblyKey, TDF_Label> unique_objs;
  std::map<flywave::topo::assembly_object, topo::shape> compounds;

  std::function<TDF_Label(const std::shared_ptr<assembly> &, TDF_Label,
                          std::shared_ptr<Quantity_Color>)>
      _to_caf_func;

  _to_caf_func = [&](const std::shared_ptr<assembly> &el, TDF_Label ancestor,
                     std::shared_ptr<Quantity_Color> color) -> TDF_Label {
    TDF_Label subassy = tool->NewShape();
    set_doc_name(subassy, el->name(), tool);

    std::shared_ptr<Quantity_Color> current_color =
        el->has_color() ? std::make_shared<Quantity_Color>(el->color()) : color;

    if (el->has_obj()) {
      auto key0 = ColorAssemblyKey{.color = *current_color, .obj = el->obj()};
      auto key1 = el->obj();

      TDF_Label lab;
      if (unique_objs.find(key0) != unique_objs.end()) {
        lab = unique_objs[key0];
      } else {
        lab = tool->NewShape();
        shape c;
        if (compounds.find(key1) != compounds.end()) {
          c = compounds[key1].copy(true);
        } else {
          c = compound::make_compound(el->shapes());
          compounds[key1] = c;
        }

        tool->SetShape(lab, c.value());
        set_doc_name(lab, el->name() + "_part", tool);
        unique_objs[key0] = lab;

        if (coloredSTEP && current_color) {
          set_doc_color(lab, *current_color, ctool);
        }
      }

      tool->AddComponent(subassy, lab, TopLoc_Location());
    }

    if (!coloredSTEP && current_color) {
      set_doc_color(subassy, *current_color, ctool);
    }

    for (const auto &child : el->children()) {
      _to_caf_func(child, subassy, current_color);
    }

    TDF_Label rv;
    if (!ancestor.IsNull()) {
      tool->AddComponent(ancestor, subassy, el->location());
      rv = subassy;
    } else {
      rv = TDF_Label();
      tool->SetLocation(subassy, assy->location(), rv);
      set_doc_name(rv, assy->name(), tool);
    }

    return rv;
  };

  TDF_Label top = _to_caf_func(assy, TDF_Label(), nullptr);
  tool->UpdateAssemblies();

  return {top, wrapper.doc};
}

bool export_assembly(
    const std::shared_ptr<assembly> &assy, const std::string &path,
    const assembly_export_mode &mode = assembly_export_mode::defalut_,
    boost::optional<float> fuzzy_tol = boost::none) {
  try {
    int pcurves = 1;
    int precision_mode = 0;
    boost::optional<float> fuzzy_tol;
    bool glue = false;

    std::string assembly_name =
        assy->name().empty() ? generate_uuid() : assy->name();

    Handle(TDocStd_Document) doc;
    if (mode == assembly_export_mode::fuse) {
      if (fuzzy_tol) {
        std::tie(std::ignore, doc) = toFusedCAF(assy, glue, *fuzzy_tol);
      } else {
        std::tie(std::ignore, doc) = toFusedCAF(assy, glue);
      }
    } else {
      std::tie(std::ignore, doc) = toCAF(assy, true);
    }

    Handle(XSControl_WorkSession) session = new XSControl_WorkSession();
    STEPCAFControl_Writer writer(session, Standard_False);
    writer.SetColorMode(Standard_True);
    writer.SetLayerMode(Standard_True);
    writer.SetNameMode(Standard_True);

    Interface_Static::SetIVal("write.surfacecurve.mode", pcurves);
    Interface_Static::SetIVal("write.precision.mode", precision_mode);

    if (!writer.Transfer(doc, STEPControl_AsIs)) {
      return false;
    }

    IFSelect_ReturnStatus status = writer.Write(path.c_str());

    return status == IFSelect_RetDone;
  } catch (const std::exception &e) {
    return false;
  }
}

const std::string PATH_DELIM = "/";
const auto name_char = x3::alnum | x3::char_('_');
const auto tag_char = x3::alnum | x3::char_('_');

struct name_rule : x3::parser<name_rule> {
  using attribute_type = std::string;

  template <typename Iterator, typename Context, typename Attribute>
  bool parse(Iterator &first, Iterator const &last, Context const &context,
             x3::unused_type, Attribute &attr) const {
    std::string result;
    bool first_segment = true;

    while (first != last) {
      std::string segment;
      auto seg_parser = +name_char;
      if (!seg_parser.parse(first, last, context, x3::unused, segment))
        break;

      if (!first_segment)
        result += PATH_DELIM;
      result += segment;
      first_segment = false;

      if (first == last || *first != PATH_DELIM[0])
        break;
      ++first;
    }

    if (result.empty())
      return false;
    attr = result;
    return true;
  }
};

const name_rule name = {};
const auto tag = x3::rule<class tag_rule, std::string>{} = +tag_char;

const auto selector_type = x3::rule<class stype_rule, std::string>{} =
    x3::lit("solids") | "faces" | "edges" | "vertices";

const auto selector = x3::rule<class sel_rule, std::string>{} = +x3::char_;

const auto grammar_def = name >> -('?' >> tag) >>
                         -('@' >> selector_type >> '@' >> selector);
} // namespace detail

bool parse(const std::string &input, parse_result &result) {
  using iterator_type = std::string::const_iterator;

  iterator_type iter = input.begin();
  iterator_type end = input.end();

  return x3::parse(iter, end, detail::grammar_def, result) && iter == end;
}

std::shared_ptr<assembly>
assembly::create(assembly_object obj, std::shared_ptr<topo_location> loc,
                 const std::string &name, std::shared_ptr<Quantity_Color> color,
                 const std::unordered_map<std::string, boost::any> &metadata) {
  auto ptr =
      std::shared_ptr<assembly>(new assembly(obj, loc, name, color, metadata));
  ptr->objects_[ptr->name_] = ptr;
  return ptr;
}

assembly::assembly(assembly_object obj, std::shared_ptr<topo_location> loc,
                   const std::string &name,
                   std::shared_ptr<Quantity_Color> color,
                   const std::unordered_map<std::string, boost::any> &metadata)
    : obj_(std::move(obj)),
      loc_(loc ? std::move(loc) : std::make_shared<topo_location>()),
      name_(name.empty() ? detail::generate_uuid() : name),
      color_(std::move(color)), metadata_(metadata), parent_(), children_(),
      objects_(), constraints_(), solve_result_(boost::none) {

  objects_[name_] = shared_from_this();
  struct validator : public boost::static_visitor<void> {
    void operator()(const std::shared_ptr<workplane> &wp) const {
      if (!wp)
        throw std::invalid_argument("Workplane object is null");
    }

    void operator()(const shape &sh) const {
      if (!sh)
        throw std::invalid_argument("Shape object is null");
    }

    void operator()(boost::blank) const {}
  };

  boost::apply_visitor(validator(), obj_);

  if (obj_.which() != -1) {
    children_.reserve(4);
  }
}

assembly::assembly(assembly &&o) noexcept {
  loc_ = std::move(o.loc_);
  name_ = std::move(o.name_);
  color_ = std::move(o.color_);
  metadata_ = std::move(o.metadata_);
  obj_ = std::move(o.obj_);
  parent_ = std::move(o.parent_);
  children_ = std::move(o.children_);
  objects_ = std::move(o.objects_);
  constraints_ = std::move(o.constraints_);
  solve_result_ = std::move(o.solve_result_);
  o.loc_.reset();
  o.name_.clear();
  o.color_.reset();
  o.metadata_.clear();
  o.obj_ = boost::blank();
  o.parent_.reset();
  o.children_.clear();
  o.objects_.clear();
  o.constraints_.clear();
  o.solve_result_.reset();
}

assembly &assembly::operator=(assembly &&o) noexcept {
  if (this != &o) {
    loc_ = std::move(o.loc_);
    name_ = std::move(o.name_);
    color_ = std::move(o.color_);
    metadata_ = std::move(o.metadata_);
    obj_ = std::move(o.obj_);
    parent_ = std::move(o.parent_);
    children_ = std::move(o.children_);
    objects_ = std::move(o.objects_);
    constraints_ = std::move(o.constraints_);
    solve_result_ = std::move(o.solve_result_);
    o.loc_.reset();
    o.name_.clear();
    o.color_.reset();
    o.metadata_.clear();
    o.obj_ = boost::blank();
    o.parent_.reset();
    o.children_.clear();
    o.objects_.clear();
    o.constraints_.clear();
    o.solve_result_.reset();
  }
  return *this;
}

std::shared_ptr<assembly> assembly::copy() const {
  auto new_assembly = assembly::create(
      obj_, loc_ ? std::make_shared<topo_location>(*loc_) : nullptr, name_,
      color_ ? std::make_shared<Quantity_Color>(*color_) : nullptr, metadata_);

  for (const auto &child : children_) {
    auto child_copy = child->copy();
    child_copy->parent_ = new_assembly;

    new_assembly->children_.push_back(child_copy);
    new_assembly->objects_[child_copy->name_] = child_copy;

    auto child_objects = child_copy->flatten();

    for (const auto &pair : child_objects) {
      new_assembly->objects_[pair.first] = pair.second;
    }
  }

  for (const auto &constraint : constraints_) {
    new_assembly->constraints_.push_back(constraint);
  }

  if (solve_result_) {
    new_assembly->solve_result_ = *solve_result_;
  }

  return new_assembly;
}

assembly &assembly::add(std::shared_ptr<assembly> subAssembly,
                        std::shared_ptr<topo_location> loc,
                        const std::string &name,
                        std::shared_ptr<Quantity_Color> color) {
  try {
    auto current = shared_from_this();
    while (current) {
      if (current == subAssembly) {
        throw std::invalid_argument("Circular dependency detected");
      }
      current = current->parent_.lock();
    }
    if (!subAssembly) {
      throw std::invalid_argument("Cannot add null assembly");
    }

    const std::string &finalName = name.empty() ? subAssembly->name_ : name;
    if (objects_.find(finalName) != objects_.end()) {
      throw std::invalid_argument("Duplicate assembly name: " + finalName);
    }

    auto newAssembly = subAssembly->copy();

    newAssembly->loc_ = loc ? loc : subAssembly->loc_;
    newAssembly->name_ = finalName;
    newAssembly->color_ = color ? color : subAssembly->color_;
    newAssembly->parent_ = shared_from_this();

    children_.push_back(newAssembly);
    objects_[finalName] = newAssembly;

    auto childObjects = newAssembly->flatten();
    for (const auto &pair : childObjects) {
      objects_[pair.first] = pair.second;
    }
  } catch (const std::exception &e) {
    set_error(e.what());
  } catch (...) {
    set_error("Unknown error occurred");
  }

  return *this;
}

assembly &
assembly::add(assembly_object obj, std::shared_ptr<topo_location> loc,
              const std::string &name, std::shared_ptr<Quantity_Color> color,
              const std::unordered_map<std::string, boost::any> &metadata) {
  auto newAssembly = assembly::create(
      std::move(obj), loc ? loc : std::make_shared<topo_location>(),
      name.empty() ? detail::generate_uuid() : name, color, metadata);

  return add(newAssembly);
}

assembly &assembly::remove(const std::string &name) {
  try {
    auto it = objects_.find(name);
    if (it == objects_.end()) {
      throw std::invalid_argument("No object with name '" + name +
                                  "' found in the assembly");
    }

    auto toRemove = it->second;

    if (auto parent = toRemove->parent_.lock()) {
      auto &children = parent->children_;
      children.erase(std::remove(children.begin(), children.end(), toRemove),
                     children.end());
    }

    objects_.erase(it);

    auto descendants = toRemove->flatten();

    for (const auto &pair : descendants) {
      objects_.erase(pair.first);
    }

    toRemove->parent_.reset();
  } catch (const std::exception &e) {
    set_error(e.what());
  } catch (...) {
    set_error("Unknown error occurred");
  }
  return *this;
}

std::pair<std::string, shape> assembly::query(const std::string &q) const {
  parse_result rs;
  try {
    bool ok = parse(q, rs);

    auto obj_it = objects_.find(rs.name);
    if (obj_it == objects_.end()) {
      throw std::invalid_argument("Object not found: " + rs.name);
    }

    auto obj = obj_it->second->obj_;
    std::shared_ptr<workplane> tmp_wp = nullptr;
    shape_object result;

    if (auto *wp = boost::get<std::shared_ptr<workplane>>(&obj)) {
      if (!rs.tag.empty()) {
        tmp_wp = (*wp)->get_tagged(rs.tag);
      } else {
        tmp_wp = std::make_shared<workplane>();
        tmp_wp->add(**wp);
      }
    } else if (auto *sh = boost::get<shape>(&obj)) {
      tmp_wp = std::make_shared<workplane>();
      tmp_wp->add(*sh);
    } else if (!boost::get<boost::blank>(&obj)) {
      throw std::invalid_argument("Invalid object type in assembly");
    } else {
      throw std::invalid_argument("Workplane or Shape required for query");
    }

    if (!tmp_wp) {
      throw std::invalid_argument("Workplane not found");
    }

    if (!rs.selector_kind.empty()) {
      if (rs.selector_kind == "faces") {
        result = tmp_wp->faces(rs.selector)->val();
      } else if (rs.selector_kind == "edges") {
        result = tmp_wp->edges(rs.selector)->val();
      } else if (rs.selector_kind == "vertices") {
        result = tmp_wp->vertices(rs.selector)->val();
      } else if (rs.selector_kind == "solids") {
        result = tmp_wp->solids(rs.selector)->val();
      } else {
        throw std::invalid_argument("Invalid selector kind: " +
                                    rs.selector_kind);
      }
    } else {
      result = tmp_wp->val();
    }

    if (auto *sh = boost::get<shape>(&result)) {
      return {rs.name, *sh};
    }
  } catch (const std::exception &e) {
    set_error(e.what());
  } catch (...) {
    set_error("Unknown error occurred");
  }
  return {rs.name, shape()};
}

assembly &assembly::constrain(const std::string &q1, const std::string &q2,
                              constraint_kind kind,
                              const constraint_param &param) {
  std::string id1, id2;
  flywave::topo::shape s1, s2;

  std::tie(id1, s1) = query(q1);
  std::tie(id2, s2) = query(q2);
  return add_constraint_impl(id1, &s1, id2, &s2, kind, param, true);
}

assembly &assembly::constrain(const std::string &q1, constraint_kind kind,
                              const constraint_param &param) {
  std::string id1;
  flywave::topo::shape s1;

  std::tie(id1, s1) = query(q1);
  return add_constraint_impl(id1, &s1, "", nullptr,
                             static_cast<constraint_kind>(kind), param, false);
}

assembly &assembly::constrain(const std::string &id1, const shape &s1,
                              const std::string &id2, const shape &s2,
                              constraint_kind kind,
                              const constraint_param &param) {
  return add_constraint_impl(id1, &s1, id2, &s2, kind, param, true);
}

assembly &assembly::constrain(const std::string &id1, const shape &s1,
                              constraint_kind kind,
                              const constraint_param &param) {
  return add_constraint_impl(id1, &s1, "", nullptr,
                             static_cast<constraint_kind>(kind), param, false);
}

assembly &assembly::add_constraint_impl(const std::string &id1, const shape *s1,
                                        const std::string &id2, const shape *s2,
                                        constraint_kind kind,
                                        const constraint_param &param,
                                        bool isBinary) {
  try {
    if (isBinary != is_binary(kind)) {
      throw std::invalid_argument(isBinary ? "Expected binary constraint type"
                                           : "Expected unary constraint type");
    }

    if (!s1) {
      throw std::invalid_argument("First shape cannot be null");
    }

    if (!isBinary) {
      topo_location loc1;
      std::string topId1;
      std::tie(loc1, topId1) = sub_location(id1);
      constraints_.push_back(constraint_spec(
          std::vector<std::string>{topId1}, std::vector<shape>{*s1},
          std::vector<topo_location>{loc1}, kind, param));
    } else {
      if (!s2) {
        throw std::invalid_argument(
            "Second shape cannot be null for binary constraint");
      }

      topo_location loc1, loc2;
      std::string topId1, topId2;
      std::tie(loc1, topId1) = sub_location(id1);
      std::tie(loc2, topId2) = sub_location(id2);

      constraints_.push_back(
          constraint_spec(std::vector<std::string>{topId1, topId2},
                          std::vector<shape>{*s1, *s2},
                          std::vector<topo_location>{loc1, loc2}, kind, param));
    }
  } catch (const std::exception &e) {
    set_error(e.what());
  } catch (...) {
    set_error("Unknown error occurred");
  }
  return *this;
}

assembly &assembly::solve(int verbosity) {
  try {
    std::lock_guard<std::mutex> lock(solve_mutex_);
    if (constraints_.empty()) {
      throw std::runtime_error("At least one constraint required");
    }

    std::unordered_map<std::string, size_t> ents;
    std::vector<size_t> locked;
    size_t index = 0;

    for (const auto &c : constraints_) {
      for (const auto &name : c.objects) {
        if (ents.find(name) == ents.end()) {
          ents[name] = index++;
        }
        if ((c.kind == constraint_kind::Fixed || name == name_) &&
            std::find(locked.begin(), locked.end(), ents[name]) ==
                locked.end()) {
          locked.push_back(ents[name]);
        }
      }
    }

    if (locked.empty()) {
      locked.push_back(0);
    }

    std::vector<gp_Trsf> locs(ents.size());
    for (const auto &entry : ents) {
      locs[entry.second] = *objects_.find(entry.first)->second->loc_;
    }

    std::vector<assembly_constraint> constraint_pods;
    constraint_pods.reserve(constraints_.size());
    for (const auto &c : constraints_) {
      auto pods = c.to_pods();
      for (const auto &pod : pods) {
        constraint_pods.push_back(pod);
      }
    }

    double scale = to_compound().bbox().diagonal_length();
    constraint_solver solver(locs, constraint_pods, locked, scale);

    auto solve_result = solver.solve(verbosity);
    solve_result_ = solve_result.second;

    auto root_loc_inv = std::make_shared<topo_location>();
    if (obj_.which() != 2) {
      for (const auto &entry : ents) {
        if (entry.first == name_) {
          *root_loc_inv = solve_result.first[entry.second].Inverted();
          break;
        }
      }
    }

    for (const auto &entry : ents) {
      if (entry.first != name_) {
        objects_.find(entry.first)->second->loc_ =
            std::make_shared<topo_location>(*root_loc_inv *
                                            solve_result.first[entry.second]);
      }
    }
  } catch (const std::exception &e) {
    set_error(e.what());
  } catch (...) {
    set_error("Unknown error occurred");
  }
  return *this;
}

assembly &assembly::export_to(const std::string &path,
                              const assembly_export_mode &mode) {
  try {
    detail::export_assembly(this->shared_from_this(), path, mode);
  } catch (const std::exception &e) {
    set_error(e.what());
  } catch (...) {
    set_error("Unknown error occurred");
  }
  return *this;
}

std::vector<shape> assembly::shapes() const {
  std::vector<shape> result;

  if (auto sh = boost::get<shape>(&obj_)) {
    result.push_back(*sh);
  } else if (auto wp = boost::get<std::shared_ptr<workplane>>(&obj_)) {
    for (const auto &val : (*wp)->vals()) {
      if (auto shape_val = boost::get<shape>(&val)) {
        result.push_back(*shape_val);
      }
    }
  }

  return result;
}

void assembly::traverse(
    std::function<void(const std::string &, const assembly &)> callback) const {
  for (const auto &child : children_) {
    child->traverse(callback);
  }
  callback(name_, *this);
}

std::unordered_map<std::string, std::shared_ptr<assembly>> assembly::flatten() {
  return flatten({});
}

std::unordered_map<std::string, std::shared_ptr<assembly>>
assembly::flatten(const std::vector<std::string> &parents) {
  std::unordered_map<std::string, std::shared_ptr<assembly>> result;

  std::vector<std::string> current_path = parents;
  current_path.push_back(name_);

  for (const auto &child : children_) {
    auto child_flattened = child->flatten(current_path);
    result.insert(child_flattened.begin(), child_flattened.end());
  }

  std::string path;
  for (size_t i = 0; i < current_path.size(); ++i) {
    if (i != 0)
      path += "/";
    path += current_path[i];
  }
  result[path] = shared_from_this();

  return result;
}

std::vector<assembly_element> assembly::get_elements() const {
  return _get_elements();
}

std::vector<assembly_element>
assembly::_get_elements(std::shared_ptr<topo_location> loc,
                        const std::string &name,
                        std::shared_ptr<Quantity_Color> color) const {
  std::vector<assembly_element> elements;

  std::function<void(const std::shared_ptr<assembly> &,
                     std::shared_ptr<topo_location>, const std::string &,
                     std::shared_ptr<Quantity_Color>)>
      collect_elements;

  collect_elements = [&](const std::shared_ptr<assembly> &assy,
                         std::shared_ptr<topo_location> current_loc,
                         const std::string &current_name,
                         std::shared_ptr<Quantity_Color> current_color) {
    std::string full_name =
        current_name.empty() ? assy->name_ : current_name + "/" + assy->name_;

    auto new_loc =
        current_loc
            ? std::make_shared<topo_location>(*current_loc * *assy->loc_)
            : assy->loc_;

    auto new_color = assy->color_ ? assy->color_ : current_color;

    if (assy->obj_.which() != 2) {
      compound shape_obj;

      if (auto sh = boost::get<shape>(&assy->obj_)) {
        shape_obj = *sh->cast<topo::compound>();
      } else if (auto wp =
                     boost::get<std::shared_ptr<workplane>>(&assy->obj_)) {
        std::vector<shape> shapes;
        for (const auto &val : (*wp)->vals()) {
          if (auto s = boost::get<shape>(&val)) {
            shapes.push_back(*s);
          }
        }
        shape_obj = compound::make_compound(shapes);
      }

      if (shape_obj) {
        elements.push_back(assembly_element{.shp = shape_obj,
                                            .name = full_name,
                                            .location = *new_loc,
                                            .color = new_color});
      }
    }

    for (const auto &child : assy->children_) {
      collect_elements(child, new_loc, full_name, new_color);
    }
  };

  collect_elements(std::const_pointer_cast<assembly>(this->shared_from_this()),
                   loc, name, color);

  return elements;
}

compound assembly::to_compound() const {
  auto shapes = this->shapes();

  for (const auto &child : children_) {
    shapes.push_back(child->to_compound());
  }

  auto result = compound::make_compound(shapes);
  if (loc_) {
    result.transform(*loc_);
  }

  return result;
}

std::pair<topo_location, std::string>
assembly::sub_location(const std::string &name) const {
  auto it = objects_.find(name);
  if (it == objects_.end()) {
    throw std::invalid_argument("Object not found: " + name);
  }

  auto obj = it->second;
  topo_location result_loc;
  std::string top_name = name;

  bool is_child =
      std::find(children_.begin(), children_.end(), obj) != children_.end();
  if (!is_child && obj.get() != this) {
    std::vector<topo_location> loc_chain;
    auto current = obj;

    while (auto parent = current->parent_.lock()) {
      if (parent.get() == this)
        break;

      loc_chain.push_back(*current->loc_);
      current = parent;
      top_name = current->name_;
    }

    for (auto it = loc_chain.rbegin(); it != loc_chain.rend(); ++it) {
      result_loc = (*it) * result_loc;
    }
  }

  return {result_loc, top_name};
}

bool assembly::has_error() const { return (bool)(error_); }

void assembly::set_error(const std::string &error) const { error_ = error; }

const std::string &assembly::error() const {
  if (error_) {
    return *error_;
  }
  static std::string empty;
  return empty;
}

void assembly::clear_error() { error_.reset(); }

} // namespace topo
} // namespace flywave
