// uncomment if you'd like negative or close to zero extrusion depths to succeed
// #define PERMISSIVE_EXTRUSION

#include <ifcgeom/mapping/mapping.h>
#define mapping POSTFIX_SCHEMA(mapping)
using namespace ifcopenshell::geometry;

taxonomy::ptr mapping::map_impl(const IfcSchema::IfcExtrudedAreaSolid *inst) {
  const double height = inst->Depth() * length_unit_;
  if (height < settings_.get<settings::Precision>().get()) {
    Logger::Message(Logger::LOG_ERROR,
                    "Non-positive extrusion height encountered for:", inst);
#ifndef PERMISSIVE_EXTRUSION
    return nullptr;
#endif
  }

  taxonomy::matrix4::ptr matrix;
  bool has_position = true;
#ifdef SCHEMA_IfcSweptAreaSolid_Position_IS_OPTIONAL
  has_position = inst->Position() != nullptr;
#endif
  if (has_position) {
    matrix = taxonomy::cast<taxonomy::matrix4>(map(inst->Position()));
  }

#ifdef PERMISSIVE_EXTRUSION
  if (abs(height) < getValue(GV_PRECISION)) {
    face->matrix = matrix;
    return face;
  }
#endif

  auto basis = map(inst->SweptArea());
  if (auto bases = taxonomy::dcast<taxonomy::collection>(basis)) {
    // @todo this requires a unified approach for all sweeps
    auto c = taxonomy::make<taxonomy::collection>();
    for (auto &f : bases->children) {
      c->children.push_back(taxonomy::make<taxonomy::extrusion>(
          matrix, taxonomy::cast<taxonomy::face>(f),
          taxonomy::cast<taxonomy::direction3>(map(inst->ExtrudedDirection())),
          height));
      c->children.back()->instance = inst;
    }
    return c;
  } else {
    return taxonomy::make<taxonomy::extrusion>(
        matrix, taxonomy::cast<taxonomy::face>(basis),
        taxonomy::cast<taxonomy::direction3>(map(inst->ExtrudedDirection())),
        height);
  }
}
