#pragma once

#include "../../VM/IFalloutOpcode.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            class Opcode80FD : virtual public IFalloutOpcode
            {
                public:
                    Opcode80FD() = default;
            };
        }
    }
}
