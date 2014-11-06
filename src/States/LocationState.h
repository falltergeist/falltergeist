/*
 * Copyright 2012-2014 Falltergeist Developers.
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
 *
 */

#ifndef FALLTERGEIST_LOCATIONSTATE_H
#define FALLTERGEIST_LOCATIONSTATE_H

// C++ standard includes
#include <memory>

// Falltergeist includes
#include "../Engine/State.h"
#include "../UI/ImageButton.h"

// Third party includes

namespace Falltergeist
{
class Animation;
class GameObject;
class Hexagon;
class HexagonGrid;
class Image;
class Location;
class LocationCamera;
class Tile;
class TileMap;
class VMStackValue;
class VM;

class LocationState : public State
{
protected:

    // Timers
    unsigned int _scrollTicks = 0;
    unsigned int _scriptsTicks = 0;

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

    bool _scrollLeft = false;
    bool _scrollRight = false;
    bool _scrollTop = false;
    bool _scrollBottom = false;

    std::vector<GameObject*> _objects;

public:
    LocationState();
    ~LocationState();

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

    static void moveObjectToHexagon(GameObject* object, Hexagon* hexagon);
    void handleAction(GameObject* object, int action);

    void onBackgroundClick(MouseEvent* event);
    void onKeyUp(std::shared_ptr<KeyboardEvent> event);
    void onObjectClick(MouseEvent* event);
    void onMouseDown(MouseEvent* event);
    void onKeyboardUp(std::shared_ptr<KeyboardEvent> event);
};

}

#endif // FALLTERGEIST_LOCATIONSTATE_H
