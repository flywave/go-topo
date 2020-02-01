CMAKE_MINIMUM_REQUIRED(VERSION 3.1.3)

PROJECT(go-topo C CXX)

# Set build type
IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Release CACHE STRING
      "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
      FORCE)
ENDIF(NOT CMAKE_BUILD_TYPE)

OPTION(FLYWAVE_ENABLE_SOLUTION_FOLDERS "Build with UBSAN" ON)

if(FLYWAVE_ENABLE_SOLUTION_FOLDERS)
  SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)
  SET_PROPERTY(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMakeTargets")
endif()

# Set output directories
SET(FLYWAVE_LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)

MAKE_DIRECTORY(${FLYWAVE_LIBRARY_OUTPUT_PATH})

SET(FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}")
SET(FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}")

# freetype2
IF(NOT FREETYPE_INCLUDE)

  ADD_SUBDIRECTORY("${CMAKE_CURRENT_SOURCE_DIR}/external/freetype2")

  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/freetype2/include/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/freetype2/src/include/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/freetype2/")
  LIST(APPEND FLYWAVE_LIBRARY_DEPES "freetype")
  SET(FREETYPE_INCLUDE YES)
ENDIF()

# oce
IF(NOT OCE_INCLUDE)
  ADD_SUBDIRECTORY("${CMAKE_CURRENT_SOURCE_DIR}/external/oce/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/oce/build_inc/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/inc/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/Standard/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/gp/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/Precision/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/TCollection/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/TopoDS/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/TopLoc/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/GeomAdaptor/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/Geom2dAdaptor/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/BRepAdaptor/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/ShapeFix/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/ShapeAnalysis/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/ShapeBuild/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/ShapeExtend/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/ShapeConstruct/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/ShapeUpgrade/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/ShapeAlgo/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/ShapeProcess/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/ShapeProcessAPI/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/BRepGProp/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/BRepMesh/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/Bnd/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/Adaptor2d/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/Adaptor3d/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/BOPAlgo/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/BOPDS/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/BRep/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/BRepApprox/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/BRepBlend/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/BRepBuilderAPI/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/BRepCheck/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/NCollection/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/TopTools/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/GCPnts/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/Poly/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/BRepFilletAPI/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/TopExp/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/BOPCol/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/BRepSweep/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/Sweep/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/ChFi2d/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/BRepTools/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/IntPatch/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/GeomInt/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/IntSurf/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/GeomAPI/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/Extrema/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/math/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/CPnts/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/BRepPrim/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/GC/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/ChFiDS/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/ElCLib/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/gce/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/Interface/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/MoniTool/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/TDF/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/Message/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/Plate/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/GCE2d/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/BRepFeat/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/GeomConvert/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/LocOpe/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/TDocStd/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/CDF")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/TNaming")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/IGESControl")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/XCAFPrs")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/XCAFDoc")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/XCAFDrivers")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/XCAFSchema")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/XmlXCAFDrivers") 
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/oce/src/STEPCAFControl") 

  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/oce/adm/cmake/FWOSPlugin/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/oce/adm/cmake/PTKernel/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/oce/adm/cmake/TKBin/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/oce/adm/cmake/TKBinL/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/oce/adm/cmake/TKBinTObj/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/oce/adm/cmake/TKBinXCAF/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/oce/adm/cmake/TKBO/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/oce/adm/cmake/TKBool/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/oce/adm/cmake/TKBRep/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/oce/adm/cmake/TKCAF/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/oce/adm/cmake/TKCDF/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/oce/adm/cmake/TKernel/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/oce/adm/cmake/TKFeat/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/oce/adm/cmake/TKFillet/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/oce/adm/cmake/TKG2d/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/oce/adm/cmake/TKG3d/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/oce/adm/cmake/TKGeomAlgo/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/oce/adm/cmake/TKGeomBase/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/oce/adm/cmake/TKHLR/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/oce/adm/cmake/TKIGES/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/oce/adm/cmake/TKLCAF/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/oce/adm/cmake/TKMath/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/oce/adm/cmake/TKMesh/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/oce/adm/cmake/TKOffset/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/oce/adm/cmake/TKPCAF/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/oce/adm/cmake/TKPLCAF/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/oce/adm/cmake/TKPrim/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/oce/adm/cmake/TKPShape/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/oce/adm/cmake/TKService/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/oce/adm/cmake/TKShapeSchema/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/oce/adm/cmake/TKShHealing/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/oce/adm/cmake/TKStdLSchema/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/oce/adm/cmake/TKStdSchema/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/oce/adm/cmake/TKSTEP/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/oce/adm/cmake/TKSTEP209/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/oce/adm/cmake/TKSTEPAttr/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/oce/adm/cmake/TKSTEPBase/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/oce/adm/cmake/TKSTL/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/oce/adm/cmake/TKTObj/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/oce/adm/cmake/TKTopAlgo/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/oce/adm/cmake/TKV3d/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/oce/adm/cmake/TKVRML/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/oce/adm/cmake/TKXCAF/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/oce/adm/cmake/TKXCAFSchema/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/oce/adm/cmake/TKXDEIGES/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/oce/adm/cmake/TKXDESTEP/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/oce/adm/cmake/TKXMesh/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/oce/adm/cmake/TKXml/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/oce/adm/cmake/TKXmlL/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/oce/adm/cmake/TKXmlTObj/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/oce/adm/cmake/TKXmlXCAF/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/oce/adm/cmake/TKXSBase/")
  
  IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    LIST(APPEND FLYWAVE_LIBRARY_DEPES "X11" "GL")
  ENDIF()
 
  LIST(APPEND FLYWAVE_LIBRARY_DEPES "TKernel"
                                    "TKMath"
                                    "TKBRep"
                                    "TKFeat"
                                    "TKGeomBase"
                                    "TKGeomAlgo"
                                    "TKG3d"
                                    "TKG2d"
                                    "TKShHealing"
                                    "TKTopAlgo"
                                    "TKMesh"
                                    "TKPrim"
                                    "TKBool"
                                    "TKBO"
                                    "TKFillet"
                                    "TKSTEP"
                                    "TKSTEPBase"
                                    "TKSTEPAttr"
                                    "TKXSBase"
                                    "TKSTEP209"
                                    "TKIGES"
                                    "TKOffset"
                                    "TKIGES"
                                    "TKSTEP209"
                                    "TKSTEP"
                                    "TKCDF"
                                    "TKCAF"
                                    "TKSTL"
                                    "TKXCAF"
                                    "TKSTEP"
                                    "TKXmlXCAF"
                                    "TKBinXCAF"
                                    "TKPCAF"
                                    "TKLCAF"
                                    "TKPLCAF"
                                    "TKXDESTEP")
SET(OCE_INCLUDE YES)
ENDIF()

foreach(LIBDIR ${FLYWAVE_LIBRARY_DIRS})
  INSTALL(
        DIRECTORY ${LIBDIR}
        DESTINATION ${FLYWAVE_LIBRARY_OUTPUT_PATH}
        USE_SOURCE_PERMISSIONS FILE_PERMISSIONS
        FILES_MATCHING PATTERN "*.a"
        )
  endforeach()