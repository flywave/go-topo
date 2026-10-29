package topo

/*
#include "topo_c_api.h"
*/
import "C"

// FixFaceWithTol repairs a face at the given tolerance (ShapeFix_Shape with
// explicit precision): fills missing pcurves on edges of analytic faces that
// BRepBuilderAPI_MakeFace leaves behind. Returns nil on failure; the
// returned face replaces the input.
func FixFaceWithTol(f *Face, tol float64) *Face {
	if f == nil || f.inner == nil {
		return nil
	}
	fixed := C.topo_face_fix_with_tol(&f.inner.val, C.double(tol))
	if fixed == nil {
		return nil
	}
	return &Face{inner: &innerFace{val: *fixed}}
}
