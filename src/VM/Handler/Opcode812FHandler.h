#pragma once

#include "../../VM/IFalloutOpcode.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            class Opcode812F : virtual public IFalloutOpcode
            {
                public:
                    Opcode812F() = default;
            };
        }
    }
}
