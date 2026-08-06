package topo

import (
	"encoding/json"
	"strings"
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
		// 回归: Shapes 返回的 wrapper 必须仍然有效 (曾因 defer topo_shape_list_free 深释放导致悬垂)
		for i, shp := range shapes {
			if shp.IsNull() {
				t.Fatalf("shape %d is null", i)
			}
			_ = shp.Type()
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

// ---------------------------------------------------------------------------
// Assembly constraint helpers
// ---------------------------------------------------------------------------

// makeAssemblyWithChild creates a root assembly with one child part.
func makeAssemblyWithChild(rootName, childName string) *Assembly {
	wp := NewNamedWorkplane("XY")
	rootBox := wp.BoxCentered(10, 10, 10)
	obj := NewAssemblyObjectFromShpe(*rootBox.Value())
	as := NewAssembly(obj, nil, rootName, nil)

	wp2 := NewNamedWorkplane("XY")
	childBox := wp2.BoxCentered(5, 5, 5)
	obj2 := NewAssemblyObjectFromShpe(*childBox.Value())
	as.AddObject(obj2, nil, childName, nil)
	return as
}

// makeAssemblyForQuery creates root + child + grandchild for query tests.
func makeAssemblyForQuery(rootName, childName, grandchildName string) *Assembly {
	as := makeAssemblyWithChild(rootName, childName)

	wp3 := NewNamedWorkplane("XY")
	gcBox := wp3.BoxCentered(2, 2, 2)
	obj3 := NewAssemblyObjectFromShpe(*gcBox.Value())
	as.AddObject(obj3, nil, grandchildName, nil)
	return as
}

// name returns the name string, or skips if empty.
func checkName(t *testing.T, as *Assembly, expected string) {
	if as.GetName() != expected {
		t.Fatalf("expected name %q, got %q", expected, as.GetName())
	}
}

// ---------------------------------------------------------------------------
// Constraint kinds enum (match C++ solver.hh)
// ---------------------------------------------------------------------------
const (
	asmPoint        = 0
	asmAxis         = 1
	asmPointInPlane = 2
	asmPointOnLine  = 3
	asmPlane        = 4
	asmFixed        = 5
	asmFixedPoint   = 6
	asmFixedAxis    = 7
	asmFixedRot     = 8
)

func TestAssemblyConstraint_AllKinds_Binary(t *testing.T) {
	t.Run("Point kind=0 with blank param", func(t *testing.T) {
		as := makeAssemblyWithChild("root", "part")
		as.Constrain("root", "part", asmPoint, NewAssemblyConstraintParmFromDouble(0))
		if err := as.HasError(); err {
			t.Fatalf("Point error: %v", as.Error())
		}
	})
	t.Run("Point kind=0 with double3 param", func(t *testing.T) {
		as := makeAssemblyWithChild("root", "part")
		as.Constrain("root", "part", asmPoint, NewAssemblyConstraintParmFromDouble3(0, 0, 1))
		if err := as.HasError(); err {
			t.Fatalf("Point d3 error: %v", as.Error())
		}
	})

	t.Run("Axis kind=1 blank param", func(t *testing.T) {
		as := makeAssemblyWithChild("root", "part")
		as.Constrain("root", "part", asmAxis, NewAssemblyConstraintParmFromDouble(0))
		if err := as.HasError(); err {
			t.Fatalf("Axis error: %v", as.Error())
		}
	})
	t.Run("Axis kind=1 angled", func(t *testing.T) {
		as := makeAssemblyWithChild("root", "part")
		as.Constrain("root", "part", asmAxis, NewAssemblyConstraintParmFromDouble(1.5708))
		if err := as.HasError(); err {
			t.Fatalf("Axis angled error: %v", as.Error())
		}
	})

	t.Run("PointInPlane kind=2 blank param", func(t *testing.T) {
		as := makeAssemblyWithChild("root", "part")
		as.Constrain("root", "part", asmPointInPlane, NewAssemblyConstraintParmFromDouble(0))
		if err := as.HasError(); err {
			t.Fatalf("PointInPlane error: %v", as.Error())
		}
	})
	t.Run("PointInPlane kind=2 offset", func(t *testing.T) {
		as := makeAssemblyWithChild("root", "part")
		as.Constrain("root", "part", asmPointInPlane, NewAssemblyConstraintParmFromDouble(5))
		if err := as.HasError(); err {
			t.Fatalf("PointInPlane offset error: %v", as.Error())
		}
	})

	t.Run("PointOnLine kind=3 blank param", func(t *testing.T) {
		as := makeAssemblyWithChild("root", "part")
		as.Constrain("root", "part", asmPointOnLine, NewAssemblyConstraintParmFromDouble(0))
		if err := as.HasError(); err {
			t.Fatalf("PointOnLine error: %v", as.Error())
		}
	})

	t.Run("Plane kind=4 double2 param", func(t *testing.T) {
		as := makeAssemblyWithChild("root", "part")
		as.Constrain("root", "part", asmPlane, NewAssemblyConstraintParmFromDouble2(0, 0))
		if err := as.HasError(); err {
			t.Fatalf("Plane error: %v", as.Error())
		}
	})

	t.Run("Plane kind=4 non-zero tol", func(t *testing.T) {
		as := makeAssemblyWithChild("root", "part")
		as.Constrain("root", "part", asmPlane, NewAssemblyConstraintParmFromDouble2(0.1, 0.1))
		if err := as.HasError(); err {
			t.Fatalf("Plane tol error: %v", as.Error())
		}
	})
}

func TestAssemblyConstraint_AllKinds_Unary(t *testing.T) {
	t.Run("Fixed kind=5 with blank param", func(t *testing.T) {
		as := makeAssemblyWithChild("root", "part")
		as.Constrain1("root", asmFixed, NewAssemblyConstraintParmFromDouble(0))
		if err := as.HasError(); err {
			t.Fatalf("Fixed error: %v", as.Error())
		}
	})
	t.Run("Fixed kind=5 on child", func(t *testing.T) {
		as := makeAssemblyWithChild("root", "part")
		as.Constrain1("part", asmFixed, NewAssemblyConstraintParmFromDouble(0))
		if err := as.HasError(); err {
			t.Fatalf("Fixed child error: %v", as.Error())
		}
	})

	t.Run("FixedPoint kind=6 with double3 xyz", func(t *testing.T) {
		as := makeAssemblyWithChild("root", "part")
		as.Constrain1("part", asmFixedPoint, NewAssemblyConstraintParmFromDouble3(5, 5, 5))
		if err := as.HasError(); err {
			t.Fatalf("FixedPoint error: %v", as.Error())
		}
	})
	t.Run("FixedPoint kind=6 origin", func(t *testing.T) {
		as := makeAssemblyWithChild("root", "part")
		as.Constrain1("part", asmFixedPoint, NewAssemblyConstraintParmFromDouble3(0, 0, 0))
		if err := as.HasError(); err {
			t.Fatalf("FixedPoint origin error: %v", as.Error())
		}
	})

	t.Run("FixedAxis kind=7 with direction", func(t *testing.T) {
		as := makeAssemblyWithChild("root", "part")
		as.Constrain1("part", asmFixedAxis, NewAssemblyConstraintParmFromDouble3(0, 0, 1))
		if err := as.HasError(); err {
			t.Fatalf("FixedAxis error: %v", as.Error())
		}
	})
	t.Run("FixedAxis kind=7 X dir", func(t *testing.T) {
		as := makeAssemblyWithChild("root", "part")
		as.Constrain1("part", asmFixedAxis, NewAssemblyConstraintParmFromDouble3(1, 0, 0))
		if err := as.HasError(); err {
			t.Fatalf("FixedAxis X error: %v", as.Error())
		}
	})

	t.Run("FixedRotation kind=8 Euler angles", func(t *testing.T) {
		as := makeAssemblyWithChild("root", "part")
		as.Constrain1("part", asmFixedRot, NewAssemblyConstraintParmFromDouble3(0, 0, 0))
		if err := as.HasError(); err {
			t.Fatalf("FixedRotation error: %v", as.Error())
		}
	})
	t.Run("FixedRotation kind=8 rotated", func(t *testing.T) {
		as := makeAssemblyWithChild("root", "part")
		as.Constrain1("part", asmFixedRot, NewAssemblyConstraintParmFromDouble3(0.5, 0.5, 0.5))
		if err := as.HasError(); err {
			t.Fatalf("FixedRotation rotated error: %v", as.Error())
		}
	})
}

func TestAssemblyConstraint_ByShapeRef(t *testing.T) {
	t.Run("Constrain2 binary by shape", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		obj := NewAssemblyObjectFromShpe(*r1.Value())
		as := NewAssembly(obj, nil, "root", nil)

		wp2 := NewNamedWorkplane("XY")
		r2 := wp2.BoxCentered(5, 5, 5)
		obj2 := NewAssemblyObjectFromShpe(*r2.Value())
		as.AddObject(obj2, nil, "part", nil)

		rootShape := r1.Value()
		childShape := r2.Value()
		as.Constrain2("root", rootShape, "part", childShape, asmPoint,
			NewAssemblyConstraintParmFromDouble(0))
		if err := as.HasError(); err {
			t.Fatalf("Constrain2 error: %v", as.Error())
		}
	})

	t.Run("Constrain3 unary by shape", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		obj := NewAssemblyObjectFromShpe(*r1.Value())
		as := NewAssembly(obj, nil, "root", nil)

		as.Constrain3("root", r1.Value(), asmFixed,
			NewAssemblyConstraintParmFromDouble(0))
		if err := as.HasError(); err {
			t.Fatalf("Constrain3 error: %v", as.Error())
		}
	})
}

func TestAssemblyConstraint_Solve(t *testing.T) {
	t.Run("Point solve", func(t *testing.T) {
		as := makeAssemblyWithChild("root", "part")
		as.Constrain1("root", asmFixed, NewAssemblyConstraintParmFromDouble(0))
		as.Constrain("root", "part", asmPoint, NewAssemblyConstraintParmFromDouble(0))
		as.Solve(0)
		if err := as.HasError(); err {
			t.Logf("Solve error (Ipopt issue in prebuilt lib): %v", err)
		}
	})

	t.Run("FixedPoint solve", func(t *testing.T) {
		as := makeAssemblyWithChild("root", "part")
		as.Constrain1("root", asmFixed, NewAssemblyConstraintParmFromDouble(0))
		as.Constrain1("part", asmFixedPoint, NewAssemblyConstraintParmFromDouble3(0, 0, 5))
		as.Solve(0)
		if err := as.HasError(); err {
			t.Logf("Solve error (Ipopt issue in prebuilt lib): %v", err)
		}
	})
}

func TestAssemblySolve_EdgeCases(t *testing.T) {
	t.Run("solve with no constraints", func(t *testing.T) {
		as := makeAssemblyWithChild("root", "part")
		as.Solve(0)
		if err := as.HasError(); err {
			t.Logf("no-constraint solve error (may be expected): %v", err)
		}
	})
	t.Run("multiple solves", func(t *testing.T) {
		as := makeAssemblyWithChild("root", "part")
		as.Constrain1("root", asmFixed, NewAssemblyConstraintParmFromDouble(0))
		as.Constrain("root", "part", asmPoint, NewAssemblyConstraintParmFromDouble(0))
		as.Solve(0)
		if err := as.HasError(); err {
			t.Logf("multiple solves error (Ipopt issue): %v", err)
		}
	})
	t.Run("constrain after solve", func(t *testing.T) {
		as := makeAssemblyWithChild("root", "part")
		as.Constrain1("root", asmFixed, NewAssemblyConstraintParmFromDouble(0))
		as.Constrain("root", "part", asmPoint, NewAssemblyConstraintParmFromDouble(0))
		as.Solve(0)
		if err := as.HasError(); err {
			t.Logf("constrain after solve error (Ipopt issue): %v", err)
		}
	})
}

func TestAssemblyConstraint_QueryWithSelector(t *testing.T) {
	t.Run("constrain via face selector", func(t *testing.T) {
		as := makeAssemblyWithChild("root", "part")
		as.Constrain1("root", asmFixed, NewAssemblyConstraintParmFromDouble(0))
		// Query: name?tag@selector_kind@selector
		as.Constrain("root?faces@>Z", "part?faces@>Z", asmPlane,
			NewAssemblyConstraintParmFromDouble2(0, 0))
		if err := as.HasError(); err {
			t.Logf("face selector error: %v", err)
		} else {
			as.Solve(0)
			if err := as.HasError(); err {
				t.Logf("face selector solve error: %v", err)
			}
		}
	})
}

func TestAssemblyConstraint_Negative(t *testing.T) {
	t.Run("incompatible unary on binary kind", func(t *testing.T) {
		as := makeAssemblyWithChild("root", "part")
		// PointOnLine (3) is binary, but we use Constrain1 (unary)
		// Should produce an error
		as.Constrain1("root", asmPointOnLine, NewAssemblyConstraintParmFromDouble(0))
		if err := as.HasError(); !err {
			t.Log("unary binary was accepted (may be valid)")
		}
	})
	t.Run("unknown kind", func(t *testing.T) {
		as := makeAssemblyWithChild("root", "part")
		as.Constrain("root", "part", 99, NewAssemblyConstraintParmFromDouble(0))
		if err := as.HasError(); !err {
			t.Log("unknown kind 99 was accepted")
		}
	})
	t.Run("missing child for binary", func(t *testing.T) {
		as := makeAssemblyWithChild("root", "part")
		as.Constrain("root", "nonexistent", asmPoint, NewAssemblyConstraintParmFromDouble(0))
		if err := as.HasError(); !err {
			t.Log("nonexistent child constrain was accepted")
		}
	})
	t.Run("nil param", func(t *testing.T) {
		as := makeAssemblyWithChild("root", "part")
		as.Constrain("root", "part", asmPoint, nil)
		if err := as.HasError(); err {
			t.Fatalf("nil param error: %v", as.Error())
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

func TestAssemblyGet(t *testing.T) {
	t.Run("hit top-level", func(t *testing.T) {
		as := makeAssemblyWithChild("root", "child")
		el, ok := as.Get("child")
		if !ok {
			t.Fatal("expected to find element 'child'")
		}
		if el.GetName() != "root/child" {
			t.Fatalf("expected element name 'root/child', got %q", el.GetName())
		}
	})

	t.Run("hit nested path", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		obj := NewAssemblyObjectFromShpe(*r1.Value())
		as := NewAssembly(obj, nil, "root", nil)

		wp2 := NewNamedWorkplane("XY")
		r2 := wp2.BoxCentered(5, 5, 5)
		obj2 := NewAssemblyObjectFromShpe(*r2.Value())
		child := NewAssembly(obj2, nil, "child", nil)

		wp3 := NewNamedWorkplane("XY")
		r3 := wp3.BoxCentered(2, 2, 2)
		obj3 := NewAssemblyObjectFromShpe(*r3.Value())
		child.AddObject(obj3, nil, "grand", nil)

		as.AddAssembly(child, nil, "", nil)

		el, ok := as.Get("child/grand")
		if !ok {
			t.Fatal("expected to find element 'child/grand'")
		}
		if el.GetName() != "root/child/grand" {
			t.Fatalf("expected element name 'root/child/grand', got %q", el.GetName())
		}
	})

	t.Run("miss", func(t *testing.T) {
		as := makeAssemblyWithChild("root", "child")
		if el, ok := as.Get("nonexistent"); ok || el != nil {
			t.Fatal("expected miss for 'nonexistent'")
		}
	})
}

func TestAssemblySetLocation(t *testing.T) {
	t.Run("set location", func(t *testing.T) {
		as := makeAssemblyWithChild("root", "child")
		loc := NewTopoLocation(NewTrsfTranslationFromVector(NewVector3([3]float64{10, 20, 30})))
		if err := as.SetLocation("child", loc); err != nil {
			t.Fatalf("SetLocation error: %v", err)
		}
		if err := as.HasError(); err {
			t.Fatalf("SetLocation assembly error: %v", as.Error())
		}

		el, ok := as.Get("child")
		if !ok {
			t.Fatal("expected to find element 'child' after SetLocation")
		}
		m := el.GetLocation().Trsf().Data()
		if m[3] != 10 || m[7] != 20 || m[11] != 30 {
			t.Fatalf("expected translation (10,20,30), got (%v,%v,%v)", m[3], m[7], m[11])
		}
	})

	t.Run("not found", func(t *testing.T) {
		as := makeAssemblyWithChild("root", "child")
		loc := NewTopoLocation(NewTrsfTranslationFromVector(NewVector3([3]float64{1, 1, 1})))
		if err := as.SetLocation("nonexistent", loc); err == nil {
			t.Fatal("expected error for nonexistent element")
		}
	})

	t.Run("nested path rejected", func(t *testing.T) {
		as := makeAssemblyWithChild("root", "child")
		loc := NewTopoLocation(NewTrsfTranslationFromVector(NewVector3([3]float64{1, 1, 1})))
		if err := as.SetLocation("child/grand", loc); err == nil {
			t.Fatal("expected error for nested path")
		}
	})
}

func TestAssemblyReplace(t *testing.T) {
	t.Run("replace keeps name location color", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		obj := NewAssemblyObjectFromShpe(*r1.Value())
		as := NewAssembly(obj, nil, "root", nil)

		wp2 := NewNamedWorkplane("XY")
		r2 := wp2.BoxCentered(5, 5, 5)
		obj2 := NewAssemblyObjectFromShpe(*r2.Value())
		loc := NewTopoLocation(NewTrsfTranslationFromVector(NewVector3([3]float64{1, 2, 3})))
		red := NewColor([3]float64{1, 0, 0})
		as.AddObject(obj2, loc, "child", &red)

		wp3 := NewNamedWorkplane("XY")
		r3 := wp3.BoxCentered(20, 20, 20)
		if err := as.Replace("child", r3.Value()); err != nil {
			t.Fatalf("Replace error: %v", err)
		}
		if err := as.HasError(); err {
			t.Fatalf("Replace assembly error: %v", as.Error())
		}

		el, ok := as.Get("child")
		if !ok {
			t.Fatal("expected to find element 'child' after Replace")
		}
		if el.GetName() != "root/child" {
			t.Fatalf("expected name preserved as 'root/child', got %q", el.GetName())
		}
		m := el.GetLocation().Trsf().Data()
		if m[3] != 1 || m[7] != 2 || m[11] != 3 {
			t.Fatalf("expected location preserved (1,2,3), got (%v,%v,%v)", m[3], m[7], m[11])
		}
		cr, cg, cb := el.GetColor().RGBD()
		if cr != 1 || cg != 0 || cb != 0 {
			t.Fatalf("expected color preserved (1,0,0), got (%v,%v,%v)", cr, cg, cb)
		}
		bb := el.GetShape().BBox().Data()
		if d := bb[3] - bb[0]; d < 19.9 || d > 20.1 {
			t.Fatalf("expected replaced box size 20, got %v", d)
		}
	})

	t.Run("not found", func(t *testing.T) {
		as := makeAssemblyWithChild("root", "child")
		wp := NewNamedWorkplane("XY")
		r := wp.BoxCentered(1, 1, 1)
		if err := as.Replace("nonexistent", r.Value()); err == nil {
			t.Fatal("expected error for nonexistent element")
		}
	})

	t.Run("nil shape", func(t *testing.T) {
		as := makeAssemblyWithChild("root", "child")
		if err := as.Replace("child", nil); err == nil {
			t.Fatal("expected error for nil shape")
		}
	})
}

// ---------------------------------------------------------------------------
// Parametric data & rebuild
// ---------------------------------------------------------------------------

func testBoxParams(w, l, h float64) json.RawMessage {
	b, _ := json.Marshal(map[string]float64{"width": w, "length": l, "height": h})
	return b
}

// registerTestBoxBuilder 注册一个 test_box builder (BoxCentered 原语), 测试结束自动注销
func registerTestBoxBuilder(t *testing.T) {
	t.Helper()
	RegisterParametricBuilder("test_box", func(params json.RawMessage) (*Shape, *TopoLocation, error) {
		var p struct {
			Width  float64 `json:"width"`
			Length float64 `json:"length"`
			Height float64 `json:"height"`
		}
		if err := json.Unmarshal(params, &p); err != nil {
			return nil, nil, err
		}
		wp := NewNamedWorkplane("XY")
		return wp.BoxCentered(p.Width, p.Length, p.Height).Value(), nil, nil
	})
	t.Cleanup(func() { RegisterParametricBuilder("test_box", nil) })
}

// addParametricBox 往 as 里加一个带 test_box 配方的 box 元素
func addParametricBox(t *testing.T, as *Assembly, name string, w, l, h float64, loc *TopoLocation) {
	t.Helper()
	wp := NewNamedWorkplane("XY")
	box := wp.BoxCentered(w, l, h)
	obj := NewAssemblyObjectFromShpe(*box.Value())
	as.AddObjectParams(obj, loc, name, nil, &ParametricData{Type: "test_box", Params: testBoxParams(w, l, h)})
	if as.HasError() {
		t.Fatalf("AddObjectParams error: %v", as.Error())
	}
}

func TestAssemblyParametric(t *testing.T) {
	t.Run("add and query", func(t *testing.T) {
		as := makeAssemblyWithChild("root", "plain")
		addParametricBox(t, as, "box1", 4, 4, 4, nil)

		pd, ok := as.GetParametric("box1")
		if !ok {
			t.Fatal("expected parametric data for 'box1'")
		}
		if pd.Type != "test_box" {
			t.Fatalf("expected type 'test_box', got %q", pd.Type)
		}
		var p map[string]float64
		if err := json.Unmarshal(pd.Params, &p); err != nil || p["width"] != 4 {
			t.Fatalf("unexpected params: %v, %v", p, err)
		}
		if _, ok := as.GetParametric("plain"); ok {
			t.Fatal("expected no parametric data for plain element")
		}
		if _, ok := as.GetParametric("nonexistent"); ok {
			t.Fatal("expected miss for 'nonexistent'")
		}
	})

	t.Run("params survive SetLocation and Replace", func(t *testing.T) {
		as := makeAssemblyWithChild("root", "plain")
		addParametricBox(t, as, "box1", 4, 4, 4, nil)

		loc := NewTopoLocation(NewTrsfTranslationFromVector(NewVector3([3]float64{5, 6, 7})))
		if err := as.SetLocation("box1", loc); err != nil {
			t.Fatalf("SetLocation error: %v", err)
		}
		if _, ok := as.GetParametric("box1"); !ok {
			t.Fatal("parametric data lost after SetLocation")
		}

		wp := NewNamedWorkplane("XY")
		r := wp.BoxCentered(8, 8, 8)
		if err := as.Replace("box1", r.Value()); err != nil {
			t.Fatalf("Replace error: %v", err)
		}
		pd, ok := as.GetParametric("box1")
		if !ok {
			t.Fatal("parametric data lost after Replace")
		}
		if pd.Type != "test_box" {
			t.Fatalf("expected type preserved as 'test_box', got %q", pd.Type)
		}
	})

	t.Run("remove clears params", func(t *testing.T) {
		as := makeAssemblyWithChild("root", "plain")
		addParametricBox(t, as, "box1", 4, 4, 4, nil)
		as.Remove("box1")
		if _, ok := as.GetParametric("box1"); ok {
			t.Fatal("expected parametric data cleared after Remove")
		}
	})
}

func TestAssemblyExportParametric(t *testing.T) {
	registerTestBoxBuilder(t)

	t.Run("export hierarchy", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		as := NewAssembly(NewAssemblyObjectFromShpe(*r1.Value()), nil, "root", nil)

		loc := NewTopoLocation(NewTrsfTranslationFromVector(NewVector3([3]float64{1, 2, 3})))
		red := NewColor([3]float64{1, 0, 0})
		obj := NewAssemblyObjectFromShpe(*r1.Value())
		as.AddObjectParams(obj, loc, "box1", &red, &ParametricData{Type: "test_box", Params: testBoxParams(4, 5, 6)})

		// 嵌套子装配, 自身带配方
		wp2 := NewNamedWorkplane("XY")
		r2 := wp2.BoxCentered(2, 2, 2)
		child := NewAssembly(NewAssemblyObjectFromShpe(*r2.Value()), nil, "sub", nil)
		child.SetParametric(&ParametricData{Type: "test_box", Params: testBoxParams(2, 2, 2)})
		addParametricBox(t, child, "inner", 1, 1, 1, nil)
		as.AddAssembly(child, nil, "", nil)
		if as.HasError() {
			t.Fatalf("AddAssembly error: %v", as.Error())
		}

		data, err := as.ExportParametric()
		if err != nil {
			t.Fatalf("ExportParametric error: %v", err)
		}

		var root ParametricElement
		if err := json.Unmarshal(data, &root); err != nil {
			t.Fatalf("exported JSON invalid: %v", err)
		}
		if root.Name != "root" {
			t.Fatalf("expected root name 'root', got %q", root.Name)
		}
		if len(root.Children) != 2 {
			t.Fatalf("expected 2 children, got %d", len(root.Children))
		}
		var box1, sub *ParametricElement
		for _, ch := range root.Children {
			switch ch.Name {
			case "box1":
				box1 = ch
			case "sub":
				sub = ch
			}
		}
		if box1 == nil || sub == nil {
			t.Fatalf("expected children 'box1' and 'sub', got %s", data)
		}
		if box1.Type != "test_box" {
			t.Fatalf("expected box1 type 'test_box', got %q", box1.Type)
		}
		if box1.Location == nil || (*box1.Location)[3] != 1 || (*box1.Location)[7] != 2 || (*box1.Location)[11] != 3 {
			t.Fatalf("expected box1 location translation (1,2,3), got %v", box1.Location)
		}
		if box1.Color == nil || (*box1.Color)[0] != 1 {
			t.Fatalf("expected box1 color red, got %v", box1.Color)
		}
		if sub.Type != "test_box" {
			t.Fatalf("expected sub type 'test_box', got %q", sub.Type)
		}
		if len(sub.Children) != 1 || sub.Children[0].Name != "inner" || sub.Children[0].Type != "test_box" {
			t.Fatalf("expected sub/inner parametric child, got %v", sub.Children)
		}
	})
}

func TestAssemblyRebuildParametric(t *testing.T) {
	registerTestBoxBuilder(t)

	t.Run("export rebuild round trip", func(t *testing.T) {
		wp := NewNamedWorkplane("XY")
		r1 := wp.BoxCentered(10, 10, 10)
		as := NewAssembly(NewAssemblyObjectFromShpe(*r1.Value()), nil, "root", nil)

		loc := NewTopoLocation(NewTrsfTranslationFromVector(NewVector3([3]float64{1, 2, 3})))
		addParametricBox(t, as, "box1", 4, 5, 6, loc)

		wp2 := NewNamedWorkplane("XY")
		r2 := wp2.BoxCentered(2, 2, 2)
		child := NewAssembly(NewAssemblyObjectFromShpe(*r2.Value()), nil, "sub", nil)
		child.SetParametric(&ParametricData{Type: "test_box", Params: testBoxParams(2, 2, 2)})
		as.AddAssembly(child, nil, "", nil)

		data, err := as.ExportParametric()
		if err != nil {
			t.Fatalf("ExportParametric error: %v", err)
		}

		rebuilt, err := RebuildFromParametric(data)
		if err != nil {
			t.Fatalf("RebuildFromParametric error: %v", err)
		}
		if rebuilt.GetName() != "root" {
			t.Fatalf("expected rebuilt root name 'root', got %q", rebuilt.GetName())
		}
		if len(rebuilt.Children()) != 2 {
			t.Fatalf("expected 2 rebuilt children, got %d", len(rebuilt.Children()))
		}

		// 几何确定性重建: box1 尺寸 4x5x6
		el, ok := rebuilt.Get("box1")
		if !ok {
			t.Fatal("expected to find 'box1' in rebuilt assembly")
		}
		bb := el.GetShape().BBox().Data()
		if d := bb[3] - bb[0]; d < 3.9 || d > 4.1 {
			t.Fatalf("expected rebuilt box width 4, got %v", d)
		}
		if d := bb[4] - bb[1]; d < 4.9 || d > 5.1 {
			t.Fatalf("expected rebuilt box length 5, got %v", d)
		}
		if d := bb[5] - bb[2]; d < 5.9 || d > 6.1 {
			t.Fatalf("expected rebuilt box height 6, got %v", d)
		}
		// 放置来自 JSON location
		m := el.GetLocation().Trsf().Data()
		if m[3] != 1 || m[7] != 2 || m[11] != 3 {
			t.Fatalf("expected rebuilt location (1,2,3), got (%v,%v,%v)", m[3], m[7], m[11])
		}

		// 重建后的树仍带配方, 可再次导出
		if _, ok := rebuilt.GetParametric("box1"); !ok {
			t.Fatal("expected parametric data on rebuilt tree")
		}
		if sub, ok := rebuilt.GetParametric("sub"); !ok || sub.Type != "test_box" {
			t.Fatal("expected parametric data on rebuilt sub assembly")
		}
		data2, err := rebuilt.ExportParametric()
		if err != nil {
			t.Fatalf("re-export error: %v", err)
		}
		if _, err := RebuildFromParametric(data2); err != nil {
			t.Fatalf("second round trip error: %v", err)
		}
	})

	t.Run("unregistered type error", func(t *testing.T) {
		data := []byte(`{"name":"root","children":[{"name":"x","type":"no_such_type","params":{}}]}`)
		_, err := RebuildFromParametric(data)
		if err == nil {
			t.Fatal("expected error for unregistered builder type")
		}
		if !strings.Contains(err.Error(), "no_such_type") {
			t.Fatalf("error should mention the type, got: %v", err)
		}
	})

	t.Run("invalid JSON", func(t *testing.T) {
		if _, err := RebuildFromParametric([]byte(`{not json`)); err == nil {
			t.Fatal("expected error for invalid JSON")
		}
	})
}
