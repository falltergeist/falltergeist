#pragma once

#include "../../VM/IFalloutOpcode.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            class Opcode80DF : virtual public IFalloutOpcode
            {
                public:
                    Opcode80DF() = default;
            };
        }
    }
}
