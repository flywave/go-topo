cmake_minimum_required(VERSION 3.10)
project(ifc LANGUAGES CXX)

include(CheckCXXCompilerFlag)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

if(MSVC)
    add_definitions(-D_UNICODE)
else()
    add_definitions(-fPIC -Wno-non-virtual-dtor)
endif()

# Include directories
set(OGG_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/../../ogg/include/opencascade")

include_directories(
    ${INCLUDE_DIRECTORIES}
    "${CMAKE_CURRENT_SOURCE_DIR}/../../libboost/boost_1_67_0"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../eigen"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../eigen/unsupported"
    "${CMAKE_CURRENT_SOURCE_DIR}/../src"
    ${OGG_INCLUDE_DIR}
)

# Schema versions configuration
if(NOT SCHEMA_VERSIONS)
    set(SCHEMA_VERSIONS "2x3" "4" "4x1" "4x2" "4x3" "4x3_tc1" "4x3_add1" "4x3_add2")
endif()

message(STATUS "IFC SCHEMA_VERSIONS that will be used for the build: ${SCHEMA_VERSIONS}")

# Schema definitions
foreach(schema ${SCHEMA_VERSIONS})
    add_definitions(-DHAS_SCHEMA_${schema})
endforeach()

string(REPLACE ";" ")(" schema_version_seq "(${SCHEMA_VERSIONS})")
add_definitions(-DSCHEMA_SEQ=${schema_version_seq})

# Source files
file(GLOB SRC_FILES_GEOM ../src/ifcgeom/*.cpp)
file(GLOB SRC_FILES_GEOM_KERNEL ../src/ifcgeom/kernel/*.cpp)
set(SRC_FILES_GEOM_SERIALIZE ../src/ifcgeom/Serialization/Serialization.cpp)
file(GLOB SRC_FILES_PARSER ../src/ifcparse/*.cpp)

# Filter parser files
foreach(file ${SRC_FILES_PARSER})
    get_filename_component(filename "${file}" NAME)
    if(NOT "${filename}" MATCHES "[0-9]")
        list(APPEND IFCPARSE_CPP_FILES "${file}")
    endif()
endforeach()


# Add schema-specific files
foreach(schema ${SCHEMA_VERSIONS})
    list(APPEND IFCPARSE_CPP_FILES
        ../src/ifcparse/Ifc${schema}.cpp
        ../src/ifcparse/Ifc${schema}-schema.cpp
    )
endforeach()

set(SRC_FILES_PARSE ${IFCPARSE_CPP_FILES})

# Create serializer libraries
foreach(schema ${SCHEMA_VERSIONS})
    add_library(geometry_serializer_ifc${schema} STATIC ../src/ifcgeom/Serialization/schema/Serialization.cpp)
    set_target_properties(geometry_serializer_ifc${schema} PROPERTIES 
        COMPILE_FLAGS "-DIFC_GEOM_EXPORTS -DIfcSchema=Ifc${schema}"
    )
    list(APPEND geometry_serializer_libraries geometry_serializer_ifc${schema})
    target_compile_features(geometry_serializer_ifc${schema} PRIVATE cxx_std_17)

    # Output directories
    set_target_properties(geometry_serializer_ifc${schema} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}/../
        ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}/../
        LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}/../
        LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}/../
        RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}/../
        RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}/../
    )
endforeach()

    foreach(schema ${SCHEMA_VERSIONS})
        file(GLOB IFCGEOM_I_FILES ../src/ifcgeom/mapping/*.i)
        file(GLOB IFCGEOM_H_FILES ../src/ifcgeom/mapping/*.h)
        file(GLOB IFCGEOM_CPP_FILES ../src/ifcgeom/mapping/*.cpp)
        set(IFCGEOM_FILES ${IFCGEOM_CPP_FILES} ${IFCGEOM_H_FILES} ${IFCGEOM_I_FILES})
        
        add_library(geometry_mapping_ifc${schema} STATIC ${IFCGEOM_FILES})
        target_compile_features(geometry_mapping_ifc${schema} PRIVATE cxx_std_17)
        set_target_properties(geometry_mapping_ifc${schema} PROPERTIES COMPILE_FLAGS "-DIFC_GEOM_EXPORTS -DIfcSchema=Ifc${schema}")

        # Output directories
        set_target_properties(geometry_mapping_ifc${schema} PROPERTIES
            ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}/../
            ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}/../
            LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}/../
            LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}/../
            RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}/../
            RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}/../
        )
    endforeach()

# Main library
add_library(ifc STATIC
    ${SRC_FILES_GEOM}
    ${SRC_FILES_GEOM_KERNEL}
    ${SRC_FILES_GEOM_SERIALIZE}
    ${SRC_FILES_PARSE}
)
target_compile_features(ifc PRIVATE cxx_std_17)

# Output directories
set_target_properties(ifc PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}/../
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}/../
    LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}/../
    LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}/../
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}/../
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}/../
)

if(FLYWAVE_ENABLE_SOLUTION_FOLDERS)
    set_target_properties(ifc PROPERTIES FOLDER external)
endif()