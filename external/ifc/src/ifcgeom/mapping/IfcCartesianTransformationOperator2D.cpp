#include <ifcgeom/mapping/mapping.h>
#define mapping POSTFIX_SCHEMA(mapping)
using namespace ifcopenshell::geometry;

taxonomy::ptr
mapping::map_impl(const IfcSchema::IfcCartesianTransformationOperator2D *inst) {
  auto m = taxonomy::make<taxonomy::matrix4>();

  Eigen::Vector4d origin, axis1(1.0, 0.0, 0.0, 0.0), axis2(0.0, 1.0, 0.0, 0.0),
      axis3(0.0, 0.0, 1.0, 0.0);

  taxonomy::point3::ptr O =
      taxonomy::cast<taxonomy::point3>(map(inst->LocalOrigin()));
  origin << *O->components_, 1.0;

  if (inst->Axis1()) {
    taxonomy::direction3::ptr ax1 =
        taxonomy::cast<taxonomy::direction3>(map(inst->Axis1()));
    axis1 << *ax1->components_, 0.0;
    if (!inst->Axis2()) {
      // orthogonal complement
      axis2 << -axis1(1), axis1(0), 0., 0.;
    }
  }
  if (inst->Axis2()) {
    taxonomy::direction3::ptr ax2 =
        taxonomy::cast<taxonomy::direction3>(map(inst->Axis2()));
    axis2 << *ax2->components_, 0.0;
    if (!inst->Axis2()) {
      // orthogonal complement
      axis1 << -axis2(1), axis2(0), 0., 0.;
    }
  }

  double scale1, scale2;
  scale1 = 1.0;

  if (inst->Scale()) {
    scale1 = *inst->Scale();
  }
  if (inst->as<IfcSchema::IfcCartesianTransformationOperator2DnonUniform>()) {
    auto nu =
        inst->as<IfcSchema::IfcCartesianTransformationOperator2DnonUniform>();
    scale2 = nu->Scale2() ? *nu->Scale2() : scale1;
  } else {
    scale2 = scale1;
  }

  m->components() << axis1 * scale1, axis2 * scale2, axis3, origin;

  // @todo why was this here
  // m->components().transposeInPlace();

  return m;
}
