#ifndef __FLYWAVE_MESH_TOPO_OCC_SHAPE_HH__
#define __FLYWAVE_MESH_TOPO_OCC_SHAPE_HH__

#include "geometry_object.hh"
#include "location.hh"
#include "mesh_receiver.hh"
#include "orientation.hh"
#include "selector.hh"
#include "shape_geom_type.hh"

#include <BRepBuilderAPI_Copy.hxx>
#include <OSD_Timer.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS_Shape.hxx>

#include <Message_ProgressIndicator.hxx>
#include <Quantity_Color.hxx>
#include <Standard_DefineHandle.hxx>
#include <Standard_Macro.hxx>
#include <TopTools_IndexedMapOfShape.hxx>

#include <unordered_map>
#include <vector>

#include "bbox.hh"

namespace flywave {
namespace topo {

class compound;
class vertex;
class wire;
class edge;
class face;
class shell;
class solid;
class comp_solid;
class topo_matrix;

enum texture_mapping_rule {
  texture_cube,
  texture_normal,
  texture_normal_auto_scale
};

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

  bool is_solid() const;

  virtual geometry_object_type type() const override;

  topo_bbox bbox(double tolerance = 1e-12) const;

  virtual Bnd_Box bounding_box(double tolerance = 1e-12) const override;

  int hash_code() const;
  virtual bool equals(const geometry_object &) const override;

  bool is_same(const shape &) const;

  bool for_construction() const;

  explicit operator bool() const;

  void set_surface_colour(const Quantity_Color &c) { _surface_colour = c; }
  void set_curve_colour(const Quantity_Color &c) { _curve_colour = c; }
  void set_label(const char *name) { _label = std::string(name); }
  void set_u_origin(double u) { _u_origin = u; }
  void set_v_origin(double v) { _v_origin = v; }
  void set_u_repeat(double u) { _u_repeat = u; }
  void set_v_repeat(double v) { _v_repeat = v; }
  void set_scale_v(double u) { _scale_v = u; }
  void set_scale_u(double v) { _scale_u = v; }
  void set_auto_scale_size_on_u(double u) { _auto_scale_size_on_u = u; }
  void set_auto_scale_size_on_v(double v) { _auto_scale_size_on_v = v; }
  void set_txture_map_type(texture_mapping_rule t);
  void set_rotation_angle(double angle) { _rotation_angle = angle; }

  Quantity_Color surface_colour() const { return _surface_colour; }
  Quantity_Color curve_colour() const { return _curve_colour; }
  const char *label() const { return _label.c_str(); }
  double get_u_origin() const { return _u_origin; }
  double get_v_origin() const { return _v_origin; }
  double get_u_repeat() const { return _u_repeat; }
  double get_v_repeat() const { return _v_repeat; }
  double get_scale_v() const { return _scale_v; }
  double get_scale_u() const { return _scale_u; }
  double get_auto_scale_size_on_u() const { return _auto_scale_size_on_u; }
  double get_auto_scale_size_on_v() const { return _auto_scale_size_on_v; }
  texture_mapping_rule get_txture_map_type() const { return _txture_map_type; }
  double get_rotation_angle() const { return _rotation_angle; }

  bool surface_colour(double *colour) const;

  int transform(gp_Trsf mat);
  int transform(const topo_matrix &mat);

  int translate(gp_Vec delta);
  int rotate(double angle, gp_Pnt p1, gp_Pnt p2);
  int rotate(double angle, gp_Ax1 a);
  int rotate(gp_Quaternion R);
  int scale(gp_Pnt pnt, double scale);
  int mirror(gp_Pnt pnt, gp_Pnt nor);
  int mirror(gp_Pnt pnt, gp_Vec nor);
  int mirror(gp_Ax1 a);
  int mirror(gp_Ax2 a);

  gp_Pnt centre_of_mass() const;
  gp_Pnt center_of_bound_box() const;
  double compute_mass() const;
  double compute_area() const;
  double distance(const shape &o) const;
  std::vector<double> distances(const std::vector<shape> &others) const;

  shape transformed(gp_Trsf mat) const;
  shape transformed(const topo_matrix &mat) const;

  shape translated(gp_Vec delta) const;
  shape rotated(double angle, gp_Pnt p1, gp_Pnt p2) const;
  shape rotated(double angle, gp_Ax1 a) const;
  shape rotated(gp_Quaternion R) const;
  shape scaled(gp_Pnt pnt, double scale) const;
  shape mirrored(gp_Pnt pnt, gp_Pnt nor) const;
  shape mirrored(gp_Pnt pnt, gp_Vec nor) const;
  shape mirrored(gp_Ax1 a) const;
  shape mirrored(gp_Ax2 a) const;

  shape clean();

  boost::optional<compound> ancestors(const shape &shape,
                                      TopAbs_ShapeEnum kind) const;
  boost::optional<compound> siblings(const shape &shape, TopAbs_ShapeEnum kind,
                                     int level = 1) const;

  gp_Pln find_plane(double tolerance = 1e-6) const;

  TopoDS_Shape &value();
  const TopoDS_Shape &value() const;

  virtual operator TopoDS_Shape &();
  virtual operator const TopoDS_Shape &() const;

  topo_location location() const;

  bool location(double *loc) const;

  void set_location(const topo_location &loc);

  shape located(const topo_location &loc) const;

  int move(const topo_location &loc);

  int move(double x = 0, double y = 0, double z = 0, double rx = 0,
           double ry = 0, double rz = 0);

  int move(const gp_Vec &vec);

  shape moved(const topo_location &loc) const;

  shape moved(std::initializer_list<topo_location> locs) const;

  shape moved(const std::vector<topo_location> &locs) const;

  shape moved(double x = 0, double y = 0, double z = 0, double rx = 0,
              double ry = 0, double rz = 0) const;

  shape moved(const gp_Vec &vec) const;

  shape moved(std::initializer_list<gp_Vec> vecs) const;

  shape moved(const std::vector<gp_Vec> &vecs) const;

  orientation get_orientation() const;

  void set_orientation(orientation ori);

  shape oriented(orientation ori) const;

  bool fix_shape();

  template <typename TShape> boost::optional<TShape> cast() const;

  boost::optional<shape> auto_cast() const;

  TopAbs_ShapeEnum shape_type() const;
  shape_geom_type geom_type() const;

  virtual int write_triangulation(mesh_receiver &mesh, double tolerance,
                                  double deflection, double angle,
                                  bool uv_coords);

  virtual int mesh(mesh_receiver &mesh, double precision = 1.0e-06,
                   double deflection = 0.1, double angle = 0.5,
                   bool uv_coords = false) {
    return write_triangulation(mesh, precision, deflection, angle, uv_coords);
  }

  virtual shape copy(bool deep = true) const;

  inline bool operator==(const shape &s) const { return this->equals(s); }
  inline bool operator!=(const shape &s) const { return !(*this == s); }

  bool operator<(const shape &other) const {
    return this->hash_code() < other.hash_code();
  }

  shape(TopoDS_Shape shp, bool forConstruction = false);
  shape(const shape &s, TopoDS_Shape shp);

  bool export_step(const std::string &fileName, bool write_pcurves = true,
                   int precision_mode = 0) const;
  bool export_brep(const std::string &fileName) const;

  static boost::optional<shape> import_from_brep(const std::string &fileName);

  static gp_Pnt combined_center(const std::vector<shape> &shapes);
  static gp_Pnt
  combined_center_of_bounding_box(const std::vector<shape> &shapes);

  boost::optional<shape> to_splines(int degree = 3, double tolerance = 1e-3,
                                    bool nurbs = false) const;
  boost::optional<shape> to_nurbs() const;

  std::vector<shape> children() const;
  std::vector<shape> get_shapes(TopAbs_ShapeEnum kind = TopAbs_SHAPE) const;

  virtual std::vector<vertex> vertices() const;
  virtual std::vector<edge> edges() const;
  virtual std::vector<compound> compounds() const;
  virtual std::vector<wire> wires() const;
  virtual std::vector<face> faces() const;
  virtual std::vector<shell> shells() const;
  virtual std::vector<solid> solids() const;
  virtual std::vector<comp_solid> comp_solids() const;

  void set_for_construction(bool for_construction) const;

  virtual int num_vertices() const { return num_entities(TopAbs_VERTEX); }
  virtual int num_edges() const { return num_entities(TopAbs_EDGE); }
  virtual int num_wires() const { return num_entities(TopAbs_WIRE); }
  virtual int num_faces() const { return num_entities(TopAbs_FACE); }
  virtual int num_shells() const { return num_entities(TopAbs_SHELL); }
  virtual int num_solids() const { return num_entities(TopAbs_SOLID); }
  virtual int num_compounds() const { return num_entities(TopAbs_COMPOUND); }
  virtual int num_comp_solids() const { return num_entities(TopAbs_COMPSOLID); }

  std::string to_string(double tolerance = 1e-3,
                        double angularTolerance = 0.1) const;

  static shape filter(const selector_ptr &sel,
                      const std::vector<shape> &shapes);

  inline shape vertices(const selector_ptr &sel) const {
    return shape::filter(sel, get_shapes(TopAbs_VERTEX));
  }

  inline shape edges(const selector_ptr &sel) const {
    return shape::filter(sel, get_shapes(TopAbs_EDGE));
  }

  inline shape wires(const selector_ptr &sel) const {
    return shape::filter(sel, get_shapes(TopAbs_WIRE));
  }

  inline shape faces(const selector_ptr &sel) const {
    return shape::filter(sel, get_shapes(TopAbs_FACE));
  }

  inline shape shells(const selector_ptr &sel) const {
    return shape::filter(sel, get_shapes(TopAbs_SHELL));
  }

  inline shape solids(const selector_ptr &sel) const {
    return shape::filter(sel, get_shapes(TopAbs_SOLID));
  }

  inline shape compounds(const selector_ptr &sel) const {
    return shape::filter(sel, get_shapes(TopAbs_COMPOUND));
  }

  inline shape comp_solids(const selector_ptr &sel) const {
    return shape::filter(sel, get_shapes(TopAbs_COMPSOLID));
  }

protected:
  template <typename OpType>
  shape bool_op(const std::vector<shape> &args, const std::vector<shape> &tools,
                OpType &op, bool parallel = true) const;
  void prepare_box_texture_coordinates(const TopoDS_Shape &aShape);
  void get_box_texture_coordinate(const gp_Pnt &p, const gp_Dir &N1,
                                  gp_Vec2d &theCoord_p);

  std::unordered_map<shape, std::vector<shape>>
  get_entities_from(TopAbs_ShapeEnum childType,
                    TopAbs_ShapeEnum parentType) const;

  template <typename T>
  std::vector<T> extract_entities(TopAbs_ShapeEnum type) const {
    std::vector<T> entities;
    for (TopExp_Explorer exp(_shape, type); exp.More(); exp.Next()) {
      if (!exp.Current().IsNull())
        entities.push_back(T(exp.Current()));
    }
    return entities;
  }

  int num_entities(TopAbs_ShapeEnum type) const;

  void clear_maps();
  void build_maps();
  int transform_impl(gp_Trsf &trans);

  friend class cad_reader;
  std::string _label;
  Quantity_Color _surface_colour;
  Quantity_Color _curve_colour;

  mutable bool _for_construction;

  TopoDS_Shape _shape;

  TopTools_IndexedMapOfShape _vmap, _emap, _fmap;

  Standard_Real _u_origin;
  Standard_Real _v_origin;
  Standard_Real _u_repeat;
  Standard_Real _v_repeat;
  Standard_Real _scale_u;
  Standard_Real _scale_v;
  Standard_Real _auto_scale_size_on_u;
  Standard_Real _auto_scale_size_on_v;
  Standard_Real _rotation_angle;
  texture_mapping_rule _txture_map_type;
  Standard_Real _bnd_box_sz;
  Standard_Real _Xmin, _Ymin, _Zmin, _Xmax, _Ymax, _Zmax;
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
