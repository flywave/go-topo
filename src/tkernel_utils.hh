
#pragma once

#include "ogg_handle.hh"

#include <Quantity_Color.hxx>
#include <Standard_Version.hxx>
#include <string>
#include <string_view>

#ifndef OCC_VERSION_CHECK
#define OCC_VERSION_CHECK(major, minor, patch)                                 \
  ((major << 16) | (minor << 8) | (patch))
#endif

#if OCC_VERSION_HEX >= OCC_VERSION_CHECK(7, 5, 0)
#include <Message_ProgressRange.hxx>
#else
class Message_ProgressIndicator;
#endif

namespace flywave {

class kernel_utils {
public:
  template <typename TransientType>
  static ogg_handle<TransientType> makeHandle(const TransientType *ptr) {
    return ptr;
  }

  using start_progress_indicator =
#if OCC_VERSION_HEX >= OCC_VERSION_CHECK(7, 5, 0)
      Message_ProgressRange;
#else
      const ogg_handle<Message_ProgressIndicator> &;
#endif
  static start_progress_indicator
  start(const ogg_handle<Message_ProgressIndicator> &progress);

  static std::string color_to_hex(const Quantity_Color &color);

  static bool color_from_hex(const std::string &strHex, Quantity_Color *color);

  static Quantity_TypeOfColor preferred_rgb_color_type();

  static Quantity_Color to_linear_rgb_color(const Quantity_Color &color);
};

} // namespace flywave