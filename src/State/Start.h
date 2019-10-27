#pragma once

#include "../Game/CountdownTimer.h"
#include "../State/State.h"

namespace Falltergeist
{
    namespace State
    {
        class Start : public State
        {
            public:
                Start();
                ~Start() override;

                void think(uint32_t nanosecondsPassed) override;
                void init() override;

            protected:
                std::unique_ptr<Game::CountdownTimer> _delayTimer;
        };
    }
}
