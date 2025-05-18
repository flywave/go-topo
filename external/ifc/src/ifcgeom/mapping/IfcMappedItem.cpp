#include <ifcgeom/mapping/mapping.h>
#define mapping POSTFIX_SCHEMA(mapping)
using namespace ifcopenshell::geometry;

taxonomy::ptr mapping::map_impl(const IfcSchema::IfcMappedItem *inst) {
  IfcSchema::IfcCartesianTransformationOperator *transform =
      inst->MappingTarget();
  taxonomy::matrix4::ptr gtrsf =
      taxonomy::cast<taxonomy::matrix4>(map(transform));
  IfcSchema::IfcRepresentationMap *rmap = inst->MappingSource();
  IfcSchema::IfcAxis2Placement *placement = rmap->MappingOrigin();
  taxonomy::matrix4::ptr trsf2 =
      taxonomy::cast<taxonomy::matrix4>(map(placement));
  Eigen::Matrix4d res = gtrsf->ccomponents() * trsf2->ccomponents();

  // @todo immutable for caching?
  // @todo allow for multiple levels of matrix?
  auto shapes =
      taxonomy::dcast<taxonomy::collection>(map(rmap->MappedRepresentation()));
  if (shapes == nullptr) {
    if (failed_on_purpose_.find(rmap->MappedRepresentation()) !=
        failed_on_purpose_.end()) {
      // propagate
      failed_on_purpose_.insert(inst);
    }
    return shapes;
  }

  auto collection = taxonomy::make<taxonomy::collection>();
  collection->children.push_back(shapes);
  collection->matrix = taxonomy::make<taxonomy::matrix4>(res);

  if (shapes != nullptr) {
    for (auto &c : taxonomy::cast<taxonomy::collection>(shapes)->children) {
      // @todo previously style was also copied.
    }
  }

  return collection;
}
