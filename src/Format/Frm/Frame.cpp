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
#include "../Frm/Frame.h"

// Third party includes

namespace Falltergeist
{
namespace Format
{
namespace Frm
{

Frame::Frame(uint16_t width, uint16_t height) : _indexes(width * height, 0)
{
    _width = width;
    _height = height;
}

uint16_t Frame::width() const
{
    return _width;
}

uint16_t Frame::height() const
{
    return _height;
}

int16_t Frame::offsetX() const
{
    return _offsetX;
}

void Frame::setOffsetX(int16_t value)
{
    _offsetX = value;
}

int16_t Frame::offsetY() const
{
    return _offsetY;
}

void Frame::setOffsetY(int16_t value)
{
    _offsetY = value;
}

uint8_t Frame::index(uint16_t x, uint16_t y) const
{
    if (x >= _width || y >= _height) return 0;

    return _indexes.at(_width*y + x);
}

uint8_t* Frame::data()
{
    return _indexes.data();
}

}
}
}
