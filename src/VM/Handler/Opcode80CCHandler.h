#pragma once

#include "../../VM/IFalloutOpcode.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            class Opcode80CC : virtual public IFalloutOpcode
            {
                public:
                    Opcode80CC() = default;
            };
        }
    }
}
