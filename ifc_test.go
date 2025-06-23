package topo

import (
	"fmt"
	"testing"
)

const TOLERANCE = 1e-8

func TestIfc(t *testing.T) {
	ts := IfcToElements("tests/buildingElementProxy.ifc")
	for _, sh := range ts {
		fmt.Println(sh.Name)
	}

	tris := IfcToTriangulations("tests/buildingElementProxy.ifc")
	for _, tri := range tris {
		fmt.Println(len(tri.GetVerts()))
	}

	convert := NewIfcConverter()
	convert.Load("tests/basic_shape_SweptSolid.ifc")

	eles := convert.GetElements()
	data := convert.GetData()
	prsets := data.GetPropertySets()
	for i := range eles {
		ps := prsets[i]
		ifcPro := ps.GetProperties()
		for _, p := range ifcPro {
			fmt.Println(p.GetName(), p.GetValue())
		}
	}
}
