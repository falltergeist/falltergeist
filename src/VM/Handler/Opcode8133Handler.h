#pragma once

#include "../../VM/IFalloutOpcode.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            class Opcode8133 : virtual public IFalloutOpcode
            {
                public:
                    Opcode8133() = default;
            };
        }
    }
}
