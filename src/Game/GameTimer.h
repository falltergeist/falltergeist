#pragma once

#include "../Game/AbstractTimer.h"

namespace Falltergeist
{
    namespace Game
    {
        class Time;

        /**
         * @brief Game-time timer.
         * Operates in game ticks (10 ticks is one game second).
         * Game second equals to real-time second, but game time is frozen during pause or turn-based mode.
         */
        class GameTimer : public AbstractTimer
        {
            public:
                GameTimer(float interval = 1000);
        };
    }
}
