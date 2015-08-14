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
#include "../Graphics/ActiveUI.h"

// Third party includes

namespace Falltergeist
{
namespace Game
{
    class GameItemObject;
}

class InventoryItem : public ActiveUI
{
protected:
    Game::GameItemObject* _item = 0;
    unsigned int _type = TYPE_INVENTORY;
    unsigned int _oldType = TYPE_INVENTORY;
public:
    enum { TYPE_INVENTORY = 0, TYPE_SLOT, TYPE_DRAG };

    InventoryItem(Game::GameItemObject* item, int x = 0, int y = 0);


    unsigned int type() const;
    void setType(unsigned int value);

    Game::GameItemObject* item();
    void setItem(Game::GameItemObject* item);

    virtual void render(bool eggTransparency = false);
    virtual unsigned int pixel(unsigned int x, unsigned int y);
    Texture* texture() const override;
    unsigned int width() const override;
    unsigned int height() const override;

    void onMouseLeftDown(MouseEvent* event);
    void onMouseDragStart(MouseEvent* event);
    void onMouseDrag(MouseEvent* event);
    void onMouseDragStop(MouseEvent* event);

    void onArmorDragStop(MouseEvent* event);
    void onHandDragStop(MouseEvent* event);



};

}
#endif // FALLTERGEIST_UI_INVENTORYITEM_H
