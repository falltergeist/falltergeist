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

#ifndef FALLTERGEIST_FORMAT_AAF_FILE_H
#define FALLTERGEIST_FORMAT_AAF_FILE_H

// C++ standard includes
#include <cstdint>
#include <fstream>
#include <memory>
#include <vector>

// Falltergeist includes
#include "../../Format/Aaf/Glyph.h"
#include "../../Format/Dat/Item.h"

// Third party includes

namespace Falltergeist
{
namespace Format
{
namespace Dat
{
class Stream;
}

namespace Aaf
{

class File : public Dat::Item
{
public:
    File(Dat::Stream&& stream);

    uint32_t* rgba();

    const std::vector<Glyph>& glyphs() const;

    uint16_t maximumHeight() const;
    uint16_t maximumWidth() const;
    uint16_t horizontalGap() const;
    uint16_t verticalGap() const;
    uint16_t spaceWidth() const;

protected:
    std::vector<Glyph> _glyphs;
    uint32_t _signature;
    uint16_t _maximumHeight = 0;
    uint16_t _maximumWidth = 0;
    uint16_t _horizontalGap = 0;
    uint16_t _spaceWidth = 0;
    uint16_t _verticalGap = 0;
    std::vector<uint32_t> _rgba;

    void _loadRgba(Dat::Stream& stream);
};

}
}
}
#endif // FALLTERGEIST_FORMAT_AAF_FILE_H
