# REQUIREMENTS: this script needs CMake 2.8 or higher. Downloads are available at http://www.cmake.org

# How to build OCE using CMake under Unix (Linux, Darwin etc.)?
# 1. Copy this file, as-is, to the top-level OCE folder
# 2. Make a build directory somewhere outside the OCE source tree
# 3. cmake "relative/path/to/OCE"
# 4. make
# 5. make install (or sudo make install)

# How to build OCE using CMake under Windows (Linux, Darwin etc.)?
# 1. Copy this file, as-is, to the top-level folder
# 2. Launch the cmake-gui, and select the top-level folder
# 3. You can choose whatever you want as an install directory
# 4. Click 'Configure'
# 5. Choose your generator
# 6. When configure is achived, you can change the variable with a red background
# 7. Click 'Generate'
# 8. From your IDE, open the generated makefile and run the compilation.

project(OCE)

set(OCE_VERSION_MAJOR 0)
set(OCE_VERSION_MINOR 18)
# OCE_VERSION_PATCH is used for bugfixes releases only
# (uncomment following line)
set(OCE_VERSION_PATCH 3)
#  Empty for official releases, set to -dev, -rc1, etc for development releases
set(OCE_VERSION_DEVEL)

# bugfix release: add ${OCE_VERSION_PATCH} to OCE_VERSION
set(OCE_VERSION ${OCE_VERSION_MAJOR}.${OCE_VERSION_MINOR}${OCE_VERSION_DEVEL})

set(OCE_ABI_SOVERSION 11)
set(OCE_ABI_VERSION ${OCE_ABI_SOVERSION}.0.0)

# Set the minimum version of cmake required to 2.6
cmake_minimum_required( VERSION 2.6 )

# Policy CMP0043 introduced in cmake version 3.0 IGNORES the use of COMPILE_DEFINITIONS suffixed variables, e.g. COMPILE_DEFINITIONS_DEBUG
# Set to OLD behavior until minimum cmake version >= 2.8.10 (version that COMPILE_DEFINITIONS can be set by generator expressions instead)
if (POLICY CMP0043)
	cmake_policy(SET CMP0043 OLD)
endif (POLICY CMP0043)
# Policy CMP0042 introduced in cmake version 3.0 enables the use of @rpath in an install name via MACOSX_RPATH by default
# Set to OLD behavior so that all versions use the same behavior, or until minimum cmake version >= 2.8.12 (version where @rpath is available)
if (POLICY CMP0042)
	cmake_policy(SET CMP0042 OLD)
endif (POLICY CMP0042)

# Define helper macro option_with_default
macro( option_with_default OPTION_NAME OPTION_STRING OPTION_DEFAULT )
	if( NOT DEFINED ${OPTION_NAME} )
		set( ${OPTION_NAME} ${OPTION_DEFAULT} )
	endif( NOT DEFINED ${OPTION_NAME} )
	option( ${OPTION_NAME} "${OPTION_STRING}" ${${OPTION_NAME}} )
endmacro( option_with_default OPTION_NAME OPTION_STRING OPTION_DEFAULT )

############################
# Check 32/64 bit platform #
############################
if (${CMAKE_SIZEOF_VOID_P} MATCHES "8") # It is 64bit, otherwise 32 bit systems match 4
	add_definitions(-D_OCC64)
	set(BIT 64)
else (${CMAKE_SIZEOF_VOID_P} MATCHES "8")
	set(BIT 32)
endif(${CMAKE_SIZEOF_VOID_P} MATCHES "8")

message(STATUS "Build ${BIT}bit")

if(NOT CMAKE_CONFIGURATION_TYPES)
	if(CMAKE_BUILD_TYPE STREQUAL "")
		set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the build type." FORCE)
		set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Release" "Debug" "RelWithDebInfo" "MinSizeRel")
	endif(CMAKE_BUILD_TYPE STREQUAL "")
endif(NOT CMAKE_CONFIGURATION_TYPES)

if(CMAKE_BUILD_TOOL STREQUAL "nmake")
	set(NMAKE TRUE)
endif(CMAKE_BUILD_TOOL STREQUAL "nmake")

if(MSVC)
	option_with_default( OCE_INSTALL_PDB_FILES "Install PDB files (debug informations)" ON )
	option_with_default( OCE_MULTITHREADED_BUILD "Multithreaded build (/MP Option)" ON )
endif(MSVC)

if(MINGW)
	option_with_default( OCE_INSTALL_PRIVATE_SAMEDIR "Install private DLLs in the same binary directory" OFF )
endif(MINGW)

INCLUDE_DIRECTORIES(BEFORE 
    "${CMAKE_CURRENT_SOURCE_DIR}/../freetype2/include/"
    "${CMAKE_CURRENT_SOURCE_DIR}/../freetype2/src/include/"
)

############################
# Library name definitions #
############################

if(MSVC)
	set( OCE_LIBRARY_PREFIX "" )
	set( CMAKE_DEBUG_POSTFIX "d" )
else(MSVC)
	set( OCE_LIBRARY_PREFIX "lib" )
endif(MSVC)


if(APPLE)
	if(OCE_NO_LIBRARY_VERSION)
		set( OCE_LIBRARY_EXTENSION ${CMAKE_SHARED_LIBRARY_SUFFIX} )
	else(OCE_NO_LIBRARY_VERSION)
		set( OCE_LIBRARY_EXTENSION ".${OCE_ABI_SOVERSION}${CMAKE_SHARED_LIBRARY_SUFFIX}" )
	endif(OCE_NO_LIBRARY_VERSION)
elseif(WIN32)
	# Don't encode library versions on Windows systems
	set( OCE_LIBRARY_EXTENSION ${CMAKE_SHARED_LIBRARY_SUFFIX} )
else()
	if(OCE_NO_LIBRARY_VERSION)
		set( OCE_LIBRARY_EXTENSION ${CMAKE_SHARED_LIBRARY_SUFFIX} )
	else(OCE_NO_LIBRARY_VERSION)
		set( OCE_LIBRARY_EXTENSION "${CMAKE_SHARED_LIBRARY_SUFFIX}.${OCE_ABI_SOVERSION}" )
	endif(OCE_NO_LIBRARY_VERSION)
endif()

if(BORLAND)
	option_with_default( OCE_INSTALL_TDS_FILES "Instal TDS files (debug informations)" ON )
endif(BORLAND)

if(WIN32)
	option_with_default( OCE_AUTOINSTALL_DEPENDENT_LIBS "Autoinstall dependent DLLs" ON )
	mark_as_advanced(OCE_AUTOINSTALL_DEPENDENT_LIBS)
endif()

if ((MSVC AND NOT NMAKE) OR CMAKE_COMPILER_IS_GNUCXX)
	set(OCE_COMPILER_SUPPORTS_PCH TRUE)
	if(MSVC)
		option_with_default( OCE_USE_PCH "Use Precompiled Headers" ON )
	else()
		option_with_default( OCE_USE_PCH "Use Precompiled Headers" OFF )
	endif()
	mark_as_advanced(OCE_USE_PCH)
endif((MSVC AND NOT NMAKE) OR CMAKE_COMPILER_IS_GNUCXX)

option_with_default( OCE_BUILD_SHARED_LIB "Build shared OCE libs" OFF )
if(APPLE)
	option_with_default( OCE_OSX_USE_COCOA "Use native OSX Cocoa backend" ON )
endif(APPLE)
if(NOT MSVC AND NOT OCE_OSX_USE_COCOA)
	option_with_default( OCE_DISABLE_X11 "Disable components requiring X11 support" OFF )
	if(NOT APPLE AND NOT WIN32)
		mark_as_advanced(OCE_DISABLE_X11)
	endif(NOT APPLE AND NOT WIN32)
endif(NOT MSVC AND NOT OCE_OSX_USE_COCOA)
option_with_default( OCE_MODEL "Build model components" ON )
option_with_default( OCE_OCAF "Build application framework" ON )
option_with_default( OCE_DATAEXCHANGE "Build data exchange" ON )
option_with_default( OCE_DRAW "Build test harness \(DRAW\)" OFF )
option_with_default( OCE_VISUALISATION "Build visualisation component" OFF )
option_with_default( OCE_WITH_GL2PS "Build with GL2PS" OFF )
option_with_default( OCE_WITH_FREEIMAGE "Build with FreeImage" OFF )
option_with_default( OCE_WITH_VTK "Build with VTK" OFF )
option_with_default( OCE_DISABLE_TKSERVICE_FONT "Disable TKService Font (only without Visualization)" OFF )
mark_as_advanced(OCE_DISABLE_TKSERVICE_FONT)
if(NOT WIN32)
  option_with_default( OCE_BUILD_TKERNEL_WITH_INSTALL_RPATH "Build TKernel with install RPATH" ON )
  mark_as_advanced(OCE_BUILD_TKERNEL_WITH_INSTALL_RPATH)
endif()
option_with_default( OCE_EXTRA_WARNINGS "Enable Maximum Warnings Level" OFF )
mark_as_advanced(OCE_EXTRA_WARNINGS)
if( NOT "${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" LESS 2.8 )
	option_with_default( OCE_TESTING "Enable unittesting framework" OFF )
endif( NOT "${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" LESS 2.8 )
option_with_default( OCE_ADD_HEADERS "Add headers to project files" OFF )
mark_as_advanced(OCE_ADD_HEADERS)
if (NOT WIN32)
	option_with_default( OCE_RPATH_FILTER_SYSTEM_PATHS "Filter out system paths from RPATH" ON )
	mark_as_advanced(OCE_RPATH_FILTER_SYSTEM_PATHS)
endif (NOT WIN32)
# When building OCE as part of another application, it may be useful to copy
# header files in a temporary location so that dependent applications can be built
option_with_default( OCE_COPY_HEADERS_BUILD "Copy header files when building OCE" OFF )

option_with_default( OCE_USE_TCL_TEST_FRAMEWORK "Add occt-tests target" OFF )

#
# By default, OSX uses X11 OpenGl implementation
#
if (APPLE)
	if (NOT OCE_OSX_USE_COCOA)
		set(MACOSX_USE_GLX TRUE)
	endif(NOT OCE_OSX_USE_COCOA)
endif(APPLE)
# The default for the OCCT_DEBUG define is ON for all the platforms , in debug mode.
# In MSVC it is not desirable to have it ON by default, since users must
# compile/use the OCE debug libraries to build it's own programs in DEBUG mode.
# OCCT_DEBUG should be enabled by developers only, in this case
if ((MSVC OR BORLAND) AND CMAKE_CONFIGURATION_TYPES)
	set (DEB_DEFAULT "OFF")
else ()
	set (DEB_DEFAULT "ON")
endif ((MSVC OR BORLAND) AND CMAKE_CONFIGURATION_TYPES)

option_with_default( OCE_ENABLE_DEB_FLAG "Enables OCCT_DEBUG define in debug configuration" ${DEB_DEFAULT} )
mark_as_advanced(OCE_ENABLE_DEB_FLAG)

if(NOT MSVC)
	option_with_default( OCE_COVERAGE "Build with coverage testing" OFF )
	mark_as_advanced(OCE_COVERAGE)
	if(OCE_COVERAGE)
		set( CMAKE_BUILD_TYPE "Debug" CACHE INTERNAL "Build type, immutable" FORCE )
	endif(OCE_COVERAGE)
endif(NOT MSVC)

set( OCE_MULTITHREAD_LIBRARY "NONE" CACHE STRING "(values are: NONE TBB OPENMP)" )

option( OCE_MULTITHREAD_LIBRARY "Multithread library" ${OCE_MULTITHREAD_LIBRARY} )

if( NOT DEFINED OCE_INSTALL_PREFIX )
	if( WIN32 )
		set(OCE_INSTALL_PREFIX
			"c:/OCE-${OCE_VERSION}")
	else( WIN32 )
		set(OCE_INSTALL_PREFIX
			"/usr/local")
	endif( WIN32 )
endif( NOT DEFINED OCE_INSTALL_PREFIX )

set( OCE_INSTALL_PREFIX ${OCE_INSTALL_PREFIX} CACHE
	PATH "Install prefix prepended to target to create install location" )
set( CMAKE_INSTALL_PREFIX "${OCE_INSTALL_PREFIX}" CACHE INTERNAL "Prefix
	prepended to install directories if target destination is not absolute,
	immutable" FORCE )

set( OCE_LIBRARY_TYPE STATIC )
set( OCE_BUILD_STATIC_LIB TRUE )

# MSVC specific options
if(MSVC_IDE)
	if (NOT DEFINED OCE_USE_MSVC_EXPRESS )
		set (OCE_USE_MSVC_EXPRESS OFF)
	endif (NOT DEFINED OCE_USE_MSVC_EXPRESS)
	option( OCE_USE_MSVC_EXPRESS "Use a Visual C++ express IDE"
		${OCE_USE_MSVC_EXPRESS} )

	if(NOT OCE_USE_MSVC_EXPRESS)
		#Use solution folders.
		set_property(GLOBAL PROPERTY USE_FOLDERS ON)
		set(USE_SOLUTION_FOLDERS TRUE)
	else( NOT OCE_USE_MSVC_EXPRESS)
		set_property(GLOBAL PROPERTY USE_FOLDERS OFF)
	endif( NOT OCE_USE_MSVC_EXPRESS)

	option( OCE_USE_STATIC_MSVC_RUNTIME "Use static version of the MSVC run-time library" OFF )
	mark_as_advanced( OCE_USE_STATIC_MSVC_RUNTIME )
endif(MSVC_IDE)

set_directory_properties(PROPERTIES COMPILE_DEFINITIONS_RELEASE NDEBUG)
set_directory_properties(PROPERTIES COMPILE_DEFINITIONS_MINSIZEREL NDEBUG)
set_directory_properties(PROPERTIES COMPILE_DEFINITIONS_RELWITHDEBINFO  NDEBUG)

if(OCE_ENABLE_DEB_FLAG)
	set_directory_properties(PROPERTIES COMPILE_DEFINITIONS_DEBUG "OCCT_DEBUG=1;_DEBUG")
else ()
	set_directory_properties(PROPERTIES COMPILE_DEFINITIONS_DEBUG "_DEBUG")
endif (OCE_ENABLE_DEB_FLAG)

if(OCE_MULTITHREAD_LIBRARY STREQUAL "NONE")
    add_definitions(-DIGNORE_NO_ATOMICS)
endif (OCE_MULTITHREAD_LIBRARY STREQUAL "NONE")

#  Make OCE version visible to OCC_VERSION_STRING_EXT
set(OCC_VERSION_DEVELOPMENT oce-${OCE_VERSION})

#
# Check components dependencies
#
set(OCE_FOUNDATION TRUE)
if(OCE_OCAF OR OCE_DATAEXCHANGE OR OCE_VISUALISATION OR OCE_DRAW)
	set(OCE_VISU_DEP TRUE)
else(OCE_OCAF OR OCE_DATAEXCHANGE OR OCE_VISUALISATION OR OCE_DRAW)
	set(OCE_VISU_DEP FALSE)
endif(OCE_OCAF OR OCE_DATAEXCHANGE OR OCE_VISUALISATION OR OCE_DRAW)
if(OCE_DISABLE_X11)
	set(OCE_VISU_DEP FALSE)
endif(OCE_DISABLE_X11)
if(OCE_DISABLE_X11 OR OCE_DISABLE_TKSERVICE_FONT)
	set(OCE_DRAW OFF CACHE BOOL "Build DRAWEXE" FORCE)
	set(OCE_VISUALISATION OFF CACHE BOOL "Build visualisation component" FORCE)
endif(OCE_DISABLE_X11 OR OCE_DISABLE_TKSERVICE_FONT)
if(OCE_DISABLE_TKSERVICE_FONT)
	# AIS_Dimension.cxx uses this flag to remove font-dependent code
	add_definitions(-DOCE_DISABLE_TKSERVICE_FONT)
endif(OCE_DISABLE_TKSERVICE_FONT)

if(NOT OCE_BUILD_SHARED_LIB AND OCE_DRAW)
	set(OCE_DRAW OFF CACHE BOOL "Build DRAWEXE" FORCE)
	message("Warning : DRAW disabled when statically linking")
endif(NOT OCE_BUILD_SHARED_LIB AND OCE_DRAW)

if(OCE_DRAW AND NOT OCE_DATAEXCHANGE)
	set(OCE_DATAEXCHANGE ON CACHE BOOL "Build data exchange" FORCE)
endif(OCE_DRAW AND NOT OCE_DATAEXCHANGE)
if(OCE_DATAEXCHANGE AND NOT OCE_OCAF)
	set(OCE_OCAF ON CACHE BOOL "Build application framework" FORCE)
endif(OCE_DATAEXCHANGE AND NOT OCE_OCAF)
if(OCE_OCAF AND NOT OCE_MODEL)
	set(OCE_MODEL ON CACHE BOOL "Build model components" FORCE)
endif(OCE_OCAF AND NOT OCE_MODEL)
if(OCE_VISUALISATION AND NOT OCE_MODEL)
	set(OCE_MODEL ON CACHE BOOL "Build model components" FORCE)
endif(OCE_VISUALISATION AND NOT OCE_MODEL)
if(OCE_DRAW AND NOT OCE_VISUALISATION)
	set(OCE_VISUALISATION ON CACHE BOOL "Build visualisation component" FORCE)
endif(OCE_DRAW AND NOT OCE_VISUALISATION)

# oce-win-bundle handling for MSVC and MINGW
if(MSVC OR MINGW)
  if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/oce-win-bundle/oce-bundle-root.empty")
      MESSAGE("Using oce-win-bundle checkout")
      option_with_default( OCE_USE_BUNDLE "Use OCE Windows Bundle that has been built and installed" ON )

      if(OCE_USE_BUNDLE)
          ADD_SUBDIRECTORY(oce-win-bundle)
          SET(OCE_SKIP_FIND_LIBRARIES TRUE)
      ENDIF()
  endif()
endif(MSVC OR MINGW)

set(INSTALL_STDRESOURCE_FILES)
set(INSTALL_RESOURCE_FILES)
file(GLOB OS_TCL_SCRIPTS RELATIVE ${OCE_SOURCE_DIR} src/OS/*.tcl)
set(INSTALL_RESOURCE_FILES ${INSTALL_RESOURCE_FILES}
	${OS_TCL_SCRIPTS}
	src/UnitsAPI/Lexi_Expr.dat
	src/UnitsAPI/Units.dat )
set(INSTALL_STDRESOURCE_FILES ${INSTALL_STDRESOURCE_FILES}
	src/UnitsAPI/CurrentUnits
	src/UnitsAPI/MDTVBaseUnits
	src/UnitsAPI/MDTVCurrentUnits )

find_package(Threads)

if(OCE_DATAEXCHANGE)
	set(INSTALL_RESOURCE_FILES ${INSTALL_RESOURCE_FILES}
		src/SHMessage/SHAPE.fr
		src/SHMessage/SHAPE.us
		src/XSMessage/IGES.fr
		src/XSMessage/IGES.us
		src/XSMessage/XSTEP.fr
		src/XSMessage/XSTEP.us
		src/XSTEPResource/IGES
		src/XSTEPResource/STEP)
endif(OCE_DATAEXCHANGE)

if(OCE_VISUALISATION)
	set(INSTALL_RESOURCE_FILES ${INSTALL_RESOURCE_FILES}
		src/Shaders/Declarations.glsl
		src/Shaders/DeclarationsImpl.glsl
		src/Shaders/FILES
		src/Shaders/PhongShading.fs
		src/Shaders/PhongShading.vs
		src/Shaders/RaytraceBase.fs
		src/Shaders/RaytraceBase.vs
		src/Shaders/RaytraceRender.fs
		src/Shaders/RaytraceSmooth.fs)
endif(OCE_VISUALISATION)

if(OCE_DRAW)
	if (APPLE AND NOT OCE_OSX_USE_COCOA)
		# under OSX-X11, should use a X11 based TCL/TK, for instance fink's implementation
		set(FINK_INSTALL_PATH /sw)
		mark_as_advanced(FINK_INSTALL_PATH)
		set(TCL_LIBRARY ${FINK_INSTALL_PATH}/lib/libtcl.dylib)
		set(TCL_INCLUDE_PATH ${FINK_INSTALL_PATH}/include)
		set(TCL_TCLSH ${FINK_INSTALL_PATH}/bin/tclsh)
		set(TK_LIBRARY ${FINK_INSTALL_PATH}/lib/libtk.dylib)
		set(TK_INCLUDE_PATH ${FINK_INSTALL_PATH}/include)
		set(TK_WISH ${FINK_INSTALL_PATH}/bin/wish)
		mark_as_advanced(TCL_INCLUDE_PATH TK_INCLUDE_PATH TCL_LIBRARY TK_LIBRARY)
	else(APPLE AND NOT OCE_OSX_USE_COCOA)
		find_package(TCL REQUIRED)
	endif(APPLE AND NOT OCE_OSX_USE_COCOA)
	message(STATUS "TCL LIB: ${TCL_LIBRARY}")
	message(STATUS "TK LIB: ${TK_LIBRARY}")
	file(GLOB DRAWRESOURCES_TCL_FILES RELATIVE ${OCE_SOURCE_DIR} src/DrawResources/*.tcl)
	set(INSTALL_RESOURCE_FILES ${INSTALL_RESOURCE_FILES}
		${DRAWRESOURCES_TCL_FILES}
		src/DrawResources/DrawDefault
		src/DrawResources/DrawPlugin
		src/DrawResources/lamp.ico
		src/TObj/TObj.msg )
endif(OCE_DRAW)

include_directories(${CMAKE_CURRENT_BINARY_DIR}/build_inc
	${CMAKE_CURRENT_SOURCE_DIR}/inc)

if(OCE_COPY_HEADERS_BUILD)
	include_directories(${CMAKE_CURRENT_BINARY_DIR}/include)
endif(OCE_COPY_HEADERS_BUILD)

###################################
# Architecture-specific libraries #
###################################
if(WIN32)
	set(LM)
	set(CSF_gdi32_LIB gdi32)
	set(CSF_advapi32_LIB advapi32)
	set(CSF_user32_LIB user32)
	set(CSF_kernel32_LIB kernel32)
	set(CSF_SOCKETLibs_LIB ws2_32)
	set(CSF_wsock32_LIB ws2_32)
	set(CSF_psapi_LIB psapi)
else(WIN32)
	set(LM "-lm")
	set(WIN32_LIBS "")
	set(CSF_gdi32_LIB "")
	set(CSF_advapi32_LIB "")
	set(CSF_user32_LIB "")
	set(CSF_kernel32_LIB "")
	set(CSF_SOCKETLibs_LIB "")
	set(CSF_wsock32_LIB "")
	set(CSF_psapi_LIB "")
endif(WIN32)

###################################################
# Check required headers, functions and libraries #
###################################################
if (NOT WIN32)
	# Check headers
	# I think these should all be check cxx headers, as I think there is no c
	# compilation anywhere in OCE
	include(CheckIncludeFile)
	check_include_file(strings.h HAVE_STRINGS_H)
	check_include_file(xlocale.h HAVE_XLOCALE_H)
	include(CheckIncludeFileCXX)
	check_include_file_cxx(mm_malloc.h HAVE_MM_MALLOC_H)
	check_include_file_cxx(atomic.h OCE_HAVE_ATOMIC_H)
	# Check library functions
	include(CheckFunctionExists)
	check_function_exists(localtime_r HAVE_LOCALTIME_R)
	check_function_exists(clock_gettime HAVE_CLOCK_GETTIME)
	check_function_exists(posix_memalign HAVE_POSIX_MEMALIGN)
	include(TestBigEndian)
	test_big_endian(WORDS_BIGENDIAN)

# TODO: check all headers/functions/libraries that are checked in configure.ac original OCC script
endif(NOT WIN32)

#######################################################
# Check compiler version - Determine Borland compiler #
#######################################################
if(BORLAND AND NOT BORLAND_VERSION)
	if(EXISTS ${CMAKE_CXX_COMPILER})
		execute_process(
			COMMAND ${CMAKE_CXX_COMPILER}  /?
			OUTPUT_VARIABLE _output
			ERROR_QUIET
		)

		string(REGEX MATCH "Embarcadero C[+][+] [0-9]+.[0-9]+"
			_borland_version "${_output}")

		if(_borland_version)
			string(REGEX MATCHALL "[0-9]+" _borland_version_list "${_borland_version}")
			list(GET _borland_version_list 0 _borland_major)
			list(GET _borland_version_list 1 _borland_minor)
		else()
			string(REGEX MATCH "Borland C[+][+] [0-9]+].[0-9]+"
				_borland_version "${_output}")

			if(_borland_version)
				string(REGEX MATCHALL "[0-9]+" _borland_version_list "${_borland_version}")
				list(GET _borland_version_list 0 _borland_major)
				list(GET _borland_version_list 1 _borland_minor)
			endif()
		endif()

		# XE2 compiler?
		if("v${_borland_major}.${_borland_minor}" STREQUAL "v6.41")
			set(BORLAND_VERSION "bcc32 v6.41 (RS XE2)")
			set(BORLAND_VERSION_RS_XE2 1)
		# XE compiler?
		elseif("v${_borland_major}.${_borland_minor}" STREQUAL "v6.30")
			set(BORLAND_VERSION "bcc32 v6.30 (RS XE)")
			set(BORLAND_VERSION_RS_XE 1)
		# 2010 compiler?
		elseif("v${_borland_major}.${_borland_minor}" STREQUAL "v6.20")
			set(BORLAND_VERSION "bcc32 v6.20 (RS 2010)")
			set(BORLAND_VERSION_RS_2010 1)
		# TODO: 2009 compiler?
		# TODO: 2007 compiler?
		# 2006 compiler?
		elseif("v${_borland_major}.${_borland_minor}" STREQUAL "v5.82")
			set(BORLAND_VERSION "bcc32 v5.82 (BDS 2006)")
			set(BORLAND_VERSION_BDS_2006 1)
		#TODO: Older compilers?
		else()
			set(BORLAND_VERSION "Unknown")
		endif()

		unset(_output)
		unset(_borland_version)
		unset(_borland_major)
		unset(_borland_minor)
	endif()
endif()

#######################################################
# Check platforms - Define specific compilation flags #
#######################################################
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	set(CLANG TRUE)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
	set(INTEL TRUE)
endif()

if(UNIX)
	if(APPLE)
		######### MacOSX ###########
		message(STATUS "MacOSX platform detected")
		set(PLATFORM Darwin)
	else(APPLE)
		######### Unix/Linux ###########
		message(STATUS "Unix/Linux platform detected")
		set(PLATFORM Unix)
		if(INTEL)
			# Disable meaningless remarks
			# remark #383 given when initializing from a literal, e.g. abc("123")
			# remark #522 given when a function is defined inline but prototype is not
			# remark #858 given when a type qualifier is applied to a function return type
			# remark #981 "operands are evaluated in unspecified order", e.g. a = b() + c()
			add_definitions("-diag-disable 383,522,858,981")
		endif(INTEL)
	endif(APPLE)
	add_definitions(-DHAVE_CONFIG_H -DCSFDB -DOCC_CONVERT_SIGNALS)
else(UNIX)
	if(WIN32)
		######### Windows ###########
		message(STATUS "Windows system detected")
		add_definitions(-DWNT -DWIN32 -D_WINDOWS -DCSFDB -DHAVE_CONFIG_H )
		######### Borland ###########
		if(BORLAND)
			message(STATUS "Borland compiler detected: ${BORLAND_VERSION}")
		endif(BORLAND)
		set(PLATFORM win)
	else(WIN32)
		message(STATUS "Unknown platform")
	endif(WIN32)
endif(UNIX)
# TODO: better detection of different Unices (Linux, Solaris etc.)
# TODO: add CXX compiler flags for each platform

# Enable Extra warnings for each compiler
if( OCE_EXTRA_WARNINGS)
	if(MSVC)
		add_definitions("/W4 /wd4100 /wd4206 /wd4127")
	endif(MSVC)
	if(CMAKE_COMPILER_IS_GNUCXX)
		add_definitions("-Wall -Wextra")
	endif(CMAKE_COMPILER_IS_GNUCXX)
	if(CLANG)
		add_definitions("-Weverything")
	endif(CLANG)
	if(BORLAND)
		#TODO
	endif(BORLAND)
	if(INTEL)
		add_definitions("-Wall -Wremarks")
	endif(INTEL)
endif(OCE_EXTRA_WARNINGS)

if(OCE_MULTITHREADED_BUILD)
   if(MSVC AND NOT NMAKE) # /MP is useless in nmake
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
   endif()
endif()

#  Detect build problems with duplicate types
try_compile(CHECK_BODY_TEMPLATE ${CMAKE_BINARY_DIR}/CMakeTmpDup
	${OCE_SOURCE_DIR}/adm/cmake/config/TestDuplicateBodyTemplate.cxx
)
if (NOT CHECK_BODY_TEMPLATE)
	message(STATUS "Duplicate types found, do not define HashCode(Standard_Utf32Char)")
	set (OCE_IS_DUPLICATE_UINT32_T TRUE)
endif ()

# TODO: under win32/64, dlls and libs should not be in the same path (non MSVC)

if(MINGW)
	#MinGW Specific Flags
	message(STATUS "MinGW:")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mthreads")
	if(BIT MATCHES "64")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")
	endif(BIT MATCHES "64")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mthreads")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mthreads -Wl,--export-all-symbols")
	set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -mthreads -Wl,--export-all-symbols")
	if(OCE_MULTITHREAD_LIBRARY STREQUAL "OPENMP")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
		set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fopenmp")
		set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -fopenmp")
	endif(OCE_MULTITHREAD_LIBRARY STREQUAL "OPENMP")
	# For the file Message_MsgFile.cxx of TKernel we must additionally set the __TCollection_DLL define to resolve the needed HashCode() method
	set_source_files_properties("src/Message/Message_MsgFile.cxx" PROPERTIES COMPILE_FLAGS "-D__Message_DLL -D__TCollection_DLL")
	message(STATUS "CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS}")

	# Define high enough WIN32 version
	add_definitions("-D_WIN32_WINNT=0x0501")
endif(MINGW)

# Disable secure CRT warnings and other MSVCRT specific things; disable bool conversion warning
if (MSVC)
	add_definitions("/D_CRT_SECURE_NO_WARNINGS /D_CRT_NONSTDC_NO_WARNINGS")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4800")

	if(OCE_USE_STATIC_MSVC_RUNTIME)
		message("Warning: OCE_USE_STATIC_MSVC_RUNTIME option can lead to deployment/maintenance issues. Use it when building
		an application executable that uses OCE, not when building redistributable OCE library for others
		to use. See the related discussion at https://github.com/tpaviot/oce/pull/577.")

		foreach(flag CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE CMAKE_CXX_FLAGS_MINSIZEREL
				CMAKE_CXX_FLAGS_RELWITHDEBINFO CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE
				CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO)
			if(${flag} MATCHES "/MD")
				STRING(REGEX REPLACE "/MD" "/MT" ${flag} "${${flag}}")
			endif()
			if(${flag} MATCHES "/MDd")
				STRING(REGEX REPLACE "/MDd" "/MTd" ${flag} "${${flag}}")
			endif()
		endforeach()
	endif()
endif(MSVC)

# Libraries are installed by default in /usr/local/lib on UNIX
# based platforms and c:/OCE-VERSION/Win[32|64]/lib on windows based
# platforms

if(WIN32)
	set(_PSUFFIX "Win${BIT}/")
else(WIN32)
	set(_PSUFFIX "")
endif(WIN32)

# Binaries
if(NOT DEFINED OCE_INSTALL_BIN_DIR)
	set(OCE_INSTALL_BIN_DIR ${_PSUFFIX}bin)
endif(NOT DEFINED OCE_INSTALL_BIN_DIR)

# Libraries
if(NOT DEFINED OCE_INSTALL_LIB_DIR)
	set(OCE_INSTALL_LIB_DIR ${_PSUFFIX}lib${LIB_SUFFIX})
endif(NOT DEFINED OCE_INSTALL_LIB_DIR)

if(MSVC OR (MINGW AND OCE_INSTALL_PRIVATE_SAMEDIR))
	if(NOT DEFINED OCE_INSTALL_PACKAGE_LIB_DIR)
		set(OCE_INSTALL_PACKAGE_LIB_DIR ${OCE_INSTALL_LIB_DIR})
	endif(NOT DEFINED OCE_INSTALL_PACKAGE_LIB_DIR)
else(MSVC)
	if(NOT DEFINED OCE_INSTALL_PACKAGE_LIB_DIR)
		set(OCE_INSTALL_PACKAGE_LIB_DIR ${OCE_INSTALL_LIB_DIR}/oce-${OCE_VERSION})
	endif(NOT DEFINED OCE_INSTALL_PACKAGE_LIB_DIR)
endif()

# RPATHS
if(IS_ABSOLUTE ${OCE_INSTALL_LIB_DIR})
	set(OCE_INSTALL_LIB_DIR_RPATH ${OCE_INSTALL_LIB_DIR})
else(IS_ABSOLUTE ${OCE_INSTALL_LIB_DIR})
	set(OCE_INSTALL_LIB_DIR_RPATH ${OCE_INSTALL_PREFIX}/${OCE_INSTALL_LIB_DIR})
endif(IS_ABSOLUTE ${OCE_INSTALL_LIB_DIR})

if(IS_ABSOLUTE ${OCE_INSTALL_PACKAGE_LIB_DIR})
	set(OCE_INSTALL_PACKAGE_LIB_DIR_RPATH ${OCE_INSTALL_PACKAGE_LIB_DIR})
else(IS_ABSOLUTE ${OCE_INSTALL_PACKAGE_LIB_DIR})
	set(OCE_INSTALL_PACKAGE_LIB_DIR_RPATH ${OCE_INSTALL_PREFIX}/${OCE_INSTALL_PACKAGE_LIB_DIR})
endif(IS_ABSOLUTE ${OCE_INSTALL_PACKAGE_LIB_DIR})

# Includes
if(NOT DEFINED OCE_INSTALL_INCLUDE_DIR)
	set(OCE_INSTALL_INCLUDE_DIR include/oce)
endif(NOT DEFINED OCE_INSTALL_INCLUDE_DIR)

# Scripts
if(NOT DEFINED OCE_INSTALL_SCRIPT_DIR)
	set(OCE_INSTALL_SCRIPT_DIR ${OCE_INSTALL_PACKAGE_LIB_DIR})
endif(NOT DEFINED OCE_INSTALL_SCRIPT_DIR)

# Data
if(NOT DEFINED OCE_INSTALL_DATA_DIR)
	if(NOT MSVC)
		set(OCE_INSTALL_DATA_DIR share/oce-${OCE_VERSION})
	else ()
		set(OCE_INSTALL_DATA_DIR "share/oce")
	endif(NOT MSVC)
endif(NOT DEFINED OCE_INSTALL_DATA_DIR)
# Absolute path, written into oce-config.h
if(IS_ABSOLUTE ${OCE_INSTALL_DATA_DIR})
	set(OCE_ABSPATH_DATA_DIR ${OCE_INSTALL_DATA_DIR})
else(IS_ABSOLUTE ${OCE_INSTALL_DATA_DIR})
	set(OCE_ABSPATH_DATA_DIR ${CMAKE_INSTALL_PREFIX}/${OCE_INSTALL_DATA_DIR})
endif(IS_ABSOLUTE ${OCE_INSTALL_DATA_DIR})

# CMake
if(NOT DEFINED OCE_INSTALL_CMAKE_DATA_DIR)
	#  See http://www.cmake.org/cmake/help/cmake-2-8-docs.html#command:find_package
	#  and the definition of OCE_INSTALL_PREFIX at the beginning.
	#  CMake files are installed under INSTALL_PREFIX/INSTALL_CMAKE_DATA_DIR.
	if(WIN32)
		set(OCE_INSTALL_CMAKE_DATA_DIR cmake)
	else(WIN32)
		if(APPLE)
			set(OCE_INSTALL_CMAKE_DATA_DIR
				OCE.framework/Versions/${OCE_VERSION}/Resources)
		else(APPLE)
			set(OCE_INSTALL_CMAKE_DATA_DIR
				lib${LIB_SUFFIX}/oce-${OCE_VERSION})
		endif(APPLE)
	endif(WIN32)
endif(NOT DEFINED OCE_INSTALL_CMAKE_DATA_DIR)

# This relative path is written into OCEConfig.cmake to set OCE_INCLUDE_DIRS relative to OCEConfig.cmake
# There is no need to prepend OCE_INSTALL_PREFIX, CMake convention is to use slashes.
# The first part is required if -DOCE_INSTALL_CMAKE_DATA_DIR and -DOCE_INSTALL_INCLUDE_DIR are not both absolute paths.
if(IS_ABSOLUTE ${OCE_INSTALL_CMAKE_DATA_DIR})
	set(_OCE_INSTALL_CMAKE_DATA_DIR ${OCE_INSTALL_CMAKE_DATA_DIR})
else(IS_ABSOLUTE ${OCE_INSTALL_CMAKE_DATA_DIR})
	set(_OCE_INSTALL_CMAKE_DATA_DIR ${CMAKE_INSTALL_PREFIX}/${OCE_INSTALL_CMAKE_DATA_DIR})
endif(IS_ABSOLUTE ${OCE_INSTALL_CMAKE_DATA_DIR})
if(IS_ABSOLUTE ${OCE_INSTALL_INCLUDE_DIR})
	set(_OCE_INSTALL_INCLUDE_DIR ${OCE_INSTALL_INCLUDE_DIR})
else(IS_ABSOLUTE ${OCE_INSTALL_INCLUDE_DIR})
	set(_OCE_INSTALL_INCLUDE_DIR ${CMAKE_INSTALL_PREFIX}/${OCE_INSTALL_INCLUDE_DIR})
endif(IS_ABSOLUTE ${OCE_INSTALL_INCLUDE_DIR})
# Now the relative path can be generated
file(RELATIVE_PATH OCE_CMAKE_DATA_TO_INCLUDE_RELATIVE_DIR "${_OCE_INSTALL_CMAKE_DATA_DIR}" "${_OCE_INSTALL_INCLUDE_DIR}")

foreach(RESOURCE_FILE ${INSTALL_RESOURCE_FILES})
	get_filename_component(RESOURCE_PATH ${RESOURCE_FILE} PATH)
	install(FILES ${RESOURCE_FILE}
		DESTINATION ${OCE_INSTALL_DATA_DIR}/${RESOURCE_PATH})
endforeach(RESOURCE_FILE ${INSTALL_RESOURCE_FILES})
install(FILES ${INSTALL_STDRESOURCE_FILES}
	DESTINATION ${OCE_INSTALL_DATA_DIR}/src/StdResource)

if(WIN32)
	set(ENV_SCRIPTS
		${OCE_SOURCE_DIR}/scripts/env.bat
		${OCE_SOURCE_DIR}/scripts/msvc.bat
	)
	install(FILES ${ENV_SCRIPTS}
		DESTINATION ${OCE_INSTALL_SCRIPT_DIR})
endif(WIN32)

file(GLOB header_files ${OCE_SOURCE_DIR}/inc/*.*)

# Install each header file individually to work around a 8192 character
# argument limit on Visual Studio generators.
foreach(header ${header_files})
  install(FILES ${header}
    DESTINATION ${OCE_INSTALL_INCLUDE_DIR} COMPONENT Development
  )
endforeach()

set(OCE_INSTALL_DATA_DIR ${OCE_INSTALL_DATA_DIR})

#this is the header used to build OCE
configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/adm/cmake/config/oce_build_config.h.cmake
	${CMAKE_CURRENT_BINARY_DIR}/build_inc/oce-config.h )
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/build_inc/oce-config.h
	RENAME oce_build_config.defs
	DESTINATION ${OCE_INSTALL_INCLUDE_DIR} COMPONENT Development )

#installation paths are written into a separate file (which is not installed)
#so that only few files have to be recompiled when installation paths are modified
add_definitions(-DHAVE_OCE_PATHS_H)
configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/adm/cmake/config/oce_build_paths.h.cmake
	${CMAKE_CURRENT_BINARY_DIR}/build_inc/oce-paths.h )

#this is the header that is installed on the system
configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/adm/cmake/config/oce_install_config.h.cmake
	${CMAKE_CURRENT_BINARY_DIR}/install_inc/oce-config.h )
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/install_inc/oce-config.h
		DESTINATION ${OCE_INSTALL_INCLUDE_DIR} COMPONENT Development )

# Version information
if(NOT OCE_NO_LIBRARY_VERSION)
configure_file (${CMAKE_CURRENT_SOURCE_DIR}/adm/cmake/config/Version.rc.cmake
				${CMAKE_CURRENT_BINARY_DIR}/Version.rc)
set ( OCE_WIN32_RES_FILE ${CMAKE_CURRENT_BINARY_DIR}/Version.rc )
endif(NOT OCE_NO_LIBRARY_VERSION)

macro(process_module modulename modules_std)
	set(modules ${modules_std})
	if(NOT OCE_DISABLE_X11)
		list(APPEND modules ${ARGN})
	endif(NOT OCE_DISABLE_X11)
	foreach(module ${modules})
		if(NOT module MATCHES ".*EXE")
			list(APPEND OCE_LIBRARIES ${module})
		endif()
		set(TOOLKIT_MODULES "")
		set(TOOLKIT_DEPENDS "")
		set(TOOLKIT_INCLUDE_DIRECTORIES "")
		set(TOOLKIT_LIBS "")
		add_subdirectory( adm/cmake/${module} )

		if (USE_SOLUTION_FOLDERS)
			set_target_properties(${module} PROPERTIES FOLDER ${modulename} )
		endif(USE_SOLUTION_FOLDERS)
	endforeach(module ${modules})
endmacro(process_module modulename modules_std)

process_module( "Kernel" "TKernel;TKMath" )

# Modeling Data
if (OCE_MODEL)
	process_module( "Modeling Data" "TKG2d;TKG3d;TKGeomBase;TKBRep" )
endif (OCE_MODEL)

# Modeling Algorithms
if (OCE_MODEL)
	process_module( "Modeling Algorithms" "TKGeomAlgo;TKTopAlgo;TKPrim;TKBO;TKHLR;TKMesh;TKShHealing;TKXMesh;TKBool;TKFillet;TKFeat;TKOffset" )
endif (OCE_MODEL)

# Visualisation
if(OCE_VISU_DEP)
	process_module( "Visualization" "" "TKService;TKV3d" )
endif(OCE_VISU_DEP)
if(OCE_VISUALISATION)
	if(OCE_WITH_VTK)
		set(oce_vtk_component TKIVtk)
	endif()
	process_module( "Visualization" "" "TKOpenGl;TKMeshVS;TKNIS;TKVoxel;${oce_vtk_component}" )
endif(OCE_VISUALISATION)

# Application framework
if(OCE_OCAF)
	process_module( "OCAF" "TKCDF;PTKernel;TKLCAF;FWOSPlugin;TKPShape;TKBinL;TKXmlL;TKPLCAF;TKTObj;TKShapeSchema;TKStdLSchema" "TKCAF;TKBin;TKXml;TKPCAF;TKBinTObj;TKXmlTObj;TKStdSchema" )
endif(OCE_OCAF)

# Data exchange
if(OCE_DATAEXCHANGE)
	process_module( "Data Exchange" "TKSTL;TKXSBase;TKSTEPBase;TKIGES;TKSTEPAttr;TKSTEP209;TKSTEP" "TKVRML;TKXCAF;TKXCAFSchema;TKXmlXCAF;TKBinXCAF;TKXDEIGES;TKXDESTEP" )
endif(OCE_DATAEXCHANGE)


IF(FLYWAVE_ENABLE_SOLUTION_FOLDERS)
	SET_TARGET_PROPERTIES(TKernel PROPERTIES FOLDER external/oce)
	SET_TARGET_PROPERTIES(TKMath PROPERTIES FOLDER external/oce)
	SET_TARGET_PROPERTIES(TKG2d PROPERTIES FOLDER external/oce)
	SET_TARGET_PROPERTIES(TKG3d PROPERTIES FOLDER external/oce)
	SET_TARGET_PROPERTIES(TKGeomBase PROPERTIES FOLDER external/oce)
	SET_TARGET_PROPERTIES(TKGeomAlgo PROPERTIES FOLDER external/oce)
	SET_TARGET_PROPERTIES(TKTopAlgo PROPERTIES FOLDER external/oce)
	SET_TARGET_PROPERTIES(TKPrim PROPERTIES FOLDER external/oce)
	SET_TARGET_PROPERTIES(TKBO PROPERTIES FOLDER external/oce)
	SET_TARGET_PROPERTIES(TKHLR PROPERTIES FOLDER external/oce)
	SET_TARGET_PROPERTIES(TKMesh PROPERTIES FOLDER external/oce)
	SET_TARGET_PROPERTIES(TKShHealing PROPERTIES FOLDER external/oce)
	SET_TARGET_PROPERTIES(TKXMesh PROPERTIES FOLDER external/oce)
	SET_TARGET_PROPERTIES(TKBool PROPERTIES FOLDER external/oce)
	SET_TARGET_PROPERTIES(TKFillet PROPERTIES FOLDER external/oce)
	SET_TARGET_PROPERTIES(TKFeat PROPERTIES FOLDER external/oce)
	SET_TARGET_PROPERTIES(TKOffset PROPERTIES FOLDER external/oce)
	SET_TARGET_PROPERTIES(TKCDF PROPERTIES FOLDER external/oce)
	SET_TARGET_PROPERTIES(PTKernel PROPERTIES FOLDER external/oce)
	SET_TARGET_PROPERTIES(TKLCAF PROPERTIES FOLDER external/oce)
	SET_TARGET_PROPERTIES(FWOSPlugin PROPERTIES FOLDER external/oce)
	SET_TARGET_PROPERTIES(TKPShape PROPERTIES FOLDER external/oce)
	SET_TARGET_PROPERTIES(TKBinL PROPERTIES FOLDER external/oce)
	SET_TARGET_PROPERTIES(TKXmlL PROPERTIES FOLDER external/oce)
	SET_TARGET_PROPERTIES(TKPLCAF PROPERTIES FOLDER external/oce)
	SET_TARGET_PROPERTIES(TKTObj PROPERTIES FOLDER external/oce)
	SET_TARGET_PROPERTIES(TKShapeSchema PROPERTIES FOLDER external/oce)
	SET_TARGET_PROPERTIES(TKStdLSchema PROPERTIES FOLDER external/oce)
	SET_TARGET_PROPERTIES(TKCAF PROPERTIES FOLDER external/oce)
	SET_TARGET_PROPERTIES(TKBin PROPERTIES FOLDER external/oce)
	SET_TARGET_PROPERTIES(TKXml PROPERTIES FOLDER external/oce)
	SET_TARGET_PROPERTIES(TKPCAF PROPERTIES FOLDER external/oce)
	SET_TARGET_PROPERTIES(TKBinTObj PROPERTIES FOLDER external/oce)
	SET_TARGET_PROPERTIES(TKXmlTObj PROPERTIES FOLDER external/oce)
	SET_TARGET_PROPERTIES(TKStdSchema PROPERTIES FOLDER external/oce)
	SET_TARGET_PROPERTIES(TKSTL PROPERTIES FOLDER external/oce)
	SET_TARGET_PROPERTIES(TKXSBase PROPERTIES FOLDER external/oce)
	SET_TARGET_PROPERTIES(TKSTEPBase PROPERTIES FOLDER external/oce)
	SET_TARGET_PROPERTIES(TKIGES PROPERTIES FOLDER external/oce)
	SET_TARGET_PROPERTIES(TKSTEPAttr PROPERTIES FOLDER external/oce)
	SET_TARGET_PROPERTIES(TKSTEP209 PROPERTIES FOLDER external/oce)
	SET_TARGET_PROPERTIES(TKSTEP PROPERTIES FOLDER external/oce)
	SET_TARGET_PROPERTIES(TKVRML PROPERTIES FOLDER external/oce)
	SET_TARGET_PROPERTIES(TKXCAF PROPERTIES FOLDER external/oce)
	SET_TARGET_PROPERTIES(TKXCAFSchema PROPERTIES FOLDER external/oce)
	SET_TARGET_PROPERTIES(TKXmlXCAF PROPERTIES FOLDER external/oce)
	SET_TARGET_PROPERTIES(TKBinXCAF PROPERTIES FOLDER external/oce)
	SET_TARGET_PROPERTIES(TKXDEIGES PROPERTIES FOLDER external/oce)
	SET_TARGET_PROPERTIES(TKXDESTEP PROPERTIES FOLDER external/oce)
	SET_TARGET_PROPERTIES(TKBRep PROPERTIES FOLDER external/oce)
	SET_TARGET_PROPERTIES(TKService PROPERTIES FOLDER external/oce)
	SET_TARGET_PROPERTIES(TKV3d PROPERTIES FOLDER external/oce)
ENDIF(FLYWAVE_ENABLE_SOLUTION_FOLDERS)
