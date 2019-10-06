#pragma once

#include "../State/State.h"

namespace Falltergeist
{
    namespace State
    {
        class PipBoy : public State
        {
            public:
                PipBoy();
                ~PipBoy() override;

                void init() override;

                void onCloseButtonClick(Event::Mouse* event);
                void onKeyDown(Event::Keyboard* event) override;
        };
    }
}
