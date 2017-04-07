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
#include "../../Exception.h"
#include "../../Format/Dat/Stream.h"
#include "../../Format/Lip/File.h"

// Third party includes

namespace Falltergeist
{
namespace Format
{
namespace Lip
{

File::File(Dat::Stream&& stream) 
{
    stream.setPosition(0);
    stream >> _version;
    if (_version != 2)
    {
        throw Exception("Invalid LIP file.");
    }
    stream >> _unknown1 >> _unknown2 >> _unknown3;
    stream >> _acmSize >> _phonemesCount;
    stream >> _unknown4;
    stream >> _markersCount;
    stream.readBytes(_acmName, 8);
    stream.readBytes(_unknown5, 4);

    for (uint32_t i=0; i < _phonemesCount; i++)
    {
        uint8_t phoneme;
        stream >> phoneme;
        _phonemes.push_back(phoneme);
    }

    for (uint32_t i=0; i < _markersCount; i++)
    {
        uint32_t stype, smarker;
        stream >> stype >> smarker;
        _markerSamples.push_back(smarker);
        _markerTimestamps.push_back(smarker*1000 / 22050 /2); //ms
    }
}

std::string File::acmName()
{
    return std::string((char*)_acmName)+std::string((char*)_unknown5);
}

uint32_t File::phonemesCount()
{
    return _phonemesCount;
}

uint32_t File::markersCount()
{
    return _markersCount;
}

uint32_t File::acmSize()
{
    return _acmSize;
}

std::vector<uint32_t>& File::timestamps()
{
    return _markerTimestamps;
}

std::vector<uint8_t> &File::phonemes()
{
    return _phonemes;
}


}
}
}
