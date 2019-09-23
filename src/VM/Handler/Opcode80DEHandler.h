#pragma once

#include "../../VM/IFalloutOpcode.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            class Opcode80DE : virtual public IFalloutOpcode
            {
                public:
                    Opcode80DE() = default;
            };
        }
    }
}
