#pragma once

#include "../State/State.h"
#include "../UI/IResourceManager.h"

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
                LoadGame(
                    std::shared_ptr<UI::IResourceManager> resourceManager,
                    std::shared_ptr<Input::Mouse> mouse
                );

                virtual ~LoadGame() = default;

                void init() override;

                void onDoneButtonClick(Event::Mouse* event);

                void doCancel();

                void onCancelFadeDone(Event::State* event);

                void onStateActivate(Event::State* event) override;

                void onStateDeactivate(Event::State* event) override;

                void onKeyDown(Event::Keyboard* event) override;

            private:
                std::shared_ptr<UI::IResourceManager> _resourceManager;

                std::unique_ptr<UI::Factory::ImageButtonFactory> _imageButtonFactory;

                Input::Mouse::Cursor _previousCursor = Input::Mouse::Cursor::NONE;
        };
    }
}
