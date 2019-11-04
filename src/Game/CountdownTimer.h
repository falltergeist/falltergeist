#pragma once

#include <cstdint>

namespace Falltergeist
{
    namespace Game
    {
        class CountdownTimer
        {
            public:
                CountdownTimer(uint32_t milliseconds = 0);
                void think(const float &deltaTime);
                bool isFinished();
                void set(uint32_t milliseconds);
                uint32_t get() const;

            private:
                uint32_t _milliseconds = 0;
        };
    }
}
