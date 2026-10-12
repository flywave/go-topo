// D120: split a face-like shape by edges lying on it
// (BRepFeat_SplitShape). Used by the DGN ACIS bridge to trim extrusion
// bands along their real splitting curves.
#include "topo_c_api.h"
#include "cgo_lock.hh"
#include "topo_impl.hh"

#include <BRepFeat_SplitShape.hxx>
#include <BRepBndLib.hxx>
#include <Bnd_Box.hxx>
#include <BRepProj_Projection.hxx>
#include <BRep_Tool.hxx>
#include <TopoDS_Compound.hxx>
#include <BRep_Builder.hxx>
#include <gp_Dir.hxx>
#include <gp_Pnt.hxx>
#include <TopAbs_ShapeEnum.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS.hxx>
#include <memory>

extern "C" topo_shape_t *toposplit_split_by_edges(topo_shape_t *S, topo_shape_t **edges,
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

// D121: project a wire onto a face along dir, split the face by the
// projected wire (BRepFeat_SplitShape), and return the piece containing
// keepPoint. Returns null on any failure (caller falls back).
extern "C" topo_shape_t *toposplit_trim_band(topo_shape_t *band, topo_shape_t *wire,
                                  topo_shape_t *keepShape, double dx,
                                  double dy, double dz) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(
      flywave::topo::topo_glock());
  try {
    const TopoDS_Shape &faceShape = band->shp->value();
    const TopoDS_Shape &splitWire = wire->shp->value();
    const TopoDS_Shape &keep = keepShape->shp->value();

    // 1. project the splitting wire onto the band surface
    BRepProj_Projection proj(splitWire, faceShape, gp_Dir(dx, dy, dz));
    if (!proj.IsDone()) {
      return nullptr;
    }
    TopoDS_Shape projWire = proj.Shape();
    if (projWire.IsNull()) {
      return nullptr;
    }

    // 2. split the band by the projected wire
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

    // 3. keep the resulting piece(s) containing the keep point (the end
    //    loop center, i.e. the face's own boundary side)
    TopoDS_Shape result = ss.Shape();
    TopoDS_Compound mc;
    BRep_Builder builder;
    builder.MakeCompound(mc);
    bool any = false;
    bool outside = false;
    for (TopExp_Explorer rf(result, TopAbs_FACE); rf.More(); rf.Next()) {
      // keep-piece test: the piece whose vertices' bbox contains the
      // keepShape center is the wanted side; the other side is dropped.
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
      } else {
        outside = true;
      }
    }
    if (!any) {
      return nullptr;
    }
    if (!outside) {
      // nothing trimmed — return the whole band unchanged
      return new topo_shape_t{std::make_shared<flywave::topo::shape>(
          static_cast<const topo_shape_t &>(*band).shp->value())};
    }
    return new topo_shape_t{std::make_shared<flywave::topo::shape>(
        static_cast<const TopoDS_Shape &>(mc))};
  } catch (...) {
    return nullptr;
  }
}
