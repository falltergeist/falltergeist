/*
 * Copyright 2012-2015 Falltergeist Developers.
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
#include "../Event/Event.h"
#include "../Game/Timer.h"
#include "../Game/Game.h"
#include "../Game/Time.h"

// Third party includes
#include <SDL.h>


namespace Falltergeist
{
namespace Game
{

TimerAbstract::TimerAbstract(unsigned interval) : _interval(interval)
{
}

Event::Handler& TimerAbstract::tickHandler()
{
    return _tickHandler;
}

void TimerAbstract::think()
{
    if (_enabled && _getTime() > _lastTick + _interval)
    {
        // Invoke directly without Event Dispatcher, for now.
        Event::Event event("tick");
        if (!_repeat)
        {
            _enabled = false;
        }
        _tickHandler.invoke(&event);
    }
}

void TimerAbstract::start()
{
    _enabled = true;
    _lastTick = _getTime();
}

void TimerAbstract::start(unsigned int interval, bool repeat)
{
    _interval = interval;
    _repeat = repeat;
    start();
}

void TimerAbstract::stop()
{
    _enabled = false;
}

bool TimerAbstract::enabled() const
{
    return _enabled;
}

unsigned int TimerAbstract::interval() const
{
    return _interval;
}

void TimerAbstract::setInterval(unsigned int interval)
{
    _interval = interval;
}

bool TimerAbstract::repeat() const
{
    return _repeat;
}

void TimerAbstract::setRepeat(bool repeat)
{
    _repeat = repeat;
}


Timer::Timer(unsigned interval) : TimerAbstract(interval)
{
}

unsigned int Timer::_getTime()
{
    return SDL_GetTicks();
}


GameTimer::GameTimer(unsigned interval) : TimerAbstract(interval)
{
    _time = Game::getInstance()->gameTime();
}

unsigned int GameTimer::_getTime()
{
    return _time->ticks();
}
}
}