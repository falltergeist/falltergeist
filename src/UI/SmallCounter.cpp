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
#include "../UI/Image.h"
#include "../UI/SmallCounter.h"

// Third party includes

namespace Falltergeist
{

SmallCounter::SmallCounter(int x, int y) : ActiveUI(x, y)
{
}

SmallCounter::~SmallCounter()
{
}

Texture* SmallCounter::texture() const
{
    static const int kCharWidth = 9;
    static const int kCharHeight = 16;

    if (_textureOnDemand) return _textureOnDemand.get();

    auto numbers = make_unique<Image>("art/intrface/numbers.frm");
    unsigned int xOffsetByColor = 0;
    switch (_color)
    {
        case COLOR_WHITE:
            break;
        case COLOR_YELLOW:
            xOffsetByColor = 120;
            break;
        case COLOR_RED:
            xOffsetByColor = 240;
            break;
    }

    // number as text, always positive
    auto texture = Texture::generateTextureForNumber(
        abs(_number), _length, numbers->texture(),
        kCharWidth, kCharHeight, xOffsetByColor, true);
    if (_type == SIGNED)
    {
        // must be 9*13+1, but it is 113
        const auto signOffset = _number < 0 ? kCharWidth * 12 + 1 : 113;
        // sign of _number
        numbers->texture()->copyTo(texture.get(), 0, 0, signOffset, 0, kCharWidth, kCharHeight);
    }
    return (_textureOnDemand = std::move(texture)).get();
}

void SmallCounter::setTexture(Texture* texture)
{
    _textureOnDemand.reset(texture);
}

void SmallCounter::setLength(unsigned int length)
{
    if (_length == length) return;
    _textureOnDemand.reset();
    _length = length;
}

unsigned int SmallCounter::length()
{
    return _length;
}

void SmallCounter::setNumber(signed int number)
{
    if (_number == number) return;
    _textureOnDemand.reset();
    _number = number;
}

signed int SmallCounter::number()
{
    return _number;
}

void SmallCounter::setColor(unsigned char color)
{
    switch(color)
    {
        case COLOR_WHITE:
        case COLOR_YELLOW:
        case COLOR_RED:
            if (_color != color)
            {
                _color = color;
                _textureOnDemand.reset();
            }
            break;
    }
}

unsigned char SmallCounter::color()
{
    return _color;
}

void SmallCounter::setType(unsigned int type)
{
    _type = 0; // unsigned by default
    switch(type)
    {
        case UNSIGNED:
        case SIGNED:
            _type = type;
            break;
    }
}

unsigned int SmallCounter::type()
{
    return _type;
}

}
