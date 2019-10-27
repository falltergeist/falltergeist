#pragma once

#include <cstdint>

namespace Falltergeist
{
    namespace Game
    {
        class CountdownTimer
        {
            public:
                CountdownTimer(uint32_t seconds, uint32_t milliseconds = 0, uint32_t microseconds = 0, uint32_t nanoseconds = 0);
                void think(uint32_t nanosecondsPassed);
                bool isFinished();

            private:
                uint32_t _seconds = 0;
                uint32_t _milliseconds = 0;
                uint32_t _microseconds = 0;
                uint32_t _nanoseconds = 0;
                void _decreaseMicroseconds(uint32_t microseconds);
                void _decreaseMilliseconds(uint32_t milliseconds);
                void _decreaseSeconds(uint32_t seconds);
        };
    }
}
