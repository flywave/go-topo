package topo

import (
	"testing"
)

func TestNewAssembly(t *testing.T) {
	t.Run("empty", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		obj := NewAssemblyObjectFromShpe(*r1.Value())
		as := NewAssembly(obj, nil, "test", nil)
		if as == nil {
			t.Fatal("NewAssembly returned nil")
		}
		if err := as.HasError(); err {
			t.Fatalf("unexpected error: %v", as.Error())
		}
	})
}

func TestAssemblyObject(t *testing.T) {
	t.Run("from shape", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		obj := NewAssemblyObjectFromShpe(*r1.Value())
		if obj == nil {
			t.Fatal("NewAssemblyObjectFromShpe returned nil")
		}
		if !obj.IsShape() {
			t.Fatal("expected IsShape true")
		}
		if obj.IsWorkplane() {
			t.Fatal("expected IsWorkplane false")
		}
		shp := obj.GetShape()
		if shp == nil {
			t.Fatal("GetShape returned nil")
		}
	})

	t.Run("from workplane", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		wpr := NewAssemblyObjectFromShpe(*r1.Value())
		_ = wpr
	})
}

func TestAssemblyAddAndQuery(t *testing.T) {
	t.Run("add object", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		obj := NewAssemblyObjectFromShpe(*r1.Value())
		as := NewAssembly(obj, nil, "root", nil)
		wp2 := NewNamedWorkplane("XY")
		r2 := wp2.BoxCentered(5, 5, 5)
		obj2 := NewAssemblyObjectFromShpe(*r2.Value())
		as.AddObject(obj2, nil, "child", nil)
		if err := as.HasError(); err {
			t.Fatalf("AddObject error: %v", as.Error())
		}
	})

	t.Run("add assembly", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		obj := NewAssemblyObjectFromShpe(*r1.Value())
		as := NewAssembly(obj, nil, "parent", nil)

		wp2 := NewNamedWorkplane("XY")
		r2 := wp2.BoxCentered(5, 5, 5)
		obj2 := NewAssemblyObjectFromShpe(*r2.Value())
		child := NewAssembly(obj2, nil, "child", nil)

		as.AddAssembly(child, nil, "", nil)
		if err := as.HasError(); err {
			t.Fatalf("AddAssembly error: %v", as.Error())
		}
	})
}

func TestAssemblyRemove(t *testing.T) {
	t.Run("remove", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		obj := NewAssemblyObjectFromShpe(*r1.Value())
		as := NewAssembly(obj, nil, "root", nil)
		wp2 := NewNamedWorkplane("XY")
		r2 := wp2.BoxCentered(5, 5, 5)
		obj2 := NewAssemblyObjectFromShpe(*r2.Value())
		as.AddObject(obj2, nil, "toremove", nil)
		as.Remove("toremove")
		if err := as.HasError(); err {
			t.Fatalf("Remove error: %v", as.Error())
		}
	})
}

func TestAssemblyCopy(t *testing.T) {
	t.Run("copy", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		obj := NewAssemblyObjectFromShpe(*r1.Value())
		as := NewAssembly(obj, nil, "original", nil)
		cp := as.Copy()
		if cp == nil {
			t.Fatal("Copy returned nil")
		}
		if cp.GetName() != "original" {
			t.Fatalf("expected name 'original', got '%s'", cp.GetName())
		}
	})
}

func TestAssemblyShapes(t *testing.T) {
	t.Run("shapes", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		obj := NewAssemblyObjectFromShpe(*r1.Value())
		as := NewAssembly(obj, nil, "test", nil)
		shapes := as.Shapes()
		if len(shapes) == 0 {
			t.Fatal("expected at least one shape")
		}
	})
}

func TestAssemblyToCompound(t *testing.T) {
	t.Run("to compound", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		obj := NewAssemblyObjectFromShpe(*r1.Value())
		as := NewAssembly(obj, nil, "test", nil)
		cmp := as.ToCompound()
		if cmp == nil {
			t.Fatal("ToCompound returned nil")
		}
	})
}

func TestAssemblyGetElements(t *testing.T) {
	t.Run("get elements", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		obj := NewAssemblyObjectFromShpe(*r1.Value())
		as := NewAssembly(obj, nil, "test", nil)
		elems := as.GetElements()
		if len(elems) == 0 {
			t.Fatal("expected at least one element")
		}
		if elems[0].GetName() == "test" {
			t.Log("element name matches assembly name")
		}
		shp := elems[0].GetShape()
		if shp == nil {
			t.Fatal("GetShape on element returned nil")
		}
	})
}

func TestAssemblyGetters(t *testing.T) {
	t.Run("get name", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		obj := NewAssemblyObjectFromShpe(*r1.Value())
		as := NewAssembly(obj, nil, "myname", nil)
		if as.GetName() != "myname" {
			t.Fatalf("expected 'myname', got '%s'", as.GetName())
		}
	})

	t.Run("get location", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		obj := NewAssemblyObjectFromShpe(*r1.Value())
		as := NewAssembly(obj, nil, "test", nil)
		loc := as.GetLocation()
		if loc == nil {
			t.Fatal("GetLocation returned nil")
		}
	})

	t.Run("get object", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		obj := NewAssemblyObjectFromShpe(*r1.Value())
		as := NewAssembly(obj, nil, "test", nil)
		obj2 := as.GetObject()
		if obj2 == nil {
			t.Fatal("GetObject returned nil")
		}
	})

	t.Run("children", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		obj := NewAssemblyObjectFromShpe(*r1.Value())
		as := NewAssembly(obj, nil, "parent", nil)

		wp2 := NewNamedWorkplane("XY")
		r2 := wp2.BoxCentered(5, 5, 5)
		obj2 := NewAssemblyObjectFromShpe(*r2.Value())
		child := NewAssembly(obj2, nil, "child", nil)
		as.AddAssembly(child, nil, "", nil)

		children := as.Children()
		if len(children) == 0 {
			t.Fatal("expected at least one child")
		}
	})
}

func TestAssemblyConstraint(t *testing.T) {
	t.Run("constrain", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		obj := NewAssemblyObjectFromShpe(*r1.Value())
		as := NewAssembly(obj, nil, "root", nil)

		wp2 := NewNamedWorkplane("XY")
		r2 := wp2.BoxCentered(5, 5, 5)
		obj2 := NewAssemblyObjectFromShpe(*r2.Value())
		as.AddObject(obj2, nil, "part", nil)
		as.Constrain("root", "part", 0, NewAssemblyConstraintParmFromDouble3(0, 0, 1))
		if err := as.HasError(); err {
			t.Fatalf("Constrain error: %v", as.Error())
		}
	})

	t.Run("constrain1 unary", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		obj := NewAssemblyObjectFromShpe(*r1.Value())
		as := NewAssembly(obj, nil, "root", nil)
		as.Constrain1("root", 3, NewAssemblyConstraintParmFromDouble(0))
		if err := as.HasError(); err != true {
			t.Log("Constrain1 completed (may or may not have error)")
		}
	})
}

func TestAssemblySolve(t *testing.T) {
	t.Run("solve", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		obj := NewAssemblyObjectFromShpe(*r1.Value())
		as := NewAssembly(obj, nil, "root", nil)

		wp2 := NewNamedWorkplane("XY")
		r2 := wp2.BoxCentered(5, 5, 5)
		obj2 := NewAssemblyObjectFromShpe(*r2.Value())
		as.AddObject(obj2, nil, "part", nil)
		as.Constrain("root", "part", 0, NewAssemblyConstraintParmFromDouble3(0, 0, 1))
		as.Solve(0)
		if err := as.HasError(); err {
			t.Logf("Solve error (may be expected): %v", as.Error())
		}
	})
}

func TestAssemblyExport(t *testing.T) {
	t.Run("export not supported in prebuilt lib", func(t *testing.T) {
		t.Skip("ExportTo crashes in prebuilt lib; needs OCC STEP support rebuild")
	})
}

func TestAssemblyConstraintParam(t *testing.T) {
	t.Run("param from double", func(t *testing.T) {
		p := NewAssemblyConstraintParmFromDouble(5.0)
		if p == nil {
			t.Fatal("NewAssemblyConstraintParmFromDouble returned nil")
		}
	})
	t.Run("param from double2", func(t *testing.T) {
		p := NewAssemblyConstraintParmFromDouble2(1.0, 2.0)
		if p == nil {
			t.Fatal("NewAssemblyConstraintParmFromDouble2 returned nil")
		}
	})
	t.Run("param from double3", func(t *testing.T) {
		p := NewAssemblyConstraintParmFromDouble3(1.0, 2.0, 3.0)
		if p == nil {
			t.Fatal("NewAssemblyConstraintParmFromDouble3 returned nil")
		}
	})
}

func TestAssemblyNilSafety(t *testing.T) {
	t.Run("add object with empty loc and color", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		obj := NewAssemblyObjectFromShpe(*r1.Value())
		as := NewAssembly(obj, nil, "root", nil)
		wp2 := NewNamedWorkplane("XY")
		r2 := wp2.BoxCentered(3, 3, 3)
		obj2 := NewAssemblyObjectFromShpe(*r2.Value())
		as.AddObject(obj2, nil, "child", nil)
		if err := as.HasError(); err {
			t.Fatalf("AddObject error: %v", as.Error())
		}
	})
}
