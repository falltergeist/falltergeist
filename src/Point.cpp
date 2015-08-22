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

#include "Point.h"
#include "Logger.h"

namespace Falltergeist
{

PointTest::PointTest()
{
    bool except = false;
    Point pt = Point(-100, -100);
    Point pt2 = Point();
    Size siz = Size(50, 50);
    pt += (siz + Point(40, 40) - pt2);
    siz -= Size(Point(60, 60)) + Size(5, 5);
    Logger::info("GAME") << "Min size " << siz << std::endl;
    Logger::info("GAME") << "Point a = " << pt << std::endl;
    Logger::info("GAME") << "Not Equals = " << (pt != siz) << std::endl;
    pt = siz;
    Logger::info("GAME") << "Equals = " << (pt == siz) << std::endl;
    siz = pt;
    Logger::info("GAME") << "Equals = " << (pt == siz) << std::endl;
    siz = Point(-5, 5);
    Logger::info("GAME") << "Min size " << except << " for " << siz << std::endl;
}

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

std::ostream& operator <<(std::ostream& lhs, const Point& rhs)
{
    lhs << "(" << rhs._x << "," << rhs._y << ")";
    return lhs;
}


Size::Size(int width, int height)
{
    setWidth(width);
    setHeight(height);
}

Size::Size(const Point& rhs)
{
    *this = rhs;
}

Size& Size::operator =(const Point& rhs)
{
    setWidth(rhs.x());
    setHeight(rhs.y());
    return *this;
}

Size::operator Point() const
{
    return Point(_width, _height);
}

int Size::width() const
{
    return _width;
}

int Size::height() const
{
    return _height;
}

/*int& Size::rwidth()
{
    return _width;
}

int& Size::rheight()
{
    return _height;
}*/

void Size::setWidth(int width)
{
    if (width < 0)
    {
        width = 0;
    }
    _width = width;
}

void Size::setHeight(int height)
{
    if (height < 0)
    {
        height = 0;
    }
    _height = height;
}

Size& Size::operator +=(const Size& rhs)
{
    setWidth(_width + rhs._width);
    setHeight(_height + rhs._height);
    return *this;
}

Size& Size::operator -=(const Size& rhs)
{
    setWidth(_width - rhs._width);
    setHeight(_height - rhs._height);
    return *this;
}

Size operator +(Size lhs, const Size& rhs)
{
    lhs += rhs;
    return lhs;
}

Size operator -(Size lhs, const Size& rhs)
{
    lhs -= rhs;
    return lhs;
}

Size Size::add(const Size& rhs) const
{
    return *this + rhs;
}

Size Size::sub(const Size& rhs) const
{
    return *this - rhs;
}

std::ostream& operator <<(std::ostream& lhs, const Size& rhs)
{
    lhs << "(" << rhs._width << "," << rhs._height << ")";
    return lhs;
}

}