#pragma once

#include "../../VM/IFalloutOpcode.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            class Opcode80CF : virtual public IFalloutOpcode
            {
                public:
                    Opcode80CF() = default;
            };
        }
    }
}
