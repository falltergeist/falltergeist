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
#include "../Engine/Event/MouseEvent.h"
#include "../Engine/Game.h"
#include "../Engine/Graphics/Animation.h"
#include "../Engine/Graphics/Renderer.h"
#include "../Engine/Input/Mouse.h"
#include "../Engine/Location.h"
#include "../Engine/LocationCamera.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/Screen.h"
#include "../Game/GameDudeObject.h"
#include "../Game/GameObject.h"
#include "../States/CursorDropdownState.h"
#include "../States/ExitConfirmState.h"
#include "../States/GameMenuState.h"
#include "../States/InventoryState.h"
#include "../States/LocationState.h"
#include "../States/MainMenuState.h"
#include "../States/SkilldexState.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"
#include "../UI/SmallCounter.h"
#include "../UI/TextArea.h"

// Third party includes

namespace Falltergeist
{

LocationState::LocationState() : State()
{
}

LocationState::~LocationState()
{
}

void LocationState::init()
{
    if (initialized()) return;
    State::init();

    auto game = Game::getInstance();

    game->mouse()->setType(Mouse::ACTION);

    _location = std::shared_ptr<Location>(new Location(ResourceManager::mapFileType("maps/artemple.map")));
    //_location = new Location(_game->resourceManager()->mapFileType("maps/sftanker.map"));

    _floor = std::shared_ptr<Image>(new Image(_location->tilesFloor()));
    _floor->addEventHandler("keyup", this, (EventRecieverMethod) &LocationState::onKeyboardUp);
    _roof = std::shared_ptr<Image>(new Image(_location->tilesRoof()));
    //_background->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &LocationState::onBackgroundClick);

    // PLAYER PANEL
    // player panel background
    _panelUIs.push_back(std::shared_ptr<Image>(new Image("art/intrface/iface.frm")));

    auto panelX = (game->renderer()->width() - 640)*0.5;   // 640 -- X size of panel
    auto panelY = game->renderer()->height() - 99;         //  99 -- Y size of panel

    _panelUIs.back()->setX(panelX);
    _panelUIs.back()->setY(panelY);
    _panelUIs.back()->addEventHandler("mouseleftdown", this, (EventRecieverMethod) &LocationState::onPanelMouseDown);

    // change hand button
    _panelUIs.push_back(std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_BIG_RED_CIRCLE, panelX+218, panelY+5)));
    _panelUIs.back()->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &LocationState::onChangeHandButtonClick);

    // inventory button
    _panelUIs.push_back(std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_PANEL_INVENTORY, panelX+211, panelY+40)));
    _panelUIs.back()->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &LocationState::onInventoryButtonClick);

    // options button
    _panelUIs.push_back(std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_PANEL_OPTIONS, panelX+210, panelY+61)));
    _panelUIs.back()->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &LocationState::onOptionsButtonClick);

    // attack button
    _panelUIs.push_back(std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_PANEL_ATTACK, panelX+267, panelY+25)));

    // hit points
    auto hitPoints = std::shared_ptr<SmallCounter>(new SmallCounter(panelX+471, panelY+40));
    hitPoints->setNumber(Game::getInstance()->player()->hitPoints());
    _panelUIs.push_back(hitPoints);

    // armor class
    auto armorClass = std::shared_ptr<SmallCounter>(new SmallCounter(panelX+472, panelY+76));
    armorClass->setNumber(Game::getInstance()->player()->armorClass());
    _panelUIs.push_back(armorClass);


    // skilldex button
    _panelUIs.push_back(std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_BIG_RED_CIRCLE, panelX+523, panelY+5)));
    _panelUIs.back()->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &LocationState::onSkilldexButtonClick);

    // map button
    _panelUIs.push_back(std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_PANEL_MAP, panelX+526, panelY+39)));

    // cha button
    _panelUIs.push_back(std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_PANEL_CHA, panelX+526, panelY+58)));

    // pip button
    _panelUIs.push_back(std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_PANEL_PIP, panelX+526, panelY+77)));
}

void LocationState::onMouseDown(std::shared_ptr<MouseEvent> event)
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
    auto game = Game::getInstance();
    game->pushState(state);

}

void LocationState::onBackgroundClick(std::shared_ptr<MouseEvent> event)
{
}

void LocationState::onObjectClick(std::shared_ptr<MouseEvent> event)
{
}

void LocationState::onKeyUp(std::shared_ptr<KeyboardEvent> event)
{
}

void LocationState::generateUi()
{
    _ui.clear();
    add(_floor);

    for (auto object : *_location->objectsToRender())
    {
        add(object->ui());
    }

     //add(_roof);

    _floor->setX(-_location->camera()->x());
    _floor->setY(-_location->camera()->y());
    //_roof->setX(-_location->camera()->x());
    //_roof->setY(-_location->camera()->y() - 100);

    for(auto object : *_location->objectsToRender())
    {
        object->ui()->removeEventHandlers("mouseleftdown");
        object->ui()->addEventHandler("mouseleftdown", object.get(), (EventRecieverMethod) &LocationState::onMouseDown);
        //object->ui()->removeEventHandlers("mouseleftclick");
        //object->ui()->addEventHandler("mouseleftclick", object, (EventRecieverMethod) &LocationState::onObjectClick);
        //object->surface()->setOwner(object);
    }

    for (auto ui : _panelUIs)
    {
        add(ui);
    }
}

void LocationState::think()
{
    State::think();
    if (!_location) return;

     _location->think();

     // location scrolling
     if (_scrollTicks + 10 < SDL_GetTicks())
     {
         _scrollTicks = SDL_GetTicks();
         unsigned int scrollDelta = 5;
         Game::getInstance()->mouse()->setType(Mouse::ACTION);
         if (_scrollLeft)
         {
             _location->camera()->setXPosition(_location->camera()->xPosition() - scrollDelta);
             Game::getInstance()->mouse()->setType(Mouse::SCROLL_W);
         }
         if (_scrollRight)
         {
             _location->camera()->setXPosition(_location->camera()->xPosition() + scrollDelta);
             Game::getInstance()->mouse()->setType(Mouse::SCROLL_E);
         }
         if (_scrollTop)
         {
             _location->camera()->setYPosition(_location->camera()->yPosition() - scrollDelta);
             Game::getInstance()->mouse()->setType(Mouse::SCROLL_N);
         }
         if (_scrollBottom)
         {
             _location->camera()->setYPosition(_location->camera()->yPosition() + scrollDelta);
             Game::getInstance()->mouse()->setType(Mouse::SCROLL_S);
         }

         if (_scrollLeft && _scrollTop)
         {
             Game::getInstance()->mouse()->setType(Mouse::SCROLL_NW);
         }
         if (_scrollLeft && _scrollBottom)
         {
             Game::getInstance()->mouse()->setType(Mouse::SCROLL_SW);
         }
         if (_scrollRight && _scrollTop)
         {
             Game::getInstance()->mouse()->setType(Mouse::SCROLL_NE);
         }
         if (_scrollRight && _scrollBottom)
         {
             Game::getInstance()->mouse()->setType(Mouse::SCROLL_SE);
         }

     }

     generateUi();
}

void LocationState::handle(std::shared_ptr<Event> event)
{
    if (auto mouseEvent = std::dynamic_pointer_cast<MouseEvent>(event))
    {
        auto game = Game::getInstance();
        unsigned int scrollArea = 8;
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

std::shared_ptr<Location> LocationState::location()
{
    return _location;
}

void LocationState::onChangeHandButtonClick(std::shared_ptr<MouseEvent> event)
{
    std::cout << "Change Hand!\n";
}

void LocationState::onPanelMouseDown(std::shared_ptr<MouseEvent> event)
{
    event->setHandled(true);
}

void LocationState::onInventoryButtonClick(std::shared_ptr<MouseEvent> event)
{
    Game::getInstance()->pushState(std::shared_ptr<InventoryState>(new InventoryState()));
}

void LocationState::onOptionsButtonClick(std::shared_ptr<MouseEvent> event)
{
    Game::getInstance()->pushState(std::shared_ptr<GameMenuState>(new GameMenuState()));
}

void LocationState::onSkilldexButtonClick(std::shared_ptr<MouseEvent> event)
{
    Game::getInstance()->pushState(std::shared_ptr<SkilldexState>(new SkilldexState()));
}

void LocationState::onKeyboardUp(std::shared_ptr<KeyboardEvent> event)
{
    if (event->keyCode() == SDLK_F10)
    {
        Game::getInstance()->pushState(std::shared_ptr<ExitConfirmState>(new ExitConfirmState()));
        //event->setHandled(true);
    }
}


}
