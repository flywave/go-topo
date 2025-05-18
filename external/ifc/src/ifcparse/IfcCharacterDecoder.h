#ifndef IFCCHARACTERDECODER_H
#define IFCCHARACTERDECODER_H

#include <ifcparse/IfcSpfStream.h>

#include <string>

namespace IfcUtil {
std::wstring::value_type convert_codepage(int codepage, int index);
std::string convert_utf8(const std::wstring &string);
std::wstring convert_utf8(const std::string &string);
std::u32string convert_utf8_to_utf32(const std::string &string);
} // namespace IfcUtil

namespace IfcParse {

class IFC_PARSE_API IfcCharacterDecoder {
private:
  IfcParse::IfcSpfStream *stream_;
  int codepage_;

public:
  enum ConversionMode { SUBSTITUTE, UTF8, ESCAPE };
  static ConversionMode mode;
  static char substitution_character;
  IfcCharacterDecoder(IfcParse::IfcSpfStream *stream);
  ~IfcCharacterDecoder();
  // Only advances the underlying token stream read pointer
  // to the next token.
  void skip();
  // Gets a decoded string representation at the token stream
  // read pointer and advances the underlying token stream.
  operator std::string();
  // Gets a decoded string representation at the offset provided,
  // does not mutate the underlying token stream read pointer.
  std::string get(unsigned int &);
};

} // namespace IfcParse

namespace IfcParse {

class IFC_PARSE_API IfcCharacterEncoder {
private:
  std::u32string str_;

public:
  IfcCharacterEncoder(const std::string &input);
  operator std::string();
};

} // namespace IfcParse

#endif
