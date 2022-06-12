// Project includes
#include "../../VM/Handler/Opcode8019Handler.h"
#include "../../VM/Script.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace VM
    {
        namespace Handler
        {
            Opcode8019::Opcode8019(std::shared_ptr<ILogger> logger) : OpcodeHandler(), _logger(logger)
            {

            }

            void Opcode8019::_run(VM::Script& script)
            {
                _logger->debug() << "[8019] [*] op_swapa" << std::endl;
                script.returnStack()->swap();
            }
        }
    }
}
