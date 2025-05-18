#ifndef GO_TOPO_IMPL_H
#define GO_TOPO_IMPL_H

#include "bbox.hh"
#include "comp_solid.hh"
#include "compound.hh"
#include "edge.hh"
#include "face.hh"
#include "matrix.hh"
#include "shell.hh"
#include "solid.hh"
#include "topo_c_api.h"
#include "vector.hh"
#include "vertex.hh"
#include "wire.hh"

#include <StlAPI_Writer.hxx>
#include <string>

#ifdef __cplusplus
extern "C" {
#endif

struct _topo_shape_t {
  std::shared_ptr<flywave::topo::shape> shp;
};

struct _topo_location_t {
  flywave::topo::topo_location loc;
};

struct _topo_vector_t {
  flywave::topo::topo_vector vec;
};

struct _topo_plane_t {
  flywave::topo::topo_plane plane;
};

struct _topo_matrix_t {
  flywave::topo::topo_matrix mat;
};

struct _topo_bbox_t {
  flywave::topo::topo_bbox bbox;
};

struct _topo_mesh_receiver_t {
  std::unique_ptr<flywave::topo::mesh_receiver> recv;
};

struct _topo_comp_solid_iterator_t {
  flywave::topo::comp_solid_iterator iter;
};

struct _topo_compound_iterator_t {
  flywave::topo::compound_iterator iter;
};

struct _topo_edge_iterator_t {
  flywave::topo::edge_iterator iter;
};

struct _topo_face_iterator_t {
  flywave::topo::face_iterator iter;
};

struct _topo_shell_iterator_t {
  flywave::topo::shell_iterator iter;
};

struct _topo_solid_iterator_t {
  flywave::topo::solid_iterator iter;
};

struct _topo_vertex_iterator_t {
  flywave::topo::vertex_iterator iter;
};

struct _topo_wire_iterator_t {
  flywave::topo::wire_iterator iter;
};

#ifdef __cplusplus
}
#endif

inline flywave::topo::comp_solid *cast_to_topo(const _topo_comp_solid_t &a) {
  return dynamic_cast<flywave::topo::comp_solid *>(a.shp->shp.get());
}

inline flywave::topo::compound *cast_to_topo(const _topo_compound_t &a) {
  return dynamic_cast<flywave::topo::compound *>(a.shp->shp.get());
}

inline flywave::topo::edge *cast_to_topo(const _topo_edge_t &a) {
  return dynamic_cast<flywave::topo::edge *>(a.shp->shp.get());
}

inline flywave::topo::face *cast_to_topo(const _topo_face_t &a) {
  return dynamic_cast<flywave::topo::face *>(a.shp->shp.get());
}

inline flywave::topo::shell *cast_to_topo(const _topo_shell_t &a) {
  return dynamic_cast<flywave::topo::shell *>(a.shp->shp.get());
}

inline flywave::topo::solid *cast_to_topo(const _topo_solid_t &a) {
  return dynamic_cast<flywave::topo::solid *>(a.shp->shp.get());
}

inline flywave::topo::vertex *cast_to_topo(const _topo_vertex_t &a) {
  return dynamic_cast<flywave::topo::vertex *>(a.shp->shp.get());
}

inline flywave::topo::wire *cast_to_topo(const _topo_wire_t &a) {
  return dynamic_cast<flywave::topo::wire *>(a.shp->shp.get());
}

#endif
