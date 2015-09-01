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

// Related headers
#include "../Event/Mouse.h"

// C++ standard includes

// Falltergeist includes

// Third party includes

namespace Falltergeist
{
namespace Event
{

Mouse::Mouse(const std::string& name) : Event(name)
{
}

Mouse::Mouse(Mouse* event) : Event("mouse")
{
    _x = event->_x;
    _y = event->_y;
    _xOffset = event->_xOffset;
    _yOffset = event->_yOffset;
    _leftButton = event->_leftButton;
    _rightButton = event->_rightButton;
    _shiftPressed = event->_shiftPressed;
    _controlPressed = event->_controlPressed;
    _name = event->_name;
}

Mouse::~Mouse()
{
}

void Mouse::setX(unsigned int value)
{
    _x = value;
}

unsigned int Mouse::x() const
{
    return _x;
}

void Mouse::setY(unsigned int value)
{
    _y = value;
}

unsigned int Mouse::y() const
{
    return _y;
}

void Mouse::setXOffset(int value)
{
    _xOffset = value;
}

int Mouse::xOffset() const
{
    return _xOffset;
}

void Mouse::setYOffset(int value)
{
    _yOffset = value;
}

int Mouse::yOffset() const
{
    return _yOffset;
}

void Mouse::setLeftButton(bool value)
{
    _leftButton = value;
}

bool Mouse::leftButton() const
{
    return _leftButton;
}

void Mouse::setRightButton(bool value)
{
    _rightButton = value;
}

bool Mouse::rightButton() const
{
    return _rightButton;
}

void Mouse::setControlPressed(bool value)
{
    this->_controlPressed = value;
}

bool Mouse::controlPressed() const
{
    return _controlPressed;
}

void Mouse::setShiftPressed(bool value)
{
    this->_shiftPressed = value;
}

bool Mouse::shiftPressed() const
{
    return _shiftPressed;
}

}
}
