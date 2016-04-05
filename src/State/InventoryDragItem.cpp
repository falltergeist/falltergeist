/*
 * Copyright 2012-2016 Falltergeist Developers.
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

// Related headers
#include "../State/InventoryDragItem.h"

// C++ standard includes
#include <sstream>

// Falltergeist includes
#include "../Game/Game.h"
#include "../Game/ArmorItemObject.h"
#include "../Game/CritterObject.h"
#include "../Game/DudeObject.h"
#include "../Game/Object.h"
#include "../Game/ObjectFactory.h"
#include "../Game/WeaponItemObject.h"
#include "../Graphics/Renderer.h"
#include "../Input/Mouse.h"
#include "../ResourceManager.h"
#include "../State/GameMenu.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"
#include "../UI/ImageList.h"
#include "../UI/TextArea.h"

// Third party includes

namespace Falltergeist
{
    namespace State
    {
        InventoryDragItem::InventoryDragItem(UI::ImageList* itemUi) : State()
        {
            _itemUi = itemUi;
        }

        InventoryDragItem::~InventoryDragItem()
        {
        }

        void InventoryDragItem::init()
        {
            if (_initialized) return;
            State::init();

            setModal(true);
            setFullscreen(false);

        }

        void InventoryDragItem::handle(Event::Event* event)
        {
            if (auto mouseEvent = dynamic_cast<Event::Mouse*>(event))
            {
                _itemUi->setCurrentImage(1);
                _itemUi->setPosition(mouseEvent->position() - _itemUi->size() / 2);
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
}
