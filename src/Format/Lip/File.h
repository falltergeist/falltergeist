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

#ifndef FALLTERGEIST_FORMAT_LIP_FILE_H
#define FALLTERGEIST_FORMAT_LIP_FILE_H

// C++ standard includes
#include <string>
#include <vector>

// Falltergeist includes
#include "../Dat/Item.h"

// Third party includes

namespace Falltergeist
{
namespace Format
{
namespace Dat
{
class Stream;
}

namespace Lip
{

class File : public Dat::Item
{
public:
    File(Dat::Stream&& stream);
    std::string acmName();
    uint32_t phonemesCount();
    uint32_t markersCount();
    uint32_t acmSize();
    std::vector<uint32_t>& timestamps();
    std::vector<uint8_t>& phonemes();

protected:
    uint32_t _version;
    uint32_t _unknown1;
    uint32_t _unknown2;
    uint32_t _unknown3;
    uint32_t _acmSize;
    uint32_t _phonemesCount;
    uint32_t _unknown4;
    uint32_t _markersCount;
    uint8_t  _acmName[8];
    uint8_t  _unknown5[4];
    std::vector<uint8_t> _phonemes;
    std::vector<uint32_t> _markerSamples;
    std::vector<uint32_t> _markerTimestamps;

};

}
}
}
#endif // FALLTERGEIST_FORMAT_LIP_FILE_H
