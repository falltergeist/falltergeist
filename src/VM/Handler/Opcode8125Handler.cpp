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
            Opcode8125::Opcode8125(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode8125::_run(VM::Script& script)
            {
                _logger->debug() << "[8125] [=] void party_remove(void* who)" << std::endl;
                script.dataStack()->popObject();
            }
        }
    }
}
