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
#include "../Event/KeyboardEvent.h"

// Third party includes

namespace Falltergeist
{

KeyboardEvent::KeyboardEvent(std::string name) : Event(name)
{
}

KeyboardEvent::~KeyboardEvent()
{
}

int KeyboardEvent::keyCode()
{
    return _keyCode;
}

void KeyboardEvent::setKeyCode(int value)
{
    _keyCode = value;
}

bool KeyboardEvent::shiftPressed()
{
    return _shiftPressed;
}

void  KeyboardEvent::setShiftPressed(bool value)
{
    _shiftPressed = value;
}

}
