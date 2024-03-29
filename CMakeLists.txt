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

# SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g")

Set(FLYWAVE_BASE_INSTALL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs")
IF(APPLE)
  if (${CMAKE_SYSTEM_PROCESSOR} MATCHES "^arm")
    SET(FLYWAVE_LIBRARY_OUTPUT_PATH "${FLYWAVE_BASE_INSTALL_DIR}/darwin_arm")
  else()
    SET(FLYWAVE_LIBRARY_OUTPUT_PATH "${FLYWAVE_BASE_INSTALL_DIR}/darwin")
  endif()
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14")
ELSEIF(WIN32)
SET(FLYWAVE_LIBRARY_OUTPUT_PATH "${FLYWAVE_BASE_INSTALL_DIR}/windows")
ELSE()
    SET(FLYWAVE_LIBRARY_OUTPUT_PATH "${FLYWAVE_BASE_INSTALL_DIR}/linux")
ENDIF()
MAKE_DIRECTORY(${FLYWAVE_LIBRARY_OUTPUT_PATH})

SET(FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}")
SET(FLYWAVE_LIBRARY_DIRS "")

# freetype2
IF(NOT FREETYPE_INCLUDE)

  ADD_SUBDIRECTORY("${CMAKE_CURRENT_SOURCE_DIR}/external/freetype2")

  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/freetype2/include/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/freetype2/src/include/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/freetype2/")
  LIST(APPEND FLYWAVE_LIBRARY_DEPES "freetype")
  SET(FREETYPE_INCLUDE YES)
ENDIF()

# boost
IF(UNIX OR MINGW)
IF(NOT BOOST_INCLUDE)
  ADD_SUBDIRECTORY("${CMAKE_CURRENT_SOURCE_DIR}/external/libboost")

  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/libboost/boost_1_67_0")
  LIST(APPEND FLYWAVE_LIBRARY_DEPES "boost_regex_internal" "boost_program_options_internal" "boost_date_time_internal" "boost_filesystem_internal" "boost_system_internal")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/libboost/")
  SET(BOOST_INCLUDE YES)
ENDIF()
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

  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/oce/")
  
  IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    LIST(APPEND FLYWAVE_LIBRARY_DEPES "X11" "GL")
  ENDIF()
 
  LIST(APPEND FLYWAVE_LIBRARY_DEPES "TKernel"
                                    "TKMath"
                                    "TKG2d"
                                    "TKG3d"
                                    "TKGeomBase"
                                    "TKGeomAlgo"
                                    "TKTopAlgo"
                                    "TKPrim"
                                    "TKBO"
                                    "TKHLR"
                                    "TKMesh"
                                    "TKShHealing"
                                    "TKXMesh"
                                    "TKBool"
                                    "TKFillet"
                                    "TKFeat"
                                    "TKOffset"
                                    "TKCDF"
                                    "PTKernel"
                                    "TKLCAF"
                                    "FWOSPlugin"
                                    "TKPShape"
                                    "TKBinL"
                                    "TKXmlL"
                                    "TKPLCAF"
                                    "TKTObj"
                                    "TKShapeSchema"
                                    "TKStdLSchema"
                                    "TKCAF"
                                    "TKBin"
                                    "TKXml"
                                    "TKPCAF"
                                    "TKBinTObj"
                                    "TKXmlTObj"
                                    "TKStdSchema"
                                    "TKSTL"
                                    "TKXSBase"
                                    "TKSTEPBase"
                                    "TKIGES"
                                    "TKSTEPAttr"
                                    "TKSTEP209"
                                    "TKSTEP"
                                    "TKVRML"
                                    "TKXCAF"
                                    "TKXCAFSchema"
                                    "TKXmlXCAF"
                                    "TKBinXCAF"
                                    "TKXDEIGES"
                                    "TKXDESTEP"
                                    "TKBRep"
                                    "TKV3d")
SET(OCE_INCLUDE YES)
ENDIF()

IF(WIN32 OR MINGW)
add_definitions(-DHAVE_NO_DLL)
ENDIF()

# zlib
IF(NOT ZLIB_INCLUDE)

  ADD_SUBDIRECTORY("${CMAKE_CURRENT_SOURCE_DIR}/external/zlib")

  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/zlib/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/zlib/win32/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/zlib/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/zlib/win32/")

  LIST(APPEND FLYWAVE_LIBRARY_DEPES "zlib")
  SET(ZLIB_INCLUDE YES)
ENDIF()

IF(NOT IFC_INCLUDE)
  ADD_SUBDIRECTORY("${CMAKE_CURRENT_SOURCE_DIR}/external/ifc/cmake")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/ifc/src/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/ifc/src/ifcgeom/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/ifc/src/ifcparse/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/ifc/src/ifcgeom_schema_agnostic/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/ifc/")
  LIST(APPEND FLYWAVE_LIBRARY_DEPES "ifc23"
                                    "ifc4" 
                                    "ifc41" 
                                    "ifc42" 
                                    "ifc43_rc1")
  SET(IFC_INCLUDE YES)
ENDIF()

LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/src/")

ADD_SUBDIRECTORY("${CMAKE_CURRENT_SOURCE_DIR}/src")

foreach(LIBDIR ${FLYWAVE_LIBRARY_DIRS})
  INSTALL(
        DIRECTORY ${LIBDIR}
        DESTINATION ${FLYWAVE_LIBRARY_OUTPUT_PATH}
        USE_SOURCE_PERMISSIONS FILE_PERMISSIONS
        FILES_MATCHING PATTERN "*.a"
        )
  endforeach()


INSTALL(
  DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/"
  DESTINATION ${FLYWAVE_BASE_INSTALL_DIR}
  USE_SOURCE_PERMISSIONS FILE_PERMISSIONS
  FILES_MATCHING PATTERN "*.h"
  )
