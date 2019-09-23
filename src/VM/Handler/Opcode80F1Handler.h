#pragma once

#include "../../VM/IFalloutOpcode.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            class Opcode80F1 : virtual public IFalloutOpcode
            {
                public:
                    Opcode80F1() = default;
            };
        }
    }
}
