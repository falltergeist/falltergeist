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
#include "../Lip/File.h"
#include "../../Exception.h"

// Third party includes

namespace Falltergeist
{
namespace Format
{
namespace Lip
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
}

void File::_initialize()
{
    if (_initialized) return;
    Dat::Item::_initialize();
    Dat::Item::setPosition(0);
    *this >> _version;
    if (_version != 2)
    {
        throw Exception("Invalid LIP file.");
    }
    *this >> _unknown1 >> _unknown2 >> _unknown3;
    *this >> _acm_size >> _phonems_count;
    *this >> _unknown4;
    *this >> _markers_count;
    this->readBytes(_acm_name, 8);
    this->readBytes(_unknown5, 4);

    for (uint32_t i=0; i < _phonems_count; i++)
    {
        uint8_t phonem;
        *this >> phonem;
        _phonems.push_back(phonem);
    }

    for (uint32_t i=0; i < _markers_count; i++)
    {
        uint32_t stype, smarker;
        *this >> stype >> smarker;
        _marker_samples.push_back(smarker);
        _marker_timestamps.push_back(smarker*1000 / 22050 /2); //ms
    }

}

void File::init()
{
    _initialize();
}

std::string File::acmName()
{
    _initialize();
    return std::string((char*)_acm_name)+std::string((char*)_unknown5);
}

uint32_t File::pcount()
{
    _initialize();
    return _phonems_count;
}

uint32_t File::mcount()
{
    _initialize();
    return _markers_count;
}

uint32_t File::acmSize()
{
    _initialize();
    return _acm_size;
}

std::vector<uint32_t>* File::timestamps()
{
    _initialize();
    return &_marker_timestamps;
}

}
}
}
