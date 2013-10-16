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

// C++ includes

// Falltergeist includes
#include "../Engine/LocationCamera.h"

// Third party includes

namespace Falltergeist
{

LocationCamera::LocationCamera(unsigned int width, unsigned int height, unsigned int x, unsigned int y)
{
    _x = x;
    _y = y;
    _width = width;
    _height = height;
}

LocationCamera::~LocationCamera()
{
}

unsigned int LocationCamera::x()
{
    return _x;
}

void LocationCamera::setX(unsigned int value)
{
    _x = value;
}

unsigned int LocationCamera::y()
{
    return _y;
}

void LocationCamera::setY(unsigned int value)
{
    _y = value;
}

unsigned int LocationCamera::width()
{
    return _width;
}

void LocationCamera::setWidth(unsigned int value)
{
    _width = value;
}

unsigned int LocationCamera::height()
{
    return _height;
}

void LocationCamera::setHeight(unsigned int value)
{
    _height = value;
}

}
