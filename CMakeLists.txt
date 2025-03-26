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

# ogg
IF(NOT OGG_INCLUDE)
  ADD_SUBDIRECTORY("${CMAKE_CURRENT_SOURCE_DIR}/external/ogg/")

  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/ogg/include/opencascade/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/ogg/")
  
  LIST(APPEND FLYWAVE_LIBRARY_DEPES "TKernel"
                                    "TKMath"
                                    "TKG2d"
                                    "TKG3d"
                                    "TKGeomBase"
                                    "TKBRep"
                                    "TKService"
                                    "TKV3d"
                                    "TKShHealing"
                                    "TKTopAlgo"
                                    "TKMesh"
                                    "TKGeomAlgo"
                                    "TKHLR"
                                    "TKOffset"
                                    "TKFillet"
                                    "TKFeat"
                                    "TKXMesh"
                                    "TKMeshVS"
                                    "TKCDF"
                                    "TKLCAF"
                                    "TKCAF"
                                    "TKBO"
                                    "TKPrim"
                                    "TKBinL"
                                    "TKXmlL"
                                    "TKBin"
                                    "TKXml"
                                    "TKStdL"
                                    "TKStd"
                                    "TKTObj"
                                    "TKBinTObj"
                                    "TKXmlTObj"
                                    "TKVCAF"
                                    "TKXDE"
                                    "TKXSBase"
                                    "TKSTEPBase"
                                    "TKSTEPAttr"
                                    "TKSTEP209"
                                    "TKSTEP"
                                    "TKIGES"
                                    "TKBool"
                                    "TKXCAF"
                                    "TKXDEIGES"
                                    "TKXDESTEP"
                                    "TKSTL"
                                    "TKVRML"
                                    "TKRWMesh"
                                    "TKXmlXCAF"
                                    "TKBinXCAF"
                                    "TKXDECascade"
                                    "TKExpress"
)
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
