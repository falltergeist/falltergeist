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
            Opcode8018::Opcode8018(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode8018::_run(VM::Script& script)
            {
                _logger->debug() << "[8018] [*] op_swap" << std::endl;
                script.dataStack()->swap();
            }
        }
    }
}
