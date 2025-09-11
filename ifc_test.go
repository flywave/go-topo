package topo

import (
	"fmt"
	"testing"
)

const TOLERANCE = 1e-8

func TestIfc(t *testing.T) {

	convert := NewIfcConverter()
	convert.Load("tests/buildingElementProxy.ifc")

	// tris := IfcToTriangulations("tests/buildingElementProxy.ifc")//主管道加参数测试文件

	eles := convert.GetElements()
	for _, e := range eles {
		fmt.Println(e.Name, e.Type, e.Id, e.ParentId)
	}

	tris := convert.GetTriangulations()
	for _, tri := range tris {
		fmt.Println(len(tri.GetVerts()))
	}
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
		if len(objs) > 0 && objs[0] == "1XbPbka$v7pParXi$0VLWx" {
			fmt.Println(rdp.GetID(), rdp.GetName(), rdp.GetObjectIds(), " GetTypeObjectID", rdp.GetPropertySetId())

		}
	}

}

func TestIfc2(t *testing.T) {
	convert := NewIfcConverter()
	convert.Load("tests/buildingElementProxy.ifc")
	convert.GetTriangulations()
	for _, t := range convert.GetTriangulations() {
		if t.Transform != nil {
			fmt.Println(*t.Transform)
		}
	}
}

func TestIfc3(t *testing.T) {
	meshs, err := IfcToMstWithProperties("tests/buildingElementProxy.ifc")
	if err != nil {
		t.Error(err)
	}
	for _, m := range meshs {
		if len(m.Nodes) > 0 {
			fmt.Println(m.Nodes[0])
		}
	}
}
