#pragma once

// Project includes
#include "../VM/OpcodeHandler.h"

// Third-party includes

// stdlib
#include <memory>

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
