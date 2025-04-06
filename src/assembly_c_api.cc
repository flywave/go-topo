#include "assembly_c_api.h"
#include "assembly.hh"
#include "topo_impl.hh"
#include "workplane_impl.hh"

#ifdef __cplusplus
extern "C" {
#endif

struct _assembly_object_t {
  flywave::topo::assembly_object obj;
};

struct _assembly_element_t {
  flywave::topo::assembly_element el;
};

struct _assembly_t {
  std::shared_ptr<flywave::topo::assembly> ptr;
};

struct _constraint_param_t {
  flywave::topo::constraint_param param;
};

// Assembly object functions
assembly_object_t *aassembly_object_create_from_shape(topo_shape_t *shape) {
  auto obj = new assembly_object_t{flywave::topo::assembly_object(*shape->shp)};
  return obj;
}

assembly_object_t *
assembly_object_create_from_workplane(workplane_t *workplane) {
  auto obj =
      new assembly_object_t{flywave::topo::assembly_object(workplane->ptr)};
  return obj;
}

void assembly_object_free(assembly_object_t *obj) {
  if (obj)
    delete obj;
}

topo_shape_t *assembly_object_get_shape(assembly_object_t *obj) {
  if (auto shp = boost::get<flywave::topo::shape>(&obj->obj)) {
    return new topo_shape_t{std::make_shared<flywave::topo::shape>(*shp)};
  }
  return nullptr;
}

workplane_t *assembly_object_get_workplane(assembly_object_t *obj) {
  if (auto wp =
          boost::get<std::shared_ptr<flywave::topo::workplane>>(&obj->obj)) {
    return new workplane_t{*wp};
  }
  return nullptr;
}

_Bool assembly_object_is_shape(assembly_object_t *obj) {
  if (boost::get<flywave::topo::shape>(&obj->obj)) {
    return true;
  }
  return false;
}

_Bool assembly_object_is_workplane(assembly_object_t *obj) {
  if (boost::get<std::shared_ptr<flywave::topo::workplane>>(&obj->obj)) {
    return true;
  }
  return false;
}

// Assembly element functions
const char *assembly_element_get_name(assembly_element_t *el) {
  return el->el.name.c_str();
}

topo_shape_t *assembly_element_get_shape(assembly_element_t *el) {
  auto shape =
      new topo_shape_t{std::make_shared<flywave::topo::shape>(el->el.shp)};
  return shape;
}

color_t *assembly_element_get_color(assembly_element_t *el) {
  auto color = new color_t{.r = el->el.color->Red(),
                           .g = el->el.color->Green(),
                           .b = el->el.color->Blue()};
  return color;
}

topo_location_t *assembly_element_get_location(assembly_element_t *el) {
  auto loc = new topo_location_t{el->el.location};
  return loc;
}

void assembly_element_free(assembly_element_t *el) {
  if (el)
    delete el;
}

// Constraint param functions
constraint_param_t *constraint_param_create_from_double(double value) {
  auto param = new constraint_param_t{flywave::topo::constraint_param(value)};
  return param;
}

constraint_param_t *constraint_param_create_from_double3(double x, double y,
                                                         double z) {
  auto param = new constraint_param_t{
      flywave::topo::constraint_param(std::array<double, 3>{x, y, z})};
  return param;
}

constraint_param_t *constraint_param_create_from_double2(double x, double y) {
  auto param = new constraint_param_t{
      flywave::topo::constraint_param(std::array<double, 2>{x, y})};
  return param;
}

void constraint_param_free(constraint_param_t *param) {
  if (param)
    delete param;
}

// Assembly functions
assembly_t *assembly_create(assembly_object_t *obj, topo_location_t *loc,
                            const char *name, color_t *color) {
  auto as = new assembly_t{flywave::topo::assembly::create(
      obj->obj,
      loc ? std::make_shared<flywave::topo::topo_location>(loc->loc) : nullptr,
      name ? name : "",
      color ? std::make_shared<Quantity_Color>(color->r, color->g, color->b,
                                               Quantity_TOC_RGB)
            : nullptr)};
  return as;
}

void assembly_free(assembly_t *as) {
  if (as)
    delete as;
}

assembly_t *assembly_copy(assembly_t *as) {
  auto copy = new assembly_t{as->ptr};
  return copy;
}

void assembly_add_object(assembly_t *as, assembly_object_t *obj,
                         topo_location_t *loc, const char *name,
                         color_t *color) {
  as->ptr->add(
      obj->obj,
      loc ? std::make_shared<flywave::topo::topo_location>(loc->loc) : nullptr,
      name ? name : "",
      color ? std::make_shared<Quantity_Color>(color->r, color->g, color->b,
                                               Quantity_TOC_RGB)
            : nullptr);
}

void assembly_add_assembly(assembly_t *as, assembly_t *obj,
                           topo_location_t *loc, const char *name,
                           color_t *color) {
  as->ptr->add(
      obj->ptr,
      loc ? std::make_shared<flywave::topo::topo_location>(loc->loc) : nullptr,
      name ? name : "",
      color ? std::make_shared<Quantity_Color>(color->r, color->g, color->b,
                                               Quantity_TOC_RGB)
            : nullptr);
}

void assembly_remove(assembly_t *as, const char *name) {
  as->ptr->remove(name ? name : "");
}

// Constraint functions
void assembly_constrain(assembly_t *as, const char *q1, const char *q2,
                        int kind, constraint_param_t *param) {
  as->ptr->constrain(q1 ? q1 : "", q2 ? q2 : "",
                     static_cast<flywave::topo::constraint_kind>(kind),
                     param ? param->param : flywave::topo::constraint_param());
}

void assembly_constrain1(assembly_t *as, const char *q1, int kind,
                         constraint_param_t *param) {
  as->ptr->constrain(q1 ? q1 : "",
                     static_cast<flywave::topo::constraint_kind>(kind),
                     param ? param->param : flywave::topo::constraint_param());
}

void assembly_constrain2(assembly_t *as, const char *id1, topo_shape_t *s1,
                         const char *id2, topo_shape_t *s2, int kind,
                         constraint_param_t *param) {
  as->ptr->constrain(id1 ? id1 : "", s1 ? *s1->shp : flywave::topo::shape(),
                     id2 ? id2 : "", s2 ? *s2->shp : flywave::topo::shape(),
                     static_cast<flywave::topo::constraint_kind>(kind),
                     param ? param->param : flywave::topo::constraint_param());
}

void assembly_constrain3(assembly_t *as, const char *id1, topo_shape_t *s1,
                         int kind, constraint_param_t *param) {
  as->ptr->constrain(id1 ? id1 : "", s1 ? *s1->shp : flywave::topo::shape(),
                     static_cast<flywave::topo::constraint_kind>(kind),
                     param ? param->param : flywave::topo::constraint_param());
}

// Other assembly operations
void assembly_solve(assembly_t *as, int verbosity) {
  as->ptr->solve(verbosity);
}

void assembly_export_to(assembly_t *as, const char *path, int mode) {
  as->ptr->export_to(path ? path : "",
                     static_cast<flywave::topo::assembly_export_mode>(mode));
}

topo_shape_t **assembly_shapes(assembly_t *as, int *size) {
  auto shapes = as->ptr->shapes();
  *size = static_cast<int>(shapes.size());
  auto result = new topo_shape_t *[shapes.size()];
  for (size_t i = 0; i < shapes.size(); i++) {
    result[i] =
        new topo_shape_t{std::make_shared<flywave::topo::shape>(shapes[i])};
  }
  return result;
}

void topo_shape_list_free(topo_shape_t **list, int size) {
  if (list) {
    delete[] list;
  }
}

topo_compound_t *assembly_to_compound(assembly_t *as) {
  auto comp = new topo_compound_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::compound>(
                                  as->ptr->to_compound())}};
  return comp;
}

assembly_element_t **assembly_get_elements(assembly_t *as, int *size) {
  auto elements = as->ptr->get_elements();
  *size = static_cast<int>(elements.size());
  auto result = new assembly_element_t *[elements.size()];
  for (size_t i = 0; i < elements.size(); i++) {
    result[i] = new assembly_element_t{elements[i]};
  }
  return result;
}

void assembly_element_list_free(assembly_element_t **list, int size) {
  if (list) {
    delete[] list;
  }
}

const char *assembly_get_name(assembly_t *as) {
  return as->ptr->name().c_str();
}

topo_location_t *assembly_get_location(assembly_t *as) {
  auto loc = new topo_location_t{as->ptr->location()};
  return loc;
}

color_t *assembly_get_color(assembly_t *as) {
  auto c = as->ptr->color();
  auto color = new color_t{.r = c.Red(), .g = c.Green(), .b = c.Blue()};
  return color;
}

assembly_object_t *assembly_get_object(assembly_t *as) {
  auto obj = new assembly_object_t{as->ptr->obj()};
  return obj;
}

assembly_t **assembly_children(assembly_t *as, int *size) {
  auto children = as->ptr->children();
  *size = static_cast<int>(children.size());
  auto result = new assembly_t *[children.size()];
  for (size_t i = 0; i < children.size(); i++) {
    result[i] = new assembly_t{children[i]};
  }
  return result;
}

void assembly_list_free(assembly_t **list, int size) {
  if (list) {
    delete[] list;
  }
}

#ifdef __cplusplus
}
#endif
