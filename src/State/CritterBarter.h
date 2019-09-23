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

#ifndef FALLTERGEIST_STATE_CRITTERBARTER_H
#define FALLTERGEIST_STATE_CRITTERBARTER_H

// C++ standard includes
#include <vector>

// Falltergeist includes
#include "../State/State.h"

// Third party includes

namespace Falltergeist
{
    namespace Game
    {
        class ContainerItemObject;
        class CritterObject;
        class ItemObject;
    }
    namespace UI
    {
        class ItemsList;
    }
    namespace State
    {
        class CritterBarter : public State
        {
            public:
                CritterBarter();
                ~CritterBarter() override;

                void init() override;
                void resetTransaction();

                void onOfferButtonClick(Event::Mouse* event);
                void onTalkButtonClick(Event::Mouse* event);
                void onKeyDown(Event::Keyboard* event) override;
                void onStateDeactivate(Event::State* event) override;

                Game::CritterObject* trader();
                void setTrader(Game::CritterObject* trader);

            protected:
                int _sellPriceTotal = 0;
                int _buyPriceTotal = 0;

                Game::CritterObject* _trader = nullptr;
                std::vector<Game::ItemObject*> _itemsToSell;
                std::vector<Game::ItemObject*> _itemsToBuy;
        };
    }
}
#endif // FALLTERGEIST_STATE_CRITTERBARTER_H
