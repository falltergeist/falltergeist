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

#ifndef FALLTERGEIST_FORMAT_FMR_FRAME_H
#define FALLTERGEIST_FORMAT_FMR_FRAME_H

// C++ standard includes
#include <cstdint>
#include <vector>

// Falltergeist includes

// Third party includes

namespace Falltergeist
{
namespace Format
{
namespace Frm
{

class Frame
{
public:
    Frame() = default;
    Frame(uint16_t width, uint16_t height);
    Frame(const Frame& other) = delete;
    Frame(Frame&& other) = default;
    Frame& operator= (const Frame&) = delete;
    Frame& operator= (Frame&&) = default;
    ~Frame() = default;

    uint16_t width() const;
    uint16_t height() const;

    int16_t offsetX() const;
    void setOffsetX(int16_t value);

    int16_t offsetY() const;
    void setOffsetY(int16_t value);

    uint8_t index(uint16_t x, uint16_t y) const;

    uint8_t* data();

protected:
    uint16_t _width = 0;
    uint16_t _height = 0;
    int16_t _offsetX = 0;
    int16_t _offsetY = 0;
    std::vector<uint8_t> _indexes;

};

}
}
}
#endif // FALLTERGEIST_FORMAT_FMR_FRAME_H
