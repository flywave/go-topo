#ifndef __FLYWAVE_MESH_TOPO_OCC_SHAPE_HH__
#define __FLYWAVE_MESH_TOPO_OCC_SHAPE_HH__

#include "geometry_object.hh"
#include "location.hh"
#include "mesh_receiver.hh"
#include "orientation.hh"

#include <BRepBuilderAPI_Copy.hxx>
#include <OSD_Timer.hxx>
#include <TopoDS_Shape.hxx>

#include <Message_ProgressIndicator.hxx>
#include <Quantity_Color.hxx>
#include <Standard_DefineHandle.hxx>
#include <Standard_Macro.hxx>
#include <TopTools_IndexedMapOfShape.hxx>

#include <vector>

namespace flywave {
namespace topo {

class shape : public geometry_object {
public:
  shape();
  virtual ~shape() = default;
  shape(const shape &) = default;
  shape &operator=(const shape &) = default;

  shape(shape &&) noexcept;
  shape &operator=(shape &&) noexcept;

  static boost::optional<shape> make_shape(TopoDS_Shape shp);

  virtual bool is_null() const override;
  virtual bool is_valid() const override;

  virtual geometry_object_type type() const override;

  virtual Bnd_Box bounding_box(double tolerance = 1e-12) const override;

  int hash_code() const;
  virtual bool equals(const geometry_object &) const override;

  explicit operator bool() const;

  void set_surface_colour(const Quantity_Color &c) { _surface_colour = c; }
  void set_curve_colour(const Quantity_Color &c) { _curve_colour = c; }
  void set_label(const char *name) { _label = std::string(name); }

  Quantity_Color surface_colour() const { return _surface_colour; }
  Quantity_Color curve_colour() const { return _curve_colour; }
  const char *label() const { return _label.c_str(); }

  bool surface_colour(double *colour) const;

  int transform(gp_Trsf mat);

  int translate(gp_Vec delta);
  int rotate(double angle, gp_Pnt p1, gp_Pnt p2);
  int rotate(double angle, gp_Ax1 a);
  int rotate(gp_Quaternion R);
  int scale(gp_Pnt pnt, double scale);
  int mirror(gp_Pnt pnt, gp_Pnt nor);
  int mirror(gp_Ax1 a);
  int mirror(gp_Ax2 a);

  shape transformed(gp_Trsf mat) const;

  shape translated(gp_Vec delta) const;
  shape rotated(double angle, gp_Pnt p1, gp_Pnt p2) const;
  shape rotated(double angle, gp_Ax1 a) const;
  shape rotated(gp_Quaternion R) const;
  shape scaled(gp_Pnt pnt, double scale) const;
  shape mirrored(gp_Pnt pnt, gp_Pnt nor) const;
  shape mirrored(gp_Ax1 a) const;
  shape mirrored(gp_Ax2 a) const;

  gp_Pln find_plane(double tolerance = 1e-6);

  TopoDS_Shape &value();
  const TopoDS_Shape &value() const;

  virtual operator TopoDS_Shape &();
  virtual operator const TopoDS_Shape &() const;

  topo_location location() const;

  bool location(double *loc) const;

  void set_location(const topo_location &loc);

  orientation get_orientation() const;

  void set_orientation(orientation ori);

  shape oriented(orientation ori) const;

  bool fix_shape();

  template <typename TShape> boost::optional<TShape> cast() const;

  boost::optional<shape> auto_cast() const;

  std::string shape_type() const;

  virtual int write_triangulation(mesh_receiver &mesh, double tolerance,
                                  double deflection, double angle);

  virtual int mesh(mesh_receiver &mesh, double precision = 1.0e-06,
                   double deflection = 0.1, double angle = 0.5) {
    return write_triangulation(mesh, precision, deflection, angle);
  }

  virtual shape copy(bool deep = true) const;

  inline bool operator==(const shape &s) const { return this->equals(s); }
  inline bool operator!=(const shape &s) const { return !(*this == s); }

  shape(TopoDS_Shape shp) : _shape(shp) {}

protected:
  void clear_maps();
  void build_maps();
  int transform_impl(gp_Trsf &trans);

  friend class cad_reader;
  std::string _label;
  Quantity_Color _surface_colour;
  Quantity_Color _curve_colour;

  TopoDS_Shape _shape;

  TopTools_IndexedMapOfShape _vmap, _emap, _fmap;
};
} // namespace topo
} // namespace flywave

namespace std {

template <> struct hash<::flywave::topo::shape> {
  size_t operator()(const ::flywave::topo::shape &v) const {
    return v.hash_code();
  }
};
} // namespace std
#endif // __FLYWAVE_MESH_TOPO_OCC_SHAPE_HH__
