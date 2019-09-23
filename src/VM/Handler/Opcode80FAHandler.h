#pragma once

#include "../../VM/IFalloutOpcode.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            class Opcode80FA : virtual public IFalloutOpcode
            {
                public:
                    Opcode80FA() = default;
            };
        }
    }
}
