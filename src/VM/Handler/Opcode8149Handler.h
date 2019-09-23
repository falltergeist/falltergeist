#pragma once

#include "../../VM/IFalloutOpcode.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            class Opcode8149 : virtual public IFalloutOpcode
            {
                public:
                    Opcode8149() = default;
            };
        }
    }
}
