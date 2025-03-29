cmake_minimum_required(VERSION 2.8.12)

ENABLE_LANGUAGE(Fortran)

project(LAPACK Fortran C)

get_filename_component (Fortran_COMPILER_NAME ${CMAKE_Fortran_COMPILER} NAME)

set(LAPACK_MAJOR_VERSION 3)
set(LAPACK_MINOR_VERSION 8)
set(LAPACK_PATCH_VERSION 0)
set(
  LAPACK_VERSION
  ${LAPACK_MAJOR_VERSION}.${LAPACK_MINOR_VERSION}.${LAPACK_PATCH_VERSION}
  )

IF(UNIX)
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-float-conversion -Wno-unused-variable -Wno-unused-const-variable -Wno-switch -Wno-unknown-pragmas -Wno-enum-compare -Wno-unused-result  -Wno-tautological-compare -Wno-attributes -Wno-sign-compare -Wno-deprecated-declarations")
IF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unused-but-set-variable -Wno-tautological-compare -Wno-unused-const-variable")
ENDIF()
ENDIF()

# Add the CMake directory for custon CMake modules
set(CMAKE_MODULE_PATH "${LAPACK_SOURCE_DIR}/CMAKE" ${CMAKE_MODULE_PATH})

# Export all symbols on Windows when building shared libraries
SET(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)

string(TOUPPER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE_UPPER)
if(${CMAKE_BUILD_TYPE_UPPER} STREQUAL "COVERAGE")
  message(STATUS "Adding coverage")
  find_package(codecov)
endif()

include(GNUInstallDirs)

set(CMAKE_MACOSX_RPATH ON)
set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
list(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES ${CMAKE_INSTALL_FULL_LIBDIR} isSystemDir)
if("${isSystemDir}" STREQUAL "-1")
  set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_FULL_LIBDIR})
  set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
endif()


# Configure the warning and code coverage suppression file
configure_file(
  "${LAPACK_SOURCE_DIR}/CTestCustom.cmake.in"
  "${LAPACK_BINARY_DIR}/CTestCustom.cmake"
  @ONLY
)

include(PreventInSourceBuilds)
include(PreventInBuildInstalls)

if(UNIX)
  if("${CMAKE_Fortran_COMPILER}" MATCHES "ifort")
    set(CMAKE_Fortran_FLAGS "${CMAKE_Fortran_FLAGS} -fp-model strict")
  endif()
  if("${CMAKE_Fortran_COMPILER}" MATCHES "xlf")
    set(CMAKE_Fortran_FLAGS "${CMAKE_Fortran_FLAGS} -qnosave -qstrict=none")
  endif()
# Delete libmtsk in linking sequence for Sun/Oracle Fortran Compiler.
# This library is not present in the Sun package SolarisStudio12.3-linux-x86-bin
  string(REPLACE \;mtsk\; \; CMAKE_Fortran_IMPLICIT_LINK_LIBRARIES "${CMAKE_Fortran_IMPLICIT_LINK_LIBRARIES}")
endif()

if(CMAKE_Fortran_COMPILER_ID STREQUAL "Compaq")
  if(WIN32)
    if(CMAKE_GENERATOR STREQUAL "NMake Makefiles")
      get_filename_component(CMAKE_Fortran_COMPILER_CMDNAM ${CMAKE_Fortran_COMPILER} NAME_WE)
      message(STATUS "Using Compaq Fortran compiler with command name ${CMAKE_Fortran_COMPILER_CMDNAM}")
      set(cmd ${CMAKE_Fortran_COMPILER_CMDNAM})
      string(TOLOWER "${cmd}" cmdlc)
      if(cmdlc STREQUAL "df")
        message(STATUS "Assume the Compaq Visual Fortran Compiler is being used")
        set(CMAKE_Fortran_USE_RESPONSE_FILE_FOR_OBJECTS 1)
        set(CMAKE_Fortran_USE_RESPONSE_FILE_FOR_INCLUDES 1)
        #This is a workaround that is needed to avoid forward-slashes in the
        #filenames listed in response files from incorrectly being interpreted as
        #introducing compiler command options
        if(${BUILD_SHARED_LIBS})
          message(FATAL_ERROR "Making of shared libraries with CVF has not been tested.")
        endif()
        set(str "NMake version 9 or later should be used. NMake version 6.0 which is\n")
        set(str "${str}   included with the CVF distribution fails to build Lapack because\n")
        set(str "${str}   the number of source files exceeds the limit for NMake v6.0\n")
        message(STATUS ${str})
        set(CMAKE_Fortran_LINK_EXECUTABLE "LINK /out:<TARGET> <LINK_FLAGS> <LINK_LIBRARIES> <OBJECTS>")
      endif()
    endif()
  endif()
endif()

# Get Python
message(STATUS "Looking for Python greater than 2.6 - ${PYTHONINTERP_FOUND}")
find_package(PythonInterp 2.7) # lapack_testing.py uses features from python 2.7 and greater
if(PYTHONINTERP_FOUND)
  message(STATUS "Using Python version ${PYTHON_VERSION_STRING}")
else()
  message(STATUS "No suitable Python version found, so skipping summary tests.")
endif()
# --------------------------------------------------

set(PKG_CONFIG_DIR ${CMAKE_INSTALL_LIBDIR}/pkgconfig)


# --------------------------------------------------
# Check for any necessary platform specific compiler flags
include(CheckLAPACKCompilerFlags)
CheckLAPACKCompilerFlags()

# --------------------------------------------------
# Check second function

include(CheckTimeFunction)
set(TIME_FUNC NONE ${TIME_FUNC})
CHECK_TIME_FUNCTION(NONE TIME_FUNC)
CHECK_TIME_FUNCTION(INT_CPU_TIME TIME_FUNC)
CHECK_TIME_FUNCTION(EXT_ETIME TIME_FUNC)
CHECK_TIME_FUNCTION(EXT_ETIME_ TIME_FUNC)
CHECK_TIME_FUNCTION(INT_ETIME TIME_FUNC)
message(STATUS "--> Will use second_${TIME_FUNC}.f and dsecnd_${TIME_FUNC}.f as timing function.")

set(SECOND_SRC ${LAPACK_SOURCE_DIR}/INSTALL/second_${TIME_FUNC}.f)
set(DSECOND_SRC ${LAPACK_SOURCE_DIR}/INSTALL/dsecnd_${TIME_FUNC}.f)

# deprecated LAPACK and LAPACKE routines
option(BUILD_DEPRECATED "Build deprecated routines" OFF)
message(STATUS "Build deprecated routines: ${BUILD_DEPRECATED}")

# --------------------------------------------------
# Precision to build
# By default all precisions are generated
option(BUILD_SINGLE "Build single precision real" ON)
option(BUILD_DOUBLE "Build double precision real" ON)
option(BUILD_COMPLEX "Build single precision complex" ON)
option(BUILD_COMPLEX16 "Build double precision complex" ON)
message(STATUS "Build single precision real: ${BUILD_SINGLE}")
message(STATUS "Build double precision real: ${BUILD_DOUBLE}")
message(STATUS "Build single precision complex: ${BUILD_COMPLEX}")
message(STATUS "Build double precision complex: ${BUILD_COMPLEX16}")

if(NOT (BUILD_SINGLE OR BUILD_DOUBLE OR BUILD_COMPLEX OR BUILD_COMPLEX16))
  message(FATAL_ERROR "Nothing to build, no precision selected.
  Please enable at least one of these:
  BUILD_SINGLE, BUILD_DOUBLE, BUILD_COMPLEX, BUILD_COMPLEX16.")
endif()

# --------------------------------------------------
# Subdirectories that need to be processed
option(USE_OPTIMIZED_BLAS "Whether or not to use an optimized BLAS library instead of included netlib BLAS" OFF)

add_subdirectory(BLAS)
set(BLAS_LIBRARIES blas)

add_subdirectory(CBLAS)


# Neither user specified or optimized LAPACK libraries can be used
set(LAPACK_LIBRARIES lapack)
add_subdirectory(SRC)
add_subdirectory(LAPACKE)
