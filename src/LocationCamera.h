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

#ifndef FALLTERGEIST_LOCATIONCAMERA_H
#define FALLTERGEIST_LOCATIONCAMERA_H

// C++ standard includes

// Falltergeist includes
#include "Graphics/Point.h"
#include "Graphics/Size.h"

// Third party includes

namespace Falltergeist
{

using Graphics::Point;
using Graphics::Size;

class LocationCamera
{
protected:
    Point _center;
    Size _size;

public:
    LocationCamera(const Size& size, const Point& center);
    ~LocationCamera();

    Point topLeft() const;

    const Point& center() const;
    void setCenter(const Point& pos);

    const Size& size() const;
    void setSize(const Size& size);
};

}
#endif // FALLTERGEIST_LOCATIONCAMERA_H
