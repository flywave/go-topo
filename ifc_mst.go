package topo

import (
	mst "github.com/flywave/go-mst"
	mat4d "github.com/flywave/go3d/float64/mat4"
	vec3d "github.com/flywave/go3d/float64/vec3"

	"github.com/flywave/go3d/vec2"
	"github.com/flywave/go3d/vec3"
)

func IfcToMst(filepath string) ([]*mst.Mesh, error) {
	convert := NewIfcConverter()
	convert.Load(filepath)
	trgs := convert.GetTriangulations()
	mh, _, err := TriangulationsToMst(trgs)
	if err != nil {
		return nil, err
	}
	return mh, nil
}

func TriangulationsToMst(trgs []*IfcTriangulation) ([]*mst.Mesh, []*vec3d.Box, error) {
	meshs := []*mst.Mesh{}
	defaultMtl := &mst.BaseMaterial{
		Color: [3]byte{
			byte(255),
			byte(255),
			byte(255),
		},
	}
	boxes := []*vec3d.Box{}
	for _, trg := range trgs {
		mesh := mst.NewMesh()
		vertices := trg.GetVerts()
		faces := trg.GetFaces()
		fcount := len(faces) / 3
		normals := trg.GetNormals()
		textures := trg.GetUVs()
		mtlIds := trg.GetMaterialIds()
		mtls := trg.GetMaterials()
		if len(mtls) == 0 {
			mtls = append(mtls, nil)
		}

		mhNode := &mst.MeshNode{}
		var mt *mat4d.T
		if trg.Transform != nil {
			tmp := mat4d.FromArray(*trg.Transform)
			tmp = mat4d.RecomposeMatrix(tmp)
			mt = &tmp
		}

		mhNode.Vertices = make([]vec3.T, len(vertices)/3)
		mhNode.Normals = make([]vec3.T, len(normals)/3)
		hasNormals := len(mhNode.Normals) > 0
		mhNode.TexCoords = make([]vec2.T, len(textures)/3)
		hasTc := len(mhNode.TexCoords) > 0
		mhNode.FaceGroup = make([]*mst.MeshTriangle, len(mtls))
		b := vec3d.MinBox
		for i := 0; i < fcount; i++ {
			f1 := uint32(faces[i*3])
			f2 := uint32(faces[i*3+1])
			f3 := uint32(faces[i*3+2])
			v1 := vec3d.T{vertices[f1*3], vertices[f1*3+1], vertices[f1*3+2]}
			v2 := vec3d.T{vertices[f2*3], vertices[f2*3+1], vertices[f2*3+2]}
			v3 := vec3d.T{vertices[f3*3], vertices[f3*3+1], vertices[f3*3+2]}
			if mt != nil {
				v1 = mt.MulVec3(&v1)
				v2 = mt.MulVec3(&v2)
				v3 = mt.MulVec3(&v3)
			}
			b.Extend(&v1)
			b.Extend(&v2)
			b.Extend(&v3)
			mhNode.Vertices[f1] = [3]float32{float32(v1[0]), float32(v1[1]), float32(v1[2])}
			mhNode.Vertices[f2] = [3]float32{float32(v2[0]), float32(v2[1]), float32(v2[2])}
			mhNode.Vertices[f3] = [3]float32{float32(v3[0]), float32(v3[1]), float32(v3[2])}
			if hasNormals {
				n1 := [3]float32{float32(normals[f1*3]), float32(normals[f1*3+1]), float32(normals[f1*3+2])}
				n2 := [3]float32{float32(normals[f2*3]), float32(normals[f2*3+1]), float32(normals[f2*3+2])}
				n3 := [3]float32{float32(normals[f3*3]), float32(normals[f3*3+1]), float32(normals[f3*3+2])}
				mhNode.Normals[f1] = n1
				mhNode.Normals[f2] = n2
				mhNode.Normals[f3] = n3
			}
			if hasTc {
				t1 := [2]float32{float32(textures[f1*2]), float32(textures[f1*2+1])}
				t2 := [2]float32{float32(textures[f2*2]), float32(textures[f2*2+1])}
				t3 := [2]float32{float32(textures[f3*2]), float32(textures[f3*2+1])}
				mhNode.TexCoords[f1] = t1
				mhNode.TexCoords[f2] = t2
				mhNode.TexCoords[f3] = t3
			}

			mtlId := 0
			if len(mtlIds) > i {
				mtlId = int(mtlIds[i])
			}
			group := mhNode.FaceGroup[mtlId]
			if group == nil {
				mhNode.FaceGroup[mtlId] = &mst.MeshTriangle{Batchid: int32(len(mesh.Materials))}
				group = mhNode.FaceGroup[mtlId]

				style := mtls[mtlId]
				if style != nil {
					mtl := &mst.PhongMaterial{}
					mtl.Color = [3]byte{
						byte(style.Diffuse.R * 255),
						byte(style.Diffuse.G * 255),
						byte(style.Diffuse.B * 255),
					}
					mtl.Transparency = float32(style.Transparency)
					mtl.Specularity = float32(style.Specularity)
					mtl.Specular = [3]byte{
						byte(style.Specular.R * 255),
						byte(style.Specular.G * 255),
						byte(style.Specular.B * 255),
					}
					mesh.Materials = append(mesh.Materials, mtl)
				} else {
					mesh.Materials = append(mesh.Materials, defaultMtl)
				}
			}
			group.Faces = append(group.Faces, &mst.Face{Vertex: [3]uint32{f1, f2, f3}})
		}
		if !hasNormals {
			mhNode.ReComputeNormal()
		}
		mesh.Nodes = append(mesh.Nodes, mhNode)
		meshs = append(meshs, mesh)
		boxes = append(boxes, &b)
	}
	return meshs, boxes, nil
}
