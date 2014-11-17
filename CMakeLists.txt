#
# Copyright 2012-2014 Falltergeist Developers.
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
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/modules)

project(falltergeist)
set(falltergeist_VERSION  0.1.6)

option(LIBFALLTERGEIST_EMBEDDED "Use embedded libfalltergeist" ON)

if(LIBFALLTERGEIST_EMBEDDED)
    set(LIBFALLTERGEIST_LIBRARY falltergeist)
    include_directories(${CMAKE_SOURCE_DIR}/lib/libfalltergeist)
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

find_package(OpenGL REQUIRED)
if(NOT OPENGL_FOUND)
    message(FATAL_ERROR "OpenGL library not found")
endif(NOT OPENGL_FOUND)
include_directories(${OPENGL_INCLUDE_DIR})

configure_file(src/Engine/CrossPlatform.cpp.in src/Engine/CrossPlatform.cpp)

set(SOURCES main.cpp
    src/Engine/Audio/AudioMixer.h
    src/Engine/Audio/AudioMixer.cpp
    src/Engine/CrossPlatform.cpp
    src/Engine/CrossPlatform.h
    src/Engine/Event/Event.cpp
    src/Engine/Event/Event.h
    src/Engine/Event/EventReciever.cpp
    src/Engine/Event/EventReciever.h
    src/Engine/Event/EventHandler.cpp
    src/Engine/Event/EventHandler.h
    src/Engine/Event/EventEmitter.cpp
    src/Engine/Event/EventEmitter.h
    src/Engine/Event/KeyboardEvent.cpp
    src/Engine/Event/KeyboardEvent.h
    src/Engine/Event/MouseEvent.cpp
    src/Engine/Event/MouseEvent.h
    src/Engine/Event/StateEvent.cpp
    src/Engine/Event/StateEvent.h
    src/Engine/Exception.cpp
    src/Engine/Exception.h
    src/Engine/Font.cpp
    src/Engine/Font.h
    src/Engine/FontString.cpp
    src/Engine/FontString.h
    src/Engine/Game.cpp
    src/Engine/Game.h
    src/Engine/GameTime.cpp
    src/Engine/GameTime.h
    src/Engine/Graphics/ActiveUI.cpp
    src/Engine/Graphics/ActiveUI.h
    src/Engine/Graphics/AnimatedPalette.cpp
    src/Engine/Graphics/AnimatedPalette.h
    src/Engine/Graphics/Animation.cpp
    src/Engine/Graphics/Animation.h
    src/Engine/Graphics/AnimationFrame.cpp
    src/Engine/Graphics/AnimationFrame.h
    src/Engine/Graphics/AnimationQueue.cpp
    src/Engine/Graphics/AnimationQueue.h
    src/Engine/Graphics/OpenGLRenderer.cpp
    src/Engine/Graphics/OpenGLRenderer.h
    src/Engine/Graphics/SDLRenderer.cpp
    src/Engine/Graphics/SDLRenderer.h
    src/Engine/Graphics/Renderer.cpp
    src/Engine/Graphics/Renderer.h
    src/Engine/Graphics/Texture.cpp
    src/Engine/Graphics/Texture.h
    src/Engine/Graphics/Tile.cpp
    src/Engine/Graphics/Tile.h
    src/Engine/Graphics/TileMap.cpp
    src/Engine/Graphics/TileMap.h
    src/Engine/Graphics/UI.cpp
    src/Engine/Graphics/UI.h
    src/Engine/Input/Mouse.cpp
    src/Engine/Input/Mouse.h
    src/Engine/LocationCamera.cpp
    src/Engine/LocationCamera.h
    src/Engine/Logger.cpp
    src/Engine/Logger.h
    src/Engine/PathFinding/Hexagon.cpp
    src/Engine/PathFinding/Hexagon.h
    src/Engine/PathFinding/HexagonGrid.cpp
    src/Engine/PathFinding/HexagonGrid.h
    src/Engine/ResourceManager.cpp
    src/Engine/ResourceManager.h
    src/Engine/Settings/IniFile.cpp
    src/Engine/Settings/IniFile.h
    src/Engine/Settings/IniParser.cpp
    src/Engine/Settings/IniParser.h
    src/Engine/Settings/IniSection.cpp
    src/Engine/Settings/IniSection.h
    src/Engine/Settings/IniWriter.cpp
    src/Engine/Settings/IniWriter.h
    src/Engine/Settings/IniValue.cpp
    src/Engine/Settings/IniValue.h
    src/Engine/Settings/Settings.cpp
    src/Engine/Settings/Settings.h
    src/Engine/State.cpp
    src/Engine/State.h
    src/Game/GameDefines.h
    src/Game/GameDudeObject.cpp
    src/Game/GameDudeObject.h
    src/Game/GameObject.cpp
    src/Game/GameObject.h
    src/Game/GameObjectFactory.cpp
    src/Game/GameObjectFactory.h
    src/Game/GameCritterObject.cpp
    src/Game/GameCritterObject.h
    src/Game/GameItemObject.cpp
    src/Game/GameItemObject.h
    src/Game/GameAmmoItemObject.cpp
    src/Game/GameAmmoItemObject.h
    src/Game/GameArmorItemObject.cpp
    src/Game/GameArmorItemObject.h
    src/Game/GameContainerItemObject.cpp
    src/Game/GameContainerItemObject.h
    src/Game/GameDrugItemObject.cpp
    src/Game/GameDrugItemObject.h
    src/Game/GameKeyItemObject.cpp
    src/Game/GameKeyItemObject.h
    src/Game/GameMiscItemObject.cpp
    src/Game/GameMiscItemObject.h
    src/Game/GameWeaponItemObject.cpp
    src/Game/GameWeaponItemObject.h
    src/Game/GameSceneryObject.cpp
    src/Game/GameSceneryObject.h
    src/Game/GameDoorSceneryObject.cpp
    src/Game/GameDoorSceneryObject.h
    src/Game/GameGenericSceneryObject.cpp
    src/Game/GameGenericSceneryObject.h
    src/Game/GameLadderSceneryObject.cpp
    src/Game/GameLadderSceneryObject.h
    src/Game/GameStairsSceneryObject.cpp
    src/Game/GameStairsSceneryObject.h
    src/Game/GameElevatorSceneryObject.cpp
    src/Game/GameElevatorSceneryObject.h
    src/Game/GameWallObject.cpp
    src/Game/GameWallObject.h
    src/Game/GameMiscObject.cpp
    src/Game/GameMiscObject.h
    src/States/CreditsState.cpp
    src/States/CreditsState.h
    src/States/CritterBarterState.cpp
    src/States/CritterBarterState.h
    src/States/CritterDialogReviewState.cpp
    src/States/CritterDialogReviewState.h
    src/States/CritterDialogState.cpp
    src/States/CritterDialogState.h
    src/States/CritterInteractState.cpp
    src/States/CritterInteractState.h
    src/States/CursorDropdownState.cpp
    src/States/CursorDropdownState.h
    src/States/ExitConfirmState.cpp
    src/States/ExitConfirmState.h
    src/States/GameMenuState.cpp
    src/States/GameMenuState.h
    src/States/InventoryDragItemState.cpp
    src/States/InventoryDragItemState.h
    src/States/InventoryState.cpp
    src/States/InventoryState.h
    src/States/LoadGameState.cpp
    src/States/LoadGameState.h
    src/States/LocationState.cpp
    src/States/LocationState.h
    src/States/MainMenuState.cpp
    src/States/MainMenuState.h
    src/States/MovieState.cpp
    src/States/MovieState.h
    src/States/NewGameState.cpp
    src/States/NewGameState.h
    src/States/PipBoyState.cpp
    src/States/PipBoyState.h
    src/States/PlayerCreateState.cpp
    src/States/PlayerCreateState.h
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
    src/States/PlayerPanelState.cpp
    src/States/PlayerPanelState.h
    src/States/SaveGameState.cpp
    src/States/SaveGameState.h
    src/States/SettingsMenuState.cpp
    src/States/SettingsMenuState.h
    src/States/SkilldexState.cpp
    src/States/SkilldexState.h
    src/States/StartState.cpp
    src/States/StartState.h
    src/States/WorldMapState.cpp
    src/States/WorldMapState.h
    src/UI/AnimatedImage.cpp
    src/UI/AnimatedImage.h
    src/UI/BigCounter.cpp
    src/UI/BigCounter.h
    src/UI/FpsCounter.cpp
    src/UI/FpsCounter.h
    src/UI/HiddenMask.cpp
    src/UI/HiddenMask.h
    src/UI/Image.cpp
    src/UI/Image.h
    src/UI/ImageButton.cpp
    src/UI/ImageButton.h
    src/UI/ImageList.cpp
    src/UI/ImageList.h
    src/UI/MultistateImageButton.cpp
    src/UI/MultistateImageButton.h
    src/UI/MonthCounter.cpp
    src/UI/MonthCounter.h
    src/UI/MvePlayer.cpp
    src/UI/MvePlayer.h
    src/UI/Slider.cpp
    src/UI/Slider.h
    src/UI/SmallCounter.cpp
    src/UI/SmallCounter.h
    src/UI/TextArea.cpp
    src/UI/TextArea.h
    src/VM/Handlers/Opcode8002Handler.h
    src/VM/Handlers/Opcode8002Handler.cpp
    src/VM/Handlers/Opcode8003Handler.h
    src/VM/Handlers/Opcode8003Handler.cpp
    src/VM/Handlers/Opcode8004Handler.h
    src/VM/Handlers/Opcode8004Handler.cpp
    src/VM/Handlers/Opcode8005Handler.h
    src/VM/Handlers/Opcode8005Handler.cpp
    src/VM/Handlers/Opcode800CHandler.h
    src/VM/Handlers/Opcode800CHandler.cpp
    src/VM/Handlers/Opcode800DHandler.h
    src/VM/Handlers/Opcode800DHandler.cpp
    src/VM/Handlers/Opcode8010Handler.h
    src/VM/Handlers/Opcode8010Handler.cpp
    src/VM/Handlers/Opcode8012Handler.h
    src/VM/Handlers/Opcode8012Handler.cpp
    src/VM/Handlers/Opcode8013Handler.h
    src/VM/Handlers/Opcode8013Handler.cpp
    src/VM/Handlers/Opcode8014Handler.h
    src/VM/Handlers/Opcode8014Handler.cpp
    src/VM/Handlers/Opcode8015Handler.h
    src/VM/Handlers/Opcode8015Handler.cpp
    src/VM/Handlers/Opcode8016Handler.h
    src/VM/Handlers/Opcode8016Handler.cpp
    src/VM/Handlers/Opcode8018Handler.h
    src/VM/Handlers/Opcode8018Handler.cpp
    src/VM/Handlers/Opcode8019Handler.h
    src/VM/Handlers/Opcode8019Handler.cpp
    src/VM/Handlers/Opcode801AHandler.h
    src/VM/Handlers/Opcode801AHandler.cpp
    src/VM/Handlers/Opcode801BHandler.h
    src/VM/Handlers/Opcode801BHandler.cpp
    src/VM/Handlers/Opcode801CHandler.h
    src/VM/Handlers/Opcode801CHandler.cpp
    src/VM/Handlers/Opcode8027Handler.h
    src/VM/Handlers/Opcode8027Handler.cpp
    src/VM/Handlers/Opcode8028Handler.h
    src/VM/Handlers/Opcode8028Handler.cpp
    src/VM/Handlers/Opcode8029Handler.h
    src/VM/Handlers/Opcode8029Handler.cpp
    src/VM/Handlers/Opcode802AHandler.h
    src/VM/Handlers/Opcode802AHandler.cpp
    src/VM/Handlers/Opcode802BHandler.h
    src/VM/Handlers/Opcode802BHandler.cpp
    src/VM/Handlers/Opcode802CHandler.h
    src/VM/Handlers/Opcode802CHandler.cpp
    src/VM/Handlers/Opcode802FHandler.h
    src/VM/Handlers/Opcode802FHandler.cpp
    src/VM/Handlers/Opcode8030Handler.h
    src/VM/Handlers/Opcode8030Handler.cpp
    src/VM/Handlers/Opcode8031Handler.h
    src/VM/Handlers/Opcode8031Handler.cpp
    src/VM/Handlers/Opcode8032Handler.h
    src/VM/Handlers/Opcode8032Handler.cpp
    src/VM/Handlers/Opcode8033Handler.h
    src/VM/Handlers/Opcode8033Handler.cpp
    src/VM/Handlers/Opcode8034Handler.h
    src/VM/Handlers/Opcode8034Handler.cpp
    src/VM/Handlers/Opcode8035Handler.h
    src/VM/Handlers/Opcode8035Handler.cpp
    src/VM/Handlers/Opcode8036Handler.h
    src/VM/Handlers/Opcode8036Handler.cpp
    src/VM/Handlers/Opcode8037Handler.h
    src/VM/Handlers/Opcode8037Handler.cpp
    src/VM/Handlers/Opcode8038Handler.h
    src/VM/Handlers/Opcode8038Handler.cpp
    src/VM/Handlers/Opcode8039Handler.h
    src/VM/Handlers/Opcode8039Handler.cpp
    src/VM/Handlers/Opcode803AHandler.h
    src/VM/Handlers/Opcode803AHandler.cpp
    src/VM/Handlers/Opcode803BHandler.h
    src/VM/Handlers/Opcode803BHandler.cpp
    src/VM/Handlers/Opcode803CHandler.h
    src/VM/Handlers/Opcode803CHandler.cpp
    src/VM/Handlers/Opcode803DHandler.h
    src/VM/Handlers/Opcode803DHandler.cpp
    src/VM/Handlers/Opcode803EHandler.h
    src/VM/Handlers/Opcode803EHandler.cpp
    src/VM/Handlers/Opcode803FHandler.h
    src/VM/Handlers/Opcode803FHandler.cpp
    src/VM/Handlers/Opcode8040Handler.h
    src/VM/Handlers/Opcode8040Handler.cpp
    src/VM/Handlers/Opcode8041Handler.h
    src/VM/Handlers/Opcode8041Handler.cpp
    src/VM/Handlers/Opcode8045Handler.h
    src/VM/Handlers/Opcode8045Handler.cpp
    src/VM/Handlers/Opcode8046Handler.h
    src/VM/Handlers/Opcode8046Handler.cpp
    src/VM/Handlers/Opcode80A1Handler.h
    src/VM/Handlers/Opcode80A1Handler.cpp
    src/VM/Handlers/Opcode80A3Handler.h
    src/VM/Handlers/Opcode80A3Handler.cpp
    src/VM/Handlers/Opcode80A4Handler.h
    src/VM/Handlers/Opcode80A4Handler.cpp
    src/VM/Handlers/Opcode80A6Handler.h
    src/VM/Handlers/Opcode80A6Handler.cpp
    src/VM/Handlers/Opcode80A7Handler.h
    src/VM/Handlers/Opcode80A7Handler.cpp
    src/VM/Handlers/Opcode80A8Handler.h
    src/VM/Handlers/Opcode80A8Handler.cpp
    src/VM/Handlers/Opcode80A9Handler.h
    src/VM/Handlers/Opcode80A9Handler.cpp
    src/VM/Handlers/Opcode80AAHandler.h
    src/VM/Handlers/Opcode80AAHandler.cpp
    src/VM/Handlers/Opcode80ABHandler.h
    src/VM/Handlers/Opcode80ABHandler.cpp
    src/VM/Handlers/Opcode80ACHandler.h
    src/VM/Handlers/Opcode80ACHandler.cpp
    src/VM/Handlers/Opcode80AEHandler.h
    src/VM/Handlers/Opcode80AEHandler.cpp
    src/VM/Handlers/Opcode80AFHandler.h
    src/VM/Handlers/Opcode80AFHandler.cpp
    src/VM/Handlers/Opcode80B0Handler.h
    src/VM/Handlers/Opcode80B0Handler.cpp
    src/VM/Handlers/Opcode80B2Handler.h
    src/VM/Handlers/Opcode80B2Handler.cpp
    src/VM/Handlers/Opcode80B4Handler.h
    src/VM/Handlers/Opcode80B4Handler.cpp
    src/VM/Handlers/Opcode80B6Handler.h
    src/VM/Handlers/Opcode80B6Handler.cpp
    src/VM/Handlers/Opcode80B7Handler.h
    src/VM/Handlers/Opcode80B7Handler.cpp
    src/VM/Handlers/Opcode80B8Handler.h
    src/VM/Handlers/Opcode80B8Handler.cpp
    src/VM/Handlers/Opcode80B9Handler.h
    src/VM/Handlers/Opcode80B9Handler.cpp
    src/VM/Handlers/Opcode80BAHandler.h
    src/VM/Handlers/Opcode80BAHandler.cpp
    src/VM/Handlers/Opcode80BBHandler.h
    src/VM/Handlers/Opcode80BBHandler.cpp
    src/VM/Handlers/Opcode80BCHandler.h
    src/VM/Handlers/Opcode80BCHandler.cpp
    src/VM/Handlers/Opcode80BDHandler.h
    src/VM/Handlers/Opcode80BDHandler.cpp
    src/VM/Handlers/Opcode80BFHandler.h
    src/VM/Handlers/Opcode80BFHandler.cpp
    src/VM/Handlers/Opcode80C1Handler.h
    src/VM/Handlers/Opcode80C1Handler.cpp
    src/VM/Handlers/Opcode80C2Handler.h
    src/VM/Handlers/Opcode80C2Handler.cpp
    src/VM/Handlers/Opcode80C3Handler.h
    src/VM/Handlers/Opcode80C3Handler.cpp
    src/VM/Handlers/Opcode80C4Handler.h
    src/VM/Handlers/Opcode80C4Handler.cpp
    src/VM/Handlers/Opcode80C5Handler.h
    src/VM/Handlers/Opcode80C5Handler.cpp
    src/VM/Handlers/Opcode80C6Handler.h
    src/VM/Handlers/Opcode80C6Handler.cpp
    src/VM/Handlers/Opcode80C7Handler.h
    src/VM/Handlers/Opcode80C7Handler.cpp
    src/VM/Handlers/Opcode80C8Handler.h
    src/VM/Handlers/Opcode80C8Handler.cpp
    src/VM/Handlers/Opcode80C9Handler.h
    src/VM/Handlers/Opcode80C9Handler.cpp
    src/VM/Handlers/Opcode80CAHandler.h
    src/VM/Handlers/Opcode80CAHandler.cpp
    src/VM/Handlers/Opcode80CBHandler.h
    src/VM/Handlers/Opcode80CBHandler.cpp
    src/VM/Handlers/Opcode80CCHandler.h
    src/VM/Handlers/Opcode80CCHandler.cpp
    src/VM/Handlers/Opcode80CEHandler.h
    src/VM/Handlers/Opcode80CEHandler.cpp
    src/VM/Handlers/Opcode80CFHandler.h
    src/VM/Handlers/Opcode80CFHandler.cpp
    src/VM/Handlers/Opcode80D0Handler.h
    src/VM/Handlers/Opcode80D0Handler.cpp
    src/VM/Handlers/Opcode80D2Handler.h
    src/VM/Handlers/Opcode80D2Handler.cpp
    src/VM/Handlers/Opcode80D3Handler.h
    src/VM/Handlers/Opcode80D3Handler.cpp
    src/VM/Handlers/Opcode80D4Handler.h
    src/VM/Handlers/Opcode80D4Handler.cpp
    src/VM/Handlers/Opcode80D5Handler.h
    src/VM/Handlers/Opcode80D5Handler.cpp
    src/VM/Handlers/Opcode80D8Handler.h
    src/VM/Handlers/Opcode80D8Handler.cpp
    src/VM/Handlers/Opcode80D9Handler.h
    src/VM/Handlers/Opcode80D9Handler.cpp
    src/VM/Handlers/Opcode80DAHandler.h
    src/VM/Handlers/Opcode80DAHandler.cpp
    src/VM/Handlers/Opcode80DEHandler.h
    src/VM/Handlers/Opcode80DEHandler.cpp
    src/VM/Handlers/Opcode80DCHandler.h
    src/VM/Handlers/Opcode80DCHandler.cpp
    src/VM/Handlers/Opcode80DFHandler.h
    src/VM/Handlers/Opcode80DFHandler.cpp
    src/VM/Handlers/Opcode80E1Handler.h
    src/VM/Handlers/Opcode80E1Handler.cpp
    src/VM/Handlers/Opcode80E3Handler.h
    src/VM/Handlers/Opcode80E3Handler.cpp
    src/VM/Handlers/Opcode80E4Handler.h
    src/VM/Handlers/Opcode80E4Handler.cpp
    src/VM/Handlers/Opcode80E5Handler.h
    src/VM/Handlers/Opcode80E5Handler.cpp
    src/VM/Handlers/Opcode80E7Handler.h
    src/VM/Handlers/Opcode80E7Handler.cpp
    src/VM/Handlers/Opcode80E8Handler.h
    src/VM/Handlers/Opcode80E8Handler.cpp
    src/VM/Handlers/Opcode80E9Handler.h
    src/VM/Handlers/Opcode80E9Handler.cpp
    src/VM/Handlers/Opcode80EAHandler.h
    src/VM/Handlers/Opcode80EAHandler.cpp
    src/VM/Handlers/Opcode80ECHandler.h
    src/VM/Handlers/Opcode80ECHandler.cpp
    src/VM/Handlers/Opcode80EFHandler.h
    src/VM/Handlers/Opcode80EFHandler.cpp
    src/VM/Handlers/Opcode80F0Handler.h
    src/VM/Handlers/Opcode80F0Handler.cpp
    src/VM/Handlers/Opcode80F1Handler.h
    src/VM/Handlers/Opcode80F1Handler.cpp
    src/VM/Handlers/Opcode80F2Handler.h
    src/VM/Handlers/Opcode80F2Handler.cpp
    src/VM/Handlers/Opcode80F3Handler.h
    src/VM/Handlers/Opcode80F3Handler.cpp
    src/VM/Handlers/Opcode80F4Handler.h
    src/VM/Handlers/Opcode80F4Handler.cpp
    src/VM/Handlers/Opcode80F6Handler.h
    src/VM/Handlers/Opcode80F6Handler.cpp
    src/VM/Handlers/Opcode80F7Handler.h
    src/VM/Handlers/Opcode80F7Handler.cpp
    src/VM/Handlers/Opcode80F9Handler.h
    src/VM/Handlers/Opcode80F9Handler.cpp
    src/VM/Handlers/Opcode80FAHandler.h
    src/VM/Handlers/Opcode80FAHandler.cpp
    src/VM/Handlers/Opcode80FBHandler.h
    src/VM/Handlers/Opcode80FBHandler.cpp
    src/VM/Handlers/Opcode80FCHandler.h
    src/VM/Handlers/Opcode80FCHandler.cpp
    src/VM/Handlers/Opcode80FFHandler.h
    src/VM/Handlers/Opcode80FFHandler.cpp
    src/VM/Handlers/Opcode810AHandler.h
    src/VM/Handlers/Opcode810AHandler.cpp
    src/VM/Handlers/Opcode810CHandler.h
    src/VM/Handlers/Opcode810CHandler.cpp
    src/VM/Handlers/Opcode810DHandler.cpp
    src/VM/Handlers/Opcode810EHandler.cpp
    src/VM/Handlers/Opcode8118Handler.h
    src/VM/Handlers/Opcode8118Handler.cpp
    src/VM/Handlers/Opcode8119Handler.h
    src/VM/Handlers/Opcode8119Handler.cpp
    src/VM/Handlers/Opcode8123Handler.h
    src/VM/Handlers/Opcode8123Handler.cpp
    src/VM/Handlers/Opcode8126Handler.h
    src/VM/Handlers/Opcode8126Handler.cpp
    src/VM/Handlers/Opcode8127Handler.h
    src/VM/Handlers/Opcode8127Handler.cpp
    src/VM/Handlers/Opcode8136Handler.h
    src/VM/Handlers/Opcode8136Handler.cpp
    src/VM/Handlers/Opcode8137Handler.h
    src/VM/Handlers/Opcode8137Handler.cpp
    src/VM/Handlers/Opcode813CHandler.h
    src/VM/Handlers/Opcode813CHandler.cpp
    src/VM/Handlers/Opcode9001Handler.h
    src/VM/Handlers/Opcode9001Handler.cpp
    src/VM/Handlers/OpcodeC001Handler.h
    src/VM/Handlers/OpcodeC001Handler.cpp
    src/VM/OpcodeHandler.h
    src/VM/OpcodeHandler.cpp
    src/VM/VM.cpp
    src/VM/VM.h
    src/VM/VMHaltException.cpp
    src/VM/VMHaltException.h
    src/VM/VMStack.cpp
    src/VM/VMStack.h
    src/VM/VMStackValue.cpp
    src/VM/VMStackValue.h
    src/VM/VMStackFloatValue.cpp
    src/VM/VMStackFloatValue.h
    src/VM/VMStackIntValue.cpp
    src/VM/VMStackIntValue.h
    src/VM/VMStackPointerValue.cpp
    src/VM/VMStackPointerValue.h)

add_definitions (-std=c++11 -Wall)
set(CMAKE_BUILD_TYPE Debug)

if(LIBFALLTERGEIST_EMBEDDED)
    add_subdirectory(lib/libfalltergeist)
endif()

add_executable(falltergeist-bin ${SOURCES})
set_target_properties(falltergeist-bin PROPERTIES OUTPUT_NAME falltergeist)
target_link_libraries(falltergeist-bin ${SDL2_LIBRARY} ${SDLMIXER_LIBRARY} ${OPENGL_LIBRARIES} ${LIBFALLTERGEIST_LIBRARY})

#
# Install section
#
if(WIN32)
    install(TARGETS falltergeist-bin RUNTIME DESTINATION .) 
    install(DIRECTORY data DESTINATION .)                   

    if(LIBFALLTERGEIST_EMBEDDED)
        install(FILES ${CMAKE_BINARY_DIR}/lib/libfalltergeist/libfalltergeist.dll DESTINATION .)
    endif()

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

    if(LIBFALLTERGEIST_EMBEDDED)
        install(FILES ${CMAKE_BINARY_DIR}/lib/libfalltergeist/libfalltergeist.so DESTINATION lib)
    endif()
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
