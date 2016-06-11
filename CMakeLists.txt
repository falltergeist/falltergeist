#
# Copyright 2012-2016 Falltergeist Developers.
#
# This file is part of Falltergeist.
#
# Falltergeist is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Falltergeist is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Falltergeist.  If not, see <http://www.gnu.org/licenses/>.
#

# It must be set before project
set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build (by default Debug)")

cmake_minimum_required(VERSION 2.8)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/modules)

project(falltergeist)
set(falltergeist_VERSION  0.3.0)

include_directories(src)

find_package(ZLIB REQUIRED)
if(NOT ZLIB_FOUND)
    message(FATAL_ERROR "zlib library not found")
endif(NOT ZLIB_FOUND)
include_directories(${ZLIB_INCLUDE_DIRS})

find_package(SDL2 REQUIRED)
if(NOT SDL2_FOUND)
    message(FATAL_ERROR "SDL2 library not found")
endif(NOT SDL2_FOUND)
include_directories(${SDL2_INCLUDE_DIR})

find_package(SDL2_mixer REQUIRED)
if(NOT SDLMIXER_FOUND)
    message(FATAL_ERROR "SDL2_mixer library not found")
endif(NOT SDLMIXER_FOUND)
include_directories(${SDL_MIXER_INCLUDE_DIR})

find_package(SDL2_image REQUIRED)
if(NOT SDLIMAGE_FOUND)
    message(FATAL_ERROR "SDL2_image library not found")
endif(NOT SDLIMAGE_FOUND)
include_directories(${SDL_IMAGE_INCLUDE_DIR})

find_package(OpenGL REQUIRED)
if(NOT OPENGL_FOUND)
    message(FATAL_ERROR "GL library not found")
endif(NOT OPENGL_FOUND)
include_directories(${OPENGL_INCLUDE_DIR})

find_package(GLEW REQUIRED)
if(NOT GLEW_FOUND)
    message(FATAL_ERROR "GLEW library not found")
endif(NOT GLEW_FOUND)
include_directories(${GLEW_INCLUDE_PATH})

find_package(GLM REQUIRED)
if(NOT GLM_FOUND)
    message(FATAL_ERROR "GLM library not found")
endif(NOT GLM_FOUND)
include_directories(${GLM_INCLUDE_DIR})

file(GLOB_RECURSE SOURCES  src/*.cpp)

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
else()
    add_definitions (-std=c++14 -Wall)
endif()

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
add_executable(falltergeist main.cpp ${SOURCES} "package/windows.rc")
else()
add_executable(falltergeist main.cpp ${SOURCES})
endif()
target_link_libraries(falltergeist ${ZLIB_LIBRARIES} ${SDL2_LIBRARY} ${SDL_MIXER_LIBRARY} ${SDL_IMAGE_LIBRARY} ${OPENGL_gl_LIBRARY} ${GLEW_LIBRARY})

include(cmake/install/windows.cmake)
include(cmake/install/linux.cmake)
include(cmake/install/apple.cmake)
