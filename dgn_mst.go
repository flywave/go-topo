package topo

// DGN mesh bridge: pure-Go tessellation of go-dgn scene entities into
// mst.Mesh outlines (no cgo geometry). Mirrors IfcToMst (ifc_mst.go);
// arc/ellipse subdivision follows analysis/05-go-design/topo-bridge.md §6.4:
//
//	n = ceil(sweep / (2*acos(1 - eps/r)))   // r = primary axis
//	clamped to [3, 256] segments
//
// One MeshNode per wire-bearing element (Segment/Polyline/Arc/Ellipse),
// EdgeGroup edges = consecutive vertex index pairs. Cell/complex-group
// transforms are NOT pre-multiplied here (§6.5: consumers descend them).

import (
	"math"

	mst "github.com/flywave/go-mst"
	"github.com/flywave/go3d/vec3"

	"github.com/flywave/go-dgn/dgn/scene"
)

// DefaultArcEpsilon is the default chordal error (sagitta) in document
// units — master units for v7, raw UOR for v8 unless SetUnits was called.
const DefaultArcEpsilon = 0.1

// DgnToMst converts the DGN file at path into mst.Mesh outlines using
// DefaultArcEpsilon for arc/ellipse subdivision.
func DgnToMst(path string) ([]*mst.Mesh, error) {
	return DgnToMstEps(path, DefaultArcEpsilon)
}

// DgnToMstEps is DgnToMst with an explicit chordal error eps > 0
// (document units).
func DgnToMstEps(path string, eps float64) ([]*mst.Mesh, error) {
	r := NewDgnReader()
	if err := r.Load(path); err != nil {
		return nil, err
	}
	return r.toMst(eps), nil
}

// toMst tessellates every wire-bearing entity into one outline MeshNode.
func (r *DgnReader) toMst(eps float64) []*mst.Mesh {
	mesh := mst.NewMesh()
	mesh.Materials = append(mesh.Materials, &mst.BaseMaterial{
		Color: [3]byte{255, 255, 255},
	})
	for i := range r.ents {
		pts := r.tessellate(&r.ents[i], eps)
		if len(pts) < 2 {
			continue
		}
		node := &mst.MeshNode{
			Vertices:  make([]vec3.T, len(pts)),
			EdgeGroup: []*mst.MeshOutline{{Batchid: 0}},
		}
		edges := make([][2]uint32, len(pts)-1)
		for j, p := range pts {
			node.Vertices[j] = vec3.T{float32(p[0]), float32(p[1]), float32(p[2])}
			if j > 0 {
				edges[j-1] = [2]uint32{uint32(j - 1), uint32(j)}
			}
		}
		node.EdgeGroup[0].Edges = edges
		mesh.Nodes = append(mesh.Nodes, node)
	}
	return []*mst.Mesh{mesh}
}

// tessellate returns the outline point sequence of one entity in output
// units (master for v7; UOR scaled by SetUnits for v8), or nil when the
// kind carries no outline (text/cell/point-string/metadata).
func (r *DgnReader) tessellate(e *scene.Entity, eps float64) [][3]float64 {
	switch e.Kind {
	case scene.KindSegment:
		if len(e.Points) < 2 {
			return nil
		}
		return [][3]float64{r.scalePoint(e.Points[0]), r.scalePoint(e.Points[1])}
	case scene.KindPolyline:
		if len(e.Points) < 2 {
			return nil
		}
		pts := make([][3]float64, len(e.Points))
		for i, p := range e.Points {
			pts[i] = r.scalePoint(p)
		}
		return pts
	case scene.KindArc:
		return r.tessArc(e, false, eps)
	case scene.KindEllipse:
		return r.tessArc(e, true, eps)
	}
	return nil
}

// tessArc samples an arc (circle or ellipse) at chordal error eps.
// The effective radius is the primary axis for circles and the minimum
// radius of curvature (min²/max) for ellipses, so the bound holds across
// the whole curve. Points include both endpoints; a full sweep makes the
// last point equal the first (closed outline).
func (r *DgnReader) tessArc(e *scene.Entity, ellipse bool, eps float64) [][3]float64 {
	if e.Arc == nil {
		return nil
	}
	a := e.Arc
	c := r.scalePoint(a.Center)
	rx := a.PrimaryAxis
	ry := a.PrimaryAxis
	if ellipse {
		ry = a.SecondaryAxis
	}
	if r.units > 0 {
		rx /= r.units
		ry /= r.units
	}
	if rx < 0 {
		rx = -rx
	}
	if ry < 0 {
		ry = -ry
	}

	// effective radius: circle → r; ellipse → min²/max (min curvature)
	rEff := rx
	if ellipse {
		lo, hi := rx, ry
		if lo > hi {
			lo, hi = hi, lo
		}
		if hi > 0 {
			rEff = lo * lo / hi
		} else {
			rEff = 0
		}
	}

	n := arcSegments(a.Sweep, rEff, eps)

	sweepRad := a.Sweep * math.Pi / 180
	pts := make([][3]float64, n+1)
	for i := 0; i <= n; i++ {
		theta := a.Start*math.Pi/180 + sweepRad*float64(i)/float64(n)
		pts[i] = arcOutlinePoint(a, c, rx, ry, theta)
	}
	return pts
}

// arcSegments implements the §6.4 subdivision count for a sweep in
// degrees, clamped to [3, 256].
func arcSegments(sweepDeg, rEff, eps float64) int {
	n := 3
	if rEff > 0 && eps > 0 {
		arg := 1 - eps/rEff
		if arg < -1 {
			arg = -1
		}
		if arg > 1-1e-12 {
			arg = 1 - 1e-12
		}
		step := 2 * math.Acos(arg)
		if step > 0 {
			n = int(math.Ceil(math.Abs(sweepDeg) * math.Pi / 180 / step))
		}
	}
	if n < 3 {
		n = 3
	}
	if n > 256 {
		n = 256
	}
	return n
}

// arcOutlinePoint maps an angle on the arc plane to a world point: scale
// by the radii, rotate by the 2D rotation or quaternion, translate by the
// center. rx == ry for circles.
func arcOutlinePoint(a *scene.Arc, c [3]float64, rx, ry, theta float64) [3]float64 {
	v := [3]float64{rx * math.Cos(theta), ry * math.Sin(theta), 0}
	if a.Quat != [4]float64{} {
		v = quatRotate(a.Quat, v)
	} else if a.Rotation != 0 {
		rot := a.Rotation * math.Pi / 180
		cs, sn := math.Cos(rot), math.Sin(rot)
		v = [3]float64{cs*v[0] - sn*v[1], sn*v[0] + cs*v[1], v[2]}
	}
	return [3]float64{c[0] + v[0], c[1] + v[1], c[2] + v[2]}
}
