#pragma once

#include "tkernel_utils.hh"
#include <Message_ProgressIndicator.hxx>

namespace flywave {

class progress_indicator : public Message_ProgressIndicator {
public:
  progress_indicator();

  bool UserBreak() override;

#if OCC_VERSION_HEX >= OCC_VERSION_CHECK(7, 5, 0)
  void Show(const Message_ProgressScope &theScope, const bool isForce) override;
#else
  bool Show(const bool force) override;
#endif

private:
};

} // namespace flywave