package topo

import (
	"testing"
)

func makeBoxShape(t *testing.T) *Shape {
	wp := NewNamedWorkplane("XY")
	r := wp.BoxCorners(10, 10, 10)
	return r.Value()
}

// validStringSyntax verifies a string-syntax selector parses without error.
func validStringSyntax(t *testing.T, name, expr string) {
	t.Run(name, func(t *testing.T) {
		s := NewStringSyntaxSelector(expr)
		if s == nil {
			t.Fatalf("NewStringSyntaxSelector(%q) returned nil", expr)
		}
	})
}

// expectStringSyntaxFails verifies a string-syntax selector is rejected.
func expectStringSyntaxFails(t *testing.T, name, expr string) {
	t.Run(name, func(t *testing.T) {
		s := NewStringSyntaxSelector(expr)
		if s != nil {
			t.Fatalf("NewStringSyntaxSelector(%q) should have returned nil", expr)
		}
	})
}

func TestSelectorConstructors(t *testing.T) {
	t.Run("nearest to point", func(t *testing.T) {
		v := NewTopoVector(5, 5, 5)
		s := NewNearestToPointSelector(v)
		if s == nil {
			t.Fatal("NewNearestToPointSelector returned nil")
		}
	})
	t.Run("box selector", func(t *testing.T) {
		p0 := NewTopoVector(0, 0, 0)
		p1 := NewTopoVector(10, 10, 10)
		s := NewBoxSelector(p0, p1, false)
		if s == nil {
			t.Fatal("NewBoxSelector returned nil")
		}
	})
	t.Run("radius nth", func(t *testing.T) {
		s := NewRadiusNthSelector(0, true, 1e-4)
		if s == nil {
			t.Fatal("NewRadiusNthSelector returned nil")
		}
	})
	t.Run("center nth", func(t *testing.T) {
		dir := NewTopoVector(0, 0, 1)
		s := NewCenterNthSelector(dir, 0, true, 1e-4)
		if s == nil {
			t.Fatal("NewCenterNthSelector returned nil")
		}
	})
	t.Run("direction minmax", func(t *testing.T) {
		dir := NewTopoVector(0, 0, 1)
		s := NewDirectionMinmaxSelector(dir, true, 1e-4)
		if s == nil {
			t.Fatal("NewDirectionMinmaxSelector returned nil")
		}
	})
	t.Run("parallel dir", func(t *testing.T) {
		dir := NewTopoVector(0, 0, 1)
		s := NewParallelDirSelector(dir, 1e-4)
		if s == nil {
			t.Fatal("NewParallelDirSelector returned nil")
		}
	})
	t.Run("dir selector", func(t *testing.T) {
		dir := NewTopoVector(0, 0, 1)
		s := NewDirSelector(dir, 1e-4)
		if s == nil {
			t.Fatal("NewDirSelector returned nil")
		}
	})
	t.Run("perpendicular dir", func(t *testing.T) {
		dir := NewTopoVector(0, 0, 1)
		s := NewPerpendicularDirSelector(dir, 1e-4)
		if s == nil {
			t.Fatal("NewPerpendicularDirSelector returned nil")
		}
	})
	t.Run("direction nth", func(t *testing.T) {
		dir := NewTopoVector(0, 0, 1)
		s := NewDirectionNthSelector(dir, 0, true, 1e-4)
		if s == nil {
			t.Fatal("NewDirectionNthSelector returned nil")
		}
	})
	t.Run("length nth", func(t *testing.T) {
		s := NewLengthNthSelector(0, true, 1e-4)
		if s == nil {
			t.Fatal("NewLengthNthSelector returned nil")
		}
	})
	t.Run("type selector", func(t *testing.T) {
		s := NewTypeSelector(TopoFace)
		if s == nil {
			t.Fatal("NewTypeSelector returned nil")
		}
	})
	t.Run("area nth", func(t *testing.T) {
		s := NewAreaNthSelector(0, true, 1e-4)
		if s == nil {
			t.Fatal("NewAreaNthSelector returned nil")
		}
	})
	t.Run("string syntax", func(t *testing.T) {
		s := NewStringSyntaxSelector(">Z")
		if s == nil {
			t.Fatal("NewStringSyntaxSelector returned nil")
		}
	})
}

func TestSelectorCombine(t *testing.T) {
	t.Run("and selector", func(t *testing.T) {
		l := NewTypeSelector(TopoFace)
		r := NewTypeSelector(TopoEdge)
		s := NewAndSelector(l, r)
		if s == nil {
			t.Fatal("NewAndSelector returned nil")
		}
	})
	t.Run("or selector", func(t *testing.T) {
		l := NewTypeSelector(TopoFace)
		r := NewTypeSelector(TopoEdge)
		s := NewOrSelector(l, r)
		if s == nil {
			t.Fatal("NewOrSelector returned nil")
		}
	})
	t.Run("subtract selector", func(t *testing.T) {
		l := NewTypeSelector(TopoFace)
		r := NewTypeSelector(TopoEdge)
		s := NewSubtractSelector(l, r)
		if s == nil {
			t.Fatal("NewSubtractSelector returned nil")
		}
	})
	t.Run("not selector", func(t *testing.T) {
		s := NewNotSelector(NewTypeSelector(TopoFace))
		if s == nil {
			t.Fatal("NewNotSelector returned nil")
		}
	})
	t.Run("string syntax combine", func(t *testing.T) {
		l := NewStringSyntaxSelector(">Z")
		r := NewTypeSelector(TopoEdge)
		s := NewAndSelector(l, r)
		if s == nil {
			t.Fatal("NewAndSelector with string syntax returned nil")
		}
	})
}

func TestSelectorCustom(t *testing.T) {
	t.Run("custom selector", func(t *testing.T) {
		s := NewCustomSelector(func(shapes []*Shape) []*Shape {
			return shapes[:0]
		})
		if s == nil {
			t.Fatal("NewCustomSelector returned nil")
		}
	})
}

// ---------------------------------------------------------------------------
// String-syntax selector grammar: all parser rules
// ---------------------------------------------------------------------------

func TestSelectorStringSyntax_Directions(t *testing.T) {
	validStringSyntax(t, "greater Z", ">Z")
	validStringSyntax(t, "greater z", ">z")
	validStringSyntax(t, "greater X", ">X")
	validStringSyntax(t, "greater x", ">x")
	validStringSyntax(t, "greater Y", ">Y")
	validStringSyntax(t, "greater y", ">y")

	validStringSyntax(t, "greater XY", ">XY")
	validStringSyntax(t, "greater xy", ">xy")
	validStringSyntax(t, "greater XZ", ">XZ")
	validStringSyntax(t, "greater xz", ">xz")
	validStringSyntax(t, "greater YZ", ">YZ")
	validStringSyntax(t, "greater yz", ">yz")

	validStringSyntax(t, "less X", "<X")
	validStringSyntax(t, "less x", "<x")
	validStringSyntax(t, "less Y", "<Y")
	validStringSyntax(t, "less y", "<y")
	validStringSyntax(t, "less Z", "<Z")
	validStringSyntax(t, "less z", "<z")

	validStringSyntax(t, "greater vector", ">(1.5,-2.5,3.0)")
	validStringSyntax(t, "greater integer vector", ">(1,0,0)")
	validStringSyntax(t, "less vector", "<(0,-1,0)")

	expectStringSyntaxFails(t, "illegal direction", ">Q")
	expectStringSyntaxFails(t, "empty direction", ">()")
	expectStringSyntaxFails(t, "partial vector", ">(1,2)")
	expectStringSyntaxFails(t, "garbage after dir", ">Zx")
}

func TestSelectorStringSyntax_CenterNth(t *testing.T) {
	expectStringSyntaxFails(t, "center nth not in grammar", ">>Z")
}

func TestSelectorStringSyntax_TypeSelectors(t *testing.T) {
	types := []string{"plane", "cylinder", "cone", "sphere", "torus",
		"line", "circle", "ellipse", "hyperbola", "parabola"}
	for _, typ := range types {
		validStringSyntax(t, typ, "%"+typ)
		validStringSyntax(t, typ+" upper", "%"+upperFirst(typ))
	}
	expectStringSyntaxFails(t, "type with index unsupported", "%plane[2]")
	expectStringSyntaxFails(t, "face not in cqtype", "%face")
	expectStringSyntaxFails(t, "edge not in cqtype", "%edge")
}

func upperFirst(s string) string {
	if len(s) == 0 {
		return s
	}
	return string(s[0]-32) + s[1:]
}

func TestSelectorStringSyntax_NamedViews(t *testing.T) {
	validStringSyntax(t, "front", "front")
	validStringSyntax(t, "back", "back")
	validStringSyntax(t, "left", "left")
	validStringSyntax(t, "right", "right")
	validStringSyntax(t, "top", "top")
	validStringSyntax(t, "bottom", "bottom")

	validStringSyntax(t, "FRONT", "FRONT")
	validStringSyntax(t, "Back", "Back")
}

func TestSelectorStringSyntax_OtherOps(t *testing.T) {
	validStringSyntax(t, "pipe X", "|X")
	validStringSyntax(t, "hash Z", "#Z")
	validStringSyntax(t, "plus Y", "+Y")
	validStringSyntax(t, "minus X", "-X")

	validStringSyntax(t, "pipe vector", "|(0,0,1)")
	validStringSyntax(t, "hash vector", "#(1,1,0)")
	validStringSyntax(t, "plus vector", "+(0,1,0)")
	validStringSyntax(t, "minus vector", "-(1,0,0)")
}

func TestSelectorStringSyntax_IndexModifier(t *testing.T) {
	validStringSyntax(t, ">Z idx 0", ">Z[0]")
	validStringSyntax(t, ">Z idx 5", ">Z[5]")
	validStringSyntax(t, ">Z idx -1", ">Z[-1]")
	validStringSyntax(t, ">Z idx empty", ">Z[]")
	validStringSyntax(t, ">XY idx 1", ">XY[1]")
	validStringSyntax(t, "<X idx 3", "<X[3]")
	expectStringSyntaxFails(t, "center nth not in grammar", "<<Z[2]")
}

func TestSelectorStringSyntax_BooleanCombinations(t *testing.T) {
	validStringSyntax(t, "and", ">Z and %plane")
	validStringSyntax(t, "or", ">Z or %plane")
	validStringSyntax(t, "exc", ">Z exc %plane")

	validStringSyntax(t, "and nested l", "(>Z and >X)")
	validStringSyntax(t, "and nested r", "(>Z and >X) and %plane")
	validStringSyntax(t, "or nested", "(>Z or >X) or %plane")
	validStringSyntax(t, "exc nested", "(>Z exc >X) exc %plane")
	validStringSyntax(t, "mixed chained", ">Z and >X or %plane")
	validStringSyntax(t, "triple and", ">Z and >X and %plane")

	validStringSyntax(t, "complex 1", ">Z and >X or %sphere exc %circle")
	validStringSyntax(t, "complex 2", "((>Z and >X) or %sphere) exc %circle")
	validStringSyntax(t, "combined with vector", ">(1,0,0) and %plane")

	validStringSyntax(t, "or with named view", "front or back")
	validStringSyntax(t, "exc chain", ">Z exc >X exc >Y")
}

func TestSelectorStringSyntax_RejectInvalid(t *testing.T) {
	expectStringSyntaxFails(t, "empty", "")
	expectStringSyntaxFails(t, "only op", ">")
	expectStringSyntaxFails(t, "only type op", "%")
	expectStringSyntaxFails(t, "unknown keyword", ">Z andd %face")
	expectStringSyntaxFails(t, "unclosed paren", "(>Z and >X")
	expectStringSyntaxFails(t, "unopened paren", ">Z and >X)")
	expectStringSyntaxFails(t, "trailing garbage", ">Z and >X garbage")
	expectStringSyntaxFails(t, "double op", ">>Z")
}

func TestSelectorProgrammatic_Combine(t *testing.T) {
	face := TopoFace
	edge := TopoEdge
	solid := TopoSolid
	shell := TopoShell
	vertex := TopoVertex
	wire := TopoWire

	t.Run("and three types", func(t *testing.T) {
		a := NewAndSelector(NewTypeSelector(face), NewTypeSelector(edge))
		b := NewAndSelector(a, NewTypeSelector(solid))
		if b == nil {
			t.Fatal("triple and returned nil")
		}
	})
	t.Run("or three types", func(t *testing.T) {
		a := NewOrSelector(NewTypeSelector(face), NewTypeSelector(edge))
		b := NewOrSelector(a, NewTypeSelector(solid))
		if b == nil {
			t.Fatal("triple or returned nil")
		}
	})
	t.Run("subtract chain", func(t *testing.T) {
		a := NewSubtractSelector(NewTypeSelector(solid), NewTypeSelector(face))
		b := NewSubtractSelector(a, NewTypeSelector(edge))
		if b == nil {
			t.Fatal("chained subtract returned nil")
		}
	})
	t.Run("not then and", func(t *testing.T) {
		n := NewNotSelector(NewTypeSelector(edge))
		s := NewAndSelector(NewTypeSelector(face), n)
		if s == nil {
			t.Fatal("not+and returned nil")
		}
	})
	t.Run("nested mix", func(t *testing.T) {
		inner := NewAndSelector(NewTypeSelector(face), NewTypeSelector(edge))
		s := NewOrSelector(inner, NewTypeSelector(solid))
		if s == nil {
			t.Fatal("nested mix returned nil")
		}
	})
	t.Run("all types together", func(t *testing.T) {
		a := NewAndSelector(NewTypeSelector(face), NewTypeSelector(edge))
		b := NewOrSelector(NewTypeSelector(solid), NewTypeSelector(shell))
		c := NewSubtractSelector(a, b)
		d := NewAndSelector(c, NewTypeSelector(vertex))
		e := NewOrSelector(d, NewTypeSelector(wire))
		if e == nil {
			t.Fatal("deep tree returned nil")
		}
	})
	t.Run("and with dir selector", func(t *testing.T) {
		dir := NewTopoVector(0, 0, 1)
		ds := NewDirSelector(dir, 1e-4)
		s := NewAndSelector(NewTypeSelector(face), ds)
		if s == nil {
			t.Fatal("type+dir and returned nil")
		}
	})
	t.Run("or with box selector", func(t *testing.T) {
		p0 := NewTopoVector(-5, -5, -5)
		p1 := NewTopoVector(5, 5, 5)
		bs := NewBoxSelector(p0, p1, true)
		s := NewOrSelector(NewTypeSelector(face), bs)
		if s == nil {
			t.Fatal("type+box or returned nil")
		}
	})
	t.Run("not of center nth", func(t *testing.T) {
		dir := NewTopoVector(1, 0, 0)
		c := NewCenterNthSelector(dir, 0, true, 1e-4)
		s := NewNotSelector(c)
		if s == nil {
			t.Fatal("not center_nth returned nil")
		}
	})
}

func TestSelectorProgrammatic_MixedStringTypes(t *testing.T) {
	face := TopoFace

	t.Run("string syntax and type", func(t *testing.T) {
		l := NewStringSyntaxSelector(">Z")
		r := NewTypeSelector(face)
		s := NewAndSelector(l, r)
		if s == nil {
			t.Fatal("string+type and returned nil")
		}
	})
	t.Run("string syntax or type", func(t *testing.T) {
		l := NewStringSyntaxSelector("%plane")
		r := NewTypeSelector(face)
		s := NewOrSelector(l, r)
		if s == nil {
			t.Fatal("string+type or returned nil")
		}
	})
	t.Run("string syntax subtract type", func(t *testing.T) {
		l := NewStringSyntaxSelector(">Z and %plane")
		r := NewTypeSelector(face)
		s := NewSubtractSelector(l, r)
		if s == nil {
			t.Fatal("string+type subtract returned nil")
		}
	})
	t.Run("string syntax not", func(t *testing.T) {
		s := NewNotSelector(NewStringSyntaxSelector(">Z"))
		if s == nil {
			t.Fatal("not string_syntax returned nil")
		}
	})
	t.Run("two string syntaxes and", func(t *testing.T) {
		l := NewStringSyntaxSelector(">Z")
		r := NewStringSyntaxSelector("%plane")
		s := NewAndSelector(l, r)
		if s == nil {
			t.Fatal("two string syntax and returned nil")
		}
	})
	t.Run("two string syntaxes or", func(t *testing.T) {
		l := NewStringSyntaxSelector("<X")
		r := NewStringSyntaxSelector("%plane")
		s := NewOrSelector(l, r)
		if s == nil {
			t.Fatal("two string syntax or returned nil")
		}
	})
	t.Run("string syntax with index combine", func(t *testing.T) {
		l := NewStringSyntaxSelector(">Z[0]")
		r := NewStringSyntaxSelector("%plane")
		s := NewAndSelector(l, r)
		if s == nil {
			t.Fatal("indexed string syntax and returned nil")
		}
	})
}


