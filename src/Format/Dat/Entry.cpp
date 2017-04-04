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
#include "../../Format/Dat/Entry.h"
#include "../../Format/Dat/File.h"

// Third party includes

namespace Falltergeist
{
namespace Format
{
namespace Dat
{

Entry::Entry(File* datFile)
{
    _datFile = datFile;
}

std::string Entry::filename() const
{
    return _filename;
}

void Entry::setFilename(std::string value)
{
    std::replace(value.begin(), value.end(), '\\','/');
    std::transform(value.begin(), value.end(), value.begin(), ::tolower);
    _filename = value;
}

uint32_t Entry::packedSize() const
{
    return _packedSize;
}

void Entry::setPackedSize(uint32_t value)
{
    _packedSize = value;
}

uint32_t Entry::unpackedSize() const
{
    return _unpackedSize;
}

void Entry::setUnpackedSize(uint32_t value)
{
    _unpackedSize = value;
}

uint32_t Entry::dataOffset() const
{
    return _dataOffset;
}

void Entry::setDataOffset(uint32_t value)
{
    _dataOffset = value;
}

bool Entry::compressed() const
{
    return _compressed;
}

void Entry::setCompressed(bool value)
{
    _compressed = value;
}

File* Entry::datFile()
{
    return _datFile;
}

}
}
}
