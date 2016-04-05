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

#ifndef FALLTERGEIST_STATE_INVENTORY_H
#define FALLTERGEIST_STATE_INVENTORY_H

// C++ standard includes

// Falltergeist includes
#include "../State/State.h"

// Third party includes

namespace Falltergeist
{
    namespace Game
    {
        class ItemObject;
    }
    namespace State
    {
        class Inventory : public State
        {
            public:
                Inventory();
                ~Inventory() override;

                void init() override;

                void onDoneButtonClick(Event::Mouse* event);
                void onScrollUpButtonClick(Event::Mouse* event);
                void onScrollDownButtonClick(Event::Mouse* event);
                void onArmorSlotMouseDown(Event::Mouse* event);
                void onLeftHandSlotMouseDown(Event::Mouse* event);
                void onRightHandSlotMouseDown(Event::Mouse* event);
                void enableScrollDownButton(bool enable);
                void enableScrollUpButton(bool enable);
                //void onSlotMouseDown(Event::Mouse* event);
                //void onSlotMouseUp(Event::Mouse* event);
                //void onSlotDrag(Event::Mouse* event);
                void backgroundRightClick(Event::Mouse* event);
                void onKeyDown(Event::Keyboard* event) override;
                void onInventoryModified();

            private:
                std::string _handItemSummary (Game::ItemObject* hand);
                void _screenShow (unsigned int PID);
        };
    }
}
#endif // FALLTERGEIST_STATE_INVENTORY_H
