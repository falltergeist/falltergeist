// Project includes
#include "../../VM/Handler/Opcode8125Handler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8125::Opcode8125(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode8125::_run()
            {
                logger->debug() << "[8125] [=] void party_remove(void* who)" << std::endl;
                _script->dataStack()->popObject();
            }
        }
    }
}
