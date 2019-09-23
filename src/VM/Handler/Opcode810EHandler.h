#pragma once

#include "../../VM/IFalloutOpcode.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            class Opcode810E : virtual public IFalloutOpcode
            {
                public:
                    Opcode810E() = default;
            };
        }
    }
}
