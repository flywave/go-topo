// parametric_test — the C++ parametric factory: registry round-trip, node
// metadata through copy, rebuild dispatch (incl. the Go-mirrored error paths).
// Hand-rolled pass/fail, same pattern as cadquery_examples_test.cc.
#include <iostream>
#include <string>

#include "parametric.hh"

#include "solid.hh"
#include "vertex.hh"

namespace ftopo = flywave::topo;

static int pass = 0, fail = 0;

#define CHECK(cond, msg)                                                       \
  do {                                                                         \
    if (cond) {                                                                \
      pass++;                                                                  \
    } else {                                                                   \
      fail++;                                                                  \
      std::cout << "FAIL: " << msg << " (line " << __LINE__ << ")\n";          \
    }                                                                          \
  } while (0)

// A box builder: params "WxDxH" in millimetres.
static ftopo::parametric_build_result
build_box(const std::string &params) {
  double w = 100, d = 100, h = 50;
  if (sscanf(params.c_str(), "%lfx%lfx%lf", &w, &d, &h) != 3) {
    throw std::runtime_error("bad params, want WxDxH");
  }
  auto box = ftopo::solid::make_solid_from_box(w, d, h);
  ftopo::parametric_build_result r;
  r.shp = box;
  return r;
}

int main() {
  // 1. register / has / build
  ftopo::register_parametric_builder("test_box", build_box);
  CHECK(ftopo::has_parametric_builder("test_box"), "registered type visible");
  CHECK(!ftopo::has_parametric_builder("nope"), "unregistered type absent");

  auto r = ftopo::build_parametric("test_box", "120x60x18");
  CHECK(!r.shp.is_null(), "built shape non-null");
  CHECK(std::abs(r.shp.bbox().z_length() - 18) < 1e-6, "box height 18");

  // 2. unregistered type: the Go-mirrored error
  bool threw = false;
  try {
    ftopo::build_parametric("nope", "{}");
  } catch (const std::runtime_error &e) {
    threw = std::string(e.what()).find("no parametric builder registered") !=
            std::string::npos;
  }
  CHECK(threw, "unregistered type throws the Go-worded error");

  // 3. null-shape builder: the Go-mirrored error
  ftopo::register_parametric_builder(
      "test_null", [](const std::string &) -> ftopo::parametric_build_result {
        return {ftopo::shape{}, nullptr};
      });
  threw = false;
  try {
    ftopo::build_parametric("test_null", "{}");
  } catch (const std::runtime_error &e) {
    threw = std::string(e.what()).find("null shape") != std::string::npos;
  }
  CHECK(threw, "null-shape builder throws");

  // 4. node metadata survives copy
  auto node = ftopo::assembly::create(ftopo::vertex(0, 0, 0), nullptr, "cover");
  ftopo::set_parametric(*node, {"gim_cover_plate", "{\"length\":300}"});
  auto got = ftopo::get_parametric(*node);
  CHECK(got.has_value() && got->type == "gim_cover_plate", "metadata set/get");
  auto copied = node->copy();
  auto got2 = ftopo::get_parametric(*copied);
  CHECK(got2.has_value() && *got2 == *got, "metadata survives copy");

  // 5. rebuild_parametric_node: recipe node via builder + children + location
  ftopo::register_parametric_builder("test_box", build_box);
  ftopo::parametric_data data{"test_box", "120x60x18"};
  std::vector<std::shared_ptr<ftopo::assembly>> children;
  auto built = ftopo::rebuild_parametric_node("plate", data, std::nullopt,
                                              std::nullopt, children);
  CHECK(ftopo::get_parametric(*built).has_value(), "rebuilt node keeps recipe");
  CHECK(!built->has_obj() == false, "rebuilt node carries geometry");

  // 6. container node (no recipe) gets the origin-vertex placeholder
  auto container = ftopo::rebuild_parametric_node("root", std::nullopt,
                                                  std::nullopt, std::nullopt,
                                                  {built});
  CHECK(container->children().size() == 1, "children attached");
  CHECK(container->has_obj(), "container carries placeholder vertex");

  // 7. unregister via empty fn
  ftopo::register_parametric_builder("test_box", nullptr);
  CHECK(!ftopo::has_parametric_builder("test_box"), "empty fn unregisters");

  std::cout << (fail == 0 ? "ALL PASS" : "HAS FAILURES") << " (" << pass
            << " passed, " << fail << " failed)\n";
  return fail == 0 ? 0 : 1;
}
