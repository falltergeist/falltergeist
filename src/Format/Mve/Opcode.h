#pragma once

// Project includes
#include "../../Base/Buffer.h"

// Third-party includes

// stdlib
#include <cstdint>

namespace Falltergeist
{
    namespace Format
    {
        namespace Mve
        {
            class Opcode
            {
                public:
                    Opcode(uint16_t length);

                    uint16_t length() const;

                    uint8_t type() const;
                    void setType(uint8_t value);

                    uint8_t version() const;
                    void setVersion(uint8_t value);

                    uint8_t* data();

                protected:
                    uint16_t _length = 0;
                    uint8_t _type = 0;
                    uint8_t _version = 0;
                    Base::Buffer<uint8_t> _data;
            };
        }
    }
}
