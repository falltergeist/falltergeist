// Project includes
#include "../../VM/Handler/Opcode801AHandler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode801A::Opcode801A(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode801A::_run(VM::Script& script)
            {
                _logger->debug() << "[801A] [*] op_pop" << std::endl;
                script.dataStack()->pop();
            }
        }
    }
}
