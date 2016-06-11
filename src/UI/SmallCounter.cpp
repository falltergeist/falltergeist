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
#include "../Graphics/Texture.h"
#include "../ResourceManager.h"
#include "../UI/Image.h"

// Third party includes

namespace Falltergeist
{
namespace UI
{

SmallCounter::SmallCounter(const Point& pos) : Falltergeist::UI::Base(pos)
{
    _sprite = std::make_shared<Graphics::Sprite>("art/intrface/numbers.frm");

    for (int cl = 0; cl<3; cl++) //colors
    {
        for (int i = 0; i < 12; i++) // numbers
        {
            _rects.push_back({120*cl+i * 9, 0, 9, 17});
        }
        // signs are 6 px wide
        _rects.push_back({120*cl+108 + 0 * 6, 0, 6, 17});
        _rects.push_back({120*cl+108 + 1 * 6, 0, 6, 17});
    }
}

SmallCounter::~SmallCounter()
{
}

void SmallCounter::setLength(unsigned int length)
{
    _length = length;
}

unsigned int SmallCounter::length() const
{
    return _length;
}

void SmallCounter::setNumber(signed int number)
{
    _number = number;
    _numberText = std::to_string(number);
    if (_numberText.size() < _length)
    {
        _numberText.insert(0, _length - _numberText.size(), '0');
    }
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
            _color = color;
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

void SmallCounter::render(bool eggTransparency)
{
    int pad = 0;
    if (_type == Type::SIGNED)
    {
        if (_number < 0)
        {
            SDL_Rect rect = _rects.at(12*_color);
            _sprite->renderCropped(position().x(), position().y(), rect.x, rect.y, rect.w, rect.h);
        }
        else
        {
            SDL_Rect rect = _rects.at(13*_color);
            _sprite->renderCropped(position().x(), position().y(), rect.x, rect.y, rect.w, rect.h);
        }
        pad = 6;
    }
    for (unsigned int i=0; i<_length;i++)
    {
        int num = _numberText.at(i)-'0';
        switch (_color)
        {
            case Color::YELLOW:
                num+=14;
                break;
            case Color::RED:
                num+=28;
                break;
            case Color::WHITE:
            default:
                break;
        }
        SDL_Rect rect = _rects.at(num);
        _sprite->renderCropped(position().x() + pad + i * 9, position().y(), rect.x, rect.y, rect.w, rect.h);
    }
}

bool SmallCounter::opaque(const Point &pos) {
    return false;
}
}
}
