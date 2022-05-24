// Project includes
#include "../Dat/Stream.h"
#include "../Mve/Chunk.h"
#include "../Mve/File.h"
#include "../../Exception.h"

// Third-party includes

// stdlib
#include <cstring>

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
                int16_t check1 = 0, check2 = 0, check3 = 0;

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
