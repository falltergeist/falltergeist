#pragma once

#include "../../VM/IFalloutOpcode.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            class Opcode80CE : virtual public IFalloutOpcode
            {
                public:
                    Opcode80CE() = default;
            };
        }
    }
}
