#pragma once

#include "../../VM/IFalloutOpcode.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            class Opcode80F2 : virtual public IFalloutOpcode
            {
                public:
                    Opcode80F2() = default;
            };
        }
    }
}
