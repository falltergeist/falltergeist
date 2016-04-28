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
#include "../UI/BigCounter.h"

// C++ standard includes

// Falltergeist includes
#include "../Graphics/Texture.h"
#include "../ResourceManager.h"
#include "../UI/Image.h"

// Third party includes

namespace Falltergeist
{
namespace UI
{

BigCounter::BigCounter(int x, int y, unsigned int length) : BigCounter(Point(x, y), length)
{
}

BigCounter::BigCounter(const Point& pos, unsigned int length) : Base(pos)
{
    _length = length;
    _sprite = std::make_shared<Graphics::Sprite>("art/intrface/bignum.frm");
    for (int i = 0; i < 24; i++)
    {
        _rects.push_back({i*14, 0, 14, 24});
    }
}

BigCounter::~BigCounter()
{
}

void BigCounter::setNumber(unsigned int number)
{
    _number = number;
    _numberText = std::to_string(number);
    if (_numberText.size() < _length)
    {
        _numberText.insert(0, _length - _numberText.size(), '0');
    }
}

unsigned int BigCounter::number()
{
    return _number;
}


void BigCounter::setColor(Color color)
{
    switch (color)
    {
        case Color::WHITE:
        case Color::RED:
            if (_color != color)
            {
                _color = color;
                //_textureOnDemand.reset();
            }
            break;
    }
}

BigCounter::Color BigCounter::color()
{
    return _color;
}


void BigCounter::render(bool eggTransparency)
{
    for (unsigned int i=0; i<_length;i++)
    {
        int num = _numberText.at(i)-'0';
        if (_color==Color::RED)
        {
            num += 12;
        }
        SDL_Rect rect = _rects.at(num);
        _sprite->renderCropped(position().x() + i * 14, position().y(), rect.x, rect.y, rect.w, rect.h);
    }
}

bool BigCounter::opaque(const Point &pos) {
    return false;
}
}
}
