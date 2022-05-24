#pragma once

// Project includes
#include "../../ILogger.h"
#include "../../VM/OpcodeHandler.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            class Opcode814E : public OpcodeHandler
            {
                public:
                    Opcode814E(VM::Script *script, std::shared_ptr<ILogger> logger);

                private:
                    std::shared_ptr<ILogger> logger;
                    void _run() override;
            };
        }
    }
}
