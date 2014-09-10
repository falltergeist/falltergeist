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
    unsigned int _xPosition = 0;
    unsigned int _yPosition = 0;
    unsigned int _width = 0;
    unsigned int _height = 0;

public:
    LocationCamera(unsigned int width, unsigned int height, unsigned int xPosition, unsigned int yPosition);
    ~LocationCamera();

    unsigned int x();
    unsigned int y();

    unsigned int xPosition();
    void setXPosition(unsigned int value);

    unsigned int yPosition();
    void setYPosition(unsigned int value);

    unsigned int height();
    void setHeight(unsigned int value);

    unsigned int width();
    void setWidth(unsigned int value);
};

}
#endif // FALLTERGEIST_LOCATIONCAMERA_H
