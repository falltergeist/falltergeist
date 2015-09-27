/*
 * Copyright 2012-2015 Falltergeist Developers.
 *
 * This file is part of Falltergeist.
 *
 * Falltergeist is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Falltergeist is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Falltergeist.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef FALLTERGEIST_Location_H
#define FALLTERGEIST_Location_H

// C++ standard includes
#include <memory>

// Falltergeist includes
#include "State.h"
#include "../Input/Mouse.h"
#include "../UI/ImageButton.h"

// Third party includes

namespace Falltergeist
{
namespace Game
{
    class Object;
}
namespace UI
{
    class Animation;
    class Image;
    class PlayerPanel;
    class Tile;
    class TileMap;
}
class Hexagon;
class HexagonGrid;
class LocationCamera;
class VMStackValue;
class VM;

namespace State
{
    
/**
 * Location state works whenever player is on some map.
 * This state holds pointers to all object on current map, hexagon grid and other map-specific information.
 * 
 * pushed: when player starts new game or loads new game
 * popped: when player closes the game, exits to main menu or loads the game
 */
class Location : public State
{
public:
    Location();
    ~Location() override;

    void setLocation(const std::string& name);

    void init();
    void think() override;
    void handle(Event::Event* event) override;
    void render() override;

    HexagonGrid* hexagonGrid();
    LocationCamera* camera();

    void setMVAR(unsigned int number, int value);
    int MVAR(unsigned int number);

    std::map<std::string, VMStackValue>* EVARS();

    static void moveObjectToHexagon(Game::Object* object, Hexagon* hexagon);
    void destroyObject(Game::Object* object);
    void centerCameraAtHexagon(Hexagon* hexagon);
    void centerCameraAtHexagon(int tileNum);
    void handleAction(Game::Object* object, Input::Mouse::Icon action);
    void toggleCursorMode();

    void displayMessage(const std::string& message);

    void onBackgroundClick(Event::Mouse* event);
    void onObjectMouseEvent(Event::Event* event, Game::Object* object);
    void onObjectHover(Event::Event* event, Game::Object* object);
    void onKeyDown(Event::Keyboard* event) override;

    void onStateActivate(Event::State* event) override;
    void onStateDeactivate(Event::State* event) override;

    UI::PlayerPanel* playerPanel();

protected:
    
    static const int KEYBOARD_SCROLL_STEP;
    static const int DROPDOWN_DELAY;

    // Timers
    unsigned int _scrollTicks = 0;
    unsigned int _scriptsTicks = 0;
    unsigned int _actionCursorTicks = 0;

    std::unique_ptr<HexagonGrid> _hexagonGrid;
    std::unique_ptr<LocationCamera> _camera;
    std::unique_ptr<UI::TileMap> _floor;
    std::unique_ptr<UI::TileMap> _roof ;
    std::unique_ptr<VM> _locationScript;
    std::vector<int> _MVARS;
    std::map<std::string, VMStackValue> _EVARS;
    std::vector<UI::Base*> _floatMessages;

    bool _locationEnter = true;
    unsigned int _currentElevation = 0;
    unsigned int _lastClickedTile = 0;
    Game::Object* _objectUnderCursor = NULL;
    Game::Object* _actionCursorLastObject = NULL;
    bool _actionCursorButtonPressed = false;
    std::unique_ptr<UI::PlayerPanel> _playerPanel;

    bool _scrollLeft = false;
    bool _scrollRight = false;
    bool _scrollTop = false;
    bool _scrollBottom = false;

    std::vector<std::unique_ptr<Game::Object>> _objects;
    std::unique_ptr<UI::TextArea> _hexagonInfo;
    
    std::vector<Input::Mouse::Icon> getCursorIconsForObject(Game::Object* object);

};

}
}

#endif // FALLTERGEIST_Location_H
