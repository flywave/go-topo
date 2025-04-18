message(STATUS "CBLAS enable")
enable_language(C)

set(LAPACK_INSTALL_EXPORT_NAME cblas-targets)

include_directories(include ${LAPACK_BINARY_DIR}/include)
add_subdirectory(include)
add_subdirectory(src)

macro(append_subdir_files variable dirname)
get_directory_property(holder DIRECTORY ${dirname} DEFINITION ${variable})
foreach(depfile ${holder})
  list(APPEND ${variable} "${dirname}/${depfile}")
endforeach()
endmacro()

append_subdir_files(CBLAS_INCLUDE "include")
