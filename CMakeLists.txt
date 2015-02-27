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

set(SOURCES main.cpp
    src/Audio/AudioMixer.cpp
    src/Audio/AudioMixer.h
    src/CrossPlatform.cpp
    src/CrossPlatform.h
    src/Event/Event.cpp
    src/Event/Event.h
    src/Event/EventEmitter.cpp
    src/Event/EventEmitter.h
    src/Event/KeyboardEvent.cpp
    src/Event/KeyboardEvent.h
    src/Event/MouseEvent.cpp
    src/Event/MouseEvent.h
    src/Event/StateEvent.cpp
    src/Event/StateEvent.h
    src/Exception.cpp
    src/Exception.h
    src/Font.cpp
    src/Font.h
    src/FontString.cpp
    src/FontString.h
    src/functions.cpp
    src/functions.h
    src/Graphics/ActiveUI.cpp
    src/Graphics/ActiveUI.h
    src/Graphics/AnimatedPalette.cpp
    src/Graphics/AnimatedPalette.h
    src/Graphics/Animation.cpp
    src/Graphics/Animation.h
    src/Graphics/AnimationFrame.cpp
    src/Graphics/AnimationFrame.h
    src/Graphics/AnimationQueue.cpp
    src/Graphics/AnimationQueue.h
    src/Graphics/Renderer.cpp
    src/Graphics/Renderer.h
    src/Graphics/Texture.cpp
    src/Graphics/Texture.h
    src/Graphics/Tile.cpp
    src/Graphics/Tile.h
    src/Graphics/TileMap.cpp
    src/Graphics/TileMap.h
    src/Graphics/UI.cpp
    src/Graphics/UI.h
    src/Ini/File.cpp
    src/Ini/File.h
    src/Ini/Parser.cpp
    src/Ini/Parser.h
    src/Ini/Section.cpp
    src/Ini/Section.h
    src/Ini/Writer.cpp
    src/Ini/Writer.h
    src/Ini/Value.cpp
    src/Ini/Value.h
    src/Input/Mouse.cpp
    src/Input/Mouse.h
    src/LocationCamera.cpp
    src/LocationCamera.h
    src/Logger.cpp
    src/Logger.h
    src/PathFinding/Hexagon.cpp
    src/PathFinding/Hexagon.h
    src/PathFinding/HexagonGrid.cpp
    src/PathFinding/HexagonGrid.h
    src/ResourceManager.cpp
    src/ResourceManager.h
    src/Settings.cpp
    src/Settings.h
    src/Game/Game.cpp
    src/Game/Game.h
    src/Game/Defines.h
    src/Game/DudeObject.cpp
    src/Game/DudeObject.h
    src/Game/Object.cpp
    src/Game/Object.h
    src/Game/ObjectFactory.cpp
    src/Game/ObjectFactory.h
    src/Game/CritterObject.cpp
    src/Game/CritterObject.h
    src/Game/ItemObject.cpp
    src/Game/ItemObject.h
    src/Game/AmmoItemObject.cpp
    src/Game/AmmoItemObject.h
    src/Game/ArmorItemObject.cpp
    src/Game/ArmorItemObject.h
    src/Game/ContainerItemObject.cpp
    src/Game/ContainerItemObject.h
    src/Game/DrugItemObject.cpp
    src/Game/DrugItemObject.h
    src/Game/KeyItemObject.cpp
    src/Game/KeyItemObject.h
    src/Game/MiscItemObject.cpp
    src/Game/MiscItemObject.h
    src/Game/WeaponItemObject.cpp
    src/Game/WeaponItemObject.h
    src/Game/SceneryObject.cpp
    src/Game/SceneryObject.h
    src/Game/Time.cpp
    src/Game/Time.h
    src/Game/DoorSceneryObject.cpp
    src/Game/DoorSceneryObject.h
    src/Game/GenericSceneryObject.cpp
    src/Game/GenericSceneryObject.h
    src/Game/LadderSceneryObject.cpp
    src/Game/LadderSceneryObject.h
    src/Game/StairsSceneryObject.cpp
    src/Game/StairsSceneryObject.h
    src/Game/ElevatorSceneryObject.cpp
    src/Game/ElevatorSceneryObject.h
    src/Game/WallObject.cpp
    src/Game/WallObject.h
    src/Game/ExitMiscObject.cpp
    src/Game/ExitMiscObject.h
    src/Game/MiscObject.cpp
    src/Game/MiscObject.h
    src/Game/Location.cpp
    src/Game/Location.h
    src/Game/LocationElevation.cpp
    src/Game/LocationElevation.h
    src/State/Container.cpp
    src/State/Container.h
    src/State/Credits.cpp
    src/State/Credits.h
    src/State/CritterBarter.cpp
    src/State/CritterBarter.h
    src/State/CritterDialogReview.cpp
    src/State/CritterDialogReview.h
    src/State/CritterDialog.cpp
    src/State/CritterDialog.h
    src/State/CritterInteract.cpp
    src/State/CritterInteract.h
    src/State/CursorDropdown.cpp
    src/State/CursorDropdown.h
    src/State/ExitConfirm.cpp
    src/State/ExitConfirm.h
    src/State/GameMenu.cpp
    src/State/GameMenu.h
    src/State/InventoryDragItem.cpp
    src/State/InventoryDragItem.h
    src/State/Inventory.cpp
    src/State/Inventory.h
    src/State/LoadGame.cpp
    src/State/LoadGame.h
    src/State/Location.cpp
    src/State/Location.h
    src/State/MainMenu.cpp
    src/State/MainMenu.h
    src/State/Movie.cpp
    src/State/Movie.h
    src/State/NewGame.cpp
    src/State/NewGame.h
    src/State/PipBoy.cpp
    src/State/PipBoy.h
    src/State/PlayerCreateOptions.cpp
    src/State/PlayerCreateOptions.h
    src/State/PlayerCreate.cpp
    src/State/PlayerCreate.h
    src/State/PlayerEdit.cpp
    src/State/PlayerEdit.h
    src/State/PlayerEditAge.cpp
    src/State/PlayerEditAge.h
    src/State/PlayerEditAlert.cpp
    src/State/PlayerEditAlert.h
    src/State/PlayerEditGender.cpp
    src/State/PlayerEditGender.h
    src/State/PlayerEditName.cpp
    src/State/PlayerEditName.h
    src/State/PlayerPanel.cpp
    src/State/PlayerPanel.h
    src/State/SaveGame.cpp
    src/State/SaveGame.h
    src/State/SettingsMenu.cpp
    src/State/SettingsMenu.h
    src/State/Skilldex.cpp
    src/State/Skilldex.h
    src/State/Start.cpp
    src/State/Start.h
    src/State/State.cpp
    src/State/State.h
    src/State/WorldMap.cpp
    src/State/WorldMap.h
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
    src/UI/InventoryItem.cpp
    src/UI/InventoryItem.h
    src/UI/ItemsList.cpp
    src/UI/ItemsList.h
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
    src/UI/TextSymbol.cpp
    src/UI/TextSymbol.h
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
    src/VM/Handlers/OpcodeComparisonHandler.h
    src/VM/Handlers/OpcodeComparisonHandler.cpp
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
    src/VM/Handlers/Opcode8042Handler.h
    src/VM/Handlers/Opcode8042Handler.cpp
    src/VM/Handlers/Opcode8043Handler.h
    src/VM/Handlers/Opcode8043Handler.cpp
    src/VM/Handlers/Opcode8044Handler.h
    src/VM/Handlers/Opcode8044Handler.cpp
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
    src/VM/Handlers/Opcode80FDHandler.h
    src/VM/Handlers/Opcode80FDHandler.cpp
    src/VM/Handlers/Opcode80FEHandler.h
    src/VM/Handlers/Opcode80FEHandler.cpp
    src/VM/Handlers/Opcode80FFHandler.h
    src/VM/Handlers/Opcode80FFHandler.cpp
    src/VM/Handlers/Opcode8100Handler.h
    src/VM/Handlers/Opcode8100Handler.cpp
    src/VM/Handlers/Opcode8101Handler.h
    src/VM/Handlers/Opcode8101Handler.cpp
    src/VM/Handlers/Opcode8102Handler.h
    src/VM/Handlers/Opcode8102Handler.cpp
    src/VM/Handlers/Opcode8105Handler.h
    src/VM/Handlers/Opcode8105Handler.cpp
    src/VM/Handlers/Opcode8106Handler.h
    src/VM/Handlers/Opcode8106Handler.cpp
    src/VM/Handlers/Opcode810AHandler.h
    src/VM/Handlers/Opcode810AHandler.cpp
    src/VM/Handlers/Opcode810BHandler.h
    src/VM/Handlers/Opcode810BHandler.cpp
    src/VM/Handlers/Opcode810CHandler.h
    src/VM/Handlers/Opcode810CHandler.cpp
    src/VM/Handlers/Opcode810DHandler.cpp
    src/VM/Handlers/Opcode810EHandler.cpp
    src/VM/Handlers/Opcode810FHandler.h
    src/VM/Handlers/Opcode810FHandler.cpp
    src/VM/Handlers/Opcode8113Handler.h
    src/VM/Handlers/Opcode8113Handler.cpp
    src/VM/Handlers/Opcode8115Handler.h
    src/VM/Handlers/Opcode8115Handler.cpp
    src/VM/Handlers/Opcode8116Handler.h
    src/VM/Handlers/Opcode8116Handler.cpp
    src/VM/Handlers/Opcode8117Handler.h
    src/VM/Handlers/Opcode8117Handler.cpp
    src/VM/Handlers/Opcode8118Handler.h
    src/VM/Handlers/Opcode8118Handler.cpp
    src/VM/Handlers/Opcode8119Handler.h
    src/VM/Handlers/Opcode8119Handler.cpp
    src/VM/Handlers/Opcode811CHandler.h
    src/VM/Handlers/Opcode811CHandler.cpp
    src/VM/Handlers/Opcode811DHandler.h
    src/VM/Handlers/Opcode811DHandler.cpp
    src/VM/Handlers/Opcode811EHandler.h
    src/VM/Handlers/Opcode811EHandler.cpp
    src/VM/Handlers/Opcode8120Handler.h
    src/VM/Handlers/Opcode8120Handler.cpp
    src/VM/Handlers/Opcode8121Handler.h
    src/VM/Handlers/Opcode8121Handler.cpp
    src/VM/Handlers/Opcode8122Handler.h
    src/VM/Handlers/Opcode8122Handler.cpp
    src/VM/Handlers/Opcode8123Handler.h
    src/VM/Handlers/Opcode8123Handler.cpp
    src/VM/Handlers/Opcode8125Handler.h
    src/VM/Handlers/Opcode8125Handler.cpp
    src/VM/Handlers/Opcode8126Handler.h
    src/VM/Handlers/Opcode8126Handler.cpp
    src/VM/Handlers/Opcode8127Handler.h
    src/VM/Handlers/Opcode8127Handler.cpp
    src/VM/Handlers/Opcode8128Handler.h
    src/VM/Handlers/Opcode8128Handler.cpp
    src/VM/Handlers/Opcode8129Handler.h
    src/VM/Handlers/Opcode8129Handler.cpp
    src/VM/Handlers/Opcode812DHandler.h
    src/VM/Handlers/Opcode812DHandler.cpp
    src/VM/Handlers/Opcode812EHandler.h
    src/VM/Handlers/Opcode812EHandler.cpp
    src/VM/Handlers/Opcode812FHandler.h
    src/VM/Handlers/Opcode812FHandler.cpp
    src/VM/Handlers/Opcode8130Handler.h
    src/VM/Handlers/Opcode8130Handler.cpp
    src/VM/Handlers/Opcode8131Handler.h
    src/VM/Handlers/Opcode8131Handler.cpp
    src/VM/Handlers/Opcode8132Handler.h
    src/VM/Handlers/Opcode8132Handler.cpp
    src/VM/Handlers/Opcode8134Handler.h
    src/VM/Handlers/Opcode8134Handler.cpp	
    src/VM/Handlers/Opcode8136Handler.h
    src/VM/Handlers/Opcode8136Handler.cpp
    src/VM/Handlers/Opcode8137Handler.h
    src/VM/Handlers/Opcode8137Handler.cpp
    src/VM/Handlers/Opcode8138Handler.h
    src/VM/Handlers/Opcode8138Handler.cpp
    src/VM/Handlers/Opcode8139Handler.h
    src/VM/Handlers/Opcode8139Handler.cpp	
    src/VM/Handlers/Opcode813CHandler.h
    src/VM/Handlers/Opcode813CHandler.cpp
    src/VM/Handlers/Opcode8143Handler.h
    src/VM/Handlers/Opcode8143Handler.cpp
    src/VM/Handlers/Opcode8147Handler.h
    src/VM/Handlers/Opcode8147Handler.cpp
    src/VM/Handlers/Opcode8149Handler.h
    src/VM/Handlers/Opcode8149Handler.cpp
    src/VM/Handlers/Opcode814BHandler.h
    src/VM/Handlers/Opcode814BHandler.cpp
    src/VM/Handlers/Opcode814CHandler.h
    src/VM/Handlers/Opcode814CHandler.cpp
    src/VM/Handlers/Opcode814EHandler.h
    src/VM/Handlers/Opcode814EHandler.cpp
    src/VM/Handlers/Opcode8150Handler.h
    src/VM/Handlers/Opcode8150Handler.cpp
    src/VM/Handlers/Opcode8151Handler.h
    src/VM/Handlers/Opcode8151Handler.cpp
    src/VM/Handlers/Opcode8152Handler.h
    src/VM/Handlers/Opcode8152Handler.cpp
    src/VM/Handlers/Opcode8153Handler.h
    src/VM/Handlers/Opcode8153Handler.cpp
    src/VM/Handlers/Opcode8154Handler.h
    src/VM/Handlers/Opcode8154Handler.cpp	
    src/VM/Handlers/Opcode9001Handler.h
    src/VM/Handlers/Opcode9001Handler.cpp
    src/VM/Handlers/OpcodeC001Handler.h
    src/VM/Handlers/OpcodeC001Handler.cpp
    src/VM/Handlers/OpcodeA001Handler.h
    src/VM/Handlers/OpcodeA001Handler.cpp
    src/VM/OpcodeFactory.h
    src/VM/OpcodeFactory.cpp
    src/VM/OpcodeHandler.h
    src/VM/OpcodeHandler.cpp
    src/VM/VM.cpp
    src/VM/VM.h
    src/VM/VMHaltException.cpp
    src/VM/VMHaltException.h
    src/VM/VMStack.cpp
    src/VM/VMStack.h
    src/VM/VMStackValue.cpp
    src/VM/VMStackValue.h)

add_definitions (-std=c++11 -Wall)

if(LIBFALLTERGEIST_EMBEDDED)
    add_subdirectory(lib/libfalltergeist)
endif()

add_executable(falltergeist-bin ${SOURCES})
set_target_properties(falltergeist-bin PROPERTIES OUTPUT_NAME falltergeist)
target_link_libraries(falltergeist-bin ${SDL2_LIBRARY} ${SDLMIXER_LIBRARY} ${SDLIMAGE_LIBRARY} ${LIBFALLTERGEIST_LIBRARY})

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
