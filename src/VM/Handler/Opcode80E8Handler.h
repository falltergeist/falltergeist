#pragma once

#include "../../VM/IFalloutOpcode.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            class Opcode80E8 : virtual public IFalloutOpcode
            {
                public:
                    Opcode80E8() = default;
            };
        }
    }
}
