// Project includes
#include "../../VM/Handler/Opcode80B9Handler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80B9::Opcode80B9(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80B9::_run()
            {
                logger->debug() << "[80B9] script_overrides" << std::endl;
                _script->setOverrides(true);
            }
        }
    }
}
