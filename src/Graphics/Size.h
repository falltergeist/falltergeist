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

#ifndef FALLTERGEIST_GRAPHICS_SIZE_H
#define FALLTERGEIST_GRAPHICS_SIZE_H

// C++ standard includes

// Falltergeist includes
#include "../Graphics/Point.h"

// Third party includes

namespace Falltergeist
{
namespace Graphics
{

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

protected:
    int _width;
    int _height;
};

}
}
#endif // FALLTERGEIST_GRAPHICS_SIZE_H
