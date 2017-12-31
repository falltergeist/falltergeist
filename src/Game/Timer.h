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

#ifndef FALLTERGEIST_TIMER_H
#define FALLTERGEIST_TIMER_H

// C++ standard includes

// Falltergeist includes
#include "../Event/Handler.h"

// Third party includes

namespace Falltergeist
{
namespace Game
{

class Time;

class TimerAbstract
{
public:
    TimerAbstract(unsigned int interval);

    void start();

    void start(unsigned int interval, bool repeat = false);

    void stop();

    bool enabled() const;

    unsigned int interval() const;

    void setInterval(unsigned int interval);

    bool repeat() const;

    void setRepeat(bool repeat);

    Event::Handler& tickHandler();

    void think();

protected:
    virtual unsigned int _getTime() = 0;

    Event::Handler _tickHandler;

    bool _enabled = false;
    bool _repeat = false;
    unsigned int _interval;
    unsigned int _lastTick;
};

/**
 * @brief Real-time timer.
 * Operates in milliseconds (1000 is one real-time second).
 */
class Timer : public TimerAbstract
{
public:
    Timer(unsigned interval = 1000);

protected:
    unsigned int _getTime() override;
};

/**
 * @brief Game-time timer.
 * Operates in game ticks (10 ticks is one game second).
 * Game second equals to real-time second, but game time is frozen during pause or turn-based mode.
 */
class GameTimer : public TimerAbstract
{
public:
    GameTimer(unsigned interval = 1000);

protected:
    Time* _time;

    unsigned int _getTime() override;
};

}
}


#endif //FALLTERGEIST_TIMER_H
