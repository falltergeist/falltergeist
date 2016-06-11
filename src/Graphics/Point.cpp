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

// Related headers
#include "../Graphics/Point.h"

// C++ standard includes

// Falltergeist includes
#include "../Logger.h"

// Third party includes

namespace Falltergeist
{
namespace Graphics
{

int Point::x() const
{
    return _x;
}

int Point::y() const
{
    return _y;
}

int& Point::rx()
{
    return _x;
}

int& Point::ry()
{
    return _y;
}

void Point::setX(int x)
{
    _x = x;
}

void Point::setY(int y)
{
    _y = y;
}

Point& Point::operator +=(const Point& rhs)
{
    _x += rhs._x;
    _y += rhs._y;
    return *this;
}

Point& Point::operator -=(const Point& rhs)
{
    _x -= rhs._x;
    _y -= rhs._y;
    return *this;
}

Point& Point::operator *=(double rhs)
{
    _x *= rhs;
    _y *= rhs;
    return *this;
}

Point& Point::operator /=(double rhs)
{
    _x /= rhs;
    _y /= rhs;
    return *this;
}

bool Point::operator ==(const Point& rhs) const
{
    return _x == rhs._x && _y == rhs._y;
}

bool Point::operator !=(const Point& rhs) const
{
    return !(*this == rhs);
}

Point operator +(Point lhs, const Point& rhs)
{
    lhs += rhs;
    return lhs;
}

Point operator -(Point lhs, const Point& rhs)
{
    lhs -= rhs;
    return lhs;
}

Point operator *(Point lhs, double rhs)
{
    lhs *= rhs;
    return lhs;
}

Point operator /(Point lhs, double rhs)
{
    lhs /= rhs;
    return lhs;
}

Point Point::add(const Point& rhs) const
{
    return *this + rhs;
}

Point Point::sub(const Point& rhs) const
{
    return *this - rhs;
}

Point Point::mul(double rhs) const
{
    return *this * rhs;
}

Point Point::div(double rhs) const
{
    return *this / rhs;
}

}
}
