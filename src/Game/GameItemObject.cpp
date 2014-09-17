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

// Falltergeist includes
#include "../Engine/Graphics/Animation.h"
#include "../Engine/ResourceManager.h"
#include "../Game/GameItemObject.h"
#include "../UI/Image.h"

// Third party includes

namespace Falltergeist
{

GameItemObject::GameItemObject() : GameObject()
{
    _type = TYPE_ITEM;
}

GameItemObject::~GameItemObject()
{
}

unsigned int GameItemObject::amount()
{
    return _amount;
}

void GameItemObject::setAmount(unsigned int value)
{
    _amount = value;
}

unsigned int GameItemObject::weight()
{
    return _weight;
}

void GameItemObject::setWeight(unsigned int value)
{
    _weight = value;
}

unsigned int GameItemObject::inventoryFID()
{
    return _inventoryFID;
}

void GameItemObject::setInventoryFID(unsigned int value)
{
    _inventoryFID = value;
}

std::shared_ptr<ActiveUI> GameItemObject::inventoryUi()
{
    // return image of object as it looks in inventory
    std::shared_ptr<ActiveUI> ui;

    auto frm = ResourceManager::frmFileType(this->inventoryFID());
    if (frm)
    {
        if (frm->framesPerDirection() > 1)
        {
            ui = std::shared_ptr<Animation>(new Animation(ResourceManager::FIDtoFrmName(this->inventoryFID()), orientation()));
        }
        else
        {
            ui = std::shared_ptr<Image>(new Image(frm, orientation()));
        }
    }
    return ui;
}

}

