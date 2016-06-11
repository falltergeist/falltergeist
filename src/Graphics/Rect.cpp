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
#include "../Graphics/Rect.h"

// C++ standard includes
#include <algorithm>

// Falltergeist includes

// Third party includes

namespace Falltergeist
{
namespace Graphics
{

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
    const Point bottomRight1 = topLeft1 + size1;
    const Point bottomRight2 = topLeft2 + size2;

    return !(std::max(topLeft1.x(), topLeft2.x()) > std::min(bottomRight1.x(), bottomRight2.x())
             || std::max(topLeft1.y(), topLeft2.y()) > std::min(bottomRight1.y(), bottomRight2.y()));
}

}
}
