IF(UNIX)
  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-array-bounds  -Wno-unused-function -Wno-enum-compare -Wno-implicit-function-declaration -Wno-int-conversion -Wno-format-extra-args -Wno-float-conversion -Wno-tautological-pointer-compare -Wno-attributes -Wno-unknown-pragmas -Wno-tautological-compare -Wno-attributes -Wno-unused-const-variable -Wno-sign-compare -Wno-deprecated-declarations")

IF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unused-but-set-variable -Wno-misleading-indentation")
ENDIF()
ENDIF()


INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../icu/source/common/")
INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../icu/source/i18n/")
INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../zlib/")
INCLUDE_DIRECTORIES("${CMAKE_CURRENT_BINARY_DIR}/../zlib/")

SET(XML2_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
INCLUDE_DIRECTORIES("${XML2_SOURCE_DIR}/include" "${CMAKE_INSTALL_PREFIX}/include")

IF (WIN32)
  INCLUDE_DIRECTORIES(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/win32 ${CMAKE_CURRENT_SOURCE_DIR}/win32/include)
  INCLUDE_DIRECTORIES("${XML2_SOURCE_DIR}/win32/VC10")
ELSEIF(APPLE)
  INCLUDE_DIRECTORIES(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/mac ${CMAKE_CURRENT_SOURCE_DIR}/mac/include)
ELSEIF(UNIX)
  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-parentheses-equality " )
  INCLUDE_DIRECTORIES(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/linux ${CMAKE_CURRENT_SOURCE_DIR}/linux/include)
  set(UNIX_DEFINITIONS -D_REENTRANT)
  add_definitions(${UNIX_DEFINITIONS})
ENDIF()


FILE( GLOB xml2_SOURCES ${XML2_SOURCE_DIR}/*.c )

FILE( GLOB xml2_api_HEADERS ${XML2_SOURCE_DIR}/include/libxml/*.h )

SET(XML2_LIBTYPE STATIC)

SET(xml2_HEADERS
${CMAKE_CURRENT_SOURCE_DIR}/linux/config.h
${CMAKE_CURRENT_SOURCE_DIR}/linux/include/libxml/xmlversion.h
${CMAKE_CURRENT_SOURCE_DIR}/mac/config.h
${CMAKE_CURRENT_SOURCE_DIR}/mac/include/libxml/xmlversion.h
${CMAKE_CURRENT_SOURCE_DIR}/win32/config.h
${CMAKE_CURRENT_SOURCE_DIR}/win32/include/libxml/xmlversion.h
${CMAKE_CURRENT_SOURCE_DIR}/src/include/libxml/c14n.h
${CMAKE_CURRENT_SOURCE_DIR}/src/include/libxml/catalog.h
${CMAKE_CURRENT_SOURCE_DIR}/src/include/libxml/chvalid.h
${CMAKE_CURRENT_SOURCE_DIR}/src/include/libxml/debugXML.h
${CMAKE_CURRENT_SOURCE_DIR}/src/include/libxml/dict.h
${CMAKE_CURRENT_SOURCE_DIR}/src/include/libxml/DOCBparser.h
${CMAKE_CURRENT_SOURCE_DIR}/src/include/libxml/encoding.h
${CMAKE_CURRENT_SOURCE_DIR}/src/include/libxml/entities.h
${CMAKE_CURRENT_SOURCE_DIR}/src/include/libxml/globals.h
${CMAKE_CURRENT_SOURCE_DIR}/src/include/libxml/hash.h
${CMAKE_CURRENT_SOURCE_DIR}/src/include/libxml/HTMLparser.h
${CMAKE_CURRENT_SOURCE_DIR}/src/include/libxml/HTMLtree.h
${CMAKE_CURRENT_SOURCE_DIR}/src/include/libxml/list.h
${CMAKE_CURRENT_SOURCE_DIR}/src/include/libxml/parser.h
${CMAKE_CURRENT_SOURCE_DIR}/src/include/libxml/parserInternals.h
${CMAKE_CURRENT_SOURCE_DIR}/src/include/libxml/pattern.h
${CMAKE_CURRENT_SOURCE_DIR}/src/include/libxml/relaxng.h
${CMAKE_CURRENT_SOURCE_DIR}/src/include/libxml/SAX.h
${CMAKE_CURRENT_SOURCE_DIR}/src/include/libxml/SAX2.h
${CMAKE_CURRENT_SOURCE_DIR}/src/include/libxml/schemasInternals.h
${CMAKE_CURRENT_SOURCE_DIR}/src/include/libxml/schematron.h
${CMAKE_CURRENT_SOURCE_DIR}/src/include/libxml/threads.h
${CMAKE_CURRENT_SOURCE_DIR}/src/include/libxml/tree.h
${CMAKE_CURRENT_SOURCE_DIR}/src/include/libxml/uri.h
${CMAKE_CURRENT_SOURCE_DIR}/src/include/libxml/valid.h
${CMAKE_CURRENT_SOURCE_DIR}/src/include/libxml/xinclude.h
${CMAKE_CURRENT_SOURCE_DIR}/src/include/libxml/xlink.h
${CMAKE_CURRENT_SOURCE_DIR}/src/include/libxml/xmlautomata.h
${CMAKE_CURRENT_SOURCE_DIR}/src/include/libxml/xmlerror.h
${CMAKE_CURRENT_SOURCE_DIR}/src/include/libxml/xmlexports.h
${CMAKE_CURRENT_SOURCE_DIR}/src/include/libxml/xmlIO.h
${CMAKE_CURRENT_SOURCE_DIR}/src/include/libxml/xmlmemory.h
${CMAKE_CURRENT_SOURCE_DIR}/src/include/libxml/xmlmodule.h
${CMAKE_CURRENT_SOURCE_DIR}/src/include/libxml/xmlreader.h
${CMAKE_CURRENT_SOURCE_DIR}/src/include/libxml/xmlregexp.h
${CMAKE_CURRENT_SOURCE_DIR}/src/include/libxml/xmlsave.h
${CMAKE_CURRENT_SOURCE_DIR}/src/include/libxml/xmlschemas.h
${CMAKE_CURRENT_SOURCE_DIR}/src/include/libxml/xmlschemastypes.h
${CMAKE_CURRENT_SOURCE_DIR}/src/include/libxml/xmlstring.h
${CMAKE_CURRENT_SOURCE_DIR}/src/include/libxml/xmlunicode.h
${CMAKE_CURRENT_SOURCE_DIR}/src/include/libxml/xmlwriter.h
${CMAKE_CURRENT_SOURCE_DIR}/src/include/libxml/xpath.h
${CMAKE_CURRENT_SOURCE_DIR}/src/include/libxml/xpathInternals.h
${CMAKE_CURRENT_SOURCE_DIR}/src/include/libxml/xpointer.h
${CMAKE_CURRENT_SOURCE_DIR}/src/include/win32config.h
${CMAKE_CURRENT_SOURCE_DIR}/src/include/wsockcompat.h
)

SET(xml2_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/buf.c
  ${CMAKE_CURRENT_SOURCE_DIR}/src/buf.h
            ${CMAKE_CURRENT_SOURCE_DIR}/src/c14n.c
            ${CMAKE_CURRENT_SOURCE_DIR}/src/catalog.c
            ${CMAKE_CURRENT_SOURCE_DIR}/src/chvalid.c
            ${CMAKE_CURRENT_SOURCE_DIR}/src/debugXML.c
            ${CMAKE_CURRENT_SOURCE_DIR}/src/dict.c
            ${CMAKE_CURRENT_SOURCE_DIR}/src/DOCBparser.c
            ${CMAKE_CURRENT_SOURCE_DIR}/src/elfgcchack.h
            ${CMAKE_CURRENT_SOURCE_DIR}/src/enc.h
            ${CMAKE_CURRENT_SOURCE_DIR}/src/encoding.c
            ${CMAKE_CURRENT_SOURCE_DIR}/src/entities.c
            ${CMAKE_CURRENT_SOURCE_DIR}/src/error.c
            ${CMAKE_CURRENT_SOURCE_DIR}/src/globals.c
            ${CMAKE_CURRENT_SOURCE_DIR}/src/hash.c
            ${CMAKE_CURRENT_SOURCE_DIR}/src/HTMLparser.c
            ${CMAKE_CURRENT_SOURCE_DIR}/src/HTMLtree.c
            ${CMAKE_CURRENT_SOURCE_DIR}/src/legacy.c
            ${CMAKE_CURRENT_SOURCE_DIR}/src/libxml.h
            ${CMAKE_CURRENT_SOURCE_DIR}/src/list.c
            ${CMAKE_CURRENT_SOURCE_DIR}/src/parser.c
            ${CMAKE_CURRENT_SOURCE_DIR}/src/parserInternals.c
            ${CMAKE_CURRENT_SOURCE_DIR}/src/pattern.c
            ${CMAKE_CURRENT_SOURCE_DIR}/src/relaxng.c
            ${CMAKE_CURRENT_SOURCE_DIR}/src/save.h
            ${CMAKE_CURRENT_SOURCE_DIR}/src/SAX.c
            ${CMAKE_CURRENT_SOURCE_DIR}/src/SAX2.c
            ${CMAKE_CURRENT_SOURCE_DIR}/src/schematron.c
            ${CMAKE_CURRENT_SOURCE_DIR}/src/threads.c
            ${CMAKE_CURRENT_SOURCE_DIR}/src/timsort.h
            ${CMAKE_CURRENT_SOURCE_DIR}/src/tree.c
            ${CMAKE_CURRENT_SOURCE_DIR}/src/uri.c
            ${CMAKE_CURRENT_SOURCE_DIR}/src/valid.c
            ${CMAKE_CURRENT_SOURCE_DIR}/src/xinclude.c
            ${CMAKE_CURRENT_SOURCE_DIR}/src/xlink.c
            ${CMAKE_CURRENT_SOURCE_DIR}/src/xmlIO.c
            ${CMAKE_CURRENT_SOURCE_DIR}/src/xmlmemory.c
            ${CMAKE_CURRENT_SOURCE_DIR}/src/xmlmodule.c
            ${CMAKE_CURRENT_SOURCE_DIR}/src/xmlreader.c
            ${CMAKE_CURRENT_SOURCE_DIR}/src/xmlregexp.c
            ${CMAKE_CURRENT_SOURCE_DIR}/src/xmlsave.c
            ${CMAKE_CURRENT_SOURCE_DIR}/src/xmlschemas.c
            ${CMAKE_CURRENT_SOURCE_DIR}/src/xmlschemastypes.c
            ${CMAKE_CURRENT_SOURCE_DIR}/src/xmlstring.c
            ${CMAKE_CURRENT_SOURCE_DIR}/src/xmlunicode.c
            ${CMAKE_CURRENT_SOURCE_DIR}/src/xmlwriter.c
            ${CMAKE_CURRENT_SOURCE_DIR}/src/xpath.c
            ${CMAKE_CURRENT_SOURCE_DIR}/src/xpointer.c
            ${CMAKE_CURRENT_SOURCE_DIR}/src/xzlib.h
)
SOURCE_GROUP("src" FILES ${xml2_SOURCES})
SOURCE_GROUP("include" FILES ${xml2_HEADERS} ${xml2_api_HEADERS})

ADD_LIBRARY(xml2 STATIC ${xml2_SOURCES} ${xml2_HEADERS})

IF(APPLE)
  TARGET_COMPILE_DEFINITIONS(xml2 PUBLIC _REENTRANT)
ENDIF()

SET_TARGET_PROPERTIES(xml2 PROPERTIES PUBLIC_HEADER "${xml2_api_HEADERS}")

SET_TARGET_PROPERTIES(xml2 PROPERTIES
ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}
ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR})
SET_TARGET_PROPERTIES(xml2 PROPERTIES 
LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}
LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR})
SET_TARGET_PROPERTIES(xml2 PROPERTIES
RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}
RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR})

IF(FLYWAVE_ENABLE_SOLUTION_FOLDERS)
  SET_TARGET_PROPERTIES(xml2 PROPERTIES FOLDER external)
ENDIF(FLYWAVE_ENABLE_SOLUTION_FOLDERS)
