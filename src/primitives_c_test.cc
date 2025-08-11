#include "primitives_c_api.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 辅助函数：创建点
pnt3d_t create_point(double x, double y, double z) {
  pnt3d_t p = {x, y, z};
  return p;
}

// 辅助函数：创建多边形剖面
shape_profile_t create_polygon_profile(pnt3d_t *points, int count) {
  shape_profile_t profile;
  profile.type_ = PROFILE_TYPE_POLYGON;

  // 分配内存并复制点
  profile.polygon.edges = (pnt3d_t *)malloc(sizeof(pnt3d_t) * count);
  memcpy(profile.polygon.edges, points, sizeof(pnt3d_t) * count);
  profile.polygon.edgeCount = count;

  // 无内孔
  profile.polygon.inners = NULL;
  profile.polygon.innerCounts = NULL;
  profile.polygon.innerArrayCount = 0;

  return profile;
}

void test_multi_segment_pipe_with_split_distances() {
  // 创建路径点 - 第一段
  pnt3d_t *wire1 = (pnt3d_t *)malloc(sizeof(pnt3d_t) * 2);
  wire1[0] = create_point(0, 0, 0);
  wire1[1] =
      create_point(13.363751136232167, -26.227833716198802, 40.422308564186096);

  // 创建路径点 - 第二段
  pnt3d_t *wire2 = (pnt3d_t *)malloc(sizeof(pnt3d_t) * 2);
  wire2[0] =
      create_point(13.363751136232167, -26.227833716198802, 40.422308564186096);
  wire2[1] =
      create_point(46.29231750732288, -90.69991450663656, 108.94551491551101);

  // 设置线段类型
  segment_type_t *segment_types =
      (segment_type_t *)malloc(sizeof(segment_type_t) * 2);
  segment_types[0] = SEGMENT_TYPE_LINE;
  segment_types[1] = SEGMENT_TYPE_LINE;

  // 创建外部剖面点数组
  // 外部剖面1 (12个点)
  pnt3d_t edges1[12] = {
      create_point(-3.171, 2.538, 0), create_point(-3.136, 3.954, 0),
      create_point(-2.498, 5.219, 0), create_point(-1.382, 6.09, 0),
      create_point(0, 6.4, 0),        create_point(1.382, 6.09, 0),
      create_point(2.498, 5.219, 0),  create_point(3.136, 3.954, 0),
      create_point(3.171, 2.538, 0),  create_point(2.5, 0, 0),
      create_point(-2.5, 0, 0),       create_point(-3.171, 2.538, 0)};

  // 外部剖面2 (10个点)
  pnt3d_t edges2[10] = {
      create_point(-3.4, 3.25, 0),    create_point(-2.773, 4.717, 0),
      create_point(-1.553, 5.746, 0), create_point(0, 6.115, 0),
      create_point(1.553, 5.746, 0),  create_point(2.773, 4.717, 0),
      create_point(3.4, 3.25, 0),     create_point(3.4, 0, 0),
      create_point(-3.4, 0, 0),       create_point(-3.4, 3.25, 0)};

  // 创建内部剖面点数组
  // 内部剖面1 (12个点 + 闭合点)
  pnt3d_t edges3[12] = {
      create_point(-3.078273455639578, 2.575440459011272, 0),
      create_point(-3.036354153205542, 3.945591360596666, 0),
      create_point(-2.415107425541498, 5.163064134049417, 0),
      create_point(-1.339465963909452, 5.999496653245043, 0),
      create_point(-0.00978236558095332, 6.3004796235756695, 0),
      create_point(1.3250857438602934, 6.007776113883715, 0),
      create_point(2.410219147892808, 5.171098830877157, 0),
      create_point(3.0362530020384777, 3.946891104328797, 0),
      create_point(3.0763705290048873, 2.57033053075941, 0),
      create_point(2.4402700090676666, 0.08020179663338835, 0),
      create_point(-2.4484020179459174, 0.08566007382641323, 0),
      create_point(-3.078273455639578, 2.575440459011272, 0) // 闭合多边形
  };

  // 内部剖面2 (10个点)
  pnt3d_t edges4[10] = {
      create_point(-3.3009689384399516, 3.2638870027828157, 0),
      create_point(-2.681019727080062, 4.6777618885065335, 0),
      create_point(-1.5023855429647655, 5.659755134999072, 0),
      create_point(-0.013823869618346543, 6.0159601058725585, 0),
      create_point(1.4854596950468153, 5.672255120809437, 0),
      create_point(2.678133803605064, 4.68537082388747, 0),
      create_point(3.30065175118932, 3.2613984849103375, 0),
      create_point(3.328711291934881, 0.07012788391507485, 0),
      create_point(-3.336054557835377, 0.07688290074113246, 0),
      create_point(-3.3009689384399516, 3.2638870027828157, 0)};

  // 创建外部剖面
  shape_profile_t profile1 = create_polygon_profile(edges1, 12);
  shape_profile_t profile2 = create_polygon_profile(edges2, 10);

  // 创建内部剖面
  shape_profile_t inner_profile1 = create_polygon_profile(edges3, 12);
  shape_profile_t inner_profile2 = create_polygon_profile(edges4, 10);

  // 创建剖面数组
  shape_profile_t *profiles =
      (shape_profile_t *)malloc(sizeof(shape_profile_t) * 2);
  profiles[0] = profile1;
  profiles[1] = profile2;

  // 创建内部剖面数组
  shape_profile_t *inner_profiles =
      (shape_profile_t *)malloc(sizeof(shape_profile_t) * 2);
  inner_profiles[0] = inner_profile1;
  inner_profiles[1] = inner_profile2;

  // 创建路径计数数组
  int *wire_counts = (int *)malloc(sizeof(int) * 2);
  wire_counts[0] = 2; // 第一段有2个点
  wire_counts[1] = 2; // 第二段有2个点

  // 创建路径数组
  pnt3d_t **wires = (pnt3d_t **)malloc(sizeof(pnt3d_t *) * 2);
  wires[0] = wire1;
  wires[1] = wire2;

  // 设置上方向
  dir3d_t up_dir = {.x = -0.37127704827582503,
                    .y = 0.7201908387390975,
                    .z = 0.586070396129907};

  int inner_profile_count = 2;

  // 初始化参数结构体
  multi_segment_pipe_params_t params = {.wires = wires,
                                        .wire_counts = wire_counts,
                                        .wire_array_count = 2,
                                        .profiles = profiles,
                                        .profile_count = 2,
                                        .inner_profiles = &inner_profiles,
                                        .inner_profile_counts = &inner_profile_count,
                                        .segment_types = segment_types,
                                        .segment_type_count = 2,
                                        .transition_mode =
                                            TRANSITION_TRANSFORMED,
                                        .up_dir = &up_dir};

  // 创建带分割距离的多段管道
  topo_shape_t *shape =
      create_multi_segment_pipe_with_split_distances(params, 2.0, 5.0);

  if (shape != NULL) {
    printf("Successfully created multi-segment pipe with split distances\n");
    // 这里可以添加导出形状的代码
  } else {
    printf("Failed to create multi-segment pipe with split distances\n");
  }

  // 清理内存
  free(wire1);
  free(wire2);
  free(segment_types);

  // 清理剖面内存
  free(profile1.polygon.edges);
  free(profile2.polygon.edges);
  free(inner_profile1.polygon.edges);
  free(inner_profile2.polygon.edges);

  // 清理剖面数组
  free(profiles);
  free(inner_profiles);

  // 清理其他数组
  free(wire_counts);
  free(wires);
}

int main() {
  test_multi_segment_pipe_with_split_distances();
  return 0;
}
