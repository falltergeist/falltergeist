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

#ifndef FALLTERGEIST_UI_INVENTORYITEM_H
#define FALLTERGEIST_UI_INVENTORYITEM_H

// C++ standard includes

// Falltergeist includes
#include "../UI/Base.h"

// Third party includes
#include <libfalltergeist/Enums.h>

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

class InventoryItem : public Falltergeist::UI::Base
{
public:
    enum class Type
    {
        INVENTORY = 0,
        SLOT,
        DRAG
    };

    InventoryItem(Game::ItemObject* item, const Point& pos = Point());
    ~InventoryItem() override;

    Type type() const;
    void setType(Type value);

    Game::ItemObject* item();
    void setItem(Game::ItemObject* item);

    void render(bool eggTransparency = false) override;
    unsigned int pixel(const Point& pos) override;
    Graphics::Texture* texture() const override;
    Size size() const override;

    void onMouseLeftDown(Event::Mouse* event);
    void onMouseDragStart(Event::Mouse* event);
    void onMouseDrag(Event::Mouse* event);
    void onMouseDragStop(Event::Mouse* event);

    void onArmorDragStop(Event::Mouse* event);
    void onHandDragStop(Event::Mouse* event, HAND hand);

    Event::MouseHandler& itemDragStopHandler();

protected:
    Game::ItemObject* _item = nullptr;
    Type _type = Type::INVENTORY;
    Type _oldType = Type::INVENTORY;

    Event::MouseHandler _itemDragStopHandler;
};

}
}
#endif // FALLTERGEIST_UI_INVENTORYITEM_H
