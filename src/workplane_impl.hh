#ifndef GO_WORKPLANE_IMPL_H
#define GO_WORKPLANE_IMPL_H

#include "workplane.hh"

#ifdef __cplusplus
extern "C" {
#endif

struct _shape_objectt_t {   
    flywave::topo::shape_object obj;
};

struct _workplane_t {
  std::shared_ptr<flywave::topo::workplane> ptr;
};

#ifdef __cplusplus
}
#endif

#endif
