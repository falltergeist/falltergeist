#pragma once

#include "../../VM/IFalloutOpcode.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            class Opcode80D4 : virtual public IFalloutOpcode
            {
                public:
                    Opcode80D4() = default;
            };
        }
    }
}
