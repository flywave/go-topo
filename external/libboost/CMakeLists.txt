add_definitions(-Wno-unused-variable)
add_definitions(-Wno-deprecated-declarations)

INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/boost_1_67_0")

add_library(boost_chrono_internal STATIC
boost_1_67_0/libs/chrono/src/chrono.cpp
boost_1_67_0/libs/chrono/src/process_cpu_clocks.cpp
boost_1_67_0/libs/chrono/src/thread_clock.cpp
)

SET_TARGET_PROPERTIES(boost_chrono_internal PROPERTIES
ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}
ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR})
SET_TARGET_PROPERTIES(boost_chrono_internal PROPERTIES 
LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}
LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR})
SET_TARGET_PROPERTIES(boost_chrono_internal PROPERTIES
RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}
RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR})

IF(FLYWAVE_ENABLE_SOLUTION_FOLDERS)
  SET_TARGET_PROPERTIES(boost_chrono_internal PROPERTIES FOLDER external/boost)
ENDIF(FLYWAVE_ENABLE_SOLUTION_FOLDERS)

add_library(boost_date_time_internal STATIC
boost_1_67_0/libs/date_time/src/gregorian/date_generators.cpp
boost_1_67_0/libs/date_time/src/gregorian/greg_month.cpp
boost_1_67_0/libs/date_time/src/gregorian/greg_weekday.cpp
)

SET_TARGET_PROPERTIES(boost_date_time_internal PROPERTIES
ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}
ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR})
SET_TARGET_PROPERTIES(boost_date_time_internal PROPERTIES 
LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}
LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR})
SET_TARGET_PROPERTIES(boost_date_time_internal PROPERTIES
RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}
RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR})

IF(FLYWAVE_ENABLE_SOLUTION_FOLDERS)
  SET_TARGET_PROPERTIES(boost_date_time_internal PROPERTIES FOLDER external/boost)
ENDIF(FLYWAVE_ENABLE_SOLUTION_FOLDERS)

add_library(boost_program_options_internal STATIC
boost_1_67_0/libs/program_options/src/cmdline.cpp
boost_1_67_0/libs/program_options/src/config_file.cpp
boost_1_67_0/libs/program_options/src/convert.cpp
boost_1_67_0/libs/program_options/src/options_description.cpp
boost_1_67_0/libs/program_options/src/parsers.cpp
boost_1_67_0/libs/program_options/src/positional_options.cpp
boost_1_67_0/libs/program_options/src/split.cpp
boost_1_67_0/libs/program_options/src/utf8_codecvt_facet.cpp
boost_1_67_0/libs/program_options/src/value_semantic.cpp
boost_1_67_0/libs/program_options/src/variables_map.cpp
boost_1_67_0/libs/program_options/src/winmain.cpp)

SET_TARGET_PROPERTIES(boost_program_options_internal PROPERTIES
ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}
ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR})
SET_TARGET_PROPERTIES(boost_program_options_internal PROPERTIES 
LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}
LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR})
SET_TARGET_PROPERTIES(boost_program_options_internal PROPERTIES
RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}
RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR})

IF(FLYWAVE_ENABLE_SOLUTION_FOLDERS)
  SET_TARGET_PROPERTIES(boost_program_options_internal PROPERTIES FOLDER external/boost)
ENDIF(FLYWAVE_ENABLE_SOLUTION_FOLDERS)

add_library(boost_filesystem_internal STATIC
boost_1_67_0/libs/filesystem/src/codecvt_error_category.cpp
boost_1_67_0/libs/filesystem/src/operations.cpp
boost_1_67_0/libs/filesystem/src/path.cpp
boost_1_67_0/libs/filesystem/src/path_traits.cpp
boost_1_67_0/libs/filesystem/src/portability.cpp
boost_1_67_0/libs/filesystem/src/unique_path.cpp
boost_1_67_0/libs/filesystem/src/utf8_codecvt_facet.cpp
boost_1_67_0/libs/filesystem/src/windows_file_codecvt.cpp)

SET_TARGET_PROPERTIES(boost_filesystem_internal PROPERTIES
ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}
ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR})
SET_TARGET_PROPERTIES(boost_filesystem_internal PROPERTIES 
LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}
LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR})
SET_TARGET_PROPERTIES(boost_filesystem_internal PROPERTIES
RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}
RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR})
IF(FLYWAVE_ENABLE_SOLUTION_FOLDERS)
  SET_TARGET_PROPERTIES(boost_filesystem_internal PROPERTIES FOLDER external/boost)
ENDIF(FLYWAVE_ENABLE_SOLUTION_FOLDERS)

add_library(boost_regex_internal STATIC
  boost_1_67_0/libs/regex/src/c_regex_traits.cpp
  boost_1_67_0/libs/regex/src/cpp_regex_traits.cpp
  boost_1_67_0/libs/regex/src/cregex.cpp
  boost_1_67_0/libs/regex/src/fileiter.cpp
  boost_1_67_0/libs/regex/src/icu.cpp
  boost_1_67_0/libs/regex/src/instances.cpp
  boost_1_67_0/libs/regex/src/posix_api.cpp
  boost_1_67_0/libs/regex/src/regex.cpp
  boost_1_67_0/libs/regex/src/regex_debug.cpp
  boost_1_67_0/libs/regex/src/regex_raw_buffer.cpp
  boost_1_67_0/libs/regex/src/regex_traits_defaults.cpp
  boost_1_67_0/libs/regex/src/static_mutex.cpp
  boost_1_67_0/libs/regex/src/usinstances.cpp
  boost_1_67_0/libs/regex/src/w32_regex_traits.cpp
  boost_1_67_0/libs/regex/src/wc_regex_traits.cpp
  boost_1_67_0/libs/regex/src/wide_posix_api.cpp
  boost_1_67_0/libs/regex/src/winstances.cpp
)

SET_TARGET_PROPERTIES(boost_regex_internal PROPERTIES
ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}
ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR})
SET_TARGET_PROPERTIES(boost_regex_internal PROPERTIES 
LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}
LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR})
SET_TARGET_PROPERTIES(boost_regex_internal PROPERTIES
RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}
RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR})

IF(FLYWAVE_ENABLE_SOLUTION_FOLDERS)
  SET_TARGET_PROPERTIES(boost_regex_internal PROPERTIES FOLDER external/boost)
ENDIF(FLYWAVE_ENABLE_SOLUTION_FOLDERS)

add_library(boost_system_internal STATIC
boost_1_67_0/libs/system/src/error_code.cpp)

IF(FLYWAVE_ENABLE_SOLUTION_FOLDERS)
  SET_TARGET_PROPERTIES(boost_system_internal PROPERTIES FOLDER external/boost)
  SET_TARGET_PROPERTIES(boost_system_internal PROPERTIES
ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}
ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR})
SET_TARGET_PROPERTIES(boost_system_internal PROPERTIES 
LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}
LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR})
SET_TARGET_PROPERTIES(boost_system_internal PROPERTIES
RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR})
ENDIF(FLYWAVE_ENABLE_SOLUTION_FOLDERS)

add_library(boost_test_internal STATIC
boost_1_67_0/libs/test/src/compiler_log_formatter.cpp
boost_1_67_0/libs/test/src/cpp_main.cpp
boost_1_67_0/libs/test/src/debug.cpp
boost_1_67_0/libs/test/src/decorator.cpp
boost_1_67_0/libs/test/src/execution_monitor.cpp
boost_1_67_0/libs/test/src/framework.cpp
boost_1_67_0/libs/test/src/junit_log_formatter.cpp
boost_1_67_0/libs/test/src/plain_report_formatter.cpp
boost_1_67_0/libs/test/src/progress_monitor.cpp
boost_1_67_0/libs/test/src/results_collector.cpp
boost_1_67_0/libs/test/src/results_reporter.cpp
boost_1_67_0/libs/test/src/test_main.cpp
boost_1_67_0/libs/test/src/test_tools.cpp
boost_1_67_0/libs/test/src/test_tree.cpp
boost_1_67_0/libs/test/src/unit_test_log.cpp
boost_1_67_0/libs/test/src/unit_test_main.cpp
boost_1_67_0/libs/test/src/unit_test_monitor.cpp
boost_1_67_0/libs/test/src/unit_test_parameters.cpp
boost_1_67_0/libs/test/src/xml_log_formatter.cpp
boost_1_67_0/libs/test/src/xml_report_formatter.cpp)

IF(APPLE)
SET_TARGET_PROPERTIES(boost_test_internal PROPERTIES
ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}
ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR})
SET_TARGET_PROPERTIES(boost_test_internal PROPERTIES 
LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}
LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR})
SET_TARGET_PROPERTIES(boost_test_internal PROPERTIES
RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}
RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR})
endif()

IF(FLYWAVE_ENABLE_SOLUTION_FOLDERS)
  SET_TARGET_PROPERTIES(boost_test_internal PROPERTIES FOLDER external/boost)
ENDIF(FLYWAVE_ENABLE_SOLUTION_FOLDERS)
