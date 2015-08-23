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

#include <vector>

#include "Point.h"
#include "Logger.h"

namespace Falltergeist
{

PointTest::PointTest()
{
    Point pt = Point(-70, -100);
    Point pt2 = Point();
    Size siz = Size(50, 65);
    pt += (siz + Point(42, 40) / 2 - pt2);
    siz -= Size(Point(60, 60)) + Size(5, 5);
    Logger::info("GAME") << "Min size " << siz << std::endl;
    Logger::info("GAME") << "Point a = " << pt << std::endl;
    Logger::info("GAME") << "Not Equals = " << (pt != siz) << std::endl;
    pt = siz;
    Logger::info("GAME") << "Equals = " << (pt == siz) << std::endl;
    siz = pt;
    Logger::info("GAME") << "Equals = " << (pt == siz) << std::endl;
    siz = Point(-5, 5);
    Logger::info("GAME") << "Min size " << siz << std::endl;
    siz = Size(640, 480) / 2;
    Logger::info("GAME") << "Half size " << siz << std::endl;
    siz = Size(640, 480) / 2.0;
    Logger::info("GAME") << "Half size 2 " << siz << std::endl;
    pt = Size(640, 480) / 2.0;
    Logger::info("GAME") << "Half size 3 " << pt << std::endl;
}


// Point class members

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

std::ostream& operator <<(std::ostream& lhs, const Point& rhs)
{
    lhs << "(" << rhs._x << "," << rhs._y << ")";
    return lhs;
}

// end Point class


// Size class members

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

Size& Size::operator *=(double rhs)
{
    setWidth((int)(_width * rhs));
    setHeight((int)(_height * rhs));
    return *this;
}

Size& Size::operator /=(double rhs)
{
    setWidth((int)(_width / rhs));
    setHeight((int)(_height / rhs));
    return *this;
}

bool Size::operator ==(const Size& rhs) const
{
    return _width == rhs._width && _height == rhs._height;
}

bool Size::operator !=(const Size& rhs) const
{
    return !(*this == rhs);
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

Size operator *(Size lhs, double rhs)
{
    lhs *= rhs;
    return lhs;
}

Size operator /(Size lhs, double rhs)
{
    lhs /= rhs;
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

Size Size::mul(double rhs) const
{
    return *this * rhs;
}

Size Size::div(double rhs) const
{
    return *this / rhs;
}

std::ostream& operator <<(std::ostream& lhs, const Size& rhs)
{
    lhs << "(" << rhs._width << "," << rhs._height << ")";
    return lhs;
}

// end Size class


// Rect class members

bool Rect::inRect(const Point& needle, const Size& size)
{
    return (needle.x() >= 0
            && needle.x() < size.width()
            && needle.y() >= 0
            && needle.y() < size.height());
}

bool Rect::inRect(const Point& needle, const Point& topLeft, const Size& size)
{
    Point bottomRight = topLeft + size;
    return (needle.x() >= topLeft.x()
            && needle.x() < bottomRight.x()
            && needle.y() >= topLeft.y()
            && needle.y() < bottomRight.y());
}

bool Rect::intersects(const Point& topLeft1, const Size& size1, const Point& topLeft2, const Size& size2)
{
    Point bottomRight1 = topLeft1 + size1;
    Point bottomRight2 = topLeft2 + size2;
    return (bottomRight1.x() >= topLeft2.x() && bottomRight1.y() >= topLeft2.y())
           || (bottomRight2.x() >= topLeft1.x() && bottomRight2.y() >= topLeft1.y());
}

// end Rect class

}