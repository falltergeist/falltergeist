// Project includes
#include "../../VM/Handler/Opcode80FBHandler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode80FB::Opcode80FB(VM::Script *script, std::shared_ptr<ILogger> logger) : OpcodeHandler(script)
            {
                this->logger = std::move(logger);
            }

            void Opcode80FB::_run()
            {
                logger->debug() << "[80FB] [=] int critter_state(void* who)" << std::endl;
                _script->dataStack()->popObject();
                _script->dataStack()->push(0);
            }
        }
    }
}
