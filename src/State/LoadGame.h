#pragma once

// Project includes
#include "../State/State.h"
#include "../UI/IResourceManager.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace Event
    {
        class Keyboard;
        class Mouse;
        class State;
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
        class LoadGame final : public State
        {
            public:
                LoadGame(std::shared_ptr<UI::IResourceManager> resourceManager);
                virtual ~LoadGame() = default;

                void init() override;

                void onDoneButtonClick(Event::Mouse* event);
                void doCancel();
                void onCancelFadeDone(Event::State* event);

                void onStateActivate(Event::State* event) override;
                void onStateDeactivate(Event::State* event) override;
                void onKeyDown(Event::Keyboard* event) override;

            private:
                std::shared_ptr<UI::IResourceManager> resourceManager;
                std::unique_ptr<UI::Factory::ImageButtonFactory> imageButtonFactory;
        };
    }
}
