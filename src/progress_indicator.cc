
#include "progress_indicator.hh"
#include "string_conv.hh"
#include "version.hh"

#include <algorithm>

namespace flywave {

progress_indicator::progress_indicator() {
#if OCC_VERSION_HEX < OCC_VERSION_CHECK(7, 5, 0)
  this->SetScale(0., 100., 1.);
#endif
}

#if OCC_VERSION_HEX >= OCC_VERSION_CHECK(7, 5, 0)
void progress_indicator::Show(const Message_ProgressScope &scope,
                              const bool isForce) {}
#else
bool progress_indicator::Show(const bool /*force*/) { return true; }
#endif

bool progress_indicator::UserBreak() { return false; }

} // namespace flywave