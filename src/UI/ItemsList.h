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

#ifndef FALLTERGEIST_UI_ITEMSLIST_H
#define FALLTERGEIST_UI_ITEMSLIST_H

// C++ standard includes
#include <vector>

// Falltergeist includes
#include "../UI/Base.h"
#include "../UI/InventoryItem.h"

// Third party includes

namespace Falltergeist
{
namespace Event
{
    class Mouse;
}
namespace Game
{
    class ItemObject;
}
namespace UI
{

class ItemsList : public Falltergeist::UI::Base
{
public:
    ItemsList(const Point& pos);

    void setItems(std::vector<Game::ItemObject*>* items);
    std::vector<Game::ItemObject*>* items();

    std::vector<std::unique_ptr<InventoryItem>>& inventoryItems();
    InventoryItem* draggedItem();

    /*void setSlotsNumber(unsigned int value);
    unsigned int slotsNumber();

    void setSlotOffset(unsigned int value);
    unsigned int slotOffset();*/

    void update();

    void scrollUp();
    void scrollDown();

    bool canScrollUp();
    bool canScrollDown();

    unsigned int slotsNumber();
    unsigned int slotOffset();

    virtual void render(bool eggTransparency = false) override;

    void onMouseLeftDown(Event::Mouse* event);
    void onMouseDragStart(Event::Mouse* event);
    void onMouseDrag(Event::Mouse* event);
    void onMouseDragStop(Event::Mouse* event);
    void onItemDragStop(Event::Mouse* event, HAND hand);
    void onItemDragStop(Event::Mouse* event);

    void addItem(InventoryItem* item, unsigned int ammount);
    void removeItem(InventoryItem* item, unsigned int ammount);

    Event::MouseHandler& itemDragStopHandler();
    Event::Handler& itemsListModifiedHandler();


    virtual bool opaque(const Point &pos) override;

protected:
    std::vector<Game::ItemObject*>* _items = nullptr;
    InventoryItem* _draggedItem = nullptr;
    std::vector<std::unique_ptr<InventoryItem>> _inventoryItems;
    InventoryItem::Type _type = InventoryItem::Type::INVENTORY;
    unsigned int _slotsNumber = 7; // Height of widget in items
    unsigned int _slotOffset = 0;
    unsigned int _slotWidth = 77;
    unsigned int _slotHeight = 40;

    Event::MouseHandler _itemDragStopHandler;
    Event::Handler _itemsListModifiedHandler;
};

}
}
#endif // FALLTERGEIST_UI_ITEMSLIST_H
