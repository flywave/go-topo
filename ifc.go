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
	Shape     *Shape
	Id        int
	ParentId  int
	Name      string
	Guid      string
	Type      string
	Transform *[16]float64
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
	inner *innerIfcConverter
}

type innerIfcConverter struct {
	ptr *C.ifc_convert_t
}

func (c *innerIfcConverter) free() {
	if c.ptr != nil {
		C.ifc_convert_free(c.ptr)
		c.ptr = nil
	}
}

func NewIfcConverter() *IfcConverter {
	converter := &IfcConverter{
		inner: &innerIfcConverter{
			ptr: C.ifc_convert_new(),
		},
	}
	runtime.SetFinalizer(converter.inner, (*innerIfcConverter).free)
	return converter
}

func (c *IfcConverter) Load(filename string) bool {
	fl := C.CString(filename)
	defer C.free(unsafe.Pointer(fl))
	return bool(C.ifc_convert_load(c.inner.ptr, fl))
}

func (c *IfcConverter) GetVersion() string {
	ver := C.ifc_convert_get_version(c.inner.ptr)
	defer C.free(unsafe.Pointer(ver))
	return C.GoString(ver)
}

func (c *IfcConverter) GetElements() []*IfcElement {
	var count C.int = 0
	elements := []*IfcElement{}
	res := C.ifc_convert_get_elements(c.inner.ptr, (*C.int)(unsafe.Pointer(&count)))
	if count == 0 {
		return elements
	}
	defer C.ifc_elements_free(res)

	for i := 0; i < int(count); i++ {
		element := C.ifc_get_element(res, C.int(i))
		shp := NewShape(C.ifc_element_get_shape(element))
		mat := (*[16]float64)(nil)
		trans := C.ifc_element_get_transform(element)
		if trans != nil {
			goSlice := *(*[16]float64)(unsafe.Pointer(trans))
			mat = &goSlice
		}
		elements = append(elements, &IfcElement{
			Shape:     shp,
			Id:        int(C.ifc_element_get_id(element)),
			ParentId:  int(C.ifc_element_get_parent_id(element)),
			Name:      C.GoString(C.ifc_element_get_name(element)),
			Guid:      C.GoString(C.ifc_element_get_guid(element)),
			Type:      C.GoString(C.ifc_element_get_type(element)),
			Transform: mat,
		})

	}
	return elements
}

func (c *IfcConverter) GetTriangulations() []*IfcTriangulation {
	count := 0
	tris := []*IfcTriangulation{}
	res := C.ifc_convert_get_triangulations(c.inner.ptr, (*C.int)(unsafe.Pointer(&count)))
	if count == 0 {
		return tris
	}
	defer C.ifc_triangulations_free(res)

	for i := 0; i < count; i++ {
		inner := &innerTriangulation{C.ifc_get_triangulation(res, C.int(i))}
		tri := &IfcTriangulation{
			inner:    inner,
			Id:       int(C.ifc_triangulation_get_id(inner.ptr)),
			ParentId: int(C.ifc_triangulation_get_parent_id(inner.ptr)),
			Name:     C.GoString(C.ifc_triangulation_get_name(inner.ptr)),
			Guid:     C.GoString(C.ifc_triangulation_get_guid(inner.ptr)),
			Type:     C.GoString(C.ifc_triangulation_get_type(inner.ptr)),
		}
		ary := C.ifc_triangulation_get_transform(tri.inner.ptr)
		mat := (*[16]float64)(nil)
		if ary != nil {
			goSlice := *(*[16]float64)(unsafe.Pointer(ary))
			mat = &goSlice
		}
		tri.Transform = mat
		runtime.SetFinalizer(tri.inner, (*innerTriangulation).free)
		tris = append(tris, tri)
	}
	return tris
}

func (c *IfcConverter) GetData() *IfcData {
	data := &IfcData{
		inner: &innerIfcData{
			ptr: C.ifc_convert_get_data(c.inner.ptr),
		},
	}
	runtime.SetFinalizer(data.inner, (*innerIfcData).free)
	return data
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
			Type:     C.GoString(C.ifc_element_get_type(element)),
		})
	}
	return elements
}

func IfcToTriangulations(f string) []*IfcTriangulation {
	fl := C.CString(f)
	defer C.free(unsafe.Pointer(fl))
	var count C.int
	tris := []*IfcTriangulation{}
	res := C.ifc_get_triangulations(fl, (*C.int)(unsafe.Pointer(&count)))
	if count == 0 {
		return tris
	}
	defer C.ifc_triangulations_free(res)

	for i := 0; i < int(count); i++ {
		inner := &innerTriangulation{C.ifc_get_triangulation(res, C.int(i))}
		tri := &IfcTriangulation{
			inner:    inner,
			Id:       int(C.ifc_triangulation_get_id(inner.ptr)),
			ParentId: int(C.ifc_triangulation_get_parent_id(inner.ptr)),
			Name:     C.GoString(C.ifc_triangulation_get_name(inner.ptr)),
			Guid:     C.GoString(C.ifc_triangulation_get_guid(inner.ptr)),
			Type:     C.GoString(C.ifc_triangulation_get_type(inner.ptr)),
		}
		ary := C.ifc_triangulation_get_transform(tri.inner.ptr)
		mat := (*[16]float64)(nil)
		if ary != nil {
			goSlice := *(*[16]float64)(unsafe.Pointer(ary))
			mat = &goSlice
		}
		tri.Transform = mat
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
	inner     *innerTriangulation
	Id        int
	ParentId  int
	Name      string
	Guid      string
	Type      string
	Transform *[16]float64
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
	rets := make([]float64, count)
	copy(rets, (*[1 << 30]float64)(unsafe.Pointer(verts))[:count:count])
	return rets
}

func (t *IfcTriangulation) GetFaces() []int32 {
	count := 0
	faces := C.ifc_triangulation_get_faces(t.inner.ptr, (*C.int)(unsafe.Pointer(&count)))
	rets := make([]int32, count)
	copy(rets, (*[1 << 30]int32)(unsafe.Pointer(faces))[:count:count])
	return rets
}

func (t *IfcTriangulation) GetNormals() []float64 {
	count := 0
	normals := C.ifc_triangulation_get_normals(t.inner.ptr, (*C.int)(unsafe.Pointer(&count)))
	if count == 0 {
		return nil
	}
	rets := make([]float64, count)
	copy(rets, (*[1 << 30]float64)(unsafe.Pointer(normals))[:count:count])
	return rets
}

func (t *IfcTriangulation) GetEdges() []int32 {
	count := 0
	edges := C.ifc_triangulation_get_edges(t.inner.ptr, (*C.int)(unsafe.Pointer(&count)))
	if count == 0 {
		return nil
	}
	rets := make([]int32, count)
	copy(rets, (*[1 << 30]int32)(unsafe.Pointer(edges))[:count:count])
	return rets
}

func (t *IfcTriangulation) GetUVs() []float64 {
	count := 0
	uvs := C.ifc_triangulation_get_uvs(t.inner.ptr, (*C.int)(unsafe.Pointer(&count)))
	if count == 0 {
		return nil
	}
	rets := make([]float64, count)
	copy(rets, (*[1 << 30]float64)(unsafe.Pointer(uvs))[:count:count])
	return rets
}

func (t *IfcTriangulation) GetMaterialIds() []int32 {
	count := 0
	ids := C.ifc_triangulation_get_material_ids(t.inner.ptr, (*C.int)(unsafe.Pointer(&count)))
	if count == 0 {
		return nil
	}
	rets := make([]int32, count)
	copy(rets, (*[1 << 30]int32)(unsafe.Pointer(ids))[:count:count])
	return rets
}

func (t *IfcTriangulation) GetMaterials() []*IfcTriangulationMaterial {
	var count C.int
	res := C.ifc_triangulation_get_materials(t.inner.ptr, &count)
	if res == nil || count == 0 {
		return nil
	}
	defer C.ifc_triangulation_materials_free(res)

	materials := make([]*IfcTriangulationMaterial, 0, int(count))
	for i := 0; i < int(count); i++ {
		materials = append(materials, &IfcTriangulationMaterial{
			Name:         C.GoString(C.ifc_triangulation_material_get_name(res)),
			Diffuse:      toIfcColor(C.ifc_triangulation_material_get_diffuse(res)),
			Surface:      toIfcColor(C.ifc_triangulation_material_get_surface(res)),
			Specular:     toIfcColor(C.ifc_triangulation_material_get_specular(res)),
			Specularity:  float64(C.ifc_triangulation_material_get_specularity(res)),
			Transparency: float64(C.ifc_triangulation_material_get_transparency(res)),
		})
		sz := C.ifc_triangulation_material_size()
		res = (*C.ifc_triangulation_material_t)(unsafe.Pointer(uintptr(unsafe.Pointer(res)) + uintptr(sz)))
	}
	return materials
}

func (t *IfcTriangulation) GetItemIds() []int32 {
	count := 0
	ids := C.ifc_triangulation_get_item_ids(t.inner.ptr, (*C.int)(unsafe.Pointer(&count)))
	if count == 0 {
		return nil
	}
	rets := make([]int32, count)
	copy(rets, (*[1 << 30]int32)(unsafe.Pointer(ids))[:count:count])
	return rets
}

func (t *IfcTriangulation) GetEdgesItemIds() []int32 {
	count := 0
	ids := C.ifc_triangulation_get_edges_item_ids(t.inner.ptr, (*C.int)(unsafe.Pointer(&count)))
	rets := make([]int32, count)
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

type IfcData struct {
	inner *innerIfcData
}

type innerIfcData struct {
	ptr *C.ifc_data_t
}

func (d *innerIfcData) free() {
	if d.ptr != nil {
		C.ifc_data_free(d.ptr)
		d.ptr = nil
	}
}

func (d *IfcData) GetHeader() *IfcHeader {
	header := &IfcHeader{
		inner: &innerIfcHeader{
			ptr: C.ifc_data_get_header(d.inner.ptr),
		},
	}
	runtime.SetFinalizer(header.inner, (*innerIfcHeader).free)
	return header
}

func (d *IfcData) GetUnits() []*IfcUnit {
	count := 0
	units := []*IfcUnit{}
	res := C.ifc_data_get_units(d.inner.ptr, (*C.int)(unsafe.Pointer(&count)))
	if count == 0 {
		return units
	}
	defer C.ifc_data_free_units(res)

	for i := 0; i < count; i++ {
		unit := &IfcUnit{
			inner: &innerIfcUnit{
				ptr: *(**C.ifc_unit_t)(unsafe.Pointer(uintptr(unsafe.Pointer(res)) + uintptr(i)*unsafe.Sizeof(*res))),
			},
		}
		runtime.SetFinalizer(unit.inner, (*innerIfcUnit).free)
		units = append(units, unit)
	}
	return units
}

func (d *IfcData) GetPropertySets() []*IfcPropertySet {
	count := 0
	propertySets := []*IfcPropertySet{}
	res := C.ifc_data_get_properties(d.inner.ptr, (*C.int)(unsafe.Pointer(&count)))
	if count == 0 {
		return propertySets
	}
	defer C.ifc_data_free_properties(res)

	for i := 0; i < count; i++ {
		ps := &IfcPropertySet{
			inner: &innerIfcPropertySet{
				ptr: *(**C.ifc_property_set_t)(unsafe.Pointer(uintptr(unsafe.Pointer(res)) + uintptr(i)*unsafe.Sizeof(*res))),
			},
		}
		runtime.SetFinalizer(ps.inner, (*innerIfcPropertySet).Free)
		propertySets = append(propertySets, ps)
	}
	return propertySets
}

func (d *IfcData) GetQuantities() []*IfcElementQuantity {
	count := 0
	quantities := []*IfcElementQuantity{}
	res := C.ifc_data_get_quantities(d.inner.ptr, (*C.int)(unsafe.Pointer(&count)))
	if count == 0 {
		return quantities
	}
	defer C.ifc_data_free_quantities(res)

	for i := 0; i < count; i++ {
		eq := &IfcElementQuantity{
			inner: &innerIfcElementQuantity{
				ptr: *(**C.ifc_element_quantity_t)(unsafe.Pointer(uintptr(unsafe.Pointer(res)) + uintptr(i)*unsafe.Sizeof(*res))),
			},
		}
		runtime.SetFinalizer(eq.inner, (*innerIfcElementQuantity).free)
		quantities = append(quantities, eq)
	}
	return quantities
}

func (d *IfcData) GetWorkSchedules() []*IfcWorkSchedule {
	count := 0
	schedules := []*IfcWorkSchedule{}
	res := C.ifc_data_get_work_schedules(d.inner.ptr, (*C.int)(unsafe.Pointer(&count)))
	if count == 0 {
		return schedules
	}
	defer C.ifc_data_free_work_schedules(res)

	for i := 0; i < count; i++ {
		ws := &IfcWorkSchedule{
			inner: &innerIfcWorkSchedule{
				ptr: *(**C.ifc_work_schedule_t)(unsafe.Pointer(uintptr(unsafe.Pointer(res)) + uintptr(i)*unsafe.Sizeof(*res))),
			},
		}
		runtime.SetFinalizer(ws.inner, (*innerIfcWorkSchedule).free)
		schedules = append(schedules, ws)
	}
	return schedules
}

func (d *IfcData) GetWorkPlans() []*IfcWorkPlan {
	count := 0
	plans := []*IfcWorkPlan{}
	res := C.ifc_data_get_work_plans(d.inner.ptr, (*C.int)(unsafe.Pointer(&count)))
	if count == 0 {
		return plans
	}
	defer C.ifc_data_free_work_plans(res)

	for i := 0; i < count; i++ {
		wp := &IfcWorkPlan{
			inner: &innerIfcWorkPlan{
				ptr: *(**C.ifc_work_plan_t)(unsafe.Pointer(uintptr(unsafe.Pointer(res)) + uintptr(i)*unsafe.Sizeof(*res))),
			},
		}
		runtime.SetFinalizer(wp.inner, (*innerIfcWorkPlan).free)
		plans = append(plans, wp)
	}
	return plans
}

func (d *IfcData) GetCalendars() []*IfcWorkCalendar {
	count := 0
	calendars := []*IfcWorkCalendar{}
	res := C.ifc_data_get_calendars(d.inner.ptr, (*C.int)(unsafe.Pointer(&count)))
	if count == 0 {
		return calendars
	}
	defer C.ifc_data_free_calendars(res)

	for i := 0; i < count; i++ {
		wc := &IfcWorkCalendar{
			inner: &innerIfcWorkCalendar{
				ptr: *(**C.ifc_work_calendar_t)(unsafe.Pointer(uintptr(unsafe.Pointer(res)) + uintptr(i)*unsafe.Sizeof(*res))),
			},
		}
		runtime.SetFinalizer(wc.inner, (*innerIfcWorkCalendar).free)
		calendars = append(calendars, wc)
	}
	return calendars
}

func (d *IfcData) GetConnections() []*IfcConnection {
	count := 0
	connections := []*IfcConnection{}
	res := C.ifc_data_get_connections(d.inner.ptr, (*C.int)(unsafe.Pointer(&count)))
	if count == 0 {
		return connections
	}
	defer C.ifc_data_free_connections(res)

	for i := 0; i < count; i++ {
		conn := &IfcConnection{
			inner: &innerIfcConnection{
				ptr: *(**C.ifc_connection_t)(unsafe.Pointer(uintptr(unsafe.Pointer(res)) + uintptr(i)*unsafe.Sizeof(*res))),
			},
		}
		runtime.SetFinalizer(conn.inner, (*innerIfcConnection).free)
		connections = append(connections, conn)
	}
	return connections
}

func (d *IfcData) GetTypes() []*IfcTypeObject {
	count := 0
	types := []*IfcTypeObject{}
	res := C.ifc_data_get_types(d.inner.ptr, (*C.int)(unsafe.Pointer(&count)))
	if count == 0 {
		return types
	}
	defer C.ifc_data_free_types(res)

	for i := 0; i < count; i++ {
		typ := &IfcTypeObject{
			inner: &innerIfcTypeObject{
				ptr: *(**C.ifc_type_object_t)(unsafe.Pointer(uintptr(unsafe.Pointer(res)) + uintptr(i)*unsafe.Sizeof(*res))),
			},
		}
		runtime.SetFinalizer(typ.inner, (*innerIfcTypeObject).free)
		types = append(types, typ)
	}
	return types
}

func (d *IfcData) GetLayers() []*IfcLayer {
	count := 0
	layers := []*IfcLayer{}
	res := C.ifc_data_get_layers(d.inner.ptr, (*C.int)(unsafe.Pointer(&count)))
	if count == 0 {
		return layers
	}
	defer C.ifc_data_free_layers(res)

	for i := 0; i < count; i++ {
		layer := &IfcLayer{
			inner: &innerIfcLayer{
				ptr: *(**C.ifc_layer_t)(unsafe.Pointer(uintptr(unsafe.Pointer(res)) + uintptr(i)*unsafe.Sizeof(*res))),
			},
		}
		runtime.SetFinalizer(layer.inner, (*innerIfcLayer).free)
		layers = append(layers, layer)
	}
	return layers
}

func (d *IfcData) GetMaterials() []*IfcMaterial {
	count := 0
	materials := []*IfcMaterial{}
	res := C.ifc_data_get_materials(d.inner.ptr, (*C.int)(unsafe.Pointer(&count)))
	if count == 0 {
		return materials
	}
	defer C.ifc_data_free_materials(res)

	for i := 0; i < count; i++ {
		mtl := &IfcMaterial{
			inner: &innerIfcMaterial{
				ptr: *(**C.ifc_material_t)(unsafe.Pointer(uintptr(unsafe.Pointer(res)) + uintptr(i)*unsafe.Sizeof(*res))),
			},
		}
		runtime.SetFinalizer(mtl.inner, (*innerIfcMaterial).free)
		materials = append(materials, mtl)
	}
	return materials
}

func (d *IfcData) GetGroups() []*IfcGroup {
	count := 0
	groups := []*IfcGroup{}
	res := C.ifc_data_get_groups(d.inner.ptr, (*C.int)(unsafe.Pointer(&count)))
	if count == 0 {
		return groups
	}
	defer C.ifc_data_free_groups(res)

	for i := 0; i < count; i++ {
		group := &IfcGroup{
			inner: &innerIfcGroup{
				ptr: *(**C.ifc_group_t)(unsafe.Pointer(uintptr(unsafe.Pointer(res)) + uintptr(i)*unsafe.Sizeof(*res))),
			},
		}
		runtime.SetFinalizer(group.inner, (*innerIfcGroup).free)
		groups = append(groups, group)
	}
	return groups
}

func (d *IfcData) GetRelDefinesByTypes() []*IfcRelDefinesByType {
	count := 0
	rels := []*IfcRelDefinesByType{}
	res := C.ifc_data_get_rel_defines_by_types(d.inner.ptr, (*C.int)(unsafe.Pointer(&count)))
	if count == 0 {
		return rels
	}
	defer C.ifc_data_free_rel_defines_by_types(res)

	for i := 0; i < count; i++ {
		rel := &IfcRelDefinesByType{
			inner: &innerIfcRelDefinesByType{
				ptr: *(**C.ifc_rel_defines_by_type_t)(unsafe.Pointer(uintptr(unsafe.Pointer(res)) + uintptr(i)*unsafe.Sizeof(*res))),
			},
		}
		runtime.SetFinalizer(rel.inner, (*innerIfcRelDefinesByType).free)
		rels = append(rels, rel)
	}
	return rels
}

func (d *IfcData) GetRelDefinesByProperties() []*IfcRelDefinesByProperties {
	count := 0
	rels := []*IfcRelDefinesByProperties{}
	res := C.ifc_data_get_rel_defines_by_properties(d.inner.ptr, (*C.int)(unsafe.Pointer(&count)))
	if count == 0 {
		return rels
	}
	defer C.ifc_data_free_rel_defines_by_properties(res)

	for i := 0; i < count; i++ {
		rel := &IfcRelDefinesByProperties{
			inner: &innerIfcRelDefinesByProperties{
				ptr: *(**C.ifc_rel_defines_by_properties_t)(unsafe.Pointer(uintptr(unsafe.Pointer(res)) + uintptr(i)*unsafe.Sizeof(*res))),
			},
		}
		runtime.SetFinalizer(rel.inner, (*innerIfcRelDefinesByProperties).free)
		rels = append(rels, rel)
	}
	return rels
}

type IfcHeader struct {
	inner *innerIfcHeader
}

func (h *IfcHeader) GetImplementationLevel() string {
	level := C.ifc_header_get_implementation_level(h.inner.ptr)
	return C.GoString(level)
}

func (h *IfcHeader) GetDescriptions() []string {
	count := 0
	descriptions := C.ifc_header_get_descriptions(h.inner.ptr, (*C.int)(unsafe.Pointer(&count)))
	defer C.ifc_header_free_descriptions(descriptions)

	result := make([]string, count)
	for i := 0; i < count; i++ {
		result[i] = C.GoString(*(**C.char)(unsafe.Pointer(uintptr(unsafe.Pointer(descriptions)) + uintptr(i)*unsafe.Sizeof(*descriptions))))
	}
	return result
}

func (h *IfcHeader) GetFilename() string {
	filename := C.ifc_header_get_filename(h.inner.ptr)
	return C.GoString(filename)
}

func (h *IfcHeader) GetAuthors() []string {
	count := 0
	authors := C.ifc_header_get_authors(h.inner.ptr, (*C.int)(unsafe.Pointer(&count)))
	defer C.ifc_header_free_authors(authors)

	result := make([]string, count)
	for i := 0; i < count; i++ {
		result[i] = C.GoString(*(**C.char)(unsafe.Pointer(uintptr(unsafe.Pointer(authors)) + uintptr(i)*unsafe.Sizeof(*authors))))
	}
	return result
}

func (h *IfcHeader) GetOrganizations() []string {
	count := 0
	orgs := C.ifc_header_get_organizations(h.inner.ptr, (*C.int)(unsafe.Pointer(&count)))
	defer C.ifc_header_free_organizations(orgs)

	result := make([]string, count)
	for i := 0; i < count; i++ {
		result[i] = C.GoString(*(**C.char)(unsafe.Pointer(uintptr(unsafe.Pointer(orgs)) + uintptr(i)*unsafe.Sizeof(*orgs))))
	}
	return result
}

func (h *IfcHeader) GetTimestamp() string {
	timestamp := C.ifc_header_get_timestamp(h.inner.ptr)
	return C.GoString(timestamp)
}

func (h *IfcHeader) GetPreprocessorVersion() string {
	version := C.ifc_header_get_preprocessor_version(h.inner.ptr)
	return C.GoString(version)
}

func (h *IfcHeader) GetOriginatingSystem() string {
	system := C.ifc_header_get_originating_system(h.inner.ptr)
	return C.GoString(system)
}

func (h *IfcHeader) GetAuthorization() string {
	auth := C.ifc_header_get_authorization(h.inner.ptr)
	return C.GoString(auth)
}

func (h *IfcHeader) GetSchemaIdentifiers() []string {
	count := 0
	ids := C.ifc_header_get_schema_identifiers(h.inner.ptr, (*C.int)(unsafe.Pointer(&count)))
	defer C.ifc_header_free_schema_identifiers(ids)

	result := make([]string, count)
	for i := 0; i < count; i++ {
		result[i] = C.GoString(*(**C.char)(unsafe.Pointer(uintptr(unsafe.Pointer(ids)) + uintptr(i)*unsafe.Sizeof(*ids))))
	}
	return result
}

type innerIfcHeader struct {
	ptr *C.ifc_header_t
}

func (h *innerIfcHeader) free() {
	if h.ptr != nil {
		C.ifc_header_free(h.ptr)
		h.ptr = nil
	}
}

type IfcUnit struct {
	inner *innerIfcUnit
}

type innerIfcUnit struct {
	ptr *C.ifc_unit_t
}

func (u *innerIfcUnit) free() {
	if u.ptr != nil {
		C.ifc_unit_free(u.ptr)
		u.ptr = nil
	}
}

func (u *IfcUnit) GetType() string {
	unitType := C.ifc_unit_get_type(u.inner.ptr)
	return C.GoString(unitType)
}

func (u *IfcUnit) GetName() string {
	name := C.ifc_unit_get_name(u.inner.ptr)
	return C.GoString(name)
}

func (u *IfcUnit) HasSIEquivalent() bool {
	return bool(C.ifc_unit_has_SI_equivalent(u.inner.ptr))
}

func (u *IfcUnit) GetSIEquivalent() float64 {
	return float64(C.ifc_unit_get_SI_equivalent(u.inner.ptr))
}

type IfcProperty struct {
	inner *innerIfcProperty
}

type innerIfcProperty struct {
	ptr *C.ifc_property_t
}

func (p *innerIfcProperty) free() {
	if p.ptr != nil {
		C.ifc_property_free(p.ptr)
		p.ptr = nil
	}
}

func (p *IfcProperty) GetName() string {
	name := C.ifc_property_get_name(p.inner.ptr)
	return C.GoString(name)
}

func (p *IfcProperty) GetType() string {
	propType := C.ifc_property_get_type(p.inner.ptr)
	return C.GoString(propType)
}

func (p *IfcProperty) IsNull() bool {
	return bool(C.ifc_property_is_null(p.inner.ptr))
}

func (p *IfcProperty) IsInt() bool {
	return bool(C.ifc_property_is_int(p.inner.ptr))
}

func (p *IfcProperty) IsBool() bool {
	return bool(C.ifc_property_is_bool(p.inner.ptr))
}

func (p *IfcProperty) IsDouble() bool {
	return bool(C.ifc_property_is_double(p.inner.ptr))
}

func (p *IfcProperty) IsString() bool {
	return bool(C.ifc_property_is_string(p.inner.ptr))
}

func (p *IfcProperty) IsBitset() bool {
	return bool(C.ifc_property_is_bitset(p.inner.ptr))
}

func (p *IfcProperty) IsIntVector() bool {
	return bool(C.ifc_property_is_int_vector(p.inner.ptr))
}

func (p *IfcProperty) IsDoubleVector() bool {
	return bool(C.ifc_property_is_double_vector(p.inner.ptr))
}

func (p *IfcProperty) IsStringVector() bool {
	return bool(C.ifc_property_is_string_vector(p.inner.ptr))
}

func (p *IfcProperty) IsBitsetVector() bool {
	return bool(C.ifc_property_is_bitset_vector(p.inner.ptr))
}

func (p *IfcProperty) IsIntMatrix() bool {
	return bool(C.ifc_property_is_int_matrix(p.inner.ptr))
}

func (p *IfcProperty) IsDoubleMatrix() bool {
	return bool(C.ifc_property_is_double_matrix(p.inner.ptr))
}

func (p *IfcProperty) GetInt() int {
	return int(C.ifc_property_get_int(p.inner.ptr))
}

func (p *IfcProperty) GetBool() bool {
	return bool(C.ifc_property_get_bool(p.inner.ptr))
}

func (p *IfcProperty) GetDouble() float64 {
	return float64(C.ifc_property_get_double(p.inner.ptr))
}

func (p *IfcProperty) GetString() string {
	str := C.ifc_property_get_string(p.inner.ptr)
	return C.GoString(str)
}

func (p *IfcProperty) GetBitset() []byte {
	size := 0
	bits := C.ifc_property_get_bitset(p.inner.ptr, (*C.int)(unsafe.Pointer(&size)))
	return C.GoBytes(unsafe.Pointer(bits), C.int(size))
}

func (p *IfcProperty) GetIntVector() []int32 {
	count := 0
	vec := C.ifc_property_get_int_vector(p.inner.ptr, (*C.int)(unsafe.Pointer(&count)))
	rets := make([]int32, count)
	copy(rets, (*[1 << 30]int32)(unsafe.Pointer(vec))[:count:count])
	return rets
}

func (p *IfcProperty) GetDoubleVector() []float64 {
	count := 0
	vec := C.ifc_property_get_double_vector(p.inner.ptr, (*C.int)(unsafe.Pointer(&count)))
	rets := make([]float64, count)
	copy(rets, (*[1 << 30]float64)(unsafe.Pointer(vec))[:count:count])
	return rets
}

func (p *IfcProperty) GetStringVector() []string {
	count := 0
	vec := C.ifc_property_get_string_vector(p.inner.ptr, (*C.int)(unsafe.Pointer(&count)))
	rets := make([]string, count)
	for i := 0; i < count; i++ {
		rets[i] = C.GoString(*(**C.char)(unsafe.Pointer(uintptr(unsafe.Pointer(vec)) + uintptr(i)*unsafe.Sizeof(*vec))))
	}
	return rets
}

func (p *IfcProperty) GetBitsetVector() [][]byte {
	count := 0
	sizesPtr := (*C.int)(nil)
	vec := C.ifc_property_get_bitset_vector(p.inner.ptr, (*C.int)(unsafe.Pointer(&count)), (**C.int)(unsafe.Pointer(&sizesPtr)))
	if count == 0 {
		return nil
	}
	defer C.ifc_property_free_vector(unsafe.Pointer(vec))
	defer C.ifc_property_free_vector(unsafe.Pointer(sizesPtr))

	sizes := (*[1 << 30]C.int)(unsafe.Pointer(sizesPtr))[:count:count]
	result := make([][]byte, count)

	for i := 0; i < count; i++ {
		size := int(sizes[i])
		bits := *(*[]byte)(unsafe.Pointer(&struct {
			ptr *C.uchar
			len int
		}{*(**C.uchar)(unsafe.Pointer(uintptr(unsafe.Pointer(vec)) + uintptr(i)*unsafe.Sizeof(*vec))), size}))
		result[i] = make([]byte, size)
		copy(result[i], bits)
	}
	return result
}

func (p *IfcProperty) GetIntMatrix() [][]int32 {
	rows := 0
	cols := 0
	matrix := C.ifc_property_get_int_matrix(p.inner.ptr, (*C.int)(unsafe.Pointer(&rows)), (*C.int)(unsafe.Pointer(&cols)))
	if rows == 0 || cols == 0 {
		return nil
	}
	defer func() {
		matrixSlice := (*[1 << 30]unsafe.Pointer)(unsafe.Pointer(&matrix))[:rows:rows]
		C.ifc_property_free_matrix(&matrixSlice[0], C.int(rows))
	}()

	result := make([][]int32, rows)
	for i := 0; i < rows; i++ {
		row := (*[1 << 30]C.int)(unsafe.Pointer(*(**C.int)(unsafe.Pointer(uintptr(unsafe.Pointer(matrix)) + uintptr(i)*unsafe.Sizeof(*matrix)))))[:cols:cols]
		result[i] = make([]int32, cols)
		for j := 0; j < cols; j++ {
			result[i][j] = int32(row[j])
		}
	}
	return result
}

func (p *IfcProperty) GetDoubleMatrix() [][]float64 {
	rows := 0
	cols := 0
	matrix := C.ifc_property_get_double_matrix(p.inner.ptr, (*C.int)(unsafe.Pointer(&rows)), (*C.int)(unsafe.Pointer(&cols)))
	if rows == 0 || cols == 0 {
		return nil
	}
	defer func() {
		matrixSlice := (*[1 << 30]unsafe.Pointer)(unsafe.Pointer(&matrix))[:rows:rows]
		C.ifc_property_free_matrix(&matrixSlice[0], C.int(rows))
	}()

	result := make([][]float64, rows)
	for i := 0; i < rows; i++ {
		row := (*[1 << 30]C.double)(unsafe.Pointer(*(**C.double)(unsafe.Pointer(uintptr(unsafe.Pointer(matrix)) + uintptr(i)*unsafe.Sizeof(*matrix)))))[:cols:cols]
		result[i] = make([]float64, cols)
		for j := 0; j < cols; j++ {
			result[i][j] = float64(row[j])
		}
	}
	return result
}

func (p *IfcProperty) GetValue() interface{} {
	switch {
	case p.IsNull():
		return nil
	case p.IsInt():
		return p.GetInt()
	case p.IsBool():
		return p.GetBool()
	case p.IsDouble():
		return p.GetDouble()
	case p.IsString():
		return p.GetString()
	case p.IsBitset():
		return p.GetBitset()
	case p.IsIntVector():
		return p.GetIntVector()
	case p.IsDoubleVector():
		return p.GetDoubleVector()
	case p.IsStringVector():
		return p.GetStringVector()
	case p.IsBitsetVector():
		return p.GetBitsetVector()
	case p.IsIntMatrix():
		return p.GetIntMatrix()
	case p.IsDoubleMatrix():
		return p.GetDoubleMatrix()
	default:
		return nil
	}
}

type IfcPropertySet struct {
	inner *innerIfcPropertySet
}

type innerIfcPropertySet struct {
	ptr *C.ifc_property_set_t
}

func (ps *innerIfcPropertySet) Free() {
	if ps.ptr != nil {
		C.ifc_property_set_free(ps.ptr)
		ps.ptr = nil
	}
}

func (ps *IfcPropertySet) GetID() string {
	id := C.ifc_property_set_get_id(ps.inner.ptr)
	return C.GoString(id)
}

func (ps *IfcPropertySet) GetName() string {
	name := C.ifc_property_set_get_name(ps.inner.ptr)
	return C.GoString(name)
}

func (ps *IfcPropertySet) GetProperties() []*IfcProperty {
	count := 0
	properties := []*IfcProperty{}
	res := C.ifc_property_set_get_properties(ps.inner.ptr, (*C.int)(unsafe.Pointer(&count)))
	if count == 0 {
		return properties
	}
	defer C.ifc_property_set_free_properties(res)

	for i := 0; i < count; i++ {
		prop := &IfcProperty{
			inner: &innerIfcProperty{
				ptr: *(**C.ifc_property_t)(unsafe.Pointer(uintptr(unsafe.Pointer(res)) + uintptr(i)*unsafe.Sizeof(*res))),
			},
		}
		runtime.SetFinalizer(prop.inner, (*innerIfcProperty).free)
		properties = append(properties, prop)
	}
	return properties
}

type IfcQuantity struct {
	inner *innerIfcQuantity
}

type innerIfcQuantity struct {
	ptr *C.ifc_quantity_t
}

func (q *innerIfcQuantity) free() {
	if q.ptr != nil {
		C.ifc_quantity_free(q.ptr)
		q.ptr = nil
	}
}

func (q *IfcQuantity) GetType() string {
	qType := C.ifc_quantity_get_type(q.inner.ptr)
	return C.GoString(qType)
}

func (q *IfcQuantity) GetName() string {
	name := C.ifc_quantity_get_name(q.inner.ptr)
	return C.GoString(name)
}

func (q *IfcQuantity) GetValue() float64 {
	return float64(C.ifc_quantity_get_value(q.inner.ptr))
}

func (q *IfcQuantity) GetUnit() string {
	unit := C.ifc_quantity_get_unit(q.inner.ptr)
	return C.GoString(unit)
}

type IfcElementQuantity struct {
	inner *innerIfcElementQuantity
}

type innerIfcElementQuantity struct {
	ptr *C.ifc_element_quantity_t
}

func (eq *innerIfcElementQuantity) free() {
	if eq.ptr != nil {
		C.ifc_element_quantity_free(eq.ptr)
		eq.ptr = nil
	}
}

func (eq *IfcElementQuantity) GetID() string {
	id := C.ifc_element_quantity_get_id(eq.inner.ptr)
	return C.GoString(id)
}

func (eq *IfcElementQuantity) GetName() string {
	name := C.ifc_element_quantity_get_name(eq.inner.ptr)
	return C.GoString(name)
}

func (eq *IfcElementQuantity) GetQuantities() []*IfcQuantity {
	count := 0
	quantities := []*IfcQuantity{}
	res := C.ifc_element_quantity_get_quantities(eq.inner.ptr, (*C.int)(unsafe.Pointer(&count)))
	if count == 0 {
		return quantities
	}
	defer C.ifc_element_quantity_free_quantities(res)

	for i := 0; i < count; i++ {
		qty := &IfcQuantity{
			inner: &innerIfcQuantity{
				ptr: *(**C.ifc_quantity_t)(unsafe.Pointer(uintptr(unsafe.Pointer(res)) + uintptr(i)*unsafe.Sizeof(*res))),
			},
		}
		runtime.SetFinalizer(qty.inner, (*innerIfcQuantity).free)
		quantities = append(quantities, qty)
	}
	return quantities
}

type IfcTaskTime struct {
	inner *innerIfcTaskTime
}

type innerIfcTaskTime struct {
	ptr *C.ifc_task_time_t
}

func (tt *innerIfcTaskTime) free() {
	if tt.ptr != nil {
		C.ifc_task_time_free(tt.ptr)
		tt.ptr = nil
	}
}

func (tt *IfcTaskTime) GetScheduleStart() string {
	start := C.ifc_task_time_get_schedule_start(tt.inner.ptr)
	return C.GoString(start)
}

func (tt *IfcTaskTime) GetScheduleFinish() string {
	finish := C.ifc_task_time_get_schedule_finish(tt.inner.ptr)
	return C.GoString(finish)
}

func (tt *IfcTaskTime) GetActualStart() string {
	start := C.ifc_task_time_get_actual_start(tt.inner.ptr)
	return C.GoString(start)
}

func (tt *IfcTaskTime) GetActualFinish() string {
	finish := C.ifc_task_time_get_actual_finish(tt.inner.ptr)
	return C.GoString(finish)
}

func (tt *IfcTaskTime) GetFreeFloat() string {
	float := C.ifc_task_time_get_free_float(tt.inner.ptr)
	return C.GoString(float)
}

func (tt *IfcTaskTime) GetTotalFloat() string {
	float := C.ifc_task_time_get_total_float(tt.inner.ptr)
	return C.GoString(float)
}

func (tt *IfcTaskTime) IsCritical() bool {
	return bool(C.ifc_task_time_is_critical(tt.inner.ptr))
}

type IfcTask struct {
	inner *innerIfcTask
}

type innerIfcTask struct {
	ptr *C.ifc_task_t
}

func (t *innerIfcTask) free() {
	if t.ptr != nil {
		C.ifc_task_free(t.ptr)
		t.ptr = nil
	}
}

// 基本属性方法
func (t *IfcTask) GetID() string {
	id := C.ifc_task_get_id(t.inner.ptr)
	return C.GoString(id)
}

func (t *IfcTask) GetName() string {
	name := C.ifc_task_get_name(t.inner.ptr)
	return C.GoString(name)
}

func (t *IfcTask) GetStatus() string {
	status := C.ifc_task_get_status(t.inner.ptr)
	return C.GoString(status)
}

func (t *IfcTask) GetDescription() string {
	desc := C.ifc_task_get_description(t.inner.ptr)
	return C.GoString(desc)
}

func (t *IfcTask) GetObjectType() string {
	objType := C.ifc_task_get_object_type(t.inner.ptr)
	return C.GoString(objType)
}

// 任务时间
func (t *IfcTask) GetTaskTime() *IfcTaskTime {
	tt := &IfcTaskTime{
		inner: &innerIfcTaskTime{
			ptr: C.ifc_task_get_task_time(t.inner.ptr),
		},
	}
	runtime.SetFinalizer(tt.inner, (*innerIfcTaskTime).free)
	return tt
}

func (t *IfcTask) GetWorkMethod() string {
	method := C.ifc_task_get_work_method(t.inner.ptr)
	return C.GoString(method)
}

func (t *IfcTask) GetPriority() int {
	return int(C.ifc_task_get_priority(t.inner.ptr))
}

func (t *IfcTask) IsMilestone() bool {
	return bool(C.ifc_task_is_milestone(t.inner.ptr))
}

// 列表属性方法
func (t *IfcTask) GetPredecessors() []string {
	count := 0
	list := C.ifc_task_get_predecessors(t.inner.ptr, (*C.int)(unsafe.Pointer(&count)))
	defer C.ifc_task_free_string_list(list)

	result := make([]string, count)
	for i := 0; i < count; i++ {
		result[i] = C.GoString(*(**C.char)(unsafe.Pointer(uintptr(unsafe.Pointer(list)) + uintptr(i)*unsafe.Sizeof(*list))))
	}
	return result
}

func (t *IfcTask) GetSuccessors() []string {
	count := 0
	list := C.ifc_task_get_successors(t.inner.ptr, (*C.int)(unsafe.Pointer(&count)))
	defer C.ifc_task_free_string_list(list)

	result := make([]string, count)
	for i := 0; i < count; i++ {
		result[i] = C.GoString(*(**C.char)(unsafe.Pointer(uintptr(unsafe.Pointer(list)) + uintptr(i)*unsafe.Sizeof(*list))))
	}
	return result
}

func (t *IfcTask) GetSubtasks() []*IfcTask {
	count := 0
	subtasks := []*IfcTask{}
	res := C.ifc_task_get_subtasks(t.inner.ptr, (*C.int)(unsafe.Pointer(&count)))
	if count == 0 {
		return subtasks
	}
	defer C.ifc_task_free_subtasks(res)

	for i := 0; i < count; i++ {
		task := &IfcTask{
			inner: &innerIfcTask{
				ptr: *(**C.ifc_task_t)(unsafe.Pointer(uintptr(unsafe.Pointer(res)) + uintptr(i)*unsafe.Sizeof(*res))),
			},
		}
		runtime.SetFinalizer(task.inner, (*innerIfcTask).free)
		subtasks = append(subtasks, task)
	}
	return subtasks
}

type IfcWorkTime struct {
	inner *innerIfcWorkTime
}

type innerIfcWorkTime struct {
	ptr *C.ifc_work_time_t
}

func (wt *innerIfcWorkTime) free() {
	if wt.ptr != nil {
		C.ifc_work_time_free(wt.ptr)
		wt.ptr = nil
	}
}

func (wt *IfcWorkTime) GetName() string {
	name := C.ifc_work_time_get_name(wt.inner.ptr)
	return C.GoString(name)
}

func (wt *IfcWorkTime) GetStartTime() string {
	start := C.ifc_work_time_get_start_time(wt.inner.ptr)
	return C.GoString(start)
}

func (wt *IfcWorkTime) GetFinishTime() string {
	end := C.ifc_work_time_get_finish_time(wt.inner.ptr)
	return C.GoString(end)
}

func (wt *IfcWorkTime) GetRecurrencePattern() *IfcRecurrencePattern {
	rp := &IfcRecurrencePattern{
		inner: &innerIfcRecurrencePattern{
			ptr: C.ifc_work_time_get_recurrence_pattern(wt.inner.ptr),
		},
	}
	runtime.SetFinalizer(rp.inner, (*innerIfcRecurrencePattern).free)
	return rp
}

type IfcWorkCalendar struct {
	inner *innerIfcWorkCalendar
}

type innerIfcWorkCalendar struct {
	ptr *C.ifc_work_calendar_t
}

func (wc *innerIfcWorkCalendar) free() {
	if wc.ptr != nil {
		C.ifc_work_calendar_free(wc.ptr)
		wc.ptr = nil
	}
}

func (wc *IfcWorkCalendar) GetID() string {
	id := C.ifc_work_calendar_get_id(wc.inner.ptr)
	return C.GoString(id)
}

func (wc *IfcWorkCalendar) GetName() string {
	name := C.ifc_work_calendar_get_name(wc.inner.ptr)
	return C.GoString(name)
}

func (wc *IfcWorkCalendar) GetWorkingTimes() []*IfcWorkTime {
	count := 0
	workingTimes := []*IfcWorkTime{}
	res := C.ifc_work_calendar_get_working_times(wc.inner.ptr, (*C.int)(unsafe.Pointer(&count)))
	if count == 0 {
		return workingTimes
	}
	defer C.ifc_work_calendar_free_working_times(res)

	for i := 0; i < count; i++ {
		wt := &IfcWorkTime{
			inner: &innerIfcWorkTime{
				ptr: *(**C.ifc_work_time_t)(unsafe.Pointer(uintptr(unsafe.Pointer(res)) + uintptr(i)*unsafe.Sizeof(*res))),
			},
		}
		runtime.SetFinalizer(wt.inner, (*innerIfcWorkTime).free)
		workingTimes = append(workingTimes, wt)
	}
	return workingTimes
}

type IfcWorkSchedule struct {
	inner *innerIfcWorkSchedule
}

type innerIfcWorkSchedule struct {
	ptr *C.ifc_work_schedule_t
}

func (ws *innerIfcWorkSchedule) free() {
	if ws.ptr != nil {
		C.ifc_work_schedule_free(ws.ptr)
		ws.ptr = nil
	}
}

func (ws *IfcWorkSchedule) GetID() string {
	id := C.ifc_work_schedule_get_id(ws.inner.ptr)
	return C.GoString(id)
}

func (ws *IfcWorkSchedule) GetName() string {
	name := C.ifc_work_schedule_get_name(ws.inner.ptr)
	return C.GoString(name)
}

func (ws *IfcWorkSchedule) GetTasks() []*IfcTask {
	count := 0
	tasks := []*IfcTask{}
	res := C.ifc_work_schedule_get_tasks(ws.inner.ptr, (*C.int)(unsafe.Pointer(&count)))
	if count == 0 {
		return tasks
	}
	defer C.ifc_work_schedule_free_tasks(res)

	for i := 0; i < count; i++ {
		task := &IfcTask{
			inner: &innerIfcTask{
				ptr: *(**C.ifc_task_t)(unsafe.Pointer(uintptr(unsafe.Pointer(res)) + uintptr(i)*unsafe.Sizeof(*res))),
			},
		}
		runtime.SetFinalizer(task.inner, (*innerIfcTask).free)
		tasks = append(tasks, task)
	}
	return tasks
}

func (ws *IfcWorkSchedule) GetPurpose() string {
	purpose := C.ifc_work_schedule_get_purpose(ws.inner.ptr)
	return C.GoString(purpose)
}

func (ws *IfcWorkSchedule) GetStartTime() string {
	start := C.ifc_work_schedule_get_start_time(ws.inner.ptr)
	return C.GoString(start)
}

func (ws *IfcWorkSchedule) GetFinishTime() string {
	finish := C.ifc_work_schedule_get_finish_time(ws.inner.ptr)
	return C.GoString(finish)
}

func (ws *IfcWorkSchedule) GetDuration() float64 {
	return float64(C.ifc_work_schedule_get_duration(ws.inner.ptr))
}

func (ws *IfcWorkSchedule) GetTotalFloat() float64 {
	return float64(C.ifc_work_schedule_get_total_float(ws.inner.ptr))
}

func (ws *IfcWorkSchedule) GetCreators() []string {
	count := 0
	creators := C.ifc_work_schedule_get_creators(ws.inner.ptr, (*C.int)(unsafe.Pointer(&count)))
	defer C.ifc_work_schedule_free_creators(creators)

	result := make([]string, count)
	for i := 0; i < count; i++ {
		result[i] = C.GoString(*(**C.char)(unsafe.Pointer(uintptr(unsafe.Pointer(creators)) + uintptr(i)*unsafe.Sizeof(*creators))))
	}
	return result
}

type IfcWorkPlan struct {
	inner *innerIfcWorkPlan
}

type innerIfcWorkPlan struct {
	ptr *C.ifc_work_plan_t
}

func (wp *innerIfcWorkPlan) free() {
	if wp.ptr != nil {
		C.ifc_work_plan_free(wp.ptr)
		wp.ptr = nil
	}
}

func (wp *IfcWorkPlan) GetID() string {
	id := C.ifc_work_plan_get_id(wp.inner.ptr)
	return C.GoString(id)
}

func (wp *IfcWorkPlan) GetName() string {
	name := C.ifc_work_plan_get_name(wp.inner.ptr)
	return C.GoString(name)
}

func (wp *IfcWorkPlan) GetWorkScheduleIDs() []string {
	count := 0
	ids := C.ifc_work_plan_get_work_schedule_ids(wp.inner.ptr, (*C.int)(unsafe.Pointer(&count)))
	defer C.ifc_work_plan_free_work_schedule_ids(ids)

	result := make([]string, count)
	for i := 0; i < count; i++ {
		result[i] = C.GoString(*(**C.char)(unsafe.Pointer(uintptr(unsafe.Pointer(ids)) + uintptr(i)*unsafe.Sizeof(*ids))))
	}
	return result
}

func (wp *IfcWorkPlan) GetPurpose() string {
	purpose := C.ifc_work_plan_get_purpose(wp.inner.ptr)
	return C.GoString(purpose)
}

func (wp *IfcWorkPlan) GetStartTime() string {
	start := C.ifc_work_plan_get_start_time(wp.inner.ptr)
	return C.GoString(start)
}

func (wp *IfcWorkPlan) GetFinishTime() string {
	finish := C.ifc_work_plan_get_finish_time(wp.inner.ptr)
	return C.GoString(finish)
}

func (wp *IfcWorkPlan) GetDuration() float64 {
	return float64(C.ifc_work_plan_get_duration(wp.inner.ptr))
}

func (wp *IfcWorkPlan) GetTotalFloat() float64 {
	return float64(C.ifc_work_plan_get_total_float(wp.inner.ptr))
}

func (wp *IfcWorkPlan) GetCreators() []string {
	count := 0
	creators := C.ifc_work_plan_get_creators(wp.inner.ptr, (*C.int)(unsafe.Pointer(&count)))
	defer C.ifc_work_plan_free_creators(creators)

	result := make([]string, count)
	for i := 0; i < count; i++ {
		result[i] = C.GoString(*(**C.char)(unsafe.Pointer(uintptr(unsafe.Pointer(creators)) + uintptr(i)*unsafe.Sizeof(*creators))))
	}
	return result
}

type IfcConnection struct {
	inner *innerIfcConnection
}

type innerIfcConnection struct {
	ptr *C.ifc_connection_t
}

func (c *innerIfcConnection) free() {
	if c.ptr != nil {
		C.ifc_connection_free(c.ptr)
		c.ptr = nil
	}
}

func (c *IfcConnection) GetID() string {
	id := C.ifc_connection_get_id(c.inner.ptr)
	return C.GoString(id)
}

func (c *IfcConnection) GetRelatingElementID() string {
	id := C.ifc_connection_get_relating_element_id(c.inner.ptr)
	return C.GoString(id)
}

func (c *IfcConnection) GetRelatedElementID() string {
	id := C.ifc_connection_get_related_element_id(c.inner.ptr)
	return C.GoString(id)
}

type IfcTypeObject struct {
	inner *innerIfcTypeObject
}

type innerIfcTypeObject struct {
	ptr *C.ifc_type_object_t
}

func (o *innerIfcTypeObject) free() {
	if o.ptr != nil {
		C.ifc_type_object_free(o.ptr)
		o.ptr = nil
	}
}

func (o *IfcTypeObject) GetID() string {
	id := C.ifc_type_object_get_id(o.inner.ptr)
	return C.GoString(id)
}

func (o *IfcTypeObject) GetName() string {
	name := C.ifc_type_object_get_name(o.inner.ptr)
	return C.GoString(name)
}

func (o *IfcTypeObject) GetPropertySets() []*IfcPropertySet {
	count := 0
	propertySets := []*IfcPropertySet{}
	res := C.ifc_type_object_get_property_sets(o.inner.ptr, (*C.int)(unsafe.Pointer(&count)))
	if count == 0 {
		return propertySets
	}
	defer C.ifc_type_object_free_property_sets(res)

	for i := 0; i < count; i++ {
		ps := &IfcPropertySet{
			inner: &innerIfcPropertySet{
				ptr: *(**C.ifc_property_set_t)(unsafe.Pointer(uintptr(unsafe.Pointer(res)) + uintptr(i)*unsafe.Sizeof(*res))),
			},
		}
		runtime.SetFinalizer(ps.inner, (*innerIfcPropertySet).Free)
		propertySets = append(propertySets, ps)
	}
	return propertySets
}

type IfcLayer struct {
	inner *innerIfcLayer
}

type innerIfcLayer struct {
	ptr *C.ifc_layer_t
}

func (l *innerIfcLayer) free() {
	if l.ptr != nil {
		C.ifc_layer_free(l.ptr)
		l.ptr = nil
	}
}

func (l *IfcLayer) GetName() string {
	name := C.ifc_layer_get_name(l.inner.ptr)
	return C.GoString(name)
}

func (l *IfcLayer) GetID() string {
	id := C.ifc_layer_get_id(l.inner.ptr)
	return C.GoString(id)
}

func (l *IfcLayer) GetAssignedElements() []string {
	count := 0
	elements := C.ifc_layer_get_assigned_elements(l.inner.ptr, (*C.int)(unsafe.Pointer(&count)))
	defer C.ifc_layer_free_assigned_elements(elements)

	result := make([]string, count)
	for i := 0; i < count; i++ {
		result[i] = C.GoString(*(**C.char)(unsafe.Pointer(uintptr(unsafe.Pointer(elements)) + uintptr(i)*unsafe.Sizeof(*elements))))
	}
	return result
}

func (l *IfcLayer) GetDescription() string {
	desc := C.ifc_layer_get_description(l.inner.ptr)
	return C.GoString(desc)
}

type IfcMaterial struct {
	inner *innerIfcMaterial
}

type innerIfcMaterial struct {
	ptr *C.ifc_material_t
}

func (m *innerIfcMaterial) free() {
	if m.ptr != nil {
		C.ifc_material_free(m.ptr)
		m.ptr = nil
	}
}

func (m *IfcMaterial) GetID() string {
	id := C.ifc_material_get_id(m.inner.ptr)
	return C.GoString(id)
}

func (m *IfcMaterial) GetName() string {
	name := C.ifc_material_get_name(m.inner.ptr)
	return C.GoString(name)
}

func (m *IfcMaterial) GetDescription() string {
	desc := C.ifc_material_get_description(m.inner.ptr)
	return C.GoString(desc)
}

func (m *IfcMaterial) GetCategory() string {
	category := C.ifc_material_get_category(m.inner.ptr)
	return C.GoString(category)
}

type IfcGroup struct {
	inner *innerIfcGroup
}

type innerIfcGroup struct {
	ptr *C.ifc_group_t
}

func (g *innerIfcGroup) free() {
	if g.ptr != nil {
		C.ifc_group_free(g.ptr)
		g.ptr = nil
	}
}

func (g *IfcGroup) GetID() string {
	id := C.ifc_group_get_id(g.inner.ptr)
	return C.GoString(id)
}

func (g *IfcGroup) GetName() string {
	name := C.ifc_group_get_name(g.inner.ptr)
	return C.GoString(name)
}

func (g *IfcGroup) GetMemberIDs() []string {
	count := 0
	ids := C.ifc_group_get_member_ids(g.inner.ptr, (*C.int)(unsafe.Pointer(&count)))
	defer C.ifc_group_free_member_ids(ids)

	result := make([]string, count)
	for i := 0; i < count; i++ {
		result[i] = C.GoString(*(**C.char)(unsafe.Pointer(uintptr(unsafe.Pointer(ids)) + uintptr(i)*unsafe.Sizeof(*ids))))
	}
	return result
}

type IfcTimePeriod struct {
	inner *innerIfcTimePeriod
}

type innerIfcTimePeriod struct {
	ptr *C.ifc_time_period_t
}

func (tp *innerIfcTimePeriod) free() {
	if tp.ptr != nil {
		C.ifc_time_period_free(tp.ptr)
		tp.ptr = nil
	}
}

func (tp *IfcTimePeriod) GetStartTime() string {
	start := C.ifc_time_period_get_start_time(tp.inner.ptr)
	return C.GoString(start)
}

func (tp *IfcTimePeriod) GetEndTime() string {
	end := C.ifc_time_period_get_end_time(tp.inner.ptr)
	return C.GoString(end)
}

type IfcRecurrencePattern struct {
	inner *innerIfcRecurrencePattern
}

type innerIfcRecurrencePattern struct {
	ptr *C.ifc_recurrence_pattern_t
}

func (rp *innerIfcRecurrencePattern) free() {
	if rp.ptr != nil {
		C.ifc_recurrence_pattern_free(rp.ptr)
		rp.ptr = nil
	}
}

func (rp *IfcRecurrencePattern) GetPosition() int {
	return int(C.ifc_recurrence_pattern_get_position(rp.inner.ptr))
}

func (rp *IfcRecurrencePattern) GetInterval() int {
	return int(C.ifc_recurrence_pattern_get_interval(rp.inner.ptr))
}

func (rp *IfcRecurrencePattern) GetOccurrences() int {
	return int(C.ifc_recurrence_pattern_get_occurrences(rp.inner.ptr))
}

func (rp *IfcRecurrencePattern) GetDayComponents() []float64 {
	count := 0
	components := C.ifc_recurrence_pattern_get_day_components(rp.inner.ptr, (*C.int)(unsafe.Pointer(&count)))
	result := make([]float64, count)
	copy(result, (*[1 << 30]float64)(unsafe.Pointer(components))[:count:count])
	return result
}

func (rp *IfcRecurrencePattern) GetWeekdayComponents() []float64 {
	count := 0
	components := C.ifc_recurrence_pattern_get_weekday_components(rp.inner.ptr, (*C.int)(unsafe.Pointer(&count)))
	result := make([]float64, count)
	copy(result, (*[1 << 30]float64)(unsafe.Pointer(components))[:count:count])
	return result
}

func (rp *IfcRecurrencePattern) GetMonthComponents() []float64 {
	count := 0
	components := C.ifc_recurrence_pattern_get_month_components(rp.inner.ptr, (*C.int)(unsafe.Pointer(&count)))
	result := make([]float64, count)
	copy(result, (*[1 << 30]float64)(unsafe.Pointer(components))[:count:count])
	return result
}

func (rp *IfcRecurrencePattern) GetTimePeriods() []*IfcTimePeriod {
	count := 0
	periods := []*IfcTimePeriod{}
	res := C.ifc_recurrence_pattern_get_time_periods(rp.inner.ptr, (*C.int)(unsafe.Pointer(&count)))
	if count == 0 {
		return periods
	}
	defer C.ifc_recurrence_pattern_free_time_periods(res)

	for i := 0; i < count; i++ {
		tp := &IfcTimePeriod{
			inner: &innerIfcTimePeriod{
				ptr: *(**C.ifc_time_period_t)(unsafe.Pointer(uintptr(unsafe.Pointer(res)) + uintptr(i)*unsafe.Sizeof(*res))),
			},
		}
		runtime.SetFinalizer(tp.inner, (*innerIfcTimePeriod).free)
		periods = append(periods, tp)
	}
	return periods
}

type IfcRelDefinesByType struct {
	inner *innerIfcRelDefinesByType
}

type innerIfcRelDefinesByType struct {
	ptr *C.ifc_rel_defines_by_type_t
}

func (ps *innerIfcRelDefinesByType) free() {
	if ps.ptr != nil {
		C.ifc_rel_defines_by_type_free(ps.ptr)
		ps.ptr = nil
	}
}

func (r *IfcRelDefinesByType) GetID() string {
	id := C.ifc_rel_defines_by_type_get_id(r.inner.ptr)
	return C.GoString(id)
}

func (r *IfcRelDefinesByType) GetName() string {
	name := C.ifc_rel_defines_by_type_get_name(r.inner.ptr)
	return C.GoString(name)
}

func (r *IfcRelDefinesByType) GetDescription() string {
	desc := C.ifc_rel_defines_by_type_get_desc(r.inner.ptr)
	return C.GoString(desc)
}

func (r *IfcRelDefinesByType) GetTypeObjectID() string {
	id := C.ifc_rel_defines_by_type_get_type_obj_id(r.inner.ptr)
	return C.GoString(id)
}

func (r *IfcRelDefinesByType) GetObjectIds() []string {
	count := 0
	ids := C.ifc_rel_defines_by_type_get_obj_ids(r.inner.ptr, (*C.int)(unsafe.Pointer(&count)))
	defer C.ifc_rel_defines_by_type_free_obj_ids(ids)

	result := make([]string, count)
	for i := 0; i < count; i++ {
		result[i] = C.GoString(*(**C.char)(unsafe.Pointer(uintptr(unsafe.Pointer(ids)) + uintptr(i)*unsafe.Sizeof(*ids))))
	}
	return result
}

type IfcRelDefinesByProperties struct {
	inner *innerIfcRelDefinesByProperties
}

type innerIfcRelDefinesByProperties struct {
	ptr *C.ifc_rel_defines_by_properties_t
}

func (ps *innerIfcRelDefinesByProperties) free() {
	if ps.ptr != nil {
		C.ifc_rel_defines_by_properties_free(ps.ptr)
		ps.ptr = nil
	}
}

func (r *IfcRelDefinesByProperties) GetID() string {
	id := C.ifc_rel_defines_by_properties_get_id(r.inner.ptr)
	return C.GoString(id)
}

func (r *IfcRelDefinesByProperties) GetName() string {
	name := C.ifc_rel_defines_by_properties_get_name(r.inner.ptr)
	return C.GoString(name)
}

func (r *IfcRelDefinesByProperties) GetDescription() string {
	desc := C.ifc_rel_defines_by_properties_get_desc(r.inner.ptr)
	return C.GoString(desc)
}

func (r *IfcRelDefinesByProperties) GetObjectIds() []string {
	count := 0
	ids := C.ifc_rel_defines_by_properties_get_obj_ids(r.inner.ptr, (*C.int)(unsafe.Pointer(&count)))
	defer C.ifc_rel_defines_by_properties_free_obj_ids(ids)

	result := make([]string, count)
	for i := 0; i < count; i++ {
		result[i] = C.GoString(*(**C.char)(unsafe.Pointer(uintptr(unsafe.Pointer(ids)) + uintptr(i)*unsafe.Sizeof(*ids))))
	}
	return result
}

func (r *IfcRelDefinesByProperties) GetPropertySetId() string {
	pid := C.ifc_rel_defines_by_properties_get_propertyset_id(r.inner.ptr)
	return C.GoString(pid)

}
