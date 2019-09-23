#pragma once

#include "../../VM/IFalloutOpcode.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            class OpcodeA001 : virtual public IFalloutOpcode
            {
                public:
                    OpcodeA001() = default;
            };
        }
    }
}
