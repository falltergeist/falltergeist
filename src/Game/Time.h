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

#ifndef FALLTERGEIST_GAME_TIME_H
#define FALLTERGEIST_GAME_TIME_H

// C++ standard includes

// Falltergeist includes

// Third party includes

namespace Falltergeist
{
namespace Game
{

class Time
{

public:
    Time();
    ~Time();

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
#endif // FALLTERGEIST_GAME_TIME_H
