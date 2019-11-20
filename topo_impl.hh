#ifndef GO_TOPO_IMPL_H
#define GO_TOPO_IMPL_H

#include "comp_solid.hh"
#include "compound.hh"
#include "edge.hh"
#include "face.hh"
#include "shell.hh"
#include "solid.hh"
#include "vertex.hh"
#include "wire.hh"

#ifdef __cplusplus
extern "C" {
#endif

struct _topo_comp_solid_t {
  std::shared_ptr<flywave::topo::comp_solid> shp;
};

struct _topo_compound_t {
  std::shared_ptr<flywave::topo::compound> shp;
};

struct _topo_edge_t {
  std::shared_ptr<flywave::topo::edge> shp;
};

struct _topo_face_t {
  std::shared_ptr<flywave::topo::face> shp;
};

struct _topo_shape_t {
  std::shared_ptr<flywave::topo::shape> shp;
};

struct _topo_shell_t {
  std::shared_ptr<flywave::topo::shell> shp;
};

struct _topo_solid_t {
  std::shared_ptr<flywave::topo::solid> shp;
};

struct _topo_vertex_t {
  std::shared_ptr<flywave::topo::vertex> shp;
};

struct _topo_wire_t {
  std::shared_ptr<flywave::topo::wire> shp;
};

#ifdef __cplusplus
}
#endif

#endif
