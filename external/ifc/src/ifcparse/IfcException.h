#ifndef IFCEXCEPTION_H
#define IFCEXCEPTION_H

#include <ifcparse/ifc_parse_api.h>

#include <boost/lexical_cast.hpp>
#include <exception>
#include <string>

#ifdef _MSC_VER
// "C4275 can be ignored in Visual C++ if you are deriving from a type in the
// Standard C++ Library", https://msdn.microsoft.com/en-us/library/3tdb471s.aspx
#pragma warning(push)
#pragma warning(disable : 4275)
#endif

namespace IfcParse {
class IFC_PARSE_API IfcException : public std::exception {
private:
  std::string message_;

public:
  IfcException(const std::string &message) : message_(message) {}
  virtual ~IfcException() throw() {}
  virtual const char *what() const throw() { return message_.c_str(); }
};

class IFC_PARSE_API IfcAttributeOutOfRangeException : public IfcException {
public:
  IfcAttributeOutOfRangeException(const std::string &exception)
      : IfcException(exception) {}
  ~IfcAttributeOutOfRangeException() throw() {}
};

class IFC_PARSE_API IfcInvalidTokenException : public IfcException {
public:
  IfcInvalidTokenException(int token_start, const std::string &token_string,
                           const std::string &expected_type)
      : IfcException(std::string("Token ") + token_string + " at offset " +
                     boost::lexical_cast<std::string>(token_start) +
                     " invalid " + expected_type) {}
  IfcInvalidTokenException(int token_start, char character)
      : IfcException(std::string("Unexpected '") + std::string(1, character) +
                     "' at offset " +
                     boost::lexical_cast<std::string>(token_start)) {}
  ~IfcInvalidTokenException() throw() {}
};

} // namespace IfcParse

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif
