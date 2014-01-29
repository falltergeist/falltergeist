/*
 * Copyright 2012-2013 Falltergeist Developers.
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

#ifndef FALLTERGEIST_TEXTURE_H
#define FALLTERGEIST_TEXTURE_H

// C++ standard includes

// Falltergeist includes

// Third party includes

namespace Falltergeist
{

class Texture
{
protected:
    unsigned int _id = 0;
    unsigned int _width = 0;
    unsigned int _height = 0;
    unsigned int* _data = 0; // array of RGBA pixels

public:
    Texture(unsigned int width, unsigned int height);
    ~Texture();

    unsigned int id();
    void setId(unsigned int value);

    unsigned int width();
    unsigned int height();
    unsigned int* data();

    unsigned int pixel(unsigned int x, unsigned int y);
    void setPixel(unsigned int x, unsigned int y, unsigned int color);

    void loadFromRGBA(unsigned int* data);

};

}
#endif // FALLTERGEIST_TEXTURE_H
