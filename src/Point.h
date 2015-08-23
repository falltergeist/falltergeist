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

// C++ standard includes
#include <ostream>

// Falltergeist includes
#include "Exception.h"

// Third party includes


namespace Falltergeist
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

    // Addition of given Point
    Point add(const Point& rhs) const;
    // Subtraction of given Point
    Point sub(const Point& rhs) const;
    // Multiplication by given number
    Point mul(double rhs) const;
    // Division by given number
    Point div(double rhs) const;

    friend std::ostream& operator <<(std::ostream& lhs, const Point& rhs);

protected:
    int _x;
    int _y;

};

/**
 * Represents a Size of a rectangular object: width and height, in pixels.
 */
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
    Size& operator *=(double rhs);
    Size& operator /=(double rhs);

    bool operator ==(const Size& rhs) const;
    bool operator !=(const Size& rhs) const;

    friend Size operator +(Size lhs, const Size& rhs);
    friend Size operator -(Size lhs, const Size& rhs);
    friend Size operator *(Size lhs, double rhs);
    friend Size operator /(Size lhs, double rhs);

    // Addition of another Size
    Size add(const Size& rhs) const;
    // Subtraction of another Size
    Size sub(const Size& rhs) const;
    // Multiplication of width/height by given number
    Size mul(double rhs) const;
    // Division by given number
    Size div(double rhs) const;

    friend std::ostream& operator <<(std::ostream& lhs, const Size& rhs);

protected:
    int _width;
    int _height;
};

// static class for Rectangle-related function
class Rect
{
public:
    // checks if given point is located withing the rectangle specified by size
    static bool inRect(const Point& needle, const Size& size);

    // checks if given point is located withing the rectangle with given top-left position and size
    static bool inRect(const Point& needle, const Point& topLeft, const Size& size);

    // checks if two rectangles, given as their top-left positions and sizes, intersect each other
    static bool intersects(const Point& topLeft1, const Size& size1, const Point& topLeft2, const Size& size2);
};


class PointTest
{

public:
    PointTest();
};

} // namespace Falltergeist

#endif //FALLTERGEIST_POINT_H
