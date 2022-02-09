

include_directories(${FLYWAVE_INCLUDE_DIRS})

if (MSVC)
    add_definitions(-DCONSTEXPR=const -DNOMINMAX -D_CRT_SECURE_NO_WARNINGS)
else()
    add_definitions(-DCONSTEXPR=constexpr)
endif()

FILE( GLOB topo_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cc )
FILE( GLOB topo_HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.hh ${CMAKE_CURRENT_SOURCE_DIR}/*.h )

ADD_LIBRARY(topo STATIC
            ${topo_HEADER_FILES}
            ${topo_SOURCE_FILES}
          )

TARGET_INCLUDE_DIRECTORIES(topo PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>)

SOURCE_GROUP("src" FILES ${gdal_SOURCE_FILES})
SOURCE_GROUP("include" FILES ${gdal_HEADER_FILES})

SET_TARGET_PROPERTIES(topo
                    PROPERTIES PUBLIC_HEADER "${headers}")

                    ADD_EXECUTABLE(ifc_test ifc_test.cc)

IF(UNIX AND NOT APPLE)
TARGET_LINK_LIBRARIES(ifc_test -Wl,--start-group topo pthread dl stdc++ m ${FLYWAVE_LIBRARY_DEPES} -Wl,--end-group)
ELSE()
TARGET_LINK_LIBRARIES(ifc_test topo ${FLYWAVE_LIBRARY_DEPES})
ENDIF()