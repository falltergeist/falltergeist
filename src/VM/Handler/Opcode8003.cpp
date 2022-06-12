// Project includes
#include "../../VM/Handler/Opcode8003.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8003::Opcode8003(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode8003::_run(VM::Script& script)
            {
                _logger->debug() << "[8003] op_critical_done" << std::endl;
            }
        }
    }
}
