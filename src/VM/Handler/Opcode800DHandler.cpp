// Project includes
#include "../../VM/Handler/Opcode800DHandler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode800D::Opcode800D(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode800D::_run(VM::Script& script)
            {
                _logger->debug() << "[800D] [*] op_d_to_a" << std::endl;
                script.returnStack()->push(script.dataStack()->pop());
            }
        }
    }
}
