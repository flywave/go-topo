project(freetype)

IF(UNIX)
  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-self-assign -Wno-parentheses-equality -Wno-shift-negative-value -Wno-deprecated-declarations -Wno-shadow -Wno-unused-function -Wno-format-extra-args -Wno-unknown-pragmas -Wno-tautological-compare -Wno-attributes -Wno-unused-const-variable -Wno-sign-compare -Wno-deprecated-declarations")
    IF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-cpp ")
    ENDIF()
  
ENDIF()

add_definitions(-DFT2_BUILD_LIBRARY)
add_definitions(-DFT_CONFIG_OPTION_SYSTEM_ZLIB)
add_definitions(-DFT2_BUILD_LIBRARY)
add_definitions(-DFT_CONFIG_CONFIG_H=<freetype/config/ftconfig.h>)
add_definitions(-DDARWIN_NO_CARBON)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/freetype")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/freetype/config")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/freetype/internal")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/devel")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src/include")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src/base")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../zlib")
include_directories("${CMAKE_CURRENT_BINARY_DIR}/../zlib")

set(BASE_SRCS
  src/autofit/autofit.c
  src/base/ftbase.c
  src/base/ftbbox.c
  src/base/ftbdf.c
  src/base/ftbitmap.c
  src/base/ftcid.c
  src/base/ftfstype.c
  src/base/ftgasp.c
  src/base/ftglyph.c
  src/base/ftgxval.c
  src/base/ftinit.c
  src/base/ftmm.c
  src/base/ftotval.c
  src/base/ftpatent.c
  src/base/ftpfr.c
  src/base/ftstroke.c
  src/base/ftsynth.c
  src/base/ftsystem.c
  src/base/fttype1.c
  src/base/ftwinfnt.c
  src/bdf/bdf.c
  src/bzip2/ftbzip2.c
  src/cache/ftcache.c
  src/cff/cff.c
  src/cid/type1cid.c
  src/gzip/ftgzip.c
  src/lzw/ftlzw.c
  src/pcf/pcf.c
  src/pfr/pfr.c
  src/psaux/psaux.c
  src/pshinter/pshinter.c
  src/psnames/psnames.c
  src/raster/raster.c
  src/sfnt/sfnt.c
  src/smooth/smooth.c
  src/truetype/truetype.c
  src/type1/type1.c
  src/type42/type42.c
  src/winfonts/winfnt.c
)

if (WIN32)
  enable_language(RC)
  list(APPEND BASE_SRCS builds/windows/ftdebug.c
                        src/base/ftver.rc)
elseif (WINCE)
  list(APPEND BASE_SRCS builds/wince/ftdebug.c)
else ()
  list(APPEND BASE_SRCS src/base/ftdebug.c)
endif ()

add_library(freetype STATIC
  ${BASE_SRCS}
)
 
SET_TARGET_PROPERTIES(freetype PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}
  ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR})
SET_TARGET_PROPERTIES(freetype PROPERTIES 
  LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}
  LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR})
SET_TARGET_PROPERTIES(freetype PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}
  RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR})
  
IF(FLYWAVE_ENABLE_SOLUTION_FOLDERS)
	SET_TARGET_PROPERTIES(freetype PROPERTIES FOLDER external)
ENDIF(FLYWAVE_ENABLE_SOLUTION_FOLDERS)

if (NOT CMAKE_VERSION VERSION_LESS 2.8.11)
  target_include_directories(freetype
    PUBLIC $<INSTALL_INTERFACE:include/freetype2>)
endif ()
