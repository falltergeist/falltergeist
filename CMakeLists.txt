#
# Copyright 2012-2015 Falltergeist Developers.
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
set(falltergeist_VERSION  0.2.0)

option(LIBFALLTERGEIST_EMBEDDED "Use embedded libfalltergeist" ON)

include_directories(src)

if(LIBFALLTERGEIST_EMBEDDED)
    set(LIBFALLTERGEIST_LIBRARY falltergeist)
    include_directories(${CMAKE_SOURCE_DIR}/lib/libfalltergeist/src)
    set(LIBFALLTERGEIST_EMBEDDED ON CACHE BOOL "")
else()
    find_package(LIBFALLTERGEIST REQUIRED)
    include_directories(${LIBFALLTERGEIST_INCLUDE_DIRS})
endif()

find_package(SDL2 REQUIRED)
if(NOT SDL2_FOUND)
    message(FATAL_ERROR "SDL2 library not found")
endif(NOT SDL2_FOUND)
include_directories(${SDL2_INCLUDE_DIR})

find_package(SDL2_mixer REQUIRED)
if(NOT SDLMIXER_FOUND)
    message(FATAL_ERROR "SDL2_mixer library not found")
endif(NOT SDLMIXER_FOUND)
include_directories(${SDLMIXER_INCLUDE_DIR})

find_package(SDL2_image REQUIRED)
if(NOT SDLIMAGE_FOUND)
    message(FATAL_ERROR "SDL2_image library not found")
endif(NOT SDLIMAGE_FOUND)
include_directories(${SDLIMAGE_INCLUDE_DIR})

find_package(Lua 5.1 REQUIRED)
if (NOT LUA_FOUND)
    message(FATAL_ERROR "Lua library not found")
endif(NOT LUA_FOUND)
include_directories(${LUA_INCLUDE_DIR})

include_directories(${CMAKE_SOURCE_DIR}/lib/LuaBridge/Source/LuaBridge)

file(GLOB_RECURSE SOURCES  src/*.cpp)
file(GLOB_RECURSE HEADERS  src/*.h)

add_definitions (-std=c++11 -Wall)

if(LIBFALLTERGEIST_EMBEDDED)
    add_subdirectory(lib/libfalltergeist)
endif()

add_executable(falltergeist-bin main.cpp ${SOURCES} ${HEADERS})
set_target_properties(falltergeist-bin PROPERTIES OUTPUT_NAME falltergeist)
target_link_libraries(falltergeist-bin ${SDL2_LIBRARY} ${SDLMIXER_LIBRARY} ${SDLIMAGE_LIBRARY} ${LIBFALLTERGEIST_LIBRARY} ${LUA_LIBRARY})

#
# Install section
#
if(WIN32)
    install(TARGETS falltergeist-bin RUNTIME DESTINATION .)
    install(DIRECTORY data DESTINATION .)

    #MinGW runtime
    if(MINGW)
        get_filename_component(MINGW_BIN_PATH ${CMAKE_CXX_COMPILER} PATH )
        set(dep_files ${dep_files} "${MINGW_BIN_PATH}/libwinpthread-*.dll")
        set(dep_files ${dep_files} "${MINGW_BIN_PATH}/libgcc_s_*.dll")
        set(dep_files ${dep_files} "${MINGW_BIN_PATH}/libstdc++-*.dll")
    endif()

    #dependencies
    file(GLOB dep_files ${dep_files} "${CMAKE_FIND_ROOT_PATH}/bin/*.dll")
    install(FILES ${dep_files} DESTINATION .)
endif()

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    install(TARGETS falltergeist-bin RUNTIME DESTINATION bin)
    install(DIRECTORY data DESTINATION share/falltergeist)
endif()

if(APPLE)
  configure_file(package/osx/Info.plist.in package/osx/Info.plist)
  configure_file(package/osx.sh.in package/osx.sh)
  add_custom_command(
    OUTPUT Falltergeist.dmg
    COMMAND sh ./package/osx.sh
  )
  add_custom_target(dmg DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/Falltergeist.dmg)
endif()
