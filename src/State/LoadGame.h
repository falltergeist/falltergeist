#pragma once

#include "../State/State.h"

namespace Falltergeist
{
    namespace Event
    {
        class Keyboard;
        class Mouse;
        class State;
    }
    namespace State
    {
        class LoadGame : public State
        {
            public:
                LoadGame();
                ~LoadGame() override;

                void init() override;

                void onDoneButtonClick(Event::Mouse* event);
                void doCancel();
                void onCancelFadeDone(Event::State* event);

                void onStateActivate(Event::State* event) override;
                void onStateDeactivate(Event::State* event) override;
                void onKeyDown(Event::Keyboard* event) override;
        };
    }
}
