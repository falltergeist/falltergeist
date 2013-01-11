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

project(falltergeist)

include(FindSDL)
IF(SDL_FOUND)
        message("SDL Found")
        include_directories(SDL_INCLUDE_DIR)
else(SDL_FOUND)
        message("SDL not found")
        return()
endif(SDL_FOUND)

set(SOURCES main.cpp
            src/Engine/Animation.cpp
            src/Engine/Animation.h
            src/Engine/CrossPlatform.cpp
            src/Engine/CrossPlatform.h
            src/Engine/Event.cpp
            src/Engine/Event.h
            src/Engine/Exception.cpp
            src/Engine/Exception.h
            src/Engine/File.cpp
            src/Engine/File.h
            src/Engine/VirtualFile.cpp
            src/Engine/VirtualFile.h
            src/Engine/Font.cpp
            src/Engine/Font.h
            src/Engine/Game.cpp
            src/Engine/Game.h
            src/Engine/InteractiveSurface.cpp
            src/Engine/InteractiveSurface.h
            src/Engine/Player.cpp
            src/Engine/Player.h
            src/Engine/ResourceManager.cpp
            src/Engine/ResourceManager.h
            src/Engine/Screen.cpp
            src/Engine/Screen.h
            src/Engine/State.cpp
            src/Engine/State.h
            src/Engine/Surface.cpp
            src/Engine/Surface.h
            src/Engine/SurfaceSet.cpp
            src/Engine/SurfaceSet.h
            src/Fallout/AafFileType.cpp
            src/Fallout/AafFileType.h
            src/Fallout/BioFileType.cpp
            src/Fallout/BioFileType.h
            src/Fallout/DatFile.cpp
            src/Fallout/DatFile.h
            src/Fallout/FonFileType.cpp
            src/Fallout/FonFileType.h
            src/Fallout/FrmFileType.cpp
            src/Fallout/FrmFileType.h
            src/Fallout/GcdFileType.cpp
            src/Fallout/GcdFileType.h
            src/Fallout/LstFileType.cpp
            src/Fallout/LstFileType.h
            src/Fallout/MsgFileType.cpp
            src/Fallout/MsgFileType.h
            src/Fallout/PalFileType.cpp
            src/Fallout/PalFileType.h
            src/States/MainMenuState.cpp
            src/States/MainMenuState.h
            src/States/NewGameState.cpp
            src/States/NewGameState.h
            src/States/PlayerEditState.cpp
            src/States/PlayerEditState.h
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

set(dir ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${dir} CACHE PATH "Build directory" FORCE)
add_executable(falltergeist ${SOURCES})
target_link_libraries(falltergeist ${SDL_LIBRARY})

