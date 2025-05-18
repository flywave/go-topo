#include <ifcgeom/mapping/mapping.h>
#define mapping POSTFIX_SCHEMA(mapping)
using namespace ifcopenshell::geometry;

taxonomy::ptr mapping::map_impl(const IfcSchema::IfcEdge *inst) {
  if (!inst->EdgeStart()->declaration().is(
          IfcSchema::IfcVertexPoint::Class()) ||
      !inst->EdgeEnd()->declaration().is(IfcSchema::IfcVertexPoint::Class())) {
    Logger::Message(Logger::LOG_ERROR,
                    "Only IfcVertexPoints are supported for EdgeStart and -End",
                    inst);
    return nullptr;
  }

  IfcSchema::IfcPoint *pnt1 =
      ((IfcSchema::IfcVertexPoint *)inst->EdgeStart())->VertexGeometry();
  IfcSchema::IfcPoint *pnt2 =
      ((IfcSchema::IfcVertexPoint *)inst->EdgeEnd())->VertexGeometry();
  if (!pnt1->declaration().is(IfcSchema::IfcCartesianPoint::Class()) ||
      !pnt2->declaration().is(IfcSchema::IfcCartesianPoint::Class())) {
    Logger::Message(Logger::LOG_ERROR,
                    "Only IfcCartesianPoints are supported for VertexGeometry",
                    inst);
    return nullptr;
  }

  auto e = taxonomy::make<taxonomy::edge>();

  e->start = taxonomy::cast<taxonomy::point3>(map(pnt1));
  e->end = taxonomy::cast<taxonomy::point3>(map(pnt2));

  if (inst->as<IfcSchema::IfcEdgeCurve>()) {
    auto basis = map(inst->as<IfcSchema::IfcEdgeCurve>()->EdgeGeometry());
    auto loop = taxonomy::dcast<taxonomy::loop>(basis);
    if (loop && loop->children.size() == 1) {
      loop->calculate_linear_edge_curves();
      basis = loop->children[0]->basis;
    }
    e->basis = basis;
    e->curve_sense = inst->as<IfcSchema::IfcEdgeCurve>()->SameSense();
  }

  return e;
}
