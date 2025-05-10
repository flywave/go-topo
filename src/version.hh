#pragma once

#include <Standard_Version.hxx>

#ifndef OCC_VERSION_CHECK
#define OCC_VERSION_CHECK(major, minor, patch)                                 \
  ((major << 16) | (minor << 8) | (patch))
#endif
