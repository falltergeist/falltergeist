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

// C++ standard includes
#include <iostream>
#include <sstream>
#include <string.h>

// Falltergeist includes
#include "../UI/BigCounter.h"
#include "../Engine/ResourceManager.h"
#include "../UI/Image.h"
#include "../Engine/Graphics/Texture.h"

// Third party includes

namespace Falltergeist
{

BigCounter::BigCounter(int x, int y) : ActiveUI(x, y)
{
}

BigCounter::~BigCounter()
{
    delete _texture;
}

Texture* BigCounter::texture()
{
    if (_texture) return _texture;

    auto numbers = new Image("art/intrface/bignum.frm");

    // number as text
    std::stringstream ss;
    ss << _number;

    _texture = new Texture(14*_length, 24);

    char* textNumber = new char[_length + 1]();

    for (unsigned int i = 0; i < _length; ++i)
    {
        textNumber[i] = '0';
    }

    unsigned int length = strlen(ss.str().c_str());
    unsigned int diff = _length - length;
    for (unsigned int i = 0; i < length; i++)
    {
        textNumber[diff + i] = ss.str().c_str()[i];
    }

    for (unsigned int i = 0; i < _length; i++)
    {
        int key = 9 -  ('9' - textNumber[i]);
        unsigned int x = 14 * key;
        switch (_color)
        {
            case COLOR_WHITE:
                break;
            case COLOR_RED:
                x += 168;
                break;
        }
        numbers->texture()->copyTo(_texture, 14*i, 0, x, 0, 14, 24);
    }
    delete [] textNumber;
    delete numbers;
    return _texture;
}

void BigCounter::setNumber(unsigned int number)
{
    if (_number == number) return;

    _number = number;
    delete _texture;
    _texture = 0;
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
                delete _texture;
                _texture = 0;
            }
            break;
    }
}

unsigned char BigCounter::color()
{
    return _color;
}

}
