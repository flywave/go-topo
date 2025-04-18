#pragma once

#include <Geom_BSplineCurve.hxx>
#include <Resource_FormatType.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Vertex.hxx>
#include <TopoDS_Wire.hxx>
#include <gp_Circ.hxx>
#include <gp_Elips.hxx>

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

#include "dxf.hh"
#include "ogg_handle.hh"

namespace flywave {
namespace dxf {

struct dxf_text_entity {
  std::string text;
  gp_Pnt position;
  gp_Vec normal;
  gp_Vec x_axis_dir;
  double height = 1.0;
  double rotation = 0.0;
  color_index_t color = 256;
};

struct dxf_shape_entity {
  color_index_t color = 0;
  TopoDS_Shape shape;
};

class dxf_shape_reader : public dxf_read {
public:
  struct parameters {
    double scaling = 1.;
  };

private:
  std::set<std::string> _layer_names;
  std::unordered_map<std::string, std::vector<dxf_shape_entity>> _layers;
  std::unordered_map<std::string, std::vector<dxf_text_entity>> _texts;
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
  void add_text(const dxf_text_entity &text);

  TopoDS_Face make_face(const dxf_quad_base &quad) const;
};

class dxf_shape_writer : public dxf_write {
public:
  struct parameters {
    double scaling = 1.0;
    bool write_3d_face = false;
  };

private:
  std::unordered_map<std::string, std::vector<dxf_shape_entity>> _layers;
  std::unordered_map<std::string, std::vector<dxf_text_entity>> _texts;

  parameters _params;

public:
  dxf_shape_writer(const std::string &filepath);

  void set_parameters(const parameters &params) { _params = params; }

  void add_text(const std::string &layer_name, const dxf_text_entity &text);

  void add_shape(const std::string &layer_name, const TopoDS_Shape &shape,
                 color_index_t color = 256);

  void add_shape_layer(
      const std::string &layer_name,
      const std::vector<std::pair<TopoDS_Shape, color_index_t>> &shapes);

  void add_text_layer(const std::string &layer_name,
                      const std::vector<dxf_text_entity> &texts);

  bool write();

protected:
  void put_arc(const dxf_coords &center, const dxf_coords &start,
               const dxf_coords &end, std::ostringstream &outStream,
               const std::string &handle, const std::string &ownerHandle);
  void put_ellipse(const dxf_coords &center, const dxf_coords &majorPoint,
                   double ratio, std::ostringstream &outStream,
                   const std::string &handle, const std::string &ownerHandle);
  void put_point(const dxf_coords &point, std::ostringstream &outStream,
                 const std::string &handle, const std::string &ownerHandle);
  void put_line(const gp_Pnt &start, const gp_Pnt &end,
                std::ostringstream &outStream, const std::string &handle,
                const std::string &ownerHandle);
  void put_circle(const gp_Circ &circle, std::ostringstream &outStream,
                  const std::string &handle, const std::string &ownerHandle);
  void put_text(const dxf_text_entity &text, std::ostringstream &outStream,
                const std::string &handle, const std::string &ownerHandle);
  void put_3d_face(const std::array<dxf_coords, 4> &corners,
                   std::ostringstream &outStream, const std::string &handle,
                   const std::string &ownerHandle);
  void put_spline(const dxf_spline &spline, std::ostringstream &outStream,
                  const std::string &handle, const std::string &ownerHandle);

  void write_shape(const TopoDS_Shape &shape, color_index_t color);
  void write_edge(const TopoDS_Edge &edge, color_index_t color);
  void write_wire(const TopoDS_Wire &wire, color_index_t color);
  void write_face(const TopoDS_Face &face, color_index_t color);
  void write_vertex(const TopoDS_Vertex &vertex, color_index_t color);
  void write_spline(const Handle(Geom_BSplineCurve) & spline,
                    color_index_t color);
  void write_3d_face(const TopoDS_Face &face, color_index_t color);

  void write_line(const gp_Pnt &start, const gp_Pnt &end);
  void write_circle(const gp_Circ &circle);
  void write_arc(const gp_Circ &circle, double start_angle, double end_angle);
  void write_ellipse(const gp_Elips &ellipse);
  void write_point(const gp_Pnt &point);
};

} // namespace dxf
} // namespace flywave
