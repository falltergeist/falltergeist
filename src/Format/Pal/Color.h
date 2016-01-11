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

#ifndef FALLTERGEIST_FORMAT_PAL_COLOR_H
#define FALLTERGEIST_FORMAT_PAL_COLOR_H

// C++ standard includes
#include <cstdint>

// Falltergeist includes

// Third party includes

namespace Falltergeist
{
namespace Format
{
namespace Pal
{

class Color
{

public:
    Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255);
    ~Color();

    operator int() const;
    operator unsigned int() const;

    void setRed(uint8_t red);
    uint8_t red() const;

    void setGreen(uint8_t green);
    uint8_t green() const;

    void setBlue(uint8_t blue);
    uint8_t blue() const;

    void setAlpha(uint8_t alpha);
    uint8_t alpha() const;

protected:
    uint8_t _red;
    uint8_t _green;
    uint8_t _blue;
    uint8_t _alpha;


};

}
}
}
#endif // FALLTERGEIST_FORMAT_PAL_COLOR_H
