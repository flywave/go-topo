#pragma once

#include <Geom_BSplineCurve.hxx>
#include <Resource_FormatType.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Shape.hxx>

#include <string>
#include <unordered_map>
#include <vector>

#include "dxf.hh"
#include "ogg_handle.hh"

namespace flywave {
namespace dxf {

class dxf_shape_reader : public dxf_read {
public:
  struct shape_entity {
    color_index_t color = 0;
    TopoDS_Shape shape;
  };
  struct parameters {
    double scaling = 1.;
  };
  struct text_entity {
    std::string text;
    gp_Pnt point;
    gp_Vec normal;
    gp_Vec x_axis_dir;
  };

private:
  std::set<std::string> _layer_names;
  std::unordered_map<std::string, std::vector<dxf_shape_reader::shape_entity>>
      _layers;
  std::unordered_map<std::string, std::vector<dxf_shape_reader::text_entity>>
      _texts;
  std::uintmax_t _file_size = 0;
  std::uintmax_t _file_read_size = 0;
  Resource_FormatType _src_encoding = Resource_ANSI;
  parameters _params;
  std::string _error;

protected:
  void get_line() override;
  bool set_source_encoding(const std::string &codepage) override;
  std::string to_utf8(const std::string &strSource) override;

public:
  dxf_shape_reader(const std::string &filepath);

  const auto &shape_layers() const { return _layers; }
  const auto &text_layers() const { return _texts; }
  const auto &layer_names() const { return _layer_names; }
  const auto &error() const { return _error; }

  void on_read_line(const dxf_coords &s, const dxf_coords &e,
                    bool hidden) override;
  void on_read_polyline(const dxf_polyline &polyline) override;
  void on_read_point(const dxf_coords &s) override;
  void on_read_text(const dxf_text &text) override;
  void on_read_mtext(const dxf_mtext &text) override;
  void on_read_arc(const dxf_coords &s, const dxf_coords &e,
                   const dxf_coords &c, bool dir, bool hidden) override;
  void on_read_circle(const dxf_coords &s, const dxf_coords &c, bool dir,
                      bool hidden) override;
  void on_read_ellipse(const dxf_coords &c, double major_radius,
                       double minor_radius, double rotation, double start_angle,
                       double end_angle, bool dir) override;
  void on_read_spline(const dxf_spline &spline) override;
  void on_read_insert(const dxf_insert &ins) override;
  void on_read_dimension(const dxf_coords &s, const dxf_coords &e,
                         const dxf_coords &point, double rotation) override;
  void on_read_solid(const dxf_solid &solid) override;
  void on_read_3d_face(const dxf_3d_face &face) override;

  void report_error(const std::string &msg) override;
  void add_graphics() const override;

  static ogg_handle<Geom_BSplineCurve>
  create_spline_from_poles_and_knots(const dxf_spline &spline);
  static ogg_handle<Geom_BSplineCurve>
  create_interpolation_spline(const dxf_spline &spline);

  gp_Pnt to_pnt(const dxf_coords &coords) const;
  void add_shape(const TopoDS_Shape &shape);
  void add_text(const dxf_shape_reader::text_entity &text);

  TopoDS_Face make_face(const dxf_quad_base &quad) const;
};

} // namespace dxf
} // namespace flywave
