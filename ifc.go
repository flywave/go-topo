package topo

/*
#include <stdlib.h>
#include "ifc_c_api.h"
#cgo CFLAGS: -I  ./libs
#cgo linux CXXFLAGS: -I ./libs  -std=gnu++14
#cgo darwin CXXFLAGS: -I ./libs  -std=gnu++14
#cgo darwin,arm CXXFLAGS: -I ./libs  -std=gnu++14
#cgo windows CXXFLAGS: -I ./libs  -std=gnu++14
*/
import "C"

import (
	"errors"
	"unsafe"

	"github.com/flywave/go-mst"
	vec3d "github.com/flywave/go3d/float64/vec3"
)

func init() {
	C.ifc_register_schema()
}

type IfcElementInfo struct {
	Shape    *Shape
	Id       int
	ParentId int
	Name     string
	Guid     string
}

func IfcToTopoShape(f string) []*IfcElementInfo {
	fl := C.CString(f)
	defer C.free(unsafe.Pointer(fl))
	count := 0
	sp := []*IfcElementInfo{}
	res := C.ifc_get_topo_shapes(fl, (*C.int)(unsafe.Pointer(&count)))
	if count == 0 {
		return sp
	}
	defer C.ifc_shapes_free(res)
	for i := 0; i < count; i++ {
		shp := NewShape(C.ifc_get_topo_shape(res, C.int(i)))
		sp = append(sp, &IfcElementInfo{
			Shape:    shp,
			Id:       shp.Id(),
			ParentId: shp.ParentId(),
			Name:     shp.Name(),
			Guid:     shp.Guid(),
		})
	}
	return sp
}

func IsIfc(f string) bool {
	fl := C.CString(f)
	defer C.free(unsafe.Pointer(fl))
	return bool(C.is_ifc_file(fl))
}

func TopoShapeToMst(shp []*Shape) (*mst.Mesh, error) {
	mesh := mst.NewMesh()
	for _, shp := range shp {
		node := &mst.MeshNode{}
		if shp == nil || shp.IsNull() {
			continue
		}

		rev := NewMeshReceiver()
		res := int8(1)
		res = shp.Mesh(rev, 1e-8, 1, 0.5)

		if res != 0 {
			return nil, errors.New("gen mesh failed")
		}
		mtrg := &mst.MeshTriangle{Batchid: int32(len(mesh.Materials))}
		for i := range rev.Tris {
			ts := rev.Tris[i]
			vcount := len(node.Vertices)
			for _, v := range ts {
				mtrg.Faces = append(mtrg.Faces, &mst.Face{Vertex: [3]uint32{uint32(v[0] + vcount), uint32(v[1] + vcount), uint32(v[2] + vcount)}})
			}

			vers := rev.Vers[i]
			for _, v := range vers {
				rawV := (vec3d.T)(v.Data())
				node.Vertices = append(node.Vertices, [3]float32{float32(rawV[0]), float32(rawV[1]), float32(rawV[2])})
			}
			nm := rev.Norms[i]
			for _, v := range nm {
				d := v.Data()
				node.Normals = append(node.Normals, [3]float32{float32(d[0]), float32(d[1]), float32(d[2])})
			}
			if rev.HasTexCoord() {
				tc := rev.TexCoords[i]
				for _, v := range tc {
					d := v.Data()
					node.TexCoords = append(node.TexCoords, [2]float32{float32(d[0]), float32(d[1])})
				}
			}
		}
		node.FaceGroup = append(node.FaceGroup, mtrg)

		mtl := &mst.BaseMaterial{}
		mtl.Color = [3]byte{255, 255, 255}
		mtl.Transparency = 0.0
		mesh.Materials = append(mesh.Materials, mtl)
		mesh.Nodes = append(mesh.Nodes, node)
	}
	return mesh, nil
}
