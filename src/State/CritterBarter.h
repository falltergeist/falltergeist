#pragma once

#include <memory>
#include <vector>
#include "../State/State.h"
#include "../UI/IResourceManager.h"

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
        namespace Factory
        {
            class ImageButtonFactory;
        }

        class ItemsList;
    }
    namespace State
    {
        class CritterBarter final : public State
        {
            public:
                CritterBarter(std::shared_ptr<UI::IResourceManager> resourceManager);
                ~CritterBarter() override;

                void init() override;
                void resetTransaction();

                void onOfferButtonClick(Event::Mouse* event);
                void onTalkButtonClick(Event::Mouse* event);
                void onKeyDown(Event::Keyboard* event) override;
                void onStateDeactivate(Event::State* event) override;

                std::shared_ptr<Game::CritterObject> trader();
                void setTrader(const std::shared_ptr<Game::CritterObject> &trader);

            protected:
                int _sellPriceTotal = 0;
                int _buyPriceTotal = 0;

                std::shared_ptr<Game::CritterObject> _trader;
                std::vector<std::shared_ptr<Game::ItemObject>> _itemsToSell;
                std::vector<std::shared_ptr<Game::ItemObject>> _itemsToBuy;

            private:
                std::shared_ptr<UI::IResourceManager> resourceManager;
                std::unique_ptr<UI::Factory::ImageButtonFactory> imageButtonFactory;
        };
    }
}
