#pragma once

// Project includes
#include "../Mve/Opcode.h"

// Third-party includes

// stdlib
#include <memory>
#include <vector>

namespace Falltergeist
{
    namespace Format
    {
        namespace Mve
        {
            class Chunk
            {
                public:
                    uint16_t length() const;
                    void setLength(uint16_t value);

                    uint16_t type() const;
                    void setType(uint16_t value);

                    std::vector<Opcode>& opcodes();
                    const std::vector<Opcode>& opcodes() const;

                protected:
                    uint16_t _length;
                    uint16_t _type;
                    std::vector<Opcode> _opcodes;
            };
        }
    }
}
