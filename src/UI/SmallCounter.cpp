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
#include "../UI/SmallCounter.h"

// C++ standard includes

// Falltergeist includes
#include "../Base/StlFeatures.h"
#include "../Graphics/Texture.h"
#include "../ResourceManager.h"
#include "../UI/Image.h"

// Third party includes

namespace Falltergeist
{
namespace UI
{

using namespace Base;

SmallCounter::SmallCounter(const Point& pos) : Falltergeist::UI::Base(pos)
{
}

SmallCounter::~SmallCounter()
{
}

Graphics::Texture* SmallCounter::texture() const
{
    static const int kCharWidth = 9;
    static const int kCharHeight = 16;

    if (_textureOnDemand) return _textureOnDemand.get();

    auto numbers = make_unique<Image>("art/intrface/numbers.frm");
    unsigned int xOffsetByColor = 0;
    switch (_color)
    {
        case Color::WHITE:
            break;
        case Color::YELLOW:
            xOffsetByColor = 120;
            break;
        case Color::RED:
            xOffsetByColor = 240;
            break;
    }

    // number as text, always positive
    auto texture = Graphics::Texture::generateTextureForNumber(
        abs(_number), _length, numbers->texture(),
        kCharWidth, kCharHeight, xOffsetByColor, true);
    if (_type == Type::SIGNED)
    {
        // must be 9*13+1, but it is 113
        const auto signOffset = _number < 0 ? kCharWidth * 12 + 1 : 113;
        // sign of _number
        numbers->texture()->copyTo(texture.get(), 0, 0, signOffset, 0, kCharWidth, kCharHeight);
    }
    return (_textureOnDemand = std::move(texture)).get();
}

void SmallCounter::setTexture(Graphics::Texture* texture)
{
    _textureOnDemand.reset(texture);
}

void SmallCounter::setLength(unsigned int length)
{
    if (_length == length) return;
    _textureOnDemand.reset();
    _length = length;
}

unsigned int SmallCounter::length() const
{
    return _length;
}

void SmallCounter::setNumber(signed int number)
{
    if (_number == number) return;
    _textureOnDemand.reset();
    _number = number;
}

signed int SmallCounter::number() const
{
    return _number;
}

void SmallCounter::setColor(Color color)
{
    switch(color)
    {
        case Color::WHITE:
        case Color::YELLOW:
        case Color::RED:
            if (_color != color)
            {
                _color = color;
                _textureOnDemand.reset();
            }
            break;
    }
}

SmallCounter::Color SmallCounter::color() const
{
    return _color;
}

void SmallCounter::setType(Type type)
{
    _type = type;
}

SmallCounter::Type SmallCounter::type() const
{
    return _type;
}

}
}
