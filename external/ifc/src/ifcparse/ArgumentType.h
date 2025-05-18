#ifndef ARGUMENTTYPE_H
#define ARGUMENTTYPE_H

#include <ifcparse/IfcSchema.h>
#include <ifcparse/ifc_parse_api.h>

namespace IfcUtil {

enum ArgumentType {
  Argument_NULL,
  Argument_DERIVED,
  Argument_INT,
  Argument_BOOL,
  Argument_LOGICAL,
  Argument_DOUBLE,
  Argument_STRING,
  Argument_BINARY,
  Argument_ENUMERATION,
  Argument_ENTITY_INSTANCE,

  Argument_EMPTY_AGGREGATE,
  Argument_AGGREGATE_OF_INT,
  Argument_AGGREGATE_OF_DOUBLE,
  Argument_AGGREGATE_OF_STRING,
  Argument_AGGREGATE_OF_BINARY,
  Argument_AGGREGATE_OF_ENTITY_INSTANCE,

  Argument_AGGREGATE_OF_EMPTY_AGGREGATE,
  Argument_AGGREGATE_OF_AGGREGATE_OF_INT,
  Argument_AGGREGATE_OF_AGGREGATE_OF_DOUBLE,
  Argument_AGGREGATE_OF_AGGREGATE_OF_ENTITY_INSTANCE,

  Argument_UNKNOWN
};

IFC_PARSE_API ArgumentType
from_parameter_type(const IfcParse::parameter_type *);
IFC_PARSE_API ArgumentType make_aggregate(ArgumentType elem_type);
} // namespace IfcUtil

#endif
