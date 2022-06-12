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
            Opcode80FB::Opcode80FB(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger) {
            }

            void Opcode80FB::_run(VM::Script& script)
            {
                _logger->debug() << "[80FB] [=] int critter_state(void* who)" << std::endl;
                script.dataStack()->popObject();
                script.dataStack()->push(0);
            }
        }
    }
}
