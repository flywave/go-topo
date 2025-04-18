cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0075 NEW)
project(IpOpt CXX)

# FUNNY_LAPACK_FINT

#undef HAVE_MPI_INITIALIZED - Define to 1 if you have the `MPI_Initialized' function.

option(COIN_ENABLE_READLINE "Enable the use of the readline library" OFF)

set(COIN_IPOPT_CHECKLEVEL "0" CACHE STRING "The debug sanity check level of IpOpt (0 if no test)")
set(COIN_IPOPT_VERBOSITY  "0" CACHE STRING "The debug verbosity level of IpOpt (0 if no output)")

# Compilation options
option(ENABLE_SHARED_LIBRARIES       "Build libraries as shared libraries" OFF)
option(COIN_COMPILE_STATIC           "Activate the static linking" ON)
option(COIN_COMPILE_COVERAGE         "Activate the code coverage compilation" OFF)
option(COIN_COMPILE_PROFILE          "Activate the code profiling compilation" OFF)
option(COIN_COMPILE_PROFILE_VALGRIND "Activate the code profiling compilation for valgrind" OFF)
option(COIN_COMPILE_LTO              "Activate the whole program optimization" OFF)  # GCC macOS does not support this
option(COIN_USE_FAST_CODE            "Use intensive optimization flags" ON)
option(COIN_COMPILE_WARNINGS         "Activate a set of warning options" OFF)
option(COIN_COMPILE_CXX11            "Activate C++11 compilation" ON)
option(COIN_TESTS_DISABLE_TIMEOUT    "Disable the timeout of the tests" OFF)

option(USE_PROCESSOR_EXTENSIONS      "Use sse / mmx / avx extensions during compilation" OFF)
option(COIN_ENABLE_COMPAT            "Enable libc compatibility" OFF)   # Do not compile if ON

# Set paths of source
set(COIN_DIR "${CMAKE_CURRENT_SOURCE_DIR}" CACHE PATH "The Cbc Path")

set(COIN_COVERAGE_CTEST_LABEL "SAMPLE" CACHE PATH "The label sent to ctest during coverage")

mark_as_advanced(ENABLE_SHARED_LIBRARIES
        COIN_ENABLE_READLINE
        COIN_COMPILE_STATIC
        COIN_COMPILE_COVERAGE
        COIN_COMPILE_PROFILE
        COIN_COMPILE_PROFILE_VALGRIND
        COIN_COMPILE_LTO
        COIN_USE_FAST_CODE
        COIN_COMPILE_WARNINGS
        COIN_COMPILE_CXX11
        COIN_DIR
        COIN_IPOPT_CHECKLEVEL
        COIN_IPOPT_VERBOSITY
        USE_PROCESSOR_EXTENSIONS
        COIN_COVERAGE_CTEST_LABEL)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
        ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(coin-macros)
include(GetAcInitVersion)
include(CheckCLinkerFlag)
include(GNUInstallDirs)

Enable_Testing ()

#------------------------------------------------------------
# Detect 64 bits
#------------------------------------------------------------

if (CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(HAVE_64_BIT 0)
else ()
    set(HAVE_64_BIT 1)
endif ()

# Various definitions

# Name of package
set(PACKAGE           "IpOpt")
# Define to the address where bug reports for this package should be sent.
set(PACKAGE_BUGREPORT "bugs@coin-or.org")
# Define to the full name of this package.
set(PACKAGE_NAME      "IpOpt")
# Define to the full name and version of this package.
set(PACKAGE_STRING    "IpOpt")
# Define to the one symbol short name of this package.
set(PACKAGE_TARNAME   "ipopt")

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/ipopt_binary"
            CACHE PATH "IpOpt install prefix" FORCE)
endif ()

include(CheckCCompilerFlag)
if (COIN_COMPILE_LTO)
    if (NOT CMAKE_VERSION VERSION_LESS "3.9")
        cmake_policy(SET CMP0069 NEW)
        include(CheckIPOSupported)
        check_ipo_supported()
    endif ()
endif ()

if (COIN_ENABLE_COMPAT)
    # Disable extra stdc++ symbols (@GLIBCXX_3.4.21)
    add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -include ${CMAKE_CURRENT_SOURCE_DIR}/cmake/compatibility.h")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -include ${CMAKE_CURRENT_SOURCE_DIR}/cmake/compatibility.h")
endif ()

# Desactivate some relocation types for portability
if (UNIX AND COIN_ENABLE_COMPAT)
    check_c_compiler_flag("-Wa,-mrelax-relocations=no" HAVE_RELAX_RELOC_FLAG)
    if (HAVE_RELAX_RELOC_FLAG)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wa,-mrelax-relocations=no")
    endif ()
endif ()

# Check for readline
set(COIN_HAS_READLINE "OFF")
if (COIN_ENABLE_READLINE)
    find_package(Readline)
    if (READLINE_FOUND)
        set(COIN_HAS_READLINE "ON")

        include_directories(${READLINE_INCLUDE_DIR})
    endif ()
endif ()

if (USE_PROCESSOR_EXTENSIONS)
    # Check for SSE* and AVX*
    find_package(SSE)
    if (MMX_FOUND OR
            SSE2_FOUND OR SSE3_FOUND OR SSSE3_FOUND OR SSE4_1_FOUND OR SSE4_2_FOUND OR
            AVX_FOUND OR AVX2_FOUND)
        set(CMAKE_C_FLAGS       "${CMAKE_C_FLAGS} ${SSE_COMPILER_FLAGS}")
        set(CMAKE_CXX_FLAGS     "${CMAKE_CXX_FLAGS} ${SSE_COMPILER_FLAGS}")
        set(CMAKE_Fortran_FLAGS "${CMAKE_Fortran_FLAGS} ${SSE_COMPILER_FLAGS}")
    endif ()
endif ()

#-----------------------------------------------------------------------------
# Manage compilation options
#-----------------------------------------------------------------------------

if (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated")
    set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -Wno-deprecated")

    if (NOT ENABLE_SHARED_LIBRARIES)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
        set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -fPIC")
    endif ()
    if (COIN_COMPILE_WARNINGS)
        # Try to locate unitizalized variables
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Wuninitialized ")
        set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -Wall -Wshadow -Wmissing-prototypes -Wuninitialized ")
    endif ()
    if (COIN_COMPILE_STATIC)
        if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND NOT APPLE)
            set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")

            check_c_linker_flag("-z muldef" ZFLAGDEFINED)
            if (ZFLAGDEFINED)
                set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -z muldefs")
            endif ()
        endif ()
    endif ()
    if (COIN_COMPILE_COVERAGE)
        if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
            set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -O0 --coverage")
            set(CMAKE_C_FLAGS          "${CMAKE_C_FLAGS} -O0 --coverage")
            set(CMAKE_CXX_FLAGS        "${CMAKE_CXX_FLAGS} -O0 --coverage")
        endif ()
        if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -Xclang -coverage-cfg-checksum -Xclang -coverage-no-function-names-in-data -Xclang -coverage-version='408*'")
        endif ()
    endif ()
    if (COIN_COMPILE_PROFILE)
        set(CMAKE_CXX_FLAGS        "${CMAKE_CXX_FLAGS} -pg")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")
    endif ()
    if (COIN_COMPILE_PROFILE_VALGRIND)
        set(CMAKE_CXX_FLAGS        "${CMAKE_CXX_FLAGS} -p")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -p")
    else ()
        if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND NOT APPLE)
            check_c_linker_flag("-z muldef" ZFLAGDEFINED)
            if (ZFLAGDEFINED)
                set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -z muldefs")
            endif ()
        endif ()
    endif ()
endif ()

#-----------------------------------------------------------------------------
# Manage specific VS flags
#-----------------------------------------------------------------------------

if (MSVC)
    # Avoid Warning C4530 by using the flag /EHsc
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc ")
    set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} /EHsc ")
endif ()

#-----------------------------------------------------------------------------
# Manage threads include dir under Windows
#-----------------------------------------------------------------------------

if (WIN32)
    if (NOT COIN_THREADS_INC_PATH STREQUAL "None")
        include_directories(${COIN_THREADS_INC_PATH})
    endif ()
    if (NOT COIN_THREADS_LIB_PATH STREQUAL "None")
        link_directories(${COIN_THREADS_LIB_PATH})
    endif ()
endif ()

# Check for a fortran compiler
include(CMakeDetermineFortranCompiler)
if (NOT CMAKE_Fortran_COMPILER)
    message(STATUS "WARNING: fortran compiler not found. Disabling f77/f95 bindings")
endif ()

# Define FORTRAN_INTEGER_TYPE for Ipopt.
set(FORTRAN_INTEGER_TYPE int)

#-----------------------------------------------------------------------------
# Detect name mangling convention used between Fortran and C
#-----------------------------------------------------------------------------

if (false)
    enable_language(Fortran)

    include(FortranCInterface)

    FortranCInterface_HEADER(${CMAKE_BINARY_DIR}/F77Mangle.h
            MACRO_NAMESPACE "F77_"
            SYMBOL_NAMESPACE "F77_")

    file(STRINGS ${CMAKE_BINARY_DIR}/F77Mangle.h CONTENTS REGEX "F77_GLOBAL\\(.*,.*\\) +(.*)")
    message(${CMAKE_BINARY_DIR}/F77Mangle.h)
    message(${CONTENTS})
    string(REGEX MATCH "F77_GLOBAL\\(.*,.*\\) +(.*)" RESULT ${CONTENTS})
    set(F77_FUNC         "F77_FUNC(name,NAME) ${CMAKE_MATCH_1}")
    set(COIN_LAPACK_FUNC "COIN_LAPACK_FUNC(name,NAME) ${CMAKE_MATCH_1}")
else ()
    set(F77_FUNC          "F77_FUNC(name,NAME)  name##_")
    set(F77_FUNC_         "F77_FUNC_(name,NAME) name##__")
    set(COIN_LAPACK_FUNC  "COIN_LAPACK_FUNC(name,NAME)  name##_")
    set(COIN_LAPACK_FUNC_ "COIN_LAPACK_FUNC_(name,NAME) name##__")
endif ()

set(F77_DUMMY_MAIN "" CACHE STRING "Define to dummy 'main' function (if any) required to link to the Fortran libraries.")
set(FC_DUMMY_MAIN  "" CACHE STRING "Define to dummy 'main' function (if any) required to link to the Fortran libraries.")
option(FC_DUMMY_MAIN_EQ_F77 "Define if F77 and FC dummy 'main' functions are identical." OFF)

if (FC_DUMMY_MAIN_EQ_F77)
    set(FC_DUMMY_MAIN "${F77_DUMMY_MAIN}")
endif ()

mark_as_advanced(F77_FUNC
        F77_FUNC_
        F77_DUMMY_MAIN
        FC_DUMMY_MAIN
        FC_DUMMY_MAIN_EQ_F77)

# Manage coverage via lcov automatically

if (COIN_COMPILE_COVERAGE AND NOT ((CMAKE_BUILD_TYPE STREQUAL "DEBUG") OR (CMAKE_BUILD_TYPE STREQUAL "RELWITHDEBINFO")))
    message(STATUS "Warning: to enable coverage, you must compile in DEBUG ou RELWITHDEBINFO mode")
endif ()

if (COIN_COMPILE_COVERAGE)
    if (WIN32)
        message(FATAL_ERROR "Error: code coverage analysis is only available under Linux for now.")
    endif ()

    find_program(GCOV_PATH gcov)
    find_program(LCOV_PATH lcov)
    find_program(GENHTML_PATH genhtml)

    if (NOT GCOV_PATH)
        message(FATAL_ERROR "gcov not found! Please install lcov and gcov. Aborting...")
    endif ()

    if (NOT LCOV_PATH)
        message(FATAL_ERROR "lcov not found! Please install lcov and gcov. Aborting...")
    endif ()

    if (NOT GENHTML_PATH)
        message(FATAL_ERROR "genhtml not found! Please install lcov and gcov. Aborting...")
    endif ()

    # /!\ FAILURE IF AT LEAST ONE TEST FAILS
    # Capturing lcov counters and generating report
    add_custom_target(coverage
            COMMAND ${LCOV_PATH} --directory ${CMAKE_BINARY_DIR} --zerocounters
            COMMAND ${LCOV_PATH} --capture --initial --directory ${CMAKE_BINARY_DIR} --output-file ${CMAKE_BINARY_DIR}/coverage.info
            COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_BINARY_DIR} ${CMAKE_CTEST_COMMAND} -LE "(LONG|FAIL)" -L "${COIN_COVERAGE_CTEST_LABEL}" || true
            COMMAND ${LCOV_PATH} --capture --directory ${CMAKE_BINARY_DIR} --output-file ${CMAKE_BINARY_DIR}/coverage.info
            COMMAND ${LCOV_PATH} --remove ${CMAKE_BINARY_DIR}/coverage.info "*/usr/include/*" '${CMAKE_BINARY_DIR}/Dependencies/${CMAKE_CFG_INTDIR}/*' --output-file ${CMAKE_BINARY_DIR}/coverage.info.cleaned
            COMMAND ${GENHTML_PATH} -o ${CMAKE_BINARY_DIR}/coverage ${CMAKE_BINARY_DIR}/coverage.info.cleaned
            COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/coverage.info ${CMAKE_BINARY_DIR}/coverage.info.cleaned
            VERBATIM
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMENT "Resetting code coverage counters to zero.
Processing code coverage counters and generating report.
You can zip the directory ${CMAKE_BINARY_DIR}/coverage and upload the content to a web server.")
endif ()

#
# Add uninstall-target
#

add_custom_target(uninstall
        COMMAND ${CMAKE_COMMAND} -P "${CMAKE_CURRENT_SOURCE_DIR}/cmake/uninstall.cmake")

# Directories where to find the source code

set(Ipopt_DIR ${COIN_DIR})

# End of coverage

include(CheckIncludeFileCXX)
include(CheckIncludeFile)
include(VA_COPY)

check_include_file("assert.h"    HAVE_ASSERT_H)
check_include_file("bzlib.h"     HAVE_BZLIB_H)
check_include_file("ctype.h"     HAVE_CTYPE_H)
check_include_file("dlfcn.h"     HAVE_DLFCN_H)
check_include_file("endian.h"    HAVE_ENDIAN_H)
check_include_file("float.h"     HAVE_FLOAT_H)
check_include_file("ieeefp.h"    HAVE_IEEEFP_H)
check_include_file("inttypes.h"  HAVE_INTTYPES_H)
check_include_file("math.h"      HAVE_MATH_H)
check_include_file("memory.h"    HAVE_MEMORY_H)
if (COIN_ENABLE_READLINE)
    check_include_file("readline/readline.h" HAVE_READLINE_READLINE_H)
endif ()
check_include_file("stdint.h"    HAVE_STDINT_H)
check_include_file("stdlib.h"    HAVE_STDLIB_H)
check_include_file("stdio.h"     HAVE_STDIO_H)
check_include_file("stdarg.h"    HAVE_STDARG_H)
check_include_file("stddef.h"    HAVE_STDDEF_H)
check_include_file("strings.h"   HAVE_STRINGS_H)
check_include_file("string.h"    HAVE_STRING_H)
check_include_file("sys/stat.h"  HAVE_SYS_STAT_H)
check_include_file("sys/types.h" HAVE_SYS_TYPES_H)
check_include_file("time.h"      HAVE_TIME_H)
check_include_file("unistd.h"    HAVE_UNISTD_H)
check_include_file("windows.h"   HAVE_WINDOWS_H)
check_include_file("zlib.h"      HAVE_ZLIB_H)
check_include_file_cxx("cctype"    HAVE_CCTYPE)
check_include_file_cxx("cmath"     HAVE_CMATH)
check_include_file_cxx("cieeefp"   HAVE_CIEEEFP)
check_include_file_cxx("cfloat"    HAVE_CFLOAT)
check_include_file_cxx("cinttypes" HAVE_CINTTYPES)
check_include_file_cxx("cassert"   HAVE_CASSERT)
check_include_file_cxx("cstdio"    HAVE_CSTDIO)
check_include_file_cxx("cstdlib"   HAVE_CSTDLIB)
check_include_file_cxx("cstdarg"   HAVE_CSTDARG)
check_include_file_cxx("cstddef"   HAVE_CSTDDEF)
check_include_file_cxx("cstring"   HAVE_CSTRING)
check_include_file_cxx("ctime"     HAVE_CTIME)

string(SUBSTRING ${CMAKE_SHARED_LIBRARY_SUFFIX} 1 -1 SHAREDLIBEXT)

include(CheckCXXCompilerFlag)

if (COIN_COMPILE_CXX11 AND NOT WIN32)
    # VS2013 activate C++11 by default
    check_cxx_compiler_flag(-std=c++11 HAVE_STD_CPP11_FLAG)
    if (HAVE_STD_CPP11_FLAG)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    else ()
        check_cxx_compiler_flag(-std=c++0x HAVE_STD_CPP0X_FLAG)
        if (HAVE_STD_CPP0X_FLAG)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
        endif ()
    endif ()
endif ()

check_cxx_compiler_flag(-Qunused-arguments HAVE_QUNUSED_ARGUMENTS)
if (HAVE_QUNUSED_ARGUMENTS)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Qunused-arguments")
endif ()

if (UNIX)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND NOT APPLE)
        check_cxx_compiler_flag(-Wno-unused-local-typedefs GCC_HAS_TYPEDEFS)
        if (GCC_HAS_TYPEDEFS)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-local-typedefs")
        endif ()
    endif ()

    if (NOT APPLE)
        check_cxx_compiler_flag(-Wno-narrowing GCC_HAS_NARROWING)
        if (GCC_HAS_NARROWING)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-narrowing")
            set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -Wno-narrowing")
        endif ()
    endif ()
endif ()

include(CheckTypeSize)

check_type_size("int *" SIZEOF_INT_P)

include(CheckSymbolExists)
include(CheckCXXSymbolExists)
include(CheckFunctionExists)

set(CMAKE_REQUIRED_LIBRARIES m)
check_cxx_symbol_exists(std::isfinite "cmath" COIN_C_FINITE_R)
if (COIN_C_FINITE_R)
    set(COIN_C_FINITE std::isfinite)
endif ()
if (NOT COIN_C_FINITE_R)
    set(CMAKE_REQUIRED_LIBRARIES m)
    check_symbol_exists(isfinite "math.h" COIN_C_FINITE_R)
    if (COIN_C_FINITE_R)
        set(COIN_C_FINITE isfinite)
    endif ()
endif ()
if (NOT COIN_C_FINITE_R)
    set(CMAKE_REQUIRED_LIBRARIES m)
    check_symbol_exists(_finite "math.h" COIN_C_FINITE_R)
    if (COIN_C_FINITE_R)
        set(COIN_C_FINITE _finite)
    endif ()
endif ()
if (NOT COIN_C_FINITE_R)
    set(CMAKE_REQUIRED_LIBRARIES m)
    check_symbol_exists(finite "math.h" COIN_C_FINITE_R)
    if (COIN_C_FINITE_R)
        set(COIN_C_FINITE finite)
    endif ()
endif ()

set(CMAKE_REQUIRED_LIBRARIES m)
check_cxx_symbol_exists(std::isnan "cmath" COIN_C_ISNAN_R)
if (COIN_C_ISNAN_R)
    set(COIN_C_ISNAN std::isnan)
endif ()
if (NOT COIN_C_ISNAN_R)
    set(CMAKE_REQUIRED_LIBRARIES m)
    check_symbol_exists(isnan "math.h" COIN_C_ISNAN_R)
    if (COIN_C_ISNAN_R)
        set(COIN_C_NAN isnan)
    endif ()
endif ()
if (NOT COIN_C_ISNAN_R)
    set(CMAKE_REQUIRED_LIBRARIES m)
    check_symbol_exists(_isnan "math.h" COIN_C_ISNAN_R)
    if (COIN_C_NAN_R)
        set(COIN_C_NAN _isnan)
    endif ()
endif ()
if (NOT COIN_C_ISNAN_R)
    set(CMAKE_REQUIRED_LIBRARIES m)
    check_symbol_exists(isnand "ieeefp.h" COIN_C_ISNAN_R)
    if (COIN_C_NAN_R)
        set(COIN_C_NAN isnand)
    endif ()
endif ()

check_symbol_exists(clock_gettime time.h     HAVE_CLOCK_GETTIME)
check_symbol_exists(gettimeofday  sys/time.h HAVE_GETTIMEOFDAY)

check_function_exists(dran48     HAVE_DRAND48)
check_function_exists(rand       HAVE_RAND)
check_function_exists(snprintf   HAVE_SNPRINTF)
check_function_exists(va_copy    HAVE_VA_COPY)
check_function_exists(vsnprintf  HAVE_VSNPRINTF)
check_function_exists(_snprintf  HAVE__SNPRINTF)
check_function_exists(_vsnprintf HAVE__VSNPRINTF)

if (WIN32)
    # snprintf not correctly detected under Visual Studio.
    # Hack: we just activate snprintf under Windows.
    # TO BE FIXED
    set(HAVE_STDIO_H    1)
    set(HAVE_SNPRINTF   1)
    set(HAVE__SNPRINTF  1)
    set(HAVE_VSNPRINTF  1)
    set(HAVE__VSNPRINTF 1)
    set(HAVE_VA_COPY    1)
endif ()

set(IPOPT_HAS_LAPACK 1)
set(IPOPT_HAS_HSL 1)
set(IPOPT_SINGLE 1)

if(COIN_COMPILE_CXX11)
  message(STATUS "C++11 support enabled. Assuming we have std::rand")
  set(HAVE_STD__RAND 1)
endif()

if (COIN_USE_FAST_CODE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fomit-frame-pointer ")
    set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} -fomit-frame-pointer ")

    if (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-math-errno -fp-trap=none ")
        set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} -fno-math-errno -fp-trap=none ")
    endif ()

    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffast-math -fno-math-errno -fno-trapping-math ")
        set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} -ffast-math -fno-math-errno -fno-trapping-math ")
    endif ()

endif ()

include(AC_HEADER_STDC)

add_definitions(-DHAVE_CONFIG_H)

if (("${MSVC_VERSION}" STREQUAL "1900") OR ("${MSVC_VERSION}" STREQUAL "1910"))
    add_definitions(/DHAVE_SNPRINTF /DHAVE_STRUCT_TIMESPEC)
endif ()

#
# HSL Management
#
add_definitions(-DCOINHSL_HAS_METIS)
add_subdirectory(src)
