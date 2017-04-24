/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2012-2016 Falltergeist developers
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

// Related headers
#include "../Fon/File.h"

// C++ standard includes

// Falltergeist includes
#include "../Dat/Stream.h"
#include "../Fon/Glyph.h"

// Third party includes

namespace Falltergeist
{
namespace Format
{
namespace Fon
{

File::File(Dat::Stream&& stream)
{
    stream.setPosition(0);

    _numchars = stream.uint32();
    _maximumHeight = stream.uint32();
    _horizontalGap = stream.uint32();
    _verticalGap = _horizontalGap; // i hope
    stream.skipBytes(8);

    for (unsigned int i = 0; i < _numchars; ++i)
    {
        uint32_t width = stream.uint32();
        uint32_t offset = stream.uint32();

        if (width > _maximumWidth)
        {
            _maximumWidth = width;
        }
        _glyphs.push_back(Glyph(width, _maximumHeight));
        _glyphs.back().setDataOffset(offset);
    }

    _spaceWidth = _glyphs.at(0x20).width();

    _loadRgba(stream);
}

void File::_loadRgba(Dat::Stream& stream)
{
    _rgba.resize((_maximumWidth + 2) * 16 * (_maximumHeight + 2) * 16);

    for (unsigned int i=0; i < _numchars; i++)
    {
        uint32_t glyphY = (i/16) * _maximumHeight+(i/16)*2+1;
        uint32_t glyphX = (i%16) * _maximumWidth+(i%16)*2+1;

        // Move glyph to bottom
        glyphY += _maximumHeight - _glyphs.at(i).height();

        if (_maximumHeight * _glyphs.at(i).width() != 0)
        {
            uint32_t offset = _glyphs.at(i).dataOffset();
            uint32_t bytesPerLine = (_glyphs.at(i).width() + 7) / 8;
            for (unsigned int y = 0; y < _maximumHeight; y++)
            {
                for (unsigned int x = 0; x < _glyphs.at(i).width(); x++)
                {
                    // [offset + y * bytesPerLine + (x / 8)]
                    stream.setPosition(0x0414+offset + y * bytesPerLine + (x / 8));
                    uint8_t b = stream.uint8();

                    if (b & (1 << (7 - (x % 8))))
                    {
                        _rgba[(glyphY + y)*(_maximumWidth+2)*16  + glyphX + x] = 0xFFFFFFFF;
                    }
                    else
                    {
                        _rgba[(glyphY + y)*(_maximumWidth+2)*16  + glyphX + x] = 0x00000000;
                    }
                }
            }

        }
    }
}

uint32_t* File::rgba()
{
    return _rgba.data();
}

const std::vector<Glyph>& File::glyphs() const
{
    return _glyphs;
}

uint32_t File::maximumHeight() const
{
    return _maximumHeight;
}

uint32_t File::maximumWidth() const
{
    return _maximumWidth;
}

uint32_t File::horizontalGap() const
{
    return _horizontalGap;
}

uint32_t File::verticalGap() const
{
    return _horizontalGap;
}

uint32_t File::spaceWidth() const
{
    return _spaceWidth;
}

}
}
}
