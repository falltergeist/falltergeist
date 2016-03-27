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

#ifndef FALLTERGEIST_GRAPHICS_POINT_H
#define FALLTERGEIST_GRAPHICS_POINT_H

// C++ standard includes

// Falltergeist includes

// Third party includes

namespace Falltergeist
{
namespace Graphics
{

/**
 * Represents a Point on screen: x and y coordinates, in pixels.
 */
class Point
{
public:
    Point() : _x(0), _y(0) {}

    Point(int x, int y) : _x(x), _y(y) {}

    int x() const;
    int y() const;

    // Reference to x coordinate
    int& rx();
    // Reference to y coordinate
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

    // Addition of given Point
    Point add(const Point& rhs) const;
    // Subtraction of given Point
    Point sub(const Point& rhs) const;
    // Multiplication by given number
    Point mul(double rhs) const;
    // Division by given number
    Point div(double rhs) const;

protected:
    int _x;
    int _y;

};

}
}
#endif //FALLTERGEIST_GRAPHICS_POINT_H
