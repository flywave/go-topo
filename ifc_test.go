package topo

import (
	"fmt"
	"testing"
)

const TOLERANCE = 1e-8

func TestIfc(t *testing.T) {
	ts := IfcToTopoShape("tests/buildingElementProxy.ifc")
	for _, sh := range ts {
		fmt.Println(sh.Name)
	}
}
