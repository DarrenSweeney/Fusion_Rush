CMAKE_MINIMUM_REQUIRED (VERSION 2.8.12)

PROJECT (Gamesparks) 

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/CMakeIncludes")
INCLUDE("create_source_groups_macro.cmake")

FILE(GLOB_RECURSE SOURCES
	"${PROJECT_SOURCE_DIR}/../include/*.h"
	"${PROJECT_SOURCE_DIR}/../include/*.hpp"
)

IF (CMAKE_SYSTEM_NAME STREQUAL WindowsPhone OR CMAKE_SYSTEM_NAME STREQUAL WindowsStore)

	# For WindowsPhone and WindowsStore, we pull the GameSparksAll.cpp because we can't add
	# C files to a WinRT target without getting linker errors.
	set(SOURCES ${SOURCES} "${PROJECT_SOURCE_DIR}/../src/GameSparksAll.cpp")

	# Also set /ZW for Store extension compilation.
	set_source_files_properties("${PROJECT_SOURCE_DIR}/../src/GameSparksAll.cpp" PROPERTIES COMPILE_FLAGS /ZW)

ELSE ()

	# Otherwise, we include all source files and remove the GameSparksAll.cpp to avoid redefinitions.
	FILE(GLOB_RECURSE SOURCES
		"${PROJECT_SOURCE_DIR}/../src/*.c"
		"${PROJECT_SOURCE_DIR}/../src/*.cpp"
	)
	list(REMOVE_ITEM SOURCES "${PROJECT_SOURCE_DIR}/../src/GameSparksAll.cpp")

ENDIF ()

create_source_groups( SOURCES )

INCLUDE_DIRECTORIES (
	"${PROJECT_SOURCE_DIR}/../include/"
)


OPTION(BUILD_IOS "Build iOS static lib" OFF)

IF(NO_STL_FUNCTIONAL)
	ADD_DEFINITIONS(-DSTL_FUNCTIONAL_SUPPORTED=0)
ELSE(NO_STL_FUNCTIONAL)
	ADD_DEFINITIONS(-DSTL_FUNCTIONAL_SUPPORTED=1)
ENDIF()


# C++ Dialect needs to be set to std-c++-11
# cmake -DBUILD_IOS=1 ../gsCpp -GXcode

IF (APPLE)
	SET(CMAKE_XCODE_ATTRIBUTE_GCC_VERSION "com.apple.compilers.llvm.clang.1_0")
	SET(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++11")
	SET(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
	SET(SOURCES ${SOURCES} "${PROJECT_SOURCE_DIR}/../src/GameSparks/GSIosHelper.mm")
	
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Wextra -pedantic -Wuninitialized -Werror")
ELSEIF (WIN32)
	# avoid warnings about depricated sprintf
	ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)
ENDIF()

IF (${BUILD_IOS} STREQUAL "1")
	IF (NOT DEFINED IOS_PLATFORM)
		SET(IOS_PLATFORM "OS")
	ENDIF (NOT DEFINED IOS_PLATFORM)
	SET (IOS_PLATFORM ${IOS_PLATFORM} CACHE STRING "Type of iOS Platform")

	if (${IOS_PLATFORM} STREQUAL "OS")
		SET(CMAKE_OSX_ARCHITECTURES "armv6" "armv7" "armv7s" "arm64")
		SET(CMAKE_IOS_DEVELOPER_ROOT "/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer")
		SET(CMAKE_OSX_SYSROOT ${CMAKE_IOS_DEVELOPER_ROOT}/SDKs/iPhoneOS.sdk)
		SET(CMAKE_XCODE_EFFECTIVE_PLATFORMS "-iphoneos")
	else (${IOS_PLATFORM} STREQUAL "OS")
		SET(CMAKE_OSX_ARCHITECTURES "i386" "x86_64")
		SET(CMAKE_IOS_DEVELOPER_ROOT "/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneSimulator.platform/Developer")
		SET(CMAKE_OSX_SYSROOT ${CMAKE_IOS_DEVELOPER_ROOT}/SDKs/iPhoneSimulator.sdk)
		SET(CMAKE_XCODE_EFFECTIVE_PLATFORMS "-iphonesimulator")
	ENDIF (${IOS_PLATFORM} STREQUAL "OS")
ENDIF()


# 
# GameSparks Lib
# 

ADD_LIBRARY (GameSparks ${SOURCES})
#target_compile_features(GameSparks PRIVATE cxx_long_long_type)
TARGET_INCLUDE_DIRECTORIES (
	GameSparks
	PUBLIC
	"${PROJECT_SOURCE_DIR}/../include/"
)
ADD_DEFINITIONS(-DSESSION_CERTS)

IF (APPLE)
	# set(CMAKE_XCODE_ATTRIBUTE_GCC_VERSION "com.apple.compilers.llvm.clang.1_0")
	# set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++11")
	# set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
ENDIF()

IF (BUILD_IOS)
	SET(SAMPLE_EXTRA_ARG "MACOSX_BUNDLE")
ENDIF (BUILD_IOS)


#
#	Samples
#

IF (CMAKE_SYSTEM_NAME STREQUAL WindowsPhone OR CMAKE_SYSTEM_NAME STREQUAL WindowsStore)

	# The Samples don't have a valid entry point for WindowsPhone or WindowsStore
	# So just skip them here for now.

ELSE ()

	file(GLOB SAMPLE_FILES "${PROJECT_SOURCE_DIR}/../samples/*.cpp")

	# export variable to parent scope
	set(WS_LIBS ${WS_LIBS} PARENT_SCOPE)

	foreach(SAMPLE_FILE ${SAMPLE_FILES})
		#add_test(validate_${i}, "validator", ${SAMPLE_FILE})

		get_filename_component(SAMPLE_NAME ${SAMPLE_FILE} NAME_WE)

		set(SAMPLE_EXTRA_FILES "")
		
		# add extra sources for simulator
		IF ("${BUILD_IOS}" STREQUAL "1")
			IF (${IOS_PLATFORM} STREQUAL "SIMULATOR")
				set(SAMPLE_EXTRA_FILES ${SAMPLE_EXTRA_FILES} "${PROJECT_SOURCE_DIR}/../samples/extra/UNIX2003_Fix.c")
			ENDIF(${IOS_PLATFORM} STREQUAL "SIMULATOR")
		ENDIF("${BUILD_IOS}" STREQUAL "1")


		IF (BUILD_IOS)
			set(MACOSX_BUNDLE_GUI_IDENTIFIER "com.mycompany.\${PRODUCT_NAME:identifier}")
		ENDIF(BUILD_IOS)

		ADD_EXECUTABLE (
			${SAMPLE_NAME}
			${SAMPLE_EXTRA_ARG}
			${SAMPLE_FILE}
			"${PROJECT_SOURCE_DIR}/../samples/sample_configuration.h"
			"${PROJECT_SOURCE_DIR}/../samples/extra/usleep.cpp"
			${SAMPLE_EXTRA_FILES}
			#"${PROJECT_SOURCE_DIR}/../samples/extra/UNIX2003_Fix.c"
		)
		#target_compile_features(${SAMPLE_NAME} PRIVATE cxx_auto_type)

		TARGET_LINK_LIBRARIES (${SAMPLE_NAME} GameSparks ${WS_LIBS})

		#IF (CMAKE_SYSTEM_NAME STREQUAL WindowsPhone OR CMAKE_SYSTEM_NAME STREQUAL WindowsStore)
			# don't use default libs for win rt, otherwise linker errors occur
			#set_property(TARGET ${SAMPLE_NAME} APPEND PROPERTY LINK_FLAGS_DEBUG "/nodefaultlib:vccorlibd /nodefaultlib:msvcrtd vccorlibd.lib msvcrtd.lib")
			#set_property(TARGET ${SAMPLE_NAME} APPEND PROPERTY LINK_FLAGS_RELEASE "/nodefaultlib:vccorlib /nodefaultlib:msvcrt vccorlib.lib msvcrt.lib")
		#ENDIF()

		IF (APPLE)
			TARGET_LINK_LIBRARIES (${SAMPLE_NAME} GameSparks "-framework Foundation")
		ENDIF(APPLE)

		IF (BUILD_IOS)
			set_target_properties(${SAMPLE_NAME} PROPERTIES XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "iPhone Developer")

		    if(DEFINED ENV{DEVELOPMENT_TEAM})
		        set_target_properties(${SAMPLE_NAME} PROPERTIES XCODE_ATTRIBUTE_DEVELOPMENT_TEAM "$ENV{DEVELOPMENT_TEAM}")
		    else()
		        set_target_properties(${SAMPLE_NAME} PROPERTIES XCODE_ATTRIBUTE_DEVELOPMENT_TEAM "7TFM6B4A93") # EJ6B39LVZL
		    endif()

		ENDIF(BUILD_IOS)
	endforeach()
ENDIF()

