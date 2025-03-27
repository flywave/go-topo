
#pragma once

#include <Standard_Version.hxx>
#if OCC_VERSION_HEX >= 0x070400
#include <IMeshTools_Parameters.hxx>
#else
#include <BRepMesh_FastDiscret.hxx>
#endif

namespace flywave {

// Portable alias over parameters for OpenCascade's built-in BRep mesher
#if OCC_VERSION_HEX >= 0x070400
using brep_mesh_parameters = IMeshTools_Parameters;
#else
using brep_mesh_parameters = BRepMesh_FastDiscret::Parameters;
#endif

} // namespace flywave