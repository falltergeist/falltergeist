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
#include <algorithm>

// Falltergeist includes
#include "../Frm/Direction.h"
#include "../Frm/Frame.h"

// Third party includes

namespace Falltergeist
{
namespace Format
{
namespace Frm
{

Direction::Direction()
{
}

Direction::~Direction()
{
    for (auto frame : _frames)
    {
        delete frame;
    }
}

int16_t Direction::shiftX() const
{
    return _shiftX;
}

void Direction::setShiftX(int16_t value)
{
    _shiftX = value;
}

int16_t Direction::shiftY() const
{
    return _shiftY;
}

void Direction::setShiftY(int16_t value)
{
    _shiftY = value;
}

uint32_t Direction::dataOffset() const
{
    return _dataOffset;
}

uint16_t Direction::width() const
{
    std::vector<uint16_t> widths;
    for (auto frame : _frames)
    {
        widths.push_back(frame->width()+2);
    }
    return (*std::max_element(widths.begin(), widths.end())) * _frames.size();
}

uint16_t Direction::height() const
{
    std::vector<uint16_t> heights;
    for (auto frame : _frames)
    {
        heights.push_back(frame->height()+2);
    }
    return *std::max_element(heights.begin(), heights.end());
}

void Direction::setDataOffset(uint32_t value)
{
    _dataOffset = value;
}

std::vector<Frame*>* Direction::frames()
{
    return &_frames;
}

}
}
}
