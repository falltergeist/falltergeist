#pragma once

#include <vector>
#include "../State/State.h"

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
