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
#include "../Event/MouseEvent.h"

// Third party includes

namespace Falltergeist
{

MouseEvent::MouseEvent(const std::string& name) : Event(name)
{
}

MouseEvent::MouseEvent(MouseEvent* event) : Event("mouse")
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

MouseEvent::~MouseEvent()
{
}

void MouseEvent::setX(unsigned int value)
{
    _x = value;
}

unsigned int MouseEvent::x()
{
    return _x;
}

void MouseEvent::setY(unsigned int value)
{
    _y = value;
}

unsigned int MouseEvent::y()
{
    return _y;
}

void MouseEvent::setXOffset(int value)
{
    _xOffset = value;
}

int MouseEvent::xOffset()
{
    return _xOffset;
}

void MouseEvent::setYOffset(int value)
{
    _yOffset = value;
}

int MouseEvent::yOffset()
{
    return _yOffset;
}

void MouseEvent::setLeftButton(bool value)
{
    _leftButton = value;
}

bool MouseEvent::leftButton()
{
    return _leftButton;
}

void MouseEvent::setRightButton(bool value)
{
    _rightButton = value;
}

bool MouseEvent::rightButton()
{
    return _rightButton;
}

void MouseEvent::setControlPressed(bool _controlPressed)
{
    this->_controlPressed = _controlPressed;
}

bool MouseEvent::controlPressed() const
{
    return _controlPressed;
}

void MouseEvent::setShiftPressed(bool _shiftPressed)
{
    this->_shiftPressed = _shiftPressed;
}

bool MouseEvent::shiftPressed() const
{
    return _shiftPressed;
}



}
