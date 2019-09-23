#pragma once

#include "../../VM/IFalloutOpcode.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            class Opcode80D2 : virtual public IFalloutOpcode
            {
                public:
                    Opcode80D2() = default;
            };
        }
    }
}
