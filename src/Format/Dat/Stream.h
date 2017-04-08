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

#ifndef FALLTERGEIST_FORMAT_DAT_STREAM_H
#define FALLTERGEIST_FORMAT_DAT_STREAM_H

// C++ standard includes
#include <fstream>
#include <string>
#include <memory>

// Falltergeist includes
#include "../../Base/Buffer.h"
#include "../../Format/Enums.h"

// Third party includes

namespace Falltergeist
{
namespace Format
{
namespace Dat
{

class Entry;

// An abstract data stream for binary resource files loaded from either Dat file or a file system
class Stream: public std::streambuf
{
public:
    Stream(std::ifstream& stream);
    Stream(Dat::Entry& datFileEntry);

    Stream(Stream&& other);
    Stream(const Stream&) = delete;
    Stream& operator= (Stream&& other);
    Stream& operator= (const Stream&) = delete;

    virtual std::streambuf::int_type underflow();

    Stream& readBytes(uint8_t* destination, size_t size);
    Stream& skipBytes(size_t numberOfBytes);
    Stream& setPosition(size_t position);
    size_t position() const;
    size_t size() const;

    size_t bytesRemains();

    ENDIANNESS endianness();
    void setEndianness(ENDIANNESS value);

    uint32_t uint32();
    int32_t int32();
    uint16_t uint16();
    int16_t int16();
    uint8_t uint8();
    int8_t int8();

    Stream& operator>>(uint32_t &value);
    Stream& operator>>(int32_t &value);
    Stream& operator>>(uint16_t &value);
    Stream& operator>>(int16_t &value);
    Stream& operator>>(uint8_t &value);
    Stream& operator>>(int8_t &value);

private:
    Base::Buffer<char> _buffer;
    ENDIANNESS _endianness = ENDIANNESS::BIG;
};

}
}
}
#endif //FALLTERGEIST_FORMAT_DAT_STREAM_H
