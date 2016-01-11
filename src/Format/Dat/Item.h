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

#ifndef FALLTERGEIST_FORMAT_DAT_ITEM_H
#define FALLTERGEIST_FORMAT_DAT_ITEM_H

// C++ standard includes
#include <fstream>
#include <string>
#include <memory>

// Falltergeist includes
#include "../../Format/Enums.h"

// Third party includes

namespace Falltergeist
{
namespace Format
{
namespace Dat
{

class Entry;

class Item: public std::streambuf
{

public:

    Item(std::ifstream* stream);
    Item(Dat::Entry* datFileEntry);
    ~Item();

    virtual std::streambuf::int_type underflow();

    Item* setFilename(const std::string filename);
    std::string filename();

    Item* readBytes(uint8_t* destination, uint32_t size);
    Item* skipBytes(unsigned int numberOfBytes);
    Item* setPosition(unsigned int position);
    uint32_t position();
    uint32_t size();

    unsigned int bytesRemains();

    ENDIANNESS endianness();
    void setEndianness(ENDIANNESS value);

    uint32_t uint32();
    int32_t int32();
    uint16_t uint16();
    int16_t int16();
    uint8_t uint8();
    int8_t int8();

    Item& operator>>(uint32_t &value);
    Item& operator>>(int32_t &value);
    Item& operator>>(uint16_t &value);
    Item& operator>>(int16_t &value);
    Item& operator>>(uint8_t &value);
    Item& operator>>(int8_t &value);

protected:
    std::string _filename;
    Entry* _datFileEntry = nullptr;
    std::ifstream* _stream = nullptr;

    uint8_t* _buffer = nullptr;
    int32_t _size;
    ENDIANNESS _endianness = ENDIANNESS::BIG;

    bool _initialized = false;
    virtual void _initialize();

};

}
}
}
#endif //FALLTERGEIST_FORMAT_DAT_ITEM_H
