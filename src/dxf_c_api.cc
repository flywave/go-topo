#include "dxf_c_api.h"
#include "aci_table.hh"
#include "dxf_shape.hh"
#include "shape.hh"
#include "topo_impl.hh"

#include <memory>
#include <string>
#include <vector>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _dxf_reader_t {
  std::unique_ptr<flywave::dxf::dxf_shape_reader> reader;
} dxf_reader_t;

struct _dxf_writer_t {
  std::unique_ptr<flywave::dxf::dxf_shape_writer> writer;
};

typedef struct _dxf_shape_entity_layer_t {
  std::vector<flywave::dxf::dxf_shape_entity> entities;
} dxf_shape_entity_layer_t;

typedef struct _dxf_shape_entity_t {
  flywave::dxf::dxf_shape_entity entity;
} dxf_shape_entity_t;

typedef struct _dxf_text_entity_layer_t {
  std::vector<flywave::dxf::dxf_text_entity> entities;
} dxf_text_entity_layer_t;

typedef struct _dxf_text_entity_t {
  flywave::dxf::dxf_text_entity entity;
} dxf_text_entity_t;

dxf_reader_t *dxf_open_reader(const char *filename) {
  auto reader = std::make_unique<flywave::dxf::dxf_shape_reader>(filename);
  reader->do_read();
  return new dxf_reader_t{.reader = std::move(reader)};
}

void dxf_reader_free(dxf_reader_t *p) {
  if (p) {
    delete p;
  }
}

_Bool dxf_reader_is_failed(dxf_reader_t *p) {
  if (p) {
    return p->reader->failed();
  }
  return false;
}

void dxf_reader_do_read(dxf_reader_t *p) {
  if (p) {
    p->reader->do_read();
  }
}

const char *dxf_reader_get_error(dxf_reader_t *p) {
  if (p) {
    return p->reader->error().c_str();
  }
  return nullptr;
}

_Bool dxf_reader_has_error(dxf_reader_t *p) {
  if (p) {
    return !p->reader->error().empty();
  }
  return false;
}

const char **dxf_reader_get_layer_names(dxf_reader_t *p, int *count) {
  if (p) {
    const auto &layers = p->reader->shape_layers();
    *count = static_cast<int>(layers.size());
    const char **names = new const char *[*count];
    int i = 0;
    for (const auto &layer : layers) {
      names[i++] = layer.first.c_str();
    }
    return names;
  }
  return nullptr;
}

void dxf_layer_names_free(const char **names) {
  if (names) {
    delete[] names;
  }
}

dxf_shape_entity_layer_t *dxf_shape_entity_layer_new() {
  return new dxf_shape_entity_layer_t;
}

dxf_shape_entity_layer_t *dxf_reader_get_shape_entity_layer(dxf_reader_t *p,
                                                            const char *name) {
  if (p) {
    const auto &layers = p->reader->shape_layers();
    auto it = layers.find(name);
    if (it != layers.end()) {
      return new dxf_shape_entity_layer_t{.entities = it->second};
    }
  }
  return nullptr;
}

void dxf_shape_entity_layer_add(dxf_shape_entity_layer_t *p,
                                dxf_shape_entity_t *entity) {
  if (p) {
    p->entities.push_back(entity->entity);
  }
}

void dxf_shape_entity_layer_free(dxf_shape_entity_layer_t *p) {
  if (p) {
    delete p;
  }
}

int dxf_shape_entity_layer_get_count(dxf_shape_entity_layer_t *p) {
  if (p) {
    return static_cast<int>(p->entities.size());
  }
  return 0;
}
dxf_shape_entity_t *
dxf_shape_entity_layer_get_entity(dxf_shape_entity_layer_t *p, int index) {
  if (p) {
    return new dxf_shape_entity_t{.entity = p->entities[index]};
  }
  return nullptr;
}

dxf_shape_entity_t *dxf_shape_entity_new(topo_shape_t *shape, int color) {
  return new dxf_shape_entity_t{.entity = flywave::dxf::dxf_shape_entity{
                                    .color = color,
                                    .shape = shape->shp->value(),
                                }};
}

void dxf_shape_entity_free(dxf_shape_entity_t *p) {
  if (p) {
    delete p;
  }
}

color_t dxf_shape_entity_get_color(dxf_shape_entity_t *p) {
  if (p) {
    auto index = p->entity.color;
    auto rgb = flywave::dxf::aci_table[index];
    return color_t{double(rgb.second.r / 255), double(rgb.second.g / 255),
                   double(rgb.second.b / 255)};
  }
  return color_t{0, 0, 0};
}

topo_shape_t *dxf_shape_entity_get_shape(dxf_shape_entity_t *p) {
  if (p) {
    return new topo_shape_t{
        .shp = std::make_shared<flywave::topo::shape>(p->entity.shape)};
  }
  return nullptr;
}

dxf_text_entity_layer_t *dxf_text_entity_layer_new() {
  return new dxf_text_entity_layer_t;
}

dxf_text_entity_layer_t *dxf_reader_get_text_entity_layer(dxf_reader_t *p,
                                                          const char *name) {
  if (p) {
    const auto &layers = p->reader->text_layers();
    auto it = layers.find(name);
    if (it != layers.end()) {
      return new dxf_text_entity_layer_t{.entities = it->second};
    }
  }
  return nullptr;
}

void dxf_text_entity_layer_add_entity(dxf_text_entity_layer_t *p,
                                      dxf_text_entity_t *entity) {
  if (p) {
    p->entities.push_back(entity->entity);
  }
}

void dxf_text_entity_layer_free(dxf_text_entity_layer_t *p) {
  if (p) {
    delete p;
  }
}

int dxf_text_entity_layer_get_count(dxf_text_entity_layer_t *p) {
  if (p) {
    return static_cast<int>(p->entities.size());
  }
  return 0;
}

dxf_text_entity_t *dxf_text_entity_layer_get_entity(dxf_text_entity_layer_t *p,
                                                    int index) {
  if (p) {
    return new dxf_text_entity_t{.entity = p->entities[index]};
  }
  return nullptr;
}

dxf_text_entity_t *dxf_text_entity_new(const char *text, pnt3d_t position,
                                       double height, double rotation,
                                       int color) {
  return new dxf_text_entity_t{
      .entity = flywave::dxf::dxf_text_entity{
          text, gp_Pnt(position.x, position.y, position.z), gp_Vec(0, 0, 1),
          gp_Vec(1, 0, 0), height, rotation, color}};
}

void dxf_text_entity_free(dxf_text_entity_t *p) {
  if (p) {
    delete p;
  }
}

const char *dxf_text_entity_get_text(dxf_text_entity_t *p) {
  if (p) {
    return p->entity.text.c_str();
  }
  return nullptr;
}

pnt3d_t dxf_text_entity_get_position(dxf_text_entity_t *p) {
  if (p) {
    return pnt3d_t{p->entity.position.X(), p->entity.position.Y(),
                   p->entity.position.Z()};
  }
  return pnt3d_t{0, 0, 0};
}

vec3d_t dxf_text_entity_get_normal(dxf_text_entity_t *p) {
  if (p) {
    return vec3d_t{p->entity.normal.X(), p->entity.normal.Y(),
                   p->entity.normal.Z()};
  }
  return vec3d_t{0, 0, 0};
}

vec3d_t dxf_text_entity_get_x_axis_dir(dxf_text_entity_t *p) {
  if (p) {
    return vec3d_t{p->entity.x_axis_dir.X(), p->entity.x_axis_dir.Y(),
                   p->entity.x_axis_dir.Z()};
  }
  return vec3d_t{0, 0, 0};
}

dxf_writer_t *dxf_open_writer(const char *filename) {
  auto writer = std::make_unique<flywave::dxf::dxf_shape_writer>(filename);
  return new dxf_writer_t{.writer = std::move(writer)};
}

void dxf_writer_free(dxf_writer_t *p) {
  if (p) {
    delete p;
  }
}

void dxf_writer_add_shape(dxf_writer_t *p, const char *layerName,
                          topo_shape_t *shape, int index) {
  if (p) {
    p->writer->add_shape(layerName, *shape->shp, index);
  }
}

void dxf_writer_add_text(dxf_writer_t *p, const char *layerName,
                         const char *text, pnt3d_t position, double height,
                         double rotation, int index) {
  if (p) {
    p->writer->add_text(layerName,
                        flywave::dxf::dxf_text_entity{
                            text, gp_Pnt(position.x, position.y, position.z),
                            gp_Vec(0, 0, 1), gp_Vec(1, 0, 0), height, rotation,
                            index});
  }
}

void dxf_writer_add_shape_layer(dxf_writer_t *p, const char *name,
                                dxf_shape_entity_layer_t *layer) {
  if (p) {
    std::vector<std::pair<TopoDS_Shape, flywave::dxf::color_index_t>> shapes;
    for (int i = 0; i < dxf_shape_entity_layer_get_count(layer); ++i) {
      auto entity = dxf_shape_entity_layer_get_entity(layer, i);
      shapes.emplace_back(entity->entity.shape, entity->entity.color);
    }
    p->writer->add_shape_layer(name, shapes);
  }
}

void dxf_writer_add_text_layer(dxf_writer_t *p, const char *name,
                               dxf_text_entity_layer_t *layer) {
  if (p) {
    std::vector<flywave::dxf::dxf_text_entity> texts;
    for (int i = 0; i < dxf_text_entity_layer_get_count(layer); ++i) {
      auto entity = dxf_text_entity_layer_get_entity(layer, i);
      texts.push_back(entity->entity);
    }
    p->writer->add_text_layer(name, texts);
  }
}

_Bool dxf_writer_write(dxf_writer_t *p) {
  if (p) {
    return p->writer->write();
  }
  return false;
}

#ifdef __cplusplus
}
#endif
