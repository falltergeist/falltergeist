#pragma once

#include "../../VM/IFalloutOpcode.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            class Opcode810A : virtual public IFalloutOpcode
            {
                public:
                    Opcode810A() = default;
            };
        }
    }
}
