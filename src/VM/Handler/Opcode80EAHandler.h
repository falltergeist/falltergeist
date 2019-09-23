#pragma once

#include "../../VM/IFalloutOpcode.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            class Opcode80EA : virtual public IFalloutOpcode
            {
                public:
                    Opcode80EA() = default;
            };
        }
    }
}
