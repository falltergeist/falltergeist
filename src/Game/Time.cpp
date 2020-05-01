#include "../Game/Time.h"

namespace Falltergeist
{
    namespace Game
    {
        void Time::think(const float &deltaTime)
        {
            _milliseconds += deltaTime;

            while (_milliseconds >= 1000.0f) {
                _milliseconds -= 1000.0f;
                _increaseSeconds();
            }
        }

        void Time::increaseTicks()
        {
            // TODO get rid of this method
            _ticks++;
            // 1 tick = 10 ms


            for (auto i = 0; i < 10; i++) {
                _increaseMilliseconds();
            }
        }

        // TODO pass number of ms as param
        void Time::_increaseMilliseconds()
        {
            _milliseconds++;
            if (_milliseconds >= 1000) {
                _milliseconds -= 1000;
                _increaseSeconds();
            }
        }

        void Time::_increaseSeconds()
        {
            _seconds++;
            if (_seconds >= 60) {
                _seconds -= 60;
                _increaseMinutes();
            }
        }

        void Time::_increaseMinutes()
        {
            _minutes++;
            if (_minutes >= 60) {
                _minutes -= 60;
                _increaseHours();
            }
        }

        void Time::_increaseHours()
        {
            _hours++;
            if (_hours >= 24) {
                _hours -= 24;
                _increaseDay();
            }
        }

        void Time::_increaseDay()
        {
            _day++;

            switch(_month)
            {
                case 1: // January
                case 3: // March
                case 5: // May
                case 7: // July
                case 8: // August
                case 10: // October
                case 12:// December
                    if (_day == 32) {
                        _day = 1;
                        _increaseMonth();
                    }
                    break;
                case 4: // April
                case 6: // June
                case 9: // September
                case 11:// November
                    if (_day == 31) {
                        _day = 1;
                        _increaseMonth();
                    }
                    break;
                case 2: // February
                    // leap year
                    if (_year%4 == 0 && (_year%100 != 0 || _year%400 == 0)) {
                        if (_day == 30) {
                            _day = 1;
                            _increaseMonth();
                        }
                    } else {
                        if (_day == 29) {
                            _day = 1;
                            _increaseMonth();
                        }
                    }
            }
        }

        void Time::_increaseMonth()
        {
            _month++;
            if (_month == 13) {
                _month = 1;
                _increaseYear();
            }
        }

        void Time::_increaseYear()
        {
            _year++;
        }

        unsigned int Time::ticks()
        {
            return _ticks;
        }

        uint32_t Time::milliseconds()
        {
            return _milliseconds;
        }

        uint32_t Time::seconds()
        {
            return _seconds;
        }

        unsigned int Time::minutes()
        {
            return _minutes;
        }

        unsigned int Time::hours()
        {
            return _hours;
        }

        unsigned int Time::day()
        {
            return _day;
        }

        unsigned int Time::month()
        {
            return _month;
        }

        unsigned int Time::year()
        {
            return _year;
        }
    }
}
