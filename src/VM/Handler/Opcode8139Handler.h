#pragma once

#include "../../VM/IFalloutOpcode.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            class Opcode8139 : virtual public IFalloutOpcode
            {
                public:
                    Opcode8139() = default;
            };
        }
    }
}
