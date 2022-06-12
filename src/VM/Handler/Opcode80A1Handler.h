#pragma once

// Project includes
#include "../../VM/OpcodeHandler.h"
#include "../../ILogger.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            class Opcode80A1 final : public OpcodeHandler
            {
                public:
                    Opcode80A1(std::shared_ptr<ILogger> logger);

                private:
                    std::shared_ptr<ILogger> _logger;

                    void _run(VM::Script& script) override;
            };
        }
    }
}
