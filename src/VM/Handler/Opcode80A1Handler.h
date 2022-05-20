#pragma once

#include "../../VM/OpcodeHandler.h"
#include "../../ILogger.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            class Opcode80A1 final : public OpcodeHandler
            {
                public:
                    Opcode80A1(VM::Script *script, std::shared_ptr<ILogger> logger);

                private:
                    std::shared_ptr<ILogger> logger;
                    void _run() override;
            };
        }
    }
}
