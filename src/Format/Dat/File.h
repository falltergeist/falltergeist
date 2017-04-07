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

#ifndef FALLTERGEIST_FORMAT_DAT_FILE_H
#define FALLTERGEIST_FORMAT_DAT_FILE_H

// C++ standard includes
#include <cstdint>
#include <fstream>
#include <memory>
#include <string>
#include <unordered_map>

// Falltergeist includes
#include "Entry.h"

// Third party includes

namespace Falltergeist
{
namespace Format
{
namespace Dat
{

class File
{
public:
    File();
    File(const std::string& pathToFile);

    std::string filename() const;
    File* setFilename(const std::string& filename);

    // an pointer to an entry with given name or nullptr if no such entry exists
    Entry* entry(const std::string& filename);

    File* readBytes(char* destination, unsigned int numberOfBytes);
    File* skipBytes(unsigned int numberOfBytes);
    File* setPosition(unsigned int position);
    unsigned int position();
    unsigned int size();

    File& operator>>(int32_t &value);
    File& operator>>(uint32_t &value);
    File& operator>>(int16_t &value);
    File& operator>>(uint16_t &value);
    File& operator>>(int8_t &value);
    File& operator>>(uint8_t &value);
    File& operator>>(Entry &entry);

protected:
    std::unordered_map<std::string, Dat::Entry> _entries;
    std::ifstream _stream;
    std::string _filename;
    void _initialize();
};

}
}
}
#endif // FALLTERGEIST_FORMAT_DAT_FILE_H
