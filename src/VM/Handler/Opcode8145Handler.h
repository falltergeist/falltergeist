#pragma once

#include "../../VM/IFalloutOpcode.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            class Opcode8145 : virtual public IFalloutOpcode
            {
                public:
                    Opcode8145() = default;
            };
        }
    }
}
