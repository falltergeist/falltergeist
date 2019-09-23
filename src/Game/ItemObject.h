/*
 * Copyright 2012-2018 Falltergeist Developers.
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

#ifndef FALLTERGEIST_GAME_ITEMOBJECT_H
#define FALLTERGEIST_GAME_ITEMOBJECT_H

// C++ standard includes

// Falltergeist includes
#include "../Game/Object.h"

// Third party includes

namespace Falltergeist
{
    namespace Game
    {
        /**
         * Item. Can be placed inside other object inventories (critters and containers)
         */
        class ItemObject : public Object
        {
            public:
                enum class Subtype
                {
                    ARMOR = 0,
                    CONTAINER,
                    DRUG,
                    WEAPON,
                    AMMO,
                    MISC,
                    KEY
                };

                ItemObject();
                ~ItemObject() override;

                Subtype subtype() const;

                // item stack size in inventory or on the ground
                unsigned int amount() const;
                void setAmount(unsigned int value);

                // item weight, in pounds
                unsigned int weight() const;
                void setWeight(unsigned int value);

                // item price without any modifiers
                unsigned int price() const;
                void setPrice(unsigned price);

                // item volume
                unsigned int volume() const;
                void setVolume(unsigned int volume);

                // item inventory frame ID
                int inventoryFID() const;
                void setInventoryFID(int value);

                UI::Image* inventoryUi() const;
                UI::Image* inventorySlotUi() const;
                UI::Image* inventoryDragUi() const;

            protected:
                Subtype _subtype;
                unsigned int _amount = 1;
                unsigned int _weight = 0;
                unsigned int _price = 0;
                unsigned int _volume = 0;
                int _inventoryFID = -1;
                std::unique_ptr<UI::Image> _inventoryUi, _inventorySlotUi, _inventoryDragUi;
                void _generateUi() override;
        };
    }
}

#endif // FALLTERGEIST_GAME_ITEMOBJECT_H
