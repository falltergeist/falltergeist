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

#ifndef FALLTERGEIST_FORMAT_FRM_DIRECTION_H
#define FALLTERGEIST_FORMAT_FRM_DIRECTION_H

// C++ standard includes
#include <cstdint>
#include <vector>

// Falltergeist includes
#include "../Frm/Frame.h"

// Third party includes

namespace Falltergeist
{
namespace Format
{
namespace Frm
{

class Direction
{
public:
    Direction() = default;
    Direction(Direction&&) = default;
    Direction(const Direction&) = delete;
    Direction& operator= (const Direction&) = delete;
    Direction& operator= (Direction&&) = default;
    ~Direction() = default;

    int16_t shiftX() const;
    void setShiftX(int16_t value);

    int16_t shiftY() const;
    void setShiftY(int16_t value);

    uint32_t dataOffset() const;
    void setDataOffset(uint32_t value);

    uint16_t width() const;
    uint16_t height() const;

    std::vector<Frame>& frames();
    const std::vector<Frame>& frames() const;

protected:
    int16_t _shiftX = 0;
    int16_t _shiftY = 0;
    uint32_t _dataOffset = 0;
    std::vector<Frame> _frames;

};

}
}
}
#endif // FALLTERGEIST_FORMAT_FRM_DIRECTION_H
