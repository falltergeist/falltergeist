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
            class Opcode8014 final : public OpcodeHandler
            {
                public:
                    Opcode8014(std::shared_ptr<ILogger> logger);

                private:
                    std::shared_ptr<ILogger> _logger;
                    void _run(VM::Script& script) override;
            };

        }
    }
}
