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
#include "../Game/ArmorItemObject.h"
#include "../Game/DudeObject.h"
#include "../Game/Game.h"
#include "../Game/ItemObject.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/Texture.h"
#include "../Logger.h"
#include "../UI/InventoryItem.h"
#include "../UI/ItemsList.h"

// Third party includes

namespace Falltergeist
{

ItemsList::ItemsList(int x, int y) : ActiveUI(x, y)
{
    _texture = new Texture(_slotWidth, _slotHeight * _slotsNumber);
    _texture->fill(0x000000FF);

    addEventHandler("mouseleftdown", [this](Event* event){ this->onMouseLeftDown(dynamic_cast<MouseEvent*>(event)); });
    addEventHandler("mousedragstart", [this](Event* event){ this->onMouseDragStart(dynamic_cast<MouseEvent*>(event)); });
    addEventHandler("mousedrag", [this](Event* event){ this->onMouseDrag(dynamic_cast<MouseEvent*>(event)); });
    addEventHandler("mousedragstop", [this](Event* event){ this->onMouseDragStop(dynamic_cast<MouseEvent*>(event)); });
}

void ItemsList::setItems(std::vector<Game::GameItemObject *>* items)
{
    _items = items;
    update();
}

std::vector<Game::GameItemObject*>* ItemsList::items()
{
    return _items;
}

void ItemsList::update()
{
    while(!inventoryItems()->empty())
    {
        delete inventoryItems()->back();
        inventoryItems()->pop_back();
    }

    for (unsigned int i = _slotOffset; i < items()->size() && i != _slotOffset + _slotsNumber; i++)
    {
        auto inventoryItem = new InventoryItem(items()->at(i));
        inventoryItems()->push_back(inventoryItem);
    }
}

void ItemsList::render(bool eggTransparency, bool grayscale)
{
    //ActiveUI::render();
    unsigned int i = 0;
    for (auto item : *inventoryItems())
    {
        item->setX(x());
        item->setY(y() + _slotHeight*i);
        item->render();
        i++;
    }
}

unsigned int ItemsList::pixel(unsigned int x, unsigned int y)
{
    unsigned int i = 0;
    for (auto item : *inventoryItems())
    {
        unsigned int pixel = item->pixel(x, y - _slotHeight*i);
        if (pixel) return pixel;
        i++;
    }
    return 0;
}

std::vector<InventoryItem*>* ItemsList::inventoryItems()
{
    return &_inventoryItems;
}

void ItemsList::onMouseLeftDown(MouseEvent* event)
{
    Logger::critical() << "mouseleftdown" << std::endl;
}

void ItemsList::onMouseDragStart(MouseEvent* event)
{
    unsigned int index = (event->y() - y())/_slotHeight;
    _draggedItem = inventoryItems()->at(index);
    _draggedItem->setType(InventoryItem::TYPE_DRAG);
    _draggedItem->setX(event->x());
    _draggedItem->setY(event->y());
    Logger::critical() << "mousedragstart at " << index << " (" << _draggedItem->item()->name() << ")" << std::endl;
}

void ItemsList::onMouseDrag(MouseEvent* event)
{
    _draggedItem->setXOffset(_draggedItem->xOffset() + event->xOffset());
    _draggedItem->setYOffset(_draggedItem->yOffset() + event->yOffset());
    Logger::critical() << "mousedrag" << std::endl;
}

void ItemsList::onMouseDragStop(MouseEvent* event)
{
    _draggedItem->setXOffset(0);
    _draggedItem->setYOffset(0);
    _draggedItem->setType(_type);
    auto itemevent = new MouseEvent("itemdragstop");
    itemevent->setX(event->x());
    itemevent->setY(event->y());
    itemevent->setEmitter(this);
    emitEvent(itemevent);
    delete itemevent;
    _draggedItem = 0;
    Logger::critical() << "mousedragstop" << std::endl;
}

void ItemsList::onItemDragStop(MouseEvent* event)
{
    Logger::critical() << "itemdragstop" << std::endl;

    // check if mouse is in this item list

    int x = event->x() - this->x();
    int y = event->y() - this->y();


    if (x < 0 || x > _slotWidth) return;
    if (y < 0 || y > _slotHeight*_slotsNumber) return;

    if (auto itemsList = dynamic_cast<ItemsList*>(event->emitter()))
    {
        // @todo create addItem method
        this->addItem(itemsList->draggedItem(), 1);

        itemsList->removeItem(itemsList->draggedItem(), 1);
        itemsList->update();
    }

    if (auto inventoryItem = dynamic_cast<InventoryItem*>(event->emitter()))
    {
        // @todo create addItem method
        this->addItem(inventoryItem, 1);

        if (dynamic_cast<Game::GameArmorItemObject*>(inventoryItem->item()) && inventoryItem->type() == InventoryItem::TYPE_SLOT)
        {
            Game::getInstance()->player()->setArmorSlot(nullptr);
        }
        inventoryItem->setItem(0);
    }

    Logger::critical() << "IN!" << std::endl;
}

InventoryItem* ItemsList::draggedItem()
{
    return _draggedItem;
}

void ItemsList::addItem(InventoryItem* item, unsigned int amount)
{
    _items->push_back(item->item());
    this->update();
}

void ItemsList::removeItem(InventoryItem* item, unsigned int amount)
{
    for (auto it = _items->begin(); it != _items->end(); ++it)
    {
        Game::GameItemObject* object = *it;
        if (object == item->item())
        {
            _items->erase(it);
            break;
        }
    }
    this->update();
}

bool ItemsList::canScrollUp()
{
    if(_slotOffset > 0)
    {
        return true;
    }
    return false;
}

bool ItemsList::canScrollDown()
{
    if(_slotOffset + _slotsNumber >= _items->size())
    {
        return false;
    }
    return true;
}

void ItemsList::scrollUp()
{
    _slotOffset--;
    this->update();
}

void ItemsList::scrollDown()
{
    _slotOffset++;
    this->update();
}

}
