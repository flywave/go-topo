package topo

import "testing"

func TestBoxProbe(t *testing.T) {
	wp := NewNamedWorkplane("XY")
	r := wp.BoxCentered(2, 2, 2)
	if r.HasError() {
		t.Logf("BoxCentered error: %s", r.Error())
	}
	v := r.Value()
	if v == nil {
		t.Fatal("Value() nil")
	}
	t.Logf("Value: IsNull=%v IsValid=%v", v.IsNull(), v.IsValid())
	if v.IsNull() {
		t.Skip("box value is null")
	}
	as := NewAssembly(NewAssemblyObjectFromShpe(*v), nil, "root", nil)
	if as == nil {
		t.Fatal("NewAssembly nil")
	}
	if as.HasError() {
		t.Logf("NewAssembly error: %s", as.Error())
	}
	child := NewAssembly(NewAssemblyObjectFromShpe(*r.BoxCentered(1, 1, 1).Value()), nil, "c", nil)
	if child == nil {
		t.Fatal("child nil")
	}
	as.AddAssembly(child, nil, "", nil)
	t.Logf("AddAssembly error: %v", as.HasError())
}
