#ifndef ARGUMENT_H
#define ARGUMENT_H

#include <ifcparse/ArgumentType.h>
#include <ifcparse/ifc_parse_api.h>

#include <boost/dynamic_bitset.hpp>
#include <boost/logic/tribool.hpp>
#include <boost/shared_ptr.hpp>
#include <string>
#include <vector>

namespace IfcUtil {

IFC_PARSE_API const char *ArgumentTypeToString(ArgumentType argument_type);

/// Returns false when the string `s` contains character outside of {'0', '1'}
IFC_PARSE_API bool valid_binary_string(const std::string &string);
} // namespace IfcUtil

#endif
