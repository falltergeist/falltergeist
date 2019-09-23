#pragma once

#include "../../VM/IFalloutOpcode.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            class Opcode80DA : virtual public IFalloutOpcode
            {
                public:
                    Opcode80DA() = default;
            };
        }
    }
}
