#include <cstdio>
#include "assembly_c_api.h"
#include "cgo_lock.hh"
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

assembly_object_t *assembly_object_create_from_shape(topo_shape_t *shape) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new assembly_object_t{.obj =
                                   flywave::topo::assembly_object(*shape->shp)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

assembly_object_t *
assembly_object_create_from_workplane(workplane_t *workplane) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new assembly_object_t{
      .obj = flywave::topo::assembly_object(workplane->ptr)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

void assembly_object_free(assembly_object_t *obj) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (obj)
    delete obj;
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

topo_shape_t *assembly_object_get_shape(assembly_object_t *obj) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (auto shp = boost::get<flywave::topo::shape>(&obj->obj)) {
    return new topo_shape_t{.shp =
                                std::make_shared<flywave::topo::shape>(*shp)};
  }
  return nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

workplane_t *assembly_object_get_workplane(assembly_object_t *obj) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (auto wp =
          boost::get<std::shared_ptr<flywave::topo::workplane>>(&obj->obj)) {
    return new workplane_t{.ptr = *wp};
  }
  return nullptr;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

_Bool assembly_object_is_shape(assembly_object_t *obj) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (boost::get<flywave::topo::shape>(&obj->obj)) {
    return true;
  }
  return false;
  }
  catch (const std::exception &e) {
    (void)e;
    return false;
  }
  catch (...) {
    return false;
  }
}

_Bool assembly_object_is_workplane(assembly_object_t *obj) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (boost::get<std::shared_ptr<flywave::topo::workplane>>(&obj->obj)) {
    return true;
  }
  return false;
  }
  catch (const std::exception &e) {
    (void)e;
    return false;
  }
  catch (...) {
    return false;
  }
}

const char *assembly_element_get_name(assembly_element_t *el) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return el->el.name.c_str();
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

topo_shape_t *assembly_element_get_shape(assembly_element_t *el) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new topo_shape_t{
      .shp = std::make_shared<flywave::topo::shape>(el->el.shp)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

color_t assembly_element_get_color(assembly_element_t *el) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return color_t{.r = el->el.color->Red(),
                 .g = el->el.color->Green(),
                 .b = el->el.color->Blue()};
  }
  catch (const std::exception &e) {
    (void)e;
    return color_t{};
  }
  catch (...) {
    return color_t{};
  }
}

topo_location_t *assembly_element_get_location(assembly_element_t *el) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new topo_location_t{.loc = el->el.location};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

void assembly_element_free(assembly_element_t *el) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (el)
    delete el;
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

constraint_param_t *constraint_param_create_from_double(double value) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new constraint_param_t{.param =
                                    flywave::topo::constraint_param(value)};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

constraint_param_t *constraint_param_create_from_double3(double x, double y,
                                                         double z) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new constraint_param_t{
      .param = flywave::topo::constraint_param(std::array<double, 3>{x, y, z})};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

constraint_param_t *constraint_param_create_from_double2(double x, double y) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new constraint_param_t{
      .param = flywave::topo::constraint_param(std::array<double, 2>{x, y})};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

void constraint_param_free(constraint_param_t *param) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (param)
    delete param;
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

assembly_t *assembly_create(assembly_object_t *obj, topo_location_t *loc,
                            const char *name, color_t *color) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  auto as = new assembly_t{
      .ptr = flywave::topo::assembly::create(
          obj->obj,
          loc ? std::make_shared<flywave::topo::topo_location>(loc->loc)
              : nullptr,
          name ? name : "",
          color ? std::make_shared<Quantity_Color>(color->r, color->g, color->b,
                                                   Quantity_TOC_RGB)
                : nullptr)};
  return as;
  }
  catch (const std::exception &e) {
    return nullptr;
  }
  catch (...) {
    // 失败路径告警 (遵循仓库 warn 惯例): OCC 侧 Standard_Failure 体系
    // 不继承 std::exception, 与 std 异常分开报告
    try { throw; }
    catch (const std::exception &e2) { fprintf(stderr, "assembly_create warning: %s\n", e2.what()); }
    catch (const Standard_Failure &e2) { fprintf(stderr, "assembly_create warning: %s\n", e2.GetMessageString() ? e2.GetMessageString() : "(no msg)"); }
    catch (...) { fprintf(stderr, "assembly_create warning: unknown error\n"); }
    return nullptr;
  }
}

void assembly_free(assembly_t *as) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (as)
    delete as;
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

assembly_t *assembly_copy(assembly_t *as) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  auto copy = new assembly_t{.ptr = as->ptr};
  return copy;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

void assembly_add_object(assembly_t *as, assembly_object_t *obj,
                         topo_location_t *loc, const char *name,
                         color_t *color) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  as->ptr->add(
      obj->obj,
      loc ? std::make_shared<flywave::topo::topo_location>(loc->loc) : nullptr,
      name ? name : "",
      color ? std::make_shared<Quantity_Color>(color->r, color->g, color->b,
                                               Quantity_TOC_RGB)
            : nullptr);
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

void assembly_add_assembly(assembly_t *as, assembly_t *obj,
                           topo_location_t *loc, const char *name,
                           color_t *color) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  as->ptr->add(
      obj->ptr,
      loc ? std::make_shared<flywave::topo::topo_location>(loc->loc) : nullptr,
      name ? name : "",
      color ? std::make_shared<Quantity_Color>(color->r, color->g, color->b,
                                               Quantity_TOC_RGB)
            : nullptr);
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

void assembly_remove(assembly_t *as, const char *name) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  as->ptr->remove(name ? name : "");
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

void assembly_constrain(assembly_t *as, const char *q1, const char *q2,
                        int kind, constraint_param_t *param) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  as->ptr->constrain(q1 ? q1 : "", q2 ? q2 : "",
                     static_cast<flywave::topo::constraint_kind>(kind),
                     param ? param->param : flywave::topo::constraint_param());
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

void assembly_constrain1(assembly_t *as, const char *q1, int kind,
                         constraint_param_t *param) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  as->ptr->constrain(q1 ? q1 : "",
                     static_cast<flywave::topo::constraint_kind>(kind),
                     param ? param->param : flywave::topo::constraint_param());
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

void assembly_constrain2(assembly_t *as, const char *id1, topo_shape_t *s1,
                         const char *id2, topo_shape_t *s2, int kind,
                         constraint_param_t *param) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  as->ptr->constrain(id1 ? id1 : "", s1 ? *s1->shp : flywave::topo::shape(),
                     id2 ? id2 : "", s2 ? *s2->shp : flywave::topo::shape(),
                     static_cast<flywave::topo::constraint_kind>(kind),
                     param ? param->param : flywave::topo::constraint_param());
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

void assembly_constrain3(assembly_t *as, const char *id1, topo_shape_t *s1,
                         int kind, constraint_param_t *param) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  as->ptr->constrain(id1 ? id1 : "", s1 ? *s1->shp : flywave::topo::shape(),
                     static_cast<flywave::topo::constraint_kind>(kind),
                     param ? param->param : flywave::topo::constraint_param());
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

void assembly_solve(assembly_t *as, int verbosity) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  as->ptr->solve(verbosity);
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

void assembly_export_to(assembly_t *as, const char *path, int mode) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  as->ptr->export_to(path ? path : "",
                     static_cast<flywave::topo::assembly_export_mode>(mode));
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

topo_shape_t **assembly_shapes(assembly_t *as, int *size) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  auto shapes = as->ptr->shapes();
  *size = static_cast<int>(shapes.size());
  auto result = new topo_shape_t *[shapes.size()];
  for (size_t i = 0; i < shapes.size(); i++) {
    result[i] = new topo_shape_t{
        .shp = std::make_shared<flywave::topo::shape>(shapes[i])};
  }
  return result;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

topo_compound_t assembly_to_compound(assembly_t *as) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return topo_compound_t{
      .shp = new topo_shape_t{.shp = std::make_shared<flywave::topo::compound>(
                                  as->ptr->to_compound())}};
  }
  catch (const std::exception &e) {
    (void)e;
    return topo_compound_t{};
  }
  catch (...) {
    return topo_compound_t{};
  }
}

assembly_element_t **assembly_get_elements(assembly_t *as, int *size) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  auto elements = as->ptr->get_elements();
  *size = static_cast<int>(elements.size());
  auto result = new assembly_element_t *[elements.size()];
  for (size_t i = 0; i < elements.size(); i++) {
    result[i] = new assembly_element_t{.el = elements[i]};
  }
  return result;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

void assembly_element_list_free(assembly_element_t **list, int size) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (list) {
    for (int i = 0; i < size; i++) {
      delete list[i];
    }
    delete[] list;
  }
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

void assembly_element_list_free_shallow(assembly_element_t **list) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  delete[] list;
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

const char *assembly_get_name(assembly_t *as) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return as->ptr->name().c_str();
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

topo_location_t *assembly_get_location(assembly_t *as) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new topo_location_t{.loc = as->ptr->location()};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

color_t assembly_get_color(assembly_t *as) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  auto c = as->ptr->color();
  return color_t{.r = c.Red(), .g = c.Green(), .b = c.Blue()};
  }
  catch (const std::exception &e) {
    (void)e;
    return color_t{};
  }
  catch (...) {
    return color_t{};
  }
}

assembly_object_t *assembly_get_object(assembly_t *as) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  return new assembly_object_t{.obj = as->ptr->obj()};
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

assembly_t **assembly_children(assembly_t *as, int *size) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  auto children = as->ptr->children();
  *size = static_cast<int>(children.size());
  auto result = new assembly_t *[children.size()];
  for (size_t i = 0; i < children.size(); i++) {
    result[i] = new assembly_t{.ptr = children[i]};
  }
  return result;
  }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

void assembly_list_free(assembly_t **list, int size) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try {
  if (list) {
    for (int i = 0; i < size; i++) {
      delete list[i];
    }
    delete[] list;
  }
  }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

// 仅释放指针数组本身, 元素所有权归调用方 (由 assembly_free 逐个释放)。
void assembly_list_free_shallow(assembly_t **list) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try { delete[] list;   }
  catch (const std::exception &e) {
    (void)e;
  }
  catch (...) {
  }
}

bool assembly_has_error(assembly_t *as) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try { return as->ptr->has_error();   }
  catch (const std::exception &e) {
    (void)e;
    return false;
  }
  catch (...) {
    return false;
  }
}

const char *assembly_error(assembly_t *as) {
  std::lock_guard<std::recursive_mutex> ___cgo_glock(flywave::topo::topo_glock()); try { return as->ptr->error().c_str();   }
  catch (const std::exception &e) {
    (void)e;
    return nullptr;
  }
  catch (...) {
    return nullptr;
  }
}

#ifdef __cplusplus
}
#endif
