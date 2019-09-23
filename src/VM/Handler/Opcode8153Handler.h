#pragma once

#include "../../VM/IFalloutOpcode.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            class Opcode8153 : virtual public IFalloutOpcode
            {
                public:
                    Opcode8153() = default;
            };
        }
    }
}
