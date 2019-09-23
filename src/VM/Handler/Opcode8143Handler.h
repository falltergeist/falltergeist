#pragma once

#include "../../VM/IFalloutOpcode.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            class Opcode8143 : virtual public IFalloutOpcode
            {
                public:
                    Opcode8143() = default;
            };
        }
    }
}
