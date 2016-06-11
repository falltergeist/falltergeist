/*
 * Copyright 2012-2016 Falltergeist Developers.
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
#include "LocationCamera.h"
#include "Logger.h"

// Third party includes

namespace Falltergeist
{

LocationCamera::LocationCamera(const Size& size, const Point& center)
{
    setSize(size);
    setCenter(center);
}

LocationCamera::~LocationCamera()
{
}

Point LocationCamera::topLeft() const
{
    return _center - (_size / 2.0);
}

const Point& LocationCamera::center() const
{
    return _center;
}

void LocationCamera::setCenter(const Point& pos)
{
    _center = pos;
    if (_center.x() < _size.width() / 2)
    {
        _center.setX(_size.width() / 2);
    }
    if (_center.y() < _size.height() / 2)
    {
        _center.setY(_size.height() / 2);
    }
}

const Size& LocationCamera::size() const
{
    return _size;
}

void LocationCamera::setSize(const Size& size)
{
    _size = size;
}

}
