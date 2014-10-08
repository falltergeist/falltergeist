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

find_package(LIBFALLTERGEIST REQUIRED)
if(NOT LIBFALLTERGEIST_FOUND)
          message(FATAL_ERROR "libfalltergeist library not found")
endif(NOT LIBFALLTERGEIST_FOUND)
include_directories(${LIBFALLTERGEIST_INCLUDE_DIR})

find_package(SDL2 REQUIRED)
if(NOT SDL2_FOUND)
          message(FATAL_ERROR "SDL2 library not found")
endif(NOT SDL2_FOUND)
include_directories(${SDL2_INCLUDE_DIR})

find_package(OpenGL REQUIRED)
if(NOT OPENGL_FOUND)
          message(FATAL_ERROR "OpenGL library not found")
endif(NOT OPENGL_FOUND)
include_directories(${OPENGL_INCLUDE_DIR})

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
            src/Engine/Event/MouseEvent.cpp
            src/Engine/Event/MouseEvent.h
            src/Engine/Event/KeyboardEvent.cpp
            src/Engine/Event/KeyboardEvent.h
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
            src/VM/Handlers/Opcode8033Handler.h
            src/VM/Handlers/Opcode8033Handler.cpp
            src/VM/Handlers/Opcode8034Handler.h
            src/VM/Handlers/Opcode8034Handler.cpp
            src/VM/Handlers/Opcode8039Handler.h
            src/VM/Handlers/Opcode8039Handler.cpp
            src/VM/Handlers/Opcode80BAHandler.h
            src/VM/Handlers/Opcode80BAHandler.cpp
            src/VM/Handlers/Opcode80BCHandler.h
            src/VM/Handlers/Opcode80BCHandler.cpp
            src/VM/Handlers/Opcode80CAHandler.h
            src/VM/Handlers/Opcode80CAHandler.cpp
            src/VM/Handlers/Opcode80CBHandler.h
            src/VM/Handlers/Opcode80CBHandler.cpp
            src/VM/Handlers/Opcode80DEHandler.h
            src/VM/Handlers/Opcode80DEHandler.cpp
            src/VM/Handlers/Opcode810AHandler.h
            src/VM/Handlers/Opcode810AHandler.cpp
            src/VM/Handlers/Opcode810DHandler.cpp
            src/VM/Handlers/Opcode8119Handler.h
            src/VM/Handlers/Opcode8119Handler.cpp
            src/VM/Handlers/Opcode8127Handler.h
            src/VM/Handlers/Opcode8127Handler.cpp
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
            src/VM/VMStackPointerValue.h
            )

add_definitions (-std=c++11 -Wall)
set(CMAKE_BUILD_TYPE Debug)
add_executable(falltergeist ${SOURCES})
target_link_libraries(falltergeist ${SDL2_LIBRARY} ${OPENGL_LIBRARIES} ${LIBFALLTERGEIST_LIBRARY})
