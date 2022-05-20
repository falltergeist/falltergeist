#pragma once

#include "../../ILogger.h"
#include "../../VM/OpcodeHandler.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            class Opcode803F : public OpcodeHandler
            {
                public:
                    Opcode803F(VM::Script *script, std::shared_ptr<ILogger> logger);

                private:
                    std::shared_ptr<ILogger> logger;
                    void _run() override;
            };
        }
    }
}
