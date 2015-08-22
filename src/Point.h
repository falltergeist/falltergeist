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

#ifndef FALLTERGEIST_POINT_H
#define FALLTERGEIST_POINT_H

#include <ostream>

#include "Exception.h"

namespace Falltergeist
{

/**
 * Represents a Point coordinates on screen
 */
class Point
{
public:
    Point() : _x(0), _y(0) {}

    Point(int x, int y) : _x(x), _y(y) {}

    int x() const;

    int y() const;

    int& rx();

    int& ry();

    void setX(int x);

    void setY(int y);

    Point& operator +=(const Point& rhs);

    Point& operator -=(const Point& rhs);

    Point& operator *=(double rhs);

    Point& operator /=(double rhs);

    bool operator ==(const Point& rhs) const;

    bool operator !=(const Point& rhs) const;

    friend Point operator +(Point lhs, const Point& rhs);

    friend Point operator -(Point lhs, const Point& rhs);

    friend Point operator *(Point lhs, double rhs);

    friend Point operator /(Point lhs, double rhs);

    Point add(const Point& rhs) const;

    Point sub(const Point& rhs) const;

    friend std::ostream& operator <<(std::ostream& lhs, const Point& rhs);

protected:
    int _x;
    int _y;

};


class Size
{
public:
    Size() : _width(0), _height(0) {}

    Size(int width, int height);

    explicit Size(const Point& rhs);

    Size& operator=(const Point& rhs);

    // Implicit conversion to Point
    operator Point() const;

    int width() const;

    int height() const;

    /*int& rwidth();

    int& rheight();*/

    void setWidth(int width);

    void setHeight(int height);

    Size& operator +=(const Size& rhs);

    Size& operator -=(const Size& rhs);

    friend Size operator +(Size lhs, const Size& rhs);

    friend Size operator -(Size lhs, const Size& rhs);

    Size add(const Size& rhs) const;

    Size sub(const Size& rhs) const;

    friend std::ostream& operator <<(std::ostream& lhs, const Size& rhs);

protected:
    int _width;
    int _height;
};

class PointTest
{

public:
    PointTest();
};

} // namespace Falltergeist

#endif //FALLTERGEIST_POINT_H
