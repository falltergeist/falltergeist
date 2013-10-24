/*
 * Copyright 2012-2013 Falltergeist Developers.
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

#ifndef FALLTERGEIST_EVENT_H
#define FALLTERGEIST_EVENT_H

// C++ standard includes

// Falltergeist includes

// Third party includes
#include "SDL.h"

namespace Falltergeist
{

class InteractiveSurface;

class Event
{
protected:
    SDL_Event * _event;
    InteractiveSurface * _sender;
    int _x;
    int _y;
    int _keyCode;
    bool _isMouseEvent;
    bool _isKeyboardEvent;
public:
    Event(SDL_Event * event);
    virtual ~Event();

    void setSender(InteractiveSurface * sender);
    InteractiveSurface * sender();

    int x();

    int y();

    int keyCode();

    SDL_Event * SDLEvent();

    bool isMouseEvent();
    bool isKeyboardEvent();
    bool shiftPressed();
};

}
#endif // FALLTERGEIST_EVENT_H
