package topo

/*
#include "topo_c_api.h"
*/
import "C"

// SewFacesToSolid sews independent faces into a connected shell and wraps the
// result into a solid (BRepBuilderAPI_Sewing + MakeSolid + ShapeFix). The
// faces may be built independently (even with duplicated boundary edges);
// sewing merges coincident edges within tol. Returns nil when no face could
// be sewn; returns the raw sewn shape (possibly an open shell or compound)
// when no closed shell emerged.
func SewFacesToSolid(faces []*Face, tol float64) *Shape {
	if len(faces) == 0 {
		return nil
	}
	vals := make([]C.struct__topo_face_t, 0, len(faces))
	for _, f := range faces {
		if f == nil || f.inner == nil {
			continue
		}
		vals = append(vals, f.inner.val)
	}
	if len(vals) == 0 {
		return nil
	}
	shp := C.topo_sew_faces_to_solid(&vals[0], C.int(len(vals)), C.double(tol))
	if shp == nil {
		return nil
	}
	return NewShape(shp)
}
