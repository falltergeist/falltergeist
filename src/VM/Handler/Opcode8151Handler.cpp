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
            Opcode8151::Opcode8151(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode8151::_run(VM::Script& script)
            {
                _logger->debug() << "[8151] [=] int critter_is_fleeing(void* who)" << std::endl;
                script.dataStack()->popObject();
                script.dataStack()->push(0);
            }
        }
    }
}
