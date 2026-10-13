// nwd2mesh exports the geometry of a Navisworks .nwd file to STL or STEP
// through go-topo (OpenCASCADE).
//
// Usage:
//
//	nwd2mesh <file.nwd> <out.stl|out.step> [soup]
//
// "soup" enables best-effort triangle-soup faces (go-nwd U21 pending).
//
// Fidelity: line-set elements become exact edge compounds; triangle
// elements contribute vertices and (with soup) non-indexed triangles.
// Elements without a bridged Shape are skipped. STEP preserves edges and
// faces; STL stores triangulated faces only (so a line-only export yields
// an empty STL).
package main

import (
	"encoding/binary"
	"fmt"
	"math"
	"os"
	"path/filepath"
	"strings"

	topo "github.com/flywave/go-topo"
)

func main() {
	if len(os.Args) < 3 {
		fmt.Fprintln(os.Stderr, "usage: nwd2mesh <file.nwd> <out.stl|out.step> [soup]")
		os.Exit(2)
	}
	in, out := os.Args[1], os.Args[2]
	r := topo.NewNwdReader()
	for _, a := range os.Args[3:] {
		if a == "soup" {
			r.SetTriangleSoup(true)
		}
	}
	if err := r.Load(in); err != nil {
		fmt.Fprintln(os.Stderr, "error:", err)
		os.Exit(1)
	}

	var shapes []topo.Shape
	total := 0
	for _, e := range r.GetElements() {
		total++
		if e.Shape != nil {
			shapes = append(shapes, *e.Shape)
		}
	}
	if len(shapes) == 0 {
		fmt.Fprintln(os.Stderr, "no bridged shapes (line sets / triangle soup)")
		os.Exit(1)
	}
	comp := topo.TopoCompoundMake(shapes)
	sh := comp.ToShape()

	switch strings.ToLower(filepath.Ext(out)) {
	case ".stl":
		n, err := writeSTL(out, sh)
		if err != nil {
			fmt.Fprintln(os.Stderr, "STL export:", err)
			os.Exit(1)
		}
		fmt.Fprintf(os.Stderr, "wrote %s: %d triangles from %d/%d elements\n", out, n, len(shapes), total)
	case ".step", ".stp":
		if !sh.ExportStepUnit(out, true, 0, "MM") {
			fmt.Fprintln(os.Stderr, "STEP export failed")
			os.Exit(1)
		}
		fmt.Fprintf(os.Stderr, "wrote %s from %d/%d elements\n", out, len(shapes), total)
	default:
		fmt.Fprintln(os.Stderr, "unsupported output extension (use .stl or .step)")
		os.Exit(2)
	}
}

// writeSTL triangulates the shape via topo's mesh receiver and writes a
// binary STL.
func writeSTL(path string, sh *topo.Shape) (int, error) {
	m := topo.NewMeshReceiver()
	sh.Mesh(m, 0.5, 0.5, 0.5)

	f, err := os.Create(path)
	if err != nil {
		return 0, err
	}
	defer f.Close()

	// Count triangles across faces.
	count := 0
	for fi := range m.Tris {
		count += len(m.Tris[fi])
	}
	var hdr [80]byte
	copy(hdr[:], "go-nwd nwd2mesh binary STL")
	if _, err := f.Write(hdr[:]); err != nil {
		return 0, err
	}
	var cnt [4]byte
	binary.LittleEndian.PutUint32(cnt[:], uint32(count))
	if _, err := f.Write(cnt[:]); err != nil {
		return 0, err
	}
	written := 0
	for fi := range m.Tris {
		vers := m.Vers[fi]
		for _, t := range m.Tris[fi] {
			if t[0] < 0 || t[0] >= len(vers) || t[1] < 0 || t[1] >= len(vers) || t[2] < 0 || t[2] >= len(vers) {
				continue
			}
			p0, p1, p2 := vers[t[0]], vers[t[1]], vers[t[2]]
			n := normal(p0, p1, p2)
			var rec [50]byte
			putVec(rec[0:12], n)
			putVec(rec[12:24], f32vec(p0))
			putVec(rec[24:36], f32vec(p1))
			putVec(rec[36:48], f32vec(p2))
			if _, err := f.Write(rec[:]); err != nil {
				return written, err
			}
			written++
		}
	}
	return written, nil
}

func normal(p0, p1, p2 topo.Point3) [3]float32 {
	a := p0.Data()
	b := p1.Data()
	c := p2.Data()
	u := [3]float64{b[0] - a[0], b[1] - a[1], b[2] - a[2]}
	v := [3]float64{c[0] - a[0], c[1] - a[1], c[2] - a[2]}
	n := [3]float64{u[1]*v[2] - u[2]*v[1], u[2]*v[0] - u[0]*v[2], u[0]*v[1] - u[1]*v[0]}
	l := math.Sqrt(n[0]*n[0] + n[1]*n[1] + n[2]*n[2])
	if l == 0 {
		return [3]float32{0, 0, 0}
	}
	return [3]float32{float32(n[0] / l), float32(n[1] / l), float32(n[2] / l)}
}

func f32vec(p topo.Point3) [3]float32 {
	d := p.Data()
	return [3]float32{float32(d[0]), float32(d[1]), float32(d[2])}
}

func putVec(dst []byte, v [3]float32) {
	binary.LittleEndian.PutUint32(dst[0:4], math.Float32bits(v[0]))
	binary.LittleEndian.PutUint32(dst[4:8], math.Float32bits(v[1]))
	binary.LittleEndian.PutUint32(dst[8:12], math.Float32bits(v[2]))
}
