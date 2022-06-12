// Project includes
#include "../../VM/Handler/Opcode800CHandler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode800C::Opcode800C(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode800C::_run(VM::Script& script)
            {
                _logger->debug() << "[800C] [*] op_a_to_d" << std::endl;
                script.dataStack()->push(script.returnStack()->pop());
            }
        }
    }
}
