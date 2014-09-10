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

// C++ standard includes
#include <cmath>
#include <iostream>

// Falltergeist includes
#include "../Engine/Graphics/Animation.h"
#include "../Engine/Game.h"
#include "../Engine/Screen.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/InteractiveSurface.h"
#include "../Engine/Location.h"
#include "../Engine/LocationCamera.h"
#include "../Game/GameObject.h"
#include "../States/LocationState.h"
#include "../States/CursorDropdownState.h"
#include "../Engine/Input/Mouse.h"
#include "../UI/TextArea.h"
#include "../UI/Image.h"
#include "../Engine/Event/MouseEvent.h"
#include "../Engine/Graphics/Renderer.h"

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

    _game->mouse()->setType(Mouse::ACTION);

    _location = new Location(_game->resourceManager()->mapFileType("maps/artemple.map"));
    //_location = new Location(_game->resourceManager()->mapFileType("maps/sftanker.map"));
    _game->setLocation(_location);
    _floor = new Image(_location->tilesFloor());
    _roof = new Image(_location->tilesRoof());
    //_background->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &LocationState::onBackgroundClick);
    //_background->addEventHandler("keyup", this, (EventRecieverMethod) &LocationState::onKeyUp);

    //*/
}

void LocationState::onMouseDown(MouseEvent* event)
{
    auto object = dynamic_cast<GameObject*>(event->reciever());
    if (!object) return;

    std::vector<int> icons;

    switch(object->type())
    {
        case GameObject::TYPE_DUDE:
            icons.push_back(Mouse::ICON_ROTATE);
            break;
        case GameObject::TYPE_SCENERY:
            icons.push_back(Mouse::ICON_LOOK);
            break;
        case GameObject::TYPE_CRITTER:
            icons.push_back(Mouse::ICON_TALK);
            break;
        default:
            return;
    }
    icons.push_back(Mouse::ICON_INVENTORY);
    icons.push_back(Mouse::ICON_SKILL);
    icons.push_back(Mouse::ICON_CANCEL);

    auto state = std::shared_ptr<CursorDropdownState>(new CursorDropdownState(icons));
    state->setObject(object);
    auto game = &Game::getInstance();
    game->pushState(state);

}

void LocationState::onBackgroundClick(MouseEvent* event)
{
    int x = _location->camera()->x() + event->x();
    int y = _location->camera()->y() + event->y();
    unsigned int hexagon = _location->positionToHexagon(x, y);

    //std::cout << std::dec << x << " : " << y << " > " << hexagon << std::endl;
}

void LocationState::onObjectClick(MouseEvent* event)
{
    auto obj = dynamic_cast<GameObject*>(event->reciever());
    std::cout << obj << std::endl;
    return;
    auto surface = dynamic_cast<InteractiveSurface*>(event->emitter());
    if (!surface) return;
    auto object = dynamic_cast<GameObject*>((GameObject*)surface->owner());
    if (!object) return;
        std::cout << "object: " << object->PID()
                  << "name: " << object->name()
                  << "description: " << object->description() << std::endl;
}

void LocationState::onKeyUp(KeyboardEvent * event)
{
}

void LocationState::think()
{
    State::think();
    if (!_location) return;

     _location->think();

     // Скролим локацию
     if (_scrollTicks + 10 < SDL_GetTicks())
     {
         _scrollTicks = SDL_GetTicks();
         unsigned int scrollDelta = 5;
         if (_scrollLeft) _location->camera()->setXPosition(_location->camera()->xPosition() - scrollDelta);
         if (_scrollRight) _location->camera()->setXPosition(_location->camera()->xPosition() + scrollDelta);
         if (_scrollTop) _location->camera()->setYPosition(_location->camera()->yPosition() - scrollDelta);
         if (_scrollBottom) _location->camera()->setYPosition(_location->camera()->yPosition() + scrollDelta);
     }


    _ui.clear();
    _activeUi.clear();
    add(_floor);

    for (auto it = _location->objectsToRender()->begin(); it != _location->objectsToRender()->end(); ++it)
    {
        GameObject* object = *it;

        ActiveUI* ui = dynamic_cast<ActiveUI*>(object->ui());
        ui->setX(Location::hexagonToX(object->position()) -_location->camera()->x());
        ui->setY(Location::hexagonToY(object->position())-_location->camera()->y());
        add(ui);
    }

     //add(_roof);



    _floor->setX(-_location->camera()->x());
    _floor->setY(-_location->camera()->y());
    _roof->setX(-_location->camera()->x());
    _roof->setY(-_location->camera()->y() - 100);




    for(GameObject* object : *_location->objectsToRender())
    {
        object->ui()->removeEventHandlers("mouseleftdown");
        object->ui()->addEventHandler("mouseleftdown", object, (EventRecieverMethod) &LocationState::onMouseDown);
        //object->ui()->removeEventHandlers("mouseleftclick");
        //object->ui()->addEventHandler("mouseleftclick", object, (EventRecieverMethod) &LocationState::onObjectClick);
        //object->surface()->setOwner(object);
    }
}

void LocationState::handle(Event* event)
{
    if (MouseEvent* mouseEvent = dynamic_cast<MouseEvent*>(event))
    {
        auto game = &Game::getInstance();
        auto scrollArea = 5;
        if (mouseEvent->name() == "mousemove")
        {
            _scrollLeft = mouseEvent->x() < scrollArea ? true : false;
            _scrollRight = mouseEvent->x() > game->renderer()->width()- scrollArea ? true : false;
            _scrollTop = mouseEvent->y() < scrollArea ? true : false;
            _scrollBottom = mouseEvent->y() > game->renderer()->height() - scrollArea ? true : false;
        }
    }
    State::handle(event);
}

}
