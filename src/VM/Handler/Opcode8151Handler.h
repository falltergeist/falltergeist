#pragma once

#include "../../VM/IFalloutOpcode.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            class Opcode8151 : virtual public IFalloutOpcode
            {
                public:
                    Opcode8151() = default;
            };
        }
    }
}
