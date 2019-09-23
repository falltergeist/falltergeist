#pragma once

#include "../../VM/IFalloutOpcode.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            class Opcode80FC : virtual public IFalloutOpcode
            {
                public:
                    Opcode80FC() = default;
            };
        }
    }
}
