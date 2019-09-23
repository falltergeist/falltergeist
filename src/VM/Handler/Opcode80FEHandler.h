#pragma once

#include "../../VM/IFalloutOpcode.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            class Opcode80FE : virtual public IFalloutOpcode
            {
                public:
                    Opcode80FE() = default;
            };
        }
    }
}
