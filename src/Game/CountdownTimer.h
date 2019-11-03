#pragma once

#include <cstdint>

namespace Falltergeist
{
    namespace Game
    {
        class CountdownTimer
        {
            public:
                CountdownTimer(uint32_t seconds, uint32_t milliseconds = 0);
                void think(float deltaTime);
                bool isFinished();

            private:
                uint32_t _seconds = 0;
                uint32_t _milliseconds = 0;
                void _decreaseSeconds(uint32_t seconds);
        };
    }
}
