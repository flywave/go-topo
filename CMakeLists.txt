CMAKE_MINIMUM_REQUIRED(VERSION 3.1.3)

PROJECT(go-topo C CXX)

IF(APPLE)
set(CMAKE_Fortran_COMPILER
    "gfortran"
    CACHE STRING "" FORCE)
ENDIF(APPLE)

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
  if(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64")
    SET(FLYWAVE_LIBRARY_OUTPUT_PATH "${FLYWAVE_BASE_INSTALL_DIR}/linux_arm")
  else()
    SET(FLYWAVE_LIBRARY_OUTPUT_PATH "${FLYWAVE_BASE_INSTALL_DIR}/linux")
  endif()
ENDIF()
MAKE_DIRECTORY(${FLYWAVE_LIBRARY_OUTPUT_PATH})

SET(FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}")
SET(FLYWAVE_LIBRARY_DIRS "")

# fontconfig
IF(NOT FC_INCLUDE)
  ADD_SUBDIRECTORY("${CMAKE_CURRENT_SOURCE_DIR}/external/fontconfig/")

  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/fontconfig/include/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/fontconfig/include/src/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/fontconfig/src/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/fontconfig/")
  LIST(APPEND FLYWAVE_LIBRARY_DEPES "fontconfig")
  SET(FC_INCLUDE YES)
ENDIF()

# freetype2
IF(NOT FREETYPE_INCLUDE)

  ADD_SUBDIRECTORY("${CMAKE_CURRENT_SOURCE_DIR}/external/freetype2")

  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/freetype2/include/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/freetype2/")
  LIST(APPEND FLYWAVE_LIBRARY_DEPES "freetype")
  SET(FREETYPE_INCLUDE YES)
ENDIF()

# libexpat
IF(NOT EXPAT_INCLUDE)
  ADD_SUBDIRECTORY("${CMAKE_CURRENT_SOURCE_DIR}/external/libexpat")
  IF (WIN32)
    LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/libexpat/arch/win")
  ELSE()
    LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/libexpat/arch/unix")
  ENDIF()

  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/libexpat/expat/lib")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/libexpat/")
  LIST(APPEND FLYWAVE_LIBRARY_DEPES "expat")
  SET(EXPAT_INCLUDE YES)
ENDIF()

# icu
IF(NOT ICU_INCLUDE)
  ADD_SUBDIRECTORY("${CMAKE_CURRENT_SOURCE_DIR}/external/icu")

  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/icu/source/common/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/icu/source/i18n/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/icu/")
  LIST(APPEND FLYWAVE_LIBRARY_DEPES "icudata" "icui18n" "icuuc" "icudt" "icuuc")
  SET(ICU_INCLUDE YES)
ENDIF()

# xml2
IF(NOT XML2_INCLUDE)
  ADD_SUBDIRECTORY("${CMAKE_CURRENT_SOURCE_DIR}/external/libxml")
  IF (WIN32)
    LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/libxml/win32
                                      ${CMAKE_CURRENT_SOURCE_DIR}/external/libxml/win32/include")
  ENDIF()

  IF(UNIX)
  IF(APPLE)
    LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/libxml/mac
                                      ${CMAKE_CURRENT_SOURCE_DIR}/external/libxml/mac/include")
  ELSE()
    LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/libxml/linux
                                      ${CMAKE_CURRENT_SOURCE_DIR}/external/libxml/linux/include")
  ENDIF()
  ENDIF()
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/libxml/src/include/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/libxml/")
  LIST(APPEND FLYWAVE_LIBRARY_DEPES "xml2")
  SET(XML2_INCLUDE YES)
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

# rapidjson
IF(NOT RAPIDJSON_INCLUDE)
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/rapidjson/include/")

  SET(RAPIDJSON_INCLUDE YES)
ENDIF()

# Eigen
IF(NOT EIGEN_INCLUDE)
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/eigen/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/eigen/unsupported/")

  SET(EIGEN_INCLUDE YES)
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
  LIST(APPEND FLYWAVE_LIBRARY_DEPES "ifc"
                                    "geometry_mapping_ifc2x3" 
                                    "geometry_mapping_ifc4" 
                                    "geometry_mapping_ifc4x1" 
                                    "geometry_mapping_ifc4x2"
                                    "geometry_mapping_ifc4x3_add1"
                                    "geometry_mapping_ifc4x3_add2"
                                    "geometry_mapping_ifc4x3_tc1"
                                    "geometry_mapping_ifc4x3"
                                    "geometry_serializer_ifc2x3"
                                    "geometry_serializer_ifc4"
                                    "geometry_serializer_ifc4x1"
                                    "geometry_serializer_ifc4x2"
                                    "geometry_serializer_ifc4x3_add1"
                                    "geometry_serializer_ifc4x3_add2"
                                    "geometry_serializer_ifc4x3_tc1"
                                    "geometry_serializer_ifc4x3"
                                    "read_data_ifc2x3"
                                    "read_data_ifc4"
                                    "read_data_ifc4x1"
                                    "read_data_ifc4x2"
                                    "read_data_ifc4x3_add1"
                                    "read_data_ifc4x3_add2"
                                    "read_data_ifc4x3_tc1"
                                    "read_data_ifc4x3")
  SET(IFC_INCLUDE YES)
ENDIF()

# Ipopt
IF(NOT IPOPT_INCLUDE)
  ADD_SUBDIRECTORY("${CMAKE_CURRENT_SOURCE_DIR}/external/Ipopt")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/Ipopt/src/Interfaces/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/Ipopt/src/Interfaces/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/Ipopt/src/LinAlg/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/Ipopt/src/Algorithm/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/Ipopt/src/Common/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/Ipopt/src/")
  LIST(APPEND FLYWAVE_LIBRARY_DEPES "ipopt")
  SET(IPOPT_INCLUDE YES)
ENDIF()

# LAPACK
IF(NOT LAPACK_INCLUDE AND NOT APPLE)
  ADD_SUBDIRECTORY("${CMAKE_CURRENT_SOURCE_DIR}/external/lapack/")

  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/lapack/BLAS/SRC/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/lapack/SRC/")
  LIST(APPEND FLYWAVE_LIBRARY_DEPES "lapack" "blas" )
  SET(LAPACK_INCLUDE YES)
ENDIF()

# Ma27
IF(NOT MA27_INCLUDE)
  ADD_SUBDIRECTORY("${CMAKE_CURRENT_SOURCE_DIR}/external/ma27")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/ma27/")
  LIST(APPEND FLYWAVE_LIBRARY_DEPES "ma27")
  SET(MA27_INCLUDE YES)
ENDIF()

# Metis
IF(NOT METIS_INCLUDE)
  ADD_SUBDIRECTORY("${CMAKE_CURRENT_SOURCE_DIR}/external/metis")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/metis/include/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/metis/libmetis/")
  LIST(APPEND FLYWAVE_LIBRARY_DEPES "metis")
  SET(METIS_INCLUDE YES)
ENDIF()

# NLOPT
IF(NOT NLOPT_INCLUDE)
  ADD_SUBDIRECTORY("${CMAKE_CURRENT_SOURCE_DIR}/external/nlopt")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/external/nlopt/src/api/")
  LIST(APPEND FLYWAVE_INCLUDE_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/nlopt/")
  LIST(APPEND FLYWAVE_LIBRARY_DIRS "${CMAKE_CURRENT_BINARY_DIR}/external/nlopt/")
  LIST(APPEND FLYWAVE_LIBRARY_DEPES "nlopt")
  SET(NLOPT_INCLUDE YES)
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
