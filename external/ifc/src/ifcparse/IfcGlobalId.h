#ifndef IFCGLOBALID_H
#define IFCGLOBALID_H

#include <ifcparse/ifc_parse_api.h>

#include <boost/uuid/uuid.hpp>
#include <string>

namespace IfcParse {

/// A helper class for the creation of IFC GlobalIds.
class IFC_PARSE_API IfcGlobalId {
private:
  std::string string_data_;
  std::string formatted_string_;
  boost::uuids::uuid uuid_data_;

public:
  static const unsigned int length = 22;
  IfcGlobalId();
  IfcGlobalId(const std::string &);
  operator const std::string &() const;
  operator const boost::uuids::uuid &() const;
  const std::string &formatted() const;
};

} // namespace IfcParse

#endif
