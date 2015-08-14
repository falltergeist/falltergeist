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

// C++ standard includes
#include <sstream>
#include <string.h>

// Falltergeist includes
#include "../Graphics/Texture.h"
#include "../ResourceManager.h"
#include "../UI/BigCounter.h"
#include "../UI/Image.h"

// Third party includes

namespace Falltergeist
{

BigCounter::BigCounter(int x, int y, unsigned int length) : ActiveUI(x, y)
{
    _length = length;
}

BigCounter::~BigCounter()
{
}

Texture* BigCounter::texture() const
{
    static const int kCharWidth = 14;
    static const int kCharHeight = 24;

    if (_texture) return _texture;

    auto numbers = std::unique_ptr<Image>(new Image("art/intrface/bignum.frm"));
    unsigned int xOffsetByColor = 0;
    switch (_color)
    {
        case COLOR_WHITE:
            break;
        case COLOR_RED:
            xOffsetByColor = 168;
            break;
    }

    auto texture = Texture::generateTextureForNumber(
        _number, _length, numbers->texture(),
        kCharWidth, kCharHeight, xOffsetByColor);
    return (_texture = texture.release());
}

void BigCounter::setNumber(unsigned int number)
{
    if (_number == number) return;
    delete _texture; _texture = 0;
    _number = number;
}

unsigned int BigCounter::number()
{
    return _number;
}


void BigCounter::setColor(unsigned char color)
{
    switch(color)
    {
        case COLOR_WHITE:
        case COLOR_RED:
            if (_color != color)
            {
                _color = color;
                delete _texture; _texture = 0;
            }
            break;
    }
}

unsigned char BigCounter::color()
{
    return _color;
}

}
