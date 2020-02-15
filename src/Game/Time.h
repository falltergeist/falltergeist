#pragma once

namespace Falltergeist
{
    namespace Game
    {
        class Time
        {
            public:
                Time() = default;
                ~Time() = default;

                void think();

                void increaseTicks();
                unsigned int ticks();
                unsigned int seconds();
                unsigned int minutes();
                unsigned int hours();
                unsigned int day();
                unsigned int month();
                unsigned int year();

            protected:
                unsigned int _timer = 0;
                unsigned int _ticks = 300000;
                unsigned int _seconds = 0;
                unsigned int _minutes = 30;
                unsigned int _hours = 8;
                unsigned int _day = 25;
                unsigned int _month = 7;
                unsigned int _year = 2241;

                void _increaseSeconds();
                void _increaseMinutes();
                void _increaseHours();
                void _increaseDay();
                void _increaseMonth();
                void _increaseYear();
        };
    }
}
