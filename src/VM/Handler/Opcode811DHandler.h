#pragma once

#include "../../VM/IFalloutOpcode.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            class Opcode811D : virtual public IFalloutOpcode
            {
                public:
                    Opcode811D() = default;
            };
        }
    }
}
