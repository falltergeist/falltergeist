#pragma once

#include <cstdint>

namespace Falltergeist
{
    namespace Game
    {
        class Time final
        {
            public:
                Time() = default;
                ~Time() = default;

                void think(const float &deltaTime);
                void increaseTicks();
                uint32_t ticks();
                uint32_t milliseconds();
                uint32_t seconds();
                uint32_t minutes();
                uint32_t hours();
                uint32_t day();
                uint32_t month();
                uint32_t year();

            protected:
                uint32_t _ticks = 300000;
                uint32_t _milliseconds = 0;
                uint32_t _seconds = 0;
                uint32_t _minutes = 30;
                uint32_t _hours = 8;
                uint32_t _day = 25;
                uint32_t _month = 7;
                uint32_t _year = 2241;

                void _increaseMilliseconds();
                void _increaseSeconds();
                void _increaseMinutes();
                void _increaseHours();
                void _increaseDay();
                void _increaseMonth();
                void _increaseYear();
        };
    }
}
