#pragma once

#include "../State/State.h"

namespace Falltergeist
{
    namespace UI
    {
        class BigCounter;
    }
    namespace State
    {
        class PlayerEditAge : public State
        {
            public:
                PlayerEditAge();
                ~PlayerEditAge() override;

                void init() override;

                void onIncButtonClick(Event::Mouse* event);
                void onDecButtonClick(Event::Mouse* event);
                void onDoneButtonClick(Event::Mouse* event);
                void doInc();
                void doDec();
                void doDone();
                void doBack();
                void onKeyDown(Event::Keyboard* event) override;

            protected:
                UI::BigCounter* _counter = nullptr;
        };
    }
}
