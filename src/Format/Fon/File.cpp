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
#include "../Fon/Glyph.h"

// Third party includes

namespace Falltergeist
{
namespace Format
{
namespace Fon
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
    for (auto glyph : _glyphs)
    {
        delete glyph;
    }
    delete [] _rgba;
}

void File::_initialize()
{
    if (_initialized) return;
    Dat::Item::_initialize();
    Dat::Item::setPosition(0);

    _numchars = uint32();
    _maximumHeight = uint32();
    _horizontalGap = uint32();
    _verticalGap = _horizontalGap; // i hope
    skipBytes(8);

    for (unsigned int i=0;i<_numchars;i++)
    {
        uint32_t width = uint32();
        uint32_t offset = uint32();

        if (width > _maximumWidth)
        {
            _maximumWidth = width;
        }
        _glyphs.push_back(new Glyph(width, _maximumHeight));
        _glyphs.back()->setDataOffset(offset);

    }

    _spaceWidth = _glyphs.at(0x20)->width();
}

uint32_t *File::rgba()
{
    if (_rgba) return _rgba;
    _rgba = new uint32_t[(_maximumWidth+2)*16 * (_maximumHeight+2) * 16]();

    for (unsigned int i=0; i < _numchars; i++)
    {
        uint32_t glyphY = (i/16) * _maximumHeight+(i/16)*2+1;
        uint32_t glyphX = (i%16) * _maximumWidth+(i%16)*2+1;

        // Move glyph to bottom
        glyphY += _maximumHeight - _glyphs.at(i)->height();

        if (_maximumHeight * _glyphs.at(i)->width() != 0)
        {
            uint32_t offset = _glyphs.at(i)->dataOffset();
            uint32_t bytesPerLine = (_glyphs.at(i)->width() + 7) / 8;
            for(unsigned int y = 0; y < _maximumHeight; y++)
            {
                for(unsigned int x = 0; x < _glyphs.at(i)->width(); x++)
                {
                    // [offset + y * bytesPerLine + (x / 8)]
                    setPosition(0x0414+offset + y * bytesPerLine + (x / 8));
                    uint8_t b = uint8();

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
    return _rgba;
}

std::vector<Glyph *>* File::glyphs()
{
    return &_glyphs;
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
