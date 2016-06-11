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

#ifndef FALLTERGEIST_GRAPHICS_RECT_H
#define FALLTERGEIST_GRAPHICS_RECT_H

// C++ standard includes

// Falltergeist includes
#include "../Graphics/Point.h"
#include "../Graphics/Size.h"

// Third party includes

namespace Falltergeist
{
namespace Graphics
{

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

}
}
#endif // FALLTERGEIST_GRAPHICS_RECT_H
