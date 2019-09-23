#pragma once

#include "../../VM/IFalloutOpcode.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            class Opcode80D3 : virtual public IFalloutOpcode
            {
                public:
                    Opcode80D3() = default;
            };
        }
    }
}
