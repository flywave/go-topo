#ifndef GO_TOPO_C_API_H
#define GO_TOPO_C_API_H

#ifdef __cplusplus
extern "C" {
#endif

enum { DIR_WEST, DIR_EAST, DIR_NORTH, DIR_SOUTH, DIR_UP, DIR_DOWN };
enum {
  TopoSolid,
  TopoShell,
  TopoFace,
  TopoEdge,
  TopoVertex,
  TopoWire,
  TopoCompound,
  TopoCompSolid,
  TopoShape,
};
enum { ORI_FORWARD, ORI_REVERSED, ORI_INTERNAL, ORI_EXTERNAL, ORI_UNKNOW };

typedef struct _topo_comp_solid_t topo_comp_solid_t;
typedef struct _topo_compound_t topo_compound_t;
typedef struct _topo_edge_t topo_edge_t;
typedef struct _topo_face_t topo_face_t;
typedef struct _topo_shape_t topo_shape_t;
typedef struct _topo_shell_t topo_shell_t;
typedef struct _topo_solid_t topo_solid_t;
typedef struct _topo_vertex_t topo_vertex_t;
typedef struct _topo_wire_t topo_wire_t;

#ifdef __cplusplus
}
#endif

#endif
