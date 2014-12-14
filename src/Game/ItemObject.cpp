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
 */

// C++ standard includes

// Falltergeist includes
#include "../Graphics/Animation.h"
#include "../Graphics/Texture.h"
#include "../ResourceManager.h"
#include "ItemObject.h"
#include "../UI/Image.h"

// Third party includes

namespace Falltergeist
{
namespace Game
{

GameItemObject::GameItemObject() : GameObject()
{
    _type = TYPE_ITEM;
}

GameItemObject::~GameItemObject()
{
    delete _inventoryDragUi;
    delete _inventorySlotUi;
    delete _inventoryUi;
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

int GameItemObject::inventoryFID()
{
    return _inventoryFID;
}

void GameItemObject::setInventoryFID(int value)
{
    _inventoryFID = value;
}

Image* GameItemObject::inventoryDragUi()
{
    return _inventoryDragUi;
}

Image* GameItemObject::inventoryUi()
{
    return _inventoryUi;
}

Image* GameItemObject::inventorySlotUi()
{
    return _inventorySlotUi;
}

void GameItemObject::_generateUi()
{
    GameObject::_generateUi();

    if (inventoryFID() == -1) return;

    // Big unscaled image of item
    _inventoryDragUi = new Image(ResourceManager::FIDtoFrmName(inventoryFID()));

    // Small scaled image
    auto inventoryUiTexture = _inventoryDragUi->texture()->fitTo(57, 40);
    _inventoryUi = new Image(inventoryUiTexture->width(),inventoryUiTexture->height());
    _inventoryUi->setTexture(inventoryUiTexture);

    // Medium scaled image
    auto inventorySlotUiTexture = _inventoryDragUi->texture()->fitTo(88, 58);
    _inventorySlotUi = new Image(inventorySlotUiTexture->width(),inventorySlotUiTexture->height());
    _inventorySlotUi->setTexture(inventorySlotUiTexture);
}

}
}
