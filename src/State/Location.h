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
#include "../State/PlayerPanel.h"
#include "../UI/ImageButton.h"

// Third party includes

namespace Falltergeist
{
namespace Game
{
    class GameObject;

}
class Animation;
class Hexagon;
class HexagonGrid;
class Image;
class LocationCamera;
class Tile;
class TileMap;
class VMStackValue;
class VM;

namespace State
{
class Location : public State
{
protected:
    
    const int KEYBOARD_SCROLL_STEP = 35;

    // Timers
    unsigned int _scrollTicks = 0;
    unsigned int _scriptsTicks = 0;
    unsigned int _actionCursorTicks = 0;

    HexagonGrid* _hexagonGrid = 0;
    LocationCamera* _camera = 0;
    TileMap* _floor = 0;
    TileMap* _roof = 0;
    VM* _locationScript = 0;
    std::vector<int> _MVARS;
    std::map<std::string, VMStackValue*> _EVARS;
    std::vector<ActiveUI*> _floatMessages;

    bool _locationEnter = true;
    unsigned int _currentElevation = 0;
    unsigned int _lastClickedTile = 0;
    Game::GameObject* _objectUnderCursor = NULL;
    Game::GameObject* _actionCursorLastObject = NULL;
    bool _actionCursorButtonPressed = false;
    PlayerPanel* _playerPanel = NULL;

    bool _scrollLeft = false;
    bool _scrollRight = false;
    bool _scrollTop = false;
    bool _scrollBottom = false;

    std::vector<Game::GameObject*> _objects;
    TextArea* _hexagonInfo = 0;
    
    std::vector<int> getCursorIconsForObject(Game::GameObject* object);
public:
    Location();
    ~Location();

    void setLocation(std::string name);

    virtual void init();
    virtual void think();
    virtual void handle(Event* event);
    virtual void render();

    HexagonGrid* hexagonGrid();
    LocationCamera* camera();

    void setMVAR(unsigned int number, int value);
    int MVAR(unsigned int number);

    std::map<std::string, VMStackValue*>* EVARS();

    static void moveObjectToHexagon(Game::GameObject* object, Hexagon* hexagon);
    void centerCameraAtHexagon(Hexagon* hexagon);
    void handleAction(Game::GameObject* object, int action);
    void toggleCursorMode();
    PlayerPanel* playerPanelState();
    
    void displayMessage(std::string message);

    void onBackgroundClick(MouseEvent* event);
    void onObjectMouseEvent(Event* event, Game::GameObject* object);
    void onObjectHover(Event* event, Game::GameObject* object);
    virtual void onKeyDown(KeyboardEvent* event);

    virtual void onStateActivate(StateEvent* event);
    virtual void onStateDeactivate(StateEvent* event);



};

}
}

#endif // FALLTERGEIST_Location_H
