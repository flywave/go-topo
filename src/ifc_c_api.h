#ifndef GO_IFC_C_API_H
#define GO_IFC_C_API_H

#include "topo_c_api.h"

#if defined(WIN32) || defined(WINDOWS) || defined(_WIN32) || defined(_WINDOWS)
#define IFCCAPICALL __declspec(dllexport)
#else
#define IFCCAPICALL
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _ifc_convert_t ifc_convert_t;
typedef struct _ifc_element_t ifc_element_t;
typedef struct _ifc_triangulation_t ifc_triangulation_t;
typedef struct _ifc_triangulation_material_t ifc_triangulation_material_t;
typedef struct _ifc_data_t ifc_data_t;
typedef struct _ifc_header_t ifc_header_t;
typedef struct _ifc_unit_t ifc_unit_t;
typedef struct _ifc_property_t ifc_property_t;
typedef struct _ifc_property_set_t ifc_property_set_t;
typedef struct _ifc_quantity_t ifc_quantity_t;
typedef struct _ifc_element_quantity_t ifc_element_quantity_t;
typedef struct _ifc_task_time_t ifc_task_time_t;
typedef struct _ifc_task_t ifc_task_t;
typedef struct _ifc_work_time_t ifc_work_time_t;
typedef struct _ifc_work_calendar_t ifc_work_calendar_t;
typedef struct _ifc_work_schedule_t ifc_work_schedule_t;
typedef struct _ifc_work_plan_t ifc_work_plan_t;
typedef struct _ifc_connection_t ifc_connection_t;
typedef struct _ifc_type_object_t ifc_type_object_t;
typedef struct _ifc_layer_t ifc_layer_t;
typedef struct _ifc_material_t ifc_material_t;
typedef struct _ifc_group_t ifc_group_t;
typedef struct _ifc_time_period_t ifc_time_period_t;
typedef struct _ifc_recurrence_pattern_t ifc_recurrence_pattern_t;
typedef struct _ifc_rel_defines_by_type_t ifc_rel_defines_by_type_t;
typedef struct _ifc_rel_defines_by_properties_t ifc_rel_defines_by_properties_t;

typedef struct _ifc_color_t {
  double r;
  double g;
  double b;
} ifc_color_t;

IFCCAPICALL _Bool is_ifc_file(const char *filename);

IFCCAPICALL ifc_convert_t *ifc_convert_new();
IFCCAPICALL void ifc_convert_free(ifc_convert_t *p);
IFCCAPICALL _Bool ifc_convert_load(ifc_convert_t *p, const char *filename);
IFCCAPICALL char *ifc_convert_get_version(ifc_convert_t *p); // must free
IFCCAPICALL ifc_data_t *ifc_convert_get_data(ifc_convert_t *p);
IFCCAPICALL ifc_element_t **ifc_convert_get_elements(ifc_convert_t *p,
                                                     int *count);
IFCCAPICALL ifc_triangulation_t **
ifc_convert_get_triangulations(ifc_convert_t *p, int *count);

IFCCAPICALL ifc_element_t **ifc_get_elements(const char *filename, int *count);
IFCCAPICALL void ifc_elements_free(ifc_element_t **shps);
IFCCAPICALL ifc_element_t *ifc_get_element(ifc_element_t **elements, int index);

IFCCAPICALL ifc_triangulation_t **ifc_get_triangulations(const char *filename,
                                                         int *count);
IFCCAPICALL void ifc_triangulations_free(ifc_triangulation_t **triangulations);
IFCCAPICALL ifc_triangulation_t *
ifc_get_triangulation(ifc_triangulation_t **triangulations, int index);
IFCCAPICALL int ifc_triangulation_material_size();

IFCCAPICALL int ifc_element_get_id(ifc_element_t *p);
IFCCAPICALL int ifc_element_get_parent_id(ifc_element_t *p);
IFCCAPICALL const char *ifc_element_get_name(ifc_element_t *p);
IFCCAPICALL const char *ifc_element_get_guid(ifc_element_t *p);
IFCCAPICALL topo_shape_t *ifc_element_get_shape(ifc_element_t *p);
IFCCAPICALL const char *ifc_element_get_type(ifc_element_t *p);
IFCCAPICALL const double *ifc_element_get_transform(ifc_element_t *p);

IFCCAPICALL void ifc_triangulation_free(ifc_triangulation_t *p);
IFCCAPICALL const double *ifc_triangulation_get_verts(ifc_triangulation_t *p,
                                                      int *count);
IFCCAPICALL const int *ifc_triangulation_get_faces(ifc_triangulation_t *p,
                                                   int *count);
IFCCAPICALL const double *ifc_triangulation_get_normals(ifc_triangulation_t *p,
                                                        int *count);
IFCCAPICALL const int *ifc_triangulation_get_edges(ifc_triangulation_t *p,
                                                   int *count);
IFCCAPICALL const double *ifc_triangulation_get_uvs(ifc_triangulation_t *p,
                                                    int *count);
IFCCAPICALL const int *
ifc_triangulation_get_material_ids(ifc_triangulation_t *p, int *count);
IFCCAPICALL const int *ifc_triangulation_get_item_ids(ifc_triangulation_t *p,
                                                      int *count);
IFCCAPICALL int ifc_triangulation_get_id(ifc_triangulation_t *p);

IFCCAPICALL int ifc_triangulation_get_parent_id(ifc_triangulation_t *p);

IFCCAPICALL const char *ifc_triangulation_get_name(ifc_triangulation_t *p);

IFCCAPICALL const char *ifc_triangulation_get_guid(ifc_triangulation_t *p);

IFCCAPICALL const char *ifc_triangulation_get_type(ifc_triangulation_t *p);

IFCCAPICALL const double *ifc_triangulation_get_transform(ifc_triangulation_t *p);
IFCCAPICALL const int *
ifc_triangulation_get_edges_item_ids(ifc_triangulation_t *p, int *count);

IFCCAPICALL ifc_triangulation_material_t *
ifc_triangulation_get_materials(ifc_triangulation_t *p, int *count);
IFCCAPICALL void
ifc_triangulation_materials_free(ifc_triangulation_material_t *mtls);

IFCCAPICALL const char *
ifc_triangulation_material_get_name(ifc_triangulation_material_t *mtl);
IFCCAPICALL ifc_color_t
ifc_triangulation_material_get_diffuse(ifc_triangulation_material_t *mtl);
IFCCAPICALL ifc_color_t
ifc_triangulation_material_get_surface(ifc_triangulation_material_t *mtl);
IFCCAPICALL ifc_color_t
ifc_triangulation_material_get_specular(ifc_triangulation_material_t *mtl);
IFCCAPICALL double
ifc_triangulation_material_get_specularity(ifc_triangulation_material_t *mtl);
IFCCAPICALL double
ifc_triangulation_material_get_transparency(ifc_triangulation_material_t *mtl);

IFCCAPICALL void ifc_header_free(ifc_header_t *header);

// FileDescription 相关函数
IFCCAPICALL const char *
ifc_header_get_implementation_level(ifc_header_t *header);
IFCCAPICALL const char **ifc_header_get_descriptions(ifc_header_t *header,
                                                     int *count);
IFCCAPICALL void ifc_header_free_descriptions(const char **descriptions);

// FileName 相关函数
IFCCAPICALL const char *ifc_header_get_filename(ifc_header_t *header);
IFCCAPICALL const char **ifc_header_get_authors(ifc_header_t *header,
                                                int *count);
IFCCAPICALL void ifc_header_free_authors(const char **authors);
IFCCAPICALL const char **ifc_header_get_organizations(ifc_header_t *header,
                                                      int *count);
IFCCAPICALL void ifc_header_free_organizations(const char **organizations);
IFCCAPICALL const char *ifc_header_get_timestamp(ifc_header_t *header);
IFCCAPICALL const char *
ifc_header_get_preprocessor_version(ifc_header_t *header);
IFCCAPICALL const char *ifc_header_get_originating_system(ifc_header_t *header);
IFCCAPICALL const char *ifc_header_get_authorization(ifc_header_t *header);

// FileSchema 相关函数
IFCCAPICALL const char **ifc_header_get_schema_identifiers(ifc_header_t *header,
                                                           int *count);
IFCCAPICALL void ifc_header_free_schema_identifiers(const char **identifiers);

IFCCAPICALL void ifc_unit_free(ifc_unit_t *unit);

IFCCAPICALL const char *ifc_unit_get_type(ifc_unit_t *unit);
IFCCAPICALL const char *ifc_unit_get_name(ifc_unit_t *unit);
IFCCAPICALL _Bool ifc_unit_has_SI_equivalent(ifc_unit_t *unit);
IFCCAPICALL double ifc_unit_get_SI_equivalent(ifc_unit_t *unit);

IFCCAPICALL void ifc_property_free(ifc_property_t *property);

IFCCAPICALL const char *ifc_property_get_name(ifc_property_t *property);
IFCCAPICALL const char *ifc_property_get_type(ifc_property_t *property);

// 获取不同类型的属性值
IFCCAPICALL _Bool ifc_property_is_null(ifc_property_t *property);
IFCCAPICALL _Bool ifc_property_is_int(ifc_property_t *property);
IFCCAPICALL _Bool ifc_property_is_bool(ifc_property_t *property);
IFCCAPICALL _Bool ifc_property_is_double(ifc_property_t *property);
IFCCAPICALL _Bool ifc_property_is_string(ifc_property_t *property);
IFCCAPICALL _Bool ifc_property_is_bitset(ifc_property_t *property);
IFCCAPICALL _Bool ifc_property_is_int_vector(ifc_property_t *property);
IFCCAPICALL _Bool ifc_property_is_double_vector(ifc_property_t *property);
IFCCAPICALL _Bool ifc_property_is_string_vector(ifc_property_t *property);
IFCCAPICALL _Bool ifc_property_is_bitset_vector(ifc_property_t *property);
IFCCAPICALL _Bool ifc_property_is_int_matrix(ifc_property_t *property);
IFCCAPICALL _Bool ifc_property_is_double_matrix(ifc_property_t *property);

IFCCAPICALL int ifc_property_get_int(ifc_property_t *property);
IFCCAPICALL _Bool ifc_property_get_bool(ifc_property_t *property);
IFCCAPICALL double ifc_property_get_double(ifc_property_t *property);
IFCCAPICALL const char *ifc_property_get_string(ifc_property_t *property);
IFCCAPICALL const unsigned char *
ifc_property_get_bitset(ifc_property_t *property, int *size);
IFCCAPICALL const int *ifc_property_get_int_vector(ifc_property_t *property,
                                                   int *count);
IFCCAPICALL const double *
ifc_property_get_double_vector(ifc_property_t *property, int *count);
IFCCAPICALL const char **
ifc_property_get_string_vector(ifc_property_t *property, int *count);
IFCCAPICALL unsigned char **
ifc_property_get_bitset_vector(ifc_property_t *property, int *count,
                               int **sizes);
IFCCAPICALL const int **ifc_property_get_int_matrix(ifc_property_t *property,
                                                    int *rows, int *cols);
IFCCAPICALL const double **
ifc_property_get_double_matrix(ifc_property_t *property, int *rows, int *cols);

// 向量/矩阵释放函数
IFCCAPICALL void ifc_property_free_vector(void *vec);
IFCCAPICALL void ifc_property_free_matrix(void **matrix, int rows);

IFCCAPICALL void ifc_property_set_free(ifc_property_set_t *ps);

IFCCAPICALL const char *ifc_property_set_get_id(ifc_property_set_t *ps);
IFCCAPICALL const char *ifc_property_set_get_name(ifc_property_set_t *ps);
IFCCAPICALL ifc_property_t **
ifc_property_set_get_properties(ifc_property_set_t *ps, int *count);
IFCCAPICALL void ifc_property_set_free_properties(ifc_property_t **properties);

IFCCAPICALL void ifc_quantity_free(ifc_quantity_t *quantity);

IFCCAPICALL const char *ifc_quantity_get_type(ifc_quantity_t *quantity);
IFCCAPICALL const char *ifc_quantity_get_name(ifc_quantity_t *quantity);
IFCCAPICALL double ifc_quantity_get_value(ifc_quantity_t *quantity);
IFCCAPICALL const char *ifc_quantity_get_unit(ifc_quantity_t *quantity);

IFCCAPICALL void ifc_element_quantity_free(ifc_element_quantity_t *eq);

IFCCAPICALL const char *ifc_element_quantity_get_id(ifc_element_quantity_t *eq);
IFCCAPICALL const char *
ifc_element_quantity_get_name(ifc_element_quantity_t *eq);
IFCCAPICALL ifc_quantity_t **
ifc_element_quantity_get_quantities(ifc_element_quantity_t *eq, int *count);
IFCCAPICALL void
ifc_element_quantity_free_quantities(ifc_quantity_t **quantities);

IFCCAPICALL void ifc_task_time_free(ifc_task_time_t *tt);

IFCCAPICALL const char *ifc_task_time_get_schedule_start(ifc_task_time_t *tt);
IFCCAPICALL const char *ifc_task_time_get_schedule_finish(ifc_task_time_t *tt);
IFCCAPICALL const char *ifc_task_time_get_actual_start(ifc_task_time_t *tt);
IFCCAPICALL const char *ifc_task_time_get_actual_finish(ifc_task_time_t *tt);
IFCCAPICALL const char *ifc_task_time_get_free_float(ifc_task_time_t *tt);
IFCCAPICALL const char *ifc_task_time_get_total_float(ifc_task_time_t *tt);
IFCCAPICALL _Bool ifc_task_time_is_critical(ifc_task_time_t *tt);

IFCCAPICALL void ifc_task_free(ifc_task_t *task);

// 基本属性
IFCCAPICALL const char *ifc_task_get_id(ifc_task_t *task);
IFCCAPICALL const char *ifc_task_get_name(ifc_task_t *task);
IFCCAPICALL const char *ifc_task_get_status(ifc_task_t *task);
IFCCAPICALL const char *ifc_task_get_description(ifc_task_t *task);
IFCCAPICALL const char *ifc_task_get_object_type(ifc_task_t *task);
IFCCAPICALL const char *ifc_task_get_work_method(ifc_task_t *task);
IFCCAPICALL int ifc_task_get_priority(ifc_task_t *task);
IFCCAPICALL _Bool ifc_task_is_milestone(ifc_task_t *task);

// 任务时间
IFCCAPICALL ifc_task_time_t *ifc_task_get_task_time(ifc_task_t *task);

// 列表属性
IFCCAPICALL const char **ifc_task_get_predecessors(ifc_task_t *task,
                                                   int *count);
IFCCAPICALL const char **ifc_task_get_successors(ifc_task_t *task, int *count);
IFCCAPICALL ifc_task_t **ifc_task_get_subtasks(ifc_task_t *task, int *count);

// 列表释放函数
IFCCAPICALL void ifc_task_free_string_list(const char **list);
IFCCAPICALL void ifc_task_free_subtasks(ifc_task_t **subtasks);

IFCCAPICALL void ifc_work_time_free(ifc_work_time_t *wt);

IFCCAPICALL const char *ifc_work_time_get_name(ifc_work_time_t *wt);
IFCCAPICALL const char *ifc_work_time_get_start_time(ifc_work_time_t *wt);
IFCCAPICALL const char *ifc_work_time_get_finish_time(ifc_work_time_t *wt);
IFCCAPICALL ifc_recurrence_pattern_t *
ifc_work_time_get_recurrence_pattern(ifc_work_time_t *wt);

IFCCAPICALL void ifc_work_calendar_free(ifc_work_calendar_t *wc);

IFCCAPICALL const char *ifc_work_calendar_get_id(ifc_work_calendar_t *wc);
IFCCAPICALL const char *ifc_work_calendar_get_name(ifc_work_calendar_t *wc);
IFCCAPICALL ifc_work_time_t **
ifc_work_calendar_get_working_times(ifc_work_calendar_t *wc, int *count);
IFCCAPICALL void
ifc_work_calendar_free_working_times(ifc_work_time_t **working_times);

IFCCAPICALL void ifc_work_schedule_free(ifc_work_schedule_t *ws);

IFCCAPICALL const char *ifc_work_schedule_get_id(ifc_work_schedule_t *ws);
IFCCAPICALL const char *ifc_work_schedule_get_name(ifc_work_schedule_t *ws);
IFCCAPICALL ifc_task_t **ifc_work_schedule_get_tasks(ifc_work_schedule_t *ws,
                                                     int *count);
IFCCAPICALL void ifc_work_schedule_free_tasks(ifc_task_t **tasks);

IFCCAPICALL const char *ifc_work_schedule_get_purpose(ifc_work_schedule_t *ws);
IFCCAPICALL const char *
ifc_work_schedule_get_start_time(ifc_work_schedule_t *ws);
IFCCAPICALL const char *
ifc_work_schedule_get_finish_time(ifc_work_schedule_t *ws);
IFCCAPICALL double ifc_work_schedule_get_duration(ifc_work_schedule_t *ws);
IFCCAPICALL double ifc_work_schedule_get_total_float(ifc_work_schedule_t *ws);
IFCCAPICALL const char **ifc_work_schedule_get_creators(ifc_work_schedule_t *ws,
                                                        int *count);
IFCCAPICALL void ifc_work_schedule_free_creators(const char **creators);

IFCCAPICALL void ifc_work_plan_free(ifc_work_plan_t *wp);

IFCCAPICALL const char *ifc_work_plan_get_id(ifc_work_plan_t *wp);
IFCCAPICALL const char *ifc_work_plan_get_name(ifc_work_plan_t *wp);
IFCCAPICALL const char **
ifc_work_plan_get_work_schedule_ids(ifc_work_plan_t *wp, int *count);
IFCCAPICALL void ifc_work_plan_free_work_schedule_ids(const char **ids);

IFCCAPICALL const char *ifc_work_plan_get_purpose(ifc_work_plan_t *wp);
IFCCAPICALL const char *ifc_work_plan_get_start_time(ifc_work_plan_t *wp);
IFCCAPICALL const char *ifc_work_plan_get_finish_time(ifc_work_plan_t *wp);
IFCCAPICALL double ifc_work_plan_get_duration(ifc_work_plan_t *wp);
IFCCAPICALL double ifc_work_plan_get_total_float(ifc_work_plan_t *wp);
IFCCAPICALL const char **ifc_work_plan_get_creators(ifc_work_plan_t *wp,
                                                    int *count);
IFCCAPICALL void ifc_work_plan_free_creators(const char **creators);

IFCCAPICALL void ifc_connection_free(ifc_connection_t *conn);

IFCCAPICALL const char *ifc_connection_get_id(ifc_connection_t *conn);
IFCCAPICALL const char *
ifc_connection_get_relating_element_id(ifc_connection_t *conn);
IFCCAPICALL const char *
ifc_connection_get_related_element_id(ifc_connection_t *conn);

IFCCAPICALL void ifc_type_object_free(ifc_type_object_t *obj);

IFCCAPICALL const char *ifc_type_object_get_id(ifc_type_object_t *obj);
IFCCAPICALL const char *ifc_type_object_get_name(ifc_type_object_t *obj);
IFCCAPICALL ifc_property_set_t **
ifc_type_object_get_property_sets(ifc_type_object_t *obj, int *count);
IFCCAPICALL void ifc_type_object_free_property_sets(ifc_property_set_t **psets);

IFCCAPICALL void ifc_layer_free(ifc_layer_t *layer);

IFCCAPICALL const char *ifc_layer_get_name(ifc_layer_t *layer);
IFCCAPICALL const char *ifc_layer_get_id(ifc_layer_t *layer);
IFCCAPICALL const char **ifc_layer_get_assigned_elements(ifc_layer_t *layer,
                                                         int *count);
IFCCAPICALL const char *ifc_layer_get_description(ifc_layer_t *layer);

IFCCAPICALL void ifc_layer_free_assigned_elements(const char **elements);

IFCCAPICALL void ifc_material_free(ifc_material_t *mtl);

IFCCAPICALL const char *ifc_material_get_id(ifc_material_t *mtl);
IFCCAPICALL const char *ifc_material_get_name(ifc_material_t *mtl);
IFCCAPICALL const char *ifc_material_get_description(ifc_material_t *mtl);
IFCCAPICALL const char *ifc_material_get_category(ifc_material_t *mtl);

IFCCAPICALL void ifc_group_free(ifc_group_t *group);

IFCCAPICALL const char *ifc_group_get_id(ifc_group_t *group);
IFCCAPICALL const char *ifc_group_get_name(ifc_group_t *group);
IFCCAPICALL const char **ifc_group_get_member_ids(ifc_group_t *group,
                                                  int *count);
IFCCAPICALL void ifc_group_free_member_ids(const char **member_ids);

IFCCAPICALL void ifc_data_free(ifc_data_t *data);

IFCCAPICALL ifc_header_t *ifc_data_get_header(ifc_data_t *data);
IFCCAPICALL ifc_unit_t **ifc_data_get_units(ifc_data_t *data, int *count);
IFCCAPICALL ifc_property_set_t **ifc_data_get_properties(ifc_data_t *data,
                                                         int *count);
IFCCAPICALL ifc_element_quantity_t **ifc_data_get_quantities(ifc_data_t *data,
                                                             int *count);
IFCCAPICALL ifc_work_schedule_t **ifc_data_get_work_schedules(ifc_data_t *data,
                                                              int *count);
IFCCAPICALL ifc_work_plan_t **ifc_data_get_work_plans(ifc_data_t *data,
                                                      int *count);
IFCCAPICALL ifc_work_calendar_t **ifc_data_get_calendars(ifc_data_t *data,
                                                         int *count);
IFCCAPICALL ifc_connection_t **ifc_data_get_connections(ifc_data_t *data,
                                                        int *count);
IFCCAPICALL ifc_type_object_t **ifc_data_get_types(ifc_data_t *data,
                                                   int *count);
IFCCAPICALL ifc_layer_t **ifc_data_get_layers(ifc_data_t *data, int *count);
IFCCAPICALL ifc_material_t **ifc_data_get_materials(ifc_data_t *data,
                                                    int *count);
IFCCAPICALL ifc_group_t **ifc_data_get_groups(ifc_data_t *data, int *count);

IFCCAPICALL ifc_rel_defines_by_type_t **ifc_data_get_rel_defines_by_types(ifc_data_t *data, int *count);

IFCCAPICALL ifc_rel_defines_by_properties_t **ifc_data_get_rel_defines_by_properties(ifc_data_t *data, int *count);

// IfcTimePeriod 相关函数
IFCCAPICALL const char *ifc_time_period_get_start_time(ifc_time_period_t *tp);
IFCCAPICALL const char *ifc_time_period_get_end_time(ifc_time_period_t *tp);

IFCCAPICALL void ifc_time_period_free(ifc_time_period_t *tp);

// IfcRecurrencePattern 相关函数
IFCCAPICALL int
ifc_recurrence_pattern_get_position(ifc_recurrence_pattern_t *rp);
IFCCAPICALL int
ifc_recurrence_pattern_get_interval(ifc_recurrence_pattern_t *rp);
IFCCAPICALL int
ifc_recurrence_pattern_get_occurrences(ifc_recurrence_pattern_t *rp);

IFCCAPICALL const double *
ifc_recurrence_pattern_get_day_components(ifc_recurrence_pattern_t *rp,
                                          int *count);
IFCCAPICALL const double *
ifc_recurrence_pattern_get_weekday_components(ifc_recurrence_pattern_t *rp,
                                              int *count);
IFCCAPICALL const double *
ifc_recurrence_pattern_get_month_components(ifc_recurrence_pattern_t *rp,
                                            int *count);
IFCCAPICALL ifc_time_period_t **
ifc_recurrence_pattern_get_time_periods(ifc_recurrence_pattern_t *rp,
                                        int *count);

IFCCAPICALL void ifc_recurrence_pattern_free(ifc_recurrence_pattern_t *rp);

// 列表释放函数
IFCCAPICALL void
ifc_recurrence_pattern_free_time_periods(ifc_time_period_t **periods);

// 列表释放函数
IFCCAPICALL void ifc_data_free_units(ifc_unit_t **units);
IFCCAPICALL void ifc_data_free_properties(ifc_property_set_t **properties);
IFCCAPICALL void ifc_data_free_quantities(ifc_element_quantity_t **quantities);
IFCCAPICALL void ifc_data_free_work_schedules(ifc_work_schedule_t **schedules);
IFCCAPICALL void ifc_data_free_work_plans(ifc_work_plan_t **plans);
IFCCAPICALL void ifc_data_free_calendars(ifc_work_calendar_t **calendars);
IFCCAPICALL void ifc_data_free_connections(ifc_connection_t **connections);
IFCCAPICALL void ifc_data_free_types(ifc_type_object_t **types);
IFCCAPICALL void ifc_data_free_layers(ifc_layer_t **layers);
IFCCAPICALL void ifc_data_free_materials(ifc_material_t **materials);
IFCCAPICALL void ifc_data_free_groups(ifc_group_t **groups);
IFCCAPICALL void ifc_data_free_rel_defines_by_types(ifc_rel_defines_by_type_t **rdts);
IFCCAPICALL void ifc_data_free_rel_defines_by_properties(ifc_rel_defines_by_properties_t **rdts);


IFCCAPICALL const char * ifc_rel_defines_by_type_get_id(ifc_rel_defines_by_type_t *rdt);
IFCCAPICALL const char * ifc_rel_defines_by_type_get_name(ifc_rel_defines_by_type_t *rdt);
IFCCAPICALL const char * ifc_rel_defines_by_type_get_desc(ifc_rel_defines_by_type_t *rdt);
IFCCAPICALL const char * ifc_rel_defines_by_type_get_type_obj_id(ifc_rel_defines_by_type_t *rdt);
IFCCAPICALL const char ** ifc_rel_defines_by_type_get_obj_ids(ifc_rel_defines_by_type_t *rdt, int *count);
IFCCAPICALL void ifc_rel_defines_by_type_free(ifc_rel_defines_by_type_t *rdt);
IFCCAPICALL void ifc_rel_defines_by_type_free_obj_ids(const char **ids);


IFCCAPICALL const char * ifc_rel_defines_by_properties_get_id(ifc_rel_defines_by_properties_t *rdt);
IFCCAPICALL const char * ifc_rel_defines_by_properties_get_name(ifc_rel_defines_by_properties_t *rdt);
IFCCAPICALL const char * ifc_rel_defines_by_properties_get_desc(ifc_rel_defines_by_properties_t *rdt);
IFCCAPICALL const char ** ifc_rel_defines_by_properties_get_obj_ids(ifc_rel_defines_by_properties_t *rdt, int *count);
IFCCAPICALL const char* ifc_rel_defines_by_properties_get_propertyset_id(ifc_rel_defines_by_properties_t *rdt);

IFCCAPICALL void ifc_rel_defines_by_properties_free(ifc_rel_defines_by_properties_t *rdt);
IFCCAPICALL void ifc_rel_defines_by_properties_free_obj_ids(const char **ids);
 


#ifdef __cplusplus
}
#endif

#endif