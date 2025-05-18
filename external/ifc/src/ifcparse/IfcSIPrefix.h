#ifndef IFCSIPREFIX
#define IFCSIPREFIX

#include <ifcparse/ifc_parse_api.h>

#include <string>

namespace IfcParse {
IFC_PARSE_API double IfcSIPrefixToValue(const std::string &prefix);

template <typename Schema>
IFC_PARSE_API double get_SI_equivalent(typename Schema::IfcNamedUnit *);
} // namespace IfcParse

#endif
