#include "shape3d.hh"
#include "edge.hh"
#include "face.hh"
#include "shell.hh"
#include "solid.hh"
#include "vertex.hh"
#include "wire.hh"

#include <BRepBuilderAPI_MakeSolid.hxx>
#include <BRepClass3d_SolidClassifier.hxx>
#include <BRepFeat_MakeDPrism.hxx>
#include <BRepFilletAPI_MakeChamfer.hxx>
#include <BRepFilletAPI_MakeFillet.hxx>
#include <BRepOffsetAPI_MakeThickSolid.hxx>
#include <TopExp.hxx>
#include <TopTools_IndexedDataMapOfShapeListOfShape.hxx>
#include <TopTools_ListOfShape.hxx>
#include <TopoDS.hxx>
#include <gp_Pnt.hxx>
#include <vector>

namespace flywave {
namespace topo {
namespace {

std::vector<std::vector<wire>>
sort_wires_by_build_order(const std::vector<wire> &wireList) {
  if (wireList.size() < 2) {
    return {wireList};
  }

  wire outerWire = wireList[0];
  std::vector<wire> innerWires(wireList.begin() + 1, wireList.end());

  std::vector<face> faces = face::make_from_wires(outerWire, innerWires);

  std::vector<std::vector<wire>> result;
  for (const face &face : faces) {
    std::vector<wire> faceWires;
    faceWires.push_back(face.outer_wire());

    auto inners = face.inner_wires();
    faceWires.insert(faceWires.end(), inners.begin(), inners.end());

    result.push_back(faceWires);
  }

  return result;
}

} // namespace

shape shape3d::fillet(double radius, const std::vector<edge> &edgeList) const {
  if (radius <= 0) {
    throw std::invalid_argument("Radius must be positive");
  }

  BRepFilletAPI_MakeFillet filletBuilder(this->value());

  for (const edge &e : edgeList) {
    filletBuilder.Add(radius, e.value());
  }

  if (!filletBuilder.IsDone()) {
    throw std::runtime_error("Failed to create fillet");
  }

  return solid(filletBuilder.Shape());
}

shape shape3d::chamfer(double length, const boost::optional<double> &length2,
                       const std::vector<edge> &edgeList) const {
  if (length <= 0 || (length2 && *length2 <= 0)) {
    throw std::invalid_argument("Chamfer lengths must be positive");
  }

  TopTools_IndexedDataMapOfShapeListOfShape edgeFaceMap;
  TopExp::MapShapesAndAncestors(this->value(), TopAbs_EDGE, TopAbs_FACE,
                                edgeFaceMap);

  BRepFilletAPI_MakeChamfer chamferBuilder(this->value());
  double d1 = length;
  double d2 = length2 ? *length2 : length;

  for (const edge &e : edgeList) {
    const TopTools_ListOfShape &faces = edgeFaceMap.FindFromKey(e.value());
    if (faces.IsEmpty()) {
      throw std::runtime_error("Edge has no adjacent faces");
    }
    chamferBuilder.Add(d1, d2, e.value(), TopoDS::Face(faces.First()));
  }

  if (!chamferBuilder.IsDone()) {
    throw std::runtime_error("Failed to create chamfer");
  }

  return solid(chamferBuilder.Shape());
}

std::vector<flywave::topo::shell> shape3d::shells() const {
  std::vector<flywave::topo::shell> ret;
  TopExp_Explorer ex;
  for (ex.Init(_shape, TopAbs_SHELL); ex.More(); ex.Next()) {
    if (!ex.Current().IsNull()) {
      ret.push_back(flywave::topo::shell(ex.Current()));
    }
  }
  return ret;
}

shape shape3d::make_shell(const std::vector<face> &faceList, double thickness,
                          double tolerance, const std::string &kind) const {
  if (tolerance <= 0) {
    throw std::invalid_argument("Tolerance must be positive");
  }

  GeomAbs_JoinType joinType;
  if (kind == "arc") {
    joinType = GeomAbs_Arc;
  } else if (kind == "intersection") {
    joinType = GeomAbs_Intersection;
  } else {
    throw std::invalid_argument("Invalid join type");
  }

  TopTools_ListOfShape facesToRemove;
  for (const face &f : faceList) {
    facesToRemove.Append(f.value());
  }

  BRepOffsetAPI_MakeThickSolid shellBuilder;
  shellBuilder.MakeThickSolidByJoin(this->value(), facesToRemove, thickness,
                                    tolerance, BRepOffset_Skin,
                                    true, // Intersection
                                    joinType);
  shellBuilder.Build();

  if (!faceList.empty()) {
    return solid(shellBuilder.Shape());
  } else {
    flywave::topo::shell s1 = solid(shellBuilder.Shape()).shells()[0];
    flywave::topo::shell s2 = this->shells()[0];

    BRepBuilderAPI_MakeSolid solidMaker;
    if (thickness > 0) {
      solidMaker = BRepBuilderAPI_MakeSolid(s1.value(), s2.value());
    } else {
      solidMaker = BRepBuilderAPI_MakeSolid(s2.value(), s1.value());
    }

    if (!solidMaker.IsDone()) {
      throw std::runtime_error("Failed to create watertight shell");
    }

    return solid(solidMaker.Shape());
  }
}

bool shape3d::is_inside(const gp_Pnt &point, double tolerance) const {
  if (tolerance <= 0) {
    throw std::invalid_argument("Tolerance must be positive");
  }

  BRepClass3d_SolidClassifier classifier(this->value());
  classifier.Perform(point, tolerance);

  return classifier.State() == TopAbs_IN || classifier.IsOnAFace();
}

solid shape3d::dprism(const std::shared_ptr<face> &basis,
                      const std::vector<wire> &profiles,
                      const boost::optional<double> &depth, double taper,
                      const std::shared_ptr<face> &upToFace, bool thruAll,
                      bool additive) const {
  auto sortedProfiles = sort_wires_by_build_order(profiles);
  std::vector<face> faces;

  for (const auto &profileGroup : sortedProfiles) {
    if (profileGroup.empty())
      continue;

    wire outerWire = profileGroup[0];
    std::vector<wire> innerWires(profileGroup.begin() + 1, profileGroup.end());
    faces.push_back(face::make_face(outerWire, innerWires));
  }

  return this->dprism(basis, faces, depth, taper, upToFace, thruAll, additive);
}

solid shape3d::dprism(const std::shared_ptr<face> &basis,
                      const std::vector<face> &faces,
                      const boost::optional<double> &depth, double taper,
                      const std::shared_ptr<face> &upToFace, bool thruAll,
                      bool additive) const {
  TopoDS_Shape shape = this->value();
  const TopoDS_Face basisFace = basis ? basis->value() : TopoDS_Face();
  const double taperRad = taper * M_PI / 180.0;

  for (const face &f : faces) {
    BRepFeat_MakeDPrism prismBuilder(shape, f.value(), basisFace, taperRad,
                                     additive, false);

    if (upToFace) {
      prismBuilder.Perform(upToFace->value());
    } else if (thruAll || !depth) {
      prismBuilder.PerformThruAll();
    } else {
      prismBuilder.Perform(*depth);
    }

    if (!prismBuilder.IsDone()) {
      throw std::runtime_error("Failed to create prismatic feature");
    }

    shape = prismBuilder.Shape();
  }

  return solid(TopoDS::Solid(shape));
}
} // namespace topo
} // namespace flywave
