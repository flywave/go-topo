#include <ifcgeom/mapping/mapping.h>
#define mapping POSTFIX_SCHEMA(mapping)
using namespace ifcopenshell::geometry;

#include <ifcgeom/profile_helper.h>

#include <boost/math/constants/constants.hpp>

/*
namespace {
        std::string format_edge(const TopoDS_Edge& e) {
                std::ostringstream oss;
                double _, __;
                TopoDS_Vertex v0, v1;

                auto crv = BRep_Tool::Curve(e, _, __);
                auto nm = crv->DynamicType()->Name();
                TopExp::Vertices(e, v0, v1, true);

                auto p0 = BRep_Tool::Pnt(v0);
                auto p1 = BRep_Tool::Pnt(v1);

                oss << "Edge" << std::endl << std::setprecision(2)
                        << " (" << p0.X() << " " << p0.Y() << " " << p0.Z() <<
")" << std::endl
                        << " (" << p1.X() << " " << p1.Y() << " " << p1.Z() <<
")" << std::endl
                        << nm << std::endl;

                return oss.str();
        }
}
*/

taxonomy::ptr mapping::map_impl(const IfcSchema::IfcSweptDiskSolid *inst) {
  auto loop = taxonomy::cast<taxonomy::loop>(map(inst->Directrix()));

  // Start- EndParam became optional in IFC4
#ifdef SCHEMA_IfcSweptDiskSolid_StartParam_IS_OPTIONAL
  auto sp = inst->StartParam();
  auto ep = inst->EndParam();
#else
  boost::optional<double> sp, ep;
  try {
    sp = inst->StartParam();
    ep = inst->EndParam();
  } catch (const IfcParse::IfcException &e) {
    Logger::Warning(e);
  }
#endif

  const double tol = settings_.get<settings::Precision>().get();

#ifdef SCHEMA_HAS_IfcSweptDiskSolidPolygonal
  if (inst->as<IfcSchema::IfcSweptDiskSolidPolygonal>()) {
    auto fr = inst->as<IfcSchema::IfcSweptDiskSolidPolygonal>()->FilletRadius();
    if (fr && *fr > tol) {
      fillet_loop(loop, *fr);
    }
  }
#endif

  std::vector<double> radii = {inst->Radius() * length_unit_};

  if (inst->InnerRadius()) {
    // Subtraction of pipes with small radii is unstable.
    radii.push_back(*inst->InnerRadius() * length_unit_);
  }

  auto f = taxonomy::make<taxonomy::face>();

  {
    for (auto it = radii.begin(); it != radii.end(); ++it) {
      const double r = *it;
      const bool exterior = it == radii.begin();

      auto c = taxonomy::make<taxonomy::circle>();
      c->radius = r;

      auto e = taxonomy::make<taxonomy::edge>();
      e->basis = c;
      e->start = 0.;
      e->end = 2 * boost::math::constants::pi<double>();
      // @todo allow identity by leaving unspecified?
      c->matrix = taxonomy::make<taxonomy::matrix4>();

      auto l = taxonomy::make<taxonomy::loop>();
      l->children = {e};
      l->external = exterior;

      f->children.push_back(l);
    }
  }

  return taxonomy::make<taxonomy::sweep_along_curve>(
      taxonomy::make<taxonomy::matrix4>(), f, nullptr, loop);
}
