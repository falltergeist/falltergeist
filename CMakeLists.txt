# It must be set before project
set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build (by default Debug)")

cmake_minimum_required(VERSION 3.8)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/modules)

project(falltergeist)
set(FALLTERGEIST_VERSION  0.3.1)

if (USE_CLANG_TIDY)
	message(STATUS "Using clang-tidy")
	set(CMAKE_CXX_CLANG_TIDY clang-tidy)
endif()

include_directories(src)

if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
	set(USE_CONAN TRUE)
endif()

if (USE_CONAN)
	include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
	conan_basic_setup()
endif()

find_package(ZLIB REQUIRED)
if(NOT ZLIB_FOUND)
	message(FATAL_ERROR "zlib library not found")
endif(NOT ZLIB_FOUND)
include_directories(SYSTEM ${ZLIB_INCLUDE_DIRS})

find_package(SDL2 REQUIRED)
if(NOT SDL2_FOUND)
	message(FATAL_ERROR "SDL2 library not found")
endif(NOT SDL2_FOUND)
include_directories(SYSTEM ${SDL2_INCLUDE_DIR})

find_package(SDL2_mixer REQUIRED)
if(NOT SDLMIXER_FOUND)
	message(FATAL_ERROR "SDL2_mixer library not found")
endif(NOT SDLMIXER_FOUND)
include_directories(SYSTEM ${SDL_MIXER_INCLUDE_DIR})

find_package(SDL2_image REQUIRED)
if(NOT SDLIMAGE_FOUND)
	message(FATAL_ERROR "SDL2_image library not found")
endif(NOT SDLIMAGE_FOUND)
include_directories(SYSTEM ${SDL_IMAGE_INCLUDE_DIR})

find_package(OpenGL REQUIRED)
if(NOT OPENGL_FOUND)
	message(FATAL_ERROR "GL library not found")
endif(NOT OPENGL_FOUND)
include_directories(SYSTEM ${OPENGL_INCLUDE_DIR})

if (NOT USE_CONAN)
	find_package(GLEW REQUIRED)
	if(NOT GLEW_FOUND)
		message(FATAL_ERROR "GLEW library not found")
	endif(NOT GLEW_FOUND)
endif()

find_package(GLM REQUIRED)
if(NOT GLM_FOUND)
	message(FATAL_ERROR "GLM library not found")
endif(NOT GLM_FOUND)
include_directories(SYSTEM ${GLM_INCLUDE_DIR})

file(GLOB_RECURSE SOURCES  src/*.cpp)

if(MSVC)
        file(GLOB_RECURSE HEADERS  src/*.h)
        set(_additional_includes "package/windows.rc" pchheader.cpp ${HEADERS})
endif()

add_executable(${PROJECT_NAME} main.cpp ${SOURCES} ${_additional_includes})

set_target_properties(${PROJECT_NAME} PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED YES
	CXX_EXTENSIONS NO
)

if(MSVC)
	set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY LINK_FLAGS_DEBUG /NODEFAULTLIB:MSVCRT)

	set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY LINK_FLAGS_RELEASE /NODEFAULTLIB:MSVCRTD)
	set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY LINK_FLAGS_MINSIZEREL /NODEFAULTLIB:MSVCRTD)
	set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY LINK_FLAGS_RELWITHDEBINFO /NODEFAULTLIB:MSVCRTD)

	include(cmake/modules/PrecompiledHeader.cmake)
	add_precompiled_header(${PROJECT_NAME} pchheader.h FORCEINCLUDE SOURCE_CXX pchheader.cpp)

	set_property(GLOBAL PROPERTY USE_FOLDERS ON)
	source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" PREFIX "Source Files" FILES ${SOURCES})
	source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" PREFIX "Header Files" FILES ${HEADERS})

	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
else()
	add_definitions(-Wall)
endif()

if (CONAN_LIBS)
	target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})
else()
	target_link_libraries(
        ${PROJECT_NAME}
		${ZLIB_LIBRARIES}
        ${SDL2MAIN_LIBRARY}
		${SDL2_LIBRARY}
		${SDL_MIXER_LIBRARY}
		${SDL_IMAGE_LIBRARY}
		${OPENGL_gl_LIBRARY}
		GLEW::glew
	)
endif()

include(cmake/install/windows.cmake)
include(cmake/install/linux.cmake)
include(cmake/install/apple.cmake)

include(CPack)
