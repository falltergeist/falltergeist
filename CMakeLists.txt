#
# Copyright 2012-2013 Falltergeist Developers.
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

cmake_minimum_required(VERSION 2.8)
set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

project(falltergeist)

find_package(LIBFALLTERGEIST REQUIRED)
if(NOT LIBFALLTERGEIST_FOUND)
          message(FATAL_ERROR "libfalltergeist library not found")
endif(NOT LIBFALLTERGEIST_FOUND)
include_directories(LIBFALLTERGEIST_INCLUDE_DIR)

find_package(SDL REQUIRED)
if(NOT SDL_FOUND)
	  message(FATAL_ERROR "SDL library not found")
endif(NOT SDL_FOUND)
include_directories(${SDL_INCLUDE_DIR})

set(SOURCES main.cpp
            src/Engine/AnimatedPalette.cpp
            src/Engine/AnimatedPalette.h
            src/Engine/Animation.cpp
            src/Engine/Animation.h
            src/Engine/CrossPlatform.cpp
            src/Engine/CrossPlatform.h
            src/Engine/Event.cpp
            src/Engine/Event.h
            src/Engine/Exception.cpp
            src/Engine/Exception.h
            src/Engine/Font.cpp
            src/Engine/Font.h
            src/Engine/Game.cpp
            src/Engine/Game.h
            src/Engine/InteractiveSurface.cpp
            src/Engine/InteractiveSurface.h
            src/Engine/Location.cpp
            src/Engine/Location.h
            src/Engine/LocationCamera.cpp
            src/Engine/LocationCamera.h
            src/Engine/LocationObject.cpp
            src/Engine/LocationObject.h
            src/Engine/Map.cpp
            src/Engine/Map.h
            src/Engine/Mouse.cpp
            src/Engine/Mouse.h
            src/Engine/Player.cpp
            src/Engine/Player.h
            src/Engine/ResourceManager.cpp
            src/Engine/ResourceManager.h
            src/Engine/Renderer.cpp
            src/Engine/Renderer.h
            src/Engine/Screen.cpp
            src/Engine/Screen.h
            src/Engine/SdlRenderer.cpp
            src/Engine/SdlRenderer.h
            src/Engine/State.cpp
            src/Engine/State.h
            src/Engine/Surface.cpp
            src/Engine/Surface.h
            src/Engine/SurfaceSet.cpp
            src/Engine/SurfaceSet.h
            src/States/LocationState.cpp
            src/States/LocationState.h
            src/States/MainMenuState.cpp
            src/States/MainMenuState.h
            src/States/NewGameState.cpp
            src/States/NewGameState.h
            src/States/PlayerEditState.cpp
            src/States/PlayerEditState.h
            src/States/PlayerEditAgeState.cpp
            src/States/PlayerEditAgeState.h
            src/States/PlayerEditAlertState.cpp
            src/States/PlayerEditAlertState.h
            src/States/PlayerEditGenderState.cpp
            src/States/PlayerEditGenderState.h
            src/States/PlayerEditNameState.cpp
            src/States/PlayerEditNameState.h
            src/States/StartState.cpp
            src/States/StartState.h
            src/UI/BigCounter.cpp
            src/UI/BigCounter.h
            src/UI/FpsCounter.cpp
            src/UI/FpsCounter.h
            src/UI/HiddenMask.cpp
            src/UI/HiddenMask.h
            src/UI/ImageButton.cpp
            src/UI/ImageButton.h
            src/UI/TextArea.cpp
            src/UI/TextArea.h)

add_definitions (-std=c++11)
set(CMAKE_BUILD_TYPE Debug)
add_executable(falltergeist ${SOURCES})
target_link_libraries(falltergeist ${SDL_LIBRARY} ${LIBFALLTERGEIST_LIBRARY})

