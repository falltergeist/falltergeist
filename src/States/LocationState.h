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
class Image;
class InteractiveSurface;
class Location;
class LocationCamera;
class VMStackValue;
class VM;

class LocationState : public State
{
protected:

    // Timers
    unsigned int _lastObjectsToRenderCheck = 0;
    unsigned int _scrollTicks = 0;
    unsigned int _scriptsTicks = 0;

    std::shared_ptr<VM> _locationScript;

    bool _locationEnter = true;

    std::vector<std::shared_ptr<Hexagon>> _hexagons;
    std::vector<std::shared_ptr<Hexagon>> _hexagonsWithObjects;

    unsigned int _currentElevation = 0;
    std::shared_ptr<LocationCamera> _camera;

    std::vector<std::shared_ptr<GameObject>> _objectsToRender;

    std::vector<int> _MVARS;
    std::map<std::string, std::shared_ptr<VMStackValue>> _EVARS;


    std::shared_ptr<Image> _floorFull;
    std::shared_ptr<Image> _floor;
    std::shared_ptr<Image> _roofFull;
    std::vector<std::shared_ptr<ActiveUI>> _panelUIs;    
    std::vector<std::shared_ptr<ActiveUI>> _floatMessages;

    bool _scrollLeft = false;
    bool _scrollRight = false;
    bool _scrollTop = false;
    bool _scrollBottom = false;

    void _initPanel();

public:
    LocationState();
    ~LocationState();

    void setLocation(std::string name);

    virtual void init();
    virtual void think();
    virtual void handle(std::shared_ptr<Event> event);

    std::vector<std::shared_ptr<Hexagon>>* hexagons();
    std::shared_ptr<LocationCamera> camera();

    void checkObjectsToRender();
    void checkHexagonsWidthObjects();
    void generateUi();

    void setMVAR(unsigned int number, int value);
    int MVAR(unsigned int number);

    std::map<std::string, std::shared_ptr<VMStackValue>>* EVARS();

    static void moveObjectToHexagon(std::shared_ptr<GameObject> object, std::shared_ptr<Hexagon> hexagon, bool calculateHexagons = true);
    void handleAction(GameObject* object, int action);

    void onBackgroundClick(std::shared_ptr<MouseEvent> event);
    void onKeyUp(std::shared_ptr<KeyboardEvent> event);
    void onObjectClick(std::shared_ptr<MouseEvent> event);
    void onMouseDown(std::shared_ptr<MouseEvent> event);
    void onChangeHandButtonClick(std::shared_ptr<MouseEvent> event);
    void onPanelMouseDown(std::shared_ptr<MouseEvent> event);
    void onInventoryButtonClick(std::shared_ptr<MouseEvent> event);
    void onOptionsButtonClick(std::shared_ptr<MouseEvent> event);
    void onSkilldexButtonClick(std::shared_ptr<MouseEvent> event);
    void onKeyboardUp(std::shared_ptr<KeyboardEvent> event);
    void onPipBoyButtonClick(std::shared_ptr<MouseEvent> event);
};

}

#endif // FALLTERGEIST_LOCATIONSTATE_H
