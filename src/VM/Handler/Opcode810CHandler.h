#pragma once

#include "../../VM/IFalloutOpcode.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            class Opcode810C : virtual public IFalloutOpcode
            {
                public:
                    Opcode810C() = default;
            };
        }
    }
}
