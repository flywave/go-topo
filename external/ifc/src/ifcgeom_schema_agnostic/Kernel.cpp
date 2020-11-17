#include "Kernel.h"

#include <TopExp.hxx>
#include <TopTools_IndexedDataMapOfShapeListOfShape.hxx>
#include <TopTools_IndexedMapOfShape.hxx>
#include <TopTools_ListOfShape.hxx>

namespace IFC_NAMESPACE {
IfcGeom::Kernel::Kernel(IfcParse::IfcFile *file) {
  if (file != 0) {
    if (file->schema() == 0) {
      throw IfcParse::IfcException("No schema associated with file");
    }

    const std::string &schema_name = file->schema()->name();
    implementation_ =
        impl::kernel_implementations().construct(schema_name, file);
  }
}

int IfcGeom::Kernel::count(const TopoDS_Shape &s, TopAbs_ShapeEnum t,
                           bool unique) {
  if (unique) {
    TopTools_IndexedMapOfShape map;
    TopExp::MapShapes(s, t, map);
    return map.Extent();
  } else {
    int i = 0;
    TopExp_Explorer exp(s, t);
    for (; exp.More(); exp.Next()) {
      ++i;
    }
    return i;
  }
}

int IfcGeom::Kernel::surface_genus(const TopoDS_Shape &s) {
  int nv = count(s, TopAbs_VERTEX, true);
  int ne = count(s, TopAbs_EDGE, true);
  int nf = count(s, TopAbs_FACE, true);

  const int euler = nv - ne + nf;
  const int genus = (2 - euler) / 2;

  return genus;
}

IfcGeom::impl::KernelFactoryImplementation &
IfcGeom::impl::kernel_implementations() {
  static KernelFactoryImplementation impl;
  return impl;
}

extern void MAKE_TYPE_NAME(init_KernelImplementation_)(
    IfcGeom::impl::KernelFactoryImplementation *);
// extern void
// init_KernelImplementation_Ifc4(IfcGeom::impl::KernelFactoryImplementation*);
// extern void
// init_KernelImplementation_Ifc4x1(IfcGeom::impl::KernelFactoryImplementation*);
// extern void
// init_KernelImplementation_Ifc4x2(IfcGeom::impl::KernelFactoryImplementation*);
// extern void
// init_KernelImplementation_Ifc4x3_rc1(IfcGeom::impl::KernelFactoryImplementation*);

IfcGeom::impl::KernelFactoryImplementation::KernelFactoryImplementation() {
  MAKE_TYPE_NAME(init_KernelImplementation_)(this);
  // init_KernelImplementation_Ifc4(this);
  // init_KernelImplementation_Ifc4x1(this);
  // init_KernelImplementation_Ifc4x2(this);
  // init_KernelImplementation_Ifc4x3_rc1(this);
}

void IfcGeom::impl::KernelFactoryImplementation::bind(
    const std::string &schema_name, IfcGeom::impl::kernel_fn fn) {
  const std::string schema_name_lower = boost::to_lower_copy(schema_name);
  this->insert(std::make_pair(schema_name_lower, fn));
}

IfcGeom::Kernel *IfcGeom::impl::KernelFactoryImplementation::construct(
    const std::string &schema_name, IfcParse::IfcFile *file) {
  const std::string schema_name_lower = boost::to_lower_copy(schema_name);
  std::map<std::string, IfcGeom::impl::kernel_fn>::const_iterator it;
  it = this->find(schema_name_lower);
  if (it == end()) {
    throw IfcParse::IfcException("No geometry kernel registered for " +
                                 schema_name);
  }
  return it->second(file);
}

#define CREATE_GET_DECOMPOSING_ENTITY(IfcSchema)                               \
                                                                               \
  IFC_NAMESPACE::IfcSchema::IfcObjectDefinition *get_decomposing_entity_impl(                 \
      IFC_NAMESPACE::IfcSchema::IfcProduct *product, bool include_openings) {                 \
    IFC_NAMESPACE::IfcSchema::IfcObjectDefinition *parent = 0;                                \
                                                                               \
    /* In case of an opening element, parent to the RelatingBuildingElement */ \
    if (include_openings &&                                                    \
        product->declaration().is(IFC_NAMESPACE::IfcSchema::IfcOpeningElement::Class())) {    \
      IFC_NAMESPACE::IfcSchema::IfcOpeningElement *opening =                                  \
          (IFC_NAMESPACE::IfcSchema::IfcOpeningElement *)product;                             \
      IFC_NAMESPACE::IfcSchema::IfcRelVoidsElement::list::ptr voids =                         \
          opening->VoidsElements();                                            \
      if (voids->size()) {                                                     \
        IFC_NAMESPACE::IfcSchema::IfcRelVoidsElement *ifc_void = *voids->begin();             \
        parent = ifc_void->RelatingBuildingElement();                          \
      }                                                                        \
    } else if (product->declaration().is(IFC_NAMESPACE::IfcSchema::IfcElement::Class())) {    \
      IFC_NAMESPACE::IfcSchema::IfcElement *element = (IFC_NAMESPACE::IfcSchema::IfcElement *)product;       \
      IFC_NAMESPACE::IfcSchema::IfcRelFillsElement::list::ptr fills = element->FillsVoids();  \
      /* In case of a RelatedBuildingElement parent to the opening element */  \
      if (fills->size() && include_openings) {                                 \
        for (IFC_NAMESPACE::IfcSchema::IfcRelFillsElement::list::it it = fills->begin();      \
             it != fills->end(); ++it) {                                       \
          IFC_NAMESPACE::IfcSchema::IfcRelFillsElement *fill = *it;                           \
          IFC_NAMESPACE::IfcSchema::IfcObjectDefinition *ifc_objectdef =                      \
              fill->RelatingOpeningElement();                                  \
          if (product == ifc_objectdef)                                        \
            continue;                                                          \
          parent = ifc_objectdef;                                              \
        }                                                                      \
      }                                                                        \
      /* Else simply parent to the containing structure */                     \
      if (!parent) {                                                           \
        IFC_NAMESPACE::IfcSchema::IfcRelContainedInSpatialStructure::list::ptr parents =      \
            element->ContainedInStructure();                                   \
        if (parents->size()) {                                                 \
          IFC_NAMESPACE::IfcSchema::IfcRelContainedInSpatialStructure *container =            \
              *parents->begin();                                               \
          parent = container->RelatingStructure();                             \
        }                                                                      \
      }                                                                        \
    }                                                                          \
                                                                               \
    /* Parent decompositions to the RelatingObject */                          \
    if (!parent) {                                                             \
      IfcEntityList::ptr parents = product->data().getInverse(                 \
          (&IFC_NAMESPACE::IfcSchema::IfcRelAggregates::Class()), -1);                        \
      parents->push(                                                           \
          product->data().getInverse((&IFC_NAMESPACE::IfcSchema::IfcRelNests::Class()), -1)); \
      for (IfcEntityList::it it = parents->begin(); it != parents->end();      \
           ++it) {                                                             \
        IFC_NAMESPACE::IfcSchema::IfcRelDecomposes *decompose =                               \
            (IFC_NAMESPACE::IfcSchema::IfcRelDecomposes *)*it;                                \
        IfcUtil::IfcBaseEntity *ifc_objectdef;                                 \
                                                                               \
        ifc_objectdef = get_RelatingObject(decompose);                         \
                                                                               \
        if (product == ifc_objectdef)                                          \
          continue;                                                            \
        parent = ifc_objectdef->as<IFC_NAMESPACE::IfcSchema::IfcObjectDefinition>();          \
      }                                                                        \
    }                                                                          \
    return parent;                                                             \
  }

namespace {

#ifdef USE_23
IfcUtil::IfcBaseEntity *
get_RelatingObject(IFC_NAMESPACE::IfcSchema::IfcRelDecomposes *decompose) {
  return decompose->RelatingObject();
}
#else
IfcUtil::IfcBaseEntity *
get_RelatingObject(IFC_NAMESPACE::IfcSchema::IfcRelDecomposes *decompose) {
  IFC_NAMESPACE::IfcSchema::IfcRelAggregates *aggr =
      decompose->as<IFC_NAMESPACE::IfcSchema::IfcRelAggregates>();
  if (aggr != nullptr) {
    return aggr->RelatingObject();
  }
  return nullptr;
}
#endif
CREATE_GET_DECOMPOSING_ENTITY(IfcSchema);
} // namespace

IfcUtil::IfcBaseEntity *
IfcGeom::Kernel::get_decomposing_entity(IfcUtil::IfcBaseEntity *inst,
                                        bool include_openings) {
  return get_decomposing_entity_impl(inst->as<IFC_NAMESPACE::IfcSchema::IfcProduct>(),
                                     include_openings);
}

namespace {
static std::map<std::string, IfcUtil::IfcBaseEntity *>
get_layers_impl(typename IFC_NAMESPACE::IfcSchema::IfcProduct *prod) {
  std::map<std::string, IfcUtil::IfcBaseEntity *> layers;
  if (prod->hasRepresentation()) {
    IfcEntityList::ptr r = IfcParse::traverse(prod->Representation());
    typename IFC_NAMESPACE::IfcSchema::IfcRepresentation::list::ptr representations =
        r->as<typename IFC_NAMESPACE::IfcSchema::IfcRepresentation>();
    for (typename IFC_NAMESPACE::IfcSchema::IfcRepresentation::list::it it =
             representations->begin();
         it != representations->end(); ++it) {
      typename IFC_NAMESPACE::IfcSchema::IfcPresentationLayerAssignment::list::ptr a =
          (*it)->LayerAssignments();
      for (typename IFC_NAMESPACE::IfcSchema::IfcPresentationLayerAssignment::list::it jt =
               a->begin();
           jt != a->end(); ++jt) {
        layers[(*jt)->Name()] = *jt;
      }
    }
  }
  return layers;
}
} // namespace

std::map<std::string, IfcUtil::IfcBaseEntity *>
IfcGeom::Kernel::get_layers(IfcUtil::IfcBaseEntity *inst) {
  return get_layers_impl(inst->as<IFC_NAMESPACE::IfcSchema::IfcProduct>());
}

bool IfcGeom::Kernel::is_manifold(const TopoDS_Shape &a) {
  if (a.ShapeType() == TopAbs_COMPOUND || a.ShapeType() == TopAbs_SOLID) {
    TopoDS_Iterator it(a);
    for (; it.More(); it.Next()) {
      if (!is_manifold(it.Value())) {
        return false;
      }
    }
    return true;
  } else {
    TopTools_IndexedDataMapOfShapeListOfShape map;
    TopExp::MapShapesAndAncestors(a, TopAbs_EDGE, TopAbs_FACE, map);

    for (int i = 1; i <= map.Extent(); ++i) {
      if (map.FindFromIndex(i).Extent() != 2) {
        return false;
      }
    }

    return true;
  }
}
} // namespace IFC_NAMESPACE
