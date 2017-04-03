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
#include "../../Format/Aaf/File.h"
#include "../../Format/Acm/File.h"
#include "../../Format/Bio/File.h"
#include "../../Format/Dat/Entry.h"
#include "../../Format/Dat/File.h"
#include "../../Format/Dat/Item.h"
#include "../../Format/Dat/MiscFile.h"
#include "../../Format/Dat/Stream.h"
#include "../../Format/Fon/File.h"
#include "../../Format/Frm/File.h"
#include "../../Format/Gam/File.h"
#include "../../Format/Gcd/File.h"
#include "../../Format/Int/File.h"
#include "../../Format/Map/File.h"
#include "../../Format/Msg/File.h"
#include "../../Format/Mve/File.h"
#include "../../Format/Lip/File.h"
#include "../../Format/Lst/File.h"
#include "../../Format/Pal/File.h"
#include "../../Format/Pro/File.h"
#include "../../Format/Rix/File.h"
#include "../../Format/Sve/File.h"
#include "../../Format/Txt/CityFile.h"
#include "../../Format/Txt/CSVBasedFile.h"
#include "../../Format/Txt/MapsFile.h"
#include "../Txt/WorldmapFile.h"

// Third party includes

namespace Falltergeist
{
namespace Format
{
namespace Dat
{

File::File()
{
    _initialize();
}

File::File(const std::string& filename)
{
    setFilename(filename);
    _initialize();
}

File::~File()
{
    for (auto item : _items)
    {
        delete item.second;
    }

    for (auto entry : _entries)
    {
        delete entry;
    }
    delete _stream;
}

std::string File::filename()
{
    return _filename;
}

File* File::setFilename(const std::string& filename)
{
    _filename = filename;
    return this;
}

void File::_initialize()
{
    if (_initialized) return;
    _initialized = true;

    _stream = new std::ifstream();
    _stream->open(filename(), std::ios_base::binary);
    if (!_stream->is_open())
    {
        throw Exception("File::_initialize() - can't open stream: " + filename());
    }

    unsigned int FileSize;
    unsigned int filesTreeSize;
    unsigned int filesTotalNumber;

    // reading data size from dat file
    setPosition(size() - 4);
    *this >> FileSize;
    if (FileSize != size())
    {
        throw Exception("File::items() - wrong file size");
    }
    // reading size of files tree
    setPosition(size() - 8);
    *this >> filesTreeSize;

    // reading total number of items in dat file
    setPosition(size() - filesTreeSize - 8);
    *this >> filesTotalNumber;

    //reading files data one by one
    for (unsigned int i = 0; i != filesTotalNumber; ++i)
    {
        auto entry = new Entry(this);

        *this >> *entry;

        _entries.push_back(entry);
    }
}

File* File::setPosition(unsigned int position)
{
    _stream->seekg(position, std::ios::beg);
    return this;
}

unsigned int File::position()
{
    return static_cast<unsigned>(_stream->tellg());
}

unsigned int File::size(void)
{
    auto oldPosition = _stream->tellg();
    _stream->seekg(0,std::ios::end);
    auto currentPosition = _stream->tellg();
    _stream->seekg(oldPosition, std::ios::beg);
    return static_cast<unsigned>(currentPosition);
}

File* File::skipBytes(unsigned int numberOfBytes)
{
    setPosition(position() + numberOfBytes);
    return this;
}

File* File::readBytes(char * destination, unsigned int numberOfBytes)
{
    unsigned int position = this->position();
    _stream->read(destination, numberOfBytes);
    setPosition(position + numberOfBytes);
    return this;
}

template <class T>
inline T* itemFromEntry(Entry& entry)
{
    return new T(Stream(entry));
}

Item* File::_createItemByName(const std::string& filename, Entry& entry)
{
    std::string extension = filename.substr(filename.length() - 3, 3);

    if (extension == "aaf") return itemFromEntry<Aaf::File>(entry);
    else if (extension == "acm") return itemFromEntry<Acm::File>(entry);
    else if (extension == "bio") return itemFromEntry<Bio::File>(entry);
    else if (extension == "fon") return itemFromEntry<Fon::File>(entry);
    else if (extension == "frm") return itemFromEntry<Frm::File>(entry);
    else if (extension == "gam") return itemFromEntry<Gam::File>(entry);
    else if (extension == "gcd") return itemFromEntry<Gcd::File>(entry);
    else if (extension == "int") return itemFromEntry<Int::File>(entry);
    else if (extension == "lip") return itemFromEntry<Lip::File>(entry);
    else if (extension == "lst") return itemFromEntry<Lst::File>(entry);
    else if (extension == "map") return itemFromEntry<Map::File>(entry);
    else if (extension == "msg") return itemFromEntry<Msg::File>(entry);
    else if (extension == "mve") return itemFromEntry<Mve::File>(entry);
    else if (extension == "pal") return itemFromEntry<Pal::File>(entry);
    else if (extension == "pro") return itemFromEntry<Pro::File>(entry);
    else if (extension == "rix") return itemFromEntry<Rix::File>(entry);
    else if (extension == "sve") return itemFromEntry<Sve::File>(entry);
    else if (filename == "data/city.txt")     return itemFromEntry<Txt::CityFile>(entry);
    else if (filename == "data/enddeath.txt") return itemFromEntry<Txt::EndDeathFile>(entry);
    else if (filename == "data/endgame.txt")  return itemFromEntry<Txt::EndGameFile>(entry);
    else if (filename == "data/genrep.txt")   return itemFromEntry<Txt::GenRepFile>(entry);
    else if (filename == "data/holodisk.txt") return itemFromEntry<Txt::HolodiskFile>(entry);
    else if (filename == "data/karmavar.txt") return itemFromEntry<Txt::KarmaVarFile>(entry);
    else if (filename == "data/maps.txt")     return itemFromEntry<Txt::MapsFile>(entry);
    else if (filename == "data/quests.txt")   return itemFromEntry<Txt::QuestsFile>(entry);
    else if (filename == "data/worldmap.txt") return itemFromEntry<Txt::WorldmapFile>(entry);
    else return itemFromEntry<Format::Dat::MiscFile>(entry);
}

Item* File::item(const std::string& filename)
{
    using std::move;
    if (_items.find(filename) != _items.end())
    {
        return _items.at(filename);
    }

    for (auto entry : _entries)
    {
        if (entry->filename() != filename) continue;

        auto item = _createItemByName(filename, *entry);
        item->setFilename(filename);
        if (item != nullptr)
        {
            _items.insert(std::make_pair(filename, item));
        }
        return item;
    }

    return nullptr;
}

File& File::operator>>(int32_t &value)
{
    readBytes(reinterpret_cast<char *>(&value), sizeof(value));
    return *this;
}

File& File::operator>>(uint32_t &value)
{
    return *this >> (int32_t&) value;
}

File& File::operator>>(int16_t &value)
{
    readBytes(reinterpret_cast<char *>(&value), sizeof(value));
    return *this;
}

File& File::operator>>(uint16_t &value)
{
    return *this >> (int16_t&) value;
}

File& File::operator>>(int8_t &value)
{
    readBytes(reinterpret_cast<char *>(&value), sizeof(value));
    return *this;
}

File& File::operator>>(uint8_t &value)
{
    return *this >> (int8_t&) value;
}

File& File::operator>>(Entry& entry)
{
    uint32_t filenameSize;
    uint8_t compressed;
    uint32_t unpackedSize;
    uint32_t packedSize;
    uint32_t dataOffset;

    *this >> filenameSize;

    std::string filename;
    filename.resize(filenameSize);
    readBytes(&filename[0], filenameSize);
    entry.setFilename(filename);

    *this >> compressed >> unpackedSize >> packedSize >> dataOffset;

    entry.setCompressed((bool) compressed);
    entry.setUnpackedSize(unpackedSize);
    entry.setPackedSize(packedSize);
    entry.setDataOffset(dataOffset);

    return *this;
}

}
}
}
