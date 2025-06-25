package topo

import (
	"fmt"
	"testing"
)

const TOLERANCE = 1e-8

func TestIfc(t *testing.T) {

	convert := NewIfcConverter()
	convert.Load("tests/主管道.ifc")

	// tris := IfcToTriangulations("tests/buildingElementProxy.ifc")//主管道加参数测试文件
	// for _, tri := range tris {
	// 	fmt.Println(len(tri.GetVerts()))
	// }

	// eles := convert.GetElements()
	// for _, e := range eles {
	// 	fmt.Println(e.Name, e.Type, e.Id, e.ParentId)
	// }
	data := convert.GetData()
	prsets := data.GetPropertySets()

	objs := data.GetTypes()
	for _, o := range objs {
		fmt.Println(o.GetName(), o.GetID())
		props := o.GetPropertySets()
		for _, p := range props {
			fmt.Println(p.GetName(), p.GetID())
			ps := p.GetProperties()
			for _, ps := range ps {
				fmt.Println(ps.GetName(), ps.GetValue())
			}
		}
	}
	fmt.Println("-----------------")
	for i := range prsets {
		ps := prsets[i]
		ifcPro := ps.GetProperties()
		fmt.Println(ps.GetName(), ps.GetID())
		for _, p := range ifcPro {
			fmt.Println(p.GetName(), p.GetValue())
		}
	}

	rdts := data.GetRelDefinesByTypes()
	for _, rdt := range rdts {
		fmt.Println(rdt.GetID(), rdt.GetName(), rdt.GetObjectIds(), " GetTypeObjectID", rdt.GetTypeObjectID())
	}

	rdps := data.GetRelDefinesByProperties()
	for _, rdp := range rdps {
		objs := rdp.GetObjectIds()
		if objs[0] == "1XbPbka$v7pParXi$0VLWx" {
			fmt.Println(rdp.GetID(), rdp.GetName(), rdp.GetObjectIds(), " GetTypeObjectID", rdp.GetPropertySetId())

		}
	}

}
