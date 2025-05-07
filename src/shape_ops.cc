#include "shape_ops.hh"
#include <BOPAlgo_BOP.hxx>
#include <BOPAlgo_Builder.hxx>
#include <BOPAlgo_GlueEnum.hxx>
#include <BRepAlgoAPI_Check.hxx>
#include <BRepAlgoAPI_Cut.hxx>
#include <BRepAlgoAPI_Splitter.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeSolid.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepExtrema_DistShapeShape.hxx>
#include <BRepFeat_MakeDPrism.hxx>
#include <BRepFilletAPI_MakeChamfer.hxx>
#include <BRepFilletAPI_MakeFillet.hxx>
#include <BRepGProp.hxx>
#include <BRepIntCurveSurface_Inter.hxx>
#include <BRepOffsetAPI_MakeFilling.hxx>
#include <BRepOffsetAPI_MakePipeShell.hxx>
#include <BRepOffsetAPI_MakeThickSolid.hxx>
#include <BRepOffsetAPI_ThruSections.hxx>
#include <BRepOffset_MakeOffset.hxx>
#include <BRepPrimAPI_MakePrism.hxx>
#include <BRepPrimAPI_MakeRevol.hxx>
#include <BRepTools.hxx>
#include <BRep_Builder.hxx>
#include <GProp_GProps.hxx>
#include <GeomAPI_ProjectPointOnCurve.hxx>
#include <GeomAbs_JoinType.hxx>
#include <GeomAbs_Shape.hxx>
#include <Geom_TrimmedCurve.hxx>
#include <LocOpe_DPrism.hxx>
#include <STEPControl_Reader.hxx>
#include <ShapeUpgrade_UnifySameDomain.hxx>
#include <TopExp_Explorer.hxx>
#include <TopTools_ListOfShape.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Shell.hxx>
#include <TopoDS_Solid.hxx>
#include <TopoDS_Vertex.hxx>
#include <TopoDS_Wire.hxx>
#include <algorithm>
#include <cmath> // for M_PI
#include <gce_MakeDir.hxx>
#include <gce_MakeLin.hxx>
#include <gp_Ax1.hxx>
#include <gp_Dir.hxx>
#include <gp_Lin.hxx>
#include <gp_Pnt.hxx>
#include <gp_Vec.hxx>
#include <stdexcept>
#include <vector>

namespace flywave {
namespace topo {
namespace {

boost::optional<wire> _toWire(const shape &shp) {
  if (shp.shape_type() == TopAbs_WIRE) {
    return shp.cast<wire>();
  } else if (shp.shape_type() == TopAbs_FACE) {
    return wire::make_wire({*shp.cast<edge>()});
  }
  throw std::invalid_argument("Path must be either Wire or Edge");
}

static bool _setSweepMode(BRepOffsetAPI_MakePipeShell &builder,
                          const shape &path, const shape *mode) {
  if (mode == nullptr) {
    builder.SetMode(false);
    return false;
  }
  if (mode->shape_type() == TopAbs_VERTEX) {
    gp_Pnt pnt = *mode->cast<vertex>();
    builder.SetMode(mode->cast<vertex>()->value());
    return false;
  } else if (mode->shape_type() == TopAbs_WIRE) {
    builder.SetMode(mode->cast<wire>()->value());
    return true;
  } else if (mode->shape_type() == TopAbs_EDGE) {
    builder.SetMode(mode->cast<edge>()->value());
    return true;
  }
  throw std::invalid_argument("Invalid mode type");
}

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

TopoDS_Shape _extrudeAuxSpine(const TopoDS_Wire &profile,
                              const TopoDS_Wire &spine,
                              const TopoDS_Wire &auxSpine) {
  BRepOffsetAPI_MakePipeShell pipeMaker(spine);
  pipeMaker.SetMode(auxSpine);
  pipeMaker.Add(profile);
  pipeMaker.Build();

  if (!pipeMaker.IsDone()) {
    throw std::runtime_error("Auxiliary spine extrusion failed");
  }

  return pipeMaker.Shape();
}

} // namespace

void set_builder_options(BOPAlgo_Builder &builder, double tol = 0.0,
                         bool glue = false) {
  builder.SetRunParallel(true);
  builder.SetUseOBB(true);
  builder.SetNonDestructive(true);

  if (tol > 0.0) {
    builder.SetFuzzyValue(tol);
  }

  if (glue) {
    builder.SetGlue(BOPAlgo_GlueEnum::BOPAlgo_GlueFull);
  }
}

boost::optional<shape> fuse(const std::vector<shape> &shapes, double tol,
                            bool glue) {
  if (shapes.size() < 2) {
    std::cerr << "At least two shapes required for fuse " << std::endl;
    return boost::none;
  }
  try {
    BOPAlgo_BOP builder;
    builder.SetOperation(BOPAlgo_Operation::BOPAlgo_FUSE);
    set_builder_options(builder, tol, glue);

    builder.AddArgument(shapes[0]);
    for (size_t i = 1; i < shapes.size(); ++i) {
      builder.AddTool(shapes[i]);
    }
    builder.Perform();

    return boost::make_optional<shape>(builder.Shape());
  } catch (const std::exception &e) {
    std::cerr << "Error in fuse operation: " << e.what() << std::endl;
    return boost::none;
  }
}

boost::optional<shape> cut(const shape &shp, const shape &toCut, double tol,
                           bool glue) {
  if (shp.is_null()) {
    std::cerr << "Input shape is null " << std::endl;
    return boost::none;
  }
  try {
    BOPAlgo_BOP builder;
    builder.SetOperation(BOPAlgo_Operation::BOPAlgo_CUT);
    set_builder_options(builder, tol, glue);

    builder.AddArgument(shp.value());
    builder.AddTool(toCut);

    builder.Perform();

    return boost::make_optional<shape>(builder.Shape());
  } catch (const std::exception &e) {
    std::cerr << "Error in fuse operation: " << e.what() << std::endl;
    return boost::none;
  }
}

boost::optional<shape> cut(const shape &shp, const std::vector<shape> &toCuts,
                           double tol, bool glue) {
  if (shp.is_null()) {
    std::cerr << "Input shape is null " << std::endl;
    return boost::none;
  }
  try {
    BOPAlgo_BOP builder;
    builder.SetOperation(BOPAlgo_Operation::BOPAlgo_CUT);
    set_builder_options(builder, tol, glue);

    builder.AddArgument(shp.value());

    TopTools_ListOfShape theShapes;
    for (const auto &toCut : toCuts) {
      theShapes.Append(toCut.value());
    }
    builder.SetTools(theShapes);

    builder.Perform();

    return boost::make_optional<shape>(builder.Shape());
  } catch (const std::exception &e) {
    std::cerr << "Error in fuse operation: " << e.what() << std::endl;
    return boost::none;
  }
}

boost::optional<shape> intersect(const shape &shp, const shape &toIntersect,
                                 double tol, bool glue) {
  if (shp.is_null()) {
    std::cerr << "Input shape is null " << std::endl;
    return boost::none;
  }
  try {
    BOPAlgo_BOP builder;
    builder.SetOperation(BOPAlgo_Operation::BOPAlgo_COMMON);
    set_builder_options(builder, tol, glue);

    builder.AddArgument(shp);
    builder.AddTool(toIntersect);

    builder.Perform();

    return boost::make_optional<shape>(builder.Shape());
  } catch (const std::exception &e) {
    std::cerr << "Error in fuse operation: " << e.what() << std::endl;
    return boost::none;
  }
}

boost::optional<shape> intersect(const shape &shp,
                                 const std::vector<shape> &toIntersects,
                                 double tol, bool glue) {
  if (shp.is_null()) {
    std::cerr << "Input shape is null " << std::endl;
    return boost::none;
  }
  try {
    BOPAlgo_BOP builder;
    builder.SetOperation(BOPAlgo_Operation::BOPAlgo_COMMON);
    set_builder_options(builder, tol, glue);

    builder.AddArgument(shp);

    TopTools_ListOfShape theShapes;
    for (const auto &toIntersect : toIntersects) {
      theShapes.Append(toIntersect.value());
    }
    builder.SetTools(theShapes);
    builder.Perform();

    return boost::make_optional<shape>(builder.Shape());
  } catch (const std::exception &e) {
    std::cerr << "Error in fuse operation: " << e.what() << std::endl;
    return boost::none;
  }
}

boost::optional<shape> split(const shape &shp, const shape &splitters,
                             double tol) {
  return split(shp, {splitters}, tol);
}

boost::optional<shape> split(const shape &shp,
                             const std::vector<shape> &splitters, double tol) {
  if (shp.is_null()) {
    std::cerr << "Input shape is null " << std::endl;
    return boost::none;
  }
  try {
    BRepAlgoAPI_Splitter builder;
    builder.SetRunParallel(true);
    builder.SetUseOBB(true);

    if (tol > 0.0) {
      builder.SetFuzzyValue(tol);
    }

    TopTools_ListOfShape args;
    args.Append(shp.value());
    builder.SetArguments(args);

    TopTools_ListOfShape tools;
    for (const auto &splitter : splitters) {
      tools.Append(splitter.value());
    }
    builder.SetTools(tools);

    builder.Build();
    if (!builder.IsDone()) {
      throw std::runtime_error("Split operation failed");
    }

    return boost::make_optional<shape>(builder.Shape());
  } catch (const std::exception &e) {
    std::cerr << "Error in fuse operation: " << e.what() << std::endl;
    return boost::none;
  }
}

std::vector<face> faces_intersected_by_line(const shape &shp,
                                            const gp_Pnt &point,
                                            const gp_Dir &axis,
                                            double tolerance,
                                            intersection_direction direction) {
  gp_Lin line = gce_MakeLin(point, axis).Value();

  BRepIntCurveSurface_Inter intersectMaker;
  intersectMaker.Init(shp, line, tolerance);

  std::vector<std::pair<TopoDS_Face, double>> facesDist;

  while (intersectMaker.More()) {
    const gp_Pnt &interPt = intersectMaker.Pnt();
    double distance = point.SquareDistance(interPt);

    bool includeFace = true;

    if (direction != intersection_direction::None) {
      gce_MakeDir interDirMaker(point, interPt);

      if (interDirMaker.IsDone()) {
        gp_Dir interDir = interDirMaker.Value();

        if (direction == intersection_direction::AlongAxis) {
          includeFace =
              !interDir.IsOpposite(axis, tolerance) && (distance > tolerance);
        } else if (direction == intersection_direction::Opposite) {
          includeFace =
              interDir.IsOpposite(axis, tolerance) && (distance > tolerance);
        }
      } else {
        includeFace = false;
      }
    }

    if (includeFace) {
      facesDist.emplace_back(intersectMaker.Face(), distance);
    }

    intersectMaker.Next();
  }

  std::sort(facesDist.begin(), facesDist.end(),
            [](const auto &a, const auto &b) { return a.second < b.second; });

  std::vector<face> result;
  result.reserve(facesDist.size());
  for (const auto &pair : facesDist) {
    result.push_back(pair.first);
  }

  return result;
}

boost::optional<shape> fill(const shape &shp,
                            const std::vector<shape> &constraints) {
  if (shp.is_null()) {
    std::cerr << "Input shape is null " << std::endl;
    return boost::none;
  }
  try {
    BRepOffsetAPI_MakeFilling builder;

    for (TopExp_Explorer exp(shp.value(), TopAbs_EDGE); exp.More();
         exp.Next()) {
      builder.Add(TopoDS::Edge(exp.Current()), GeomAbs_C0);
    }

    for (const auto &c : constraints) {
      for (TopExp_Explorer exp(c, TopAbs_EDGE); exp.More(); exp.Next()) {
        builder.Add(TopoDS::Edge(exp.Current()), GeomAbs_C0, false);
      }
    }

    builder.Build();
    if (!builder.IsDone()) {
      throw std::runtime_error("Fill operation failed");
    }
    return boost::make_optional<shape>(builder.Shape());
  } catch (const std::exception &e) {
    std::cerr << "Error in fuse operation: " << e.what() << std::endl;
    return boost::none;
  }
}

boost::optional<shape> shelling(const shape &shp,
                                const std::vector<face> &faceList,
                                double thickness, double tolerance,
                                GeomAbs_JoinType joinType) {
  try {

    TopTools_ListOfShape facesToRemove;
    BRepOffsetAPI_MakeThickSolid shell_builder;

    // Convert face list to OCCT list
    for (const auto &face : faceList) {
      facesToRemove.Append(face.value());
    }

    // Create the thick solid
    shell_builder.MakeThickSolidByJoin(shp, facesToRemove, thickness, tolerance,
                                       BRepOffset_Skin,
                                       Standard_True,  // Intersection
                                       Standard_False, // SelfInter
                                       joinType);
    shell_builder.Build();
    if (!shell_builder.IsDone()) {
      throw std::runtime_error("Shell operation failed");
    }

    if (!faceList.empty()) {
      // Case 1: Faces were provided - return the result directly
      shape shp(shell_builder.Shape());
      if (shp.fix_shape()) {
        return shp;
      } else {
        throw std::runtime_error("Shape orientation fix failed");
      }
    } else {
      // Case 2: No faces provided - create watertight solid
      auto shells = shp.shells();
      if (shells.size() < 1) {
        throw std::runtime_error("Input shape has no shells");
      }

      TopoDS_Shell s1 = TopoDS::Shell(shell_builder.Shape());
      TopoDS_Shell s2 = shells[0].value();

      BRepBuilderAPI_MakeSolid solidMaker;
      if (thickness > 0) {
        solidMaker = BRepBuilderAPI_MakeSolid(s1, s2);
      } else {
        solidMaker = BRepBuilderAPI_MakeSolid(s2, s1);
      }

      if (!solidMaker.IsDone()) {
        throw std::runtime_error("Solid creation failed");
      }

      // Fix orientation and return
      shape shp(solidMaker.Shape());
      if (shp.fix_shape()) {
        return shp;
      } else {
        throw std::runtime_error("Shape orientation fix failed");
      }
    }
  } catch (const std::exception &e) {
    std::cerr << "Error in shelling operation: " << e.what() << std::endl;
    return boost::none;
  }
}

boost::optional<shape> fillet(const shape &shp, const std::vector<edge> &edges,
                              double radius) {
  if (shp.is_null()) {
    std::cerr << "Input shape is null " << std::endl;
    return boost::none;
  }
  try {
    BRepFilletAPI_MakeFillet builder(shp.value());

    for (const auto &e : edges) {
      builder.Add(radius, e.value());
    }

    builder.Build();
    if (!builder.IsDone()) {
      throw std::runtime_error("Fillet operation failed");
    }
    return boost::make_optional<shape>(builder.Shape());
  } catch (const std::exception &e) {
    std::cerr << "Error in fuse operation: " << e.what() << std::endl;
    return boost::none;
  }
}

boost::optional<shape> chamfer(const shape &baseShape,
                               const std::vector<edge> &edges, double distance,
                               boost::optional<double> distance2) {
  if (baseShape.value().ShapeType() != TopAbs_SOLID &&
      baseShape.value().ShapeType() != TopAbs_SHELL) {
    std::cerr << "Base shape must be a Solid or Shell " << std::endl;
    return boost::none;
  }
  if (distance <= 0) {
    std::cerr << "Chamfer distance must be positive " << std::endl;
    return boost::none;
  }
  if (distance2 && *distance2 <= 0) {
    std::cerr << "Chamfer distance must be positive " << std::endl;
    return boost::none;
  }

  try {
    TopTools_IndexedDataMapOfShapeListOfShape edgeFaceMap;
    TopExp::MapShapesAndAncestors(baseShape, TopAbs_EDGE, TopAbs_FACE,
                                  edgeFaceMap);

    BRepFilletAPI_MakeChamfer chamferBuilder(baseShape);

    const double d1 = distance;
    const double d2 = distance2.value_or(distance);

    for (const auto &edge : edges) {
      const TopoDS_Edge &occEdge = edge.value();

      if (!edgeFaceMap.Contains(occEdge)) {
        throw std::runtime_error("Edge not found in shape");
      }

      const TopoDS_Shape &faceShape = edgeFaceMap.FindFromKey(occEdge).First();
      if (faceShape.IsNull()) {
        throw std::runtime_error("No adjacent face found for edge");
      }

      chamferBuilder.Add(d1, d2, occEdge, TopoDS::Face(faceShape));
    }

    chamferBuilder.Build();
    if (!chamferBuilder.IsDone()) {
      throw std::runtime_error("Chamfer operation failed");
    }

    return boost::make_optional<shape>(chamferBuilder.Shape());
  } catch (const std::exception &e) {
    std::cerr << "Error in fuse operation: " << e.what() << std::endl;
    return boost::none;
  }
}

boost::optional<shape> extrude_linear(const topo::wire &outerWire,
                                      const std::vector<topo::wire> &innerWires,
                                      const gp_Vec &vecNormal, double taper) {
  face f;
  if (taper == 0.0) {
    f = face::make_face(outerWire, innerWires);
  } else {
    f = face::make_face(outerWire);
  }

  return extrude_linear(f, vecNormal, taper);
}

boost::optional<shape> extrude_linear(const topo::face &f,
                                      const gp_Vec &vecNormal, double taper) {
  if (taper == 0.0) {
    BRepPrimAPI_MakePrism prismBuilder(f.value(), vecNormal,
                                       true // Copy the face
    );

    prismBuilder.Build();

    if (!prismBuilder.IsDone()) {
      throw std::runtime_error("Prism creation failed");
    }

    return boost::make_optional<shape>(prismBuilder.Shape());
  } else {
    gp_Dir faceNormal = f.normal_at();
    double angle = vecNormal.Angle(faceNormal);
    int d = (angle < M_PI / 2) ? 1 : -1; // M_PI/2 = 90 degrees

    double height =
        (d * vecNormal.Magnitude()) / std::cos(taper * M_PI / 180.0);

    LocOpe_DPrism prismBuilder(f.value(), height, d * taper * M_PI / 180.0);

    return boost::make_optional<shape>(prismBuilder.Shape());
  }
}

boost::optional<shape> extrude(const shape &shp, const gp_Vec &direction) {
  if (shp.is_null()) {
    std::cerr << "Input shape is null " << std::endl;
    return boost::none;
  }
  try {
    std::vector<TopoDS_Shape> results;

    for (TopExp_Explorer exp(shp.value(), TopAbs_VERTEX); exp.More();
         exp.Next()) {
      BRepPrimAPI_MakePrism builder(exp.Current(), direction);
      builder.Build();
      if (builder.IsDone()) {
        results.push_back(builder.Shape());
      }
    }

    for (TopExp_Explorer exp(shp.value(), TopAbs_EDGE); exp.More();
         exp.Next()) {
      BRepPrimAPI_MakePrism builder(exp.Current(), direction);
      builder.Build();
      if (builder.IsDone()) {
        results.push_back(builder.Shape());
      }
    }

    for (TopExp_Explorer exp(shp.value(), TopAbs_WIRE); exp.More();
         exp.Next()) {
      BRepPrimAPI_MakePrism builder(exp.Current(), direction);
      builder.Build();
      if (builder.IsDone()) {
        results.push_back(builder.Shape());
      }
    }

    for (TopExp_Explorer exp(shp.value(), TopAbs_FACE); exp.More();
         exp.Next()) {
      BRepPrimAPI_MakePrism builder(exp.Current(), direction);
      builder.Build();
      if (builder.IsDone()) {
        results.push_back(builder.Shape());
      }
    }

    if (results.empty()) {
      throw std::runtime_error("No valid subshapes for extrusion");
    }

    if (results.size() == 1) {
      return boost::make_optional<shape>(results[0]);
    } else {
      TopoDS_Compound compound;
      BRep_Builder builder;
      builder.MakeCompound(compound);
      for (const auto &s : results) {
        builder.Add(compound, s);
      }
      return boost::make_optional<shape>(compound);
    }
  } catch (const std::exception &e) {
    std::cerr << "Error in extrude operation: " << e.what() << std::endl;
    return boost::none;
  }
}

boost::optional<shape> revolve(const shape &shp, const gp_Pnt &axisPoint,
                               const gp_Dir &axisDirection,
                               double angleDegrees) {
  if (shp.is_null()) {
    std::cerr << "Input shape is null " << std::endl;
    return boost::none;
  }
  try {
    gp_Ax1 axis(axisPoint, axisDirection);

    double angleRad = angleDegrees * M_PI / 180.0;

    std::vector<TopoDS_Shape> results;

    for (TopExp_Explorer exp(shp, TopAbs_VERTEX); exp.More(); exp.Next()) {
      BRepPrimAPI_MakeRevol builder(exp.Current(), axis, angleRad);
      builder.Build();
      if (builder.IsDone()) {
        results.push_back(builder.Shape());
      }
    }

    for (TopExp_Explorer exp(shp, TopAbs_EDGE); exp.More(); exp.Next()) {
      BRepPrimAPI_MakeRevol builder(exp.Current(), axis, angleRad);
      builder.Build();
      if (builder.IsDone()) {
        results.push_back(builder.Shape());
      }
    }

    for (TopExp_Explorer exp(shp, TopAbs_WIRE); exp.More(); exp.Next()) {
      BRepPrimAPI_MakeRevol builder(exp.Current(), axis, angleRad);
      builder.Build();
      if (builder.IsDone()) {
        results.push_back(builder.Shape());
      }
    }

    for (TopExp_Explorer exp(shp, TopAbs_FACE); exp.More(); exp.Next()) {
      BRepPrimAPI_MakeRevol builder(exp.Current(), axis, angleRad);
      builder.Build();
      if (builder.IsDone()) {
        results.push_back(builder.Shape());
      }
    }

    if (results.empty()) {
      throw std::runtime_error("No valid subshapes for revolution");
    }

    if (results.size() == 1) {
      return boost::make_optional<shape>(results[0]);
    } else {
      TopoDS_Compound compound;
      BRep_Builder builder;
      builder.MakeCompound(compound);
      for (const auto &s : results) {
        builder.Add(compound, s);
      }
      return boost::make_optional<shape>(compound);
    }
  } catch (const std::exception &e) {
    std::cerr << "Error in revolve operation: " << e.what() << std::endl;
    return boost::none;
  }
}

boost::optional<shape> revolve(const wire &outerWire,
                               const std::vector<wire> &innerWires,
                               double angleDegrees, const gp_Pnt &axisStart,
                               const gp_Pnt &axisEnd) {
  face f = face::make_face(outerWire, innerWires);
  return revolve(f, angleDegrees, axisStart, axisEnd);
}

boost::optional<shape> revolve(const face &f, double angleDegrees,
                               const gp_Pnt &axisStart, const gp_Pnt &axisEnd) {
  gp_Vec axisVec(axisStart, axisEnd);
  if (axisVec.Magnitude() < Precision::Confusion()) {
    throw std::invalid_argument("Axis start and end points are coincident");
  }

  gp_Ax1 revolutionAxis(axisStart, axisVec);

  double angleRadians = angleDegrees * M_PI / 180.0;

  BRepPrimAPI_MakeRevol revolBuilder(f.value(), revolutionAxis, angleRadians,
                                     true // Copy the shape
  );

  if (!revolBuilder.IsDone()) {
    throw std::runtime_error("Revolution operation failed");
  }

  return boost::make_optional<shape>(revolBuilder.Shape());
}

boost::optional<shape> offset(const shape &shp, double offset, bool cap,
                              bool both, double tol) {
  if (shp.is_null()) {
    std::cerr << "Input shape is null " << std::endl;
    return boost::none;
  }
  try {
    auto performOffset = [&](double offsetValue) -> std::vector<TopoDS_Shape> {
      std::vector<TopoDS_Shape> results;

      for (TopExp_Explorer exp(shp.value(), TopAbs_FACE); exp.More();
           exp.Next()) {
        BRepOffset_MakeOffset offsetter;
        offsetter.Initialize(TopoDS::Face(exp.Current()), offsetValue, tol,
                             BRepOffset_Mode::BRepOffset_Skin, false, false,
                             GeomAbs_Intersection, cap);

        offsetter.MakeOffsetShape();
        if (offsetter.IsDone()) {
          results.push_back(offsetter.Shape());
        }
      }

      for (TopExp_Explorer exp(shp.value(), TopAbs_SHELL); exp.More();
           exp.Next()) {
        BRepOffset_MakeOffset offsetter;
        offsetter.Initialize(TopoDS::Shell(exp.Current()), offsetValue, tol,
                             BRepOffset_Mode::BRepOffset_Skin, false, false,
                             GeomAbs_Intersection, cap);

        offsetter.MakeOffsetShape();
        if (offsetter.IsDone()) {
          results.push_back(offsetter.Shape());
        }
      }

      return results;
    };

    if (both) {
      auto positive = performOffset(offset);
      auto negative = performOffset(-offset);

      if (positive.empty() || negative.empty()) {
        throw std::runtime_error("Offset operation failed");
      }

      BRep_Builder builder;
      TopoDS_Compound compound;
      builder.MakeCompound(compound);

      for (const auto &shape : positive) {
        builder.Add(compound, shape);
      }
      for (const auto &shape : negative) {
        builder.Add(compound, shape);
      }

      return boost::make_optional<shape>(compound);
    } else {
      auto results = performOffset(offset);
      if (results.empty()) {
        throw std::runtime_error("Offset operation failed");
      }

      if (results.size() == 1) {
        return boost::make_optional<shape>(results[0]);
      }

      BRep_Builder builder;
      TopoDS_Compound compound;
      builder.MakeCompound(compound);
      for (const auto &shape : results) {
        builder.Add(compound, shape);
      }
      return boost::make_optional<shape>(compound);
    }
  } catch (const std::exception &e) {
    std::cerr << "Error in offset operation: " << e.what() << std::endl;
    return boost::none;
  }
}

boost::optional<shape> sweep(const wire &outerWire,
                             const std::vector<wire> &innerWires,
                             const shape &path, bool makeSolid, bool isFrenet,
                             const shape *mode,
                             transition_mode transitionMode) {
  auto pathWire = _toWire(path);

  if (!pathWire) {
    throw std::invalid_argument("Path must be either Edge or Wire");
  }

  std::vector<shape> shapes;
  std::vector<wire> allWires = {outerWire};
  allWires.insert(allWires.end(), innerWires.begin(), innerWires.end());

  for (const auto &wire : allWires) {
    BRepOffsetAPI_MakePipeShell builder(pathWire->value());

    bool translate = false;
    bool rotate = false;

    if (mode) {
      rotate = _setSweepMode(builder, path, mode);
    } else {
      builder.SetMode(isFrenet);
    }

    switch (transitionMode) {
    case transition_mode::TRANSFORMED:
      builder.SetTransitionMode(BRepBuilderAPI_Transformed);
      break;
    case transition_mode::ROUND:
      builder.SetTransitionMode(BRepBuilderAPI_RoundCorner);
      break;
    case transition_mode::RIGHT:
    default:
      builder.SetTransitionMode(BRepBuilderAPI_RightCorner);
      break;
    }

    builder.Add(wire.value(), translate, rotate);
    builder.Build();

    if (makeSolid) {
      builder.MakeSolid();
    }

    shapes.push_back(shape(builder.Shape()));
  }

  auto result = shapes[0];
  if (shapes.size() > 1) {
    std::vector<shape> innerShapes(shapes.begin() + 1, shapes.end());
    result = *cut(result, innerShapes);
  }

  return result;
}

boost::optional<shape> sweep(const face &face, const shape &path,
                             bool makeSolid, bool isFrenet, const shape *mode,
                             transition_mode transitionMode) {
  return sweep(face.outer_wire(), face.inner_wires(), path, makeSolid, isFrenet,
               mode, transitionMode);
}

boost::optional<shape> sweep_multi(const std::vector<shape> &profiles,
                                   const shape &path, bool makeSolid,
                                   bool isFrenet, const shape *mode) {
  TopoDS_Wire pathWire;
  if (path.shape_type() == TopAbs_EDGE) {
    pathWire = topo::wire::make_wire({*path.cast<edge>()}).value();
  } else {
    pathWire = path.cast<wire>()->value();
  }

  BRepOffsetAPI_MakePipeShell builder(pathWire);

  bool translate = false;
  bool rotate = false;

  if (mode) {
    rotate = _setSweepMode(builder, path, mode);
  } else {
    builder.SetMode(isFrenet);
  }

  for (const auto &profile : profiles) {
    TopoDS_Wire profileWire;
    if (profile.shape_type() == TopAbs_WIRE) {
      profileWire = profile.cast<wire>()->value();
    } else if (profile.shape_type() == TopAbs_FACE) {
      profileWire = profile.cast<face>()->outer_wire().value();
    } else {
      throw std::invalid_argument("Profile must be either Wire or Face");
    }

    builder.Add(profileWire, translate, rotate);
  }

  builder.Build();

  if (makeSolid) {
    builder.MakeSolid();
  }

  return boost::make_optional<shape>(builder.Shape());
}

GeomAbs_Shape to_continuity(const std::string &continuity) {
  if (continuity == "C1")
    return GeomAbs_C1;
  if (continuity == "C2")
    return GeomAbs_C2;
  if (continuity == "C3")
    return GeomAbs_C3;
  throw std::invalid_argument("Invalid continuity value");
}

Approx_ParametrizationType
to_parametrization(const std::string &parametrization) {
  if (parametrization == "uniform")
    return Approx_IsoParametric;
  if (parametrization == "chordal")
    return Approx_ChordLength;
  if (parametrization == "centripetal")
    return Approx_Centripetal;
  throw std::invalid_argument("Invalid parametrization value");
}

boost::optional<shape> loft(const std::vector<shape> &profiles, bool cap,
                            bool ruled, const std::string &continuity,
                            const std::string &parametrization, int degree,
                            bool compat, bool smoothing,
                            const std::array<double, 3> &weights) {
  if (profiles.size() < 2) {
    std::cerr << "At least two profiles required for loft" << std::endl;
    return boost::none;
  }
  try {
    BRepOffsetAPI_ThruSections builder(cap, ruled);
    builder.SetMaxDegree(degree);
    builder.CheckCompatibility(compat);
    builder.SetContinuity(to_continuity(continuity));
    builder.SetParType(to_parametrization(parametrization));
    builder.SetSmoothing(smoothing);
    builder.SetCriteriumWeight(weights[0], weights[1], weights[2]);

    for (const auto &profile : profiles) {
      switch (profile.value().ShapeType()) {
      case TopAbs_WIRE:
        builder.AddWire(TopoDS::Wire(profile));
        break;
      case TopAbs_VERTEX:
        builder.AddVertex(TopoDS::Vertex(profile));
        break;
      case TopAbs_EDGE: {
        BRepBuilderAPI_MakeWire wireMaker(TopoDS::Edge(profile));
        if (wireMaker.IsDone()) {
          builder.AddWire(wireMaker.Wire());
        }
        break;
      }
      case TopAbs_FACE: {
        TopoDS_Wire outerWire = BRepTools::OuterWire(TopoDS::Face(profile));
        builder.AddWire(outerWire);
        break;
      }
      default:
        throw std::invalid_argument("Unsupported profile type");
      }
    }

    builder.Build();
    if (!builder.IsDone()) {
      throw std::runtime_error("Loft operation failed");
    }
    return boost::make_optional<shape>(builder.Shape());
  } catch (const std::exception &e) {
    std::cerr << "Error in loft operation: " << e.what() << std::endl;
    return boost::none;
  }
}

boost::optional<shape> loft(const std::vector<face> &faceProfiles,
                            const std::string &continuity) {
  if (faceProfiles.size() < 2) {
    std::cerr << "At least two profiles required for loft" << std::endl;
    return boost::none;
  }
  try {
    BRepOffsetAPI_ThruSections outerBuilder(false, false);
    outerBuilder.SetContinuity(to_continuity(continuity));

    std::vector<BRepOffsetAPI_ThruSections> innerBuilders;

    TopTools_ListOfShape innerWires;
    TopoDS_Wire outerWire = BRepTools::OuterWire(faceProfiles[0].value());
    TopExp_Explorer exp(faceProfiles[0], TopAbs_WIRE);
    for (; exp.More(); exp.Next()) {
      TopoDS_Wire wire = TopoDS::Wire(exp.Current());
      if (!wire.IsSame(outerWire)) {
        innerWires.Append(wire);
      }
    }

    for (TopTools_ListIteratorOfListOfShape it(innerWires); it.More();
         it.Next()) {
      BRepOffsetAPI_ThruSections innerBuilder(false, false);
      innerBuilder.SetContinuity(to_continuity(continuity));
      innerBuilder.AddWire(TopoDS::Wire(it.Value()));
      innerBuilders.push_back(innerBuilder);
    }

    for (const auto &f : faceProfiles) {
      outerBuilder.AddWire(BRepTools::OuterWire(f.value()));

      TopTools_ListOfShape currentInners;
      TopoDS_Wire currentOuter = BRepTools::OuterWire(f.value());
      TopExp_Explorer expInner(f.value(), TopAbs_WIRE);
      for (; expInner.More(); expInner.Next()) {
        TopoDS_Wire wire = TopoDS::Wire(expInner.Current());
        if (!wire.IsSame(currentOuter)) {
          currentInners.Append(wire);
        }
      }

      int i = 0;
      for (TopTools_ListIteratorOfListOfShape it(currentInners);
           it.More() && i < innerBuilders.size(); it.Next(), i++) {
        innerBuilders[i].AddWire(TopoDS::Wire(it.Value()));
      }
    }

    outerBuilder.Build();
    if (!outerBuilder.IsDone()) {
      throw std::runtime_error("Outer loft failed");
    }
    TopoDS_Shape outerShape = outerBuilder.Shape();

    std::vector<TopoDS_Shape> innerShapes;
    for (auto &builder : innerBuilders) {
      builder.Build();
      if (builder.IsDone()) {
        innerShapes.push_back(builder.Shape());
      }
    }

    if (innerShapes.empty()) {
      return boost::make_optional<shape>(outerShape);
    } else {
      BRepAlgoAPI_Cut cutter;

      TopTools_ListOfShape arguments;
      arguments.Append(outerShape);
      cutter.SetArguments(arguments);

      TopTools_ListOfShape theTools;
      for (const auto &s : innerShapes) {
        theTools.Append(s);
      }
      cutter.SetTools(theTools);

      cutter.Build();
      if (!cutter.IsDone()) {
        throw std::runtime_error("Cutting inner holes failed");
      }
      return boost::make_optional<shape>(cutter.Shape());
    }

  } catch (const std::exception &e) {
    std::cerr << "Error in loft operation: " << e.what() << std::endl;
    return boost::none;
  }
}

boost::optional<shape> imprint(const std::vector<shape> &shapes, double tol,
                               bool glue,
                               std::map<std::string, shape> *history) {
  if (shapes.size() < 2) {
    std::cerr << "At least two shapes required for imprint" << std::endl;
    return boost::none;
  }
  try {
    BOPAlgo_Builder builder;
    builder.SetRunParallel(true);
    builder.SetUseOBB(true);
    builder.SetNonDestructive(true);

    if (tol > 0.0) {
      builder.SetFuzzyValue(tol);
    }

    if (glue) {
      builder.SetGlue(BOPAlgo_GlueEnum::BOPAlgo_GlueFull);
    }

    for (const auto &shape : shapes) {
      builder.AddArgument(shape);
    }

    builder.Perform();

    if (history != nullptr) {
      const TopTools_DataMapOfShapeListOfShape &images = builder.Images();

      for (const auto &s : shapes) {
        if (images.IsBound(s.value())) {
          const TopTools_ListOfShape &resultShapes = images.Find(s.value());
          if (!resultShapes.IsEmpty()) {
            (*history)[std::to_string(s.value().HashCode(INT_MAX))] =
                resultShapes.First();
          }
        }
      }
    }

    return boost::make_optional<shape>(builder.Shape());
  } catch (const std::exception &e) {
    std::cerr << "Error in imprint operation: " << e.what() << std::endl;
    return boost::none;
  }
}

boost::optional<shape> clean(const shape &s) {
  try {
    ShapeUpgrade_UnifySameDomain cleaner(s,
                                         true,  // 统一面
                                         true,  // 统一边
                                         true); // 统一顶点

    cleaner.AllowInternalEdges(false);
    cleaner.Build();

    return boost::make_optional<shape>(cleaner.Shape());
  } catch (const std::exception &e) {
    std::cerr << "Error in clean operation: " << e.what() << std::endl;
    return boost::none;
  }
}

bool check(
    const shape &shp,
    std::vector<std::pair<std::vector<shape>, BOPAlgo_CheckStatus>> *results,
    double tol) {
  BRepAlgoAPI_Check checker(shp);
  checker.SetRunParallel(true);
  checker.SetUseOBB(true);

  if (tol > 0.0) {
    checker.SetFuzzyValue(tol);
  }

  checker.Perform();

  if (results != nullptr) {
    results->clear();
    const BOPAlgo_ListOfCheckResult &checkResult = checker.Result();

    for (auto it = checkResult.begin(); it != checkResult.end(); ++it) {
      const BOPAlgo_CheckResult &checkResult = *it;

      BOPAlgo_CheckStatus status = checkResult.GetCheckStatus();

      const TopTools_ListOfShape &faultyShapes = checkResult.GetFaultyShapes1();

      std::vector<shape> shapes;
      for (TopTools_ListIteratorOfListOfShape it(faultyShapes); it.More();
           it.Next()) {
        shapes.push_back(it.Value());
      }
      results->emplace_back(shapes, status);
    }
  }

  return checker.IsValid();
}

std::pair<gp_Pnt, gp_Pnt> closest(const shape &shape1, const shape &shape2) {
  BRepExtrema_DistShapeShape distCalculator(shape1, shape2);
  distCalculator.Perform();

  if (!distCalculator.IsDone() || distCalculator.NbSolution() == 0) {
    throw std::runtime_error("Closest points calculation failed");
  }

  return {distCalculator.PointOnShape1(1), distCalculator.PointOnShape2(1)};
}

boost::optional<shape>
dprism(const shape &shp, const std::shared_ptr<face> &basis,
       const std::vector<wire> &profiles, const boost::optional<double> &depth,
       double taper, const face *upToFace, bool thruAll, bool additive) {
  auto sortedProfiles = sort_wires_by_build_order(profiles);
  std::vector<face> faces;

  for (const auto &profileGroup : sortedProfiles) {
    if (profileGroup.empty())
      continue;

    wire outerWire = profileGroup[0];
    std::vector<wire> innerWires(profileGroup.begin() + 1, profileGroup.end());
    faces.push_back(face::make_face(outerWire, innerWires));
  }

  return dprism(shp, basis, faces, depth, taper, upToFace, thruAll, additive);
}

boost::optional<shape>
dprism(const shape &shp, const std::shared_ptr<face> &basis,
       const std::vector<face> &faces, const boost::optional<double> &depth,
       double taper, const face *upToFace, bool thruAll, bool additive) {
  TopoDS_Shape shape_ = shp.value();
  const TopoDS_Face basisFace = basis ? basis->value() : TopoDS_Face();
  const double taperRad = taper * M_PI / 180.0;

  for (const face &f : faces) {
    BRepFeat_MakeDPrism prismBuilder(shape_, f.value(), basisFace, taperRad,
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

    shape_ = prismBuilder.Shape();
  }

  return boost::make_optional<shape>(shape_);
}

boost::optional<shape> extrude_linear_with_rotation(
    const wire &outerWire, const std::vector<wire> &innerWires,
    const gp_Pnt &center, const gp_Vec &normal, double angleDegrees) {
  gp_Pnt endPoint = center.Translated(normal);
  edge straightSpine = edge::make_polygon(center, endPoint);
  std::vector<shape> spines({straightSpine});
  TopoDS_Wire straightSpineWire = wire::combine(spines)[0].value();

  double pitch = (360.0 / angleDegrees) * normal.Magnitude();
  double radius = 1.0;
  wire auxSpine =
      wire::make_helix(pitch, normal.Magnitude(), radius, center, normal);
  TopoDS_Wire auxSpineWire = auxSpine.value();

  TopoDS_Shape outerSolid =
      _extrudeAuxSpine(outerWire.value(), straightSpineWire, auxSpineWire);

  std::vector<shape> innerSolids;
  for (const auto &wire : innerWires) {
    innerSolids.push_back(
        _extrudeAuxSpine(wire.value(), straightSpineWire, auxSpineWire));
  }

  topo::compound innerCompound = topo::compound::make_compound(innerSolids);

  BRepAlgoAPI_Cut cutter(outerSolid, innerCompound);
  if (!cutter.IsDone()) {
    throw std::runtime_error(
        "Cut operation failed in extrudeLinearWithRotation");
  }

  return boost::make_optional<shape>(cutter.Shape());
}

boost::optional<shape> extrude_linear_with_rotation(const face &face,
                                                    const gp_Pnt &center,
                                                    const gp_Vec &normal,
                                                    double angleDegrees) {
  return extrude_linear_with_rotation(face.outer_wire(), face.inner_wires(),
                                      center, normal, angleDegrees);
}

gp_Pnt combined_center(const std::vector<shape> &objects) {
  if (objects.empty()) {
    throw std::invalid_argument("Objects list cannot be empty");
  }

  double totalMass = 0.0;
  for (const auto &obj : objects) {
    totalMass += obj.compute_mass();
  }

  gp_Vec sumWeightedCenters(0, 0, 0);
  for (const auto &obj : objects) {
    double mass = obj.compute_mass();
    gp_Pnt com = obj.centre_of_mass();
    sumWeightedCenters += gp_Vec(com.X(), com.Y(), com.Z()) * mass;
  }

  gp_Vec result = sumWeightedCenters / totalMass;
  return gp_Pnt(result.X(), result.Y(), result.Z());
}

gp_Pnt combined_center_of_bound_box(const std::vector<shape> &objects) {
  if (objects.empty()) {
    throw std::invalid_argument("Objects list cannot be empty");
  }

  Bnd_Box combinedBox;
  for (const auto &obj : objects) {
    Bnd_Box objBox;
    BRepBndLib::Add(obj, objBox);
    combinedBox.Add(objBox);
  }

  double xMin, yMin, zMin, xMax, yMax, zMax;
  combinedBox.Get(xMin, yMin, zMin, xMax, yMax, zMax);
  return gp_Pnt((xMin + xMax) / 2.0, (yMin + yMax) / 2.0, (zMin + zMax) / 2.0);
}

shape read_shape_from_step(const std::string &filename) {
  STEPControl_Reader reader;
  IFSelect_ReturnStatus status = reader.ReadFile(filename.c_str());
  if (status != IFSelect_RetDone) {
    throw std::runtime_error("Failed to read STEP file");
  }
  reader.TransferRoots();
  TopoDS_Shape shp = reader.OneShape();
  return std::move(shp);
}

std::vector<wire_sample_point>
sample_wire_at_distances(const wire &wire_path,
                         const std::vector<double> &distances) {
  std::vector<wire_sample_point> results(distances.size());

  // 1. 使用map记录原始位置索引和距离
  std::map<size_t, double> indexedDistances;
  for (size_t i = 0; i < distances.size(); ++i) {
    indexedDistances[i] = distances[i];
  }

  // 2. 按距离值排序
  std::vector<std::pair<size_t, double>> sortedDistances(
      indexedDistances.begin(), indexedDistances.end());
  std::sort(sortedDistances.begin(), sortedDistances.end(),
            [](const auto &a, const auto &b) { return a.second < b.second; });

  // 3. 计算路径总长度
  GProp_GProps props;
  BRepGProp::LinearProperties(wire_path, props);
  double totalLength = props.Mass();

  // 4. 按排序后的距离执行采样
  for (auto it = sortedDistances.begin(); it != sortedDistances.end(); ++it) {
    size_t origIndex = it->first;
    double distance = it->second;

    if (distance < 0 || distance > totalLength) {
      continue;
    }

    wire_sample_point sample;
    double accumulatedLength = 0;
    bool found = false;

    TopExp_Explorer edgeExplorer(wire_path, TopAbs_EDGE);
    for (int edgeIndex = 0; edgeExplorer.More() && !found;
         edgeExplorer.Next(), edgeIndex++) {
      const TopoDS_Edge &e = TopoDS::Edge(edgeExplorer.Current());

      GProp_GProps edgeProps;
      BRepGProp::LinearProperties(e, edgeProps);
      double edgeLength = edgeProps.Mass();

      if (distance <= accumulatedLength + edgeLength) {
        BRepAdaptor_Curve curveAdaptor(e);
        double param =
            curveAdaptor.FirstParameter() +
            (distance - accumulatedLength) / edgeLength *
                (curveAdaptor.LastParameter() - curveAdaptor.FirstParameter());

        curveAdaptor.D1(param, sample.position, sample.tangent);
        sample.edge = edge(e);
        found = true;
      }
      accumulatedLength += edgeLength;
    }

    if (found) {
      results[origIndex] = sample;
    }
  }

  return results;
}

wire clip_wire_between_distances(const wire &wire_path, double start_distance,
                                 double end_distance) {
  if (start_distance < 0 || end_distance < 0 ||
      start_distance >= end_distance) {
    throw std::invalid_argument("Invalid distance range");
  }

  // 计算路径总长度
  GProp_GProps props;
  BRepGProp::LinearProperties(wire_path, props);
  double totalLength = props.Mass();

  if (end_distance > totalLength) {
    end_distance = totalLength;
  }

  if (start_distance >= totalLength) {
    throw std::invalid_argument("start_distance exceeds total wire length");
  }
  if (end_distance >= totalLength) {
    end_distance = totalLength;
  }

  BRepBuilderAPI_MakeWire wireBuilder;
  double accumulatedLength = 0;
  bool inRange = false;

  TopExp_Explorer edgeExplorer(wire_path, TopAbs_EDGE);
  for (; edgeExplorer.More(); edgeExplorer.Next()) {
    const TopoDS_Edge &edge = TopoDS::Edge(edgeExplorer.Current());

    // 获取原始边的定位和方向
    const TopLoc_Location &edgeLoc = edge.Location();
    TopAbs_Orientation edgeOrientation = edge.Orientation();

    // 计算当前边的长度
    GProp_GProps edgeProps;
    BRepGProp::LinearProperties(edge, edgeProps);
    double edgeLength = edgeProps.Mass();

    double edgeStart = accumulatedLength;
    double edgeEnd = accumulatedLength + edgeLength;

    // 检查边是否在区间内
    if (edgeEnd <= start_distance) {
      accumulatedLength += edgeLength;
      continue;
    }

    if (edgeStart >= end_distance) {
      break;
    }

    // 获取边的几何曲线
    BRepAdaptor_Curve curveAdaptor(edge);
    Handle(Geom_Curve) curve = curveAdaptor.Curve().Curve();

    // 检查曲线是否是周期性的(如圆弧)
    bool isPeriodic = curve->IsPeriodic();
    double period = isPeriodic ? curve->Period() : 0.0;

    // 计算截取参数
    double param1 = curveAdaptor.FirstParameter();
    double param2 = curveAdaptor.LastParameter();

    if (edgeStart < start_distance && edgeEnd > start_distance) {
      double ratio = (start_distance - edgeStart) / edgeLength;
      param1 = curveAdaptor.FirstParameter() +
               ratio * (curveAdaptor.LastParameter() -
                        curveAdaptor.FirstParameter());
    }

    if (edgeStart < end_distance && edgeEnd > end_distance) {
      double ratio = (end_distance - edgeStart) / edgeLength;
      param2 = curveAdaptor.FirstParameter() +
               ratio * (curveAdaptor.LastParameter() -
                        curveAdaptor.FirstParameter());
    }

    // 创建截取后的曲线
    Handle(Geom_TrimmedCurve) trimmedCurve =
        new Geom_TrimmedCurve(curve, param1, param2);

    BRepBuilderAPI_MakeEdge makeEdge(trimmedCurve);
    if (!makeEdge.IsDone())
      continue;

    TopoDS_Edge newEdge = makeEdge.Edge();
    newEdge.Location(edgeLoc);
    newEdge.Orientation(edgeOrientation);

    wireBuilder.Add(newEdge);

    accumulatedLength += edgeLength;
  }

  if (!wireBuilder.IsDone()) {
    throw std::runtime_error("Failed to create sub wire");
  }

  return wire(wireBuilder.Wire());
}

profile_projection cacl_profile_projection(wire path, gp_Dir upDir,
                                           boost::optional<double> offset) {
  // 获取路径起始点的切线方向
  gp_Pnt startPoint;
  gp_Vec startTangent;
  BRepAdaptor_CompCurve curveAdaptor(path.value());

  if (offset) {
    double length = path.length();

    if (*offset > length) {
      *offset = length;
    }

    if (*offset < 0) {
      *offset = 0;
    }

    double ratio = *offset / length;
    curveAdaptor.D1(
        curveAdaptor.FirstParameter() +
            (curveAdaptor.LastParameter() - curveAdaptor.FirstParameter()) *
                ratio,
        startPoint, startTangent);
  } else {
    curveAdaptor.D1(curveAdaptor.FirstParameter(), startPoint, startTangent);
  }

  // 在创建截面圆之前添加方向修正
  gp_Dir tanDir = startTangent.Normalized();
  gp_Dir refDir = gp_Vec(upDir.Crossed(tanDir)).Normalized();

  // 如果参考方向长度接近0(切线几乎与径向平行)，使用全局Y轴作为备用
  if (gp_Vec(refDir).SquareMagnitude() < Precision::SquareConfusion()) {
    refDir = gp::DY();
  }

  gp_Ax2 sectionAxes(startPoint, tanDir, refDir);

  // 创建变换对象
  gp_Trsf trsf;

  trsf.SetTransformation(sectionAxes, gp_Ax2(gp::Origin(), gp::DZ()));

  return {.axes = sectionAxes,
          .trsf = trsf,
          .tangent = startTangent.Normalized(),
          .position = startPoint};
}

gp_Pnt profile_project_point(profile_projection *proj, gp_Pnt point) {
  return proj->axes.Location().Translated(
      gp_Vec(point.Z(), point.Y(), 0).Transformed(proj->trsf));
}

double wrie_length(wire path) {
  try {
    return path.length();
  } catch (const std::exception &e) {
    return 0.0;
  }
}

} // namespace topo
} // namespace flywave
