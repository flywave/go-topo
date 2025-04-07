#include "selector_c_api.h"
#include "selector.hh"
#include "selector_impl.hh"
#include "topo_impl.hh"

#ifdef __cplusplus
extern "C" {
#endif

selector_t *selector_custom_selector_create(
    void *user_data,
    topo_shape_t **(*func)(void *user_data, topo_shape_t **, int, int *)) {
  auto func_ = [func,
                user_data](const std::vector<flywave::topo::shape> &shapes) {
    topo_shape_t **shapes_ = new topo_shape_t *[shapes.size()];
    for (size_t i = 0; i < shapes.size(); ++i) {
      shapes_[i] = new topo_shape_t{
          .shp = std::make_shared<flywave::topo::shape>(shapes[i])};
    }
    int retSize = 0;
    auto rets =
        func(user_data, shapes_, static_cast<int>(shapes.size()), &retSize);
    for (int i = 0; i < shapes.size(); ++i) {
      delete shapes_[i];
    }
    delete[] shapes_;
    std::vector<flywave::topo::shape> outs;
    outs.reserve(retSize);
    for (int i = 0; i < retSize; ++i) {
      outs.push_back(*(rets[i]->shp));
    }
    return outs;
  };

  auto sel =
      new selector_t{std::make_shared<flywave::topo::custom_selector>(func_)};
  return sel;
}

void selector_custom_selector_free(selector_t *sel) {
  if (sel) {
    delete sel;
  }
}

selector_t *selector_nearest_to_point_selector_create(topo_vector_t *p) {
  auto sel = new selector_t{
      std::make_shared<flywave::topo::nearest_to_point_selector>(p->vec)};
  return sel;
}

void selector_nearest_to_point_selector_free(selector_t *sel) {
  if (sel)
    delete sel;
}

selector_t *selector_box_selector_create(topo_vector_t *p0, topo_vector_t *p1,
                                         bool use_bb) {
  auto sel = new selector_t{
      std::make_shared<flywave::topo::box_selector>(p0->vec, p1->vec, use_bb)};
  return sel;
}

void selector_box_selector_free(selector_t *sel) {
  if (sel)
    delete sel;
}

selector_t *selector_radius_nth_selector_create(int n, bool direction_max,
                                                double tolerance) {
  auto sel =
      new selector_t{std::make_shared<flywave::topo::radius_nth_selector>(
          n, direction_max, tolerance)};
  return sel;
}

void selector_radius_nth_selector_free(selector_t *sel) {
  if (sel)
    delete sel;
}

selector_t *selector_center_nth_selector_create(topo_vector_t *dir, int n,
                                                bool direction_max,
                                                double tolerance) {
  auto sel =
      new selector_t{std::make_shared<flywave::topo::center_nth_selector>(
          dir->vec, n, direction_max, tolerance)};
  return sel;
}

void selector_center_nth_selector_free(selector_t *sel) {
  if (sel)
    delete sel;
}

selector_t *selector_direction_minmax_selector_create(topo_vector_t *dir,
                                                      bool direction_max,
                                                      double tolerance) {
  auto sel =
      new selector_t{std::make_shared<flywave::topo::direction_minmax_selector>(
          dir->vec, direction_max, tolerance)};
  return sel;
}

void selector_direction_minmax_selector_free(selector_t *sel) {
  if (sel)
    delete sel;
}

selector_t *selector_parallel_dir_selector_create(topo_vector_t *dir,
                                                  double tol) {
  auto sel = new selector_t{
      std::make_shared<flywave::topo::parallel_dir_selector>(dir->vec, tol)};
  return sel;
}

void selector_parallel_dir_selector_free(selector_t *sel) {
  if (sel)
    delete sel;
}

selector_t *selector_dir_selector_create(topo_vector_t *dir, double tol) {
  auto sel = new selector_t{
      std::make_shared<flywave::topo::dir_selector>(dir->vec, tol)};
  return sel;
}

void selector_dir_selector_free(selector_t *sel) {
  if (sel)
    delete sel;
}

selector_t *selector_perpendicular_dir_selector_create(topo_vector_t *dir,
                                                       double tol) {
  auto sel = new selector_t{
      std::make_shared<flywave::topo::perpendicular_dir_selector>(dir->vec,
                                                                  tol)};
  return sel;
}

void selector_perpendicular_dir_selector_free(selector_t *sel) {
  if (sel)
    delete sel;
}

selector_t *selector_direction_nth_selector_create(topo_vector_t *dir, int n,
                                                   bool direction_max,
                                                   double tolerance) {
  auto sel =
      new selector_t{std::make_shared<flywave::topo::direction_nth_selector>(
          dir->vec, n, direction_max, tolerance)};
  return sel;
}

void selector_direction_nth_selector_free(selector_t *sel) {
  if (sel)
    delete sel;
}

selector_t *selector_length_nth_selector_create(int n, bool direction_max,
                                                double tolerance) {
  auto sel =
      new selector_t{std::make_shared<flywave::topo::length_nth_selector>(
          n, direction_max, tolerance)};
  return sel;
}

void selector_length_nth_selector_free(selector_t *sel) {
  if (sel)
    delete sel;
}

selector_t *selector_type_selector_create(int type) {
  auto sel = new selector_t{std::make_shared<flywave::topo::type_selector>(
      static_cast<flywave::topo::shape_geom_type>(type))};
  return sel;
}

void selector_type_selector_free(selector_t *sel) {
  if (sel)
    delete sel;
}

selector_t *selector_area_nth_selector_create(int n, bool direction_max,
                                              double tolerance) {
  auto sel = new selector_t{std::make_shared<flywave::topo::area_nth_selector>(
      n, direction_max, tolerance)};
  return sel;
}

void selector_area_nth_selector_free(selector_t *sel) {
  if (sel)
    delete sel;
}

selector_t *selector_and_selector_create(selector_t *left, selector_t *right) {
  auto sel = new selector_t{
      std::make_shared<flywave::topo::and_selector>(left->ptr, right->ptr)};
  return sel;
}

void selector_and_selector_free(selector_t *sel) {
  if (sel)
    delete sel;
}

selector_t *selector_or_selector_create(selector_t *left, selector_t *right) {
  auto sel = new selector_t{
      std::make_shared<flywave::topo::or_selector>(left->ptr, right->ptr)};
  return sel;
}

void selector_or_selector_free(selector_t *sel) {
  if (sel)
    delete sel;
}

selector_t *selector_subtract_selector_create(selector_t *left,
                                              selector_t *right) {
  auto sel = new selector_t{std::make_shared<flywave::topo::subtract_selector>(
      left->ptr, right->ptr)};
  return sel;
}

void selector_subtract_selector_free(selector_t *sel) {
  if (sel)
    delete sel;
}

selector_t *selector_not_selector_create(selector_t *sel) {
  auto new_sel =
      new selector_t{std::make_shared<flywave::topo::not_selector>(sel->ptr)};
  return new_sel;
}

void selector_not_selector_free(selector_t *sel) {
  if (sel)
    delete sel;
}

selector_t *selector_string_syntax_selector_create(const char *selector_str) {
  auto sel =
      new selector_t{std::make_shared<flywave::topo::string_syntax_selector>(
          selector_str ? selector_str : "")};
  return sel;
}

void selector_string_syntax_selector_free(selector_t *sel) {
  if (sel)
    delete sel;
}

#ifdef __cplusplus
}
#endif
