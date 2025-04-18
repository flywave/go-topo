#ifndef __FLYWAVE_MESH_TOPO_MESH_HH__
#define __FLYWAVE_MESH_TOPO_MESH_HH__

#include <Quantity_Color.hxx>
#include <TDF_Label.hxx>
#include <TDocStd_Document.hxx>
#include <TopTools_HSequenceOfShape.hxx>
#include <TopTools_IndexedMapOfShape.hxx>
#include <TopoDS_Shape.hxx>
#include <XCAFApp_Application.hxx>
#include <XCAFDoc_ColorTool.hxx>
#include <XCAFDoc_DocumentTool.hxx>
#include <XCAFDoc_ShapeTool.hxx>

#include <list>
#include <vector>

#include "mesh_receiver.hh"
#include "shape.hh"

namespace flywave {
namespace topo {

class mesh : public std::enable_shared_from_this<mesh> {
public:
  mesh();
  mesh(TopoDS_Shape shp);
  mesh(const shape &shp);
  mesh(Handle_TDocStd_Document doc);

  virtual ~mesh() = default;

  void map_shapes(Handle_TopTools_HSequenceOfShape shapes);
  void map_shape(TopoDS_Shape shp);
  void map_shape(const shape &shp);
  void map_shape(const std::vector<shape> &shp);

  void triangulation(mesh_receiver &mesh, double deflection = 0.01,
                     double tolerance = 1.e-6);

private:
  void map_shapes(Handle_TDocStd_Document doc);
  void heal_geometry(TopoDS_Shape shape, double tolerance, bool fixsmalledges,
                     bool fixspotstripfaces, bool sewfaces,
                     bool makesolids = false);
  void clear_maps();
  void build_maps(const TopoDS_Shape &shape);
  void create_shape_colour_stacks(const TDF_Label &label);
  bool has_children(const TDF_Label &label);
  void add_label_contents(const TDF_Label &label);
  bool map_stacks();
  void basic_traversal();
  bool style_print(const TDF_Label &label, const TopLoc_Location &aLocation,
                   shape *shp);
  void label_traversal(const TDF_Label &aLabel,
                       const TopLoc_Location &aLocation, shape *parent);
  bool extract_colour(const TDF_Label &label, Quantity_Color &colour);
  bool extract_colour(const TopoDS_Shape &shape,
                      const Handle_XCAFDoc_ColorTool &colourTool,
                      Quantity_Color &colour);
  bool extract_colour(const TDF_Label &label,
                      const Handle_XCAFDoc_ColorTool &colourTool,
                      Quantity_Color &colour);
  void traverse_shape(const TopoDS_Shape &shape);
  void traverse_label(const TDF_Label &label);
  bool query_color(const TopoDS_Shape &shape, Quantity_Color &color);

private:
  TopTools_IndexedMapOfShape _cmap, _csmap, _somap, _shmap, _fmap, _emap, _vmap;

  Handle(TDocStd_Document) _doc;
  Handle(XCAFDoc_ShapeTool) _shape_tool;
  Handle(XCAFApp_Application) _app;
  Handle(XCAFDoc_ColorTool) _color_tool;
  Handle(XCAFDoc_LayerTool) _layer_tool;

  std::vector<shape> _label_shapes;

  std::vector<TopoDS_Shape> _shape_stack;
  std::vector<Quantity_Color> _colour_stack;
  Quantity_Color _current_colour;
};

} // namespace topo
} // namespace flywave

#endif // __FLYWAVE_MESH_TOPO_MESH_HH__
