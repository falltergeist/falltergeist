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

// C++ includes

// Falltergeist includes
#include "../Engine/LocationCamera.h"

// Third party includes

namespace Falltergeist
{

LocationCamera::LocationCamera(int width, int height, int xPosition, int yPosition)
{
    setWidth(width);
    setHeight(height);
    setXPosition(xPosition);
    setYPosition(yPosition);
}

LocationCamera::~LocationCamera()
{
}

int LocationCamera::x()
{
    return xPosition() - width()*0.5;
}


int LocationCamera::y()
{
    return yPosition() - height()*0.5;
}

int LocationCamera::xPosition()
{
    return _xPosition;
}

void LocationCamera::setXPosition(int value)
{
    if (value < width()*0.5)
    {
        _xPosition = width()*0.5;
    }
    else
    {
        _xPosition = value;
    }
}

int LocationCamera::yPosition()
{
    return _yPosition;
}

void LocationCamera::setYPosition(int value)
{
    if (value < height()*0.5)
    {
        _yPosition = height()*0.5;
    }
    else
    {
        _yPosition = value;
    }
}

int LocationCamera::width()
{
    return _width;
}

void LocationCamera::setWidth(int value)
{
    _width = value;
}

int LocationCamera::height()
{
    return _height;
}

void LocationCamera::setHeight(int value)
{
    _height = value;
}

}
