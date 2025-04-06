#ifndef GO_SKETCH_IMPL_H
#define GO_SKETCH_IMPL_H

#include "sketch.hh"

#ifdef __cplusplus
extern "C" {
#endif

struct _sketch_val_t {
  flywave::topo::sketch_val val;
};

struct _sketch_t {
  std::shared_ptr<flywave::topo::sketch> ptr;
};

struct _sketch_constraint_value_t {
  flywave::topo::sketch_constraint_value val;
};

#ifdef __cplusplus
}
#endif

#endif
