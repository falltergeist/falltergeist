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
#include <string.h> // for memcpy
#include <algorithm>

// Falltergeist includes
#include "../../Format/Dat/Entry.h"
#include "../../Format/Dat/File.h"
#include "../../Format/Dat/Item.h"

// Third party includes
#include "zlib.h"

namespace Falltergeist
{
namespace Format
{
namespace Dat
{

Item::Item(std::ifstream * stream)
{
    _stream = stream;
}


Item::Item(Entry* datFileEntry)
{
    _datFileEntry = datFileEntry;
    setFilename(datFileEntry->filename());
}

void Item::_initialize()
{
    if (_initialized) return;
    _initialized = true;

    if (_stream != 0)
    {
        _stream->seekg(0, std::ios::end);
        _size = _stream->tellg();
        _stream->seekg(0, std::ios::beg);

        _buffer = new uint8_t[_size];
        _stream->read((char*)_buffer, _size);
        _stream->close();
        setg((char*)_buffer, (char*)_buffer, (char*)_buffer + _size);
        return;
    }

    if (_datFileEntry != 0)
    {

        _buffer = new uint8_t[_datFileEntry->unpackedSize()];
        _size = _datFileEntry->unpackedSize();

        auto datFile = _datFileEntry->datFile();
        unsigned int oldPos = datFile->position();
        datFile->setPosition(_datFileEntry->dataOffset());

        if (_datFileEntry->compressed())
        {
            char * packedData = new char[_datFileEntry->packedSize()]();
            datFile->readBytes(packedData, _datFileEntry->packedSize());

            // unpacking
            z_stream zStream;
            zStream.total_in  = _datFileEntry->packedSize();
            zStream.avail_in = _datFileEntry->packedSize();
            zStream.next_in  = (unsigned char *)packedData;
            zStream.total_out = zStream.avail_out = _size;
            zStream.next_out = (unsigned char *)_buffer;
            zStream.zalloc = Z_NULL;
            zStream.zfree = Z_NULL;
            zStream.opaque = Z_NULL;
            inflateInit( &zStream );            // zlib function
            inflate( &zStream, Z_FINISH );      // zlib function
            inflateEnd( &zStream );             // zlib function

            delete [] packedData;
        }
        else
        {
            datFile->readBytes((char*)_buffer, _size);
        }

        datFile->setPosition(oldPos);
        setg((char*)_buffer, (char*)_buffer, (char*)_buffer + _size);
        return;
    }
}


Item::~Item()
{
    delete [] _buffer;
}

uint32_t Item::size()
{
    _initialize();
    return _size;
}

std::streambuf::int_type Item::underflow()
{
    _initialize();
    if (gptr() == egptr())
    {
        return traits_type::eof();
    }
    return traits_type::to_int_type(*gptr());
}

Item* Item::setFilename(const std::string filename)
{
    _filename = filename;

    // convert to lowercase and replace slashes
    std::replace(_filename.begin(),_filename.end(),'\\','/');
    std::transform(_filename.begin(),_filename.end(),_filename.begin(), ::tolower);
    return this;
}

std::string Item::filename()
{
    return _filename;
}

Item* Item::setPosition(unsigned int pos)
{
    _initialize();
    setg((char*)_buffer, (char*)_buffer + pos, (char*)_buffer + _size);
    return this;
}

uint32_t Item::position()
{
    _initialize();
    return gptr() - eback();
}

Item* Item::skipBytes(unsigned int numberOfBytes)
{
    _initialize();
    setg((char*)_buffer, gptr() + numberOfBytes, (char*)_buffer + _size);
    return this;
}

Item* Item::readBytes(uint8_t* destination, uint32_t size)
{
    _initialize();
    sgetn((char*)destination, size);
    return this;
}


Item& Item::operator>>(uint32_t &value)
{
    _initialize();
    char * buff = reinterpret_cast<char *>(&value);
    sgetn(buff, sizeof(value));
    if (endianness() == ENDIANNESS::BIG) std::reverse(buff, buff + sizeof(value));
    return *this;
}

Item& Item::operator>>(int32_t &value)
{
    return *this >> (uint32_t&) value;
}

Item& Item::operator>>(uint16_t &value)
{
    _initialize();
    char * buff = reinterpret_cast<char *>(&value);
    sgetn(buff, sizeof(value));
    if (endianness() == ENDIANNESS::BIG) std::reverse(buff, buff + sizeof(value));
    return *this;
}

Item& Item::operator>>(int16_t &value)
{
    return *this >> (uint16_t&) value;
}

Item& Item::operator>>(uint8_t &value)
{
    _initialize();
    sgetn(reinterpret_cast<char *>(&value), sizeof(value));
    return *this;
}

Item& Item::operator>>(int8_t &value)
{
    return *this >> (uint8_t&) value;
}

ENDIANNESS Item::endianness()
{
    return _endianness;
}

void Item::setEndianness(ENDIANNESS value)
{
    _endianness = value;
}

unsigned int Item::bytesRemains()
{
    return size() - position();
}

uint32_t Item::uint32()
{
    uint32_t value;
    *this >> value;
    return value;
}

int32_t Item::int32()
{
    return uint32();
}

uint16_t Item::uint16()
{
    uint16_t value;
    *this >> value;
    return value;
}

int16_t Item::int16()
{
    return uint16();
}

uint8_t Item::uint8()
{
    uint8_t value;
    *this >> value;
    return value;
}

int8_t Item::int8()
{
    return uint8();
}

}
}
}
