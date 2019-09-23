#pragma once

#include "../../VM/IFalloutOpcode.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            class Opcode8138 : virtual public IFalloutOpcode
            {
                public:
                    Opcode8138() = default;
            };
        }
    }
}
