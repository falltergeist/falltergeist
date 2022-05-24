// Project includes
#include "../../VM/Handler/Opcode8151Handler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8151::Opcode8151(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode8151::_run()
            {
                logger->debug() << "[8151] [=] int critter_is_fleeing(void* who)" << std::endl;
                _script->dataStack()->popObject();
                _script->dataStack()->push(0);
            }
        }
    }
}
