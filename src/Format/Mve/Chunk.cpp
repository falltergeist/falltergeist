#pragma once

#include "../Mve/Chunk.h"

namespace Falltergeist
{
    namespace Format
    {
        namespace Mve
        {
            uint16_t Chunk::length() const
            {
                return _length;
            }

            void Chunk::setLength(uint16_t value)
            {
                _length = value;
            }

            uint16_t Chunk::type() const
            {
                return _type;
            }

            void Chunk::setType(uint16_t value)
            {
                _type = value;
            }

            std::vector<Opcode>& Chunk::opcodes()
            {
                return _opcodes;
            }

            const std::vector<Opcode>& Chunk::opcodes() const
            {
                return _opcodes;
            }
        }
    }
}
