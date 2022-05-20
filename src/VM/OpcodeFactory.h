#pragma once

#include <memory>
#include "../VM/OpcodeHandler.h"

namespace Falltergeist
{
    namespace VM
    {
        class Script;

        class OpcodeFactory
        {
            public:
                static std::unique_ptr<OpcodeHandler> createOpcode(unsigned int number, VM::Script *script);
        };
    }
}
