#include "workplane.hh"

#include <unordered_set>

namespace flywave {
namespace topo {
namespace {

boost::optional<shape> selectShape(const shape_object &object) {
  if (auto s = boost::get<shape>(&object)) {
    return *s;
  }
  return boost::none;
}

std::vector<shape> selectShapes(const std::vector<shape_object> &objects) {
  std::vector<shape> result;
  for (const auto &obj : objects) {
    if (auto s = boost::get<shape>(&obj)) {
      result.push_back(*s);
    }
  }
  return result;
}
} // namespace

workplane::workplane()
    : _plane(nullptr), _parent(nullptr), _ctx(std::make_shared<context>()) {}

workplane::workplane(topo_plane plane, topo_vector *origin, shape_object obj)
    : _plane(std::make_shared<topo_plane>(plane)), _parent(nullptr),
      _ctx(std::make_shared<context>()) {
  if (!obj.empty()) {
    _objects.push_back(obj);
  }
}

workplane::workplane(const std::string &planeName, topo_vector *origin,
                     shape_object obj)
    : _parent(nullptr), _ctx(std::make_shared<context>()) {
  _plane = std::make_shared<topo_plane>(
      topo_plane::named(planeName, origin ? *origin : topo_vector(0, 0, 0)));
  if (!obj.empty()) {
    _objects.push_back(obj);
  }
}

workplane &workplane::tag(const std::string &name) {
  _tag = name;
  _ctx->tags()[name] = shared_from_this();
  return *this;
}

std::vector<shape> workplane::collectProperty(const std::string &propName) {
  std::vector<shape> result;
  std::unordered_map<shape, bool> seen; // used as an ordered set

  for (auto &obj : _objects) {
    if (propName == "Solids") {
      if (auto s = boost::get<shape>(&obj)) {
        if (s->shape_type() == "Compound") {
          for (auto &k : s->compounds()) {
            if (seen.find(k) == seen.end()) {
              seen[k] = true;
              result.push_back(k);
            }
          }
        }
      }
    }
    /**
        // Check if object has the property
        // This is a simplified version - in real code you'd need proper type
        // checking and property access based on the actual shape types
        if (auto shp = boost::get<shape>(&obj)) {
          if (shp->has_property(propName)) {
            for (auto &k : shp->get_property(propName)) {
              if (seen.find(k) == seen.end()) {
                seen[k] = true;
                result.push_back(k);
              }
            }
          }
        } */
  }

  return result;
}

std::shared_ptr<workplane> workplane::split(bool keepTop, bool keepBottom) {
  if (!keepTop && !keepBottom) {
    throw std::runtime_error("You have to keep at least one half");
  }

  solid &s = findSolid();
  double maxDim = s.bbox().GetDiagonalLength() * 10.0;

  // Create cutting boxes
  auto topCutBox = this->rect(maxDim, maxDim)->_extrude(maxDim);
  auto bottomCutBox = this->rect(maxDim, maxDim)->_extrude(-maxDim);

  // Perform cuts
  auto top = s.cuted({bottomCutBox});
  auto bottom = s.cuted({topCutBox});

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

  return this->newObject(rv);
}

std::shared_ptr<workplane> workplane::split(const shape &splitter) {
  solid &s = findSolid();
  std::vector<shape> tools = {splitter};
  std::vector<shape_object> rv = {s.splited(tools)};
  return this->newObject(rv);
}

std::shared_ptr<workplane> workplane::split(const workplane &splitter) {
  solid &s = findSolid();
  std::vector<shape> tools;
  for (const auto &obj : splitter.vals()) {
    if (const shape *sh = boost::get<shape>(&obj)) {
      tools.push_back(*sh);
    }
  }

  std::vector<shape_object> rv = {s.splited(tools)};
  this->mergeTags(splitter);
  return this->newObject(rv);
}

std::vector<std::shared_ptr<workplane>> workplane::all() {
  std::vector<std::shared_ptr<workplane>> result;
  for (const auto &obj : _objects) {
    result.push_back(this->newObject({obj}));
  }
  return result;
}

size_t workplane::size() const { return _objects.size(); }

std::vector<shape_object> workplane::vals() const { return _objects; }

// Overload for adding another workplane
workplane &workplane::add(const workplane &other) {
  _objects.insert(_objects.end(), other._objects.begin(), other._objects.end());
  mergeTags(other);
  return *this;
}

// Overload for adding a single shape object
workplane &workplane::add(const shape_object &obj) {
  _objects.push_back(obj);
  return *this;
}

// Overload for adding a vector of shape objects
workplane &workplane::add(const std::vector<shape_object> &objs) {
  _objects.insert(_objects.end(), objs.begin(), objs.end());
  return *this;
}

shape_object workplane::val() const {
  if (!_objects.empty()) {
    return _objects[0];
  }
  return _plane ? _plane->origin : topo_vector(0, 0, 0);
}

std::shared_ptr<workplane> workplane::getTagged(const std::string &name) {
  auto it = _ctx->tags().find(name);
  if (it == _ctx->tags().end()) {
    throw std::runtime_error("No Workplane object named " + name + " in chain");
  }
  return it->second;
}

workplane &workplane::mergeTags(const workplane &other) {
  if (_ctx != other._ctx) {
    // Merge tags from other context into this one
    _ctx->tags().insert(other._ctx->tags().begin(), other._ctx->tags().end());
  }
  return *this;
}

shape workplane::value() const {
  shape_object v = val();

  if (const auto *sk = boost::get<std::shared_ptr<topo::sketch>>(&v)) {
    return *(*sk)->faces_; // Assuming sketch has a faces() method returning
                           // TopoDS_Shape
  } else if (const shape *sh = boost::get<shape>(&v)) {
    return sh->value(); // Assuming shape has a wrapped() method
  } else {
    throw std::runtime_error("Unsupported object type for toOCC conversion");
  }
}

std::shared_ptr<workplane> workplane::create(double offset, bool invert,
                                             const std::string &centerOption,
                                             topo_vector *origin) {
  // Validate center option
  static const std::unordered_set<std::string> validOptions = {
      "CenterOfMass", "ProjectedOrigin", "CenterOfBoundBox"};
  if (validOptions.find(centerOption) == validOptions.end()) {
    throw std::runtime_error("Undefined centerOption value provided.");
  }
  gp_Pnt center_;
  gp_Dir xDir;
  gp_Vec normal;

  // Check for multiple objects
  if (_objects.size() > 1) {
    std::vector<face> faces;
    for (auto &obj : _objects) {
      if (auto f = boost::get<shape>(&obj)) {
        if (f->shape_type() == "Face") {
          faces.push_back(*f->cast<topo::face>());
        }
      }
    }

    if (faces.size() != _objects.size()) {
      throw std::runtime_error(
          "If multiple objects selected, they all must be planar faces.");
    }

    // Check if all faces are coplanar
    if (!areFacesCoplanar(faces)) {
      throw std::runtime_error("Selected faces must be co-planar.");
    }

    if (centerOption == "CenterOfMass" || centerOption == "ProjectedOrigin") {
      center_ = topo::combined_center(selectShapes(_objects));
    } else if (centerOption == "CenterOfBoundBox") {
      center_ = topo::combined_center_of_bound_box(selectShapes(_objects));
    }

    normal = faces[0].normal_at();
    xDir = computeXDir(normal);
  } else {
    shape_object obj = val();

    if (auto shp = boost::get<shape>(&obj)) {
      if (shp->shape_type() == "Face") {
        auto f = *shp->cast<topo::face>();
        if (centerOption == "CenterOfMass" ||
            centerOption == "ProjectedOrigin") {
          center_ = f.center();
        } else if (centerOption == "CenterOfBoundBox") {
          center_ = f.centre_of_mass();
        }
        normal = f.normal_at(&center_);
        xDir = computeXDir(normal);
      } else {
        if (centerOption == "CenterOfMass" ||
            centerOption == "ProjectedOrigin") {
          center_ = shp->centre_of_mass();
        } else if (centerOption == "CenterOfBoundBox") {
          center_ = shp->center_of_bound_box();
        }

        shape_object parentVal = _parent ? _parent->val() : shape_object();
        if (auto parentFace = boost::get<shape>(&parentVal)) {
          if (parentFace->shape_type() == "Face") {
            normal = parentFace->cast<topo::face>()->normal_at(&center_);
            xDir = computeXDir(normal);
          }
        } else {
          normal = _plane->getZDir();
          xDir = _plane->getXDir();
        }
      }
    } else if (auto vec = boost::get<topo_vector>(&obj)) {
      if (centerOption == "CenterOfMass" || centerOption == "ProjectedOrigin") {
        center_ = *vec;
      } else if (centerOption == "CenterOfBoundBox") {
        center_ = *vec;
      }

      shape_object parentVal = _parent ? _parent->val() : shape_object();
      if (auto parentFace = boost::get<shape>(&parentVal)) {
        if (parentFace->shape_type() == "Face") {
          normal = parentFace->cast<topo::face>()->normal_at(&center_);
          xDir = computeXDir(normal);
        }
      } else {
        normal = _plane->getZDir();
        xDir = _plane->getXDir();
      }
    } else {
      throw std::runtime_error(
          "Needs a face or a vertex or point on a work plane");
    }
  }

  // Handle ProjectedOrigin case
  if (centerOption == "ProjectedOrigin") {
    topo_vector orig = origin ? *origin : _plane->getOrigin();
    center_ = orig.projectToPlane(topo_plane(center_, xDir, normal));
  }

  // Invert if requested
  if (invert) {
    normal = normal.Multiplied(-1.0);
  }

  // Apply offset
  gp_Vec offsetVector = normal.Normalized().Multiplied(offset);
  gp_Pnt offsetCenter = center_.Translated(offsetVector);

  // Create new workplane
  topo_plane newPlane(offsetCenter, xDir, normal);
  auto s = std::make_shared<workplane>(newPlane);
  s->_parent = this->shared_from_this();
  s->_ctx = _ctx;

  return s;
}

// Helper methods
bool workplane::areFacesCoplanar(const std::vector<face> &faces) const {
  if (faces.empty())
    return true;

  topo_vector p0 = faces[0].center();
  topo_vector n0 = faces[0].normal_at();

  for (size_t i = 1; i < faces.size(); ++i) {
    gp_Pnt p1 = faces[i].center();
    gp_Vec n1 = faces[i].normal_at();

    // Test normals (direction of planes)
    if (!n0.is_equal(n1, _ctx->tolerance())) {
      return false;
    }

    // Test if p1 is on the plane of f0 (offset of planes)
    if (std::abs(n0.dot(p0 - p1)) > _ctx->tolerance()) {
      return false;
    }
  }
  return true;
}

gp_Vec workplane::computeXDir(const gp_Vec &normal) const {
  gp_Vec xd = gp_Vec(0, 0, 1).Crossed(normal);
  if (xd.Magnitude() < _ctx->tolerance()) {
    // Face is parallel with x-y plane, use global x direction
    xd = gp_Vec(1, 0, 0);
  }
  return xd;
}

std::shared_ptr<workplane> workplane::copy_workplane(const workplane &obj) {
  auto out = std::make_shared<workplane>(*obj._plane);
  out->_parent = this->shared_from_this();
  out->_ctx = _ctx;
  return out;
}

std::shared_ptr<workplane>
workplane::workplane_from_tagged(const std::string &name) {
  auto tagged = getTagged(name);
  return copy_workplane(*tagged);
}

std::shared_ptr<workplane> workplane::first() {
  if (_objects.empty()) {
    throw std::runtime_error("No objects in stack");
  }
  return newObject({_objects.front()});
}

std::shared_ptr<workplane> workplane::item(size_t i) {
  if (i >= _objects.size()) {
    throw std::out_of_range("Index out of range");
  }
  return newObject({_objects[i]});
}

std::shared_ptr<workplane> workplane::last() {
  if (_objects.empty()) {
    throw std::runtime_error("No objects in stack");
  }
  return newObject({_objects.back()});
}

std::shared_ptr<workplane> workplane::end(int n) {
  std::shared_ptr<workplane> rv = this->shared_from_this();
  for (int i = 0; i < n; ++i) {
    if (rv->_parent) {
      rv = rv->_parent;
    } else {
      throw std::runtime_error("Cannot End the chain-- no parents!");
    }
  }
  return rv;
}

struct shape_type_visitor : public boost::static_visitor<std::string> {
  template <typename T> std::string operator()(const T &arg) const {
    return arg.shape_type();
  }

  std::string operator()(const std::shared_ptr<sketch> &) const { return "Sketch"; }
  std::string operator()(const topo_vector &) const { return "Vector"; }
  std::string operator()(const topo_location &) const { return "Location"; }
  std::string operator()(const boost::blank &) const { return "Blank"; }
};

shape_object workplane::find_type(const std::vector<std::string> &types,
                                  bool searchStack, bool searchParents) {
  std::vector<shape> rv;

  if (searchStack) {
    for (auto &obj : _objects) {
      bool matchesType = false;
      std::string objType = boost::apply_visitor(shape_type_visitor(), obj);

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
      }
      // Special handling for Compounds when looking for Solids
      else if (objType == "Compound" &&
               std::find(types.begin(), types.end(), "Solid") != types.end()) {
        if (auto c = boost::get<shape>(&obj)) {
          if (c->shape_type() == "Compound") {
            auto solids = c->get_shapes(TopAbs_SOLID);
            rv.insert(rv.end(), solids.begin(), solids.end());
          }
        }
      }
      // Normal unpacking of Compounds
      else if (objType == "Compound") {
        if (auto cs = boost::get<shape>(&obj)) {
          if (cs->shape_type() == "Compound") {
            for (auto &el : cs->children()) {
              std::string elType = el.shape_type();
              for (const auto &type : types) {
                if (elType == type) {
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
      if (std::find(types.begin(), types.end(), "Solid") != types.end()) {
        return compound::make_compound(rv);
      } else {
        return rv.front();
      }
    }
  }

  if (searchParents && _parent != nullptr) {
    return _parent->find_type(types, true, true);
  }

  return shape_object{}; // return empty variant
}

shape workplane::find_solid(bool searchStack, bool searchParents) {
  auto found = find_type({"Solid"}, searchStack, searchParents);

  if (found.empty()) {
    std::string message = searchStack ? "on the stack or " : "";
    throw std::runtime_error("Cannot find a solid " + message +
                             "in the parent chain");
  }

  if (auto s = boost::get<shape>(&found)) {
    if (s->shape_type() == "Solid") {
      return *s;
    } else if (s->shape_type() == "Compound") {
      auto solids = s->get_shapes(TopAbs_SOLID);
      if (!solids.empty()) {
        return solids.front();
      }
    }
  }

  throw std::runtime_error("Found object is not a valid solid");
}

std::shared_ptr<workplane> workplane::select_objects(
    const std::string &objType,
    const boost::optional<
        boost::variant<std::shared_ptr<selector>, std::string>> &selector,
    const boost::optional<std::string> &tag) {
  workplane &cq_obj = tag ? *getTagged(*tag) : *this;
  auto toReturn = cq_obj.collectProperty(objType);
  return newShapeObject(filter(toReturn, selector));
}

std::vector<shape> workplane::filter(
    const std::vector<shape> &objs,
    const boost::optional<
        boost::variant<std::shared_ptr<selector>, std::string>> &s) {
  if (s) {
    std::shared_ptr<flywave::topo::selector> selectorObj;
    if (auto str = boost::get<std::string>(&*s)) {
      selectorObj = std::make_shared<string_syntax_selector>(*str);
    } else {
      selectorObj = boost::get<std::shared_ptr<selector>>(*s);
    }
    return selectorObj->filter(objs);
  }
  return objs;
}

std::shared_ptr<workplane> workplane::vertices(
    const boost::optional<
        boost::variant<std::shared_ptr<selector>, std::string>> &selector,
    const boost::optional<std::string> &tag) {
  return select_objects("Vertices", selector, tag);
}

std::shared_ptr<workplane> workplane::faces(
    const boost::optional<
        boost::variant<std::shared_ptr<selector>, std::string>> &selector,
    const boost::optional<std::string> &tag) {
  return select_objects("Faces", selector, tag);
}

std::shared_ptr<workplane> workplane::edges(
    const boost::optional<
        boost::variant<std::shared_ptr<selector>, std::string>> &selector,
    const boost::optional<std::string> &tag) {
  return select_objects("Edges", selector, tag);
}

std::shared_ptr<workplane> workplane::wires(
    const boost::optional<
        boost::variant<std::shared_ptr<selector>, std::string>> &selector,
    const boost::optional<std::string> &tag) {
  return select_objects("Wires", selector, tag);
}

std::shared_ptr<workplane> workplane::solids(
    const boost::optional<
        boost::variant<std::shared_ptr<selector>, std::string>> &selector,
    const boost::optional<std::string> &tag) {
  return select_objects("Solids", selector, tag);
}

std::shared_ptr<workplane> workplane::shells(
    const boost::optional<
        boost::variant<std::shared_ptr<selector>, std::string>> &selector,
    const boost::optional<std::string> &tag) {
  return select_objects("Shells", selector, tag);
}

std::shared_ptr<workplane> workplane::compounds(
    const boost::optional<
        boost::variant<std::shared_ptr<selector>, std::string>> &selector,
    const boost::optional<std::string> &tag) {
  return select_objects("Compounds", selector, tag);
}

std::shared_ptr<workplane>
workplane::ancestors(TopAbs_ShapeEnum kind,
                     const boost::optional<std::string> &tag) {
  solid ctx_solid = findSolid();
  std::vector<shape_object> objects =
      tag ? getTagged(*tag)->_objects : _objects;

  std::vector<shape> results;
  for (auto &obj : objects) {
    if (auto shp = boost::get<shape>(&obj)) {
      auto ancestors = shp->ancestors(ctx_solid, kind)->get_shapes();
      results.insert(results.end(), ancestors.begin(), ancestors.end());
    }
  }
/**
  // Remove duplicates
  std::unordered_set<shape_object> unique_results(results.begin(),
                                                  results.end()); */
  return newShapeObject(results);
}

std::shared_ptr<workplane>
workplane::siblings(TopAbs_ShapeEnum kind, int level,
                    const boost::optional<std::string> &tag) {
  solid ctx_solid = findSolid();
  std::vector<shape_object> objects =
      tag ? getTagged(*tag)->_objects : _objects;

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
  for (auto &shp : shapes) {
    unique_results.erase(shp);
  }
  return newObject(
      std::vector<shape_object>(unique_results.begin(), unique_results.end()));
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
  std::vector<shape_object> newObjects;
  for (auto &obj : _objects) {
    if (auto sh = boost::get<shape>(&obj)) {
      newObjects.push_back(shape_object(
          sh->rotated(angleDegrees, axisStartPoint, axisEndPoint)));
    } else {
      newObjects.push_back(obj);
    }
  }
  return newObject(newObjects);
}

std::shared_ptr<workplane> workplane::mirror(
    const boost::variant<std::string, gp_Vec, face, workplane> &mirrorPlane,
    const boost::optional<gp_Pnt> &basePointVector, bool unionResult) {
  gp_Vec mp;
  gp_Pnt bp;
  boost::optional<face> mirrorFace;

  // Handle mirrorPlane parameter
  if (auto wp = boost::get<workplane>(&mirrorPlane)) {
    shape_object val = wp->val();
    if (auto f = boost::get<shape>(&val)) {
      if (f->shape_type() == "Face") {
        mp = f->cast<topo::face>()->normal_at();
        mirrorFace = *f;
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

  // Handle base point
  if (mirrorFace && !basePointVector) {
    bp = mirrorFace->center();
  } else if (!basePointVector) {
    bp = gp_Pnt(0, 0, 0);
  } else {
    bp = *basePointVector;
  }

  // Create mirrored objects
  std::vector<shape_object> mirrored;
  for (auto &obj : vals()) {
    if (auto sh = boost::get<shape>(&obj)) {
      mirrored.push_back(shape_object(sh->mirrored(bp, mp)));
    }
  }
  auto newS = newObject(mirrored);

  if (unionResult) {
    return this->union_(newS);
  }
  return newS;
}

std::shared_ptr<workplane> workplane::translate(const gp_Vec &vec) {
  std::vector<shape_object> newObjects;
  for (auto &obj : _objects) {
    if (auto sh = boost::get<shape>(&obj)) {
      newObjects.push_back(sh->translated(vec));
    } else {
      newObjects.push_back(obj);
    }
  }
  return newObject(newObjects);
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
  solid &s = findSolid();

  std::vector<face> faces;
  for (auto &obj : _objects) {
    if (auto f = boost::get<shape>(&obj)) {
      if (f->shape_type() == "Face") {
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
  return newShapeObject(std::vector<shape>({shp}));
}

std::shared_ptr<workplane> workplane::fillet(double radius) {
  solid &s = findSolid();

  std::vector<edge> edgeList;
  for (auto &obj : edges()->vals()) {
    if (auto e = boost::get<shape>(&obj)) {
      if (e->shape_type() == "Edge") {
        edgeList.push_back(*e->cast<topo::edge>());
      }
    }
  }

  if (edgeList.empty()) {
    throw std::runtime_error("Fillet requires that edges be selected");
  }

  shape result = *topo::fillet(s, edgeList, radius);
  return newShapeObject(std::vector<shape>({result.clean()}));
}

std::shared_ptr<workplane> workplane::chamfer(double length,
                                              boost::optional<double> length2) {
  solid &s = findSolid();

  std::vector<edge> edgeList;
  for (auto &obj : edges()->vals()) {
    if (auto e = boost::get<shape>(&obj)) {
      if (e->shape_type() == "Edge") {
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

  return newShapeObject(std::vector<shape>({result}));
}

std::shared_ptr<workplane> workplane::transformed(const gp_Vec &rotate,
                                                  const gp_Vec &offset) {
  auto p = _plane->rotated(rotate);
  p.setOrigin(_plane->toWorldCoords(offset));

  auto ns = std::make_shared<workplane>();
  ns->_objects.push_back(p.getOrigin());
  ns->_plane = std::make_shared<topo_plane>(p);
  ns->_parent = this->shared_from_this();
  ns->_ctx = _ctx;

  return ns;
}

template <typename T>
std::shared_ptr<workplane>
workplane::newShapeObject(const std::vector<T> &objlist) {
  // Create new workplane instance
  auto ns = std::make_shared<workplane>();

  // Copy plane if it exists
  if (_plane) {
    ns->_plane = std::make_shared<topo_plane>(*_plane);
  }

  // Set parent and context
  ns->_parent = this->shared_from_this();
  ns->_ctx = _ctx;

  // Copy objects
  ns->_objects.clear();
  for (const auto &obj : objlist) {
    ns->_objects.push_back(obj);
  }

  return ns;
}

template
std::shared_ptr<workplane>
workplane::newShapeObject(const std::vector<shape> &objlist);

template
std::shared_ptr<workplane>
workplane::newShapeObject(const std::vector<compound> &objlist);

template
std::shared_ptr<workplane>
workplane::newShapeObject(const std::vector<vertex> &objlist);

template
std::shared_ptr<workplane>
workplane::newShapeObject(const std::vector<topo::wire> &objlist);

template
std::shared_ptr<workplane>
workplane::newShapeObject(const std::vector<edge> &objlist);

template
std::shared_ptr<workplane>
workplane::newShapeObject(const std::vector<face> &objlist);

template
std::shared_ptr<workplane>
workplane::newShapeObject(const std::vector<topo::shell> &objlist);

template
std::shared_ptr<workplane>
workplane::newShapeObject(const std::vector<solid> &objlist);

template 
std::shared_ptr<workplane>
workplane::newShapeObject(const std::vector<comp_solid> &objlist);

std::shared_ptr<workplane>
workplane::newObject(const std::vector<shape_object> &objlist) {
  // Create new workplane instance
  auto ns = std::make_shared<workplane>();

  // Copy plane if it exists
  if (_plane) {
    ns->_plane = std::make_shared<topo_plane>(*_plane);
  }

  // Set parent and context
  ns->_parent = this->shared_from_this();
  ns->_ctx = _ctx;

  // Copy objects
  ns->_objects = objlist;

  return ns;
}

gp_Pnt workplane::find_from_point(bool useLocalCoords) {
  shape_object obj = _objects.empty() ? _plane->getOrigin() : _objects.back();

  topo_vector p;
  if (auto shp = boost::get<shape>(&obj)) {
    if (shp->shape_type() == "Edge") {
      p = shp->cast<topo::edge>()->end_point();
    }
  } else if (auto vec = boost::get<topo_vector>(&obj)) {
    p = *vec;
  } else {
    throw std::runtime_error("Cannot convert object type to point");
  }

  return useLocalCoords ? _plane->toLocalCoords(p) : p;
}

edge workplane::find_from_edge(bool useLocalCoords) {
  if (_objects.empty()) {
    throw std::runtime_error("No objects on stack to find edge from");
  }

  shape_object obj = _objects.back();
  if (auto e = boost::get<shape>(&obj)) {
    if (e->shape_type() == "Edge") {
      return useLocalCoords ? *_plane->toLocalCoords(*e).cast<edge>()
                            : *e->cast<edge>();
    }
  } else {
    throw std::runtime_error(
        "Previous Edge requested, but the previous object was not an Edge");
  }
}

std::shared_ptr<workplane>
workplane::rarray(double xSpacing, double ySpacing, int xCount, int yCount,
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

  // Calculate angle between elements
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
  return newObject(vecs);
}

std::shared_ptr<workplane>
workplane::push_points(const std::vector<topo_vector> &pntList) {
  std::vector<shape_object> vecs;
  for (const auto &pnt : pntList) {
    vecs.push_back(pnt);
  }
  return newObject(vecs);
}

std::shared_ptr<workplane> workplane::center(double x, double y) {
  gp_Pnt new_origin = _plane->toWorldCoords(gp_Pnt(x, y, 0));
  auto n = newObject({new_origin});
  n->_plane->setOrigin2d(x, y);
  return n;
}

std::shared_ptr<workplane> workplane::lineTo(double x, double y,
                                             bool forConstruction) {
  gp_Pnt startPoint = find_from_point(false);
  gp_Pnt endPoint = _plane->toWorldCoords(gp_Pnt(x, y, 0));

  edge p = edge::make_edge(startPoint, endPoint);

  if (!forConstruction) {
    addPendingEdge(p);
  }

  return newShapeObject(std::vector<shape>({p}));
}

std::shared_ptr<workplane>
workplane::bezier(const std::vector<gp_Pnt> &listOfPoints, bool forConstruction,
                  bool includeCurrent, bool makeWire) {
  std::vector<gp_Pnt> allPoints;

  if (includeCurrent) {
    allPoints.push_back(find_from_point(false));
  }
  allPoints.insert(allPoints.end(), listOfPoints.begin(), listOfPoints.end());

  edge e = edge::make_bezier(allPoints);

  if (makeWire) {
    topo::wire rv_w = topo::wire::make_wire({e});
    if (!forConstruction) {
      addPendingWire(rv_w);
    }
    return newShapeObject(std::vector<shape>({rv_w}));
  } else {
    if (!forConstruction) {
      addPendingEdge(e);
    }
    return newShapeObject(std::vector<shape>({e}));
  }
}

std::shared_ptr<workplane> workplane::line(double xDist, double yDist,
                                           bool forConstruction) {
  gp_Pnt p = find_from_point(true); // returns local coordinates
  return lineTo(p.X() + xDist, p.Y() + yDist, forConstruction);
}

std::shared_ptr<workplane> workplane::vLine(double distance,
                                            bool forConstruction) {
  return line(0, distance, forConstruction);
}

std::shared_ptr<workplane> workplane::hLine(double distance,
                                            bool forConstruction) {
  return line(distance, 0, forConstruction);
}

std::shared_ptr<workplane> workplane::vLineTo(double yCoord,
                                              bool forConstruction) {
  gp_Pnt p = find_from_point(true);
  return lineTo(p.X(), yCoord, forConstruction);
}

std::shared_ptr<workplane> workplane::hLineTo(double xCoord,
                                              bool forConstruction) {
  gp_Pnt p = find_from_point(true);
  return lineTo(xCoord, p.Y(), forConstruction);
}

std::shared_ptr<workplane> workplane::polarLine(double distance, double angle,
                                                bool forConstruction) {
  double x = std::cos(angle * M_PI / 180.0) * distance;
  double y = std::sin(angle * M_PI / 180.0) * distance;

  return line(x, y, forConstruction);
}

std::shared_ptr<workplane> workplane::polarLineTo(double distance, double angle,
                                                  bool forConstruction) {
  double x = std::cos(angle * M_PI / 180.0) * distance;
  double y = std::sin(angle * M_PI / 180.0) * distance;

  return lineTo(x, y, forConstruction);
}

std::shared_ptr<workplane> workplane::moveTo(double x, double y) {
  gp_Pnt newCenter(x, y, 0);
  return newObject({_plane->toWorldCoords(newCenter)});
}

std::shared_ptr<workplane> workplane::move(double xDist, double yDist) {
  gp_Pnt p = find_from_point(true);
  gp_Pnt newCenter(p.X() + xDist, p.Y() + yDist, 0);
  return newObject({_plane->toWorldCoords(newCenter)});
}

std::shared_ptr<workplane> workplane::slot2D(double length, double diameter,
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

  return eachpoint([slot](const topo_location &loc) { return slot.moved(loc); },
                   true);
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
    allPoints.push_back(_plane->toWorldCoords(p));
  }

  std::vector<gp_Vec> worldTangents;
  if (tangents) {
    std::vector<gp_Vec> tans;
    for (const auto &t : *tangents) {
      tans.push_back(_plane->toWorldCoords(t) - _plane->getOrigin());
    }
    worldTangents = tans;
  }

  edge e = edge::make_spline(allPoints, &worldTangents, periodic,
                             parameters ? &*parameters : nullptr, scale,
                             tol ? *tol : 1e-6);

  if (makeWire) {
    topo::wire w = topo::wire::make_wire({e});
    if (!forConstruction) {
      addPendingWire(w);
    }
    return newShapeObject(std::vector<shape>({w}));
  } else {
    if (!forConstruction) {
      addPendingEdge(e);
    }
    return newShapeObject(std::vector<shape>({e}));
  }
}

std::shared_ptr<workplane> workplane::splineApprox(
    const std::vector<gp_Pnt> &points, boost::optional<double> tol, int minDeg,
    int maxDeg,
    const boost::optional<std::tuple<double, double, double>> &smoothing,
    bool forConstruction, bool includeCurrent, bool makeWire) {
  std::vector<gp_Pnt> allPoints;
  if (includeCurrent) {
    allPoints.push_back(find_from_point(false));
  }
  for (const auto &p : points) {
    allPoints.push_back(_plane->toWorldCoords(p));
  }

  edge e = edge::make_spline_approx(allPoints, tol ? *tol : 1e-6, smoothing,
                                    minDeg, maxDeg);

  if (makeWire) {
    topo::wire w = topo::wire::make_wire({e});
    if (!forConstruction) {
      addPendingWire(w);
    }
    return newShapeObject(std::vector<shape>({w}));
  } else {
    if (!forConstruction) {
      addPendingEdge(e);
    }
    return newShapeObject(std::vector<shape>({e}));
  }
}

std::shared_ptr<workplane> workplane::parametricCurve(
    std::function<gp_Pnt(double)> func, int N, double start, double stop,
    double tol, int minDeg, int maxDeg,
    const std::tuple<double, double, double> &smoothing, bool makeWire) {
  double diff = stop - start;
  std::vector<gp_Pnt> allPoints;
  for (int t = 0; t <= N; t++) {
    allPoints.push_back(_plane->toWorldCoords(func(start + diff * t / N)));
  }

  edge e = edge::make_spline_approx(allPoints, tol, smoothing, minDeg, maxDeg);

  if (makeWire) {
    topo::wire w = topo::wire::make_wire({e});
    addPendingWire(w);
    return newShapeObject(std::vector<shape>({w}));
  } else {
    addPendingEdge(e);
    return newShapeObject(std::vector<shape>({e}));
  }
}

std::shared_ptr<workplane> workplane::parametricSurface(
    std::function<gp_Pnt(double, double)> func, int N, double start,
    double stop, double tol, int minDeg, int maxDeg,
    const std::tuple<double, double, double> &smoothing) {
  double diff = stop - start;
  std::vector<std::vector<gp_Pnt>> allPoints;
  for (int i = 0; i <= N; i++) {
    std::vector<gp_Pnt> row;
    for (int j = 0; j <= N; j++) {
      row.push_back(_plane->toWorldCoords(
          func(start + diff * i / N, start + diff * j / N)));
    }
    allPoints.push_back(row);
  }

  face f = face::make_spline_approx(allPoints, tol, &smoothing, minDeg, maxDeg);

  return newShapeObject(std::vector<shape>({f}));
}

std::shared_ptr<workplane>
workplane::ellipseArc(double x_radius, double y_radius, double angle1,
                      double angle2, double rotation_angle, int sense,
                      bool forConstruction, bool startAtCurrent,
                      bool makeWire) {
  gp_Pnt center = find_from_point(false);
  edge e = edge::make_ellipse(x_radius, y_radius, center, _plane->zDir,
                              _plane->xDir, angle1, angle2, sense);

  if (rotation_angle != 0.0) {
    e.rotate(rotation_angle, center, center.Translated(_plane->zDir));
  }

  if (startAtCurrent) {
    gp_Pnt startPoint = e.start_point();
    e.translate(center.XYZ() - startPoint.XYZ());
  }

  if (makeWire) {
    topo::wire w = topo::wire::make_wire({e});
    if (!forConstruction) {
      addPendingWire(w);
    }
    return newShapeObject(std::vector<shape>({w}));
  } else {
    if (!forConstruction) {
      addPendingEdge(e);
    }
    return newShapeObject(std::vector<shape>({e}));
  }
}

std::shared_ptr<workplane> workplane::threePointArc(const gp_Pnt &point1,
                                                    const gp_Pnt &point2,
                                                    bool forConstruction) {
  gp_Pnt gstartPoint = find_from_point(false);
  gp_Pnt gpoint1 = _plane->toWorldCoords(point1);
  gp_Pnt gpoint2 = _plane->toWorldCoords(point2);

  edge arc = edge::make_three_point_arc(gstartPoint, gpoint1, gpoint2);

  if (!forConstruction) {
    addPendingEdge(arc);
  }

  return newShapeObject(std::vector<shape>({arc}));
}

std::shared_ptr<workplane> workplane::sagittaArc(const gp_Pnt &endPoint,
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
  return threePointArc(sagPoint, endPointVec, forConstruction);
}

std::shared_ptr<workplane> workplane::radiusArc(const gp_Pnt &endPoint,
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
    return sagittaArc(endPointVec, sag, forConstruction);
  } else {
    return sagittaArc(endPointVec, -sag, forConstruction);
  }
}

std::shared_ptr<workplane> workplane::tangentArcPoint(const gp_Pnt &endpoint,
                                                      bool forConstruction,
                                                      bool relative) {
  gp_Pnt endpointVec(endpoint.X(), endpoint.Y(), 0);
  if (relative) {
    gp_Pnt current = find_from_point(true);
    endpointVec =
        gp_Pnt(endpointVec.X() + current.X(), endpointVec.Y() + current.Y(), 0);
  }
  endpointVec = _plane->toWorldCoords(endpointVec);

  edge previousEdge = find_from_edge();
  gp_Pnt edgeEnd = previousEdge.end_point();
  gp_Vec edgeTangent = previousEdge.tangent_at(1.0);

  edge arc = edge::make_tangent_arc(edgeEnd, edgeTangent, endpointVec);

  if (!forConstruction) {
    addPendingEdge(arc);
  }

  return newShapeObject(std::vector<shape>({arc}));
}

std::shared_ptr<workplane> workplane::wire(bool forConstruction) {
  // Check if there are no pending edges
  if (_ctx->pending_edges().empty()) {
    return this->shared_from_this();
  }

  // Get pending edges from context
  std::vector<topo::edge> edges = _ctx->pop_pending_edges();

  // Assemble edges into a wire
  topo::wire w = topo::wire::make_wire(edges);

  // Add to pending wires if not for construction
  if (!forConstruction) {
    addPendingWire(w);
  }

  // Filter out edges from objects and add the new wire
  std::vector<shape> newObjects;
  for (const auto &obj : _objects) {
    if (auto edge = boost::get<shape>(&obj)) {
      if (edge->shape_type() == "Edge") {
        newObjects.push_back(*edge);
      }
    }
  }
  newObjects.push_back(w);

  return newShapeObject(newObjects);
}

std::shared_ptr<workplane> workplane::mirrorY() {
  std::shared_ptr<workplane> n = this->wire(false);
  std::shared_ptr<workplane> consolidated = n->consolidateWires();

  std::vector<shape> shapes;
  for (auto &obj : consolidated->wires()->vals()) {
    if (auto shp = boost::get<shape>(&obj)) {
      shapes.push_back(*shp);
    } else if (auto shp = boost::get<std::shared_ptr<topo::sketch>>(&obj)) {
      shapes.push_back(*(*shp)->faces_);
    }
  }

  std::vector<shape> mirroredWires = _plane->mirrorInPlane(shapes, "Y");
  for (auto &w : mirroredWires) {
    consolidated->_objects.push_back(w);
    consolidated->addPendingWire(*w.cast<topo::wire>());
  }

  return consolidated->consolidateWires();
}

std::shared_ptr<workplane> workplane::mirrorX() {
  std::shared_ptr<workplane> n = this->wire(false);
  std::shared_ptr<workplane> consolidated = n->consolidateWires();

  std::vector<shape> shapes;
  for (auto &obj : consolidated->wires()->vals()) {
    if (auto shp = boost::get<shape>(&obj)) {
      shapes.push_back(*shp);
    } else if (auto shp = boost::get<std::shared_ptr<topo::sketch>>(&obj)) {
      shapes.push_back(*(*shp)->faces_);
    }
  }

  std::vector<shape> mirroredWires = _plane->mirrorInPlane(shapes, "X");
  for (auto &w : mirroredWires) {
    consolidated->_objects.push_back(w);
    consolidated->addPendingWire(*w.cast<topo::wire>());
  }

  return consolidated->consolidateWires();
}

void workplane::addPendingEdge(const edge &e) {
  _ctx->pending_edges().push_back(e);

  if (!_ctx->first_point()) {
    _ctx->set_first_point(_plane->toLocalCoords(e.start_point()));
  }
}

void workplane::addPendingWire(const topo::wire &w) {
  _ctx->pending_wires().push_back(w);
}

std::vector<topo::wire> workplane::_consolidateWires() {
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

std::shared_ptr<workplane> workplane::consolidateWires() {
  std::vector<flywave::topo::wire> w = _consolidateWires();

  if (w.empty()) {
    return this->shared_from_this();
  }

  auto r = newShapeObject(w);
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
      auto shape = selectShape(obj);
      if (shape) {
        shape_object so(_plane->toLocalCoords(*shape));
        r = callback(so);

        auto shape = selectShape(r);
        shape->transform(_plane->rG);

        r = *shape;
      }

    } else {
      r = callback(obj);
    }

    if (auto w = boost::get<shape>(&r)) {
      if (w->shape_type() == "Wire") {
        // if (!w->forConstruction()) {
        addPendingWire(*w->cast<topo::wire>());
        //}
      }
    }

    if (auto shp = boost::get<shape>(&r)) {
      results.push_back(*shp);
    } else if (auto shp = boost::get<std::shared_ptr<topo::sketch>>(&r)) {
      results.push_back(*(*shp)->faces_);
    }
  }

  return combineWithBase(results, combine, clean);
}

std::shared_ptr<workplane> workplane::eachpoint(
    const boost::variant<shape, workplane, std::function<shape(topo_location)>>
        &arg,
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
  if (auto wp = boost::get<workplane>(&arg)) {
    if (useLocalCoordinates) {
      for (auto &v : wp->vals()) {
        if (auto s = boost::get<shape>(&v)) {
          for (auto &p : pnts) {
            res.push_back(s->moved(p).moved(loc));
          }
        }
      }
    } else {
      for (auto &v : wp->vals()) {
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
      // if (!w->forConstruction()) {
      addPendingWire(*w);
      //}
    }
  }

  return combineWithBase(res, combine, clean);
}

std::shared_ptr<workplane>
workplane::rect(double xLen, double yLen,
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
  return eachpoint(
      [w](const topo_location &loc) -> shape { return w.moved(loc); }, true);
}

std::shared_ptr<workplane> workplane::circle(double radius,
                                             bool forConstruction) {
  topo::wire c = topo::wire::make_circle(radius, gp_Pnt(), gp_Vec(0, 0, 1));
  // c.setForConstruction(forConstruction);
  return eachpoint([c](const topo_location &loc) { return c.moved(loc); },
                   true);
}

std::shared_ptr<workplane> workplane::ellipse(double x_radius, double y_radius,
                                              double rotation_angle,
                                              bool forConstruction) {
  topo::wire e =
      topo::wire::make_ellipse(x_radius, y_radius, gp_Pnt(), gp_Vec(0, 0, 1),
                               gp_Vec(1, 0, 0), rotation_angle);
  // e.setForConstruction(forConstruction);
  return eachpoint([e](const topo_location &loc) { return e.moved(loc); },
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

  topo::wire p = topo::wire::make_polygon(pnts, forConstruction);
  return eachpoint([p](const topo_location &loc) { return p.moved(loc); },
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
    startPoint = _plane->toWorldCoords(points[0]);
  }

  size_t startIdx = includeCurrent ? 0 : 1;
  for (size_t i = startIdx; i < points.size(); i++) {
    gp_Pnt endPoint = _plane->toWorldCoords(points[i]);
    edges.push_back(edge::make_edge(startPoint, endPoint));
    if (!forConstruction) {
      addPendingEdge(edges.back());
    }
    startPoint = endPoint;
  }

  return newShapeObject(edges);
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

double workplane::largestDimension() {
  solid s = findSolid();
  return s.bbox().GetDiagonalLength();
}

std::shared_ptr<workplane>
workplane::cutEach(std::function<shape(topo_location)> fcn, bool useLocalCoords,
                   bool clean) {
  shape ctxSolid = findSolid();
  auto results = eachpoint(fcn, useLocalCoords)->vals();

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

  return newShapeObject(std::vector<shape>({*s}));
}

std::shared_ptr<workplane>
workplane::cboreHole(double diameter, double cboreDiameter, double cboreDepth,
                     boost::optional<double> depth, bool clean) {
  if (!depth) {
    depth = largestDimension();
  }

  gp_Vec boreDir(0, 0, -1);
  gp_Pnt center;

  solid hole =
      solid::make_solid_from_cylinder(diameter / 2.0, *depth, center, boreDir);
  solid cbore = solid::make_solid_from_cylinder(cboreDiameter / 2.0, cboreDepth,
                                                gp_Pnt(), boreDir);
  boost::optional<shape> r = topo::fuse({hole, cbore});

  return cutEach([r](const topo_location &loc) { return r->moved(loc); }, true,
                 clean);
}

std::shared_ptr<workplane>
workplane::cskHole(double diameter, double cskDiameter, double cskAngle,
                   boost::optional<double> depth, bool clean) {
  if (!depth) {
    depth = largestDimension();
  }

  gp_Dir boreDir(0, 0, -1);
  gp_Pnt center;

  solid hole =
      solid::make_solid_from_cylinder(diameter / 2.0, *depth, center, boreDir);
  double r = cskDiameter / 2.0;
  double h = r / std::tan(cskAngle * M_PI / 180.0 / 2.0);
  solid csk = solid::make_solid_from_cone(r, 0.0, h, center, boreDir);
  shape res = *topo::fuse({hole, csk});

  return cutEach([res](const topo_location &loc) { return res.moved(loc); },
                 true, clean);
}

std::shared_ptr<workplane>
workplane::hole(double diameter, boost::optional<double> depth, bool clean) {
  if (!depth) {
    depth = largestDimension();
  }

  gp_Vec boreDir(0, 0, -1);
  solid h = solid::make_solid_from_cylinder(diameter / 2.0, *depth, gp_Pnt(),
                                            boreDir);

  return cutEach([h](const topo_location &loc) { return h.moved(loc); }, true,
                 clean);
}

std::shared_ptr<workplane> workplane::twistExtrude(double distance,
                                                   double angleDegrees,
                                                   bool combine, bool clean) {
  auto faces = getFaces();
  gp_Vec eDir = _plane->zDir.multiply(distance);

  std::vector<shape> shapes;
  for (auto &f : faces) {
    shapes.push_back(*topo::extrude_linear_with_rotation(f, _plane->getOrigin(),
                                                         eDir, angleDegrees));
  }

  shape r = compound::make_compound(shapes).fuse({});
  return combineWithBase(r, combine, clean);
}

std::shared_ptr<workplane>
workplane::extrude(boost::variant<double, std::string, face> &until,
                   const boost::variant<bool, std::string> &combine, bool clean,
                   bool both, boost::optional<double> taper) {
  auto combineStr = boost::get<std::string>(&combine);
  if (combineStr && (*combineStr == "cut" || *combineStr == "s")) {
    return cutBlind(until, clean, both, taper);
  }

  shape r;
  if (auto dist = boost::get<double>(&until)) {
    r = _extrude(*dist, both, taper);
  } else if (auto str = boost::get<std::string>(&until)) {
    int faceIndex = (*str == "next") ? 0 : -1;
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

  return combineWithBase(r, combine, clean);
}

std::shared_ptr<workplane> workplane::revolve(
    double angleDegrees, const boost::optional<gp_Pnt> &axisStart,
    const boost::optional<gp_Pnt> &axisEnd, bool combine, bool clean) {
  // Normalize angle
  angleDegrees = std::fmod(angleDegrees, 360.0);
  if (angleDegrees == 0)
    angleDegrees = 360.0;

  // Calculate axis points
  gp_Pnt startPoint = axisStart ? _plane->toWorldCoords(*axisStart)
                                : _plane->toWorldCoords(gp_Pnt(0, 0, 0));

  gp_Pnt endPoint;
  if (axisEnd) {
    endPoint = _plane->toWorldCoords(*axisEnd);
  } else {
    if (startPoint.Y() != 0) {
      endPoint = _plane->toWorldCoords(gp_Pnt(0, startPoint.Y(), 0));
    } else {
      endPoint = _plane->toWorldCoords(gp_Pnt(0, 1, 0));
    }
  }

  shape r = _revolve(angleDegrees, startPoint, endPoint);
  return combineWithBase(r, combine, clean);
}

std::shared_ptr<workplane> workplane::sweep(
    boost::variant<std::shared_ptr<workplane>, topo::wire, edge> path,
    bool multisection, bool makeSolid, bool isFrenet, bool combine, bool clean,
    const transition_mode &transition, const boost::optional<gp_Vec> &normal,
    const boost::optional<workplane> &auxSpine) {
  boost::variant<std::shared_ptr<workplane>, topo::wire, topo::edge> pathWire;
  if (auto wp = boost::get<std::shared_ptr<workplane>>(&path)) {
    pathWire = (*wp)->wire();
  } else if (auto w = boost::get<topo::wire>(&path)) {
    pathWire = *w;
  } else if (auto e = boost::get<edge>(&path)) {
    pathWire = wire::make_wire({*e});
  }

  shape r = _sweep(pathWire, multisection, makeSolid, isFrenet, transition,
                   normal, auxSpine);

  return combineWithBase(r, combine, clean);
}

std::shared_ptr<workplane>
workplane::combineWithBase(const boost::variant<shape, std::vector<shape>> &obj,
                           const boost::variant<bool, std::string> &mode,
                           bool clean) {
  shape newS;
  auto smode = boost::get<std::string>(&mode);
  auto bmode = boost::get<bool>(&mode);

  if (smode || (bmode && *bmode)) {
    shape shp = boost::get<shape>(obj);
    auto shapes = boost::get<std::vector<shape>>(&obj);
    if (shapes) {
      shp = compound::make_compound(*shapes);
    }
    if (smode && *smode == "cut" || *smode == "s") {
      newS = cutFromBase(shp);
    } else if ((smode && *smode == "a") || *bmode) {
      newS = fuseWithBase(shp);
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

  return newObject({newS});
}

shape workplane::fuseWithBase(const shape &obj) {
  shape baseSolid = findType({"Solid"}, true, true);
  if (baseSolid) {
    return *topo::fuse({baseSolid, obj});
  } else if (obj.shape_type() == "Compound") {
    return obj.cast<compound>()->fuse({});
  }
  return obj;
}

shape workplane::cutFromBase(const shape &obj) {
  shape baseSolid = findType({"Solid"}, true, true);
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

  return newObject({s});
}

std::shared_ptr<workplane> workplane::union_(
    boost::variant<std::shared_ptr<workplane>, solid, compound> toUnion,
    bool clean, bool glue, const boost::optional<double> &tol) {
  std::vector<shape> newS;
  if (auto wp = boost::get<std::shared_ptr<workplane>>(&toUnion)) {
    auto solids = (*wp)->solids()->vals();
    if (solids.empty()) {
      throw std::runtime_error(
          "Workplane must have at least one solid to union");
    }
    for (auto &obj : solids) {
      if (auto s = boost::get<shape>(&obj)) {
        newS.push_back(*s);
      }
    }
    mergeTags(**wp);
  } else if (auto s = boost::get<solid>(&toUnion)) {
    newS = {*s};
  } else if (auto c = boost::get<compound>(&toUnion)) {
    newS = {*c};
  }

  shape r;
  shape solidRef = findType({"Solid"}, true, true);
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

  return newObject({r});
}

std::shared_ptr<workplane> workplane::cut(
    boost::variant<std::shared_ptr<workplane>, solid, compound> toCut,
    bool clean, const boost::optional<double> &tol) {
  solid solidRef = findSolid(true, true);

  std::vector<shape> solidToCut;
  if (auto wp = boost::get<std::shared_ptr<workplane>>(&toCut)) {
    solidToCut = selectShapes((*wp)->vals());
    mergeTags(**wp);
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

  return newObject({newS});
}

std::shared_ptr<workplane> workplane::intersect(
    boost::variant<std::shared_ptr<workplane>, solid, compound> toIntersect,
    bool clean, const boost::optional<double> &tol) {
  solid solidRef = findSolid(true, true);

  std::vector<shape> solidToIntersect;
  if (auto wp = boost::get<std::shared_ptr<workplane>>(&toIntersect)) {
    solidToIntersect = selectShapes((*wp)->vals());
    mergeTags(**wp);
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

  return newObject({newS});
}

std::shared_ptr<workplane>
workplane::cutBlind(boost::variant<double, std::string, face> &until,
                    bool clean, bool both,
                    const boost::optional<double> &taper) {
  shape s;
  if (auto dist = boost::get<double>(&until)) {
    shape toCut = _extrude(*dist, both, taper, {}, false);
    solid solidRef = findSolid();
    s = *topo::cut(solidRef, toCut);
  } else if (auto str = boost::get<std::string>(&until)) {
    int faceIndex = (*str == "next") ? 0 : -1;
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

  return newObject({s});
}

std::shared_ptr<workplane> workplane::cutThruAll(bool clean, double taper) {
  solid solidRef = findSolid();
  auto faces = getFaces();

  if (faces.empty()) {
    throw std::runtime_error("No pending wires to cut with");
  }

  shape s = *topo::dprism(solidRef, nullptr, faces, boost::none, taper, nullptr,
                          true, false);
  if (clean) {
    s = s.clean();
  }

  return newObject({s});
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
    auto facesVerts = getFacesVertices();
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
  return combineWithBase(r, combine, clean);
}

std::vector<face> workplane::getFaces() {
  std::vector<face> rv;
  for (auto &obj : _objects) {
    if (auto sk = boost::get<std::shared_ptr<topo::sketch>>(&obj)) {
      auto faces = (*sk)->get_faces();
      rv.insert(rv.end(), faces.begin(), faces.end());
    } else if (auto shp = boost::get<shape>(&obj)) {
      if (shp->shape_type() == "Face") {
        rv.push_back(*shp->cast<face>());
      } else if (shp->shape_type() == "Compound") {
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

std::vector<shape> workplane::getFacesVertices() {
  std::vector<shape> rv;
  for (auto &obj : _objects) {
    if (auto sk = boost::get<std::shared_ptr<topo::sketch>>(&obj)) {
      auto faces = (*sk)->get_faces();
      rv.insert(rv.end(), faces.begin(), faces.end());
    } else if (auto shp = boost::get<shape>(&obj)) {
      if (shp->shape_type() == "Face") {
        rv.push_back(*shp->cast<face>());
      } else if (shp->shape_type() == "Compound") {
        auto comp = shp->cast<compound>();
        for (auto &subel : comp->children()) {
          if (auto f = subel.cast<topo::face>()) {
            rv.push_back(*f);
          } else if (auto v = subel.cast<topo::vertex>()) {
            rv.push_back(*v);
          }
        }
      } else if (shp->shape_type() == "Vertex") {
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
  auto faces = getFaces();

  // Check for nested geometry with tapered extrusion
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
    eDir = _plane->zDir;
  } else if (distance) {
    eDir = _plane->zDir.multiply(*distance);
  }

  double taperAngle = taper ? *taper : 0.0;
  flywave::topo::intersection_direction direction =
      additive ? flywave::topo::intersection_direction::AlongAxis
               : flywave::topo::intersection_direction::Opposite;

  if (upToFace) {
    shape res = findSolid();
    for (auto &face : faces) {
      topo::face limitFace;
      if (auto idx = boost::get<int>(&*upToFace)) {
        auto facesList = _getIntersectedFaces(face, eDir, direction, both);
        if (res.cast<topo::solid>()->is_inside(face.outer_wire().center()) &&
            additive && *idx == 0) {
          *idx = 1; // extrude until next face outside the solid
        }
        limitFace = facesList[*idx];
      } else {
        limitFace = boost::get<topo::face>(*upToFace);
      }

      res = *topo::dprism(res, nullptr, {face}, boost::none, taperAngle,
                          &limitFace, additive);

      if (both) {
        auto facesList2 =
            _getIntersectedFaces(face, eDir.Multiplied(-1.0), direction, both);
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

std::vector<face> workplane::_getIntersectedFaces(
    const face &face, const gp_Vec &eDir,
    const flywave::topo::intersection_direction &direction, bool both) {
  auto facesList = topo::faces_intersected_by_line(findSolid(), face.center(),
                                                   eDir, 1.0E-4, direction);

  if (facesList.empty() && both) {
    throw std::runtime_error(
        "Couldn't find a face to extrude/cut to for both directions");
  }

  if (facesList.empty()) {
    // Try opposite direction
    facesList = topo::faces_intersected_by_line(
        findSolid(), face.center(), eDir.Multiplied(-1.0), 1.0E-4, direction);
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
  for (auto &f : getFaces()) {
    toFuse.push_back(*topo::revolve(f, angleDegrees, axisStart, axisEnd));
  }
  return compound::make_compound(toFuse);
}

shape workplane::_sweep(
    boost::variant<std::shared_ptr<workplane>, topo::wire, topo::edge> &path,
    bool multisection, bool makeSolid, bool isFrenet,
    const transition_mode &transition, const boost::optional<gp_Vec> &normal,
    const boost::optional<workplane> &auxSpine) {
  topo::shape pathWire;
  if (auto wp = boost::get<std::shared_ptr<workplane>>(&path)) {
    auto val = (*wp)->val();
    if (auto shp = boost::get<shape>(&val)) {
      if (shp->shape_type() == "Wire") {
        pathWire = *shp->cast<topo::wire>();
      } else if (shp->shape_type() == "Edge") {
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
    mode = vertex::make_vertex(*normal);
  } else if (auxSpine) {
    auto val = auxSpine->val();

    if (auto shp = boost::get<topo::shape>(&val)) {
      if (shp->shape_type() == "Wire") {
        mode = *shp->cast<topo::wire>();
      } else if (shp->shape_type() == "Edge") {
        mode = *shp->cast<topo::edge>();
      }
    } else {
      throw std::runtime_error("Invalid auxSpine type");
    }
  }

  std::vector<shape> toFuse;
  if (!multisection) {
    for (auto &f : getFaces()) {
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
      for (auto &f : getFaces()) {
        sections.push_back(f.outer_wire());
      }
    }
    toFuse.push_back(
        *topo::sweep_multi(sections, pathWire, makeSolid, isFrenet, &mode));
  }

  return compound::make_compound(toFuse);
}

std::shared_ptr<workplane> workplane::interpPlate(
    boost::variant<std::vector<gp_Pnt>, std::vector<edge>, workplane>
        &surf_edges,
    const std::vector<gp_Pnt> &surf_pts, double thickness, bool combine,
    bool clean, int degree, int nbPtsOnCur, int nbIter, bool anisotropy,
    double tol2d, double tol3d, double tolAng, double tolCurv, int maxDeg,
    int maxSegments) {
  std::vector<boost::variant<edge, topo::wire>> edges;
  std::vector<gp_Pnt> points;

  if (auto wp = boost::get<workplane>(&surf_edges)) {
    for (auto &obj : wp->edges()->_objects) {
      if (auto shp = boost::get<shape>(&obj)) {
        if (shp->shape_type() == "Edge") {
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
  return eachpoint([s](const topo_location &loc) { return s.moved(loc); }, true,
                   combine, clean);
}

std::shared_ptr<workplane> workplane::box(
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

  return eachpoint([box](const topo_location &loc) { return box.moved(loc); },
                   true, combine, clean);
}

std::shared_ptr<workplane> workplane::sphere(
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

  return eachpoint([s](const topo_location &loc) { return s.moved(loc); }, true,
                   combine, clean);
}

std::shared_ptr<workplane> workplane::cylinder(
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

  return eachpoint([s](const topo_location &loc) { return s.moved(loc); }, true,
                   combine, clean);
}

std::shared_ptr<workplane> workplane::wedge(
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

  return eachpoint([w](const topo_location &loc) { return w.moved(loc); }, true,
                   combine, clean);
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
  return newObject(cleanObjects);
}

std::shared_ptr<workplane>
workplane::text(const std::string &txt, double fontsize, double distance,
                bool cut, bool combine, bool clean, const std::string &font,
                const boost::optional<std::string> &fontPath,
                const std::string &kind_, const std::string &halign_,
                const std::string &valign_) {

  if (cut) {
    combine = true; // "cut" mode
  }

  compound::FontKind kind = compound::FontKind::REGULAR;
  compound::HAlign halign = compound::HAlign::CENTER;
  compound::VAlign valign = compound::VAlign::CENTER;
  if (kind_ == "bold") {
    kind = compound::FontKind::BOLD;
  } else if (kind_ == "italic") {
    kind = compound::FontKind::ITALIC;
  } else if (kind_ == "bold") {
    kind = compound::FontKind::BOLD;
  }

  if (halign_ == "left") {
    halign = compound::HAlign::LEFT;
  } else if (halign_ == "right") {
    halign = compound::HAlign::RIGHT;
  }
  if (valign_ == "top") {
    valign = compound::VAlign::TOP;
  } else if (valign_ == "bottom") {
    valign = compound::VAlign::BOTTOM;
  }

  shape r = topo::compound::make_text(txt, fontsize, distance, font, *fontPath,
                                      kind, halign, valign, *_plane);

  return combineWithBase(r, combine, clean);
}

std::shared_ptr<workplane> workplane::section(double height) {
  shape solidRef = findSolid(true, true);

  if (!solidRef) {
    throw std::runtime_error("No solid found to section");
  }

  gp_Pnt basePnt = _plane->origin + _plane->zDir * height;
  face plane = face::make_plane(basePnt, _plane->zDir);

  shape r = *topo::intersect(solidRef, plane);

  return newObject({r});
}

workplane &workplane::toPending() {
  for (auto &obj : _objects) {
    if (auto shp = boost::get<shape>(&obj)) {
      if (shp->shape_type() == "Wire") {
        _ctx->pending_wires().push_back(*shp->cast<topo::wire>());
      } else if (shp->shape_type() == "Edge") {
        _ctx->pending_edges().push_back(*shp->cast<topo::edge>());
      }
    }
  }
  return *this;
}

std::shared_ptr<workplane>
workplane::offset2D(double d, const std::string &kind, bool forConstruction) {
  std::vector<topo::wire> ws = _consolidateWires();
  std::vector<topo::wire> rv;

  for (auto &w : ws) {
    auto offsetWires = w.offset2d(d, kind);
    rv.insert(rv.end(), offsetWires.begin(), offsetWires.end());
  }

  _ctx->pending_edges().clear();
  if (forConstruction) {
    for (auto &wire : rv) {
      // wire.forConstruction = true;
    }
    _ctx->pending_wires().clear();
  } else {
    _ctx->set_pending_wires(rv);
  }

  return newShapeObject(rv);
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

std::shared_ptr<topo::sketch> workplane::sketch() {
  std::shared_ptr<workplane> parent = newObject({});

  std::shared_ptr<topo::sketch> rv =
      std::make_shared<topo::sketch>(parent, locs());
  parent->_objects.push_back(rv);

  return rv;
}

std::shared_ptr<workplane>
workplane::placeSketch(const std::vector<topo::sketch> &sketches) {
  std::vector<topo::shape_object> rv;

  for (auto &s : sketches) {
    auto s_new = s.copy();
    s_new->locs_ = locs();
    rv.push_back(s_new);
  }

  return newObject(rv);
}

// Indexing operator
std::shared_ptr<workplane> workplane::operator[](
    const boost::variant<int, std::vector<int>, std::pair<int, int>> &item) {
  if (item.type() == typeid(int)) {
    int idx = boost::get<int>(item);
    return newObject({_objects[idx]});
  } else if (item.type() == typeid(std::vector<int>)) {
    std::vector<int> indices = boost::get<std::vector<int>>(item);
    std::vector<shape_object> selected;
    for (int i : indices) {
      selected.push_back(_objects[i]);
    }
    return newObject(selected);
  } else {
    std::pair<int, int> slice = boost::get<std::pair<int, int>>(item);
    std::vector<shape_object> sliced(_objects.begin() + slice.first,
                                     _objects.begin() + slice.second);
    return newObject(sliced);
  }
}

shape &workplane::iterator::operator*() {
  if (auto shp = boost::get<shape>(&*_it)) {
    return *shp;
  } else if (auto sk = boost::get<std::shared_ptr<topo::sketch>>(&*_it)) {
    return *(*sk)->faces_; // Assuming sketch is iterable
  }
  throw std::runtime_error("Invalid object type in iterator");
}

// Filter method
std::shared_ptr<workplane>
workplane::filter(const std::function<bool(const shape_object &)> &predicate) {
  std::vector<shape_object> filtered;
  std::copy_if(_objects.begin(), _objects.end(), std::back_inserter(filtered),
               predicate);
  return newObject(filtered);
}

// Map method
std::shared_ptr<workplane> workplane::map(
    const std::function<shape_object(const shape_object &)> &mapper) {
  std::vector<shape_object> mapped;
  std::transform(_objects.begin(), _objects.end(), std::back_inserter(mapped),
                 mapper);
  return newObject(mapped);
}

// Apply method
std::shared_ptr<workplane>
workplane::apply(const std::function<std::vector<shape_object>(
                     const std::vector<shape_object> &)> &applier) {
  return newObject(applier(_objects));
}

// Sort method
std::shared_ptr<workplane> workplane::sort(
    const std::function<bool(const shape_object &, const shape_object &)>
        &comparator) {
  std::vector<shape_object> sorted = _objects;
  std::sort(sorted.begin(), sorted.end(), comparator);
  return newObject(sorted);
}

// Invoke method
workplane &
workplane::invoke(const boost::variant<std::function<workplane &(workplane &)>,
                                       std::function<void(workplane &)>,
                                       std::function<void()>> &func) {
  if (func.type() == typeid(std::function<void()>)) {
    boost::get<std::function<void()>>(func)();
    return *this;
  } else if (func.type() == typeid(std::function<void(workplane &)>)) {
    boost::get<std::function<void(workplane &)>>(func)(*this);
    return *this;
  } else {
    auto result =
        boost::get<std::function<workplane &(workplane &)>>(func)(*this);
    return result;
  }
}

} // namespace topo
} // namespace flywave
