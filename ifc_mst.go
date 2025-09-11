package topo

import (
	"fmt"

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

// ExtractIfcProperties extracts property information from an IFC file and returns MST Properties
func ExtractIfcProperties(convert *IfcConverter) ([]*mst.Properties, error) {
	// Get elements
	elements := convert.GetElements()
	propertiesList := make([]*mst.Properties, 0, len(elements))

	// Process each element
	for _, element := range elements {
		if element == nil {
			continue
		}

		// Create properties for this element
		props := make(mst.Properties)

		// Add basic element information
		props["id"] = mst.PropsValue{Type: mst.PROP_TYPE_INT, Value: int64(element.Id)}
		props["name"] = mst.PropsValue{Type: mst.PROP_TYPE_STRING, Value: element.Name}
		props["guid"] = mst.PropsValue{Type: mst.PROP_TYPE_STRING, Value: element.Guid}
		props["type"] = mst.PropsValue{Type: mst.PROP_TYPE_STRING, Value: element.Type}

		// Add transform matrix if available
		if element.Transform != nil {
			transformArray := make([]mst.PropsValue, 16)
			for i, val := range *element.Transform {
				transformArray[i] = mst.PropsValue{Type: mst.PROP_TYPE_FLOAT, Value: float64(val)}
			}
			props["transform"] = mst.PropsValue{Type: mst.PROP_TYPE_ARRAY, Value: transformArray}
		}

		propertiesList = append(propertiesList, &props)
	}

	// Get property sets directly associated with elements through relationships
	relDefinesByProperties := convert.GetData().GetRelDefinesByProperties()

	// First, collect all property sets
	propertySets := convert.GetData().GetPropertySets()
	propertySetMap := make(map[string]*mst.Properties)

	for _, ps := range propertySets {
		if ps == nil {
			continue
		}

		// Create properties for this property set
		props := make(mst.Properties)
		props["id"] = mst.PropsValue{Type: mst.PROP_TYPE_STRING, Value: ps.GetID()}
		props["name"] = mst.PropsValue{Type: mst.PROP_TYPE_STRING, Value: ps.GetName()}

		// Add individual properties
		properties := ps.GetProperties()
		propertyMap := make(mst.Properties)
		for _, prop := range properties {
			if prop == nil {
				continue
			}

			// Convert property value based on its type
			var propValue mst.PropsValue
			if prop.IsNull() {
				propValue = mst.PropsValue{Type: mst.PROP_TYPE_STRING, Value: "null"}
			} else if prop.IsInt() {
				propValue = mst.PropsValue{Type: mst.PROP_TYPE_INT, Value: int64(prop.GetInt())}
			} else if prop.IsBool() {
				propValue = mst.PropsValue{Type: mst.PROP_TYPE_BOOL, Value: prop.GetBool()}
			} else if prop.IsDouble() {
				propValue = mst.PropsValue{Type: mst.PROP_TYPE_FLOAT, Value: prop.GetDouble()}
			} else if prop.IsString() {
				propValue = mst.PropsValue{Type: mst.PROP_TYPE_STRING, Value: prop.GetString()}
			} else if prop.IsBitset() {
				bitset := prop.GetBitset()
				bitsetArray := make([]mst.PropsValue, len(bitset))
				for i, b := range bitset {
					bitsetArray[i] = mst.PropsValue{Type: mst.PROP_TYPE_INT, Value: int64(b)}
				}
				propValue = mst.PropsValue{Type: mst.PROP_TYPE_ARRAY, Value: bitsetArray}
			} else if prop.IsIntVector() {
				intVec := prop.GetIntVector()
				intArray := make([]mst.PropsValue, len(intVec))
				for i, val := range intVec {
					intArray[i] = mst.PropsValue{Type: mst.PROP_TYPE_INT, Value: int64(val)}
				}
				propValue = mst.PropsValue{Type: mst.PROP_TYPE_ARRAY, Value: intArray}
			} else if prop.IsDoubleVector() {
				doubleVec := prop.GetDoubleVector()
				doubleArray := make([]mst.PropsValue, len(doubleVec))
				for i, val := range doubleVec {
					doubleArray[i] = mst.PropsValue{Type: mst.PROP_TYPE_FLOAT, Value: val}
				}
				propValue = mst.PropsValue{Type: mst.PROP_TYPE_ARRAY, Value: doubleArray}
			} else if prop.IsStringVector() {
				stringVec := prop.GetStringVector()
				stringArray := make([]mst.PropsValue, len(stringVec))
				for i, val := range stringVec {
					stringArray[i] = mst.PropsValue{Type: mst.PROP_TYPE_STRING, Value: val}
				}
				propValue = mst.PropsValue{Type: mst.PROP_TYPE_ARRAY, Value: stringArray}
			} else if prop.IsBitsetVector() {
				bitsetVec := prop.GetBitsetVector()
				bitsetArray := make([]mst.PropsValue, len(bitsetVec))
				for i, bitset := range bitsetVec {
					subBitsetArray := make([]mst.PropsValue, len(bitset))
					for j, b := range bitset {
						subBitsetArray[j] = mst.PropsValue{Type: mst.PROP_TYPE_INT, Value: int64(b)}
					}
					bitsetArray[i] = mst.PropsValue{Type: mst.PROP_TYPE_ARRAY, Value: subBitsetArray}
				}
				propValue = mst.PropsValue{Type: mst.PROP_TYPE_ARRAY, Value: bitsetArray}
			} else if prop.IsIntMatrix() {
				intMatrix := prop.GetIntMatrix()
				matrixArray := make([]mst.PropsValue, len(intMatrix))
				for i, row := range intMatrix {
					rowArray := make([]mst.PropsValue, len(row))
					for j, val := range row {
						rowArray[j] = mst.PropsValue{Type: mst.PROP_TYPE_INT, Value: int64(val)}
					}
					matrixArray[i] = mst.PropsValue{Type: mst.PROP_TYPE_ARRAY, Value: rowArray}
				}
				propValue = mst.PropsValue{Type: mst.PROP_TYPE_ARRAY, Value: matrixArray}
			} else if prop.IsDoubleMatrix() {
				doubleMatrix := prop.GetDoubleMatrix()
				matrixArray := make([]mst.PropsValue, len(doubleMatrix))
				for i, row := range doubleMatrix {
					rowArray := make([]mst.PropsValue, len(row))
					for j, val := range row {
						rowArray[j] = mst.PropsValue{Type: mst.PROP_TYPE_FLOAT, Value: val}
					}
					matrixArray[i] = mst.PropsValue{Type: mst.PROP_TYPE_ARRAY, Value: rowArray}
				}
				propValue = mst.PropsValue{Type: mst.PROP_TYPE_ARRAY, Value: matrixArray}
			} else {
				// For other types, convert to string
				propValue = mst.PropsValue{Type: mst.PROP_TYPE_STRING, Value: fmt.Sprintf("%v", prop.GetValue())}
			}

			propertyMap[prop.GetName()] = propValue
		}

		props["properties"] = mst.PropsValue{Type: mst.PROP_TYPE_MAP, Value: propertyMap}
		propertySetMap[ps.GetID()] = &props
	}

	// Associate property sets with elements using relationships
	for _, rel := range relDefinesByProperties {
		if rel == nil {
			continue
		}

		propertySetId := rel.GetPropertySetId()
		propertySet, exists := propertySetMap[propertySetId]
		if !exists {
			continue
		}

		// In a real implementation, we would need to map object IDs to elements
		// For now, we'll just add the property set to all elements
		for _, props := range propertiesList {
			(*props)["property_set"] = mst.PropsValue{Type: mst.PROP_TYPE_MAP, Value: *propertySet}
		}
	}

	// Also get property sets from type objects
	types := convert.GetData().GetTypes()
	for _, typ := range types {
		if typ != nil {
			typePropertySets := typ.GetPropertySets()
			for _, ps := range typePropertySets {
				if ps == nil {
					continue
				}

				// Create properties for this property set
				props := make(mst.Properties)
				props["id"] = mst.PropsValue{Type: mst.PROP_TYPE_STRING, Value: ps.GetID()}
				props["name"] = mst.PropsValue{Type: mst.PROP_TYPE_STRING, Value: ps.GetName()}

				// Add individual properties
				properties := ps.GetProperties()
				propertyMap := make(mst.Properties)
				for _, prop := range properties {
					if prop == nil {
						continue
					}

					// Convert property value based on its type
					var propValue mst.PropsValue
					if prop.IsNull() {
						propValue = mst.PropsValue{Type: mst.PROP_TYPE_STRING, Value: "null"}
					} else if prop.IsInt() {
						propValue = mst.PropsValue{Type: mst.PROP_TYPE_INT, Value: int64(prop.GetInt())}
					} else if prop.IsBool() {
						propValue = mst.PropsValue{Type: mst.PROP_TYPE_BOOL, Value: prop.GetBool()}
					} else if prop.IsDouble() {
						propValue = mst.PropsValue{Type: mst.PROP_TYPE_FLOAT, Value: prop.GetDouble()}
					} else if prop.IsString() {
						propValue = mst.PropsValue{Type: mst.PROP_TYPE_STRING, Value: prop.GetString()}
					} else if prop.IsBitset() {
						bitset := prop.GetBitset()
						bitsetArray := make([]mst.PropsValue, len(bitset))
						for i, b := range bitset {
							bitsetArray[i] = mst.PropsValue{Type: mst.PROP_TYPE_INT, Value: int64(b)}
						}
						propValue = mst.PropsValue{Type: mst.PROP_TYPE_ARRAY, Value: bitsetArray}
					} else if prop.IsIntVector() {
						intVec := prop.GetIntVector()
						intArray := make([]mst.PropsValue, len(intVec))
						for i, val := range intVec {
							intArray[i] = mst.PropsValue{Type: mst.PROP_TYPE_INT, Value: int64(val)}
						}
						propValue = mst.PropsValue{Type: mst.PROP_TYPE_ARRAY, Value: intArray}
					} else if prop.IsDoubleVector() {
						doubleVec := prop.GetDoubleVector()
						doubleArray := make([]mst.PropsValue, len(doubleVec))
						for i, val := range doubleVec {
							doubleArray[i] = mst.PropsValue{Type: mst.PROP_TYPE_FLOAT, Value: val}
						}
						propValue = mst.PropsValue{Type: mst.PROP_TYPE_ARRAY, Value: doubleArray}
					} else if prop.IsStringVector() {
						stringVec := prop.GetStringVector()
						stringArray := make([]mst.PropsValue, len(stringVec))
						for i, val := range stringVec {
							stringArray[i] = mst.PropsValue{Type: mst.PROP_TYPE_STRING, Value: val}
						}
						propValue = mst.PropsValue{Type: mst.PROP_TYPE_ARRAY, Value: stringArray}
					} else if prop.IsBitsetVector() {
						bitsetVec := prop.GetBitsetVector()
						bitsetArray := make([]mst.PropsValue, len(bitsetVec))
						for i, bitset := range bitsetVec {
							subBitsetArray := make([]mst.PropsValue, len(bitset))
							for j, b := range bitset {
								subBitsetArray[j] = mst.PropsValue{Type: mst.PROP_TYPE_INT, Value: int64(b)}
							}
							bitsetArray[i] = mst.PropsValue{Type: mst.PROP_TYPE_ARRAY, Value: subBitsetArray}
						}
						propValue = mst.PropsValue{Type: mst.PROP_TYPE_ARRAY, Value: bitsetArray}
					} else if prop.IsIntMatrix() {
						intMatrix := prop.GetIntMatrix()
						matrixArray := make([]mst.PropsValue, len(intMatrix))
						for i, row := range intMatrix {
							rowArray := make([]mst.PropsValue, len(row))
							for j, val := range row {
								rowArray[j] = mst.PropsValue{Type: mst.PROP_TYPE_INT, Value: int64(val)}
							}
							matrixArray[i] = mst.PropsValue{Type: mst.PROP_TYPE_ARRAY, Value: rowArray}
						}
						propValue = mst.PropsValue{Type: mst.PROP_TYPE_ARRAY, Value: matrixArray}
					} else if prop.IsDoubleMatrix() {
						doubleMatrix := prop.GetDoubleMatrix()
						matrixArray := make([]mst.PropsValue, len(doubleMatrix))
						for i, row := range doubleMatrix {
							rowArray := make([]mst.PropsValue, len(row))
							for j, val := range row {
								rowArray[j] = mst.PropsValue{Type: mst.PROP_TYPE_FLOAT, Value: val}
							}
							matrixArray[i] = mst.PropsValue{Type: mst.PROP_TYPE_ARRAY, Value: rowArray}
						}
						propValue = mst.PropsValue{Type: mst.PROP_TYPE_ARRAY, Value: matrixArray}
					} else {
						// For other types, convert to string
						propValue = mst.PropsValue{Type: mst.PROP_TYPE_STRING, Value: fmt.Sprintf("%v", prop.GetValue())}
					}

					propertyMap[prop.GetName()] = propValue
				}

				props["properties"] = mst.PropsValue{Type: mst.PROP_TYPE_MAP, Value: propertyMap}

				// Add this property set to all elements (simplified approach)
				for _, elementProps := range propertiesList {
					(*elementProps)["type_property_set"] = mst.PropsValue{Type: mst.PROP_TYPE_MAP, Value: props}
				}
			}
		}
	}

	return propertiesList, nil
}

// TriangulationsToMstWithProperties converts IFC triangulations to MST meshes with properties
func TriangulationsToMstWithProperties(convert *IfcConverter) ([]*mst.Mesh, []*vec3d.Box, error) {
	trgs := convert.GetTriangulations()
	elements := convert.GetElements()

	// First, get the basic mesh conversion
	meshs, boxes, err := TriangulationsToMst(trgs)
	if err != nil {
		return nil, nil, err
	}

	// Extract IFC properties
	propertiesList, err := ExtractIfcProperties(convert)
	if err != nil {
		// If we can't extract properties, return the basic meshes
		return meshs, boxes, nil
	}

	// Create a map of element GUIDs to their properties for easier lookup
	elementPropertyMap := make(map[string]*mst.Properties)
	for i, element := range elements {
		if i < len(propertiesList) && propertiesList[i] != nil {
			elementPropertyMap[element.Guid] = propertiesList[i]
		}
	}

	// Assign properties to mesh nodes based on GUID matching
	for i, mesh := range meshs {
		if i < len(trgs) {
			trg := trgs[i]
			// Look up properties by GUID
			if props, exists := elementPropertyMap[trg.Guid]; exists {
				// Create properties for the mesh if it doesn't have any
				if mesh.Props == nil {
					mesh.Props = &mst.Properties{}
				}

				// Copy properties from the extracted IFC properties
				for key, value := range *props {
					(*mesh.Props)[key] = value
				}

				// Assign properties to individual nodes as well
				for _, node := range mesh.Nodes {
					if node.Props == nil {
						node.Props = &mst.Properties{}
					}

					// Copy properties to each node
					for key, value := range *props {
						(*node.Props)[key] = value
					}
				}
			}
		}
	}

	return meshs, boxes, nil
}

// IfcToMstWithProperties converts an IFC file to MST meshes with properties
func IfcToMstWithProperties(filepath string) ([]*mst.Mesh, error) {
	convert := NewIfcConverter()
	convert.Load(filepath)
	meshs, _, err := TriangulationsToMstWithProperties(convert)
	if err != nil {
		return nil, err
	}
	return meshs, nil
}
