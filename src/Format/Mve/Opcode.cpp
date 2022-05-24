// Project includes
#include "../Mve/Opcode.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace Format
    {
        namespace Mve
        {
            Opcode::Opcode(uint16_t length) : _data(length)
            {
            }

            uint16_t Opcode::length() const
            {
                return static_cast<uint16_t>(_data.size());
            }

            uint8_t Opcode::type() const
            {
                return _type;
            }

            void Opcode::setType(uint8_t value)
            {
                _type = value;
            }

            uint8_t Opcode::version() const
            {
                return _version;
            }

            void Opcode::setVersion(uint8_t value)
            {
                _version = value;
            }

            uint8_t* Opcode::data()
            {
                return _data.data();
            }
        }
    }
}
