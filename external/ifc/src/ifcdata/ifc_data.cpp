#include "ifc_data.h"

#include <boost/algorithm/string/case_conv.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/stringize.hpp>

using namespace ifcopenshell;
using namespace ifcopenshell::data;

#ifndef SCHEMA_SEQ
static_assert(false, "A boost preprocessor sequence of schema identifiers is "
                     "needed for this file to compile.");
#endif

#define EXTERNAL_DEFS(r, data, elem)                                           \
  extern IfcData BOOST_PP_CAT(read_data_Ifc, elem)(IfcParse::IfcFile *);

#define CALL_FUNCS(r, data, elem)                                              \
  if (schema == BOOST_PP_STRINGIZE(BOOST_PP_CAT(ifc, elem))) {                  \
    return BOOST_PP_CAT(read_data_Ifc, elem)(file);                            \
  }

BOOST_PP_SEQ_FOR_EACH(EXTERNAL_DEFS, , SCHEMA_SEQ)

namespace ifcopenshell {
namespace data {

IfcData read_data(IfcParse::IfcFile *file) {
  auto schema = file->schema()->name();
  boost::algorithm::to_lower(schema);
  BOOST_PP_SEQ_FOR_EACH(CALL_FUNCS, , SCHEMA_SEQ)
}

} // namespace data
} // namespace ifcopenshell
