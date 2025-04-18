#pragma once

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iosfwd>
#include <optional>
#include <set>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "base.hh"
#include "math_utils.hh"

namespace flywave {
namespace dxf {

typedef int color_index_t; // DXF color index

typedef enum {
  eUnspecified = 0, // Unspecified (No units)
  eInches,
  eFeet,
  eMiles,
  eMillimeters,
  eCentimeters,
  eMeters,
  eKilometers,
  eMicroinches,
  eMils,
  eYards,
  eAngstroms,
  eNanometers,
  eMicrons,
  eDecimeters,
  eDekameters,
  eHectometers,
  eGigameters,
  eAstronomicalUnits,
  eLightYears,
  eParsecs
} dxf_units_type;

struct dxf_coords {
  double x;
  double y;
  double z;

  dxf_coords() = default;
  dxf_coords(double x, double y, double z = 0.) : x(x), y(y), z(z) {}

  // Add equality operator
  bool operator==(const dxf_coords &other) const {
    return math_utils::fuzzy_equal(x, other.x) &&
           math_utils::fuzzy_equal(y, other.y) &&
           math_utils::fuzzy_equal(z, other.z);
  }

  bool operator!=(const dxf_coords &other) const { return !(*this == other); }
};

struct dxf_scale {
  double x;
  double y;
  double z;
};

struct dxf_style {
  // Code: 2
  std::string name;
  // Code: 40
  double fixed_text_height = 0;
  // Code: 41
  double width_factor = 1.;
  // Code: 50
  // AutoCad documentation doesn't specify units, but "Group Codes in Numerical
  // Order" section states that codes 50-58 are in degrees
  double oblique_angle = 0.;
  // Code: 3
  std::string primary_font_file_name;
  // Code: 4
  std::string big_font_file_name;

  // TODO Code 70(standard flag values)
  // TODO Code 71(text generation flags)
  // TODO Code 42(last height used)
};

struct dxf_text {
  // Code: 39
  double thickness = 0.;
  // Code: 10, 20, 30
  dxf_coords first_alignment_point = {};
  // Code: 40
  double height = 0.;
  // Code: 1
  std::string str;
  // Code: 50
  // AutoCad documentation doesn't specify units, but "Group Codes in Numerical
  // Order" section states that codes 50-58 are in degrees
  double rotation_angle = 0.;
  // Code: 41
  // "This value is also adjusted when fit-type text is used"
  double relative_x_scale_factor_width = 1.;
  // Code: 51
  // AutoCad documentation doesn't specify units, but "Group Codes in Numerical
  // Order" section states that codes 50-58 are in degrees
  double oblique_angle = 0.;
  // Code: 7
  std::string style_name;

  // TODO Code 71(text generation flags)

  enum class horizontal_justification_type {
    Left = 0,
    Center = 1,
    Right = 2,
    Aligned = 3,
    Middle = 4,
    Fit = 5
  };
  // Code: 72
  horizontal_justification_type horizontal_justification =
      horizontal_justification_type::Left;
  // Code: 11, 21, 31
  dxf_coords second_alignment_point = {};
  // Code: 210, 220, 230
  dxf_coords extrusion_direction = {0., 0., 1.};

  enum class vertical_justification_type {
    Baseline = 0,
    Bottom = 1,
    Middle = 2,
    Top = 3
  };
  // Code: 73
  vertical_justification_type vertical_justification =
      vertical_justification_type::Baseline;
};

struct dxf_mtext {
  enum class attachment_point_type {
    TopLeft = 1,
    TopCenter,
    TopRight,
    MiddleLeft,
    MiddleCenter,
    MiddleRight,
    BottomLeft,
    BottomCenter,
    BottomRight
  };

  // Code: 10, 20, 30
  dxf_coords insertion_point = {};
  // Code: 40
  double height = 0.;
  // Code: 41
  double reference_rectangle_width = 0;
  // Code 71
  attachment_point_type attachment_point = attachment_point_type::TopLeft;

  // TODO Code 72(drawing direction)

  // Code: 1, 3
  std::string str;

  // TODO Code 7(text sytle name)

  // Code: 210, 220, 230
  dxf_coords extrusion_direction = {0., 0., 1.};

  // Code: 11, 21, 31
  dxf_coords x_axis_direction = {1., 0., 0.}; // WCS

  // NOTE AutoCad documentation states that codes 42, 43 are "read-only, ignored
  // if supplied"

  double rotation_angle = 0.; // radians(AutoCad documentation)

  // TODO Code 73(line spacing style)
  // TODO Code 44(line spacing factor)
  // TODO Code 90(background fill setting)
  // TODO Code 420-429(background color, if RGB)
  // TODO Code 430-439(background color, if name)
  // TODO Code 45(fill box scale)
  // TODO Code 63(background fill color)
  // TODO Code 441(transparency of background fill color)
  // TODO Codes for columns: 75, 76, 78, 79, 48, 49, 50

  enum class column_type { None = 0, Static, Dynamic };
  bool acad_has_column_info = false;
  column_type acad_column_info_type = column_type::None;
  bool acad_column_info_auto_height = false;
  int acad_column_info_count = 0;
  bool acad_column_info_flow_reversed = false;
  double acad_column_info_width = 0.;
  double acad_column_info_gutter_width = 0.;

  bool acad_has_defined_height = false;
  double acad_defined_height = 0.;
};

struct dxf_vertex {
  enum class bulge { StraightSegment = 0, SemiCircle = 1 };
  enum Flag {
    None = 0,
    extraVertex = 1,
    CurveFitTangent = 2,
    NotUsed = 4,
    SplineVertex = 8,
    SplineFrameControlPoint = 16,
    Polyline3dVertex = 32,
    Polygon3dVertex = 64,
    PolyfaceMeshVertex = 128
  };
  using Flags = unsigned;

  // Code: 10, 20, 30
  dxf_coords point = {};
  // Code: 40
  double starting_width = 0.;
  // Code: 41
  double ending_width = 0.;
  // Code: 42
  bulge bulge = bulge::StraightSegment;
  // Code: 70
  Flags flags = Flag::None;
  // Code: 50
  double curve_fit_tangent_direction = 0.;
  // Code: 71
  int polyface_mesh_vertex1 = 0;
  // Code: 72
  int polyface_mesh_vertex2 = 0;
  // Code: 73
  int polyface_mesh_vertex3 = 0;
  // Code: 74
  int polyface_mesh_vertex4 = 0;
  // Code: 91
  // int identifier = 0;
};

struct dxf_polyline {
  enum Flag {
    None = 0,
    Closed = 1,
    CurveFit = 2,
    SplineFit = 4,
    Polyline3d = 8,
    PolygonMesh3d = 16,
    PolygonMeshClosedNDir = 32,
    PolyfaceMesh = 64,
    ContinuousLinetypePattern = 128
  };
  using Flags = unsigned;

  enum Type {
    NoSmoothSurfaceFitted = 0,
    QuadraticBSplineSurface = 5,
    CubicBSplineSurface = 6,
    BezierSurface = 8
  };

  // Code: 39
  double thickness = 0.;
  // Code: 70
  Flags flags = Flag::None;
  // Code: 40
  double default_start_width = 0.;
  // Code: 41
  double default_end_width = 0.;
  // Code: 71(number of vertices in the mesh)
  int polygon_mesh_m_vertex_count = 0;
  // Code: 72(number of faces in the mesh)
  int polygon_mesh_n_vertex_count = 0;
  // Code: 73
  double smooth_surface_m_density = 0.;
  // Code: 74
  double smooth_surface_n_density = 0.;
  // Code: 75
  Type type = Type::NoSmoothSurfaceFitted;
  // Code: 210, 220, 230
  dxf_coords extrusion_direction = {0., 0., 1.};

  std::vector<dxf_vertex> vertices;
};

struct dxf_insert {
  // Code: 2
  std::string block_name;
  // Code: 10, 20, 30
  dxf_coords insert_point = {}; // OCS
  // Code: 41, 42, 43
  dxf_scale scale_factor = {1., 1., 1.};
  // Code: 50
  double rotation_angle = 0.;
  // Code: 70
  int column_count = 1;
  // Code: 71
  int row_count = 1;
  // Code: 44
  double column_spacing = 0.;
  // Code: 45
  double row_spacing = 0.;
  // Code: 210, 220, 230
  dxf_coords extrusion_direction = {0., 0., 1.};
};

struct dxf_quad_base {
  // Code: 10, 20, 30
  dxf_coords corner1;
  // Code: 11, 21, 31
  dxf_coords corner2;
  // Code: 12, 22, 32
  dxf_coords corner3;
  // Code: 13, 23, 33
  dxf_coords corner4;
  bool has_corner4 = false;
};

struct dxf_3d_face : public dxf_quad_base {
  enum Flag {
    None = 0,
    InvisibleEdge1 = 1,
    InvisibleEdge2 = 2,
    InvisibleEdge3 = 4,
    InvisibleEdge4 = 8
  };
  using Flags = unsigned;

  // Code: 70
  Flags flags = Flag::None;
};

struct dxf_solid : public dxf_quad_base {
  // Code: 39
  double thickness = 0.;
  // Code: 210, 220, 230
  dxf_coords extrusion_direction = {0., 0., 1.};
};

struct dxf_spline {
  enum Flag {
    None = 0,
    Closed = 1,
    Periodic = 2,
    Rational = 4,
    Planar = 8,
    Linear = 16 // Planar bit is also set
  };
  using Flags = unsigned;

  // Code: 210, 220, 230
  dxf_coords normal_vector = {0., 0., 1.};
  // Code: 70
  Flags flags = Flag::None;
  // Code: 71
  int degree = 0;

  // Code: 42
  double knot_tolerance = 0.0000001;
  // Code: 43
  double control_point_tolerance = 0.0000001;
  // Code: 44
  double fit_tolerance = 0.0000000001;

  // Code: 12, 22, 32
  std::vector<dxf_coords> start_tangents;
  // Code: 13, 23, 33
  std::vector<dxf_coords> end_tangents;
  // Code: 40
  std::vector<double> knots;
  // Code: 41
  std::vector<double> weights;
  // Code: 10, 20, 30
  std::vector<dxf_coords> control_points;
  // Code: 11, 21, 31
  std::vector<dxf_coords> fit_points;
};

typedef enum {
  RUnknown,
  ROlder,
  R10,
  R11_12,
  R13,
  R14,
  R2000,
  R2004,
  R2007,
  R2010,
  R2013,
  R2018,
  RNewer,
} dxf_version_t;

struct point3d {
  double x;
  double y;
  double z;
};

struct spline_data_out {
  point3d norm;
  int degree;
  int knots;
  int control_points;
  int fit_points;
  int flag;
  point3d starttan;
  point3d endtan;
  std::vector<double> knot;
  std::vector<double> weight;
  std::vector<point3d> control;
  std::vector<point3d> fit;
};

struct lw_poly_data_out {
  double nvert;
  int flag;
  double width;
  double elev;
  double thick;
  std::vector<point3d> verts;
  std::vector<double> start_width;
  std::vector<double> end_width;
  std::vector<double> bulge;
  point3d extr;
};

class dxf_write {
private:
  std::ofstream _ofs;
  bool _fail;
  std::ostringstream _ss_block;
  std::ostringstream _ss_blk_record;
  std::ostringstream _ss_entity;
  std::ostringstream _ss_layer;

protected:
  void put_line(const vector3d &s, const vector3d &e,
                std::ostringstream &outStream, const std::string &handle,
                const std::string &ownerHandle);
  void put_text(const char *text, const vector3d &location1,
                const vector3d &location2, const double height,
                const int horizJust, std::ostringstream &outStream,
                const std::string &handle, const std::string &ownerHandle);
  void put_arrow(const vector3d &arrowPos, const vector3d &barb1Pos,
                 const vector3d &barb2Pos, std::ostringstream &outStream,
                 const std::string &handle, const std::string &ownerHandle);

  std::string get_plate_file(const std::string &fileSpec);
  void set_data_dir(const std::string &s) { _data_dir = s; }
  std::string get_handle();
  std::string get_entity_handle();
  std::string get_layer_handle();
  std::string get_block_handle();
  std::string get_blk_record_handle();

  std::ostringstream &get_entity_stream() { return _ss_entity; }

  std::string _option_source;
  int _version;
  int _handle;
  int _entity_handle;
  int _layer_handle;
  int _block_handle;
  int _blk_record_handle;
  bool _poly_override;

  std::string _save_model_space_handle;
  std::string _save_paper_space_handle;
  std::string _save_block_record_table_handle;
  std::string _save_blk_record_handle;
  std::string _current_block;
  std::string _data_dir;
  std::string _layer_name;
  std::vector<std::string> _layer_list;
  std::vector<std::string> _block_list;
  std::vector<std::string> _blk_record_list;

public:
  dxf_write(const char *filepath);
  ~dxf_write();

  void init();
  void end_run();

  bool failed() { return _fail; }

  std::string get_layer_name() { return _layer_name; }
  void set_layer_name(std::string s);
  void set_version(int v) { _version = v; }
  void set_poly_override(bool b) { _poly_override = b; }
  void add_block_name(std::string s, std::string blkRecordHandle);

  void write_line(const double *s, const double *e);
  void write_point(const double *);
  void write_arc(const double *s, const double *e, const double *c, bool dir);
  void write_ellipse(const double *c, double major_radius, double minor_radius,
                     double rotation, double start_angle, double end_angle,
                     bool endIsCW);
  void write_circle(const double *c, double radius);
  void write_spline(const spline_data_out &sd);
  void write_lw_polyline(const lw_poly_data_out &pd);
  void write_polyline(const lw_poly_data_out &pd);
  void write_vertex(double x, double y, double z);
  void write_text(const char *text, const double *location1,
                  const double *location2, const double height,
                  const int horizJust);
  void write_linear_dim(const double *textMidPoint, const double *lineDefPoint,
                        const double *extLine1, const double *extLine2,
                        const char *dimText, int type);
  void write_linear_dim_block(const double *textMidPoint,
                              const double *lineDefPoint,
                              const double *extLine1, const double *extLine2,
                              const char *dimText, int type);
  void write_angular_dim(const double *textMidPoint, const double *lineDefPoint,
                         const double *startExt1, const double *endExt1,
                         const double *startExt2, const double *endExt2,
                         const char *dimText);
  void write_angular_dim_block(const double *textMidPoint,
                               const double *lineDefPoint,
                               const double *startExt1, const double *endExt1,
                               const double *startExt2, const double *endExt2,
                               const char *dimText);
  void write_radial_dim(const double *centerPoint, const double *textMidPoint,
                        const double *arcPoint, const char *dimText);
  void write_radial_dim_block(const double *centerPoint,
                              const double *textMidPoint,
                              const double *arcPoint, const char *dimText);
  void write_diametric_dim(const double *textMidPoint, const double *arcPoint1,
                           const double *arcPoint2, const char *dimText);
  void write_diametric_dim_block(const double *textMidPoint,
                                 const double *arcPoint1,
                                 const double *arcPoint2, const char *dimText);

  void write_dim_block_preamble();
  void write_block_trailer();

  void write_header_section();
  void write_tables_section();
  void write_blocks_section();
  void write_entities_section();
  void write_objects_section();
  void write_classes_section();

  void make_layer_table();
  void make_block_record_table_head();
  void make_block_record_table_body();
  void make_block_section_head();
};

namespace dxf_internal {

enum class string_to_error_mode { Throw = 0x1, ReturnErrorValue = 0x2 };

double
string_to_double(const std::string &line,
                 string_to_error_mode errorMode = string_to_error_mode::Throw);

int string_to_int(const std::string &line,
                  string_to_error_mode errorMode = string_to_error_mode::Throw);

unsigned string_to_unsigned(
    const std::string &line,
    string_to_error_mode errorMode = string_to_error_mode::Throw);

} // namespace dxf_internal

class dxf_read {
private:
  std::ifstream _ifs;

  bool _fail = false;
  std::string _str;
  std::string _unused_line;
  dxf_units_type _units = eMillimeters;
  bool _measurement_inch = false;
  std::string _layer_name{"0"};
  std::string _section_name;
  std::string _block_name;
  bool _ignore_errors = true;

  std::streamsize _gcount = 0;
  int _line_nb = 0;

  std::unordered_map<std::string, color_index_t> _layer_ColorIndex_map;
  const color_index_t ColorBylayer = 256;

  std::unordered_map<std::string, dxf_style> _map_style;

  bool read_ins_units();
  bool read_measurement();
  bool read_acad_ver();
  bool read_dwg_code_page();

  bool read_layer();
  bool read_style();
  bool read_line();
  bool read_mtext();
  bool read_text();
  bool read_arc();
  bool read_circle();
  bool read_ellipse();
  bool read_point();
  bool read_spline();
  bool read_lw_polyline();
  bool read_polyline();
  bool read_vertex(dxf_vertex *vertex);
  bool read_3d_face();
  bool read_solid();
  bool read_section();
  bool read_table();
  bool read_end_sec();

  void on_read_arc(double start_angle, double end_angle, double radius,
                   const dxf_coords &c, double z_extrusion_dir, bool hidden);
  void on_read_circle(const dxf_coords &c, double radius, bool hidden);
  void on_read_ellipse(const dxf_coords &c, const dxf_coords &m, double ratio,
                       double start_angle, double end_angle);
  bool read_insert();
  bool read_dimension();
  bool read_block_info();

  bool resolve_encoding();

  template <unsigned XCode = 10, unsigned YCode = 20, unsigned ZCode = 30>
  void handle_coord_code(int n, dxf_coords *coords) {
    switch (n) {
    case XCode:
      coords->x = mm(dxf_internal::string_to_double(_str));
      break;
    case YCode:
      coords->y = mm(dxf_internal::string_to_double(_str));
      break;
    case ZCode:
      coords->z = mm(dxf_internal::string_to_double(_str));
      break;
    }
  }

  template <unsigned XCode, unsigned YCode, unsigned ZCode>
  void handle_vector_coord_code(int n, std::vector<dxf_coords> *ptrVecCoords) {
    if (n == XCode || ptrVecCoords->empty())
      ptrVecCoords->push_back({});

    handle_coord_code<XCode, YCode, ZCode>(n, &ptrVecCoords->back());
  }

  void handle_common_group_code(int n);

  void put_line(const std::string &value);
  void resolve_color_index();

  void report_error_read_integer(const char *context);

protected:
  color_index_t _color_index = 0;
  dxf_version_t _version = RUnknown;

  std::streamsize gcount() const;
  virtual void get_line();
  virtual void report_error(const std::string & /*msg*/) {}

  virtual bool set_source_encoding(const std::string & /*codepage*/) {
    return true;
  }
  virtual std::string to_utf8(const std::string &strSource) {
    return strSource;
  }

private:
  std::string _code_page;

public:
  dxf_read(const char *filepath);
  virtual ~dxf_read();

  bool ignore_errors() const { return _ignore_errors; }
  bool failed() const { return _fail; }

  double mm(double value) const;

  const dxf_style *find_style(const std::string &name) const;

  void do_read(bool ignore_errors = false);

  virtual void on_read_line(const dxf_coords &s, const dxf_coords &e,
                            bool hidden) = 0;

  virtual void on_read_polyline(const dxf_polyline &) = 0;

  virtual void on_read_3d_face(const dxf_3d_face &) = 0;

  virtual void on_read_point(const dxf_coords &s) = 0;

  virtual void on_read_text(const dxf_text &) = 0;

  virtual void on_read_mtext(const dxf_mtext &) = 0;

  virtual void on_read_arc(const dxf_coords &s, const dxf_coords &e,
                           const dxf_coords &c, bool dir, bool hidden) = 0;

  virtual void on_read_circle(const dxf_coords &s, const dxf_coords &c,
                              bool dir, bool hidden) = 0;

  virtual void on_read_ellipse(const dxf_coords &c, double major_radius,
                               double minor_radius, double rotation,
                               double start_angle, double end_angle,
                               bool dir) = 0;

  virtual void on_read_spline(const dxf_spline &spline) = 0;

  virtual void on_read_insert(const dxf_insert &ins) = 0;

  virtual void on_read_solid(const dxf_solid &solid) = 0;

  virtual void on_read_dimension(const dxf_coords &s, const dxf_coords &e,
                                 const dxf_coords &point, double rotation) = 0;

  virtual void add_graphics() const = 0;

  std::string layer_name() const;
};

} // namespace dxf
} // namespace flywave
