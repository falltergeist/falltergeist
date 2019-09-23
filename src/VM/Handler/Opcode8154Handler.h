#pragma once

#include "../../VM/IFalloutOpcode.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            class Opcode8154 : virtual public IFalloutOpcode
            {
                public:
                    Opcode8154(std::shared_ptr<VM::Script> script) = default;
            };
        }
    }
}
