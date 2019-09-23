#pragma once

#include "../../VM/IFalloutOpcode.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            class Opcode80FB : virtual public IFalloutOpcode
            {
                public:
                    Opcode80FB(std::shared_ptr<VM::Script> script) = default;
            };
        }
    }
}
