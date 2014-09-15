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
class Location;
class Animation;
class InteractiveSurface;
class GameObject;
class Image;

class LocationState : public State
{
protected:
    std::shared_ptr<Location> _location;
    std::shared_ptr<Image> _floor;
    std::shared_ptr<Image> _roof;
    std::vector<std::shared_ptr<ActiveUI>> _panelUIs;
    unsigned int _direction;
    unsigned int _cameraX;
    unsigned int _cameraY;
    unsigned int _scrollTicks = 0;
    bool _scrollLeft = false;
    bool _scrollRight = false;
    bool _scrollTop = false;
    bool _scrollBottom = false;
public:
    LocationState();
    ~LocationState();

    std::shared_ptr<Location> location();

    virtual void init();
    virtual void think();
    virtual void handle(std::shared_ptr<Event> event);

    void generateUi();

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
