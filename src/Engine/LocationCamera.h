/*
 * Copyright 2012-2014 Falltergeist Developers.
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

// Third party includes

namespace Falltergeist
{

class LocationCamera
{
protected:
    int _xPosition = 0;
    int _yPosition = 0;
    int _width = 0;
    int _height = 0;

public:
    LocationCamera(int width, int height, int xPosition, int yPosition);
    ~LocationCamera();

    int x();
    int y();

    int xPosition();
    void setXPosition(int value);

    int yPosition();
    void setYPosition(int value);

    int height();
    void setHeight(int value);

    int width();
    void setWidth(int value);
};

}
#endif // FALLTERGEIST_LOCATIONCAMERA_H
