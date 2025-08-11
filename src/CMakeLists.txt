

include_directories(${FLYWAVE_INCLUDE_DIRS})

if (MSVC)
    add_definitions(-DCONSTEXPR=const -DNOMINMAX -D_CRT_SECURE_NO_WARNINGS)
else()
    add_definitions(-DCONSTEXPR=constexpr)
endif()

IF(APPLE)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++17")
ELSE()
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
ENDIF()

FILE( GLOB topo_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cc )
FILE( GLOB topo_HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.hh ${CMAKE_CURRENT_SOURCE_DIR}/*.h )

LIST(FILTER topo_SOURCE_FILES EXCLUDE REGEX ".*_test.cc")

ADD_LIBRARY(topo STATIC
            ${topo_HEADER_FILES}
            ${topo_SOURCE_FILES}
          )

TARGET_INCLUDE_DIRECTORIES(topo PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>)
target_compile_features(topo PRIVATE cxx_std_17)

SOURCE_GROUP("src" FILES ${gdal_SOURCE_FILES})
SOURCE_GROUP("include" FILES ${gdal_HEADER_FILES})

IF(APPLE)
SET_TARGET_PROPERTIES(topo PROPERTIES
ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}
ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR})
SET_TARGET_PROPERTIES(topo PROPERTIES 
LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}
LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR})
SET_TARGET_PROPERTIES(topo PROPERTIES
RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}
RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR})
ENDIF()

SET_TARGET_PROPERTIES(topo
                    PROPERTIES PUBLIC_HEADER "${headers}")

                    ADD_EXECUTABLE(ifc_test ifc_test.cc)
target_compile_features(ifc_test PRIVATE cxx_std_17)

IF(UNIX AND NOT APPLE)
TARGET_LINK_LIBRARIES(ifc_test -Wl,--start-group topo pthread dl stdc++ m ${FLYWAVE_LIBRARY_DEPES} -Wl,--end-group)
ELSE()
TARGET_LINK_LIBRARIES(ifc_test topo ${FLYWAVE_LIBRARY_DEPES})
ENDIF()

ADD_EXECUTABLE(topo_test topo_test.cc)
target_compile_features(topo_test PRIVATE cxx_std_17)

IF(MINGW)
     TARGET_LINK_LIBRARIES(topo_test -Wl,--start-group  stdc++ ${FLYWAVE_LIBRARY_DEPES} topo  -Wl,--end-group)
ELSEIF(UNIX AND NOT APPLE)
    TARGET_LINK_LIBRARIES(topo_test -Wl,--start-group topo pthread dl stdc++ m ${FLYWAVE_LIBRARY_DEPES} -Wl,--end-group)
ELSE()
    TARGET_LINK_LIBRARIES(topo_test topo ${FLYWAVE_LIBRARY_DEPES})
ENDIF()

ADD_EXECUTABLE(primitives_test primitives_test.cc)
target_compile_features(primitives_test PRIVATE cxx_std_17)

IF(MINGW)
     TARGET_LINK_LIBRARIES(primitives_test -Wl,--start-group  stdc++ ${FLYWAVE_LIBRARY_DEPES} topo  -Wl,--end-group)
ELSEIF(UNIX AND NOT APPLE)
    TARGET_LINK_LIBRARIES(primitives_test -Wl,--start-group topo pthread dl stdc++ m ${FLYWAVE_LIBRARY_DEPES} -Wl,--end-group)
ELSE()
    TARGET_LINK_LIBRARIES(primitives_test topo ${FLYWAVE_LIBRARY_DEPES})
ENDIF()

ADD_EXECUTABLE(bounding_pipe_test bounding_pipe_test.cc)
target_compile_features(bounding_pipe_test PRIVATE cxx_std_17)

IF(MINGW)
     TARGET_LINK_LIBRARIES(bounding_pipe_test -Wl,--start-group  stdc++ ${FLYWAVE_LIBRARY_DEPES} topo  -Wl,--end-group)
ELSEIF(UNIX AND NOT APPLE)
    TARGET_LINK_LIBRARIES(bounding_pipe_test -Wl,--start-group topo pthread dl stdc++ m ${FLYWAVE_LIBRARY_DEPES} -Wl,--end-group)
ELSE()
    TARGET_LINK_LIBRARIES(bounding_pipe_test topo ${FLYWAVE_LIBRARY_DEPES})
ENDIF()

ADD_EXECUTABLE(primitives_c_test primitives_c_test.cc)
target_compile_features(primitives_c_test PRIVATE cxx_std_17)

IF(MINGW)
     TARGET_LINK_LIBRARIES(primitives_c_test -Wl,--start-group  stdc++ ${FLYWAVE_LIBRARY_DEPES} topo  -Wl,--end-group)
ELSEIF(UNIX AND NOT APPLE)
    TARGET_LINK_LIBRARIES(primitives_c_test -Wl,--start-group topo pthread dl stdc++ m ${FLYWAVE_LIBRARY_DEPES} -Wl,--end-group)
ELSE()
    TARGET_LINK_LIBRARIES(primitives_c_test topo ${FLYWAVE_LIBRARY_DEPES})
ENDIF()