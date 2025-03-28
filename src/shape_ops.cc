#include <BOPAlgo_BOP.hxx>
#include <BOPAlgo_Builder.hxx>
#include <BOPAlgo_GlueEnum.hxx>
#include <BRepAlgoAPI_Check.hxx>
#include <BRepAlgoAPI_Cut.hxx>
#include <BRepAlgoAPI_Splitter.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepExtrema_DistShapeShape.hxx>
#include <BRepFilletAPI_MakeChamfer.hxx>
#include <BRepFilletAPI_MakeFillet.hxx>
#include <BRepOffsetAPI_MakeFilling.hxx>
#include <BRepOffsetAPI_MakePipeShell.hxx>
#include <BRepOffsetAPI_ThruSections.hxx>
#include <BRepOffset_MakeOffset.hxx>
#include <BRepPrimAPI_MakePrism.hxx>
#include <BRepPrimAPI_MakeRevol.hxx>
#include <BRepTools.hxx>
#include <BRep_Builder.hxx>
#include <GeomAbs_Shape.hxx>
#include <ShapeUpgrade_UnifySameDomain.hxx>
#include <TopExp_Explorer.hxx>
#include <TopTools_ListOfShape.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Vertex.hxx>
#include <TopoDS_Wire.hxx>
#include <gp_Ax1.hxx>
#include <gp_Vec.hxx>
#include <stdexcept>
#include <vector>
#include <cmath> // for M_PI

#include "shape_ops.hh"

namespace flywave {
namespace topo {

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

boost::optional<shape> cut(const shape &shp, const shape &tool, double tol,
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
    builder.AddTool(tool);

    builder.Perform();

    return boost::make_optional<shape>(builder.Shape());
  } catch (const std::exception &e) {
    std::cerr << "Error in fuse operation: " << e.what() << std::endl;
    return boost::none;
  }
}

boost::optional<shape> intersect(const shape &shape1, const shape &shape2,
                                 double tol, bool glue) {
  if (shape1.is_null()) {
    std::cerr << "Input shape is null " << std::endl;
    return boost::none;
  }
  try {
    BOPAlgo_BOP builder;
    builder.SetOperation(BOPAlgo_Operation::BOPAlgo_COMMON);
    set_builder_options(builder, tol, glue);

    builder.AddArgument(shape1);
    builder.AddTool(shape2);

    builder.Perform();

    return boost::make_optional<shape>(builder.Shape());
  } catch (const std::exception &e) {
    std::cerr << "Error in fuse operation: " << e.what() << std::endl;
    return boost::none;
  }
}

boost::optional<shape> split(const shape &shp, const shape &tool, double tol) {
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
    tools.Append(tool);
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
                               const std::vector<edge> &edges,
                               double distance) {
  if (baseShape.value().ShapeType() != TopAbs_SOLID &&
      baseShape.value().ShapeType() != TopAbs_SHELL) {
    std::cerr << "Base shape must be a Solid or Shell " << std::endl;
    return boost::none;
  }

  if (distance <= 0) {
    std::cerr << "Chamfer distance must be positive " << std::endl;
    return boost::none;
  }

  try {

    BRepFilletAPI_MakeChamfer builder(baseShape.value());

    for (const auto &e : edges) {
      if (e.is_null()) {
        throw std::invalid_argument("Invalid edge in chamfer list");
      }
      builder.Add(distance, e.value());
    }

    builder.Build();
    if (!builder.IsDone()) {
      throw std::runtime_error("Chamfer operation failed");
    }

    return boost::make_optional<shape>(builder.Shape());
  } catch (const std::exception &e) {
    std::cerr << "Error in fuse operation: " << e.what() << std::endl;
    return boost::none;
  }
}

boost::optional<shape> extrude(const shape &shp, const gp_Vec &direction) {
  if (shp.is_null()) {
    std::cerr << "Input shape is null " << std::endl;
    return boost::none;
  }
  try {
    std::vector<TopoDS_Shape> results;

    // 遍历所有可拉伸的子形状（顶点、边、线框、面）
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

boost::optional<shape> sweep(const shape &profile, const wire &path,
                             const wire *auxiliaryPath, bool makeSolid) {
  if (profile.is_null() || path.is_null()) {
    std::cerr << "Profile and path cannot be null: " << std::endl;
    return boost::none;
  }
  try {
    BRepOffsetAPI_MakePipeShell builder(path.value());

    if (auxiliaryPath) {
      builder.SetMode(auxiliaryPath->value(), true);
    } else {
      builder.SetMode(false);
    }

    if (profile.value().ShapeType() == TopAbs_FACE) {
      TopoDS_Wire outerWire = BRepTools::OuterWire(TopoDS::Face(profile));
      builder.Add(outerWire, false, false);
    } else {
      builder.Add(profile, false, false);
    }

    builder.Build();
    if (!builder.IsDone()) {
      throw std::runtime_error("Sweep operation failed");
    }

    if (makeSolid) {
      builder.MakeSolid();
    }

    return boost::make_optional<shape>(builder.Shape());
  } catch (const std::exception &e) {
    std::cerr << "Error in sweep operation: " << e.what() << std::endl;
    return boost::none;
  }
}

boost::optional<shape> sweep(const std::vector<shape> &profiles,
                             const wire &path, const wire *auxiliaryPath,
                             bool makeSolid) {
  if (profiles.empty() || path.is_null()) {
    std::cerr << "Invalid input parameters: " << std::endl;
    return boost::none;
  }
  try {
    BRepOffsetAPI_MakePipeShell builder(path.value());

    if (auxiliaryPath) {
      builder.SetMode(auxiliaryPath->value(), true);
    } else {
      builder.SetMode(false);
    }

    for (const auto &profile : profiles) {
      if (profile.value().ShapeType() == TopAbs_FACE) {
        TopoDS_Wire outerWire = BRepTools::OuterWire(TopoDS::Face(profile));
        builder.Add(outerWire, false, false);
      } else {
        builder.Add(profile, false, false);
      }
    }

    builder.Build();
    if (!builder.IsDone()) {
      throw std::runtime_error("Multi-section sweep failed");
    }

    if (makeSolid) {
      builder.MakeSolid();
    }

    return boost::make_optional<shape>(builder.Shape());
  } catch (const std::exception &e) {
    std::cerr << "Error in sweep operation: " << e.what() << std::endl;
    return boost::none;
  }
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

} // namespace topo
} // namespace flywave
