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

Mouse::Mouse(const Mouse& event, const std::string& newName) : Event(newName)
{
    _position = event._position;
    _offset = event._offset;
    _leftButton = event._leftButton;
    _rightButton = event._rightButton;
    _shiftPressed = event._shiftPressed;
    _controlPressed = event._controlPressed;
}

Mouse::Mouse(const Mouse& event) : Mouse(event, event._name)
{
}

Mouse::~Mouse()
{
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

const Point& Mouse::position() const
{
    return _position;
}

void Mouse::setPosition(const Point& position)
{
    _position = position;
}

const Point& Mouse::offset() const
{
    return _offset;
}

void Mouse::setOffset(const Point& offset)
{
    _offset = offset;
}

bool Mouse::obstacle() const
{
    return _obstacle;
}

void Mouse::setObstacle(bool obstacle)
{
    _obstacle = obstacle;
}

}
}
