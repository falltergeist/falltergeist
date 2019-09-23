#pragma once

#include "../../VM/IFalloutOpcode.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            class Opcode8150 : virtual public IFalloutOpcode
            {
                public:
                    Opcode8150() = default;
            };
        }
    }
}
