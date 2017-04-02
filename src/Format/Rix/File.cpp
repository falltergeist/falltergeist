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
#include "../Rix/File.h"

// Third party includes

namespace Falltergeist
{
namespace Format
{
namespace Rix
{

File::File(Dat::Entry* datFileEntry) : Dat::Item(datFileEntry)
{
    _initialize();
}

File::File(std::ifstream* stream) : Dat::Item(stream)
{
    _initialize();
}

File::~File()
{
    delete [] _rgba;
}

void File::_initialize()
{
    if (_initialized) return;
    Dat::Item::_initialize();
    Dat::Item::setPosition(0);

    // Signature
    uint32();

    this->setEndianness(ENDIANNESS::LITTLE);
    _width = uint16();
    _height = uint16();
    this->setEndianness(ENDIANNESS::BIG);

    // Unknown 1
    uint16();

    uint32_t palette[256];

    // Palette
    for (unsigned i = 0; i != 256; ++i)
    {
        uint8_t r = uint8();
        uint8_t g = uint8();
        uint8_t b = uint8();
        palette[i] = static_cast<uint32_t >(r << 26 | g << 18 | b << 10 | 0x000000FF);  // RGBA
    }

    _rgba = new uint32_t[_width*_height];

    // Data
    for (unsigned i = 0; i != (unsigned)_width*_height; ++i)
    {
        _rgba[i] = palette[uint8()];
    }
}

uint16_t File::width() const
{
    return _width;
}

uint16_t File::height() const
{
    return _height;
}

uint32_t* File::rgba() const
{
    return _rgba;
}

}
}
}
