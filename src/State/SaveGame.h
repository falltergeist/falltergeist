#pragma once

// Project includes
#include "../State/State.h"
#include "../UI/IResourceManager.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace UI
    {
        namespace Factory
        {
            class ImageButtonFactory;
        }
    }
    namespace State
    {
        class SaveGame final : public State
        {
            public:
                SaveGame(std::shared_ptr<UI::IResourceManager> resourceManager);
                virtual ~SaveGame() = default;

                void init() override;

                void onDoneButtonClick(Event::Mouse* event);
                void onCancelButtonClick(Event::Mouse* event);

                void onStateActivate(Event::State* event) override;
                void onStateDeactivate(Event::State* event) override;
                void onKeyDown(Event::Keyboard* event) override;

            private:
                std::shared_ptr<UI::IResourceManager> resourceManager;
                std::unique_ptr<UI::Factory::ImageButtonFactory> imageButtonFactory;
        };
    }
}
