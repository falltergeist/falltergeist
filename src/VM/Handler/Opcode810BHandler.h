#pragma once

#include "../../VM/IFalloutOpcode.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            class Opcode810B : virtual public IFalloutOpcode
            {
                public:
                    Opcode810B() = default;
            };
        }
    }
}
