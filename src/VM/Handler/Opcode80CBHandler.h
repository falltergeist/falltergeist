#pragma once

#include "../../VM/IFalloutOpcode.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            class Opcode80CB : virtual public IFalloutOpcode
            {
                public:
                    Opcode80CB() = default;
            };
        }
    }
}
