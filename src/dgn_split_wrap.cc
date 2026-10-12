// D120/D121: cgo wrappers for the DGN ACIS bridge (go-topo dgn_acis.go):
//   - toposplit_split_by_edges: split a face-like shape by edges lying on
//     it (BRepFeat_SplitShape);
//   - toposplit_trim_band: project a wire onto a face along dir, split
//     the face by the projected wire, and keep the piece containing the
//     keep point (BRepProj_Projection + BRepFeat_SplitShape).
// (Exact bounding box lives in topo_c_api.cc:
// topo_shape_bounding_box_optimal — BRepBndLib::AddOptimal.)
#include "topo_c_api.h"
#include "cgo_lock.hh"
#include "topo_impl.hh"

#include <BRepFeat_SplitShape.hxx>
#include <BRepProj_Projection.hxx>
#include <BRepBndLib.hxx>
#include <Bnd_Box.hxx>
#include <BRep_Tool.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Compound.hxx>
#include <BRep_Builder.hxx>
#include <gp_Dir.hxx>
#include <gp_Pnt.hxx>
#include <memory>

extern "C" topo_shape_t *toposplit_split_by_edges(topo_shape_t *S,
                                                  topo_shape_t **edges,
                                                  int count) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(
      flywave::topo::topo_glock());
  try {
    BRepFeat_SplitShape ss;
    ss.Init(S->shp->value());
    for (int i = 0; i < count; ++i) {
      const TopoDS_Shape &tool = edges[i]->shp->value();
      for (TopExp_Explorer ef(S->shp->value(), TopAbs_FACE); ef.More();
           ef.Next()) {
        const TopoDS_Face &fc = TopoDS::Face(ef.Current());
        for (TopExp_Explorer ee(tool, TopAbs_EDGE); ee.More(); ee.Next()) {
          try {
            ss.Add(TopoDS::Edge(ee.Current()), fc);
          } catch (...) {
          }
        }
      }
    }
    ss.Build();
    return new topo_shape_t{
        std::make_shared<flywave::topo::shape>(ss.Shape())};
  } catch (...) {
    return nullptr;
  }
}

extern "C" topo_shape_t *toposplit_trim_band(topo_shape_t *band,
                                             topo_shape_t *wire,
                                             topo_shape_t *keepShape,
                                             double dx, double dy,
                                             double dz) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(
      flywave::topo::topo_glock());
  try {
    const TopoDS_Shape &faceShape = band->shp->value();
    const TopoDS_Shape &splitWire = wire->shp->value();
    const TopoDS_Shape &keep = keepShape->shp->value();

    BRepProj_Projection proj(splitWire, faceShape, gp_Dir(dx, dy, dz));
    if (!proj.IsDone()) {
      return nullptr;
    }
    TopoDS_Shape projWire = proj.Shape();
    if (projWire.IsNull()) {
      return nullptr;
    }

    BRepFeat_SplitShape ss;
    ss.Init(faceShape);
    for (TopExp_Explorer pe(projWire, TopAbs_EDGE); pe.More(); pe.Next()) {
      for (TopExp_Explorer ff(faceShape, TopAbs_FACE); ff.More(); ff.Next()) {
        try {
          ss.Add(TopoDS::Edge(pe.Current()), TopoDS::Face(ff.Current()));
        } catch (...) {
        }
      }
    }
    ss.Build();

    TopoDS_Shape result = ss.Shape();
    BRep_Builder builder;
    TopoDS_Compound mc;
    builder.MakeCompound(mc);
    bool any = false;
    for (TopExp_Explorer rf(result, TopAbs_FACE); rf.More(); rf.Next()) {
      Bnd_Box box;
      BRepBndLib::Add(rf.Current(), box);
      double xmin, ymin, zmin, xmax, ymax, zmax;
      box.Get(xmin, ymin, zmin, xmax, ymax, zmax);
      TopExp_Explorer ve(keep, TopAbs_VERTEX);
      bool in = true;
      for (; ve.More(); ve.Next()) {
        gp_Pnt p = BRep_Tool::Pnt(TopoDS::Vertex(ve.Current()));
        if (p.X() < xmin - 1e-6 || p.X() > xmax + 1e-6 ||
            p.Y() < ymin - 1e-6 || p.Y() > ymax + 1e-6 ||
            p.Z() < zmin - 1e-6 || p.Z() > zmax + 1e-6) {
          in = false;
          break;
        }
      }
      if (in) {
        builder.Add(mc, rf.Current());
        any = true;
      }
    }
    if (!any) {
      return nullptr;
    }
    // if no piece was dropped, mc holds every resulting face anyway —
    // return the kept-piece compound uniformly.
    return new topo_shape_t{std::make_shared<flywave::topo::shape>(mc)};
  } catch (...) {
    return nullptr;
  }
}
