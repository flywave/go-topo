#include "bounding_pipe.hh"

#include <BRepAdaptor_CompCurve.hxx>
#include <BRepAdaptor_Curve.hxx>
#include <BRepAdaptor_Surface.hxx>
#include <BRepAlgoAPI_Cut.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepCheck_Analyzer.hxx>
#include <BRepAlgoAPI_Section.hxx>
#include <BRepBndLib.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_MakeVertex.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_Sewing.hxx>
#include <BRepExtrema_DistShapeShape.hxx>
#include <BRepGProp.hxx>
#include <BRepLib.hxx>
#include <BRepMesh_IncrementalMesh.hxx>
#include <BRepOffsetAPI_MakePipeShell.hxx>
#include <BRepPrimAPI_MakePrism.hxx>
#include <BRepTools.hxx>
#include <BRep_Tool.hxx>
#include <GCPnts_AbscissaPoint.hxx>
#include <GCPnts_UniformAbscissa.hxx>
#include <GProp_GProps.hxx>
#include <GeomAPI_ExtremaCurveCurve.hxx>
#include <GeomAPI_Interpolate.hxx>
#include <GeomAPI_PointsToBSpline.hxx>
#include <GeomAPI_ProjectPointOnCurve.hxx>
#include <GeomAPI_ProjectPointOnSurf.hxx>
#include <GeomAdaptor_Curve.hxx>
#include <GeomConvert_ApproxCurve.hxx>
#include <GeomLProp_CLProps.hxx>
#include <Geom_BSplineCurve.hxx>
#include <Geom_Circle.hxx>
#include <Geom_Curve.hxx>
#include <Geom_Line.hxx>
#include <Geom_Plane.hxx>
#include <Geom_RectangularTrimmedSurface.hxx>
#include <Geom_Surface.hxx>
#include <Geom_TrimmedCurve.hxx>
#include <Poly_Triangulation.hxx>
#include <Precision.hxx>
#include <Standard_Failure.hxx>
#include <ShapeAnalysis_Curve.hxx>
#include <ShapeAnalysis_FreeBounds.hxx>
#include <ShapeAnalysis_Surface.hxx>
#include <ShapeFix_Shape.hxx>
#include <TColgp_Array1OfPnt.hxx>
#include <TopExp.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Shell.hxx>
#include <TopoDS_Vertex.hxx>
#include <TopoDS_Wire.hxx>
#include <algorithm>
#include <gce_MakeLin.hxx>
#include <gp_Ax1.hxx>
#include <gp_Circ.hxx>
#include <gp_Dir.hxx>
#include <gp_Pln.hxx>
#include <gp_Vec.hxx>
#include <gp_XYZ.hxx>
#include <map>
#include <tuple>
#include <math_Jacobi.hxx>
#include <math_Matrix.hxx>

namespace flywave {
namespace topo {

TopoDS_Wire clip_wire_between_distances_helper(const TopoDS_Wire &wire_path,
                                               double start_distance,
                                               double end_distance) {
  if (start_distance < 0 || end_distance < 0 ||
      start_distance >= end_distance) {
    throw std::invalid_argument("Invalid distance range");
  }

  // 计算路径总长度
  GProp_GProps props;
  BRepGProp::LinearProperties(wire_path, props);
  double totalLength = props.Mass();

  if (end_distance > totalLength) {
    end_distance = totalLength;
  }

  if (start_distance >= totalLength) {
    throw std::invalid_argument("start_distance exceeds total wire length");
  }
  if (end_distance >= totalLength) {
    end_distance = totalLength;
  }

  BRepBuilderAPI_MakeWire wireBuilder;
  double accumulatedLength = 0;
  bool inRange = false;

  TopExp_Explorer edgeExplorer(wire_path, TopAbs_EDGE);
  for (; edgeExplorer.More(); edgeExplorer.Next()) {
    const TopoDS_Edge &edge = TopoDS::Edge(edgeExplorer.Current());

    // 获取原始边的定位和方向
    const TopLoc_Location &edgeLoc = edge.Location();
    TopAbs_Orientation edgeOrientation = edge.Orientation();

    // 计算当前边的长度
    GProp_GProps edgeProps;
    BRepGProp::LinearProperties(edge, edgeProps);
    double edgeLength = edgeProps.Mass();

    double edgeStart = accumulatedLength;
    double edgeEnd = accumulatedLength + edgeLength;

    // 检查边是否在区间内
    if (edgeEnd <= start_distance) {
      accumulatedLength += edgeLength;
      continue;
    }

    if (edgeStart >= end_distance) {
      break;
    }

    // 获取边的几何曲线
    BRepAdaptor_Curve curveAdaptor(edge);
    Handle(Geom_Curve) curve = curveAdaptor.Curve().Curve();

    // 计算截取参数: 参数化未必与弧长成比例 (拟合 BSpline 尤甚),
    // 必须按弧长精确求参, 线性插值参数会把切点算偏
    double param1 = curveAdaptor.FirstParameter();
    double param2 = curveAdaptor.LastParameter();

    if (edgeStart < start_distance && edgeEnd > start_distance) {
      GCPnts_AbscissaPoint splitPoint(curveAdaptor, start_distance - edgeStart,
                                      curveAdaptor.FirstParameter());
      if (splitPoint.IsDone()) {
        param1 = splitPoint.Parameter();
      }
    }

    if (edgeStart < end_distance && edgeEnd > end_distance) {
      GCPnts_AbscissaPoint splitPoint(curveAdaptor, end_distance - edgeStart,
                                      curveAdaptor.FirstParameter());
      if (splitPoint.IsDone()) {
        param2 = splitPoint.Parameter();
      }
    }

    if (param2 <= param1) {
      accumulatedLength += edgeLength;
      continue;
    }

    // 创建截取后的曲线
    Handle(Geom_TrimmedCurve) trimmedCurve =
        new Geom_TrimmedCurve(curve, param1, param2);

    BRepBuilderAPI_MakeEdge makeEdge(trimmedCurve);
    if (!makeEdge.IsDone())
      continue;

    TopoDS_Edge newEdge = makeEdge.Edge();
    newEdge.Location(edgeLoc);
    newEdge.Orientation(edgeOrientation);

    wireBuilder.Add(newEdge);

    accumulatedLength += edgeLength;
  }

  if (!wireBuilder.IsDone()) {
    throw std::runtime_error("Failed to create sub wire");
  }

  return wireBuilder.Wire();
}

// 新增方法：从形状中提取所有三角网格顶点
std::vector<gp_Pnt> extract_shape_points(const TopoDS_Shape &shape) {
  // 1. 网格化形状（如果还不是离散形式）。
  // 先清除已有网格: 缓存状态随调用历史变化会破坏结果确定性
  BRepTools::Clean(shape);
  BRepMesh_IncrementalMesh mesher(shape, 0.1, false, 0.5, false);
  mesher.Perform();

  // 2. 提取所有顶点
  std::vector<gp_Pnt> points;
  TopExp_Explorer faceExplorer(shape, TopAbs_FACE);
  for (; faceExplorer.More(); faceExplorer.Next()) {
    TopoDS_Face face = TopoDS::Face(faceExplorer.Current());
    TopLoc_Location loc;
    Handle(Poly_Triangulation) triangulation =
        BRep_Tool::Triangulation(face, loc);
    if (!triangulation.IsNull()) {
      // 节点在面局部坐标系中, 必须变换到全局 (STEP 导入常带 Location)
      const gp_Trsf &trsf = loc.Transformation();
      const Poly_ArrayOfNodes &nodes = triangulation->InternalNodes();
      for (int i = nodes.Lower(); i <= nodes.Upper(); ++i) {
        points.push_back(nodes.Value(i).Transformed(trsf));
      }
    }
  }
  return points;
}

// 添加Douglas-Peucker算法实现
std::vector<gp_Pnt> douglas_peucker(const std::vector<gp_Pnt> &points,
                                    double epsilon) {
  if (points.size() <= 2)
    return points;

  // 首尾重合时无法定义基线, 直接收缩为两点
  gp_Vec span(points.front(), points.back());
  if (span.Magnitude() < Precision::Confusion()) {
    return {points.front(), points.back()};
  }

  // 找到离首尾线段最远的点
  double maxDistance = 0.0;
  size_t index = 0;
  gp_Lin line(points.front(), span);

  for (size_t i = 1; i < points.size() - 1; i++) {
    double d = line.Distance(points[i]);
    if (d > maxDistance) {
      maxDistance = d;
      index = i;
    }
  }

  if (maxDistance <= epsilon) {
    return {points.front(), points.back()};
  }

  std::vector<gp_Pnt> firstPart(points.begin(), points.begin() + index + 1);
  std::vector<gp_Pnt> firstResult = douglas_peucker(firstPart, epsilon);

  std::vector<gp_Pnt> secondPart(points.begin() + index, points.end());
  std::vector<gp_Pnt> secondResult = douglas_peucker(secondPart, epsilon);

  // 合并结果(避免重复点)
  firstResult.pop_back();
  firstResult.insert(firstResult.end(), secondResult.begin(),
                     secondResult.end());
  return firstResult;
}

// ---- 端盖截面扫掠中心线提取 ----
// 适用: 有两个相对端盖的类管/柱/异形拉伸体 (直管、弯管、螺旋管、
// 渐变截面、任意断面轮廓的拉伸体)。从端盖质心与法向出发, 垂直于局部
// 行进方向逐层截面料并跟随截面质心前进。为提高密集线圈等复杂结构上
// 的覆盖率, 从两端各扫掠一次再拼接。无端盖结构 (环/球/分支体) 由
// 调用方回退到 PCA 截面拟合。已知边界: 螺距接近管径的密集线圈、
// 分叉结构, 自动提取可能中途终止 (由双端合并弥补大部分缺口)。

namespace {

struct planar_cap_info {
  gp_Pnt center;
  gp_Dir normal;
  double area;
};

struct mesh_triangle {
  gp_Pnt a, b, c;
};

} // namespace

static void collect_mesh_triangles(const TopoDS_Shape &shape,
                                   double deflection,
                                   std::vector<mesh_triangle> &tris) {
  // 清除已存三角网格再网格化: BRepMesh 会跳过已有更细网格的面,
  // 缓存状态随调用历史变化, 导致提取结果不确定
  BRepTools::Clean(shape);
  // 串行网格化: 并行模式三角剖分顺序不定, 提取结果随之漂移
  BRepMesh_IncrementalMesh mesher(shape, deflection, false, 0.5, false);
  mesher.Perform();
  for (TopExp_Explorer exp(shape, TopAbs_FACE); exp.More(); exp.Next()) {
    TopoDS_Face face = TopoDS::Face(exp.Current());
    TopLoc_Location loc;
    Handle(Poly_Triangulation) tri = BRep_Tool::Triangulation(face, loc);
    if (tri.IsNull()) {
      continue;
    }
    const gp_Trsf &trsf = loc.Transformation();
    const Poly_ArrayOfNodes &nodes = tri->InternalNodes();
    std::vector<gp_Pnt> pts(static_cast<size_t>(nodes.Length()) + 1);
    for (int i = nodes.Lower(); i <= nodes.Upper(); ++i) {
      pts[i - nodes.Lower() + 1] = nodes.Value(i).Transformed(trsf);
    }
    const Poly_Array1OfTriangle &triangles = tri->InternalTriangles();
    const int base = 1 - nodes.Lower();
    for (int t = triangles.Lower(); t <= triangles.Upper(); ++t) {
      int a, b, c;
      triangles.Value(t).Get(a, b, c);
      tris.push_back({pts[a + base], pts[b + base], pts[c + base]});
    }
  }
}

static bool pick_end_caps(const TopoDS_Shape &shape, planar_cap_info &capA,
                          planar_cap_info &capB) {
  std::vector<planar_cap_info> caps;
  for (TopExp_Explorer exp(shape, TopAbs_FACE); exp.More(); exp.Next()) {
    TopoDS_Face face = TopoDS::Face(exp.Current());
    BRepAdaptor_Surface surf(face);
    if (surf.GetType() != GeomAbs_Plane) {
      continue;
    }
    GProp_GProps props;
    BRepGProp::SurfaceProperties(face, props);
    const double area = props.Mass();
    if (area <= Precision::Confusion()) {
      continue;
    }
    caps.push_back(
        {props.CentreOfMass(), surf.Plane().Axis().Direction(), area});
  }
  if (caps.size() < 2) {
    return false;
  }
  // 端盖对 = 质心相距最远的一对平面面 (管/柱体的两端)
  double best = 0.0;
  size_t bi = 0, bj = 1;
  for (size_t i = 0; i < caps.size(); ++i) {
    for (size_t j = i + 1; j < caps.size(); ++j) {
      const double d = caps[i].center.Distance(caps[j].center);
      if (d > best) {
        best = d;
        bi = i;
        bj = j;
      }
    }
  }
  capA = caps[bi];
  capB = caps[bj];
  return best > Precision::Confusion();
}

// 轨迹收尾: 至少 4 个中心点才值得拟合; 2 轮 3 点滑动平均抑制网格噪声摆动
static Handle(Geom_Curve)
    finish_trace(const std::vector<gp_Pnt> &centers) {
  if (centers.size() < 4) {
    return nullptr;
  }
  std::vector<gp_Pnt> smoothed = centers;
  for (int pass = 0; pass < 2; ++pass) {
    std::vector<gp_Pnt> next;
    next.push_back(smoothed.front());
    for (size_t i = 1; i + 1 < smoothed.size(); ++i) {
      next.push_back(gp_Pnt((smoothed[i - 1].XYZ() + smoothed[i].XYZ() +
                             smoothed[i + 1].XYZ()) /
                            3.0));
    }
    next.push_back(smoothed.back());
    smoothed.swap(next);
  }
  // 振荡安全网: 插值样条在噪声点列上可能大幅过冲,
  // 曲线长度显著超过中心点折线长度时放弃扫掠结果 (调用方回退 PCA)
  double polyLen = 0.0;
  for (size_t i = 1; i < smoothed.size(); ++i) {
    polyLen += smoothed[i - 1].Distance(smoothed[i]);
  }
  Handle(Geom_Curve) curve = centerline_to_curve(smoothed);
  if (!curve.IsNull()) {
    const double curveLen =
        GCPnts_AbscissaPoint::Length(GeomAdaptor_Curve(curve));
    if (curveLen > 2.5 * std::max(polyLen, 1e-9)) {
      return nullptr;
    }
  }
  return curve;
}

// 从 startCap 沿材料扫掠中心点列 (单向)。判定规则:
//   - 截面环取距预测点最近的连续簇 (相邻结构段落由带限排除);
//   - 环心/环半径相对环心度量, 防止正反馈膨胀;
//   - 前进守卫失败时减半步长重试, 连续失败终止 (由另一端补扫)。
static std::vector<gp_Pnt>
trace_centers_from(const std::vector<mesh_triangle> &tris,
                   const planar_cap_info &startCap, double bboxDiag,
                   double capDist, double deflection) {
  const double kPi = 3.14159265358979323846;
  gp_XYZ dir = startCap.normal.XYZ();
  // 初始截面半径: 实心端盖用面积反推; 圆环状端盖 (面积法高估) 用
  // 端盖间距的 15% 封顶, 两者取小
  const double areaR = std::sqrt(startCap.area / kPi);
  double localR = std::max(std::min(areaR, 0.15 * capDist), bboxDiag * 0.01);
  const double localRMax = 0.35 * bboxDiag;

  // 初始方向: 由端盖邻域内材料的分布决定指向。
  // 必须只统计端盖邻域: 螺旋结构中远端材料在法向两侧几乎对称,
  // 全局统计会选反方向导致扫掠跑飞。
  const double probeBand = localR * 3.0;
  int posCount = 0, negCount = 0;
  for (const auto &t : tris) {
    const gp_Pnt mid((t.a.XYZ() + t.b.XYZ() + t.c.XYZ()) / 3.0);
    if (mid.Distance(startCap.center) > probeBand) {
      continue;
    }
    const double d = dir.Dot(mid.XYZ() - startCap.center.XYZ());
    if (d > 0) {
      ++posCount;
    } else if (d < 0) {
      ++negCount;
    }
  }
  if (posCount < negCount) {
    dir.Reverse();
  }

  static const bool traceDbg = getenv("TOPO_TRACE_DEBUG") != nullptr;
  std::vector<gp_Pnt> centers;
  centers.push_back(startCap.center);
  gp_Pnt prev = startCap.center;
  double traced = 0.0;
  int guardFailures = 0;
  double stepScale = 1.0;

  for (int step = 0; step < 900; ++step) {
    // 同一位置的尝试序列: 1x → 2x → 4x 步长 (加倍跨网格间隙)
    gp_Pnt c(0, 0, 0);
    double rr = 0.0;
    bool found = false;
    for (int attempt = 0; attempt < 3 && !found; ++attempt) {
      const double len = 0.7 * localR * stepScale * (1 << attempt);
      const gp_Pnt pred = prev.XYZ() + dir * len;
      const double h = dir.Dot(pred.XYZ());
      const double band = 1.6 * localR;
      // 收集平面上的候选段, 只保留距预测点最近的连续簇,
      // 排除同平面切到的远端其他段落 (螺旋相邻圈等)
      std::vector<gp_Pnt> cand;
      for (const auto &t : tris) {
        const double d0 = dir.Dot(t.a.XYZ()) - h;
        const double d1 = dir.Dot(t.b.XYZ()) - h;
        const double d2 = dir.Dot(t.c.XYZ()) - h;
        if ((d0 > 0 && d1 > 0 && d2 > 0) || (d0 < 0 && d1 < 0 && d2 < 0)) {
          continue;
        }
        gp_Pnt ip[2];
        int ipc = 0;
        const gp_Pnt *v[3] = {&t.a, &t.b, &t.c};
        const double dv[3] = {d0, d1, d2};
        for (int e = 0; e < 3 && ipc < 2; ++e) {
          const int i1 = e, i2 = (e + 1) % 3;
          if ((dv[i1] > 0 && dv[i2] < 0) || (dv[i1] < 0 && dv[i2] > 0)) {
            const double tt = dv[i1] / (dv[i1] - dv[i2]);
            ip[ipc++] = gp_Pnt(v[i1]->XYZ() +
                               (v[i2]->XYZ() - v[i1]->XYZ()) * tt);
          }
        }
        if (ipc < 2) {
          continue;
        }
        const gp_Pnt mid((ip[0].XYZ() + ip[1].XYZ()) * 0.5);
        if (mid.Distance(pred) <= band) {
          cand.push_back(ip[0]);
          cand.push_back(ip[1]);
        }
      }
      if (cand.size() < 2) {
        continue;
      }
      // 最近簇: 以最近点为基准, 只纳入其邻域内的候选
      double dmin = DBL_MAX;
      for (const auto &p : cand) {
        dmin = std::min(dmin, p.Distance(pred));
      }
      const double clusterBand = std::max(1.2 * localR, dmin + 0.8 * localR);
      std::vector<gp_Pnt> ring;
      for (const auto &p : cand) {
        if (p.Distance(pred) <= clusterBand) {
          ring.push_back(p);
        }
      }
      if (ring.size() < 2) {
        continue;
      }
      // 环心与环半径相对环心度量 (相对预测点度量会正反馈膨胀)
      gp_XYZ rsum(0, 0, 0);
      for (const auto &p : ring) {
        rsum += p.XYZ();
      }
      c = gp_Pnt(rsum / static_cast<double>(ring.size()));
      for (const auto &p : ring) {
        rr = std::max(rr, p.Distance(c));
      }
      found = true;
    }

    if (!found) {
      if (traceDbg) {
        fprintf(stderr, "[trace] step=%d NO RING at (%.1f,%.1f,%.1f) traced=%.1f localR=%.2f scale=%.3f\n",
                step, prev.X(), prev.Y(), prev.Z(), traced, localR, stepScale);
      }
      break;
    }

    const gp_XYZ move = c.XYZ() - prev.XYZ();
    const double moveLen = move.Modulus();
    if (moveLen <= Precision::Confusion()) {
      break; // 环心未前进: 已到达端部, 退化重试只会原地累积噪声
    }
    // 前进守卫: 新中心必须沿当前方向前方且距离合理。
    // 失败则缩小步长重试 (密集线圈上整步预测会切到相邻圈), 连续 3 次
    // 才终止
    if (moveLen > 3.0 * localR || move.Dot(dir) <= 0) {
      ++guardFailures;
      if (guardFailures >= 3) {
        break;
      }
      stepScale *= 0.5;
      continue;
    }
    guardFailures = 0;
    stepScale = 1.0;
    if (traceDbg && step % 25 == 0) {
      fprintf(stderr, "[trace] step=%d c=(%.1f,%.1f,%.1f) move=%.2f localR=%.2f traced=%.1f\n",
              step, c.X(), c.Y(), c.Z(), moveLen, localR, traced);
    }
    centers.push_back(c);
    if (moveLen <= Precision::Confusion()) {
      break;
    }
    traced += moveLen;
    // 多圈线圈的弧长可达包围盒对角线的 10 倍以上, 上限须足够宽
    if (traced > 12.0 * bboxDiag) {
      break;
    }
    dir = move;
    dir.Normalize();
    // 平滑更新局部截面半径 (限幅防突变; 收缩可较快以进入渐细段)
    if (rr > localR * 0.3 && rr < localR * 2.0) {
      localR = std::min(0.5 * localR + 0.5 * rr, localRMax);
    }
    prev = c;
  }
  return centers;
}

static Handle(Geom_Curve)
    trace_centerline_by_section_sweep(const TopoDS_Shape &shape,
                                      const planar_cap_info &capA,
                                      const planar_cap_info &capB,
                                      double bboxDiag, double capDist) {
  const double deflection = std::max(bboxDiag * 0.002, 1e-4);
  std::vector<mesh_triangle> tris;
  collect_mesh_triangles(shape, deflection, tris);
  if (tris.empty()) {
    return nullptr;
  }

  // 双端扫掠: 复杂结构 (密集线圈) 上单端扫掠可能在困惑区提前终止,
  // 从两端各扫一次再拼接, 缺口只剩中间一小段由样条桥接。
  static const bool traceDbg = getenv("TOPO_TRACE_DEBUG") != nullptr;
  // A 已到达 capB 时 B 的结果完全不参与 (避免反向重复路径)。
  std::vector<gp_Pnt> centersA =
      trace_centers_from(tris, capA, bboxDiag, capDist, deflection);
  std::vector<gp_Pnt> merged = centersA;
  const double trimBand = std::max(bboxDiag * 0.02, 0.2 * capDist);
  if (merged.back().Distance(capB.center) > trimBand) {
    std::vector<gp_Pnt> centersBr =
        trace_centers_from(tris, capB, bboxDiag, capDist, deflection);
    if (centersBr.size() >= 2) {
      // B 从 capB 起扫, 反转后序列头部为其深入端。
      // 逐点跳过与 A 重叠的部分 (空间哈希), 其余按序拼接
      std::vector<gp_Pnt> rb(centersBr.rbegin(), centersBr.rend());
      const double cell = std::max(trimBand, 1e-9);
      auto keyOf = [&](const gp_Pnt &p) {
        return std::make_tuple(lround(p.X() / cell), lround(p.Y() / cell),
                               lround(p.Z() / cell));
      };
      std::map<std::tuple<long, long, long>, std::vector<gp_Pnt>> aHash;
      for (const auto &p : merged) {
        aHash[keyOf(p)].push_back(p);
      }
      auto nearA = [&](const gp_Pnt &p) {
        const auto key = keyOf(p);
        const long hx = std::get<0>(key), hy = std::get<1>(key),
                   hz = std::get<2>(key);
        for (long dx = -1; dx <= 1; ++dx) {
          for (long dy = -1; dy <= 1; ++dy) {
            for (long dz = -1; dz <= 1; ++dz) {
              auto it = aHash.find(std::make_tuple(hx + dx, hy + dy, hz + dz));
              if (it == aHash.end()) {
                continue;
              }
              for (const auto &q : it->second) {
                if (q.Distance(p) <= trimBand) {
                  return true;
                }
              }
            }
          }
        }
        return false;
      };
      for (const auto &p : rb) {
        if (nearA(p)) {
          continue;
        }
        merged.push_back(p);
        aHash[keyOf(p)].push_back(p);
      }
    }
  }
  // 端锚定校验: 可信的扫掠轨迹必须终止于终点端盖附近
  // (端盖误选/中途终止过远时放弃扫掠, 由调用方回退 PCA 路径)
  if (merged.back().Distance(capB.center) > 0.5 * capDist) {
    return nullptr;
  }
  return finish_trace(merged);
}

Handle(Geom_Curve)
    fit_centerline_from_shape(const TopoDS_Shape &shape, int numSamples,
                              double smoothingFactor) {
  // 1. 提取形状点
  std::vector<gp_Pnt> points = extract_shape_points(shape);
  if (points.empty())
    return nullptr;

  // 2. 计算包围盒和特征长度
  Bnd_Box bbox;
  for (const auto &p : points)
    bbox.Add(p);

  double xMin, yMin, zMin, xMax, yMax, zMax;
  bbox.Get(xMin, yMin, zMin, xMax, yMax, zMax);
  const double bboxDiag =
      sqrt(pow(xMax - xMin, 2) + pow(yMax - yMin, 2) + pow(zMax - zMin, 2));
  const double avgSpacing = bboxDiag / sqrt(points.size());

  // 2.5 优先端盖截面扫掠: 对直管/弯管/螺旋管/异形拉伸体都能跟随真实
  // 行进方向 (PCA 截面法在螺旋线/大弯曲结构上会因一平面切多段而失效)。
  // 无端盖结构 (环/球/分支体) 落回下方 PCA 路径。
  {
    // 仅实体参与端盖扫掠: 开放壳体 (如线框棱柱) 没有真实端面,
    // 平面面对候选会误判为端盖
    bool hasSolid = false;
    for (TopExp_Explorer solidExplorer(shape, TopAbs_SOLID);
         solidExplorer.More(); solidExplorer.Next()) {
      hasSolid = true;
      break;
    }
    planar_cap_info capA, capB;
    if (hasSolid && pick_end_caps(shape, capA, capB)) {
      Handle(Geom_Curve) traced = trace_centerline_by_section_sweep(
          shape, capA, capB, bboxDiag, capA.center.Distance(capB.center));
      if (!traced.IsNull()) {
        return traced;
      }
      // 实体带端盖但扫掠失败: 该形态对 PCA 截面法同样致命
      // (螺旋/弯管), 返回空让上层走手工编辑兜底, 不输出失真轴线
      return nullptr;
    }
  }

  // 3. 改进PCA - 修正投影范围计算
  gp_XYZ centroid(0, 0, 0);
  for (const auto &p : points)
    centroid += p.XYZ();
  centroid /= points.size();

  math_Matrix cov(1, 3, 1, 3, 0.0);
  for (const auto &p : points) {
    gp_XYZ diff = p.XYZ() - centroid;
    for (int i = 1; i <= 3; ++i)
      for (int j = 1; j <= 3; ++j)
        cov(i, j) += diff.Coord(i) * diff.Coord(j);
  }

  math_Jacobi jacobi(cov);
  math_Vector eigenValues = jacobi.Values();
  math_Matrix eigenVectors = jacobi.Vectors();

  // 修正1：独立计算每个轴的投影范围
  double bestMinProj = DBL_MAX, bestMaxProj = -DBL_MAX;
  int bestAxis = 1;
  double maxSpan = -DBL_MAX;

  for (int axisIdx = 1; axisIdx <= 3; ++axisIdx) {
    // 为每个轴重置min/max
    double axisMin = DBL_MAX, axisMax = -DBL_MAX;
    gp_Dir axis(eigenVectors(1, axisIdx), eigenVectors(2, axisIdx),
                eigenVectors(3, axisIdx));

    for (const auto &p : points) {
      double proj = (p.XYZ() - centroid).Dot(axis.XYZ());
      axisMin = std::min(axisMin, proj);
      axisMax = std::max(axisMax, proj);
    }

    const double span = axisMax - axisMin;
    if (span > maxSpan) {
      maxSpan = span;
      bestAxis = axisIdx;
      bestMinProj = axisMin;
      bestMaxProj = axisMax;
    }
  }

  gp_Dir mainAxis(eigenVectors(1, bestAxis), eigenVectors(2, bestAxis),
                  eigenVectors(3, bestAxis));

  // 4. 分段投影拟合
  const int numSegments =
      std::max(3, static_cast<int>(maxSpan / (2 * avgSpacing)));
  std::vector<gp_Pnt> validCenterPoints; // 改用vector存储有效点

  for (int seg = 0; seg <= numSegments; ++seg) {
    double proj = bestMinProj + seg * (bestMaxProj - bestMinProj) / numSegments;
    gp_Pnt basePoint = gp_Pnt(centroid).Translated(mainAxis.XYZ() * proj);

    gp_Pln sectionPlane(basePoint, mainAxis);
    gp_XYZ localCentroid(0, 0, 0);
    int count = 0;

    for (const auto &p : points) {
      double distToPlane = fabs(sectionPlane.Distance(p));
      if (distToPlane < 2.0 * avgSpacing) {
        localCentroid += p.XYZ();
        count++;
      }
    }

    if (count > 3) {
      localCentroid /= count;
      validCenterPoints.push_back(gp_Pnt(localCentroid));
    }
  }

  // 定义距离阈值，用于判断两点是否重复
  const double distanceThreshold = Precision::Confusion();
  // 对 validCenterPoints 按主轴投影排序。
  // 字典序排序会被质心的微小横向抖动主导, 沿非 X 轴结构
  // (如竖直柱体) 会搅乱先后顺序, 拟合出乱序曲线
  std::sort(validCenterPoints.begin(), validCenterPoints.end(),
            [&](const gp_Pnt &a, const gp_Pnt &b) {
              return mainAxis.XYZ().Dot(a.XYZ() - centroid) <
                     mainAxis.XYZ().Dot(b.XYZ() - centroid);
            });

  // 移除重复点
  auto last =
      std::unique(validCenterPoints.begin(), validCenterPoints.end(),
                  [distanceThreshold](const gp_Pnt &a, const gp_Pnt &b) {
                    return a.Distance(b) < distanceThreshold;
                  });
  validCenterPoints.erase(last, validCenterPoints.end());

  const double simplifyThreshold = avgSpacing;
  if (validCenterPoints.size() > 2) {
    validCenterPoints = douglas_peucker(validCenterPoints, simplifyThreshold);
  }

  // 5. 分段拟合B样条
  if (validCenterPoints.size() < 2) {
    gp_Lin line(centroid, mainAxis);
    return new Geom_Line(line);
  }

  auto compute_section_center = [&](const gp_Pnt &curve_point,
                                    const gp_Vec &tangent) -> gp_Pnt {
    if (tangent.Magnitude() < Precision::Confusion())
      return curve_point;

    // 从 validCenterPoints 中找到最接近 curve_point 的点及其前后点
    size_t closestIndex = 0;
    double minDistance = DBL_MAX;
    for (size_t i = 0; i < validCenterPoints.size(); ++i) {
      double dist = curve_point.Distance(validCenterPoints[i]);
      if (dist < minDistance) {
        minDistance = dist;
        closestIndex = i;
      }
    }

    // 确保有足够的点来计算曲率
    double curvature = 0.0;
    if (closestIndex > 0 && closestIndex < validCenterPoints.size() - 1) {
      gp_Pnt p0 = validCenterPoints[closestIndex - 1];
      gp_Pnt p1 = validCenterPoints[closestIndex];
      gp_Pnt p2 = validCenterPoints[closestIndex + 1];

      gp_Vec v1 = gp_Vec(p0, p1);
      gp_Vec v2 = gp_Vec(p1, p2);

      // 计算曲率的近似值
      gp_Vec crossProduct = v1.Crossed(v2);
      double crossMag = crossProduct.Magnitude();
      double v1Mag = v1.Magnitude();
      double v2Mag = v2.Magnitude();
      if (v1Mag > Precision::Confusion() && v2Mag > Precision::Confusion()) {
        curvature = crossMag / (v1Mag * v2Mag * (v1Mag + v2Mag));
      }
    }

    // 动态调整搜索半径
    double radius = (curvature > 1e-3) ? 1.5 * avgSpacing : 4.0 * avgSpacing;
    gp_Pln section_plane(curve_point, gp_Dir(tangent));

    gp_XYZ weightedCentroid(0, 0, 0);
    double totalWeight = 0.0;

    for (const auto &p : points) {
      double distToPlane = section_plane.Distance(p);
      double distToPoint = curve_point.Distance(p);
      if (distToPlane < radius && distToPoint < 2.0 * radius) {
        // 计算权重，距离越近权重越高
        double weight = 1.0 / (1.0 + distToPoint);
        weightedCentroid += p.XYZ() * weight;
        totalWeight += weight;
      }
    }

    return (totalWeight > 0.0) ? gp_Pnt(weightedCentroid / totalWeight)
                               : curve_point;
  };

  // 获取初始曲线端点
  gp_Pnt startPoint = validCenterPoints.front();
  gp_Pnt endPoint = validCenterPoints.back();

  // 改进切线计算，使用更多点
  gp_Vec startVec = gp_Vec(validCenterPoints[1], startPoint);
  gp_Vec endVec =
      gp_Vec(endPoint, validCenterPoints[validCenterPoints.size() - 2]);
  // 邻点重合时回退主轴方向, 避免 Normalized() 对零向量抛异常
  gp_Vec startTangent =
      startVec.Magnitude() > Precision::Confusion()
          ? startVec.Normalized()
          : gp_Vec(mainAxis);
  gp_Vec endTangent = endVec.Magnitude() > Precision::Confusion()
                          ? endVec.Normalized()
                          : gp_Vec(mainAxis);

  // 计算精确端面中心
  gp_Pnt startCenter = compute_section_center(startPoint, startTangent);
  gp_Pnt endCenter = compute_section_center(endPoint, endTangent);

  // 替换首尾点为端面中心
  validCenterPoints.front() = startCenter;
  validCenterPoints.back() = endCenter;

  // 创建插值点集
  Handle(TColgp_HArray1OfPnt) centerlinePoints =
      new TColgp_HArray1OfPnt(1, validCenterPoints.size());
  for (int i = 0; i < validCenterPoints.size(); ++i) {
    centerlinePoints->SetValue(i + 1, validCenterPoints[i]);
  }

  Handle(Geom_BSplineCurve) centerline;

  // 修正3：使用插值而非逼近
  GeomAPI_Interpolate interpolator(centerlinePoints, Standard_False,
                                   Precision::Confusion());
  interpolator.Perform();

  if (interpolator.IsDone()) {
    centerline = interpolator.Curve();
  } else {
    // 在分段拟合前添加直线检测
    bool isLinear = true;
    if (validCenterPoints.size() > 2) {
      gp_Vec baseDir(validCenterPoints[0], validCenterPoints[1]);
      for (size_t i = 2; i < validCenterPoints.size(); i++) {
        gp_Vec testDir(validCenterPoints[0], validCenterPoints[i]);
        if (!testDir.IsParallel(baseDir, Precision::Angular())) {
          isLinear = false;
          break;
        }
      }
    }

    if (isLinear) {
      gp_Lin line(
          validCenterPoints.front(),
          gp_Dir(gp_Vec(validCenterPoints.front(), validCenterPoints.back())));
      return new Geom_Line(line);
    }
  }

  if (centerline.IsNull()) {
    // 插值失败且非线性: 回退为端面中心连线, 保证有可用轴线
    gp_Vec axisVec(endCenter.XYZ() - startCenter.XYZ());
    if (axisVec.Magnitude() > Precision::Confusion()) {
      return new Geom_Line(startCenter, gp_Dir(axisVec));
    }
    return new Geom_Line(centroid, mainAxis);
  }

  // 6. 曲率自适应迭代优化 - 修正后的曲率计算
  // 近直线情形 (DP 后仅剩 2 个共线质心) 跳过迭代: 小邻域质心只会
  // 放大网格噪声, 让直线拟合摆动
  const bool nearlyStraight = validCenterPoints.size() <= 2;
  const int maxIterations = nearlyStraight ? 0 : 20;

  // 迭代基线长度: 用于检测拟合塌缩 (直线形状在 smoothing→1 时易塌缩)
  const double baseLength = centerline.IsNull()
                                ? 0.0
                                : GCPnts_AbscissaPoint::Length(
                                      GeomAdaptor_Curve(centerline));

  for (int iter = 0; iter < maxIterations; ++iter) {
    try {
    bool significantChange = false;
    GeomAdaptor_Curve adaptor(centerline);

    // 动态采样数
    int adaptiveSamples = std::min(100, std::max(20, numSamples));
    GCPnts_UniformAbscissa abscissa(adaptor, adaptiveSamples);
    if (!abscissa.IsDone())
      break;

    Handle(TColgp_HArray1OfPnt) newPoints =
        new TColgp_HArray1OfPnt(1, abscissa.NbPoints());

    for (int i = 1; i <= abscissa.NbPoints(); ++i) {
      bool isStart = (i == 1);
      bool isEnd = (i == abscissa.NbPoints());
      if (isStart) {
        newPoints->SetValue(i, startCenter);
        continue;
      }
      if (isEnd) {
        newPoints->SetValue(i, endCenter);
        continue;
      }
      double param = abscissa.Parameter(i);
      gp_Pnt point;
      gp_Vec tangent, normal;

      // 直接计算导矢（避免使用GeomLProp_CLProps）
      centerline->D1(param, point, tangent);
      centerline->D2(param, point, tangent, normal);

      // 计算曲率
      double curvature = 0.0;
      const double tangentMag = tangent.Magnitude();
      if (tangentMag > Precision::Confusion()) {
        const double normalMag = normal.Magnitude();
        curvature = normalMag / (tangentMag * tangentMag);
      }

      // 动态搜索半径
      double searchRadius =
          (curvature > 1e-3) ? 0.5 * avgSpacing : 2.0 * avgSpacing;

      gp_XYZ localCentroid(0, 0, 0);
      int count = 0;
      if (tangent.Magnitude() > Precision::Confusion()) {
        gp_Pln plane(point, gp_Dir(tangent));
        for (const auto &p : points) {
          if (point.Distance(p) < searchRadius &&
              fabs(plane.Distance(p)) < 0.5 * searchRadius) {
            localCentroid += p.XYZ();
            count++;
          }
        }
      }
      gp_Pnt newPoint = point;
      if (count > 0) {
        localCentroid /= count;
        // 限制混合比例上限, 防止平滑系数接近 1 时采样点整体塌缩
        double blendFactor = std::min(
            0.8, smoothingFactor * exp(-iter / static_cast<double>(maxIterations)));
        newPoint = gp_Pnt(point.XYZ() * (1.0 - blendFactor) +
                          localCentroid * blendFactor);
        if (newPoint.Distance(point) > 0.01 * avgSpacing) {
          significantChange = true;
        }
      }
      newPoints->SetValue(i, newPoint);
    }

    if (!significantChange)
      break;

    // 重新拟合
    GeomAPI_Interpolate refitter(newPoints, Standard_False, 0.001 * bboxDiag);
    refitter.Perform();
    if (refitter.IsDone()) {
      // 拒绝塌缩的候选曲线: 长度不得明显短于基线
      const double candLen = GCPnts_AbscissaPoint::Length(
          GeomAdaptor_Curve(refitter.Curve()));
      if (candLen < 0.5 * baseLength) {
        break;
      }
      centerline = refitter.Curve();
    } else {
      break;
    }
    } catch (const Standard_Failure &) {
      // 退化输入 (零切向量/塌缩曲线等) 时保留上一轮可用曲线
      break;
    } catch (const std::exception &) {
      break;
    }
  }

  // 7. 端部延伸已移除: 原实现平移 BSpline 末端极点会造成端部回环/过冲
  //    (实测曲线多出 ~10% 长度且裁切走廊畸形), 而拟合曲线本就覆盖端面
  //    质心, 配合 2 倍半径的裁切走廊足以覆盖端部, 无需延伸。

  // 8. 动态调整起点和终点：确保中心线略微超出原始形状
  // 计算中心线长度
  GCPnts_AbscissaPoint abscissa;
  const double totalLength = abscissa.Length(GeomAdaptor_Curve(centerline));
  const double extensionLength = 0.00001 * totalLength;

  // 投影所有点到中心线以找到最小和最大参数
  double t_min = DBL_MAX, t_max = -DBL_MAX;
  for (const auto &p : points) {
    GeomAPI_ProjectPointOnCurve projector(p, centerline);
    if (projector.NbPoints() > 0) {
      double param = projector.LowerDistanceParameter();
      t_min = std::min(t_min, param);
      t_max = std::max(t_max, param);
    }
  }

  // 计算新的起点和终点参数（略微超出形状）
  double t_start =
      std::max(centerline->FirstParameter(), t_min - extensionLength);
  double t_end = std::min(centerline->LastParameter(), t_max + extensionLength);

  // 使用Geom_TrimmedCurve创建修剪后的曲线
  try {
    Handle(Geom_TrimmedCurve) trimmedCurve =
        new Geom_TrimmedCurve(centerline, t_start, t_end);
    return trimmedCurve;
  } catch (const Standard_Failure &) {
    // 修剪区间退化时返回未修剪曲线
    return centerline;
  } catch (const std::exception &) {
    return centerline;
  }
}

bounding_pipe compute_simple_bounding_pipe_from_shape(const TopoDS_Shape &shape,
                                                      const gp_Dir &userDir) {
  bounding_pipe result;

  if (shape.IsNull()) {
    return result;
  }

  // 1. 计算形状的包围盒
  Bnd_Box bbox;
  BRepBndLib::Add(shape, bbox);
  double xmin, ymin, zmin, xmax, ymax, zmax;
  bbox.Get(xmin, ymin, zmin, xmax, ymax, zmax);
  gp_Pnt minPt(xmin, ymin, zmin);
  gp_Pnt maxPt(xmax, ymax, zmax);

  // 2. 计算沿用户方向的投影范围
  double minProj = DBL_MAX, maxProj = -DBL_MAX;
  for (TopExp_Explorer exp(shape, TopAbs_VERTEX); exp.More(); exp.Next()) {
    gp_Pnt p = BRep_Tool::Pnt(TopoDS::Vertex(exp.Current()));
    double proj = p.XYZ().Dot(userDir.XYZ());
    minProj = std::min(minProj, proj);
    maxProj = std::max(maxProj, proj);
  }

  // 3. 创建中心线(直线)
  gp_Pnt start = gp::Origin().Translated(userDir.XYZ() * minProj);
  gp_Pnt end = gp::Origin().Translated(userDir.XYZ() * maxProj);
  gp_Lin line(start, gp_Dir(userDir));
  result.centerline = new Geom_Line(line);

  // 4. 计算最大半径
  double maxRadius = 0.0;
  for (TopExp_Explorer exp(shape, TopAbs_VERTEX); exp.More(); exp.Next()) {
    gp_Pnt p = BRep_Tool::Pnt(TopoDS::Vertex(exp.Current()));
    double dist = line.Distance(p);
    maxRadius = std::max(maxRadius, dist);
  }

  // 添加安全余量
  result.radius = maxRadius * 1.2; // 20% 安全余量

  // 5. 生成点集
  result.points = {start, end};

  return result;
}

double compute_max_radius(const TopoDS_Shape &shape,
                          const Handle(Geom_Curve) & centerline) {
  std::vector<gp_Pnt> allPoints;
  TopExp_Explorer vertexExplorer(shape, TopAbs_VERTEX);
  for (; vertexExplorer.More(); vertexExplorer.Next()) {
    TopoDS_Vertex vertex = TopoDS::Vertex(vertexExplorer.Current());
    allPoints.push_back(BRep_Tool::Pnt(vertex));
  }

  // 2. 从边采样点（如果顶点不足）
  if (allPoints.size() < 50) {
    TopExp_Explorer edgeExplorer(shape, TopAbs_EDGE);
    for (; edgeExplorer.More(); edgeExplorer.Next()) {
      TopoDS_Edge edge = TopoDS::Edge(edgeExplorer.Current());
      BRepAdaptor_Curve curve(edge);
      double first = curve.FirstParameter();
      double last = curve.LastParameter();
      int numSamplesPerEdge = 10;
      for (int i = 0; i < numSamplesPerEdge; i++) {
        double param = first + i * (last - first) / (numSamplesPerEdge - 1);
        gp_Pnt point = curve.Value(param);
        allPoints.push_back(point);
      }
    }
  }

  // 3. 计算所有点到中心线的最大距离
  double maxRadius = 0.0;
  ShapeAnalysis_Curve sac;
  for (const auto &point : allPoints) {
    gp_Pnt nearestPoint;
    double paramOnCurve;
    double distance = sac.Project(centerline, point, Precision::Confusion(),
                                  nearestPoint, paramOnCurve);

    if (distance > maxRadius) {
      maxRadius = distance;
    }
  }

  // 4. 添加安全余量并保存结果。
  //    1.5 倍即可覆盖断面 + 拟合摆动; 2 倍在密集线圈上会啃到相邻圈
  if (maxRadius > Precision::Confusion()) {
    return maxRadius * 1.5;
  }

  return maxRadius;
}

double compute_max_radius_to_wire(const TopoDS_Shape &shape,
                                  const TopoDS_Wire &path) {
  // 1. 形状采样点: 顶点优先, 不足则沿边采样 (与 compute_max_radius 一致)
  std::vector<gp_Pnt> allPoints;
  TopExp_Explorer vertexExplorer(shape, TopAbs_VERTEX);
  for (; vertexExplorer.More(); vertexExplorer.Next()) {
    allPoints.push_back(
        BRep_Tool::Pnt(TopoDS::Vertex(vertexExplorer.Current())));
  }
  if (allPoints.size() < 50) {
    TopExp_Explorer edgeExplorer(shape, TopAbs_EDGE);
    for (; edgeExplorer.More(); edgeExplorer.Next()) {
      BRepAdaptor_Curve curve(TopoDS::Edge(edgeExplorer.Current()));
      double first = curve.FirstParameter();
      double last = curve.LastParameter();
      int numSamplesPerEdge = 10;
      for (int i = 0; i < numSamplesPerEdge; i++) {
        double param = first + i * (last - first) / (numSamplesPerEdge - 1);
        allPoints.push_back(curve.Value(param));
      }
    }
  }
  if (allPoints.empty()) {
    return 0.0;
  }

  // 2. 路径均匀采样为折线 (避免对多段 wire 依赖单一 Geom_Curve)
  std::vector<gp_Pnt> pathPts;
  try {
    BRepAdaptor_CompCurve adaptor(path);
    GCPnts_UniformAbscissa sampler(adaptor, 200);
    if (sampler.IsDone()) {
      for (int i = 1; i <= sampler.NbPoints(); ++i) {
        pathPts.push_back(adaptor.Value(sampler.Parameter(i)));
      }
    }
  } catch (const Standard_Failure &) {
    return 0.0;
  } catch (const std::exception &) {
    return 0.0;
  }
  if (pathPts.size() < 2) {
    return 0.0;
  }

  // 3. 形状点到路径折线的最大距离 (点到线段精确距离)
  double maxRadius = 0.0;
  for (const auto &p : allPoints) {
    double best = DBL_MAX;
    for (size_t i = 0; i + 1 < pathPts.size(); ++i) {
      const gp_XYZ ab = pathPts[i + 1].XYZ() - pathPts[i].XYZ();
      const gp_XYZ ap = p.XYZ() - pathPts[i].XYZ();
      double t = ab.Modulus() > 0.0 ? ap.Dot(ab) / ab.Modulus() / ab.Modulus()
                                    : 0.0;
      t = std::max(0.0, std::min(1.0, t));
      const gp_XYZ closest = pathPts[i].XYZ() + ab * t;
      const double d = p.Distance(gp_Pnt(closest));
      if (d < best) {
        best = d;
      }
    }
    if (best > maxRadius) {
      maxRadius = best;
    }
  }

  // 4. 与 compute_max_radius 相同的安全余量, 并覆盖折线采样欠估
  if (maxRadius > Precision::Confusion()) {
    return maxRadius * 1.5;
  }
  return maxRadius;
}

bounding_pipe extract_bounding_pipe_from_shape(const TopoDS_Shape &shape,
                                               const gp_Dir *userDir,
                                               int numSamplePoints,
                                               bool fitCenterline) {
  bounding_pipe result;

  // 1. 检查是否为管道形状
  if (shape.IsNull()) {
    return result;
  }

  // 2. 计算包围盒用于后续参考
  Bnd_Box bbox;
  BRepBndLib::Add(shape, bbox);
  double xmin, ymin, zmin, xmax, ymax, zmax;
  bbox.Get(xmin, ymin, zmin, xmax, ymax, zmax);
  double bboxDiag =
      sqrt(pow(xmax - xmin, 2) + pow(ymax - ymin, 2) + pow(zmax - zmin, 2));
  const double avgSpacing = bboxDiag / 100.0; // 估算平均点间距

  // 3. 检查是否使用用户指定的方向
  bool useUserDirection = (userDir != nullptr && gp_Vec(*userDir).Magnitude() >
                                                     Precision::Confusion());

  if (useUserDirection) {
    return compute_simple_bounding_pipe_from_shape(shape, *userDir);
  }

  // 4. 提取中心线
  if (fitCenterline) {
    result.centerline = fit_centerline_from_shape(shape, numSamplePoints, 0.4);
  }

  // 5. 提取截面信息
  if (!result.centerline.IsNull()) {
    result.radius = compute_max_radius(shape, result.centerline);
  }

  // 6. 采样中心线
  if (!result.centerline.IsNull()) {
    result.points = sample_centerline(result.centerline, numSamplePoints);
  }

  return result;
}

TopoDS_Shape create_bounding_pipe_shape(double radius,
                                        const TopoDS_Wire &path) {
  if (path.IsNull() || radius <= Precision::Confusion()) {
    return TopoDS_Shape();
  }

  // 沿路径分段弦向棱柱, 生成覆盖路径的圆柱走廊。
  // 刻意不用 MakePipeShell 扫掠: 它对拟合出的近直 BSpline 脊线会以
  // IsDone=true 产出无法参与布尔运算的实体 (实测静默少切), 而棱柱
  // 走廊逐段都是标准圆柱体, 裁切精确; 段长上界 2*radius 保证弦高误差
  // 远小于工具半径的 2 倍安全余量。
  GProp_GProps pathProps;
  BRepGProp::LinearProperties(path, pathProps);
  const double pathLength = pathProps.Mass();

  try {
    BRepAdaptor_CompCurve adaptor(path);
    // 分段数: 弦长在曲率下的矢高必须远小于工具半径余量。
    // 用路径总转角估计: 每 0.5 rad 一个段 (矢高 ≈ 0.08×曲率半径),
    // 直线段退化为长度准则
    double totalTurn = 0.0;
    {
      const int nDir = 48;
      gp_Pnt dummy;
      gp_Vec prevTan;
      adaptor.D1(adaptor.FirstParameter(), dummy, prevTan);
      for (int i = 1; i <= nDir; ++i) {
        const double u =
            adaptor.FirstParameter() +
            (adaptor.LastParameter() - adaptor.FirstParameter()) * i /
                static_cast<double>(nDir);
        gp_Vec tan;
        adaptor.D1(u, dummy, tan);
        if (tan.Magnitude() > Precision::Confusion() &&
            prevTan.Magnitude() > Precision::Confusion()) {
          const double ang = acos(std::max(-1.0, std::min(
              1.0, gp_Dir(tan).Dot(gp_Dir(prevTan)))));
          totalTurn += ang;
        }
        prevTan = tan;
      }
    }
    const int nByTurn = static_cast<int>(ceil(totalTurn / 0.5));
    const int nByLen =
        static_cast<int>(pathLength / (2 * radius)) + 1;
    const int nSegs = std::min(64, std::max(1, std::max(nByTurn, nByLen)));
    GCPnts_UniformAbscissa sampler(adaptor, nSegs + 1);
    if (sampler.IsDone() && sampler.NbPoints() >= 2) {
      TopoDS_Compound corridor;
      BRep_Builder builder;
      builder.MakeCompound(corridor);
      int added = 0;
      for (int i = 1; i < sampler.NbPoints(); ++i) {
        const gp_Pnt a = adaptor.Value(sampler.Parameter(i));
        const gp_Pnt b = adaptor.Value(sampler.Parameter(i + 1));
        const gp_Vec seg(a, b);
        if (seg.Magnitude() <= Precision::Confusion()) {
          continue;
        }
        gp_Ax2 axis(a, gp_Dir(seg));
        Handle(Geom_Circle) circle = new Geom_Circle(axis, radius);
        TopoDS_Edge circEdge = BRepBuilderAPI_MakeEdge(circle).Edge();
        TopoDS_Wire circWire = BRepBuilderAPI_MakeWire(circEdge).Wire();
        BRepBuilderAPI_MakeFace faceMaker(circWire, Standard_True);
        if (!faceMaker.IsDone()) {
          continue;
        }
        TopoDS_Shape segPrism =
            BRepPrimAPI_MakePrism(faceMaker.Face(), seg).Shape();
        if (!segPrism.IsNull()) {
          builder.Add(corridor, segPrism);
          added++;
        }
      }
      if (added > 0) {
        return corridor;
      }
    }
  } catch (const Standard_Failure &) {
  } catch (const std::exception &) {
  }

  // 最终回退: 轴心近似直线时用圆截面沿首末弦向拉伸
  BRepAdaptor_CompCurve curveAdaptor(path);
  const gp_Pnt p0 = curveAdaptor.Value(curveAdaptor.FirstParameter());
  const gp_Pnt p1 = curveAdaptor.Value(curveAdaptor.LastParameter());
  const gp_Vec chord(p0, p1);
  const double chordLen = chord.Magnitude();

  if (chordLen > Precision::Confusion() && pathLength <= chordLen * 1.05) {
    gp_Ax2 axis(p0, gp_Dir(chord));
    Handle(Geom_Circle) circle = new Geom_Circle(axis, radius);
    TopoDS_Edge circEdge = BRepBuilderAPI_MakeEdge(circle).Edge();
    TopoDS_Wire circWire = BRepBuilderAPI_MakeWire(circEdge).Wire();
    BRepBuilderAPI_MakeFace faceMaker(circWire, Standard_True);
    if (faceMaker.IsDone()) {
      BRepPrimAPI_MakePrism prismMaker(faceMaker.Face(), chord);
      if (prismMaker.IsDone()) {
        return prismMaker.Shape();
      }
    }
  }

  return TopoDS_Shape();
}

// 顺序裁切: compound 工具拆成单个 solid 逐个裁切, 每个 Cut 都是
// 单工具布尔 (实测最稳定); 任一步失败即抛错, 不静默返回部分结果
static TopoDS_Shape cut_with_tools(const TopoDS_Shape &shape,
                                   const TopoDS_Shape &tools) {
  TopoDS_Shape result = shape;
  if (tools.ShapeType() == TopAbs_COMPOUND) {
    for (TopExp_Explorer ex(tools, TopAbs_SOLID); ex.More(); ex.Next()) {
      BRepAlgoAPI_Cut cut(result, ex.Current());
      if (!cut.IsDone()) {
        throw Standard_ConstructionError("Segment clipping failed");
      }
      result = cut.Shape();
    }
    return result;
  }
  BRepAlgoAPI_Cut cut(result, tools);
  if (!cut.IsDone()) {
    throw Standard_ConstructionError("Segment clipping failed");
  }
  return cut.Shape();
}

TopoDS_Shape clip_with_bounding_pipe_and_split_distances(
    const TopoDS_Shape &shape, const bounding_pipe &boundPipe,
    const std::array<double, 2> &splitDistances, TopoDS_Wire originalPathWire) {
  // 参数验证
  if (splitDistances[0] < 0) {
    throw Standard_ConstructionError("First split distance must be >= 0");
  }

  Handle(Geom_Curve) centerline;
  if (boundPipe.centerline.IsNull() && boundPipe.points.size() > 0) {
    centerline = centerline_to_curve(boundPipe.points);
  } else {
    centerline = boundPipe.centerline;
  }

  TopoDS_Shape fullPipe = shape;
  TopoDS_Wire pathWire =
      originalPathWire.IsNull()
          ? BRepLib_MakeWire(BRepLib_MakeEdge(centerline).Edge()).Wire()
          : originalPathWire;

  if (pathWire.IsNull()) {
    throw Standard_ConstructionError("Failed to extract path wire");
  }

  // 计算路径总长度
  GProp_GProps lengthProps;
  BRepGProp::LinearProperties(pathWire, lengthProps);
  double totalLength = lengthProps.Mass();

  // 处理第二个分割距离
  double secondSplitStart = splitDistances[0];
  double secondSplitEnd = splitDistances[1];

  if (secondSplitEnd == -1 || secondSplitEnd > totalLength * 0.99) {
    secondSplitEnd = totalLength;
  }

  if (secondSplitStart == -1 || secondSplitStart < totalLength * 0.01) {
    secondSplitStart = 0;
  }

  if (secondSplitEnd <= secondSplitStart || secondSplitEnd > totalLength) {
    throw Standard_ConstructionError("Invalid second split distance");
  }

  // 如果不需要分割，直接返回完整管道
  if (secondSplitStart == 0 && secondSplitEnd >= totalLength) {
    return fullPipe;
  }

  // 需要裁切时半径必须有效, 否则静默返回完整形状会伪装成 100% 进度
  if (!(boundPipe.radius > Precision::Confusion())) {
    throw Standard_ConstructionError(
        "Invalid bounding pipe radius for clipping");
  }

  // 创建前段裁切体
  TopoDS_Shape frontCut;
  if (secondSplitStart > 0) {
    TopoDS_Wire frontWire =
        clip_wire_between_distances_helper(pathWire, 0, secondSplitStart);

    if (!frontWire.IsNull()) {
      frontCut = create_bounding_pipe_shape(boundPipe.radius, frontWire);
      if (frontCut.IsNull()) {
        throw Standard_ConstructionError("Failed to build front cut tool");
      }
    }
  }

  // 创建后段裁切体
  TopoDS_Shape backCut;
  if (secondSplitEnd < totalLength) {
    TopoDS_Wire backWire = clip_wire_between_distances_helper(
        pathWire, secondSplitEnd, totalLength);

    if (!backWire.IsNull()) {
      // 使用最大圆形截面创建裁切体
      backCut = create_bounding_pipe_shape(boundPipe.radius, backWire);
      if (backCut.IsNull()) {
        throw Standard_ConstructionError("Failed to build back cut tool");
      }
    }
  }

  // 执行裁切操作 (校验布尔运算状态, 不允许静默丢失裁切)。
  // 工具若是 compound (分段棱柱走廊), 拆成单个 solid 依次裁:
  // 实测 compound/预融合工具会让 BOP 静默少切, 而单工具顺序裁精确。
  TopoDS_Shape result = fullPipe;
  if (!frontCut.IsNull()) {
    result = cut_with_tools(result, frontCut);
  }
  if (!backCut.IsNull()) {
    result = cut_with_tools(result, backCut);
  }

  return result;
}

TopoDS_Shape clip_with_bounding_pipe_by_ratios(
    const TopoDS_Shape &shape, const bounding_pipe &boundPipe,
    const std::array<double, 2> &splitRatios, TopoDS_Wire originalPathWire) {
  // 参数验证
  if (splitRatios[0] < 0 || splitRatios[0] > 1.0) {
    throw Standard_ConstructionError(
        "First split ratio must be between 0 and 1");
  }
  if (splitRatios[1] != -1 &&
      (splitRatios[1] <= splitRatios[0] || splitRatios[1] > 1.0)) {
    throw Standard_ConstructionError("Invalid second split ratio");
  }

  Handle(Geom_Curve) centerline;
  if (boundPipe.centerline.IsNull() && boundPipe.points.size() > 0) {
    centerline = centerline_to_curve(boundPipe.points);
  } else {
    centerline = boundPipe.centerline;
  }

  // 计算路径总长度
  TopoDS_Wire pathWire =
      originalPathWire.IsNull()
          ? BRepLib_MakeWire(BRepLib_MakeEdge(centerline).Edge()).Wire()
          : originalPathWire;

  if (pathWire.IsNull()) {
    throw Standard_ConstructionError("Failed to extract path wire");
  }

  GProp_GProps lengthProps;
  BRepGProp::LinearProperties(pathWire, lengthProps);
  double totalLength = lengthProps.Mass();

  // 转换为实际距离
  std::array<double, 2> splitDistances = {
      splitRatios[0] * totalLength,
      splitRatios[1] == -1 ? -1 : splitRatios[1] * totalLength};

  // 调用基于距离的版本
  return clip_with_bounding_pipe_and_split_distances(shape, boundPipe,
                                                     splitDistances, pathWire);
}

std::vector<gp_Pnt> sample_centerline(Handle(Geom_Curve) centerline,
                                      int numSamples, bool simplify) {
  std::vector<gp_Pnt> points;
  if (centerline.IsNull() || numSamples < 1) {
    return points;
  }

  // 创建曲线适配器以访问参数范围
  GeomAdaptor_Curve adaptor(centerline);
  double firstParam = adaptor.FirstParameter();
  double lastParam = adaptor.LastParameter();

  // 计算路径总长度
  GCPnts_AbscissaPoint abscissa;
  double totalLength = abscissa.Length(GeomAdaptor_Curve(centerline));
  
  // 检查总长度是否有效
  if (std::isinf(totalLength) || std::isnan(totalLength) || totalLength <= 0) {
    totalLength = lastParam - firstParam; // 使用参数范围作为替代
  }

  // 使用限制后的参数范围进行采样
  GCPnts_UniformAbscissa sampler;
  sampler.Initialize(adaptor, numSamples, firstParam, lastParam);
  
  if (!sampler.IsDone()) {
    // 如果初始化失败，尝试使用默认参数范围
    sampler.Initialize(adaptor, numSamples, 0.0, 1.0);
  }
  
  if (sampler.IsDone()) {
    for (int i = 1; i <= sampler.NbPoints(); ++i) {
      double param = sampler.Parameter(i);
      // 确保参数在有效范围内
      param = std::max(firstParam, std::min(lastParam, param));
      gp_Pnt point;
      centerline->D0(param, point);
      points.push_back(point);
    }
  }

  if (simplify && points.size() > 2) {
    double epsilon = totalLength * 0.001;
    // 确保epsilon是有效值
    if (std::isinf(epsilon) || std::isnan(epsilon) || epsilon <= 0) {
      epsilon = 0.001;
    }
    return douglas_peucker(points, epsilon);
  }

  return points;
}

Handle(Geom_Curve) centerline_to_curve(const std::vector<gp_Pnt> &points) {
  if (points.empty()) {
    return nullptr;
  }

  if (points.size() == 2) {
    gp_Lin line = gce_MakeLin(points[0], points[1]);
    return new Geom_Line(line);
  }

  // 将点集转换为TColgp_Array1OfPnt
  TColgp_Array1OfPnt pointArray(1, static_cast<int>(points.size()));
  for (int i = 0; i < points.size(); i++) {
    pointArray.SetValue(i + 1, points[i]);
  }

  // 使用PointsToBSpline拟合曲线
  GeomAPI_PointsToBSpline fitter;
  fitter.Init(pointArray, 3, 8, GeomAbs_C2,
              Precision::Confusion()); // 使用默认参数

  if (fitter.IsDone()) {
    return Handle_Geom_Curve(fitter.Curve());
  }

  return nullptr;
}

} // namespace topo
} // namespace flywave
