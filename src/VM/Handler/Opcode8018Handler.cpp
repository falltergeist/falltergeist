// Project includes
#include "../../VM/Handler/Opcode8018Handler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8018::Opcode8018(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode8018::_run()
            {
                logger->debug() << "[8018] [*] op_swap" << std::endl;
                _script->dataStack()->swap();
            }
        }
    }
}
