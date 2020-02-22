
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
add_definitions(-DFT_CONFIG_CONFIG_H=<ftconfig.h>)
add_definitions(-DFT_CONFIG_MODULES_H=<ftmodule.h>)
add_definitions(-DDARWIN_NO_CARBON)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src/include")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src/src/base")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../zlib")
include_directories("${CMAKE_CURRENT_BINARY_DIR}/../zlib")

set(BASE_SRCS
      src/src/base/ftsystem.c
      src/src/base/ftinit.c
      src/src/base/ftdebug.c

      src/src/base/ftbase.c

      src/src/base/ftbbox.c
      src/src/base/ftglyph.c

      src/src/base/ftbdf.c
      src/src/base/ftbitmap.c
      src/src/base/ftcid.c
      src/src/base/ftfstype.c
      src/src/base/ftgasp.c
      src/src/base/ftgxval.c
      src/src/base/ftlcdfil.c
      src/src/base/ftmm.c
      src/src/base/ftpfr.c
      src/src/base/ftstroke.c
      src/src/base/ftsynth.c
      src/src/base/fttype1.c
      src/src/base/ftwinfnt.c
      src/src/base/ftxf86.c

      src/src/bdf/bdf.c
      src/src/cff/cff.c
      src/src/cid/type1cid.c
      src/src/pcf/pcf.c
      src/src/pfr/pfr.c
      src/src/sfnt/sfnt.c
      src/src/truetype/truetype.c
      src/src/type1/type1.c
      src/src/type42/type42.c
      src/src/winfonts/winfnt.c

      src/src/psaux/psaux.c
      src/src/psnames/psnames.c
      src/src/pshinter/pshinter.c

      src/src/raster/raster.c
      src/src/smooth/smooth.c

      src/src/autofit/autofit.c
      src/src/gzip/ftgzip.c
      src/src/lzw/ftlzw.c
)

# if(NOT PLATFORM STREQUAL "macosx")
# list(APPEND BASE_SRCS
# 	src/builds/mac/ftmac.c
# 	)
# endif()

add_library(freetype STATIC
  ${BASE_SRCS}
)

IF(FLYWAVE_ENABLE_SOLUTION_FOLDERS)
	SET_TARGET_PROPERTIES(freetype PROPERTIES FOLDER external)
ENDIF(FLYWAVE_ENABLE_SOLUTION_FOLDERS)

if (NOT CMAKE_VERSION VERSION_LESS 2.8.11)
  target_include_directories(freetype
    PUBLIC $<INSTALL_INTERFACE:include/freetype2>)
endif ()
