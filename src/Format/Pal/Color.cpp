/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2012-2015 Falltergeist developers
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

// C++ standard includes

// Falltergeist includes
#include "../Pal/Color.h"

// Third party includes

namespace Falltergeist
{
namespace Format
{
namespace Pal
{

Color::Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
    _red = red;
    _green = green;
    _blue = blue;
    _alpha = alpha;
}

Color::~Color()
{
}

void Color::setRed(uint8_t red)
{
    _red = red;
}

uint8_t Color::red() const
{
    return _red;
}

void Color::setGreen(uint8_t green)
{
    _green = green;
}

uint8_t Color::green() const
{
    return _green;
}

void Color::setBlue(uint8_t blue)
{
    _blue = blue;
}

uint8_t Color::blue() const
{
    return _blue;
}

void Color::setAlpha(uint8_t alpha)
{
    _alpha = alpha;
}

uint8_t Color::alpha() const
{
    return _alpha;
}

Color::operator int() const
{
    return (int) (unsigned int) *this;
}

Color::operator unsigned int() const
{
    uint8_t k;
    if (_nomod) {
        k = 1;
    }
    else
    {
        k = 4;
    }
    return ((red() * k) << 24) | ((green() * k) << 16) | ((blue() * k) << 8) | alpha();
}

void Color::nomod() {
_nomod= true;
}
}
}
}
