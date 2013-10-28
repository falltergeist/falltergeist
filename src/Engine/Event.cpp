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

// C++ standard includes

// Falltergeist includes
#include "../Engine/Event.h"

// Third party includes

namespace Falltergeist
{

Event::Event(SDL_Event* event) : _event(event)
{
    _isMouseEvent = false;
    _isKeyboardEvent = false;
    _x = -1;
    _y = -1;
    _keyCode = -1;

    switch(_event->type)
    {
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
            _isMouseEvent = true;
            _x = event->button.x;
            _y = event->button.y;
            break;
        case SDL_MOUSEMOTION:
            _isMouseEvent = true;
            _x = event->motion.x;
            _y = event->motion.y;
            _xOffset = event->motion.xrel;
            _yOffset = event->motion.yrel;
            break;
        case SDL_KEYDOWN:
        case SDL_KEYUP:
            _isKeyboardEvent = true;
            _keyCode = event->key.keysym.sym;
            break;
    }
}

Event::~Event()
{
}

SDL_Event* Event::SDLEvent()
{
    return _event;
}

InteractiveSurface* Event::sender()
{
    return _sender;
}

void Event::setSender(InteractiveSurface* sender)
{
    _sender = sender;
}

bool Event::isMouseEvent()
{
    return _isMouseEvent;
}

bool Event::isKeyboardEvent()
{
    return _isKeyboardEvent;
}

int Event::x()
{
    return _x;
}

int Event::xOffset()
{
    return _xOffset;
}

int Event::y()
{
    return _y;
}

int Event::yOffset()
{
    return _yOffset;
}

int Event::keyCode()
{
    return _keyCode;
}

bool Event::shiftPressed()
{
    return SDLEvent()->key.keysym.mod & (KMOD_LSHIFT | KMOD_RSHIFT);
}

}
