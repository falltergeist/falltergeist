/*
 * Copyright 2012-2014 Falltergeist Developers.
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

// C++ standard includes

// Falltergeist includes
#include "../Engine/GameTime.h"

// Third party includes
#include "SDL.h"

namespace Falltergeist
{

GameTime::GameTime()
{
}

GameTime::~GameTime()
{
}

void GameTime::think()
{
    if (SDL_GetTicks() - _timer < 100) return;
    _timer = SDL_GetTicks();
    _increaseTicks();
}

void GameTime::_increaseTicks()
{
    _ticks++;

    if (_ticks%10 == 0)
    {
        _increaseSeconds();
    }
}

void GameTime::_increaseSeconds()
{
    _seconds++;
    if (_seconds == 60)
    {
        _seconds = 0;
        _increaseMinutes();
    }
}

void GameTime::_increaseMinutes()
{
    _minutes++;
    if (_minutes == 60)
    {
        _minutes = 0;
        _increaseHours();
    }
}

void GameTime::_increaseHours()
{
    _hours++;
    if (_hours == 24)
    {
        _hours = 0;
        _increaseDay();
    }
}

void GameTime::_increaseDay()
{

}

unsigned int GameTime::ticks()
{
    return _ticks;
}

unsigned int GameTime::seconds()
{
    return _seconds;
}

unsigned int GameTime::minutes()
{
    return _minutes;
}

unsigned int GameTime::hours()
{
    return _hours;
}

unsigned int GameTime::day()
{
    return _day;
}

unsigned int GameTime::month()
{
    return _month;
}

unsigned int GameTime::year()
{
    return _year;
}

}
