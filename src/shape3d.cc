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

bool shape3d::is_inside(const gp_Pnt &point, double tolerance) const {
  if (tolerance <= 0) {
    throw std::invalid_argument("Tolerance must be positive");
  }

  BRepClass3d_SolidClassifier classifier(this->value());
  classifier.Perform(point, tolerance);

  return classifier.State() == TopAbs_IN || classifier.IsOnAFace();
}

} // namespace topo
} // namespace flywave
