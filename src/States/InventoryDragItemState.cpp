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
#include <sstream>
#include <iostream>

// Falltergeist includes
#include "../Engine/Game.h"
#include "../Engine/Graphics/Renderer.h"
#include "../Engine/Input/Mouse.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/State.h"
#include "../Game/GameArmorItemObject.h"
#include "../Game/GameCritterObject.h"
#include "../Game/GameDudeObject.h"
#include "../Game/GameObject.h"
#include "../Game/GameObjectFactory.h"
#include "../Game/GameWeaponItemObject.h"
#include "../States/GameMenuState.h"
#include "../States/InventoryDragItemState.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"
#include "../UI/TextArea.h"
#include "../UI/ImageList.h"

// Third party includes

namespace Falltergeist
{

InventoryDragItemState::InventoryDragItemState(ImageList* itemUi) : State()
{
    _itemUi = itemUi;
}

InventoryDragItemState::~InventoryDragItemState()
{
}

void InventoryDragItemState::init()
{
    if (_initialized) return;
    State::init();

    setModal(true);
    setFullscreen(false);

}

void InventoryDragItemState::handle(std::shared_ptr<Event> event)
{
    if (auto mouseEvent = std::dynamic_pointer_cast<MouseEvent>(event))
    {
        _itemUi->setCurrentImage(1);
        _itemUi->setX(mouseEvent->x() - _itemUi->width()*0.5);
        _itemUi->setY(mouseEvent->y() - _itemUi->height()*0.5);
        if (mouseEvent->name() == "mouseup" && mouseEvent->leftButton())
        {
            _itemUi->setCurrentImage(0);
            //_itemUi->setX(100 - _itemUi->width()*0.5);
            //_itemUi->setY(115 - _itemUi->height()*0.5);
            Game::getInstance()->popState();
        }
    }
}

}

