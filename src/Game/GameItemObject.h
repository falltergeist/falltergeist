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

#ifndef FALLTERGEIST_GAMEITEMOBJECT_H
#define FALLTERGEIST_GAMEITEMOBJECT_H

// C++ standard includes

// Falltergeist includes
#include "../Game/GameObject.h"

// Third party includes

namespace Falltergeist
{

class GameItemObject : public GameObject
{
protected:
    unsigned int _amount = 1;
    unsigned int _weight = 0;
    unsigned int _inventoryFID = 0;
public:
    GameItemObject();
    virtual ~GameItemObject();

    unsigned int amount();
    void setAmount(unsigned int value);

    unsigned int weight();
    void setWeight(unsigned int value);

    unsigned int inventoryFID();
    void setInventoryFID(unsigned int value);

    std::shared_ptr<ActiveUI> inventoryUi();
};

}
#endif // FALLTERGEIST_GAMEITEMOBJECT_H
