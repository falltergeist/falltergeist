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

#ifndef FALLTERGEIST_FORMAT_FON_FILE_H
#define FALLTERGEIST_FORMAT_FON_FILE_H

// C++ standard includes
#include <vector>

// Falltergeist includes
#include "../Dat/Item.h"

// Third party includes

namespace Falltergeist
{
namespace Format
{
namespace Fon
{

class Glyph;

class File : public Dat::Item
{

public:
    File(Dat::Entry* datFileEntry);
    File(std::ifstream* stream);
    virtual ~File();
    uint32_t* rgba();

    std::vector<Glyph*>* glyphs();

    uint32_t maximumHeight() const;
    uint32_t maximumWidth() const;
    uint32_t horizontalGap() const;
    uint32_t verticalGap() const;
    uint32_t spaceWidth() const;


protected:
    virtual void _initialize();
    std::vector<Glyph*> _glyphs;
    uint32_t _maximumHeight = 0;
    uint32_t _maximumWidth = 0;
    uint32_t _horizontalGap = 0;
    uint32_t _spaceWidth = 0;
    uint32_t _verticalGap = 0;
    uint32_t* _rgba = 0;
    uint32_t _numchars;

};

}
}
}
#endif // FALLTERGEIST_FORMAT_FON_FILE_H
