#pragma once

#include <map>
#include <vector>
#include "../ILogger.h"
#include "../State/State.h"
#include "../UI/IResourceManager.h"
#include "../Game/Elevator.h"

namespace Falltergeist
{
    namespace Event
    {
        class Keyboard;
        class State;
    }

    namespace Game
    {
        class Elevator;
    }

    namespace UI
    {
        namespace Factory
        {
            class ImageButtonFactory;
        }

        class ImageButton;
        class ElevatorProgress;
    }

    namespace State
    {
        class ElevatorDialog final : public State
        {
            public:
                ElevatorDialog(
                    std::shared_ptr<UI::IResourceManager> resourceManager,
                    std::shared_ptr<Input::Mouse> mouse,
                    std::shared_ptr<ILogger> logger,
                    uint32_t elevatorType,
                    uint32_t elevatorLevel
                );

                ~ElevatorDialog() override = default;

                void init() override;

                void doElevate(int pressedButtonIndex);

                void onKeyDown(Event::Keyboard* event) override;

                void onStateActivate(Event::State* event) override;

                void onStateDeactivate(Event::State* event) override;

            private:
                std::vector<UI::ImageButton*> _buttons;

                std::shared_ptr<ILogger> _logger;

                std::shared_ptr<UI::IResourceManager> _resourceManager;

                std::unique_ptr<UI::Factory::ImageButtonFactory> _imageButtonFactory;

                Game::Elevator* _elevator;

                Input::Mouse::Cursor _previousCursor = Input::Mouse::Cursor::NONE;

                uint32_t _elevatorType;

                uint32_t _elevatorLevel;

                uint32_t _pressedButton;
        };
    }
}
