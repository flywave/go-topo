package topovis

/*
#include <stdlib.h>
#include "topovis_c_api.h"
#cgo CFLAGS: -I ./
#cgo linux CXXFLAGS: -I ./include/oce -I ./include/linux/oce -I ./
#cgo darwin CXXFLAGS: -I ./include/oce -I ./include/darwin/oce -I ./
#cgo windows CXXFLAGS:  -I ./include/oce -I ./include/windows/oce -I ./
#cgo linux LDFLAGS: -L ./lib/linux_amd64 -L /usr/lib/x86_64-linux-gnu/ -Wl,--start-group -lpthread -ldl -lm -lGL -lGLU -lX11 -lfreetype -lTKernel -lTKMath -lTKG2d -lTKG3d -lTKGeomBase -lTKBRep -lTKGeomAlgo -lTKTopAlgo -lTKPrim -lTKBO -lTKHLR -lTKMesh -lTKShHealing -lTKXMesh -lTKBool -lTKFillet -lTKFeat -lTKOffset -lTKService -lTKV3d -lTKCDF -lPTKernel -lTKLCAF -lFWOSPlugin -lTKPShape -lTKBinL -lTKXmlL -lTKPLCAF -lTKTObj -lTKShapeSchema -lTKStdLSchema -lTKCAF -lTKBin -lTKXml -lTKPCAF -lTKBinTObj -lTKXmlTObj -lTKStdSchema -lTKSTL -lTKXSBase -lTKSTEPBase -lTKIGES -lTKSTEPAttr -lTKSTEP209 -lTKSTEP -lTKVRML -lTKXCAF -lTKXCAFSchema -lTKXmlXCAF -lTKBinXCAF -lTKXDEIGES -lTKXDESTEP -Wl,--end-group
#cgo darwin LDFLAGS: -L ./lib/darwin_amd64 -lfreetype -lTKernel -lTKMath -lTKG2d -lTKG3d -lTKGeomBase -lTKBRep -lTKGeomAlgo -lTKTopAlgo -lTKPrim -lTKBO -lTKHLR -lTKMesh -lTKShHealing -lTKXMesh -lTKBool -lTKFillet -lTKFeat -lTKOffset -lTKService -lTKV3d -lTKCDF -lPTKernel -lTKLCAF -lFWOSPlugin -lTKPShape -lTKBinL -lTKXmlL -lTKPLCAF -lTKTObj -lTKShapeSchema -lTKStdLSchema -lTKCAF -lTKBin -lTKXml -lTKPCAF -lTKBinTObj -lTKXmlTObj -lTKStdSchema -lTKSTL -lTKXSBase -lTKSTEPBase -lTKIGES -lTKSTEPAttr -lTKSTEP209 -lTKSTEP -lTKVRML -lTKXCAF -lTKXCAFSchema -lTKXmlXCAF -lTKBinXCAF -lTKXDEIGES -lTKXDESTEP
#cgo windows LDFLAGS: -L ./lib/windows_amd64 -lfreetype -lTKernel -lTKMath -lTKG2d -lTKG3d -lTKGeomBase -lTKBRep -lTKGeomAlgo -lTKTopAlgo -lTKPrim -lTKBO -lTKHLR -lTKMesh -lTKShHealing -lTKXMesh -lTKBool -lTKFillet -lTKFeat -lTKOffset -lTKService -lTKV3d -lTKCDF -lPTKernel -lTKLCAF -lFWOSPlugin -lTKPShape -lTKBinL -lTKXmlL -lTKPLCAF -lTKTObj -lTKShapeSchema -lTKStdLSchema -lTKCAF -lTKBin -lTKXml -lTKPCAF -lTKBinTObj -lTKXmlTObj -lTKStdSchema -lTKSTL -lTKXSBase -lTKSTEPBase -lTKIGES -lTKSTEPAttr -lTKSTEP209 -lTKSTEP -lTKVRML -lTKXCAF -lTKXCAFSchema -lTKXmlXCAF -lTKBinXCAF -lTKXDEIGES -lTKXDESTEP
*/
import "C"
