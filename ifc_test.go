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
}
