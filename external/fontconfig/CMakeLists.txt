cmake_minimum_required(VERSION 2.8)
project( fontconfig )

IF(UNIX)
  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-implicit-function-declaration -Wno-deprecated-declarations -Wno-shadow -Wno-unused-function -Wno-format-extra-args -Wno-unknown-pragmas -Wno-tautological-compare -Wno-attributes -Wno-unused-const-variable -Wno-sign-compare -Wno-deprecated-declarations")
    IF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-cpp -Wno-unused-variable")
    ENDIF()
ENDIF()

add_definitions(-DHAVE_CONFIG_H)
add_definitions(-DFC_CACHEDIR="/var/cache/fontconfig")
add_definitions(-DFONTCONFIG_PATH="/etc/fonts")

IF(APPLE)
INCLUDE_DIRECTORIES( BEFORE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/darwin)
  INCLUDE_DIRECTORIES(AFTER "${CMAKE_CURRENT_SOURCE_DIR}/../libxml/mac
                                    ${CMAKE_CURRENT_SOURCE_DIR}/../libxml/mac/include")
ENDIF()

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
INCLUDE_DIRECTORIES( BEFORE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/linux)
INCLUDE_DIRECTORIES( AFTER "${CMAKE_CURRENT_SOURCE_DIR}/../libxml/linux
                                    ${CMAKE_CURRENT_SOURCE_DIR}/../libxml/linux/include")
ENDIF()

IF (WIN32)
  INCLUDE_DIRECTORIES(AFTER "${CMAKE_CURRENT_SOURCE_DIR}/../libxml/win32
                                    ${CMAKE_CURRENT_SOURCE_DIR}/../libxml/win32/include")
  INCLUDE_DIRECTORIES( BEFORE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/win32)
ENDIF()


IF (WIN32)
  INCLUDE_DIRECTORIES(AFTER "${CMAKE_CURRENT_SOURCE_DIR}/../libexpat/arch/win")
ELSE()
  INCLUDE_DIRECTORIES(AFTER "${CMAKE_CURRENT_SOURCE_DIR}/../libexpat/arch/unix")
ENDIF()

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include)

INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    "${CMAKE_CURRENT_SOURCE_DIR}/../libexpat/expat/lib"
    "${CMAKE_CURRENT_SOURCE_DIR}/../freetype2/include/"
    "${CMAKE_CURRENT_SOURCE_DIR}/../freetype2/src/include/"
    "${CMAKE_CURRENT_SOURCE_DIR}/../zlib"
    "${CMAKE_CURRENT_BINARY_DIR}/../zlib"
    "${CMAKE_CURRENT_SOURCE_DIR}/../libxml/src/include/"
    "${CMAKE_CURRENT_SOURCE_DIR}/../icu/source/common/"
    "${CMAKE_CURRENT_SOURCE_DIR}/../icu/source/i18n/"
)

if( MSVC )
  include_directories( ${CMAKE_INCLUDE_PATH}/msvc )
  add_definitions( -D_CRT_SECURE_NO_DEPRECATE -D_CRT_NONSTDC_NO_DEPRECATE -wd4018)
endif(MSVC)
set(sub_dir_name src)

set( fontconfig_SRCS
      src/src/fcarch.h
      src/src/fcatomic.c
      src/src/fcblanks.c
      src/src/fccache.c
      src/src/fccfg.c
      src/src/fccharset.c
      src/src/fccompat.c
      src/src/fcdbg.c
      src/src/fcdefault.c
      src/src/fcdir.c
      src/src/fcformat.c
      src/src/fcfreetype.c
      src/src/fcfs.c
      src/src/fchash.c
      src/src/fcinit.c
      src/src/fclang.c
      src/src/fclist.c
      src/src/fcmatch.c
      src/src/fcmatrix.c
      src/src/fcname.c
      src/src/fcobjs.c
      src/src/fcpat.c
      src/src/fcserialize.c
      src/src/fcstat.c
      src/src/fcstr.c
      src/src/fcxml.c
      src/src/ftglue.h
      src/src/ftglue.c
)

add_library( fontconfig STATIC ${fontconfig_SRCS} )

set_target_properties(fontconfig PROPERTIES OUTPUT_NAME fontconfig )

SET_TARGET_PROPERTIES(fontconfig PROPERTIES
ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}
ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR})
SET_TARGET_PROPERTIES(fontconfig PROPERTIES 
LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}
LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR})
SET_TARGET_PROPERTIES(fontconfig PROPERTIES
RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}
RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR})

IF(FLYWAVE_ENABLE_SOLUTION_FOLDERS)
  SET_TARGET_PROPERTIES(fontconfig PROPERTIES FOLDER external)
ENDIF(FLYWAVE_ENABLE_SOLUTION_FOLDERS)
