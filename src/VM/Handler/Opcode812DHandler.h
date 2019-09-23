#pragma  once

#include "../../VM/IFalloutOpcode.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            class Opcode812D : virtual public IFalloutOpcode
            {
                public:
                    Opcode812D() = default;
            };
        }
    }
}
