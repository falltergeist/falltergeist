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
#include <cstring>

// Falltergeist includes
#include "../Dat/Stream.h"
#include "../Mve/Chunk.h"
#include "../Mve/File.h"
#include "../../Exception.h"

// Third party includes

namespace Falltergeist
{
namespace Format
{
namespace Mve
{

File::File(Dat::Stream&& stream) : _stream(std::move(stream))
{
    _stream.setPosition(0);
    _stream.setEndianness(ENDIANNESS::LITTLE);
    // header
    const char  MVE_HEADER[]  = "Interplay MVE File\x1A";
    const int16_t MVE_HDRCONST1 = 0x001A;
    const int16_t MVE_HDRCONST2 = 0x0100;
    const int16_t MVE_HDRCONST3 = 0x1133;
    int16_t check1, check2, check3;

    char head[20];
    _stream.readBytes((uint8_t*)head,20);

    if (strncmp(head,MVE_HEADER,20)!=0)
    {
        throw Exception("Invalid MVE file.!");
    }
    _stream >> check1 >> check2 >> check3;
    if  (!(check1 == MVE_HDRCONST1 && check2 == MVE_HDRCONST2 && check3 == MVE_HDRCONST3))
    {
        throw Exception("Invalid MVE file.");
    }
}

std::unique_ptr<Chunk> File::getNextChunk()
{
    if (_stream.position() < _stream.size())
    {
        auto chunk = std::make_unique<Chunk>();
        chunk->setLength(_stream.uint16());
        chunk->setType(_stream.uint16());
        for (size_t i = 0; i < chunk->length();)
        {
            chunk->opcodes().emplace_back(_stream.uint16());
            auto& opcode = chunk->opcodes().back();
            opcode.setType(_stream.uint8());
            opcode.setVersion(_stream.uint8());
            _stream.readBytes(opcode.data(), opcode.length());
            i += opcode.length() + 4;
        }
        return chunk;
    }
    return nullptr;
}

void File::setPosition(unsigned int position)
{
    _stream.setPosition(position);
}

}
}
}
