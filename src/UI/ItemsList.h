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

#ifndef FALLTERGEIST_UI_ITEMSLIST_H
#define FALLTERGEIST_UI_ITEMSLIST_H

// C++ standard includes

// Falltergeist includes
#include "../UI/Image.h"

// Third party includes

namespace Falltergeist
{
namespace Game
{
    class GameItemObject;
}
class InventoryItem;

class ItemsList : public ActiveUI
{
protected:
    std::vector<Game::GameItemObject*>* _items = 0;
    InventoryItem* _draggedItem = 0;
    std::vector<InventoryItem*> _inventoryItems;
    unsigned int _type = TYPE_INVENTORY;
    unsigned int _slotsNumber = 7; // Height of widget in items
    unsigned int _slotOffset = 0;
    unsigned int _slotWidth = 77;
    unsigned int _slotHeight = 40;
public:
    enum { TYPE_INVENTORY = 0, TYPE_SLOT};

    ItemsList(int x = 0, int y = 0);

    void setItems(std::vector<Game::GameItemObject*>* items);
    std::vector<Game::GameItemObject*>* items();

    std::vector<InventoryItem*>* inventoryItems();
    InventoryItem* draggedItem();

    void setSlotsNumber(unsigned int value);
    unsigned int slotsNumber();

    void setSlotOffset(unsigned int value);
    unsigned int slotOffset();

    void update();

    void scrollUp();
    void scrollDown();

    bool canScrollUp();
    bool canScrollDown();

    virtual void render();
    virtual unsigned int pixel(unsigned int x, unsigned int y);

    void onMouseLeftDown(MouseEvent* event);
    void onMouseDragStart(MouseEvent* event);
    void onMouseDrag(MouseEvent* event);
    void onMouseDragStop(MouseEvent* event);
    void onItemDragStop(MouseEvent* event);

    void addItem(InventoryItem* item, unsigned int ammount);
    void removeItem(InventoryItem* item, unsigned int ammount);

};

}
#endif // FALLTERGEIST_UI_ITEMSLIST_H
