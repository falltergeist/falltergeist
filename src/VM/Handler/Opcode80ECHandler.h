#pragma once

#include "../../VM/IFalloutOpcode.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            class Opcode80EC : virtual public IFalloutOpcode
            {
                public:
                    Opcode80EC() = default;
            };
        }
    }
}
