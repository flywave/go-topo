#pragma once

#define IFC_NAMESPACE ifc23
namespace  IFC_NAMESPACE{
  #define IfcSchema Ifc2x3
}
#include "ifcgeom/ifc_geom_api.h"
#include "ifcgeom/IfcGeom.h"
#include "ifcgeom/IfcGeomElement.h"
#include "ifcgeom/IfcGeomRepresentation.h"
#include "ifcgeom/IfcGeomShapeType.h"
#include "ifcgeom/IfcRepresentationShapeItem.h"
#include "ifcgeom/IfcGeomIteratorImplementation.h"
#include "ifcgeom/IfcGeomTree.h"
#include "ifcgeom/IfcGeomShapeType.h"

#include "ifcgeom_schema_agnostic/IfcGeomFilter.h"
#include "ifcgeom_schema_agnostic/IfcGeomIterator.h"
#include "ifcgeom_schema_agnostic/IfcGeomMaterial.h"
#include "ifcgeom_schema_agnostic/IfcGeomRenderStyles.h"
#include "ifcgeom_schema_agnostic/IteratorImplementation.h"
#include "ifcgeom_schema_agnostic/Kernel.h"
#include "ifcgeom_schema_agnostic/Serialization.h"


#include "ifcparse/ifc_parse_api.h"
#include "ifcparse/Argument.h"
#include "ifcparse/ArgumentType.h"
#include "ifcparse/IfcBaseClass.h"
#include "ifcparse/IfcEntityInstanceData.h"
#include "ifcparse/IfcEntityList.h"
#include "ifcparse/IfcLogger.h"
#include "ifcparse/IfcSchema.h"
#include "ifcparse/IfcCharacterDecoder.h"
#include "ifcparse/IfcException.h"
#include "ifcparse/IfcFile.h"
#include "ifcparse/IfcGlobalId.h"
#include "ifcparse/IfcHierarchyHelper.h"
#include "ifcparse/IfcParse.h"
#include "ifcparse/IfcSIPrefix.h"
#include "ifcparse/IfcSpfHeader.h"
#include "ifcparse/IfcSpfStream.h"
#include "ifcparse/IfcWrite.h"
#include "ifcparse/macros.h"
#include "ifcparse/utils.h"
#include "ifcparse/Ifc2x3-definitions.h"
#include "ifcparse/Ifc2x3.h"

#undef IFC_NAMESPACE
