#pragma once

#undef IFCWRITE_H
#undef IFCPARSE_UTILS_H
#undef IFCSPFSTREAM_H
#undef IFCSPFHEADER_H
#undef IFCSIPREFIX
#undef IFCSCHEMA_H
#undef IFCPARSE_H
#undef IFCLOGGER_H
#undef IFCHIERARCHYHELPER_H
#undef IFCGLOBALID_H
#undef IFCFILE_H
#undef IFCEXCEPTION_H
#undef IFCENTITYLIST_H
#undef IFCENTITYINSTANCEDATA_H
#undef IFCCHARACTERDECODER_H
#undef IFCBASECLASS_H
#undef ARGUMENTTYPE_H
#undef ARGUMENT_H
#undef ITERATOR_KERNEL_H
#undef ITERATOR_IMPLEMENTATION_H
#undef IFCGEOMRENDERSTYLES_H
#undef IFCGEOMMATERIAL_H
#undef IFCGEOMITERATOR_H
#undef IFCGEOMFILTER_H
#undef IFCSHAPELIST_H
#undef IFCGEOMTREE_H
#undef IFCGEOMSHAPETYPE_H
#undef IFCGEOMREPRESENTATION_H
#undef IFCGEOMITERATORSETTINGS_H
#undef IFCGEOMITERATORIMPLEMENTION_H
#undef IFCGEOMELEMENT_H
#undef IFCGEOM_H

#include "ifcparse/Ifc4x3_rc1-definitions.h"
#include "ifc.h"

#define IFC_NAMESPACE ifc43_rc1
#define IfcSchema Ifc4x3_rc1
#define USE_43_RC1
namespace IFC_NAMESPACE{
  
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
#include "ifcparse/Ifc4x3_rc1.h"
 
#undef IfcSchema
#undef IFC_NAMESPACE
#undef USE_43_RC1