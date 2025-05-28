package topo

/*
#include <stdlib.h>
#include "ifc_c_api.h"
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

type IfcColor struct {
	R, G, B float64
}

type IfcElement struct {
	Shape    *Shape
	Id       int
	ParentId int
	Name     string
	Guid     string
}

type IfcTriangulationMaterial struct {
	Name         string
	Diffuse      IfcColor
	Surface      IfcColor
	Specular     IfcColor
	Specularity  float64
	Transparency float64
}

type IfcConverter struct {
	ptr *C.ifc_convert_t
}

func NewIfcConverter() *IfcConverter {
	return &IfcConverter{ptr: C.ifc_convert_new()}
}

func (c *IfcConverter) Free() {
	if c.ptr != nil {
		C.ifc_convert_free(c.ptr)
		c.ptr = nil
	}
}

func (c *IfcConverter) Load(filename string) bool {
	fl := C.CString(filename)
	defer C.free(unsafe.Pointer(fl))
	return bool(C.ifc_convert_load(c.ptr, fl))
}

func (c *IfcConverter) GetVersion() string {
	ver := C.ifc_convert_get_version(c.ptr)
	defer C.free(unsafe.Pointer(ver))
	return C.GoString(ver)
}

func (c *IfcConverter) GetElements() []*IfcElement {
	count := 0
	elements := []*IfcElement{}
	res := C.ifc_convert_get_elements(c.ptr, (*C.int)(unsafe.Pointer(&count)))
	if count == 0 {
		return elements
	}
	defer C.ifc_elements_free(res)

	for i := 0; i < count; i++ {
		element := C.ifc_get_element(res, C.int(i))
		shp := NewShape(C.ifc_element_get_shape(element))
		elements = append(elements, &IfcElement{
			Shape:    shp,
			Id:       int(C.ifc_element_get_id(element)),
			ParentId: int(C.ifc_element_get_parent_id(element)),
			Name:     C.GoString(C.ifc_element_get_name(element)),
			Guid:     C.GoString(C.ifc_element_get_guid(element)),
		})
	}
	return elements
}

func (c *IfcConverter) GetTriangulations() []*IfcTriangulation {
	count := 0
	tris := []*IfcTriangulation{}
	res := C.ifc_convert_get_triangulations(c.ptr, (*C.int)(unsafe.Pointer(&count)))
	if count == 0 {
		return tris
	}
	defer C.ifc_triangulations_free(res)

	for i := 0; i < count; i++ {
		tri := &IfcTriangulation{}
		tri.inner = &innerTriangulation{C.ifc_get_triangulation(res, C.int(i))}
		runtime.SetFinalizer(tri.inner, (*innerTriangulation).free)
		tris = append(tris, tri)
	}
	return tris
}

func IfcToElements(f string) []*IfcElement {
	fl := C.CString(f)
	defer C.free(unsafe.Pointer(fl))
	count := 0
	elements := []*IfcElement{}
	res := C.ifc_get_elements(fl, (*C.int)(unsafe.Pointer(&count)))
	if count == 0 {
		return elements
	}
	defer C.ifc_elements_free(res)
	for i := 0; i < count; i++ {
		element := C.ifc_get_element(res, C.int(i))
		shp := NewShape(C.ifc_element_get_shape(element))
		elements = append(elements, &IfcElement{
			Shape:    shp,
			Id:       int(C.ifc_element_get_id(element)),
			ParentId: int(C.ifc_element_get_parent_id(element)),
			Name:     C.GoString(C.ifc_element_get_name(element)),
			Guid:     C.GoString(C.ifc_element_get_guid(element)),
		})
	}
	return elements
}

func IfcToTriangulations(f string) []*IfcTriangulation {
	fl := C.CString(f)
	defer C.free(unsafe.Pointer(fl))
	count := 0
	tris := []*IfcTriangulation{}
	res := C.ifc_get_triangulations(fl, (*C.int)(unsafe.Pointer(&count)))
	if count == 0 {
		return tris
	}
	defer C.ifc_triangulations_free(res)

	for i := 0; i < count; i++ {
		tri := &IfcTriangulation{}
		tri.inner = &innerTriangulation{C.ifc_get_triangulation(res, C.int(i))}
		runtime.SetFinalizer(tri.inner, (*innerTriangulation).free)
		tris = append(tris, tri)
	}
	return tris
}

func IsIfc(f string) bool {
	fl := C.CString(f)
	defer C.free(unsafe.Pointer(fl))
	return bool(C.is_ifc_file(fl))
}

type IfcTriangulation struct {
	inner *innerTriangulation
}

type innerTriangulation struct {
	ptr *C.ifc_triangulation_t
}

func (t *innerTriangulation) free() {
	if t.ptr != nil {
		C.ifc_triangulation_free(t.ptr)
		t.ptr = nil
	}
}

func (t *IfcTriangulation) GetVerts() []float64 {
	count := 0
	verts := C.ifc_triangulation_get_verts(t.inner.ptr, (*C.int)(unsafe.Pointer(&count)))
	rets := []float64{}
	copy(rets, (*[1 << 30]float64)(unsafe.Pointer(verts))[:count:count])
	return rets
}

func (t *IfcTriangulation) GetFaces() []int32 {
	count := 0
	faces := C.ifc_triangulation_get_faces(t.inner.ptr, (*C.int)(unsafe.Pointer(&count)))
	rets := []int32{}
	copy(rets, (*[1 << 30]int32)(unsafe.Pointer(faces))[:count:count])
	return rets
}

func (t *IfcTriangulation) GetNormals() []float64 {
	count := 0
	normals := C.ifc_triangulation_get_normals(t.inner.ptr, (*C.int)(unsafe.Pointer(&count)))
	rets := []float64{}
	copy(rets, (*[1 << 30]float64)(unsafe.Pointer(normals))[:count:count])
	return rets
}

func (t *IfcTriangulation) GetEdges() []int32 {
	count := 0
	edges := C.ifc_triangulation_get_edges(t.inner.ptr, (*C.int)(unsafe.Pointer(&count)))
	rets := []int32{}
	copy(rets, (*[1 << 30]int32)(unsafe.Pointer(edges))[:count:count])
	return rets
}

func (t *IfcTriangulation) GetUVs() []float64 {
	count := 0
	uvs := C.ifc_triangulation_get_uvs(t.inner.ptr, (*C.int)(unsafe.Pointer(&count)))
	rets := []float64{}
	copy(rets, (*[1 << 30]float64)(unsafe.Pointer(uvs))[:count:count])
	return rets
}

func (t *IfcTriangulation) GetMaterialIds() []int32 {
	count := 0
	ids := C.ifc_triangulation_get_material_ids(t.inner.ptr, (*C.int)(unsafe.Pointer(&count)))
	rets := []int32{}
	copy(rets, (*[1 << 30]int32)(unsafe.Pointer(ids))[:count:count])
	return rets
}

func (t *IfcTriangulation) GetMaterials() []*IfcTriangulationMaterial {
	count := 0
	materials := []*IfcTriangulationMaterial{}
	res := C.ifc_triangulation_get_materials(t.inner.ptr, (*C.int)(unsafe.Pointer(&count)))
	if count == 0 {
		return materials
	}
	defer C.ifc_triangulation_materials_free(res)
	materialsSlice := (*[1 << 30]C.ifc_triangulation_material_t)(unsafe.Pointer(res))[:count:count]

	for i := 0; i < count; i++ {
		mtl := &materialsSlice[i]
		materials = append(materials, &IfcTriangulationMaterial{
			Name:         C.GoString(C.ifc_triangulation_material_get_name(mtl)),
			Diffuse:      toIfcColor(C.ifc_triangulation_material_get_diffuse(mtl)),
			Surface:      toIfcColor(C.ifc_triangulation_material_get_surface(mtl)),
			Specular:     toIfcColor(C.ifc_triangulation_material_get_specular(mtl)),
			Specularity:  float64(C.ifc_triangulation_material_get_specularity(mtl)),
			Transparency: float64(C.ifc_triangulation_material_get_transparency(mtl)),
		})
	}
	return materials
}

func (t *IfcTriangulation) GetItemIds() []int32 {
	count := 0
	ids := C.ifc_triangulation_get_item_ids(t.inner.ptr, (*C.int)(unsafe.Pointer(&count)))
	rets := []int32{}
	copy(rets, (*[1 << 30]int32)(unsafe.Pointer(ids))[:count:count])
	return rets
}

func (t *IfcTriangulation) GetEdgesItemIds() []int32 {
	count := 0
	ids := C.ifc_triangulation_get_edges_item_ids(t.inner.ptr, (*C.int)(unsafe.Pointer(&count)))
	rets := []int32{}
	copy(rets, (*[1 << 30]int32)(unsafe.Pointer(ids))[:count:count])
	return rets
}

func toIfcColor(c C.ifc_color_t) IfcColor {
	return IfcColor{
		R: float64(c.r),
		G: float64(c.g),
		B: float64(c.b),
	}
}
