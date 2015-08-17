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

// C++ standard includes

// Falltergeist includes
#include "../Game/ContainerItemObject.h"
#include "../Game/DudeObject.h"
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../Logger.h"
#include "../State/Container.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"
#include "../UI/ItemsList.h"
#include "../Input/Mouse.h"

// Third party includes

namespace Falltergeist
{
namespace State
{

Container::Container() : State()
{
}

Container::~Container()
{
}

void Container::init()
{
    if (_initialized) return;

    setModal(true);
    setFullscreen(false);

    auto game = Game::getInstance();

    setX((game->renderer()->width()  - 537)/2);
    setY((game->renderer()->height() - 376)/2);

    addUI("background", new Image("art/intrface/loot.frm"));

    addUI("button_done", new ImageButton(ImageButton::Type::SMALL_RED_CIRCLE, 478, 331));
    getActiveUI("button_done")->addEventHandler("mouseleftclick", [this](Event::Event* event){ this->onDoneButtonClick(dynamic_cast<Event::Mouse*>(event)); });


    // TAKEALL
    // invmadn
    // invmaup

    // invupds
    // invupin
    // invupout


    auto dudeList = new ItemsList(170, 35);
    dudeList->setItems(Game::getInstance()->player()->inventory());
    addUI(dudeList);

    auto containerList = new ItemsList(292, 35);
    containerList->setItems(object()->inventory());
    addUI(containerList);

    dudeList->addEventHandler("itemdragstop", [containerList](Event::Event* event){ containerList->onItemDragStop(dynamic_cast<Event::Mouse*>(event)); });
    containerList->addEventHandler("itemdragstop", [dudeList](Event::Event* event){ dudeList->onItemDragStop(dynamic_cast<Event::Mouse*>(event)); });

}

Game::ContainerItemObject* Container::object()
{
    return _object;
}

void Container::setObject(Game::ContainerItemObject* object)
{
    _object = object;
}

void Container::onDoneButtonClick(Event::Mouse* event)
{
    Game::getInstance()->popState();
}

void Container::onStateActivate(Event::State* event)
{
    Game::getInstance()->mouse()->pushState(Mouse::Cursor::BIG_ARROW);
}

void Container::onStateDeactivate(Event::State* event)
{
    Game::getInstance()->mouse()->popState();
}

void Container::onKeyDown(Event::Keyboard* event)
{
    if (event->keyCode() == SDLK_ESCAPE)
    {
        Game::getInstance()->popState();
    }
}

}
}
