#pragma once

#include "../Game/Timer.h"
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

                void think(const float &deltaTime) override;
                void init() override;

            protected:
                std::unique_ptr<Game::Timer> _delayTimer;
        };
    }
}
