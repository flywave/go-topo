#include "workplane.hh"
#include "shape_geom_type.hh"

#include <unordered_set>

namespace flywave {
namespace topo {
namespace {

boost::optional<shape> select_shape(const shape_object &object) {
  if (auto s = boost::get<shape>(&object)) {
    return *s;
  }
  return boost::none;
}

std::vector<shape> select_shapes(const std::vector<shape_object> &objects) {
  std::vector<shape> result;
  result.reserve(objects.size());
  for (const auto &obj : objects) {
    if (auto s = boost::get<shape>(&obj)) {
      result.push_back(*s);
    }
  }
  return result;
}
} // namespace

workplane::workplane()
    : _plane(nullptr), _parent(), _ctx(std::make_shared<context>()) {}

workplane::workplane(topo_plane plane, topo_vector *origin, shape_object obj)
    : _plane(std::make_shared<topo_plane>(plane)), _parent(),
      _ctx(std::make_shared<context>()),
      _objects(obj.empty() ? std::vector<shape_object>{}
                           : std::vector<shape_object>{obj}) {}

workplane::workplane(const std::string &planeName, topo_vector *origin,
                     shape_object obj)
    : _parent(), _ctx(std::make_shared<context>()) {
  auto plane =
      topo_plane::named(planeName, origin ? *origin : topo_vector(0, 0, 0));
  _plane = std::make_shared<topo_plane>(std::move(plane));
  if (!obj.empty()) {
    _objects.push_back(obj);
  }
}

workplane::workplane(workplane &&o) noexcept {
  _plane = std::move(o._plane);
  _objects = std::move(o._objects);
  _parent = std::move(o._parent);
  _ctx = std::move(o._ctx);
  _tag = std::move(o._tag);
  o._plane.reset();
  o._objects.clear();
  o._parent.reset();
  o._ctx.reset();
  o._tag = boost::none;
}

workplane &workplane::operator=(workplane &&o) noexcept {
  if (this != &o) {
    _plane = std::move(o._plane);
    _objects = std::move(o._objects);
    _parent = std::move(o._parent);
    _ctx = std::move(o._ctx);
    _tag = std::move(o._tag);
    o._plane.reset();
    o._objects.clear();
    o._parent.reset();
    o._ctx.reset();
    o._tag = boost::none;
  }
  return *this;
}

workplane &workplane::tag(const std::string &name) {
  _tag = name;
  _ctx->tags()[name] = shared_from_this();
  return *this;
}

std::vector<shape>
workplane::collect_property(const shape_object_type &propName) const {
  std::vector<shape> result;
  std::unordered_map<shape, bool> seen; // used as an ordered set

  for (auto &obj : _objects) {
    if (auto shp = boost::get<shape>(&obj)) {
      if (propName == shape_object_type::solid) {
        if (shp->shape_type() == TopAbs_COMPOUND) {
          for (auto &k : shp->compounds()) {
            if (seen.find(k) == seen.end()) {
              seen[k] = true;
              result.push_back(k);
            }
          }
        }
      } else if (propName == shape_object_type::compound) {
        for (auto &k : shp->compounds()) {
          if (seen.find(k) == seen.end()) {
            seen[k] = true;
            result.push_back(k);
          }
        }
      } else if (propName == shape_object_type::face) {
        for (auto &k : shp->faces()) {
          if (seen.find(k) == seen.end()) {
            seen[k] = true;
            result.push_back(k);
          }
        }
      } else if (propName == shape_object_type::edge) {
        for (auto &k : shp->edges()) {
          if (seen.find(k) == seen.end()) {
            seen[k] = true;
            result.push_back(k);
          }
        }
      } else if (propName == shape_object_type::vertex) {
        for (auto &k : shp->vertices()) {
          if (seen.find(k) == seen.end()) {
            seen[k] = true;
            result.push_back(k);
          }
        }
      } else if (propName == shape_object_type::wire) {
        for (auto &k : shp->wires()) {
          if (seen.find(k) == seen.end()) {
            seen[k] = true;
            result.push_back(k);
          }
        }
      } else if (propName == shape_object_type::solid) {
        for (auto &k : shp->solids()) {
          if (seen.find(k) == seen.end()) {
            seen[k] = true;
            result.push_back(k);
          }
        }
      } else if (propName == shape_object_type::comp_solid) {
        for (auto &k : shp->comp_solids()) {
          if (seen.find(k) == seen.end()) {
            seen[k] = true;
            result.push_back(k);
          }
        }
      }
    }
  }

  return result;
}

std::shared_ptr<workplane> workplane::split(bool keepTop, bool keepBottom) {
  if (!keepTop && !keepBottom) {
    throw std::runtime_error("You have to keep at least one half");
  }

  solid s = find_solid();
  double maxDim = s.bbox().diagonal_length() * 10.0;

  auto topCutBox = this->_rect(maxDim, maxDim)->_extrude(maxDim);
  auto bottomCutBox = this->_rect(maxDim, maxDim)->_extrude(-maxDim);

  auto top = *topo::cut(s, {bottomCutBox});
  auto bottom = *topo::cut(s, {topCutBox});

  std::vector<shape_object> rv;
  if (keepTop && keepBottom) {
    rv = std::vector<shape_object>({top, bottom});
  } else {
    if (keepTop) {
      rv = std::vector<shape_object>({top});
    } else {
      rv = std::vector<shape_object>({bottom});
    }
  }

  return this->new_object(rv);
}

std::shared_ptr<workplane> workplane::split(const shape &splitter) {
  solid s = find_solid();
  std::vector<shape_object> rv = {*topo::split(s, splitter)};
  return this->new_object(rv);
}

std::shared_ptr<workplane> workplane::split(const workplane &splitter) {
  solid s = find_solid();
  std::vector<shape> tools;
  for (const auto &obj : splitter.vals()) {
    if (const shape *sh = boost::get<shape>(&obj)) {
      tools.push_back(*sh);
    }
  }

  std::vector<shape_object> rv = {*topo::split(s, tools)};
  this->merge_tags(splitter);
  return this->new_object(rv);
}

std::vector<std::shared_ptr<workplane>> workplane::all() {
  std::vector<std::shared_ptr<workplane>> result;
  for (const auto &obj : _objects) {
    result.push_back(this->new_object({obj}));
  }
  return result;
}

size_t workplane::size() const { return _objects.size(); }

bool workplane::has_parent() const { return !_parent.expired(); }

std::shared_ptr<workplane> workplane::parent() const { return _parent.lock(); }

std::vector<shape_object> workplane::vals() const { return _objects; }

bool workplane::has_error() const { return _ctx->has_error(); }

const std::string &workplane::error() const { return _ctx->error(); }

std::shared_ptr<context> workplane::ctx() const { return _ctx; }

workplane &workplane::add(const workplane &other) {
  _objects.insert(_objects.end(), other._objects.begin(), other._objects.end());
  merge_tags(other);
  return *this;
}

workplane &workplane::add(const shape_object &obj) {
  _objects.push_back(obj);
  return *this;
}

workplane &workplane::add(const std::vector<shape_object> &objs) {
  _objects.insert(_objects.end(), objs.begin(), objs.end());
  return *this;
}

shape_object workplane::val() const {
  if (!_objects.empty()) {
    return _objects[0];
  }
  return _plane ? _plane->origin() : topo_vector(0, 0, 0);
}

std::shared_ptr<workplane>
workplane::get_tagged(const std::string &name) const {
  auto it = _ctx->tags().find(name);
  if (it == _ctx->tags().end()) {
    throw std::runtime_error("No Workplane object named " + name + " in chain");
  }
  return it->second;
}

workplane &workplane::merge_tags(const workplane &other) {
  if (_ctx != other._ctx) {
    _ctx->tags().insert(other._ctx->tags().begin(), other._ctx->tags().end());
  }
  return *this;
}

shape workplane::value() const {
  shape_object v = val();

  if (const auto *sk = boost::get<std::shared_ptr<topo::sketch>>(&v)) {
    return *(*sk)->faces_;
  } else if (const shape *sh = boost::get<shape>(&v)) {
    return sh->value();
  } else {
    throw std::runtime_error("Unsupported object type for toOCC conversion");
  }
}

std::shared_ptr<workplane> workplane::create(double offset, bool invert,
                                             const center_option &centerOption,
                                             topo_vector *origin) {
  static const std::unordered_set<center_option> validOptions = {
      center_option::CenterOfMass, center_option::ProjectedOrigin,
      center_option::CenterOfBoundBox};
  if (validOptions.find(centerOption) == validOptions.end()) {
    throw std::runtime_error("Undefined centerOption value provided.");
  }
  gp_Pnt center_;
  gp_Dir xDir;
  gp_Vec normal;

  if (_objects.size() > 1) {
    std::vector<face> faces;
    for (auto &obj : _objects) {
      if (auto f = boost::get<shape>(&obj)) {
        if (f->shape_type() == TopAbs_FACE) {
          faces.push_back(*f->cast<topo::face>());
        }
      }
    }

    if (faces.size() != _objects.size()) {
      throw std::runtime_error(
          "If multiple objects selected, they all must be planar faces.");
    }

    if (!are_faces_coplanar(faces)) {
      throw std::runtime_error("Selected faces must be co-planar.");
    }

    if (centerOption == center_option::CenterOfMass ||
        centerOption == center_option::ProjectedOrigin) {
      center_ = topo::combined_center(select_shapes(_objects));
    } else if (centerOption == center_option::CenterOfBoundBox) {
      center_ = topo::combined_center_of_bound_box(select_shapes(_objects));
    }

    normal = faces[0].normal_at();
    xDir = compute_x_dir(normal);
  } else {
    shape_object obj = val();

    if (auto shp = boost::get<shape>(&obj)) {
      if (shp->shape_type() == TopAbs_FACE) {
        auto f = *shp->cast<topo::face>();
        if (centerOption == center_option::CenterOfMass ||
            centerOption == center_option::ProjectedOrigin) {
          center_ = f.center();
        } else if (centerOption == center_option::CenterOfBoundBox) {
          center_ = f.centre_of_mass();
        }
        normal = f.normal_at(&center_);
        xDir = compute_x_dir(normal);
      } else {
        if (centerOption == center_option::CenterOfMass ||
            centerOption == center_option::ProjectedOrigin) {
          center_ = shp->centre_of_mass();
        } else if (centerOption == center_option::CenterOfBoundBox) {
          center_ = shp->center_of_bound_box();
        }
        shape_object parentVal =
            has_parent() ? parent()->val() : shape_object();
        if (auto parentFace = boost::get<shape>(&parentVal)) {
          if (parentFace->shape_type() == TopAbs_FACE) {
            normal = parentFace->cast<topo::face>()->normal_at(&center_);
            xDir = compute_x_dir(normal);
          }
        } else {
          normal = _plane->z_dir();
          xDir = _plane->x_dir();
        }
      }
    } else if (auto vec = boost::get<topo_vector>(&obj)) {
      if (centerOption == center_option::CenterOfMass ||
          centerOption == center_option::ProjectedOrigin) {
        center_ = *vec;
      } else if (centerOption == center_option::CenterOfBoundBox) {
        center_ = *vec;
      }
      shape_object parentVal = has_parent() ? parent()->val() : shape_object();
      if (auto parentFace = boost::get<shape>(&parentVal)) {
        if (parentFace->shape_type() == TopAbs_FACE) {
          normal = parentFace->cast<topo::face>()->normal_at(&center_);
          xDir = compute_x_dir(normal);
        }
      } else {
        normal = _plane->z_dir();
        xDir = _plane->x_dir();
      }
    } else {
      throw std::runtime_error(
          "Needs a face or a vertex or point on a work plane");
    }
  }

  if (centerOption == center_option::ProjectedOrigin) {
    topo_vector orig = origin ? *origin : _plane->origin();
    center_ = orig.project_to_plane(topo_plane(center_, xDir, normal));
  }

  if (invert) {
    normal = normal.Multiplied(-1.0);
  }

  gp_Vec offsetVector = normal.Normalized().Multiplied(offset);
  gp_Pnt offsetCenter = center_.Translated(offsetVector);

  topo_plane newPlane(offsetCenter, xDir, normal);
  auto s = std::make_shared<workplane>(newPlane);
  s->_parent = shared_from_this();
  s->_ctx = _ctx;

  return s;
}

bool workplane::are_faces_coplanar(const std::vector<face> &faces) const {
  if (faces.empty())
    return true;

  topo_vector p0 = faces[0].center();
  topo_vector n0 = faces[0].normal_at();

  for (size_t i = 1; i < faces.size(); ++i) {
    gp_Pnt p1 = faces[i].center();
    gp_Vec n1 = faces[i].normal_at();

    if (!n0.is_equal(n1, _ctx->tolerance())) {
      return false;
    }

    if (std::abs(n0.dot(p0 - p1)) > _ctx->tolerance()) {
      return false;
    }
  }
  return true;
}

gp_Vec workplane::compute_x_dir(const gp_Vec &normal) const {
  gp_Vec xd = gp_Vec(0, 0, 1).Crossed(normal);
  if (xd.Magnitude() < _ctx->tolerance()) {
    xd = gp_Vec(1, 0, 0);
  }
  return xd;
}

std::shared_ptr<workplane> workplane::copy_workplane(const workplane &obj) {
  auto out = std::make_shared<workplane>(*obj._plane);
  out->_parent = shared_from_this();
  out->_ctx = _ctx;
  return out;
}

std::shared_ptr<workplane> workplane::from_tagged(const std::string &name) {
  auto tagged = get_tagged(name);
  return copy_workplane(*tagged);
}

std::shared_ptr<workplane> workplane::first() {
  if (_objects.empty()) {
    throw std::runtime_error("No objects in stack");
  }
  return new_object({_objects.front()});
}

std::shared_ptr<workplane> workplane::item(size_t i) {
  if (i >= _objects.size()) {
    throw std::out_of_range("Index out of range");
  }
  return new_object({_objects[i]});
}

std::shared_ptr<workplane> workplane::last() {
  if (_objects.empty()) {
    throw std::runtime_error("No objects in stack");
  }
  return new_object({_objects.back()});
}

std::shared_ptr<workplane> workplane::end(int n) {
  std::shared_ptr<workplane> rv = nullptr;
  for (int i = 0; i < n; ++i) {
    if (rv->has_parent()) {
      rv = rv->parent();
    } else {
      throw std::runtime_error("Cannot End the chain-- no parents!");
    }
  }
  if (!rv) {
    return this->shared_from_this();
  }
  return rv;
}

struct shape_type_visitor : public boost::static_visitor<shape_object_type> {
  template <typename T> shape_object_type operator()(const T &arg) const {
    return static_cast<shape_object_type>(arg.shape_type());
  }

  shape_object_type operator()(const std::shared_ptr<sketch> &) const {
    return shape_object_type::sketch;
  }
  shape_object_type operator()(const topo_vector &) const {
    return shape_object_type::vector;
  }
  shape_object_type operator()(const topo_location &) const {
    return shape_object_type::location;
  }
  shape_object_type operator()(const boost::blank &) const {
    return shape_object_type::blank;
  }
};

shape_object_type workplane::get_shape_object_type(const shape_object &obj) {
  return boost::apply_visitor(shape_type_visitor(), obj);
}

shape workplane::find_type(const std::vector<shape_object_type> &types,
                           bool searchStack, bool searchParents) const {
  std::vector<shape> rv;

  if (searchStack) {
    for (auto &obj : _objects) {
      bool matchesType = false;
      shape_object_type objType =
          boost::apply_visitor(shape_type_visitor(), obj);

      for (const auto &type : types) {
        if (objType == type) {
          matchesType = true;
          break;
        }
      }

      if (matchesType) {
        if (auto shp = boost::get<shape>(&obj)) {
          rv.push_back(*shp);
        } else if (auto shp = boost::get<std::shared_ptr<topo::sketch>>(&obj)) {
          rv.push_back(*(*shp)->faces_);
        }
      } else if (objType == shape_object_type::compound &&
                 std::find(types.begin(), types.end(),
                           shape_object_type::solid) != types.end()) {
        if (auto c = boost::get<shape>(&obj)) {
          if (c->shape_type() == TopAbs_COMPOUND) {
            auto solids = c->get_shapes(TopAbs_SOLID);
            rv.insert(rv.end(), solids.begin(), solids.end());
          }
        }
      } else if (objType == shape_object_type::compound) {
        if (auto cs = boost::get<shape>(&obj)) {
          if (cs->shape_type() == TopAbs_COMPOUND) {
            for (auto &el : cs->children()) {
              TopAbs_ShapeEnum elType = el.shape_type();
              for (const auto &type : types) {
                if (static_cast<shape_object_type>(elType) == type) {
                  rv.push_back(el);
                  break;
                }
              }
            }
          }
        }
      }
    }

    if (!rv.empty()) {
      if (std::find(types.begin(), types.end(), shape_object_type::solid) !=
          types.end()) {
        return compound::make_compound(rv);
      } else {
        return rv.front();
      }
    }
  }

  if (searchParents && has_parent()) {
    return parent()->find_type(types, true, true);
  }

  return shape{}; // return empty variant
}

solid workplane::find_solid(bool searchStack, bool searchParents) const {
  auto s = find_type({shape_object_type::solid}, searchStack, searchParents);

  if (!s) {
    std::string message = searchStack ? "on the stack or " : "";
    throw std::runtime_error("Cannot find a solid " + message +
                             "in the parent chain");
  }

  if (s.shape_type() == TopAbs_SOLID) {
    return *s.cast<solid>();
  } else if (s.shape_type() == TopAbs_COMPOUND) {
    auto solids = s.get_shapes(TopAbs_SOLID);
    if (!solids.empty()) {
      return *solids.front().cast<solid>();
    }
  }

  throw std::runtime_error("Found object is not a valid solid");
}

std::shared_ptr<workplane> workplane::select_objects(
    const shape_object_type &objType,
    const boost::optional<boost::variant<selector_ptr, std::string>> &selector,
    const boost::optional<std::string> &tag) const {
  const workplane &cq_obj = tag ? *get_tagged(*tag) : *this;
  auto toReturn = cq_obj.collect_property(objType);
  return new_shape_object(filter(toReturn, selector));
}

std::vector<shape> workplane::filter(
    const std::vector<shape> &objs,
    const boost::optional<boost::variant<selector_ptr, std::string>> &s) const {
  if (s) {
    std::shared_ptr<flywave::topo::selector> selectorObj;
    if (auto str = boost::get<std::string>(&*s)) {
      selectorObj = std::make_shared<string_syntax_selector>(*str);
    } else {
      selectorObj = boost::get<selector_ptr>(*s);
    }
    return selectorObj->filter(objs);
  }
  return objs;
}

std::shared_ptr<workplane> workplane::vertices(const std::string &selector,
                                               const std::string &tag) const {
  return _vertices(
      selector.empty()
          ? boost::none
          : boost::optional<boost::variant<selector_ptr, std::string>>(
                selector),
      tag.empty() ? boost::none : boost::optional<std::string>(tag));
}

std::shared_ptr<workplane> workplane::vertices(const selector_ptr &sel,
                                               const std::string &tag) const {
  return _vertices(boost::variant<selector_ptr, std::string>(sel),
                   tag.empty() ? boost::none
                               : boost::optional<std::string>(tag));
}

std::shared_ptr<workplane> workplane::faces(const std::string &selector,
                                            const std::string &tag) const {
  return _faces(
      selector.empty()
          ? boost::none
          : boost::optional<boost::variant<selector_ptr, std::string>>(
                selector),
      tag.empty() ? boost::none : boost::optional<std::string>(tag));
}

std::shared_ptr<workplane> workplane::faces(const selector_ptr &sel,
                                            const std::string &tag) const {
  return _faces(boost::variant<selector_ptr, std::string>(sel),
                tag.empty() ? boost::none : boost::optional<std::string>(tag));
}

std::shared_ptr<workplane> workplane::edges(const std::string &selector,
                                            const std::string &tag) const {
  return _edges(
      selector.empty()
          ? boost::none
          : boost::optional<boost::variant<selector_ptr, std::string>>(
                selector),
      tag.empty() ? boost::none : boost::optional<std::string>(tag));
}

std::shared_ptr<workplane> workplane::edges(const selector_ptr &sel,
                                            const std::string &tag) const {
  return _edges(boost::variant<selector_ptr, std::string>(sel),
                tag.empty() ? boost::none : boost::optional<std::string>(tag));
}

std::shared_ptr<workplane> workplane::wires(const std::string &selector,
                                            const std::string &tag) const {
  return _wires(
      selector.empty()
          ? boost::none
          : boost::optional<boost::variant<selector_ptr, std::string>>(
                selector),
      tag.empty() ? boost::none : boost::optional<std::string>(tag));
}

std::shared_ptr<workplane> workplane::wires(const selector_ptr &sel,
                                            const std::string &tag) const {
  return _wires(boost::variant<selector_ptr, std::string>(sel),
                tag.empty() ? boost::none : boost::optional<std::string>(tag));
}

std::shared_ptr<workplane> workplane::solids(const std::string &selector,
                                             const std::string &tag) const {
  return _solids(
      selector.empty()
          ? boost::none
          : boost::optional<boost::variant<selector_ptr, std::string>>(
                selector),
      tag.empty() ? boost::none : boost::optional<std::string>(tag));
}

std::shared_ptr<workplane> workplane::solids(const selector_ptr &sel,
                                             const std::string &tag) const {
  return _solids(boost::variant<selector_ptr, std::string>(sel),
                 tag.empty() ? boost::none : boost::optional<std::string>(tag));
}

std::shared_ptr<workplane> workplane::shells(const std::string &selector,
                                             const std::string &tag) const {
  return _shells(
      selector.empty()
          ? boost::none
          : boost::optional<boost::variant<selector_ptr, std::string>>(
                selector),
      tag.empty() ? boost::none : boost::optional<std::string>(tag));
}

std::shared_ptr<workplane> workplane::shells(const selector_ptr &sel,
                                             const std::string &tag) const {
  return _shells(boost::variant<selector_ptr, std::string>(sel),
                 tag.empty() ? boost::none : boost::optional<std::string>(tag));
}

std::shared_ptr<workplane> workplane::compounds(const std::string &selector,
                                                const std::string &tag) const {
  return _compounds(
      selector.empty()
          ? boost::none
          : boost::optional<boost::variant<selector_ptr, std::string>>(
                selector),
      tag.empty() ? boost::none : boost::optional<std::string>(tag));
}

std::shared_ptr<workplane> workplane::compounds(const selector_ptr &sel,
                                                const std::string &tag) const {
  return _compounds(boost::variant<selector_ptr, std::string>(sel),
                    tag.empty() ? boost::none
                                : boost::optional<std::string>(tag));
}

std::shared_ptr<workplane> workplane::_vertices(
    const boost::optional<boost::variant<selector_ptr, std::string>> &selector,
    const boost::optional<std::string> &tag) const {
  return select_objects(shape_object_type::vertex, selector, tag);
}

std::shared_ptr<workplane> workplane::_faces(
    const boost::optional<boost::variant<selector_ptr, std::string>> &selector,
    const boost::optional<std::string> &tag) const {
  return select_objects(shape_object_type::face, selector, tag);
}

std::shared_ptr<workplane> workplane::_edges(
    const boost::optional<boost::variant<selector_ptr, std::string>> &selector,
    const boost::optional<std::string> &tag) const {
  return select_objects(shape_object_type::edge, selector, tag);
}

std::shared_ptr<workplane> workplane::_wires(
    const boost::optional<boost::variant<selector_ptr, std::string>> &selector,
    const boost::optional<std::string> &tag) const {
  return select_objects(shape_object_type::wire, selector, tag);
}

std::shared_ptr<workplane> workplane::_solids(
    const boost::optional<boost::variant<selector_ptr, std::string>> &selector,
    const boost::optional<std::string> &tag) const {
  return select_objects(shape_object_type::solid, selector, tag);
}

std::shared_ptr<workplane> workplane::_shells(
    const boost::optional<boost::variant<selector_ptr, std::string>> &selector,
    const boost::optional<std::string> &tag) const {
  return select_objects(shape_object_type::shell, selector, tag);
}

std::shared_ptr<workplane> workplane::_compounds(
    const boost::optional<boost::variant<selector_ptr, std::string>> &selector,
    const boost::optional<std::string> &tag) const {
  return select_objects(shape_object_type::compound, selector, tag);
}

std::shared_ptr<workplane>
workplane::ancestors(TopAbs_ShapeEnum kind,
                     const boost::optional<std::string> &tag) const {
  solid ctx_solid = find_solid();
  std::vector<shape_object> objects =
      tag ? get_tagged(*tag)->_objects : _objects;

  std::vector<shape> results;
  for (auto &obj : objects) {
    if (auto shp = boost::get<shape>(&obj)) {
      auto ancestors = shp->ancestors(ctx_solid, kind)->get_shapes();
      results.insert(results.end(), ancestors.begin(), ancestors.end());
    }
  }
  std::unordered_set<shape> unique_results(results.begin(), results.end());
  std::vector<shape> newResults(unique_results.begin(), unique_results.end());

  return new_shape_object(newResults);
}

std::shared_ptr<workplane>
workplane::siblings(TopAbs_ShapeEnum kind, int level,
                    const boost::optional<std::string> &tag) const {
  solid ctx_solid = find_solid();
  std::vector<shape_object> objects =
      tag ? get_tagged(*tag)->_objects : _objects;

  std::vector<shape> shapes;
  for (auto &obj : objects) {
    if (auto shp = boost::get<shape>(&obj)) {
      shapes.push_back(*shp);
    }
  }

  std::vector<shape> results;
  for (auto &shp : shapes) {
    auto siblings = shp.siblings(ctx_solid, kind, level)->get_shapes();
    results.insert(results.end(), siblings.begin(), siblings.end());
  }

  std::unordered_set<shape> unique_results(results.begin(), results.end());
  std::vector<shape> newResults(unique_results.begin(), unique_results.end());

  return new_shape_object(newResults);
}

std::shared_ptr<workplane>
workplane::rotate_about_center(const gp_Pnt &axisEndPoint,
                               double angleDegrees) {
  auto _rot = [&](shape_object &obj) -> shape_object {
    if (auto sh = boost::get<shape>(&obj)) {
      gp_Pnt startPt = sh->centre_of_mass();
      gp_Vec endVec(axisEndPoint.X(), axisEndPoint.Y(), axisEndPoint.Z());
      gp_Pnt endPt = startPt.Translated(endVec);
      return sh->rotated(angleDegrees, startPt, endPt);
    }
    return obj;
  };

  return this->each(_rot, false, false);
}

std::shared_ptr<workplane> workplane::rotate(const gp_Pnt &axisStartPoint,
                                             const gp_Pnt &axisEndPoint,
                                             double angleDegrees) {
  std::vector<shape_object> new_objects;
  for (auto &obj : _objects) {
    if (auto sh = boost::get<shape>(&obj)) {
      new_objects.push_back(shape_object(
          sh->rotated(angleDegrees, axisStartPoint, axisEndPoint)));
    } else {
      new_objects.push_back(obj);
    }
  }
  return new_object(new_objects);
}

std::shared_ptr<workplane> workplane::mirror(const std::string &planeName,
                                             const gp_Pnt &basePoint,
                                             bool unionResult) {
  return _mirror(planeName, basePoint, unionResult);
}

std::shared_ptr<workplane> workplane::mirror(const gp_Vec &normal,
                                             const gp_Pnt &basePoint,
                                             bool unionResult) {
  return _mirror(normal, basePoint, unionResult);
}

std::shared_ptr<workplane> workplane::mirror(const face &mirrorFace,
                                             const gp_Pnt &basePoint,
                                             bool unionResult) {
  return _mirror(mirrorFace, basePoint, unionResult);
}

std::shared_ptr<workplane> workplane::mirror(const workplane &mirrorPlane,
                                             const gp_Pnt &basePoint,
                                             bool unionResult) {
  return _mirror(mirrorPlane, basePoint, unionResult);
}

std::shared_ptr<workplane> workplane::_mirror(
    const boost::variant<std::string, gp_Vec, face,
                         std::reference_wrapper<const workplane>> &mirrorPlane,
    const boost::optional<gp_Pnt> &basePointVector, bool unionResult) {
  gp_Vec mp;
  gp_Pnt bp;
  boost::optional<topo::face> mirrorFace;

  if (auto wp =
          boost::get<std::reference_wrapper<const workplane>>(&mirrorPlane)) {
    shape_object val = wp->get().val();
    if (auto f = boost::get<shape>(&val)) {
      if (f->shape_type() == TopAbs_FACE) {
        mp = f->cast<topo::face>()->normal_at();
        mirrorFace = *f->cast<topo::face>();
      }
    } else {
      throw std::runtime_error("Face required for mirror plane");
    }
  } else if (auto f = boost::get<face>(&mirrorPlane)) {
    mp = f->normal_at();
    mirrorFace = *f;
  } else if (auto vec = boost::get<gp_Vec>(&mirrorPlane)) {
    mp = *vec;
  } else if (auto planeStr = boost::get<std::string>(&mirrorPlane)) {
    mp = plane_string_to_normal(*planeStr);
  }

  if (mirrorFace && !basePointVector) {
    bp = mirrorFace->center();
  } else if (!basePointVector) {
    bp = gp_Pnt(0, 0, 0);
  } else {
    bp = *basePointVector;
  }

  std::vector<shape_object> mirrored;
  for (auto &obj : vals()) {
    if (auto sh = boost::get<shape>(&obj)) {
      mirrored.push_back(shape_object(sh->mirrored(bp, mp)));
    }
  }
  auto newS = new_object(mirrored);

  if (unionResult) {
    return this->union_(*newS);
  }
  return newS;
}

std::shared_ptr<workplane> workplane::translate(const gp_Vec &vec) {
  std::vector<shape_object> new_objects;
  for (auto &obj : _objects) {
    if (auto sh = boost::get<shape>(&obj)) {
      new_objects.push_back(sh->translated(vec));
    } else {
      new_objects.push_back(obj);
    }
  }
  return new_object(new_objects);
}

// Helper function
gp_Vec workplane::plane_string_to_normal(const std::string &planeStr) {
  if (planeStr == "XY" || planeStr == "YX")
    return gp_Vec(0, 0, 1);
  if (planeStr == "XZ" || planeStr == "ZX")
    return gp_Vec(0, 1, 0);
  if (planeStr == "YZ" || planeStr == "ZY")
    return gp_Vec(1, 0, 0);
  throw std::runtime_error("Invalid plane string");
}

std::shared_ptr<workplane> workplane::shell(double thickness,
                                            const std::string &kind) {
  solid s = find_solid();

  std::vector<face> faces;
  for (auto &obj : _objects) {
    if (auto f = boost::get<shape>(&obj)) {
      if (f->shape_type() == TopAbs_FACE) {
        faces.push_back(*f->cast<topo::face>());
      }
    }
  }

  if (faces.empty()) {
    throw std::runtime_error("Shell requires at least one face to be selected");
  }

  GeomAbs_JoinType joinType;
  if (kind == "arc") {
    joinType = GeomAbs_Arc;
  } else if (kind == "intersection") {
    joinType = GeomAbs_Intersection;
  }

  shape shp = *topo::shelling(s, faces, thickness, 1.0E-4, joinType);
  return new_shape_object(std::vector<shape>({shp}));
}

std::shared_ptr<workplane> workplane::fillet(double radius) {
  solid s = find_solid();

  std::vector<edge> edgeList;
  for (auto &obj : edges()->vals()) {
    if (auto e = boost::get<shape>(&obj)) {
      if (e->shape_type() == TopAbs_EDGE) {
        edgeList.push_back(*e->cast<topo::edge>());
      }
    }
  }

  if (edgeList.empty()) {
    throw std::runtime_error("Fillet requires that edges be selected");
  }

  shape result = *topo::fillet(s, edgeList, radius);
  return new_shape_object(std::vector<shape>({result.clean()}));
}

std::shared_ptr<workplane> workplane::chamfer(double length,
                                              boost::optional<double> length2) {
  solid s = find_solid();

  std::vector<edge> edgeList;
  for (auto &obj : edges()->vals()) {
    if (auto e = boost::get<shape>(&obj)) {
      if (e->shape_type() == TopAbs_EDGE) {
        edgeList.push_back(*e->cast<topo::edge>());
      }
    }
  }

  if (edgeList.empty()) {
    throw std::runtime_error("Chamfer requires that edges be selected");
  }

  shape result;
  if (length2) {
    result = *topo::chamfer(s, edgeList, length, *length2);
  } else {
    result = *topo::chamfer(s, edgeList, length);
  }

  return new_shape_object(std::vector<shape>({result}));
}

std::shared_ptr<workplane> workplane::transformed(const gp_Vec &rotate,
                                                  const gp_Vec &offset) {
  auto p = _plane->rotated(rotate);
  p.set_origin(_plane->to_world_coords(offset));

  auto ns = std::make_shared<workplane>();
  ns->_objects.push_back(p.origin());
  ns->_plane = std::make_shared<topo_plane>(p);
  ns->_parent = shared_from_this();
  ns->_ctx = _ctx;

  return ns;
}

template <typename T>
std::shared_ptr<workplane>
workplane::new_shape_object(const std::vector<T> &objlist) const {
  auto ns = std::make_shared<workplane>();

  if (_plane) {
    ns->_plane = std::make_shared<topo_plane>(*_plane);
  }

  ns->_parent = std::const_pointer_cast<workplane>(shared_from_this());
  ns->_ctx = _ctx;

  ns->_objects.clear();
  for (const auto &obj : objlist) {
    ns->_objects.push_back(obj);
  }

  return ns;
}

template std::shared_ptr<workplane>
workplane::new_shape_object(const std::vector<shape> &objlist) const;

template std::shared_ptr<workplane>
workplane::new_shape_object(const std::vector<compound> &objlist) const;

template std::shared_ptr<workplane>
workplane::new_shape_object(const std::vector<vertex> &objlist) const;

template std::shared_ptr<workplane>
workplane::new_shape_object(const std::vector<topo::wire> &objlist) const;

template std::shared_ptr<workplane>
workplane::new_shape_object(const std::vector<edge> &objlist) const;

template std::shared_ptr<workplane>
workplane::new_shape_object(const std::vector<face> &objlist) const;

template std::shared_ptr<workplane>
workplane::new_shape_object(const std::vector<topo::shell> &objlist) const;

template std::shared_ptr<workplane>
workplane::new_shape_object(const std::vector<solid> &objlist) const;

template std::shared_ptr<workplane>
workplane::new_shape_object(const std::vector<comp_solid> &objlist) const;

std::shared_ptr<workplane>
workplane::new_object(const std::vector<shape_object> &objlist) const {
  auto ns = std::make_shared<workplane>();

  if (_plane) {
    ns->_plane = std::make_shared<topo_plane>(*_plane);
  }

  ns->_parent = std::const_pointer_cast<workplane>(shared_from_this());
  ns->_ctx = _ctx;

  ns->_objects = objlist;

  return ns;
}

gp_Pnt workplane::find_from_point(bool useLocalCoords) {
  shape_object obj = _objects.empty() ? _plane->origin() : _objects.back();

  topo_vector p;
  if (auto shp = boost::get<shape>(&obj)) {
    if (shp->shape_type() == TopAbs_EDGE) {
      p = shp->cast<topo::edge>()->end_point();
    }
  } else if (auto vec = boost::get<topo_vector>(&obj)) {
    p = *vec;
  } else {
    throw std::runtime_error("Cannot convert object type to point");
  }

  return useLocalCoords ? _plane->to_local_coords(p) : p;
}

edge workplane::find_from_edge(bool useLocalCoords) {
  if (_objects.empty()) {
    throw std::runtime_error("No objects on stack to find edge from");
  }

  shape_object obj = _objects.back();
  if (auto e = boost::get<shape>(&obj)) {
    if (e->shape_type() == TopAbs_EDGE) {
      return useLocalCoords ? *_plane->to_local_coords(*e).cast<edge>()
                            : *e->cast<edge>();
    }
  } else {
    throw std::runtime_error(
        "Previous Edge requested, but the previous object was not an Edge");
  }
}

std::shared_ptr<workplane> workplane::rarray(double xSpacing, double ySpacing,
                                             int xCount, int yCount,
                                             std::pair<bool, bool> center) {
  return _rarray(xSpacing, ySpacing, xCount, yCount,
                 std::make_tuple(center.first, center.second));
}

std::shared_ptr<workplane> workplane::rarray(double xSpacing, double ySpacing,
                                             int xCount, int yCount,
                                             bool centerAll) {
  return _rarray(xSpacing, ySpacing, xCount, yCount, centerAll);
}

std::shared_ptr<workplane>
workplane::_rarray(double xSpacing, double ySpacing, int xCount, int yCount,
                   const boost::variant<bool, std::tuple<bool, bool>> &center) {
  if ((xSpacing <= 0 && ySpacing <= 0) || xCount < 1 || yCount < 1) {
    throw std::runtime_error(
        "Spacing and count must be > 0 in at least one direction");
  }

  bool centerX, centerY;
  if (auto b = boost::get<bool>(&center)) {
    centerX = centerY = *b;
  } else {
    auto t = boost::get<std::tuple<bool, bool>>(center);
    centerX = std::get<0>(t);
    centerY = std::get<1>(t);
  }

  std::vector<topo_vector> lpoints;
  for (int x = 0; x < xCount; x++) {
    for (int y = 0; y < yCount; y++) {
      lpoints.emplace_back(xSpacing * x, ySpacing * y, 0);
    }
  }

  gp_Vec offset;
  if (centerX) {
    offset += gp_Vec(-xSpacing * (xCount - 1) * 0.5, 0, 0);
  }
  if (centerY) {
    offset += gp_Vec(0, -ySpacing * (yCount - 1) * 0.5, 0);
  }

  for (auto &p : lpoints) {
    p.sub(offset);
  }

  return push_points(lpoints);
}

std::shared_ptr<workplane> workplane::polar_array(double radius,
                                                  double startAngle,
                                                  double angle, int count,
                                                  bool fill, bool rotate) {
  if (count < 1) {
    throw std::runtime_error("At least 1 element required");
  }

  if (fill) {
    if (std::abs(std::fmod(angle, 360.0)) < TOL) {
      angle = angle / count;
    } else {
      angle = (count > 1) ? angle / (count - 1) : startAngle;
    }
  }

  std::vector<topo_location> locs;
  for (int i = 0; i < count; i++) {
    double phi_deg = startAngle + (angle * i);
    double phi = phi_deg * M_PI / 180.0;
    double x = radius * std::cos(phi);
    double y = radius * std::sin(phi);

    if (rotate) {
      locs.emplace_back(gp_Vec(x, y, 0), gp_Vec(0, 0, 1), phi_deg);
    } else {
      locs.emplace_back(gp_Pnt(x, y, 0));
    }
  }

  return push_points(locs);
}

std::shared_ptr<workplane>
workplane::push_points(const std::vector<topo_location> &pntList) {
  std::vector<shape_object> vecs;
  for (const auto &pnt : pntList) {
    vecs.push_back(pnt);
  }
  return new_object(vecs);
}

std::shared_ptr<workplane>
workplane::push_points(const std::vector<topo_vector> &pntList) {
  std::vector<shape_object> vecs;
  for (const auto &pnt : pntList) {
    vecs.push_back(pnt);
  }
  return new_object(vecs);
}

std::shared_ptr<workplane> workplane::center(double x, double y) {
  topo_vector new_origin = _plane->to_world_coords(gp_Pnt(x, y, 0));
  auto n = new_object({shape_object(new_origin)});
  n->_plane->set_origin2d(x, y);
  return n;
}

std::shared_ptr<workplane> workplane::line_to(double x, double y,
                                              bool forConstruction) {
  gp_Pnt startPoint = find_from_point(false);
  gp_Pnt endPoint = _plane->to_world_coords(gp_Pnt(x, y, 0));

  edge p = edge::make_edge(startPoint, endPoint);

  if (!forConstruction) {
    add_pending_edge(p);
  }

  return new_shape_object(std::vector<shape>({p}));
}

std::shared_ptr<workplane>
workplane::bezier(const std::vector<topo_vector> &listOfPoints,
                  bool forConstruction, bool includeCurrent, bool makeWire) {
  std::vector<gp_Pnt> allPoints;

  if (includeCurrent) {
    allPoints.push_back(find_from_point(false));
  }
  for (auto &pt : listOfPoints) {
    allPoints.push_back(pt.to_pnt());
  }

  edge e = edge::make_bezier(allPoints);

  if (makeWire) {
    topo::wire rv_w = topo::wire::make_wire({e});
    if (!forConstruction) {
      add_pending_wire(rv_w);
    }
    return new_shape_object(std::vector<shape>({rv_w}));
  } else {
    if (!forConstruction) {
      add_pending_edge(e);
    }
    return new_shape_object(std::vector<shape>({e}));
  }
}

std::shared_ptr<workplane> workplane::line(double xDist, double yDist,
                                           bool forConstruction) {
  gp_Pnt p = find_from_point(true); // returns local coordinates
  return line_to(p.X() + xDist, p.Y() + yDist, forConstruction);
}

std::shared_ptr<workplane> workplane::vline(double distance,
                                            bool forConstruction) {
  return line(0, distance, forConstruction);
}

std::shared_ptr<workplane> workplane::hline(double distance,
                                            bool forConstruction) {
  return line(distance, 0, forConstruction);
}

std::shared_ptr<workplane> workplane::vline_to(double yCoord,
                                               bool forConstruction) {
  gp_Pnt p = find_from_point(true);
  return line_to(p.X(), yCoord, forConstruction);
}

std::shared_ptr<workplane> workplane::hline_to(double xCoord,
                                               bool forConstruction) {
  gp_Pnt p = find_from_point(true);
  return line_to(xCoord, p.Y(), forConstruction);
}

std::shared_ptr<workplane> workplane::polar_line(double distance, double angle,
                                                 bool forConstruction) {
  double x = std::cos(angle * M_PI / 180.0) * distance;
  double y = std::sin(angle * M_PI / 180.0) * distance;

  return line(x, y, forConstruction);
}

std::shared_ptr<workplane>
workplane::polar_line_to(double distance, double angle, bool forConstruction) {
  double x = std::cos(angle * M_PI / 180.0) * distance;
  double y = std::sin(angle * M_PI / 180.0) * distance;

  return line_to(x, y, forConstruction);
}

std::shared_ptr<workplane> workplane::move_to(double x, double y) {
  gp_Pnt newCenter(x, y, 0);
  return new_object({_plane->to_world_coords(newCenter)});
}

std::shared_ptr<workplane> workplane::move(double xDist, double yDist) {
  gp_Pnt p = find_from_point(true);
  gp_Pnt newCenter(p.X() + xDist, p.Y() + yDist, 0);
  return new_object({_plane->to_world_coords(newCenter)});
}

std::shared_ptr<workplane> workplane::slot2d(double length, double diameter,
                                             double angle) {
  double radius = diameter / 2;

  gp_Pnt p1(-length / 2 + radius, diameter / 2, 0);
  gp_Pnt p2 = p1.Translated(gp_Vec(length - diameter, 0, 0));
  gp_Pnt p3 = p1.Translated(gp_Vec(length - diameter, -diameter, 0));
  gp_Pnt p4 = p1.Translated(gp_Vec(0, -diameter, 0));
  gp_Pnt arc1 = p2.Translated(gp_Vec(radius, -radius, 0));
  gp_Pnt arc2 = p4.Translated(gp_Vec(-radius, radius, 0));

  std::vector<edge> edges;
  edges.push_back(edge::make_polygon(p1, p2));
  edges.push_back(edge::make_three_point_arc(p2, arc1, p3));
  edges.push_back(edge::make_edge(p3, p4));
  edges.push_back(edge::make_three_point_arc(p4, arc2, p1));

  topo::wire slot = topo::wire::make_wire(edges);
  slot.rotate(angle * M_PI / 180.0, gp_Pnt(), gp_Pnt(0, 0, 1));

  return _eachpoint(
      [slot](const topo_location &loc) { return slot.moved(loc); }, true);
}

std::shared_ptr<workplane>
workplane::spline(const std::vector<gp_Pnt> &points,
                  const boost::optional<std::vector<gp_Vec>> &tangents,
                  bool periodic,
                  const boost::optional<std::vector<double>> &parameters,
                  bool scale, boost::optional<double> tol, bool forConstruction,
                  bool includeCurrent, bool makeWire) {
  std::vector<gp_Pnt> allPoints;
  if (includeCurrent) {
    allPoints.push_back(find_from_point(false));
  }
  for (const auto &p : points) {
    allPoints.push_back(_plane->to_world_coords(p));
  }

  std::vector<gp_Vec> worldTangents;
  if (tangents) {
    std::vector<gp_Vec> tans;
    for (const auto &t : *tangents) {
      tans.push_back(_plane->to_world_coords(t) - _plane->origin());
    }
    worldTangents = tans;
  }

  edge e = edge::make_spline(allPoints, &worldTangents, periodic,
                             parameters ? &*parameters : nullptr, scale,
                             tol ? *tol : 1e-6);

  if (makeWire) {
    topo::wire w = topo::wire::make_wire({e});
    if (!forConstruction) {
      add_pending_wire(w);
    }
    return new_shape_object(std::vector<shape>({w}));
  } else {
    if (!forConstruction) {
      add_pending_edge(e);
    }
    return new_shape_object(std::vector<shape>({e}));
  }
}

std::shared_ptr<workplane> workplane::spline_approx(
    const std::vector<gp_Pnt> &points, boost::optional<double> tol, int minDeg,
    int maxDeg,
    const boost::optional<std::tuple<double, double, double>> &smoothing,
    bool forConstruction, bool includeCurrent, bool makeWire) {
  std::vector<gp_Pnt> allPoints;
  if (includeCurrent) {
    allPoints.push_back(find_from_point(false));
  }
  for (const auto &p : points) {
    allPoints.push_back(_plane->to_world_coords(p));
  }

  edge e = edge::make_spline_approx(allPoints, tol ? *tol : 1e-6, smoothing,
                                    minDeg, maxDeg);

  if (makeWire) {
    topo::wire w = topo::wire::make_wire({e});
    if (!forConstruction) {
      add_pending_wire(w);
    }
    return new_shape_object(std::vector<shape>({w}));
  } else {
    if (!forConstruction) {
      add_pending_edge(e);
    }
    return new_shape_object(std::vector<shape>({e}));
  }
}

std::shared_ptr<workplane> workplane::parametric_curve(
    std::function<gp_Pnt(double)> func, int N, double start, double stop,
    double tol, int minDeg, int maxDeg,
    const std::tuple<double, double, double> &smoothing, bool makeWire) {
  double diff = stop - start;
  std::vector<gp_Pnt> allPoints;
  for (int t = 0; t <= N; t++) {
    allPoints.push_back(_plane->to_world_coords(func(start + diff * t / N)));
  }

  edge e = edge::make_spline_approx(allPoints, tol, smoothing, minDeg, maxDeg);

  if (makeWire) {
    topo::wire w = topo::wire::make_wire({e});
    add_pending_wire(w);
    return new_shape_object(std::vector<shape>({w}));
  } else {
    add_pending_edge(e);
    return new_shape_object(std::vector<shape>({e}));
  }
}

std::shared_ptr<workplane> workplane::parametric_surface(
    std::function<gp_Pnt(double, double)> func, int N, double start,
    double stop, double tol, int minDeg, int maxDeg,
    const std::tuple<double, double, double> &smoothing) {
  double diff = stop - start;
  std::vector<std::vector<gp_Pnt>> allPoints;
  for (int i = 0; i <= N; i++) {
    std::vector<gp_Pnt> row;
    for (int j = 0; j <= N; j++) {
      row.push_back(_plane->to_world_coords(
          func(start + diff * i / N, start + diff * j / N)));
    }
    allPoints.push_back(row);
  }

  face f = face::make_spline_approx(allPoints, tol, &smoothing, minDeg, maxDeg);

  return new_shape_object(std::vector<shape>({f}));
}

std::shared_ptr<workplane>
workplane::ellipse_arc(double x_radius, double y_radius, double angle1,
                       double angle2, double rotation_angle, int sense,
                       bool forConstruction, bool startAtCurrent,
                       bool makeWire) {
  gp_Pnt center = find_from_point(false);
  edge e = edge::make_ellipse(x_radius, y_radius, center, _plane->z_dir(),
                              _plane->x_dir(), angle1, angle2, sense);

  if (rotation_angle != 0.0) {
    e.rotate(rotation_angle, center, center.Translated(_plane->z_dir()));
  }

  if (startAtCurrent) {
    gp_Pnt startPoint = e.start_point();
    e.translate(center.XYZ() - startPoint.XYZ());
  }

  if (makeWire) {
    topo::wire w = topo::wire::make_wire({e});
    if (!forConstruction) {
      add_pending_wire(w);
    }
    return new_shape_object(std::vector<shape>({w}));
  } else {
    if (!forConstruction) {
      add_pending_edge(e);
    }
    return new_shape_object(std::vector<shape>({e}));
  }
}

std::shared_ptr<workplane> workplane::three_point_arc(const gp_Pnt &point1,
                                                      const gp_Pnt &point2,
                                                      bool forConstruction) {
  gp_Pnt gstartPoint = find_from_point(false);
  gp_Pnt gpoint1 = _plane->to_world_coords(point1);
  gp_Pnt gpoint2 = _plane->to_world_coords(point2);

  edge arc = edge::make_three_point_arc(gstartPoint, gpoint1, gpoint2);

  if (!forConstruction) {
    add_pending_edge(arc);
  }

  return new_shape_object(std::vector<shape>({arc}));
}

std::shared_ptr<workplane> workplane::sagitta_arc(const gp_Pnt &endPoint,
                                                  double sag,
                                                  bool forConstruction) {
  gp_Pnt startPoint = find_from_point(true);
  gp_Pnt endPointVec(endPoint.X(), endPoint.Y(), 0);
  gp_Pnt midPoint = gp_Pnt((endPointVec.X() + startPoint.X()) / 2.0,
                           (endPointVec.Y() + startPoint.Y()) / 2.0, 0);

  gp_Vec baseVec(endPointVec.X() - startPoint.X(),
                 endPointVec.Y() - startPoint.Y(), 0);
  baseVec.Normalize();
  gp_Vec sagVec = baseVec.Multiplied(std::abs(sag));

  if (sag > 0) {
    // Rotate +90 degrees
    sagVec = gp_Vec(-sagVec.Y(), sagVec.X(), 0);
  } else {
    // Rotate -90 degrees
    sagVec = gp_Vec(sagVec.Y(), -sagVec.X(), 0);
  }

  gp_Pnt sagPoint = midPoint.Translated(sagVec);
  return three_point_arc(sagPoint, endPointVec, forConstruction);
}

std::shared_ptr<workplane> workplane::radius_arc(const gp_Pnt &endPoint,
                                                 double radius,
                                                 bool forConstruction) {
  gp_Pnt startPoint = find_from_point(true);
  gp_Pnt endPointVec(endPoint.X(), endPoint.Y(), 0);

  double length = startPoint.Distance(endPointVec) / 2.0;
  double sag;
  try {
    sag = std::abs(radius);
    double r_2_l_2 = radius * radius - length * length;
    if (std::abs(r_2_l_2) >= TOL) {
      sag -= std::sqrt(r_2_l_2);
    }
  } catch (...) {
    throw std::runtime_error(
        "Arc radius is not large enough to reach the end point");
  }

  if (radius > 0) {
    return sagitta_arc(endPointVec, sag, forConstruction);
  } else {
    return sagitta_arc(endPointVec, -sag, forConstruction);
  }
}

std::shared_ptr<workplane> workplane::tangent_arc_point(const gp_Pnt &endpoint,
                                                        bool forConstruction,
                                                        bool relative) {
  gp_Pnt endpointVec(endpoint.X(), endpoint.Y(), 0);
  if (relative) {
    gp_Pnt current = find_from_point(true);
    endpointVec =
        gp_Pnt(endpointVec.X() + current.X(), endpointVec.Y() + current.Y(), 0);
  }
  endpointVec = _plane->to_world_coords(endpointVec);

  edge previousEdge = find_from_edge();
  gp_Pnt edgeEnd = previousEdge.end_point();
  gp_Vec edgeTangent = previousEdge.tangent_at(1.0);

  edge arc = edge::make_tangent_arc(edgeEnd, edgeTangent, endpointVec);

  if (!forConstruction) {
    add_pending_edge(arc);
  }

  return new_shape_object(std::vector<shape>({arc}));
}

std::shared_ptr<workplane> workplane::wire(bool forConstruction) {
  if (_ctx->pending_edges().empty()) {
    return this->shared_from_this();
  }

  std::vector<topo::edge> edges = _ctx->pop_pending_edges();

  topo::wire w = topo::wire::make_wire(edges);

  if (!forConstruction) {
    add_pending_wire(w);
  }

  std::vector<shape> new_objects;
  for (const auto &obj : _objects) {
    if (auto edge = boost::get<shape>(&obj)) {
      if (edge->shape_type() == TopAbs_EDGE) {
        new_objects.push_back(*edge);
      }
    }
  }
  new_objects.push_back(w);

  return new_shape_object(new_objects);
}

std::shared_ptr<workplane> workplane::mirror_y() {
  std::shared_ptr<workplane> n = this->wire(false);
  std::shared_ptr<workplane> consolidated = n->consolidate_wires();

  std::vector<shape> shapes;
  for (auto &obj : consolidated->wires()->vals()) {
    if (auto shp = boost::get<shape>(&obj)) {
      shapes.push_back(*shp);
    } else if (auto shp = boost::get<std::shared_ptr<topo::sketch>>(&obj)) {
      shapes.push_back(*(*shp)->faces_);
    }
  }

  std::vector<shape> mirroredWires = _plane->mirror_in_plane(shapes, "Y");
  for (auto &w : mirroredWires) {
    consolidated->_objects.push_back(w);
    consolidated->add_pending_wire(*w.cast<topo::wire>());
  }

  return consolidated->consolidate_wires();
}

std::shared_ptr<workplane> workplane::mirror_x() {
  std::shared_ptr<workplane> n = this->wire(false);
  std::shared_ptr<workplane> consolidated = n->consolidate_wires();

  std::vector<shape> shapes;
  for (auto &obj : consolidated->wires()->vals()) {
    if (auto shp = boost::get<shape>(&obj)) {
      shapes.push_back(*shp);
    } else if (auto shp = boost::get<std::shared_ptr<topo::sketch>>(&obj)) {
      shapes.push_back(*(*shp)->faces_);
    }
  }

  std::vector<shape> mirroredWires = _plane->mirror_in_plane(shapes, "X");
  for (auto &w : mirroredWires) {
    consolidated->_objects.push_back(w);
    consolidated->add_pending_wire(*w.cast<topo::wire>());
  }

  return consolidated->consolidate_wires();
}

void workplane::add_pending_edge(const edge &e) {
  _ctx->pending_edges().push_back(e);

  if (!_ctx->first_point()) {
    _ctx->set_first_point(_plane->to_local_coords(e.start_point()));
  }
}

void workplane::add_pending_wire(const topo::wire &w) {
  _ctx->pending_wires().push_back(w);
}

std::vector<topo::wire> workplane::_consolidate_wires() {
  std::vector<topo::shape> wires;
  for (auto &e : _ctx->pending_edges()) {
    wires.push_back(topo::wire::make_wire({e}));
  }
  for (auto &w : _ctx->pending_wires()) {
    wires.push_back(w);
  }

  if (wires.empty()) {
    return {};
  }

  return topo::wire::combine(wires);
}

std::shared_ptr<workplane> workplane::consolidate_wires() {
  std::vector<flywave::topo::wire> w = _consolidate_wires();

  if (w.empty()) {
    return this->shared_from_this();
  }

  auto r = new_shape_object(w);
  r->_ctx->set_pending_wires(w);
  r->_ctx->pending_edges().clear();

  return r;
}

std::shared_ptr<workplane>
workplane::each(std::function<shape_object(shape_object &)> callback,
                bool useLocalCoordinates, bool combine, bool clean) {
  std::vector<shape> results;
  for (auto &obj : _objects) {
    shape_object r;
    if (useLocalCoordinates) {
      auto shape = select_shape(obj);
      if (shape) {
        shape_object so(_plane->to_local_coords(*shape));
        r = callback(so);

        auto shape = select_shape(r);
        shape->transform(_plane->_rG);

        r = *shape;
      }

    } else {
      r = callback(obj);
    }

    if (auto w = boost::get<shape>(&r)) {
      if (w->shape_type() == TopAbs_WIRE) {
        if (!w->for_construction()) {
          add_pending_wire(*w->cast<topo::wire>());
        }
      }
    }

    if (auto shp = boost::get<shape>(&r)) {
      results.push_back(*shp);
    } else if (auto shp = boost::get<std::shared_ptr<topo::sketch>>(&r)) {
      results.push_back(*(*shp)->faces_);
    }
  }

  return combine_with_base(results, combine, clean);
}

std::shared_ptr<workplane> workplane::eachpoint(const shape &shapeObj,
                                                bool useLocalCoordinates,
                                                bool combine, bool clean) {
  return _eachpoint(shapeObj, useLocalCoordinates, combine, clean);
}

std::shared_ptr<workplane>
workplane::eachpoint(std::function<shape(topo_location)> func,
                     bool useLocalCoordinates, bool combine, bool clean) {
  return _eachpoint(func, useLocalCoordinates, combine, clean);
}

std::shared_ptr<workplane> workplane::eachpoint(const workplane &wp,
                                                bool useLocalCoordinates,
                                                bool combine, bool clean) {
  return _eachpoint(wp, useLocalCoordinates, combine, clean);
}

std::shared_ptr<workplane> workplane::_eachpoint(
    const boost::variant<shape, std::reference_wrapper<const workplane>,
                         std::function<shape(topo_location)>> &arg,
    bool useLocalCoordinates, bool combine, bool clean) {
  std::vector<topo_location> pnts;
  auto loc = _plane->location();

  if (_objects.empty()) {
    pnts.push_back(topo_location());
  } else {
    for (auto &o : _objects) {
      if (auto s = boost::get<shape>(&o)) {
        pnts.push_back(loc.inverted() *
                       topo_location(*_plane, s->centre_of_mass()));
      } else if (auto vec = boost::get<topo_vector>(&o)) {
        pnts.push_back(loc.inverted() * *vec);
      } else if (auto sk = boost::get<std::shared_ptr<topo::sketch>>(&o)) {
        pnts.push_back(loc.inverted() *
                       topo_location(*_plane, (*sk)->faces_->centre_of_mass()));
      } else if (auto loc = boost::get<topo_location>(&o)) {
        pnts.push_back(*loc);
      }
    }
  }

  std::vector<shape> res;
  if (auto wp = boost::get<std::reference_wrapper<const workplane>>(&arg)) {
    if (useLocalCoordinates) {
      for (auto &v : wp->get().vals()) {
        if (auto s = boost::get<shape>(&v)) {
          for (auto &p : pnts) {
            res.push_back(s->moved(p).moved(loc));
          }
        }
      }
    } else {
      for (auto &v : wp->get().vals()) {
        if (auto s = boost::get<shape>(&v)) {
          for (auto &p : pnts) {
            res.push_back(s->moved(p * loc));
          }
        }
      }
    }
  } else if (auto s = boost::get<shape>(&arg)) {
    if (useLocalCoordinates) {
      for (auto &p : pnts) {
        res.push_back(s->moved(p).moved(loc));
      }
    } else {
      for (auto &p : pnts) {
        res.push_back(s->moved(p * loc));
      }
    }
  } else if (auto f = boost::get<std::function<shape(topo_location)>>(&arg)) {
    if (useLocalCoordinates) {
      for (auto &p : pnts) {
        res.push_back((*f)(p).moved(loc));
      }
    } else {
      for (auto &p : pnts) {
        res.push_back((*f)(p * loc));
      }
    }
  } else {
    throw std::runtime_error("Unsupported argument type");
  }

  for (auto &r : res) {
    if (auto w = r.cast<topo::wire>()) {
      if (!w->for_construction()) {
        add_pending_wire(*w);
      }
    }
  }

  return combine_with_base(res, combine, clean);
}

std::shared_ptr<workplane> workplane::rect(double xLen, double yLen,
                                           std::pair<bool, bool> center,
                                           bool forConstruction) {
  return _rect(xLen, yLen, std::make_tuple(center.first, center.second),
               forConstruction);
}

std::shared_ptr<workplane> workplane::rect(double xLen, double yLen,
                                           bool centerAll,
                                           bool forConstruction) {
  return _rect(xLen, yLen, centerAll, forConstruction);
}

std::shared_ptr<workplane>
workplane::_rect(double xLen, double yLen,
                 const boost::variant<bool, std::tuple<bool, bool>> &centered,
                 bool forConstruction) {
  bool centerX, centerY;
  if (auto b = boost::get<bool>(&centered)) {
    centerX = centerY = *b;
  } else {
    auto t = boost::get<std::tuple<bool, bool>>(centered);
    centerX = std::get<0>(t);
    centerY = std::get<1>(t);
  }

  gp_Vec offset;
  if (!centerX)
    offset += gp_Vec(xLen / 2, 0, 0);
  if (!centerY)
    offset += gp_Vec(0, yLen / 2, 0);

  std::vector<gp_Pnt> points = {
      gp_Pnt(xLen / -2.0, yLen / -2.0, 0), gp_Pnt(xLen / 2.0, yLen / -2.0, 0),
      gp_Pnt(xLen / 2.0, yLen / 2.0, 0), gp_Pnt(xLen / -2.0, yLen / 2.0, 0),
      gp_Pnt(xLen / -2.0, yLen / -2.0, 0) // Close the wire
  };

  for (auto &p : points) {
    p.Translate(offset);
  }

  topo::wire w = topo::wire::make_polygon(points, forConstruction);
  return _eachpoint(
      [w](const topo_location &loc) -> shape { return w.moved(loc); }, true);
}

std::shared_ptr<workplane> workplane::circle(double radius,
                                             bool forConstruction) {
  topo::wire c = topo::wire::make_circle(radius, gp_Pnt(), gp_Vec(0, 0, 1));
  c.set_for_construction(forConstruction);
  return _eachpoint([c](const topo_location &loc) { return c.moved(loc); },
                    true);
}

std::shared_ptr<workplane> workplane::ellipse(double x_radius, double y_radius,
                                              double rotation_angle,
                                              bool forConstruction) {
  topo::wire e =
      topo::wire::make_ellipse(x_radius, y_radius, gp_Pnt(), gp_Vec(0, 0, 1),
                               gp_Vec(1, 0, 0), rotation_angle);
  e.set_for_construction(forConstruction);
  return _eachpoint([e](const topo_location &loc) { return e.moved(loc); },
                    true);
}

std::shared_ptr<workplane> workplane::polygon(int nSides, double diameter,
                                              bool forConstruction,
                                              bool circumscribed) {
  if (nSides < 3) {
    throw std::runtime_error("Polygon must have at least 3 sides");
  }

  double angle = 2.0 * M_PI / nSides;
  double radius = diameter / 2.0;
  if (circumscribed) {
    radius /= std::cos(angle / 2.0);
  }

  std::vector<gp_Pnt> pnts;
  for (int i = 0; i <= nSides; i++) {
    double o = angle * i;
    if (circumscribed) {
      o += angle / 2.0;
    }
    pnts.emplace_back(radius * std::cos(o), radius * std::sin(o), 0);
  }

  topo::wire p = topo::wire::make_polygon(pnts, false, forConstruction);
  return _eachpoint([p](const topo_location &loc) { return p.moved(loc); },
                    true);
}

std::shared_ptr<workplane>
workplane::polyline(const std::vector<gp_Pnt> &points, bool forConstruction,
                    bool includeCurrent) {
  std::vector<edge> edges;
  gp_Pnt startPoint;

  if (includeCurrent) {
    startPoint = find_from_point(false);
  } else {
    startPoint = _plane->to_world_coords(points[0]);
  }

  size_t startIdx = includeCurrent ? 0 : 1;
  for (size_t i = startIdx; i < points.size(); i++) {
    gp_Pnt endPoint = _plane->to_world_coords(points[i]);
    edges.push_back(edge::make_edge(startPoint, endPoint));
    if (!forConstruction) {
      add_pending_edge(edges.back());
    }
    startPoint = endPoint;
  }

  return new_shape_object(edges);
}

std::shared_ptr<workplane> workplane::close() {
  gp_Pnt endPoint = find_from_point(true);

  if (!_ctx->first_point()) {
    throw std::runtime_error("No start point specified - cannot close");
  }

  gp_Pnt startPoint = *_ctx->first_point();
  if (endPoint.Distance(startPoint) > 1e-6) {
    polyline({endPoint, startPoint});
  }

  _ctx->set_first_point(boost::none);
  return wire();
}

double workplane::largest_dimension() const {
  solid s = find_solid();
  return s.bbox().diagonal_length();
}

std::shared_ptr<workplane>
workplane::cut_each(std::function<shape(topo_location)> fcn,
                    bool useLocalCoords, bool clean) {
  shape ctxSolid = find_solid();
  auto results = _eachpoint(fcn, useLocalCoords)->vals();

  std::vector<shape> cutShapes;
  for (auto &obj : results) {
    if (auto s = boost::get<shape>(&obj)) {
      cutShapes.push_back(*s);
    }
  }

  boost::optional<shape> s = topo::cut(ctxSolid, cutShapes);
  if (clean) {
    s = s->clean();
  }

  return new_shape_object(std::vector<shape>({*s}));
}

std::shared_ptr<workplane>
workplane::cbore_hole(double diameter, double cboreDiameter, double cboreDepth,
                      boost::optional<double> depth, bool clean) {
  if (!depth) {
    depth = largest_dimension();
  }

  gp_Vec boreDir(0, 0, -1);
  gp_Pnt center;

  solid hole =
      solid::make_solid_from_cylinder(diameter / 2.0, *depth, center, boreDir);
  solid cbore = solid::make_solid_from_cylinder(cboreDiameter / 2.0, cboreDepth,
                                                gp_Pnt(), boreDir);
  boost::optional<shape> r = topo::fuse({hole, cbore});

  return cut_each([r](const topo_location &loc) { return r->moved(loc); }, true,
                  clean);
}

std::shared_ptr<workplane>
workplane::csk_hole(double diameter, double cskDiameter, double cskAngle,
                    boost::optional<double> depth, bool clean) {
  if (!depth) {
    depth = largest_dimension();
  }

  gp_Dir boreDir(0, 0, -1);
  gp_Pnt center;

  solid hole =
      solid::make_solid_from_cylinder(diameter / 2.0, *depth, center, boreDir);
  double r = cskDiameter / 2.0;
  double h = r / std::tan(cskAngle * M_PI / 180.0 / 2.0);
  solid csk = solid::make_solid_from_cone(r, 0.0, h, center, boreDir);
  shape res = *topo::fuse({hole, csk});

  return cut_each([res](const topo_location &loc) { return res.moved(loc); },
                  true, clean);
}

std::shared_ptr<workplane>
workplane::hole(double diameter, boost::optional<double> depth, bool clean) {
  if (!depth) {
    depth = largest_dimension();
  }

  gp_Vec boreDir(0, 0, -1);
  solid h = solid::make_solid_from_cylinder(diameter / 2.0, *depth, gp_Pnt(),
                                            boreDir);

  return cut_each([h](const topo_location &loc) { return h.moved(loc); }, true,
                  clean);
}

std::shared_ptr<workplane> workplane::twist_extrude(double distance,
                                                    double angleDegrees,
                                                    bool combine, bool clean) {
  auto faces = get_faces();
  gp_Vec eDir = _plane->z_dir().multiply(distance);

  std::vector<shape> shapes;
  for (auto &f : faces) {
    shapes.push_back(*topo::extrude_linear_with_rotation(f, _plane->origin(),
                                                         eDir, angleDegrees));
  }

  shape r = compound::make_compound(shapes).fuse({});
  return combine_with_base(r, combine, clean);
}

std::shared_ptr<workplane> workplane::extrude(double distance,
                                              const combine_mode &combine,
                                              bool clean, bool both,
                                              boost::optional<double> taper) {
  return _extrude(distance, combine, clean, both, taper);
}

std::shared_ptr<workplane> workplane::extrude(face_index_type untilFace,
                                              const combine_mode &combine,
                                              bool clean, bool both,
                                              boost::optional<double> taper) {
  return _extrude(untilFace, combine, clean, both, taper);
}

std::shared_ptr<workplane> workplane::extrude(const face &untilFace,
                                              const combine_mode &combine,
                                              bool clean, bool both,
                                              boost::optional<double> taper) {
  return _extrude(untilFace, combine, clean, both, taper);
}

std::shared_ptr<workplane>
workplane::_extrude(boost::variant<double, face_index_type, face> until,
                    const combine_mode &combine, bool clean, bool both,
                    boost::optional<double> taper) {
  auto combineStr = boost::get<combine_mode_type>(&combine);
  if (combineStr && (*combineStr == combine_mode_type::cut ||
                     *combineStr == combine_mode_type::subtractive)) {
    return _cut_blind(until, clean, both, taper);
  }

  shape r;
  if (auto dist = boost::get<double>(&until)) {
    r = _extrude(*dist, both, taper);
  } else if (auto str = boost::get<face_index_type>(&until)) {
    int faceIndex = static_cast<int>(*str);
    r = _extrude(boost::none, both, taper,
                 boost::make_optional<boost::variant<int, face>>(faceIndex));
  } else if (auto f = boost::get<face>(&until)) {
    if (!boost::get<bool>(combine)) {
      throw std::runtime_error(
          "`combine` can't be False when extruding until a face");
    }
    r = _extrude(boost::none, both, taper,
                 boost::make_optional<boost::variant<int, face>>(*f));
  } else {
    throw std::runtime_error("Invalid until argument type");
  }

  return combine_with_base(r, combine, clean);
}

std::shared_ptr<workplane> workplane::revolve(
    double angleDegrees, const boost::optional<gp_Pnt> &axisStart,
    const boost::optional<gp_Pnt> &axisEnd, bool combine, bool clean) {
  angleDegrees = std::fmod(angleDegrees, 360.0);
  if (angleDegrees == 0)
    angleDegrees = 360.0;

  gp_Pnt startPoint = axisStart ? _plane->to_world_coords(*axisStart)
                                : _plane->to_world_coords(gp_Pnt(0, 0, 0));

  gp_Pnt endPoint;
  if (axisEnd) {
    endPoint = _plane->to_world_coords(*axisEnd);
  } else {
    if (startPoint.Y() != 0) {
      endPoint = _plane->to_world_coords(gp_Pnt(0, startPoint.Y(), 0));
    } else {
      endPoint = _plane->to_world_coords(gp_Pnt(0, 1, 0));
    }
  }

  shape r = _revolve(angleDegrees, startPoint, endPoint);
  return combine_with_base(r, combine, clean);
}

std::shared_ptr<workplane>
workplane::sweep(workplane &path, bool multisection, bool makeSolid,
                 bool isFrenet, bool combine, bool clean,
                 const transition_mode &transition,
                 const boost::optional<topo_vector> &normal,
                 const std::shared_ptr<workplane> &auxSpine) {
  return _sweep(path, multisection, makeSolid, isFrenet, combine, clean,
                transition, normal, auxSpine);
}

std::shared_ptr<workplane>
workplane::sweep(const topo::wire &path, bool multisection, bool makeSolid,
                 bool isFrenet, bool combine, bool clean,
                 const transition_mode &transition,
                 const boost::optional<topo_vector> &normal,
                 const std::shared_ptr<workplane> &auxSpine) {
  return _sweep(path, multisection, makeSolid, isFrenet, combine, clean,
                transition, normal, auxSpine);
}

std::shared_ptr<workplane>
workplane::sweep(const topo::edge &path, bool multisection, bool makeSolid,
                 bool isFrenet, bool combine, bool clean,
                 const transition_mode &transition,
                 const boost::optional<topo_vector> &normal,
                 const std::shared_ptr<workplane> &auxSpine) {
  return _sweep(path, multisection, makeSolid, isFrenet, combine, clean,
                transition, normal, auxSpine);
}

std::shared_ptr<workplane> workplane::_sweep(
    boost::variant<std::reference_wrapper<workplane>, topo::wire, edge> path,
    bool multisection, bool makeSolid, bool isFrenet, bool combine, bool clean,
    const transition_mode &transition,
    const boost::optional<topo_vector> &normal,
    const std::shared_ptr<workplane> &auxSpine) {
  boost::variant<std::shared_ptr<workplane>, topo::wire, topo::edge> pathWire;
  if (auto wp = boost::get<std::reference_wrapper<workplane>>(&path)) {
    pathWire = wp->get().wire();
  } else if (auto w = boost::get<topo::wire>(&path)) {
    pathWire = *w;
  } else if (auto e = boost::get<edge>(&path)) {
    pathWire = wire::make_wire({*e});
  }

  shape r = _sweep(pathWire, multisection, makeSolid, isFrenet, transition,
                   normal, auxSpine);

  return combine_with_base(r, combine, clean);
}

std::shared_ptr<workplane> workplane::combine_with_base(
    const boost::variant<shape, std::vector<shape>> &obj,
    const combine_mode &mode, bool clean) {
  shape newS;
  auto smode = boost::get<combine_mode_type>(&mode);
  auto bmode = boost::get<bool>(&mode);

  if (smode || (bmode && *bmode)) {
    shape shp = boost::get<shape>(obj);
    auto shapes = boost::get<std::vector<shape>>(&obj);
    if (shapes) {
      shp = compound::make_compound(*shapes);
    }
    if (*smode == combine_mode_type::cut ||
        *smode == combine_mode_type::subtractive) {
      newS = cut_from_base(shp);
    } else if ((smode && *smode == combine_mode_type::additive) || *bmode) {
      newS = fuse_with_base(shp);
    }
  } else {
    if (auto s = boost::get<shape>(&obj)) {
      newS = *s;
    } else if (auto ss = boost::get<std::vector<shape>>(&obj)) {
      newS = compound::make_compound(*ss);
    }
  }

  if (clean) {
    newS = newS.clean();
  }

  return new_object({newS});
}

shape workplane::fuse_with_base(const shape &obj) {
  shape baseSolid = find_type({shape_object_type::solid}, true, true);
  if (baseSolid) {
    return *topo::fuse({baseSolid, obj});
  } else if (obj.shape_type() == TopAbs_COMPOUND) {
    return obj.cast<compound>()->fuse({});
  }
  return obj;
}

shape workplane::cut_from_base(const shape &obj) {
  shape baseSolid = find_type({shape_object_type::solid}, true, true);
  if (baseSolid) {
    return *topo::cut(baseSolid, obj);
  }
  return obj;
}

std::shared_ptr<workplane>
workplane::combine(bool clean, bool glue, const boost::optional<double> &tol) {
  std::vector<shape> items;
  for (auto &obj : _objects) {
    if (auto s = boost::get<shape>(&obj)) {
      items.push_back(*s);
    }
  }

  if (items.empty()) {
    throw std::runtime_error("No shapes to combine");
  }

  shape s = items[0];
  if (items.size() > 1) {
    std::vector<shape> shapes(items.begin() + 1, items.end());
    shapes.push_back(s);
    s = *topo::fuse(shapes, tol ? *tol : 0.0001, glue);
  }

  if (clean) {
    s = s.clean();
  }

  return new_object({s});
}

std::shared_ptr<workplane> workplane::union_(const workplane &other, bool clean,
                                             bool glue, double tol) {
  return _union_(other, clean, glue, tol);
}

std::shared_ptr<workplane> workplane::union_(const solid &other, bool clean,
                                             bool glue, double tol) {
  return _union_(other, clean, glue, tol);
}

std::shared_ptr<workplane> workplane::union_(const compound &other, bool clean,
                                             bool glue, double tol) {
  return _union_(other, clean, glue, tol);
}

std::shared_ptr<workplane> workplane::_union_(
    boost::variant<std::reference_wrapper<const workplane>, solid, compound>
        toUnion,
    bool clean, bool glue, const boost::optional<double> &tol) {
  std::vector<shape> newS;
  if (auto wp = boost::get<std::reference_wrapper<const workplane>>(&toUnion)) {
    auto solids = wp->get().solids()->vals();
    if (solids.empty()) {
      throw std::runtime_error(
          "Workplane must have at least one solid to union");
    }
    for (auto &obj : solids) {
      if (auto s = boost::get<shape>(&obj)) {
        newS.push_back(*s);
      }
    }
    merge_tags(*wp);
  } else if (auto s = boost::get<solid>(&toUnion)) {
    newS = {*s};
  } else if (auto c = boost::get<compound>(&toUnion)) {
    newS = {*c};
  }

  shape r;
  shape solidRef = find_type({shape_object_type::solid}, true, true);
  if (solidRef) {
    newS.push_back(solidRef);
    r = *topo::fuse(newS, tol ? *tol : 0.0001, glue);
  } else if (newS.size() > 1) {
    r = *topo::fuse(newS, tol ? *tol : 0.0001, glue);
  } else if (!newS.empty()) {
    r = newS[0];
  } else {
    throw std::runtime_error("No shapes to union");
  }

  if (clean) {
    r = r.clean();
  }

  return new_object({r});
}

std::shared_ptr<workplane> workplane::cut(const workplane &other, bool clean,
                                          double tol) {
  return _cut(other, clean, tol);
}

std::shared_ptr<workplane> workplane::cut(const solid &other, bool clean,
                                          double tol) {
  return _cut(other, clean, tol);
}

std::shared_ptr<workplane> workplane::cut(const compound &other, bool clean,
                                          double tol) {
  return _cut(other, clean, tol);
}

std::shared_ptr<workplane> workplane::_cut(
    boost::variant<std::reference_wrapper<const workplane>, solid, compound>
        toCut,
    bool clean, const boost::optional<double> &tol) {
  solid solidRef = find_solid(true, true);

  std::vector<shape> solidToCut;
  if (auto wp = boost::get<std::reference_wrapper<const workplane>>(&toCut)) {
    solidToCut = select_shapes(wp->get().vals());
    merge_tags(*wp);
  } else if (auto s = boost::get<solid>(&toCut)) {
    solidToCut = {*s};
  } else if (auto c = boost::get<compound>(&toCut)) {
    solidToCut = {*c};
  } else {
    throw std::runtime_error("Invalid type for cutting");
  }

  shape newS = *topo::cut(solidRef, solidToCut, tol ? *tol : 0.0001);
  if (clean) {
    newS = newS.clean();
  }

  return new_object({newS});
}

std::shared_ptr<workplane> workplane::intersect(const workplane &other,
                                                bool clean, double tol) {
  return _intersect(other, clean, tol);
}

std::shared_ptr<workplane> workplane::intersect(const solid &other, bool clean,
                                                double tol) {
  return _intersect(other, clean, tol);
}

std::shared_ptr<workplane> workplane::intersect(const compound &other,
                                                bool clean, double tol) {
  return _intersect(other, clean, tol);
}

std::shared_ptr<workplane> workplane::_intersect(
    boost::variant<std::reference_wrapper<const workplane>, solid, compound>
        toIntersect,
    bool clean, const boost::optional<double> &tol) {
  solid solidRef = find_solid(true, true);

  std::vector<shape> solidToIntersect;
  if (auto wp =
          boost::get<std::reference_wrapper<const workplane>>(&toIntersect)) {
    solidToIntersect = select_shapes(wp->get().vals());
    merge_tags(*wp);
  } else if (auto s = boost::get<solid>(&toIntersect)) {
    solidToIntersect = {*s};
  } else if (auto c = boost::get<compound>(&toIntersect)) {
    solidToIntersect = {*c};
  } else {
    throw std::runtime_error("Invalid type for intersection");
  }

  shape newS =
      *topo::intersect(solidRef, solidToIntersect, tol ? *tol : 0.0001);
  if (clean) {
    newS = newS.clean();
  }

  return new_object({newS});
}

std::shared_ptr<workplane>
workplane::cut_blind(double distance, bool clean, bool both,
                     const boost::optional<double> &taper) {
  return _cut_blind(distance, clean, both, taper);
}

std::shared_ptr<workplane>
workplane::cut_blind(face_index_type untilFace, bool clean, bool both,
                     const boost::optional<double> &taper) {
  return _cut_blind(untilFace, clean, both, taper);
}

std::shared_ptr<workplane>
workplane::cut_blind(const face &untilFace, bool clean, bool both,
                     const boost::optional<double> &taper) {
  return _cut_blind(untilFace, clean, both, taper);
}

std::shared_ptr<workplane>
workplane::_cut_blind(boost::variant<double, face_index_type, face> until,
                      bool clean, bool both,
                      const boost::optional<double> &taper) {
  shape s;
  if (auto dist = boost::get<double>(&until)) {
    shape toCut = _extrude(*dist, both, taper, {}, false);
    solid solidRef = find_solid();
    s = *topo::cut(solidRef, toCut);
  } else if (auto tp = boost::get<face_index_type>(&until)) {
    int faceIndex = static_cast<int>(*tp);
    s = _extrude(boost::none, both, taper,
                 boost::make_optional<boost::variant<int, face>>(faceIndex),
                 false);
  } else if (auto f = boost::get<face>(&until)) {
    s = _extrude(boost::none, both, taper,
                 boost::make_optional<boost::variant<int, face>>(*f), false);
  } else {
    throw std::runtime_error("Invalid until argument type");
  }

  if (clean) {
    s = s.clean();
  }

  return new_object({s});
}

std::shared_ptr<workplane> workplane::cut_thru_all(bool clean, double taper) {
  solid solidRef = find_solid();
  auto faces = get_faces();

  if (faces.empty()) {
    throw std::runtime_error("No pending wires to cut with");
  }

  shape s = *topo::dprism(solidRef, nullptr, faces, boost::none, taper, nullptr,
                          true, false);
  if (clean) {
    s = s.clean();
  }

  return new_object({s});
}

std::shared_ptr<workplane> workplane::loft(bool ruled, bool combine,
                                           bool clean) {
  std::vector<shape> toLoft;
  if (!_ctx->pending_wires().empty()) {
    auto wires = _ctx->pop_pending_wires();
    for (auto &w : wires) {
      toLoft.push_back(w);
    }
  } else {
    auto facesVerts = get_faces_vertices();
    for (auto &el : facesVerts) {
      if (auto v = el.cast<topo::vertex>()) {
        toLoft.push_back(*v);
      } else {
        toLoft.push_back(el.cast<face>()->outer_wire());
      }
    }
  }

  if (toLoft.empty()) {
    throw std::runtime_error("Nothing to loft");
  } else if (toLoft.size() == 1) {
    throw std::runtime_error("More than one wire or face is required");
  }

  shape r = *topo::loft(toLoft, true, ruled);
  return combine_with_base(r, combine, clean);
}

std::vector<face> workplane::get_faces() {
  std::vector<face> rv;
  for (auto &obj : _objects) {
    if (auto sk = boost::get<std::shared_ptr<topo::sketch>>(&obj)) {
      auto faces = (*sk)->get_faces();
      rv.insert(rv.end(), faces.begin(), faces.end());
    } else if (auto shp = boost::get<shape>(&obj)) {
      if (shp->shape_type() == TopAbs_FACE) {
        rv.push_back(*shp->cast<face>());
      } else if (shp->shape_type() == TopAbs_COMPOUND) {
        auto comp = shp->cast<compound>();
        for (auto &subel : comp->children()) {
          if (auto f = subel.cast<topo::face>()) {
            rv.push_back(*f);
          }
        }
      }
    }
  }

  if (rv.empty()) {
    auto wires = _ctx->pop_pending_wires();
    topo::wire wires1;
    if (!wires.empty()) {
      wires1 = wires[0];
    }
    std::vector<topo::wire> wires2;
    if (wires.size() > 1) {
      wires2.insert(wires2.end(), wires.begin() + 1, wires.end());
    }
    rv = face::make_from_wires(wires1, wires2);
  }

  return rv;
}

std::vector<shape> workplane::get_faces_vertices() {
  std::vector<shape> rv;
  for (auto &obj : _objects) {
    if (auto sk = boost::get<std::shared_ptr<topo::sketch>>(&obj)) {
      auto faces = (*sk)->get_faces();
      rv.insert(rv.end(), faces.begin(), faces.end());
    } else if (auto shp = boost::get<shape>(&obj)) {
      if (shp->shape_type() == TopAbs_FACE) {
        rv.push_back(*shp->cast<face>());
      } else if (shp->shape_type() == TopAbs_COMPOUND) {
        auto comp = shp->cast<compound>();
        for (auto &subel : comp->children()) {
          if (auto f = subel.cast<topo::face>()) {
            rv.push_back(*f);
          } else if (auto v = subel.cast<topo::vertex>()) {
            rv.push_back(*v);
          }
        }
      } else if (shp->shape_type() == TopAbs_VERTEX) {
        rv.push_back(*shp->cast<vertex>());
      }
    }
  }
  return rv;
}

shape workplane::_extrude(const boost::optional<double> &distance, bool both,
                          const boost::optional<double> &taper,
                          boost::optional<boost::variant<int, face>> upToFace,
                          bool additive) {
  auto faces = get_faces();

  if (taper) {
    for (auto &face : faces) {
      if (!face.inner_wires().empty()) {
        throw std::runtime_error(
            "Inner wires not allowed with tapered extrusion");
      }
    }
  }

  gp_Vec eDir;
  if (upToFace) {
    eDir = _plane->z_dir();
  } else if (distance) {
    eDir = _plane->z_dir().multiply(*distance);
  }

  double taperAngle = taper ? *taper : 0.0;
  flywave::topo::intersection_direction direction =
      additive ? flywave::topo::intersection_direction::AlongAxis
               : flywave::topo::intersection_direction::Opposite;

  if (upToFace) {
    shape res = find_solid();
    for (auto &face : faces) {
      topo::face limitFace;
      if (auto idx = boost::get<int>(&*upToFace)) {
        auto facesList = _get_intersected_faces(face, eDir, direction, both);
        if (res.cast<topo::solid>()->is_inside(face.outer_wire().center()) &&
            additive && *idx == 0) {
          *idx = 1;
        }
        limitFace = facesList[*idx];
      } else {
        limitFace = boost::get<topo::face>(*upToFace);
      }

      res = *topo::dprism(res, nullptr, {face}, boost::none, taperAngle,
                          &limitFace, additive);

      if (both) {
        auto facesList2 = _get_intersected_faces(face, eDir.Multiplied(-1.0),
                                                 direction, both);
        auto limitFace2 = facesList2[boost::get<int>(*upToFace)];
        res = *topo::dprism(res, nullptr, {face}, boost::none, taperAngle,
                            &limitFace2, additive);
      }
    }
    return res;
  } else {
    std::vector<shape> toFuse;
    for (auto &face : faces) {
      shape s1 = *topo::extrude_linear(face, eDir, taperAngle);
      if (both) {
        shape s2 =
            *topo::extrude_linear(face, eDir.Multiplied(-1.0), taperAngle);
        toFuse.push_back(*topo::fuse({s1, s2}, true));
      } else {
        toFuse.push_back(s1);
      }
    }
    return compound::make_compound(toFuse);
  }
}

std::vector<face> workplane::_get_intersected_faces(
    const face &face, const gp_Vec &eDir,
    const flywave::topo::intersection_direction &direction, bool both) {
  auto facesList = topo::faces_intersected_by_line(find_solid(), face.center(),
                                                   eDir, 1.0E-4, direction);

  if (facesList.empty() && both) {
    throw std::runtime_error(
        "Couldn't find a face to extrude/cut to for both directions");
  }

  if (facesList.empty()) {
    facesList = topo::faces_intersected_by_line(
        find_solid(), face.center(), eDir.Multiplied(-1.0), 1.0E-4, direction);
    if (facesList.empty()) {
      throw std::runtime_error("Couldn't find a face to extrude/cut to. Check "
                               "workplane orientation");
    }
  }
  return facesList;
}

shape workplane::_revolve(double angleDegrees, const gp_Pnt &axisStart,
                          const gp_Pnt &axisEnd) {
  std::vector<shape> toFuse;
  for (auto &f : get_faces()) {
    toFuse.push_back(*topo::revolve(f, angleDegrees, axisStart, axisEnd));
  }
  return compound::make_compound(toFuse);
}

shape workplane::_sweep(
    boost::variant<std::shared_ptr<workplane>, topo::wire, topo::edge> &path,
    bool multisection, bool makeSolid, bool isFrenet,
    const transition_mode &transition,
    const boost::optional<topo_vector> &normal,
    const std::shared_ptr<workplane> &auxSpine) {
  topo::shape pathWire;
  if (auto wp = boost::get<std::shared_ptr<workplane>>(&path)) {
    auto val = (*wp)->val();
    if (auto shp = boost::get<shape>(&val)) {
      if (shp->shape_type() == TopAbs_WIRE) {
        pathWire = *shp->cast<topo::wire>();
      } else if (shp->shape_type() == TopAbs_EDGE) {
        pathWire = wire::make_wire({*shp->cast<topo::edge>()});
      }
    }
  } else if (auto w = boost::get<topo::wire>(&path)) {
    pathWire = *w;
  } else if (auto e = boost::get<edge>(&path)) {
    pathWire = wire::make_wire({*e});
  }

  shape mode;
  if (normal) {
    mode = vertex::make_vertex(normal->to_vec());
  } else if (auxSpine) {
    auto val = auxSpine->val();

    if (auto shp = boost::get<topo::shape>(&val)) {
      if (shp->shape_type() == TopAbs_WIRE) {
        mode = *shp->cast<topo::wire>();
      } else if (shp->shape_type() == TopAbs_EDGE) {
        mode = *shp->cast<topo::edge>();
      }
    } else {
      throw std::runtime_error("Invalid auxSpine type");
    }
  }

  std::vector<shape> toFuse;
  if (!multisection) {
    for (auto &f : get_faces()) {
      toFuse.push_back(
          *topo::sweep(f, pathWire, makeSolid, isFrenet, &mode, transition));
    }
  } else {
    std::vector<shape> sections;
    if (!_ctx->pending_wires().empty()) {
      auto wires = _ctx->pop_pending_wires();
      for (auto &w : wires) {
        sections.push_back(w);
      }
    } else {
      for (auto &f : get_faces()) {
        sections.push_back(f.outer_wire());
      }
    }
    toFuse.push_back(
        *topo::sweep_multi(sections, pathWire, makeSolid, isFrenet, &mode));
  }

  return compound::make_compound(toFuse);
}

std::shared_ptr<workplane>
workplane::interp_plate(const std::vector<gp_Pnt> &points, double thickness,
                        bool combine, bool clean, int degree, int nbPtsOnCur,
                        int nbIter, bool anisotropy, double tol2d, double tol3d,
                        double tolAng, double tolCurv, int maxDeg,
                        int maxSegments) {
  return _interp_plate(points, {}, thickness, combine, clean, degree,
                       nbPtsOnCur, nbIter, anisotropy, tol2d, tol3d, tolAng,
                       tolCurv, maxDeg, maxSegments);
}

std::shared_ptr<workplane> workplane::interp_plate(
    const std::vector<edge> &edges, const std::vector<gp_Pnt> &points,
    double thickness, bool combine, bool clean, int degree, int nbPtsOnCur,
    int nbIter, bool anisotropy, double tol2d, double tol3d, double tolAng,
    double tolCurv, int maxDeg, int maxSegments) {
  return _interp_plate(edges, points, thickness, combine, clean, degree,
                       nbPtsOnCur, nbIter, anisotropy, tol2d, tol3d, tolAng,
                       tolCurv, maxDeg, maxSegments);
}

std::shared_ptr<workplane>
workplane::interp_plate(const workplane &wp, const std::vector<gp_Pnt> &points,
                        double thickness, bool combine, bool clean, int degree,
                        int nbPtsOnCur, int nbIter, bool anisotropy,
                        double tol2d, double tol3d, double tolAng,
                        double tolCurv, int maxDeg, int maxSegments) {
  return _interp_plate(wp, points, thickness, combine, clean, degree,
                       nbPtsOnCur, nbIter, anisotropy, tol2d, tol3d, tolAng,
                       tolCurv, maxDeg, maxSegments);
}
std::shared_ptr<workplane>
workplane::_interp_plate(boost::variant<std::vector<gp_Pnt>, std::vector<edge>,
                                        std::reference_wrapper<const workplane>>
                             surf_edges,
                         const std::vector<gp_Pnt> &surf_pts, double thickness,
                         bool combine, bool clean, int degree, int nbPtsOnCur,
                         int nbIter, bool anisotropy, double tol2d,
                         double tol3d, double tolAng, double tolCurv,
                         int maxDeg, int maxSegments) {
  std::vector<boost::variant<edge, topo::wire>> edges;
  std::vector<gp_Pnt> points;

  if (auto wp =
          boost::get<std::reference_wrapper<const workplane>>(&surf_edges)) {
    for (auto &obj : wp->get().edges()->_objects) {
      if (auto shp = boost::get<shape>(&obj)) {
        if (shp->shape_type() == TopAbs_EDGE) {
          edges.push_back(*shp->cast<edge>());
        }
      }
    }
  } else if (auto pts = boost::get<std::vector<gp_Pnt>>(&surf_edges)) {
    points = *pts;
  } else if (auto edgs = boost::get<std::vector<edge>>(&surf_edges)) {
    for (auto &e : *edgs) {
      edges.push_back(e);
    }
  }

  std::vector<boost::variant<edge, topo::wire, gp_Pnt>> constraints;
  for (auto pnt : surf_pts) {
    constraints.push_back(pnt);
  }

  face f;
  if (!points.empty()) {
    topo::wire w = topo::wire::make_polygon(points, false);
    f = face::make_face({w}, constraints, GeomAbs_C0, degree, nbPtsOnCur,
                        nbIter, anisotropy, tol2d, tol3d, tolAng, tolCurv,
                        maxDeg, maxSegments);
  } else {
    f = face::make_face(edges, constraints, GeomAbs_C0, degree, nbPtsOnCur,
                        nbIter, anisotropy, tol2d, tol3d, tolAng, tolCurv,
                        maxDeg, maxSegments);
  }

  shape s = thickness > 0 ? f.thicken(thickness) : shape(f);
  return _eachpoint([s](const topo_location &loc) { return s.moved(loc); },
                    true, combine, clean);
}

std::shared_ptr<workplane> workplane::box(double length, double width,
                                          double height,
                                          const std::array<bool, 3> &center,
                                          bool combine, bool clean) {
  return _box(length, width, height,
              std::make_tuple(center[0], center[1], center[2]), combine, clean);
}

std::shared_ptr<workplane> workplane::box(double length, double width,
                                          double height, bool centerAll,
                                          bool combine, bool clean) {
  return _box(length, width, height, centerAll, combine, clean);
}

std::shared_ptr<workplane> workplane::_box(
    double length, double width, double height,
    const boost::variant<bool, std::tuple<bool, bool, bool>> &centered,
    bool combine, bool clean) {
  std::tuple<bool, bool, bool> centerTuple;
  if (centered.type() == typeid(bool)) {
    bool c = boost::get<bool>(centered);
    centerTuple = std::make_tuple(c, c, c);
  } else {
    centerTuple = boost::get<std::tuple<bool, bool, bool>>(centered);
  }

  gp_Vec offset;
  if (std::get<0>(centerTuple)) {
    offset += gp_Vec(-length / 2, 0, 0);
  }
  if (std::get<1>(centerTuple)) {
    offset += gp_Vec(0, -width / 2, 0);
  }
  if (std::get<2>(centerTuple)) {
    offset += gp_Vec(0, 0, -height / 2);
  }

  shape box = solid::make_solid_from_box(
      gp_Pnt(offset.X(), offset.Y(), offset.Z()), width, height, length);

  return _eachpoint([box](const topo_location &loc) { return box.moved(loc); },
                    true, combine, clean);
}

std::shared_ptr<workplane>
workplane::sphere(double radius, const gp_Vec &direct, double angle1,
                  double angle2, double angle3,
                  const std::array<bool, 3> &center, bool combine, bool clean) {
  return _sphere(radius, direct, angle1, angle2, angle3,
                 std::make_tuple(center[0], center[1], center[2]), combine,
                 clean);
}

std::shared_ptr<workplane> workplane::sphere(double radius,
                                             const gp_Vec &direct,
                                             double angle1, double angle2,
                                             double angle3, bool centerAll,
                                             bool combine, bool clean) {
  return _sphere(radius, direct, angle1, angle2, angle3, centerAll, combine,
                 clean);
}

std::shared_ptr<workplane> workplane::_sphere(
    double radius, const gp_Vec &direct, double angle1, double angle2,
    double angle3,
    const boost::variant<bool, std::tuple<bool, bool, bool>> &centered,
    bool combine, bool clean) {
  std::tuple<bool, bool, bool> centerTuple;
  if (centered.type() == typeid(bool)) {
    bool c = boost::get<bool>(centered);
    centerTuple = std::make_tuple(c, c, c);
  } else {
    centerTuple = boost::get<std::tuple<bool, bool, bool>>(centered);
  }

  gp_Vec offset;
  if (!std::get<0>(centerTuple)) {
    offset += gp_Vec(radius, 0, 0);
  }
  if (!std::get<1>(centerTuple)) {
    offset += gp_Vec(0, radius, 0);
  }
  if (!std::get<2>(centerTuple)) {
    offset += gp_Vec(0, 0, radius);
  }

  shape s = solid::make_solid_from_sphere(
      gp_Ax2(gp_Pnt(offset.X(), offset.Y(), offset.Z()), direct), radius,
      angle1, angle2, angle3);

  return _eachpoint([s](const topo_location &loc) { return s.moved(loc); },
                    true, combine, clean);
}

std::shared_ptr<workplane>
workplane::cylinder(double height, double radius, const gp_Vec &direct,
                    double angle, const std::array<bool, 3> &center,
                    bool combine, bool clean) {
  return _cylinder(height, radius, direct, angle,
                   std::make_tuple(center[0], center[1], center[2]), combine,
                   clean);
}

std::shared_ptr<workplane> workplane::cylinder(double height, double radius,
                                               const gp_Vec &direct,
                                               double angle, bool centerAll,
                                               bool combine, bool clean) {
  return _cylinder(height, radius, direct, angle, centerAll, combine, clean);
}

std::shared_ptr<workplane> workplane::_cylinder(
    double height, double radius, const gp_Vec &direct, double angle,
    const boost::variant<bool, std::tuple<bool, bool, bool>> &centered,
    bool combine, bool clean) {
  std::tuple<bool, bool, bool> centerTuple;
  if (centered.type() == typeid(bool)) {
    bool c = boost::get<bool>(centered);
    centerTuple = std::make_tuple(c, c, c);
  } else {
    centerTuple = boost::get<std::tuple<bool, bool, bool>>(centered);
  }

  gp_Vec offset;
  if (!std::get<0>(centerTuple)) {
    offset += gp_Vec(radius, 0, 0);
  }
  if (!std::get<1>(centerTuple)) {
    offset += gp_Vec(0, radius, 0);
  }
  if (std::get<2>(centerTuple)) {
    offset += gp_Vec(0, 0, -height / 2);
  }

  shape s =
      solid::make_solid_from_cylinder(
          gp_Ax2(gp_Pnt(offset.X(), offset.Y(), offset.Z()), gp_Dir(0, 0, 1)),
          radius, height, angle)
          .moved(topo_plane(gp_Pnt(), direct).location());

  return _eachpoint([s](const topo_location &loc) { return s.moved(loc); },
                    true, combine, clean);
}

std::shared_ptr<workplane>
workplane::wedge(double dx, double dy, double dz, double xmin, double zmin,
                 double xmax, double zmax, const gp_Pnt &pnt, const gp_Vec &dir,
                 const std::array<bool, 3> &center, bool combine, bool clean) {
  return _wedge(dx, dy, dz, xmin, zmin, xmax, zmax, pnt, dir,
                std::make_tuple(center[0], center[1], center[2]), combine,
                clean);
}

std::shared_ptr<workplane>
workplane::wedge(double dx, double dy, double dz, double xmin, double zmin,
                 double xmax, double zmax, const gp_Pnt &pnt, const gp_Vec &dir,
                 bool centerAll, bool combine, bool clean) {
  return _wedge(dx, dy, dz, xmin, zmin, xmax, zmax, pnt, dir, centerAll,
                combine, clean);
}

std::shared_ptr<workplane> workplane::_wedge(
    double dx, double dy, double dz, double xmin, double zmin, double xmax,
    double zmax, const gp_Pnt &pnt, const gp_Vec &dir,
    const boost::variant<bool, std::tuple<bool, bool, bool>> &centered,
    bool combine, bool clean) {
  std::tuple<bool, bool, bool> centerTuple;
  if (centered.type() == typeid(bool)) {
    bool c = boost::get<bool>(centered);
    centerTuple = std::make_tuple(c, c, c);
  } else {
    centerTuple = boost::get<std::tuple<bool, bool, bool>>(centered);
  }

  gp_Vec offset;
  if (std::get<0>(centerTuple)) {
    offset += gp_Vec(-dx / 2, 0, 0);
  }
  if (std::get<1>(centerTuple)) {
    offset += gp_Vec(0, -dy / 2, 0);
  }
  if (std::get<2>(centerTuple)) {
    offset += gp_Vec(0, 0, -dz / 2);
  }

  shape w = solid::make_solid_from_wedge(
      gp_Ax2(gp_Pnt(offset.X(), offset.Y(), offset.Z()), dir), dx, dy, dz, xmin,
      zmin, xmax, zmax);

  return _eachpoint([w](const topo_location &loc) { return w.moved(loc); },
                    true, combine, clean);
}

std::shared_ptr<workplane> workplane::clean() {
  std::vector<shape_object> cleanObjects;
  for (auto &obj : _objects) {
    if (auto shp = boost::get<shape>(&obj)) {
      cleanObjects.push_back(shp->clean());
    } else {
      cleanObjects.push_back(obj);
    }
  }
  return new_object(cleanObjects);
}

std::shared_ptr<workplane>
workplane::text(const std::string &txt, double fontsize, double distance,
                bool cut, bool combine, bool clean, const std::string &font,
                const boost::optional<std::string> &fontPath,
                const font_kind &kind, const horizontal_align &halign,
                const vertical_align &valign) {

  if (cut) {
    combine = true; // "cut" mode
  }

  shape r = topo::compound::make_text(txt, fontsize, distance, font, *fontPath,
                                      kind, halign, valign, *_plane);

  return combine_with_base(r, combine, clean);
}

std::shared_ptr<workplane> workplane::section(double height) {
  shape solidRef = find_solid(true, true);

  if (!solidRef) {
    throw std::runtime_error("No solid found to section");
  }

  gp_Pnt basePnt = _plane->origin() + _plane->z_dir() * height;
  face plane = face::make_plane(basePnt, _plane->z_dir());

  shape r = *topo::intersect(solidRef, plane);

  return new_object({r});
}

workplane &workplane::to_pending() {
  for (auto &obj : _objects) {
    if (auto shp = boost::get<shape>(&obj)) {
      if (shp->shape_type() == TopAbs_WIRE) {
        _ctx->pending_wires().push_back(*shp->cast<topo::wire>());
      } else if (shp->shape_type() == TopAbs_EDGE) {
        _ctx->pending_edges().push_back(*shp->cast<topo::edge>());
      }
    }
  }
  return *this;
}

std::shared_ptr<workplane> workplane::offset2d(double d,
                                               const GeomAbs_JoinType &kind,
                                               bool forConstruction) {
  std::vector<topo::wire> ws = _consolidate_wires();
  std::vector<topo::wire> rv;

  for (auto &w : ws) {
    auto offsetWires = w.offset2d(d, kind);
    rv.insert(rv.end(), offsetWires.begin(), offsetWires.end());
  }

  _ctx->pending_edges().clear();
  if (forConstruction) {
    for (auto &wire : rv) {
      wire.set_for_construction(true);
    }
    _ctx->pending_wires().clear();
  } else {
    _ctx->set_pending_wires(rv);
  }

  return new_shape_object(rv);
}

std::vector<topo_location> workplane::locs() {
  std::vector<topo_location> locs;

  for (auto &obj : _objects) {
    if (auto vec = boost::get<topo_vector>(&obj)) {
      locs.push_back(topo_location((gp_Pln)(*_plane), *vec));
    } else if (auto shp = boost::get<shape>(&obj)) {
      locs.push_back(topo_location((gp_Pln)(*_plane), shp->centre_of_mass()));
    } else if (auto loc = boost::get<topo_location>(&obj)) {
      locs.push_back(*loc);
    }
  }

  if (locs.empty()) {
    locs.push_back(_plane->location());
  }

  return locs;
}

void workplane::add_error(const std::string &error) { _ctx->set_error(error); }

std::shared_ptr<topo::sketch> workplane::sketch() {
  std::shared_ptr<workplane> parent = new_object({});

  std::shared_ptr<topo::sketch> rv =
      std::make_shared<topo::sketch>(parent, locs());
  parent->_objects.push_back(rv);
  return rv;
}

std::shared_ptr<workplane> workplane::place_sketch(
    const std::vector<std::shared_ptr<topo::sketch>> &sketches) {
  std::vector<topo::shape_object> rv;

  for (auto &s : sketches) {
    auto s_new = s->copy();
    s_new->locs_ = locs();
    rv.push_back(s_new);
  }

  return new_object(rv);
}

std::shared_ptr<workplane> workplane::operator[](int index) {
  if (index < 0 || static_cast<size_t>(index) >= _objects.size()) {
    throw std::out_of_range("Index out of range");
  }
  return new_object({_objects[index]});
}

std::shared_ptr<workplane>
workplane::operator[](const std::vector<int> &indices) {
  std::vector<shape_object> selected;
  for (int idx : indices) {
    if (idx < 0 || static_cast<size_t>(idx) >= _objects.size()) {
      throw std::out_of_range("Index out of range");
    }
    selected.push_back(_objects[idx]);
  }
  return new_object(selected);
}

std::shared_ptr<workplane>
workplane::operator[](const std::pair<int, int> &range) {
  auto start = range.first;
  auto end = range.second;
  if (start < 0 || static_cast<size_t>(end) > _objects.size() || start > end) {
    throw std::out_of_range("Invalid range");
  }

  std::vector<shape_object> selected;
  for (int i = start; i < end; ++i) {
    selected.push_back(_objects[i]);
  }
  return new_object(selected);
}

std::shared_ptr<workplane>
workplane::filter(const std::function<bool(const shape_object &)> &predicate) {
  std::vector<shape_object> filtered;
  std::copy_if(_objects.begin(), _objects.end(), std::back_inserter(filtered),
               predicate);
  return new_object(filtered);
}

std::shared_ptr<workplane> workplane::map(
    const std::function<shape_object(const shape_object &)> &mapper) {
  std::vector<shape_object> mapped;
  std::transform(_objects.begin(), _objects.end(), std::back_inserter(mapped),
                 mapper);
  return new_object(mapped);
}

std::shared_ptr<workplane>
workplane::apply(const std::function<std::vector<shape_object>(
                     const std::vector<shape_object> &)> &applier) {
  return new_object(applier(_objects));
}

std::shared_ptr<workplane> workplane::sort(
    const std::function<bool(const shape_object &, const shape_object &)>
        &comparator) {
  std::vector<shape_object> sorted = _objects;
  std::sort(sorted.begin(), sorted.end(), comparator);
  return new_object(sorted);
}

std::shared_ptr<workplane> workplane::invoke(
    const boost::variant<std::function<std::shared_ptr<workplane>(workplane &)>,
                         std::function<void(workplane &)>,
                         std::function<void()>> &func) {
  if (func.type() == typeid(std::function<void()>)) {
    boost::get<std::function<void()>>(func)();
    return this->shared_from_this();
  } else if (func.type() == typeid(std::function<void(workplane &)>)) {
    boost::get<std::function<void(workplane &)>>(func)(*this);
    return this->shared_from_this();
  } else {
    auto result =
        boost::get<std::function<std::shared_ptr<workplane>(workplane &)>>(
            func)(*this);
    return result;
  }
}

std::vector<shape> workplane::shapes() const {
  std::vector<shape> result;
  for (auto &obj : _objects) {
    if (auto shp = boost::get<shape>(&obj)) {
      result.push_back(*shp);
    } else if (auto wp = boost::get<std::shared_ptr<topo::sketch>>(&obj)) {
      if ((*wp)->faces_) {
        result.push_back(*(*wp)->faces_);
      }
    }
  }
  return result;
}

workplane &workplane::export_to(const std::string &path) {
  compound comp = compound::make_compound(shapes());
  comp.export_step(path);
  return *this;
}

} // namespace topo
} // namespace flywave
