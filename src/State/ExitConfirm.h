#pragma once

#include "../State/State.h"

namespace Falltergeist
{
    namespace Event
    {
        class Keyboard;
        class State;
    }
    namespace State
    {
        class ExitConfirm : public State
        {
            public:
                ExitConfirm();
                ~ExitConfirm() override;

                void init() override;

                void doYes();
                void doNo();

                void onKeyDown(Event::Keyboard* event) override;
                void onStateActivate(Event::State* event) override;
                void onStateDeactivate(Event::State* event) override;
        };
    }
}
