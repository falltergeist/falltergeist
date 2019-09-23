#pragma once

#include "../../VM/IFalloutOpcode.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            class Opcode80E3 : virtual public IFalloutOpcode
            {
                public:
                    Opcode80E3() = default;
            };
        }
    }
}
