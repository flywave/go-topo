#pragma once

#include "ogg_handle.hh"
#include <NCollection_UtfString.hxx>
#include <TCollection_AsciiString.hxx>
#include <TCollection_ExtendedString.hxx>
#include <TCollection_HAsciiString.hxx>
#include <locale>
#include <string>

namespace flywave {

template <typename InputStringType, typename OutputStringType>
struct string_conv_t {};

template <typename OutputStringType, typename InputStringType>
OutputStringType string_conv(const InputStringType &str) {
  return string_conv_t<InputStringType, OutputStringType>::to(str);
}

template <typename StringType>
std::string to_std_string(const StringType &str) {
  return string_conv<std::string>(str);
}

template <typename StringType>
TCollection_AsciiString to_ogg_ascii_string(const StringType &str) {
  return string_conv<TCollection_AsciiString>(str);
}

template <typename StringType>
ogg_handle<TCollection_HAsciiString>
to_ogg_ascii_string_handle(const StringType &str) {
  return string_conv<ogg_handle<TCollection_HAsciiString>>(str);
}

template <typename StringType>
TCollection_ExtendedString to_ogg_ext_string(const StringType &str) {
  return string_conv<TCollection_ExtendedString>(str);
}

struct double_to_string_options {
  std::locale locale;
  int decimalCount = 6;
  bool removeTrailingZeroes = true;
  bool roundToZero = true;
  bool to_utf8 = true;
};

class double_to_string_operation {
public:
  double_to_string_operation(double value);
  double_to_string_operation &locale(const std::locale &l);
  double_to_string_operation &decimalCount(int c);
  double_to_string_operation &removeTrailingZeroes(bool on);
  double_to_string_operation &roundToZero(bool on);
  double_to_string_operation &to_utf8(bool on);
  operator std::string();
  std::string get() const;

private:
  double m_value;
  double_to_string_options m_opts;
};

std::string to_std_string(double value, const double_to_string_options &opts);
double_to_string_operation to_std_string(double value);

template <> struct string_conv_t<const char *, TCollection_ExtendedString> {
  static auto to(const char *str) {
    return TCollection_ExtendedString(str, true /*multi-byte*/);
  }
};

template <size_t N> struct string_conv_t<char[N], TCollection_ExtendedString> {
  static auto to(const char (&str)[N]) {
    return TCollection_ExtendedString(str, true /*multi-byte*/);
  }
};

template <>
struct string_conv_t<ogg_handle<TCollection_HAsciiString>, std::string> {
  static auto to(const ogg_handle<TCollection_HAsciiString> &str) {
    return string_conv<std::string>(str ? str->String()
                                        : TCollection_AsciiString());
  }
};

template <> struct string_conv_t<std::string, TCollection_AsciiString> {
  static auto to(const std::string &str) {
    return TCollection_AsciiString(str.c_str(), int(str.length()));
  }
};

template <>
struct string_conv_t<std::string, ogg_handle<TCollection_HAsciiString>> {
  static auto to(const std::string &str) {
    return make_ogg_handle<TCollection_HAsciiString>(str.c_str());
  }
};

template <> struct string_conv_t<std::string, TCollection_ExtendedString> {
  static auto to(const std::string &str) {
    return TCollection_ExtendedString(str.c_str(), true /*multi-byte*/);
  }
};

template <> struct string_conv_t<std::string, NCollection_Utf8String> {
  static auto to(const std::string &str) {
    return NCollection_Utf8String(str.c_str(), static_cast<int>(str.size()));
  }
};

template <> struct string_conv_t<TCollection_AsciiString, std::string> {
  static auto to(const TCollection_AsciiString &str) {
    return std::string(str.ToCString(), str.Length());
  }
};

template <> struct string_conv_t<TCollection_ExtendedString, std::string> {
  static auto to(const TCollection_ExtendedString &str) {
    std::string u8;
    u8.resize(str.LengthOfCString());
    char *u8Data = &u8[0];
    str.ToUTF8CString(u8Data);
    return u8;
  }
};

template <> struct string_conv_t<TCollection_ExtendedString, std::u16string> {
  static auto to(const TCollection_ExtendedString &str) {
    return std::u16string(str.ToExtString(), str.Length());
  }
};

} // namespace flywave
