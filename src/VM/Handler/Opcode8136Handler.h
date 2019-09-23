#pragma once

#include "../../VM/IFalloutOpcode.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            class Opcode8136 : virtual public IFalloutOpcode
            {
                public:
                    Opcode8136() = default;
            };
        }
    }
}
