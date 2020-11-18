package topo

import (
	"fmt"
	"testing"
)

const TOLERANCE = 1E-8

func TestIfc(t *testing.T) {
	ts := IfcToTopoShape("tests/buildingElementProxy.ifc")
	rev := NewMeshReceiver()
	ts[0].Mesh(rev, TOLERANCE, 0.1, 0.5)
	fmt.Println(len(rev.Tris))
}
