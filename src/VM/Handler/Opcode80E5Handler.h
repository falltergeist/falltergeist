#pragma once

#include "../../VM/IFalloutOpcode.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            class Opcode80E5 : virtual public IFalloutOpcode
            {
                public:
                    Opcode80E5() = default;
            };
        }
    }
}
