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

// Falltergeist includes
#include "../../Format/Dat/Stream.h"
#include "../../Format/Int/File.h"
#include "../../Format/Int/Procedure.h"
#include "../../Exception.h"

// Third party includes

namespace Falltergeist
{
namespace Format
{
namespace Int
{

File::File(Dat::Stream&& stream) : _stream(std::move(stream))
{
    _stream.setPosition(0);

    // Initialization code goes here
    _stream.setPosition(42);

    // Procedures table
    uint32_t proceduresCount = _stream.uint32();

    std::vector<uint32_t> procedureNameOffsets;

    for (unsigned i = 0; i != proceduresCount; ++i)
    {
        _procedures.emplace_back();
        auto& procedure = _procedures.back();

        procedureNameOffsets.push_back(_stream.uint32());
        procedure.setFlags(_stream.uint32());
        procedure.setDelay(_stream.uint32());
        procedure.setConditionOffset(_stream.uint32());
        procedure.setBodyOffset(_stream.uint32());
        procedure.setArgumentsCounter(_stream.uint32());
    }

    // Identifiers table
    uint32_t tableSize = _stream.uint32();
    unsigned j = 0;
    while (j < tableSize)
    {
        uint16_t nameLength = _stream.uint16();
        j += 2;

        uint32_t nameOffset = j + 4;
        std::string name;
        for (unsigned i = 0; i != nameLength; ++i, ++j)
        {
            uint8_t ch = _stream.uint8();
            if (ch != 0) name.push_back(ch);
        }

        _identifiers.insert(std::make_pair(nameOffset, name)); // names of functions and variables
    }

    _stream.skipBytes(4); // signature 0xFFFFFFFF

    for (unsigned i = 0; i != procedureNameOffsets.size(); ++i)
    {
        _procedures.at(i).setName(_identifiers.at(procedureNameOffsets.at(i)));
    }

    // STRINGS TABLE
    uint32_t stringsTable = _stream.uint32();

    if (stringsTable != 0xFFFFFFFF)
    {
        uint32_t j = 0;
        while (j < stringsTable)
        {
            uint16_t length = _stream.uint16();
            j += 2;
            uint32_t nameOffset = j + 4;
            std::string name;
            for (unsigned i = 0; i != length; ++i, ++j)
            {
                uint8_t ch = _stream.uint8();
                if (ch != 0) name.push_back(ch);
            }
            _strings.insert(std::make_pair(nameOffset, name));
        }
    }
}

const std::map<unsigned int, std::string>& File::identifiers() const
{
    return _identifiers;
}

const std::map<unsigned int, std::string>& File::strings() const
{
    return _strings;
}

size_t File::position() const
{
    return _stream.position();
}

void File::setPosition(size_t pos)
{
    _stream.setPosition(pos);
}

size_t File::size() const
{
    return _stream.size();
}

uint16_t File::readOpcode()
{
    return _stream.uint16();
}

uint32_t File::readValue()
{
    return _stream.uint32();
}

const std::vector<Procedure>& File::procedures() const
{
    return _procedures;
}

const Procedure* File::procedure(const std::string& name) const
{
    for (auto& procedure : _procedures)
    {
        if (procedure.name() == name)
        {
            return &procedure;
        }
    }
    return nullptr;
}

}
}
}
