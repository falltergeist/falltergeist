#pragma once

#include "../../VM/IFalloutOpcode.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            class Opcode80DC : virtual public IFalloutOpcode
            {
                public:
                    Opcode80DC() = default;
            };
        }
    }
}
