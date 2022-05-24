#pragma once

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
                CritterBarter(
                    std::shared_ptr<UI::IResourceManager> resourceManager,
                    std::shared_ptr<Input::Mouse> mouse,
                    Game::CritterObject* trader
                );

                ~CritterBarter() override;

                void init() override;

                void resetTransaction();

                void onOfferButtonClick(Event::Mouse* event);

                void onTalkButtonClick(Event::Mouse* event);

                void onKeyDown(Event::Keyboard* event) override;

                void onStateDeactivate(Event::State* event) override;

                Game::CritterObject* trader() const;

            private:
                int _sellPriceTotal = 0;

                int _buyPriceTotal = 0;

                Game::CritterObject* _trader = nullptr;

                std::vector<Game::ItemObject*> _itemsToSell;

                std::vector<Game::ItemObject*> _itemsToBuy;

                std::shared_ptr<UI::IResourceManager> _resourceManager;

                std::unique_ptr<UI::Factory::ImageButtonFactory> _imageButtonFactory;
        };
    }
}
