#ifndef GO_SELECTOR_IMPL_H
#define GO_SELECTOR_IMPL_H

#include "selector.hh"

#ifdef __cplusplus
extern "C" {
#endif

struct _selector_t {
  flywave::topo::selector_ptr ptr;
};

#ifdef __cplusplus
}
#endif

#endif
