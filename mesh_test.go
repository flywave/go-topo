package topo

import (
	"testing"
)

func TestNewMeshReceiver(t *testing.T) {
	t.Run("create", func(t *testing.T) {
		m := NewMeshReceiver()
		if m == nil {
			t.Fatal("NewMeshReceiver returned nil")
		}
	})
	t.Run("has tex coord", func(t *testing.T) {
		m := NewMeshReceiver()
		if m.HasTexCoord() {
			t.Fatal("new receiver should not have tex coords")
		}
	})
}

func TestMeshWithBox(t *testing.T) {
	m := NewMeshReceiver()
	wp := NewNamedWorkplane("XY")
	r := wp.BoxCentered(10, 10, 10)
	s := r.Value()
	s.Mesh(m, 0.1, 0.1, 0.5)
	t.Run("has faces", func(t *testing.T) {
		if len(m.Faces) == 0 {
			t.Fatal("expected at least one face")
		}
		if len(m.Vers) == 0 {
			t.Fatal("expected at least one vertex group")
		}
		if len(m.Tris) == 0 {
			t.Fatal("expected at least one triangle group")
		}
	})
	t.Run("has vertices in face 0", func(t *testing.T) {
		if len(m.Vers[0]) == 0 {
			t.Fatal("expected vertices in face 0")
		}
	})
	t.Run("has triangles in face 0", func(t *testing.T) {
		if len(m.Tris[0]) == 0 {
			t.Fatal("expected triangles in face 0")
		}
	})
	t.Run("vertex and normal count match", func(t *testing.T) {
		if len(m.Vers[0]) != len(m.Norms[0]) {
			t.Fatalf("vertex count %d != normal count %d", len(m.Vers[0]), len(m.Norms[0]))
		}
	})
}

func TestMeshWithTexture(t *testing.T) {
	m := NewMeshReceiver()
	wp := NewNamedWorkplane("XY")
	r := wp.BoxCentered(10, 10, 10)
	s := r.Value()
	s.MeshWithTexture(m, 0.1, 0.1, 0.5)
	t.Run("has tex coords", func(t *testing.T) {
		if !m.HasTexCoord() {
			t.Fatal("expected HasTexCoord after MeshWithTexture")
		}
	})
}

func TestMeshMultipleFaces(t *testing.T) {
	m := NewMeshReceiver()
	wp := NewNamedWorkplane("XY")
	r := wp.BoxCentered(10, 10, 10)
	s := r.Value()
	s.Mesh(m, 0.1, 0.1, 0.5)
	t.Run("face data integrity", func(t *testing.T) {
		faceCount := len(m.Faces)
		if faceCount != len(m.Vers) || faceCount != len(m.Tris) {
			t.Logf("faces=%d vers=%d tris=%d", faceCount, len(m.Vers), len(m.Tris))
		}
		for i := 0; i < faceCount && i < len(m.Vers) && i < len(m.Tris); i++ {
			if len(m.Vers[i]) == 0 {
				continue
			}
			if len(m.Vers[i]) != len(m.Norms[i]) {
				t.Fatalf("face %d: %d vertices but %d normals", i, len(m.Vers[i]), len(m.Norms[i]))
			}
		}
	})
}

func TestMeshWithCompound(t *testing.T) {
	m := NewMeshReceiver()
	wp := NewNamedWorkplane("XY")
	r1 := wp.BoxCentered(10, 10, 10)
	r2 := wp.BoxCentered(5, 5, 5)
	shapes := []Shape{*r1.Value(), *r2.Value()}
	c := TopoCompoundMake(shapes)
	c.Mesh(m, 0.1, 0.1, 0.5)
	t.Run("mesh compound", func(t *testing.T) {
		totalTris := 0
		for i := range m.Tris {
			totalTris += len(m.Tris[i])
		}
		if totalTris == 0 {
			t.Fatal("expected triangles from compound mesh")
		}
		t.Logf("compound mesh: %d faces, %d total triangles", len(m.Faces), totalTris)
	})
}
