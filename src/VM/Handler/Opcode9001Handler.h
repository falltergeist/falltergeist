#pragma once

#include "../../VM/IFalloutOpcode.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            class Opcode9001 : virtual public IFalloutOpcode
            {
                public:
                    Opcode9001() = default;
            };
        }

    }
}
