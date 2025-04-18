package topo

/*
#include <stdlib.h>
#include "dxf_c_api.h"
#cgo CFLAGS: -I  ./libs
#cgo linux CXXFLAGS: -I ./libs  -std=gnu++14
#cgo darwin,amd64 CXXFLAGS: -I ./libs  -std=gnu++14
#cgo darwin,arm64 CXXFLAGS: -I ./libs  -std=gnu++14
#cgo windows CXXFLAGS: -I ./libs  -std=gnu++14
*/
import "C"
import (
	"runtime"
	"unsafe"
)

type DxfReader struct {
	inner *innerDxfReader
}

type innerDxfReader struct {
	val *C.struct__dxf_reader_t
}

func (t *innerDxfReader) free() {
	C.dxf_reader_free(t.val)
}

func NewDxfReader(f string) *DxfReader {
	fl := C.CString(f)
	defer C.free(unsafe.Pointer(fl))
	reader := &DxfReader{
		inner: &innerDxfReader{
			val: C.dxf_open_reader(fl),
		},
	}
	runtime.SetFinalizer(reader.inner, (*innerDxfReader).free)
	return reader
}

func (t *DxfReader) IsFailed() bool {
	return bool(C.dxf_reader_is_failed(t.inner.val))
}

func (t *DxfReader) DoRead() {
	C.dxf_reader_do_read(t.inner.val)
}

func (t *DxfReader) GetError() string {
	return C.GoString(C.dxf_reader_get_error(t.inner.val))
}

func (t *DxfReader) HasError() bool {
	return bool(C.dxf_reader_has_error(t.inner.val))
}

func (t *DxfReader) GetLayerNames() []string {
	var count int
	names := C.dxf_reader_get_layer_names(t.inner.val, (*C.int)(unsafe.Pointer(&count)))
	defer C.dxf_layer_names_free(names)
	cNames := unsafe.Slice(names, count)
	sp := make([]string, 0, count)
	for _, name := range cNames {
		sp = append(sp, C.GoString(name))
	}
	return sp
}

type DxfShapeLayer struct {
	inner *innerDxfShapeLayer
}

type innerDxfShapeLayer struct {
	val *C.struct__dxf_shape_entity_layer_t
}

func (t *innerDxfShapeLayer) free() {
	C.dxf_shape_entity_layer_free(t.val)
}
func NewDxfShapeLayer() *DxfShapeLayer {
	layer := &DxfShapeLayer{
		inner: &innerDxfShapeLayer{
			val: C.dxf_shape_entity_layer_new(),
		},
	}
	runtime.SetFinalizer(layer.inner, (*innerDxfShapeLayer).free)
	return layer
}

// 向形状图层添加实体
func (l *DxfShapeLayer) AddEntity(entity *DxfShapeEntity) {
	C.dxf_shape_entity_layer_add(l.inner.val, entity.inner.val)
}

func (t *DxfReader) GetLayer(name string) *DxfShapeLayer {
	cName := C.CString(name)
	defer C.free(unsafe.Pointer(cName))
	layer := &DxfShapeLayer{
		inner: &innerDxfShapeLayer{
			val: C.dxf_reader_get_shape_entity_layer(t.inner.val, cName),
		},
	}
	runtime.SetFinalizer(layer.inner, (*innerDxfShapeLayer).free)
	return layer
}

func (t *DxfShapeLayer) GetShapeEntityCount() int {
	return int(C.dxf_shape_entity_layer_get_count(t.inner.val))
}

type DxfShapeEntity struct {
	inner *innerDxfShapeEntity
}

type innerDxfShapeEntity struct {
	val *C.struct__dxf_shape_entity_t
}

func (t *innerDxfShapeEntity) free() {
	C.dxf_shape_entity_free(t.val)
}

func NewDxfShapeEntity(shape *Shape, color int) *DxfShapeEntity {
	entity := &DxfShapeEntity{
		inner: &innerDxfShapeEntity{
			val: C.dxf_shape_entity_new(shape.inner.val, C.int(color)),
		},
	}
	runtime.SetFinalizer(entity.inner, (*innerDxfShapeEntity).free)
	return entity
}

func (t *DxfShapeLayer) GetShapeEntity(index int) *DxfShapeEntity {
	entity := &DxfShapeEntity{
		inner: &innerDxfShapeEntity{
			val: C.dxf_shape_entity_layer_get_entity(t.inner.val, C.int(index)),
		},
	}
	runtime.SetFinalizer(entity.inner, (*innerDxfShapeEntity).free)
	return entity
}

func (t *DxfShapeLayer) GetShapeEntities() []*DxfShapeEntity {
	count := t.GetShapeEntityCount()
	sp := make([]*DxfShapeEntity, 0, count)
	for i := 0; i < count; i++ {
		sp = append(sp, t.GetShapeEntity(i))
	}
	return sp
}

func (t *DxfShapeLayer) GetShapes() []*Shape {
	count := t.GetShapeEntityCount()
	sp := make([]*Shape, 0, count)
	for i := 0; i < count; i++ {
		sp = append(sp, t.GetShapeEntity(i).GetShape())
	}
	return sp
}

func (t *DxfShapeEntity) GetColor() Color {
	return Color{val: C.dxf_shape_entity_get_color(t.inner.val)}
}

func (t *DxfShapeEntity) GetShape() *Shape {
	return NewShape(C.dxf_shape_entity_get_shape(t.inner.val))
}

func (t *DxfReader) GetTextLayer(name string) *DxfTextLayer {
	cName := C.CString(name)
	defer C.free(unsafe.Pointer(cName))
	layer := &DxfTextLayer{
		inner: &innerDxfTextLayer{
			val: C.dxf_reader_get_text_entity_layer(t.inner.val, cName),
		},
	}
	runtime.SetFinalizer(layer.inner, (*innerDxfTextLayer).free)
	return layer
}

type DxfTextLayer struct {
	inner *innerDxfTextLayer
}

type innerDxfTextLayer struct {
	val *C.struct__dxf_text_entity_layer_t
}

func (t *innerDxfTextLayer) free() {
	C.dxf_text_entity_layer_free(t.val)
}

func NewDxfTextLayer() *DxfTextLayer {
	layer := &DxfTextLayer{
		inner: &innerDxfTextLayer{
			val: C.dxf_text_entity_layer_new(),
		},
	}
	runtime.SetFinalizer(layer.inner, (*innerDxfTextLayer).free)
	return layer
}

func (l *DxfTextLayer) AddEntity(entity *DxfTextEntity) {
	C.dxf_text_entity_layer_add_entity(l.inner.val, entity.inner.val)
}

func (t *DxfTextLayer) GetCount() int {
	return int(C.dxf_text_entity_layer_get_count(t.inner.val))
}

func (t *DxfTextLayer) GetEntity(index int) *DxfTextEntity {
	entity := &DxfTextEntity{
		inner: &innerDxfTextEntity{
			val: C.dxf_text_entity_layer_get_entity(t.inner.val, C.int(index)),
		},
	}
	runtime.SetFinalizer(entity.inner, (*innerDxfTextEntity).free)
	return entity
}

func (t *DxfTextLayer) GetEntities() []*DxfTextEntity {
	count := t.GetCount()
	sp := make([]*DxfTextEntity, 0, count)
	for i := 0; i < count; i++ {
		sp = append(sp, t.GetEntity(i))
	}
	return sp
}

type DxfTextEntity struct {
	inner *innerDxfTextEntity
}

type innerDxfTextEntity struct {
	val *C.struct__dxf_text_entity_t
}

func NewDxfTextEntity(text string, position Point3, height, rotation float64, color int) *DxfTextEntity {
	cText := C.CString(text)
	defer C.free(unsafe.Pointer(cText))

	entity := &DxfTextEntity{
		inner: &innerDxfTextEntity{
			val: C.dxf_text_entity_new(
				cText,
				position.val,
				C.double(height),
				C.double(rotation),
				C.int(color)),
		},
	}
	runtime.SetFinalizer(entity.inner, (*innerDxfTextEntity).free)
	return entity
}

func (t *innerDxfTextEntity) free() {
	C.dxf_text_entity_free(t.val)
}

func (t *DxfTextEntity) GetText() string {
	return C.GoString(C.dxf_text_entity_get_text(t.inner.val))
}

func (t *DxfTextEntity) GetPosition() Point3 {
	return Point3{val: C.dxf_text_entity_get_position(t.inner.val)}
}

func (t *DxfTextEntity) GetNormal() Vector3 {
	return Vector3{val: C.dxf_text_entity_get_normal(t.inner.val)}
}

func (t *DxfTextEntity) GetXAxisDir() Vector3 {
	return Vector3{val: C.dxf_text_entity_get_x_axis_dir(t.inner.val)}
}

func (t *DxfTextEntity) GetAxis3() Axis3 {
	return NewAxis3FromNVX(t.GetPosition(), NewDir3FromVector(t.GetNormal()), NewDir3FromVector(t.GetXAxisDir()))
}

type DxfWriter struct {
	inner *innerDxfWriter
}

type innerDxfWriter struct {
	val *C.struct__dxf_writer_t
}

func (t *innerDxfWriter) free() {
	C.dxf_writer_free(t.val)
}

func NewDxfWriter(filename string) *DxfWriter {
	cFilename := C.CString(filename)
	defer C.free(unsafe.Pointer(cFilename))

	writer := &DxfWriter{
		inner: &innerDxfWriter{
			val: C.dxf_open_writer(cFilename),
		},
	}
	runtime.SetFinalizer(writer.inner, (*innerDxfWriter).free)
	return writer
}

func (w *DxfWriter) AddShape(layerName string, shape *Shape, index int) {
	cLayerName := C.CString(layerName)
	defer C.free(unsafe.Pointer(cLayerName))

	C.dxf_writer_add_shape(w.inner.val, cLayerName, shape.inner.val, C.int(index))
}

func (w *DxfWriter) AddText(layerName, text string, position Point3, height, rotation float64, index int) {
	cLayerName := C.CString(layerName)
	defer C.free(unsafe.Pointer(cLayerName))

	cText := C.CString(text)
	defer C.free(unsafe.Pointer(cText))

	C.dxf_writer_add_text(w.inner.val, cLayerName, cText, position.val,
		C.double(height), C.double(rotation), C.int(index))
}

func (w *DxfWriter) AddShapeLayer(name string, layer *DxfShapeLayer) {
	cName := C.CString(name)
	defer C.free(unsafe.Pointer(cName))

	C.dxf_writer_add_shape_layer(w.inner.val, cName, layer.inner.val)
}

func (w *DxfWriter) AddTextLayer(name string, layer *DxfTextLayer) {
	cName := C.CString(name)
	defer C.free(unsafe.Pointer(cName))

	C.dxf_writer_add_text_layer(w.inner.val, cName, layer.inner.val)
}

func (w *DxfWriter) Write() bool {
	return bool(C.dxf_writer_write(w.inner.val))
}
