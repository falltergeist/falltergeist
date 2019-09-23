#pragma once

#include "../../VM/IFalloutOpcode.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            class Opcode80FF : virtual public IFalloutOpcode
            {
                public:
                    Opcode80FF() = default;
            };
        }
    }
}
