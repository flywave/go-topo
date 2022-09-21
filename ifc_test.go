package topo

import (
	"fmt"
	"testing"
)

const TOLERANCE = 1e-8

func TestIfc(t *testing.T) {
	ts := IfcToTopoShape("tests/buildingElementProxy.ifc")
	rev := NewMeshReceiver()
	for _, sh := range ts {
		sh.Mesh(rev, TOLERANCE, 0.1, 0.5)
		fmt.Println(len(rev.Tris))
	}
}
