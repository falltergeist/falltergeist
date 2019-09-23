#pragma once

#include "../../VM/IFalloutOpcode.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            class Opcode810D : virtual public IFalloutOpcode
            {
                public:
                    Opcode810D() = default;
            };
        }
    }
}
