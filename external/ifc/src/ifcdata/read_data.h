#ifndef READ_DATA_STRUCTS_HH
#define READ_DATA_STRUCTS_HH

#include "ifc_data.h"

#include <ifcgeom/abstract_mapping.h>
#include <ifcparse/IfcFile.h>
#include <ifcparse/macros.h>

// clang-format off
#define INCLUDE_PARENT_PARENT_DIR(x) STRINGIFY(../ifcparse/x.h)
#include INCLUDE_PARENT_PARENT_DIR(IfcSchema)
#undef INCLUDE_PARENT_PARENT_DIR
#define INCLUDE_PARENT_PARENT_DIR(x) STRINGIFY(../ifcparse/x-definitions.h)
#include INCLUDE_PARENT_PARENT_DIR(IfcSchema)
// clang-format on

ifcopenshell::data::IfcData POSTFIX_SCHEMA(read_data)(IfcParse::IfcFile *file);

#endif // READ_DATA_STRUCTS_HH
