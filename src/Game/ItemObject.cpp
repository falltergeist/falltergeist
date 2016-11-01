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
#include "../Game/ItemObject.h"

// C++ standard includes
#include <memory>

// Falltergeist includes
#include "../Graphics/Texture.h"
#include "../ResourceManager.h"
#include "../UI/Animation.h"
#include "../UI/Image.h"

// Third party includes

namespace Falltergeist
{
namespace Game
{

using namespace Base;

ItemObject::ItemObject() : Object()
{
    _type = Type::ITEM;
}

ItemObject::~ItemObject()
{
}

unsigned int ItemObject::amount() const
{
    return _amount;
}

void ItemObject::setAmount(unsigned int value)
{
    _amount = value;
}

unsigned int ItemObject::weight() const
{
    return _weight;
}

void ItemObject::setWeight(unsigned int value)
{
    _weight = value;
}

int ItemObject::inventoryFID() const
{
    return _inventoryFID;
}

void ItemObject::setInventoryFID(int value)
{
    _inventoryFID = value;
}

UI::Image* ItemObject::inventoryDragUi() const
{
    return _inventoryDragUi.get();
}

void ItemObject::setVolume(unsigned int volume)
{
    _volume = volume;
}

unsigned int ItemObject::volume() const
{
    return _volume;
}

UI::Image* ItemObject::inventoryUi() const
{
    return _inventoryUi.get();
}

UI::Image* ItemObject::inventorySlotUi() const
{
    return _inventorySlotUi.get();
}

void ItemObject::_generateUi()
{
    Object::_generateUi();

    if (inventoryFID() == -1) return;

    // Big unscaled image of item
    _inventoryDragUi = std::make_unique<UI::Image>(ResourceManager::getInstance()->FIDtoFrmName(inventoryFID()));
    _inventoryUi = std::make_unique<UI::Image>(ResourceManager::getInstance()->FIDtoFrmName(inventoryFID()));
    _inventorySlotUi = std::make_unique<UI::Image>(ResourceManager::getInstance()->FIDtoFrmName(inventoryFID()));
}

ItemObject::Subtype ItemObject::subtype() const
{
    return _subtype;
}

}
}
