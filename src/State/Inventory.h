#pragma once

#include "../ILogger.h"
#include "../State/State.h"
#include "../UI/IResourceManager.h"

namespace Falltergeist
{
    namespace Game
    {
        class ItemObject;
    }
    namespace UI
    {
        namespace Factory
        {
            class ImageButtonFactory;
        }
    }
    namespace State
    {
        class Inventory final : public State
        {
            public:
                Inventory(
                    std::shared_ptr<UI::IResourceManager> resourceManager,
                    std::shared_ptr<Input::Mouse> mouse,
                    std::shared_ptr<ILogger> logger
                );

                Inventory(const Inventory&) = delete;

                Inventory& operator=(const Inventory&) = delete;

                ~Inventory() override = default;

                void init() override;

                void onDoneButtonClick(Event::Mouse* event);

                void onScrollUpButtonClick(Event::Mouse* event);

                void onScrollDownButtonClick(Event::Mouse* event);

                void enableScrollDownButton(bool enable);

                void enableScrollUpButton(bool enable);

                void backgroundRightClick(Event::Mouse* event);

                void onKeyDown(Event::Keyboard* event) override;

                void onInventoryModified();

            private:
                std::string _handItemSummary(Game::ItemObject* hand);

                void _screenShow (unsigned int PID);

                std::shared_ptr<ILogger> _logger;

                std::shared_ptr<UI::IResourceManager> _resourceManager;

                std::unique_ptr<UI::Factory::ImageButtonFactory> _imageButtonFactory;
        };
    }
}
