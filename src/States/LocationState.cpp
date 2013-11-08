/*
 * Copyright 2012-2013 Falltergeist Developers.
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

// C++ standard includes
#include <cmath>

// Falltergeist includes
#include "../Engine/Animation.h"
#include "../Engine/Game.h"
#include "../Engine/Screen.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/InteractiveSurface.h"
#include "../Engine/Location.h"
#include "../Engine/LocationCamera.h"
#include "../Game/GameObject.h"
#include "../States/LocationState.h"
#include "../States/CursorDropdownState.h"
#include "../Engine/Mouse.h"
#include "../UI/TextArea.h"

// Third party includes

namespace Falltergeist
{

LocationState::LocationState() : State()
{
}

LocationState::~LocationState()
{
    _game->setLocation(0);
}

void LocationState::init()
{
    if (initialized()) return;
    State::init();
    setScrollable(true);

    _location = new Location(_game->resourceManager()->mapFileType("maps/artemple.map"));
    _game->setLocation(_location);
    _game->mouse()->setType(Mouse::ACTION);
    _background = new InteractiveSurface(_location->tilesBackground());
    _background->onLeftButtonClick((EventHandler) &LocationState::onBackgroundClick);
    //_background->onKeyboardRelease((EventHandler) &LocationState::onKeyboardRelease);

    add(_background);
}

void LocationState::onMouseDown(Event* event)
{
    auto state = new CursorDropdownState({ Mouse::ICON_ROTATE, Mouse::ICON_USE, Mouse::ICON_SKILL, Mouse::ICON_INVENTORY, Mouse::ICON_UNLOAD, Mouse::ICON_CANCEL});
    state->setObject(event->sender()->owner());
    _game->pushState(state);
}

void LocationState::onBackgroundClick(Event * event)
{
    int x = _location->camera()->x() + event->x();
    int y = _location->camera()->y() + event->y();
    unsigned int hexagon = _location->positionToHexagon(x, y);

    std::cout << std::dec << x << " : " << y << " > " << hexagon << std::endl;
}

void LocationState::onObjectClick(Event* event)
{
    auto object = dynamic_cast<GameObject*>(event->sender());
    if (object)
    {
        std::cout << "object:" << object->PID() << std::endl;
        //std::cout << object->descriptionId() << std::endl;
        //std::cout << object->description() << std::endl;
    }
}

void LocationState::onKeyboardRelease(Event * event)
{
    if (event->keyCode() == SDLK_g) // "g" button - enable\disable hex grid
    {
        if (_hexagonalGrid)
        {
            _hexagonalGrid = false;
        }
        else
        {
            _hexagonalGrid = true;
        }
    }
}

void LocationState::blit()
{

    State::blit();

    if (_location == 0) return;

    _drawHexagonalGrid();


    for (GameObject* object : *_location->objectsToRender())
    {        
        int x, y;
        if (Animation* animation = object->animationQueue()->animation())
        {
            x = Location::hexagonToX(object->position()) - animation->surfaces()->at(0)->width()/2 - _location->camera()->x();
            y = Location::hexagonToY(object->position()) - animation->surfaces()->at(0)->height() - _location->camera()->y();
            animation->setX(x);
            animation->setY(y);
            animation->blit(_game->screen()->surface());

        }
        else
        {
            auto surface = object->surface();
            x = Location::hexagonToX(object->position()) - surface->width()/2 - _location->camera()->x();
            y = Location::hexagonToY(object->position()) - surface->height() - _location->camera()->y();
            surface->setX(x);
            surface->setY(y);
            surface->blit(_game->screen()->surface());
        }
   }
}

void LocationState::_drawHexagonalGrid()
{
    if (!_hexagonalGrid) return;
    Surface * hexagon = ResourceManager::surface("art/intrface/msef000.frm");
    hexagon->setXOffset(0 - hexagon->width()/2);
    hexagon->setYOffset(0 - hexagon->height()/2);
    for (unsigned int i = 0; i != 200*200; ++i)
    {
        int x = _location->hexagonToX(i) - _location->camera()->x();
        int y = _location->hexagonToY(i) - _location->camera()->y();
        hexagon->setX(x);
        hexagon->setY(y);
        hexagon->blit(_game->screen()->surface());
    }
}

void LocationState::think()
{

    if (!_location) return;
    _location->think();

    _background->loadFromSurface(_location->tilesBackground());

    for(GameObject* object : *_location->objectsToRender())
    {

        if (Animation* animation = object->animationQueue()->animation())
        {
            animation->onLeftButtonPress((EventHandler) &LocationState::onMouseDown);
            animation->setOwner(object);
        }
        else
        {
            object->surface()->onLeftButtonPress((EventHandler) &LocationState::onMouseDown);
            object->surface()->setOwner(object);
        }
    }
}

void LocationState::handle(Event* event)
{
    if (event->isMouseEvent())
    {
        // Handle objects
        for (auto object : *_location->objectsToRender())
        {            
            if (Animation* animation = object->animationQueue()->animation())
            {
                animation->handle(event, this);
            }
            else
            {
                object->surface()->handle(event, this);
            }
        }
        State::handle(event);
    }
    else
    {
        State::handle(event);
    }
}

}
