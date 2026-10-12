package topo

// DGN mesh bridge: pure-Go tessellation of go-dgn scene entities into
// mst.Mesh outlines (no cgo geometry). Mirrors IfcToMst (ifc_mst.go);
// arc/ellipse subdivision follows analysis/05-go-design/topo-bridge.md §6.4:
//
//	n = ceil(sweep / (2*acos(1 - eps/r)))   // r = primary axis
//	clamped to [3, 256] segments
//
// One MeshNode per geometry-bearing element: wire kinds (Segment/Polyline/
// Arc/Ellipse/BSplineCurve) get EdgeGroup outline edges, cones become
// face MeshNodes, and mesh solids (scene.KindSolid) become triangle-face
// MeshNodes (fan-triangulated loops). BIM placement (D93): cell-header (v7 type 2)
// transforms are multiplied DOWN the ancestor chain here (§6.5 consumer
// duty), and shared-cell refs (type 35) instance their definition (type
// 34) geometry — DefnOnly definition-space entities never render raw.
// CellRef placement is identity in sample.dgn (39/39 bbox-verified);
// a non-nil Entity.Transform on the ref will be applied when a placing
// sample pins the field layout.

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

// toMst tessellates every wire-bearing entity into one outline MeshNode
// and cones into a face MeshNode, applying cell placement transforms and
// instancing shared-cell refs.
func (r *DgnReader) toMst(eps float64) []*mst.Mesh {
	mesh := mst.NewMesh()
	mesh.Materials = append(mesh.Materials, &mst.BaseMaterial{
		Color: [3]byte{255, 255, 255},
	})

	byID := make(map[uint64]int, len(r.ents))
	kids := make(map[uint64][]int, len(r.ents))
	for i := range r.ents {
		byID[r.ents[i].ID] = i
		if r.ents[i].ParentID != 0 {
			kids[r.ents[i].ParentID] = append(kids[r.ents[i].ParentID], i)
		}
	}

	// worldTransform: accumulated cell-header placement down the ancestor
	// chain (complex headers and shared defns contribute identity).
	worldCache := make([]*[16]float64, len(r.ents))
	worldDone := make([]bool, len(r.ents))
	var worldOf func(i int) *[16]float64
	worldOf = func(i int) *[16]float64 {
		if worldDone[i] {
			return worldCache[i]
		}
		worldDone[i] = true
		pid := r.ents[i].ParentID
		if pid == 0 {
			return nil
		}
		pi, ok := byID[pid]
		if !ok {
			return nil
		}
		pm := worldOf(pi)
		pt := r.ents[pi].Transform // set only by cell headers (type 2)
		switch {
		case pm != nil && pt != nil:
			worldCache[i] = mat4Mul(pm, pt)
		case pm != nil:
			worldCache[i] = pm
		case pt != nil:
			worldCache[i] = pt
		}
		return worldCache[i]
	}

	// defnGeometry collects the DefnOnly tessellable descendants of a
	// shared-cell definition (nested defs inlined — no refs inside defs
	// in the sample).
	var collect func(idx int, out *[]int)
	collect = func(idx int, out *[]int) {
		for _, c := range kids[r.ents[idx].ID] {
			ce := &r.ents[c]
			if ce.DefnOnly && tessKind(ce.Kind) {
				*out = append(*out, c)
			}
			collect(c, out)
		}
	}
	defnByName := make(map[string]int, len(r.ents))
	for i := range r.ents {
		if r.ents[i].Kind == scene.KindCellDef && !r.ents[i].DefnOnly && r.ents[i].Name != "" {
			if _, dup := defnByName[r.ents[i].Name]; !dup {
				defnByName[r.ents[i].Name] = i
			}
		}
	}

	emit := func(e *scene.Entity, t *[16]float64) {
		if nd := r.nodeFor(e, eps, t); nd != nil {
			mesh.Nodes = append(mesh.Nodes, nd)
		}
	}
	for i := range r.ents {
		e := &r.ents[i]
		if e.DefnOnly {
			continue // definition space renders only through CellRefs
		}
		if e.Kind == scene.KindCellRef {
			di, ok := defnByName[e.Name]
			if !ok && e.DefID != 0 {
				// v8 shared-cell references resolve by definition element
				// id (the 0x2716 dependency root, D112); the name path
				// stays for v7 and name-carrying v8 definitions.
				if pi, inID := byID[e.DefID]; inID && r.ents[pi].Kind == scene.KindCellDef {
					di, ok = pi, true
				}
			}
			if !ok {
				continue
			}
			var geo []int
			collect(di, &geo)
			// instance world = ref's cell chain ∘ ref placement ∘ defn chain
			rw := worldOf(i)
			for _, gi := range geo {
				var t *[16]float64
				dw := worldOf(gi)
				switch {
				case rw != nil && e.Transform != nil && dw != nil:
					t = mat4Mul(rw, mat4Mul(e.Transform, dw))
				case rw != nil && e.Transform != nil:
					t = mat4Mul(rw, e.Transform)
				case rw != nil && dw != nil:
					t = mat4Mul(rw, dw)
				case e.Transform != nil && dw != nil:
					t = mat4Mul(e.Transform, dw)
				case rw != nil:
					t = rw
				case e.Transform != nil:
					t = e.Transform
				case dw != nil:
					t = dw
				}
				emit(&r.ents[gi], t)
			}
			continue
		}
		emit(e, worldOf(i))
	}
	return []*mst.Mesh{mesh}
}

// tessKind reports whether a scene kind produces mesh nodes.
func tessKind(k scene.Kind) bool {
	switch k {
	case scene.KindSegment, scene.KindPolyline, scene.KindArc,
		scene.KindEllipse, scene.KindBSplineCurve, scene.KindCone,
		scene.KindSolid:
		return true
	}
	return false
}

// nodeFor converts one entity into a MeshNode (outline, cone faces or
// mesh triangles), applying the placement transform t (nil = identity).
func (r *DgnReader) nodeFor(e *scene.Entity, eps float64, t *[16]float64) *mst.MeshNode {
	if e.Kind == scene.KindCone {
		nd := r.coneNode(e)
		return transformNode(nd, t)
	}
	if e.Kind == scene.KindSolid {
		nd := r.meshNode(e)
		return transformNode(nd, t)
	}
	pts := r.tessellate(e, eps)
	if len(pts) < 2 {
		return nil
	}
	node := &mst.MeshNode{
		Vertices:  make([]vec3.T, len(pts)),
		EdgeGroup: []*mst.MeshOutline{{Batchid: 0}},
	}
	edges := make([][2]uint32, len(pts)-1)
	for j, p := range pts {
		if t != nil {
			p = mat4Point(t, p)
		}
		node.Vertices[j] = vec3.T{float32(p[0]), float32(p[1]), float32(p[2])}
		if j > 0 {
			edges[j-1] = [2]uint32{uint32(j - 1), uint32(j)}
		}
	}
	node.EdgeGroup[0].Edges = edges
	return node
}

// transformNode applies the placement transform to every node vertex
// (nil = identity; nil nodes pass through).
func transformNode(nd *mst.MeshNode, t *[16]float64) *mst.MeshNode {
	if nd == nil || t == nil {
		return nd
	}
	for i := range nd.Vertices {
		p := mat4Point(t, [3]float64{
			float64(nd.Vertices[i][0]),
			float64(nd.Vertices[i][1]),
			float64(nd.Vertices[i][2]),
		})
		nd.Vertices[i] = vec3.T{float32(p[0]), float32(p[1]), float32(p[2])}
	}
	return nd
}

// meshNode converts a KindSolid mesh into one triangle MeshNode: the
// vertex pool becomes the node vertices and each face loop is fan
// triangulated (p0, pi, pi+1). Entities without decodable faces produce
// no node (clouds still appear through their own element metadata).
func (r *DgnReader) meshNode(e *scene.Entity) *mst.MeshNode {
	if len(e.Faces) == 0 || len(e.Points) == 0 {
		return nil
	}
	verts := make([]vec3.T, len(e.Points))
	for i, p := range e.Points {
		sp := r.scalePoint(p)
		verts[i] = vec3.T{float32(sp[0]), float32(sp[1]), float32(sp[2])}
	}
	inRange := func(i int32) bool { return i >= 0 && int(i) < len(e.Points) }
	var faces []*mst.Face
	for _, f := range e.Faces {
		if len(f) < 3 {
			continue
		}
		valid := true
		for _, idx := range f {
			if !inRange(idx) {
				valid = false
				break
			}
		}
		if !valid { // any out-of-range index drops the whole face
			continue
		}
		for j := 1; j+1 < len(f); j++ {
			faces = append(faces, &mst.Face{Vertex: [3]uint32{uint32(f[0]), uint32(f[j]), uint32(f[j+1])}})
		}
	}
	if len(faces) == 0 {
		return nil
	}
	return &mst.MeshNode{
		Vertices:  verts,
		FaceGroup: []*mst.MeshTriangle{{Batchid: 0, Faces: faces}},
	}
}

// mat4Mul composes two column-major 4×4 transforms: result = a ∘ b.
func mat4Mul(a, b *[16]float64) *[16]float64 {
	var out [16]float64
	for col := 0; col < 4; col++ {
		for row := 0; row < 4; row++ {
			s := 0.0
			for k := 0; k < 4; k++ {
				s += a[k*4+row] * b[col*4+k]
			}
			out[col*4+row] = s
		}
	}
	return &out
}

// mat4Point applies a column-major 4×4 to a point.
func mat4Point(m *[16]float64, p [3]float64) [3]float64 {
	return [3]float64{
		m[0]*p[0] + m[4]*p[1] + m[8]*p[2] + m[12],
		m[1]*p[0] + m[5]*p[1] + m[9]*p[2] + m[13],
		m[2]*p[0] + m[6]*p[1] + m[10]*p[2] + m[14],
	}
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
	case scene.KindBSplineCurve:
		return r.tessBSpline(e)
	}
	return nil // text / cell / point-string / metadata; cone handled by coneNode
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

// tessBSpline samples an assembled B-spline curve (scene.KindBSplineCurve)
// with de Boor's algorithm at n+1 uniform parameters across the domain
// [knots[degree], knots[len−1−degree]]; n = clamp(2·poles, 16, 128).
// Pure Go — the mesh path stays cgo-free.
func (r *DgnReader) tessBSpline(e *scene.Entity) [][3]float64 {
	if len(e.Points) < 2 || len(e.Knots) == 0 || e.Degree < 1 {
		return nil
	}
	poles := make([][3]float64, len(e.Points))
	for i, p := range e.Points {
		poles[i] = r.scalePoint(p)
	}
	n := 2 * len(poles)
	if n < 16 {
		n = 16
	}
	if n > 128 {
		n = 128
	}
	t0 := e.Knots[e.Degree]
	t1 := e.Knots[len(e.Knots)-1-e.Degree]
	pts := make([][3]float64, n+1)
	for i := 0; i <= n; i++ {
		t := t0 + (t1-t0)*float64(i)/float64(n)
		pts[i] = deBoor(poles, e.Knots, e.Weights, e.Degree, t)
	}
	return pts
}

// deBoor evaluates a (possibly rational) clamped B-spline at parameter t.
// Weights nil means non-rational (homogeneous weight 1). The algorithm
// works in homogeneous space and divides by w at the end.
func deBoor(poles [][3]float64, knots []float64, weights []float64, degree int, t float64) [3]float64 {
	p := degree
	t0, t1 := knots[p], knots[len(knots)-1-p]
	if t < t0 {
		t = t0
	}
	if t > t1 {
		t = t1
	}
	// span k: knots[k] <= t < knots[k+1], k in [p, n]
	n := len(poles) - 1
	k := n
	for i := p; i < n; i++ {
		if t < knots[i+1] {
			k = i
			break
		}
	}
	type hp struct{ x, y, z, w float64 }
	d := make([]hp, p+1)
	for j := 0; j <= p; j++ {
		idx := k - p + j
		wt := 1.0
		if idx < len(weights) {
			wt = weights[idx]
		}
		d[j] = hp{poles[idx][0] * wt, poles[idx][1] * wt, poles[idx][2] * wt, wt}
	}
	for lev := 1; lev <= p; lev++ {
		for j := p; j >= lev; j-- {
			i := k - p + j
			denom := knots[i+p-lev+1] - knots[i]
			alpha := 0.0
			if denom != 0 {
				alpha = (t - knots[i]) / denom
			}
			d[j].x = (1-alpha)*d[j-1].x + alpha*d[j].x
			d[j].y = (1-alpha)*d[j-1].y + alpha*d[j].y
			d[j].z = (1-alpha)*d[j-1].z + alpha*d[j].z
			d[j].w = (1-alpha)*d[j-1].w + alpha*d[j].w
		}
	}
	if d[p].w == 0 {
		return poles[k]
	}
	return [3]float64{d[p].x / d[p].w, d[p].y / d[p].w, d[p].z / d[p].w}
}

// coneSegmentCount is the ring resolution of a triangulated cone/frustum.
const coneSegmentCount = 32

// coneNode triangulates a KindCone frustum into a face MeshNode: two
// rings of coneSegmentCount+1 vertices (closed seam) plus cap fans from
// the center points. A zero radius collapses that end to its apex.
func (r *DgnReader) coneNode(e *scene.Entity) *mst.MeshNode {
	if len(e.Points) < 2 {
		return nil
	}
	c1 := r.scalePoint(e.Points[0])
	c2 := r.scalePoint(e.Points[1])
	r1, r2 := e.Radii[0], e.Radii[1]
	if r.units > 0 {
		r1 /= r.units
		r2 /= r.units
	}
	if r1 < 0 {
		r1 = -r1
	}
	if r2 < 0 {
		r2 = -r2
	}
	if r1 == 0 && r2 == 0 {
		return nil
	}
	// orthonormal frame around the axis
	axis := [3]float64{c2[0] - c1[0], c2[1] - c1[1], c2[2] - c1[2]}
	al := math.Sqrt(axis[0]*axis[0] + axis[1]*axis[1] + axis[2]*axis[2])
	if al == 0 {
		axis = [3]float64{0, 0, 1}
		al = 1
	}
	axis = [3]float64{axis[0] / al, axis[1] / al, axis[2] / al}
	helper := [3]float64{1, 0, 0}
	if math.Abs(axis[0]) > 0.9 {
		helper = [3]float64{0, 1, 0}
	}
	u := [3]float64{
		axis[1]*helper[2] - axis[2]*helper[1],
		axis[2]*helper[0] - axis[0]*helper[2],
		axis[0]*helper[1] - axis[1]*helper[0],
	}
	ul := math.Sqrt(u[0]*u[0] + u[1]*u[1] + u[2]*u[2])
	u = [3]float64{u[0] / ul, u[1] / ul, u[2] / ul}
	v := [3]float64{
		axis[1]*u[2] - axis[2]*u[1],
		axis[2]*u[0] - axis[0]*u[2],
		axis[0]*u[1] - axis[1]*u[0],
	}

	n := coneSegmentCount
	verts := make([]vec3.T, 0, 2*(n+1)+2)
	ring := func(c [3]float64, rad float64) {
		for i := 0; i <= n; i++ {
			a := 2 * math.Pi * float64(i) / float64(n)
			cs, sn := math.Cos(a), math.Sin(a)
			p := [3]float64{
				c[0] + rad*(cs*u[0]+sn*v[0]),
				c[1] + rad*(cs*u[1]+sn*v[1]),
				c[2] + rad*(cs*u[2]+sn*v[2]),
			}
			verts = append(verts, vec3.T{float32(p[0]), float32(p[1]), float32(p[2])})
		}
	}
	ring(c1, r1)
	ring(c2, r2)
	c1Idx := uint32(len(verts))
	verts = append(verts, vec3.T{float32(c1[0]), float32(c1[1]), float32(c1[2])})
	c2Idx := uint32(len(verts))
	verts = append(verts, vec3.T{float32(c2[0]), float32(c2[1]), float32(c2[2])})

	r1Base, r2Base := uint32(0), uint32(n+1)
	face := func(a, b, c uint32) *mst.Face {
		return &mst.Face{Vertex: [3]uint32{a, b, c}}
	}
	var faces []*mst.Face
	for i := 0; i < n; i++ {
		a, b := r1Base+uint32(i), r1Base+uint32(i+1)
		c, d := r2Base+uint32(i), r2Base+uint32(i+1)
		switch {
		case r1 > 0 && r2 > 0:
			faces = append(faces, face(a, c, d), face(a, d, b))
		case r1 == 0: // apex at c1
			faces = append(faces, face(c1Idx, c, d))
		default: // apex at c2
			faces = append(faces, face(a, c2Idx, b))
		}
	}
	if r1 > 0 {
		for i := 0; i < n; i++ {
			faces = append(faces, face(c1Idx, r1Base+uint32(i+1), r1Base+uint32(i)))
		}
	}
	if r2 > 0 {
		for i := 0; i < n; i++ {
			faces = append(faces, face(c2Idx, r2Base+uint32(i), r2Base+uint32(i+1)))
		}
	}
	return &mst.MeshNode{
		Vertices:  verts,
		FaceGroup: []*mst.MeshTriangle{{Batchid: 0, Faces: faces}},
	}
}
