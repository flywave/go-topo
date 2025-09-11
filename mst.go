package topo

import (
	mst "github.com/flywave/go-mst"
	vec3d "github.com/flywave/go3d/float64/vec3"
)

type TextureOptions struct {
	Texture          string      `json:"texture,omitempty"`
	TextureScale     *[2]float64 `json:"texture-scale,omitempty"`
	TextureOrigin    *[2]float64 `json:"texture-origin,omitempty"`
	TextureRepeat    *[2]float64 `json:"texture-repeat,omitempty"`
	TextureAutoScale *[2]float64 `json:"texture-auto-scale,omitempty"`
	TextureMap       *string     `json:"texture-map,omitempty"`
	TextureAngle     *float64    `json:"texture-angle,omitempty"`
}

func TopoShapeToMst(shps []*Shape, mtls []mst.MeshMaterial, opt TextureOptions) (*mst.Mesh, *vec3d.Box, error) {
	mesh := mst.NewMesh()
	bbx := vec3d.MinBox
	for i, shp := range shps {
		node := &mst.MeshNode{}
		if shp == nil || shp.IsNull() {
			continue
		}

		var texture *mst.Texture
		if opt.Texture != "" {
			var err error
			texture, err = mst.CreateTexture(opt.Texture, true)
			if err != nil {
				return nil, nil, err
			}
			if opt.TextureScale != nil {
				shp.SetScaleU(opt.TextureScale[0])
				shp.SetScaleV(opt.TextureScale[1])
			}
			if opt.TextureOrigin != nil {
				shp.SetUVOrigin(opt.TextureOrigin[0], opt.TextureOrigin[1])
			}
			if opt.TextureRepeat != nil {
				shp.SetUVRepeat(opt.TextureRepeat[0], opt.TextureRepeat[1])
			}
			if opt.TextureAutoScale != nil {
				shp.SetAutoScaleSizeOnU(opt.TextureAutoScale[0])
				shp.SetAutoScaleSizeOnV(opt.TextureAutoScale[1])
			}
			if opt.TextureMap != nil {
				tp := StringToTxtureMap(*opt.TextureMap)
				shp.SetTextureMapType(tp)
			}
			if opt.TextureAngle != nil {
				shp.SetRotationAngle(*opt.TextureAngle)
			}
		}
		rev := NewMeshReceiver()
		res := int8(1)
		if opt.Texture != "" {
			res = shp.MeshWithTexture(rev, 1e-8, 1, 0.5)
		} else {
			res = shp.Mesh(rev, 1e-8, 1, 0.5)
		}

		if res != 0 {
			continue
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
				bbx.Extend(&rawV)
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
		var mtl mst.MeshMaterial
		if len(mtls) == 0 || len(mtls) <= i {
			m := &mst.TextureMaterial{}
			m.Color = [3]byte{255, 255, 255}
			m.Transparency = 0.0
			if texture != nil {
				m.Texture = texture
			}
			mtl = m
		} else {
			mtl = mtls[i]
		}
		if len(node.Normals) == 0 {
			node.ReComputeNormal()
		}
		mesh.Materials = append(mesh.Materials, mtl)
		mesh.Nodes = append(mesh.Nodes, node)
	}
	return mesh, &bbx, nil
}
