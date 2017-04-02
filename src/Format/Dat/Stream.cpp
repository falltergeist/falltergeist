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

#include "../../Format/Dat/Stream.h"

// C++ standard includes
#include <string.h> // for memcpy
#include <algorithm>

// Falltergeist includes
#include "../../Format/Dat/Entry.h"
#include "../../Format/Dat/File.h"

// Third party includes
#include "zlib.h"

namespace Falltergeist
{
namespace Format
{
namespace Dat
{

Stream::Stream(std::ifstream& stream)
{
    stream.seekg(0, std::ios::end);
    _size = static_cast<int32_t>(stream.tellg());
    stream.seekg(0, std::ios::beg);

    _buffer = new uint8_t[_size];
    stream.read((char*)_buffer, _size);
    setg((char*)_buffer, (char*)_buffer, (char*)_buffer + _size);
}


Stream::Stream(Entry& datFileEntry)
{
    _size = datFileEntry.unpackedSize();
    _buffer = new uint8_t[_size];

    auto datFile = datFileEntry.datFile();
    unsigned int oldPos = datFile->position();
    datFile->setPosition(datFileEntry.dataOffset());

    if (datFileEntry.compressed()) {
        std::vector<char> packedData;
        packedData.reserve(datFileEntry.packedSize());
        datFile->readBytes(packedData.data(), datFileEntry.packedSize());

        // unpacking
        z_stream zStream;
        zStream.total_in = datFileEntry.packedSize();
        zStream.avail_in = datFileEntry.packedSize();
        zStream.next_in = (unsigned char *)packedData.data();
        zStream.total_out = zStream.avail_out = _size;
        zStream.next_out = (unsigned char *)_buffer;
        zStream.zalloc = Z_NULL;
        zStream.zfree = Z_NULL;
        zStream.opaque = Z_NULL;
        inflateInit(&zStream);            // zlib function
        inflate(&zStream, Z_FINISH);      // zlib function
        inflateEnd(&zStream);             // zlib function
    } else {
        datFile->readBytes((char*)_buffer, _size);
    }

    datFile->setPosition(oldPos);
    setg((char*)_buffer, (char*)_buffer, (char*)_buffer + _size);
}

Stream::~Stream()
{
    delete [] _buffer;
}

uint32_t Stream::size()
{
    return _size;
}

std::streambuf::int_type Stream::underflow()
{
    if (gptr() == egptr())
    {
        return traits_type::eof();
    }
    return traits_type::to_int_type(*gptr());
}

Stream& Stream::setPosition(unsigned int pos)
{
    setg((char*)_buffer, (char*)_buffer + pos, (char*)_buffer + _size);
    return *this;
}

uint32_t Stream::position()
{
    return static_cast<uint32_t>(gptr() - eback());
}

Stream& Stream::skipBytes(unsigned int numberOfBytes)
{
    setg((char*)_buffer, gptr() + numberOfBytes, (char*)_buffer + _size);
    return *this;
}

Stream& Stream::readBytes(uint8_t* destination, uint32_t size)
{
    sgetn((char*)destination, size);
    return *this;
}


Stream& Stream::operator>>(uint32_t &value)
{
    char * buff = reinterpret_cast<char *>(&value);
    sgetn(buff, sizeof(value));
    if (endianness() == ENDIANNESS::BIG) std::reverse(buff, buff + sizeof(value));
    return *this;
}

Stream& Stream::operator>>(int32_t &value)
{
    return *this >> (uint32_t&) value;
}

Stream& Stream::operator>>(uint16_t &value)
{
    char * buff = reinterpret_cast<char *>(&value);
    sgetn(buff, sizeof(value));
    if (endianness() == ENDIANNESS::BIG) std::reverse(buff, buff + sizeof(value));
    return *this;
}

Stream& Stream::operator>>(int16_t &value)
{
    return *this >> (uint16_t&) value;
}

Stream& Stream::operator>>(uint8_t &value)
{
    sgetn(reinterpret_cast<char *>(&value), sizeof(value));
    return *this;
}

Stream& Stream::operator>>(int8_t &value)
{
    return *this >> (uint8_t&) value;
}

ENDIANNESS Stream::endianness()
{
    return _endianness;
}

void Stream::setEndianness(ENDIANNESS value)
{
    _endianness = value;
}

unsigned int Stream::bytesRemains()
{
    return size() - position();
}

uint32_t Stream::uint32()
{
    uint32_t value;
    *this >> value;
    return value;
}

int32_t Stream::int32()
{
    return uint32();
}

uint16_t Stream::uint16()
{
    uint16_t value;
    *this >> value;
    return value;
}

int16_t Stream::int16()
{
    return uint16();
}

uint8_t Stream::uint8()
{
    uint8_t value;
    *this >> value;
    return value;
}

int8_t Stream::int8()
{
    return uint8();
}

}
}
}
