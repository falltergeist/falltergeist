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

// Falltergeist includes
#include "../Base/StlFeatures.h"
#include "../Graphics/Texture.h"
#include "../ResourceManager.h"
#include "../UI/BigCounter.h"
#include "../UI/Image.h"

// Third party includes

namespace Falltergeist
{

using namespace Base;

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

    if (_textureOnDemand) return _textureOnDemand.get();

    auto numbers = make_unique<Image>("art/intrface/bignum.frm");
    unsigned int xOffsetByColor = 0;
    switch (_color)
    {
        case COLOR_WHITE:
            break;
        case COLOR_RED:
            xOffsetByColor = 168;
            break;
    }

    _textureOnDemand = Texture::generateTextureForNumber(
        _number, _length, numbers->texture(),
        kCharWidth, kCharHeight, xOffsetByColor);
    return _textureOnDemand.get();
}

void BigCounter::setTexture(Texture* texture)
{
    _textureOnDemand.reset(texture);
}

void BigCounter::setNumber(unsigned int number)
{
    if (_number == number) return;
    _textureOnDemand.reset();
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
                _textureOnDemand.reset();
            }
            break;
    }
}

unsigned char BigCounter::color()
{
    return _color;
}

}
