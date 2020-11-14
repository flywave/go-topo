package ifc

import (
	"testing"
)

func TestIfc(t *testing.T) {
	IfcToTopoShape("../tests/basic_shape_SweptSolid.ifc")
}
