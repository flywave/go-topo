// ShapeOperations.h
#pragma once

#include <BRepBndLib.hxx>
#include <BRepMesh_IncrementalMesh.hxx>
#include <Bnd_Box.hxx>
#include <TopoDS_Shape.hxx>
#include <cmath>
#include <memory>

#include "vector.hh"

namespace flywave {
namespace topo {

class topo_bbox {
private:
  Bnd_Box wrapped;
  double xmin, xmax, ymin, ymax, zmin, zmax;
  double xlen, ylen, zlen;
  topo_vector center;
  double DiagonalLength;

  void updateProperties() {
    wrapped.Get(xmin, ymin, zmin, xmax, ymax, zmax);
    xlen = xmax - xmin;
    ylen = ymax - ymin;
    zlen = zmax - zmin;
    center = topo_vector((xmax + xmin) / 2.0, (ymax + ymin) / 2.0,
                         (zmax + zmin) / 2.0);
    DiagonalLength = std::sqrt(wrapped.SquareExtent());
  }

public:
  // Constructor from OCCT Bnd_Box
  topo_bbox(const Bnd_Box &bb) : wrapped(bb) { updateProperties(); }

  // Properties
  double XMin() const { return xmin; }
  double XMax() const { return xmax; }
  double XLength() const { return xlen; }

  double YMin() const { return ymin; }
  double YMax() const { return ymax; }
  double YLength() const { return ylen; }

  double ZMin() const { return zmin; }
  double ZMax() const { return zmax; }
  double ZLength() const { return zlen; }

  topo_vector Min() const { return topo_vector(xmin, ymin, zmin); }
  topo_vector Max() const { return topo_vector(xmax, ymax, zmax); }

  topo_vector Center() const { return center; }
  double GetDiagonalLength() const { return DiagonalLength; }

  // Bounding box operations
  topo_bbox add(const topo_vector &obj, double tol = 1e-6) const {
    Bnd_Box tmp;
    tmp.SetGap(tol);
    tmp.Add(wrapped);
    tmp.Update(obj.x(), obj.y(), obj.z());
    return topo_bbox(tmp);
  }

  topo_bbox add(const topo_bbox &other, double tol = 1e-6) const {
    Bnd_Box tmp;
    tmp.SetGap(tol);
    tmp.Add(wrapped);
    tmp.Add(other.wrapped);
    return topo_bbox(tmp);
  }

  topo_bbox enlarge(double tol) const {
    Bnd_Box tmp(wrapped);
    tmp.SetGap(wrapped.GetGap());
    tmp.Enlarge(tol);
    return topo_bbox(tmp);
  }

  // 2D comparison
  static std::shared_ptr<topo_bbox> FindOutsideBox2D(const topo_bbox &bb1,
                                                     const topo_bbox &bb2) {
    if (bb1.xmin < bb2.xmin && bb1.xmax > bb2.xmax && bb1.ymin < bb2.ymin &&
        bb1.ymax > bb2.ymax) {
      return std::make_shared<topo_bbox>(bb1);
    }

    if (bb2.xmin < bb1.xmin && bb2.xmax > bb1.xmax && bb2.ymin < bb1.ymin &&
        bb2.ymax > bb1.ymax) {
      return std::make_shared<topo_bbox>(bb2);
    }

    return nullptr;
  }

  // Factory method from shape
  static topo_bbox FromTopoDS(const TopoDS_Shape &shape, double tol = 1e-6,
                              bool optimal = true) {
    Bnd_Box bbox;
    bbox.SetGap(tol);

    if (optimal) {
      BRepBndLib::AddOptimal(shape, bbox);
    } else {
      BRepMesh_IncrementalMesh mesh(shape, tol, true);
      mesh.Perform();
      BRepBndLib::Add(shape, bbox, true);
    }

    return topo_bbox(bbox);
  }

  // Containment check
  bool isInside(const topo_bbox &other) const {
    return (other.xmin > xmin && other.ymin > ymin && other.zmin > zmin &&
            other.xmax < xmax && other.ymax < ymax && other.zmax < zmax);
  }

  // Access to wrapped OCCT object
  const Bnd_Box &GetWrapped() const { return wrapped; }
};
} // namespace topo
} // namespace flywave
