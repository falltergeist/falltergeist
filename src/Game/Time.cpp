/*
 * Copyright 2012-2018 Falltergeist Developers.
 *
 * This file is part of Falltergeist.
 *
 * Falltergeist is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Falltergeist is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Falltergeist.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "../Game/Time.h"

#include "SDL.h"

namespace Falltergeist
{
    namespace Game
    {
        void Time::think()
        {
            if (SDL_GetTicks() - _timer < 100) {
                return;
            }
            _timer = SDL_GetTicks();
            increaseTicks();
        }

        void Time::increaseTicks()
        {
            _ticks++;

            if (_ticks%10 == 0) {
                _increaseSeconds();
            }
        }

        void Time::_increaseSeconds()
        {
            _seconds++;
            if (_seconds == 60) {
                _seconds = 0;
                _increaseMinutes();
            }
        }

        void Time::_increaseMinutes()
        {
            _minutes++;
            if (_minutes == 60) {
                _minutes = 0;
                _increaseHours();
            }
        }

        void Time::_increaseHours()
        {
            _hours++;
            if (_hours == 24) {
                _hours = 0;
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

        unsigned int Time::seconds()
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
