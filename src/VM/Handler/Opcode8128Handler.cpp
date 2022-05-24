// Project includes
#include "../../VM/Handler/Opcode8128Handler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8128::Opcode8128(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode8128::_run()
            {
                logger->debug() << "[8128] [=] int combat_is_initialized()" << std::endl;
                _script->dataStack()->push(0);
            }
        }
    }
}
