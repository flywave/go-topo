message(STATUS "LAPACKE enable")
enable_language(C)

set(LAPACK_INSTALL_EXPORT_NAME lapacke-targets)

if(WIN32 AND NOT UNIX)
  add_definitions(-DHAVE_LAPACK_CONFIG_H -DLAPACK_COMPLEX_STRUCTURE)
  message(STATUS "Windows BUILD")
endif()

get_directory_property(DirDefs COMPILE_DEFINITIONS)

include_directories(include ${LAPACK_BINARY_DIR}/include)
add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(utils)

macro(append_subdir_files variable dirname)
  get_directory_property(holder DIRECTORY ${dirname} DEFINITION ${variable})
  foreach(depfile ${holder})
    list(APPEND ${variable} "${dirname}/${depfile}")
  endforeach()
endmacro()

append_subdir_files(LAPACKE_INCLUDE "include")
append_subdir_files(SOURCES "src")
append_subdir_files(DEPRECATED "src")
append_subdir_files(EXTENDED "src")
append_subdir_files(MATGEN "src")
append_subdir_files(UTILS "utils")

if(BUILD_DEPRECATED)
  list(APPEND SOURCES ${DEPRECATED})
endif()
if(USE_XBLAS)
  list(APPEND SOURCES ${EXTENDED})
endif()
if(LAPACKE_WITH_TMG)
  list(APPEND SOURCES ${MATGEN})
endif()
list(APPEND SOURCES ${UTILS})

add_library(lapacke STATIC ${SOURCES})

IF(FLYWAVE_ENABLE_SOLUTION_FOLDERS)
  SET_TARGET_PROPERTIES(lapacke PROPERTIES FOLDER external)
ENDIF(FLYWAVE_ENABLE_SOLUTION_FOLDERS)

SET_TARGET_PROPERTIES(lapacke PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR})
SET_TARGET_PROPERTIES(lapacke PROPERTIES 
    LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}
    LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR})
SET_TARGET_PROPERTIES(lapacke PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR})